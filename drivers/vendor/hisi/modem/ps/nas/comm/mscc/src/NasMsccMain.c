/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccMain.c
Author          :   k902809
Version         :
Date            :   2015-0202
Description     :   Contains processes related to preproc, process msg in fsm, process internal message and process message in buffer.

Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/
/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include "NasFsm.h"
#include "NasComm.h"
#include "NasMsccMain.h"
#include "NasMsccPreProcTbl.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccCtx.h"

#include "NasMntn.h"
#include "NasMsccMntn.h"
#include "NasMsccFsmSwitchOnTbl.h"
#include "NasMsccFsmPowerOffTbl.h"
#include "NasMsccFsmSysCfgTbl.h"
#include "NasMsccFsmSysCfg.h"

#include "NasMsccFsmBsrTbl.h"
#include "NasMsccMsgPrioCompare.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccFsmSysAcqTbl.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "NasMsccFsmCLInterSysTbl.h"
#include "NasMsccFsmCLInterSys.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_MAIN_C


/*****************************************************************************
  2. Global Variable.
*****************************************************************************/

/**************************************************************************/
/* 3. List of action tables */
/**************************************************************************/


VOS_UINT32 NAS_MSCC_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    /* Get PreProcess address */
    pstFsmDesc = NAS_MSCC_GetPreFsmDescAddr();

    /* Find preprocess message handler in preprocess table */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, NAS_MSCC_L1_STA_PREPROC, ulEventType);

    /* Check the message handler is valid */
    if (VOS_NULL_PTR != pActFun )
    {
        /* Process the message in handler */
        ulRet = (*pActFun) ( ulEventType, pstMsg);
    }

    /* Return FALSE if there is no handler or Return the value returned by preprocess message handler */
    return ulRet;
}


VOS_UINT32 NAS_MSCC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    NAS_INFO_LOG2(UEPS_PID_MSCC,"NAS_MSCC_FSM_ProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = NAS_MSCC_GetCurFsmDesc();

    /* Find the handler for event in current FSM */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Call the function */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        NAS_INFO_LOG1(UEPS_PID_MSCC,"NAS_MSCC_FSM_ProcessEvent", ulRet);
        return ulRet;
    }

    /* Return if not handler is found */
    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    pstCurFsm           = NAS_MSCC_GetCurFsmAddr();

    usOldStackDepth    = NAS_MSCC_GetFsmStackDepth();

    ulRet     = NAS_MSCC_FSM_ProcessEvent( pstCurFsm->ulState,
                                           ulEventType,
                                           (VOS_VOID*)pstMsg );

    usNewStackDepth    = NAS_MSCC_GetFsmStackDepth();

    if ( usNewStackDepth <= usOldStackDepth )
    {
        /* Return if there is no FSM loaded or FSM exited */
        return ulRet;
    }

    /* Get new FSM address */
    pstCurFsm   = NAS_MSCC_GetCurFsmAddr();

    /* Process the message in new FSM */
    ulRet       = NAS_MSCC_FSM_ProcessEvent( pstCurFsm->ulState,
                                             ulEventType,
                                             (VOS_VOID*)pstMsg );

    return ulRet;
}


VOS_VOID NAS_MSCC_ProcessMsccIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)NAS_MSCC_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        NAS_MSCC_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                                  pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                                  (VOS_VOID *)pstIntMsg);

        ulEventType  = NAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* Preprocess the message if it in preproc table */
        if (VOS_TRUE == NAS_MSCC_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* If the message is processed then free Msg pointer */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* Get next internal message */
            pstIntMsg = (MSG_HEADER_STRU *)NAS_MSCC_GetNextIntMsg();

            continue;
        }
        /* There is no entry in Pre process table then process in current FSM */
        /* Send the message to process in current FSM */
        (VOS_VOID)NAS_MSCC_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* Free the message */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* Get next internal message  */
        pstIntMsg = (MSG_HEADER_STRU *)NAS_MSCC_GetNextIntMsg();
    }

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcessBufferMsg
Description     :
                       1) Copy the message into local and process in preproc table
                       2) Depending on return value of preproc: if return value is TRUE then continue to handle message
                            from buffer.
                       3) Otherwise process the message in current FSM and internal message.

Input parameters:   Void
Outout parameters:  None
Return Value    :

Modify History:
    1)  Date    :   2015-02-03
        Author  :   k902809
        Modify content :    Create
    2)  Date    :   2015-08-17
        Author  :   wenlutao00176964
        Modify content :DTS2015070802862:CL搜网状态机中SCAN超时后,用户设置SYSCFG，导致
                        同时出现SCAN超时消息以及用户SYSCFG两条缓存同时出现的情况
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcessBufferMsg( VOS_VOID )
{
    NAS_MSCC_MSG_STRU                  *pstEntryMsg = VOS_NULL_PTR;

    /* Allocate memory to copy the buffer message */
    pstEntryMsg = (NAS_MSCC_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_MSCC_MSG_STRU));

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == NAS_MSCC_GetNextCachedMsg(pstEntryMsg))
    {

        /* Update the cache message queue. Clear the first member of the cache message and shift the queue one place.  */
        NAS_MSCC_ClearCacheMsg(0);

        /* Process the message in preproc */
        if (VOS_TRUE == NAS_MSCC_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            continue;
        }

        /* If message handler is not found in preproc, process the message in FSM */
        if (VOS_TRUE == NAS_MSCC_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            /* Process the message in internal message handler */
            NAS_MSCC_ProcessMsccIntMsg();
        }
        else
        {
            /* postprocess always abort or cache,so we could not process the buffer any more,break*/
            if (VOS_TRUE == NAS_MSCC_PostProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
            {
                break;
            }
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstEntryMsg);

    return;
}


VOS_UINT32  NAS_MSCC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8               enMsgPrio;

    enMsgPrio = NAS_MSCC_GetMsgComparePrioRslt(ulEventType, pstMsg);

    switch ( enMsgPrio )
    {
        case NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT :

            NAS_MSCC_SndAbortFsmReq();

            (VOS_VOID)NAS_MSCC_SaveCacheMsg(ulEventType,
                                (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        case NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE :

            (VOS_VOID)NAS_MSCC_SaveCacheMsg(ulEventType,
                              (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        case NAS_MSCC_MSG_COMPARE_PRIO_RSLT_INITFSM :

            return VOS_FALSE;

        case NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD :
            return VOS_FALSE;

        default:
            return VOS_FALSE;
    }
}


VOS_UINT32 NAS_MSCC_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    usOldStackDepth = NAS_MSCC_GetFsmStackDepth();

    if (VOS_TRUE == NAS_MSCC_ProcMsgPrio(ulEventType, pstMsg))
    {
        NAS_MSCC_ProcessMsccIntMsg();

        usNewStackDepth = NAS_MSCC_GetFsmStackDepth();

        /* If there is FSM pop then process the message in buffer message */
        if (usNewStackDepth < usOldStackDepth)
        {
            NAS_MSCC_ProcessBufferMsg();
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MSCC_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    NAS_MSCC_LogMsgInfo(pstMsgHeader);

    /* If the sender pid is timer then stop the timer */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* Stop the particular protection timer */
        NAS_MSCC_StopTimer(pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    if (VOS_TRUE == NAS_MSCC_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }

    usOldStackDepth = NAS_MSCC_GetFsmStackDepth();

    /* Process the message in current FSM,if  */
    if (VOS_TRUE == NAS_MSCC_ProcessMsgInFsm(ulEventType, pstMsg))
    {
        /* Process the internal message */
        NAS_MSCC_ProcessMsccIntMsg();

        usNewStackDepth = NAS_MSCC_GetFsmStackDepth();

        /* If there is FSM pop then process the message in buffer message */
        if (usNewStackDepth < usOldStackDepth)
        {
            NAS_MSCC_ProcessBufferMsg();
        }
    }
    else
    {
        (VOS_VOID)NAS_MSCC_PostProcessMsg(ulEventType, pstMsg);
    }

    NAS_MSCC_UpdateMsgExitTime();

    return;
}



VOS_VOID NAS_MSCC_RegPreFsm(VOS_VOID)
{
    /* register pre process FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetPreFsmDescAddr()),
                         "NAS:FSM:MSCC:PRE",
                         (VOS_UINT32)(NAS_MSCC_GetPreProcessStaTblSize()),
                         NAS_MSCC_GetPreProcStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return;
}


VOS_VOID NAS_MSCC_RegMainL1Fsm(VOS_VOID)
{
    /* register main FSm */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetMainFsmDescAddr()),
                         "NAS:FSM:MSCC:MAIN",
                         (VOS_UINT32)(NAS_MSCC_GetMainStaTblSize()),
                         NAS_MSCC_GetMsccMainStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_L1Main);

    return;
}


VOS_VOID NAS_MSCC_RegL2Fsm(VOS_VOID)
{
    /* register SwitchOn FSm  */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetSwitchOnFsmDescAddr()),
                         "NAS:FSM:MSCC:SwitchOn",
                         (VOS_UINT32)NAS_MSCC_GetSwitchOnStaTblSize(),
                         NAS_MSCC_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_SwitchOn);


    /* Register PowerOff FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetPowerOffFsmDescAddr()),
                         "NAS:FSM:MSCC:PowerOff",
                         (VOS_UINT32)NAS_MSCC_GetPowerOffStaTblSize(),
                         NAS_MSCC_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_PowerOff);

    /* Register syscfg FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetSysCfgFsmDescAddr()),
                         "NAS:FSM:MSCC:SysCfg",
                         (VOS_UINT32)NAS_MSCC_GetSysCfgStaTblSize(),
                         NAS_MSCC_GetSysCfgStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_SysCfg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* Register BSR FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetBsrFsmDescAddr()),
                         "NAS:FSM:MSCC:BSR",
                         (VOS_UINT32)NAS_MSCC_GetBsrStaTblSize(),
                         NAS_MSCC_GetBsrStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_BSR);

    /* Register SystemAcquire FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetSysAcqFsmDescAddr()),
                         "NAS:FSM:MSCC:System acquire",
                         (VOS_UINT32)NAS_MSCC_GetSysAcqStaTblSize(),
                         NAS_MSCC_GetSysAcqStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_SysAcq);

    /* Register CL Intersys FSM */
    NAS_FSM_RegisterFsm((NAS_MSCC_GetCLInterSysFsmDescAddr()),
                         "NAS:FSM:MSCC:CL InterSys",
                         (VOS_UINT32)NAS_MSCC_GetCLInterSysStaTblSize(),
                         NAS_MSCC_GetCLInterSysStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MSCC_InitFsmCtx_CLInterSys);

#endif

}


VOS_VOID  NAS_MSCC_RegFsm(VOS_VOID)
{
    NAS_MSCC_RegPreFsm();

    /* Register L1 main FSM */
    NAS_MSCC_RegMainL1Fsm();

    /* register L2 main FSM*/
    NAS_MSCC_RegL2Fsm();
}


VOS_UINT32  NAS_MSCC_InitTask(VOS_VOID)
{
    /*  init ctx for MSCC*/
    NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_STARTUP);

    /* MSCC FSM register */
    NAS_MSCC_RegFsm();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* Init task for MSCC */
            (VOS_VOID)NAS_MSCC_InitTask();
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
            break;

        default:
            break;
    }

    return VOS_OK;
}



VOS_UINT32 NAS_MSCC_FidInit(enum VOS_INIT_PHASE_DEFINE enInitPhase)
{

    VOS_UINT32 ulReturnCode;

    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_MSCC,
                                               (Init_Fun_Type)NAS_MSCC_InitPid,
                                               (Msg_Fun_Type)NAS_MSCC_MsgProc);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterTaskPrio(UEPS_FID_MSCC, NAS_MSCC_TASK_PRIO);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
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

    }

    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
