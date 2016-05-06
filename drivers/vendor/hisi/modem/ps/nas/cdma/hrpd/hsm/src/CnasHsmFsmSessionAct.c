

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmSessionAct.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmCtx.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmSndAs.h"
#include "CnasHsmSndTtf.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
#include "CnasMntn.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmSndRrm.h"

#include "CnasHsmSndEhsm.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmDecode.h"
#include "CnasHsmFsmUatiRequest.h"
#include "CnasHsmProcNvim.h"

#include "CnasMntn.h"
#include "NasOmInterface.h"
#include "CnasHsmMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_SESSION_ACT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_ACT_FAIL_REASON_STRU g_astHsmScpFailReasonMapSessionActFailReasonTbl[] =
{
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_FAILURE,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NEG_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_EXPIRED,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_AN_EXP,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_FAIL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_FAIL,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_GENERAL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_NW_BUSY,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_AUTH_BILL_FAIL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_PREF_CHAN_NOT_AVAIL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
    },


    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_PERSONALITY_INVALID,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_PERS_INVALID,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_RSP_EXPIRED,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_RSP_EXP,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_MSG_FAIL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_MSG_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_GAUP_FAIL,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_AN_GAUP_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_IRAT_TO_LTE,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_IRAT_TO_LTE,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF,
        CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NO_RF,
    },
};

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_QuitFsmScpActReq(
    CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8               enRslt,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enFailReason
)
{
    CNAS_HSM_InitSessionActiveFsmCtx(CNAS_HSM_GetSessionActiveFsmCtxAddr());

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_VACANT);

    CNAS_HSM_SndInternalSessionActiveResultInd(enRslt, enFailReason);

    return;
}


CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8 CNAS_HSM_GetScpActivationType(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enActiveReason
)
{
    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enScpActType;

    enScpActType = CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_NEG;

    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == enActiveReason)
    {
        enScpActType = CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_RECOVERY;
    }
    else if (CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_SYS_ACQ_SUBNET_CHANGE == CNAS_HSM_GetLatestSessionDeactReason())
    {
        /* 搜到网之后AMP判断失败，进行会话恢复流程 */
        enScpActType = CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_PRIOR_RESTORE;
    }
    else
    {
        enScpActType = CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_NEG;
    }

    return enScpActType;
}


PS_BOOL_ENUM_UINT8 CNAS_HSM_GetEhrpdFlag(
    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enScpActType
)
{
    PS_BOOL_ENUM_UINT8                                      enEhrpdFlag;

    if (CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_RECOVERY == enScpActType)
    {
        if (CNAS_HSM_SESSION_TYPE_EHRPD == CNAS_HSM_GetLastSessionType())
        {
            enEhrpdFlag = PS_TRUE;
        }
        else
        {
            enEhrpdFlag = PS_FALSE;
        }
    }
    else if (CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD == CNAS_HSM_GetLatestSessionDeactReason())
    {
        /* session close reason is fallback process*/
        enEhrpdFlag = PS_FALSE;
    }
    else
    {
        /* keep session type*/
        if (VOS_TRUE == CNAS_HSM_IsCurrentCapSupportEhrpd())
        {
            enEhrpdFlag = PS_TRUE;
        }
        else
        {
            enEhrpdFlag = PS_FALSE;
        }
    }

    return enEhrpdFlag;
}


VOS_UINT32 CNAS_HSM_RcvInterSessionActiveReq_SessionAct_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU                   *pstSessionActiveReq;
    PS_BOOL_ENUM_UINT8                                      enEhrpdFlag;

    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enScpActType;

    pstSessionActiveReq = (CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU *)pstMsg;

    CNAS_HSM_SetSessionActiveReason_SessionActive(pstSessionActiveReq->enSessionActiveReason);

    enScpActType = CNAS_HSM_GetScpActivationType(pstSessionActiveReq->enSessionActiveReason);

    if (CNAS_HSM_SESSION_TYPE_EHRPD == CNAS_HSM_GetReqSessionTypeForRetry())
    {
        enEhrpdFlag = PS_TRUE;
    }
    else if (CNAS_HSM_SESSION_TYPE_HRPD == CNAS_HSM_GetReqSessionTypeForRetry())
    {
        enEhrpdFlag = PS_FALSE;
    }
    /* 如果CNAS_HSM_GetReqSessionTypeForRetry()返回BUTT，说明不是重试流程 */
    else
    {
        enEhrpdFlag = CNAS_HSM_GetEhrpdFlag(enScpActType);
    }

    if (PS_TRUE == enEhrpdFlag)
    {
        CNAS_HSM_SetReqSessionType(CNAS_HSM_SESSION_TYPE_EHRPD);

        CNAS_HSM_SetReqSessionTypeForRetry(CNAS_HSM_SESSION_TYPE_EHRPD);
    }
    else
    {
        CNAS_HSM_SetReqSessionType(CNAS_HSM_SESSION_TYPE_HRPD);

        CNAS_HSM_SetReqSessionTypeForRetry(CNAS_HSM_SESSION_TYPE_HRPD);
    }

    CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_BUTT);

    /* Send the SCP Active Req to CAS */
    CNAS_HSM_SndCasHrpdScpActiveReq(enScpActType, enEhrpdFlag);

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF,
                        TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* session recovery过程中收到power off；因为此时session是有效的，session recovery过程只是进行本地操作
       不需要和网络交互，所以只缓存power off消息，继续执行session active过程，然后再关机 */
    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == CNAS_HSM_GetSessionActiveReason_SessionActive())
    {
        CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

        CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                  CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_OFF);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasScpActiveCnf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SCP_ACTIVE_CNF_STRU                      *pstHrpdScpActCnf;
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enSessionActFailReason;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;
    VOS_UINT8                                               ucIsGetPaNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enReqSessionType;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

    pstHrpdScpActCnf = (CAS_CNAS_HRPD_SCP_ACTIVE_CNF_STRU *)pstMsg;

    if (CAS_CNAS_HRPD_SCP_NEG_RSLT_SUCCESS == pstHrpdScpActCnf->enResult)
    {
        enCurrSessionRelType = CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType(pstHrpdScpActCnf->enSessionReleaseType);

        CNAS_HSM_SetCurrSessionRelType(enCurrSessionRelType);

        ucIsGetPaNtf = CNAS_HSM_GetPaNtfFlag_SessionActive();

        if (VOS_FALSE == ucIsGetPaNtf)
        {
            CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF,
                                TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF_LEN);

            CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF);

        }
        else
        {
            if(CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY != CNAS_HSM_GetSessionActiveReason_SessionActive())
            {
                enReqSessionType = CNAS_HSM_GetNegoSessionType();

                if (CNAS_HSM_SESSION_TYPE_BUTT == enReqSessionType)
                {
                    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasScpActiveCnf_SessionAct_WaitScpActiveCnf: Curr Session Type is BUTT!");
                }

                CNAS_HSM_SndEhsmSessionInfoInd(enReqSessionType);
            }

            CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_SUCC,
                                      CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT);
        }

    }
    else
    {
        CNAS_HSM_SetCurrSessionRelType(CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

        /* Convert SCP reason to HSM reason */
        enSessionActFailReason = CNAS_HSM_ConvertScpFailReasonToSessionActFailReason(
                                                                pstHrpdScpActCnf->enResult);

        if (PS_TRUE == pstHrpdScpActCnf->enProtocolTypeVaildFlag)
        {
            CNAS_HSM_SetScpActFailProcType(pstHrpdScpActCnf->usProtocolType);
            CNAS_HSM_SetScpActFailProcSubtype(pstHrpdScpActCnf->usProtocolSubType);
        }

        /* on receiving no RF reason session active fail, here send radio resource register to RRM,
           then implement session deactive procedure and switch to Inactive State */
        if (CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF == pstHrpdScpActCnf->enResult)
        {
            CNAS_HSM_SndRrmRegisterInd(RRM_PS_TASK_TYPE_HRPD_SESSION_NEG,
                                       VOS_RATMODE_HRPD);
        }

        CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                  enSessionActFailReason);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;

    CNAS_HSM_SetPaNtfFlag_SessionActive(VOS_TRUE);

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* directly send ID_HSM_EHSM_SESSION_INFO_IND with the result */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);

    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf,receive the invalid session type--BUTT");

        enSessionType = CNAS_HSM_GetReqSessionType();
    }

    /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitScpActiveCnfTimerExpire_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitScpActiveCnfTimerExpire_SessionAct_WaitScpActiveCnf: timer out");

    CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                              CNAS_HSM_SESSION_ACT_FAIL_REASON_WAIT_SCP_CNF_EXP);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 等待PA状态，收到PowerOff，只打标记，不退出，继续等待PA，PA流程结束后再处理PowerOff*/
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enReqSessionType;


    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF);

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    enReqSessionType = CNAS_HSM_GetReqSessionType();

    /* convert session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);
    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf,receive the invalid session type--BUTT");

        enSessionType = CNAS_HSM_GetReqSessionType();
    }
    else
    {
        if ((CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == CNAS_HSM_GetSessionActiveReason_SessionActive())
         && (enReqSessionType != enSessionType))
        {
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf,receive the differnt session type when recover");
        }
    }

    /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    if(CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY != CNAS_HSM_GetSessionActiveReason_SessionActive())
    {
        CNAS_HSM_SndEhsmSessionInfoInd(enSessionType);

        if (CNAS_HSM_SESSION_TYPE_EHRPD == enSessionType)
        {
            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_SUPPORT_EHRPD, UEPS_PID_HSM);
        }
        else
        {
            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_NOT_SUPPORT_EHRPD, UEPS_PID_HSM);
        }
    }

    CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_SUCC,
                              CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitPaRatModeNtfTimerExpire_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitPaRatModeNtfTimerExpire_SessionAct_WaitPaRatModeNtf: timer out");

    /* send ID_HSM_EHSM_SESSION_INFO_IND with the session type incorrespondance with the active request */
    CNAS_HSM_SndEhsmSessionInfoInd(CNAS_HSM_GetReqSessionType());

    /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(CNAS_HSM_GetReqSessionType());

    /* process this case as activation succes*/
    CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_SUCC,
                              CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}





VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    /* Save the Overhead message to the cache queue */
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* (保护)session recovery过程中收到suspend ind；因为此时session是有效的，session recovery过程只是进行本地操作
       不需要和网络交互，所以只缓存suspend ind消息，继续执行session active过程，然后再挂起 */
    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == CNAS_HSM_GetSessionActiveReason_SessionActive())
    {
        CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        /* HSM 只会在对冲场景下才会在此子状态收到suspend ind,HSM不等待结果直接退状态机 */
        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

        CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                  CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_SUSPEND);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* session recovery过程中收到power save；因为此时session是有效的，session recovery过程只是进行本地操作
       不需要和网络交互，所以只缓存power save消息，继续执行session active过程，然后再处理power save */
    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == CNAS_HSM_GetSessionActiveReason_SessionActive())
    {
        CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

        CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                  CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_SAVE);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSM only can rcv this msg in session recovery procedure after quit Slave State */
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* In SessionAct_WaitPaRatModeNtf substate, the session active procedure is going to success,
       wait the procedure finish,this procedure is very quick*/
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSM only can rcv this msg in session recovery procedure after quit Slave State */
    CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* during session recovery, on rceiving network lost, wait current procedure finish */
    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == CNAS_HSM_GetSessionActiveReason_SessionActive())
    {
        CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        /* during session recovery, on rceiving suspend ind, wait current procedure finish */

        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

        CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                  CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_NETWORK_LOST);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd;
    VOS_UINT8                                               ucMsgType;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;

    pstSnpDataInd  = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU*)pstMsg;

    enProtocolType = pstSnpDataInd->enProtocolType;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);


    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        if (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN == ucMsgType)
        {
            CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);
            /* just cache the message */
            CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;
    VOS_UINT8                                               ucMsgType;

    pstSnpDataInd  = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU*)pstMsg;

    enProtocolType = pstSnpDataInd->enProtocolType;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        if (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN == ucMsgType)
        {
            CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);
            /* just cache the message */
            CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason;
    HSD_HSM_OVERHEAD_MSG_IND_STRU                          *pstOverHeadMsgInd;
    CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8                       enRcvOhmScene;
    VOS_UINT8                                               ucIsNeedStartDeactProc;

    pstOverHeadMsgInd      = (HSD_HSM_OVERHEAD_MSG_IND_STRU *)pstMsg;

    ucIsNeedStartDeactProc = VOS_FALSE;
    enSessionActiveReason  = CNAS_HSM_GetSessionActiveReason_SessionActive();

    CNAS_HSM_LogSessionOperateCtrlInfo();

    if (CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY == enSessionActiveReason)
    {
        CNAS_HSM_UpdateHrpdSysInfo(pstOverHeadMsgInd);

        CNAS_HSM_SetAbortFlag_SessionActive(VOS_TRUE);
        /* just cache the message */
        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSM_HandleMonitorDistance_Open(&ucIsNeedStartDeactProc);

        if (VOS_TRUE == ucIsNeedStartDeactProc)
        {
            CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

            CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                      CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        enRcvOhmScene = CNAS_HSM_GetRcvOhmScene();

        /* clear the rcv ohm scene */
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_OHM);

        if (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ == enRcvOhmScene)
        {
            /*************************************************************************************
             C.S0024-A_v3.0 7.3.7.1.6.1:
                 one of the following conditions is true:
                 1: the UATISubnetMask is not equal to the SubnetMask of the sector in the active set;
                 2: the result of bitwise logical AND of the UATI and ReducedSubnetMask is different from
                    the result of bitwise logical AND of SectorID and ReducedMask(where SectorID and SubnetMask
                    correspond to the sector in the active set)
             **************************************************************************************/

            ucIsNeedStartDeactProc = CNAS_HSM_IsNeedStartDeactProcedure();

            if (VOS_TRUE == ucIsNeedStartDeactProc)
            {
                CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

                CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                          CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_OHM);

            }
        }
        else
        {
            /*****************************************************************************************
              C.S0024-A V3.0 7.3.7.1.6.1:
              If the access terminal receives a RouteUpdate.IdleHO indication or a ConnectedState.ConnectionClosed,
              and then it receives an OverheadMessages.Updated indication,
              access terminal shall send a UATIRequest, if both of the following two conditions are true
              1: the subnet associated with UATI and the current subnet are different;
              2: supportSecondaryColorCodes is set to 0x00 or UATIColorCode is different from all of the
                 secondaryColorCode values provided as public data by the Overhead Messages protocol
              完全按照协议处理CCF用例C.S0038 2.2.2.8将会Failed并且RF自动化测试(DTS2015091705555)也不会通过。
              因此如果CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg()返回TRUE(NV可控)，则CNAS参照标杆处理，
              不判断CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE 和 CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO两个条件。
              *****************************************************************************************/

            if ((VOS_TRUE == CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg())
             || (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO    == enRcvOhmScene)
             || (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE == enRcvOhmScene))
            {
                if (VOS_TRUE == CNAS_HSM_IsNeedSndUatiReq())
                {
                     CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

                     CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                                               CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_OHM);
                }
            }
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitScpActiveCnf
Description     :   process hsm internal session close ind message wait scp active cnf state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED-------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED---the current event need to further process

Modify History  :
1)  Date           : 2015-06-10
    Author         : y00307564
    Modify content : Create
2)  Date           : 2016-01-25
    Author         : w00351686
    Modify content : DTS2016011700511:当前缓存中有OHM消息，则清除此消息，避免多次向网侧发送session close
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    /* 如果缓存中有OHM消息，则清除缓存中的OHM消息，因为后续在处理session close ind的时候会重新进行重试流程,
        此处如果不清理OHM消息，则在稳态处理缓存时可能向网侧发送两次session close */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                              CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitPaRatModeNtf
Description     :   process hsm internal session close ind message wait pa rat mode ntf state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED-------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED---the current event need to further process

Modify History  :
1)  Date           : 2015-06-10
    Author         : y00307564
    Modify content : Create
2)  Date           : 2016-01-25
    Author         : w00351686
    Modify content : DTS2016011700511:当前缓存中有OHM消息，则清除此消息，避免多次向网侧发送session close
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    /* 如果缓存中有OHM消息，则清除缓存中的OHM消息，因为后续在处理session close ind的时候会重新进行重试流程,
        此处如果不清理OHM消息，则在稳态处理缓存时可能向网侧发送两次session close */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmScpActReq(CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
                              CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8
CNAS_HSM_ConvertScpFailReasonToSessionActFailReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpFailReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;

    ulReasonCnt = sizeof(g_astHsmScpFailReasonMapSessionActFailReasonTbl) /
                            sizeof(CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_ACT_FAIL_REASON_STRU);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (g_astHsmScpFailReasonMapSessionActFailReasonTbl[ulLoop].enScpFailReason
                                                                         == enScpFailReason)
        {
            return g_astHsmScpFailReasonMapSessionActFailReasonTbl[ulLoop].enSessionActFailReason;
        }
    }

    return CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


