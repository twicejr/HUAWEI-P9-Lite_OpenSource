/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndAps.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月6日
  最近修改   :
  功能描述   : XCC发送给APS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月6日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXccSndAps.h"
#include  "CnasMain.h"
#include  "xcc_aps_pif.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsDataCallSuspendInd
 功能描述  : XCC通知APS挂起
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsDataCallSuspendInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
)
{
    XCC_APS_DATA_CALL_SUSPEND_IND_STRU         *pstMsg         = VOS_NULL_PTR;
    XCC_APS_SERVICE_TYPE_ENUM_UINT8             enTmpSrvType;

    enTmpSrvType = XCC_APS_SERVICE_TYPE_BUTT;

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_VOICE_CALL;
    }
    else if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_SMS;

    }
    else if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_AGPS;

    }
    else
    {
        return;
    }

    pstMsg = (XCC_APS_DATA_CALL_SUSPEND_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_DATA_CALL_SUSPEND_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_DATA_CALL_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_DATA_CALL_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_XCC_APS_DATA_CALL_SUSPEND_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(XCC_APS_DATA_CALL_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnectId;
    pstMsg->enServiceType               = enTmpSrvType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsDataCallResumeInd
 功能描述  : XCC通知APS挂起
 输入参数  : ucConnectId   -- 连接标识
             enServiceType -- 业务类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : c00294324
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsDataCallResumeInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU          *pstMsg         = VOS_NULL_PTR;
    XCC_APS_SERVICE_TYPE_ENUM_UINT8             enTmpSrvType;

    enTmpSrvType = XCC_APS_SERVICE_TYPE_BUTT;

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_VOICE_CALL;
    }
    else if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_SMS;

    }
    else if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
    {
        enTmpSrvType = XCC_APS_SERVICE_TYPE_AGPS;

    }
    else
    {
        return;
    }

    pstMsg = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_DATA_CALL_RESUME_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_DATA_CALL_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_DATA_CALL_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_XCC_APS_DATA_CALL_RESUME_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(XCC_APS_DATA_CALL_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnectId;
    pstMsg->enServiceType               = enTmpSrvType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsOrigDataCallCnf
 功能描述  : 给APS发送ID_XCC_APS_ORIG_DATA_CALL_CNF
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
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsOrigDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucConRef,
    VOS_UINT8                           ucConnectId,
    VOS_INT16                           sRssi
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU            *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_ORIG_DATA_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_ORIG_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_ORIG_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_ORIG_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_ORIG_DATA_CALL_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->enRslt                      = enCause;
    pstMsg->enFailLayer                 = enFailLayer;
    pstMsg->ucCallId                    = ucCallId;
    /* APS给PPP携带ConRef，用于查找信道 */
    pstMsg->ucConRef                    = ucConRef;
    pstMsg->ucConnectId                 = ucConnectId;
    pstMsg->sRssi                       = sRssi;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsHangupDataCallCnf
 功能描述  : 给APS发送ID_XCC_APS_HANGUP_DATA_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsHangupDataCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU                      *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_HANGUP_DATA_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_HANGUP_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_HANGUP_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_HANGUP_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_HANGUP_DATA_CALL_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsAnswerDataCallCnf
 功能描述  : 给APS发送ID_XCC_APS_ANSWER_DATA_CALL_CNF
 输入参数  : ucCallId    -- 呼叫实体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsAnswerDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU                      *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_ANSWER_DATA_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_ANSWER_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_ANSWER_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_ANSWER_DATA_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_ANSWER_DATA_CALL_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enRslt                      = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsIncomingCallInd
 功能描述  : 给APS发送ID_XCC_APS_INCOMING_CALL_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_INCOMING_CALL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_INCOMING_CALL_IND;
    pstMsg->usOpId                      = 0;
    /* APS需要通过初始化SO来判断进哪个DORMANT */
    pstMsg->enSo                        = pstCallInfo->enInitSo;
    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucIsAlertAnsByPass          = pstCallInfo->ucIsByPassAlertAns;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsDataCallConnectInd
 功能描述  : 给APS发送ID_XCC_APS_DATA_CALL_CONN_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsDataCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_DATA_CALL_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_DATA_CALL_CONN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_DATA_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_DATA_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_DATA_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_DATA_CALL_CONN_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsDataServiceConnectInd
 功能描述  : 给APS发送ID_XCC_APS_DATA_SERVICE_CONNECT_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsDataServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU                  *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_DATA_SERVICE_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_DATA_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_DATA_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_DATA_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_DATA_SERVICE_CONNECT_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    pstMsg->ucSrId                      = pstCallInfo->ucSrId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsDataCallDiscInd
 功能描述  : 给APS发送ID_XCC_APS_DATA_CALL_DISC_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsDataCallDiscInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU                        *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_APS_DATA_CALL_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_DATA_CALL_DISC_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_DATA_CALL_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_DATA_CALL_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_DATA_CALL_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_DATA_CALL_DISC_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->enCause                     = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsSoCtrlMsgInd
 功能描述  : 给APS发送ID_XCC_APS_SO_CTRL_MSG_IND
 输入参数  : pstCallInfo    -- 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月14日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsSoCtrlMsgInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{

    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (XCC_APS_SO_CTRL_MSG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_SO_CTRL_MSG_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_SO_CTRL_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_SO_CTRL_MSG_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->enSo                        = (TAF_CDMA_SO_TYPE_ENUM_UINT16)pstSOCM->usSo;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;

    /* 1.  Dormant Timer Control
            Field                         Length(bits)
            DORM_CNTL                      3
            RESERVED                       2
            FIELD_TYPE                     3
            DORM_TIME                      0 or 8

        2.  Packet Zone Reconnection Control
            Field                         Length(bits)
            PKT_CON_CNTL                   3
            RESERVED                       2
            FIELD_TYPE                     3
            RESERVED                       0 or 4
            PKT_ZONE_LIST_LEN              0 or 4 */

    pstMsg->enFieldType = pstSOCM->aucData[0] & CNAS_XCC_LOW_3_BIT_MASK;

    switch(pstMsg->enFieldType)
    {
        case XCC_APS_SO_CTRL_FIELD_DORMANT_TIMER_CTRL:
            /* Dormant Timer Control */
            pstMsg->ucDormCntl      = (VOS_UINT8)(pstSOCM->aucData[0] >> CNAS_XCC_5_BIT_OFFSET);
            if (pstSOCM->usBitLen >= CNAS_XCC_BIT_LEN_16_BIT)
            {
                pstMsg->ucDormTimer = pstSOCM->aucData[1];
            }
            break;

        case XCC_APS_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL:
            /* Packet Zone Reconnection Control */
            pstMsg->ucPktConCntl    = (VOS_UINT8)(pstSOCM->aucData[0] >> CNAS_XCC_5_BIT_OFFSET);
            if (pstSOCM->usBitLen >= CNAS_XCC_BIT_LEN_16_BIT)
            {
                pstMsg->ucPktZoneListLen = (VOS_UINT8)(pstSOCM->aucData[1] & CNAS_XCC_LOW_4_BIT_MASK);
            }
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_SndApsSoCtrlMsgInd: Wrong Field Type ");
            PS_FREE_MSG(UEPS_PID_XCC, pstMsg);
            return;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* Send Message */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndApsUpdateDataCallInfoInd
 功能描述  : Send APS Message:ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND
 输入参数  : pstCallInfo    -- Call Related Information
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndApsUpdateDataCallInfoInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->ulLength                    = sizeof(XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->ucSrId                      = pstCallInfo->ucSrId;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

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
