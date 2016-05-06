/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2016. All rights reserved.
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
#ifndef  __BSP_MODEM_LOG_H__
#define  __BSP_MODEM_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <osl_types.h>
#include <bsp_ring_buffer.h>

#define MODEM_LOG_WAKEUP_INTERVAL       (3000)

struct log_usr_info;

/* if return val == 0 success, else fail */
typedef int (*USR_READ_FUNC)(struct log_usr_info *usr_info, char *buf, u32 count);

/* if return val == 0 success, else fail */
typedef int (*USR_OPEN_FUNC)(struct log_usr_info *usr_info);

/**
 * struct log_mem - represents shared information between reader & writer
 * This structure is allocated by writer
 */
struct log_mem
{
	u32 magic;         /* magic number: protect memory  */
	u32 write;         /* write offset of ring buffer */
	u32 read;          /* read offset of ring buffer */
	u32 size;          /* ring buffer size */
	u32 app_is_active; /* reader's ready flag */
};

/**
 * struct log_usr_info - represents user information which register to modem log
 * This structure is allocated by writer
 */
struct log_usr_info
{
	char               *dev_name;     /* misc device name */
	u32                mem_is_ok;     /* whether are two momory block(ring buffer & ring buffer info) initilized  */
	char               *ring_buf;     /* The data area(ring buffer) */
	struct log_mem     *mem;          /* The management area(ring buffer info) */
	u32                wake_interval; /* The interval of wakeup acore to trigger log file write, just used in ccore */
	USR_READ_FUNC      read_func;     /* user function in log read method */
	USR_OPEN_FUNC      open_func;     /* user function in log open method */
};

/**
 * bsp_modem_log_register - tell modem log which user information is
 * @usr_info: information which modem log need to know
 *
 * Returns 0 if success
 */
s32 bsp_modem_log_register(struct log_usr_info *usr_info);

/**
 * bsp_modem_log_fwrite_trigger - trigger file write from ring buffer to log record file
 * @usr_info: information regitered to modem log 
 */
void bsp_modem_log_fwrite_trigger(struct log_usr_info *usr_info);

/**
 * modem_log_ring_buffer_get - get generic ring buffer(struct ring buffer) from struct log_usr_info
 * @usr_info: information regitered to modem log 
 * @rb: generic ring buffer info 
 */
void modem_log_ring_buffer_get(struct log_usr_info * usr_info, struct ring_buffer *rb);

/**
 * bsp_modem_log_init - for ccore init decleration
 */
int bsp_modem_log_init(void);

#ifdef __cplusplus
}
#endif

#endif   /* __BSP_MODEM_LOG_H__ */

