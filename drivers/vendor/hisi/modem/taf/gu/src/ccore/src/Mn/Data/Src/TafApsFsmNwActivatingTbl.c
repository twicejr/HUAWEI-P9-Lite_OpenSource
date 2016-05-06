
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmNwActivatingTbl.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : Nw Activating状态机处理表
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
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmNwActivating.h"
#include "AtMnInterface.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_NWACTIVATING_TBL_C

/******************************************************************************
   2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:NW ACTIVATING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsNwActivatingFsmDesc;

/* TAF_APS_NW_ACTIVATING_SUBSTA_INIT*/
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_IND,
                     TAF_APS_RcvSmPdpActivateInd_NwActivating_Init),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_APP_ESM_PDP_MANAGER_IND,
                     TAF_APS_RcvEsmPdpManageInd_NwActivating_Init),
#endif
};

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER动作表 */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitAppAnswerActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvSetPdpContextStateReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_NwActivating_WaitAppAnswer),

};

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitSmCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_REJ,
                     TAF_APS_RcvSmPdpActRej_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_REJ,
                     TAF_APS_RcvSmPdpActSecRej_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_CNF,
                     TAF_APS_RcvSmPdpActSecCnf_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_CNF,
                     TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSmActivateCnf),
};

#if (FEATURE_ON == FEATURE_LTE)
/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF动作表 */
TAF_ACT_STRU g_astTafApsNwActivatingSubStaWaitEsmCgansActTbl[] =
{

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_SET_CGANS_CNF,
                     TAF_APS_RcvL4aSetCgansCnf_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitEsmCgansCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitEsmCgansCnf),

};
#endif

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP动作表 */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitSndcpActivateRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_ACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSndcpActivateRsp),
};

TAF_STA_STRU g_astTafApsNwActivatingStaTbl[] =
{
    /*****************定义TAF_APS_NW_ACTIVATING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_INIT,
                      g_astTafApsNwActivatingSubStaInitActTbl ),

    /*****************定义TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER,
                      g_astTafApsNwActivatingSubStaWaitAppAnswerActTbl ),

    /*****************定义TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF,
                      g_astTafApsNwActivatingSubStaWaitSmCnfActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_STA_TBL_ITEM(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF,
                     g_astTafApsNwActivatingSubStaWaitEsmCgansActTbl),
#endif
    /*****************定义TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP,
                      g_astTafApsNwActivatingSubStaWaitSndcpActivateRspActTbl ),

};


/******************************************************************************
   3 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_GetNwActivatingStaTblSize
 功能描述  : 获取NW ACTIVATING状态机的大小
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
VOS_UINT32 TAF_APS_GetNwActivatingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsNwActivatingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetNwActivatingFsmDescAddr
 功能描述  : 获取NW ACTIVATING状态机的描述表
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
TAF_FSM_DESC_STRU * TAF_APS_GetNwActivatingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsNwActivatingFsmDesc);
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif










