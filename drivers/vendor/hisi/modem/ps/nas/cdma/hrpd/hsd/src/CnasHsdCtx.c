

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasCcb.h"
#include "CnasHsdCtx.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdFsmSwitchOnTbl.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasPrlApi.h"
#include "CnasHsdMntn.h"
#include "CnasHsdProcNvim.h"
#include "CnasHsdFsmPowerSaveTbl.h"

#include "hsd_mscc_pif.h"
#include "CnasHsdFsmInterSysTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* HSD CTX,用于保存HSD状态机,描述表 */
CNAS_HSD_CTX_STRU                       g_stCnasHsdCtx;
VOS_UINT16                              g_ausCachePriorityList[] =
{
    ID_MSCC_HSD_POWER_OFF_REQ,
    ID_MSCC_HSD_POWER_SAVE_REQ,
    ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HSD_InitCurrFsmCtx(
    CNAS_HSD_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_HSD_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_HSD_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   CNAS_HSD_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   CNAS_HSD_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               CNAS_HSD_MAX_MSG_BUFFER_LEN);

    return;
}


VOS_VOID CNAS_HSD_InitFsmStackCtx(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for (i = 0 ; i < CNAS_HSD_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_HSD_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_HSD_L1_STA_BUTT;
    }

    return;
}


VOS_VOID CNAS_HSD_InitCacheMsgQueue(
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue,
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    VOS_UINT32                          i;

    pstCacheMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM; i++)
    {
        /* 开机时直接把变量置空，软开关时候防止内存泄露，需要释放内存 */
        if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
        {
            pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
        }
        else
        {
            if (VOS_NULL_PTR != pstCacheMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_HSD, pstCacheMsgQueue->pastCacheMsg[i]);
            }
        }
    }

    return;
}


VOS_VOID CNAS_HSD_InitSysRecList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysRecList
)
{
    pstSysRecList->usHrpdSysNum     = 0;

    if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
    {
        pstSysRecList->pstHrpdSysItem   = VOS_NULL_PTR;

        return;
    }

    if (VOS_NULL_PTR != pstSysRecList->pstHrpdSysItem)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstSysRecList->pstHrpdSysItem);
        pstSysRecList->pstHrpdSysItem = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID CNAS_HSD_InitScanChanList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanChanList
)
{
    pstScanChanList->usTotalFreqNum     = 0;
    pstScanChanList->usAvailFreqNum     = 0;
    pstScanChanList->usCurrIndex        = 0;
    pstScanChanList->ucLowPrioLevel     = CNAS_PRL_PRIO_LEVEL_1;

    if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
    {
        pstScanChanList->pstScanFreqItem    = VOS_NULL_PTR;

        return;
    }

    if (VOS_NULL_PTR != pstScanChanList->pstScanFreqItem)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstScanChanList->pstScanFreqItem);
        pstScanChanList->pstScanFreqItem = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID CNAS_HSD_InitSystemAcquireCtrl(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
)
{
    pstSysAcqCtrl->enModeType           = CNAS_HSD_SYS_MODE_BUTT;

    pstSysAcqCtrl->st1xSysInfo.enStatus   = CNAS_HSD_1X_SYSTEM_UNAVAILABLE;
    pstSysAcqCtrl->stHrpdSysInfo.enStatus = CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE;

    PS_MEM_SET(&(pstSysAcqCtrl->st1xSysInfo.st1xSys), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stMruList), 0, sizeof(CNAS_HSD_HRPD_MRU_LIST_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stAvoidFreqList), 0, sizeof(CNAS_HSD_AVOID_FREQ_LIST_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stHistorySysList), 0, sizeof(CNAS_HSD_HISTORY_SYS_LIST_STRU));

    CNAS_HSD_InitSysRecList(enInitType, &(pstSysAcqCtrl->stSysRecList));

    CNAS_HSD_InitScanChanList(enInitType, &(pstSysAcqCtrl->stScanFreqList));

    CNAS_HSD_InitOocScheduleInfo(&(pstSysAcqCtrl->stOocScheduleInfo));

    PS_MEM_SET(&(pstSysAcqCtrl->stHighPriority), 0, sizeof(CNAS_HSD_HIGHPRIORITY_STRU));
    PS_MEM_SET(&(pstSysAcqCtrl->stCasOhmHrpdSys), 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));
    PS_MEM_SET(&(pstSysAcqCtrl->stNetwkLostSysRec), 0, sizeof(CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU));

    /* 锁频参数 */
    CNAS_HSD_InitCFreqLockValue();

    PS_MEM_SET(&(pstSysAcqCtrl->stSyncFreq), 0, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU));

    CNAS_HSD_InitMatchedHrpdSysIndexList();

    return;
}


VOS_VOID CNAS_HSD_InitSystemAssistInfo(
    CNAS_HSD_SYSTEM_ASSIST_INFO_STRU   *pstSysAssistInfo
)
{
    pstSysAssistInfo->enNoRfScene        = CNAS_HSD_SYS_ACQ_SCENE_BUTT;
    pstSysAssistInfo->enATStatus         = CNAS_HSD_AT_STATUS_ENUM_NONE;
    pstSysAssistInfo->enSessionNegStatus = CNAS_HSD_NOT_IN_SESSION_NEG;
    pstSysAssistInfo->ucHrpdRfAvailFlg   = VOS_TRUE;
    pstSysAssistInfo->ucMru0RelateFlg    = VOS_FALSE;
    pstSysAssistInfo->ulUeSupportedBand  = 0xFFFF;

    return;
}


VOS_VOID CNAS_HSD_InitFsmCtx_L1Main(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* 检查当前状态机是否是L1状态机 */
    if (CNAS_HSD_FSM_L1_MAIN != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stL1MainCtx.ulCurAvailableTimerCount = 0;

    return;
}


VOS_VOID CNAS_HSD_InitFsmCtx_SwitchOn(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* 检查当前状态机是否时开机状态机 */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg = CNAS_HSD_READ_CARD_FILE_FLG_NULL;

    return;
}


VOS_VOID CNAS_HSD_InitFsmCtx_SysAcq(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* 检查当前状态机是否时SYSTEM ACQUIRE状态机 */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg     = VOS_FALSE;
    pstHsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason  = CNAS_HSD_ABORT_REASON_BUTT;

    return;
}


VOS_VOID CNAS_HSD_InitCtx(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* 当前不处理开机原因值，后续会扩展 */

    /* 当前的状态机数组初始化 */
    CNAS_HSD_InitCurrFsmCtx(&(pstHsdCtx->stCurFsm));

    /* 状态机栈数组初始化 */
    CNAS_HSD_InitFsmStackCtx(&(pstHsdCtx->stFsmStack));

    /* CNAS HSD缓存消息队列初始化 */
    CNAS_HSD_InitCacheMsgQueue(&(pstHsdCtx->stCacheMsgQueue), enInitType);

    /* CNAS HSD缓存内部消息队列初始化 */
    CNAS_HSD_InitInternalBuffer(&(pstHsdCtx->stIntMsgQueue));

    /* CNAS HSD系统获取控制初始化 */
    CNAS_HSD_InitSystemAcquireCtrl(enInitType, &(pstHsdCtx->stSysAcqCtrl));

    /* CNAS HSD辅助信息 */
    CNAS_HSD_InitSystemAssistInfo(&(pstHsdCtx->stSysAssistInfo));

    return;
}


VOS_VOID  CNAS_HSD_LoadSubFsm(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case CNAS_HSD_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = CNAS_HSD_SWITCH_ON_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetSwitchOnFsmDescAddr();
            break;

        case CNAS_HSD_FSM_POWER_OFF :
            pstCurFsm->ulState                  = CNAS_HSD_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetPowerOffFsmDescAddr();
            break;

        case CNAS_HSD_FSM_SYS_ACQ:
            pstCurFsm->ulState                  = CNAS_HSD_SYS_ACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetSysAcqFsmDescAddr();
            break;

        case CNAS_HSD_FSM_POWER_SAVE:
            pstCurFsm->ulState                  = CNAS_HSD_POWER_SAVE_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetPowerSaveFsmDescAddr();
            break;

        case CNAS_HSD_FSM_INTER_SYS:
            pstCurFsm->ulState                  = CNAS_HSD_INTER_SYS_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetInterSysFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    return;
}


VOS_VOID CNAS_HSD_PushFsm(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack,
    CNAS_HSD_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* 入参指针检查 */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD,
                       "CNAS_HSD_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* 栈深度检查 */
    if (pstFsmStack->usStackDepth >= CNAS_HSD_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD,
                       "CNAS_HSD_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push当前状态机上下文入栈 */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(CNAS_HSD_FSM_CTX_STRU));

    /* 栈深度增加 */
    pstFsmStack->usStackDepth++;

    return;
}


VOS_VOID CNAS_HSD_PopFsm(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack = CNAS_HSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();

    /* 检查栈空间是否为空 */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_PopFsm: FSM Stack is empty");

        return;
    }

    /* 状态机栈深度减少 */
    pstFsmStack->usStackDepth--;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(CNAS_HSD_FSM_CTX_STRU));

    return;
}


VOS_VOID CNAS_HSD_InitFsmL2(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId
)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId     = CNAS_HSD_GetCurrFsmId();
    ulParentEventType = CNAS_HSD_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    pstFsmStack = CNAS_HSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();
    CNAS_HSD_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId = enFsmId;

    /* 加载L2状态机 */
    CNAS_HSD_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    return;
}


VOS_VOID CNAS_HSD_QuitFsmL2(VOS_VOID)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = CNAS_HSD_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_QuitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    /* 状态机出栈操作 */
    CNAS_HSD_PopFsm();

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_QuitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    return;
}


CNAS_HSD_CTX_STRU* CNAS_HSD_GetHsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx);
}


CNAS_HSD_FSM_STACK_STRU* CNAS_HSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stFsmStack);
}


CNAS_HSD_FSM_CTX_STRU* CNAS_HSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCurFsm);
}


VOS_UINT32 CNAS_HSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->ulState);
}


NAS_FSM_DESC_STRU* CNAS_HSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->pstFsmDesc);
}


VOS_UINT16 CNAS_HSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}


VOS_VOID CNAS_HSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;

    return;
}


VOS_UINT16 CNAS_HSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


CNAS_HSD_CACHE_MSG_QUEUE_STRU* CNAS_HSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue);
}


VOS_VOID CNAS_HSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulMsgLen;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = CNAS_HSD_GetCacheMsgAddr();

    ulOffset     = pstMsgQueue->ucCacheMsgNum;

    if (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM <= ulOffset)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    ulMsgLen = (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    /* 在此申请内测 */
    pstMsgQueue->pastCacheMsg[ulOffset] = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSD, ulMsgLen);

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[ulOffset])
    {
        return;
    }

    PS_MEM_CPY((pstMsgQueue->pastCacheMsg[ulOffset]),
               pstMsg,
               ulMsgLen);

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_INFO_LOG1(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);

    return;
}


VOS_UINT32  CNAS_HSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* 被cache的消息长度检查 */
    if ((CNAS_HSD_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* 将消息缓存在缓存内存池中 */
    CNAS_HSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    CNAS_HSD_SortCacheMsgInMsgQueue();

    return VOS_TRUE;
}



VOS_VOID CNAS_HSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    if (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        return;
    }

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;
        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_HSD, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* 清除的消息不是数组最后一个，需要把后续对列中的消息前移 */
            PS_MEM_MOVE(&(pstMsgQueue->pastCacheMsg[ucIndex]),
                        &(pstMsgQueue->pastCacheMsg[ucIndex + 1]),
                        (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT32));
        }

       pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum] = VOS_NULL_PTR;
    }

    return;
}


VOS_UINT32 CNAS_HSD_GetNextCachedMsg(
    CNAS_HSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;
    VOS_UINT32                          ulMsgLen;

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[0]);

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    ulMsgLen = (pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

    if (CNAS_HSD_MAX_MSG_BUFFER_LEN < ulMsgLen)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNextCachedMsg: beyond msg size ");

        ulMsgLen = CNAS_HSD_MAX_MSG_BUFFER_LEN;
    }

    PS_MEM_CPY(&pstEntryMsg->aucMsgBuffer[0],
               pstMsgQueue->pastCacheMsg[0],
               ulMsgLen);

    /* 清除index为0的cache消息 */
    CNAS_HSD_ClearCacheMsg(0);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_HSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue;

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


VOS_VOID  CNAS_HSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm;

    /* 获取当前的状态信息 */
    pstCurFsm                   = CNAS_HSD_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的当前状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, pstCurFsm->enFsmId, ulCurrState, 0);

    return;
}


CNAS_HSD_MSG_STRU* CNAS_HSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stCurFsm.stEntryMsg);
}


VOS_VOID CNAS_HSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_MSG_STRU                  *pstEntryMsg;
    VOS_UINT32                          ulLen;

    /* 获得当前处理CNAS HSD入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_HSD_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    if (CNAS_HSD_MAX_MSG_BUFFER_LEN < ulLen)
    {
        CNAS_ERROR_LOG( UEPS_PID_HSD, "CNAS_HSD_SaveCurEntryMsg: msg size big than 1600!" );
        ulLen = CNAS_HSD_MAX_MSG_BUFFER_LEN;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY(&pstEntryMsg->aucMsgBuffer[0], pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}


CNAS_HSD_FSM_ID_ENUM_UINT32 CNAS_HSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasHsdCtx.stCurFsm.enFsmId);
}


CNAS_HSD_INT_MSG_QUEUE_STRU* CNAS_HSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stIntMsgQueue);
}


VOS_VOID CNAS_HSD_InitInternalBuffer(
    CNAS_HSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_HSD_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;

    return;
}



VOS_VOID  CNAS_HSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_HSD_GetIntMsgNum();

    /* 检查内部消息队列，是否有缓存队列已满 */
    if (CNAS_HSD_MAX_INT_MSG_QUEUE_NUM <= ucIntMsgNum)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

        CNAS_ERROR_LOG( UEPS_PID_HSD, "CNAS_HSD_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    /* 保存当前信息 */
    CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}


VOS_UINT8 *CNAS_HSD_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* 获取下一个缓存的消息消息 */
        pstIntMsg = CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* 内部消息数目减少一个 */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* 前移内部消息 */
            PS_MEM_MOVE(&(CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* 对消息队列中尾部的消息清为空指针 */
        CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}


VOS_UINT8 CNAS_HSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}


CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg;
}


VOS_VOID CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg |= enReadCardFileCnfFlg;

    return;
}


VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg &= ~enReadCardFileCnfFlg;

    return;
}


CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_GetModeType(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType;
}


VOS_VOID CNAS_HSD_SetSysModeType(CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 enModeType)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType = enModeType;

    return;
}


CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_Get1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.st1xSysInfo);
}

CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_GetScanListMatched1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdMatched1xSysInfo);
}


CNAS_HSD_HRPD_MRU_LIST_STRU* CNAS_HSD_GetMruList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList);
}



VOS_VOID CNAS_HSD_UpdateMru0(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurSysId)
{
    VOS_UINT8                           i;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMruList;
    VOS_UINT32                          ulIsSysInMru = VOS_FALSE;
    CNAS_PRL_HRPD_SYSTEM_STRU           stMruItem;

    pstMruList       = CNAS_HSD_GetMruList();

    PS_MEM_SET(&stMruItem, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));
    stMruItem.stFreq = pstCurSysId->stFreq;

    /* MRU中只存SubnetID中的高6字节 */
    PS_MEM_CPY(stMruItem.aucSubnet, pstCurSysId->aucSubnet + (CNAS_PRL_BYTES_IN_SUBNET - CNAS_HSD_CHECK_BYTES_SUBNET_ID),
               CNAS_HSD_CHECK_BYTES_SUBNET_ID);

    /* 查找有无重复 */
    for (i = 0; i < pstMruList->ucCurrMruNum; i++)
    {
        /* 如果重复，进行去重操作 */
        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstMruList->astHrpdSys[i].stFreq), &(stMruItem.stFreq)))
        {
            if (VOS_TRUE == CNAS_PRL_CmpSubnetValue(pstMruList->astHrpdSys[i].aucSubnet,
                                                    stMruItem.aucSubnet, CNAS_HSD_CHECK_BYTES_SUBNET_ID))
            {
                ulIsSysInMru = VOS_TRUE;

                if (0 != i)
                {
                    PS_MEM_MOVE(&pstMruList->astHrpdSys[1], pstMruList->astHrpdSys, (i)*(sizeof(CNAS_PRL_HRPD_SYSTEM_STRU)));
                }

                break;
            }
        }
    }

    /* 如果不在MRU中，直接填MRU0，其他后移 */
    if (VOS_FALSE == ulIsSysInMru)
    {
        PS_MEM_MOVE(&pstMruList->astHrpdSys[1], pstMruList->astHrpdSys,
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU)*(CNAS_HSD_MAX_MRU_SYS_NUM - 1));

        if (pstMruList->ucCurrMruNum < CNAS_HSD_MAX_MRU_SYS_NUM)
        {
            pstMruList->ucCurrMruNum++;
        }
    }

    /* 赋值MRU[0] */
    PS_MEM_CPY(pstMruList->astHrpdSys, &stMruItem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    CNAS_HSD_WriteMruNvim(pstMruList);

    CNAS_HSD_LogMruList(pstMruList, ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_STAY_SUCC);

    return;
}


VOS_UINT8 CNAS_HSD_GetMruListNum(VOS_VOID)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enHrpdMode;
    VOS_UINT8                           ucMruNum = 0;

    enHrpdMode = CNAS_HSD_GetModeType();

    /* 获取MRU个数总数 */
    /* 如果个数为0返回0  如果HYBRID 且不为0 返回1 ；如果nonhybrid 直接使用原来的值 */
    if ((0 == CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList.ucCurrMruNum)
     || (CNAS_HSD_SYS_MODE_NONHYBRID == enHrpdMode))
    {
        ucMruNum    = CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList.ucCurrMruNum;
    }
    else
    {
        ucMruNum    = 1;
    }

    return ucMruNum;
}


VOS_UINT32 CNAS_HSD_GetMru0SysId(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstMru0SysId
)
{
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_HSD_GetMruList();

    if (0 < CNAS_HSD_GetMruListNum())
    {
        pstMru0SysId->stFreq    = pstMruList->astHrpdSys[0].stFreq;
        PS_MEM_CPY(pstMru0SysId->aucSubnet, pstMruList->astHrpdSys[0].aucSubnet, CNAS_PRL_BYTES_IN_SUBNET);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



CNAS_HSD_HRPD_SYS_LIST_STRU* CNAS_HSD_GetSysRecListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSysRecList);
}


VOS_UINT16 CNAS_HSD_GetSysRecItemNum(VOS_VOID)
{
    return (CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum);
}


VOS_VOID CNAS_HSD_SetSysRecListIndex(
    VOS_UINT16                          usHrpdSysNum
)
{
    CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum = usHrpdSysNum;

    return;
}



CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU* CNAS_HSD_GetScanFreqListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stScanFreqList);
}


VOS_UINT16 CNAS_HSD_GetScanFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usAvailFreqNum);
}


VOS_UINT16 CNAS_HSD_GetCurScanFreqIndex(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usCurrIndex);
}


VOS_UINT16 CNAS_HSD_GetScanListAvailFreqNum(VOS_VOID)
{
    VOS_UINT16                          usAvailFreqNum = 0;
    VOS_UINT16                          usCurrIndex    = 0;

    /* 总的可用频点个数 */
    usAvailFreqNum = CNAS_HSD_GetScanFreqNum();

    /* 当前索引 */
    usCurrIndex    = CNAS_HSD_GetCurScanFreqIndex();

    return (usAvailFreqNum - usCurrIndex);
}


VOS_VOID CNAS_HSD_SetCurScanFreqIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    CNAS_HSD_GetScanFreqListAddr()->usCurrIndex = usCurScanIndex;

    return;
}


CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_HSD_GetScanFreqByIndex(
    VOS_UINT16                          usFreqIndex
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstFreqList;

    if (usFreqIndex >= CNAS_HSD_GetScanFreqNum())
    {
        return VOS_NULL_PTR;
    }

    pstFreqList = CNAS_HSD_GetScanFreqListAddr();

    return &(pstFreqList->pstScanFreqItem[usFreqIndex].stFreq);
}


CNAS_HSD_REDIRECTION_STRU* CNAS_HSD_GetRedirectionFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection);
}


VOS_UINT16 CNAS_HSD_GetRedirectionFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection.ucChanNum);
}


CNAS_HSD_OOC_CONFIG_INFO_STRU *CNAS_HSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}


CNAS_HSD_OOC_SCHEDULE_INFO_STRU *CNAS_HSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}


VOS_VOID CNAS_HSD_InitOocScheduleInfo(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    PS_MEM_SET(pstOocScheduleInfo, 0, sizeof(CNAS_HSD_OOC_SCHEDULE_INFO_STRU));

    pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 1;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

    return;

}


VOS_VOID CNAS_HSD_InitOocCtxInfo(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enSysMode;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    PS_MEM_SET(&pstOocScheduleInfo->stOocCtxInfo, 0, sizeof(CNAS_HSD_OOC_CTX_INFO_STRU));

    enSysMode          = CNAS_HSD_GetModeType();

    if (CNAS_HSD_SYS_MODE_HYBRID == enSysMode)
    {
        /* 混合模式下第一个OOC搜网时间间隔不为0 */
        pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase = 1;
    }

    return;
}


VOS_UINT8 CNAS_HSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}


VOS_VOID CNAS_HSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;

    return;
}


CNAS_HSD_AVOID_FREQ_LIST_STRU* CNAS_HSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stSysAcqCtrl.stAvoidFreqList);
}


VOS_UINT8 CNAS_HSD_GetAvoidFreqListUsedNum(VOS_VOID)
{
    return (CNAS_HSD_GetAvoidFreqListAddr()->ucAvoidItemUsedNum);
}


CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32 CNAS_HSD_GetSessionNegStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus);
}


VOS_VOID CNAS_HSD_SaveSessionNegStatus(
    CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32                 enSessionNegStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus = enSessionNegStatus;

     return;
}


CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_GetATStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus);
}


VOS_VOID CNAS_HSD_SaveATStatus(
    CNAS_HSD_AT_STATUS_ENUM_UINT32     enATStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus = enATStatus;

     return;
}


CNAS_HSD_HISTORY_SYS_LIST_STRU* CNAS_HSD_GetHistorySysList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHistorySysList);
}


VOS_VOID CNAS_HSD_UpdateHistorySysList(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurrSystem)
{
    CNAS_HSD_HISTORY_SYS_LIST_STRU                         *pstHistorySysList;

    pstHistorySysList = CNAS_HSD_GetHistorySysList();

    if (pstHistorySysList->ulTotalNum < CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM)
    {
        PS_MEM_MOVE(&(pstHistorySysList->stCampedHrpdSysInfo[1]),
                    &(pstHistorySysList->stCampedHrpdSysInfo[0]),
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU) * pstHistorySysList->ulTotalNum);

        pstHistorySysList->ulTotalNum++;
    }
    else
    {
        PS_MEM_MOVE(&(pstHistorySysList->stCampedHrpdSysInfo[1]),
                    &(pstHistorySysList->stCampedHrpdSysInfo[0]),
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU) * (CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM - 1));
    }

    PS_MEM_CPY(&(pstHistorySysList->stCampedHrpdSysInfo[0]),
               pstCurrSystem,
               sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}


CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 CNAS_HSD_GetHrpdSysStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus;
}


VOS_VOID CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus = enStatus;

    return;
}


CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCampedHrpdSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.stCampedHrpdSysInfo);
}


VOS_VOID CNAS_HSD_UpdateHrpdSysInfo(CNAS_PRL_HRPD_SYSTEM_STRU *pstSystem)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* 设置当前Hrpd系统可用 */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_AVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_CPY(pstHrpdSystem, pstSystem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}


VOS_VOID CNAS_HSD_ClearHrpdSysInfo(VOS_VOID)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* 设置当前Hrpd系统非驻留 */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_SET(pstHrpdSystem, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}


VOS_VOID CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene = enNoRfScene;

    return;
}


CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetNoRfScene(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene;
}


CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_HSD_GetNoRf1XUeStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus;
}


VOS_VOID CNAS_HSD_SetNoRf1XUeStatus(CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus = enStatus;
    return ;
}



VOS_UINT8   CNAS_HSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetAbortFlg_SysAcq: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason >= CNAS_HSD_GetAbortReason_SysAcq())
    {
        return VOS_FALSE;
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg     = ucFlg;
    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason  = enAbortReason;

    return VOS_TRUE;
}


VOS_UINT8 CNAS_HSD_GetAbortFlg_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_SysAcq: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg;
}


CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_SysAcq: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason;
}


CNAS_HSD_HIGHPRIORITY_STRU* CNAS_HSD_GetHighPriorityFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority);
}


VOS_UINT8 CNAS_HSD_GetHighPriorityFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority.ucFreqNum);
}


VOS_VOID CNAS_HSD_InitHighPriorityFreq(CNAS_HSD_HIGHPRIORITY_STRU* pstHighFreq)
{
    PS_MEM_SET(pstHighFreq, 0, sizeof(CNAS_HSD_HIGHPRIORITY_STRU));

    return;
}


CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCasOhmHrpdSysAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stCasOhmHrpdSys);
}


VOS_UINT32 CNAS_HSD_GetEventType(
    VOS_UINT8                          *pucCacheMsg
)
{
    VOS_UINT32                          ulEventType;
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;

    pstCacheMsgHdr = (MSG_HEADER_STRU *)pucCacheMsg;

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    return ulEventType;
}


VOS_VOID CNAS_HSD_SortCacheMsgInMsgQueue(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucPri1;
    VOS_UINT8                           ucPri2;
    VOS_UINT8                          *pstCacheMsg;
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;

    pstMsgQueue  = CNAS_HSD_GetCacheMsgAddr();

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        ucPri1 =  CNAS_HSD_GetCacheMsgPriority(CNAS_HSD_GetEventType(pstMsgQueue->pastCacheMsg[i]));

        for (j = i + 1; j < pstMsgQueue->ucCacheMsgNum; j++)
        {
            ucPri2 =  CNAS_HSD_GetCacheMsgPriority(CNAS_HSD_GetEventType(pstMsgQueue->pastCacheMsg[j]));

            /* 交换位置 */
            if (ucPri1 > ucPri2)
            {
                pstCacheMsg = pstMsgQueue->pastCacheMsg[i];

                pstMsgQueue->pastCacheMsg[i] = pstMsgQueue->pastCacheMsg[j];

                pstMsgQueue->pastCacheMsg[j] = pstCacheMsg;
#if 0
                PS_MEM_CPY(pstCacheMsg->aucMsgBuffer,
                           &(pstMsgQueue->pastCacheMsg[i]),
                           sizeof(CNAS_HSD_MSG_STRU));

                PS_MEM_CPY(&pstMsgQueue->pastCacheMsg[i],
                           &pstMsgQueue->pastCacheMsg[j],
                           sizeof(CNAS_HSD_MSG_STRU));

                PS_MEM_CPY(&pstMsgQueue->pastCacheMsg[j],
                           pstCacheMsg->aucMsgBuffer,
                           sizeof(CNAS_HSD_MSG_STRU));
#endif
            }
        }
    }

    return;
}


VOS_UINT8 CNAS_HSD_GetCacheMsgPriority(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          usMsgName;

    usMsgName = (VOS_UINT16)(ulEventType & 0xFFFF);

    for (i = 0; i < sizeof(g_ausCachePriorityList)/sizeof(VOS_UINT16); i++)
    {
        if (usMsgName == g_ausCachePriorityList[i])
        {
            break;
        }
    }

    return i;
}


VOS_VOID CNAS_HSD_InitFsmCtx_InterSys(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* 检查当前状态机是否时CNAS_HSD_FSM_INTER_SYS状态机 */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_InterSys:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg     = VOS_FALSE;
    pstHsdCtx->stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason  = CNAS_HSD_ABORT_REASON_BUTT;

    return;
}


VOS_UINT8   CNAS_HSD_SetAbortFlg_InterSys(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetAbortFlg_InterSys: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason >= CNAS_HSD_GetAbortReason_InterSys())
    {
        return VOS_FALSE;
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg     = ucFlg;
    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason  = enAbortReason;

    return VOS_TRUE;
}


VOS_UINT8 CNAS_HSD_GetAbortFlg_InterSys(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_InterSys: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg;
}


CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_InterSys(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortReason_InterSys: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason;
}


CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU* CNAS_HSD_GetNetwkLostSysRec(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stNetwkLostSysRec);
}


CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_HSD_GetFreqLockAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara);
}


VOS_UINT8 CNAS_HSD_GetFreqLockMode(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}


VOS_UINT8 CNAS_HSD_GetHrpdRfAvailFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg;
}


VOS_VOID CNAS_HSD_SetHrpdRfAvailFlg(VOS_UINT8 ucHrpdRfAvailFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg = ucHrpdRfAvailFlg;

    return;
}


VOS_UINT8 CNAS_HSD_GetMru0RelateFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg;
}


VOS_VOID CNAS_HSD_SetMru0RelateFlg(VOS_UINT8 ucMru0RelateFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg = ucMru0RelateFlg;

    return;
}


VOS_VOID CNAS_HSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasHsdCFreqLockValue;

    pstCnasHsdCFreqLockValue = CNAS_HSD_GetFreqLockAddr();

    PS_MEM_SET(pstCnasHsdCFreqLockValue, 0x00, sizeof(CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}


VOS_UINT32 CNAS_HSD_GetUeSupportedBandClass(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ulUeSupportedBand);
}


CNAS_HSD_TEST_CONFIG_STRU* CNAS_HSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stTestConfig);
}


VOS_VOID CNAS_HSD_SetSysCfgFlag(VOS_UINT8 ucIsSysCfg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg = ucIsSysCfg;

    return;
}


VOS_UINT8 CNAS_HSD_GetSysCfgFlag(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg;
}



CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU* CNAS_HSD_GetMatchedHrpdSysIndexListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMatchedHrpdSysIndexList);
}


VOS_VOID CNAS_HSD_InitMatchedHrpdSysIndexList(VOS_VOID)
{
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU              *pstMatchedHrpdSysIndex;

    pstMatchedHrpdSysIndex              = CNAS_HSD_GetMatchedHrpdSysIndexListAddr();
    pstMatchedHrpdSysIndex->usIndexNum  = 0;

    PS_MEM_SET(pstMatchedHrpdSysIndex->ausMatchedHrpdSysIndexList, 0, CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM * (sizeof(VOS_UINT16)));

    return;
}


VOS_UINT8   CNAS_HSD_IsCurAbortFlgSet_SysAcq(
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* 如果当前状态机不是CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_IsCurAbortFlgSet_SysAcq: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason == CNAS_HSD_GetAbortReason_SysAcq())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_VOID CNAS_HSD_SetAbnormalLostFlag(VOS_UINT8 ucIsAbnormalLost)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucIsAbnormalLostFLg = ucIsAbnormalLost;

    return;
}


VOS_UINT8 CNAS_HSD_GetAbnormalLostFlag(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucIsAbnormalLostFLg;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



