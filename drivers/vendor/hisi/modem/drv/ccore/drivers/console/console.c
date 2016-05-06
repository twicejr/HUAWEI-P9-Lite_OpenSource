#include <sre_io_intf.h>
#include <string.h>
#include <osl_module.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>
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

	(void)con_driver_lock();

	/*lint -e413*/
	/* check whether a console withe identical name exists. */
	list_for_each_entry(pos, lhead, next)
	{
		if(0 == strncmp(con_new->name, pos->name, strlen(con_new->name) + 1))
		{
			(void)con_driver_unlock();
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

	(void)con_driver_unlock();

	return CON_OK;
}

int con_unregister(struct console * con)/* CON_INFLG_AGENT作为入参， */
{
	struct console *pos = NULL;
	struct list_head * lhead = NULL;

	if(!con)
		return -1;
	lhead = con->inflags & CON_INFLG_AGENT ? &agent_consoles : &consoles;

	(void)con_driver_lock();

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
		(void)con_driver_unlock();
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

	(void)con_driver_unlock();

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
	sema_init(&con_list_sem, OS_SEM_FULL);
	console_driver_inited = 1;
	return 0;
}
