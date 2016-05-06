
#ifndef _IP6_PMTUINIT_H
#define _IP6_PMTUINIT_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_HA_RegisterCallBack
                        (PMTU_SHELL_HA_BACUP_SET_S *pstCallBackSet);
ULONG IP6_PMTU_Init_Com_NEW (IPB_IR_PMTU_COM_ID_INFO_S *pstComInfo,
                                                                ULONG ulComLen);
ULONG IP6_PMTU_SetModuleInfo (PMTU_MOD_INFO_S *pMInfo);
ULONG IP6_PMTU_Activate_Com (VOID);
ULONG IP6_PMTU_RegDebugCallBack (PMTU_SHELL_DEBUG_CALLBACK_SET_S
                                                            *pstCallBackSet);
ULONG IP6_PMTU_RegTimeoutCallBack (PMTU_SHELL_TIMEOUT_CALLBACUP_SET_S
                                                            *pstCallBackSet);
ULONG IP6_PMTU_Notification_Register (SOCKADDR_IN6_S *pstsAD, LONG lSockid,
                                      ULONG ulTaskId, ULONG ulIfindex);
ULONG IP6_PMTU_Notification_Unregister (LONG lSockid, ULONG ulTaskId);
ULONG IP6_PMTU_RegSocketCallBack(PMTU_CALLBACKUP_SET_S *pstCallBackSet);
ULONG IP6_PMTU_RegShellCallbackFunc (IP6_PMTU_SH_CALLBACK_FUNC_S
                                                            *pstCallBackSet);

ULONG IP6_PMTU_RegNPCallback(IPV6_PPI_HOOK_S *pstCallbackFunc);


extern IComponentFactory m_PMTUFactory;

extern IIF_IP6_PMTU_INIT         g_stPMTU_INIT;
extern IIF_IP6_PMTU_INT_INIT     g_stPMTU_INT_INIT;
extern IIF_IP6_PMTU_CFG          g_stPMTU_CFG;
extern IIF_IP6_PMTU_INT_SSA      g_stPMTU_INT_SSA;
extern IIF_IP6_PMTU_FUN          g_stPMTU_FUN;
extern IIF_IP6_PMTU_IR_FUN       g_stPMTU_IR_FUN;
extern IIF_IP6_PMTU_INT_HSB      g_stPMTU_INT_HSB;

#ifdef  __cplusplus
}
#endif

#endif

