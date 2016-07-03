

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasComm.h"
#include "MM_Ext.h"
#include "GmmExt.h"
#include "NasMmcMain.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndOm.h"
#include "NasUtranCtrlInterface.h"

#include "TafMmaMain.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:zhoujun \40661;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_MSGPROC_C
/*lint +e767 修改人:zhoujun \40661;原因:Log打印*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/
extern VOS_UINT32 WuepsMmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_UINT32 WuepsGmmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );



/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

NAS_MML_INTERNAL_MSG_BUF_STRU *NAS_MML_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNasMmlMsg        = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);

    /* 从上下文中获取消息缓冲区指针 */
    pstNasMmlMsg = ( NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if ( ulLen > NAS_MML_MAX_INTERNAL_MSG_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_GetIntMsgSendBuf: Buffer full" );
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return VOS_NULL_PTR;
    }

    /* 清空这个消息缓冲单元 */
    PS_MEM_SET(pstNasMmlMsg, 0x00, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 返回缓冲区指针 */
    return pstNasMmlMsg;
}


VOS_VOID NAS_MML_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);

        return;
    }

    /* 2. 取得一个消息缓冲单元 */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[ucMsgPnt]);

    /* 3. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列中 */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= NAS_MML_MAX_MSG_QUEUE_SIZE;

    return;
}


NAS_MML_INTERNAL_MSG_BUF_STRU* NAS_MML_GetNextInternalMsg( VOS_VOID )
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;
    NAS_MML_CTX_STRU                   *pstMmlCtx  =  VOS_NULL_PTR;

    pstMmlCtx   = NAS_MML_GetMmlCtx();

    if ( pstMmlCtx->stInternalMsgQueue.ucHeader != pstMmlCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmlCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstMmlCtx->stInternalMsgQueue.astNasMmMsgQueue[ucNextIndex]);

        /* 取完一条消息,头指针向后偏移 */
        (pstMmlCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmlCtx->stInternalMsgQueue.ucHeader) %= NAS_MML_MAX_MSG_QUEUE_SIZE;
        return pstNextMsg;
    }

    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MML_GetNextInternalMsg:Empty Internal Msg");
    return VOS_NULL_PTR;

}



VOS_VOID NAS_MML_InsertInternalMsgHead(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);
        return;
    }
    /* 2. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    if ( (pstInternalMsgQueue->ucHeader % NAS_MML_MAX_MSG_QUEUE_SIZE) >= 1 )
    {
        pstInternalMsgQueue->ucHeader--;
        pstInternalMsgQueue->ucHeader         %= NAS_MML_MAX_MSG_QUEUE_SIZE;
    }
    else
    {
        pstInternalMsgQueue->ucHeader = NAS_MML_MAX_MSG_QUEUE_SIZE- 1;
    }

    /* 3. 取得一个消息缓冲单元 */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[pstInternalMsgQueue->ucHeader]);

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列的最前面 */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */

    return;
}




pNasMmPIdMsgProc NAS_MML_FindPidMsgProc(
    VOS_UINT32                          ulRcvPid
)
{
    pNasMmPIdMsgProc                    fReturnMsgProcHandle;

    fReturnMsgProcHandle =  VOS_NULL_PTR;
    switch ( ulRcvPid )
    {
        case WUEPS_PID_MM :
            fReturnMsgProcHandle    = MmMsgProc;
            break;
        case WUEPS_PID_GMM :
            fReturnMsgProcHandle    = GmmMsgProc;
            break;
        case WUEPS_PID_MMC :
            fReturnMsgProcHandle    = NAS_MMC_MsgProc;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            fReturnMsgProcHandle    = NAS_MM_PidMsgEntry;
            break;
#endif

        default:
            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MML_FindPidMsgProc:invalide rcv pid", ulRcvPid);
            break;
    }

    return fReturnMsgProcHandle;
}



VOS_VOID NAS_MML_MsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg   = VOS_NULL_PTR;
    pNasMmPIdMsgProc                    pMsgProc     = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
#ifndef __PS_WIN32_RECUR__
    VOS_UINT32                          ulIsSndOmPcRecurMsgValid;
#endif
    VOS_UINT32                          ulRslt;
    struct MsgCB                       *pstNextDestMsg;

    /* 入口参数检查 */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Empty Msg");
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
        NAS_MML_ConvertOamSendPid(&pRcvMsg->ulSenderPid);
    }

    pMsgProc = NAS_MML_FindPidMsgProc(pRcvMsg->ulReceiverPid);

    /* 未找到处理函数直接返回 */
    if ( VOS_NULL_PTR == pMsgProc )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        return;
    }

    /* 先处理外部消息 */
    pMsgProc(pRcvMsg);

    /* 外部消息处理完成后处理内部消息 */
    pstNextMsg = NAS_MML_GetNextInternalMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (PS_PID_MM == pstNextMsg->ulSenderPid)
        {
            pstMsgHeader = (MSG_HEADER_STRU *)pstNextMsg;

            NAS_MML_LogMsgInfo(pstMsgHeader);

        }
#endif

        pMsgProc = NAS_MML_FindPidMsgProc(pstNextMsg->ulReceiverPid);

        /* 未找到处理函数直接返回 */
        if ( VOS_NULL_PTR == pMsgProc )
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_FALSE == NAS_MML_IsPlatformSupportLte())
              && (PS_PID_MM == pstNextMsg->ulReceiverPid))
        {
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Platform not support Lte");
        }
#endif
        else
        {
            /* 将该消息钩出来,以便于在PSTAS中显示 */
            DIAG_TraceReport(pstNextMsg);


            /* 将当前消息进入UTRANCTRL模块进行处理 */
            ulRslt = NAS_UTRANCTRL_MsgProc((struct MsgCB *)pstNextMsg, &pstNextDestMsg);

            /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
            if ( VOS_FALSE == ulRslt )
            {
                pMsgProc((struct MsgCB *)pstNextDestMsg);
            }

        }

        /* 寻找下一条内部消息 */
        pstNextMsg = NAS_MML_GetNextInternalMsg();
    }

#ifndef __PS_WIN32_RECUR__

    ulIsSndOmPcRecurMsgValid = NAS_MML_IsSndOmPcRecurMsgValid();

    if ( (VOS_TRUE == NAS_MML_GetUePcRecurFlg())
      && (VOS_TRUE == ulIsSndOmPcRecurMsgValid))
    {
        NAS_MML_SetUePcRecurFlg(VOS_FALSE);

        NAS_MMC_SndOutsideContextData();
        NAS_MM_SndOutsideContextData();
        NAS_GMM_SndOutsideContextData();
    }

#endif


    return;
}





VOS_UINT32  NAS_MML_FidMsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    struct MsgCB                       *pstDestMsg;
    VOS_UINT32                          ulRslt;


    pstDestMsg = VOS_NULL_PTR;

    /* 入口参数检查 */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_FidMsgProc:Empty Msg");
        return VOS_ERR;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    NAS_MML_LogMsgInfo(pstMsgHeader);


    /* 将当前消息进入UTRANCTRL模块进行处理 */
    ulRslt = NAS_UTRANCTRL_MsgProc(pRcvMsg, &pstDestMsg);

    /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
    if ( VOS_TRUE == ulRslt )
    {
        return VOS_OK;
    }

    /* 如果经过UTRUNCTRL处理消息改变，则在记录一次 */
    if (pRcvMsg != pstDestMsg)
    {
        NAS_MML_LogMsgInfo(pstMsgHeader);
    }

    /* 处理从UTRANCTRL模块返回的消息 */
    NAS_MML_MsgProc(pstDestMsg);

    /* 处理UTRANCTRL模块缓存的消息 */
    NAS_UTRANCTRL_ProcBufferMsg();

    NAS_MML_UpdateExitTime();

    return VOS_OK;
}




VOS_UINT32 NAS_MML_FidInit (
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    VOS_UINT32 ulReturnCode;

    switch( enInitPhase )
    {
        case   VOS_IP_LOAD_CONFIG:
#if defined(INSTANCE_1)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_1);
#elif defined(INSTANCE_2)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_2);
#else
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS);
#endif

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MM,
                                  (Init_Fun_Type) WuepsMmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMC,
                                      (Init_Fun_Type) NAS_MMC_InitPid,
                                      (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_GMM,
                                  (Init_Fun_Type) WuepsGmmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMA,
                                    (Init_Fun_Type) TAF_MMA_InitPid,
                                    (Msg_Fun_Type)TAF_MMA_MsgProcEntry);

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

#ifndef DMT
#if (FEATURE_ON == FEATURE_LTE)
    #if defined(INSTANCE_1) || defined(INSTANCE_2)
            /* 双卡双通modem1不编译L模 */
    #else
            ulReturnCode = VOS_RegisterPIDInfo(PS_PID_MM,
                          (Init_Fun_Type) NAS_MM_PidInit,
                          (Msg_Fun_Type) NAS_MML_FidMsgProc  );
    #endif
#endif
#endif

            ulReturnCode = VOS_RegisterTaskPrio(WUEPS_FID_MM,
                                                NAS_MM_TASK_PRIO);

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

    }

    return VOS_OK;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

