/*
  * hisilicon udp board id driver, hisi_udp_board_id.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/smp.h>
#include <hisi_udp_board_id.h>
#include <linux/string.h>

#define UDP_BOARDID_MAX_COUNT		10
#define	UDP_BOARDID_SIZE		8

#define	UDP_BIDV_D2			"V3MM3A10"
#define	UDP_BIDV_JDI			"V3MM3A20"
#define	DEFAULT_TYPE_LCD		JDI_TYPE_LCD

/* board id buffer */
static unsigned char udp_bid_buf[UDP_BOARDID_MAX_COUNT][UDP_BOARDID_SIZE];

/******************************************************************************
Function:	    read_lcd_type
Description:	    读取MMU扣板对应的LCD类型
Input:		    none
Output:		    none
Return:		    01: D2_TYPE_LCD  02: JDI_TYPE_LCD 其他: ERROR
******************************************************************************/
int read_lcd_type(void)
{
	int i;
	for (i=0; i<UDP_BOARDID_MAX_COUNT; i++) {
		if (0 == udp_bid_buf[i][0]) {
			/* search end */
			pr_info("%s : found no udp board id.\n", __func__);
			return DEFAULT_TYPE_LCD;
		} else if (0 == strncmp(UDP_BIDV_JDI, udp_bid_buf[i], UDP_BOARDID_SIZE)) {
			/* find JDI udp board id */
			pr_info("%s : found jdi lcd.\n", __func__);
			return JDI_TYPE_LCD;
		} else if (0 == strncmp(UDP_BIDV_D2, udp_bid_buf[i], UDP_BOARDID_SIZE)) {
			/* find D2 udp board id */
			pr_info("%s : found d2 lcd.\n", __func__);
			return D2_TYPE_LCD;
		}
	}

	pr_info("%s : found no udp board id.\n", __func__);
	return DEFAULT_TYPE_LCD;
}
EXPORT_SYMBOL_GPL(read_lcd_type);

static int __init early_parse_udp_board_id_cmdline(char *arg)
{
	int len = 0;
	memset(udp_bid_buf, 0, sizeof(udp_bid_buf));
	if (arg) {
		len = strlen(arg);
		if(len%UDP_BOARDID_SIZE != 0){
			pr_err("%s : board id size is worng!\n", __func__);
			return 0;
		}

		if (len > sizeof(udp_bid_buf)) {
			len = sizeof(udp_bid_buf);
		}
		pr_info("%s:arg = %s\n", __func__, arg);
		memcpy(udp_bid_buf, arg, len);
	} else {
		pr_info("%s : arg is NULL\n", __func__);
	}

	return 0;
}
early_param("udp_board_id", early_parse_udp_board_id_cmdline);
