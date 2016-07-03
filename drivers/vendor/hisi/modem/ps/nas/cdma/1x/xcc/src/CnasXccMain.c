

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasCcb.h"
#include  "CnasXccMain.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccFsmMoCallingTbl.h"
#include  "CnasXccFsmMtCallingTbl.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccInstanceMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXccMainCtrl.h"
#include  "NasFsm.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXccSndXsd.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_UINT32 CNAS_XCC_RegMainL1Fsm(VOS_VOID)
{
    /* main状态机注册 */

    NAS_FSM_RegisterFsm((CNAS_XCC_GetMainFsmDescAddr()),
                         "CNAS:FSM:XCC:MAIN",
                         (VOS_UINT32)(CNAS_XCC_GetL1MainStaTblSize()),
                         CNAS_XCC_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_L1Main);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_XCC_RegL2Fsm(VOS_VOID)
{
    /* L2状态机注册 */
    /* MO CALLING状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XCC_GetMoCallingFsmDescAddr()),
                         "CNAS:FSM:XCC:MO CALLING",
                         (VOS_UINT32)CNAS_XCC_GetMoCallingStaTblSize(),
                         CNAS_XCC_GetMoCallingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_MoCalling);

    /* MT CALLING状态机注册 */
    NAS_FSM_RegisterFsm((CNAS_XCC_GetMtCallingFsmDescAddr()),
                         "CNAS:FSM:XCC:MT CALLING",
                         (VOS_UINT32)CNAS_XCC_GetMtCallingStaTblSize(),
                         CNAS_XCC_GetMtCallingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_MtCalling);

    return VOS_TRUE;
}


VOS_VOID  CNAS_XCC_RegFsm(VOS_VOID)
{
    /* 注册L1状态机 */
    CNAS_XCC_RegMainL1Fsm();

    /* 注册L2状态机 */
    CNAS_XCC_RegL2Fsm();
}


VOS_VOID CNAS_XCC_LoadSpecifiedCallInstEntity(
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity
)
{
    /* 把对应的状态机实体加载为当前状态机 */
    CNAS_XCC_GetCtxAddr()->pstCurFsmEntity = pstFsmEntity;

    pstFsmEntity->stCurFsm.ucConnectId = pstFsmEntity->stCallInfoCtx.ucConnectId;
}


VOS_UINT32 CNAS_XCC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt     = VOS_FALSE;

    CNAS_INFO_LOG2(UEPS_PID_XCC,
                   "CNAS_XCC_FsmProcessEvent",
                   ulCurState, ulEventType);

    pstFsmDesc = CNAS_XCC_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    /* 函数空指针检查 */
    if (VOS_NULL_PTR == pActFun)
    {
        /* 消息未被处理完成需继续处理 */
        return VOS_FALSE;
    }

    /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
    ulRslt   = (*pActFun) (ulEventType, (struct MsgCB*)pRcvMsg);

    CNAS_INFO_LOG1(UEPS_PID_XCC, "CNAS_XCC_FsmProcessEvent", ulRslt);

    return ulRslt;
}


VOS_VOID CNAS_XCC_ProcBufferReqMsg(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           ucActInstNum;
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;

    /* 获取当前激活的call instance数目 */
    ucActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* 获取当前缓存消息数目 */
    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    /* 注: 如果当前消息不能处理，需要继续缓存，则重新放到了队列的尾部，在本循环的最后一步
     *     把在队列头部的该消息清除了，即遍历队列中所有缓存的消息一次，需要继续缓存的会被
     *     重新被放到消息队列中
     */

    for (i = 0; i < ucMsgNum; i++)
    {
        pstBufferMsgHdr = (MSG_HEADER_STRU *)CNAS_XCC_GetNextBufferMsg();

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        /* 如果缓存的是关机请求，跳出，等待所有call instance去激活 */
        if ((CNAS_BuildEventType(UEPS_PID_XSD, ID_XSD_XCC_POWER_OFF_REQ) == ulBufferMsgEventType)
         && (0                                                           != ucActInstNum))
        {
            return;
        }

        /* main处理 */
        if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulBufferMsgEventType,
                                                       (struct MsgCB *)pstBufferMsgHdr))
        {
            /* 外部消息进状态机处理 */
            CNAS_XCC_ProcessMsgInFsm(ulBufferMsgEventType,
                                     (struct MsgCB *)pstBufferMsgHdr);

        }

        /* 处理内部消息队列 */
        CNAS_XCC_ProcXccIntMsg();

        /* 释放缓存消息 */
        CNAS_XCC_FreeCurrentBufferMsg();
    }
}


VOS_UINT32 CNAS_XCC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRslt;
    VOS_UINT16                                              usOldStackDepth;
    VOS_UINT16                                              usNewStackDepth;
    CNAS_XCC_FSM_ENTITY_LIST_STRU                           stFsmEntityList;
    CNAS_XCC_FSM_ENTITY_STRU                               *pstFsmEntity = VOS_NULL_PTR;
    CNAS_XCC_FSM_CTX_STRU                                  *pstCurFsm    = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    ulRslt = VOS_TRUE;

    /* 获取返回需要处理的call control instance列表 */
    NAS_MEM_SET_S(&stFsmEntityList, sizeof(CNAS_XCC_FSM_ENTITY_LIST_STRU), 0, sizeof(CNAS_XCC_FSM_ENTITY_LIST_STRU));

    CNAS_XCC_GetCallInstanceEntity(ulEventType, pstMsg, &stFsmEntityList);

    for (i = 0; i < CNAS_MIN(stFsmEntityList.ucFsmNum, CNAS_XCC_MAX_FSM_ENTITY_NUM); i++)
    {
        pstFsmEntity = (stFsmEntityList.pstFsmEntity[i]);

        CNAS_INFO_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessMsgInFsm",
                       pstFsmEntity->stCallInfoCtx.ucConnectId);

        /* 加载指定的call control instance状态机 */
        CNAS_XCC_LoadSpecifiedCallInstEntity(pstFsmEntity);

        /* 获取当前XCC的状态机上下文 */
        pstCurFsm           = CNAS_XCC_GetCurFsmAddr();

        /* 获取当前XCC的栈深度 */
        usOldStackDepth    = CNAS_XCC_GetFsmStackDepth();

        /* 消息处理 */
        ulRslt    = CNAS_XCC_FSM_ProcessEvent(pstCurFsm->ulState,
                                              ulEventType,
                                             (VOS_VOID*)pstMsg);

        /* 获取当前XCC的新栈深度 */
        usNewStackDepth    = CNAS_XCC_GetFsmStackDepth();

        /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
        if (usNewStackDepth <= usOldStackDepth)
        {
            continue;
        }

        /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
        /* 重新获取当前XCC的顶层状态 */
        pstCurFsm   = CNAS_XCC_GetCurFsmAddr();

        /* 将消息放入顶层状态机，继续处理 */
        ulRslt      = CNAS_XCC_FSM_ProcessEvent(pstCurFsm->ulState,
                                                ulEventType,
                                                (VOS_VOID*)pstMsg );
    }

    return ulRslt;
}


VOS_VOID CNAS_XCC_ProcXccIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;


    pstIntMsg = (MSG_HEADER_STRU *)CNAS_XCC_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* 消息勾包 */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulEventType, (struct MsgCB *)pstIntMsg))
        {
            /* 消息进状态机处理 */
            CNAS_XCC_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);
        }

        /* 释放内部消息 */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* 继续下一条消息处理 */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_XCC_GetNextIntMsg();
    }
}


VOS_VOID CNAS_XCC_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ulOldActInstNum;
    VOS_UINT8                           ulNewActInstNum;
    VOS_UINT32                          ulSenderPid;

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    /* 获取消息头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 生成事件类型 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* 停止对应的定时器 */
        CNAS_StopTimer(UEPS_PID_XCC, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid,
                                           (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* 获取消息处理前激活的call instance数目 */
    ulOldActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* main处理 */
    if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulEventType, pstMsg))
    {
        /* 外部消息进状态机处理 */
        CNAS_XCC_ProcessMsgInFsm(ulEventType, pstMsg);
    }

    /* 处理内部消息队列 */
    CNAS_XCC_ProcXccIntMsg();

    /* 获取消息处理后激活的call instance数目 */
    ulNewActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* 如果新的激活call instance数目等于0或小于消息处理前激活的call instance数目，处理缓存请求 */
    if ((0               == ulNewActInstNum)
     || (ulNewActInstNum <  ulOldActInstNum))
    {
        /* 处理缓存的用户请求消息 */
        CNAS_XCC_ProcBufferReqMsg();
    }

    return;
}


VOS_UINT32  CNAS_XCC_InitTask(VOS_VOID)
{
    /* 初始化XCC全局变量 */
    CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_ON);

    /* XCC 状态机注册 */
    CNAS_XCC_RegFsm();

    return VOS_OK;
}


VOS_UINT32 CNAS_XCC_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 调用XCC模块初始化函数 */
            CNAS_XCC_InitTask();
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



