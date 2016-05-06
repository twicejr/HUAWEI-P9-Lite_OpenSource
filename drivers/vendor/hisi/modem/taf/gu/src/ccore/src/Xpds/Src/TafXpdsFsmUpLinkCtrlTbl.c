/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmLinkCtrlTbl.c
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

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_UP_LINK_CTRL_TBL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmUpLinkCtrl.h"
#include "TafXpdsSndInternalMsg.h"
#include "AtXpdsInterface.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* TAF XPDS LINK状态机数组:CDATA LINK Ctrl 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafXpdsUpLinkCtrlFsmDesc;

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaInitTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_UP_LINK_CTRL_REQ,
                      TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init),
};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitDataCallConnectCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_DATA_CALL_STATUS_IND,
                      TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND,
                      TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),
};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitOpenMpcSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitCloseMpcSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitOpenPdeSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF动作表 */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitClosePdeSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitClosePdeSocketExpired_UpLinkCtrl_WaitClosePdeSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),
};

TAF_STA_STRU g_astTafXpdsUpLinkCtrlStaTbl[] =
{

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT,
                      g_astTafXpdsUpLinkCtrlSubStaInitTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitDataCallConnectCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitOpenMpcSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitCloseMpcSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitOpenPdeSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitClosePdeSocketCnfTbl ),

};

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetUpLinkCtrlStaTblSize
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
VOS_UINT32 TAF_XPDS_GetUpLinkCtrlStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsUpLinkCtrlStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetUpLinkCtrlStaTblAddr
 功能描述  : 获取XPDS Up Link Ctrl状态机的大小
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
TAF_STA_STRU* TAF_XPDS_GetUpLinkCtrlStaTblAddr( VOS_VOID )
{
    return g_astTafXpdsUpLinkCtrlStaTbl;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmUpLinkFsmDescAddr
 功能描述  : 获取XPDS Up LINK Ctrl状态机的描述表
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
TAF_FSM_DESC_STRU * TAF_XPDS_GetFsmUpLinkFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsUpLinkCtrlFsmDesc);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



