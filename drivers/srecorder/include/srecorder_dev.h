/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2013. All rights reserved.
    
    @file: srecorder_dev.h
    
    @brief: 
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2013-01-30
    
    @history:
*/

#ifndef SRECORDER_DEV_H
#define SRECORDER_DEV_H


/*----includes-----------------------------------------------------------------------*/


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化SRecorder字符设备模块

    @param: pinit_params 模块初始化数据

    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_dev(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: 退出SRecorder字符设备模块

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_dev(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_DEV_H */

