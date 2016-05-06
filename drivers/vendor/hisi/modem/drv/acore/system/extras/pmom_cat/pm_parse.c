/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  pm_parse.c
*
*   作    者 :  lixiaojie 00227190
*
*   描    述 :  pm 解析主流程
*
*   修改记录 : 2015年1月6日  v1.00  l00227190  创建
**************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "pm_parse.h"
char *g_pm_set_wakesrc_obj[] = {
	"WAKE_SRC_UART0 ", /*for acore at_uart*/
	"WAKE_SRC_SOCP" ,     /*for acore sd_log*/
	"WAKE_SRC_DRX_TIMER", /*for ccore drx timer*/
};
char *g_pm_set_waketype_obj[] = {
	"TYPE_ACORE_SLEEP",
	"TYPE_ACORE_WAKE",
	"TYPE_CCORE_SLEEP",
	"TYPE_CCORE_WAKE",
	"TYPE_ASET_WSRC",
	"TYPE_CSET_WSRC",
	"TYPE_AUNSET_WSRC",
	"TYPE_CUNSET_WSRC",
};


int pm_msg_parse_acore(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct pm_info_acore *log_msg = (struct pm_info_acore *)in_buf;

	/* step1: 消息类型检查 */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

	/* step2: 格式化消息到out_buf: 以回车结束 */
	if (PM_LOG_NORMAL_RECORD == typeid)
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"suspend_start:0x%x, suspend_end:0x%x, resume_start:0x%x, resume_end:0x%x\n", log_msg->suspend_start_time, 
				log_msg->suspend_end_time,log_msg->resume_start_time, log_msg->resume_end_time); 
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}

	return PMOM_OK;
}
int pm_msg_parse_ccore(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	if (PM_LOG_NORMAL_RECORD == typeid)
	{	
		struct pm_info_ccore *log_msg = (struct pm_info_ccore *)in_buf;
		if(len != sizeof(*log_msg))
		{
			return PMOM_ERR;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"suspend_start:0x%x, suspend_end:0x%x, suspend_max:0x%x(s_max_start = 0x%x, s_max_end=0x%x), resume_start:0x%x, resume_end:0x%x, resume_max=0x%x,dpm_suspend_max=0x%x,dpm_resume_max = 0x%x,dpm_fail_count = 0x%x\n", 
				log_msg->suspend_start_time,log_msg->suspend_end_time,log_msg->suspend_max_time,log_msg->suspend_max_start_time,log_msg->suspend_max_end_time,
				log_msg->resume_start_time, log_msg->resume_end_time,log_msg->resume_max_time,log_msg->dpm_suspend_max,log_msg->dpm_resume_max,log_msg->dpm_fail_count); 
		*out_ptr = *out_ptr + data_len;
	}
	else if(PM_LOG_IDLE_RECORD == typeid){
		struct idle_pm_s *log_msg = (struct idle_pm_s *)in_buf;
		if(len != sizeof(*log_msg))
		{
			return PMOM_ERR;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"slice:0x%x, idle_time_ms:0x%x, bbp_sleep_timer:0x%x\n",log_msg->slice,log_msg->idle_time_ms,log_msg->bbp_sleeptimer); 
		*out_ptr = *out_ptr + data_len;
	}
	else if(PM_LOG_SET_WAKE_SRC_RECORD == typeid){
		struct pm_wake_src_s *log_msg = (struct pm_wake_src_s *)in_buf;
		if(len != sizeof(*log_msg))
		{
			return PMOM_ERR;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"slice:0x%x, task_id:0x%x, %s, %s\n",log_msg->time_slice,log_msg->task_id,g_pm_set_waketype_obj[(unsigned int)log_msg->set_type],g_pm_set_wakesrc_obj[(unsigned int)log_msg->wake_src]); 
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}

	return PMOM_OK;
}


