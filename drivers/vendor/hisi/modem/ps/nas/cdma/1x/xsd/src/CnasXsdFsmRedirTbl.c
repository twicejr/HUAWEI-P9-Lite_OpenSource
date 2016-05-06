



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXsdFsmRedir.h"
#include "CnasXsdFsmRedirTbl.h"
#include "CnasXsdComFunc.h"
#include "CnasXsdSndInternalMsg.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "cas_1x_control_main_nas_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_REDIR_TBL_C
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XSD状态机数组:REDIRECTION 子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXsdRedirFsmDesc;

/* CNAS_XSD_REDIR_STA_INIT act table */
NAS_ACT_STRU g_astCnasXsdRedirInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_REDIRECTION_IND,
                      CNAS_XSD_RcvXsdRedirInd_Redir_Init)
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnf),
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasStopSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasStopSysSyncCnfTimerExpired_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnf),
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasSyncCnfRetOrigSysActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnfOrigSys),
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasStopSyncCnfRetOrigSysActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnfOrigSys),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnfOrigSys),
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_OHM_IND,
                      CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmInd),
};

/* CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND act table */
NAS_ACT_STRU g_astCnasXsdRedirWaitCasOhmRetOrigSysIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_OHM_IND,
                      CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmIndRetOrigSysInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmIndRetOrigSysInd),
};

/* Redirection state table */
NAS_STA_STRU g_astCnasXsdRedirStaTbl[] =
{
    /***************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_INIT,
                      g_astCnasXsdRedirInitActTbl),

    /**************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF,
                      g_astCnasXsdRedirWaitCasSyncCnfActTbl ),

    /*************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF,
                      g_astCnasXsdRedirWaitCasStopSyncCnfActTbl),

    /**************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS,
                      g_astCnasXsdRedirWaitCasSyncCnfRetOrigSysActTbl),

    /*************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS,
                      g_astCnasXsdRedirWaitCasStopSyncCnfRetOrigSysActTbl),

    /************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND,
                      g_astCnasXsdRedirWaitCasOhmIndActTbl),

    /************************************/
    NAS_STA_TBL_ITEM( CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND,
                      g_astCnasXsdRedirWaitCasOhmRetOrigSysIndActTbl)
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/



VOS_UINT32 CNAS_XSD_GetRedirStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdRedirStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *CNAS_XSD_GetRedirFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdRedirFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



