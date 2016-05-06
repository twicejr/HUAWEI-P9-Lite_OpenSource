/*************************************************************************
*   版权所有(C) 2008-2015, 华为技术有限公司.
*
*   文 件 名 :  memrepair_balong.h
*
*   作    者 :  x00195528
*
*   描    述 :  memrepair相关头文件
*
*   修改记录 :  2015年10月20日  v1.00  x00195528  创建
*************************************************************************/

#ifndef MEMREPAIR_BALONG_H
#define MEMREPAIR_BALONG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_om.h>
#include <bsp_memrepair.h>

struct repair_info
{
    u32 cnts;/*计数*/
    u32 time;/*计时*/
};

struct memrepair_info
{
    int flag;
    int errno;
    struct repair_info info[MODEM_MEMREPAIR_BUTT];
};

#define MEMRAIR_START_TIMEOUT_SLICE    (58)
#define MEMRAIR_DONE_TIMEOUT_SLICE     (580)

#define  mr_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEMREPAIR, "[memrepair]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  mr_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_MEMREPAIR, "[memrepair]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))


#ifdef __cplusplus
}
#endif

#endif


