
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_MNTN_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsMntn.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))


VOS_VOID TAF_XPDS_MNTN_LogFsmInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
)
{
    TAF_XPDS_MNTN_LOG_FSM_INFO_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(ulPid,
                                                            sizeof(TAF_XPDS_MNTN_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_LOG_FSM_INFO_IND;
    pstMsg->ulModuleId      = ulPid;
    pstMsg->ulCurFsmId      = ulFsmId;
    pstMsg->ulCurFsmState   = ulFsmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);

    return;
}


VOS_VOID  TAF_XPDS_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;

    pucData = (VOS_UINT8 *)PS_MEM_ALLOC(ulModuleId, ulLength);

    if (VOS_NULL_PTR == pucData)
    {
        XPDS_ERROR_LOG("CNAS_CDMA_TraceIntMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    /* 勾包消息赋值 */
    PS_MEM_CPY(pucData, pstMsg, ulLength);

    /* 消息勾包 */
    DIAG_TraceReport(pucData);

    PS_MEM_FREE(ulModuleId, pucData);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceSessionBeginIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU    *pstMsg      = VOS_NULL_PTR;
    TAF_XPDS_CFG_INFO_STRU                  *pstCagpsCfg = VOS_NULL_PTR;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();
    pstMsg      = (TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceSessionBeginIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_SESSION_BEGIN_IND;

    PS_MEM_CPY(&pstMsg->stCagpsCfg, pstCagpsCfg, sizeof(TAF_XPDS_CFG_INFO_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceSessionEndIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_SESSION_END_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_SESSION_END_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_SESSION_END_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceSessionEndIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_SESSION_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_SESSION_END_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_SESSION_END_IND;

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceReverseMsgInfoIndMsg(
    TAF_XPDS_ENCODE_RL_INFO_STRU  *pstRlMsgInfo
)
{
    TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU                *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReverseMsgInfoIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND;

    PS_MEM_CPY(&pstMsg->stRlMsgInfo, pstRlMsgInfo, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceForwardMsgInfoIndMsg(
    VOS_UINT32                          ulPdeDataMask
)
{
    TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU                *pstMsg = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU                    *pstReqRespFlag;

    pstReqRespFlag = TAF_XPDS_GetFwdlinkMsgFlagAddr();
    pstMsg         = (TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceForwardMsgInfoIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND;

    PS_MEM_CPY(&pstMsg->stReqRespFlag, pstReqRespFlag, sizeof(TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU));

    pstMsg->ulPdeDataMask = ulPdeDataMask;

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TracePilotPhaseInfoCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU                  *pstMsg       = VOS_NULL_PTR;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotInfo = VOS_NULL_PTR;

    pstPilotInfo = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);
    pstMsg       = (TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TracePilotPhaseInfoCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_PILOT_INFO_CTX_IND;

    PS_MEM_CPY(&pstMsg->stPilotInfo, pstPilotInfo, sizeof(TAF_XPDS_MNTN_PILOT_INFO_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU             *pstMsg        = VOS_NULL_PTR;
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstRspPrmInfo = VOS_NULL_PTR;

    pstRspPrmInfo = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstMsg        = (TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND;

    PS_MEM_CPY(&pstMsg->stRspPrmInfo, pstRspPrmInfo, sizeof(TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU                 *pstMsg           = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU               *pstProvAcqAssist = VOS_NULL_PTR;

    pstProvAcqAssist = &(TAF_XPDS_GetPdePublicData()->stProvAcqAssist);
    pstMsg      = (TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND;

    PS_MEM_CPY(&pstMsg->stProvAcqAssist, pstProvAcqAssist, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU               *pstMsg      = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU                *pstProvLocRsp = VOS_NULL_PTR;

    pstProvLocRsp = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);
    pstMsg        = (TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_POS_INFO_CTX_IND;

    PS_MEM_CPY(&pstMsg->stProvLocRsp, pstProvLocRsp, sizeof(TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceEphInfoCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU                    *pstMsg     = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph = VOS_NULL_PTR;

    pstProvEph = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);
    pstMsg     = (TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceEphInfoCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_EPH_INFO_CTX_IND;

    PS_MEM_CPY(&(pstMsg->stProvEph), pstProvEph, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceAlmInfoCtxIndMsg(VOS_VOID)
{
    TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU               *pstMsg     = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                 *pstProvAlm = VOS_NULL_PTR;

    pstProvAlm = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);
    pstMsg     = (TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceEphInfoCtxIndMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_ALM_INFO_CTX_IND;

    PS_MEM_CPY(&(pstMsg->stProvAlm), pstProvAlm, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceForwardPdeHeaderInfo(VOS_VOID)
{
    TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU     *pstMsg         = VOS_NULL_PTR;
    TAF_XPDS_PD_MSG_HEADER_STRU                            *pstPdMsgHeader = VOS_NULL_PTR;

    pstPdMsgHeader = &(TAF_XPDS_GetPdePublicData()->stFwdPdMsgHeader);

    pstMsg = (TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                        sizeof(TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceForwardPdeHeaderInfo:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_FORWARD_PDE_HEADER_IND;

    PS_MEM_CPY(&(pstMsg->stPdMsgHeader), pstPdMsgHeader, sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU     *pstMsg         = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                sizeof(TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReversePdeHeaderInfo:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_PDE_HEADER_IND;

    PS_MEM_CPY(&(pstMsg->stPdMsgHeader), pstPdMsgHeader, sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceReverseStartDeliverData(
    TAF_XPDS_START_DELV_DATA_STRU      *pstStartDelvData
)
{
    TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU *pstMsg         = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                sizeof(TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReverseStartDeliverData:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND;

    PS_MEM_CPY(&(pstMsg->stStartDelvData), pstStartDelvData, sizeof(TAF_XPDS_START_DELV_DATA_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceReverseMpcStartPosReq(
    TAF_XPDS_MPC_START_POS_REQ_STRU    *pstStartPosReq
)
{
    TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU *pstMsg         = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                sizeof(TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReverseMpcStartPosReq:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND;

    PS_MEM_CPY(&(pstMsg->stStartPosReq), pstStartPosReq, sizeof(TAF_XPDS_MPC_START_POS_REQ_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceReverseMpcPosReportReq(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
)
{
    TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU *pstMsg         = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                        sizeof(TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReverseMpcPosReportReq:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND;

    PS_MEM_CPY(&(pstMsg->stPosReportReq), pstPosReportReq, sizeof(TAF_XPDS_MPC_POS_REPORT_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}



VOS_VOID TAF_XPDS_MNTN_TraceReversePdeRejRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU   *pstRejInfo
)
{
    TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU   *pstMsg         = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                sizeof(TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_MNTN_TraceReversePdeRejRsp:ERROR:Alloc Mem Fail!");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XPDS;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->ulLength        = sizeof(TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND;

    PS_MEM_CPY(&(pstMsg->stRejInfo), pstRejInfo, sizeof(TAF_XPDS_REVLINK_RSP_REJECT_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

