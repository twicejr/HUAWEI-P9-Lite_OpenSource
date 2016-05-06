/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_dfs.h
  版 本 号   : 初稿
  作    者   : 黄星宇 212111
  生成日期   : 2012年9月3日
  最近修改   :
  功能描述   : pwrctrl_dfs.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月3日
    作    者   : 黄星宇 212111
    修改内容   : 创建文件

******************************************************************************/

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


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern int pwrctrl_dfs_init(void);


/*
 *  GPU Interface
 */
extern int pwrctrl_dfs_gpu_target(int step);

typedef int(*get_func_handle)(unsigned int *func);

#if 0//stub
extern int acpu_get_func_handle(unsigned char *func);
extern int gpu_get_func_handle(unsigned char *func);
extern int ddr_get_func_handle(unsigned char *func);
#else
extern int acpu_get_func_handle(unsigned int *func);
extern int gpu_get_func_handle(unsigned int *func);
extern int ddr_get_func_handle(unsigned int *func);
extern int bus_get_func_handle(unsigned int *func);
#endif

typedef int(*set_func_handle)(unsigned int func);

#if 0//stub
int acpu_set_func_handle(unsigned char func){}
int gpu_set_func_handle(unsigned char func){}
int ddr_set_func_handle(unsigned char func){}
#else
extern int acpu_set_func_handle(unsigned int func);
extern int gpu_set_func_handle(unsigned int func);
extern int ddr_set_func_handle(unsigned int func);
extern int bus_set_func_handle(unsigned int func);
#endif

typedef int(*cur_profile_handle)(unsigned int *profile_id);

#if 0//stub
int acpu_cur_profile_handle(unsigned int *profile_id){}
int gpu_cur_profile_handle(unsigned int *profile_id){}
int ddr_cur_profile_handle(unsigned int *profile_id){}
#else
extern int acpu_cur_profile_handle(unsigned int *profile_id);
extern int gpu_cur_profile_handle(unsigned int *profile_id);
extern int ddr_cur_profile_handle(unsigned int *profile_id);
#endif

typedef int(*set_policy_handle)(void *policy, unsigned int len);

#if 0//stub
int acpu_set_policy_handle(void *policy, unsigned int len){}
int gpu_set_policy_handle(void *policy, unsigned int len){}
int ddr_set_policy_handle(void *policy, unsigned int len){}
#else
extern int acpu_set_policy_handle(void *policy, unsigned int len);
extern int gpu_set_policy_handle(void *policy, unsigned int len);
extern int ddr_set_policy_handle(void *policy, unsigned int len);
#endif

typedef int(*set_profile_handle)(void *profile, unsigned int len);

#if 0//stub
int acpu_set_profile_handle(void *profile, unsigned int len){}
int gpu_set_profile_handle(void *profile, unsigned int len){}
int ddr_set_profile_handle(void *profile, unsigned int len){}
#else
extern int acpu_set_profile_handle(void *profile, unsigned int len);
extern int gpu_set_profile_handle(void *profile, unsigned int len);
extern int ddr_set_profile_handle(void *profile, unsigned int len);
#endif

typedef int(*set_freq_handle)(unsigned int freq);

#if 0//stub
int acpu_maxfreq_handle(unsigned int freq){}
int gpu_maxfreq_handle(unsigned int freq){}
int ddr_maxfreq_handle(unsignedint freq){}
int acpu_minfreq_handle(unsigned int freq){}
int gpu_minfreq_handle(unsigned int freq){}
int ddr_minfreq_handle(unsigned int freq){}
int acpu_lockfreq_handle(unsignedint profile){}
int gpu_lockfreq_handle(unsigned int profile){}
int ddr_lockfreq_handle(unsigned int profile){}
int acpu_safefreq_handle(unsigned int freq){}
int gpu_safefreq_handle(unsigned int freq){}
int ddr_safefreq_handle(unsigned int freq){}
#else
extern int acpu_maxfreq_handle(unsigned int freq);
extern int gpu_maxfreq_handle(unsigned int freq);
extern int ddr_maxfreq_handle(unsigned int freq);
extern int acpu_minfreq_handle(unsigned int freq);
extern int gpu_minfreq_handle(unsigned int freq);
extern int ddr_minfreq_handle(unsigned int freq);
extern int acpu_lockfreq_handle(unsigned int profile);
extern int gpu_lockfreq_handle(unsigned int profile);
extern int ddr_lockfreq_handle(unsigned int profile);
extern int acpu_safefreq_handle(unsigned int freq);
extern int gpu_safefreq_handle(unsigned int freq);
extern int ddr_safefreq_handle(unsigned int freq);
extern int bus_minfreq_handle(unsigned int req_value);
extern int bus_maxfreq_handle(unsigned int req_value);
extern int bus_lockfreq_handle(unsigned int req_value);
extern int bus_safefreq_handle(unsigned int req_value);

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_dfs.h */
