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
#include <bsp_ipc.h>
#include <sysTimer.h>
#include <bsp_wdt.h>
#include "watchdog_inter.h"

struct wdt_info wdg_timer_ident;

static int watchdog_start(struct wdg_nv_param nv_param)
{
	wdg_timer_ident.my_timer.func = NULL;
	wdg_timer_ident.my_timer.mode = TIMER_PERIOD_COUNT;
	wdg_timer_ident.my_timer.timeout = WDT_HI_TIMER_CLK * nv_param.wdt_timeout;
	wdg_timer_ident.my_timer.timerId = CCORE_WDT_TIMER_ID;
	wdg_timer_ident.my_timer.unit = TIMER_UNIT_NONE;

    if (WDT_OK != bsp_hardtimer_start(&wdg_timer_ident.my_timer))
    {
		wdt_err("wdt start hardtimer err\n");
		return WDT_ERROR;
    }

    return WDT_OK;
}

static int watchdog_stop(void)
{
	(void)bsp_hardtimer_disable(CCORE_WDT_TIMER_ID);
	return WDT_OK;
}
static int watchdog_keepalive(void)
{
	(void)bsp_hardtimer_disable(CCORE_WDT_TIMER_ID);
	(void)bsp_hardtimer_load_value(CCORE_WDT_TIMER_ID, wdg_timer_ident.my_timer.timeout);
	(void)bsp_hardtimer_enable(CCORE_WDT_TIMER_ID);

    wdt_debug("exit wdt keepalive\n");
    return WDT_OK;
}

static int watchdog_set_timeout(u32 timeout_s)
{
	u32 value = 0;
	value = timeout_s * WDT_HI_TIMER_CLK;
	wdg_timer_ident.my_timer.timeout = value;

	if (WDT_OK != bsp_hardtimer_start(&wdg_timer_ident.my_timer))
	{
		wdt_err("wdt start hardtimer failed\n");
		return WDT_ERROR;
	}
	return WDT_OK;
}

static int watchdog_get_timeleft(u32 *timeleft_s)
{
	u32 reg;
	if(WDT_NULL == timeleft_s)
	{
		return WDT_ERROR;
	}
	reg = bsp_get_timer_current_value(CCORE_WDT_TIMER_ID);

	*timeleft_s = reg/WDT_HI_TIMER_CLK;

	return WDT_OK;
}

static struct watchdog_ops timer_wdog_ops={
	.start = watchdog_start,
	.stop = watchdog_stop,
	.feed = watchdog_keepalive,
	.set_timeout = watchdog_set_timeout,
	.get_timeleft = watchdog_get_timeleft,
	.suspend = NULL,
	.resume = NULL,
};

static struct watchdog_driver timer_watchdog={
	.ops = &timer_wdog_ops,
	.periphid = 0x11111111,
	.driver_name = "timer_watchdog",
};
int timer_watchdog_init(void)
{
	(void)watchdog_device_register(&timer_watchdog);
	return OK;
}

