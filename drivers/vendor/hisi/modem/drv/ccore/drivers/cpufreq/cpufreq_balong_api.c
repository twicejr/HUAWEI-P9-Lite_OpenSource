/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_balong_api.c
*
*   作    者 :  y00221789
*
*   描    述 :提取对外接口到一个.c中
*
*   修改记录 :  2013年1月2日  v1.00  y00221789  创建
*************************************************************************/

#include <osl_malloc.h>
#include <bsp_hardtimer.h>
#include <mdrv_pm.h>
#include "cpufreq_balong.h"
/*lint --e{322, 413} */
#ifdef __cplusplus
extern "C"
{
#endif



extern struct cpufreq_query *balong_query_profile_table;


/*分配的最后一个request ID*/
int g_last_req_id = 0;
struct DFS_Qos_ST g_qos_list;

struct DFS_Qos_ST g_diffmode_with_vote[END_OF_DIFF_MODE] =
{
	[DIFF_MODE_OF_LT] = {
				.request_id = DIFF_MODE_OF_LT,
				.request_flag = 0,
				.request_profile = BALONG_FREQ_MIN,
	},
	[DIFF_MODE_OF_GU] = {
				.request_id = DIFF_MODE_OF_GU,
				.request_flag = 0,
				.request_profile = BALONG_FREQ_MIN,
	},
};
#define CPUFREQ_VOTE_NUM  (15)
struct DFS_Qos_ST g_cpufreq_vote_info[CPUFREQ_VOTE_NUM];
static inline void cpufreq_save_vote_info(int qos_id, int req_id, int target_freq, int task_id)
{
    static u32 vote_num = 0;
    g_cpufreq_vote_info[vote_num % CPUFREQ_VOTE_NUM].request_id = req_id;
    g_cpufreq_vote_info[vote_num % CPUFREQ_VOTE_NUM].request_type = qos_id;
    g_cpufreq_vote_info[vote_num % CPUFREQ_VOTE_NUM].request_profile = target_freq;
    g_cpufreq_vote_info[vote_num % CPUFREQ_VOTE_NUM].task_id = task_id;
    g_cpufreq_vote_info[vote_num % CPUFREQ_VOTE_NUM].request_flag = (int)bsp_get_slice_value();
    vote_num++;
}
static inline void cpufreq_pm_om_vote_log(int qos_id, int request_freq, int taskid, int req_id, int tar_profile)
{
	struct cpufreq_pm_om_qos_log cpufreq_log = {0, (unsigned int)qos_id, 0, (unsigned int)request_freq, 0};
	cpufreq_log.taskid = (unsigned int)taskid;
	cpufreq_log.req_id = (unsigned int)req_id;
	cpufreq_log.req_true_value = (unsigned int)tar_profile;
	(void)bsp_pm_log_type(PM_OM_CPUF, CPUFREQ_VOTE_LOG, sizeof(struct cpufreq_pm_om_qos_log), &cpufreq_log);
}

int cpufreq_dfs_get_profile(void)
{
	int cur_profile = 0;
	cur_profile = (s32)cpufreq_get_current_profile();
	if ((cur_profile < BALONG_FREQ_MIN) || (cur_profile > BALONG_FREQ_MAX))
	{
		cur_profile = BALONG_FREQ_MAX;
		cpufreq_info("m3 cpufreq return right cur_profile value? %d\n", cur_profile);
	}
	return cur_profile;
}
/*
 * 设置profile
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_profile(int profile)
{
	struct cpufreq_msg set_msg = {0,0,0,0};
	int cur_profile = 0;
	if ((profile < BALONG_FREQ_MIN) || (profile > BALONG_FREQ_MAX))
	{
		cpufreq_err("profile in right bound? %d\n", profile);
		return MDRV_ERROR;
	}
	set_msg.msg_type = CPUFREQ_ADJUST_FREQ;
	set_msg.source = CPUFREQ_CCORE;
	cur_profile = cpufreq_dfs_get_profile();
	if (cur_profile < profile)
	{
		set_msg.content = DFS_PROFILE_UP_TARGET;
	}
	else if (cur_profile > profile)
	{
		set_msg.content = DFS_PROFILE_DOWN_TARGET;
	}
	else
	{
		return MDRV_OK;
	}

	set_msg.profile = (u32)profile;
	return cpufreq_driver_target(&set_msg);
}
/*
 * 设置profile下限
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int cpufreq_dfs_set_baseprofile(int baseprofile)
{
	struct cpufreq_msg set_msg = {0,0,0,0};
	if ((baseprofile < BALONG_FREQ_MIN) || (baseprofile > BALONG_FREQ_MAX))
	{
		cpufreq_err("profile in right bound? %d\n", baseprofile);
		return MDRV_ERROR;
	}
	set_msg.msg_type = CPUFREQ_ADJUST_FREQ;
	set_msg.source = CPUFREQ_CCORE;
	set_msg.content = DFS_PROFILE_DOWN_LIMIT;
	set_msg.profile = (u32)baseprofile;
	return cpufreq_driver_target(&set_msg);
}

void cpufreq_dfs_set_limitprofile_with_voteid(int baseprofile, int request_mode_id)
{
	int i = 0;
	unsigned long irqlock = 0;
	int target_profile = BALONG_FREQ_MIN;
	local_irq_save(irqlock);
	for (i = 0; i < END_OF_DIFF_MODE; i++)
	{
		if (request_mode_id == g_diffmode_with_vote[i].request_id)
		{
			g_diffmode_with_vote[i].request_flag = 1;
			g_diffmode_with_vote[i].request_profile = baseprofile;
		}
		if ((1 == g_diffmode_with_vote[i].request_flag) && (g_diffmode_with_vote[i].request_profile > target_profile))
		{
			target_profile = g_diffmode_with_vote[i].request_profile;
		}
	}
	local_irq_restore(irqlock);
	(void)cpufreq_dfs_set_baseprofile(target_profile);
}

/*
 * 锁定调频 DFS_PROFILE_LOCKFREQ=0锁定;DFS_PROFILE_LOCKFREQ=1解锁
 */
void cpufreq_dfs_lock(u32 lock)
{
	struct cpufreq_msg set_msg = {0,0,0,0};
	
	cpufreq_set_enable((s32)lock);

	set_msg.content = lock;

	set_msg.msg_type = CPUFREQ_LOCK_MCORE_ACTION;
	set_msg.source = CPUFREQ_CCORE;
	(void)cpufreq_driver_target(&set_msg);
}
/*
 * 设置频率 BSP_ERROR 设置失败;BSP_OK 设置成功
 * 入参分别为当前核的cpu频率，ddr频率，slowbus频率
 * 注:因C核profile4、5的频率相同，
 * 若想调至最高频请将ccpu频率设为最高频+1
 */
int cpufreq_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	int target_profile = 0;
	int a9_freq = 0;
	int ddr_freq = 0;
	int slow_freq = 0;
	
	a9_freq = (a9freq < 0) ? (0) : (a9freq /CPUFREQ_ARGV_KHZ2MHZ);
	ddr_freq = (ddrfreq < 0) ? (0) : (ddrfreq /CPUFREQ_ARGV_KHZ2MHZ);
	slow_freq = (slowfreq < 0) ? (0) : (slowfreq /CPUFREQ_ARGV_KHZ2MHZ);
	
	target_profile = cpufreq_find_min_profile((u32)a9_freq, (u32)ddr_freq, (u32)slow_freq);
	cpufreq_debug("prolfie : %d\n", target_profile);
	cpufreq_dfs_set_limitprofile_with_voteid(target_profile, DIFF_MODE_OF_LT);
	return MDRV_OK;
}
/*
 * 获取当前频率 BSP_ERROR 设置失败;BSP_OK 设置成功
 * 
 */
int cpufreq_dfs_current(int *a9freq, int *ddrfreq, int *slowfreq)
{
	int cur_profile = 0;
	int ret = MDRV_OK;
	if ((a9freq != NULL) && (ddrfreq != NULL) && (slowfreq != NULL))
	{
		cur_profile = cpufreq_dfs_get_profile();
		*a9freq = (s32)balong_query_profile_table[cur_profile].cpu_frequency * CPUFREQ_ARGV_KHZ2MHZ;
		*ddrfreq = (s32)balong_query_profile_table[cur_profile].ddr_frequency * CPUFREQ_ARGV_KHZ2MHZ;
		*slowfreq = (s32)balong_query_profile_table[cur_profile].sbus_frequency * CPUFREQ_ARGV_KHZ2MHZ;
	}
	else
	{
		cpufreq_err("argv is NULL,check it\n");
		ret = MDRV_ERROR;
	}
	return ret;
}
/*通知M3是否锁定lock_flag=0:锁定M3调频，lock_flag=1:解锁m3调频 */
void cpufreq_lock_mcore_freq(bool lock_flag)
{
	struct cpufreq_msg set_msg = {0,0,0,0};
	if ((lock_flag != 0) && (lock_flag != 1))
	{
		cpufreq_err("argv is error\n");
		return ;
	}
	set_msg.msg_type = CPUFREQ_LOCK_MCORE_ACTION;
	set_msg.source = CPUFREQ_CCORE;
	set_msg.content = (u32)lock_flag;
	(void)cpufreq_driver_target(&set_msg);
}
void cpufreq_set_ddrfreq(int ddrfreq)
{
	struct cpufreq_msg set_msg = {CPUFREQ_SET_DDR_LIMIT, CPUFREQ_CCORE, 1, 0};
	set_msg.profile = (unsigned int)ddrfreq;
	if(g_cpufreq_core_ctrl.cdrx_dump_addr)
	{
		writel((unsigned int)ddrfreq, (unsigned)(g_cpufreq_core_ctrl.cdrx_dump_addr + CDRX_DUMP_CPUF_DDR_FREQ_ADDR));
	}
	(void)cpufreq_driver_target(&set_msg);
}

/*提供pm流程调用，设置最大频率CPU DDR*/
void cpufreq_set_max_freq(void)
{
	(void)cpufreq_dfs_set_profile(BALONG_FREQ_MAX);
	//cpufreq_set_ddrfreq(BALONG_FREQ_MAX_DDR);
}
/******************************for v9r1 adp start**********************************/

int cpufreq_qos_get_profile(int request_id, int request_freq)
{
	if (DFS_QOS_ID_CCPU_MINFREQ == request_id)
	{
		return cpufreq_get_ccore_profile(request_freq);
	}
	else if (DFS_QOS_ID_DDR_MINFREQ == request_id)
	{
		return cpufreq_get_ddr_profile(request_freq);
	}
	else if(DFS_QOS_ID_BUS_MINFREQ == request_id)
	{
        return cpufreq_get_bus_profile(request_freq);
	}
	else
	{
		cpufreq_err("request_id is right? %d\n", request_id);
		return BALONG_FREQ_MIN;
	}
}

void cpufreq_qos_update_request(int qos_id)
{
	unsigned long irqlock = 0;
	struct DFS_Qos_ST *qos_list = NULL;
	int target_profile = BALONG_FREQ_MIN;
	if (g_cpufreq_core_ctrl.g_cpufreq_is_sync_ddr)
	{

		local_irq_save(irqlock);
		list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
		{
			if (qos_list->request_profile >= target_profile)
			{
				target_profile = qos_list->request_profile;
			}
		}
		local_irq_restore(irqlock);
		cpufreq_dfs_set_limitprofile_with_voteid(target_profile, DIFF_MODE_OF_GU);
	}
	else
	{
		if (qos_id == DFS_QOS_ID_CCPU_MINFREQ) /*cpu请求，发送profile*/
		{
			local_irq_save(irqlock);
			list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
			{
				if ((qos_list->request_type == DFS_QOS_ID_CCPU_MINFREQ) && (qos_list->request_profile >= target_profile))
				{
					target_profile = qos_list->request_profile;
				}
			}
			local_irq_restore(irqlock);
			cpufreq_dfs_set_limitprofile_with_voteid(target_profile, DIFF_MODE_OF_GU);
		}
		else if (qos_id == DFS_QOS_ID_DDR_MINFREQ)/*ddr 请求，发送频率值*/
		{
			local_irq_save(irqlock);
			list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
			{
				if (qos_list->request_type == DFS_QOS_ID_DDR_MINFREQ)
				{
					target_profile += qos_list->request_profile;
				}
			}
			local_irq_restore(irqlock);
			cpufreq_set_ddrfreq(target_profile);
		}
		else if (qos_id == DFS_QOS_ID_BUS_MINFREQ)/*bus 请求，发送频率值*/
		{
			local_irq_save(irqlock);
			list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
			{
				if (qos_list->request_type == DFS_QOS_ID_BUS_MINFREQ)
				{
					target_profile += qos_list->request_profile;
				}
			}
			g_cpufreq_core_ctrl.g_bus_total_freq = target_profile;
			local_irq_restore(irqlock);
		}
	}
}


int cpufreq_find_rightid(int req_id)
{
	struct DFS_Qos_ST *qos_list = NULL;
	list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
	{
		if (req_id == qos_list->request_id)
		{
			return BSP_ERROR;
		}
	}
	return BSP_OK;
}
/*返回req_id用于表示投票组件g_last_req_id 从1开始*/
int cpufreq_qos_request_with_reqid(int qos_id, int request_freq)
{
	 /*lint --e{429 } */
	 int req_id = 0;
	 int taskid = 0;
	 unsigned long irqlock = 0;
	 int tar_profile = BALONG_FREQ_MIN;
	 struct DFS_Qos_ST *qos_request = NULL;	 
	 
 	 req_id = g_last_req_id + 1;
	 tar_profile = cpufreq_qos_get_profile(qos_id, request_freq);
	 qos_request = (struct DFS_Qos_ST *)osl_malloc(sizeof(struct DFS_Qos_ST));/* [false alarm]:误报 */
	 if (NULL == qos_request)
	 {
		cpufreq_err("request:malloc failed\n");
		return BSP_ERROR;
	 }
	taskid = osl_task_self();
 	local_irq_save(irqlock);
 	while((BSP_ERROR == cpufreq_find_rightid(req_id)))
 	{
		req_id = req_id + 1;
 	}
	qos_request->request_id = req_id;
	qos_request->request_type = qos_id;
	qos_request->request_profile = tar_profile;
	qos_request->request_flag = request_freq;
	qos_request->task_id = taskid;
	INIT_LIST_HEAD(&(qos_request->entry));
	list_add_tail(&(qos_request->entry), &(g_qos_list.entry));
	g_last_req_id = req_id;
	local_irq_restore(irqlock);
	/*pm om log*/
	cpufreq_pm_om_vote_log(qos_id, request_freq, taskid, req_id, tar_profile);

	return req_id;
}

void cpufreq_qos_release_with_reqid(int qos_id, int req_id)
{
	unsigned long irqlock = 0;
	struct DFS_Qos_ST *qos_list = NULL;
	struct DFS_Qos_ST *qos_release = NULL;
	local_irq_save(irqlock);
	list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
	{
		if (req_id == qos_list->request_id)
		{
			qos_release = qos_list;
			list_del(&(qos_list->entry));
			break;
		}
	}
 	local_irq_restore(irqlock);
	if(NULL != qos_release)
	{
		osl_free(qos_release);
	}
}
/*****************************************************************************
 函 数 名  : PWRCTRL_DfsQosRequest
 功能描述  : 请求DFS QoS
 输入参数  : qos_id - QoS ID
             					req_value - 请求值
 输出参数  : req_id - 请求ID
 返 回 值  : 		DFS_RET_OK - Success
 调用函数  :
 被调函数  :
*****************************************************************************/
int cpufreq_qos_request(int qos_id, unsigned int req_value, int* req_id)
{
    if(!req_id)
        return MDRV_ERROR;

    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MUDU_CPUFREQ, "qos_id:%d, req_value:%d\n", qos_id, req_value);

	*req_id = cpufreq_qos_request_with_reqid((int)qos_id, (int)req_value/1000);
	
	cpufreq_qos_update_request(qos_id);
    return MDRV_OK;
}


/*****************************************************************************
 函 数 名  : PWRCTRL_DfsQosRelease
 功能描述  : 释放DFS QoS
 输入参数  : qos_id - QoS ID
             req_id - 请求ID
 输出参数  : req_id = DFS_INVALID_ID if success
 返 回 值  : DFS_RET_OK - Success,
 调用函数  :
 被调函数  :
*****************************************************************************/
int cpufreq_qos_release(int qos_id, int* req_id)
{
	int req_release_id = 0;
    if(!req_id)
    {
        return MDRV_ERROR;
    }
    req_release_id = * req_id;
    cpufreq_err("qos_id:%d, req_id:%d\n", qos_id, *req_id);
    
	cpufreq_qos_release_with_reqid(qos_id, (int)req_release_id);

	cpufreq_qos_update_request(qos_id);
	
    *req_id = -1;

    return MDRV_OK;
}

/*****************************************************************************
 函 数 名  : PWRCTRL_DfsQosUpdate
 功能描述  : 更新DFS QoS
 输入参数  : qos_id - QoS ID
             req_id - 请求ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :
*****************************************************************************/
int cpufreq_qos_update(int qos_id, int req_id, unsigned int req_value)
{
	int taskid = 0;
	unsigned long irqlock = 0;
	struct DFS_Qos_ST *qos_list = NULL;
	
	bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MUDU_CPUFREQ,"qos_id:%d, req_value:%d, req_id:%d\n", qos_id, req_value, req_id);

	taskid = osl_task_self();
	cpufreq_debug("taskid:%x\n", taskid);
	local_irq_save(irqlock);
	list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
	{
		if (req_id == qos_list->request_id)
		{
			qos_list->request_profile = cpufreq_qos_get_profile((int)qos_id, (int)req_value/1000);
			qos_list->request_flag = (int)req_value/1000;
			qos_list->task_id = taskid;
			break;
		}
	}
    cpufreq_save_vote_info(qos_id, req_id, (int)req_value, taskid);
    local_irq_restore(irqlock);
    /*pm om log*/
	cpufreq_pm_om_vote_log(qos_id, (int)req_value, taskid, req_id, qos_list->request_profile);

    cpufreq_qos_update_request(qos_id);
    return MDRV_OK;
}

void cpufreq_print_vote_status(void)
{
	int total_ddr = 0;
	char *taskname = NULL;
	struct DFS_Qos_ST *qos_list = NULL;
	cpufreq_err("vote status:\n");
	list_for_each_entry(qos_list, &(g_qos_list.entry), entry)
	{
	    (void)osl_task_name_get(qos_list->task_id, &taskname);
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MUDU_CPUFREQ,"req id:%d, qos type:%d, req_value:%d ,taskid:0x%x, taskname:%s\n",
					qos_list->request_id, qos_list->request_type, qos_list->request_flag, qos_list->task_id, taskname);
		if (qos_list->request_type == DFS_QOS_ID_DDR_MINFREQ)
		{
			total_ddr += qos_list->request_profile;
		}
	}
	cpufreq_err("qos type 4 is ddr, 2 is cpu, total ddr:%d\n", total_ddr);
}

/******************************for v9r1 adp end**********************************/

/********************************adp interface start**************************************/
static PWRCTRLFUNCPTR cpufreq_ttf_flow_ctrl_cb = NULL;
void cpufreq_balong_flow_callback(void)
{
    PWRCTRLFUNCPTR pRoutine = NULL;
    unsigned int flowctrl_cpuload = 0;
    flowctrl_cpuload = cpufreq_cpu_load();
    if ((NULL != cpufreq_ttf_flow_ctrl_cb))
    {
		pRoutine = cpufreq_ttf_flow_ctrl_cb;
		(void)(*pRoutine)(flowctrl_cpuload);
	}
}
void cpufreq_ttf_get_cpuload_cb(PWRCTRLFUNCPTR pFunc)
{
	if (NULL == pFunc)
	{
	 cpufreq_err("BSP_PWRCTRL_FlowCtrlCallBackRegister param is Null,pls check\n");
	 return;
	}
	else
	{
	 cpufreq_ttf_flow_ctrl_cb = pFunc;
	}
}
void mdrv_pm_register_ccpuload_cb(PWRCTRLFUNCPTR pFunc )
{
	cpufreq_ttf_get_cpuload_cb(pFunc);
}
int mdrv_pm_get_ccpuload(unsigned int *ptrCCpuLoad)
{
	return MDRV_OK;
}
int mdrv_pm_dfs_qos_get(int qos_id, unsigned int req_value, int* req_id)
{
	return cpufreq_qos_request(qos_id, req_value, req_id);
}

int mdrv_pm_dfs_qos_put(int qos_id, int* req_id)
{
	return cpufreq_qos_release(qos_id, req_id);
}

int mdrv_pm_dfs_qos_update(int qos_id, int req_id, unsigned int req_value)
{
	return cpufreq_qos_update(qos_id, req_id, req_value);
}

 /*
 * 获取当前profile 范围
 */
 int mdrv_pm_get_dfs_profile_limit(struct mdrv_pm_profile *profile_limit)
{
	if (NULL == profile_limit)
	{
		return MDRV_ERROR;
	}
	profile_limit->max_profile = (unsigned int)BALONG_FREQ_MAX;
	profile_limit->min_profile = (unsigned int)BALONG_FREQ_MIN;
	return MDRV_OK;
}
int mdrv_pm_get_dfs_profile(void)
{
	return cpufreq_dfs_get_profile();
}

int mdrv_pm_set_dfs_profile(int profile)
{
	return cpufreq_dfs_set_profile(profile);
}

int mdrv_pm_set_dfs_baseprofile(int profile)
{
	return cpufreq_dfs_set_baseprofile(profile);
}

void mdrv_pm_lock_dfs(unsigned int lock)
{
	cpufreq_dfs_lock(lock);
}

int mdrv_pm_set_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return	cpufreq_dfs_target(a9freq, ddrfreq, slowfreq);
}
/********************************new interface end ***********************************/

void cpufreq_api_init(void)
{
    INIT_LIST_HEAD(&(g_qos_list.entry));
}
#ifdef __cplusplus
}
#endif


