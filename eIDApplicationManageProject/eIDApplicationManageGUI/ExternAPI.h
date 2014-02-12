//#define EXTERNAPI_EXPORTS
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 EXTERNAPI_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// EXTERNAPI_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef EXTERNAPI_EXPORTS
#define EXTERNAPI_API __declspec(dllexport)
#else
#define EXTERNAPI_API __declspec(dllimport)
#endif

#pragma once


void EXTERNAPI_API SetUkeyLastErr(DWORD dwErr);

DWORD EXTERNAPI_API GetUkeyLastErr(void);

//打开UKey
BOOL EXTERNAPI_API UKeyOpen(HANDLE *hUKey);
	
//关闭UKey
BOOL EXTERNAPI_API UKeyClose(HANDLE hUKey);

//验证UKey 的pin 含密码输入框,
BOOL EXTERNAPI_API UKeyVerifyPIN(HANDLE hUKey, const char *Pin, const short PinLen);
BOOL EXTERNAPI_API UKeyCheckPIN(HANDLE hUKey, int nLanguage = 1);
BOOL EXTERNAPI_API UKeyChangePINToUkey(HANDLE hUKey, const char *Pin, const short PinLen);
BOOL EXTERNAPI_API UKeyChangePIN(HANDLE hUKey, int nLanguage = 1);
//去随机数
BOOL EXTERNAPI_API UKeyGetChallange(HANDLE hUKey, unsigned char *Challange, const short Len);

BOOL EXTERNAPI_API UKeyGetContainer(HANDLE hUKey,BYTE *pbContainer,BYTE *pstrCardCt);
BOOL EXTERNAPI_API UKeyGetCspContainerCount(HANDLE hUKey, WORD *wCount, BYTE *pContainers);
BOOL EXTERNAPI_API UKeyFindContainer(HANDLE hUKey,BYTE *pbContainer);
BOOL EXTERNAPI_API UKeyDelContainer(HANDLE hUKey,BYTE *pbContainer);
BOOL EXTERNAPI_API UKeyAddContainer(HANDLE hUKey,BYTE *strCardCt);
BOOL EXTERNAPI_API UKeyUpdateContainer(HANDLE hUKey, BYTE *ContainerName, BYTE *strCardCt);
BOOL EXTERNAPI_API UKeyGenKey(HANDLE hUKey, WORD wKeyPSfi, WORD wKeySSfi);
BOOL EXTERNAPI_API UKeyGetKey(HANDLE hUKey, DWORD sfi, unsigned char KeyFlag, unsigned char *Key);
BOOL EXTERNAPI_API UKeyRSAEncrypt(HANDLE hUKey, DWORD sfi, unsigned char *InData, int *InDataLen, 
					unsigned char *OutData, int *OutDataLen);
BOOL EXTERNAPI_API UKeyRSADecrypt(HANDLE hUKey, DWORD sfi, unsigned char *InData, int *InDataLen, 
					unsigned char *OutData, int *OutDataLen);
BOOL EXTERNAPI_API UKeyRSASignature(HANDLE hUKey, DWORD sfi, unsigned char *InData, int InDataLen, 
					unsigned char *OutData, int *OutDataLen);
BOOL EXTERNAPI_API UKeyRSASignatureVerify(HANDLE hUKey, DWORD sfi, const unsigned char *InData, int InDataLen, 
					unsigned char *OutData, int *OutDataLen);
//证书相关
BOOL EXTERNAPI_API UKeyGetNameFromCN(char *cn,char *name);
BOOL EXTERNAPI_API UKeyGetCertName(BYTE *pbData, DWORD dwLen, char *pcOutName);
BOOL EXTERNAPI_API UKeyAppendCert(HANDLE hUKey, BYTE *pstrCardCt, BYTE *pbData, DWORD dwLen);
BOOL EXTERNAPI_API UKeyGetCert(HANDLE hUKey, BYTE *pstrCardCt, BYTE *pbData, DWORD dwLen);
BOOL EXTERNAPI_API UKeyImportKey(HANDLE hUKey, DWORD sfi, unsigned char *Key);

BOOL EXTERNAPI_API UKeyUnLock(HANDLE hUKey, BYTE *NewPin, int NewPinLen);
BOOL EXTERNAPI_API UKeyGetInfo(HANDLE hUKey,BYTE *Info, int *InfoLen);
BOOL EXTERNAPI_API UKeyGetContainerName(HANDLE hUKey,BYTE *CName, int *CNameLen);
BOOL EXTERNAPI_API UKeySetContainerName(HANDLE hUKey,BYTE *CName, int CNameLen);
BOOL EXTERNAPI_API UKeyClearPin(HANDLE hUKey);

BOOL EXTERNAPI_API UKeyTestDisplayNum(HANDLE hUKey, int num);

