/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_allcpu_stack.h
    
    @brief: 读取死机时所有活动 CPU的调用栈
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-30
    
    @history:
*/

#ifndef SRECORDER_ALLCPU_STACK_H
#define SRECORDER_ALLCPU_STACK_H


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
    @function: int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取死机时所有活动 CPU的调用栈

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function:int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化allcpu stack模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_allcpu(void)
    @brief: 模块退出函数，它的主要工作是清除allcpu stack模块中的变量s_reserved_mem_info_for_log_temp，
           因为在等待workqueue完成检查cpu调用栈的超时时间到了以后，我们不再希望其他的线程或者任务往
           SRecorder的保留内存区写内容，因此必须把它设置为NULL。

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_allcpu_stack(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_ALLCPU_STACK_H */

