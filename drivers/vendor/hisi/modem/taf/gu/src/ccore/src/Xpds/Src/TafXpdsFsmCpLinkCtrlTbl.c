/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmCpLinkCtrlTbl.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : Xpds Link Ctrl Fsm Tbl file
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCpLinkCtrlStaTblSize
 功能描述  : 获取XPDS Link Ctrl状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetCpLinkCtrlStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsCpLinkCtrlStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCpLinkCtrlStaTblSize
 功能描述  : 获取XPDS Link Ctrl状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_STA_STRU* TAF_XPDS_GetCpLinkCtrlStaTblAddr( VOS_VOID )
{
    return g_astTafXpdsCpLinkCtrlStaTbl;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmLinkFsmDescAddr
 功能描述  : 获取XPDS LINK Ctrl状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
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




