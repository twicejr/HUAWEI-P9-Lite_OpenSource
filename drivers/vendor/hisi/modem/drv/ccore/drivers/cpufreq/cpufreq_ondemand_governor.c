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
extern unsigned int g_in_interr_times;
extern osl_sem_id g_sem_calccpu_flag;
extern unsigned int g_flowctrl_in_interr_times;

/*cpufreq task 是否执行结果*/
unsigned int g_cpufreq_task_result_flag = 1;

OSL_TASK_ID 	  cpufreq_ondemand_task_id;
DFS_CONTROL_STRU g_stDfsCpuControl = {0,1,1,0,0};
ST_PWC_DFS_STRU gov_ctrl_info = {0};

/*
	调频判决
*/
int  cpufreq_governor_ond_decision(unsigned int cpuload)
{
    if ((cpuload > gov_ctrl_info.CcpuUpLimit) || (cpuload >= gov_ctrl_info.DFSDdrUpLimit))
    {
        g_stDfsCpuControl.ulCurSysDownTime = 0;
		g_stDfsCpuControl.ulCurSysUpTime++;
	}
    else if ((cpuload < gov_ctrl_info.CcpuDownLimit) || (cpuload <= gov_ctrl_info.DFSDdrDownLimit))
    {
		g_stDfsCpuControl.ulCurSysUpTime = 0;
		g_stDfsCpuControl.ulCurSysDownTime++;
    }
    else /*The System Load is Normal Value*/
    {
		g_stDfsCpuControl.ulCurSysDownTime = 0;
        g_stDfsCpuControl.ulCurSysUpTime = 0;

        return DFS_PROFILE_NOCHANGE;
    }
    
    if (g_stDfsCpuControl.ulCurSysDownTime >= gov_ctrl_info.CcpuDownNum)
    {
		g_stDfsCpuControl.ulCurSysDownTime = 0;
        g_stDfsCpuControl.ulCurSysUpTime = 0;

        return DFS_PROFILE_DOWN;
    }

    if (g_stDfsCpuControl.ulCurSysUpTime >= gov_ctrl_info.CcpuUpNum)
    {
		g_stDfsCpuControl.ulCurSysDownTime = 0;
        g_stDfsCpuControl.ulCurSysUpTime = 0;
        return DFS_PROFILE_UP_TARGET;
    }

	return DFS_PROFILE_NOCHANGE;
}
int cpufreq_gov_ddr_decision(int cur_profile)
{
	int ddr_value_id = 0;
	int ddr_profile = 0xff;
	ddr_value_id = g_cpufreq_core_ctrl.g_last_ddr_value_id;
	if (!g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
	{
		if ((ddr_value_id > BALONG_DDRFREQUENCY_MAX) || (ddr_value_id < BALONG_DDRFREQUENCY_MIN))
		{
			ddr_value_id = (int)gov_ctrl_info.DFSDdrprofile;
		}
		/*bit2表示是否打开ddr辅助调频*/
		if (((gov_ctrl_info.Strategy) & (0x1<<1)))
		{
			/*直接将DDR调制最高或降一档*/
			if ((cur_profile == BALONG_FREQ_MAX)
			&& (g_ulCCpuload >= gov_ctrl_info.DFSDdrUpLimit)
			&& (ddr_value_id < (int)gov_ctrl_info.DFSDdrprofile))
			{
			    ddr_profile = (int)gov_ctrl_info.DFSDdrprofile;
			}
			else if ((g_ulCCpuload <= gov_ctrl_info.DFSDdrDownLimit) && (ddr_value_id > BALONG_DDRFREQUENCY_MIN))
			{
				ddr_profile = ((ddr_value_id -1) > BALONG_DDRFREQUENCY_MIN) ? (ddr_value_id -1) : BALONG_DDRFREQUENCY_MIN;
			}
		}
	}

	return ddr_profile;
}

int cpufreq_gov_ddr_target(int ddr_profile, unsigned int result)
{
    unsigned long irqlock = 0;
    unsigned int ddr_value = 0;
    int ddr_result = (int)result;
    struct cpufreq_query freq_table = {0};
    
    if ((ddr_profile > BALONG_DDRFREQUENCY_MAX) || (ddr_profile < BALONG_DDRFREQUENCY_MIN))
    {
        return ddr_result;
    }
    cpufreq_find_frequence(ddr_profile, &freq_table);
	ddr_value = freq_table.ddr_frequency;
	(void)cpufreq_qos_update(DFS_QOS_ID_DDR_MINFREQ, g_cpufreq_core_ctrl.g_ddr_request_id, ddr_value * 1000);
	local_irq_save(irqlock);
	g_cpufreq_core_ctrl.g_last_ddr_value_id = ddr_profile;
	ddr_result = DFS_PROFILE_NOCHANGE;
	local_irq_restore(irqlock);

	return ddr_result;
}
static void  cpufreq_dfs_ondemand_task(void)
{
    int cur_profile = 0;
    int ddr_profile = 0;
    unsigned int result = 0;
    struct cpufreq_msg task_msg = {0,0,0,0};
	/* coverity[INFINITE_LOOP] */
	/* coverity[no_escape] */
    for (;;)
    {
		if (0 != g_sem_calccpu_flag)
		{	
			osl_sem_down(&g_sem_calccpu_flag);/* [false alarm]:fake warning*/
			 /*调用ttf回调函数*/
		    if (g_flowctrl_in_interr_times >= 200)
		    {
		    	cpufreq_balong_flow_callback();
		        continue;
		    }
		}
		if (!cpufreq_is_enable())
		{
			continue;
		}
		
		cur_profile = cpufreq_get_current_profile();
		result = cpufreq_get_load_result();
		ddr_profile = cpufreq_gov_ddr_decision(cur_profile);
		result = cpufreq_gov_ddr_target(ddr_profile, result);
		if ((DFS_PROFILE_NOCHANGE != result) && (1 == g_cpufreq_task_result_flag))
		{
			task_msg.msg_type = CPUFREQ_ADJUST_FREQ;
			task_msg.source = CPUFREQ_CCORE;
			task_msg.content = result;
			if (DFS_PROFILE_UP_TARGET == result)
			{
				cur_profile = DC_RESV;
			}
			else if ((u32)cur_profile == CPUFREQ_MIN_PROFILE_LIMIT)
			{
				continue;
			}
			task_msg.profile = (unsigned int)cur_profile - 1;
			(void)cpufreq_driver_target(&task_msg);
        }

    }
}

static int cpufreq_governor_ondemand_resume(struct dpm_device *cpufreq_resume)
{
    g_in_interr_times = 0;
	g_stDfsCpuControl.ulCurSysDownTime = 0;
    g_stDfsCpuControl.ulCurSysUpTime = 0;
    return BSP_OK;
}


int cpufreq_governor_ondemand_init(ST_PWC_DFS_STRU cpufreq_nv)
{
	(void)memcpy_s(&gov_ctrl_info, sizeof(ST_PWC_DFS_STRU), &cpufreq_nv, sizeof(ST_PWC_DFS_STRU));
    (void)memset_s(&g_stDfsCpuControl, sizeof(DFS_CONTROL_STRU), 0, sizeof(DFS_CONTROL_STRU));
    (void)osl_task_init("ondemand_dfs_task", 1,4096, (OSL_TASK_FUNC)cpufreq_dfs_ondemand_task, 0,&cpufreq_ondemand_task_id);/*lint !e64 !e119 */    
    /*添加DDR调频请求*/
    (void)cpufreq_qos_request(DFS_QOS_ID_DDR_MINFREQ, BALONG_DDRFREQUENCY_MIN, &g_cpufreq_core_ctrl.g_ddr_request_id);
    return OK;
}
int cpufreq_governor_ondemand_release(void)
{
	if (cpufreq_ondemand_task_id)
		(void)osl_task_delete(&cpufreq_ondemand_task_id);
	return OK;
}


struct cpufreq_governor_s cpufreq_governor_ondemand = {
	.gov_name = "ondemand",
	.gov_id = 1,
	.gov_ops = {
		.governor_init = cpufreq_governor_ondemand_init,
		.governor_release = cpufreq_governor_ondemand_release,
		.governor_decision = cpufreq_governor_ond_decision,
		.governor_resume = cpufreq_governor_ondemand_resume,
	},
};

#ifdef __cplusplus
}
#endif



