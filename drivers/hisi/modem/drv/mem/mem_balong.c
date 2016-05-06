/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*lint -save -e537*/
#include "mem_balong.h"
#include "osl_barrier.h"
/*lint -restore*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************/
/*lint -save -e413 -e19*/
/**************************************************************************/
/**************************************************************************
  宏定义
**************************************************************************/
#ifndef __BSP_MEM_DEBUG__
#define __BSP_MEM_DEBUG__
#endif/*__BSP_MEM_DEBUG__*/

/* 每个内存节点的最大值定义 */
#define MEM_NODE_MGR_SIZE           32

/* MAGIC定义码 */
#define MEM_MAGIC_NUM               0x11223344

/* 内存尺寸分配表 */
u32 sg_AllocListSize[]  =   {32,    128,   512,    1024,   2048, 4096, 8192,   0x4000, 0x8000, 0x10000, 0x20000};
u32 sg_AllocMinNum[]    =   {512,   256,   100,    10,     1,     2,    10,     10,      1,      1,        1};
u32 sg_AllocMaxNum[]    =   {1024,  1024,  1024,   1024,   2048, 100 , 80,     40,      10,     4,        1};

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
    void*           allocList[MEM_ALLOC_LIST_NUM];          /* 分配后回收的相应内存节点的大小*/
    u32         allocNum[MEM_ALLOC_LIST_NUM];            /*已经分配出来的相应内存节点的数量*/
    MEM_USED_INFO   allocUsedInfoList[MEM_ALLOC_LIST_NUM];  /*调试使用*/
    MEM_POOL_INFO   memPoolInfo;                            /*内存池信息*/
    u32         mostUsedItem;                           /*最频繁使用的尺寸的标志*/
    u32         u32AllocFailCnt;                        /*分配失败的次数*/
}MEM_ALLOC_INFO;


/**************************************************************************
  全局变量
**************************************************************************/
LOCAL MEM_ALLOC_INFO sg_stLocalAllocInfo[1];

#define AXI_MEM_ADDR        (SRAM_BASE_ADDR)
#define AXI_MEM_SIZE        (HI_SRAM_MEM_SIZE)

#define MEM_CTX_RESERVED    4

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


#define MEM_GET_ALLOC_ADDR(x)       ((void*)((unsigned long)(x)-(unsigned long)MEM_NODE_MGR_SIZE))
#define MEM_OFFSET_OF(type, member) ((size_t) (&((type *)0)->member))
#define MEM_ITEM_NEXT(x)            (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Next))))
#define MEM_ITEM_SIZE(x)            (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Size))))
#define MEM_ITEM_FLAGS(x)           (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Flags))))
#define MEM_ITEM_MAGIC(x)           (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32MagicNumber))))
#define MEM_ITEM_FILE_NAME(x)       (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32FileName))))
#define MEM_ITEM_LINE(x)            (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Line))))
#define MEM_ITEM_STATUS(x)          (*(u32*)(((x)-MEM_NODE_MGR_SIZE+MEM_OFFSET_OF(MEM_MGR_INFO, u32Status))))
#define MEM_IS_AXI_ADDR(ptr) \
((unsigned long)(ptr) >= (unsigned long)AXI_MEM_ADDR && (unsigned long)(ptr) < ((unsigned long)AXI_MEM_ADDR + AXI_MEM_SIZE))

spinlock_t g_ulMemSpinLock;
unsigned long g_ulMemSpinFlag = 0;

#define MEM_LOCAL_LOCK() \
do{\
    spin_lock_irqsave(&g_ulMemSpinLock, g_ulMemSpinFlag);\
}while(0)

#define MEM_LOCAL_UNLOCK() spin_unlock_irqrestore(&g_ulMemSpinLock, g_ulMemSpinFlag)

#define MEM_SPIN_LOCK() \
do{\
    MEM_LOCAL_LOCK();\
    (void)bsp_ipc_spin_lock((u32)IPC_SEM_MEM);\
}while(0)

#define MEM_SPIN_UNLOCK() \
do{\
    (void)bsp_ipc_spin_unlock((u32)IPC_SEM_MEM);\
    MEM_LOCAL_UNLOCK();\
}while(0)

#define MEM_LOCK_BY_TYPE(type)  \
    do{\
    if ((MEM_POOL_TYPE)type >= MEM_ICC_DDR_POOL)\
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
    if ((MEM_POOL_TYPE)type >= MEM_ICC_DDR_POOL)\
    {\
        MEM_SPIN_UNLOCK();\
    }\
    else\
    {\
        MEM_LOCAL_UNLOCK();\
    }\
}while(0)

/*#define MEM_FLUSH_CACHE(ptr, size)  (void)flush_kernel_vmap_range(ptr,size)*/
#define MEM_FLUSH_CACHE(ptr, size)   mb()
#define MEM_INVALID_CACHE(ptr, size) (void)invalidate_kernel_vmap_range(ptr, size)
#define MEM_FLUSH_CACHE_BY_TYPE(ptr, size, type) \
do{\
    if ((MEM_POOL_TYPE)type == MEM_ICC_DDR_POOL)\
    {\
        MEM_FLUSH_CACHE(ptr, size);\
    }\
}while(0)

#define MEM_INVALID_CACHE_BY_TYPE(ptr, size, type)\
do{\
    if ((MEM_POOL_TYPE)type == MEM_ICC_DDR_POOL)\
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
s32 bsp_init_poll(u32 u32PoolType)
{
    MEM_ALLOC_INFO* pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);

    /* 分配基地址和大小 */
    switch((MEM_POOL_TYPE)u32PoolType)
    {
    case MEM_NORM_DDR_POOL:
        {
 /*           pAllocInfo->memPoolInfo.u32CurPosAddr =
            pAllocInfo->memPoolInfo.u32BaseAddr = (u32)MEM_NORM_DDR_POOL_BASE_ADDR;
            pAllocInfo->memPoolInfo.u32Left =
            pAllocInfo->memPoolInfo.u32Size = MEM_NORM_DDR_POOL_SIZE;
            pAllocInfo->memPoolInfo.u32MgrSize = MEM_MGR_SIZE_FOR_CACHE;
*/
       }
        break;

    case MEM_ICC_DDR_POOL:
        {
            pAllocInfo->memPoolInfo.u32CurPosAddr =
            pAllocInfo->memPoolInfo.u32BaseAddr = (u32)(unsigned long)SHD_DDR_V2P(MEM_ICC_DDR_POOL_BASE_ADDR);
            pAllocInfo->memPoolInfo.u32Left =
            pAllocInfo->memPoolInfo.u32Size = MEM_ICC_DDR_POOL_SIZE;
            pAllocInfo->memPoolInfo.u32MgrSize = MEM_MGR_SIZE_FOR_CACHE;
        }
        break;
    case MEM_ICC_AXI_POOL:
        {
 /*           pAllocInfo->memPoolInfo.u32CurPosAddr =
            pAllocInfo->memPoolInfo.u32BaseAddr = (u32)DRV_AXI_VIRT_TO_PHY(MEM_ICC_AXI_POOL_BASE_ADDR);
            pAllocInfo->memPoolInfo.u32Left =
            pAllocInfo->memPoolInfo.u32Size = MEM_ICC_AXI_POOL_SIZE;
            pAllocInfo->memPoolInfo.u32MgrSize = MEM_MGR_SIZE_FOR_CACHE;
*/
        }
        break;

    default:
        printk("Invalid pool type:%d, line:%d\n",  u32PoolType,  __LINE__);
        return BSP_ERROR;
    }
    if(u32PoolType == MEM_ICC_DDR_POOL)
    {
        if (!pAllocInfo->memPoolInfo.u32BaseAddr )
        {
            printk("Invalid pool ptr, line:%d\n", __LINE__);
            return BSP_ERROR;
        }
        /* 初始化其他全局变量 */
        pAllocInfo->mostUsedItem = 0;
    }
    return BSP_OK;
}

BSP_BOOL bsp_ptr_invalid(const void* pMem)
{
    u32 u32Type;
    MEM_POOL_INFO* pPoolInfo;
    u32 u32FindMem = 0;
	void *pRel = NULL;
    if(NULL == pMem)
    {
        return FALSE;
    }
	pRel = SHD_DDR_V2P(pMem);
    for (u32Type = MEM_NORM_DDR_POOL; u32Type < MEM_POOL_MAX; u32Type++)
    {
        pPoolInfo = &(MEM_GET_ALLOC_INFO(u32Type)->memPoolInfo);
        if ((u32)(unsigned long)pRel >= pPoolInfo->u32BaseAddr ||
            (u32)(unsigned long)pRel < pPoolInfo->u32BaseAddr + pPoolInfo->u32Size)
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

void* bsp_pool_alloc(MEM_ALLOC_INFO* pAllocInfo, u32 u32Size)
{
   u32 u32RetAddr = 0;
   void* pvRetAddr = NULL;
   if (pAllocInfo->memPoolInfo.u32Left < u32Size)
   {
        mem_print_error("alloc fail! left size = %x alloc size = %x", pAllocInfo->memPoolInfo.u32Left, u32Size);
        return NULL;
   }

   u32RetAddr = pAllocInfo->memPoolInfo.u32CurPosAddr;

   pvRetAddr = SHD_DDR_P2V((unsigned long)u32RetAddr);

   pAllocInfo->memPoolInfo.u32CurPosAddr += u32Size;
   pAllocInfo->memPoolInfo.u32Left -= u32Size;

   return (void*)((unsigned long)pvRetAddr+pAllocInfo->memPoolInfo.u32MgrSize);
}

void* bsp_get_item(MEM_ALLOC_INFO* pAllocInfo, u32 cnt, u32 u32PoolType, u32 u32Size)
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
	    pItem = SHD_DDR_P2V(*ppHead);

        /* Invalid Cache */
        MEM_INVALID_CACHE_BY_TYPE(MEM_GET_ALLOC_ADDR(pItem), MEM_MGR_SIZE_FOR_CACHE, u32PoolType);
        *ppHead = (void*)((unsigned long)MEM_ITEM_NEXT(pItem));
    }
    return pItem;
}

u8* bsp_memory_alloc(u32 u32PoolType, u32 u32Size)
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
        printk(
                  "Invalid malloc size:%d, line:%d\n", u32Size, __LINE__);
        return NULL;
    }


    /* 更新size为列表中的size */
    u32Size = MEM_GET_ALLOC_SIZE(cnt);
    /*lint -save -e718 -e746*/
    MEM_LOCK_BY_TYPE(u32PoolType);
    /*lint -restore*/
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

void bsp_memory_free(u32 u32PoolType, void* pMem, u32 u32Size)
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
        printk("bsp_pool_alloc Fail, size:%d, line:%d\n", u32Size, __LINE__);
        return;
    }
#endif

    MEM_LOCK_BY_TYPE(u32PoolType);

    /* 将item挂回到链表 */
    if (MEM_ICC_AXI_POOL == u32PoolType)
    {
#if 0
        MEM_ITEM_NEXT(pMem) = (u32)((unsigned long)(pAllocInfo->allocList[cnt]));
        pAllocInfo->allocList[cnt] = (void*)((unsigned long)(DRV_AXI_VIRT_TO_PHY(pMem)));
#endif
    }
    else if (MEM_ICC_DDR_POOL == u32PoolType)
    {
        MEM_ITEM_NEXT(pMem) = (u32)((unsigned long)(pAllocInfo->allocList[cnt]));
        pAllocInfo->allocList[cnt] = (void *)((unsigned long)SHD_DDR_V2P(pMem));
    }

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

/* 初始化自定义语句 */
int bsp_usr_init(void)
{
    return BSP_OK;
}

s32 bsp_mem_ccore_reset_cb(DRV_RESET_CB_MOMENT_E enParam, int userdata)
{
    u32 u32PoolType = 0;
    u32 u32MaxInitNum = 0;
    if(MDRV_RESET_CB_BEFORE == enParam)
    {
        *g_mem_init_mark = 0;
        MEM_LOCK_BY_TYPE(MEM_ICC_DDR_POOL);
        memset((void*)sg_pIccAllocInfo, 0, (sizeof(MEM_ALLOC_INFO)));
        u32MaxInitNum = MEM_POOL_MAX;
        for (u32PoolType = (u32)MEM_NORM_DDR_POOL; u32PoolType < (u32)u32MaxInitNum; u32PoolType++)
        {
            /* 分配内存池 */
            (void)bsp_init_poll(u32PoolType);
            (void)bsp_set_most_used_size(512, u32PoolType);
        }
        *g_mem_init_mark = 1;
        MEM_UNLOCK_BY_TYPE(MEM_ICC_DDR_POOL);
    }
    return BSP_OK;
}
/**************************************************************************
  接口实现
**************************************************************************/
s32 bsp_mem_init(void)
{
    u32 u32PoolType = 0;
    u32 u32MaxInitNum = 0;

    spin_lock_init(&g_ulMemSpinLock); /*lint !e123 */

    memset((void *)(SHM_BASE_ADDR + SHM_OFFSET_MEMMGR_FLAG), 0, SHM_SIZE_MEMMGR_FLAG);

    g_mem_init_mark = (u32* )MEM_CTX_ADDR;
    sg_pAllocSizeTbl = (u32*)(MEM_CTX_ADDR + MEM_CTX_RESERVED);
    sg_pIccAllocInfo = (MEM_ALLOC_INFO*)(MEM_CTX_ADDR + sizeof(sg_AllocListSize) + MEM_CTX_RESERVED);

    memset((void*)sg_pIccAllocInfo, 0, (sizeof(MEM_ALLOC_INFO)));
    memcpy(sg_pAllocSizeTbl, sg_AllocListSize, sizeof(sg_AllocListSize));
    mb();

    u32MaxInitNum = MEM_POOL_MAX;
    if (bsp_usr_init() != BSP_OK)
    {
        printk("bsp_usr_init call fail, line:%d\n", __LINE__);
    }

    for (u32PoolType = (u32)MEM_NORM_DDR_POOL; u32PoolType < (u32)u32MaxInitNum; u32PoolType++)
    {
        /* 分配内存池 */
        if (BSP_OK != bsp_init_poll(u32PoolType))
        {
            return BSP_ERROR;
        }

        (void)bsp_set_most_used_size(512, u32PoolType);
        mb();
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[mem]: <bsp_mem_init> memory init OK!\n");
    /*初始化成功标示*/
    *g_mem_init_mark = 1;
    mb();
    return BSP_OK;
}
module_init(bsp_mem_init);

s32 bsp_set_most_used_size(u32 u32Size, u32 u32PoolType)
{
    u32 u32Item;

    if (u32PoolType != MEM_ICC_DDR_POOL)
    {
        return BSP_ERROR;
    }

    for ((u32Item) = 0; (u32Item) < MEM_ALLOC_LIST_NUM && u32Size > MEM_GET_ALLOC_SIZE(u32Item); (u32Item)++)
        ;

    if (u32Item >= MEM_ALLOC_LIST_NUM)
    {
        printk("invalid size:%d, line:%d\n", u32Size, __LINE__);
        return BSP_ERROR;
    }

    /* 设置时要设置 MostItem - 1, 方便查找 */
    MEM_GET_ALLOC_INFO(u32PoolType)->mostUsedItem  = (u32Item == 0) ? (0) : (u32Item-1);

    return BSP_OK;
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
    u8 *pItem;
#if 1
    pItem = (u8 *)kmalloc(u32Size, GFP_KERNEL);
    if(pItem == NULL) {
        return NULL;
    }
#else
	if(MEM_NORM_DDR_POOL == enFlags)
	{
		return kmalloc(u32Size, GFP_KERNEL);
	}

    /* 分配内存 */
    pItem = bsp_memory_alloc(enFlags, u32Size);
#endif
    return (void*)pItem;
}
EXPORT_SYMBOL(bsp_malloc);

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
        MEM_ITEM_FILE_NAME(pItem) = (u32)(unsigned long)pFileName;
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
#if 1
	if(pMem)
        /* coverity[freed_arg] */
	    kfree(pMem);
#else
    u32 u32Size;
    u32 u32Flags;
    u32 u32MagicNumber;

    MEM_SPIN_LOCK();
    u32Size = MEM_ITEM_SIZE(pMem);
    u32Flags = MEM_ITEM_FLAGS(pMem);
    u32MagicNumber= MEM_ITEM_MAGIC(pMem);
    MEM_SPIN_UNLOCK();

    if(MEM_MAGIC_NUM != u32MagicNumber)
    {
        kfree(pMem);
    }
    else if(MEM_NORM_DDR_POOL < u32Flags)
    {
	 bsp_memory_free(u32Flags, pMem, u32Size);
    }
    else
    {
        printk("bsp_free failed: pMem is  0x%x, u32MagicNumber is 0x%x, u32Flags is 0x%x\n",(u32)pMem, u32MagicNumber, u32Flags);
    }
#endif
}
EXPORT_SYMBOL(bsp_free);

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
	/* coverity[USE_AFTER_FREE] */
#ifdef __BSP_MEM_DEBUG__
    /* 检查当前内存是否有效 */
    if (bsp_ptr_invalid(pMem))
    {
        printk("invalid mem block, ptr:0x%lx, line:%d\n", (unsigned long)pMem, __LINE__);
        return;
    }

    if (MEM_FREE == MEM_ITEM_STATUS(pMem) ||
        MEM_NORM_DDR_POOL != MEM_ITEM_FLAGS(pMem))
    {
        printk("warning! ptr:0x%lx, may free twice, or wrong mem flags line:%d\n", (unsigned long)pMem, __LINE__);
        return;
    }
#endif
	/* coverity[freed_arg] */
    bsp_free(pMem);

#ifdef __BSP_MEM_DEBUG__
    /* 更新MGR Debug信息 */
	/* coverity[use_after_free] */
    MEM_ITEM_LINE(pMem) = u32Line;
    MEM_ITEM_FILE_NAME(pMem) = (u32)(unsigned long)pFileName;
#endif

    return;
}

/*****************************************************************************
* 函 数 名  : bsp_smalloc
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
EXPORT_SYMBOL(bsp_smalloc);

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
        printk("invalid mem enFlags:%d, line:%d\n", (u32)enFlags, __LINE__);
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

    /* Invalid Cache */
    if (!MEM_IS_AXI_ADDR(pMem))
    {
        MEM_INVALID_CACHE(MEM_GET_ALLOC_ADDR(pMem), MEM_MGR_SIZE_FOR_CACHE);
    }

#ifdef __BSP_MEM_DEBUG__
    /* 检查当前内存是否有效 */
    if (bsp_ptr_invalid(pMem)                     ||
        MEM_FREE == MEM_ITEM_STATUS(pMem)       ||
        MEM_ITEM_FLAGS(pMem) == MEM_NORM_DDR_POOL)
    {
        printk("warning! ptr:0x%lx, invalid mem block, or may free twice, or wrong mem flags line:%d\n", (unsigned long)pMem, __LINE__);
        return;
    }
#endif

    u32Size = MEM_ITEM_SIZE(pMem);
    u32Flags = MEM_ITEM_FLAGS(pMem);

    bsp_memory_free(u32Flags, pMem, u32Size);
    return;
}
EXPORT_SYMBOL(bsp_sfree);

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

/**************************************************************************
  调试信息实现
**************************************************************************/
static const char* g_memPoolName[] =
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
        printk("invalid pool type:%d\n", u32MemType);
        return BSP_ERROR;
    }

        pAllocInfo = MEM_GET_ALLOC_INFO(u32MemType);
        printk("Dump Mem (%s):\n", g_memPoolName[u32MemType]);
        printk("================================\n");
        printk("mem pool info:\n");
        printk("--------------------------------\n");
        printk("Base Addr:          0x%x\n", pAllocInfo->memPoolInfo.u32BaseAddr);
        printk("Total Size:         %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Size, pAllocInfo->memPoolInfo.u32Size);
        printk("Left Size:          %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Left, pAllocInfo->memPoolInfo.u32Left);
        printk("Cur Pos Addr:       0x%x\n", pAllocInfo->memPoolInfo.u32CurPosAddr);
        printk("Mgr Size:           %d\n", pAllocInfo->memPoolInfo.u32MgrSize);
        printk("Most Used Item:     %d\n", pAllocInfo->mostUsedItem);
        printk("Alloc Fail Count:   %d\n", pAllocInfo->u32AllocFailCnt);
        printk("\n");
        printk("================================\n");
        printk("mem list used info:\n");
        printk("--------------------------------\n");
        for (u32Item = 0; u32Item < MEM_ALLOC_LIST_NUM; u32Item++)
        {
            printk("+-- dump size:%d list info:\n", MEM_GET_ALLOC_SIZE(u32Item));
            printk("|-- cur alloc num:  %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32CurNum);
            printk("|-- max alloc num:  %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32MaxNum);
	     if(u32MemType== MEM_ICC_DDR_POOL)
	     {
	         printk("|-- min num line:   %d\n", sg_AllocMinNum[u32Item]);
	         printk("|-- max num line:   %d\n", sg_AllocMaxNum[u32Item]);
	     }
            printk("|-- total alloc num:%d\n", pAllocInfo->allocUsedInfoList[u32Item].u32TotalMallocNum);
            printk("|-- total free num: %d\n", pAllocInfo->allocUsedInfoList[u32Item].u32TotalFreeNum);
            printk("+-- \n");
        }
        printk("================================\n");
    return BSP_OK;
}

#if 0
s32 bsp_mem_dump_block(void * u32Addr)
{
    BSP_BOOL bBlockInvalid = FALSE;

    if (!u32Addr)
    {
        printk("can't dump the block, the input ptr is NULL\n");
        return BSP_ERROR;
    }

    if (MEM_MAGIC_NUM != MEM_ITEM_MAGIC(u32Addr))
    {
        bBlockInvalid = TRUE;
        printk("The Block:%p may Invalid!\n", u32Addr);
    }

    /* 为确保正确,统一刷下Cache */
    MEM_INVALID_CACHE(MEM_GET_ALLOC_ADDR(u32Addr), MEM_MGR_SIZE_FOR_CACHE);

    printk("================================\n");
    printk("dump mem block info:\n");
    printk("================================\n");
    printk("usr ptr:            %p\n",    u32Addr);
    printk("alloc ptr:          %p\n",    MEM_GET_ALLOC_ADDR(u32Addr));
    printk("magic num:          0x%x\n",    MEM_ITEM_MAGIC(u32Addr));
    printk("block size:         %d\n",      MEM_ITEM_SIZE(u32Addr));
    printk("mem flags:          0x%x\n",    MEM_ITEM_FLAGS(u32Addr));
    printk("mem item next:      0x%x\n",    MEM_ITEM_NEXT(u32Addr));
#ifdef __BSP_MEM_DEBUG__
    printk("used file name:     %s\n",      (bBlockInvalid) ? ("invalid") : (BSP_CHAR*)(unsigned long)MEM_ITEM_FILE_NAME(u32Addr));
    printk("used line:          %d\n",      MEM_ITEM_LINE(u32Addr));
    printk("mem status:         %s\n",      (MEM_ITEM_STATUS(u32Addr)) ? ("ALLOC") : ("FREE"));
#endif
    printk("================================\n");
    return BSP_OK;
}

s32 bsp_mem_dump_alloc_list(u32 u32Size, u32 u32PoolType)
{
    u32 u32Item;
    u32 u32MostUsedItem;
    void* pCurAddr;
    u32 u32CurAddr = 0;
    u32 u32Num = 0;
    MEM_ALLOC_INFO* pAllocInfo;

    if (u32PoolType >= MEM_POOL_MAX)
    {
        printk("invalid pool type:%d\n", u32PoolType);
        return BSP_ERROR;
    }
    pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);
    u32MostUsedItem = pAllocInfo->mostUsedItem;
    MEM_FIND_RIGHT_ITEM(u32Item, u32Size, u32MostUsedItem);

    if (u32Item >= MEM_ALLOC_LIST_NUM)
    {
        printk("invalid size:%d\n", u32Size);
        return BSP_ERROR;
    }

    printk("dump alloc list beg:\n");

    pCurAddr = pAllocInfo->allocList[0];
    u32CurAddr = (u32)(unsigned long)SHD_DDR_V2P(pAllocInfo->allocList[0]);
    for (;NULL != pCurAddr; u32CurAddr = MEM_ITEM_NEXT(pCurAddr), pCurAddr = SHD_DDR_P2V((unsigned long)u32CurAddr))
    {
        (void)bsp_mem_dump_block(pCurAddr);
        u32Num++;
    }

    printk("dump alloc list end, num:%d\n", u32Num);
    return BSP_OK;
}
#endif

s32 bsp_mem_scan(u32 u32PoolType)
{
    MEM_ALLOC_INFO* pAllocInfo = NULL;
    void*  u32CurScan;
    void* u32EndAddr;
    u32 u32MgrSize;

    pAllocInfo = MEM_GET_ALLOC_INFO(u32PoolType);
    if (u32PoolType >= MEM_POOL_MAX)
    {
        printk("invalid pool type:%d\n", u32PoolType);
        return BSP_ERROR;
    }
    u32CurScan =  SHD_DDR_P2V((unsigned long)pAllocInfo->memPoolInfo.u32BaseAddr);
    u32MgrSize = pAllocInfo->memPoolInfo.u32MgrSize;
    u32EndAddr = SHD_DDR_P2V((unsigned long)pAllocInfo->memPoolInfo.u32CurPosAddr);

    printk("Beg Scan Mem (%s):\n", g_memPoolName[u32PoolType]);
    printk("================================\n");
    printk("mem pool info:\n");
    printk("--------------------------------\n");
    printk("Base Addr:          0x%x\n", pAllocInfo->memPoolInfo.u32BaseAddr);
    printk("Total Size:         %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Size, pAllocInfo->memPoolInfo.u32Size);
    printk("Left Size:          %d(0x%x)\n", pAllocInfo->memPoolInfo.u32Left, pAllocInfo->memPoolInfo.u32Left);
    printk("Cur Pos Addr:       0x%x\n", pAllocInfo->memPoolInfo.u32CurPosAddr);
    printk("Mgr Size:           %d\n", pAllocInfo->memPoolInfo.u32MgrSize);
    printk("Most Used Item:     %d\n", pAllocInfo->mostUsedItem);
    printk("\n");

    /* 扫描 MemPool */
    while(u32CurScan < u32EndAddr)
    {
        /* 先拿到usr ptr */
        u32CurScan += u32MgrSize;

        /* 打印当前内存块信息 */
        /*(void)bsp_mem_dump_block(u32CurScan);*/

        /* 移动到下一个内存块 */
        u32CurScan += MEM_ITEM_SIZE(u32CurScan);

        printk("\npress \'Enter\' to continue, press \'q\' to stop scan\n");
    }

    return BSP_OK;
}
/*lint -restore +e413 +e19*/
/**************************************************************************
**************************************************************************/
EXPORT_SYMBOL(bsp_mem_info);
EXPORT_SYMBOL(bsp_mem_scan);
EXPORT_SYMBOL(bsp_free_dbg);
EXPORT_SYMBOL(bsp_sfree_dbg);
EXPORT_SYMBOL(bsp_malloc_dbg);
EXPORT_SYMBOL(bsp_smalloc_dbg);

#ifdef __cplusplus
}
#endif /* __cplusplus */



