/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  reset.c    hisi watchdog v100 kernel device driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/module.h>			/* For module specific items */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <mach/queue.h>



void queue_init(struct queue *q, char *name, unsigned int len)
{
    memset(q->name, 0, QUEUE_NAME_LEN);
    if (name){
        strncpy(q->name, name, QUEUE_NAME_LEN);
        q->name[QUEUE_NAME_LEN - 1] = 0;
    }

    spin_lock_init(&q->lock);

    q->max  = len;
    q->head = 0;
    q->tail = 0;
    q->in = 0;
    q->out = 0;

    memset(q->data, 0, len);

    return;
}
EXPORT_SYMBOL(queue_init);

void queue_destory(struct queue *q)
{
    memset(q->data, 0, q->max);

    q->max = 0;
    q->head = 0;
    q->tail = 0;
    q->in = 0;
    q->out = 0;

    return;
}
EXPORT_SYMBOL(queue_destory);

void _queue_loop_in(struct queue *q, void *element, unsigned int len)
{
    unsigned int copy = min((q->max - q->head), len);
    unsigned int omit = len;
    unsigned int left = 0;

    /*left room*/
    left = q->max - (MOD_SUB(q->head, q->tail, q->max));
    if (left > (len + 1)){
        omit = 0;
    }

    /*update tail index*/
    q->tail = MOD_ADD(q->tail, omit, q->max);

    /*copy data*/
    memcpy(&(q->data[q->head]), element, copy);
    if (len > copy){
        memcpy(&(q->data[0]), element + copy, len - copy);
    }
    q->head = MOD_ADD(q->head, len, q->max);
    q->in += len;

    return;
}
EXPORT_SYMBOL(_queue_loop_in);

void queue_loop_in(struct queue *q, void *element, unsigned int len)
{
    unsigned int flags = 0;

    spin_lock_irqsave(&q->lock, flags);
    _queue_loop_in(q, element, len);
    spin_unlock_irqrestore(&q->lock, flags);

    return;
}
EXPORT_SYMBOL(queue_loop_in);

int _queue_in(struct queue *q, void *element, unsigned int len)
{
    unsigned int copy = min((q->max - q->head), len);
    unsigned int left = 0;

    /*left room*/
    left = q->max - (MOD_SUB(q->head, q->tail, q->max));
    if ((len + 1) > left){
        return -1;
    }

    memcpy(&(q->data[q->head]), element, copy);
    if (len > copy){
        memcpy(&(q->data[0]), element + copy, len - copy);
    }

    q->head = MOD_ADD(q->head, len, q->max);

    return 0;
}
EXPORT_SYMBOL(_queue_in);

int queue_in(struct queue *q, void *element, unsigned int len)
{
    unsigned int flags = 0;
    int ret;

    spin_lock_irqsave(&q->lock, flags);
    ret = _queue_in(q, element, len);
    spin_unlock_irqrestore(&q->lock, flags);

    return ret;
}
EXPORT_SYMBOL(queue_in);

int _queue_out(struct queue *q, void *element, unsigned int len)
{
    unsigned int valid;
    unsigned int copy;

    valid = MOD_SUB(q->head, q->tail, q->max);
    if (len > valid){
        return -1;
    }

    copy = min((q->max - q->tail), len);
    memcpy(element, &q->data[q->tail], copy);
    if (len > copy){
        memcpy(element + copy, &q->data[0], len - copy);
    }

    q->tail = MOD_ADD(q->tail, len, q->max);
    q->out += len;

    return 0;
}
EXPORT_SYMBOL(_queue_out);

int queue_out(struct queue *q, void *element, unsigned int len)
{
    unsigned int flags = 0;
    int ret;

    spin_lock_irqsave(&q->lock, flags);
    ret = _queue_out(q, element, len);
    spin_unlock_irqrestore(&q->lock, flags);

    return ret;
}
EXPORT_SYMBOL(queue_out);

