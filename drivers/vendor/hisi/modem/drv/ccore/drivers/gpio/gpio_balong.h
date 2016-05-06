/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  GPIO.h
*
*   作    者 :  liuwenhui
*
*   描    述 :  GPIO模块接口文件，从V7R1 BSP_GPIO.h移植
*
*   修改记录 :  2012年11月27日
*************************************************************************/
#ifndef _GPIO_BALONG_H_
#define _GPIO_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_gpio.h"
#include "osl_types.h"
#include "bsp_memmap.h"

/* GPIO状态*/
#define GPIO_OK                     0
#define GPIO_ERROR                  -1


/* GPIO是否初始化标志*/
#define GPIO_DEF_NOT_RUNNING        0
#define GPIO_DEF_RUNNING            1

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

void rf_gpio_set_high(void);

void rf_gpio_set_low(void);

int ldo_gpio123_get_value(void);

int ldo_gpio124_get_value(void);

int bsp_rf_switch_init(void);

int bsp_ldo_gpio_init(void);

int bsp_rse_gpio_set(unsigned int flag, unsigned int mask, unsigned int value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
