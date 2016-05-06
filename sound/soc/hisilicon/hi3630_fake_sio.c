/*
 * hi3630_fake_sio.c -- ALSA SoC HI3630 FAKE SIO DAI driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_FAKE_SIO"

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <sound/soc.h>

#include "hi3630_log.h"

#define HISI_SIO_RATES (SNDRV_PCM_RATE_8000_96000)

#if 0
static const struct snd_soc_dai_ops sio_dai_ops = {
	.startup	= sio_dai_startup,
	.shutdown	= sio_dai_shutdown,
	.hw_params	= sio_dai_hw_params,
	.hw_free	= sio_dai_hw_free,
};
#endif
static int hi3630_fake_sio_probe(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static int hi3630_fake_sio_remove(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static const struct snd_soc_component_driver hi3630_fake_sio_component = {
	.name		= "hi3630-fake-sio",
};

static struct snd_soc_dai_driver hi3630_fake_sio_dai = {
	.probe = hi3630_fake_sio_probe,
	.remove = hi3630_fake_sio_remove,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_SIO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE,
	},
};

static const struct of_device_id hi3630_fake_sio_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-fake-sio",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_fake_sio_of_match);

static int sio_fm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	dev_set_name(dev, "sio-fm");
	
	ret = snd_soc_register_component(dev, &hi3630_fake_sio_component,
					  &hi3630_fake_sio_dai, 1);

pr_err("---------------cg-------------%s:ret = %d", __FUNCTION__, ret);

	return ret;
}

static int sio_fm_remove(struct platform_device *pdev)
{
	snd_soc_unregister_component(&pdev->dev);
	return 0;
}

static struct platform_driver hi3630_fake_sio_driver = {
	.driver = {
		.name	= "hi3630-sio-fm",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_fake_sio_of_match,
	},
	.probe	= sio_fm_probe,
	.remove	= sio_fm_remove,
};
module_platform_driver(hi3630_fake_sio_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 FAKE SIO Interface");
MODULE_LICENSE("GPL");
