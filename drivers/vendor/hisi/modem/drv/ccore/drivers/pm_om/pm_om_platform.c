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
#include <securec.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"

struct pm_om_platform g_pmom_platform;

/*
 * pm_om_fwrite_trigger - trigger file write from log buffer to log file
 */
int pm_om_fwrite_trigger(void)
{
	if (!g_pmom_platform.ctrl || !g_pmom_platform.ctrl->log.init_flag)
	{
		return PM_OM_ERR;
	}

	bsp_modem_log_fwrite_trigger(&(g_pmom_platform.log_info));
	return PM_OM_OK;
}

s32 pm_om_icc_handler(u32 channel_id , u32 len, void *context)
{
	pm_om_icc_data_type data = 0;
	s32 ret = PM_OM_OK;

	ret = bsp_icc_read(channel_id, (u8 *)&data, sizeof(data));
	if(sizeof(data) != (u32)ret)
	{
		pmom_pr_err("icc read fail: 0x%x\n", ret);
		return ret;
	}

	if (data)
	{
		g_pmom_platform.ctrl->log.init_flag = PM_OM_INIT_MAGIC;
	}
	else
	{
		g_pmom_platform.ctrl->log.init_flag = 0;
	}

	return PM_OM_OK;
}

int pm_om_platform_init(void)
{
	struct pm_om_ctrl *ctrl  = pm_om_ctrl_get();

	(void)memset_s((void *)&g_pmom_platform, sizeof(g_pmom_platform), 0, sizeof(g_pmom_platform));

	g_pmom_platform.log_info.mem      = &(ctrl->log.smem->mem_info);
	g_pmom_platform.log_info.ring_buf = ctrl->log.rb.buf;

	g_pmom_platform.icc_chn_id = PM_OM_ICC_CHN_ID;
	if (ICC_OK != bsp_icc_event_register(g_pmom_platform.icc_chn_id, pm_om_icc_handler, NULL, NULL, NULL))
	{
		return PM_OM_ERR;
	}

	g_pmom_platform.ctrl = ctrl;
	ctrl->platform = (void *)&g_pmom_platform;
	return PM_OM_OK;
}