


/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmPreProcTbl.h"
#include "CnasHsmPreProcAct.h"
#include "CnasHsmTimer.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
#include "hsm_hlu_pif.h"
#include "hsm_aps_pif.h"
#include "cas_hrpd_idlestate_nas_pif.h"
#include "CnasHsmSndInternalMsg.h"
#include "cas_hrpd_routeupdate_nas_pif.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_PRE_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stCnasHsmPreProcFsmDesc;

NAS_ACT_STRU g_astCnasHsmPreProActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CAS_STATUS_IND,
                      CNAS_HSM_RcvCasHrpdCasStatusInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_SESSION_NEG_START_IND,
                      CNAS_HSM_RcvCasHrpdSessionNegStartInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND,
                      CNAS_HSM_RcvCasHrpdSessionNegRsltInd_PreProc),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_IND,
                      CNAS_HSM_RcvCttfHrpdSnpDataInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_ORIG_REQ,
                      CNAS_HSM_RcvApsOrigReq_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_DISC_REQ,
                      CNAS_HSM_RcvApsDiscReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_CONN_EST_REQ,
                      CNAS_HSM_RcvEhsmConnEstReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_DISC_REQ,
                      CNAS_HSM_RcvEhsmDiscReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SYSTEM_TIME_IND,
                      CNAS_HSM_RcvCasSysTimeInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_CONNECT_RSP,
                      CNAS_HSM_RcvApsConnRsp_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_HSM_1X_TO_HRPD_HANDOFF_REQ,
                      CNAS_HSM_RcvAps1xToHrpdHandOffReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HLU,
                      ID_HLU_HSM_1X_TO_HRPD_HANDOFF_CNF,
                      CNAS_HSM_RcvHlu1xToHrpdHandOffCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HLU,
                      ID_HLU_HSM_LOC_CHANGED_IND,
                      CNAS_HSM_RcvHluLocChngdInd_PreProc),


    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CONN_OPEN_IND,
                      CNAS_HSM_RcvCasHrpdConnOpenInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_CONN_CLOSE_IND,
                      CNAS_HSM_RcvCasHrpdConnCloseInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_CNAS_HRPD_DATA_SERVICE_AVAILBLE_IND,
                      CNAS_HSM_RcvCasDataServiceAvailableInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_CNAS_HRPD_IDLE_HO_IND,
                      CNAS_HSM_RcvCasIdleHoInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_HSM_COMMIT_IND,
                      CNAS_HSM_RcvCasHrpdCommitInd_PreProc),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_SIG,
                      ID_CTTF_CNAS_HRPD_SNP_DATA_CNF,
                      CNAS_HSM_RcvCttfSnpDataCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSM_LTE_REG_SUCCESS_IND,
                      CNAS_HSM_RcvEhsmLteRegSuccessInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_SUSPEND_IND,
                      CNAS_HSM_RcvHsdSuspendInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWER_SAVE_REQ,
                      CNAS_HSM_RcvHsdPowerSaveReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_POWEROFF_REQ,
                      CNAS_HSM_RcvHsdPowerOffReq_PreProc),


    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSM_RcvRrmStatusInd_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_ADDRESS_TIMER,
                      CNAS_HSM_RcvTiAddressTimerExp_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSCP,
                      ID_CAS_CNAS_HRPD_SESSION_CHANGE_IND,
                      CNAS_HSM_RcvCasSessionChangeInd_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_KEEP_ALIVE_TIMER,
                      CNAS_HSM_RcvTiKeepAliveTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiMoKeepAliveWaitSnpDataCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP,
                      CNAS_HSM_RcvTiWaitKeepAliveRspExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiMtKeepAliveWaitSnpDataCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiHardWareIdRspWaitSnpDataCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiSessionCloseRspWaitSnpDataCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF,
                      CNAS_HSM_RcvTiUatiCmplWaitSnpDataCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OHM_NOT_CURRENT_IND,
                      CNAS_HSM_RcvHsdOhmNotCurrentInd_PreProc),


    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_HSM_OVERHEAD_MSG_IND,
                      CNAS_HSM_RcvHsdOhmInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSM_RcvCasHrpdNetworkLostInd_PreProc),

    NAS_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      CNAS_HSM_RcvPihUsimStatusInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_QUERYESNMEIDRSLT_CNF,
                      CNAS_HSM_RcvUsimStoreEsnMeidRsltCnf_PreProc),

    NAS_ACT_TBL_ITEM( CTTF_PID_HRPD_RPA,
                      ID_CTTF_CNAS_HRPD_PA_ACCESS_AUTH_STATUS_IND,
                      CNAS_HSM_RcvCttfHprdPaAccAuthStatusInd_PreProc),

#ifdef DMT
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ,
                      CNAS_HSM_RcvHsmModifySessionSeedReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ,
                      CNAS_HSM_RcvHsmModifyCurSysTickReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_RCV_FWD_TRAF_CHAN_DATA_IND,
                      CNAS_HSM_RcvHsmFwdTrafChanDataInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ,
                      CNAS_HSM_RcvHsmModifyAmpSmpAttrReq_PreProc),

#endif
};

/* 预处理的消息状态表 */
NAS_STA_STRU g_astCnasHsmPreProcStaTbl[] =
{
    NAS_STA_TBL_ITEM( CNAS_HSM_L1_STA_PREPROC,
                      g_astCnasHsmPreProActTbl)
};


/*****************************************************************************
  3 The Function Define
*****************************************************************************/


VOS_UINT32 CNAS_HSM_GetPreProcStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsmPreProcStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU* CNAS_HSM_GetPreProcFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsmPreProcFsmDesc);
}



VOS_VOID  CNAS_HSM_RegisterPreFsm(VOS_VOID)
{

    NAS_FSM_RegisterFsm((CNAS_HSM_GetPreProcFsmDescAddr()),
                         "CNAS:FSM:PREPROC",
                         CNAS_HSM_GetPreProcStaTblSize(),
                         CNAS_HSM_GetPreProcStaTbl(),
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





