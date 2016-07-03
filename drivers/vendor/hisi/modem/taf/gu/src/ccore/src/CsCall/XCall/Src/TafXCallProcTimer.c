


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafXCallProcTimer.h"
#include "TafXCallCtx.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXCallSndMma.h"
#include "TafXCallSndApp.h"
#include "TafXCallProcXcc.h"
#include "TafMmaSndOm.h"

#include "TafXCallProcEccSrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_TIMER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_XCALL_RcvTiWaitCallRedialPeriodExpired(VOS_VOID *pMsg)
{
    /* nothing to do here */

    return;
}


VOS_VOID TAF_XCALL_RcvTiWaitCallRedialIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulRemainTimeLen;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    enCallType          = TAF_XCALL_GetCallType(ucCallId);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        /* 发送呼叫消息给XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);
    }
    else
    {
        if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == TAF_SDC_GetCsServiceStatus())
         && (MN_CALL_TYPE_EMERGENCY                 == enCallType))
        {
            /* 发送呼叫消息给XCC */
            TAF_XCALL_SndXccOrigCallReq(ucCallId);

            return;
        }

        ulRemainTimeLen = 0;
        TAF_XCALL_GetRemainTimerLen(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId, &ulRemainTimeLen);

        if (ulRemainTimeLen >= TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN)
        {


            TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

        }
        else
        {
            /* 停止重拨定时器,如果定时器未启动或call id不一致则跳过 */
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId);

            TAF_XCALL_UpdateCcCause(ucCallId, TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
            TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                                   TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                                   pMsg,
                                   VOS_NULL_PTR);
#endif

            /* 上报呼叫失败 */
            TAF_XCALL_SndCallReleaseInd(ucCallId);


            /* 给MMA发送TAF_MMA_1X_CALL_END_NTF消息 */
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* 释放呼叫实体 */
            TAF_XCALL_FreeCallEntity(ucCallId);

        }
    }

    return;
}



VOS_VOID TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;

    /* 处理缓存，理论上，下一条消息是Stop Cont Dtmf */
    TAF_XCALL_ProcDtmfBuffer(ucCallId);
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

VOS_VOID TAF_XCALL_RcvTiVoiceEncryptWaitOrigReqExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_WAIT_ORIG_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}


VOS_VOID TAF_XCALL_RcvTiDelayEncryptReqExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_DELAY_SEND_ENCRYPT_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}


VOS_VOID TAF_XCALL_RcvTiTx01Expired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_TX01,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}


VOS_VOID TAF_XCALL_RcvTiTx02Expired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_TX02,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}


VOS_VOID TAF_XCALL_RcvTiRemoteCtrlWaitApAnswerExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_REMOTE_CTRL_WAIT_AP_ANSWER,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,
                           pMsg,
                           VOS_NULL_PTR);
}


VOS_VOID TAF_XCALL_RcvTiPubKeyUpdateWaitAckExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_PUB_KEY_UPDATE_WAIT_ACK,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE,
                           pMsg,
                           VOS_NULL_PTR);
}

#endif

#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




