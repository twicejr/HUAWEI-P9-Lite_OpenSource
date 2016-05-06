/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  bbp_pmu.c
*
*   作    者 :  xuwenfang 00195528
*
*   描    述 :  bbp & pmu 解析主流程
*
*   修改记录 : 2015年01月05日  v1.00  x00195528  创建
**************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "bbp_pmu.h"

char *g_bbpaction_obj[] = {
	"power_on",
    "power_off",
	"clk_on",
    "clk_off",
    "pll_on",
    "pll_off",
	"others",
};
/*与枚举保持一致*/
char *g_module_obj[] = {
	"module_pa",
    "module_rf",
	"module_abb",
    "module_bbe",
    "module_bbpdrx",
    "module_bbpdpa",
	"module_bbpmem",
	"module_butt",
};
char *g_mode_obj[] = {
	"mode_gsm",
    "mode_wcdma",
	"mode_lte",
    "mode_tds",
    "mode_cdma",
    "mode_cdma_res",
	"mode_butt",
};
char *g_modem_obj[] = {
	"modem0",
    "modem1",
	"modem2",
    "modem_butt",
};
char *g_channel_obj[] = {
	"channel0",
    "channel1",
	"channel_butt",
};

char *g_pwc_obj[][7]={
    {
        "pwr_irm",
        "pwr_lte",
        "pwr_tw",
        "pwr_w",
        "pwr_g1",
        "pwr_g2",
        "pwr_butt",
    },
    {
        "clk_ao",
        "clk_comm",
        "clk_lte",
        "clk_tw_w61m",
        "clk_tw_t122m",
        "clk_tw_t245m",
    },
    {
        "pll",
    },
    {
        "others"
    },
};

char *g_pmuaction_obj[] = {
	"pmu_enable",
    "pmu_disable",
	"pmu_is_enabled",
    "pmu_set_volt",
    "pmu_get_volt",
    "pmu_set_curr",
    "pmu_get_curr",
	"others",
};

int bbp_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    int data_len = 0;
	struct bbp_pwc_infolog *info_log_msg = (struct bbp_pwc_infolog *)in_buf;
    struct bbp_pwc_actlog  *act_log_msg = (struct bbp_pwc_actlog *)in_buf;

	if (BBP_LOG_INFO == typeid)
	{
        /* step1: 消息类型检查 */
    	if(len != sizeof(*info_log_msg))
    	{
    		return PMOM_ERR;
    	}
        /* step2: 格式化消息到out_buf: 以回车结束 */
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"task_id:0x%x, ops:0x%x-%s, module_id:%d, modem_id:%d, mode_id:%d!\n", info_log_msg->task_id,
				info_log_msg->ops_id,g_bbpaction_obj[info_log_msg->ops_id],
				info_log_msg->act_module,info_log_msg->act_modem,info_log_msg->act_mode);
		*out_ptr = *out_ptr + data_len;

	}
	else if(BBP_LOG_ACTUAL== typeid)
	{
		/* step1: 消息类型检查 */
    	if(len != sizeof(*act_log_msg))
    	{
    		return PMOM_ERR;
    	}
        /* step2: 格式化消息到out_buf: 以回车结束 */
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"task_id:0x%x, ops:0x%x-%s, %d-%s, %d-%s, %d-%s, %d-%s, vote:0x%llx!\n", act_log_msg->task_id,
				act_log_msg->ops_id,g_bbpaction_obj[act_log_msg->ops_id],
				act_log_msg->act_module,g_module_obj[act_log_msg->act_module],
				act_log_msg->act_modem,g_modem_obj[act_log_msg->act_modem],
				act_log_msg->act_mode,g_mode_obj[act_log_msg->act_mode],
				act_log_msg->pwc_id, g_pwc_obj[act_log_msg->ops_id/2][act_log_msg->pwc_id],
				act_log_msg->vote_lock);
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}

	return PMOM_OK;
}
int pmu_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    int data_len = 0;
	struct pmu_pmom_log *log_msg = (struct pmu_pmom_log *)in_buf;

    /* step1: 消息类型检查 */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}
    /* step2: 格式化消息到out_buf: 以回车结束 */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
			"task_id:0x%x, ops:0x%x-%s, volt_id:%d!\n", log_msg->task_id,log_msg->ops_id,
			g_pmuaction_obj[log_msg->ops_id], log_msg->volt_id);
	*out_ptr = *out_ptr + data_len;

    return PMOM_OK;
}
