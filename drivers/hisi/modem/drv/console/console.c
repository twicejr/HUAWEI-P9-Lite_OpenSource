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

#include <linux/string.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <osl_common.h>
#include "console.h"

LIST_HEAD(consoles);
LIST_HEAD(agent_consoles);
static struct semaphore con_list_sem;
static struct console * primary_con = NULL;
static int console_driver_inited = 0;

static void con_put(struct console * con, unsigned char * inbuf, unsigned int size)
{
	unsigned long lock_flags = 0;

	spin_lock_irqsave(&con->logbuf_lock,lock_flags);
	(void)con_ring_force_append(&con->logbuf, inbuf, size);
	spin_unlock_irqrestore(&con->logbuf_lock,lock_flags);
}

static int con_get(struct console * con, unsigned char * outbuf, unsigned int size)
{
	return (int)con_ring_get(&con->cmdbuf, outbuf, size);
}

static int con_tx(struct console * con, unsigned char * outbuf, unsigned int size)
{
	unsigned long lock_flags = 0;
	int sz = 0;

	spin_lock_irqsave(&con->logbuf_lock,lock_flags);
	sz = (int)con_ring_get(&con->logbuf, outbuf, size);
	spin_unlock_irqrestore(&con->logbuf_lock,lock_flags);
	return sz;
}

static int con_rx(struct console * con, unsigned char * inbuf, unsigned int sz)
{
	int retval = 0;

	retval = (int)con_ring_append(&con->cmdbuf, inbuf, sz);

	if((con->flags & CON_PRIMARY && CON_ENABLE & con->flags) && con->start_shell)
		(void)con->start_shell(con);

	return retval;
}

int con_early_register(struct console * con_new)
{
	if(!con_new)
		return -CON_ERR_NULL_PTR;

	spin_lock_init(&con_new->logbuf_lock);
	con_new->tx = con_tx;/* 方法凤城一个结构体 */
	con_new->rx = con_rx;
	con_new->put = con_put;
	con_new->get = con_get;

	if(primary_con)
		primary_con->flags &= ~CON_PRIMARY;
	con_new->flags |= (CON_PRIMARY | CON_ENABLE);
	primary_con = con_new;

	list_add(&con_new->next, &consoles);
	return 0;
}

int con_register(struct console * con_new)
{
	struct console *pos = NULL;
	struct list_head * lhead = NULL;

	if(!con_new)
		return -CON_ERR_NULL_PTR;

	lhead = con_new->inflags & CON_INFLG_AGENT ? &agent_consoles : &consoles;

	con_driver_lock();

	/*lint -e413*/
	/* check whether a console withe identical name exists. */
	list_for_each_entry(pos, lhead, next)
	{
		if(0 == strncmp(con_new->name, pos->name, strlen(con_new->name) + 1))
		{
			con_driver_unlock();
			return -CON_ERR_EXIST;
		}
	}
	/*lint +e413*/

	spin_lock_init(&con_new->logbuf_lock);
	con_new->tx = con_tx;/* 方法凤城一个结构体 */
	con_new->rx = con_rx;
	con_new->put = con_put;
	con_new->get = con_get;

	if(!(CON_INFLG_AGENT & con_new->inflags))
	{
		if(primary_con)
			primary_con->flags &= ~CON_PRIMARY;
		con_new->flags |= (CON_PRIMARY | CON_ENABLE);
		primary_con = con_new;/* 去掉标记后，保留这一句 */
	}
	else
	{
		con_new->flags |= (CON_PRIMARY | CON_ENABLE);
	}

	list_add(&con_new->next, lhead);

	con_driver_unlock();

	return CON_OK;
}

int con_unregister(struct console * con)/* CON_INFLG_AGENT作为入参， */
{
	struct console *pos = NULL;
	struct list_head * lhead = NULL;

	if(!con)
		return -1;
	lhead = con->inflags & CON_INFLG_AGENT ? &agent_consoles : &consoles;

	con_driver_lock();

	/*lint -e413*/
	/* check whether a console with the identical name exists. */
	list_for_each_entry(pos, lhead, next)
	{
		if(0 == strncmp(con->name, pos->name, strlen(con->name) + 1))
			break;
	}
	/*lint +e413*/
	if(&pos->next == lhead)
	{
		con_driver_unlock();
		return -CON_ERR_NOEXIST;
	}

	if(pos->flags & CON_PRIMARY && !(pos->inflags & CON_INFLG_AGENT))
	{
		pos->flags &= ~CON_PRIMARY;
		primary_con = container_of(pos->next.next, struct console, next);
		if(primary_con)
			primary_con->flags |= CON_PRIMARY;
	}

	list_del_init(&pos->next);

	con_driver_unlock();

	return CON_OK;
}

struct console * con_get_cur_con(void)
{
	return primary_con;
}

int con_enable(struct console * con)
{
	con->flags |= CON_ENABLE;
	return 0;
}

int con_disable(struct console * con)
{
	con->flags &= ~CON_ENABLE;
	return 0;
}

int con_driver_lock(void)
{
	if(console_driver_inited)
	{
		down(&con_list_sem);
		//osl_task_lock();
	}

	return 0;
}

int con_driver_unlock(void)
{
	if(console_driver_inited)
	{
		//osl_task_unlock();
		up(&con_list_sem);
	}

	return 0;
}

void con_log_clear(struct console * con)
{
	con_ring_reset(&con->logbuf);
}

int con_init(void)
{
	sema_init(&con_list_sem, 1);
	console_driver_inited = 1;
	return 0;
}

module_init(con_init);
