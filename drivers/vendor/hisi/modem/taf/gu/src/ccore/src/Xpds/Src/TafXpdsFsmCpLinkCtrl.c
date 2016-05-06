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

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_CP_LINK_CTRL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmCpLinkCtrl.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndXcc.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init
 功能描述  : XPDS Link Contrl Init State, Rcv Bind Server Req
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

  1.Date        :  28-08-2015
    Author      :  Arjun A00903922
    Modification:  Added Procedure
*****************************************************************************/
VOS_UINT32  TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* send XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU */
    if (VOS_ERR == TAF_XPDS_SendCallOrigMsgtoXcc(VOS_FALSE))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init: TAF_XPDS_SendCallOrigMsgtoXcc failed");
        return VOS_FALSE;
    }

    /* change fsm state to wait data call cnf */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF,
                        TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF_TIMER_LEN);

    return VOS_TRUE;
}



VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMO(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XPDS_SERVICE_CONNECT_IND_STRU   *pstServConnInd;

    pstServConnInd  = (XCC_XPDS_SERVICE_CONNECT_IND_STRU *)pstMsg;

    if ((pstServConnInd->enSo != TAF_CDMA_SO_36_LOC_SERV)
        && (pstServConnInd->enSo != TAF_CDMA_SO_35_LOC_SERV))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMO: invalid Service option");
        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_FALSE;
    }

    TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PROC_RSLT_SUCC);

    /* stop the last state timer */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND);

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;


}


VOS_UINT32 TAF_XPDS_RcvXccOrigCallCnf_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU *pstCallCnf;

    pstCallCnf  = (XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU *)pstMsg;

    /* check the result */
    if ((pstCallCnf->enRslt != TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH)
        && (pstCallCnf->enRslt != TAF_XCC_CAUSE_SUCCESS))
    {

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        TAF_XPDS_QuitFsmL2();

        return VOS_FALSE;
    }

    if (pstCallCnf->enRslt == TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH)

    {

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PROC_RSLT_SUCC);
        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;

    }

    /* change fsm state to wait SO ind */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MO);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
                        TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND_TIMER_LEN);

    return VOS_TRUE;

}


VOS_UINT32 TAF_XPDS_RcvXccCallConnInd_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XPDS_CALL_CONN_IND_STRU   *pstCallConnInd;

    pstCallConnInd  = (XCC_XPDS_CALL_CONN_IND_STRU *)pstMsg;

    if ((pstCallConnInd->enSo != TAF_CDMA_SO_36_LOC_SERV)
        && (pstCallConnInd->enSo != TAF_CDMA_SO_35_LOC_SERV))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXccCallConnInd_CpLinkCtrl_Init: invalid Service option");

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_FAIL);

        TAF_XPDS_QuitFsmL2();

        return VOS_FALSE;
    }

    TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PROC_RSLT_SUCC);

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;


}


VOS_UINT32 TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    XCC_XPDS_INCOMING_CALL_IND_STRU *pstIncomingCall;

    pstIncomingCall = (XCC_XPDS_INCOMING_CALL_IND_STRU *)pstMsg;

    TAF_XPDS_GetAgpsCfg()->enAgpsType = TAF_XPDS_NI;
    TAF_XPDS_GetAgpsCfg()->enCallType = TAF_XPDS_CTRL_PLANE;

    /* send incoming call resp */
    if (VOS_OK != TAF_XPDS_SendIncomingCallRspMsgtoXcc(pstIncomingCall->ucConnectId))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init: TAF_XPDS_SendIncomingCallRspMsgtoXcc failed");
        return VOS_FALSE;
    }

    /* check if the ucIsAlertAnsByPass is true or not,
        if true, wait for call conn ind, else send answer req */
    if(VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* state change to wait CALL_CONN_IND */

        /* change fsm state to wait answer CALL_CONN_IND */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_CALL_CONN_IND);

        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND,
                            TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND_TIMER_LEN);
        return VOS_TRUE;
    }


    /* send Answer call req */
    if (VOS_OK != TAF_XPDS_SendAnswerCallReqMsgtoXcc())
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init: TAF_XPDS_SendAnswerCallReqMsgtoXcc failed");
        return VOS_FALSE;
    }

    /* change fsm state to wait answer call cnf */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_ANSWER_CAll_CNF);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF,
                        TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF_TIMER_LEN);

    return VOS_TRUE;

}


VOS_UINT32 TAF_XPDS_RcvXccAnsCallCnf_CpLinkCtrl_WaitAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XPDS_ANSWER_CALL_CNF_STRU *pstAnsCallCnf;

    pstAnsCallCnf = (XCC_XPDS_ANSWER_CALL_CNF_STRU *)pstMsg;

    if ((TAF_XCC_CAUSE_SUCCESS != pstAnsCallCnf->enRslt)
        && (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH != pstAnsCallCnf->enRslt))
    {

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_FAIL);

        TAF_XPDS_QuitFsmL2();

        return VOS_FALSE;
    }

    if (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH == pstAnsCallCnf->enRslt)
    {

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;

    }
    /* change fsm state to wait SO ind */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MT);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
                        TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND_TIMER_LEN);
    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMT(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XPDS_SERVICE_CONNECT_IND_STRU   *pstServConnInd;

    pstServConnInd  = (XCC_XPDS_SERVICE_CONNECT_IND_STRU *)pstMsg;

    if ((pstServConnInd->enSo != TAF_CDMA_SO_36_LOC_SERV)
        && (pstServConnInd->enSo != TAF_CDMA_SO_35_LOC_SERV))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMT: invalid Service option");

        TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_FAIL);

        TAF_XPDS_QuitFsmL2();

        return VOS_FALSE;
    }

    TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PROC_RSLT_SUCC);

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;

}


VOS_UINT32 TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_QuitFsmL2();
    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


