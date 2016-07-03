

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PWRCTRL_DFS_H__
#define __PWRCTRL_DFS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PWRCTRL_DFS_CMD_TIMEOUT (100)

#define UNLOCK_FREQ 0x0
#define UNLOCK_PROFILE 0x5C5C

#define DEVICE_ID_ACPU    (0)
#define DEVICE_ID_GPU     (2)
#define DEVICE_ID_DDR_MIN (3)
#define DEVICE_ID_DDR_MAX (4)

#define ACPU_SUSPEND_RLQOS_DDR_MIN_VALUE            (5)
#define ACPU_SUSPEND_RLQOS_DDR_MAX_VALUE            (0x0FFFFFFF)


/*ddr defualt profile related*/
#define QOS_DDR_MAX_DEFAULT_VALUE  (0x7FFFFFFF)
#define QOS_DDR_MIN_DEFAULT_VALUE  (0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
struct dfs_prof_pli
{
    unsigned int asc_threshold;
    int des_threshold;
    unsigned int asc_step;
    unsigned int des_step;
    int asc_delay;
    int des_delay;
};


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
extern ST_PWC_SWITCH_STRU * g_stPwcSwitch;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern int pwrctrl_dfs_init(void);


typedef int(*get_func_handle)(unsigned int *func);

extern int ddr_get_func_handle(unsigned int *func);
extern int buslow_get_func_handle(unsigned int *func);
extern int bus_get_func_handle(unsigned int *func);

typedef int(*set_func_handle)(unsigned int func);

extern int ddr_set_func_handle(unsigned int func);
extern int buslow_set_func_handle(unsigned int func);
extern int bus_set_func_handle(unsigned int func);

typedef int(*cur_profile_handle)(unsigned int *profile_id);

extern int ddr_cur_profile_handle(unsigned int *profile_id);

typedef int(*set_policy_handle)(void *policy, unsigned int len);

extern int ddr_set_policy_handle(void *policy, unsigned int len);

typedef int(*set_profile_handle)(void *profile, unsigned int len);

extern int ddr_set_profile_handle(void *profile, unsigned int len);

typedef int(*set_freq_handle)(unsigned int freq);

extern int ddr_maxfreq_handle(unsigned int freq);
extern int ddr_minfreq_handle(unsigned int freq);
extern int ddr_lockfreq_handle(unsigned int profile);
extern int ddr_safefreq_handle(unsigned int freq);
extern int buslow_minfreq_handle(unsigned int req_value);
extern int buslow_maxfreq_handle(unsigned int req_value);
extern int bus_minfreq_handle(unsigned int req_value);
extern int bus_maxfreq_handle(unsigned int req_value);
extern int pwrctrl_dfs_qos_update(unsigned int dev_id, int* req_id, unsigned int req_value);
extern int pwrctrl_acpu_freq_limit_max(unsigned int req_value, unsigned int req_flag);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_dfs.h */
