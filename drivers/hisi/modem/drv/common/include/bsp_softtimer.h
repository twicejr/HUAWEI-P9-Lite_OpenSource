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

#ifndef __BSP_SOFTTIMER_H__
#define __BSP_SOFTTIMER_H__

#include <osl_common.h>
#include <osl_list.h>
#include <product_config.h>
typedef void (*softtimer_func)(u32);
#define TIMER_TRUE 1
#define TIMER_FALSE 0
#define TIMER_INIT_FLAG     0X5A5A5A5A
/*结构体和枚举定义*/
enum wakeup
{
    SOFTTIMER_WAKE,
    SOFTTIMER_NOWAKE
};
struct softtimer_list
{
   softtimer_func func;
   u32 para;
   u32 timeout;
   enum wakeup wake_type;
   
   /*使用者不用关注和配置以下信息*/
   struct list_head entry;
   u32 timer_id;
   u32 count_num;/*原始配置起始计数时间*/
   u32 is_running;
   u32 init_flags;
};

#ifdef CONFIG_MODULE_TIMER
int  bsp_softtimer_init(void);
/*****************************************************************************
* 函 数 名  :bsp_softtimer_create_timer
*
* 功能描述  : 创建一个软timer，分配软timer id，
*
* 输入参数  :  要softtimer  创建的软timer的信息
* 输出参数  : 无
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年2月28日   lixiaojie     
*****************************************************************************/
s32 bsp_softtimer_create(struct softtimer_list *softtimer);
/*****************************************************************************
* 函 数 名  :     bsp_softtimer_delete
*
* 功能描述  : 从软timer队列删除一个还没有到超时时间的
                            单次执行的定时器
*
* 输入参数  :  timer 要删除的timer 
                             的参数
* 输出参数  : 无
*
* 返 回 值  :     0   删除成功
                             1   要删除的定时器不在超时队列
                             -1 传入的timer指针为空
*
* 修改记录  :  2013年2月28日   lixiaojie     
*****************************************************************************/
s32 bsp_softtimer_delete(struct softtimer_list * softtimer);

/*****************************************************************************
* 函 数 名  :bsp_softtimer_modify
*
* 功能描述  : 修改软timer超时时间，修改完成后，需要调用
*                           bsp_softtimer_add进行添加操作
*
* 输入参数  :  timer: 要修改的软timer，为bsp_softtimer_create_timer函数传出
                             的参数
                             new_expire_time: 新超时时间
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 修改记录  :  2013年2月28日   lixiaojie     
*****************************************************************************/

s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time);
/*****************************************************************************
* 函 数 名  :   bsp_softtimer_add
*
* 功能描述  : 将softtimer加入超时队列，如果超时定时器需要多次重复执行，
*                           需要在回调函数中调用本接口进行添加操作
*
* 输入参数  :  要加入队列的定时器指针
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  :  2013年2月28日   lixiaojie     
*****************************************************************************/

void bsp_softtimer_add(struct softtimer_list * timer);
/*****************************************************************************
* 函 数 名  :bsp_softtimer_free
*
* 功能描述  : 释放定时器占用的资源
*
* 输入参数  :  要释放的定时器指针
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 修改记录  :  2013年2月28日   lixiaojie     
*****************************************************************************/

s32 bsp_softtimer_free(struct softtimer_list *timer);
/*****************************************************************************
* 函 数 名  :check_softtimer_support_type
*
* 功能描述  : 检查支持对应的软件定时器类型
*
* 输入参数  :  软件定时器类型
* 输出参数  : 无
*
* 返 回 值  : 1:支持；0:不支持
*
* 修改记录  :  2015年9月2日   lixiaojie     
*****************************************************************************/

u32 check_softtimer_support_type(enum wakeup type);

#else
static inline int  bsp_softtimer_init(void) {return 0;}
static inline s32  bsp_softtimer_create(struct softtimer_list *softtimer) {return 0;}
static inline s32 bsp_softtimer_delete(struct softtimer_list * softtimer) {return 0;}
static inline s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time) {return 0;}
static inline void bsp_softtimer_add(struct softtimer_list * timer) {}
static inline s32 bsp_softtimer_free(struct softtimer_list *timer) {return 0;}
static inline u32 check_softtimer_support_type(enum wakeup type){return 0;}

#endif
#endif
