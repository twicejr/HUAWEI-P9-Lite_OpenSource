
#include <libfdt.h>
#include <bsp_uart.h>
#include "serial_core.h"

extern int synopsys_uart_drv_init(void);
extern int arm_uart_drv_init(void);

#define UART_NR 	5
static struct uart_port uart_device[UART_NR];

static int uart_device_init(void)
{
    struct device_node *node = NULL;
	struct device_node *child_node=NULL;
    int ret = 0;
	unsigned int index = 0;
	unsigned int reg_sum = 0;
	
    node = of_find_compatible_node(NULL, NULL, "hisilicon,uart_device");
    if (node)
    {
		for_each_available_child_of_node(node, child_node)
		{
			if(reg_sum >= UART_NR)
			{
				return -1;
			}
			ret = of_property_read_u32_array(child_node, "port_id", &index, 1);
			uart_device[index].id = index;
			uart_device[index].base_addr = (unsigned int)of_iomap(child_node, 0);
        	uart_device[index].irq = (unsigned int)irq_of_parse_and_map(child_node, 0);

			ret += of_property_read_u32_array(child_node, "baudrate", &uart_device[index].baudrate, 1);
        	ret += of_property_read_u32_array(child_node, "uartclk", &uart_device[index].uartclk, 1);
        	ret += of_property_read_u32_array(child_node, "periphid", &uart_device[index].periphid, 1);
        	if(ret)
           	{
				return ret;
        	}
			ret = uart_register_device(&uart_device[index]);
			reg_sum++;
		}
	}
	return ret;
}

void bsp_serial_init(void)
{
    synopsys_uart_drv_init();

    arm_uart_drv_init();

    uart_device_init();
}

