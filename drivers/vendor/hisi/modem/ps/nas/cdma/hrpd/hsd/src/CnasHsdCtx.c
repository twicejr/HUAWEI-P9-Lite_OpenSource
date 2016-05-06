/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdCtx.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2014年12月15日
  功能描述   : HRPD SD(system determination)状态机处理代码和全局变量管理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx -- 当前状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : 无
 输出参数  : pstFsmStack -- 状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitCacheMsgQueue
 功能描述  : 初始化缓存的消息队列
 输入参数  : 无
 输出参数  : pstCacheMsgQueue -- 缓存的消息队列信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数
 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪

*****************************************************************************/
VOS_VOID CNAS_HSD_InitCacheMsgQueue(
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue,
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
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
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitSysRecList
 功能描述  : 初始化关联HRPD系统表
 输入参数  : enInitType----初始化类型
 输出参数  : pstSysRecList -- 系统表列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitScanChanList
 功能描述  : 初始化频点扫描列表
 输入参数  : enInitType----初始化类型
 输出参数  : pstScanChanList -- 频点扫描列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitSystemAcquireCtrl
 功能描述  : 初始化HRPD系统获取控制信息
 输入参数  : enInitType------初始化类型
 输出参数  : pstSysAcqCtrl -- 系统获取控制信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitSystemAcquireCtrl
 功能描述  : 初始化HRPD系统获取控制信息
 输入参数  : enInitType------初始化类型
 输出参数  : pstSysAcqCtrl -- 系统获取控制信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmCtx_SwitchOn
 功能描述  : 初始化开机状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmCtx_SysAcq
 功能描述  : 初始化SYSTEM ACQUIRE状态机的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitCtx
 功能描述  : HSD 上下文全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_LoadSubFsm
 功能描述  : 加载L2状态机的信息
 输入参数  : enFsmId - L2状态机ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : pstFsmStack -- 状态机栈
             pstNewFsm   -- 需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmL2
 功能描述  : HSD启动一个L2的状态机。启动流程的同时启动状态以及保护定时器
              该函数会进行压栈操作,如果不需要进行协议栈压栈, 必须保证退出前流程
 输入参数  : enFsmId -- L2状态机ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数
 2.日    期   : 2015年07月13日
   作    者   : z00316370
   修改内容   : 清TQE
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数
 2.日    期   : 2015年07月13日
   作    者   : z00316370
   修改内容   : 清TQE

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHsdCtxAddr
 功能描述  : 获取当前HSD的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前HSD的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_CTX_STRU* CNAS_HSD_GetHsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_FSM_STACK_STRU* CNAS_HSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stFsmStack);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurFsmAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_FSM_CTX_STRU* CNAS_HSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_HSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg -- 栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回栈pop标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCacheMsgAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS HSD缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_CACHE_MSG_QUEUE_STRU* CNAS_HSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType -- 消息ID+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_VOID CNAS_HSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
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
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_INFO_LOG1(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCacheMsg
 功能描述  : 保存当前需要处理的缓存
 输入参数  : ulEventType -- 消息ID+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 保存成功
             VOS_FALSE -- 保存失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_HSD_ClearCacheMsg
 功能描述  : 清除指定的缓存消息
 输入参数  : ulCurrIndex -- 清除指定index的消息
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
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
        /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
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
       /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNextCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg -- 当前需要处理的消息地址

 返 回 值  : VOS_TRUE  -- 获取成功
             VOS_FALSE -- 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetNextCachedMsg(
    CNAS_HSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
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
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    /* 清除index为0的cache消息 */
    CNAS_HSD_ClearCacheMsg(0);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCacheMsgNum
 功能描述  : 获取当前缓存的消息个数
 输入参数  : 无
 输出参数  :
 返 回 值  : 当前存在的缓存个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue;

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetCurrFsmState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurrFsmEntryMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_MSG_STRU* CNAS_HSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
 1.日    期   : 2014年12月15日
     作    者   : g00256031
     修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
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

    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    if (CNAS_HSD_MAX_MSG_BUFFER_LEN < ulLen)
    {
        CNAS_ERROR_LOG( UEPS_PID_HSD, "CNAS_HSD_SaveCurEntryMsg: msg size big than 1600!" );
        ulLen = CNAS_HSD_MAX_MSG_BUFFER_LEN;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY(&pstEntryMsg->aucMsgBuffer[0], pstMsg, ulLen );
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurrFsmId
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数


*****************************************************************************/
CNAS_HSD_FSM_ID_ENUM_UINT32 CNAS_HSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasHsdCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetIntMsgQueueAddr
 功能描述  : 获取内部消息队列首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_HSD_INT_MSG_QUEUE_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_HSD_INT_MSG_QUEUE_STRU* CNAS_HSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitInternalBuffer
 功能描述  : 初始化HSD内部消息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_HSD_PutMsgInIntMsgQueue
 功能描述  : 将消息放到内部消息队列中
 输入参数  : pSndMsg:待发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNextIntMsg
 功能描述  : 获取内部消息队列中的下一条可用的内部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetIntMsgNum
 功能描述  : 获取当前HSD内部消息个数
 输入参数  : 无
 输出参数  :
 返 回 值  : 当前存在的内部消息个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中设置读取卡文件回复标记
 输入参数  : 设置卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中清除读取卡文件回复标记
 输入参数  : 卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetModeType
 功能描述  : 当前模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_GetModeType(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetSysModeType
 功能描述  : 设置当前搜网模式:混合或非混合
 输入参数  : enModeType:搜网模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysModeType(CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 enModeType)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType = enModeType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Get1xSystemInfo
 功能描述  : 设置当前频点扫描列表中当前扫描到的列表索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_1X_SYSTEM_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月6日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_Get1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.st1xSysInfo);
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanListMatched1xSystemInfo
 功能描述  : 获取建表时的1X系统
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_1X_SYSTEM_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月26日
   作    者   : c00299064
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_GetScanListMatched1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdMatched1xSysInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMruList
 功能描述  : 得到MRU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_HRPD_MRU_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_HRPD_MRU_LIST_STRU* CNAS_HSD_GetMruList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList);
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_UpdateMru0
 功能描述  : 更新MRU0
 输入参数  : pstCurSysId - EVDO系统
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMruListNum
 功能描述  : 获取MRU table中系统个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回MRU table中系统个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMru0SysId
 功能描述  : 获取MRU0对应的系统ID
 输入参数  : 无
 输出参数  : pstMru0SysId------MRU0对应的系统ID
 返 回 值  : 获取成功:VOS_TRUE
             获取失败:VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysRecListAddr
 功能描述  : 获取系统频点列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前系统频点列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/

CNAS_HSD_HRPD_SYS_LIST_STRU* CNAS_HSD_GetSysRecListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSysRecList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysRecItemNum
 功能描述  : 获取系统频点列表总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取系统频点列表总个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetSysRecItemNum(VOS_VOID)
{
    return (CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetSysRecListIndex
 功能描述  : 设置当前系统列表个数
 输入参数  : usHrpdSysNum-----系统个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月6日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysRecListIndex(
    VOS_UINT16                          usHrpdSysNum
)
{
    CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum = usHrpdSysNum;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanFreqListAddr
 功能描述  : 获取频点扫描列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月12日
   作    者   : c00299064
   修改内容   : 新生成函数

*****************************************************************************/

CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU* CNAS_HSD_GetScanFreqListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stScanFreqList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanFreqNum
 功能描述  : 获取当前频点扫描列表中频点总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表中频点总个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetScanFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usAvailFreqNum);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurScanFreqIndex
 功能描述  : 获取当前频点扫描列表中当前扫描到的列表索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表中当前扫描到的列表索引
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetCurScanFreqIndex(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usCurrIndex);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanListAvailFreqNum
 功能描述  : 从Scan List中获取剩余可用频点数
 输入参数  : NA

 输出参数  : NA

 返 回 值  : VOS_UINT16 /从Scan List中获取剩余可用频点数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetCurScanFreqIndex
 功能描述  : 设置当前频点扫描列表中当前扫描到的列表索引
 输入参数  : usCurScanIndex------当前频点扫描列表中当前扫描到的列表索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetCurScanFreqIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    CNAS_HSD_GetScanFreqListAddr()->usCurrIndex = usCurScanIndex;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanFreqByIndex
 功能描述  : 通过索引获得捕获频点
 输入参数  : usFreqIndex------列表索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetRedirectionFreqAddr
 功能描述  : 获取重定向频点列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前重定向列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月6日
   作    者   : d00212987
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_REDIRECTION_STRU* CNAS_HSD_GetRedirectionFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetRedirectionFreqNum
 功能描述  : 获取重定向频点列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前重定向列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月6日
   作    者   : d00212987
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetRedirectionFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection.ucChanNum);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetOocScheduleConfigInfo
 功能描述  : 获取OOC下调度配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回OOC调度配置信息地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月08日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_OOC_CONFIG_INFO_STRU *CNAS_HSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetOocScheduleInfo
 功能描述  : 获取OOC下调度信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回OOC调度信息地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月13日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_OOC_SCHEDULE_INFO_STRU *CNAS_HSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitOocScheduleInfo
 功能描述  : 初始化OOC下调度信息
 输入参数  : pstOocScheduleInfo -- 初始化类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月13日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitOocCtxInfo
 功能描述  : 初始化OOC上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月13日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetOocWaitSearchFlag
 功能描述  : 获取OOC等待搜索标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月14日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetOocWaitSearchFlag
 功能描述  : 设置OOC等待搜索标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月14日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAvoidFreqListAddr
 功能描述  : 获取avoid频点列表地址
 输入参数  : 无

 输出参数  : 无
 返 回 值  : CNAS_HSD_AVOID_FREQ_LIST_STRU* -- avoid频点列表首地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月06日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_AVOID_FREQ_LIST_STRU* CNAS_HSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stSysAcqCtrl.stAvoidFreqList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAvoidFreqListUsedNum
 功能描述  : 获取avoid频点列表数目
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT8 -- avoid列表数目
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月06日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetAvoidFreqListUsedNum(VOS_VOID)
{
    return (CNAS_HSD_GetAvoidFreqListAddr()->ucAvoidItemUsedNum);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCasSessionNegStatus
 功能描述  : 获取Session negotiation状态
 输入参数  : 无

 输出参数  : 无
 返 回 值  : CNAS_HSD_CAS_SESSION_NEG_STATUS_ENUM_UINT32 -- 状态枚举值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32 CNAS_HSD_GetSessionNegStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCasSessionNegStatus
 功能描述  : 保存Session negotionation状态
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SaveSessionNegStatus(
    CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32                 enSessionNegStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus = enSessionNegStatus;

     return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetATStatus
 功能描述  : 获取Cas状态
 输入参数  : 无

 输出参数  : 无
 返 回 值  : CNAS_HSD_CAS_STATUS_ENUM_UINT32 -- 状态枚举值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_GetATStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveATStatus
 功能描述  : 保存Cas状态
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SaveATStatus(
    CNAS_HSD_AT_STATUS_ENUM_UINT32     enATStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus = enATStatus;

     return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHistorySysList
 功能描述  : 获取历史驻留的Hrpd信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_HISTORY_SYS_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_HISTORY_SYS_LIST_STRU* CNAS_HSD_GetHistorySysList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHistorySysList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_UpdateHistorySysList
 功能描述  : 更新历史驻留的Hrpd信息
 输入参数  : pstCurrSystem - 当前驻留的系统
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHrpdSysStatus
 功能描述  : 获取当前Hrpd可用信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 Hrpd可用状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 CNAS_HSD_GetHrpdSysStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetHrpdSysStatus
 功能描述  : 设置当前Hrpd可用信息
 输入参数  : enStatus:Hrpd可用状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus = enStatus;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCampedHrpdSystemInfo
 功能描述  : 获取当前驻留的Hrpd信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_PRL_HRPD_SYSTEM_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCampedHrpdSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.stCampedHrpdSysInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_UpdateHrpdSysInfo
 功能描述  : 更新当前驻留的Hrpd信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateHrpdSysInfo(CNAS_PRL_HRPD_SYSTEM_STRU *pstSystem)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* 设置当前Hrpd系统可用 */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_AVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_CPY(pstHrpdSystem, pstSystem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ClearHrpdSysInfo
 功能描述  : 清除当前驻留的Hrpd信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearHrpdSysInfo(VOS_VOID)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* 设置当前Hrpd系统非驻留 */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_SET(pstHrpdSystem, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetNoRfScene
 功能描述  : 设置NoRf场景
 输入参数  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene = enNoRfScene;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNoRfScene
 功能描述  : 获得NoRf场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetNoRfScene(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNoRf1XUeStatus
 功能描述  : 获得NoRf场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_CAS_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月03日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_HSD_GetNoRf1XUeStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetNoRf1XUeStatus
 功能描述  : 获得NoRf场景
 输入参数  : CNAS_CCB_1X_CAS_STATE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月03日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetNoRf1XUeStatus(CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus = enStatus;
    return ;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_SetAbortFlg_SysAcq
 功能描述  : 设置当前状态机打断标记和打断场景
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : 若当前打断场景优先级更高，则将之前的消息丢弃
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAbortFlg_SysAcq
 功能描述  : 获取当前状态机打断标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAbortReason_SysAcq
 功能描述  : 获取当前状态机打断场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_HSD_ABORT_REASON_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHighPriorityFreqAddr
 功能描述  : 获取高优先级频点列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前重定向列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_HIGHPRIORITY_STRU* CNAS_HSD_GetHighPriorityFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHighPriorityFreqNum
 功能描述  : 获取高优先级频点列表的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前高优先级频点列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetHighPriorityFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority.ucFreqNum);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitHighPriorityFreq
 功能描述  : 初始化高优先级频点列表
 输入参数  : 当前高优先级频点列表的地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_InitHighPriorityFreq(CNAS_HSD_HIGHPRIORITY_STRU* pstHighFreq)
{
    PS_MEM_SET(pstHighFreq, 0, sizeof(CNAS_HSD_HIGHPRIORITY_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCasOhmHrpdSysAddr
 功能描述  : 获取空口上报频点的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前空口上报频点的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月27日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCasOhmHrpdSysAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stCasOhmHrpdSys);
}

/* add by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetEventType
 功能描述  : 通过缓存消息获取EventType
 输入参数  : pstMsgQueue        -- 缓存消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月10日
   作    者   : d00212987
   修改内容   : 新生成函数
*****************************************************************************/
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
/* add by d00212987 for CNAS内存裁剪, 2015-09-18, end */

/*****************************************************************************
 函 数 名  : CNAS_HSD_SortCacheMsgInMsgQueue
 功能描述  : 对缓存消息保存的缓存内存池进行排序，优先级高的消息优先处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月29日
   作    者   : z00316370
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_VOID CNAS_HSD_SortCacheMsgInMsgQueue(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucPri1;
    VOS_UINT8                           ucPri2;
/* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */	
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
/* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCacheMsgPriority
 功能描述  : 获取当前事件消息的优先级
 输入参数  : ulEventType        -- 事件类型
 输出参数  : 无
 返 回 值  : 待缓存消息对应的优先级
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月29日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitFsmCtx_InterSys
 功能描述  : 初始化INTER SYS状态机的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetAbortFlg_InterSys
 功能描述  : 设置当前状态机打断标记和打断场景
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : 若当前打断场景优先级更高，则将之前的消息丢弃
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAbortFlg_InterSys
 功能描述  : 获取当前状态机打断标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAbortReason_InterSys
 功能描述  : 获取当前状态机打断场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_HSD_ABORT_REASON_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNetwkLostSysRec
 功能描述  : 获取丢网记录信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU* CNAS_HSD_GetNetwkLostSysRec(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stNetwkLostSysRec);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFreqLockAddr
 功能描述  : 获取stFreqLockPara地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_HSD_GetFreqLockAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetFreqLockMode
 功能描述  : 获取当前锁频模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ucFreqLockMode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetFreqLockMode(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHrpdRfAvailFlg
 功能描述  : 获取当前X模射频资源可用标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetHrpdRfAvailFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHrpdRfAvailFlg
 功能描述  : 设置当前X模射频资源可用标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetHrpdRfAvailFlg(VOS_UINT8 ucHrpdRfAvailFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg = ucHrpdRfAvailFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMru0RelateFlg
 功能描述  : 获取Mru0相关标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetMru0RelateFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetMru0RelateFlg
 功能描述  : 设置Mru0相关标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetMru0RelateFlg(VOS_UINT8 ucMru0RelateFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg = ucMru0RelateFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitCFreqLockValue
 功能描述  : 初始化stFreqLockPara
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasHsdCFreqLockValue;

    pstCnasHsdCFreqLockValue = CNAS_HSD_GetFreqLockAddr();

    PS_MEM_SET(pstCnasHsdCFreqLockValue, 0x00, sizeof(CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetUeSupportedBandClass
 功能描述  : 获取支持的band
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetUeSupportedBandClass(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ulUeSupportedBand);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetTestConfig
 功能描述  : 获取stTestConfig首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回stTestConfig首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_HSD_TEST_CONFIG_STRU* CNAS_HSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stTestConfig);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetSysCfgFlag
 功能描述  : 设置SysCfg消息有没有完成
 输入参数  : VOS_TRUE : 已经发送给CAS，CAS还没有回复
             VOS_FALSE: SysCfg已经完成
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysCfgFlag(VOS_UINT8 ucIsSysCfg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg = ucIsSysCfg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysCfgFlag
 功能描述  : 获得SysCfg标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE : 已经发送给CAS，CAS还没有回复
             VOS_FALSE: SysCfg已经完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetSysCfgFlag(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMatchedHrpdSysIndexListAddr
 功能描述  : 获取匹配系统表索引值的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 匹配系统表索引值的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/

CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU* CNAS_HSD_GetMatchedHrpdSysIndexListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMatchedHrpdSysIndexList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitMatchedHrpdSysIndexAddr
 功能描述  : 初始化匹配系统表索引值列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_InitMatchedHrpdSysIndexList(VOS_VOID)
{
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU              *pstMatchedHrpdSysIndex;

    pstMatchedHrpdSysIndex              = CNAS_HSD_GetMatchedHrpdSysIndexListAddr();
    pstMatchedHrpdSysIndex->usIndexNum  = 0;

    PS_MEM_SET(pstMatchedHrpdSysIndex->ausMatchedHrpdSysIndexList, 0, CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM * (sizeof(VOS_UINT16)));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetAbortFlg_SysAcq
 功能描述  : 判断该打断是否已存在
 输入参数  : CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
 输出参数  : 无
 返 回 值  : VOS_TRUE   --已存在
             VOS_FALSE  --不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月7日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetAbnormalLostFlag
 功能描述  : 设置IDLE态收到CAS的abnormal lost标志
 输入参数  : VOS_TRUE : IDLE态收到AbnormalLost
             VOS_FALSE: 未在IDLE态收到AbnormalLost
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月27日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetAbnormalLostFlag(VOS_UINT8 ucIsAbnormalLost)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucIsAbnormalLostFLg = ucIsAbnormalLost;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAbnormalLostFlag
 功能描述  : 获得IDLE态收到CAS的abnormal lost标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE : IDLE态收到AbnormalLost
             VOS_FALSE: 未在IDLE态收到AbnormalLost
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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



