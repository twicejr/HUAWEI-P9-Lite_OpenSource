

/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ombufmngr.c
  版 本 号      : 初稿
  作    者      : 甘兰
  生成日期      : 2012年07月31日
  最近修改      :
  功能描述      : 该C文件给出了BM(Buffer Manager)模块的实现
  函数列表      :

  修改历史      :
   1.日    期   : 2012年07月31日
     作    者   : g47350
     修改内容   : V900R001项目新增文件
******************************************************************************/

/*****************************************************************************
  1 头文件
*****************************************************************************/
#include "ombufmngr.h"


#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_BUF_MMNGR_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
OM_BUF_RECORD_STRU                      g_stOmBufRecord;

/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : OM_CreateTraceBuffer
 功能描述  : 创建OM缓冲区
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针
             lBufSize:   分配缓冲区大小

 输出参数  : 无

 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 OM_CreateTraceBuffer(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize)
{
    VOS_UINT_PTR ulRealAddr;

    /* 参数检测 */
    if ((VOS_NULL_PTR == pstBufCtrl) || (0 == lBufSize))
    {
        return VOS_ERR;
    }

    pstBufCtrl->lAlloc   = 0;
    pstBufCtrl->lRelease = 0;
    pstBufCtrl->lPadding = 0;
    pstBufCtrl->lBufSize = lBufSize + 1;

    /*申请uncache的动态内存区*/
    pstBufCtrl->pucBuf = (VOS_UINT8*)VOS_UnCacheMemAlloc((VOS_UINT32)pstBufCtrl->lBufSize, &ulRealAddr);

    /* 分配内存失败 */
    if (VOS_NULL_PTR == pstBufCtrl->pucBuf)
    {
        return VOS_ERR;
    }

    /* 保存buf实地址 */
    pstBufCtrl->pucRealBuf = (VOS_UINT8 *)ulRealAddr;

    /*lint -e534*/
    vos_printf("\r\nOM_CreateTraceBuffer: real addr=0x%p, virt addr==0x%p\n", ulRealAddr, pstBufCtrl->pucBuf);

    VOS_MemSet(&g_stOmBufRecord, 0, sizeof(g_stOmBufRecord));
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OM_AllocTraceMem
 功能描述  : 从缓冲区中分配连续的物理内存.
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针
             lLen:      申请内存大小

 输出参数  : 无

 返 回 值  : VOS_NULL_PTR 分配失败
             VOS_VOID*    分配内存的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID* OM_AllocTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen)
{
    VOS_INT32                           lFreeSize;
    VOS_UINT8                          *pucAddr;
    VOS_INT32                           lTmpAlloc;
    VOS_INT32                           lTmpPadding;

    /* 输入参数检测 */
    if ((VOS_NULL_PTR == pstBufCtrl)
        || (lLen >= pstBufCtrl->lBufSize)
        || (0 == lLen))
    {
        OM_ALLOC_RECORD(VOS_NULL_PTR, lLen);

        return VOS_NULL_PTR;
    }

    lTmpAlloc       = pstBufCtrl->lAlloc;
    lTmpPadding     = pstBufCtrl->lPadding;

    /* 没有翻转 */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        /* 获取剩余内存大小 */
        if (0 == pstBufCtrl->lRelease)
        {
            lFreeSize = (pstBufCtrl->lBufSize - pstBufCtrl->lAlloc) - 1;
        }
        else
        {
            lFreeSize = pstBufCtrl->lBufSize - pstBufCtrl->lAlloc;
        }

        /* 满足用户申请内存大小则返回 */
        if (lFreeSize >= lLen)
        {
            pucAddr = pstBufCtrl->pucBuf + pstBufCtrl->lAlloc;
            pstBufCtrl->lAlloc += lLen;

            OM_ALLOC_RECORD(pucAddr, lLen);

            return pucAddr;
        }

        lTmpPadding  = lFreeSize;
        lTmpAlloc    = 0;
    }

    /* 翻转，获取剩余内存大小 */
    lFreeSize = (pstBufCtrl->lRelease - lTmpAlloc) - 1;

    if (lFreeSize >= lLen)
    {
        pucAddr = pstBufCtrl->pucBuf + lTmpAlloc;

        pstBufCtrl->lAlloc    = lTmpAlloc + lLen;
        pstBufCtrl->lPadding  = lTmpPadding;

        OM_ALLOC_RECORD(pucAddr, lLen);

        return pucAddr;
    }

    OM_ALLOC_RECORD(VOS_NULL_PTR, lLen);

    /* 否则分配失败，返回空指针 */
    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : OM_ReleaseTraceMem
 功能描述  : 释放从缓冲区中分配连续的物理内存.
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针
             pAddr:      指向释放内存的指针
             lLen:       释放缓冲区大小

 输出参数  : 无

 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 OM_ReleaseTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl,
                                        VOS_VOID *pAddr, VOS_INT32 lLen)
{
    VOS_INT32                           lUsedSize;
    VOS_INT32                           lTmpRls;

    OM_RLS_RECORD(pAddr, lLen);

    /* 输入参数检测 */
    if ((VOS_NULL_PTR == pstBufCtrl) || (lLen >= pstBufCtrl->lBufSize))
    {
        return VOS_ERR;
    }

    /* 释放内存地址进行检测 */
    if ((pAddr != (pstBufCtrl->pucBuf + pstBufCtrl->lRelease))
        && (pAddr != pstBufCtrl->pucBuf))
    {
        g_stOmBufRecord.ulSocpBug++;
        /*return VOS_ERR;*/
    }

    /* 未翻转 */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        lUsedSize = pstBufCtrl->lAlloc - pstBufCtrl->lRelease;

        /* 长度错误 */
        if (lUsedSize < lLen)
        {
            return VOS_ERR;
        }

        pstBufCtrl->lRelease = (VOS_UINT8 *)pAddr + lLen - pstBufCtrl->pucBuf;

        return VOS_OK;
    }

    if (((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) > pstBufCtrl->lBufSize)
    {
        lTmpRls = (((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) + pstBufCtrl->lPadding) % pstBufCtrl->lBufSize;
    }
    else
    {
        lTmpRls = ((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) % pstBufCtrl->lBufSize;
    }

    /* 输入ulLen不正确 */
    if ((lTmpRls > pstBufCtrl->lAlloc) && (lTmpRls < pstBufCtrl->lRelease))
    {
        return VOS_ERR;
    }

    /* 如果发生跳转则将Padding值归0 */
    if (lTmpRls <= pstBufCtrl->lAlloc)
    {
        pstBufCtrl->lPadding = 0;
    }

    pstBufCtrl->lRelease = lTmpRls;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OM_TraceMemNBytes
 功能描述  : 获得缓冲区中使用内存大小.
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针

 输出参数  : 无

 返 回 值  : VOS_INT32 使用内存大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_INT32 OM_TraceMemNBytes(OM_BUF_CTRL_STRU *pstBufCtrl)
{
    VOS_INT32 lUsedBytes;

    /* 输入参数检测 */
    if (VOS_NULL_PTR == pstBufCtrl)
    {
        return 0;
    }

    lUsedBytes = pstBufCtrl->lAlloc - pstBufCtrl->lRelease;

    /* 指针有翻转 */
    if (lUsedBytes < 0)
    {
        lUsedBytes += pstBufCtrl->lBufSize;
    }

    return lUsedBytes;
}

/*****************************************************************************
 函 数 名  : OM_AddrVirtToReal
 功能描述  : 将虚地址转换为实地址.
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针
             pucVirtAddr:待转换虚地址

 输出参数  : 无

 返 回 值  : VOS_NULL_PTR 转换失败
             VOS_VOID*    指向转换后实地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID* OM_AddrVirtToReal(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucVirtAddr)
{
    return (VOS_VOID *)VOS_UncacheMemVirtToPhy(pucVirtAddr, pstBufCtrl->pucRealBuf, pstBufCtrl->pucBuf, (VOS_UINT32)pstBufCtrl->lBufSize);
}

/*****************************************************************************
 函 数 名  : OM_AddrRealToVirt
 功能描述  : 将实地址转换为虚地址.
 输入参数  : pstBufCtrl: 指向缓冲区控制块指针
             pucRealAddr:待转换实地址

 输出参数  : 无

 返 回 值  : VOS_NULL_PTR 转换失败
             VOS_VOID*    指向转换后虚地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID* OM_AddrRealToVirt(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucRealAddr)
{
    return (VOS_VOID*)VOS_UncacheMemPhyToVirt(pucRealAddr, pstBufCtrl->pucRealBuf, pstBufCtrl->pucBuf, (VOS_UINT32)pstBufCtrl->lBufSize);
}

/*****************************************************************************
 函 数 名  : OM_BufShow
 功能描述  :
 输入参数  : VOS_VOID

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID OM_BufShow(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    /*lint -e534*/
    vos_printf("\r\n OM ALLOC DATA SOCP Bug: %d.\r\n",g_stOmBufRecord.ulSocpBug);

    vos_printf("\r\n OM ALLOC DATA LIST: \r\n");
    /*lint +e534*/

    for (ulIndex = g_stOmBufRecord.ulAllocNum; ulIndex < OM_RECORD_MAX_NUM; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astAllocItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astAllocItem[ulIndex].pucData,
                    g_stOmBufRecord.astAllocItem[ulIndex].lLen);
        /*lint +e534*/
    }

    for (ulIndex = 0; ulIndex < g_stOmBufRecord.ulAllocNum; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astAllocItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astAllocItem[ulIndex].pucData,
                    g_stOmBufRecord.astAllocItem[ulIndex].lLen);
        /*lint +e534*/
    }

    /*lint -e534*/
    vos_printf("\r\n OM RELEASE DATA LIST: \r\n");
    /*lint +e534*/

    for (ulIndex = g_stOmBufRecord.ulRlsNum; ulIndex < OM_RECORD_MAX_NUM; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astRlsItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astRlsItem[ulIndex].pucData,
                    g_stOmBufRecord.astRlsItem[ulIndex].lLen);
        /*lint +e534*/
    }

    for (ulIndex = 0; ulIndex < g_stOmBufRecord.ulRlsNum; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astRlsItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astRlsItem[ulIndex].pucData,
                    g_stOmBufRecord.astRlsItem[ulIndex].lLen);
        /*lint +e534*/
    }

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

