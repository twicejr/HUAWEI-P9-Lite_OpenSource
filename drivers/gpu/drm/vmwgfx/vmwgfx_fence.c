/**************************************************************************
 *
 * Copyright (C) 2010 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/


#include "vmwgfx_drv.h"

struct vmw_fence {
	struct list_head head;
	uint32_t sequence;
	struct timespec submitted;
};

void vmw_fence_queue_init(struct vmw_fence_queue *queue)
{
	INIT_LIST_HEAD(&queue->head);
	queue->lag = ns_to_timespec(0);
	getrawmonotonic(&queue->lag_time);
	spin_lock_init(&queue->lock);
}

void vmw_fence_queue_takedown(struct vmw_fence_queue *queue)
{
	struct vmw_fence *fence, *next;

	spin_lock(&queue->lock);
	list_for_each_entry_safe(fence, next, &queue->head, head) {
		kfree(fence);
	}
	spin_unlock(&queue->lock);
}

int vmw_fence_push(struct vmw_fence_queue *queue,
		   uint32_t sequence)
{
	struct vmw_fence *fence = kmalloc(sizeof(*fence), GFP_KERNEL);

	if (unlikely(!fence))
		return -ENOMEM;

	fence->sequence = sequence;
	getrawmonotonic(&fence->submitted);
	spin_lock(&queue->lock);
	list_add_tail(&fence->head, &queue->head);
	spin_unlock(&queue->lock);

	return 0;
}

int vmw_fence_pull(struct vmw_fence_queue *queue,
		   uint32_t signaled_sequence)
{
	struct vmw_fence *fence, *next;
	struct timespec now;
	bool updated = false;

	spin_lock(&queue->lock);
	getrawmonotonic(&now);

	if (list_empty(&queue->head)) {
		queue->lag = ns_to_timespec(0);
		queue->lag_time = now;
		updated = true;
		goto out_unlock;
	}

	list_for_each_entry_safe(fence, next, &queue->head, head) {
		if (signaled_sequence - fence->sequence > (1 << 30))
			continue;

		queue->lag = timespec_sub(now, fence->submitted);
		queue->lag_time = now;
		updated = true;
		list_del(&fence->head);
		kfree(fence);
	}

out_unlock:
	spin_unlock(&queue->lock);

	return (updated) ? 0 : -EBUSY;
}

static struct timespec vmw_timespec_add(struct timespec t1,
					struct timespec t2)
{
	t1.tv_sec += t2.tv_sec;
	t1.tv_nsec += t2.tv_nsec;
	if (t1.tv_nsec >= 1000000000L) {
		t1.tv_sec += 1;
		t1.tv_nsec -= 1000000000L;
	}

	return t1;
}

static struct timespec vmw_fifo_lag(struct vmw_fence_queue *queue)
{
	struct timespec now;

	spin_lock(&queue->lock);
	getrawmonotonic(&now);
	queue->lag = vmw_timespec_add(queue->lag,
				      timespec_sub(now, queue->lag_time));
	queue->lag_time = now;
	spin_unlock(&queue->lock);
	return queue->lag;
}


static bool vmw_lag_lt(struct vmw_fence_queue *queue,
		       uint32_t us)
{
	struct timespec lag, cond;

<<<<<<< HEAD
	cond = ns_to_timespec((s64) us * 1000);
	lag = vmw_fifo_lag(queue);
	return (timespec_compare(&lag, &cond) < 1);
=======
	event = kzalloc(sizeof(*event), GFP_KERNEL);
	if (unlikely(event == NULL)) {
		DRM_ERROR("Failed to allocate an event.\n");
		ret = -ENOMEM;
		goto out_no_event;
	}

	event->event.base.type = DRM_VMW_EVENT_FENCE_SIGNALED;
	event->event.base.length = sizeof(*event);
	event->event.user_data = user_data;

	event->base.event = &event->event.base;
	event->base.file_priv = file_priv;
	event->base.destroy = (void (*) (struct drm_pending_event *)) kfree;


	if (flags & DRM_VMW_FE_FLAG_REQ_TIME)
		ret = vmw_event_fence_action_queue(file_priv, fence,
						   &event->base,
						   &event->event.tv_sec,
						   &event->event.tv_usec,
						   interruptible);
	else
		ret = vmw_event_fence_action_queue(file_priv, fence,
						   &event->base,
						   NULL,
						   NULL,
						   interruptible);
	if (ret != 0)
		goto out_no_queue;

	return 0;

out_no_queue:
	event->base.destroy(&event->base);
out_no_event:
	spin_lock_irqsave(&dev->event_lock, irq_flags);
	file_priv->event_space += sizeof(*event);
	spin_unlock_irqrestore(&dev->event_lock, irq_flags);
out_no_space:
	return ret;
>>>>>>> lsk
}

int vmw_wait_lag(struct vmw_private *dev_priv,
		 struct vmw_fence_queue *queue, uint32_t us)
{
	struct vmw_fence *fence;
	uint32_t sequence;
	int ret;

	while (!vmw_lag_lt(queue, us)) {
		spin_lock(&queue->lock);
		if (list_empty(&queue->head))
			sequence = atomic_read(&dev_priv->fence_seq);
		else {
			fence = list_first_entry(&queue->head,
						 struct vmw_fence, head);
			sequence = fence->sequence;
		}
		spin_unlock(&queue->lock);

		ret = vmw_wait_fence(dev_priv, false, sequence, true,
				     3*HZ);

		if (unlikely(ret != 0))
			return ret;

<<<<<<< HEAD
		(void) vmw_fence_pull(queue, sequence);
=======
	ret = vmw_event_fence_action_create(file_priv, fence,
					    arg->flags,
					    arg->user_data,
					    true);
	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Failed to attach event to fence.\n");
		goto out_no_create;
>>>>>>> lsk
	}
	return 0;
}


