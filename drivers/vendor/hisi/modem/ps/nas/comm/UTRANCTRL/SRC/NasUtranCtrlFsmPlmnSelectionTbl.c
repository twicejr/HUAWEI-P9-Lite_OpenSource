/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmPlmnSelectionTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : UTRAN控制模块状态转移表
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月4日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmPlmnSelection.h"
#include "MsccMmcInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* UTRANCTRL模块的选网状态机 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlPlmnSelectionFsmDesc;

/**************************************************************************/
/* 新增状态动作处理表 */
/**************************************************************************/

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init),


    /* 收到MMC发送的跳过搜网W消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init),


    /* 收到MMC发送的跳过搜网TDS消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_TDS_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init),

    /* 收到WAS的搜网回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init),

    /* 搜网时收到WAS的接入层复位消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init),

    /* 收到TD的搜网回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfSearchTDActTbl[]   =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),
 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfSearchWActTbl[]   =
{

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),
   /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),
   /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
   /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf),

};



/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    /* 异常回复消息保护 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ,
                     NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf),


    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                     ID_MSCC_MMC_POWER_OFF_REQ,
                     NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),
   /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfActTbl[]   =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf),

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfBackTDActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                     ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                     NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_TDRRC_SUSPEND_CNF_BACK_W 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnBackWfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
   /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW),
};



/* 搜网状态机处理的消息 状态表 */
NAS_STA_STRU        g_astNasUtranCtrlPlmnSelectionStaTbl[]   =
{
    /* 搜网状态机初始化状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT,
                      g_astNasUtranCtrlPlmnSelectionInitActTbl ),

    /* 搜网状态机等待was挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfSearchTDActTbl ),

    /* 搜网状态机等待TDRRC挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfSearchWActTbl ),

    /* 搜网状态机等待was挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfActTbl ),

    /* 搜网状态机等待TDRRC挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnfActTbl ),

    /* 搜网状态机等待WAS搜网回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnSearchCnfActTbl ),

    /* 搜网状态机等待TDRRC搜网回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnSearchCnfActTbl ),

    /* 搜网状态机等待WAS停止搜网回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfActTbl ),

    /* 搜网状态机等待TDRRC停止搜网回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfActTbl ),

    /* 搜网状态机等待回到TD时WAS的挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD,
                      g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfBackTDActTbl ),

    /* 搜网状态机等待回到W时TDRRC挂起回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W,
                      g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnBackWfActTbl ),
};

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetPlmnSelectionStaTblSize
 功能描述  : 获取适配层搜网状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:适配层搜网状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetPlmnSelectionStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlPlmnSelectionStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr
 功能描述  : 获取适配层搜网状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向适配层搜网状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlPlmnSelectionFsmDesc);
}
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
