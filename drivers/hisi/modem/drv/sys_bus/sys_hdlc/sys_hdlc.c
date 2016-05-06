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

#include "product_config.h"
#include <osl_thread.h>
#include <dma-mapping.h>
#include "sys_hdlc.h"
#include "hdlc_for_bbit.h"
#include "osl_bio.h"
#include "baseaddr.h"
#include <sys_bus_pressure.h>


#define STRESS_TEST_BYTE 1024

UINT32 src_addr_hdlc = 0;
UINT32 des_addr_hdlc = 0;
struct device hdlc_dev;
void * sys_bus_sysctrl_crg_addr;
void * sys_bus_hdlc_base_addr;


int g_hdlc_stress_start = 0;

int hdlc_test(void)
{
	sys_mem_clr(src_addr_hdlc, 0x400);  //clear ipf source data memory
    sys_mem_clr(des_addr_hdlc, 0x400);   //clear ipf destination data memory
    return hdlcv200_frm_def_test_bbit(src_addr_hdlc, des_addr_hdlc);
}

int sys_hdlc_test(void)
{
    int ret = 0;

    if (!(src_addr_hdlc && des_addr_hdlc))
    {
        printk("cacheDmaMalloc Fail!\n");
        return ERROR;
    }
    
    ret = hdlc_test();    
    if(ret){
        printk("sys_hdlc_test fail\n");
        ret = 1;
    }
    return ret;

}
u32 count = 0;
int g_delay = 2;

void sys_hdlc_routine(void)
{
	while(g_hdlc_stress_start)
	{
		sys_hdlc_test();
		osl_task_delay(g_delay);
		count++;
	}
	return ;
}
OSL_TASK_ID  sys_hdlc_stress_test_task_id = 0;
void sys_hdlc_start(struct master* master)
{
	//UINT32 reg = 0x1F80000;  
	/*?a?¡ä??*/
	int ret = 0;
    dma_addr_t src_dma_addr_hdlc;
    dma_addr_t des_dma_addr_hdlc;
	
	g_delay = 2;

    hdlc_dev.coherent_dma_mask = ~0;

	src_addr_hdlc   = (UINT32)dma_alloc_coherent(NULL, STRESS_TEST_BYTE, &src_dma_addr_hdlc, GFP_KERNEL);
	des_addr_hdlc   = (UINT32)dma_alloc_coherent(NULL, STRESS_TEST_BYTE, &des_dma_addr_hdlc, GFP_KERNEL);
	g_hdlc_stress_start = 1;

    /*task_priority = 10;*/
	ret = osl_task_init ("guTask", 10, 80000, (OSL_TASK_FUNC)sys_hdlc_routine, NULL, &sys_hdlc_stress_test_task_id);
	if(ret == -1)
	{
		printk("sys_hdlc_routine fail.\n");
	}
    printk("sys_hdlc_routine start finish.\n");	
}

void sys_hdlc_stop(struct master* master)
{
	g_hdlc_stress_start = 0;
}

void sys_hdlc_init(struct master* master)
{
    sys_bus_sysctrl_crg_addr = ioremap(HI_MODEM_SC_BASE_ADDR, 4096);
    sys_bus_hdlc_base_addr = ioremap(HI_HDLC_REGBASE_ADDR, 4096);
    
    master->start = sys_hdlc_start;
    master->stop = sys_hdlc_stop;
    master->record = NULL;
    master->report = NULL;
}



