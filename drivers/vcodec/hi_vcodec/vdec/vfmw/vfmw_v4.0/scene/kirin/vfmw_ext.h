#ifndef __VFMW_EXT_H__
#define __VFMW_EXT_H__

#include "vfmw.h"
#include "vfmw_dts.h"

typedef HI_VOID  (*FN_VFMW_OpenModule)(HI_VOID);
typedef HI_VOID  (*FN_VFMW_ExitModule)(HI_VOID);
typedef HI_S32   (*FN_VFMW_Init)(VDEC_OPERATION_S *);
typedef HI_S32   (*FN_VFMW_Exit)(HI_U8);
typedef HI_S32   (*FN_VFMW_Control)(HI_S32, VDEC_CID_E, HI_VOID*, HI_U32);
typedef HI_S32   (*FN_VFMW_Suspend)(HI_VOID);
typedef HI_S32   (*FN_VFMW_Resume)(HI_VOID);
 

typedef struct
{
    FN_VFMW_OpenModule          pfnVfmwOpenModule;
    FN_VFMW_ExitModule          pfnVfmwExitModule;
    FN_VFMW_Init                pfnVfmwInit;
    FN_VFMW_Exit                pfnVfmwExit;
    FN_VFMW_Control             pfnVfmwControl;
    FN_VFMW_Suspend             pfnVfmwSuspend;
    FN_VFMW_Resume              pfnVfmwResume;
}VFMW_EXPORT_FUNC_S;

HI_S32 VFMW_GetFunction(VFMW_EXPORT_FUNC_S **ppVfmwExportFuncs);

#endif
