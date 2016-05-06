/*
 * hi3630_asp_irq.h  --  Interrupt controller support for Hisilicon HI3630 ASP
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef	__HI3630_ASP_IRQ_H__
#define	__HI3630_ASP_IRQ_H__

#include <linux/irqdomain.h>

#define HI3630_ASP_IRQ_NR_IRQ		4
#define HI3630_ASP_IRQ_MASK_FIELD	0xF
#define HI3630_ASP_IRQ_BITS		4
#define HI3630_ASP_IRQ_MAX_IRQS		4

struct hi3630_asp_irq {
	struct resource		*res;
	struct irq_domain	*domain;
	void __iomem		*reg_base_addr;
	spinlock_t		lock;
	int			irq;
	int			irqs[HI3630_ASP_IRQ_NR_IRQ];
};

#endif	/* __HI3630_ASP_IRQ_H__ */
