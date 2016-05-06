



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "LUPQueue.h"
#include "TTFComm.h"

#define    THIS_FILE_ID        PS_FILE_ID_L_TTFQUEUE_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 函 数 名  : LUP_IsQueEmpty
 功能描述  : 检测队列是否为空
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
 输出参数  : 无
 返 回 值  : PS_TRUE    -- 队列为空
             PS_FALSE   -- 队列不空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_IsQueEmpty(const LUP_QUEUE_STRU *pstQue)
{
    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_TRUE);

    if (pstQue->ulHead == pstQue->ulTail)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


/*****************************************************************************
 函 数 名  : LUP_IsQueFull
 功能描述  : 检测队列是否已经满
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
 输出参数  : 无
 返 回 值  : PS_TRUE    -- 队列为满
             PS_FALSE   -- 队列未满
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_IsQueFull(const LUP_QUEUE_STRU *pstQue)
{
    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_TRUE);

    if (pstQue->ulHead == TTF_MOD_ADD(pstQue->ulTail, 1, pstQue->ulMaxNum))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : LUP_QueCnt
 功能描述  : 返回队列中的个数
 输入参数  : LUP_QUEUE_STRU *pstQue
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月11日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_QueCnt(const LUP_QUEUE_STRU *pstQue)
{
    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, 0);

    return TTF_MOD_SUB(pstQue->ulTail, pstQue->ulHead, pstQue->ulMaxNum);
}

/*****************************************************************************
 函 数 名  : LUP_PeekQueHead
 功能描述  : 查看队列中的头节点
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
 输出参数  : VOS_VOID **ppNode -- 队列头节点
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_PeekQueHead(const LUP_QUEUE_STRU *pstQue, VOS_VOID **ppNode)
{
    VOS_UINT32 ulHead = 0;

    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_PTR_NULL);
    OSA_ASSERT_RTN (VOS_NULL_PTR != ppNode, PS_PARA_ERR);

    if (PS_TRUE == LUP_IsQueEmpty(pstQue))
    {
        return  PS_QUE_EMPTY;
    }

    ulHead  = TTF_MOD_ADD(pstQue->ulHead, 1, pstQue->ulMaxNum);
    *ppNode = pstQue->pBuff[ulHead];

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : LUP_EnQue
 功能描述  : 入队操作，在队列尾部插入接点
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
             VOS_VOID *pNode -- 入队节点内容
 输出参数  : 无
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 LUP_EnQue(LUP_QUEUE_STRU *pstQue, VOS_VOID *pNode)
{
    VOS_UINT32          ulTail;

    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_PTR_NULL);
    OSA_ASSERT_RTN (VOS_NULL_PTR != pNode, PS_PTR_NULL);

    ulTail = TTF_MOD_ADD(pstQue->ulTail, 1, pstQue->ulMaxNum);
    if (pstQue->ulHead == ulTail)
    {
        return PS_QUE_FULL;
    }

    pstQue->pBuff[ulTail] = pNode;
    pstQue->ulTail = ulTail;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : LUP_DeQue
 功能描述  : 出队操作，取出头接点
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
 输出参数  : VOS_VOID **ppNode -- 获取的头节点
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_DeQue(LUP_QUEUE_STRU *pstQue, VOS_VOID **ppNode)
{
    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_PTR_NULL);
    OSA_ASSERT_RTN(VOS_NULL_PTR != ppNode, PS_PTR_NULL);

    if (pstQue->ulHead == pstQue->ulTail)
    {
        return  PS_QUE_EMPTY;
    }

    pstQue->ulHead  = TTF_MOD_ADD(pstQue->ulHead, 1, pstQue->ulMaxNum);
    *ppNode         = pstQue->pBuff[pstQue->ulHead];

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : LUP_BatchDeQue
 功能描述  : 一次性把队列中的节点全部取出来，放在用户指定的缓冲中
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
 输出参数  : pulBuf -- 批量出队
             pulNum -- 个数
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月14日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 LUP_BatchDeQue(LUP_QUEUE_STRU *pstQue, VOS_VOID **ppBuf,VOS_UINT32 *pulNum)
{
    VOS_UINT32    ulCnt;
    VOS_UINT32    ulLoop;

    OSA_ASSERT_RTN(VOS_NULL_PTR != pstQue, PS_PTR_NULL);
    OSA_ASSERT_RTN(VOS_NULL_PTR != ppBuf, PS_PTR_NULL);
    OSA_ASSERT_RTN(VOS_NULL_PTR != pulNum, PS_PTR_NULL);

    ulCnt = TTF_MOD_SUB(pstQue->ulTail, pstQue->ulHead, pstQue->ulMaxNum);

    if (0 == ulCnt)
    {
        return  PS_QUE_EMPTY;
    }

    for(ulLoop=0; ulLoop<ulCnt; ulLoop++)
    {
        pstQue->ulHead  = TTF_MOD_ADD(pstQue->ulHead, 1, pstQue->ulMaxNum);
        ppBuf[ulLoop]   = pstQue->pBuff[pstQue->ulHead];
    }

    *pulNum = ulCnt;

    return PS_SUCC;
}

/*lint -e715*/
/*****************************************************************************
 函 数 名  : LUP_CreateQue
 功能描述  : 创建队列
 输入参数  : VOS_UINT32 ulMaxNodeNum -- 队列容纳的最大节点数
 输出参数  : LUP_QUEUE_STRU **ppQue  指向生成队列指针的指针
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 LUP_CreateQue(VOS_UINT32 ulPid, LUP_QUEUE_STRU **ppQue,
                                VOS_UINT32 ulMaxNodeNum)
{
    LUP_QUEUE_STRU  *pstQue     = VOS_NULL_PTR;
    VOS_UINT8       *pBuffer    = VOS_NULL_PTR;

    if (0 == ulMaxNodeNum)
    {
        return PS_PARA_ERR;
    }

    if (VOS_NULL_PTR == ppQue)
    {
        return PS_PTR_NULL;
    }

    pBuffer = (VOS_UINT8*)PS_MEM_ALLOC(ulPid, (ulMaxNodeNum + 1)* sizeof(VOS_VOID*));
    if (VOS_NULL_PTR == pBuffer)
    {
        return PS_MEM_ALLOC_FAIL;
    }

    pstQue = (LUP_QUEUE_STRU *)PS_MEM_ALLOC(ulPid, sizeof(LUP_QUEUE_STRU));
    if (VOS_NULL_PTR == pstQue)
    {
        (VOS_VOID)PS_MEM_FREE(ulPid, pBuffer);
        return PS_MEM_ALLOC_FAIL;
    }

    pstQue->ulHead      = ulMaxNodeNum;
    pstQue->ulTail      = ulMaxNodeNum;
    pstQue->ulMaxNum    = ulMaxNodeNum+1;
    /*lint -e826*/
    pstQue->pBuff       = (VOS_VOID **)pBuffer;
    /*lint +e826*/
    *ppQue              = pstQue;

    return  PS_SUCC;
}

/*****************************************************************************
 函 数 名  : LUP_DestroyQue
 功能描述  : 销毁队列，释放内存
 输入参数  : LUP_QUEUE_STRU **ppQue  指向待销毁队列指针的指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年3月10日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数


*****************************************************************************/
VOS_UINT32 LUP_DestroyQue(VOS_UINT32 ulPid, LUP_QUEUE_STRU **ppQue)
{
    /*l00258641 消除fortify告警 begin*/
    LUP_QUEUE_STRU     *pstQue;

    if (VOS_NULL_PTR == ppQue)
    {
        return PS_PTR_NULL;
    }
    pstQue = *ppQue;
    /*l00258641 消除fortify告警 end*/
    if (VOS_NULL_PTR == pstQue)
    {
        return PS_PARA_ERR;
    }

    PS_MEM_FREE(ulPid, pstQue->pBuff);
    pstQue->pBuff   = VOS_NULL_PTR;
    PS_MEM_FREE(ulPid, pstQue);
    *ppQue          = VOS_NULL_PTR;

    return PS_SUCC;
}
/*lint +e715*/

/*****************************************************************************
 函 数 名  : LUP_EnQuetoHead
 功能描述  : 入队操作，在队列头部插入接点，如果队列满，则将队尾节点移除
 输入参数  : LUP_QUEUE_STRU *pstQue -- 环形队列结构指针
             VOS_VOID *pNode -- 入队节点内容
 输出参数  : VOS_VOID** ppTailNode -- 当队列满时，返回尾节点
 返 回 值  : PS_SUCC -- 成功，其它为相应错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年10月20日
    作    者   : yechaoling 151394
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 LUP_EnQuetoHead(LUP_QUEUE_STRU *pstQue, VOS_VOID *pNode, VOS_VOID** ppTailNode)
{
    OSA_ASSERT_RTN (VOS_NULL_PTR != pstQue, PS_PTR_NULL);

    if(VOS_NULL_PTR == ppTailNode)
    {
        return PS_PTR_NULL;
    }
    if (PS_TRUE == LUP_IsQueFull(pstQue))
    {
        /*移除尾节点*/
        *ppTailNode = pstQue->pBuff[pstQue->ulTail];
        pstQue->ulTail = TTF_MOD_SUB(pstQue->ulTail, 1, pstQue->ulMaxNum);
    }
    else
    {
        *ppTailNode = VOS_NULL_PTR;
    }
    pstQue->pBuff[pstQue->ulHead] = pNode;
    pstQue->ulHead = TTF_MOD_SUB(pstQue->ulHead, 1, pstQue->ulMaxNum);
    return PS_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

