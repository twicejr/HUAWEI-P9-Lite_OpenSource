
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmDeactivating.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : Inactivating状态机处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Aps.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "AtMnInterface.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSDEACTIVATING_TBL_C

/******************************************************************************
   2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:MS ACTIVATING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsMsDeactivatingFsmDesc;

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                    ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                    TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init),

};

 /* TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND*/
 TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaSuspendActTbl[]   =
 {

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_Suspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_RELEASE_IND,
                     TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend),
#endif
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnf),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChangeInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_RELEASE_IND,
                     TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnfSuspend),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_DEACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRsp),

};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_DEACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRspSuspend),

};

#if (FEATURE_ON == FEATURE_LTE)
/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitEsmDeactivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_RELEASE_CNF,
                     TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnf),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitEsmDeactivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_RELEASE_CNF,
                     TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_RELEASE_IND,
                     TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND,
                     TAF_APS_RcvEhsmLteHandoverToEhrpdInd_MsDeactivating_WaitEsmDeactivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnfSuspend),

};
#endif


TAF_STA_STRU g_astTafApsMsDeactivatingStaTbl[] =
{
    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_INIT,
                      g_astTafApsMsDeactivatingSubStaInitActTbl ),

    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfActTbl ),

    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaSuspendActTbl ),

    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfSuspendActTbl ),

    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspActTbl ),

    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspSuspendActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /*****************定义TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitEsmDeactivateCnfActTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitEsmDeactivateCnfSuspendActTbl ),
#endif

};


/******************************************************************************
   3 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_GetMsDeactivatingStaTblSize
 功能描述  : 获取MS ACTIVATING状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:Lay1状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_GetMsDeactivatingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMsDeactivatingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetMsDeactivatingFsmDescAddr
 功能描述  : 获取MS ACTIVATING状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_APS_GetMsDeactivatingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMsDeactivatingFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif












