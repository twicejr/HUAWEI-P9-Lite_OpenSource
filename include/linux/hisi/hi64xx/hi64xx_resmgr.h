/*
 * hi64xx_resmgr.h -- resource manager for hi64xx codec
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI64XX_RESMGR_H
#define _HI64XX_RESMGR_H

#include <sound/soc.h>
#include <linux/notifier.h>
#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>
#include <linux/hisi/hi64xx/hi64xx_irq.h>


enum hi64xx_pll_type {
	PLL_LOW,
	PLL_HIGH,
	PLL_44_1,
	PLL_MAX,
	PLL_NONE = -1,
};

/* Codec driver should implement these functions for each of its PLL or PLL state */
struct pll_ctrl_func {
	/*  function to turn on this PLL or PLL state */
	int (*turn_on)(struct snd_soc_codec *);
	/*  function to turn off this PLL or PLL state */
	int (*turn_off)(struct snd_soc_codec *);
	/*  return ture if pll is locked */
	bool (*is_locked)(struct snd_soc_codec *);
};


struct resmgr_config {
	/* number of the PLL or PLL state the codec has */
	int pll_num;
	/* functions to control each PLL or PLL state */
	struct pll_ctrl_func pfn_pll_ctrls[PLL_MAX];

	/* function to get the PLL required for accessing the specified register */
	enum hi64xx_pll_type (*pll_for_reg_access)(struct snd_soc_codec *, unsigned int);

	/* functions to enable/disable micbias */
	int (*enable_micbias)(struct snd_soc_codec *);
	int (*disable_micbias)(struct snd_soc_codec *);

	/* functions to enable/disable ibias */
	int (*enable_ibias)(struct snd_soc_codec *);
	int (*disable_ibias)(struct snd_soc_codec *);
};


struct hi64xx_resmgr {
	/* define datas that should be public */
};


int hi64xx_resmgr_init(struct snd_soc_codec *codec,
                       struct hi_cdc_ctrl *cdc_ctrl,
                       struct hi64xx_irq *irqmgr,
                       const struct resmgr_config *config,
                       struct hi64xx_resmgr **resmgr);

void hi64xx_resmgr_deinit(struct hi64xx_resmgr *resmgr);

int hi64xx_resmgr_request_reg_access(struct hi64xx_resmgr *resmgr,
                                     unsigned int reg_addr);

int hi64xx_resmgr_release_reg_access(struct hi64xx_resmgr *resmgr,
                                     unsigned int reg_addr);

int hi64xx_resmgr_request_pll(struct hi64xx_resmgr *resmgr,
                              enum hi64xx_pll_type pll_type);

int hi64xx_resmgr_release_pll(struct hi64xx_resmgr *resmgr,
                              enum hi64xx_pll_type pll_type);

int hi64xx_resmgr_request_micbias(struct hi64xx_resmgr *resmgr);

int hi64xx_resmgr_release_micbias(struct hi64xx_resmgr *resmgr);

int hi64xx_resmgr_force_release_micbias(struct hi64xx_resmgr *resmgr);

void hi64xx_resmgr_dump(struct hi64xx_resmgr *resmgr);


/* definations of notification events */

struct pll_switch_event {
	enum hi64xx_pll_type from;
	enum hi64xx_pll_type to;
};

enum hi64xx_resmgr_event {
	PRE_PLL_SWITCH,  /* event payload is struct pll_switch_event */
	POST_PLL_SWITCH  /* event payload is struct pll_switch_event */
};

int hi64xx_resmgr_register_notifier(struct hi64xx_resmgr *resmgr,
                                    struct notifier_block *nblock);

int hi64xx_resmgr_unregister_notifier(struct hi64xx_resmgr *resmgr,
                                    struct notifier_block *nblock);


#endif