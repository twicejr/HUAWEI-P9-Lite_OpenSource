/* include/linux/logger.h
 *
 * Copyright (C) 2007-2008 Google, Inc.
 * Author: Robert Love <rlove@android.com>
 *
 * Copyright (C) Huawei Technologies Co., Ltd.
 * 2014-05-13 - changed several functins, decribed as follow:
 * [1]add function a_cshell_write
 * [2]replace functions used to copy data from userspace with memcpy and so on
 * [3]modify logger_init function to delete other two file nodes
 * [4]modify some macros, such as headerfile control macro and buffer size macro
 * [5]add function declaration
 * wangxiandong <foss@huawei.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef    _CSHELL_LOGGER_H_
#define    _CSHELL_LOGGER_H_


#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>

struct logger_entry {
	__u16		len;	/* length of the payload */
	__u16		__pad;	/* no matter what, we get 2 bytes of padding */
	__s32		pid;	/* generating process's pid */
	__s32		tid;	/* generating process's tid */
	__s32		sec;	/* seconds since Epoch */
	__s32		nsec;	/* nanoseconds */
	char		msg[0];	/* the entry's payload */
};

struct logger_log_tag {
	unsigned char*		tag_save_buff;
	struct mutex		mutex;
};
struct logger_log {
	unsigned char		*buffer;/* the ring buffer itself */
	struct miscdevice	misc;	/* misc device representing the log */
	wait_queue_head_t	wq;	/* wait queue for readers */
	struct list_head	readers; /* this log's readers */
	struct mutex		mutex;	/* mutex protecting buffer */
	size_t			w_off;	/* current write head offset */
	size_t			head;	/* new readers start here */
	size_t			size;	/* size of the log */
};
/*
 * struct logger_reader - a logging device open for reading
 *
 * This object lives from open to release, so we don't need additional
 * reference counting. The structure is protected by log->mutex.
 */
struct logger_reader {
	struct logger_log	*log;	/* associated log */
	struct list_head	list;	/* entry in logger_log's list */
	size_t			r_off;	/* current read head offset */
};

#define LOGGER_ENTRY_MAX_LEN		(512 + sizeof(struct logger_entry))/*(4*1024)*/
#define LOGGER_ENTRY_MAX_PAYLOAD	\
	(LOGGER_ENTRY_MAX_LEN - sizeof(struct logger_entry))

int a_cshell_write(int log_left, const void * in_buff);
#endif