/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPlmnSelectionTbl.c
  版 本 号   : 初稿
  作    者   : sunxibo /46746
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NAS 层状态机PlmnSelection状态处理表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 phase II

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmMain.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcTimerMgmt.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "MmcGmmInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_SELECTION_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/* NAS MMC状态机数组:搜网层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcPlmnSelectionFsmDesc;

/* NAS_MMC_PLMN_SELECTION_STA_PLMN_SEARCH_INIT 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    /* MMA发送过来的获取请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init),
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasPlmnSearchCnfActTbl[]        =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND,
                      NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf),
    
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasPlmnSearchCnfActTbl[]        =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf),

};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf),
#endif
};
#endif

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};


#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};

#endif


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),


};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),
};
#endif

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitCsPsRegRsltIndActTbl[]              =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSPS_REG_IND,
                      NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd),

    /*网络发起的detach*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd),

    /* AS上报当前丢网 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd),


    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd),

    /* 收到MM的Abort消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitCsPsConnRelActTbl[]              =
{
    /* 收到 GMM 的 SIGNALING_STATUS_IND 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 GMM 的的 DETACH_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 GMM 的的 TBF_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 GMM 的的 SERVICE_REQUEST_RESULT_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 MM 的 SERVICE_REQUEST_RESULT_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 MM 的 RR_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 MM 的 CM_SERVICE_REJECT_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 WAS 的 SYS_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 GAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 GAS 的 SYS_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* 收到定时器超时消息的处理  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 Abort 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd),

    /* 收到 MM Abort 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd),

};

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitMsccRegReqActTbl[]                =
{
    /* 收到 MMA 的 ID_MMA_MMC_REG_REQ 消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq),

    /* 等MMA的注册请求消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MSCC_REG_REQ,
                      NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq),

    /* 收到L模的挂起的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq),

    /* 收到L模的出服务区的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq),

#endif
};
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLSysInfoIndActTbl[]              =
{
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRegRsltIndActTbl[]         =
{
    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd),

    /* 等注册的时候发生丢网 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF,
                      NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd),
#endif
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsConnRelInd[]         =
{
    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd),

    /* 等链接释放定时器超时 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsConnRelInd),

    /* 与北研确认:注册过程中需要处理网侧的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd),

    /* 注册过程中需要处理用户的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasSuspendCnfCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasSuspendCnfCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfCsPsMode1ReCampLteActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfCsPsMode1ReCampLteActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    /* MMC发送stop search cnf时和接入层的search cnf消息对冲，接入层在快速指定搜或指定搜过程不会再
       回复stop search cnf，MMC收到接入层的search cnf当做收到stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmSysInfoIndCsPsMode1ReCampLteActTbl[]              =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRegIndCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* suspend状态机完成结果的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 等注册的时候发生丢网 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE 动作表 */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRelIndCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 等链接释放定时器超时 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 收到MMA 指定搜网消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 收到MMA SYSCFG设置消息的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 处理SYSCFG 状态机的结果 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 与北研确认:注册过程中需要处理网侧的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* 注册过程中需要处理用户的detach结果 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),
};
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#endif

/* NAS MMC模块PLMN SELECTION注册L2状态机 */
NAS_STA_STRU g_astNasMmcPlmnSelectionStaTbl[] =
{
    /* 等待消息状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_INIT,
                          g_astNasMmcPlmnSelectionInitActTbl ),

    /*  等待W模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitWasPlmnSearchCnfActTbl ),

    /*  等待G模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitGasPlmnSearchCnfActTbl),

    /*  等待W模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitWasSuspendCnfActTbl),

    /*  等待G模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitGasSuspendCnfActTbl),

    /*  等待W模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitWasPlmnStopCnfActTbl),

    /*  等待G模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitGasPlmnStopCnfActTbl),

     /*  等待W模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitWSysInfoIndActTbl ),

    /*  等待G模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitGSysInfoIndActTbl ),

    /*  等待csps注册结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND,
                          g_astNasMmcPlmnSelectionWaitCsPsRegRsltIndActTbl ),

    /*  等待链接释放结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND,
                          g_astNasMmcPlmnSelectionWaitCsPsConnRelActTbl ),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /*  等待MMA的注册请求 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ,
                          g_astNasMmcPlmnSelectionWaitMsccRegReqActTbl ),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
    /*  等待L模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfActTbl),

    /*  等待L模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmSuspendCnfActTbl),

    /*  等待L模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfActTbl),

    /*  等待L模上报系统消息结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitLSysInfoIndActTbl ),

    /*  等待eps注册结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND,
                          g_astNasMmcPlmnSelectionWaitEpsRegRsltIndActTbl ),

    /*  等待L模链接释放结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND,
                          g_astNasMmcPlmnSelectionWaitEpsConnRelInd ),

    /*  CS/PS mode 1重回L模等待W模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitWasSuspendCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待G模上报挂起结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitGasSuspendCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待L模上报搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待L模上报停止搜网结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待L模上报系统消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmSysInfoIndCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待EPS域的注册结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitEpsRegIndCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1重回L模等待EPS连接释放 */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitEpsRelIndCsPsMode1ReCampLteActTbl ),
#endif
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionStaTblSize
 功能描述  : 获取PLMN SELECTION状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:PLMN SELECTION状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月04日
    作    者   : sunxibo 46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnSelectionStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcPlmnSelectionStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionFsmDescAddr
 功能描述  : 获取自动搜网状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向PLMN SELECTION状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月04日
    作    者   : sunxibo 46746
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnSelectionFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcPlmnSelectionFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
