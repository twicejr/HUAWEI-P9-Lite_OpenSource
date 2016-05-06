/*
 * Copyright (C) 2014 Hisilicon, Inc.
 *
 * Author:
 *	Bintian Wang <bintian.wang@huawei.com>
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


#ifndef __MACH_HI6620_IOMAP_H
#define __MACH_HI6620_IOMAP_H

#include <asm/sizes.h>
#include <linux/mm.h>
#include <global_ddr_map.h>
#include "MemoryMap.h"
#include <hisi/hi6xxx-platform.h>

#define IO_TO_VIRT_BETWEEN(p, name)	(((p) >= (REG_BASE_##name)) && ((p) < ((REG_BASE_##name) + (REG_##name##_IOSIZE))))
#define IO_TO_VIRT_XLATE(p, name)	(((p) - (REG_BASE_##name) + (REG_BASE_##name##_VIRT)))

#define IPC_SHARE_MEM_TO_VIRT_BETWEEN(p)  (((p) >= (IPC_SHARE_MEM_ADDR)) && ((p) < ((IPC_SHARE_MEM_ADDR) + (IPC_SHARE_MEM_SIZE))))
#define IPC_SHARE_MEM_TO_VIRT_XLATE(p)	(((p) - (IPC_SHARE_MEM_ADDR) + (IPC_SHARE_MEM_VIRT_ADDR)))

#define IO_TO_VIRT(n) ( \
	IO_TO_VIRT_BETWEEN((n), SRAM_OFF) ?	\
		IO_TO_VIRT_XLATE((n), SRAM_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), SRAM_ON) ?	\
		IO_TO_VIRT_XLATE((n), SRAM_ON) : 	\
	IO_TO_VIRT_BETWEEN((n), SC_OFF) ?	\
		IO_TO_VIRT_XLATE((n), SC_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), SC_ON) ?	\
		IO_TO_VIRT_XLATE((n), SC_ON) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER0) ?	\
		IO_TO_VIRT_XLATE((n), TIMER0) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER3) ?	\
		IO_TO_VIRT_XLATE((n), TIMER3) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER4) ?	\
		IO_TO_VIRT_XLATE((n), TIMER4) : 	\
	IO_TO_VIRT_BETWEEN((n), IPF) ?	\
		IO_TO_VIRT_XLATE((n), IPF) : 	\
	IO_TO_VIRT_BETWEEN((n), L2CC) ?	\
		IO_TO_VIRT_XLATE((n), L2CC) : \
	IO_TO_VIRT_BETWEEN((n), PMCTRL) ?	\
		IO_TO_VIRT_XLATE((n), PMCTRL) : \
	IO_TO_VIRT_BETWEEN((n), A9PRI) ?	\
		IO_TO_VIRT_XLATE((n), A9PRI) : 	\
	IO_TO_VIRT_BETWEEN((n), IOC_OFF) ?	\
		IO_TO_VIRT_XLATE((n), IOC_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), IOC_ON) ?	\
		IO_TO_VIRT_XLATE((n), IOC_ON) : 	\
	IO_TO_VIRT_BETWEEN((n), IPC_NS) ?	\
		IO_TO_VIRT_XLATE((n), IPC_NS) : 	\
	IPC_SHARE_MEM_TO_VIRT_BETWEEN((n))? \
	    IPC_SHARE_MEM_TO_VIRT_XLATE((n)): \
	    0)

#define IO_ADDRESS(n) (IO_TO_VIRT(n))

#endif
