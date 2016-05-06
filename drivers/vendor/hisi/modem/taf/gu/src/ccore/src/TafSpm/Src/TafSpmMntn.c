/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmMntn.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : spm模块可维可测相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafSpmMntn.h"
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, begin */
#if (FEATURE_IMS == FEATURE_ON)
#include "TafSpmCtx.h"
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, end */

#include "TafSdcCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_MNTN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/



/*****************************************************************************
 函 数 名  : TAF_SPM_LogFsmInfo
 功能描述  : 状态机启动停止或状态迁移时，以消息形式在SDT中进行显示，方便可维可测
 输入参数  : pstRspData
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月16日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SPM_LogFsmInfo(VOS_VOID)
{
    TAF_SPM_LOG_FSM_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_SPM_LOG_FSM_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_LogFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SPM_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_SPM_LOG_FSM_INFO_IND;

    pstMsg->usClientId                  = TAF_SPM_GetCurrEntityFsmClientId();
    pstMsg->ulState                     = TAF_SPM_GetCurrEntityFsmState();
    pstMsg->ucFsmRunFlg                 = TAF_SPM_GetCurrEntityFsmRunFlg();
    pstMsg->enFsmId                     = TAF_SPM_GetCurrEntityFsmId();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, begin */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_LogSrvDomainSelQueueInfo
 功能描述  : 以消息形式在SDT中显示当前消息queue中缓存的消息数目，方便可维可测
             当前仅打印queue中缓存的消息数目以及最大保存消息的数目，未来需要，
             可以增加其他观测信息。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SPM_LogSrvDomainSelQueueInfo(VOS_VOID)
{
    TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_LogSrvDomainSelQueueInfo: ERROR: Memory allocation Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEQUE_INFO_IND;

    /* get the number of cached message in CC queue */
    pstMsg->ucCachedCcMsgNum            = TAF_SPM_GetCcMsgQueueNum();
    /* set the max number of CC queue */
    pstMsg->ucMaxCcMsgQueueNum          = TAF_SPM_MAX_CC_MSG_QUEUE_NUM;

    /* get the number of cached message in SMS queue */
    pstMsg->ucCachedSmsMsgNum           = TAF_SPM_GetSmsMsgQueueNum();
    /* set the max number of SMS queue */
    pstMsg->ucMaxSmsMsgQueueNum          = TAF_SPM_MAX_SMS_MSG_QUEUE_NUM;

    /* get the number of cached message in SS queue */
    pstMsg->ucCachedSsMsgNum            = TAF_SPM_GetSsMsgQueueNum();
    /* set the max number of SS queue */
    pstMsg->ucMaxSsMsgQueueNum          = TAF_SPM_MAX_SS_MSG_QUEUE_NUM;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

#if ( FEATURE_ON == FEATURE_IMS )
/*****************************************************************************
 函 数 名  : TAF_SPM_LogSrvDomainSelPreconditionInfo
 功能描述  : 以消息形式在SDT中显示与当前域选择相关的前提条件信息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  3.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                 进行正常域选择，否则选择CS域
*****************************************************************************/
VOS_VOID  TAF_SPM_LogSrvDomainSelPreconditionInfo(VOS_VOID)
{
    TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_LogSrvDomainSelPreconditionInfo: ERROR: Memory allocation Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid           = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid         = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength              = sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName             = TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_IND;

    /* get the related NV information */
    pstMsg->stNvInfo.enLteCsServiceCfg        = TAF_SDC_GetLteCsSeviceCap();
    pstMsg->stNvInfo.enSmsDomain              = TAF_SDC_GetSmsDomain();
    pstMsg->stNvInfo.enUeUsageSetting         = TAF_SDC_GetUeUsageSetting();
    pstMsg->stNvInfo.enVociceDomain           = TAF_SDC_GetVoiceDomain();
    pstMsg->stNvInfo.ucLteEmsSupport          = TAF_SDC_GetLteEmsSupportFlag();
    pstMsg->stNvInfo.ucLteImsSupport          = TAF_SDC_GetLteImsSupportFlag();
    pstMsg->stNvInfo.ucSmsOnImsSupport        = TAF_SDC_GetSmsOnImsSupportFlag();
    pstMsg->stNvInfo.ucVideoCallOnImsSupport  = TAF_SDC_GetVideoCallOnImsSupportFlag();
    pstMsg->stNvInfo.ucVoiceCallOnImsSupport  = TAF_SDC_GetVoiceCallOnImsSupportFlag();
    pstMsg->stNvInfo.ucImsRoamSupport         = TAF_SDC_GetRoamingSupportFlag();

    pstMsg->stNvInfo.ucUssdOnImsSupportFlag   = TAF_SDC_GetUssdOnImsSupportFlag();

    /* get network information, including LTE network, IMS network and roaming flag */
    pstMsg->stNwInfo.enLteCsCap               = TAF_SDC_GetLteNwCapInfo()->enLteCsCap;
    pstMsg->stNwInfo.enNwEmcBsCap             = TAF_SDC_GetLteNwCapInfo()->enNwEmcBsCap;
    pstMsg->stNwInfo.enNwImsVoCap             = TAF_SDC_GetLteNwCapInfo()->enNwImsVoCap;
    pstMsg->stNwInfo.ucSmsSupportOnImsServer  = TAF_SPM_GetImsSmsSupportedOnImsServer();
    pstMsg->stNwInfo.ucRoamFlag               = TAF_SDC_GetRoamFlag();

    /* get service status and system mode */
    pstMsg->stSrvStatusInfo.enCsSrvStatus     = TAF_SDC_GetCsServiceStatus();
    pstMsg->stSrvStatusInfo.enPsSrvStatus     = TAF_SDC_GetPsServiceStatus();
    pstMsg->stSrvStatusInfo.enImsRegStatus    = TAF_SDC_GetImsNormalRegStatus();
    pstMsg->stSrvStatusInfo.enSysMode         = TAF_SDC_GetCampSysMode();

    /* get CC/SMS/SS service exist flag */
    pstMsg->stSrvExistInfo.ucCsCallExistFlag  = TAF_SDC_GetCsCallExistFlg();
    pstMsg->stSrvExistInfo.ucImsCallExistFlag = TAF_SDC_GetImsCallExistFlg();
    pstMsg->stSrvExistInfo.ucCsSmsExistFlag   = TAF_SDC_GetCsSmsSrvExistFlg();
    pstMsg->stSrvExistInfo.ucPsSmsExistFlag   = TAF_SDC_GetPsSmsSrvExistFlg();
    pstMsg->stSrvExistInfo.ucImsSmsExistFlag  = TAF_SDC_GetImsSmsSrvExistFlg();
    pstMsg->stSrvExistInfo.ucCsSsExistFlag    = TAF_SDC_GetCsSsSrvExistFlg();
    pstMsg->stSrvExistInfo.ucImsSsExistFlag   = TAF_SDC_GetImsSsSrvExistFlg();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_LogSrvDomainSelRedialInfo
 功能描述  : 以消息形式在SDT中显示与当前域选择换域重拨信息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年2月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_LogSrvDomainSelRedialInfo(VOS_VOID)
{
    TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_LogSrvDomainSelRedialInfo: ERROR: Memory allocation Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU));

    /* 填充消息头信息 */
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid           = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid         = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength              = sizeof(TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName             = TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND;

    /* 填充消息体内容 */
    pstMsg->ucCallRedialSupport               = TAF_SDC_GetCallRedailFromImsToCsSupportFlag();
    pstMsg->ucCallCachedMsgNum                = TAF_SPM_GetNumberOfCallRedialBuffer();
    pstMsg->ucCallMaxCachedMsgNum             = TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM;

    pstMsg->ucSmsRedialSupport                = TAF_SDC_GetSmsRedailFromImsToCsSupportFlag();
    pstMsg->ucSmsCachedMsgNum                 = TAF_SPM_GetNumberOfSmsRedialBuffer();
    pstMsg->ucSmsMaxCachedMsgNum              = TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM;


    /* IMS短信正在发送标志 */    
    pstMsg->ucImsSmsSendingFlg                = TAF_SPM_GetImsSmsSendingFlg(); 

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_LogRedialCallInfo
 功能描述  : 以消息形式在SDT中显示调用IMSA API获取到的呼叫信息

 输入参数  : pstCallInfoInd:调用IMSA API获取到的呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年06月05日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_LogRedialCallInfo(
    IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU                   *pstCallInfoInd
)
{
    TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_LogRedialCallInfo: ERROR: Memory allocation Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU));

    /* 填充消息头信息 */
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid           = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid         = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength              = sizeof(TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName             = TAF_SPM_LOG_REDIAL_CALL_INFO_IND;

    /* 填充消息体内容 */
    pstMsg->ucNumOfCalls                      = pstCallInfoInd->ucNumOfCalls;

    PS_MEM_CPY(pstMsg->astCallInfo, pstCallInfoInd->astCallInfo,
               (pstCallInfoInd->ucNumOfCalls) * sizeof(MN_CALL_INFO_PARAM_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, end */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

