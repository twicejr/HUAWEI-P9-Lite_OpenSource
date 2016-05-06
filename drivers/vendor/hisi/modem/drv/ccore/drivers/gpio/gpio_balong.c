/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_GPIO.c
*
*   作    者 :  liuwenhui
*
*   描    述 :  GPIO驱动文件 
*
*   修改记录 :  2012年11月27日
*
*************************************************************************/
/* includes */
/*lint -save -e537*/
#include <stdio.h>
#include <string.h>
#include "securec.h"
#include <osl_bio.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_err.h>
#include <soc_clk.h>

#include <hi_gpio.h>
#include <hi_gpio.h>
#include <bsp_memmap.h>
#include <bsp_ipc.h>
#include <bsp_clk.h>
#include <gpio_balong.h>
#include <bsp_dpm.h>
#include <bsp_om.h>
#include <of.h>

/*lint -restore */

#ifdef __cplusplus
extern "C" {
#endif
#define  OF_INTER_OFFSET               32
#define  NAME_LENTH                    32

#define  gpio_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[gpio]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  gpio_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO,  BSP_MODU_GPIO, "[gpio]: "fmt, ##__VA_ARGS__))

#ifndef HI_K3_GPIO

static spinlock_t g_gpio_spinlock;

/*是否初始化标志*/
static u32 g_u32GpioRunning = GPIO_DEF_NOT_RUNNING; /* GPIO是否初始化标志*/

/*每组GPIO基址*/
static u32 s_u32GpioBaseAddr[GPIO_MAX_BANK_NUM];
/*=
{
    HI_GPIO0_REGBASE_ADDR,
    HI_GPIO1_REGBASE_ADDR,
    HI_GPIO2_REGBASE_ADDR,
    HI_GPIO3_REGBASE_ADDR,

#if (GPIO_MAX_BANK_NUM == 6)
    HI_GPIO4_REGBASE_ADDR,
    HI_GPIO5_REGBASE_ADDR
#endif
};
*/
#ifdef CONFIG_CCORE_PM
static int bsp_gpio_suspend(struct dpm_device *dev)
{
	return OK;
}

static int bsp_gpio_resume(struct dpm_device *dev)
{
	return OK;
}

struct dpm_device gpio_device={
	.device_name = "balong gpio driver",
	.suspend_late = NULL,
	.prepare = NULL,
	.suspend = bsp_gpio_suspend,
	.resume = bsp_gpio_resume,
	.resume_early = NULL,
	.complete = NULL,
};

#endif

/*****************************************************************************
* 函 数 名  : bsp_gpio_init
*
* 功能描述  : GPIO初始化接口
*
* 输入参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
s32 bsp_gpio_init(void)
{
    u32  i = 0;
    int  ret = 0;
    char gpio_clk_name[40]       = "";
	char node_name[NAME_LENTH]   = "";
	char *base_addr              = NULL;	
    struct clk         *gpio_clk = NULL;
	struct device_node *dev_node = NULL;

    if (GPIO_DEF_RUNNING == g_u32GpioRunning)
    {
        return GPIO_OK;
    }

    spin_lock_init(&g_gpio_spinlock);

    for(i = 0; i < GPIO_MAX_BANK_NUM; i++)
    {
		(void)snprintf_s(node_name,NAME_LENTH,NAME_LENTH,"hisilicon,gpio%d",i);
		dev_node = of_find_compatible_node(NULL,NULL,node_name);
		if(!dev_node)
		{
			gpio_print_error("get gpio%d node failed!\n",i);
			return ERROR;
		}
		
		/* 内存映射，获得基址 */
		base_addr = (char *)of_iomap(dev_node, 0);
		if (NULL == base_addr)
		{
			gpio_print_error("gpio%d iomap fail\n",i);
			return ERROR;
		}
		s_u32GpioBaseAddr[i] = (u32)base_addr;
        (void)memset_s(gpio_clk_name, 40, 0 , 40);
        (void)snprintf_s(gpio_clk_name, 40, 40, "gpio%d_clk", i); /*lint !e119*/
        gpio_clk = (struct clk *)clk_get(NULL, gpio_clk_name);
    	if(IS_ERR(gpio_clk))
        {
    		gpio_print_error("gpio%d clk cannot get, 0x%x.\n", i, gpio_clk);
			return ERROR;
    	}

        ret = clk_enable(gpio_clk);

    }

    gpio_print_info("gpio init ok.\n");
    g_u32GpioRunning = GPIO_DEF_RUNNING;

    return ret;

}


/*****************************************************************************
* 函 数 名  : bsp_gpio_direction_input
*
* 功能描述  : 设置GPIO引脚方向为输入
*
* 输入参数  : UINT32 gpio    GPIO引脚编号
*
* 返 回 值  : 无
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
void bsp_gpio_direction_input(u32 gpio)
{
    u32 chip_num;
    u32 pin;
    u32 u32GpioAddr = 0;
    u32 gpio_value = 0;
    unsigned long irq_flags;

    /* 如果GPIO 没有初始化，返回错误 */
    if (GPIO_DEF_NOT_RUNNING == g_u32GpioRunning)
    {
        gpio_print_error(" GPIO is not inited.\n");
        return ;
    }

    if(gpio >= (u32)GPIO_TOTAL_PINS_NUM)
    {
        gpio_print_error(" GPIO parameter error.\n");
        return ;
    }
    chip_num   = gpio / (u32)GPIO_MAX_PINS;
    pin        = gpio % (u32)GPIO_MAX_PINS;

	if(chip_num < (u32)GPIO_MAX_BANK_NUM){
	    u32GpioAddr = s_u32GpioBaseAddr[chip_num];
	}
	else{
        gpio_print_error(" GPIO bank number error.\n");
        return ;
	}
    spin_lock_irqsave(&g_gpio_spinlock, irq_flags);
    (void)bsp_ipc_spin_lock(IPC_SEM_GPIO);

    gpio_value = readl(u32GpioAddr + HI_GPIO_SWPORT_DDR_OFFSET);

    writel(gpio_value & ~((u32)0x1 << pin), u32GpioAddr + HI_GPIO_SWPORT_DDR_OFFSET);

    (void)bsp_ipc_spin_unlock(IPC_SEM_GPIO);
    spin_unlock_irqrestore(&g_gpio_spinlock, irq_flags);
}

/*****************************************************************************
* 函 数 名  : bsp_gpio_direction_output
*
* 功能描述  : 设置GPIO引脚的方向为输出，并设置该引脚默认电平值
*
* 输入参数  : UINT32 gpio       GPIO引脚编号
*             UINT32 value      待设置电平值,即0为低电平，1为高电平
*
* 返 回 值  : 无
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
void bsp_gpio_direction_output(u32 gpio, u32 value)
{
    u32 chip_num;
    u32 pin;
    u32 u32GpioAddr = 0;
    u32 gpio_value = 0;
    unsigned long irq_flags;

    /* 如果GPIO 没有初始化，返回错误 */
    if (GPIO_DEF_NOT_RUNNING == g_u32GpioRunning)
    {
        gpio_print_error(" GPIO is not inited.\n");
        return ;
    }

    if(gpio >= GPIO_TOTAL_PINS_NUM)
    {
         gpio_print_error(" GPIO parameter error.\n");
        return ;
    }

    chip_num   = gpio / GPIO_MAX_PINS;
    pin        = gpio % GPIO_MAX_PINS;

	if(chip_num < GPIO_MAX_BANK_NUM){
	    u32GpioAddr = s_u32GpioBaseAddr[chip_num];
	}
	else{
        gpio_print_error(" GPIO bank number error.\n");
        return ;
	}

    spin_lock_irqsave(&g_gpio_spinlock, irq_flags);
    (void)bsp_ipc_spin_lock(IPC_SEM_GPIO);

    gpio_value = readl(u32GpioAddr + HI_GPIO_SWPORT_DDR_OFFSET);
    writel(gpio_value | ((u32)0x1 << pin), u32GpioAddr + HI_GPIO_SWPORT_DDR_OFFSET);

    (void)bsp_ipc_spin_unlock(IPC_SEM_GPIO);
    spin_unlock_irqrestore(&g_gpio_spinlock, irq_flags);

    bsp_gpio_set_value(gpio, value);

}

/*****************************************************************************
* 函 数 名  : bsp_gpio_direction_get
*
* 功能描述  : 查询GPIO 引脚的方向
*
* 输入参数  : UINT32 gpio        GPIO引脚编号
*
* 返 回 值  : 返回gpio引脚方向,即0为输入，1为输出
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
s32 bsp_gpio_direction_get(u32 gpio)
{
    u32 chip_num;
    u32 pin;
    u32 u32GpioAddr = 0;
    u32 gpio_value = 0;

    /* 如果GPIO 没有初始化，返回错误 */
    if (GPIO_DEF_NOT_RUNNING == g_u32GpioRunning)
    {
        gpio_print_error(" GPIO is not inited.\n");
        return GPIO_ERROR;
    }

    if(gpio >= (u32)GPIO_TOTAL_PINS_NUM)
    {
        gpio_print_error(" GPIO parameter error.\n");
        return GPIO_ERROR;
    }
    chip_num   = gpio / (u32)GPIO_MAX_PINS;
    pin        = gpio % (u32)GPIO_MAX_PINS;

	if(chip_num < GPIO_MAX_BANK_NUM){
    	u32GpioAddr = s_u32GpioBaseAddr[chip_num];
	}
	else{
        gpio_print_error(" GPIO bank number error.\n");
        return GPIO_ERROR;
	}

    gpio_value = readl(u32GpioAddr + HI_GPIO_SWPORT_DDR_OFFSET);

    return (s32)((gpio_value & ((u32)0x1 << pin)) >> pin);
}

/*****************************************************************************
* 函 数 名  : bsp_gpio_set_value
*
* 功能描述  : 设置GPIO 引脚的电平值
*
* 输入参数  : u32 gpio        GPIO引脚编号
*              u32 value      管脚高/低电平
*
* 返 回 值  : 无
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
void bsp_gpio_set_value(u32 gpio,u32 value)
{
    u32 chip_num;
    u32 pin;
    u32 u32GpioAddr = 0;
    u32 gpio_value = 0;
    unsigned long irq_flags;

    /* 如果GPIO 没有初始化，返回错误 */
    if (GPIO_DEF_NOT_RUNNING == g_u32GpioRunning)
    {
        gpio_print_error(" GPIO is not inited.\n");
        return ;
    }

    if(gpio >= GPIO_TOTAL_PINS_NUM)
    {
        gpio_print_error(" GPIO parameter error.\n");
        return;
    }

    /*检测GPIO方向是否输出，如果为输入，则返回错误*/
    if(0 == bsp_gpio_direction_get(gpio))
    {
        gpio_print_error(" GPIO direction error.\n");
        return;
    }

    chip_num   = gpio / (u32)GPIO_MAX_PINS;
    pin        = gpio % (u32)GPIO_MAX_PINS;

	if(chip_num < GPIO_MAX_BANK_NUM){

	    u32GpioAddr = s_u32GpioBaseAddr[chip_num];
	}
	else{
        gpio_print_error(" GPIO bank number error.\n");
		return ;
	}


    spin_lock_irqsave(&g_gpio_spinlock, irq_flags);
    (void)bsp_ipc_spin_lock(IPC_SEM_GPIO);

    gpio_value = readl(u32GpioAddr + HI_GPIO_SWPORT_DR_OFFSET);
    if(!!value)
    {
        writel(gpio_value | ((u32)0x1 << pin), u32GpioAddr + HI_GPIO_SWPORT_DR_OFFSET);
    }
    else
    {
        writel(gpio_value & ~((u32)0x1 << pin), u32GpioAddr + HI_GPIO_SWPORT_DR_OFFSET);
    }

    (void)bsp_ipc_spin_unlock(IPC_SEM_GPIO);
    spin_unlock_irqrestore(&g_gpio_spinlock, irq_flags);

}

/*****************************************************************************
* 函 数 名  : bsp_gpio_get_value
*
* 功能描述  : 查询GPIO引脚的电平值
*
* 输入参数  : UINT32 gpio        GPIO引脚编号
*
* 返 回 值  : 返回GPIO引脚的电平值
*
* 修改记录  : 2012年11月27日
*****************************************************************************/
s32 bsp_gpio_get_value(u32 gpio)
{
    u32 chip_num;
    u32 pin;
    u32 u32GpioAddr = 0;
    u32 gpio_value = 0;

    /* 如果GPIO 没有初始化，返回错误 */
    if (GPIO_DEF_NOT_RUNNING == g_u32GpioRunning)
    {
        gpio_print_error(" GPIO is not inited.\n");
        return GPIO_ERROR;
    }

    if(gpio >= (u32)GPIO_TOTAL_PINS_NUM)
    {
        gpio_print_error(" GPIO parameter error.\n");
        return GPIO_ERROR;
    }

    chip_num   = gpio / (u32)GPIO_MAX_PINS;
    pin        = gpio % GPIO_MAX_PINS;

	if(chip_num < GPIO_MAX_BANK_NUM){
	    u32GpioAddr = s_u32GpioBaseAddr[chip_num];
	}
	else{
        gpio_print_error(" GPIO bank number error.\n");
        return GPIO_ERROR;
	}

    /* 读取引脚的电平值 */
    gpio_value = readl(u32GpioAddr + HI_GPIO_SWPORT_DR_OFFSET);

    //return (s32)((gpio_value & ((u32)0x1 << pin)) >> pin);
    return !!(gpio_value & ((u32)0x1 << pin));

}

#else

// static u32 gpio_total[] = {GPIO_123, GPIO_124, GPIO_158, GPIO_159, GPIO_178, GPIO_179, 0xffffffff};

s32 bsp_gpio_init(void)
{
    /* 天线选择NV初始化 */
    if(0 != bsp_rf_switch_init())
    {
        gpio_print_error("bsp_rf_switch_init is fail.\n");
    }

    /* RF LDO NV初始化 */
    if(0 != bsp_ldo_gpio_init())
    {
        gpio_print_error("bsp_rf_switch_init is fail.\n");
        return -1;
    }

    return 0;
}

/*
 * Function name:get_gpio_group.
 * Discription:get GPIO's group. There are 26(0~25) groups GPIO in K3V2 solution,
 * use this function, you can know which group is your GPIO is belonged to.
 * Parameters:
 *      @ gpio_id:GPIO pin's number which is defined in gpio.h
 * return value:
 *      @ gpio group that your GPIO is belonged to.
 */
static unsigned int get_gpio_group(unsigned int gpio_id)
{
	unsigned int gpio_group = (gpio_id >> GPIO_GROUP_BIT);
	//lint --e{716}
	//lint --e{722}

	return gpio_group;
}

/*
 * Function name:get_gpio_group.
 * Discription:Get GPIO number in a group. There are 8(0~7) GPIO pins in one group
 * in K3V2 solution, use this function, you can know your GPIO' number.
 * Parameters:
 *      @ gpio_id:GPIO pin's number which is defined in gpio.h
 * return value:
 *      @ gpio number that your GPIO in a group.
 */
static unsigned int get_gpio_number(unsigned int gpio_id)
{
	unsigned int gpio_group = get_gpio_group(gpio_id);
	unsigned int gpio_number = gpio_id - (gpio_group << GPIO_GROUP_BIT);
	//lint --e{716}
	//lint --e{722}

	return gpio_number;
}


/*
 * Function name:get_gpio_base_addr.
 * Discription:Get GPIO base address. There are 26(0~25) GPIO groups
 * in K3V2 solution, each group corresponde to each different base address,
 * use this function, you can know your GPIO' base address.
 * Parameters:
 *      @ gpio_id:GPIO pin's number which is defined in gpio.h
 * return value:
 *      @ gpio address of your GPIO.
 */
static unsigned int get_gpio_base_addr(unsigned int gpio_id)
{
	unsigned int delta_addr = HI_GPIO0_REG_SIZE;
	unsigned int gpio_group = get_gpio_group(gpio_id);
	unsigned int gpio_base_addr;

	if (gpio_group < 22)
		gpio_base_addr = (HI_GPIO0_REGBASE_ADDR + gpio_group * delta_addr);
	else
		gpio_base_addr = (HI_GPIO22_REGBASE_ADDR + (gpio_group - 22) * delta_addr);

	return gpio_base_addr;
}

void bsp_gpio_direction_input(u32 gpio)
{
	unsigned int gpio_base_addr, gpio_number, reg_value_old, reg_value_new;

	gpio_number = get_gpio_number(gpio);
	if (gpio_number >= GPIO_MAX_NUMBER) {
		return;
	}

	gpio_base_addr = get_gpio_base_addr(gpio);

	reg_value_old  = readl(gpio_base_addr + GPIODIR);
	reg_value_new  = (~(0x1UL << gpio_number)) & reg_value_old;

	writel(reg_value_new, gpio_base_addr + GPIODIR);
}


void bsp_gpio_set_value(u32 gpio,u32 value)
{
    u32 gpio_base_addr = 0;
    u32 gpio_number = 0;
    u32 gpio_data_reg = 0;

    if(value > 1 || (gpio > GPIO_TOTAL))
    {
        gpio_print_error("para is error, gpio = %d, value = %d.\n", gpio, value);
        return ;
    }

    gpio_base_addr = get_gpio_base_addr(gpio);
	gpio_number = get_gpio_number(gpio);
	gpio_data_reg = ((unsigned int)0x1 << (gpio_number + 2));

	writel(value << gpio_number, gpio_base_addr + gpio_data_reg);

}

s32 bsp_gpio_direction_get(u32 gpio)
{
	unsigned int gpio_base_addr, gpio_number;

    if(gpio > GPIO_TOTAL)
    {
        gpio_print_error("para is error, gpio = %d.\n", gpio);
        return -1;
    }

	gpio_number = get_gpio_number(gpio);
	if (gpio_number >= GPIO_MAX_NUMBER)
    {
        gpio_print_error("para is error, gpio = %d.\n", gpio);
		return -1;
	}

	gpio_base_addr = get_gpio_base_addr(gpio);
	unsigned int reg_value  = readl(gpio_base_addr + GPIODIR);
	return (reg_value >> gpio_number) & 0x01;

}


s32 bsp_gpio_get_value(u32 gpio)
{
    s32 value = 0;

    u32 gpio_base_addr = 0;
    u32 gpio_number = 0;
    u32 gpio_data_reg = 0;

    if(gpio > GPIO_TOTAL)
    {
        gpio_print_error("para is error, gpio = %d.\n", gpio);
        return -1;
    }

	gpio_base_addr = get_gpio_base_addr(gpio);
	gpio_number = get_gpio_number(gpio);
	gpio_data_reg = ((unsigned int)0x1 << (gpio_number + 2));

	value = (s32)(readl(gpio_base_addr + gpio_data_reg) >> gpio_number);
	return value;

}

void bsp_gpio_direction_output(u32 gpio, u32 value)
{
	unsigned int gpio_base_addr = 0;
	unsigned int gpio_number = 0;
	unsigned int reg_value_old = 0;
	unsigned int reg_value_new = 0;

    if(value > 1 || gpio > GPIO_TOTAL)
    {
        gpio_print_error("para is error, gpio = %d, value = %d.\n", gpio, value);
        return ;
    }

	gpio_base_addr = get_gpio_base_addr(gpio);
	gpio_number = get_gpio_number(gpio);

	reg_value_old  = readl(gpio_base_addr + GPIODIR);

	reg_value_new  = (((unsigned int)0x1 << gpio_number)) | (reg_value_old);

	writel(reg_value_new, gpio_base_addr + GPIODIR);

    bsp_gpio_set_value( gpio, value);

}


#endif

int bsp_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags,
        const char *name)
{
    return 0;
}
int bsp_gpio_irq_mask(int gpio)
{
    return 0;
}
int bsp_gpio_irq_unmask(int gpio)
{
    return 0;
}
#ifdef __cplusplus
}
#endif

