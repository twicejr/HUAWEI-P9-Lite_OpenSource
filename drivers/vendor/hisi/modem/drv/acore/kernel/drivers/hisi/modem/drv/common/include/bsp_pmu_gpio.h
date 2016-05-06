/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __BSP_PMU_GPIO_H__
#define __BSP_PMU_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_om.h>
#include <product_config.h>

#define  pgpio_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  pgpio_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_GPIO, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#define PMIC_GPIO_OUTPUT 1
#define PMIC_GPIO_INPUT  0
#define PMIC_GPIO_LOW   0
#define PMIC_GPIO_HIGH  1

typedef struct {
    unsigned int    dir_reg;
    unsigned int    data_reg;
    pmufuncptr     irq_handler;
    unsigned int    irq_num;
    const char*     name;
}PMU_GPIO_NODE_S;


typedef struct {
    PMU_GPIO_NODE_S *node;
    unsigned int    base;
    unsigned int    is_reg;              /*边沿或电平触发方式选择寄存器*/
    unsigned int    ibe_reg;            /*单沿或双沿触发方式寄存器*/
    unsigned int    iev_reg;            /*上升沿或下降沿边沿触发方式寄存器*/
    unsigned int    irq_mask_reg;  /*中断屏蔽寄存器*/
    spinlock_t       lock;
    unsigned int    num;                  /*当前支持pmu gpio管脚个数*/
    
}PMU_GPIO_INFO_S;


#ifdef CONFIG_PMU_GPIO
/*****************************************************************************
 函 数  : bsp_pmu_gpio_direction_output
 功 能  : 配置pmu gpio 输出的电平
 输 入  : gpio编号,输出的电平值
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_direction_output(unsigned int gpio_num, unsigned int value);
/*****************************************************************************
 函 数  : bsp_pmu_gpio_direction_input
 功 能  : 配置pmu gpio 方向为输入
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_direction_input(unsigned int gpio_num);

/*****************************************************************************
 函 数  : bsp_pmu_gpio_set_value
 功 能  : 配置pmu gpio 电平
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_set_value(unsigned int gpio_num, unsigned int value);

/*****************************************************************************
 函 数  : bsp_pmu_gpio_get_value
 功 能  : 获取pmu gpio 电平
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_get_value(unsigned int gpio_num);

/*****************************************************************************
 函 数  : bsp_pmu_gpio_request_irq
 功 能  : 挂接pmu gpio 中断
 输 入  : 
                 gpio_num: gpio编号
                 handler   : 回调
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_request_irq(unsigned int gpio_num,  pmufuncptr handler, unsigned long flags,  const char *name, void *bdata);

/*****************************************************************************
 函 数  : bsp_pmu_gpio_irq_mask
 功 能  : pmu gpio 中断屏蔽
 输 入  : pmu gpio 管脚编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_irq_mask(unsigned int gpio_num);

/*****************************************************************************
 函 数  : bsp_pmu_gpio_irq_mask
 功 能  : pmu gpio 中断去屏蔽
 输 入  : pmu gpio 管脚编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
extern int bsp_pmu_gpio_irq_unmask(unsigned int gpio_num);

#else
/*****************************************************************************
 函 数  : bsp_pmu_gpio_direction_output
 功 能  : 配置pmu gpio 输出的电平
 输 入  : gpio编号,输出的电平值
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_direction_output(unsigned int gpio_num, unsigned int value)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_direction_input
 功 能  : 配置pmu gpio 方向为输入
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_direction_input(unsigned int gpio_num)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_set_value
 功 能  : 配置pmu gpio 电平
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_set_value(unsigned int gpio_num, unsigned int value)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_get_value
 功 能  : 获取pmu gpio 电平
 输 入  : gpio编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_get_value(unsigned int gpio_num)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_request_irq
 功 能  : 挂接pmu gpio 中断
 输 入  : 
                 gpio_num: gpio编号
                 handler   : 回调
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_request_irq(unsigned int gpio_num,  pmufuncptr handler, unsigned long flags,  const char *name, void *bdata)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_irq_mask
 功 能  : pmu gpio 中断屏蔽
 输 入  : pmu gpio 管脚编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_irq_mask(unsigned int gpio_num)
{
    return 0;
}

/*****************************************************************************
 函 数  : bsp_pmu_gpio_irq_mask
 功 能  : pmu gpio 中断去屏蔽
 输 入  : pmu gpio 管脚编号
 输 出  : 无
 返 回  : 配置成功或失败

*****************************************************************************/
static inline int bsp_pmu_gpio_irq_unmask(unsigned int gpio_num)
{
    return 0;
}

#endif


#ifdef __cplusplus
}
#endif

#endif

