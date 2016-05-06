/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_gpio.h
*
*   作    者 :  z00228752
*
*   描    述 :  GPIO模块接口文件，从V7R1 BSP_GPIO.h移植
*
*   修改记录 :  2012年11月27日
*************************************************************************/
#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <osl_irq.h>
#include <osl_types.h>
#include "hi_gpio.h"
/* GPIO状态*/
#define GPIO_OK                     0
#define GPIO_ERROR                  -1

#define GPIO_OUTPUT 1
#define GPIO_INPUT  0

#define GPIO_INVALID_IRQ 0xffffffff

#define IRQF_SHARED		         0x00000080
#define IRQ_TYPE_NONE		     0x00000000
#define IRQ_TYPE_EDGE_RISING	 0x00000001
#define IRQ_TYPE_EDGE_FALLING	 0x00000002
#define IRQ_TYPE_EDGE_BOTH	     (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#define IRQ_TYPE_LEVEL_HIGH      0x00000004
#define IRQ_TYPE_LEVEL_LOW	     0x00000008

typedef enum{
	MASTER_0 = 0,
	MASTER_1,
	NAGTIVE,
	GR_BUTT
}ANTN_SW_GROUP_E;

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
s32 bsp_gpio_init(void);

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
void bsp_gpio_direction_input(u32 gpio);

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
void bsp_gpio_direction_output(u32 gpio, u32 value);

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
s32 bsp_gpio_direction_get(u32 gpio);

/*****************************************************************************
* 函 数 名  : bsp_gpio_set_value
*
* 功能描述  : 设置GPIO 引脚的电平值
*
* 输入参数  : u32 gpio        GPIO引脚编号
*			  u32 value      管脚高/低电平
*
* 返 回 值  : 无
*
* 修改记录  : 2012年11月27日   
*****************************************************************************/
void bsp_gpio_set_value(u32 gpio,u32 value);

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
s32 bsp_gpio_get_value(u32 gpio);

/**/
void rf_gpio_set_high(void);
void rf_gpio_set_low(void);
int ldo_gpio123_get_value(void);
int ldo_gpio124_get_value(void);
int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux);
int bsp_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags,
	    const char *name);
int bsp_gpio_irq_mask(int gpio);
int bsp_gpio_irq_unmask(int gpio);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
