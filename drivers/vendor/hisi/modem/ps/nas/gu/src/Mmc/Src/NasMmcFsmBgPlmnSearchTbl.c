/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmBgPlmnSearchTbl.c
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2011年9月10日
  最近修改   :
  功能描述   : NAS 层仅支持GU的背景搜状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月10日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmMain.h"
#include "NasMmcFsmBgPlmnSearch.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcTimerMgmt.h"
#include "MmcGmmInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "siappstk.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* NAS MMC状态机数组:仅支持GU的背景搜网层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcBgPlmnSearchFsmDesc;


/* NAS_MMC_BG_PLMN_SEARCH_STA_INIT 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchInitActTbl[]             =
{
    /* 收到HPLMN定时器超时消息 */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_HPLMN_TIMER,
                     NAS_MMC_RcvTiHPlmnTimerExpired_BgPlmnSearch_Init),

    /* 收到High_Prio_Rat_HPLMN定时器超时消息 */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER,
                     NAS_MMC_RcvTiHighPrioRatHPlmnTimerExpired_BgPlmnSearch_Init),

    /* 收到10s周期性尝试高优先级搜网定时器超时消息 */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                     NAS_MMC_RcvTiPeriodHighPrioPlmnSearchExpired_BgPlmnSearch_Init),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasBgPlmnSearchCnfActTbl[] =
{
   NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_ABORT_FSM_REQ,
                     NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_SYS_INFO_IND,
                     NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_REL_IND,
                     NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_BG_PLMN_SEARCH_CNF,
                     NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                     TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF,
                     NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitWasBgPlmnSearchCnf),


   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_AREA_LOST_IND,
                     NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),


};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasBgPlmnSearchCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitGasBgPlmnSearchCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf),


};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgStopCnf),


    /* MMC发送stop bg search cnf时和接入层的bg search cnf消息对冲，接入层在
       回复stop bg search cnf前可能会上suspend ind，MMC在该状态无法处理该消息,
       因此收到接入层的search cnf当做收到stop search cnf,在L1 处理异系统指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf),
};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitGasBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitGasBgStopCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgStopCnf),


    /* MMC发送stop bg search cnf时和接入层的bg search cnf消息对冲，接入层在
       回复stop bg search cnf前可能会上suspend ind，MMC在该状态无法处理该消息,
       因此收到接入层的search cnf当做收到stop search cnf,在L1 处理异系统指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasFastPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasFastPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasPlmnFastSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_BgPlmnSearch_WaitWasPlmnFastSearchCnf),
};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnFastSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_BgPlmnSearch_WaitGasPlmnFastSearchCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasSysinfoIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoInd),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasSysinfoIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfo),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoInd),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitCsPsRegIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* 收到MM的Abort消息的处理 */
    NAS_ACT_TBL_ITEM(WUEPS_PID_MM,
                     MMMMC_ABORT_IND,
                     NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /*网络发起的detach*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* AS上报当前丢网 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd),


    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* 收到MSCC SYSCFG设置消息的处理 */
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitCsPsRegRsltInd),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSPS_REG_IND,
                      NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitCsPsRegRsltInd),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitCsPsConnRelActTbl[]   =
{
    /* 收到 Abort 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GMM 的 SIGNALING_STATUS_IND 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GMM 的 DETACH_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GMM 的 TBF_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GMM 的 SERVICE_REQUEST_RESULT_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 MM 的 RR_CONN_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 MM 的 RR_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 MM 的 CM_SERVICE_REJECT_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到MM的Abort消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 WAS 的 SYS_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到 GAS 的 SYS_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 收到MSCC SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitRrcConnRelInd),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitRrcConnRelInd),

    /* 收到定时器超时消息的处理  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch_WaitRrcConnRelInd),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasSuspendCnfReCampVPlmnActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasSuspendCnfReCampVPlmnActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN 动作表*/
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN 动作表*/
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasSysinfoIndReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasSysinfoIndReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfoReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn),

};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmBgPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),
#endif
};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgStopCnf),

    /* MMC发送stop bg search cnf时和接入层的bg search cnf消息对冲，接入层在
       回复stop bg search cnf前可能会上suspend ind，MMC在该状态无法处理该消息,
       因此收到接入层的search cnf当做收到stop search cnf,在L1 处理异系统指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnFastSearchCnfTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                       MMCMMC_ABORT_FSM_REQ,
                       NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),
#endif

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmFastPlmnStopCnfTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchStopCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLSysInfoIndActTbl[]   =
{
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoInd),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoInd),


    /* 删除LTE上报服务状态和注册状态的接口   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitLSysInfoInd()处理函数 */
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitEpsRegRsltIndActTbl[]   =
{
    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* 删除LTE上报服务状态和注册状态的接口   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitEpsRegRsltInd()处理函数 */



    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_BgPlmnSearch_WaitEpsRegRsltInd),

    /* 等注册的时候发生丢网 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsRegRsltInd),

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 收到MSCC SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsRegRsltInd),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsRegRsltInd),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitEpsRegRsltInd),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitEpsRegRsltInd),
#endif
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitEpsConnRelInd[]   =
{

    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* 等链接释放定时器超时 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_BgPlmnSearch_WaitEpsConnRelInd),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitEpsConnRelInd),

	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    /* 收到MSCC SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsConnRelInd),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsConnRelInd),

    /* 与北研确认:注册过程中需要处理网侧的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* 注册过程中需要处理用户的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsConnRelInd),

};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmSrchCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN 动作表 */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLSysInfoIndReCampVPlmnActTbl[]   =
{
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

};
#endif



/* NAS MMC模块BG PLMN SEARCH注册L2状态机 */
NAS_STA_STRU g_astNasMmcFsmBgPlmnSearchStaTbl[] =
{
    /* 等待消息状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_INIT,
                      g_astNasMmcBgPlmnSearchInitActTbl),

    /*  等待W模上报BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasBgPlmnSearchCnfActTbl),

    /*  等待G模上报BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasBgPlmnSearchCnfActTbl),

    /*  等待W模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF,
                       g_astNasMmcBgPlmnSearchWaitWasSuspendCnfActTbl),

    /*  等待G模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasSuspendCnfActTbl),

    /*  等待W模上报停止BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasBgPlmnStopCnfActTbl ),

    /*  等待G模上报停止BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasBgPlmnStopCnfActTbl ),

    /*  等待W模上报停止快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasFastPlmnStopCnfActTbl ),

    /*  等待G模上报停止快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasFastPlmnStopCnfActTbl ),

    /*  等待W模上报快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF,
                       g_astNasMmcBgPlmnSearchWaitWasPlmnFastSearchCnfActTbl ),

    /*  等待G模上报快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF,
                       g_astNasMmcBgPlmnSearchWaitGasPlmnFastSearchCnfActTbl ),

    /*  等待W模上报系统消息*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitWasSysinfoIndActTbl ),

    /*  等待G模上报系统消息*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitGasSysinfoIndActTbl ),

    /*  等待CS+PS域的注册结果*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND,
                      g_astNasMmcBgPlmnSearchWaitCsPsRegIndActTbl ),

    /*  等待GU链接释放 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND,
                      g_astNasMmcBgPlmnSearchWaitCsPsConnRelActTbl ),

    /*  回VPLMN时等待W模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN,
                       g_astNasMmcBgPlmnSearchWaitWasSuspendCnfReCampVPlmnActTbl),

    /*  回VPLMN时等待G模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasSuspendCnfReCampVPlmnActTbl),

    /*  回VPLMN时等待W模上报指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasPlmnSearchCnfReCampVPlmnActTbl ),

    /*  回VPLMN时等待G模上报指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasPlmnSearchCnfReCampVPlmnActTbl ),

    /*  回VPLMN时等待W模上报停止指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasPlmnStopCnfReCampVPlmnActTbl ),

    /*  回VPLMN时等待G模上报停止指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasPlmnStopCnfReCampVPlmnActTbl ),

    /*  回VPLMN时等待W模上报系统消息*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasSysinfoIndReCampVPlmnActTbl ),

    /*  回VPLMN时等待G模上报系统消息*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasSysinfoIndReCampVPlmnActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* 等待L模上报BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmBgPlmnSearchCnfActTbl),

    /*  等待L模上报停止BG搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmBgPlmnStopCnfActTbl),

    /*  等待L模上报快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnFastSearchCnfTbl),


    /*  等待L模上报停止快速指定搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmFastPlmnStopCnfTbl),


    /* 等待L模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfActTbl),

    /* 等待L模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitLSysInfoIndActTbl ),

    /* 等待eps注册结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND,
                      g_astNasMmcBgPlmnSearchWaitEpsRegRsltIndActTbl ),

    /* 等待L模链接释放结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND,
                      g_astNasMmcBgPlmnSearchWaitEpsConnRelInd ),


    /* 回VPLMN时等待L模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnSearchCnfReCampVPlmnActTbl),

    /* 回VPLMN时等待L模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfReCampVPlmnActTbl),

    /* 回VPLMN时等待L模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnStopCnfReCampVPlmnActTbl),

    /* 回VPLMN时等待L模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLSysInfoIndReCampVPlmnActTbl ),
#endif
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : NAS_MMC_GetBgPlmnSearchStaTblSize
 功能描述  : 获取BG PLMN SEARCH状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:BG PLMN SEARCH状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetBgPlmnSearchStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcFsmBgPlmnSearchStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetBgPlmnSearchFsmDescAddr
 功能描述  : 获取仅支持GU的背景搜网状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向BG PLMN SEARCH状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetBgPlmnSearchFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcBgPlmnSearchFsmDesc);
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
