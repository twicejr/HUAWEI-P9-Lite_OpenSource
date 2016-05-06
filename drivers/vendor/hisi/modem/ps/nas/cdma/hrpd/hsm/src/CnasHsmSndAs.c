

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndAs.h"
#include "CnasMntn.h"
#include "CnasHsmComFunc.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_AS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_SndCasHrpdScpActiveReq(
    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enActiveType,
    PS_BOOL_ENUM_UINT8                                      enEhrpdFlag
)
{

    CNAS_CAS_HRPD_SCP_ACTIVE_REQ_STRU  *pstHrpdScpActReq    = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SCP_ACTIVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHrpdScpActReq =
            (CNAS_CAS_HRPD_SCP_ACTIVE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstHrpdScpActReq)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstHrpdScpActReq + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstHrpdScpActReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HSCP,
                     ID_CNAS_CAS_HRPD_SCP_ACTIVE_REQ,
                     ulLen);

    pstHrpdScpActReq->enActiveType    = enActiveType;
    pstHrpdScpActReq->enEhrpdFlag     = enEhrpdFlag;

    /* If active type is ression restore, send previous UATI128 to SCP */
    if (CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_PRIOR_RESTORE == enActiveType)
    {
        NAS_MEM_CPY_S(pstHrpdScpActReq->aucUATI,
                      sizeof(pstHrpdScpActReq->aucUATI),
                      CNAS_HSM_GetSessionCtrlInfoAddr()->aucPrevUatiForSessionRestore,
                      CNAS_CAS_HRPD_SCP_MAX_UATI_LENGTH);

        /* 使用之后将aucPrevUatiForSessionRestoreq清空 */
        NAS_MEM_SET_S(CNAS_HSM_GetSessionCtrlInfoAddr()->aucPrevUatiForSessionRestore,
                      CNAS_HSM_UATI_OCTET_LENGTH,
                      0,
                      CNAS_HSM_UATI_OCTET_LENGTH);
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdScpActReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdScpActReq);
}


VOS_VOID CNAS_HSM_SndCasHrpdScpDeActiveReq(VOS_VOID)
{
    CNAS_CAS_HRPD_SCP_DEACTIVE_REQ_STRU                    *pstHrpdScpDeActReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SCP_DEACTIVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHrpdScpDeActReq =
            (CNAS_CAS_HRPD_SCP_DEACTIVE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstHrpdScpDeActReq)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstHrpdScpDeActReq + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstHrpdScpDeActReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HSCP,
                     ID_CNAS_CAS_HRPD_SCP_DEACTIVE_REQ,
                     ulLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdScpDeActReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdScpDeActReq);
}


VOS_VOID CNAS_HSM_SndCasHrpdConnCloseReq(VOS_VOID)
{
    CNAS_CAS_HRPD_CONN_CLOSE_REQ_STRU  *pstHrpdConnCloseReq    = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_CONN_CLOSE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHrpdConnCloseReq =
            (CNAS_CAS_HRPD_CONN_CLOSE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstHrpdConnCloseReq)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstHrpdConnCloseReq + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstHrpdConnCloseReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HALMP,
                     ID_CNAS_CAS_HRPD_CONN_CLOSE_REQ,
                     ulLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdConnCloseReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdConnCloseReq);
}


VOS_VOID CNAS_HSM_SndCasHrpdSessionSeedNtf(VOS_UINT32 ulSessionSeed)
{
    CNAS_CAS_HRPD_SESSION_SEED_NTF_STRU                    *pstHrpdSessionSeedNtf = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SESSION_SEED_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHrpdSessionSeedNtf =
            (CNAS_CAS_HRPD_SESSION_SEED_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstHrpdSessionSeedNtf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstHrpdSessionSeedNtf + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstHrpdSessionSeedNtf,
                     UEPS_PID_HSM,
                     UEPS_PID_HALMP,
                     ID_CNAS_CAS_HRPD_SESSION_SEED_NTF,
                     ulLen);

    pstHrpdSessionSeedNtf->ulSessionSeed   = ulSessionSeed;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdSessionSeedNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdSessionSeedNtf);
}




VOS_VOID CNAS_HSM_SndCasHrpdConnOpenReq(
    CNAS_CAS_HRPD_CONN_OPEN_TYPE_ENUM_UINT8                 enConnType
)
{
    CNAS_CAS_HRPD_CONN_OPEN_REQ_STRU   *pstConnOpenReq;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_CONN_OPEN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstConnOpenReq = (CNAS_CAS_HRPD_CONN_OPEN_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (CNAS_HSM_IS_NULL_PTR(pstConnOpenReq))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstConnOpenReq + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstConnOpenReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HALMP,
                     ID_CNAS_CAS_HRPD_CONN_OPEN_REQ,
                     ulLen);

    pstConnOpenReq->enOpenType = enConnType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstConnOpenReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstConnOpenReq);
}


VOS_VOID CNAS_HSM_SndCasHrpdSessionBeginNtf(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU                   *pstSessionBeginNtf;
    VOS_UINT32                                              ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSessionBeginNtf = (CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (CNAS_HSM_IS_NULL_PTR(pstSessionBeginNtf))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstSessionBeginNtf + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstSessionBeginNtf,
                     UEPS_PID_HSM,
                     UEPS_PID_HALMP,
                     ID_CNAS_CAS_HRPD_SESSION_BEGIN_NTF,
                     ulLen);

    pstSessionBeginNtf->enSessionType   = enSessionType;
    pstSessionBeginNtf->usOpId          = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSessionBeginNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSessionBeginNtf);
}


VOS_VOID CNAS_HSM_SndCasHrpdSessionEndNtf(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_END_NTF_STRU                     *pstSessionEndNtf;
    VOS_UINT32                                              ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSessionEndNtf = (CNAS_CAS_HRPD_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (CNAS_HSM_IS_NULL_PTR(pstSessionEndNtf))
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstSessionEndNtf + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstSessionEndNtf,
                     UEPS_PID_HSM,
                     UEPS_PID_HALMP,
                     ID_CNAS_CAS_HRPD_SESSION_END_NTF,
                     ulLen);

    pstSessionEndNtf->enSessionType = enSessionType;
    pstSessionEndNtf->usOpId        = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSessionEndNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSessionEndNtf);
}



VOS_VOID CNAS_HSM_SndCasHrpdSlotVoteNtf(
    CNAS_CAS_HRPD_SLOT_VOTE_ENUM_UINT16 enSlotVoteFlag
)
{
    CNAS_CAS_HRPD_SLOT_VOTE_NTF_STRU                       *pstHrpdSlotVoteNtf = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    ulLen   = sizeof(CNAS_CAS_HRPD_SLOT_VOTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHrpdSlotVoteNtf   = (CNAS_CAS_HRPD_SLOT_VOTE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstHrpdSlotVoteNtf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstHrpdSlotVoteNtf + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0x00,
                  ulLen);

    CNAS_CFG_MSG_HDR(pstHrpdSlotVoteNtf,
                     UEPS_PID_HSM,
                     UEPS_PID_HSP,
                     ID_CNAS_CAS_HRPD_SLOT_VOTE_NTF,
                     ulLen);

    pstHrpdSlotVoteNtf->enSlotVoteFlag   = enSlotVoteFlag;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdSlotVoteNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdSlotVoteNtf);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */










