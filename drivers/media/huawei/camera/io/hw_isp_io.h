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
#define ISP_COMMAND_BEGIN	(0x50000)
#define ISP_COMMAND_END		(0x6ffff)

/* big-endian to little-endian */
#define ISP_BIG_ENDIAN(a) ((a) + 3 - 2 * ((a) & 0x3))

extern unsigned char *hw_isp_base;

#define ISPHW_GETREG8(reg) \
	(*(volatile unsigned char *)(hw_isp_base + (((reg) - 0x30000) << 2)))
#define ISPHW_SETREG8(reg, value) \
	(*((volatile unsigned char *)(hw_isp_base + (((reg) - 0x30000) << 2))) = (value))

#define ISP_GETREG8(reg) \
	(((reg) >= COMMAND_BUFFER_END) ? \
		(((reg) >= ISP_COMMAND_BEGIN && (reg) <= ISP_COMMAND_END) ? \
			((*(volatile unsigned char *)(hw_isp_base + (((reg) - 0x30000) << 2))) & 0xff) : \
			(*(volatile unsigned char *)(hw_isp_base +(reg)))) : \
		(*(volatile unsigned char *)(hw_isp_base + ISP_BIG_ENDIAN((reg)))))

#define ISP_SETREG8(reg, value) \
	(((reg) >= COMMAND_BUFFER_END) ? \
		(((reg) >= ISP_COMMAND_BEGIN && (reg) <= ISP_COMMAND_END) ? \
			(*((volatile unsigned char *)(hw_isp_base + (((reg) - 0x30000) << 2))) = (value)) : \
			(*((volatile unsigned char *)(hw_isp_base + (reg))) = (value))) : \
		(*((volatile unsigned char *)(hw_isp_base + ISP_BIG_ENDIAN(reg))) = (value)))

#define ISP_GETREG32(reg)  ((ISP_GETREG8(reg) << 24) | (ISP_GETREG8((reg) + 1) << 16) | (ISP_GETREG8((reg) + 2) << 8) | (ISP_GETREG8((reg) + 3)))

#define ISP_GETREG16(reg)  ((ISP_GETREG8(reg) << 8) | (ISP_GETREG8((reg) + 1)))

#define ISP_SETREG16(reg, value) \
	do { \
		ISP_SETREG8((reg), ((value) >> 8) & 0xff); \
		ISP_SETREG8(((reg) + 1), (value) & 0xff);    \
	} while (0)

#define ISP_SETREG32(reg, value) \
	do { \
		ISP_SETREG8((reg),     ((value) >> 24) & 0xff); \
		ISP_SETREG8(((reg) + 1), ((value) >> 16) & 0xff); \
		ISP_SETREG8(((reg) + 2), ((value) >> 8) & 0xff);  \
		ISP_SETREG8(((reg) + 3), ((value) >> 0) & 0xff);  \
	} while (0)


#define MMU_SETREG32(reg,val) \
	do {\
		*(volatile unsigned int*)(hw_isp_base+(reg)) = (val);\
	}while(0)

#define MMU_GETREG32(reg,val) \
	do {\
		(val) = *(volatile unsigned int*)(hw_isp_base+(reg)); \
	}while(0)


#define get_writeback_expo(flow) \
	(ISP_GETREG8(REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)) ? \
	ISP_GETREG32(REG_FW_AECAGC_MANUAL_EXPO(flow)) : ISP_GETREG32(REG_FW_WRITEBACK_EXPO(flow)))

#define get_writeback_gain(flow) \
	(ISP_GETREG8(REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)) ? \
	ISP_GETREG16(REG_FW_AECAGC_MANUAL_GAIN(flow)) : ISP_GETREG16(REG_FW_WRITEBACK_GAIN(flow)))

extern unsigned int HW_CSI_GETREG32(unsigned int reg);
extern void HW_CSI_SETREG32(unsigned int reg, unsigned int val);
extern void hw_io_set_isp_base(unsigned char *isp_base_addr);

#endif