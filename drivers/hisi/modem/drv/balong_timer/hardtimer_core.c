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

/*lint --e{438,537,666,713}*/
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/printk.h>
#include <linux/platform_device.h>

#include <osl_module.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include "hardtimer_core.h"
static LIST_HEAD(timer_drivers_head);
#define DRIVER_NAME "balong_timer_device"

struct wakeup_timer_ctrl_s{
	u32 count;
	int request_id[TIMER_ID_MAX];
};
struct timercore_ctrl_s{
	struct timer_device timer[TIMER_ID_MAX];
	struct wakeup_timer_ctrl_s wakeup_timer;
	spinlock_t list_lock;
}core_timer_control;
static inline u32 check_timer_valid(u32 timer_id) {
	if(core_timer_control.timer[timer_id].clk) 
		return 1;
	else 
		return 0;
}

void bsp_hardtimer_load_value(u32 timer_id, u32 value)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	if(value < 1)
		value = 1;
	core_timer_control.timer[timer_id].driver->ops->timer_set_init_value(&core_timer_control.timer[timer_id],value);
	core_timer_control.timer[timer_id].timer_ctrl.timeout = value;
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
}

u32 bsp_get_timer_current_value(u32 timer_id)
{
	u32 ret = 0;
	unsigned long flags = 0;
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	ret = core_timer_control.timer[timer_id].driver->ops->timer_get_cur_value(&core_timer_control.timer[timer_id]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
	return ret;
}

int bsp_get_timer_rest_time(u32 timer_id, DRV_TIMER_UNIT_E unit,unsigned int *rest)
{
	u32 timer_clk = 0,ret = 0;
	if(!check_timer_valid(timer_id)){
		return BSP_ERROR;
	}
	if(!core_timer_control.timer[timer_id].driver->ops->check_timer_enabled(&core_timer_control.timer[timer_id]))/*if 0, it is to say not enabled*/
	{
		*rest=0;/*osa timer request return 0 if not enabled*/
		return BSP_OK;
	}
	timer_clk = core_timer_control.timer[timer_id].clk;
	ret = bsp_get_timer_current_value(timer_id);
	if(TIMER_UNIT_NONE == unit){
		*rest = ret;
	}
	else if(TIMER_UNIT_US == unit){
		*rest=(ret*1000)/(timer_clk/1000);
	}
	else if(TIMER_UNIT_MS== unit){
		*rest=ret/(timer_clk/1000);
	}
	else
	{
		return BSP_ERROR;
	}
	return BSP_OK;
}

void bsp_hardtimer_int_unmask(u32 timer_id)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	core_timer_control.timer[timer_id].driver->ops->timer_unmask(&core_timer_control.timer[timer_id]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
}

void bsp_hardtimer_int_mask(u32 timer_id)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	core_timer_control.timer[timer_id].driver->ops->timer_mask(&core_timer_control.timer[timer_id]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
}
u32 bsp_hardtimer_int_status(u32 timer_id)
{
	return core_timer_control.timer[timer_id].driver->ops->timer_int_status(&core_timer_control.timer[timer_id]);
}

void bsp_hardtimer_int_clear(u32 timer_id)
{
	core_timer_control.timer[timer_id].driver->ops->timer_int_clear(&core_timer_control.timer[timer_id]);
}
s32 bsp_hardtimer_disable(u32 timer_id)
{
	unsigned long flags = 0;
	s32 ret = 0;
	if(!check_timer_valid(timer_id)){
		return BSP_ERROR;
	}
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	ret = core_timer_control.timer[timer_id].driver->ops->timer_disable(&core_timer_control.timer[timer_id]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
	return ret;
}

s32 bsp_hardtimer_config_init(struct bsp_hardtimer_control  *timer_ctrl)
{
	s32 ret = 0;
	unsigned long flags = 0;
	if(!check_timer_valid(timer_ctrl->timerId)){
		return BSP_ERROR;
	}
	spin_lock_irqsave(&core_timer_control.timer[timer_ctrl->timerId].lock,flags);
	memcpy((void*)&core_timer_control.timer[timer_ctrl->timerId].timer_ctrl,(const void*)timer_ctrl,(size_t)sizeof(struct bsp_hardtimer_control));
	ret = core_timer_control.timer[timer_ctrl->timerId].driver->ops->timer_init(&core_timer_control.timer[timer_ctrl->timerId]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_ctrl->timerId].lock,flags);
	if(timer_ctrl->func)
	{
		ret = request_irq(core_timer_control.timer[timer_ctrl->timerId].irq, (irq_handler_t)timer_ctrl->func, 0, "hard_timer_irq",(void *)(timer_ctrl->para));
		if (ret)
		{
			hardtimer_print_error("request_irq error,ret = %d\n",ret);
			return BSP_ERROR;
		}
	}
	return ret;
}
static s32 timer_start_ms(struct bsp_hardtimer_control  *timer_ctrl)
{
	u32 timer_clk=0;
	s32 ret = 0;
	timer_clk = core_timer_control.timer[timer_ctrl->timerId].clk;
	if(timer_clk%1000)/*32k,minish computation error*/
	{
		if(timer_ctrl->timeout<(0xFFFFFFFF/timer_clk))
			timer_ctrl->timeout= timer_clk*timer_ctrl->timeout/1000;
		else
			timer_ctrl->timeout= timer_clk/1000*timer_ctrl->timeout;
	}
	else
	{
		timer_ctrl->timeout = timer_clk/1000*timer_ctrl->timeout ;
	}
	ret = bsp_hardtimer_config_init(timer_ctrl);
	if(BSP_OK!=ret){
		hardtimer_print_error("bsp_hardtimer_config_init error \n");
		return BSP_ERROR;
	}
	ret = bsp_hardtimer_enable(timer_ctrl->timerId);/* [false alarm]:误报 */
	return ret;
}

static s32 timer_start_us(struct bsp_hardtimer_control  *timer_ctrl)
{
	u32 timer_clk=0;
	s32 ret = 0;
	timer_clk = core_timer_control.timer[timer_ctrl->timerId].clk;
	if(timer_clk%1000)/*32k,minish computation error*/
	{
		if(timer_ctrl->timeout > TIMER_32K_US_BOUNDARY)
			timer_ctrl->timeout= timer_clk*timer_ctrl->timeout/1000000;
		
		else/* 对于不大于31us的定时，直接往load寄存器写1 */
			timer_ctrl->timeout=1;
	}
	else
	{
		timer_ctrl->timeout = timer_clk/1000*timer_ctrl->timeout/1000;
	}
	ret = bsp_hardtimer_config_init(timer_ctrl);
	if(BSP_OK!=ret){
		hardtimer_print_error("bsp_hardtimer_config_init error \n");
		return BSP_ERROR;
	}
	ret = bsp_hardtimer_enable(timer_ctrl->timerId);/* [false alarm]:误报 */
	return ret;
}
static s32 timer_start_none(struct bsp_hardtimer_control  *timer_ctrl){
	s32 ret = 0;
	ret = bsp_hardtimer_config_init(timer_ctrl);
	if(BSP_OK!=ret){
		hardtimer_print_error("bsp_hardtimer_config_init error \n");
		return BSP_ERROR;
	}
	ret = bsp_hardtimer_enable(timer_ctrl->timerId);/* [false alarm]:误报 */
	return ret;
}

s32 bsp_hardtimer_start(struct bsp_hardtimer_control  *timer_ctrl)
{
	s32 ret = 0;
	if(NULL == timer_ctrl){
		hardtimer_print_error("timer_ctrl is NULL \n");
		return BSP_ERROR;
	}
	/*直接操作寄存器*/
	if(TIMER_UNIT_NONE==timer_ctrl->unit){
		ret = timer_start_none(timer_ctrl);
		return ret;
	}
	else if(TIMER_UNIT_MS ==timer_ctrl->unit ){
		ret = timer_start_ms(timer_ctrl);
		return ret;
	}
	else if(TIMER_UNIT_US ==timer_ctrl->unit ){
		ret = timer_start_us(timer_ctrl);
		return ret;
	}
	else{
		hardtimer_print_error("timer_ctrl->unit error \n");
		return BSP_ERROR;
	}
}

s32 bsp_hardtimer_enable(u32 timer_id)
{
	unsigned long flags = 0;
	s32 ret = 0;
	if(!check_timer_valid(timer_id)){
		return BSP_ERROR;
	}
	spin_lock_irqsave(&core_timer_control.timer[timer_id].lock,flags);
	ret = core_timer_control.timer[timer_id].driver->ops->timer_enable(&core_timer_control.timer[timer_id]);
	spin_unlock_irqrestore(&core_timer_control.timer[timer_id].lock,flags);
	return ret;
}

s32 bsp_hardtimer_free(u32 timer_id)
{
	if(!check_timer_valid(timer_id)){
		return BSP_ERROR;
	}
	(void)bsp_hardtimer_disable(timer_id);
	osl_free_irq(core_timer_control.timer[timer_id].irq,core_timer_control.timer[timer_id].timer_ctrl.func,core_timer_control.timer[timer_id].timer_ctrl.para);
	core_timer_control.timer[timer_id].timer_ctrl.func = NULL;
	core_timer_control.timer[timer_id].timer_ctrl.para = NULL;
	return BSP_OK;
}

/*获取唤醒源timer的下一个最近到时时间，供低功耗模块使用*/
u32 get_next_schedule_time(void)
{
	u32 i=0,min = 0xffffffff,ret = 0,request_id = 0;/*lint !e123*/
	for(i=0;i<core_timer_control.wakeup_timer.count;i++)
	{
		request_id = core_timer_control.wakeup_timer.request_id[i];
		if(!core_timer_control.timer[request_id].driver->ops->check_timer_enabled(&core_timer_control.timer[request_id]))
		{
			ret = 0xFFFFFFFF;
		}
		else
		{
			(void)bsp_get_timer_rest_time(request_id,TIMER_UNIT_MS,(unsigned int*)&ret);
		}
		if(ret<min)/*lint !e123*/
			min = ret;/*lint !e123*/
	}
 	return min;/*lint !e123*/
}

void bsp_timer_driver_register(struct timer_driver  *driver)
{
	unsigned long flags;

    spin_lock_irqsave(&core_timer_control.list_lock,flags);
    list_add_tail(&driver->timer_drivers, &timer_drivers_head);
    spin_unlock_irqrestore(&core_timer_control.list_lock,flags);
    return ;
}
static struct timer_driver *get_timer_driver(struct timer_device *device)
{
    struct timer_driver *drv=NULL;
    unsigned long flags=0;
    spin_lock_irqsave(&core_timer_control.list_lock,flags);
    if (!list_empty(&timer_drivers_head)) {
        list_for_each_entry(drv, &timer_drivers_head, timer_drivers) {
            if (drv->periphid == device->periphid){
                 spin_unlock_irqrestore(&core_timer_control.list_lock,flags);
                return drv;
            }
        }
    }
    spin_unlock_irqrestore(&core_timer_control.list_lock,flags);

    return NULL;
}

static int timer_device_init(void){
	struct device_node *node = NULL, *child_node=NULL;
	u32 index = 0,wake_flag = 0;
	int ret_value = 0;
	struct timer_driver *drv=NULL;
	node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_device");
	if(node)
	{
		for_each_available_child_of_node(node, child_node){
			ret_value = of_property_read_u32(child_node, "request_id", &index) ;
			if(ret_value)
			{
				hardtimer_print_error("request_id get failed.\n");
				return BSP_ERROR;
			}
			/*1.judge is wake timer or not*/
			if(of_property_read_u32(child_node,"wakesrc",&wake_flag)){
				hardtimer_print_error("wakesrc get failed.\n");
				return BSP_ERROR;
			}
			if(wake_flag)
			{
				core_timer_control.wakeup_timer.request_id[core_timer_control.wakeup_timer.count] = index;
				core_timer_control.wakeup_timer.count++;
			}
			/*2. get timer base info,include baseaddr\irq\clk\sr_flag\name\periphid*/
			core_timer_control.timer[index].base_addr = of_iomap(child_node, 0);
			if(!core_timer_control.timer[index].base_addr ){
				hardtimer_print_error("timer request_id %d iomap failed.\n",index);
				return BSP_ERROR;
			}
			
			core_timer_control.timer[index].irq = irq_of_parse_and_map(child_node, 0);
			ret_value = of_property_read_u32(child_node, "clock-frequency", &core_timer_control.timer[index].clk);
			ret_value |= of_property_read_u32(child_node, "sr_flag", &core_timer_control.timer[index].sr_flag);
			ret_value |= of_property_read_string(child_node, "timer_name", (const char**)&core_timer_control.timer[index].name);	    	
			ret_value |= of_property_read_u32(child_node, "periphid", &core_timer_control.timer[index].periphid);
			if(ret_value){
				hardtimer_print_error("timer %d get properity failed.\n",index);
				return BSP_ERROR;
			}
			drv = get_timer_driver(&core_timer_control.timer[index]);
			if(drv){
				core_timer_control.timer[index].driver = drv;
			}
			else{
				hardtimer_print_error("timer %d drv get failed.\n",index);
				return BSP_ERROR;
			}
			spin_lock_init(&core_timer_control.timer[index].lock);
		}
		return BSP_OK;
	}
	else
		return BSP_ERROR;
}

static int bsp_timer_probe(struct platform_device *dev){
	s32 ret = 0;
	(void)memset((void*)&core_timer_control,0x0,sizeof(struct timercore_ctrl_s));
	spin_lock_init(&core_timer_control.list_lock);
	arm_timer_drviver_init();
	synopsis_timer_drviver_init();
	ret = timer_device_init();
	ret |= set_adp_timer_isr_and_pm();
	if(ret){
		hardtimer_print_error("err\n");
		return -1;
	}
	else{
		hardtimer_print_error("ok\n");
		return 0;
	}
}

#ifdef CONFIG_PM

static s32 timer_suspend_noirq(struct device *dev)
{
	int i=0;
	u32 stamp = 0;
	pr_info("%s +\n", __func__);
	/*遍历timer，保存sr_flag为1，即为掉电区timer的sysctrl reg和load reg 寄存器值*/
	for(i=0;i<TIMER_ID_MAX;i++){
		if(core_timer_control.timer[i].sr_flag && core_timer_control.timer[i].driver->ops->suspend){
			core_timer_control.timer[i].driver->ops->suspend(&core_timer_control.timer[i]);
		}/*core_timer_control[i].sr_flag*/
		else
			continue;
	}/*FOR*/
	stamp = bsp_get_slice_value();
	while(get_timer_slice_delta(stamp,bsp_get_slice_value())< 2){}
	pr_info("%s -\n", __func__);
	return BSP_OK;
}
static s32 timer_resume_noirq(struct device *dev)
{
	u32 i=0;
	pr_info("%s +\n", __func__);
	for(i=0;i<TIMER_ID_MAX;i++){
		if(core_timer_control.timer[i].sr_flag && core_timer_control.timer[i].driver->ops->resume ){
			core_timer_control.timer[i].driver->ops->resume(&core_timer_control.timer[i]);
		}
		else
			continue;
	}
	pr_info("%s -\n", __func__);
	return BSP_OK;
}
static const struct dev_pm_ops timer_pm_ops ={
	.suspend_noirq = timer_suspend_noirq,
	.resume_noirq   = timer_resume_noirq,
};
#define BALONG_DEV_PM_OPS (&timer_pm_ops)
#else
#define BALONG_DEV_PM_OPS NULL
#endif
static struct platform_driver balong_timer_driver = {
	.probe = bsp_timer_probe,
	.driver = {
		.name = DRIVER_NAME,
		.owner  = THIS_MODULE,
		.pm     = BALONG_DEV_PM_OPS,
	},
};
static struct platform_device balong_timer_device =
{
    .name = DRIVER_NAME,
    .id       = -1,
    .num_resources = 0,
};
static int __init hi_timer_init(void)
{
	s32 ret = 0;
	ret = platform_device_register(&balong_timer_device);
	if(ret)
	{
		hardtimer_print_error("balong_timer_driver device register is failed!\n");
        return ret;
	}
	ret = platform_driver_register(&balong_timer_driver);
	if (ret)
	{
		hardtimer_print_error("balong_timer_driver deriver register is failed!\n");
		platform_device_unregister(&balong_timer_device);
		return ret;
	}
	return ret;
}
arch_initcall(hi_timer_init);


void bsp_timer_show(void){
	u32 i = 0;
	hardtimer_print_error("idx periphid   freq   irq   srflag    name\n");
	for(i=0;i<TIMER_ID_MAX;i++){
		hardtimer_print_error("%d  0x%x    %d     %d      %d      %s\n",i,core_timer_control.timer[i].periphid,core_timer_control.timer[i].clk, \
									core_timer_control.timer[i].irq,core_timer_control.timer[i].sr_flag,core_timer_control.timer[i].name);
		}
}

/*lint -save -e19*/
EXPORT_SYMBOL(bsp_hardtimer_int_clear);
EXPORT_SYMBOL(bsp_hardtimer_int_mask);
EXPORT_SYMBOL(bsp_hardtimer_int_unmask);
EXPORT_SYMBOL(bsp_hardtimer_int_status);
EXPORT_SYMBOL(bsp_hardtimer_config_init);
EXPORT_SYMBOL(bsp_hardtimer_start);
EXPORT_SYMBOL(bsp_hardtimer_enable);
EXPORT_SYMBOL(bsp_hardtimer_disable);
EXPORT_SYMBOL(bsp_hardtimer_free);
EXPORT_SYMBOL(get_next_schedule_time);
/*lint -restore +e19*/



