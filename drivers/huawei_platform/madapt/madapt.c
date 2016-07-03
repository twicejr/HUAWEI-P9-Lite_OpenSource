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
 * *	notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *	notice, this list of conditions and the following disclaimer in the
 * *	documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *	be used to endorse or promote products derived from this software
 * *	without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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

/*lint --e{533,830}*/
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG madapt
HWLOG_REGIST();



#define BSP_ERR_MADAPT_OK					(0)
#define BSP_ERR_MADAPT_PARAM_ERR			(1)
#define BSP_ERR_MADAPT_MALLOC_FAIL			(2)
#define BSP_ERR_MADAPT_COPY_FROM_USER_ERR	(3)
#define BSP_ERR_MADAPT_OPEN_FILE_ERR		(4)
#define BSP_ERR_MADAPT_FILE_SIZE_ERR		(5)
#define BSP_ERR_MADAPT_READ_FILE_ERR		(6)
#define BSP_ERR_MADAPT_FILE_HDR_CHECK_ERR	(7)
#define BSP_ERR_MADAPT_NV_HDR_CHECK_ERR		(8)
#define BSP_ERR_MADAPT_WRITE_NV_ERR			(9)
#define BSP_ERR_MADAPT_TIMEOUT				(10)
#define BSP_ERR_MADAPT_PTR_NULL				(11)

#define BSP_ERR_MADAPT_COMMON_ERR			(100)

#define MADAPT_DEVICE_NAME				"madapt"
#define MADAPT_DEVICE_CLASS				"madapt_class"
#define MADAPT_FILE_MAX_SIZE			(1024*1024)
#define MADAPT_MAX_USER_BUFF_LEN		(64)
#define MADAPT_NV_ITEM_RANGE1_START		(0)
#define MADAPT_NV_ITEM_RANGE1_END		(10000)
#define MADAPT_NV_ITEM_RANGE2_START		(50000)
#define MADAPT_NV_ITEM_RANGE2_END		(60000)
#define MADAPT_FILE_END_FLAG			(0xFFFFFFFF)
#define MADAPT_MIN_NV_MODEM_ID			(1)
#define MADAPT_MAX_NV_MODEM_ID			(3)
#define MADAPT_NVFILE_PATH	"/system/etc/modemConfig/nvcfg/"
#define MADAPT_NVFILE_VERSION			(0x0601)


#define MADAPT_MODEMID_CONVERT(x)		(x-1)

struct madapt_file_stru {
	unsigned int len;
	char file[MADAPT_MAX_USER_BUFF_LEN];
};

struct madapt_header_type {
	char pad[256];
};

struct madapt_item_hdr_type {
	unsigned int     nv_item_number;
	unsigned int     nv_modem_id;
	unsigned int     nv_item_size;
};

struct my_work_struct {
	int test;
	struct work_struct proc_nv;
};

static struct cdev cdev;
static unsigned int madapt_major;
static struct class *madapt_class;
static struct madapt_file_stru *kbuf;
static struct completion my_completion;
static struct my_work_struct test_work;
static ssize_t work_ret = BSP_ERR_MADAPT_OK;

/*lint -save -e438*/
/*lint -save -e745 -e601 -e49 -e65 -e64 -e533 -e830*/
ssize_t madapt_dev_read(struct file *file, char __user *buf, size_t count,
								loff_t *ppos);
ssize_t madapt_dev_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos);

static const struct file_operations nv_fops = {
	.owner	 = THIS_MODULE,
	.read	 = madapt_dev_read,
	.write	 = madapt_dev_write,
};

extern unsigned int mdrv_nv_writeex(unsigned int modemid,
		unsigned int itemid, void *pdata, unsigned int ulLength);

/*lint -restore +e745 +e601 +e49 +e65 +e64 +e533 +e830*/
/*
data stru:
	---------------------------------------------
	| NV ID | data length |	data	  |
	---------------------------------------------
*/

/*lint -save --e{529,527}*/
ssize_t madapt_dev_read(struct file *file, char __user *buf, size_t count,
								loff_t *ppos){
#if 0
	ssize_t ret;
	struct nv_data_stru *kbuf = NULL;


	if ((NULL == buf)
		|| (count <= NV_HEAD_LEN)
		|| (count > NV_MAX_USER_BUFF_LEN)) {
		return BSP_ERR_NV_INVALID_PARAM;
	}

	kbuf = kmalloc(count+1, GFP_KERNEL);
	if (NULL == kbuf) {
		return BSP_ERR_NV_MALLOC_FAIL;
	}

	if (copy_from_user(kbuf, buf, count)) {
		kfree(kbuf);
		return -1;
	}

	/* coverity[tainted_data] */
	ret = (ssize_t)bsp_nvm_read(kbuf->nvid, kbuf->data, kbuf->len);
	if (ret) {
		kfree(kbuf);
		return ret;
	}

	ret = (ssize_t)copy_to_user(buf, kbuf, count);
	if (ret) {
		kfree(kbuf);
		return ret;
	}

	kfree(kbuf);
	return (ssize_t)count;
#endif
	return 0;
}
/*lint -restore*/

static int madapt_header_verify(struct madapt_header_type *header)
{
	if (MADAPT_NVFILE_VERSION != (*((unsigned short *)header))) {
		hwlog_err("madapt_header_verify, file header version[0x%x] check fail!\n",
			(*((unsigned short *)header)));
		return -1;
	}
	return 0;
}

static int madapt_parse_and_writenv(char *ptr, int len)
{
	unsigned int ret = 0;
	struct madapt_item_hdr_type nv_header;

	memset(&nv_header, 0, sizeof(struct madapt_item_hdr_type));
	do {
		nv_header.nv_item_number
			= ((struct madapt_item_hdr_type *)ptr)->nv_item_number;
		if (MADAPT_FILE_END_FLAG == nv_header.nv_item_number) {
			hwlog_err("madapt_parse_and_writenv, find nv file end flag.\n");
			break;
		}
		nv_header.nv_modem_id
			= ((struct madapt_item_hdr_type *)ptr)->nv_modem_id;
		nv_header.nv_item_size
			= ((struct madapt_item_hdr_type *)ptr)->nv_item_size;
		ptr += sizeof(struct madapt_item_hdr_type);

		if (((nv_header.nv_item_number > MADAPT_NV_ITEM_RANGE1_END)
		&& (nv_header.nv_item_number < MADAPT_NV_ITEM_RANGE2_START))
		|| (nv_header.nv_item_number > MADAPT_NV_ITEM_RANGE2_END)
			|| ((nv_header.nv_modem_id < MADAPT_MIN_NV_MODEM_ID)
			|| (nv_header.nv_modem_id > MADAPT_MAX_NV_MODEM_ID))
			|| (0 == nv_header.nv_item_size)) {
			hwlog_err("madapt_parse_and_writenv, invalid nv header: nv id: [%d], nv modemid: [%d], nv size: [%d].\n",
					nv_header.nv_item_number,
					nv_header.nv_modem_id,
					nv_header.nv_item_size);
			return BSP_ERR_MADAPT_NV_HDR_CHECK_ERR;
		}

		ret = mdrv_nv_writeex(
			MADAPT_MODEMID_CONVERT(nv_header.nv_modem_id),
						nv_header.nv_item_number,
						ptr,
						nv_header.nv_item_size);
		if (0 != ret) {
			hwlog_err("madapt_parse_and_writenv, nv[%d] with modemid[%d] and size[%d] write fail, ret=%d.\n",
					nv_header.nv_item_number,
					nv_header.nv_modem_id,
					nv_header.nv_item_size,
					ret);
			return BSP_ERR_MADAPT_WRITE_NV_ERR;
		}

		ptr += nv_header.nv_item_size;
		len -= (sizeof(struct madapt_item_hdr_type)
			+ nv_header.nv_item_size);
	} while (len > 0);

	return BSP_ERR_MADAPT_OK;
}


static int parse_wirte_file(struct madapt_file_stru *file)
{
	struct file *fp = NULL;
	char filepath[128] = MADAPT_NVFILE_PATH;
	mm_segment_t fs = {0};
	loff_t pos = 0;
	int ret_size = 0;
	int size = 0;
	int ret = BSP_ERR_MADAPT_OK;
	char *k_buffer = NULL;
	struct madapt_header_type head;

	memset(&head, 0, sizeof(struct madapt_header_type));

	if (NULL == file) {
		hwlog_err("parse_wirte_file, NULL ptr!\n");
		return BSP_ERR_MADAPT_PTR_NULL;
	} else {
		hwlog_err("parse_wirte_file, file: %s, len: %d\n",
			file->file, file->len);
	}

	if (file->len > MADAPT_MAX_USER_BUFF_LEN) {
		hwlog_err("parse_wirte_file, file->len(%d) too large!\n",
					file->len);
		return BSP_ERR_MADAPT_PARAM_ERR;
	}

	strncat(filepath, file->file, strlen(file->file));

	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		hwlog_err("parse_wirte_file, open file error!\n");
		return BSP_ERR_MADAPT_OPEN_FILE_ERR;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	size = fp->f_dentry->d_inode->i_size;
	if ((size <= sizeof(struct madapt_header_type))
		|| (size >= MADAPT_FILE_MAX_SIZE)) {
		hwlog_err("parse_wirte_file, file size(%d) error!\n", size);
		ret = BSP_ERR_MADAPT_FILE_SIZE_ERR;
		goto FILE_PROC_OUT;
	} else {
		hwlog_err("parse_wirte_file, get nvbin file size(%d)!\n", size);
	}

	pos = 0;
	ret_size = vfs_read(fp, (void *)&head, sizeof(head), &pos);
	if (sizeof(head) != ret_size) {
		hwlog_err("parse_wirte_file, error vfs_read ret : %d\n",
			ret_size);
		ret = BSP_ERR_MADAPT_READ_FILE_ERR;
		goto FILE_PROC_OUT;
	}

	ret = madapt_header_verify(&head);
	if (0 != ret) {
		ret = BSP_ERR_MADAPT_FILE_HDR_CHECK_ERR;
		goto FILE_PROC_OUT;
	}

	k_buffer = kmalloc((size-sizeof(struct madapt_header_type)),
		GFP_KERNEL);
	if (NULL == k_buffer) {
		hwlog_err("parse_wirte_file, kmalloc error\n");
		ret = BSP_ERR_MADAPT_MALLOC_FAIL;
		goto FILE_PROC_OUT;
	}

	ret_size = vfs_read(fp, k_buffer,
		(size-sizeof(struct madapt_header_type)), &pos);
	if ((size-sizeof(struct madapt_header_type)) != ret_size) {
		hwlog_err("parse_wirte_file, error vfs_read ret: %d, readsize: %d\n",
			ret_size,
			(int)(size-sizeof(struct madapt_header_type)));
		ret = BSP_ERR_MADAPT_READ_FILE_ERR;
		goto MEM_PROC_OUT;
	}

	ret = madapt_parse_and_writenv(k_buffer,
		(size-sizeof(struct madapt_header_type)));

MEM_PROC_OUT:
	kfree(k_buffer);
	k_buffer = NULL;
FILE_PROC_OUT:
	filp_close(fp, NULL);
	set_fs(fs);
	return ret;
}

static void do_proc_nv_file(struct work_struct *p_work)
{
	work_ret = parse_wirte_file(kbuf);
	if (BSP_ERR_MADAPT_OK != work_ret) {
		hwlog_err("do_proc_nv_file, parse_wirte_file fail with errcode(%d)!\n",
					(int)work_ret);
	} else {
		hwlog_err("do_proc_nv_file, proc all success\n");
	}
	kfree(kbuf);
	kbuf = NULL;
	complete(&(my_completion));
}

/*lint -save --e{529,527}*/
ssize_t madapt_dev_write(struct file *file,
						const char __user *buf,
						size_t count, loff_t *ppos) {
	ssize_t ret = BSP_ERR_MADAPT_OK;
	int ticks_left = 0;

	if (NULL == buf) {
		hwlog_err("madapt_dev_write, get a NULL ptr: buf!\n");
		return BSP_ERR_MADAPT_PARAM_ERR;
	}

	/*hwlog_err("madapt_dev_write, invalid parameter count(%d)!\n",
				(int)count);*/

	if ((count <= sizeof(unsigned int))
		|| (count >= sizeof(struct madapt_file_stru))) {
		hwlog_err("madapt_dev_write, invalid parameter count(%d)!\n",
			(int)count);
		return BSP_ERR_MADAPT_PARAM_ERR;
	}

	kbuf = NULL;
	kbuf = kmalloc(sizeof(struct madapt_file_stru), GFP_KERNEL);
	if (NULL == kbuf) {
		hwlog_err("madapt_dev_write, malloc buf fail!\n");
		return BSP_ERR_MADAPT_MALLOC_FAIL;
	}

	if (copy_from_user(kbuf, buf, count)) {
		hwlog_err("madapt_dev_write, copy from user fail!\n");
		ret = BSP_ERR_MADAPT_COPY_FROM_USER_ERR;
		kfree(kbuf);
		kbuf = NULL;
		goto OUT;
	}

	/* schedule work */
	hwlog_err("madapt_dev_write, schedule work!\n");
	schedule_work(&(test_work.proc_nv));

	ticks_left = wait_for_completion_timeout(&(my_completion), HZ*30);
	if (0 == ticks_left) {
		hwlog_err("madapt_dev_write, wait_for_completion_timeout timeout!\n");
		ret = BSP_ERR_MADAPT_TIMEOUT;
	} else if (BSP_ERR_MADAPT_OK == work_ret) {
		hwlog_err("madapt_dev_write, work proc success! ticks_left:%d\n",
				ticks_left);
		ret = work_ret;
	} else {
		hwlog_err("madapt_dev_write, work proc fail! ticks_left:%d\n",
				ticks_left);
		ret = work_ret;
	}

OUT:
	return ret;
}


/*lint -save --e{529}*/
int madapt_init(void)
{
	int ret = 0;
	dev_t dev = 0;
	unsigned int devno;

	/*dynamic dev num use*/
	ret = alloc_chrdev_region(&dev, 0, 1, MADAPT_DEVICE_NAME);
	madapt_major = MAJOR(dev);

	if (ret) {
		hwlog_err("madapt_init, madapt failed alloc :%d\n",
			madapt_major);
		return ret;
	}

	devno = MKDEV(madapt_major, 0);

	/*setup dev*/
	memset(&cdev, 0, sizeof(struct cdev));

	cdev_init(&cdev, &nv_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &nv_fops;

	ret = cdev_add(&cdev, devno, 1);
	if (ret) {
		hwlog_err("madapt_init, cdev_add fail!\n");
		return ret;
	}

	madapt_class = class_create(THIS_MODULE, MADAPT_DEVICE_CLASS);
	if (IS_ERR(madapt_class)) {
		hwlog_err("madapt_init, class create failed!\n");
		return ret;
	}

	device_create(madapt_class, NULL, devno, NULL, MADAPT_DEVICE_NAME);

	INIT_WORK(&(test_work.proc_nv), do_proc_nv_file);
	init_completion(&(my_completion));

	hwlog_err("madapt_init, complete!\n");
	return BSP_ERR_MADAPT_OK;
}
/*lint -restore*/


void madapt_exit(void)
{
	cdev_del(&cdev);
	class_destroy(madapt_class);
	unregister_chrdev_region(MKDEV(madapt_major, 0), 1);
}

module_init(madapt_init);
module_exit(madapt_exit);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("madapt driver for Hisilicon");
MODULE_LICENSE("GPL");

/*lint -restore*/
