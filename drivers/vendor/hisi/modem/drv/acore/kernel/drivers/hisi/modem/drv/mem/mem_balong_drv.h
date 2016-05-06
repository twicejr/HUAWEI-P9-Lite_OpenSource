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
#ifndef    _BSP_MEM_DRV_H_
#define    _BSP_MEM_DRV_H_

#include <linux/slab.h>
#include "bsp_sram.h"
#include "bsp_shared_ddr.h"


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ASIC2 调试 */

#ifndef INLINE
#define INLINE /*__inline__*/
#endif

/**************************************************************************
  宏定义
**************************************************************************/
/* 主核定义 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define BSP_MEM_MAIN_PART
#endif

/* 长度定义 */
/* 长度定义 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define MEM_NORM_DDR_POOL_SIZE      (512*1024)
#else
#define MEM_NORM_DDR_POOL_SIZE      (4096)/*2^n*4K*/
#endif
#define MEM_ICC_DDR_POOL_SIZE       (SHM_SIZE_MEMMGR)
#define MEM_ICC_AXI_POOL_SIZE       (SRAM_SIZE_DYNAMIC_SEC)

/* Mem 全局变量放在AXI中 */
#define MEM_CTX_ADDR                ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR_FLAG)


/* 基地址定义 */
#define _ALIGN(addr, size) (((addr) + (size) - 1) & (~((size) - 1)))
#define MEM_NORM_DDR_POOL_BASE_ADDR (__get_free_pages(GFP_KERNEL, 0))//(kmalloc( _ALIGN(MEM_NORM_DDR_POOL_SIZE, 32), GFP_KERNEL))
#define MEM_ICC_AXI_POOL_BASE_ADDR  ((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC)
#define MEM_ICC_DDR_POOL_BASE_ADDR  ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR)


/* 使用ACP模式不需要刷 Cache */
//#define MEM_USE_ACP

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* _BSP_MEM_DRV_H_ */



