#ifndef __C_SYS_BUS_CORE_H__
#define __C_SYS_BUS_CORE_H__

#include "bsp_om.h"
#include <osl_thread.h>
#include <osl_spinlock.h>
#include <osl_sem.h>
#include <osl_list.h>
#include <of.h>
#include <product_config.h>


struct sys_bus {
    struct device_node	*of_node;
    OSL_TASK_ID msg_task;
    osl_sem_id msg_sem;
    spinlock_t  msg_lock;
    struct list_head msg_list;
    u32 channel_id;
    void* bus_single;
};

enum SYS_MODULE_ID {
    E_SYS_MODULE_SINGLE,
    E_SYS_MODULE_PRESSURE,
    E_SYS_MODULE_MAX
};

struct sys_msg {
    struct list_head entry;
    u32 module;    /* single/pressure/... */
    u32 type;
};

struct msghdr {

};


#define sys_bus_trace(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SYS_BUS, "sys_bus:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

#ifdef CONFIG_SYSBUS
void sys_bus_core_init(void);
#else
static inline void sys_bus_core_init(void)
{
}


#endif

#endif /* __C_SYS_BUS_CORE_H__ */

