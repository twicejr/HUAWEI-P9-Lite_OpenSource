

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
/*****************************************************************************
 函 数 名  : CSD_UL_GetAtClientIndex
 功能描述  : 获取AT Client Index
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月28日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CSD_UL_GetAtClientIndex(VOS_VOID)
{
    return g_stCsdCtx.ucAtClientIndex;
}

/*****************************************************************************
 函 数 名  : CSD_UL_SetAtClientIndex
 功能描述  : 设置AT Client Index
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月28日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_UL_SetAtClientIndex(VOS_UINT8 ucIndex)
{
    g_stCsdCtx.ucAtClientIndex = ucIndex;
}

/*****************************************************************************
 函 数 名  : CSD_UL_InsertQueueTail
 功能描述  : 数据入队操作，插入缓存队列尾部
 输入参数  : A_CIRCULAR_QUEUE_STRU * pQueueHead
            VOS_VOID               *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月8日
    作    者   : w00199382
    修改内容   : 新生成函数

  2.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：使用自旋锁

*****************************************************************************/
VOS_UINT32 CSD_UL_InsertQueueTail(
    IMM_ZC_HEAD_STRU                   *pstQueueHead,
    IMM_ZC_STRU                        *pstNode
)
{
    /* Modified by l60609 for AP适配项目 ，2012-08-31 Begin */
    VOS_ULONG                           ulLockLevel;

    ulLockLevel = 0;

    /* 队列加锁 */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* 数据插入队尾 */
    IMM_ZcQueueTail(pstQueueHead, pstNode);

    /* 队列解锁 */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* Modified by l60609 for AP适配项目 ，2012-08-31 End */

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_InsertQueueTail:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueueHead->qlen,
                   pstQueueHead->next,
                   pstQueueHead->prev);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CSD_UL_GetQueueFrontNode
 功能描述  : 获取上行队列头节点
 输入参数  : IMM_ZC_HEAD_STRU *pstQueue
 输出参数  : 无
 返 回 值  : IMM_ZC_STRU  *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : w00199382
    修改内容   : 新生成函数

  2.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：使用自旋锁
*****************************************************************************/
IMM_ZC_STRU  *CSD_UL_GetQueueFrontNode(IMM_ZC_HEAD_STRU *pstQueue)
{
    IMM_ZC_STRU                        *pstNode;
    /* Modified by l60609 for AP适配项目 ，2012-08-31 Begin */
    VOS_ULONG                           ulLockLevel;

    ulLockLevel = 0;

    /* 队列加锁 */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* 返回队尾节点指针 */
    pstNode        = IMM_ZcDequeueHead(pstQueue);

    /* 队列解锁 */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* Modified by l60609 for AP适配项目 ，2012-08-31 End */

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_GetQueueFrontNode:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueue->qlen,
                   pstQueue->next,
                   pstQueue->prev);

    return pstNode;
}
/*****************************************************************************
 函 数 名  : CSD_UL_FreeQueue
 功能描述  : 清空队列释放数据,注意此接口不释放头结点内存，头结点内存需要自行释放
 输入参数  : IMM_ZC_HEAD_STRU *stQueue
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CSD_GetUlQueue
 功能描述  : 获取上行队列指针
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : IMM_ZC_HEAD_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_HEAD_STRU *CSD_UL_GetQueue(VOS_VOID)
{
    return g_stCsdCtx.pstULQueue;
}
/*****************************************************************************
 函 数 名  : CSD_UL_SetQueue
 功能描述  : 设置上行队列指针
 输入参数  : IMM_ZC_HEAD_STRU *pstULQueue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_UL_SetQueue(IMM_ZC_HEAD_STRU *pstULQueue)
{
    g_stCsdCtx.pstULQueue = pstULQueue;
}
/*****************************************************************************
 函 数 名  : CSD_GetLastTxSlice
 功能描述  : 获取最近一次中断触发的slice若是第一次触发则为0
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CSD_GetLastTxSlice(VOS_VOID)
{
    return g_stCsdCtx.ulLastDICCIsrSlice;
}

/*****************************************************************************
 函 数 名  : CSD_SetCurrTxSlice
 功能描述  : 设置SLICE，用来记录最近触发DICC中断的时间
 输入参数  : VOS_UINT32 CurrSlice
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_SetCurrTxSlice(VOS_UINT32 ulCurrSlice)
{
    g_stCsdCtx.ulLastDICCIsrSlice       = ulCurrSlice;
}

/*****************************************************************************
 函 数 名  : CSD_GetUpLinkDataSem
 功能描述  : 上行数据信号量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_SEM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_SEM CSD_GetUpLinkDataSem(VOS_VOID)
{
    return g_stCsdCtx.hULdataSem;
}

/*****************************************************************************
 函 数 名  : CSD_GetDownLinkDataSem
 功能描述  : 下行数据信号量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_SEM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_SEM CSD_GetDownLinkDataSem(VOS_VOID)
{
    return g_stCsdCtx.hDLdataSem;
}

/*****************************************************************************
 函 数 名  : CSD_GetCallState
 功能描述  : 获取当前通话状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : AT_CSD_CALL_TYPE_STATE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 CSD_GetCallState(VOS_VOID)
{
    return g_stCsdCtx.enCallState;
}

/*****************************************************************************
 函 数 名  : CSD_SetCallState
 功能描述  : 保存当前通话状态
 输入参数  : AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_SetCallState(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState)
{
    g_stCsdCtx.enCallState                  = enCallState;
}
/*****************************************************************************
 函 数 名  : CSD_InitSem
 功能描述  : 初始化上下行队列信号量,需要在FID初始化时调用
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : CSD_CtxInit
 功能描述  : 初始化CSD全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : w00199382
    修改内容   : 新生成函数
  2.日    期   : 2012年9月12日
    作    者   : l60609
    修改内容   : AP适配项目：修改锁处理
  3.日    期   : 2013年05月28日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 CSD_InitCtx(VOS_VOID)
{

    /*缓存队列头指针初始化*/
    CSD_UL_SetQueue(VOS_NULL_PTR);

    /*用来记录最近触发DICC中断的时间，初始为0*/
    CSD_SetCurrTxSlice(CSD_DEFAULT_TX_SLICE);

    /*CSD默认通话状态设置*/
    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    /* Added by l60609 for AP适配项目 ，2012-09-10 Begin */
    /* 锁初始化 */
    VOS_SpinLockInit(&g_stCsdCtx.stSpinLock);
    /* Added by l60609 for AP适配项目 ，2012-09-10 End */

    CSD_UL_SetAtClientIndex(0);

    return VOS_OK;
}

#endif /*FEATURE_CSD*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
