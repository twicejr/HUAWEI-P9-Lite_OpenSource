

/*lint -save -e537*/
#include <mdrv_memory.h>
#include "mem_balong_drv.h"
#include "osl_malloc.h"
#include "osl_cache.h"
#include "osl_bio.h"
#include <string.h>
#include <stdio.h>
#include "mem_balong.h"


/*lint -restore */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/*lint -save -e40 -e413*/
/**************************************************************************
  宏定义
**************************************************************************/
//#ifdef __BSP_DEBUG__
#define __BSP_MEM_DEBUG__
//#endif

#ifdef __BSP_MEM_DEBUG__
/* 用于打印查找次数, 方便设置 MostUseItem 的值 */
//#define MEM_PRINT_FIND_TIMES
#endif

/* 每个内存节点的最大值定义 */
#define MEM_NODE_MGR_SIZE           32

/* MAGIC定义码 */
#define MEM_MAGIC_NUM               0x11223344

/*lint -save -e19 */
/* 内存尺寸分配表 */
u32 sg_AllocListSize[]  =   {32,    128,   512,    1024,   2048, 4096, 8192,   0x4000, 0x8000, 0x10000, 0x20000};
u32 sg_AllocMinNum[]    =   {512,   256,   100,    10,     1,     2,    10,     10,      1,      1,        1};
u32 sg_AllocMaxNum[]    =   {1024,  1024,  1024,   1024,   2048, 100 , 80,     40,      10,     4,        1};
/*lint -restore -e19 */

#define MEM_ALLOC_LIST_NUM          (sizeof(sg_AllocListSize) / sizeof(u32))


/**************************************************************************
  类型定义
**************************************************************************/
/* 内存节点状态类型 */
typedef enum tagMEM_STATUS
{
    MEM_FREE = 0,
    MEM_ALLOC = 1
}MEM_STATUS;

/* 内存池管理信息 */
typedef struct tagMEM_POOL_INFO
{
    u32 u32BaseAddr;            /* 内存池基地址 */
    u32 u32Size;                /* 内存池总大小 */
    u32 u32CurPosAddr;          /* 内存池当前分配到的位置 */
    u32 u32Left;                /* 内存池剩余大小 */
    u32 u32MgrSize;             /* 管理结构大小 */
}MEM_POOL_INFO;

/* 每个内存节点的管理信息(注意,最大不要超过 32bytes) */
typedef struct tagMEM_MGR_INFO
{
    u32 u32MagicNumber;         /* 用于检查当前内存块是否有效（仅在Debug模式下写入该）*/
    u32 u32Next;                /*用于指向本节点的下一块内存*/
    u32 u32Size;                /*描述该内存块的大小*/
    u32 u32Flags;               /*描述该内存块的属性（双核时需要该属性区别AXI还是DDR）*/
#ifdef __BSP_MEM_DEBUG__
    u32 u32FileName;            /*使用该内存块的 .c 文件（仅在Debug模式下写入该）*/
    u32 u32Line;                /*使用该内存块在 .c 文件中的行数*/
    u32 u32Status;              /*记录当前内存块的使用状态，是Malloc状态还是Free状态*/
#endif
}MEM_MGR_INFO;

/* 每个内存节点的使用计数 */
typedef struct tagMEM_USED_INFO
{
    u32 u32CurNum;              /* 当前使用个数计数 */
    u32 u32MaxNum;              /* 使用个数峰值 */
    u32 u32TotalMallocNum;      /* 累积malloc次数 */
    u32 u32TotalFreeNum;        /* 累积free次数 */
}MEM_USED_INFO;

/* 内存分配管理信息 */
typedef struct tagMEM_ALLOC_INFO
{
    void*           allocList[MEM_ALLOC_LIST_NUM];              /* 分配后回收的相应内存节点的大小*/
#ifdef BSP_CONFIG_PHONE_TYPE
    void*           allocReserved[MEM_ALLOC_LIST_NUM];          /* 分配后回收的相应内存节点的大小*/
#endif
    u32             allocNum[MEM_ALLOC_LIST_NUM];               /*已经分配出来的相应内存节点的数量*/
    MEM_USED_INFO   allocUsedInfoList[MEM_ALLOC_LIST_NUM];      /*调试使用*/
    MEM_POOL_INFO   memPoolInfo;                                /*内存池信息*/
    u32             mostUsedItem;                               /*最频繁使用的尺寸的标志*/
    u32             u32AllocFailCnt;                            /*分配失败的次数*/
}MEM_ALLOC_INFO;


/**************************************************************************
  全局变量
**************************************************************************/
#ifdef MEM_PRINT_FIND_TIMES
u32 g_MemIsPrintTimes=0;
#endif

static s32 sg_localLockKey = 0;
static MEM_ALLOC_INFO sg_stLocalAllocInfo[1];
/*
AXI 的内容:

SPIN LOCK handle
查找表
全局变量
*/

#define AXI_MEM_ADDR        (g_mem_ctrl.sram_virt_addr)
#define AXI_MEM_SIZE        (g_mem_ctrl.sram_mem_size)
#define MEM_CTX_RESERVED 4
#define MEM_INIT_FLAG       (MEM_CTX_ADDR)
u32* sg_pAllocSizeTbl = NULL;
MEM_ALLOC_INFO* sg_pIccAllocInfo = NULL;
u32* g_mem_init_mark = NULL;

/**************************************************************************
  宏实现
**************************************************************************/
#define MEM_GET_ALLOC_SIZE(i)       (*(sg_pAllocSizeTbl+i))
#define MEM_GET_ALLOC_INFO(type)    (((type) >= MEM_ICC_DDR_POOL) ? \
                                    (((MEM_ALLOC_INFO*)(sg_pIccAllocInfo)) + ((u32)(type)-(u32)MEM_ICC_DDR_POOL)) : \
                                    (&sg_stLocalAllocInfo[MEM_NORM_DDR_POOL]))
#define MEM_MGR_SIZE_FOR_CACHE      MEM_NODE_MGR_SIZE


#define MEM_GET_ALLOC_ADDR(x)       ((void*)((u32)(x)-MEM_NODE_MGR_SIZE))
#define MEM_OFFSET_OF(type, member) ((u32) (&((type *)0)->member))
#define MEM_ITEM_NEXT(x)            (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Next))))
#define MEM_ITEM_SIZE(x)            (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Size))))
#define MEM_ITEM_FLAGS(x)           (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Flags))))
#define MEM_ITEM_MAGIC(x)           (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32MagicNumber))))
#define MEM_ITEM_FILE_NAME(x)       (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32FileName))))
#define MEM_ITEM_LINE(x)            (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Line))))
#define MEM_ITEM_STATUS(x)          (*(u32*)(((u32)(x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Status))))
#define MEM_IS_AXI_ADDR(ptr) \
((unsigned long)(ptr) >= (unsigned long)AXI_MEM_ADDR && (unsigned long)(ptr) < ((unsigned long)AXI_MEM_ADDR + AXI_MEM_SIZE))


#define MEM_LOCAL_LOCK() \
do{\
    local_irq_save(sg_localLockKey);\
}while(0)

#define MEM_LOCAL_UNLOCK() local_irq_restore(sg_localLockKey)

#define MEM_SPIN_LOCK() \
do{\
    MEM_LOCAL_LOCK();\
        (void)bsp_ipc_spin_lock(IPC_SEM_MEM);\
}while(0)

#define MEM_SPIN_UNLOCK() \
do{\
        (void)bsp_ipc_spin_unlock(IPC_SEM_MEM);\
    MEM_LOCAL_UNLOCK();\
}while(0)


#define MEM_LOCK_BY_TYPE(type) \
do{\
    if ((u32)type >= MEM_ICC_DDR_POOL)\
    {\
        MEM_SPIN_LOCK();\
    }\
    else\
    {\
        MEM_LOCAL_LOCK();\
    }\
}while(0)

#define MEM_UNLOCK_BY_TYPE(type) \
do{\
    if ((u32)type >= MEM_ICC_DDR_POOL)\
    {\
        MEM_SPIN_UNLOCK();\
    }\
    else\
    {\
        MEM_LOCAL_UNLOCK();\
    }\
}while(0)

/* Cache操作定义 */
#define MEM_FLUSH_CACHE(ptr, size)      cache_sync()
#define MEM_INVALID_CACHE(ptr, size) (void)osl_cache_invalid(OSL_DATA_CACHE, ptr, size)
#define MEM_FLUSH_CACHE_BY_TYPE(ptr, size, type)\
do{\
    if ((u32)type == MEM_ICC_DDR_POOL)\
    {\
        MEM_FLUSH_CACHE(ptr, size);\
    }\
}while(0)

#define MEM_INVALID_CACHE_BY_TYPE(ptr, size, type)\
do{\
    if ((u32)type == MEM_ICC_DDR_POOL)\
    {\
        MEM_INVALID_CACHE(ptr, size);\
    }\
}while(0)

#define MEM_DEFINE_TIMES()
#define MEM_INC_TIMES()
#define MEM_PRINT_TIMES(size)

/* 在size list 中查找合适的内存节点,如果找不到则返回 MEM_ALLOC_LIST_NUM */
#define MEM_FIND_RIGHT_ITEM(item, size, most_used) \
do {\
    MEM_DEFINE_TIMES();\
    if ((size) > MEM_GET_ALLOC_SIZE(most_used))\
    {\
        MEM_INC_TIMES();\
        for ((item) = (most_used+1); (item) < MEM_ALLOC_LIST_NUM && size > MEM_GET_ALLOC_SIZE(item); (item)++)\
        {\
            MEM_INC_TIMES();\
        }\
    }\
    else\
    {\
        MEM_INC_TIMES();\
        for ((item) = 0; (item) <= (most_used) && (size) > MEM_GET_ALLOC_SIZE(item); (item)++)\
        {\
             MEM_INC_TIMES();\
        }\
        /* 如果无效, 将无效值改为 MEM_ALLOC_LIST_NUM */\
        if ((item) > (most_used))\
        {\
            (item) = MEM_ALLOC_LIST_NUM;\
        }\
    }\
    MEM_PRINT_TIMES(size);\
}while(0)


/**************************************************************************
  内部函数
**************************************************************************/
STATIC BSP_BOOL bsp_ptr_invalid(void* pMem)
{
    u32 u32Type;
    MEM_POOL_INFO* pPoolInfo;
    u32 u32FindMem = 0;

    for (u32Type = MEM_NORM_DDR_POOL; u32Type < MEM_POOL_MAX; u32Type++)
    {
        pPoolInfo = &(MEM_GET_ALLOC_INFO(u32Type)->memPoolInfo);
        if ((u32)pMem >= pPoolInfo->u32BaseAddr ||
            (u32)pMem < pPoolInfo->u32BaseAddr + pPoolInfo->u32Size)
        {
            u32FindMem = 1;
        }
    }
    if (!u32FindMem ||
        MEM_MAGIC_NUM != MEM_ITEM_MAGIC(pMem) ||
        MEM_ITEM_FLAGS(pMem) >= (u32)MEM_POOL_MAX)
    {
        return TRUE;
    }
    return FALSE;
}

STATIC void* bsp_pool_alloc(MEM_ALLOC_INFO* pAllocInfo, u32 u32Size)
{
    u32 u32RetAddr = pAllocInfo->memPoolInfo.u32CurPosAddr;

    if (pAllocInfo->memPoolInfo.u32Left < u32Size)
    {
        mem_print_error("alloc fail! left size = %x alloc size = %x", pAllocInfo->memPoolInfo.u32Left, u32Size);
        return NULL;
    }

    pAllocInfo->memPoolInfo.u32CurPosAddr += u32Size;
    pAllocInfo->memPoolInfo.u32Left -= u32Size;

    return (void*)(u32RetAddr+pAllocInfo->memPoolInfo.u32MgrSize);
}

STATIC void* bsp_get_item(MEM_ALLOC_INFO* pAllocInfo, u32 cnt, u32 u32PoolType, u32 u32Size)
{
    void *pItem;
    void **ppHead = &(pAllocInfo->allocList[cnt]);

    /* 如果链表中没有节点,则从内存池中分配 */
    if (!*ppHead)
    {
        /* 判断是否达到最大个数 */
        if((u32PoolType != MEM_ICC_DDR_POOL) || (pAllocInfo->allocNum[cnt] < sg_AllocMaxNum[cnt]))
        {
	        /* 注意从内存池中分配的尺寸要额外包含 MGR 的部分 */
	        pItem = bsp_pool_alloc(pAllocInfo, u32Size+pAllocInfo->memPoolInfo.u32MgrSize);
	        if (NULL == pItem)
	        {
	            pAllocInfo->u32AllocFailCnt++;
	            return NULL;
	        }
	        MEM_ITEM_MAGIC(pItem) = (u32)MEM_MAGIC_NUM;
	        MEM_ITEM_SIZE(pItem) = u32Size;
	        MEM_ITEM_FLAGS(pItem) = u32PoolType;
		 if(MEM_ICC_DDR_POOL == u32PoolType)
		 {
		     pAllocInfo->allocNum[cnt]++;
		 }
	 #ifdef __BSP_MEM_DEBUG__
	        MEM_ITEM_FILE_NAME(pItem) = 0;
	        MEM_ITEM_LINE(pItem) = 0;
	 #endif
        }
	 else
	 {
	 	pAllocInfo->u32AllocFailCnt++;
	       return NULL;
	 }
    }
    /* 从链表中取出节点 */
    else
    {
        pItem = *ppHead;
        /* Invalid Cache */
        MEM_INVALID_CACHE_BY_TYPE(MEM_GET_ALLOC_ADDR(pItem), MEM_MGR_SIZE_FOR_CACHE, u32PoolType);
        *ppHead = (void*)MEM_ITEM_NEXT(pItem);
    }
    return pItem;
}

STATIC u8* bsp_memory_alloc(u32 u32PoolType, u32 u32Size)
{
    u32 cnt;
    void *pItem;
    MEM_ALLOC_INFO* pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);
    u32 u32MostUsedItem = pAllocInfo->mostUsedItem;

    /* 先查找AllocList中是否有可用的内存节点 */
    MEM_FIND_RIGHT_ITEM(cnt, u32Size, u32MostUsedItem);

    /* 如果没有找到则直接返回失败 */
    if (cnt >= MEM_ALLOC_LIST_NUM)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "Invalid malloc size:%d, line:%d\n", u32Size, __LINE__);
        return NULL;
    }

    /* 更新size为列表中的size */
    u32Size = MEM_GET_ALLOC_SIZE(cnt);

    MEM_LOCK_BY_TYPE(u32PoolType);/*lint !e713*/

    pItem = bsp_get_item(pAllocInfo, cnt, u32PoolType, u32Size);

    if (NULL != pItem)
    {
#ifdef __BSP_MEM_DEBUG__
        pAllocInfo->allocUsedInfoList[cnt].u32CurNum++;
        pAllocInfo->allocUsedInfoList[cnt].u32TotalMallocNum++;

        if (pAllocInfo->allocUsedInfoList[cnt].u32CurNum >
            pAllocInfo->allocUsedInfoList[cnt].u32MaxNum)
        {
            pAllocInfo->allocUsedInfoList[cnt].u32MaxNum =
                pAllocInfo->allocUsedInfoList[cnt].u32CurNum;
        }
        MEM_ITEM_STATUS(pItem) = MEM_ALLOC;
#endif
        /* 多核要 Flush Cache, 确保管理信息写入 */
        MEM_FLUSH_CACHE_BY_TYPE(MEM_GET_ALLOC_ADDR(pItem), MEM_MGR_SIZE_FOR_CACHE, u32PoolType);
    }

    MEM_UNLOCK_BY_TYPE(u32PoolType);

    return pItem;
}

STATIC void bsp_memory_free(u32 u32PoolType, void* pMem, u32 u32Size)
{
    u32 cnt;
    u32 u32MostUsedItem;
    MEM_ALLOC_INFO* pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);

    u32MostUsedItem = pAllocInfo->mostUsedItem;
    /* 先查找AllocList中是否有可用的内存节点 */
    MEM_FIND_RIGHT_ITEM(cnt, u32Size, u32MostUsedItem);
#ifdef __BSP_MEM_DEBUG__
    /* 判断该节点是否有效 */
    if (cnt >= MEM_ALLOC_LIST_NUM)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "memPoolAlloc Fail, size:%d, line:%d\n", u32Size, __LINE__);
        return;
    }
#endif

    MEM_LOCK_BY_TYPE(u32PoolType);/*lint !e713*/

    /* 将item挂回到链表 */
    MEM_ITEM_NEXT(pMem) = (u32)pAllocInfo->allocList[cnt];
    pAllocInfo->allocList[cnt] = pMem;

#ifdef __BSP_MEM_DEBUG__
    pAllocInfo->allocUsedInfoList[cnt].u32CurNum--;
    pAllocInfo->allocUsedInfoList[cnt].u32TotalFreeNum++;
    MEM_ITEM_STATUS(pMem) = MEM_FREE;
#endif
    /* Flush Cache */
    MEM_FLUSH_CACHE_BY_TYPE(MEM_GET_ALLOC_ADDR(pMem), MEM_MGR_SIZE_FOR_CACHE, u32PoolType);

    MEM_UNLOCK_BY_TYPE(u32PoolType);
    return;
}

/*****************************************************************************
* 函 数 名  : bsp_malloc
*
* 功能描述  : BSP 动态内存分配
*
* 输入参数  : u32Size: 分配的大小(byte)
*             enFlags: 内存属性(暂不使用,预留)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
void* bsp_malloc(u32 u32Size, MEM_POOL_TYPE enFlags)
{
    void *pItem;
    pItem = (void *)osl_malloc(u32Size);

    return (void*)pItem;
}

/*****************************************************************************
* 函 数 名  : bsp_malloc_dbg
*
* 功能描述  : BSP 动态内存分配(Debug接口)
*
* 输入参数  : u32Size: 分配的大小(byte)
*             enFlags: 内存属性(暂不使用,预留)
*             pFileName: 使用的源文件
*             u32Line:   所在文件的行号
* 输出参数  : 无
* 返 回 值  : 成功/失败
*****************************************************************************/
void* bsp_malloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line)
{
    u8 *pItem;

    /* 分配内存 */
    pItem = bsp_memory_alloc((u32)enFlags, (u32)u32Size);

#ifdef __BSP_MEM_DEBUG__
    if (NULL != pItem)
    {
        /* Debug模式要更新MGR 信息 */
        MEM_ITEM_LINE(pItem) = u32Line;
        MEM_ITEM_FILE_NAME(pItem) = (u32)pFileName;
    }
#endif
    return (void*)pItem;
}

/*****************************************************************************
* 函 数 名  : bsp_free
*
* 功能描述  : BSP 动态内存释放
*
* 输入参数  : pMem: 动态内存指针
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void  bsp_free(void* pMem)
{
    /* coverity[freed_arg] */
    osl_free(pMem);
}

/*****************************************************************************
* 函 数 名  : BSP_Free
*
* 功能描述  : BSP 动态内存释放(Debug接口)
*
* 输入参数  : pMem: 动态内存指针
*             pFileName: 使用的源文件
*             u32Line:   所在文件的行号
*
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void  bsp_free_dbg(void* pMem, u8* pFileName, u32 u32Line)
{
#ifdef __BSP_MEM_DEBUG__
    /* 检查当前内存是否有效 */
    if (bsp_ptr_invalid(pMem))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "invalid mem block, ptr:0x%x, line:%d\n", pMem, __LINE__);
        return;
    }

    if (MEM_FREE == MEM_ITEM_STATUS(pMem) ||
        MEM_NORM_DDR_POOL != MEM_ITEM_FLAGS(pMem))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "warning! ptr:0x%x, may free twice, or wrong mem flags line:%d\n", pMem, __LINE__);
        return;
    }
#endif

    bsp_free(pMem);

#ifdef __BSP_MEM_DEBUG__
    /* 更新MGR Debug信息 */
    MEM_ITEM_LINE(pMem) = u32Line;
    MEM_ITEM_FILE_NAME(pMem) = (u32)pFileName;
#endif

    return;
}

/*****************************************************************************
* 函 数 名  : BSP_SMalloc
*
* 功能描述  : BSP 动态内存分配(加spin lock保护,多核场景使用)
*
* 输入参数  : u32Size: 分配的大小(byte)
*             enFlags: 内存属性(暂不使用,预留)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
void* bsp_smalloc(u32 u32Size, MEM_POOL_TYPE enFlags)
{
    u8 *pItem;
    if(0 == *g_mem_init_mark)
    {
        return NULL;
    }
    /* 分配内存 */
    pItem = bsp_memory_alloc((u32)enFlags, u32Size);

    return (void*)pItem;
}

/*****************************************************************************
* 函 数 名  : bsp_smalloc_dbg
*
* 功能描述  : BSP 动态内存分配(加spin lock保护,多核场景使用)(Debug接口)
*
* 输入参数  : u32Size: 分配的大小(byte)
*             enFlags: 内存属性(暂不使用,预留)
*             pFileName: 使用的源文件
*             u32Line:   所在文件的行号
* 输出参数  : 无
* 返 回 值  : 成功/失败
*****************************************************************************/
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line)
{
    u8 *pItem;
    if(0 == *g_mem_init_mark)
    {
        return NULL;
    }

#ifdef __BSP_MEM_DEBUG__
    if ((u32)enFlags >= MEM_POOL_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "invalid mem enFlags:%d, line:%d\n", (u32)enFlags, __LINE__);
        return NULL;
    }
#endif

    /* 分配内存 */
    pItem = bsp_memory_alloc((u32)enFlags, u32Size);

    return (void*)pItem;
}

/*****************************************************************************
* 函 数 名  : bsp_sfree
*
* 功能描述  : BSP 动态内存释放(加spin lock保护,多核场景使用)
*
* 输入参数  : pMem: 动态内存指针
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void  bsp_sfree(void* pMem)
{
    u32 u32Size;
    u32 u32Flags;
    if(0 == *g_mem_init_mark)
    {
        return;
    }

#ifdef __BSP_MEM_DEBUG__
    if (bsp_ptr_invalid(pMem))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "warning! ptr:0x%x, invalid mem block line:%d\n", pMem, __LINE__);
        return;
    }
#endif

    /* Invalid Cache */
    if (!MEM_IS_AXI_ADDR(pMem))
    {
        MEM_INVALID_CACHE(MEM_GET_ALLOC_ADDR(pMem), MEM_MGR_SIZE_FOR_CACHE);
    }

#ifdef __BSP_MEM_DEBUG__
    /* 检查当前内存是否有效 */
    if (MEM_FREE == MEM_ITEM_STATUS(pMem))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,
                  "warning! ptr:0x%x, may free twice, or wrong mem status line:%d\n", (unsigned int)pMem, __LINE__);
        return;
    }
#endif

    u32Size = MEM_ITEM_SIZE(pMem);
    u32Flags = MEM_ITEM_FLAGS(pMem);

    bsp_memory_free(u32Flags, pMem, u32Size);
    return;
}

/*****************************************************************************
* 函 数 名  : BSP_SFree
*
* 功能描述  : BSP 动态内存释放(加spin lock保护,多核场景使用)(Debug接口)
*
* 输入参数  : pMem: 动态内存指针
*             pFileName: 使用的源文件
*             u32Line:   所在文件的行号
*
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line)
{
    if(0 == *g_mem_init_mark)
    {
        return;
    }
    bsp_sfree(pMem);
    return;
}

void bsp_mem_init(void)
{
	sg_pAllocSizeTbl = (u32*)(MEM_CTX_ADDR + MEM_CTX_RESERVED);
	sg_pIccAllocInfo = (MEM_ALLOC_INFO*)(MEM_CTX_ADDR + sizeof(sg_AllocListSize) + MEM_CTX_RESERVED);
	g_mem_init_mark = (u32*)MEM_CTX_ADDR;
}


/**************************************************************************
  调试信息实现
**************************************************************************/
STATIC const char* g_memPoolName[] =
{
    "MEM_NORM_DDR_POOL",
    "MEM_ICC_DDR_POOL",
    "MEM_ICC_AXI_POOL",

    "MEM_POOL_MAX"
};

s32 bsp_mem_info(u32 u32MemType)
{
    u32 u32Item;
    MEM_ALLOC_INFO* pAllocInfo;

    if (u32MemType >= MEM_POOL_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"invalid pool type:%d\n", u32MemType);
        return BSP_ERROR;
    }

    //for (u32MemType = MEM_NORM_DDR_POOL; u32MemType < MEM_POOL_MAX; u32MemType++)
    {
        pAllocInfo = MEM_GET_ALLOC_INFO(u32MemType);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Dump Mem (%s):\n", g_memPoolName[u32MemType]);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem pool info:\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"--------------------------------\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Base Addr:          0x%x\n", pAllocInfo->memPoolInfo.u32BaseAddr);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Total Size:         %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Size, pAllocInfo->memPoolInfo.u32Size);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Left Size:          %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Left, pAllocInfo->memPoolInfo.u32Left);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Cur Pos Addr:       0x%x\n", pAllocInfo->memPoolInfo.u32CurPosAddr);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Mgr Size:           %d\n", pAllocInfo->memPoolInfo.u32MgrSize);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Most Used Item:     %d\n", pAllocInfo->mostUsedItem);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Alloc Fail Count:   %d\n", pAllocInfo->u32AllocFailCnt);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem list used info:\n");
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"--------------------------------\n");
        for (u32Item = 0; u32Item < MEM_ALLOC_LIST_NUM; u32Item++)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"+-- dump size:%d list info:\n", MEM_GET_ALLOC_SIZE(u32Item));
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- cur alloc num:  %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32CurNum);
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- max alloc num:  %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32MaxNum);
	     if(u32MemType== MEM_ICC_DDR_POOL)
	     {
	         bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- min num line:   %d\n", sg_AllocMinNum[u32Item]);
	         bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- max num line:   %d\n", sg_AllocMaxNum[u32Item]);
	     }
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- total alloc num:%d\n", pAllocInfo->allocUsedInfoList[u32Item].u32TotalMallocNum);
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"|-- total free num: %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32TotalFreeNum);
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"+-- \n");
        }
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
    }
    return BSP_OK;
}

#if 0
STATIC s32 bsp_mem_dump_block(u32 u32Addr)
{
    BSP_BOOL bBlockInvalid = FALSE;
    bBlockInvalid = bBlockInvalid;

    if (NULL == (void *)u32Addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"can't dump the block, the input ptr is NULL\n");
        return BSP_ERROR;
    }

    if (MEM_MAGIC_NUM != MEM_ITEM_MAGIC(u32Addr))
    {
        bBlockInvalid = TRUE;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"The Block:0x%x may Invalid!\n", u32Addr);
    }

    /* 为确保正确,统一刷下Cache */
    MEM_INVALID_CACHE(MEM_GET_ALLOC_ADDR(u32Addr), MEM_MGR_SIZE_FOR_CACHE);

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"dump mem block info:\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"usr ptr:            0x%x\n",    u32Addr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"alloc ptr:          0x%x\n",    (u32)MEM_GET_ALLOC_ADDR(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"magic num:          0x%x\n",    MEM_ITEM_MAGIC(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"block size:         %d\n",      MEM_ITEM_SIZE(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem flags:          0x%x\n",    MEM_ITEM_FLAGS(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem item next:      0x%x\n",    MEM_ITEM_NEXT(u32Addr));
#ifdef __BSP_MEM_DEBUG__
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"used file name:     %s\n",      (bBlockInvalid) ? ("invalid") : (BSP_CHAR*)MEM_ITEM_FILE_NAME(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"used line:          %d\n",      MEM_ITEM_LINE(u32Addr));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem status:         %s\n",      (MEM_ITEM_STATUS(u32Addr)) ? ("ALLOC") : ("FREE"));
#endif
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
    return BSP_OK;
}

s32 bsp_mem_dump_alloc_list(u32 u32Size, u32 u32PoolType)
{
    u32 u32Item;
    u32 u32MostUsedItem;
    void* pCurAddr;
    u32 u32Num = 0;
    MEM_ALLOC_INFO* pAllocInfo;

    if (u32PoolType >= MEM_POOL_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"invalid pool type:%d\n", u32PoolType);
        return BSP_ERROR;
    }
    pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);
    u32MostUsedItem = pAllocInfo->mostUsedItem;
    MEM_FIND_RIGHT_ITEM(u32Item, u32Size, u32MostUsedItem);

    if (u32Item >= MEM_ALLOC_LIST_NUM)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"invalid size:%d\n", u32Size);
        return BSP_ERROR;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"dump alloc list beg:\n");

    pCurAddr = pAllocInfo->allocList[u32Item];
    for (;NULL != pCurAddr; pCurAddr = (void*)MEM_ITEM_NEXT(pCurAddr))
    {
        (void)bsp_mem_dump_block((u32)pCurAddr);
        u32Num++;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"dump alloc list end, num:%d\n", u32Num);
    return BSP_OK;
}
#endif

STATIC s32 bsp_mem_scan(u32 u32PoolType)
{
    MEM_ALLOC_INFO* pAllocInfo = 0;
    u32 u32CurScan = 0;
    u32 u32EndAddr = 0;
    u32 u32MgrSize = 0;
    s32 s32GetChar = 0;

    pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);
    if (u32PoolType >= MEM_POOL_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"invalid pool type:%d\n", u32PoolType);
        return BSP_ERROR;
    }
    u32CurScan = pAllocInfo->memPoolInfo.u32BaseAddr;
    u32MgrSize = pAllocInfo->memPoolInfo.u32MgrSize;
    u32EndAddr = pAllocInfo->memPoolInfo.u32CurPosAddr;

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Beg Scan Mem (%s):\n", g_memPoolName[u32PoolType]);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"================================\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"mem pool info:\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"--------------------------------\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Base Addr:          0x%x\n", pAllocInfo->memPoolInfo.u32BaseAddr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Total Size:         %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Size, pAllocInfo->memPoolInfo.u32Size);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Left Size:          %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Left, pAllocInfo->memPoolInfo.u32Left);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Cur Pos Addr:       0x%x\n", pAllocInfo->memPoolInfo.u32CurPosAddr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Mgr Size:           %d\n", pAllocInfo->memPoolInfo.u32MgrSize);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"Most Used Item:     %d\n", pAllocInfo->mostUsedItem);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"\n");

    /* 扫描 MemPool */
    while(u32CurScan < u32EndAddr)
    {
        /* 先拿到usr ptr */
        u32CurScan += u32MgrSize;

        /* 打印当前内存块信息 */
        /*(void)bsp_mem_dump_block(u32CurScan);*/

        /* 移动到下一个内存块 */
        u32CurScan += MEM_ITEM_SIZE(u32CurScan);

        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"\npress \'Enter\' to continue, press \'q\' to stop scan\n");
        /*lint -save -e666 -e586*/
        /* coverity[returned_null] */
        s32GetChar = getchar();
        /*lint -restore*/
        if(!s32GetChar)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM,"error! please input a valid char\n");
        }
        if ('q' == s32GetChar)
        {
            break;
        }
    }

    return BSP_OK;
}
void * bsp_cachedma_malloc (unsigned int nBytes)
{
    return (void * )osl_cachedma_malloc((unsigned int)nBytes);
}

int bsp_cachedma_free (void* buf)
{
    return osl_cachedma_free(buf);
}

/*lint -restore +e40 +e413*/

#ifdef __cplusplus
}
#endif /* __cplusplus */



