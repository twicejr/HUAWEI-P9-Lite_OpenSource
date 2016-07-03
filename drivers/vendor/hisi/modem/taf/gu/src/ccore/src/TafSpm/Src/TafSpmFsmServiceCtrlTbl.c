

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "UsimPsInterface.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafSpmMain.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmServiceCtrl.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafFsm.h"
#include "Taf_Tafm_Remote.h"
#include "siapppb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_SERVICE_CTRL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* UTRANCTRL模块的模式变更状态机 */
TAF_FSM_DESC_STRU                       g_stTafSpmServiceCtrlFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* TAF_SPM_SERVICE_CTRL_STA_INIT 动作表 */
TAF_ACT_STRU        g_astTafSpmServiceCtrlInitActTbl[]   =
{
    /* AT SS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGISTERSS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASESS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ACTIVATESS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_DEACTIVATESS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_INTERROGATESS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGPWD_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASECCENTRY_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PROCESS_USS_MSG,
                      TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init ),


    /* STK SS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGISTERSS_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ERASESS_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ACTIVATESS_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_DEACTIVATESS_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_INTERROGATESS_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGPWD_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_USSD_REQ,
                      TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init ),

    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAtCallReqMsg_ServiceCtrl_Init ),


    /* AT SMS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                      TAF_SPM_RcvAtSmsReqMsg_ServiceCtrl_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                      TAF_SPM_RcvAtSmsReqMsg_ServiceCtrl_Init ),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_CALLORIG_REQ,
                      TAF_SPM_RcvStkCallReqMsg_ServiceCtrl_Init ),


    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvStkSmsReqMsg_ServiceCtrl_Init ),

#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_ECONF_DIAL_REQ,
                      TAF_SPM_RcvAtCallReqMsg_ServiceCtrl_Init ),
#endif
};

/* TAF_SPM_SERVICE_CTRL_STA_WAIT_PB_FDN_CHECK_CNF 动作表 */
TAF_ACT_STRU        g_astTafSpmServiceCtrlWaitPbFdnCheckCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_FDNCHECK_CNF,
                      TAF_SPM_RcvPbFdnCheckCnf_ServiceCtrl_WaitPbFdnCheckCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF,
                      TAF_SPM_RcvTiWaitPbFdnCheckCnfExpired_ServiceCtrl_WaitPbFdnCheckCnf ),
};

/* TAF_SPM_SERVICE_CTRL_STA_WAIT_USIM_CALL_CTRL_CNF 动作表 */
TAF_ACT_STRU        g_astTafSpmServiceCtrlWaitUsimCallCtrlCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      SI_STK_ENVELOPE_CNF,
                      TAF_SPM_RcvUsimEnvelopeCnf_ServiceCtrl_WaitUsimCallCtrlCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF,
                      TAF_SPM_RcvTiWaitUsimCallCtrlCnfExpired_ServiceCtrl_WaitUsimCallCtrlCnf ),

};

/* 业务控制状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafSpmServiceCtrlStaTbl[]   =
{
    /* 业务控制的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_SPM_SERVICE_CTRL_STA_INIT,
                       g_astTafSpmServiceCtrlInitActTbl ),

    /* 等待USIM的fDN的检查结果状态 */
    TAF_STA_TBL_ITEM( TAF_SPM_SERVICE_CTRL_STA_WAIT_PB_FDN_CHECK_CNF,
                      g_astTafSpmServiceCtrlWaitPbFdnCheckCnfActTbl ),

    /* 等待USIM的CALL CONTRL的检查结果状态 */
    TAF_STA_TBL_ITEM( TAF_SPM_SERVICE_CTRL_STA_WAIT_USIM_CALL_CTRL_CNF,
                      g_astTafSpmServiceCtrlWaitUsimCallCtrlCnfActTbl )
};


VOS_UINT32 TAF_SPM_GetServiceCtrlStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafSpmServiceCtrlStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_SPM_GetServiceCtrlFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmServiceCtrlFsmDesc);
}






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


