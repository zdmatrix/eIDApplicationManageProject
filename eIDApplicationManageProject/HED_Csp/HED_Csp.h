// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HED_CSP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HED_CSP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HED_CSP_EXPORTS
#define HED_CSP_API __declspec(dllexport)
#else
#define HED_CSP_API __declspec(dllimport)
#endif

// This class is exported from the HED_Csp.dll
class HED_CSP_API CHED_Csp {
public:
	CHED_Csp(void);
	// TODO: add your methods here.
};

extern HED_CSP_API int nHED_Csp;

HED_CSP_API int fnHED_Csp(void);
