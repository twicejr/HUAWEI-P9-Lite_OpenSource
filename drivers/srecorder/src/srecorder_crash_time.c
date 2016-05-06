/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_crash_time.c
    
    @brief: 读取死机时当前系统的时间(UTC格式)
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/stddef.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <asm/uaccess.h>

#include "../include/srecorder_crash_time.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_snprintf.h"


#if defined(CONFIG_DUMP_CRASH_TIME)

/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: int srecorder_get_crash_time(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 记录死机发生的时间，顺便记录死机的原因。

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_crash_time(srecorder_reserved_mem_info_t *pmem_info)
{
    struct timeval tv;
    /* struct timex txc; */
    struct rtc_time tm;
    int bytes_read = 0;
    char *pbuf = NULL;
    psrecorder_info_header_t pinfo_header = NULL;
        
    if (unlikely(NULL == pmem_info))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(CRASH_REASON_TIME_BIT0))
    {
        SRECORDER_PRINTK("Crash reason and time have been dumped successfully!\n");
        return 0;
    }
    
    memset(&tv, 0, sizeof(struct timeval));
    /* memset(&txc, 0, sizeof(struct timex)); */
    memset(&tm, 0, sizeof(struct rtc_time));

    if (0 != srecorder_write_info_header(pmem_info, CRASH_REASON_TIME_BIT0, &pinfo_header))
    {
        return -1;
    }
    
    do_gettimeofday(&tv);
    tv.tv_sec -= sys_tz.tz_minuteswest * 60; /* 一分钟=60秒 */
    rtc_time_to_tm(tv.tv_sec, &tm);
    pbuf = pmem_info->start_addr + pmem_info->bytes_read;/* [false alarm]:there is pmem_info protect before  */
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "Crash reason: %s %s Crash Time: %04d%02d%02d-%02d:%02d:%02d\n", 
        (NULL == pmem_info->crash_reason1) ? ("") : (pmem_info->crash_reason1), 
        (NULL == pmem_info->crash_reason2) ? ("") : (pmem_info->crash_reason2), 
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化crash time模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(CRASH_REASON_TIME_BIT0);
    
    return 0;
}


/**
    @function: void srecorder_exit_crash_time(void)
    @brief: 退出crash time模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_crash_time(void)
{
    srecorder_set_log_dumped_bit(CRASH_REASON_TIME_BIT0);
}
#else
int srecorder_get_crash_time(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_crash_time(void)
{
    return;
}
#endif

