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
/*lint --e{525,537, 713, 732 } */
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_thread.h>
#include <of.h>
#include <bsp_wdt.h>
#include <hi_wdt.h>
#include "watchdog_inter.h"

struct wdt_mdm_dev_info wdt_mdm_dev ={0};	
struct wdt_mdm_ctrl g_wdt_mdm_ctrl = {0,{0},0};

int get_wdt_mdm_dtsi(void)
{
    struct device_node *node = NULL;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,cp_wdt_m3");
	if (!node)
	{
		wdt_err("get mdm wdt node fail\n");
		return WDT_ERROR;
	}
	wdt_mdm_dev.base_addr= (u32)of_iomap(node, 0);
	if(0 == wdt_mdm_dev.base_addr)
	{
		wdt_err("wdt base addr err\n");
		return WDT_ERROR;
	}
	return WDT_OK;
}

static int watchdog_keepalive(void)
{
	unsigned long irqlock = 0;
	local_irq_save(irqlock);
	
	/* 寄存器解锁、中断清除、给Watchdog上锁*/
	writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	writel(0x0, wdt_mdm_dev.base_addr + HI_WDG_INTCLR_OFFSET);
	writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	
	local_irq_restore(irqlock);
	return WDT_OK;
}

static int watchdog_stop(void)
{
    unsigned long irqlock = 0;
    local_irq_save(irqlock);
	
    /* 寄存器解锁、 关闭看门狗、给Watchdog上锁*/
    writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
    writel(0x0, wdt_mdm_dev.base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	
    local_irq_restore(irqlock);
    return WDT_OK;
}

static unsigned int watchdog_init = BSP_FALSE;

static int watchdog_start(struct wdg_nv_param nv_param)
{
    unsigned long irqlock = 0;
	
	if(BSP_FALSE == watchdog_init)
	{
		(void)get_wdt_mdm_dtsi();
		watchdog_init = BSP_TRUE; 
	}
    local_irq_save(irqlock);

    g_wdt_mdm_ctrl.cur_timeout = nv_param.wdt_timeout ;
    writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
    writel(nv_param.wdt_timeout * WDT_DEF_CLK_FREQ, wdt_mdm_dev.base_addr + HI_WDG_LOAD_OFFSET);
    writel(0x01, wdt_mdm_dev.base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	
    local_irq_restore(irqlock);

    return WDT_OK;
}

static int watchdog_set_timeout(u32 timeout_s)
{
    unsigned long irqlock = 0;
    local_irq_save(irqlock);

	writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
    writel(timeout_s * WDT_DEF_CLK_FREQ, wdt_mdm_dev.base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	
    local_irq_restore(irqlock);
    g_wdt_mdm_ctrl.cur_timeout = timeout_s;
    return WDT_OK;
}
static int watchdog_get_timeleft(u32 *timeleft)
{
	u32 reg = 0;
	unsigned long irqlock = 0;
	
	if(WDT_NULL == timeleft)
	{
		wdt_err("timeleft is NULL\n");
		return WDT_ERROR;
	}
	
	local_irq_save(irqlock);
	writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	reg = readl(wdt_mdm_dev.base_addr+ HI_WDG_VALUE_OFFSET);
	writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	local_irq_restore(irqlock);
	
    *timeleft = reg/WDT_DEF_CLK_FREQ;
    return WDT_OK;
}

static int watchdog_resume(void)
{
    unsigned long irqlock = 0;

	local_irq_save(irqlock);
    writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
    writel(g_wdt_mdm_ctrl.cur_timeout * WDT_DEF_CLK_FREQ, wdt_mdm_dev.base_addr + HI_WDG_LOAD_OFFSET);
    writel(0x01, wdt_mdm_dev.base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);

	return OK;
}

static struct watchdog_ops hard_wdg_ops={
	.start = watchdog_start,
	.stop = watchdog_stop,
	.feed = watchdog_keepalive,
	.set_timeout = watchdog_set_timeout,
	.get_timeleft = watchdog_get_timeleft,
	.suspend = NULL,
	.resume = watchdog_resume,
};

static struct watchdog_driver hard_watchdog={
	.ops = &hard_wdg_ops,
	.periphid = 0xaaaaaaaa,
	.driver_name = "modem_watchdog",
};
int hard_watchdog_init(void)
{
	(void)watchdog_device_register(&hard_watchdog);
	return OK;
}

void wdt_mdm_read_reg(u32 offset)
{	
	u32 regval = 0;
	regval = readl(wdt_mdm_dev.base_addr + offset);
	wdt_err("offset :0x%x, value :0x%x\n",offset,regval);
}
void wdt_mdm_write_reg(u32 offset,u32 regval)
{
	writel(WDT_UNLOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
	writel(regval,wdt_mdm_dev.base_addr + offset);
	writel(WDT_LOCK, wdt_mdm_dev.base_addr + HI_WDG_LOCK_OFFSET);
}

