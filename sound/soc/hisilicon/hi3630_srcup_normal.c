/*
 * hi3630_srcup_normal.c -- ALSA SoC HI3630 SRCUP NORMAL driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_SRCUP_NORMAL"

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
#include "hi3630_srcup.h"

#define HWLOCK_ID		3  /* hardware lock ID */
#define HWLOCK_WAIT_TIME	50 /* 50ms */

extern void srcup_module_enable(bool enable);

extern int hi3630_asp_irq_read(struct hi3630_asp_irq *irq,
				unsigned int reg);
extern void hi3630_asp_irq_write(struct hi3630_asp_irq *irq,
				 unsigned int reg, unsigned int value);
extern void hi3630_asp_irq_set_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);
extern void hi3630_asp_irq_clr_bit(struct hi3630_asp_irq *irq,
				   unsigned int reg, unsigned int offset);
extern int hi3630_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream);
extern void hi3630_pcm_free_dma_buffers(struct snd_pcm *pcm);
extern void enable_srcup_interrupeter(bool enable);

static const struct snd_pcm_hardware hi3630_srcup_normal_hardware = {
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

static const struct of_device_id hi3630_srcup_normal_match[] = {
	{ .compatible = "hisilicon,hi3630-srcup-normal", },
	{},
};
MODULE_DEVICE_TABLE(of, hi3630_srcup_normal_match);

#ifdef SRCUP_ENABLE
static inline int hi3630_srcup_reg_read(struct hi3630_srcup_data *pdata, unsigned int reg)
{
	unsigned long flag = 0;
	int ret = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return ret;
	}

	ret = hi3630_asp_irq_read(pdata->hi3630_asp_irq, reg);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
	return ret;
}

static inline void hi3630_srcup_reg_write(struct hi3630_srcup_data *pdata,
					  unsigned int reg, unsigned int value)
{
	unsigned long flag = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	hi3630_asp_irq_write(pdata->hi3630_asp_irq, reg, value);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
}

static inline void hi3630_srcup_set_bit(struct hi3630_srcup_data *pdata,
					unsigned int reg, unsigned int offset)
{
	unsigned long flag = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	hi3630_asp_irq_set_bit(pdata->hi3630_asp_irq, reg, offset);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
}

static inline void hi3630_srcup_clr_bit(struct hi3630_srcup_data *pdata,
					unsigned int reg, unsigned int offset)
{
	unsigned long flag = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	hi3630_asp_irq_clr_bit(pdata->hi3630_asp_irq, reg, offset);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
}

static inline void hi3630_srcup_enable_dma(struct hi3630_srcup_data *pdata, unsigned int dma_ch)
{
	hi3630_srcup_set_bit(pdata, HI3630_SRCUP_CH_DMA_EN_REG, dma_ch);
}

static void config_srcup_dma(struct hi3630_srcup_runtime_data *prtd,
			     unsigned int dma_ch)
{
	struct hi3630_srcup_data *pdata = prtd->pdata;
	unsigned int addr = prtd->dma_addr + prtd->period_next * prtd->period_size;
	unsigned int size = prtd->period_size;

	switch (dma_ch) {
	case SRCUP_CH0_DMA_A:
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH0_A_ADDR_REG, addr);
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH0_A_LENGTH_REG, size);
		break;
	case SRCUP_CH0_DMA_B:
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH0_B_ADDR_REG, addr);
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH0_B_LENGTH_REG, size);
		break;
	default:
		loge("unknown src up dma ch: %d.\n", dma_ch);
		break;
	}
}

static irqreturn_t hi3630_intr_src_up_handle(int irq, void *dev_id)
{
	struct snd_pcm *pcm = dev_id;
	struct snd_pcm_substream *substream = NULL;
	struct snd_pcm_runtime *runtime = NULL;
	struct hi3630_srcup_runtime_data *prtd = NULL;
	struct hi3630_srcup_data *pdata = NULL;
	unsigned int rt_period_size = 0;
	unsigned int num_periods = 0;
	unsigned int irs = 0;
	unsigned int dma_cur = SRCUP_CH0_DMA_A;
	unsigned int dma_next = SRCUP_CH0_DMA_A;
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

	irs = hi3630_srcup_reg_read(pdata, HI3630_SRCUP_CH_INT_FLAG_REG) & SRCUP_CH0_MASK;

	if (0 == irs) {
		/* when hifi dsp playback is enable, it will go to here */
		return IRQ_HANDLED;
	}

	spin_lock(&prtd->lock);
	prtd->period_cur = (prtd->period_cur + 1) % num_periods;
	spin_unlock(&prtd->lock);

	snd_pcm_period_elapsed(substream);

	spin_lock(&prtd->lock);

	if (STATUS_SRCUP_STOP == prtd->status) {
		logd("stop dma, irs = %#x\n", irs);

		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_INT_FLAG_REG, irs);
		spin_unlock(&prtd->lock);
		return IRQ_HANDLED;
	}

	if (0 != ((1 << SRCUP_CH0_DMA_A) & irs)) {
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_INT_FLAG_REG, SRCUP_CH0_DMA_A_MASK);
		dma_cur = SRCUP_CH0_DMA_A;
		dma_next = SRCUP_CH0_DMA_B;
	} else {
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_INT_FLAG_REG, SRCUP_CH0_DMA_B_MASK);
		dma_cur = SRCUP_CH0_DMA_B;
		dma_next = SRCUP_CH0_DMA_A;
	}

	avail = snd_pcm_playback_hw_avail(runtime);

	if (avail < rt_period_size) {
		logd("Run out of data\n");
		prtd->two_dma_flag = false;
	} else {
		/* config & enable DMA */
		config_srcup_dma(prtd, dma_cur);
		hi3630_srcup_enable_dma(pdata, dma_cur);
		prtd->period_next = (prtd->period_next + 1) % num_periods;
		if ((!prtd->two_dma_flag) && (avail >= rt_period_size * 2)) {
			/* config & enable DMA */
			config_srcup_dma(prtd, dma_next);
			hi3630_srcup_enable_dma(pdata, dma_next);
			prtd->period_next = (prtd->period_next + 1) % num_periods;
			prtd->two_dma_flag = true;
		}
	}

	spin_unlock(&prtd->lock);

	return IRQ_HANDLED;
}
#endif

static int hi3630_srcup_normal_open(struct snd_pcm_substream *substream)
{
	struct hi3630_srcup_runtime_data *prtd = NULL;
	struct snd_soc_pcm_runtime *rtd = NULL;
	struct hi3630_srcup_data *pdata = NULL;
	struct snd_pcm *pcm = substream->pcm;
	int ret = 0;

	BUG_ON(NULL == pcm);

	prtd = kzalloc(sizeof(struct hi3630_srcup_runtime_data), GFP_KERNEL);
	if (NULL == prtd) {
		loge("kzalloc hi3630_srcup_runtime_data error!\n");
		return -ENOMEM;
	}

	mutex_init(&prtd->mutex);
	spin_lock_init(&prtd->lock);

	rtd = (struct snd_soc_pcm_runtime *)substream->private_data;
	pdata = (struct hi3630_srcup_data *)snd_soc_platform_get_drvdata(rtd->platform);

	BUG_ON(NULL == pdata);

	prtd->pdata = pdata;

	substream->runtime->private_data = prtd;

#ifdef SRCUP_ENABLE
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_get_sync(pdata->dev);
#else
	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret) {
		loge("couldn't enable regulators %d\n", ret);
		goto err_bulk;
	}
#endif

	srcup_module_enable(true);

	ret = request_irq(pdata->irq, hi3630_intr_src_up_handle,
			  IRQF_SHARED, "asp_irq_srcup_normal", pcm);
	if (0 > ret) {
		loge("request irq error, error No. = %d\n", ret);
		goto err_irq;
	}

	enable_srcup_interrupeter(true);
#endif

	ret = snd_soc_set_runtime_hwparams(substream, &hi3630_srcup_normal_hardware);

	return ret;

#ifdef SRCUP_ENABLE
err_irq:
	srcup_module_enable(false);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
#else
	regulator_bulk_disable(1, &prtd->pdata->regu);
err_bulk:
#endif
	kfree(prtd);
	return ret;
#endif
}

static int hi3630_srcup_normal_close(struct snd_pcm_substream *substream)
{
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;

	if (NULL == prtd) {
		loge("prtd is NULL\n");
	} else {
#ifdef SRCUP_ENABLE
		BUG_ON(NULL == prtd->pdata);
		free_irq(prtd->pdata->irq, substream->pcm);
		enable_srcup_interrupeter(false);
		srcup_module_enable(false);

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

#ifdef SRCUP_ENABLE
static int hi3630_srcup_normal_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *params)
{
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_srcup_data *pdata = prtd->pdata;
	unsigned long bytes = params_buffer_bytes(params);
	unsigned int params_value = 0;
	unsigned int channels = 0;
	unsigned int format = 0;
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

		params_value = params_format(params);
		/* check formats */
		switch (params_value) {
		case SNDRV_PCM_FORMAT_S16_BE :
			format |= SRCUP_BIG_DIAN_BIT;
			/* fallthrough */
		case SNDRV_PCM_FORMAT_S16_LE :
			if (2 == channels)
				format |= STEREO_16BIT;
			else
				format |= MONO_16BIT;
			break;
		default :
			loge("format err : %d, not support\n", params_value);
			ret = -EINVAL;
			goto err_out;
		}

		format |= SRCUP_CH0_HLC;

		mutex_lock(&prtd->mutex);
		prtd->period_size = params_period_bytes(params);
		mutex_unlock(&prtd->mutex);

		/*output format 24bit, single req mode*/
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_SINGLE_REQ_MODE_REG, SRCUP_OUT_FORMT_24BIT |
					SRCUP_STEREO_DATA | SRCUP_SINGLE_REQ_MODE);

		/*channel ctrl*/
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH0_CTRL_REG, format);

err_out:
		if (0 > ret) {
			loge("hw params error, ret : %d\n", ret);
			snd_pcm_lib_free_pages(substream);
		}
	}

	return ret;
}

static int hi3630_srcup_normal_hw_free(struct snd_pcm_substream *substream)
{
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_srcup_data *pdata = prtd->pdata;
	int ret = 0;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		/* clear interrupt */
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_INT_FLAG_REG, SRCUP_CH0_MASK);

		ret = snd_pcm_lib_free_pages(substream);
	}

	snd_pcm_set_runtime_buffer(substream, NULL);

	return ret;
}

static int hi3630_srcup_normal_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_srcup_data *pdata = prtd->pdata;
	unsigned int num_periods = substream->runtime->periods;

	mutex_lock(&prtd->mutex);

	prtd->status = STATUS_SRCUP_STOP;
	prtd->two_dma_flag = true;
	prtd->period_next = 0;
	prtd->period_cur = 0;
	prtd->dma_addr = runtime->dma_addr;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		/* config DMA CH_A */
		config_srcup_dma(prtd, SRCUP_CH0_DMA_A);
		prtd->period_next = (prtd->period_next + 1) % num_periods;
		/* config DMA CH_B */
		config_srcup_dma(prtd, SRCUP_CH0_DMA_B);
		prtd->period_next = (prtd->period_next + 1) % num_periods;

		/*clear interrupt*/
		hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_INT_FLAG_REG, SRCUP_CH0_MASK);
	}

	mutex_unlock(&prtd->mutex);

	return 0;
}

static int hi3630_srcup_normal_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;
	struct hi3630_srcup_data *pdata = prtd->pdata;
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			prtd->status = STATUS_SRCUP_RUNNING;
			hi3630_srcup_enable_dma(pdata, SRCUP_CH0_DMA_A);
			hi3630_srcup_enable_dma(pdata, SRCUP_CH0_DMA_B);
			hi3630_srcup_set_bit(pdata, HI3630_SRCUP_MIX_CTRL_REG, SRCUP_CH0);
			/* int enable */
			hi3630_srcup_set_bit(pdata, HI3630_SRCUP_CH_INTEN_REG, SRCUP_CH0_A_FINISH_EN_BIT);
			hi3630_srcup_set_bit(pdata, HI3630_SRCUP_CH_INTEN_REG, SRCUP_CH0_B_FINISH_EN_BIT);
		}
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			prtd->status = STATUS_SRCUP_STOP;
			/* int disable */
			hi3630_srcup_clr_bit(pdata, HI3630_SRCUP_CH_INTEN_REG, SRCUP_CH0_A_FINISH_EN_BIT);
			hi3630_srcup_clr_bit(pdata, HI3630_SRCUP_CH_INTEN_REG, SRCUP_CH0_B_FINISH_EN_BIT);
			/* clear mix ctl */
			hi3630_srcup_clr_bit(pdata, HI3630_SRCUP_MIX_CTRL_REG, SRCUP_CH0);
			/* stop srcup dma */
			hi3630_srcup_reg_write(pdata, HI3630_SRCUP_CH_STP_REG, SRCUP_CH0_STP);
			/* channel clear */
			hi3630_srcup_set_bit(pdata, HI3630_SRCUP_CH_CLEAR_REG, SRCUP_CH0_CLEAR_BIT);
		}
		break;

	default:
		loge("error!");
		ret = -EINVAL;
		break;
	}

	return ret;
}

static snd_pcm_uframes_t hi3630_srcup_normal_pointer(struct snd_pcm_substream *substream)
{
	snd_pcm_uframes_t offset = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_srcup_runtime_data *prtd = substream->runtime->private_data;
	unsigned int period_cur = 0;
	unsigned int period_size = 0;

	spin_lock(&prtd->lock);
	period_cur = prtd->period_cur;
	period_size = prtd->period_size;
	spin_unlock(&prtd->lock);

	offset = bytes_to_frames(runtime, period_cur * period_size);
	if (offset >= runtime->buffer_size)
		offset = 0;

	return offset;
}

static int hi3630_srcup_normal_mmap(struct snd_pcm_substream *substream,
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
#endif

static struct snd_pcm_ops hi3630_srcup_normal_ops = {
	.open		= hi3630_srcup_normal_open,
	.close		= hi3630_srcup_normal_close,
	.ioctl		= snd_pcm_lib_ioctl,
#ifdef SRCUP_ENABLE
	.hw_params	= hi3630_srcup_normal_hw_params,
	.hw_free	= hi3630_srcup_normal_hw_free,
	.prepare	= hi3630_srcup_normal_prepare,
	.trigger	= hi3630_srcup_normal_trigger,
	.pointer	= hi3630_srcup_normal_pointer,
	.mmap		= hi3630_srcup_normal_mmap,
#endif
};

static unsigned long long hi3630_pcm_dmamask = DMA_BIT_MASK(32);

static int hi3630_srcup_normal_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm  *pcm  = rtd->pcm;
	struct hi3630_srcup_data *pdata =
		(struct hi3630_srcup_data *)snd_soc_platform_get_drvdata(rtd->platform);
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

static void hi3630_srcup_normal_free(struct snd_pcm *pcm)
{
	BUG_ON(NULL == pcm);

	hi3630_pcm_free_dma_buffers(pcm);
}

static struct snd_soc_platform_driver hi3630_srcup_normal_platform = {
	.ops		= &hi3630_srcup_normal_ops,
	.pcm_new	= hi3630_srcup_normal_new,
	.pcm_free	= hi3630_srcup_normal_free,
};

static int hi3630_srcup_normal_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;
	struct hi3630_srcup_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "cannot allocate hi3630 srcup platform data\n");
		return -ENOMEM;
	}

	pdata->dev = dev;

#ifdef SRCUP_ENABLE
	pdata->hi3630_asp_irq = dev_get_drvdata(pdev->dev.parent);
	if (!pdata->hi3630_asp_irq) {
		dev_err(dev, "get parent device error\n");
		return -ENOENT;
	}

	pdata->irq = platform_get_irq_byname(pdev, "asp_srcup_normal");
	if (0 > pdata->irq) {
		dev_err(dev, "cannot get irq\n");
		return -ENOENT;
	}

	pdata->regu.supply = "asp-srcup-normal";
	ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu));
	if (0 != ret) {
		dev_err(dev, "couldn't get regulators %d\n", ret);
		return -ENOENT;
	}

	pdata->hwlock = hwspin_lock_request_specific(HWLOCK_ID);
	if(NULL == pdata->hwlock) {
		dev_err(dev, "couldn't request hwlock:%d\n", HWLOCK_ID);
		return -ENOENT;
	}

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms*/
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif
#endif
	platform_set_drvdata(pdev, pdata);

	dev_set_name(dev, "hi3630-srcup-normal");

	ret = snd_soc_register_platform(dev, &hi3630_srcup_normal_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n", ret);
		return -ENODEV;
	}

	return ret;
}

static int hi3630_srcup_normal_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
#ifdef SRCUP_ENABLE
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
#endif
	return 0;
}

#ifdef SRCUP_ENABLE
#ifdef CONFIG_PM_RUNTIME
int hi3630_srcup_normal_runtime_suspend(struct device *dev)
{
	struct hi3630_srcup_data *pdata = dev_get_drvdata(dev);

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	regulator_bulk_disable(1, &pdata->regu);

	dev_info(dev, "%s-", __FUNCTION__);

	return 0;
}

int hi3630_srcup_normal_runtime_resume(struct device *dev)
{
	struct hi3630_srcup_data *pdata = dev_get_drvdata(dev);
	int ret;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret)
		dev_err(dev, "couldn't enable regulators %d\n", ret);

	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_srcup_normal_pm_ops = {
	.runtime_suspend	= hi3630_srcup_normal_runtime_suspend,
	.runtime_resume		= hi3630_srcup_normal_runtime_resume,
};
#endif
#endif

static struct platform_driver hi3630_srcup_normal_driver = {
	.probe	= hi3630_srcup_normal_probe,
	.remove	= hi3630_srcup_normal_remove,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi3630-srcup-normal",
		.of_match_table = of_match_ptr(hi3630_srcup_normal_match),
#ifdef SRCUP_ENABLE
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_srcup_normal_pm_ops,
#endif
#endif
	},
};

module_platform_driver(hi3630_srcup_normal_driver);

MODULE_DESCRIPTION("ASoC hi3630 srcup normal driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
