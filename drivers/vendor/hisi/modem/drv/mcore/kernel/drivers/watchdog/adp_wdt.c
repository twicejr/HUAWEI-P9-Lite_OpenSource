#include <bsp_memmap.h>
#include <osl_bio.h>
#include <osl_types.h>
#include <hi_wdt.h>

extern s32 bsp_wdt_start(void);
extern s32 bsp_wdt_keepalive(void);
extern s32 bsp_wdt_stop(void);
s32 BSP_WDT_Enable(u8 wdtId)
{
	return bsp_wdt_start();
}

s32 BSP_WDT_Disable(u8 wdtId)
{
	return bsp_wdt_stop();
}

s32 BSP_WDT_HardwareFeed(u8 wdtId)
{
	return bsp_wdt_keepalive();
}
