/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsCtx.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月14日
  最近修改   :
  功能描述   : XPDS Cagps Ctx Info
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月14日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/

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
/*****************************************************************************
 函 数 名  : TAF_XPDS_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : TAF_XPDS_FSM_CTX_STRU             *pstCurrFsmCtx
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : TAF_XPDS_FSM_STACK_STRU           *pstFsmStack
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitPosCtx
 功能描述  : 初始化定位相关全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitCtx
 功能描述  : 初始化上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_InitFsmCtx_L1Main(VOS_VOID)
{
    /* 本次迭代不涉及 */

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_LoadSubFsm
 功能描述  : 加载L2状态机的信息
 输入参数  : TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId
             TAF_XPDS_FSM_CTX_STRU              *pstCurFsm
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_XPDS_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : pstFsmStack -- 状态机栈
             pstNewFsm   -- 需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_XPDS_InitFsmL2
 功能描述  : XPDS启动一个L2的状态机。启动流程的同时启动状态以及保护定时器
             该函数会进行压栈操作,如果不需要进行压栈, 必须保证退出前流程
 输入参数  : TAF_XPDS_FSM_ID_ENUM_UINT32        enFsmId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCtxAddr
 功能描述  : 获取上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_CONTEXT_STRU* TAF_XPDS_GetCtxAddr(VOS_VOID)
{
    return  &g_stTafXpdsCtx;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCurFsmAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_FSM_CTX_STRU* TAF_XPDS_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_FSM_STACK_STRU* TAF_XPDS_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stFsmStack);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_XPDS_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCurrFsmEntryMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_MSG_STRU* TAF_XPDS_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCurrFsmId
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_FSM_ID_ENUM_UINT32 TAF_XPDS_GetCurrFsmId(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetFsmTopState(VOS_VOID)
{
    return (TAF_XPDS_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  TAF_XPDS_GetFsmStackDepth(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetCurrFsmState
 功能描述  : 设置当前状态机状态
 输入参数  : VOS_UINT32                          ulCurrState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg:栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_XPDS_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  TAF_XPDS_GetFsmStackPopFlg(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetIntMsgQueueAddr
 功能描述  : 获取内部消息队列首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_INT_MSG_QUEUE_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数
*****************************************************************************/
TAF_XPDS_INT_MSG_QUEUE_STRU* TAF_XPDS_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitInternalBuffer
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_PutMsgInIntMsgQueue
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetNextIntMsg
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetIntMsgNum
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
VOS_UINT8 TAF_XPDS_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetTimerCtxAddr
 功能描述  : 获取XPDS Timer Context
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_TIMER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_TIMER_CTX_STRU* TAF_XPDS_GetTimerCtxAddr(VOS_VOID)
{
    return g_stTafXpdsCtx.astTimerCtx;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCgpsInitialType
 功能描述  : 获取AGPS触发的原因，SI or NI
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_INITIAL_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_INITIAL_TYPE_ENUM_UINT32 TAF_XPDS_GetCgpsInitialType(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enAgpsType;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetAgpsFixMode
 功能描述  : 获取CAGPS工作Mode
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_FIX_MODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_FIX_MODE_ENUM_UINT8 TAF_XPDS_GetAgpsFixMode(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enFixMode;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetAgpsFixMode
 功能描述  : set the Fix mode to
                TAF_XPDS_MSA_MODE,
                TAF_XPDS_MSB_MODE,
                TAF_XPDS_MSS_MODE,
                TAF_XPDS_AFLT_MODE,
 输入参数  : TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode
 输出参数  : TAF_XPDS_FIX_MODE_ENUM_UINT8
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : A00903922
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetAgpsFixMode(TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode)
{
    g_stTafXpdsCtx.stCagpsCfg.enFixMode = enFixMode;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetAgpsCfg
 功能描述  : 获取当前CAGPS工作模式，控制面/用户面 MSA/MSB等信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_CFG_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_CFG_INFO_STRU* TAF_XPDS_GetAgpsCfg(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCagpsCfg);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCtrlInfoAddr
 功能描述  : 获取当前CAGPS业务相关的控制信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_CTRL_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_CTRL_INFO_STRU* TAF_XPDS_GetCtrlInfoAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCtrlInfo);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPublicDataAddr
 功能描述  : 获取AGPS公共数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_PUBLIC_DATA_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_PUBLIC_DATA_STRU* TAF_XPDS_GetPublicDataAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPublicData);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetPosProcRslt
 功能描述  :
 输入参数  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPosProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPosProcRslt
)
{
    TAF_XPDS_GetPublicDataAddr()->enPosProcRslt = enPosProcRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPosProcRslt
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetPosProcRslt(VOS_VOID)
{
    return TAF_XPDS_GetPublicDataAddr()->enPosProcRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetUpLinkStatus
 功能描述  : 获取用户面数据传输通道，MPC or PDE链路
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8 TAF_XPDS_GetUpLinkStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetUpLinkStatus
 功能描述  : 更新当前数据传输通道
 输入参数  : TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enUpLinkStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetDataCallStatus
 功能描述  : 获取CAGPS Data Call Status
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32 TAF_XPDS_GetDataCallStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enDataCallState;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetDataCallStatus
 功能描述  : 更新CAGPS Data Call Status
 输入参数  : AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32         enDataCallState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetDataCallStatus(
    AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32         enDataCallState
)
{
    g_stTafXpdsCtx.stUplinkCtx.enDataCallState = enDataCallState;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetMpcServerStatus
 功能描述  : 获取当前MPC Server Bind Status
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetMpcServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPdeServerStatus
 功能描述  : 获取当前PDE Server Bind Status
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetPdeServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetMpcServerStatus
 功能描述  : 更新MPC服务器Bind状态
 输入参数  : AT_XPDS_CHSTATE_ENUM_UINT32         enMpcServerStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetMpcServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus = enMpcServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetPdeServerStatus
 功能描述  : 更新PDE服务器Bind状态
 输入参数  : AT_XPDS_CHSTATE_ENUM_UINT32         enPdeServerStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus = enPdeServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetUpLinkAbortScene
 功能描述  : 获取异常Abort的场景值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetUpLinkAbortScene(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetUplinkAbortScene
 功能描述  : 设置异常Abort的场景值
 输入参数  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetUplinkAbortScene(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
)
{
    g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene = enUpLinkAbortScene;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetCorrelationId
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  TAF_XPDS_GetCorrelationId(VOS_VOID)
{
    VOS_UINT8                           ucCorrelationId = 0;

    ucCorrelationId  = TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId;

    TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId++;

    return ucCorrelationId;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetFwdPdMsgHeader
 功能描述  : Set forward PD msg head to ctx
 输入参数  : TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月14日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetFwdPdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    PS_MEM_CPY(&(TAF_XPDS_GetPdePublicData()->stFwdPdMsgHeader),
               pstPdMsgHeader,
               sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitDefaultCfgInfo
 功能描述  : 初始化CAGPS默认配置
 输入参数  : TAF_XPDS_CFG_INFO_STRU *pstCagpsCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitProvGpsEph
 功能描述  : Init ProvGpsEph
 输入参数  : VOS_VOID
 输出参数  : pstProvEph
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_InitProvGpsEph(
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph
)
{
    PS_MEM_SET(pstProvEph, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitProvGpsAlm
 功能描述  : Init ProvGpsAlm
 输入参数  : VOS_VOID
 输出参数  : pstProvEph
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_InitProvGpsAlm(
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                 *pstProvAlm
)
{
    PS_MEM_SET(pstProvAlm, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetTimeStamp
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPdePublicData
 功能描述  : 获取PDE公共数据指针
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_PDE_PUBLIC_DATA_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_PDE_PUBLIC_DATA_STRU * TAF_XPDS_GetPdePublicData(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPdePubData);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_InitPdePublicDataTaskInit
 功能描述  : Task初始化时初始化PDE流程相关的公共数据
 输入参数  : pstPdePubData - PDE公共数据指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_InitPdePublicDataTaskInit(VOS_VOID)
{
    PS_MEM_SET(TAF_XPDS_GetPdePublicData(), 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_InitPdePublicDataPdeInit
 功能描述  : PDE流程初始化时初始化PDE流程相关的公共数据
             上行Position Determination Data Message中的sess_tag需要保持上一次session结束时的值
 输入参数  : pstPdePubData - PDE公共数据指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_InitPdePublicDataPdeInit(VOS_VOID)
{
    TAF_XPDS_PDE_PUBLIC_DATA_STRU      *pstPdePubData = VOS_NULL_PTR;
    VOS_UINT8                           ucLastSessTag;

    pstPdePubData = TAF_XPDS_GetPdePublicData();

    ucLastSessTag = pstPdePubData->ucSessTagInRsvPdMsgHeader;

    PS_MEM_SET(pstPdePubData, 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));

    pstPdePubData->ucSessTagInRsvPdMsgHeader = ucLastSessTag;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetGpsEphDataFinishedFlag
 功能描述  : 设置GPS EPH数据是否结束的标志
 输入参数  : ucIsFinisehd - 数据是否结束
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsEphDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished = ucIsFinisehd;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetGpsEphDataFinishedFlag
 功能描述  : 获取GPS EPH数据是否结束的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE  - GPS EPH数据已结束
             VOS_FALSE - GPS EPH数据未结束
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetGpsEphDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SetGpsAlmDataFinishedFlag
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsAlmDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished = ucIsFinisehd;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetGpsAlmDataFinishedFlag
 功能描述  : 获取GPS ALM数据是否结束的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE  - GPS ALM数据已结束
             VOS_FALSE - GPS ALM数据未结束
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetGpsAlmDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SetPdeSessionStatus
 功能描述  : 获取PDE session状态
 输入参数  : enPdeSessionStatus - PDE session状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeSessionStatus(
    TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8                  enPdeSessionStatus
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus) = enPdeSessionStatus;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPdeSessionStatus
 功能描述  : 获取PDE session状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 - PDE session状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 TAF_XPDS_GetPdeSessionStatus(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SetPdeSessionTriggerType
 功能描述  : 设置PDE session触发类型
 输入参数  : enPdeSessionTriggerType - PDE session触发类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeSessionTriggerType(
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8            enPdeSessionTriggerType
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType) = enPdeSessionTriggerType;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPdeSessionTriggerType
 功能描述  : 获取PDE session触发类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 - PDE session触发类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 TAF_XPDS_GetPdeSessionTriggerType(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_SetSessTagInRsvPdMsgHeader
 功能描述  : 设置反向PDE Position Determination Data Message中的sess_tag值
 输入参数  : ucSessTag - sess_tag值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetSessTagInRsvPdMsgHeader(VOS_UINT8 ucSessTag)
{
    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = ucSessTag;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetSessTagInRsvPdMsgHeader
 功能描述  : 获取反向PDE Position Determination Data Message中的sess_tag值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 - sess_tag值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetSessTagInRsvPdMsgHeader(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader);
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader
 功能描述  : 增加PDE Position Determination Data Message中的sess_tag值
             每次加1，如果超过32，从0开始
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月28日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader(VOS_VOID)
{
    VOS_UINT8                           ucLastSessTag;

    ucLastSessTag = TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader;

    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = (ucLastSessTag + 1) % 32;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPrmTimerLimitLen
 功能描述  : CAGPS 计算MS回复PRM信息的定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetPrmTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPsuRangeMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPilotPhaseTimerLimitLen
 功能描述  : CAGPS 计算MS回复PILOT PHASE信息的定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetPilotPhaseTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPilotPhaseMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetGpsClientId
 功能描述  : 获得GPS通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetGpsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usGpsClientId;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetApClientId
 功能描述  : 获得AP通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetApClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usApClientId;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetUtsClientId
 功能描述  : 获得UTS通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetUtsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usUtsClientId;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetGpsClientId
 功能描述  : 设置GPS通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usGpsClientId = usClientId;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetApClientId
 功能描述  : 设置AP通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetApClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usApClientId = usClientId;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetUtsClientId
 功能描述  : 设置UTS通道使用的ClientId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetUtsClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usUtsClientId = usClientId;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetMpcCtxAddr
 功能描述  : 获取MPC相关的全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XPDS_MPC_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月14日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_MPC_CTX_STRU* TAF_XPDS_GetMpcCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stMpcCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CAGPS_UPLINK_CTX_STRU
 功能描述  : 获取USER PLANE相关的全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XPDS_MPC_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_CAGPS_UPLINK_CTX_STRU* TAF_XPDS_GetUpLinkCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stUplinkCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetOmTestFlag
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestFlag(VOS_UINT8 ucIsOmTestMode)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode = ucIsOmTestMode;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetOmTestFlag
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetOmTestFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetOmFixRslt
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmFixRslt(VOS_UINT8 enFixRslt)
{
    TAF_XPDS_GetAgpsCfg()->enOmFixRslt = enFixRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetOmFixRslt
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 TAF_XPDS_GetOmFixRslt(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->enOmFixRslt);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetOmTestAbortFlag
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestAbortFlag(VOS_UINT8 isAborted)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted = isAborted;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetOmTestAbortFlag
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetOmTestAbortFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SetOmTestPdeProcRslt
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestPdeProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPdeProcRslt
)
{
    TAF_XPDS_GetAgpsCfg()->enOmTestPdeProcRslt = enPdeProcRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetOmTestPdeProcRslt
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
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

