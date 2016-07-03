

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallSndVc.h"
#include "PsCommonDef.h"
#include "TafXCallCtx.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_VC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID  TAF_XCALL_SndVcChannelInfoInd(
    CALL_VC_MSG_ID_ENUM_U16             enEventType,
    CALL_VC_CHANNEL_INFO_STRU          *pstChannelInfo
)
{
    CALL_VC_CHANNEL_INFO_MSG_STRU       *pstChannelInfoMsg;

    /* 申请消息 */
    pstChannelInfoMsg = (CALL_VC_CHANNEL_INFO_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(CALL_VC_CHANNEL_INFO_MSG_STRU));

    if (VOS_NULL_PTR == pstChannelInfoMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstChannelInfoMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(CALL_VC_CHANNEL_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    pstChannelInfoMsg->ulReceiverPid = WUEPS_PID_VC;
    pstChannelInfoMsg->enMsgName     = enEventType;

    pstChannelInfoMsg->stChannelInfo = *pstChannelInfo;

    PS_SEND_MSG(WUEPS_PID_TAF, pstChannelInfoMsg);

    return;
}





VOS_VOID TAF_XCALL_SndVcSoCtrlMsgInd(
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType,
    VOS_UINT8                           ucRateReduc,
    VOS_UINT8                           ucMobileToMobile,
    VOS_UINT8                           ucInitCodec
)
{
    CALL_VC_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsg = VOS_NULL_PTR;

    /* 申请消息 */
    pstSoCtrlMsg = (CALL_VC_SO_CTRL_MSG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(CALL_VC_SO_CTRL_MSG_IND_STRU));
    if (VOS_NULL_PTR == pstSoCtrlMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSoCtrlMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(CALL_VC_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSoCtrlMsg->ulReceiverPid         = WUEPS_PID_VC;
    pstSoCtrlMsg->ulLength              = sizeof(CALL_VC_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSoCtrlMsg->enMsgName             = CALL_VC_SO_CTRL_MSG_IND;

    pstSoCtrlMsg->enCodecType           = enCodecType;
    pstSoCtrlMsg->ucInitCodec           = ucInitCodec;
    pstSoCtrlMsg->ucRateReduc           = ucRateReduc;
    pstSoCtrlMsg->ucMobileToMobile      = ucMobileToMobile;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSoCtrlMsg);

    return;

}


VOS_VOID TAF_XCALL_SndVcSoCtrlOrderInd(
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType,
    VOS_UINT8                           ucORDQ
)
{
    CALL_VC_SO_CTRL_ORDER_IND_STRU     *pstSoCtrlOder = VOS_NULL_PTR;

    /* 申请消息 */
    pstSoCtrlOder = (CALL_VC_SO_CTRL_ORDER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(CALL_VC_SO_CTRL_ORDER_IND_STRU));
    if (VOS_NULL_PTR == pstSoCtrlOder)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSoCtrlOder + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(CALL_VC_SO_CTRL_ORDER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSoCtrlOder->ulReceiverPid = WUEPS_PID_VC;
    pstSoCtrlOder->ulLength      = sizeof(CALL_VC_SO_CTRL_ORDER_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSoCtrlOder->enMsgName     = CALL_VC_SO_CTRL_ORDER_IND;

    pstSoCtrlOder->enCodecType   = enCodecType;
    pstSoCtrlOder->ucORDQ        = ucORDQ;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSoCtrlOder);

    return;
}


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


