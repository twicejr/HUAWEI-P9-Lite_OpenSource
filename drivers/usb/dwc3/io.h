/**
 * io.h - DesignWare USB3 DRD IO Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __DRIVERS_USB_DWC3_IO_H
#define __DRIVERS_USB_DWC3_IO_H

#include <linux/io.h>

#include "core.h"

static inline u32 dwc3_readl(void __iomem *base, u32 offset)
{
#ifdef CONFIG_USB_DWC3_HISI
	extern atomic_t hisi_dwc3_power_on;
	if (unlikely(0 == atomic_read(&hisi_dwc3_power_on))) {
		return 0;
	}
#endif
	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	return readl(base + (offset - DWC3_GLOBALS_REGS_START));
}

static inline void dwc3_writel(void __iomem *base, u32 offset, u32 value)
{
#ifdef CONFIG_USB_DWC3_HISI
	extern atomic_t hisi_dwc3_power_on;
	if (unlikely(0 == atomic_read(&hisi_dwc3_power_on))) {
		return;
	}
#endif
	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	writel(value, base + (offset - DWC3_GLOBALS_REGS_START));
}

#endif /* __DRIVERS_USB_DWC3_IO_H */
