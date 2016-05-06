/*
 * blackbox header file (blackbox: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __BB_PRINTER_H__
#define __BB_PRINTER_H__

#include <linux/types.h>

#ifdef CONFIG_HISI_BB_DEBUG
#define BB_PRINT_PN(args...)    printk(KERN_ERR args);
#define BB_PRINT_ERR(args...)   printk(KERN_ERR args);
#define BB_PRINT_DBG(args...)   printk(KERN_DEBUG args);
#define BB_PRINT_START(args...) \
	printk(KERN_INFO ">>>>>enter blackbox %s: %.4d.\n", __func__, __LINE__);
#define BB_PRINT_END(args...)   \
	printk(KERN_INFO "<<<<<exit  blackbox %s: %.4d.\n", __func__, __LINE__);
#else
#define BB_PRINT_PN(args...)
#define BB_PRINT_ERR(args...)
#define BB_PRINT_DBG(args...)
#define BB_PRINT_START(args...)
#define BB_PRINT_END(args...)
#endif

void rdr_print_all_ops(void);
void rdr_print_all_exc(void);

#endif /* End #define __BB_PRINTER_H__ */
