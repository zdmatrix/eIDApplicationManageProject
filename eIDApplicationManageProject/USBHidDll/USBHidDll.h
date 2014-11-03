//#define USBHIDDLL_EXPORTS
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 USBHIDDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// USBHIDDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef USBHIDDLL_EXPORTS
#define USBHIDDLL_API __declspec(dllexport)
#else
#define USBHIDDLL_API __declspec(dllimport)
#endif

extern "C" {    // this MUST be included

	// These files are in the Windows DDK
	//#include <initguid.h>
#include "hidsdi.h"
#include <setupapi.h>

}


USBHIDDLL_API			bool bInitWriteHandle(PSP_DEVICE_INTERFACE_DETAIL_DATA detailData, PHANDLE pWriteHandle);
USBHIDDLL_API			 bool bInitReadHandle(PSP_DEVICE_INTERFACE_DETAIL_DATA detailData, PHANDLE pReadHandle);
USBHIDDLL_API			 bool bWrite_ToHIDDevice(PHANDLE pWriteHandle, LPBYTE lpWriteBuff);
USBHIDDLL_API			 DWORD dwRead_FromHIDDevice(PHANDLE pReadHandle, BYTE byReadBuff[], DWORD len);
USBHIDDLL_API			 PSP_DEVICE_INTERFACE_DETAIL_DATA bOpenHidDevice(USHORT VID, USHORT PID);
