/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"


struct spi_device *g_spi_dev = NULL;

static int hisi_spi_probe (struct spi_device *spi_dev)
{
	int ret = 0;
	struct device_node *np = NULL;
	uint32_t fpga_flag = 0;

	np = of_find_compatible_node(NULL, NULL, DEV_NAME_SPI);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DEV_NAME_SPI);
		return -ENXIO;
	}

	ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
	if (ret) {
		HISI_FB_ERR("failed to get fpga_flag resource.\n");
		return -ENXIO;
	}

	if (fpga_flag != 1) {
		return 0;
	}

	HISI_FB_DEBUG("+.\n");

	g_spi_dev = spi_dev;

	spi_dev->bits_per_word = 8;
	spi_dev->mode = SPI_MODE_3;
	ret = spi_setup(spi_dev);
	if (ret < 0) {
		HISI_FB_ERR(" ret = %d, spi_setup fail.\n", ret);
		return -ENXIO;
	}

	hisi_fb_device_set_status0(DTS_SPI_READY);

	HISI_FB_DEBUG("-.\n");

	return 0;
}

static int hisi_spi_remove(struct spi_device *spi_dev)
{
	HISI_FB_DEBUG("+.\n");
	/*spi_unregister_driver(&spi_driver);*/
	HISI_FB_DEBUG("-.\n");

	return 0;
}

static const struct of_device_id hisi_spi_match_table[] = {
	{
		.compatible = DEV_NAME_SPI,
		.data = NULL,
	},
	{},
};

static struct spi_driver this_driver = {
	.probe = hisi_spi_probe,
	.remove = hisi_spi_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_SPI,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_spi_match_table),
	},
};

static int __init hisi_spi_init(void)
{
	int ret = 0;

	ret = spi_register_driver(&this_driver);
	if (ret) {
		HISI_FB_ERR("spi_register_driver failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(hisi_spi_init);
