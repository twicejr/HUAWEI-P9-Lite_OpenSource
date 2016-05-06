/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  timer_balong.c.c
*
*   作    者 :  lixiaojie l00227190
*
*   描    述 :  本文件主要完成timer驱动编写
*
*   修改记录 :  2013年2月20日  v1.00  l00227190  创建
*************************************************************************/
/*lint --e{413,438,485,537,539,713,830}*/
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <osl_module.h>
#include <osl_irq.h>
#include <securec.h>
#include <soc_timer.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_sysctrl.h>
#include <bsp_dpm.h>
#include <of.h>
#include "hardtimer_core.h"

static LIST_HEAD(timer_drivers_head);	

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
	(void)memcpy_s((void*)&core_timer_control.timer[timer_ctrl->timerId].timer_ctrl,(size_t)sizeof(struct bsp_hardtimer_control),(const void*)timer_ctrl,(size_t)sizeof(struct bsp_hardtimer_control));
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
	osl_free_irq(core_timer_control.timer[timer_id].irq,core_timer_control.timer[timer_id].timer_ctrl.func,(int)core_timer_control.timer[timer_id].timer_ctrl.para);
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
			if(of_property_read_u32(child_node, "reg", &core_timer_control.timer[index].base_addr)){
				hardtimer_print_error("timer request_id %d reg failed.\n",index);
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
			/*modem reset, need disable ap ao timer used in modem*/
			if(!of_property_read_u32(child_node, "need_dis_in_reset_init", (u32 *)&ret_value)&&ret_value)
			{
				(void)bsp_hardtimer_disable(index);
				hardtimer_print_error("disable timer %d \n",index);
			}
		}
		return BSP_OK;
	}
	else
		return BSP_ERROR;
}
static s32 timer_suspend_late(struct dpm_device *dev)
{
	int i=0;
	u32 stamp = 0;
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
	return BSP_OK;
}
static s32 timer_resume_early(struct dpm_device *dev)
{
	u32 i=0;
	set_timer_clk();
	for(i=0;i<TIMER_ID_MAX;i++){
		if(core_timer_control.timer[i].sr_flag && core_timer_control.timer[i].driver->ops->resume ){
			core_timer_control.timer[i].driver->ops->resume(&core_timer_control.timer[i]);
		}
		else
			continue;
	}
	return BSP_OK;
}
struct dpm_device timer_dpm =
{
	.device_name = "timer_dpm",
	.suspend_late = timer_suspend_late,
	.resume_early = timer_resume_early,
};

void bsp_timer_init(void){
	s32 ret = 0;
	(void)memset_s((void*)&core_timer_control,sizeof(struct timercore_ctrl_s),0x0,sizeof(struct timercore_ctrl_s));
	spin_lock_init(&core_timer_control.list_lock);
	arm_timer_drviver_init();
	synopsis_timer_drviver_init();
	ret = timer_device_init();
	ret |= set_adp_timer_isr_and_pm();
	ret |= bsp_device_pm_add(&timer_dpm);
	if(ret)
		hardtimer_print_error("err\n");
	else
		hardtimer_print_error("ok\n");
	return ;
}

void bsp_timer_show(void){
	hardtimer_print_error("core timer info,func: timer_show\n");
	hardtimer_print_error(" timer clk cfg info,func: timer_clk_cfg_show\n");
}
void timer_show(void){
	u32 i = 0;
	hardtimer_print_error("idx freq irq  srflag  name\n");
	for(i=0;i<TIMER_ID_MAX;i++)
		hardtimer_print_error("%d   %d    %d      %d     %s\n",i,core_timer_control.timer[i].clk, \
									core_timer_control.timer[i].irq,core_timer_control.timer[i].sr_flag,core_timer_control.timer[i].name);
}


