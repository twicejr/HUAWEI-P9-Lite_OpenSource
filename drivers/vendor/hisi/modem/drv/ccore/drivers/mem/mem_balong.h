
#ifndef    _BSP_MEM_H_
#define    _BSP_MEM_H_

#include <bsp_om.h>
#include "osl_cache.h"
#include "osl_types.h"
#include "mem_balong_drv.h"
#include <bsp_sram.h>
#include <mdrv_memory.h>
#include <bsp_ipc.h>
#include <mdrv_ipc.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
//#include <cacheLib.h>


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  宏定义
**************************************************************************/

#define  mem_print_error(fmt,...)      (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mem_print_dbg(fmt,...)		       (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))

#define STATIC

/**************************************************************************
  函数声明
**************************************************************************/
void bsp_mem_init(void);
s32 bsp_set_most_used_size(u32 u32Size, u32 u32PoolType);

void* bsp_smalloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_sfree(void* pMem);
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line);
void *bsp_cachedma_malloc (unsigned int nBytes);
int   bsp_cachedma_free (void* buf);

/**************************************************************************
  接口声明
**************************************************************************/

/*****************************************************************************
* 函 数 名  : BSP_SMALLOC
*
* 功能描述  : BSP 动态内存分配(加spin lock保护,多核场景使用)
*
* 输入参数  : sz: 分配的大小(byte)
*             flags: 内存属性(使用DDR / AXI)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SMALLOC(sz, flags) bsp_smalloc_dbg(sz, (MEM_POOL_TYPE)flags, (u8*)__FILE__, __LINE__)
#else
#define BSP_SMALLOC(sz, flags) bsp_smalloc(sz, flags)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SFREE
*
* 功能描述  : BSP 动态内存释放(加spin lock保护,多核场景使用)
*
* 输入参数  : ptr: 动态内存指针
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SFREE(ptr) bsp_sfree_dbg(ptr, (u8*)__FILE__, __LINE__)
#else
#define BSP_SFREE(ptr) bsp_sfree(ptr)
#endif
/*以下是为了消除编译warnning*/
s32 bsp_mem_info(u32 u32MemType);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_MEM_H_ */

