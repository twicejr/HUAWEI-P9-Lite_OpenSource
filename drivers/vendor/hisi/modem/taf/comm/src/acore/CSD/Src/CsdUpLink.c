

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CsdUpLink.h"
#include "CsdDebug.h"
#include "PsLib.h"

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_UP_LINK_C

#if(FEATURE_ON == FEATURE_CSD)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID CSD_UL_SendData(IMM_ZC_STRU *pstULData)
{
    /*入参检查*/
    if (VOS_NULL_PTR == pstULData)
    {
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_SendData:: pstULData Is Null");

        return;
    }

    /*数据地址合法性检查*/
    if (VOS_NULL_PTR == pstULData->data)
    {
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_SendData:: pstULData->data Is Null");

        return;
    }

    /*数据长度检查*/
    if (0 == pstULData->len)
    {
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_SendData:: pstULData->len Is Null");

        return;
    }

    CSD_DBG_UL_RECV_PKT_NUM(1);

    /*数据入队*/
    CSD_UL_InsertQueue(pstULData);

}

VOS_UINT32 CSD_UL_InsertQueue(IMM_ZC_STRU *pstULData)
{

    IMM_ZC_HEAD_STRU                   *pstULQueue;
    VOS_UINT32                          ulInQueueRst;
    VOS_SEM                             hULDataSem = VOS_NULL_PTR;

    hULDataSem       = CSD_GetUpLinkDataSem();

    pstULQueue       = CSD_UL_GetQueue();

    /*如果链表未创建则返回错误，释放数据内存*/
    if (VOS_NULL_PTR == pstULQueue)
    {
        IMM_ZcFree(pstULData);
        CSD_DBG_UL_ENQUE_FAIL_NUM(1);
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_InsertQueue:: ULQueue Is Null");

        return VOS_ERR;
    }

    /*数据入缓存队列，此处需要加任务锁，为了防止在访问缓存队列时，自处理任务也在
    访问*/
    VOS_TaskLock();

    ulInQueueRst     = CSD_UL_InsertQueueTail(pstULQueue,pstULData);

    VOS_TaskUnlock();

    if (VOS_ERR == ulInQueueRst)
    {
        IMM_ZcFree(pstULData);
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_InsertQueue:: ULQueue Is Null");

        return VOS_ERR;
    }

    /*数据入缓存队列成功释放信号量*/
    VOS_SmV(hULDataSem);

    CSD_DBG_UL_SAVE_BUFF_PKT_NUM(1);

    CSD_NORMAL_LOG(ACPU_PID_CSD,"CSD_UL_InsertQueue::Insert ULQueue Done!");

    return VOS_OK;

}


VOS_UINT32 CSD_UL_InitQueue(VOS_VOID)
{

    IMM_ZC_HEAD_STRU                    *pstULQueue;

    pstULQueue     = CSD_UL_GetQueue();

    /*创建缓存队列，如果已创建则直接返回*/
    if (VOS_NULL_PTR ==  pstULQueue)
    {
        CSD_WARNING_LOG(ACPU_PID_CSD,
                        "CSD_UL_InitQueue:: ULQueue Is Null Need Alloc Mem !");

        /*分配头节点内存*/
        pstULQueue = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD, sizeof(IMM_ZC_HEAD_STRU));

        CSD_UL_SetQueue(pstULQueue);

        /*由于初始化链表不对指针进行判断所以此处需要对指针进行判断*/
        if (VOS_NULL_PTR == pstULQueue)
        {
            CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_InitQueue:: PS_MEM_ALLOC Fail");
            return VOS_ERR;
        }

        /*初始化链表*/
        IMM_ZcQueueHeadInit(pstULQueue);

    }

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_InitQueue:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstULQueue->qlen,
                   pstULQueue->next,
                   pstULQueue->prev);

    /*lint -e429*/
    return VOS_OK;
    /*lint +e429*/
}

VOS_UINT32 CSD_UL_BuildDiccInsertData(
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    CSD_CST_DATA_REQ_STRU              *pstULData,
    DICC_INSERT_DSCP_BLK_STRU          *pstDiccInsertData
)
{
    IMM_ZC_STRU                        *pstULImmZcData;
    IMM_MEM_STRU                       *pstULImmData;

    /*获取第一个数据*/
    pstULImmZcData                      = CSD_UL_GetQueueFrontNode(pstUlQueue);

    if (VOS_NULL_PTR == pstULImmZcData)
    {
        CSD_DBG_UL_QUENULL_NUM(1);
        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_ConfigDataToDICC pstULNode Is Null!");

        return VOS_ERR;
    }

    /*IMM_ZcMapToImmMem换为IMM头*/
    pstULImmData                        = IMM_ZcMapToImmMem(pstULImmZcData);

    if (VOS_NULL_PTR == pstULImmData)
    {
        /*释放节点内存*/
        IMM_ZcFree(pstULImmZcData);

        CSD_DBG_UL_ZCTOIMM_FAIL_NUM(1);

        CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_ConfigDataToDICC pstULImmData Is Null!");

        return VOS_ERR;
    }

    /*虚地址转换为实地址*/
    pstULData->pucData                  = (VOS_UINT8 *)TTF_VIRT_TO_PHY((VOS_VOID *)(pstULImmZcData->data));

    pstULData->pGarbage                 = (VOS_VOID *)pstULImmData;
    pstULData->usLen                    = (VOS_UINT16)pstULImmZcData->len;

    /*配置插入通道内的数据*/
    pstDiccInsertData->enAutoTrigTx     = PS_FALSE;
    pstDiccInsertData->ucDataLen        = DICC_INFO_BLOCK_MAX_LEN;
    pstDiccInsertData->pucUserData      = (VOS_UINT8 *)(pstULData);

    /*释放节点内存*/
    IMM_ZcHeadFree(pstULImmZcData);

    CSD_NORMAL_LOG(ACPU_PID_CSD,"CSD_UL_ConfigDataToDICC  Done!");

    return VOS_OK;
}

CSD_UL_SEND_DATA_STATE_ENUM_UINT16 CSD_UL_SendDataToDICC(VOS_VOID)
{
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulFreeSpaceCnt;
    VOS_UINT32                          ulLinkCnt;
    IMM_ZC_HEAD_STRU                   *pstULQueue;
    CSD_CST_DATA_REQ_STRU               stULData;
    DICC_INSERT_DSCP_BLK_STRU           stDiccInsertData;
    IMM_MEM_STRU                       *pstULImmData;

    /*获取上行队列*/
    pstULQueue      = CSD_UL_GetQueue();

    /*获取DICC发送节点数目*/
    ulFreeSpaceCnt  = DICC_GetChannelFreeSpaceCnt(ACPU_PID_CSD,
                                                  DICC_CHAN_ID_UL_CSD_DATA_CHAN,
                                                  DICC_CPU_ID_ACPU);

    if (DICC_INVALID_VALUE == ulFreeSpaceCnt)
    {
       CSD_ERROR_LOG(ACPU_PID_CSD,
                     "CSD_UL_SendDataToDICC:: DICC_GetChannelFreeSpaceCnt Fail");

       return CSD_UL_SEND_DATA_NOT_CONTINUE;
    }

    /*缓存操作，锁任务*/
    VOS_TaskLock();

    /*获取缓存节点数*/
    ulLinkCnt                           = IMM_ZcQueueLen(pstULQueue);

    if (0 == ulLinkCnt )
    {
        CSD_WARNING_LOG1(ACPU_PID_CSD,
                        "CSD_UL_SendDataToDICC:: ulLinkCnt is Null",
                        ulLinkCnt);

        VOS_TaskUnlock();

        return CSD_UL_SEND_DATA_NOT_CONTINUE;
    }

    ulCnt                               = PS_MIN(ulLinkCnt, ulFreeSpaceCnt);

    /* CST的环形BUFFER目前调整到8K，发送50个数据大概2.5K，CST起流控的流量设置在3K */
    /* 当CST起流控后，到停止发数据有0.5秒的延时，这时还会有大量的数据缓存在CSD */
    /* 队列与DICC中最小的数与最大发送的个数比较，取两者最小的发送 */
    ulCnt                               = PS_MIN(ulCnt, CSD_UL_MAX_SEND_CNT);

    while (0 < ulCnt)
    {
        /*配置上行数据*/
        ulRslt = CSD_UL_BuildDiccInsertData(pstULQueue,
                                            &stULData,
                                            &stDiccInsertData);
        if (VOS_OK != ulRslt)
        {
            CSD_ERROR_LOG(ACPU_PID_CSD,
                         "CSD_UL_SendDataToDICC:: CSD_UL_BuildDiccInsertData Fail");

            VOS_TaskUnlock();

            return CSD_UL_SEND_DATA_NOT_CONTINUE;
        }

        /*DICC插入数据通道 */
        ulRslt = DICC_InsertChannelData(ACPU_PID_CSD,
                                        DICC_CHAN_ID_UL_CSD_DATA_CHAN,
                                        &stDiccInsertData,
                                        DICC_CPU_ID_ACPU);
        if ( DICC_OK != ulRslt )
        {
            /*需要释放IMM内存*/
            pstULImmData                = (IMM_MEM_STRU *)stULData.pGarbage;
            IMM_MemFree(pstULImmData);

            CSD_DBG_UL_INSERT_FAIL_NUM(1);

            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_UL_SendDataToDICC:: DICC_InsertChannelData Fail",
                          ulRslt);
            break;
        }

        ulCnt--;

        CSD_NORMAL_LOG1(ACPU_PID_CSD,
                        "CSD_UL_SendDataToDICC:: ulCnt DEC",
                        ulCnt);
    }

    /*缓存操作完成，解锁任务*/
    VOS_TaskUnlock();

    /*触发中断*/
    ulRslt = DICC_TriggerChanDataTx(ACPU_PID_CSD,
                                    DICC_CHAN_ID_UL_CSD_DATA_CHAN,
                                    DICC_CPU_ID_ACPU);

    /*更新当前SLICE*/
    CSD_SetCurrTxSlice(VOS_GetSlice());

    if ( DICC_OK != ulRslt )
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD,
                      "CSD_UL_SendDataToDICC:: DICC_TriggerChanDataTx Fail",
                      ulRslt);

        return CSD_UL_SEND_DATA_NOT_CONTINUE;
    }

    if (ulLinkCnt > ulFreeSpaceCnt)
    {
        CSD_WARNING_LOG(ACPU_PID_CSD,
                        "CSD_UL_SendDataToDICC CSD_UL_SEND_DATA_CONTINUE !");

        return CSD_UL_SEND_DATA_CONTINUE;
    }

    return CSD_UL_SEND_DATA_NOT_CONTINUE;
}



VOS_UINT32 CSD_UL_CalcIsrSlice(VOS_VOID)
{
    VOS_UINT32                          ulCurrSliceCnt;
    VOS_UINT32                          ulLastSliceCnt;
    VOS_UINT32                          ulSliceDuration;

    ulLastSliceCnt     = CSD_GetLastTxSlice();
    ulCurrSliceCnt     = VOS_GetSlice();

    /* 时间戳是由0开始递增，所以当前的时间戳应该大于上次。另在时间戳
       到0xFFFFFFFF时会重置到0，所以else分支处理这种情况 */
    if (ulCurrSliceCnt > ulLastSliceCnt)
    {
        ulSliceDuration = ulCurrSliceCnt - ulLastSliceCnt;
    }
    else
    {
        ulSliceDuration = CSD_MAX_SLICE_CNT - ulLastSliceCnt + ulCurrSliceCnt;
    }

    return ulSliceDuration;
}


VOS_VOID CSD_UL_ProcDataTask(VOS_VOID)
{
    VOS_SEM                             hUpLinkSem = VOS_NULL_PTR;
    VOS_UINT32                          ulSliceDurationCnt;
    CSD_UL_SEND_DATA_STATE_ENUM_UINT16  enSendDataRslt;

    hUpLinkSem               = CSD_GetUpLinkDataSem();

    for ( ; ; )
    {

        /* 获取信号量, 获取到的时候, 说明可以发送数据 */
        if (VOS_OK != VOS_SmP(hUpLinkSem, 0))
        {
            CSD_NORMAL_LOG(ACPU_PID_CSD,
                          "CSD_UL_ProcDataTask:: VOS_SmP pulUpLinkSem then continue !");


#ifdef __PC_UT__
            break;
#else
            continue;
#endif

        }


        for ( ; ; )
        {
            /*判断当前是否拨号成功*/
            if (AT_CSD_CALL_STATE_ON != CSD_GetCallState())
            {
                CSD_WARNING_LOG(ACPU_PID_CSD,
                                "CSD_UL_ProcDataTask:: NOT AT_CSD_CALL_STATE_ON then Break !");

                break;
            }

            /*获取两次中断间隔时间*/
            ulSliceDurationCnt = CSD_UL_CalcIsrSlice();

            /*获取当前SLICE间隔与上次发送是否大于10MS, 首次发送, 不需要判断 */
            if (ulSliceDurationCnt < CSD_TEN_MILLISECOND)
            {
                CSD_WARNING_LOG(ACPU_PID_CSD,
                                "CSD_UL_ProcDataTask:: ulSliceDurationCnt < CSD_TX_DURATION then continue !");

                VOS_TaskDelay(CSD_UL_TASK_DELAY_TIME);

                continue;
            }

            /* 向DICC发送一次数据 */
            enSendDataRslt = CSD_UL_SendDataToDICC();

            /* 如果没有缓存未发送的数据, 循环退出 */
            if (CSD_UL_SEND_DATA_CONTINUE != enSendDataRslt)
            {
                CSD_NORMAL_LOG(ACPU_PID_CSD,
                               "CSD_UL_ProcDataTask:: CSD_UL_SEND_DATA_NOT_CONTINUE ");

                break;
            }
        }

#ifdef __PC_UT__
        break;
#endif
    }
}

VOS_UINT32 CSD_UL_RcvAtCallStateOn(VOS_VOID)
{
    VOS_UINT32                          ulRslt;

    /*初始化缓存队列*/
    ulRslt  = CSD_UL_InitQueue();

    if (VOS_ERR == ulRslt )
    {
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_UL_RcvAtCallStateInd:: CSD_UL_InitQueue Fail Set State Off");

        /*缓存初始化异常时，则认为当前未拨号成功*/
        CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

        return VOS_ERR;
    }

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    return VOS_OK;
}

VOS_UINT32 CSD_UL_RcvAtCallStateOff(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;
    VOS_UINT32                          ulRslt;

    pstULQueue      = CSD_UL_GetQueue();

    if (VOS_NULL_PTR == pstULQueue )
    {
        CSD_WARNING_LOG(ACPU_PID_CSD,
                        "CSD_UL_RcvAtCallStateInd:: pstULQueue Is NullSet State Off !");

        CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

        return VOS_OK;
    }

    VOS_TaskLock();

    /*清除缓存队列*/
    ulRslt          = CSD_UL_FreeQueue(pstULQueue);

    /*释放头结点*/
    PS_MEM_FREE(ACPU_PID_CSD, pstULQueue);

    /*头结点置为空*/
    CSD_UL_SetQueue(VOS_NULL_PTR);

    VOS_TaskUnlock();

    if (VOS_OK != ulRslt)
    {
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_UL_RcvAtCallStateInd:: CSD_UL_FreeQueue Fail Set State Off");
    }

    /*中断间隔SLICE清零*/
    CSD_SetCurrTxSlice(CSD_DEFAULT_TX_SLICE);

    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    return VOS_OK;
}


VOS_UINT32 CSD_UL_RcvAtCallStateInd(MsgBlock* pMsg)
{
    VOS_UINT32                          ulRslt;
    AT_CSD_CALL_TYPE_STATE_ENUM_UINT16  enCallState;
    AT_CSD_CALL_STATE_TYPE_IND_STRU    *pstMsg;

    pstMsg          = (AT_CSD_CALL_STATE_TYPE_IND_STRU *)pMsg;
    enCallState     = pstMsg->enCallState;

    CSD_UL_SetAtClientIndex(pstMsg->ucIndex);

    if (AT_CSD_CALL_STATE_ON == enCallState)
    {
        ulRslt      = CSD_UL_RcvAtCallStateOn();
    }
    else if (AT_CSD_CALL_STATE_OFF == enCallState)
    {
        ulRslt      = CSD_UL_RcvAtCallStateOff();
    }
    else
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD,
                      "CSD_UL_RcvAtCallStateInd:: enCallState Illage",
                      enCallState);

        return VOS_ERR;
    }

    return ulRslt;

}


VOS_VOID CSD_UL_ProcMsg(MsgBlock* pMsg)
{

    if (VOS_NULL_PTR == pMsg)
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD,
                      "CSD_UL_ProcMsg:: pMsg is Null",
                      pMsg);
        return ;
    }

    switch ( pMsg->ulSenderPid )
    {
        case WUEPS_PID_AT :
            CSD_UL_RcvAtMsg(pMsg);
            break;

        default:
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_UL_ProcMsg:: ulSenderPid Illage",
                          pMsg->ulSenderPid);
            break;
    }
}


VOS_VOID CSD_UL_RcvAtMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    /* 从消息包中获取MSG ID */
    pstMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case ID_AT_CSD_CALL_STATE_IND :
             CSD_UL_RcvAtCallStateInd((MsgBlock *)pMsg);
             break;

        default:
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_UL_RcvAtMsg:: enMsgId Illage",
                          pstMsgHeader->ulMsgName);
            break;
    }


}

#endif /*FEATURE_CSD*/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
