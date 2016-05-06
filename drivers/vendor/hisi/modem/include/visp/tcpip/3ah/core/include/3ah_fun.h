/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_fun.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH所有的函数声明(3ah_api.c中的在3ah_api.h中声明)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_FUN_H_
#define _3AH_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif


/* 3ah_cfg.c */
ULONG OAM_3AH_Enable(ULONG ulIfIndex, ULONG ul3AHEnable);
ULONG OAM_3AH_CheckIfValid(ULONG ulIfIndex);
OAM3AH_PORTINFO_S* OAM_3AH_GetEntry(ULONG ulIfIndex);
OAM3AH_PORTINFO_S* OAM_3AH_CreateEntry(ULONG ulIfIndex);
ULONG OAM_3AH_GlobalDisable(VOID);
ULONG OAM_3AH_SetMode(ULONG ulIfIndex, ULONG ul3AHMode);
ULONG OAM_3AH_SetPduSize (ULONG ulIfIndex, ULONG ulPduSize);
ULONG OAM_3AH_GetCfgInfo(ULONG ulIfIndex, OAM3AH_CFG_INFO_S* pst3AHCfgInfo);
ULONG OAM_3AH_GetCfgInfoEx(ULONG ulIfIndex, OAM3AH_CFG_INFO_EX_S* pst3AHCfgInfo);
ULONG OAM_3AH_GetFSMInfo(ULONG ulIfIndex, ULONG* pulState);
ULONG OAM_3AH_GetPacketStat(ULONG ulIfIndex, OAM3AH_PDUSTAT_S * pstOampduStat);
ULONG OAM_3AH_ClearPacketStat(ULONG ulIfIndex);
ULONG OAM_3AH_SetDbgSwitch(ULONG ulIfIndex, ULONG ulDebugSwitche);
ULONG OAM_3AH_GetDbgSwitch(ULONG ulIfIndex, ULONG *pulDugInfo);
ULONG OAM_3AH_DetectIntervalToCode(ULONG ulDetectInterval, ULONG *pulDetectCode);
ULONG OAM_3AH_CodeToDetectInterval(ULONG ulDetectCode, ULONG *pulDetectInterval);
ULONG OAM_3AH_SetDetect (ULONG ulIfIndex, ULONG ulDetectInteval);
ULONG OAM_3AH_SetLoopback (ULONG ulIfIndex, ULONG ulLoopbackCmd);
ULONG OAM_3AH_SetLbTestMode (ULONG ulIfIndex, ULONG ulLbTestMode);
ULONG OAM_3AH_NotifyCriticalLinkEvent(ULONG ulIfIndex, ULONG ulCriticalEventType, ULONG ulState);
ULONG OAM_3AH_OccurErroredLinkEvent(ULONG ulIfIndex, ULONG ulErroredType, OAM3AH_LINKEVT_PARAM_S *pstErrPrdParam);
ULONG OAM_3AH_EventEnable (ULONG ulIfIndex, ULONG ulEventEnable);
/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
ULONG OAM_3AH_SetErroredWinThres(ULONG ulIfIndex,ULONG ulLinkEventType, DULONG_S stdulErrWindow, DULONG_S stdulErrThres);
LONG  OAM_3AH_fnEntryIndexCmp(VOID * val, DLL_NODE_S * pNode);
VOID  *OAM_3AH_GetWtLstNext(VOID *pCur,VOID **ppNext);
ULONG OAM_3AH_OpenWtLstObject(UINTPTR *pulWaitListHandle);
ULONG OAM_3AH_CloseWtLstObject (UINTPTR ulWaitListHandle);
ULONG OAM_3AH_GetWtLstEntry(UINTPTR ulWaitListHandle, OAM3AH_PORTINFO_S *pstOam3ahPortInfo);
ULONG OAM_3AH_DealPktTimeTest_Hook_Register(DEALPKT_TIMETEST__HOOK_FUNC pfTimeTest);
ULONG OAM_3AH_SetBoardState(ULONG ulIfIndex, ULONG ulState);
ULONG OAM_3AH_IoBoardSyncMainBoard(OAM3AH_WARN_PARAM_S* pst3ahWarn);
ULONG OAM_3AH_Set_NegTimeoutWaring(ULONG ulTime);
ULONG OAM_3AH_Get_NegTimeoutWaring(ULONG *pulTime);
ULONG OAM_3AH_GetFaultWarnState(ULONG ulIfIndex, OAM3AH_WARN_STATE_S* pst3ahWarnState);


/* 3ah_debug.c */
ULONG OAM_3AH_DbgOamPdu(OAM3AH_PORTINFO_S* pstPortInfo, ULONG ulSndRcv, UCHAR *pucOamData, ULONG ulDataLen);
CHAR  *OAM_3AH_GetDbgStrByFsmState(ULONG ulState);
CHAR  *OAM_3AH_GetDbgStrByEvent(ULONG ulEvtType);
ULONG OAM_3AH_DbgFsm(OAM3AH_PORTINFO_S* pstPortInfo, OAM3AH_FSMTRAN_S *pstFsmState);
ULONG OAM_3AH_DbgLbData(OAM3AH_PORTINFO_S* pstPortInfo, ULONG ulSndRcv, MBUF_S* pstMbuf);
ULONG OAM_3AH_DbgErr(OAM3AH_PORTINFO_S* pstPortInfo, CHAR* szErrInfo);

/* 3ah_fsm.c */
ULONG OAM_3AH_MainStateCtrl(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulEvent);
ULONG OAM_3AH_StateCtrl_Discovery (OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulEvent);
ULONG OAM_3AH_StateCtrl_Loopback (OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulEvent);
ULONG OAM_3AH_GetStateType(ULONG ulState);
VOID OAM_3AH_Fsm_ChangeState(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulNewState, ULONG ulEvent);
VOID OAM_3AH_Fsm_ChangeState_Common(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulNewState, ULONG ulEvent,
                                                     ULONG *pulHasDownToNp);
VOID  OAM_3AH_ClearProc(OAM3AH_PORTINFO_S *pstPortInfo,ULONG ulIsDisabled);
VOID  OAM_3AH_ClearLbCfg(OAM3AH_PORTINFO_S *pstPortInfo);
VOID  OAM_3AH_PduTimerDone(ULONG ulIfIndex);
VOID  OAM_3AH_LocalLostLinkTimerDone(ULONG ulIfIndex);
VOID OAM_3AH_Notify_Optim(ULONG ulIfIndex);
VOID OAM_3AH_WarnTraceForDiscover(OAM3AH_WARN_PARAM_S *pst3ahWarn);

/* 3ah_func.c */
ULONG OAM_3AH_PpiUpdate(ULONG ulCmd, OAM3AH_PORTINFO_S *pstPortInfo);
ULONG OAM_3AH_IsEnabled(ULONG ulIfIndex);
ULONG OAM_3AH_IsCanSndPkt(ULONG ulIfIndex);
VOID  OAM_3AH_IfDelete_Notify(ULONG ulIfIndex);
VOID  OAM_3AH_IfPhyStatus_Notify(ULONG ulIfIndex, ULONG ulCmd, CHAR * pData);
ULONG OAM_3AH_SH_IfPhyStatus_Notify(VOID* pulIfIndex, ULONG ulCmd, VOID* pData, VOID** ppInfo);
ULONG OAM_3AH_LinkEvent_Notify(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulLinkEventType, ULONG ulLclRmt);
ULONG OAM_3AH_LclFault_Notify(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulFaultType, ULONG ulFaultState);
ULONG OAM_3AH_RmtFault_Notify(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulFaultType, ULONG ulFaultState);
ULONG OAM_3AH_GetPhyErrNum(ULONG ulIfIndex, DULONG_S *pstDulErrNum);
VOID  OAM_3AH_ErrFrm_TimerDone(ULONG ulIfIndex);
VOID  OAM_3AH_ErrFrmSecSum_TimerDone(ULONG ulIfIndex);
VOID  OAM_3AH_Timer_Create(OAM3AH_TIMER_FUNC pfTimerFunc, ULONG ulInterval, ULONG *pulTimerId,VOID *pArg);
VOID  OAM_3AH_StartLinkEvent(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulLinkEventType);
ULONG OAM_3AH_NpLostLink(ULONG ulIfIndex);
VOID OAM_3AH_DealLinkCtrlMsg(UINTPTR aulMsg[4]);
ULONG OAM_3AH_StartLbTest (ULONG ulIfIndex, VOID* pBuffer, ULONG ulBufLen);
ULONG OAM_3AH_Timer_IsStoped(ULONG ulTimerID);
VOID OAM_3AH_LbTimerDone(ULONG ulIndex);
ULONG OAM_3AH_GetMac(ULONG ulIfIndex, UCHAR *pucMac);
ULONG OAM_3AH_GetSessionStatus(ULONG ulIfIndex, ULONG* pulStatus);
ULONG OAM_3AH_NegTimerCntProc(ULONG ulFlag);
VOID  OAM_3AH_NegTimeout_Callback(VOID *pArg);
VOID OAM_3AH_SendEFMStatusToIF(ULONG ulIfIndex);

/* 3ah_ha.c */
ULONG OAM_3AH_HA_OutputMsg(UCHAR *pucData, ULONG ulMsgLen);
ULONG OAM_3AH_CntPortInfoBakLen(ULONG ulBakType, ULONG *pulBakLen);
ULONG OAM_3AH_HA_PackPortInfo(UCHAR* pucData, ULONG ulOffset, ULONG ulBufTotalLen,
                              OAM3AH_PORTINFO_S *pstPortInfo, ULONG *pulMsgAddLen);
ULONG OAM_3AH_HA_RealTimePack(ULONG ulBakType, VOID* pData);
ULONG OAM_3AH_HA_BatchBackup(VOID);
ULONG OAM_3AH_HA_GlobalVar(ULONG ulBakType);

ULONG OAM_3AH_HA_Restore(UCHAR * pucData, ULONG ulDataLen);
ULONG OAM_3AH_HA_Input(UCHAR *pucData, ULONG ulDataLen);
ULONG OAM_3AH_HA_Smooth(VOID);
ULONG OAM_3AH_HA_Clean(VOID);
ULONG OAM_3AH_HA_SetDbg(ULONG ulDbg);
ULONG OAM_3AH_HA_GetDbg(ULONG *pulDbg);
ULONG OAM_3AH_HA_SetVerboseDbg(ULONG ulDbg);
ULONG OAM_3AH_HA_GetVerboseDbg(ULONG *pulDbg);
ULONG OAM_3AH_GetHaStat(OAM3AH_HASTAT_S *pst3AHHaStat);
ULONG OAM_3AH_ClearHaStat(VOID);
VOID  OAM_3AH_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd) ;

/* 3ah_init.c */
ULONG OAM_3AH_Init_Com(const COM_ID_INFO_S* pstComInfo, ULONG ulComLen);
ULONG OAM_3AH_Active_Com(VOID);
ULONG OAM_3AH_SetModuleInfo(OAM3AH_MOD_INFO_S *pstMInfo);
ULONG OAM_3AH_RegShellApi(OAM3AH_SHELL_CALLBACK_SET_S *pstShellApi);

/* 3ah_pkt.c */
ULONG OAM_3AH_RcvOampdu(MBUF_S *pstMBuf, OAM3AH_PORTINFO_S *pstPortInfo);
VOID  OAM_3AH_ParseOampdu(UCHAR *pucOamData, ULONG ulOamDataLen, OAM3AH_PORTINFO_S *pstPortInfo);
ULONG OAM_3AH_DealInfoOrgSpecTlv(OAM3AH_PORTINFO_S *pstPortInfo, UCHAR *pucTlv);
ULONG OAM_3AH_RcvPkt(IFNET_S* pIf, MBUF_S *pstMBuf);
ULONG OAM_3AH_SndInfo(OAM3AH_PORTINFO_S *pstPortInfo);
ULONG OAM_3AH_SndOampdu(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulCode, VOID *pOamData, ULONG ulOamDateLen);
VOID  OAM_3AH_SetPduFlags(OAM3AH_PORTINFO_S *pstPortInfo);
ULONG OAM_3AH_FillOamPdu(OAM3AH_PORTINFO_S *pstPortInfo, UCHAR *pucBuffer, ULONG ulCode, VOID *pOamData);
VOID OAM_3AH_FillOamPdu_Info(UCHAR *pucbuf, VOID **ppInfoData, ULONG *pulFillLen);
VOID OAM_3AH_FillOamPdu_LinkEvent(UCHAR *pucbuf, VOID **ppLinkEventData, ULONG *pulFillLen);
VOID  OAM_3AH_Incr_Statistic(OAM3AH_PORTINFO_S *pstPortInfo, ULONG ulCode, ULONG ulSndRcv);

/* 3ah_sh_init.c */
ULONG OAM_3AH_SH_Init(VOID);
VOID  OAM_3AH_DeInit(VOID);
ULONG OAM_3AH_RegApp(VOID);
VOID  OAM_3AH_DebugOutString(CHAR* szString);

/* 3ah_var.c */
/* there is only 3ah module's global variables define,no function */

/* i3ah.c */
ULONG OAM_3AH_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

/* i3ah_fac.c */
ULONG ImplOAM3AHFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
ULONG ImplOAM3AHFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj);

/* 3ah_sh_disp.c */
VOID  OAM_3AH_ShowAllInfo(VOID);

/*Added by wangtong207740, DTS2012102202389 ,设置是否处理带VLAN的OAMPUD, 2012/10/22 */
ULONG OAM_3AH_SetDealPacketWithVlanSwitch(ULONG ulSwitch);
ULONG OAM_3AH_GetDealPacketWithVlanSwitch(ULONG *pulSwitch);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_FUN_H_   */

