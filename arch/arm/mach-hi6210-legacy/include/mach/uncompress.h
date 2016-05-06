/*
 *  arch/arm/mach-k3v2/include/mach/uncompress.h
 *
 *  Copyright (C) 2011 Hisilicon Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __MACH_K3V2_UNCOMPRESS_H
#define __MACH_K3V2_UNCOMPRESS_H

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <mach/platform.h>

#if defined CONFIG_MACH_HI6620SFT ||defined CONFIG_MACH_HI6210SFT
#define REG_EDB_UART    REG_BASE_UART0
#endif

#ifdef CONFIG_MACH_HI6620OEM
#define REG_EDB_UART    REG_BASE_UART0
#endif

#define AMBA_UART_DR	(*(volatile unsigned int *)(REG_EDB_UART + 0x000))
#define AMBA_UART_LCRH	(*(volatile unsigned int *)(REG_EDB_UART + 0x02C))
#define AMBA_UART_CR	(*(volatile unsigned int *)(REG_EDB_UART + 0x030))
#define AMBA_UART_FR	(*(volatile unsigned int *)(REG_EDB_UART + 0x018))

/*
 * This does not append a newline
 */

static inline void putc(int c)
{
    /*解压代码中根据系统保留寄存器中的标志，来决定是否做UART0的打印*/
	if (*(volatile int *)(SOC_AO_SCTRL_BASE_ADDR + 0x13A0) != 'A') {
		return;
	}
	
	while (AMBA_UART_FR & (1 << 5))
		barrier();

	AMBA_UART_DR = c;
}

static inline void flush(void)
{
	while (AMBA_UART_FR & (1 << 3))
		barrier();
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()

#endif
