

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CsdCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

    /*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_CTX_C
    /*lint -e767 */

#if( FEATURE_ON == FEATURE_CSD )


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CSD_CTX_STRU                            g_stCsdCtx;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT8 CSD_UL_GetAtClientIndex(VOS_VOID)
{
    return g_stCsdCtx.ucAtClientIndex;
}


VOS_VOID CSD_UL_SetAtClientIndex(VOS_UINT8 ucIndex)
{
    g_stCsdCtx.ucAtClientIndex = ucIndex;
}


VOS_UINT32 CSD_UL_InsertQueueTail(
    IMM_ZC_HEAD_STRU                   *pstQueueHead,
    IMM_ZC_STRU                        *pstNode
)
{
    VOS_ULONG                           ulLockLevel;

    ulLockLevel = 0;

    /* 队列加锁 */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* 数据插入队尾 */
    IMM_ZcQueueTail(pstQueueHead, pstNode);

    /* 队列解锁 */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);


    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_InsertQueueTail:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueueHead->qlen,
                   pstQueueHead->next,
                   pstQueueHead->prev);

    return VOS_OK;
}


IMM_ZC_STRU  *CSD_UL_GetQueueFrontNode(IMM_ZC_HEAD_STRU *pstQueue)
{
    IMM_ZC_STRU                        *pstNode;
    VOS_ULONG                           ulLockLevel;

    ulLockLevel = 0;

    /* 队列加锁 */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* 返回队尾节点指针 */
    pstNode        = IMM_ZcDequeueHead(pstQueue);

    /* 队列解锁 */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);


    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_GetQueueFrontNode:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueue->qlen,
                   pstQueue->next,
                   pstQueue->prev);

    return pstNode;
}

VOS_UINT32 CSD_UL_FreeQueue(IMM_ZC_HEAD_STRU *pstQueue)
{
    IMM_ZC_STRU                        *pstNode;
    VOS_UINT32                          i;
    VOS_UINT32                          ulQueueCnt;

    ulQueueCnt = IMM_ZcQueueLen(pstQueue);

    for (i = 0; i < ulQueueCnt; i++)
    {
        pstNode  = CSD_UL_GetQueueFrontNode(pstQueue);

        if(VOS_NULL_PTR == pstNode)
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_UL_FreeQueue:: CSD_UL_GetQueueFrontNode fail",
                          pstNode);

            return VOS_ERR;
        }

        /*释放数据内存*/
        IMM_ZcFree(pstNode);

    }

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_FreeQueue:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueue->qlen,
                   pstQueue->next,
                   pstQueue->prev);

    return VOS_OK;
}



IMM_ZC_HEAD_STRU *CSD_UL_GetQueue(VOS_VOID)
{
    return g_stCsdCtx.pstULQueue;
}

VOS_VOID CSD_UL_SetQueue(IMM_ZC_HEAD_STRU *pstULQueue)
{
    g_stCsdCtx.pstULQueue = pstULQueue;
}

VOS_UINT32 CSD_GetLastTxSlice(VOS_VOID)
{
    return g_stCsdCtx.ulLastDICCIsrSlice;
}


VOS_VOID CSD_SetCurrTxSlice(VOS_UINT32 ulCurrSlice)
{
    g_stCsdCtx.ulLastDICCIsrSlice       = ulCurrSlice;
}


VOS_SEM CSD_GetUpLinkDataSem(VOS_VOID)
{
    return g_stCsdCtx.hULdataSem;
}


VOS_SEM CSD_GetDownLinkDataSem(VOS_VOID)
{
    return g_stCsdCtx.hDLdataSem;
}


AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 CSD_GetCallState(VOS_VOID)
{
    return g_stCsdCtx.enCallState;
}


VOS_VOID CSD_SetCallState(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState)
{
    g_stCsdCtx.enCallState                  = enCallState;
}

VOS_UINT32 CSD_InitSem(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_SEM                             hULDataSem;
    VOS_SEM                             hDLDataSem;

    hDLDataSem  = CSD_GetDownLinkDataSem();
    hULDataSem  = CSD_GetUpLinkDataSem();

    /* 初始下行信号量 */
    ulRslt      = VOS_SmBCreate("ulDldataSem",
                                CSD_SEMAPHORE_INIT_CNT,
                                VOS_SEMA4_FIFO,
                                &hDLDataSem);

    if (VOS_OK != ulRslt)
    {
        VOS_SmDelete(hDLDataSem);
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_InitSem:: VOS_SmBCreate pDLDataSem fail");

        return VOS_ERR;
    }

    /* 初始上行信号量 */
    ulRslt      = VOS_SmBCreate("ulUldataSem",
                                CSD_SEMAPHORE_INIT_CNT,
                                VOS_SEMA4_FIFO,
                                &hULDataSem);

    if (VOS_OK != ulRslt)
    {
        VOS_SmDelete(hULDataSem);
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_InitSem:: VOS_SmBCreate pULDataSem fail");

        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 CSD_InitCtx(VOS_VOID)
{

    /*缓存队列头指针初始化*/
    CSD_UL_SetQueue(VOS_NULL_PTR);

    /*用来记录最近触发DICC中断的时间，初始为0*/
    CSD_SetCurrTxSlice(CSD_DEFAULT_TX_SLICE);

    /*CSD默认通话状态设置*/
    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    /* 锁初始化 */
    VOS_SpinLockInit(&g_stCsdCtx.stSpinLock);

    CSD_UL_SetAtClientIndex(0);

    return VOS_OK;
}

#endif /*FEATURE_CSD*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
