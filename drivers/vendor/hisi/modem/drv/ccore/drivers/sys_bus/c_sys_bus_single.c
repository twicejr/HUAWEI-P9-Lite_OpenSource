/*
 *
 *
 */
//#include <stdio.h>
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_bio.h>
#include "securec.h"
#include <of.h>
#include <drv_comm.h>
#include <sre_mmu.h>
#include <sre_typedef.h>
#include <bsp_icc.h>
#include <c_sys_bus_core.h>
#include <c_sys_bus_single.h>
//extern UINT32 SRE_MmuUnAssign(MMU_VA_T pVStart, UINT32 uwLen);

static LIST_HEAD(list_result_head);

extern struct sys_bus g_sys_bus;
struct bus_single *g_bus_single = NULL;

static char* g_bus_single_propname[]= {
    "bus_single_tcm0",
    "bus_single_tcm1",
};

#define magic_num_u32 0x5a5a5a5a
#define magic_num_u16 0x5b5b
#define magic_num_u8 0xc

void bus_single_mdm_a9(struct bus_single *bus_single)
{
	struct device_node *np;
    struct single_value value;
    struct single_result* single_result;
    u32 i = 0;
    u32 base = 0;
    int ret;
    MMU_VA_T paddr;
    u32 mapflag = 0;

	np = bus_single->of_node;

    for(i=0;i<(sizeof(g_bus_single_propname)/sizeof(char*));i++)
    {
        ret = of_property_read_u32_array(np, g_bus_single_propname[i], (u32*)&value, 4);
        if(ret)
        {
		    break;
	    }
        single_result = malloc(sizeof(struct single_result));
        if (!single_result)
        {
            sys_bus_trace("malloc error\n");
            return;
        }
        single_result->name = g_bus_single_propname[i];

        if(SRE_MmuPA2VA((MMU_PA_T)value.start, &paddr) == OS_ERRNO_MMU_ADDR_NOT_MAPPED)
        {
            mapflag = 1;
            base = (u32)ioremap((MMU_VA_T)value.start, value.size);
            if (!base)
            {
                sys_bus_trace("%s ioremap error\n", g_bus_single_propname[i]);
                single_result->result = 0;
                free(single_result);
    		    return;
        	}
        }
        else
        {
            base = value.start;
        }

        writeb(magic_num_u8, base+value.woffset);
        if(readb(base+value.roffset) != magic_num_u8)
        {
            sys_bus_trace("%s 8bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        writew(magic_num_u16, base+value.woffset);
        if(readw(base+value.roffset) != magic_num_u16)
        {
            sys_bus_trace("%s 16bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        writel(magic_num_u32, base+value.woffset);
        if(readl(base+value.roffset) != magic_num_u32)
        {
            sys_bus_trace("%s 32bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        single_result->result = 1;
        list_add(&single_result->entry, &list_result_head);
        if(mapflag)
        {
            //if(SRE_OK != SRE_MmuUnAssign(value.start, value.size))
        	{
        		sys_bus_trace("%s SRE_MmuUnAssign error\n", g_bus_single_propname[i]);
                return;
        	}
        }
    }
}

void bus_single_msg_handle(struct bus_single *bus_single, void *msg)
{
    struct sys_msg *sysmsg = (struct sys_msg *)msg;
    switch(sysmsg->type)
    {
        case 1:
            bus_single_mdm_a9(bus_single);
            break;
        default:
            break;
    }
}

void bus_single_start(struct bus_single *p)
{
}
void bus_single_stop(void)
{
}

void bus_single_init(struct sys_bus *sysbus, struct device_node * single_np)
{
    struct bus_single *bus_single;
    errno_t nret = 0;

    bus_single = malloc(sizeof(struct bus_single));
    if(NULL == bus_single)
    {
        sys_bus_trace("nomem error\n");
        return;
    }
    //example
    nret = memset_s(bus_single, sizeof(struct bus_single), 0, sizeof(struct bus_single));
    if(nret != EOK)
    {
        sys_bus_trace("memset error\n");
        goto errout1;
    }
    bus_single->of_node = single_np;
    bus_single->start = bus_single_start;
    bus_single->stop = bus_single_stop;

    sysbus->bus_single = (void*)bus_single;
    g_bus_single = bus_single;

    sys_bus_trace("ok\n");
    return;
errout1:
    free(bus_single);

}


