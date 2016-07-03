
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

void pm_om_dbg_on(void)
{
	(void)bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_DEBUG);
}

void pm_om_dbg_off(void)
{
	(void)bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_ERROR);
}

void pm_om_dump_show(void)
{
	u32 i = 0;
	char *magic = NULL;
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	pmom_print("**********************************************\n");
	pmom_print("init_flag : 0x%x\n", ctrl->dump.init_flag);
	pmom_print("base_addr : 0x%x\n", ctrl->dump.base);
	pmom_print("length    : 0x%x\n", PM_OM_DUMP_SIZE);
	pmom_print("region_num: 0x%x\n", ctrl->dump.region_cnt);

	for (i = 0; i < ctrl->dump.region_cnt; i++)
	{
		magic = (char *)(&(ctrl->dump.cfg->entry_tbl[i].magic));
		pmom_print("[%c%c%c%c]    : 0x%x\n",magic[0], magic[1], magic[2], magic[3], ctrl->dump.cfg->entry_tbl[i].len);
	}
	pmom_print("**********************************************\n");
}

void pm_om_log_show(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	pmom_print("**********************************************\n");
	pmom_print("init_flag   : 0x%x\n", ctrl->log.init_flag);
	pmom_print("buf_is_full : 0x%x\n", ctrl->log.buf_is_full);
	pmom_print("threshold   : 0x%x\n", ctrl->log.threshold);
	pmom_print("debug       : 0x%p\n", ctrl->debug);
	pmom_print("platform    : 0x%p\n", ctrl->platform);
	pmom_print("**********************************************\n");
}

u32 pm_om_feature_on(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	struct pm_om_platform *linux_plat = NULL;

	if (NULL == ctrl || NULL == ctrl->platform)
	{
		return 1;
	}

	linux_plat = (struct pm_om_platform *)ctrl->platform;
	ctrl->log.init_flag = PM_OM_INIT_MAGIC;
	ctrl->log.smem->nv_cfg.mod_sw_bitmap = 0xFFFFFFFFFFFFFFFF;
	linux_plat->log_info.mem_is_ok = 1;

	return 0;
}

void pm_om_help(void)
{
	pmom_print("***********************\n");
	pmom_print("pm_om_dump_show\n");
	pmom_print("pm_om_log_show\n");
	pmom_print("pm_om_dbg_on\n");;
	pmom_print("pm_om_dbg_off\n");
	pmom_print("pm_om_feature_on\n");
	pmom_print("***********************\n");
}
 
