/*
 *
 * arch/arm/mach-k3v2/include/mach/smp.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#ifndef __MACH_K3V2_SMP_H
#define __MACH_K3V2_SMP_H

#include <asm/hardware/gic.h>

#define hard_smp_processor_id()			\
	({						\
		unsigned int cpunum;			\
		__asm__("mrc p15, 0, %0, c0, c0, 5"	\
			: "=r" (cpunum));		\
		cpunum &= 0x0F;				\
	})

/*
 * We use IRQ1 as the IPI
 */
static inline void smp_cross_call(const struct cpumask *mask, int ipi)
{
	gic_raise_softirq(mask, ipi);
}

#endif
