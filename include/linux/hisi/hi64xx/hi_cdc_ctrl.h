/*
 * hi_cdc_ctrl.h -- hisilicon codec controller
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI_CDC_CTRL_H
#define _HI_CDC_CTRL_H

#include <linux/kernel.h>

enum hi_cdcctrl_supply {
	CDC_SUP_MAIN,
	CDC_SUP_ANLG,
	CDC_SUP_MAX
};

enum hi_cdcctrl_clk {
	CDC_MCLK,
	CDC_CLK_MAX
};

enum bustype_select {
	BUSTYPE_SELECT_NULL = 0,
	BUSTYPE_SELECT_SLIMBUS = 1,
	BUSTYPE_SELECT_SSI = 2,
};

struct hi_cdc_ctrl {
	/* device of codec controller */
	struct device *dev;
	enum bustype_select bus_sel;
};

void hi_cdcctrl_dump(struct hi_cdc_ctrl *cdc_ctrl);

unsigned int hi_cdcctrl_reg_read(struct hi_cdc_ctrl *cdc_ctrl,
                                 unsigned int reg_addr);

int hi_cdcctrl_reg_write(struct hi_cdc_ctrl *cdc_ctrl,
                         unsigned int reg_addr, unsigned int reg_val);

void hi_cdcctrl_reg_update_bits(struct hi_cdc_ctrl *cdc_ctrl, unsigned int reg,
                                unsigned int mask, unsigned int value);

int hi_cdcctrl_hw_reset(struct hi_cdc_ctrl *cdc_ctrl);

/* return the irq number of the codec */
int hi_cdcctrl_get_irq(struct hi_cdc_ctrl *cdc_ctrl);

int hi_cdcctrl_enable_supply(struct hi_cdc_ctrl *cdc_ctrl,
                             enum hi_cdcctrl_supply sup_type, bool enable);

int hi_cdcctrl_enable_clk(struct hi_cdc_ctrl *cdc_ctrl,
                          enum hi_cdcctrl_clk clk_type, bool enable);


#endif
