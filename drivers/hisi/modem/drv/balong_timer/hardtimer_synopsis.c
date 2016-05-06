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

/*lint --e{438,537,713}*/

#include <bsp_hardtimer.h>
#include "hardtimer_core.h"
static u32 is_timer_enabled(struct timer_device *device)
{
	u32 ret = 0;
	ret=readl(TIMER_CONTROLREG(device->base_addr));
	return ret&0x1;
}

static u32 timer_int_status(struct timer_device *device)
{
	return readl(TIMER_INTSTATUS(device->base_addr));
}

static void timer_set_value(struct timer_device *device,unsigned value)
{
	if(value < 1)
		value = 1;
	writel(value,TIMER_LOADCOUNT(device->base_addr));
}

static u32 timer_current_value(struct timer_device *device)
{
	u32 ret = 0;
	ret=readl(TIMER_CONTROLREG(device->base_addr));
	if(ret&0x1)
	{
		ret=readl(TIMER_CURRENTVALUE(device->base_addr));
		if(ret > device->timer_ctrl.timeout){
			if(timer_int_status(device))
				return 0;
			else
				return device->timer_ctrl.timeout;
		}
		else
			return ret;
	}
	else
	{
		return 0x0;
	}
}

static void timer_int_unmask(struct timer_device *device)
{
	u32 ret = 0;
	ret = readl(TIMER_CONTROLREG(device->base_addr));
	writel(ret&(~TIMER_INT_MASK),TIMER_CONTROLREG(device->base_addr));
}

static void timer_int_mask(struct timer_device *device)
{
	u32 ret = 0;
	ret = readl(TIMER_CONTROLREG(device->base_addr));
	writel(ret|TIMER_INT_MASK,TIMER_CONTROLREG(device->base_addr));
}



static void timer_int_clear(struct timer_device *device)
{
	(void)readl(TIMER_EOI(device->base_addr));
}
static s32 timer_disable(struct timer_device *device)
{
	/*最后1bit写0,关闭之前先清中断*/
	u32 ret = 0;
	ret = readl(TIMER_INTSTATUS(device->base_addr));
	if (ret )
	{
		timer_int_clear(device);
	}
	ret = readl(TIMER_CONTROLREG(device->base_addr));
	ret &= ~HARD_TIMER_ENABLE;
	ret |=TIMER_INT_MASK;
	writel(ret,TIMER_CONTROLREG(device->base_addr));
	do{
		ret = readl(TIMER_CONTROLREG(device->base_addr));
	}while(ret&0x1);
	return BSP_OK;
}

static s32 timer_config_init(struct timer_device *device)
{
	u32 readValue = 0;
	(void)timer_disable(device);
	timer_set_value(device,device->timer_ctrl.timeout);
	if (TIMER_ONCE_COUNT == device->timer_ctrl.mode||TIMER_FREERUN_COUNT == device->timer_ctrl.mode)/*自由模式,第2bit写0*/
	{
		readValue = readl(TIMER_CONTROLREG(device->base_addr));
		readValue &= (~0x2);
		writel(readValue,TIMER_CONTROLREG(device->base_addr));
	}
	else/*周期模式,第2bit写1*/
	{
		readValue = readl(TIMER_CONTROLREG(device->base_addr));
		readValue |= 0x2;
		writel(readValue,TIMER_CONTROLREG(device->base_addr));
	}
	return BSP_OK;
}



static s32 timer_enable(struct timer_device *device)
{
	u32 ret = 0;
	(void)timer_disable(device);
	while(readl(TIMER_CURRENTVALUE(device->base_addr))!=(u32)0xffffffff)
	{}
	ret = readl(TIMER_CONTROLREG(device->base_addr));
	ret |= HARD_TIMER_ENABLE ;
	ret&=(~TIMER_INT_MASK);
	writel(ret,TIMER_CONTROLREG(device->base_addr));
	do{
		ret = readl(TIMER_CONTROLREG(device->base_addr));
	}while((ret&0x1)!=0x1);
	return BSP_OK;
}

static void timer_suspend(struct timer_device *device)
{
	device->lp_timer_valuereg  = readl(TIMER_LOADCOUNT(device->base_addr));
	device->lp_timer_ctrlreg = readl(TIMER_CONTROLREG(device->base_addr));	
	return ;
}

static void timer_resume(struct timer_device *device)
{
	(void)timer_disable(device);
	timer_set_value(device,device->lp_timer_valuereg);
	writel(device->lp_timer_ctrlreg,TIMER_CONTROLREG(device->base_addr));
	return ;
}


static struct timer_core_ops  synopsis_timer_ops = {
	.timer_init = timer_config_init,
	.timer_enable = timer_enable,
	.timer_disable = timer_disable,
	.timer_mask = timer_int_mask,
	.timer_unmask = timer_int_unmask,
	.timer_get_cur_value = timer_current_value,
	.timer_int_clear = timer_int_clear,
	.timer_int_status = timer_int_status,
	.timer_set_init_value = timer_set_value,
	.check_timer_enabled = is_timer_enabled,
	.suspend = timer_suspend,
	.resume = timer_resume,
};

static struct timer_driver synopsis_timer_driver = {
    .ops = &synopsis_timer_ops,
    .periphid = 0x0000A001,
    .driver_name = "synopsis timer", 
};

void synopsis_timer_drviver_init(void)
{
	INIT_LIST_HEAD(&synopsis_timer_driver.timer_drivers);
    bsp_timer_driver_register(&synopsis_timer_driver);
}



