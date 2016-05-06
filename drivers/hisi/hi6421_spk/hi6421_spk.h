/*
 * hi6421_spk.h -- hi6421 speaker driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef HISI_6421_SPK_H
#define HISI_6421_SPK_H

#include <linux/regulator/consumer.h>
#include <linux/miscdevice.h>

#define HI6421_SPK_IOCTL_MAGIC 'u'

#define HI6421_SPK_ENABLE	_IOW(HI6421_SPK_IOCTL_MAGIC, 0xC0, unsigned)
#define HI6421_SPK_DISABLE	_IOW(HI6421_SPK_IOCTL_MAGIC, 0xC1, unsigned)

#define HI6421_SPK_CRTL_1	(0xBF << 2)
#define HI6421_SPK_CRTL_3	(0xC1 << 2)

struct hi6421_spk_platform_data {
	struct regulator_bulk_data	regu_ldo8;
	struct regulator_bulk_data	regu_boost5v;
	struct miscdevice	miscdev;
	struct resource	*res;
	struct mutex	io_mutex;
	void		__iomem *reg_base_addr;
	bool		classd_enable;
};

#endif //HI6421_SPK_H