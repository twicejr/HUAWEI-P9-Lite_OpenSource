/*
 * linux/drivers/mmc/host/k3v3_mmc_raw.h
 *
 * Raw k3v3 mmc controller driver
 *
 * Copyright (C) 2011 Hisilicon
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */

#include <linux/mmc/core.h>

#ifndef DRIVERS_MMC_HOST_K3V3_MMC_RAW_H
#define DRIVERS_MMC_HOST_K3V3_MMC_RAW_H

extern int raw_mmc_panic_probe(struct raw_hd_struct *rhd, int type);
extern int raw_mmc_panic_write(struct raw_hd_struct *rhd, char *buf, unsigned int offset, unsigned int len);
extern int raw_mmc_panic_erase(struct raw_hd_struct *rhd, unsigned int offset, unsigned int len);
extern int raw_mmc_read_async_done(void);

#endif
