/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_balong.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2013年1月2日  v1.00  y00221789  创建
*************************************************************************/
/*lint --e{525, 537, 539, , 737, 830 } */
#include <product_config.h>
#include <securec.h>

#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <of.h>
#include <bsp_hardtimer.h>
#include <bsp_icc.h>
#include <mdrv_udi_common.h>
#include <mdrv_pm.h>
#include <bsp_nvim.h>
#include <bsp_dpm.h>
#include <osl_thread.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>

#include "cpufreq_balong.h"

#ifdef __cplusplus
extern "C"
{
#endif

int cpufreq_driver_mbb_init(void)
{
	return OK;
}

int cpufreq_driver_mbb_release(void)
{
	return OK;	
}

int cpufreq_driver_mbb_get_profile(void)
{
	int cur_profile = 0;
	cur_profile = (s32)CPUFREQ_CUR_PROFILE;
	if ((cur_profile < BALONG_FREQ_MIN) || (cur_profile > BALONG_FREQ_MAX))
	{
		cur_profile = BALONG_FREQ_MAX;
		cpufreq_info("m3 cpufreq return right cur_profile value? %d\n", cur_profile);
	}
	return cur_profile;
}

int cpufreq_driver_mbb_target(struct cpufreq_msg *msg)
{
	if (NULL != msg)
		(void)cpufreq_icc_send(msg);
	return OK;
}

struct cpufreq_driver_s cpufreq_driver_mbb = {
	.drv_name = "drv_mbb",
	.drv_id = 1,
	.drv_ops = {
		.driver_init = cpufreq_driver_mbb_init,
		.driver_release = cpufreq_driver_mbb_release,
		.driver_target = cpufreq_driver_mbb_target,
		.get_current_profile = cpufreq_driver_mbb_get_profile,
	},
};
extern struct cpufreq_driver_s cpufreq_driver_phone;

void cpufreq_driver_init(void)
{
	cpufreq_driver_register(&cpufreq_driver_mbb);
	cpufreq_driver_register(&cpufreq_driver_phone);
}

#ifdef __cplusplus
}
#endif


