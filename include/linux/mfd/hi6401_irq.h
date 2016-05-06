/*
 * hi6401_irq.h  --  Interrupt controller support for Hisilicon HI6401
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef	__HI6401_IRQ_H__
#define	__HI6401_IRQ_H__

#include <linux/irqdomain.h>
#include <linux/clk.h>

#define HI6401_NR_IRQ			8
#define HI6401_MASK_FIELD		0xFF
#define HI6401_BITS			8
#define HI6401_MAX_IRQS			8

/* irq & irq mask reg */
#define HI6401_BASE_ADDR_PAGE_0		0x0000
#define HI6401_BASE_ADDR_PAGE_1		0x1000
#define HI6401_PAGE_OFFSET_MASK		0x0FFF

#define HI6401_PAGE_SELECT_REG		0x01FF

struct hi6401_irq {
	struct resource		*res;
	struct irq_domain	*domain;
	void __iomem		*reg_base_addr;
	struct clk		*codec_ssi_clk;
	struct clk		*pmu_audio_clk;
	struct pinctrl		*pctrl;
	spinlock_t		rw_lock;
	spinlock_t		lock;
	int			irq;
	unsigned int		irqs[HI6401_MAX_IRQS];
	int			gpio;
	struct device *dev;
	struct workqueue_struct *hi6401_irq_delay_wq;
	struct delayed_work hi6401_irq_delay_work;
	struct wake_lock wake_lock;
	struct mutex sr_mutex;

	struct mutex pll_mutex;
	bool pll_check_enable;
	struct workqueue_struct * pll_delay_wq;
	struct delayed_work pll_delay_work;
};

/* Register Access Helpers */
u32 hi6401_irq_read(struct hi6401_irq *irq, int reg);
void hi6401_irq_write(struct hi6401_irq *irq, int reg, u32 val);
void hi6401_pll_check_enable(struct hi6401_irq *irq, bool enable);
#endif		/* __HI6401_IRQ_H__ */
