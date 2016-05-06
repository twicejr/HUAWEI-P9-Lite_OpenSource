
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsActivatingTbl.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : MsActivating状态机处理表
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
#include "TafApsFsmMsActivating.h"
#include "TafApsFsmMsActivatingTbl.h"

#include "AtMnInterface.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "ApsL4aInterface.h"
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSACTIVATING_TBL_C

/******************************************************************************
   2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:MS ACTIVATING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsMsActivatingFsmDesc;

/* TAF_APS_MS_ACTIVATING_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init),
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaSuspendTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_Suspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND,
                     TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_Suspend),
#endif
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitSmActivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_REJ,
                     TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_REJ,
                     TAF_APS_RcvSmPdpActSecRej_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_CNF,
                     TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_CNF,
                     TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnf),
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitSmActivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_REJ,
                     TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND,
                     TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitSmActivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_CNF,
                     TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnfSuspend),
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnfSuspend),
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitSndcpActivateRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_ACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRsp),
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitSndcpActivateRspSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_ACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRspSuspend),
};

#if (FEATURE_ON == FEATURE_LTE)
/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitEsmActivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_SETUP_CNF,
                     TAF_APS_RcvEsmPdpSetupCnf_MsActivate_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_NDISCONN_CNF,
                     TAF_APS_RcvEsmNdisconnCnf_MsActivate_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnf),


    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitEsmActivateCnf),
};

/* TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsActivatingSubStaWaitEsmActivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_SETUP_CNF,
                     TAF_APS_RcvEsmPdpSetupCnfRej_MsActivate_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_NDISCONN_CNF,
                     TAF_APS_RcvEsmNdisconnCnfRej_MsActivate_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnfSuspend),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND,
                     TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitEsmActivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_ACTIVATING,
                     TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnfSuspend),
};
#endif

TAF_STA_STRU g_astTafApsMsActivatingStaTbl[] =
{
    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_INIT,
                      g_astTafApsMsActivatingSubStaInitTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND,
                      g_astTafApsMsActivatingSubStaSuspendTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF,
                      g_astTafApsMsActivatingSubStaWaitSmActivateCnfActTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsActivatingSubStaWaitSmActivateCnfSuspendActTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP,
                      g_astTafApsMsActivatingSubStaWaitSndcpActivateRspActTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND,
                      g_astTafApsMsActivatingSubStaWaitSndcpActivateRspSuspendActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF,
                      g_astTafApsMsActivatingSubStaWaitEsmActivateCnfActTbl ),

    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsActivatingSubStaWaitEsmActivateCnfSuspendActTbl ),
#endif
};


/******************************************************************************
   3 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_GetMsActivatingStaTblSize
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
VOS_UINT32 TAF_APS_GetMsActivatingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMsActivatingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetMsActivatingFsmDescAddr
 功能描述  : 获取MS ACTIVATING状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_APS_GetMsActivatingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMsActivatingFsmDesc);
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


