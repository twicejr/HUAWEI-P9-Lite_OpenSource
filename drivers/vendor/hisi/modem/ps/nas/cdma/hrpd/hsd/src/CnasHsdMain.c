/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdMain.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月12日
  功能描述   : HRPD SD(system determination)任务初始化，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHsdMain.h"
#include "CnasHsdCtx.h"
#include "CnasTimerMgmt.h"
#include "CnasCcb.h"
#include "CnasMntn.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdFsmSwitchOnTbl.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasHsdPreProcTbl.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdFsmInterSysTbl.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_RegPreFsm
 功能描述  : HSD预处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegPreFsm(VOS_VOID)
{
    /* 预处理状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPreFsmDescAddr()),
                         "CNAS:FSM:HSD:PRE",
                         (VOS_UINT32)(CNAS_HSD_GetPreProcessStaTblSize()),
                         CNAS_HSD_GetPreProcStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RegMainL1Fsm
 功能描述  : HSD L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegMainL1Fsm(VOS_VOID)
{
    /* main状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetMainFsmDescAddr()),
                         "CNAS:FSM:HSD:MAIN",
                         (VOS_UINT32)(CNAS_HSD_GetL1MainStaTblSize()),
                         CNAS_HSD_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RegL2Fsm
 功能描述  : HSD L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegL2Fsm(VOS_VOID)
{
    /* SwitchOn状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetSwitchOnFsmDescAddr()),
                         "CNAS:FSM:HSD:SwitchOn",
                         (VOS_UINT32)CNAS_HSD_GetSwitchOnStaTblSize(),
                         CNAS_HSD_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_SwitchOn);

    /* PowerOff状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPowerOffFsmDescAddr()),
                         "CNAS:FSM:HSD:PowerOff",
                         (VOS_UINT32)CNAS_HSD_GetPowerOffStaTblSize(),
                         CNAS_HSD_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* SysAcq状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetSysAcqFsmDescAddr()),
                         "CNAS:FSM:HSD:SysAcq",
                         (VOS_UINT32)CNAS_HSD_GetSysAcqStaTblSize(),
                         CNAS_HSD_GetSysAcqStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_SysAcq);

    /* PowerSave状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPowerSaveFsmDescAddr()),
                         "CNAS:FSM:HSD:PowerSave",
                         (VOS_UINT32)CNAS_HSD_GetPowerSaveStaTblSize(),
                         CNAS_HSD_GetPowerSaveStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* InterSys状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetInterSysFsmDescAddr()),
                         "CNAS:FSM:HSD:InterSys",
                         (VOS_UINT32)CNAS_HSD_GetInterSysStaTblSize(),
                         CNAS_HSD_GetInterSysStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_InterSys);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RegFsm
 功能描述  : HSD注册状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_RegFsm(VOS_VOID)
{
    /* 注册预处理状态机 */
    CNAS_HSD_RegPreFsm();

    /* 注册L1状态机 */
    CNAS_HSD_RegMainL1Fsm();

    /* 注册L2状态机 */
    CNAS_HSD_RegL2Fsm();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_PreProcessMsg
 功能描述  : HSD消息预处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 预处理完成
             VOS_FALSE -- 还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    /* 获取预处理状态机描述符地址 */
    pstFsmDesc = CNAS_HSD_GetPreFsmDescAddr();

    /* 获取状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_HSD_L1_STA_PREPROC, ulEventType);

    /* 函数空指针检查 */
    if (VOS_NULL_PTR != pActFun )
    {
        /* 执行函数功能操作 */
        ulRet = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名    : CNAS_HSD_FsmProcessEvent
 功能描述    : 状态机的事件处理函数
 输入参数    :
               ulCurState  -- 当前状态
               ulEventType -- 处理事件
               pRcvMsg     -- 消息指针
 输出参数    :
 返回值      : VOS_FALSE -- 消息处理未完成
               VOS_TRUE  -- 消息处理已完成
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 CNAS_HSD_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_HSD, "CNAS_HSD_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_HSD_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR == pActFun)
    {
        /* 消息未被处理完成需继续处理 */
        return VOS_FALSE;
    }

    /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
    ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
    CNAS_INFO_LOG1(UEPS_PID_HSD, "CNAS_HSD_FsmProcessEvent", ulRet);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcessMsgInFsm
 功能描述  : 消息状态机处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 消息处理完成
             VOS_FALSE -- 消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前HSD的状态机上下文 */
    pstCurFsm           = CNAS_HSD_GetCurFsmAddr();

    /* 获取当前HSD的栈深度 */
    usOldStackDepth     = CNAS_HSD_GetFsmStackDepth();

    /* 消息处理 */
    ulRet     = CNAS_HSD_FsmProcessEvent(pstCurFsm->ulState,
                                         ulEventType,
                                         (VOS_VOID*)pstMsg);

    /* 获取当前HSD的新栈深度 */
    usNewStackDepth    = CNAS_HSD_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前MMC的顶层状态 */
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = CNAS_HSD_FsmProcessEvent(pstCurFsm->ulState,
                                           ulEventType,
                                           (VOS_VOID*)pstMsg);


    return ulRet;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcessHsdIntMsg
 功能描述  : HSD内部队列的消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcessHsdIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* 消息勾包 */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* 如果已经处理完成则取下条消息继续处理 */
        if (VOS_TRUE == CNAS_HSD_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* 释放内部消息 */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* 继续下一条消息处理 */
            pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();

            continue;
        }

        /* 消息进状态机处理 */
        CNAS_HSD_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* 释放内部消息 */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* 继续下一条消息处理 */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcessBufferMsg(VOS_VOID)
{
    CNAS_HSD_MSG_STRU                  *pstEntryMsg = VOS_NULL_PTR;

    /* 内存空间分配 */
    pstEntryMsg = (CNAS_HSD_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, sizeof(CNAS_HSD_MSG_STRU) );

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == CNAS_HSD_GetNextCachedMsg(pstEntryMsg))
    {
        /* 如果已经处理完成则取下条消息继续处理 */
        if (VOS_TRUE == CNAS_HSD_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            continue;
        }

        /* 进入状态机处理 */
        CNAS_HSD_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer);

        /* 内部队列的消息处理 */
        CNAS_HSD_ProcessHsdIntMsg();
    }

    PS_MEM_FREE(UEPS_PID_HSD, pstEntryMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_MsgProc
 功能描述  : HRPD HSD模块消息处理入口函数
 输入参数  : pMsg -- 消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usPrevStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulSenderPid;

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 生成事件类型 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* 停止对应的定时器 */
        CNAS_StopTimer(UEPS_PID_HSD, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* 如果已经处理完成则直接返回 */
    if (VOS_TRUE == CNAS_HSD_PreProcessMsg(ulEventType, pstMsg))
    {
        /* 处理内部消息队列 */
        CNAS_HSD_ProcessHsdIntMsg();

        return;
    }

    /* 获取当前HSD的栈深度 */
    usPrevStackDepth = CNAS_HSD_GetFsmStackDepth();

    /* 进入状态机处理 */
    CNAS_HSD_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 在状态机退出后，获取新的栈深度 */
    usNewStackDepth = CNAS_HSD_GetFsmStackDepth();

    /* 处理内部消息队列 */
    CNAS_HSD_ProcessHsdIntMsg();

    /* 如果栈的深度减少,说明肯定进行了退栈操作,处理一次缓存 */
    if (usNewStackDepth < usPrevStackDepth)
    {
        CNAS_HSD_ProcessBufferMsg();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitTask
 功能描述  : HRPD SD模块任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_HSD_InitTask(VOS_VOID)
{
    /* 初始化HSD全局变量 */
    CNAS_HSD_InitCtx(CNAS_HSD_INIT_CTX_STARTUP);

    /* HSD 状态机注册 */
    CNAS_HSD_RegFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_InitPid
 功能描述  : HRPD SD模块PID初始化函数
 输入参数  : enInitPhase -- 初始化阶段
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 调用HSD模块初始化函数 */
            CNAS_HSD_InitTask();
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
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



