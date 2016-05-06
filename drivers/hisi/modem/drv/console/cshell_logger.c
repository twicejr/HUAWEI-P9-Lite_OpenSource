/*
 * drivers/misc/logger.c
 *
 * A Logging Subsystem
 *
 * Copyright (C) 2007-2008 Google, Inc.
 *
 * Robert Love <rlove@google.com>
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
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/kallsyms.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include <linux/wait.h>

#include <osl_types.h>
#include <osl_bio.h>
#include <bsp_shared_ddr.h>
#include <bsp_icc.h>
#include <bsp_modem_log.h>
#include <hi_uart.h>
#include "cshell_logger.h"

#define CSHELL_TAG_BUFF_SIZE 		(8*1024)
#define LOGGER_LOG_CSHELL			"cshell_log"
#define cshell_log_debug(fmt, ...)  pr_debug("[cshell logger]: " fmt, ##__VA_ARGS__) 
#define cshell_log_err(fmt, ...)    pr_err("[cshell logger]: " fmt, ##__VA_ARGS__)

static unsigned char _buf_cshell_log[CSHELL_TAG_BUFF_SIZE];

/**
 * struct cshell_logger - cshell logger manager struct
 * This structure is allocated by writer
 */
struct cshell_logger
{
	u32 init_flag;                /* module init flag */
	u32 threshold;                /* threshold to trigger file write from ring buffer to log record file */
	struct log_mem log_mem;       /* log memory to management ring buffer */
	struct log_usr_info log_info; /* log info to register to modem log */
};
static struct cshell_logger g_cshell_logger;

/**
 * cshell_log_writable_size_get - space left to write
 */
static inline u32 cshell_log_writable_size_get(u32 write, u32 read, u32 ring_buffer_size)
{
	return (read > write)? (read - write): (ring_buffer_size - write + read); 
}

/**
 * cshell_log_open - indicate that our memory(ring buffer) is ready
 */
int cshell_log_open(struct log_usr_info *usr_info)
{
	usr_info->mem       = (struct log_mem *)&g_cshell_logger.log_mem;
	usr_info->ring_buf  = (char *)_buf_cshell_log;
	usr_info->mem_is_ok = 1;
	cshell_log_debug("%s entry\n", __func__);

	return 0;
}

/**
 * cshell_log_read - indicate that our memory(ring buffer) is ready
 */
int cshell_log_read(struct log_usr_info *usr_info, char *buf, u32 count)
{
	u32 write_p = usr_info->mem->write;
	u32 read_p  = usr_info->mem->read;

	/* new log message will be abandoned */
    if(cshell_log_writable_size_get(write_p, read_p, usr_info->mem->size) <= 200)
    {
        usr_info->mem->read = usr_info->mem->write;
	}
	cshell_log_debug("%s entry\n", __func__);
	return 0;
}

static u32 do_write_log(void* dest, u32 destMax, const void* src, u32 count)
{
	memcpy(dest, src, count);
	return 0;
}

int a_cshell_write(int log_left, const void * in_buff)
{
	struct ring_buffer rb;
	int ret = 0;

	if (!g_cshell_logger.init_flag)
	{
		ret = -1;
		return ret;
	}

	rb.size  = g_cshell_logger.log_mem.size;
	rb.read  = g_cshell_logger.log_mem.read;
	rb.write = g_cshell_logger.log_mem.write;
	rb.buf   = (char *)_buf_cshell_log;
	log_left = min(log_left, (int)LOGGER_ENTRY_MAX_PAYLOAD);

	ret = bsp_ring_buffer_in(&rb, (void *)in_buff, log_left, (MEMCPY_FUNC)do_write_log);
	g_cshell_logger.log_mem.write = rb.write;

	/* write length > threshold, try to trigger file write */
	if (bsp_ring_buffer_writen_size(&rb) > g_cshell_logger.threshold)
	{
		bsp_modem_log_fwrite_trigger(&g_cshell_logger.log_info);
	}

	return ret;
}

static int cshell_logger_init(void)
{
	memset((void *)&g_cshell_logger, 0, sizeof(g_cshell_logger));

	g_cshell_logger.log_mem.size = (u32)sizeof(_buf_cshell_log);
	g_cshell_logger.log_mem.app_is_active = 0;

	g_cshell_logger.log_info.dev_name = LOGGER_LOG_CSHELL;
	g_cshell_logger.log_info.read_func = (USR_READ_FUNC)cshell_log_read;
	g_cshell_logger.log_info.open_func = (USR_OPEN_FUNC)cshell_log_open;
	g_cshell_logger.log_info.mem       = (struct log_mem *)&g_cshell_logger.log_mem;
	g_cshell_logger.log_info.ring_buf  = (char *)_buf_cshell_log;
	g_cshell_logger.log_info.mem_is_ok = 1;
    if(bsp_modem_log_register(&g_cshell_logger.log_info))
    {
        cshell_log_err("register to modem log fail\n");
        return -1;
    }

	g_cshell_logger.threshold = CSHELL_TAG_BUFF_SIZE / 2;
	g_cshell_logger.init_flag = 1;
    cshell_log_err("init ok\n");
	return 0;
}

module_init(cshell_logger_init);
