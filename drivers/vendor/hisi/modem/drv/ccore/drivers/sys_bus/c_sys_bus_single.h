#ifndef __C_SYS_BUS_SINGLE_H__
#define __C_SYS_BUS_SINGLE_H__

#include <osl_list.h>
#include <c_sys_bus_core.h>

struct bus_single {
    struct device_node	*of_node;
    void (*start)(struct bus_single *);
	void (*stop)(void);
};

struct single_value {
    u32 start;
    u32 size;
    u32 woffset;
    u32 roffset;
};

struct single_result {
    struct list_head entry;
    char* name;
    u32 result;
};

void bus_single_msg_handle(struct bus_single *bus_single, void *msg);

void bus_single_init(struct sys_bus *sysbus, struct device_node * single_np);




#endif /* __C_SYS_BUS_SINGLE_H__ */

