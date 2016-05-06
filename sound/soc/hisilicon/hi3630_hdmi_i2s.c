/*
 * hi3630-sio.c -- ALSA SoC HI3630 SIO DAI driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_HDMI_I2S"

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
#include <sound/core.h>
#include <sound/dmaengine_pcm.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>

#include "hi3630_log.h"
#include "hi3630_hdmi_i2s.h"

#define HISI_I2S_RATES (SNDRV_PCM_RATE_8000_96000)

#if 0
static unsigned int hi3630_sio_reg_read(struct hi3630_sio_platform_data *pdata,
					unsigned int reg)
{
	return readl(pdata->reg_base_addr + reg);
}
#endif
static int hi3630_i2s_reg_write(struct hi3630_hdmi_i2s_platform_data *pdata,
				unsigned int reg,
				unsigned int value)
{
	writel(value, pdata->reg_base_addr + reg);
	return 0;
}

static int i2s_hdmi_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct hi3630_hdmi_i2s_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	/*SIO1 config*/
	/*normal mode*/
	hi3630_i2s_reg_write(pdata, HI3630_SIO1_ASPIF_SEL, HDMI_I2S_ACC_CTL);

       /*i2s set clr*/
	hi3630_i2s_reg_write(pdata, HI3630_SIO1_I2S_CLR, HDMI_I2S_TX_CLR | HDMI_I2S_FIFO_DIS_CLR | HDMI_I2S_FIFO_THD_CLR);

	/*i2s set*/
	hi3630_i2s_reg_write(pdata, HI3630_SIO1_I2S_SET, HDMI_I2S_TX_EN | HDMI_I2S_FIFO_DIS | HDMI_I2S_FIFO_THD);

	return 0;
}

static int i2s_hdmi_hw_free(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct hi3630_hdmi_i2s_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	/*i2s set clr*/
	hi3630_i2s_reg_write(pdata, HI3630_SIO1_I2S_CLR, HDMI_I2S_TX_CLR);

	hi3630_i2s_reg_write(pdata, HI3630_SIO1_TX_CLR, 1);

	return 0;
}

static int hi3630_i2s_probe(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static int hi3630_i2s_remove(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static const struct snd_soc_dai_ops i2s_hdmi_ops = {
	.hw_params	= i2s_hdmi_hw_params,
	.hw_free	= i2s_hdmi_hw_free,
};

static struct snd_soc_dai_driver hi3630_i2s_dai = {
	.probe = hi3630_i2s_probe,
	.remove = hi3630_i2s_remove,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_I2S_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE,
	},
	.ops = &i2s_hdmi_ops,
};

static const struct snd_soc_component_driver hi3630_i2s_component = {
	.name		= "hi3630-i2s",
};

static const struct of_device_id hi3630_i2s_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-i2s",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_i2s_of_match);

static int hdmi_i2s_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3630_hdmi_i2s_platform_data *pdata = NULL;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (NULL == pdata){
		dev_err(dev, "cannot allocate hdmi i2s platform data\n");
		return -ENOMEM;
	}

	pdata->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (NULL == pdata->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	pdata->reg_base_addr = devm_ioremap(dev, pdata->res->start,
					    resource_size(pdata->res));
	if (NULL == pdata->reg_base_addr) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}

	/* rename device name */
       dev_set_name(dev, "i2s-hdmi-dai");
	platform_set_drvdata(pdev, pdata);

	return snd_soc_register_component(&pdev->dev, &hi3630_i2s_component,
					  &hi3630_i2s_dai, 1);
}

static int hdmi_i2s_remove(struct platform_device *pdev)
{
	snd_soc_unregister_component(&pdev->dev);
	return 0;
}

static struct platform_driver hi3630_i2s_driver = {
	.driver = {
		.name	= "hi3630-i2s",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_i2s_of_match,
	},
	.probe	= hdmi_i2s_probe,
	.remove	= hdmi_i2s_remove,
};
module_platform_driver(hi3630_i2s_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 HDMI I2S");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi3630_hdmi_i2s");
