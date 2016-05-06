/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_memory.h
    
    @brief: 定义SRecorder的内存操作接口
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2013-01-18
    
    @history:
*/

#ifndef SRECORDER_MEMORY_H
#define SRECORDER_MEMORY_H


/*----includes-----------------------------------------------------------------------*/

#include <asm/io.h>
#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define SRECORDER_MEMCPY_TOIO _memcpy_toio
#define SRECORDER_MEMCPY_FROMIO _memcpy_fromio
#define SRECORDER_MEMSET _memset_io
#define SRECORDER_WRITEB writeb
#define SRECORDER_WRITEW writew
#define SRECORDER_WRITEL writel

#define FLUSH_DCACHE_EVERY_TIME_WHEN_WRITE (0)


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: void srecorder_set_contiguous_virt_addr_flag(void)
    @brief: 设置s_srecorder_has_contiguous_virt_addr的值

    @param: flag 
    
    @return: none

    @note: 
*/
void srecorder_set_contiguous_virt_addr_flag(bool flag);


/**
    @function: bool srecorder_has_contiguous_virt_addr(void)
    @brief: 判断SRecorder是否拥有连续的虚拟地址空间

    @param: none 
    
    @return: true - SRecorder拥有连续的虚拟地址空间, false - SRecorder没有连续的虚拟地址空间

    @note: 
*/
bool srecorder_has_contiguous_virt_addr(void);


/**
    @function: void srecorder_read_data_from_phys_page(char *pdst, unsigned long phys_src, size_t bytes_to_read)
    @brief: 根据物理地址按照每个物理页面读数据

    @param: pdst 写入地址
    @param: phys_src 源数据物理起始地址
    @param: bytes_to_read 要读取的数据长度
    
    @return: 成功读取的字节数

    @note: 
*/
int srecorder_read_data_from_phys_page(char *pdst, unsigned long phys_src, size_t bytes_to_read);


/**
    @function: int srecorder_write_data_by_page(unsigned long phys_dst, size_t phys_mem_size, 
        char *psrc, size_t bytes_to_write)
    @brief: 根据物理地址按照每个物理页面写入数据

    @param: phys_dst 物理起始地址
    @param: phys_mem_size 物理空间大小
    @param: psrc 原始数据缓存
    @param: bytes_to_write 原始数据长度
    
    @return: 写入缓存的字节数

    @note: 
*/
int srecorder_write_data_to_phys_page(unsigned long phys_dst, size_t phys_mem_size, 
    char *psrc, size_t bytes_to_write);


/**
    @function: void srecorder_release_virt_addr(psrecorder_virt_zone_info_t pzone_info)
    @brief: 释放应经使用过的虚拟地址空间

    @param: pzone_info 

    @return: none

    @note: 
*/
void srecorder_release_virt_addr(psrecorder_virt_zone_info_t pzone_info);


/**
    @function: bool srecorder_map_phys_addr(psrecorder_virt_zone_info_t pzone_info)
    @brief: 映射物理内存到虚拟地址空间

    @param: pzone_info 
    
    @return: true - 映射成功；false - 失败

    @note: 
*/
bool srecorder_map_phys_addr(psrecorder_virt_zone_info_t pzone_info);


/**
    @function: int srecorder_init_memory(void)
    @brief: 初始化内存映射操作模块

    @param: pinit_params 模块初始化数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_memory(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_memory(void)
    @brief: 退出内存映射操作模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_memory(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_MEMORY_H */

