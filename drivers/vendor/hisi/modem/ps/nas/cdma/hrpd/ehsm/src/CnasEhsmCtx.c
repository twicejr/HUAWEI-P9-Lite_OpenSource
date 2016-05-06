

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "CnasEhsmProcNvim.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmFsmDeactivatingTbl.h"
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmComFunc.h"
#include "CnasEhsmEncode.h"
#include "CnasEhsmComFunc.h"
#include "CnasEhsmDecode.h"
#include "NasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_CTX_C
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_EHSM_CTX_STRU                       g_stCnasEhsmCtx;

/*****************************************************************************
  3 函数定义
*****************************************************************************/

CNAS_EHSM_CTX_STRU* CNAS_EHSM_GetEhsmCtxAddr(VOS_VOID)
{
    return &(g_stCnasEhsmCtx);
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_InitCtx
Description     :   THis function is used to init EHSM context

Input parameters:   None
Outout parameters:  None
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2014-05-14
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-09-18
        Author  :   w00176964
        Modify content :CNAS内存裁剪
*****************************************************************************/
VOS_VOID CNAS_EHSM_InitCtx(
    CNAS_EHSM_INIT_CTX_TYPE_ENUM_UINT8  enInitType
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    /* Init the Current FSM context */
    CNAS_EHSM_InitCurrFsmCtx(&(pstEhsmCtx->stCurFsm));

    /* Init the FSM Stack */
    CNAS_EHSM_InitFsmStackCtx(&(pstEhsmCtx->stFsmStack));

    /* Init the Cache message queue */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_EHSM_InitCacheMsgQueue(enInitType, &(pstEhsmCtx->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* Init the internal message queue */
    CNAS_EHSM_InitInternalBuffer(&(pstEhsmCtx->stIntMsgQueue));

    /* Init the Timer Context */
    CNAS_EHSM_InitTimerCtx(&(pstEhsmCtx->astEhsmTimerCtx[0]));

    /* Init the values of retry connection establishment info */
    CNAS_EHSM_InitRetryConnEstInfo(&(pstEhsmCtx->stRetryCtrlInfo.stRetryConnEstInfo));

    /* Init the values of retry PDN setup info  */
    CNAS_EHSM_InitRetryPdnsetupInfo(&(pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo));

    /* Init the values of PDN ids in astLocalPdnBearInfo and astLtePdnBearInfo  */
    CNAS_EHSM_InitPdnIdInLocalPdnBearInfo((pstEhsmCtx->astLocalPdnBearInfo));

    /* Init the values of PDN ids in astLtePdnBearInfo and astLtePdnBearInfo  */
    CNAS_EHSM_InitPdnIdInLtePdnBearInfo((pstEhsmCtx->astLtePdnBearInfo));

    /* Set AirLinkExist equal to VOS_FALSE */
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    /* Set AirLinkExist equal to VOS_FALSE */
    CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

    /* Set Ehrpd state */
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    CNAS_EHSM_InitEhrpdAutoAttachFlag();

    CNAS_CCB_SetCurrPsRatType(CNAS_CCB_PS_RATTYPE_NULL);
}


VOS_VOID CNAS_EHSM_ClearCtx(
    CNAS_EHSM_INIT_CTX_TYPE_ENUM_UINT8  enInitType
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    /* Init the Cache message queue */
    CNAS_EHSM_InitCacheMsgQueue(enInitType, &(pstEhsmCtx->stCacheMsgQueue));

    /* Init the internal message queue */
    CNAS_EHSM_InitInternalBuffer(&(pstEhsmCtx->stIntMsgQueue));

    /* Init the Timer Context */
    CNAS_EHSM_InitTimerCtx(&(pstEhsmCtx->astEhsmTimerCtx[0]));

    /* Init the values of retry connection establishment info */
    CNAS_EHSM_InitRetryConnEstInfo(&(pstEhsmCtx->stRetryCtrlInfo.stRetryConnEstInfo));

    /* Init the values of retry PDN setup info  */
    CNAS_EHSM_InitRetryPdnsetupInfo(&(pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo));

    /* Init the values of PDN ids in astLocalPdnBearInfo and astLtePdnBearInfo  */
    CNAS_EHSM_InitPdnIdInLocalPdnBearInfo((pstEhsmCtx->astLocalPdnBearInfo));

    /* Init the values of PDN ids in astLtePdnBearInfo and astLtePdnBearInfo  */
    CNAS_EHSM_InitPdnIdInLtePdnBearInfo((pstEhsmCtx->astLtePdnBearInfo));

    /* Set AirLinkExist equal to VOS_FALSE */
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    /* Set AirLinkExist equal to VOS_FALSE */
    CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

    /* Set Ehrpd state */
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    CNAS_CCB_SetCurrPsRatType(CNAS_CCB_PS_RATTYPE_NULL);
}



CNAS_EHSM_TIMER_CTX_STRU *CNAS_EHSM_GetTimerCtxAddr( VOS_VOID )
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->astEhsmTimerCtx[0]);
}



VOS_VOID  CNAS_EHSM_LoadSubFsm(
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId,
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm
)
{
    switch (enFsmId)
    {
        case CNAS_EHSM_FSM_ACTIVATING:
            pstCurFsm->ulState                  = CNAS_EHSM_ACTIVATING_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_EHSM_GetActivatingFsmDescAddr();
            break;
        case CNAS_EHSM_FSM_DEACTIVATING:
            pstCurFsm->ulState                  = CNAS_EHSM_DEACTIVATING_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_EHSM_GetDeactivatingFsmDescAddr();
            break;
        default:
            CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}




VOS_VOID CNAS_EHSM_InitFsmL2(
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
)
{
    CNAS_EHSM_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enCurrFsmId;

    enCurrFsmId = CNAS_EHSM_GetCurrFsmId();
    if (CNAS_EHSM_FSM_BUTT == enCurrFsmId)
    {
        /* Sending the Warning Log for this case */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitFsmL2: CNAS_EHSM_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    CNAS_EHSM_MNTN_LogFsmInfo(enCurrFsmId, CNAS_EHSM_GetFsmTopState());

    /* Getting the parent FSM ID and the Parent Event Type */
    enParentFsmId     = CNAS_EHSM_GetCurrFsmId();
    ulParentEventType = CNAS_EHSM_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* Getting the FSM stack address, Current FSM Context structure. The Current FSM context is pushed to the stack */
    pstFsmStack = CNAS_EHSM_GetFsmStackAddr();
    pstCurFsm   = CNAS_EHSM_GetCurFsmAddr();
    CNAS_EHSM_PushFsm(pstFsmStack, pstCurFsm);

    /* The current FSM context must now contain the ID of the new FSM to be loaded. */
    pstCurFsm->enFsmId = enFsmId;

    /* The current FSM context must contain the init state of the NEW FSM. The initializing function is also called. */
    CNAS_EHSM_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    enCurrFsmId = CNAS_EHSM_GetCurrFsmId();
    if (CNAS_EHSM_FSM_BUTT == enCurrFsmId)
    {
        /* Log the warning for the error case*/
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitFsmL2: CNAS_EHSM_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    CNAS_EHSM_MNTN_LogFsmInfo(enCurrFsmId, CNAS_EHSM_GetFsmTopState());
}




VOS_VOID CNAS_EHSM_PopFsm( VOS_VOID )
{
    CNAS_EHSM_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* Get the FSM Stack Address and the current FSM address */
    pstFsmStack = CNAS_EHSM_GetFsmStackAddr();
    pstCurFsm   = CNAS_EHSM_GetCurFsmAddr();

    /* If the Stack Depth is empty then return with Error Log */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_PopFsm: FSM Stack is empty");
        return;
    }

    /* Decrease the Stack depth */
    pstFsmStack->usStackDepth--;

    /* Copy the top Context in FSM stack to the Current FSM Context global structure */
    NAS_MEM_CPY_S(pstCurFsm,
                  sizeof(CNAS_EHSM_FSM_CTX_STRU),
                  &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
                  sizeof(CNAS_EHSM_FSM_CTX_STRU));
}




VOS_VOID CNAS_EHSM_PushFsm(
    CNAS_EHSM_FSM_STACK_STRU            *pstFsmStack,
    CNAS_EHSM_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;

    /* Check if the New FSM stack or the New FSM to be pushed */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM,
                       "CNAS_EHSM_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* Check if the Stack Depth is greater than the max FSM stack depth */
    if (pstFsmStack->usStackDepth >= CNAS_EHSM_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_EHSM,
                       "CNAS_EHSM_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* Get the address of the top member of the FSM stack and store it in pstCurFsm */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* Copy the New FSM to the address pointed by pstCurFsm */
    NAS_MEM_CPY_S(pstCurFsm, sizeof(CNAS_EHSM_FSM_CTX_STRU), pstNewFsm, sizeof(CNAS_EHSM_FSM_CTX_STRU));

    /* Increase the stack depth */
    pstFsmStack->usStackDepth++;

    return;
}




VOS_VOID CNAS_EHSM_QuitFsmL2(VOS_VOID)
{

    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enCurrFsmId;

    pstCurFsm = CNAS_EHSM_GetCurFsmAddr();

    /* The context specific to the current FSM is re-initialized */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = CNAS_EHSM_GetCurrFsmId();
    if (CNAS_EHSM_FSM_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_QuitFsmL2: CNAS_EHSM_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    CNAS_EHSM_MNTN_LogFsmInfo(enCurrFsmId, CNAS_EHSM_GetFsmTopState());

    /* Pop the FSM Stack Structure */
    CNAS_EHSM_PopFsm();

    enCurrFsmId = CNAS_EHSM_GetCurrFsmId();
    if (CNAS_EHSM_FSM_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_QuitFsmL2: CNAS_EHSM_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    CNAS_EHSM_MNTN_LogFsmInfo(enCurrFsmId, CNAS_EHSM_GetFsmTopState());

    return;
}




VOS_VOID  CNAS_EHSM_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_EHSM_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* Get the current FSM address*/
    pstCurFsm                   = CNAS_EHSM_GetCurFsmAddr();

    /* Set the current FSM State to the New state */
    pstCurFsm->ulState          = ulCurrState;

    /*  Log the FSM to OM. */
    CNAS_EHSM_MNTN_LogFsmInfo(pstCurFsm->enFsmId, ulCurrState);

    return;

}




VOS_UINT32 CNAS_EHSM_GetFsmTopState(VOS_VOID)
{
    return (CNAS_EHSM_GetCurFsmAddr()->ulState);
}




CNAS_EHSM_CACHE_MSG_QUEUE_STRU* CNAS_EHSM_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->stCacheMsgQueue);
}





VOS_UINT32  CNAS_EHSM_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* Check if the message size does not exceed the maximum */
    if ((CNAS_EHSM_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* If the message does not exceed max size, save in cache message queue.  */
    CNAS_EHSM_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;

}


/*****************************************************************************
Function Name   :   CNAS_EHSM_GetNextCachedMsg
Description     :   This function is used to get the next cache message.
Input parameters:   None
Output parameters:  pstEntryMsg - the next cache message.
Return Value    :   VOS_TRUE - IF message size if ok.
                    VOS_FALSE - IF message size if too long
Modify History:
    1)  Date    :   2014-05-14
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-09-09
        Author  :   w00176964
        Modify content :    CNAS内存裁剪
*****************************************************************************/

VOS_UINT32 CNAS_EHSM_GetNextCachedMsg(
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg
)
{
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU     *pstMsgQueue     = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstCacheMsgHdr  = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg     = VOS_NULL_PTR;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, end */

    pstMsgQueue = CNAS_EHSM_GetCacheMsgAddr();

    /* Check if the Cache is empty */
    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[0]);

    if (VOS_NULL_PTR == pstCacheMsgHdr)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    /* Copy the first cache message to the pstEntryMsg  */
    NAS_MEM_CPY_S(&pstEntryMsg->aucMsgBuffer[0],
                  CNAS_EHSM_MAX_MSG_BUFFER_LEN,
                  pstCacheMsgHdr,
                  pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */

    return VOS_TRUE;

}




CNAS_EHSM_FSM_CTX_STRU* CNAS_EHSM_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->stCurFsm);
}




NAS_FSM_DESC_STRU* CNAS_EHSM_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_EHSM_GetCurFsmAddr()->pstFsmDesc);
}




CNAS_EHSM_FSM_ID_ENUM_UINT32 CNAS_EHSM_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasEhsmCtx.stCurFsm.enFsmId);
}




CNAS_EHSM_MSG_STRU* CNAS_EHSM_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasEhsmCtx.stCurFsm.stEntryMsg);
}



CNAS_EHSM_FSM_STACK_STRU* CNAS_EHSM_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->stFsmStack);
}




VOS_UINT16 CNAS_EHSM_GetFsmStackDepth(VOS_VOID)
{
    CNAS_EHSM_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_EHSM_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}




CNAS_EHSM_INT_MSG_QUEUE_STRU* CNAS_EHSM_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->stIntMsgQueue);
}




VOS_VOID CNAS_EHSM_InitInternalBuffer(
    CNAS_EHSM_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_EHSM_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}




VOS_VOID CNAS_EHSM_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    /* Check if the number of internal messages is greater than Max */
    if (CNAS_EHSM_MAX_INT_MSG_QUEUE_NUM <= CNAS_EHSM_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_EHSM, pstMsg);

        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    ucIntMsgNum = CNAS_EHSM_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* Insert the message in internal message queue */
    CNAS_EHSM_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    /* Incrememt the number of internal messages */
    CNAS_EHSM_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}




VOS_UINT8 *CNAS_EHSM_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_EHSM_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* Get the first member in the queue */
        pstIntMsg = CNAS_EHSM_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* Decrement the number of internal messages */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* Shift the Queue by one place */
            NAS_MEM_MOVE_S(&(CNAS_EHSM_GetIntMsgQueueAddr()->pastIntMsg[0]),
                           (CNAS_EHSM_MAX_INT_MSG_QUEUE_NUM * sizeof(VOS_UINT8 *)),
                           &(CNAS_EHSM_GetIntMsgQueueAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* The last member must now point to NULL */
        CNAS_EHSM_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_EHSM_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}




VOS_UINT8 CNAS_EHSM_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_EHSM_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}


/*****************************************************************************
Function Name   :   CNAS_EHSM_ClearCacheMsg
Description     :   This function is used to clear a specified index in the cache message queue.
Input parameters:   ucIndex - The index to be cleared.
Output parameters:  None
Return Value    :   None.
Modify History:
    1)  Date    :   2014-05-14
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-09-09
        Author  :   w00176964
        Modify content :    CNAS内存裁剪
*****************************************************************************/

VOS_VOID CNAS_EHSM_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU     *pstMsgQueue = VOS_NULL_PTR;

    /* IF the index to be cleared is out of bounds, Return */
    if (CNAS_EHSM_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ClearCacheMsg: Attempted to clear out of bound value!");
        return;
    }

    pstMsgQueue = CNAS_EHSM_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_EHSM, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_EHSM_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* Shift the Messages from (Index + 1) to (Index). The message at (Index) is deleted */
            NAS_MEM_MOVE_S(&(pstMsgQueue->pastCacheMsg[ucIndex]),
                           ((CNAS_EHSM_MAX_CACHE_MSG_QUEUE_NUM - ucIndex) * sizeof(VOS_UINT8 *)),
                           &(pstMsgQueue->pastCacheMsg[ucIndex + 1]),
                           (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT8 *));
        }

        /* Clear the last member of the queue */
        pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum] = VOS_NULL_PTR;
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    CNAS_EHSM_MNTN_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_ClearAllCacheMsg
 功能描述  : 清除所有Cache的消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_ClearAllCacheMsg(VOS_VOID)
{
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU     *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ucIndex;

    pstMsgQueue = CNAS_EHSM_GetCacheMsgAddr();

    for ( ucIndex = 0 ; ucIndex < pstMsgQueue->ucCacheMsgNum ; ucIndex++ )
    {
        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_EHSM, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }
    }

    pstMsgQueue->ucCacheMsgNum = 0;

    CNAS_EHSM_MNTN_LogBufferQueueMsg(VOS_FALSE);

    return;
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_SaveCacheMsgInMsgQueue
Description     :   This function is used to Save a nessage in the cache message queue.
Input parameters:   ulEventType - The event type of the message
                    pstMsg      - Pointer to the message.
Output parameters:  None
Return Value    :   None.
Modify History:
    1)  Date    :   2014-05-14
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-09-09
        Author  :   w00176964
        Modify content :    CNAS内存裁剪
*****************************************************************************/

VOS_VOID CNAS_EHSM_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU     *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = CNAS_EHSM_GetCacheMsgAddr();

    /* Check if the cache message queue is full */
    if (CNAS_EHSM_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    /* Save the message to the end of the cache message queue */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
    pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum]
            = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_EHSM, pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum])
    {
        return;
    }

    NAS_MEM_CPY_S(pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum],
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH,
                  pstMsgHeader,
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    pstMsgQueue->ucCacheMsgNum++;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */

    /* Log the Buffer Queue */
    CNAS_EHSM_MNTN_LogBufferQueueMsg(VOS_FALSE);

    CNAS_INFO_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}


/*****************************************************************************
Function Name   :   CNAS_EHSM_InitCacheMsgQueue
Description     :   This function is used to Init the cache message queue.
Input parameters:   pstCacheMsgQueue - Pointer to the cache message queue.
Output parameters:  None
Return Value    :   None.
Modify History:
    1)  Date    :   2014-05-14
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-09-09
        Author  :   w00176964
        Modify content :    CNAS内存裁剪
*****************************************************************************/

VOS_VOID CNAS_EHSM_InitCacheMsgQueue(
    CNAS_EHSM_INIT_CTX_TYPE_ENUM_UINT8  enInitType,
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU     *pstCacheMsgQueue
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    VOS_UINT32                          i;

    if (CNAS_EHSM_INIT_CTX_STARTUP == enInitType)
    {
        pstCacheMsgQueue->ucCacheMsgNum = 0;

        for (i = 0; i < CNAS_EHSM_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
        }
    }
    else
    {
        for (i = 0; i < (VOS_UINT32)pstCacheMsgQueue->ucCacheMsgNum; i++)
        {
            if (VOS_NULL_PTR != pstCacheMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_EHSM, pstCacheMsgQueue->pastCacheMsg[i]);
                pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
            }
        }

        pstCacheMsgQueue->ucCacheMsgNum = 0;
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
}




VOS_VOID CNAS_EHSM_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* Get the Current entry message address from the FSM context */
    pstEntryMsg                 = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, begin */
    if (ulLen > CNAS_EHSM_MAX_MSG_BUFFER_LEN)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SaveCurEntryMsg:beyond the Size!");

        ulLen = CNAS_EHSM_MAX_MSG_BUFFER_LEN;
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, end */

    /* Save the message received in the entry message address  */
    NAS_MEM_CPY_S(&pstEntryMsg->aucMsgBuffer[0], CNAS_EHSM_MAX_MSG_BUFFER_LEN, pstMsg, ulLen);

    /* Save the event type */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}




VOS_VOID CNAS_EHSM_InitCurrFsmCtx(
    CNAS_EHSM_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_EHSM_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_EHSM_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   CNAS_EHSM_L1_STA_INACTIVE;
    pstCurrFsmCtx->enParentFsmId            =   CNAS_EHSM_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    /* Clear the Entry message buffer */
    NAS_MEM_SET_S(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
                  CNAS_EHSM_MAX_MSG_BUFFER_LEN,
                  0x00,
                  CNAS_EHSM_MAX_MSG_BUFFER_LEN);
}




VOS_VOID CNAS_EHSM_InitFsmStackCtx(
    CNAS_EHSM_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;

    for (i = 0 ; i < CNAS_EHSM_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_EHSM_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_EHSM_L1_STA_BUTT;
    }
}





VOS_VOID CNAS_EHSM_InitTimerCtx(
    CNAS_EHSM_TIMER_CTX_STRU            *pstTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TI_CNAS_EHSM_TIMER_BUTT; i++ )
    {
        pstTimerCtx[i].hTimer           = VOS_NULL_PTR;
        pstTimerCtx[i].enTimerId        = TI_CNAS_EHSM_TIMER_BUTT;
        pstTimerCtx[i].enTimerStatus    = CNAS_EHSM_TIMER_STATUS_STOP;
    }

}



VOS_VOID CNAS_EHSM_SetSessionType(
    EHSM_HSM_SESSION_TYPE_ENUM_UINT32   enSessionType
)
{
    CNAS_EHSM_GetEhsmCtxAddr()->enSessionType = enSessionType;
}



EHSM_HSM_SESSION_TYPE_ENUM_UINT32 CNAS_EHSM_GetSessionType(VOS_VOID)
{
    return CNAS_EHSM_GetEhsmCtxAddr()->enSessionType;
}


VOS_VOID CNAS_EHSM_InitRetryConnEstInfo(
    CNAS_EHSM_RETRY_CONN_EST_INFO_STRU  *pstRetryConnEstInfo
)
{
    /* Setting default values */
    pstRetryConnEstInfo->ulExpireTimerLen    = CNAS_EHSM_DEFAULT_RETRY_CONN_EST_TIMER_LENGTH;
    pstRetryConnEstInfo->usMaxNoOfRetry      = CNAS_EHSM_DEFAULT_MAX_RETRY_CONN_EST;

    /* TO Do: 从NV里读取 */
    /* CNAS_EHSM_InitConnEstRetryInfoNvim(pstRetryConnEstInfo); */
}



VOS_VOID CNAS_EHSM_SetAirLinkExistFlag(VOS_UINT32 ulAirLinkExist)
{
     CNAS_EHSM_GetEhsmCtxAddr()->ulAirLinkExist = ulAirLinkExist;
}


VOS_UINT32 CNAS_EHSM_GetAirLinkExistFlag(VOS_VOID)
{
    return CNAS_EHSM_GetEhsmCtxAddr()->ulAirLinkExist;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetEhrpdAutoAttachFlag
 功能描述  : 获取EHRPD网络下是否自动发起Attach Req
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetEhrpdAutoAttachFlag(VOS_VOID)
{
    return CNAS_EHSM_GetEhsmCtxAddr()->ulAutoAttachFlag;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetEhrpdAutoAttachFlag
 功能描述  : 设置EHRPD网络下是否自动发起Attach的标记
 输入参数  : VOS_UINT32                          ulAutoAttachFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetEhrpdAutoAttachFlag(
    VOS_UINT32                          ulAutoAttachFlag
)
{
    CNAS_EHSM_GetEhsmCtxAddr()->ulAutoAttachFlag = ulAutoAttachFlag;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromPdnConnCnf
 功能描述  : save ehrpd pdn info to local
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromPdnConnCnf(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo,
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU                      *pStPdnSetUpCnf
)
{
    /* save apn info  */
    if (0 != pStPdnSetUpCnf->stApn.ucApnLen)
    {
       pstPdnInfo->stApn.ucApnLen = pStPdnSetUpCnf->stApn.ucApnLen;

       NAS_MEM_CPY_S(pstPdnInfo->stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pStPdnSetUpCnf->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN);
    }

    /*save decod stApnAmbr */
    CNAS_EHSM_SaveApnAmbrInfo(&(pstPdnInfo->stApnAmbr), &(pStPdnSetUpCnf->stApnAmbr));

    /* save decode pdn address  info */
    if (CNAS_EHSM_CAUSE_SUCCESS != CNAS_EHSM_DecodeNwPDNValue(0,
                                                              (VOS_UINT8 *)&(pStPdnSetUpCnf->stPdnAddress),
                                                             &(pstPdnInfo->stPdnAddr)))
    {
       pstPdnInfo->stPdnAddr.enPdnType = CNAS_EHSM_PDN_TYPE_INVALID;
    }

    /* save decode pco info */
    CNAS_EHSM_SaveDecoPcoInfo(pstPdnInfo, &(pStPdnSetUpCnf->stPco));

    pstPdnInfo->ucPdnId       = pStPdnSetUpCnf->ucPdnId;
    pstPdnInfo->enAttachType  = pStPdnSetUpCnf->enAttachType;
    pstPdnInfo->enPdnType     = CNAS_EHSM_MapCttfPdnTypeToEhms(pStPdnSetUpCnf->enPdnType);

    /* attach succ ,then set this flag */
    pstPdnInfo->ucIsPdnActive = VOS_TRUE;

    NAS_MEM_CPY_S(&(pstPdnInfo->aucIpv4DefaultRouterAddress[0]), 
                  CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN,
                  &(pStPdnSetUpCnf->aucIpv4DefaultRouterAddress[0]), 
                  CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromAttachCnf
 功能描述  : save ehrpd pdn info to local
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromAttachCnf(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo,
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU                        *pStAttachCnf
)
{
    /* APN info */
    if (0 != pStAttachCnf->stApn.ucApnLen)
    {
       pstPdnInfo->stApn.ucApnLen = pStAttachCnf->stApn.ucApnLen;

       NAS_MEM_CPY_S(pstPdnInfo->stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pStAttachCnf->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN);
    }

    /* ApnAmbr info */
    CNAS_EHSM_SaveApnAmbrInfo(&(pstPdnInfo->stApnAmbr), &(pStAttachCnf->stApnAmbr));

    /* save decode pdn address  info */
    if (CNAS_EHSM_CAUSE_SUCCESS != CNAS_EHSM_DecodeNwPDNValue(0,
                                                              (VOS_UINT8 *)&(pStAttachCnf->stPdnAddress),
                                                             &(pstPdnInfo->stPdnAddr)))
    {
       pstPdnInfo->stPdnAddr.enPdnType = CNAS_EHSM_PDN_TYPE_INVALID;
    }
    pstPdnInfo->enPdnType = pstPdnInfo->stPdnAddr.enPdnType;

    /* PCO info */
    if (0 != pStAttachCnf->stPco.ucPcoLen)
    {
        CNAS_EHSM_SaveDecoPcoInfo(pstPdnInfo, &(pStAttachCnf->stPco));
    }

    /* aucIpv4DefaultRouterAddress  */
    NAS_MEM_CPY_S(&(pstPdnInfo->aucIpv4DefaultRouterAddress[0]), 
                  CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN,
                  &(pStAttachCnf->aucIpv4DefaultRouterAddress[0]), 
                  CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    pstPdnInfo->ucPdnId      = pStAttachCnf->ucPdnId;
    pstPdnInfo->usMtu        = pStAttachCnf->usMtu;
    pstPdnInfo->enAttachType = CNAS_EHSM_MapCttfAttachTypeToEhsm(pStAttachCnf->enAttachType);

    /* pdn conn succ ,then set this flag */
    pstPdnInfo->ucIsPdnActive = VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_ClearEhrpdLocalPdnInfo
 功能描述  : clear ehrpd local pdn info
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_ClearEhrpdLocalPdnInfo(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    if (ucPdnId < CNAS_EHSM_MAX_PDN_NUM)
    {
        NAS_MEM_SET_S(&(pstEhsmCtx->astLocalPdnBearInfo[ucPdnId]), 
                      sizeof(CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU), 
                      0, 
                      sizeof(CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU));
        pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucPdnId    = CNAS_EHSM_INVALID_PDN_ID;
    }

    return;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_ClearEhrpdLocalPdnInfo
 功能描述  : clear ehrpd local pdn info
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_ClearAllEhrpdLocalPdnInfo(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucInUsed)
        {
            /* Clear PDN info */
            CNAS_EHSM_ClearEhrpdLocalPdnInfo(pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucPdnId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetApnFromLteInfo
 功能描述  : 从LTE同步的承载信息中获取APN字符串
 输入参数  : CNAS_EHSM_APN_STRU                 *pstEhrpdApn
             CNAS_EHSM_APN_STRU                 *pstLteApn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_GetApnFromLteInfo(
    CNAS_EHSM_APN_STRU                 *pstEhrpdApn,
    CNAS_EHSM_APN_STRU                 *pstLteApn
)
{
    VOS_UINT8                           aucMnc[6];
    VOS_UINT8                           i;

    aucMnc[0] = 'M';
    aucMnc[1] = 'm';
    aucMnc[2] = 'N';
    aucMnc[3] = 'n';
    aucMnc[4] = 'C';
    aucMnc[5] = 'c';

    for (i = 1; i < pstLteApn->ucApnLen; i++)
    {
        /*数字后面紧接着是'M'/'m' */
        if ((aucMnc[0] == pstLteApn->aucApn[i])
         || (aucMnc[1] == pstLteApn->aucApn[i]))
        {
            /*'M'/'m'后面紧接着是'N'/'n' */
            if ((aucMnc[2] == pstLteApn->aucApn[i + 1])
             || (aucMnc[3] == pstLteApn->aucApn[i + 1]))
            {
                /*'N'/'n'后面紧接着是'C'/'c' */
                if ((aucMnc[4] == pstLteApn->aucApn[i + 2])
                 || (aucMnc[5] == pstLteApn->aucApn[i + 2]))
                {
                    pstEhrpdApn->ucApnLen = i - 1;
                    NAS_MEM_CPY_S(pstEhrpdApn->aucApn, CNAS_EHSM_MAX_APN_LEN, pstLteApn->aucApn, pstEhrpdApn->ucApnLen);
                    return;
                }
            }
        }

    }

    pstEhrpdApn->ucApnLen = pstLteApn->ucApnLen;
    NAS_MEM_CPY_S(pstEhrpdApn->aucApn, CNAS_EHSM_MAX_APN_LEN, pstLteApn->aucApn, pstEhrpdApn->ucApnLen);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SaveApnInfoWithEsmPdnInfo
 功能描述  : save apn info to lte local pdn info
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SaveApnInfoWithEsmPdnInfo(
    CNAS_EHSM_APN_STRU                 *pstApn,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    if ((pstSynPdnInfo->stApn.ucApnLen > 0)
     && (1 == pstSynPdnInfo->bitOpApn))
    {
        /* 当前APN有MNC,MMC标签时需要去除 */
        /* PCLINT修改，目前EHSM_ESM_APN_STRU、CNAS_EHSM_APN_STRU结构一致，可以强转 */
        CNAS_EHSM_GetApnFromLteInfo(pstApn, (CNAS_EHSM_APN_STRU *)&(pstSynPdnInfo->stApn));
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SavePdnAddressWithEsmPdnInfo
 功能描述  : save pdn address info
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SavePdnAddressWithEsmPdnInfo(
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    NAS_MEM_CPY_S(&(pstPdnAddr->aucIpv4Addr[0]), 
                  CNAS_EHSM_IPV4_ADDR_LEN, 
                  &(pstSynPdnInfo->stPdnAddr.aucIpv4Addr[0]), 
                  CNAS_EHSM_IPV4_ADDR_LEN);
    NAS_MEM_CPY_S(&(pstPdnAddr->aucIpv6Addr[0]), 
                  CNAS_EHSM_IPV6_ADDR_LEN, 
                  &(pstSynPdnInfo->stPdnAddr.aucIpv6Addr[0]), 
                  CNAS_EHSM_IPV6_ADDR_LEN);
    pstPdnAddr->enPdnType = pstSynPdnInfo->stPdnAddr.enPdnType;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SavePcoIpv4ItemWithEsmPdnInfo
 功能描述  : save PcoIpv4Item
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SavePcoIpv4ItemWithEsmPdnInfo(
    CNAS_EHSM_PCO_IPV4_ITEM_STRU       *pstPcoIpv4Item,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    if ((1 == pstSynPdnInfo->bitOpPcoIpv4Item)
     && ((1 == pstSynPdnInfo->stPcoIpv4Item.bitOpPriDns)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpSecDns)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpGateWay)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpPriNbns)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpSecNbns)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpPriPcscf)
     || (1 == pstSynPdnInfo->stPcoIpv4Item.bitOpSecPcscf)))
    {
        NAS_MEM_CPY_S(pstPcoIpv4Item, sizeof(CNAS_EHSM_PCO_IPV4_ITEM_STRU), &(pstSynPdnInfo->stPcoIpv4Item), sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SavePcoIpv6ItemWithEsmPdnInfo
 功能描述  : save PcoIpv6Item
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SavePcoIpv6ItemWithEsmPdnInfo(
    CNAS_EHSM_PCO_IPV6_ITEM_STRU       *pstPcoIpv6Item,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    if ((1 == pstSynPdnInfo->bitOpPcoIpv6Item)
     && ((1 == pstSynPdnInfo->stPcoIpv6Item.bitOpPriDns)
      || (1 == pstSynPdnInfo->stPcoIpv6Item.bitOpSecDns)
      || (1 == pstSynPdnInfo->stPcoIpv6Item.bitOpPriPcscf)
      || (1 == pstSynPdnInfo->stPcoIpv6Item.bitOpSecPcscf)))
    {
        NAS_MEM_CPY_S(pstPcoIpv6Item, sizeof(CNAS_EHSM_PCO_IPV6_ITEM_STRU), &(pstSynPdnInfo->stPcoIpv6Item), sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU));
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SaveApnAmbrWithEsmPdnInfo
 功能描述  : save apn ambr
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SaveApnAmbrWithEsmPdnInfo(
    CNAS_EHSM_APN_AMBR_STRU            *pstApnAmbr,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    if ((1 == pstSynPdnInfo->bitOpApnAmbr)
     && ((1 == pstSynPdnInfo->stApnAmbr.bitOpDLApnAmbr)
      || (1 == pstSynPdnInfo->stApnAmbr.bitOpULApnAmbr)
      || (1 == pstSynPdnInfo->stApnAmbr.bitOpDLApnAmbrExt)
      || (1 == pstSynPdnInfo->stApnAmbr.bitOpULApnAmbrExt)
      || (1 == pstSynPdnInfo->stApnAmbr.bitOpDLApnAmbrExt2)
      || (1 == pstSynPdnInfo->stApnAmbr.bitOpULApnAmbrExt2)))
    {
        CNAS_EHSM_SaveApnAmbrInfo(pstApnAmbr, (CNAS_CTTF_EHRPD_APN_AMBR_STRU *)&(pstSynPdnInfo->stApnAmbr));
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SaveLteLocalPdnInfo
 功能描述  : save lte local pdn info
 输入参数  : ucPdnId
             VOS_UINT8                         ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SaveLteLocalPdnInfo(
    VOS_UINT8                           ucIndex,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo
)
{
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU   *pstPdnInfo = VOS_NULL_PTR;

    pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo[ucIndex]);

    pstPdnInfo->ucCid       = CNAS_EHSM_GetCidFromLteBitCid(pstSynPdnInfo->ulBitCid);
    pstPdnInfo->ulEpsbId    = pstSynPdnInfo->ulEpsbId;
    pstPdnInfo->ucInUsed    = VOS_TRUE;

    /* save pdn address info */
    CNAS_EHSM_SavePdnAddressWithEsmPdnInfo(&(pstPdnInfo->stPdnAddr), pstSynPdnInfo);
    pstPdnInfo->enPdnType           = pstSynPdnInfo->stPdnAddr.enPdnType;

    /* save apn info */
    CNAS_EHSM_SaveApnInfoWithEsmPdnInfo(&(pstPdnInfo->stApn), pstSynPdnInfo);

    /* save pco info */
    CNAS_EHSM_SavePcoIpv4ItemWithEsmPdnInfo(&(pstPdnInfo->stPcoIpv4Item), pstSynPdnInfo);
    CNAS_EHSM_SavePcoIpv6ItemWithEsmPdnInfo(&(pstPdnInfo->stPcoIpv6Item), pstSynPdnInfo);

    /* save apn ambr info */
    CNAS_EHSM_SaveApnAmbrWithEsmPdnInfo(&(pstPdnInfo->stApnAmbr), pstSynPdnInfo);
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_ClearLteLocalPdnInfo
 功能描述  : clear lte pdn info
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : y00322978
    修改内容   : 新生成函数
  2. Date:  2015-06-05
    Author: K00902809
    Description:    Need to find cid value from EHSM Pdn info
                    Find pdn info (with the above result) from LTE pdn info and clean.
*****************************************************************************/
VOS_VOID CNAS_EHSM_ClearLteLocalPdnInfo(
    VOS_UINT8                           ucCid
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx  = VOS_NULL_PTR;
    UINT8                               ucIndex     = 0;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    for (ucIndex = 0; ucIndex < CNAS_EHSM_MAX_PDN_NUM; ucIndex++)
    {
        if ((pstEhsmCtx->astLtePdnBearInfo[ucIndex].ucInUsed == VOS_TRUE)
          &&(pstEhsmCtx->astLtePdnBearInfo[ucIndex].ucCid == ucCid))
        {
            break;
        }
    }

    if (ucIndex < CNAS_EHSM_MAX_PDN_NUM)
    {
        NAS_MEM_SET_S(&(pstEhsmCtx->astLtePdnBearInfo[ucIndex]), 
                       sizeof(CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU),
                       0x00, 
                       sizeof(CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU));
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_ClearLteLocalPdnInfo
 功能描述  : clear lte pdn info
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_ClearAllLteLocalPdnInfo(VOS_VOID)
{
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU   *pstLtePdnBearInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstLtePdnBearInfo = CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo;
    /* Clear LTE local PDN info*/
    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if (VOS_TRUE == pstLtePdnBearInfo[ulLoop].ucInUsed)
        {
            CNAS_EHSM_ClearLteLocalPdnInfo(pstLtePdnBearInfo[ulLoop].ucCid);
        }
    }

}


VOS_VOID CNAS_EHSM_InitRetryPdnsetupInfo(
    CNAS_EHSM_RETRY_PDN_SETUP_INFO_STRU  *pstRetryPdnSetupInfo
)
{
    /* Setting default values */
    pstRetryPdnSetupInfo->ulExpireTimerLen  = CNAS_EHSM_DEFAULT_RETRY_PDN_SETUP_TIMER_LENGTH;
    pstRetryPdnSetupInfo->usMaxNoOfRetry    = CNAS_EHSM_DEFAULT_MAX_RETRY_PDN_SETUP;

    CNAS_EHSM_InitPdnSetupRetryInfoNvim(pstRetryPdnSetupInfo);

    CNAS_EHSM_InitApnRetryInfo();
}



VOS_VOID CNAS_EHSM_InitPdnIdInLocalPdnBearInfo(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearerInfo
)
{
    VOS_UINT32                          ulLoop = 0;

    while (CNAS_EHSM_MAX_PDN_NUM > ulLoop)
    {
        NAS_MEM_SET_S(&(pstLocalPdnBearerInfo[ulLoop]), 
                      sizeof(CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU),
                      0, 
                      sizeof(CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU));
        pstLocalPdnBearerInfo[ulLoop].ucPdnId       = CNAS_EHSM_INVALID_PDN_ID;
        pstLocalPdnBearerInfo[ulLoop].ucInUsed      = VOS_FALSE;
        pstLocalPdnBearerInfo[ulLoop].ucIsPdnActive = VOS_FALSE;
        pstLocalPdnBearerInfo[ulLoop].enAttachType  = CNAS_EHSM_ATTACH_TYPE_ENUM_BUTT;
        ulLoop++;
    }

}


VOS_VOID CNAS_EHSM_InitPdnIdInLtePdnBearInfo(
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU *pstLtePdnBearerInfo
)
{
    NAS_MEM_SET_S(&(pstLtePdnBearerInfo[0]), 
                  sizeof(CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU) * CNAS_EHSM_MAX_PDN_NUM,
                  0x00, 
                  sizeof(CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU) * CNAS_EHSM_MAX_PDN_NUM);
}


VOS_UINT32 CNAS_EHSM_IsPdnActived(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx  = VOS_NULL_PTR;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    if ( (ucPdnId < CNAS_EHSM_MAX_PDN_NUM)
      && (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucInUsed)
      && (ucPdnId == pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucPdnId)
      && (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucIsPdnActive))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 CNAS_EHSM_GetLocalActivePdnConnNum(VOS_VOID)
{
    VOS_UINT32                          ulPdnConnNum;
    VOS_UINT32                          i;

    ulPdnConnNum = 0;
    i            = 0;

    while (CNAS_EHSM_MAX_PDN_NUM > i)
    {
        if ((VOS_TRUE == g_stCnasEhsmCtx.astLocalPdnBearInfo[i].ucInUsed)
          && (VOS_TRUE == g_stCnasEhsmCtx.astLocalPdnBearInfo[i].ucIsPdnActive))
        {
            ulPdnConnNum++;
        }
        i++;
    }

    return ulPdnConnNum;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetLteActivePdnNum
 功能描述  : 获取LTE激活的PDN NUM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetLteActivePdnNum(VOS_VOID)
{
    VOS_UINT32                          ulLteActivePdnNum;
    VOS_UINT32                          ulIndex;

    ulLteActivePdnNum = 0;
    ulIndex           = 0;

    while (ulIndex < CNAS_EHSM_MAX_PDN_NUM)
    {
        if (VOS_TRUE == g_stCnasEhsmCtx.astLtePdnBearInfo[ulIndex].ucInUsed)
        {
            ulLteActivePdnNum++;
        }

        ulIndex++;
    }

    return ulLteActivePdnNum;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetLocalAllocatedPdnIdNum
 功能描述  : 获取当前已经分配的PdnId
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetLocalAllocatedPdnIdNum(VOS_VOID)
{
    VOS_UINT32                          ulPdnNum;
    VOS_UINT32                          i;

    ulPdnNum = 0;
    i        = 0;

    while (i < CNAS_EHSM_MAX_PDN_NUM)
    {
        if (VOS_TRUE == g_stCnasEhsmCtx.astLocalPdnBearInfo[i].ucInUsed)
        {
            ulPdnNum++;
        }

        i++;
    }

    return ulPdnNum;
}


VOS_UINT8  CNAS_EHSM_AllocPdnId(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucPdnId;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    /*  If the entry message is Initial attach or hand over attach: */
    ucPdnId = CNAS_EHSM_INVALID_PDN_ID;
    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    /*  Allocate PDNid */
    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if (VOS_FALSE == pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucInUsed)
        {
            ucPdnId = (VOS_UINT8)ulLoop;
            pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucInUsed = VOS_TRUE;
            pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucPdnId  = ucPdnId;
            break;
        }
    }

    return ucPdnId;
}


VOS_UINT8  CNAS_EHSM_GetLtePdnUnusedIndex(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    /*  Find first unused entry */
    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if (VOS_FALSE == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ucInUsed)
        {
            pstEhsmCtx->astLtePdnBearInfo[ulLoop].ucInUsed = VOS_TRUE;
            break;
        }
    }

    return (VOS_UINT8)ulLoop;
}


CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU*  CNAS_EHSM_GetLtePdnInfoByEpsbId(
    VOS_UINT32                          ulEpsbId
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    /*  Find cid in astLtePdnBearInfo */
    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if (ulEpsbId == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ulEpsbId)
        {
            return &(pstEhsmCtx->astLtePdnBearInfo[ulLoop]);
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_InitFsmCtx_Activating
 功能描述  : Initialize the context for FSM ACTIVATING
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月26日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_InitFsmCtx_Activating(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    /* Check Current Fsm is ACTIVATING */
    if (CNAS_EHSM_FSM_ACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitFsmCtx_Activating:ENTERED");

        return;
    }

    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.stRetryInfo.usCurConnEstRetryTimes  = 0;
    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.stRetryInfo.usLcpOtherFailRetryTimes = 0;
    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.ucPdnId           = CNAS_EHSM_INVALID_PDN_ID;
    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.ucAbortFlag       = VOS_FALSE;
    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.ulAbortEventType  = 0;
    pstEhsmCtx->stCurFsm.unFsmCtx.stActivatingCtx.ucSendPdnActFlag  = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_InitFsmCtx_Deactivating
 功能描述  : Initialize the context for FSM DEACTIVATING
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月26日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_InitFsmCtx_Deactivating(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    /* Check Current Fsm is DEACTIVATING */
    if (CNAS_EHSM_FSM_DEACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitFsmCtx_Deactivating:ENTERED");

        return;
    }

    pstEhsmCtx->stCurFsm.unFsmCtx.stDeactivatingCtx.stRetryInfo.usCurConnEstRetryTimes  = 0;
    pstEhsmCtx->stCurFsm.unFsmCtx.stDeactivatingCtx.ucAbortFlag         = VOS_FALSE;
    pstEhsmCtx->stCurFsm.unFsmCtx.stDeactivatingCtx.ulAbortEventType    = 0;
    pstEhsmCtx->stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDeactFlag  = VOS_FALSE;
    pstEhsmCtx->stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDetachFlag = VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetRetryInfo_Activating
 功能描述  : Get Retry Info for Activating process
 输入参数  : 无
 输出参数  : 无
 返 回 值  : address for retry info
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU* CNAS_EHSM_GetRetryInfo_Activating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetRetryInfo_Activating: Wrong state ENTERED");
    }

    return &g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.stRetryInfo;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetRetryInfo_Deactivating
 功能描述  : Get Retry Info for Deactivating process
 输入参数  : 无
 输出参数  : 无
 返 回 值  : address for retry info
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_EHSM_DEACTIVATING_RETRY_INFO_STRU* CNAS_EHSM_GetRetryInfo_Deactivating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_DEACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetRetryInfo_Activating: Wrong state ENTERED");
    }

    return &g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.stRetryInfo;
}


VOS_UINT8 CNAS_EHSM_CheckLtePdnIsActive(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
    {
        if (VOS_TRUE == pstEhsmCtx->astLtePdnBearInfo[i].ucInUsed)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetPdnIdByCid
 功能描述  : 根据CID获取PDN ID
 输入参数  : ucCid: CID的值
 输出参数  : 无
 返 回 值  : PDN ID的值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   CNAS_EHSM_GetPdnIdByCid(
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulLoop;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if ( (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucInUsed)
          && (ucCid == pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucCid))
        {
            return pstEhsmCtx->astLocalPdnBearInfo[ulLoop].ucPdnId;
        }
    }

    return CNAS_EHSM_INVALID_PDN_ID;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetCidByPdnId
 功能描述  : 获取CID
 输入参数  : VOS_UINT8                           ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetCidByPdnId(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();
    return pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucCid;

}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetEpsbIdByPdnId
 功能描述  : 根据PdnId获取ulEpsbId
 输入参数  : VOS_UINT8                           ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetEpsbIdByPdnId(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();
    return pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ulEpsbId;
}


VOS_UINT8   CNAS_EHSM_GetLtePdnInfoIndexByEpsbId(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulLoop;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        if ( (VOS_TRUE == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ucInUsed)
          && (ulEpsbId == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ulEpsbId))
        {
            return (VOS_UINT8)ulLoop;
        }
    }

    return CNAS_EHSM_INVALID_PDN_ID;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetPdnId_Activating
 功能描述  : Get Pdn Id
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Pdn Id
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetPdnId_Activating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetPdnId_Activating: Wrong state ENTERED");
    }

    return CNAS_EHSM_GetCurFsmAddr()->unFsmCtx.stActivatingCtx.ucPdnId;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetPdnIdCid_Activating
 功能描述  : 更新当前激活状态机的PDNID/CID信息
 输入参数  : VOS_UINT8                           ucPdnId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月3日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetPdnIdCid_Activating(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid
)
{
    CNAS_EHSM_SetPdnId_Activating(ucPdnId);

    CNAS_EHSM_SetCid_Activating(ucCid);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetPdnId_Activating
 功能描述  : Set Pdn Id
 输入参数  : VOS_UINT8:PDN ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetPdnId_Activating(
    VOS_UINT8                           ucPdnId
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    CNAS_EHSM_GetCurFsmAddr()->unFsmCtx.stActivatingCtx.ucPdnId = ucPdnId;
}


VOS_VOID CNAS_EHSM_SetCid_Activating(
    VOS_UINT8                           ucCid
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetCid_Activating: Wrong state ENTERED");
    }

    CNAS_EHSM_GetCurFsmAddr()->unFsmCtx.stActivatingCtx.ucCid = ucCid;
}


VOS_VOID CNAS_EHSM_GetSdfParaAndSaveLocalPdnInfo(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulLoop;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearInfo = VOS_NULL_PTR;
    APS_EHSM_SDF_PARA_INFO_STRU         stSdfParaInfo;

    pstLocalPdnBearInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    NAS_MEM_SET_S(&stSdfParaInfo, sizeof(APS_EHSM_SDF_PARA_INFO_STRU), 0, sizeof(APS_EHSM_SDF_PARA_INFO_STRU));

    for (ulLoop = 0; ulLoop < CNAS_EHSM_CID_NV_NUM; ulLoop++)
    {
        if (VOS_TRUE == CNAS_EHSM_GetCidSdfParaInfoForEhsm((VOS_UINT8)ulLoop, &stSdfParaInfo))
        {
            break;
        }
    }

    /* NO PDP CTX */
    if (ulLoop >= CNAS_EHSM_CID_NV_NUM)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetSdfParaAndSaveLocalPdnInfo: Not able to find used Cid from APS");
    }

    /* Copy all the details from stSdfParaInfo to  pstLocalPdnBearInfo */
    pstLocalPdnBearInfo->ucCid      = ucCid;
    pstLocalPdnBearInfo->ucPdnId    = ucPdnId;
    pstLocalPdnBearInfo->ulEpsbId   = ucPdnId + CNAS_EHSM_MIN_EPSB_ID;

    pstLocalPdnBearInfo->enAuthType = CNAS_EHSM_MapApsAuthTypeToEhsm(stSdfParaInfo.enAuthType);

    if (VOS_TRUE == stSdfParaInfo.bitOpPdnType)
    {
        pstLocalPdnBearInfo->enPdnType = CNAS_EHSM_MapApsPdnTypeToEhsm(stSdfParaInfo.enPdnType);
    }
    else
    {
        pstLocalPdnBearInfo->enPdnType = CNAS_EHSM_PDN_TYPE_IPV4;
    }

    if (VOS_TRUE == stSdfParaInfo.bitOpAuthInfo)
    {
        pstLocalPdnBearInfo->ucUserNameLen = stSdfParaInfo.ucUserNameLen;
        pstLocalPdnBearInfo->ucPwdLen      = stSdfParaInfo.ucPwdLen;

        NAS_MEM_CPY_S(pstLocalPdnBearInfo->aucUserName,
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN,
                      stSdfParaInfo.aucUserName,
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        NAS_MEM_CPY_S(pstLocalPdnBearInfo->aucPwd,
                      CNAS_EHSM_MAX_AUTHDATA_PASSWORD_LEN,
                      stSdfParaInfo.aucPwd,
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);
    }

    if (VOS_TRUE == stSdfParaInfo.bitOpApn)
    {
        /* EHSM保存编码后的APN */
        CNAS_EHSM_EncodeApn((CNAS_EHSM_APN_STRU *)&stSdfParaInfo.stApn,
                            pstLocalPdnBearInfo->stApn.aucApn,
                            &pstLocalPdnBearInfo->stApn.ucApnLen);

    }

    return;
}



VOS_VOID CNAS_EHSM_LoadLocalPdnInfoFromLteInfo(
    VOS_UINT8                           ucLocPdnId,
    VOS_UINT8                           ucLtePdnIndex
)
{
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearInfo = VOS_NULL_PTR;
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU   *pstLtePdnBearInfo   = VOS_NULL_PTR;
    APS_EHSM_SDF_PARA_INFO_STRU         stSdfParaInfo;

    NAS_MEM_SET_S(&stSdfParaInfo, sizeof(APS_EHSM_SDF_PARA_INFO_STRU), 0, sizeof(APS_EHSM_SDF_PARA_INFO_STRU));

    pstLocalPdnBearInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucLocPdnId]);
    pstLtePdnBearInfo   = &(CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo[ucLtePdnIndex]);

    pstLocalPdnBearInfo->ucCid      = pstLtePdnBearInfo->ucCid;
    pstLocalPdnBearInfo->enPdnType  = pstLtePdnBearInfo->enPdnType;
    pstLocalPdnBearInfo->ulEpsbId   = pstLtePdnBearInfo->ulEpsbId;

    /* 当前APN有MNC,MMC标签时需要去除 */
    CNAS_EHSM_GetApnFromLteInfo(&(pstLocalPdnBearInfo->stApn), &(pstLtePdnBearInfo->stApn));


    /* APN AMBER */
    NAS_MEM_CPY_S(&pstLocalPdnBearInfo->stApnAmbr,
                  sizeof(CNAS_EHSM_APN_AMBR_STRU),
                  &pstLtePdnBearInfo->stApnAmbr,
                  sizeof(CNAS_EHSM_APN_AMBR_STRU));

    /* Copy all the details from stSdfParaInfo to  pstLocalPdnBearInfo */
    if (VOS_FALSE == CNAS_EHSM_GetCidSdfParaInfoForEhsm(pstLocalPdnBearInfo->ucCid, &stSdfParaInfo))
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_LoadLocalPdnInfoFromLteInfo: TAF_APS_GetCidSdfParaInfoForEhsm returns FAILURE");
        return;
    }

    /* AuthInfo */
    if (VOS_TRUE == stSdfParaInfo.bitOpAuthInfo)
    {
        NAS_MEM_CPY_S(pstLocalPdnBearInfo->aucUserName, 
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN, 
                      stSdfParaInfo.aucUserName, 
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);
        NAS_MEM_CPY_S(pstLocalPdnBearInfo->aucPwd, 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN,
                      stSdfParaInfo.aucPwd, 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);
    }

    return;
}



VOS_UINT8 CNAS_EHSM_GetCid_Activating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING!= CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetCid_Activating: Wrong state ENTERED");
    }

    return CNAS_EHSM_GetCurFsmAddr()->unFsmCtx.stActivatingCtx.ucCid;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetAbortFlag_Activating
 功能描述  : set the abort msg flag in Activating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetAbortFlag_Activating(
    VOS_UINT8                 ucAbortFlag
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ucAbortFlag = ucAbortFlag;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetInternalMsgAbortFlag_Activating
 功能描述  : get the abort msg flag in Activating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetAbortFlag_Activating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ucAbortFlag;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetInternalMsgAbortFlag_Deactivating
 功能描述  : set the abort msg flag in Deactivating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetAbortFlag_Deactivating(
    VOS_UINT8                 ucAbortFlag
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucAbortFlag = ucAbortFlag;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetInternalMsgAbortFlag_Deactivating
 功能描述  : get the abort msg flag in Deactivating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetAbortFlag_Deactivating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucAbortFlag;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetSendPdnActFlag_Activating
 功能描述  : 记录是否发过Pdn激活请求
 输入参数  : VOS_UINT8                           ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetSendPdnActFlag_Activating(
    VOS_UINT8                           ucFlag
)
{
    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ucSendPdnActFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetSendPdnActFlag_Activating
 功能描述  : 获取是否已经发送过Pdn激活请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetSendPdnActFlag_Activating(VOS_VOID)
{
    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ucSendPdnActFlag;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetSendPdnDeactFlag_Deactivating
 功能描述  : 记录是否已经发送过Pdn去激活请求
 输入参数  : VOS_UINT8                           ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetSendPdnDeactFlag_Deactivating(
    VOS_UINT8                           ucFlag
)
{
    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDeactFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetSendPdnDeactFlag_Deactivating
 功能描述  : 获取Pdn去激活请求发送标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetSendPdnDeactFlag_Deactivating(VOS_VOID)
{
    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDeactFlag;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetSendPdnDetachFlag_Deactivating
 功能描述  : 设置Pdn Detach请求发送标记
 输入参数  : VOS_UINT8                           ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetSendPdnDetachFlag_Deactivating(
    VOS_UINT8                           ucFlag
)
{
    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDetachFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetSendPdnDetachFlag_Deactivating
 功能描述  : 获取Pdn Detach请求的发送标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetSendPdnDetachFlag_Deactivating(VOS_VOID)
{
    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ucSendPdnDetachFlag;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetEhrpdState
 功能描述  : 获取EHRPD下承载的状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_EHSM_EHRPD_STA_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月1日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_EHSM_EHRPD_STA_ENUM_UINT32 CNAS_EHSM_GetEhrpdState(VOS_VOID)
{
    return g_stCnasEhsmCtx.enEhrpdState;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetEhrpdState
 功能描述  : 设置EHRPD下承载的状态
 输入参数  : CNAS_EHSM_EHRPD_STA_ENUM_UINT32     enState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月1日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetEhrpdState(
    CNAS_EHSM_EHRPD_STA_ENUM_UINT32     enState
)
{
    g_stCnasEhsmCtx.enEhrpdState = enState;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetAbortEventType_Activating
 功能描述  : set the abort msg event type in Activating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetAbortEventType_Activating(
    VOS_UINT32                ulAbortEventType
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ulAbortEventType = ulAbortEventType;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetAbortEventType_Activating
 功能描述  : get the abort msg event type in Activating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetAbortEventType_Activating(VOS_VOID)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    return g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stActivatingCtx.ulAbortEventType;
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetAbortEventType_Deactivating
 功能描述  : set the abort msg event type in Deactivating fsm ctx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SetAbortEventType_Deactivating(
    VOS_UINT32                ulAbortEventType
)
{
    if (CNAS_EHSM_FSM_ACTIVATING != CNAS_EHSM_GetCurrFsmId())
    {
        /* abnormal */
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SetPdnId_Activating: Wrong state ENTERED");
    }

    g_stCnasEhsmCtx.stCurFsm.unFsmCtx.stDeactivatingCtx.ulAbortEventType = ulAbortEventType;
}



/*****************************************************************************
 函 数 名  : CNAS_EHSM_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg:栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_EHSM_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_EHSM_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_EHSM_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  CNAS_EHSM_GetFsmStackPopFlg( VOS_VOID )
{
    CNAS_EHSM_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_EHSM_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


VOS_VOID CNAS_EHSM_SaveDecoPcoInfo(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo,
    CNAS_CTTF_EHRPD_PCO_STRU                               *pStPcoInfo
)
{
    CNAS_EHSM_CONTEXT_PCO_STRU          stMsgIE;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enCause;

    NAS_MEM_SET_S(&(stMsgIE), sizeof(CNAS_EHSM_CONTEXT_PCO_STRU), 0, sizeof(CNAS_EHSM_CONTEXT_PCO_STRU));

    enCause = CNAS_EHSM_DecodePco(pStPcoInfo->ucPcoLen, pStPcoInfo->aucPco, &stMsgIE);
    if ((0 != pStPcoInfo->ucPcoLen)
     && (CNAS_EHSM_CAUSE_SUCCESS == enCause))
    {
       /* 当前DHCP不支持DHCPv4的协商，EHRPD模式下需要打桩 */
       pstPdnInfo->stPcoIpv4Item.bitOpPriDns = 1;

       if (1 == stMsgIE.ucIpv4DnsSerNum)
       {

            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN,
                          &(stMsgIE.astIpv4DnsServer[0].aucIpV4Addr[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN);
       }
       else if (2 == stMsgIE.ucIpv4DnsSerNum)
       {
            pstPdnInfo->stPcoIpv4Item.bitOpPriDns = 1;
            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN,
                          &(stMsgIE.astIpv4DnsServer[0].aucIpV4Addr[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN);
            pstPdnInfo->stPcoIpv4Item.bitOpSecDns= 1;
            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN,
                          &(stMsgIE.astIpv4DnsServer[1].aucIpV4Addr[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN);
       }
       else
       {
       }

       if (1 == stMsgIE.ucIpv6DnsSerNum)
       {
            pstPdnInfo->stPcoIpv6Item.bitOpPriDns = 1;
            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), 
                          CNAS_EHSM_IPV6_DNS_LEN,
                          &(stMsgIE.astIpv6DnsServer[0].aucIpV6Addr[0]), 
                          CNAS_EHSM_IPV6_ADDR_LEN);
       }
       else if (2 == stMsgIE.ucIpv6DnsSerNum)
       {
            pstPdnInfo->stPcoIpv6Item.bitOpPriDns = 1;
            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]),
                          CNAS_EHSM_IPV6_DNS_LEN,
                          &(stMsgIE.astIpv6DnsServer[0].aucIpV6Addr[0]), 
                          CNAS_EHSM_IPV6_ADDR_LEN);
            pstPdnInfo->stPcoIpv6Item.bitOpSecDns= 1;
            NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), 
                          CNAS_EHSM_IPV6_DNS_LEN, 
                          &(stMsgIE.astIpv6DnsServer[1].aucIpV6Addr[0]), 
                          CNAS_EHSM_IPV6_ADDR_LEN);
       }
       else
       {
       }
    }

}


VOS_VOID CNAS_EHSM_SaveApnAmbrInfo(
    CNAS_EHSM_APN_AMBR_STRU                                *pstLocalApnAmbr,
    CNAS_CTTF_EHRPD_APN_AMBR_STRU                          *pstApnAmbr
)
{
    if (1 == pstApnAmbr->bitOpDLApnAmbr)
    {
       pstLocalApnAmbr->ucDLApnAmbr = pstApnAmbr->ucDLApnAmbr;
       pstLocalApnAmbr->bitOpDLApnAmbr = 1;
    }

    if (1 == pstApnAmbr->bitOpULApnAmbr)
    {
       pstLocalApnAmbr->ucULApnAmbr = pstApnAmbr->ucULApnAmbr;
       pstLocalApnAmbr->bitOpULApnAmbr = 1;
    }

    if (1 == pstApnAmbr->bitOpDLApnAmbrExt)
    {
       pstLocalApnAmbr->ucDLApnAmbrExt = pstApnAmbr->ucDLApnAmbrExt;
       pstLocalApnAmbr->bitOpDLApnAmbrExt = 1;
    }

    if (1 == pstApnAmbr->bitOpULApnAmbrExt)
    {
       pstLocalApnAmbr->ucULApnAmbrExt = pstApnAmbr->ucULApnAmbrExt;
       pstLocalApnAmbr->bitOpULApnAmbrExt = 1;
    }

    if (1 == pstApnAmbr->bitOpDLApnAmbrExt2)
    {
       pstLocalApnAmbr->ucDLApnAmbrExt2 = pstApnAmbr->ucDLApnAmbrExt2;
       pstLocalApnAmbr->bitOpDLApnAmbrExt2 = 1;
    }

    if (1 == pstApnAmbr->bitOpULApnAmbrExt2)
    {
       pstLocalApnAmbr->ucULApnAmbrExt2 = pstApnAmbr->ucULApnAmbrExt2;
       pstLocalApnAmbr->bitOpULApnAmbrExt2 = 1;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_FillPcoInfoForSyncPndInfoInd
 功能描述  : 设置ID_EHSM_ESM_SYNC_PDN_INFO_IND 对应结构体中的pco info
 输入参数  :
            EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
            CNAS_EHSM_PCO_IPV4_ITEM_STRU       *pstPcoIpv4Item,
            CNAS_EHSM_PCO_IPV6_ITEM_STRU       *pstPcoIpv6Item

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_FillPcoInfoForSyncPndInfoInd(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
    CNAS_EHSM_PCO_IPV4_ITEM_STRU       *pstPcoIpv4Item,
    CNAS_EHSM_PCO_IPV6_ITEM_STRU       *pstPcoIpv6Item
)
{
    /* stPcoIpv4Item */
    if ((1 == pstPcoIpv4Item->bitOpPriDns)
     || (1 == pstPcoIpv4Item->bitOpSecDns)
     || (1 == pstPcoIpv4Item->bitOpGateWay)
     || (1 == pstPcoIpv4Item->bitOpPriNbns)
     || (1 == pstPcoIpv4Item->bitOpSecNbns)
     || (1 == pstPcoIpv4Item->bitOpPriPcscf)
     || (1 == pstPcoIpv4Item->bitOpSecPcscf))
    {
        NAS_MEM_CPY_S(&(pstMsg->stPcoIpv4Item), 
                      sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU),
                      pstPcoIpv4Item, 
                      sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
        pstMsg->bitOpPcoIpv4Item = 1;
    }

    /* stPcoIpv6Item */
    if ((1 == pstPcoIpv6Item->bitOpPriDns)
     || (1 == pstPcoIpv6Item->bitOpSecDns)
     || (1 == pstPcoIpv6Item->bitOpPriPcscf)
     || (1 == pstPcoIpv6Item->bitOpSecPcscf))
    {
        NAS_MEM_CPY_S(&(pstMsg->stPcoIpv6Item), 
                      sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU),
                      pstPcoIpv6Item, 
                      sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU));
        pstMsg->bitOpPcoIpv6Item = 1;
    }

}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_FillPdnAddrInfoForSyncPndInfoInd
 功能描述  : 设置ID_EHSM_ESM_SYNC_PDN_INFO_IND 对应结构体中的pdn address info
 输入参数  :
            EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
            CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_FillPdnAddrInfoForSyncPndInfoInd(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr
)
{
    /* fill pdn address info */
    if (CNAS_EHSM_PDN_TYPE_IPV4 == pstPdnAddr->enPdnType)
    {
        NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_ESM_IPV4_ADDR_LEN, &(pstPdnAddr->aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
        pstMsg->stPdnAddr.enPdnType = EHSM_ESM_PDN_TYPE_IPV4;
    }
    else if (CNAS_EHSM_PDN_TYPE_IPV6 == pstPdnAddr->enPdnType)
    {
        NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_ESM_IPV6_ADDR_LEN, &(pstPdnAddr->aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
        pstMsg->stPdnAddr.enPdnType = EHSM_ESM_PDN_TYPE_IPV6;
    }
    else if (CNAS_EHSM_PDN_TYPE_IPV4V6 == pstPdnAddr->enPdnType)
    {
        NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_ESM_IPV6_ADDR_LEN, &(pstPdnAddr->aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
        NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_ESM_IPV4_ADDR_LEN, &(pstPdnAddr->aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
        pstMsg->stPdnAddr.enPdnType = EHSM_ESM_PDN_TYPE_IPV4V6;
    }
    else
    {
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_FillApnAmbrInfoForSyncPndInfoInd
 功能描述  : 设置ID_EHSM_ESM_SYNC_PDN_INFO_IND 对应结构体中的apn ambr info
 输入参数  :
            EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
            CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_FillApnAmbrInfoForSyncPndInfoInd(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg,
    CNAS_EHSM_APN_AMBR_STRU            *pstApnAmbr
)
{
    if (((1 == pstApnAmbr->bitOpDLApnAmbr)
      || (1 == pstApnAmbr->bitOpULApnAmbr)
      || (1 == pstApnAmbr->bitOpDLApnAmbrExt)
      || (1 == pstApnAmbr->bitOpULApnAmbrExt)
      || (1 == pstApnAmbr->bitOpDLApnAmbrExt2)
      || (1 == pstApnAmbr->bitOpULApnAmbrExt2)))
    {
        NAS_MEM_CPY_S(&(pstMsg->stApnAmbr), sizeof(EHSM_ESM_APN_AMBR_STRU), pstApnAmbr, sizeof(EHSM_ESM_APN_AMBR_STRU));
        pstMsg->bitOpApnAmbr = 1;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetLtePdnIndexWithMinEspbId
 功能描述  : 查找LTE承载中承载号最小的作为HANDOVER承载使用
 输入参数  : VOS_VOID
 输出参数  : lte pdn info 的索引值
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetLtePdnIndexWithMinEspbId(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulMinEspbId;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucPdnInfoIndex;

    pstEhsmCtx         = CNAS_EHSM_GetEhsmCtxAddr();
    ulMinEspbId        = 0xFFFFFFFF;
    ucPdnInfoIndex     = 0;

    for (ucLoop = 0; ucLoop < CNAS_EHSM_MAX_PDN_NUM; ucLoop++)
    {
        if (VOS_TRUE == pstEhsmCtx->astLtePdnBearInfo[ucLoop].ucInUsed)
        {
            if (ulMinEspbId > pstEhsmCtx->astLtePdnBearInfo[ucLoop].ulEpsbId)
            {
                ulMinEspbId        = pstEhsmCtx->astLtePdnBearInfo[ucLoop].ulEpsbId;
                ucPdnInfoIndex     = ucLoop;
            }
        }
    }

    return ucPdnInfoIndex;
}


CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU* CNAS_EHSM_GetRetryApnAddr(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    return &(pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo.astRetryApnfo[0]);
}


VOS_UINT16 CNAS_EHSM_GetMaxNumOfApnRetry(VOS_VOID)
{
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    return pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo.usMaxNoOfRetry;
}


VOS_UINT8 CNAS_EHSM_GetSpecialApnRetryCnt
(
    CNAS_EHSM_APN_STRU                 *pstApn
)
{
    CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU *pstRetryPdnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucRetryCnt;

    pstRetryPdnInfo = CNAS_EHSM_GetRetryApnAddr();

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        /* the retry pdn exist and got it  */
        if (0 == PS_MEM_CMP(pstApn, &(pstRetryPdnInfo[ulLoop].stApn), sizeof(CNAS_EHSM_APN_STRU)))
        {
            break;
        }
    }

    if (ulLoop == CNAS_EHSM_MAX_PDN_NUM)
    {
        ucRetryCnt = 0;
    }
    else
    {
        ucRetryCnt = pstRetryPdnInfo[ulLoop].ucCurrRetryCnt;
    }

    return ucRetryCnt;
}

VOS_VOID CNAS_EHSM_InitApnRetryInfo(VOS_VOID)
{
    CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU                     *pstRetryPdnBearInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ulLoop;

    pstRetryPdnBearInfo = CNAS_EHSM_GetRetryApnAddr();

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        NAS_MEM_SET_S(&(pstRetryPdnBearInfo[ulLoop]), 
                      sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU), 
                      0x00, 
                      sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU));
    }
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_IncreSpecialApnRetryCnt
Description     :   update the Pdn  retry info，place the curr retry apn in front
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-06-1
    Author         : f00279542
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_EHSM_IncreSpecialApnRetryCnt
(
    CNAS_EHSM_APN_STRU                                     *pstApn
)
{
    CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU                     *pstRetryPdnInfo = VOS_NULL_PTR;
    CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU                      stTmpApnInfo;
    VOS_UINT32                                              ulLoop;

    pstRetryPdnInfo = CNAS_EHSM_GetRetryApnAddr();

    NAS_MEM_SET_S(&stTmpApnInfo, sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU), 0x00, sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU));

    for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
    {
        /* the retry pdn exist and got it  */
        if (0 == PS_MEM_CMP(pstApn, &(pstRetryPdnInfo[ulLoop].stApn), sizeof(CNAS_EHSM_APN_STRU)))
        {
            break;
        }
    }

    /* 保存一下指定apn的信息 */
    if (ulLoop< CNAS_EHSM_MAX_PDN_NUM)
    {
        NAS_MEM_CPY_S(&stTmpApnInfo, sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU), &(pstRetryPdnInfo[ulLoop]), sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU));
    }
    else
    {
        NAS_MEM_CPY_S(&(stTmpApnInfo.stApn), sizeof(CNAS_EHSM_APN_STRU), pstApn, sizeof(CNAS_EHSM_APN_STRU));
    }

    /* 把指定apn前面的元素整体后移一个位置０，再把指定的apn放到第0个位置，指定的apn在第0个位置上除外 */
    if ((ulLoop >= 1)
     && (ulLoop < CNAS_EHSM_MAX_PDN_NUM))
    {
        NAS_MEM_MOVE_S(&(pstRetryPdnInfo[1]), 
                       ((CNAS_EHSM_MAX_PDN_NUM - 1) * sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU)), 
                       pstRetryPdnInfo, 
                       sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU)*(ulLoop));
    }

    /* 指定的apn不存在，有尝试的apn整体后移一个位置 */
    if (CNAS_EHSM_MAX_PDN_NUM == ulLoop)
    {
        NAS_MEM_MOVE_S(&(pstRetryPdnInfo[1]), 
                       (sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU) * (CNAS_EHSM_MAX_PDN_NUM - 1)),
                       pstRetryPdnInfo, 
                       sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU) * (CNAS_EHSM_MAX_PDN_NUM - 1));
    }


    /* fill the curr retry pdn to the first place, initial the IE to 0 firstly */
    NAS_MEM_CPY_S(pstRetryPdnInfo, sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU), &stTmpApnInfo, sizeof(CNAS_EHSM_RETRY_PDN_BEAR_INFO_STRU));

    /* increase the retry count */
    pstRetryPdnInfo->ucCurrRetryCnt += 1;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_InitEhrpdAutoAttachFlag
 功能描述  : 初始化EHRPD发起Auto Attach的标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_InitEhrpdAutoAttachFlag(VOS_VOID)
{
    NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU      stAutoAttachFlag;

    if (NV_OK == NV_Read(en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG, &stAutoAttachFlag, sizeof(stAutoAttachFlag)))
    {
        CNAS_EHSM_SetEhrpdAutoAttachFlag(stAutoAttachFlag.ucEnableFlag);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitEhrpdAutoAttachFlag(): en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG read error");

        CNAS_EHSM_SetEhrpdAutoAttachFlag(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_EHSM_GetCidSdfParaInfoForEhsm
 功能描述  : 获取CID对应的SDF参数, 由APS保证获取的SDF参数有效, 如果CID对应的
             SDF参数无效, 返回VOS_ERR, 否则返回VOS_OK
 输入参数  : ucCid                      - CID
 输出参数  : pstSdfParaInfo             - CID对应的SDF参数
 返 回 值  : VOS_OK                     - CID对应的SDF参数有效, 获取成功
             VOS_ERR                    - CID对应的SDF参数无效, 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_GetCidSdfParaInfoForEhsm(
    VOS_UINT8                           ucCid,
    APS_EHSM_SDF_PARA_INFO_STRU        *pstSdfParaInfo
)
{
    if (MODEM_ID_0 == CNAS_CCB_GetCdmaModeModemId())
    {
        return TAF_APS_GetCidSdfParaInfoForEhsm(ucCid, pstSdfParaInfo);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    else if (MODEM_ID_1 == CNAS_CCB_GetCdmaModeModemId())
    {
        return I1_TAF_APS_GetCidSdfParaInfoForEhsm(ucCid, pstSdfParaInfo);
    }
#if ( 3 == MULTI_MODEM_NUMBER )/* three modems */
    else if (MODEM_ID_2 == CNAS_CCB_GetCdmaModeModemId())
    {
        return I2_TAF_APS_GetCidSdfParaInfoForEhsm(ucCid, pstSdfParaInfo);
    }
#endif
#endif
    else
    {
        NAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_GetCidSdfParaInfoForEhsm invalid modemId!\r\n");
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetEhrpdLocPdnAddr
 功能描述  : 获取本地pdn地址
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月7日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU* CNAS_EHSM_GetEhrpdLocPdnAddr(
    VOS_UINT8                           ucPdnId
)
{
    return &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SyncEhrpdIpv6PrfixWithLtePdnInfo
 功能描述  : 同步当前LTE的IPV6前缀到Ehrp的信息中
 输入参数  : VOS_UINT8                           ucPdnId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月28日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SyncEhrpdIpv6PrfixWithLtePdnInfo(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU            *pstPdnInfo = VOS_NULL_PTR;
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU              *pstLtePdnInfo = VOS_NULL_PTR;

    pstPdnInfo    = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);
    pstLtePdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo[ucPdnId]);

    PS_MEM_CPY(&(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]),
               &(pstLtePdnInfo->stPdnAddr.aucIpv6Addr[0]),
               (EHSM_APS_IPV6_ADDR_LEN-EHSM_APS_IPV6_IFID_LEN));

}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


