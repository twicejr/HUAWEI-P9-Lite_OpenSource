/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _SLIMBUS_UTILS_H_
#define _SLIMBUS_UTILS_H_
#include "slimbus_types.h"

#define IOC_BASE_ADDR		(0xfff11000)
#define IOC_REG_SIZE		(0x1000)

#define IOC_SYS_IOMG_011	(0x02c)
#define IOC_SYS_IOMG_012	(0x030)
#define IOC_SYS_IOCG_013	(0x834)
#define IOC_SYS_IOCG_014	(0x838)
#define HI6402_SLIMBUS_PORT_NUM (16)
#define SLIMBUS_PORT_BASE_ADDR	(0x100)
#define SLIMBUS_PORT_OFFSET 	(0x8)

#define SLIMBUS_PORT_ACTIVE 	(0x1)
void slimbus_freq_request(void __iomem *asp_reg_base_addr);
void slimbus_freq_release(void __iomem *asp_reg_base_addr);
uint32_t slimbus_port_state_get(void __iomem *asp_reg_base_addr);
uint32_t slimbus_asppower_state_get(void __iomem *asppower_base_addr, uint32_t offset);
void slimbus_module_enable(slimbus_device_info_t *dev, void __iomem *asp_reg_base_addr, bool enable);

#endif
