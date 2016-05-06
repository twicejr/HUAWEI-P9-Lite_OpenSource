/*
*Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*/

#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/compiler.h>
#include <linux/regulator/consumer.h>
#include <linux/pm_runtime.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/dma-mapping.h>
#include <linux/input.h>
#include <linux/wakelock.h>
#include <linux/clk.h>
#include <linux/hwspinlock.h>
#include <linux/semaphore.h>

#include <sound/core.h>
#include <sound/dmaengine_pcm.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>
#include <sound/jack.h>

#include "mlib_static_ringbuffer.h"
#include "soundtrigger_dma_drv.h"
#include "soundtrigger_log.h"
#include "slimbus.h"

#define DRV_NAME									"soundtrigger_dma_drv"

#define COMP_SOUNDTRIGGER_DMA_DRV_NAME				"hisilicon,soundtrigger_dma_drv"

#define SOUNDTRIGGER_HWLOCK_ID						(5)

#define HISILICON_SOUNDTRIGGER_DMA_DRIVER_VERSION	"1.0"

#define MAX_MSG_SIZE			(1024)

#define RINGBUFFER_SIZE 		(61440) 									/* accoring to 6402 ringbuffer size, which will be totally transmited to AP */

#define FAST_FRAME_LENGTH		(1920)										/* time: 10ms */

#define FAST_TRAN_RATE			(192000)

#define NORMAL_FRAME_LENGTH 	(160)										/* time: 10ms */

#define NORMAL_TRAN_RATE		(16000)

#define BYTE_COUNT				(4) 										/* each sampling point has 4 bytes */

#define VALID_BYTE_COUNT		(2) 										/* each sampling point only has 2 bytes valid data */

#define FAST_HEAD_FRAME_COUNT	(1) 										/* head frame count of fast channel, which is full of 0x5A5A */

#define FAST_TAIL_FRAME_COUNT	(1) 										/* tail  frame count of fast channel, which is full of 0x5A5A */

#define NORMAL_HEAD_FRAME_COUNT (2) 										/* head frame count of normal channel, which is full of 0x5A5A */

#define FAST_TRAN_COUNT 		(RINGBUFFER_SIZE / (FAST_FRAME_LENGTH * VALID_BYTE_COUNT) + FAST_HEAD_FRAME_COUNT + FAST_TAIL_FRAME_COUNT)	/* 16 + 2=18 */

#define FAST_BUFFER_SIZE		(FAST_FRAME_LENGTH * VALID_BYTE_COUNT * FAST_TRAN_COUNT)													/* 1920x2x18=69120 */

#define HEAD_FRAME_WORD 		(0x5A5A)																									/* key word that fill with head/tail frame */

#define NORMAL_BUFFER_SIZE		(320 * 200 + 20)																							/* according to mlib_ringbuffer.c */

//#define STEREO_TYPE
#ifdef STEREO_TYPE
	#define DMA_PORT_NUM		(2)
#else
	#define DMA_PORT_NUM		(1)
#endif

typedef struct
{
	uint32_t  port; 		/* slimbus port address */
	uint32_t  config;		/* dma config number */
	uint32_t  channel;		/* dma channel number */
}DRV_DMA_CONFIG_STRU;

struct dma_lli_cfg {
	uint32_t lli;
	uint32_t reserved[3];
	uint32_t a_count;
	uint32_t src_addr;
	uint32_t des_addr;
	uint32_t config;
} __aligned(32);

struct soundtrigger_pcm_config {
	uint32_t channels;		/* stereo type: channel = 2, mono type: channel = 1 */
	uint32_t rate;			/* sampling rate */
	uint32_t frame_len; 	/* frame length */
	uint32_t byte_count;	/* each sampling point contain byte number	*/
};

struct soundtrigger_pcm_info {
	struct soundtrigger_pcm_config	pcm_cfg;
	void							*buffer[DMA_PORT_NUM][PCM_SWAP_BUFFER_NUM]; 				/* swap buffer */
	dma_addr_t						buffer_physical_addr[DMA_PORT_NUM][PCM_SWAP_BUFFER_NUM];	/* swap buffer physical addr */
	uint32_t						buffer_size;												/* one swap buffer size, each sampling point contains 4 bytes */
	uint32_t						channel[DMA_PORT_NUM];										/* dma channel number */
	struct dma_lli_cfg				*dma_cfg[DMA_PORT_NUM][PCM_SWAP_BUFFER_NUM];
	dma_addr_t						lli_dma_physical_addr[DMA_PORT_NUM][PCM_SWAP_BUFFER_NUM];
};

struct fast_tran_info {
	uint32_t	fast_frame_find_flag;			/* flag to decide whether get first frame; before first frame, all input data is unuse */
	uint32_t	fast_start_addr;				/* address of valid data in the first frame */
	uint16_t	fast_head_frame_word;			/* word of head frame which is full of unuse data, such as 0x5A5A */
	uint32_t	fast_head_frame_size;
	uint16_t	*fast_buffer;					/* buffer to store all fast transmit data, including head frame */
	uint32_t	fast_buffer_size;
	int32_t 	dma_tran_count; 				/* tnumber of valid fast transmission */
	int32_t 	dma_tran_total_count;			/* total number of fast transmit */
	int32_t 	fast_complete_flag; 			/* fast tansmit complete flag */
	int32_t 	fast_read_complete_flag;		/* flag to decide whether HAL read cpmlete */
	uint32_t	irq_count_left; 				/* left channel interrupt count */
	uint32_t	irq_count_right;				/* left channel interrupt count */
	uint32_t	read_count_left;				/* left channel read count */
	uint32_t	read_count_right;				/* right channel read count */
};

struct normal_tran_info {
	uint32_t	normal_frame_find_flag; 		/* flag to decide whether get first frame; before first frame, all input data is unuse */
	uint32_t	normal_start_addr;				/* address of valid data in the first frame */
	uint32_t	normal_first_frame_read_flag;	/* flag to decide whether HAL read first frame */
	uint16_t	normal_head_frame_word; 		/*word of head frame which is full of unuse data, such as 0xA5A5 */
	uint32_t	normal_head_frame_size;
	uint16_t	*normal_buffer; 				/* ringbuffer which stores normal transmit data , including head frame */
	uint32_t	normal_buffer_size;
	uint32_t	normal_tran_count;				/* tnumber of valid normal transmission */
	uint32_t	irq_count_left; 				/* left channel interrupt count */
	uint32_t	irq_count_right;				/* left channel interrupt count */
	uint32_t	read_count_left;				/* left channel read count */
	uint32_t	read_count_right;				/* right channel read count */
};

struct soundtrigger_dma_drv_info {
	struct hwspinlock	*hwlock;
	spinlock_t			lock;
	struct resource 	*res;
	void __iomem		*reg_base_addr;
	void __iomem		*v_slimbus_base_reg_addr;
	int32_t 			irq;
	struct regulator	*asp_ip;
	struct device		*dev;
	uint32_t			dma_int_fast_flag;
	uint32_t			dma_int_nomal_flag;
	uint32_t			dma_alloc_flag;
	uint32_t			soundtrigger_dma_drv_state;
	int32_t 			fm_status;
	struct clk *asp_subsys_clk;
	struct soundtrigger_pcm_info	st_pcm_info[SOUNDTRIGGER_PCM_CHAN_NUM];
	struct fast_tran_info			st_fast_tran_info;
	struct normal_tran_info 		st_normal_tran_info;

	struct workqueue_struct 		*soundtrigger_delay_wq;
	struct delayed_work 			soundtrigger_delay_dma_fast_left_work;		/* delay work of interrupt response for fast transmit left channel */
	struct delayed_work 			soundtrigger_delay_dma_fast_right_work; 	/* delay work of interrupt response for fast transmit right channel */
	struct delayed_work 			soundtrigger_delay_dma_normal_left_work;	/* delay work of interrupt response for normal transmit left channel */
	struct delayed_work 			soundtrigger_delay_dma_normal_right_work;	/* delay work of interrupt response for normal transmit right channel */
};


DRV_DMA_CONFIG_STRU g_soundtrigger_dma_fast_cfg[2] = {
	{.port = 0xe8051180, .config = 0x43322067, .channel = 7},	/*fast data left channel*/
	{.port = 0xe80511c0, .config = 0x43322077, .channel = 8},	/*fast data right channel*/
};

DRV_DMA_CONFIG_STRU g_soundtrigger_dma_normal_cfg[2] = {
	{.port = 0xe8051280, .config = 0x433220a7, .channel = 3},	/*normal data left channel*/
	{.port = 0xe80512c0, .config = 0x433220b7, .channel = 4},	/*normal data right channel*/
};

struct soundtrigger_pcm_config g_pcm_fast_cfg= {				/*fast trans pcm config*/
	.channels = DMA_PORT_NUM,
	.rate = FAST_TRAN_RATE,
	.frame_len = FAST_FRAME_LENGTH,
	.byte_count = BYTE_COUNT,
};

struct soundtrigger_pcm_config g_pcm_normal_cfg= {				/*normal trans pcm config*/
	.channels = DMA_PORT_NUM,
	.rate = NORMAL_TRAN_RATE,
	.frame_len = NORMAL_FRAME_LENGTH,
	.byte_count = BYTE_COUNT,
};

struct soundtrigger_dma_drv_info *g_dma_drv_info = NULL;

static irqreturn_t soundtrigger_dmac_irq_handler(int32_t irq, void *dev_id);

static int get_input_param(unsigned int usr_para_size,
				  void __user *usr_para_addr,
				  unsigned int *krn_para_size,
				  void **krn_para_addr)
{
	void *para_in = NULL;
	unsigned int para_size_in = 0;

	if (!usr_para_addr) {
		loge("usr_para_addr NULL.\n");
		goto ERR;
	}

	if ((usr_para_size == 0) || (usr_para_size > MAX_MSG_SIZE)) {
		loge("usr_para_size invalid %d, max %d.\n", usr_para_size, MAX_MSG_SIZE);
		goto ERR;
	}

	para_size_in = roundup(usr_para_size, 4);

	para_in = kzalloc(para_size_in, GFP_KERNEL);
	if (para_in == NULL) {
		loge("kzalloc fail\n");
		goto ERR;
	}

	if (copy_from_user(para_in , (void __user *)usr_para_addr, usr_para_size)) {
		loge("copy_from_user fail\n");
		goto ERR;
	}

	*krn_para_size = para_size_in;
	*krn_para_addr = para_in;

	return 0;

ERR:
	if (para_in) {
		kfree(para_in);
		para_in = NULL;
	}
	return -EIO;
}

static void param_free(void **krn_para_addr)
{
	if (*krn_para_addr) {
		kfree(*krn_para_addr);
		*krn_para_addr = NULL;
	} else {
		loge("krn_para_addr to free is NULL\n");
	}

	return;
}

static inline int32_t slimbus_register_read(struct soundtrigger_dma_drv_info *dma_drv_info,uint32_t reg)
{
	unsigned long flag = 0;
	int32_t ret = 0;

	BUG_ON(NULL == dma_drv_info);

	if (hwspin_lock_timeout_irqsave(dma_drv_info->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("hwspinlock timeout\n");
		return 0;
	}

	ret = readl(dma_drv_info->v_slimbus_base_reg_addr + reg);

	hwspin_unlock_irqrestore(dma_drv_info->hwlock, &flag);
	return ret;
}

static inline int32_t dmac_register_read(struct soundtrigger_dma_drv_info *dma_drv_info, uint32_t reg)
{
	long unsigned int flag = 0;
	int32_t ret = 0;

	BUG_ON(NULL == dma_drv_info);

	if (hwspin_lock_timeout_irqsave(dma_drv_info->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("hwspinlock timeout\n");
		return 0;
	}

	ret = readl(dma_drv_info->reg_base_addr + reg);
	hwspin_unlock_irqrestore(dma_drv_info->hwlock, &flag);
	return ret;
}

static inline void dmac_register_write(struct soundtrigger_dma_drv_info *dma_drv_info,
	uint32_t reg, uint32_t value)
{
	long unsigned int flag = 0;

	BUG_ON(NULL == dma_drv_info);

	if (hwspin_lock_timeout_irqsave(dma_drv_info->hwlock, HWLOCK_WAIT_TIME, &flag)) {
		loge("hwspinlock timeout\n");
		return;
	}

	writel(value, dma_drv_info->reg_base_addr + reg);
	hwspin_unlock_irqrestore(dma_drv_info->hwlock, &flag);
}

static inline void dmac_register_set_bit(struct soundtrigger_dma_drv_info *dma_drv_info,
					   uint32_t reg, uint32_t offset, uint32_t set_flag)
{
	uint32_t value = 0;
	long unsigned int  flag_hw = 0;
	long unsigned int  flag_sft = 0;

	BUG_ON(NULL == dma_drv_info);

	if (hwspin_lock_timeout_irqsave(dma_drv_info->hwlock, HWLOCK_WAIT_TIME, &flag_hw)) {
		loge("hwspinlock timeout\n");
		return;
	}

	spin_lock_irqsave(&dma_drv_info->lock, flag_sft);
	value = readl(dma_drv_info->reg_base_addr + reg);
	if (set_flag)
		value |= (1 << offset);
	else
		value &= ~(1 << offset);

	writel(value, dma_drv_info->reg_base_addr + reg);
	spin_unlock_irqrestore(&dma_drv_info->lock, flag_sft);
	hwspin_unlock_irqrestore(dma_drv_info->hwlock, &flag_hw);
}

static void pcm_valid_data_get(uint32_t *input_buffer, uint16_t *ouput_buffer, int frame_count)
{
	int count = 0;

	BUG_ON(NULL == input_buffer);
	BUG_ON(NULL == ouput_buffer);

	for (count = 0; count < frame_count; count++) {
		ouput_buffer[count] = input_buffer[count]>>16;
	}
}

static bool pcm_start_addr_find(uint32_t pcm_index, uint16_t *input_buffer, uint32_t input_length, uint32_t *start_addr)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct fast_tran_info *fast_info = &(dma_drv_info->st_fast_tran_info);
	struct normal_tran_info *normal_info = &(dma_drv_info->st_normal_tran_info);
	uint32_t index = 0;
	static uint32_t s_fast_count;
	static uint32_t s_normal_count;

	if (pcm_index == SOUNDTRIGGER_PCM_FAST) {
		if ((input_buffer[0] != fast_info->fast_head_frame_word) && (input_buffer[input_length - 1] != fast_info->fast_head_frame_word))
			return false;

		for (index = 0; index < input_length; index++) {
			if (input_buffer[index] == fast_info->fast_head_frame_word) {
				s_fast_count++;
			} else {
				if (s_fast_count > (input_length * FAST_HEAD_FRAME_COUNT / 2)) {
					*start_addr = index;
					s_fast_count = 0;
					logi("fast channel find head.\n");
					return true;
				}
				s_fast_count = 0;
			}
		}
	}

	if (pcm_index == SOUNDTRIGGER_PCM_NORMAL) {
		if ((input_buffer[0] != normal_info->normal_head_frame_word) && (input_buffer[input_length - 1] != normal_info->normal_head_frame_word))
			return false;

		for (index = 0; index < input_length; index++) {
			if (input_buffer[index] == normal_info->normal_head_frame_word) {
				s_normal_count++;
			} else {
				if (s_normal_count > (input_length * NORMAL_HEAD_FRAME_COUNT / 2)) {
					*start_addr = index;
					s_normal_count = 0;
					logi("normal channel find head.\n");
					return true;
				}
				s_normal_count = 0;
			}
		}
	}
	return false;
}

static void pcm_fast_buffer_check(struct fast_tran_info *fast_info)
{
	uint32_t word_count;
	uint32_t index;
	uint16_t *fast_valid_buffer = fast_info->fast_buffer + fast_info->fast_start_addr;
	uint32_t fast_valid_buffer_len = RINGBUFFER_SIZE / VALID_BYTE_COUNT;

	for (word_count = 0; word_count < fast_valid_buffer_len; word_count++) {
		if (fast_valid_buffer[fast_valid_buffer_len - 1 - word_count] != fast_info->fast_head_frame_word)
			break;
	}

	for (index = 0; index < word_count; index++) {
		fast_valid_buffer[fast_valid_buffer_len - 1 - index] = fast_valid_buffer[fast_valid_buffer_len - 1 - word_count];
		logi("fast tran slimbus miss sampling point[%d].\n", word_count);
	}
}

static void dma_node_set(uint32_t channelNo,struct dma_lli_cfg *lli_cfg)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;

	dmac_register_write(dma_drv_info, HI3xxx_DMAC_CX_LLI_0_REG + channelNo*(0x40),		lli_cfg->lli );
	dmac_register_write(dma_drv_info, HI3xxx_DMAC_CX_CNT0_0_REG + channelNo*(0x40), 	lli_cfg->a_count);
	dmac_register_write(dma_drv_info, HI3xxx_DMAC_CX_SRC_ADDR_0_REG + channelNo*(0x40), lli_cfg->src_addr);
	dmac_register_write(dma_drv_info, HI3xxx_DMAC_CX_DES_ADDR_0_REG + channelNo*(0x40), lli_cfg->des_addr);
	dmac_register_write(dma_drv_info, HI3xxx_DMAC_CX_CONFIG_0_REG + channelNo*(0x40),	lli_cfg->config);
}

static int32_t dma_config_set(struct soundtrigger_dma_drv_info *dma_drv_info)
{
	int32_t err;
	uint32_t pcm_channel;
	uint32_t dma_num;
	uint32_t buffer_num;
	uint32_t dma_cfg_num;
	uint32_t next_addr;
	struct soundtrigger_pcm_info *pcm_info = NULL;

	if (!dma_drv_info ) {
		err = -ENOENT;
		goto err_exit;
	}

	for (pcm_channel = 0; pcm_channel < SOUNDTRIGGER_PCM_CHAN_NUM; pcm_channel++) {
		pcm_info = &(dma_drv_info->st_pcm_info[pcm_channel]);
		if (pcm_channel == SOUNDTRIGGER_PCM_FAST) {
			memcpy(&(pcm_info->pcm_cfg), &g_pcm_fast_cfg, sizeof(struct soundtrigger_pcm_config));
			for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
				pcm_info->channel[dma_num] = g_soundtrigger_dma_fast_cfg[dma_num].channel;
			}
		}
		if (pcm_channel == SOUNDTRIGGER_PCM_NORMAL) {
			memcpy(&(pcm_info->pcm_cfg), &g_pcm_normal_cfg, sizeof(struct soundtrigger_pcm_config));
			for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
				pcm_info->channel[dma_num] = g_soundtrigger_dma_normal_cfg[dma_num].channel;
			}
		}

		pcm_info->buffer_size = pcm_info->pcm_cfg.frame_len * pcm_info->pcm_cfg.byte_count;

		/* alloc swap buffers and dma configs, accoring to swap buffer number and input channel number. */
		for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
			for (buffer_num = 0; buffer_num < PCM_SWAP_BUFFER_NUM; buffer_num++) {
				pcm_info->buffer[dma_num][buffer_num] = (void *)dma_alloc_coherent(dma_drv_info->dev, pcm_info->buffer_size,
					&(pcm_info->buffer_physical_addr[dma_num][buffer_num]), GFP_KERNEL);
				if (pcm_info->buffer[dma_num][buffer_num] == NULL) {
					err = -ENOMEM;
					goto err_exit;
				}
				memset(pcm_info->buffer[dma_num][buffer_num], 0, pcm_info->buffer_size);

				pcm_info->dma_cfg[dma_num][buffer_num] = (struct dma_lli_cfg *)dma_alloc_coherent(dma_drv_info->dev,
					sizeof(struct dma_lli_cfg), &(pcm_info->lli_dma_physical_addr[dma_num][buffer_num]), GFP_KERNEL);
				if (pcm_info->dma_cfg == NULL) {
					err = -ENOMEM;
					goto err_exit;
				}
				memset(pcm_info->dma_cfg[dma_num][buffer_num], 0, sizeof(struct dma_lli_cfg));
			}
		}

		/* set dma config */
		for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
			for (dma_cfg_num = 0; dma_cfg_num < PCM_SWAP_BUFFER_NUM; dma_cfg_num++) {
				if (pcm_channel == SOUNDTRIGGER_PCM_FAST) {
					pcm_info->dma_cfg[dma_num][dma_cfg_num]->config = g_soundtrigger_dma_fast_cfg[dma_num].config;
					pcm_info->dma_cfg[dma_num][dma_cfg_num]->src_addr = g_soundtrigger_dma_fast_cfg[dma_num].port;
				}
				if (pcm_channel == SOUNDTRIGGER_PCM_NORMAL) {
					pcm_info->dma_cfg[dma_num][dma_cfg_num]->config = g_soundtrigger_dma_normal_cfg[dma_num].config;
					pcm_info->dma_cfg[dma_num][dma_cfg_num]->src_addr = g_soundtrigger_dma_normal_cfg[dma_num].port;
				}

				next_addr = pcm_info->lli_dma_physical_addr[dma_num][(dma_cfg_num + 1) % PCM_SWAP_BUFFER_NUM];
				pcm_info->dma_cfg[dma_num][dma_cfg_num]->lli = DRV_DMA_LLI_LINK(next_addr);
				pcm_info->dma_cfg[dma_num][dma_cfg_num]->des_addr = (uint32_t)pcm_info->buffer_physical_addr[dma_num][dma_cfg_num];
				pcm_info->dma_cfg[dma_num][dma_cfg_num]->a_count = pcm_info->buffer_size;
			}
		}
	}
	return 0;

err_exit:
	for (pcm_channel = 0; pcm_channel < SOUNDTRIGGER_PCM_CHAN_NUM; pcm_channel++) {
		pcm_info = &(dma_drv_info->st_pcm_info[pcm_channel]);
		for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
			for (buffer_num = 0; buffer_num < PCM_SWAP_BUFFER_NUM; buffer_num++) {
				if (pcm_info->buffer[dma_num][buffer_num]) {
					dma_free_coherent(dma_drv_info->dev, pcm_info->buffer_size, pcm_info->buffer[dma_num][buffer_num],
						pcm_info->buffer_physical_addr[dma_num][buffer_num]);
					pcm_info->buffer[dma_num][buffer_num] = NULL;
				}

				if (pcm_info->dma_cfg[dma_num][buffer_num]) {
					dma_free_coherent(dma_drv_info->dev, sizeof(struct dma_lli_cfg), pcm_info->dma_cfg[dma_num][buffer_num],
						pcm_info->lli_dma_physical_addr[dma_num][buffer_num]);
					pcm_info->dma_cfg[dma_num][buffer_num] = NULL;
				}
			}
		}
	}

	loge("dma config fail, err:[%d].\n", err);
	return err;
}

static int32_t dma_start(struct st_fast_status * fast_status)
{
	int32_t err;
	uint32_t pcm_channel;
	uint32_t dma_channel;
	uint32_t dma_port_num;
	struct soundtrigger_pcm_info *pcm_info = NULL;
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	slimbus_track_param_t  slimbus_params;
	if (!dma_drv_info) {
		err = -ENOENT;
		goto err_exit;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state != DMA_DRV_INIT) {
		err = -EAGAIN;
		goto err_exit;
	}

	{
		/* slimbus config */
		slimbus_params.rate = 16000;
		slimbus_params.channels = 2;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP, &slimbus_params);
		if(fast_status->fm_status){
			slimbus_params.rate = 48000;
		}else{
			slimbus_params.rate = 192000;
		}
		logi("fast slimbus_params.rate[%d]\n",slimbus_params.rate);
		slimbus_params.channels = 2;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_SOUND_TRIGGER, &slimbus_params);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_SOUND_TRIGGER, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_SOUND_TRIGGER);
	}

	for (pcm_channel = 0; pcm_channel < SOUNDTRIGGER_PCM_CHAN_NUM; pcm_channel++) {
		pcm_info = &(dma_drv_info->st_pcm_info[pcm_channel]);

		for (dma_port_num = 0; dma_port_num < DMA_PORT_NUM; dma_port_num++) {
			dma_channel = pcm_info->channel[dma_port_num];
			/* set initial dma config */
			dma_node_set(dma_channel, pcm_info->dma_cfg[dma_port_num][0]);
			/* clear interrupt */
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC1_RAW_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC2_RAW_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR1_RAW_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR2_RAW_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR3_RAW_REG, dma_channel, 1);
			/* dma channel unmask interrupt */
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC1_MASK_0_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC2_MASK_0_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR1_MASK_0_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR2_MASK_0_REG, dma_channel, 1);
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR3_MASK_0_REG, dma_channel, 1);
			/* enable dma channel interrupt */
			dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_CX_CONFIG_0_REG + dma_channel*(0x40), 0, 1);
		}
	}

	return 0;

err_exit:
	return err;
}

static void dma_stop(int32_t pcm_channel)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct soundtrigger_pcm_info *pcm_info = &(dma_drv_info->st_pcm_info[pcm_channel]);
	uint32_t dma_port_num;
	uint32_t dma_channel;

	for (dma_port_num = 0; dma_port_num < DMA_PORT_NUM; dma_port_num++) {
		dma_channel = pcm_info->channel[dma_port_num];
		/* disable dma channel interrupt */
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_CX_CONFIG_0_REG + dma_channel*(0x40), 0, 0);
		/* dma channel mask interrupt */
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC1_MASK_0_REG, dma_channel, 0);
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_TC2_MASK_0_REG, dma_channel, 0);
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR1_MASK_0_REG, dma_channel, 0);
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR2_MASK_0_REG, dma_channel, 0);
		dmac_register_set_bit(dma_drv_info, HI3xxx_DMAC_INT_ERR3_MASK_0_REG, dma_channel, 0);
	}
}

static int32_t dma_open(struct st_fast_status * fast_status)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct fast_tran_info *fast_info = &(dma_drv_info->st_fast_tran_info);
	struct normal_tran_info *normal_info = &(dma_drv_info->st_normal_tran_info);
	int32_t err;

	if (!dma_drv_info) {
		err = -ENOENT;
		goto err_exit;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state != DMA_DRV_NO_INIT)
		return -EAGAIN;

	/*alloc fast buffer*/
	fast_info->fast_buffer = (uint16_t *)kzalloc(FAST_BUFFER_SIZE, GFP_KERNEL);
	if (!fast_info->fast_buffer) {
		loge("fast_buffer kzalloc failed.\n");
		err = -ENOENT;
		goto err_exit;
	}

	memset(fast_info->fast_buffer, 0x00, FAST_BUFFER_SIZE);
	fast_info->fast_read_complete_flag = READ_NOT_COMPLETE;
	fast_info->fast_buffer_size = FAST_BUFFER_SIZE;
	fast_info->dma_tran_count = 0;
	fast_info->dma_tran_total_count = FAST_TRAN_COUNT;
	fast_info->fast_complete_flag = FAST_TRAN_NOT_COMPLETE;
	fast_info->fast_head_frame_word = HEAD_FRAME_WORD;
	fast_info->fast_head_frame_size = FAST_FRAME_LENGTH * VALID_BYTE_COUNT;
	fast_info->fast_frame_find_flag = FRAME_NOT_FIND;
	fast_info->irq_count_left = 0;
	fast_info->irq_count_right = 0;
	fast_info->read_count_left = 0;
	fast_info->read_count_right = 0;

	/*alloc normal buffer*/
	normal_info->normal_buffer = (uint16_t *)kzalloc(NORMAL_BUFFER_SIZE, GFP_KERNEL);
	if (!normal_info->normal_buffer) {
		loge("normal_buffer kzalloc failed.\n");
		err = -ENOENT;
		goto err_exit;
	}

	Static_RingBuffer_Init(normal_info->normal_buffer);

	normal_info->normal_buffer_size = NORMAL_BUFFER_SIZE;
	normal_info->normal_head_frame_word = HEAD_FRAME_WORD;
	normal_info->normal_head_frame_size = NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT;
	normal_info->normal_frame_find_flag = FRAME_NOT_FIND;
	normal_info->normal_first_frame_read_flag = READ_NOT_COMPLETE;
	normal_info->normal_tran_count = 0;
	normal_info->irq_count_left = 0;
	normal_info->irq_count_right = 0;
	normal_info->read_count_left = 0;
	normal_info->read_count_right = 0;

	dma_drv_info->fm_status = fast_status->fm_status;

	if (dma_drv_info->dma_alloc_flag == 0) {
		dma_drv_info->dma_alloc_flag = 1;
		err = dma_config_set(dma_drv_info);
		if (err)
			goto err_exit;
	}

	dma_drv_info->dma_int_fast_flag = 0;
	dma_drv_info->dma_int_nomal_flag = 0;

	err = clk_prepare_enable(dma_drv_info->asp_subsys_clk);
	if (IS_ERR_VALUE(err)) {
		loge( "clk prepare enable failed, err:[%d].\n", err);
		goto err_exit;
	}

	dma_drv_info->soundtrigger_dma_drv_state = DMA_DRV_INIT;
	return 0;

err_exit:
	if (fast_info->fast_buffer) {
		kzfree(fast_info->fast_buffer);
		fast_info->fast_buffer = NULL;
	}

	if (normal_info->normal_buffer) {
		kzfree(normal_info->normal_buffer);
		normal_info->normal_buffer = NULL;
	}

	loge( "dma open fail, err:[%d].\n", err);
	return err;
}

static int32_t dma_close(struct st_fast_status * fast_status)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct fast_tran_info *fast_info = NULL;
	struct normal_tran_info *normal_info = NULL;
	struct soundtrigger_pcm_info *fast_pcm_info = NULL;
	struct soundtrigger_pcm_info *normal_pcm_info = NULL;
	int32_t err;
	if (!dma_drv_info) {
		err = -ENOENT;
		goto err_exit;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state != DMA_DRV_INIT) {
		err = -EAGAIN;
		goto err_exit;
	}

	dma_drv_info->soundtrigger_dma_drv_state = DMA_DRV_NO_INIT;

	fast_info = &(dma_drv_info->st_fast_tran_info);
	normal_info = &(dma_drv_info->st_normal_tran_info);
	fast_pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_FAST]);
	normal_pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_NORMAL]);

	if (fast_info->fast_read_complete_flag != FAST_TRAN_COMPLETE)
		dma_stop(SOUNDTRIGGER_PCM_FAST);

	dma_stop(SOUNDTRIGGER_PCM_NORMAL);

	slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_SOUND_TRIGGER);
	slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_SOUND_TRIGGER);

	cancel_delayed_work(&dma_drv_info->soundtrigger_delay_dma_fast_left_work);
	cancel_delayed_work(&dma_drv_info->soundtrigger_delay_dma_fast_right_work);
	cancel_delayed_work(&dma_drv_info->soundtrigger_delay_dma_normal_left_work);
	cancel_delayed_work(&dma_drv_info->soundtrigger_delay_dma_normal_right_work);
	flush_workqueue(dma_drv_info->soundtrigger_delay_wq);

	fast_info->irq_count_left = 0;
	fast_info->irq_count_right = 0;
	fast_info->read_count_left = 0;
	fast_info->read_count_right = 0;
	fast_info->dma_tran_count = 0;
	fast_info->dma_tran_total_count = 0;

	normal_info->irq_count_left = 0;
	normal_info->irq_count_right = 0;
	normal_info->read_count_left = 0;
	normal_info->read_count_right = 0;
	normal_info->normal_tran_count = 0;

	/* free fast and normal channel pcm buffer */
	if (fast_info->fast_buffer) {
		kzfree(fast_info->fast_buffer);
		fast_info->fast_buffer = NULL;
	}

	Static_RingBuffer_DeInit();

	if (normal_info->normal_buffer) {
		kzfree(normal_info->normal_buffer);
		normal_info->normal_buffer = NULL;
	}

	clk_disable_unprepare(dma_drv_info->asp_subsys_clk);
	return 0;
err_exit:
	loge( "dma close fail, err:[%d].\n", err);
	return err;
}

static int32_t dma_fops_open(struct inode *finode, struct file *fd)
{
	int32_t err;
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;

	if (!dma_drv_info)
		return -ENOENT;

	err = request_irq(dma_drv_info->irq, soundtrigger_dmac_irq_handler,
			  IRQF_SHARED, "asp_dma_irq", dma_drv_info->dev);
	if (err)
		return -ENOENT;

	return 0;
}

static int32_t dma_fops_release(struct inode *finode, struct file *fd)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;

	if (!dma_drv_info)
		return -ENOENT;

	free_irq(dma_drv_info->irq, dma_drv_info->dev);

	return 0;
}


static ssize_t dma_fops_read(struct file *file, char __user *buffer, size_t count, loff_t *f_ops)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct fast_tran_info *fast_info = &(dma_drv_info->st_fast_tran_info);
	struct normal_tran_info *normal_info = &(dma_drv_info->st_normal_tran_info);
	int32_t rest_bytes = 0;
	int32_t max_read_len = 0;
	uint16_t *pcm_buffer = NULL;
	static uint16_t static_buffer[NORMAL_FRAME_LENGTH];

	if (dma_drv_info == NULL || fast_info == NULL || normal_info == NULL) {
		loge("pointer is NULL.\n");
		return -EINVAL;
	}

	if(!buffer) {
		loge("user input buffer is invalid\n");
		return -EINVAL;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state == DMA_DRV_NO_INIT) {
		loge("soundtrigger dma aleady closed\n");
		return -EINVAL;
	}

	max_read_len = (RINGBUFFER_SIZE > (NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT)) ?
		RINGBUFFER_SIZE : (NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT);
	if (count < max_read_len) {
		loge("user buffer too short, need %d\n", max_read_len);
		return -EINVAL;
	}

	if (fast_info->fast_complete_flag == FAST_TRAN_NOT_COMPLETE) {
		//loge("fast channel not complete.\n");
		return -EAGAIN;
	}

	if((0 == dma_drv_info->dma_int_fast_flag) || (0 == dma_drv_info->dma_int_nomal_flag)){
		loge("normal config: %x, fast config: %x, PORT6_REG_0: %x, PORT6_REG_1: %x, PORT10_REG_0: %x, PORT10_REG_1: %x\n"
			, dmac_register_read(dma_drv_info, HI3xxx_DMAC_CX_CONFIG_0_REG + 3*(0x40))
			, dmac_register_read(dma_drv_info, HI3xxx_DMAC_CX_CONFIG_0_REG + 7*(0x40))
			, slimbus_register_read(dma_drv_info, HI3xxx_SLIMBUS_PORT6_REG_0)
			, slimbus_register_read(dma_drv_info, HI3xxx_SLIMBUS_PORT6_REG_1)
			, slimbus_register_read(dma_drv_info, HI3xxx_SLIMBUS_PORT10_REG_0)
			, slimbus_register_read(dma_drv_info, HI3xxx_SLIMBUS_PORT10_REG_1));
		dma_drv_info->dma_int_fast_flag = 1;
		dma_drv_info->dma_int_nomal_flag = 1;
	}

	/* first, hal not read fast data, we copy fast data to user */
	if (fast_info->fast_read_complete_flag == READ_NOT_COMPLETE) {
		pcm_fast_buffer_check(fast_info);
		rest_bytes = copy_to_user(buffer,fast_info->fast_buffer + fast_info->fast_start_addr, RINGBUFFER_SIZE);
		fast_info->fast_read_complete_flag = READ_COMPLETE;
		if (rest_bytes) {
			loge("fast chan copy to user space fail, rest bytes[%d].\n", rest_bytes);
			return -EINVAL;
		} else {
			return RINGBUFFER_SIZE;
		}
	} else {
	/* second, hal already read fast data, we copy normal data to user */
		if (!Static_RingBuffer_IsEmpty()) {
			pcm_buffer = (uint16_t *)kzalloc(NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT, GFP_KERNEL);
			if (!pcm_buffer) {
				loge("pcm_buffer kzalloc failed.\n");
				return -EINVAL;
			}
			Static_RingBuffer_Get(pcm_buffer);

			if (normal_info->normal_first_frame_read_flag == READ_NOT_COMPLETE) {
				normal_info->normal_first_frame_read_flag = READ_COMPLETE;
				memcpy(static_buffer, pcm_buffer + dma_drv_info->st_normal_tran_info.normal_start_addr,
					(NORMAL_FRAME_LENGTH - dma_drv_info->st_normal_tran_info.normal_start_addr) * VALID_BYTE_COUNT);
				kzfree(pcm_buffer);
			} else {
				memcpy(static_buffer + (NORMAL_FRAME_LENGTH - dma_drv_info->st_normal_tran_info.normal_start_addr),
					pcm_buffer, dma_drv_info->st_normal_tran_info.normal_start_addr * VALID_BYTE_COUNT);
				rest_bytes = copy_to_user(buffer, static_buffer, NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT);
				memcpy(static_buffer, pcm_buffer + dma_drv_info->st_normal_tran_info.normal_start_addr,
					(NORMAL_FRAME_LENGTH - dma_drv_info->st_normal_tran_info.normal_start_addr) * VALID_BYTE_COUNT);
				kzfree(pcm_buffer);
				if (rest_bytes) {
					loge("normal chan copy to user space fail, rest bytes[%d].\n", rest_bytes);
					return -EINVAL;
				} else {
					return (NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT);
				}
			}
		}
	}
	return -EINVAL;
}

static long dma_fops_ioctl(struct file *fd, uint32_t cmd, unsigned long arg)
{
	int32_t err = 0;
	struct soundtrigger_io_sync_param param;
	struct krn_param_io_buf krn_param;
	struct st_fast_status * fast_status;

	if (!(void __user *)arg) {
		loge("INPUT ERROR: arg is NULL\n");
		err = -EINVAL;
		return (long)err;
	}

	if (copy_from_user(&param, (void __user *)arg, sizeof(struct soundtrigger_io_sync_param))) {
		loge("copy_from_user fail.\n");
		err = -EIO;
		return (long)err;
	}

	err = get_input_param(param.para_size_in,
					 INT_TO_ADDR(param.para_in_l, param.para_in_h),
					 &krn_param.buf_size_in,
					 (void **)&krn_param.buf_in);
	if (err) {
		loge("INPUT ERROR: input param is not valid!\n");
		err = -EINVAL;
		return (long)err;
	}

	fast_status = (struct st_fast_status * )krn_param.buf_in;

	switch(cmd) {
		case SOUNDTRIGGER_CMD_DMA_READY:
			err = dma_open(fast_status);
			logi("dma open, ret[%d].\n", err);
			break;
		case SOUNDTRIGGER_CMD_DMA_OPEN:
			err = dma_start(fast_status);
			break;
		case SOUNDTRIGGER_CMD_DMA_CLOSE:
			err = dma_close(fast_status);
			logi("dma close, ret[%d].\n", err);
			break;
		default:
			loge("invalid value, ret[%d].\n", err);
			err = -ENOTTY;
			break;
	}

	param_free((void **)&(krn_param.buf_in));
	return (long)err;
}

static long dma_fops_ioctl32(struct file *fd, uint32_t cmd, unsigned long arg)
{
	void __user *user_arg = (void __user*)compat_ptr(arg);

	return dma_fops_ioctl(fd, cmd, (unsigned long)user_arg);
}

void dma_fast_left_workfunc(struct work_struct *work)
{
	uint32_t *left_buffer = NULL;
	uint16_t *temp_buffer = NULL;
	uint32_t start_addr = 0;
	static uint32_t om_fast_count = 0;
	struct soundtrigger_dma_drv_info *dma_drv_info = NULL;
	struct soundtrigger_pcm_info *pcm_info = NULL;
	struct fast_tran_info *fast_info = NULL;

	om_fast_count++;
	if (om_fast_count == 50) {
		om_fast_count = 0;
		logi("fast dma irq come.\n");
	}

	dma_drv_info = container_of(work, struct soundtrigger_dma_drv_info, soundtrigger_delay_dma_fast_left_work.work);
	if (!dma_drv_info) {
		loge("dma_drv_info get error\n");
		return;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state == DMA_DRV_NO_INIT) {
		loge("drv is not open, work queue don't process\n");
		return;
	}

	pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_FAST]);

	fast_info = &(dma_drv_info->st_fast_tran_info);
	if (fast_info->fast_complete_flag == FAST_TRAN_COMPLETE)
		return;

	if (pcm_info->buffer_size == 0) {
		loge( "pcm info buffer_size is 0.\n");
		return;
	}

	left_buffer = (uint32_t *)kzalloc(pcm_info->buffer_size, GFP_KERNEL);
	if (!left_buffer) {
		loge("left_buffer kzalloc failed\n");
		return;
	}

	temp_buffer = (uint16_t *)kzalloc(FAST_FRAME_LENGTH * VALID_BYTE_COUNT, GFP_KERNEL);
	if (!temp_buffer) {
		kzfree(left_buffer);
		loge("temp_buffer kzalloc failed.\n");
		return;
	}

	if (dma_drv_info->st_fast_tran_info.read_count_left >= dma_drv_info->st_fast_tran_info.irq_count_left) {
		loge("read_count_left[%d] out of range irq_count_left[%d]error\n",
					dma_drv_info->st_fast_tran_info.read_count_left,
					dma_drv_info->st_fast_tran_info.irq_count_left);
		goto exit;
	}

	if (dma_drv_info->st_fast_tran_info.read_count_left >= FAST_CHANNEL_TIMEOUT_READ_COUNT) {
		loge( "dma fast channel timeout.\n");
		dma_stop(SOUNDTRIGGER_PCM_FAST);
		dma_stop(SOUNDTRIGGER_PCM_NORMAL);
		goto exit;
	} else {
		memcpy(left_buffer, (uint32_t *)pcm_info->buffer[0][dma_drv_info->st_fast_tran_info.read_count_left % PCM_SWAP_BUFFER_NUM], pcm_info->buffer_size);
		dma_drv_info->st_fast_tran_info.read_count_left++;
		pcm_valid_data_get(left_buffer, temp_buffer, FAST_FRAME_LENGTH);

		if (dma_drv_info->st_fast_tran_info.fast_frame_find_flag == FRAME_NOT_FIND) {
			if (pcm_start_addr_find(SOUNDTRIGGER_PCM_FAST, temp_buffer, FAST_FRAME_LENGTH, &start_addr)){
				dma_drv_info->st_fast_tran_info.fast_start_addr = start_addr;
				memcpy(dma_drv_info->st_fast_tran_info.fast_buffer + FAST_FRAME_LENGTH * dma_drv_info->st_fast_tran_info.dma_tran_count,
						temp_buffer, FAST_FRAME_LENGTH * VALID_BYTE_COUNT);
				dma_drv_info->st_fast_tran_info.fast_frame_find_flag = FRAME_FIND;
				dma_drv_info->st_fast_tran_info.fast_start_addr = start_addr;
				dma_drv_info->st_fast_tran_info.dma_tran_count++;
			}
		} else {
			memcpy(dma_drv_info->st_fast_tran_info.fast_buffer + FAST_FRAME_LENGTH * dma_drv_info->st_fast_tran_info.dma_tran_count,
					temp_buffer, FAST_FRAME_LENGTH * VALID_BYTE_COUNT);
			dma_drv_info->st_fast_tran_info.dma_tran_count++;
		}

		if (fast_info->dma_tran_count == fast_info->dma_tran_total_count) {
			dma_stop(SOUNDTRIGGER_PCM_FAST);
			fast_info->fast_complete_flag = FAST_TRAN_COMPLETE;
		}
	}

exit:
	kzfree(temp_buffer);
	kzfree(left_buffer);
}

void dma_fast_right_workfunc(struct work_struct *work)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = container_of(work, struct soundtrigger_dma_drv_info,
		soundtrigger_delay_dma_fast_right_work.work);

	if (!dma_drv_info) {
		loge("dma_drv_info NULL.\n");
		return;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state == DMA_DRV_NO_INIT) {
		loge("drv is not open, work queue don't process\n");
		return;
	}

	if (dma_drv_info->st_fast_tran_info.read_count_right >= dma_drv_info->st_fast_tran_info.irq_count_right)
		return;
	else
		dma_drv_info->st_fast_tran_info.read_count_right++;

	/* we do nothing here */
}

void dma_normal_left_workfunc(struct work_struct *work)
{
	uint32_t *left_buffer = NULL;
	uint16_t *temp_buf = NULL;
	uint32_t start_addr = 0;
	static uint32_t om_normal_count = 0;
	struct soundtrigger_pcm_info *pcm_info = NULL;
	struct soundtrigger_dma_drv_info *dma_drv_info = NULL;

	om_normal_count++;
	if (om_normal_count == 50) {
		om_normal_count = 0;
		logi("normal dma irq come.\n");
	}

	dma_drv_info = container_of(work, struct soundtrigger_dma_drv_info, soundtrigger_delay_dma_normal_left_work.work);
	if (!dma_drv_info) {
		loge("dma_drv_info NULL\n");
		return;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state == DMA_DRV_NO_INIT) {
		loge("drv is not open, work queue don't process\n");
		return;
	}

	pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_NORMAL]);

	if (pcm_info->buffer_size == 0) {
		loge( "pcm info buffer_size is 0.\n");
		return;
	}

	left_buffer = (uint32_t *)kzalloc(pcm_info->buffer_size, GFP_KERNEL);
	if (!left_buffer) {
		loge("normal left_buffer kzalloc failed\n");
		return;
	}

	temp_buf = (uint16_t *)kzalloc(NORMAL_FRAME_LENGTH * VALID_BYTE_COUNT, GFP_KERNEL);
	if (temp_buf == NULL) {
		loge("normal temp_buf kzalloc failed\n");
		goto exit_free;
	}

	if (dma_drv_info->st_normal_tran_info.read_count_left >= dma_drv_info->st_normal_tran_info.irq_count_left) {
		goto exit;
	}
	else {
		memcpy(left_buffer, (uint32_t *)pcm_info->buffer[0][dma_drv_info->st_normal_tran_info.read_count_left % PCM_SWAP_BUFFER_NUM], pcm_info->buffer_size);
		dma_drv_info->st_normal_tran_info.read_count_left++;
		pcm_valid_data_get(left_buffer, temp_buf, NORMAL_FRAME_LENGTH);

		if (dma_drv_info->st_normal_tran_info.normal_frame_find_flag == FRAME_NOT_FIND) {
			if (pcm_start_addr_find(SOUNDTRIGGER_PCM_NORMAL, temp_buf, NORMAL_FRAME_LENGTH, &start_addr)) {
				Static_RingBuffer_Put(temp_buf);
				dma_drv_info->st_normal_tran_info.normal_frame_find_flag = FRAME_FIND;
				dma_drv_info->st_normal_tran_info.normal_start_addr = start_addr;
				dma_drv_info->st_normal_tran_info.normal_tran_count++;
			}
		} else {
			Static_RingBuffer_Put(temp_buf);
			dma_drv_info->st_normal_tran_info.normal_tran_count++;
		}
	}

	if ((dma_drv_info->st_normal_tran_info.read_count_left - dma_drv_info->st_normal_tran_info.normal_tran_count)
		>= NORMAL_CHANNEL_TIMEOUT_READ_COUNT) {
		loge( "dma normal channel timeout.\n");
		dma_stop(SOUNDTRIGGER_PCM_FAST);
		dma_stop(SOUNDTRIGGER_PCM_NORMAL);
		goto exit;
	}

exit:
	kzfree(temp_buf);
exit_free:
	kzfree(left_buffer);

}

void dma_normal_right_workfunc(struct work_struct *work)
{
	struct soundtrigger_dma_drv_info *dma_drv_info = container_of(work, struct soundtrigger_dma_drv_info,
		soundtrigger_delay_dma_normal_right_work.work);
	if (!dma_drv_info ) {
		loge("dma_drv_info NULL.\n");
		return;
	}

	if (dma_drv_info->soundtrigger_dma_drv_state == DMA_DRV_NO_INIT) {
		loge("drv is not open, work queue don't process\n");
		return;
	}

	if (dma_drv_info->st_normal_tran_info.read_count_right >= dma_drv_info->st_normal_tran_info.irq_count_right)
		return;
	else
		dma_drv_info->st_normal_tran_info.read_count_right++;

	/* we do nothing here */
}

static int32_t dma_interrupt_query(struct soundtrigger_dma_drv_info *pinfo)
{
	int32_t irq_err = 0;
	int32_t register_state = 0;
	int32_t errCount = 0;

	if (!pinfo) {
		irq_err = IRQ_ERR;
		goto err_exit;
	}
	/* whether have interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_STAT_0_REG) & DMA_CH_UNMASK;
	if (register_state == 0) {
		irq_err = IRQ_ERR;
		loge( "dma interrupt status error[%x].\n",register_state);
		goto err_exit;
	}
	/* whether have error interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_ERR1_0_REG) & DMA_CH_UNMASK;
	if (register_state != 0) {
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_ERR1_RAW_REG, DMA_CH_UNMASK);
		loge( "dma interrupt setting error[%x]\n",register_state);
		errCount++;
	}
	/* whether have transmit error interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_ERR2_0_REG) & DMA_CH_UNMASK;
	if (register_state != 0) {
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_ERR2_RAW_REG, DMA_CH_UNMASK);
		loge( "dma interrupt transmission error[%x]\n",register_state);
		errCount++;
	}
	/* whether have lli error interrupt  */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_ERR3_0_REG) & DMA_CH_UNMASK;
	if (register_state != 0) {
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_ERR3_RAW_REG, DMA_CH_UNMASK);
		loge( "dma interrupt lli error[%x]\n",register_state);
		errCount++;
	}

	if (errCount > 0) {
		irq_err = IRQ_ERR;
		goto err_exit;
	}
	/* whether have transmit complete interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_TC1_0_REG) & DMA_CH_UNMASK;
	if (register_state != 0) {
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_TC1_RAW_REG, DMA_CH_UNMASK);
		irq_err = IRQ_FINISH;
		loge( "dma interrupt transmission finish error[%x]\n",register_state);
		goto err_exit;
	}
	/* whether is fast left lli interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_TC2_0_REG) & DMA_FAST_LEFT_CH_UNMASK;
	if (register_state != 0) {
		(pinfo->st_fast_tran_info.irq_count_left)++;
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_TC2_RAW_REG, DMA_FAST_LEFT_CH_UNMASK);
		return IRQ_FAST_LEFT_CHAN;
	}
	/* whether is fast right lli interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_TC2_0_REG) & DMA_FAST_RIGHT_CH_UNMASK;
	if (register_state != 0) {
		(pinfo->st_fast_tran_info.irq_count_right)++;
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_TC2_RAW_REG, DMA_FAST_RIGHT_CH_UNMASK);
		return IRQ_FAST_RIGHT_CHAN;
	}
	/* whether is normal left lli interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_TC2_0_REG) & DMA_NORMAL_LEFT_CH_UNMASK;
	if (register_state != 0) {
		(pinfo->st_normal_tran_info.irq_count_left)++;
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_TC2_RAW_REG, DMA_NORMAL_LEFT_CH_UNMASK);
		return IRQ_NORMAL_LEFT_CHAN;
	}
	/* whether is normal right lli interrupt */
	register_state = dmac_register_read(pinfo, HI3xxx_DMAC_INT_TC2_0_REG) & DMA_NORMAL_RIGHT_CH_UNMASK;
	if (register_state != 0) {
		(pinfo->st_normal_tran_info.irq_count_right)++;
		dmac_register_write(pinfo, HI3xxx_DMAC_INT_TC2_RAW_REG, DMA_NORMAL_RIGHT_CH_UNMASK);
		return IRQ_NORMAL_RIGHT_CHAN;
	}

err_exit:
	return irq_err;
}

static irqreturn_t soundtrigger_dmac_irq_handler(int32_t irq, void *dev_id)
{
	int32_t irq_state;
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	if (!dma_drv_info)
		return IRQ_NONE;
	 irq_state = dma_interrupt_query(dma_drv_info);

	switch(irq_state) {
		case IRQ_FAST_LEFT_CHAN:
			dma_drv_info->dma_int_fast_flag = 1;
			queue_delayed_work(dma_drv_info->soundtrigger_delay_wq,
				&dma_drv_info->soundtrigger_delay_dma_fast_left_work, msecs_to_jiffies(0));
			break;
		case IRQ_FAST_RIGHT_CHAN:
			queue_delayed_work(dma_drv_info->soundtrigger_delay_wq,
				&dma_drv_info->soundtrigger_delay_dma_fast_right_work, msecs_to_jiffies(0));
			break;
		case IRQ_NORMAL_LEFT_CHAN:
			dma_drv_info->dma_int_nomal_flag= 1;
			queue_delayed_work(dma_drv_info->soundtrigger_delay_wq,
				&dma_drv_info->soundtrigger_delay_dma_normal_left_work, msecs_to_jiffies(0));
			break;
		case IRQ_NORMAL_RIGHT_CHAN:
			queue_delayed_work(dma_drv_info->soundtrigger_delay_wq,
				&dma_drv_info->soundtrigger_delay_dma_normal_right_work, msecs_to_jiffies(0));
		break;
		default:
			break;
	}

	return IRQ_HANDLED;
}

static const struct file_operations soundtrigger_dma_drv_fops = {
	.owner			= THIS_MODULE,
	.open			= dma_fops_open,
	.release		= dma_fops_release,
	.read			= dma_fops_read,
	.unlocked_ioctl = dma_fops_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= dma_fops_ioctl32,
#endif
};

static struct miscdevice soundtrigger_dma_drv_device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DRV_NAME,
	.fops	= &soundtrigger_dma_drv_fops,
};

static int32_t soundtrigger_dma_drv_probe (struct platform_device *pdev)
{
	struct device					 *dev			= &pdev->dev;
	struct soundtrigger_dma_drv_info *dma_drv_info	 = NULL;
	int32_t  err;
	g_dma_drv_info = NULL;

	logi("dma probe.\n");

	if (!dev) {
		loge("dev is null\n");
		err = -ENOENT;
		goto err_nodev;
	}

	err = misc_register(&soundtrigger_dma_drv_device);
	if (err)
		goto err_register;

	dma_drv_info = devm_kzalloc(dev, sizeof(struct soundtrigger_dma_drv_info), GFP_KERNEL);
	if (!dma_drv_info) {
		err = -ENOMEM;
		goto err_kzalloc;
	}

	memset(dma_drv_info,0x00,sizeof(struct soundtrigger_dma_drv_info));
	dma_drv_info->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!dma_drv_info->res) {
		err = -ENOENT;
		goto err_resource;
	}

	if (!devm_request_mem_region(dev, dma_drv_info->res->start,
					 resource_size(dma_drv_info->res),
					 pdev->name)) {
		err = -ENOMEM;
		goto err_resource;
	}

	dma_drv_info->reg_base_addr = devm_ioremap(dev, dma_drv_info->res->start,
						resource_size(dma_drv_info->res));
	if (!dma_drv_info->reg_base_addr) {
		err = -ENOMEM;
		goto err_ioremap;
	}

	dma_drv_info->v_slimbus_base_reg_addr = ioremap(HI3xxx_SLIMBUS_BASE_REG,HI3xxx_SLIMBUS_REG_SIZE);
	if (!dma_drv_info->v_slimbus_base_reg_addr)
	{
		err = -ENOENT;
		loge("slimbus ioremap error!\n");
		goto err_dma_drv_exit;
	}

	dma_drv_info->irq = platform_get_irq_byname(pdev, "asp_dma_irq");
	if (dma_drv_info->irq < 0) {
		err = -ENOENT;
		goto err_irq;
	}

	dma_drv_info->asp_ip = devm_regulator_get(dev, "asp-dmac");
	if (IS_ERR(dma_drv_info->asp_ip)) {
		err = -ENOENT;
		goto err_dma_drv_exit;
	}

	dma_drv_info->hwlock = hwspin_lock_request_specific(SOUNDTRIGGER_HWLOCK_ID);
	if (!dma_drv_info->hwlock) {
		err = -ENOENT;
		goto err_dma_drv_exit;
	}

	spin_lock_init(&dma_drv_info->lock);

	dma_drv_info->soundtrigger_delay_wq = create_singlethread_workqueue("soundtrigger_delay_wq");
	if (!dma_drv_info->soundtrigger_delay_wq) {
		err = -ENOMEM;
		goto err_dma_drv_exit;
	}

	dma_drv_info->asp_subsys_clk = devm_clk_get(dev, "clk_asp_subsys");
	if ( IS_ERR(dma_drv_info->asp_subsys_clk)) {
		err= PTR_ERR(dma_drv_info->asp_subsys_clk);
		loge( "asp subsys clk fail.\n");
		goto err_dma_drv_exit;
	}

	INIT_DELAYED_WORK(&dma_drv_info->soundtrigger_delay_dma_fast_left_work, dma_fast_left_workfunc);
	INIT_DELAYED_WORK(&dma_drv_info->soundtrigger_delay_dma_fast_right_work, dma_fast_right_workfunc);
	INIT_DELAYED_WORK(&dma_drv_info->soundtrigger_delay_dma_normal_left_work, dma_normal_left_workfunc);
	INIT_DELAYED_WORK(&dma_drv_info->soundtrigger_delay_dma_normal_right_work, dma_normal_right_workfunc);

	dma_drv_info->dev = dev;
	dma_drv_info->soundtrigger_dma_drv_state = DMA_DRV_NO_INIT;
	dma_drv_info->dma_alloc_flag = 0;
	platform_set_drvdata(pdev, dma_drv_info);
	g_dma_drv_info = dma_drv_info;
	return 0;

err_dma_drv_exit:
err_irq:
	iounmap(dma_drv_info->reg_base_addr);
err_ioremap:
err_resource:
	devm_kfree(dev, dma_drv_info);
err_kzalloc:
	misc_deregister(&soundtrigger_dma_drv_device);
err_register:
err_nodev:
	loge( "dma driver init fail.\n");
	return err;
}

static int32_t soundtrigger_dma_drv_remove(struct platform_device *pdev)
{
	uint32_t dma_num;
	uint32_t buffer_num;
	struct device *dev = &pdev->dev;
	struct soundtrigger_dma_drv_info *dma_drv_info = g_dma_drv_info;
	struct soundtrigger_pcm_info *fast_pcm_info = NULL;
	struct soundtrigger_pcm_info *normal_pcm_info = NULL;

	if (!dma_drv_info) {
		loge("dma_drv_info NULL.\n");
		return -ENOENT;
	}

	fast_pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_FAST]);
	normal_pcm_info = &(dma_drv_info->st_pcm_info[SOUNDTRIGGER_PCM_NORMAL]);

	for (dma_num = 0; dma_num < DMA_PORT_NUM; dma_num++) {
		for (buffer_num = 0; buffer_num < PCM_SWAP_BUFFER_NUM; buffer_num++) {
			/* free fast swap buffer and dma config */
			if (fast_pcm_info->buffer[dma_num][buffer_num]) {
				dma_free_coherent(dma_drv_info->dev, fast_pcm_info->buffer_size, fast_pcm_info->buffer[dma_num][buffer_num],
					fast_pcm_info->buffer_physical_addr[dma_num][buffer_num]);
				fast_pcm_info->buffer[dma_num][buffer_num] = NULL;
			}

			if (fast_pcm_info->dma_cfg[dma_num][buffer_num]) {
				dma_free_coherent(dma_drv_info->dev, sizeof(struct dma_lli_cfg), fast_pcm_info->dma_cfg[dma_num][buffer_num],
					fast_pcm_info->lli_dma_physical_addr[dma_num][buffer_num]);
				fast_pcm_info->dma_cfg[dma_num][buffer_num] = NULL;
			}

			/* free normal swap buffer and dma config */
			if (normal_pcm_info->buffer[dma_num][buffer_num]) {
				dma_free_coherent(dma_drv_info->dev, normal_pcm_info->buffer_size, normal_pcm_info->buffer[dma_num][buffer_num],
					normal_pcm_info->buffer_physical_addr[dma_num][buffer_num]);
				normal_pcm_info->buffer[dma_num][buffer_num] = NULL;
			}

			if (normal_pcm_info->dma_cfg[dma_num][buffer_num]) {
				dma_free_coherent(dma_drv_info->dev, sizeof(struct dma_lli_cfg), normal_pcm_info->dma_cfg[dma_num][buffer_num],
					normal_pcm_info->lli_dma_physical_addr[dma_num][buffer_num]);
				fast_pcm_info->dma_cfg[dma_num][buffer_num] = NULL;
			}
		}
	}

	dma_drv_info->dma_alloc_flag = 0;

	iounmap(g_dma_drv_info->reg_base_addr);
	iounmap(g_dma_drv_info->v_slimbus_base_reg_addr);
	misc_deregister(&soundtrigger_dma_drv_device);

	if(g_dma_drv_info->soundtrigger_delay_wq) {
		cancel_delayed_work(&g_dma_drv_info->soundtrigger_delay_dma_fast_left_work);
		cancel_delayed_work(&g_dma_drv_info->soundtrigger_delay_dma_fast_right_work);
		cancel_delayed_work(&g_dma_drv_info->soundtrigger_delay_dma_normal_left_work);
		cancel_delayed_work(&g_dma_drv_info->soundtrigger_delay_dma_normal_right_work);
		flush_workqueue(g_dma_drv_info->soundtrigger_delay_wq);
		destroy_workqueue(g_dma_drv_info->soundtrigger_delay_wq);
	}

	if(g_dma_drv_info) {
		devm_kfree(dev,g_dma_drv_info);
		g_dma_drv_info = NULL;
	}

	logi( "dma remove.\n");
	return 0;
}

static const struct of_device_id soundtrigger_dma_match_table[] = {
	{ .compatible = COMP_SOUNDTRIGGER_DMA_DRV_NAME, },
	{},
};

MODULE_DEVICE_TABLE(of, soundtrigger_dma_match_table);

static struct platform_driver soundtrigger_dma_driver = {
	.driver 	= {
		.name	= "soundtrigger dma drviver",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(soundtrigger_dma_match_table),
	},
	.probe		= soundtrigger_dma_drv_probe,
	.remove 	= soundtrigger_dma_drv_remove,
};

static int32_t __init soundtrigger_dma_drv_init(void)
{
	return platform_driver_register(&soundtrigger_dma_driver);
}
module_init(soundtrigger_dma_drv_init);

static void __exit soundtrigger_dma_drv_exit(void)
{
	platform_driver_unregister(&soundtrigger_dma_driver);
}
module_exit(soundtrigger_dma_drv_exit);

MODULE_AUTHOR("Yue Yu <yuyue321@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon (R) Soundtrigger DMA Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_VERSION(HISILICON_SOUNDTRIGGER_DMA_DRIVER_VERSION);

