
#include <product_config.h>
#include <bsp_om.h>
#include <mdrv_sysboot.h>
#include <bsp_reset.h>

#ifndef CONFIG_BALONG_MODEM_RESET

int mdrv_sysboot_ok(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
    return 0;
}

s32 bsp_reset_init(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return 0;
}


#endif /* end of CONFIG_BALONG_MODEM_RESET */
