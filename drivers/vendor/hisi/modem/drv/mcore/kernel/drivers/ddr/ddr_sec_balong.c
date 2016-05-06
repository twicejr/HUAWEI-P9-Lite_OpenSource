

#include <osl_common.h>
#include <libfdt.h>
#include <bsp_memmap.h>
#include <soc_interrupts_m3.h>
#include "ddr_sec_balong.h"

struct ddr_security_info ddr_sec_info = {0};

/* int clear and info records */
void ddr_sec_int_clear(u32 port)
{
    u32 base_addr = 0;
    u32 sec_fail_cmd_info;
    
    base_addr = (u32)ddr_sec_info.base_addr;

    sec_fail_cmd_info = readl(base_addr + SEC_FAIL_CMD_INF_2(port));

    ddr_sec_info.port_info[port].cmd_id       = sec_fail_cmd_info & SEC_FAIL_CMD_INF_2_ID;
    ddr_sec_info.port_info[port].mid          = sec_fail_cmd_info >>SEC_FAIL_CMD_INF_2_MID_SHIFT;
    ddr_sec_info.port_info[port].low_address  = readl(base_addr + SEC_FAIL_CMD_INF_0(port));

    writel( 0, base_addr + SEC_INT_CLEAR(port));

    printk("ddr sec int: port%d cmd=%d\n",port,ddr_sec_info.port_info[port].cmd_id);
    
    printk("master %d access addr=0x%x \n",port,ddr_sec_info.port_info[port].cmd_id);
}

s32 ddr_sec_int_check(void)
{
    u32 ddr_sec_int_status, port ;
    s32 ret = 0;
    ddr_sec_int_status = readl((u32)(ddr_sec_info.base_addr)+DDRC_INTST);
    for(port=0;port<NUM_OF_PORTS;port++){
        if( ddr_sec_int_status & (0x1<<port) ){
            ret++;
            ddr_sec_int_clear( port );
        }
    }
    return ret;
}

irqreturn_t ddr_sec_int_handler(int irq, void* data)
{
    (void)ddr_sec_int_check();
	return IRQ_HANDLED;
}

void ddr_sec_int_enable(void)
{
    u32 port,val;
    for(port=0;port<NUM_OF_PORTS;port++){
        val = 0x1 | readl((u32)ddr_sec_info.base_addr+0x420+0x200*port);
        writel(val, (u32)ddr_sec_info.base_addr+0x420+0x200*port);
    }
}

s32 ddr_sec_int_init(void)
{
    struct device_node *ddr_sec_node = NULL;

	ddr_sec_node = of_find_compatible_node(NULL, NULL, "ddr_sec_m3");
	if (!ddr_sec_node){
        ddr_sec_info.inited = 0;
		printk("ddr_sec node not found\n");
		return ERROR;
	}
	ddr_sec_info.base_addr = of_iomap(ddr_sec_node, 0);
    ddr_sec_info.irq_no = irq_of_parse_and_map(ddr_sec_node, 0);
	if ((NULL == ddr_sec_info.base_addr)||(0 == ddr_sec_info.irq_no)){
        ddr_sec_info.inited = 0;
		printk("ddr_sec init fail: base_addr=0x%x, irq_no=0x%x\n",\
            ddr_sec_info.base_addr, ddr_sec_info.irq_no);
		return ERROR;
	}
    
    /* check int & clear int */
    if(ddr_sec_int_check())
        printk("ddr_sec has err when init\n");

    (void)request_irq(ddr_sec_info.irq_no, ddr_sec_int_handler, 0, "ddr sec", NULL);
    ddr_sec_int_enable();

    ddr_sec_info.inited = 1;
    return OK;
}




