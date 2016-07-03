

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Ps.h"
#include "VcPhyInterface.h"
#include "VcCallInterface.h"
#include "VcCodecInterface.h"
#include "VcComm.h"

#include "NasUtranCtrlInterface.h"

#include "MnComm.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#include "TafOamInterface.h"

#include "VcCtx.h"
#include "VcMntn.h"

#include "Taf_Tafm_Remote.h"

#include "mdrv.h"


#ifdef  __cplusplus
  #if  __cplusplus
      extern "C"{
  #endif
#endif

/*lint -e958*/

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_VC_SEND_MSG_C
/*lint +e767*/

/*****************************************************************************
   2 函数实现
*****************************************************************************/

VOS_UINT32  APP_VC_SendStartReq(
    CALL_VC_CHANNEL_INFO_STRU           *pstChanInfo,
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode
)
{
    /*构造消息VC_PHY_START_REQ，发送给物理层*/
    VCVOICE_START_REQ_STRU             *pstStartReq;
    VOS_UINT32                          ulRet;

    VCVOICE_NET_MODE_ENUM_UINT16        enMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__) || defined (DMT))
    VCVOICE_OP_RSLT_STRU               *pstRstMsg;
    VOS_UINT32                          ulSenderPid;
#endif

    /* 申请消息 */
    pstStartReq = (VCVOICE_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstStartReq)
    {
        return VOS_ERR;
    }

    pstStartReq->usMsgName    = ID_VC_VOICE_START_REQ;
    pstStartReq->ulReceiverPid           = DSP_PID_VOICE;

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    ulSenderPid = pstStartReq->ulReceiverPid;
#endif
    enMode = pstChanInfo->stChannelParam.enMode;
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 如果消息中的制式为WCDMA，则需进一步判断当前是否是工作在TD-SCDMA模式，
        如果当前工作在TD-SCDMA模式，则以TD-SCDMA制式通知HIFI启动语音处理 */
    if ( (VCVOICE_NET_MODE_WCDMA       == enMode)
      && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode ) )
    {
        enMode = VCVOICE_NET_MODE_TDSCDMA;
    }

    /* 如果网络模式是EUTRAN_IMS,则以EUTRAN_IMS制式通知HIFI启动语音处理 */
    if (CALL_VC_MODE_IMS_EUTRAN == pstChanInfo->stChannelParam.enMode)
    {
        enMode = VCVOICE_NET_MODE_IMS_EUTRAN;
    }

    /* 如果网络模式是CDMA,则以CDMA制式通知HIFI启动语音处理 */
    if (CALL_VC_MODE_CDMA == pstChanInfo->stChannelParam.enMode)
    {
        enMode = VCVOICE_NET_MODE_CDMA;
    }

    pstStartReq->enMode       = enMode;

    pstStartReq->enCodecType  = APP_VC_ConvertCallCodeTypeToVodecType(pstChanInfo->stChannelParam.enCodecType);

    pstStartReq->enWorkType   = APP_VC_GetWorkType();

    /* 新增可谓可测需求，发起和释放呼叫时设置底软变量，标志当前是否存在呼叫 */
    (VOS_VOID)mdrv_om_set_voicestate(1);

    ulRet = PS_SEND_MSG(WUEPS_PID_VC, pstStartReq);

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))

    /*构造消息PHY_VC_START_CNF，发送给VC*/
    pstRstMsg = (VCVOICE_OP_RSLT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_OP_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRstMsg)
    {
        return VOS_ERR;
    }

    pstRstMsg->usMsgName          = ID_VOICE_VC_START_CNF;
    pstRstMsg->enExeRslt          = VCVOICE_EXECUTE_RSLT_SUCC;
    pstRstMsg->ulReceiverPid      = WUEPS_PID_VC;
    pstRstMsg->ulSenderPid        = ulSenderPid;

    PS_SEND_MSG(pstStartReq->ulReceiverPid, pstRstMsg);

#endif

    return ulRet;

}


VOS_VOID APP_VC_SendStopReq(
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode
)
{
    /*构造消息VC_PHY_STOP_REQ，发送给物理层*/
    VCVOICE_STOP_REQ_STRU              *pstStopReq;

#if (defined(__PS_WIN32_RECUR__) || defined(DMT))
    VCVOICE_OP_RSLT_STRU               *pstRstMsg;
    VOS_UINT32                          ulSenderPid;
#endif

    /* 申请消息 */
    pstStopReq = (VCVOICE_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstStopReq)
    {
        return;
    }

    pstStopReq->usMsgName = ID_VC_VOICE_STOP_REQ;
    pstStopReq->ulReceiverPid       = DSP_PID_VOICE;


#if (defined(__PS_WIN32_RECUR__) || defined(DMT))
    ulSenderPid = pstStopReq->ulReceiverPid;
#endif

    /* 新增可谓可测需求，发起和释放呼叫时设置底软变量，标志当前是否存在呼叫 */
    (VOS_VOID)mdrv_om_set_voicestate(0);

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_VC, pstStopReq);

#if (defined(__PS_WIN32_RECUR__) || defined(DMT))

    /*构造消息PHY_VC_STOP_CNF，发送给VC*/
    pstRstMsg = (VCVOICE_OP_RSLT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_OP_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRstMsg)
    {
        return;
    }

    pstRstMsg->usMsgName              = ID_VOICE_VC_STOP_CNF;
    pstRstMsg->enExeRslt              = VCVOICE_EXECUTE_RSLT_SUCC;
    pstRstMsg->ulSenderPid            = ulSenderPid;
    pstRstMsg->ulReceiverPid          = WUEPS_PID_VC;

    /* 把pstStopReq->ulReceiverPid改成DSP_PID_VOICE 因为上面消息发送后，pstStopReq就释放了 */
    PS_SEND_MSG(DSP_PID_VOICE, pstRstMsg);

#endif

    return;
}


VOS_UINT32  APP_VC_SendSetDeviceReq(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode
)
{
    /*构造消息VC_PHY_SET_DEVICE_REQ，发送给物理层*/
    VCVOICE_SET_DEVICE_REQ_STRU        *pstSetDeviceReq;
    VOS_UINT32                          ulRet;

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    VCVOICE_OP_RSLT_STRU               *pstRstMsg;
    VOS_UINT32                          ulSenderPid;
#endif

    /* 申请消息 */
    pstSetDeviceReq = (VCVOICE_SET_DEVICE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_SET_DEVICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSetDeviceReq)
    {
        return VOS_ERR;
    }

    pstSetDeviceReq->usMsgName      = ID_VC_VOICE_SET_DEVICE_REQ;
    pstSetDeviceReq->ulReceiverPid  = DSP_PID_VOICE;
    pstSetDeviceReq->usReserve      = 0;
    pstSetDeviceReq->usReserve2     = 0;

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    ulSenderPid = pstSetDeviceReq->ulReceiverPid;
#endif

    pstSetDeviceReq->usDeviceMode    = enDeviceMode;

    ulRet = PS_SEND_MSG(WUEPS_PID_VC, pstSetDeviceReq);

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))

    /*构造消息VCCODEC_EXECUTE_RSLT_SUCC，发送给VC*/
    pstRstMsg = (VCVOICE_OP_RSLT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_OP_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRstMsg)
    {
        return VOS_ERR;
    }

    pstRstMsg->usMsgName          = ID_VOICE_VC_SET_DEVICE_CNF;
    pstRstMsg->enExeRslt          = VCVOICE_EXECUTE_RSLT_SUCC;
    pstRstMsg->ulReceiverPid      = WUEPS_PID_VC;
    pstRstMsg->ulSenderPid        = ulSenderPid;

    PS_SEND_MSG(pstSetDeviceReq->ulReceiverPid, pstRstMsg);

#endif

    return ulRet;
}


VOS_UINT32  APP_VC_SendSetVolumeReq(
    VOS_UINT16                          usVolTarget,
    VOS_INT16                           sVolValue
)
{
    /*构造消息VC_PHY_SET_VOLUME_REQ，发送给物理层*/
    VCVOICE_SET_VOLUME_REQ_STRU        *pstSetVolumeReq;
    VOS_UINT32                          ulRet;

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    VCVOICE_OP_RSLT_STRU               *pstRstMsg;
    VOS_UINT32                          ulSenderPid;
#endif

    /* 申请消息 */
    pstSetVolumeReq = (VCVOICE_SET_VOLUME_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_SET_VOLUME_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSetVolumeReq)
    {
        return VOS_ERR;
    }

    pstSetVolumeReq->usMsgName      = ID_VC_VOICE_SET_VOLUME_REQ;
    pstSetVolumeReq->enVolTarget    = usVolTarget;
    pstSetVolumeReq->sVolValue      = sVolValue;
    pstSetVolumeReq->ulReceiverPid  = DSP_PID_VOICE;
    pstSetVolumeReq->usReserve      = 0;

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    ulSenderPid = pstSetVolumeReq->ulReceiverPid;
#endif

    ulRet = PS_SEND_MSG(WUEPS_PID_VC, pstSetVolumeReq);

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))

    /*构造消息ID_CODEC_VC_SET_VOLUME_CNF，发送给VC*/
    pstRstMsg = (VCVOICE_OP_RSLT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_OP_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRstMsg)
    {
        return VOS_ERR;
    }

    pstRstMsg->usMsgName          = ID_VOICE_VC_SET_VOLUME_CNF;
    pstRstMsg->enExeRslt          = VCVOICE_EXECUTE_RSLT_SUCC;
    pstRstMsg->ulReceiverPid      = WUEPS_PID_VC;
    pstRstMsg->ulSenderPid        = ulSenderPid;

    PS_SEND_MSG(pstSetVolumeReq->ulReceiverPid, pstRstMsg);

#endif

    return ulRet;

}


VOS_VOID APP_VC_SendSetCodecReq(
    CALL_VC_CHANNEL_INFO_STRU           *pstChanInfo
)
{
    /*构造消息VC_PHY_SET_CODEC_REQ，发送给物理层*/
    VCVOICE_SET_CODEC_REQ_STRU         *pstSetCodecReq;
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;


#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    VCVOICE_OP_RSLT_STRU              *pstRstMsg;
    VOS_UINT32                          ulSenderPid;
#endif

    /* 申请消息 */
    pstSetCodecReq = (VCVOICE_SET_CODEC_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_SET_CODEC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSetCodecReq)
    {
        return;
    }

    pstSetCodecReq->usMsgName   = ID_VC_VOICE_SET_CODEC_REQ;

    pstSetCodecReq->enCodecType = APP_VC_ConvertCallCodeTypeToVodecType(pstChanInfo->stChannelParam.enCodecType);

    pstSetCodecReq->ulReceiverPid             = DSP_PID_VOICE;

    enMode = pstChanInfo->stChannelParam.enMode;
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 如果消息中的制式为WCDMA，则需进一步判断当前是否是工作在TD-SCDMA模式，
        如果当前工作在TD-SCDMA模式，则以TD-SCDMA制式通知HIFI启动语音处理 */
    if ( (VCVOICE_NET_MODE_WCDMA       == enMode)
      && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode ) )
    {
        enMode = VCVOICE_NET_MODE_TDSCDMA;
    }

    /* 如果网络模式是EUTRAN_IMS,则以EUTRAN_IMS制式通知HIFI启动语音处理 */
    if (CALL_VC_MODE_IMS_EUTRAN == pstChanInfo->stChannelParam.enMode)
    {
        enMode = VCVOICE_NET_MODE_IMS_EUTRAN;
    }

    /* 如果网络模式是CDMA,则以CDMA制式通知HIFI启动语音处理 */
    if (CALL_VC_MODE_CDMA == pstChanInfo->stChannelParam.enMode)
    {
        enMode = VCVOICE_NET_MODE_CDMA;
    }

    pstSetCodecReq->enMode       = enMode;


#if (defined(__PS_WIN32_RECUR__) || defined (DMT))
    ulSenderPid = pstSetCodecReq->ulReceiverPid;
#endif

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstSetCodecReq))
    {
        VC_ERR_LOG("APP_VC_SendSetCodecReq:ERROR:Send Msg Fail!");
    }

#if (defined(__PS_WIN32_RECUR__) || defined (DMT))

    /*构造消息PHY_VC_SET_CODEC_CNF，发送给VC*/
    pstRstMsg = (VCVOICE_OP_RSLT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_OP_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRstMsg)
    {
        return;
    }

    pstRstMsg->usMsgName          = ID_VOICE_VC_SET_CODEC_CNF;
    pstRstMsg->enExeRslt          = VCVOICE_EXECUTE_RSLT_SUCC;
    pstRstMsg->ulReceiverPid      = WUEPS_PID_VC;
    pstRstMsg->ulSenderPid        = ulSenderPid;

    PS_SEND_MSG(ulSenderPid, pstRstMsg);

#endif

    return;
}


VOS_VOID APP_VC_SendEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32  enCause
)
{
    VC_CALL_MSG_STRU            *pstMsg;

    /*构造消息，发送给CALL模块*/
    /* 申请消息 */
    pstMsg = (VC_CALL_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VC_CALL_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("APP_VC_SendEndCallReq: Alloc Msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH),
               0,
               (sizeof(VC_CALL_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid = WUEPS_PID_TAF;
    pstMsg->enMsgName     = VC_CALL_END_CALL;
    pstMsg->enCause       = enCause;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("APP_VC_SendEndCallReq: Send Msg fail!");
    }

    return;

}


VOS_VOID APP_VC_SendPhyTestModeNotify(
    CALL_VC_RADIO_MODE_ENUM_U8              enMode
)
{
    VC_PHY_TEST_MODE_NOTIFY_STRU            *pstMsg;

    /* 申请消息 */
    pstMsg = (VC_PHY_TEST_MODE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VC_PHY_TEST_MODE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /*
        不同接入模式，需要发送不同的测试模式消息给物理层，当前的测试模式
        只有G DSP需要，所以目前的实现是只发送给GDSP，其他场景直接返回，后面
        其他模的DSP有需要的时候再添加
    */
    if (CALL_VC_MODE_GSM == enMode)
    {
        pstMsg->usMsgName       = ID_VC_GPHY_TEST_MODE_NOTIFY;
        pstMsg->ulReceiverPid   = DSP_PID_GPHY;
    }
    else
    {
        PS_FREE_MSG(WUEPS_PID_VC, pstMsg);
        return;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_WARN_LOG("APP_VC_SendPhyTestModeNotify():WARNING:SEND MSG FIAL");
    }

    return;
}



VOS_UINT32 APP_VC_SendSetForeGroundReq(VOS_VOID)
{
    VCVOICE_FOREGROUND_REQ_STRU        *pstCodecMsg = VOS_NULL_PTR;

    pstCodecMsg = (VCVOICE_FOREGROUND_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(VCVOICE_FOREGROUND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstCodecMsg)
    {
        return VOS_ERR;
    }

    pstCodecMsg->usMsgName       = ID_VC_VOICE_FOREGROUND_REQ;
    pstCodecMsg->usReserve       = 0;
    pstCodecMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCodecMsg->ulSenderPid     = WUEPS_PID_VC;
    pstCodecMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCodecMsg->ulReceiverPid   = DSP_PID_VOICE;

    if (VOS_OK != PS_SEND_MSG(pstCodecMsg->ulSenderPid, pstCodecMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 APP_VC_SendSetBackGroundReq(VOS_VOID)
{
    VCVOICE_BACKGROUND_REQ_STRU        *pstCodecMsg = VOS_NULL_PTR;

    pstCodecMsg = (VCVOICE_BACKGROUND_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(VCVOICE_BACKGROUND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstCodecMsg)
    {
        return VOS_ERR;
    }

    pstCodecMsg->usMsgName       = ID_VC_VOICE_BACKGROUND_REQ;
    pstCodecMsg->usReserve       = 0;
    pstCodecMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCodecMsg->ulSenderPid     = WUEPS_PID_VC;
    pstCodecMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCodecMsg->ulReceiverPid   = DSP_PID_VOICE;

    if (VOS_OK != PS_SEND_MSG(pstCodecMsg->ulSenderPid, pstCodecMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 APP_VC_SendGroundQry(VOS_VOID)
{
    VCVOICE_GROUND_QRY_STRU    *pstCodecMsg = VOS_NULL_PTR;

    pstCodecMsg = (VCVOICE_GROUND_QRY_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(VCVOICE_GROUND_QRY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCodecMsg)
    {
        return VOS_ERR;
    }

    pstCodecMsg->usMsgName       = ID_VC_VOICE_GROUND_QRY;
    pstCodecMsg->usReserve       = 0;
    pstCodecMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCodecMsg->ulSenderPid     = WUEPS_PID_VC;
    pstCodecMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCodecMsg->ulReceiverPid   = DSP_PID_VOICE;

    if (VOS_OK != PS_SEND_MSG(pstCodecMsg->ulSenderPid, pstCodecMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID APP_VC_SendSetForeGroundCnf(
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg = VOS_NULL_PTR;

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return;
    }

    PS_MEM_SET(pstAtMsg, 0x00, sizeof(MN_AT_IND_EVT_STRU));

    pstAtMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAtMsg->ulSenderPid       = WUEPS_PID_VC;
    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAtMsg->ulLength          = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = APP_VC_MSG_SET_FOREGROUND_CNF;

    /* 回复消息内容中第一个字节为设置结果 */
    if ( VCVOICE_EXECUTE_RSLT_SUCC == enExeRslt )
    {
        pstAtMsg->aucContent[0] = VOS_OK;
    }
    else
    {
        pstAtMsg->aucContent[0] = VOS_ERR;
    }

    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg) )
    {
        return;
    }

    return;
}


VOS_VOID APP_VC_SendSetBackGroundCnf(
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg = VOS_NULL_PTR;

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return;
    }

    PS_MEM_SET(pstAtMsg, 0x00, sizeof(MN_AT_IND_EVT_STRU));

    pstAtMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAtMsg->ulSenderPid       = WUEPS_PID_VC;
    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAtMsg->ulLength          = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = APP_VC_MSG_SET_BACKGROUND_CNF;

    /* 回复消息内容中第一个字节为设置结果 */
    if ( VCVOICE_EXECUTE_RSLT_SUCC == enExeRslt )
    {
        pstAtMsg->aucContent[0] = VOS_OK;
    }
    else
    {
        pstAtMsg->aucContent[0] = VOS_ERR;
    }

    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg) )
    {
        return;
    }

    return;
}


VOS_VOID APP_VC_SendGroundRsp(
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_GROUND_ENUM_UINT16          enState ,
    VOS_UINT8                           ucQryRslt
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg = VOS_NULL_PTR;
    APP_VC_QRY_GROUNG_RSP_STRU          stQryRsp;

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return;
    }

    PS_MEM_SET(pstAtMsg, 0x00, sizeof(MN_AT_IND_EVT_STRU));

    pstAtMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAtMsg->ulSenderPid       = WUEPS_PID_VC;
    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAtMsg->ulLength          = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = APP_VC_MSG_FOREGROUND_RSP;

    /* 模式查询结果 */
    stQryRsp.ucQryRslt   = ucQryRslt;
    stQryRsp.aucReserved = 0;
    stQryRsp.enGround    = (APP_VC_QRY_GROUND_ENUM_U16)enState;

    /* 填写新消息内容 */
    PS_MEM_CPY(&pstAtMsg->aucContent[0], &stQryRsp, sizeof(APP_VC_QRY_GROUNG_RSP_STRU));

    /*发送消息到AT_PID;*/
    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg))
    {
        return;
    }

    return;
}


VOS_UINT32 APP_VC_SendSetModemLoopReq(VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop)
{
    VCVOICE_LOOP_REQ_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (VCVOICE_LOOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(VCVOICE_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00, sizeof(VCVOICE_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写新消息内容 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_VC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_VOICE;

    pstMsg->usMsgName       = ID_VC_VOICE_LOOP_REQ;
    pstMsg->usReserve1      = 0;
    pstMsg->enMode          = enVoiceLoop;
    pstMsg->usReserve2      = 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID APP_VC_SendImsaExceptionNtf(
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enCause
)
{
    VC_IMSA_HIFI_EXCEPTION_NTF_STRU    *pstMsg;

    pstMsg = (VC_IMSA_HIFI_EXCEPTION_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                        sizeof(VC_IMSA_HIFI_EXCEPTION_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(VC_IMSA_HIFI_EXCEPTION_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid       = WUEPS_PID_VC;
    pstMsg->ulReceiverPid     = PS_PID_IMSA;
    pstMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulLength          = sizeof(VC_IMSA_HIFI_EXCEPTION_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName         = ID_VC_IMSA_HIFI_EXCEPTION_NTF;
    pstMsg->enCause           = enCause;

    /* 发送消息到IMSA */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        return;
    }

    return;
}
#endif



VOS_VOID  APP_VC_LogEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
)
{
    TAF_OAM_LOG_END_CALL_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_OAM_LOG_END_CALL_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_VC,
                                         sizeof(TAF_OAM_LOG_END_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(TAF_OAM_LOG_END_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_VC;
    pstMsg->ulReceiverPid   = WUEPS_PID_VC;
    pstMsg->ulLength        = sizeof(TAF_OAM_LOG_END_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId         = TAF_OAM_LOG_END_CALL_REQ;
    pstMsg->ulCause         = enVcCause;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_VC, pstMsg);

    return;
}


#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID APP_VC_SendAtSetCnf(
    VOS_UINT16                          usMsgName,
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg = VOS_NULL_PTR;
    APP_VC_SET_MSD_CNF_STRU            *pstRslt  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(MN_AT_IND_EVT_STRU) - 4
            - VOS_MSG_HEAD_LENGTH
            + sizeof(APP_VC_SET_MSD_CNF_STRU);

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, ulLen);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        VC_ERR_LOG("APP_VC_SendAtSetCnf:ALLOC MSG FIAL");
        return;
    }

    PS_MEM_SET(pstAtMsg, 0x00, sizeof(MN_AT_IND_EVT_STRU));

    pstAtMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAtMsg->ulSenderPid       = WUEPS_PID_VC;
    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAtMsg->ulLength          = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = usMsgName;

    pstRslt = (APP_VC_SET_MSD_CNF_STRU *)pstAtMsg->aucContent;

    /* 回复消息内容中第一个字节为设置结果 */
    if ( VCVOICE_EXECUTE_RSLT_SUCC == enExeRslt )
    {
        pstRslt->ucRslt = VOS_OK;
    }
    else
    {
        pstRslt->ucRslt = VOS_ERR;
    }

    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg))
    {
        VC_ERR_LOG("APP_VC_SendAtSetCnf:SEND MSG FIAL");
    }

    return;
}


VOS_VOID APP_VC_SendQryMsdCnf(
    MN_CLIENT_ID_T                      usClientId
)
{
    VOS_UINT8                          *pstMsd    = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU                 *pstAtMsg  = VOS_NULL_PTR;
    APP_VC_MSG_QRY_MSD_CNF_STRU         stQryCnf;
    VOS_UINT32                          ulLen;
    APP_VC_MSG_QRY_MSD_CNF_STRU        *pstQryCnf = VOS_NULL_PTR;

    ulLen = sizeof(MN_AT_IND_EVT_STRU)
            - VOS_MSG_HEAD_LENGTH - 4
            + sizeof(APP_VC_MSG_QRY_MSD_CNF_STRU);

    /* 初始化stQryCnf */
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    pstMsd      = APP_VC_GetEcallMsdAddr();

    pstAtMsg    = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, ulLen);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return;
    }

    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = APP_VC_MSG_QRY_MSD_CNF;

    /* 设置结果 */
    stQryCnf.ucQryRslt  = VOS_OK;

    /* 根据产品线要求，如果没有下发过MSD数据，则直接返回全0。
       pstMsd指向的本地MSD数据即为全0。*/
    PS_MEM_CPY(stQryCnf.aucMsdData, pstMsd, APP_VC_MSD_DATA_LEN);


    /* 填写新消息内容 */
    pstQryCnf = (APP_VC_MSG_QRY_MSD_CNF_STRU *)&(pstAtMsg->aucContent[0]);
    PS_MEM_CPY(pstQryCnf, &stQryCnf, sizeof(APP_VC_MSG_QRY_MSD_CNF_STRU));

    /*发送消息到AT */
    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg))
    {
        return;
    }

    return;
}


VOS_VOID APP_VC_SendQryEcallCfgCnf(
    MN_CLIENT_ID_T                      usClientId
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg  = VOS_NULL_PTR;
    APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU   stQryCnf;
    VOS_UINT32                          ulLen;
    APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU  *pstQryCnf = VOS_NULL_PTR;

    /* 初始化 */
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    ulLen   = sizeof(MN_AT_IND_EVT_STRU) - 4
              + sizeof(APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU)
              - VOS_MSG_HEAD_LENGTH;

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, ulLen);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return;
    }

    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->clientId          = MN_GetRealClientId(usClientId, WUEPS_PID_VC);
    pstAtMsg->usMsgName         = APP_VC_MSG_QRY_ECALL_CFG_CNF;

    /* 模式查询结果 */
    stQryCnf.ucQryRslt      = VOS_OK;

    /* 获取配置信息 */
    APP_VC_GetCurrEcallCfg(&stQryCnf.enMode, &stQryCnf.enVocConfig);


    /* 填写新消息内容 */
    pstQryCnf = (APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU *)&(pstAtMsg->aucContent[0]);
    PS_MEM_CPY(pstQryCnf, &stQryCnf, sizeof(APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU));

    /*发送消息到AT */
    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg))
    {
        return;
    }

    return;
}


VOS_UINT32  APP_VC_SendEcallCfgReq(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enMode,
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16 enVocConfig
)
{
    /*构造消息ID_VC_VOICE_SET_ECALLCFG_REQ，发送给MED*/
    VCVOICE_SET_ECALLCFG_REQ_STRU      *pstSetEcallCfg = VOS_NULL_PTR;

    /* 申请消息 */
    pstSetEcallCfg = (VCVOICE_SET_ECALLCFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_SET_ECALLCFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSetEcallCfg)
    {
        return VOS_ERR;
    }

    pstSetEcallCfg->ulReceiverPid   = DSP_PID_VOICE;
    pstSetEcallCfg->usMsgName       = ID_VC_VOICE_SET_ECALLCFG_REQ;
    APP_VC_MapMedMsdMode(enMode, &pstSetEcallCfg->enMsdMode);
    APP_VC_MapMedVocConfig(enVocConfig, &pstSetEcallCfg->enNoVoice);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstSetEcallCfg))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_VOID APP_VC_SendEcallTransStatusInd(
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8      enEcallTransStatus,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enEcallTransFailCause
)
{
    /*构造消息VC_CALL_ECALL_TRANS_STATUS_NTF，发送给Call*/
    VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *pstTransStatus = VOS_NULL_PTR;

    /* 申请消息 */
    pstTransStatus = (VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VC_CALL_ECALL_TRANS_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstTransStatus)
    {
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8 *)pstTransStatus + VOS_MSG_HEAD_LENGTH,
                0x0,
                sizeof(VC_CALL_ECALL_TRANS_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstTransStatus->ulReceiverPid           = WUEPS_PID_TAF;
    pstTransStatus->enMsgName               = VC_CALL_ECALL_TRANS_STATUS_NTF;
    pstTransStatus->enEcallTransStatus      = enEcallTransStatus;
    pstTransStatus->enEcallTransFailCause   = enEcallTransFailCause;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstTransStatus))
    {
        return;
    }

    return;

}


VOS_VOID APP_VC_SendMsdReq(VOS_VOID)
{
    VCVOICE_SET_MSD_REQ_STRU           *pstMsdReq  = VOS_NULL_PTR;
    VOS_UINT8                          *pucMsdAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 勾出全局变量g_stVcStateMgmt的内容，查看enMsdFlag和enInECall，
       以便分析没有发送msd数据的原因 */
    VC_MNTN_TraceCtxInfo();

    /* 判断当前是否有MSD数据 */
    if (PS_FALSE == APP_VC_GetMsdFlag())
    {
        return;
    }

    /* 当前是否在ecall过程中 */
    if (PS_FALSE == APP_VC_GetInEcallFlag())
    {
        return;
    }

    /* 初始化局部变量 */
    pucMsdAddr = APP_VC_GetEcallMsdAddr();

     /* 申请消息 */
    pstMsdReq = (VCVOICE_SET_MSD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                 sizeof(VCVOICE_SET_MSD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsdReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstMsdReq + VOS_MSG_HEAD_LENGTH, 0, sizeof(VCVOICE_SET_MSD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsdReq->ulReceiverPid            = DSP_PID_VOICE;
    pstMsdReq->usMsgName                = ID_VC_VOICE_SET_MSD_REQ;
    pstMsdReq->ulMsdLen                 = APP_VC_MSD_DATA_LEN;

    /* 拷贝MSD数据 */
    PS_MEM_CPY(pstMsdReq->aucMsd, pucMsdAddr, APP_VC_MSD_DATA_LEN);

    ulRet = PS_SEND_MSG(WUEPS_PID_VC, pstMsdReq);
    if (VOS_ERR == ulRet)
    {
        VC_ERR_LOG("APP_VC_SendMsdReq:SEND MSG FIAL");

        return;
    }

    return;
}
#endif


VOS_UINT32 APP_VC_SendDtmfInd(
    VOICEVC_DTMF_IND_STRU              *pstDtmfInd
)
{
    MN_AT_IND_EVT_STRU                 *pstAtMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    APP_VC_DTMF_DECODER_IND_STRU        stDtmfDecoderInd;

    ulLength = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;

    pstAtMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,ulLength);
    if (VOS_NULL_PTR == pstAtMsg)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstAtMsg, 0x00, sizeof(MN_AT_IND_EVT_STRU));
    PS_MEM_SET(&stDtmfDecoderInd, 0x00, sizeof(APP_VC_DTMF_DECODER_IND_STRU));

    pstAtMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAtMsg->ulSenderPid       = WUEPS_PID_VC;
    pstAtMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstAtMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAtMsg->ulLength          = ulLength;
    pstAtMsg->usMsgName         = APP_VC_MSG_DTMF_DECODER_IND;
    pstAtMsg->clientId          = MN_GetRealClientId(TAF_CLIENTID_BROADCAST, WUEPS_PID_VC);
    pstAtMsg->usLen             = sizeof(APP_VC_DTMF_DECODER_IND_STRU);

    /* 模式查询结果 */
    stDtmfDecoderInd.ucDtmfCode = (VOS_CHAR)pstDtmfInd->usDtmfCode;

    /* 填写新消息内容 */
    PS_MEM_CPY(pstAtMsg->aucContent, &stDtmfDecoderInd, pstAtMsg->usLen);

    /*发送消息到AT_PID;*/
    if (VOS_OK != PS_SEND_MSG(pstAtMsg->ulSenderPid, pstAtMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32  APP_VC_SendSoCtrlOrderInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    VOS_UINT8                       ucORDQ
)
{
    VCVOICE_SO_CTRL_ORDER_IND_STRU     *pstSoCtrlOrder = VOS_NULL_PTR;

    pstSoCtrlOrder = (VCVOICE_SO_CTRL_ORDER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_VC,
                                                            sizeof(VCVOICE_SO_CTRL_ORDER_IND_STRU));

    if (VOS_NULL_PTR == pstSoCtrlOrder)
    {
        return VOS_ERR;
    }

    /* 填写消息内容 */
    pstSoCtrlOrder->ulReceiverPid   = DSP_PID_VOICE;
    pstSoCtrlOrder->ulLength        = sizeof(VCVOICE_SO_CTRL_ORDER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstSoCtrlOrder + VOS_MSG_HEAD_LENGTH,
               0 ,
               pstSoCtrlOrder->ulLength);

    pstSoCtrlOrder->usMsgName       = ID_VC_VOICE_SO_CTRL_ORDER_IND;
    pstSoCtrlOrder->enCodecType     = enCodecType;
    pstSoCtrlOrder->ucORDQ          = ucORDQ;

    PS_SEND_MSG(WUEPS_PID_VC, pstSoCtrlOrder);

    return VOS_OK;

}


VOS_UINT32  APP_VC_SendSoCtrlMsgInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    SO_CTRL_MSG_CODEC_STRU         *pstCodec
)
{
    VCVOICE_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsg = VOS_NULL_PTR;

    pstSoCtrlMsg = (VCVOICE_SO_CTRL_MSG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_VC,
                                                            sizeof(VCVOICE_SO_CTRL_MSG_IND_STRU));

    if (VOS_NULL_PTR == pstSoCtrlMsg)
    {
        return VOS_ERR;
    }

    /* 填写消息内容 */
    pstSoCtrlMsg->ulReceiverPid   = DSP_PID_VOICE;
    pstSoCtrlMsg->ulLength        = sizeof(VCVOICE_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstSoCtrlMsg + VOS_MSG_HEAD_LENGTH,
               0,
               pstSoCtrlMsg->ulLength);

    pstSoCtrlMsg->usMsgName       = ID_VC_VOICE_SO_CTRL_MSG_IND;
    pstSoCtrlMsg->enCodecType     = enCodecType;

    PS_MEM_CPY(&pstSoCtrlMsg->stSoCtrlMsg,
               pstCodec,
               sizeof(SO_CTRL_MSG_CODEC_STRU));

    PS_SEND_MSG(WUEPS_PID_VC, pstSoCtrlMsg);

    return VOS_OK;

}

#endif

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


