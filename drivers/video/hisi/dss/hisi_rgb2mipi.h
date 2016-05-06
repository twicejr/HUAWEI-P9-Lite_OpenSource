/*
**Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
**
**This program is free software; you can redistribute it and/or modify
**it under the terms of the GNU General Public License version 2 and
**only version 2 as published by the Free Software Foundation.
**
**This program is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
**GNU General Public License for more details.
**
*/

#ifndef HISI_RGB2MIPI_H
#define HISI_RGB2MIPI_H

#include "hisi_mipi_dsi.h"


struct rgb2mipi_spi_cmd_desc {
	uint16_t reg;
	uint8_t value;
	int delay;
	int delaytype;
};

struct dsi_cmd_desc;


int rgb2mipi_cmds_tx(struct spi_device *spi_dev, struct dsi_cmd_desc *cmds, int cnt);


#endif /* HISI_RGB2MIPI_H */
