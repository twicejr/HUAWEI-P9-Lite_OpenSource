/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcMsgPrioCompare.c
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年9月27日
  最近修改   :
  功能描述   : NasMmcMsgCompare.h的实现
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月27日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasComm.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include  "MmcMmInterface.h"
#include  "MmcGmmInterface.h"
#include  "NasMmcSndInternalMsg.h"
#include  "UsimPsInterface.h"
#include  "NasMmcMsgPrioCompare.h"
#include  "NasMmcFsmSyscfg.h"
#include  "NasMmcFsmPlmnSelectionTbl.h"
#include  "NasMmcFsmPLmnListTbl.h"
#include  "NasMmcFsmBgPlmnSearchTbl.h"
#include  "NasMmcFsmAnyCellSearchTbl.h"
#include  "NasMmlCtx.h"
#include  "NasMmcCtx.h"
#include  "NasMmlLib.h"
#include  "siappstk.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "PsRrmInterface.h"

#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithInterSysCcoTbl
 全局变量说明  : MMC CCO 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/

NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCcoTbl[] =
{
    /* InterSys Cco过程中收到MMC的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCco),
};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithInterSysHoTbl
 全局变量说明  : MMC HO 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysHoTbl[] =
{

    /* InterSys HO过程中收到MMC的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysHo),

};

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithInterSysCellReselTbl
 全局变量说明  : MMC cell resel 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2012年11月15日
   作    者   : s00217060
   修改内容   : DTS2012082007133:SYSCFG和用户指定搜可以打断小区重选状态机
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCellReselTbl[] =
{
    /* InterSys cellresel过程中收到用户指定搜网请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel),


    /* InterSys cellresel过程中收到syscfg设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel),

    /* InterSys cellresel过程中收到关机请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysCellResel),

    /* InterSys cellresel过程中收到DETACH请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareDetachReqPrioWithInterSysCellResel),

    /* InterSys cellresel过程中收到power save请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithInterSysCellResel),


    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel),

    /* InterSys cellresel过程中收到MMC的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel),
};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithInterSysOosTbl
 全局变量说明  : MMC OOS 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysOosTbl[] =
{

    /* OOS过程中收到关机请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysOos),


    /* OOS过程中收到用户重选请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithInterSysOos),

    /* OOS过程中收到用户LIST请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),
#if (FEATURE_ON == FEATURE_CSG)
    /* OOS过程中收到用户CSG 列表请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithInterSysOos),


    /* OOS过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH定时器超时消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithInterSysOos),
#endif

    /* OOS过程中收到用户指定搜网请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos),


    /* OOS过程中收到syscfg设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysOos),


    /* OOS过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),

    /* OOS过程中收到TI_NAS_MMC_AVAILABLE_TIMER设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_AVAILABLE_TIMER),
                             NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
    /* OOS过程中收到TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */


    /* OOS过程中收到TI_NAS_MMC_FORBID_LA_TIMER_LEN设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN),
                             NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos),

    /* OOS过程中收到用户MMCMM_CM_SERVICE_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithInterSysOos),
};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithPlmnSelectionTbl
 全局变量说明  : MMC plmn selection 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 3.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 4.日    期   : 2015年5月7日
   作    者   : b00269685
   修改内容   : 增加打断csfb 触发的搜网处理
 5.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnSelectionTbl[] =
{

    /* PlmnSelection过程中收到关机请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* PlmnSelection过程中收到PowerSave请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection),
#endif

    /* PlmnSelection过程中收到SYSCFG设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* PlmnSelection过程中收到用户重选请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* PlmnSelection过程中收到用户LIST请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* PlmnSelection过程中收到用户LIST请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

#if (FEATURE_ON == FEATURE_CSG)
    /* PlmnSelection过程中收到用户CSG 列表请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),


    /* PlmnSelection过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH定时器超时消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),
#endif

    /* PlmnSelection过程中收到用户指定搜网请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* PlmnSelection过程中收到用户MMCMM_CM_SERVICE_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* PlmnSelection过程中收到用户MMCMM_CM_SERVICE_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection),

    /* PlmnSelection过程中收到ID_LMM_MMC_SERVICE_RESULT_IND消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection),

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

    /* PlmnSelection过程中收到用户MMCMM_PLMN_SEARCH_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection),

    /* Added by c00318887 for 预置频点搜网优化, 2015-8-31, begin */
    /* PlmnSelection过程中收到TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection),
    /* Added by c00318887 for 预置频点搜网优化, 2015-8-31, end */

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_DPLMN_SET_REQ),
                             NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection),

};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithAnyCellTbl
 全局变量说明  : MMC any cell 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2012年5月12日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 3.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 5.日    期   : 2014年7月3日
   作    者   : z00161729
   修改内容   : DSDS III新增
 6.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithAnyCellTbl[] =
{
    /* anycell过程中收到SYSCFG设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* anycell 过程中收到关机请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* PlmnSelection过程中收到PowerSave请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* anycell过程中收到用户重选请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* anycell过程中收到用户LIST请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                            NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),
#if (FEATURE_ON == FEATURE_CSG)
    /* anycell过程中收到用户CSG 列表请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),


    /* anycell过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH定时器超时消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),
#endif

    /* anycell过程中收到用户指定搜网请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
    /* anycell过程中收到用户MMCMM_CM_SERVICE_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch),
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch),
#endif

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch),
#endif

    /* anycell过程中收到用户LIST请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* anycell过程中收到用户MMCMM_PLMN_SEARCH_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch),
    /* Added by c00318887 for 预置频点搜网优化, 2015-8-31, begin */
    /* PlmnSelection过程中收到TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch),
    /* Added by c00318887 for 预置频点搜网优化, 2015-8-31, end */
};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithSysCfgTbl
 全局变量说明  : MMC syscfg 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithSysCfgTbl[] =
{

    /* SYSCFG过程中收到MMC的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithSysCfg),

};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithPlmnListTbl
 全局变量说明  : MMC Plmn List 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2012年5月10日
   作    者   : w00176964
   修改内容   : GUL BG搜网项目调整
 3.日    期   : 2012年6月4日
   作    者   : t00212959
   修改内容   : GUL BG搜网项目调整
 4.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 5.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 6.日    期   : 2014年7月3日
   作    者   : z00161729
   修改内容   : DSDS III新增
 7.日    期   : 2015年9月8日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnListTbl[] =
{

    /* 内部list或掉卡时用户list搜网过程中收到ID_MSCC_MMC_POWER_OFF_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnList),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* PlmnSelection过程中收到PowerSave请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnList),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* 内部list搜网过程中收到ID_MSCC_MMC_SYS_CFG_SET_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnList),


    /* 内部list搜网过程中收到MSCC_MMC_PLMN_SPECIAL_REQ_STRU的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnList),


    /* 内部list搜网过程中收到ID_MSCC_MMC_PLMN_SPECIAL_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList),
#if (FEATURE_ON == FEATURE_CSG)
    /* 内部list过程中收到用户CSG 列表请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnList),
#endif

    /* 内部list搜网过程中收到ID_MSCC_MMC_PLMN_LIST_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnList),

    /* 内部list搜网过程中收到ID_MSCC_MMC_DETACH_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithPlmnList),

    /* list搜网过程中收到WAS RRMM_SUSPEND_IND 的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

    /* list搜网过程中收到GAS RRMM_SUSPEND_IND 的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnList),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* LIST搜网过程中收到LMM的挂起指示的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
    /* LIST搜网过程中收到ID_LMM_MMC_SERVICE_RESULT_IND消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
    /* OOS过程中收到TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */

};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithBgSearchTbl
 全局变量说明  : MMC Bg search 状态机消息优先级比较处理的比较表
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建

 2.日    期   : 2011年11月10日
   作    者   : zhoujun 40661
   修改内容   : 增加RRMM_SUSPEND_IND原语的优先级比较

 3.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整:BG搜网和高优先级搜网状态机合并,增加L下的消息比较
 4.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 5.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 6.日    期   : 2014年7月3日
   作    者   : z00161729
   修改内容   : DSDS III新增
 7.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithBgSearchTbl[] =
{

    /* BG搜网过程中收到ID_MSCC_MMC_POWER_OFF_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePoweroffPrioWithBgSearch),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* PlmnSelection过程中收到PowerSave请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithBgSearch),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* BG搜网过程中收到ID_MSCC_MMC_PLMN_LIST_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* BG搜网过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
    /* BG搜过程中收到TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER设置请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */
#if (FEATURE_ON == FEATURE_CSG)
    /* BG搜网过程中收到用户CSG 列表请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithBgSearch),


    /* BG搜网过程中收到TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH定时器超时消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithBgSearch),
#endif

    /* BG搜网过程中收到ID_MSCC_MMC_PLMN_SPECIAL_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch),


    /* BG搜网过程中收到ID_MSCC_MMC_SYS_CFG_SET_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithBgSearch),

    /* BG搜网过程中收到MSCC_MMC_PLMN_SPECIAL_REQ_STRU的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithBgSearch),

    /* BG搜网过程中收到STK_NAS_STEERING_OF_ROAMING_IND的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_STK_PID, STK_NAS_STEERING_OF_ROAMING_IND),
                             NAS_MMC_CompareStkRoamingIndPrioWithBgSearch),

    /* BG搜网过程中收到PS_USIM_REFRESH_IND的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             NAS_MMC_CompareUsimRefreshPrioWithBgSearch),


    /* BG搜网过程中收到ID_MSCC_MMC_UPDATE_UPLMN_NTF的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_UPDATE_UPLMN_NTF),
                             NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch),


    /* BG搜网过程中收到过程中收到接入层(WAS)上报的RRMM_SUSPEND_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),


    /* BG搜网过程中收到过程中收到接入层(GAS)上报的RRMM_SUSPEND_IND请求的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),

    /* 内部list搜网过程中收到ID_MSCC_MMC_PLMN_LIST_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithBgSearch),


#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithBgSearch),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* BG搜网过程中收到过程中收到LMM的挂起指示的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
    /* BG搜网过程中收到ID_LMM_MMC_SERVICE_RESULT_IND消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch),

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */
#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND),
                             NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch),



};
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithGetGeoTbl
 全局变量说明  : MMC GET GEO状态机消息优先级比较处理的比较表
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新建
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithGetGeoTbl[] =
{
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithGetGeo),
};

/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioCompareWithPowerOffTbl
 全局变量说明  : MMC power off 状态机消息优先级比较处理的比较表
 1.日    期   : 2015年7月9日
   作    者   : w00242748
   修改内容   : 新建

*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPowerOffTbl[] =
{

    /* BG搜网过程中收到ID_MSCC_MMC_POWER_OFF_REQ的消息优先级比较 */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff)
};



/*****************************************************************************
 全局变量名    : g_astMmcMsgPrioHighPlmnSearchCompareTbl
 全局变量说明  : MMC状态机比较函数表单
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
NAS_MMC_FSM_MSG_COMPARE_STRU g_astMmcMsgCompareTbl[] =
{
     /* CCO状态机比较函数表*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CCO,
                     g_astMmcMsgPrioCompareWithInterSysCcoTbl),

    /* HO状态机比较函数表*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_HO,
                      g_astMmcMsgPrioCompareWithInterSysHoTbl),


     /* cellresel状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CELLRESEL,
                       g_astMmcMsgPrioCompareWithInterSysCellReselTbl),

     /* OOS状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_OOS,
                       g_astMmcMsgPrioCompareWithInterSysOosTbl),


     /* PLMN Selection状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_SELECTION,
                       g_astMmcMsgPrioCompareWithPlmnSelectionTbl),


     /* anycell状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_ANYCELL_SEARCH,
                       g_astMmcMsgPrioCompareWithAnyCellTbl),

     /* SYSCFG状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_SYSCFG,
                       g_astMmcMsgPrioCompareWithSysCfgTbl),


     /* PLMN LIST状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_LIST,
                       g_astMmcMsgPrioCompareWithPlmnListTbl),

     /* BG搜索状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_BG_PLMN_SEARCH,
                       g_astMmcMsgPrioCompareWithBgSearchTbl),

     /* GET GEO状态机比较函数表*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_GET_GEO,
                       g_astMmcMsgPrioCompareWithGetGeoTbl),

     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_POWER_OFF,
                        g_astMmcMsgPrioCompareWithPowerOffTbl)

};

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsTrigerDisableLte_MoDetach
 功能描述  : 判断用户detach的时候是否需要触发disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年05月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 3.日    期   : 2015年4月17日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsTrigerDisableLte_MoDetach(
    MSCC_MMC_DETACH_REQ_STRU           *pstDetachReq
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /* 获取LTE的能力状态 */
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 如果已经disable 不需要再disable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果是LTE only模式，不要disable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* 获取LTE的UE模式 */
    enLUeMode = NAS_MML_GetLteUeOperationMode();

    /* UE模式为CS PS mode1或CS PS mode2需要disable LTE */
    if ((NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enLUeMode)
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enLUeMode))
    {
        /* 如果detach为用户触发或服务域变化触发的，且包含PS detach类型，则需要disable LTE */
        if (VOS_TRUE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReq->enDetachType,
                                                         pstDetachReq->enDetachReason))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif



/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMmcMsgPrioWithInterSysCco
 功能描述  : 将MMC收到的消息与CCO状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCco(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMmcMsgPrioWithInterSysHo
 功能描述  : 将MMC收到的消息与HO状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysHo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel
 功能描述  : 将用户指定搜网消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel
 功能描述  : 将SYSCFG消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerOffPrioWithInterSysCellResel
 功能描述  : 将关机请求消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月19日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerSavePrioWithInterSysCellResel
 功能描述  : 将power save请求消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareDetachReqPrioWithInterSysCellResel
 功能描述  : 将DetachReq消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月20日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年11月27日
   作    者   : w00176964
   修改内容   : PS域的detach需要打断状态机
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareDetachReqPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_DETACH_REQ_STRU             *pstTafDetachReq = VOS_NULL_PTR;

    pstTafDetachReq = (MSCC_MMC_DETACH_REQ_STRU *)pstMsg;

    /* ps域的detach会触发disable LTE,需要打断 */
    if ((NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI == pstTafDetachReq->enDetachType)
     || (NAS_MSCC_PIF_DETACH_TYPE_GPRS    == pstTafDetachReq->enDetachType))
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType     = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel
 功能描述  : MMCMM_PLMN_SEARCH_IND和异系统状态机的优先级比较
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd    = VOS_NULL_PTR;

    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;

    /* 不是重定向失败回退到LTE的流程时，缓存 */
    if (MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE != pstPlmnSearchInd->enPlmnSearchType)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 重定向失败回退到LTE的流程时，打断 */
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel
 功能描述  : 将MMC收到的消息与cell resel状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerOffPrioWithInterSysOos
 功能描述  : 将关机消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserReselPrioWithInterSysOos
 功能描述  : 将用户重选消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserCsgListPrioWithInterSysOos
 功能描述  : 将用户CSG LIST搜网消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnListPrioWithInterSysOos
 功能描述  : 将用户LIST搜网消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos
 功能描述  : 将用户SPEC搜网消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSysCfgSetPrioWithInterSysOos
 功能描述  : 将SYSCFG设置消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 功能描述  : 将available timer超时消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos
 功能描述  : 将TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER超时消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月11日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos
 功能描述  : 将forbid la timer超时消息与OOS状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareCmServiceIndPrioWithInterSysOos
 功能描述  : 将CM Service Ind消息与oos状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : z00161729
   修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
                 不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg = VOS_NULL_PTR;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* 正常呼叫直接丢弃该消息,紧急呼叫立即打断 */
    if (MM_EMERGENCY_CALL_TRUE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerOffPrioWithPlmnSelection
 功能描述  : 将关机消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerSavePrioWithPlmnSelection
 功能描述  : 将Power Save消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareAcqReqPrioWithPlmnSelection
 功能描述  : 将获取消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRegReqPrioWithPlmnSelection
 功能描述  : 将注册消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/* Added by c00318887 for 预置频点搜网优化, 2015-8-31, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection
 功能描述  : 将TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER超时消息与Plmn selection 状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月31日
   作    者   : c00318887
   修改内容   : 新建
  2.日    期   : 2015年12月22日
    作    者   : c00318887
    修改内容   : DTS2015121106060: phaseI定时器超时不打断用户指定搜等场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                       enPlmnSearchScene;
    
    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED                      == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH  == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH == enPlmnSearchScene))
    {
        *penAbortType                   = NAS_MMC_ABORT_FSM_DELAY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;    
    }

    *penAbortType                       = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    
}

/* Added by c00318887 for 预置频点搜网优化, 2015-8-31, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection
 功能描述  : AP下发的预置DPLMN时和选网状态机优先级比较
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月13日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          i;
    VOS_INT32                           lVersionCmpRst;
    VOS_UINT32                          ulHplmnCmpRslt;
    VOS_UINT32                          ulCurrState;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    VOS_UINT8                          *pucImsi              = VOS_NULL_PTR;
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU   *pstDplmnSetReq       = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU  *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo        = VOS_NULL_PTR;

    /* 打断当前搜网的条件:
        1. 搜网场景为开机搜网
        2. 当前正在进行漫游排序后的搜网
        3. AP下发的DPLMN列表中version或HPLMN与当前使用的不同
    */

    pstDplmnSetReq          = (NAS_MMC_INTER_DPLMN_SET_REQ_STRU *)pstMsg;
    pstDPlmnNPlmnCfgInfo    = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstPrioRatList          = NAS_MML_GetMsPrioRatList();
    ulCurrState             = NAS_MMC_GetFsmTopState();

    /* 不是选网状态机不需要打断 */
    if (NAS_MMC_FSM_PLMN_SELECTION  != NAS_MMC_GetCurrFsmId())
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 不是开机搜网场景，下一轮搜网有效，本次不打断 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON != NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 没有进行漫游排序，当前正在搜RPLMN/HPLMN，不需要打断 */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList))
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 搜网成功之后的那些状态都不需要打断 */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND       == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND        == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND   == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND   == ulCurrState))
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 从当前的IMSI中取出home plmn */
    pucImsi     = NAS_MML_GetSimImsi();
    stHplmnId   = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* 比较version是否相同 */
    lVersionCmpRst = PS_MEM_CMP(pstDplmnSetReq->aucVersionId,
                                pstDPlmnNPlmnCfgInfo->aucVersionId,
                                NAS_MCC_INFO_VERSION_LEN);


    /* 版本号不同，需要打断当前搜网 */
    if (0 != lVersionCmpRst)
    {
        NAS_TRACE_HIGH("version updating abort current plmn selection");

        *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* 比较当前使用的hplmn是否在AP预置的dplmn列表所对应的ehplmn list */
    ulHplmnCmpRslt = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHplmnId,
                                                           pstDplmnSetReq->ucEhPlmnNum,
                                                           pstDplmnSetReq->astEhPlmnInfo);


    /* hplmn在AP预置的DPLMN列表中，不需要打断当前搜网 */
    if (VOS_TRUE == ulHplmnCmpRslt)
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 比较当前的EHPLMN列表是否与AP预置的有重复的 */
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

    ulHplmnCmpRslt      = VOS_FALSE;

    for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        ulHplmnCmpRslt = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                                               pstDplmnSetReq->ucEhPlmnNum,
                                                               pstDplmnSetReq->astEhPlmnInfo);

        if (VOS_TRUE == ulHplmnCmpRslt)
        {
            *penAbortType = NAS_MMC_ABORT_BUTT;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
        }
    }

    NAS_TRACE_HIGH("EHPLMN list changed abort current plmn selection");

    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch
 功能描述  : 将available timer超时消息与AnyCell状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月11日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */


#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection
 功能描述  : 将ID_MSCC_MMC_SRV_ACQ_REQ与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;

    pstSrvAcqReq    = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;

    /* 如果是紧急呼叫则直接打断，非紧急呼叫则缓存，等搜网状态机退出后处理，
       如果搜网状态机退出后是正常服务则直接回复业务触发搜网成功结果，
       否则会再次触发业务触发搜网场景的搜网 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch
 功能描述  : 将ID_MSCC_MMC_SRV_ACQ_REQ与anycell状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSrvAcqReqPrioWithPlmnList
 功能描述  : 将ID_MSCC_MMC_SRV_ACQ_REQ与list搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSrvAcqReqPrioWithBgSearch
 功能描述  : 将ID_MSCC_MMC_SRV_ACQ_REQ与bg搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection
 功能描述  : 将SYSCFG设置消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年07月02日
   作    者   : s46746
   修改内容   : For CS/PS mode 1，增加EPS连接释放的处理
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : DTS2014063003419:SYSCFG触发高优先级接入技术搜网增加NV控制，同时
                打断搜网状态机(包括等待CS/PS注册结果状态)
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;
    VOS_UINT32                          ulNeedHighPrioRat;

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* 判断当前SYSCFG配置是否会触发SYSCFG搜网 */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    /* 如果NV打开且当前未驻留在最高优先级接入技术的PLMN上，需要打断 */
    ulNeedHighPrioRat   = NAS_MMC_IsRatPrioChangeTriggerPlmnSrch( NAS_MML_GetMsPrioRatList(),
                                    &((MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg)->stRatPrioList);

    if ( (VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg())
      && (VOS_FALSE == ulNeedPlmnSearch)
      && (VOS_TRUE == ulNeedHighPrioRat) )
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* 对不需要搜网情况具体进行判断 */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND == ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))

    {
        /* 直接在状态机中处理 */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#if   (FEATURE_ON == FEATURE_LTE)

    /* 对于不需要搜网情况下,直接在状态机中处理 */
    if ( ( VOS_FALSE == ulNeedPlmnSearch )
      && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )))
    {
        /* 直接在状态机中处理 */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#endif

    /* 其他情况则需要打断当前状态机 */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserReselPrioWithPlmnSelection
 功能描述  : 将用户重选消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserCsgListPrioWithPlmnSelection
 功能描述  : 将用户CSG LIST搜网消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection
 功能描述  : 将用户LIST搜网消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection
 功能描述  : 将用户SPEC搜网消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 1.日    期   : 2012年06月07日
   作    者   : s00217060
   修改内容   : For CS/PS mode 1，增加重新驻留LTE网络的状态判断
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserPlmnInfo;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulRlt;

    ulCurrState         = NAS_MMC_GetFsmTopState();
    pstUserPlmnInfo     = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    *penAbortType       = NAS_MMC_ABORT_BUTT;

    /* 仅需要在等待注册结果和链接释放,需要进入状态机 */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND ==  ulCurrState ) )
    {
        /* 获取当前驻留网络信息,由于收到系统消息此时获取肯定没有问题 */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* 需要判断PLMN ID和接入接入是否相同,相同则直接进入状态机 */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* 如果在等待系统消息则需要进行缓存 */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND ==  ulCurrState ))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {

        /* 获取当前驻留网络信息,由于收到系统消息此时获取肯定没有问题 */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* 需要判断PLMN ID和接入接入是否相同,相同则直接进入状态机 */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* 如果在等待系统消息则需要进行缓存 */
    if ( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND ==  ulCurrState )
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#endif

    /* 其他情况下需要打断 */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection
 功能描述  : 将CM Service Ind消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 3.日    期   : 2012年12月27日
   作    者   : t00212959
   修改内容   : DTS2012122607665 L下搜网可能时间比较长，影响紧急呼，需要立即打断
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    /* 正常呼叫直接丢弃该消息 */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 搜网和挂起状态时需要打断当前状态机 */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* 等L的搜网结果状态或等L挂起回复状态需要打断当前状态机 */
    if ((NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE == ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection
 功能描述  : 将csfb abort ind消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月7日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* 搜网和挂起状态时需要打断当前状态机 */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* 等L的挂起回复状态需要打断当前状态机 */
    if (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection
 功能描述  : 将Plmn Search Ind消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulCurrState;
    VOS_UINT8                           ucIsLteSearched;

    ulCurrState               = NAS_MMC_GetFsmTopState();
    *penAbortType             = NAS_MMC_ABORT_BUTT;
    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ucIsLteSearched           = NAS_MMC_IsSpecRatSearched_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

    if ((NAS_MMC_FSM_PLMN_SELECTION       != NAS_MMC_GetCurrFsmId())
     || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 正在搜索LTE或者已经搜索LTE时则不需要打断当前状态机 */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState )
     || (VOS_TRUE                                            == ucIsLteSearched ))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* GU搜网成功等待系统消息或者等待注册结果时不打断搜网状态机 */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND       == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND   == ulCurrState))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch
 功能描述  : anycell过程中收到用户MMCMM_PLMN_SEARCH_IND请求的消息优先级比较
 输入参数  : ulEventType :消息类型
             pstMsg      :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulIsUsimStausValid;

    *penAbortType             = NAS_MMC_ABORT_BUTT;

    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ulIsUsimStausValid        = NAS_MML_IsUsimStausValid();

    if ( (NAS_MMC_FSM_ANYCELL_SEARCH       != NAS_MMC_GetCurrFsmId())
      || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType)
      || (VOS_FALSE                        == ulIsUsimStausValid))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMmcMsgPrioWithSysCfg
 功能描述  : 将MMC收到的消息与SYSCFG状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* 默认返回消息需要丢弃 */
    *penAbortType = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerOffPrioWithPlmnList
 功能描述  : 将关机消息与LIST搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerSavePrioWithPlmnList
 功能描述  : 将Power Save消息与LIST状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareAcqReqPrioWithPlmnSelection
 功能描述  : 将获取消息与LIST状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRegReqPrioWithPlmnSelection
 功能描述  : 将注册消息与LIST状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSysCfgSetPrioWithPlmnList
 功能描述  : 将SYSCFG设置消息与LIST搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserReselPrioWithPlmnList
 功能描述  : 将用户重选消息与LIST搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserCsgListPrioWithPlmnList
 功能描述  : 将用户CSG列表搜网消息与LIST搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnListWaitGuSearchCnfState
 功能描述  : 判断是否是list搜网等gu搜网回复状态
 输入参数  : ulState - 状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:是list搜网状态机等gu搜网回复状态
             VOS_FALSE:不是list搜网状态机等gu搜网回复状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月22日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnListWaitGuSearchCnfState(
    VOS_UINT32                          ulCurrState
)
{
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
#endif
       ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList
 功能描述  : 将用户指定搜网消息与LIST搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnListPrioWithPlmnList
 功能描述  : 将用户LIST搜网消息与LIST搜网状态机的优先级进行比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月9日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserPlmnListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserDetachReqPrioWithPlmnList
 功能描述  : 将用户detach消息与LIST搜网状态机的优先级进行比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    *penAbortType    = NAS_MMC_ABORT_BUTT;


    enRat = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 判断当前用户的detach是否会触发disable LTE */
    ulTrigerDisableLte      = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);

    ulCurrState             = NAS_MMC_GetFsmTopState();

    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* 当前在L下的内部LIST搜网过程中收到用户detach消息,在CS/PS mode2下需要disable
           LTE,此时需要打断L下的内部LIST搜网,处理用户的detach流程 */
        if (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState)
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* 获取下个需要搜索的接入技术 */
        (VOS_VOID)NAS_MMC_GetNextSearchingRat_PlmnList(&enRat);

        /* 在GU下内部列表搜网时,与接入层的RRMM_NOT_CAMP_ON_IND消息对冲,挂起GU搜L
           过程中如果用户detach导致需要disable LTE,此时不在继续在L下内部LIST搜网
           退出LIST搜网状态机处理缓存的detach */
        if (((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF == ulCurrState)
          || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE    == enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSuspendIndPrioWithPlmnList
 功能描述  : 将RRMM_SUSPEND_IND消息与LIST搜网状态机的优先级进行比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月4日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2014年8月1日
    作    者   : w00167002
    修改内容   : 在等系统消息时候收到异系统信息，则打断当前状态机进行异系统操作。
  3.日    期   : 2015年9月8日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    VOS_UINT32                          ulIsPlmnListWaitGuSearchCnfState;

    ulCurrState                      = NAS_MMC_GetFsmTopState();
    ulIsPlmnListWaitGuSearchCnfState = NAS_MMC_IsPlmnListWaitGuSearchCnfState(ulCurrState);

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* LIST搜网请求与异系统指示对冲,RRC会回复List_REJ,为保证不丢弃该异系统指示
       MMC先缓存这个消息,收到List_REJ后退出状态机后处理缓存的挂起指示消息 */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((VOS_TRUE == ulIsPlmnListWaitGuSearchCnfState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 注册状态直接进入状态机中处理 */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }


    /* 在等系统消息时候直接打断LIST搜网状态机，如果丢弃，则导致不回复SUSPEDN RSP,GAS复位 */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND ==  ulCurrState )))
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* 其他情况与以前情况保持一致 */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList
 功能描述  : 将ID_RRM_PS_STATUS_IND与list搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年9月8日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* NO RF时发起LIST搜网，等待LIST搜网回复时,RRM通知资源可用,LIST搜网完成后通知不可用,可能存在重复去注册L模,需要在
       等待LIST搜网回复收到资源可用不缓存 */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
#if (FEATURE_ON == FEATURE_LTE)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState)
#endif
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF == ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF == ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* NO RF后进入LIST搜网状态机,后续如果RRM通知资源可用,需要在LIST
       搜网流程结束后触发一次搜网,因此该消息需要缓存,待LIST搜网状态
       机退出后处理一次 */
    *penAbortType   = NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList
 功能描述  : 将TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER超时消息与PLMN LIST状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月11日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch
 功能描述  : 将CM Service Ind消息与anycell状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年12月28日
   作    者   : t00212959
   修改内容   : DTS2012122607665 L下等系统消息打断后，紧急呼无法发起
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU                              *pstServiceIndMsg;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    VOS_UINT32                                              ulCurrState;

    ulCurrState             =  NAS_MMC_GetFsmTopState();
#endif

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    /* 正常呼叫直接丢弃该消息 */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* GU挂起状态且下一个要搜索的接入技术为L且还有未anycell搜索过的GU接入技术时需要打断当前状态机 */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (enRat == NAS_MML_NET_RAT_TYPE_LTE)
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF  ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFB时等L搜网回复状态需要打断当前状态机 */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch
 功能描述  : 将CM Service Ind消息与anycell状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月11日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* GU挂起状态且下一个要搜索的接入技术为L且还有未anycell搜索过的GU接入技术时需要打断当前状态机 */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFB时等L搜网回复状态需要打断当前状态机 */
    if (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF == ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList
 功能描述  : List搜网状态机与ID_LMM_MMC_SUSPEND_IND消息的优先级比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月4日
   作    者   : t00212959
   修改内容   : 新生成函数
 2.日    期   : 2015年9月8日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* LIST搜网请求与异系统指示对冲,LMM会回复List_REJ,为保证不丢弃该异系统指示
       MMC先缓存这个消息,收到List_REJ后退出状态机后处理缓存的挂起指示消息 */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF    ==  ulCurrState )
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }


    /* 注册状态直接进入状态机中处理 */
    if (( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* 其他情况与以前情况保持一致 */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList
 功能描述  : List搜网状态机与ID_LMM_MMC_SERVICE_RESULT_IND消息的优先级比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : 新生成函数


 2.日    期   : 2015年8月10日
   作    者   : w00167002
   修改内容   : DTS2015080700349:在L下内部LIST搜时候，收到被叫，收到L的SERVICE
                RESULT消息没有进行处理。

 3.日    期   : 2015年9月6日
   作    者   : z00359541
   修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
 4.日    期   : 2015年9月8日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB紧急呼时等L搜网回复状态或等L注册结果状态或等链接释放状态需要打断当前状态机  */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
          && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState)
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
#if (FEATURE_ON == FEATURE_CSG)
           || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
#endif
           ))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection
 功能描述  : 将ID_LMM_MMC_SERVICE_RESULT_IND消息与搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年12月27日
   作    者   : t00212959
   修改内容   : DTS2012122607665 L下紧急呼,csps mode1 回L的vplmn链接释放时需要打断当前状态机
 3.日    期   : 2015年3月20日
   作    者   : z00161729
   修改内容   : DTS2015031709266:l下csfb到gu搜网无任何网络搜l的rplmn成功，tau成功，等ims cap ind时，
               cc重发定时器超时，l回复service result ind指示搜网导致mmc获取下一个lte网络注册被拒限制驻留，available超时搜lte rplmn成恢复，呼叫失败
 4.日    期   : 2015年9月6日
   作    者   : z00359541
   修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
   *penAbortType         = NAS_MMC_ABORT_BUTT;

    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* CSFB紧急呼时等L注册结果或链接释放状态或csps mode1 回L的vplmn等L注册结果或链接释放时需要打断当前状态机 */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState)
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState)
         || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState))
        {
            *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
             return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }


    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {
        /* 直接在状态机中处理 */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePoweroffPrioWithBgSearch
 功能描述  : 将关机消息与用户背景搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePoweroffPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* 关机消息发送延迟退出 */
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerSavePrioWithBgSearch
 功能描述  : 将Power Save消息与BG状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareAcqReqPrioWithBgSearch
 功能描述  : 将获取消息与BG状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRegReqPrioWithBgSearch
 功能描述  : 将注册消息与BG状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSysCfgSetPrioWithBgSearch
 功能描述  : 将SYSCFG搜网消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整:增减LTE模不切换状态机
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;

    /* 判断当前SYSCFG配置是否会触发SYSCFG搜网 */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* 对不需要搜网情况具体进行判断 */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND == ulCurrState )
#if (FEATURE_ON == FEATURE_LTE)
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState )
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
#endif
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))
    {
        /* 直接在状态机中处理 */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* 其他情况则需要打断当前状态机 */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserReselPrioWithBgSearch
 功能描述  : 将user resel重选消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月9日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserReselPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareStkRoamingIndPrioWithBgSearch
 功能描述  : 将stk steer of roaming ind消息与用户高优先级搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月8日
   作    者   : w00167002
   修改内容   : 收到STK_NAS_STEERING_OF_ROAMING_IND,则立即打断当前流程
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareStkRoamingIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* BG搜网状态机在运行时,该消息先缓存,退出状态机后处理 */
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUsimRefreshPrioWithBgSearch
 功能描述  : 将usim refresh ind消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月07日
   作    者   : l00130025
   修改内容   : 适配V3R1的 Usim接口
 3.日    期   : 2011年11月8日
   作    者   : w00167002
   修改内容   : HPLMN/UPLMN/OPLMN文件发生更新，则立即打断当前的高优先级搜网，
                 而非延迟打断，这样可以初始化当前的高优先级网络列表。
 4.日    期   : 2012年5月14日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改,如果卡中UPLMN和OPLMN个数为0，初始化高优先级搜网列表
                时使用的是卡中PLMN Sel文件，该场景PLMN Sel文件改变也需打断
 5.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 6.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 7.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 8.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
 9.日    期   : 2015年02月06日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUsimRefreshPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          i;
    USIMM_STKREFRESH_IND_STRU          *pstUsimRefreshInd = VOS_NULL_PTR;

    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnList = VOS_NULL_PTR;
    VOS_UINT8                            ucIsUoplmnExist;

    pstUsimRefreshInd = (USIMM_STKREFRESH_IND_STRU *)pstMsg;

    if (USIMM_REFRESH_FILE_LIST != pstUsimRefreshInd->enRefreshType)
    {
        /* refresh消息指示所有文件都更新暂不做处理 */
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 获取UOPLMN */
    pstUserPlmnList   = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList   = NAS_MML_GetSimOperPlmnList();
    ucIsUoplmnExist   = VOS_TRUE;

    /* UPLMN个数不为0或者OPLMN个数不为0 */
    if ((0 == pstUserPlmnList->ucUserPlmnNum)
     && (0 == pstOperPlmnList->usOperPlmnNum))
    {
        ucIsUoplmnExist = VOS_FALSE;
    }

    for(i = 0; i < pstUsimRefreshInd->usEfNum; i++ )
    {
        if ((USIMM_USIM_EFHPLMNwACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFHPLMNACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
		 || (USIMM_USIM_EFEHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTGSM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTUSIM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || ((USIMM_GSM_EFPLMNSEL_ID == pstUsimRefreshInd->astEfId[i].usFileId)
          && (VOS_FALSE == ucIsUoplmnExist)))
        {
            /* H、U、O文件刷新时,BG搜网状态机中暂不刷新,退出BG搜网状态机后刷新 */
            *penAbortType   = NAS_MMC_ABORT_BUTT;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
        }
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch
 功能描述  : 将ID_MSCC_MMC_UPDATE_UPLMN_NTF消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月31日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;

}



#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserCsgListPrioWithBgSearch
 功能描述  : 将用户CSG List搜网消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnListPrioWithBgSearch
 功能描述  : 将用户List搜网消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}





/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch
 功能描述  : 将用户SpEC搜网消息与BG搜网状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* 手动模式时立即打断 */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareSuspendIndPrioWithBgSearch
 功能描述  : BG搜网状态机与RRMM_SUSPEND_IND消息的优先级比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月7日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年5月24日
   作    者   : w00176964
   修改内容   : GUL BG项目调整:异系统与BG搜网请求对冲
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG搜网请求与异系统指示对冲,RRC会回复BG ABORT,为保证不丢弃该异系统指示
       MMC先缓存这个消息,收到bg abort后退出状态机后处理缓存的挂起指示消息 */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF    ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 注册状态直接进入状态机中处理 */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* 其他情况与以前情况保持一致 */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_CompareUserDetachReqPrioWithBgSearch
 功能描述  : BG搜网状态机与ID_MSCC_MMC_DETACH_REQ消息的优先级比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年4月16日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurHighPrioPlmn = VOS_NULL_PTR;

    *penAbortType               = NAS_MMC_ABORT_BUTT;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取当前状态机的状态 */
    ulCurrState                 = NAS_MMC_GetFsmTopState();

    /* 判断当前用户的detach是否会触发disable LTE */
    ulTrigerDisableLte          = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);


    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* 当前在LTE下非挂起状态(detach请求需要确定当前的接入模式,挂起状态接入模式为BUTT),需要disable LTE时,直接打断在
           L1处理缓存的detach消息,disable LTE后通过指定搜网回GU下 */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF != ulCurrState))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* 当前在GU下如下状态需要打断:
          1)GU下BG搜网L,当前需要disable LTE
          2)GU下等待挂起回复时,当前需要搜索的高优先级网络为L,当前需要disable LTE
          此时打断到L1下处理缓存的detach消息,收到GMM的注册结果后根据L1上CS的additional值
          决定是否需要触发指定搜网 */
        if (((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF        == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF        == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE == pstCurHighPrioPlmn->enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    /* 其他情况与以前情况保持一致 */
    *penAbortType               = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch
 功能描述  : BG搜网状态机与ID_LMM_MMC_SUSPEND_IND消息的优先级比较
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG搜网请求与异系统指示对冲,RRC会回复BG ABORT,为保证不丢弃该异系统指示
       MMC先缓存这个消息,收到bg abort后退出状态机后处理缓存的挂起指示消息 */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF    ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 注册状态直接进入状态机中处理 */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* 其他情况与以前情况保持一致 */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch
 功能描述  : BG搜网状态机与ID_LMM_MMC_SERVICE_RESULT_IND消息的优先级比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年9月6日
   作    者   : z00359541
   修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
 3.日    期   : 2015年12月7日
   作    者   : z00359541
   修改内容   : DTS2015113009064: CSFB需要打断背景搜
   
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB紧急呼时等L BG搜网回复状态或等L注册结果状态或等链接释放状态或等L快速指定搜状态
       或回vplmn等L搜网回复状态需要打断当前状态机  */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
         && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF ==  ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN  ==  ulCurrState)))
        {
           *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if ((VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState))
    {
        /* 直接在状态机中处理 */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePowerOffPrioWithGetGeo
 功能描述  : 将Power Off消息与GETGEO状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithGetGeo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_FindMsgPrioCompareFun
 功能描述  : 查找消息比较函数
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
             ulFsmEntryEventType    :状态机的入口消息
             enFsmId                :状态机的ID
 输出参数  : 无
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月29日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/

NAS_MMC_MSG_COMPARE_FUNC  NAS_MMC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_astMmcMsgCompareTbl)/sizeof(NAS_MMC_FSM_MSG_COMPARE_STRU)) ; i++ )
    {
        if ( enFsmId == g_astMmcMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmcMsgCompareTbl[i];
            break;
        }
    }

    /* 未能找到该状态机的比较函数表,直接返回空指针 */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* 如果需要匹配任何消息则直接进入比较函数 */
        if ( NAS_MMC_UNIVERAL_MSG_ID == pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType )
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }

        /* 查找不同事件的比较函数 */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* 未找到处理函数直接返回空指针 */
    return VOS_NULL_PTR;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsgComparePrio
 功能描述  : 获取消息优先级比较后的结果
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
 输出参数  : pulAbortType:返回值为打断时,返回的打断类型
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月29日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 NAS_MMC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    NAS_MMC_MSG_COMPARE_FUNC                    pfCompareFunc;
    NAS_MMC_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  获取当前状态机的ID */
    enCurrFsmId         = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enCurrFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }


    /*  获取比较函数 NAS_MMC_FindMsgPrioCompareFun() */
    pfCompareFunc       = NAS_MMC_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* 未找到处理函数,则默认消息丢弃 */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 调用比较函数,返回优先级和打断类型 */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch
 功能描述  : 如果处于背景搜则推迟消息处理
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
 输出参数  : pulAbortType:返回值为打断时,返回的打断类型
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : x65241
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;

    ulCacheEventType     = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);

    /* 如果已经有同样的消息了，则仅保留一个即可*/
    if (VOS_TRUE == ulExistFlg)
    {
        NAS_MMC_ClearCacheMsg(ulCacheEventType);
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 功能描述  : 将available timer超时消息与BG 搜状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月11日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}
/* Added by c00318887 for 预置频点搜网优化, 2015-9-11, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff
 功能描述  : power off状态机时，收到资源可用消息的处理
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
 输出参数  : pulAbortType:返回值为打断时,返回的打断类型
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
