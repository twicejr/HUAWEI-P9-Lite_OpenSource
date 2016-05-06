#include <mach/dma.h>
#include <mach/irqs.h>
#include <linux/i2c/designware.h>
#include <linux/platform_device.h>
#include <linux/stringify.h>
#include "reg_ops.h"
#include <mach/platform.h>
#if defined(CHIP_BB_HI6210)
#else
#include "soc_sctrl_interface.h"
#endif
#include "soc_peri_sctrl_interface.h"
#include <linux/mux.h>

/*i2c device declare and register*/

#if 0
MODULE_FUNCS_DELAY_SDA_DEFINE(I2C0)
MODULE_FUNCS_DELAY_SDA_DEFINE(I2C1)
MODULE_FUNCS_RESET_CONTROLLER_DEFINE(I2C0)
MODULE_FUNCS_RESET_CONTROLLER_DEFINE(I2C1)
MODULE_FUNCS_DEFINE(I2C0)
MODULE_FUNCS_DEFINE(I2C1)
MODULE_RESET_DEFINE(I2C0)
MODULE_RESET_DEFINE(I2C1)
#endif


#define I2C_RESET_CONTROLLER_TIMEOUT    10

/*add i2c1 for ts use*/
#define I2C_INIT_FUNC(chip_id, reg_name) \
static void I2C ## chip_id ## _init(void)\
{\
    unsigned int ret;\
    unsigned int timeout = I2C_RESET_CONTROLLER_TIMEOUT;\
\
    phy_reg_writel(REG_BASE_SC_OFF,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(CALC_REG_OFFSET),\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_ ## reg_name ## _START,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_ ## reg_name ## _END, 1);\
\
    while (timeout--) { \
        ret = phy_reg_readl(REG_BASE_SC_OFF, \
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_ADDR(CALC_REG_OFFSET),\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## reg_name ## _START,\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## reg_name ## _END);\
        \
        if ((!timeout) && ret){\
            printk(KERN_ERR "i2c %d clock rst disable fail\n", chip_id);\
        } else if (!ret){\
            break;\
        }\
    } \
}

#define I2C_EXIT_FUNC(chip_id,reg_name) \
static void I2C ## chip_id ## _exit(void)\
{\
    unsigned int ret;\
    unsigned int timeout = I2C_RESET_CONTROLLER_TIMEOUT;\
\
    phy_reg_writel(REG_BASE_SC_OFF,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTEN3_ADDR(CALC_REG_OFFSET),\
        SOC_PERI_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_ ## reg_name ## _START,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_ ## reg_name ## _END, 1);\
\
    while (timeout--) { \
        ret = phy_reg_readl(REG_BASE_SC_OFF, \
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_ADDR(CALC_REG_OFFSET),\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## reg_name ## _START,\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_ ## reg_name ## _END);\
        \
        if ((!timeout) && (!ret)){\
            printk(KERN_ERR "i2c %d clock rst enable fail\n", chip_id);\
        } else if (ret){\
            break;\
        }\
    } \
}

#define I2C_RESET_FUNC(chip_id) \
static void I2C ## chip_id ## _reset()\
{\
    /*to do*/\
    return;\
}

#define I2C_RESET_CONTROLLER_FUNC(chip_id) \
static void I2C ## chip_id ## _reset_controller()\
{\
    /*to do*/\
    return;\
}

I2C_INIT_FUNC(0, i2c0)
I2C_INIT_FUNC(1, i2c1)
I2C_INIT_FUNC(2, i2c2)
I2C_INIT_FUNC(3, i2c3)

I2C_EXIT_FUNC(0,i2c0)
I2C_EXIT_FUNC(1,i2c1)
I2C_EXIT_FUNC(2,i2c2)
I2C_EXIT_FUNC(3,i2c3)

I2C_RESET_FUNC(0)
I2C_RESET_FUNC(1)
I2C_RESET_FUNC(2)
I2C_RESET_FUNC(3)


I2C_RESET_CONTROLLER_FUNC(0)
I2C_RESET_CONTROLLER_FUNC(1)
I2C_RESET_CONTROLLER_FUNC(2)
I2C_RESET_CONTROLLER_FUNC(3)

#define I2C_PLATFORM_DATA_DEFINE(chip_id) \
static struct i2c_dw_data i2c ## chip_id ## _plat_data = {\
	.dma_filter = NULL,\
	.dma_rx_param = NULL,\
	.dma_tx_param = NULL,\
	.init = I2C ## chip_id ## _init,\
	.exit = I2C ## chip_id ## _exit,\
	.reset = I2C ## chip_id ## _reset,\
	.delay_sda = NULL,\
	.reset_controller = I2C ## chip_id ## _reset_controller,\
	.iomux_name = "block_i2c" __stringify(chip_id),\
};\
\
static struct resource i2c_resource ## chip_id[] = {\
	[0] = {\
		.start = REG_BASE_I2C ## chip_id,\
		.end = REG_BASE_I2C ## chip_id + REG_I2C ## chip_id ## _IOSIZE - 1,\
		.flags = IORESOURCE_MEM,\
	},\
	[1] = {\
		.start = IRQ_I2C ## chip_id,\
		.end = IRQ_I2C ## chip_id,\
		.flags = IORESOURCE_IRQ,\
	},\
};\
\
static struct platform_device plat_i2c_device ## chip_id = {\
	.name = "i2c_designware",\
	.id = chip_id,\
	.resource = i2c_resource ## chip_id,\
	.num_resources = ARRAY_SIZE(i2c_resource ## chip_id),\
	.dev = {\
		.platform_data = &i2c ## chip_id ## _plat_data,\
		.init_name = "dw-i2c." __stringify(chip_id),\
	},\
};

I2C_PLATFORM_DATA_DEFINE(0)
I2C_PLATFORM_DATA_DEFINE(1)
I2C_PLATFORM_DATA_DEFINE(2)
I2C_PLATFORM_DATA_DEFINE(3)

/* please add platform device in the struct.*/
static struct platform_device *i2c_devices[] __initdata = {
	&plat_i2c_device0,
	&plat_i2c_device1,
	&plat_i2c_device2,
	&plat_i2c_device3,
};

static int __init plat_i2c_dev_init(void)
{
	/* platform devices were addded here. */
	platform_add_devices(i2c_devices, ARRAY_SIZE(i2c_devices));

    printk("plat_i2c_dev_init");

	return 0;
}

#if defined(RUN_IN_EMULATOR)

#else
arch_initcall(plat_i2c_dev_init);
#endif

