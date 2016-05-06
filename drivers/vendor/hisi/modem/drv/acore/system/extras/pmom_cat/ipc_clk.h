/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  ipc_clk.h
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  ipc & clk 解析头文件
*
*   修改记录 : 2014年12月31日  v1.00  h00277960  创建
*************************************************************************/

#ifndef  __IPC_CLK_H__
#define  __IPC_CLK_H__

#ifdef __cplusplus
    extern "C" {
#endif


enum clk_op_type{
    CLK_OP_TYPE_ENAB = 0x454E4142,  /* clk_enable              */
    CLK_OP_TYPE_DISA = 0x44495341,  /* clk_disable             */
    CLK_OP_TYPE_SETR = 0x53455452,  /* clk_set_rate            */
    CLK_OP_TYPE_SETP = 0x53455450,  /* clk_set_parent          */
    CLK_OP_TYPE_ENAU = 0x454E4155,  /* clk_enable_auto_gating  */
    CLK_OP_TYPE_DIAU = 0x44494155   /* clk_disable_auto_gating */
};

enum pm_log_core_no{
    PM_LOG_ACORE,  
	PM_LOG_CCORE
};


#define LOG_CLK_NAME_LEN   8  /* 记录时钟名字的前8个字符 */

struct clk_op_entry{
    unsigned int      task_id;                         /* 操作者任务ID */
	char              clk_name[LOG_CLK_NAME_LEN]; /* 被操作的时钟名字 */
    unsigned int      op_type;                         /* 操作类型 */
	unsigned int      enable_count_before_op;          /* 操作前的应用计数 */
};




int ipc_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int clk_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __IPC_CLK_H__ */

