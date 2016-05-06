/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsSndAt.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年08月25日
  功能描述   : 发送消息给AT模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月25日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsSndAt.h"
#include "AtXpdsInterface.h"
#include "TafXpdsMntn.h"
#include "cprocstime.h"
#include "NasOmTrans.h"
#include "TafXpdsCtx.h"
#include "TafXpdsCommFunc.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_SND_AT_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XPDS_FillMpcStartPosReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_FillMpcStartPosReq
(
    TAF_XPDS_MPC_START_POS_REQ_STRU                   *pstStartPosReq
)
{
    pstStartPosReq->ucVersion       = TAF_XPDS_CUR_VERSION;
    pstStartPosReq->enMsgType       = ID_TAF_XPDS_MS_TO_MPC_START_POS_REQ;

    /* 能力下发 to be checked in IT2*/
    pstStartPosReq->enMsPosCap      = TAF_XPDS_MS_POS_CAPABILITY_BOTH;

    /* 那个APP发起 TO DO  */
    if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
    {
        pstStartPosReq->enAppTypeIndicator  = TAF_XPDS_APP_TYPE_INDICATOR_NETWORK_INITIATED;
    }
    else
    {
        pstStartPosReq->enAppTypeIndicator  = TAF_XPDS_APP_TYPE_INDICATOR_MS_RESIDENT;
    }

    /* 1.0 if ni process ,the value is in mt pos req
       2.0 if java it is a default value
       3.0 other app should get from ap */
    if (TAF_XPDS_APP_TYPE_INDICATOR_NETWORK_INITIATED == pstStartPosReq->enAppTypeIndicator)
    {
        if (1 == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucPosQoSInc)
        {
            pstStartPosReq->ucPQoS = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucPosQoS;
        }
        else
        {
             pstStartPosReq->ucPQoS = 0;
        }

        pstStartPosReq->ucCorrelationId = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;

        if (1 == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usNumOfFixs)
        {
            pstStartPosReq->ulDuration = 0;
        }
        else
        {
            pstStartPosReq->ulDuration = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usTimeBetweenFixs *
                                         TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usNumOfFixs;
        }
    }
    else
    {
        /* to do */
        pstStartPosReq->ucPQoS          = (VOS_UINT8)TAF_XPDS_GetAgpsCfg()->ulQosPerformance;

        pstStartPosReq->ucCorrelationId = TAF_XPDS_GetCorrelationId();

        /* ulDuration: WAP: 0 SINGLE-SHOT FIX: 0 SUCC_TRACKING: 1- XXX to be checked*/
        if (1 == TAF_XPDS_GetAgpsCfg()->usFixNum)
        {
            pstStartPosReq->ulDuration      = 0;
        }
        else
        {
            pstStartPosReq->ulDuration      = (VOS_UINT32)(TAF_XPDS_GetAgpsCfg()->ulFixRateTime * \
                                                TAF_XPDS_GetAgpsCfg()->usFixNum);
        }

    }

    /* MS_ID_REC TO DO */
    TAF_XPDS_EncodeMsIdRec(&pstStartPosReq->stMsIdRec);

    pstStartPosReq->usSID         = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstStartPosReq->usNID         = (VOS_UINT16)TAF_SDC_Get1xNid();
    pstStartPosReq->ulBaseID      = TAF_SDC_Get1xSysInfo()->stBaseStationInfo.usBaseId;
    pstStartPosReq->ulBaseLat     = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLatitude;
    pstStartPosReq->ulBaseLong    = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLongitude;

    /* get from page channel to be checked*/
    pstStartPosReq->usRefPn       = TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn;

    pstStartPosReq->usBandClass   = TAF_SDC_Get1xSysInfo()->usBandClass;
    pstStartPosReq->ulCdmaFreq    = TAF_SDC_Get1xSysInfo()->usFreq;

    /* time stamp need to do */
    TAF_XPDS_SetTimeStamp(&pstStartPosReq->stTimeStamp);

#if 0
    if (TAF_XPDS_APP_TYPE_INDICATOR_BREW == pstStartPosReq->enAppTypeIndicator)
    {
        /* ulBrewAppID to do */

        /* stAPPIDREC to do*/
    }
#endif
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_FillMpcPosReportReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_FillMpcPosReportReq
(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
)
{
    pstPosReportReq->ucVersion       = TAF_XPDS_CUR_VERSION;
    pstPosReportReq->enMsgType       = ID_TAF_XPDS_MS_TO_MPC_POS_REPORT;

    pstPosReportReq->usCorrelationId = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;

    /* need to do */
    pstPosReportReq->usFixNum        = TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum;

    /* MS_ID_REC TO DO */
    TAF_XPDS_EncodeMsIdRec(&pstPosReportReq->stMsIdRec);

    pstPosReportReq->usSID         = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstPosReportReq->usNID         = (VOS_UINT16)TAF_SDC_Get1xNid();
    pstPosReportReq->ulBaseID      = TAF_SDC_Get1xSysInfo()->stBaseStationInfo.usBaseId;
    pstPosReportReq->ulBaseLat     = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLatitude;
    pstPosReportReq->ulBaseLong    = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLongitude;

    /* get from page channel to be checked*/
    pstPosReportReq->usRefPn       = TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn;

    pstPosReportReq->usBandClass   = TAF_SDC_Get1xSysInfo()->usBandClass;
    pstPosReportReq->ulCdmaFreq    = TAF_SDC_Get1xSysInfo()->usFreq;

    /* time stamp need to do */
    TAF_XPDS_SetTimeStamp(&pstPosReportReq->stCellIdTimeStamp);

    TAF_XPDS_SetTimeStamp(&pstPosReportReq->stPosTimeStamp);

    /* 有无位置信息 */
    TAF_XPDS_SetPosReportLocInfo(pstPosReportReq);

    /* 位置信息需要重新考虑 */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CalcTimeInWeek
 功能描述  : 相对于当前周的时间
 输入参数  : ulRefTime
 输出参数  : 无
 返 回 值  : 相对于当前周的毫秒时间
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_CalcTimeInWeek(VOS_UINT32 ulRefTime)
{
    VOS_UINT64                          ulCurrTime64;
    VOS_UINT64                          ulStdTime64;
    VOS_UINT64                          ulStartTime64;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD);
    }
    else
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);
    }

    /* 先转化为毫秒 */
    ulCurrTime64 = ulCurrTime64 * 80;

    /* RegTime单位为1.28s */
    ulRefTime    = ulRefTime * 1280;

    /* 基础时间点是以320s为间隔 */
    ulStdTime64  = ulCurrTime64 - ulCurrTime64 % (320 * 1000);

    if ((ulStdTime64 + ulRefTime) > ulCurrTime64)
    {
        ulStartTime64 = (ulStdTime64 - (320 * 1000)) + ulRefTime;
    }
    else
    {
        ulStartTime64 = ulStdTime64 + ulRefTime;
    }

    /* 相对当前周的毫秒 */
    return (VOS_UINT32)(ulStartTime64 % (7*24*3600*1000));
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_CalcAbsTime
 功能描述  : 计算当前的绝对时间
 输入参数  : ulRefTime
 输出参数  : 无
 返 回 值  : 以毫秒为单位的绝对时间
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT64 TAF_XPDS_CalcAbsTime(VOS_UINT32 ulRefTime)
{
    VOS_UINT64                          ulCurrTime64;
    VOS_UINT64                          ulStdTime64;
    VOS_UINT64                          ulStartTime64;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD);
    }
    else
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);
    }

    /* 先转化为毫秒 */
    ulCurrTime64 = ulCurrTime64 * 80;

    /* RegTime单位为1s */
    ulRefTime    = ulRefTime * 1000;

    /* 转换为基准时间点,以16384s为间隔 */
    ulStdTime64 = ulCurrTime64 - ulCurrTime64 % (16384 * 1000);

    if ((ulStdTime64 + ulRefTime) > ulCurrTime64)
    {
        ulStartTime64 = (ulStdTime64 - (16384 * 1000)) + ulRefTime;
    }
    else
    {
        ulStartTime64 = ulStdTime64 + ulRefTime;
    }

    return ulStartTime64;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtMsg
 功能描述  : XPDS发送msg至AT的模板
 输入参数  : AT_APPCTRL_STRU                    *pAppCtrl
             VOS_UINT32                          ulMsgId
             VOS_UINT32                          ulLen
             VOS_UINT8                          *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtMsg(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;

    /* 判断输入参数 */
    if ((VOS_NULL_PTR == pData) || (0 == ulLen))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg: para is invalid!");
        return;
    }

    /* 消息空间申请 */
    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS,
                                                 sizeof(AT_APPCTRL_STRU) + sizeof(ulMsgId) + ulLen);
    if (VOS_NULL_PTR == pstMsgStr)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg: alloc msg fail!");
        return;
    }

    /* 填消息包 */
    pstMsgStr->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderPid           = UEPS_PID_XPDS;
    pstMsgStr->ulReceiverPid         = WUEPS_PID_AT;
    pstMsgStr->ulMsgId               = ulMsgId;
    pstMsgStr->stAppCtrl.usClientId  = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgStr->stAppCtrl.ucOpId      = pAppCtrl->ucOpId;
    pstMsgStr->stAppCtrl.aucReserved[0] = 0;
    PS_MEM_CPY(pstMsgStr->aucContent, pData, ulLen);

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStr))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtMsgNoData
 功能描述  : 发送给AT不带数据内容的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : g00256031
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtMsgNoData(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;


    /* 消息空间申请 */
    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS,
                                                 sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsgStr)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsgNoData: alloc msg fail!");
        return;
    }

    /* 填消息包 */
    pstMsgStr->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderPid           = UEPS_PID_XPDS;
    pstMsgStr->ulReceiverPid         = WUEPS_PID_AT;
    pstMsgStr->ulLength              = (sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH) - 4; /* 需要减去消息中的aucContent字段长度 */
    pstMsgStr->ulMsgId               = ulMsgId;
    pstMsgStr->stAppCtrl.usClientId  = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgStr->stAppCtrl.ucOpId      = pAppCtrl->ucOpId;
    pstMsgStr->stAppCtrl.aucReserved[0] = 0;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStr))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsgNoData():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsStartReq
 功能描述  :
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : g00256031
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsStartReq(
    AT_APPCTRL_STRU                    *pAppCtrl
)
{
    XPDS_AT_GPS_START_REQ_STRU         *pstMsgStartReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 消息空间申请 */
    pstMsgStartReq = (XPDS_AT_GPS_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStartReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsStartReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStartReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgStartReq->stAppCtrl.usClientId = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgStartReq->stAppCtrl.ucOpId     = pAppCtrl->ucOpId;

    /* 填消息包 */
    pstMsgStartReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStartReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStartReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgStartReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgStartReq->ulMsgId         = ID_XPDS_AT_GPS_START_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStartReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsStartReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApOpenCagpsDataCall
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApOpenCagpsDataCall(VOS_VOID)
{
    XPDS_AT_AP_DATA_CALL_REQ_STRU      *pstMsgDataCallReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_AP_DATA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgDataCallReq = (XPDS_AT_AP_DATA_CALL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgDataCallReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApOpenCagpsDataCall: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgDataCallReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgDataCallReq->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    pstMsgDataCallReq->enAgpsMode = TAF_XPDS_GetCgpsInitialType();
    pstMsgDataCallReq->enAgpsOper = AT_XPDS_AGPS_DATA_CALL_CTRL_CONNECT;

    /* 填消息包 */
    pstMsgDataCallReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgDataCallReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgDataCallReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgDataCallReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgDataCallReq->ulMsgId         = ID_XPDS_AT_AP_DATA_CALL_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgDataCallReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApOpenCagpsDataCall():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApCloseCagpsDataCall
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApCloseCagpsDataCall(VOS_VOID)
{
    XPDS_AT_AP_DATA_CALL_REQ_STRU      *pstMsgDataCallReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_AP_DATA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgDataCallReq = (XPDS_AT_AP_DATA_CALL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgDataCallReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApCloseCagpsDataCall: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgDataCallReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgDataCallReq->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetApClientId(), UEPS_PID_XPDS);

    pstMsgDataCallReq->enAgpsMode = TAF_XPDS_GetCgpsInitialType();
    pstMsgDataCallReq->enAgpsOper = AT_XPDS_AGPS_DATA_CALL_CTRL_RELEASE;

    /* 填消息包 */
    pstMsgDataCallReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgDataCallReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgDataCallReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgDataCallReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgDataCallReq->ulMsgId         = ID_XPDS_AT_AP_DATA_CALL_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgDataCallReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApCloseCagpsDataCall():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApOpenSocketReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApOpenSocketReq(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
)
{
    XPDS_AT_AP_SERVER_BIND_REQ_STRU    *pstMsgBindReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_AP_SERVER_BIND_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgBindReq = (XPDS_AT_AP_SERVER_BIND_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgBindReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApOpenSocketReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgBindReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgBindReq->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetApClientId(), UEPS_PID_XPDS);

    pstMsgBindReq->enDataCallCtrl = AT_XPDS_AGPS_DATA_CALL_CTRL_CONNECT;
    pstMsgBindReq->enServerMode   = enServerMode;
    pstMsgBindReq->ulIpAddr       = ulIpAddr;
    pstMsgBindReq->ulPortNum      = ulPortNum;

    /* 填消息包 */
    pstMsgBindReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgBindReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgBindReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgBindReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgBindReq->ulMsgId         = ID_XPDS_AT_AP_SERVER_BIND_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgBindReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApOpenSocketReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApCloseSocketReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApCloseSocketReq(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
)
{
    XPDS_AT_AP_SERVER_BIND_REQ_STRU    *pstMsgBindReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_AP_SERVER_BIND_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgBindReq = (XPDS_AT_AP_SERVER_BIND_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgBindReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApCloseSocketReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgBindReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgBindReq->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetApClientId(), UEPS_PID_XPDS);

    pstMsgBindReq->enDataCallCtrl = AT_XPDS_AGPS_DATA_CALL_CTRL_RELEASE;
    pstMsgBindReq->enServerMode   = enServerMode;
    pstMsgBindReq->ulIpAddr       = ulIpAddr;
    pstMsgBindReq->ulPortNum      = ulPortNum;

    /* 填消息包 */
    pstMsgBindReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgBindReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgBindReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgBindReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgBindReq->ulMsgId         = ID_XPDS_AT_AP_SERVER_BIND_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgBindReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApCloseSocketReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsTimeSyncInfo
 功能描述  : XPDS给AT模块上报获取Sync timer结果
 输入参数  : pstRcvSyncTime : Cas上报sync time结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsTimeSyncInfo(
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime
)
{
    XPDS_AT_GPS_SYNC_TIME_IND_STRU     *pstMsgSyncTimeInd;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_SYNC_TIME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgSyncTimeInd = (XPDS_AT_GPS_SYNC_TIME_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgSyncTimeInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsTimeSyncInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgSyncTimeInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgSyncTimeInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    if (XPDS_CAS_RESULT_NO_ERROR == pstRcvSyncTime->enResult)
    {
        pstMsgSyncTimeInd->enResult  = XPDS_AT_SYNC_TIME_VALID;
    }
    else
    {
        /* 异常回复AP协商错误值 */
        pstMsgSyncTimeInd->enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }

    PS_MEM_CPY((VOS_UINT8*)pstMsgSyncTimeInd->aulPulseTime,
               (VOS_UINT8*)pstRcvSyncTime->aulPulseTime,
               2 * sizeof(VOS_UINT32));

#if 0 /* modem不具备这样精度的计算能力，直接透传 */
    /* GPS需要的单位是ns,cas上报的时1/16chip = 50.863ns */
    ulRet = VOS_64Multi32(pstRcvSyncTime->aulPulseTime[1],
                          pstRcvSyncTime->aulPulseTime[0],
                          51,
                          &stSyncTimeInfo.aulPulseTime[1],
                          &stSyncTimeInfo.aulPulseTime[0]);
    if (VOS_OK != ulRet)
    {
        /* 回复无效值 */
        pstMsgSyncTimeInd->enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }

    ulRet = VOS_64Div32(aulPulseTimeTemp[1],
                        aulPulseTimeTemp[0],
                        1000,
                        &pstMsgSyncTimeInd->aulPulseTime[1],
                        &pstMsgSyncTimeInd->aulPulseTime[0],
                        VOS_NULL_PTR);

    if (VOS_OK != ulRet)
    {
        /* 回复无效值 */
        pstMsgSyncTimeInd->enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }
#endif

    /* 填消息包 */
    pstMsgSyncTimeInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgSyncTimeInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgSyncTimeInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgSyncTimeInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgSyncTimeInd->ulMsgId         = ID_XPDS_AT_GPS_TIME_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgSyncTimeInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsTimeSyncInfo():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsReflocInfoCnf
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsReflocInfoCnf(
    AT_APPCTRL_STRU                    *pstAppCtrl,
    XPDS_AT_GPS_REFLOC_INFO_STRU       *pstRefloc
)
{
    XPDS_AT_GPS_REFLOC_INFO_CNF_STRU   *pstMsgRefLocCnf;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_REFLOC_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgRefLocCnf = (XPDS_AT_GPS_REFLOC_INFO_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgRefLocCnf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsReflocInfoCnf: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgRefLocCnf + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgRefLocCnf->stAppCtrl.usClientId = MN_GetRealClientId(pstAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgRefLocCnf->stAppCtrl.ucOpId     = pstAppCtrl->ucOpId;

    PS_MEM_CPY(&(pstMsgRefLocCnf->stRefLoc), pstRefloc, sizeof(XPDS_AT_GPS_REFLOC_INFO_STRU));

    /* 填消息包 */
    pstMsgRefLocCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgRefLocCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgRefLocCnf->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgRefLocCnf->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgRefLocCnf->ulMsgId         = ID_XPDS_AT_GPS_REFLOC_INFO_CNF;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgRefLocCnf))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsReflocInfoCnf():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApMpcStartPosReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApMpcStartPosReq
(
    VOS_VOID
)
{
    TAF_XPDS_MPC_START_POS_REQ_STRU     stStartPosReq;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[TAF_XPDS_MAX_DATA_LEN];

    PS_MEM_SET(&stStartPosReq, 0, sizeof(TAF_XPDS_MPC_START_POS_REQ_STRU));
    PS_MEM_SET(aucData, 0x00, TAF_XPDS_MAX_DATA_LEN);

    TAF_XPDS_FillMpcStartPosReq(&stStartPosReq);

    TAF_XPDS_MNTN_TraceReverseMpcStartPosReq(&stStartPosReq);

    TAF_XPDS_EncodeMpcStartPosReq(&stStartPosReq,
                                  &ulDataLen,
                                  aucData);

    TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_MPC, aucData, ulDataLen);

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndMpcPosReportReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApMpcPosReportReq
(
    VOS_VOID
)
{
    TAF_XPDS_MPC_POS_REPORT_STRU        stPosReportReq;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[TAF_XPDS_MAX_DATA_LEN];

    PS_MEM_SET(&stPosReportReq, 0, sizeof(TAF_XPDS_MPC_POS_REPORT_STRU));
    PS_MEM_SET(aucData, 0x00, TAF_XPDS_MAX_DATA_LEN);

    TAF_XPDS_FillMpcPosReportReq(&stPosReportReq);

    TAF_XPDS_MNTN_TraceReverseMpcPosReportReq(&stPosReportReq);

    TAF_XPDS_EncodeMpcPosReportReq(&stPosReportReq,
                                   &ulDataLen,
                                   aucData);

    TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_MPC, aucData, ulDataLen);

    return ;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApPdeSessionEndMsg
 功能描述  : During MSA, When Got Loc Rsp, MS can end Session
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApPdeSessionEndMsg(VOS_VOID)
{
    TAF_XPDS_PD_MSG_HEADER_STRU                stPdMsgHeader;
    VOS_UINT8                                 *pucMsgBuff;
    VOS_UINT32                                 ulTotLength;
    VOS_UINT32                                 ulTempLen;

    /* allocate memory for the message */
    pucMsgBuff  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucMsgBuff)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApPdeSessionEndMsg, malloc failed");

        return;
    }

    PS_MEM_SET(pucMsgBuff, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    PS_MEM_SET(&stPdMsgHeader, 0x00, sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));

    stPdMsgHeader.ucSessStart  = 0;
    stPdMsgHeader.ucSessEnd    = 1;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();
    stPdMsgHeader.ucPdMsgType = 0;

    /* number of req and response is 0 as of now in session end message */
    stPdMsgHeader.ucNumOfReq   = 0;
    stPdMsgHeader.ucNumOfResp  = 1;

    ulTotLength              = 0;
    ulTempLen                = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;
    ulTempLen    = 0;

    TAF_XPDS_EncodeProvMsInfo(pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;

    /* update the length field of data burst message */
    pucMsgBuff[0] = (VOS_UINT8)ulTotLength;

    ulTotLength += 1;

    /* need to send message to PDE */
    TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_PDE, pucMsgBuff, ulTotLength);

    /* freeing the memory */
    PS_MEM_FREE(UEPS_PID_XPDS, pucMsgBuff);
}

/*****************************************************************************
 Func Name    : TAF_XPDS_SndAtApPdeRejectRsp
 Description  : Function for sending different messages after processing
                PDE message buffer

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApPdeRejectRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU                       *pstRejInfo
)
{
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
    VOS_UINT8                           aucSendData[TAF_XPDS_MAX_PDM_MSG_BUF_LEN];
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulTempLen;

    PS_MEM_SET(aucSendData, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    /* 构造Posotion Determination Data Message header */
    PS_MEM_SET(&stPdMsgHeader, 0, sizeof(stPdMsgHeader));

    stPdMsgHeader.ucSessStart = 0;
    stPdMsgHeader.ucSessEnd   = 0;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();

    stPdMsgHeader.ucPdMsgType = 0;

    stPdMsgHeader.ucNumOfReq  = 0;
    stPdMsgHeader.ucNumOfResp = 1;

    ulDataLen  = 0;
    ulTempLen  = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    /* First Session Header */
    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, &aucSendData[1], &ulTempLen);

    ulDataLen  += ulTempLen;
    ulTempLen   = 0;

    TAF_XPDS_EncodeReject(pstRejInfo, &aucSendData[ulDataLen + 1], &ulTempLen);

    ulDataLen += ulTempLen;

    aucSendData[0] = (VOS_UINT8)(ulDataLen);

    /* add the first byte */
    ulDataLen  += 1;

    TAF_XPDS_MNTN_TraceReversePdeRejRsp(pstRejInfo);

    /* After encode work, Snd msg to AP */
    TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_PDE, aucSendData, ulDataLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtApReverseData
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtApReverseData
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLen
)
{
    XPDS_AT_AP_REVERSE_DATA_IND_STRU   *pstMsgReverseDataInd;
    VOS_UINT32                          ulMsgLength;

    if (ulLen >= 4)
    {
        ulMsgLength = sizeof(XPDS_AT_AP_REVERSE_DATA_IND_STRU) + ulLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(XPDS_AT_AP_REVERSE_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsgReverseDataInd = (XPDS_AT_AP_REVERSE_DATA_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgReverseDataInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApReverseData: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgReverseDataInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgReverseDataInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetApClientId(), UEPS_PID_XPDS);

    pstMsgReverseDataInd->enServerMode  = enServerMode;
    pstMsgReverseDataInd->ulDataLen     = ulLen;

    PS_MEM_CPY(pstMsgReverseDataInd->aucData, pucData, ulLen);

    /* 填消息包 */
    pstMsgReverseDataInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgReverseDataInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgReverseDataInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgReverseDataInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgReverseDataInd->ulMsgId         = ID_XPDS_AT_AP_REVERSE_DATA_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgReverseDataInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApReverseData():WARNING:SEND MSG FIAL");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsAbortPosInd
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsAbortPosInd(
    XPDS_AT_ABORT_POS_REASON_ENUM_UINT16                    enAbortReason
)
{
    XPDS_AT_GPS_ABORT_IND_STRU                             *pstMsgAbortInd;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_ABORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgAbortInd = (XPDS_AT_GPS_ABORT_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgAbortInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAbortPosInd: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgAbortInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgAbortInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);
    pstMsgAbortInd->enAbortReason        = enAbortReason;

    /* 填消息包 */
    pstMsgAbortInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgAbortInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgAbortInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgAbortInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgAbortInd->ulMsgId         = ID_XPDS_AT_GPS_ABORT_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgAbortInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAbortPosInd():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsStopCnf
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsStopCnf(VOS_VOID)
{
    XPDS_AT_RESULT_CNF_STRU            *pstMsgRsltCnf;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_RESULT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgRsltCnf = (XPDS_AT_RESULT_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgRsltCnf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsStopCnf: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgRsltCnf + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgRsltCnf->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstMsgRsltCnf->enResult = XPDS_AT_RESULT_NO_ERROR;

    /* 填消息包 */
    pstMsgRsltCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgRsltCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgRsltCnf->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgRsltCnf->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgRsltCnf->ulMsgId         = ID_XPDS_AT_GPS_STOP_CNF;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgRsltCnf))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsStopCnf():WARNING:SEND MSG FIAL");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsNiSessionInd
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsNiSessionInd(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU    *pstXsmsMsg
)
{
    XPDS_AT_GPS_NI_SESSION_IND_STRU    *pstMsgNiInd;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_NI_SESSION_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgNiInd = (XPDS_AT_GPS_NI_SESSION_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgNiInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsNiSessionInd: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgNiInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgNiInd->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    pstMsgNiInd->ucLen              = pstXsmsMsg->ucLen;
    pstMsgNiInd->enNotificationInd  = pstXsmsMsg->enNotificationInd;
    pstMsgNiInd->enPosTechInd       = pstXsmsMsg->enPosTechInd;
    pstMsgNiInd->ucPosQoSInc        = pstXsmsMsg->ucPosQoSInc;
    pstMsgNiInd->ucPosQoS           = pstXsmsMsg->ucPosQoS;
    pstMsgNiInd->enIS801PosMode     = pstXsmsMsg->enIS801PosMode;
    pstMsgNiInd->usNumOfFixs        = pstXsmsMsg->usNumOfFixs;
    pstMsgNiInd->usTimeBetweenFixs  = pstXsmsMsg->usTimeBetweenFixs;
    pstMsgNiInd->ucCorrelationId    = pstXsmsMsg->ucCorrelationId;
    pstMsgNiInd->ucReqIdEncode      = pstXsmsMsg->ucReqIdEncode;
    pstMsgNiInd->ucReqIdLen         = pstXsmsMsg->ucReqIdLen;

    PS_MEM_CPY(pstMsgNiInd->aucData, pstXsmsMsg->aucData, pstMsgNiInd->ucReqIdLen);

    /* 填消息包 */
    pstMsgNiInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgNiInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgNiInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgNiInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgNiInd->ulMsgId         = ID_XPDS_AT_GPS_NI_SESSION_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgNiInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsNiSessionInd():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsCancelNiSession
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsCancelNiSession(
    VOS_VOID
)
{
    XPDS_AT_GPS_CANCEL_IND_STRU        *pstMsgCancelInd;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_CANCEL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgCancelInd = (XPDS_AT_GPS_CANCEL_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgCancelInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCancelNiSession: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgCancelInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgCancelInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstMsgCancelInd->ulData      = 1;

    /* 填消息包 */
    pstMsgCancelInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgCancelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgCancelInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgCancelInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgCancelInd->ulMsgId         = ID_XPDS_AT_GPS_CANCEL_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgCancelInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCancelNiSession():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsCpNiStart
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsCpNiStart(
    VOS_VOID
)
{
    XPDS_AT_GPS_NI_CP_START_STRU       *pstMsgNiStart;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_NI_CP_START_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgNiStart = (XPDS_AT_GPS_NI_CP_START_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgNiStart)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCpNiStart: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgNiStart + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgNiStart->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    pstMsgNiStart->ulStartCode      = 0;

    /* 填消息包 */
    pstMsgNiStart->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgNiStart->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgNiStart->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgNiStart->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgNiStart->ulMsgId         = ID_XPDS_AT_GPS_NI_CP_START;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgNiStart))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCpNiStart():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsCpNiStop
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsCpNiStop(
    VOS_VOID
)
{
    XPDS_AT_GPS_NI_CP_STOP_STRU        *pstMsgNiStop;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_NI_CP_STOP_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgNiStop = (XPDS_AT_GPS_NI_CP_STOP_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgNiStop)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCpNiStop: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgNiStop + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgNiStop->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    /* 填消息包 */
    pstMsgNiStop->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgNiStop->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgNiStop->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgNiStop->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgNiStop->ulMsgId         = ID_XPDS_AT_GPS_NI_CP_STOP;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgNiStop))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsCpNiStop():WARNING:SEND MSG FIAL");
    }

    return;
}



VOS_VOID TAF_XPDS_SndAtGpsAcqAssistData(VOS_VOID)
{
    XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU                   *pstMsgAssistData;
    VOS_UINT32                                              ulMsgLength;
    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU               *pstProvAcqAssist;
    VOS_UINT8                                               ucLoopCount;

    ulMsgLength = sizeof(XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgAssistData = (XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgAssistData)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAcqAssistData: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgAssistData + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgAssistData->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstProvAcqAssist = &(TAF_XPDS_GetPdePublicData()->stProvAcqAssist);

    pstMsgAssistData->ucaAzEl           = pstProvAcqAssist->ucAzElIncl;
    pstMsgAssistData->ucAddDopplerInc   = pstProvAcqAssist->ucAddDoppIncl;
    pstMsgAssistData->ucCodePhaseInc    = pstProvAcqAssist->ucCodePhParIncl;
    pstMsgAssistData->ucDoppler0Inc     = pstProvAcqAssist->ucDopp0Incl;
    pstMsgAssistData->ucSvNum           = pstProvAcqAssist->ucNumOfSv;
    pstMsgAssistData->ulRefTow          = TAF_XPDS_CalcTimeInWeek(pstProvAcqAssist->ucTimeOfApp);

    for (ucLoopCount = 0; ucLoopCount < TAF_MSG_CDMA_MAX_SV_NUM; ucLoopCount++)
    {
        pstMsgAssistData->astAaData[ucLoopCount].ucSvId            = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvPrnNum; //TODO - confirm
        pstMsgAssistData->astAaData[ucLoopCount].ucGpsBitNum       = pstProvAcqAssist->astSatInfo[ucLoopCount].ucGpsBitNum;
        pstMsgAssistData->astAaData[ucLoopCount].cDoppler1         = pstProvAcqAssist->astSatInfo[ucLoopCount].cDoppler1;
        pstMsgAssistData->astAaData[ucLoopCount].sDoppler0         = pstProvAcqAssist->astSatInfo[ucLoopCount].sDoppler0;
        pstMsgAssistData->astAaData[ucLoopCount].ucDoppler_win     = pstProvAcqAssist->astSatInfo[ucLoopCount].ucDopplerWin;
        pstMsgAssistData->astAaData[ucLoopCount].ucAzimuth         = pstProvAcqAssist->astSatInfo[ucLoopCount].ucAzimuth;
        pstMsgAssistData->astAaData[ucLoopCount].ucElevation       = pstProvAcqAssist->astSatInfo[ucLoopCount].ucElevation;
        pstMsgAssistData->astAaData[ucLoopCount].usSvCodePhase     = pstProvAcqAssist->astSatInfo[ucLoopCount].usSvCodePh;
        pstMsgAssistData->astAaData[ucLoopCount].ucSvCodePhaseInt  = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvCodePhInt;
        pstMsgAssistData->astAaData[ucLoopCount].ucSvCodePhaseWin  = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvCodePhWin;
    }

    /* 填消息包 */
    pstMsgAssistData->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgAssistData->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgAssistData->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgAssistData->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgAssistData->ulMsgId         = ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgAssistData))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAcqAssistData():WARNING:SEND MSG FIAL");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsIonInfo
 功能描述  : XPDS发送ION信息到AT
 输入参数  : pstProvEph
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsIonInfo(VOS_VOID)
{
    XPDS_AT_GPS_ION_INFO_IND_STRU      *pstMsgIonInfoInd;
    VOS_UINT32                          ulMsgLength;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph;

    ulMsgLength = sizeof(XPDS_AT_GPS_ION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgIonInfoInd = (XPDS_AT_GPS_ION_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgIonInfoInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsIonInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgIonInfoInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgIonInfoInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstProvEph  = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    pstMsgIonInfoInd->ucABParIncl = pstProvEph->ucABParIncl;
    pstMsgIonInfoInd->ucAlpha0    = pstProvEph->ucAlpha0;
    pstMsgIonInfoInd->ucAlpha1    = pstProvEph->ucAlpha1;
    pstMsgIonInfoInd->ucAlpha2    = pstProvEph->ucAlpha2;
    pstMsgIonInfoInd->ucAlpha3    = pstProvEph->ucAlpha3;
    pstMsgIonInfoInd->ucBeta0     = pstProvEph->ucBeta0;
    pstMsgIonInfoInd->ucBeta1     = pstProvEph->ucBeta1;
    pstMsgIonInfoInd->ucBeta2     = pstProvEph->ucBeta2;
    pstMsgIonInfoInd->ucBeta3     = pstProvEph->ucBeta3;

    /* 填消息包 */
    pstMsgIonInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgIonInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgIonInfoInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgIonInfoInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgIonInfoInd->ulMsgId         = ID_XPDS_AT_GPS_ION_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgIonInfoInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsIonInfo():WARNING:SEND MSG FIAL");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsEphInfo
 功能描述  : XPDS发送EPH信息到AT
 输入参数  : pstProvEph
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsEphInfo(VOS_VOID)
{
    XPDS_AT_GPS_EPH_INFO_IND_STRU      *pstMsgEphInfoInd;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           ucLoop;

    ulMsgLength = sizeof(XPDS_AT_GPS_EPH_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgEphInfoInd = (XPDS_AT_GPS_EPH_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgEphInfoInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsEphInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgEphInfoInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgEphInfoInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstProvEph  = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    if (pstProvEph->ucNumOfSvP >= TAF_MSG_CDMA_MAX_EPH_PRN_NUM)
    {
        pstMsgEphInfoInd->ucSvNum = TAF_MSG_CDMA_MAX_EPH_PRN_NUM;
    }
    else
    {
        pstMsgEphInfoInd->ucSvNum = pstProvEph->ucNumOfSvP;
    }

    for (ucLoop = 0; ucLoop < pstMsgEphInfoInd->ucSvNum; ucLoop++)
    {
        pstMsgEphInfoInd->astEphData[ucLoop].ucSvId         = pstProvEph->astSatInfo[ucLoop].ucSv_Prn_Num;
        pstMsgEphInfoInd->astEphData[ucLoop].ucAf2          = pstProvEph->astSatInfo[ucLoop].ucAF2;
        pstMsgEphInfoInd->astEphData[ucLoop].ucIode         = pstProvEph->astSatInfo[ucLoop].ucIODE;
        pstMsgEphInfoInd->astEphData[ucLoop].usToc          = pstProvEph->astSatInfo[ucLoop].usTOC;
        pstMsgEphInfoInd->astEphData[ucLoop].usToe          = pstProvEph->astSatInfo[ucLoop].usTOE;
        pstMsgEphInfoInd->astEphData[ucLoop].usAf1          = pstProvEph->astSatInfo[ucLoop].usAF1;
        pstMsgEphInfoInd->astEphData[ucLoop].usDelta_n      = pstProvEph->astSatInfo[ucLoop].usDelta_N;
        pstMsgEphInfoInd->astEphData[ucLoop].usIdot         = pstProvEph->astSatInfo[ucLoop].usIdot;
        pstMsgEphInfoInd->astEphData[ucLoop].usCrs          = pstProvEph->astSatInfo[ucLoop].usC_RS;
        pstMsgEphInfoInd->astEphData[ucLoop].usCrc          = pstProvEph->astSatInfo[ucLoop].usC_RC;
        pstMsgEphInfoInd->astEphData[ucLoop].usCus          = pstProvEph->astSatInfo[ucLoop].usC_US;
        pstMsgEphInfoInd->astEphData[ucLoop].usCuc          = pstProvEph->astSatInfo[ucLoop].usC_UC;
        pstMsgEphInfoInd->astEphData[ucLoop].usCis          = pstProvEph->astSatInfo[ucLoop].usC_IS;
        pstMsgEphInfoInd->astEphData[ucLoop].usCic          = pstProvEph->astSatInfo[ucLoop].usC_IC;
        pstMsgEphInfoInd->astEphData[ucLoop].ulAf0          = pstProvEph->astSatInfo[ucLoop].ulAF0;
        pstMsgEphInfoInd->astEphData[ucLoop].ulM0           = pstProvEph->astSatInfo[ucLoop].ulM0;
        pstMsgEphInfoInd->astEphData[ucLoop].ulAsqrt        = pstProvEph->astSatInfo[ucLoop].ulA_Sqrt;
        pstMsgEphInfoInd->astEphData[ucLoop].ulEccentricity = pstProvEph->astSatInfo[ucLoop].ulEcCentricity;
        pstMsgEphInfoInd->astEphData[ucLoop].ulIangle       = pstProvEph->astSatInfo[ucLoop].ulAngle_Incli;
        pstMsgEphInfoInd->astEphData[ucLoop].ulOmega0       = pstProvEph->astSatInfo[ucLoop].ulOmega_0;
        pstMsgEphInfoInd->astEphData[ucLoop].ulOmega        = pstProvEph->astSatInfo[ucLoop].ulOmega;
        pstMsgEphInfoInd->astEphData[ucLoop].ulOmegadot     = pstProvEph->astSatInfo[ucLoop].ulOmegaDot;
    }

    /* 填消息包 */
    pstMsgEphInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgEphInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgEphInfoInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgEphInfoInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgEphInfoInd->ulMsgId         = ID_XPDS_AT_GPS_EPH_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgEphInfoInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsEphInfo():WARNING:SEND MSG FIAL");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsAlmInfo
 功能描述  : XPDS发送ALM信息到AT
 输入参数  : pstProvEph
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsAlmInfo(VOS_VOID)
{
    XPDS_AT_GPS_ALM_INFO_IND_STRU      *pstMsgAlmInfoInd;
    VOS_UINT32                          ulMsgLength;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm;
    VOS_UINT8                           ucLoop;

    ulMsgLength = sizeof(XPDS_AT_GPS_ALM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgAlmInfoInd = (XPDS_AT_GPS_ALM_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgAlmInfoInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAlmInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgAlmInfoInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgAlmInfoInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstProvAlm  = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    if (pstProvAlm->ucNumOfSvP >= TAF_MSG_CDMA_MAX_ALM_PRN_NUM)
    {
        pstMsgAlmInfoInd->ucSvNum = TAF_MSG_CDMA_MAX_ALM_PRN_NUM;
    }
    else
    {
        pstMsgAlmInfoInd->ucSvNum = pstProvAlm->ucNumOfSvP;
    }

    pstMsgAlmInfoInd->ucWeekNum = pstProvAlm->ucWeekNum;
    pstMsgAlmInfoInd->ucToa     = pstProvAlm->ucTOA;

    for (ucLoop = 0; ucLoop < pstMsgAlmInfoInd->ucSvNum; ucLoop++)
    {
        pstMsgAlmInfoInd->astAlmData[ucLoop].ucSvId         = pstProvAlm->astSatInfo[ucLoop].ucSv_Prn_Num;
        pstMsgAlmInfoInd->astAlmData[ucLoop].usDeltai       = pstProvAlm->astSatInfo[ucLoop].usDelta_Incli;
        pstMsgAlmInfoInd->astAlmData[ucLoop].usAf0          = pstProvAlm->astSatInfo[ucLoop].usAF0;
        pstMsgAlmInfoInd->astAlmData[ucLoop].usAf1          = pstProvAlm->astSatInfo[ucLoop].usAF1;
        pstMsgAlmInfoInd->astAlmData[ucLoop].usOmegadot     = pstProvAlm->astSatInfo[ucLoop].usOmegaDot;
        pstMsgAlmInfoInd->astAlmData[ucLoop].usEccentricity = pstProvAlm->astSatInfo[ucLoop].usEcCentricity;
        pstMsgAlmInfoInd->astAlmData[ucLoop].ulAsqrt        = pstProvAlm->astSatInfo[ucLoop].ulA_Sqrt;
        pstMsgAlmInfoInd->astAlmData[ucLoop].ulOmega_0      = pstProvAlm->astSatInfo[ucLoop].ulOmega_0;
        pstMsgAlmInfoInd->astAlmData[ucLoop].ulOmega        = pstProvAlm->astSatInfo[ucLoop].ulOmega;
        pstMsgAlmInfoInd->astAlmData[ucLoop].ulM0           = pstProvAlm->astSatInfo[ucLoop].ulM0;
    }

    /* 填消息包 */
    pstMsgAlmInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgAlmInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgAlmInfoInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgAlmInfoInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgAlmInfoInd->ulMsgId         = ID_XPDS_AT_GPS_ALM_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgAlmInfoInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsAlmInfo():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID TAF_XPDS_SndAtGpsPositionInfo(VOS_VOID)
{
    XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU *pstMsgPosiInfoInd;
    VOS_UINT32                          ulMsgLength;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU *pstProvLocRsp;

    ulMsgLength = sizeof(XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgPosiInfoInd = (XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgPosiInfoInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsPositionInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgPosiInfoInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgPosiInfoInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetGpsClientId(), UEPS_PID_XPDS);

    pstProvLocRsp   = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);

    /* update the sending data */
    pstMsgPosiInfoInd->ucVelocityIncl = pstProvLocRsp->ucVelocityIncl;
    pstMsgPosiInfoInd->ucHeightIncl   = pstProvLocRsp->ucHeightIncl;
    pstMsgPosiInfoInd->ucClockIncl    = pstProvLocRsp->ucClockIncl;
    pstMsgPosiInfoInd->ucFixType      = pstProvLocRsp->ucFixType;
    pstMsgPosiInfoInd->sLocUncAng     = pstProvLocRsp->ucLocUncerAng;
    pstMsgPosiInfoInd->sClockDrift    = pstProvLocRsp->sClockDrift;
    pstMsgPosiInfoInd->lClockBias     = pstProvLocRsp->lClockBias;
    pstMsgPosiInfoInd->lLatitude      = pstProvLocRsp->lLattitude;
    pstMsgPosiInfoInd->lLongitude     = pstProvLocRsp->lLongitude;
    pstMsgPosiInfoInd->ulLocUncA      = pstProvLocRsp->ucLocUncerA;
    pstMsgPosiInfoInd->ulLocUncP      = pstProvLocRsp->ucLocUncerP;
    pstMsgPosiInfoInd->ulVelocityHor  = pstProvLocRsp->usVelocityHor;
    pstMsgPosiInfoInd->ulHeading      = pstProvLocRsp->usHeading;
    pstMsgPosiInfoInd->lHeight        = pstProvLocRsp->sHeight;
    pstMsgPosiInfoInd->lVerticalVelo  = pstProvLocRsp->cVelocityVer;
    pstMsgPosiInfoInd->ulLocUncV      = pstProvLocRsp->ucLocUncerV;

    /* 填消息包 */
    pstMsgPosiInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgPosiInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgPosiInfoInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgPosiInfoInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgPosiInfoInd->ulMsgId         = ID_XPDS_AT_GPS_PDE_POSI_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgPosiInfoInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsPositionInfo():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetPosReportLocInfo
 功能描述  : 设置POS REP里面的位置信息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月22日
    作    者   : c00299064
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SetPosReportLocInfo(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
)
{
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enCurFixMode;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU *pstProvLocRsp;
    AT_XPDS_GPS_POS_INFO_STRU          *pstGpsPosInfo;

    pstProvLocRsp = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);
    pstGpsPosInfo = &(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo);
    enCurFixMode  = TAF_XPDS_GetAgpsFixMode();

    if ((TAF_XPDS_MSA_MODE == enCurFixMode)
     || (TAF_XPDS_AFLT_MODE == enCurFixMode))
    {
        pstPosReportReq->ulPosIncFlag = VOS_TRUE;

        pstPosReportReq->lLat               = pstProvLocRsp->lLattitude;
        pstPosReportReq->lLong              = pstProvLocRsp->lLongitude;
        pstPosReportReq->ucLocUncrtntyAng   = pstProvLocRsp->ucLocUncerAng;
        pstPosReportReq->ucLocUncrtntyA     = pstProvLocRsp->ucLocUncerA;
        pstPosReportReq->ucLocUncrtntyP     = pstProvLocRsp->ucLocUncerP;
        pstPosReportReq->ucVelocityIncl     = VOS_TRUE;
        pstPosReportReq->usVelocityHor      = pstProvLocRsp->usVelocityHor;
        pstPosReportReq->sVelocityVer       = (VOS_INT16)pstProvLocRsp->cVelocityVer;

        pstPosReportReq->usHeading          = pstProvLocRsp->usHeading;

        pstPosReportReq->usHeihtIncl        = VOS_TRUE;
        pstPosReportReq->sHeiht             =  pstProvLocRsp->sHeight;
        pstPosReportReq->usLocUncrtntyV     =  pstProvLocRsp->ucLocUncerV;


    }
    else if (TAF_XPDS_MSB_MODE == enCurFixMode)
    {
        if (VOS_FALSE == pstGpsPosInfo->ulValidityMask)
        {
            pstPosReportReq->ulPosIncFlag = VOS_FALSE;
        }
        else
        {
            pstPosReportReq->ulPosIncFlag = VOS_TRUE;

            pstPosReportReq->lLat               = pstGpsPosInfo->lLatitude;
            pstPosReportReq->lLong              = pstGpsPosInfo->lLongitude;
            pstPosReportReq->ucLocUncrtntyAng   = 0;
            pstPosReportReq->ucLocUncrtntyA     = 0;
            pstPosReportReq->ucLocUncrtntyP     = 0;
            pstPosReportReq->ucVelocityIncl     = VOS_TRUE;
            pstPosReportReq->usVelocityHor      = (VOS_UINT16)pstGpsPosInfo->ulHorizontalVelocity;
            pstPosReportReq->sVelocityVer       = (VOS_INT16)pstGpsPosInfo->ulVerticalVelocity;

            pstPosReportReq->usHeading          = (VOS_UINT16)pstGpsPosInfo->ulHeading;

            pstPosReportReq->usHeihtIncl        = VOS_FALSE;
        }
    }
    else
    {
        pstPosReportReq->ulPosIncFlag = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsUtsTestStartReq
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsUtsTestStartReq(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulMsgLength;

    if (ulDataLen >= 4)
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) + ulDataLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstAtXpdsMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsUtsTestStartReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstAtXpdsMsg + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstAtXpdsMsg->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    PS_MEM_CPY(pstAtXpdsMsg->aucContent, pucData, ulDataLen);

    /* 填消息包 */
    pstAtXpdsMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstAtXpdsMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstAtXpdsMsg->ulMsgId         = ID_XPDS_AT_GPS_UTS_TEST_START_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstAtXpdsMsg))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsUtsTestStartReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsUtsTestStopReq
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsUtsTestStopReq(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulMsgLength;

    if (ulDataLen >= 4)
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) + ulDataLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstAtXpdsMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsUtsTestStartReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstAtXpdsMsg + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstAtXpdsMsg->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    PS_MEM_CPY(pstAtXpdsMsg->aucContent, pucData, ulDataLen);

    /* 填消息包 */
    pstAtXpdsMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstAtXpdsMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstAtXpdsMsg->ulMsgId         = ID_XPDS_AT_GPS_UTS_TEST_STOP_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstAtXpdsMsg))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsUtsTestStopReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtUtsGpsPosInfo
 功能描述  : XPDS发送MSB GPS定位结果到UTS
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtUtsGpsPosInfo(VOS_VOID)
{
    XPDS_AT_UTS_GPS_POS_INFO_IND_STRU  *pstMsgUtsPosInfoInd;
    VOS_UINT32                          ulMsgLength;
    AT_XPDS_GPS_POS_INFO_STRU          *pstXpdsGpsPosInfo;

    ulMsgLength = sizeof(XPDS_AT_UTS_GPS_POS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgUtsPosInfoInd = (XPDS_AT_UTS_GPS_POS_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgUtsPosInfoInd)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtUtsGpsPosInfo: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgUtsPosInfoInd + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgUtsPosInfoInd->stAppCtrl.usClientId = MN_GetRealClientId(TAF_XPDS_GetUtsClientId(), UEPS_PID_XPDS);

    pstXpdsGpsPosInfo = &(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo);

    PS_MEM_CPY(&(pstMsgUtsPosInfoInd->stPosInfo), pstXpdsGpsPosInfo, sizeof(AT_XPDS_GPS_POS_INFO_STRU));

    /* 填消息包 */
    pstMsgUtsPosInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgUtsPosInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgUtsPosInfoInd->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgUtsPosInfoInd->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgUtsPosInfoInd->ulMsgId         = ID_XPDS_AT_UTS_GPS_POS_INFO_IND;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgUtsPosInfoInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtGpsPositionInfo():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtOmGpsTestStartReq
 功能描述  : XPDS发送测试请求到GPS
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtOmGpsTestStartReq(
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enFixMode,
    TAF_XPDS_GPS_START_MODE_ENUM_UINT8  enStartMode
)
{
    XPDS_AT_GPS_OM_TEST_START_REQ_STRU                     *pstTestStartReq;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_OM_TEST_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 消息空间申请 */
    pstTestStartReq = (XPDS_AT_GPS_OM_TEST_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstTestStartReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtOmGpsTestStartReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstTestStartReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstTestStartReq->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    pstTestStartReq->enFixMode   = enFixMode;
    pstTestStartReq->enStartMode = enStartMode;

    /* 填消息包 */
    pstTestStartReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTestStartReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTestStartReq->ulSenderPid     = UEPS_PID_XPDS;
    pstTestStartReq->ulReceiverPid   = WUEPS_PID_AT;
    pstTestStartReq->ulMsgId         = ID_XPDS_AT_GPS_OM_TEST_START_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstTestStartReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtOmGpsTestStartReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndAtGpsAbortPosInd
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtOmGpsTestStopReq(VOS_VOID)
{
    XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU  *pstMsgStopReq;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 消息空间申请 */
    pstMsgStopReq = (XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStopReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtOmGpsTestStopReq: alloc msg fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStopReq + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgStopReq->stAppCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ALL, UEPS_PID_XPDS);

    /* 填消息包 */
    pstMsgStopReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStopReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStopReq->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgStopReq->ulReceiverPid   = WUEPS_PID_AT;
    pstMsgStopReq->ulMsgId         = ID_XPDS_AT_GPS_OM_TEST_STOP_REQ;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStopReq))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtOmGpsTestStopReq():WARNING:SEND MSG FIAL");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmStartGpsFixCnf
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmStartGpsFixCnf(
    OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *pstMsgStartReq
)
{
    NAS_OM_CDMA_START_GPS_FIX_CNF_STRU *pstMsgStartCnf;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(NAS_OM_CDMA_START_GPS_FIX_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 消息空间申请 */
    pstMsgStartCnf = (NAS_OM_CDMA_START_GPS_FIX_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStartCnf)
    {
        return ;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStartCnf + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgStartCnf->usOriginalId    = pstMsgStartReq->usOriginalId;
    pstMsgStartCnf->usTerminalId    = pstMsgStartReq->usTerminalId;
    pstMsgStartCnf->ulTimeStamp     = pstMsgStartReq->ulTimeStamp;
    pstMsgStartCnf->ulSn            = pstMsgStartReq->ulSn;

    pstMsgStartCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStartCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStartCnf->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgStartCnf->ulReceiverPid   = MSP_PID_DIAG_APP_AGENT;
    pstMsgStartCnf->ulMsgId         = ID_NAS_OM_CDMA_START_GPS_FIX_CNF;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStartCnf))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndOmStartGpsFixCnf():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmStopGpsFixCnf
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmStopGpsFixCnf(
    OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU  *pstMsgStopReq
)
{
    NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU  *pstMsgStopCnf;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 消息空间申请 */
    pstMsgStopCnf = (NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStopCnf)
    {
        return ;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStopCnf + VOS_MSG_HEAD_LENGTH), 0x00, ulMsgLength);

    pstMsgStopCnf->usOriginalId    = pstMsgStopReq->usOriginalId;
    pstMsgStopCnf->usTerminalId    = pstMsgStopReq->usTerminalId;
    pstMsgStopCnf->ulTimeStamp     = pstMsgStopReq->ulTimeStamp;
    pstMsgStopCnf->ulSn            = pstMsgStopReq->ulSn;

    pstMsgStopCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStopCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStopCnf->ulSenderPid     = UEPS_PID_XPDS;
    pstMsgStopCnf->ulReceiverPid   = MSP_PID_DIAG_APP_AGENT;
    pstMsgStopCnf->ulMsgId         = ID_NAS_OM_CDMA_STOP_GPS_FIX_CNF;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStopCnf))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndOmStopGpsFixCnf():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmGpsFixRsltInd
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmGpsFixRsltInd(
    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 enFixRslt
)
{
    NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU  *pstFixRsltInd;
    AT_XPDS_GPS_POS_INFO_STRU          *pstXpdsGpsPosInfo;
    DIAG_TRANS_IND_STRU                 stIndMsg;

    if (VOS_FALSE == TAF_XPDS_GetOmTestFlag())
    {
        return;
    }

    pstXpdsGpsPosInfo = &(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo);

    pstFixRsltInd = (NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU *)PS_MEM_ALLOC(
                                         UEPS_PID_XPDS,
                                         sizeof(NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU));

    if (VOS_NULL_PTR == pstFixRsltInd)
    {
        return;
    }

    PS_MEM_SET(pstFixRsltInd, 0x00, sizeof(NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU));

    pstFixRsltInd->usToolsId = 0;
    pstFixRsltInd->usPrimId  = ID_NAS_OM_CDMA_GPS_FIX_RSLT_IND;
    pstFixRsltInd->enRslt    = enFixRslt;

    if (NAS_OM_CDMA_GPS_FIX_RSLT_SUCCESS == enFixRslt)
    {
        PS_MEM_CPY(&(pstFixRsltInd->stPosInfo.stUtcTime), &(pstXpdsGpsPosInfo->stUTCTime),
                   sizeof(NAS_OM_CDMA_GPS_UTC_TIME_STRU));

        pstFixRsltInd->stPosInfo.lLatitude           = pstXpdsGpsPosInfo->lLatitude;
        pstFixRsltInd->stPosInfo.lLongitude          = pstXpdsGpsPosInfo->lLongitude;
        pstFixRsltInd->stPosInfo.ulHeading           = pstXpdsGpsPosInfo->ulHeading;
        pstFixRsltInd->stPosInfo.ulSpeed             = pstXpdsGpsPosInfo->ulSpeed;
        pstFixRsltInd->stPosInfo.enFixType           = TAF_XPDS_ConvertXpdsGpsFixTypeToOmGpsFixType(
                                                                            pstXpdsGpsPosInfo->enFixType);
        pstFixRsltInd->stPosInfo.ulHDOP              = pstXpdsGpsPosInfo->ulHorizontalDilutionOfPrecision;
        pstFixRsltInd->stPosInfo.ulPDOP              = pstXpdsGpsPosInfo->ulPositionDilutionOfPrecision;
        pstFixRsltInd->stPosInfo.ulVDOP              = pstXpdsGpsPosInfo->ulVerticalDilutionOfPrecision;
        pstFixRsltInd->stPosInfo.ulSeaLevelAltitude  = pstXpdsGpsPosInfo->ulAltitudeWRTSeaLevel;
        pstFixRsltInd->stPosInfo.ulEllipsoidAltitude = pstXpdsGpsPosInfo->ulAltitudeWRTEllipsoid;
        pstFixRsltInd->stPosInfo.ulMagneticVariation = pstXpdsGpsPosInfo->ulMagneticVariation;
    }

    stIndMsg.ulPid    = UEPS_PID_XPDS;
    stIndMsg.ulLength = sizeof(NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU);
    stIndMsg.ulModule = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XPDS), DIAG_MODE_COMM);
    stIndMsg.ulMsgId  = ID_NAS_OM_CDMA_GPS_FIX_RSLT_IND;
    stIndMsg.pData    = (VOS_VOID *)pstFixRsltInd;

    DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFixRsltInd);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmGpsSignalMsgInd
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmGpsSignalMsgInd(
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8              enMsgType
)
{
    NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU                    *pstGpsSignalMsgInd;
    DIAG_TRANS_IND_STRU                                     stIndMsg;

    if (VOS_FALSE == TAF_XPDS_GetOmTestFlag())
    {
        return;
    }

    if (NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_BUTT == enMsgType)
    {
        return;
    }

    pstGpsSignalMsgInd = (NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU *)PS_MEM_ALLOC(
                                         UEPS_PID_XPDS,
                                         sizeof(NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU));

    if (VOS_NULL_PTR == pstGpsSignalMsgInd)
    {
        return ;
    }

    /*初始化参数*/
    PS_MEM_SET(pstGpsSignalMsgInd, 0x00, sizeof(NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU));

    pstGpsSignalMsgInd->usToolsId = 0;
    pstGpsSignalMsgInd->usPrimId  = ID_NAS_OM_CDMA_GPS_SIGNAL_MSG_IND;
    pstGpsSignalMsgInd->enMsgType = enMsgType;

    stIndMsg.ulPid      = UEPS_PID_XPDS;
    stIndMsg.ulLength   = sizeof(NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU);
    stIndMsg.ulModule   = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XPDS), DIAG_MODE_COMM);
    stIndMsg.ulMsgId    = ID_NAS_OM_CDMA_GPS_SIGNAL_MSG_IND;
    stIndMsg.pData      = (VOS_VOID *)pstGpsSignalMsgInd;

    DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstGpsSignalMsgInd);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmGpsFixStartInd
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmGpsFixStartInd(VOS_VOID)
{
    NAS_OM_CDMA_GPS_FIX_START_IND_STRU                     *pstGpsFixStartInd;
    DIAG_TRANS_IND_STRU                                     stIndMsg;

    if (VOS_FALSE == TAF_XPDS_GetOmTestFlag())
    {
        return;
    }

    pstGpsFixStartInd = (NAS_OM_CDMA_GPS_FIX_START_IND_STRU *)PS_MEM_ALLOC(
                                         UEPS_PID_XPDS,
                                         sizeof(NAS_OM_CDMA_GPS_FIX_START_IND_STRU));

    if (VOS_NULL_PTR == pstGpsFixStartInd)
    {
        return ;
    }

    /*初始化参数*/
    PS_MEM_SET(pstGpsFixStartInd, 0x00, sizeof(NAS_OM_CDMA_GPS_FIX_START_IND_STRU));

    pstGpsFixStartInd->usToolsId = 0;
    pstGpsFixStartInd->usPrimId  = ID_NAS_OM_CDMA_GPS_FIX_START_IND;

    stIndMsg.ulPid      = UEPS_PID_XPDS;
    stIndMsg.ulLength   = sizeof(NAS_OM_CDMA_GPS_FIX_START_IND_STRU);
    stIndMsg.ulModule   = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XPDS), DIAG_MODE_COMM);
    stIndMsg.ulMsgId    = ID_NAS_OM_CDMA_GPS_FIX_START_IND;
    stIndMsg.pData      = (VOS_VOID *)pstGpsFixStartInd;

    DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstGpsFixStartInd);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
