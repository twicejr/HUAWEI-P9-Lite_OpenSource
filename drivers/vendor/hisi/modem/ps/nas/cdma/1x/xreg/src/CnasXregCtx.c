/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregCtx.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : 1X REG(register)任务上下文管理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregCtx.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasMntn.h"
#include  "CnasXregRegingProcTbl.h"
#include  "CnasXregFsmSwitchOnTbl.h"

/* add by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
#include  "CnasCcb.h"
/* add by d00212987 for CNAS内存裁剪, 2015-09-18, end */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_XREG_CTX_STRU                      g_stCnasXregCtx;


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : CNAS_XREG_FSM_CTX_STRU             *pstCurrFsmCtx
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitCurrFsmCtx(
    CNAS_XREG_FSM_CTX_STRU             *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_XREG_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_XREG_GetMainFsmDescAddr();
    pstCurrFsmCtx->enParentFsmId            =   CNAS_XREG_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->ulState                  =   CNAS_XREG_L1_STA_NULL;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               CNAS_XREG_MAX_MSG_BUFFER_LEN);

    /* unFsmCtx本次迭代不涉及 */
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : CNAS_XREG_FSM_STACK_STRU           *pstFsmStack
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitFsmStackCtx(
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < CNAS_XREG_MAX_FSM_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_XREG_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_XREG_L1_STA_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitCacheMsgQueue
 功能描述  : 初始化缓存消息队列
 输入参数  : CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstCacheMsgQueue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_VOID CNAS_XREG_InitCacheMsgQueue(
    CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstCacheMsgQueue
)
{
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    VOS_UINT32                          i;

    pstCacheMsgQueue->ulCurrIndex     = 0;
    pstCacheMsgQueue->ucCacheMsgNum   = 0;

    for (i = 0; i < CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM; i++)
    {
        pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
    }
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitCtx
 功能描述  : 初始化上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitCtx(VOS_VOID)
{
    CNAS_XREG_CTX_STRU                 *pstXregCtx = VOS_NULL_PTR;

    pstXregCtx = CNAS_XREG_GetCtxAddr();

    /* 初始化XREG当前状态机上下文 */
    CNAS_XREG_InitCurrFsmCtx(&(pstXregCtx->stCurFsm));

    /* 初始化XREG状态机栈上下文 */
    CNAS_XREG_InitFsmStackCtx(&(pstXregCtx->stFsmStack));

    /* 初始化XREG缓存消息队列 */
    CNAS_XREG_InitCacheMsgQueue(&(pstXregCtx->stCacheMsgQueue));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitFsmCtx_L1Main(VOS_VOID)
{
    /* 本次迭代不涉及 */

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_LoadSubFsm
 功能描述  : 加载L2状态机的信息
 输入参数  : CNAS_XREG_FSM_ID_ENUM_UINT32         enFsmId
             CNAS_XREG_FSM_CTX_STRU              *pstCurFsm
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XREG_LoadSubFsm(
    CNAS_XREG_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XREG_FSM_CTX_STRU              *pstCurFsm
)
{
    /* 在本次开发阶段，只有开关机状态机 */
    switch (enFsmId)
    {
        case CNAS_XREG_FSM_SWITCH_ON:
            pstCurFsm->ulState                  = CNAS_XREG_SWITCH_ON_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XREG_GetSwitchOnFsmDescAddr();
            break;

        case CNAS_XREG_FSM_REGING :
            pstCurFsm->ulState                  = CNAS_XREG_REGING_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XREG_GetRegingFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : pstFsmStack -- 状态机栈
             pstNewFsm   -- 需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月15日
   作    者   : l60609
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_PushFsm(
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack,
    CNAS_XREG_FSM_CTX_STRU             *pstNewFsm
)
{
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;

    /* 入参指针检查 */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG,
                       "CNAS_XREG_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* 栈深度检查 */
    if (pstFsmStack->usStackDepth >= CNAS_XREG_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG,
                       "CNAS_XREG_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push当前状态机上下文入栈 */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(CNAS_XREG_FSM_CTX_STRU));

    /* 栈深度增加 */
    pstFsmStack->usStackDepth++;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月15日
   作    者   : l60609
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_PopFsm(VOS_VOID)
{
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack = CNAS_XREG_GetFsmStackAddr();
    pstCurFsm   = CNAS_XREG_GetCurFsmAddr();

    /* 检查栈空间是否为空 */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_PopFsm: FSM Stack is empty");

        return;
    }

    /* 状态机栈深度减少 */
    pstFsmStack->usStackDepth--;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(CNAS_XREG_FSM_CTX_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_InitFsmL2
 功能描述  : XREG启动一个L2的状态机。启动流程的同时启动状态以及保护定时器
             该函数会进行压栈操作,如果不需要进行压栈, 必须保证退出前流程
 输入参数  : CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitFsmL2(
    CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId
)
{
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;
    CNAS_XREG_FSM_ID_ENUM_UINT32        enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XREG, CNAS_XREG_GetCurrFsmId(), CNAS_XREG_GetFsmTopState(), 0);

    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId     = CNAS_XREG_GetCurrFsmId();
    ulParentEventType = CNAS_XREG_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    pstFsmStack = CNAS_XREG_GetFsmStackAddr();
    pstCurFsm   = CNAS_XREG_GetCurFsmAddr();
    CNAS_XREG_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId = enFsmId;

    /* 加载L2状态机 */
    CNAS_XREG_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XREG, CNAS_XREG_GetCurrFsmId(), CNAS_XREG_GetFsmTopState(), 0);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : l60609
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_QuitFsmL2(VOS_VOID)
{
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm = CNAS_XREG_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  打印压栈前的L1和L2状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XREG, CNAS_XREG_GetCurrFsmId(), CNAS_XREG_GetFsmTopState(), 0);

    /* 状态机出栈操作 */
    CNAS_XREG_PopFsm();

    /*  打印当前的L1和L2状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XREG, CNAS_XREG_GetCurrFsmId(), CNAS_XREG_GetFsmTopState(), 0);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCtxAddr
 功能描述  : 获取上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XREG_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_CTX_STRU* CNAS_XREG_GetCtxAddr(VOS_VOID)
{
    return &(g_stCnasXregCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCurFsmAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_FSM_CTX_STRU* CNAS_XREG_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_XREG_GetCtxAddr()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_FSM_STACK_STRU* CNAS_XREG_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_XREG_GetCtxAddr()->stFsmStack);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XREG_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_XREG_GetCtxAddr()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCurrFsmEntryMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_MSG_STRU* CNAS_XREG_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(CNAS_XREG_GetCtxAddr()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCurrFsmId
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_FSM_ID_ENUM_UINT32 CNAS_XREG_GetCurrFsmId(VOS_VOID)
{
    return (CNAS_XREG_GetCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetFsmTopState(VOS_VOID)
{
    return (CNAS_XREG_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  CNAS_XREG_GetFsmStackDepth(VOS_VOID)
{
    CNAS_XREG_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XREG_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetCurrFsmState
 功能描述  : 设置当前状态机状态
 输入参数  : VOS_UINT32                          ulCurrState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = CNAS_XREG_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XREG, CNAS_XREG_GetCurrFsmId(), ulCurrState, 0);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg:栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XREG_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XREG_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  CNAS_XREG_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XREG_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年8月27日
     作    者   : h00246512
     修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理CNAS XSD入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCacheMsgNum
 功能描述  : 获取当前缓存消息的个数
 输入参数  : 无
 输出参数  : 当前缓存消息的个数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_GetCacheMsgNum(VOS_VOID)
{
    CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = CNAS_XREG_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCacheMsgAddr
 功能描述  : 获取缓存消息队列地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XREG_CACHE_MSG_QUEUE_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_CACHE_MSG_QUEUE_STRU* CNAS_XREG_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_XREG_GetCtxAddr()->stCacheMsgQueue);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearCacheMsg
 功能描述  : 清除当前的缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:清除成功
             VOS_FALSE:清除失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月06日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_VOID CNAS_XREG_ClearCacheMsg(VOS_VOID)
{
    CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ulOffset;

    pstMsgQueue = CNAS_XREG_GetCacheMsgAddr();

    if ((pstMsgQueue->ucCacheMsgNum < 1)
        ||(pstMsgQueue->ucCacheMsgNum >= CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM))
    {
        return;
    }

    ulOffset = (pstMsgQueue->ulCurrIndex % CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM);
	
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    if(VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ulOffset])
    {
        PS_MEM_FREE(UEPS_PID_XREG, pstMsgQueue->pastCacheMsg[ulOffset]);
    }
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    pstMsgQueue->ulCurrIndex = (pstMsgQueue->ulCurrIndex + 1) % CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM;

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetNextCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级最高的缓存消息
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_UINT32  CNAS_XREG_GetNextCachedMsg(
    CNAS_XREG_MSG_STRU                 *pstEntryMsg
)
{
    /* 获取缓存消息成功,返回缓存消息 */
    CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstMsgQueue    = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          i;
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return VOS_FALSE;
    }

    pstMsgQueue = CNAS_XREG_GetCacheMsgAddr();

    if (pstMsgQueue->ucCacheMsgNum < 1)
    {
        return VOS_FALSE;
    }

    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    if ((pstMsgQueue->ucCacheMsgNum >= CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM)
        ||(pstMsgQueue->ucCacheMsgNum == VOS_NULL))
    {
        /* 释放申请内存 */
        for (i = 0; i < CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_XREG, pstMsgQueue->pastCacheMsg[i]);
            }
        }

        VOS_MemSet(pstMsgQueue, VOS_NULL, sizeof(CNAS_XREG_CACHE_MSG_QUEUE_STRU));

        return VOS_FALSE;
    }

    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[pstMsgQueue->ulCurrIndex]);

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    ulMsgLen = (pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

    if (CNAS_XREG_MAX_MSG_BUFFER_LEN < ulMsgLen)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_GetNextCachedMsg: beyond msg size ");

        ulMsgLen = CNAS_XREG_MAX_MSG_BUFFER_LEN;
    }

    VOS_MemCpy(&pstEntryMsg->aucMsgBuffer[0], pstCacheMsgHdr, ulMsgLen);
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    CNAS_XREG_ClearCacheMsg();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SaveMsgToCache
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级最高的缓存消息
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月7日
   作    者   : h00246512
   修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_VOID  CNAS_XREG_SaveMsgToCache(
    VOS_UINT32                          ulEventType,
    VOS_UINT8                           *pucMsg
)
{
    /* 获取缓存消息成功,返回缓存消息 */
    CNAS_XREG_CACHE_MSG_QUEUE_STRU     *pstMsgQueue = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          i;

    if (VOS_NULL_PTR == pucMsg)
    {
        return ;
    }

    pstMsgQueue = CNAS_XREG_GetCacheMsgAddr();

    if (pstMsgQueue->ucCacheMsgNum >= CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM)
    {
        /* 释放申请内存 */
        for (i = 0; i < CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_XREG, pstMsgQueue->pastCacheMsg[i]);
            }
        }

        PS_MEM_SET(pstMsgQueue, VOS_NULL, sizeof(CNAS_XREG_CACHE_MSG_QUEUE_STRU));
    }

    ulOffset = (pstMsgQueue->ulCurrIndex + pstMsgQueue->ucCacheMsgNum) % CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM;

    /* 在此申请内测 */
    pstMsgHeader = (MSG_HEADER_STRU*)pucMsg;

    ulMsgLen = (VOS_MSG_HEAD_LENGTH + pstMsgHeader->ulLength);

    pstMsgQueue->pastCacheMsg[ulOffset] = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XREG, ulMsgLen) ;

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[ulOffset])
    {
        return;
    }

    PS_MEM_CPY(pstMsgQueue->pastCacheMsg[ulOffset], pucMsg, ulMsgLen);
    /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

    pstMsgQueue->ucCacheMsgNum++;

    return ;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitFsmCtx_SwitchOn
 功能描述  : 初始化开机状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_InitFsmCtx_SwitchOn(VOS_VOID)
{
    /* 检查当前状态机是否时开机状态机 */
    if (CNAS_XREG_FSM_SWITCH_ON != CNAS_XREG_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_InitFsmCtx_SwitchOn:State is incorrect.");

        return;
    }

    g_stCnasXregCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXregReadCardFileFlg = CNAS_XREG_READ_CARD_FILE_FLG_NULL;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XREG_FSM_SWITCH_ON != CNAS_XREG_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn: State is incorrect.");
    }

    return g_stCnasXregCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXregReadCardFileFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中设置读取卡文件回复标记
 输入参数  : 设置卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XREG_FSM_SWITCH_ON != CNAS_XREG_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn: State is incorrect.");

        return;
    }

    g_stCnasXregCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXregReadCardFileFlg |= enReadCardFileCnfFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中清除读取卡文件回复标记
 输入参数  : 卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XREG_FSM_SWITCH_ON != CNAS_XREG_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn: State is incorrect.");
    }

    g_stCnasXregCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXregReadCardFileFlg &= ~enReadCardFileCnfFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetReadCardFilesIndFlg
 功能描述  : 预处理过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32 CNAS_XREG_GetReadCardFilesIndFlg(VOS_VOID)
{
    return g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enRefreshReadCard;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetReadCardFilesIndFlg
 功能描述  : 预处理过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SetReadCardFilesIndFlg(
    CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32    enRefreshReadCard
)
{
    g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enRefreshReadCard |= enRefreshReadCard;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearReadCardFilesIndFlg
 功能描述  : 预处理过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ClearReadCardFilesIndFlg(
    VOS_UINT32                          ulEfId
)
{
    switch ( ulEfId )
    {
        case USIMM_CDMA_EFTERM_ID:
        case USIMM_CSIM_EFTERM_ID:
            g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enRefreshReadCard &= ~CNAS_XREG_REFRESH_CARD_FILE_TERM_FLG;
            break;

        case USIMM_CSIM_EFSSCI_ID:
        case USIMM_CDMA_EFSSCI_ID:
            g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enRefreshReadCard &= ~CNAS_XREG_REFRESH_CARD_FILE_SSCI_FLG;
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetCardFilesChangeFlg
 功能描述  : 预处理过程中卡文件变化标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32 CNAS_XREG_GetCardFilesChangeFlg(VOS_VOID)
{
    return g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enCardFileChange;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetCardFilesChangeFlg
 功能描述  : 预处理过程中卡文件变化标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SetCardFilesChangeFlg(
    CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32    enCardFileChange
)
{
    g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enCardFileChange |= enCardFileChange;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearRefreshCardFilesCtx
 功能描述  : 预处理过程中卡文件变化标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月25日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ClearRefreshCardFilesCtx(VOS_VOID)
{
    g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enCardFileChange  = CNAS_XREG_CARD_FILE_CHANGE_FLG_NULL;
    g_stCnasXregCtx.stRegPreProcCtx.stXregRefreshCardFileStatus.enRefreshReadCard = CNAS_XREG_REFRESH_CARD_FILE_FLG_NULL;

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



