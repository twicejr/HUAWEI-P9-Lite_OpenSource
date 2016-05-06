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

#include <linux/of.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include <bsp_hardtimer.h>
#include <sys_bus_core.h>
#include <sys_bus_pressure.h>
#include <sys_acore.h>

struct sys_acore g_sys_acore;

void sys_acore_record(struct master* master)
{

}

void sys_acore_report(struct master* master)
{

}

void sys_acore_start(struct master* master)
{
    g_sys_acore.flag = 1;
}

void sys_acore_stop(struct master* master)
{
    g_sys_acore.flag = 0;
}

void sys_acore_thread(void)
{
    while(1)
    {
        if(g_sys_acore.flag)
        {
            memset((void*)g_sys_acore.dst, 0x0, g_sys_acore.size);
            memset((void*)g_sys_acore.src, 0xF, g_sys_acore.size);
            memcpy((void*)g_sys_acore.dst, (const void*)g_sys_acore.src, g_sys_acore.size);
        }
        msleep(10);
    }
}

void sys_acore_init(struct master* master)
{
    dma_addr_t dma_handle;
    struct edma_cb* edma_cb = NULL;

    edma_cb = dma_alloc_coherent(NULL, acore_ddr_size, &dma_handle, \
              GFP_DMA|__GFP_WAIT);
    g_sys_acore.src = (u32)edma_cb;

    edma_cb = dma_alloc_coherent(NULL, acore_ddr_size, &dma_handle, \
              GFP_DMA|__GFP_WAIT);
    g_sys_acore.dst = (u32)edma_cb;

    g_sys_acore.size = acore_ddr_size;

	g_sys_acore.tsk =  kthread_run((void*)sys_acore_thread, (void*)NULL, "sys_acore");
	if (IS_ERR(g_sys_acore.tsk))
	{
		g_sys_acore.tsk = NULL;
		sys_bus_trace("cannot start sys_acore thread\n");
        return;
	}

    master->start = sys_acore_start;
    master->stop = sys_acore_stop;
    master->record = sys_acore_record;
    master->report = sys_acore_report;

    sys_bus_trace("ok\n");
}

