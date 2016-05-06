/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_save_log.h
    
    @brief: 定义保存定位信息的函数
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-22
    
    @history:
*/

#ifndef SRECORDER_SAVE_LOG_H
#define SRECORDER_SAVE_LOG_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"
#include "srecorder_snprintf.h"
#include "srecorder_memory.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_save_log(char *file_path, char *pbuf, int data_len)
    @brief: 在内核中将信息保存到文件中

    @param: file_path 文件路径
    @param: pbuf 存放信息的内存起始地址
    @param: pbuf 要保存的数据长度
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_save_log(char *file_path, char *pbuf, int data_len);


/**
    @function: int srecorder_renew_meminfo(srecorder_reserved_mem_t *pmem_info, int bytes_read)
    @brief: 更改SRecorder保留内存区描述信息数据结构

    @param: pmem_info 
    @param: bytes_read 
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_renew_meminfo(srecorder_reserved_mem_info_t *pmem_info, int bytes_read);


/**
    @function:int srecorder_write_info_header(srecorder_reserved_mem_t *pmem_info, 
        srecorder_info_type_e type, 
        psrecorder_info_header_t *pinfo_header)
    @brief: 初始化给类信息的头部数据结构

    @param: pmem_info SRecorder的保留内存信息
    @param: type 信息类型
    @param: pinfo_header 信息头部校验数据结构
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_write_info_header(srecorder_reserved_mem_info_t *pmem_info, 
    srecorder_info_type_e type, 
    psrecorder_info_header_t *pinfo_header);


/**
    @function: int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
    @brief: 对各种定位信息的头部并进行校验

    @param: pheader 各类信息的校验头
    @param: data_len 每类信息的数据长度，不包括校验头的数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SAVE_LOG_H */

