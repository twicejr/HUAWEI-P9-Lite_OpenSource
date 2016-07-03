

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


