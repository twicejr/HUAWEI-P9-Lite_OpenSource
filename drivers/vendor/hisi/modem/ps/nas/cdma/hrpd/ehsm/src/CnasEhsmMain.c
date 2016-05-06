


/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmMain.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmTimerMgmt.h"
#include "CnasEhsmMntn.h"
#include "CnasEhsmPreProcAct.h"
#include "CnasEhsmPreProcTbl.h"

#include "CnasEhsmFsmActivating.h"
#include "CnasEhsmFsmDeactivating.h"
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmFsmDeactivatingTbl.h"
#include "CnasEhsmMsgPrioCompare.h"
#include "ehsm_aps_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_MAIN_C

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 CNAS_EHSM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    /* Get PreProcess address */
    pstFsmDesc = CNAS_EHSM_GetPreProcDescAddr();

    /* Find preprocess message handler in preprocess table */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_EHSM_L1_STA_PREPROC, ulEventType);

    /* Check the message handler is valid */
    if (VOS_NULL_PTR != pActFun )
    {
        /* Process the message in handler */
        ulRet = (*pActFun) ( ulEventType, pstMsg);
    }

    /* Return FALSE if there is no handler or Return the value returned by preprocess message handler */
    return ulRet;
}


VOS_UINT32 CNAS_EHSM_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_EHSM,"CNAS_EHSM_FSM_ProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_EHSM_GetCurFsmDesc();

    /* Find the handler for event in current FSM */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Call the function */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        CNAS_INFO_LOG1(UEPS_PID_EHSM,"CNAS_EHSM_FSM_ProcessEvent", ulRet);
        return ulRet;
    }

    /* Return if not handler is found */
    return VOS_FALSE;
}


VOS_UINT32 CNAS_EHSM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    pstCurFsm           = CNAS_EHSM_GetCurFsmAddr();

    usOldStackDepth     = CNAS_EHSM_GetFsmStackDepth();

    /* Log the context details */
    CNAS_EHSM_MNTN_LogCtxInfo();

    ulRet     = CNAS_EHSM_FSM_ProcessEvent( pstCurFsm->ulState,
                                            ulEventType,
                                            (VOS_VOID*)pstMsg );

    usNewStackDepth     = CNAS_EHSM_GetFsmStackDepth();

    if ( usNewStackDepth <= usOldStackDepth )
    {
        /* Return if there is no FSM loaded or FSM exited */
        return ulRet;
    }

    /* Log the context details */
    CNAS_EHSM_MNTN_LogCtxInfo();

    /* Get new FSM address */
    pstCurFsm   = CNAS_EHSM_GetCurFsmAddr();

    /* Process the message in new FSM */
    ulRet       = CNAS_EHSM_FSM_ProcessEvent( pstCurFsm->ulState,
                                              ulEventType,
                                              (VOS_VOID*)pstMsg );

    return ulRet;
}


VOS_VOID CNAS_EHSM_ProcessBufferMsg( VOS_VOID )
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulRet;

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-17, begin */
    if (0 < CNAS_EHSM_GetCacheMsgAddr()->ucCacheMsgNum)
    {
        /* Allocate memory to copy the buffer message */
        pstEntryMsg = (CNAS_EHSM_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM, sizeof(CNAS_EHSM_MSG_STRU));
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-17, end */

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == CNAS_EHSM_GetNextCachedMsg(pstEntryMsg))
    {

        /* Update the cache message queue. Clear the first member of the cache message and shift the queue one place.  */
        CNAS_EHSM_ClearCacheMsg(0);

        /* Process the message in preproc */
        if (VOS_TRUE == CNAS_EHSM_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            continue;
        }

        /* get current FSM stack depth */
        usOldStackDepth     = CNAS_EHSM_GetFsmStackDepth();

        /* If message handler is not found in preproc, process the message in FSM */
        ulRet = CNAS_EHSM_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer);

        /* get current FSM stack depth */
        usNewStackDepth     = CNAS_EHSM_GetFsmStackDepth();

        /* If the depth changed, can not process more buffered message */
        if ( usNewStackDepth > usOldStackDepth )
        {
            break;
        }

        /* 该消息进入了后处理,后处理中是打断或缓存的,则表明不能继续处理缓存 */
        if (VOS_FALSE == ulRet)
        {
            if ( VOS_TRUE == CNAS_EHSM_PostProcessMsg(pstEntryMsg->ulEventType,
                            (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
            {
                break;
            }
        }

    }

    PS_MEM_FREE(UEPS_PID_EHSM, pstEntryMsg);

    return;
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_MsgProc
Description     :
                    1) Find recieved message is from timer, if yes stop that particular time.
                    2) Send the message to process in pre proc table.
                    3) Send the message to process in current FSM
                    4) Process the internal message
                    5) If there is FSM pop then process the message in buffer message.

Input parameters:   Void
Output parameters:  None
Return Value    :

Modify History:
    1)  Date    :   2015-05-14
        Author  :   K00902809
        Modify content :    Create
    2)  Date    :   2015-12-24
        Author  :   w00242748
        Modify content :DTS2015121805249:副卡支持EHRPD
*****************************************************************************/
VOS_VOID CNAS_EHSM_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulSenderPid;

    /* 适配modem1，且当前与modem1对接时，忽略ESM发送的消息 */
    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    if ( (MODEM_ID_0 != CNAS_CCB_GetCdmaModeModemId())
      && (PS_PID_ESM == pstMsg->ulSenderPid) )
    {
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* If the sender pid is timer then stop the timer */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* Stop the particular protection timer */
        CNAS_EHSM_StopTimer(pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    if (VOS_TRUE == CNAS_EHSM_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }

    usOldStackDepth = CNAS_EHSM_GetFsmStackDepth();

    /* Process the message in current FSM */
    ulRslt = CNAS_EHSM_ProcessMsgInFsm(ulEventType, pstMsg);

    usNewStackDepth = CNAS_EHSM_GetFsmStackDepth();

    /* If there is FSM pop then fist process the result of FSM */
    if (usNewStackDepth < usOldStackDepth)
    {
        CNAS_EHSM_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    if (VOS_TRUE == ulRslt)
    {
        /* 当前仅收到状态机的退出消息才能够处理缓存 */
        if (VOS_TRUE == CNAS_EHSM_GetFsmStackPopFlg())
        {
            CNAS_EHSM_ProcessBufferMsg();
            CNAS_EHSM_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    else
    {
        (VOS_VOID)CNAS_EHSM_PostProcessMsg(ulEventType, pstMsg);
    }

    return;
}


VOS_UINT32 CNAS_EHSM_RegPreProcFsm(VOS_VOID)
{
    /* register pre process FSM */
    NAS_FSM_RegisterFsm((CNAS_EHSM_GetPreProcDescAddr()),
                         "CNAS:FSM:EHSM:PRE",
                         (VOS_UINT32)(CNAS_EHSM_GetPreProcStaTblSize()),
                         CNAS_EHSM_GetPreProcStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RegL1MainFsm(VOS_VOID)
{
    /* register main FSm */
    NAS_FSM_RegisterFsm((CNAS_EHSM_GetMainFsmDescAddr()),
                         "CNAS:FSM:EHSM:MAIN",
                         (VOS_UINT32)(CNAS_EHSM_GetMainStaTblSize()),
                         CNAS_EHSM_GetEhsmMainStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}


VOS_VOID CNAS_EHSM_RegL2Fsm(VOS_VOID)
{
    /* Register ACtivating FSM */
    NAS_FSM_RegisterFsm((CNAS_EHSM_GetActivatingFsmDescAddr()),
                         "CNAS:FSM:EHSM:Activating",
                         (VOS_UINT32)CNAS_EHSM_GetActivatingStaTblSize(),
                         CNAS_EHSM_GetActivatingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_EHSM_InitFsmCtx_Activating);

    /* Register Deativating FSM */
    NAS_FSM_RegisterFsm((CNAS_EHSM_GetDeactivatingFsmDescAddr()),
                         "CNAS:FSM:EHSM:Deactivating",
                         (VOS_UINT32)CNAS_EHSM_GetDeactivatingStaTblSize(),
                         CNAS_EHSM_GetDeactivatingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_EHSM_InitFsmCtx_Deactivating);
}


VOS_VOID  CNAS_EHSM_RegFsm(VOS_VOID)
{
    CNAS_EHSM_RegPreProcFsm();

    /* Register L1 main FSM */
    CNAS_EHSM_RegL1MainFsm();

    /* register L2 main FSM*/
    CNAS_EHSM_RegL2Fsm();
}


VOS_UINT32  CNAS_EHSM_InitTask(VOS_VOID)
{
    /* Init ctx for EHSM */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_EHSM_InitCtx(CNAS_EHSM_INIT_CTX_STARTUP);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* EHSM FSM register */
    CNAS_EHSM_RegFsm();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* Init task for EHSM */
            CNAS_EHSM_InitTask();
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

/*****************************************************************************
 函 数 名  : CNAS_EHSM_ProcMsgPrio
 功能描述  : 将当前收到的消息和子状态机的入口消息进行比较,并根据比较结果进行后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前消息处理完成，不需要后续处理
             VOS_FALSE:当前消息处理完成，需要后续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_EHSM_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8                  enAbortType;
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32     enMsgPrio;

    enAbortType = CNAS_EHSM_ABORT_BUTT;

    enMsgPrio = CNAS_EHSM_GetMsgComparePrioRslt(ulEventType, pstMsg, &enAbortType);

    switch ( enMsgPrio )
    {
        /* 缓存消息 */
        case CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE :
            CNAS_EHSM_SaveCacheMsg(ulEventType,(VOS_VOID *) pstMsg);
            return VOS_TRUE;

        /* 打断处理 */
        case CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT :
            CNAS_EHSM_SndInternalAbortReq(ulEventType);
            CNAS_EHSM_SaveCacheMsg(ulEventType, (VOS_VOID *) pstMsg);
            return VOS_TRUE;

        case CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM :
        case CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD :
        default:
            CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_ProcMsgPrio:invlid msg priority",ulEventType);
            return VOS_FALSE;
    }
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_PostProcessMsg
 功能描述  : EHSM状态机后处理函数,将当前收到的消息和sub状态机的入口消息进行比较,
              判断后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : 返回消息是否已经处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_EHSM_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    ulRet = CNAS_EHSM_ProcMsgPrio(ulEventType, pstMsg);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MsgProcEntry
 功能描述  : MMA的消息处理入口函数
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月5日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_MsgProcEntry(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstNextMsg = VOS_NULL_PTR;

    /* 先处理外部消息 */
    CNAS_EHSM_MsgProc(pstMsg);

    /* 外部消息处理完成后处理内部消息 */
    pstNextMsg = (MSG_HEADER_STRU*)CNAS_EHSM_GetNextIntMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {
        /* 将该消息钩出来,以便于在PSTAS中显示 */
        DIAG_TraceReport(pstNextMsg);
        CNAS_EHSM_MsgProc((struct MsgCB *)pstNextMsg);

        PS_MEM_FREE(pstNextMsg->ulSenderPid, pstNextMsg);

        /* 寻找下一条内部消息 */
        pstNextMsg = (MSG_HEADER_STRU*)CNAS_EHSM_GetNextIntMsg();
    }
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


