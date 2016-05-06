
#include <of.h>
#include <drv_comm.h>
#include <c_sys_bus_core.h>
#include <c_sys_edma.h>
#include <c_sys_ipf.h>
#include <c_sys_acc.h>
#include <c_sys_cpufreq.h>
#include <c_sys_gu.h>
#include <c_sys_dsp.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_ddr.h>


extern struct sys_bus g_sys_bus;

static LIST_HEAD(master_head);

static struct of_device_id bus_pressure_ids[] = {
    {.compatible = "bus_pressure, edma", .data = sys_edma_init},
	{.compatible = "bus_pressure, ipf", .data = sys_ipf_init},
    {.compatible = "bus_pressure, acc", .data = sys_acc_init},
    {.compatible = "bus_pressure, gu", .data = sys_gu_init},
    {.compatible = "bus_pressure, dsp", .data = sys_dsp_init},
    {.compatible = "bus_pressure, mem", .data= sys_mem_init},
    {.compatible = "bus_pressure, cpufreq", .data = sys_cpufreq_init},
    {},
};

typedef void(*master_of_init_fn)(struct master*);

void bus_pressure_init(struct sys_bus *sysbus, struct device_node * pressure_np)
{
    const struct of_device_id *match;
    struct master* master;
    master_of_init_fn init_func;
    struct device_node *np;

    np = pressure_np;
    for_each_matching_node_and_match(np, bus_pressure_ids, &match)
    {
        master = malloc(sizeof(struct master));
        if (!master)
        {
            sys_bus_trace("failed to allocate master!");
            return;
        }
        master->np = np;
        init_func = match->data;
        init_func(master);
        list_add_tail(&master->entry, &master_head);
    }
    sys_bus_trace("ok\n");
}

void bus_pressure_start(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->start)
            master->start(master);
    }
}

void bus_pressure_stop(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->stop)
            master->stop(master);
    }
}

void bus_pressure_record(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->record)
            master->record(master);
    }
}

void bus_pressure_report(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->report)
            master->report(master);
    }
}


