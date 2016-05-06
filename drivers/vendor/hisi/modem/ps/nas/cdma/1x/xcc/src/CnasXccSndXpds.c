/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndXpds.c
  版 本 号   : 初稿
  作    者   : y00314741
  生成日期   : 2015年08月31日
  最近修改   :
  功能描述   : XCC发送给XPDS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_XPDS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXpdsOrigCallCnf
 功能描述  : 给XPDS发送ID_XCC_XPDS_ORIG_AGPS_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU   *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_ORIG_AGPS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->enRslt                      = enCause;
    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enIsL2Err                   = enFailLayer;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXpdsEndCallCnf
 功能描述  : 给XPDS发送ID_XCC_XPDS_END_AGPS_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsEndCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_XPDS_END_AGPS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_END_AGPS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_END_AGPS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXpdsIncomingCallInd
 功能描述  : 给XPDS发送ID_XCC_XPDS_INCOMING_CALL_IND
 输入参数  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_INCOMING_CALL_IND_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_INCOMING_CALL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucIsAlertAnsByPass          = pstCallInfo->ucIsByPassAlertAns;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndCsmsCallConnectInd
 功能描述  : 给XPDS发送ID_XCC_XPDS_CALL_CONN_IND
 输入参数  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_CALL_CONN_IND_STRU        *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_CALL_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_CALL_CONN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_CALL_CONN_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXpdsAnswerCallCnf
 功能描述  : 给XPDS发送ID_XCC_XPDS_ANSWER_CALL_CNF
 输入参数  : VOS_UINT8                           ucCallId-- 呼叫实体
             TAF_XCC_CAUSE_ENUM_UINT32           enRslt
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
)
{
    XCC_XPDS_ANSWER_CALL_CNF_STRU      *pstMsg           = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_ANSWER_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_ANSWER_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enRslt                      = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXpdsServiceConnectInd
 功能描述  : 给XPDS发送ID_XCC_XPDS_SERVICE_CONNECT_IND
 输入参数  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_SERVICE_CONNECT_IND_STRU  *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_SERVICE_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_SERVICE_CONNECT_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
