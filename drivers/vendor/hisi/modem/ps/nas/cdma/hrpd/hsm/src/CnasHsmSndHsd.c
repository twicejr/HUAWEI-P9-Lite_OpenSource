

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndHsd.h"
#include "CnasMain.h"
#include "CnasHsmCtx.h"
#include "CnasMntn.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_HSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_SndHsdHrpdCasStatusInd(
    HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16           enCasStatus
)
{
    HSM_HSD_CAS_STATUS_IND_STRU        *pstHsmHsdCasStatusInd   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                          ulLen;

    ulLen           = sizeof(HSM_HSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdCasStatusInd = (HSM_HSD_CAS_STATUS_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM,ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdCasStatusInd = (HSM_HSD_CAS_STATUS_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_CAS_STATUS_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdCasStatusInd)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdCasStatusInd + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdCasStatusInd,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_CAS_STATUS_IND,
                     (sizeof(HSM_HSD_CAS_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstHsmHsdCasStatusInd->enCasStatus = enCasStatus;

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdCasStatusInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdCasStatusInd);
#endif
}


VOS_VOID CNAS_HSM_SndHsdSessionNegResultInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8                     enNegResult,
    VOS_UINT8                                               ucIsNewSession,
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enHsmSessionRelType
)
{
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstHsmHsdSessionNegResultInd   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                                              ulLen;

    ulLen = sizeof(HSM_HSD_SESSION_NEG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdSessionNegResultInd = (HSM_HSD_SESSION_NEG_RESULT_IND_STRU *)
                                        PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdSessionNegResultInd = (HSM_HSD_SESSION_NEG_RESULT_IND_STRU *)
                                        CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_SESSION_NEG_RESULT_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdSessionNegResultInd)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdSessionNegResultInd + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_SESSION_NEG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_SESSION_NEG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdSessionNegResultInd,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_SESSION_NEG_RESULT_IND,
                     (sizeof(HSM_HSD_SESSION_NEG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstHsmHsdSessionNegResultInd->enNegResult                 = enNegResult;
    pstHsmHsdSessionNegResultInd->ucIsNewSession              = ucIsNewSession;
    pstHsmHsdSessionNegResultInd->enSessionRelType            = CNAS_HSM_ConvertHsmSessionRelTypeToHsdSessionRelType(enHsmSessionRelType);
    pstHsmHsdSessionNegResultInd->usOpId                      = 0;

    /* ucIsEhrpdSupport表示当前Session类型是HRPD或EHRPD，只有在NegResult为success时才有效 */
    if (CNAS_HSM_SESSION_TYPE_EHRPD == CNAS_HSM_GetNegoSessionType())
    {
        pstHsmHsdSessionNegResultInd->ucIsEhrpdSupport        = VOS_TRUE;
    }
    else
    {
        pstHsmHsdSessionNegResultInd->ucIsEhrpdSupport        = VOS_FALSE;
    }

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdSessionNegResultInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdSessionNegResultInd);
#endif
}


VOS_VOID CNAS_HSM_SndHsdStartCnf(VOS_VOID)
{
    HSM_HSD_START_CNF_STRU             *pstHsmHsdStartCnf   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                          ulLen;

    ulLen           = sizeof(HSM_HSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdStartCnf = (HSM_HSD_START_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdStartCnf = (HSM_HSD_START_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_START_CNF_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdStartCnf)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdStartCnf + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdStartCnf,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_START_CNF,
                     (sizeof(HSM_HSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdStartCnf);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdStartCnf);
#endif
}


VOS_VOID CNAS_HSM_SndHsdPowerOffCnf(VOS_VOID)
{
    HSM_HSD_POWEROFF_CNF_STRU          *pstHsmHsdPowerOffCnf   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_HSD_POWEROFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdPowerOffCnf = (HSM_HSD_POWEROFF_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdPowerOffCnf = (HSM_HSD_POWEROFF_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_POWEROFF_CNF_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdPowerOffCnf)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdPowerOffCnf + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_POWEROFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_POWEROFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdPowerOffCnf,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_POWEROFF_CNF,
                     (sizeof(HSM_HSD_POWEROFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdPowerOffCnf);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdPowerOffCnf);
#endif
}


VOS_VOID CNAS_HSM_SndHsdPowerSaveCnf(VOS_VOID)
{
    HSM_HSD_POWER_SAVE_CNF_STRU        *pstHsmHsdPowerSaveCnf   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_HSD_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdPowerSaveCnf = (HSM_HSD_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdPowerSaveCnf = (HSM_HSD_POWER_SAVE_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_POWER_SAVE_CNF_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdPowerSaveCnf)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdPowerSaveCnf + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdPowerSaveCnf,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_POWER_SAVE_CNF,
                     (sizeof(HSM_HSD_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdPowerSaveCnf);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdPowerSaveCnf);
#endif

}



VOS_VOID CNAS_HSM_SndHsdConnOpenInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enConnOpenRslt
)
{
    HSM_HSD_CONN_OPEN_IND_STRU         *pstHsmHsdConnOpenInd   = VOS_NULL_PTR;
#if defined(DMT)
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_HSD_CONN_OPEN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHsmHsdConnOpenInd = (HSM_HSD_CONN_OPEN_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstHsmHsdConnOpenInd = (HSM_HSD_CONN_OPEN_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_HSD_CONN_OPEN_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (VOS_NULL_PTR == pstHsmHsdConnOpenInd)
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstHsmHsdConnOpenInd + VOS_MSG_HEAD_LENGTH),
                  (sizeof(HSM_HSD_CONN_OPEN_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0,
                  (sizeof(HSM_HSD_CONN_OPEN_IND_STRU) - VOS_MSG_HEAD_LENGTH));
#endif

    CNAS_CFG_MSG_HDR(pstHsmHsdConnOpenInd,
                     UEPS_PID_HSM,
                     UEPS_PID_HSD,
                     ID_HSM_HSD_CONN_OPEN_IND,
                     (sizeof(HSM_HSD_CONN_OPEN_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstHsmHsdConnOpenInd->enRslt = enConnOpenRslt;

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHsmHsdConnOpenInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstHsmHsdConnOpenInd);
#endif
}


HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_ConvertHsmSessionRelTypeToHsdSessionRelType(
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enHsmSessionRelType
)
{
    HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8                 enHsdSessinRelType;

    switch (enHsmSessionRelType)
    {
        case CNAS_HSM_SESSION_RELEASE_TYPE_0:
            enHsdSessinRelType = HSM_HSD_SESSION_RELEASE_TYPE_0;
            break;

        case CNAS_HSM_SESSION_RELEASE_TYPE_A:
            enHsdSessinRelType = HSM_HSD_SESSION_RELEASE_TYPE_A;
            break;

        default:
            enHsdSessinRelType = HSM_HSD_SESSION_RELEASE_TYPE_ENUM_BUTT;
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ConvertHsmSessionRelTypeToHsdSessionRelType: unknow session rel type!");
            break;
    }

    return enHsdSessinRelType;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */












