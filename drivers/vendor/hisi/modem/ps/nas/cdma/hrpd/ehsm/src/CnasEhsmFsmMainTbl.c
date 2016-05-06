



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "CnasEhsmFsmMain.h"
#include "CnasEhsmFsmMainTbl.h"
#include "ehsm_esm_pif.h"
#include "ehsm_hsm_pif.h"
#include "ehsm_hsd_pif.h"
#include "ehsm_aps_pif.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "CnasEhsmSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS EHSM 状态机数 */
NAS_FSM_DESC_STRU                       g_stCnasEhsmMainFsmDesc;

/* CNAS_EHSM_L1_STA_INACTIVE act table */
NAS_ACT_STRU g_astCnasEhsmMainInactiveActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_EHSM_START_REQ,
                      CNAS_EHSM_RcvHsdStartReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SESSION_INFO_IND,
                      CNAS_EHSM_RcvHsmSessionInfoInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ATTACH_REQ,
                      CNAS_EHSM_RcvEhsmAttachReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_EHSM_POWER_OFF_REQ,
                      CNAS_EHSM_RcvHsdPowerOffReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF,
                      CNAS_EHSM_RcvEhsmActivatingRsltCnf_Inactive),

    NAS_ACT_TBL_ITEM( PS_PID_ESM,
                      ID_ESM_EHSM_SYNC_PDN_INFO_IND,
                      CNAS_EHSM_RcvEsmSyncPdnInfoInd_Inactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PS_RAT_TYPE_NOTIFY,
                      CNAS_EHSM_RcvApsPsRatTypeNotify_Inactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_RECONN_REQ,
                      CNAS_EHSM_RcvApsReconnReq_Inactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_DEACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnDeactivateReq_Inactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_ATTACH_REQ,
                      CNAS_EHSM_RcvApsPdnAttachReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ,
                      CNAS_EHSM_RcvEhsmLocalDetachAllReq_Inactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY,
                      CNAS_EHSM_RcvApsLocalDeactiveNtf_Inactive),
};


/* CNAS_EHSM_L1_STA_ACTIVE act table */
NAS_ACT_STRU g_astCnasEhsmMainActiveActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_ACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnActivateReq_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_DISC_IND,
                      CNAS_EHSM_RcvHsmDiscInd_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_DEACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnDeactivateReq_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_LOC_DETACH_NOTIFY,
                      CNAS_EHSM_RcvApsLocDetachNotify_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_EHSM_POWER_OFF_REQ,
                      CNAS_EHSM_RcvHsdPowerOffReq_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF,
                      CNAS_EHSM_RcvEhsmActivatingRsltCnf_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF,
                      CNAS_EHSM_RcvEhsmDeactivatingRsltCnf_Active),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_PDN_DISC_IND,
                      CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Active),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_DETACH_IND,
                      CNAS_EHSM_RcvCttfEhrpdDetachInd_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ,
                      CNAS_EHSM_RcvEhsmPdnSetupReq_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_RECONN_REQ,
                      CNAS_EHSM_RcvApsReConnReq_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PS_RAT_TYPE_NOTIFY,
                      CNAS_EHSM_RcvApsPsRatTypeNty_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SUSPEND_IND,
                      CNAS_EHSM_RcvHsmSuspendInd_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY,
                      CNAS_EHSM_RcvApsLocDeactivateNty_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ,
                      CNAS_EHSM_RcvEhsmLocalDetachAllReq_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_DISC_NOTIFY,
                      CNAS_EHSM_RcvApsDiscNotify_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SESSION_INFO_IND,
                      CNAS_EHSM_RcvHsmSessionInfoInd_Active),

    NAS_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_CTTF_CNAS_EHRPD_MODIFY_IND,
                      CNAS_EHSM_RcvPppModifyInd_Active),
};


/* CNAS_EHSM_L1_STA_SUSPEND act table */
NAS_ACT_STRU g_astCnasEhsmMainSuspendActTbl[] =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_RECONN_REQ,
                      CNAS_EHSM_RcvApsReConnReq_Suspend),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_DEACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnDeactivateReq_Suspend),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_EHSM_POWER_OFF_REQ,
                      CNAS_EHSM_RcvHsdPowerOffReq_Suspend),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PDN_ACTIVATE_REQ,
                      CNAS_EHSM_RcvApsPdnActivateReq_Suspend),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_EHSM_SESSION_INFO_IND,
                      CNAS_EHSM_RcvHsmSessionInfoInd_Suspend),

    NAS_ACT_TBL_ITEM( PS_PID_ESM,
                      ID_ESM_EHSM_SYNC_PDN_INFO_IND,
                      CNAS_EHSM_RcvEsmSyncPdnInfoInd_Suspend),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_LOC_DETACH_NOTIFY,
                      CNAS_EHSM_RcvApsLocDetachNotify_Suspend),

    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_PS_RAT_TYPE_NOTIFY,
                      CNAS_EHSM_RcvApsPsRatTypeNty_Suspend),


    NAS_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY,
                      CNAS_EHSM_RcvApsLocDeactivateNty_Suspend),
};


/* L1Main  state table */
NAS_STA_STRU g_astCnasEhsmMainStaTbl[] =
{
    /* Inactive State */
    NAS_STA_TBL_ITEM(CNAS_EHSM_L1_STA_INACTIVE,
                      g_astCnasEhsmMainInactiveActTbl),

    /* Active State */
    NAS_STA_TBL_ITEM(CNAS_EHSM_L1_STA_ACTIVE,
                      g_astCnasEhsmMainActiveActTbl),

    /* Suspend State */
    NAS_STA_TBL_ITEM(CNAS_EHSM_L1_STA_SUSPEND,
                     g_astCnasEhsmMainSuspendActTbl)
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/



VOS_UINT32 CNAS_EHSM_GetMainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasEhsmMainStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *CNAS_EHSM_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasEhsmMainFsmDesc);
}
/*lint -restore*/

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


