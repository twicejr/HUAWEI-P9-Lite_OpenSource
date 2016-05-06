/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmAnyCellSearchTbl.c
  版 本 号   : 初稿
  作    者   : likelai /00130025
  生成日期   : 2011年07月19日
  最近修改   :
  功能描述   : NAS 层状态机AnycellSearch状态处理表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月19日
    作    者   : likelai /00130025
    修改内容   : Added for V7R1 phase II

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmAnyCellSearch.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcTimerMgmt.h"

#include "NasMmcSndInternalMsg.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_ANYCELL_SEARCH_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* NAS MMC状态机数组:搜网层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcAnyCellSearchFsmDesc;

/* NAS_MMC_ANYCELL_SEARCH_STA_INIT Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchInitActTbl[]        =
{

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ANYCELL_SEARCH_REQ,
                      NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init),
};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND,
                      NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf),

};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf),

};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf),

};
#endif

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};
#endif

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),


};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd),
};


#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF Anycell动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLSysInfoIndActTbl[]                =
{
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLSysInfoInd),

};

#endif


/* 协议栈无卡搜网注册L2状态机 */
NAS_STA_STRU g_astNasMmcAnyCellSearchStaTbl[] =
{
    /* 等待消息状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_INIT,
                          g_astNasAnyCellSearchInitActTbl ),

    /*  等待W模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitWasPlmnSrchCnfActTbl ),

    /*  等待G模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitGasPlmnSrchCnfActTbl),

#if   (FEATURE_ON == FEATURE_LTE)
    /*  等待L模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitLmmPlmnSrchCnfActTbl),

#endif
    /* 等待W模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitWasSuspendCnfActTbl),

    /* 等待G模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitGasSuspendCnfActTbl),

#if   (FEATURE_ON == FEATURE_LTE)

    /* 等待L模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitLmmSuspendCnfActTbl),
#endif

    /* 等待W模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitWasPlmnStopCnfActTbl),

    /* 等待G模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitGasPlmnStopCnfActTbl),


    /* 等待W模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitWSysInfoIndActTbl ),

    /* 等待G模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitGSysInfoIndActTbl ),

#if   (FEATURE_ON == FEATURE_LTE)

    /*  等待L模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitLmmPlmnStopCnfActTbl),


    /* 等待L模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitLSysInfoIndActTbl ),

#endif

};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetAnyCellSearchStaTblSize
 功能描述  : 获取anycell搜网状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:anycell搜网状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAnyCellSearchStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMmcAnyCellSearchStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAnyCellSearchFsmDescAddr
 功能描述  : 获取手动动搜网状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向手动搜网状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetAnyCellSearchFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcAnyCellSearchFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
