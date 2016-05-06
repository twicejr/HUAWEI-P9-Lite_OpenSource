/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  pm_om_platform.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成低功耗可维可测平台相关处理
*
*   修改记录 :  2014年11月17日  v1.00  y00184236  创建
*************************************************************************/
#include <bsp_pm_om.h>
#include "pm_om_platform.h"

/*
 * pm_om_fwrite_trigger - trigger file write from log buffer
 */
int pm_om_fwrite_trigger(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	u32 data = 0;

	/* 是否需要唤醒acore */
	if (ctrl->log.smem->mem_info.app_is_active)
	{
		if (bsp_icc_send(ICC_CPU_APP, PM_OM_ICC_CHN_ID, (u8 *)&data, sizeof(data)) != sizeof(data))
		{
			return PM_OM_ERR;
		}

		pmom_pr_debug("icc[0x%x] send ok\n", PM_OM_ICC_CHN_ID);
	}
	return PM_OM_OK;
}
