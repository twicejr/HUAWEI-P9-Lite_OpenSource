/* drivers/misc/apanic_mmc.h
 *
 * Copyright (C) 2010 Motorola, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 */
#ifndef DRIVERS_MISC_APANIC_MMC_H
#define DRIVERS_MISC_APANIC_MMC_H

extern int log_buf_copy(char *dest, int idx, int len);
extern void log_buf_clear(void);

#define memdump_wdt_disable() do {} while (0);

#endif
