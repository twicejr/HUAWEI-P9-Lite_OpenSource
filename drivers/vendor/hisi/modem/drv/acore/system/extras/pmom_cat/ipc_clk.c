/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  ipc_clk.c
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  ipc & clk 解析主流程
*
*   修改记录 : 2014年12月31日  v1.00  h00277960  创建
**************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "ipc_clk.h"


/* 根据stat  重写字符串数组 ，stat为0的bit，字符串数组设置为"" */
static int reset_str_array(char *str_array[], unsigned int stat)
{
    unsigned int i = 0;

	for (i = 0; i < 32; i++)
	{
	    if (0 == (stat & (1 << i)))
    	{
    	    str_array[i] = "";
    	}
	}

    return 0;
}

/* A核接收的中断 */
char *g_aipc_int[32] = {
    "IPC_ACPU_INT_SRC_CCPU_MSG"          , /* 0  */
	"IPC_ACPU_INT_SRC_HIFI_MSG"	         , /* 1  */
	"IPC_ACPU_INT_SRC_MCU_MSG"	         , /* 2  */
	"IPC_ACPU_INT_SRC_CCPU_NVIM"         , /* 3  */
	"IPC_INT_DICC_USRDATA" 		         , /* 4  */
	"IPC_INT_DICC_RELDATA"		         , /* 5  */
	"IPC_ACPU_INT_SRC_CCPU_ICC"			 , /* 6  */
	"IPC_ACPU_INT_SRC_ICC_PRIVATE"       , /* 7  */
	"IPC_ACPU_SRC_CCPU_DUMP"		     , /* 8  */
	"IPC_ACPU_INT_SRC_MCPU"		         , /* 9  */
	"IPC_ACPU_INT_SRC_MCPU_WDT"	         , /* 10 */
	"IPC_ACPU_INT_MCU_SRC_DUMP"	         , /* 11 */
	"IPC_ACPU_INT_SRC_CCPU_RESET_IDLE"   , /* 12 */
	"IPC_ACPU_INT_SRC_CCPU_RESET_SUCC"   , /* 13 */
	"IPC_ACPU_INT_SRC_CCPU_LOG"	         , /* 14 */
	"IPC_ACPU_INT_SRC_MCU_FOR_TEST"      , /* 15 */
	"IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE"  , /* 16 */
	"IPC_ACPU_INT_SRC_MCPU_USB_PME"      , /* 17 */
	""                                   , /* 18 */
	""                                   , /* 19 */
	""                                   , /* 20 */
	""                                   , /* 21 */
	""                                   , /* 22 */
	""                                   , /* 23 */
	""                                   , /* 24 */
	""                                   , /* 25 */
	""                                   , /* 26 */
	""                                   , /* 27 */
	""                                   , /* 28 */
	""                                   , /* 29 */
	""                                   , /* 30 */
	""                                     /* 31 */
};

/* C核接收的中断 */
char *g_cipc_int[32] = {
    "IPC_CCPU_INT_SRC_HIFI_MSG"             ,  /* 0  */
    "IPC_CCPU_INT_SRC_MCU_MSG"              ,  /* 1  */
    "IPC_INT_DSP_HALT"                      ,  /* 2  */
    "IPC_INT_DSP_RESUME"                    ,  /* 3  */
    "IPC_INT_DICC_USRDATA"                  ,  /* 4  由于上层共代码，此处的名字与A核中断号名字一样*/
    "IPC_INT_DICC_RELDATA"                  ,  /* 5  由于上层共代码，此处的名字与A核中断号名字一样*/                                                         
    "IPC_INT_WAKE_GU"                       ,  /* 6  */
    "IPC_INT_SLEEP_GU"                      ,  /* 7  */
    "IPC_INT_WAKE_GSM"                      ,  /* 8  */
    "IPC_INT_WAKE_WCDMA"                    ,  /* 9  */
    "IPC_INT_DSP_PS_PUB_MBX"                ,  /* 10 */
    "IPC_INT_DSP_PS_MAC_MBX"                ,  /* 11 */
    "IPC_INT_DSP_MBX_RSD"                   ,  /* 12 */
    "IPC_CCPU_INT_SRC_DSP_MNTN"             ,  /* 13 */
    "IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX"      ,  /* 14 */
    "IPC_CCPU_INT_SRC_ACPU_ICC"             ,  /* 15 */
    "IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR",  /* 16 */         
    "IPC_CCPU_INT_SRC_ACPU_RESET"           ,  /* 17 */
    "IPC_CCPU_SRC_ACPU_DUMP"                ,  /* 18 */
    "IPC_CCPU_INT_SRC_ICC_PRIVATE"          ,  /* 19 */
    "IPC_CCPU_INT_SRC_MCPU"                 ,  /* 20 */
    "IPC_CCPU_INT_SRC_MCPU_WDT"             ,  /* 21 */
	""                                      ,  /* 22 */
	""                                      ,  /* 23 */
	""                                      ,  /* 24 */
	""                                      ,  /* 25 */
	""                                      ,  /* 26 */
	""                                      ,  /* 27 */
	""                                      ,  /* 28 */
	""                                      ,  /* 29 */
	""                                      ,  /* 30 */
	""                                         /* 31 */	
};

int ipc_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	unsigned int ipc_int_stat = ((unsigned int*)in_buf)[0];
	char **ptr_str_tmp = NULL;
	int i = 0;
	char* ptr_str[32] = {NULL};

	/* step1: 消息类型检查 */
	if(len != sizeof(unsigned int))
	{
		return PMOM_ERR;
	}

	switch (core_no)
	{
	    case PM_LOG_ACORE:
			for (i = 0; i < 32; i++)
			{
			     ptr_str[i] = g_aipc_int[i];
			}
			(void)reset_str_array(ptr_str, ipc_int_stat);
			ptr_str_tmp = &ptr_str[0];
			break;
		case PM_LOG_CCORE:
			for (i = 0; i < 32; i++)
			{
			     ptr_str[i] = g_cipc_int[i];
			}
			(void)reset_str_array(ptr_str, ipc_int_stat);
			ptr_str_tmp = &ptr_str[0];
			break;
		default:
			return PMOM_ERR;
	}

	/* step2: 格式化消息到out_buf */                                         
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "int stat:[Bit31:0][0x%08x]", ipc_int_stat);
	*out_ptr = *out_ptr + data_len;
	for (i = 31; i >=0 ; i--)
	{
	    if ('\0' != ptr_str_tmp[i][0])
    	{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%s ", ptr_str_tmp[i]);
			*out_ptr = *out_ptr + data_len;
    	}
	}
	/* 打印回车 */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "\n");
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}



int clk_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct clk_op_entry *clk_log = (struct clk_op_entry *)in_buf;
	char *clk_op_type_str = NULL;
	char *enable_cnt_before_or_after = NULL;
	

	/* step1: 消息类型检查 */
	if(len != sizeof(struct clk_op_entry))
	{
		return PMOM_ERR;
	}


	/* step2: 格式化消息到out_buf: 以回车结束 */
	switch (clk_log->op_type)
	{
	    case CLK_OP_TYPE_ENAB:
			clk_op_type_str = "enable";
			break;
		case CLK_OP_TYPE_DISA:
			clk_op_type_str = "disable";
			break;
		case CLK_OP_TYPE_SETR:
			clk_op_type_str = "set_rate";
			break;
		case CLK_OP_TYPE_SETP:
			clk_op_type_str = "set_parent";
			break;
		case CLK_OP_TYPE_ENAU:
			clk_op_type_str = "en_auto_gate";
			break;
		case CLK_OP_TYPE_DIAU:
			clk_op_type_str = "dis_auto_gate";
			break;

		default:
			return PMOM_ERR;
	}

    clk_log->clk_name[LOG_CLK_NAME_LEN - 1] = 0x00;  /* 防止解析出的名字后出现乱码 */
	if (PM_LOG_CCORE == core_no) /* ccore */
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task:0x%x,%s,%s,enable_cnt before op %d\n", clk_log->task_id,  
				                                             clk_op_type_str, &clk_log->clk_name[0],
				                                             clk_log->enable_count_before_op); 
	}
	else  /* acore，由于是在ops里记录的log，所以不再解析引用计数 */
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task:0x%x,%s,%s\n", clk_log->task_id, clk_op_type_str, &clk_log->clk_name[0]); 
	}
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}

