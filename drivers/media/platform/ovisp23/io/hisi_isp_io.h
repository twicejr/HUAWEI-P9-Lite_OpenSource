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

#ifndef _HI_ISP_IO_H_
#define _HI_ISP_IO_H_

#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/printk.h>

#define COMMAND_BUFFER_END	(0x34fff)
#define ISP_COMMAND_BEGIN	(0x60000)
#define ISP_COMMAND_END		(0x6ffff)

/* big-endian to little-endian */
#define ISP_BIG_ENDIAN(a) ((a) + 3 - 2 * ((a) & 0x3))

extern void __iomem * isp_base;

#define GETREG8_ISPHW(reg) \
	(*(volatile unsigned char *)(isp_base + (((reg) - 0x30000) << 2)))
#define SETREG8_ISPHW(reg, value) \
	(*((volatile unsigned char *)(isp_base + (((reg) - 0x30000) << 2))) = (value))

#define GETREG8(reg) \
	(((reg) >= COMMAND_BUFFER_END) ? \
		(((reg) >= ISP_COMMAND_BEGIN && (reg) <= ISP_COMMAND_END) ? \
			((*(volatile unsigned char *)(isp_base + (((reg) - 0x30000) << 2))) & 0xff) : \
			(*(volatile unsigned char *)(isp_base +(reg)))) : \
		(*(volatile unsigned char *)(isp_base + ISP_BIG_ENDIAN((reg)))))

#define SETREG8(reg, value) \
	(((reg) >= COMMAND_BUFFER_END) ? \
		(((reg) >= ISP_COMMAND_BEGIN && (reg) <= ISP_COMMAND_END) ? \
			(*((volatile unsigned char *)(isp_base + ((reg - 0x30000) << 2))) = (value)) : \
			(*((volatile unsigned char *)(isp_base + reg)) = (value))) : \
		(*((volatile unsigned char *)(isp_base + ISP_BIG_ENDIAN(reg))) = (value)))

#define GETREG32(reg, value) \
	do { \
		(value) = (GETREG8(reg) << 24) + \
			(GETREG8((reg) + 1) << 16) + \
			(GETREG8((reg) + 2) << 8) + \
			(GETREG8((reg) + 3)); \
	} while (0)

#define GETREG16(reg, value) \
	do { \
		(value) = (GETREG8(reg) << 8) + \
		(GETREG8((reg) + 1)); \
	} while (0)

#define SETREG16(reg, value) \
	do { \
		SETREG8((reg), ((value) >> 8) & 0xff); \
		SETREG8((reg) + 1, (value) & 0xff);    \
	} while (0)

#define SETREG32(reg, value) \
	do { \
		SETREG8(reg,     ((value) >> 24) & 0xff); \
		SETREG8(reg + 1, ((value) >> 16) & 0xff); \
		SETREG8(reg + 2, ((value) >> 8) & 0xff);  \
		SETREG8(reg + 3, ((value) >> 0) & 0xff);  \
	} while (0)

#define MY_GETREG32(reg) \
		((GETREG8(reg) << 24) + \
		(GETREG8((reg) + 1) << 16) + \
		(GETREG8((reg) + 2) << 8) + \
		GETREG8((reg) + 3))

#define MY_GETREG16(reg) ((GETREG8(reg) << 8) + GETREG8((reg) + 1))

#define get_writeback_expo(flow) \
	(GETREG8(REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)) ? \
	MY_GETREG32(REG_FW_AECAGC_MANUAL_EXPO(flow)) : MY_GETREG32(REG_FW_WRITEBACK_EXPO(flow)))

#define get_writeback_gain(flow) \
	(GETREG8(REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)) ? \
	MY_GETREG16(REG_FW_AECAGC_MANUAL_GAIN(flow)) : MY_GETREG16(REG_FW_WRITEBACK_GAIN(flow)))

extern unsigned int CSI_GETREG32(unsigned int reg);
extern void CSI_SETREG32(unsigned int reg, unsigned int val);
extern void io_set_isp_base(unsigned long isp_base_addr);

#endif