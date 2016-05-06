



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "IMMmemZC.h"
#include "v_id.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_IMM_ZC_C
/*lint +e767*/

/******************************************************************************
   2 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : IMM_ZcStaticAlloc_Debug
 功能描述  : 从A核数传内存中申请内存的分配函数
 输入参数  : ulLen - 申请的字节数
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 成功：返回指向IMM_ZC_STRU的指针
             失败：返回NULL；
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* IMM_ZcStaticAlloc_Debug(unsigned short usFileID, unsigned short usLineNum, unsigned int ulLen)
{
    IMM_ZC_STRU *pstAlloc = VOS_NULL_PTR;

    /* 智能机形态上, 申请skb系统内存 */
    pstAlloc = (IMM_ZC_STRU *)IMM_ZcLargeMemAlloc(ulLen);

    return pstAlloc;
}

/*****************************************************************************
 函 数 名  : IMM_ZcStaticCopy_Debug
 功能描述  : IMM_ZC的数据结构的拷贝（控制节点和数据块），把数据块从Linux自带的内存拷贝到A核共享内存
 输入参数  : pstImmZc - 源数据结构
 输出参数  : 无
 返 回 值  : 成功：返回目的IMM_ZC_STRU的指针
             失败：返回NULL；
 调用函数  :
 被调函数  :
 其它      : A核数据类型为MEM_TYPE_SYS_DEFINED的数据块，数据传给C核前，一定要调用本接口，将数据拷贝到A核共享内存。
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* IMM_ZcStaticCopy_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, IMM_ZC_STRU* pstImmZc)
{
    return NULL;
}

/*****************************************************************************
 函 数 名  : IMM_ZcHeadFree
 功能描述  : 释放IMM_ZC_STRU控制节点，数据块不释放。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcHeadFree(IMM_ZC_STRU* pstImmZc)
{
    return;
}

/*****************************************************************************
 函 数 名  : IMM_ZcMapToImmMem
 功能描述  : 把IMM_Zc零拷贝控制节点转换成IMM_Mem控制节点
 输入参数  : IMM_ZC_STRU *pstImmZc
 输出参数  : 无
 返 回 值  : 成功:指向IMM_MEM_STRU的指针;失败:NULL。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : s00164817
    修改内容   : 新生成函数

*****************************************************************************/
IMM_MEM_STRU *IMM_ZcMapToImmMem_Debug(unsigned short usFileID,
        unsigned short usLineNum, IMM_ZC_STRU *pstImmZc)
{
    return NULL;
} /* IMM_ZcMapToImmMem */


/*****************************************************************************
 函 数 名  : IMM_ZcAddMacHead
 功能描述  : 给IMM_ZC_STRU 零拷贝结构添加MAC头
 输入参数  : IMM_ZC_STRU *pstImmZc
             unsigned char* pucAddData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_OK 添加成功
             VOS_ERR 添加失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月2日
    作    者   :
    修改内容   : Created
*****************************************************************************/
unsigned int IMM_ZcAddMacHead (IMM_ZC_STRU *pstImmZc, const unsigned char* pucAddData)
{
    unsigned char                      *pucDestAddr;

    if ( NULL == pstImmZc )
    {
        vos_printf("IMM_ZcAddMacHead pstImmZc ptr is null! \n");
        return VOS_ERR;
    }

    if ( NULL == pucAddData )
    {
        vos_printf("IMM_ZcAddMacHead pucData ptr is null! \n");
        return VOS_ERR;
    }


    if( IMM_MAC_HEADER_RES_LEN > (pstImmZc->data - pstImmZc->head) )
    {
        vos_printf("IMM_ZcAddMacHead invalid data Len! data = %p, head = %p \n",
                    pstImmZc->data, pstImmZc->head);

        return VOS_ERR;
    }

    pucDestAddr = IMM_ZcPush(pstImmZc, IMM_MAC_HEADER_RES_LEN);
    memcpy(pucDestAddr, pucAddData, IMM_MAC_HEADER_RES_LEN);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : IMM_ZcRemoveMacHead
 功能描述  : 移除零拷贝结构MAC头
 输入参数  : IMM_ZC_STRU *pstImmZc
 输出参数  : 无
 返 回 值  : VOS_OK 添加成功
             VOS_ERR 添加失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月2日
    作    者   : s00164817
    修改内容   : Created
*****************************************************************************/
unsigned int IMM_ZcRemoveMacHead(IMM_ZC_STRU *pstImmZc)
{
    if ( NULL == pstImmZc )
    {
        vos_printf("IMM_ZcRemoveMacHead pstImmZc ptr is null! \n");
        return VOS_ERR;
    }

    if ( IMM_MAC_HEADER_RES_LEN > pstImmZc->len )
    {
        vos_printf("IMM_ZcRemoveMacHead invalid data Len! tail = %p, data = %p, len = %d \n",
                    skb_tail_pointer(pstImmZc), pstImmZc->data, pstImmZc->len);

        return VOS_ERR;
    }

    IMM_ZcPull(pstImmZc, IMM_MAC_HEADER_RES_LEN);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : IMM_ZcPush_Debug
 功能描述  : 数据添加到有效数据块的头部。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
             ulLen - 添加数据的长度
 输出参数  : 无
 返 回 值  : 返回的数据块首地址，并且是添加数据之后的数据块地址。
 调用函数  :
 被调函数  :
 其它      : 本接口只移动指针；
             数据添加到有效数据块的头部之前,调用本接口
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
unsigned char* IMM_ZcPush_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen)
{
    unsigned char* pucRet = NULL;

    pucRet = skb_push((pstImmZc), (ulLen));

    return pucRet;
}


/*****************************************************************************
 函 数 名  : IMM_ZcPull_Debug
 功能描述  : 从IMM_ZC指向的数据块的头部取出数据。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
             ulLen - 取出数据的长度
 输出参数  : 无
 返 回 值  : 返回的数据块首地址，并且是取出数据之后的地址。
 调用函数  :
 被调函数  :
 其它      : 本接口只移动指针；
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
unsigned char* IMM_ZcPull_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen)
{
    unsigned char* pucRet = NULL;

    pucRet = skb_pull(pstImmZc, ulLen);

    return pucRet;
}


/*****************************************************************************
 函 数 名  : IMM_ZcPut_Debug
 功能描述  : 添加数据在IMM_ZC指向的数据块的尾部。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
             ulLen - 添加数据的长度
 输出参数  : 无
 返 回 值  : 返回的数据块尾部地址，并且是添加数据之前的数据块尾部地址。
 调用函数  :
 被调函数  :
 其它      : 本接口只移动指针；
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
unsigned char* IMM_ZcPut_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen)
{
    unsigned char* pucRet = NULL;

    pucRet = skb_put(pstImmZc, ulLen);

    return pucRet;
}


/*****************************************************************************
 函 数 名  : IMM_ZcReserve_Debug
 功能描述  : 预留IMM_ZC指向的数据块头部空间。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
             ulLen - 预留数据头部的空间(byte)
 输出参数  : 无
 返 回 值  : 无。
 调用函数  :
 被调函数  :
 其它      : 本接口只移动指针，为头部预留空间。
             只用于刚分配的IMM_ZC,IMM_ZC指向的数据块还没有使用；
 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcReserve_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen)
{
    skb_reserve(pstImmZc, (int)ulLen);

    return;
}


/*****************************************************************************
 函 数 名  : IMM_ZcGetUserApp
 功能描述  : 得到UserApp。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
 输出参数  : 无
 返 回 值  : 得到UserApp。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
unsigned short IMM_ZcGetUserApp(IMM_ZC_STRU *pstImmZc)
{
    return IMM_PRIV_CB(pstImmZc)->usApp;
}


/*****************************************************************************
 函 数 名  : IMM_ZcSetUserApp
 功能描述  : 设置UserApp。
 输入参数  : pstImmZc - 指向IMM_ZC_STRU的指针
             usApp - 用户自定义
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcSetUserApp (IMM_ZC_STRU *pstImmZc, unsigned short usApp)
{
    if ( NULL == pstImmZc )
    {
        return;
    }

    IMM_PRIV_CB(pstImmZc)->usApp = usApp;

    return;
}


/*****************************************************************************
 函 数 名  : IMM_ZcDataTransformImmZc_Debug
 功能描述  : 数据块的挂接到IMM_ZC_STRU上。
 输入参数  : unsigned char *pucData    数据块内存地址
             unsigned int ulLen      数据块长度
             void *pstTtfMem   数据块控制节点指针
 输出参数  : 无
 返 回 值  : skbuf 指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月2日
    作    者   : s00164817
    修改内容   : Created
*****************************************************************************/
IMM_ZC_STRU * IMM_ZcDataTransformImmZc_Debug(unsigned short usFileID,
        unsigned short usLineNum, const unsigned char *pucData, unsigned int ulLen, void *pstTtfMem)
{
    return NULL;
}/* IMM_ZcDataTransformImmZc_Debug */


/*****************************************************************************
 函 数 名  : IMM_ZcQueueHeadInit_Debug
 功能描述  : 队列初始化。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcQueueHeadInit_Debug(unsigned short usFileID, unsigned short usLineNum,
        IMM_ZC_HEAD_STRU* pstList)
{
    skb_queue_head_init((pstList));
}


/*****************************************************************************
 函 数 名  : IMM_ZcQueueHead_Debug
 功能描述  : 元素插入队列头部。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
             pstNew  - 插入的元素，是指向IMM_ZC_STRU的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcQueueHead_Debug(unsigned short usFileID, unsigned short usLineNum,
                                 IMM_ZC_HEAD_STRU *list, IMM_ZC_STRU *pstNew)
{
    skb_queue_head((list), (pstNew));
}

/*****************************************************************************
 函 数 名  : IMM_ZcQueueTail_Debug
 功能描述  : 元素插入队列尾部 。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
             pstNew  - 插入的元素，是指向IMM_ZC_STRU的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
void IMM_ZcQueueTail_Debug(unsigned short usFileID, unsigned short usLineNum,
                                 IMM_ZC_HEAD_STRU *pstList, IMM_ZC_STRU *pstNew)
{
    skb_queue_tail((pstList), (pstNew));
}

/*****************************************************************************
 函 数 名  : IMM_ZcDequeueHead_Debug
 功能描述  : 从队列头部 取元素 。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
 输出参数  : 无
 返 回 值  : 指向IMM_ZC_STRU的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* IMM_ZcDequeueHead_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList)
{
    IMM_ZC_STRU *pstHead = NULL;

    pstHead = skb_dequeue((pstList));


    return pstHead;
}


/*****************************************************************************
 函 数 名  : IMM_ZcDequeueTail_Debug
 功能描述  : 从队列尾部取元素 。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
 输出参数  : 无
 返 回 值  : 指向IMM_ZC_STRU的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* IMM_ZcDequeueTail_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList)
{
    IMM_ZC_STRU *pstTail = NULL;

    pstTail = skb_dequeue_tail((pstList));


    return pstTail;
}


/*****************************************************************************
 函 数 名  : IMM_ZcQueueLen_Debug
 功能描述  : 得到队列中的元素的数目。
 输入参数  : pstList - 指向IMM_ZC_HEAD_STRU的指针
 输出参数  : 无
 返 回 值  : 得到队列中的元素的数目。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : y00171741
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int IMM_ZcQueueLen_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList)
{
    unsigned int ulLen;

    ulLen = skb_queue_len((pstList));

    return ulLen;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

