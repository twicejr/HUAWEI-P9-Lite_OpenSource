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

#ifndef __BSP_HARDTIMER_H__
#define __BSP_HARDTIMER_H__
#include <soc_timer.h>

#define TIMER_STAMP_FREQ        (0x8000)

#ifndef __ASSEMBLY__
#include <product_config.h>
#include <osl_common.h>
#include <osl_math64.h>
#include <mdrv_timer.h>
#include <bsp_slice.h>
#include <bsp_om.h>


/*32k timer 一个slice大约为31us*/
#define TIMER_32K_US_BOUNDARY           31
#define  Second_To_Millisecond                               1000

#define  hardtimer_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HARDTIMER, "timer: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))

struct bsp_hardtimer_control
{
	u32 timerId;
	u32 mode;
	u32 timeout;
	irq_handler_t func;
	void* para;
	DRV_TIMER_UNIT_E unit; /*计数单位*/
};



#ifdef CONFIG_MODULE_TIMER

/*****************************************************************************
* 函 数 名  :bsp_hardtimer_load_value
*
* 功能描述  : 载入timer计数初始值
*
*输入参数  :  timer_id,
						value:计数值
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  :  2013年9月16日   lixiaojie
*****************************************************************************/


void bsp_hardtimer_load_value(u32 timer_id, u32 value);

/*****************************************************************************
* 函 数 名  :bsp_hardtimer_config_init
*
* 功能描述  : 载入timer计数模式、计数初始值、挂接用户回调函数
*
*输入参数  :  struct bsp_hardtimer_control *my_hardtimer
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_config_init(struct bsp_hardtimer_control *my_hardtimer);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_start
*
* 功能描述  : 载入timer计数模式、计数初始值、挂接用户回调函数
					   同时使能定时器开始计数。
*输入参数  :  struct bsp_hardtimer_control *my_hardtimer  定时器配置参数结构体
                             unit  单位:0 毫秒，
                                                 1微秒 ，
                                                 2单位为1，即直接操作寄存器
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_start(struct bsp_hardtimer_control  *timer_ctrl);

/*****************************************************************************
* 函 数 名  :bsp_hardtimer_enable
*
* 功能描述  : 使能某hardtimer开始计数
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_enable(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_disable
*
* 功能描述  : 去使能某hardtimer开始计数
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_disable(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_free
*
* 功能描述  : disable掉硬timer，取消注册的回调函数
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_free(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_clear
*
* 功能描述  : 超时后会产生一个中断，本函数用于清除本次产生
*                           的中断
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  :
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_clear(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_mask
*
* 功能描述  : 屏蔽中断
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_mask(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_unmask
*
* 功能描述  : 不屏蔽中断
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_unmask(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_hardtimer_int_status
*
* 功能描述  : 查询中断状态
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : 寄存器中断状态
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/

u32 bsp_hardtimer_int_status(u32 timer_id);
/*****************************************************************************
* 函 数 名  :bsp_get_timer_current_value
*
* 功能描述  : 获取定时器计数寄存器当前值
*
* 输入参数  :  timer_id
* 输出参数  : 无
*
* 返 回 值  : 计数寄存器当前值
*
* 修改记录  :  2013年1月8日   lixiaojie
*****************************************************************************/
u32 bsp_get_timer_current_value(u32 timer_id);

/*****************************************************************************
* 函 数 名  :bsp_get_timer_rest_time
*
* 功能描述  : 根据传入参数，获取指定定时器以指定单位为单位的
*                           剩余时间
*
* 输入参数  : timer_id:定时器id
*                           unit:获取剩余时间单位
				*rest :rest time
* 输出参数  : 无
*
* 返 回 值  : 0:success;-1:error
*
* 修改记录  :  2013年6月20日   lixiaojie
*****************************************************************************/

int bsp_get_timer_rest_time(u32 timer_id, DRV_TIMER_UNIT_E unit,unsigned int *rest);

u32 get_next_schedule_time(void);

void bsp_timer_init(void);

#else
static inline void bsp_hardtimer_load_value(u32 timer_id, u32 value){}
static inline s32 bsp_hardtimer_config_init(struct bsp_hardtimer_control *my_hardtimer) {return 0;}
static inline s32 bsp_hardtimer_start(struct bsp_hardtimer_control  *timer_ctrl) {return 0;}
static inline s32 bsp_hardtimer_enable(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_disable(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_free(u32 timer_id) {return 0;}
static inline void bsp_hardtimer_int_clear(u32 timer_id) {}
static inline void bsp_hardtimer_int_mask(u32 timer_id) {}
static inline void bsp_hardtimer_int_unmask(u32 timer_id) {}
static inline u32 bsp_hardtimer_int_status(u32 timer_id) {return 0;}
static inline u32 bsp_get_timer_current_value(u32 timer_id) {return 0;}
static inline int bsp_get_timer_rest_time(u32 timer_id, DRV_TIMER_UNIT_E unit,unsigned int *rest) {return 0;}
static inline u32 get_next_schedule_time(void){return 0;}
static inline void bsp_timer_init(void){return;}
#endif/*CONFIG_MODULE_TIMER*/
void bsp_timer_iomap_and_clk_cfg(void);

#endif /*__ASSEMBLY__*/

#endif /*__BSP_HARDTIMER_H__*/


