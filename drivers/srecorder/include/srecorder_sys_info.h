/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_allcpu_stack.h
    
    @brief: 读取死机时所有活动 CPU的调用栈
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-30
    
    @history:
*/

#ifndef SRECORDER_SYS_INFO_H
#define SRECORDER_SYS_INFO_H


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
    @function: int srecorder_get_sys_info(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取死机时当前系统的信息

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_sys_info(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化sys info模块

    @param: pinit_params 模块初始化数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_sys_info(void)
    @brief: 退出sys info模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_sys_info(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SYS_INFO_H */

