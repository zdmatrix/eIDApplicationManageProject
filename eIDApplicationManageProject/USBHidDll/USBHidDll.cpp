// USBHidDll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "USBHidDll.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

USBHIDDLL_API			bool bInitWriteHandle(PSP_DEVICE_INTERFACE_DETAIL_DATA detailData, PHANDLE pWriteHandle){
				 
				 *pWriteHandle = CreateFile( 
					 detailData->DevicePath,
					 GENERIC_WRITE,
					 FILE_SHARE_READ | FILE_SHARE_WRITE,
					 (LPSECURITY_ATTRIBUTES)NULL,
					 OPEN_EXISTING,
					 0,						//for write
					 NULL);

				 if(*pWriteHandle != INVALID_HANDLE_VALUE){
					 return true;
				 }else{
					 return false;
				 }
			 }

USBHIDDLL_API			 bool bInitReadHandle(PSP_DEVICE_INTERFACE_DETAIL_DATA detailData, PHANDLE pReadHandle){
				
				 *pReadHandle = CreateFile( 
					 detailData->DevicePath,
					 GENERIC_READ,
					 FILE_SHARE_READ | FILE_SHARE_WRITE,
					 (LPSECURITY_ATTRIBUTES)NULL,
					 OPEN_EXISTING,
					 FILE_FLAG_OVERLAPPED,						//for read

					 NULL);

				 if(*pReadHandle != INVALID_HANDLE_VALUE){
					 return true;
				 }else{
					 DWORD err = GetLastError();
					 return false;
				 }
			 }


USBHIDDLL_API			 bool bWrite_ToHIDDevice(PHANDLE pWriteHandle, LPBYTE lpWriteBuff){

				 DWORD			dwNumberOfBytesWrite;
				 HIDP_CAPS		Capabilities;
				 PHIDP_PREPARSED_DATA		HidParsedData;

				 BOOL bResult = false;

				 if(*pWriteHandle != NULL){
					 HidD_GetPreparsedData(*pWriteHandle, &HidParsedData);

					 /* extract the capabilities info */
					 HidP_GetCaps( HidParsedData ,&Capabilities);

					 /* Free the memory allocated when getting the preparsed data */
					 HidD_FreePreparsedData(HidParsedData);

					 bResult = WriteFile(*pWriteHandle, 
						 lpWriteBuff, 
						 Capabilities.OutputReportByteLength, 
						 &dwNumberOfBytesWrite,
						 NULL);


				 }
				 return bResult;

			 }


USBHIDDLL_API			 DWORD dwRead_FromHIDDevice(PHANDLE pReadHandle, BYTE byReadBuff[], DWORD len){

				 DWORD			dwNumberOfBytesRead;
				 DWORD			dwResponseSW = 0;
				 HIDP_CAPS		Capabilities;
				 PHIDP_PREPARSED_DATA		HidParsedData;
				 OVERLAPPED		HidOverlapped;
				 HANDLE			hEvent;

				 LPBYTE	 lpReadBuff = (LPBYTE)malloc(0x21);


				 /* Create a new event for report capture */
				 hEvent = CreateEvent(NULL, TRUE, TRUE, "");

				 /* fill the HidOverlapped structure so that Windows knows which
				 event to cause when the device sends an IN report */
				 HidOverlapped.hEvent = hEvent;
				 HidOverlapped.Offset = 0;
				 HidOverlapped.OffsetHigh = 0;

				 BOOL bResult = false;

				 //			LPCOMMTIMEOUTS lpCommitTimes = (LPCOMMTIMEOUTS)malloc(sizeof(LPCOMMTIMEOUTS));

				 if(*pReadHandle != NULL){
					 HidD_GetPreparsedData(*pReadHandle, &HidParsedData);

					 /* extract the capabilities info */
					 HidP_GetCaps( HidParsedData ,&Capabilities);

					 /* Free the memory allocated when getting the preparsed data */
					 HidD_FreePreparsedData(HidParsedData);

					 bResult = ReadFile(*pReadHandle, 
						 lpReadBuff, 
						 Capabilities.InputReportByteLength,
						 &dwNumberOfBytesRead,
						 (LPOVERLAPPED)&HidOverlapped);


					 if ( bResult == 0 )
					 {
						 // 读取错误信息
						 DWORD dwResult = GetLastError();

						 // I/O端口繁忙
						 if ( dwResult == ERROR_IO_PENDING )
						 {

							 // 需挂起等待
							 dwResult = WaitForSingleObject ( HidOverlapped.hEvent, INFINITE );

							 // I/O端口正常
							 if ( dwResult == WAIT_OBJECT_0 )
							 {
								 // 去读取数据的正常返回值
								 GetOverlappedResult ( *pReadHandle, &HidOverlapped, &dwNumberOfBytesRead, FALSE );
							 }
							 else
							 {
								 //							BOOL bGetTime = GetCommTimeouts(*pReadHandle, lpCommitTimes);
								 free(lpReadBuff);
								 CloseHandle(hEvent);
								 return -1;	// 等待超时
							 }

						 }
						 else
						 {
							 return -1;	// 不明错误
						 }
					 }
				 }
				 for(int i = 0; i < (len + 2); i ++){
					 byReadBuff[i] = *(lpReadBuff + i + 1);
				 }
				 dwResponseSW |= byReadBuff[len];

				 dwResponseSW = (dwResponseSW << 8) | (byReadBuff[len + 1]);
				 free(lpReadBuff);
				 CloseHandle(hEvent);
				 return	dwResponseSW;
			 }


USBHIDDLL_API			 PSP_DEVICE_INTERFACE_DETAIL_DATA bOpenHidDevice(USHORT VID, USHORT PID){
				 GUID HidGuid;
				 HDEVINFO HidDevInfo;						/* handle to structure containing all attached HID Device information */
				 SP_DEVICE_INTERFACE_DATA devInfoData;		/* Information structure for HID devices */
				 BOOL Result = false;								/* result of getting next device information structure */
				 DWORD Index;								/* index of HidDevInfo array entry */
				 DWORD DataSize;								/* size of the DeviceInterfaceDetail structure */		
				 bool GotRequiredSize;					/* 1-shot got device info data structure size flag */
				 DWORD RequiredSize;							/* size of device info data structure */
				 bool DIDResult = false;							/* get device info data result */
				 HIDD_ATTRIBUTES HIDAttrib;					/* HID device attributes */

				 HANDLE HidDevHandle;

				 BOOLEAN bRet = false;

				 PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = NULL;
				 /* initialize variables */
				 GotRequiredSize = FALSE;



				 /* 1) Get the HID Globally Unique ID from the OS */
				 HidD_GetHidGuid(&HidGuid);


				 /* 2) Get an array of structures containing information about
				 all attached and enumerated HIDs */
				 HidDevInfo = SetupDiGetClassDevs(	
					 &HidGuid,
					 NULL, 
					 NULL, 
					 DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
				 //													DIGCF_INTERFACEDEVICE);

				 /* 3) Step through the attached device list 1 by 1 and examine
				 each of the attached devices.  When there are no more entries in
				 the array of structures, the function will return FALSE. */

				 Index = 0;									/* init to first index of array */
				 devInfoData.cbSize = sizeof(devInfoData);	/* set to the size of the structure
															that will contain the device info data */

				 do {
					 /* Get information about the HID device with the 'Index' array entry */
					 Result = SetupDiEnumDeviceInterfaces(	HidDevInfo, 
						 0, 
						 &HidGuid,
						 Index, 
						 &devInfoData);

					 /* If we run into this condition, then there are no more entries
					 to examine, we might as well return FALSE at point */
					 if(Result == FALSE)
					 {

						 /* free HID device info list resources */
						 SetupDiDestroyDeviceInfoList(HidDevInfo);

//						 return bRet;
						 return detailData;
					 }


					 if(GotRequiredSize == FALSE)
					 {
						 /* 3) Get the size of the DEVICE_INTERFACE_DETAIL_DATA
						 structure.  The first call will return an error condition, 
						 but we'll get the size of the strucure */
						 DIDResult = SetupDiGetDeviceInterfaceDetail(	HidDevInfo,
							 &devInfoData,
							 NULL,
							 0,
							 &DataSize,
							 NULL);
						 GotRequiredSize = TRUE;

						 /* allocate memory for the HidDevInfo structure */
						 detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(DataSize);

						 /* set the size parameter of the structure */
						 detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
					 }


					 /* 4) Now call the function with the correct size parameter.  This 
					 function will return data from one of the array members that 
					 Step #2 pointed to.  This way we can start to identify the
					 attributes of particular HID devices.  */
					 DIDResult = SetupDiGetDeviceInterfaceDetail(	HidDevInfo,
						 &devInfoData,
						 detailData,
						 DataSize,
						 &RequiredSize,
						 NULL);


					 /* 5) Open a file handle to the device.  Make sure the
					 attibutes specify overlapped transactions or the IN
					 transaction may block the input thread. */

					 HidDevHandle = CreateFile( detailData->DevicePath,
						 0,
						 FILE_SHARE_READ | FILE_SHARE_WRITE,
						 (LPSECURITY_ATTRIBUTES)NULL,
						 OPEN_EXISTING,
						 NULL,
						 NULL);


					 /* 6) Get the Device VID & PID to see if it's the device we want */
					 if(HidDevHandle != INVALID_HANDLE_VALUE)
					 {
						 HIDAttrib.Size = sizeof(HIDAttrib);
						 HidD_GetAttributes(	HidDevHandle, &HIDAttrib);						
						 if((HIDAttrib.VendorID == VID) && (HIDAttrib.ProductID == PID))
						 {		

							 /* free HID device info list resources */
							 SetupDiDestroyDeviceInfoList(HidDevInfo);

							 bRet = true;	/* found HID device */

						 }
						 else{

							 bRet = false;
						 }
						 /* 7) Close the Device Handle because we didn't find the device
						 with the correct VID and PID */
						 CloseHandle(HidDevHandle);
					 }

					 Index++;	/* increment the array index to search the next entry */

				 } while(Result == TRUE);
//				 return bRet;
				 return detailData;
			 }
