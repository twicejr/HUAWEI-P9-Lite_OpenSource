

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "vos.h"
#include "VosPidDef.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmCtx.h"
#include "CnasMntn.h"
#include "CnasHsmComFunc.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */


VOS_VOID CNAS_HSM_SndInternalUATIReq(
    CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8                    enTriggerReason
)
{
    CNAS_HSM_HSM_UATI_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_UATI_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_UATI_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_UATI_REQ_STRU), 0, sizeof(CNAS_HSM_HSM_UATI_REQ_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_UATI_REQ,
                     (sizeof(CNAS_HSM_HSM_UATI_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->enTriggerReason = enTriggerReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


/* Added session active reason as input parameter */
VOS_VOID CNAS_HSM_SndInternalSessionActiveReq(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU), 0, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SESSION_ACTIVE_REQ,
                     sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId = 0;

    pstMsg->enSessionActiveReason = enSessionActiveReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}



VOS_VOID CNAS_HSM_SndInternalSessionDeactiveReq(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
)
{
    CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU), 0, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SESSION_DEACTIVE_REQ,
                     sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId               = 0;
    pstMsg->enSessionDeactReason = enSessionDeactReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}


VOS_VOID CNAS_HSM_SndInternalUATIRequestResultInd(
    CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8                 enRslt,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enFailReason
)
{
    CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND,
                     sizeof(CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId       = 0;
    pstMsg->enRslt       = enRslt;
    pstMsg->enFailReason = enFailReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}



VOS_VOID CNAS_HSM_SndInternalSessionActiveResultInd(
    CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8               enRslt,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enFailReason
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND,
                     sizeof(CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId                = 0;
    pstMsg->enRslt                = enRslt;
    pstMsg->enFailReason          = enFailReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}


VOS_VOID CNAS_HSM_SndInternalSessionDeactiveResultInd(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
)
{
    CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND,
                     sizeof(CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId               = 0;
    pstMsg->enSessionDeactReason = enSessionDeactReason;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}




VOS_VOID CNAS_HSM_SndInternalSwitchOnReq(VOS_VOID)
{
    CNAS_HSM_HSM_READ_SWITCH_ON_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_READ_SWITCH_ON_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_READ_SWITCH_ON_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_READ_SWITCH_ON_STRU), 0, sizeof(CNAS_HSM_HSM_READ_SWITCH_ON_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SWITCH_ON_REQ,
                     sizeof(CNAS_HSM_HSM_READ_SWITCH_ON_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId = 0;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}



VOS_VOID CNAS_HSM_SndInternalSwitchOnResultInd(VOS_VOID)
{
    CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SWITCH_ON_RESULT_IND,
                     sizeof(CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId = 0;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}



VOS_VOID CNAS_HSM_SndInternalSessionCloseInd(
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM_UINT8    enScene,
    CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO                     *pstSessionNegRsltInfo
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM,
                                            sizeof(CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU), 0, sizeof(CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,
                     sizeof(CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId                = 0;
    pstMsg->enScene               = enScene;

    if (VOS_NULL_PTR != pstSessionNegRsltInfo)
    {
        NAS_MEM_CPY_S(&(pstMsg->stSessionNegRsltInfo),
                      sizeof(pstMsg->stSessionNegRsltInfo),
                      pstSessionNegRsltInfo,
                      sizeof(CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO));
    }

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}




VOS_VOID CNAS_HSM_SndInternalConnMnmtReq(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8           enTriggerScene
)
{
    CNAS_HSM_HSM_CONN_MNMT_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_CONN_MNMT_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_CONN_MNMT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_CONN_MNMT_REQ_STRU), 0, sizeof(CNAS_HSM_HSM_CONN_MNMT_REQ_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_CONN_MNMT_REQ,
                     (sizeof(CNAS_HSM_HSM_CONN_MNMT_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->enTriggerScene = enTriggerScene;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}



VOS_VOID CNAS_HSM_SndInternalConnMnmtResultInd(
    CNAS_HSM_CONN_MNMT_RESULT_ENUM_UINT8                    enRslt,
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene
)
{
    CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_CONN_MNMT_RESULT_IND,
                     sizeof(CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->usOpId              = 0;
    pstMsg->enRslt              = enRslt;
    pstMsg->enTriggerScene      = enTriggerScene;

    CNAS_HSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg
 功能描述  : 构造hsm hrpd pa rat mode ntf 消息
 输入参数  : CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstCasHrpdPaRatModeNtf
 输出参数  : CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                 *pstHsmHrpdPaRatModeNtf
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月15日
    作    者   : y00307564
    修改内容   : 新生成函数，调用者保证收到的ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF中的enPaMode不为butt

*****************************************************************************/
VOS_VOID CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg(
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstCasHrpdPaRatModeNtf,
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                 *pstHsmHrpdPaRatModeNtf
)
{
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstCasHrpdPaRatModeNtf->enPaMode);
    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg receive the invalid session type--BUTT");
    }

    NAS_MEM_SET_S(pstHsmHrpdPaRatModeNtf, sizeof(CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU), 0x00, sizeof(CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU));

    CNAS_CFG_MSG_HDR(pstHsmHrpdPaRatModeNtf,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF,
                     sizeof(CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstHsmHrpdPaRatModeNtf->usOpId              = pstCasHrpdPaRatModeNtf->usOpId;
    pstHsmHrpdPaRatModeNtf->enSessionType       = enSessionType;

    return;
}


/*lint -restore*/



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




