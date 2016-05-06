/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmFsmActivatingTbl.c
 Author          :
 Version         :
 Date            :   18/05/2015
 Description     :   This file has EHSM ACTIVATING FSM table.
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
#include "CnasEhsmFsmActivating.h"
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmSndInternalMsg.h"
#include "ehsm_hsd_pif.h"

/* To Do: Need to add EHSM to ESM interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_ACTIVATING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

NAS_FSM_DESC_STRU                       g_stCnasEhsmActivatingFsmDesc;


/* CNAS_EHSM_ACTIVATING_STA_INIT Action table */
NAS_ACT_STRU        g_astCnasEhsmActivatingInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ATTACH_REQ,
                      CNAS_EHSM_RcvEhsmAttachReq_Activating_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ,
                      CNAS_EHSM_RcvEhsmPdnSetupReq_Activating_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_RECONN_REQ,
                      CNAS_EHSM_RcvApsReConnReq_Activating_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_ACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnActivateReq_Activating_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_ATTACH_REQ,
                      CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init),
};

/* CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF Action table */
NAS_ACT_STRU        g_astCnasEhsmActivatingWaitHsmConnCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_CONN_EST_CNF,
                      CNAS_EHSM_RcvHsmConnEstCnf_Activating_WaitHsmConnCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF,
                      CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Activating_WaitHsmConnCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvAbortReq_Activating_WaitHsmConnCnf),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_ATTACH_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf),
};

/* CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT Action table */
NAS_ACT_STRU        g_astCnasEhsmActivatingWaitConnEstRetryActTbl[]   =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CONN_RETRY_EST,
                      CNAS_EHSM_RcvTiWaitConnRetryEst_Activating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_ATTACH_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SESSION_INFO_IND,
                      CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry),
};

/* CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF Action table */
NAS_ACT_STRU        g_astCnasEhsmActivatingWaitCttfPdnSetupCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitCttfPdnSetupCnf),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_ATTACH_CNF,
                      CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitCttfPdnSetupCnf),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_RECONN_IND,
                      CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_Activating_WaitCttfPdnSetupCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF,
                      CNAS_EHSM_RcvTiWaitCttfPdnSetupCnf_Activating_WaitCttfPdnSetupCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitCttfPdnSetupCnf)

};

/* CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY Action table */
NAS_ACT_STRU        g_astCnasEhsmActivatingWaitPdnRetryActTbl[]   =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP,
                      CNAS_EHSM_RcvTiWaitRetryPdnSetup_Activating_WaitPdnRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ABORT_REQ,
                      CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitPdnRetry),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_Activating_WaitPdnRetry)

};

/* CNAS EHSM ACTIVATING fsm state table */
NAS_STA_STRU        g_astCnasEhsmActivatingStaTbl[]   =
{
    NAS_STA_TBL_ITEM( CNAS_EHSM_ACTIVATING_STA_INIT,
                      g_astCnasEhsmActivatingInitActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF,
                      g_astCnasEhsmActivatingWaitHsmConnCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT,
                      g_astCnasEhsmActivatingWaitConnEstRetryActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF,
                      g_astCnasEhsmActivatingWaitCttfPdnSetupCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY,
                      g_astCnasEhsmActivatingWaitPdnRetryActTbl )
};

/*****************************************************************************
  3 Function Define
*****************************************************************************/


VOS_UINT32 CNAS_EHSM_GetActivatingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasEhsmActivatingStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * CNAS_EHSM_GetActivatingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasEhsmActivatingFsmDesc);
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




