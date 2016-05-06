/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  Hi6930_wdt.c
*
*   作    者 :  y00221789
*
*   描    述 :  wdt模块
*
*   修改记录 :
*
*************************************************************************/
/*lint --e{525,537,539,586, 713, 732 } */
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <osl_thread.h>
#include <of.h>
#include "securec.h"
#include <bsp_sram.h>
#include <bsp_ipc.h>
#include <bsp_dpm.h>
#include <bsp_sysctrl.h>
#include <sysTimer.h>
#include <bsp_wdt.h>
#include "watchdog_inter.h"

wdt_timeout_cb g_pSoftFeedFunc = WDT_NULL;
wdt_timeout_cb g_wdt_rebootfunc = WDT_NULL;

struct wdt_mdm_ctrl g_wdog_ctrl = {0,{0},0};

static LIST_HEAD(wdog_drivers);	

int watchdog_device_register(struct watchdog_driver *drv)
{
	unsigned long flags;

    spin_lock_irqsave(&g_wdog_ctrl.lock, flags);
    list_add_tail(&drv->wdog_lists, &wdog_drivers);
    spin_unlock_irqrestore(&g_wdog_ctrl.lock, flags);

	return OK;
}
/*lint --e{530}*/
void get_watchdog_driver(void)
{
	struct watchdog_driver *drv;
    unsigned long flags = 0;
    spin_lock_irqsave(&g_wdog_ctrl.lock, flags);
    if(!list_empty(&wdog_drivers))
	{
        list_for_each_entry(drv, &wdog_drivers, wdog_lists) 
		{
            if(drv->periphid == g_wdog_ctrl.drv_id)
			{
    			spin_unlock_irqrestore(&g_wdog_ctrl.lock, flags);
                g_wdog_ctrl.ops = drv->ops;
			    wdt_err("%s\n",drv->driver_name);
            }
        }
    }
    spin_unlock_irqrestore(&g_wdog_ctrl.lock, flags);
}

void wdt_feed_lowtask(void)
{ /*lint !e527 */
	/* coverity[INFINITE_LOOP] */
	/* coverity[no_escape] */
	for(;;)
    {
        (void)osl_task_delay((s32)g_wdog_ctrl.task_delay_value);
        (void)bsp_wdt_keepalive();
		wdt_debug("enter wdog lowtask\n");
    }
}
s32 bsp_wdt_start(void)
{
    if(NULL != g_wdog_ctrl.ops)
    {
		(void)g_wdog_ctrl.ops->start(g_wdog_ctrl.nv_param);
		g_wdog_ctrl.stop_flag = BSP_FALSE;

	    /*A-M 核标志for 仿真器停狗*/
	    STOP_WDT_TRACR_RUN_FLAG = 0;
	}
    return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
	if(NULL != g_wdog_ctrl.ops)
    {
		(void)g_wdog_ctrl.ops->stop();
		g_wdog_ctrl.stop_flag = BSP_TRUE;

		STOP_WDT_TRACR_RUN_FLAG = 1;
	}
	return WDT_OK;
}
s32 bsp_wdt_keepalive(void)
{
	if(BSP_FALSE == g_wdog_ctrl.stop_flag)
	{
		if(g_wdog_ctrl.ops->feed)
	    {
			(void)g_wdog_ctrl.ops->feed();
		}
	    wdt_debug("exit wdt keepalive\n");
	}
	return WDT_OK;
}

s32 bsp_wdt_set_timeout(u32 timeout_s)/*s*/
{
	if(NULL != g_wdog_ctrl.ops)
    {
		(void)g_wdog_ctrl.ops->set_timeout(timeout_s);
		g_wdog_ctrl.cur_timeout = timeout_s;
	}
	return WDT_OK;
}

 s32 bsp_wdt_get_timeleft(u32 *timeleft_s)
{
	if(NULL != g_wdog_ctrl.ops)
    {
		(void)g_wdog_ctrl.ops->get_timeleft(timeleft_s);
	}
	return WDT_OK;
}

s32 bsp_wdt_register_hook(void *hook)
{
    if(NULL == hook)
    {
		 wdt_err("hook is null\n");
        return WDT_ERROR;
    }
	g_pSoftFeedFunc = hook;
	return WDT_OK;
}

s32  bsp_wdt_unregister_hook(void)
{
	g_pSoftFeedFunc = WDT_NULL;
	return WDT_OK;
}

s32 bsp_wdt_reboot_register_hook(void *hook)
{
    if(NULL == hook)
    {
		 wdt_err("hook is null\n");
        return WDT_ERROR;
    }

	g_wdt_rebootfunc = hook;

	return WDT_OK;
}

s32  bsp_wdt_reboot_unregister_hook(void)
{
	g_wdt_rebootfunc = WDT_NULL;
	wdt_pinfo("wdt unregister hook\n");
	return WDT_OK;
}

static int watchdog_suspend(struct dpm_device *dev)
{
	if(NULL != g_wdog_ctrl.ops->suspend)
	{
		(void)g_wdog_ctrl.ops->suspend();
	}
	return OK;
}

static int watchdog_resume(struct dpm_device *dev)
{
	if(NULL != g_wdog_ctrl.ops->resume)
	{
		(void)g_wdog_ctrl.ops->resume();
	}	
	return OK;
}

struct dpm_device watchdog_device =
{
	.device_name = "watchdog device",
	.suspend = watchdog_suspend,
	.resume = watchdog_resume,
};
s32 bsp_watchdog_init(void)
{
    OSL_TASK_ID uwTaskUsrInitId;
	s32 retValue = -1;
	DRV_WDT_INIT_PARA_STRU wdt_nv_param = {0};
	unsigned int regval = 2;
	unsigned int flag = 0;
	unsigned int wdog_offset = 0;   //watchdog enable offset in sctrl reg 
	struct device_node *node = NULL;

	retValue = bsp_nvm_read(NV_ID_DRV_WDT_INIT_PARAM, (u8*)&wdt_nv_param, sizeof(DRV_WDT_INIT_PARA_STRU));
    if (WDT_OK != retValue)
    {
    	wdt_err("read nv failed use default value\n");
		wdt_nv_param.wdt_enable = BSP_FALSE;
    }

	node = of_find_compatible_node(NULL, NULL, "hisilicon,cp_wdt_m3");
	if(!node)
	{
		wdt_err("get mdm wdog node fail\n");
		return WDT_ERROR;
	}
	if(of_property_read_u32(node, "wdog_periphid", &g_wdog_ctrl.drv_id))
	{
		wdt_err("read mdm wdog periphid err\n");
		return WDT_ERROR;
	}
	(void)of_property_read_u32(node, "flag", &flag);
	if(flag)
	{
		if(!of_property_read_u32(node, "offset", &wdog_offset))
		{
			regval = readl((u32)bsp_sysctrl_addr_byindex(sysctrl_ao) + wdog_offset);
		}
	}
		
	if(BSP_TRUE == wdt_nv_param.wdt_enable && (regval & 0x02) != 0)
	{
		(void)memcpy_s((void *)&g_wdog_ctrl.nv_param, sizeof(struct wdg_nv_param),(void *)&wdt_nv_param, sizeof(struct wdg_nv_param));
		g_wdog_ctrl.task_delay_value = wdt_nv_param.wdt_keepalive_ctime * 100;
		g_wdog_ctrl.cur_timeout = wdt_nv_param.wdt_timeout;

		(void)timer_watchdog_init();
		(void)hard_watchdog_init();

		get_watchdog_driver();
		
	   if(bsp_device_pm_add(&watchdog_device))
	   {
			wdt_err("device add err\n");
			return WDT_ERROR;
	   }
	    if(WDT_ERROR == bsp_wdt_start())
	    {
			wdt_err("wdog start error\n");
	        return WDT_ERROR;
	    }
	    if(WDT_ERROR == osl_task_init("cwdogfeedtask", WDT_MDM_TASK_PRO, WDT_MDM_TASK_SIZE, 
			            (OSL_TASK_FUNC)wdt_feed_lowtask, 0, &uwTaskUsrInitId))
		{
	    	wdt_err("task create err\n");
	        return WDT_ERROR;
		}
		wdt_err("wdog init end\n");
	}
	else
	{
		wdt_err("wdog nv disable\n");
	}
    return WDT_OK;
}

void bsp_wdt_print_debug(void)
{
    unsigned int timeleft = 0;
    (void)bsp_wdt_get_timeleft(&timeleft);
    wdt_err("time left:   %d\n", timeleft);
    wdt_err("set  time:   %d\n", g_wdog_ctrl.cur_timeout);
}


void wdt_set_loglevel(u32 value)
{
	(void)bsp_mod_level_set(BSP_MUDU_WDT , value);
}

