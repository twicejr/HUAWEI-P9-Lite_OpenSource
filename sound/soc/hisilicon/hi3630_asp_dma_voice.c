/*
 * hi3630_asp_dma_voice.c -- ALSA SoC HI3630 ASP DMA driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "hi3630_asp_dma_voice"

#include <linux/dma-mapping.h>
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
#include <linux/compiler.h>
#include <linux/regulator/consumer.h>
#include <sound/core.h>
#include <sound/dmaengine_pcm.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>

#include "hi3630_log.h"

extern void dmac_module_enable(bool enable);

struct hi3630_asp_dma_voice_data {
	struct regulator_bulk_data	regu;
};

enum hi3630_asp_dma_voice_status {
	STATUS_DMAC_STOP = 0,
	STATUS_DMAC_RUNNING,
};

struct dma_lli_cfg
{
	unsigned int lli;
	unsigned int reserved[3];
	unsigned int a_count;
	unsigned int src_addr;
	unsigned int des_addr;
	unsigned int config;
} __aligned(32);

struct hi3630_asp_dma_voice_runtime_data {
	struct hi3630_asp_dma_voice_data *pdata;
};

static const struct of_device_id hi3630_asp_dma_voice_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-pcm-asp-dma-voice",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_asp_dma_voice_of_match);


static const struct snd_pcm_hardware hi3630_asp_dma_voice_hardware = {
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.formats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S16_BE |
				  SNDRV_PCM_FMTBIT_S24_LE |
				  SNDRV_PCM_FMTBIT_S24_BE,
	.period_bytes_min	= 32,
	.period_bytes_max	= 16 * 1024,
	.periods_min		= 2,
	.periods_max		= 32,
	.buffer_bytes_max	= 128 * 1024,
};

static int hi3630_asp_dma_voice_open(struct snd_pcm_substream *substream)
{
	struct hi3630_asp_dma_voice_runtime_data *prtd = NULL;
	struct snd_soc_pcm_runtime *rtd = NULL;
	struct hi3630_asp_dma_voice_data *pdata = NULL;
	int ret = 0;

	prtd = kzalloc(sizeof(struct hi3630_asp_dma_voice_runtime_data), GFP_KERNEL);
	if (NULL == prtd) {
		loge("kzalloc hi3630_asp_dma_voice_runtime_data error!\n");
		return -ENOMEM;
	}

	rtd = (struct snd_soc_pcm_runtime *)substream->private_data;
	pdata = (struct hi3630_asp_dma_voice_data *)snd_soc_platform_get_drvdata(rtd->platform);

	BUG_ON(NULL == pdata);
	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret) {
		loge("couldn't enable regulators %d\n", ret);
		kfree(prtd);
		return -ENOENT;
	}

	prtd->pdata = pdata;

	substream->runtime->private_data = prtd;

	dmac_module_enable(true);

	snd_soc_set_runtime_hwparams(substream, &hi3630_asp_dma_voice_hardware);

	return 0;
}

static int hi3630_asp_dma_voice_close(struct snd_pcm_substream *substream)
{
	struct hi3630_asp_dma_voice_runtime_data *prtd = substream->runtime->private_data;

	if (NULL == prtd) {
		loge("prtd is NULL\n");
	} else {
		BUG_ON(NULL == prtd->pdata);
		dmac_module_enable(false);
		regulator_bulk_disable(1, &prtd->pdata->regu);
		kfree(prtd);
		substream->runtime->private_data = NULL;
	}

	return 0;
}

static struct snd_pcm_ops hi3630_asp_dma_voice_ops = {
	.open	    = hi3630_asp_dma_voice_open,
	.close	    = hi3630_asp_dma_voice_close,
	.ioctl      = snd_pcm_lib_ioctl,
};

static unsigned long long hi3630_pcm_dmamask = DMA_BIT_MASK(32);

static int hi3630_asp_dma_voice_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm  *pcm  = rtd->pcm;

	BUG_ON(NULL == card);
	BUG_ON(NULL == pcm);

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &hi3630_pcm_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = DMA_BIT_MASK(32);
	
	return 0;
}

static void hi3630_asp_dma_voice_free(struct snd_pcm *pcm)
{
}

static struct snd_soc_platform_driver hi3630_pcm_asp_dmac_platform = {
	.ops		= &hi3630_asp_dma_voice_ops,
	.pcm_new	= hi3630_asp_dma_voice_new,
	.pcm_free	= hi3630_asp_dma_voice_free,
};

static int hi3630_asp_dma_voice_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;
	struct hi3630_asp_dma_voice_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "cannot allocate hi3630 asp dma platform data\n");
		return -ENOMEM;
	}

	pdata->regu.supply = "asp-dmac";
	ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
	if (0 != ret) {
		dev_err(dev, "couldn't get regulators %d\n", ret);
		return -ENOENT;
	}

	platform_set_drvdata(pdev, pdata);

	dev_set_name(dev, "hi3630-pcm-asp-dma-voice");

	ret = snd_soc_register_platform(dev, &hi3630_pcm_asp_dmac_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n" ,ret);
		return -ENODEV;
	}

	return 0;
}

static int hi3630_asp_dma_voice_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
	return 0;
}

static struct platform_driver hi3630_asp_dma_voice_driver = {
	.driver = {
		.name	= "hi3630-pcm-asp-dma-voice",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_asp_dma_voice_of_match,
	},
	.probe	= hi3630_asp_dma_voice_probe,
	.remove	= hi3630_asp_dma_voice_remove,
};
module_platform_driver(hi3630_asp_dma_voice_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 ASP DMA Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi3630_asp_dma_voice");
