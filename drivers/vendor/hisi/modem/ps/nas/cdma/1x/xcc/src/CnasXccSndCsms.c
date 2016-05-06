/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndCsms.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年10月14日
  最近修改   :
  功能描述   : XCC发送给CSMS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasXccSndCsms.h"
#include  "xcc_sms_pif.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_CSMS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsOrigCallCnf
 功能描述  : 给CSMS发送ID_XCC_CSMS_ORIG_SMS_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_ORIG_SMS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC, sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_ORIG_SMS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->enRslt                      = enCause;
    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsHangupCallCnf
 功能描述  : 给CSMS发送ID_XCC_CSMS_END_SMS_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsHangupCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_CSMS_END_SMS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_END_SMS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_END_SMS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsHangupCallCnf
 功能描述  : 给CSMS发送ID_XCC_CSMS_END_SMS_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
)
{
    XCC_CSMS_ANSWER_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_ANSWER_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_ANSWER_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enRslt                      = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsIncomingCallInd
 功能描述  : 给CSMS发送ID_XCC_CSMS_INCOMING_CALL_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_INCOMING_CALL_IND_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_INCOMING_CALL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucIsAlertAnsByPass          = pstCallInfo->ucIsByPassAlertAns;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsCallConnectInd
 功能描述  : 给CSMS发送ID_XCC_CSMS_CALL_CONN_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_CALL_CONN_IND_STRU        *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_CALL_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_CALL_CONN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_CALL_CONN_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsServiceConnectInd
 功能描述  : 给CSMS发送ID_XCC_CSMS_SERVICE_CONNECT_IND，SO协商完成后，通知SMS
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU                      *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_SERVICE_CONNECT_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsMsgWaitingInd
 功能描述  : 给CSMS发送ID_XCC_CSMS_MSG_WATING_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsMsgWaitingInd(
    VOS_UINT8                           ucMsgCnt
)
{
    XCC_CSMS_MSG_WATING_IND_STRU       *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_MSG_WATING_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_MSG_WATING_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_MSG_WATING_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucMsgCnt                    = ucMsgCnt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
