/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluMain.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : HLU消息处理主文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasHluMain.h"
#include "CnasHluComm.h"
#include "CnasHluSndFsig.h"
#include "CnasHluSndHsm.h"
#include "CnasMntn.h"

#include "CnasHluProcNvim.h"

#include "cnas_cttf_hrpd_pa_pif.h"

#include "CnasCcb.h"

#include "CnasHluSndAs.h"
#include "Nas_Mem.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HLU_HndlHsmHandoffReq(
    HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstHsmHandOffReq
)
{
    CNAS_HLU_MSG_TX_OPTION_INFO         stMsgTxInfo;
    CNAS_HLU_LOC_VALUE_STRU             stHandOffLocVal;

    if (CNAS_HLU_RAN_HANDOFF_IS_SET == CNAS_HLU_GetRANHandoff())
    {
        /* 向接入层发送保护请求 */
        CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

        CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);

        /* 设置HandOff标记 */
        CNAS_HLU_SetHandOffFlg(VOS_TRUE);


        /* SNP_DATA_REQ msg transmission info.  */
        stMsgTxInfo.enChannelType  = CTTF_HRPD_CHANNEL_AC_OR_RTC;
        stMsgTxInfo.enDeliveryType = CTTF_HRPD_DELIVERY_TYPE_RELIABLE;
        stMsgTxInfo.enAddressType  = CTTF_HRPD_ADDRESS_UNICAST;
        stMsgTxInfo.ucPriority     = CNAS_HLU_LOC_MSG_PRIORITY;

        /* Check and fill HANDOFF msg details received from AT. */
        if (CNAS_HLU_IS_EQUAL(CNAS_HLU_SID_INVALID, pstHsmHandOffReq->usSid)
         || CNAS_HLU_IS_EQUAL(CNAS_HLU_NID_INVALID, pstHsmHandOffReq->usNid)
         || CNAS_HLU_IS_EQUAL(CNAS_HLU_PACKET_ZONE_ID_INVALID, pstHsmHandOffReq->ucPktZoneId))
        {
            CNAS_WARNING_LOG3(UEPS_PID_HLU,"CNAS_HLU_HndlHsmHandoffReq:Invalid "
                              "Location value received from AT. HLU location "
                              "values will be used in HandOff.",
                              pstHsmHandOffReq->usSid,
                              pstHsmHandOffReq->usNid,
                              pstHsmHandOffReq->ucPktZoneId);

            CNAS_HLU_SendLocNotification(&stMsgTxInfo, VOS_TRUE, VOS_NULL_PTR);
        }
        else
        {
            stHandOffLocVal.usSID          = pstHsmHandOffReq->usSid;
            stHandOffLocVal.usNID          = pstHsmHandOffReq->usNid;
            stHandOffLocVal.ucPacketZoneID = pstHsmHandOffReq->ucPktZoneId;

            /* Send notification mesage to FSIG */
            CNAS_HLU_SendLocNotification(&stMsgTxInfo, VOS_TRUE, &stHandOffLocVal);

            /* When g_bCnasRANHandoff is enabled, CNAS_HLU_SndHsmHandoffCnf will be
               invoked in CNAS_HLU_DispatchFsigMsg. */
        }
    }
    else
    {
        CNAS_HLU_SndHsmHandoffCnf(CNAS_HLU_HSM_HANDOFF_UNSOLICIT_NOT_ALLOWED);

        CNAS_ERROR_LOG1(UEPS_PID_HLU, "CNAS_HLU_HndlHsmHandoffReq:" \
                                     "AT not allowed to send LocationNotification "
                                     "in unsolicited manner."
                                     "RANHandoff is disabled.",
                                     CNAS_HLU_GetRANHandoff());


    }

    return;
}



VOS_VOID CNAS_HLU_HndlHsmSessChngInd(
    HSM_HLU_SESSION_CHANGED_IND_STRU   *pstHsmSessChngInd
)
{
    CNAS_HLU_MSG_TX_OPTION_INFO         stMsgTxInfo;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     ulPrevDataMode;
    HSM_HLU_SESSION_RAT_MODE_ENUM_UINT8 ulCurrDataMode;

    ulCurrDataMode = pstHsmSessChngInd->enRatMode;
    ulPrevDataMode = CNAS_CCB_GetPrevPsRatType();

    /* Check the cause of session change - this is judged and handled in HSM */
    if ((CNAS_HLU_RAN_HANDOFF_IS_SET == CNAS_HLU_GetRANHandoff())
     && (((CNAS_CCB_PS_RATTYPE_EHRPD == ulPrevDataMode) && (HSM_HLU_SESSION_RAT_MODE_EHRPD == ulCurrDataMode))
      || ((CNAS_CCB_PS_RATTYPE_HRPD == ulPrevDataMode) && (HSM_HLU_SESSION_RAT_MODE_HRPD == ulCurrDataMode))
      || ((CNAS_CCB_PS_RATTYPE_1X == ulPrevDataMode) && (HSM_HLU_SESSION_RAT_MODE_EHRPD == ulCurrDataMode))))
    {
        /* Send notification mesage to FSIG */
        stMsgTxInfo.enChannelType       = CTTF_HRPD_CHANNEL_AC_OR_RTC; /* need to confirm */
        stMsgTxInfo.enDeliveryType      = CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT; /* need to confirm */
        stMsgTxInfo.enAddressType       = CTTF_HRPD_ADDRESS_UNICAST;
        stMsgTxInfo.ucPriority          = CNAS_HLU_LOC_MSG_PRIORITY;

        /* 向接入层发送保护请求 */
        CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

        CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);

        CNAS_HLU_SendLocNotification(&stMsgTxInfo, VOS_FALSE, VOS_NULL_PTR);

    }
    else
    {
        CNAS_ERROR_LOG1(UEPS_PID_HLU,
                        "CNAS_HLU_HndlHsmSessChngInd:Location update procedures could not be performed,RANHandoff value is ",
                        CNAS_HLU_GetRANHandoff());
    }

    return;
}




VOS_VOID CNAS_HLU_HndlPowerOnReq(VOS_VOID)
{
    CNAS_HLU_SetHandOffFlg(VOS_FALSE);

    CNAS_HLU_GetLocCtxAddr()->ucOpId = 0;

    /* Read Last stored LocationValue from NV */
    CNAS_HLU_ReadLocInfoNvim();

    /* Read Last stored StorageBLOB from NV */
    CNAS_HLU_ReadStrgBlobNvim();


    /* Return Start confirm to HSD */
    CNAS_HLU_SndHsdStartCnf();

    return;
}


VOS_VOID CNAS_HLU_HndlPowerOffReq(VOS_VOID)
{
    CNAS_HLU_SetHandOffFlg(VOS_FALSE);

    CNAS_HLU_GetLocCtxAddr()->ucOpId = 0;

    CNAS_HLU_StopTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF);

    CNAS_HLU_SndHsdPowerOffCnf();

    return;
}


VOS_VOID CNAS_HLU_HndlRpaCommitInd(
    CTTF_CNAS_HRPD_PA_COMMITTED_IND_STRU *pstCommitInd
)
{
    CNAS_HLU_SetProtocolType(pstCommitInd->enProtocolType);

    if ((pstCommitInd->ucRanHandoff != CNAS_HLU_RAN_HANDOFF_IS_SET)
     && (pstCommitInd->ucRanHandoff != CNAS_HLU_RAN_HANDOFF_IS_NOT_SET))
    {
        CNAS_ERROR_LOG1(UEPS_PID_HLU,
                        "CNAS_HLU_HndlRpaCommitInd:Invalid ucRanHandoff attribute value ",
                        pstCommitInd->ucRanHandoff);
        return;
    }

    CNAS_HLU_SetRANHandoff(pstCommitInd->ucRanHandoff);

    return;
}


VOS_VOID CNAS_HLU_DispatchFsigMsg(
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstSnpDataInd;
    CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU   *pstFsigAckMsg;

    CNAS_HLU_HSM_1X_TO_HRPD_HANDOFF_RSLT_ENUM_UINT32        enHandOffRslt;
    VOS_UINT8                                               ucOpId;
    VOS_UINT16                                              usMsgName;

    usMsgName = *((VOS_UINT16 *)(pstMsg->aucValue));

    switch (usMsgName)
    {
        case ID_CTTF_CNAS_HRPD_SNP_DATA_IND:
        {

            pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU *)pstMsg;

            if (CTTF_HRPD_SNP_PROTOCOL_TYPE_BUTT == CNAS_HLU_GetProtocolType())
            {
                CNAS_HLU_SetProtocolType(pstSnpDataInd->enProtocolType);
            }

            /* Validate Instance type. */
            if (pstSnpDataInd->enInstanceType != CTTF_HRPD_INSTANCE_INUSE)
            {
                CNAS_ERROR_LOG1(UEPS_PID_HLU,
                                "CNAS_HLU_DispatchFsigMsg: Invalid instance type received.",
                                pstSnpDataInd->enInstanceType);
                return;
            }
            /* Decode and store the location details, if received.*/
            CNAS_HLU_ProcSnpDataInd(&pstSnpDataInd->stMsgData);

            break;
        }
        case ID_CTTF_CNAS_HRPD_SNP_DATA_CNF:
        {
            CNAS_HLU_StopTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF);

            /* 释放资源申请 */
            CNAS_HLU_SndCasEndSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* 如果不在HandOff流程中,不需要回复HandOffRslt */
            if (VOS_FALSE == CNAS_HLU_GetHandOffFlg())
            {
                break;
            }

            ucOpId       = CNAS_HLU_GetHandOffOpId();
            pstFsigAckMsg = (CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU *)pstMsg;

            /* AT will not send HANDOFF_REQ again untill unless it receives
               the HANDOFF_CNF for last HANDOFF_REQ sent.
               Therefor, at any point of time, ucMsgId will correspond to
               last HANDOFF_REQ sent to FSIG and for which AT awaits the
               HANDOFF_CNF msg. */
            if (ucOpId == pstFsigAckMsg->usOpId)
            {
                enHandOffRslt = CNAS_HLU_GetHandOffRslt(pstFsigAckMsg->enRslt);

                /* Send HandOffCNF to HSM. */
                CNAS_HLU_SndHsmHandoffCnf(enHandOffRslt);
            }
            else
            {
                /* Discard the received ack msg from FSIG, It does not belong
                   to last HANDOFF reqest sent to FSIG. */
            }


            CNAS_HLU_SetHandOffFlg(VOS_FALSE);

            break;
        }
        default:
        {
            CNAS_ERROR_LOG1(UEPS_PID_HLU,
                            "CNAS_HLU_ProcSnpDataInd: Incorrect FSIG msg received.",
                            usMsgName);


            break;
        }
    }

    return;
}



VOS_VOID CNAS_HLU_DispatchRpaMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                                        *pstRpaMsg;
    CTTF_CNAS_HRPD_PA_COMMITTED_IND_STRU                   *pstCommitInd;

    pstRpaMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstRpaMsg->ulMsgName)
    {
        case ID_CTTF_CNAS_HRPD_PA_COMMITTED_IND:
        {
            pstCommitInd = (CTTF_CNAS_HRPD_PA_COMMITTED_IND_STRU *)pstMsg;

            CNAS_HLU_HndlRpaCommitInd(pstCommitInd);
            break;
        }
        default:
        {
            CNAS_ERROR_LOG1(UEPS_PID_HLU,
                            "CNAS_HLU_DispatchRpaMsg: Incorrect FSIG msg received.",
                            pstRpaMsg->ulMsgName);
            break;
        }
    }

    return;
}



VOS_VOID  CNAS_HLU_DispatchHsdMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstHdrMsg;

    pstHdrMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstHdrMsg->ulMsgName)
    {
        case ID_HSD_HLU_START_REQ:
            /* HLU power on request.
               Return typr of CNAS_HLU_HandlePowerOnReq is not handled currently
               as there is no operation happening inside it.
               Return check can be added in future, if needed.
            */
            CNAS_HLU_HndlPowerOnReq();
            break;

        case ID_HSD_HLU_POWER_OFF_REQ:
            /* HLU power on request.
               Return typr of CNAS_HLU_HandlePowerOffReq is not handled currently
               as there is no operation happening inside it.
               Return check can be added in future, if needed.
            */
            CNAS_HLU_HndlPowerOffReq();
            break;

        default:
            CNAS_ERROR_LOG1(UEPS_PID_HLU,
                            "CNAS_HLU_DispatchHsdMsg: Incorrect FSIG msg received.",
                            pstHdrMsg->ulMsgName);
            break;
    }

    return;
}


VOS_VOID  CNAS_HLU_DispatchHsmMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstHsmMsg;

    HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstHsmHandOffReq;

    HSM_HLU_SESSION_CHANGED_IND_STRU   *pstHsmSessChngInd;


    pstHsmMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstHsmMsg->ulMsgName)
    {
        case ID_HSM_HLU_SESSION_CHANGED_IND:
        {
            pstHsmSessChngInd = (HSM_HLU_SESSION_CHANGED_IND_STRU *)pstMsg;

            /* Session change indication */
            CNAS_HLU_HndlHsmSessChngInd(pstHsmSessChngInd);


            break;
        }
        case ID_HSM_HLU_1X_TO_HRPD_HANDOFF_REQ:
        {
            /* 1x DO handoff request */
            pstHsmHandOffReq = (HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU *)pstMsg;

            CNAS_HLU_HndlHsmHandoffReq(pstHsmHandOffReq);


            break;
        }
        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HLU_DisPatchTimerMsg
 功能描述  : 处理TIMER超时
 输入参数  : struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HLU_DisPatchTimerMsg(
    struct MsgCB                       *pstMsg
)
{
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    CNAS_HLU_StopTimer(pstRcvTimerMsg->ulName);

    switch (pstRcvTimerMsg->ulName)
    {
        case TI_CNAS_HLU_WAIT_SIG_DATA_CNF:
            /* 释放资源 */
            CNAS_HLU_SndCasEndSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* HANDOFF流程，需要给HSM返回结果 */
            if (VOS_TRUE == CNAS_HLU_GetHandOffFlg())
            {
                CNAS_HLU_SndHsmHandoffCnf(CNAS_HLU_HSM_HANDOFF_FAILURE);
            }

            break;
        default:
            break;
    }

    return;
}

VOS_VOID  CNAS_HLU_DispatchMsg(
    struct MsgCB                       *pstMsg
)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    switch (pstMsg->ulSenderPid)
    {
        case UEPS_PID_HSD:
            CNAS_HLU_DispatchHsdMsg(pstMsg);
            break;

        case UEPS_PID_HSM:
            CNAS_HLU_DispatchHsmMsg(pstMsg);
            break;

        case CTTF_PID_HRPD_SIG:
            CNAS_HLU_DispatchFsigMsg(pstMsg);
            break;

        case CTTF_PID_HRPD_RPA:
            CNAS_HLU_DispatchRpaMsg(pstMsg);
            break;


        case VOS_PID_TIMER:
            CNAS_HLU_DisPatchTimerMsg(pstMsg);
            break;
        default:
            break;
    }

    return;
}



VOS_UINT32  CNAS_HLU_InitTask(VOS_VOID)
{
    /* Init global variable */
    NAS_MEM_SET_S((VOS_VOID *)(CNAS_HLU_GetLocCtxAddr()), sizeof(CNAS_HLU_CTX_STRU), 0, sizeof(CNAS_HLU_CTX_STRU));

    CNAS_HLU_SetRANHandoff(0);
    CNAS_HLU_SetProtocolType(CTTF_HRPD_SNP_PROTOCOL_TYPE_BUTT);


    return VOS_OK;
}


VOS_UINT32 CNAS_HLU_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            CNAS_HLU_InitTask();
            break;

        case VOS_IP_INITIAL:
        case VOS_IP_FARMALLOC:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




