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
#include "hw_isp_io.h"

unsigned char *hw_isp_base;

unsigned int HW_CSI_GETREG32(unsigned int reg)
{
	//cam_info("%s enter reg=0x%x.\n", __func__, reg);
	return ioread32((unsigned int*)(hw_isp_base + reg));
}

void HW_CSI_SETREG32(unsigned int reg, unsigned int val)
{
	//cam_info("%s enter reg=0x%x,val=0x%x.\n", __func__, reg, val);
	iowrite32(val, (void*)(hw_isp_base + reg));
}

void hw_io_set_isp_base(unsigned char *isp_base_addr)
{
	printk("%s enter, isp_base_addr=0x%p\n", __func__, isp_base_addr);
	hw_isp_base = isp_base_addr;
}
