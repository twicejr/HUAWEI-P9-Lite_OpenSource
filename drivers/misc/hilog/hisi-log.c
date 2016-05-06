/*
 * drivers/misc/hilog/k3log.c
 *
 * A Logging Subsystem
 *
 * Copyright (C) 2010- Hisilicon, Inc.
 *
 *
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
#include <linux/mutex.h>
#include <linux/completion.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/rtc.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/huawei/hilog.h>
#include <linux/syscalls.h>
#include <linux/huawei/rdr.h>


int hilog_loaded ; /*used to indicate printk can ioremap*/
EXPORT_SYMBOL(hilog_loaded);


extern volatile log_buffer_head *log_buf_info;
extern volatile unsigned char *res_log_buf;
volatile unsigned char *exception_log_buf;

EXPORT_SYMBOL(exception_log_buf);

static int  __init hisi_log_init(void)
{
	int rc = 0;
#ifdef CONFIG_HISI_RDR
	u32 rdr_int = 0;

	RDR_ASSERT(rdr_afreg(rdr_int, RDR_LOG_BUF_INFO, RDR_STR, LOG_INFO_BUF_LEN));
	log_buf_info = (volatile log_buffer_head *)field_addr(u32, rdr_int);
	RDR_ASSERT(rdr_afreg(rdr_int, RDR_LOG_KERNEL_BUF, RDR_STR, KERNEL_LOG_BUF_LEN));
	res_log_buf = (volatile unsigned char *)field_addr(u32, rdr_int);
	RDR_ASSERT(rdr_afreg(rdr_int, RDR_LOG_EXCEPTION_BUF, RDR_STR, EXCEPTION_LOG_BUF_LEN));
	exception_log_buf = (volatile unsigned char *) field_addr(u32, rdr_int);
#else
	log_buf_info = (volatile log_buffer_head *)ioremap_wc((volatile uint32_t *)HISI_LOG_INFO_BASE, LOG_INFO_BUF_LEN);
	res_log_buf = (volatile unsigned char *)ioremap_wc((volatile uint32_t *)HISI_KERNEL_LOG_BASE, KERNEL_LOG_BUF_LEN);
	exception_log_buf = (volatile unsigned char *)ioremap_wc((volatile uint32_t *)HISI_EXCEPTION_LOG_BASE, EXCEPTION_LOG_BUF_LEN);
	printk("log_buf_info is 0x%p\n", log_buf_info);
	printk("res_log_buf is 0x%p\n", res_log_buf);
#endif
	pr_info("hisi_log_init ok\n");
	hilog_loaded  = 1;

	return rc;
}

static void __init hisi_log_exit(void)
{

}
module_init(hisi_log_init);
module_exit(hisi_log_exit);
MODULE_LICENSE("GPL");
