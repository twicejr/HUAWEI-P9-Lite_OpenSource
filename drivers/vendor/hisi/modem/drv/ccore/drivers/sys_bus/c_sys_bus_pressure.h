#ifndef __C_SYS_BUS_PRESSURE_H__
#define __C_SYS_BUS_PRESSURE_H__

#include <osl_irq.h>
#include <osl_list.h>
#include <c_sys_bus_core.h>

struct master
{
    struct list_head entry;
    struct device_node *np;
    int init_flag;
    int enable_flag;
    char name[32];
    void (*master_init)(struct master* master);
    int (*request_irq)(struct master*, irq_handler_t handler);
    void (*free_irq)(struct master*);
    void (*start)(struct master*);
    void (*stop)(struct master*);
    void (*record)(struct master*);
    void (*report)(struct master*);
};

void bus_pressure_init(struct sys_bus *sysbus, struct device_node * pressure_np);
void bus_pressure_start(void);
void bus_pressure_stop(void);
void bus_pressure_record(void);
void bus_pressure_report(void);


#endif /* __C_SYS_BUS_PRESSURE_H__ */

