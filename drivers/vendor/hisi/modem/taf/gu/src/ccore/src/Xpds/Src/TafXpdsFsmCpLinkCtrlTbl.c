
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_CP_LINK_CTRL_TBL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmCpLinkCtrlTbl.h"
#include "TafXpdsFsmCpLinkCtrl.h"
#include "TafXpdsSndInternalMsg.h"
#include "AtXpdsInterface.h"
#include "TafXpdsFsmCpLinkCtrl.h"
#include "cas_1x_control_main_nas_pif.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* TAF XPDS LINK状态机数组:CDATA LINK Ctrl 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafXpdsCpLinkCtrlFsmDesc;

/* TAF_APS_CDATA_DISCING_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaInitTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_CP_LINK_START_REQ,
                      TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XPDS_INCOMING_CALL_IND,
                      TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init),

};

TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaWaitDataCallConnectCnfTbl[] =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                      ID_XCC_XPDS_ORIG_AGPS_CALL_CNF,
                      TAF_XPDS_RcvXccOrigCallCnf_CpLinkCtrl_Init),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF,
                      TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl),

};

TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaWaitCallConnIndTbl[] =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                      ID_XCC_XPDS_CALL_CONN_IND,
                      TAF_XPDS_RcvXccCallConnInd_CpLinkCtrl_Init),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND,
                      TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl),

};

TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaWaitXccDataCallStatusIndMOTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                      ID_XCC_XPDS_SERVICE_CONNECT_IND,
                      TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMO),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
                      TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl),

};

TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaWaitXccDataCallStatusIndMTTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                      ID_XCC_XPDS_SERVICE_CONNECT_IND,
                      TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMT),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
                      TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl),

};


TAF_ACT_STRU   g_astTafXpdsCpLinkCtrlSubStaWaitXccAnswerCallCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                      ID_XCC_XPDS_ANSWER_CALL_CNF,
                      TAF_XPDS_RcvXccAnsCallCnf_CpLinkCtrl_WaitAnsCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF,
                      TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl),

};


TAF_STA_STRU g_astTafXpdsCpLinkCtrlStaTbl[] =
{

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_LINK_CTRL_SUBSTA_INIT,
                      g_astTafXpdsCpLinkCtrlSubStaInitTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF,
                      g_astTafXpdsCpLinkCtrlSubStaWaitDataCallConnectCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_CALL_CONN_IND,
                      g_astTafXpdsCpLinkCtrlSubStaWaitCallConnIndTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MO,
                      g_astTafXpdsCpLinkCtrlSubStaWaitXccDataCallStatusIndMOTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_ANSWER_CAll_CNF,
                      g_astTafXpdsCpLinkCtrlSubStaWaitXccAnswerCallCnfTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MT,
                      g_astTafXpdsCpLinkCtrlSubStaWaitXccDataCallStatusIndMTTbl ),


};


VOS_UINT32 TAF_XPDS_GetCpLinkCtrlStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsCpLinkCtrlStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetCpLinkCtrlStaTblAddr( VOS_VOID )
{
    return g_astTafXpdsCpLinkCtrlStaTbl;
}


TAF_FSM_DESC_STRU * TAF_XPDS_GetFsmCpLinkFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsCpLinkCtrlFsmDesc);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




