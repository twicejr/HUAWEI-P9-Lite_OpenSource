
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "Taf_Aps.h"
#include "TafApsCtx.h"
#include "TafApsSndInternalMsg.h"
#include "MnApsComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_INTERNALMSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/


VOS_VOID TAF_APS_SndInterPdpDeactivateReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU   *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU));
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterDeactivateReq: Get internal message failed!");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->enCause                     = enCause;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterDeactivateReq: Send internal message failed.");
        return;
    }

    return;
}


VOS_VOID TAF_APS_SndLocalPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU   *pstLocalMsg;

    /* 构造消息 */
    pstLocalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU));
    if (VOS_NULL_PTR == pstLocalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndLocalPdpDeactivateInd: Get Local message failed!");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstLocalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstLocalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLocalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstLocalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLocalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstLocalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND;
    pstLocalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstLocalMsg->ucPdpId                     = ucPdpId;
    pstLocalMsg->enCause                     = enCause;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstLocalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndLocalPdpDeactivateInd: Send internal message failed.");
        return;
    }

    return;
}


VOS_VOID TAF_APS_SndLocalAllSecPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT8                           i;

    if (APS_PDP_ACT_PRI == TAF_APS_GetPdpEntActType(ucPdpId))
    {
        for (i = 0; i < TAF_APS_MAX_PDPID; i++)
        {
            if ((TAF_APS_GetPdpEntNsapi(ucPdpId) == TAF_APS_GetPdpEntLinkedNsapi(i))
             && (APS_PDP_ACT_SEC == TAF_APS_GetPdpEntActType(i))
             && (VOS_TRUE == TAF_APS_GetPdpEntUsedFlg(i)))
            {
                TAF_APS_SndLocalPdpDeactivateInd(i, enCause);
            }
        }
    }
}



VOS_VOID TAF_APS_SndInterAttachBearerActivateInd(VOS_VOID)
{
    TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU    *pstInternalMsg = VOS_NULL_PTR;

    /* 构造内部消息 */
    pstInternalMsg  = (TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU *)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Get internal message failed!");
        return;
    }

    /* 填写消息头 */
    TAF_APS_CFG_INTER_MSG_HDR(pstInternalMsg, (sizeof(TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    pstInternalMsg->enMsgId = ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterAttachBearerActivateInd: Send message failed.");
    }

    return;
}


VOS_VOID TAF_APS_SndInterFsmEntryMsg(TAF_APS_ENTRY_MSG_STRU *pstEntryMsg)
{
    VOS_VOID                           *pstInternalMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    pstMsgHeader = (MSG_HEADER_STRU *)(&pstEntryMsg->aucEntryMsgBuffer[0]);
    ulMsgLength  = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 构造内部消息 */
    pstInternalMsg  = (VOS_VOID *)TAF_APS_GetIntMsgSendBuf(ulMsgLength);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Get internal message failed!");
        return;
    }

    /* 拷贝消息内容 */
    PS_MEM_CPY(pstInternalMsg, (VOS_VOID *)pstMsgHeader, ulMsgLength);

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Send internal message failed.");
    }

    return;
}



VOS_UINT32 TAF_APS_SndEnterDormantInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstDormantInd = VOS_NULL_PTR;

    /* 构造消息 */
    pstDormantInd  = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU));

    if (VOS_NULL_PTR == pstDormantInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEnterDormantInd: ALLOC MEMERY FAIL!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstDormantInd,
               0x00,
               sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU));

    /* 填写消息头 */
    pstDormantInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstDormantInd->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstDormantInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDormantInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstDormantInd->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND;
    pstDormantInd->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDormantInd->ucPdpId                     = ucPdpId;

    /* 发送内部消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstDormantInd);

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterEndCdmaCallReq(
    TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8     enEndScene,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8    enEndReason,
    VOS_UINT8                                   ucPdpId,
    VOS_UINT32                                  ulRemainTmrLen
)
{
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU   *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEndCdmaCallReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->ulRemainTmrLen              = ulRemainTmrLen;
    pstInternalMsg->enEndScene                  = enEndScene;
    pstInternalMsg->enEndReason                 = enEndReason;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEndCdmaCallReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterEpdszidReOrigReq(VOS_VOID)
{
    TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU    *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterHtExpiredInd(VOS_VOID)
{
    TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU  *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_HT_EXPIRED_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 TAF_APS_SndHaiChangeInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_HAI_CHANGE_IND_STRU         *pstHaiChangeInd;

    /* 构造消息 */
    pstHaiChangeInd  = (TAF_PS_HAI_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(TAF_PS_HAI_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstHaiChangeInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHaiChangeInd: ALLOC MEMERY FAIL!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstHaiChangeInd,
               0x00,
               sizeof(TAF_PS_HAI_CHANGE_IND_STRU));

    /* 填写消息头 */
    pstHaiChangeInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstHaiChangeInd->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstHaiChangeInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstHaiChangeInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstHaiChangeInd->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_HAI_CHANGE_IND;
    pstHaiChangeInd->stMsgHeader.ulLength        = sizeof(TAF_PS_HAI_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstHaiChangeInd->ucPdpId                     = ucPdpId;

    /* 发送内部消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstHaiChangeInd);

    return VOS_OK;
}



VOS_UINT32 TAF_APS_SndInter1XToHrpdHandOffReq(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU         *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInter1XToHrpdHandOffReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInter1XToHrpdHandOffReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterHrpdTo1XHandOffReq(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU         *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterHrpdTo1XHandOffReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterHrpdTo1XHandOffReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterServiceStatusChangeInd(
    VOS_UINT8                           ucPdpId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType,
    VOS_UINT32                          ulPsSimRegStatus,
    VOS_UINT8                           ucIsNewSession,
    TAF_APS_INTER_SERVICE_TYPE_ENUM_UINT8         ucServiceType
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU     *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterServiceStatusChangeInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->ucIsNewSession              = ucIsNewSession;
    pstInternalMsg->enRatType                   = enRatType;
    pstInternalMsg->enLastRatType               = enLastRatType;
    pstInternalMsg->ulPsSimRegStatus            = ulPsSimRegStatus;
    pstInternalMsg->ucServiceType               = ucServiceType;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterServiceStatusChangeInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SndInterPsServiceModeModifyInd(
    TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8 enPsOptionType
)
{
    TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU     *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterPsServiceModeModifyInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstInternalMsg->enPsOptionType              = enPsOptionType;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterPsServiceModeModifyInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 TAF_APS_SndInterEnd1xServiceInDormantInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU   *pstInternalMsg;

    /* 构造消息 */
    pstInternalMsg  = (TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU *)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEnd1xServiceInDormantInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* 发送内部消息 */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEnd1xServiceInDormantInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

