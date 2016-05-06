#include <pwrctrl_multi_dfs.h>
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_dfs.h>
#include <mach/pwrctrl/pwrctrl_mca.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/pm_qos_params.h>
#include <mali_balong_pmm.h>
#include "soc_ao_sctrl_interface.h"
#if defined(CHIP_BB_HI6210)
#include"soc_peri_sctrl_interface.h"
#endif
#define PWRCTRL_DFS_CMD_TIMEOUT 100
/* CPU 当前频率值保存,避免频繁发消息获取 0-3字节:acpu 4-7字节:DDR 8-11字节:GPU*/
#define MEM_CUR_FREQ_ADDR           (IO_ADDRESS(MEMORY_AXI_CUR_FREQ_ADDR))


local_t s32_t bus150M_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t bus150M_minfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t bus100M_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t bus100M_minfreq_qos_req_id = DFS_INVALID_ID;


/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_rqqos
 功能描述  : 请求DFS QoS
 输入参数  : qos_id - QoS ID
             req_value - 请求值
 输出参数  : req_id - 请求ID
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : 黄星宇 212111
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_rqqos(s32_t qos_id, u32_t req_value, s32_t* req_id)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    printk(KERN_NOTICE "%s qos_id:%d req_value:%d\n", __FUNCTION__, qos_id, req_value);
    if(!req_id)
        return RET_ERR_PARAM_NULL;

    req.dfs_rqqos_req.qos_id    = qos_id;
    req.dfs_rqqos_req.req_value = req_value;

    if(mca_send(MCA_CMD_DFS_RQQOS, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;

    if(0 == rsp.dfs_rqqos_rsp.ret)
    {
        *req_id = rsp.dfs_rqqos_rsp.req_id;
    }

    printk(KERN_NOTICE "%s req_id:%d\n", __FUNCTION__, rsp.dfs_rqqos_rsp.req_id);

    return rsp.dfs_rqqos_rsp.ret;
}

/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_set_policy
 功能描述  : 设置DFS QoS policy
 输入参数  : policy_id - policy ID
             policy_buf - policy buffer
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_set_policy(s32_t policy_id, void *policy_buf, unsigned int len)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    if(len > POLICY_MAX_TOTAL_SIZE)
    {
        printk(KERN_ERR "%s policy_id:%d len:%d exceed max value(%d) error!!!\n", __FUNCTION__, policy_id, len, POLICY_MAX_TOTAL_SIZE);
        return -1;
    }
    
    printk(KERN_NOTICE "%s policy_id:%d len:%d\n", __FUNCTION__, policy_id, len);

    req.dfs_setpli_req.policy_id = policy_id;
    memcpy(req.dfs_setpli_req.pli_buf, policy_buf, len);

    if(mca_send(MCA_CMD_DFS_SETPLI, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;

    printk(KERN_NOTICE "%s ret:%d\n", __FUNCTION__, rsp.dfs_setpli_rsp.ret);
    return rsp.dfs_setpli_rsp.ret;
}

int acpu_set_policy_handle(void *policy, unsigned int len)
{
    return pwrctrl_dfs_cmd_set_policy(DFS_POLICY_ID_ACPU, policy, len);
}

int gpu_set_policy_handle(void *policy, unsigned int len)
{
    //return pwrctrl_dfs_cmd_set_policy(DFS_POLICY_ID_GPU, policy, len);
    /*stub*/
    return -1;
}

int ddr_set_policy_handle(void *policy, unsigned int len)
{
    return pwrctrl_dfs_cmd_set_policy(DFS_POLICY_ID_DDR, policy, len);
}

/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_set_profile
 功能描述  : 设置DFS QoS profile
 输入参数  : policy_id - policy ID
             policy_buf - policy buffer
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_set_profile(s32_t dev_id, void *profile_buf, unsigned int len)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    if(len > PROFILE_MAX_TOTAL_SIZE)
    {
        printk(KERN_ERR "%s dev_id:%d len:%d exceed max value(%d) error!!!\n", __FUNCTION__, dev_id, len, PROFILE_MAX_TOTAL_SIZE);
        return -1;
    }
    
    printk(KERN_NOTICE "%s dev_id:%d len:%d\n", __FUNCTION__, dev_id, len);
    req.dfs_set_prof_req.dev_id = dev_id;
    memcpy(req.dfs_set_prof_req.prof_buf, profile_buf, len);

    if(mca_send(MCA_CMD_DFS_SETPROFILE, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;
    printk(KERN_NOTICE "%s ret:%d\n", __FUNCTION__, rsp.dfs_set_prof_rsp.ret);
    return rsp.dfs_set_prof_rsp.ret;
}

int acpu_set_profile_handle(void *profile, unsigned int len)
{
    return pwrctrl_dfs_cmd_set_profile(DFS_DEVICE_ID_ACPU, profile, len);
}

int gpu_set_profile_handle(void *profile, unsigned int len)
{
    //return pwrctrl_dfs_cmd_set_profile(DFS_DEVICE_ID_GPU, profile, len);
    /*stub*/
    return -1;
}

int ddr_set_profile_handle(void *profile, unsigned int len)
{
    return pwrctrl_dfs_cmd_set_profile(DFS_DEVICE_ID_DDR, profile, len);
}

/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_lock
 功能描述  : 锁频DFS QoS
 输入参数  : dev_id - Dev ID
             prof_id - profile ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_lock(s32_t dev_id, u32_t prof_id)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    printk(KERN_NOTICE "%s dev_id:%d prof_id:%d\n", __FUNCTION__, dev_id, prof_id);
    req.dfs_lock_req.dev_id = dev_id;
    req.dfs_lock_req.prof_id = prof_id;

    if(mca_send(MCA_CMD_DFS_LOCK, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;
    printk(KERN_NOTICE "%s ret:%d\n", __FUNCTION__, rsp.dfs_lock_rsp.ret);
    return rsp.dfs_lock_rsp.ret;
}


/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_unlock
 功能描述  : 解锁频DFS QoS
 输入参数  : dev_id - Dev ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_unlock(s32_t dev_id)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    printk(KERN_NOTICE "%s dev_id:%d\n", __FUNCTION__, dev_id);
    req.dfs_unlock_req.dev_id = dev_id;

    if(mca_send(MCA_CMD_DFS_UNLOCK, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;

    printk(KERN_NOTICE "%s ret:%d\n", __FUNCTION__, rsp.dfs_unlock_rsp.ret);
    return rsp.dfs_unlock_rsp.ret;
}

int acpu_lockfreq_handle( u32_t prof_id)
{
    if(UNLOCK_PROFILE == prof_id) {
        return pwrctrl_dfs_cmd_unlock(DFS_DEVICE_ID_ACPU);
    } else {
        return pwrctrl_dfs_cmd_lock(DFS_DEVICE_ID_ACPU,  prof_id);
    }
}

int gpu_lockfreq_handle( u32_t prof_id)
{
#if 0
    if(UNLOCK_PROFILE == prof_id) {
        pmqos_gpu_dfs_unlock();
    } else {
        pmqos_gpu_dfs_lock(prof_id);
    }
#endif
    return 0;
}

int ddr_lockfreq_handle( u32_t prof_id)
{
    if(UNLOCK_PROFILE == prof_id) {
        return pwrctrl_dfs_cmd_unlock(DFS_DEVICE_ID_DDR);
    } else {
        return pwrctrl_dfs_cmd_lock(DFS_DEVICE_ID_DDR,  prof_id);
    }
}


/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_current
 功能描述  : 锁频DFS QoS
 输入参数  : dev_id - Dev ID
             prof_id - profile ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_current(s32_t dev_id, u32_t *prof_id)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    PRINT_PWC_DBG(PWC_SWITCH_DEBPT, "%s dev_id:%d\n", __FUNCTION__, dev_id);
    req.dfs_current_req.dev_id = dev_id;

    if(mca_send(MCA_CMD_DFS_CURRENT, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;

    *prof_id = rsp.dfs_current_rsp.prof_id;

    PRINT_PWC_DBG(PWC_SWITCH_DEBPT, "%s prof_id:%d ret:%d\n", __FUNCTION__, *prof_id, rsp.dfs_current_rsp.ret);
    return rsp.dfs_current_rsp.ret;
}

dfs_ret acpu_cur_profile_handle(u32_t *prof_id)
{
    /*return pwrctrl_dfs_cmd_current(DFS_DEVICE_ID_ACPU, prof_id);*/
    *prof_id = *(unsigned int*)MEM_CUR_FREQ_ADDR;
    return 0;	
}

dfs_ret gpu_cur_profile_handle(u32_t *prof_id)
{
#if 0
    pmqos_gpu_dfs_get_current_profile(prof_id);
#endif
    return 0;
}


dfs_ret ddr_cur_profile_handle(u32_t *prof_id)
{
   /*return pwrctrl_dfs_cmd_current(DFS_DEVICE_ID_DDR, prof_id);*/
   *prof_id = *(unsigned int*)(MEM_CUR_FREQ_ADDR+4);
   return 0;
}

/*DVFS功能开关变量*/
volatile ST_PWC_SWITCH_STRU * g_stPwcSwitch = NULL;

int get_pwc_switch_value(unsigned int object, unsigned int *func)
{
    int ret = 0;
    unsigned int local_func = 0;

    if(NULL == g_stPwcSwitch)
    {
        return PWC_FUNC_INVALID;
    }

    printk(KERN_NOTICE "%s object:%d status:0x%x\n", __FUNCTION__, object, *(unsigned int*)g_stPwcSwitch);

    if (MCA_OBJ_CPU == object) {
		if(g_stPwcSwitch->aAvs)
		{
            local_func = PWC_FUNC_AVS_ENABLE;
		}

		if(g_stPwcSwitch->aDfs)
		{
            local_func |= PWC_FUNC_DFS_ENABLE;
		}
	} else if (MCA_OBJ_GPU == object) {
		if(g_stPwcSwitch->gAvs)
		{
            local_func = PWC_FUNC_AVS_ENABLE;
		}

		if(g_stPwcSwitch->gDfs)
		{
            local_func |= PWC_FUNC_DFS_ENABLE;
		}
	} else if (MCA_OBJ_DDR == object) {
		if(g_stPwcSwitch->dAvs)
		{
            local_func = PWC_FUNC_AVS_ENABLE;
		}

		if(g_stPwcSwitch->dDfs)
		{
            local_func |= PWC_FUNC_DFS_ENABLE;
		}
	}
	else if(MCA_OBJ_BUS == object){
        if(g_stPwcSwitch->bDfs)
        {
            local_func = PWC_FUNC_DFS_ENABLE;
        }
	}


    if(0 == local_func)
    {
        local_func = PWC_FUNC_DVFS_DISABLE;
    }

    *func = local_func;

    printk(KERN_NOTICE "%s ret:%d func:0x%x\n", __FUNCTION__, ret, *func);

	return ret;

}

void test_get_pwc_value(unsigned int object)
{
    unsigned int func = 0;
    int ret = 0;

    ret = get_pwc_switch_value(object, &func);

    printk("ret:%d func:0x%x\n", ret, func);
}
int acpu_get_func_handle(unsigned int *func)
{
    return get_pwc_switch_value(MCA_OBJ_CPU, func);
}

int gpu_get_func_handle(unsigned int *func)
{
#if 0
    pmqos_gpu_get_current_func(func);
#endif
    return 0;
}

int ddr_get_func_handle(unsigned int *func)
{
    return get_pwc_switch_value(MCA_OBJ_DDR, func);
}

int bus_get_func_handle(unsigned int *func)
{
    return get_pwc_switch_value(MCA_OBJ_BUS, func);
}

int set_pwc_switch_value(unsigned int object, unsigned int func)
{
    int ret = 0;

    if(NULL == g_stPwcSwitch)
    {
        return PWC_FUNC_INVALID;
    }

    printk(KERN_NOTICE "%s object:%d func:0x%x status:0x%x\n", __FUNCTION__, object,
        func, *(unsigned int *)g_stPwcSwitch);

    if (MCA_OBJ_CPU == object) {
		if(func & PWC_FUNC_AVS_ENABLE)
		{
            g_stPwcSwitch->aAvs = 1;
		}

		if(func & PWC_FUNC_DFS_ENABLE)
		{
            g_stPwcSwitch->aDfs = 1;
		}

        if(func & PWC_FUNC_DVFS_ENABLE)
		{
            g_stPwcSwitch->aDfs = 1;
            g_stPwcSwitch->aAvs = 1;
		}

		if(func & PWC_FUNC_DVFS_DISABLE)
		{
		    g_stPwcSwitch->aAvs = 0;
            g_stPwcSwitch->aDfs = 0;
		}
	} else if (MCA_OBJ_GPU == object) {
		if(func & PWC_FUNC_AVS_ENABLE)
		{
            g_stPwcSwitch->gAvs = 1;
		}

		if(func & PWC_FUNC_DFS_ENABLE)
		{
            g_stPwcSwitch->gDfs = 1;
		}

        if(func & PWC_FUNC_DVFS_ENABLE)
		{
            g_stPwcSwitch->gDfs = 1;
            g_stPwcSwitch->gAvs = 1;
		}

		if(func & PWC_FUNC_DVFS_DISABLE)
		{
		    g_stPwcSwitch->gAvs = 0;
            g_stPwcSwitch->gDfs = 0;
		}
	} else if (MCA_OBJ_DDR == object) {
		if(func & PWC_FUNC_AVS_ENABLE)
		{
            g_stPwcSwitch->dAvs = 1;
		}

		if(func & PWC_FUNC_DFS_ENABLE)
		{
            g_stPwcSwitch->dDfs = 1;
		}

        if(func & PWC_FUNC_DVFS_ENABLE)
		{
            g_stPwcSwitch->dDfs = 1;
            g_stPwcSwitch->dAvs = 1;
		}

		if(func & PWC_FUNC_DVFS_DISABLE)
		{
		    g_stPwcSwitch->dAvs = 0;
            g_stPwcSwitch->dDfs = 0;
		}
	}
	else if(MCA_OBJ_BUS == object){
        if(func & PWC_FUNC_DFS_ENABLE)
        {
            g_stPwcSwitch->bDfs = 1;
        }
        if(func & PWC_FUNC_DFS_DISABLE)
        {
            g_stPwcSwitch->bDfs = 0;
        }

        if(func & PWC_FUNC_DVFS_ENABLE)
		{
            g_stPwcSwitch->bDfs = 1;
		}

		if(func & PWC_FUNC_DVFS_DISABLE)
		{
		    g_stPwcSwitch->bDfs = 0;
		}
	}

    printk(KERN_NOTICE "%s new status:0x%x\n", __FUNCTION__, *(unsigned int *)g_stPwcSwitch);
	return ret;

}

int acpu_set_func_handle(unsigned int func)
{
    return set_pwc_switch_value(MCA_OBJ_CPU, func);
}

int gpu_set_func_handle(unsigned int func)
{
#if 0
    pmqos_gpu_set_current_func(func);
#endif
    return 0;
}

int ddr_set_func_handle(unsigned int func)
{
    return set_pwc_switch_value(MCA_OBJ_DDR, func);
}

int bus_set_func_handle(unsigned int func)
{
    return set_pwc_switch_value(MCA_OBJ_BUS, func);
}

/*****************************************************************************

 函 数 名  : pwrctrl_dfs_cmd_rlqos
 功能描述  : 释放DFS QoS
 输入参数  : qos_id - QoS ID
             req_id - 请求ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : 黄星宇 212111
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_rlqos(s32_t qos_id, s32_t* req_id)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    if(!req_id)
        return RET_ERR_PARAM_NULL;

    printk(KERN_NOTICE "%s qos_id:%d req_id:%d\n", __FUNCTION__, qos_id, *req_id);
    req.dfs_rlqos_req.qos_id = qos_id;
    req.dfs_rlqos_req.req_id = *req_id;

    if(mca_send(MCA_CMD_DFS_RLQOS, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
    {
        *req_id = DFS_INVALID_ID;
        printk(KERN_NOTICE "%s error!!! mailbox timeout req_id:%d\n", __FUNCTION__, *req_id);
        return RET_ERR_CONNECT_FAIL;
    }

    *req_id = rsp.dfs_rlqos_rsp.req_id;

    printk(KERN_NOTICE "%s req_id:%d ret:%d\n", __FUNCTION__, *req_id, rsp.dfs_rlqos_rsp.ret);
    return rsp.dfs_rlqos_rsp.ret;
}

/*****************************************************************************
 函 数 名  : pwrctrl_dfs_cmd_udqos
 功能描述  : 更新DFS QoS
 输入参数  : qos_id - QoS ID
             req_id - 请求ID
 输出参数  : 无
 返 回 值  : DFS_RET_OK - Success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : 黄星宇 212111
    修改内容   : 新生成函数

*****************************************************************************/
local_t dfs_ret pwrctrl_dfs_cmd_udqos(s32_t qos_id, s32_t req_id, u32_t req_value)
{
    union mca_udata_req req = {0};
    union mca_udata_rsp rsp = {0};

    printk(KERN_NOTICE "%s qos_id:%d req_id:%d req_value:%d\n", __FUNCTION__,
        qos_id, req_id, req_value);
    req.dfs_udqos_req.qos_id    = qos_id;
    req.dfs_udqos_req.req_id    = req_id;
    req.dfs_udqos_req.req_value = req_value;

    if(mca_send(MCA_CMD_DFS_UDQOS, req, &rsp, PWRCTRL_DFS_CMD_TIMEOUT))
        return RET_ERR_CONNECT_FAIL;
    printk(KERN_NOTICE "%s ret:%d\n", __FUNCTION__, rsp.dfs_udqos_rsp.ret);
    return rsp.dfs_udqos_rsp.ret;
}

local_t int dfs_qos_update(s32_t qos_id, s32_t* req_id, u32_t req_value)
{
    if(req_value == PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE) {
        if(*req_id == DFS_INVALID_ID)
            return RET_OK;
        else
            return pwrctrl_dfs_cmd_rlqos(qos_id, req_id);
    } else {
        if(*req_id == DFS_INVALID_ID)
            return pwrctrl_dfs_cmd_rqqos(qos_id, req_value, req_id);
        else
            return pwrctrl_dfs_cmd_udqos(qos_id, *req_id, req_value);
    }
}

local_t s32_t ddr_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t ddr_minfreq_qos_req_id = DFS_INVALID_ID;

int ddr_minfreq_handle(unsigned int req_value)
{
    return dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ, &ddr_minfreq_qos_req_id, req_value);
}

local_t int ddr_minfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ, &ddr_minfreq_qos_req_id, req_value);
}

int ddr_maxfreq_handle(unsigned int req_value)
{
    return dfs_qos_update(DFS_QOS_ID_DDR_MAXFREQ, &ddr_maxfreq_qos_req_id, req_value);
}

local_t int ddr_maxfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_DDR_MAXFREQ, &ddr_maxfreq_qos_req_id, req_value);
}

local_t struct notifier_block ddr_minfreq_notifier = {
    .notifier_call = ddr_minfreq_notify,
};

local_t struct notifier_block ddr_maxfreq_notifier = {
    .notifier_call = ddr_maxfreq_notify,
};

local_t s32_t acpu_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t acpu_minfreq_qos_req_id = DFS_INVALID_ID;

local_t s32_t gpu_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t gpu_minfreq_qos_req_id = DFS_INVALID_ID;

int acpu_minfreq_handle(unsigned int req_value)
{
    return dfs_qos_update(DFS_QOS_ID_ACPU_MINFREQ, &acpu_minfreq_qos_req_id, req_value);
}

/*acore bus dfs handle*/
int bus_minfreq_handle(unsigned int req_value)
{
    /*get dfs switch flag*/
    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_BDFS))
    {
        return RET_ERR;
    }

    if(DFS_BUS_FREQ_MIN >= req_value)
    {
        /*set SC_MCU_VOTE2DIS0 bit,vote lock,enable bus dfs*/
#if defined(CHIP_BB_HI6210) /*B020 Modify*/
	pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2DIS_ADDR(SOC_AO_SCTRL_BASE_ADDR)), BIT(BUS_DFS_BIT_ACPU));
#else
        pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_ADDR(SOC_SC_ON_BASE_ADDR)), BIT(BUS_DFS_BIT_ACPU));
#endif
    }
    else
    {
        /*set SC_MCU_VOTE2EN0 bit,vote unlock,disable bus dfs*/
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
		pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2EN_ADDR(SOC_AO_SCTRL_BASE_ADDR)), BIT(BUS_DFS_BIT_ACPU));
#else
        pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2EN0_ADDR(SOC_SC_ON_BASE_ADDR)), BIT(BUS_DFS_BIT_ACPU));
#endif
    }
    return RET_OK;

}
int bus_maxfreq_handle(unsigned int req_value)
{
    return 0;
}
int bus_lockfreq_handle(unsigned int req_value)
{
    return 0;
}
int bus_safefreq_handle(unsigned int req_value)
{
    return 0;
}

int gpu_minfreq_handle(unsigned int req_value)
{
#if 0
    pmqos_gpu_dfs_limit_min(req_value);
#endif
    return 0;
}

local_t int acpu_minfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_ACPU_MINFREQ, &acpu_minfreq_qos_req_id, req_value);
}

int acpu_safefreq_handle(unsigned int freq)
{
    return dfs_qos_update(DFS_QOS_ID_ACPU_MAXFREQ, &acpu_maxfreq_qos_req_id, freq);
}

int gpu_safefreq_handle(unsigned int freq)
{
    //return dfs_qos_update(DFS_QOS_ID_GPU_MAXFREQ, &gpu_maxfreq_qos_req_id, freq);
    /*stub*/
    return -1;
}

int ddr_safefreq_handle(unsigned int freq)
{
    return dfs_qos_update(DFS_QOS_ID_DDR_MAXFREQ, &ddr_maxfreq_qos_req_id, freq);
}

int acpu_maxfreq_handle(unsigned int req_value)
{
    return dfs_qos_update(DFS_QOS_ID_ACPU_MAXFREQ, &acpu_maxfreq_qos_req_id, req_value);
}

int gpu_maxfreq_handle(unsigned int req_value)
{
#if 0
    pmqos_gpu_dfs_limit_max(req_value);
#endif
    return 0;
}
local_t int acpu_maxfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_ACPU_MAXFREQ, &acpu_maxfreq_qos_req_id, req_value);
}

local_t struct notifier_block acpu_minfreq_notifier = {
    .notifier_call = acpu_minfreq_notify,
};

local_t struct notifier_block acpu_maxfreq_notifier = {
    .notifier_call = acpu_maxfreq_notify,
};

/*
*V8R1B050 新增两组bus调频, 100M和150M
**/
local_t int bus150M_minfreq_notify(struct notifier_block *b, unsigned long req_value, void *v)
{
    return dfs_qos_update(DFS_QOS_ID_BUS150M_MINFREQ, &bus150M_minfreq_qos_req_id, req_value);
}

local_t int bus150M_maxfreq_notify(struct notifier_block *b, unsigned long req_value, void *v)
{
    return dfs_qos_update(DFS_QOS_ID_BUS150M_MAXFREQ, &bus150M_maxfreq_qos_req_id, req_value);
}

local_t struct notifier_block bus150M_minfreq_notifier = {
    .notifier_call = bus150M_minfreq_notify,
};

local_t struct notifier_block bus150M_maxfreq_notifier = {
    .notifier_call = bus150M_maxfreq_notify,
};

local_t int bus100M_minfreq_notify(struct notifier_block *b, unsigned long req_value, void *v)
{
    return dfs_qos_update(DFS_QOS_ID_BUS100M_MINFREQ, &bus100M_minfreq_qos_req_id, req_value);
}

local_t int bus100M_maxfreq_notify(struct notifier_block *b, unsigned long req_value, void *v)
{
    return dfs_qos_update(DFS_QOS_ID_BUS100M_MAXFREQ, &bus100M_maxfreq_qos_req_id, req_value);
}

local_t struct notifier_block bus100M_minfreq_notifier = {
    .notifier_call = bus100M_minfreq_notify,
};

local_t struct notifier_block bus100M_maxfreq_notifier = {
    .notifier_call = bus100M_maxfreq_notify,
};


#if 0
local_t s32_t gpu_maxfreq_qos_req_id = DFS_INVALID_ID;
local_t s32_t gpu_minfreq_qos_req_id = DFS_INVALID_ID;

local_t int gpu_minfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_GPU_MINFREQ, &gpu_minfreq_qos_req_id, req_value);
}

local_t int gpu_maxfreq_notify(struct notifier_block *b, unsigned long req_value,    void *v)
{
    return dfs_qos_update(DFS_QOS_ID_GPU_MAXFREQ, &gpu_maxfreq_qos_req_id, req_value);
}

local_t struct notifier_block gpu_minfreq_notifier = {
    .notifier_call = gpu_minfreq_notify,
};

local_t struct notifier_block gpu_maxfreq_notifier = {
    .notifier_call = gpu_maxfreq_notify,
};
#endif

int pwrctrl_dfs_init(void)
{
     unsigned int sys_off_addr;

     sys_off_addr = IO_ADDRESS(SOC_PERI_SCTRL_BASE_ADDR);
#if defined(CHIP_BB_HI6210)
     g_stPwcSwitch = (ST_PWC_SWITCH_STRU *)SOC_PERI_SCTRL_SC_RESERVED8_ADDR(sys_off_addr);
#else
	g_stPwcSwitch = (ST_PWC_SWITCH_STRU *)SOC_PERI_SCTRL_SC_RESERVED8_ADDR(sys_off_addr);
#endif

#if 0
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_DDR_MINFREQ, &ddr_minfreq_notifier) < 0);
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_DDR_MAXFREQ, &ddr_maxfreq_notifier) < 0);
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_ACPU_MINFREQ, &acpu_minfreq_notifier) < 0);
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_ACPU_MAXFREQ, &acpu_maxfreq_notifier) < 0);
#endif
    #if 0
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_GPU_MINFREQ, &gpu_minfreq_notifier) < 0);
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_GPU_MAXFREQ, &gpu_maxfreq_notifier) < 0);
    #endif

    return RET_OK;
}

#if 0
int pwrctrl_dfs_gpu_target(int step)
{
}
#endif
