/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NasUtranCtrlFsmMainTbl.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月13日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmMainTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMain.h"
#include "MsccMmcInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasUtranCtrlMntn.h"

#include "MmcGmmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MAIN_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* 预处理状态机 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlMainFsmDesc;


/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* IDLE状态机处理的消息动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlMainProcessActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvWasSysInfo_Main ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvGasSysInfo_Main ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvTdSysInfo_Main ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvLmmSysInfo_Main ),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_START_CNF,
                      NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_START_CNF,
                      NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main),

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvPlmnSpecialReq_Main),
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvPlmnSearchReq_Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_UTRANCTRL_RcvMsccAcqReq_Main),


    /* 收到Was的开机回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_Main),

    /* 收到Was的开机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main),

    /* 收到Td的开机回复消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_Main),

    /* 收到TD的开机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main),

    /* 收到Was的关机回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_Main),

    /* 收到WAS的关机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main),


    /* 收到TD的关机回复消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_Main),

    /* 收到TD的关机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main),

    /* 收到Was的syscfg设置回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_Main),

    /* 收到WAS的SYSCFG回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main),

    /* 收到Td的syscfg设置回复消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_Main),

    /* 收到TD的SYSCFG回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main),

    /* 收到Was的搜网回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ,
                     NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_Main),


    /* 收到MMC发送的跳过搜网W消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_Main),


    /* 收到MMC发送的跳过搜网TDS消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_TDS_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_Main),

    /* 收到WAS的搜网回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvWasRrMmRelInd_Main),

    /* 收到TD的搜网回复消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main),

    /* 收到TD的搜网回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main),

    /* 收到Was的搜网回复消息 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvGasPlmnSrchCnf_Main),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main ),
#endif
    /* 收到Was的搜网回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ANYCELL_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),

     NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_HPLMN_TIMER,
                      NAS_UTRANCTRL_RcvTiHplmnTimerExpired_Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                      NAS_UTRANCTRL_RcvTiTryingHighPrioPlmnSearchExpired_Main),

#ifdef __PS_WIN32_RECUR__
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY,
                      NAS_UTRANCTRL_RestoreContextData_Main),

#endif

};

/* MAIN状态机处理的消息 状态表 */
NAS_STA_STRU        g_astNasUtranCtrlMainProcessFsmTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MAIN_STA_INIT,
                      g_astNasUtranCtrlMainProcessActTbl )
};

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetMainProcessStaTblSize
 功能描述  : 获取适配层主处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:适配层主处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月14日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetMainProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlMainProcessFsmTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetMainFsmDescAddr
 功能描述  : 获取适配层主处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向适配层主处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月14日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlMainFsmDesc);
}
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
