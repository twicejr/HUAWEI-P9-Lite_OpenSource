/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_mem_balong.c
*
*   作    者 :  fuxin 00221597
*
*   描    述 :  本文件主要内存接口的适配
*************************************************************************/
#include <string.h>
#include <drv_comm.h>
#include <mdrv_memory.h>
#include <osl_types.h>
#include <stdlib.h>
#include <mem_balong.h>

/*****************************************************************************
* 函 数 名  : mdrv_memcpy
*
* 功能描述  : 数据拷贝接口。底层基于汇编实现的最优化接口，目前在v8r1上使用。
*
* 输入参数  :  dest : 拷贝的目的地址
*              src  : 拷贝的源地址
*             count : 拷贝数据的大小
* 输出参数  : 无
* 返 回 值  : 无
****************************************************************************/
extern void * __rt_memcpy(void * dest, const void * src, unsigned long count);
void * mdrv_memcpy(void * dest, const void * src, unsigned long count)
{
    return __rt_memcpy(dest,src,count);
}

/*****************************************************************************
* 函 数 名  : mdrv_cachedmem_alloc
*
* 功能描述  :为DMA设备或者驱动分配一个cache安全的内存。
*
* 输入参数  : bytes: 需要分配的字节的数量
*
* 输出参数  : 无
* 返 回 值  :  NULL :    分配内存失败
*            非NULL指针: 分配内存成功，该指针指向分配的内存块的指针
****************************************************************************/
void* mdrv_cachedmem_alloc (unsigned int  bytes)
{
#ifdef CONFIG_MEM
    return bsp_cachedma_malloc(bytes);
#else
    return NULL;
#endif
}

/*****************************************************************************
* 函 数 名  : mdrv_cachedmem_free
*
* 功能描述  :释放由mdrv_cachedmem_alloc分配的内存。
*
* 输入参数  : pBuf:指向要释放的内存块的指针
*
* 输出参数  : 无
* 返 回 值  :  0: 成功
*             -1: 失败
****************************************************************************/
int mdrv_cachedmem_free(void*  pBuf)
{
#ifdef CONFIG_MEM
    return bsp_cachedma_free(pBuf);
#else
    return MDRV_OK;
#endif
}
/*****************************************************************************
* 函 数 名  : mdrv_smalloc
*
* 功能描述  :为分配一个内存。
*
* 输入参数  : size: 需要分配的字节的数量
*
* 输出参数  : 无
* 返 回 值  :     NULL : 分配内存失败
*            非NULL指针: 分配内存成功，该指针指向分配的内存块的指针
****************************************************************************/
void* mdrv_smalloc (unsigned int size,MEM_POOL_TYPE flags)
{
#ifdef CONFIG_MEM
    return bsp_smalloc(size, flags);
#else
    return NULL;
#endif
}

/*****************************************************************************
* 函 数 名  : mdrv_sfree
*
* 功能描述  :释放由mdrv_smalloc分配的内存。
*
* 输入参数  : pBuf:指向要释放的内存块的指针
*
* 输出参数  : 无
* 返 回 值  :  0: 成功
*             -1: 失败
****************************************************************************/
int mdrv_sfree(void*  pBuf)
{
#ifdef CONFIG_MEM
    bsp_sfree(pBuf);
#endif
    return MDRV_OK;
}

/*****************************************************************************
 函 数 名  : mdrv_get_freeblockmem
 功能描述  : 释放mem
 输入参数  :
 输出参数  :

 返回值    ：0    成功
             -1   失败
*****************************************************************************/
int mdrv_get_freeblockmem(void)
{
    return 0;
}

#if 0
BSP_VOID* bsp_malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return malloc(u32Size);
}
BSP_VOID* bsp_malloc_dbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line)
{
    return malloc(u32Size);
}
BSP_VOID  bsp_free(BSP_VOID* pMem)
{
    free(pMem);
    return;
}
BSP_VOID  bsp_free_dbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line)
{
    free(pMem);
    return;
}
BSP_VOID* bsp_smalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return malloc(u32Size);
}
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line)
{
    return malloc(u32Size);

}
BSP_VOID  bsp_sfree(BSP_VOID* pMem)
{
    free(pMem);
    return;
}
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line)
{
    free(pMem);
    return;
}
#endif




