/* arch/arm/mach-k3v2/include/mach/early-debug.h
*
* Copyright (c) 2006 Hisilicon Co., Ltd.
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
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*
*/
#ifndef __MACH_K3V2_EARLY_DEBUG_H
#define __MACH_K3V2_EARLY_DEBUG_H

#include <asm/io.h>
#include <mach/hardware.h>
#include <mach/platform.h>

#if defined CONFIG_MACH_HI6620SFT ||defined CONFIG_MACH_HI6210SFT
#define REG_EDB_UART	REG_BASE_UART0
#else
#define REG_EDB_UART	REG_BASE_UART4
#endif

#if (CONFIG_K3_EDB_LEVEL == 255)

#define edb_reinit()
#define edb_init()
#define edb_cleanup()
#define edb_putc(x)
#define edb_putul(x)
#define edb_putstr(x)
#define edb_puthex(x)
#define edb_trace(x)
#define edb_put_strul(x, y)
#define hisik3_trace(level, s, param...)

#else /* (CONFIG_K3_EDB_LEVEL<255) */

#define edb_init()						\
	do {							\
		edb_putstr("Kernel Early-Debug on Level ");	\
		edb_putul(CONFIG_K3_EDB_LEVEL);			\
		edb_putstr("\n");				\
	} while (0)

#define edb_cleanup()

#define AMBA_UART_DR	IO_ADDRESS(REG_EDB_UART + 0x000)
#define AMBA_UART_LCRH	IO_ADDRESS(REG_EDB_UART + 0x02C)
#define AMBA_UART_CR	IO_ADDRESS(REG_EDB_UART + 0x030)
#define AMBA_UART_FR	IO_ADDRESS(REG_EDB_UART + 0x018)

static inline void edb_reinit(void)
{
	unsigned int usctrl_base = IO_ADDRESS(REG_BASE_SC_OFF);
	unsigned int uuart_base  = IO_ADDRESS(REG_EDB_UART);
	unsigned int io_base = IO_ADDRESS(REG_BASE_IOC_OFF);
	unsigned int uregv = 0;

	/* Config necessary IOMG configuration */
	writel(0, (io_base+0xF4));

	/* config necessary IOCG configuration */
	writel(0, (io_base+0xA08));
	writel(0, (io_base+0xA0C));

	/*disable clk*/
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x44));

	/*select 26MHz clock*/
	uregv = (1<<23);
	writel(uregv, (usctrl_base + 0x100));

	/*@ enable clk*/
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x40));

	/*@;禁止收发功能*/
	uregv = 0x0;
	writel(uregv, (uuart_base + 0x30));

	/*@;使能FIFO功能*/
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2c));

	/*@;设置波特率*/
	uregv = 0xE;
	writel(uregv, (uuart_base + 0x24));

	uregv = 0x7;
	writel(uregv, (uuart_base + 0x28));

	/*@;清空缓冲区*/
	uregv = readl(uuart_base);

	/*@;使能FIFO功能*/
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2C));

	/*@;设置FIFO大小*/
	uregv = 0x10A;
	writel(uregv, (uuart_base + 0x34));

	uregv = 0x50;
	writel(uregv, (uuart_base + 0x38));

	/*@;使能收发功能*/
	uregv = 0xF01;
	writel(uregv, (uuart_base + 0x30));
}

static inline void edb_putc(char c)
{
	while ((1 << 5) & readl(AMBA_UART_FR))
		barrier();

	writel(c, AMBA_UART_DR);
	/*AMBA_UART_DR = c;*/

	while ((1 << 3) & readl(AMBA_UART_FR))
		barrier();
}

static void __edb_putul(unsigned long num)
{
	if (num == 0)
		return;
	return;
}

static inline void edb_putul(unsigned long num)
{
	if (num == 0) {
		edb_putc('0');
		return;
	}
	__edb_putul(num);
}

static inline void edb_putstr(const char *s)
{
	while (*s) {
		while ((1 << 5) & readl(AMBA_UART_FR))
			barrier();

		/* AMBA_UART_DR = *s; */
		writel(*s, AMBA_UART_DR);

		if (*s == '\n') {
			while ((1 << 5) & readl(AMBA_UART_FR))
				barrier();

			writel('\r', AMBA_UART_DR);
		}
		s++;
	}

	while ((1 << 3) & readl(AMBA_UART_FR))
		barrier();
}

static inline void edb_puthex(unsigned long h)
{
	int i;
	char c;

	edb_putstr("0x");

	for (i = 0; i < 8; i++) {
		c = (h >> 28) & 0x0F;

		if (c >= 10)
			c = (c - 10) + 'A';
		else
			c = c + '0';

		edb_putc(c);

		h = h << 4;
	}
}

#define EDB_TRACE_LEVEL CONFIG_K3_EDB_LEVEL

#define edb_trace(level)				\
	do {						\
		if (level >= EDB_TRACE_LEVEL) {		\
			edb_putstr(__func__);	\
			edb_putstr("\t");		\
			edb_putul(__LINE__);		\
			edb_putstr("\t[");		\
			edb_putstr(__FILE__);		\
			edb_putstr("]\n");		\
		}					\
	} while (0)

#define edb_put_strul(s, ul)	\
	do {			\
		edb_putstr(s);	\
		edb_putul(ul);	\
	} while (0)

#define hisik3_trace(level, s, param...)			\
	do {							\
		if (level >= EDB_TRACE_LEVEL) {			\
			printk(KERN_INFO "[%s, %d]\t" s		\
				"\n", __func__, __LINE__, param);	\
		}						\
	} while (0)

#endif /* (CONFIG_K3_EDB_LEVEL == 255) */
#endif /* __ASM_ARCH_K3_EARLY_DEBUG_H */
