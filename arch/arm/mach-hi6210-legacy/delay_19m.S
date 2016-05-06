/*
 *  linux/arch/arm/lib/delay.S

 *
 *  Copyright (C) 1995, 1996 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <asm/assembler.h>
#include <mach/io.h>
#include <asm/sizes.h>

#include <mach/platform.h>
#include <mach/hardware.h>
#include <asm/hardware/arm_timer.h>
#include <mach/fixmap.h>

/* loads a 32-bit value into a register without a data access */
	.text

ENTRY(__udelay)
ENTRY(__const_udelay)
	stmfd	sp!, {r1-r3}

	ldr 	r3, =(REG_BASE_TIMER0_VIRT+0x24)
	ldr 	r1, [r3]

	/* Timer1 Clock is 19.2MHz, so r0 must mul 20 */
	mov	    r2, r0, lsl #2     /* 4*x */
	add	    r0, r2, r2, lsl #2 /* 4*x + 4*x << 2 = 20*x*/
	/* r0 - usecs to wait
	 * r1 - initial value of the counter
	 */

loop:
	ldr 	r2, [r3]
	rsb 	r2, r2, r1
	cmp 	r2, r0
	bls 	loop

	ldmfd	sp!, {r1-r3}
	mov 	pc, lr

ENDPROC(__const_udelay)
ENDPROC(__udelay)


@ Delay routine
ENTRY(__delay)
	/*mov r0, r0, ror #3*/
	subs  	r0, r0, #1
	bhi 	__delay
	mov 	pc, lr
ENDPROC(__delay)

