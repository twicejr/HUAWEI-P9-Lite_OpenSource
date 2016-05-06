/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  dsp.h
*
*   作    者 :  wangxia 271929
*
*   描    述 :  dsp 解析主流程
*
*   修改记录 : 2015年01月9日  v1.00  w00271929  创建
**************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "dsp.h"

int dsp_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    unsigned int data_len = 0;
    struct dsp_pm_om_qos_log *time_log = NULL;

    /* step1: 消息类型检查 */
    if(len != sizeof(*time_log))
    {
        return PMOM_ERR;
    }

    /* step2: 格式化消息到out_buf: 以回车结束 */
	time_log = (struct dsp_pm_om_qos_log *)in_buf;
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
			"load_start:0x%x, load_end:0x%x, msp_store:0x%x, dpm_store:0x%x, dsp_store:0x%x, dsp_store_end:0x%x, poweroff:0x%x, poweron:0x%x, dpm_wait_store_ok:0x%x, dpm_restore:0x%x, dsp_restore:0x%x, msp_restore:0x%x, msp_restore_ok:0x%x\n", 
			time_log->load_start, time_log->load_end, time_log->msp_store, 
			time_log->dpm_store, time_log->dsp_store, time_log->dsp_store_end,
			time_log->poweroff, time_log->poweron, time_log->dpm_wait_store_ok,
			time_log->dpm_restore, time_log->dsp_restore, time_log->msp_restore,
			time_log->msp_restore_ok); 
	*out_ptr = *out_ptr + data_len;
	
	return PMOM_OK;
}
