/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdMain.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : 1X SD(system determination)任务初始化，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXsdMain.h"
#include "CnasXsdCtx.h"
#include "CnasTimerMgmt.h"
#include "CnasCcb.h"
#include "CnasMntn.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdFsmPowerOffTbl.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasXsdPreProcTbl.h"
#include "CnasXsdFsmRedirTbl.h"

#include "CnasXsdPreProcAct.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_RegPreFsm
 功能描述  : XSD预处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月04日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RegPreFsm(VOS_VOID)
{
    /* 预处理状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetPreFsmDescAddr()),
                         "CNAS:FSM:XSD:PRE",
                         (VOS_UINT32)(CNAS_XSD_GetPreProcessStaTblSize()),
                         CNAS_XSD_GetPreProcStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RegMainL1Fsm
 功能描述  : XSD L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月04日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RegMainL1Fsm(VOS_VOID)
{
    /* main状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetMainFsmDescAddr()),
                         "CNAS:FSM:XSD:MAIN",
                         (VOS_UINT32)(CNAS_XSD_GetL1MainStaTblSize()),
                         CNAS_XSD_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XSD_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RegL2Fsm
 功能描述  : XSD L1 main状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月04日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified:Add redirection state machine

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RegL2Fsm(VOS_VOID)
{
    /* SwitchOn状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetSwitchOnFsmDescAddr()),
                         "CNAS:FSM:XSD:SwitchOn",
                         (VOS_UINT32)CNAS_XSD_GetSwitchOnStaTblSize(),
                         CNAS_XSD_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XSD_InitFsmCtx_SwitchOn);

    /* PowerOff状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetPowerOffFsmDescAddr()),
                         "CNAS:FSM:XSD:PowerOff",
                         (VOS_UINT32)CNAS_XSD_GetPowerOffStaTblSize(),
                         CNAS_XSD_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XSD_InitFsmCtx_PowerOff);


    /* SysAcq状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetSysAcqFsmDescAddr()),
                         "CNAS:FSM:XSD:SysAcq",
                         (VOS_UINT32)CNAS_XSD_GetSysAcqStaTblSize(),
                         CNAS_XSD_GetSysAcqStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XSD_InitFsmCtx_SysAcq);

    /* redirection state machine register */
    NAS_FSM_RegisterFsm((CNAS_XSD_GetRedirFsmDescAddr()),
                         "CNAS:FSM:XSD:Redirection",
                         (VOS_UINT32)CNAS_XSD_GetRedirStaTblSize(),
                         CNAS_XSD_GetRedirStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XSD_InitFsmCtx_Redirection);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RegFsm
 功能描述  : XSD注册状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月04日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XSD_RegFsm(VOS_VOID)
{
    CNAS_XSD_RegPreFsm();

    /* 注册L1状态机 */
    CNAS_XSD_RegMainL1Fsm();

    /* 注册L2状态机 */
    CNAS_XSD_RegL2Fsm();
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PreProcessMsg
 功能描述  : XSD消息预处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 预处理完成
             VOS_FALSE -- 还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月04日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    /* 获取预处理状态机描述符地址 */
    pstFsmDesc = CNAS_XSD_GetPreFsmDescAddr();

    /* 获取状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_XSD_L1_STA_PREPROC, ulEventType);

    /* 函数空指针检查 */
    if (VOS_NULL_PTR != pActFun )
    {
        /* 执行函数功能操作 */
        ulRet = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名    : CNAS_XSD_FsmProcessEvent
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
   1.日    期   : 2014年7月04日
     作    者   : y00245242
     修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 CNAS_XSD_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_XSD, "CNAS_XSD_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_XSD_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR == pActFun)
    {
        /* 消息未被处理完成需继续处理 */
        return VOS_FALSE;
    }

    /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
    ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_FsmProcessEvent", ulRet);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcessMsgInFsm
 功能描述  : 消息状态机处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 消息处理完成
             VOS_FALSE -- 消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前XSD的状态机上下文 */
    pstCurFsm           = CNAS_XSD_GetCurFsmAddr();

    /* 获取当前XSD的栈深度 */
    usOldStackDepth     = CNAS_XSD_GetFsmStackDepth();

    /* 消息处理 */
    ulRet     = CNAS_XSD_FsmProcessEvent(pstCurFsm->ulState,
                                         ulEventType,
                                         (VOS_VOID*)pstMsg);

    /* 获取当前XSD的新栈深度 */
    usNewStackDepth    = CNAS_XSD_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前MMC的顶层状态 */
    pstCurFsm   = CNAS_XSD_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = CNAS_XSD_FsmProcessEvent(pstCurFsm->ulState,
                                           ulEventType,
                                           (VOS_VOID*)pstMsg);


    return ulRet;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcessXsdIntMsg
 功能描述  : XSD内部队列的消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcessXsdIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)CNAS_XSD_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* 消息勾包 */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* 如果已经处理完成则取下条消息继续处理 */
        if (VOS_TRUE == CNAS_XSD_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* 释放内部消息 */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* 继续下一条消息处理 */
            pstIntMsg = (MSG_HEADER_STRU *)CNAS_XSD_GetNextIntMsg();

            continue;
        }

        /* 消息进状态机处理 */
        CNAS_XSD_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* 释放内部消息 */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* 继续下一条消息处理 */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_XSD_GetNextIntMsg();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcessBufferMsg(VOS_VOID)
{
    CNAS_XSD_MSG_STRU                  *pstEntryMsg = VOS_NULL_PTR;

    /* 内存空间分配 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    if (0 < CNAS_XSD_GetCacheMsgNum())
    {
        pstEntryMsg = (CNAS_XSD_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_XSD_MSG_STRU));
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == CNAS_XSD_GetNextCachedMsg(pstEntryMsg))
    {
        /* 如果已经处理完成则取下条消息继续处理 */
        if (VOS_TRUE == CNAS_XSD_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            continue;
        }

        /* 进入状态机处理 */
        CNAS_XSD_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer);

        CNAS_XSD_ProcessXsdIntMsg();
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstEntryMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_MsgProc
 功能描述  : 1X XSD模块消息处理入口函数
 输入参数  : pMsg -- 消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月28日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年01月13日
   作    者   : m00312079
   修改内容   : 不判断预处理函数CNAS_XSD_PreProcessMsg的返回值
                目的是为了在预处理过程中发送的内部消息可以得到
                处理。
 3.日    期   : 2015年5月22日
   作    者   : w00242748
   修改内容   : CDMA Iteration 15 modified

  4.日    期   : 2015年7月27日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usOldStackDepth;
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
        CNAS_StopTimer(UEPS_PID_XSD, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* 预处理处理成功，不进入状态机处理 */
    if (VOS_TRUE == CNAS_XSD_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }

    /* 获取当前XSD的栈深度 */
    usOldStackDepth = CNAS_XSD_GetFsmStackDepth();



    /* 进入状态机处理 */
    CNAS_XSD_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 处理内部消息队列 */
    CNAS_XSD_ProcessXsdIntMsg();

    /* 在状态机退出后，获取新的栈深度 */
    usNewStackDepth = CNAS_XSD_GetFsmStackDepth();


    /* 如果栈的深度减少,说明肯定进行了退栈操作,处理一次缓存 */
    if (usNewStackDepth < usOldStackDepth)
    {
        CNAS_XSD_ProcessBufferMsg();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitTask
 功能描述  : 1X SD模块任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_XSD_InitTask(VOS_VOID)
{
    /* 初始化XSD全局变量 */
    CNAS_XSD_InitCtx(CNAS_XSD_INIT_CTX_STARTUP);

    /* XSD 状态机注册 */
    CNAS_XSD_RegFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitPid
 功能描述  : 1X SD模块PID初始化函数
 输入参数  : enInitPhase -- 初始化阶段
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 调用XSD模块初始化函数 */
            CNAS_XSD_InitTask();
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



