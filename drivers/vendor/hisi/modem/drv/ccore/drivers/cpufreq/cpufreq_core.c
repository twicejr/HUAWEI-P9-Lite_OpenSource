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

#include <mdrv_icc.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>

#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <of.h>
#include <bsp_hardtimer.h>
#include <bsp_icc.h>
#include <bsp_nvim.h>
#include <bsp_dpm.h>
#include <bsp_dump.h>

#include "cpufreq_balong.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*lint --e{413} */
/*读取NV*/
ST_PWC_DFS_STRU cpufreq_nv_ctrl={
    .CcpuDownLimit = 60,
    .CcpuDownNum = 3,
    .CcpuUpLimit = 85,
    .CcpuUpNum = 1,
    .DFSTimerLen = 400,
    .Strategy = 0,
    .DFSDdrUpLimit = 85,
    .DFSDdrDownLimit = 60,
    .DFSDdrprofile = 5,
    .reserved = 0,    
};

struct cpufreq_core_st g_cpufreq_core_ctrl = {
    .g_cpufreq_lock_status_flag = 0,/*cpufreq 锁定标志 1:未锁，0: 锁定(锁定后不会主动调频)*/
    .g_ddr_request_id = 0,
    .g_last_ddr_value_id = 0,
    .g_cpufreq_is_sync_ddr = 1,
    .g_cpufreq_bus_vote_valid = 0,
    .g_bus_total_freq = 0,
    .g_cpufreq_ddr_max_profile = 6,
};

int g_cur_profile = 0;

int g_cpufreq_max_profile = 5;/*dts 读取当前芯片profile数*/

struct cpufreq_governor_s governor_list;
struct cpufreq_driver_s driver_list;

struct cpufreq_driver_s *cpufreq_driver;
struct cpufreq_governor_s *cpufreq_governor;

/*频率表*/
static struct cpufreq_frequency_table *balong_clockrate_table = NULL;
struct cpufreq_query *balong_query_profile_table = NULL;


static inline void cpufreq_pm_om_log(struct cpufreq_msg *msg)
{
	struct cpufreq_debug_msg debug_msg_log = {msg->msg_type, msg->source, msg->content, msg->profile, 0, 0, 0};
	debug_msg_log.taskid = osl_task_self();
	debug_msg_log.cur_profile = (unsigned int)cpufreq_get_current_profile();
	debug_msg_log.cur_load = g_ulCCpuload;
	(void)bsp_pm_log_type(PM_OM_CPUF, CPUFREQ_ICC_LOG, sizeof(struct cpufreq_debug_msg), &debug_msg_log);
}

u32 cpufreq_is_enable(void)
{
	return (u32)g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag;
}
void cpufreq_set_enable(int lock_flag)
{
	g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag = lock_flag;
}
static void cpufreq_check_profile_limit(int *max_limit, int *min_limit)
{
	*max_limit = BALONG_FREQ_MAX;
	*min_limit = BALONG_FREQ_MIN;
	if ((CPUFREQ_MAX_PROFILE_LIMIT >= CPUFREQ_MIN_PROFILE_LIMIT)
	&& ((s32)CPUFREQ_MAX_PROFILE_LIMIT <= BALONG_FREQ_MAX)
	&& ((s32)CPUFREQ_MIN_PROFILE_LIMIT >= BALONG_FREQ_MIN))
	{
		*max_limit = (s32)CPUFREQ_MAX_PROFILE_LIMIT;
    	*min_limit = (s32)CPUFREQ_MIN_PROFILE_LIMIT;
	}
}

/*检查调频请求是否符合限制*/
static int cpufreq_check_msg(struct cpufreq_msg *msg)
{
	int ret = BSP_OK;
	int max_limit = 0;
	int min_limit = 0;
	cpufreq_check_profile_limit(&max_limit, &min_limit);
	int cur_profile = cpufreq_get_current_profile();
	if (CPUFREQ_ADJUST_FREQ == msg->msg_type)
	{
		switch(msg->content)
		{
			case DFS_PROFILE_UP:
			case DFS_PROFILE_UP_TARGET:
				if (max_limit == cur_profile)
				{
					ret = BSP_ERROR;
				}
				if (msg->profile > (u32)max_limit)
				{
					msg->profile = (u32)max_limit;
				}
				break;
			case DFS_PROFILE_DOWN:
			case DFS_PROFILE_DOWN_TARGET:
				if (min_limit == cur_profile)
				{
					ret = BSP_ERROR;
				}
				if (msg->profile < (u32)min_limit)
				{
					msg->profile = (u32)min_limit;
				}
				break;
			case DFS_PROFILE_DOWN_LIMIT:
				if ((u32)min_limit == msg->profile)
				{
					ret =BSP_ERROR;
				}
				break;
			case DFS_PROFILE_UP_LIMIT:
				if ((u32)max_limit == msg->profile)
				{
					ret =BSP_ERROR;
				}
				break;
			default:
				break;
		}
	}/*CPUFREQ_ADJUST_FREQ == msg->msg_type*/
	return ret;
}
/*
 * 发送消息 BSP_ERROR 发送失败;BSP_OK 发送成功
 */
int cpufreq_icc_send(struct cpufreq_msg *msg)
{
	u32 channel_id = ICC_CHN_MCORE_CCORE << 16 | MCU_CCORE_CPUFREQ;
	s32 ret = 0;
	u32 time_value = 0;
	u32 msg_len = sizeof(struct cpufreq_msg);
	ret = cpufreq_check_msg(msg);
	if (BSP_ERROR == ret)
	{
		bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MUDU_CPUFREQ,"msg is: msg_type:%d source:%d content:%d profile:%d\n",
														msg->msg_type, msg->source, msg->content, msg->profile);
		return BSP_OK;
	}
	if(g_cpufreq_core_ctrl.cdrx_dump_addr)
	{
		time_value=  bsp_get_slice_value();
		writel(time_value, (unsigned)(g_cpufreq_core_ctrl.cdrx_dump_addr + CDRX_DUMP_CPUF_ICC_SLICE_ADDR));
	}

	cpufreq_pm_om_log(msg);
	bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MUDU_CPUFREQ,"msg is: msg_type:%d source:%d content:%d profile:%d\n",
														msg->msg_type, msg->source, msg->content, msg->profile);
    cpufreq_debug_record_icc_msg(msg);
	ret = bsp_icc_send(ICC_CPU_MCU, channel_id, (u8 *)msg, msg_len);

	if((ret < 0) && (ret != BSP_ERR_ICC_CCORE_RESETTING))
	{
		cpufreq_err("mcore return an ERROR please check m3 %d\n", ret);
		return BSP_ERROR;
	}

    return BSP_OK;
}


/*获取大于等于请求频率的最小profile*/
int cpufreq_get_ccore_profile(int request_freq)
{
	int target_profile = BALONG_FREQ_MAX;
	int i = 0;
	
	for (i = BALONG_FREQ_MIN; i < DC_RESV; i++)
	{
		if (balong_query_profile_table[i].cpu_frequency >= (unsigned int)request_freq)
		{
			target_profile = (s32)balong_query_profile_table[i].profile;
			break;
		}
	}
	cpufreq_debug("ccore target_profile:%d\n", target_profile);
	return target_profile;
}
/*获取大于等于请求频率的最小profile*/
int cpufreq_get_ddr_profile(int request_freq)
{
	int target_profile = BALONG_FREQ_MAX;
	int i = 0;
	/* 同步调频*/
	if (g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
	{
		for (i = BALONG_FREQ_MIN; i < DC_RESV; i++)
		{
			if (balong_query_profile_table[i].ddr_frequency >= (unsigned int)request_freq)
			{
				target_profile = (s32)balong_query_profile_table[i].profile;
				break;
			}
		}
	}
	else
	{
		target_profile = request_freq;
	}
	cpufreq_debug("ddr target_profile:%d\n", target_profile);
	return target_profile;
}
/*获取大于等于请求频率的最小profile*/
int cpufreq_get_bus_profile(int request_freq)
{
	int target_profile = BALONG_FREQ_MIN;
#if 0
	int target_profile = BALONG_FREQ_MAX;
	int i = 0;

	for (i = BALONG_FREQ_MIN; i < DC_RESV; i++)
	{
		if (balong_query_profile_table[i]>= request_freq)
		{
			target_profile = balong_query_profile_table[i].profile;
			goto bus_out;
		}
	}

bus_out:
	cpufreq_debug("ddr target_profile:%d\n", target_profile);
	return target_profile;
#endif
	if (g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
	{
        target_profile = BALONG_FREQ_MIN;
	}
	else
	{
        target_profile = request_freq;
	}

	return target_profile;
}


int cpufreq_find_min_profile(unsigned int a9freq, unsigned int ddrfreq, unsigned int slowfreq)
{
	int target_profile = DC_RESV;
	int i = 0;
	if (!cpufreq_is_enable())
	{
		return BALONG_FREQ_MAX;
	}
	for (i = BALONG_FREQ_MIN; i < DC_RESV; i++)
	{
		if ((balong_query_profile_table[i].cpu_frequency >= a9freq) && (balong_query_profile_table[i].ddr_frequency >= ddrfreq)
					&& (balong_query_profile_table[i].sbus_frequency >= slowfreq))
		{
			if (target_profile >= (int)balong_query_profile_table[i].profile)
			{
				target_profile = (int)balong_query_profile_table[i].profile;
			}
		}
	}
	if (DC_RESV == target_profile)
	{
		target_profile = BALONG_FREQ_MAX;
	}
	return target_profile;
}
void cpufreq_find_frequence(int profile, struct cpufreq_query *freq_table)
{
    if ((profile <= BALONG_FREQ_MAX) && (BALONG_FREQ_MIN <= profile))
    {
        freq_table->cpu_frequency = balong_query_profile_table[profile].cpu_frequency;
        freq_table->ddr_frequency= balong_query_profile_table[profile].ddr_frequency;
        freq_table->sbus_frequency = balong_query_profile_table[profile].sbus_frequency;
    }
}
int cpufreq_governor_decision(unsigned int cpuload)
{
    if (cpufreq_governor && cpufreq_governor->gov_ops.governor_decision)
        return cpufreq_governor->gov_ops.governor_decision(cpuload);
    return DFS_PROFILE_NOCHANGE;
}
void cpufreq_governor_register(struct cpufreq_governor_s *cpufreq_gov)
{	
	unsigned long irqlock = 0;
	if (NULL == cpufreq_gov)
	{
		return;
	}
	local_irq_save(irqlock);
	INIT_LIST_HEAD(&(cpufreq_gov->entry));
	list_add_tail(&(cpufreq_gov->entry), &(governor_list.entry));	
	local_irq_restore(irqlock);
}
void cpufreq_driver_register(struct cpufreq_driver_s *cpufreq_drv)
{	
	unsigned long irqlock = 0;
	if (NULL == cpufreq_drv)
	{
		return;
	}
	local_irq_save(irqlock);
	INIT_LIST_HEAD(&(cpufreq_drv->entry));
	list_add_tail(&(cpufreq_drv->entry), &(driver_list.entry));	
	local_irq_restore(irqlock);
}

void cpufreq_find_governor(const char *name, int id, struct cpufreq_governor_s **gov)
{
	unsigned long irqlock = 0;
	struct cpufreq_governor_s *gov_list = NULL;
	local_irq_save(irqlock);
	list_for_each_entry(gov_list, &(governor_list.entry), entry)
	{
		if((NULL != name) && (!(strcmp(gov_list->gov_name, name))))
		{
			*gov = gov_list;
			break;
		}
		if ((0 <= id) && (id == gov_list->gov_id))
		{
			*gov = gov_list;
			break;
		}
	}
	local_irq_restore(irqlock);
	return;

}
void cpufreq_find_driver(const char *name, int id, struct cpufreq_driver_s **drv)
{
	unsigned long irqlock = 0;
	struct cpufreq_driver_s *drv_list = NULL;
	local_irq_save(irqlock);
	list_for_each_entry(drv_list, &(driver_list.entry), entry)
	{
		if((NULL != name) && (!(strcmp(drv_list->drv_name, name))))
		{
			*drv = drv_list;
			break;
		}
		if ((0 <= id) && (id == drv_list->drv_id))
		{
			*drv = drv_list;
			break;
		}
	}
	local_irq_restore(irqlock);
	return;
}

void cpufreq_governor_switch(int id)
{
	unsigned long irqlock = 0;
	local_irq_save(irqlock);
	if (cpufreq_governor && cpufreq_governor->gov_ops.governor_release)
		(void)cpufreq_governor->gov_ops.governor_release();
	cpufreq_find_governor(NULL, id, &cpufreq_governor);
	if (cpufreq_governor && cpufreq_governor->gov_ops.governor_init)
		(void)cpufreq_governor->gov_ops.governor_init(cpufreq_nv_ctrl);
	local_irq_restore(irqlock);
}

void cpufreq_driver_switch(int id)
{
	unsigned long irqlock = 0;
	local_irq_save(irqlock);
	cpufreq_find_driver(NULL, id, &cpufreq_driver);
	if (cpufreq_driver && cpufreq_driver->drv_ops.driver_init)
		(void)cpufreq_driver->drv_ops.driver_init();
	local_irq_restore(irqlock);
}

int cpufreq_get_current_profile(void)
{
	int cur_profile = BALONG_FREQ_MAX;
	if (cpufreq_driver && cpufreq_driver->drv_ops.get_current_profile)
		cur_profile = cpufreq_driver->drv_ops.get_current_profile();
	g_cur_profile = cur_profile;

	if(g_cpufreq_core_ctrl.cdrx_dump_addr)
	{
		writel(CDRX_DUMP_CPUF_MAGIC, (unsigned)(g_cpufreq_core_ctrl.cdrx_dump_addr + CDRX_DUMP_CPUF_MAGIC_ADDR));
		writel((unsigned int)cur_profile, (unsigned)(g_cpufreq_core_ctrl.cdrx_dump_addr + CDRX_DUMP_CPUF_CUR_PROF_ADDR));
	}

	return cur_profile;
}

int cpufreq_driver_target(struct cpufreq_msg *msg)
{	
	if (!cpufreq_is_enable())
	{
		return BSP_ERROR;
	}
	cpufreq_debug_record_target_msg(msg);
	if (cpufreq_driver && cpufreq_driver->drv_ops.driver_target)
		return cpufreq_driver->drv_ops.driver_target(msg);
	return BSP_OK;
}
void cpufreq_enter_idle(void)
{
    if (!cpufreq_is_enable())
	{
		return;
	}

	if (cpufreq_driver && cpufreq_driver->drv_ops.enter_idle)
		cpufreq_driver->drv_ops.enter_idle();
	return;
}
void cpufreq_exit_idle(void)
{
    if (!cpufreq_is_enable())
	{
		return;
	}

	if (cpufreq_driver && cpufreq_driver->drv_ops.exit_idle)
		cpufreq_driver->drv_ops.exit_idle();
	return;
}

void cpufreq_match_init(struct device_node *cpufreq_n)
{
	int ret = 0;
	const char *gov_name = NULL;
	const char *drv_name = NULL;
	ret = of_property_read_string(cpufreq_n,"hisi_gov_name", &gov_name);
	ret |= of_property_read_string(cpufreq_n,"hisi_drv_name", &drv_name);
	if ((!ret) && (NULL != drv_name) && (NULL != gov_name))
	{
		cpufreq_find_governor(gov_name, -1, &cpufreq_governor);
		if (cpufreq_governor && cpufreq_governor->gov_ops.governor_init)
			(void)cpufreq_governor->gov_ops.governor_init(cpufreq_nv_ctrl);
			
		cpufreq_find_driver(drv_name, -1, &cpufreq_driver);
		if (cpufreq_driver && cpufreq_driver->drv_ops.driver_init)
			(void)cpufreq_driver->drv_ops.driver_init();
	}
	else
	{
		cpufreq_err("match init error,check dts or other init\n");
	}
	return;
}



struct device_node *cpufreq_node = NULL;
static int cpufreq_table_init(void)
{
	int i = 0;
	int ret = 0;
	unsigned int profile_count = 0;
	unsigned int is_sync_ddr[2] = {0,0};
	unsigned int *cpufreq_cpu_freq = NULL;
	unsigned int *cpufreq_ddr_freq = NULL;
	cpufreq_node = of_find_compatible_node(NULL, NULL, "cpufreq_balong_ccore");
	if (!cpufreq_node)
	{
		cpufreq_err("cpufreq dts node not found!  %s\n");
		return ERROR;
	}
	if(!of_property_read_u32_array(cpufreq_node, "cpufreq_freq_count", &profile_count, 1))
		g_cpufreq_max_profile = (s32)profile_count;
	if(!of_property_read_u32_array(cpufreq_node, "cpufreq_is_sync_ddr", is_sync_ddr, 2))
	{
		g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr = (s32)is_sync_ddr[0];
		g_cpufreq_core_ctrl.g_cpufreq_ddr_max_profile = (s32)is_sync_ddr[1];
	}
	balong_query_profile_table = (struct cpufreq_query *) osl_malloc(sizeof(struct cpufreq_query) * (g_cpufreq_max_profile + 1));
	if (NULL == balong_query_profile_table)
	{
		cpufreq_err("malloc profile table failed \n");
		return ERROR;
	}
	cpufreq_cpu_freq = (unsigned int *)osl_malloc(sizeof(unsigned int) * g_cpufreq_max_profile);
	if (NULL == cpufreq_cpu_freq)
	{
		cpufreq_err("malloc cpu freq failed\n");
		osl_free(balong_query_profile_table);
		return ERROR;
	}
	cpufreq_ddr_freq = (unsigned int *)osl_malloc(sizeof(unsigned int) * g_cpufreq_max_profile);
	if (NULL == cpufreq_ddr_freq)
	{
		cpufreq_err("malloc ddr freq failed\n");
		osl_free(balong_query_profile_table);
		osl_free(cpufreq_cpu_freq);
		return ERROR;
	}
	ret = of_property_read_u32_array(cpufreq_node, "cpufreq_cpu_frequence", cpufreq_cpu_freq, (u32)g_cpufreq_max_profile);
	ret |= of_property_read_u32_array(cpufreq_node, "cpufreq_ddr_frequence", cpufreq_ddr_freq, (u32)g_cpufreq_max_profile);
	balong_clockrate_table = (struct cpufreq_frequency_table *) osl_malloc(sizeof(struct cpufreq_query) * (g_cpufreq_max_profile + 1));
	if (NULL == balong_clockrate_table)
	{
		cpufreq_err("malloc balong_clockrate_table table failed \n");
		osl_free(balong_query_profile_table);
		osl_free(cpufreq_cpu_freq);
		osl_free(cpufreq_ddr_freq);
		return ERROR;
	}
	for (i = BALONG_FREQ_MIN; (!ret) && (i < DC_RESV); i++)
	{
		balong_query_profile_table[i].profile = (u32)i;
		balong_query_profile_table[i].cpu_frequency = cpufreq_cpu_freq[i];
		balong_query_profile_table[i].ddr_frequency = cpufreq_ddr_freq[i];
		balong_clockrate_table[i].index = balong_query_profile_table[i].profile;
		balong_clockrate_table[i].frequency = balong_query_profile_table[i].cpu_frequency;
	}
	balong_clockrate_table[DC_RESV].index = (u32)DC_RESV;
	balong_clockrate_table[DC_RESV].frequency = CPUFREQ_TABLE_END;
	osl_free(cpufreq_cpu_freq);
	osl_free(cpufreq_ddr_freq);
	return BSP_OK;
}

#ifdef CONFIG_CCORE_PM
static int cpufreq_resume(struct dpm_device *resume_device)
{
    if (cpufreq_governor && cpufreq_governor->gov_ops.governor_resume)
        (void)cpufreq_governor->gov_ops.governor_resume(resume_device);
    if (cpufreq_driver && cpufreq_driver->drv_ops.driver_resume)
        (void)cpufreq_driver->drv_ops.driver_resume(resume_device);
    return BSP_OK;
}

static struct dpm_device g_cpufreq_dpm_device={
    .device_name = "cpufreq_dpm",
    .resume = cpufreq_resume,
};
#endif


/*****************************************************************************
Function:   cpufreq_init
Description:DFS Module Initialiation Process
Input:      None
Output:     None
Return:     None
Others:
*****************************************************************************/
int  cpufreq_init(void)
{
	/*lint --e{516}*/
	int ret = 0;
	u32 retValue = 0;
	ST_PWC_SWITCH_STRU cpufreq_control_nv = {0};
    ST_PWC_DFS_STRU cpufreq_nv = {0};
    
    retValue = bsp_nvm_read(NV_ID_DRV_NV_DFS_SWITCH,(u8*)&cpufreq_nv,sizeof(ST_PWC_DFS_STRU));
    if (NV_OK == retValue)
    {
        (void)memcpy_s(&cpufreq_nv_ctrl, sizeof(ST_PWC_DFS_STRU), &cpufreq_nv, sizeof(ST_PWC_DFS_STRU));
    }
    g_cpufreq_core_ctrl.g_cpufreq_bus_vote_valid = (cpufreq_nv_ctrl.Strategy >> 2) & 0x1;
	ret = cpufreq_table_init();
	if (ret != OK)
	{
		g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag = 0;
		cpufreq_err("init cpufreq freq table failed return\n");
		return -1;
	}
	INIT_LIST_HEAD(&(driver_list.entry));
	INIT_LIST_HEAD(&(governor_list.entry));
	cpufreq_api_init();
	cpufreq_governor_init(cpufreq_nv_ctrl);
	cpufreq_driver_init();
	cpufreq_match_init(cpufreq_node);

	retValue = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH,(u8*)&cpufreq_control_nv,sizeof(ST_PWC_SWITCH_STRU));
	if (NV_OK == retValue)
	{
		g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag = cpufreq_control_nv.dfs;
	}
	else
	{
		g_cpufreq_core_ctrl.g_cpufreq_lock_status_flag = 0;
		cpufreq_err("read nv failed %d\n", retValue);
	}
#ifdef CONFIG_CCORE_PM
    if (bsp_device_pm_add(&g_cpufreq_dpm_device))
    {
		cpufreq_err("register dpm failed,check it\n");
    }
#endif

	g_cpufreq_core_ctrl.cdrx_dump_addr = 0;
	g_cpufreq_core_ctrl.cdrx_dump_addr = (char *)bsp_dump_register_field(DUMP_CP_DRX, "DRX_CCORE", 0, 0, PM_DUMP_CCORE_DRX_SIZE, 0);
	if(NULL == g_cpufreq_core_ctrl.cdrx_dump_addr)
	{
		cpufreq_err("get dump buffer failed!\n");
	}

	cpufreq_err("cpufreq init ok\n");
	
    return 0;
}


#ifdef __cplusplus
}
#endif




