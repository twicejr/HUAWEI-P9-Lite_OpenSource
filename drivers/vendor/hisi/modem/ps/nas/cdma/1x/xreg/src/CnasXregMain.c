/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregMain.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : 1X REG(register)任务初始化，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregCtx.h"
#include  "CnasXregMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXregRegingProcTbl.h"
#include  "CnasXregPreProcTbl.h"
#include  "CnasXregProcess.h"
#include  "CnasXregListProc.h"
#include  "CnasXregFsmSwitchOnTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_RegPreFsm
 功能描述  : XREG预处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月07日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegPreFsm(VOS_VOID)
{
    /* 预处理状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetPreFsmDescAddr()),
                         "CNAS:FSM:XREG:PRE",
                         (VOS_UINT32)(CNAS_XREG_GetPreProcessStaTblSize()),
                         g_astCnasXregPreProcessFsmTbl,
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RegMainL1Fsm
 功能描述  : XREG L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月07日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegMainL1Fsm(VOS_VOID)
{
    /* main状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetMainFsmDescAddr()),
                         "CNAS:FSM:XREG:MAIN",
                         (VOS_UINT32)(CNAS_XREG_GetL1MainStaTblSize()),
                         CNAS_XREG_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XREG_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RegL2Fsm
 功能描述  : XREG L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月04日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegL2Fsm(VOS_VOID)
{
    /* SWITCHON状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetSwitchOnFsmDescAddr()),
                         "CNAS:FSM:XREG:SwitchOn",
                         (VOS_UINT32)CNAS_XREG_GetSwitchOnStaTblSize(),
                         CNAS_XREG_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XREG_InitFsmCtx_SwitchOn);

    /* Reging状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetRegingFsmDescAddr()),
                         "CNAS:FSM:XREG:Reging",
                         (VOS_UINT32)CNAS_XREG_GetRegingStaTblSize(),
                         CNAS_XREG_GetRegingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RegFsm
 功能描述  : XREG注册状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月07日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XREG_RegFsm(VOS_VOID)
{
    /* 注册预处理状态机 */
    CNAS_XREG_RegPreFsm();

    /* 注册L1状态机 */
    CNAS_XREG_RegMainL1Fsm();

    /* 注册L2状态机 */
    CNAS_XREG_RegL2Fsm();
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_PreProcessMsg
 功能描述  : XREG消息预处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 预处理完成
             VOS_FALSE -- 还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月07日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 获取预处理动作表中的相应的动作处理函数 */
    pstFsmDesc = CNAS_XREG_GetPreFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_XREG_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 预处理消息,分为两类消息,一类为预处理结束就返回,另外一类为预处理
        结束后,仍然需要进行到状态机中继续处理,因此此处直接通过函数返回预处
        理结束后是否需要进行状态机处理*/
        ulRslt = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名    : CNAS_XREG_FsmProcessEvent
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
   1.日    期   : 2014年7月07日
     作    者   : h00246512
     修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 CNAS_XREG_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_XREG, "CNAS_XREG_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_XREG_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pRcvMsg);

        CNAS_INFO_LOG1(UEPS_PID_XREG, "CNAS_XREG_FsmProcessEvent", ulRet);

        return VOS_TRUE;
    }

    /* 消息未被处理需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ProcessMsgInFsm
 功能描述  : 消息状态机处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 消息处理完成
             VOS_FALSE -- 消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月07日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前XREG的状态机上下文 */
    pstCurFsm          = CNAS_XREG_GetCurFsmAddr();

    /* 获取当前XREG的栈深度 */
    usOldStackDepth    = CNAS_XREG_GetFsmStackDepth();

    /* 消息处理 */
    ulRet              = CNAS_XREG_FsmProcessEvent(pstCurFsm->ulState,
                                                   ulEventType,
                                                   (VOS_VOID*)pstMsg);

    /* 获取当前XREG的新栈深度 */
    usNewStackDepth    = CNAS_XREG_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前XREG的顶层状态 */
    pstCurFsm   = CNAS_XREG_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = CNAS_XREG_FsmProcessEvent(pstCurFsm->ulState,
                                            ulEventType,
                                            (VOS_VOID*)pstMsg);


    return ulRet;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ProcMsgPrio
 功能描述  : 将当前收到的消息和L2状态机的入口消息进行比较,并根据比较结果进行后续的动作
 输入参数  : ulEventType -- 消息类型
             pstMsg      -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 当前消息处理完成，不需要后续处理
             VOS_FALSE -- 当前消息处理完成，需要后续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 判断当前在层二状态机 */
    if (CNAS_XREG_FSM_REGING == CNAS_XREG_GetCurrFsmId())
    {
        return CNAS_XREG_PostProcessMsg_Reging(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_PostProcessMsg
 功能描述  : XREG状态机后处理函数,将当前收到的消息和L2状态机的入口消息进行比较,
             判断后续的动作
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 消息处理完成
             VOS_FALSE -- 消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月07日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 本次迭代不涉及 */

    if (VOS_TRUE == CNAS_XREG_ProcMsgPrio(ulEventType, pstMsg))
    {
        /* 打印log信息 */


        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月07日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_ProcessBufferMsg(VOS_VOID)
{
    CNAS_XREG_MSG_STRU                 *pstCacheMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    /* 内存空间分配 */
    pstCacheMsg = (CNAS_XREG_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XREG, sizeof(CNAS_XREG_MSG_STRU));

    if (VOS_NULL_PTR == pstCacheMsg)
    {
        return VOS_FALSE;
    }

    ulRet = VOS_TRUE;
    while (VOS_TRUE == CNAS_XREG_GetNextCachedMsg(pstCacheMsg))
    {
        if (VOS_TRUE == CNAS_XREG_PreProcessMsg(pstCacheMsg->ulEventType, (struct MsgCB*)pstCacheMsg->aucMsgBuffer))
        {
            continue;
        }

        /* 获取当前XREG的栈深度 */
        usOldStackDepth     = CNAS_XREG_GetFsmStackDepth();

        /* 进入状态机处理 */
        ulRet  = CNAS_XREG_ProcessMsgInFsm(pstCacheMsg->ulEventType, (struct MsgCB*)pstCacheMsg->aucMsgBuffer);

        /* 获取当前XREG的栈深度 */
        usNewStackDepth     = CNAS_XREG_GetFsmStackDepth();

        /* 如果栈的深度增加,说明肯定进行了压栈操作,不能继续处理消息 */
        if (usNewStackDepth > usOldStackDepth)
        {
            ulRet   = VOS_FALSE;
            break;
        }

        /* 该消息进入了后处理,后处理中是打断或缓存的,则表明不能继续处理缓存 */
        if (VOS_FALSE == ulRet)
        {
            if (VOS_TRUE == CNAS_XREG_PostProcessMsg(pstCacheMsg->ulEventType,
                                                     (struct MsgCB*)pstCacheMsg->aucMsgBuffer))
            {
                ulRet   = VOS_FALSE;
                break;
            }
        }
    }

    PS_MEM_FREE(UEPS_PID_XREG, pstCacheMsg);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_MsgProc
 功能描述  : 1X REG模块消息处理入口函数
 输入参数  : pMsg -- 消息指针
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月28日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulSenderPid;

    /* 空指针检查 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 打印错误信息 */
        return;
    }

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 生成事件类型 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* 停止对应的定时器 */
        CNAS_StopTimer(UEPS_PID_XREG, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALIN, ulEventType);

    /* 如果已经处理完成则直接返回 */
    if (VOS_TRUE == CNAS_XREG_PreProcessMsg(ulEventType, pstMsg))
    {
       CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALOUT, ulEventType);
       return;
    }

    /* 获取当前XREG的栈深度 */
    usOldStackDepth = CNAS_XREG_GetFsmStackDepth();

    /* 进入状态机处理 */
    ulRet = CNAS_XREG_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 在状态机退出后，获取新的栈深度 */
    usNewStackDepth = CNAS_XREG_GetFsmStackDepth();

    /* 如果栈的深度减少,说明肯定进行了退栈操作,需要优先处理该状态机的结果消息,直接返回 */
    if (usNewStackDepth < usOldStackDepth)
    {
        /* 记录退栈操作,只要发生了退栈后续就可以处理缓存 */
        CNAS_XREG_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    /* 该消息在状态机中已经处理完成,可尝试处理一下缓存 */
    if (VOS_TRUE == ulRet)
    {
        /* 当前仅收到状态机的退出消息才能够处理缓存 */
        if (VOS_TRUE == CNAS_XREG_GetFsmStackPopFlg())
        {
            CNAS_XREG_ProcessBufferMsg();
            CNAS_XREG_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    /* 在当前状态机中未处理完毕，判断消息是否需要打断当前的L2状态机,后处理 */
    else
    {
        CNAS_XREG_PostProcessMsg(ulEventType, pstMsg);
    }

    CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALOUT, ulEventType);

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitTask
 功能描述  : 1X REG模块任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : l60609
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_XREG_InitTask(VOS_VOID)
{
    /* 初始化ZONE注册使用的链表 */
    CNAS_XREG_InitList();

    /* 初始化上下文 */
    CNAS_XREG_InitCtx();

    /* 注册状态机 */
    CNAS_XREG_RegFsm();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitPid
 功能描述  : 1X REG的PID初始化函数
 输入参数  : enInitPhase -- PID初始化阶段
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 调用XREG模块初始化函数 */
            CNAS_XREG_InitTask();
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
        case VOS_IP_BUTT:
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



