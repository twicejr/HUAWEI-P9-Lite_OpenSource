/*
 * hi64xx_vad.h -- hi64xx vad driver
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HI64XX_VAD_H
#define _HI64XX_VAD_H

#include <sound/soc.h>
#include <linux/hisi/hi64xx/hi64xx_irq.h>

extern int hi64xx_vad_init(struct snd_soc_codec *codec, struct hi64xx_irq *irq);
extern int hi64xx_vad_deinit(void);

#endif
