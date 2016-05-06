/*
 * hi3630_asp_dmac.c -- ALSA SoC HI3630 ASP DMA driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "hi3630_asp_dmac"

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
#include <linux/hwspinlock.h>
#include <linux/pm_runtime.h>
#include <sound/core.h>
#include <sound/dmaengine_pcm.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>

#include "hi3630_log.h"
#include "hi3630_asp_dma.h"

#define HWLOCK_ID		2  /* hardware lock ID */
#define HWLOCK_WAIT_TIME	50 /* 50ms */

#undef CONFIG_PM_RUNTIME

struct hi3630_asp_dmac_data {
	struct hwspinlock *hwlock;
	struct resource	*res;
	void __iomem	*reg_base_addr;
	int		irq;
	spinlock_t 	lock;
	struct regulator_bulk_data	regu;
	struct device *dev;
};

enum hi3630_asp_dmac_status {
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

struct hi3630_asp_dmac_runtime_data {
	spinlock_t lock;
	struct hi3630_asp_dmac_data *pdata;
	struct mutex mutex;
	enum hi3630_asp_dmac_status status;
	bool two_dma_flag;
	unsigned int dma_addr;
	unsigned int period_size;
	unsigned int period_cur;
	unsigned int period_next;

	struct dma_lli_cfg *pdma_lli_cfg;
	unsigned int lli_dma_addr;
};

static const struct of_device_id hi3630_asp_dmac_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-pcm-asp-dma",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_asp_dmac_of_match);

static inline int hi3630_dmac_reg_read(struct hi3630_asp_dmac_data *pdata, unsigned int reg)
{
	unsigned long flag = 0;
	int ret = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return ret;
	}

	ret = readl_relaxed(pdata->reg_base_addr + reg);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
	return ret;
}

static inline void hi3630_dmac_reg_write(struct hi3630_asp_dmac_data *pdata,
					 unsigned int reg, unsigned int value)
{
	unsigned long flag = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	writel_relaxed(value, pdata->reg_base_addr + reg);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag);
}

static inline void hi3630_dmac_set_bit(struct hi3630_asp_dmac_data *pdata,
				       unsigned int reg, unsigned int offset)
{
	unsigned int value = 0;
	unsigned long flag_hw = 0;
	unsigned long flag_sft = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag_hw)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	spin_lock_irqsave(&pdata->lock, flag_sft);
	value = readl_relaxed(pdata->reg_base_addr + reg);
	value |= (1 << offset);
	writel_relaxed(value, pdata->reg_base_addr + reg);
	spin_unlock_irqrestore(&pdata->lock, flag_sft);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag_hw);
}

static inline void hi3630_dmac_clr_bit(struct hi3630_asp_dmac_data *pdata,
				       unsigned int reg, unsigned int offset)
{
	unsigned int value = 0;
	unsigned long flag_hw = 0;
	unsigned long flag_sft = 0;

	BUG_ON(NULL == pdata);

	if (hwspin_lock_timeout_irqsave(pdata->hwlock, HWLOCK_WAIT_TIME, &flag_hw)) {
		loge("%s: hwspinlock timeout!\n", __func__);
		return;
	}

	spin_lock_irqsave(&pdata->lock, flag_sft);
	value = readl_relaxed(pdata->reg_base_addr + reg);
	value &= ~(1 << offset);
	writel_relaxed(value, pdata->reg_base_addr + reg);
	spin_unlock_irqrestore(&pdata->lock, flag_sft);

	hwspin_unlock_irqrestore(pdata->hwlock, &flag_hw);
}

static const struct snd_pcm_hardware hi3630_asp_dmac_hardware = {
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

int hi3630_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream)
{
	struct snd_pcm_substream *substream = pcm->streams[stream].substream;
	struct snd_dma_buffer *buf = &substream->dma_buffer;
	size_t size = hi3630_asp_dmac_hardware.buffer_bytes_max;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->private_data = NULL;
	buf->area = dma_alloc_coherent(pcm->card->dev, size,
					   &buf->addr, GFP_KERNEL);

	if (!buf->area) {
		loge("dma_alloc_writecombine error\n");
		return -ENOMEM;
	}

	buf->bytes = size;

	return 0;
}
EXPORT_SYMBOL(hi3630_pcm_preallocate_dma_buffer);

void hi3630_pcm_free_dma_buffers(struct snd_pcm *pcm)
{
	struct snd_pcm_substream *substream;
	struct snd_dma_buffer *buf;
	int stream;

	for (stream = 0; stream < 2; stream++) {
		substream = pcm->streams[stream].substream;
		if (!substream)
			continue;

		buf = &substream->dma_buffer;
		if (!buf->area)
			continue;

		dma_free_coherent(pcm->card->dev, buf->bytes,
				      buf->area, buf->addr);
		buf->area = NULL;
	}
}
EXPORT_SYMBOL(hi3630_pcm_free_dma_buffers);

/*
*dma operations
*
**/
static void asp_dma_init(struct hi3630_asp_dmac_data *pdata)
{
	/*clear interrupt*/
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_TC1_RAW_REG,  CH_0_INT_CLR);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_TC2_RAW_REG,  CH_0_INT_CLR);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR1_RAW_REG, CH_0_INT_CLR);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR2_RAW_REG, CH_0_INT_CLR);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR3_RAW_REG, CH_0_INT_CLR);

	/*dma ch unmask*/
	hi3630_dmac_set_bit(pdata, HI3630_DMAC_INT_TC1_MASK_0_REG , CH_0_UNMASK_BIT);
	hi3630_dmac_set_bit(pdata, HI3630_DMAC_INT_TC2_MASK_0_REG , CH_0_UNMASK_BIT);
	hi3630_dmac_set_bit(pdata, HI3630_DMAC_INT_ERR1_MASK_0_REG , CH_0_UNMASK_BIT);
	hi3630_dmac_set_bit(pdata, HI3630_DMAC_INT_ERR2_MASK_0_REG , CH_0_UNMASK_BIT);
	hi3630_dmac_set_bit(pdata, HI3630_DMAC_INT_ERR3_MASK_0_REG , CH_0_UNMASK_BIT);
}

/*dma config lli node*/
static void asp_dma_cfg(struct hi3630_asp_dmac_runtime_data *prtd)
{
	unsigned int sio_tx_dma_addr = BASE_ADDR_SIO_VOICE + HI3630_SIO_I2S_TX_CHN_REG;
	unsigned int next_addr = 0x0;
	unsigned int dma_lli_num = DMA_LLI_NUM;
	unsigned int i;

	memset(prtd->pdma_lli_cfg, 0, dma_lli_num * sizeof(struct dma_lli_cfg));

	for (i = 0; i < dma_lli_num; i++) {
		next_addr = (unsigned int)(prtd->lli_dma_addr + sizeof(struct dma_lli_cfg) * (i + 1));
		prtd->pdma_lli_cfg[i].lli = next_addr | DMA_LLI_ENABLE;
		prtd->pdma_lli_cfg[i].config = DMA_CONFIG;
		prtd->pdma_lli_cfg[i].des_addr = sio_tx_dma_addr;
	}

	prtd->pdma_lli_cfg[dma_lli_num - 1].lli = prtd->lli_dma_addr | DMA_LLI_ENABLE;
}

static void check_and_stop_rxdma(struct hi3630_asp_dmac_runtime_data *prtd)
{
	struct hi3630_asp_dmac_data *pdata;
	unsigned int lli_index = prtd->period_next % DMA_LLI_NUM;
	unsigned int der = 0;
	unsigned int irsr = 0;
	unsigned int i = 45;/* 1ms * 45; one buffer is about 20ms */

	pdata = prtd->pdata;

	do {
		der = hi3630_dmac_reg_read(pdata, HI3630_DMAC_CX_CONFIG_0_REG) & CH_0_UNMASK;
		irsr = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_STAT_0_REG) & CH_0_UNMASK;
		if (der | irsr) {
			prtd->pdma_lli_cfg[lli_index].lli= 0x0;
			usleep_range(HI3630_MIN_STOP_DMA_TIME_US, HI3630_MAX_STOP_DMA_TIME_US);
		} else {
			break;
		}
	} while(--i);

	hi3630_dmac_clr_bit(pdata, HI3630_DMAC_CX_CONFIG_0_REG, DMA_ENABLE_BIT);

	if (!i)
		loge("exit with der=%#x, irsr=%#x\n", der, irsr);
}

/*dma write first node to registers*/
static void asp_dma_set_first_node(struct hi3630_asp_dmac_runtime_data *prtd)
{
	struct hi3630_asp_dmac_data *pdata;
	struct dma_lli_cfg *lli_cfg = &prtd->pdma_lli_cfg[0];

	pdata = prtd->pdata;

	hi3630_dmac_reg_write(pdata, HI3630_DMAC_CX_LLI_0_REG, lli_cfg->lli);

	hi3630_dmac_reg_write(pdata, HI3630_DMAC_CX_CNT0_0_REG, lli_cfg->a_count);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_CX_SRC_ADDR_0_REG, lli_cfg->src_addr);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_CX_DES_ADDR_0_REG, lli_cfg->des_addr);
	hi3630_dmac_reg_write(pdata, HI3630_DMAC_CX_CONFIG_0_REG, lli_cfg->config);
}

static void asp_dma_set_lli_node(struct hi3630_asp_dmac_runtime_data *prtd,
				 unsigned int dma_lli_num, unsigned int dma_addr)
{
	unsigned int lli_index = prtd->period_next % dma_lli_num;
	prtd->pdma_lli_cfg[lli_index].src_addr = dma_addr + prtd->period_next * prtd->period_size;
	prtd->pdma_lli_cfg[lli_index].a_count = prtd->period_size;
}

static bool error_interrupt_handle(struct hi3630_asp_dmac_data *pdata)
{
	unsigned int irs_tmp = 0;
	unsigned int count = 0;

	// loge("%d in\n", __LINE__);
	/*dma config error interrupt*/
	irs_tmp = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_ERR1_0_REG) & CH_0_UNMASK;
	if (unlikely(0 != irs_tmp)) {
		loge("dmac ch0 interrupt config error happend!");
		hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR1_RAW_REG, CH_0_INT_CLR);
		count++;
	}

	/*dma transit error interrupt*/
	irs_tmp = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_ERR2_0_REG) & CH_0_UNMASK;
	if (unlikely(0 != irs_tmp)) {
		loge("dmac ch0 interrupt transit error happend!");
		hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR2_RAW_REG, CH_0_INT_CLR);
		count++;
	}

	/*dma lli transit, read lli error interrupt*/
	irs_tmp = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_ERR3_0_REG) & CH_0_UNMASK;
	if (unlikely(0 != irs_tmp)) {
		loge("dmac ch0 interrupt read lli error happend!");
		hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_ERR3_RAW_REG, CH_0_INT_CLR);
		count++;
	}

	if (unlikely(0 < count))
		return true;

	irs_tmp = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_TC1_0_REG) & CH_0_UNMASK;
	if (unlikely(0 != irs_tmp)) {
		logd("dmac ch0 transit finished!");
		hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_TC1_RAW_REG, CH_0_INT_CLR);
		return true;
	}

	/*dma lli transit finish interrupt*/
	irs_tmp = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_TC2_0_REG) & CH_0_UNMASK;
	if (likely(0 != irs_tmp)) {
		hi3630_dmac_reg_write(pdata, HI3630_DMAC_INT_TC2_RAW_REG, CH_0_INT_CLR);
	}

	return false;
}

static int hi3630_asp_dmac_hw_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *params)
{
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;
	unsigned long bytes = params_buffer_bytes(params);
	unsigned int lli_dma_addr = 0;
	int ret = 0;

	loge("%d in\n", __LINE__);
	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		ret = snd_pcm_lib_malloc_pages(substream, bytes);
		if (ret < 0) {
			loge("snd_pcm_lib_malloc_pages ret is %d", ret);
			return ret;
		}

		mutex_lock(&prtd->mutex);

		prtd->pdma_lli_cfg = (struct dma_lli_cfg *)dma_alloc_coherent(prtd->pdata->dev,
			DMA_LLI_NUM * sizeof(struct dma_lli_cfg), &lli_dma_addr, GFP_KERNEL);

		if (NULL == prtd->pdma_lli_cfg) {
			loge("prtd->pdma_lli_cfg dma alloc coherent error!");
			ret = -ENOMEM;
			goto err_out;
		}

		prtd->lli_dma_addr = lli_dma_addr;
		prtd->period_size = params_period_bytes(params);
		prtd->period_next = 0;

err_out:
		if (0 > ret) {
			loge("hw params error, ret : %d\n", ret);
			snd_pcm_lib_free_pages(substream);
		}

		mutex_unlock(&prtd->mutex);
	}

	return ret;
}

static int hi3630_asp_dmac_hw_free(struct snd_pcm_substream *substream)
{
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;
	int ret = 0;

	loge("%d in\n", __LINE__);
	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		check_and_stop_rxdma(prtd);

		dma_free_coherent(prtd->pdata->dev, DMA_LLI_NUM * sizeof(struct dma_lli_cfg),
				(void*)prtd->pdma_lli_cfg, prtd->lli_dma_addr);

		ret = snd_pcm_lib_free_pages(substream);
	}

	snd_pcm_set_runtime_buffer(substream, NULL);

	return ret;
}

static int hi3630_asp_dmac_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;
	unsigned int num_periods = substream->runtime->periods;

	loge("%d in\n", __LINE__);
	mutex_lock(&prtd->mutex);

	prtd->status = STATUS_DMAC_STOP;
	prtd->two_dma_flag = true;
	prtd->period_next = 0;
	prtd->period_cur = 0;
	prtd->dma_addr = runtime->dma_addr;

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		check_and_stop_rxdma(prtd);

		asp_dma_cfg(prtd);

		asp_dma_set_lli_node(prtd, DMA_LLI_NUM, runtime->dma_addr);
		prtd->period_next = (prtd->period_next + 1) % num_periods;

		asp_dma_set_lli_node(prtd, DMA_LLI_NUM, runtime->dma_addr);
		prtd->period_next = (prtd->period_next + 1) % num_periods;

		asp_dma_set_first_node(prtd);

		asp_dma_init(prtd->pdata);
	}

	mutex_unlock(&prtd->mutex);

	return 0;
}

static int hi3630_asp_dmac_trigger(struct snd_pcm_substream *substream, int cmd)
{
	int ret = 0;
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;

    loge("%d in cmd = %d \n", __LINE__,cmd);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			prtd->status = STATUS_DMAC_RUNNING;
			hi3630_dmac_set_bit(prtd->pdata,
					HI3630_DMAC_CX_CONFIG_0_REG, DMA_ENABLE_BIT);
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
			prtd->status = STATUS_DMAC_STOP;
		}
		break;
	default:
		loge("error!");
		ret = -EINVAL;
		break;
	}

	return ret;
}

static snd_pcm_uframes_t hi3630_asp_dmac_pointer(struct snd_pcm_substream *substream)
{
	snd_pcm_uframes_t offset = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;
	unsigned int period_cur = 0;
	unsigned int period_size = 0;

    //loge("%d in \n", __LINE__);
	spin_lock(&prtd->lock);
	period_cur = prtd->period_cur;
	period_size = prtd->period_size;
	spin_unlock(&prtd->lock);

	offset = bytes_to_frames(runtime, period_cur * period_size);

	if(offset >= runtime->buffer_size)
		offset = 0;

	return offset;
}

static int hi3630_asp_dmac_mmap(struct snd_pcm_substream *substream,
				struct vm_area_struct *vma)
{

    loge("%d in \n", __LINE__);
	int ret = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (NULL != runtime){
		ret = dma_mmap_writecombine(substream->pcm->card->dev,
				vma,
				runtime->dma_area,
				runtime->dma_addr,
				runtime->dma_bytes);
         loge("%d dma_mmap_writecombine \n", __LINE__);
    }

	return ret;
}

static irqreturn_t hi3630_intr_dmac_handle(int irq, void *dev_id)
{
	struct snd_pcm *pcm = dev_id;
	struct snd_pcm_substream *substream = NULL;
	struct snd_pcm_runtime *runtime = NULL;
	struct hi3630_asp_dmac_runtime_data *prtd = NULL;
	snd_pcm_uframes_t avail = 0;
	unsigned int irs_stat = 0;
	unsigned int rt_period_size = 0;
	unsigned int num_period = 0;
	struct hi3630_asp_dmac_data *pdata = NULL;

  BUG_ON(NULL == pcm);
	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	if (NULL == substream) {
		loge("substream is NULL\n");
		return IRQ_HANDLED;
	}

		loge("=======hi3630_intr_dmac_handle========= \n");
		
	runtime = substream->runtime;
	BUG_ON(NULL == runtime);
	prtd = runtime->private_data;
	BUG_ON(NULL == prtd);
	pdata = prtd->pdata;
	BUG_ON(NULL == pdata);

	/*dma transit state*/
	irs_stat = hi3630_dmac_reg_read(pdata, HI3630_DMAC_INT_STAT_0_REG) & CH_0_UNMASK;
	if (0 == irs_stat) {
		/* when hifi dsp is incall, it will go to here */
		return IRQ_NONE;
	}

	if (error_interrupt_handle(pdata)) {
		return IRQ_HANDLED;
	}

	rt_period_size = runtime->period_size;
	num_period = runtime->periods;

	spin_lock(&prtd->lock);
	prtd->period_cur = (prtd->period_cur + 1) % num_period;
	spin_unlock(&prtd->lock);

	snd_pcm_period_elapsed(substream);

	spin_lock(&prtd->lock);

	/* DMA IS STOPPED */
	if (STATUS_DMAC_STOP == prtd->status) {
		logd("dma stop.\n");
		prtd->pdma_lli_cfg[(prtd->period_next) % DMA_LLI_NUM].lli= 0x0;
		spin_unlock(&prtd->lock);
		return IRQ_HANDLED;
	}

	avail = snd_pcm_capture_hw_avail(runtime);

	if(avail < rt_period_size) {
		if (prtd->two_dma_flag) {
			prtd->two_dma_flag = false;
			logw("Run out of data in one DMA, disable one DMA\n");
		} else {
			logw("Run out of data in both DMAs, disable both DMAs\n");
		}
		spin_unlock(&prtd->lock);
		return IRQ_HANDLED;
	} else {
		asp_dma_set_lli_node(prtd, DMA_LLI_NUM, runtime->dma_addr);
		prtd->period_next = (prtd->period_next + 1) % num_period;

		if ((!prtd->two_dma_flag) && (avail >= rt_period_size * 2 )) {
			logd("enable both DMAs\n");
			prtd->two_dma_flag = true;

			asp_dma_set_lli_node(prtd, DMA_LLI_NUM, runtime->dma_addr);
			prtd->period_next = (prtd->period_next + 1) % num_period;
		}
	}

	spin_unlock(&prtd->lock);
	return IRQ_HANDLED;
}

static int hi3630_asp_dmac_open(struct snd_pcm_substream *substream)
{
	struct hi3630_asp_dmac_runtime_data *prtd = NULL;
	struct snd_soc_pcm_runtime *rtd = NULL;
	struct hi3630_asp_dmac_data *pdata = NULL;
	struct snd_pcm *pcm = substream->pcm;
	int ret = 0;

	loge("%d in\n", __LINE__);
	prtd = kzalloc(sizeof(struct hi3630_asp_dmac_runtime_data), GFP_KERNEL);
	if (NULL == prtd) {
		loge("kzalloc hi3630_asp_dmac_runtime_data error!\n");
		return -ENOMEM;
	}

	mutex_init(&prtd->mutex);
	spin_lock_init(&prtd->lock);

	rtd = (struct snd_soc_pcm_runtime *)substream->private_data;
	pdata = (struct hi3630_asp_dmac_data *)snd_soc_platform_get_drvdata(rtd->platform);

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

	ret = request_irq(pdata->irq, hi3630_intr_dmac_handle,
			  IRQF_SHARED, "asp_dma_irq", pcm);
	if (0 > ret) {
		loge("request irq error, error No. = %d\n", ret);
		goto err_irq;
	}
	loge("request_irq = %d,irq = %d \n", ret,pdata->irq);

	ret = snd_soc_set_runtime_hwparams(substream, &hi3630_asp_dmac_hardware);

	return ret;

err_irq:
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

static int hi3630_asp_dmac_close(struct snd_pcm_substream *substream)
{
	struct hi3630_asp_dmac_runtime_data *prtd = substream->runtime->private_data;

	loge("%d in\n", __LINE__);
	if (NULL == prtd) {
		loge("prtd is NULL\n");
	} else {
		BUG_ON(NULL == prtd->pdata);
		free_irq(prtd->pdata->irq, substream->pcm);
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

static struct snd_pcm_ops hi3630_asp_dmac_ops = {
	.open	    = hi3630_asp_dmac_open,
	.close	    = hi3630_asp_dmac_close,
	.ioctl      = snd_pcm_lib_ioctl,
	.hw_params  = hi3630_asp_dmac_hw_params,
	.hw_free    = hi3630_asp_dmac_hw_free,
	.prepare    = hi3630_asp_dmac_prepare,
	.trigger    = hi3630_asp_dmac_trigger,
	.pointer    = hi3630_asp_dmac_pointer,
	.mmap       = hi3630_asp_dmac_mmap,
};

static unsigned long long hi3630_pcm_dmamask = DMA_BIT_MASK(32);

static int hi3630_asp_dmac_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm  *pcm  = rtd->pcm;
	struct hi3630_asp_dmac_data *pdata =
		(struct hi3630_asp_dmac_data *)snd_soc_platform_get_drvdata(rtd->platform);
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
			loge("preallocate dma for dmac error(%d)\n", ret);
			hi3630_pcm_free_dma_buffers(pcm);
			return ret;
		}
	}

	return ret;
}

static void hi3630_asp_dmac_free(struct snd_pcm *pcm)
{
	BUG_ON(NULL == pcm);

	hi3630_pcm_free_dma_buffers(pcm);
}

static struct snd_soc_platform_driver hi3630_pcm_asp_dmac_platform = {
	.ops		= &hi3630_asp_dmac_ops,
	.pcm_new	= hi3630_asp_dmac_new,
	.pcm_free	= hi3630_asp_dmac_free,
};

static int hi3630_asp_dmac_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct device *dev = &pdev->dev;
	struct hi3630_asp_dmac_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "cannot allocate hi3630 asp dma platform data\n");
		return -ENOMEM;
	}

	/* get resources */
	pdata->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pdata->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	if (!devm_request_mem_region(dev, pdata->res->start,
				     resource_size(pdata->res),
				     pdev->name)) {
		dev_err(dev, "cannot claim register memory\n");
		return -ENOMEM;
	}

	pdata->reg_base_addr = devm_ioremap(dev, pdata->res->start,
					    resource_size(pdata->res));
	if (!pdata->reg_base_addr) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}

	pdata->irq = platform_get_irq_byname(pdev, "asp_dma_irq");
	if (0 > pdata->irq) {
		dev_err(dev, "cannot get irq\n");
		return -ENOENT;
	}
	pdata->regu.supply = "asp-dmac";
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

	spin_lock_init(&pdata->lock);

	pdata->dev = dev;

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms*/
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif

	platform_set_drvdata(pdev, pdata);

	dev_set_name(dev, "hi3630-pcm-asp-dma");

	ret = snd_soc_register_platform(dev, &hi3630_pcm_asp_dmac_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n" ,ret);
		return -ENODEV;
	}

	return 0;
}

static int hi3630_asp_dmac_remove(struct platform_device *pdev)
{
	snd_soc_unregister_platform(&pdev->dev);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
	return 0;
}

#ifdef CONFIG_PM_RUNTIME
int hi3630_asp_dmac_runtime_suspend(struct device *dev)
{
	struct hi3630_asp_dmac_data *pdata = dev_get_drvdata(dev);

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	regulator_bulk_disable(1, &pdata->regu);

	dev_info(dev, "%s-", __FUNCTION__);

	return 0;
}

int hi3630_asp_dmac_runtime_resume(struct device *dev)
{
	struct hi3630_asp_dmac_data *pdata = dev_get_drvdata(dev);
	int ret;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	ret = regulator_bulk_enable(1, &pdata->regu);
	if (0 != ret)
		dev_err(dev, "couldn't enable regulators %d\n", ret);

	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_asp_dmac_pm_ops = {
	.runtime_suspend	= hi3630_asp_dmac_runtime_suspend,
	.runtime_resume		= hi3630_asp_dmac_runtime_resume,
};
#endif

static struct platform_driver hi3630_asp_dmac_driver = {
	.driver = {
		.name	= "hi3630-pcm-asp-dma",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_asp_dmac_of_match,
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_asp_dmac_pm_ops,
#endif
	},
	.probe	= hi3630_asp_dmac_probe,
	.remove	= hi3630_asp_dmac_remove,
};
module_platform_driver(hi3630_asp_dmac_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 ASP DMA Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi3630_asp_dmac");
