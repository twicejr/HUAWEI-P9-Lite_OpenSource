


/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmFsmUatiRequest.h"
#include "CnasHsmFsmSessionDeact.h"
#include "CnasHsmFsmSessionAct.h"
#include "CnasHsmFsmMain.h"
#include "hsm_hsd_pif.h"
#include "CnasHsmSndInternalMsg.h"
#include "cttf_hrpd_rmac_data_status_pif.h"
#include "nas_cttf_hrpd_rsnp_pif.h"
#include "CnasHsmTimer.h"
#include "ehsm_hsm_pif.h"
#include "cas_hrpd_routeupdate_nas_pif.h"
#include "UsimPsInterface.h"
#include "hsm_aps_pif.h"
#include "CnasHsmSndRrm.h"
#include "CnasHsmFsmSwitchOn.h"
#include "CnasHsmKeepAlive.h"
#include "CnasHsmFsmConnMnmt.h"
#include "cas_hrpd_idlestate_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stCnasHsmFsmDesc;

/* the event process table in NULL state and substate is not exist */
NAS_ACT_STRU g_astCnasHsmNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_START_REQ,
                      CNAS_HSM_RcvHsdStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SWITCH_ON_RESULT_IND,
                      CNAS_HSM_RcvHsmSwitchOnResultInd_Null),
};

/* switch on init subprocedure */
NAS_ACT_STRU g_astCnasHsmNullSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SWITCH_ON_REQ,
                      CNAS_HSM_RcvInterSwitchOnReq_Init),
};

/* switch on subprocedure */
NAS_ACT_STRU g_astCnasHsmNullSwitchOnWaitReadCardCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_HSM_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_CARD_READ_CNF,
                      CNAS_HSM_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SwitchOn_WaitCardFileCnf),
};


/* the event process table in inactive state and substate is not exist */
NAS_ACT_STRU g_astCnasHsmInactiveActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SYSTEM_ACQUIRED_IND,
                      CNAS_HSM_RcvHsdSystemAcqInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSM_RcvRrmStatusInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF,
                      CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_IRAT_FROM_LTE_IND,
                      CNAS_HSM_RcvHsdIratFromLteNtf_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionActiveResultInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvHsmHrpdPaRatModeNtf_Inactive),

};

/* the event process table in setup state and substate is not exist */
NAS_ACT_STRU g_astCnasHsmSetupActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_Setup),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND,
                      CNAS_HSM_RcvUatiRequestResultInd_Setup),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionDeactiveResultInd_Setup),
};

/* the event process table in open state and substate is not exist */
NAS_ACT_STRU g_astCnasHsmOpenActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SYSTEM_ACQUIRED_IND,
                      CNAS_HSM_RcvHsdSystemAcqInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_Open),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionActiveResultInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionDeactiveResultInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND,
                      CNAS_HSM_RcvUatiRequestResultInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF,
                      CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Open),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_ORIG_REQ,
                      CNAS_HSM_RcvApsOrigReq_Open),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_CONN_EST_REQ,
                      CNAS_HSM_RcvEhsmConnEstReq_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_CONN_MNMT_RESULT_IND,
                      CNAS_HSM_RcvHsmConnMnmtResultInd_Open),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_Open),
};

NAS_ACT_STRU g_astCnasHsmSlaveActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SYSTEM_ACQUIRED_IND,
                      CNAS_HSM_RcvHsdSystemAcqInd_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_RESUME_IND,
                      CNAS_HSM_RcvHsdResumeInd_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_IRAT_FROM_LTE_IND,
                      CNAS_HSM_RcvHsdIratFromLteNtf_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionActiveResultInd_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND,
                      CNAS_HSM_RcvHsmSessionDeactiveResultInd_Slave),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_Slave),
};

/************************substate machine process table*********************************/

/* session active subprocedure */
/* the event process table in inactive or open state and substate is session active init state */
NAS_ACT_STRU g_astCnasHsmSessionActInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_ACTIVE_REQ,
                      CNAS_HSM_RcvInterSessionActiveReq_SessionAct_Init),
};


/* the event process table in session active wait scp active cnf state */
NAS_ACT_STRU g_astCnasHsmSessionActWaitScpActiveCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF,
                      CNAS_HSM_RcvTiWaitScpActiveCnfTimerExpire_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_SCP_ACTIVE_CNF,
                      CNAS_HSM_RcvCasScpActiveCnf_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF,
                      CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitScpActiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitScpActiveCnf),
};

NAS_ACT_STRU g_astCnasHsmSessionActWaitPaRatModeNtfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvTiWaitPaRatModeNtfTimerExpire_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF,
                      CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitPaRatModeNtf),


    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitPaRatModeNtf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_WaitPaRatModeNtf),

};

/* session deactive subprocedure */

/* the event process table in session deactive init state */
NAS_ACT_STRU g_astCnasHsmSessionDeactInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_DEACTIVE_REQ,
                      CNAS_HSM_RcvInterSessionDeactReq_SessionDeact_Init)
};

/* the event process table in session deactive wait snp data cnf indication state */
NAS_ACT_STRU g_astCnasHsmSessionDeactWaitSessionCloseSnpDataCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_RESUME_IND,
                      CNAS_HSM_RcvHsdResumeInd_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLostIndProc_SessionDeact_WaitSessionCloseSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitSessionCloseSnpDataCnf),
};


/* the event process table in session deactive wait connection close state */
NAS_ACT_STRU g_astCnasHsmSessionDeactWaitConnCloseIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                      CNAS_HSM_RcvTiWaitHrpdConnCloseIndTimerExpire_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CONN_CLOSE_IND,
                      CNAS_HSM_RcvCasConnCloseInd_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_SessionDeact_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitConnCloseInd),
};

/* the event process table in session deactive wait scp deactive cnf state */
NAS_ACT_STRU g_astCnasHsmSessionDeactWaitScpDeactiveCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_SCP_DEACTIVE_CNF,
                      CNAS_HSM_RcvTiWaitScpDeactiveCnfTimerExpire_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_SCP_DEACTIVE_CNF,
                      CNAS_HSM_RcvCasScpDeactiveCnf_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SYSTEM_ACQUIRED_IND,
                      CNAS_HSM_RcvHsdSystemAcquiredInd_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_RESUME_IND,
                      CNAS_HSM_RcvHsdResumeInd_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_IRAT_FROM_LTE_IND,
                      CNAS_HSM_RcvHsdIratFromLteInd_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF,
                      CNAS_HSM_RcvHsdPilotSrchFailNtf_SessionDeact_WaitScpDeactiveCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitScpDeactiveCnf),

};

/* uati reqeust subprocedure */

/* the event process table in UATI request init state */
NAS_ACT_STRU g_astCnasHsmUATIRequestInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_UATI_REQ,
                      CNAS_HSM_RcvInterUatiReq_UATIRequest_Init),
};


/* the event process table in Uati request wait tx ended */
NAS_ACT_STRU g_astCnasHsmSetupUatiRequestWaitSnpDataCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                       TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF,
                       CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiReqSnpDataCnf),
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfHrpdSnpDataInd_UatiReq_WaitUatiReqSnpDataCnf),

};

/* the event process table in uati request wait uati assignment state */
NAS_ACT_STRU g_astCnasHsmSetupUatiWaitUATIAssignActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_UATI_ASSIGN,
                      CNAS_HSM_RcvTiWaitUATIAssignTimerExpire_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiAssign),
};

#if 0
NAS_ACT_STRU g_astCnasHsmSetupUatiCmplWaitSnpDataCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiCmplSnpDataCnf),

};
#endif

/* the event process table in Uati request wait snp data cnf */
NAS_ACT_STRU g_astCnasHsmOpenUatiRequestWaitSnpDataCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiReqSnpDataCnf),

     NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfHrpdSnpDataInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_WaitUatiReqSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_WaitUatiReqSnpDataCnf),


};

/* the event process table in uati request wait uati assignment state */
NAS_ACT_STRU g_astCnasHsmOpenUatiWaitUATIAssignActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_UATI_ASSIGN,
                      CNAS_HSM_RcvTiWaitUATIAssignTimerExpire_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiAssign),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiAssign),
};

#if 0
NAS_ACT_STRU g_astCnasHsmOpenUatiCmplWaitSnpDataCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiCmplSnpDataCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiCmplSnpDataCnf),
};
#endif

NAS_ACT_STRU g_astCnasHsmOpenConnMnmtInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_CONN_MNMT_REQ,
                      CNAS_HSM_RcvInterConnMnmtReq_ConnMnmt_Init),

};

NAS_ACT_STRU g_astCnasHsmOpenConnMnmtWaitConnOpenIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CONN_OPEN_IND,
                      CNAS_HSM_RcvCasConnOpenInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND,
                      CNAS_HSM_RcvTiWaitConnOpenIndTimerExp_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOverHeadMsgInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_ORIG_REQ,
                      CNAS_HSM_RcvApsOrigReq_ConnMnmt_WaitConnOpenInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_CONN_EST_REQ,
                      CNAS_HSM_RcvEhsmConnEstReq_ConnMnmt_WaitConnOpenInd),
};

NAS_ACT_STRU g_astCnasHsmOpenConnMnmtWaitConnCloseIndActTbl[] =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CONN_CLOSE_IND,
                      CNAS_HSM_RcvCasConnCloseInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND,
                      CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF,
                      CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                      CNAS_HSM_RcvTiWaitConnCloseIndTimerExp_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfSnpDataInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                      CNAS_HSM_RcvHsmSessionCloseInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_ORIG_REQ,
                      CNAS_HSM_RcvApsOrigReq_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_CONN_EST_REQ,
                      CNAS_HSM_RcvEhsmConnEstReq_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOverHeadMsgInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_PAGE_IND,
                      CNAS_HSM_RcvCasHrpdPageInd_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_ConnMnmt_WaitConnCloseInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_ConnMnmt_WaitConnCloseInd),

};



/* The Process Table of The State  Machine */
NAS_STA_STRU g_astCnasHsmFsmStaTbl[] =
{
    /* Main State is Inactive and Substate is vacant */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_NULL,
                           CNAS_HSM_SS_VACANT,
                           g_astCnasHsmNullActTbl ),

    /***************************************************************************/
    /**********************Switch on read card Procedure ********************/
    /***************************************************************************/
    /* Main State is NULL and Substate is wait init */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_NULL,
                           CNAS_HSM_SS_SWITCH_ON_INIT,
                           g_astCnasHsmNullSwitchOnInitActTbl),

    /* Main State is NULL and Substate is wait read card cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_NULL,
                           CNAS_HSM_SS_SWITCH_ON_WAIT_CARD_READ_CNF,
                           g_astCnasHsmNullSwitchOnWaitReadCardCnfActTbl),

    /* Main State is Inactive and Substate is vacant */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_INACTIVE,
                           CNAS_HSM_SS_VACANT,
                           g_astCnasHsmInactiveActTbl ),

    /***************************************************************************/
    /**********************Session Recovery Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_INACTIVE,
                           CNAS_HSM_SS_SESSION_ACT_INIT,
                           g_astCnasHsmSessionActInitActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_INACTIVE,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF,
                           g_astCnasHsmSessionActWaitScpActiveCnfActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_INACTIVE,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF,
                           g_astCnasHsmSessionActWaitPaRatModeNtfActTbl ),

    /***************************************************************************/
    /**********************Session Active Procedure ****************************/
    /***************************************************************************/

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_ACT_INIT,
                           g_astCnasHsmSessionActInitActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF,
                           g_astCnasHsmSessionActWaitScpActiveCnfActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF,
                           g_astCnasHsmSessionActWaitPaRatModeNtfActTbl ),

    /* Main State is Setup and Substate is vacant */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_VACANT,
                           g_astCnasHsmSetupActTbl ),

    /***************************************************************************/
    /**********************Session Deactive Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_SESSION_DEACT_INIT,
                           g_astCnasHsmSessionDeactInitActTbl ),

    /* Main State is setup and Substate is wait snp data cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF,
                           g_astCnasHsmSessionDeactWaitSessionCloseSnpDataCnfActTbl),

    /* Main State is setup and Substate is wait connection close */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND,
                           g_astCnasHsmSessionDeactWaitConnCloseIndActTbl ),

    /* Main State is setup and Substate is wait scp deactive cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF,
                           g_astCnasHsmSessionDeactWaitScpDeactiveCnfActTbl ),

    /***************************************************************************/
    /**********************UATI Request Procedure ****************************/
    /***************************************************************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_UATI_REQUEST_INIT,
                           g_astCnasHsmUATIRequestInitActTbl),

    /* Main State is setup and Substate is wait snp data cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF,
                           g_astCnasHsmSetupUatiRequestWaitSnpDataCnfActTbl ),


    /* Main State is setup and Substate is wait uati assignment */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_ASSIGN,
                           g_astCnasHsmSetupUatiWaitUATIAssignActTbl ),
#if 0
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SETUP,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_COMPLETE_SNP_DATA_CNF,
                           g_astCnasHsmSetupUatiCmplWaitSnpDataCnfActTbl ),
#endif

    /* Main State is Open and Substate is vacant */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_VACANT,
                           g_astCnasHsmOpenActTbl ),

    /***************************************************************************/
    /**********************Session Deactive Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_DEACT_INIT,
                           g_astCnasHsmSessionDeactInitActTbl ),

    /* Main State is open and Substate is wait snp data cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF,
                           g_astCnasHsmSessionDeactWaitSessionCloseSnpDataCnfActTbl),

    /* Main State is open and Substate is wait connection close */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND,
                           g_astCnasHsmSessionDeactWaitConnCloseIndActTbl),

    /* Main State is open and Substate is wait scp deactive cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF,
                           g_astCnasHsmSessionDeactWaitScpDeactiveCnfActTbl ),

    /***************************************************************************/
    /**********************UATI Request Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_UATI_REQUEST_INIT,
                           g_astCnasHsmUATIRequestInitActTbl),

    /* Main State is open and Substate is wait snp data cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF,
                           g_astCnasHsmOpenUatiRequestWaitSnpDataCnfActTbl),

    /* Main State is open and Substate is wait uati assignment */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_ASSIGN,
                           g_astCnasHsmOpenUatiWaitUATIAssignActTbl),

#if 0
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_COMPLETE_SNP_DATA_CNF,
                           g_astCnasHsmOpenUatiCmplWaitSnpDataCnfActTbl ),
#endif


    /***************************************************************************/
    /**********************Connection management Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_CONN_MNMT_INIT,
                           g_astCnasHsmOpenConnMnmtInitActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND,
                           g_astCnasHsmOpenConnMnmtWaitConnOpenIndActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_OPEN,
                           CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND,
                           g_astCnasHsmOpenConnMnmtWaitConnCloseIndActTbl ),



    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_VACANT,
                           g_astCnasHsmSlaveActTbl),

    /***************************************************************************/
    /**********************Session Recovery Procedure ****************************/
    /***************************************************************************/
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_ACT_INIT,
                           g_astCnasHsmSessionActInitActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF,
                           g_astCnasHsmSessionActWaitScpActiveCnfActTbl ),

    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF,
                           g_astCnasHsmSessionActWaitPaRatModeNtfActTbl ),

    /***************************************************************************/
    /**********************Session Deactive Procedure ****************************/
    /***************************************************************************/
    /* Main State is slave and Substate is deact init */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_DEACT_INIT,
                           g_astCnasHsmSessionDeactInitActTbl ),

    /* Main State is open and Substate is wait connection close */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND,
                           g_astCnasHsmSessionDeactWaitConnCloseIndActTbl),

    /* Main State is slave and Substate is wait scp deactive cnf */
    NAS_MUTI_STA_TBL_ITEM( CNAS_HSM_L1_STA_SLAVE,
                           CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF,
                           g_astCnasHsmSessionDeactWaitScpDeactiveCnfActTbl ),
};

/*****************************************************************************
  3 The Function Define
*****************************************************************************/


VOS_UINT32 CNAS_HSM_GetFsmStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsmFsmStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU* CNAS_HSM_GetFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsmFsmDesc);
}



VOS_VOID  CNAS_HSM_RegisterFsm(VOS_VOID)
{

    NAS_FSM_RegisterFsm((CNAS_HSM_GetFsmDescAddr()),
                         "CNAS:FSM:HSM",
                         CNAS_HSM_GetFsmStaTblSize(),
                         CNAS_HSM_GetFsmStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




