/*
 *  linux/drivers/acorn/scsi/queue.h: queue handling
 *
 *  Copyright (C) 1997 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <linux/list.h>
#include <linux/interrupt.h>

#include "hi_drv_venc.h"      //for omxvenc
#include "hi_drv_video.h"
#include "hi_type.h"

typedef struct queue_data {
	struct list_head list;
	/*msg payload*/
	HI_DRV_VIDEO_FRAME_S queue_info;
	venc_msginfo msg_info_omx;              //for omxvenc
} queue_data_s;

typedef struct queue_info {
	spinlock_t msg_lock;
	wait_queue_head_t wait;

	HI_VOID* alloc_data;              //实际为  queue_data_s* 类型
	HI_U32   queue_num;
	HI_S32   stop;
	struct list_head head;
	struct list_head free;

    volatile HI_BOOL bSleep;
} queue_info_s;

queue_info_s* VENC_DRV_MngQueueInit( HI_U32 depth,HI_BOOL bOMX);

HI_S32 VENC_DRV_MngQueueDeinit(queue_info_s *queue);

HI_S32 VENC_DRV_MngDequeue(queue_info_s *queue, queue_data_s *pQueue_data);

HI_S32 VENC_DRV_MngQueue(queue_info_s *queue,queue_data_s *pQueue_data,HI_U32 msgcode, HI_U32 status);

HI_S32 VENC_DRV_MngQueueEmpty(queue_info_s *queue);

HI_S32 VENC_DRV_MngQueueFull(queue_info_s *queue);

HI_S32 VENC_DRV_MngQueueRefresh(queue_info_s *queue);

HI_S32 VENC_DRV_MngQueueSize(queue_info_s *queue);

#endif /* QUEUE_H */
