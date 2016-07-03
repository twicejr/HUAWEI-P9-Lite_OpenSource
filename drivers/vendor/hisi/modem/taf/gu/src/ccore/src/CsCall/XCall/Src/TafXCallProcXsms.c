

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallProcXsms.h"
#include "TafXCallProcEccSrv.h"
#include "TafXCallDecKmcMsg.h"
#include "TafXCallMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_XSMS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID TAF_XCALL_RcvXsmsKmcMsgRcvInd(VOS_VOID *pMsg)
{
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                        *pstXsmsRcvInd = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_STRU                                  stKmcMsg;
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32          enStateMachine;
    VOS_UINT32                                              ulStateMachineEvent;

    if (VOS_FALSE == TAF_XCALL_GetVoiceEncryptCapCfgPara()->ucEccSrvCap)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_RcvXsmsKmcMsgRcvInd: ECC SERVICE CAP is not supported!");
        return;
    }

    pstXsmsRcvInd       = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg;

    PS_MEM_SET(&stKmcMsg, 0, sizeof(TAF_XCALL_KMC_MSG_STRU));

    /* 对KMC消息进行解码 */
    TAF_XCALL_DecodeKmcMsg(&(pstXsmsRcvInd->aucData[0]),
                           pstXsmsRcvInd->usDataLen,
                           &stKmcMsg);

    /* log解码后的KMC消息 */
    TAF_XCALL_MNTN_LogKmcDecMsg(&stKmcMsg);

    ulStateMachineEvent = 0;
    enStateMachine      = TAF_XCALL_ECC_STATE_MACHINE_ID_BUTT;

    switch (stKmcMsg.enSmsType)
    {
        case TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_MO_KEY_RSP;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_MT_ENCRYPT_IND;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_MT_KEY_RSP;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_ERR_IND:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_ERR_IND;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_IND;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_ACK;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE;
            break;

        case TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND:
            ulStateMachineEvent = TAF_XCALL_KMC_MSG_EVENT_ROMOTE_CTRL_CMD_IND;
            enStateMachine      = TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL;
            break;

        /* 未知消息，不处理 */
        default:
            TAF_ERROR_LOG1(WUEPS_PID_TAF,
                           "TAF_XCALL_RcvXsmsKmcMsgRcvInd: KMC type = ",
                           stKmcMsg.enSmsType);
            return;
    }

    TAF_XCALL_ProcEccEvent(ulStateMachineEvent,
                           enStateMachine,
                           pMsg,
                           (VOS_VOID *)&stKmcMsg);
}


VOS_VOID TAF_XCALL_RcvXsmsKmcMsgSendCnf(VOS_VOID *pMsg)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                       *pstXsmsSendCnf = VOS_NULL_PTR;
    TAF_XCALL_ENCRYPT_VOICE_CTX_STRU                       *pstEncVoiceCtx = VOS_NULL_PTR;

    pstXsmsSendCnf  = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;

    pstEncVoiceCtx = TAF_XCALL_GetVoiceEncryptCtxAddr();

    /* opId是密话协商过程的消息发送opId */
    if (pstXsmsSendCnf->usOpId == pstEncVoiceCtx->stNegotiateCtx.usWaitXsmsCnfOpId)
    {
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XSMS_MSG_EVENT_ENC_VOICE_XSMS_SEND_CNF,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
    }

    /* opId是公钥更新阶段的消息发送opId */
    if (pstXsmsSendCnf->usOpId == pstEncVoiceCtx->stPubKeyUpdateCtx.usWaitXsmsCnfOpId)
    {
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_PUB_KEY_UPDATE_XSMS_SEND_CNF,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE,
                               pMsg,
                               VOS_NULL_PTR);
    }

    /* opId是远程控制阶段的消息发送opId */
    if (pstXsmsSendCnf->usOpId == pstEncVoiceCtx->stRemoteCtrlCtx.usWaitXsmsCnfOpId)
    {
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_ROMOTE_CTRL_XSMS_SEND_CNF,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,
                               pMsg,
                               VOS_NULL_PTR);
    }
}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
