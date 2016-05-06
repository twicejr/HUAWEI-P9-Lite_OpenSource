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
#ifndef    _BSP_MEM_H_
#define    _BSP_MEM_H_

#include <linux/highmem.h>
#include <bsp_sram.h>
#include <drv_comm.h>
#include <asm/cacheflush.h>
#include <asm/cache.h>
#include <asm/tlbflush.h>
#include <linux/module.h>
#include <bsp_shared_ddr.h>
#include <bsp_om.h>
#include <mdrv_ipc.h>
#include <bsp_ipc.h>
#include <mdrv_memory.h>
#include <bsp_memmap.h>
#include "mem_balong_drv.h"
#include <osl_spinlock.h>
#include <bsp_reset.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  宏定义
**************************************************************************/
#if defined (VERSION_V3R2)

#else
#define PBXA9_DRAM_SHARE_VIRT            IO_ADDRESS(PBXA9_DRAM_SHARE_PHYS)
#define PBXA9_DRAM_SHARE_SIZE            SZ_1M
#endif

#define VX_PBXA9_DRAM_SHARE_VIRT            IO_ADDRESS(VX_PBXA9_DRAM_SHARE_PHYS)
#define VX_PBXA9_DRAM_SHARE_SIZE            SZ_64M


#define  mem_print_error(fmt,...)      (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mem_print_dbg(fmt,...)		       (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))

/**************************************************************************
  函数声明
**************************************************************************/
s32 bsp_mem_init(void);
s32 bsp_mem_ccore_reset_cb(DRV_RESET_CB_MOMENT_E enParam, int userdata);
s32 bsp_set_most_used_size(u32 u32Size, u32 u32PoolType);

void* bsp_malloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_malloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_free(void* pMem);
void  bsp_free_dbg(void* pMem, u8* pFileName, u32 u32Line);

void* bsp_smalloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_sfree(void* pMem);
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line);


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
#define BSP_MALLOC(sz, flags) bsp_malloc_dbg(sz, flags, __FILE__, __LINE__)
#else
#define BSP_MALLOC(sz, flags) bsp_malloc(sz, flags)
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



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_MEM_H_ */

