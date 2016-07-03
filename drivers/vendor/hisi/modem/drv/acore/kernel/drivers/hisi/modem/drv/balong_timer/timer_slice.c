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

/*lint --e{537}*/
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <hi_base.h>
#include <osl_types.h>

#include <bsp_version.h>
#include <bsp_hardtimer.h>

struct timerslice_control{
	void* timerslice_base_addr;
	void* timerslice_base_addr_phy;  /*时间戳实地址*/
	void* timerslice_hrt_base_addr;   /*udelay timer stamp addr*/
	u32 hrt_slice_is_increase;
	u32 slice_is_increase;
	u32 hrt_slice_offset[2];                     /*udelay timer stamp 偏移*/
	u32 slice_offset[2];/*32 k slice offset*/
	u32 hrt_slice_clock_freq;
	u32 slice_clock_freq;
	u64 slice_judgetime;
	u32 version_id;
	u32 is_inited_flag ;
};

struct timerslice_control timeslice_ctrl=
{
	NULL,
	NULL,
	NULL,
	0,
	0,
	{0,0},
	{0,0},
	0,
	0,
	0x50000,/*default 10s*/
	0,
	0,
};
void slice_set_judgetime(u64 time_s)
{
	if(timeslice_ctrl.is_inited_flag){
    	timeslice_ctrl.slice_judgetime = timeslice_ctrl.slice_clock_freq*time_s;
		return;
	}
	else
		return;
}

/*****************************************************************************
* 函数  : bbp_get_curtime
* 功能  : 被PS调用，用来获取系统精确时间
* 输入  : void
* 输出  : u64 *pcurtime
* 返回  : u32
*****************************************************************************/
u32 bsp_slice_getcurtime(u64 *pcurtime)
{
	/*lint -save -e958*/
	u64  timervalue[4];
	/*lint -restore*/
	if(timeslice_ctrl.is_inited_flag){
		timervalue[0] = (u64)readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
		timervalue[1] = (u64)readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[1]);
		if(timervalue[0]>=(0xffffffff-timeslice_ctrl.slice_judgetime))
		{
			timervalue[2] = (u64)readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
			timervalue[3] = (u64)readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[1]);

			if(timervalue[2] < timervalue[0])
			{
				(*pcurtime) = ((timervalue[3] - 1) << 32) | timervalue[0];
			}
			else
			{
				(*pcurtime) = (timervalue[1] << 32) | timervalue[0];
			}
		}
		else
			(*pcurtime) = (timervalue[1] << 32) | timervalue[0];
	}
	return 0;
}


u32 bsp_get_slice_value_hrt(void){
	if(timeslice_ctrl.is_inited_flag ){
		if(timeslice_ctrl.hrt_slice_is_increase){
				return readl(timeslice_ctrl.timerslice_hrt_base_addr+timeslice_ctrl.hrt_slice_offset[0]);
			}
			else{
				return (0xFFFFFFFF - readl(timeslice_ctrl.timerslice_hrt_base_addr+timeslice_ctrl.hrt_slice_offset[0]));
			}
	}
	else
		return 0;
}
u32 bsp_get_slice_value(void){
	if(timeslice_ctrl.is_inited_flag ){
		if(timeslice_ctrl.slice_is_increase)
			return readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
		else
			return 0xFFFFFFFF - readl(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
	}
	else
		return 0;
}

u32 bsp_get_elapse_ms(void)
{
	u64 tmp=0;
	unsigned long timer_get = 0;
	if(timeslice_ctrl.is_inited_flag ){
		timer_get = bsp_get_slice_value();
		tmp = (u64)(timer_get & 0xFFFFFFFF);
		tmp = tmp*1000;
		tmp = div_u64(tmp,timeslice_ctrl.slice_clock_freq);
		return (u32)tmp;
	}
	else
		return 0;
}

void* bsp_get_stamp_addr(void)
{
	if(timeslice_ctrl.is_inited_flag )
		return (void*)(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
	else
		return NULL;
}
void* bsp_get_stamp_addr_phy(void)
{
	if(timeslice_ctrl.is_inited_flag )
		return timeslice_ctrl.timerslice_base_addr_phy+timeslice_ctrl.slice_offset[0];
	else
		return NULL;
}

u32 bsp_get_slice_freq(void)
{
	return timeslice_ctrl.slice_clock_freq;
}

int slice_init(void){
	struct device_node *node = NULL;
	void *iomap_node = NULL;
	const u32 *regaddr_p=NULL;
	u64 regaddr64=0, size64=0;
	s32 ret = 0;
	/*p532 fpga 与p532 asic读取同一套dts，所以通过版本号区分slice来源;
	*porting timer slice also come from timer*/
	if(BSP_BOARD_TYPE_SOC == bsp_get_version_info()->board_type|| \
		BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type)
	{
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_stamp");
	}
	else
	{
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_slice");
	}
	if(!node)
	{
		hardtimer_print_error("timer slice of_find_compatible_node failed.\r\n");
		return BSP_ERROR;
	}
	if(!of_device_is_available(node)){
		hardtimer_print_error("timer slice dts status is not ok.\n");
		return BSP_ERROR;
	}
	regaddr_p = of_get_address(node, 0, &size64, NULL);
	if (!regaddr_p) {
		hardtimer_print_error("timer_stamp of_get_address failed.\r\n");
		return BSP_ERROR;
	}

	regaddr64 = of_translate_address(node, regaddr_p);
	timeslice_ctrl.timerslice_base_addr_phy =(void*)(unsigned long)regaddr64;
	iomap_node = of_iomap(node, 0);
	if (NULL == iomap_node)
	{
		hardtimer_print_error("timer slice of_iomap failed.\r\n");
		return BSP_ERROR;
	}
	timeslice_ctrl.timerslice_base_addr =iomap_node;
	
	ret = of_property_read_u32(node, "increase_count_flag", &timeslice_ctrl.slice_is_increase);
	ret |=of_property_read_u32_array(node, "offset", timeslice_ctrl.slice_offset, 2);
	ret |=of_property_read_u32(node, "clock-frequency", &timeslice_ctrl.slice_clock_freq);
	if(ret)
	{
		hardtimer_print_error("timer slice property get failed.\r\n");
		return BSP_ERROR;
	}
	return BSP_OK;
}
int hrt_slice_init(void){
	struct device_node *node = NULL;
	char* hrttimer_slice = "hisilicon,hrttimer_slice";
	void *iomap_node = NULL;
	s32 ret = 0;
	node = of_find_compatible_node(NULL, NULL, hrttimer_slice);
	if(!node)
	{
		hardtimer_print_error("timer_hrtslice of_find_compatible_node failed.\n");
		return BSP_ERROR;
	}
	if(!of_device_is_available(node)){
		hardtimer_print_error("timer hrtslice dts status is not ok.\n");
		return BSP_ERROR;
	}
	/* 内存映射，获得基址 */
	iomap_node = of_iomap(node, 0);
	if (NULL == iomap_node)
	{
		hardtimer_print_error("hrttimer_app of_iomap failed.\n");
		return BSP_ERROR;
	}
	timeslice_ctrl.timerslice_hrt_base_addr = iomap_node;
	ret  = of_property_read_u32(node, "increase_count_flag", &timeslice_ctrl.hrt_slice_is_increase);
	ret |= of_property_read_u32(node, "clock-frequency", &timeslice_ctrl.hrt_slice_clock_freq);
	ret |= of_property_read_u32_array(node, "offset", timeslice_ctrl.hrt_slice_offset, 2);
	if(ret)
	{
		hardtimer_print_error("timer_hrtslice get property failed.\n");
		return BSP_ERROR;
	}
	
	return BSP_OK;
}

int bsp_slice_init(void)
{
	int ret = 0;
	ret=slice_init();
	ret|=hrt_slice_init();
	if(ret){
		hardtimer_print_error("failed.\n");
		return BSP_ERROR;
	}
	timeslice_ctrl.is_inited_flag = 1;
	hardtimer_print_error("ok.\n");
	return BSP_OK;
}
int test_timer_slice(void)
{
	u32 low=0,high=0;
	if(mdrv_timer_get_accuracy_timestamp(&high,&low))
		return -1;
	else{
		hardtimer_print_error("low =0x%x\n",low);
		hardtimer_print_error("high =0x%x\n",high);
	}
	return 0;
}
EXPORT_SYMBOL(bsp_get_slice_value);
EXPORT_SYMBOL(bsp_get_slice_value_hrt);
EXPORT_SYMBOL(bsp_get_elapse_ms);
EXPORT_SYMBOL(bsp_get_stamp_addr);
EXPORT_SYMBOL(bsp_get_stamp_addr_phy);
core_initcall(bsp_slice_init);

