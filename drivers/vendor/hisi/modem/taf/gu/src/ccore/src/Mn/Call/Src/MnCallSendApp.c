


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallSendApp.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "TafSdcCtx.h"
#include "NasUsimmApi.h"
#include "TafInternalInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_SEND_APP_C
/*****************************************************************************
   2 函数实现
*****************************************************************************/

/*lint -save -e958 */

VOS_VOID TAF_CALL_SendCallOrigCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_MGMT_STRU                   stCallMgmt;                             /* 呼叫信息 */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;    

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    if (VOS_ERR == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        /* 可能会存在还没分配callid就发现错误，需要给AT回复,
           此时需要构造stCallInfo,不能取实体中的stCallInfo */
        stCallMgmt.stCallInfo.clientId   = clientId;
        stCallMgmt.stCallInfo.opId       = opId;
        stCallMgmt.stCallInfo.enCause    = enCause;
    }
    else
    {
        /* 如果已经分配callid就取实体中的stCallInfo */        
        
        stCallMgmt.stCallInfo.clientId = clientId;
        stCallMgmt.stCallInfo.opId     = opId;
        stCallMgmt.stCallInfo.callId   = callId;
        stCallMgmt.stCallInfo.enCause  = enCause;

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();        
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        TAF_CALL_UpdateCallInfo(callId, &(stCallMgmt.stCallInfo));
    }

    /* 对所有注册了CS域呼叫事件回调函数的Client调用回调函数 */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_ORIG_CNF,
                       &(stCallMgmt.stCallInfo));
}


VOS_VOID TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_MGMT_STRU                   stCallMgmt;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    if (VOS_OK == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        stCallMgmt.stCallInfo.clientId = clientId;
        stCallMgmt.stCallInfo.opId     = opId;
        stCallMgmt.stCallInfo.callId   = callId;
        /* 1. 只有enCause值不是TAF_CS_CAUSE_SUCCESS，才更新CALL实体的原因值。*/
        if (enCause != TAF_CS_CAUSE_SUCCESS)
        {
            stCallMgmt.stCallInfo.enCause  = enCause;
        }

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                        MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        TAF_CALL_UpdateCallInfo(callId, &(stCallMgmt.stCallInfo));
    }
}


VOS_VOID TAF_CALL_SendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_MGMT_STRU                   stCallMgmt;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    /* 1. 可能会存在还没分配callid就发现错误，需要给AT回复,
        此时需要构造stCallInfo,不能取实体中的stCallInfo
       2. 如果已经分配callid就取实体中的stCallInfo
    */
    if (VOS_OK == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        stCallMgmt.stCallInfo.callId   = callId;

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                        MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);
    }

    stCallMgmt.stCallInfo.clientId   = clientId;
    stCallMgmt.stCallInfo.opId       = opId;
    stCallMgmt.stCallInfo.enCause    = enCause;

    if (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == TAF_CALL_GetCallSubState(callId))
    {
        stCallMgmt.stCallInfo.ucAtaReportOkAsyncFlag = TAF_CALL_GetAtaReportOkAsyncFlag();
    }

    /* 对所有注册了CS域呼叫事件回调函数的Client调用回调函数 */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SUPS_CMD_CNF,
                       &(stCallMgmt.stCallInfo));
}


VOS_VOID MN_CALL_SndStkCallDiscEvent(
    const VOS_VOID                     *pMsg,
    MNCC_PRIM_NAME_ENUM_U16             enMsgName,
    VOS_BOOL                            bNetMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bReleaseFlag;

    VOS_UINT32                          ulMsgLength;
    NAS_STK_CALL_DISC_EVENT_STRU       *pstCallDiscEvent = VOS_NULL_PTR;

    ulMsgLength    = sizeof(NAS_STK_CALL_DISC_EVENT_STRU);

    pstCallDiscEvent = (NAS_STK_CALL_DISC_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstCallDiscEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallDiscEvent: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstCallDiscEvent->stCallDiscEventInfo), 0, sizeof(NAS_STK_CALL_DISC_EVENT_INFO_STRU));

    pstCallDiscEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstCallDiscEvent->ulMsgId       = ID_NAS_STK_CALL_DISC_EVENT;


    ucTi            = 0;
    ucCallId        = 0;

    bReleaseFlag    = VOS_FALSE;

    /*
    判断是否已经发送过释放消息给(U)SIM: 是，则直接退出
    呼叫重建后释放呼叫是否允许重发DISCONNECT EVENT，待确认；
    */

    /*
        协议ETSI TS 102 223 V10.5.0 (2011-09) 7.5.3 Call disconnected event
        If the terminal initiates the disconnection, or in the case of radio
        link failure, this is considered a "near end" disconnection,
        whereas a "far end" disconnection is defined as when the network
        initiates the disconnection.
        in the case of "near end" disconnection, the terminal shall set the
        device identities to:
        - source: terminal;
        - destination: UICC.
        in the case of connecting at the far end (an MO call), the terminal
        shall set the device identities to:
        - source: network;
        - destination: UICC.
    */

    if ((VOS_TRUE != bNetMsg)
     || (MNCC_REJ_IND == enMsgName))
    {
        pstCallDiscEvent->stCallDiscEventInfo.ucLocalDiscFlg = VOS_TRUE;
    }
    else
    {
        pstCallDiscEvent->stCallDiscEventInfo.ucLocalDiscFlg = VOS_FALSE;
    }



    /* 填写TransactionId，和Cause到stEvent */

    if (VOS_TRUE == bNetMsg)
    {
        ulRet = MN_CALL_GetNetDiscEventInfo((MNCC_IND_PRIM_MSG_STRU *)pMsg,
                                             &(pstCallDiscEvent->stCallDiscEventInfo.stCause),
                                             &ucTi,
                                             &ucCallId);
        ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);
    }
    else
    {
        ulRet = MN_CALL_GetUeDiscEventInfo((MNCC_REQ_PRIM_MSG_STRU *)pMsg,
                                            &(pstCallDiscEvent->stCallDiscEventInfo.stCause),
                                            &ucTi,
                                            &ucCallId);
        ucTi  = (VOS_UINT8)(ucTi << 4);
    }
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_FREE_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
        return;
    }


    /* 一个呼叫仅记录一次呼叫释放事件的原因值，bReleaseFlag为VOS_TRUE标志已经有记录，退出 */
    MN_CALL_GetCallReleaseFlag(ucCallId, &bReleaseFlag);

    if (VOS_TRUE == bReleaseFlag)
    {
        PS_FREE_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
        return;
    }

    pstCallDiscEvent->stCallDiscEventInfo.ucTi = ucTi;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallDiscEvent: Send Msg Fail!");
        return;
    }

    /* 一个呼叫仅记录一次呼叫释放事件的原因值，此处更新标志为已记录 */
    MN_CALL_UpdateCallReleaseFlag(ucCallId, VOS_TRUE);

    return;

}


VOS_VOID MN_CALL_SndStkCallConnEvent(
    VOS_UINT8                           ucTi,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    NAS_STK_CALL_CONNECT_EVENT_STRU    *pstCallConnEvent = VOS_NULL_PTR;

    ulMsgLength         = sizeof(NAS_STK_CALL_CONNECT_EVENT_STRU);

    pstCallConnEvent    = (NAS_STK_CALL_CONNECT_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstCallConnEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallConnEvent: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstCallConnEvent->stCallConnectEventInfo),
                0,
                sizeof(NAS_STK_CALL_CONNECT_EVENT_INFO_STRU));



    /* 协议ETSI TS 102 223 V10.5.0 (2011-09) 7.5.2.2 Structure of ENVELOPE
        (EVENT DOWNLOAD - call connected)
        Device identities:
        in the case of connecting at the near end (an MT call), the terminal
        shall set the device identities to:
        - source: terminal;
        - destination: UICC.
        in the case of connecting at the far end (an MO call), the terminal
        shall set the device identities to:
        - source: network;
        - destination: UICC.
    */
    if (MN_CALL_DIR_MO == enCallDir)
    {
        ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);
    }
    else
    {
        ucTi  = (VOS_UINT8)(ucTi << 4);
    }

    pstCallConnEvent->stCallConnectEventInfo.enCallDir = enCallDir;
    pstCallConnEvent->stCallConnectEventInfo.ucTi      = ucTi;

    pstCallConnEvent->ulReceiverPid                    = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstCallConnEvent->ulMsgId                          = ID_NAS_STK_CALL_CONNECT_EVENT;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCallConnEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallConnEvent: Send Msg Fail!");
    }


    return;

}


VOS_VOID MN_CALL_SndStkMtCallEvent(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    MN_CALL_INFO_STRU                   stCallInfo;
    NAS_STK_MT_CALL_EVENT_STRU         *pstMtCallEvent = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    ulMsgLength    = sizeof(NAS_STK_MT_CALL_EVENT_STRU);

    pstMtCallEvent = (NAS_STK_MT_CALL_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMtCallEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkMtCallEvent: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstMtCallEvent->stMtCallEventInfo), 0, sizeof(NAS_STK_MT_CALL_EVENT_INFO_STRU));

    /* 获取当前呼叫实体的呼叫信息 */
    MN_CALL_GetCallInfoByCallId(callId, &stCallInfo);

    /* MT call event包括TransactionId，Addr和Subaddr */
    /* 填写TransactionId到stEvent */
    pstMtCallEvent->stMtCallEventInfo.ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);


    /* 填写主叫号码到stEvent */
    PS_MEM_CPY(&pstMtCallEvent->stMtCallEventInfo.stCallerNumber,
               &stCallInfo.stCallNumber,
               sizeof(MN_CALL_BCD_NUM_STRU));

    /* 填写主叫号码子地址到stEvent */
    PS_MEM_CPY(&pstMtCallEvent->stMtCallEventInfo.stCallerSubNumber,
               &stCallInfo.stSubCallNumber,
               sizeof(MN_CALL_SUBADDR_STRU));

    pstMtCallEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstMtCallEvent->ulMsgId       = ID_NAS_STK_MT_CALL_EVENT;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMtCallEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkMtCallEvent: Send Msg Fail!");
    }

    return;

}


VOS_VOID TAF_CALL_SendDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(stDtmfCnf));

    TAF_CALL_FillDtmfCnf(usClientId, opId, enCause, &stDtmfCnf);

    TAF_CALL_SendMsg(usClientId,
                     enEventType,
                     (VOS_VOID *)&stDtmfCnf,
                     sizeof(stDtmfCnf));

    return;
}


VOS_VOID TAF_CALL_SendCcwaiCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_UINT32                          ulResult
)
{
    TAF_CALL_EVT_CCWAI_CNF_STRU         stCcwaiCnf;

    PS_MEM_SET(&stCcwaiCnf, 0, sizeof(stCcwaiCnf));

    stCcwaiCnf.usClientId = usClientId;
    stCcwaiCnf.opId       = opId;
    stCcwaiCnf.ulResult   = ulResult;

    TAF_CALL_SendMsg(usClientId,
                     enEventType,
                     (VOS_VOID *)&stCcwaiCnf,
                     sizeof(stCcwaiCnf));

    return;
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_CALL_SendQueryEcallInfoCnf(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU                    *pstEcallInfo
)
{
    MN_SendClientEvent(usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_QRY_ECALL_INFO_CNF,
                       pstEcallInfo);
}


VOS_VOID TAF_CALL_SendTafRelCallCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_CALL_TAF_REL_CALL_CNF_STRU      *pstCallCnf = VOS_NULL_PTR;

    pstCallCnf = (TAF_CALL_TAF_REL_CALL_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, 
                    sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstCallCnf)
    {
        MN_ERR_LOG("TAF_CALL_SendTafRelCallCnf: ERROR: Memory allocation Fail.");
        return;
    }

    PS_MEM_SET(pstCallCnf, 0, sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU));
    
    pstCallCnf->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstCallCnf->ulSenderPid          = WUEPS_PID_TAF;
    pstCallCnf->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstCallCnf->ulReceiverPid        = WUEPS_PID_TAF;
    pstCallCnf->ulLength             = sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCallCnf->ulMsgId              = TAF_CALL_TAF_REL_CALL_CNF;

    pstCallCnf->usClientId           = usClientId;
    pstCallCnf->ucOpId               = ucOpId;
    pstCallCnf->enCause              = enCause;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCallCnf))
    {
        MN_WARN_LOG( "TAF_CALL_SendTafRelCallCnf:WARNING:SEND TAF_CALL_TAF_REL_CALL_CNF msg FAIL!" );
    }

    return;
}

#endif
/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
