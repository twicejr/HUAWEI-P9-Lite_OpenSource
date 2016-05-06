/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_regulator.h
*
*   作    者 :  yangqiang 221789
*
*   描    述 :  cpufreq & regulator 解析主流程
*
*   修改记录 : 2014年12月27日  v1.00  y00221789  创建
**************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "cpufreq_regulator.h"
char *g_req_obj[] = {
	"\0",
	"\0",
	"cpu_limit",
	"\0",
	"ddr_limit",
	"\0",
	"\0",
	"\0",
	"bus_limit",
};
char *g_source_obj[] = {
	"acore",
	"ccore",
};
char *g_action_obj[] = {
	"up pro to",
	"up pro to",
	"down pro to",
	"down pro to",
	"limit min pro to",
	"limit max pro to",
	"limit min ddr to"
};
int cpufreq_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct cpufreq_debug_msg *icc_log = NULL;
	struct cpufreq_pm_om_qos_log *vote_log = NULL;

	/* step1: 消息类型检查 */
	if((len != sizeof(struct cpufreq_pm_om_qos_log)) &&  (len != sizeof(struct cpufreq_debug_msg)))
	{
		return PMOM_ERR;
	}

	/* step2: 格式化消息到out_buf: 以回车结束 */
	if (CPUFREQ_VOTE_LOG == typeid)
	{
		vote_log = (struct cpufreq_pm_om_qos_log *)in_buf;
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task_id:0x%x, qos_id:0x%x, %s, req:%d KHZ, ack:%d(pro)\n", vote_log->taskid, vote_log->qos_id, 
				g_req_obj[vote_log->req_id], vote_log->req_value, vote_log->req_true_value); 
		*out_ptr = *out_ptr + data_len;
	}
	else if (CPUFREQ_ICC_LOG == typeid)
	{
		icc_log = (struct cpufreq_debug_msg *)in_buf;
		if((unsigned int)CPUFREQ_DDR_LIMIT_MSG == icc_log->msg_type)
			icc_log->content = icc_log->msg_type;
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task_id:0x%x, %s, cur pro:%d and want %s:%d, cur load:%d\n", icc_log->taskid , g_source_obj[icc_log->source], 
				icc_log->cur_profile, g_action_obj[icc_log->content], icc_log->target_profile, icc_log->cur_load); 
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}

	return PMOM_OK;
}
char *g_regu_ops[] = {
	"enable",
	"disable",
	"isenabled",
	"get volt",
	"set volt",
};
char *g_mtcmos_status[] = {
	"open",
	"close",
};
int regulator_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	int status = 0;
	struct regulator_pm_om_log *regu_log = NULL;
	struct mtcmos_pm_om_log *mtcmos_log = NULL;
	if(len != sizeof(struct regulator_pm_om_log) && (len != sizeof(struct mtcmos_pm_om_log)))
	{
		return PMOM_ERR;
	}
	if (REGULATOR_TYPE == typeid)
	{
		regu_log = (struct regulator_pm_om_log *)in_buf;
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task_id:0x%x, action:%s->id:%d(%s), use count:%d\n", regu_log->task_id, g_regu_ops[regu_log->ops_id], 
				regu_log->regulator_id, regu_log->pmutype, regu_log->use_count); 
		*out_ptr = *out_ptr + data_len;
	}
	else if (MTCMOS_TYPE == typeid)
	{
		mtcmos_log = (struct mtcmos_pm_om_log *)in_buf;
		if (mtcmos_log->status)
		{
			status = 1;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"mtcmos: action:%s->mtcmos id:%d's status:%s, buck3 status:%s\n", g_regu_ops[mtcmos_log->ops], mtcmos_log->mtcmos_id, 
				g_mtcmos_status[status], g_mtcmos_status[mtcmos_log->buck3_flag]); 
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}
	return PMOM_OK;
}
