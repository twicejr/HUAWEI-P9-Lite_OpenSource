/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年11月12日
  最近修改   :
  功能描述   : NAS MMC L1 Main状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmMain.h"
#include "NasMmcTimerMgmt.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#include "NasMmcSndInternalMsg.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcFsmMainTbl.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "PsRrmInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSMMAIN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 预处理状态机 */

/* NAS MMC状态机 */
NAS_FSM_DESC_STRU                       g_stNasMmcMainFsmDesc;


/*新增状态动作处理表 */
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/* NAS_MMC_L1_STA_NULL动作表 */
NAS_ACT_STRU   g_astNasMmcNullActTbl[]                      =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_START_REQ,
                      NAS_MMC_RcvStartReq_NULL),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SWITCH_ON_RSLT_CNF,
                      NAS_MMC_RcvSwitchOnRslt_NULL),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvPowerOffReq_NULL),
};

/* NAS_MMC_L1_STA_INITIAL动作表 */
NAS_ACT_STRU   g_astNasMmcInitialActTbl[]                   =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_MMC_POWER_OFF_REQ,
                     NAS_MMC_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     MMCMMC_POWER_OFF_RSLT_CNF,
                     NAS_MMC_RcvPowerOffRslt_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvSysCfgReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvSyscfgRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_MMC_RcvTafPlmnListReq_L1Main),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_MMC_RcvMsccCsgListSearchReq_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH,
                      NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main),

#endif
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST,
                      NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_PLMN_LIST_RSLT_CNF,
                      NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main),

    /* MSCC发送过来的用户指定搜网请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvPlmnSpecialReq_L1Main),

    /* MSCC发送过来的开机搜网请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_L1Main),

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    /* MSCC发送过来的获取请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_L1Main),

    /* MSCC发送过来的注册请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_L1Main),

    /* MSCC发送过来的PowerSave请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_L1Main),
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

#if (FEATURE_ON == FEATURE_DSDS)
    /* MSCC发送过来的ID_MSCC_MMC_SRV_ACQ_REQ */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SRV_ACQ_REQ,
                      NAS_MMC_RcvMsccSrvAcqReq_L1Main),
#endif

    /* MMC内部发起的搜网请求 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvInterPlmnSrchReq_Initial),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ANYCELL_SEARCH_REQ,
                      NAS_MMC_RcvInterAnyCellSrchReq_Initial),

    /* 收到搜网完成回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_PLMN_SELECTION_RSLT_CNF,
                      NAS_MMC_RcvMmcPlmnSelectionRslt_Initial),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ANYCELL_SEARCH_RSLT_CNF,
                      NAS_MMC_RcvMmcAnycellSearchRslt_Initial),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_GET_GEO_RSLT_CNF,
                      NAS_MMC_RcvMmcGetGeoRslt_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      NAS_MMC_RcvRrmPsStatusInd_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_IND,
                      NAS_MMC_RcvMmCmServiceInd_Initial),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CSFB_ABORT_IND,
                      NAS_MMC_RcvMmCsfbAbortInd_Initial),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_PLMN_SEARCH_IND,
                      NAS_MMC_RcvMmPlmnSearchInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_MMC_RcvUserReselReq_L1Main),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_DPLMN_SET_REQ,
                      NAS_MMC_RcvMmcInterDplmnSetReq_Initial),

    /* 底层发起的异系统重选 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvSuspendInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvSuspendInd_Initial),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvSuspendInd_Initial),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_L1Main),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_Initial),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_GET_GEO_REQ,
                      NAS_MMC_RcvMsccGetGeoReq_L1Main),


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmServiceResultInd_Initial),
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-12, begin */
    /* available Timer定时器超时 */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_AVAILABLE_TIMER,
                     NAS_MMC_RcvTiAvailTimerExpired_L1Main),

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-12, end */
};

/* NAS_MMC_L1_STA_ON_PLMN动作表 */
NAS_ACT_STRU   g_astNasMmcOnPlmnActTbl[] =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvPowerOffReq_L1Main),

    /* 收到关机状态机的回复消息  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_POWER_OFF_RSLT_CNF,
                      NAS_MMC_RcvPowerOffRslt_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvSysCfgReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvSyscfgRsltCnf_L1Main),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_MMC_RcvTafPlmnListReq_L1Main),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_MMC_RcvMsccCsgListSearchReq_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH,
                      NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main),

#endif
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST,
                      NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_PLMN_LIST_RSLT_CNF,
                      NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvUserSpecPlmnSearch_OnPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_MMC_RcvUserReselReq_L1Main),

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    /* MSCC发送过来的获取请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_L1Main),

    /* MSCC发送过来的注册请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_L1Main),

    /* MSCC发送过来的PowerSave请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_L1Main),
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    /* MMC内部发起的列表搜网请求 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_LIST_REQ,
                      NAS_MMC_RcvMmcInterPlmnListReq_OnPlmn),

    /* 底层发起的异系统重选 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_OnPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_OnPlmn),

#if (FEATURE_ON == FEATURE_DSDS)
    /* MSCC发送过来的ID_MSCC_MMC_SRV_ACQ_REQ */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SRV_ACQ_REQ,
                      NAS_MMC_RcvMsccSrvAcqReq_L1Main),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_IND,
                      NAS_MMC_RcvMmCmServiceInd_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_PLMN_SEARCH_IND,
                      NAS_MMC_RcvMmPlmnSearchInd_OnPlmn),



    /* MM发送的链接请求 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmRrConnInfoInd_OnPlmn),

    /* GMM发送的链接请求 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_OnPlmn),

    /* CS业务导致卡无效过来的请求 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_OnPlmn),

    /* PS域注册结果消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvPsRegResultInd_OnPlmn),

    /* CS域注册结果消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvCsRegResultInd_OnPlmn),

    /* 收到 MM Abort消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_OnPlmn),

    /*网络发起的detach*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvNetworkDetachInd_OnPlmn),

    /* available Timer定时器超时 */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_AVAILABLE_TIMER,
                     NAS_MMC_RcvTiAvailTimerExpired_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      NAS_MMC_RcvRrmPsStatusInd_L1Main),

    /* AS上报的系统消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfo_OnPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfo_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_OnPlmn),

    /* AS上报当前丢网 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_OnPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_OnPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER,
                      NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_FORBID_LA_TIMER,
                      NAS_MMC_RcvForbLaTimerExpired_OnPlmn ),

    /* 重选状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST,
                      NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_OnPlmn),



    /* 收到HPLMN定时器超时消息,尝试进行高优先级/背景搜索 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_HPLMN_TIMER,
                      NAS_MMC_RcvTiHplmnTimerExpired_OnPlmn),

    /* 收到10s周期性尝试高优先级搜网定时器超时消息，尝试进行高优先级/背景搜索 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                      NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_OnPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER,
                      NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_OnPlmn),

    /* 收到背景搜状态机完成结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_BG_PLMN_SEARCH_RSLT_CNF,
                      NAS_MMC_RcvBgPlmnSearchRsltCnf_OnPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_OnPlmn),

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_NCELL_INFO_NOTIFY,
                      NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn),
#endif

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_L1Main),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_OnPlmn),

    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_OnPlmn),

    /* attach ind */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_OnPlmn),
    /* tau ind */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn),

    /* detach还待确认 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_OnPlmn),

    /* Service ind:ID_LMM_MMC_SERVICE_RESULT_IND */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn),

    /* 收到L模的丢网消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmAreaLostInd_OnPlmn),

    /* 收到LMM的异系统重选消息,调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn),


    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_L1Main),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn),
#endif

#endif

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_OnPlmn),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */

#if (FEATURE_IMS == FEATURE_ON)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_SWITCH_STATE_IND,
                      NAS_MMC_RcvMsccImsSwitchStateInd_OnPlmn ),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND,
                      NAS_MMC_RcvMsccVoiceDomainChangeInd_OnPlmn ),

};

/* NAS_MMC_L1_STA_OOC动作表 */
NAS_ACT_STRU   g_astNasMmcOOCActTbl[]   =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_POWER_OFF_RSLT_CNF,
                      NAS_MMC_RcvPowerOffRslt_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvSysCfgReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvSyscfgRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_MMC_RcvTafPlmnListReq_L1Main),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_MMC_RcvMsccCsgListSearchReq_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH,
                      NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main),
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    /* MSCC发送过来的获取请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_L1Main),

    /* MSCC发送过来的中注册请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_L1Main),

    /* MSCC发送过来的PowerSave请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_L1Main),
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST,
                      NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_PLMN_LIST_RSLT_CNF,
                      NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main),

#if (FEATURE_ON == FEATURE_DSDS)
    /* MSCC发送过来的ID_MSCC_MMC_SRV_ACQ_REQ */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SRV_ACQ_REQ,
                      NAS_MMC_RcvMsccSrvAcqReq_L1Main),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_IND,
                      NAS_MMC_RcvMmCmServiceInd_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvPlmnSpecialReq_L1Main),

    /* available Timer定时器超时 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_AVAILABLE_TIMER,
                      NAS_MMC_RcvTiAvailTimerExpired_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      NAS_MMC_RcvRrmPsStatusInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_MMC_RcvUserReselReq_L1Main),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_L1Main),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_L1Main),

    /* Modified by z00161729 for DCM定制需求和遗留问题DTS2012090401384, 2012-9-4, begin */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn),
    /* Modified by z00161729 for DCM定制需求和遗留问题DTS2012090401384, 2012-9-4, end */
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_NCELL_INFO_NOTIFY,
                      NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_Ooc),
};
/* In NAS_MMC_L1_STA_DEACT state, action table
   reference NAS_MMC_L1_STA_OOC，
*/
NAS_ACT_STRU g_astNasMmcDeactActTbl[]  =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_POWER_OFF_RSLT_CNF,
                      NAS_MMC_RcvPowerOffRslt_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvSysCfgReq_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvSyscfgRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_MMC_RcvTafPlmnListReq_L1Main),


#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_MMC_RcvMsccCsgListSearchReq_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH,
                      NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main),

#endif
    /* MSCC发送过来的获取请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_L1Main),

    /* MSCC发送过来的中注册请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_L1Main),

    /* MSCC发送过来的PowerSave请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST,
                      NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_PLMN_LIST_RSLT_CNF,
                      NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main),
#if (FEATURE_ON == FEATURE_DSDS)
    /* MSCC发送过来的ID_MSCC_MMC_SRV_ACQ_REQ */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SRV_ACQ_REQ,
                      NAS_MMC_RcvMsccSrvAcqReq_L1Main),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvPlmnSpecialReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      NAS_MMC_RcvRrmPsStatusInd_L1Main_Deactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_MMC_RcvUserReselReq_L1Main),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_L1Main),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_L1Main),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn),
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_NCELL_INFO_NOTIFY,
                      NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_Deact),
#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_Deact),
#endif
};
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
NAS_STA_STRU g_astNasMmcL1MainStaTbl[] =
{
    /*****************定义及关机到开机初始化状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_L1_STA_NULL,
                      g_astNasMmcNullActTbl ),

    /*****************定义搜网注册状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_L1_STA_INITIAL,
                      g_astNasMmcInitialActTbl ),

    /*****************定义在驻留及限制驻留时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_L1_STA_ON_PLMN,
                      g_astNasMmcOnPlmnActTbl ),

    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_L1_STA_OOC,
                      g_astNasMmcOOCActTbl ),

    /*****************定义在DEACTIVE状态时候的状态转移表*********************/
    NAS_STA_TBL_ITEM( NAS_MMC_L1_STA_DEACT,
                      g_astNasMmcDeactActTbl ),
};

/*****************************************************************************
 函 数 名  : NAS_MMC_GetL1MainStaTblSize
 功能描述  : 获取L1MAIN状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:L1MAIN状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetL1MainStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMainFsmDescAddr
 功能描述  : 获取MAIN状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcMainFsmDesc);
}

/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
