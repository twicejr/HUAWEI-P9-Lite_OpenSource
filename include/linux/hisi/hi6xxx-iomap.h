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


#ifndef __MACH_HI6210_IOMAP_H
#define __MACH_HI6210_IOMAP_H

#include <asm/sizes.h>
#include <linux/mm.h>
#include <global_ddr_map.h>
#include "MemoryMap.h"
#include <linux/hisi/hi6xxx-platform.h>


extern unsigned long hisi_lookup_va(unsigned long pa);
extern unsigned long hisi_lookup_pa(unsigned long va);

#define HISI_VA_ADDRESS(pa) (hisi_lookup_va((unsigned long)(pa)))
#define HISI_PA_ADDRESS(va) (hisi_lookup_pa((unsigned long)(va)))


void *hisi_io_memset(void *s, int c, unsigned int count);
void *hisi_io_memcpy(void *dest, const void *src, unsigned int count);
int hisi_io_memcmp(const void *cs, const void *ct, unsigned int count);
#endif
