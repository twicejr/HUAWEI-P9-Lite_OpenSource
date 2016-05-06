/*
 * hi3630_fake_fm.c -- ALSA SoC HI3630 FACK FM driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_FAKE_FM"

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <sound/soc.h>

#include "hi3630_log.h"

static const struct of_device_id hi3630_fake_fm_match[] = {
	{ .compatible = "hisilicon,hi3630-fake-fm", },
	{},
};
MODULE_DEVICE_TABLE(of, hi3630_fake_fm_match);

static int hi3630_fake_fm_new(struct snd_soc_pcm_runtime *rtd)
{
	/* do nothing */
	return 0;
}

static void hi3630_fake_fm_free(struct snd_pcm *pcm)
{
	/* do nothing */
}

static struct snd_soc_platform_driver hi3630_fm_platform = {
	.pcm_new	= hi3630_fake_fm_new,
	.pcm_free	= hi3630_fake_fm_free,
};

static int hi3630_fake_fm_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	dev_set_name(dev, "hi3630-fm");

	ret = snd_soc_register_platform(dev, &hi3630_fm_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n", ret);
		return -ENODEV;
	}

	return ret;
}

static int hi3630_fake_fm_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
	return 0;
}

static struct platform_driver hi3630_fake_fm_driver = {
	.probe	= hi3630_fake_fm_probe,
	.remove	= hi3630_fake_fm_remove,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi3630-fm",
		.of_match_table = of_match_ptr(hi3630_fake_fm_match),
	},
};

module_platform_driver(hi3630_fake_fm_driver);

MODULE_DESCRIPTION("ASoC hi3630 fake fm driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
