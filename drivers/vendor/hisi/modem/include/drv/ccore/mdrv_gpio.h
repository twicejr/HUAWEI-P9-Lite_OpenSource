#ifndef __MDRV_CCORE_GPIO_H__
#define __MDRV_CCORE_GPIO_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"

/*查询和设置GPIO电平。*/
typedef enum GPIO_OPRT_ENUM
{
    GPIO_OPRT_SET = 0,
    GPIO_OPRT_GET,
    GPIO_OPRT_BUTT
}GPIO_OPRT_E;

/*管脚复用配置。*/
typedef enum MODEM_PIN_MUX_ENUM
{
    MODEM_PIN_MUX_GPIO = 0,
    MODEM_PIN_MUX_ANTEN,
    MODEM_PIN_MUX_BUTT
}MODEM_PIN_MUX_E;

#define GPIO_IRQ_TYPE_NONE		     0x00000000
#define GPIO_IRQ_TYPE_EDGE_RISING	 0x00000001/*上升沿触发*/
#define GPIO_IRQ_TYPE_EDGE_FALLING	 0x00000002/*下降沿触发*/
#define GPIO_IRQ_TYPE_EDGE_BOTH	     (GPIO_IRQ_TYPE_EDGE_FALLING | GPIO_IRQ_TYPE_EDGE_RISING)
#define GPIO_IRQ_TYPE_LEVEL_HIGH     0x00000004/*高电平触发*/
#define GPIO_IRQ_TYPE_LEVEL_LOW	     0x00000008/*低电平触发*/

/*****************************************************************************
	 *  函 数 名  : mdrv_gpio_oprt
	 *  功能描述  :  设置和查询GPIO的电平。
	 *  输入参数  : ulOp : 1:设置/0:查询
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL);

/*1.	mdrv_set_os_status
2.	mdrv_get_board_info
待确认*/

/*****************************************************************************
	 *	函 数 名  : mdrv_gpio_irq_enable
	 *	功能描述  : gpio中断时能
	 *	输入参数  : gpio gpio编号
	 *
	 *	输出参数  : 无
	 *	返 回 值  :  0		   操作成功。
	 *	             其他	   操作失败。
	 *
	 ******************************************************************************/
int mdrv_gpio_irq_enable(int gpio);
/*****************************************************************************
	 *	函 数 名  : mdrv_gpio_irq_disable
	 *	功能描述  : gpio中断去时能
	 *	输入参数  : gpio gpio编号
	 *
	 *	输出参数  : 无
	 *	返 回 值  :  0		   操作成功。
	 *	             其他	   操作失败。
	 *
	 ******************************************************************************/
int mdrv_gpio_irq_disable(int gpio);

/*****************************************************************************
	 *	函 数 名  : mdrv_gpio_request_irq
	 *	功能描述  : gpio中断注册
	 *	输入参数  : gpio gpio编号
	 *              handler 回调函数
	 *              flags   触发类型
	 *              name    名称
	 *
	 *	输出参数  : 无
	 *	返 回 值  :  0		   操作成功。
	 *	             其他	   操作失败。
	 *
	 ******************************************************************************/
int mdrv_gpio_request_irq(int gpio, pFUNCPTR handler, unsigned long flags,
	    const char *name);
/*****************************************************************************
	 *	函 数 名  : mdrv_gpio_get_value
	 *	功能描述  : 获取gpio电平
	 *	输入参数  : gpio gpio编号
	 *
	 *	输出参数  : 无
	 *	返 回 值  :  0		   操作成功。
	 *	             其他	   操作失败。
	 *
	 ******************************************************************************/
int mdrv_gpio_get_value(int gpio);
#ifdef __cplusplus
}
#endif

#endif

