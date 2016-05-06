/*
 * hi3630-sio.c -- ALSA SoC HI3630 SIO DAI driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_SIO"

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
#include <linux/pm_runtime.h>

#include "hi3630_log.h"
#include "hi3630_sio.h"

#define HISI_SIO_RATES (SNDRV_PCM_RATE_8000_96000)

extern void sio_audio_module_enable(bool enable);
extern void sio_voice_module_enable(bool enable);
extern void sio_bt_module_enable(bool enable);
extern void sio_modem_module_enable(bool enable);

extern void set_sio_audio_master(bool enable);
extern void set_sio_voice_master(bool enable);
extern void set_sio_bt_master(bool enable);
extern void set_sio_modem_master(bool enable);

#define REGULATOR_ENABLE 1
#define PINCTRL_ENABLE   1
#if 0
static unsigned int hi3630_sio_reg_read(struct hi3630_sio_platform_data *pdata,
					unsigned int reg)
{
	return readl(pdata->reg_base_addr + reg);
}
#endif
static int hi3630_sio_reg_write(struct hi3630_sio_platform_data *pdata,
				unsigned int reg,
				unsigned int value)
{
	writel(value, pdata->reg_base_addr + reg);
	return 0;
}

static int sio_dai_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);
	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:
/* AP don't control sio start or stop,
 * SIO start or stop control handled in HiFi!
 * delete this code!
 */
#if 0
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_get_sync(pdata->dev);
#else
	{
		struct pinctrl_state *pinctrl_state;
		int ret = -1;

#ifdef  REGULATOR_ENABLE
		ret = regulator_bulk_enable(1, &pdata->regu);
		if (0 != ret) {
			loge("couldn't enable regulators %d\n", ret);
			return -ENOENT;
		}
#endif

		mutex_lock(&pdata->mutex);
		if (0 == pdata->active_count) {
			/* config iomux */
#ifdef PINCTRL_ENABLE
			pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_DEFAULT);
			if (IS_ERR(pinctrl_state)) {
				loge("could not get defstate (%li)\n", PTR_ERR(pinctrl_state));
				mutex_unlock(&pdata->mutex);
				return ret;
			}
			ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
			if (ret) {
				loge("could not set pins to default state\n");
				mutex_unlock(&pdata->mutex);
				return ret;
			}
#endif
		}		
		pdata->active_count++;
		mutex_unlock(&pdata->mutex);
	}
#endif
		set_sio_audio_master(pdata->is_master);
		sio_audio_module_enable(true);
#endif
		break;
	case SIO_VOICE_ID:
#if 0
		set_sio_voice_master(pdata->is_master);
		sio_voice_module_enable(true);
#endif
		break;
	case SIO_BT_ID:
		set_sio_bt_master(pdata->is_master);
		sio_bt_module_enable(true);
		break;
	case SIO_MODEM_ID:
		set_sio_modem_master(pdata->is_master);
		sio_modem_module_enable(true);
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static void sio_dai_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:
/* AP don't control sio start or stop,
 * SIO start or stop control handled in HiFi!
 * delete this code!
 */
#if 0
		sio_audio_module_enable(false);

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
#else
	{
		struct pinctrl_state *pinctrl_state;
		int ret = -1;

		mutex_lock(&pdata->mutex);
		if (0 == pdata->active_count) {
			loge("sio iomux is alread set as default\n");
			goto err;
		}
		pdata->active_count--;
		if (0 == pdata->active_count) {
			/* config iomux */
#ifdef PINCTRL_ENABLE
			pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_IDLE);
			if (IS_ERR(pinctrl_state)) {
				loge("could not get defstate (%li)\n", PTR_ERR(pinctrl_state));
				goto err;
			}
			ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
			if (0 != ret) {
				loge("could not set pins to idle state\n");
				goto err;
			}
#endif
		}
	}
err:
#ifdef  REGULATOR_ENABLE
	regulator_bulk_disable(1, &pdata->regu);
#endif
	mutex_unlock(&pdata->mutex);
#endif
#endif
		break;
	case SIO_VOICE_ID:
#if 0
		sio_voice_module_enable(false);
#endif
		break;
	case SIO_BT_ID:
		sio_bt_module_enable(false);
		break;
	case SIO_MODEM_ID:
		sio_modem_module_enable(false);
		break;
	default:
		loge("unknown sio\n");
		break;
	}
}

static void enable_sio_audio_tx(struct hi3630_sio_platform_data *pdata)
{
	if (0 == pdata->pb_active) {
		/* clr fifo */
		hi3630_sio_reg_write(pdata, SIO_CTL_SET, SIO_TX_FIFO_DISABLE);
		hi3630_sio_reg_write(pdata, SIO_CTL_CLR,
				SIO_TX_ENABLE | SIO_TX_FIFO_DISABLE |
				SIO_TX_DATA_MERGE | SIO_TX_FIFO_THRESHOLD_CLR);
		hi3630_sio_reg_write(pdata, SIO_CTL_SET,
				SIO_TX_ENABLE | SIO_TX_DATA_MERGE | SIO_TX_FIFO_THRESHOLD);
	}

	pdata->pb_active++;
}

static void disable_sio_audio_tx(struct hi3630_sio_platform_data *pdata)
{
	if (0 == pdata->pb_active) {
		loge("sio audio has already closed");
		return;
	}

	pdata->pb_active--;

	if (0 == pdata->pb_active)
		hi3630_sio_reg_write(pdata, SIO_CTL_CLR, SIO_TX_ENABLE);
}

static inline void enable_sio_audio_rx(struct hi3630_sio_platform_data *pdata)
{
	/* clr fifo */
	hi3630_sio_reg_write(pdata, SIO_CTL_SET, SIO_RX_FIFO_DISABLE);
	hi3630_sio_reg_write(pdata, SIO_CTL_CLR,
			SIO_RX_ENABLE | SIO_RX_FIFO_DISABLE |
			SIO_RX_DATA_MERGE | SIO_RX_FIFO_THRESHOLD_CLR);
	hi3630_sio_reg_write(pdata, SIO_CTL_SET,
			SIO_RX_ENABLE | SIO_RX_DATA_MERGE | SIO_RX_FIFO_THRESHOLD);
}

static inline void disable_sio_audio_rx(struct hi3630_sio_platform_data *pdata)
{
	hi3630_sio_reg_write(pdata, SIO_CTL_CLR, SIO_RX_ENABLE);
}

static int sio_dai_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	/* config sio mode & parameters */
	switch (pdata->id) {
	case SIO_AUDIO_ID:
/* AP don't control sio start or stop,
 * SIO start or stop handled in HiFi!
 * delete this code!
 */
#if 0
		hi3630_sio_reg_write(pdata, SIO_CFG, SIO_CFG_SIO_MODE);
		/* to do*/
		hi3630_sio_reg_write(pdata, SIO_DATA_WIDTH, 0x24);
		hi3630_sio_reg_write(pdata, SIO_I2S_POS_MERGE, 0x1);

		/* config control regs */
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
			enable_sio_audio_tx(pdata);
		else
			enable_sio_audio_rx(pdata);
#endif
		break;
	case SIO_VOICE_ID:
		break;
	case SIO_BT_ID:
		/* not used */
		break;
	case SIO_MODEM_ID:
		hi3630_sio_reg_write(pdata, SIO_CFG, SIO_CFG_SIO_MODE);
		/* todo */
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static int sio_dai_hw_free(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:
/* AP don't control sio start or stop,
 * SIO start or stop handled in HiFi!
 * delete this code!
 */
#if 0
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
			disable_sio_audio_tx(pdata);
		else
			disable_sio_audio_rx(pdata);
#endif
		break;
	case SIO_VOICE_ID:
		break;
	case SIO_BT_ID:
		/* not used */
		break;
	case SIO_MODEM_ID:
		/* todo */
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static const struct snd_soc_dai_ops sio_dai_ops = {
	.startup	= sio_dai_startup,
	.shutdown	= sio_dai_shutdown,
	.hw_params	= sio_dai_hw_params,
	.hw_free	= sio_dai_hw_free,
};

static int hi3630_sio_probe(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static int hi3630_sio_remove(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static const struct snd_soc_component_driver hi3630_sio_component = {
	.name		= "hi3630-sio",
};

static struct snd_soc_dai_driver hi3630_sio_dai = {
	.probe = hi3630_sio_probe,
	.remove = hi3630_sio_remove,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_SIO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE,
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_SIO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	},
	.ops = &sio_dai_ops,
};

static const struct of_device_id hi3630_sio_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-sio",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_sio_of_match);

static int soc_sio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3630_sio_platform_data *pdata = NULL;
	const struct of_device_id *match;
	int ret = -1;

	BUG_ON(NULL == dev);

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (NULL == pdata){
		dev_err(dev, "cannot allocate hi6401 codec platform data\n");
		return -ENOMEM;
	}

	pdata->dev = dev;

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
#ifdef PINCTRL_ENABLE
	/* get pinctrl */
	pdata->pctrl = pinctrl_get(dev);
	if (IS_ERR(pdata->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		return -ENOENT;
	}
#endif 
	match = of_match_device(hi3630_sio_of_match, dev);
	if (!match) {
		dev_err(dev, "get device info err\n");
		return -ENOENT;
	} else {
		struct device_node *node = dev->of_node;

		/* get defination */
		pdata->is_master = of_property_read_bool(node, "hisilicon,is_master");
	}

	logi("sio is_master = %s\n", pdata->is_master ? "t":"f");

	dev_set_name(dev, "1111 SIO_AUDIO_ADDR = 0x%x,0x%x \n",SIO_AUDIO_ADDR,SIO_BT_ADDR);
	/* rename device name */
	switch (pdata->res->start) {
	case SIO_AUDIO_ADDR:
		dev_set_name(dev, "sio-audio");
		pdata->id = SIO_AUDIO_ID;
		pdata->pb_active = 0;

#ifdef  REGULATOR_ENABLE
		pdata->regu.supply = "sio-audio";
		ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
		if (0 != ret) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_VOICE_ADDR:
		dev_set_name(dev, "sio-voice");
		pdata->id = SIO_VOICE_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu.supply = "sio-voice";
		ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
		if (0 != ret) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_BT_ADDR:
		dev_set_name(dev, "sio-bt");
		pdata->id = SIO_BT_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu.supply = "sio-bt";
		ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
		if (0 != ret) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_MODEM_ADDR:
		dev_set_name(dev, "sio-modem");
		pdata->id = SIO_MODEM_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu.supply = "sio-modem";
		ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
		if (0 != ret) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif

		break;
	default:
		dev_err(dev, "111 unknown sio\n");
		break;
	}

	mutex_init(&pdata->mutex);

	pdata->active_count = 0;

	platform_set_drvdata(pdev, pdata);

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms */
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif

	return snd_soc_register_component(&pdev->dev, &hi3630_sio_component,
					  &hi3630_sio_dai, 1);
}

static int soc_sio_remove(struct platform_device *pdev)
{
	struct hi3630_sio_platform_data *pdata = platform_get_drvdata(pdev);
	BUG_ON(NULL == pdata);
#ifdef PINCTRL_ENABLE
	pinctrl_put(pdata->pctrl);
#endif
	snd_soc_unregister_component(&pdev->dev);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
	return 0;
}

#ifdef CONFIG_PM_RUNTIME
int hi3630_sio_runtime_suspend(struct device *dev)
{
	struct hi3630_sio_platform_data *pdata = dev_get_drvdata(dev);
	struct pinctrl_state *pinctrl_state;
	int ret = 0;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	/* VOICE SIO handled in HiFi */
	/* AP don't control sio start or stop,
	 * SIO start or stop handled in HiFi!
	 */
	if ((SIO_VOICE_ID == pdata->id) || (SIO_AUDIO_ID == pdata->id)) {
		goto err_exit;
	}
#ifdef REGULATOR_ENABLE
	regulator_bulk_disable(1, &pdata->regu);
#endif
#ifdef PINCTRL_ENABLE
	pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get defstate (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		ret = -ENOENT;
		goto err_exit;
	}
	ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
	if (0 != ret) {
		pr_err("%s : could not set pins to idle state\n",
				__FUNCTION__);
		ret = -ENOENT;
	}
#endif
err_exit:
	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

int hi3630_sio_runtime_resume(struct device *dev)
{
	struct hi3630_sio_platform_data *pdata = dev_get_drvdata(dev);
	struct pinctrl_state *pinctrl_state;
	int ret = 0;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	/* VOICE SIO handled in HiFi */
	/* AP don't control sio start or stop,
	 * SIO start or stop handled in HiFi!
	 */
	if ((SIO_VOICE_ID == pdata->id) || (SIO_AUDIO_ID == pdata->id)) {
		goto err_exit;
	}

#ifdef PINCTRL_ENABLE
	pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get defstate (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		ret = -ENOENT;
		goto err_exit;
	}

	ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
	if (0 != ret) {
		pr_err("%s : could not set pins to default state\n", __FUNCTION__);
		goto err_exit;
	}
#endif 

#ifdef  REGULATOR_ENABLE
	
	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret){
		dev_err(dev, "couldn't enable regulators %d\n", ret);
	}
	else {
		dev_err(dev, "============== Enable regulators ===========\n");
	}
	
#endif

err_exit:
	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_sio_pm_ops = {
	.runtime_suspend	= hi3630_sio_runtime_suspend,
	.runtime_resume		= hi3630_sio_runtime_resume,
};
#endif

static struct platform_driver hi3630_sio_driver = {
	.driver = {
		.name	= "hi3630-sio",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_sio_of_match,
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_sio_pm_ops,
#endif
	},
	.probe	= soc_sio_probe,
	.remove	= soc_sio_remove,
};
module_platform_driver(hi3630_sio_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 SIO Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi3630_sio");
