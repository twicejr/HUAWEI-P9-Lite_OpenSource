/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmUpLinkCtrl.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : Xpds Link Ctrl Fsm
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

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_UP_LINK_CTRL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmUpLinkCtrl.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetServerBindOperType
 功能描述  : 获取服务器操作类型
 输入参数  : TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOper
             TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOper
 输出参数  : 无
 返 回 值  : TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8 TAF_XPDS_GetServerBindOperType(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOper,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOper
)
{
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32                  enCurrMpcStatus;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32                  enCurrPdeStatus;

    enCurrMpcStatus = TAF_XPDS_GetMpcServerStatus();
    enCurrPdeStatus = TAF_XPDS_GetPdeServerStatus();

    if ((enMpcBindOper == enCurrMpcStatus)
     && (enPdeBindOper == enCurrPdeStatus))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_NO_ACT;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT     == enCurrMpcStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET == enMpcBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT     == enCurrPdeStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET == enPdeBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_CLOSE_PDE_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_IDLE       == enCurrMpcStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET == enMpcBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_IDLE       == enCurrPdeStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET == enPdeBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_OPEN_PDE_SOCKET;
    }

    return TAF_XPDS_SERVER_BIND_TYPE_NO_ACT;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetServerBindFailCause
 功能描述  : 获取Bind Fail 原因值
 输入参数  : TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
 输出参数  : 无
 返 回 值  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetServerBindFailCause(
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
)
{
    if ((enBindType == TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET)
     || (enBindType == TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET))
    {
        return TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT;
    }
    else
    {
        return TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_UpLinkCtrlServerBindProc
 功能描述  : Bind/Release MPC/PDE Server操作
 输入参数  : TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8                    enBindType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_UpLinkCtrlServerBindProc(
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
)
{
    TAF_XPDS_CFG_INFO_STRU             *pstConfigInfo;

    pstConfigInfo = TAF_XPDS_GetAgpsCfg();

    switch (enBindType)
    {
        case TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET:

            TAF_XPDS_SndAtApOpenSocketReq(AT_XPDS_SERVER_MODE_MPC,
                                          pstConfigInfo->ulMpcAddr,
                                          pstConfigInfo->ulMpcPort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_OPEN_PDE_SOCKET:

            TAF_XPDS_SndAtApOpenSocketReq(AT_XPDS_SERVER_MODE_PDE,
                                          pstConfigInfo->ulPdeAddr,
                                          pstConfigInfo->ulPdePort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET:

            TAF_XPDS_SndAtApCloseSocketReq(AT_XPDS_SERVER_MODE_MPC,
                                           pstConfigInfo->ulMpcAddr,
                                           pstConfigInfo->ulMpcPort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_CLOSE_PDE_SOCKET:

            TAF_XPDS_SndAtApCloseSocketReq(AT_XPDS_SERVER_MODE_PDE,
                                           pstConfigInfo->ulPdeAddr,
                                           pstConfigInfo->ulPdePort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF);

            break;

        default:
            return;
    }

    /* 启动保护定时器 */
    if (TAF_XPDS_TIMER_START_FAILURE == TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                                                            TI_TAF_XPDS_WAIT_AT_BINDUP_IND_TIMER_LEN))
    {
        XPDS_WARNING_LOG("TAF_XPDS_UpLinkCtrlServerBindProc: WARNING: Start Timer failed!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_UpLinkCtrlPreEntryMsgProc
 功能描述  : 如果进入Init的入口消息还未处理完毕，继续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_UpLinkCtrlPreEntryMsgProc(VOS_VOID)
{
    TAF_XPDS_MSG_STRU                                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU                    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8                    enBindType;

    pstEntryMsg       = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq  = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;


    enBindType        = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                   pstBindServerReq->enPdeBindOpt);

    /* 如果入口消息指定的操作类型与本地服务器维护的Socket Bind状态一致，退出L2状态机 */
    if (TAF_XPDS_SERVER_BIND_TYPE_NO_ACT == enBindType)
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_QuitFsmL2();

        return;
    }

    TAF_XPDS_UpLinkCtrlServerBindProc(enBindType);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init
 功能描述  : User Plane, Rcv L1 Open/Close Server Socker Req
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq = VOS_NULL_PTR;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;

    pstBindServerReq = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstMsg;
    enBindType       = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                      pstBindServerReq->enPdeBindOpt);

    /* Init函数里将Abort状态设置为VOS_FALSE */
    TAF_XPDS_SetUplinkAbortScene(TAF_XPDS_PROC_RSLT_SUCC);

    /* 如果入口消息指定的操作类型与本地服务器维护的Socket Bind状态一致，退出L2状态机 */
    if (TAF_XPDS_SERVER_BIND_TYPE_NO_ACT == enBindType)
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 保存入口消息 */
    TAF_XPDS_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 如果AGPS Data Call不存在，需要先去建立Data Call */
    if (AT_XPDS_DATA_CALL_STATUS_IDLE == TAF_XPDS_GetDataCallStatus())
    {
        /* 发送消息给给Open Cagps Data CAll 状态*/
        TAF_XPDS_SndAtApOpenCagpsDataCall();

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF);

        /* 设置等待AP回复定时器 */
        if (TAF_XPDS_TIMER_START_FAILURE == TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND,
                                                                TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND_TIMER_LEN))
        {
            XPDS_WARNING_LOG("TAF_XPDS_RcvXpdsServerBindOperReq_UpLinkCtrl_Init: WARNING: Start Timer failed!");
        }

        return VOS_TRUE;
    }

    TAF_XPDS_UpLinkCtrlServerBindProc(enBindType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf
 功能描述  : In Xpds Link Control Init State, Rcv Data CAll Status Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU   *pstMsgDataCallInd;
    TAF_XPDS_MSG_STRU                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enRslt;

    pstEntryMsg       = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq  = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;
    enBindType        = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                       pstBindServerReq->enPdeBindOpt);

    pstMsgDataCallInd = (AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU *)pstMsg;

    /* 保存与AP通道使用的ClientId */
    TAF_XPDS_SetApClientId(pstMsgDataCallInd->stAppCtrl.usClientId);

    /* 停止切换APN，建立AGPS Data Call的等待定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND);

    /* 更新AGPS DATA CALL STATUS */
    TAF_XPDS_SetDataCallStatus(pstMsgDataCallInd->enChannelState);

    /* 如果当前存在Abort场景，直接回复L1 Abort CNF */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果切换APN失败,回复Failure */
    if (AT_XPDS_DATA_CALL_STATUS_CONNECT != pstMsgDataCallInd->enChannelState)
    {
        enRslt = TAF_XPDS_GetServerBindFailCause(enBindType);

        TAF_XPDS_SndInternalServerBindRsltCnf(enRslt);

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket
 功能描述  : In Xpds Link Ctrl Init State, Rcv server Bind Rslt Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (AT_XPDS_SERVER_MODE_MPC != pstMsgBindStatusInd->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_SetMpcServerStatus(pstMsgBindStatusInd->enBindStatus);

    /* 停止等待定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    /* 存在Abort标记，则直接退出L2状态机 */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == pstMsgBindStatusInd->enBindStatus)
    {
        /* 继续Check是否继续去Open PDE Socket */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);

        TAF_XPDS_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket
 功能描述  : Wait Close Mpc Socket State, rcv Bind Status Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (AT_XPDS_SERVER_MODE_MPC != pstMsgBindStatusInd->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    TAF_XPDS_SetMpcServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    /* 存在Abort标记，则直接退出L2状态机 */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 继续Check是否继续操作其他服务器 */
    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket
 功能描述  : Wait Open Pde Socket State, Rcv bind Status Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (AT_XPDS_SERVER_MODE_PDE != pstMsgBindStatusInd->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_SetPdeServerStatus(pstMsgBindStatusInd->enBindStatus);

    /* 停止等待定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    /* 存在Abort标记，则直接退出L2状态机 */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == pstMsgBindStatusInd->enBindStatus)
    {
        /* 继续Check是否继续去Open MPC Socket */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);

        TAF_XPDS_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket
 功能描述  : Wait Close Pde Socket State, rcv Bind Status Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (AT_XPDS_SERVER_MODE_PDE != pstMsgBindStatusInd->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    TAF_XPDS_SetPdeServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    /* 存在Abort标记，则直接退出L2状态机 */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 继续Check是否继续操作其他服务器 */
    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf
 功能描述  : 等待切换APN 建立CAGPS Data Call超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_MSG_STRU                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enRslt;

    pstEntryMsg      = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;
    enBindType       = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                      pstBindServerReq->enPdeBindOpt);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        enRslt = TAF_XPDS_GetUpLinkAbortScene();
    }
    else
    {
        enRslt = TAF_XPDS_GetServerBindFailCause(enBindType);
    }

    TAF_XPDS_SndInternalServerBindRsltCnf(enRslt);

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket
 功能描述  : MPC Bind server超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);
    }

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket
 功能描述  : MPC关闭Socket，等待超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetMpcServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* 继续Check是否继续操作其他服务器 */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket
 功能描述  : 等待建立PDE Socket链路超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);
    }

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket
 功能描述  : PDE关闭Socket，等待超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 TAF_XPDS_RcvTiWaitClosePdeSocketExpired_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetPdeServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* 继续Check是否继续操作其他服务器 */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink
 功能描述  : L2 User Plane状态机，收到abort异常
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortInd;

    pstAbortInd = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *)pstMsg;

    TAF_XPDS_SetUplinkAbortScene(pstAbortInd->enAbortScene);

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


