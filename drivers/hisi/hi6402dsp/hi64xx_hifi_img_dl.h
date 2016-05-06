/*
 * hi64xx_hifi_img_dl.h -- 64xx hifi img download
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI64XX_HIFI_IMG_DL_H
#define _HI64XX_HIFI_IMG_DL_H

#include <linux/firmware.h>
#include <linux/hisi/hi64xx_hifi_misc.h>

struct hi64xx_hifi_img_dl_config {
	uint32_t dspif_clk_en_addr;
};

int hi64xx_release_all_dma(void);
void hi64xx_hifi_download(const struct firmware *fw);
void hi64xx_hifi_download_slimbus(const struct firmware *fw);
int hi64xx_hifi_img_dl_init(struct hi64xx_irq *irqmgr,
			struct hi64xx_hifi_img_dl_config *dl_config);
void hi64xx_hifi_img_dl_deinit(void);

#endif


