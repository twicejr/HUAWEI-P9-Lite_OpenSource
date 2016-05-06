
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsModifyingTbl.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : Modifying状态机处理函数
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
#include "AtMnInterface.h"
#include "MmcApsInterface.h"

#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsFsmMsModifying.h"

#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "ApsL4aInterface.h"
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSMODIFYING_TBL_C

/******************************************************************************
   2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:MS ACTIVATING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsMsModifyingFsmDesc;


/* TAF_APS_MS_MODIFYING_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_IND,
                     TAF_APS_RcvSmPdpModifyInd_MsModifying_Init),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSmModifyCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_CNF,
                     TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_REJ,
                     TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_RABM,
                     RABM_APS_LOCAL_PDP_DEACT_REQ_MSG,
                     TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSmModifyCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_REJ,
                     TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSndcpModifyRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_MDF_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSndcpModifyRspSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_MDF_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend),
};

#if (FEATURE_ON == FEATURE_LTE)

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitEsmModifyCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_MODIFY_CNF,
                     TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitEsmModifyCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_MODIFY_CNF,
                     TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend),
};
#endif


TAF_STA_STRU g_astTafApsMsModifyingStaTbl[] =
{
    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_INIT,
                      g_astTafApsMsModifyingSubStaInitActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_SUPEND状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND,
                      g_astTafApsMsModifyingSubStaSuspendActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF,
                      g_astTafApsMsModifyingSubStaWaitSmModifyCnfActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND,
                      g_astTafApsMsModifyingSubStaWaitSmModifyCnfSuspendActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP,
                      g_astTafApsMsModifyingSubStaWaitSndcpModifyRspActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND,
                      g_astTafApsMsModifyingSubStaWaitSndcpModifyRspSuspendActTbl ),

#if (FEATURE_ON == FEATURE_LTE)

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF,
                      g_astTafApsMsModifyingSubStaWaitEsmModifyCnfActTbl ),

    /*****************定义TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND的状态转移表**********************/
      TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND,
                        g_astTafApsMsModifyingSubStaWaitEsmModifyCnfSuspendActTbl ),
#endif
};


/******************************************************************************
   3 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_GetMsModifyingStaTblSize
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
VOS_UINT32 TAF_APS_GetMsModifyingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMsModifyingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetMsModifyingFsmDescAddr
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
TAF_FSM_DESC_STRU * TAF_APS_GetMsModifyingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMsModifyingFsmDesc);
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif













