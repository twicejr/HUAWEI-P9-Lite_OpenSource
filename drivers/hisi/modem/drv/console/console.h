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

#ifndef __BALONG_CONSOLE_H_
#define __BALONG_CONSOLE_H_

#include <osl_list.h>
#include <osl_spinlock.h>
#include <bsp_icc.h>
#include "ringbuffer.h"
#include "virtshell.h"

#define LOG_BUF_SHIFT 14
#define CMD_BUF_SHIFT 7

#define CON_ACORE ICC_CPU_APP
#define CON_CCORE ICC_CPU_MODEM
#define CON_MCORE ICC_CPU_MCU
#if defined(__KERNEL__)
#define CON_CURCORE ICC_CPU_APP
#elif defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
#define CON_CURCORE ICC_CPU_MODEM
#elif defined(__CMSIS_RTOS)
#define CON_CURCORE ICC_CPU_MCU
#endif

#define CON_OK           0x0
#define CON_ERR_NULL_PTR 0x1
#define CON_ERR_EXIST    0x2
#define CON_ERR_NOEXIST  0x3


#define CON_ENABLE   (0x1U << 0)
#define CON_PRIMARY  (0x1U << 1)

#define CON_INFLG_AGENT    (1U << 0)
#define CON_INFLG_ICC      (1U << 1)
#define CON_INFLG_UART     (1U << 2)
#define CON_INFLG_CONSTANT (1U << 3)

struct console
{
	/* set by user */
	char name[16];
	void * data;
	void (*start_tx)(struct console * con);
	int (*start_shell)(struct console *con);
	unsigned int coreid;
	unsigned int inflags;
	struct con_ring_buffer cmdbuf;
	struct con_ring_buffer logbuf;
	spinlock_t logbuf_lock;
	/* Set by console manager */
	struct virtshl_icc_l16id * icchn;
	struct console * predecessor;
	/* set by console driver, console ldisc */
	int (*tx)(struct console * con, unsigned char * outbuf, unsigned int size);
	int (*rx)(struct console * con, unsigned char * inbuf, unsigned int size);
	void (*put)(struct console * con, unsigned char * inbuf, unsigned int size);
	int (*get)(struct console * con, unsigned char * outbuf, unsigned int size);

	/* private data, not permitted for user to use */
	struct list_head next;
	unsigned int flags;
};

extern struct list_head consoles;
extern struct list_head agent_consoles;

int con_early_register(struct console * con_new);
int con_register(struct console * con_new);
int con_unregister(struct console * con_new);
struct console * con_get_cur_con(void);
int con_enable(struct console * con);
int con_disable(struct console * con);
int con_driver_lock(void);
int con_driver_unlock(void);
void con_log_clear(struct console * con);
int con_init(void);

#endif
