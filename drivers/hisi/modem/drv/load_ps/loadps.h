#ifndef __BSP_LOADPS_H__
#define __BSP_LOADPS_H__

#include <linux/semaphore.h>
#include <linux/wakelock.h>
#include "bsp_om.h"
#include "bsp_loadps.h"

/*loadps模块的打印级别*/
enum bsp_loadps_trace_level
{
    BSP_LOADPS_TRACE_INFO = 0,
    BSP_LOADPS_TRACE_WARNING,
    BSP_LOADPS_TRACE_ERROR
};

/* loadps模块的状态 */
enum bsp_loadps_init_enum
{
    EN_LOADPS_INIT_INVALID = 0,  /* 未初始化 */
    EN_LOADPS_INIT_SUSPEND,      /* C核重启过程中 */
    EN_LOADPS_INIT_FINISH        /* 初始化结束 */
};

/* 处理状态 */
enum bsp_loadps_state_en
{
    EN_LOADPS_IDLE = 0,      /* 待处理 */
    EN_LOADPS_DOING,         /* 正在处理 */
    EN_LOADPS_DONE           /* 处理结束 */
};

struct bsp_loadps_loadinfo_debug
{
    u32 ps_loadinfo_rat_mode;
    u32 ps_loadinfo_phy_loadaddress;
    u32 ps_loadinfo_total_size;
    u32 ps_loadinfo_result;

};
/*loadps模块的加载时间调试数据结构*/
struct bsp_loadps_timestamp_debug
{
    u32 ps_callback_ms;
    u32 ps_task_wakeup_ms;
    u32 ps_load_image_success_ms;
    u32 ps_load_image_total_elapse_ms;

};
/* 主控信息 */
struct bsp_loadps_main_stru
{
    enum bsp_loadps_init_enum  eInitFlag;
    struct task_struct      *taskid;
    loadps_msg              loadps_msg;
    struct semaphore        task_mutex;                /* 任务信号量 */
    struct wake_lock        wake_lock;
    u32                     opState;                /*操作状态*/
    /*记录各个关键的时间点信息方便协议栈同事定位镜像加载时间*/
    struct bsp_loadps_timestamp_debug timestamp_debug;
    struct bsp_loadps_loadinfo_debug  loadinfo_debug;
};

/*loadps模块的动态调试功能*/
#define loadps_trace(trace_level, fmt, ...) do { \
        bsp_trace(trace_level, BSP_MODU_LOADPS,"loadps: " fmt "\n", ##__VA_ARGS__); \
} while (0)

#endif
