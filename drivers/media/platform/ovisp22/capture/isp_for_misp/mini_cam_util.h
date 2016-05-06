/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MINI_K3_CAM_UTIL_H__
#define __MINI_K3_CAM_UTIL_H__

#include "cam_util_comm.h"

#include "../camera.h"

typedef struct _mini_camera_frame_buf {
	int index;
	u32 phyaddr;
	u32 size;
	void *viraddr;
    u32 statphyaddr;
    void *statviraddr;

	u32 flags;		/* reference to CAMERA_FLAG_XXX */
	struct list_head queue;
	struct timeval timestamp;
} mini_camera_frame_buf;

typedef struct _mini_buffer_arr {
	mini_camera_frame_buf buffers[MAX_FRAME_NR];
	u32 buf_count;
} mini_buffer_arr_t;

typedef struct _mini_data_queue {
	/* buffer queues for capture / preview / ipp */
	/* buffers with no data */
	struct list_head ready_q[STATE_MAX];
	/* buffers that is working on preview  */
	struct list_head work_q[STATE_MAX];
	/* buffers that have valid data */
	struct list_head done_q[STATE_MAX];

	/* work queue for capture and preview */
	wait_queue_head_t queue[STATE_MAX];

	spinlock_t queue_lock;
} mini_data_queue_t;

#ifdef READ_BACK_RAW
int mini_load_raw_file(char *filename, u8 *addr);
#endif
int mini_load_file(char *filename, u8 *addr);
void mini_add_to_queue(mini_camera_frame_buf *f, struct list_head *l, u32 flag);
void mini_del_from_queue(mini_camera_frame_buf *f, u32 flag);
int mini_get_queue_size(struct list_head *l);
void mini_reset_buffer(mini_camera_frame_buf *buf, int count);
void mini_camera_init_buffer(mini_buffer_arr_t *pbuf);
void mini_init_queue(mini_data_queue_t *data_queue, camera_state state);
u32 mini_bits_per_pixel(u32 pix_fmt);

#endif /*__K3_CAM_UTIL_H__ */

/********************** END ***********************/
