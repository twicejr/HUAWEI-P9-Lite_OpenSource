
#ifndef _TWAMP_SH_VAR_H_
#define _TWAMP_SH_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern ULONG g_ulTwampConfigMngTimerId;

extern VOID *g_pstTwampConfigMnglistHead;


extern TCPIP_HOOK_TWAMP_CTRL_FUNC g_pfnCtrlHook;

extern TCPIP_HOOK_TWAMP_SESS_FUNC g_pfnSessHook;



#ifdef __cplusplus
}
#endif

#endif

