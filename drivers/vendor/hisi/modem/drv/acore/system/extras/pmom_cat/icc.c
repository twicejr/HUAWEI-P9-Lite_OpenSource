/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  icc.c
*
*   作    者 :  yaoguocai 184236
*
*   描    述 :  icc 解析主流程
*
*   修改记录 : 2014年12月27日  v1.00  y00184236  创建
*************************************************************************/

#include <stdio.h>
#include "pmom_cat.h"
#include "icc.h"

char *g_com_channel_name[] = {
	"IFC",
	"RFILE",
	"NV",
	"GUOM0",
	"GUOM1",
	"GUOM2",
	"GUOM3",
	"GUOM4",
	"GUOM5",
	"CSHELL",
	"PANRPC"
};

char *g_diff_channel_name[] = {
	"A<->M",
	"C<->M"
};

int icc_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    int data_len = 0;
	struct icc_pm_om *log_msg = (struct icc_pm_om *)in_buf;
	char *channel_name = NULL;
	u32 real_chn_id = GET_CHN_ID(log_msg->packet.channel_id);

    /* step1: 消息类型检查 */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

	if (real_chn_id == ICC_CHN_MCORE_CCORE)
	{
		channel_name = g_diff_channel_name[1];
	}
	else if (real_chn_id == ICC_CHN_MCORE_ACORE)
	{
		channel_name = g_diff_channel_name[0];
	}
	else if (real_chn_id < ICC_CHN_ACORE_CCORE_MAX)
	{
		channel_name = g_com_channel_name[real_chn_id];
	}

    /* step2: 格式化消息到out_buf: 以回车结束 */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
			"sender: cpu%d, task(0x%x), %s(0x%x) at0x%x. receiver: read_cb=0x%llx, read_cb_context=0x%llx\n", 
			log_msg->packet.src_cpu_id, log_msg->packet.task_id, channel_name, 
			log_msg->packet.channel_id, log_msg->packet.timestamp,
			log_msg->read_cb, log_msg->read_context);
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}
