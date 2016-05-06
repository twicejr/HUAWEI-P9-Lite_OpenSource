/*
 * hi3630_srcdown.c -- ALSA SoC HI3630 SRCDOWN driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_SRCDOWN"

#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/dmaengine_pcm.h>
#include <sound/soc.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/pm_runtime.h>

#include <linux/mfd/hi3630_asp_irq.h>

#include "hi3630_log.h"
#include "hi3630_srcdown.h"

extern void srcdown_module_enable(bool enable);
extern int  hi3630_asp_irq_read(struct hi3630_asp_irq *irq,
				unsigned int reg);
extern void hi3630_asp_irq_write(struct hi3630_asp_irq *irq,
				 unsigned int reg, unsigned int value);
extern void hi3630_asp_irq_set_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);
extern void hi3630_asp_irq_clr_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);

static const struct snd_pcm_hardware hi3630_srcdown_hardware = {
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.formats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S16_BE |
				  SNDRV_PCM_FMTBIT_S24_LE |
				  SNDRV_PCM_FMTBIT_S24_BE,
	.period_bytes_min	= 32,
	.period_bytes_max	= 256,
	.periods_min		= 2,
	.periods_max		= 4,
	.buffer_bytes_max	= 1 * 1024,
};

static const struct of_device_id hi3630_srcdown_match[] = {
	{ .compatible = "hisilicon,hi3630-srcdown", },
	{},
};
MODULE_DEVICE_TABLE(of, hi3630_srcdown_match);

static int hi3630_srcdown_open(struct snd_pcm_substream *substream)
{
	struct hi3630_srcdown_runtime_data *prtd = NULL;
	struct snd_soc_pcm_runtime *rtd = NULL;
	struct hi3630_srcdown_data *pdata = NULL;
	struct snd_pcm *pcm = substream->pcm;
	int ret = 0;

	BUG_ON(NULL == pcm);

	prtd = kzalloc(sizeof(struct hi3630_srcdown_runtime_data), GFP_KERNEL);
	if (NULL == prtd) {
		loge("kzalloc hi3630_srcdown_runtime_data error!\n");
		return -ENOMEM;
	}

	rtd = (struct snd_soc_pcm_runtime *)substream->private_data;
	pdata = (struct hi3630_srcdown_data *)snd_soc_platform_get_drvdata(rtd->platform);

	BUG_ON(NULL == pdata);

	prtd->pdata = pdata;

	substream->runtime->private_data = prtd;

#ifdef SRCDOWN_ENABLE
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_get_sync(pdata->dev);
#else
	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret) {
		loge("couldn't enable regulators %d\n", ret);
		kfree(prtd);
		return -ENOENT;
	}
#endif

	srcdown_module_enable(true);
#endif

	ret = snd_soc_set_runtime_hwparams(substream, &hi3630_srcdown_hardware);

	return ret;
}

static int hi3630_srcdown_close(struct snd_pcm_substream *substream)
{
	struct hi3630_srcdown_runtime_data *prtd = substream->runtime->private_data;

	if (NULL == prtd) {
		loge("prtd is NULL\n");
	} else {
#ifdef SRCDOWN_ENABLE
		BUG_ON(NULL == prtd->pdata);

		srcdown_module_enable(false);

#ifdef CONFIG_PM_RUNTIME
		pm_runtime_mark_last_busy(prtd->pdata->dev);
		pm_runtime_put_autosuspend(prtd->pdata->dev);
#else
		regulator_bulk_disable(1, &prtd->pdata->regu);
#endif
#endif

		kfree(prtd);
		substream->runtime->private_data = NULL;
	}

	return 0;
}

static struct snd_pcm_ops hi3630_srcdown_ops = {
	.open	= hi3630_srcdown_open,
	.close	= hi3630_srcdown_close,
	.ioctl	= snd_pcm_lib_ioctl,
};

static unsigned long long hi3630_pcm_dmamask = DMA_BIT_MASK(32);

static int hi3630_srcdown_new(struct snd_soc_pcm_runtime *rtd)
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

static void hi3630_srcdown_free(struct snd_pcm *pcm)
{
	//do nothing
}

static struct snd_soc_platform_driver hi3630_srcdown_platform = {
	.ops		= &hi3630_srcdown_ops,
	.pcm_new	= hi3630_srcdown_new,
	.pcm_free	= hi3630_srcdown_free,
};

static int hi3630_srcdown_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;
	struct hi3630_srcdown_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata){
		dev_err(dev, "cannot allocate hi3630 srcdown platform data\n");
		return -ENOMEM;
	}

	pdata->dev = dev;

#ifdef SRCDOWN_ENABLE
	pdata->hi3630_asp_irq = dev_get_drvdata(pdev->dev.parent);
	if (!pdata->hi3630_asp_irq) {
		dev_err(dev, "get parent device error\n");
		return -ENOENT;
	}

	pdata->regu.supply = "asp-srcdown";
	ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
	if (0 != ret) {
		dev_err(dev, "couldn't get regulators %d\n", ret);
		return -ENOENT;
	}

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms*/
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif
#endif

	platform_set_drvdata(pdev, pdata);

	dev_set_name(dev, "hi3630-srcdown");

	ret = snd_soc_register_platform(dev, &hi3630_srcdown_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n",ret);
		return -ENODEV;
	}

	return ret;
}

static int hi3630_srcdown_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
#ifdef SRCDOWN_ENABLE
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
#endif
	return 0;
}

#ifdef SRCDOWN_ENABLE
#ifdef CONFIG_PM_RUNTIME
int hi3630_srcdown_runtime_suspend(struct device *dev)
{
	struct hi3630_srcdown_data *pdata = dev_get_drvdata(dev);

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	regulator_bulk_disable(1, &pdata->regu);

	dev_info(dev, "%s-", __FUNCTION__);

	return 0;
}

int hi3630_srcdown_runtime_resume(struct device *dev)
{
	struct hi3630_srcdown_data *pdata = dev_get_drvdata(dev);
	int ret;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret)
		dev_err(dev, "couldn't enable regulators %d\n", ret);

	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_srcdown_pm_ops = {
	.runtime_suspend	= hi3630_srcdown_runtime_suspend,
	.runtime_resume		= hi3630_srcdown_runtime_resume,
};
#endif
#endif

static struct platform_driver hi3630_srcdown_driver = {
	.probe	= hi3630_srcdown_probe,
	.remove	= hi3630_srcdown_remove,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi3630-srcdown",
		.of_match_table = of_match_ptr(hi3630_srcdown_match),
#ifdef SRCDOWN_ENABLE
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_srcdown_pm_ops,
#endif
#endif
	},
};

module_platform_driver(hi3630_srcdown_driver);

MODULE_DESCRIPTION("ASoC hi3630 srcdown dsp driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
