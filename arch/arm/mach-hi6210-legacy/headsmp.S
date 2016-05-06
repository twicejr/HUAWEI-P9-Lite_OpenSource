/*
 * arch/arm/mach-k3v2/headsmp.S
 *
 *  Copyright (c) 2011 Hisilicon co.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <linux/init.h>
#include "pwrctrl_multi_memcfg.h"
        .section ".text.head", "ax"
	__CPUINIT

/*
 * K3v2 specific entry point for secondary CPUs.  This provides
 * a "holding pen" into which all secondary cores are held until we're
 * ready for them to initialise.
 */
ENTRY(k3v2_secondary_startup)
	mrc	p15, 0, r0, c0, c0, 5
	and	r0, r0, #15
	adr	r4, 1f
	ldmia	r4, {r5, r6}
	sub	r4, r4, r5
	add	r6, r6, r4
pen:	ldr	r7, [r6]
	cmp	r7, r0
	bne	pen

	/*
	 * we've been released from the holding pen: secondary_stack
	 * should now contain the SVC stack for this core
	 */
	ldr r9,=MEMORY_AXI_SEC_CORE_BOOT_TEST_ADDR
	ldr r7,[r9]
	cmp r7,#208
	beq loop
	b	secondary_startup
loop:
	b .
1:	.long	.
	.long	pen_release
