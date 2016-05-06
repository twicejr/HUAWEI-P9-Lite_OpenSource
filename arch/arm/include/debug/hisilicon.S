/*
 * Early serial output macro for Hisilicon SoC
 *
 * Copyright (C) 2012-2013 Linaro Ltd.
 *
 * Haojian Zhuang <haojian.zhuang@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define HI3620_UART0_PHYS_BASE	0xfcb00000
#define HI3620_UART0_VIRT_BASE	0xfeb00000

#define HI3716_UART0_PHYS_BASE	0xf8b00000
#define HI3716_UART0_VIRT_BASE	0xfeb00000

#define HI3630_UART0_PHYS_BASE	0xfdf02000
#define HI3630_UART0_VIRT_BASE	0xfeb02000

#define HI3630_UART6_PHYS_BASE	0xfff32000
#define HI3630_UART6_VIRT_BASE	0xfdf32000

#define HI6620_UART0_PHYS_BASE	0xf7110000
#define HI6620_UART0_VIRT_BASE	0xf7d10000

#define HI6210_UART0_PHYS_BASE	0xf8015000
#define HI6210_UART0_VIRT_BASE	0xf8c15000

#if defined(CONFIG_SERIAL_AMBA_PL010) || defined(CONFIG_SERIAL_AMBA_PL011)
#include <asm/hardware/debug-pl01x.S>

#if defined(CONFIG_DEBUG_HI3620_UART0)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI3620_UART0_PHYS_BASE
		ldr	\rv, =HI3620_UART0_VIRT_BASE
		.endm

#elif defined(CONFIG_DEBUG_HI3630_UART0)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI3630_UART0_PHYS_BASE
		ldr	\rv, =HI3630_UART0_VIRT_BASE
		.endm

#elif defined(CONFIG_DEBUG_HI3630_UART6)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI3630_UART6_PHYS_BASE
		ldr	\rv, =HI3630_UART6_VIRT_BASE
		.endm

#elif defined(CONFIG_DEBUG_HI3716_UART0)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI3716_UART0_PHYS_BASE
		ldr	\rv, =HI3716_UART0_VIRT_BASE
		.endm

#elif defined(CONFIG_DEBUG_HI6620_UART0)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI6620_UART0_PHYS_BASE
		ldr	\rv, =HI6620_UART0_VIRT_BASE
		.endm

#elif defined(CONFIG_DEBUG_HI6210_UART0)
		.macro	addruart,rp,rv,tmp
		ldr	\rp, =HI6210_UART0_PHYS_BASE
		ldr	\rv, =HI6210_UART0_VIRT_BASE
		.endm

#endif

#endif
