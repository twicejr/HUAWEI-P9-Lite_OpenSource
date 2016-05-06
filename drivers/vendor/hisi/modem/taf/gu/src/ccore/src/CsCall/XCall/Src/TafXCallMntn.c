/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallMntn.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月20日
  功能描述   : XCALL的可维可测
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月20日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogCallInfo
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月20日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月13日
    作    者   : f279542
    修改内容   : 1X SS Project修改
                 为了解决PCLINT告警，把stLogCallInfoMsg修改为指针类型
*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_INFO_STRU  *pstLogCallInfoMsg;

    pstLogCallInfoMsg = (TAF_XCALL_MNTN_LOG_CALL_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                    sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    if (VOS_NULL_PTR == pstLogCallInfoMsg)
    {
        return;
    }

    PS_MEM_SET(pstLogCallInfoMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    /* 消息封装 */
    pstLogCallInfoMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulReceiverPid       = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulLength            = sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLogCallInfoMsg->enMsgId             = ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND;

    PS_MEM_CPY(pstLogCallInfoMsg->astCallEntity,
               TAF_XCALL_GetCtxAddr()->astCallEntity,
               TAF_XCALL_CALL_ENTITY_MAX_NUM * sizeof(TAF_XCALL_CALL_ENTITY_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(pstLogCallInfoMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstLogCallInfoMsg);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogSupsCmdMgmt
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU                   stLogSupsCmdMgmt;

    PS_MEM_SET(&stLogSupsCmdMgmt, 0x00, sizeof(stLogSupsCmdMgmt));

    /* 消息封装 */
    stLogSupsCmdMgmt.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulSenderPid         = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulReceiverPid       = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulLength            = sizeof(stLogSupsCmdMgmt) - VOS_MSG_HEAD_LENGTH;

    stLogSupsCmdMgmt.enMsgId             = ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT;

    PS_MEM_CPY(&(stLogSupsCmdMgmt.stSupsCmdMgmt),
               TAF_XCALL_GetSupsCmdMgmt(),
               sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogSupsCmdMgmt);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogEmcCallRedialPeriod
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU              stLogEmcCallRedialPeriod;

    PS_MEM_SET(&stLogEmcCallRedialPeriod, 0x00, sizeof(stLogEmcCallRedialPeriod));

    /* 消息封装 */
    stLogEmcCallRedialPeriod.ulSenderCpuId                  = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulSenderPid                    = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulReceiverCpuId                = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulReceiverPid                  = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulLength                       = sizeof(TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogEmcCallRedialPeriod.enMsgId                        = ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD;
    stLogEmcCallRedialPeriod.ulEmcRedialPeriod              = TAF_XCALL_GetConfigInfo()->ulEmcRedialPeriod;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogEmcCallRedialPeriod);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval
 功能描述  : 勾TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU                   stLogMntn;

    PS_MEM_SET(&stLogMntn, 0x00, sizeof(stLogMntn));

    /* 消息封装 */
    stLogMntn.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stLogMntn.ulSenderPid       = WUEPS_PID_TAF;
    stLogMntn.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stLogMntn.ulReceiverPid     = WUEPS_PID_TAF;
    stLogMntn.ulLength          = sizeof(TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMntn.enMsgId           = ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL;
    stLogMntn.ulStartAndStopContDtmfInterval = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMntn);

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogTimeStampValidation
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogTimeStampValidation(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstMsgTimeZone,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastTimeZone,
    VOS_UINT64                          ullStdSysTimeInterval,
    VOS_UINT64                          ullStdLastTimeInterval,
    VOS_UINT64                          ullStdMsgTimeInterval
)
{
    TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU           stLogLogTimeStampValidation;

    PS_MEM_SET(&stLogLogTimeStampValidation, 0x00, sizeof(TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU));

    /* 消息封装 */
    stLogLogTimeStampValidation.ulSenderCpuId               = VOS_LOCAL_CPUID;
    stLogLogTimeStampValidation.ulSenderPid                 = WUEPS_PID_TAF;
    stLogLogTimeStampValidation.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    stLogLogTimeStampValidation.ulReceiverPid               = WUEPS_PID_TAF;
    stLogLogTimeStampValidation.ulLength                    = sizeof(TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogLogTimeStampValidation.enMsgId                     = ID_TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION;

    stLogLogTimeStampValidation.ullStdLastTimeInterval      = ullStdLastTimeInterval;
    stLogLogTimeStampValidation.ullStdSysTimeInterval       = ullStdSysTimeInterval;
    stLogLogTimeStampValidation.ullStdMsgTimeInterval       = ullStdMsgTimeInterval;

    PS_MEM_CPY(&(stLogLogTimeStampValidation.stLastTimeZone), pstLastTimeZone, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));
    PS_MEM_CPY(&(stLogLogTimeStampValidation.stMsgTimeZone), pstMsgTimeZone, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogLogTimeStampValidation);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncPubKeyAndVerInfo
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_INFO消息
 输入参数  : VOS_UINT8                           ucVerNum,
             VOS_UINT8                          *pucPubKey
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncPubKeyAndVerInfo(
    VOS_UINT8                           ucVerNum,
    VOS_UINT8                          *pucPubKey
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU        stLogVoiceEncPubKeyAndVerInfo;

    PS_MEM_SET(&stLogVoiceEncPubKeyAndVerInfo, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU));

    /* 消息封装 */
    stLogVoiceEncPubKeyAndVerInfo.ulSenderCpuId             = VOS_LOCAL_CPUID;
    stLogVoiceEncPubKeyAndVerInfo.ulSenderPid               = WUEPS_PID_TAF;
    stLogVoiceEncPubKeyAndVerInfo.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    stLogVoiceEncPubKeyAndVerInfo.ulReceiverPid             = WUEPS_PID_TAF;
    stLogVoiceEncPubKeyAndVerInfo.ulLength                  = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogVoiceEncPubKeyAndVerInfo.enMsgId                   = ID_TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_INFO;
    stLogVoiceEncPubKeyAndVerInfo.ucVerNum                  = ucVerNum;

    PS_MEM_CPY(stLogVoiceEncPubKeyAndVerInfo.aucPubKey, pucPubKey, sizeof(VOS_UINT8) * TAF_XCALL_MNTN_LOG_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogVoiceEncPubKeyAndVerInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncryptCapCfgPara
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_INFO消息
 输入参数  : VOS_UINT8                           ucEccSrvCap,
             VOS_UINT8                           ucEccSrvStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptCapCfgPara(
    VOS_UINT8                           ucEccSrvCap,
    VOS_UINT8                           ucEccSrvStatus
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU           stLogVoiceEncryptCapCfgPara;

    PS_MEM_SET(&stLogVoiceEncryptCapCfgPara, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU));

    /* 消息封装 */
    stLogVoiceEncryptCapCfgPara.ulSenderCpuId               = VOS_LOCAL_CPUID;
    stLogVoiceEncryptCapCfgPara.ulSenderPid                 = WUEPS_PID_TAF;
    stLogVoiceEncryptCapCfgPara.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    stLogVoiceEncryptCapCfgPara.ulReceiverPid               = WUEPS_PID_TAF;
    stLogVoiceEncryptCapCfgPara.ulLength                    = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogVoiceEncryptCapCfgPara.enMsgId                     = ID_TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_INFO;
    stLogVoiceEncryptCapCfgPara.ucEccSrvCap                 = ucEccSrvCap;
    stLogVoiceEncryptCapCfgPara.ucEccSrvStatus              = ucEccSrvStatus;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogVoiceEncryptCapCfgPara);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncryptLastInfoEraseTime
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME消息
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastInfoEraseTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU   stLogLastInfoEraseTime;

    PS_MEM_SET(&stLogLastInfoEraseTime, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU));

    /* 消息封装 */
    stLogLastInfoEraseTime.ulSenderCpuId                    = VOS_LOCAL_CPUID;
    stLogLastInfoEraseTime.ulSenderPid                      = WUEPS_PID_TAF;
    stLogLastInfoEraseTime.ulReceiverCpuId                  = VOS_LOCAL_CPUID;
    stLogLastInfoEraseTime.ulReceiverPid                    = WUEPS_PID_TAF;
    stLogLastInfoEraseTime.ulLength                         = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogLastInfoEraseTime.enMsgId                          = ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME;

    stLogLastInfoEraseTime.usYear                           = pstTimeZoneInfo->usYear;
    stLogLastInfoEraseTime.usMonth                          = pstTimeZoneInfo->usMonth;
    stLogLastInfoEraseTime.usDay                            = pstTimeZoneInfo->usDay;
    stLogLastInfoEraseTime.usHour                           = pstTimeZoneInfo->usHour;
    stLogLastInfoEraseTime.usMinute                         = pstTimeZoneInfo->usMinute;
    stLogLastInfoEraseTime.usSecond                         = pstTimeZoneInfo->usSecond;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogLastInfoEraseTime);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncryptLastPassworResetTime
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME消息
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastPassworResetTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU   stLogLastPasswdResetTime;

    PS_MEM_SET(&stLogLastPasswdResetTime, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU));

    /* 消息封装 */
    stLogLastPasswdResetTime.ulSenderCpuId                  = VOS_LOCAL_CPUID;
    stLogLastPasswdResetTime.ulSenderPid                    = WUEPS_PID_TAF;
    stLogLastPasswdResetTime.ulReceiverCpuId                = VOS_LOCAL_CPUID;
    stLogLastPasswdResetTime.ulReceiverPid                  = WUEPS_PID_TAF;
    stLogLastPasswdResetTime.ulLength                       = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogLastPasswdResetTime.enMsgId                        = ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME;

    stLogLastPasswdResetTime.usYear                         = pstTimeZoneInfo->usYear;
    stLogLastPasswdResetTime.usMonth                        = pstTimeZoneInfo->usMonth;
    stLogLastPasswdResetTime.usDay                          = pstTimeZoneInfo->usDay;
    stLogLastPasswdResetTime.usHour                         = pstTimeZoneInfo->usHour;
    stLogLastPasswdResetTime.usMinute                       = pstTimeZoneInfo->usMinute;
    stLogLastPasswdResetTime.usSecond                       = pstTimeZoneInfo->usSecond;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogLastPasswdResetTime);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncryptTimerCfgInfo
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_DELAY_ENCVOICE_REQ_TIMER_LEN消息
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptTimerCfgInfo(
    VOS_UINT16                                              usDelayEncVoiceReqTimerLen,
    VOS_UINT16                                              usRemoteCtrlAnswerTimerLen
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU         stLogDelayEncVoiceReqTimerLen;

    PS_MEM_SET(&stLogDelayEncVoiceReqTimerLen, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU));

    /* 消息封装 */
    stLogDelayEncVoiceReqTimerLen.ulSenderCpuId                 = VOS_LOCAL_CPUID;
    stLogDelayEncVoiceReqTimerLen.ulSenderPid                   = WUEPS_PID_TAF;
    stLogDelayEncVoiceReqTimerLen.ulReceiverCpuId               = VOS_LOCAL_CPUID;
    stLogDelayEncVoiceReqTimerLen.ulReceiverPid                 = WUEPS_PID_TAF;
    stLogDelayEncVoiceReqTimerLen.ulLength                      = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogDelayEncVoiceReqTimerLen.enMsgId                       = ID_TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO;

    stLogDelayEncVoiceReqTimerLen.usDelayEncVoiceReqTimerlen    = usDelayEncVoiceReqTimerLen;
    stLogDelayEncVoiceReqTimerLen.usRemoteCtrlAnswerTimerLen    = usRemoteCtrlAnswerTimerLen;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogDelayEncVoiceReqTimerLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogMoKmcMsgKeyReq
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ消息
 输入参数  : TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMoKeyReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMoKeyReq
)
{
    TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU              stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ;

    PS_MEM_CPY(&(stLogMsg.stMoKeyReq), pstMoKeyReq, sizeof(TAF_XCALL_KMC_MSG_KEY_REQ_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogMoKmcMsgKeyRsp
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP消息
 输入参数  : TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMoKeyRsp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMoKeyRsp
)
{
    TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU              stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stMoKeyRsp), pstMoKeyRsp, sizeof(TAF_XCALL_KMC_MSG_KEY_RSP_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgMtEncryptInd
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND消息
 输入参数  : TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU                   *pstMtEncryptInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgMtEncryptInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU                  *pstMtEncryptInd
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU          stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stMtEncryptInd), pstMtEncryptInd, sizeof(TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogMtKmcMsgKeyReq
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ消息
 输入参数  : TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMoKeyReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMtKeyReq
)
{
    TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU              stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ;

    PS_MEM_CPY(&(stLogMsg.stMtKeyReq), pstMtKeyReq, sizeof(TAF_XCALL_KMC_MSG_KEY_REQ_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogMtKmcMsgKeyRsp
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP消息
 输入参数  : TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMoKeyRsp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMtKeyRsp
)
{
    TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU              stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stMtKeyRsp), pstMtKeyRsp, sizeof(TAF_XCALL_KMC_MSG_KEY_RSP_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgErrInd
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND消息
 输入参数  : TAF_XCALL_KMC_MSG_ERR_IND_STRU                         *pstErrInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgErrInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ERR_IND_STRU                         *pstErrInd
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU                 stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stErrInd), pstErrInd, sizeof(TAF_XCALL_KMC_MSG_ERR_IND_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateInd
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND消息
 输入参数  : TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU               *pstPubKeyUpdateInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU              *pstPubKeyUpdateInd
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU      stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stPubKeyUpdateInd), pstPubKeyUpdateInd, sizeof(TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateRsp
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP消息
 输入参数  : TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU               *pstPubKeyUpdateRsp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateRsp(
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU              *pstPubKeyUpdateRsp
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU      stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP;

    PS_MEM_CPY(&(stLogMsg.stPubKeyUpdateRsp), pstPubKeyUpdateRsp, sizeof(TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateAck
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK消息
 输入参数  : TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU               *pstPubKeyUpdateAck
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateAck(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU              *pstPubKeyUpdateAck
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU      stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stPubKeyUpdateAck), pstPubKeyUpdateAck, sizeof(TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdInd
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND消息
 输入参数  : TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU               *pstRemoteCtrlInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU             *pstRemoteCtrlInd
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU     stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND;
    stLogMsg.enRslt                     = enRslt;

    PS_MEM_CPY(&(stLogMsg.stRemoteCtrlInd), pstRemoteCtrlInd, sizeof(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdRsp
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP消息
 输入参数  : TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_REQ_STRU               *pstRemoteCtrlRsp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdRsp(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU             *pstRemoteCtrlRsp
)
{
    TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU     stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP;

    PS_MEM_CPY(&(stLogMsg.stRemoteCtrlRsp), pstRemoteCtrlRsp, sizeof(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO消息
 输入参数  : TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType
             TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEventType,
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enState
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO;
    stLogMsg.enStateMachine             = TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL;
    stLogMsg.enEventType                = enEventType;
    stLogMsg.enState                    = enState;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO消息
 输入参数  : TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType
             TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType,
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enState
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU  stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO;
    stLogMsg.enStateMachine             = TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE;
    stLogMsg.enEventType                = enEventType;
    stLogMsg.enState                    = enState;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogVoiceEncryptState
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO消息
 输入参数  : TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType
             TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptState(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType,
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enState
)
{
    TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU   stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO;
    stLogMsg.enStateMachine             = TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC;
    stLogMsg.enEventType                = enEventType;
    stLogMsg.enState                    = enState;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogCipherText
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO消息
 输入参数  : VOS_UINT8                          *pucMeid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogCipherText(
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstCipherInfo,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum
)
{
    TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU                 stLogMsg;

    PS_MEM_SET(&stLogMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU));

    /* 消息封装 */
    stLogMsg.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stLogMsg.ulSenderPid                = WUEPS_PID_TAF;
    stLogMsg.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stLogMsg.ulReceiverPid              = WUEPS_PID_TAF;
    stLogMsg.ulLength                   = sizeof(TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMsg.enMsgId                    = ID_TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO;
    stLogMsg.ulEsn                      = TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn;
    PS_MEM_CPY(stLogMsg.aucImsi, TAF_SDC_GetCsimImsi(), sizeof(VOS_UINT8) * TAF_SDC_MAX_IMSI_LEN);
    PS_MEM_CPY(stLogMsg.aucMeId, TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, sizeof(VOS_UINT8) * TAF_XCALL_MNTN_LOG_MEID_LEN);
    PS_MEM_CPY(&(stLogMsg.stCalledNum), pstCalledNum, sizeof(TAF_ECC_CALL_BCD_NUM_STRU));
    PS_MEM_CPY(&(stLogMsg.stPlainTextInfo), pstCipherInfo, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcDecMsg
 功能描述  : log解码后的KMC消息
 输入参数  : pstKmcMsg -- 解码后的KMC消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : y00245242
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcDecMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    switch (pstKmcMsg->enSmsType)
    {
        case TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP:
            TAF_XCALL_MNTN_LogMoKmcMsgKeyRsp(pstKmcMsg->enRslt, &(pstKmcMsg->u.stKeyRsp));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND:
            TAF_XCALL_MNTN_LogKmcMsgMtEncryptInd(pstKmcMsg->enRslt, &(pstKmcMsg->u.stMtEncryptInd));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP:
            TAF_XCALL_MNTN_LogMtKmcMsgKeyRsp(pstKmcMsg->enRslt, &(pstKmcMsg->u.stKeyRsp));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_ERR_IND:
            TAF_XCALL_MNTN_LogKmcMsgErrInd(pstKmcMsg->enRslt, &(pstKmcMsg->u.stErrInd));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND:
            TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateInd(pstKmcMsg->enRslt, &(pstKmcMsg->u.stPubKeyUpdateInd));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK:
            TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateAck(pstKmcMsg->enRslt, &(pstKmcMsg->u.stPubKeyUpdateAck));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND:
            TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdInd(pstKmcMsg->enRslt, &(pstKmcMsg->u.stRemoteCtrlInd));

            break;

        default:
            /* 类型错误 */
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_MNTN_LogKmcDecMsg():Error EnSmsType Unknown!");

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogKmcEncMsg
 功能描述  : log编码前的KMC消息
 输入参数  : pstKmcMsg -- 编码前的KMC消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogKmcEncMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    switch (pstKmcMsg->enSmsType)
    {
        case TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ:
            TAF_XCALL_MNTN_LogMoKmcMsgKeyReq(&(pstKmcMsg->u.stKeyReq));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ:
            TAF_XCALL_MNTN_LogMtKmcMsgKeyReq(&(pstKmcMsg->u.stKeyReq));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP:
            TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateRsp(&(pstKmcMsg->u.stPubKeyUpdateRsp));

            break;

        case TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP:
            TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdRsp(&(pstKmcMsg->u.stRemoteCtrlRsp));

            break;

        default:
            /* 类型错误 */
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_MNTN_LogKmcEncMsg():Error EnSmsType Unknown!");

            break;
    }

    return;
}
#endif

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




