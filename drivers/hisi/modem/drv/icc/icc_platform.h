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


#ifndef ICC_PLATFORM_H
#define ICC_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/suspend.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/wakelock.h>
#include <asm/barrier.h>
#include <osl_common.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <osl_spinlock.h>
#include <osl_wait.h>
#include <osl_list.h>
#include <osl_malloc.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_dump.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <mdrv_sysboot_commmon.h>
#include <bsp_icc.h>

#define ICC_CHANNEL_INIT_COMPITABLE  "hisilicon,icc_balong_app"


#define  ICC_THIS_CPU                 (ICC_CPU_APP)
#define  ICC_SEND_CPU                 (ICC_CPU_MODEM)
#define  ICC_RECV_IPC_SHARED          (IPC_ACPU_INT_SRC_CCPU_ICC)
#define  ICC_TASK_STK_SIZE            (0x1000)
#define  ICC_DUMP_SAVE_MOD            DUMP_AP_ICC
#define  ICC_DUMP_EXT_SIZE            (0x800)

#define ICC_SDDR_START_ADDR_ON_THIS_CORE    (ICC_DBG_MSG_ADDR_IN_DDR + ICC_DBG_MSG_LEN_IN_DDR)
#define ICC_SRAM_START_ADDR_ON_THIS_CORE    (ADDR_MACORE_SEND)
#define ICC_SDDR_S_START_ADDR_ON_THIS_CORE  (ICC_DBG_MSG_ADDR_IN_DDR_S + ICC_DBG_MSG_LEN_IN_DDR_S)

#define  icc_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ICC, "icc: %s "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  icc_print_info                printk
#define  icc_print_notice(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_NOTICE, BSP_MODU_ICC, "%s "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  icc_print_debug(fmt, ...) \
do {                               \
    if (g_icc_dbg.msg_print_sw)    \
        icc_print_error(fmt, ##__VA_ARGS__);\
} while (0)

#define memset_s(dest, destMax, val, count) memset(dest, val, count)
#define memcpy_s(dest, destMax, src, count) memcpy(dest, src, count)
#define sprintf_s(buf, max_dst_size, fmt, ...)   sprintf(buf, fmt, ...)

typedef struct task_struct*  icc_task_id;

/* 数据类型定义start */
struct icc_pm_debug{
	FUNCPTR_1 debug_routine;
	int para;
};

struct icc_channel_vector
{
	read_cb_func  read_cb;        /* 接收向量的读回调函数指针 */
	void          *read_context;  /* 接收向量的读回调函数context */
	write_cb_func write_cb;       /* 接收向量的写回调函数指针 */
	void          *write_context; /* 接收向量的写回调函数context */
	struct icc_pm_debug pm_debug;
};

struct icc_control
{
	u32                      cpu_id;                    /* 当前核cpu id */
	u32                      state;                     /* icc控制结构体状态: 可用|不可用 */
	icc_task_id              shared_task_id;            /* 通道共享任务id */
	u32                      shared_recv_ipc_irq_id;    /* 通道共享的接收数据使用ipc中断 */
	osl_sem_id               shared_task_sem;           /* 唤醒通道共享任务的信号量 */
	u32                      wake_up_flag;
	u32                      sleep_flag;
	struct icc_channel       *channels[ICC_CHN_ID_MAX]; /* icc_channel的结构体指针数组 */
	u32                      channel_size;              /* 本核上有的通道数目 */
	struct     wake_lock     wake_lock;
	struct notifier_block    pm_notify;
};

void icc_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length);
void icc_wake_lock_init(struct wake_lock *lock, int lock_id, const char *name);
void icc_wake_lock(struct wake_lock *lock);
void icc_wake_unlock(struct wake_lock *lock);
void bsp_icc_channel_uninit(u32 real_channel_id);
int icc_pm_init(void);
int icc_ccore_is_reseting(u32 cpuid);

void icc_packet_print(struct icc_channel_packet *packet);
int icc_channel_packet_dump(struct icc_channel_packet *packet);
u32 bsp_icc_channel_status_get(u32 real_channel_id, u32 *channel_stat);

void icc_debug_in_isr(void);
s32  icc_debug_init(u32 channel_num);
void icc_debug_before_send(struct icc_channel_packet *packet);
void icc_debug_after_send(struct icc_channel *channel, struct icc_channel_packet *packet, u8 *data);
void icc_debug_before_recv(struct icc_channel_packet *pkg_header);
void icc_debug_in_read_cb(u32 channel_id, u8 *buf, u32 buf_len, u32 read_ptr, u32 write_ptr);
void icc_debug_after_recv(struct icc_channel_packet *pkg_header);

#ifdef __cplusplus
}
#endif

#endif


