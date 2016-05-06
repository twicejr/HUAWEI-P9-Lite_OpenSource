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
#include <soc_memmap.h>
#include <bsp_om.h>
#include <bsp_s_memory.h>
#include <bsp_ddr.h>

#define  s_mem_pr_err(fmt, ...) \
	(printk(KERN_ERR "[s_mem]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
struct mem_ctrl g_mem_ctrl;

static int __init bsp_shared_mem_init(void)
{
#ifndef CONFIG_SRAM_SECURE
	g_mem_ctrl.sram_phy_addr = (void*)HI_SRAM_MEM_ADDR;
	g_mem_ctrl.sram_mem_size  = HI_SRAM_SIZE;
	g_mem_ctrl.sram_virt_addr = (void*)ioremap_wc((unsigned long)g_mem_ctrl.sram_phy_addr, g_mem_ctrl.sram_mem_size);
#endif
	g_mem_ctrl.sddr_phy_addr  = (void*)HI_SHARED_DDR_BASE_ADDR;
	g_mem_ctrl.sddr_mem_size  = HI_SHARED_DDR_SIZE;
	g_mem_ctrl.sddr_virt_addr = (void*)ioremap_wc((unsigned long)g_mem_ctrl.sddr_phy_addr, g_mem_ctrl.sddr_mem_size);
	s_mem_pr_err("ok!\n");
	
	return 0;
}

core_initcall(bsp_shared_mem_init);
EXPORT_SYMBOL_GPL(g_mem_ctrl);

