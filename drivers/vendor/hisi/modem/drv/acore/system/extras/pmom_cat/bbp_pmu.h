/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_regulator.h
*
*   作    者 :  yangqiang 221789
*
*   描    述 :  cpufreq & regulator 解析头文件
*
*   修改记录 : 2014年12月27日  v1.00  y00221789  创建
*************************************************************************/

#ifndef  __BBP_PMU_H__
#define  __BBP_PMU_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

struct bbp_pwc_infolog
{
    unsigned int ops_id;
    unsigned int   act_module;       /*记录实现开关操作的组件*/
    unsigned int   act_modem;       /*记录实现开关操作的卡(主卡还是副卡)*/
    unsigned int   act_mode;       /*记录实现开关操作的模*/
    unsigned int   task_id;
};
struct bbp_pwc_actlog
{
    u32 ops_id;
    u32 pwc_id;
    u64 vote_lock; /*当前投票情况*/
    unsigned int   act_module;       /*记录实现开关操作的组件*/
    unsigned int   act_modem;       /*记录实现开关操作的卡(主卡还是副卡)*/
    unsigned int   act_mode;       /*记录实现开关操作的模*/
    unsigned int   task_id;
};
typedef enum{
    BBP_LOG_INFO,/*流程*/
    BBP_LOG_ACTUAL/*实际操作了电/钟/pll*/
}BBP_LOG_TYPE_E;
typedef enum{
	BBP_LOG_POWERON = 0,
	BBP_LOG_POWEROFF,
	BBP_LOG_CLKON,
	BBP_LOG_CLKOFF,
	BBP_LOG_PLLON,
	BBP_LOG_PLLOFF,
	BBP_LOG_OTHERS
}BBP_LOG_ID_E;


struct pmu_pmom_log {
    u32 ops_id;
	u32 volt_id;
	u32 task_id;
};
enum PMU_OPS_ID
{
	PMU_OPS_ENABLE = 0,
	PMU_OPS_DISABLE = 1,
	PMU_OPS_IS_ENABLED = 2,
	PMU_OPS_GET_VOLT = 3,
	PMU_OPS_SET_VOLT = 4,
	PMU_OPS_GET_CURR = 5,
	PMU_OPS_SET_CURR = 6,
	PMU_OPS_OTHERS
};

int bbp_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int pmu_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __BBP_PMU_H__ */