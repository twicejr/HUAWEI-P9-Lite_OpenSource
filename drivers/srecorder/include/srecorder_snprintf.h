/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_snprintf.h
    
    @brief: 
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2013-01-18
    
    @history:
*/

#ifndef SRECORDER_SNPRINTF_H
#define SRECORDER_SNPRINTF_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define SRECORDER_SNPRINTF srecorder_snprintf


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/


/**
    @function: int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
    @brief: 按指定格式输出字符串到指定缓存中。

    @param: buf 缓存
    @param: size 缓存空间大小
    @param: fmt 字符串格式

    @return: 写入缓存的字节数

    @note: 
*/
int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...);


/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化格式化输出模块

    @param: pinit_params 模块初始化数据

    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: 退出格式化输出模块

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_snprintf(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SNPRINTF_H */

