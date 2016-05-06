/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmPdeProc.c
  版 本 号   : 初稿
  作    者   : c00299064
  生成日期   : 2015年08月24日
  功能描述   : MPC状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月24日
    作    者   : c00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafMtaMain.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmMpcProc.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndXsms.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MPC_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvMpcLinkConnectedMsg_MpcProc_Init
 功能描述  : 在MPC INIT状态收到链路建链成功的消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvMpcOperationReqMsg_MpcProc_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU              *pstStartReq;

    pstStartReq = (TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU*)pstMsg;

    TAF_XPDS_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 如果当前需要发送START POS REQ */
    if (TAF_XPDS_MPC_OPER_START_POS_REQ == pstStartReq->enMpcOperation)
    {
        TAF_XPDS_SndAtApMpcStartPosReq();

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_RL_START_POS_REQ);

        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_MPC_START_POS_RSP, TI_TAF_XPDS_WAIT_MPC_START_POS_RSP_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_MPC_PROC_STA_WAIT_START_POS_RESP);
    }
    else if (TAF_XPDS_MPC_OPER_POS_REPORT == pstStartReq->enMpcOperation)
    {
        /* 如果上报Pos Report至MPC服务器，表明此时已经Fix计算出位置，当前FixNum次数需要累加 */
        TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum++;

        TAF_XPDS_SndAtApMpcPosReportReq();

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_RL_POS_REPORT);

        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP, TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP_TIMER_LEN);

        /* 如果当前需要发送POS_REPORT */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_MPC_PROC_STA_WAIT_POS_REPORT_RESP);
    }
    else
    {
        /* 参数错误 */
        TAF_XPDS_QuitFsmL2();

        TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_BUTT, TAF_XPDS_PDE_PROC_RSLT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvMpcStartPosResp_MpcProc_WaitStartPosResp
 功能描述  : 在MPC WaitStartPosResp状态收到MpcStartPosResp消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvMpcStartPosResp_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 根据RESP的原因值进行处理 */
    TAF_XPDS_MPC_START_POS_RSP_STRU    *pstStartResp;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enMpcRslt = TAF_XPDS_PROC_RSLT_BUTT;

    pstStartResp = (TAF_XPDS_MPC_START_POS_RSP_STRU*)pstMsg;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_MPC_START_POS_RSP);

    /* 信息存储 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stStartPosRsp),
               pstStartResp,
               sizeof(TAF_XPDS_MPC_START_POS_RSP_STRU));

    /* 根据不同的原因值进行处理 */
    switch (pstStartResp->enPosStatusInd)
    {
        case TAF_XPDS_POS_STATUS_INDICATOR_USE_GPSONE:

            enMpcRslt = TAF_XPDS_PROC_RSLT_SUCC;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_CACHED_POS:
        case TAF_XPDS_POS_STATUS_INDICATOR_WITH_CELL_SECTOR:

            enMpcRslt = TAF_XPDS_MPC_OPER_RSLT_POS_TECH_CHANGED;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_REQ_NOT_AUTH:
        case TAF_XPDS_POS_STATUS_INDICATOR_MPC_REFUSED:
        case TAF_XPDS_POS_STATUS_INDICATOR_SRV_UNAVAILABLE:
        case TAF_XPDS_POS_STATUS_INDICATOR_CANCEL_FIX_REQ:

            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_ACK_REQ_NO_ACTION:
            /* 对于UE来说，默认的定位技术是GPSONE 所以回复不需要下一步操作是不对的 */
            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;
            break;

        default:
            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;
            break;

    }

    /* 将处理结果发送給L1状态机 */

    TAF_XPDS_QuitFsmL2();

    /*
      如果是单次定位，启动IS 801会话定时器

      中国电信需求：
      LBS-05012  [必选]   第三方定位流程
      6） 当发生的是一个单次定位时，
          终端在收到 Start Positioning Process Response消息后应启动一个定时器 T8

      非第三方定位也要启动T8定时器:
      表 A-1： WAP/WEB 定位应用中的定时器值
      Timer  Default value (sec)  Set at  Description                              Action on expiration
      T8     32                   MS      从收到SPPRes 到完成 IS-801 会话的定时器  向 CP 发送无位置信息的第二次WAP/WEB 业务请求
    */
    if ((1 == TAF_XPDS_GetAgpsCfg()->usFixNum)
     && (TAF_XPDS_PROC_RSLT_SUCC == enMpcRslt))
    {
        TAF_XPDS_StartTimer(TI_TAF_XPDS_IS801_SESSION, TI_TAF_XPDS_IS801_SESSION_TIMER_LEN);
    }

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_START_POS_REQ, enMpcRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiStartPosRespExperied_MpcProc_WaitStartPosResp
 功能描述  : 在MPC WaitStartPosResp状态收到MpcStartPosResp消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiStartPosRespExperied_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 等待超时的处理 */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_START_POS_REQ, TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvMpcPosReportResp_MpcProc_WaitPosReportResp
 功能描述  : 在MPC WaitPOS REP Resp状态收到POS REPORT RESP消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvMpcPosReportResp_MpcProc_WaitPosReportResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enPosRslt;
    TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU         *pstPosReportResp;
    TAF_XPDS_CFG_INFO_STRU                                 *pstCagpsConfigInfo;

    pstCagpsConfigInfo = TAF_XPDS_GetAgpsCfg();

    pstPosReportResp  = (TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU*)pstMsg;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP);

    switch (pstPosReportResp->stPosReportRsp.enReportStatus)
    {
        case TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ACK:
            enPosRslt = TAF_XPDS_PROC_RSLT_SUCC;
            break;

        case TAF_XPDS_MPC_REPORT_STATUS_DISCON_REPORT:
            enPosRslt = TAF_XPDS_MPC_OPER_RSLT_DISCON_REPORT;
            break;

        case TAF_XPDS_MPC_REPORT_STATUS_PDE_HANDOFF:
            enPosRslt = TAF_XPDS_MPC_OPER_RSLT_PDE_HANDOFF;
            pstCagpsConfigInfo->ulPdeAddr = TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp.stPdeAddr.ulPdeIpAddr;
            pstCagpsConfigInfo->ulPdePort = TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp.stPdeAddr.usPdePortNum;

            break;

        default:
            enPosRslt = TAF_XPDS_PROC_RSLT_SUCC;
            break;

    }

    /* 根据RESP的原因值进行处理 */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_POS_REPORT, enPosRslt);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiPosReportExperied_MpcProc_WaitStartPosResp
 功能描述  : 在MPC WaitResp状态收到定时器超时消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiPosReportExperied_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 等待超时的处理 */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_POS_REPORT, TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsAbortInd_MpcProc
 功能描述  : 在MPC 状态收到ABORT IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月29日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsAbortInd_MpcProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortInd;

    pstAbortInd = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU*)pstMsg;

    if (TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT == pstAbortInd->enAbortScene)
    {
        return VOS_TRUE;
    }

    /* 等待超时的处理 */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_BUTT, pstAbortInd->enAbortScene);

    return VOS_TRUE;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */









