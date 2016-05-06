
#ifndef _TWAMP_VAR_H_
#define _TWAMP_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************Common Start******************************************************************/

/*Initialization flag*/
extern ULONG g_ulTwampInitFlag;

/*********************************************Common End******************************************************************/

/*********************************************Reflector Start******************************************************************/

/*TWAMP Reflector control queue ID*/
extern ULONG g_ulTwampRefCtrlQId;


/*TWAMP Reflector Task Id*/
extern ULONG g_ulTwampRefTaskId;

extern ULONG g_ulTwampShelltimerQId;

extern ULONG g_ulTwampReftimerQId;



extern ULONG g_ulReflectorCount;

extern TCPIP_TWAMP_REFL_GCONFIG_S *g_pstTwampRefGConfig;

extern TWAMP_REFLECTOR_S * g_pstTWAMPReflectorTable[TWAMP_MAX_REFLECTORS];

extern fd_set g_stTWAMPReflectorFDSet;

extern LONG g_lTwampMAXReflectorFD;



extern fd_set g_stTWAMPStopSessionFDSet ;

extern LONG g_lTwampMAXStopSessionFD ;

extern ULONG g_ulTWAMPStopSessionCount;



extern TWAMP_REFLECTOR_CTRL_SESSION_S* g_pstTWAMPCtrlSessionTable[TWAMP_CTRL_SESSION_TABLE_SIZE];

extern ULONG g_ulSIDCount;

extern ULONG g_ulTWAMPSysTestSessionCount;

extern ULONG g_ulTWAMPSysClientCount;



/*********************************************Reflector End******************************************************************/

/*********************************************Client Start******************************************************************/
/*TWAMP Client control queue ID*/
extern ULONG g_ulTwampCliCtrlQId;

/*TWAMP Client Task Id*/
extern ULONG g_ulTwampCliTaskId;

extern ULONG g_ulClientCount;
extern ULONG g_ulShellClientCount;
extern ULONG g_ulShellSenderCount;

extern ULONG g_ulSenderCount;

extern ULONG g_aTcpSockFds[TWAMP_MAX_CTRL_SESSIONS];

extern TCPIP_TWAMP_CLIENT_SOCK_TBL_S g_stClientSockTbl;

extern TCPIP_TWAMP_CLIENT_SESSION_TBL_S g_stClientSessionTbl;

extern fd_set g_stTWAMPClientFDSet;

extern fd_set g_stTWAMPClientReadFDSet;

extern LONG g_lTwampMAXClientFD;

extern TCPIP_HOOK_TWAMP_REFL_FUNC g_pfnReflHook;

extern TWAMP_CORE_HOOK_CLIENT_CTRL_TIMEOUTFUNC g_pfnCtrlCoreTimeoutHook;

extern TWAMP_CORE_HOOK_CLIENT_CTRL_FUNC g_pfnCtrlCoreHook;

extern TWAMP_CORE_HOOK_SENDER_SESS_FUNC g_pfnSessCoreHook;

extern ULONG g_ulTwampReflTimerId;

extern TWAMP_TIMER_INFO_S  *g_pstTwampTimerInfo;

extern TCPIP_TWAMP_PPI_HOOK_S g_stTwampPPIHook;

extern TCPIP_TWAMP_SYS_HOOK_FUN_S g_stTwampSysHook;


/*********************************************Client End******************************************************************/


extern ULONG g_ulTwampdebugSwitch;


#ifdef __cplusplus
}
#endif

#endif

