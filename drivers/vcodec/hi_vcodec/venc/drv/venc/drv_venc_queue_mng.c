/*
 * Copyright (c) (2011 - ...) digital media project platform development dept,
 * Hisilicon. All rights reserved.
 *
 * File: queue.c
 *
 * Purpose: vdec omx adaptor layer
 *
 * Author: sunny. liucan
 *
 * Date: 26, Dec, 2011
 *
 */
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/delay.h>

/* add include here */
#include <linux/version.h>

#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/vmalloc.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
//#include <linux/devfs_fs_kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/seq_file.h>
#include <linux/list.h>

#include <asm/uaccess.h>
//#include <asm/hardware.h>
#include <asm/io.h>
//#include <asm/system.h>

#include <linux/ioport.h>
#include <linux/string.h>

#include "drv_venc_queue_mng.h"
#include "hi_drv_venc.h"
//#include "hi_error_mpi.h"
#include "hi_drv_mem.h"

#define MAX_QUEUE_DEPTH	200

static void VENC_DRV_MngQueueStop(queue_info_s *queue)
{
	unsigned long flags   = 0;
	struct list_head *pos = NULL;
    struct list_head *n   = NULL;

	HI_INFO_VENC("%s, msg prepare to stop!\n", __func__);

	/* flush msg list */
	spin_lock_irqsave(&queue->msg_lock, flags);
	queue->stop = 1;
	if (!list_empty(&queue->head))
    {
		HI_INFO_VENC("%s, msg queue not empty, flush it!\n", __func__);
		list_for_each_safe(pos, n, &queue->head)        //== for (pos = (head)->next,n = pos->next; pos != (head);pos = n, n = pos->next)
        {
			list_del(pos);
			list_add_tail(pos, &queue->free);
		}
	}
	spin_unlock_irqrestore(&queue->msg_lock, flags);
	wake_up(&queue->wait);

	HI_INFO_VENC("%s, Queue Stop ok!\n", __func__);
    return;
}

queue_info_s* VENC_DRV_MngQueueInit( HI_U32 depth,HI_BOOL bOMX)     //申请内存，并初始化
{
    queue_info_s  *queue = NULL;
	queue_data_s  *data  = NULL;
    HI_U32         num   = 0;

    if ((depth > MAX_QUEUE_DEPTH) || (depth == 0))
    {
		HI_ERR_VENC("%s, Invalid Param: depth = %d!\n", __func__, depth);
		return NULL;
	}

    num   = depth;
	queue = kzalloc(sizeof(queue_info_s), GFP_KERNEL);
	if (!queue) {
		HI_ERR_VENC("%s, kzalloc queue failed!\n", __func__);
		return NULL;
	}

	spin_lock_init(&queue->msg_lock);
	INIT_LIST_HEAD(&queue->head);
	INIT_LIST_HEAD(&queue->free);

	if (bOMX)
	{
	   // 等待队列 l00214825
	   init_waitqueue_head(&queue->wait);       // just for omxvenc
	}

	queue->stop = 0;

	/* alloc element for seg stream */
	data  = (queue_data_s *)kzalloc(sizeof(queue_data_s) * num, GFP_KERNEL);
	if (!data)
	{
		HI_ERR_VENC("%s, kzalloc queue_data_s failed\n", __func__);
		kfree((HI_VOID *)queue);
		queue = NULL;
		return NULL;
	}
    queue->alloc_data = data;
    //开始都push到空队列里面去  l00214825
	for (; num; data++, num--)
	{
		list_add(&data->list, &queue->free);
	}

	queue->queue_num = depth;
	queue->bSleep    = HI_FALSE;
	return queue;
}

HI_S32 VENC_DRV_MngQueueDeinit(queue_info_s *queue)
{
	if (!queue)
	{
	    HI_ERR_VENC("%s, Invalid Param : queue is null!\n", __func__);
		return HI_ERR_VENC_NULL_PTR;
	}

    while(queue->bSleep)
    {
       msleep(10);
    }

	VENC_DRV_MngQueueStop(queue);
	if(queue->alloc_data)
	{
		kfree((HI_VOID *)queue->alloc_data);
		queue->alloc_data = NULL;
	}
	if(queue)
	{
		kfree((HI_VOID *)queue);
		queue = NULL;
	}
    return 0;
}

HI_S32 VENC_DRV_MngQueueEmpty(queue_info_s *queue)
{
	return list_empty(&queue->head);
}

HI_S32 VENC_DRV_MngQueueFull(queue_info_s *queue)
{
    return list_empty(&queue->free);
}

static HI_U32 VENC_DRV_MngQueuePending(queue_info_s *queue)
{
	HI_U32 has_msg = 0;
	HI_U32 stopped = 0;
    unsigned long flags  = 0;

	if (!queue)
		return 1;

	spin_lock_irqsave(&queue->msg_lock, flags);
	has_msg = !list_empty(&queue->head);
	stopped = queue->stop;

    spin_unlock_irqrestore(&queue->msg_lock, flags);

	return has_msg || stopped;
}

HI_S32 VENC_DRV_MngDequeue(queue_info_s *queue, queue_data_s *pQueue_data)
{
	HI_S32 ret = 0;
    unsigned long flags  = 0;
	queue_data_s *msg    = NULL;

	if (!queue || !pQueue_data)
    {
		HI_ERR_VENC("%s, Invalid Param : queue = %p, pQueue_data = %p\n", __func__, queue, pQueue_data);
		return HI_ERR_VENC_NULL_PTR;
	}

    queue->bSleep = HI_TRUE;
	ret = wait_event_interruptible_timeout(queue->wait, VENC_DRV_MngQueuePending(queue),msecs_to_jiffies(30)); // msg_pending(queue)为真则退出阻塞的等待!
    queue->bSleep = HI_FALSE;
	if (ret <= 0)   /*ret >0 is success*/
    {
		//HI_DBG_VENC("dequeue timeout, failed, ret = %d\n", ret);
		return HI_FAILURE;
	}
	spin_lock_irqsave(&queue->msg_lock, flags);
	if (queue->stop)
    {
		HI_ERR_VENC("%s, msg queue stoped\n", __func__);
		spin_unlock_irqrestore(&queue->msg_lock, flags);
		return HI_FAILURE;
	}

	if (list_empty(&queue->head))
    {
		HI_ERR_VENC("%s, no free msg dequeue!\n", __func__);
		spin_unlock_irqrestore(&queue->msg_lock, flags);
		return HI_FAILURE;
	}

	msg = list_first_entry(&queue->head, queue_data_s, list);
	list_del(&msg->list);
	memcpy((HI_VOID *)&pQueue_data->msg_info_omx, (HI_VOID *)&msg->msg_info_omx,sizeof(venc_msginfo));
	list_add(&msg->list, &queue->free);
	spin_unlock_irqrestore(&queue->msg_lock, flags);

	return HI_SUCCESS;
}

HI_S32 VENC_DRV_MngQueue(queue_info_s *queue,queue_data_s *pQueue_data,HI_U32 msgcode, HI_U32 status)
{
    unsigned long flags  = 0;
	queue_data_s *msg    = NULL;
	if (!queue)
    {
		HI_ERR_VENC("%s, Invalid Param : queue is null!\n", __func__);
		return HI_ERR_VENC_NULL_PTR;
	}

	spin_lock_irqsave(&queue->msg_lock, flags);
	if (queue->stop)
    {
		HI_ERR_VENC("%s, msg queue stopped!\n", __func__);
		spin_unlock_irqrestore(&queue->msg_lock, flags);
		return HI_FAILURE;
	}

	if (list_empty(&queue->free))
    {
		HI_ERR_VENC("%s, no free msg left!\n", __func__);
		spin_unlock_irqrestore(&queue->msg_lock, flags);
		return HI_FAILURE;
	}

	msg = list_first_entry(&queue->free, queue_data_s, list);

	list_del(&msg->list);

	msg->msg_info_omx.status_code = status;
	msg->msg_info_omx.msgcode     = msgcode;
    if((VENC_MSG_RESP_INPUT_DONE == msgcode) || (VENC_MSG_RESP_OUTPUT_DONE == msgcode))
    {
        if( !pQueue_data)
        {
            HI_ERR_VENC("%s, invalid param of parm : pQueue_data = %p!\n", __func__, pQueue_data);
            return HI_ERR_VENC_NULL_PTR;
        }
        memcpy((HI_VOID *)&msg->msg_info_omx.buf, (HI_VOID *)&pQueue_data->msg_info_omx.buf, sizeof(venc_user_buf));
	}

	list_add_tail(&msg->list, &queue->head);
	spin_unlock_irqrestore(&queue->msg_lock, flags);
	wake_up_interruptible(&queue->wait);

	return HI_SUCCESS;
}

HI_S32 VENC_DRV_MngQueueRefresh(queue_info_s *queue)
{
    unsigned long flags  = 0;
	queue_data_s *msg    = NULL;
	spin_lock_irqsave(&queue->msg_lock, flags);
    while( !VENC_DRV_MngQueueEmpty(queue))
    {
        msg = list_first_entry(&queue->head, queue_data_s, list);
		list_del(&msg->list);
		list_add(&msg->list, &queue->free);
    }
	spin_unlock_irqrestore(&queue->msg_lock, flags);
	return HI_SUCCESS;
}

HI_S32 VENC_DRV_MngQueueSize(queue_info_s *queue)
{
    int icount = 0;
    struct list_head *pos = NULL;
    unsigned long flags   = 0;
	spin_lock_irqsave(&queue->msg_lock, flags);
    list_for_each(pos, &queue->head)
    {
        icount++;
    }
	spin_unlock_irqrestore(&queue->msg_lock, flags);
    return icount;
}

