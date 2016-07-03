
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_MAIN_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafLog.h"
#include "TafXpdsMain.h"
#include "TafXpdsMntn.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMainTbl.h"
#include "TafXpdsPreProcTbl.h"
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmCpLinkCtrlTbl.h"
#include "TafXpdsFsmMpcProcTbl.h"
#include "TafXpdsFsmPdeProcTbl.h"
#include "TafXpdsFsmCpPdeProcTbl.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*lint -save -e958*/

VOS_UINT32 TAF_XPDS_RegPreFsm(VOS_VOID)
{
    /* 预处理状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetPreProcFsmDescAddr()),
                         "TAF:FSM:XPDS:PRE",
                         (VOS_UINT32)(TAF_XPDS_GetPreProcStaTblSize()),
                         TAF_XPDS_GetPreProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RegMainL1Fsm(VOS_VOID)
{
    /* main状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetMainFsmDescAddr()),
                         "TAF:FSM:XPDS:MAIN",
                         (VOS_UINT32)(TAF_XPDS_GetMainStaTblSize()),
                         TAF_XPDS_GetMainStaTblAddr(),
                         VOS_NULL_PTR,
                         TAF_XPDS_InitFsmCtx_L1Main);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RegL2Fsm(VOS_VOID)
{
    /* 用户面链路状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetFsmUpLinkFsmDescAddr()),
                         "TAF:FSM:XPDS:UP_LINK_CTRL",
                         (VOS_UINT32)TAF_XPDS_GetUpLinkCtrlStaTblSize(),
                         TAF_XPDS_GetUpLinkCtrlStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* 控制面链路状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetFsmCpLinkFsmDescAddr()),
                         "TAF:FSM:XPDS:CP_LINK_CTRL",
                         (VOS_UINT32)TAF_XPDS_GetCpLinkCtrlStaTblSize(),
                         TAF_XPDS_GetCpLinkCtrlStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* MPC状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetL2MpcProcFsmDescAddr()),
                         "TAF:FSM:XPDS:MPC",
                         (VOS_UINT32)TAF_XPDS_GetL2MpcProcStaTblSize(),
                         TAF_XPDS_GetL2MpcProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* PDE状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetL2PdeProcFsmDescAddr()),
                         "TAF:FSM:XPDS:PDE",
                         (VOS_UINT32)TAF_XPDS_GetL2PdeProcStaTblSize(),
                         TAF_XPDS_GetL2PdeProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* 控制面PDE状态机注册 */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetCpL2PdeProcFsmDescAddr()),
                         "TAF:FSM:XPDS:CP_PDE",
                         (VOS_UINT32)TAF_XPDS_GetCpL2PdeProcStaTblSize(),
                         TAF_XPDS_GetCpL2PdeProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}


VOS_VOID  TAF_XPDS_RegFsm(VOS_VOID)
{
    /* 注册预处理状态机 */
    TAF_XPDS_RegPreFsm();

    /* 注册L1状态机 */
    TAF_XPDS_RegMainL1Fsm();

    /* 注册L2状态机 */
    TAF_XPDS_RegL2Fsm();
}


VOS_UINT32 TAF_XPDS_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;
    TAF_ACTION_FUNC                     pActFun;
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 获取预处理动作表中的相应的动作处理函数 */
    pstFsmDesc = TAF_XPDS_GetPreProcFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_XPDS_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 预处理消息,分为两类消息,一类为预处理结束就返回,另外一类为预处理
        结束后,仍然需要进行到状态机中继续处理,因此此处直接通过函数返回预处
        理结束后是否需要进行状态机处理*/
        ulRslt = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRslt;
}


VOS_UINT32 TAF_XPDS_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    TAF_ACTION_FUNC                     pActFun;
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(UEPS_PID_XPDS, "TAF_XPDS_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = TAF_XPDS_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pRcvMsg);

        TAF_INFO_LOG1(UEPS_PID_XPDS, "TAF_XPDS_FsmProcessEvent", ulRet);

        return VOS_TRUE;
    }

    /* 消息未被处理需继续处理 */
    return VOS_FALSE;
}


VOS_UINT32 TAF_XPDS_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_XPDS_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前XREG的状态机上下文 */
    pstCurFsm          = TAF_XPDS_GetCurFsmAddr();

    /* 获取当前XREG的栈深度 */
    usOldStackDepth    = TAF_XPDS_GetFsmStackDepth();

    /* 消息处理 */
    ulRet              = TAF_XPDS_FsmProcessEvent(pstCurFsm->ulState,
                                                   ulEventType,
                                                   (VOS_VOID*)pstMsg);

    /* 获取当前XREG的新栈深度 */
    usNewStackDepth    = TAF_XPDS_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前XREG的顶层状态 */
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = TAF_XPDS_FsmProcessEvent(pstCurFsm->ulState,
                                            ulEventType,
                                            (VOS_VOID*)pstMsg);


    return ulRet;
}


VOS_VOID TAF_XPDS_ProcessIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* 消息勾包 */
        TAF_XPDS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                                  pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                                  (VOS_VOID *)pstIntMsg);

        ulEventType = TAF_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* 如果已经处理完成则取下条消息继续处理 */
        if (VOS_TRUE == TAF_XPDS_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* 释放内部消息 */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* 继续下一条消息处理 */
            pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();

            continue;
        }

        /* 消息进状态机处理 */
        TAF_XPDS_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* 释放内部消息 */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* 继续下一条消息处理 */
        pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();
    }

    return;
}


VOS_VOID TAF_XPDS_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    /* 空指针检查 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 打印错误信息 */
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 生成事件类型 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* 停止对应的定时器 */
        TAF_XPDS_StopTimer(pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* 如果已经处理完成则直接返回 */
    if (VOS_TRUE == TAF_XPDS_PreProcessMsg(ulEventType, pstMsg))
    {
        /* 处理内部消息队列 */
        TAF_XPDS_ProcessIntMsg();

        return;
    }

    /* 获取当前XREG的栈深度 */
    usOldStackDepth = TAF_XPDS_GetFsmStackDepth();

    /* 进入状态机处理 */
    TAF_XPDS_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 在状态机退出后，获取新的栈深度 */
    usNewStackDepth = TAF_XPDS_GetFsmStackDepth();

    /* 处理内部消息队列 */
    TAF_XPDS_ProcessIntMsg();

    /* 如果栈的深度减少,说明肯定进行了退栈操作,需要优先处理该状态机的结果消息,直接返回 */
    if (usNewStackDepth < usOldStackDepth)
    {
        /* To do: 记录退栈操作,只要发生了退栈后续就可以处理缓存 */
        return;
    }

    return;
}


VOS_UINT32 TAF_XPDS_InitTask(VOS_VOID)
{
    /* 初始化上下文 */
    TAF_XPDS_InitCtx();

    /* 注册状态机 */
    TAF_XPDS_RegFsm();

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_InitPid(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 调用XPDS模块初始化函数 */
            TAF_XPDS_InitTask();
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
#endif
#endif

