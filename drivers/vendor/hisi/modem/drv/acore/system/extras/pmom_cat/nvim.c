/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  icc.h
*
*   作    者 :  yaoguocai 184236
*
*   描    述 :  icc 解析主流程
*
*   修改记录 : 2014年12月27日  v1.00  y00184236  创建
*************************************************************************/

#include <stdio.h>
#include "pmom_cat.h"
#include "nvim.h"

struct nv_icc_msg_name g_nv_msg_name_table[NV_ICC_MSG_TYPE_SUM] = {
    {NV_ICC_REQ_SYS,    "CCPU", "req write system nv"},
    {NV_ICC_REQ_INSTANT_FLUSH,  "CCPU", "req write all work nv instant"},
    {NV_ICC_REQ_CCORE_DELAY_FLUSH,  "CCPU", "ccore req flush nv delay"},
    {NV_REQ_ACORE_DELAY_FLUSH,  "CCPU", "acore req flush nv delay"},
    {NV_ICC_CNF,        "ACPU", "cnf from ACPU"},
    {NV_ICC_RESUME,     "CCPU", "req resume nv"},
};

int nvim_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    int data_len = 0;
	struct nv_icc_stru *log_msg = (struct nv_icc_stru *)in_buf;
    int temp = 0;

	typeid = typeid;
	
    /* step1: 消息类型检查 */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

    for(temp = 0; temp < NV_ICC_MSG_TYPE_SUM; temp++)
    {
        if(g_nv_msg_name_table[temp].msg_type == log_msg->msg_type)
        {
            break;
        }
    }

    if(temp < NV_ICC_MSG_TYPE_SUM)
    {
        /* step2: 格式化消息到out_buf: 以回车结束 */
    	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
    			"[%s] [%s], nvid:0x%x, data off:0x%x, data len:0x%x, slice:0x%x\n", 
    			g_nv_msg_name_table[temp].cpu, g_nv_msg_name_table[temp].work, log_msg->itemid, log_msg->data_off, log_msg->data_len, log_msg->slice
                );
    	*out_ptr = *out_ptr + data_len;
    }
	return PMOM_OK;
}
