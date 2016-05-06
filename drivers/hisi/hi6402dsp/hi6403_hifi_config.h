/*
 * hi6403_hifi_config.h -- adapt 64xx hifi misc to 6403
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI6403_HIFI_CONFIG_H
#define _HI6403_HIFI_CONFIG_H

#include <linux/hisi/hi64xx/hi64xx_irq.h>
#include <linux/hisi/hi64xx/hi64xx_resmgr.h>
#include <linux/hisi/hi64xx/hi64xx_mbhc.h>

int hi6403_hifi_config_init(struct snd_soc_codec *codec,
				struct hi64xx_resmgr *resmgr,
				struct hi64xx_irq *irqmgr);
void hi6403_hifi_config_deinit(void);

#endif
