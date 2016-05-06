

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndHlu.h"
#include "CnasMntn.h"
#include "hsm_hlu_pif.h"
#include "CnasHsmCtx.h"
#include "CnasMain.h"
#include "PsCommonDef.h"
#include "CnasHsmComFunc.h"
#include "v_msg.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_HLU_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/




VOS_VOID CNAS_HSM_SndHluHandOffReq(
    CNAS_HSM_CONST APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU          *pstApsHandOffReq
)
{
    HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstHluHandOffReq;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstHluHandOffReq = (HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    pstHluHandOffReq  = (HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM,
                                        sizeof(HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU));
#endif
    if (CNAS_HSM_IS_NULL_PTR(pstHluHandOffReq))
    {
        return;
    }

    /* Modified by w00176964 for CNASÄÚ´æ²Ã¼ô, 2015-9-17, begin */
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHluHandOffReq + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);
    /* Modified by w00176964 for CNASÄÚ´æ²Ã¼ô, 2015-9-17, end */

    CNAS_CFG_MSG_HDR(pstHluHandOffReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HLU,
                     ID_HSM_HLU_1X_TO_HRPD_HANDOFF_REQ,
                     ulLen);

    pstHluHandOffReq->usSid       = pstApsHandOffReq->usSid;
    pstHluHandOffReq->usNid       = pstApsHandOffReq->usNid;
    pstHluHandOffReq->ucPktZoneId = pstApsHandOffReq->ucPktZoneId;

#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHluHandOffReq);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHluHandOffReq);
#endif
}


VOS_VOID CNAS_HSM_SndHluSessionChangedInd(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType
)
{
    HSM_HLU_SESSION_CHANGED_IND_STRU                        *pstSessionChangedInd;
    VOS_UINT32                                              ulLen;

    ulLen = sizeof(HSM_HLU_SESSION_CHANGED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstSessionChangedInd = (HSM_HLU_SESSION_CHANGED_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    pstSessionChangedInd  = (HSM_HLU_SESSION_CHANGED_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM,
                                        sizeof(HSM_HLU_SESSION_CHANGED_IND_STRU));
#endif

    if (VOS_NULL_PTR == pstSessionChangedInd)
    {
        return;
    }

/* Modified by w00176964 for CNASÄÚ´æ²Ã¼ô, 2015-9-17, begin */
    NAS_MEM_SET_S(((VOS_UINT8 *)pstSessionChangedInd + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);
/* Modified by w00176964 for CNASÄÚ´æ²Ã¼ô, 2015-9-17, end */

    CNAS_CFG_MSG_HDR(pstSessionChangedInd,
                     UEPS_PID_HSM,
                     UEPS_PID_HLU,
                     ID_HSM_HLU_SESSION_CHANGED_IND,
                     ulLen);

    pstSessionChangedInd->enRatMode = CNAS_HSM_ConvertHsmSessionTypeToHluSessionRatMode(enSessionType);

#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSessionChangedInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstSessionChangedInd);
#endif
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */











