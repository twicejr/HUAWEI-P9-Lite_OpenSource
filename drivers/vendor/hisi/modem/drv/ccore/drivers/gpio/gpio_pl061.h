/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  GPIO_pl061.h
*
*   作    者 :  z00228752
*
*   描    述 :  GPIO模块接口文件，从V7R1 BSP_GPIO.h移植
*
*   修改记录 :  2012年11月27日
*************************************************************************/
#ifndef _GPIO_PL061_H_
#define _GPIO_PL061_H_

#ifdef __cplusplus
extern "C" {
#endif

#define  OF_INTER_OFFSET               32
#define  NAME_LENTH                    32

#define  gpio_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[gpio]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  gpio_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[gpio]: "fmt, ##__VA_ARGS__))

struct gpio_pl061{
    void*         base;
	u32           irq;
	const char*   name[PL061_GPIO_NR];
	irq_handler_t handler[PL061_GPIO_NR];
    spinlock_t    lock;
    struct clk*   clk;
}; 

typedef struct{
    struct gpio_pl061 *group;     /*gpio 信息*/
    unsigned int       group_num; /*gpio 组数*/
    unsigned int       max_pin;   /*gpio 每组管脚数*/
    unsigned int       clk_flag;  /*clk是否要非用即关*/
}GPIO_INFO_S;

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
