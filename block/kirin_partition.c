/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文    件  名   : mmc_partition.c
  版    本  号   : 初稿
  作            者   : denghao 00221160
  生成日期   : 2015年11月3日
  最近修改   :
  功能描述   : mmc partition 接口
  函数列表   :
  修改历史   :
  日            期   : 2015年11月3日
  作            者   : denghao 00221160
  修改内容   : 创建文件
******************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/ctype.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/debugfs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/of_gpio.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/unistd.h>
#include <linux/sort.h>
#include <linux/err.h>
#include <linux/workqueue.h>
#include <asm/uaccess.h>
#include <linux/mmc/host.h>
#include <linux/sysfs.h>
#include <linux/semaphore.h>
#include <linux/stat.h>
#include <linux/hisi/util.h>

#include <partition.h>

/*partition interface*/
int current_ptn_num = sizeof(partition_table) / sizeof(struct partition);

int flash_find_ptn(const char* str, char* pblkname)
{
	unsigned int n;
	char block_str[] = "/dev/block/mmcblk0p";
	char ptn_num[3] = {0};

	if (NULL == pblkname) {
		printk(KERN_ERR "pblkname is null\n");
		return -1;
	}

	for(n = 1; n < current_ptn_num; n++) {
		if(partition_table[n].name != 0 && (!strcmp(partition_table[n].name, str))) {
			snprintf(ptn_num, sizeof(ptn_num), "%d", n - 1);
			strncpy(pblkname, block_str, strlen(block_str));
			strncpy(pblkname + strlen(block_str), ptn_num, strlen(ptn_num)+1);
			return 0;
		}
	}
	printk(KERN_ERR "partition is not found\n");
	return -1;
}
EXPORT_SYMBOL(flash_find_ptn);

int get_cunrrent_total_ptn_num(void)
{
	return current_ptn_num - 3;
}
EXPORT_SYMBOL(get_cunrrent_total_ptn_num);

unsigned int flash_get_ptn_index(const char* pblkname)
{
	unsigned int n;

	if (NULL == pblkname) {
		printk(KERN_ERR "pblkname is null\n");
		return -1;
	} else if (PART_XLOADER == pblkname) {
		printk(KERN_ERR "This is boot partition\n");
		return -1;
	}

	for(n = 1; n < current_ptn_num; n++) {
		if(partition_table[n].name != 0 &&(!strcmp(partition_table[n].name, pblkname))) {
			return n;
		}
	}
	printk(KERN_ERR "partition is not found\n");
	return -1;
}
EXPORT_SYMBOL(flash_get_ptn_index);


