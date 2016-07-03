

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID            PS_FILE_ID_TAF_XPDS_CTX_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafLog.h"
#include "TafXpdsMntn.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMainTbl.h"
#include "cprocstime.h"
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmCpLinkCtrlTbl.h"
#include "TafXpdsFsmMpcProcTbl.h"
#include "TafXpdsFsmPdeProcTbl.h"
#include "TafXpdsFsmCpPdeProcTbl.h"
#include "TafXpdsCommFunc.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
/*****************************************************************************
  2 Global variable
*****************************************************************************/
TAF_XPDS_CONTEXT_STRU            g_stTafXpdsCtx;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XPDS_InitCurrFsmCtx(
    TAF_XPDS_FSM_CTX_STRU             *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   TAF_XPDS_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   TAF_XPDS_GetMainFsmDescAddr();
    pstCurrFsmCtx->enParentFsmId            =   TAF_XPDS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->ulState                  =   TAF_XPDS_L1_STA_INIT;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               TAF_XPDS_MAX_MSG_BUFFER_LEN);

    /* unFsmCtx本次迭代不涉及 */
}


VOS_VOID TAF_XPDS_InitFsmStackCtx(
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < TAF_XPDS_MAX_FSM_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = TAF_XPDS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = TAF_XPDS_L1_STA_BUTT;
    }
}


VOS_VOID TAF_XPDS_InitPosCtx(VOS_VOID)
{
    TAF_XPDS_InitDefaultCfgInfo();

    PS_MEM_SET(TAF_XPDS_GetCtrlInfoAddr(), 0, sizeof(TAF_XPDS_CTRL_INFO_STRU));

    PS_MEM_SET(TAF_XPDS_GetPublicDataAddr(), 0, sizeof(TAF_XPDS_PUBLIC_DATA_STRU));

    TAF_XPDS_InitPdePublicDataPdeInit();

    PS_MEM_SET(TAF_XPDS_GetMpcCtxAddr(), 0, sizeof(TAF_XPDS_MPC_CTX_STRU));

    PS_MEM_SET(TAF_XPDS_GetUpLinkCtxAddr(), 0, sizeof(TAF_XPDS_CAGPS_UPLINK_CTX_STRU));

    return;
}


VOS_VOID TAF_XPDS_InitCtx(VOS_VOID)
{
    TAF_XPDS_CONTEXT_STRU              *pstXpdsCtx = VOS_NULL_PTR;

    pstXpdsCtx = TAF_XPDS_GetCtxAddr();

    /* 初始化XPDS定时器上下文 */
    TAF_XPDS_InitAllTimers(pstXpdsCtx->astTimerCtx);

    /* 初始化XPDS当前状态机上下文 */
    TAF_XPDS_InitCurrFsmCtx(&(pstXpdsCtx->stCurFsm));

    /* 初始化XPDS状态机栈上下文 */
    TAF_XPDS_InitFsmStackCtx(&(pstXpdsCtx->stFsmStack));

    TAF_XPDS_InitInternalBuffer(&(pstXpdsCtx->stIntMsgQueue));

    TAF_XPDS_InitPdePublicDataTaskInit();

    TAF_XPDS_InitPosCtx();

    return;
}


VOS_VOID TAF_XPDS_InitFsmCtx_L1Main(VOS_VOID)
{
    /* 本次迭代不涉及 */

    return;
}



VOS_VOID  TAF_XPDS_LoadSubFsm(
    TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId,
    TAF_XPDS_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case TAF_XPDS_FSM_LINK_CTRL:
            pstCurFsm->ulState          = TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetFsmUpLinkFsmDescAddr();
            break;

        case TAF_XPDS_FSM_CP_LINK_CTRL:
            pstCurFsm->ulState          = TAF_XPDS_CP_LINK_CTRL_SUBSTA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetFsmCpLinkFsmDescAddr();
            break;

        case TAF_XPDS_FSM_MPC_PROC:
            pstCurFsm->ulState          = TAF_XPDS_L2_MPC_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetL2MpcProcFsmDescAddr();
            break;

        case TAF_XPDS_FSM_PDE_PROC:
            pstCurFsm->ulState          = TAF_XPDS_L2_PDE_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetL2PdeProcFsmDescAddr();
            break;

        case TAF_XPDS_FSM_CP_PDE_PROC:
            pstCurFsm->ulState          = TAF_XPDS_CP_L2_PDE_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetCpL2PdeProcFsmDescAddr();
            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}



VOS_VOID TAF_XPDS_PushFsm(
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack,
    TAF_XPDS_FSM_CTX_STRU             *pstNewFsm
)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;

    /* 入参指针检查 */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        XPDS_ERROR_LOG("TAF_XPDS_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* 栈深度检查 */
    if (pstFsmStack->usStackDepth >= TAF_XPDS_MAX_FSM_STACK_DEPTH)
    {
        XPDS_ERROR1_LOG("TAF_XPDS_PushFsm: Fsm Stack Depth = %d Error!",
                        pstFsmStack->usStackDepth);

        return;
    }

    /* push当前状态机上下文入栈 */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(TAF_XPDS_FSM_CTX_STRU));

    /* 栈深度增加 */
    pstFsmStack->usStackDepth++;

    return;
}


VOS_VOID TAF_XPDS_PopFsm(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack = TAF_XPDS_GetFsmStackAddr();
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();

    /* 检查栈空间是否为空 */
    if (0 == pstFsmStack->usStackDepth)
    {
        XPDS_ERROR_LOG("TAF_XPDS_PopFsm: FSM Stack is empty");

        return;
    }

    /* 状态机栈深度减少 */
    pstFsmStack->usStackDepth--;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(TAF_XPDS_FSM_CTX_STRU));
}



VOS_VOID TAF_XPDS_InitFsmL2(
    TAF_XPDS_FSM_ID_ENUM_UINT32        enFsmId
)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;
    TAF_XPDS_FSM_ID_ENUM_UINT32        enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId     = TAF_XPDS_GetCurrFsmId();
    ulParentEventType = TAF_XPDS_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    pstFsmStack = TAF_XPDS_GetFsmStackAddr();
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();
    TAF_XPDS_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId = enFsmId;

    /* 加载L2状态机 */
    TAF_XPDS_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());
}


VOS_VOID TAF_XPDS_QuitFsmL2(VOS_VOID)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm = TAF_XPDS_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  打印压栈前的L1和L2状态 */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    /* 状态机出栈操作 */
    TAF_XPDS_PopFsm();

    /*  打印当前的L1和L2状态 */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    return;
}



TAF_XPDS_CONTEXT_STRU* TAF_XPDS_GetCtxAddr(VOS_VOID)
{
    return  &g_stTafXpdsCtx;
}


TAF_XPDS_FSM_CTX_STRU* TAF_XPDS_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm);
}


TAF_XPDS_FSM_STACK_STRU* TAF_XPDS_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stFsmStack);
}


TAF_FSM_DESC_STRU* TAF_XPDS_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.pstFsmDesc);
}


TAF_XPDS_MSG_STRU* TAF_XPDS_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm.stEntryMsg);
}


TAF_XPDS_FSM_ID_ENUM_UINT32 TAF_XPDS_GetCurrFsmId(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.enFsmId);
}


VOS_UINT32 TAF_XPDS_GetFsmTopState(VOS_VOID)
{
    return (TAF_XPDS_GetCurFsmAddr()->ulState);
}


VOS_UINT16  TAF_XPDS_GetFsmStackDepth(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}


VOS_VOID TAF_XPDS_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = TAF_XPDS_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), ulCurrState);

    return;
}


VOS_VOID  TAF_XPDS_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}


VOS_UINT16  TAF_XPDS_GetFsmStackPopFlg(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


VOS_VOID TAF_XPDS_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理CNAS XSD入口消息的缓冲区地址 */
    pstEntryMsg                 = TAF_XPDS_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}


TAF_XPDS_INT_MSG_QUEUE_STRU* TAF_XPDS_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stIntMsgQueue);
}


VOS_VOID TAF_XPDS_InitInternalBuffer(
    TAF_XPDS_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < TAF_XPDS_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;

    return;
}


VOS_VOID  TAF_XPDS_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = TAF_XPDS_GetIntMsgNum();

    /* 检查内部消息队列，是否有缓存队列已满 */
    if (TAF_XPDS_MAX_INT_MSG_QUEUE_NUM <= ucIntMsgNum)
    {
        PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

        XPDS_ERROR_LOG("TAF_XPDS_PutMsgInIntMsgQueue: msg queue is full!");

        return;
    }

    /* 保存当前信息 */
    TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}


VOS_UINT8 *TAF_XPDS_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* 获取下一个缓存的消息消息 */
        pstIntMsg = TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* 内部消息数目减少一个 */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* 前移内部消息 */
            PS_MEM_MOVE(&(TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* 对消息队列中尾部的消息清为空指针 */
        TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}


VOS_UINT8 TAF_XPDS_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}



TAF_XPDS_TIMER_CTX_STRU* TAF_XPDS_GetTimerCtxAddr(VOS_VOID)
{
    return g_stTafXpdsCtx.astTimerCtx;
}


TAF_XPDS_INITIAL_TYPE_ENUM_UINT32 TAF_XPDS_GetCgpsInitialType(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enAgpsType;
}


TAF_XPDS_FIX_MODE_ENUM_UINT8 TAF_XPDS_GetAgpsFixMode(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enFixMode;
}


VOS_VOID TAF_XPDS_SetAgpsFixMode(TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode)
{
    g_stTafXpdsCtx.stCagpsCfg.enFixMode = enFixMode;
    return;
}



TAF_XPDS_CFG_INFO_STRU* TAF_XPDS_GetAgpsCfg(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCagpsCfg);
}


TAF_XPDS_CTRL_INFO_STRU* TAF_XPDS_GetCtrlInfoAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCtrlInfo);
}


TAF_XPDS_PUBLIC_DATA_STRU* TAF_XPDS_GetPublicDataAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPublicData);
}


VOS_VOID TAF_XPDS_SetPosProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPosProcRslt
)
{
    TAF_XPDS_GetPublicDataAddr()->enPosProcRslt = enPosProcRslt;
}


TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetPosProcRslt(VOS_VOID)
{
    return TAF_XPDS_GetPublicDataAddr()->enPosProcRslt;
}


TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8 TAF_XPDS_GetUpLinkStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus;
}


VOS_VOID TAF_XPDS_UpdateUpLinkStatus(VOS_VOID)
{
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcBindStatus;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeBindStatus;

    enMpcBindStatus = TAF_XPDS_GetMpcServerStatus();
    enPdeBindStatus = TAF_XPDS_GetPdeServerStatus();

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT == enMpcBindStatus)
     && (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enPdeBindStatus))
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED;
    }
    else if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enMpcBindStatus)
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_MPC_CONNECTED;
    }
    else if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enPdeBindStatus)
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_PDE_CONNECTED;
    }
    else
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_NOT_EXISTED;
    }

    return;
}


AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32 TAF_XPDS_GetDataCallStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enDataCallState;
}


VOS_VOID TAF_XPDS_SetDataCallStatus(
    AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32         enDataCallState
)
{
    g_stTafXpdsCtx.stUplinkCtx.enDataCallState = enDataCallState;

    return;
}


AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetMpcServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus;
}


AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetPdeServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus;
}


VOS_VOID TAF_XPDS_SetMpcServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus = enMpcServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}


VOS_VOID TAF_XPDS_SetPdeServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus = enPdeServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}


TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetUpLinkAbortScene(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene;
}


VOS_VOID TAF_XPDS_SetUplinkAbortScene(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
)
{
    g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene = enUpLinkAbortScene;

    return;
}


VOS_UINT8  TAF_XPDS_GetCorrelationId(VOS_VOID)
{
    VOS_UINT8                           ucCorrelationId = 0;

    ucCorrelationId  = TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId;

    TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId++;

    return ucCorrelationId;
}


VOS_VOID TAF_XPDS_SetFwdPdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    PS_MEM_CPY(&(TAF_XPDS_GetPdePublicData()->stFwdPdMsgHeader),
               pstPdMsgHeader,
               sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));
}


VOS_VOID TAF_XPDS_InitDefaultCfgInfo(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    VOS_UINT8                           ucLastOmTestFlag;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    /* 需要保存上一次的OM test 标志 */
    ucLastOmTestFlag = pstCagpsCfg->ucIsOmTestMode;

    PS_MEM_SET(pstCagpsCfg, 0x0, sizeof(TAF_XPDS_CFG_INFO_STRU));

    pstCagpsCfg->enFixMode      = TAF_XPDS_MSA_MODE;
    pstCagpsCfg->enAgpsType     = TAF_XPDS_SI;
    pstCagpsCfg->enCallType     = TAF_XPDS_USER_PLANE;
    pstCagpsCfg->usFixNum       = 1;
    pstCagpsCfg->enOmFixRslt    = NAS_OM_CDMA_GPS_FIX_RSLT_BUTT;

    pstCagpsCfg->ucIsOmTestMode = ucLastOmTestFlag;

    return;
}


VOS_VOID TAF_XPDS_InitProvGpsEph(
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph
)
{
    PS_MEM_SET(pstProvEph, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU));

    return;
}


VOS_VOID TAF_XPDS_InitProvGpsAlm(
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                 *pstProvAlm
)
{
    PS_MEM_SET(pstProvAlm, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU));

    return;
}


VOS_VOID TAF_XPDS_SetTimeStamp(
    TAF_XPDS_TIME_STAMP_STRU            *pstTimeStamp
)
{
    VOS_UINT64                          ullSecNum = 0;

    if (TAF_SDC_SYS_MODE_EVDO == TAF_SDC_GetSysMode())
    {
        ullSecNum = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD) * 8 / 100;
    }
    else
    {
        ullSecNum = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X)  * 8 / 100;
    }

    pstTimeStamp->ulWeekNum = (VOS_UINT32)(ullSecNum / (7 * 24 * 3600));
    pstTimeStamp->ulSecNum  = (VOS_UINT32)(ullSecNum % (7 * 24 * 3600));

    return;
}



TAF_XPDS_PDE_PUBLIC_DATA_STRU * TAF_XPDS_GetPdePublicData(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPdePubData);
}



VOS_VOID TAF_XPDS_InitPdePublicDataTaskInit(VOS_VOID)
{
    PS_MEM_SET(TAF_XPDS_GetPdePublicData(), 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));
}



VOS_VOID TAF_XPDS_InitPdePublicDataPdeInit(VOS_VOID)
{
    TAF_XPDS_PDE_PUBLIC_DATA_STRU      *pstPdePubData = VOS_NULL_PTR;
    VOS_UINT8                           ucLastSessTag;

    pstPdePubData = TAF_XPDS_GetPdePublicData();

    ucLastSessTag = pstPdePubData->ucSessTagInRsvPdMsgHeader;

    PS_MEM_SET(pstPdePubData, 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));

    pstPdePubData->ucSessTagInRsvPdMsgHeader = ucLastSessTag;
}


VOS_VOID TAF_XPDS_SetGpsEphDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished = ucIsFinisehd;
}



VOS_UINT8 TAF_XPDS_GetGpsEphDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished);
}



VOS_VOID TAF_XPDS_SetGpsAlmDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished = ucIsFinisehd;
}



VOS_UINT8 TAF_XPDS_GetGpsAlmDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished);
}



VOS_VOID TAF_XPDS_SetPdeSessionStatus(
    TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8                  enPdeSessionStatus
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus) = enPdeSessionStatus;
}



TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 TAF_XPDS_GetPdeSessionStatus(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus);
}



VOS_VOID TAF_XPDS_SetPdeSessionTriggerType(
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8            enPdeSessionTriggerType
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType) = enPdeSessionTriggerType;
}



TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 TAF_XPDS_GetPdeSessionTriggerType(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType);
}



VOS_VOID TAF_XPDS_SetSessTagInRsvPdMsgHeader(VOS_UINT8 ucSessTag)
{
    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = ucSessTag;
}



VOS_UINT8 TAF_XPDS_GetSessTagInRsvPdMsgHeader(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader);
}



VOS_VOID TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader(VOS_VOID)
{
    VOS_UINT8                           ucLastSessTag;

    ucLastSessTag = TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader;

    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = (ucLastSessTag + 1) % 32;
}



VOS_UINT32 TAF_XPDS_GetPrmTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPsuRangeMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}


VOS_UINT32 TAF_XPDS_GetPilotPhaseTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPilotPhaseMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}


VOS_UINT16 TAF_XPDS_GetGpsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usGpsClientId;
}


VOS_UINT16 TAF_XPDS_GetApClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usApClientId;
}


VOS_UINT16 TAF_XPDS_GetUtsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usUtsClientId;
}


VOS_VOID TAF_XPDS_SetGpsClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usGpsClientId = usClientId;

    return;
}


VOS_VOID TAF_XPDS_SetApClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usApClientId = usClientId;

    return;
}


VOS_VOID TAF_XPDS_SetUtsClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usUtsClientId = usClientId;

    return;
}


TAF_XPDS_MPC_CTX_STRU* TAF_XPDS_GetMpcCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stMpcCtx);
}


TAF_XPDS_CAGPS_UPLINK_CTX_STRU* TAF_XPDS_GetUpLinkCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stUplinkCtx);
}


VOS_VOID TAF_XPDS_SetOmTestFlag(VOS_UINT8 ucIsOmTestMode)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode = ucIsOmTestMode;
}


VOS_UINT8 TAF_XPDS_GetOmTestFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode);
}


VOS_VOID TAF_XPDS_SetOmFixRslt(VOS_UINT8 enFixRslt)
{
    TAF_XPDS_GetAgpsCfg()->enOmFixRslt = enFixRslt;
}


NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 TAF_XPDS_GetOmFixRslt(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->enOmFixRslt);
}


VOS_VOID TAF_XPDS_SetOmTestAbortFlag(VOS_UINT8 isAborted)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted = isAborted;
}


VOS_UINT8 TAF_XPDS_GetOmTestAbortFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted);
}


VOS_VOID TAF_XPDS_SetOmTestPdeProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPdeProcRslt
)
{
    TAF_XPDS_GetAgpsCfg()->enOmTestPdeProcRslt = enPdeProcRslt;
}


TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetOmTestPdeProcRslt(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->enOmTestPdeProcRslt);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

