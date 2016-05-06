/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccCtx.c
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年06月27日
  功能描述   : XccCtx，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : Y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXccCtx.h"
#include "PsCommonDef.h"
#include "CnasXccFsmMoCallingTbl.h"
#include "CnasXccFsmMtCallingTbl.h"
#include "CnasXsdMntn.h"
#include "CnasXccFsmMainTbl.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"

#include "CnasXccProcNvim.h"
#include "NasMntn.h"

#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* XCC CTX,用于保存MMC状态机,描述表 */
CNAS_XCC_CTX_STRU                       g_stCnasXccCtx;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCtxAddr
 功能描述  : 获取当前XCC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前XCC的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_CTX_STRU* CNAS_XCC_GetCtxAddr(VOS_VOID)
{
    return &(g_stCnasXccCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : ucIndex -- 状态机实例索引
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_FSM_STACK_STRU* CNAS_XCC_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_XCC_GetCtxAddr()->pstCurFsmEntity->stFsmStack);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCurFsmAddr
 功能描述  : 获取当前状态机地址
 输入参数  : ucIndex -- 状态机实例索引
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_FSM_CTX_STRU* CNAS_XCC_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_XCC_GetCtxAddr()->pstCurFsmEntity->stCurFsm);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月04日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetFsmTopState(VOS_VOID)
{
    return (CNAS_XCC_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetFsmConnectId
 功能描述  : 获取状态机顶层的connect id状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层connect id状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月04日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetFsmConnectId(VOS_VOID)
{
    return (CNAS_XCC_GetCurFsmAddr()->ucConnectId);
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_GetMainCtrlCtx
 功能描述  : 获取main control上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前main control上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月10日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_MAIN_CTRL_CTX_STRU* CNAS_XCC_GetMainCtrlCtx(VOS_VOID)
{
    return &(CNAS_XCC_GetCtxAddr()->stMainCtrlCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitEmergencyCallCtrlCtx
 功能描述  : 初始化emergency ctrl 上下文
 输入参数  : pstEmcCtrl -- emergency call ctrl ctx
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitEmergencyCallCtrlCtx(
    CNAS_XCC_EMERGENCY_CALL_CTRL_STRU  *pstEmcCtrl
)
{
    pstEmcCtrl->ucWaitFlashMsgRspFlg    = VOS_FALSE;
    pstEmcCtrl->ucFlashMsgSeqNum        = 0;
    pstEmcCtrl->ucEmcCallId             = CNAS_XCC_INVAILD_CALL_ID;
    pstEmcCtrl->ucMtVoiceCallId         = CNAS_XCC_INVAILD_CALL_ID;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_InitMainCtrlCtx
 功能描述  : 初始化main control 上下文
 输入参数  : pstMainCtrlCtx -- main control上下文索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月10日
   作    者   : y00245242
   修改内容   : 新生成函数

 2.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : CDMA 1X项目迭代5修改

 3.日    期   : 2015年1月6日
   作    者   : y00245242
   修改内容   : NDSS ORIG功能增加

 4.日    期   : 2015年11月06日
   作    者   : w00176964
   修改内容   : Modify for CDMA DMT Stability Optimize

*****************************************************************************/
VOS_VOID CNAS_XCC_InitMainCtrlCtx(
    CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrlCtx
)
{
    VOS_UINT32                          i;

    /* 上电时无动态内存分配,可以直接清零 */
    /* 关机或power save时可能存在缓存队列中未释放内存的指针,需要释放内存,避免内存泄漏 */
    if ((CNAS_XCC_INIT_TYPE_POWER_DOWN == enInitType)
     || (CNAS_XCC_INIT_TYPE_POWER_SAVE == enInitType))
    {
        for (i = 0; i < (VOS_UINT32)pstMainCtrlCtx->stBufferMsgQueue.ucMsgNum; i++)
        {
            if (VOS_NULL_PTR != pstMainCtrlCtx->stBufferMsgQueue.pastBufferMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstMainCtrlCtx->stBufferMsgQueue.pastBufferMsg[i]);
                pstMainCtrlCtx->stBufferMsgQueue.pastBufferMsg[i] = VOS_NULL_PTR;
            }
        }

        pstMainCtrlCtx->stBufferMsgQueue.ucMsgNum = 0;
    }

    NAS_MEM_SET_S(pstMainCtrlCtx,
                  sizeof(CNAS_XCC_MAIN_CTRL_CTX_STRU),
                  0,
                  sizeof(CNAS_XCC_MAIN_CTRL_CTX_STRU));

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstMainCtrlCtx->stEmcCallCtrl));
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitCallNvimCfg
 功能描述  : 初始化CallNvimCfg
 输入参数  : CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月17日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_InitCallNvimCfg(
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg
)
{
    NAS_MEM_SET_S(pstCallNvimCfg, sizeof(CNAS_XCC_CALL_NVIM_CFG_STRU), 0, sizeof(CNAS_XCC_CALL_NVIM_CFG_STRU));

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_Init1xPagingRspSoCfg
 功能描述  : 初始化1x paging rsp带so的配置项
 输入参数  : CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU *pstPagingRspSoCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_Init1xPagingRspSoCfg(
    CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU *pstPagingRspSoCfg
)
{
    NAS_MEM_SET_S(pstPagingRspSoCfg, sizeof(CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU), 0, sizeof(CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ReadNvimInfo
 功能描述  : 读取NV控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1. 日    期   : 2015年6月15日
   作    者   : c00299063
   修改内容   : 新增函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ReadNvimInfo()
{
    CNAS_XCC_ReadCallCfgNvim();

    CNAS_XCC_Read1xPagingRspSoCfg();

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    CNAS_XCC_ReadVoiceEncryptCapCfgPara();
#endif
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitCtx
 功能描述  : XCC 上下文全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :


 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数
 2.日    期   : 2015年11月06日
   作    者   : w00176964
   修改内容   : Modify for CDMA DMT Stability Optimize

*****************************************************************************/
VOS_VOID CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_ENUM_UINT8 enInitType)
{
    VOS_UINT32                          i;
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity = VOS_NULL_PTR;

    for ( i = 0 ; i < CNAS_XCC_MAX_FSM_ENTITY_NUM ; i++ )
    {
        /* 获取每个状态机 */
        pstFsmEntity = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[i]);

        /* 状态机上下文初始化 */
        CNAS_XCC_InitCurrFsmCtx(enInitType, &(pstFsmEntity->stCurFsm));

        /* 状态机栈数组初始化   */
        CNAS_XCC_InitFsmStackCtx(&(pstFsmEntity->stFsmStack));

        /* call info实体初始化   */
        CNAS_XCC_InitCallInfoCtx(&(pstFsmEntity->stCallInfoCtx), CNAS_XCC_INIT_CALLINFO_SCENE_POWER_ON);
    }

    CNAS_XCC_GetCtxAddr()->pstCurFsmEntity = VOS_NULL_PTR;

    /* CNAS XCC缓存消息队列初始化 */
    CNAS_XCC_InitInternalBuffer(&(CNAS_XCC_GetCtxAddr()->stIntMsgQueue));

    CNAS_XCC_InitMainCtrlCtx(enInitType, &(CNAS_XCC_GetCtxAddr()->stMainCtrlCtx));

    CNAS_XCC_ClearAllOrigCallOrderIndex();

    CNAS_XCC_INIT_SRID_INFO();

    CNAS_XCC_InitCallNvimCfg(&(CNAS_XCC_GetCtxAddr()->stCallNvimCfg));

    CNAS_XCC_Init1xPagingRspSoCfg(&(CNAS_XCC_GetCtxAddr()->stPagingRspSoCfg));

    CNAS_XCC_ReadNvimInfo();
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_LoadSubFsm
 功能描述  : 加载L2状态机的信息
 输入参数  : enFsmId - L2状态机ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月04日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XCC_LoadSubFsm(
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        /* 主叫状态机 */
        case CNAS_XCC_FSM_MO_CALLING :
            pstCurFsm->ulState    = CNAS_XCC_MO_CALLING_STA_INIT;
            pstCurFsm->pstFsmDesc = CNAS_XCC_GetMoCallingFsmDescAddr();
            break;

        /* 被叫状态机 */
        case CNAS_XCC_FSM_MT_CALLING :
            pstCurFsm->ulState    = CNAS_XCC_MT_CALLING_STA_INIT;
            pstCurFsm->pstFsmDesc = CNAS_XCC_GetMtCallingFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : pstFsmStack -- 状态机栈
             pstNewFsm   -- 需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_PushFsm(
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack,
    CNAS_XCC_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* 入参指针检查 */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC,
                       "CNAS_XCC_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* 栈深度检查 */
    if (pstFsmStack->usStackDepth >= CNAS_XCC_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC,
                       "CNAS_XCC_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push当前状态机上下文入栈 */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    NAS_MEM_CPY_S(pstCurFsm, sizeof(CNAS_XCC_FSM_CTX_STRU), pstNewFsm, sizeof(CNAS_XCC_FSM_CTX_STRU));

    /* 栈深度增加 */
    pstFsmStack->usStackDepth++;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_PopFsm(VOS_VOID)
{
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack = CNAS_XCC_GetFsmStackAddr();
    pstCurFsm   = CNAS_XCC_GetCurFsmAddr();

    /* 检查栈空间是否为空 */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_PopFsm: FSM Stack is empty");

        return;
    }

    /* 状态机栈深度减少 */
    pstFsmStack->usStackDepth--;

    /* 设置当前状态机 */
    NAS_MEM_CPY_S(pstCurFsm,
                  sizeof(CNAS_XCC_FSM_CTX_STRU),
                  &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
                  sizeof(CNAS_XCC_FSM_CTX_STRU));

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitFsmL2
 功能描述  : XCC启动一个L2的状态机。启动流程的同时启动状态以及保护定时器
              该函数会进行压栈操作,如果不需要进行协议栈压栈, 必须保证退出前流程
 输入参数  : enFsmId -- L2状态机ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitFsmL2(
    CNAS_XCC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_XCC_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XCC, CNAS_XCC_GetCurrFsmId(), CNAS_XCC_GetFsmTopState(), CNAS_XCC_GetFsmConnectId());

    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId     = CNAS_XCC_GetCurrFsmId();
    ulParentEventType = CNAS_XCC_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    pstFsmStack = CNAS_XCC_GetFsmStackAddr();
    pstCurFsm   = CNAS_XCC_GetCurFsmAddr();
    CNAS_XCC_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId = enFsmId;

    /* 加载L2状态机 */
    CNAS_XCC_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XCC, CNAS_XCC_GetCurrFsmId(), CNAS_XCC_GetFsmTopState(), CNAS_XCC_GetFsmConnectId());

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_QuitFsmL2(VOS_VOID)
{

    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm = CNAS_XCC_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XCC, CNAS_XCC_GetCurrFsmId(), CNAS_XCC_GetFsmTopState(), CNAS_XCC_GetFsmConnectId());

    /* 状态机出栈操作 */
    CNAS_XCC_PopFsm();

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XCC, CNAS_XCC_GetCurrFsmId(), CNAS_XCC_GetFsmTopState(), CNAS_XCC_GetFsmConnectId());

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : ucIndex -- 状态机实例索引
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XCC_GetFsmStackDepth(VOS_VOID)
{
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XCC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
函 数 名  : CNAS_XCC_GetCurrFsmId
功能描述  : 获取当前状态机标识
输入参数  : 无
输出参数  : 无
返 回 值  : CNAS_XCC_FSM_ID_ENUM_UINT32 -- 返回当前状态机ID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2014年09月03日
作    者   : w00242748
修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_FSM_ID_ENUM_UINT32 CNAS_XCC_GetCurrFsmId(VOS_VOID)
{
    return (CNAS_XCC_GetCtxAddr()->pstCurFsmEntity->stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月13日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XCC_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_XCC_GetCurFsmAddr()->pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetBufferedMsgNum
 功能描述  : 获取当前缓存的消息数目
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT8 -- 返回缓存的消息数目
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetBufferedMsgNum(VOS_VOID)
{
    return (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetNextBufferMsg
 功能描述  : 获取下一个缓存消息
 输入参数  : 无

 输出参数  :
 返 回 值  : VOS_UINT8* -- 缓存消息地址
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_UINT8 *CNAS_XCC_GetNextBufferMsg(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    return (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[0]);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FreeCurrentBufferMsg
 功能描述  : free当前首个缓存的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整

*****************************************************************************/
VOS_VOID CNAS_XCC_FreeCurrentBufferMsg(VOS_VOID)
{
    VOS_UINT8                           ucMsgNum;

    ucMsgNum = CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum;

    /* 异常保护 */
    if (0 == ucMsgNum)
    {
        return;
    }

    ucMsgNum--;

    /* 更新缓存消息数目 */
    CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum = ucMsgNum;

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    if (VOS_NULL_PTR != (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[0]))
    {
        PS_MEM_FREE(UEPS_PID_XCC, (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[0]));

        (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[0]) = VOS_NULL_PTR;
    }

    if (0 < ucMsgNum)
    {
        NAS_MEM_MOVE_S(&(CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[0]),
                       CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM * sizeof(VOS_UINT8 *),
                       &(CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[1]),
                       (ucMsgNum) * sizeof(VOS_UINT8 *));
    }

    (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucMsgNum]) = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetSpecifiedIndexBufferMsg
 功能描述  : 获取指定索引的用户请求信息
 输入参数  : ucIndex -- 缓存消息索引

 输出参数  : 无
 返 回 值  : VOS_UINT8* -- 缓存消息地址
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整

*****************************************************************************/
VOS_UINT8  *CNAS_XCC_GetSpecifiedIndexBufferMsg(
    VOS_UINT8                           ucIndex
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    return (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FreeSpecifiedIndexBufferMsg
 功能描述  : free指定的用户请求消息
 输入参数  : ucIndex -- 缓存消息索引

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整

*****************************************************************************/
VOS_VOID CNAS_XCC_FreeSpecifiedIndexBufferMsg(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucMsgNum;

    ucMsgNum = CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum;

    if (0 == ucMsgNum)
    {
        return;
    }

    ucMsgNum--;

    /* 更新缓存消息数目 */
    CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum = ucMsgNum;

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    if (VOS_NULL_PTR != (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]))
    {
        PS_MEM_FREE(UEPS_PID_XCC, (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]));

        (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]) = VOS_NULL_PTR;
    }

    if (0 < ucMsgNum)
    {
        NAS_MEM_MOVE_S(&(CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]),
                       (CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM - ucIndex) * sizeof(VOS_UINT8 *),
                       &(CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex + 1]),
                       (ucMsgNum - ucIndex) * sizeof(VOS_UINT8 *));
    }

    (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucMsgNum]) = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FreeAllBufferMsgInQueue
 功能描述  : free所有用户请求消息
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_VOID CNAS_XCC_FreeAllBufferMsgInQueue(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulMsgNum;

    ulMsgNum = (CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum);

    for (ulIndex = 0; ulIndex < ulMsgNum; ulIndex++)
    {
        CNAS_XCC_FreeSpecifiedIndexBufferMsg((VOS_UINT8)ulIndex);
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_BufferMsgInQueue
 功能描述  : 缓存用户请求信息，待后续处理
 输入参数  : ulEventType -- 入口消息类型
             pstMsg      -- 入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年9月16日
     作    者   : y00245242
     修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整

*****************************************************************************/
VOS_VOID CNAS_XCC_BufferMsgInQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    MSG_HEADER_STRU                     *pstMsgHdr;

    pstMsgHdr = (MSG_HEADER_STRU *)pstMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, end */

    ucIndex = CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum;

    if (ucIndex < CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        if (CNAS_XCC_MAX_MSG_BUFFER_LEN < pstMsg->ulLength)
        {
            CNAS_ERROR_LOG( UEPS_PID_XCC, "CNAS_XCC_BufferMsgInQueue: message is too length!");
            return;
        }

        CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]
                = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XCC, pstMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex])
        {
            return;
        }

        NAS_MEM_CPY_S((CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.pastBufferMsg[ucIndex]),
                       pstMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH,
                       pstMsgHdr,
                       pstMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

        CNAS_XCC_GetMainCtrlCtx()->stBufferMsgQueue.ucMsgNum++;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetIntCacheMsgAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS XCC缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_INT_MSG_QUEUE_STRU* CNAS_XCC_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_XCC_GetCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitInternalBuffer
 功能描述  : 初始化内部队列
 输入参数  : pstIntMsgQueue -- 内部队列地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitInternalBuffer(
    CNAS_XCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                          i;

    for (i = 0; i < CNAS_XCC_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_PutMsgInIntMsgQueue
 功能描述  : 保存当前需要处理的缓存
 输入参数  : pstMsg -- 消息地址
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月05日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    if (CNAS_XCC_MAX_INT_MSG_QUEUE_NUM <= CNAS_XCC_GetIntMsgNum())
    {
        /* 释放内部消息 */
        PS_MEM_FREE(UEPS_PID_XCC, pstMsg);

        CNAS_ERROR_LOG( UEPS_PID_XCC, "CNAS_XCC_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    ucIntMsgNum = CNAS_XCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* 保存当前信息 */
    CNAS_XCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    CNAS_XCC_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetNextIntMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  :

 返 回 值  : pstIntMSg -- 返回下一条内部消息

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 *CNAS_XCC_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_XCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* 获取下一个缓存的消息消息 */
        pstIntMsg = CNAS_XCC_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* 内部消息数目减少一个 */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* 前移内部消息 */
            NAS_MEM_MOVE_S(&(CNAS_XCC_GetIntMsgQueueAddr()->pastIntMsg[0]),
                           CNAS_XCC_MAX_INT_MSG_QUEUE_NUM * sizeof(VOS_UINT8 *),
                           &(CNAS_XCC_GetIntMsgQueueAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* 对消息队列中尾部的消息清为空指针 */
        CNAS_XCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_XCC_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetIntMsgNum
 功能描述  : 获取当前XCC内部消息个数
 输入参数  : 无
 输出参数  :
 返 回 值  : 当前存在的缓存个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetIntMsgNum(VOS_VOID)
{
    CNAS_XCC_INT_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_XCC_GetIntMsgQueueAddr();

    return pstMsgQueue->ucIntMsgNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitFsmCtx_L1Main(VOS_VOID)
{

    /* 暂时没有需要初始化的全局变量，后续有变量需初始化再在此添加 */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitFsmCtx_MoCalling
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitFsmCtx_MoCalling(VOS_VOID)
{
    /* 暂时没有需要初始化的全局变量，后续有变量需初始化再在此添加 */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitFsmCtx_MtCalling
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_InitFsmCtx_MtCalling(VOS_VOID)
{
    /* 暂时没有需要初始化的全局变量，后续有变量需初始化再在此添加 */
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitCurrFsmCtx
 功能描述  : 初始化当前状态机
 输入参数  : ucIndex -- 状态机实例索引
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月03日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XCC_InitCurrFsmCtx(
    CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
    CNAS_XCC_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    /* 当前的状态机数组初始化 */
    pstCurrFsmCtx->enFsmId                  = CNAS_XCC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               = CNAS_XCC_GetMainFsmDescAddr();

    /* 只有关机状态置成POWER_OFF，开机和挂起状态都置成IDLE */
    if (CNAS_XCC_INIT_TYPE_POWER_DOWN == enInitType)
    {
        pstCurrFsmCtx->ulState              = CNAS_XCC_L1_STA_POWER_OFF;
    }
    else
    {
        pstCurrFsmCtx->ulState              = CNAS_XCC_L1_STA_IDLE;
    }

    pstCurrFsmCtx->stEntryMsg.ulEventType   = 0;
    pstCurrFsmCtx->enParentFsmId            = CNAS_XCC_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        = 0;

    pstCurrFsmCtx->ucConnectId              = CNAS_XCC_INVAILD_CON_ID;

    NAS_MEM_SET_S(pstCurrFsmCtx->ucReserved, sizeof(pstCurrFsmCtx->ucReserved), 0x00, sizeof(pstCurrFsmCtx->ucReserved));

    NAS_MEM_SET_S(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
                  CNAS_XCC_MAX_MSG_BUFFER_LEN,
                  0x00,
                  CNAS_XCC_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : 无
 输出参数  : pstFsmStack:状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  CNAS_XCC_InitFsmStackCtx(
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;

    for ( i = 0 ; i < CNAS_XCC_MAX_FSM_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_XCC_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_XCC_L1_STA_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitCallInfoCtx
 功能描述  : 初始化呼叫信息上下文
 输入参数  : 无
 输出参数  : pstFsmStack:状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数

 2.日    期   : 2015年7月20日
   作    者   : h00313353
   修改内容   : 迭代17 紧急呼
 3.日    期   : 2015年7月27日
   作    者   : l00324781
   修改内容   : Iter16 修改
 4.日    期   : 2015年12月24日
   作    者   : y00245242
   修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_VOID  CNAS_XCC_InitCallInfoCtx(
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo,
    CNAS_XCC_INIT_CALLINFO_SCENE_ENUM_UINT8                 enScene
)
{
    VOS_UINT8                                               uc1XCallExistCount;

    uc1XCallExistCount                                      = CNAS_CCB_Get1XCallExistCount();

    /* 初始化呼叫类型时开机或者ENDED时，才需要将SO/CONNECT ID/CONNECT REF信息清除 */
    if ( (CNAS_XCC_INIT_CALLINFO_SCENE_POWER_ON == enScene)
      || (CNAS_XCC_INIT_CALLINFO_SCENE_ENDED == enScene) )
    {
        pstCallInfo->ucIsNullCc           = VOS_FALSE;
        pstCallInfo->ucIsEntityActive     = VOS_FALSE;
        pstCallInfo->ucConnectId          = CNAS_XCC_INVAILD_CON_ID;
        pstCallInfo->ucConRef             = CNAS_XCC_INVALID_CON_REF;
        pstCallInfo->enInitSo             = CAS_CNAS_1X_SO_BUTT;
        pstCallInfo->enCurrentSo          = CAS_CNAS_1X_SO_BUTT;
    }

    if (CNAS_XCC_INIT_CALLINFO_SCENE_ENDED == enScene)
    {
        if (uc1XCallExistCount > 0)
        {
            uc1XCallExistCount--;
        }

        CNAS_CCB_Set1XCallExistCount(uc1XCallExistCount);
    }

    /* ENDING场景只需要将下面部分信息初始化即可 */
    pstCallInfo->bitOpCallingPartyNum     = VOS_FALSE;
    pstCallInfo->bitOpCallingPartySubAddr = VOS_FALSE;
    pstCallInfo->bitOpCalledPartySubAddr  = VOS_FALSE;
    pstCallInfo->bitOpQosInfo             = VOS_FALSE;
    pstCallInfo->bitOpSpare               = 0;


    pstCallInfo->ucCallId                 = CNAS_XCC_INVAILD_CALL_ID;
    pstCallInfo->ucIsMoCall               = VOS_FALSE;

    pstCallInfo->ucIsByPassAlertAns       = VOS_FALSE;
    /* 删除ucIsStartDtmfAckWait,ucIsStopDtmfAckWait等无用元素 */
    pstCallInfo->ucIsBurstDtmfAckWait     = VOS_FALSE;
    pstCallInfo->ucIsSendFlashAckWait     = VOS_FALSE;
    pstCallInfo->ucIsCodecOpen            = VOS_FALSE;
    pstCallInfo->ucIsSoNegCmplt           = VOS_FALSE;
    pstCallInfo->ucMsgSeqNum              = 0;
    pstCallInfo->ucQosInfoLen             = 0;
    NAS_MEM_SET_S(pstCallInfo->aucQosInfo, sizeof(pstCallInfo->aucQosInfo), 0x00, sizeof(pstCallInfo->aucQosInfo));

    NAS_MEM_SET_S(&(pstCallInfo->stCalledPartyNum), sizeof(pstCallInfo->stCalledPartyNum), 0x00, sizeof(pstCallInfo->stCalledPartyNum));
    NAS_MEM_SET_S(&(pstCallInfo->stCallingPartyNum), sizeof(pstCallInfo->stCallingPartyNum), 0x00, sizeof(pstCallInfo->stCallingPartyNum));
    NAS_MEM_SET_S(&(pstCallInfo->stCallingPartySubAddr), sizeof(pstCallInfo->stCallingPartySubAddr), 0x00, sizeof(pstCallInfo->stCallingPartySubAddr));
    NAS_MEM_SET_S(&(pstCallInfo->stCalledPartySubAddr), sizeof(pstCallInfo->stCalledPartySubAddr), 0x00, sizeof(pstCallInfo->stCalledPartySubAddr));

    pstCallInfo->ucReOrigCount        = 0;
    pstCallInfo->ucIsL2ErrReOrig      = VOS_FALSE;
    pstCallInfo->ucIsEmergencyCall    = VOS_FALSE;
    pstCallInfo->ucIsDataReady        = VOS_FALSE;
    pstCallInfo->ucIsReOrigReason     = VOS_FALSE;
    pstCallInfo->ucIsDormDataCall     = VOS_FALSE;

    NAS_MEM_SET_S(&(pstCallInfo->stAWIorEAWIInfoRecoBuffer), sizeof(pstCallInfo->stAWIorEAWIInfoRecoBuffer), 0x00, sizeof(pstCallInfo->stAWIorEAWIInfoRecoBuffer));
    pstCallInfo->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid = VOS_FALSE;

    pstCallInfo->ucIsDataSrvConn      = VOS_FALSE;
    pstCallInfo->ucSrId               = CNAS_XCC_INVALID_SR_ID;

    pstCallInfo->ulIsPrevHrpdFlg      = VOS_FALSE;

    pstCallInfo->enReqPrivacyMode     = XCALL_XCC_PRIVACY_MODE_BUTT;
    pstCallInfo->enNegPrivacyMode     = XCALL_XCC_PRIVACY_MODE_BUTT;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_InitIntMsgQueue
 功能描述  : 清除内部缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XCC_InitIntMsgQueue(
    CNAS_XCC_INT_MSG_QUEUE_STRU      *pstIntMsgQueue
)
{
    pstIntMsgQueue->ucIntMsgNum = 0;

    NAS_MEM_SET_S(pstIntMsgQueue->pastIntMsg,
                  CNAS_XCC_MAX_INT_MSG_QUEUE_NUM,
                  0x00,
                  CNAS_XCC_MAX_INT_MSG_QUEUE_NUM);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SetCurrFsmState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  CNAS_XCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = CNAS_XCC_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的当前状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XCC, pstCurFsm->enFsmId, ulCurrState, pstCurFsm->ucConnectId);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCurrFsmEntityCallInfoCtx
 功能描述  : 获取当前状态机实体中的呼叫相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XCC_CALL_INFO_CTX_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_XCC_CALL_INFO_CTX_STRU*  CNAS_XCC_GetCurrFsmEntityCallInfoCtx( VOS_VOID )
{
    return &(g_stCnasXccCtx.pstCurFsmEntity->stCallInfoCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCurrFsmMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月13日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XCC_ENTRY_MSG_STRU* CNAS_XCC_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(g_stCnasXccCtx.pstCurFsmEntity->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetInitSo
 功能描述  : 获取初始化的SO
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月13日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetInitSo(VOS_VOID)
{
    return (g_stCnasXccCtx.pstCurFsmEntity->stCallInfoCtx.enInitSo);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SetInitSo
 功能描述  : 设置初始化的SO
 输入参数  : enSo:CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SetInitSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo)
{
    g_stCnasXccCtx.pstCurFsmEntity->stCallInfoCtx.enInitSo = enSo;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetCurrentSo
 功能描述  : 获取当前的SO
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月13日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetCurrentSo(VOS_VOID)
{
    return (g_stCnasXccCtx.pstCurFsmEntity->stCallInfoCtx.enCurrentSo);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SetCurrentSo
 功能描述  : 设置当前的SO
 输入参数  : enSo:CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SetCurrentSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo)
{
    g_stCnasXccCtx.pstCurFsmEntity->stCallInfoCtx.enCurrentSo = enSo;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014-09-13
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ENTRY_MSG_STRU            *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理NAS_MMC入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_XCC_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        CNAS_WARNING_LOG( UEPS_PID_XCC, "CNAS_XCC_SaveCurEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, begin */
    if (ulLen > CNAS_XCC_MAX_MSG_BUFFER_LEN)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_SaveCurEntryMsg:beyond the Size!");

        ulLen = CNAS_XCC_MAX_MSG_BUFFER_LEN;
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, end */

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    NAS_MEM_CPY_S( pstEntryMsg->aucMsgBuffer, CNAS_XCC_MAX_MSG_BUFFER_LEN, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetSeqNum
 功能描述  : 获取seqnum
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月13日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_AllocSeqNum(VOS_VOID)
{
    VOS_UINT8                           ucSeqNum;

    ucSeqNum = g_stCnasXccCtx.stMainCtrlCtx.ucSeqNum;

    g_stCnasXccCtx.stMainCtrlCtx.ucSeqNum = (g_stCnasXccCtx.stMainCtrlCtx.ucSeqNum + 1)%CNAS_XCC_MAX_UINT8;

    return ucSeqNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_BufferAWIOrEAWIInfoReco
 功能描述  : 缓存AWI/EAWI的Info record
 输入参数  : pstDschDataInd
             pstCallInfoCtx
 输出参数  : 无
 返 回 值  : VOS_OK      -- 处理成功
             VOS_ERR     -- 处理失败
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月12日
   作    者   : L00256032
   修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_BufferAWIOrEAWIInfoReco(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
)
{
    CNAS_XCC_AWIM_STRU                 *pstAWIM;
    CNAS_XCC_EAWIM_STRU                *pstEAWIM;

    if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
    {
        pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
        if (VOS_NULL_PTR == pstAWIM)
        {
            return VOS_ERR;
        }

        if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
        {
            PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
            return VOS_ERR;
        }

        /* 缓存info record */
        if (0 != pstAWIM->ucNumInfoRecs)
        {
            pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid = VOS_TRUE;
            pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.enMsgType       = CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG;
            NAS_MEM_CPY_S(&(pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.u.stAWIM),
                          sizeof(CNAS_XCC_AWIM_STRU),
                          pstAWIM,
                          sizeof(CNAS_XCC_AWIM_STRU));
        }

        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
    }
    else
    {
        pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
        if (VOS_NULL_PTR == pstEAWIM)
        {
            return VOS_ERR;
        }

        if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
        {
            PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
            return VOS_ERR;
        }

        /* 缓存info record */
        if (0 != pstEAWIM->ucNumInfoRecs)
        {
            pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid = VOS_TRUE;
            pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.enMsgType       = CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG;
            NAS_MEM_CPY_S(&(pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.u.stEAWIM),
                          sizeof(CNAS_XCC_EAWIM_STRU),
                          pstEAWIM,
                          sizeof(CNAS_XCC_EAWIM_STRU));
        }

        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer
 功能描述  : 清空AWI/EAWI的Info record缓存
 输入参数  : ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月12日
   作    者   : L00256032
   修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_VOID CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer(VOS_VOID)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    if (VOS_TRUE == pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid)
    {
        NAS_MEM_SET_S(&(pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer),
                      sizeof(CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU),
                      0,
                      sizeof(CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU));

        pstCallInfoCtx->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SetWaitEmcFlashMsgRspFlg
 功能描述  : 设置等待紧急呼叫flash消息回复标记
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SetWaitEmcFlashMsgRspFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    pstMainCtrl->stEmcCallCtrl.ucWaitFlashMsgRspFlg = ucFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetWaitEmcFlashMsgRspFlg
 功能描述  : 获取等待紧急呼叫flash消息回复标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetWaitEmcFlashMsgRspFlg(VOS_VOID)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    return pstMainCtrl->stEmcCallCtrl.ucWaitFlashMsgRspFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SaveEmcCallId
 功能描述  : 保存紧急呼叫的CALL ID
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SaveEmcCallId(
    VOS_UINT8                           ucCallId
)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    pstMainCtrl->stEmcCallCtrl.ucEmcCallId = ucCallId;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetEmcCallId
 功能描述  : 获取紧急呼叫的CALL ID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetEmcCallId(VOS_VOID)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    return pstMainCtrl->stEmcCallCtrl.ucEmcCallId;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SaveMtVoiceCallId
 功能描述  : 保存MT被叫的CALL ID
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SaveMtVoiceCallId(
    VOS_UINT8                           ucCallId
)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    pstMainCtrl->stEmcCallCtrl.ucMtVoiceCallId = ucCallId;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetMtVoiceCallId
 功能描述  : 获取MT被叫的CALL ID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetMtVoiceCallId(VOS_VOID)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    return pstMainCtrl->stEmcCallCtrl.ucMtVoiceCallId;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_SaveEmcFlashMsgSeqNum
 功能描述  : 保存发送紧急呼叫的flash消息的sequence number
 输入参数  : VOS_UINT8                           ucSeqNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SaveEmcFlashMsgSeqNum(
    VOS_UINT8                           ucSeqNum
)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    pstMainCtrl->stEmcCallCtrl.ucFlashMsgSeqNum = ucSeqNum;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetEmcFlashMsgSeqNum
 功能描述  : 获取发送紧急呼叫的flash消息的sequence number
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetEmcFlashMsgSeqNum(VOS_VOID)
{
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrl = VOS_NULL_PTR;

    pstMainCtrl = CNAS_XCC_GetMainCtrlCtx();

    return pstMainCtrl->stEmcCallCtrl.ucFlashMsgSeqNum;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_AllocSrId
 功能描述  : 分配SR_ID
 输入参数  : enSo           - 使用的SO
             ucConnectId    - 使用的Connect Id
 输出参数  : pucSrId - 分配的SR_ID
 返 回 值  : SR_ID的分配结果,VOS_TRUE:分配成功；VOS_FALSE:分配失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32   CNAS_XCC_AllocSrId(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16      enSo,
    VOS_UINT8                                  *pucSrId,
    VOS_UINT8                                   ucConnectId
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if ((CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K == enSo)
     || (CAS_CNAS_1X_SO_7_PPP_PKT_DATA == enSo))
    {
        if (VOS_FALSE == pstXccCtxAddr->astSridInfo[CNAS_XCC_RESERVED_SR_ID].ucIsUsed)
        {
            *pucSrId = CNAS_XCC_RESERVED_SR_ID;
            pstXccCtxAddr->astSridInfo[CNAS_XCC_RESERVED_SR_ID].ucIsUsed      = VOS_TRUE;
            pstXccCtxAddr->astSridInfo[CNAS_XCC_RESERVED_SR_ID].ucSrid        = *pucSrId;
            pstXccCtxAddr->astSridInfo[CNAS_XCC_RESERVED_SR_ID].enSo          = enSo;
            pstXccCtxAddr->astSridInfo[CNAS_XCC_RESERVED_SR_ID].ucConnectId   = ucConnectId;
            return VOS_TRUE;
        }
    }

    for (i = CNAS_XCC_RESERVED_SR_ID + 1 ; i <= CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_FALSE == pstXccCtxAddr->astSridInfo[i].ucIsUsed)
        {
            *pucSrId = i;
            pstXccCtxAddr->astSridInfo[i].ucIsUsed      = VOS_TRUE;
            pstXccCtxAddr->astSridInfo[i].ucSrid        = *pucSrId;
            pstXccCtxAddr->astSridInfo[i].enSo          = enSo;
            pstXccCtxAddr->astSridInfo[i].ucConnectId   = ucConnectId;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_UpdateSrIdUsed
 功能描述  : 刷新已经使用的SR_ID
 输入参数  : ucSrId       - 已经使用的SR_ID
             enSo         - 当前使用的SO
             ucConnectId  - 当前使用的Connect Id
 输出参数  : 无
 返 回 值  : 设置结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32   CNAS_XCC_UpdateSrIdUsed(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16      enSo,
    VOS_UINT8                                   ucSrId,
    VOS_UINT8                                   ucConnectId
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    /* 异常保护，防止接入层刷新异常的SR ID */
    if (ucSrId > CNAS_XCC_MAX_SRID_NUM)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_UpdateSrIdUsed: Invalid SR_ID: %d",ucSrId);
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 如果之前已经有过分配的SR_ID，需要先清除，然后再重新赋值 */
    for (i = CNAS_XCC_RESERVED_SR_ID; i <= CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if ((VOS_TRUE == pstXccCtxAddr->astSridInfo[i].ucIsUsed)
         && (ucConnectId == pstXccCtxAddr->astSridInfo[i].ucConnectId)
         && (i != ucSrId))
        {
            pstXccCtxAddr->astSridInfo[i].ucIsUsed      = VOS_FALSE;
            pstXccCtxAddr->astSridInfo[i].ucSrid        = CNAS_XCC_INVALID_SR_ID;
            pstXccCtxAddr->astSridInfo[i].enSo          = enSo;
            pstXccCtxAddr->astSridInfo[i].ucConnectId   = CNAS_XCC_INVAILD_CON_ID;
            break;
        }
    }

    /* 重新刷新生成，目前没有做冲突检查，如果有冲突，当前接入层与物理层的映射应该会有问题，因此认为
        这种场景目前不会有 */
    pstXccCtxAddr->astSridInfo[ucSrId].ucIsUsed      = VOS_TRUE;
    pstXccCtxAddr->astSridInfo[ucSrId].ucSrid        = ucSrId;
    pstXccCtxAddr->astSridInfo[ucSrId].enSo          = enSo;
    pstXccCtxAddr->astSridInfo[ucSrId].ucConnectId   = ucConnectId;

    return VOS_TRUE;


}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SetOrigCallOrderIndex
 功能描述  : 设置最后一路呼叫索引
 输入参数  : VOS_UINT8                           ucLatestCallIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SetOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
)
{
    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU             *pstOrigCallIndexOrder = VOS_NULL_PTR;
    VOS_UINT8                                               ucCallNum;

    pstOrigCallIndexOrder = &(CNAS_XCC_GetCtxAddr()->stOrigCallIndexOrder);

    ucCallNum = pstOrigCallIndexOrder->ucCallNum;

    pstOrigCallIndexOrder->aucCallIndex[ucCallNum] = ucCallIndex;

    pstOrigCallIndexOrder->ucCallNum++;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ClearSpecificedOrigCallIndex
 功能描述  : 设置最后一路呼叫索引
 输入参数  : VOS_UINT8                           ucCallIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年3月6日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_ClearSpecificedOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
)
{
    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU             *pstOrigCallIndexOrder = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    pstOrigCallIndexOrder = &(CNAS_XCC_GetCtxAddr()->stOrigCallIndexOrder);

    for (i = 0; i < pstOrigCallIndexOrder->ucCallNum; i++)
    {
        if (pstOrigCallIndexOrder->aucCallIndex[i] == ucCallIndex)
        {
            break;
        }
    }

    if (i == pstOrigCallIndexOrder->ucCallNum)
    {
        /* 未找到，返回 */
        return;
    }

    if (i == (pstOrigCallIndexOrder->ucCallNum - 1))
    {
        pstOrigCallIndexOrder->aucCallIndex[i] = CNAS_XCC_INVAILD_CALL_INDEX;
    }
    else
    {
        NAS_MEM_MOVE_S(&pstOrigCallIndexOrder->aucCallIndex[i],
                       sizeof(UINT8) * (CNAS_XCC_MAX_FSM_ENTITY_NUM - i),
                       &pstOrigCallIndexOrder->aucCallIndex[i+1],
                       sizeof(UINT8) * (pstOrigCallIndexOrder->ucCallNum - i - 1));

        pstOrigCallIndexOrder->aucCallIndex[pstOrigCallIndexOrder->ucCallNum - 1] = CNAS_XCC_INVAILD_CALL_INDEX;
    }

    pstOrigCallIndexOrder->ucCallNum--;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ClearAllOrigCallOrderIndex
 功能描述  : 清除所有呼叫顺序索引
 输入参数  : VOS_UINT8                           ucCallIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_ClearAllOrigCallOrderIndex(VOS_VOID)
{
    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU             *pstOrigCallIndexOrder = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    pstOrigCallIndexOrder = &(CNAS_XCC_GetCtxAddr()->stOrigCallIndexOrder);

    NAS_MEM_SET_S(pstOrigCallIndexOrder, sizeof(CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU), 0, sizeof(CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU));

    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        pstOrigCallIndexOrder->aucCallIndex[i] = CNAS_XCC_INVAILD_CALL_INDEX;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetLastCallIndex
 功能描述  : 清除所有呼叫顺序索引
 输入参数  : VOS_UINT8                           ucCallIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetLastCallIndex(VOS_VOID)
{
    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU             *pstOrigCallIndexOrder = VOS_NULL_PTR;

    pstOrigCallIndexOrder = &(CNAS_XCC_GetCtxAddr()->stOrigCallIndexOrder);

    if (0 == pstOrigCallIndexOrder->ucCallNum)
    {
        return CNAS_XCC_INVAILD_CALL_INDEX;
    }

    return pstOrigCallIndexOrder->aucCallIndex[pstOrigCallIndexOrder->ucCallNum - 1];
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_INIT_SRID_INFO
 功能描述  : 初始化SR ID相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_INIT_SRID_INFO( VOS_VOID )
{
    NAS_MEM_SET_S(CNAS_XCC_GetCtxAddr()->astSridInfo, sizeof(CNAS_XCC_SRID_INFO_STRU) * (CNAS_XCC_MAX_SRID_NUM + 1), 0, sizeof(CNAS_XCC_SRID_INFO_STRU) * (CNAS_XCC_MAX_SRID_NUM + 1));
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ClearSpecificedSrIdByConnectId
 功能描述  : 根据特定的connect id来清除sr id信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_ClearSpecificedSrIdByConnectId(
    VOS_UINT8                           ucConnectId
)
{
    VOS_UINT32                          i;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    for (i = 1; i <= CNAS_XCC_MAX_SRID_NUM; i++)
    {
        if ((VOS_TRUE == pstXccCtxAddr->astSridInfo[i].ucIsUsed)
         && (ucConnectId == pstXccCtxAddr->astSridInfo[i].ucConnectId))
        {
            pstXccCtxAddr->astSridInfo[i].ucIsUsed      = VOS_FALSE;
            pstXccCtxAddr->astSridInfo[i].ucSrid        = CNAS_XCC_INVALID_SR_ID;
            pstXccCtxAddr->astSridInfo[i].enSo          = CAS_CNAS_1X_SO_BUTT;
            pstXccCtxAddr->astSridInfo[i].ucConnectId   = CNAS_XCC_INVAILD_CON_ID;
            break;
        }
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsExist1xDataOperation
 功能描述  : 获取当前状态机状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月18日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
)
{
    if (MODEM_ID_0 == CNAS_CCB_GetCdmaModeModemId())
    {
        return TAF_APS_IsExist1xDataOperation(enSo);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    else if (MODEM_ID_1 == CNAS_CCB_GetCdmaModeModemId())
    {
        return I1_TAF_APS_IsExist1xDataOperation(enSo);
    }
#if ( 3 == MULTI_MODEM_NUMBER )
    else if (MODEM_ID_2 == CNAS_CCB_GetCdmaModeModemId())
    {
        return I2_TAF_APS_IsExist1xDataOperation(enSo);
    }
#endif
#endif
    else
    {
        NAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_IsExist1xDataOperation invalid modemId!\r\n");
    }

    return VOS_FALSE;

}


/*lint -restore*/
#endif /* end FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




