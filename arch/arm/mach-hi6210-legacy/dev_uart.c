#include <mach/dma.h>
#include <linux/amba/serial.h>
#include <linux/amba/bus.h>
#include <mach/irqs.h>
#include <mach/dev.h>
#include <mach/early-debug.h>
#include "reg_ops.h"
#if defined(CHIP_BB_HI6210)
#else
#include "soc_sctrl_interface.h"
#endif
#include "soc_peri_sctrl_interface.h"
/*uart device declare and register*/

#define UART_RESET_CONTROLLER_TIMEOUT 10

#define MODULE_FUNCS_DEFINE(chip_id, dev_name)				\
static void dev_name ## _init(void){				\
    unsigned int ret;\
    unsigned int timeout = UART_RESET_CONTROLLER_TIMEOUT;\
\
    phy_reg_writel(REG_BASE_SC_OFF,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(CALC_REG_OFFSET),\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_ ## dev_name ## _START,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_ ## dev_name ## _END, 1);\
\
    while (timeout--){\
        ret = phy_reg_readl(REG_BASE_SC_OFF, \
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_ADDR(CALC_REG_OFFSET),\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## dev_name ## _START,\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## dev_name ## _END);\
\
        if (ret && (!timeout)){\
            printk(KERN_ERR "mmc %d clock rst fail\n", chip_id);\
        } else if (!ret){\
              break;\
        } \
    } \
}								\
static void dev_name##_exit(void){				\
}

#if 1
K3_DEF_DMA_PARAM(uart0_RX);
K3_DEF_DMA_PARAM(uart0_TX);
#endif
K3_DEF_DMA_PARAM(uart1_RX);
K3_DEF_DMA_PARAM(uart1_TX);
K3_DEF_DMA_PARAM(uart2_RX);
K3_DEF_DMA_PARAM(uart2_TX);
K3_DEF_DMA_PARAM(uart3_RX);
K3_DEF_DMA_PARAM(uart3_TX);
K3_DEF_DMA_PARAM(uart4_RX);
K3_DEF_DMA_PARAM(uart4_TX);


#define UART0_BLOCK_NAME            "block_uart0"
#define UART1_BLOCK_NAME            "block_uart1"
#define UART3_BLOCK_NAME            "block_uart3"

#if 0
MODULE_FUNCS_DEFINE(0, uart0)
#else
static void uart0_init(void)
{
    ;
}

static void uart0_exit(void)
{
    ;
}

#endif
MODULE_FUNCS_DEFINE(1, uart1)
MODULE_FUNCS_DEFINE(2, uart2)
MODULE_FUNCS_DEFINE(3, uart3)
MODULE_FUNCS_DEFINE(4, uart4)
#if 0
MODULE_FUNCS_DEFINE(5, uart5)
MODULE_FUNCS_DEFINE(6, uart6)
#endif

#define uart0_dma_filter  NULL
#define uart1_dma_filter  NULL
#define uart2_dma_filter  NULL
#define uart3_dma_filter  NULL
#define uart4_dma_filter  NULL

#define K3_UART_PLAT_DATA(dev_name, flag)				\
	{								\
		.dma_filter = dev_name##_dma_filter,			\
		.dma_rx_param = &K3_DMA_PARAM_NAME(dev_name##_RX),	\
		.dma_tx_param = &K3_DMA_PARAM_NAME(dev_name##_TX),	\
		.irq_flags = flag,					\
		.init = dev_name##_init,				\
		.exit = dev_name##_exit,				\
	}

static struct amba_pl011_data uart_plat_data[] = {
	K3_UART_PLAT_DATA(uart0, 0),
	K3_UART_PLAT_DATA(uart1, 0),
	K3_UART_PLAT_DATA(uart2, 0),
	K3_UART_PLAT_DATA(uart3, 0),
	K3_UART_PLAT_DATA(uart4, 0),
};

#ifdef CONFIG_MACH_HI6210SFT
AMBA_DEVICE(uart0, "amba-uart.0", UART0, &uart_plat_data[0]);
AMBA_DEVICE(uart3, "amba-uart.3", UART3, &uart_plat_data[3]);
AMBA_DEVICE(uart4, "amba-uart.4", UART4, &uart_plat_data[4]);
#endif

#ifdef CONFIG_MACH_HI6210OEM
#if 0
AMBA_DEVICE(uart0, "amba-uart.0", UART0, &uart_plat_data[0]);
#endif
AMBA_DEVICE(uart1, "amba-uart.1", UART1, &uart_plat_data[1]);
AMBA_DEVICE(uart2, "amba-uart.2", UART2, &uart_plat_data[2]);
AMBA_DEVICE(uart3, "amba-uart.3", UART3, &uart_plat_data[3]);
AMBA_DEVICE(uart4, "amba-uart.4", UART4, &uart_plat_data[4]);
#endif


static struct amba_device *amba_uart_devs[] __initdata = {

#ifdef CONFIG_MACH_HI6210SFT
	&uart0_device,
	&uart3_device,
	&uart4_device,
#endif

#ifdef CONFIG_MACH_HI6210OEM
#if 0
    &uart0_device,
#endif
	&uart1_device,
	&uart2_device,
	&uart3_device,
	&uart4_device,
#endif

};


static int __initdata uart_console_enabled = 1;
static int __init uart_console_disable(char *__unused)
{
	uart_console_enabled = 0;

	return 0;
}
early_param("no_uart_console", uart_console_disable);


static void __init amba_uart_dev_init(void)
{
        int i = 1;
	edb_trace(1);

    if (uart_console_enabled){
		i = 0;
    }

	for (; i < ARRAY_SIZE(amba_uart_devs); i++) {
		struct amba_device *d = amba_uart_devs[i];
		amba_device_register(d, &iomem_resource);
	}
	edb_trace(1);
}

arch_initcall(amba_uart_dev_init);
