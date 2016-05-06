
#ifndef _ADDR_SH_VAR_H_
#define _ADDR_SH_VAR_H_


#ifdef __cplusplus
extern "C" {
#endif

extern ULONG g_ulIP6AddrMemShortageFlag;

extern ULONG g_ulAddrCliState;


extern struct  IIF_IP6_ADDR_GENERIC_INTVtbl        *g_pstADDRInitTable;
extern struct  IIF_IP6_ADDR_GENERIC_CFGVtbl        *g_pstADDRCfgTable;
extern struct  IIF_IP6_ADDR_GENERIC_FUNVtbl        *g_pstADDRFunTable;
extern struct  IIF_IP6_ADDR_GENERIC_IR_FUNVtbl     *g_pstADDRIRFunTable;
extern struct  IIF_IP6_ADDR_GENERIC_INT_INITVtbl   *g_pstADDRINTInitTable;
extern struct  IIF_IP6_ADDR_GENERIC_INT_FUNVtbl    *g_pstADDRINTFunTable;
#if (VRP_NO == IP6_NDHOST)
extern struct  IIF_IP6_ADDR_GENERIC_INT_HSBVtbl    *g_pstADDRINTHSBTable;
#endif
extern struct  IIF_IP6_ADDR_GENERIC_INT_SSAVtbl    *g_pstADDRINTSSATable;

/* Begin  : Defect ID: D01006, Modifier:Rajesh, Date:2004/9/13
   Reason : Initial, Max Mtu change for Pos, GE interfaces*/
extern SPECS_RES_VALUE_S  g_stShMtuPosVal;
extern SPECS_RES_VALUE_S  g_stShMtuGEVal;
extern SPECS_RES_VALUE_S  g_stShAddrNum;

extern ULONG g_ulAddrExecIndex;

extern IP6_ADDR_MOD_INFO_S g_stADDRShellModInfo;

extern CHAR *Msg_Router_En[];
extern CHAR *Inf_Addr_Ch[];
extern CHAR *Inf_Addr_En[];
extern ULONG ulSOCKTmrQueID;

extern VOID IP6_Addr_SH_IfnetHotNotifyCB (ULONG ulEvent, ULONG ulSlot,
                                        VOID *pstIfnet, ULONG ulIfIndex);
extern ULONG IP6_Addr_SH_NotifyCliChange(ULONG ulCliState);
extern VOID IP6_Addr_SH_ProcTimerEvents (IP6_Addr_TIMER_S *pstTimerMsg);
extern ULONG IP6_Addr_SH_BuildRun(CHAR *pszSectionName, CHAR **pszBuildRunInfo);

/* extern VOID IP6_Log_Text(enum LOG_LEVEL enLevel, CHAR *pMessage, ...);*/
ULONG IP6_SH_CheckDebug(ULONG ulLevel);

extern ULONG IP6_Addr_RegPPNotifyCallBack (ULONG ulRoutingFlag);

extern ULONG IP6_Addr_SH_TimerCreate(ULONG ulTaskID, ULONG ulMsgQueID,
                                ULONG ulMillSec,
                                VOID (*pfTimerFunc)(VOID *), VOID  *pArg,
                                ULONG *pulRetTimerID, ULONG ulFlag);
extern ULONG IP6_Addr_SH_TimerCreate_SockRun(ULONG ulMillSec,
                                VOID (*pfTimerFunc)(VOID *), VOID  *pArg,
                                ULONG *pulRetTimerID, ULONG ulFlag);
extern ULONG IP6_Addr_SH_Tm_Now(ULONG *pulRetTimeInMillSecHigh,
                                     ULONG *pulRetTimeInMillSecLow);
extern VOID IP6_Addr_SH_ReplaceBuildRunInfo (CHAR *, ULONG, CHAR*);

/*extern ULONG VOS_Que_Write(ULONG ulQueID, ULONG ulMsg [IP6_QUEUE_WRITE_MSG_LEN],
                        ULONG ulFlags, ULONG ulTimeOutInMillSec);*/

#if (VRP_YES == VRP_CENTERALIZATION)
#if (TCPIP_IN_VRP == VRP_NO)
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */  
/* extern ULONG SFIB6_Item_IsAvailable(VOID); */
extern ULONG SFIB6_Item_IsAvailable(USHORT usZoneId);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */  
extern ULONG SFIB6_Update_InterfaceAddress(IP6_ADDR_NOTIFY_MSG_S*);
extern ULONG TCPIP_IPV6AddrChangeProc(IP6_ADDR_NOTIFY_MSG_S *pMsg);
#endif
#endif

extern ULONG ulSOCKTmrQueID;
extern ULONG ulVRPTID_SOCK;


extern ULONG g_ulADDR_Sh_IsIAS;


#if (VRP_YES == IP6_NDHOST)

/* Added For ND Host */
extern ULONG IP6_ND_SH_StopTimer(ULONG ulTimerID);

extern ULONG IP6_ND_SH_CreateNonPeriodTimer(ULONG ulTimeValue,
                    ULONG (*pfIP6_TimeOutHandler)(UINTPTR aulPara[]),
                    UINTPTR ulPara[TWL_MAX_USE_PARA_LEN], ULONG *pulTimerid);

extern ULONG IP6_ND_SH_GetTimerMsg(ULONG ulTimerID,
                                        UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);

extern ULONG IP6_ND_SH_RefreshTimer(ULONG ulTimerID,ULONG ulNewTimeValue);

extern ULONG IP6_ND_SH_GetRestTimeValue(ULONG ulTimerID,ULONG *pulRestTimeValue);

#endif

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
extern IPV6_PPI_HOOK_S * g_pstNPCallBack;
#endif

extern USHORT  g_usMaxAddrVrf;


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _ADDR_SH_VAR_H_ */

