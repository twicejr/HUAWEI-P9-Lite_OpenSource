

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsCtx.h"
#include "TafLog.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsApi.h"
#include "Taf_ApsForSndcp.h"
#include "MmcApsInterface.h"
#include "Taf_Aps.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsGetPdpIdList.h"
#include "TafApsProcNvim.h"
#include "MnApsComm.h"

#include "apminterface.h"

#include "TafApsProcEpdszid.h"

#include "TafSdcLib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_CONTEXT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAF_APS_CONTEXT_STRU                    g_stTafApsCtx;
VOS_UINT32                              g_ulApsTestStub = VOS_FALSE;


/*****************************************************************************
  3 函数实现
*****************************************************************************/


TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetPdpEntityFsm(
    VOS_UINT32                          ulMainFsmState,
    TAF_APS_FSM_ID_ENUM_UINT32          enSubFsmId,
    VOS_UINT32                          ulSubFsmState
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ((ulMainFsmState == g_stTafApsCtx.astPdpEntityFsmCtx[i].stMainFsm.ulState)
         && (enSubFsmId == g_stTafApsCtx.astPdpEntityFsmCtx[i].stSubFsm.enFsmId)
         && (ulSubFsmState == g_stTafApsCtx.astPdpEntityFsmCtx[i].stSubFsm.ulState))
        {
            return &g_stTafApsCtx.astPdpEntityFsmCtx[i];
        }
    }

    return VOS_NULL_PTR;
}


TAF_APS_TIMER_CTX_STRU*  TAF_APS_GetTimerCtxAddr( VOS_VOID )
{
    return g_stTafApsCtx.astApsTimerCtx;
}


VOS_VOID  TAF_APS_InitDsFlowCtx(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx
)
{
    /* 初始化流量统计上下文为0 */
    PS_MEM_SET(pstApsDsFlowCtx, 0, sizeof(TAF_APS_DSFLOW_STATS_CTX_STRU));

    /* 从NV中读取流量统计相关信息 */
    TAF_APS_ReadDsFlowInfoFromNv(pstApsDsFlowCtx);

    return;
}



VOS_VOID TAF_APS_InitSwitchDdrInfo(VOS_VOID)
{
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU  *pstSwitchDdrInfo;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    PS_MEM_SET(pstSwitchDdrInfo, 0, sizeof(TAF_APS_SWITCH_DDR_RATE_INFO_STRU));

    /* APS任务初始化起来后，主卡投票CPU频率到75Mhz */
#if defined(INSTANCE_1) || defined(INSTANCE_2)
#else

    /* 从NV中读取流速配置 */
    TAF_APS_ReadDsflowRateConfigFromNv(pstSwitchDdrInfo);

    if (0 != TAF_APS_GET_DFS_PROFILE_NUM())
    {
        /* 发起对DDR调频的投票请求,初始投票在为NV设置的第一个频率 */
        if (MDRV_OK != mdrv_pm_dfs_qos_get(DFS_QOS_ID_DDR_MINFREQ_E,
                                           pstSwitchDdrInfo->ulMinBand,
                                           &(pstSwitchDdrInfo->iDfsReqId)))
        {
            TAF_APS_DFS_REQUEST_FAIL_CNT(1);
            return;
        }

        TAF_APS_DFS_REQUEST_SUCC_CNT(1);
        pstSwitchDdrInfo->ulReqValue     = pstSwitchDdrInfo->ulMinBand;
        pstSwitchDdrInfo->ulSetMaxFlag   = VOS_FALSE;
    }

#endif

    return;
}


TAF_APS_SWITCH_DDR_RATE_INFO_STRU*  TAF_APS_GetSwitchDdrRateInfoAddr(VOS_VOID)
{
    return &g_stTafApsCtx.stSwitchDdrRateInfo;
}


TAF_APS_DSFLOW_STATS_CTX_STRU*  TAF_APS_GetDsFlowCtxAddr( VOS_VOID )
{
    return &g_stTafApsCtx.stApsDsFlowCtx;
}



TAF_APS_MSG_QUEUE_STRU* TAF_APS_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stTafApsCtx.stBufferEntryMsgQueue);
}


TAF_APS_PS_CALL_ANSWER_MSG_STRU* TAF_APS_GetCachPsCallMsg(
    VOS_UINT8                           ucPdpId
)
{
    return &(g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId].stSubFsm.unFsmCtx.stNwActivatingCtx.stAnswerMsg);
}


VOS_UINT8  TAF_APS_GetCacheNum( VOS_VOID )
{
    TAF_APS_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_APS_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


VOS_VOID  TAF_APS_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    TAF_APS_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = TAF_APS_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= TAF_APS_MAX_MSG_QUEUE_NUM )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SaveCacheMsgInMsgQueue:No Empty buffer");

        /* 输出缓存满的信息 */

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    /* 输出缓存信息 */
}


VOS_VOID  TAF_APS_SaveCachePsCallAnswerMsg(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    VOS_UINT8                           ucPdpid
)
{
    TAF_APS_PS_CALL_ANSWER_MSG_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = TAF_APS_GetCachPsCallMsg(ucPdpid);

    pstMsg->enMsgType = enMsgType;
    pstMsg->ucPdpid   = ucPdpid;
}


VOS_UINT32  TAF_APS_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if ( pstMsgHeader->ulLength >= ( TAF_APS_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* 将消息缓存在缓存内存池中 */
    TAF_APS_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;
}



VOS_VOID  TAF_APS_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    TAF_APS_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = TAF_APS_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(TAF_APS_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
            break;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_APS_ClearCacheMsg:invalid msg type", (VOS_INT32)ulEventType);
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        (VOS_VOID)PS_MEM_MOVE(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(TAF_APS_ENTRY_MSG_STRU));

    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    /* TAF_APS_LogBufferQueueMsg(VOS_FALSE); */

    return;
}



VOS_UINT32  TAF_APS_GetNextCachedMsg(
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_APS_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_APS_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF,"TAF_APS_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astMsgQueue[0].stMsgEntry),
               sizeof(TAF_APS_ENTRY_MSG_STRU));

    /* 消息已经取出则清除当前缓存 */
    TAF_APS_ClearCacheMsg(pstEntryMsg->ulEventType);

    return VOS_TRUE;
}


VOS_VOID TAF_APS_SetCurrPdpEntityFsmAddr(
    VOS_UINT8                           ucPdpId
)
{
    g_stTafApsCtx.pstCurrPdpEntityFsmCtx = &g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId];
}




TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetCurrPdpEntityFsmAddr(VOS_VOID)
{
    return g_stTafApsCtx.pstCurrPdpEntityFsmCtx;
}


VOS_VOID  TAF_APS_InitCmdBufferQueue(
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        pstCmdBufferQueue[i].pulMsgInfo     = VOS_NULL_PTR;
        pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
        pstCmdBufferQueue[i].enTimerId      = TI_TAF_APS_TIMER_BUTT;
        pstCmdBufferQueue[i].ulPara         = TAF_APS_INVALID_CMD_PARA;
    }

    return;
}


TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetCmdBufferQueueAddr( VOS_VOID )
{
    return g_stTafApsCtx.astCmdBufferQueue;
}


VOS_VOID  TAF_APS_DelItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    VOS_UINT32                          i;
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    pstCmdBufferQueue = TAF_APS_GetCmdBufferQueueAddr();

    for ( i = 0 ; i < TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if ((enTimerId == pstCmdBufferQueue[i].enTimerId)
         && (ulPara == pstCmdBufferQueue[i].ulPara))
        {
            /* 如果有缓存的消息，释放消息内存 */
            if (VOS_NULL_PTR != pstCmdBufferQueue[i].pulMsgInfo)
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pstCmdBufferQueue[i].pulMsgInfo);
            }

            /* 初始化 */
            pstCmdBufferQueue[i].pulMsgInfo     = VOS_NULL_PTR;
            pstCmdBufferQueue[i].enTimerId      = TI_TAF_APS_TIMER_BUTT;
            pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
            pstCmdBufferQueue[i].ulPara         = TAF_APS_INVALID_CMD_PARA;
            break;
        }
    }

    return;
}


VOS_VOID  TAF_APS_SaveItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                         *pulMsgInfo,
    VOS_UINT32                          ulMsgInfoLen,
    VOS_UINT32                          ulPara
)
{
    VOS_UINT32                          i;
    VOS_UINT32                         *pulMsgBuf;
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    /* 如果消息指针为空，直接返回 */
    if (VOS_NULL_PTR == pulMsgInfo)
    {
        return;
    }

    pstCmdBufferQueue = TAF_APS_GetCmdBufferQueueAddr();

    for ( i = 0 ; i < TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (TI_TAF_APS_TIMER_BUTT == pstCmdBufferQueue[i].enTimerId)
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if ( i >= TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* 缓存队列已满 */
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_SaveInfoInWaitL4aCnfMsgQueue, Buffer Full, Timer Id :",
                       enTimerId);

        return;
    }

    /* 在队列增加相应的信息，分配内存，进行信息赋值 */
    pulMsgBuf = (VOS_UINT32 *)PS_MEM_ALLOC(WUEPS_PID_TAF, ulMsgInfoLen);
    if (VOS_NULL_PTR == pulMsgBuf)
    {
        /* 缓存队列已满 */
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_SaveInfoInWaitL4aCnfMsgQueue, Mem Alloc Fail, Timer Id :",
                       enTimerId);
        return;
    }

    /* 赋值 */
    PS_MEM_CPY((VOS_UINT8 *)pulMsgBuf, (VOS_UINT8 *)pulMsgInfo, ulMsgInfoLen);
    pstCmdBufferQueue[i].pulMsgInfo     = pulMsgBuf;
    pstCmdBufferQueue[i].enTimerId      = enTimerId;
    pstCmdBufferQueue[i].ulMsgInfoLen   = ulMsgInfoLen;
    pstCmdBufferQueue[i].ulPara         = ulPara;
    return;
}


TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetItemFromCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    VOS_UINT32                          i;
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue;


    pstCmdBufferQueue = TAF_APS_GetCmdBufferQueueAddr();

    /* 遍历队列, 获取enTimerId指定的消息节点 */
    for ( i = 0 ; i < TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if ((enTimerId == pstCmdBufferQueue[i].enTimerId)
         && (ulPara == pstCmdBufferQueue[i].ulPara))
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if ( i >= TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* 未找到 */
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_GetInfoFromWaitL4aCnfMsgQueue, Msg Not Found, Timer Id :",
                       enTimerId);

        return VOS_NULL_PTR;
    }

    /* 将缓存的消息指针返回 */
    return &pstCmdBufferQueue[i];
}


VOS_VOID  TAF_APS_SetCurrPdpEntityMainFsmState(
    VOS_UINT32                          ulState
)
{
    VOS_UINT8                           ucPreCallExistFlg;

    g_stTafApsCtx.pstCurrPdpEntityFsmCtx->stMainFsm.ulState = ulState;

    ucPreCallExistFlg = g_stTafApsCtx.pstCurrPdpEntityFsmCtx->ucCallActiveFlg;

    switch (ulState)
    {
        case TAF_APS_STA_INACTIVE:
            g_stTafApsCtx.pstCurrPdpEntityFsmCtx->ucCallActiveFlg = VOS_FALSE;
            if (VOS_TRUE == ucPreCallExistFlg)
            {
                TAF_APS_SndStkPsCallEvent();
            }
            break;

        case TAF_APS_STA_ACTIVE:
            g_stTafApsCtx.pstCurrPdpEntityFsmCtx->ucCallActiveFlg = VOS_TRUE;
            if (VOS_FALSE == ucPreCallExistFlg)
            {
                TAF_APS_SndStkPsCallEvent();
            }
            break;

        default:
            break;
    }

    /*  打印当前的L1和L2状态 */

    return;
}


VOS_VOID  TAF_APS_SetCurrPdpEntitySubFsmState(
    VOS_UINT32                          ulState
)
{
    g_stTafApsCtx.pstCurrPdpEntityFsmCtx->stSubFsm.ulState = ulState;

    /*  打印当前的L1和L2状态 */

    return;
}


VOS_UINT32  TAF_APS_SetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
)
{
    return g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId].stMainFsm.ulState = ulState;
}



VOS_UINT32  TAF_APS_GetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId
)
{
    return g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId].stMainFsm.ulState;
}


VOS_UINT32  TAF_APS_CheckPdpServiceActivated(
    VOS_UINT8                          ucPdpId
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 检查NSAPI标记, 如果已经未标记, 代表当前的APS实体未激活 */
    if (VOS_FALSE == pstPdpEntity->PdpNsapiFlag)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32  TAF_APS_SetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
)
{
    return g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId].stSubFsm.ulState = ulState;
}


VOS_UINT32  TAF_APS_GetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId
)
{
    return g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId].stSubFsm.ulState;

}



VOS_VOID  TAF_APS_InitMainFsmCtx(
    TAF_APS_MAIN_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId    = TAF_APS_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc = TAF_APS_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState    = TAF_APS_STA_INACTIVE;
}


VOS_VOID  TAF_APS_InitSubFsmCtx(
    TAF_APS_SUB_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId    = TAF_APS_FSM_BUTT;
    pstCurrFsmCtx->pstFsmDesc = VOS_NULL_PTR;
    PS_MEM_SET(&pstCurrFsmCtx->stEntryMsg,
               0,
               sizeof(pstCurrFsmCtx->stEntryMsg));

}



VOS_VOID TAF_APS_InitSubFsm(
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_APS_SUB_FSM_CTX_STRU         *pstCurrSubFsm         = VOS_NULL_PTR;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU  *pstCurPdpEntityFsmCtx = VOS_NULL_PTR;

    /*  获取当前的Sub状态机 */
    pstCurPdpEntityFsmCtx = TAF_APS_GetCurrPdpEntityFsmAddr();
    pstCurrSubFsm         = &pstCurPdpEntityFsmCtx->stSubFsm;

    /* 设置当前Sub状态机状态机名 */
    pstCurrSubFsm->enFsmId     = enFsmId;

    /* 设置当前Sub状态机的PDP ID */
    pstCurrSubFsm->pstFsmDesc  = pstFsmDesc;

    /* 设置当前Sub状态机的状态 */
    pstCurrSubFsm->ulState     = ulState;

    /* 初始化Sub状态机 */
    /* pstCurrSubFsm->pstFsmDesc->pfInitHandle(); */

    /* 打印当前的Sub和Main状态机 */
    /* TAF_APS_LogMmcFsmInfo(); */
}


VOS_VOID TAF_APS_QuitCurrSubFsm( VOS_VOID )
{
    TAF_APS_SUB_FSM_CTX_STRU         *pstCurrSubFsm         = VOS_NULL_PTR;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU  *pstCurPdpEntityFsmCtx = VOS_NULL_PTR;

    /*  获取当前的L2状态状态机 */
    pstCurPdpEntityFsmCtx = TAF_APS_GetCurrPdpEntityFsmAddr();
    pstCurrSubFsm         = &pstCurPdpEntityFsmCtx->stSubFsm;

    /* 清空层二状态机描述表 */
    pstCurrSubFsm->pstFsmDesc  = VOS_NULL_PTR;

    /* 清空当前L2状态机ID */
    pstCurrSubFsm->enFsmId     = TAF_APS_FSM_BUTT;

}



VOS_VOID  TAF_APS_InitInternalBuffer(
    TAF_APS_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    pstBufferEntryMsgQueue->ucCurrIndex     = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(pstBufferEntryMsgQueue->astMsgQueue));
}


TAF_APS_ENTRY_MSG_STRU* TAF_APS_GetCurrSubFsmMsgAddr(VOS_VOID)
{
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstCurPdpEntityFsmCtx = VOS_NULL_PTR;

    /*  获取当前的L1状态机和L2状态状态机 */
    pstCurPdpEntityFsmCtx = TAF_APS_GetCurrPdpEntityFsmAddr();

    return &(pstCurPdpEntityFsmCtx->stSubFsm.stEntryMsg);
}


VOS_VOID TAF_APS_SaveCurrSubFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理入口消息的缓冲区地址 */
    /* 获得当前处理APS入口消息的缓冲区地址 */
    pstEntryMsg                 =   TAF_APS_GetCurrSubFsmMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        TAF_WARNING_LOG( WUEPS_PID_TAF, "TAF_APS_SaveCurrSubFsmEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen  = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}


VOS_VOID  TAF_APS_SetCurrFsmEntityPdpId(
    VOS_UINT8                           ucPdpId
)
{
    g_stTafApsCtx.pstCurrPdpEntityFsmCtx->ucPdpId = ucPdpId;
}


VOS_UINT8  TAF_APS_GetCurrFsmEntityPdpId( VOS_VOID )
{
    return g_stTafApsCtx.pstCurrPdpEntityFsmCtx->ucPdpId;
}




VOS_VOID  TAF_APS_SetCurrPdpEntitySimRegStatus(
    VOS_UINT32                          ulPsSimRegStatus
)
{
    /* TODO:合入主线前修改函数名称，下同 */
    g_stTafApsCtx.ulPsSimRegStatus = ulPsSimRegStatus;

}


VOS_UINT32  TAF_APS_GetCurrPdpEntitySimRegStatus( VOS_VOID )
{

    return g_stTafApsCtx.ulPsSimRegStatus;


}


VOS_VOID  TAF_APS_SetCurrPdpEntityRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
)
{
    /* TODO:合入主线前，修改函数名称，下同 */
    g_stTafApsCtx.enCurrRatType = enRatType;
}


TAF_APS_RAT_TYPE_ENUM_UINT32  TAF_APS_GetCurrPdpEntityRatType( VOS_VOID )
{

    return g_stTafApsCtx.enCurrRatType;

}




VOS_VOID  TAF_APS_SetCurrPdpEntityDataServiceMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
)
{
    g_stTafApsCtx.enDataServiceMode = enRatType;
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetCurrPdpEntityDataServiceMode(VOS_VOID)
{
    return g_stTafApsCtx.enDataServiceMode;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_APS_FillL4aSdfParaApnInfo(
    APS_L4A_SDF_PARA_STRU       *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU          *pstTafCidInfo
)
{
    if (0 == pstTafCidInfo->CidTab.stApn.ucLength)
    {
        pstSdfParaInfo->bitOpApn    = VOS_FALSE;
    }
    else
    {
        pstSdfParaInfo->bitOpApn    = VOS_TRUE;
        pstSdfParaInfo->stApnInfo.ucApnLen  = pstTafCidInfo->CidTab.stApn.ucLength;
        PS_MEM_CPY(pstSdfParaInfo->stApnInfo.aucApnName,
                   pstTafCidInfo->CidTab.stApn.aucValue,
                   pstSdfParaInfo->stApnInfo.ucApnLen);
    }
}


VOS_VOID TAF_APS_FillL4aSdfParaSdfQosInfo(
    APS_L4A_SDF_PARA_STRU       *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU          *pstTafCidInfo
)
{
    if (VOS_FALSE == pstTafCidInfo->ucEpsQosInfoFlg)
    {
        pstSdfParaInfo->bitOpSdfQos             = VOS_FALSE;
    }
    else
    {
        pstSdfParaInfo->bitOpSdfQos             = VOS_TRUE;
        pstSdfParaInfo->stSdfQosInfo.ucQCI      = pstTafCidInfo->stEpsQosInfo.ucQCI;
        pstSdfParaInfo->stSdfQosInfo.ulDLGBR    = pstTafCidInfo->stEpsQosInfo.ulDLGBR;
        pstSdfParaInfo->stSdfQosInfo.ulULGBR    = pstTafCidInfo->stEpsQosInfo.ulULGBR;
        pstSdfParaInfo->stSdfQosInfo.ulDLMBR    = pstTafCidInfo->stEpsQosInfo.ulDLMBR;
        pstSdfParaInfo->stSdfQosInfo.ulULMBR    = pstTafCidInfo->stEpsQosInfo.ulULMBR;
    }
}


VOS_VOID TAF_APS_FillL4aSdfParaAuthInfo(
    APS_L4A_SDF_PARA_STRU              *pstSdfParaInfo,
    VOS_UINT8                           ucCid
)
{
    if ( (VOS_TRUE == g_ApsNdisAuthdataTab[ucCid].ucUsed)
      && ( (TAF_PDP_AUTH_TYPE_PAP        == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        || (TAF_PDP_AUTH_TYPE_CHAP       == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        || (TAF_PDP_AUTH_TYPE_PAP_OR_CHAP == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType) ) )
    {
        pstSdfParaInfo->bitOpGwAuthInfo                 = VOS_TRUE;

        /* 鉴权类型 */
        if (TAF_PDP_AUTH_TYPE_PAP  == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        {
            pstSdfParaInfo->stGwAuthInfo.enGwAuthType   = APS_L4A_GW_AUTH_TYPE_PAP;
        }
        else
        {
            pstSdfParaInfo->stGwAuthInfo.enGwAuthType   = APS_L4A_GW_AUTH_TYPE_CHAP;
        }

        /* Access Number参数保留暂不使用 */
        pstSdfParaInfo->stGwAuthInfo.ucAccNumLen        = 0;

        /* 用户名 */
        pstSdfParaInfo->stGwAuthInfo.ucUserNameLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername);
        if (0 != pstSdfParaInfo->stGwAuthInfo.ucUserNameLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->stGwAuthInfo.aucUserName,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                       pstSdfParaInfo->stGwAuthInfo.ucUserNameLen);
        }

        /* 密码 */
        pstSdfParaInfo->stGwAuthInfo.ucPwdLen           = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword);
        if (0 != pstSdfParaInfo->stGwAuthInfo.ucPwdLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->stGwAuthInfo.aucPwd,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                       pstSdfParaInfo->stGwAuthInfo.ucPwdLen);
        }
    }
    else
    {
        pstSdfParaInfo->bitOpGwAuthInfo                 = VOS_FALSE;
    }
}


VOS_UINT32 TAF_APS_GetCidSdfParaInfo(
    VOS_UINT8                           ucCid,
    APS_L4A_SDF_PARA_STRU              *pstSdfParaInfo
)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;

    if (ucCid > TAF_MAX_CID)
    {
        TAF_PS_ERR_LOG("TAF_APS_GetCidSdfParaInfo: CID is invalid.");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 全网通版本，VIA不使用CID 0 作为默认承载，因此在CL工作模式下CID0 返回ERROR，不使用 */
    if ((VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside()) && (TAF_APS_DEFAULT_CID == ucCid))
    {
        TAF_PS_NORM_LOG("TAF_APS_GetCidSdfParaInfo: CID 0 is passed in CL interwork mode!");
        return VOS_ERR;
    }
#endif

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);

    /* CID */
    pstSdfParaInfo->ulCid = ucCid;

    if (VOS_FALSE != pstTafCidInfo->ucUsed)
    {
        /* PdpType */
        if (TAF_PDP_PPP == pstTafCidInfo->CidTab.stPdpAddr.enPdpType)
        {
            /* PPP拨号类型直接返回VOS_ERR */
            return VOS_ERR;
        }

        /* Bearer Type & LinkdCID */
        if (VOS_FALSE == pstTafCidInfo->ucPriCidFlag)
        {
            pstSdfParaInfo->bitOpLinkdCId     = VOS_FALSE;
            pstSdfParaInfo->enBearerCntxtType = APS_L4A_BEARER_TYPE_DEFAULT;

            pstSdfParaInfo->bitOpPdnType      = VOS_TRUE;
            pstSdfParaInfo->enPdnType         = pstTafCidInfo->CidTab.stPdpAddr.enPdpType;
        }
        else
        {
            pstSdfParaInfo->bitOpLinkdCId     = VOS_TRUE;
            pstSdfParaInfo->ulLinkdCid        = pstTafCidInfo->ucPriCid;
            pstSdfParaInfo->enBearerCntxtType = APS_L4A_BEARER_TYPE_DEDICATED;

            pstSdfParaInfo->bitOpPdnType      = VOS_FALSE;
        }

        /* Ipv4AddrAllocType */
        pstSdfParaInfo->bitIpv4AddrAllocType = VOS_TRUE;
        pstSdfParaInfo->enIpv4AddrAllocType  = pstTafCidInfo->CidTab.enIpv4AddrAlloc;

        /* APN */
        TAF_APS_FillL4aSdfParaApnInfo(pstSdfParaInfo, pstTafCidInfo);

    }
    else
    {
        return VOS_ERR;
    }

    /* EPS QOS */
    TAF_APS_FillL4aSdfParaSdfQosInfo(pstSdfParaInfo, pstTafCidInfo);

    /* AuthInfo */
    TAF_APS_FillL4aSdfParaAuthInfo(pstSdfParaInfo, ucCid);

    pstSdfParaInfo->bitOpEmergencyInd   = VOS_TRUE;
    pstSdfParaInfo->enEmergencyInd      = pstTafCidInfo->CidTab.enEmergencyInd;

    pstSdfParaInfo->bitOpImsCnSignalFlag = VOS_TRUE;
    pstSdfParaInfo->enImsCnSignalFlag    = pstTafCidInfo->CidTab.enImCnSignalFlg;

    pstSdfParaInfo->bitOpPcscfDiscovery = VOS_TRUE;
    pstSdfParaInfo->enPcscfDiscovery    = pstTafCidInfo->CidTab.enPcscfDiscovery;

    /* TFT */
    if (VOS_FALSE != pstTafCidInfo->ucPfTabFlag)
    {
        pstSdfParaInfo->ulPfNum = pstTafCidInfo->ucPfNum;
        PS_MEM_CPY(pstSdfParaInfo->astCntxtTftInfo,
                   pstTafCidInfo->astPfTab,
                   (TAF_MAX_SDF_PF_NUM * sizeof(TAF_PDP_PF_STRU)));

    }

    pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();

    if (VOS_TRUE == pstCidImsCfgTbl->aucImsFlag[ucCid])
    {
        pstSdfParaInfo->bitImsSuppFlag  = VOS_TRUE;
        pstSdfParaInfo->enImsSuppFlag   = VOS_TRUE;
    }

    return VOS_OK;
}


VOS_UINT8 TAF_APS_GetCidImsCfgFlag(VOS_UINT8 ucCid)
{
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;

    if (ucCid > TAF_MAX_CID)
    {
        return VOS_FALSE;
    }

    pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();

    if (VOS_TRUE == pstCidImsCfgTbl->aucImsFlag[ucCid])
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_GetPdpManageInfo(
    APS_L4A_PDP_MANAGE_INFO_STRU       *pstPdpManageInfo
)
{
    /* 从全局变量中获取PDP管理模式 */
    if (TAF_PDP_ANSWER_MODE_AUTO == g_PsAnsMode.enAnsMode)
    {
        pstPdpManageInfo->enMode = APS_L4A_BEARER_MANAGE_MODE_AUTO;
    }
    else
    {
        pstPdpManageInfo->enMode = APS_L4A_BEARER_MANAGE_MODE_MANUAL;
    }

    if (TAF_PDP_ANSWER_TYPE_ACCEPT == g_PsAnsMode.enAnsType)
    {
        pstPdpManageInfo->enType = APS_L4A_BEARER_MANAGE_TYPE_ACCEPT;
    }
    else
    {
        pstPdpManageInfo->enType = APS_L4A_BEARER_MANAGE_TYPE_REJ;
    }

    return VOS_OK;
}

#endif


TAF_APS_CONTEXT_STRU*  TAF_APS_GetApsCtxAddr( VOS_VOID )
{
    return &(g_stTafApsCtx);
}


TAF_APS_PDP_ENTITY_FSM_CTX_STRU*  TAF_APS_GetApsEntityFsmCtxAddr(
    VOS_UINT8                           ucPdpId
)
{
    return &g_stTafApsCtx.astPdpEntityFsmCtx[ucPdpId];
}



VOS_VOID  TAF_APS_InitInternalMsgQueue(
    TAF_APS_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM子层的内部消息队列 */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < TAF_APS_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astApsMsgQueue[i].usMsgID    = TAF_APS_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astApsMsgQueue[i].aucBuf,
                   0x00,
                   TAF_APS_MAX_MSG_BUFFER_LEN);
    }

}


TAF_APS_INTERNAL_MSG_BUF_STRU* TAF_APS_GetNextInternalMsg( VOS_VOID )
{
    TAF_APS_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;
    TAF_APS_CONTEXT_STRU               *pstApsCtx  =  VOS_NULL_PTR;

    pstApsCtx   = TAF_APS_GetApsCtxAddr();

    if ( pstApsCtx->stInternalMsgQueue.ucHeader != pstApsCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstApsCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (TAF_APS_INTERNAL_MSG_BUF_STRU *)&(pstApsCtx->stInternalMsgQueue.astApsMsgQueue[ucNextIndex]);

        /* 取完一条消息,头指针向后偏移 */
        (pstApsCtx->stInternalMsgQueue.ucHeader)++;
        (pstApsCtx->stInternalMsgQueue.ucHeader) %= TAF_APS_MAX_MSG_QUEUE_SIZE;
        return pstNextMsg;
    }

    TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_APS_GetNextInternalMsg:Empty Internal Msg");
    return VOS_NULL_PTR;

}


TAF_APS_INTERNAL_MSG_BUF_STRU *TAF_APS_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    TAF_APS_INTERNAL_MSG_BUF_STRU      *pstTafApsMsg        = VOS_NULL_PTR;
    TAF_APS_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(TAF_APS_GetApsCtxAddr()->stInternalMsgQueue);

    /* 从上下文中获取消息缓冲区指针 */
    pstTafApsMsg = ( TAF_APS_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if ( ulLen > TAF_APS_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_GetIntMsgSendBuf: Buffer full" );
        return VOS_NULL_PTR;
    }

    /* 清空这个消息缓冲单元 */
    PS_MEM_SET(pstTafApsMsg, 0x00, sizeof(TAF_APS_INTERNAL_MSG_BUF_STRU));

    /* 返回缓冲区指针 */
    return pstTafApsMsg;
}


VOS_UINT32  TAF_APS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    TAF_APS_INTERNAL_MSG_BUF_STRU      *pstApsMsg           = VOS_NULL_PTR;
    TAF_APS_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    TAF_APS_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(TAF_APS_GetApsCtxAddr()->stInternalMsgQueue);
    pstSndMsg                           = (TAF_APS_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % TAF_APS_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SndInternalMsg:Warning: The Queue is full.");
        return VOS_ERR;
    }

    /* 2. 取得一个消息缓冲单元 */
    pstApsMsg = (TAF_APS_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astApsMsgQueue[ucMsgPnt]);

    /* 3. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > TAF_APS_MAX_MSG_BUFFER_LEN)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMC, "TAF_APS_SndInternalMsg:Warning: ulBufLen is too long.");
        return VOS_ERR;
    }

    TAF_NORMAL_LOG1(WUEPS_PID_TAF, "TAF_APS_SndInternalMsg: usMsgID is ", pstApsMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列中 */
    PS_MEM_CPY(pstApsMsg, pstSndMsg, sizeof(TAF_APS_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= TAF_APS_MAX_MSG_QUEUE_SIZE;

    return VOS_OK;
}


VOS_VOID TAF_APS_InitPdpActLimitInfo(VOS_VOID)
{
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo = VOS_NULL_PTR;

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    /* 初始化PDP激活限制功能开启flag */
    pstPdpActLimitInfo->ucPdpActLimitFlg  = VOS_FALSE;

    /* 初始化激活失败次数计数器 */
    pstPdpActLimitInfo->ucPdpActFailCount = 0;

    /* 先对flag初始化，再读取nv项值 */
    TAF_APS_ReadPdpActLimitFlgFromNv();

    return;
}


TAF_APS_PDP_ACT_LIMIT_INFO_STRU* TAF_APS_GetPdpActLimitInfoAddr(VOS_VOID)
{
    return &(g_stTafApsCtx.stPdpActLimitInfo);
}



VOS_VOID TAF_APS_FillSdfParaApnInfo(
    TAF_SDF_PARA_STRU           *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU          *pstTafCidInfo
)
{
    if (0 == pstTafCidInfo->CidTab.stApn.ucLength)
    {
        pstSdfParaInfo->bitOpApn    = VOS_FALSE;
    }
    else
    {
        pstSdfParaInfo->bitOpApn    = VOS_TRUE;
        pstSdfParaInfo->stApnInfo.ucLength  = pstTafCidInfo->CidTab.stApn.ucLength;
        PS_MEM_CPY(pstSdfParaInfo->stApnInfo.aucValue,
                   pstTafCidInfo->CidTab.stApn.aucValue,
                   pstSdfParaInfo->stApnInfo.ucLength);
    }
}


VOS_VOID TAF_APS_FillSdfParaSdfQosInfo(
    TAF_SDF_PARA_STRU           *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU          *pstTafCidInfo
)
{
    if (VOS_FALSE == pstTafCidInfo->ucEpsQosInfoFlg)
    {
        pstSdfParaInfo->bitOpEpsQos             = VOS_FALSE;
    }
    else
    {
        pstSdfParaInfo->bitOpEpsQos             = VOS_TRUE;
        pstSdfParaInfo->stEpsQosInfo.ucQCI      = pstTafCidInfo->stEpsQosInfo.ucQCI;
        pstSdfParaInfo->stEpsQosInfo.ulDLGBR    = pstTafCidInfo->stEpsQosInfo.ulDLGBR;
        pstSdfParaInfo->stEpsQosInfo.ulULGBR    = pstTafCidInfo->stEpsQosInfo.ulULGBR;
        pstSdfParaInfo->stEpsQosInfo.ulDLMBR    = pstTafCidInfo->stEpsQosInfo.ulDLMBR;
        pstSdfParaInfo->stEpsQosInfo.ulULMBR    = pstTafCidInfo->stEpsQosInfo.ulULMBR;
    }
}


VOS_VOID TAF_APS_FillSdfParaAuthInfo(
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo,
    VOS_UINT8                           ucCid
)
{
    if ( (VOS_TRUE == g_ApsNdisAuthdataTab[ucCid].ucUsed)
      && ( (TAF_PDP_AUTH_TYPE_PAP        == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        || (TAF_PDP_AUTH_TYPE_CHAP       == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        || (TAF_PDP_AUTH_TYPE_PAP_OR_CHAP == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType) ) )
    {
        pstSdfParaInfo->bitOpGwAuthInfo                 = VOS_TRUE;

        /* 鉴权类型 */
        if (TAF_PDP_AUTH_TYPE_PAP  == g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType)
        {
            pstSdfParaInfo->stGwAuthInfo.enAuthType     = TAF_PDP_AUTH_TYPE_PAP;
        }
        else
        {
            pstSdfParaInfo->stGwAuthInfo.enAuthType     = TAF_PDP_AUTH_TYPE_CHAP;
        }

        /* Access Number参数保留暂不使用 */
        pstSdfParaInfo->stGwAuthInfo.ucAccNumLen        = 0;

        /* 用户名 */
        pstSdfParaInfo->stGwAuthInfo.ucUserNameLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername);
        if (0 != pstSdfParaInfo->stGwAuthInfo.ucUserNameLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->stGwAuthInfo.aucUserName,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                       pstSdfParaInfo->stGwAuthInfo.ucUserNameLen);
        }

        /* 密码 */
        pstSdfParaInfo->stGwAuthInfo.ucPwdLen           = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword);
        if (0 != pstSdfParaInfo->stGwAuthInfo.ucPwdLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->stGwAuthInfo.aucPwd,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                       pstSdfParaInfo->stGwAuthInfo.ucPwdLen);
        }
    }
    else
    {
        pstSdfParaInfo->bitOpGwAuthInfo                 = VOS_FALSE;
    }
}

VOS_UINT32 TAF_APS_GetSdfParaInfo(
    VOS_UINT8                           ucCid,
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo
)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;

    if (ucCid > TAF_MAX_CID_NV)
    {
        TAF_PS_ERR_LOG("TAF_APS_GetCSdfParaInfo: CID is invalid.");
        return VOS_ERR;
    }

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);

    if (VOS_FALSE == pstTafCidInfo->ucUsed)
    {
        return VOS_ERR;
    }

    /* CID */
    pstSdfParaInfo->ucCid = ucCid;

    /* PdpType */
    if (TAF_PDP_PPP == pstTafCidInfo->CidTab.stPdpAddr.enPdpType)
    {
        /* PPP拨号类型直接返回VOS_ERR */
        return VOS_ERR;
    }

    /* LinkdCID */
    if (VOS_FALSE == pstTafCidInfo->ucPriCidFlag)
    {
        pstSdfParaInfo->bitOpLinkdCid     = VOS_FALSE;
        pstSdfParaInfo->bitOpPdnType      = VOS_TRUE;
        pstSdfParaInfo->enPdnType         = pstTafCidInfo->CidTab.stPdpAddr.enPdpType;
    }
    else
    {
        pstSdfParaInfo->bitOpLinkdCid     = VOS_TRUE;
        pstSdfParaInfo->ucLinkdCid        = pstTafCidInfo->ucPriCid;
        pstSdfParaInfo->bitOpPdnType      = VOS_FALSE;
    }

    /* Ipv4AddrAllocType */
    pstSdfParaInfo->bitOpIpv4AddrAllocType= VOS_TRUE;
    pstSdfParaInfo->enIpv4AddrAllocType   = pstTafCidInfo->CidTab.enIpv4AddrAlloc;

    /* APN */
    TAF_APS_FillSdfParaApnInfo(pstSdfParaInfo, pstTafCidInfo);

    pstSdfParaInfo->bitOpEmergencyInd   = VOS_TRUE;
    pstSdfParaInfo->enEmergencyInd      = pstTafCidInfo->CidTab.enEmergencyInd;

    pstSdfParaInfo->bitOpImCnSignalFlg  = VOS_TRUE;
    pstSdfParaInfo->enImCnSignalFlg     = pstTafCidInfo->CidTab.enImCnSignalFlg;

    pstSdfParaInfo->bitOpPcscfDiscovery = VOS_TRUE;
    pstSdfParaInfo->enPcscfDiscovery    = pstTafCidInfo->CidTab.enPcscfDiscovery;

    /* EPS QOS */
    TAF_APS_FillSdfParaSdfQosInfo(pstSdfParaInfo, pstTafCidInfo);

    /* AuthInfo */
    TAF_APS_FillSdfParaAuthInfo(pstSdfParaInfo, ucCid);

    /* Umts Qos */
    if (VOS_TRUE == pstTafCidInfo->ucQosTabFlag)
    {
        pstSdfParaInfo->bitOpUmtsQos    = VOS_TRUE;
        pstSdfParaInfo->stUmtsQosInfo   = pstTafCidInfo->QosTab;
    }
    /* TFT */
    if (VOS_FALSE != pstTafCidInfo->ucPfTabFlag)
    {
        pstSdfParaInfo->ucPfNum = pstTafCidInfo->ucPfNum;
        PS_MEM_CPY(pstSdfParaInfo->astCntxtTftInfo,
                   pstTafCidInfo->astPfTab,
                   (TAF_MAX_SDF_PF_NUM * sizeof(TAF_PDP_PF_STRU)));
    }

    pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();
    if (VOS_TRUE == pstCidImsCfgTbl->aucImsFlag[ucCid])
    {
        pstSdfParaInfo->bitOpImsSuppFlg = VOS_TRUE;
        pstSdfParaInfo->ucImsSuppFlg    = VOS_TRUE;
    }

    return VOS_OK;
}



VOS_VOID TAF_APS_InitCallRemainTmrLen(VOS_VOID)
{
    TAF_APS_CONTEXT_STRU               *pstTafApsCtx;

    pstTafApsCtx   = TAF_APS_GetApsCtxAddr();
    PS_MEM_SET(pstTafApsCtx->aulCallRemainTmrLen, 0x00, sizeof(pstTafApsCtx->aulCallRemainTmrLen));
    return;
}


VOS_VOID TAF_APS_SetCallRemainTmrLen(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulTmrLen
)
{
    TAF_APS_CONTEXT_STRU               *pstTafApsCtx;

    pstTafApsCtx = TAF_APS_GetApsCtxAddr();
    pstTafApsCtx->aulCallRemainTmrLen[ucCid] = ulTmrLen;
    return;
}


VOS_UINT32 TAF_APS_GetCallRemainTmrLen(VOS_UINT8 ucCid)
{
    TAF_APS_CONTEXT_STRU               *pstTafApsCtx;

    pstTafApsCtx = TAF_APS_GetApsCtxAddr();
    return pstTafApsCtx->aulCallRemainTmrLen[ucCid];
}


VOS_VOID  TAF_APS_SetApsDmtTestStub(
    VOS_UINT32                          ulEnable
)
{
    g_ulApsTestStub = ulEnable;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_APS_InitPdnTeardownPolicy(VOS_VOID)
{
    TAF_APS_PDN_TEARDOWN_POLICY_STRU   *pstPdnTeardownPolicy = VOS_NULL_PTR;

    pstPdnTeardownPolicy = TAF_APS_GetPdnTeardownPolicy();
    pstPdnTeardownPolicy->ucAllowDefPdnTeardownFlg = VOS_FALSE;

    TAF_APS_ReadPdnTeardownPolicyNV();
    return;
}


TAF_APS_PDN_TEARDOWN_POLICY_STRU* TAF_APS_GetPdnTeardownPolicy(VOS_VOID)
{
    return &(TAF_APS_GetApsCtxAddr()->stPdnTeardownPolicy);
}


VOS_UINT8 TAF_APS_GetAllowDefPdnTeardownFlg(VOS_VOID)
{
    return TAF_APS_GetPdnTeardownPolicy()->ucAllowDefPdnTeardownFlg;
}


VOS_VOID TAF_APS_SetAllowDefPdnTeardownFlg(VOS_UINT8 ucAllowFlg)
{
    TAF_APS_GetPdnTeardownPolicy()->ucAllowDefPdnTeardownFlg = ucAllowFlg;
    return;
}
#endif


TAF_APS_CID_IMS_CFG_TBL_STRU* TAF_APS_GetCidImsCfgTable(VOS_VOID)
{
    return &g_stCidImsCfgTable;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 TAF_APS_IsEnterCdataEsting(VOS_VOID)
{

    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;


    /* 如果当前不为内部支持CDMA模式，则不进CDATA_ESTING状态机 */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_FALSE;
    }

    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();

    /* 当前为1X/EVDO/NULL状态，优先进CDATA_ESTING状态机处理 */
    if ((TAF_APS_RAT_TYPE_1X    == enCurrRatType)
     || (TAF_APS_RAT_TYPE_HRPD  == enCurrRatType)
     || (TAF_APS_RAT_TYPE_EHRPD == enCurrRatType)
     || (TAF_APS_RAT_TYPE_NULL  == enCurrRatType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_IsEnterCdataDiscing(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrDataSerMode;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    enCurrDataSerMode   = TAF_APS_GetCurrPdpEntityDataServiceMode();

    enRatType           = TAF_APS_GetCurrPdpEntityRatType();

    /* 当前建立数据业务的为1X/HRPD/EHPRD模式，则进CDATA_DISCING状态机处理 */
    /* 当前数据业务在其它模式，但是接入技术已经切换到EHRPD */
    if ((TAF_APS_RAT_TYPE_1X    == enCurrDataSerMode)
     || (TAF_APS_RAT_TYPE_HRPD  == enCurrDataSerMode)
     || (TAF_APS_RAT_TYPE_EHRPD == enCurrDataSerMode)
     || (TAF_APS_RAT_TYPE_EHRPD == enRatType))
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_GetSocmDormantTiLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.ulSocmDormTiVal;
}


VOS_VOID TAF_APS_SetSocmDormantTiLen(
    VOS_UINT32                          ulDormantTiLen
)
{
    g_stTafApsCtx.stCdataCtx.ulSocmDormTiVal = ulDormantTiLen;
}


VOS_VOID TAF_APS_SetCdataPppDeactTimerLen(
    VOS_UINT8                           ucPppDeactTiLen
)
{
    g_stTafApsCtx.stCdataCtx.ulPppDeactTimerLen = (ucPppDeactTiLen) * 1000;

    return;
}


VOS_UINT32 TAF_APS_GetCdataPppDeactTimerLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.ulPppDeactTimerLen;
}



VOS_UINT8 TAF_APS_GetEhrpdAutoAttachFlag(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.ucEhrpdAutoAttachFlag;
}


VOS_VOID TAF_APS_SetEhrpdAutoAttachFlag(
    VOS_UINT8                           ucAutoAttachFlag
)
{
    g_stTafApsCtx.stCdataCtx.ucEhrpdAutoAttachFlag = ucAutoAttachFlag;

    return;
}


VOS_UINT32 TAF_APS_GetUserCfgDormTiVal(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.ulUserCfgDormTival;
}


VOS_VOID TAF_APS_SetUserCfgDormTiVal(
    VOS_UINT32                          ulUserCfgDormTival
)
{
    g_stTafApsCtx.stCdataCtx.ulUserCfgDormTival = ulUserCfgDormTival;
}


VOS_VOID TAF_APS_InitCdataCtx( VOS_VOID )
{
    PS_MEM_SET(&g_stTafApsCtx.stCdataCtx, 0, sizeof(TAF_APS_CDATA_CTX_STRU));

    g_stTafApsCtx.stCdataCtx.enCdataDialMode = TAF_PS_CDATA_DIAL_MODE_NETWORK;

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_BUTT);

    TAF_APS_Read1xDataSoCfgNvim();

    TAF_APS_ReadPktCdataInactivityTimeLenFromNv();

    TAF_APS_ReadCdataDiscingParaCfgFromNv();

    TAF_APS_ReadPppAuthInfoFromCardNv();

    TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv();

    TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv();

    TAF_APS_InitEpdszidCtx();
}


VOS_VOID TAF_APS_SetPktCdataInactivityTimerLen(
    VOS_UINT8                           ucTimeLen
)
{
    TAF_APS_GetApsCtxAddr()->stCdataCtx.ucPktCdataInactivityTmrLen = ucTimeLen;

    return;
}


VOS_UINT8 TAF_APS_GetPktCdataInactivityTimerLen()
{
    VOS_UINT8                           ucTimeLen;

    ucTimeLen = TAF_APS_GetApsCtxAddr()->stCdataCtx.ucPktCdataInactivityTmrLen;

    return ucTimeLen;
}





VOS_VOID TAF_APS_SetFsmCtxCdataDialMode(
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
)
{
    g_stTafApsCtx.stCdataCtx.enCdataDialMode = enDialMode;
}


TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataDialMode( VOS_VOID )
{
    return g_stTafApsCtx.stCdataCtx.enCdataDialMode;
}



VOS_VOID  TAF_APS_Set1XPsServiceStatus(
    VOS_UINT32                          ulExist
)
{
    g_stTafApsCtx.ulExist1XService = ulExist;
}


VOS_UINT32  TAF_APS_Get1XPsServiceStatus(VOS_VOID)
{
    return g_stTafApsCtx.ulExist1XService;
}


VOS_VOID TAF_APS_FillEhsmSdfParaApnInfo(
    APS_EHSM_SDF_PARA_INFO_STRU         *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU                  *pstTafCidInfo
)
{
    if (0 == pstTafCidInfo->CidTab.stApn.ucLength)
    {
        pstSdfParaInfo->bitOpApn       = VOS_FALSE;
    }
    else
    {
        pstSdfParaInfo->bitOpApn       = VOS_TRUE;
        pstSdfParaInfo->stApn.ulLength = pstTafCidInfo->CidTab.stApn.ucLength;
        PS_MEM_CPY(pstSdfParaInfo->stApn.aucApn,
                   pstTafCidInfo->CidTab.stApn.aucValue,
                   pstSdfParaInfo->stApn.ulLength);
    }
}


VOS_VOID TAF_APS_FillEhsmSdfParaAuthInfo(
    APS_EHSM_SDF_PARA_INFO_STRU        *pstSdfParaInfo,
    VOS_UINT8                           ucCid
)
{
    if (VOS_TRUE == g_ApsNdisAuthdataTab[ucCid].ucUsed)
    {
        pstSdfParaInfo->bitOpAuthInfo = VOS_TRUE;

        pstSdfParaInfo->ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername);
        if (0 != pstSdfParaInfo->ucUserNameLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->aucUserName,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                       pstSdfParaInfo->ucUserNameLen);
        }

        pstSdfParaInfo->ucPwdLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword);
        if (0 != pstSdfParaInfo->ucPwdLen)
        {
            PS_MEM_CPY(pstSdfParaInfo->aucPwd,
                       g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                       pstSdfParaInfo->ucPwdLen);
        }

        pstSdfParaInfo->enAuthType    = g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType;
    }
    else
    {
        pstSdfParaInfo->bitOpAuthInfo = VOS_FALSE;
    }
}



VOS_UINT32 TAF_APS_GetCidSdfParaInfoForEhsm(
    VOS_UINT8                           ucCid,
    APS_EHSM_SDF_PARA_INFO_STRU        *pstSdfParaInfo
)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;

    if (ucCid > TAF_MAX_CID)
    {
        TAF_PS_ERR_LOG("TAF_APS_GetCidSdfParaInfoForEhsm: CID is invalid.");
        return VOS_FALSE;
    }

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);

    if (VOS_FALSE == pstTafCidInfo->ucUsed)
    {
        return VOS_FALSE;

    }
    else
    {
        /* CID */
        pstSdfParaInfo->ucCid           = ucCid;

        /* PdpType */
        pstSdfParaInfo->bitOpPdnType    = VOS_TRUE;
        pstSdfParaInfo->enPdnType       = pstTafCidInfo->CidTab.stPdpAddr.enPdpType;

        /* UserName , Password , Authtype */
        TAF_APS_FillEhsmSdfParaAuthInfo(pstSdfParaInfo, ucCid);

        /* APN */
        TAF_APS_FillEhsmSdfParaApnInfo(pstSdfParaInfo, pstTafCidInfo);

    }

    return VOS_TRUE;
}




VOS_UINT32  TAF_APS_GetClDelaySearch(VOS_VOID)
{
    return g_stTafApsCtx.ulClDelaySearch;
}


VOS_VOID  TAF_APS_SetClDelaySearch(
    VOS_UINT32                          ulClDelaySearch
)
{
    g_stTafApsCtx.ulClDelaySearch = ulClDelaySearch;
}


VOS_UINT32  TAF_APS_GetIsHrpdDisabledFlag(VOS_VOID)
{
    return g_stTafApsCtx.ulIsHrpdDisabled;
}


VOS_VOID  TAF_APS_SetIsHrpdDisabledFlag(
    VOS_UINT32                          ulIsHrpdDisabled
)
{
    g_stTafApsCtx.ulIsHrpdDisabled = ulIsHrpdDisabled;
}



VOS_VOID TAF_APS_SetFsmCtxCdataLastDialOnRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastOirgOnRatType
)
{
    g_stTafApsCtx.stCdataCtx.enLastOirgOnRatType = enLastOirgOnRatType;
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataLastDialOnRatType(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.enLastOirgOnRatType;
}


VOS_VOID TAF_APS_SetFsmCtxCdataSoInitType(
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSoInitType
)
{
    g_stTafApsCtx.stCdataCtx.enSoInitType = enSoInitType;
}


TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetFsmCtxCdataSoInitType (VOS_VOID)
{
    return TAF_APS_GetApsCtxAddr()->stCdataCtx.enSoInitType;
}


VOS_VOID TAF_APS_Init3GpdOpInfo(VOS_VOID)
{
    PS_MEM_SET(&g_stTafApsCtx.st3GpdOpInfo, 0, sizeof(TAF_APS_3GPD_OPERATION_INFO_STRU));

    g_stTafApsCtx.st3GpdOpInfo.ucTafAps3GdpCurrActSipNaiIndex                 = 0;

}

VOS_UINT32 TAF_APS_GetRead3GpdFileDoneFlag( VOS_VOID  )
{
    return g_stTafApsCtx.ulIsAlreadyRead3GpdFile;
}

VOS_VOID TAF_APS_SetRead3GpdFileDoneFlag(
    VOS_UINT32                          ulSimFileCnfFlg
)
{
    g_stTafApsCtx.ulIsAlreadyRead3GpdFile = ulSimFileCnfFlg;
}


TAF_APS_3GPD_OPERATION_INFO_STRU* TAF_APS_Get3GpdOpInfoAddr( VOS_VOID )
{
    return &g_stTafApsCtx.st3GpdOpInfo;
}

VOS_UINT32 TAF_APS_GetPppAuthInfoGetFromCardFlag( VOS_VOID )
{
    return g_stTafApsCtx.ulPppAuthInfFromCardFlag;
}

VOS_VOID TAF_APS_SetPppAuthInfoGetFromCardFlag(
    VOS_UINT32                          ulIsPppAuthGetFromCard
)
{
    g_stTafApsCtx.ulPppAuthInfFromCardFlag = ulIsPppAuthGetFromCard;
    return;
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
