/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmPreProcTbl.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   Contains definitions of all EHSM pre proc table interfaces.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmPreProcTbl.h"
#include "CnasEhsmPreProcAct.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_esm_pif.h"
#include "ehsm_hsd_pif.h"
#include "ehsm_aps_pif.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
/* To Do: Need to add EHSM depending interfaces */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_PRE_PROC_TBL_C

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

NAS_FSM_DESC_STRU                       g_stCnasEhsmPreProcFsmDesc;

NAS_ACT_STRU g_astCnasEhsmPreProActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_CONTEXT_INFO_NOTIFY,
                      CNAS_EHSM_RcvApsPdnContextInfoNotify_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_CONNECT_IND,
                      CNAS_EHSM_RcvHsmConnectInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_PreProc),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_MODIFY_IND,
                      CNAS_EHSM_RcvPppModifyInd_PreProc),

    NAS_ACT_TBL_ITEM( PS_PID_ESM,
                      ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY,
                      CNAS_EHSM_RcvEsmClearAllBearer_PreProc),
};

NAS_STA_STRU g_astCnasEhsmPreProcStaTbl[] =
{
    NAS_STA_TBL_ITEM( CNAS_EHSM_L1_STA_PREPROC,
                      g_astCnasEhsmPreProActTbl)
};


/*****************************************************************************
  3 Function Define
*****************************************************************************/



/* To Do: Need to write deifinitions of all PreProc message handlers */

VOS_UINT32 CNAS_EHSM_GetPreProcStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasEhsmPreProcStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU* CNAS_EHSM_GetPreProcDescAddr(VOS_VOID)
{
    return (&g_stCnasEhsmPreProcFsmDesc);
}

#endif /* FEATURE_UE_MODE_CDMA */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

