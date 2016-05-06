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

#ifndef _BSP_DR_H_
#define _BSP_DR_H_

#include "product_config.h"
#include "osl_types.h"
#ifdef CONFIG_PMU_NEW
#include "hi_dr.h"
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

/*error code*/
#define BSP_DR_OK              0
#define BSP_DR_ERROR          (-1)
#define BSP_DR_PARA_ERROR      0x2002/*无效参数值*/

typedef enum  _dr_mode_e
{
    PMU_DRS_MODE_FLA_FLASH = 0,     /*闪烁闪动模式(DR1/2/3/4/5)*/
    PMU_DRS_MODE_FLA_LIGHT ,        /*闪烁长亮模式(DR1/2/3/4/5)*/
    PMU_DRS_MODE_BRE ,              /*呼吸模式(DR3/4/5)*/
    PMU_DRS_MODE_BRE_FLASH ,        /*呼吸闪烁模式，高精度闪烁(DR1/2)*/
    PMU_DRS_MODE_BRE_LIGHT ,        /*呼吸长亮模式(DR1/2)*/
    PMU_DRS_MODE_BUTTOM
}dr_mode_e;

typedef enum  _dr_bre_time_e
{
    PMU_DRS_BRE_ON_MS = 0,      /*呼吸长亮时间(DR1/2/3/4/5)*/
    PMU_DRS_BRE_OFF_MS ,        /*呼吸长暗时间(DR1/2/3/4/5)*/
    PMU_DRS_BRE_RISE_MS ,       /*呼吸渐亮时间(DR1/2/3/4/5))*/
    PMU_DRS_BRE_FALL_MS ,       /*呼吸渐灭时间(DR1/2/3/4/5))*/
    PMU_DRS_BRE_TIME_BUTTOM
}dr_bre_time_e;

typedef struct
{
    unsigned int fla_on_us;     /*闪烁点亮时间*/
    unsigned int fla_off_us;    /*闪烁点亮时间*/
}DR_FLA_TIME;

typedef struct
{
    unsigned int bre_on_ms;
    unsigned int bre_off_ms;
    unsigned int bre_rise_ms;
    unsigned int bre_fall_ms;
}DR_BRE_TIME;

#define ALWAYS_ON_OFF_TIME_DR12     5000        /*长亮或者长暗寄存器配置值*/
#define ALWAYS_ON_OFF_TIME_DR345    50000       /*长亮或者长暗寄存器配置值*/
#define BRE_TIME_NOT_SURE           0xfffffe    
#define DR_VALUE_INVALIED           0xffffffff

#ifdef __KERNEL__
/*****************************************************************************
* 函 数 名  : bsp_dr_list_current
* 功能描述  :查询某路电流源指定档位电流。
* 输入参数  :dr_id:电流源id号；selector：要查询的档位；
* 输出参数  :无
* 返回值：   所查询的电流源指定档位的电流值（单位：uA）
*
*****************************************************************************/
int bsp_dr_list_current(int dr_id, unsigned selector);

/*****************************************************************************
* 函 数 名  : bsp_pmu_dr_set_mode
* 功能描述  :设置某路电流源模式。
* 输入参数  :dr_id:电流源id号；mode：设置的模式；
* 输出参数  :无
* 返回值：   成功或失败
*
*****************************************************************************/
int bsp_dr_set_mode(int dr_id, dr_mode_e mode);

/*****************************************************************************
* 函 数 名  : bsp_hi6551_dr_get_mode
* 功能描述  :获取某路电流源模式。
* 输入参数  :dr_id:电流源id号；
* 输出参数  :无
* 返回值：   电流源当前模式
*
*****************************************************************************/
dr_mode_e bsp_dr_get_mode(int dr_id);

/*****************************************************************************
 函 数 名  : bsp_dr_fla_time_set
 功能描述  : 设置dr的闪烁周期时间和点亮时间
 输入参数  : dr_fla_time_st:闪烁时间参数结构体;单位:us
 输出参数  : 无
 返 回 值  : 设置成功或者失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁
             闪烁周期:reg_value*31.25ms;点亮时间:reg_value*7.8125ms
*****************************************************************************/
int bsp_dr_fla_time_set(int dr_id, DR_FLA_TIME *dr_fla_time_st);
int bsp_dr_fla_time_get(int dr_id, DR_FLA_TIME *dr_fla_time_st);

/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_set
 功能描述  : 设置dr的呼吸时间(包括长亮，长暗、渐亮、渐暗时间)
 输入参数  : dr_id:要设置的电流源编号;dr_bre_time_st:呼吸时间参数结构体;
            没有找到设置的时间，就设置为长亮
 输出参数  : 无
 返 回 值  : 设置成功或者失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁
*****************************************************************************/
int bsp_dr_bre_time_set(int dr_id, DR_BRE_TIME *dr_bre_time_st);

/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_list
 功能描述  : 陈列dr的呼吸时间(包括长亮，长暗、渐亮、渐暗时间)各档位的时间值
 输入参数  : dr_id:要查询的电流源编号;bre_time_enum:所要查询的时间类型;
             selector，时间档位
 输出参数  : 无
 返 回 值  : 档位时间
 调用函数  :
 备注说明  :
*****************************************************************************/
unsigned bsp_dr_bre_time_list(int dr_id, dr_bre_time_e bre_time_enum ,unsigned selector);

/*****************************************************************************
 函 数 名  : bsp_dr_bre_time_selectors_get
 功能描述  : 获取dr 呼吸时间总共档位值
 输入参数  : dr_id:要设置的电流源编号;bre_time_enum:所要查询的时间类型;
 输出参数  : 无
 返 回 值  : 档位时间
 调用函数  :
 备注说明  :
*****************************************************************************/
unsigned bsp_dr_bre_time_selectors_get(int dr_id, dr_bre_time_e bre_time_enum);

/*****************************************************************************
 函 数 名  : bsp_dr_start_delay_set
 功能描述  : 设置dr的启动延时时间
 输入参数  : dr_id:要设置的电流源编号;delay_ms:启动延时的时间，单位:ms
             设置范围:[0 , 32768]ms
 输出参数  : 无
 返 回 值  : 设置成功或失败
 调用函数  :
 备注说明  : 对应寄存器只有设置时间的功能，不需要互斥锁，只有DR3/4/5有此功能
*****************************************************************************/
int bsp_dr_start_delay_set(int dr_id, unsigned delay_ms);
#else /* __FASTBOOT__ */
#ifdef CONFIG_PMU_NEW
void bsp_dr_init(void);
#else
void bsp_dr_init(void){}
#endif /* end #define CONFIG_PMU_NEW */
#endif /* end #define __KERNEL__ */
#endif /* end #define _BSP_DR_H_*/
