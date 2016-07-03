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
#ifndef _BSP_IPC_H_
#define _BSP_IPC_H_
#ifdef __ASSEMBLY__
#include <bsp_memmap.h>

/* c->m send ipc_int  addr & bit  */
//#define  PM_C2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
//#define  PM_C2M_IPC_BIT        (0x1<<17)
/* a->m send ipc_int  addr & bit  */
/*#define  PM_A2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)*/
//#define  PM_A2M_IPC_BIT        (0x1<<16)

#else

#include <product_config.h>
#include <osl_common.h>
#include <mdrv_ipc.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef void  (*voidfuncptr)(u32);
#define IPC_ERR_MODEM_RESETING 1
#define MODEM_RESET_HWLOCK_ID 10
#define  IPC_CPU_RAW_INT_M3   0x420

struct ipc_entry
{
 	voidfuncptr routine;
	u32	arg;
} ;

#define INTSRC_NUM                     32

#ifdef CONFIG_MODULE_IPC
/*****************************************************************************
* 函 数 名     : bsp_ipc_init
*
* 功能描述  : IPC模块初始化
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值     : 
*
* 修改记录  : 2013年1月9日   lixiaojie     
                          
*****************************************************************************/
void bsp_ipc_init(void);
/*****************************************************************************
* 函 数 名     : bsp_ipc_sem_create
*
* 功能描述  : 创建信号量
*
* 输入参数  :   u32 u32SignalNum 要创建的信号量编号

* 输出参数  : 无
*
* 返 回 值     : OK&ERROR
*
* 修改记录  : 2013年1月9日 lixiaojie 
*****************************************************************************/
s32 bsp_ipc_sem_create(u32 u32SignalNum);
/*****************************************************************************
* 函 数 名      : bsp_ipc_sem_delete
*
* 功能描述  : 删除信号量
*
* 输入参数  :   u32 u32SignalNum 要删除的信号量编号

* 输出参数  : 无
*
* 返 回 值     : OK&ERROR
*
* 修改记录  : 2013年1月9日 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_sem_delete(u32 u32SignalNum);
/*****************************************************************************
* 函 数 名     :bsp_ipc_int_enable
*
* 功能描述  : 使能某个中断
*
* 输入参数  :   u32 ulLvl 要使能的中断号，取值范围0～31  
* 输出参数  : 无
*
* 返 回 值     : OK&ERROR
*
* 修改记录  : 2013年1月8日    lixiaojie 
*****************************************************************************/

s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 * 函 数 名      : ipc_int_disable
 *
 * 功能描述  : 去使能某个中断
 *
 * 输入参数  : u32 ulLvl 要使能的中断号，取值范围0～31   
 * 输出参数  : 无
 *
 * 返 回 值      : OK&ERROR
 *
 * 修改记录  :  2013年1月8日 lixiaojie  
 *****************************************************************************/

s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 * 函 数 名     : bsp_ipc_int_connect
 *
 * 功能描述  : 注册某个中断
 *
 * 输入参数  : u32 ulLvl 要使能的中断号，取值范围0～31 
                              routine 中断服务程序
 *                            u32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值      : OK&ERROR
 *
 * 修改记录  : 2013年1月9日 lixiaojie
 *****************************************************************************/

s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter);
/*****************************************************************************
 * 函 数 名     : bsp_ipc_int_disconnect
 *
 * 功能描述  : 取消注册某个中断
 *
 * 输入参数  : u32 ulLvl 要使能的中断号，取值范围0～31 
 *                           voidfuncptr routine 中断服务程序
 *                           u32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值      : OK&ERROR
 *
 * 修改记录  : 2013年1月9日 lixiaojie 
 *****************************************************************************/   

s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter);
/*****************************************************************************
* 函 数 名      : bsp_ipc_int_send
*
* 功能描述  : 发送中断
*
* 输入参数  : ipc_int_core enDstore 要接收中断的core
                             u32 ulLvl 要发送的中断号，取值范围0～31  
* 输出参数  : 无
*
* 返 回 值      :  OK&ERROR
*
* 修改记录  :  2013年1月9日 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 * 函 数 名     : bsp_ipc_sem_take
 *
 * 功能描述  : 获取信号量
 *
 * 输入参数  : u32SignalNum 要获取的信号量ID
                                s32timeout  超时时间,tick为单位，一个tick为10ms
 * 输出参数  : 无
 *
 * 返 回 值      : OK&ERROR
 *
 * 修改记录  : 2013年1月9日 lixiaojie 
 *****************************************************************************/

s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout);
/*****************************************************************************
 * 函 数 名     : bsp_ipc_sem_give
 *
 * 功能描述  : 释放信号量
 *
 * 输入参数  : u32SignalNum 要获取的信号量
 					    s32timeout  以10ms为单位的超时时间
 * 输出参数  : 无
 *
 * 返 回 值      :OK&&ERROR
 *
 * 修改记录  : 2013年1月9日 lixiaojie 
 *****************************************************************************/

s32 bsp_ipc_sem_give(u32 u32SignalNum);
/*****************************************************************************
* 函 数 名     : bsp_ipc_spin_lock
*
* 功能描述  : 查询等待获取信号量,在使用本函数前需要锁中断，
			建议使用带锁中断功能的bsp_ipc_spin_lock_irqsave函数
*
* 输入参数  : u32SignalNum 要获取的信号量
* 输出参数  : 无
*
* 返 回 值      :ERROR&OK
*
* 修改记录  :  2013年1月8日 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_spin_lock (u32 u32SignalNum);

/*****************************************************************************
* 函 数 名     : bsp_ipc_spin_trylock
*
* 功能描述  : 尝试获取信号量,不循环等待
*
* 输入参数  : u32SignalNum 要获取的信号量
* 输出参数  : 无
*
* 返 回 值      :ERROR&OK
*
* 修改记录  :  2014年11月11日 huangxianke 
*****************************************************************************/
s32 bsp_ipc_spin_trylock (u32 u32SignalNum);

/*****************************************************************************
* 函 数 名      : bsp_ipc_spin_unlock
*
* 功能描述  : 释放信号量，与bsp_ipc_spin_lock搭配使用，用后需要开中断，
			建议使用带开中断功能的bsp_ipc_spin_unlock_irqrestore函数
*
* 输入参数  : u32SignalNum  要释放的信号量
* 输出参数  : 无
*
* 返 回 值      : OK&ERROR
*
* 修改记录  :  2013年1月9日 lixiaojie
*****************************************************************************/
s32 bsp_ipc_spin_unlock (u32 u32SignalNum);

/*****************************************************************************
* 函 数 名  : bsp_ipc_spin_lock_timeout_irqsave
*
* 功能描述  : 在超时时间内锁中断并查询等待获取信号量
*
* 输入参数  : u32SignalNum:要获取的信号量
              TimeoutMs:超时时间，单位为毫秒
			  flags:锁中断标志，
					注意: 获取成功与bsp_ipc_spin_unlock_irqrestore配对使用
						  获取失败不需要bsp_ipc_spin_unlock_irqrestore
						  参考spin_lock_irqsave用法
* 输出参数  : 无
*
* 返 回 值  : MDRV_ERROR&MDRV_OK
*
* 修改记录  : 2016年2月26日 nieluhua 
*****************************************************************************/
s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags);

/*****************************************************************************
* 函 数 名     : bsp_ipc_spin_lock_irqsave
*
* 功能描述  : 锁中断并查询等待获取信号量
*
* 输入参数  : u32SignalNum 要获取的信号量
						flags:锁中断标志，与bsp_ipc_spin_unlock_irqrestore配对使用，
						这两个宏只能在同一个函数内部同时前后被调用，
						参考spin_lock_irqsave用法
* 输出参数  : 无
*
* 返 回 值      :ERROR&OK
*
* 修改记录  :  2013年5月8日 lixiaojie 
*****************************************************************************/

#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
	do{local_irq_save(flags);(void)bsp_ipc_spin_lock(u32SignalNum);}while(0)
/*****************************************************************************
* 函 数 名     : bsp_ipc_spin_unlock_irqrestore
*
* 功能描述  :开中断并释放获得的信号量
*
* 输入参数  : u32SignalNum 要获取的信号量
					flags:锁中断标志，与bsp_ipc_spin_lock_irqsave配对使用，
						这两个宏只能在同一个函数内部同时前后被调用，
						参考spin_unlock_irqrestore用法
* 输出参数  : 无
*
* 返 回 值      :ERROR&OK
*
* 修改记录  :  2013年5月8日 lixiaojie 
*****************************************************************************/

#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
	do{(void)bsp_ipc_spin_unlock(u32SignalNum);local_irq_restore(flags);}while(0)
#else
static inline s32 bsp_ipc_init(void) {return 0;}
static inline s32 bsp_ipc_sem_create(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_sem_delete(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout) {return 0;}
static inline s32 bsp_ipc_sem_give(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_trylock(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_unlock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags); {return 0;}
#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
	do{flags = flags;}while(0)
#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
	do{flags = flags;}while(0)

static inline void bsp_ipc_suspend(void){return ;}

static inline void bsp_ipc_resume(void){return ;}
#endif
/*****************************************************************************
* 函 数 名     : bsp_int_send_info
*
* 功能描述  :查看往每个核发送每个中断次数
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值      :无
*
* 修改记录  :  2013年5月10日 lixiaojie 
*****************************************************************************/

void bsp_int_send_info(void);
#ifdef __CMSIS_RTOS
/*****************************************************************************
* 函 数 名	: bsp_ipc_suspend
*
* 功能描述	:IPC设备下电前保存寄存器
*
* 输入参数	: 无
* 输出参数	: 无
*
* 返 回 值		:
*
* 修改记录	:  2013年6月14日 lixiaojie 
*****************************************************************************/
void bsp_ipc_suspend(void);
/*****************************************************************************
* 函 数 名	: bsp_ipc_resume
*
* 功能描述	:IPC设备上电后恢复寄存器
*
* 输入参数	: 无
* 输出参数	: 无
*
* 返 回 值		:0: success
						 -1:fail
*
* 修改记录	:  2013年6月14日 lixiaojie 
*****************************************************************************/
void bsp_ipc_resume(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifdef __ASSEMBLY__*/

#endif /* end #define _BSP_IPC_H_*/
