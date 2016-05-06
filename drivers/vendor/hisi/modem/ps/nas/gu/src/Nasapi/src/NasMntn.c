/******************************************************************************

                  版权所有 (C), 2004-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMntn.c
  版 本 号   : 初稿
  作    者   : f00179208
  生成日期   : 2014年10月07日
  最近修改   : 2014年10月07日
  功能描述   : NAS可维可测的公共处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月07日
    作    者   : f00179208
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "MnComm.h"

#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasComm.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MNTN_C
/*lint +e767 */

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

VOS_UINT32   gulNasOTASwitch = NAS_OTA_SWITCH_OFF;

#if (FEATURE_ON == FEATURE_PTM)
/* NAS模块Error Log异常级别表 */
NAS_ERR_LOG_ALM_LEVEL_STRU g_astNasErrAlmLevelTb[] = {
    {NAS_ERR_LOG_ALM_CS_REG_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_REG_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,                 NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_CALL_FAIL,                          NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_CALL_FAIL,                          NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_SMS_FAIL,                              NAS_ERR_LOG_CTRL_LEVEL_MAJOR},
    {NAS_ERR_LOG_ALM_VC_OPT_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_PAGING_FAIL,                        NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,                       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,                     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_MNTN,                                  NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_NW_DETACH_IND,                         NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,                       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,                        NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_MO_DETACH_IND,                         NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,                 NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_OOS_BEGIN,                             NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_OOS_END,                               NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PORCESS_INFO_IND,                      NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,                     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL,                     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO,                       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},

};

NAS_ERR_LOG_ALM_REPORT_TYPE_STRU g_astNasErrAlmUnsoliReportTypeTb[] = {
    {NAS_ERR_LOG_ALM_CS_PAGING_FAIL,                        NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,                       NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,                     NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_OOS_BEGIN,                             NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_OOS_END,                               NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CS_CALL_FAIL,                          NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,                 NAS_ERR_LOG_ALARM_REPORT},
    {NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL,                    NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO,                       NAS_ERR_LOG_FAULT_REPORT},
};
#endif

NAS_ERR_LOG_BAST_STATE_TO_CSFB_MT_STATE_STRU    g_astNasErrBaseStateToCsfbMtState[] = {
    {NAS_ERR_LOG_BASE_STATE_NULL,                               NAS_ERR_LOG_CSFB_MT_STATE_NULL},
    {NAS_ERR_LOG_BASE_STATE_LMM_CS_PAGING_RECEIVED,             NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST, NAS_ERR_LOG_CSFB_MT_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST},
    {NAS_ERR_LOG_BASE_STATE_END_IND_RECEIVED,                   NAS_ERR_LOG_CSFB_MT_STATE_END_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_SUSPEND_IND_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_SUSPEND_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_LTE_RESUME_IND_RECEIVED,            NAS_ERR_LOG_CSFB_MT_STATE_LTE_RESUME_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_GU_RESUME_IND_RECEIVED,             NAS_ERR_LOG_CSFB_MT_STATE_GU_RESUME_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_RESUME_TO_GU_FAIL,                  NAS_ERR_LOG_CSFB_MT_STATE_RESUME_TO_GU_FAIL},
    {NAS_ERR_LOG_BASE_STATE_LTE_SYS_INFO_RECEIVED,              NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,                    NAS_ERR_LOG_CSFB_MT_STATE_PAGING_RSP_SEND},
    {NAS_ERR_LOG_BASE_STATE_TRAG_LAU,                           NAS_ERR_LOG_CSFB_MT_STATE_TRAG_LAU},
    {NAS_ERR_LOG_BASE_STATE_EST_FAILED,                         NAS_ERR_LOG_CSFB_MT_STATE_EST_FAILED},
    {NAS_ERR_LOG_BASE_STATE_EST_SUCCESSED,                      NAS_ERR_LOG_CSFB_MT_STATE_EST_SUCCESSED},
    {NAS_ERR_LOG_BASE_STATE_AUTH_REJ,                           NAS_ERR_LOG_CSFB_MT_STATE_AUTH_REJ},
    {NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,                          NAS_ERR_LOG_CSFB_MT_STATE_AUTH_FAIL},
    {NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT,                      NAS_ERR_LOG_CSFB_MT_STATE_T3240_TIMEOUT},
    {NAS_ERR_LOG_BASE_STATE_LAU_REJECT,                         NAS_ERR_LOG_CSFB_MT_STATE_LAU_REJECT},
    {NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,                         NAS_ERR_LOG_CSFB_MT_STATE_LAU_ACCEPT},
    {NAS_ERR_LOG_BASE_STATE_RRC_REL_IND_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_RRC_REL_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT,        NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_PROTECT_TI_TIME_OUT},
    {NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND,    NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND},
    {NAS_ERR_LOG_BASE_STATE_CM_SERVICE_MSG_RECEIVED,            NAS_ERR_LOG_CSFB_MT_STATE_CM_SERVICE_MSG_RECEIVED},
};

NAS_ERR_LOG_OOS_EVENT_TO_OOS_CAUSE_STRU     g_astNasErrOosEventToOosCause[] = {
    {NAS_ERR_LOG_OOS_EVENT_NULL,                                            NAS_ERR_LOG_OOS_CAUSE_NULL},
    {NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG,                                     NAS_ERR_LOG_OOS_CAUSE_USER_SYSCFG},
    {NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH,                                  NAS_ERR_LOG_OOS_CAUSE_USER_LIST_SRCH},
    {NAS_ERR_LOG_OOS_EVENT_USER_SPEC_SRCH,                                  NAS_ERR_LOG_OOS_CAUSE_USER_SPEC_SRCH},
    {NAS_ERR_LOG_OOS_EVENT_USER_AUTO_SEL,                                   NAS_ERR_LOG_OOS_CAUSE_USER_AUTO_SEL},
    {NAS_ERR_LOG_OOS_EVENT_USER_POWER_ON,                                   NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON},
    {NAS_ERR_LOG_OOS_EVENT_USER_POWER_OFF,                                  NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF},
    {NAS_ERR_LOG_OOS_EVENT_USER_DETACH,                                     NAS_ERR_LOG_OOS_CAUSE_USER_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_GAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_GAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_WAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_TAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_TAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_LMM_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_LMM_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_GAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_GAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_WAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_TAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_TAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_LMM_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_LMM_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_LIMITED_CAMP,                                NAS_ERR_LOG_OOS_CAUSE_WAS_LIMITED_CAMP},
    {NAS_ERR_LOG_OOS_EVENT_TAS_LIMITED_CAMP,                                NAS_ERR_LOG_OOS_CAUSE_TAS_LIMITED_CAMP},
    {NAS_ERR_LOG_OOS_EVENT_GAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_GAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_WAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_WAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_TAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_TAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_CS_REG_FAIL,                                     NAS_ERR_LOG_OOS_CAUSE_CS_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_PS_REG_FAIL,                                     NAS_ERR_LOG_OOS_CAUSE_PS_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ATTACH_FAIL,                     NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ATTACH_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_TAU_FAIL,                        NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_TAU_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ONLY_EPS_SUCC,                   NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ONLY_EPS_SUCC},
    {NAS_ERR_LOG_OOS_EVENT_EPS_REG_ATTACH_FAIL,                             NAS_ERR_LOG_OOS_CAUSE_EPS_REG_ATTACH_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_REG_TAU_FAIL,                                NAS_ERR_LOG_OOS_CAUSE_EPS_REG_TAU_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH,                                 NAS_ERR_LOG_OOS_CAUSE_EPS_ONLY_ATTACH},
    {NAS_ERR_LOG_OOS_EVENT_ATTACH_AUTH_REJ,                                 NAS_ERR_LOG_OOS_CAUSE_ATTACH_AUTH_REJ},
    {NAS_ERR_LOG_OOS_EVENT_CM_SERVICE_REJ,                                  NAS_ERR_LOG_OOS_CAUSE_CM_SERVICE_REJ},
    {NAS_ERR_LOG_OOS_EVENT_PS_SERVICE_REG_FAIL,                             NAS_ERR_LOG_OOS_CAUSE_PS_SERVICE_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_SERVICE_REQ_FAIL,                            NAS_ERR_LOG_OOS_CAUSE_EPS_SERVICE_REQ_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_GUT_NW_DETACH,                                   NAS_ERR_LOG_OOS_CAUSE_GUT_NW_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH,                                   NAS_ERR_LOG_OOS_CAUSE_LTE_NW_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_GUT_LOCAL_DETACH,                                NAS_ERR_LOG_OOS_CAUSE_GUT_LOCAL_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_LTE_LOCAL_DETACH,                                NAS_ERR_LOG_OOS_CAUSE_LTE_LOCAL_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP,  NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP,         NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL,       NAS_ERR_LOG_OOS_CAUSE_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE,                                     NAS_ERR_LOG_OOS_CAUSE_DISABLE_LTE},
    {NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE,                                      NAS_ERR_LOG_OOS_CAUSE_ENABLE_LTE},
};

NAS_MNTN_MM_INFO_STRU                   g_stNasMntnErrorLogMm;

extern NAS_MNTN_SM_INFO_STRU            g_stNasMntnErrorlogSm;

NAS_TIMER_EVENT_INFO_STRU               g_stTimerReportCfg;

VOS_UINT32                              g_ulNasTraceLevle  = NAS_TRACE_LEVEL_HIGH;
VOS_UINT32                              g_ulNasTraceOutput = NAS_TRACE_OUTPUT_ASHELL;

#if defined (INSTANCE_1)
extern VOS_UINT8    *gpucGunasExcAddr;
#elif defined (INSTANCE_2)
extern VOS_UINT8    *gpucGunasExcAddr;
#else
VOS_UINT8           *gpucGunasExcAddr    = VOS_NULL_PTR;

#endif

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_TIMER_EventReport
 功能描述  : 判断是否需要上报定时器的OTA事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 记录哪些定时器事件需要上报的全局变量的首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月28日
   作    者   : l00167671
   修改内容   : 新生成函数
*****************************************************************************/
NAS_TIMER_EVENT_INFO_STRU* NAS_GetTimerEventReportCfg()
{
    return (&g_stTimerReportCfg);
}

/*****************************************************************************
 函 数 名  : NAS_TIMER_EventReport
 功能描述  : 判断是否需要上报定时器的OTA事件
 输入参数  : ulTimerName, 定时器名称
             ulPid,定时器所在模块的PID
             enEventId,哪种事件包括开始、停止和超时三种事件
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月28日
   作    者   : l00167671
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_TIMER_EventReport(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    VOS_UINT32                ulEventType;
    NAS_TIMER_EVENT_STRU      stNasTimerEvent;

    ulEventType                 = NAS_BuildEventType(ulPid,ulTimerName);
    stNasTimerEvent.usPid       = (VOS_UINT16)ulPid;
    stNasTimerEvent.usTimerName = (VOS_UINT16)ulTimerName;

    if (VOS_TRUE == NAS_IsNeedTimerEventReport(ulEventType))
    {
        NAS_EventReport(ulPid, enEventId, &stNasTimerEvent, sizeof(stNasTimerEvent));
    }
}

/*****************************************************************************
 函 数 名  : NAS_IsNeedTimerEventReport
 功能描述  : 判断是否需要上报定时器的OTA事件
 输入参数  : ulMcc:当前PLMN ID的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月28日
   作    者   : l00167671
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_IsNeedTimerEventReport(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          ulI;
    NAS_TIMER_EVENT_INFO_STRU          *pstTimerEventInfo;

    pstTimerEventInfo = NAS_GetTimerEventReportCfg();

    for ( ulI = 0; ulI < pstTimerEventInfo->ulItems; ulI++ )
    {
        if ( ulEventType == pstTimerEventInfo->aulTimerMsg[ulI] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

/*****************************************************************************
 函 数 名  : NAS_MNTN_OutputPositionInfo
 功能描述  : 将驻留或尝试驻留位置相关信息刷新到异常事件记录
 输入参数  : 无
 输出参数  : NAS_MNTN_POSITION_INFO_STRU *pstPositionInfo
                        UE驻留或尝试驻留位置相关信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

  2.日    期   : 2011年8月3日
    作    者   : zhoujun 40661
    修改内容   : MMC_MAIN文件删除该函数移动到此文件

*****************************************************************************/
VOS_VOID NAS_MNTN_OutputPositionInfo(NAS_MNTN_POSITION_INFO_STRU *pstPositionInfo)
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo;

    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    pstPositionInfo->stRai.usRac        = pstCampPlmnInfo->ucRac;

    pstPositionInfo->stRai.usLac        = (VOS_UINT16)(pstCampPlmnInfo->stLai.aucLac[1]
                                                    | (pstCampPlmnInfo->stLai.aucLac[0] << 8));

    /* 网络模式:
    #define MMC_NW_MODE_I                     0
    #define MMC_NW_MODE_II                    1
    #define MMC_NW_MODE_III                   2
    */
    /* 由于MMC */
    pstPositionInfo->ucNetworkMode      = pstCampPlmnInfo->enNetworkMode;

    /* 从gstMmcCellInfo中获取小区信息； */
    pstPositionInfo->ulCellId           = pstCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId;

    /* 从g_RrMmSysInfoInd中获取子系统模式和PLMN信息
    #define     MMC_NET_TYPE_GSM            0
    #define     MMC_NET_TYPE_WCDMA          1
    #define     MMC_NET_TYPE_INVALID        0xff
    */
    pstPositionInfo->enSysSubMode       = pstCampPlmnInfo->enSysSubMode;
    pstPositionInfo->stRai.stPlmn.ulMcc = pstCampPlmnInfo->stLai.stPlmnId.ulMcc;
    pstPositionInfo->stRai.stPlmn.ulMnc = pstCampPlmnInfo->stLai.stPlmnId.ulMnc;

    /* 从g_MmSubLyrShare中获取接入技术 */
#if (FEATURE_ON == FEATURE_PTM)
    if (NAS_MML_NET_RAT_TYPE_WCDMA == pstCampPlmnInfo->enNetRatType)
    {
        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            pstPositionInfo->ucRat      = NAS_ERR_LOG_RATMODE_WCDMA;
        }
        else
        {
            pstPositionInfo->ucRat      = NAS_ERR_LOG_RATMODE_TDS;
        }
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == pstCampPlmnInfo->enNetRatType)
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_LTE == pstCampPlmnInfo->enNetRatType)
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_LTE;
    }
    else
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_BUTT;
    }
#else
    pstPositionInfo->ucRat              = pstCampPlmnInfo->enNetRatType;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_RecordPdpActiveFail
 功能描述  : 记录拨号失败事件到ERROR LOG文件
 输入参数  : NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32 enFailType   PDP激活请求失败类型
             VOS_UINT8                             ucCntxtIndex PDP context的索引
             VOS_UINT8                             ucSmCause    PDP激活请求被网络拒绝的原因值
             VOS_UINT8                             ucRegisterFlg    PS域的注册状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月18日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月29日
    作    者   : z60575
    修改内容   : DTS2013062500138,ERROR_LOG修改
*****************************************************************************/
VOS_VOID NAS_MNTN_RecordPdpActiveFail(
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                       enFailType,
    VOS_UINT8                                                   ucCntxtIndex,
    VOS_UINT8                                                   ucSmCause,
    VOS_UINT8                                                   ucRegisterFlg
)
{
    NAS_MNTN_ACTIVE_FAIL_EVENT_STRU     stPsActiveFailEvent;
    VOS_UINT32                          ulRet;

    /* 判断是否需要记录 */
    if (g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter >= NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: counter reach NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX.");
        return;
    }

    PS_MEM_SET(&stPsActiveFailEvent, 0x00, sizeof(stPsActiveFailEvent));

    /* 填写拨号失败事件信息 */
    /* 存储PDP激活失败直接相关数据 */
    stPsActiveFailEvent.stPsActiveFail.enFailType    = enFailType;
    stPsActiveFailEvent.stPsActiveFail.ucSmCause     = ucSmCause;

    /* 记录PS域服务状态 */
    stPsActiveFailEvent.stPsActiveFail.ucRegisterFlg = ucRegisterFlg;

    NAS_MMA_OutputUsimInfo(&stPsActiveFailEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stPsActiveFailEvent.stPositionInfo);

    /* 输出拨号失败事件信息 */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_SM,MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT),
                                &stPsActiveFailEvent,
                                sizeof(stPsActiveFailEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: MNTN_RecordErrorLog fail.");
        return;
    }

    g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_CheckServiceUnavailableEvent
 功能描述  : 业务不可用事件检查
 输入参数  : NAS_OM_EVENT_ID_ENUM                enEventId 需要上报的事件ID
 输出参数  : 无
 返 回 值  : VOS_UINT32 CS域或PS域业务获取失败相关事件返回VOS_OK
                        否则返回VOS_ERR

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月11日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MNTN_CheckServiceUnavailableEvent(
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    /* 过滤非业务获取失败事件，非CS域或PS域业务获取失败相关事件返回VOS_ERR
    仅下述事件5个事件是业务获取失败事件 */
    if ((NAS_OM_EVENT_LOCATION_UPDATE_FAILURE != enEventId)
     && (NAS_OM_EVENT_ATTACH_FAIL             != enEventId)
     && (NAS_OM_EVENT_RAU_FAIL                != enEventId)
     && (NAS_OM_EVENT_AUTH_REJECT             != enEventId)
     && (NAS_OM_EVENT_AUTH_AND_CIPHER_REJ     != enEventId))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_RecordServiceUnavailable
 功能描述  : 记录CS或PS域业务不可用事件
 输入参数  : VOS_UINT32                          ulPid     需要上报事件的模块ID
             NAS_OM_EVENT_ID_ENUM                enEventId 需要上报的事件ID
             VOS_VOID                           *pPara     事件中的可选参数
             VOS_UINT32                          ulLen      可选参数长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月19日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月29日
    作    者   : z60575
    修改内容   : DTS2013062500138,ERROR_LOG修改
*****************************************************************************/
VOS_VOID NAS_MNTN_RecordServiceUnavailable(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU                 stServiceUnavailableEvent;
    VOS_UINT32                                              ulIsHomePlmn;
    VOS_UINT32                                              ulRet;
    VOS_UINT8                                               ucCause;

    /* 网络拒绝UE的RAU,LAU请求的原因值总是1个字节长度 */
    if ((VOS_NULL_PTR == pPara) || (1 != ulLen))
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: invalid input para.");
        return;
    }

    /* 过滤注册失败无关的事件 */
    ulRet = NAS_MNTN_CheckServiceUnavailableEvent(enEventId);
    if (VOS_OK != ulRet)
    {
        return;
    }

    /* 仅对驻留在HOME PLMN上的无服务事件进行记录，驻留其他网络不记录 */
    ulIsHomePlmn = NAS_MMC_IsRoam();
    if (VOS_TRUE == ulIsHomePlmn)
    {
        return;
    }

    /* 记录CS域或PS域业务获取失败原因 */
    ucCause = *(VOS_UINT8 *)pPara;
    if (WUEPS_PID_MM == ulPid)
    {
        NAS_MM_StoreCsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stCsUnavailableInfo);
    }
    else
    {
        NAS_GMM_StorePsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stPsUnavailableInfo);
    }

    /* 判断是否需要记录事件 */
    if ((VOS_TRUE != g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
     && (VOS_TRUE != g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired))
    {
        return;
    }

    /* 判断是否需要记录:次数达上限，则直接返回 */
    if (g_stNasMntnErrorLogMm.ucServiceUnavailableCounter >= NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: counter reach NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    /* 填写无服务事件信息 */
    PS_MEM_SET(&stServiceUnavailableEvent, 0x00, sizeof(stServiceUnavailableEvent));

    NAS_MMA_OutputUsimInfo(&stServiceUnavailableEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stServiceUnavailableEvent.stPositionInfo);

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stCsUnavailable,
               &g_stNasMntnErrorLogMm.stCsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stCsUnavailable));

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stPsUnavailable,
               &g_stNasMntnErrorLogMm.stPsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stPsUnavailable));

    /* 输出无服务事件信息 */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(ulPid,MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT),
                        &stServiceUnavailableEvent,
                        sizeof(stServiceUnavailableEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: Error Counter.");
        return;
    }

    /* 计数器累加 */
    g_stNasMntnErrorLogMm.ucServiceUnavailableCounter++;

    /* 清除已记录信息 */
    if (VOS_TRUE == g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stCsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stCsUnavailableInfo));
    }

    if (VOS_TRUE == g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stPsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stPsUnavailableInfo));
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_RecordPlmnUnavailable
 功能描述  : 记录搜网失败事件到ERROR LOG 文件
 输入参数  : VOS_UINT8 ucValIndex 可用PLMN搜索间隔定时器时长索引
             VOS_UINT8 ucCurTimes 同一时长的可用PLMN搜索间隔定时器启动次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月6日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月29日
    作    者   : z60575
    修改内容   : DTS2013062500138,ERROR_LOG修改
*****************************************************************************/
VOS_VOID NAS_MNTN_RecordPlmnUnavailable(
    VOS_UINT8                           ucValIndex,
    VOS_UINT8                           ucCurTimes
)
{
    NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU                        *pstPlmnUnavailableEvent = VOS_NULL_PTR;
    VOS_UINT32                                                   ulRet;
    VOS_UINT32                                                   ulEventLen;
    VOS_UINT32                                                   ulPos;
    VOS_UINT8                                                    ucHighPlmnLen;
    VOS_UINT8                                                    ucLowPlmnLen;
    VOS_UINT8                                                   *pucPlmnAvailable = VOS_NULL_PTR;

    /* 判断是否需要记录:判断当前搜网间隔定时器时长及计数器数值，
       仅在搜网间隔定时器时长为5秒第5次启动时记录 */
    if ((NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO   != ucValIndex)
     || (NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES != ucCurTimes))
    {
        return;
    }

    /* 判断计数器是否达上限 */
    if (g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter >= NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: counter reach NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    ucHighPlmnLen = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulHighPlmnNum * sizeof(MNTN_PLMN_ID_STRU));
    ucLowPlmnLen  = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulLowPlmnNum * sizeof(NAS_MNTN_LOW_PLMN_INFO_STRU));
    /* 可用PLMN列表的长度不在NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU结构中计算
       aucPlmnAttempt[4]占用的4个字节需要先去掉； */
    ulEventLen = (sizeof(NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU) - 4)
                  + ((sizeof(ucHighPlmnLen) + ucHighPlmnLen)
                  + (sizeof(ucLowPlmnLen) + ucLowPlmnLen));

    pstPlmnUnavailableEvent = (NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMC, ulEventLen);
    if (VOS_NULL_PTR == pstPlmnUnavailableEvent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: Fail to alloc memory.");
        return;
    }

    /* 填写搜网失败事件信息 */
    PS_MEM_SET(pstPlmnUnavailableEvent, 0x00, ulEventLen);

    NAS_MMA_OutputUsimInfo(&pstPlmnUnavailableEvent->stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&pstPlmnUnavailableEvent->stPositionInfo);

    NAS_MMA_OutputPlmnSrchBand(&pstPlmnUnavailableEvent->ulBand);

    pucPlmnAvailable = pstPlmnUnavailableEvent->aucPlmnAttempt;
    ulPos            = 0;

    /* 填写高质量PLMN数据结构: LV格式，V部分结构为MNTN_PLMN_ID_STRU */
    *(pucPlmnAvailable + ulPos) = ucHighPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astHighPlmnList,
                ucHighPlmnLen);
    ulPos += ucHighPlmnLen;

    /* 填写低质量PLMN数据结构: LV格式，V部分结构为NAS_MNTN_LOW_PLMN_INFO_STRU */
    *(pucPlmnAvailable + ulPos) = ucLowPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astLowPlmnList,
                ucLowPlmnLen);

    /* 输出搜网失败事件信息 */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_MMC, MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT),
                         pstPlmnUnavailableEvent, ulEventLen);
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnUnavailableEvent);

    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: fail to MNTN_RecordErrorLog.");
        return;
    }

    /* 事件计数器累加 */
    g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter++;

    return;
}

/*******************************************************************************
  Module:   NAS_EventReport
  Function: 向OM上报NAS事件
  Input:    ulPid        需要上报事件的模块ID
            enEventId    需要上报的事件ID
            Para         事件中的可选参数
            ulLen        可选参数长度
  Output:   无
  NOTE:     该函数被NAS所有任务调用，可能重入
  Return:   VOS_VOID
  History:
  1.  s46746     2008.04.29  新版做成
  2.日    期   : 2010年10月25日
    作    者   : 傅映君/f62575
    修改内容   : ERROR LOG
  3.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2015年6月27日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
VOS_VOID NAS_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    /* Modified by wx270776 for OM融合, 2015-7-23, begin */
    DIAG_EVENT_IND_STRU                 stDiagEvent;
    NAS_OM_EVENT_IND_STRUCT            *pstNasOmEvent = VOS_NULL_PTR;
    VOS_VOID                           *pData = pPara;
    VOS_UINT32                          ulNasOmEventMsgLen;
    VOS_UINT32                          ulRslt;

    /* 入参检查 */
    if ( (VOS_NULL_PTR == pData) && (ulLen != 0) )
    {
        /* 错误打印 */
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:pPara is NULL.");
        return;
    }

    /* 申请内存 */
    if (4 >= ulLen)
    {
        ulNasOmEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT);
        pstNasOmEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulNasOmEventMsgLen);
    }
    else
    {
        ulNasOmEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT) + ulLen -4;
        pstNasOmEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulNasOmEventMsgLen);
    }

    if (VOS_NULL_PTR == pstNasOmEvent)
    {
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:Alloc mem fail.");
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstNasOmEvent, 0x0, ulNasOmEventMsgLen);

    /* 填写事件消息内容 */
    pstNasOmEvent->usEventId          = enEventId;
    pstNasOmEvent->usReserve          = 0;
    if ( (VOS_NULL_PTR != pData) && (ulLen > 0) )
    {
        PS_MEM_CPY(pstNasOmEvent->aucData, pData, ulLen);
    }

    /* 填写发给DIAG的结构体 */
    stDiagEvent.ulLength              = sizeof(NAS_OM_EVENT_IND_STRUCT) - 4 + ulLen;
    stDiagEvent.ulPid                 = ulPid;
    stDiagEvent.ulEventId             = (VOS_UINT32)enEventId;
    stDiagEvent.ulModule              = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stDiagEvent.pData                 = pstNasOmEvent;

    /* 发送消息 */
    ulRslt = DIAG_EventReport(&stDiagEvent);
    if (VOS_OK != ulRslt)
    {
        /* 错误打印 */
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:DIAG_EventReport fail.");
    }

    /* 释放内存 */
    PS_MEM_FREE(ulPid, pstNasOmEvent);
    /* Modified by wx270776 for OM融合, 2015-7-23, end */


    NAS_MNTN_RecordServiceUnavailable(ulPid, enEventId, pPara, ulLen);

    return;
}

/*****************************************************************************
 Module   : NAS_SendAirMsgToOM
 Function : 上报空口消息给 OM
 Input    :  ulPid:    空口消息pid
             usMsgID:  空口消息ID
             ucUpDown: 空口消息方向(上行还是下行)
             ulMsgLen: 空口消息长度
             pucMsg:   空口消息内容
 Output  : 无
 Return  : VOS_VOID

 History:
  1.  L60609     2009.07.27  新版做成
  2.日    期   : 2012年11月1日
    作    者   : z40661
    修改内容   : DTS2012102501504
  3.日    期   : 2012年12月29日
    作    者   : l00198894
    修改内容   : DTS2012122702627: 增加SS空口消息可维可测
  4.日    期   : 2013年04月12日
    作    者   : m00217266
    修改内容   : DTS2013041202045
  5.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID NAS_SendAirMsgToOM(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          usMsgID,
    VOS_UINT8                           ucUpDown,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                          *pucMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-18, begin */
    NAS_AIR_MSG_STRU                   *pstNasAirMsg    = VOS_NULL_PTR;
    DIAG_AIR_IND_STRU                   stNasOtaAirInd;
    VOS_UINT32                          ulNasAirMsgLen;
    VOS_UINT32                          ulRet;


    PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_SendAirMsgToOM!");

    /* 入口参数检查 */
    /* 当空口消息长度为 0 或者 空口消息指针为空时，异常返回 */
    if ( (0 == ulMsgLen)
        || (VOS_NULL_PTR == pucMsg ))
    {
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_SendAirMsgToOM:WARNING: Input params invalid.");
        return;
    }

    /* 如果不需要上报空口消息，则直接返回 */
    if ( NAS_OTA_SWITCH_OFF == gulNasOTASwitch )
    {
        return;
    }

    /* 申请内存 */
#if 0
    if (8 >= ulMsgLen)
    {
        ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) + 4;
    }
    else
    {
        ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) - 4 + ulMsgLen;
    }
#endif

    ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) + ulMsgLen;

    pstNasAirMsg = (NAS_AIR_MSG_STRU*)PS_MEM_ALLOC(ulPid, ulNasAirMsgLen);
    if ( VOS_NULL_PTR == pstNasAirMsg )
    {
        NAS_WARNING_LOG(ulPid, "NAS_SendAirMsgToOM:WARNING: PS_MEM_ALLOC Failed!");
        return;
    }

    /* 初始化 */
    PS_MEM_SET(pstNasAirMsg, 0x00, ulNasAirMsgLen);

    pstNasAirMsg->usMsgId             = usMsgID;
    pstNasAirMsg->ucUpDown            = ucUpDown;
    pstNasAirMsg->ucReserve           = 0;
    pstNasAirMsg->ulLengthASN         = ulMsgLen;
    PS_MEM_CPY(pstNasAirMsg->aucNasMsg, pucMsg, ulMsgLen);

    /* 填写消息内容 */
    stNasOtaAirInd.ulModule           = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stNasOtaAirInd.ulPid              = ulPid;
    stNasOtaAirInd.ulMsgId            = usMsgID;
    stNasOtaAirInd.ulLength           = ulMsgLen + NAS_OTA_MSG_ASN_LEN_OFFSET;
    stNasOtaAirInd.pData              = pstNasAirMsg;

    switch(ucUpDown)
    {
    case NAS_OTA_DIRECTION_UP:
        stNasOtaAirInd.ulDirection    = DIAG_SIDE_NET;
        break;

    case NAS_OTA_DIRECTION_DOWN:
        stNasOtaAirInd.ulDirection    = DIAG_SIDE_UE;
        break;

    default:
        stNasOtaAirInd.ulDirection    = 0;
        break;
    }

    /* 发送消息 */
    ulRet = DIAG_AirMsgReport(&stNasOtaAirInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(ulPid, "NAS_SendAirMsgToOM: WARNING: Sending Air Msg To OM Failed!");
    }

    /* 释放内存 */
    PS_MEM_FREE(ulPid, pstNasAirMsg);

    return;
    /* Modified by wx270776 for OM融合, 2015-7-18, end */
}

/*****************************************************************************
 函 数 名  : NAS_SetNasOtaSwitch
 功能描述  : 设置OTA的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_SetNasOtaSwitch(
    VOS_UINT32                          ulNasOTASwitch
)
{
    gulNasOTASwitch = ulNasOTASwitch;
}

/*****************************************************************************
 函 数 名  : NAS_GetNasOtaSwitch
 功能描述  : 设置OTA的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GetNasOtaSwitch(VOS_VOID)
{
    return gulNasOTASwitch;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_GetErrLogAlmLevel
 功能描述  : 获取对应Alam ID的Error Log级别
 输入参数  : NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId
 输出参数  : 无
 返 回 值  : VOS_UINT16:Log等级

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* 获取Tab表长度 */
    usTableLen = sizeof(g_astNasErrAlmLevelTb)/sizeof(g_astNasErrAlmLevelTb[0]);

    /* 查表返回对应Alm ID的log等级 */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
        {
            return g_astNasErrAlmLevelTb[usStep].usLogLevel;
        }
    }

    /* 未查到，返回未定义等级 */
    return NAS_ERR_LOG_CTRL_LEVEL_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_GetErrLogUnsoliReportType
 功能描述  : 获取ERR LOG主动上报类型
 输入参数  : NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16 NAS_GetErrLogUnsoliReportType(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* 获取Tab表长度 */
    usTableLen = sizeof(g_astNasErrAlmUnsoliReportTypeTb)/sizeof(g_astNasErrAlmUnsoliReportTypeTb[0]);

    /* 查表返回对应Alm ID的log等级 */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astNasErrAlmUnsoliReportTypeTb[usStep].enAlmID == enAlmId)
        {
            return g_astNasErrAlmUnsoliReportTypeTb[usStep].enReportType;
        }
    }

    /* 未查到，返回未定义等级 */
    return NAS_ERR_LOG_REPORT_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_COM_MntnPutRingbuf
 功能描述  : 将MM层写入到RINGBUFFER中的内容勾出来
 输入参数  : ulName
             ulPid
             pucData
             ulLen
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_COM_MntnPutRingbuf(
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulMsgLen;
    /*lint -e961*/
    ulMsgLen = sizeof(NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU) - 4 + ulLen;
    /*lint +e961*/

    pstMsg = (NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MntnPutRingbuf:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, ulMsgLen);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulPid;
    /* Modified by wx270776 for OM融合, 2015-7-16, begin */
    pstMsg->ulReceiverPid               = MSP_PID_DIAG_APP_AGENT;
    /* Modified by wx270776 for OM融合, 2015-7-16, end */
    pstMsg->ulLength                    = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName                   = ulName;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pucData)
    {
        PS_MEM_CPY(pstMsg->aucContent, pucData, ulLen);
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MNTN_ConvertBaseStateToCsfbMtState
 功能描述  : 把基本状态转换为CSFB MT的过程状态
 输入参数  : NAS_ERR_LOG_BASE_STATE_ENUM_U32   :基本状态
 输出参数  : 无
 返 回 值  : NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32:CSFB MT的过程状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MNTN_ConvertBaseStateToCsfbMtState(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState
)
{
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;
    VOS_UINT32                          i;

    enCsfbMtState  = NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT;

    for (i = 0; i < (sizeof(g_astNasErrBaseStateToCsfbMtState) / sizeof(g_astNasErrBaseStateToCsfbMtState[0])); i++)
    {
        if (enBaseState == g_astNasErrBaseStateToCsfbMtState[i].enBaseState)
        {
            enCsfbMtState = g_astNasErrBaseStateToCsfbMtState[i].enCsfbMtState;
        }
    }

    return enCsfbMtState;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_ConvertOosEventToOosCause
 功能描述  : 把OOS事件转换为OOS的原因值
 输入参数  : NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32  : 无服务事件
 输出参数  : 无
 返 回 值  : NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32  : 无服务原因
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月21日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32 NAS_MNTN_ConvertOosEventToOosCause(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
)
{
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause;
    VOS_UINT32                          i;

    enOosCause  = NAS_ERR_LOG_OOS_CAUSE_NULL;

    for (i = 0; i < (sizeof(g_astNasErrOosEventToOosCause) / sizeof(g_astNasErrOosEventToOosCause[0])); i++)
    {
        if (enOosEvent == g_astNasErrOosEventToOosCause[i].enOosEvent)
        {
            enOosCause = g_astNasErrOosEventToOosCause[i].enOosCause;
        }
    }

    return enOosCause;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SndLogMsg
 功能描述  : 发送LOG消息
 输入参数  : pcData       --- 数据指针
             ulDataLength --- 数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2014年7月10日
    作    者   : j00174725
    修改内容   : TQE
*****************************************************************************/
VOS_VOID NAS_MNTN_SndLogMsg(VOS_CHAR *pcData, VOS_UINT32 ulDataLength)
{
    TAF_MNTN_LOG_PRINT_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulRet;

    /* 消息长度 = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + 数据实际长度 + 字符串结束符'\0' */
    /*lint -e961*/
    ulMsgLength = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + ulDataLength + 1;
    /*lint +e961*/

    /* 申请消息 */
    pstMsg = (TAF_MNTN_LOG_PRINT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                WUEPS_PID_TAF,
                                ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               ulMsgLength - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ulMsgName       = MN_CALLBACK_LOG_PRINT;
    pstMsg->enModemId       = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    PS_MEM_CPY(pstMsg->acLog, pcData, ulDataLength);
    pstMsg->acLog[ulDataLength] = '\0';

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SndLogMsg:ERROR:Snd Msg Fail.");
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_LogPrintf
 功能描述  : NAS可维可测LOG输出
 输入参数  : VOS_CHAR *pcFmt
             ...
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID NAS_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[NAS_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* 格式化输出BUFFER */
    /*lint -e530 -e830*/
    NAS_MNTN_LOG_FORMAT(ulPrintLength, acBuf, NAS_TRACE_BUF_LEN, pcFmt);
    /*lint +e530 +e830*/

    /* 选择输出ASEHLL或CSHELL */
    if (NAS_TRACE_OUTPUT_ASHELL == (NAS_TRACE_OUTPUT_ASHELL & g_ulNasTraceOutput))
    {
        NAS_MNTN_SndLogMsg(acBuf, ulPrintLength);
    }

    if (NAS_TRACE_OUTPUT_CSHELL == (NAS_TRACE_OUTPUT_CSHELL & g_ulNasTraceOutput))
    {
        (VOS_VOID)vos_printf("%s", acBuf);
    }

    return;
}
/*lint +esym(960,69)*/

/*****************************************************************************
 函 数 名  : NAS_MNTN_SetTraceLevel
 功能描述  : 设置可维可测追踪级别
 输入参数  : ulLvl --- 追踪级别
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MNTN_SetTraceLevel(VOS_UINT32 ulLvl)
{
    g_ulNasTraceLevle = (ulLvl >= NAS_TRACE_LEVEL_TOP) ? NAS_TRACE_LEVEL_TOP : ulLvl;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SetTraceOutput
 功能描述  : 设置可维可测追踪输出端
 输入参数  : ulOutput --- 追踪输出端
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MNTN_SetTraceOutput(VOS_UINT32 ulOutput)
{
    g_ulNasTraceOutput = (ulOutput >= NAS_TRACE_OUTPUT_ALL) ? NAS_TRACE_LEVEL_TOP : ulOutput;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveLogEventState
 功能描述  : 将MML中存储的Event state信息保存到指定地址
 输入参数  : NAS_MML_SAVE_EXC_LOG_STRU *pstNasMmlSaveExcLog --- 保存的目标地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月02日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MNTN_SaveLogEventState(
    NAS_MML_SAVE_EXC_LOG_STRU          *pstNasMmlSaveExcLog
)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState    = VOS_NULL_PTR;

    pstLogEventState = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);

    PS_MEM_CPY(&(pstNasMmlSaveExcLog->stLogEventState),
               pstLogEventState,
               sizeof(NAS_MML_LOG_EVENT_STATE_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveSimInfo
 功能描述  : 将MML中存储的Sim info信息保存到指定地址
 输入参数  : NAS_MML_SAVE_EXC_LOG_STRU *pstNasMmlSaveExcLog --- 保存的目标地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月02日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MNTN_SaveSimInfo(
    NAS_MML_SAVE_EXC_LOG_STRU          *pstNasMmlSaveExcLog
)
{
    NAS_MML_SIM_INFO_STRU              *pstSimInfo          = VOS_NULL_PTR;

    pstSimInfo = NAS_MML_GetSimInfo();

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stSimStatus),
                &(pstSimInfo->stSimStatus),
                sizeof(NAS_MML_SIM_STATUS_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stMsIdentity),
                &(pstSimInfo->stMsIdentity),
                sizeof(NAS_MML_SIM_MS_IDENTITY_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stPsSecurity),
                &(pstSimInfo->stPsSecurity),
                sizeof(NAS_MML_SIM_PS_SECURITY_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stCsSecurity),
                &(pstSimInfo->stCsSecurity),
                sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stSimNativeContent),
                &(pstSimInfo->stSimNativeContent),
                sizeof(NAS_MML_SIM_NATIVE_CONTENT_STRU));

    pstNasMmlSaveExcLog->enCallMode = pstSimInfo->enCallMode;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveMsCfgInfo
 功能描述  : 将MML中存储的MS cfg信息保存到指定地址
 输入参数  : NAS_MML_SAVE_EXC_LOG_STRU *pstNasMmlSaveExcLog --- 保存的目标地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月02日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MNTN_SaveMsCfgInfo(
    NAS_MML_SAVE_EXC_LOG_STRU          *pstNasMmlSaveExcLog
)
{
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfgInfo        = VOS_NULL_PTR;

    pstMsCfgInfo = NAS_MML_GetMsCfgInfo();

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stMs3GppRel),
                &(pstMsCfgInfo->stMs3GppRel),
                sizeof(NAS_MML_MS_3GPP_REL_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stMsCapability),
                &(pstMsCfgInfo->stMsCapability),
                sizeof(NAS_MML_MS_CAPACILITY_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stMsSysCfgInfo),
                &(pstMsCfgInfo->stMsSysCfgInfo),
                sizeof(NAS_MML_MS_SYS_CFG_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveNetworkInfo
 功能描述  : 将MML中存储的Network Info信息保存到指定地址
 输入参数  : NAS_MML_SAVE_EXC_LOG_STRU *pstNasMmlSaveExcLog --- 保存的目标地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月02日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MNTN_SaveNetworkInfo(
    NAS_MML_SAVE_EXC_LOG_STRU          *pstNasMmlSaveExcLog
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo      = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stCampPlmnInfo),
                &(pstNetworkInfo->stCampPlmnInfo),
                sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stCsDomainInfo),
                &(pstNetworkInfo->stCsDomainInfo),
                sizeof(NAS_MML_CS_DOMAIN_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stPsDomainInfo),
                &(pstNetworkInfo->stPsDomainInfo),
                sizeof(NAS_MML_PS_DOMAIN_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stBandInfo),
                &(pstNetworkInfo->stBandInfo),
                sizeof(NAS_MML_MS_BAND_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stNetwork3GppRel),
                &(pstNetworkInfo->stNetwork3GppRel),
                sizeof(NAS_MML_NETWORK_3GPP_REL_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stConnStatus),
                &(pstNetworkInfo->stConnStatus),
                sizeof(NAS_MML_CONN_STATUS_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stEpsDomainInfo),
                &(pstNetworkInfo->stEpsDomainInfo),
                sizeof(NAS_MML_EPS_DOMAIN_INFO_STRU));

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        PS_MEM_CPY( &(pstNasMmlSaveExcLog->astPsBearerContext[i]),
                    &(pstNetworkInfo->astPsBearerContext[i]),
                    sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU));
    }

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stImsDomainInfo),
                &(pstNetworkInfo->stImsDomainInfo),
                sizeof(NAS_MML_IMS_DOMAIN_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stNoRfInfo),
                &(pstNetworkInfo->stNoRfInfo),
                sizeof(NAS_MML_NO_RF_INFO_STRU));

    PS_MEM_CPY( &(pstNasMmlSaveExcLog->stOriginalRejectCause),
                &(pstNetworkInfo->stOriginalRejectCause),
                sizeof(NAS_MML_ORIGNAL_REJECT_CAUSE_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveExcLog
 功能描述  : 将MML中存储的相关信息保存到指定地址
 输入参数  : VOS_UINT8 *pucAddr             --- 保存的目标地址
             VOS_UINT32 ulLength          --- 剩余保存的地址长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月28日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MNTN_SaveExcLog(
    VOS_UINT8                          *pucAddr,
    VOS_UINT32                          ulLength
)
{
    NAS_MML_SAVE_EXC_LOG_STRU          *pstNasMmlSaveExcLog = VOS_NULL_PTR;
    VOS_UINT32                          ulNasFilledLength;

    /* 入参检查 */
    if ( ( VOS_NULL_PTR == pucAddr )
      || ( 0 == ulLength ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SaveExcLog(): No memory allocated");
        return;
    }

    ulNasFilledLength   = sizeof(NAS_MML_SAVE_EXC_LOG_STRU);

    if (ulLength < ulNasFilledLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SaveExcLog(): Memory allocated not enough");
        return;
    }

    pstNasMmlSaveExcLog    = (NAS_MML_SAVE_EXC_LOG_STRU*)pucAddr;

    /* 标示存储的有效信息的开始和结束字段 */
    pstNasMmlSaveExcLog->ulBeginTag = 0x55AA55AA;
    pstNasMmlSaveExcLog->ulEndTag = 0x55AA55AA;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MNTN_SaveExcLog(): Save MML related info before reset");

    /* Event state信息保存 */
    NAS_MNTN_SaveLogEventState(pstNasMmlSaveExcLog);

    /* SIM卡相关信息保存 */
    NAS_MNTN_SaveSimInfo(pstNasMmlSaveExcLog);

    /* MS的配置信息保存 */
    NAS_MNTN_SaveMsCfgInfo(pstNasMmlSaveExcLog);

    /* 当前驻留的网络信息保存 */
    NAS_MNTN_SaveNetworkInfo(pstNasMmlSaveExcLog);

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MNTN_SaveGunasExcLog
 功能描述  : 临终遗言中保留GUNAS的相关信息
 输入参数  : VOS_VOID
             VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月28日
    作    者   : z00359541
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MNTN_SaveGunasExcLog( VOS_VOID )
{
    VOS_UINT8                          *pucSaveAddr   = VOS_NULL_PTR;
    VOS_UINT32                          ulLeftLength   = 0;

    /* 申请失败，则反馈VOS_FALSE */
    if ( VOS_NULL_PTR == gpucGunasExcAddr )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SaveGunasExcLog(): No memory allocated");
        return;
    }

#if defined (INSTANCE_1)
    pucSaveAddr     = gpucGunasExcAddr + GUNAS_SAVE_EXC_LOG_LENGTH_MODEM0;
    ulLeftLength    = GUNAS_SAVE_EXC_LOG_LENGTH_MODEM1;

    /* 拷贝MML的全局变量信息 */
    NAS_MNTN_SaveExcLog( ( VOS_UINT8 *)pucSaveAddr, ulLeftLength);
#elif defined (INSTANCE_2)
    pucSaveAddr     = gpucGunasExcAddr + GUNAS_SAVE_EXC_LOG_LENGTH_MODEM0 + GUNAS_SAVE_EXC_LOG_LENGTH_MODEM1;
    ulLeftLength    = GUNAS_SAVE_EXC_LOG_LENGTH_MODEM2;

    /* 拷贝MML的全局变量信息 */
    NAS_MNTN_SaveExcLog( ( VOS_UINT8 *)pucSaveAddr, ulLeftLength);
#else
    pucSaveAddr     = gpucGunasExcAddr;
    ulLeftLength    = GUNAS_SAVE_EXC_LOG_LENGTH_MODEM0;

    /* 拷贝MML的全局变量信息 */
    NAS_MNTN_SaveExcLog( ( VOS_UINT8 *)pucSaveAddr, ulLeftLength);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_RegisterDumpCallBack
 功能描述  : MMC注册异常复位dump信息及回调函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月28日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_RegisterDumpCallBack( VOS_VOID )
{
#if defined (INSTANCE_1)
#elif defined (INSTANCE_2)
#else
    /* 调用底软接口进行申请内存 */
    /*分配内存*/
    gpucGunasExcAddr = (VOS_UINT8 *)mdrv_om_register_field(OM_CP_GUNAS,
                                                           "GUNAS dump",
                                                           VOS_NULL_PTR,
                                                           VOS_NULL_PTR,
                                                           ( GUNAS_SAVE_EXC_LOG_LENGTH_MODEM0 + GUNAS_SAVE_EXC_LOG_LENGTH_MODEM1 + GUNAS_SAVE_EXC_LOG_LENGTH_MODEM2),
                                                           0);

#endif

    /* 保存GUPS复位前的临终遗言信息,注册回调函数 */
    (VOS_VOID)mdrv_om_register_callback("GUNAS_EXCLOG", (dump_hook)NAS_MNTN_SaveGunasExcLog);
    NAS_TRACE_HIGH("register call back function finished");

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

