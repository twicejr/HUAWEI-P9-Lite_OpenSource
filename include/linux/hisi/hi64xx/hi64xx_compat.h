/*
 * hi64xx_compat.h -- hisilicon codec controller
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI64XX_COMPAT_H
#define _HI64XX_COMPAT_H

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>

struct hi64xx_irq;

extern unsigned int hi64xx_compat_reg_read(unsigned int reg_addr);
extern int hi64xx_compat_reg_write(unsigned int reg_addr, unsigned int reg_val);
extern int hi64xx_compat_request_irq(int phy_irq_id, irq_handler_t handler, const char *name, void *priv_data);
extern int hi64xx_compat_init(struct hi_cdc_ctrl *hi_cdc, struct hi64xx_irq *irq);
extern void hi64xx_compat_deinit(void);

#endif
