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

#ifndef  __CPUFREQ_REGULATOR_H__
#define  __CPUFREQ_REGULATOR_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>


#define DFS_QOS_ID_CCPU_MINFREQ     (2)
#define DFS_QOS_ID_DDR_MINFREQ      (4)
#define CPUFREQ_DDR_LIMIT_MSG		(6)
struct cpufreq_pm_om_qos_log {
	unsigned int taskid;
	unsigned int qos_id;
	unsigned int req_id;
	unsigned int req_value;
	unsigned int req_true_value;
};

struct cpufreq_debug_msg {
	unsigned int msg_type;
	unsigned int source;
	unsigned int content;
	unsigned int target_profile;
	int taskid;
	unsigned int cur_profile;
	unsigned int cur_load;
};

enum CPUFREQ_LOG_TYPE{
	CPUFREQ_ICC_LOG,
	CPUFREQ_VOTE_LOG,
};

typedef enum
{
    DFS_PROFILE_UP   = 0,
    DFS_PROFILE_UP_TARGET = 1,
    DFS_PROFILE_DOWN = 2,
    DFS_PROFILE_DOWN_TARGET = 3,
    DFS_PROFILE_DOWN_LIMIT = 4,
    DFS_PROFILE_UP_LIMIT = 5,
    DFS_PROFILE_LOCKFREQ = 0,
    DFS_PROFILE_UNLOCKFREQ = 1,
	DFS_PROFILE_NOCHANGE = 10,
} DFS_PROFILE_STATE_ENUM;

enum REGULATOR_TYPE_ID
{
	REGULATOR_TYPE = 0,
	MTCMOS_TYPE = 2,
};

#define PMU_TYPE_LEN   (8)
struct regulator_pm_om_log {
	u32 ops_id;
	u32 regulator_id;
	u32 use_count;
	u32 task_id;
	char pmutype[PMU_TYPE_LEN];
};

struct mtcmos_pm_om_log {
	u32 mtcmos_id;
	u32 status;
	u32 ops;
	u32 buck3_flag;
};


int cpufreq_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int regulator_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __CPUFREQ_REGULATOR_H__ */

