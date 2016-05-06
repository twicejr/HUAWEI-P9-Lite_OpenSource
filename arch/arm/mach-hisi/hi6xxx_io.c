/*
 * arch/arm/mach-hisi/hi6210-io.c
 *
 * Copyright (C) 2014 Hisilicon, Inc.
 *
 * Author:
 *		Bintian Wang <bintian.wang@huawei.com>
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/io.h>

#include <asm/page.h>
#include <asm/mach/map.h>

#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */

/* P:0xFFF80000 V:0xFFF80000 SIZE:72KB */
#define REG_BASE_SRAM_OFF_VIRT    (0xFFF80000)

static struct map_desc hi6210_io_desc[] __initdata = {
	{
		.virtual = (unsigned long)REG_BASE_SRAM_OFF_VIRT,
		.pfn = __phys_to_pfn(REG_BASE_SRAM_OFF),
		.length = REG_SRAM_OFF_IOSIZE,
		.type = MT_MEMORY_ITCM,
	},
};

void __init hi6210_map_common_io(void)
{
	iotable_init(hi6210_io_desc, ARRAY_SIZE(hi6210_io_desc));

}

