/*
 *
 * arch/arm/mach-k3v3/hisi_pm_setup.S
 *
 * Copyright (C) 2013 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */

#include <linux/linkage.h>
#include <asm/mcpm.h>

#define A7_CCI_PHYS_BASE	0xe8294000
#define A15_CCI_PHYS_BASE	0xe8295000
#define CCI_PHYS_STATUS		0xe8290000

#define SNOOPCTL_ENABLE		0x00000003

#define CCI_STATUS_OFFSET	0xc
#define STATUS_CHANGE_PENDING	(1 << 0)

/*
 * Enable cluster-level coherency, in preparation for turning on the MMU.
 * The ACTLR SMP bit does not need to be set here, because cpu_resume()
 * already restores that.
 */

ENTRY(hisi_pm_power_up_setup)
	cmp	r0, #0
	beq	exit
	b       cci_enable_port_for_self
exit:
	bx	lr
ENDPROC(hisi_pm_power_up_setup)
