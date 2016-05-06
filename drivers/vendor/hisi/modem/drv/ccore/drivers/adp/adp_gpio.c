/*lint -save -e537*/
#include <product_config.h>
#include <hi_gpio.h>
#include <mdrv_gpio.h>
#include <bsp_gpio.h>


/*lint -restore */

#define  GPIO_OPRT_ERROR    (-1)
#ifdef CONFIG_PASTAR
/*天线开关不下电特性开关，只在k3中使用，v7R2不涉及*/
unsigned int  sw_unpd_en = 0;
int bsp_rf_ldo_init(void)
{
    return -1;
}

void rf_gpio_set_high(void)
{
    return;
}

void rf_gpio_set_low(void)
{
    return;
}

int ldo_gpio123_get_value(void)
{

    return -1;
}

int ldo_gpio124_get_value(void)
{

    return -1;
}


int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux)
{
    return 0;
}

#endif
#ifndef HI_K3_GPIO
/*****************************************************************************
 函 数 名  : mdrv_gpio_oprt
 功能描述  : at^GPIOPL,设置和查询GPIO的电平
 输入参数  : 操作类型 ulOp:
             0  设置各GPIO的PL值
             1  查询当前各GPIO的PL值

             pucPL 对应20Byte的数组,每个BYTE代表一个8个管脚的值

             设置操作时,pucPL为设置的20的Byte
             查询操作时,pucPL为当前获取到的PL的实际值组成的16进制数据
             例如用户设置at^GPIOPL = ABCDEF,则对应pucPL的数组值为{A,B,C,D,E,F,0,0,...}

 输出参数  : 无
 返 回 值  :  0 ：OK  非 0 ：Error

*****************************************************************************/
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int bype_pin = 8;
    int          value = 0;

    if(NULL == pucPL)
    {
        return GPIO_OPRT_ERROR;
    }
    
    if(GPIO_OPRT_SET == ulOp)
    {
        for(i = 0;i < GPIO_MAX_BANK_NUM * GPIO_MAX_PINS / bype_pin;i++)
        {
            for(j = 0;j < bype_pin;j++)
            {
                /*lint -save -e701*/
                if(pucPL[i] & (0x1 << j))
                {
                    bsp_gpio_set_value(i * bype_pin + j, 1);
                }
                /*lint -restore */

            }
        }
    }
    else if(GPIO_OPRT_GET == ulOp)
    {
        for(i = 0;i < GPIO_MAX_BANK_NUM * GPIO_MAX_PINS / bype_pin;i++)
        {
            pucPL[i] = 0;
            for(j = 0;j < bype_pin;j++)
            {
                value = bsp_gpio_get_value(i * bype_pin + j);
                if(GPIO_ERROR == value)
                {
                    continue;
                }
                pucPL[i] = (unsigned char)(pucPL[i] | ( (unsigned int)value << j));
            }
        }
    }
    
    return 0;
}
#else
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL)
{
    return 0;
}
#endif

int mdrv_gpio_irq_enable(int gpio)
{
    return bsp_gpio_irq_unmask(gpio);
}

int mdrv_gpio_irq_disable(int gpio)
{
    return bsp_gpio_irq_mask(gpio);
}

int mdrv_gpio_request_irq(int gpio, pFUNCPTR handler, unsigned long flags,
	    const char *name)
{
    return bsp_gpio_request_irq(gpio, (irq_handler_t)handler, flags, name);
}

int mdrv_gpio_get_value(int gpio)
{
    return bsp_gpio_get_value((unsigned int)gpio);
}
