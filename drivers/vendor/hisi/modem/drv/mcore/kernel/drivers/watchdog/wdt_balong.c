/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  wdt_balong.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :
*
*************************************************************************/
#include <cmsis_os.h>
#include <product_config.h>
#include <osl_common.h>
#include <libfdt.h>

#ifdef CONFIG_CCORE_WDT
/*lint --e{537, 762 } */
#include <bsp_softtimer.h>
#include <bsp_hardtimer.h>
#include <osl_irq.h>
#include <irq.h>
#include <printk.h>
#include "m3_dump.h"
#include <bsp_wdt.h>
#include <hi_wdt.h>
#include "wdt_balong.h"

struct wdt_info g_wdt_ident;

unsigned long start_time = 0;

static struct wdt_control g_wdt_ctrl={
	.wdt_cb = WDT_NULL,
};
wdt_timeout_cb g_wdt_rebootfunc = WDT_NULL;

#define M3_WDT_DTS_NAME 		"hisilicon,watchdog_m3"
#define APP_WDT_DTS_NAME  		"hisilicon,ap_wdt_m3"
#define MDM_WDT_DTS_NAME  		"hisilicon,cp_wdt_m3"
#define MDM_A9_UNRESET_TIME 600
struct wdt_base
{
	u32 wdt_base_addr;
	u32 wdt_app_base_addr;
	u32 wdt_mdm_base_addr;
	u32 wdt_int_no;
	u32 wdt_app_int_no;
	u32 wdt_mdm_int_no;
	u32 wdt_sre_int_no;
};
struct wdt_base g_wdt_base_info = {0};

static irqreturn_t wdt_app_int(int irqno, void*param)
{
	/*clear timer3 interrupt*/
#ifdef TIMER_ARM_FEATURE
	writel(0,g_wdt_base_info.wdt_app_base_addr + ARM_ODD_INTCLR_OFFSET);
#else
	readl(g_wdt_base_info.wdt_app_base_addr + HI_TIMER_EOI_OFFSET);
#endif
	printk("awdt\n");

    dump_int_enter(g_wdt_base_info.wdt_app_int_no);

	if(g_wdt_ctrl.wdt_cb)
	{
		g_wdt_ctrl.wdt_cb(ACORE_WDT_TIMEOUT);
	}

    dump_int_exit(g_wdt_base_info.wdt_app_int_no);

	return IRQ_HANDLED;
}

static irqreturn_t wdt_sre_int(int irqno, void*param)
{
	(void)disable_irq(g_wdt_base_info.wdt_sre_int_no);
	printk("swdt\n");
	return IRQ_HANDLED;
}
static irqreturn_t wdt_mdm_int(int irqno, void* param)
{
	printk("cwdt\n");
	
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		(void)disable_irq(g_wdt_base_info.wdt_mdm_int_no);
	}

    dump_int_enter(g_wdt_base_info.wdt_mdm_int_no);

	if(g_wdt_ctrl.wdt_cb)
	{
		g_wdt_ctrl.wdt_cb(CCORE_WDT_TIMEOUT);
	}

    dump_int_exit(g_wdt_base_info.wdt_mdm_int_no);

	return IRQ_HANDLED;
}
s32 bsp_wdt_start(void)
{
	unsigned int retValue = 0;
	int irqlock = 0;

	start_time = bsp_get_slice_value();
	retValue = (s32)(WDT_DEF_CLK_FREQ * g_wdt_ident.wdt_timeout);/*lint !e713*/

	local_irq_save(irqlock);
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(retValue, g_wdt_base_info.wdt_base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_RST_INT_EN, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);

	return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
    int irqlock = 0;
	
    local_irq_save(irqlock);
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);

    return WDT_OK;
}

s32 bsp_wdt_keepalive(void)
{
	int irqlock = 0;
	
	local_irq_save(irqlock);
	writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_INTCLR_OFFSET);
	writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	local_irq_restore(irqlock);

	return WDT_OK;
}

void bsp_wdt_feed(void)
{
	u32 end_time = bsp_get_slice_value();
	if (get_timer_slice_delta(start_time, end_time) >= (WDT_KEEPALIVE_TIME * WDT_DEF_CLK_FREQ))
	{
		start_time = bsp_get_slice_value();
		(void)bsp_wdt_keepalive();
	}
}

void wdt_timer_event(u32 agrv)
{
	if (BSP_FALSE == g_wdt_ident.enable)
	{
		wdt_err("wdtnvdis\n");
		return;
	}
	bsp_softtimer_add(&g_wdt_ident.wdt_timer_list);
}

s32 bsp_wdt_get_timeleft(u32 *timeleft)
{
	
    int regval = 0;
	int irqlock = 0;
	
	if(WDT_NULL == timeleft)
	{
		printk("null\n");
		return WDT_ERROR;
	}
	
	local_irq_save(irqlock);
	
	writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	regval = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_VALUE_OFFSET);
	writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	
	local_irq_restore(irqlock);

	*timeleft  = regval/WDT_DEF_CLK_FREQ;
    return WDT_OK;
}


int bsp_wdt_set_timeout(u32 timeout)
{
 	int irqlock = 0;
	
    local_irq_save(irqlock);
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(timeout * WDT_DEF_CLK_FREQ, g_wdt_base_info.wdt_base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);
	
    g_wdt_ident.wdt_timeout = timeout;	

	return WDT_OK;
}

int bsp_wdt_register_hook(void *hook)
{
    if(NULL == hook)
    {
    	printk("hookNULL\n");
		return WDT_ERROR;
    }

	g_wdt_ctrl.wdt_cb = hook;
    return WDT_OK;
}

int bsp_wdt_unregister_hook()
{
	g_wdt_ctrl.wdt_cb = NULL;
	return WDT_OK;
}


void bsp_wdt_stop_awdt(void)
{
	u32 ret = 0;
	if (BSP_FALSE == g_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		ret = readl(g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
		writel(ret&(~0x80),g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
		ret &= ~HARD_TIMER_ENABLE;
		ret |= TIMER_INT_MASK;
		writel(ret, HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
	}
}
void bsp_wdt_restart_awdt(void)
{
	u32 ret = 0;
	if (BSP_FALSE == g_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		ret = readl(g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
		writel(ret|0x80,g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);		
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
		ret |= HARD_TIMER_ENABLE ;
		ret&=(~TIMER_INT_MASK);
		writel(ret,HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
	}
}
void bsp_wdt_stop_cwdt(void)
{
	u32 ret = 0;
	unsigned long irqlock;
	if (BSP_FALSE == g_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		local_irq_save(irqlock);
    	writel(WDT_UNLOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	writel(0x0, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_CONTROL_OFFSET);
    	writel(WDT_LOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	local_irq_restore(irqlock);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
		ret &= ~HARD_TIMER_ENABLE;
		ret |=TIMER_INT_MASK;
		writel(ret, HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
	}
}
void bsp_wdt_restart_cwdt(void)
{
	u32 ret = 0;
	unsigned long irqlock;

	if (BSP_FALSE == g_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		local_irq_save(irqlock);
    	writel(WDT_UNLOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	writel(0x01, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_CONTROL_OFFSET);
    	writel(WDT_LOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	local_irq_restore(irqlock);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
		ret |= HARD_TIMER_ENABLE ;
		ret&=(~TIMER_INT_MASK);
		writel(ret,HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
	}
}

s32 bsp_wdt_suspend(u32 timeout)
{
	u32 suspend_timeout = g_wdt_ident.wdt_suspend_timeout;
	
	if (BSP_FALSE == g_wdt_ident.enable)
	{
		return WDT_OK;
	}
	(void)bsp_softtimer_delete(&g_wdt_ident.wdt_timer_list);
	(void)bsp_softtimer_modify(&g_wdt_ident.wdt_timer_list, 
										(suspend_timeout - WDT_KEEPALIVE_TIME) * 1000);
	bsp_softtimer_add(&g_wdt_ident.wdt_timer_list);
	bsp_wdt_set_timeout(suspend_timeout);
	return WDT_OK;
}
void bsp_wdt_resume(void)
{
	if (BSP_FALSE == g_wdt_ident.enable)
	{
		return;
	}
	(void)bsp_softtimer_delete(&g_wdt_ident.wdt_timer_list);
	(void)bsp_softtimer_modify(&g_wdt_ident.wdt_timer_list, g_wdt_ident.wdt_timer_list.timeout);
	bsp_softtimer_add(&g_wdt_ident.wdt_timer_list);
    bsp_wdt_set_timeout(g_wdt_ident.wdt_timeout);
}

s32 get_base_info_from_dts(void)
{
	s32 ret = 0;
    struct device_node *np = NULL;

	/* wdt info from dts */
	np = of_find_compatible_node(NULL, NULL, M3_WDT_DTS_NAME);
	if (!np)
	{
		ret = -1;
		goto fail;
	}

	g_wdt_base_info.wdt_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_base_addr)
	{
		ret = -2;
		goto fail;
	}
	g_wdt_base_info.wdt_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_int_no)
	{
		ret = -3;
		goto fail;
	}

	/* a core watchdog info from dts */
	np = of_find_compatible_node(NULL, NULL, APP_WDT_DTS_NAME);
	if (!np)
	{
		ret = -4;
		goto fail;
	}

	g_wdt_base_info.wdt_app_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_app_base_addr)
	{
		ret = -5;
		goto fail;
	}
	g_wdt_base_info.wdt_app_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_app_int_no)
	{
		ret = -6;
		goto fail;
	}

	/* c core watchdog info from dts */
	np = of_find_compatible_node(NULL, NULL, MDM_WDT_DTS_NAME);
	if (!np)
	{
		ret = -7;
		goto fail;
	}

	g_wdt_base_info.wdt_mdm_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_mdm_base_addr)
	{
		ret = -8;
		goto fail;
	}
	g_wdt_base_info.wdt_mdm_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_mdm_int_no)
	{
		ret = -9;
		goto fail;
	}
	
	if(of_property_read_u32_array(np, "wdog_periphid", &g_wdt_ctrl.periphid ,1))
	{
		ret = -10;
		goto fail;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,watchdog_sre");
	if (np)
	{
		g_wdt_base_info.wdt_sre_int_no = (u32)irq_of_parse_and_map(np, 0);
	}


	return WDT_OK;
fail:
    printk("failret%d\n", ret);
    return WDT_ERROR;
}

s32 bsp_wdt_init(void)
{
    DRV_WDT_INIT_PARA_STRU wdt_nv_param = {0};
	s32 ret = -1;

	ret = (s32)bsp_nvm_read(NV_ID_DRV_WDT_INIT_PARAM, (u8*)&wdt_nv_param, sizeof(DRV_WDT_INIT_PARA_STRU));
    if (NV_OK != ret)
    {
        wdt_err("WdtNvERR\n");
		return WDT_ERROR;
    }
	g_wdt_ident.enable = (s32)wdt_nv_param.wdt_enable;
	g_wdt_ident.wdt_timeout = wdt_nv_param.wdt_timeout;
	g_wdt_ident.wdt_suspend_timeout = wdt_nv_param.wdt_suspend_timerout;
	g_wdt_ident.wdt_timer_list.func = ( softtimer_func )wdt_timer_event;
	g_wdt_ident.wdt_timer_list.para = 0;
	g_wdt_ident.wdt_timer_list.timeout = WDT_KEEPALIVE_TIME * 1000;
	g_wdt_ident.wdt_timer_list.wake_type = SOFTTIMER_WAKE;

	if (BSP_FALSE == g_wdt_ident.enable)
    {
		printk("wdtdis\n");
		return WDT_OK;
    }
	
	if(0 != get_base_info_from_dts())
	{
        return WDT_ERROR;
    }
    if(0 != request_irq(g_wdt_base_info.wdt_app_int_no, wdt_app_int, 0, "wdt acore irq", NULL)) 
	{
        printk("airqerr\n");
    }
    if(0 != request_irq(g_wdt_base_info.wdt_mdm_int_no, wdt_mdm_int, 0, "wdt ccore irq", NULL)) 
	{
        printk("cirqerr\n");
    }
	if(0 != g_wdt_base_info.wdt_sre_int_no)
	{
		if(0 != request_irq(g_wdt_base_info.wdt_sre_int_no, wdt_sre_int, 0, "wdt sre irq", NULL)) 
		{
        	printk("sreerr\n");
    	}
	}
	
	ret= bsp_softtimer_create(&g_wdt_ident.wdt_timer_list);
	if (ret)
    {
		printk("wdttimererr\n");
		return WDT_ERROR;
    }
    bsp_softtimer_add(&g_wdt_ident.wdt_timer_list);

	bsp_wdt_start();

    printk("wdtok\n");
    return WDT_OK;	
}

void bsp_wdt_enable(void)
{	
 	int irqlock = 0;
	
	if (BSP_FALSE == g_wdt_ident.enable)
    {
		return;
    }

    local_irq_save(irqlock);
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    writel(MDM_A9_UNRESET_TIME * WDT_DEF_CLK_FREQ, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOAD_OFFSET);
	writel(0x1, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);
}

void bsp_wdt_print_debug(void)
{
    unsigned int timeleft = 0;
    bsp_wdt_get_timeleft(&timeleft);
    printk("\r\ntimeleft:%d\n", timeleft);
    printk("set time:%d\n", g_wdt_ident.wdt_timeout);
    timeleft = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    printk("ctr reg:0x%x\n", timeleft);
    timeleft = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_VALUE_OFFSET);
    printk("wdt val:0x%x\n", timeleft);
}


#else       /* !CONFIG_CCORE_WDT   此分支为打桩*/

#ifndef WDT_OK
#define WDT_OK                   			(0)
#endif
#ifndef WDT_ERROR
#define WDT_ERROR                			(-1)
#endif

s32 hi6930_wdt_init(void)
{
	return WDT_OK;
}
s32 bsp_wdt_start(void)
{
    return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
	return WDT_OK;
}
void bsp_wdt_enable(void)
{

}
/*****************************************************************************
* 函 数 名  : BSP_WDT_HardwareFeed
*
* 功能描述  : 重置看门狗计数寄存器（喂狗）
*
* 输入参数  : BSP_U8 u8WdtId :看门狗ID
* 输出参数  : 无
*
* 返 回 值  : WDT_OK:    操作成功
*             WDT_ERROR: 操作失败
* 其它说明  :
*
*****************************************************************************/
s32 bsp_wdt_keepalive(void)
{
    return WDT_OK;
}


/*****************************************************************************
* 函 数 名  : BSP_WDT_TimerReboot
*
* 功能描述  : 通过设置timer中断，通知mcore重启。
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : WDT_OK:    操作成功
*             WDT_ERROR: 操作失败
* 其它说明  :
*
*****************************************************************************/

s32 bsp_wdt_set_timeout(u32 timeout)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_get_timeleft(u32 *timeleft)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_register_hook(void *hook)
{
	return WDT_OK;
}

s32  bsp_wdt_unregister_hook(void)
{
	return WDT_OK;
}

 s32 bsp_wdt_suspend(u32 timeout)
 {
	return WDT_OK;
 }
 void bsp_wdt_resume(void)
 {
 }
 
void bsp_wdt_stop_awdt(void)
{
	
}
void bsp_wdt_restart_awdt(void)
{
	
}
void bsp_wdt_stop_cwdt(void)
{
	
}
void bsp_wdt_restart_cwdt(void)
{
	
}
void bsp_wdt_feed(void)
{

}
void bsp_wdt_print_debug(void)
{

}
#endif   /* end of CONFIG_CCORE_WDT */

