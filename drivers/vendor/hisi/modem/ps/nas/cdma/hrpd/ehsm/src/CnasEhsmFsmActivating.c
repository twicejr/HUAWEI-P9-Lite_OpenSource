/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmFsmActivating.c
 Author          :
 Version         :
 Date            :   18/05/2015
 Description     :   This file has definition of each message handler in EHSM ACTIVATING FSM.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmMntn.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmFsmActivating.h"
#include "CnasEhsmSndHsm.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmSndAps.h"
#include "CnasEhsmSndEsm.h"
#include "ehsm_hsd_pif.h"
#include "CnasEhsmEncode.h"

/* To Do: Need to add EHSM to APS interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_ACTIVATING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all message handlers in EHSM activating FSM */


VOS_UINT32 CNAS_EHSM_RcvEhsmAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU     *pstAttachReq    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid ;

    pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)pstMsg;

    /* 申请PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* After allocating PDNid in EHSM PDN info, need to allocate CID if the entry message reason is initial attach.
        If the entry message reason is hand over attach, get first used cid from LTE pdn info array */
    if (CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH == pstAttachReq->enAttachReason)
    {
        /* 初始化Initial Attach的Cid值为0 */
        ucCid = 0;

        /* Need to find valid cid and save sdf param in local pdn info */
        CNAS_EHSM_GetSdfParaAndSaveLocalPdnInfo(ucPdnId, ucCid);
    }
    else
    {
        /* 处理HandOver Attach的情况 */
        /*
            1. ehsm收到sync pdn info后，根据ctx 中astLtePdnBearInfo是否使用存放该pdn info
            当后续存取时，要首先获取对应pdn info的索引值
            2.handover时，通过pdnid和lte pdn info的索引值，先把lte pdn info拷贝到local ehrpd pdn info数组中，方便读取
            3. cid可以同pdnid直接从ctx中的astLocalPdnBearInfo中读取
        */
        CNAS_EHSM_LoadLocalPdnInfoFromLteInfo(ucPdnId, CNAS_EHSM_GetLtePdnIndexWithMinEspbId());
        ucCid = CNAS_EHSM_GetCidByPdnId(ucPdnId);
    }

    /* Save the generated PDNid and CID in activating FSM ctx
        And save the generated CID in EHSM pdn info */
    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, ucCid);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstRconnReq  = VOS_NULL_PTR;

    pstRconnReq = (APS_EHSM_RECONN_REQ_STRU*)pstMsg;

    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    CNAS_EHSM_SetPdnIdCid_Activating(pstRconnReq->ucPdnId, CNAS_EHSM_GetCidByPdnId(pstRconnReq->ucPdnId));

    CNAS_EHSM_SndHsmConnEstReq();
    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstPdnActReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstPdnActReq = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstMsg;

    /* 申请PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Save the generated PDNid and CID in activating FSM ctx */
    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, pstPdnActReq->ucCid);

    CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(ucPdnId);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();
        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init
 功能描述  : EHSM激活状态机处理APS Attach请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_ATTACH_REQ_STRU       *pstAttachReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid ;

    pstAttachReq = (APS_EHSM_PDN_ATTACH_REQ_STRU*)pstMsg;

    /* 申请PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    ucCid = pstAttachReq->ucCid;

    /* 获取激活PDN相应的信息*/
    CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(ucPdnId);

    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, ucCid);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmPdnSetupReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU   *pstReEstReq = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdnId;

    pstReEstReq = (CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU *)pstMsg;

    /* 申请PdnId */
    ucPdnId  = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* get PDN Info from LTE pdn info And set Cid in local bearer PDN info */
    CNAS_EHSM_LoadLocalPdnInfoFromLteInfo(ucPdnId, (VOS_UINT8)pstReEstReq->ulLtePdnIndex);

    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, CNAS_EHSM_GetCidByPdnId(ucPdnId));

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_CONN_EST_CNF_STRU             *pstConnEstCnf   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                     *pstEntryMsg     = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                     *pstCtxAdrr      = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU   *pstRetryInfo    = VOS_NULL_PTR;
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU         *pstAttachReq    = VOS_NULL_PTR;
    VOS_UINT32                              ulConnRetryFlag;
    VOS_UINT8                               ucPdnId;
    VOS_UINT8                               ucCid;

    pstConnEstCnf   = (HSM_EHSM_CONN_EST_CNF_STRU *)pstMsg;
    pstEntryMsg     = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstCtxAdrr      = CNAS_EHSM_GetEhsmCtxAddr();
    pstRetryInfo    = CNAS_EHSM_GetRetryInfo_Activating();
    ucPdnId         = CNAS_EHSM_GetPdnId_Activating();
    ucCid           = CNAS_EHSM_GetCidByPdnId(ucPdnId);
    ulConnRetryFlag = VOS_FALSE;

    /* 停止建链保护定时器 */
    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

    if (EHSM_HSM_RSLT_SUCCESS == pstConnEstCnf->enResult)
    {
        CNAS_EHSM_SetAirLinkExistFlag(VOS_TRUE);
    }

    /* 建链成功的处理 */
    if (EHSM_HSM_RSLT_SUCCESS == pstConnEstCnf->enResult)
    {
        CNAS_EHSM_ResetConntRetryTimes_Activating();

        if (CNAS_EHSM_EHRPD_DORMANT_STA == CNAS_EHSM_GetEhrpdState())
        {
            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_ACTIVE_STA);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_SUCCESS, ucPdnId, ucCid);

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_TRUE);

            CNAS_EHSM_QuitFsmL2();

            return VOS_TRUE;
        }

        if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
        {
            /* 如果PDN已经处在激活过程中，则不再发送Attach_Req/Conn_Req */
            CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(CNAS_CTTF_EHRPD_LINK_CONNECTED);
        }
        else
        {
            if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
            {
                pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

                CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);
            }
            else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
            {
                CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
            }
            else
            {
                CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);
            }

            CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);
        }

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }
    else
    {
        /* 建链失败的处理 */
        ulConnRetryFlag = CNAS_EHSM_IsCommonConnRetryNeeded(pstConnEstCnf->enResult);

        if ((VOS_TRUE == ulConnRetryFlag)
         && (pstRetryInfo->usCurConnEstRetryTimes < pstCtxAdrr->stRetryCtrlInfo.stRetryConnEstInfo.usMaxNoOfRetry))
        {
            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST, pstCtxAdrr->stRetryCtrlInfo.stRetryConnEstInfo.ulExpireTimerLen);
            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT);
        }
        else
        {
            if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
            {
                /* 之前已经发过Attach_req/Pdn_Conn_Req */
                CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

                /* 如果当前是最后一个PDN,直接发送Detach Ind */
                if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
                {
                    CNAS_EHSM_SndCttfEhrpdDetachInd();
                }
                else
                {
                    CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(ucPdnId);
                }
            }

            CNAS_EHSM_EstPdnFailureHandler_Activating(CNAS_EHSM_MapHsmCauseToAps(pstConnEstCnf->enResult),
                                                      pstEntryMsg->ulEventType);

            if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
             || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
            {
                CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
            }
            else
            {
                CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
            }

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 之前已经发过Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        /* 如果当前是最后一个PDN,直接发送Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }
    }

    /* 建链超时的处理 */
    CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT, pstEntryMsg->ulEventType);

    if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
      ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
    }
    else
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
    }

    CNAS_EHSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvTiWaitConnRetryEst_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* retry time count increse */
    CNAS_EHSM_IncreConntRetryTimes_Activating();

    CNAS_EHSM_SndHsmConnEstReq();

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU      *pstAbortMsg    = VOS_NULL_PTR;

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

    pstAbortMsg = (CNAS_EHSM_EHSM_ABORT_REQ_STRU *)pstMsg;

    /* DORMANT状态下重新建链被挂起 */
    if (CNAS_EHSM_EHRPD_DORMANT_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_SUSPEND_STA);
    }

    CNAS_EHSM_ProcAbortProcedure_Activating(pstAbortMsg->ulEventType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry
 功能描述  : 子状态CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT下收
             到消息ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_CONN_EST_FAIL,
                                                  pstEntryMsg->ulEventType);

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

        CNAS_EHSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry
 功能描述  : 子状态CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT下收
             到消息ID_CTTF_CNAS_EHRPD_ATTACH_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);
        /* 之前已经发过Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(pStAttachCnf->enErrorCode));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry
 功能描述  : 子状态CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT下收
             到定时器TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        /* 如果当前是最后一个PDN,直接发送Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                                  pstEntryMsg->ulEventType);

        if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
          ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);
        }
        else
        {
            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry
 功能描述  : 等待链路重建时收到HSM发送的Session Info Ind消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstHsmSessionInd = VOS_NULL_PTR;

    pstHsmSessionInd = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    CNAS_EHSM_SetSessionType(pstHsmSessionInd->enSessionType);

    if (EHSM_HSM_SESSION_TYPE_EHRPD == pstHsmSessionInd->enSessionType)
    {
        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        /* retry time count increse */
        CNAS_EHSM_IncreConntRetryTimes_Activating();

        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

        return VOS_TRUE;
    }
    else
    {
        /* 此处必须返回VOS_FALSE,非EHRPD模式后续会处理为Abort的内部消息 */
        return VOS_FALSE;
    }
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnSetUpCnf = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo     = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    pstPdnSetUpCnf = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)pstMsg;
    pstPdnInfo     = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[pstPdnSetUpCnf->ucPdnId]);

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

    if (CNAS_CTTF_EHRPD_RSLT_SUCCESS == pstPdnSetUpCnf->enPdnConnRslt)
    {
        /* clean the retry pdn info */
        CNAS_EHSM_InitApnRetryInfo();

        /* update ehrpd local pdn info */
        CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromPdnConnCnf(pstPdnInfo, pstPdnSetUpCnf);

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnActivateCnf(pstPdnInfo->ucCid, EHSM_APS_CAUSE_SUCCESS);

            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_CONNECTED);
        }

        if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsLteHandOverToEhrpdInd(pstPdnSetUpCnf->ucPdnId, EHSM_APS_PDN_OPTION_MODIFIED);

            /* Incase of HAND OVER ATTACH send PDN option as EHSM_ESM_PDN_OPT_CONNECTED */
            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_CONNECTED);

            CNAS_EHSM_ClearLteLocalPdnInfo(pstPdnInfo->ucCid);
        }

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_FALSE);
        CNAS_EHSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_FALSE);

        CNAS_EHSM_PdnSetupFailureHandler_Activating(pstPdnSetUpCnf->ucPdnId, pstPdnSetUpCnf->enErrorCode, &(pstPdnInfo->stApn));
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;
    pstPdnInfo   = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[pStAttachCnf->ucPdnId]);
    pstEntryMsg  = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

    if (CNAS_CTTF_EHRPD_RSLT_SUCCESS == pStAttachCnf->enAttachRslt)
    {
        /* clean the retry pdn info */
        CNAS_EHSM_InitApnRetryInfo();

        CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromAttachCnf(pstPdnInfo, pStAttachCnf);

        /* 如果此次Attach请求时用户激活自己触发的，需要给用户上报Attach Cnf结果 */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(pStAttachCnf->ucPdnId, EHSM_APS_CAUSE_SUCCESS);

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_TRUE);
        }
        else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            /* 自动触发的Initial Attach */
            if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pStAttachCnf->enAttachType)
            {
                CNAS_EHSM_SndApsPdnActivateInd(pStAttachCnf->ucPdnId);
            }

            /* LTE之前存在用户触发的数据业务，切换至EHRPD时，需要做HandOver Attach */
            if (CNAS_CTTF_EHRPD_ATTACH_TYPE_HANDOVER == pStAttachCnf->enAttachType)
            {
                /* 更新当前ehrpd的IPV6地址，刷新前缀 */
                if ((CNAS_EHSM_PDN_TYPE_IPV6 == pstPdnInfo->stPdnAddr.enPdnType)
                 || (CNAS_EHSM_PDN_TYPE_IPV4V6 == pstPdnInfo->stPdnAddr.enPdnType))
                {
                    CNAS_EHSM_SyncEhrpdIpv6PrfixWithLtePdnInfo(pStAttachCnf->ucPdnId);
                }

                CNAS_EHSM_SndApsLteHandOverToEhrpdInd(pStAttachCnf->ucPdnId, EHSM_APS_PDN_OPTION_MODIFIED);
                CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
            }

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_FALSE);
        }
        else
        {
            /* To Do */
        }

        CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_TRUE, EHSM_ESM_PDN_OPT_CONNECTED);

        CNAS_EHSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_FALSE);

        CNAS_EHSM_AttachFailureHandler_Activating(pStAttachCnf->ucPdnId, pStAttachCnf->enErrorCode, &(pstPdnInfo->stApn));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf
 功能描述  : CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF子状态下收到消
             息ID_CTTF_CNAS_EHRPD_RECONN_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SndHsmConnEstReq();

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    if (CNAS_EHSM_EHRPD_ACTIVE_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);
    }

    CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(CNAS_CTTF_EHRPD_LINK_NOT_EXISTED);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    /* 如果当前是最后一个PDN,直接发送Detach Ind */
    if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
    {
        CNAS_EHSM_SndCttfEhrpdDetachInd();
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
    }

    CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                              pstEntryMsg->ulEventType);

    CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvTiWaitRetryPdnSetup_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU     *pstAttachReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    ucPdnId     = CNAS_EHSM_GetPdnId_Activating();

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        /* airlink exist case */
        if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

            CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);
        }
        else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);
        }

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU      *pstAbortReq    = VOS_NULL_PTR;

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP);

    pstAbortReq = (CNAS_EHSM_EHSM_ABORT_REQ_STRU*)pstMsg;

    CNAS_EHSM_ProcAbortProcedure_Activating(pstAbortReq->ulEventType);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新空口链路状态 */
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    if (CNAS_EHSM_EHRPD_ACTIVE_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU         *pstRcvAbortMsg = VOS_NULL_PTR;

    pstRcvAbortMsg = (CNAS_EHSM_EHSM_ABORT_REQ_STRU *)pstMsg;

    CNAS_EHSM_ProcAbortProcedure_Activating(pstRcvAbortMsg->ulEventType);

    return VOS_TRUE;
}

VOS_UINT32 CNAS_EHSM_RcvAbortReq_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);
    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    CNAS_EHSM_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf
 功能描述  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF状态下收到消息ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg    = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* 之前已经发过Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_CONN_EST_FAIL,
                                                  pstEntryMsg->ulEventType);

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

        CNAS_EHSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf
 功能描述  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF收到消息ID_CTTF_CNAS_EHRPD_ATTACH_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf   = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        CNAS_EHSM_SndHsmDiscReq();

        /* 停止保护定时器 */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* 之前已经发过Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(pStAttachCnf->enErrorCode));
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf
 功能描述  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF收到定时器TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* 如果当前是最后一个PDN,直接发送Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                                  pstEntryMsg->ulEventType);

        if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
          ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);
        }
        else
        {
            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}


VOS_VOID CNAS_EHSM_IncreConntRetryTimes_Activating(VOS_VOID)
{
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;

    /*update conn est retry time +1*/
    pstRetryInfo = CNAS_EHSM_GetRetryInfo_Activating();

    pstRetryInfo->usCurConnEstRetryTimes++;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_ResetConntRetryTimes_Activating
 功能描述  : 重置链路Retry建链次数为0
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_ResetConntRetryTimes_Activating(VOS_VOID)
{
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;

    pstRetryInfo = CNAS_EHSM_GetRetryInfo_Activating();

    pstRetryInfo->usCurConnEstRetryTimes = 0;

    return;
}


VOS_VOID CNAS_EHSM_EstPdnFailureHandler_Activating(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause,
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid;

    ucPdnId  = CNAS_EHSM_GetPdnId_Activating();
    ucCid    = CNAS_EHSM_GetCidByPdnId(ucPdnId);

    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsReconnCnf(enCause, ucPdnId, ucCid);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsPdnActivateCnf(ucCid, enCause);

        /* 清除本地的拨号上下文信息 */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, enCause);

        /* 清除本地的拨号上下文信息 */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsLteHandOverToEhrpdInd(ucPdnId, EHSM_APS_PDN_OPTION_DEACTIVED);

        /* 清除本地的拨号上下文信息 */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);

        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
    }
    else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == ulEventType)
    {
        /* 清除本地的拨号上下文信息 */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else
    {
    }

    return;
}


EHSM_APS_CAUSE_ENUM_UINT32 CNAS_EHSM_GetAbortCauseByEventType_Activating(
    VOS_UINT32                          ulEventType
)
{

    if (CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ) == ulEventType)
    {
        return EHSM_APS_CAUSE_POWER_OFF;
    }
    else if (CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_EHRPD_SUSPEND;
    }
    else if (CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_PPP_DETACH;
    }
    else if (CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_NOT_SUPPORT_EHRPD;
    }
    else
    {
        return EHSM_APS_CAUSE_CONN_EST_FAIL;
    }

}



VOS_VOID CNAS_EHSM_ProcAbortProcedure_Activating(
    VOS_UINT32                          ulAbortEventType
)
{
    VOS_UINT32                          ulEntryEventType;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg      = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    ulEntryEventType = pstEntryMsg->ulEventType;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* 之前已经发过Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        /* 如果当前是最后一个PDN,直接发送Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }
    }

    CNAS_EHSM_EstPdnFailureHandler_Activating(CNAS_EHSM_GetAbortCauseByEventType_Activating(ulAbortEventType),
                                              ulEntryEventType);

    if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ)    == ulAbortEventType)
     || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY) == ulAbortEventType))
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
    }
    else
    {

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
    }

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_UINT8 CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode
)
{
    switch(enErrorCode)
    {
        case CNAS_CTTF_EHRPD_ERROR_CODE_GENERAL_ERROR:
        case CNAS_CTTF_EHRPD_ERROR_CODE_UNAUTHORIZED_APN:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDN_LIMIT_EXCEEDED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_NO_PGW_AVAILABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PGW_UNREACHABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PGW_REJECT:
        case CNAS_CTTF_EHRPD_ERROR_CODE_INSUFFICIENT_PARAMETERS:
        case CNAS_CTTF_EHRPD_ERROR_CODE_RESOURCE_UNAVAILABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_ADMIN_PROHIBITED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDNID_ALREADY_IN_USE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_SUBSCRIPTION_LIMITATION:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN:
        case CNAS_CTTF_EHRPD_ERROR_CODE_EMERGENCY_SERVICES_NOT_SUPPORTED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_RECONNECT_TO_THIS_APN_NOT_ALLOWED:
             return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}


VOS_VOID CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx  = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();
    ucPdnId     = CNAS_EHSM_GetPdnId_Activating();

    CNAS_EHSM_SetSessionType(EHSM_HSM_SESSION_TYPE_NULL);

    /* clean the retry pdn info */
    CNAS_EHSM_InitApnRetryInfo();

    /* 如果本轮attach是由用户激活业务触发的，需要回复激活失败 */
    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
    {
        /* 避免重复发送Attach Cnf */
        if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucInUsed)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, enCause);
        }
    }

    CNAS_EHSM_SndHsmEhrpdNotAvailableInd();

    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    CNAS_EHSM_SndLocalDetachAllReq(enCause);

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_VOID CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating
(
    VOS_UINT8                           ucCid,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    CNAS_EHSM_InitApnRetryInfo();

    CNAS_EHSM_SndApsPdnActivateCnf(ucCid, enCause);

    CNAS_EHSM_SetSessionType(EHSM_HSM_SESSION_TYPE_NULL);

    CNAS_EHSM_SndHsmEhrpdNotAvailableInd();

    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    /* 退状态机后，本地去激活 */
    CNAS_EHSM_SndLocalDetachAllReq(enCause);

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_VOID CNAS_EHSM_AttachFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
)
{
    CNAS_EHSM_CTX_STRU                                     *pstCtxAdrr   = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                                     *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                                              ucIsRejectByNW;
    VOS_UINT16                                              usMaxNoOfRetry;
    VOS_UINT8                                               ucCurrApnRetryCnt;
    CNAS_EHSM_APN_STRU                                      stApn;

    NAS_MEM_SET_S(&stApn, sizeof(CNAS_EHSM_APN_STRU), 0x00, sizeof(CNAS_EHSM_APN_STRU));
    stApn.ucApnLen = pstApn->ucApnLen;
    NAS_MEM_CPY_S(stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pstApn->aucApn, CNAS_EHSM_MAX_APN_LEN);

    pstCtxAdrr        = CNAS_EHSM_GetEhsmCtxAddr();
    pstRetryInfo      = CNAS_EHSM_GetRetryInfo_Activating();
    ucIsRejectByNW    = CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(enErrorCode);
    ucCurrApnRetryCnt = CNAS_EHSM_GetSpecialApnRetryCnt(&stApn);
    usMaxNoOfRetry    = CNAS_EHSM_GetMaxNumOfApnRetry();
    pstEntryMsg       = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if ((VOS_TRUE == ucIsRejectByNW)
     || (CNAS_CTTF_EHRPD_ERROR_CODE_TIMEROUT == enErrorCode))
    {
        /* 超过NV定制的重试次数，回落到hrpd */
        if (ucCurrApnRetryCnt >= usMaxNoOfRetry)
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }
        /*
             第一条pdn建立失败时，失败原因是NW侧的原因或VSNCP协商超时，无论intial attach还是handover attach都需要重试
             为保证 非a ）中鉴权失败的三次连续的PPP-LCP层失败  ，此处清空usLcpOtherFailRetryTimes
         */
        pstRetryInfo->usLcpOtherFailRetryTimes = 0;

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

        /* 更新一下retry apn的尝试次数 */
        CNAS_EHSM_IncreSpecialApnRetryCnt(&stApn);
        return;
    }

    /*
         6.4.2.4  eHRPD PPP-LCP 失败处理要求
             6.4.2.4.1  eHRPD 回退到 HRPD 要求
        终端选择eHRPD网络接入，如果在eHRPD PPP会话建立过程中遇到以下PPP-LCP失败：
        a)  终端收到网络侧发送的“EAP-Failure ”消息，EAP-AKA’ 鉴权失败。主要场景为网络侧在向
        终端发送含错误码（error code ）的“EAP Notify ”消息后，发送“EAP-Failure”消息。错
        误码取值范围0～16384。
        b)  非a ）中鉴权失败的三次连续的PPP-LCP层失败，失败情况包括网络侧未成功响应请求、请求
        或其它流程超时（time out ），包括鉴权请求time out 。
            注意1：VSNCP失败如网络侧未响应VSCNP请求或者VSCNP请求time out 的情况不包括在内，
        见本标准6.4.2.3  节a)中VSNCP协议部分。
            注意2：LCP配置请求（LCP-Co nfig Request ）尝试完设定次数的重传后仍失败才被认为
        是time out 。
        详见 <[华为]中国电信LTE手机终端技术要求（单卡槽）（ 2014 SX-007 ）_20140922>
    */

    /* 是LCP 协商中的EAP-Failure失败或网侧处理超时，直接回退到hrpd */
    else if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
    {
        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
        return;
    }

    /* b)  非a ）中鉴权失败的三次连续的PPP-LCP层失败 (尝试连续失败3次回落到hrpd) */
    else if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode)
    {
        if (pstRetryInfo->usLcpOtherFailRetryTimes < CNAS_EHSM_MAX_RETRY_PDN_SETUP_FOR_LCP_OTHER_FAIL)
        {
            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

            pstRetryInfo->usLcpOtherFailRetryTimes++;
            return;
        }

        /* 非a ）中鉴权失败的三次连续的PPP-LCP层失败 */
        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
        return;
    }
    else
    {
        pstRetryInfo->usLcpOtherFailRetryTimes = 0;

        /* 如果本轮attach是由用户激活业务触发的，需要回复激活失败 */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, CNAS_EHSM_MapCttfErrCode(enErrorCode));
        }

        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
    }

    return;
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_PdnSetupFailureHandler_Activating
Description     :  默认承载外的其他pdn建立失败时的处理
Input parameters:       EHSM_APS_CAUSE_ENUM_UINT32          enCause,
                        VOS_UINT32                          ulEventType,
                        VOS_UINT8                           ucPdnId
Output parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-07-23
    Author         : f00279542
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_EHSM_PdnSetupFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
)
{
    CNAS_EHSM_CTX_STRU                                     *pstCtxAdrr   = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                                     *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usMaxNoOfRetry;
    VOS_UINT8                                               ucIsRejectByNW;
    VOS_UINT8                                               ucCurrApnRetryCnt;
    CNAS_EHSM_APN_STRU                                      stApn;

    NAS_MEM_SET_S(&stApn, sizeof(CNAS_EHSM_APN_STRU), 0x00, sizeof(CNAS_EHSM_APN_STRU));
    stApn.ucApnLen = pstApn->ucApnLen;
    NAS_MEM_CPY_S(stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pstApn->aucApn, CNAS_EHSM_MAX_APN_LEN);

    pstCtxAdrr           = CNAS_EHSM_GetEhsmCtxAddr();
    pstPdnInfo           = &(pstCtxAdrr->astLocalPdnBearInfo[ucPdnId]);
    ucIsRejectByNW       = CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(enErrorCode);
    ucCurrApnRetryCnt    = CNAS_EHSM_GetSpecialApnRetryCnt(&stApn);
    usMaxNoOfRetry       = CNAS_EHSM_GetMaxNumOfApnRetry();
    pstEntryMsg          = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstRetryInfo         = CNAS_EHSM_GetRetryInfo_Activating();

    /*
        ehrpd 回退到hrpd的策略:
        一、被网络拒绝，也就是X.S0057   Table 5    Error Code values（见下图） 中的原因值和 VSNCP timeout
        1.Handover场景
        1）第一条PDN建立被网络拒绝，重试NV定制次数(默认两次)，仍然失败，回退到HRPD
        2）非第一条PDN建立被网络拒绝，不重试，直接向APS指示PDN恢复失败

        2.Initial场景
        PDN建立被网络拒绝，直接回复APS建立失败，并记录一个次数(针对该APN),不再重试。后续AP重拨，如果仍然失败，累加次数。当累积次数达到NV定制次数，而且当前没有其它建立成功的PDN时，启动回退。
        在该APN上建立成功时，清除所有累积的次数。

        补充：
        1.当某个apn累计次数达到最大值，该apn的失败计数不清，下次再重试时，不判断累计的次数，如果失败就回退到hrpd
          当一个apn激活成功时，把所有apn的计数都清除

        2.


        二、非被网络拒绝，也就是非X.S0057   Table 5    Error Code values 中的原因值，这个电信技术文档已经给出明确说明了，处理保持不变。
           本地apn去激活，清除本地资源
    */
    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
    {
        if ((VOS_TRUE == ucIsRejectByNW)
         || (CNAS_CTTF_EHRPD_ERROR_CODE_TIMEROUT == enErrorCode))
        {
            /*  建立第二条pdn时，且失败的原因值为NW的原因值或VSNCP协商超时的原因值，且是用户数据拨号时才记录retry info */
            if (ucCurrApnRetryCnt >= usMaxNoOfRetry)
            {
                CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
                return;
            }

            /* 更新retry apn的信息 */
            CNAS_EHSM_IncreSpecialApnRetryCnt(&stApn);
        }

        /* 是LCP 协商中的EAP-Failure失败或网侧处理超时，直接回退到hrpd */
        if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
        {
            CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }

        /* b)  非a ）中鉴权失败的三次连续的PPP-LCP层失败 (尝试连续失败3次回落到hrpd) */
        if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode)
        {
            if (pstRetryInfo->usLcpOtherFailRetryTimes < CNAS_EHSM_MAX_RETRY_PDN_SETUP_FOR_LCP_OTHER_FAIL)
            {
                CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
                CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

                pstRetryInfo->usLcpOtherFailRetryTimes++;
                return;
            }

            /* 非a ）中鉴权失败的三次连续的PPP-LCP层失败 */
            CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }
        CNAS_EHSM_SndApsPdnActivateCnf(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
        return;
    }

    if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == pstEntryMsg->ulEventType)
    {
        CNAS_EHSM_SndApsLteHandOverToEhrpdInd(ucPdnId, EHSM_APS_PDN_OPTION_DEACTIVED);


        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
        return;
    }
}


VOS_VOID CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(
    VOS_UINT8                           ucPdnId
)
{

    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo           = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg          = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstApsPdnActivateReq = VOS_NULL_PTR;
    APS_EHSM_PDN_ATTACH_REQ_STRU       *pstApsPdnAttachReq   = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    pstPdnInfo->ucPdnId   = ucPdnId;
    pstPdnInfo->ulEpsbId  = ucPdnId + CNAS_EHSM_MIN_EPSB_ID;

    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
    {
        pstApsPdnActivateReq = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

        pstPdnInfo->ucCid         = pstApsPdnActivateReq->ucCid;
        pstPdnInfo->enPdnType     = CNAS_EHSM_MapApsPdnTypeToEhsm(pstApsPdnActivateReq->enPdnType);

        pstPdnInfo->enAuthType    = CNAS_EHSM_MapApsAuthTypeToEhsm(pstApsPdnActivateReq->enAuthType);
        pstPdnInfo->ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnActivateReq->aucUserName);
        pstPdnInfo->ucPwdLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnActivateReq->aucPassword);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucUserName[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN, 
                      &(pstApsPdnActivateReq->aucUserName[0]), 
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucPwd[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_PASSWORD_LEN,
                      &(pstApsPdnActivateReq->aucPassword[0]), 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        /* EHSM保存编码后的APN */
        CNAS_EHSM_EncodeApn((CNAS_EHSM_APN_STRU *)&(pstApsPdnActivateReq->stApn),
                            pstPdnInfo->stApn.aucApn,
                            &pstPdnInfo->stApn.ucApnLen);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
    {
        pstApsPdnAttachReq   = (APS_EHSM_PDN_ATTACH_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

        pstPdnInfo->ucCid     = pstApsPdnAttachReq->ucCid;
        pstPdnInfo->enPdnType = CNAS_EHSM_MapApsPdnTypeToEhsm(pstApsPdnAttachReq->enPdnType);

        pstPdnInfo->enAuthType    = CNAS_EHSM_MapApsAuthTypeToEhsm(pstApsPdnAttachReq->enAuthType);
        pstPdnInfo->ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnAttachReq->aucUserName);
        pstPdnInfo->ucPwdLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnAttachReq->aucPassword);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucUserName[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN,
                      &(pstApsPdnAttachReq->aucUserName[0]), 
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucPwd[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_PASSWORD_LEN,
                      &(pstApsPdnAttachReq->aucPassword[0]), 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        /* EHSM保存编码后的APN */
        CNAS_EHSM_EncodeApn((CNAS_EHSM_APN_STRU *)&(pstApsPdnAttachReq->stApn),
                            pstPdnInfo->stApn.aucApn,
                            &pstPdnInfo->stApn.ucApnLen);
    }
    else
    {
    }

    return;
}

#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


