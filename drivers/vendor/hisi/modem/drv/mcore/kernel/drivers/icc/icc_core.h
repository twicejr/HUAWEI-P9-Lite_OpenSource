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

#ifndef ICC_BALONG_CORE_H
#define ICC_BALONG_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "icc_platform.h"

extern struct icc_dbg g_icc_dbg;

#ifndef BSP_ERR_ICC_BASE
#define BSP_ERR_ICC_BASE                ((int)(0x80000000 | 0x10180000))
#endif

#ifndef BSP_ERR_ICC_CCORE_RESETTING
#define BSP_ERR_ICC_CCORE_RESETTING    (BSP_ERR_ICC_BASE + 0x12)
#endif

#define icc_safe_free(p) \
do \
{ \
	if(p) \
	{ \
		osl_free((void *)p); \
		p = NULL; \
	} \
} \
while(0)

#define ICC_MIN(x, y)             ((x) < (y) ? (x) : (y))
#define GET_CHN_ID(channel_id)    (((channel_id)>>16) & 0xffff)
#define GET_FUNC_ID(channel_id)   ((channel_id) & 0xffff)

/* 宏定义start */
#define ICC_CHN_MAGIC_SIGN    (0x87651234)
#define ICC_CHN_MAGIC_UNSIGN  (0xabcd8765)


#define PRIVATE_MODE          ((ICC_TASK_PRIVATE << 1) |(ICC_IPC_PRIVATE))
#define SHARED_MODE           ((ICC_TASK_SHARED << 1) |(ICC_IPC_SHARED))
#define ICC_SHARED_IPC_CHN_IDX (0xffffffff)

#define ICC_SDDR_ADDR_MAX      (SHM_ADDR_ICC + SHM_SIZE_ICC)    /* 用于ICC的共享DDR不能大于此地址 */
#define ICC_SRAM_ADDR_MAX      (SRAM_ADDR_ICC + SRAM_SIZE_ICC)  /* 用于ICC的SRAM不能大于此地址 */
#define ICC_SDDR_S_ADDR_MAX    (SHM_S_ADDR_ICC + SHM_S_SIZE_ICC)/* 用于安全ICC的共享DDR不能大于此地址 */

#define ICC_SEM_FULL          (1)
#define ICC_SEM_EMPTY         (0)

struct icc_init_info
{
	u32        real_channel_id;
	u32        mode;
	u32        fifo_size;
	char*      recv_addr;
	char*      send_addr;	
	u32        ipc_recv_irq_id;
	u32        ipc_send_irq_id;
	u32        func_size;
	const char *name;
};

/* 枚举定义start */
/* icc状态 */
enum ICC_STATUS
{
	ICC_UNINITIALIZED = 0,
	ICC_INITIALIZED,
	ICC_STATUS_MAX
};

/* 任务类别分配 */
enum ICC_TASK_TYPE
{
	ICC_TASK_PRIVATE = 0,
	ICC_TASK_SHARED,
	ICC_TASK_TYPE_MAX
};

enum IPC_VEC_TYPE
{
	ICC_IPC_PRIVATE = 0,
	ICC_IPC_SHARED,
	IPC_VEC_TYPE_MAX
};

enum ICC_HAS_TASK
{
	ICC_HAS_TASK = 0,
	ICC_NO_TASK,
	ICC_TASK_MAX
};

/* 通道状态 */
enum ICC_CHN_STAT
{
	ICC_CHN_CLOSED = 0,
	ICC_CHN_OPENED,
	ICC_CHN_STAT_MAX
};

enum ICC_PACKET_RETURN
{
	ICC_PACKET_NONEED_RESPONSE = 0,
	ICC_PACKET_NEED_RESPONSE,
	ICC_PACKET_RETURN_MAX
};

/* 枚举定义end */

union ipc_task_shared
{
	u32 val;
	struct
	{
		u32 ipc_shared :1;  /* 1:共享IPC  0:私有IPC */
		u32 task_shared:1;  /* 1:共享任务 0:私有任务 */
		u32 no_task    :1;  /* 1:无任务   0:有任务 */
		u32 reserved   :29;
	}union_stru;
};

struct icc_channel
{
	u32                       id;               /* 通道id */
	const char                *name;            /* 通道名称 */
	u32                       state;            /* 通道状态: 标识发送通道是否可用 */
	u32                       ready_recv;       /* 通道状态: 标识接收通道是否可用 */
	union ipc_task_shared     mode;             /* 通道接收处理任务类型: shared|private */
	icc_task_id               private_task_id;  /* 通道私有的处理任务id */
	u32                       ipc_send_irq_id;  /* 通道私有的发送数据使用的ipc中断 */
	u32                       ipc_recv_irq_id;  /* 通道私有的接收数据使用的ipc中断 */
	osl_sem_id                private_task_sem; /* 唤醒通道私有的接收任务的信号量 */
	struct icc_channel_fifo   *fifo_recv;       /* 接收fifo的指针 */
	struct icc_channel_fifo   *fifo_send;       /* 发送fifo的指针 */
	spinlock_t                write_lock;       /* 保护通道写互斥的spin锁 */
	spinlock_t                read_lock;        /* 保护通道读互斥的spin锁 */
	struct icc_channel_vector *vector;          /* 接收向量(子通道)指针 */
	u32                       func_size;        /* 接收向量(子通道)大小 */
};

struct channel_cfg{
    unsigned int id;             /* 物理通道ID */
	unsigned int mode;           /* 通道模式:共享or独享 */
	unsigned int size;           /* 本通道发送fifo及接收fifo大小 */
	unsigned int tx_ipc;         /* 发送到对方核的IPC中断号 */
	unsigned int rx_ipc;         /* 在此IPC中断号上接收 */
	unsigned int func_size;      /* 支持的func_size个数 */
	unsigned int rx_fifo_first;  /* 本通道，对于本核，接收fifo在前 */
};

struct icc_wait_data
{
	u32 channel_id;
	u32 packet_seq_num;
};

/* 消息类型定义for debug */
enum ICC_MSG_TYPE
{
	ICC_MSG_SEND = 0,
	ICC_MSG_RECV,
	ICC_MSG_TYPE_MAX
};


/*** 发送/接收消息统计，以消息为维度，需要调用dump接口，以备异常时分析 ***/
#define ICC_MSG_RECORED_DATA_LEN  40
#define ICC_STAT_MSG_NUM          10
struct icc_uni_msg_info
{
	u32 channel_id;    /* channel_id + func_id */
	u32 send_task_id;
	u32 recv_task_id;
	u32 len;            /* 用户数据长度，不包括pkg头 */
	u32 write_pos;      /* write位置 */
	u32 read_pos;       /* read位置 */
	u32 duration_prev;  /* 发送或者接收之前的slice */
	u32 duration_post;  /* 发送或者接收之后的slice */
	u8 data[ICC_MSG_RECORED_DATA_LEN];       
};

struct icc_debug_perf
{
    u32 max_readcb_consume_slice; /* 读回调执行最长的时间 */
	u32 max_readcb_channel_id;    /* 读回调执行最长时间的chan_id_func_id */
	u32 cnt;   /* 统计的次数 */
	u32 sum;   /* 统计的总的执行时长(slice)，从发送到接收完成 */
	u32 avg;   /* 统计的平均执行时长(slice)，从发送到接收完成 */
};

struct icc_recv_msg_info
{
	u32 channel_id;    /* channel_id + func_id */
	u32 send_task_id;
	u32 recv_task_id;
	u32 len;            /* 用户数据长度，不包括pkg头 */
	u32 write_pos;      /* write位置 */
	u32 read_pos;       /* read位置 */
	u32 before_recv_slice;  /* 发送或者接收之前的slice */
	u32 in_read_cb_slice;  /* 接收回调中的slice */
	u32 after_recv_slice;  /* 发送或者接收之后的slice */
	struct icc_debug_perf perf; /* 性能统计 */
};

struct icc_msg_fifo
{
	u32 front;
	u32 rear;
	u32 size;
	struct icc_uni_msg_info msg[ICC_STAT_MSG_NUM];
};

struct icc_msg_fifo_recv
{
	u32 front;
	u32 rear;
	u32 size;
	struct icc_recv_msg_info msg[ICC_STAT_MSG_NUM];
};

struct icc_msg_info
{
	struct icc_msg_fifo send;
	struct icc_msg_fifo_recv recv;
};

/*** 发送/接收消息统计，以通道为维度，分析通道数据 ***/
struct icc_channel_stat_info
{
	u32 sum_len;
	u32 sum_num;
	u32 sum_num_prev;
	u32 task_id;
};

struct icc_uni_channel_info
{
	struct icc_channel_stat_info total;
	struct icc_channel_stat_info *sub_chn;
	u32 func_size;
};

struct icc_channel_info
{
	u32 id;
	struct icc_uni_channel_info send;
	struct icc_uni_channel_info recv;
};

struct icc_dbg
{
	u32 state;
	u32 ipc_int_cnt;
	u32 msg_print_sw;
	u32 send_cpu_id;
	u32 recv_task_id;
	u32 timestamp;
	char *dump_buf_addr;
	u32 dump_buf_size;
    u32 reserved; /* for 8byte allignment */
	struct icc_msg_info msg_stat;
	struct icc_channel_info *channel_stat[ICC_CHN_ID_MAX];
};

void icc_sleep_flag_set(void);
u32 fifo_get(struct icc_channel_fifo *fifo, u8 *data_buf, u32 data_len, u32 *read);
void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo);
s32 icc_channel_has_data(void);
void icc_shared_sem_init(void);
void icc_private_sem_init(osl_sem_id *private_sem);
int icc_shared_task_init(void);
void icc_task_shared_func(void const *obj);
void icc_ipc_isr(u32 data);
struct icc_channel *icc_channel_init(struct icc_init_info *info, s32 *ret);

#ifdef __cplusplus
}
#endif

#endif


