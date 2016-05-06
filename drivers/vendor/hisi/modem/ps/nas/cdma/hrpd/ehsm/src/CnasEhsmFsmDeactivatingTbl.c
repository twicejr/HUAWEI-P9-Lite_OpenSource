/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmFsmDectivatingTbl.c
 Author          :
 Version         :
 Date            :   18/05/2015
 Description     :   This file has EHSM DEACTIVATING FSM table.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_hsd_pif.h"
#include "ehsm_aps_pif.h"
#include "ehsm_hsm_pif.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "CnasEhsmFsmDeactivatingTbl.h"
#include "CnasEhsmFsmDeactivating.h"


/* To Do: Need to add EHSM to ESM interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_DEACTIVATING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

NAS_FSM_DESC_STRU                       g_stCnasEhsmDeactivatingFsmDesc;

/* CNAS_EHSM_DEACTIVATING_STA_INIT Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_EHSM_POWER_OFF_REQ,
                      CNAS_EHSM_RcvHsdPowerOffReq_Deactivating_Init ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_DEACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnDeactivate_Deactivating_Init ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_DISC_NOTIFY,
                      CNAS_EHSM_RcvApsDiscNotify_Deactivating_Init ),
};


/* CNAS_EHSM_DEACTIVATING_STA_WAIT_PDN_DISC_CNF Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingWaitPdnDiscCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitPdnDiscCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_IND,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitPdnDiscCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_RECONN_IND,
                      CNAS_EHSM_RcvCttfEhrpdReconnInd_Deactivating_WaitPdnDiscCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_Deactivating_WaitPdnDiscCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitPdnDiscCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnDiscCnf_Deactivating_WaitPdnDiscCnf )
};

/* CNAS_EHSM_DEACTIVATING_STA_WAIT_DETACH_CNF Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingWaitDetachCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_DETACH_CNF,
                      CNAS_EHSM_RcvCttfEhrpdDetachCnf_Deactivating_WaitDetachCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_RECONN_IND,
                      CNAS_EHSM_RcvCttfEhrpdReconnInd_Deactivating_WaitDetachCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_Deactivating_WaitDetachCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_DETACH_CNF,
                      CNAS_EHSM_RcvTiCttfEhrpdDetachCnf_Deactivating_WaitDetachCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS,
                      CNAS_EHSM_RcvTiProtectingPowerOff_Deactivating_WaitDetachCnf )
};

/* CNAS_EHSM_DEACTIVATING_STA_WAIT_HSM_CONN_EST_CNF Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingWaitHsmConnEstCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_CONN_EST_CNF,
                      CNAS_EHSM_RcvHsmConnEstCnf_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF,
                      CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS,
                      CNAS_EHSM_RcvTiProtectingPowerOff_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_IND,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_DETACH_CNF,
                      CNAS_EHSM_RcvCttfEhrpdDetachCnf_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnDiscCnfExpired_Deactivating_WaitHsmConnEstCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_DETACH_CNF,
                      CNAS_EHSM_RcvTiCttfEhrpdDetachCnf_Deactivating_WaitHsmConnEstCnf ),
};

/* CNAS_EHSM_DEACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingWaitConnEstRetryActTbl[]   =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CONN_RETRY_EST,
                      CNAS_EHSM_RcvTiWaitConnRetryEst_Deativating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SESSION_INFO_IND,
                      CNAS_EHSM_RcvHsmSessionInfoInd_Deativating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitConnEstRetry ),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_IND,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnDiscCnfExpired_Deactivating_WaitConnEstRetry),
};

/* CNAS_EHSM_DEACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT Action table */
NAS_ACT_STRU        g_astCnasEhsmDeactivatingWaitHsmDisCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_CNF,
                      CNAS_EHSM_RcvHsmDiscCnf_Deactivating_WaitHsmDiscCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_HSM_DISC_CNF,
                      CNAS_EHSM_RcvTiWaitHsmDiscCnf_Deactivating_WaitHsmDiscCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitHsmDiscCnf )
};

/* CNAS EHSM DEACTIVATING fsm state table */
NAS_STA_STRU        g_astCnasEhsmDeactivatingStaTbl[]   =
{
    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_INIT,
                      g_astCnasEhsmDeactivatingInitActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_WAIT_PDN_DISC_CNF,
                      g_astCnasEhsmDeactivatingWaitPdnDiscCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_WAIT_DETACH_CNF,
                      g_astCnasEhsmDeactivatingWaitDetachCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_WAIT_HSM_CONN_EST_CNF,
                      g_astCnasEhsmDeactivatingWaitHsmConnEstCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT,
                      g_astCnasEhsmDeactivatingWaitConnEstRetryActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_DEACTIVATING_STA_WAIT_HSM_DISC_CNF,
                      g_astCnasEhsmDeactivatingWaitHsmDisCnfActTbl )

};


/*****************************************************************************
  3 Function Define
*****************************************************************************/



VOS_UINT32 CNAS_EHSM_GetDeactivatingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasEhsmDeactivatingStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * CNAS_EHSM_GetDeactivatingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasEhsmDeactivatingFsmDesc);
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




