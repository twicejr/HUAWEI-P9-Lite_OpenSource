#include <product_config.h>
#include <bsp_vic.h>

#ifndef CONFIG_MODULE_VIC
s32 bsp_vic_init(void)
{
	return 0;
}
s32 bsp_vic_enable(int level) {return 0;}
s32 bsp_vic_disable (int level) {return 0;}
s32 bsp_vic_connect(int level, vicfuncptr routine, s32 parameter) {return 0;}
s32 bsp_vic_disconnect(int level) {return 0;}
#endif