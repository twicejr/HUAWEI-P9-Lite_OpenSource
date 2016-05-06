/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccComFunc.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月15日
  最近修改   :
  功能描述   : XCC模块公用函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "CnasXccInstanceMgmt.h"
#include  "CnasXccSndCas.h"
#include  "xcc_aps_pif.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CAS_TAF_EST_CAUSE_CODE_MAP_STRU          g_astCasTafEstCauseMapTbl[] =
{
    { CAS_CNAS_1X_EST_RSLT_SUCCESS,             TAF_XCC_CAUSE_SUCCESS},
    { CAS_CNAS_1X_EST_RSLT_NO_SERVICE,          TAF_XCC_CAUSE_NO_SERVICE},
    { CAS_CNAS_1X_EST_RSLT_MAX_ACCESS_PROBES,   TAF_XCC_CAUSE_MAX_ACCESS_PROBES},
    { CAS_CNAS_1X_EST_RSLT_REORDER ,            TAF_XCC_CAUSE_REORDER},
    { CAS_CNAS_1X_EST_RSLT_INTERCEPT,           TAF_XCC_CAUSE_INTERCEPT},
    { CAS_CNAS_1X_EST_RSLT_ACCESS_DENYIED,      TAF_XCC_CAUSE_ACCESS_DENYIED},
    { CAS_CNAS_1X_EST_RSLT_LOCK,                TAF_XCC_CAUSE_LOCK},
    { CAS_CNAS_1X_EST_RSLT_ACCT_BLOCK,          TAF_XCC_CAUSE_ACCT_BLOCK},
    { CAS_CNAS_1X_EST_RSLT_NDSS,                TAF_XCC_CAUSE_NDSS},
    { CAS_CNAS_1X_EST_RSLT_REDIRECTION,         TAF_XCC_CAUSE_REDIRECTION},
    { CAS_CNAS_1X_EST_RSLT_NOT_ACCEPT_BY_BS,    TAF_XCC_CAUSE_NOT_ACCEPT_BY_BS},
    { CAS_CNAS_1x_EST_RSLT_ACCESS_IN_PROGRESS,  TAF_XCC_CAUSE_ACCESS_IN_PROGRESS},
    { CAS_CNAS_1x_EST_RSLT_ACCESS_FAIL,         TAF_XCC_CAUSE_ACCESS_FAIL},
    { CAS_CNAS_1X_EST_RSLT_ABORT,               TAF_XCC_CAUSE_ABORT},
    { CAS_CNAS_1X_EST_RSLT_RETRY_FAIL,          TAF_XCC_CAUSE_RETRY_FAIL},
    { CAS_CNAS_1X_EST_RSLT_NO_RF,               TAF_XCC_CAUSE_NO_RF},
    { CAS_CNAS_1X_EST_RSLT_SIGNAL_FADE_IN_ACH,  TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH},
    { CAS_CNAS_1X_EST_RSLT_SIGNAL_FADE_IN_TCH,  TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH},
    { CAS_CNAS_1X_EST_RSLT_BUTT,                TAF_XCC_CAUSE_BUTT}
};

CAS_TAF_TERMINATE_CAUSE_CODE_MAP_STRU   g_astCasTafTerminateCauseMapTbl[]   =
{
    {CAS_CNAS_1X_TERMINATE_REASON_MS_END,                    TAF_XCC_CAUSE_MS_NORMAL_RELEASE},
    {CAS_CNAS_1X_TERMINATE_REASON_RELEASE_TIME_OUT,          TAF_XCC_CAUSE_RELEASE_TIME_OUT},
    {CAS_CNAS_1X_TERMINATE_REASON_REDIRECTION,               TAF_XCC_CAUSE_REDIRECTION},
    {CAS_CNAS_1X_TERMINATE_REASON_LOCK,                      TAF_XCC_CAUSE_LOCK},
    {CAS_CNAS_1X_TERMINATE_REASON_SO_REJ,                    TAF_XCC_CAUSE_SO_REJ},

    {CAS_CNAS_1X_TERMINATE_REASON_NW_NORMAL_END,             TAF_XCC_CAUSE_NW_NORMAL_RELEASE},

    {CAS_CNAS_1X_TERMINATE_REASON_CHANNEL_ASSIGN_TIMEOUT,    TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT},
    {CAS_CNAS_1X_TERMINATE_REASON_SIGNAL_FADE_IN_ACH,        TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH},
    {CAS_CNAS_1X_TERMINATE_REASON_SIGNAL_FADE_IN_TCH,        TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH},
    {CAS_CNAS_1X_TERMINATE_REASON_BUTT,                      TAF_XCC_CAUSE_BUTT}
};


VOS_UINT8 g_aucXccDtmfKeyMapTbl[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#'};

XCC_MMA_1X_CALL_STATE_MAP_STRU          g_astXccMma1XCallStateMapTbl[]      =
{
    {CNAS_CCB_1X_CALL_STATE_IDLE,                    XCC_MMA_1X_CALL_STATE_IDLE},
    {CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,          XCC_MMA_1X_CALL_STATE_INCOMMING_CALL},
    {CNAS_CCB_1X_CALL_STATE_ORIG_CALL,               XCC_MMA_1X_CALL_STATE_ORIG_CALL},
    {CNAS_CCB_1X_CALL_STATE_CONVERSATION,            XCC_MMA_1X_CALL_STATE_CONVERSATION},
    {CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,         XCC_MMA_1X_CALL_STATE_INCOMMING_CALL},
    {CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ORDER,          XCC_MMA_1X_CALL_STATE_IDLE},
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsConcurrentSupported
 功能描述  : 并发业务是否被支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  支持
             VOS_FALSE --  不支持

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月18日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsConcurrentSupported(VOS_VOID)
{
    VOS_UINT8                           ucPRevInUse;

    ucPRevInUse = CNAS_CCB_GetPRevInUse();

    if ((VOS_TRUE       == CNAS_CCB_GetConcurrentSupportedFlag())
     && (P_REV_IN_USE_7 <=  ucPRevInUse))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_StartTimer
 功能描述  : XCC模块封装的启动定时器函数
 输入参数  : VOS_UINT8                           ucConnectId,
             CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
             VOS_UINT32                          ulTimerLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_StartTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    /* 当前XCC的定时器，ulParam取值为CONNEC ID，ulTimerPrecision均是
       VOS_TIMER_NO_PRECISION，后续如果需要根据TimerId来做不同设定时，再
       增加相关的封装函数 */
    NAS_MEM_SET_S(&stTimerInfo, sizeof(CNAS_TIMER_INFO_STRU), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = ucConnectId;
    stTimerInfo.ulTimerPrecision        = (VOS_UINT32)VOS_TIMER_PRECISION_5;

    CNAS_StartTimer(UEPS_PID_XCC, &stTimerInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_StopTimer
 功能描述  : XCC模块封装的停止定时器函数
 输入参数  : VOS_UINT8                           ucConnectId,
             CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_StopTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    /* XCC模块不要ulParam，因此在调用CNAS_StopTimer的时候，ulParam值为ucConnectId */
    CNAS_StopTimer(UEPS_PID_XCC, enTimerId, (VOS_UINT32)ucConnectId);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RestartTimer
 功能描述  : XCC模块封装的停止定时器函数
 输入参数  : VOS_UINT8                           ucConnectId,
             CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_RestartTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    /* 当前XCC的定时器，ulParam取值为CONNEC ID，ulTimerPrecision均是
       VOS_TIMER_NO_PRECISION，后续如果需要根据TimerId来做不同设定时，再
       增加相关的封装函数 */
    NAS_MEM_SET_S(&stTimerInfo, sizeof(CNAS_TIMER_INFO_STRU), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = (VOS_UINT32)ucConnectId;
    stTimerInfo.ulTimerPrecision        = VOS_TIMER_NO_PRECISION;

    CNAS_RestartTimer(UEPS_PID_XCC, &stTimerInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertSoToServiceType
 功能描述  : SO转成相应的服务类型
 输入参数  : enSo           : service option
 输出参数  : penServiceType : service type
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                      *penServiceType
)
{
    switch (enSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            *penServiceType = CNAS_XCC_SERVICE_TYPE_VOICE_CALL;
            break;

        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            *penServiceType = CNAS_XCC_SERVICE_TYPE_DATA_CALL;
            break;

        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            *penServiceType = CNAS_XCC_SERVICE_TYPE_SMS;
            break;

        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
            *penServiceType = CNAS_XCC_SERVICE_TYPE_LOOPBACK;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            *penServiceType = CNAS_XCC_SERVICE_TYPE_AGPS_CALL;
            break;

        default:
            *penServiceType = CNAS_XCC_SERVICE_TYPE_LOOPBACK;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertSoToCasSessionType
 功能描述  : SO转成Session类型
 输入参数  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
             enSo : Service Option
 输出参数  : enCasSessionType: 发送给CAS的SessionType
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID CNAS_XCC_ConvertSoToCasSessionType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                   *penCasSessionType
)
{
    switch (enSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_CS_CALL;
            break;

        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_PS_CALL;
            break;

        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_SMS;
            break;

        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
        case CAS_CNAS_1X_SO_32_TDSO:
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_CS_CALL;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_AGPS;
            break;

        default:
            /* 异常情况返回CS CALL SessionType */
            *penCasSessionType = CNAS_CAS_1X_SESSION_TYPE_CS_CALL;
            break;
    }

    return;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertSoToMtcSessionType
 功能描述  : SO转成MTC模块的Session类型
 输入参数  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
             enSo : Service Option
 输出参数  : enMtcSessionType: 发送给MTC的SessionType
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID CNAS_XCC_ConvertSoToMtcSessionType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    MTC_SESSION_TYPE_ENUM_UINT8                            *penMtcSessionType
)
{
    switch (enSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            *penMtcSessionType = MTC_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            *penMtcSessionType = MTC_SESSION_TYPE_1X_PS_CALL;
            break;

        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            *penMtcSessionType = MTC_SESSION_TYPE_CS_MO_SMS;
            break;

        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
        case CAS_CNAS_1X_SO_32_TDSO:
            *penMtcSessionType = MTC_SESSION_TYPE_CS_LOOP_BACK;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            *penMtcSessionType = MTC_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        default:
            *penMtcSessionType = MTC_SESSION_TYPE_CS_LOOP_BACK;
            break;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertTerminateReasonToTafCause
 功能描述  : 将与接入层的terminate原因转化成taf层
 输入参数  : enTerminateReason - CAS_CNAS_1X_TERMINATE_REASON_ENUM_UINT8
             penCause          - TAF_XCC_CAUSE_ENUM_UINT32
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ConvertTerminateReasonToTafCause(
    CAS_CNAS_1X_TERMINATE_REASON_ENUM_UINT8                 enCasCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astCasTafTerminateCauseMapTbl)/sizeof(CAS_TAF_TERMINATE_CAUSE_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astCasTafTerminateCauseMapTbl[ulCnt].enCasCause == enCasCause)
        {
            return g_astCasTafTerminateCauseMapTbl[ulCnt].enXccCause;
        }
    }

    return TAF_XCC_CAUSE_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_Convert1XcallState
 功能描述  : CNAS_CCB_CDMA_1X_CALL_STATE
 输入参数  : enCcb1XCallState
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月20日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_Convert1XcallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8   enCcb1XCallState
)
{

    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astXccMma1XCallStateMapTbl)/sizeof(XCC_MMA_1X_CALL_STATE_MAP_STRU)); ulCnt++)
    {
        if (g_astXccMma1XCallStateMapTbl[ulCnt].enCcbCallState == enCcb1XCallState)
        {
            return g_astXccMma1XCallStateMapTbl[ulCnt].enXccMmaCallState;
        }
    }

    return XCC_MMA_1X_CALL_STATE_IDLE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertEstReasonToTafCause
 功能描述  : 将与接入层的EST原因转化成taf层
 输入参数  : enCasCause - CAS_CNAS_1X_EST_RSLT_ENUM_UINT8

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ConvertEstReasonToTafCause(
    CAS_CNAS_1X_EST_RSLT_ENUM_UINT8                 enCasCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astCasTafEstCauseMapTbl)/sizeof(CAS_TAF_EST_CAUSE_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astCasTafEstCauseMapTbl[ulCnt].enCasCause == enCasCause)
        {
            return g_astCasTafEstCauseMapTbl[ulCnt].enXccCause;
        }
    }

    return TAF_XCC_CAUSE_UNKNOWN;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertTafHangupReasonToCas
 功能描述  : taf hangup原因值转换成CAS
 输入参数  : tafEndReason - TAF_XCC_END_REASON_ENUM_UINT8
             penReason    - CAS_CNAS_1X_REL_REASON_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ConvertTafHangupReasonToCas(
    TAF_XCC_END_REASON_ENUM_UINT8       tafEndReason,
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8  *penReason
)
{
    switch (tafEndReason)
    {
        case TAF_XCC_END_REASON_NORMAL_RELEASE:
            *penReason = CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE;
            break;

        case TAF_XCC_END_REASON_POWER_DOWN_RELEASE:
            *penReason = CAS_CNAS_1X_REL_REASON_POWER_DOWN_RELEASE;
            break;

        case TAF_XCC_END_REASON_SERVICE_INACTIVE:
            *penReason = CAS_CNAS_1X_REL_REASON_SERVICE_INACTIVE;
            break;

        default:
            *penReason = CAS_CNAS_1X_REL_REASON_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetOrderSpecificMsgType
 功能描述  : 根据order消息获取具体的消息类型
 输入参数  : c_F_Orders *pstOrderMsg,
             CAS_1X_FOR_ORDER_TYPE_ENUM_UINT8 *penOrderMsgType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetOrderSpecificMsgType(
    CNAS_XCC_ORDERS_STRU                *pstOrderMsg,
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      *penOrderMsgType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSize;
    CNAS_XCC_ORDER_TO_SPECIFIC_MSG_STRU   astOrderMsg[] =
    {
        /* Order Messages are sent by the base station on the f-csch and the f-dsch.  The general PDU
           format used on the f-csch is defined in 3.7.2.3.2.7, and the general PDU format used on the
           f-dsch is defined in 3.7.3.3.2.1.  There are many specific types of Order Messages, as shown
           in Table 3.7.4-1. */
        /* order消息和具体内部消息对应关系 */
        /* ORDER , ORDQ(min) , ORDQ(max) , MsgType  */
 /* 这里只定义了，当前需要处理order消息，如果有新的order消息再添加 */
        {0x01, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_ABBREVIATED_ALERT},
        {0x02, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_BS_CHALLENGE_CONFIRMATION},
        {0x03, 0x00, 0x03, CNAS_XCC_ORDER_TYPE_MSG_ENCRYPTION_MODE},
        {0x04, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_RECORDER},
        {0x05, 0x00, 0x0F, CNAS_XCC_ORDER_TYPE_PARAMETER_UPDATE},
        {0x06, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_AUDIT},
        {0x09, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_INTERCEPT},
        {0x0A, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_MAINTENANCE},
        {0x10, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_BS_ACKNOWLEDGMENT},
        {0x11, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_PILOT_MEASUREMENT},
        {0x11, 0x01, 0xFF, CNAS_XCC_ORDER_TYPE_PERIODIC_PILOT_MEASUREMENT},
        {0x12, 0x10, 0x1F, CNAS_XCC_ORDER_TYPE_LOCK_UNTIL_PWR_CYCLED},
        {0x12, 0x20, 0x2F, CNAS_XCC_ORDER_TYPE_MAINTENANCE_REQUIRED},
        {0x12, 0xFF, 0xFF, CNAS_XCC_ORDER_TYPE_UNLOCK},
        {0x13, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_REQUEST},
        {0x14, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_RESPONSE},
        {0x15, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_RELEASE},
        {0x15, 0x02, 0x02, CNAS_XCC_ORDER_TYPE_RELEASE},
        {0x16, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_OUTER_LOOP_REPORT_REQUEST},
        {0x17, 0x00, 0x01, CNAS_XCC_ORDER_TYPE_LONG_CODE_TRANSITION},
        {0x19, 0x00, 0x0F, CNAS_XCC_ORDER_TYPE_CONTINUOUS_DTMF_TONE},
        {0x19, 0xFF, 0xFF, CNAS_XCC_ORDER_TYPE_CONTINUOUS_DTMF_TONE},
        {0x1A, 0x00, 0xFF, CNAS_XCC_ORDER_TYPE_STATUS_REQUEST},
        {0x1B, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_REGISTRATION_ACCEPTED},
        {0x1B, 0x01, 0x01, CNAS_XCC_ORDER_TYPE_REGISTRATION_REQUEST},
        {0x1B, 0x02, 0x02, CNAS_XCC_ORDER_TYPE_REGISTRATION_REJECTED},
        {0x1B, 0x04, 0x04, CNAS_XCC_ORDER_TYPE_REGISTRATION_REJECTED},
        {0x1B, 0x05, 0x05, CNAS_XCC_ORDER_TYPE_REGISTRATION_ACCEPTED},
        {0x1B, 0x07, 0x07, CNAS_XCC_ORDER_TYPE_REGISTRATION_ACCEPTED},
        {0x1D, 0x00, 0xFF, CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL},
        {0x1E, 0x00, 0xFF, CNAS_XCC_ORDER_TYPE_LOCAL_CONTROL},
        {0x1F, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_SLOTTED_MODE},
        {0x20, 0x00, 0x00, CNAS_XCC_ORDER_TYPE_RETRY},
        {0x21, 0x00, 0x01, CNAS_XCC_ORDER_TYPE_BS_REJECT}
    };

    ulSize = sizeof(astOrderMsg) / sizeof(CNAS_XCC_ORDER_TO_SPECIFIC_MSG_STRU);
    for ( ulLoop = 0; ulLoop < ulSize; ulLoop++ )
    {
        if (( astOrderMsg[ulLoop].ucOrder == pstOrderMsg->ucOrder )
        && (astOrderMsg[ulLoop].ucOrdqMin <= pstOrderMsg->ucOrdq)
        && (astOrderMsg[ulLoop].ucOrdqMax >= pstOrderMsg->ucOrdq))
        {
            *penOrderMsgType = astOrderMsg[ulLoop].enOrderMsgType;
            return VOS_OK;
        }
    }

    CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_GetOrderSpecificMsgType: Invalid Msgtype ");

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeOrderMsg
 功能描述  : 解码Order消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeOrderMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_ORDRM_STRU                *pstOrdrm
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

	/* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeOrderMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_ORDER_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.ORDRM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    NAS_MEM_SET_S(pstOrdrm, sizeof(CNAS_XCC_ORDRM_STRU), 0x00, sizeof(CNAS_XCC_ORDRM_STRU));

    pstOrdrm->ucUseTime           = stMsgFDsch.u.ORDRM->USE_TIME;
    pstOrdrm->ucActionTime        = stMsgFDsch.u.ORDRM->ACTION_TIME;
    pstOrdrm->ucConRefIncl        = stMsgFDsch.u.ORDRM->CON_REF_INCL;
    pstOrdrm->ucConRefInclPresent = stMsgFDsch.u.ORDRM->CON_REF_INCL_Present;
    pstOrdrm->ucConRef            = stMsgFDsch.u.ORDRM->CON_REF;
    pstOrdrm->ucConRefPresent     = stMsgFDsch.u.ORDRM->CON_REF_Present;

    /* ORDER内容，建议不要用PS_MEM_CPY。字节对齐问题 */
    //pstOrdrm->stOrder.ulOrderDesc = stMsgFDsch.u.ORDRM->order.ORDER_DESC;
    //pstOrdrm->stOrder.ulNNNN      = stMsgFDsch.u.ORDRM->order.NNNN;
    pstOrdrm->stOrder.ucOrder     = stMsgFDsch.u.ORDRM->order.ORDER;
    pstOrdrm->stOrder.ucOrdq      = stMsgFDsch.u.ORDRM->order.parameters.u.p_R_Generic_Order->ORDQ;

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeServiceOptionCtrlMsg
 功能描述  : 解码Order消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeServiceOptionCtrlMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    VOS_UINT8                          *pucSoCtrlMsgData,
    VOS_UINT8                          *pucConRef
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeServiceOptionCtrlMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.SOCM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    /* Table 2.2.2.2-2   Service Option Control Message
                Type-Specific Fields
    Field Length                        (bits)
    RATE_REDUC                          3
    RESERVED                            3
    MOBILE_TO_MOBILE                    1
    INIT_CODEC                          1
    从协议看，域内容的长度固定为1字节
    */
    *pucSoCtrlMsgData   = *(stMsgFDsch.u.SOCM->Type_specific_fields.value);

    *pucConRef          = stMsgFDsch.u.SOCM->CON_REF;

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsDisp
 功能描述  : 填充解码消息中的information records中DISPLAY字段
 输入参数  : c_InfoRec_Display                  *pstInfoRecDsip
 输出参数  : CNAS_XCC_INFO_RECS_DISP_STRU       *pstXccInfoRecsDsip
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsDisp(
    c_InfoRec_Display                  *pstInfoRecDsip,
    CNAS_XCC_INFO_RECS_DISP_STRU       *pstXccInfoRecsDsip
)
{
    /* 若解码后的display指针为空，或者字符串为空 */
    if (VOS_NULL_PTR == pstInfoRecDsip)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecDsip->CHARi.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecDsip->CHARi.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsDsip->ucDigitNum
        = ((VOS_UINT8)pstInfoRecDsip->CHARi.items < CNAS_XCC_MAX_DISPALY_CHARI_OCTET_NUM)
        ? ((VOS_UINT8)pstInfoRecDsip->CHARi.items) : (CNAS_XCC_MAX_DISPALY_CHARI_OCTET_NUM);
    NAS_MEM_CPY_S(pstXccInfoRecsDsip->aucDigit,
                  CNAS_XCC_MAX_DISPALY_CHARI_OCTET_NUM,
                  pstInfoRecDsip->CHARi.data,
                  pstXccInfoRecsDsip->ucDigitNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsCalledNum
 功能描述  : 填充解码消息中的information records中called party number字段
 输入参数  : c_InfoRec_Called_Party_Number      *pstInfoRecCalledNum
 输出参数  : CNAS_XCC_INFO_RECS_CALLED_NUM_STRU *pstXccInfoRecsCalledNum
 返 回 值  : VOS_OK,VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsCalledNum(
    c_InfoRec_Called_Party_Number      *pstInfoRecCalledNum,
    CNAS_XCC_INFO_RECS_CALLED_NUM_STRU *pstXccInfoRecsCalledNum
)
{
    /* 若解码后的called number指针为空，或者字符串为空 */
    if (VOS_NULL_PTR == pstInfoRecCalledNum)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecCalledNum->CHARi.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecCalledNum->CHARi.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsCalledNum->ucNumberType = pstInfoRecCalledNum->NUMBER_TYPE;
    pstXccInfoRecsCalledNum->ucNumberPlan = pstInfoRecCalledNum->NUMBER_PLAN;
    pstXccInfoRecsCalledNum->ucDigitNum
        = ((VOS_UINT8)pstInfoRecCalledNum->CHARi.items < CNAS_XCC_MAX_CALLED_NUMBER_CHARI_OCTET_NUM)
        ? ((VOS_UINT8)pstInfoRecCalledNum->CHARi.items) : (CNAS_XCC_MAX_CALLED_NUMBER_CHARI_OCTET_NUM);
    NAS_MEM_CPY_S(pstXccInfoRecsCalledNum->aucDigit,
                  CNAS_XCC_MAX_CALLED_NUMBER_CHARI_OCTET_NUM,
                  pstInfoRecCalledNum->CHARi.data,
                  pstXccInfoRecsCalledNum->ucDigitNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsCallingNum
 功能描述  : c_InfoRec_Calling_Party_Number      *pstInfoRecCallingNum
 输入参数  : c_R_InformationRecords              stInformationRecords, 解码后的info recs
 输出参数  : CNAS_XCC_INFO_RECS_CALLING_NUM_STRU *pstXccInfoRecsCallingNum
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsCallingNum(
    c_InfoRec_Calling_Party_Number                         *pstInfoRecCallingNum,
    CNAS_XCC_INFO_RECS_CALLING_NUM_STRU                    *pstXccInfoRecsCallingNum
)
{
    /* 若解码后的calling number指针为空，或者字符串为空 */
    if (VOS_NULL_PTR == pstInfoRecCallingNum)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecCallingNum->CHARi.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecCallingNum->CHARi.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsCallingNum->ucNumberType = pstInfoRecCallingNum->NUMBER_TYPE;
    pstXccInfoRecsCallingNum->ucNumberPlan = pstInfoRecCallingNum->NUMBER_PLAN;
    pstXccInfoRecsCallingNum->ucPi         = pstInfoRecCallingNum->PI;
    pstXccInfoRecsCallingNum->ucSi         = pstInfoRecCallingNum->SI;
    pstXccInfoRecsCallingNum->ucDigitNum
        = ((VOS_UINT8)pstInfoRecCallingNum->CHARi.items < CNAS_XCC_MAX_CALLING_NUMBER_CHARI_OCTET_NUM)
        ? ((VOS_UINT8)pstInfoRecCallingNum->CHARi.items) : CNAS_XCC_MAX_CALLING_NUMBER_CHARI_OCTET_NUM;
    NAS_MEM_CPY_S(pstXccInfoRecsCallingNum->aucDigit,
                  CNAS_XCC_MAX_CALLING_NUMBER_CHARI_OCTET_NUM,
                  pstInfoRecCallingNum->CHARi.data,
                  pstXccInfoRecsCallingNum->ucDigitNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsConnNum
 功能描述  : 填充解码消息中的information records中connected number字段
 输入参数  : c_InfoRec_Connected_Number         *pstInfoRecConnNum
 输出参数  : CNAS_XCC_INFO_RECS_CON_NUM_STRU    *pstXccInfoRecsConnNum
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsConnNum(
    c_InfoRec_Connected_Number         *pstInfoRecConnNum,
    CNAS_XCC_INFO_RECS_CON_NUM_STRU    *pstXccInfoRecsConnNum
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;

    /* 若解码后的connected num指针为空 */
    if (VOS_NULL_PTR == pstInfoRecConnNum)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecConnNum->data_01.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecConnNum->data_01.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsConnNum->ucNumberType = pstInfoRecConnNum->NUMBER_TYPE;
    pstXccInfoRecsConnNum->ucNumberPlan = pstInfoRecConnNum->NUMBER_PLAN;
    pstXccInfoRecsConnNum->ucPi         = pstInfoRecConnNum->PI;
    pstXccInfoRecsConnNum->ucSi         = pstInfoRecConnNum->SI;


    /* 解码后的information records中connected number data_01中数据字段为指针的指针(c_InfoRec_Connected_Number_data_01),对应数据为data[ulLoop][0]*/
    for (ucLoop = 0, ucFillLoop = 0;
          ( (ucLoop < pstInfoRecConnNum->data_01.items)
          &&(ucFillLoop < CNAS_XCC_MAX_CONNECTED_NUMBER_CHARI_OCTET_NUM));
         ucLoop++)
    {
        if (VOS_NULL_PTR == pstInfoRecConnNum->data_01.data[ucLoop])
        {
            continue;
        }

        pstXccInfoRecsConnNum->aucDigit[ucFillLoop] = (pstInfoRecConnNum->data_01.data[ucLoop])->CHARi;
        ucFillLoop++;
    }

    pstXccInfoRecsConnNum->ucDigitNum = ucFillLoop;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsSignal
 功能描述  : 填充解码消息中的information records中signal字段
 输入参数  : c_InfoRec_Signal                   *pstInfoRecSignal
 输出参数  : CNAS_XCC_INFO_RECS_SIGNAL_STRU     *pstXccInfoRecsSignal
 返 回 值  : VOS_OK,VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsSignal(
    c_InfoRec_Signal                   *pstInfoRecSignal,
    CNAS_XCC_INFO_RECS_SIGNAL_STRU     *pstXccInfoRecsSignal
)
{
    /* 若解码后的signal指针为空 */
    if (VOS_NULL_PTR == pstInfoRecSignal)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsSignal->ucSignalType = pstInfoRecSignal->SIGNAL_TYPE;
    pstXccInfoRecsSignal->ucAlertPitch = pstInfoRecSignal->ALERT_PITCH;
    pstXccInfoRecsSignal->ucSignal     = pstInfoRecSignal->SIGNAL;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsRedirNum
 功能描述  : 填充解码消息中的information records中redirecting num字段
 输入参数  : c_InfoRec_Redirecting_Number       *pstInfoRecRedirNum
 输出参数  : CNAS_XCC_INFO_RECS_REDIR_NUM_STRU  *pstXccInfoRecsRedirNu
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsRedirNum(
    c_InfoRec_Redirecting_Number       *pstInfoRecRedirNum,
    CNAS_XCC_INFO_RECS_REDIR_NUM_STRU  *pstXccInfoRecsRedirNum
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;

    /* 若解码后的Redirecting number指针为空 */
    if (VOS_NULL_PTR == pstInfoRecRedirNum)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecRedirNum->data_01.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecRedirNum->data_01.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsRedirNum->ucExtensionBit1            = (VOS_UINT8)pstInfoRecRedirNum->EXTENSION_BIT_1;
    pstXccInfoRecsRedirNum->ucNumbertype               = pstInfoRecRedirNum->NUMBER_TYPE;
    pstXccInfoRecsRedirNum->ucNumberPlan               = pstInfoRecRedirNum->NUMBER_PLAN;
    pstXccInfoRecsRedirNum->ucExtensionBit2            = (VOS_UINT8)pstInfoRecRedirNum->EXTENSION_BIT_2;
    pstXccInfoRecsRedirNum->ucExtensionBit2Present     = (VOS_UINT8)pstInfoRecRedirNum->EXTENSION_BIT_2_Present;
    pstXccInfoRecsRedirNum->ucPi                       = pstInfoRecRedirNum->PI;
    pstXccInfoRecsRedirNum->ucPiPresent                = (VOS_UINT8)pstInfoRecRedirNum->PI_Present;
    pstXccInfoRecsRedirNum->ucSi                       = pstInfoRecRedirNum->SI;
    pstXccInfoRecsRedirNum->ucSiPresent                = (VOS_UINT8)pstInfoRecRedirNum->SI_Present;
    pstXccInfoRecsRedirNum->ucExtensionBit3            = (VOS_UINT8)pstInfoRecRedirNum->EXTENSION_BIT_3;
    pstXccInfoRecsRedirNum->ucExtensionBit3Present     = (VOS_UINT8)pstInfoRecRedirNum->EXTENSION_BIT_3_Present;
    pstXccInfoRecsRedirNum->ucRedirectionReason        = pstInfoRecRedirNum->REDIRECTION_REASON;
    pstXccInfoRecsRedirNum->ucRedirectionReasonPresent = (VOS_UINT8)pstInfoRecRedirNum->REDIRECTION_REASON_Present;

    /* 解码后的information records中Redirecting number data_01中数据字段为指针的指针(c_InfoRec_Redirecting_Number_data_01),对应数据为data[ulLoop][0]*/
    for (ucLoop = 0, ucFillLoop = 0;
         ((ucLoop < pstInfoRecRedirNum->data_01.items)
          && (ucFillLoop < CNAS_XCC_MAX_REDIRECTING_NUMBER_CHARI_OCTET_NUM));
         ucLoop++)
    {
        if (VOS_NULL_PTR == pstInfoRecRedirNum->data_01.data[ucLoop])
        {
            continue;
        }
        pstXccInfoRecsRedirNum->aucDigit[ucFillLoop] = (pstInfoRecRedirNum->data_01.data[ucLoop])->CHARi;
        ucFillLoop++;
    }

    pstXccInfoRecsRedirNum->ucDigitNum = ucFillLoop;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsLineCtr
 功能描述  : 填充解码消息中的information records中line ctrl字段
 输入参数  : c_InfoRec_Line_Control             *pstInfoRecLineCtr
 输出参数  : CNAS_XCC_INFO_RECS_LINE_CTR_STRU   *pstXccInfoRecsLineCtr
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsLineCtr(
    c_InfoRec_Line_Control             *pstInfoRecLineCtr,
    CNAS_XCC_INFO_RECS_LINE_CTR_STRU   *pstXccInfoRecsLineCtr
)
{
    /* 若解码后的line ctrl指针为空 */
    if (VOS_NULL_PTR == pstInfoRecLineCtr)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsLineCtr->ucPolarityIncluded       = pstInfoRecLineCtr->POLARITY_INCLUDED;
    pstXccInfoRecsLineCtr->ucToggleMode             = pstInfoRecLineCtr->TOGGLE_MODE;
    pstXccInfoRecsLineCtr->ucToggleModePresent      = pstInfoRecLineCtr->TOGGLE_MODE_Present;
    pstXccInfoRecsLineCtr->ucReversePolarity        = pstInfoRecLineCtr->REVERSE_POLARITY;
    pstXccInfoRecsLineCtr->ucReversePolarityPresent = pstInfoRecLineCtr->REVERSE_POLARITY_Present;
    pstXccInfoRecsLineCtr->ucPowerDenialTime        = pstInfoRecLineCtr->POWER_DENIAL_TIME;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsExtDisp
 功能描述  : 填充解码消息中的information records中extdisplay字段
 输入参数  : c_InfoRec_Extended_Display         *pstInfoRecExtDsip
 输出参数  : CNAS_XCC_INFO_RECS_EXTDISP_STRU    *pstXccInfoRecsExtDsip
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsExtDisp(
    c_InfoRec_Extended_Display         *pstInfoRecExtDsip,
    CNAS_XCC_INFO_RECS_EXTDISP_STRU    *pstXccInfoRecsExtDsip
)
{
    VOS_UINT8                           ucExtDispLoop;
    VOS_UINT8                           ucFillExtDispLoop;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;

    /* 若解码后的ExtDisplay指针为空 */
    if (VOS_NULL_PTR == pstInfoRecExtDsip)
    {
        return VOS_ERR;
    }

    if (0 == pstInfoRecExtDsip->data_01.items)
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstInfoRecExtDsip->data_01.data)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsExtDsip->ucExtDisplayInd  = (VOS_UINT8)pstInfoRecExtDsip->EXT_DISPLAY_IND;
    pstXccInfoRecsExtDsip->ucDispalyType    = pstInfoRecExtDsip->DISPLAY_TYPE;

    for (ucExtDispLoop = 0, ucFillExtDispLoop = 0;
         ((ucExtDispLoop < pstInfoRecExtDsip->data_01.items)
          && (ucFillExtDispLoop < CNAS_XCC_MAX_EXT_DISPLAY_DATA_NUM));
         ucExtDispLoop++)
    {
        if (VOS_NULL_PTR == pstInfoRecExtDsip->data_01.data[ucExtDispLoop])
        {
            continue;
        }

        if (VOS_NULL_PTR == (pstInfoRecExtDsip->data_01.data[ucExtDispLoop])->data_02.data)
        {
            continue;
        }

        pstXccInfoRecsExtDsip->astExtDispData[ucFillExtDispLoop].ucDispalyLen
                   = (pstInfoRecExtDsip->data_01.data[ucExtDispLoop])->DISPLAY_LEN;
        pstXccInfoRecsExtDsip->astExtDispData[ucFillExtDispLoop].ucDispalyTag
                   = (pstInfoRecExtDsip->data_01.data[ucExtDispLoop])->DISPLAY_TAG;

        for (ucLoop = 0, ucFillLoop = 0;
             ((ucLoop < (pstInfoRecExtDsip->data_01.data[ucExtDispLoop])->data_02.items)
               && (ucFillLoop < CNAS_XCC_MAX_EXTENDED_DISPLAY_CHARI_OCTET_NUM));
             ucLoop++)
        {
            if (VOS_NULL_PTR == pstInfoRecExtDsip->data_01.data[ucExtDispLoop]->data_02.data[ucLoop])
            {
                continue;
            }

            pstXccInfoRecsExtDsip->astExtDispData[ucFillExtDispLoop].aucDigit[ucFillLoop]
                       = ((pstInfoRecExtDsip->data_01.data[ucExtDispLoop])->data_02.data[ucLoop])->CHARi;

            ucFillLoop++;
        }

        pstXccInfoRecsExtDsip->astExtDispData[ucFillExtDispLoop].ucDigitNum = ucFillLoop;

        ucFillExtDispLoop++;

    }

    pstXccInfoRecsExtDsip->ucNumExtDispData = ucFillExtDispLoop;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecsMsgWaiting
 功能描述  : 填充解码消息中的information records中message waitng字段
 输入参数  : c_InfoRec_Message_Waiting              *pstInfoRecMsgWaiting
 输出参数  : CNAS_XCC_INFO_RECS_MSG_WAITING_STRU    *pstXccInfoRecsMsgWaiting
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsMsgWaiting(
    c_InfoRec_Message_Waiting              *pstInfoRecMsgWaiting,
    CNAS_XCC_INFO_RECS_MSG_WAITING_STRU    *pstXccInfoRecsMsgWaiting
)
{
    /* 若解码后的message waiting指针为空 */
    if (VOS_NULL_PTR == pstInfoRecMsgWaiting)
    {
        return VOS_ERR;
    }

    pstXccInfoRecsMsgWaiting->ucMsgCnt = pstInfoRecMsgWaiting->MSG_COUNT;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeInfoRecs
 功能描述  : 填充解码消息中的information records字段
 输入参数  : c_R_InformationRecords             *pstInformationRecords, 解码后的info recs
 输出参数  : CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs，本地平铺的info recs
 返 回 值  : VOS_ERR,VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecs(
    c_F_InformationRecords             *pstInformationRecords,
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs
)
{
    TPRESENT_c_F_InformationRecords     ulPresent;
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_ERR;

    ulPresent = pstInformationRecords->Present;
    switch (ulPresent)
    {
        /* 填充display字段 */
        case U_c_F_InformationRecords_p_InfoRec_Display:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_DISPLAY;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsDisp(pstInformationRecords->u.p_InfoRec_Display,
                                                     &(pstInfoRecs->u.stDisp));
            break;

        /* 填充called party number */
        case U_c_F_InformationRecords_p_InfoRec_Called_Party_Number:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_NUMBER;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsCalledNum(pstInformationRecords->u.p_InfoRec_Called_Party_Number,
                                                          &(pstInfoRecs->u.stCalledNum));
            break;

        /* 填充calling paryt number */
        case U_c_F_InformationRecords_p_InfoRec_Calling_Party_Number:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsCallingNum(pstInformationRecords->u.p_InfoRec_Calling_Party_Number,
                                                           &(pstInfoRecs->u.stCallingNum));
            break;

        /* 填充connected number */
        case U_c_F_InformationRecords_p_InfoRec_Connected_Number:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CONNECTED_NUMBER;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsConnNum(pstInformationRecords->u.p_InfoRec_Connected_Number,
                                                        &(pstInfoRecs->u.stConNum));
            break;

        /* 填充signal */
        case U_c_F_InformationRecords_p_InfoRec_Signal:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsSignal(pstInformationRecords->u.p_InfoRec_Signal,
                                                       &(pstInfoRecs->u.stSignal));
            break;

        /* 填充redirecting number */
        case U_c_F_InformationRecords_p_InfoRec_Redirecting_Number:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_REDIRECTING_NUMBER;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsRedirNum(pstInformationRecords->u.p_InfoRec_Redirecting_Number,
                                                         &(pstInfoRecs->u.stRedirNum));
            break;

        /* 填充line control */
        case U_c_F_InformationRecords_p_InfoRec_Line_Control:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_LINE_CONTROL;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsLineCtr(pstInformationRecords->u.p_InfoRec_Line_Control,
                                                        &(pstInfoRecs->u.stLineCtr));
            break;

        /* 填充extended display */
        case U_c_F_InformationRecords_p_InfoRec_Extended_Display:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_EXTENDED_DISPLAY;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsExtDisp(pstInformationRecords->u.p_InfoRec_Extended_Display,
                                                        &(pstInfoRecs->u.stExtDisp));
            break;

        case U_c_F_InformationRecords_p_InfoRec_Message_Waiting:
            pstInfoRecs->enInfoRecsType = CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING;
            ulRslt = CNAS_XCC_FillDecodeInfoRecsMsgWaiting(pstInformationRecords->u.p_InfoRec_Message_Waiting,
                                                        &(pstInfoRecs->u.stMsgWaiting));
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_FillDecodeInfoRecs: Wrong informations records type");
            ulRslt = VOS_ERR;
            break;

    }

    return ulRslt;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeEAWIMRecords
 功能描述  : 填充EAWI消息中records字段
 输入参数  : c_f_dsch_EAWIM_RECs                *pstEAWIMInfoRecords
 输出参数  : CNAS_XCC_EAWIM_STRU                *pstEAWIM
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_VOID CNAS_XCC_FillDecodeEAWIMRecords(
    c_f_dsch_EAWIM_RECs                *pstEAWIMInfoRecords,
    CNAS_XCC_EAWIM_STRU                *pstEAWIM
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;
    VOS_UINT32                          ulRslt;
    c_F_InformationRecords              stInformationRecords;
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs;

    if (VOS_NULL_PTR == pstEAWIMInfoRecords->data)
    {
        return;
    }

    /* 循环处理items个解码后的data数据，若填充了CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM，后续数据不处理 */
    for (ucLoop = 0, ucFillLoop = 0;
        (ucLoop < pstEAWIMInfoRecords->items) && (ucFillLoop < CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM);
         ucLoop++)
    {
        /* 解码后的数据为空 */
        if (VOS_NULL_PTR == pstEAWIMInfoRecords->data[ucLoop])
        {
            continue;
        }

        stInformationRecords = (pstEAWIMInfoRecords->data[ucLoop])->Type_specific_fields;
        pstInfoRecs          = &(pstEAWIM->astInfoRecsData[ucFillLoop].stInfoRecs);
        ulRslt = CNAS_XCC_FillDecodeInfoRecs(&stInformationRecords, pstInfoRecs);
        if (VOS_OK == ulRslt)
        {
            pstEAWIM->astInfoRecsData[ucFillLoop].ucRecordType = (pstEAWIMInfoRecords->data[ucLoop])->RECORD_TYPE;
            pstEAWIM->astInfoRecsData[ucFillLoop].ucRecordLen  = (pstEAWIMInfoRecords->data[ucLoop])->RECORD_LEN;
            ucFillLoop++;
        }
        else
        {
            /* 清空本次所填数据 */
            NAS_MEM_SET_S(pstInfoRecs, sizeof(CNAS_XCC_INFO_RECS_STRU), 0, sizeof(CNAS_XCC_INFO_RECS_STRU));
        }
    }

    pstEAWIM->ucNumInfoRecs = ucFillLoop;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeAWIMRecords
 功能描述  : 填充AFWI消息中records字段
 输入参数  : c_f_dsch_AWIM_INFO_RECORDs         *pstAWIMInfoRecords
 输出参数  : CNAS_XCC_AWIM_STRU                 *pstAWIM
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_VOID CNAS_XCC_FillDecodeAWIMRecords(
    c_f_dsch_AWIM_INFO_RECORDs         *pstAWIMInfoRecords,
    CNAS_XCC_AWIM_STRU                 *pstAWIM
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;
    c_F_InformationRecords              stInformationRecords;
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs;
    VOS_UINT32                          ulRslt;

    if (VOS_NULL_PTR == pstAWIMInfoRecords->data)
    {
        return;
    }

    /* 循环处理items个解码后的data数据，若填充了CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM，后续数据不处理 */
    for (ucLoop = 0, ucFillLoop = 0;
        (ucLoop < pstAWIMInfoRecords->items) && (ucFillLoop < CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM);
         ucLoop++)
    {
        /* 解码后的数据为空 */
        if (VOS_NULL_PTR == pstAWIMInfoRecords->data[ucLoop])
        {
            continue;
        }

        stInformationRecords = (pstAWIMInfoRecords->data[ucLoop])->Type_specific_fields;
        pstInfoRecs          = &(pstAWIM->astInfoRecsData[ucFillLoop].stInfoRecs);
        ulRslt = CNAS_XCC_FillDecodeInfoRecs(&stInformationRecords, pstInfoRecs);
        if (VOS_OK == ulRslt)
        {
            pstAWIM->astInfoRecsData[ucFillLoop].ucRecordType = (pstAWIMInfoRecords->data[ucLoop])->RECORD_TYPE;
            pstAWIM->astInfoRecsData[ucFillLoop].ucRecordLen  = (pstAWIMInfoRecords->data[ucLoop])->RECORD_LEN;
            ucFillLoop++;
        }
        else
        {
            /* 清空本次所填数据 */
            NAS_MEM_SET_S(pstInfoRecs, sizeof(CNAS_XCC_INFO_RECS_STRU), 0, sizeof(CNAS_XCC_INFO_RECS_STRU));
        }
    }

    pstAWIM->ucNumInfoRecs = ucFillLoop;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeExtendedAlertWithInformationMsg
 功能描述  : 解码EAWI消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  3.日    期   : 2014年12月27日
    作    者   : Y00307564
    修改内容   : 1X SS Project修改,增加stMsgFDsch初始化，防止其被异常释放
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeExtendedAlertWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_EAWIM_STRU                *pstEAWIM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeExtendedAlertWithInformationMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.EAWIM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.EAWIM)
    {
        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_EAWI_IS_NULL_PTR,
                                           CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG);

        return VOS_ERR;
    }

    pstEAWIM->ucConRef        = stMsgFDsch.u.EAWIM->CON_REF;
    pstEAWIM->ucConRefPresent = stMsgFDsch.u.EAWIM->CON_REF_Present;
    pstEAWIM->ucConRefIncl    = stMsgFDsch.u.EAWIM->CON_REF_INCL;
    pstEAWIM->ucRecNum        = stMsgFDsch.u.EAWIM->NUM_REC;

    /* 将c_f_dsch_EAWIM_RECs 内容填充到平铺的EAWI结构中 */
    CNAS_XCC_FillDecodeEAWIMRecords(&(stMsgFDsch.u.EAWIM->RECs), pstEAWIM);

    if (pstEAWIM->ucRecNum != pstEAWIM->ucNumInfoRecs)
    {
        /* 若解码后info record个数NUM_REC不相同，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_EAWI_RECNUM_NE_NUMINFORECORD,
                                           CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG);
    }

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeAlertWithInformationMsg
 功能描述  : 解码AWI消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2014年12月27日
    作    者   : Y00307564
    修改内容   : 1X SS Project修改,增加stMsgFDsch初始化，防止其被异常释放
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeAlertWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_AWIM_STRU                 *pstAWIM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeAlertWithInformationMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.AWIM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.AWIM)
    {
        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_AWI_IS_NULL_PTR,
                                           CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG);

        return VOS_ERR;
    }

    /* 将c_f_dsch_AWIM_INFO_RECORDs 内容填充到平铺的EAWI结构中 */
    CNAS_XCC_FillDecodeAWIMRecords(&(stMsgFDsch.u.AWIM->INFO_RECORDs), pstAWIM);

    if (0 == pstAWIM->ucNumInfoRecs)
    {
        /* 若解码后的个数为0，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_AWI_RECNUM_EQ_ZERO,
                                           CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG);
    }

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeEFWIMRecords
 功能描述  : 填充EFWI消息的records
 输入参数  : c_f_dsch_EFWIM_RECs                *pstEFWIMInfoRecords
 输出参数  : CNAS_XCC_EFWIM_STRU                *pstEFWIM
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_FillDecodeEFWIMRecords(
    c_f_dsch_EFWIM_RECs                *pstEFWIMInfoRecords,
    CNAS_XCC_EFWIM_STRU                *pstEFWIM
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;
    c_F_InformationRecords              stInformationRecords;
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs;
    VOS_UINT32                          ulRslt;

    if (VOS_NULL_PTR == pstEFWIMInfoRecords->data)
    {
        return;
    }

    /* 循环处理items个解码后的data数据，若填充了CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM，后续数据不处理 */
    for (ucLoop = 0, ucFillLoop = 0;
        (ucLoop < pstEFWIMInfoRecords->items) && (ucFillLoop < CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM);
         ucLoop++)
    {
        /* 解码后的数据为空 */
        if (VOS_NULL_PTR == pstEFWIMInfoRecords->data[ucLoop])
        {
            continue;
        }

        stInformationRecords = (pstEFWIMInfoRecords->data[ucLoop])->Type_specific_fields;
        pstInfoRecs          = &(pstEFWIM->astInfoRecsData[ucFillLoop].stInfoRecs);
        ulRslt = CNAS_XCC_FillDecodeInfoRecs(&stInformationRecords, pstInfoRecs);
        if (VOS_OK == ulRslt)
        {
            pstEFWIM->astInfoRecsData[ucFillLoop].ucRecordType = (pstEFWIMInfoRecords->data[ucLoop])->RECORD_TYPE;
            pstEFWIM->astInfoRecsData[ucFillLoop].ucRecordLen  = (pstEFWIMInfoRecords->data[ucLoop])->RECORD_LEN;
            ucFillLoop++;
        }
        else
        {
            /* 清空本次所填数据 */
            NAS_MEM_SET_S(pstInfoRecs, sizeof(CNAS_XCC_INFO_RECS_STRU), 0, sizeof(CNAS_XCC_INFO_RECS_STRU));
        }
    }

    pstEFWIM->ucNumInfoRecs = ucFillLoop;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeFWIMRecords
 功能描述  : 填充FWI消息中records字段
 输入参数  : c_f_dsch_FWIM_INFO_RECORDs         *pstFWIMInfoRecords
 输出参数  : CNAS_XCC_FWIM_STRU                 *pstFWIM
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_FillDecodeFWIMRecords(
    c_f_dsch_FWIM_INFO_RECORDs         *pstFWIMInfoRecords,
    CNAS_XCC_FWIM_STRU                 *pstFWIM
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;
    c_F_InformationRecords              stInformationRecords;
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs;
    VOS_UINT32                          ulRslt;

    if (VOS_NULL_PTR == pstFWIMInfoRecords->data)
    {
        return;
    }

    /* 循环处理items个解码后的data数据，若填充了CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM，后续数据不处理 */
    for (ucLoop = 0, ucFillLoop = 0;
        (ucLoop < pstFWIMInfoRecords->items) && (ucFillLoop < CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM);
         ucLoop++)
    {
        /* 解码后的数据为空 */
        if (VOS_NULL_PTR == pstFWIMInfoRecords->data[ucLoop])
        {
            continue;
        }

        stInformationRecords = (pstFWIMInfoRecords->data[ucLoop])->Type_specific_fields;
        pstInfoRecs          = &(pstFWIM->astInfoRecsData[ucFillLoop].stInfoRecs);
        ulRslt = CNAS_XCC_FillDecodeInfoRecs(&stInformationRecords, pstInfoRecs);
        if (VOS_OK == ulRslt)
        {
            pstFWIM->astInfoRecsData[ucFillLoop].ucRecordType = (pstFWIMInfoRecords->data[ucLoop])->RECORD_TYPE;
            pstFWIM->astInfoRecsData[ucFillLoop].ucRecordLen  = (pstFWIMInfoRecords->data[ucLoop])->RECORD_LEN;
            ucFillLoop++;
        }
        else
        {
            /* 清空本次所填数据 */
            NAS_MEM_SET_S(pstInfoRecs, sizeof(CNAS_XCC_INFO_RECS_STRU), 0, sizeof(CNAS_XCC_INFO_RECS_STRU));
        }
    }

    pstFWIM->ucNumInfoRecs = ucFillLoop;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeExtendedFlashWithInformationMsg
 功能描述  : 解码EFWI消息
 输入参数  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 输出参数  : CNAS_XCC_EFWIM_STRU                *pstEFWIM
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   :  1X SS Project修改
  3.日    期   : 2014年12月27日
    作    者   : Y00307564
    修改内容   : 1X SS Project修改,增加stMsgFDsch初始化，防止其被异常释放
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeExtendedFlashWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_EFWIM_STRU                *pstEFWIM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeExtendedFlashWithInformationMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.EFWIM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.EFWIM)
    {
        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_EFWI_IS_NULL_PTR,
                                           CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG);

        return VOS_ERR;
    }

    pstEFWIM->ucConRef        = stMsgFDsch.u.EFWIM->CON_REF;
    pstEFWIM->ucConRefPresent = stMsgFDsch.u.EFWIM->CON_REF_Present;
    pstEFWIM->ucConRefIncl    = stMsgFDsch.u.EFWIM->CON_REF_INCL;
    pstEFWIM->ucRecNum        = stMsgFDsch.u.EFWIM->NUM_REC;

    /* 将c_f_dsch_EFWIM_RECs RECs内容填充到平铺的EFWI结构中 */
    CNAS_XCC_FillDecodeEFWIMRecords(&(stMsgFDsch.u.EFWIM->RECs), pstEFWIM);

    if (pstEFWIM->ucRecNum != pstEFWIM->ucNumInfoRecs)
    {
        /* 若解码后info record个数NUM_REC不相同，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_EFWI_RECNUM_NE_NUMINFORECORD,
                                           CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG);
    }

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeFlashWithInformationMsg
 功能描述  : 解码FWI消息
 输入参数  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 输出参数  : CNAS_XCC_FWIM_STRU                 *pstFWIM
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数
  2.日    期   : 2014年12月27日
    作    者   : Y00307564
    修改内容   : 1X SS Project修改,增加stMsgFDsch初始化，防止其被异常释放
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeFlashWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_FWIM_STRU                 *pstFWIM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara(&stCS0005Detail,
                                      pstDschDataInd->enDschMsgType,
                                      CNAS_CCB_GetPRevInUse(),
                                      0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                             0,
                                             &stMsgFDsch,
                                             pstDschDataInd->usMsgDataLen,
                                             &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeFlashWithInformationMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFDsch.u.FWIM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.FWIM)
    {
        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_FWI_IS_NULL_PTR,
                                           CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG);

        return VOS_ERR;
    }

    /* 将c_f_dsch_FWIM_INFO_RECORDs INFO_RECORDs内容填充到平铺的FWI结构中 */
    CNAS_XCC_FillDecodeFWIMRecords(&(stMsgFDsch.u.FWIM->INFO_RECORDs), pstFWIM);

    if (0 == pstFWIM->ucNumInfoRecs)
    {
        /* 若解码后的个数为0，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                           CNAS_XCC_DECODE_ERRCODE_FWI_RECNUM_EQ_ZERO,
                                           CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG);
    }

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeDschMsg
 功能描述  : 编码dsch信道上的数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeDschMsg(
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8           enMsgTag,
    c_r_dsch                                        *pstRDschMsg,
    VOS_UINT8                                       *pucBuff,
    VOS_UINT32                                      *pulBitDataLen
)
{
    CS0005E_Details                     stDetail;
    VOS_INT32                           iEncodeRet;

    CNAS_XCC_SetCS0005EDetailPara(&stDetail, enMsgTag, CNAS_CCB_GetPRevInUse(), 0);

    /* 得到编码后的L3 PDU */
    iEncodeRet = CNAS_XCC_EncodeRDschMsg((char*)pucBuff, 0, pstRDschMsg, &stDetail);
    if (iEncodeRet < 0)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_EncodeDschMsg: CNAS_XCC_EncodeRDschMsg return wrong: ", iEncodeRet);

        /* 编码失败，可维可测勾包 */
        CNAS_MNTN_LogEncodeAbnormalInfoInd(UEPS_PID_XCC, iEncodeRet, enMsgTag);

        return VOS_ERR;
    }

    /* 编码后的数据长度 */
    *pulBitDataLen = (VOS_UINT32)iEncodeRet;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_FillRDschMSRejectInvalidMsg
 功能描述  : 填充RDSCH上MS REJECT 消息结构
 输入参数  : CAS_1X_REV_ORDER_CODE_ENUM_UINT8  enOrderMsgType,
             VOS_UINT8                         ucOrderQ
 输出参数  : c_r_dsch                         *pstMsgRDsch
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月16日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年08月03日
    作    者   : a00295761
    修改内容   : Added code CON_REF in the Reject Order Message, according to some ORDQ values.

*****************************************************************************/
VOS_UINT32 CNAS_XCC_FillRDschMSRejectInvalidMsg(
    c_r_dsch                                       *pstMsgRDsch,
    CNAS_XCC_REJ_ORDER_INFO_STRU                   *pstRejInfo
)
{
    c_r_dsch_ORDM                        *pstORDM;
    c_R_Mobile_Station_Reject_Order      *pstMSRejectOrder;

    ED_OCTET                              ucPRevInUse;

    NAS_MEM_SET_S(pstMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配rdsch ORDM结构 */
    SETPRESENT_c_r_dsch_ORDM(pstMsgRDsch);

    pstORDM                               = pstMsgRDsch->u.ORDM;

    if (VOS_NULL_PTR == pstORDM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_FillRDschMSRejectInvalidMsg: allocate memory fail");

        /* 防止外面空指针再次做释放 */
        pstMsgRDsch->Present              = U_c_r_dsch_NONE;

        return VOS_ERR;
    }

    SETPRESENT_c_R_Orders_parameters_p_R_Mobile_Station_Reject_Order(&(pstORDM->order.parameters));

    /* 先赋值 order code 和orderq */
    if (CNAS_XCC_INVALID_CON_REF != pstRejInfo->ucConRef)
    {
        pstORDM->CON_REF_INCL           = ED_TRUE;
        pstORDM->CON_REF_INCL_Present   = ED_TRUE;
        pstORDM->CON_REF                = pstRejInfo->ucConRef;
        pstORDM->CON_REF_Present        = ED_TRUE;
    }

    ucPRevInUse = CNAS_CCB_GetPRevInUse();
    if (ucPRevInUse <= P_REV_IN_USE_6)
    {
        pstORDM->CON_REF_INCL           = ED_FALSE;
        pstORDM->CON_REF_INCL_Present   = ED_FALSE;
        pstORDM->CON_REF                = 0x00;
        pstORDM->CON_REF_Present        = ED_FALSE;
    }

    pstORDM->order.ORDER                  = pstRejInfo->enRevOrderCode;

    pstMSRejectOrder                      = pstORDM->order.parameters.u.p_R_Mobile_Station_Reject_Order;
    if (VOS_NULL_PTR == pstMSRejectOrder)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_FillRDschMSRejectInvalidMsg: allocate memory fail");

        /* 防止外面空指针再次做释放 */
        pstORDM->order.parameters.Present    = U_c_R_Orders_parameters_NONE;

        return VOS_ERR;
    }

    pstMSRejectOrder->ORDQ                   = pstRejInfo->enRevOrdq;
    pstMSRejectOrder->REJECTED_TYPE          = (VOS_UINT8)pstRejInfo->enRejRxTchMsgType;

    if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pstRejInfo->enRejRxTchMsgType)
    {
        /*对 MS reject 消息携带的参数赋值*/
        pstMSRejectOrder->REJECTED_ORDER         = pstRejInfo->ucRejOrderCode;
        pstMSRejectOrder->REJECTED_ORDER_Present = ED_TRUE;
        pstMSRejectOrder->REJECTED_ORDQ          = pstRejInfo->ucRejOrdq;
        pstMSRejectOrder->REJECTED_ORDQ_Present  = ED_TRUE;
    }


    /* According to CS005-A_v6.0, section 2.7.3.4:
    If the Reject ORDQ is '00010000', '00010001' or '00010010', the Order Specific fields also includes the CON_REF (8 bits) */
    if ((CNAS_XCC_REV_ORDER_MS_REJECT_CALL_ASSIGN == pstRejInfo->enRevOrdq)
     || (CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST == pstRejInfo->enRevOrdq)
     || (CNAS_XCC_REV_ORDER_MS_REJECT_CC_ALREADY_PRESENT == pstRejInfo->enRevOrdq))
    {
        pstMSRejectOrder->CON_REF_Present = ED_TRUE;
        pstMSRejectOrder->CON_REF         = pstRejInfo->ucConRef;
    }

    /* 对于SCM消息的REJECT ORDER消息中，无需携带其他参数，后面对其他类型的消息的回复暂无实现 */


    /* If the order is sent on the Access Channel or Enhanced Access Channel and  REJECTED_TYPE is
       '00001100' or or if the order is sent on the Reverse Traffic Channel and REJECTED_TYPE is
       '00000011','00101000','00001110' or '00101010'.
       the order-specific fields also include the following field:
        _________________________________________________________
       |    REJECTED_RECORD          |           8(bits)         |
       |_____________________________|___________________________|
     */
    if ((CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstRejInfo->enRejRxTchMsgType)
     || (CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG == pstRejInfo->enRejRxTchMsgType)
     || (CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG == pstRejInfo->enRejRxTchMsgType)
     || (CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG == pstRejInfo->enRejRxTchMsgType))
    {
        pstMSRejectOrder->REJECTED_RECORD_Present = ED_TRUE;

        /* TODO: 如何填写REJECTED_RECORD字段? 目前先填写为Reserved(0x01) */
        pstMSRejectOrder->REJECTED_RECORD         = 0x01;
    }


    /* REJECTED_PDU_TYPE暂没实现 */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        pstMSRejectOrder->REJECTED_PDU_TYPE_Present  = PS_IE_PRESENT;
        pstMSRejectOrder->REJECTED_PDU_TYPE          = 0; /* 参照标杆，此处固定填0 */
    }
    else
    {
        pstMSRejectOrder->REJECTED_PDU_TYPE_Present  = PS_IE_NOT_PRESENT;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeTxTchMSRejectOrderMsg
 功能描述  : RDSCH发送order消息公共处理函数
 输入参数  : enOrderCode    - 参见C.S0005 Table 2.7.3
             enORDQ         - 参见C.S0005 Table 2.7.3
             enRxTchMsgType - C.S0004-D Table 3.2.2.2.1.2-1
             pucPdudata     - 编码后的PDU
             pulL3PduBitLen - PDU的bit len
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeTxTchMSRejectOrderMsg(
    CNAS_XCC_REJ_ORDER_INFO_STRU                   *pstRejInfo
)
{
    VOS_UINT32                                  ulRslt;
    c_r_dsch                                    stMsgRDsch;

    /* 填充MS REJECT INVALID 参数 */
    NAS_MEM_SET_S(&stMsgRDsch, sizeof(stMsgRDsch), 0, sizeof(stMsgRDsch));
    ulRslt = CNAS_XCC_FillRDschMSRejectInvalidMsg(&stMsgRDsch,
                                                  pstRejInfo);

    if (VOS_OK != ulRslt)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_EncodeTxTchMSRejectOrderMsg: CNAS_XCC_FillRDschMSRejectInvalidMsg fail, result", ulRslt);

        FREE_c_r_dsch(&stMsgRDsch);

        return ulRslt;
    }

    /* 编码L3 PDU */
    pstRejInfo->ulL3PduBitLen  = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                                    &stMsgRDsch,
                                    pstRejInfo->pucPdudata,
                                    &pstRejInfo->ulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeTxTchConnectOrderMsg
 功能描述  : TCH信道下，编码Connect Order消息
 输入参数  : 无
 输出参数  : pucPdudata  -- 编码后的PDU数据
             pulL3PduBit --
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeTxTchConnectOrderMsg(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{

    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配rdsch ORDM结构 */
    SETPRESENT_c_r_dsch_ORDM(&stMsgRDsch);

    if (VOS_NULL_PTR == stMsgRDsch.u.ORDM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeTxTchConnectOrderMsg: allocate memory fail");

        *pulL3PduBitLen = 0;

        return VOS_ERR;
    }

    /* 先赋值 order code 和orderq */
    if (CNAS_XCC_INVALID_CON_REF != ucConRef)
    {
        stMsgRDsch.u.ORDM->CON_REF_INCL         = ED_TRUE;
        stMsgRDsch.u.ORDM->CON_REF_INCL_Present = ED_TRUE;
        stMsgRDsch.u.ORDM->CON_REF              = ucConRef;
        stMsgRDsch.u.ORDM->CON_REF_Present      = ED_TRUE;
    }

    /* 申请内存 */
    SETPRESENT_c_R_Orders_parameters_p_R_Generic_Order(&stMsgRDsch.u.ORDM->order.parameters);

    if (VOS_NULL_PTR == stMsgRDsch.u.ORDM->order.parameters.u.p_R_Generic_Order)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeTxTchConnectOrderMsg: allocate memory fail");

        stMsgRDsch.u.ORDM->order.parameters.Present = U_c_R_Orders_parameters_NONE;

        FREE_c_r_dsch(&stMsgRDsch);

        return VOS_ERR;
    }

    stMsgRDsch.u.ORDM->order.ORDER                                = CNAS_XCC_REV_ORDER_CODE_CONNECT;
    stMsgRDsch.u.ORDM->order.parameters.u.p_R_Generic_Order->ORDQ = 0;

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq
 功能描述  : 编码Flash With Information Message消息
 输入参数  : 无
 输出参数  : ucDigitNum     -- 需要发送的码流长度
             pucDigit       -- 需要发送的码流指针
             pucPdudata     -- 编码后的PDU数据
             pulL3PduBitLen -- 编码后的PDU数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2014年12月1日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配c_r_dsch_FWIM结构 */
    SETPRESENT_c_r_dsch_FWIM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.FWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq: allocate c_r_dsch_FWIM memory fail");
        return VOS_ERR;
    }

    if (0 != ucDigitNum)
    {
        /* 分配c_r_dsch_FWIM_INFO_RECORDSs_data结构 */
        ADDITEMS_c_r_dsch_FWIM_INFO_RECORDSs(&stMsgRDsch.u.FWIM->INFO_RECORDSs, 1);
        if ( (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data)
           ||(VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq: allocate c_r_dsch_FWIM_INFO_RECORDSs_data memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->RECORD_TYPE = CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_KEYPAD_FACILITY;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->RECORD_LEN  = ucDigitNum;

        /* 分配c_RIR_Keypad_Facility结构 */
        SETPRESENT_c_R_InformationRecords_p_Keypad_Facility(&(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields));
        if (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Keypad_Facility)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq: allocate c_RIR_Keypad_Facility memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        /* 分配c_RIR_Keypad_Facility_CHARi结构 */
        ADDITEMS_c_RIR_Keypad_Facility_CHARi(
                         &(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi),
                         ucDigitNum);
        if (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi.data)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq: allocate c_RIR_Keypad_Facility_CHARi memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        NAS_MEM_CPY_S(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi.data,
                      ucDigitNum,
                      pucDigit,
                      ucDigitNum);
    }

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq
 功能描述  : 编码Extern Flash With Information Message消息
 输入参数  : 无
 输出参数  : ucConRef       -- connect reference
             ucDigitNum     -- 需要发送的码流长度
             pucDigit       -- 需要发送的码流指针
             pucPdudata     -- 编码后的PDU数据
             pulL3PduBitLen -- 编码后的PDU数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2014年12月1日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配c_r_dsch_EFWIM结构 */
    SETPRESENT_c_r_dsch_EFWIM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq: allocate c_r_dsch_EFWIM memory fail");
        return VOS_ERR;
    }

    if (CNAS_XCC_INVALID_CON_REF != ucConRef)
    {
        stMsgRDsch.u.EFWIM->CON_REF         = ucConRef;
        stMsgRDsch.u.EFWIM->CON_REF_Present = ED_TRUE;
        stMsgRDsch.u.EFWIM->CON_REF_INCL    = ED_TRUE;
    }

    if (0 == ucDigitNum)
    {
        stMsgRDsch.u.EFWIM->NUM_REC = 0;
    }
    else
    {
        stMsgRDsch.u.EFWIM->NUM_REC = 1;

        /* 分配c_r_dsch_EFWIM_RECs_data结构 */
        ADDITEMS_c_r_dsch_EFWIM_RECs(&stMsgRDsch.u.EFWIM->RECs, 1);
        if ( (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data)
           ||(VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq: allocate c_r_dsch_EFWIM_RECs_data memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.EFWIM->RECs.data[0]->RECORD_TYPE = CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_KEYPAD_FACILITY;
        stMsgRDsch.u.EFWIM->RECs.data[0]->RECORD_LEN  = ucDigitNum;

        /* 分配c_RIR_Keypad_Facility结构 */
        SETPRESENT_c_R_InformationRecords_p_Keypad_Facility(&(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields));
        if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Keypad_Facility)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq: allocate c_RIR_Keypad_Facility memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        /* 分配c_RIR_Keypad_Facility_CHARi结构 */
        ADDITEMS_c_RIR_Keypad_Facility_CHARi(
                         &(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi),
                         ucDigitNum);
        if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi.data)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq: allocate c_RIR_Keypad_Facility_CHARi memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        NAS_MEM_CPY_S(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Keypad_Facility->CHARi.data,
                      ucDigitNum,
                      pucDigit,
                      ucDigitNum);
    }

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertDtmfMinInterDigitIntervalToDtmfOffLength
 功能描述  : DTMF minimum inter-digit interval转换为DTMF Off Length    - VOS_UINT32
             pucDtmfOffLen                                             - VOS_UINT8
 输出参数  : VOS_UINT32
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ConvertDtmfMinInterDigitIntervalToDtmfOffLength(
    VOS_UINT32                          ulDtmfMinInterDigitInterval,
    VOS_UINT8                          *pucDtmfOffLen
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ulDtmfMinInterDigitInterval)
    {
        case CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_60:
            *pucDtmfOffLen = CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_0;
            break;

        case CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_100:
            *pucDtmfOffLen = CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_1;
            break;

        case CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_150:
            *pucDtmfOffLen = CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_2;
            break;

        case CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_200:
            *pucDtmfOffLen = CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_3;
            break;

        default:
            ulRslt = VOS_ERR;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertDtmfPulseWidthCodeToDtmfOnLength
 功能描述  : DTMF pulse width转换成DTMF On length
 输入参数  : ulDtmfPulseWidth - VOS_UINT32
             pucDtmfOnLen    - VOS_UINT8
 输出参数  : VOS_UINT32
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ConvertDtmfPulseWidthCodeToDtmfOnLength(
    VOS_UINT32                          ulDtmfPulseWidth,
    VOS_UINT8                          *pucDtmfOnLen
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ulDtmfPulseWidth)
    {
        case CNAS_XCC_DTMF_PULSE_WIDTH_95:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_0;
            break;

        case CNAS_XCC_DTMF_PULSE_WIDTH_150:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_1;
            break;

        case CNAS_XCC_DTMF_PULSE_WIDTH_200:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_2;
            break;

        case CNAS_XCC_DTMF_PULSE_WIDTH_250:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_3;
            break;

        case CNAS_XCC_DTMF_PULSE_WIDTH_300:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_4;
            break;

        case CNAS_XCC_DTMF_PULSE_WIDTH_350:
            *pucDtmfOnLen = CNAS_XCC_SEND_BURST_DTMF_ON_LEN_5;
            break;

        default:
            ulRslt = VOS_ERR;
            break;
    }

    return ulRslt;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_AsciiToBcdCode
 功能描述  : 将Ascii码字符转换成BCD码字符
 输入参数  : ucAsciiCode  - ASCII字符
 输出参数  : pucBcdCode   - 转换得到的BCD码
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32  CNAS_XCC_AsciiToBcdCode(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        return VOS_ERR;
    }

    if ((cAsciiCode > '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0c;
    }
    else if ('0' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeSendBurstDTMFMsg
 功能描述  : 编码Send Burst DTMF消息
 输入参数  : 无
 输出参数  : pstXcallBurstDTMFReq  -- 需要发送的码流指针
             pucPdudata            -- 编码后的PDU数据
             pulL3PduBitLen        -- 编码后的PDU数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeSendBurstDTMFMsg(
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;
    VOS_UINT8                           ucDtmfOnLen;
    VOS_UINT8                           ucDtmfOffLen;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT8                           ucPRevInUse;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;


    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallBurstDTMFReq->ucCallId, &ucIndex))
    {
        return VOS_ERR;
    }

    if (0 == pstXcallBurstDTMFReq->ucDigitNum)
    {
        return VOS_ERR;
    }

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));
    /* 分配c_r_dsch_BDTMFM结构 */
    SETPRESENT_c_r_dsch_BDTMFM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.BDTMFM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeSendBurstDTMFMsg: allocate c_r_dsch_BDTMFM memory fail");
        return VOS_ERR;
    }

    if (CNAS_XCC_INVALID_CON_REF != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef)
    {
        stMsgRDsch.u.BDTMFM->CON_REF         = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef;
        stMsgRDsch.u.BDTMFM->CON_REF_Present = ED_TRUE;
        stMsgRDsch.u.BDTMFM->CON_REF_INCL    = ED_TRUE;
    }

    /*
        If P_REV_IN_USEs is equal to or greater than seven, the mobile station shall perform the following:
          if this Call Control instance is identified by NULL,the mobile station shall set the CON_REL_INCL field of the
          message to '0';otherwise,the mobile station shall set the CON_REL_INCL field of the message to '1' and the
          CON_REF field of the message to the connection reference of the service option connection corresponding to this
          call
    */
    ucPRevInUse = CNAS_CCB_GetPRevInUse();

    if (ucPRevInUse >= P_REV_IN_USE_7)
    {
        stMsgRDsch.u.BDTMFM->CON_REF_INCL_Present = ED_TRUE;
    }
    else
    {
        stMsgRDsch.u.BDTMFM->CON_REF_INCL_Present = ED_FALSE;
    }

    if ((ucPRevInUse < P_REV_IN_USE_7)
      ||(VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc))
    {
        stMsgRDsch.u.BDTMFM->CON_REF_INCL    = ED_FALSE;

        stMsgRDsch.u.BDTMFM->CON_REF_Present = ED_FALSE;
    }
    else
    {
        stMsgRDsch.u.BDTMFM->CON_REF_INCL    = ED_TRUE;
    }
    stMsgRDsch.u.BDTMFM->NUM_DIGITS = pstXcallBurstDTMFReq->ucDigitNum;

    ulRslt = CNAS_XCC_ConvertDtmfPulseWidthCodeToDtmfOnLength(pstXcallBurstDTMFReq->ulOnLength, &ucDtmfOnLen);
    if (VOS_OK != ulRslt)
    {
        FREE_c_r_dsch(&stMsgRDsch);
        return VOS_ERR;
    }

    ulRslt = CNAS_XCC_ConvertDtmfMinInterDigitIntervalToDtmfOffLength(pstXcallBurstDTMFReq->ulOffLength, &ucDtmfOffLen);
    if (VOS_OK != ulRslt)
    {
        FREE_c_r_dsch(&stMsgRDsch);
        return VOS_ERR;
    }

    stMsgRDsch.u.BDTMFM->DTMF_ON_LENGTH   = ucDtmfOnLen;
    stMsgRDsch.u.BDTMFM->DTMF_OFF_LENGTH  = ucDtmfOffLen;

    /* 分配c_r_dsch_BDTMFM_DIGITSs结构 */
    ADDITEMS_c_r_dsch_BDTMFM_DIGITSs(&stMsgRDsch.u.BDTMFM->DIGITSs, pstXcallBurstDTMFReq->ucDigitNum);

    if (VOS_NULL_PTR == stMsgRDsch.u.BDTMFM->DIGITSs.data)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeSendBurstDTMFMsg: allocate c_r_dsch_FWIM_INFO_RECORDSs_data memory fail");
        FREE_c_r_dsch(&stMsgRDsch);
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < pstXcallBurstDTMFReq->ucDigitNum; ucLoop++)
    {
        if (VOS_NULL_PTR == stMsgRDsch.u.BDTMFM->DIGITSs.data[ucLoop])
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeSendBurstDTMFMsg: allocate c_r_dsch_FWIM_INFO_RECORDSs_data[] memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        ulRslt = CNAS_XCC_AsciiToBcdCode((VOS_CHAR)pstXcallBurstDTMFReq->aucDigit[ucLoop], &ucBcdCode);
        if (VOS_OK != ulRslt)
        {
            FREE_c_r_dsch(&stMsgRDsch);
            return ulRslt;
        }

        /*将数字填入相应的空间*/
        (stMsgRDsch.u.BDTMFM->DIGITSs.data[(ucLoop)])->DIGITi = ucBcdCode;
    }

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_SEND_BURST_DTMF_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillDecodeFNMRecords
 功能描述  : 填充FNM消息中records字段
 输入参数  : c_f_csch_FNM_INFO_RECORDs        *pstFNMInfoRecords
 输出参数  : CNAS_XCC_FNM_STRU                *pstFNM
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_VOID CNAS_XCC_FillDecodeFNMRecords(
    c_f_csch_FNM_INFO_RECORDs          *pstFNMInfoRecords,
    CNAS_XCC_FNM_STRU                  *pstFNM
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFillLoop;
    VOS_UINT32                          ulRslt;
    c_F_InformationRecords              stInformationRecords;
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs;

    if (VOS_NULL_PTR == pstFNMInfoRecords->data)
    {
        return;
    }

    /* 循环处理items个解码后的data数据，若填充了CNAS_XCC_MAX_FNM_INFO_RECO_NUM，后续数据不处理 */
    for (ucLoop = 0, ucFillLoop = 0;
        (ucLoop < pstFNMInfoRecords->items) && (ucFillLoop < CNAS_XCC_MAX_FNM_INFO_RECO_NUM);
         ucLoop++)
    {
        /* 解码后的数据为空 */
        if (VOS_NULL_PTR == pstFNMInfoRecords->data[ucLoop])
        {
            continue;
        }

        stInformationRecords = (pstFNMInfoRecords->data[ucLoop])->Type_specific_fields;
        pstInfoRecs          = &(pstFNM->astInfoRecsData[ucFillLoop].stInfoRecs);
        ulRslt = CNAS_XCC_FillDecodeInfoRecs(&stInformationRecords, pstInfoRecs);
        if (VOS_OK == ulRslt)
        {
            pstFNM->astInfoRecsData[ucFillLoop].ucRecordType = (pstFNMInfoRecords->data[ucLoop])->RECORD_TYPE;
            pstFNM->astInfoRecsData[ucFillLoop].ucRecordLen  = (pstFNMInfoRecords->data[ucLoop])->RECORD_LEN;
            ucFillLoop++;
        }
        else
        {
            /* 清空本次所填数据 */
            NAS_MEM_SET_S(pstInfoRecs, sizeof(CNAS_XCC_INFO_RECS_STRU), 0, sizeof(CNAS_XCC_INFO_RECS_STRU));
        }
    }

    pstFNM->ucNumInfoRecs = ucFillLoop;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeFeatureNotificationMsg
 功能描述  : 解码FNM消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeFeatureNotificationMsg(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd,
    CNAS_XCC_FNM_STRU                  *pstFNM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_csch_mini6                      stMsgFCsch;
    VOS_INT32                           lDecodeRslt;

    NAS_MEM_SET_S(&stMsgFCsch, sizeof(stMsgFCsch), 0, sizeof(stMsgFCsch));

    /* 填充 CS0005E_Details 结构 */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                   pstCschDataInd->enCschMsgType,
                                   CNAS_CCB_GetPRevInUse(),
                                   0);

    /* 解码普通消息 */
    lDecodeRslt = CNAS_XCC_DecodeFCschMsg((char*)(pstCschDataInd->aucMsgData),
                                           0,
                                           &stMsgFCsch,
                                           pstCschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeFeatureNotificationMsg: decode fail");

        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG);

        /* 释放编解码分配的内存 */
        if (VOS_NULL_PTR != stMsgFCsch.u.FNM)
        {
            CNAS_XCC_FreeFCschMsg(&stMsgFCsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFCsch.u.FNM)
    {
        /* 解码失败，可维可测勾包 */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, CNAS_XCC_DECODE_ERRCODE_FNM_IS_NULL_PTR, CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG);

        return VOS_ERR;
    }

    pstFNM->ucIsRelease        = stMsgFCsch.u.FNM->RELEASE;

    /* 将c_f_csch_FNM_INFO_RECORDs 内容填充到平铺的FNM结构中 */
    CNAS_XCC_FillDecodeFNMRecords(&(stMsgFCsch.u.FNM->INFO_RECORDs), pstFNM);

    CNAS_XCC_FreeFCschMsg(&stMsgFCsch);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_DecodeServiceOptionControlMsg
 功能描述  : Decode SCOM Message
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:decode success, VOS_ERR:decode fail
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DecodeServiceOptionControlMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;
    VOS_UINT16                          usOctetLen;
    //VOS_UINT16                          usCpyLen;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* fill the sturct of CS0005E_Details  */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pstDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* decode FDSCH MSG */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pstDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pstDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* decode fail, release memory and return */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeServiceOptionControlMsg: decode fail");

        /* log  abnormal info */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, lDecodeRslt, CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG);

        /* release the allocated memory */
        if (VOS_NULL_PTR != stMsgFDsch.u.SOCM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.SOCM)
    {
        CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC, CNAS_XCC_DECODE_ERRCODE_SOCM_IS_NULL_PTR, CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG);

        return VOS_ERR;
    }

    /* fill pstSOCM */
    NAS_MEM_SET_S(pstSOCM, sizeof(CNAS_XCC_SOCM_STRU), 0, sizeof(CNAS_XCC_SOCM_STRU));
    pstSOCM->usSo               = (VOS_UINT16)stMsgFDsch.u.SOCM->SERVICE_OPTION;
    pstSOCM->ucActionTime       = stMsgFDsch.u.SOCM->ACTION_TIME;
    pstSOCM->ucConRef           = stMsgFDsch.u.SOCM->CON_REF;
    pstSOCM->ucCtlRecLen        = stMsgFDsch.u.SOCM->CTL_REC_LEN;
    pstSOCM->ucUseTime          = stMsgFDsch.u.SOCM->USE_TIME;
    pstSOCM->usBitLen           = (VOS_UINT16)stMsgFDsch.u.SOCM->Type_specific_fields.usedBits;

    /* get octect len */
    usOctetLen = (VOS_UINT16)(stMsgFDsch.u.SOCM->Type_specific_fields.usedBits / CNAS_XCC_OCTET_BIT_LEN);
    if (0 != (stMsgFDsch.u.SOCM->Type_specific_fields.usedBits % CNAS_XCC_OCTET_BIT_LEN))
    {
        usOctetLen++;
    }

    NAS_MEM_CPY_S(pstSOCM->aucData,
                  CNAS_XCC_MAX_SOCM_FIELD_DATA_LEN,
                  stMsgFDsch.u.SOCM->Type_specific_fields.value,
                  CNAS_MIN(usOctetLen, CNAS_XCC_MAX_SOCM_FIELD_DATA_LEN));

    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_VoiceSoCtrlMsgParaCheck
 功能描述  : check SCOM Message Parameter
 输入参数  : pstSOCM: SOCM Message
 输出参数  : 无
 返 回 值  : VOS_TRUE:Para is OK, VOS_FALSE:Para is not ok
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_VoiceSoCtrlMsgParaCheck(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    VOS_UINT8                           ucRateReduc;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    switch(pstSOCM->usSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
            /* If the RATE_REDUC field is not equal to a value defined in  Table  2.2.2.2-1,
               the mobile station shall reject the message by sending a Mobile Station Reject
               Order with the ORDQ field set equal to '00000100' */
            ucRateReduc = pstSOCM->aucData[0] >> CNAS_XCC_BIT_LEN_5_BIT;
            if (ucRateReduc > CNAS_XCC_SO3_MAX_RATE_REDUC)
            {
                NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));
                NAS_MEM_SET_S(aucPduData, sizeof(aucPduData), 0x0, sizeof(aucPduData));

                /* encode REJ ORDER */
                stRejInfo.ucConRef          = pstSOCM->ucConRef;
                stRejInfo.enRejRxTchMsgType = CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG;
                stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
                stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_FIELD;
                stRejInfo.ulL3PduBitLen     = 0;
                stRejInfo.pucPdudata        = aucPduData;
                CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

                /* Send ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER) To CAS */
                CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                          0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, stRejInfo.pucPdudata);
                return VOS_FALSE;
            }
            break;

        /* Only support SO3 and SO68，SO68 do not need check parameter */
        default:
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_DataSoCtrlMsgParaCheck
 功能描述  : 对数据类的SCOM消息，进行参数检查
 输入参数  : pstSOCM:SOCM Message
 输出参数  : 无
 返 回 值  : VOS_TRUE:解码成功 VOS_FALSE:解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_DataSoCtrlMsgParaCheck(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    CNAS_XCC_REJ_ORDER_INFO_STRU                stRejInfo;
    CNAS_XCC_FDSCH_SO_CTRL_FIELD_ENUM_UINT8     enSoCtrlField;
    VOS_UINT8                                   ucDormCntl;
    VOS_UINT8                                   aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT8                                   ucPktConCtrl;

    /* FIELD_TYPE is different，means different SOCM Message
        Dormant Timer Control              FIELD TYPE is '011'
        Packet Zone Reconnection Control   FIELD TYPE is '100' */

    /* Data Dormant Timer Control          Packet Connection Control
        Field Length        (bits)          Field Length        (bits)
        DORM_CNTL           3               PKT_CON_CNTL        3
        RESERVED            2               RESERVED            2
        FIELD_TYPE          3               FIELD_TYPE          3
        DORM_TIME           0 or 8          RESERVED            0 or 4
                                            PKT_ZONE_LIST_LEN   0 or 4
    */

    NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

    enSoCtrlField = (pstSOCM->aucData[0] & CNAS_XCC_LOW_3_BIT_MASK);

    switch(enSoCtrlField)
    {
        case CNAS_XCC_FDSCH_SO_CTRL_FIELD_DORMANT_TIMER_CTRL:
            /* The DORM_CNTL field shall be set appropriately as specified in Table 3.
                  If the mobile station receives a Service Option Control Message for the
                  service option with FIELD_TYPE set to '011' and the DORM_CNTL field is not
                  equal to a value defined in Table 3, the mobile station shall reject the
                  message by sending a Mobile Station Reject Order with the ORDQ ield set
                  equal to '00000100'  */
            ucDormCntl = (VOS_UINT8)(pstSOCM->aucData[0] >> CNAS_XCC_5_BIT_OFFSET);
            if (ucDormCntl > CNAS_XCC_MAX_DORM_CNTL_VAL)
            {

                /* encode REJ ORDER */
                NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));
                NAS_MEM_SET_S(aucPduData, sizeof(aucPduData), 0x0, sizeof(aucPduData));
                stRejInfo.ucConRef          = pstSOCM->ucConRef;
                stRejInfo.enRejRxTchMsgType = CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG;
                stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
                stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_FIELD;
                stRejInfo.ulL3PduBitLen     = 0;
                stRejInfo.pucPdudata        = aucPduData;
                CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

                /* send ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER) to CAS */
                CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                          0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, stRejInfo.pucPdudata);
                return VOS_FALSE;
            }
            break;


        case CNAS_XCC_FDSCH_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL:
            /* If the mobile station receives a Service Option Control Message for the service option with
                  FIELD_TYPE set to '100' and the PKT_CON_CNTL field is not equal to a value defined in
                  Table 6, the mobile station shall reject the message by sending a Mobile Station Reject
                  Order with the ORDQ field set equal to '00000100' */
            ucPktConCtrl = (VOS_UINT8)(pstSOCM->aucData[0] >> CNAS_XCC_5_BIT_OFFSET);
            if (ucPktConCtrl > CNAS_XCC_MAX_PKT_CONN_CTRL_VAL)
            {
                /* encode REJ ORDER */
                NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));
                NAS_MEM_SET_S(aucPduData, sizeof(aucPduData), 0x0, sizeof(aucPduData));
                stRejInfo.ucConRef          = pstSOCM->ucConRef;
                stRejInfo.enRejRxTchMsgType = CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG;
                stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
                stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_FIELD;
                stRejInfo.ulL3PduBitLen     = 0;
                stRejInfo.pucPdudata        = aucPduData;
                CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

                /* send ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER) to CAS */
                CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                          0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, stRejInfo.pucPdudata);
                return VOS_FALSE;
            }
            break;

        /* Currently, other type do not need to check  */
        default:
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList
 功能描述  : 在下行消息解析出来的info record列表中，查找指定类型的info record
 输入参数  : enInfoRecsType  - 指定的info record type
             ucNumInfoRecs   - 待查找的info record列表元素个数
             pstInfoRecsData - 待查找的info record列表指针
 输出参数  : pucIndex        - 查找成功，则返回对应的索引号
 返 回 值  : VOS_TRUE  - 查找成功
             VOS_FALSE - 查找失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32  CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM_UINT32            enInfoRecsType,
    VOS_UINT8                                               ucNumInfoRecs,
    CNAS_XCC_INFO_RECS_DATA_STRU                           *pstInfoRecsData,
    VOS_UINT8                                              *pucIndex
)
{
    VOS_UINT8                           ucLoop;

    for (ucLoop = 0; ucLoop < ucNumInfoRecs; ucLoop++)
    {
        if (enInfoRecsType == pstInfoRecsData[ucLoop].stInfoRecs.enInfoRecsType)
        {
            *pucIndex = ucLoop;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq
 功能描述  : 紧急呼叫场景编码Flash With Information Message消息
 输入参数  : 无
 输出参数  : ucDigitNum     -- 需要发送的码流长度
             pucDigit       -- 需要发送的码流指针
             pucPdudata     -- 编码后的PDU数据
             pulL3PduBitLen -- 编码后的PDU数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq(
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8                         enDigitMode,
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU                   *pstCalledPartyNum,
    VOS_UINT8                                              *pucPdudata,
    VOS_UINT32                                             *pulL3PduBitLen
)
{
    VOS_UINT32                                              ulRslt;
    c_r_dsch                                                stMsgRDsch;
    VOS_UINT8                                               i;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配c_r_dsch_FWIM结构 */
    SETPRESENT_c_r_dsch_FWIM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.FWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq: allocate c_r_dsch_FWIM memory fail");
        return VOS_ERR;
    }

    if (0 != pstCalledPartyNum->ucDigitNum)
    {
        /* 分配c_r_dsch_FWIM_INFO_RECORDSs_data结构 */
        ADDITEMS_c_r_dsch_FWIM_INFO_RECORDSs(&stMsgRDsch.u.FWIM->INFO_RECORDSs, 1);
        if ((VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data)
         || (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq: allocate c_r_dsch_FWIM_INFO_RECORDSs_data memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->RECORD_TYPE = CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_GLOBAL_EMERGENCY_CALL;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->RECORD_LEN  = pstCalledPartyNum->ucDigitNum;

        /* 分配p_Global_Emergency_Call结构 */
        SETPRESENT_c_R_InformationRecords_p_Global_Emergency_Call(&(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields));
        if (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        /* 分配c_RIR_Global_Emergency_Call_CHARi结构 */
        ADDITEMS_c_RIR_Global_Emergency_Call_CHARi(
                         &(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi),
                         pstCalledPartyNum->ucDigitNum);
        if (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->DIGIT_MODE          = enDigitMode;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->DIGIT_MODE_Present  = VOS_TRUE;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->MS_ORIG_POS_LOC_IND = VOS_FALSE;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_PLAN         = pstCalledPartyNum->enNumPlan;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_PLAN_Present = VOS_TRUE;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_TYPE         = pstCalledPartyNum->enNumType;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_TYPE_Present = VOS_TRUE;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_CHAR            = pstCalledPartyNum->ucDigitNum;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_CHAR_Present    = VOS_TRUE;
        stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_INCL            = VOS_TRUE;

        for (i = 0; i < pstCalledPartyNum->ucDigitNum; i++)
        {
            stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value
                                = EDAlloc(sizeof(ED_BYTE));

            if (VOS_NULL_PTR == stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value)
            {
                CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call_CHARI_data_value memory fail");
                FREE_c_r_dsch(&stMsgRDsch);
                return VOS_ERR;
            }

            *(stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value)
                        = pstCalledPartyNum->aucDigit[i];

            if (XCC_XCALL_DIGIT_MODE_DTMF == enDigitMode)
            {
                stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->usedBits
                                = 4;
            }
            else
            {
                stMsgRDsch.u.FWIM->INFO_RECORDSs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->usedBits
                                = 8;
            }
        }
    }

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq
 功能描述  : 编码Extern Flash With Information Message消息
 输入参数  : 无
 输出参数  : ucConRef       -- connect reference
             ucDigitNum     -- 需要发送的码流长度
             pucDigit       -- 需要发送的码流指针
             pucPdudata     -- 编码后的PDU数据
             pulL3PduBitLen -- 编码后的PDU数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq(
    VOS_UINT8                                               ucConRef,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8                         enDigitMode,
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU                   *pstCalledPartyNum,
    VOS_UINT8                                              *pucPdudata,
    VOS_UINT32                                             *pulL3PduBitLen
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;
    VOS_UINT8                           i;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配c_r_dsch_EFWIM结构 */
    SETPRESENT_c_r_dsch_EFWIM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq: allocate c_r_dsch_EFWIM memory fail");
        return VOS_ERR;
    }

    if (CNAS_XCC_INVALID_CON_REF != ucConRef)
    {
        stMsgRDsch.u.EFWIM->CON_REF         = ucConRef;
        stMsgRDsch.u.EFWIM->CON_REF_Present = ED_TRUE;
        stMsgRDsch.u.EFWIM->CON_REF_INCL    = ED_TRUE;
    }

    if (0 == pstCalledPartyNum->ucDigitNum)
    {
        stMsgRDsch.u.EFWIM->NUM_REC = 0;
    }
    else
    {
        stMsgRDsch.u.EFWIM->NUM_REC = 1;

        /* 分配c_r_dsch_EFWIM_RECs_data结构 */
        ADDITEMS_c_r_dsch_EFWIM_RECs(&stMsgRDsch.u.EFWIM->RECs, 1);
        if ((VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data)
         || (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq: allocate c_r_dsch_EFWIM_RECs_data memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.EFWIM->RECs.data[0]->RECORD_TYPE = CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_GLOBAL_EMERGENCY_CALL;
        stMsgRDsch.u.EFWIM->RECs.data[0]->RECORD_LEN  = pstCalledPartyNum->ucDigitNum;

        /* 分配p_Global_Emergency_Call结构 */
        SETPRESENT_c_R_InformationRecords_p_Global_Emergency_Call(&(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields));
        if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        /* 分配c_RIR_Global_Emergency_Call_CHARi结构 */
        ADDITEMS_c_RIR_Global_Emergency_Call_CHARi(
                         &(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi),
                         pstCalledPartyNum->ucDigitNum);
        if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call memory fail");
            FREE_c_r_dsch(&stMsgRDsch);
            return VOS_ERR;
        }

        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->DIGIT_MODE          = enDigitMode;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->DIGIT_MODE_Present  = VOS_TRUE;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->MS_ORIG_POS_LOC_IND = VOS_TRUE;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_PLAN         = pstCalledPartyNum->enNumPlan;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_PLAN_Present = VOS_TRUE;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_TYPE         = pstCalledPartyNum->enNumType;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUMBER_TYPE_Present = VOS_TRUE;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_CHAR            = pstCalledPartyNum->ucDigitNum;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_CHAR_Present    = VOS_TRUE;
        stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->NUM_INCL            = VOS_TRUE;

        for (i = 0; i < pstCalledPartyNum->ucDigitNum; i++)
        {
            stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value
                                = EDAlloc(sizeof(ED_BYTE));

            if (VOS_NULL_PTR == stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value)
            {
                CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq: allocate p_Global_Emergency_Call_CHARI_data_value memory fail");
                FREE_c_r_dsch(&stMsgRDsch);
                return VOS_ERR;
            }

            *(stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->value)
                    = pstCalledPartyNum->aucDigit[i];

            if (XCC_XCALL_DIGIT_MODE_DTMF == enDigitMode)
            {
                 stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->usedBits
                                    = 4 ;
            }
            else
            {
                 stMsgRDsch.u.EFWIM->RECs.data[0]->Type_specific_fields.u.p_Global_Emergency_Call->CHARi.data[i]->usedBits
                                    = 8 ;
            }
        }
    }

    /* 编码L3 PDU */
    *pulL3PduBitLen                 = 0;
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeCschMsg
 功能描述  : 编码csch信道上的数据
 输入参数  : enMsgTag: 消息类型
             pstRDschMsg:待编码的消息
 输出参数  : pucBuff:编码后的码流
             pulBitDataLen:码流的bit长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeCschMsg(
    CAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM_UINT8        enMsgTag,
    c_r_csch_mini6                                  *pstRCschMsg,
    VOS_UINT8                                       *pucBuff,
    VOS_UINT32                                      *pulBitDataLen
)
{
    CS0005E_Details                     stDetail;
    VOS_INT32                           iEncodeRet;

    CNAS_XCC_SetCS0005EDetailPara(&stDetail, enMsgTag, CNAS_CCB_GetPRevInUse(), 0);

    /* 得到编码后的L3 PDU */
    iEncodeRet = CNAS_XCC_EncodeRCschMsg((char*)pucBuff, 0, pstRCschMsg, &stDetail);
    if (iEncodeRet < 0)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_EncodeCschMsg: CNAS_XCC_EncodeCschMsg return wrong: ", iEncodeRet);

        /* 编码失败，可维可测勾包 */
        CNAS_MNTN_LogEncodeAbnormalInfoInd(UEPS_PID_XCC, iEncodeRet, enMsgTag);

        return VOS_ERR;
    }

    /* 编码后的数据长度 */
    *pulBitDataLen = (VOS_UINT32)iEncodeRet;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeCschMsAckOrderMsg
 功能描述  : 对CSCH 的order msg 进行编码
 输入参数  : 无
 输出参数  : pucPdudata     - 输出的码流
             pulL3PduBitLen - 输出的码流长度
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeCschMsAckOrderMsg(
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{
    c_r_csch_ORDM                                          *pstORDM = VOS_NULL_PTR;
    c_r_csch_mini6                                          stMsgRCsch;
    VOS_UINT32                                              ulRslt;

    /* 初始化内存 */
    NAS_MEM_SET_S(&stMsgRCsch, sizeof(stMsgRCsch), 0, sizeof(stMsgRCsch));

    /* 分配ORDM结构 */
    SETPRESENT_c_r_csch_mini6_ORDM(&stMsgRCsch);

    pstORDM = stMsgRCsch.u.ORDM;

    if (VOS_NULL_PTR == pstORDM)
    {
        /* 防止外面空指针再次做释放 */
        stMsgRCsch.Present        = U_c_r_csch_mini6_NONE;

        return VOS_ERR;
    }

    /* 申请内存 */
    SETPRESENT_c_R_Orders_parameters_p_R_Generic_Order(&stMsgRCsch.u.ORDM->order.parameters);

    if (VOS_NULL_PTR == stMsgRCsch.u.ORDM->order.parameters.u.p_R_Generic_Order)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeCschMsAckOrderMsg: allocate memory fail");

        stMsgRCsch.u.ORDM->order.parameters.Present = U_c_R_Orders_parameters_NONE;

        FREE_c_r_csch_mini6(&stMsgRCsch);

        return VOS_ERR;
    }

    /* 先赋值 order code 和orderq */
    pstORDM->order.ORDER                                = CNAS_XCC_REV_ORDER_CODE_MS_ACKNOWLEDGEMENT;
    pstORDM->order.parameters.u.p_R_Generic_Order->ORDQ = 0;

    *pulL3PduBitLen                         = 0;
    ulRslt = CNAS_XCC_EncodeCschMsg(CAS_CNAS_1X_TX_COMMON_ORDER_MSG,
                                    &stMsgRCsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_csch_mini6(&stMsgRCsch);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_EncodeTxTchMSRejectOrderMsg
 功能描述  : RDSCH发送order消息公共处理函数
 输入参数  : enOrderCode    - 参见C.S0005 Table 2.7.3
             enORDQ         - 参见C.S0005 Table 2.7.3
             enRxTchMsgType - C.S0004-D Table 3.2.2.2.1.2-1
             pucPdudata     - 编码后的PDU
             pulL3PduBitLen - PDU的bit len
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_EncodeServiceOptionCtrlMsg(
    APS_XCC_PZID_INFO_NTF_STRU         *pstPzidInfo,
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;
    VOS_UINT8                           ucOctectLen;

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* 分配c_r_dsch_FWIM结构 */
    SETPRESENT_c_r_dsch_SOCM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.SOCM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "v: allocate c_r_dsch_FWIM memory fail");
        return VOS_ERR;
    }


    stMsgRDsch.u.SOCM->CON_REF        = ucConRef;
    stMsgRDsch.u.SOCM->SERVICE_OPTION = pstPzidInfo->usSo;

    if (pstPzidInfo->ucPzidReportLen > CNAS_XCC_MAX_PKT_ZONE_LIST_LEN)
    {
        pstPzidInfo->ucPzidReportLen = CNAS_XCC_MAX_PKT_ZONE_LIST_LEN;
    }

    /*
    Field               Length (bits)
    PKT_CON_RESP        3
    RESERVED            2
    FIELD_TYPE          3
    RESERVED            4
    PKT_ZONE_LIST_LEN   4
    The mobile station shall include PKT_ZONE_LIST_LEN
    occurrences of the following record:
    PACKET_ZONE_ID      8
    */

    stMsgRDsch.u.SOCM->Type_specific_fields.usedBits = (CNAS_XCC_PKT_CON_RESP_HEADER_LEN * CNAS_XCC_OCTET_LEN_8_BIT)
                                                      + (pstPzidInfo->ucPzidReportLen * CNAS_XCC_OCTET_LEN_8_BIT)
                                                      + CNAS_XCC_OCTET_LEN_8_BIT;


    stMsgRDsch.u.SOCM->CTL_REC_LEN    = (VOS_UINT8)(stMsgRDsch.u.SOCM->Type_specific_fields.usedBits / CNAS_XCC_OCTET_LEN_8_BIT);
    stMsgRDsch.u.SOCM->Type_specific_fields.value    = EDAlloc(stMsgRDsch.u.SOCM->CTL_REC_LEN);
    if (VOS_NULL_PTR == stMsgRDsch.u.SOCM->Type_specific_fields.value)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeServiceOptionCtrlMsg: allocate Type_specific_fields memory fail");
        FREE_c_r_dsch(&stMsgRDsch);
        return VOS_ERR;
    }

    ucOctectLen = 0;
    stMsgRDsch.u.SOCM->Type_specific_fields.value[ucOctectLen++] = (VOS_UINT8)CNAS_XCC_RDSCH_SO_CTRL_FIELD_PKT_CON_RESP;
    stMsgRDsch.u.SOCM->Type_specific_fields.value[ucOctectLen++] = pstPzidInfo->ucPzidReportLen;
    NAS_MEM_CPY_S(&stMsgRDsch.u.SOCM->Type_specific_fields.value[ucOctectLen],
                  stMsgRDsch.u.SOCM->CTL_REC_LEN,
                  pstPzidInfo->aucPzid,
                  pstPzidInfo->ucPzidReportLen);

    /* 编码L3 PDU */
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_SERVICE_OPTION_CONTROL_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_IsL3ErrReOrigCount
 功能描述  : 是否将重拨的次数进行转换
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsL3ErrReOrigCount()
{
   return (CNAS_XCC_GetCtxAddr()->stCallNvimCfg.ucIsL3ErrReOrigCount);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ConvertReOrigCount
 功能描述  : 重拨次数转换
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_ConvertL3ErrReOrigCount(
    VOS_UINT8                           ReOrigCount
)
{
    switch(ReOrigCount)
    {
        case CNAS_XCC_RE_ORIG_COUNT_0:
            return CNAS_XCC_RE_ORIG_COUNT_0;

        case CNAS_XCC_RE_ORIG_COUNT_1:
        case CNAS_XCC_RE_ORIG_COUNT_2:
        case CNAS_XCC_RE_ORIG_COUNT_3:
        case CNAS_XCC_RE_ORIG_COUNT_4:
            return CNAS_XCC_RE_ORIG_COUNT_1;

        case CNAS_XCC_RE_ORIG_COUNT_5:
        case CNAS_XCC_RE_ORIG_COUNT_6:
        case CNAS_XCC_RE_ORIG_COUNT_7:
        case CNAS_XCC_RE_ORIG_COUNT_8:
            return CNAS_XCC_RE_ORIG_COUNT_2;

        default:
            return CNAS_XCC_RE_ORIG_COUNT_3;

    }
}




VOS_VOID CNAS_XCC_SendComDschDataRejectOrder(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU                         *pst1xDschDataInd,
    VOS_UINT8                                               ucConRef,
    CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8                  enRejectRevOrdq
)
{
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));
    NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

    stRejInfo.ucConRef          = ucConRef;
    stRejInfo.enRejRxTchMsgType = pst1xDschDataInd->enDschMsgType;
    stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
    stRejInfo.enRevOrdq         = enRejectRevOrdq;
    stRejInfo.ulL3PduBitLen     = 0;
    stRejInfo.pucPdudata        = aucPduData;

    if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pst1xDschDataInd->enDschMsgType)
    {
        NAS_MEM_SET_S(&stOrdrm, sizeof(CNAS_XCC_ORDRM_STRU), 0, sizeof(CNAS_XCC_ORDRM_STRU));

        CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm);
        stRejInfo.ucRejOrderCode    = stOrdrm.stOrder.ucOrder;
        stRejInfo.ucRejOrdq         = stOrdrm.stOrder.ucOrdq;
    }

    CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                               CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                               0,
                               (VOS_UINT16)stRejInfo.ulL3PduBitLen,
                               stRejInfo.pucPdudata);

    return;
}


VOS_UINT32  CNAS_XCC_ConvertBcdCodeToDtmfKey(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucAsciiCode
)
{
    if ((VOS_NULL_PTR == pucAsciiCode)
      ||(CNAS_XCC_DTMF_DIGIT_MIN > ucBcdCode)
      ||(CNAS_XCC_DTMF_DIGIT_MAX < ucBcdCode))
    {
        return VOS_ERR;
    }
    else
    {
        *pucAsciiCode = g_aucXccDtmfKeyMapTbl[ucBcdCode - 1];
    }

    return VOS_OK;
}


VOS_UINT32 CNAS_XCC_GetDigitAndSwitchFromORDQ(
    VOS_UINT8                           ucOrdq,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucSwitch
)
{
    /* Check the value (ucOrdq) in binary form as 11111111*/
    if (CNAS_XCC_CONT_DTMF_ORDQ_STOP == ucOrdq)
    {
        *pucSwitch = 0;
        return VOS_OK;
    }

    /* Check the value (ucOrdq) must be in the format of binary 0000nnnn, the value can be max 0x0F */
    if (CNAS_XCC_CONT_DTMF_ORDQ_START == (ucOrdq & 0xF0))
    {
        *pucSwitch = 1;
        return CNAS_XCC_ConvertBcdCodeToDtmfKey(ucOrdq, pucDigit);
    }

    return VOS_ERR;
}



VOS_UINT32 CNAS_XCC_EncodeSendContDTMFToneOrder(
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstContDtmfMsg,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen,
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRslt;
    c_r_dsch                            stMsgRDsch;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT8                           ucPRevInUse;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    NAS_MEM_SET_S(&stMsgRDsch, sizeof(c_r_dsch), 0x00, sizeof(c_r_dsch));

    /* Allocate memory for ORDM */
    SETPRESENT_c_r_dsch_ORDM(&stMsgRDsch);
    if (VOS_NULL_PTR == stMsgRDsch.u.ORDM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeSendContDTMFToneOrder: allocate memory fail");

        return VOS_ERR;
    }

    /* Set the PDu Bit length to zero */
    *pulL3PduBitLen = 0;

    /****************************************************************************************************
    If P_REV_IN_USEs is equal to or greater than seven, the mobile station shall perform the following:
    if this Call Control instance is identified by NULL,the mobile station shall either set the CON_REL_INCL field of the
    message to '0'or set the CON_REF_INCL fiels to 1 and set the CON_REF field to the connection reference of the service
    option connection corressponding to this call; otherwise,the mobile station shall set the CON_REL_INCL field of the.
    message to '1' and the CON_REF field of the message to the connection reference of the service option connection
    corresponding to this call
    *****************************************************************************************************/

    if (CNAS_XCC_INVALID_CON_REF != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef)
    {
        stMsgRDsch.u.ORDM->CON_REF         = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef;
        stMsgRDsch.u.ORDM->CON_REF_Present = ED_TRUE;
        stMsgRDsch.u.ORDM->CON_REF_INCL    = ED_TRUE;
    }

    ucPRevInUse = CNAS_CCB_GetPRevInUse();

    if (ucPRevInUse >= P_REV_IN_USE_7)
    {
        stMsgRDsch.u.ORDM->CON_REF_INCL_Present = ED_TRUE;
    }
    else
    {
        stMsgRDsch.u.ORDM->CON_REF_INCL_Present = ED_FALSE;
    }

    if ((ucPRevInUse < P_REV_IN_USE_7)
      ||(VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc))
    {
        stMsgRDsch.u.ORDM->CON_REF_INCL    = ED_FALSE;

        stMsgRDsch.u.ORDM->CON_REF_Present = ED_FALSE;
    }
    else
    {
        stMsgRDsch.u.ORDM->CON_REF_INCL    = ED_TRUE;
    }

    /* Allocate memory for parameter of the order */
    SETPRESENT_c_R_Orders_parameters_p_R_Generic_Order(&stMsgRDsch.u.ORDM->order.parameters);

    if (VOS_NULL_PTR == stMsgRDsch.u.ORDM->order.parameters.u.p_R_Generic_Order)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_EncodeSendContDTMFToneOrder: allocate memory fail");

        stMsgRDsch.u.ORDM->order.parameters.Present = U_c_R_Orders_parameters_NONE;

        FREE_c_r_dsch(&stMsgRDsch);

        return VOS_ERR;
    }

    stMsgRDsch.u.ORDM->order.ORDER          = CNAS_XCC_REV_ORDER_CODE_CONTINUOUS_DTMF_TONE;
    stMsgRDsch.u.ORDM->order.ADD_RECORD_LEN = 1;

    /* If the tone is start continuous DTMF tone order then convert the ASCII digit to Binary code and FILL ORDQ value
        else if the tone is stop continuous DTMF tone order then fill ORDQ value as "11111111" */
    if (XCALL_XCC_CONT_DTMF_START == pstContDtmfMsg->enSwitch)
    {
        ulRslt = CNAS_XCC_AsciiToBcdCode((VOS_CHAR)pstContDtmfMsg->ucDigit, &ucBcdCode);
        if (VOS_OK != ulRslt)
        {
            FREE_c_r_dsch(&stMsgRDsch);
            return ulRslt;
        }

        stMsgRDsch.u.ORDM->order.parameters.u.p_R_Generic_Order->ORDQ = ucBcdCode;
    }
    else
    {
        stMsgRDsch.u.ORDM->order.parameters.u.p_R_Generic_Order->ORDQ = CNAS_XCC_CONT_DTMF_ORDQ_STOP;
    }

    /* Encode DSCH message */
    ulRslt = CNAS_XCC_EncodeDschMsg(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                                    &stMsgRDsch,
                                    pucPdudata,
                                    pulL3PduBitLen);

    FREE_c_r_dsch(&stMsgRDsch);

    return ulRslt;

}


VOS_UINT32 CNAS_XCC_ConvertDtmfOffLengthToDtmfMinInterDigitInterval(
    VOS_UINT8                           ucDtmfOffLen,
    VOS_UINT32                         *pulDtmfMinInterDigitInterval
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ucDtmfOffLen)
    {
        case CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_0:
            *pulDtmfMinInterDigitInterval = CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_60;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_1:
            *pulDtmfMinInterDigitInterval = CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_100;
            break;

        case  CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_2:
            *pulDtmfMinInterDigitInterval = CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_150;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_3:
            *pulDtmfMinInterDigitInterval = CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_200;
            break;

        default:
            ulRslt = VOS_ERR;
            break;
    }

    return ulRslt;
}


VOS_UINT32 CNAS_XCC_ConvertDtmfOnLengthToDtmfPulseWidthCode(
    VOS_UINT8                           ucDtmfOnLen,
    VOS_UINT32                         *pulDtmfPulseWidth
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ucDtmfOnLen)
    {
        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_0:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_95;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_1:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_150;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_2:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_200;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_3:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_250;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_4:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_300;
            break;

        case CNAS_XCC_SEND_BURST_DTMF_ON_LEN_5:
            *pulDtmfPulseWidth = CNAS_XCC_DTMF_PULSE_WIDTH_350;
            break;

        default:
            ulRslt = VOS_ERR;
            break;
    }

    return ulRslt;
}


CNAS_XCC_DECODE_RESULT_ENUM_UINT8 CNAS_XCC_DecodeSndBurstDtmfMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd,
    CNAS_XCC_SEND_BURST_DTMF_STRU      *pstSndBurstDtmfMsg
)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stMsgFDsch;
    VOS_INT32                           lDecodeRslt;
    VOS_UINT32                          ulOnLength;
    VOS_UINT32                          ulOffLength;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucAsciiCode;

    NAS_MEM_SET_S(&stMsgFDsch, sizeof(c_f_dsch), 0, sizeof(c_f_dsch));

    /* fill the sturct of CS0005E_Details  */
    CNAS_XCC_SetCS0005EDetailPara((&stCS0005Detail),
                                    pst1xDschDataInd->enDschMsgType,
                                    CNAS_CCB_GetPRevInUse(),
                                    0);

    /* decode FDSCH MSG */
    lDecodeRslt = CNAS_XCC_DecodeFDschMsg((char*)(pst1xDschDataInd->aucMsgData),
                                           0,
                                           &stMsgFDsch,
                                           pst1xDschDataInd->usMsgDataLen,
                                           &stCS0005Detail);

    /* decode fail, release memory and return */
    if (lDecodeRslt < 0)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_DecodeSndBurstDtmfMsg: decode fail");

        /* log  abnormal info */
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                       lDecodeRslt,
                                       CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG);

        /* release the allocated memory */
        if (VOS_NULL_PTR != stMsgFDsch.u.BDTMFM)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        }

        return CNAS_XCC_DECODE_RSLT_FAILURE;
    }

    if (VOS_NULL_PTR == stMsgFDsch.u.BDTMFM)
    {
        CNAS_MNTN_LogDecodeAbnormalInfoInd(UEPS_PID_XCC,
                                    CNAS_XCC_DECODE_ERRCODE_BDTMFM_IS_NULL_PTR,
                                    CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG);

        return CNAS_XCC_DECODE_RSLT_INVALID_FIELD;
    }

    /* Get ON length and Off length values if ON length and off length values are not valid return error */
    ulRslt = CNAS_XCC_ConvertDtmfOnLengthToDtmfPulseWidthCode(stMsgFDsch.u.BDTMFM->DTMF_ON_LENGTH, &ulOnLength);
    if (VOS_OK != ulRslt)
    {
        CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        return CNAS_XCC_DECODE_RSLT_INVALID_FIELD;
    }

    ulRslt = CNAS_XCC_ConvertDtmfOffLengthToDtmfMinInterDigitInterval(stMsgFDsch.u.BDTMFM->DTMF_OFF_LENGTH, &ulOffLength);
    if (VOS_OK != ulRslt)
    {
        CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
        return CNAS_XCC_DECODE_RSLT_INVALID_FIELD;
    }

    pstSndBurstDtmfMsg->ulOffLength = ulOffLength;
    pstSndBurstDtmfMsg->ulOnLength  = ulOnLength;

    /* Get the conref value */
    pstSndBurstDtmfMsg->ucConRef    = (VOS_TRUE == stMsgFDsch.u.BDTMFM->CON_REF_Present) ? stMsgFDsch.u.BDTMFM->CON_REF : CNAS_XCC_INVALID_CON_REF;

    pstSndBurstDtmfMsg->ucDigitNum  = stMsgFDsch.u.BDTMFM->NUM_DIGITS;

    /* convert digits from binary code to ASCII code */
    for (ucLoop = 0; ucLoop < stMsgFDsch.u.BDTMFM->NUM_DIGITS; ucLoop++)
    {
        if (VOS_NULL_PTR == stMsgFDsch.u.BDTMFM->DIGITSs.data[ucLoop])
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
            return CNAS_XCC_DECODE_RSLT_INVALID_FIELD;
        }

        ulRslt = CNAS_XCC_ConvertBcdCodeToDtmfKey(stMsgFDsch.u.BDTMFM->DIGITSs.data[ucLoop]->DIGITi, &ucAsciiCode);
        if (VOS_OK != ulRslt)
        {
            CNAS_XCC_FreeFDschMsg(&stMsgFDsch);
            return CNAS_XCC_DECODE_RSLT_INVALID_FIELD;
        }

        pstSndBurstDtmfMsg->aucDigit[ucLoop]    = ucAsciiCode;
    }

    /* free the memory*/
    CNAS_XCC_FreeFDschMsg(&stMsgFDsch);

    return CNAS_XCC_DECODE_RSLT_SUCCESS;
}

/*****************************************************************************
Function Name   :   CNAS_XCC_DecodeConRefFromFDschOrdmMsg
Description     :   The function is used to extract the Con_Ref_Incl and Con_Ref from an FDsch Msg.
                    According to protocol, the Con_Ref_Incl and Con_Ref are present in the last 9 bits of the message.
                    The function reads the Last 9 bits of the Encoded message and finds the Con_Ref_Incl and Con_Ref.

Input parameters:   pucMsgData   - Input Encoded message bit stream
                    usMsgDataLen - The Bit Length of the Encoded message.

Output parameters:  pucConRefIncl - Set to VOS_TRUE if Con_Ref is present.
                    pucConRef     - Set to CON_REF value present in the message.

Return Value    :   NOne

Modify History  :
1)  Date           : 2015-07-31
    Author         : a00295761
    Modify content : Create

2.  日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_VOID CNAS_XCC_DecodeConRefFromFDschOrdmMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    VOS_UINT8                          *pucConRefIncl,
    VOS_UINT8                          *pucConRef
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT8                           ucBitOffset;
    VOS_UINT8                           ucConRefIncl;
    VOS_UINT8                           ucConRef;
    VOS_UINT8                           ucAddRecLen;
    VOS_UINT16                          usConRefInclBitPos;
    VOS_UINT8                           ucVal;

    /* Get the Additional record length from the Encoded message data */
    ucAddRecLen = CNAS_XCC_GetAddRecLenFromOrderMsg(pucMsgData);

    /* The ORDM Message in the forward DSCH channel will have the following structure

        Field               | Bit Len
       ------------------------------
       USE_TIME             | 1
       ACTION_TIME          | 6
       ORDER                | 6
       ADD_RECORD_LEN       | 3
       Order-specific_fields| 8 * ADD_RECORD_LEN
       CON_REF_INCL         | 0 or 1
       CON_REF              | 0 or 8  */

    usConRefInclBitPos = CNAS_XCC_BIT_LEN_16_BIT + (ucAddRecLen * CNAS_XCC_OCTET_BIT_LEN);

    /* If the Bit Position is equal to the Msg Data Len, the Con_Ref_Incl is absent. Hence return */
    if (usConRefInclBitPos == usMsgDataLen)
    {
         *pucConRefIncl = VOS_FALSE;
         *pucConRef     = 0;

          return;
    }

    /* ucIndex contains the Octet position at which the Con_Ref_Incl is present in the Encoded bit stream */
    usIndex     = usConRefInclBitPos / CNAS_XCC_OCTET_BIT_LEN;

    /* ucBitOffset contains the bit position in a byte, where Con_Ref_Incl bit is present */
    ucBitOffset = usConRefInclBitPos % CNAS_XCC_OCTET_BIT_LEN;

    /* Get the Con_Ref_Incl from the encoded message */
    ucConRefIncl = pucMsgData[usIndex] & (((VOS_UINT32)0x01) << (CNAS_XCC_OCTET_BIT_LEN - ucBitOffset - 1));

    if (VOS_FALSE == ucConRefIncl)
    {
        /* If the Con_Ref_Incl is zero, set the Con_Ref_Incl and Con_Ref to zero */
        *pucConRefIncl = VOS_FALSE;
        *pucConRef     = 0;

        return;
    }

    ucBitOffset++;

    /* Modulo with CNAS_XCC_OCTET_BIT_LEN, as the Bit Offset may move to next octet */
    ucBitOffset %= CNAS_XCC_OCTET_BIT_LEN;

    ucConRef = 0;

    /* The 8 bits after Con_Ref_Incl contains the CON_REF */
    ucConRef = pucMsgData[usIndex] & (0xFF >> (ucBitOffset));

    if (0 != (ucBitOffset % CNAS_XCC_OCTET_BIT_LEN))
    {
        /* In this case, the Con_Ref value is present in two Octets. Increment the Index to get the next octet */
        usIndex++;

        /* Shift ucConRef to the higher order bit position */
        ucConRef  = (VOS_UINT8) (((VOS_UINT32)ucConRef) << ucBitOffset);

        /* ucVal contains the part of Con_Ref present in the next octet. Extract the part of Con_Ref and store in ucVal*/
        ucVal = pucMsgData[usIndex] & (~(0xFF >> ucBitOffset));

        /* Shift the ucVal to the Lower order bit position */
        ucConRef |= ucVal >> (CNAS_XCC_OCTET_BIT_LEN - ucBitOffset);
    }

    *pucConRefIncl = VOS_TRUE;
    *pucConRef     = ucConRef;

    return;
}




VOS_UINT8 CNAS_XCC_GetAddRecLenFromOrderMsg(
    VOS_UINT8                          *pucMsgData
)
{
    VOS_UINT8                          ucAddRecLen;

    ucAddRecLen = 0;
    /* The ORDM Message in the forward DSCH channel will have the following structure

            Field               | Bit Len
           ------------------------------
           USE_TIME             | 1
           ACTION_TIME          | 6
           ORDER                | 6
           ADD_RECORD_LEN       | 3
           Order-specific_fields| 8 * ADD_RECORD_LEN
           CON_REF_INCL         | 0 or 1
           CON_REF              | 0 or 8  */

    /* Get the last Three bits of the second Octet of the Encoded message stream */
    ucAddRecLen = pucMsgData[1] & (0xFF >> CNAS_XCC_BIT_LEN_5_BIT);

    return ucAddRecLen;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsPagingRspSo33InNoDataSrv
 功能描述  : 没有数据业务时，paging rsp中是否带so33
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsPagingRspSo33InNoDataSrv(VOS_VOID)
{
    return (CNAS_XCC_GetCtxAddr()->stPagingRspSoCfg.ucNoDataSrvRspSo33Flg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndSessionBeginNtf
 功能描述  : 发送Session Begin消息
 输入参数  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID CNAS_XCC_SndSessionBeginNtf(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
)
{
    TAF_CTRL_STRU                                           stCtrl;
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enCasSessionType;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType;

    NAS_MEM_SET_S(&stCtrl, sizeof(TAF_CTRL_STRU), 0x00, sizeof(TAF_CTRL_STRU));
    stCtrl.ulModuleId                   = UEPS_PID_XCC;
    enCasSessionType                    = CNAS_CAS_1X_SESSION_TYPE_ENUM_BUTT;
    enMtcSessionType                    = MTC_SESSION_TYPE_BUTT;

    /* 获取Cas Session类型 */
    CNAS_XCC_ConvertSoToCasSessionType(enSo, &enCasSessionType);

    /* 向CAS申请射频资源 */
    CNAS_XCC_SndCasBeginSessionNotify(enCasSessionType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 获取MTC 的Session类型 */
    CNAS_XCC_ConvertSoToMtcSessionType(enSo, &enMtcSessionType);

    /* 通知MTC Session Type */
    MTC_SetBeginSessionInfo(&stCtrl, enMtcSessionType);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndSessionEndNtf
 功能描述  : 发送Session End消息
 输入参数  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID CNAS_XCC_SndSessionEndNtf(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
)
{
    TAF_CTRL_STRU                                           stCtrl;
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enCasSessionType;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType;

    NAS_MEM_SET_S(&stCtrl, sizeof(TAF_CTRL_STRU), 0x00, sizeof(TAF_CTRL_STRU));
    stCtrl.ulModuleId                   = UEPS_PID_XCC;
    enCasSessionType                    = CNAS_CAS_1X_SESSION_TYPE_ENUM_BUTT;
    enMtcSessionType                    = MTC_SESSION_TYPE_BUTT;

    /* 获取Cas Session类型 */
    CNAS_XCC_ConvertSoToCasSessionType(enSo, &enCasSessionType);

    /* 向CAS申请射频资源 */
    CNAS_XCC_SndCasEndSessionNotify(enCasSessionType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 获取MTC 的Session类型 */
    CNAS_XCC_ConvertSoToMtcSessionType(enSo, &enMtcSessionType);

    /* 通知MTC Session Type */
    MTC_SetEndSessionInfo(&stCtrl, enMtcSessionType);
#endif

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
