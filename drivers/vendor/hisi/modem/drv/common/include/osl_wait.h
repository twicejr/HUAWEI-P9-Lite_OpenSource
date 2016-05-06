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

#ifndef _OSL_WAIT_H
#define _OSL_WAIT_H

#ifdef __KERNEL__
#include <linux/wait.h>


typedef int (*osl_wait_func_t)(void* data);

struct osl_wait_data
{
	void* task;
	osl_wait_func_t func;
	void* data;
};

int try_to_wake_up(struct task_struct *p, unsigned int state, int wake_flags);

static inline int osl_wait_wake_function(wait_queue_t *curr, unsigned mode, int wake_flags,
			  void *key)
{
	int ret = 0;
	struct osl_wait_data* data = (struct osl_wait_data*)curr->private;

	if(data->func(data->data))
		ret =  try_to_wake_up((struct task_struct *)data->task, mode, wake_flags);

	if (ret)
		list_del_init(&curr->task_list);
	return ret;
}

#define __wait_event_timeout_func(wq, ret, condition_func, condition_data)			\
do {			\
	struct osl_wait_data __private_data = {              \
		.task = current,	\
		.func = condition_func,	\
		.data = condition_data,		\
		};\
	wait_queue_t __wait = {						\
		.private	= &__private_data,				\
		.func		= osl_wait_wake_function,				\
		.task_list	= LIST_HEAD_INIT((__wait).task_list),	\
		};			\
									\
	for (;;) {							\
		prepare_to_wait(&wq, &__wait, TASK_UNINTERRUPTIBLE);	\
		if (condition_func(condition_data))						\
			break;						\
		ret = schedule_timeout(ret);				\
		if (!ret)						\
			break;						\
	}								\
	finish_wait(&wq, &__wait);					\
} while (0)

#define wait_event_timeout_func(wq, timeout, condition_func, condition_data)			\
{									\
	long __ret = timeout;						\
	if (!(condition_func(condition_data))) 						\
		__wait_event_timeout_func(wq, __ret, condition_func, condition_data);		\
	__ret=__ret;								\
}

#elif defined(__OS_VXWORKS__)

#include <vxWorks.h>
#include <vsbConfig.h>
#include <classLib.h>
#include <errno.h>
#include <taskLib.h>
#include <intLib.h>
#include <errnoLib.h>
#include <eventLib.h>
#include <qLib.h>
#include <common.h>

typedef int (*osl_wait_func_t)(void* data);
typedef SEM_ID wait_queue_head_t;
#define MAX_SCHEDULE_TIMEOUT WAIT_FOREVER

struct osl_wait_data
{
	void* task;
	osl_wait_func_t func;
	void* data;
    Q_NODE qNode;		/* multiway q node: rdy/pend q */
};


wait_queue_head_t osl_waitqueue_create(int options);

STATUS osl_waitqueue_wakeup(wait_queue_head_t qhead);

STATUS osl_waitqueue_wait(wait_queue_head_t qhead, int timeout, struct osl_wait_data* entry);

#define init_waitqueue_head(q)				\
	do {						\
		*(q) = osl_waitqueue_create(SEM_Q_PRIORITY);	\
	} while (0)

#define wait_event_timeout_func(wq, timeout, condition_func, condition_data)			\
{		\
	STATUS __ret = OK;	\
	struct osl_wait_data __wait;		\
	__wait.data = condition_data;	\
	__wait.func = condition_func;	\
	__wait.task = taskIdCurrent;	\
	\
	__ret = osl_waitqueue_wait(wq, timeout, &__wait);	\
	if(ERROR == __ret && errnoGet() == S_objLib_OBJ_TIMEOUT)	\
    	__ret = 0; /* timeout */	\
}

#define wake_up(x)	\
	do{ \
		(void)osl_waitqueue_wakeup(*(x));	\
		/*if(OK != __ret){BUG();};*/	\
	}while(0)

#elif defined(__CMSIS_RTOS)
#define  MAX_SCHEDULE_TIMEOUT         (0xff)
#elif defined(__OS_RTOSCK__)
#include "sre_sem.h"
#include "osl_spinlock.h"
#include "osl_list.h"

typedef int (*osl_wait_func_t)(void* data);

#define MAX_SCHEDULE_TIMEOUT OS_WAIT_FOREVER

struct __wait_queue_head {
	spinlock_t lock;
	struct list_head task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;

struct osl_wait_data
{
	UINT32 task_id;           /*TASK ID*/
	osl_wait_func_t func; /*check fun*/
	void* data;           /*check fun input*/
	struct list_head task_list;
};
typedef struct osl_wait_data wait_queue_t;

void __wake_up_wait_queque(wait_queue_head_t *q);
void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait);
void finish_wait(wait_queue_head_t *q, wait_queue_t *wait);
#define __wait_event_timeout_func(wq, ret, condition_func, condition_data)			\
do {			\
    UINT32 task_pid = 0; \
    (void)SRE_TaskSelf(&task_pid); \
	struct osl_wait_data __waitqueue_data = {              \
		.task_id = task_pid,	\
		.func = condition_func,	\
		.data = condition_data,	\
		.task_list	= LIST_HEAD_INIT((__waitqueue_data).task_list),	\
		};\
	if (!(condition_func(condition_data))) 						\
		    prepare_to_wait(&wq, &__waitqueue_data);	\
} while (0)

/**************API****************/
/*init waitqueue head*/
void init_waitqueue_head(wait_queue_head_t *q);

/*add event to waitqueue and suspend*/
#define wait_event_timeout_func(wq, timeout, condition_func, condition_data)			\
{									\
	long __ret = timeout;						\
	if (!(condition_func(condition_data))) 						\
		__wait_event_timeout_func(wq, __ret, condition_func, condition_data);		\
	__ret=__ret;								\
}

/*wake up event*/
#define wake_up(x)			__wake_up_wait_queque(x)     

#endif /* __KERNEL__ */

#endif
