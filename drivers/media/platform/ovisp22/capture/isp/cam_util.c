/*
 *  Hisilicon K3 soc camera v4l2 driver source file
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
#include <linux/err.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <linux/list.h>
#include <linux/uaccess.h>
#include <linux/stat.h>
#include "cam_util.h"

/* #define DEBUG_DEBUG 1 */
#define LOG_TAG "K3_CAM_UTIL"
#include "cam_log.h"

#ifdef READ_BACK_RAW
 int load_raw_file(char *filename, u8 * addr)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;

	if (NULL == filename || NULL == addr) {
		print_error("%s param error", __func__);
		return -EINVAL;
	}

	print_debug("enter %s", __func__);

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(filename, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_error("open file error!\n");
		return -1;
	}

	if (0 != vfs_stat(filename, &stat)) {
		print_error("failed to get file state!");
		goto error_out;
	}
	print_debug("file size : %d", (u32) stat.size);
	ret = vfs_read(fp, (char *)addr, (u32) stat.size - 24, &fp->f_pos);
	if (ret < 0)
		print_error("read file error!, %s , ret=%d\n", filename, ret);

	/* must have the following 1 statement */
	set_fs(fs);

error_out:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}
#endif

/*
 **************************************************************************
 * FunctionName: load_file;
 * Description : load firmware to isp;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int load_file(char *filename, u8 * addr,u32 *size)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;

	if (NULL == filename || NULL == addr) {
		print_error("%s param error", __func__);
		return -EINVAL;
	}

	print_debug("enter %s", __func__);

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(filename, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_error("open file error!\n");
		return -1;
	}

	if (0 != vfs_stat(filename, &stat)) {
		print_error("failed to get file state!");
		goto error_out;
	}

    if (stat.size > *size ){
		print_error("file buf too small");
        ret =-1;
		goto error_out;
    }

    *size = stat.size;
	print_debug("file size : %d", (u32) stat.size);
	ret = vfs_read(fp, (char *)addr, (u32) stat.size, &fp->f_pos);
	if (ret < 0)
		print_error("read file error!, %s , ret=%d\n", filename, ret);

	/* must have the following 1 statement */
	set_fs(fs);

error_out:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}

void init_queue(data_queue_t *data_queue, camera_state state)
{
	unsigned long lock_flags;
	print_debug("enter %s", __func__);

	spin_lock_irqsave(&data_queue->queue_lock, lock_flags);
	INIT_LIST_HEAD(&data_queue->ready_q[state]);
	INIT_LIST_HEAD(&data_queue->work_q[state]);
	INIT_LIST_HEAD(&data_queue->done_q[state]);
	init_waitqueue_head(&data_queue->queue[state]);
	spin_unlock_irqrestore(&data_queue->queue_lock, lock_flags);
}

/*
 **************************************************************************
 * FunctionName: del_from_queue;
 * Description : Remove buffer from the corresponding queue: ready queue,
 *               work queue and done queue;
 * Input       : f: buffer pointer;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
inline void del_from_queue(camera_frame_buf *f, u32 flag)
{
	if (f->flags & flag) {
		list_del(&f->queue);
		f->flags &= (~flag);
	} else {
		print_warn("frame[%08x] NOT in queue with flag[%d]", f->phyaddr, flag);
	}
}

/*
 **************************************************************************
 * FunctionName: add_to_queue
 * Description : add buffer to the corresponding queue;
 * Input       : f: buffer pointer;
 *               l: list head that buffer 'f' need to be added;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
inline void add_to_queue(camera_frame_buf *f, struct list_head *l, u32 flag)
{
	if (!(f->flags & flag)) {
		list_add_tail(&f->queue, l);
		f->flags |= flag;
	} else {
		print_warn("frame[%08x] has been added to queue with flag[%d]", f->phyaddr, flag);
	}
}
/*
 **************************************************************************
 * FunctionName: get_queue_size
 * Description : get nodes count of queue
 * Input       : l: buffer pointer;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
inline int get_queue_size(struct list_head *l)
{
	struct list_head *pos = NULL, *tmp = NULL;
	int size = 0;
	list_for_each_safe(pos, tmp, l) size++;
	return size;
}

/*
 **************************************************************************
 * FunctionName: reset_buffer;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void reset_buffer(camera_frame_buf *buf, int count)
{
	int i = 0;
	for (i = 0; i < count; ++i) {
		buf[i].flags = 0;
		INIT_LIST_HEAD(&(buf[i].queue));
	}
}

void camera_free_ion_handle(struct ion_client *ion_client, buffer_arr_t *pbuf)
{
    int i = 0;

    print_info("enter %s.", __func__);

    if((NULL == ion_client) || (NULL == pbuf)){
        print_error("%s:ion_client=%p,pbuf=%p.", __func__,ion_client,pbuf);
        return;
    }

    /* release ion handle */
    for (i = 0; i < pbuf->buf_count; i++) {        if(pbuf->buffers[i].viraddr != NULL){
            ion_unmap_kernel(ion_client, pbuf->buffers[i].ion_handle);
            pbuf->buffers[i].viraddr = NULL;
        }

        ion_unmap_iommu(ion_client, pbuf->buffers[i].ion_handle);
        if(pbuf->buffers[i].ion_handle != NULL){
            print_info("%s:ion_client=%p,i=%d,handle=%p.", __func__,ion_client,i,pbuf->buffers[i].ion_handle);
            ion_free(ion_client, pbuf->buffers[i].ion_handle);
            pbuf->buffers[i].ion_handle = NULL;
        }
    }
}

void camera_init_buffer(buffer_arr_t *pbuf)
{
	print_debug("enter %s", __func__);

	memset(pbuf->buffers, 0x00, ((sizeof(camera_frame_buf)) * MAX_FRAME_NR));
	pbuf->buf_count = 0;
	reset_buffer(pbuf->buffers, MAX_FRAME_NR);
}

/*
 **************************************************************************
 * FunctionName: bits_per_pixel;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
u32 bits_per_pixel(u32 pix_fmt)
{
	switch (pix_fmt) {
	case V4L2_PIX_FMT_RAW8:
	    return 8;
	case V4L2_PIX_FMT_RAW10:
	case V4L2_PIX_FMT_RAW12:
	case V4L2_PIX_FMT_RAW14:
		return 16;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
    case V4L2_PIX_FMT_YUV420:
		return 12;
	case V4L2_PIX_FMT_YUYV:
		return 16;
	default:
		print_error("Bad format: %#x", pix_fmt);
		return 12;
	}
}

/************************* END ******************************/
