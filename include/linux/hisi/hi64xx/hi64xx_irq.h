/*
 * hisi_64xx_irq.h  --  Interrupt controller support for Hisilicon HI64XX
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef	__HI64XX_IRQ_H__
#define	__HI64XX_IRQ_H__

#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <sound/soc.h>
#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>



enum hi64xx_irq_type {
	IRQ_BTNUP_COMP1 = 0,
	IRQ_BTNDOWN_COMP1 = 1,
	IRQ_BTNDOWN_COMP2 = 2,
	IRQ_BTNUP_COMP2 = 3,
	IRQ_BTNUP_ECO = 4,
	IRQ_BTNDOWN_ECO = 5,
	IRQ_PLUGIN = 6,
	IRQ_PLUGOUT = 7,
	IRQ_VAD = 12,
	IRQ_WTD = 13,
	IRQ_CMD_VALID = 16,
	IRQ_PLL_UNLOCK = 20,
	IRQ_MAX,
};


/* max number of hi64xx irqs */
#define HI64XX_MAX_IRQS_NUM 64
/* number of bits in irq register */
#define HI64XX_IRQ_REG_BITS_NUM 8
/* max number of hi64xx irq regsiters */
#define HI64XX_MAX_IRQ_REGS_NUM (HI64XX_MAX_IRQS_NUM / HI64XX_IRQ_REG_BITS_NUM)

struct hi64xx_irq_map {
	/* irq registers in codec */
	unsigned int irq_regs[HI64XX_MAX_IRQ_REGS_NUM];
	/* irq mask register in codec */
	unsigned int irq_mask_regs[HI64XX_MAX_IRQ_REGS_NUM];
	/* irq numbers */
	int irq_num;
};

struct hi64xx_irq {
	/* device of hi64xx_irq */
	struct device *dev;
};

/* initialize hi64xx-irq */
extern int hi64xx_irq_init_irq(struct hi64xx_irq *irq_data, struct hi64xx_irq_map *irq_map);

extern void hi64xx_irq_deinit_irq(struct hi64xx_irq *hi64xx_data);

/* request irq */
extern int hi64xx_irq_request_irq(struct hi64xx_irq *irq_data, int phy_irq,
				irq_handler_t handler, const char *name, void *priv);

extern void hi64xx_irq_free_irq(struct hi64xx_irq *irq_data, int phy_irq, void *priv);

extern int hi64xx_irq_enable_irq(struct hi64xx_irq *irq_data, int phy_irq);

extern int hi64xx_irq_disable_irq(struct hi64xx_irq *irq_data, int phy_irq);

extern int hi64xx_irq_enable_irqs(struct hi64xx_irq *irq_data, int irq_num, int* phy_irqs);

extern int hi64xx_irq_disable_irqs(struct hi64xx_irq *irq_data, int irq_num, int* phy_irqs);

extern void hi64xx_irq_resume_wait(struct hi64xx_irq *irq_data);

#endif /* __HI64XX_IRQ_H__ */
