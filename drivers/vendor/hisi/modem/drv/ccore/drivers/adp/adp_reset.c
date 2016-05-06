/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_reset.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成单独复位相关接口的打桩
*
*   修改记录 :  2014年02月15日  v1.00  y00184236  创建
*************************************************************************/
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
