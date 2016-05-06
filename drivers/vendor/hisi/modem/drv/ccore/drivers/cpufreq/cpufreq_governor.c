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


/*调频模块开启声明该宏，用于和CPUIDLE解耦*/
#ifdef CONFIG_CPUFREQ
/*task idle time, unit:slice*/
unsigned int g_ulDfsCcpuIdleTime = 1;
unsigned int g_ulDfsCcpuIdleTime_long = 1;
#else
extern unsigned int g_ulDfsCcpuIdleTime;
extern unsigned int g_ulDfsCcpuIdleTime_long;
#endif

static unsigned int g_cpufreq_start_time = 0;
static unsigned int g_cpufreq_int_ctrl_start_time = 0;

/*当前占用率*/
u32 g_ulCCpuload = 1;

u32 g_cpuload_debug_count = 0;

osl_sem_id g_sem_calccpu_flag = 0;
/*用于计时*/
unsigned int g_in_interr_times = 0;
/*用于流控负载统计计时*/
unsigned int g_flowctrl_in_interr_times = 0;

unsigned int g_calccpu_load_result = DFS_PROFILE_NOCHANGE;
/*通过NV读取，多少个tick后进行负载统计*/
unsigned int g_cpufreq_in_interr_times = 20;

unsigned int cpufreq_get_load_result(void)
{
	return g_calccpu_load_result;
}

/*
	调频策略
*/
static inline u32  cpufreq_cpuload_result_insysint(void)
{
    u32 ulSleepTime;
    u32 ulCpuLoad_C;
    u32 ulProTime;
    u32 ulEndTime;

    /*这里是读取时间,暂时大桩*/
	ulEndTime = bsp_get_slice_value();
  	ulProTime = get_timer_slice_delta(g_cpufreq_int_ctrl_start_time, ulEndTime);
	ulSleepTime = g_ulDfsCcpuIdleTime;
	g_ulDfsCcpuIdleTime = 0;
	g_cpufreq_int_ctrl_start_time = ulEndTime;
	
	ulCpuLoad_C= (ulProTime == 0) ? (0) : (((ulProTime -ulSleepTime)* 100) / (ulProTime));    /*Calc the Cpu load Value*/
	if (ulCpuLoad_C > 100)
	{
		g_cpuload_debug_count++;
		ulCpuLoad_C = 100;
	}
	g_ulCCpuload = ulCpuLoad_C;
	if(g_cpufreq_core_ctrl.cdrx_dump_addr)
	{
		writel(g_ulCCpuload, (unsigned)(g_cpufreq_core_ctrl.cdrx_dump_addr + CDRX_DUMP_CPUF_CPULOAD_ADDR));
	}
	
    return (u32)cpufreq_governor_decision(ulCpuLoad_C);
}

void cpufreq_checkload_in_sysint(void)
{
	if (!cpufreq_is_enable())
	{
		return;
	}
	if (0 != g_sem_calccpu_flag)
	{
		if (g_in_interr_times >= g_cpufreq_in_interr_times)/* [false alarm]:为误报*/
		{
			g_calccpu_load_result = cpufreq_cpuload_result_insysint();

			g_in_interr_times = 0;
			if (DFS_PROFILE_NOCHANGE != g_calccpu_load_result)
			{
				osl_sem_up(&g_sem_calccpu_flag);
			}
		}
		else
		{
			g_in_interr_times++;
		}
		/*2s释放信号量，回调流控接口*/
		if (g_flowctrl_in_interr_times == 200)
		{
			osl_sem_up(&g_sem_calccpu_flag);
		}
		g_flowctrl_in_interr_times++;
	}
}

unsigned int cpufreq_cpu_load(void)
{
	u32 end_time = 0;
	u32 idle_time = 0;
	u32 wall_time = 0;
	u32 cpu_load = 0;
	unsigned long irqlock = 0;
	local_irq_save(irqlock);
	end_time = bsp_get_slice_value();
	wall_time = get_timer_slice_delta(g_cpufreq_start_time, end_time);
	idle_time = g_ulDfsCcpuIdleTime_long;
	g_cpufreq_start_time = end_time;
	g_ulDfsCcpuIdleTime_long = 0;
	g_flowctrl_in_interr_times = 0;
	cpu_load = (wall_time == 0) ? (0) : (((wall_time - idle_time) * 100) / wall_time);
	local_irq_restore(irqlock);
	if (cpu_load > 100)
	{
		cpu_load = g_ulCCpuload;
		cpufreq_info("cpuload: %d, wall:%d, idle:%d\n", cpu_load, wall_time, idle_time);
	}
	return cpu_load;
}

extern struct cpufreq_governor_s cpufreq_governor_ondemand;
void cpufreq_governor_init(ST_PWC_DFS_STRU cpufreq_nv)
{
	g_cpufreq_start_time = bsp_get_slice_value();
	g_cpufreq_int_ctrl_start_time = bsp_get_slice_value();
    g_cpufreq_in_interr_times = cpufreq_nv.DFSTimerLen;
   	osl_sem_init(SEM_EMPTY, &g_sem_calccpu_flag);
	cpufreq_governor_register(&cpufreq_governor_ondemand);
}

#ifdef __cplusplus
}
#endif


