/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSysAcqTbl.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月17日
  功能描述   : HRPD L2 SYSTEM ACQUIRE状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHsdFsmSysAcq.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasHsdComFunc.h"
#include "CnasHsdSndInternalMsg.h"
#include "hsd_mscc_pif.h"
#include "cas_hrpd_overheadmsg_nas_pif.h"
#include "hsm_hsd_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SYS_ACQ_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS HSD状态机数组:SYSTEM ACQUIRE子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasHsdSysAcqFsmDesc;

/* CNAS_HSD_SYS_ACQ_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasHsdSysAcqInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_HSD_RcvMsccSysAcqReq_SysAcq_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_HSD_RcvHsdSysAcqReq_SysAcq_Init),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitCasSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasSysSyncCnf),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitCasStopSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_STOP_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasStopSysSyncCnf),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND动作表 */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOverheadInd_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_OHM_IND,
                      CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasIndProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasInd),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SESSION_IND动作表 */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitSessionNegRsltIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_SESSION_NEG_RESULT_IND,
                      CNAS_HSD_RcvSessionNegRsltInd_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND,
                      CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionIndProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_CONN_OPEN_IND,
                      CNAS_HSD_RcvHsmConnOpenInd_WaitSessionInd),
};

/* System Acquire状态机消息 状态表 */
NAS_STA_STRU g_astCnasHsdSysAcqStaTbl[] =
{
    /*****************定义SYSTEM ACQUIRE初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_INIT,
                      g_astCnasHsdSysAcqInitActTbl),

    /*****************定义等待CAS回复同步确认状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF,
                      g_astCnasHsdSysAcqWaitCasSyncCnfActTbl ),

    /*****************定义等待CAS回复停止捕获确认状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF,
                      g_astCnasHsdSysAcqWaitCasStopSyncCnfActTbl),

    /*****************定义等待CAS上报OHM上报状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND,
                      g_astCnasHsdSysAcqWaitOhmIndActTbl),

    /*****************定义等待HSM上报SESSION态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND,
                      g_astCnasHsdSysAcqWaitSessionNegRsltIndActTbl),
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysAcqStaTblSize
 功能描述  : 获取SYSTEM ACQUIRE状态机的大小
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetSysAcqStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdSysAcqStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysAcqFsmDescAddr
 功能描述  : 获取SYSTEM ACQUIRE状态机的描述表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetSysAcqFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdSysAcqFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



