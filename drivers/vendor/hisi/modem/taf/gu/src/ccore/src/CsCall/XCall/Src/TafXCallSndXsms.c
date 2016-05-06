/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallSndXsms.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年10月22日
  功能描述   : TAF X CALL发送给SMS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

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
/*****************************************************************************
 函 数 名  : TAF_XCALL_SendXsmsKmcMsgSendReq
 功能描述  : 请求XSMS发送KMC消息
 输入参数  : usOpId -- 当前消息的操作码
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
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


