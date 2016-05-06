/*
 * hi3630_pcm_hdmi.c -- ALSA SoC HI3630 PCM HDMI driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_PCM_HDMI"

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
#include "hi3630_pcm_hdmi.h"

#include "../../../drivers/video/k3/hdmi/k3_hdmi.h"

static const unsigned int freq[] = {
	8000,	11025,	12000,	16000,
	22050,	24000,	32000,	44100,
	48000,	88200,	96000,	176400,
	192000,
};

#define HI3630_RATE_INDEX_32000	6
#define HI3630_RATE_INDEX_44100	7
#define HI3630_RATE_INDEX_48000	8
#define HI3630_RATE_INDEX_96000	10
#define HI3630_RATE_INDEX_176400	11
#define HI3630_RATE_INDEX_192000	12

#define HI3630_RATE_48000	( 48000 )

extern void hdmi_module_enable(bool enable);

extern int  hi3630_asp_irq_read(struct hi3630_asp_irq *irq,
				unsigned int reg);
extern void hi3630_asp_irq_write(struct hi3630_asp_irq *irq,
				 unsigned int reg, unsigned int value);
extern void hi3630_asp_irq_set_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);
extern void hi3630_asp_irq_clr_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);
extern int hi3630_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream);
extern void hi3630_pcm_free_dma_buffers(struct snd_pcm *pcm);
extern void enable_hdmi_interrupeter(bool enable);
extern void hi3630_hdmi_set_freq(const unsigned int value);
extern void hi3630_hdmi_clk_cfg(bool enable);

static const struct snd_pcm_hardware hi3630_pcm_hdmi_hardware = {
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

static const struct of_device_id hi3630_pcm_hdmi_match[] = {
	{ .compatible = "hisilicon,hi3630-pcm-hdmi", },
	{},
};
MODULE_DEVICE_TABLE(of, hi3630_pcm_hdmi_match);

static inline int hi3630_hdmi_reg_read(struct hi3630_hdmi_data *pdata, unsigned int reg)
{
	BUG_ON(NULL == pdata);
	return hi3630_asp_irq_read(pdata->hi3630_asp_irq, reg);
}

static inline void hi3630_hdmi_reg_write(struct hi3630_hdmi_data *pdata, unsigned int reg, unsigned int value)
{
	BUG_ON(NULL == pdata);
	hi3630_asp_irq_write(pdata->hi3630_asp_irq, reg, value);
}

static inline void hi3630_hdmi_set_bit(struct hi3630_hdmi_data *pdata, unsigned int reg, unsigned int offset)
{
	BUG_ON(NULL == pdata);
	hi3630_asp_irq_set_bit(pdata->hi3630_asp_irq, reg, offset);
}

static inline void hi3630_hdmi_clr_bit(struct hi3630_hdmi_data *pdata, unsigned int reg, unsigned int offset)
{
	BUG_ON(NULL == pdata);
	hi3630_asp_irq_clr_bit(pdata->hi3630_asp_irq, reg, offset);
}

static inline void hi3630_hdmi_enable_dma(struct hi3630_hdmi_data *pdata, unsigned int dma_ch)
{
	BUG_ON(NULL == pdata);
	hi3630_hdmi_set_bit(pdata, HI3630_ASP_DMA_EN, dma_ch);
}

static void config_hdmi_dma(struct hi3630_hdmi_runtime_data *prtd,
			     unsigned int dma_ch)
{
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	unsigned int addr = prtd->dma_addr + prtd->period_next * prtd->period_size;
	unsigned int size = prtd->period_size;

	switch (dma_ch) {
	case HDMI_DMA_A:
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_A_ADDR, addr);
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_A_LEN, size);
		break;
	case HDMI_DMA_B:
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_B_ADDR, addr);
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_B_LEN, size);
		break;
	default:
		loge("unknown hdmi dma ch: %d.\n", dma_ch);
		break;
	}
}

void hi3630_tx3_enable(struct hi3630_hdmi_data *pdata, bool enable)
{
	BUG_ON(NULL == pdata);

	if (enable) {
		hi3630_hdmi_set_bit(pdata, HI3630_ASP_TX3, HDMI_TX3_EN_BIT);
	} else {
		if (1 == (hi3630_hdmi_reg_read(pdata, HI3630_ASP_TX3) & 0x1))
			hi3630_hdmi_clr_bit(pdata, HI3630_ASP_TX3, HDMI_TX3_EN_BIT);
	}
}

static unsigned int hi3630_get_afrequency(unsigned int infreq_index,unsigned int* outfreq_index,unsigned int channels)
{
	const unsigned int freq_48k = 0x45E7B2;
	const unsigned int freq_96k = 0x8BCF65;
	//by default, input freq is equal to output freq
	*outfreq_index = infreq_index;

	//pcm
	if(freq[infreq_index] > HI3630_RATE_48000) {
		*outfreq_index = HI3630_RATE_INDEX_96000;
		hi3630_hdmi_set_freq(freq_96k);
	} else {
		*outfreq_index = HI3630_RATE_INDEX_48000;
		hi3630_hdmi_set_freq(freq_48k);
	}

	return 0;//eroute;
}

static irqreturn_t hi3630_intr_pcm_hdmi_handle(int irq, void *dev_id)
{
	struct snd_pcm *pcm = dev_id;
	struct snd_pcm_substream *substream = NULL;
	struct snd_pcm_runtime *runtime = NULL;
	struct hi3630_hdmi_runtime_data *prtd = NULL;
	struct hi3630_hdmi_data *pdata = NULL;
	unsigned int rt_period_size = 0;
	unsigned int num_periods = 0;
	unsigned int irs = 0;
	unsigned int dma_cur = HDMI_DMA_A;
	unsigned int dma_next = HDMI_DMA_A;
	snd_pcm_uframes_t avail = 0;

	BUG_ON(NULL == pcm);
	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	if (NULL == substream) {
		loge("substream is NULL\n");
		return IRQ_HANDLED;
	}

	runtime = substream->runtime;
	prtd = runtime->private_data;
	pdata = prtd->pdata;
	rt_period_size = runtime->period_size;
	num_periods = runtime->periods;

	irs = hi3630_hdmi_reg_read(pdata, HI3630_ASP_INT_STATE) & HDMI_DMA_MASK;

	if (0 == irs) {
		logw("not hdmi dma irq\n");
		return IRQ_HANDLED;
	}

	spin_lock(&prtd->lock);
	prtd->period_cur = (prtd->period_cur + 1) % num_periods;
	spin_unlock(&prtd->lock);

	snd_pcm_period_elapsed(substream);

	spin_lock(&prtd->lock);

	if (STATUS_HDMI_STOP == prtd->status) {
		logd("stop dma, irs = %#x\n", irs);
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_INT_CLR, irs);
		spin_unlock(&prtd->lock);
		return IRQ_HANDLED;
	}

	if (0 != ((1 << HDMI_DMA_A) & irs)) {
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_INT_CLR, HDMI_DMA_A_MASK);
		dma_cur = HDMI_DMA_A;
		dma_next = HDMI_DMA_B;
	} else {
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_INT_CLR, HDMI_DMA_B_MASK);
		dma_cur = HDMI_DMA_B;
		dma_next = HDMI_DMA_A;
	}

	avail = snd_pcm_playback_hw_avail(runtime);

	if(avail < rt_period_size) {
		logd("Run out of data\n");
		prtd->two_dma_flag = false;
	} else {
		/* config & enable DMA */
		config_hdmi_dma(prtd, dma_cur);
		hi3630_hdmi_enable_dma(pdata, dma_cur);
		prtd->period_next = (prtd->period_next + 1) % num_periods;
		if ((!prtd->two_dma_flag) && (avail >= rt_period_size * 2)) {
			/* config & enable DMA */
			config_hdmi_dma(prtd, dma_next);
			hi3630_hdmi_enable_dma(pdata, dma_next);
			prtd->period_next = (prtd->period_next + 1) % num_periods;
			prtd->two_dma_flag = true;
		}
	}

	spin_unlock(&prtd->lock);

	return IRQ_HANDLED;
}

static int hi3630_pcm_hdmi_open(struct snd_pcm_substream *substream)
{
	struct hi3630_hdmi_runtime_data *prtd = NULL;
	struct snd_soc_pcm_runtime *rtd = NULL;
	struct hi3630_hdmi_data *pdata = NULL;
	struct snd_pcm *pcm = substream->pcm;
	int ret = 0;

	BUG_ON(NULL == pcm);

	prtd = kzalloc(sizeof(struct hi3630_hdmi_runtime_data), GFP_KERNEL);
	if (NULL == prtd) {
		loge("kzalloc hi3630_hdmi_runtime_data error!\n");
		return -ENOMEM;
	}

	mutex_init(&prtd->mutex);
	spin_lock_init(&prtd->lock);

	rtd = (struct snd_soc_pcm_runtime *)substream->private_data;
	pdata = (struct hi3630_hdmi_data *)snd_soc_platform_get_drvdata(rtd->platform);

	BUG_ON(NULL == pdata);

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_get_sync(pdata->dev);
#else
	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret) {
		loge("couldn't enable regulators %d\n", ret);
		goto err_bulk;
	}
#endif

	prtd->pdata = pdata;

	substream->runtime->private_data = prtd;

	hdmi_module_enable(true);

	ret = request_irq(pdata->irq, hi3630_intr_pcm_hdmi_handle,
			  IRQF_SHARED, "asp_irq_hdmi", pcm);
	if (0 > ret) {
		loge("request irq error, error No. = %d\n", ret);
		goto err_irq;
	}

	hi3630_tx3_enable(pdata, true);

	enable_hdmi_interrupeter(true);

	ret = snd_soc_set_runtime_hwparams(substream, &hi3630_pcm_hdmi_hardware);

	return ret;

err_irq:
	hdmi_module_enable(false);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
#else
	regulator_bulk_disable(1, &prtd->pdata->regu);
err_bulk:
#endif
	kfree(prtd);
	return ret;
}

static int hi3630_pcm_hdmi_close(struct snd_pcm_substream *substream)
{
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;

	if(NULL == prtd) {
		loge("prtd is NULL\n");
	} else {
		BUG_ON(NULL == prtd->pdata);
		free_irq(prtd->pdata->irq, substream->pcm);
		enable_hdmi_interrupeter(false);
		hi3630_tx3_enable(prtd->pdata, false);
		hdmi_module_enable(false);

#ifdef CONFIG_PM_RUNTIME
		pm_runtime_mark_last_busy(prtd->pdata->dev);
		pm_runtime_put_autosuspend(prtd->pdata->dev);
#else
		regulator_bulk_disable(1, &prtd->pdata->regu);
#endif

		kfree(prtd);
		substream->runtime->private_data = NULL;
	}

	return 0;
}

static int hi3630_pcm_hdmi_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *params)
{
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	unsigned long bytes = params_buffer_bytes(params);
	unsigned int params_value = 0;
	unsigned int channels = 0;
	unsigned int infreq_index = 0;
	unsigned int outfreq_index = 0;
	unsigned int width = 0;
	unsigned int format = 0;
	int txValue = 0;
	int ret = 0;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		ret = snd_pcm_lib_malloc_pages(substream, bytes);
		if (0 > ret) {
			loge("snd_pcm_lib_malloc_pages ret is %d", ret);
			return ret;
		}

		/* CHECK SUPPORT CHANNELS : mono or stereo */
		params_value = params_channels(params);
		if (2 == params_value || 1 == params_value) {
			channels = params_value;
		} else {
			loge("DAC not support %d channels\n", params_value);
			ret = -EINVAL;
			goto err_out;
		}
		params_value = params_rate(params);
		logd("set rate = %d \n", params_value);
		for (infreq_index = 0; infreq_index < ARRAY_SIZE(freq); infreq_index++) {
			if(params_value == freq[infreq_index])
				break;
		}
		if ( ARRAY_SIZE(freq) <= infreq_index) {
			loge("set rate = %d error\n", params_value);
			return -EINVAL;
		}
		hi3630_get_afrequency(infreq_index, &outfreq_index, channels);

		params_value = params_format(params);
		/* check formats */
		switch (params_value) {
		case SNDRV_PCM_FORMAT_S16_BE :
			format = HDMI_BIG_DIAN_BIT;
			/* fallthrough */
		case SNDRV_PCM_FORMAT_S16_LE :
			if (2 == channels)
				width = STEREO_16BIT;
			break;
		default :
			loge("format err : %d, not support\n", params_value);
			ret = -EINVAL;
			goto err_out;
		}

		mutex_lock(&prtd->mutex);
		prtd->period_size = params_period_bytes(params);
		mutex_unlock(&prtd->mutex);

		txValue = hi3630_hdmi_reg_read(pdata, HI3630_ASP_TX3);
		txValue |= (width << 3) | (1 << 6) | ((channels-1) << 7) |format;
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_TX3, txValue);
		logi("hdmi params.freq:%d, channel:%d\n", freq[outfreq_index], channels);
		k3_hdmi_audio_set_param(freq[outfreq_index], HDMI_SAMPLE_16BITS, true, 0, 1, channels);

err_out:
		if (0 > ret) {
			loge("hw params error, ret : %d\n", ret);
			snd_pcm_lib_free_pages(substream);
		}
	}

	return ret;
}

static void wait_hdmi_dma_stop(struct hi3630_hdmi_runtime_data *prtd)
{
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	unsigned int dma_en = 0;
	unsigned int int_mask_flag = 0;
	unsigned int i = 3;

	/*don't use ASP_DSTOP whitch can create delayed interrupt*/
	do {
		dma_en = hi3630_hdmi_reg_read(pdata, HI3630_ASP_DMA_EN);
		int_mask_flag = hi3630_hdmi_reg_read(pdata, HI3630_ASP_INT_MSK_STATE);

		if ((dma_en | int_mask_flag) & HDMI_DMA_MASK) {
			usleep_range(HI3630_MIN_DMA_TIME_US, HI3630_MAX_DMA_TIME_US);
		} else {
			break;
		}
	} while(--i);

	if (!i)
		loge("wait hdmi dma over time!");
}

static int hi3630_pcm_hdmi_hw_free(struct snd_pcm_substream *substream)
{
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	int ret = 0;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		wait_hdmi_dma_stop(prtd);

		/*clear interrupt*/
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_INT_CLR, HDMI_INT_MASK);

		ret = snd_pcm_lib_free_pages(substream);
	}

	snd_pcm_set_runtime_buffer(substream, NULL);

	return ret;
}

static int hi3630_pcm_hdmi_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	unsigned int num_periods = substream->runtime->periods;

	mutex_lock(&prtd->mutex);

	prtd->status = STATUS_HDMI_STOP;
	prtd->two_dma_flag = true;
	prtd->period_next = 0;
	prtd->period_cur = 0;
	prtd->dma_addr = runtime->dma_addr;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		wait_hdmi_dma_stop(prtd);

		/* config DMA CH_A */
		config_hdmi_dma(prtd, HDMI_DMA_A);
		prtd->period_next = (prtd->period_next + 1) % num_periods;
		/* config DMA CH_B */
		config_hdmi_dma(prtd, HDMI_DMA_B);
		prtd->period_next = (prtd->period_next + 1) % num_periods;

		/*clear all interrupt*/
		hi3630_hdmi_reg_write(pdata, HI3630_ASP_INT_CLR, HDMI_INT_MASK);
	}

	mutex_unlock(&prtd->mutex);

	return 0;
}

static int hi3630_pcm_hdmi_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_hdmi_data *pdata = prtd->pdata;
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			k3_hdmi_audio_set_power(true);
			prtd->status = STATUS_HDMI_RUNNING;
			hi3630_hdmi_enable_dma(pdata, HDMI_DMA_A);
			hi3630_hdmi_enable_dma(pdata, HDMI_DMA_B);

			/*hdmi ch int en*/
			hi3630_hdmi_set_bit(pdata, HI3630_ASP_INT_EN, HDMI_A_INT_EN_BIT);
			hi3630_hdmi_set_bit(pdata, HI3630_ASP_INT_EN, HDMI_B_INT_EN_BIT);
		}
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			k3_hdmi_audio_set_power(false);
			prtd->status = STATUS_HDMI_STOP;

			/*int disable*/
			hi3630_hdmi_clr_bit(pdata, HI3630_ASP_INT_EN, HDMI_A_INT_EN_BIT);
			hi3630_hdmi_clr_bit(pdata, HI3630_ASP_INT_EN, HDMI_B_INT_EN_BIT);
		}
		break;

	default:
		loge("error!");
		ret = -EINVAL;
		break;
	}

	return ret;
}

static snd_pcm_uframes_t hi3630_pcm_hdmi_pointer(struct snd_pcm_substream *substream)
{
	snd_pcm_uframes_t offset = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_hdmi_runtime_data *prtd = substream->runtime->private_data;

	unsigned int period_cur = 0;
	unsigned int period_size = 0;

	spin_lock(&prtd->lock);
	period_cur = prtd->period_cur;
	period_size = prtd->period_size;
	spin_unlock(&prtd->lock);

	offset = bytes_to_frames(runtime, period_cur * period_size);
	if(offset >= runtime->buffer_size)
		offset = 0;

	return offset;
}

static int hi3630_hdmi_normal_mmap(struct snd_pcm_substream *substream,
				 struct vm_area_struct *vma)
{
	int ret = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (NULL != runtime)
		ret = dma_mmap_writecombine(substream->pcm->card->dev,
					    vma,
					    runtime->dma_area,
					    runtime->dma_addr,
					    runtime->dma_bytes);

	return ret;
}


static struct snd_pcm_ops hi3630_pcm_hdmi_ops = {
	.open		= hi3630_pcm_hdmi_open,
	.close		= hi3630_pcm_hdmi_close,
	.ioctl		= snd_pcm_lib_ioctl,
	.hw_params	= hi3630_pcm_hdmi_hw_params,
	.hw_free	= hi3630_pcm_hdmi_hw_free,
	.prepare	= hi3630_pcm_hdmi_prepare,
	.trigger	= hi3630_pcm_hdmi_trigger,
	.pointer	= hi3630_pcm_hdmi_pointer,
	.mmap	= hi3630_hdmi_normal_mmap,
};

static unsigned long long hi3630_pcm_dmamask = DMA_BIT_MASK(32);

static int hi3630_pcm_hdmi_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm  *pcm  = rtd->pcm;
	struct hi3630_hdmi_data *pdata =
		(struct hi3630_hdmi_data *)snd_soc_platform_get_drvdata(rtd->platform);
	int ret = 0;

	BUG_ON(NULL == card);
	BUG_ON(NULL == pcm);
	BUG_ON(NULL == pdata);

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &hi3630_pcm_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = DMA_BIT_MASK(32);

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) {
		ret = hi3630_pcm_preallocate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK);
		if (ret) {
			loge("preallocate dma buffer error, error No. = %d\n", ret);
			return ret;
		}
	}

	return ret;
}

static void hi3630_pcm_hdmi_free(struct snd_pcm *pcm)
{
	BUG_ON(NULL == pcm);

	hi3630_pcm_free_dma_buffers(pcm);
}

static struct snd_soc_platform_driver hi3630_pcm_hdmi_platform = {
	.ops		= &hi3630_pcm_hdmi_ops,
	.pcm_new	= hi3630_pcm_hdmi_new,
	.pcm_free	= hi3630_pcm_hdmi_free,
};

static int hi3630_pcm_hdmi_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;
	struct hi3630_hdmi_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata){
		dev_err(dev, "cannot allocate hi3630 hdmi platform data\n");
		return -ENOMEM;
	}

	pdata->hi3630_asp_irq = dev_get_drvdata(pdev->dev.parent);
	if (!pdata->hi3630_asp_irq) {
		dev_err(dev, "get parent device error\n");
		return -ENOENT;
	}

	pdata->irq = platform_get_irq_byname(pdev, "asp_irq_hdmi");
	if (0 > pdata->irq) {
		dev_err(dev, "cannot get irq\n");
		return -ENOENT;
	}

	pdata->regu.supply = "hdmi-pcm";
	ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
	if (0 != ret) {
		dev_err(dev, "couldn't get regulators %d\n", ret);
		return -ENOENT;
	}

	pdata->dev = dev;

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms*/
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif

	platform_set_drvdata(pdev, pdata);

	dev_set_name(dev, "hi3630-pcm-hdmi");

	ret = snd_soc_register_platform(dev, &hi3630_pcm_hdmi_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n", ret);
		return -ENODEV;
	}

	return ret;
}

static int hi3630_pcm_hdmi_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
	return 0;
}

#ifdef CONFIG_PM_RUNTIME
int hi3630_hdmi_runtime_suspend(struct device *dev)
{
	struct hi3630_hdmi_data *pdata = dev_get_drvdata(dev);

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	regulator_bulk_disable(1, &pdata->regu);

	dev_info(dev, "%s-", __FUNCTION__);

	return 0;
}

int hi3630_hdmi_runtime_resume(struct device *dev)
{
	struct hi3630_hdmi_data *pdata = dev_get_drvdata(dev);
	int ret;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret)
		dev_err(dev, "couldn't enable regulators %d\n", ret);

	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_hdmi_pm_ops = {
	.runtime_suspend	= hi3630_hdmi_runtime_suspend,
	.runtime_resume		= hi3630_hdmi_runtime_resume,
};
#endif

static struct platform_driver hi3630_pcm_hdmi_driver = {
	.probe	= hi3630_pcm_hdmi_probe,
	.remove	= hi3630_pcm_hdmi_remove,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi3630-pcm-hdmi",
		.of_match_table = of_match_ptr(hi3630_pcm_hdmi_match),
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_hdmi_pm_ops,
#endif
	},
};

module_platform_driver(hi3630_pcm_hdmi_driver);

MODULE_DESCRIPTION("ASoC hi3630 pcm hdmi driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
