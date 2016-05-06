/*
 * blackbox header file (blackbox: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __BB_DEBUG_H__
#define __BB_DEBUG_H__

#include <linux/types.h>

#ifdef CONFIG_HISI_BB_DEBUG
int rdr_debug_init(void);
#else
int rdr_debug_init(void)
{
	return 0;
}
#endif /* End #define CONFIG_HISI_BB_DEBUG */

#endif /* End #define __BB_DEBUG_H__ */
