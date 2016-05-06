#include <bsp_memmap.h>
#include <osl_bio.h>
#include <bsp_wdt.h>
#include <hi_wdt.h>


#ifndef CONFIG_CCORE_WDT


wdt_timeout_cb g_wdt_rebootfunc = WDT_NULL;

s32 bsp_watchdog_init(void)
{
	wdt_pinfo("enter wdt init\n");
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

s32 bsp_wdt_keepalive(void)
{
    return WDT_OK;
}

void bsp_wdt_reboot_direct(void)
{
	//hi_syssc_wdt_reboot();
}
void bsp_wdt_reboot(void)
{
	if (g_wdt_rebootfunc)
	{
		g_wdt_rebootfunc(ACORE_WDT_TIMEOUT);
	}
	bsp_wdt_reboot_direct();
}
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
 
s32 bsp_wdt_reboot_register_hook(void *hook)
{
    /*参数判断，如果函数指针为空返回错误*/
    if(WDT_NULL == hook)
    {
		 wdt_err("hook is NULL\n");
        return WDT_ERROR;
    }

    /*通过全局变量注册上层MSP处理函数*/
	g_wdt_rebootfunc = hook;
	
	return WDT_OK;
}

s32  bsp_wdt_reboot_unregister_hook(void)
{
	/*卸载上层超时处理函数*/
	g_wdt_rebootfunc = WDT_NULL;
	wdt_pinfo("wdt unregister_hook\n");
	return WDT_OK;
}

#endif

BSP_S32 BSP_WDT_Enable(BSP_U8 wdtId)
{
	return bsp_wdt_start();
}

BSP_S32 BSP_WDT_Disable(BSP_U8 wdtId)
{
	return bsp_wdt_stop();
}

BSP_S32 BSP_WDT_HardwareFeed(BSP_U8 wdtId)
{
	return bsp_wdt_keepalive();
}
