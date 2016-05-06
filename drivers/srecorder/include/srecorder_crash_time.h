/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_crash_time.h
    
    @brief: 读取死机时当前系统的时间(UTC格式)
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-30
    
    @history:
*/

#ifndef SRECORDER_CRASH_TIME_H
#define SRECORDER_CRASH_TIME_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_get_crash_time(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 记录死机发生的时间，顺便记录死机的原因。

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_crash_time(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化crash time模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_crash_time(void)
    @brief: 退出crash time模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_crash_time(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_CRASH_TIME_H */

