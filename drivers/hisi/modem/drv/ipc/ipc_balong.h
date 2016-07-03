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

#ifndef _IPC_BALONG_H_
#define _IPC_BALONG_H_
#include <bsp_ipc.h>
#include <osl_irq.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BSP_IPC_CPU_RAW_INT(i)		(0x400 + (i * 0x10))
#define BSP_IPC_CPU_INT_MASK(i)		(0x404 + (i * 0x10))
#define BSP_IPC_CPU_INT_STAT(i)		(0x408 + (i * 0x10))
#define BSP_IPC_CPU_INT_CLR(i)		(0x40C + (i * 0x10))

#define BSP_IPC_SEM_RAW_INT(i)		(0x600 + (i * 0x10))
#define BSP_IPC_SEM_INT_MASK(i)		(0x604 + (i * 0x10))
#define BSP_IPC_SEM_INT_STAT(i)		(0x608 + (i * 0x10))
#define BSP_IPC_SEM_INT_CLR(i)		(0x60C + (i * 0x10))

#define BSP_IPC_HS_CTRL(i,j)		(0x800 + (i * 0x100) + (j * 0x8 ))
#define BSP_IPC_HS_STAT(i,j)		(0x804 + (i * 0x100) + (j * 0x8 ))



#ifndef SEM_FULL
#define SEM_FULL            (1)
#endif
#ifndef SEM_EMPTY
#define SEM_EMPTY           (0)
#endif

struct ipc_debug_s
{
	u32 u32RecvIntCore;										/*当前发送中断目标核ID*/
	u32 u32IntHandleTimes[INTSRC_NUM];						/*记录某号中断接收次数*/
	u32 u32IntSendTimes[IPC_CORE_BUTTOM][INTSRC_NUM];		/*记录往每个核发送每个中断的次数*/
	u32 u32SemId;											/*当前占用信号量*/
	u32 u32SemTakeTimes[INTSRC_NUM];						/*某信号量占用成功次数*/
	u32 u32SemTakeFailTimes[INTSRC_NUM];					/*某信号量占用失败次数*/
	u32 u32SemGiveTimes[INTSRC_NUM];						/*某信号量释放次数*/
	u32 u32IntTimeDelta[INTSRC_NUM];						/*记录每个中断对应处理函数所用时间*/
	u32 u32SemCore;											/*获取信号量超时时对应的持有核*/
};
struct ipc_control{
    u32     core_num;										/*记录IPC模块工作所在的核ID*/
    void*   ipc_base;										/*ipc基址*/
    bool   sem_exist[INTSRC_NUM];							/*记录信号量是否已经创建*/
    struct ipc_entry ipc_int_table[INTSRC_NUM];				/*记录每一个中断源注册的回调函数*/
    osl_sem_id	 sem_ipc_task[INTSRC_NUM];
    spinlock_t lock;
	unsigned long last_int_cb_addr;  /* 最后一个被回调的中断函数的地址 */
};
#ifdef __cplusplus
}
#endif

#endif /* end #define _IPC_BALONG_H_*/

