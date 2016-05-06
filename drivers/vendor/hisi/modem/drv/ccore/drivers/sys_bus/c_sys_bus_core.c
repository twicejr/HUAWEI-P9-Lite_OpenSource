/*
 *
 *
 */
#include <of.h>
#include <drv_comm.h>
#include <bsp_icc.h>
#include <c_sys_monitor.h>
#include <c_sys_bus_single.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_pmu.h>
#include <c_sys_bus_core.h>

struct sys_bus* g_sys_bus = NULL;

typedef void(*sysbus_of_init_fn)(struct sys_bus *, struct device_node *);

static struct of_device_id sys_bus_of_device_ids[] = {
	{.compatible = "sys_bus, bus_single", .data = bus_single_init},
	{.compatible = "sys_bus, bus_pressure",	.data = bus_pressure_init},
	{},
};

s32 sys_bus_read_cb(u32 id , u32 len, void* context)
{
	s32 ret = 0;
    struct sys_msg *msg;
    unsigned long flags;
    struct sys_bus *sysbus = (struct sys_bus *)context;

	if((len == 0) || (len > sizeof(struct sys_msg)))
	{
		sys_bus_trace("readcb len is err\n");
        return -1;
	}

    msg = malloc(sizeof(struct sys_msg));
    if(!msg)
    {
        sys_bus_trace("malloc err\n");
        return -1;
    }
	ret = bsp_icc_read(id, (u8*)msg, len);
	if(len != ret)
	{
		sys_bus_trace("readcb err\n");
        free(msg);
		return -1;
	}
    spin_lock_irqsave(&sysbus->msg_lock, flags);
    list_add_tail(&msg->entry, &sysbus->msg_list);
    spin_unlock_irqrestore(&sysbus->msg_lock, flags);

	return 0;
}

int sysbus_task_func(void* data)
{
 	struct sys_msg *p, *n;
	unsigned long flags;
    struct sys_bus *sysbus = (struct sys_bus *)data;

	for( ; ; )
	{
		osl_sem_down(&sysbus->msg_sem);
		spin_lock_irqsave(&sysbus->msg_lock, flags);
		if (!list_empty(&sysbus->msg_list))
		{
            list_for_each_entry_safe(p, n, &sysbus->msg_list, entry)
            {
                list_del(&p->entry);
                spin_unlock_irqrestore(&sysbus->msg_lock, flags);
                switch(p->module)
                {
                    case E_SYS_MODULE_SINGLE:
                        bus_single_msg_handle((struct bus_single *)sysbus->bus_single, (void*)p);
                        break;
                    case E_SYS_MODULE_PRESSURE:
                        break;
                    default:
                        break;
                }
                free(p);
            }
		}
		else
		{
			spin_unlock_irqrestore(&sysbus->msg_lock, flags);
		}
	}
	return 0;
}

void sys_bus_core_init(void)
{
    sysbus_of_init_fn init_fn = NULL;
    const struct of_device_id *match;
    struct device_node *np;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_SYS_BUS;
    s32 ret = 0;
    struct sys_bus *sysbus;

    sysbus = malloc(sizeof(struct sys_bus));
    if(NULL == sysbus)
    {
        sys_bus_trace("nomem error\n");
        return;
    }

    ret = bsp_icc_event_register(channel_id, sys_bus_read_cb, (void*)sysbus, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
		sys_bus_trace("icc register error\n");
        goto errout1;
	}
    sysbus->channel_id = channel_id;
    INIT_LIST_HEAD(&sysbus->msg_list);

    osl_sem_init(SEM_EMPTY,&sysbus->msg_sem);
    if(ERROR == osl_task_init("sysbus_t", 10, 0x1000 ,(void *)sysbus_task_func, (void*)sysbus, &sysbus->msg_task))
    {
        sys_bus_trace("task init error\n");
        goto errout1;
    }

    np = of_find_compatible_node(NULL, NULL, "hisilicon, sys_bus");
    if (!np)
    {
        sys_bus_trace("find sys_bus node error\n");
        goto errout1;
    }
    sysbus->of_node = np;

    for_each_matching_node_and_match(np, sys_bus_of_device_ids, &match)
    {
		init_fn = (sysbus_of_init_fn)match->data;
		init_fn(sysbus, np);
	}
    g_sys_bus = sysbus;

    (void)sys_monitor_init();
    sys_pmu_init();
    sys_bus_trace("ok\n");
    return;

errout1:
    free(sysbus);

}


