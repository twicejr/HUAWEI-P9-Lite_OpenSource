

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXCallSndXsms.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_XSMS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID TAF_XCALL_SendXsmsKmcMsgSendReq(
    VOS_UINT16                          usOpId,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucUserData
)
{
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU   *pstXsmsReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen   = sizeof(XCALL_XSMS_KMC_MSG_SEND_REQ_STRU) - 4 * sizeof(VOS_UINT8) + usDataLen;

    /* 分配消息 */
    pstXsmsReq = (XCALL_XSMS_KMC_MSG_SEND_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, ulMsgLen);

    if (VOS_NULL_PTR == pstXsmsReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstXsmsReq + VOS_MSG_HEAD_LENGTH,
               0,
               ulMsgLen - VOS_MSG_HEAD_LENGTH);

    /* 填写VOS消息头 */
    pstXsmsReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstXsmsReq->ulSenderPid     = WUEPS_PID_TAF;
    pstXsmsReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstXsmsReq->ulReceiverPid   = UEPS_PID_XSMS;
    pstXsmsReq->ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstXsmsReq->enMsgId         = ID_XCALL_XSMS_KMC_MSG_SEND_REQ;
    pstXsmsReq->usOpId          = usOpId;
    pstXsmsReq->usDataLen       = usDataLen;

    PS_MEM_CPY(&(pstXsmsReq->aucData[0]),
               pucUserData,
               usDataLen);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstXsmsReq);
}
#endif

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


