/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.

    @file: srecorder_snprintf.c

    @brief: 定义SRecorder的格式化输出模块

    @version: 1.0 

    @author: QiDechun ID: 216641

    @date: 2013-01-18

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <stdarg.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <linux/highmem.h>

#include <linux/version.h>
#include <net/addrconf.h>

#include <asm/page.h>        /* for PAGE_SIZE */
#include <asm/div64.h>
#include <asm/sections.h>    /* for dereference_function_descriptor() */

#include "../include/srecorder_snprintf.h"


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
    @brief: 按指定格式输出字符串到指定缓存中。

    @param: buf 缓存
    @param: size 缓存空间大小
    @param: fmt 字符串格式

    @return: 写入缓存的字节数

    @note: 
*/
int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list args;
    int i = 0;

    va_start(args, fmt);
    i = vscnprintf(buf, size, fmt, args);
    va_end(args);

    return i;
}


/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化格式化输出模块

    @param: pinit_params 模块初始化数据

    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: 退出格式化输出模块

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_snprintf(void)
{
}

