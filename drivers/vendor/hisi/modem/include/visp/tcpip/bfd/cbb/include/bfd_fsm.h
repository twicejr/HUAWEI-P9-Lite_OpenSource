/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_fsm.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD FSM 
*  Date Created: 2006-12-13
*        Author: qinyun(62011)
*   Description: BFD FSM 函数声明以及宏定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-13  qinyun(62011)         Create the first version.
*
*******************************************************************************/
#ifndef _BFD_FSM_H_
#define _BFD_FSM_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG  BFD_PPI_HookRegister(BFD_PPI_HOOK_FUNC pfBfdPpiHook);
ULONG  BFD_HaCanSendPacket_HookRegister(BFD_HA_CAN_SEND_PACKET pfHaCanSendPacket);
ULONG  BFD_HaSendLivePacket_HookRegister(BFD_HA_SEND_LIVE_PACKET pfSendLivePacket);
ULONG  BFD_HaGetDbgSwitch_HookRegister(BFD_HA_GET_DBG_SWITCH pfHaGetBdgSwitch);
ULONG  BFD_HaCannotCfg_HookRegister(BFD_HA_CANNOT_CFG pfBfdCannotCfgHook);
ULONG  BFD_HaDbgOutput_HookRegister(BFD_HA_DBG_OUTPUT pfBfdHaDbgOutputHook);
/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
ULONG  BFD_Core_DetectDownByPrdt(ULONG ulSessionID,ULONG ulVrfIndex);
ULONG  BFD_Core_DetectDownWithDiagByPrdt(ULONG ulSessionID,ULONG ulDiag,ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
VOID   BFD_FSM_SetPpiInfo( const BFD_SESS_ENTRY_S *pstSessEntry , BFD_PPI_S*pstPpiInfo,ULONG ulPpiType);
ULONG  BFD_FSM_ProcPkt( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_ProcRcvAdminDownPkt( BFD_SESS_ENTRY_S *pstSessEntry ,BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_AdminDownProcRcvPkt( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_DownProcDown( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_DownProcInit( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_DownProcUp ( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_InitProcDown(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_InitProcInit(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_InitProcUp(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_UpProcDown(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_UpProcInit(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_UpProcUp(BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_ProcSessionUp ( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_SetDetectModeAndInterval ( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);
ULONG  BFD_FSM_ProcSessDiagDown(BFD_SESS_ENTRY_S *pstSessEntry, ULONG ulDiag);

/* 产品需适配该通知函数 */
extern VOID BFD_NotifyAppSessionState(ULONG ulSessionID, ULONG ulState, ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, 
                                      ULONG ulAppGroup,ULONG ulVrfIndex);
 
extern VOID BFD_NotifyAppSessionStateChange(ULONG ulVrfIndex,ULONG ulSessionID, 
                                   ULONG ulOldState, ULONG ulNewState,ULONG ulDstIP, 
                                   ULONG ulSrcIP,ULONG ulInIfIndex,ULONG ulAppGroup);

extern VOID BFD6_NotifyAppSessionState(BFD6_NOTIFY_S * pstBfd6Notify);
VOID BFD_PPI_Download(ULONG ulPpiType,const BFD_SESS_ENTRY_S *pstSessEntry);

SHORT BFD_MallocPfPos(USHORT usVrfIndex, USHORT usSessionId);
extern USHORT BFD_CallbackPfPos(USHORT usVrfIndex, USHORT usSessionId);
extern VOID BFD_PF_RetranTimerOut(ULONG ulTimerIndex, ULONG ulTimerId);
extern ULONG BFD_SetPfRetranPara(USHORT usVrfIndex, USHORT usSessionId, UCHAR ucState, UCHAR ucSendCount);
extern VOID BFD_PF_RetranPreProcess(ULONG ulVrfIndex, ULONG ulSessId);

/*extern LONG rand(VOID) ;*/

/* 得到2000ms到3000ms之间的一个随机数 */
#define BFD_GetRand(ulRand) \
{ \
    ULONG ulTimeInMSHigh = 0 ; \
    ULONG ulTimeInMSLow  = 0 ; \
    ULONG ulTemp  = 0 ; \
    ( VOID )VOS_Tm_Now(&ulTimeInMSHigh , &ulTimeInMSLow) ; \
    ulTemp = TCPIP_Rand_Safe(ulTimeInMSHigh + ulTimeInMSLow) ; \
    (ulRand) = (ulTemp % 1000) + 2000 ; \
}

#define BFD_FSM_InitTxRx( pstSessEntry ) \
{ \
    VOS_DBGASSERT(NULL != (pstSessEntry)) ; \
    if (NULL != (pstSessEntry)) \
    { \
        ULONG ulTxRxInt = 0 ; \
        BFD_GetRand(ulTxRxInt) ; \
        (pstSessEntry)->stSessRunEntry.ulActTxInterval = ulTxRxInt ; \
        (pstSessEntry)->stSessRunEntry.ulActRxInterval = ulTxRxInt ; \
    } \
}

/* Modified by likaikun213099,  , 2014/9/26   问题单号:DTS2014092501767 */
#define BFD_NOSEND_FOR_RXZERO(pstSessEntry)  ((g_ulBfdComplianceSwitch & BFD_PROCOMPLIANCE_FOR_RXZERO)\
    && ((BFD_PROTO_STD == (pstSessEntry)->ulBfdProtocol) && (0 == (pstSessEntry)->stSessRunEntry.ulRemoteMinRxInterval)))

/* End of Modified by likaikun213099, 2014/9/26   问题单号:DTS2014092501767 */

#ifdef __cplusplus
}
#endif

#endif/*_BFD_FSM_H_*/

