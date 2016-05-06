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

#include <drv_comm.h>
#include <mdrv_memory.h>
#include <linux/slab.h>
#include <osl_types.h>

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
void * mdrv_memcpy(void * dest, const void * src, unsigned long count)
{
    return memcpy(dest,src,count);
}

#if 0

/*******************以下为打桩函数*********************************/
BSP_VOID* bsp_malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return kmalloc(u32Size, GFP_KERNEL);
}
BSP_VOID* bsp_malloc_dbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line)
{
    return kmalloc(u32Size, GFP_KERNEL);
}
BSP_VOID  bsp_free(BSP_VOID* pMem)
{
    kfree(pMem);
    return;
}
BSP_VOID  bsp_free_dbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line)
{
    kfree(pMem);
    return;
}
BSP_VOID* bsp_smalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return kmalloc(u32Size, GFP_KERNEL);
}
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line)
{
    return kmalloc(u32Size, GFP_KERNEL);
}
BSP_VOID  bsp_sfree(BSP_VOID* pMem)
{
    kfree(pMem);
    return;
}
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line)
{
    kfree(pMem);
    return;
}
#endif


