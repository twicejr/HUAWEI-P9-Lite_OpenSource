


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasCommDef.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcMain.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcFsmPowerOff.h"

#include "MsccMmcInterface.h"

#include "NasMmcFsmPlmnSelection.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMC CTX,用于保存MMC状态机,描述表 */
NAS_MMC_CONTEXT_STRU                    g_stNasMmcCtx;

/*lint -save -e958 */



VOS_UINT32 g_aulFsmEntryEventType[] =
{
    NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
    NAS_BuildEventType(UEPS_PID_MSCC, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
#endif
    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_LIST_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ANYCELL_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HPLMN_TIMER),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_GET_GEO_REQ),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND)
#endif
};



NAS_MMC_CONTEXT_STRU* NAS_MMC_GetMmcCtxAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx);
}


NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetCurFsmAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm);
}


NAS_MMC_FSM_STACK_STRU* NAS_MMC_GetFsmStackAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stFsmStack);
}


NAS_FSM_DESC_STRU* NAS_MMC_GetCurFsmDesc(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.pstFsmDesc);
}


NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.stEntryMsg);
}


NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enFsmId);
}


VOS_UINT32 NAS_MMC_GetCurrFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.stEntryMsg.ulEventType);
}


NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetParentFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enParentFsmId);
}


VOS_UINT32 NAS_MMC_GetParentFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.ulParentEventType);
}


NAS_MMC_FSM_EXTRA_CTX_UNION* NAS_MMC_GetParentFsmCtx(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.punParentFsmCtx);
}



NAS_MMC_MSG_QUEUE_STRU* NAS_MMC_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBufferEntryMsgQueue);
}


VOS_VOID NAS_MMC_FSM_PushFsm(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack,
    NAS_MMC_FSM_CTX_STRU                *pstNewFsm
)
{
    NAS_MMC_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= NAS_MMC_MAX_STACK_DEPTH )
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* 将当前状态机所有CTX都需要保存起来 */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MMC_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}


VOS_VOID NAS_MMC_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();
    pstCurFsm                       = NAS_MMC_GetCurFsmAddr();

    /* 栈已空 */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(NAS_MMC_FSM_CTX_STRU));

    return;
}


NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetBottomFsmInFsmStack(VOS_VOID)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack     = VOS_NULL_PTR;

    /* 获取状态机栈的地址 */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();

    /* 空栈直接退出 */
    if (0 == pstFsmStack->usStackDepth)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetBottomFsmInFsmStack:FsmStack is empty.");
        return VOS_NULL_PTR;
    }

    return &(pstFsmStack->astFsmStack[0]);
}


VOS_VOID NAS_MMC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理NAS_MMC入口消息的缓冲区地址 */
    pstEntryMsg                 =   NAS_MMC_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_MMC_SaveCurEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}


VOS_VOID  NAS_MMC_LoadSubFsm(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MMC_SWITCH_ON_STA_SWITCH_ON_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MMC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MMC_POWER_OFF_STA_POWEROFF_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_SELECTION :
            pstCurFsm->ulState                  = NAS_MMC_PLMN_SELECTION_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_MMC_FSM_ANYCELL_SEARCH :
            pstCurFsm->ulState                  = NAS_MMC_ANYCELL_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetAnyCellSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_SYSCFG :
            pstCurFsm->ulState                  = NAS_MMC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSysCfgFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CELLRESEL :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCellReselFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_HO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_HO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysHoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CCO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CCO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCcoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_OOS:
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_OOS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysOosFsmDescAddr();
            break;



        case NAS_MMC_FSM_PLMN_LIST:
            pstCurFsm->ulState                  = NAS_MMC_PLMN_LIST_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnListFsmDescAddr();
            break;



        case NAS_MMC_FSM_BG_PLMN_SEARCH:
            pstCurFsm->ulState                  = NAS_MMC_BG_PLMN_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetBgPlmnSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_GET_GEO:
            pstCurFsm->ulState                  = NAS_MMC_GET_GEO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetGeoFsmDescAddr();
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadSubFsm:Invalid Fsm Id");
            break;
    }


    /*执行初始化L2状态机的函数*/
    pstCurFsm->pstFsmDesc->pfInitHandle();
}


VOS_VOID NAS_MMC_FSM_InitFsmL2(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */

    enParentFsmId                       = NAS_FSM_BUTT;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();
    pstFsmStack                         = NAS_MMC_GetFsmStackAddr();

    /*  打印压栈前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();


    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId                       = pstCurFsm->enFsmId;
    ulParentEventType                   = pstCurFsm->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    NAS_MMC_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId                  = enFsmId;

    /* 加载L2状态机 */
    NAS_MMC_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId            = enParentFsmId;
    pstCurFsm->ulParentEventType        = ulParentEventType;

    usStackDepth = pstFsmStack->usStackDepth;

    pstCurFsm->punParentFsmCtx = VOS_NULL_PTR;

    /* 增加状态机栈深的异常保护 */
    if ( (0            < usStackDepth)
      && (usStackDepth <= NAS_MMC_MAX_STACK_DEPTH) )
    {
        /* 记录上层状态机的数据内容地址 */
        pstCurFsm->punParentFsmCtx          = &(pstFsmStack->astFsmStack[(usStackDepth - 1)].unFsmCtx);
    }


    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();
}



VOS_VOID NAS_MMC_FSM_QuitFsmL2( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    pstCurFsm->pstFsmDesc->pfInitHandle();

    /*  打印压栈前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    /* 状态机出栈操作 */
    NAS_MMC_FSM_PopFsm();

    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    return;
}

VOS_VOID  NAS_MMC_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = NAS_MMC_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    return;
}



VOS_UINT32 NAS_MMC_GetFsmTopState( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* 获取当前状态机 */
    pstCurFsm               = NAS_MMC_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}


VOS_UINT16  NAS_MMC_GetFsmStackDepth( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}


NAS_MMC_TIMER_CTX_STRU*  NAS_MMC_GetTimerAddr( VOS_VOID )
{
    return g_stNasMmcCtx.astMmcTimerCtx;
}


VOS_VOID  NAS_MMC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_MMC_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_MMC_MAX_MSG_QUEUE_NUM )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:No Empty buffer");

        NAS_MMC_LogBufferQueueMsg(VOS_TRUE);

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
}


VOS_VOID NAS_MMC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if ( pstMsgHeader->ulLength >= ( NAS_MMC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:Len too Long");
        return;
    }

    /* 比较消息优先级,判断是否需要保存在缓存池中 */
    if ( VOS_FALSE == NAS_MMC_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:already exist msg");
        return;
    }

    /* 将消息缓存在缓存内存池中 */
    NAS_MMC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return;
}



VOS_UINT32  NAS_MMC_GetNextInterSysCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextInterSysCachedMsg:No Empty suspend buffer");
            break;
    }

    return ulCacheFlg;
}




VOS_UINT32  NAS_MMC_GetNextUserCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ)  :
#if (FEATURE_ON == FEATURE_CSG)
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ):
#endif
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextUserCachedMsg:No Empty buffer");
            break;
    }

    return ulCacheFlg;

}


VOS_UINT32 NAS_MMC_GetNextHighPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          i;
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheFlg  ;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    ulCacheFlg                          = VOS_FALSE;


    /* 必须先获取所有的状态机的非入口消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* 优先获取状态机非入口消息 */
        if ( VOS_FALSE == NAS_MMC_IsFsmEntryEventType(pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType) )
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;

        }

        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* 认为intersys消息的优先级比用户请求消息的优先级高,目前仅在BG搜索过程
       中,收到rrmm_suspend_ind消息后会打断当前状态机缓存intersys消息*/
    /* 必须先获取所有的intersys消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        if ( VOS_TRUE == NAS_MMC_GetNextInterSysCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry)) )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;
        }

        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* 必须先获取所有的高优先级消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* 用户的缓存消息优先级次高 */
        ulCacheFlg = NAS_MMC_GetNextUserCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry));
        if ( VOS_TRUE == ulCacheFlg )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
        }


        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }



    return VOS_FALSE;
}


VOS_UINT32  NAS_MMC_GetNextNormalPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astMsgQueue[0].stMsgEntry),
               sizeof(NAS_MMC_ENTRY_MSG_STRU));

    /* 消息已经取出则清除当前缓存 */
    NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_GetNextCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }


    /* 如果存在高优先级的消息,先返回高优先级的消息, 优先级高的消息优先得到处理 */
    if ( VOS_TRUE == NAS_MMC_GetNextHighPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    /* 获取普通的缓存消息成功,返回普通的缓存消息 */
    if ( VOS_TRUE == NAS_MMC_GetNextNormalPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_UINT32  NAS_MMC_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }

    }


    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}



VOS_VOID NAS_MMC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);

    return;
}



VOS_VOID NAS_MMC_ClearAllCacheMsg( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    pstMsgQueue->ucCacheMsgNum          = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_MSG_QUEUE_NUM ; i++ )
    {
        PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   0x00,
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
    }

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
    return;
}



VOS_VOID  NAS_MMC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    NAS_MMC_ClearAllRegAttemptCount_L1Main();

    /* 默认AVAILABLE COUNTER为NORMAL类型 */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);
}



VOS_VOID  NAS_MMC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;

    VOS_UINT8                                              *pucLastImsi = VOS_NULL_PTR;

    VOS_UINT32                                              i;

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSwitchOnRecord                   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnRecord->aucSwitchOnRatPrio;

    pucLastImsi = NAS_MMC_GetLastImsi_SwitchOn();

    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();

    /* Switch On状态机上下文中设置接入层开机优先级顺序信息的初始化:
       搜网索引初始化为0,每向接入层发送卡机后，该索引自增1，表示要发开机的模的接入模式 */
    pstSwitchOnRecord->ucSwitchOnIndex = 0;

    /* 设置需要下发开机接入技术的总个数 */
    pstSwitchOnRecord->ucTotalSwitchOnRatNum = 0;

    /* SYSCFG状态机上下文中设置接入层优先级顺序信息的初始化:
       接入模式全部初始化为NAS_MML_NET_RAT_TYPE_BUTT */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pucSwitchOnRatPrio[i]           = NAS_MML_NET_RAT_TYPE_BUTT;
    }


    /* 初始化状态机上下文中的开机钱的IMSI信息 */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pucLastImsi[i] = NAS_MML_IMSI_INVALID;
    }
}


NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU* NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSwitchOnSettingRecord_SwitchOn,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.stSwitchOnRecord);
}




VOS_VOID NAS_MMC_AddSwitchOnIndex_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSwitchOnIndex_SwitchOn,ERROR:FsmId Error");
    }

    /* 获取状态机中的要设置SwitchOn接入模所对应的索引和列表地址 */
    pstSwitchOnRecord   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* 更新INDEX索引,指向下一个要进行SwitchOn设置的接入技术 */
    pstSwitchOnRecord->ucSwitchOnIndex ++;

    /* 返回 */
    return ;
}




NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSendingRat_SwitchOn(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucNextSwitchOnRat;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSendingRat_SwitchOn,ERROR:FsmId Error");
    }

    pstSwitchOnRecord      = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* 获取状态机中的要设置SwitchOn接入模所对应的索引和列表地址 */
    pucSwitchOnRatPrio     = pstSwitchOnRecord->aucSwitchOnRatPrio;

    /* 如果索引以到达设置的总个数，返回接入技术为无效值，表示SwitchOn设置结束 */
    if ( pstSwitchOnRecord->ucSwitchOnIndex >= pstSwitchOnRecord->ucTotalSwitchOnRatNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* 取得数组中索引所对应的接入技术 */
    ucNextSwitchOnRat                     = pucSwitchOnRatPrio[pstSwitchOnRecord->ucSwitchOnIndex];

    /* 返回需要SwitchOn设置的接入技术 */
    return ucNextSwitchOnRat;
}


VOS_VOID NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio       = VOS_NULL_PTR;
    VOS_UINT8                                               ucRatIndex;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSwitchOnSendingOrder_SwitchOn,ERROR:FsmId Error");
    }

    ucRatIndex                          = 0;

    /* 取得当前 SwitchOn状态机上下文中的记录设置接入层优先级顺序信息 */
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnSettingRecord->aucSwitchOnRatPrio;

    /* 设置下发SwitchOn请求的顺序为GLW,若LTE不支持，则为GW */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif

    /* 如果平台支持W或TD，需要给U模发开机请求 */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    /* 设置需要下发开机接入层的总个数 */
    pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum = ucRatIndex;

    return;
}


VOS_UINT8* NAS_MMC_GetLastImsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastImsi_SwitchOn,ERROR:FsmId Error");
    }

    /* 返回存储开机前NV中保存的IMSI的内容的首地址 */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastImsi;
}




VOS_VOID  NAS_MMC_InitFsmCtx_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_NET_RAT_TYPE_BUTT );

    /* 初始化关机时的从模列表 */
    pstSlaveModeRatList           = NAS_MMC_GetSlaveModeRatList_PowerOff();
    pstSlaveModeRatList->ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstSlaveModeRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }
}


VOS_VOID  NAS_MMC_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stInvalidPlmnId;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
#endif

    /* 设置Abort标志为VOS_FALSE */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_FALSE);

    /* 设置Rel Request标志为VOS_FALSE */
    NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetInterSysSuspendRat_PlmnSelection(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 设置等待注册标志为NULL */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* 设置CS注册结果触发的后续动作为BUTT */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 设置PS注册结果触发的后续动作为BUTT */
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 初始化CS、PS cause值为BUTT */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    /* 初始化搜网列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* 初始化搜网状态机上下文中不同接入技术的覆盖及搜索信息 */
    NAS_MMC_InitSearchRatInfo_PlmnSelection();

    pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
    PS_MEM_SET(pstForbRoamLaInfo, 0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(&stPlmnId);
#endif

    PS_MEM_SET(&stInvalidPlmnId, 0x0, sizeof(stInvalidPlmnId));
    stInvalidPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stInvalidPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;

    NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(&stInvalidPlmnId);

    NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_BUTT);

    NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    return;
}


VOS_VOID  NAS_MMC_InitFsmCtx_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList      = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

    pstAnyCellSearchCtx = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    /* 获取MS当前支持的接入技术 */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* 初始化ANYCELL状态机的接入技术为当前MS支持的接入技术 */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio = (*pstRatPrioList);

    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    /* 初始化接入技术为未搜索过 */
    for (i = 0; i < ucRatNum; i++)
    {
        pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_FALSE;
    }

    /* 设置Abort标志为VOS_FALSE */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_FALSE);

}


VOS_VOID  NAS_MMC_InitFsmCtx_BgPlmnSearch()
{
    NAS_MML_PLMN_ID_STRU                stInvalidPlmnId;
    NAS_MML_EQUPLMN_INFO_STRU           stEquPlmnInfo;

    stInvalidPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    PS_MEM_SET(&stEquPlmnInfo, 0x00, sizeof(stEquPlmnInfo));


    /* 记录状态机上下文中Abort事件类型0xFFFFFFFF */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(NAS_MML_INVALID_EVENT_TYPE);

    /* 初始化ABORT标志为无打断 */
    NAS_MMC_SetAbortType_BgPlmnSearch(NAS_MMC_ABORT_BUTT);

    NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_FALSE);

#if (FEATURE_OFF == FEATURE_LTE)
    /* 初始化保留字段 */
    PS_MEM_SET(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve,
               0X00,
               sizeof(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve));
#endif

    /* 初始化RegInfo信息 */
    NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 初始化当前正在尝试的高优先级网络及其接入技术信息 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* 初始化VPlmn信息 */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* 初始化EPlmn信息 */
    NAS_MML_InitEquPlmnInfo(&stEquPlmnInfo);
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(&stInvalidPlmnId, &stEquPlmnInfo);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_FALSE);
#endif
}



VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCellResel(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel();
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_FALSE);
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_FALSE);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_BUTT);
}




VOS_VOID  NAS_MMC_InitFsmCtx_InterSysHo(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysHo();
    NAS_MMC_ClearAllResumeRspFlag_InterSysHo();

    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);
}




VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCco(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCco();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();
}




VOS_VOID  NAS_MMC_InitFsmCtx_InterSysOos(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysOos();
    NAS_MMC_ClearAllResumeRspFlag_InterSysOos();
}



VOS_VOID  NAS_MMC_InitFsmCtx_PlmnList(VOS_VOID)
{
    /* 初始化搜索的接入技术信息*/
    NAS_MMC_InitSearchRatInfo_PlmnList();

    /* 设置状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_FALSE);

    /* 设置通知MSCC标记为假 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_FALSE);

    /* 初始化所搜到的各个网络信息 */
    NAS_MMC_InitSearchedPlmnListInfo_PlmnList();

    /* 清除等待所有域的标记信息 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* 清除CS/PS的addition值 */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* 保存当前L disable状态到状态机上下文 */
    NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
#endif

    /* 设置anycell搜网标记 */
    NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_FALSE);

#if (FEATURE_ON == FEATURE_CSG)
    /* 初始化CSG搜索到的CSG ID结果列表信息 */
    NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList();
#endif

}



VOS_VOID  NAS_MMC_InitFsmCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_GET_GEO_CTX_STRU       *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx    = NAS_MMC_GetFsmCtxAddr_GetGeo();

    /* 状态机变量在这里初始化 */
    PS_MEM_SET(pstGetGeoCtx, 0, sizeof(NAS_MMC_FSM_GET_GEO_CTX_STRU));

    /* 设置状态机ABORT标识为无效 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_FALSE);

    /* 设置通知MSCC回复标记为无效 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_FALSE);

    /* 设置状态机任务阶段为BUTT */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BUTT);

    /* 初始化GET GEO接入技术优先级列表 */
    pstGetGeoCtx->stGetGeoRatInfoList.ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_FALSE;
    }

    return;
}





VOS_VOID  NAS_MMC_InitPlmnSearchCtrlCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstPlmnSearchCtrl
)
{
    pstPlmnSearchCtrl->ucWrrLimitServiceInd             = VOS_FALSE;
    pstPlmnSearchCtrl->stUserSpecPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_BUTT;

    if ( NAS_MMC_INIT_CTX_STARTUP  == enInitType )
    {
        pstPlmnSearchCtrl->enSelectionMode                  = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;

        pstPlmnSearchCtrl->ucUserSpecPlmnRegStatus          = VOS_TRUE;
    }

    pstPlmnSearchCtrl->stUserReselPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = VOS_FALSE;
    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    pstPlmnSearchCtrl->enAsCellCampOn                   = NAS_MMC_AS_CELL_NOT_CAMP_ON;
    pstPlmnSearchCtrl->enSpecPlmnSearchState            = NAS_MMC_SPEC_PLMN_SEARCH_STOP;

    NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* 默认不支持ncell搜网 */
    NAS_MMC_SetNcellSearchFirstTimerLen(0);
    NAS_MMC_SetNcellSearchSecondTimerLen(0);


    NAS_MMC_SetNcellSearchFlag(VOS_FALSE);
    NAS_MML_InitEquPlmnInfo(&pstPlmnSearchCtrl->stNcellSearchInfo.stOtherModemEplmnInfo);
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo));
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo));


    NAS_MMC_SetRegCtrl(NAS_MMC_REG_CONTROL_BY_3GPP_MMC);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    NAS_MMC_InitUserDPlmnNPlmnInfo(&pstPlmnSearchCtrl->stDplmnNplmnCtx);

    NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
    NAS_MMC_ClearDisabledLtePlmnId();

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);

    NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(VOS_FALSE);
    NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(&pstPlmnSearchCtrl->stNonOosPlmnSearchFeatureSupportCfg);
    NAS_MMC_InitOosSearchStrategyInfo(&pstPlmnSearchCtrl->stOosPlmnSearchStrategyInfo);

    NAS_MMC_InitGetGeoInfo(&pstPlmnSearchCtrl->stGetGeoInfo);

    pstPlmnSearchCtrl->stLastCampedPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stLastCampedPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstPlmnSearchCtrl->stLastCampedPlmnId.enRat = NAS_MML_NET_RAT_TYPE_BUTT;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.ucAllowSrchLteFlg         = VOS_TRUE;
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.enLteSysPriClass          = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
#endif
}


VOS_VOID  NAS_MMC_InitServiceInfo(
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo
)
{
    pstServiceInfo->enCsCurrService = NAS_MMC_NO_SERVICE;
    pstServiceInfo->enPsCurrService = NAS_MMC_NO_SERVICE;
}


VOS_VOID  NAS_MMC_InitMaintainCtx(
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMaintainInfo
)
{
    pstMaintainInfo->ucGcfCh9_4_3_AND_Ch26_7_4_3    = VOS_FALSE;

    pstMaintainInfo->ucActionType                   = NAS_MMC_AT_ACTION_TYPE_START_FOREVER;
    pstMaintainInfo->ucMsgType                      = NAS_MMC_AT_MSG_TYPE_CELL_SIGN;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_ID;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_BLER;


    pstMaintainInfo->ucSignThreshold       = 0;   /* 默认接入层取缺省值*/

    pstMaintainInfo->ucMinRptTimerInterval = 0; /*默认间隔时间*/
}



VOS_VOID  NAS_MMC_InitPlmnRegRejCtx(
    NAS_MMC_PLMN_REG_REJ_CTX_STRU          *pstPlmnRegRejInfo
)
{
    VOS_UINT32                          i;

    pstPlmnRegRejInfo->ucPlmnRegInfoNum     = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_REG_PLMN_INFO_NUM ; i++ )
    {
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#if (FEATURE_ON == FEATURE_LTE)
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    }
}



VOS_VOID  NAS_MMC_InitCurrFsmCtx(
    NAS_MMC_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MMC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MMC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MMC_L1_STA_NULL;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    pstCurrFsmCtx->enParentFsmId            =   NAS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;


    /* 默认AVAILABLE COUNTER为NORMAL类型 */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_MMC_MAX_MSG_BUFFER_LEN);
}


VOS_VOID  NAS_MMC_InitFsmStackCtx(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < NAS_MMC_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MMC_L1_STA_BUTT;
    }
}


VOS_VOID  NAS_MMC_InitInternalBuffer(
    NAS_MMC_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    pstBufferEntryMsgQueue->ucCurrIndex     = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(pstBufferEntryMsgQueue->astMsgQueue));
}


VOS_VOID NAS_MMC_InitNetScanReqCtx(
    NAS_MMC_NET_SCAN_REQ_CTX_STRU      *pstNetScanReqCtx
)
{
    PS_MEM_SET( &(pstNetScanReqCtx->stNetScanReq), 0X00, sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) );

    pstNetScanReqCtx->stNetScanReq.ucRat = NAS_MML_NET_RAT_TYPE_BUTT;

    return;
}



NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrEntryMsg(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.stEntryMsg);
}



NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU *NAS_MMC_GetPlmnSearchCtrl(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl);
}


NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionMode(VOS_VOID)
{
    /* CL模式下无条件返回自动搜网 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        return NAS_MMC_PLMN_SELECTION_MODE_AUTO;
    }
#endif

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode);
}


VOS_UINT8 NAS_MMC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag);
}


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetOtherModemPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId);
}


VOS_VOID NAS_MMC_SetOtherModemPlmnId(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId = *pstPlmnId;

}



VOS_VOID NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8 ucUtranSkipWPlmnSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
}



NAS_MMC_NCELL_SEARCH_INFO_STRU* NAS_MMC_GetNcellSearchInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNcellSearchInfo);
}



VOS_UINT8 NAS_MMC_GetNcellSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag);
}


VOS_VOID NAS_MMC_SetNcellSearchFlag(VOS_UINT8 ucNcellSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag = ucNcellSearchFlag;
}


VOS_UINT8 NAS_MMC_GetNcellSearchFirstTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen);
}


VOS_VOID NAS_MMC_SetNcellSearchFirstTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen = ucNcellSearchTimerLen;
}



VOS_UINT8 NAS_MMC_GetNcellSearchSecondTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen);
}


VOS_VOID NAS_MMC_SetNcellSearchSecondTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen = ucNcellSearchTimerLen;
}




VOS_VOID Mmc_ComGetPlmnSearchMode(VOS_UINT8 *pucReselMode)
{
    *pucReselMode = NAS_MMC_GetPlmnSelectionMode();
    return;
}


VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8      enSelectionMode
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode = enSelectionMode;
}


NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8 NAS_MMC_GetAsCellCampOn(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn);
}


VOS_VOID NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8   enAsCellCampOn)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn = enAsCellCampOn;
}


NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 NAS_MMC_GetSpecPlmnSearchState(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState);
}


VOS_VOID NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState = enSpecPlmnSearchState;
}



NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserSpecPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId);
}



VOS_UINT32 NAS_MMC_GetUserSpecPlmnRegisterStatus()
{
    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus;
}



NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserReselPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserReselPlmnId);
}



VOS_VOID NAS_MMC_SetUserSpecPlmnId(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId),
               pstPlmnInfo,
               sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
}



VOS_VOID NAS_MMC_SetUserSpecPlmnRegisterStatus(
    VOS_UINT8                           ucRegisterStatus
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus = ucRegisterStatus;
}



VOS_VOID NAS_MMC_SetUserReselPlmnId(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    pstUserReselPlmn->stPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstUserReselPlmn->stPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstUserReselPlmn->enRat          = enRat;
}



NAS_MMC_PLMN_REG_REJ_CTX_STRU *NAS_MMC_GetPlmnRegRejInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnRegInfo);
}


NAS_MMC_SERVICE_INFO_CTX_STRU *NAS_MMC_GetServiceInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stServiceInfo);
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrCsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService);
}


NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrPsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService);
}




VOS_UINT32 NAS_MMC_IsCsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsPsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNormalServiceStatus(VOS_VOID)
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



NAS_MMC_MAINTAIN_CTX_STRU *NAS_MMC_GetMaintainInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stMaintainInfo);
}


NAS_MMC_SERVICE_ENUM_UINT8  NAS_MMC_ConverMmStatusToMmc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8           enRegDomain,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8    enServiceStatus
)
{
    switch ( enServiceStatus )
    {
        case MM_COM_SRVST_NORMAL_SERVICE :
            return NAS_MMC_NORMAL_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE_REGION :
            return NAS_MMC_LIMITED_SERVICE_REGION;

        case MM_COM_SRVST_NO_IMSI :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_NO_SERVICE :
            return NAS_MMC_NO_SERVICE;

        default:
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ConverMmStatusToMmc,", enServiceStatus);
            break;
    }

    if ( NAS_MMC_REG_DOMAIN_CS == enRegDomain )
    {
        return NAS_MMC_GetCsServiceStatus();
    }
    else
    {
        return NAS_MMC_GetPsServiceStatus();
    }
}





VOS_VOID NAS_MMC_UpdateDomainServiceStatus(
    VOS_UINT8                           enCurrDomain,
    NAS_MMC_SERVICE_ENUM_UINT8          enCurrService
)
{
    /* 如果存在CS域，则更新CS域的结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_CS == (NAS_MMC_WAIT_REG_RESULT_IND_CS & enCurrDomain) )
    {
        NAS_MMC_SetCsServiceStatus(enCurrService);
    }

    /* 如果存在PS域，则更新PS域的结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_PS == (NAS_MMC_WAIT_REG_RESULT_IND_PS & enCurrDomain) )
    {
        NAS_MMC_SetPsServiceStatus(enCurrService);
    }
}





VOS_VOID    NAS_MMC_SetCsServiceStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enCsCurrService = enCsCurrService;
}



VOS_UINT32  NAS_MMC_IsInValidCampPlmn( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo = VOS_NULL_PTR;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 判定当前驻留PLMN为无效值 */
    if ( (NAS_MML_INVALID_MCC == pstCampPlmnInfo->stLai.stPlmnId.ulMcc )
      && (NAS_MML_INVALID_MNC == pstCampPlmnInfo->stLai.stPlmnId.ulMnc ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID    NAS_MMC_SetPsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enPsCurrService)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enPsCurrService = enPsCurrService;
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enCsCurrService;
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetPsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enPsCurrService;
}



VOS_UINT32  NAS_MMC_GetNextAvailableTimerValue(VOS_VOID)
{

    VOS_UINT32                          ulTimerLen;

    //Fen = Ncell Priority?
    if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {
        /* NCELL全局变量中存的只是数字，将其转换成以毫秒为单位 */
        if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchFirstTimerLen();
        }
        else
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchSecondTimerLen();
        }
    }
    else
    {
        ulTimerLen  = NAS_MMC_GetNextSearchSleepTimerLen();
    }

    return ulTimerLen;
}







VOS_UINT32 NAS_MMC_GetNextSearchSleepTimerLen(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT32                                              ulTimerLen;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen);
    }
    else
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen);
    }

    return ulTimerLen;
}

/*************************************** L1 MAIN状态机上下文操作函数 *************************************************/

VOS_UINT32  NAS_MMC_GetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount;
}


VOS_VOID    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = 0;
}


VOS_VOID    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount++;
}


VOS_VOID   NAS_MMC_SetCurNormalAvailableTimerCount(
    VOS_UINT32                          ulCurTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = ulCurTimerCount;
}


VOS_UINT8  NAS_MMC_IsNeedStartNcellAvailableTimer(VOS_VOID)
{
    VOS_UINT8                           ucNcellSearchFlag;
    VOS_UINT8                           ucNcellSearchTimerLen;
    VOS_UINT32                          ulAvailableSearchTimeLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;



    ucNcellSearchFlag          = NAS_MMC_GetNcellSearchFlag();
    ucPsAttachAllowFlag        = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag        = NAS_MML_GetCsAttachAllowFlg();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段available时间间隔和ncell时间间隔 */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseOnePeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchFirstTimerLen();
    }
    else
    {
        /* 获取第二阶段available时间间隔和ncell时间间隔 */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchSecondTimerLen();
    }

    /*
       1、支持ncell快速搜网nv开启:
        -- modem1 gas上报存在t或l的邻区频点信息或邻区个数为0时也需启动ncell搜定时器
        -- 当前为PS attach not allow/cs attach not allow,防止国外情况开启该功能
        -- 如果普通available定时器为5s，NCELL available时长为10s，
          此时不需要启动NCELL available定时器。还是启动5s 普通available定时器，超时做
          普通 available搜索。
          如果要启动NCELL available定时器的话，必须满足普通available定时器时长内
          至少可启动两次NCELL available定时器，第一次NCELL available定时器超时做NCELL快速搜，
          第二次超时做普通Available搜
        -- 如果ncell时长为0，则启动普通available定时器
   */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (0 != ucNcellSearchTimerLen)
     && (ulAvailableSearchTimeLen >= (2*ucNcellSearchTimerLen))
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MMC_IsNeedStartHistoryTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT8                           ucHistoryNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();



    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段历史搜次数 */
        ucHistoryNum = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
    }
    else
    {
        /* 获取第二阶段历史搜次数 */
        ucHistoryNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
    }

    /* 次数为0，表示history特性关闭，不需要启动history搜定时器 */

    if (0 < ucHistoryNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_UINT8 NAS_MMC_IsNeedStartPrefBandTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT8                           ucPrefBandNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段PrefBand搜次数 */
        ucPrefBandNum = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
    }
    else
    {
        /* 获取第二阶段PrefBand搜次数 */
        ucPrefBandNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
    }

    /* 次数为0不需要启动PrefBand搜定时器 */
    if (0 < ucPrefBandNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8  NAS_MMC_GetAvailableTimerType_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAvailableTimerType_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType;
}


VOS_VOID  NAS_MMC_SetAvailableTimerType_OnPlmn(
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAvailableTimerType_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType = enAvailableTimerType;

}




VOS_UINT32  NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount;
}


VOS_VOID  NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount = 0;
}


VOS_VOID  NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount++;
}



VOS_UINT32  NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
}


VOS_VOID  NAS_MMC_SetCurHistorySearchTimerCount(
    VOS_UINT32                          ulCurHistorySearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = ulCurHistorySearchTimerCount;
}



VOS_VOID NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = 0;

    return;
}


VOS_VOID  NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount++;

    return;
}



VOS_VOID NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    /* Reset Normal Available Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount                 = 0;
    /* Reset NCell Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount      = 0;
    /* Reset History Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount    = 0;
    /* Reset PrefBand Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount   = 0;
    /* Reset OOS Phase Num */
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}

VOS_UINT32  NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
}


VOS_VOID  NAS_MMC_SetCurPrefBandSearchTimerCount(
    VOS_UINT32                          ulCurPrefBandSearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = ulCurPrefBandSearchTimerCount;
}



VOS_VOID NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = 0;

    return;
}


VOS_VOID  NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount++;

    return;
}


VOS_VOID NAS_MMC_GetOosCurInfo(
    NAS_MML_OOS_INFO_STRU              *pstOosInfo
)
{
    NAS_MMC_FSM_CTX_STRU               *pstL1MainFsm = VOS_NULL_PTR;

    /* 当前在NAS_MMC_FSM_L1_MAIN状态机 */
    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        pstOosInfo->ucCurOosPhaseNum          = NAS_MMC_GetCurrOosSearchPhaseNum();
        pstOosInfo->ulCurHistoryTimerCount    = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();
        pstOosInfo->ulCurPrefBandTimerCount   = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();
        pstOosInfo->ulCurFullBandTimerCount   = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
        return;
    }

    /* 当前不在NAS_MMC_FSM_L1_MAIN状态机，去栈中获取NAS_MMC_FSM_L1_MAIN的内容 */
    pstL1MainFsm = NAS_MMC_GetBottomFsmInFsmStack();

    if (VOS_NULL_PTR == pstL1MainFsm)
    {
        pstOosInfo->ucCurOosPhaseNum = NAS_MMC_OOS_PHASE_BUTT;
        return;
    }

    pstOosInfo->ucCurOosPhaseNum        = NAS_MMC_GetCurrOosSearchPhaseNum();
    pstOosInfo->ulCurHistoryTimerCount  = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
    pstOosInfo->ulCurPrefBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
    pstOosInfo->ulCurFullBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurTimerCount;

    return;
}



NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetCsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetPsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}


NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCLRegAdditionalAction_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetCLRegAdditionalAction_L1Main(
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enCLRegAdditionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = enCLRegAdditionalAction;
}



VOS_VOID NAS_MMC_ClearAllRegAdditionalAction_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = NAS_MMC_CL_ADDITIONAL_ACTION_BUTT;

}


VOS_VOID NAS_MMC_SetCsRegAttemptCount_L1Main(
    VOS_UINT32      ulCsCount
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = ulCsCount;
}


VOS_VOID NAS_MMC_SetPsRegAttemptCount_L1Main(
    VOS_UINT32      ulPsCount
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = ulPsCount;
}


VOS_UINT32 NAS_MMC_GetCsRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount;
}



VOS_UINT32 NAS_MMC_GetPsRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount;
}



VOS_VOID NAS_MMC_ClearAllRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = 0;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = 0;
}

/*************************************** 开机相关状态机上下文操作函数 *************************************************/



NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg;
}



NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32   NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitSimFilesFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg;
}


VOS_VOID    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg &= ~enMmStartCnfFlg;
}


VOS_VOID    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg = NAS_MMC_WAIT_MMGMM_START_CNF_NULL;
}




VOS_VOID    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg &= ~enSimFileCnfFlg;
}


VOS_VOID    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg = NAS_MML_READ_USIM_FILE_FLG_NULL;
}


VOS_VOID    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg |= enMmStartCnfFlg;
}


VOS_VOID    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg |= enSimFileCnfFlg;
}

/*************************************** 关机相关状态机上下文操作函数 *************************************************/

NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetMmPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMmPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg;
}


NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetAsPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAsPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg;
}


VOS_VOID    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg |= enMmPowerOffFlg;
}


VOS_VOID    NAS_MMC_SetAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg |= enAsPowerOffFlg;
}


VOS_VOID    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg &= ~enMmPowerOffFlg;
}


NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetMasterModeRat_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMasterModeRat_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat;
}


VOS_VOID NAS_MMC_SetMasterModeRat_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMasterModeRat_PowerOff:ENTERED");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat = enMasterModeRat;
}


NAS_MML_PLMN_RAT_PRIO_STRU *NAS_MMC_GetSlaveModeRatList_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSlaveModeRatList_PowerOff:ENTERED");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx.stSlaveModeList);
}


VOS_VOID NAS_MMC_BuildSlaveModeRatList_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeList = VOS_NULL_PTR; /* 发送关机请求的从模列表 */
    VOS_UINT8                                   ucRatIndex;
    VOS_UINT8                                   i;

    pstSlaveModeList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    ucRatIndex = 0;

    /* 先按平台接入技术能力把LWG都加到从模列表中 */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif


    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

    pstSlaveModeList->ucRatNum = ucRatIndex;

    /* 把主模从列表中删除 */
    for (i = 0; i < ucRatIndex; i++)
    {
        if (pstSlaveModeList->aucRatPrio[i] == enMasterModeRat)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstSlaveModeList->aucRatPrio[i]),
                        &(pstSlaveModeList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1) * sizeof(pstSlaveModeList->aucRatPrio[i]));
            /*lint +e961*/
            pstSlaveModeList->ucRatNum--;
            break;
        }
    }

    return;

}

VOS_VOID    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg &= ~enAsPowerOffFlg;
}



VOS_VOID    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg = NAS_MMC_MMGMM_POWER_OFF_NULL_FLG;
}


VOS_VOID    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff:ENTERED");

    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg = NAS_MMC_AS_POWER_OFF_NULL_FLG;

    return;
}

/*************************************** 异系统重选相关状态机上下文操作函数 *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg;
}


MMC_RESUME_ORIGEN_ENUM_UINT8 NAS_MMC_GetResumeOrign_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign;
}


VOS_VOID NAS_MMC_SetResumeOrign_InterSysCellResel(
    MMC_RESUME_ORIGEN_ENUM_UINT8        enResumeOrign
)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeOrign_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign = enResumeOrign;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}


VOS_VOID NAS_MMC_SetAbortFlag_InterSysCellResel(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT8 NAS_MMC_GetAbortFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg;
}


VOS_VOID NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(
    VOS_UINT8                           ucSndSuspendRelReqFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg = ucSndSuspendRelReqFlg;
}


VOS_UINT8 NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg;
}


/*************************************** 异系统OOS相关状态机上下文操作函数 *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*************************************** 异系统HO相关状态机上下文操作函数 *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}


VOS_VOID NAS_MMC_SetCsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg = ucSigExistFlg;
}


VOS_VOID NAS_MMC_SetPsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg = ucSigExistFlg;
}



VOS_UINT8  NAS_MMC_GetCsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg;
}


VOS_UINT8  NAS_MMC_GetPsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg;
}



/*************************************** 异系统CCO相关状态机上下文操作函数 *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}




NAS_MMC_FSM_L1_MAIN_CTX_STRU* NAS_MMC_GetL1MainCtx_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetL1MainCtx_L1Main,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx);
}


NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU* NAS_MMC_GetPlmnSelectionCtx_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionCtx_PlmnSelection,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx);
}




VOS_UINT32 NAS_MMC_GetAbortFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}


VOS_VOID NAS_MMC_SetAbortFlag_PlmnSelection(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT32 NAS_MMC_GetRelRequestFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg);
}


VOS_VOID NAS_MMC_SetRelRequestFlag_PlmnSelection(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnSelectionRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg = ucRelRequestFlg;
}




VOS_UINT8 NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag);
}


VOS_VOID NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(
    VOS_UINT8                           ucExistRplmnOrHplmnFlag
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag = ucExistRplmnOrHplmnFlag;
    return;
}



VOS_VOID NAS_MMC_SetInterSysSuspendRat_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat = enRat;

    return;
}


NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetInterSysSuspendRat_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat);
}



VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag);
}


VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(VOS_UINT8 ucWaitFlag)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}


VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(
    VOS_UINT8                           ucRegDomain
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}


VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(VOS_VOID)
{

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}


NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetCsRegCause_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause;
}


NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetPsRegCause_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause;
}


VOS_VOID NAS_MMC_SetCsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause = enCsCause;
}


VOS_VOID NAS_MMC_SetPsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause = enPsCause;
}


NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU * NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stPlmnSelectionListInfo);
}


VOS_UINT8 NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = ucSearchedRoamPlmnSortedFlag;
            return;
        }
    }
}


VOS_UINT8 NAS_MMC_GetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");

        return VOS_FALSE;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}



VOS_VOID NAS_MMC_SetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucHistorySearchedFlag
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag = ucHistorySearchedFlag;

            return;
        }
    }

    return;
}


VOS_UINT8 NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* 找到未进行HISTORY搜的RAT */
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_FALSE;
        }
    }

    /* 指定的接入技术列表都已完成了HISTORY搜索 */
    return VOS_TRUE;
}




VOS_UINT8 NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* 找到排过序的RAT,则返回TRUE */
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    /* 都没有排过序,则返回FALSE */
    return VOS_FALSE;
}




VOS_UINT8 NAS_MMC_GetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucAllBandSearch
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand = ucAllBandSearch;
            return;
        }
    }
}


VOS_VOID NAS_MMC_SetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType = enCoverType;
            return ;
        }
    }

    /* 若未找到更新的接入技术，则进行LOG打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:NOT FOUND THE enRAT");
}


NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return NAS_MMC_COVERAGE_TYPE_BUTT;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType;

        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}




VOS_UINT8 NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = ucSearchRplmnAndHplmnFlg;
            return;
        }
    }
}



VOS_UINT8 NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndEplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = ucSearchRplmnAndEplmnFlg;
            return;
        }
    }
}



VOS_UINT8 NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchDplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = ucSearchDplmnAndHplmnFlg;
            return;
        }
    }
}

/*lint -e438 -e830*/

VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;

    pstSearchRatInfo = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);

     /* 先进行初始化，将剩余的初始化为无效值 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg   = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucHistorySearchedFlag    = VOS_FALSE;
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;

    }

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        /* 设置LTE接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_LTE;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;

        i++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        /* 设置WCDMA接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;

        i++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        /* 设置GSM接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_GSM;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;

        i++;
    }

    return;
}

/*lint +e438 +e830*/



NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU* NAS_MMC_GetForbRoamLaInfo_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbRoamLaInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbRoamLaInfo);
}



NAS_MML_PLMN_ID_STRU* NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbGprsPlmn);
}


VOS_VOID NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn = *pstPlmnId;
}


NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn);
}



VOS_VOID NAS_MMC_SetCurrSearchingType_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enCurrSearchingType
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType = enCurrSearchingType;
}


NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MMC_GetCurrSearchingType_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType);
}



#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn = *pstPlmnId;
}


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn);
}
#endif


VOS_UINT32 NAS_MMC_GetAbortFlag_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag);
}


VOS_VOID NAS_MMC_SetAbortFlag_AnyCellSearch(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag = ucAbortFlg;
}


NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU* NAS_MMC_GetFsmCtxAddr_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_AnyCellSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx);
}


VOS_UINT8 NAS_MMC_GetRatNum_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatNum_AnyCellSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio.ucRatNum;
}


VOS_VOID NAS_MMC_DelMsUnsupportRat(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stNewPrioList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulMsRatIndex;

    VOS_UINT8                          ucNewRatNum;
    ucNewRatNum      = NAS_MMC_NUM_ZERO;
    pstMsPrioRatList = NAS_MML_GetMsPrioRatList();

    /*初始化中间结构变量*/
    stNewPrioList.ucRatNum = ucNewRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        stNewPrioList.aucRatPrio[ulRatIndex] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    for ( ulRatIndex = 0 ; ulRatIndex < pstRatPrioList->ucRatNum; ulRatIndex++ )
    {
        for ( ulMsRatIndex = 0 ; ulMsRatIndex < pstMsPrioRatList->ucRatNum; ulMsRatIndex++ )
        {
            if (pstRatPrioList->aucRatPrio[ulRatIndex] == pstMsPrioRatList->aucRatPrio[ulMsRatIndex])
            {
                stNewPrioList.aucRatPrio[ucNewRatNum]= pstRatPrioList->aucRatPrio[ulRatIndex];
                ucNewRatNum++;
                stNewPrioList.ucRatNum = ucNewRatNum;
            }
        }
    }

    pstRatPrioList->ucRatNum = stNewPrioList.ucRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        pstRatPrioList->aucRatPrio[ulRatIndex] = stNewPrioList.aucRatPrio[ulRatIndex];
    }

    return;
}


VOS_VOID NAS_MMC_SetRatPrioList_AnyCellSearch(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstAnycellPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulIsLteOnly;
    VOS_UINT8                           ucSupportCsServiceFlg;
    VOS_UINT8                           ucSimCsPsRegStatus;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulIsSupportLte;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;


    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    ucLowPrioAnycellSearchLteFlg        = NAS_MML_GetLowPrioAnycellSearchLteFlg();

    pstSimStatus          = NAS_MML_GetSimStatus();
    ucSimCsPsRegStatus    = VOS_TRUE;
    ulIsLteOnly           = NAS_MML_IsLteOnlyMode(pstRatPrioList);
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();
    ulIsSupportLte        = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                       pstRatPrioList);
    ucIndex               = 0;
    enMsMode              = NAS_MML_GetMsMode();
    PS_MEM_SET(&stAnycellSrchRatList, (VOS_CHAR)0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        ucSimCsPsRegStatus = VOS_FALSE;
    }
#endif

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatPrioList_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnycellPrioList = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio);

    pstAnycellPrioList->ucRatNum = pstRatPrioList->ucRatNum;

    for ( i = 0 ; i < pstRatPrioList->ucRatNum; i++ )
    {
        pstAnycellPrioList->aucRatPrio[i] = pstRatPrioList->aucRatPrio[i];
    }

    /* 45008协议描述: If the mobile station supports CS voice services,the MS shall avoid
       reselecting acceptable(but not suitable) E-UTRA cells regardless of the priorities
       in system information,支持cs语音业务，无卡或csps卡均无效导致的anycell搜，非L单模，不是ps only
       (软银有用例ps only被3、6、8拒绝需要待在L),将L的接入技术排在最后 */
#if (FEATURE_ON == FEATURE_LTE)

    if ( (((VOS_FALSE == NAS_MML_GetSimPresentStatus())
         || (VOS_FALSE == ucSimCsPsRegStatus)
         || (VOS_TRUE == ucLowPrioAnycellSearchLteFlg))
        && (VOS_TRUE == ucSupportCsServiceFlg)
        && (VOS_FALSE == ulIsLteOnly)
        && (VOS_TRUE == ulIsSupportLte)
        && (NAS_MML_MS_MODE_PS_ONLY != enMsMode)))
    {
        for (i = 0; i < pstRatPrioList->ucRatNum; i++)
        {
            if (pstRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
            {
                stAnycellSrchRatList.aucRatPrio[ucIndex] = pstRatPrioList->aucRatPrio[i];
                ucIndex++;
            }
        }

        stAnycellSrchRatList.aucRatPrio[ucIndex] = NAS_MML_NET_RAT_TYPE_LTE;
        ucIndex++;
        stAnycellSrchRatList.ucRatNum = ucIndex;
        PS_MEM_CPY(pstAnycellPrioList, &stAnycellSrchRatList, sizeof(stAnycellSrchRatList));
    }
#endif

    return;
}



NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSearchRat_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();
    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    for ( i = 0; i < ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* 获取LTE的能力状态 */
        enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();

        /* 接入技术为LTE且当前LTE状态为disable时，不选择LTE的接入技术 */
        if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
         && (NAS_MML_NET_RAT_TYPE_LTE   == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i]))
        {
            continue;
        }
#endif

        if ( VOS_FALSE == pstAnyCellSearchCtx->aucSearchedFlag[i])
        {
            /* 获取下个未搜索过的接入技术 */
            return pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i];
        }
    }

    /* 获取下个未搜索过的接入技术失败 */
    return NAS_MML_NET_RAT_TYPE_BUTT;
}



VOS_VOID NAS_MMC_SetSearchedFlag_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    /* 获取AnyCell搜网状态机的上下文地址 */
    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    for (i = 0; i < NAS_MMC_GetRatNum_AnyCellSearch(); i++)
    {
        if ( enSpecRat == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i])
        {
            /* 设置该接入技术为已搜过 */
            pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_TRUE;
        }
    }

    return;

}



VOS_VOID NAS_MMC_InitFsmCtx_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord  = VOS_NULL_PTR;

    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSyscfgSettingRecord              = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);

    /* SYSCFG状态机上下文中搜网的初始化:默认不需要搜网 */
    NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_FALSE);

    /* SYSCFG状态机上下文中设置接入层优先级顺序信息的初始化:
       搜网索引初始化为0,每设置SYSCFG后，该索引自增1，表示要设置SYSCFG的接入模式 */
    pstSyscfgSettingRecord->ucSetCurrSyscfgIndex = 0;

    /* 设置需要下发SYSCFG的总个数 */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = 0;

    /* 初始设置下发SYSCFG请求的顺序为LUG，如果平台不支持某个接入技术，不给该接入技术发送请求 */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_LTE;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_GSM;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_BUTT;
#else
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
#endif

    NAS_MMC_SetPrePrioRatList_SysCfg(&stPrePrioRatList);
    return ;
}



NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSysCfgSettingRecord_SysCfg,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.stSyscfgSettingRecord);
}


VOS_VOID NAS_MMC_SetPrePrioRatList_SysCfg(
    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrePrioRatList
)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList
                   = *pstPrePrioRatList;
    return;
}


NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetPrePrioRatList_SysCfg(VOS_VOID)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList);
}



VOS_VOID NAS_MMC_AddSysCfgIndex_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSysCfgIndex_SysCfg,ERROR:FsmId Error");
    }

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSysCfgRecord   = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 更新INDEX索引,指向下一个要进行SYSCFG设置的接入技术 */
    pstSysCfgRecord->ucSetCurrSyscfgIndex ++;

    /* 返回 */
    return ;
}




NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSettingRat_SysCfg(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *pucSyscfgRatPrio    = VOS_NULL_PTR;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     ucNextSyscfgRat;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstSysCfgRecord      = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pucSyscfgRatPrio     = pstSysCfgRecord->aucSyscfgRatPrio;

    /* 如果索引以到达设置的总个数，返回接入技术为无效值，表示SYSCFG设置结束 */
    if ( pstSysCfgRecord->ucSetCurrSyscfgIndex >= pstSysCfgRecord->ucTotalSyscfgNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* 取得数组中索引所对应的接入技术 */
    ucNextSyscfgRat                     = pucSyscfgRatPrio[pstSysCfgRecord->ucSetCurrSyscfgIndex];

    /* 返回需要SYSCFG设置的接入技术 */
    return ucNextSyscfgRat;
}


VOS_UINT32  NAS_MMC_GetPlmnSearchFlag_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    return (pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag);
}


VOS_VOID NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_UINT32 ulNeedSearchPlmnFlag)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag = ulNeedSearchPlmnFlag;
    return;
}



VOS_VOID NAS_MMC_SetSysCfgSendingOrder_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg
)
{
    VOS_UINT32                          i;
    /* 保存新增的接入技术列表 */
    NAS_MML_PLMN_RAT_PRIO_STRU          stTempRatList;
    /* 保存SYSCFG上报的顺序 */
    NAS_MML_PLMN_RAT_PRIO_STRU          stSyscfgSendingOrder;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSysCfgSendingOrder_SysCfg,ERROR:FsmId Error");
    }

    /* 取得当前 SYSCFG状态机上下文中的记录设置接入层优先级顺序信息 */
    pstSyscfgSettingRecord  = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 初始化 */
    PS_MEM_SET(&stSyscfgSendingOrder, 0x00, sizeof(stSyscfgSendingOrder));
    stSyscfgSendingOrder.ucRatNum = pstSyscfgSettingRecord->ucTotalSyscfgNum;
    PS_MEM_CPY( stSyscfgSendingOrder.aucRatPrio,
                pstSyscfgSettingRecord->aucSyscfgRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    /* 1. 找出新增的接入技术，放入临时的列表中 */
    NAS_MML_GetNewRatFromRatList( NAS_MML_GetMsPrioRatList(),
                                  &(pstSysCfgMsg->stRatPrioList),
                                  &stTempRatList );

    /* 2. 将当前主模优先级设置到最高 */
    NAS_MML_SortSpecRatPrioHighest( NAS_MML_GetCurrNetRatType(),
                                    &stSyscfgSendingOrder );

    /* 3. 将新增的接入技术排序到接入技术列表表首 */
    for ( i = stTempRatList.ucRatNum; i > 0 ; i-- )
    {
        NAS_MML_SortSpecRatPrioHighest( stTempRatList.aucRatPrio[i-1],
                                        &stSyscfgSendingOrder );
    }

    /* 将SYSCFG上报顺序存入全局变量中 */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = stSyscfgSendingOrder.ucRatNum;
    PS_MEM_CPY( pstSyscfgSettingRecord->aucSyscfgRatPrio,
                stSyscfgSendingOrder.aucRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    return;
}


VOS_UINT8 NAS_MMC_GetRelRequestFlag_SysCfg(VOS_VOID)
{
    /* 如果当前状态机不是 SysCfg, 异常打印 */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_SysCfg,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg);
}


VOS_VOID NAS_MMC_SetRelRequestFlag_SysCfg(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是 SysCfg, 异常打印  */
    if (NAS_MMC_FSM_SYSCFG !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_SysCfg,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg = ucRelRequestFlg;
}


VOS_UINT32 NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg          = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId           = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg,ERROR:FsmId Error");
    }

    pstRoamCfg      = NAS_MML_GetRoamCfg();

    /* 取得当前驻留的PLMN ID */
    pstPlmnId       = NAS_MML_GetCurrCampPlmnId();

    /* 与HPLMN相同，直接返回允许 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /* 漫游特性开关关闭，直接返回允许 */
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg)
    {
        return VOS_TRUE;
    }

    /* 允许漫游时直接返回允许 */
    if (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
    {
        return VOS_TRUE;
    }


    /* 判断当前网络是否在允许国内漫游列表中 */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );

    /* 若SYSCFG设置准许进行国内漫游，且当前网络在允许国内漫游列表中，返回准许漫游 */
    if ( (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability)
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* 若SYSCFG设置不准许进行国内漫游，且当前网络在漫游不支持时可以注册网络中，返回准许漫游 */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNotRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
        || (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* 否则返回不允许漫游 */
    return VOS_FALSE;
}

/* LIST搜网状态机上下文操作函数 */


VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* 构造一份临时接入技术列表, 便于调整 */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前接入技术存在,当前接入技术排在最前面 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* 初始化接入技术优先级列表以及搜索标记 */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;
    }
}



NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *NAS_MMC_GetSearchCtrlInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRatInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnListCtrlInfo[0]);
}



VOS_UINT32  NAS_MMC_GetNextSearchingRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;

    for ( i = 0; i < ucRatNum; i++)
    {
        if ( VOS_FALSE == pstSearchRatInfo[i].ucSearchedFlag)
        {
            /* 获取下个未搜索过的接入技术 */
            *penRat  = pstSearchRatInfo[i].enRat;
            return VOS_TRUE;
        }
    }

    /* 获取下个未搜索过的接入技术失败 */
    return VOS_FALSE;
}



VOS_VOID NAS_MMC_GetOrigenSearchRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetOrigenSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    *penRat = pstSearchRatInfo[0].enRat;
}



VOS_VOID NAS_MMC_SetSearchedFlag_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                              i;
    VOS_UINT8                               ucRatNum;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU     *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU   *pstListInfo      = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_PlmnList,ERROR:FsmId Error");
       return ;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;
    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i = 0; i < ucRatNum; i++)
    {
       if ( enSpecRat == pstSearchRatInfo[i].enRat )
       {
           pstSearchRatInfo[i].ucSearchedFlag = VOS_TRUE;

           /* 更新搜索到的网络列表中所带的接入技术，便于后续根据接入技术对列表进行更新 */
           pstListInfo[i].enRatType           = enSpecRat;
           break;
       }
    }

    return;
}



VOS_UINT8 NAS_MMC_GetAbortFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg;
}



VOS_VOID NAS_MMC_SetAbortFlag_PlmnList(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg = ucAbortFlg;
}



VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg;
}



VOS_VOID NAS_MMC_SetNotifyMsccFlag_PlmnList(
    VOS_UINT8                           ucNotifyFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg= ucNotifyFlg;
}


VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag;
}


VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucWaitFlag
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}


VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(
    VOS_UINT8                           ucRegRslt
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag &= ~ucRegRslt;
}


VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}



NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnList(VOS_VOID)
{

    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnList(VOS_VOID)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction;
}


VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}



NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU *NAS_MMC_GetRegRsltInfo_PlmnList(VOS_VOID)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo);
}



VOS_VOID NAS_MMC_InitSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId() )
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i= 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* 高优先级列表 */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* 低优先级列表 */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}




NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnSearchInfo[0]);
}

#if (FEATURE_ON == FEATURE_CSG)


VOS_VOID NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印*/
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* 初始化CSG搜网结果列表 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    PS_MEM_SET(pstCsgPlmnIdList, 0, sizeof(NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU));

    for ( i= 0; i < RRC_NAS_MAX_PLMN_CSG_ID_NUM; i++ )
    {
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId                      = NAS_MML_INVALID_CSG_ID_VALUE;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat          = RRC_NAS_RAT_TYPE_BUTT;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    }

    return;
}



NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stCsgListSearchedPlmnInfoList);
}


VOS_UINT32 NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(
    NAS_MML_PLMN_ID_STRU                          *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU          *pstSearchedPlmnList
)
{
    /* 检查重复，只要高低质量列表中有一个已经存在此PLMN，则返回已经在表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulHighPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astHighPlmnList))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulLowPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astLowPlmnList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrio = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* 实现思路很简单，在状态机上下文中保存的CSG ID搜索结果列表中，取出每个PLMN ID，保存到状态机上下文原
    来的那个高优先级搜网结果列表中，高质量的更新到高质量列表中，低质量的更新到低质量列表中，更新时需检查
    重复情况，如果表中已经有了此PLMN，则不再向里加入 */

    /* 局部变量初始化 */
    ulIndex         = 0;
    pstRatPrio      = NAS_MML_GetMsPrioRatList();
    ucRatNum        = pstRatPrio->ucRatNum;
    stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    pstRatPrio      = NAS_MML_GetMsPrioRatList();

    /* 保存高质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < ucRatNum; i++)
    {
        for (j = 0; j < NAS_MML_MIN(pstCsgPlmnList->ulHighPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* 如果判断的PLMN与当前循环的第i个接入技术相同，则进一步考虑是否加入当前接入技术的高优先级列表 */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* 检查重复，如果表中没有此PLMN，则添加，否则不添加 */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulHighPlmnNum;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].ulHighPlmnNum ++;

                    /* 保证数组不越界 */
                    if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                    {
                        /* 数组越界，跳出外层循环 */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* 保存低质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < ucRatNum; i++)
    {
        /* 除去高质量的PLMN，剩下的都是低质量的PLMN，所以起始位置是从最后1个高质量PLMN的下1个开始 */
        for (j = pstCsgPlmnList->ulHighPlmnNum; j < NAS_MML_MIN(pstCsgPlmnList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* 如果判断的PLMN与当前循环的第i个接入技术相同，则进一步考虑是否加入当前接入技术的低优先级列表 */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* 检查重复，如果表中没有此PLMN，则添加，否则不添加 */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulLowPlmnNum;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].astLowPlmnList[ulIndex].lRscp = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].lRscp;
                    pstListInfo[i].ulLowPlmnNum ++;

                    /* 保证数组不越界 */
                    if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                    {
                        /* 数组越界，跳出外层循环 */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* 根据高低质量个数更新覆盖类型 */
    for (i = 0; i < ucRatNum; i++)
    {
        pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;

        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;
        }

        if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;
        }
    }

    return;

}


#endif



VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstRrcList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    ucRatNum        = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* 保存高质量列表到上下文相应接入技术的列表 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulHighPlmnNum; j++ )
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[j].ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulHighPlmnNum;
                pstListInfo[i].astHighPlmnList[ulIndex].ulMcc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMcc;

                pstListInfo[i].astHighPlmnList[ulIndex].ulMnc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMnc;

                pstListInfo[i].ulHighPlmnNum ++;

                /* 保证数组不越界 */
                if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                {
                    /* 数组越界，跳出外层循环 */
                    i = ucRatNum;
                    break;
                }
            }

        }
    }

    /* 保存低质量列表到上下文相应接入技术的列表 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulLowPlmnNum; j++ )
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[j].PlmnId.ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulLowPlmnNum;
                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMcc;

                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMnc;

                pstListInfo[i].astLowPlmnList[ulIndex].lRscp
                       = pstRrcList->aLowPlmnList[j].lRscp;

                pstListInfo[i].ulLowPlmnNum ++;

                /* 保证数组不越界 */
                if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                {
                    /* 数组越界，跳出外层循环 */
                    i = ucRatNum;
                    break;
                }
            }
        }
    }

    /* 根据高低质量个数更新覆盖类型 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
        }
        else if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
        }
        else
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT8 NAS_MMC_GetPreLteDisableFlg_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg;
}



VOS_VOID NAS_MMC_SetPreLteDisableFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg = ucPreLteDisableFlg;
    return;

}
#endif



VOS_UINT8 NAS_MMC_GetAnyCellSrchFlg_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg;
}



VOS_VOID NAS_MMC_SetAnyCellSrchFlg_PlmnList(
    VOS_UINT8                           ucAnyCellSrchFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg = ucAnyCellSrchFlg;
    return;
}


VOS_VOID NAS_MMC_InitHighPrioPlmnSearchCtx(NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU *pstHighPrioPlmnSearchCtrl)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstHighPrioPlmnSearchCtrl->ucFirstStartHPlmnTimerFlg                       = VOS_TRUE;
    pstHighPrioPlmnSearchCtrl->enPlmnSelectionListType                         = NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST;
    pstHighPrioPlmnSearchCtrl->ucTdHighRatSearchCount                          = 0;
    pstHighPrioPlmnSearchCtrl->aucReserve[0]                                   = 0;

    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.usSearchPlmnNum = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[0]   = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[1]   = 0;

    for (i = 0; i < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST; i++)
    {
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].enPlmnType     = NAS_MMC_PLMN_TYPE_BUTT;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].ucRatNum       = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[0]  = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[1]  = 0;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality   = NAS_MMC_NET_QUALITY_BUTT;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].ucReserve   = 0;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *NAS_MMC_GetHighPrioPlmnList(VOS_VOID)
{

    return &(g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.stHighPrioPlmnSearchListInfo);
}


NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionListType(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType;
}


VOS_VOID NAS_MMC_SetPlmnSelectionListType(
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enListType
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType = enListType;

    return;
}


VOS_UINT8 NAS_MMC_GetTdHighRatSearchCount(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount;
}


VOS_VOID NAS_MMC_AddTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount++;

    return;
}


VOS_VOID NAS_MMC_InitTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount = 0;

    return;
}


MSCC_MMC_NET_SCAN_REQ_STRU *NAS_MMC_GetNetScanReq(VOS_VOID)
{
    return &(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq);
}


VOS_VOID NAS_MMC_SetNetScanReq(
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    PS_MEM_CPY(&(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq),
                pstNetScanReq,
                sizeof(MSCC_MMC_NET_SCAN_REQ_STRU));

    return;
}





RRMM_RAT_PRIO_ENUM_UINT8 NAS_MMC_GetSpecRatPrio(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* 查找对应接入技术是否在支持列表中 */
    for ( i = 0; i < pstRatList->ucRatNum; i++ )
    {
        if ( (pstRatList->aucRatPrio[i] == enRat)
          && (enRat < NAS_MML_NET_RAT_TYPE_BUTT) )
        {
            break;
        }
    }

    /* 查找成功,返回对应的接入技术优先级 */
    if ( i < pstRatList->ucRatNum )
    {
        /*接入技术的优先级，从高到低排列 */
        return (VOS_UINT8)(RRMM_RAT_PRIO_HIGH - i);
    }

    /* 不在支持列表中时，返回优先级为NULL*/
    else
    {
        return RRMM_RAT_PRIO_NULL;
    }

}





VOS_UINT32 NAS_MMC_GetEHPlmn(
    RRC_PLMN_ID_STRU                   *pstEHPlmn,
    VOS_UINT8                          *pucEHPlmnNum
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHplmn = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSimFlg;

    /* 获取当前的SIM卡状态信息 */
    pstSimStatus = NAS_MML_GetSimStatus();
    ucSimFlg    = pstSimStatus->ucSimPresentStatus;

    if ((VOS_NULL_PTR == pstEHPlmn) || (VOS_NULL_PTR == pucEHPlmnNum))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, input para is null.");
        return VOS_ERR;
    }

    if (VOS_FALSE == ucSimFlg)
    {

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, sim is absent or locked");
        return VOS_ERR;
    }

    pstSimEHplmn = NAS_MML_GetSimEhplmnList();

    /* 获得EHPLMN的个数 */
    *pucEHPlmnNum  = pstSimEHplmn->ucEhPlmnNum;

    /* 获取EHPLMN */
    for (i = 0; i < (*pucEHPlmnNum); i++)
    {
        pstEHPlmn[i].ulMcc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmn[i].ulMnc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMnc;
    }

    return VOS_OK;
}


VOS_VOID NAS_MMC_UpdateGURegRlstRPlmnIdInNV(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN标识 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    VOS_UINT32                          ulGRplmnChangeFlag;
    VOS_UINT32                          ulWRplmnChangeFlag;
    VOS_UINT32                          ulRatChangeFlag;

    ulGRplmnChangeFlag = VOS_FALSE;
    ulWRplmnChangeFlag = VOS_FALSE;
    ulRatChangeFlag    = VOS_FALSE;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 获取当前的接入技术 */
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* 用于最后一次注册成功的PLMN,没有Rplmn时，返回失败 */
    if (VOS_FALSE == NAS_MML_GetRPlmn(enCurrRat, &stPlmnId))
    {
        return;
    }

    /* 更新全局变量中的LastRPLMN的接入技术 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        ulRatChangeFlag = VOS_TRUE;
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }


    /* 更新全局变量中的RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
        ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stWRplmnInNV);
        /* 不支持双RPLMN，则W和G的RPLMN都更新 */
        pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;

    }
    else
    {
        /* 支持双RPLMN, 则只更新对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
            pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;

        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                                 &pstRplmnCfgInfo->stWRplmnInNV);
            pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE ==ulRatChangeFlag)
     || (VOS_TRUE == ulWRplmnChangeFlag)
     || (VOS_TRUE == ulGRplmnChangeFlag))
    {
        NAS_MMC_WriteRplmnWithRatNvim();
    }

    return;

}

VOS_VOID NAS_MMC_SaveUserReselPlmnInfo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList    = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        /* 在正常服务状态下，保存当前驻留的网络ID和对应的RAT */
        NAS_MMC_SetUserReselPlmnId( NAS_MML_GetCurrCampPlmnId(),
                                    NAS_MML_GetCurrNetRatType() );
    }
    else
    {
        /* 原来是自动模式才需要保存。
           原来是手动搜网模式，在限制服务状态，说明旧的PLMN信息已经保存,此时不需
           要再保存，避免把原来的PLMN ID信息清除 */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType    = NAS_MML_GetCurrNetRatType();

            /* 获取MML中保存的当前MS支持的接入模式和接入优先级 */
            pstPlmnRatList = NAS_MML_GetMsPrioRatList();

            /* 获取用户设置的优先级RAT */
            if (pstPlmnRatList->ucRatNum != 0)
            {
                enRatType = pstPlmnRatList->aucRatPrio[0];
            }

            /* 在限制服务下，保存HOME PLMN，和用户设置的优先级RAT */
            NAS_MMC_SetUserReselPlmnId(&(NAS_MML_GetSimEhplmnList()->astEhPlmnInfo[0].stPlmnId),
                                       enRatType);
        }
    }
}


VOS_VOID  NAS_MMC_SetPlmnRegRejInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    NAS_MML_LAI_STRU                   *pstCurrLai;
    VOS_UINT32                          i;
    VOS_UINT8                           ucCurrCampRac;

    if (VOS_NULL_PTR == pstPlmnRegInfo)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnRegRejInfo:WARNING:pstPlmnRegInfo IS NULL POINTER");
        return;
    }

    /* 获取当前的接入技术 */
    enCurrRat     = NAS_MML_GetCurrNetRatType();
    pstCurrLai    = NAS_MML_GetCurrCampLai();
    ucCurrCampRac = NAS_MML_GetCurrCampRac();

    pstPlmnRegInfo->stPlmnId = *pstPlmnId;

    for (i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPlmnRegInfo->aucLac[i] = pstCurrLai->aucLac[i];
    }
    pstPlmnRegInfo->ucRac = ucCurrCampRac;

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: PLMN MCC, MNC, Domain and Reg Fail Cause",
                    pstPlmnRegInfo->stPlmnId.ulMcc,
                    pstPlmnRegInfo->stPlmnId.ulMnc,
                    enDomain,
                    enCause);

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: RAT, LAI and RAC ",
                    enCurrRat,
                    pstPlmnRegInfo->aucLac[0],
                    pstPlmnRegInfo->aucLac[1],
                    pstPlmnRegInfo->ucRac);

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enWCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enWPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
#if   (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_EPS == enDomain)
        {
            pstPlmnRegInfo->enLPsRegStatus  = enCause;
            return;
        }
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enLCsRegStatus = enCause;
            return;
        }
    }
#endif
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_FillPlmnRegInfo: NORMAL: enCurrRat is wrong!");
    }


}



VOS_VOID NAS_MMC_UpdatePlmnRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* 获取注册原因列表的指针 */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* 判断当前网络是否已在注册列表中   */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);


    /* 当前网络在注册被拒列表中 */
    if ( ulIndex < NAS_MML_MIN(pstPlmnRegRejInfo->ucPlmnRegInfoNum ,(NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* 该网络已在列表中存在,更新注册原因值 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause, (pstPlmnRegList + ulIndex));
        /*lint -e961*/
        /* 判断网络是否存在注册失败的域信息，若未曾有注册失败的域信息，则将此网络从被拒信息表里删除 */
        if ( VOS_TRUE == NAS_MMC_IsPlmnRegInfoAllSucc( pstPlmnRegList + ulIndex ) )
        {
            (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList + ulIndex, (pstPlmnRegList + ulIndex + 1),
                (pstPlmnRegRejInfo->ucPlmnRegInfoNum - ulIndex - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

            /* 更新列表中的个数 */
            pstPlmnRegRejInfo->ucPlmnRegInfoNum--;
        }
        /*lint +e961*/
        return;
    }

    /* 该网络不在注册表里且注册原因值为NULL,则不保存 */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCause )
    {
        return;
    }

    /* 当前网络不在保存的列表中或列表为空 */
    if (pstPlmnRegRejInfo->ucPlmnRegInfoNum < NAS_MMC_MAX_REG_PLMN_INFO_NUM)
    {
        /* 列表未满，追加注册原因到列表中 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
                     (pstPlmnRegList + pstPlmnRegRejInfo->ucPlmnRegInfoNum));

        /* 更新列表中的个数 */
        pstPlmnRegRejInfo->ucPlmnRegInfoNum++;
    }
    else
    {
        /* 列表已满, 最早的记录移动出数组 */
        (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList, (pstPlmnRegList + 1),
                   (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

        /* 保存注册原因到列表中 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
              (pstPlmnRegList + (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)));
    }

    return;

}


VOS_VOID NAS_MMC_ConvertHplmnRegStatusToDomainInfo(
    VOS_UINT8                          *pucDomainInfo,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    enNetRatType   = NAS_MML_GetCurrNetRatType();
    *pucDomainInfo = NAS_MMC_REG_DOMAIN_NONE;

    switch (enNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_EPS;
                return;
            }
            return;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertHplmnRegStatusToDomainInfo:invalid rat type");
            return;
    }
}



VOS_VOID NAS_MMC_GetHplmnRejDomainInfo(
    VOS_UINT8                          *pucRejDomainRlst
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 获取当前驻留的PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* 用于获取HPLMN注册被拒的列表 */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* 当前驻留PLMN不在HPLMN列表中，则直接返回 */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;

        return;
    }

    /* 判断当前网络是否在HPLMN注册被拒列表中 */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);


    if (ulIndex < NAS_MML_MIN(pstRegRejCtx->ucPlmnRegInfoNum, (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* 该网络已在HPLMN注册被拒列表中，更新其被拒域 */
        NAS_MMC_ConvertHplmnRegStatusToDomainInfo(pucRejDomainRlst,
                                             &pstRegRejCtx->astPlmnRegInfoList[ulIndex]);

    }
    else
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}


VOS_VOID NAS_MMC_ClearHplmnRejDomainInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    VOS_UINT8                           ucAcceptCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    VOS_UINT8                           ucIdx;

    /* 获取HPLMN注册被拒的列表 */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* 在HPLMN注册被拒列表中未查找到当前驻留PLMN，则直接返回 */
    ucIdx = (VOS_UINT8)NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (ucIdx >= pstRegRejCtx->ucPlmnRegInfoNum)
    {
        return;
    }

    /* 清除对应域的被拒信息 */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                      ucAcceptCnDomain, NAS_MML_REG_FAIL_CAUSE_NULL);

}


VOS_UINT32 NAS_MMC_GetAbortEventType_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType);
}


VOS_VOID NAS_MMC_SetAbortEventType_BgPlmnSearch(
    VOS_UINT32                          ulAbortEventType
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType = ulAbortEventType;
}




NAS_MMC_ABORT_FSM_TYPE_UINT8 NAS_MMC_GetAbortType_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType);
}


VOS_VOID NAS_MMC_SetAbortType_BgPlmnSearch(
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType = enAbortType;
}


VOS_UINT8 NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo;
}


VOS_VOID NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(
    VOS_UINT8                           ucNeedSndSysInfo
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo = ucNeedSndSysInfo;
}



VOS_UINT8 NAS_MMC_GetRelRequestFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg);
}


VOS_VOID NAS_MMC_SetRelRequestFlag_BgPlmnSearch(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg = ucRelRequestFlg;
}


VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag);
}


VOS_VOID NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucWaitFlag
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}


VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucRegDomain
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}


VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction);
}


VOS_VOID NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction);
}


VOS_VOID NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}


NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn);
}


VOS_VOID NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.enRat    = enRat;
}


NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetPreCampPlmn_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn);
}


VOS_VOID NAS_MMC_SetPreCampPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}





VOS_VOID NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}



NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo);
}


VOS_VOID NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");

        return;
    }

    /* 第一个EQUPLMN(即RPLMN)与当前驻留网络相同, 则保存当前驻留网络的EQUPLMN到状态机上下文 */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &(pstEquPlmnInfo->astEquPlmnAddr[0])))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo = *pstEquPlmnInfo;
    }
    else
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.ucEquPlmnNum = 0x1;
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.astEquPlmnAddr[0] = *pstCurrCampPlmnId;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_TRUE;
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_FALSE;
    return;
}


VOS_UINT32 NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg;
}

VOS_VOID NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_UINT8 ucNeedEnableLteFlg)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg = ucNeedEnableLteFlg;
    return;
}


VOS_UINT32 NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg;
}


VOS_UINT32 NAS_MML_IsLteSearched_AreaLost(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                                              i;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if ((NAS_MSCC_PIF_NET_RAT_TYPE_LTE == pstSearchedPlmnListInfo[i].enRatType)
        && ((VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucPrefBandSearchedFlg)
         || (VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucSpecSearchedFlg)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


VOS_VOID NAS_MMC_SetFirstStartHPlmnTimerFlg(
    VOS_UINT8                           ucFirstStartHPlmnTimer
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg = ucFirstStartHPlmnTimer;
}


VOS_UINT8 NAS_MMC_GetFirstStartHPlmnTimerFlg(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg;
}


VOS_UINT32  NAS_MMC_GetHplmnTimerLen( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulHplmnTimerLen;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (VOS_TRUE == NAS_MMC_GetFirstStartHPlmnTimerFlg())
    {
        /* 首次启动，从NV：en_NV_Item_HPlmnFirstTimer中读取，默认为2分钟 */
        ulHplmnTimerLen = pstBgSearchCfg->ulFirstStartHplmnTimerLen;
    }
    else
    {
        ulHplmnTimerLen = NAS_MML_GetSimHplmnTimerLen();
        
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "GetHplmnTimerLen:NAS_MML_GetSimHplmnTimerLen is",ulHplmnTimerLen);
    }

    /* H3G需求: VPLMN下非首次搜HPLMN周期可在NV中配置 */
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        if (VOS_TRUE != NAS_MMC_GetFirstStartHPlmnTimerFlg())
        {
            /* 非首次启动，从NV: en_NV_Item_SearchHplmnTtimerValue中获取，无论USIM文件中
               的取值或NV: en_NV_Item_Default_Max_Hplmn_Srch_Peri中取的值是否生效 */
            ulHplmnTimerLen = pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen;

            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetHplmnTimerLen:nvim ulNonFirstHplmnTimerLen is",ulHplmnTimerLen);
        }
    }

    return ulHplmnTimerLen;
}






VOS_UINT32  NAS_MMC_GetCacheNum( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}



VOS_VOID  NAS_MMC_SetFsmStackPopFlg(
    VOS_UINT16                          ucStachPopFlg
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStachPopFlg;
}


VOS_UINT16  NAS_MMC_GetFsmStackPopFlg( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}



VOS_UINT32 NAS_MMC_IsFsmEntryEventType(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_aulFsmEntryEventType) / sizeof(VOS_UINT32)) ; i++ )
    {
        if ( ulEventType == g_aulFsmEntryEventType[i] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32  NAS_MMC_GetBufferedPlmnSearchFlg( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg;
}


NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  NAS_MMC_GetBufferedPlmnSearchScene( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene;
}



VOS_VOID NAS_MMC_SetBufferedPlmnSearchInfo(
    VOS_UINT32                                              ulPlmnSearchFlg,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = ulPlmnSearchFlg;
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene = enPlmnSearchScene;
}



NAS_MMC_SRV_STA_CHNG_INFO_STRU* NAS_MMC_GetSrvStaChngInfo( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastSrvStaInfo;
}


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetLastCampedPlmnid( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.stPlmnId;
}



NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetLastCampedPlmnRat( VOS_VOID )
{
    return g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat;
}


VOS_VOID NAS_MMC_SetLastCampedPlmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat = enRat;
}


VOS_VOID NAS_MMC_SaveLastCampedPlmnWithRat(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_ID_STRU             *pstLastPlmnid;

    pstLastPlmnid = NAS_MMC_GetLastCampedPlmnid();

    pstLastPlmnid->ulMcc = ulMcc;
    pstLastPlmnid->ulMnc = ulMnc;

    NAS_MMC_SetLastCampedPlmnRat(enRat);

    return;
}





VOS_UINT32  NAS_MMC_IsFsmIdInFsmStack(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    for (i = 0; i < pstFsmStack->usStackDepth; i++)
    {
        if (enFsmId == pstFsmStack->astFsmStack[i].enFsmId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;


    pstSimStatus     = NAS_MML_GetSimStatus();
    enCsCurrService  = NAS_MMC_GetCsServiceStatus();
    enPsCurrService  = NAS_MMC_GetPsServiceStatus();

    /* 用户指定当前驻留Plmn,CS/PS同时都为正常服务时，不需要触发搜网 */
    if (( NAS_MMC_NORMAL_SERVICE == enCsCurrService)
     && ( NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* 用户指定当前驻留Plmn,CS正常服务,PS不允许注册或PS卡无效时，不需要触发搜网 */
    if ((( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enCsCurrService))
    {
        return VOS_FALSE;
    }

    /* 用户指定当前驻留Plmn,PS正常服务,CS不允许注册或CS卡无效时，不需要触发搜网 */
    if (( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* 其他情况下，需要发起搜网 */
    return VOS_TRUE;

}







VOS_UINT32 NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* 如果同时支持FDD和TDD，定时器时长为301s */
    if ( (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {
        return TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN;
    }

    /* 如果只支持FDD和TDD中的一个，定时器时长为150s */
    if (ulSupportFddFlg != ulSupportTddFlg)
    {
        return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;
    }
#endif

    return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;

}












VOS_VOID  NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(
    VOS_UINT8                           ucSrvTriggerPlmnSearchFlag
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag = ucSrvTriggerPlmnSearchFlag;
    return;
}


VOS_UINT8 NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag;
}


VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulHplmnTimerLen;
    VOS_UINT32                                              ulCount;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();
    ulCount                 = NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    if (ulCount < pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount)
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
    }
    else
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
    }

    return ulHplmnTimerLen;
}


VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerRetryLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
}



VOS_UINT32  NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount;
}


VOS_VOID    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount= 0;
}


VOS_VOID    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount++;
}




VOS_VOID NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo(VOS_VOID)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo     = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi              = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;
    VOS_UINT8                                               i,j;

    pucImsi = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHPlmn                   = NAS_MML_GetImsiHomePlmn(pucImsi);
    pstDPlmnNPlmnCfgInfo      = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstSimEhplmnInfo          = NAS_MML_GetSimEhplmnList();

    j = 0;
    pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = stHPlmn;
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

    for (i = 0; i < pstSimEhplmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId),
                                                              pstDPlmnNPlmnCfgInfo->ucEHplmnNum,
                                                              pstDPlmnNPlmnCfgInfo->astEHplmnList))
        {
            continue;
        }

        pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId;

        if (j >= NAS_MMC_MAX_CFG_HPLMN_NUM)
        {
            break;
        }
    }

    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

}


NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU* NAS_MMC_GetDPlmnNPlmnCfgInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx.stDplmnNplmnInfo);
}


NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU* NAS_MMC_GetDPlmnNPlmnCfgCtx( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx);
}


VOS_VOID  NAS_MMC_InitUserDPlmnNPlmnInfo(
    NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU                      *pstDPlmnNPlmnCfgCtx
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo;

    VOS_UINT32                                              i;

    if (VOS_TRUE != pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg)
    {
        pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg = VOS_FALSE;
    }

    pstDPlmnNPlmnCfgInfo                                    = &(pstDPlmnNPlmnCfgCtx->stDplmnNplmnInfo);
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum                       = 0;
    pstDPlmnNPlmnCfgInfo->usDplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usNplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum                  = 0;

    PS_MEM_SET(pstDPlmnNPlmnCfgInfo->aucVersionId, 0x00, NAS_MCC_INFO_VERSION_LEN*sizeof(VOS_UINT8));

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_DPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_NPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}



VOS_UINT8 NAS_MMC_GetRoamPlmnSelectionSortActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg);
}


VOS_VOID NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg = ucRoamPlmnSelectionSortFlg;
}



VOS_VOID NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(
    VOS_UINT8 ucSrchUOplmnPriorToDplmnFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg = ucSrchUOplmnPriorToDplmnFlg;
    return;
}


VOS_UINT8 NAS_MMC_GetSrchUOplmnPriorToDplmnFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg;
}



NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetGeoPlmn(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn);
}


VOS_VOID NAS_MMC_SetGeoPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn = *pstGeoPlmn;
    return;
}


NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU* NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg);
}



VOS_UINT8 NAS_MMC_GetNonOosSceneHistorySearchActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg.ucHistoryActiveFlg);
}



NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU* NAS_MMC_GetOosPlmnSearchStrategyInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo);
}


NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseOnePatternCfg);
}


NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseTwoPatternCfg);
}



VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByHistory( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurHistoryCount       = 0;
    VOS_UINT8                                               ucTotalHistoryCount     = 0;
    VOS_UINT8                                               ucTotalPrefBandCount    = 0;
    VOS_UINT8                                               ucTotalFullBandCount    = 0;

    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurHistoryCount                           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalHistoryCount     = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalHistoryCount     = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* 若不是最後一阶段且history为最大定时器则进入下一阶段 */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalPrefBandCount)
     &&(0 == ucTotalFullBandCount)
     &&((ulCurHistoryCount == ucTotalHistoryCount)))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByPrefBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurPrefBandCount;
    VOS_UINT8                                               ucTotalPrefBandCount = 0;
    VOS_UINT8                                               ucTotalFullBandCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurPrefBandCount                          = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalPrefBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
        /* 第二阶段 */
        ucTotalPrefBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* 若不是最後一阶段且Prefband为最大定时器则进入下一阶段 */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalFullBandCount)
     && (ulCurPrefBandCount == ucTotalPrefBandCount))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByFullBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurFullBandCount;
    VOS_UINT8                                               ucTotalFullBandCount;


    pstPhaseOneOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    ulCurFullBandCount          = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    /* 若Fullband到达设定执行次数且目前不是最後一阶段则进入下一阶段 */
    if ((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
      &&(ulCurFullBandCount == ucTotalFullBandCount))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;

}


NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetOosPhaseNum( VOS_VOID )
{

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum);

}


VOS_VOID NAS_MMC_ResetOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}


VOS_VOID  NAS_MMC_AddOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum++;
    return;
}


VOS_VOID NAS_MMC_SetCurrOosSearchPhaseNum(
    NAS_MMC_OOS_PHASE_ENUM_UINT8        enCurrPhaseNum
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = enCurrPhaseNum;
    return;
}


NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetCurrOosSearchPhaseNum( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum);
}


VOS_VOID NAS_MMC_InitOosSearchStrategyInfo(
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU                 *pstSearchTypeStrategyInfo
)
{
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usTotalTimerLen    = 0;

    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usTotalTimerLen    = 0;

    return;
}


VOS_UINT32 NAS_MMC_GetPhaseOnePeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseOnePeriodicSleepTimerLen;

    pstPhaseOneOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    ulPhaseOnePeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV 会回避, 变成 F=1, P=0, H=0
        */
    return ulPhaseOnePeriodicSleepTimerLen;
}


VOS_UINT32 NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseTwoPeriodicSleepTimerLen;

    pstPhaseTwoOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulPhaseTwoPeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV 会回避, 变成 F=1, P=0, H=0
        */
    return ulPhaseTwoPeriodicSleepTimerLen;
}




VOS_VOID NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosPlmnSearchFeatureSupportCfg
)
{
    PS_MEM_SET(pstNonOosPlmnSearchFeatureSupportCfg, 0,
               sizeof(NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU));

    /* 默认不激活history搜特性 */
    pstNonOosPlmnSearchFeatureSupportCfg->ucHistoryActiveFlg                        = VOS_FALSE;

    /* 默认不激活PrefBand搜特性 */
    pstNonOosPlmnSearchFeatureSupportCfg->ucPrefBandActiveFlg                       = VOS_FALSE;

    /* 默认area lost场景history之后进行spec搜 */
    pstNonOosPlmnSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene   = NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC;
    return;
}

#if (FEATURE_ON == FEATURE_CSG)

VOS_VOID NAS_MMC_InitCsgListSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgListSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* 构造一份临时接入技术列表, 便于调整 */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前接入技术存在,当前接入技术排在最前面 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* 初始化接入技术优先级列表以及搜索标记,目前只支持LTE CSG,gu的设置为true */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;

        if (NAS_MML_NET_RAT_TYPE_LTE != stTmpPrioRatList.aucRatPrio[i])
        {
            pstSearchRatInfo[i].ucSearchedFlag  = VOS_TRUE;
        }
    }
}
#endif



VOS_VOID NAS_MMC_InitGetGeoInfo(
    NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
)
{
    /* 初始化GEO PLMN */
    NAS_MMC_InitGeoPlmn();

    return;
}


VOS_VOID NAS_MMC_InitGeoPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU                              stGeoPlmn;

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    stGeoPlmn.enRat             = NAS_MML_NET_RAT_TYPE_BUTT;
    stGeoPlmn.stPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    stGeoPlmn.stPlmnId.ulMnc    = NAS_MML_INVALID_MNC;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}


NAS_MML_PLMN_ID_STRU *NAS_MMC_GetDisabledLtePlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId);
}


VOS_VOID NAS_MMC_SetDisabledLtePlmnId(
    NAS_MML_PLMN_ID_STRU              *pstPlmnId
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = pstPlmnId->ulMcc;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = pstPlmnId->ulMnc;
    return;
}


VOS_VOID NAS_MMC_ClearDisabledLtePlmnId(VOS_VOID)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = NAS_MML_INVALID_MCC;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = NAS_MML_INVALID_MNC;
    return;
}


VOS_UINT8 NAS_MMC_GetEnableLteTimerExpireFlag( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag);
}


VOS_VOID NAS_MMC_SetEnableLteTimerExpireFlag(
    VOS_UINT8                           ucEnableLteTimerExpireFlag
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag = ucEnableLteTimerExpireFlag;
    return;
}




NAS_MMC_REG_CONTROL_ENUM_UINT8 NAS_MMC_GetRegCtrl( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl);
}


VOS_VOID NAS_MMC_SetRegCtrl(
    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl) = enRegCtrl;
}


VOS_UINT8 NAS_MMC_GetAsAnyCampOn( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn);
}


VOS_VOID NAS_MMC_SetAsAnyCampOn(
    VOS_UINT8                          ucAsAnyCampOn
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn) = ucAsAnyCampOn;
}



VOS_VOID NAS_MMC_SaveRegReqNCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    /* 目前仅支持注册请求中携带LTE的NCell信息 */
    if (NAS_MML_NET_RAT_TYPE_LTE != pstCellInfo->ucRat)
    {
        return;
    }

    /* 保存NCELL信息 */
    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum       = 1;
    pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList[0]  = pstCellInfo->ulArfcn;

    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum        = NAS_MML_MIN(pstCellInfo->ucCellNum, NAS_MMC_LTE_CELL_MAX_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stLteNcellInfo.ausLteCellList, pstCellInfo->ausCellId,
               ((pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum) * sizeof(VOS_UINT16)));

    pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum = NAS_MML_MIN(pstCellInfo->ucPlmnNum, NAS_MML_MAX_EQUPLMN_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr, pstCellInfo->astPlmnId,
               ((pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum) * sizeof(NAS_MML_PLMN_ID_STRU)));

    return;
}


VOS_UINT32 NAS_MMC_GetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    /* 参数有效性判断 */
    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* 指针为空指针，返回错误 */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:NULL PTR ");
        return VOS_FALSE;
    }

    if (pstMmcPara->enMmaParaType >= EN_MMC_BEGIN_SET_MMC_PARA)
    {
        /* 类型参数错误,返回错误值 */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(&(pstMmcPara->u.stOPlmnInfo));
            break;

        case EN_MMC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        case EN_MMC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(&(pstMmcPara->u.stHPlmnInfo));
            break;


        /* PLMNSEL 和 UPLMN 只可能出现一个，故都存在 stUPlmnInfo 中 */
        case EN_MMC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        default:
            /* 打印出错信息,返回出错标志 */
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_SetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    VOS_UINT32                          ulI = 0;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmn  = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmn = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* 指针为空指针，返回错误 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:Set Para Point is NULL");
        return VOS_FALSE;
    }

    pstUserPlmn = NAS_MML_GetSimUserPlmnList();
    pstSelPlmn  = NAS_MML_GetSimSelPlmnList();

    if ((pstMmcPara->enMmaParaType < EN_MMC_BEGIN_SET_MMC_PARA)
      || (pstMmcPara->enMmaParaType > EN_MMC_END_SET_MMC_PARA))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_SET_UPLMN_INFO:
             pstUserPlmn->ucUserPlmnNum      = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
             for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
             {
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
                 pstUserPlmn->astUserPlmnInfo[ulI].usSimRat       = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].usRaMode;
             }

             break;

        case  EN_MMC_SET_PLMNSEL_INFO:
            pstSelPlmn->ucSelPlmnNum    = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
            for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
            {
                pstSelPlmn->astPlmnId[ulI].ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                pstSelPlmn->astPlmnId[ulI].ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
            }

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;

    }
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_GetPlmnInfo(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
)
{
    VOS_UINT32                          ulLoop;
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccSelPlmnList = VOS_NULL_PTR;

    pstRptMsccSelPlmnList = (MMC_TAF_PLMN_LIST_INFO_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(MMC_TAF_PLMN_LIST_INFO_ST));
    if (VOS_NULL_PTR == pstRptMsccSelPlmnList)
    {
        return VOS_FALSE;
    }

    switch (enPrefPlmnParaType)
    {
        case NAS_MSCC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        /* PLMNSEL 和 UPLMN 只可能出现一个，故都存在 stUPlmnInfo 中 */
        case NAS_MSCC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        default:
            /* 打印出错信息,返回出错标志 */
            PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnInfo:WARNING:PARA TYPE WRONG IN DEFAULT ");
            return VOS_FALSE;
    }

    pstPlmnInfo->usPlmnNum = pstRptMsccSelPlmnList->usCurPlmnNum;
    for ( ulLoop = 0; ulLoop < pstRptMsccSelPlmnList->usCurPlmnNum ; ulLoop++ )
    {
        pstPlmnInfo->Plmn[ulLoop].ulMcc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMcc;
        pstPlmnInfo->Plmn[ulLoop].ulMnc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMnc;
        NAS_MMC_PlmnId2Bcd(&(pstPlmnInfo->Plmn[ulLoop]));
        pstPlmnInfo->ausPlmnRat[ulLoop] = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].usRaMode;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);

    return VOS_TRUE;
}


VOS_UINT16 NAS_MMC_GetSpecificPlmnTblSize(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                                              usCurPlmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRat = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnInfo  = VOS_NULL_PTR;

    usCurPlmnNum = 0;
    switch(enPrefPLMNType)
    {
        case NAS_MSCC_UPLMN_INFO:
            pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
            usCurPlmnNum    = pstUserPlmnList->ucUserPlmnNum;
            break;
        case NAS_MSCC_PLMNSEL_INFO:
            pstSelPlmnInfo  = NAS_MML_GetSimSelPlmnList();
            usCurPlmnNum    = pstSelPlmnInfo->ucSelPlmnNum;
            break;
        case NAS_MSCC_OPLMN_INFO:
            pstOperPlmnList = NAS_MML_GetSimOperPlmnList();
            usCurPlmnNum    = pstOperPlmnList->usOperPlmnNum;
            break;
        case NAS_MSCC_HPLMN_INFO:
            pstHplmnWithRat = NAS_MML_GetSimHplmnWithRatList();
            usCurPlmnNum    = pstHplmnWithRat->ucHPlmnWithRatNum;
            break;
        default:
            break;
    }

    return usCurPlmnNum;
}


VOS_VOID NAS_MMC_UpdatePlmnInfo(
    VOS_UINT16                          usEfId
)
{
    MMC_MMA_SHARE_PARA_ST              *pstMsccPara;
    VOS_UINT16                          usIndex;
    MMC_MODIFY_PLMN_INFO_STRU          *pstPrefPlmnCtx;

    pstMsccPara = (MMC_MMA_SHARE_PARA_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                            sizeof(MMC_MMA_SHARE_PARA_ST));

    if (VOS_NULL_PTR == pstMsccPara)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_UpdatePlmnInfo: Alloc memory fail.");
        return ;
    }

    if (USIMM_GSM_EFPLMNSEL_ID == usEfId ) /* EFPLMNsel */
    {
        pstMsccPara->enMmaParaType = EN_MMC_PLMNSEL_INFO;
    }
    else if ((USIMM_USIM_EFPLMNWACT_ID == usEfId) /* EFPLMNwAcT */
         || ((USIMM_GSM_EFPLMNWACT_ID  == usEfId)))
    {
        pstMsccPara->enMmaParaType = EN_MMC_UPLMN_INFO;
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->enMmaParaType = EN_MMC_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = EN_MMC_HPLMN_INFO;
    }

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();

    usIndex = pstPrefPlmnCtx->usIndex;

    if (usIndex >= NAS_MML_MAX_USERPLMN_NUM)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);
        return ;
    }

    (VOS_VOID)NAS_MMC_GetPrefPlmnPara(pstMsccPara);

    if ( (USIMM_GSM_EFPLMNSEL_ID   == usEfId ) /* EFPLMNsel */
      || (USIMM_USIM_EFPLMNWACT_ID == usEfId)
      || (USIMM_GSM_EFPLMNWACT_ID  == usEfId)) /* EFPLMNwAcT */
    {
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

        /* UPLMN需要进行更新 */
        NAS_MMC_SndMmcUpdateUplmnNotify();
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

    }
    else
    {
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;
    }


    if (EN_MMC_UPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_UPLMN_INFO;
    }
    else if (EN_MMC_PLMNSEL_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_PLMNSEL_INFO;
    }
    else if (EN_MMC_OPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = MMC_MMA_PARA_TYPE_BUTT;
    }

    (VOS_VOID)NAS_MMC_SetPrefPlmnPara(pstMsccPara);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);

    return;

}


VOS_UINT32 NAS_MMC_QryPrefPlmnId(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8       enPrefPLMNType,
    VOS_UINT32                              ulFromIndex,
    VOS_UINT32                              ulPlmnNum,
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU      *pstPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstOrgPlmnInfo;

    pstOrgPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOrgPlmnInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstOrgPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    /* 获取优先网络列表 */
    if (VOS_TRUE != NAS_MMC_GetPlmnInfo(enPrefPLMNType, pstOrgPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

        return VOS_FALSE;
    }

    pstPlmnInfo->ulPlmnNum = pstOrgPlmnInfo->usPlmnNum;

    for (i = 0; i < ulPlmnNum; i++ )
    {
        pstPlmnInfo->ausPlmnRat[i]                         = pstOrgPlmnInfo->ausPlmnRat[(i + ulFromIndex)];
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMcc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMcc;
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMnc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMnc;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

    return VOS_TRUE;

}



VOS_VOID NAS_MMC_InitPrefPlmnCtx(
    MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
)
{
    pstPreflmnInfo->stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    pstPreflmnInfo->stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstPreflmnInfo->usIndex         = 0;
    pstPreflmnInfo->PlmnRat         = NAS_MMC_RAT_BUTT;

    return;
}


MMC_MODIFY_PLMN_INFO_STRU* NAS_MMC_GetPrefPlmnCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPreflmnInfo);
}


VOS_VOID NAS_MMC_InitDetachReqCtx(
    NAS_MMC_DETACH_REQ_CTX_STRU        *pstDetachReqCtx
)
{
    pstDetachReqCtx->enDetachReason = NAS_MSCC_PIF_DETACH_REASON_BUTT;

    pstDetachReqCtx->enDetachType   = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    return;
}


NAS_MMC_DETACH_REQ_CTX_STRU *NAS_MMC_GetDetachReqCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stDetachReqCtx);
}


VOS_VOID NAS_MMC_InitAttachReqCtx(
    NAS_MMC_ATTACH_REQ_CTX_STRU        *pstAttachReqCtx
)
{
    pstAttachReqCtx->ulOpID = 0;

    return;
}


VOS_UINT32 NAS_MMC_GetAttachReqOpId(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID);
}


VOS_VOID NAS_MMC_SetAttachReqOpId(VOS_UINT32 ulOpId)
{
    NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID = ulOpId;
}

/*lint -restore */


NAS_MMC_FSM_GET_GEO_CTX_STRU* NAS_MMC_GetFsmCtxAddr_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx);
}


NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU* NAS_MMC_GetGeoRatInfoList_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetGeoRatListInfo_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.stGetGeoRatInfoList);
}


VOS_UINT8 NAS_MMC_GetAbortFlag_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag;
}


VOS_VOID NAS_MMC_SetAbortFlag_GetGeo(
    VOS_UINT8                           ucAbortFlag
)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag = ucAbortFlag;
    return;
}


VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg;
}


VOS_VOID NAS_MMC_SetNotifyMsccFlag_GetGeo(
    VOS_UINT8                           ucNotifyMsccFlg
)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg = ucNotifyMsccFlg;

    return;
}


NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8 NAS_MMC_GetFsmTaskPhase_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase;
}


VOS_VOID NAS_MMC_SetFsmTaskPhase_GetGeo(
    NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8     enGetGeoTaskPhase
)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase = enGetGeoTaskPhase;

    return;
}


NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    return g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene;
}


VOS_VOID NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32             enPlmnSearchScene
)
{
    g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene = enPlmnSearchScene;

    return;
}


NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU* NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.astHistorySearchRatInfo[0]);
}


NAS_MMC_RAT_SEARCH_INFO_STRU* NAS_MMC_GetSearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);
}


VOS_VOID NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;


    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 备份HISTORY搜网数据 */
    pstSearchRatInfo                    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    PS_MEM_SET(pstHsirotySearchRatInfo, 0, sizeof(NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstHsirotySearchRatInfo[i].enRatType                = pstSearchRatInfo[i].enRatType;
        pstHsirotySearchRatInfo[i].ucHistorySearchedFlag    = pstSearchRatInfo[i].ucHistorySearchedFlag;
    }

    /* 备份搜网场景 */
    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(enPlmnSearchScene);

    return;
}


VOS_VOID NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo

)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;

    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    /* 恢复HISTORY搜网数据 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType             = pstHsirotySearchRatInfo[i].enRatType;
        pstSearchRatInfo[i].ucHistorySearchedFlag = pstHsirotySearchRatInfo[i].ucHistorySearchedFlag;
    }
    return;
}


VOS_VOID NAS_MMC_InitNoRFBackUpSearchedInfoCtx(
    NAS_MMC_BACK_UP_SEARCH_INFO_STRU*         pstBackSearchInfo
)
{
    VOS_UINT32                                              i;

    pstBackSearchInfo->stNoRFBackUpSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].enRatType                        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].ucHistorySearchedFlag            = VOS_FALSE;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[0]                   = 0;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[1]                   = 0;
    }
    return;
}


VOS_VOID NAS_MMC_GetCampPosition(
    NAS_MSCC_PIF_CAMP_POSITION_STRU    *pstCampPosition
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;

    pstCampPlmnInfo               = NAS_MML_GetCurrCampPlmnInfo();

    pstCampPosition->stPlmnId     = pstCampPlmnInfo->stLai.stPlmnId;
    pstCampPosition->ulCellId     = pstCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId;
    pstCampPosition->usLac        = (pstCampPlmnInfo->stLai.aucLac[0] << 8) | (pstCampPlmnInfo->stLai.aucLac[1]);
    pstCampPosition->ucRac        = pstCampPlmnInfo->ucRac;
    pstCampPosition->enNetRatType = NAS_MML_GetCurrNetRatType();

}


MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8 NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection( VOS_VOID )
{
    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus);
}


VOS_VOID NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus = enLmmAttachClRegStatus;

    return;
}


VOS_UINT32 NAS_MMC_GetCountryCode_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          ulCurrCampPlmnMcc;
    VOS_UINT32                          ulLastCampedPlmnMcc;

    ulCurrCampPlmnMcc   = NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc;
    ulLastCampedPlmnMcc = NAS_MMC_GetLastCampedPlmnid()->ulMcc;

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_GetCountryCode_PlmnSelection: ulCurrCampPlmnMcc, ulLastCampedPlmnMcc",
        ulCurrCampPlmnMcc, 
        ulLastCampedPlmnMcc);

    if (NAS_MML_INVALID_MCC != ulCurrCampPlmnMcc)
    {
        /* 当前驻留小区国家码为有效值，直接返回 */
        return ulCurrCampPlmnMcc;
    }

    /* 当前驻留小区信息已被清除，取上一次成功驻留小区的MCC */
    return ulLastCampedPlmnMcc;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU* NAS_MMC_GetCLAssociatedInfoAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stPlmnSearchCtrl.stCLAssociatedInfoNtf);
}
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


