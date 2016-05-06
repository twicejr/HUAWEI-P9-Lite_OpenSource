/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSysAcqTbl.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月28日
  功能描述   : 1X SD L2 SYSTEM ACQUIRE状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月28日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXsdFsmSysAcq.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasXsdComFunc.h"
#include "CnasXsdSndInternalMsg.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "cas_1x_control_main_nas_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SYS_ACQ_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XSD状态机数组:SYSTEM ACQUIRE子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXsdSysAcqFsmDesc;

/* CNAS_XSD_SYS_ACQ_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasXsdSysAcqInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init),
};

/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf),
};


/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND动作表 */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_OHM_IND,
                      CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd),
};

/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasStopSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf),
};


/* System Acquire状态机消息 状态表 */
NAS_STA_STRU g_astCnasXsdSysAcqStaTbl[] =
{
    /*****************定义SYSTEM ACQUIRE初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_INIT,
                      g_astCnasXsdSysAcqInitActTbl),

    /*****************定义等待CAS回复同步确认状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF,
                      g_astCnasXsdSysAcqWaitCasSyncCnfActTbl ),

    /*****************定义等待CAS上报OHM指示状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND,
                      g_astCnasXsdSysAcqWaitCasOhmIndActTbl),

    /*****************定义等待CAS回复停止同步确认状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF,
                      g_astCnasXsdSysAcqWaitCasStopSyncCnfActTbl),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSysAcqStaTblSize
 功能描述  : 获取SYSTEM ACQUIRE状态机的大小
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSysAcqStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdSysAcqStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSysAcqFsmDescAddr
 功能描述  : 获取SYSTEM ACQUIRE状态机的描述表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XSD_GetSysAcqFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdSysAcqFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



