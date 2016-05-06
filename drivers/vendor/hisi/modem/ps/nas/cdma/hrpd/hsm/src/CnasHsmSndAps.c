

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndAps.h"
#include "CnasHsmCtx.h"
#include "CnasHsmSndHlu.h"
#include "hsm_aps_pif.h"
#include "hsm_hlu_pif.h"
#include "CnasHsmComFunc.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "CnasCcb.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/


VOS_VOID CNAS_HSM_SndApsOrigCnf(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enConnOpenIndRslt
)
{
    HSM_APS_ORIG_CNF_STRU              *pstApsOrigCnfMsg;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_ORIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsOrigCnfMsg = (HSM_APS_ORIG_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsOrigCnfMsg))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsOrigCnfMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsOrigCnfMsg,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_ORIG_CNF,
                     ulLen);

    pstApsOrigCnfMsg->enResult = enConnOpenIndRslt;
    pstApsOrigCnfMsg->ucCallId = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsOrigCnfMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsOrigCnfMsg);

    return;
}



VOS_VOID CNAS_HSM_SndApsConnInd(
    VOS_UINT8                           ucCallId
)
{
    HSM_APS_CONNECT_IND_STRU           *pstApsConnIndMsg;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsConnIndMsg = (HSM_APS_CONNECT_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsConnIndMsg))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsConnIndMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsConnIndMsg,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_CONNECT_IND,
                     ulLen);

    pstApsConnIndMsg->ucCallId = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsConnIndMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsConnIndMsg);

    return;
}



VOS_VOID CNAS_HSM_SndApsDiscCnf(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enCause
)
{
    HSM_APS_DISC_CNF_STRU              *pstApsDiscCnfMsg;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsDiscCnfMsg = (HSM_APS_DISC_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsDiscCnfMsg))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsDiscCnfMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsDiscCnfMsg,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_DISC_CNF,
                     ulLen);

    pstApsDiscCnfMsg->ucCallId = ucCallId;

    pstApsDiscCnfMsg->enCause  = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsDiscCnfMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsDiscCnfMsg);

    return;
}



VOS_VOID CNAS_HSM_SndApsDiscInd(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enCause
)
{
    HSM_APS_DISC_IND_STRU              *pstApsDiscIndMsg;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsDiscIndMsg = (HSM_APS_DISC_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsDiscIndMsg))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsDiscIndMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsDiscIndMsg,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_DISC_IND,
                     ulLen);

    pstApsDiscIndMsg->ucCallId = ucCallId;
    pstApsDiscIndMsg->enCause  = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsDiscIndMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsDiscIndMsg);
}



VOS_VOID CNAS_HSM_SndApsHandOffCnf(
    HSM_APS_CAUSE_ENUM_UINT32           enCause
)
{
    HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU          *pstApsHandOffCnf;
    VOS_UINT32                                    ulLen;

    ulLen = sizeof(HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsHandOffCnf = (HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsHandOffCnf))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsHandOffCnf + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsHandOffCnf,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF,
                     ulLen);

    pstApsHandOffCnf->ulCause = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsHandOffCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsHandOffCnf);
    return;
}



VOS_VOID CNAS_HSM_SndApsLocChngdInd(
    CNAS_HSM_CONST  HLU_HSM_LOC_CHANGED_IND_STRU           *pstHluLocChngMsg
)
{
    HSM_APS_LOC_CHANGED_IND_STRU       *pstApsLocChngMsg;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_LOC_CHANGED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstApsLocChngMsg = (HSM_APS_LOC_CHANGED_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstApsLocChngMsg))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstApsLocChngMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstApsLocChngMsg,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_LOC_CHANGED_IND,
                     ulLen);

    pstApsLocChngMsg->usSid       = pstHluLocChngMsg->usSid;
    pstApsLocChngMsg->usNid       = pstHluLocChngMsg->usNid;
    pstApsLocChngMsg->ucPktZoneId = pstHluLocChngMsg->ucPktZoneId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstApsLocChngMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstApsLocChngMsg);

    return;
}


VOS_VOID CNAS_HSM_SndApsHrpdAvailableInd(VOS_VOID)
{
    HSM_APS_HRPD_AVAILABLE_IND_STRU    *pstAvailableInd;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_APS_HRPD_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstAvailableInd = (HSM_APS_HRPD_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
    if (CNAS_HSM_IS_NULL_PTR(pstAvailableInd))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstAvailableInd + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstAvailableInd,
                     UEPS_PID_HSM,
                     CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF),
                     ID_HSM_APS_HRPD_AVAILABLE_IND,
                     ulLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU *)pstAvailableInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstAvailableInd);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */











