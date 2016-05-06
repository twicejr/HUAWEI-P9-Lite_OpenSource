/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_ap_test.c
 版 本 号   : 初稿
 作    者   : 刘海龙 00249396
 生成日期   : 2015年3月5日
 最近修改   :
 功能描述   : ap可维可测的测试函数
 修改历史   :
 1.日  期   : 2015年3月5日
   作  者   : 刘海龙 00249396
 修改内容   : 创建文件

 *******************************************************************************/

/*******************************************************************************
  1 头文件包含
 *******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/thread_info.h>
#include <linux/hardirq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <asm/cacheflush.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/spinlock.h>
#include "rdr_hisi_platform.h"
#include "rdr_hisi_ap_ringbuffer.h"
#include "../rdr_inner.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern u64 g_hisiap_addr;
extern u64 get_32k_abs_timer_value(void);

/*****************************************************************************
Description : 测试获取版本信息功能
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void test_get_product_version(void)
{
	char version[32];
	 get_product_version(version, PRODUCT_VERSION_LEN);
}

/*****************************************************************************
Description : 测试hung task
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int test_hung_task_thread_fn(void *data)
{
	int i;
	preempt_disable();
	for (i = 0; i < 1800; i++) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		mdelay(1000);	/* 1s */
	}
	return 0;
}

/*****************************************************************************
 Description : 测试hung task
  History
  1.Date: 2015/02/06
    Author : l00249396
    Modification : Created function
*****************************************************************************/
int test_hung_task(void)
{
	if (!kthread_run(test_hung_task_thread_fn, NULL,
	     "test_hung_task_thread_fn")) {
		printk(KERN_ERR
		       "[%s], kthread_run:test_hung_task_thread_fn failed.\n",
		       __func__);
		return -1;
	}
	printk(KERN_ERR
	       "[%s], kthread_run:test_hung_task_thread_fn start.\n",
	       __func__);
	return 0;
}

/*****************************************************************************
Description : 显示临终遗言模块指定任务调用栈信息
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void ap_exch_task_stack_dump(int taskPid)
{
	pid_t exc_pid = (pid_t) taskPid;
	struct task_struct *task = NULL;

	if (exc_pid < 0) {
		printk("exch_task_stack_dump:invalid param pid[0x%x]\n",
		       exc_pid);
		return;
	}

	task = find_task_by_vpid(exc_pid);
	if (task) {
		show_stack(find_task_by_vpid(exc_pid), NULL);
	} else {
		printk("exch_task_stack_dump:no such a task pid[0x%x]\n",
		     exc_pid);
	}
}

/*****************************************************************************
Description : 显示临终遗言模块指定内存地址内的内容，offset是要访问的异常区的偏移
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void ap_exch_buf_show(unsigned int offset, unsigned int size)
{
	unsigned int add_offset = 0;

	if (!offset || !size) {
		printk("exch_buf_show:invalid param offset[0x%x] size[%d]\n",
		     offset, size);
	}

	add_offset =
	    (offset / (sizeof(unsigned int))) * sizeof(unsigned int);

	ap_exch_hex_dump((unsigned char *)(g_hisiap_addr + add_offset),
			 size, 16);
}

/*****************************************************************************
Description : 打印buf信息，若为ASCII字符则打印字符
input:    buf     待dump地址
       size    内容大小
       per_row 每行打印数据量
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void ap_exch_hex_dump(unsigned char *buf, unsigned int size,
		      unsigned char per_row)
{
	int i, row;
	unsigned char line[140];
	unsigned int left = size;

	if (!buf)
		return;

	per_row = (per_row > 32) ? 32 : per_row;
	if (!per_row) {
		per_row = 16;
	}

	printk("Dump buffer [%p] size [%d]:\n", buf, size);

#define TO_CHAR(a)      (((a) > 9) ? ((a) - 10 + 'A') : ((a) + '0'))
#define IS_PRINTABLE(a) ((a) > 31 && (a) < 127)

	for (row = 0; left; row++) {
		(void)memset(line, ' ', sizeof(line));

		for (i = 0; (i < per_row) && left; i++, left--, buf++) {
			unsigned char val = *buf;

			/* The HEX value */
			line[(i * 3)] = TO_CHAR(val >> 4);
			line[(i * 3) + 1] = TO_CHAR(val & 0x0F);

			/* 若为可显示ASCII字符，则打印该字符，否则打印"." */
			line[(per_row * 3) + 2 + i] =
			    IS_PRINTABLE(val) ? val : '.';
		}

		line[(per_row * 3) + 2 + per_row] = '\0';

		printk("[%4u]: %s\n", row * per_row, line);
	}

#undef TO_CHAR
#undef IS_PRINTABLE
}

typedef void (*FUNC_VOID) (void);

/*****************************************************************************
 Description : 未定义指令异常
  History
  1.Date: 2015/02/06
    Author : l00249396
    Modification : Created function
*****************************************************************************/
int ap_exchUNDEF(void *arg)
{
	int b = 0;
	FUNC_VOID a = (FUNC_VOID) (&b);
	b = 0x12345678;
	a();
	return 0;
}

/*****************************************************************************
 Description : 软中断异常
  History
  1.Date: 2015/02/06
    Author : l00249396
    Modification : Created function
*****************************************************************************/
int ap_exchSWI(void *arg)
{
#ifdef CONFIG_ARM64
	__asm__("        SVC   0x1234   ");
#else
	__asm__("        SWI   0x1234   ");
#endif
	return 0;
}


int ap_exchPABT(void *arg)
{
	FUNC_VOID a = (FUNC_VOID) 0xe0000000;
	a();
	return 0;
}


int ap_exchDABT(void *arg)
{
	*(int *)0xa0000000 = 0x12345678;
	return 0;
}


extern u64 hisi_getcurtime(void);

void ap_get_curtime_slice_diff(void)
{
	u64 diff_curtime, diff_slice;

	diff_curtime = hisi_getcurtime();
	diff_slice = get_32k_abs_timer_value();

	printk("printk_curtime is %llu, 32k_abs_timer_value is %llu.\n",
	       diff_curtime, diff_slice);
}

MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
