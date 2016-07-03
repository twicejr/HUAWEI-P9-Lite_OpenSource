
#include <bsp_pm_om.h>
#include "pm_om_platform.h"

/*
 * pm_om_fwrite_trigger - trigger file write from log buffer
 */
int pm_om_fwrite_trigger(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	u32 data = 0;

	/* ÊÇ·ñÐèÒª»½ÐÑacore */
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
