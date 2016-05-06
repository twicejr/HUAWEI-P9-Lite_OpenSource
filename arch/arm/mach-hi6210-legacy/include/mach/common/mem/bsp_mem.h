#ifndef    _BSP_MEM_H_
#define    _BSP_MEM_H_

#include "BSP.h"
#include <mach/common/mem/bsp_mem_drv.h>
/*#include <mach/balong_v100r001.h>*/
/*#include <generated/FeatureConfig.h>  */


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**************************************************************************
  函数声明
**************************************************************************/
BSP_S32 BSP_MEM_Init(VOID);
BSP_S32 BSP_MEM_SetMostUsedSize(BSP_U32 u32Size, BSP_U32 u32PoolType);

BSP_VOID* BSP_Malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
BSP_VOID* BSP_MallocDbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line);
BSP_VOID  BSP_Free(BSP_VOID* pMem);
BSP_VOID  BSP_FreeDbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line);

BSP_VOID* BSP_SMalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
BSP_VOID* BSP_SMallocDbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line);
BSP_VOID  BSP_SFree(BSP_VOID* pMem);
BSP_VOID  BSP_SFreeDbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line);


/**************************************************************************
  接口声明
**************************************************************************/
/*****************************************************************************
* 函 数 名  : BSP_MALLOC
*
* 功能描述  : BSP 动态内存分配
*
* 输入参数  : sz: 分配的大小(byte)
*             flags: 内存属性(暂不使用,预留)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_MALLOC(sz, flags) BSP_MallocDbg(sz, flags, __FILE__, __LINE__)
#else
#define BSP_MALLOC(sz, flags) BSP_Malloc(sz, flags)
#endif


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
#define BSP_SMALLOC(sz, flags) BSP_SMallocDbg(sz, (MEM_POOL_TYPE)flags, (BSP_U8*)__FILE__, __LINE__)
#else
#define BSP_SMALLOC(sz, flags) BSP_SMalloc(sz, flags)
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
#define BSP_SFREE(ptr) BSP_SFreeDbg(ptr, (BSP_U8*)__FILE__, __LINE__)
#else
#define BSP_SFREE(ptr) BSP_SFree(ptr)
#endif



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_MEM_H_ */

