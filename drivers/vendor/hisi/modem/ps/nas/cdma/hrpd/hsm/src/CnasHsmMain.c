

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmMain.h"
#include "CnasHsmCtx.h"
#include "CnasTimerMgmt.h"
#include "CnasCcb.h"
#include "CnasMntn.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmPreProcAct.h"
#include "CnasHsmPreProcTbl.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmSndAs.h"
#include "cas_hrpd_idlestate_nas_pif.h"
#include "CnasHsmSndAps.h"
#include "CnasHsmMntn.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/


VOS_UINT32 CNAS_HSM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    pstFsmDesc = CNAS_HSM_GetPreProcFsmDescAddr();

    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_HSM_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        ulRet = (*pActFun) (ulEventType, pstMsg);
    }

    return ulRet;
}




VOS_UINT32 CNAS_HSM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    CNAS_HSM_L1_STA_ENUM_UINT32         enCurMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32          enCurSubState;

    enCurMainState = CNAS_HSM_GetCurrMainState();
    enCurSubState  = CNAS_HSM_GetCurrSubState();

    CNAS_INFO_LOG3(UEPS_PID_HSM, "CNAS_HSM_ProcessMsgInFsm", enCurMainState, enCurSubState,ulEventType);

    pstFsmDesc = CNAS_HSM_GetFsmDescAddr();

    /* according to the current main state and substate, search the matched action process function */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, NAS_BuildCurState(enCurMainState, enCurSubState), ulEventType);

    if (VOS_NULL_PTR == pActFun)
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
    CNAS_INFO_LOG1(UEPS_PID_HSM, "CNAS_HSM_ProcessMsgInFsm", ulRet);

    return ulRet;
}



VOS_VOID CNAS_HSM_ProcessBufferMsg(VOS_VOID)
{
    CNAS_HSM_MSG_STRU                                      *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT8                                               ucOldBuffMsgNum;
    VOS_UINT8                                               ucNewBuffMsgNum;

    ucOldBuffMsgNum = CNAS_HSM_GetCacheMsgNum();

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    if (0 < ucOldBuffMsgNum)
    {
        /* Allocate memory to copy the buffer message */
        pstEntryMsg = (CNAS_HSM_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MSG_STRU));
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == CNAS_HSM_GetNextCachedMsg(pstEntryMsg))
    {
        /* Process the message in preproc */
        if (CNAS_HSM_FSM_EVENT_HANDLED == CNAS_HSM_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            /* Process the message in internal message handler */
            CNAS_HSM_ProcessHsmIntMsg();

            continue;
        }

        /* If message handler is not found in preproc, process the message in FSM */
        if (CNAS_HSM_FSM_EVENT_HANDLED == CNAS_HSM_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            /* Process the message in internal message handler */
            CNAS_HSM_ProcessHsmIntMsg();
        }
        else
        {
            CNAS_HSM_LogDiscardMsgInfo(CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_BUFF_MSG_PROC, VOS_NULL_PTR);

            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcessBufferMsg the current event could not be processed...");
        }

        /* 同时缓存多余1条消息时，可能会发生继续缓存的场景，导致缓存队列中一直存在消息，导致此循环无法退出 */
        ucNewBuffMsgNum = CNAS_HSM_GetCacheMsgNum();

        if (ucNewBuffMsgNum >= ucOldBuffMsgNum)
        {
            break;
        }

        ucOldBuffMsgNum = ucNewBuffMsgNum;
    }

    PS_MEM_FREE(UEPS_PID_HSM, pstEntryMsg);

    return;
}



VOS_VOID CNAS_HSM_ProcessHsmIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSM_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* log the internal message here */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        if (CNAS_HSM_FSM_EVENT_HANDLED == CNAS_HSM_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* free the buffer of the current internal message */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* continue process the next internal message */
            pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSM_GetNextIntMsg();

            continue;
        }

        /* process the current message in the state machine */
        CNAS_HSM_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* free the buffer of the current internal message */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* continue process the next internal message */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSM_GetNextIntMsg();
    }

    return;
}




VOS_VOID CNAS_HSM_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulSenderPid;
    CNAS_HSM_SS_ID_ENUM_UINT32          enOldSubState;
    CNAS_HSM_SS_ID_ENUM_UINT32          enNewSubState;

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* generate the event type and judge if it's timer expired */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* stop the timer to update the timer status */
        CNAS_StopTimer(UEPS_PID_HSM, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    enOldSubState = CNAS_HSM_GetCurrSubState();

    /* first process the message in MainCtrl,If process result is ended,need not to process continue */
    if (CNAS_HSM_FSM_EVENT_HANDLED == CNAS_HSM_PreProcessMsg(ulEventType, pstMsg))
    {
        /* HSM processes the internal message sent during pre-process step */
        CNAS_HSM_ProcessHsmIntMsg();

        enNewSubState = CNAS_HSM_GetCurrSubState();

         /* judge the sub procedure is quit just now */
        if ((CNAS_HSM_SS_VACANT != enOldSubState)
         && (CNAS_HSM_SS_VACANT == enNewSubState))
        {
            CNAS_HSM_ProcessBufferMsg();
        }

        return;
    }

    /* process the message in the fsm */
    CNAS_HSM_ProcessMsgInFsm(ulEventType, pstMsg);

    CNAS_HSM_ProcessHsmIntMsg();

    enNewSubState = CNAS_HSM_GetCurrSubState();

    /*judge the sub procedure is quit just now */
    if ((CNAS_HSM_SS_VACANT != enOldSubState)
     && (CNAS_HSM_SS_VACANT == enNewSubState))
    {
        CNAS_HSM_ProcessBufferMsg();
    }

    return;
}



VOS_UINT32  CNAS_HSM_InitTask(VOS_VOID)
{
    CNAS_HSM_InitCtx(CNAS_HSM_INIT_CTX_STARTUP);

    CNAS_HSM_RegisterPreFsm();

    CNAS_HSM_RegisterFsm();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_InitPid
Description     :   The init function of HSM module PID
Input parameters:   enInitPhase----the init phase
Outout parameters:  None
Return Value    :   VOS_UINT32

Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create
2)  Date           : 2015-09-30
    Author         : y00307564
    Modify content : DTS2015082403731 增加卡状态状态上报注册函数
*****************************************************************************/

VOS_UINT32 CNAS_HSM_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            CNAS_HSM_InitTask();
            break;

        case VOS_IP_INITIAL:
            (VOS_VOID)NAS_PIHAPI_RegUsimCardStatusIndMsg(UEPS_PID_HSM);
            break;
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
#endif /* __cpluscplus */
#endif /* __cpluscplus */




