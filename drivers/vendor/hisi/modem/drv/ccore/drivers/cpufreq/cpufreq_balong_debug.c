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
/*lint --e{525, 537, 539, 737, 830 } */
#include <product_config.h>
#include <securec.h>
#include <string.h>
#include <stdlib.h>
#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include "osl_cache.h"
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

extern DFS_CONTROL_STRU g_stDfsCpuControl;
extern ST_PWC_DFS_STRU cpufreq_nv_ctrl;
extern struct cpufreq_msg g_cpufreq_debug_msg;
extern struct cpufreq_msg target_debug_msg;
extern unsigned int g_cpufreq_task_result_flag;
extern struct cpufreq_driver_s *cpufreq_driver;
extern struct cpufreq_governor_s *cpufreq_governor;
extern int cpufreq_dfs_set_profile(int profile);

struct cpufreq_msg g_cpufreq_debug_msg = {0,0,0,0};
struct cpufreq_msg target_debug_msg = {0,0,0,0};

void cpufreq_debug_record_icc_msg(struct cpufreq_msg *msg)
{  
	g_cpufreq_debug_msg.msg_type = msg->msg_type;
	g_cpufreq_debug_msg.source = msg->source;
	g_cpufreq_debug_msg.content = msg->content;
	g_cpufreq_debug_msg.profile = msg->profile;
}

void cpufreq_debug_record_target_msg(struct cpufreq_msg *msg)
{
	target_debug_msg.msg_type = msg->msg_type;
	target_debug_msg.source = msg->source;
	target_debug_msg.content = msg->content;
	target_debug_msg.profile = msg->profile;
}
//extern int g_last_ddr_value_id;
void cpufreq_print_debug(void)
{
	int profile = 0;
	profile = cpufreq_dfs_get_profile();
	cpufreq_err("cur profile: %d\n", profile);
	cpufreq_err("ccore load: %d\n", g_ulCCpuload);
	//cpufreq_err("lase\t ddr: %d\n", g_last_ddr_value_id);
	cpufreq_err("up      times: %d\n", g_stDfsCpuControl.ulCurSysUpTime);
	cpufreq_err("down  times: %d\n", g_stDfsCpuControl.ulCurSysDownTime);
	cpufreq_err("up_threshold: %d\n", cpufreq_nv_ctrl.CcpuUpLimit);
	cpufreq_err("up_threshold_times: %d\n",  cpufreq_nv_ctrl.CcpuUpNum);
	cpufreq_err("down_threshold: %d\n", cpufreq_nv_ctrl.CcpuDownLimit);
	cpufreq_err("down_threshold_times: %d\n",  cpufreq_nv_ctrl.CcpuDownNum);
	cpufreq_err("sampling_rate: %d\n", cpufreq_nv_ctrl.DFSTimerLen);
	if (cpufreq_governor)
		cpufreq_err("gov_name: %s\n", cpufreq_governor->gov_name);
	if (cpufreq_driver)
		cpufreq_err("drv_name: %s\n", cpufreq_driver->drv_name);
	cpufreq_err("last icc msg\n");
	cpufreq_err("icc msg_type: %d\n", g_cpufreq_debug_msg.msg_type);
	cpufreq_err("icc source: %d\n", g_cpufreq_debug_msg.source);
	cpufreq_err("icc content: %d\n", g_cpufreq_debug_msg.content);
	cpufreq_err("icc profile: %d\n", g_cpufreq_debug_msg.profile);
	cpufreq_err("target msg_type: %d\n", target_debug_msg.msg_type);
	cpufreq_err("target source: %d\n", target_debug_msg.source);
	cpufreq_err("target content: %d\n", target_debug_msg.content);
	cpufreq_err("target profile: %d\n", target_debug_msg.profile);
	cpufreq_err("cur max limit:%d\n", CPUFREQ_MAX_PROFILE_LIMIT);
	cpufreq_err("cur min limit:%d\n", CPUFREQ_MIN_PROFILE_LIMIT);
}

void cpufreq_debug_stop(int flag, int enable)
{
	g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag = flag;
	g_cpufreq_task_result_flag = enable;
}

void cpufreq_debug_set_target(unsigned int msg_type, unsigned int source, unsigned int content, unsigned int profile)
{
	struct cpufreq_msg task_msg = {0,0,0,0};
	task_msg.msg_type = msg_type;
	task_msg.source = source;
	task_msg.content = content;
	task_msg.profile = profile;
	(void)cpufreq_driver_target(&task_msg);
}

void cpufreq_debug_qos_interface(int inter_id, int request_id, int request_freq, int req_id)
{
	int req_request_id = 0;
	switch(inter_id)
	{
		case 0://request
			if (cpufreq_qos_request(request_id, (u32)request_freq, &req_request_id))
			{
				cpufreq_err("QosRequest error\n");
			}
			break;
		case 1://release
			if (cpufreq_qos_release(request_id, &req_request_id))
			{
				cpufreq_err("QosRelease error\n");
			}
			break;
		case 2: //update
			(void)cpufreq_qos_update(request_id, req_id, (u32)request_freq);
			break;
		default:
			break;
	}
}

/*1 tick 3000000*/
unsigned int busy_time = 10;
unsigned int idle_time = 1;
unsigned long start_time = 0;
void cpufreq_debug_cpuload(int busytime, int idletime)
{
	if (busytime)
	busy_time = (u32)busytime;
	if (idletime)
	idle_time = (u32)idletime;
}

#define TEST_CPUFREQ_ADDR_FROM_PM  (0x3e396f30 + 0x218)

static void cpufreq_debug_stress(void)
{
	if (!idle_time)
	{
        cpufreq_err("leave load task\n");
	}
	//writel(0x41414141, TEST_CPUFREQ_ADDR_FROM_PM);
	//readl(TEST_CPUFREQ_ADDR_FROM_PM);
}
 
void cpufreq_debug_task(void)
{/*lint --e{716 } */
	while (1)
	{
		start_time = bsp_get_elapse_ms();
		while (bsp_get_elapse_ms()-start_time <= busy_time)
		{
			cpufreq_debug_stress();
		}
		(void)osl_task_delay((int)idle_time);
		if (!idle_time)
		{
			break;
		}
	}
}

void cpufreq_debug_switch_load_auto(void)
{/*lint --e{716 } */
	int which_load_bound = 0;
	/* coverity[INFINITE_LOOP] */
	/* coverity[no_escape] */
	while(1)
	{
		/*每30s改变cpu占用，测试长时间调频是否正常*/
		(void)osl_task_delay(3000);
		switch(which_load_bound)
		{
			case 0:
				cpufreq_debug_cpuload(40, 1);//90
				break;
			case 1:
				cpufreq_debug_cpuload(10,1);//50
				break;
			case 2:
				cpufreq_debug_cpuload(13,1);//8-11
				break;
			default:
				break;
		}
		which_load_bound = (which_load_bound + 1) % 3;
	}
}

void cpufreq_debug_start_cpuload_task(void)
{
	OSL_TASK_ID ret = 0;
	(void)osl_task_init("testPmuEvent", 2, 4096, (OSL_TASK_FUNC)cpufreq_debug_task, 0, &ret); /*lint !e64 !e119 */
}

u32 cpufreq_ddr_num = 1024;
u32 cpufreq_debug_ddr_size = 1024;
u32 cpufreq_debug_ddr_pro = 0;
u32 cpufreq_debug_ddr_flag = 1;
u32 cpufreq_debug_ddr_tick = 10;
void cpufreq_debug_change_ddr_size(u32 size, u32 tick)
{
    cpufreq_ddr_num = size;
    cpufreq_debug_ddr_tick = tick;
}

void cpufreq_debug_ddr_stress_task(void)
{
    u32 tmp = 0;
    u32 i = 0, j = 0;
    u32 *ddt_test_addr = NULL;
    cpufreq_debug_ddr_size = cpufreq_ddr_num * cpufreq_ddr_num;
    ddt_test_addr = (u32 *)osl_malloc(cpufreq_debug_ddr_size);
    if (NULL == ddt_test_addr)
    {
        cpufreq_err("malloc failed\n");
        return;
    }
    while (cpufreq_debug_ddr_flag)
    {
        for (i = BALONG_FREQ_MAX; i > BALONG_FREQ_MIN; i--)
        {
            for (j = (u32)BALONG_FREQ_MIN; j < (u32)BALONG_FREQ_MAX; j++)
            {
                cpufreq_debug_set_target(1, 1, 4, 0);
                if (g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
                    cpufreq_debug_set_target(1, 0, 4, 0);
                (void)cpufreq_dfs_set_profile((s32)i);
                (void)osl_task_delay((s32)cpufreq_debug_ddr_tick);
                tmp = j;/* [false alarm]:debug test program */
                if (g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
                    cpufreq_debug_set_target(1, 0, 3, 0);
                (void)cpufreq_dfs_set_profile((s32)tmp);
                (void)osl_task_delay(1);

                cpufreq_debug_ddr_pro = cpufreq_dfs_get_profile();
                (void)memset_s((void *)ddt_test_addr, cpufreq_debug_ddr_size, 0x14141414, cpufreq_debug_ddr_size);
                (void)osl_cache_flush(OSL_DATA_CACHE, (void *)ddt_test_addr, cpufreq_debug_ddr_size);
                if (memcmp(ddt_test_addr, ddt_test_addr + cpufreq_ddr_num, cpufreq_ddr_num))
                {
                    cpufreq_err("ddr memcmp error have cache flush,cur pro:%d\n", cpufreq_debug_ddr_pro);
                }

                (void)memset_s(ddt_test_addr, cpufreq_debug_ddr_size, 0x28282828, cpufreq_debug_ddr_size);
                if (memcmp(ddt_test_addr, ddt_test_addr + cpufreq_ddr_num, cpufreq_ddr_num))
                {
                    cpufreq_err("ddr memcmp error no cache flush,cur pro:%d\n", cpufreq_debug_ddr_pro);
                }
                (void)osl_task_delay((s32)cpufreq_debug_ddr_tick);
            }
        }
    }
    osl_free(ddt_test_addr);/* [false alarm]:debug test code and  cpufreq_debug_ddr_flag can change to 0*/
}

void cpufreq_debug_ddr_task(void)
{
    OSL_TASK_ID ret = 0;
	(void)osl_task_init("testddr", 33, 4096, (OSL_TASK_FUNC)cpufreq_debug_ddr_stress_task, 0, &ret); /*lint !e64 !e119 */
}

void cpufreq_debug_start_stress_task(void)
{
	OSL_TASK_ID ret = 0;
	(void)osl_task_init("cpufreq_test_task", 2, 4096, (OSL_TASK_FUNC)cpufreq_debug_task, 0, &ret); /*lint !e64 !e119 */
	(void)osl_task_init("cpufreq_stress_test_task", 2, 4096, (OSL_TASK_FUNC)cpufreq_debug_switch_load_auto, 0, &ret); /*lint !e64 !e119 */
}

#ifdef __cplusplus
}
#endif



