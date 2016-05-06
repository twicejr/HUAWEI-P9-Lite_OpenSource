/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/printk.h>
#include "hisi_isp_io.h"

void __iomem * isp_base;

unsigned int CSI_GETREG32(unsigned int reg)
{
	//cam_info("%s enter reg=0x%x.\n", __func__, reg);
	return ioread32((volatile unsigned int*)(isp_base + reg));
}

void CSI_SETREG32(unsigned int reg, unsigned int val)
{
	//cam_info("%s enter reg=0x%x,val=0x%x.\n", __func__, reg, val);
	iowrite32(val, (volatile void*)(isp_base + reg));
}

void io_set_isp_base(unsigned long isp_base_addr)
{
	isp_base = isp_base_addr;
}
