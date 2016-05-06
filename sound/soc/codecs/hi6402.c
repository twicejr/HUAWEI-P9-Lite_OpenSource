/*
 * hi6402.c -- ALSA SoC HI6402 codec driver
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/wakelock.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <asm/io.h>
#include <linux/debugfs.h>

#include <hisi/hilog.h>
#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/hisi/hi64xx/hi64xx_compat.h>
#include <linux/hisi/hi64xx_hifi_misc.h>
#include <linux/hisi/hi64xx/hi64xx_vad.h>

#include <linux/hisi/hi64xx/hi6402_regs.h>
#include "huawei_platform/audio/anc_hs_interface.h"
#include "../../../drivers/hisi/slimbus/slimbus.h"
#include "../../../drivers/hisi/hi6402dsp/hi6402_hifi_config.h"


/*lint -e750*/
#define HI6402_FORMATS	( SNDRV_PCM_FMTBIT_S16_LE | \
			  SNDRV_PCM_FMTBIT_S16_BE | \
			  SNDRV_PCM_FMTBIT_S24_LE | \
			  SNDRV_PCM_FMTBIT_S24_BE )

#define HI6402_RATES SNDRV_PCM_RATE_8000_96000

#define FS_8000 0x0
#define FS_16000 0x1
#define FS_32000 0x2
#define FS_48000 0x4
#define FS_96000 0x5

#define HI6402_IRQ_NUM (32)

/* reset audio clk, this function just for 3mic */
#define HI6402_DP_CLK_BIT 0x0
#define HI6402_3MIC_SENCE_BIT   0x1

#define HI6402_WAIT_PLL_LOCK_TIME 10
#define HI6402_ENSURE_PLL_LOCK_TIME 3

#define HAC_ENABLE                   1
#define HAC_DISABLE                  0
#define GPIO_PULL_UP                 1
#define GPIO_PULL_DOWN               0

static int hac_en_gpio = 0;

static int hac_switch = 0;

enum track_state {
	TRACK_FREE = 0,
	TRACK_STARTUP = 1,
};

enum s1s3_up_state_t {
	S1S3_UP_NULL = 0,
	S1S3_UP_AUDIO_CAPTURE = 1,
	S1S3_UP_VOICEUP_16K = 2,
	S1S3_UP_VOICEUP_8K = 3,
	S1_UP_NULL = 4,
	S3_UP_NULL = 5,
};

enum hi6402_cp_clk_div {
	HI6402_CP_CLK_DIV_2 = 0,
	HI6402_CP_CLK_DIV_4 = 1,
	HI6402_CP_CLK_DIV_8 = 2,
	HI6402_CP_CLK_DIV_16 = 3,
	HI6402_CP_CLK_DIV_32 = 4,
	HI6402_CP_CLK_DIV_64 = 5,
	HI6402_CP_CLK_DIV_128 = 6,
	HI6402_CP_CLK_DIV_256 = 7,
};

enum rec_pll_offset{
	MAD_BIT = 0,
	REC_BIT,
};

struct hi6402_board_cfg {
	/* board defination */
	int mic_num;
	int hac_gpio;
	bool use_stereo_smartpa;
	unsigned int mic2_source;
};

/* codec private data */
struct hi6402_platform_data {
	struct snd_soc_codec *codec;
	struct device_node *node;
	struct hi_cdc_ctrl *cdc_ctrl;
	struct hi64xx_resmgr *resmgr;
	struct hi64xx_irq *irqmgr;
	struct hi64xx_mbhc *mbhc;
	struct hi6402_board_cfg board_cfg;
	struct mutex rw_mutex;
	struct mutex ref_mutex;
	unsigned int mm_reg;
	unsigned int ref_voice_clk;
	unsigned int ref_audio_tx;
	unsigned int ref_audio_rx;
	slimbus_track_param_t voice_params;
	slimbus_track_param_t capture_params;
	enum track_state voicedown_state;
	enum track_state voiceup_8k_state;
	enum track_state voiceup_16k_state;
	enum track_state capture_state;
	enum s1s3_up_state_t s1s3_up_state;
	bool hsr_power_on;
	bool hsl_power_on;
	bool main_mic_power_on;
	bool mic2_power_on;
};

struct snd_soc_codec *g_hi6402_codec = NULL;
static unsigned int rec_state = 0;

static struct mbhc_reg hi6402_mbhc_reg = {
	.irq_source_reg = 0x2000701c,
	.irq_mbhc_2_reg = 0x20007016,
	.ana_60_reg = 0x200070dd,
	.saradc_value_reg = 0x200070f1,
	.mbhc_vref_reg = 0x200070e0,
	.sar_cfg_reg = 0x200070df,
	.micbias_eco_reg = 0x200070e1,
	.hsdet_ctrl_reg = 0x200070de,
};

static int hac_gpio_switch(int hac_number)
{
	if (!hac_en_gpio) {
		pr_err("%s: Failed to get the hac gpio", __func__);
		return 0;
	}

	if (HAC_ENABLE == hac_number) {
		pr_debug("%s: Enable hac enable gpio %u\n",
		__func__, hac_en_gpio);
		gpio_direction_output(hac_en_gpio, GPIO_PULL_UP);
	} else {
		pr_debug("%s: Disable hac enable gpio %u\n",
		__func__, hac_en_gpio);
		gpio_direction_output(hac_en_gpio, GPIO_PULL_DOWN);
	}

	return hac_number;
}

static const char * const hac_switch_text[] = {"OFF", "ON"};

static const struct soc_enum hac_switch_enum[] = {
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(hac_switch_text), hac_switch_text),
};

static int hac_switch_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	if (NULL == kcontrol || NULL == ucontrol) {
		pr_err("%s: input pointer is null\n", __func__);
		return 0;
	}

	pr_debug("%s: hac_switch = %d\n", __func__, hac_switch);
	ucontrol->value.integer.value[0] = hac_switch;

	return 0;
}

static int hac_switch_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	int ret = 0;

	if (NULL == kcontrol || NULL == ucontrol) {
		pr_err("%s: input pointer is null\n", __func__);
		return ret;
	}

	hac_switch = ucontrol->value.integer.value[0];
	pr_debug("%s: hac_switch = %d\n", __func__, hac_switch);
	ret = hac_gpio_switch(hac_switch);

	return ret;
}

void hi6402_set_rec_pll(struct snd_soc_codec *codec,unsigned int offset,unsigned int state)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	unsigned int m_rec_state = rec_state;

	BUG_ON(NULL == priv);

	if((MAD_BIT == offset) && (false == state) && (m_rec_state & (1<<REC_BIT))) {
		hi64xx_resmgr_request_pll(priv->resmgr , PLL_HIGH);
	} else if ((REC_BIT == offset) && (true == state) && (0 == (m_rec_state & (1<<MAD_BIT)))) {
		hi64xx_resmgr_request_pll(priv->resmgr , PLL_HIGH);
	} else if ((REC_BIT == offset) && (false == state) && (0 == (m_rec_state & (1<<MAD_BIT)))) {
		hi64xx_resmgr_release_pll(priv->resmgr , PLL_HIGH);
	} else if ((MAD_BIT == offset) && (true == state) && (m_rec_state & (1<<REC_BIT))) {
		hi64xx_resmgr_release_pll(priv->resmgr , PLL_HIGH);
	} else {
		dev_info(codec->dev, "%s : donothing, param is offset %d, state %d, m_rec_state %d. \n",
			__FUNCTION__, offset, state, m_rec_state);
	}

	if(true == state)
		rec_state = m_rec_state | (1 << offset);
	else
		rec_state = m_rec_state & (~(1 << offset));
}

int hi6402_mad_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_resmgr_request_pll(priv->resmgr , PLL_LOW);
		hi6402_set_rec_pll(codec, MAD_BIT, true);
		hi64xx_update_bits(codec, HI6402_MISC_CLK_EN, 1 << HI6402_MAD_CLK1_EN_BIT, 1 << HI6402_MAD_CLK1_EN_BIT);
		hi64xx_update_bits(codec, HI6402_MISC_CLK_EN, 1 << HI6402_MAD_CLK0_EN_BIT, 1 << HI6402_MAD_CLK0_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_MISC_CLK_EN, 1 << HI6402_MAD_CLK1_EN_BIT, 0);
		hi64xx_update_bits(codec, HI6402_MISC_CLK_EN, 1 << HI6402_MAD_CLK0_EN_BIT, 0);
		hi6402_set_rec_pll(codec, MAD_BIT, false);
		hi64xx_resmgr_release_pll(priv->resmgr , PLL_LOW);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_rec_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6402_set_rec_pll(codec, REC_BIT, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6402_set_rec_pll(codec, REC_BIT, false);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_audio_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	dev_info(codec->dev, "%s : power mode event: 0x%x\n", __FUNCTION__, event);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_CODEC_DP_CLKEN, 1 << HI6402_CODEC_DP_CLKEN_BIT, 1 << HI6402_CODEC_DP_CLKEN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_CODEC_DP_CLKEN, 1 << HI6402_CODEC_DP_CLKEN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_pll_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_resmgr_request_pll(priv->resmgr , PLL_HIGH);
		/* slimbus master framer is hi6402 */
		usleep_range(2000, 2050);
		slimbus_switch_framer(SLIMBUS_DEVICE_HI6402, SLIMBUS_FRAMER_CODEC);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* slimbus master framer is soc */
		slimbus_switch_framer(SLIMBUS_DEVICE_HI6402, SLIMBUS_FRAMER_SOC);
		usleep_range(2000, 2050);
		hi64xx_resmgr_release_pll(priv->resmgr , PLL_HIGH);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void hi6402_audio_rx_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->ref_mutex);
	if (enable) {
		if (1 == ++priv->ref_audio_rx)
			hi64xx_update_bits(codec, HI6402_S1_PORT_CFG_L, 1 << HI6402_IF_RX_EN_BIT, 1 << HI6402_IF_RX_EN_BIT);
	} else {
		if (0 == priv->ref_audio_rx) {
			dev_err(codec->dev, "%s : ref_audio_rx error : %d\n", __FUNCTION__, priv->ref_audio_rx);
		} else {
			if (0 == --priv->ref_audio_rx)
				hi64xx_update_bits(codec, HI6402_S1_PORT_CFG_L, 1 << HI6402_IF_RX_EN_BIT, 0);
		}
	}
	mutex_unlock(&priv->ref_mutex);
}

static void hi6402_audio_tx_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->ref_mutex);
	if (enable) {
		if (1 == ++priv->ref_audio_tx)
			hi64xx_update_bits(codec, HI6402_S1_PORT_CFG_L, 1 << HI6402_IF_TX_EN_BIT, 1 << HI6402_IF_TX_EN_BIT);
	} else {
		if (0 == priv->ref_audio_tx) {
			dev_err(codec->dev, "%s : ref_audio_tx error : %d\n", __FUNCTION__, priv->ref_audio_tx);
		} else {
			if (0 == --priv->ref_audio_tx)
				hi64xx_update_bits(codec, HI6402_S1_PORT_CFG_L, 1 << HI6402_IF_TX_EN_BIT, 0);
		}
	}
	mutex_unlock(&priv->ref_mutex);
}

static void hi6402_voice_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->ref_mutex);
	if (enable) {
		if (1 == ++priv->ref_voice_clk) {
			hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 1 << HI6402_PORT_CLK_EN, 1 << HI6402_PORT_CLK_EN);
			hi64xx_update_bits(codec, HI6402_S3_PORT_CFG_L, 1 << HI6402_IF_TX_EN_BIT, 1 << HI6402_IF_TX_EN_BIT);
			hi64xx_update_bits(codec, HI6402_S3_PORT_CFG_L, 1 << HI6402_IF_RX_EN_BIT, 1 << HI6402_IF_RX_EN_BIT);
		}
	} else {
		if (0 == priv->ref_voice_clk) {
			dev_err(codec->dev, "%s : ref_voice_clk error : %d\n", __FUNCTION__, priv->ref_voice_clk);
		} else {
			if (0 == --priv->ref_voice_clk) {
				hi64xx_update_bits(codec, HI6402_S3_PORT_CFG_L, 1 << HI6402_IF_RX_EN_BIT, 0);
				hi64xx_update_bits(codec, HI6402_S3_PORT_CFG_L, 1 << HI6402_IF_TX_EN_BIT, 0);
				hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 1 << HI6402_PORT_CLK_EN, 0);
			}
		}
	}
	mutex_unlock(&priv->ref_mutex);
}

int hi6402_s1_tx_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6402_audio_tx_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6402_audio_tx_clk_enable(codec, false);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s1_rx_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6402_audio_rx_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6402_audio_rx_clk_enable(codec, false);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s3_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6402_voice_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6402_voice_clk_enable(codec, false);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_slimbus_port01_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	dev_info(codec->dev, "[%s:%d], event:0x%x, \n", __FUNCTION__, __LINE__, event);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_0, HI6402_FS_SLIM_P01_48K);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_PLAY, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_PLAY);
		break;
	case SND_SOC_DAPM_POST_PMD:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_PLAY);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_PLAY);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_slimbus_port89_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	slimbus_track_param_t  *slimbus_params = NULL;

	BUG_ON(NULL == priv);

	slimbus_params = &(priv->voice_params);
	dev_info(codec->dev, "[%s:%d], event:0x%x, \n", __FUNCTION__, __LINE__, event);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (slimbus_params->rate == 8000) {
			/* sample rate  8K */
			snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_4, 0);
		} else if (slimbus_params->rate == 16000) {
			/* sample rate  16K */
			snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_4, 0x11);
		}
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);

		/*
		*bugfix:wait 4ms to clear fifo
		*fifo size 32,samplerate 8k,time 4ms
		*time * samplerate = fifo size
		*/
		usleep_range(4000, 4050);

		hi64xx_update_bits(codec, HI6402_DACL_MIXER_SEL_0, 1 << HI6402_DACL_MIXER_MDM_BIT, 0);
		hi64xx_update_bits(codec, HI6402_DACR_MIXER_SEL_0, 1 << HI6402_DACR_MIXER_MDM_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		hi64xx_update_bits(codec, HI6402_DACL_MIXER_SEL_0, 1 << HI6402_DACL_MIXER_MDM_BIT, 1 << HI6402_DACL_MIXER_MDM_BIT);
		hi64xx_update_bits(codec, HI6402_DACR_MIXER_SEL_0, 1 << HI6402_DACR_MIXER_MDM_BIT, 1 << HI6402_DACL_MIXER_MDM_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_slimbus_port1415_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	dev_info(codec->dev, "[%s:%d], event:0x%x, \n", __FUNCTION__, __LINE__, event);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* sample rate  48k */
		hi64xx_update_bits(codec, HI6402_SC_FS_SLIM_CTRL_7, 0x77, 0x44);
		hi64xx_update_bits(codec, HI6402_SC_RES_RW_REG_2, 1 << 0x6, 1 << 0x6);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_ECREF, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_ECREF);
		break;
	case SND_SOC_DAPM_POST_PMD:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_ECREF);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_ECREF);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s1_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 1 << HI6402_PORT_CLK_EN, 1 << HI6402_PORT_CLK_EN);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 1 << HI6402_PORT_CLK_EN, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_adc1r_pga_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC1R_EN_BIT, 1 << HI6402_ADC1R_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC1R_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_adc1l_pga_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC1L_EN_BIT, 1 << HI6402_ADC1L_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC1L_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_adc0r_pga_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0R_EN_BIT, 1 << HI6402_ADC0R_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0R_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_adc0l_pga_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0L_EN_BIT, 1 << HI6402_ADC0L_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0L_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s1_ol_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OL_EN_BIT, 1 << HI6402_S1_PGA_OL_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OL_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s1_or_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OR_EN_BIT, 1 << HI6402_S1_PGA_OR_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OR_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s3_ol_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OL_EN_BIT, 1 << HI6402_S3_PGA_OL_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OL_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_s3_or_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OR_EN_BIT, 1 << HI6402_S3_PGA_OR_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OR_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_modem_audio_8k_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	dev_info(codec->dev, "%s: set 8K mode.\n", __FUNCTION__);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_H, 0x77, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_SRC_IN_MODE_CGF, 0xEE, 0xAA);
		hi64xx_update_bits(codec, HI6402_S3_SRC_OUT_MODE_CGF, 0x36, 0x24);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 1 << HI6402_S3_IL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 1 << HI6402_S3_OL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 1 << HI6402_S3_OR_SRC_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		dev_info(codec->dev, "%s: modem audio test finished, do nothing.\n", __FUNCTION__);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_modem_audio_16k_switch_power_mode_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	slimbus_track_param_t  *slimbus_params = NULL;

	BUG_ON(NULL == priv);

	slimbus_params = &(priv->voice_params);
	dev_info(codec->dev, "%s: set 16K mode.\n", __FUNCTION__);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x01);
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_H, 0x77, 0x11);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_SRC_IN_MODE_CGF, 0xEE, 0x22);
		hi64xx_update_bits(codec, HI6402_S3_SRC_OUT_MODE_CGF, 0x36, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 1 << HI6402_S3_IL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 1 << HI6402_S3_OL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 1 << HI6402_S3_OR_SRC_BIT);
		slimbus_params->rate = 16000;
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_4, 0x11);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		break;
	case SND_SOC_DAPM_POST_PMD:
		dev_info(codec->dev, "%s: modem audio test finished, do nothing.\n", __FUNCTION__);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static inline void hi6402_cp_clk_select(struct snd_soc_codec *codec, enum hi6402_cp_clk_div div)
{
	/* cp clk div */
	hi64xx_update_bits(codec, HI6402_CP_CLK_SEL_REG, 0x7, div);
}

int hi6402_cp1_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* cp-pop clk on */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_POP_CLK_PD_BIT, 0);
		/* cp1 clk on */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_CLK_PD_BIT, 0);
		/* cp1 on */
		hi64xx_update_bits(codec, HI6402_CP_PD_REG, 1 << HI6402_CP_PD_BIT, 0);
		msleep(20);
		/* cp1 soft off */
		hi64xx_update_bits(codec, HI6402_CP_PD_REG, 1 << HI6402_CP_SOFT_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* cp1 soft en */
		hi64xx_update_bits(codec, HI6402_CP_PD_REG, 1 << HI6402_CP_SOFT_BIT, 1 << HI6402_CP_SOFT_BIT);
		/* cp1 on */
		hi64xx_update_bits(codec, HI6402_CP_PD_REG, 1 << HI6402_CP_PD_BIT, 1 << HI6402_CP_PD_BIT);
		/* cp1 clk pd */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_CLK_PD_BIT, 1 << HI6402_CLK_PD_BIT);
		/* cp-pop clk pd */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_POP_CLK_PD_BIT, 1 << HI6402_POP_CLK_PD_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_cp2_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* cp-pop clk on */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_POP_CLK_PD_BIT, 0);
		/* cp2_clk_pd clr */
		hi64xx_update_bits(codec, HI6402_CP2_CLK_PD_REG, 1 << HI6402_CP2_CLK_PD_BIT, 0);
		/* cp2 on */
		hi64xx_update_bits(codec, HI6402_CP2_PD_REG, 1 << HI6402_CP2_PD_BIT, 0);
		msleep(1);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* cp2 pd */
		hi64xx_update_bits(codec, HI6402_CP2_PD_REG, 1 << HI6402_CP2_PD_BIT, 1 << HI6402_CP2_PD_BIT);
		/* cp2_clk_pd set */
		hi64xx_update_bits(codec, HI6402_CP2_CLK_PD_REG, 1 << HI6402_CP2_CLK_PD_BIT, 1 << HI6402_CP2_CLK_PD_BIT);
		/* cp-pop clk pd */
		hi64xx_update_bits(codec, HI6402_POP_CLK_PD_REG, 1 << HI6402_POP_CLK_PD_BIT, 1 << HI6402_POP_CLK_PD_BIT);
		msleep(1);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void hi6402_hp_power_on(struct snd_soc_codec *codec)
{
	unsigned int hsl_reg_value = snd_soc_read(codec, HI6402_HPL_PGA_CFG_REG);
	unsigned int hsr_reg_value = snd_soc_read(codec, HI6402_HPR_PGA_CFG_REG);
	unsigned int hsl_pga_value = hsl_reg_value & 0x3F;
	unsigned int hsr_pga_value = hsr_reg_value & 0x3F;
	unsigned int min_pga = (hsl_pga_value<hsr_pga_value? hsl_pga_value:hsr_pga_value);
	int i = 0;

	hi64xx_update_bits(codec, HI6402_HPL_POP_CFG1_REG, 0x3F, 0x01F);
	/* -32dB init */
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 0x3F, 0x00);
	hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 0x3F, 0x00);
	/* dac power on */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0xA0, 0x00);
	msleep(50);
	/* dac hp on */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0x50, 0x00);
	/* dac hp mute off */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0x0C, 0x00);
	/* hp on */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0x03, 0x00);
	msleep(100);
	/* hp mute off */
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 1 << HI6402_HPL_PGA_MUTE_BIT, 0);
	hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 1 << HI6402_HPR_PGA_MUTE_BIT, 0);
	/* gain on */
	for (i += 1; i <= min_pga; i++){
		hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 0x3F, i);
		hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 0x3F, i);
	}

	/* zero cross on */
	hi64xx_update_bits(codec, HI6402_ZCD_CFG_REG, 1 << HI6402_HPL_ZCD_BIT, 1 << HI6402_HPL_ZCD_BIT);
	hi64xx_update_bits(codec, HI6402_ZCD_CFG_REG, 1 << HI6402_HPR_ZCD_BIT, 1 << HI6402_HPR_ZCD_BIT);
}

static void hi6402_hp_power_off(struct snd_soc_codec *codec)
{
	unsigned int hsl_reg_value = snd_soc_read(codec, HI6402_HPL_PGA_CFG_REG);
	unsigned int hsr_reg_value = snd_soc_read(codec, HI6402_HPR_PGA_CFG_REG);
	unsigned int hsl_pga_value = hsl_reg_value & 0x3F;
	unsigned int hsr_pga_value = hsr_reg_value & 0x3F;
	unsigned int min_pga = (hsl_pga_value<hsr_pga_value? hsl_pga_value:hsr_pga_value);
	int i = min_pga;

	/* gain off */
	for (i -= 1; i >= 0; i--){
		hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 0x3F, i);
		hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 0x3F, i);
	}
	/* hp mute */
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 1 << HI6402_HPL_PGA_MUTE_BIT, 1 << HI6402_HPL_PGA_MUTE_BIT);
	hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 1 << HI6402_HPR_PGA_MUTE_BIT, 1 << HI6402_HPR_PGA_MUTE_BIT);
	/* hp off */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0x03, 0x03);
	msleep(80);
	/* dac hp mute */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0x0C, 0x0C);
	/* dac power pd */
	/* dac hp opd */
	hi64xx_update_bits(codec, HI6402_DAC_HP_PD_REG, 0xF0, 0xF0);
	msleep(50);
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 0x3F, min_pga);
	hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 0x3F, min_pga);
	hi64xx_update_bits(codec, HI6402_HPL_POP_CFG1_REG, 0x3F, 0x013);
	/* zero cross off */
	hi64xx_update_bits(codec, HI6402_ZCD_CFG_REG, 1 << HI6402_HPL_ZCD_BIT, 0);
	hi64xx_update_bits(codec, HI6402_ZCD_CFG_REG, 1 << HI6402_HPR_ZCD_BIT, 0);
}

int hi6402_hpl_drv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->hsl_power_on = true;
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6402_hp_power_on(codec);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6402_hp_power_off(codec);
		priv->hsl_power_on = false;
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_hpr_drv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* hpr dac on */
		priv->hsr_power_on = true;
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6402_hp_power_on(codec);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6402_hp_power_off(codec);
		priv->hsr_power_on = false;
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_ep_drv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* ep dac on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_EP_PD_BIT, 0);
		/* ep pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_EP_PD_BIT, 0);
		/* ep mute off */
		hi64xx_update_bits(codec, HI6402_EP_PGA_CFG_REG, 1 << HI6402_EP_PGA_MUTE_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* ep mute on */
		hi64xx_update_bits(codec, HI6402_EP_PGA_CFG_REG, 1 << HI6402_EP_PGA_MUTE_BIT, 1 << HI6402_EP_PGA_MUTE_BIT);
		/* ep pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_EP_PD_BIT, 1 << HI6402_EP_PD_BIT);
		/* ep dac pb */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_EP_PD_BIT, 1 << HI6402_DAC_EP_PD_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_lol_drv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* lol dac on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_LOL_PD_BIT, 0);
		/* lol pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_LOL_PD_BIT, 0);
		/* lol mute off */
		hi64xx_update_bits(codec, HI6402_LOL_PGA_CFG_REG, 1 << HI6402_LOL_PGA_MUTE_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* lol mute off */
		hi64xx_update_bits(codec, HI6402_LOL_PGA_CFG_REG, 1 << HI6402_LOL_PGA_MUTE_BIT, 1 << HI6402_LOL_PGA_MUTE_BIT);
		/* lol pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_LOL_PD_BIT, 1 << HI6402_LOL_PD_BIT);
		/* lol dac pb */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_LOL_PD_BIT, 1 << HI6402_DAC_LOL_PD_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_lor_drv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* lor dac on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_LOR_PD_BIT, 0);
		/* lor pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_LOR_PD_BIT, 0);
		/* lor mute off */
		hi64xx_update_bits(codec, HI6402_LOR_PGA_CFG_REG, 1 << HI6402_LOR_PGA_MUTE_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* lor mute off */
		hi64xx_update_bits(codec, HI6402_LOR_PGA_CFG_REG, 1 << HI6402_LOR_PGA_MUTE_BIT, 1 << HI6402_LOR_PGA_MUTE_BIT);
		/* lor pga on */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_LOR_PD_BIT, 1 << HI6402_LOR_PD_BIT);
		/* lor dac pb */
		hi64xx_update_bits(codec, HI6402_DAC_EP_LO_PD_REG, 1 << HI6402_DAC_LOR_PD_BIT, 1 << HI6402_DAC_LOR_PD_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_mainmic_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* main pga mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_MAIN_PGA_MUTE1_BIT, 0);
		/* main pga mute2 */
		hi64xx_update_bits(codec, HI6402_MAIN_PGA_SEL_REG, 1 << HI6402_MAIN_PGA_MUTE2_BIT, 0);
		/* main pga on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_MAINPGA_PD_BIT, 0);
		/* main pga unlock bypass */
		//hi6402_dapm_reg_set_bit(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, HI6402_MAIN_PGA_MUTE_UNLOCK_BIT);
		/* adc0l on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC0L_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* adc0l pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC0L_PD_BIT, 1 << HI6402_ADC0L_PD_BIT);
		/* main pga unlock bypass */
		//hi6402_dapm_reg_clr_bit(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, HI6402_MAIN_PGA_MUTE_UNLOCK_BIT);
		/* main pga pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_MAINPGA_PD_BIT, 1 << HI6402_MAINPGA_PD_BIT);
		/* main pga mute2 */
		hi64xx_update_bits(codec, HI6402_MAIN_PGA_SEL_REG, 1 << HI6402_MAIN_PGA_MUTE2_BIT, 1 << HI6402_MAIN_PGA_MUTE2_BIT);
		/* main pga mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_MAIN_PGA_MUTE1_BIT, 1 << HI6402_MAIN_PGA_MUTE1_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}
int hi6402_auxmic_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* main pga mute1 */
		hi64xx_update_bits(codec, HI6402_AUX_PGA_SEL_REG, 1 << HI6402_AUX_PGA_MUTE1_BIT, 0);
		/* main pga mute2 */
		hi64xx_update_bits(codec, HI6402_AUX_PGA_SEL_REG, 1 << HI6402_AUX_PGA_MUTE2_BIT, 0);
		/* aux pga on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_AUXPGA_PD_BIT, 0);
		/* aux pga unlock bypass */
		//hi6402_dapm_reg_set_bit(codec, HI6402_AUX_PGA_SEL_REG, HI6402_AUX_PGA_MUTE_UNLOCK_BIT);
		/* adc0r on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC0R_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* adc0r pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC0R_PD_BIT, 1 << HI6402_ADC0R_PD_BIT);
		/* aux pga unlock bypass */
		//hi6402_dapm_reg_clr_bit(codec, HI6402_AUX_PGA_SEL_REG, HI6402_AUX_PGA_MUTE_UNLOCK_BIT);
		/* aux pga pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_AUXPGA_PD_BIT, 1 << HI6402_AUXPGA_PD_BIT);
		/* main pga mute2 */
		hi64xx_update_bits(codec, HI6402_AUX_PGA_SEL_REG, 1 << HI6402_AUX_PGA_MUTE2_BIT, 1 << HI6402_AUX_PGA_MUTE2_BIT);
		/* main pga mute1 */
		hi64xx_update_bits(codec, HI6402_AUX_PGA_SEL_REG, 1 << HI6402_AUX_PGA_MUTE1_BIT, 1 << HI6402_AUX_PGA_MUTE1_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_lineinl_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* lineinl mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_LINEL_PGA_MUTE1_BIT, 0);
		/* lineinl mute2 */
		hi64xx_update_bits(codec, HI6402_LINEL_PGA_SEL_REG, 1 << HI6402_LINEL_PGA_MUTE2_BIT, 0);
		/* lineinl pga on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_LINEPGAL_PD_BIT, 0);
		/* adc1l on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC1L_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* adc1l pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC1L_PD_BIT, 1 << HI6402_ADC1L_PD_BIT);
		/* lineinl pga pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_LINEPGAL_PD_BIT, 1 << HI6402_LINEPGAL_PD_BIT);
		/* lineinl mute2 */
		hi64xx_update_bits(codec, HI6402_LINEL_PGA_SEL_REG, 1 << HI6402_LINEL_PGA_MUTE2_BIT, 1 << HI6402_LINEL_PGA_MUTE2_BIT);
		/* lineinl mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_LINEL_PGA_MUTE1_BIT, 1 << HI6402_LINEL_PGA_MUTE1_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_lineinr_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* lineinr mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_LINER_PGA_MUTE1_BIT, 0);
		/* lineinr mute2 */
		hi64xx_update_bits(codec, HI6402_LINER_PGA_SEL_REG, 1 << HI6402_LINER_PGA_MUTE2_BIT, 0);
		/* lineinr pga on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_LINEPGAR_PD_BIT, 0);
		/* adc1r on */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC1R_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* adc1rl pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_ADC1R_PD_BIT, 1 << HI6402_ADC1R_PD_BIT);
		/* lineinr pga pd */
		hi64xx_update_bits(codec, HI6402_ADC_PD_REG, 1 << HI6402_LINEPGAR_PD_BIT, 1 << HI6402_LINEPGAR_PD_BIT);
		/* lineinr mute2 */
		hi64xx_update_bits(codec, HI6402_LINER_PGA_SEL_REG, 1 << HI6402_LINER_PGA_MUTE2_BIT, 1 << HI6402_LINER_PGA_MUTE2_BIT);
		/* lineinr mute1 */
		hi64xx_update_bits(codec, HI6402_ADC_PGA_MUTE1_SEL_REG, 1 << HI6402_LINER_PGA_MUTE1_BIT, 1 << HI6402_LINER_PGA_MUTE1_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_mad_src_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* s1_ol_src_cfg 96KHz to 16KHz */
		hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 1 << HI6402_OL_SRC_FS_CFG, 1 << HI6402_OL_SRC_FS_CFG);
		hi64xx_update_bits(codec, HI6402_S1_SRC_OUT_MODE_CGF, 0x3<<HI6402_S1_SRC_OL_MODE_BIT, 0x2<<HI6402_S1_SRC_OL_MODE_BIT);
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_SRC_OL_EN_BIT, 1 << HI6402_S1_SRC_OL_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_SRC_OL_EN_BIT, 0);
		/* s1_ol_src_cfg 48KHz to 48KHz */
		hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 1 << HI6402_OL_SRC_FS_CFG, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_hpdac_i2v_cfg_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* hpdac high performance */
		/* i2v 1k & max current & max ibias */
		snd_soc_write(codec, HI6402_DAC_HPL_I2V_CFG_REG, 0x0F);
		snd_soc_write(codec, HI6402_DAC_HPR_I2V_CFG_REG, 0x0F);
		/* 5uA */
		snd_soc_write(codec, HI6402_ANA_IB05_HP_REG, 0x2D);
		/* cp2 clk -> 768k */
		hi64xx_update_bits(codec, HI6402_CP2_CLK_PD_REG, 0x1C, 0x0C);
		/* DIG PGA GAIN -5dB */
		snd_soc_write(codec, HI6402_DACL_PGA_GAIN_CFG_REG, 0xFB);
		snd_soc_write(codec, HI6402_DACR_PGA_GAIN_CFG_REG, 0xFB);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* hpdac lower power */
		/* cp2 clk -> 48k */
		hi64xx_update_bits(codec, HI6402_CP2_CLK_PD_REG, 0x1C, 0x1C);
		/* 4uA */
		snd_soc_write(codec, HI6402_ANA_IB05_HP_REG, 0x1B);
		/* i2v 8k & 3/4 current & 1/8 ibias */
		snd_soc_write(codec, HI6402_DAC_HPL_I2V_CFG_REG, 0x92);
		snd_soc_write(codec, HI6402_DAC_HPR_I2V_CFG_REG, 0x92);
		/* DIG PGA GAIN -9dB */
		snd_soc_write(codec, HI6402_DACL_PGA_GAIN_CFG_REG, 0xF7);
		snd_soc_write(codec, HI6402_DACR_PGA_GAIN_CFG_REG, 0xF7);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void hi6402_s1s3_up_state_switch(struct snd_soc_codec *codec, struct hi6402_platform_data *priv)
{
	slimbus_track_param_t  *slimbus_params = &(priv->capture_params);

	memset(slimbus_params, 0, sizeof(slimbus_track_param_t));
	dev_info(codec->dev, "[%s:%d] state:%#x !\n", __FUNCTION__, __LINE__, priv->s1s3_up_state);

	if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
		slimbus_params->channels = 4;
	} else {
		slimbus_params->channels = 2;
	}

	switch(priv->s1s3_up_state) {
	case S1S3_UP_AUDIO_CAPTURE:
		slimbus_params->rate = 48000;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE, slimbus_params);
		/* sample rate  48K */
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_1, HI6402_FS_SLIM_P23_48K);
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_5, 0x44);
		hi64xx_update_bits(codec, HI6402_SC_RES_RW_REG_2, 0x11, 0x11);
		hi64xx_update_bits(codec, HI6402_SLIM_CTRL3, 1 << HI6402_SLIM_CTRL3_BIT1, 1 << HI6402_SLIM_CTRL3_BIT1);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE);
		break;
	case S1S3_UP_VOICEUP_16K:
		slimbus_params->rate = 16000;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP, slimbus_params);
		/* sample rate  16k */
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_1, 0x11);
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_5, 0x11);
		hi64xx_update_bits(codec, HI6402_SC_RES_RW_REG_2, 0x11, 0x11);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		/* dnlink sample rate change */
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_4, 0x11);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		break;
	case S1S3_UP_VOICEUP_8K:
		slimbus_params->rate = 8000;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP, slimbus_params);
		/* sample rate  8k */
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_1, 0);
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_5, 0);
		hi64xx_update_bits(codec, HI6402_SC_RES_RW_REG_2, 0x11, 0x11);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		/* dnlink sample rate change */
		snd_soc_write(codec, HI6402_SC_FS_SLIM_CTRL_4, 0);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN, NULL);
		slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		break;
	case S1S3_UP_NULL:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE);
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		/* dnlink sample rate change */
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		break;
	case S1_UP_NULL:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_AUDIO_CAPTURE);
		break;
	case S3_UP_NULL:
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_UP);
		/* dnlink sample rate change */
		slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_VOICE_DOWN);
		break;
	default:
		break;
	}
}

int hi6402_audio_capture_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	dev_info(codec->dev, "[%s:%d] event:%#x ch:%d, audio:%#x, 16k:%#x, 8k:%#x !\n",__FUNCTION__, __LINE__,
		event, priv->board_cfg.mic_num, priv->capture_state, priv->voiceup_16k_state, priv->voiceup_8k_state);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->capture_state = TRACK_STARTUP;
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			if (priv->voiceup_8k_state == TRACK_FREE && priv->voiceup_16k_state == TRACK_FREE) {
				priv->s1s3_up_state = S1S3_UP_AUDIO_CAPTURE;
				hi6402_s1s3_up_state_switch(codec, priv);
			}
		} else {
			priv->s1s3_up_state = S1S3_UP_AUDIO_CAPTURE;
			hi6402_s1s3_up_state_switch(codec, priv);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		priv->capture_state = TRACK_FREE;
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			if (priv->voiceup_8k_state == TRACK_FREE && priv->voiceup_16k_state == TRACK_FREE) {
				priv->s1s3_up_state = S1S3_UP_NULL;
				hi6402_s1s3_up_state_switch(codec, priv);
			}
		} else {
			priv->s1s3_up_state = S1_UP_NULL;
			hi6402_s1s3_up_state_switch(codec, priv);
		}
		break;
	default:
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_voiceup_16k_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	dev_info(codec->dev, "[%s:%d] event:%#x audio:%#x, 16k:%#x, 8k:%#x !\n",__FUNCTION__, __LINE__,
		event, priv->capture_state, priv->voiceup_16k_state, priv->voiceup_8k_state);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->voiceup_16k_state = TRACK_STARTUP;
		priv->s1s3_up_state = S1S3_UP_VOICEUP_16K;
		hi6402_s1s3_up_state_switch(codec, priv);
		break;
	case SND_SOC_DAPM_POST_PMD:
		priv->voiceup_16k_state = TRACK_FREE;
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			if (priv->voiceup_8k_state == TRACK_FREE && priv->capture_state == TRACK_FREE) {
				priv->s1s3_up_state = S1S3_UP_NULL;
				hi6402_s1s3_up_state_switch(codec, priv);
			} else {
				if (priv->capture_state == TRACK_STARTUP && priv->voiceup_8k_state == TRACK_FREE) {
					priv->s1s3_up_state = S1S3_UP_AUDIO_CAPTURE;
					hi6402_s1s3_up_state_switch(codec, priv);
				}
			}
		} else {
			if (priv->voiceup_8k_state == TRACK_FREE && priv->voiceup_16k_state == TRACK_FREE) {
				priv->s1s3_up_state = S3_UP_NULL;
				hi6402_s1s3_up_state_switch(codec, priv);
			}
		}
		break;
	default:
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_voiceup_8k_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	dev_info(codec->dev, "[%s:%d] event:%#x audio:%#x, 16k:%#x, 8k:%#x !\n",__FUNCTION__, __LINE__,
		event, priv->capture_state, priv->voiceup_16k_state, priv->voiceup_8k_state);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->voiceup_8k_state = TRACK_STARTUP;
		priv->s1s3_up_state = S1S3_UP_VOICEUP_8K;
		hi6402_s1s3_up_state_switch(codec, priv);
		break;
	case SND_SOC_DAPM_POST_PMD:
		priv->voiceup_8k_state = TRACK_FREE;
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			if (priv->voiceup_16k_state == TRACK_FREE && priv->capture_state == TRACK_FREE) {
				priv->s1s3_up_state = S1S3_UP_NULL;
				hi6402_s1s3_up_state_switch(codec, priv);
			} else {
				if (priv->capture_state == TRACK_STARTUP && priv->voiceup_16k_state == TRACK_FREE) {
					priv->s1s3_up_state = S1S3_UP_AUDIO_CAPTURE;
					hi6402_s1s3_up_state_switch(codec, priv);
				}
			}
		} else {
			if (priv->voiceup_8k_state == TRACK_FREE && priv->voiceup_16k_state == TRACK_FREE) {
				priv->s1s3_up_state = S3_UP_NULL;
				hi6402_s1s3_up_state_switch(codec, priv);
			}
		}
		break;
	default:
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_fm_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* cp clk 96k */
		hi64xx_update_bits(codec, HI6402_CP_CLK_SEL_REG, 0x7, 0x6);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* cp clk 768k */
		hi64xx_update_bits(codec, HI6402_CP_CLK_SEL_REG, 0x7, 0x3);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_dacl_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* dacl src clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACL_SRC_EN_BIT, 1 << HI6402_DACL_SRC_EN_BIT);
		/* dacl clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACL_EN_BIT, 1 << HI6402_DACL_EN_BIT);
		/* dacl pga clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_PGA_CLK_REG, 1 << HI6402_DACL_PGA_EN_BIT, 1 << HI6402_DACL_PGA_EN_BIT);
		/* dacl src lk enable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACL_SRC_EN_BIT, 1 << HI6402_DACL_SRC_EN_BIT);
		/* dacl src up16 clk enable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16L_EN_BIT, 1 << HI6402_SRC_UP16L_EN_BIT);
		/* dacl sdm clk enable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACL_SDM_EN_BIT, 1 << HI6402_DACL_SDM_EN_BIT);
		/* dacl sdm enable */
		hi64xx_update_bits(codec, HI6402_SDM_DAC_REG, 1 << HI6402_SDM_DACL_EN_BIT, 1 << HI6402_SDM_DACL_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* dacl sdm disable */
		hi64xx_update_bits(codec, HI6402_SDM_DAC_REG, 1 << HI6402_SDM_DACL_EN_BIT, 0);
		/* dacl sdm clk disable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACL_SDM_EN_BIT, 0);
		/* dacl src up16 clk disable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16L_EN_BIT, 0);
		/* dacl src lk disable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACR_SRC_EN_BIT, 0);
		/* dacl pga clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_PGA_CLK_REG, 1 << HI6402_DACL_PGA_EN_BIT, 0);
		/* dacl clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACL_EN_BIT, 0);
		/* dacl src clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACL_SRC_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_dacr_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* dacr src clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACR_SRC_EN_BIT, 1 << HI6402_DACR_SRC_EN_BIT);
		/* dacr clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACR_EN_BIT, 1 << HI6402_DACR_EN_BIT);
		/* dacr pga clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_PGA_CLK_REG, 1 <<  HI6402_DACR_PGA_EN_BIT, 1 <<  HI6402_DACR_PGA_EN_BIT);
		/* dacr src lk enable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 <<  HI6402_DACR_SRC_EN_BIT, 1 <<  HI6402_DACR_SRC_EN_BIT);
		/* dacr src up16 clk enable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 <<  HI6402_SRC_UP16R_EN_BIT, 1 <<  HI6402_SRC_UP16R_EN_BIT);
		/* dacr sdm clk enable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 <<  HI6402_DACR_SDM_EN_BIT, 1 <<  HI6402_DACR_SDM_EN_BIT);
		/* dacr sdm enable */
		hi64xx_update_bits(codec, HI6402_SDM_DAC_REG, 1 << HI6402_SDM_DACR_EN_BIT, 1 << HI6402_SDM_DACR_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* dacr sdm disable */
		hi64xx_update_bits(codec, HI6402_SDM_DAC_REG, 1 <<  HI6402_SDM_DACR_EN_BIT, 0);
		/* dacr sdm clk disable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 <<  HI6402_DACR_SDM_EN_BIT, 0);
		/* dacr src up16 clk disable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 <<  HI6402_SRC_UP16R_EN_BIT, 0);
		/* dacr src lk disable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 <<  HI6402_DACR_SRC_EN_BIT, 0);
		/* dacrl pga clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_PGA_CLK_REG, 1 <<  HI6402_DACR_PGA_EN_BIT, 0);
		/* dacr clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 <<  HI6402_DACR_EN_BIT, 0);
		/* dacrl src clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_SRC_CLK_REG, 1 << HI6402_DACR_SRC_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_dacsl_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* dacl clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACSL_EN_BIT, 1 << HI6402_DACSL_EN_BIT);
		/* dacl src up16 clk enable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16L_EN_BIT, 1 << HI6402_SRC_UP16L_EN_BIT);
		/* dacl sdm clk enable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACSL_SDM_EN_BIT, 1 << HI6402_DACSL_SDM_EN_BIT);
		/* dacsl sdm enable */
		hi64xx_update_bits(codec, HI6402_SDM_DACS_REG, 1 << HI6402_SDM_DACSL_EN_BIT, 1 << HI6402_SDM_DACSL_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* dacsl sdm disable */
		hi64xx_update_bits(codec, HI6402_SDM_DACS_REG, 1 << HI6402_SDM_DACSL_EN_BIT, 0);
		/* dacl sdm clk disable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACSL_SDM_EN_BIT, 0);
		/* dacl src up16 clk disable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16L_EN_BIT, 0);
		/* dacl clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACSL_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_dacsr_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* dacr clk enable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACSR_EN_BIT, 1 << HI6402_DACSR_EN_BIT);
		/* dacr src up16 clk enable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16R_EN_BIT, 1 << HI6402_SRC_UP16R_EN_BIT);
		/* dacr sdm clk enable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACSR_SDM_EN_BIT, 1 << HI6402_DACSR_SDM_EN_BIT);
		/* dacsrl sdm enable */
		hi64xx_update_bits(codec, HI6402_SDM_DACS_REG, 1 << HI6402_SDM_DACSR_EN_BIT, 1 << HI6402_SDM_DACSR_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* dacsrsdm disable */
		hi64xx_update_bits(codec, HI6402_SDM_DACS_REG, 1 << HI6402_SDM_DACSR_EN_BIT, 1 << HI6402_SDM_DACSR_EN_BIT);
		/* dacr sdm clk disable */
		hi64xx_update_bits(codec, HI6402_SDM_CLK_REG, 1 << HI6402_DACSR_SDM_EN_BIT, 0);
		/* dac rsrc up16 clk disable */
		hi64xx_update_bits(codec, HI6402_EQ_SM_CLK_REG, 1 << HI6402_SRC_UP16R_EN_BIT, 0);
		/* dacrl clk disable */
		hi64xx_update_bits(codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_DACSR_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_side_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* sidetone pga & srcclk enable */
		hi64xx_update_bits(codec, HI6402_MDM_SRC_SEL, 1 << HI6402_SIDE_PGA_EN_BIT, 1 << HI6402_SIDE_PGA_EN_BIT);
		hi64xx_update_bits(codec, HI6402_MDM_SRC_SEL, 1 << HI6402_SIDE_SRC_EN_BIT, 1 << HI6402_SIDE_SRC_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* sidetone pga & src clk disable */
		hi64xx_update_bits(codec, HI6402_MDM_SRC_SEL, 1 << HI6402_SIDE_SRC_EN_BIT, 0);
		hi64xx_update_bits(codec, HI6402_MDM_SRC_SEL, 1 << HI6402_SIDE_PGA_EN_BIT, 0);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_main_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
#ifdef CONFIG_ANC_HS_INTERFACE
		if(check_anc_hs_interface_support()) {
			anc_hs_interface_5v_control(ANC_HS_ENABLE_5VOLTATE);
		}
#endif
		if(!(priv->main_mic_power_on) && (!priv->mic2_power_on)){
			/* mainmic chg */
			hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MAIN_MIC_DISCHG_BIT, 0);
			/* mainmic on */
			hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MAIN_MIC_PD_BIT, 0);
		}
		priv->main_mic_power_on = true;
		break;
	case SND_SOC_DAPM_POST_PMD:
		priv->main_mic_power_on = false;
		if(!(priv->main_mic_power_on) && (!priv->mic2_power_on)){
			/* mainmic pd */
			hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MAIN_MIC_PD_BIT, 1 << HI6402_MAIN_MIC_PD_BIT);
			/* mainmic dischg */
			hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MAIN_MIC_DISCHG_BIT, 1 << HI6402_MAIN_MIC_DISCHG_BIT);
		}
#ifdef CONFIG_ANC_HS_INTERFACE
		if(check_anc_hs_interface_support()) {
			anc_hs_interface_5v_control(ANC_HS_DISABLE_5VOLTATE);
		}
#endif
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_aux_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* auxmic chg */
		hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_AUX_MIC_DISCHG_BIT, 0);
		/* auxmic on */
		hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_AUX_MIC_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* dismic pd */
		hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_AUX_MIC_PD_BIT, 1 << HI6402_AUX_MIC_PD_BIT);
		/* auxmic dischg */
		hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_AUX_MIC_DISCHG_BIT, 1 << HI6402_AUX_MIC_DISCHG_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void anc_hs_control_charge(struct snd_soc_codec *codec, bool enable)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	dev_info(codec->dev, "%s + \n",__FUNCTION__);

#ifdef CONFIG_ANC_HS_INTERFACE
	if(!check_anc_hs_interface_support()) {
		return;
	}

	/* mask btn irqs */
	hi64xx_irq_mask_btn_irqs(priv->mbhc);
	if(enable) {
		pr_info("%s enable \n",__FUNCTION__);
		anc_hs_interface_force_charge(ANC_HS_ENABLE_CHARGE);
	} else {
		pr_info("%s disable \n",__FUNCTION__);
		anc_hs_interface_force_charge(ANC_HS_DISABLE_CHARGE);
	}
	/* unmask btn irqs */
	hi64xx_irq_unmask_btn_irqs(priv->mbhc);
#endif

}

int hi6402_hs_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* stop anc charge */
		anc_hs_control_charge(codec, false);
		/* hs micbias on */
		hi64xx_resmgr_request_micbias(priv->resmgr);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* hs micbias off */
		hi64xx_resmgr_release_micbias(priv->resmgr);
		/* resume anc charge */
		anc_hs_control_charge(codec, true);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_mic2_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if(1 == priv->board_cfg.mic2_source){
			if(!(priv->main_mic_power_on) && (!priv->mic2_power_on)){
				/* mic2 chg */
				hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MAIN_MIC_DISCHG_BIT, 0);
				/* mic2 on */
				hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MAIN_MIC_PD_BIT, 0);
			}
			priv->mic2_power_on = true;
		}else{
			/* mic2 chg */
			hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MIC2_DISCHG_BIT, 0);
			/* mic2 on */
			hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MIC2_PD_BIT, 0);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (1 == priv->board_cfg.mic2_source) {
			priv->mic2_power_on = false;
			if(!(priv->main_mic_power_on) && (!priv->mic2_power_on)){
				/* mic2 pd */
				hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MAIN_MIC_PD_BIT, 1 << HI6402_MAIN_MIC_PD_BIT);
				/* mic2 dischg */
				hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MAIN_MIC_DISCHG_BIT, 1 << HI6402_MAIN_MIC_DISCHG_BIT);
			}
		}else{
			/* mic2 pd */
			hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MIC2_PD_BIT, 1 << HI6402_MIC2_PD_BIT);
			/* mic2 dischg */
			hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MIC2_DISCHG_BIT, 1 << HI6402_MIC2_DISCHG_BIT);
		}
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6402_mic3_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* mic3 chg */
		hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MIC3_DISCHG_BIT, 0);
		/* mic3 on */
		hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MIC3_PD_BIT, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* mic3 pd */
		hi64xx_update_bits(codec, HI6402_ANA_MIC_PD_REG, 1 << HI6402_MIC3_PD_BIT, 1 << HI6402_MIC3_PD_BIT);
		/* mic3 dischg */
		hi64xx_update_bits(codec, HI6402_MIC_DISCHG_REG, 1 << HI6402_MIC3_DISCHG_BIT, 1 << HI6402_MIC3_DISCHG_BIT);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

/* VOLUME CONTROLS */
/*
* MAIN MIC GAIN volume control:
* from 0 to 36 dB in 2 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(main_mic_tlv, 0, 200, 0);

/*
* AUX MIC GAIN volume control:
* from 0 to 36 dB in 2 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(aux_mic_tlv, 0, 200, 0);

/*
* LINEINR MIC GAIN volume control:
* from -20 to 36 dB in 2 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(lineinr_mic_tlv, -2000, 200, 0);

/*
* LINEINL MIC GAIN volume control:
* from -20 to 36 dB in 2 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(lineinl_mic_tlv, -2000, 200, 0);

/*
* LOL PGA GAIN volume control:
* from -21 to 6 dB in 1.5 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(lol_pga_tlv, -2100, 150, 0);

/*
* LOR PGA GAIN volume control:
* from -21 to 6 dB in 1.5 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(lor_pga_tlv, -2100, 150, 0);

/*
* EP PGA GAIN volume control:
* from -21to 6 dB in 1.5 dB steps
* MAX VALUE is 18
*/
static DECLARE_TLV_DB_SCALE(ep_pga_tlv, -2100, 150, 0);

/* SOUND KCONTROLS */
static const struct snd_kcontrol_new hi6402_snd_controls[] = {
	/* s1 wordlength */
	SOC_SINGLE("S1 WORDLEN SEL",
		HI6402_S1_PORT_CFG_H, HI6402_WORD_LENGTH_BIT, 3, 0),
	/* s3 wordlength */
	SOC_SINGLE("S3 WORDLEN SEL",
		HI6402_S3_PORT_CFG_H, HI6402_WORD_LENGTH_BIT, 3, 0),
	/* s1 port cfg */
	SOC_SINGLE("S1 IF CLK EN",
		HI6402_S1_FS_CFG_L, HI6402_PORT_CLK_EN, 1, 0),
	SOC_SINGLE("S1 IF FS CFG",
		HI6402_S1_FS_CFG_L, HI6402_PORT_FS_CFG, 7, 0),
	/* s2 port cfg */
	SOC_SINGLE("S2 IF CLK EN",
		HI6402_S2_FS_CFG_L, HI6402_PORT_CLK_EN, 1, 0),
	SOC_SINGLE("S2 IF FS CFG",
		HI6402_S2_FS_CFG_L, HI6402_PORT_FS_CFG, 7, 0),
	SOC_SINGLE("S2 DSP IF IN FS",
		HI6402_S2_FS_CFG_H, HI6402_DSP_IF_IN_FS_CFG, 7, 0),
	SOC_SINGLE("S2 DSP IF OUT FS",
		HI6402_S2_FS_CFG_H, HI6402_DSP_IF_OUT_FS_CFG, 7, 0),
	SOC_SINGLE("S2 IF FUNC MODE CFG",
		HI6402_S2_PORT_CFG_L, HI6402_FUNC_MODE_BIT, 5, 0),
	SOC_SINGLE("S2 MST SLV CFG",
		HI6402_S2_PORT_CFG_L, HI6402_MST_SLV_BIT, 1, 0),
	SOC_SINGLE("S2 LRCLK CFG",
		HI6402_S2_PORT_CFG_H, HI6402_LRCLK_MODE_BIT, 1, 0),
	SOC_SINGLE("S2 IF FRAME MODE CFG",
		HI6402_S2_PORT_CFG_H, HI6402_FRAME_MODE_BIT, 1, 0),
	SOC_SINGLE("S2 IF WORD LENGTH CFG",
		HI6402_S2_PORT_CFG_H, HI6402_WORD_LENGTH_BIT, 3, 0),
	SOC_SINGLE("S2 IF CHNNL MODE CFG",
		HI6402_S2_PORT_CFG_H, HI6402_CHNNL_MODE_BIT, 1, 0),
	SOC_SINGLE("S2 RX CLK SEL",
		HI6402_S2_PORT_CFG_H, HI6402_RX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("S2 TX CLK SEL",
		HI6402_S2_PORT_CFG_H, HI6402_TX_CLK_SEL_BIT, 1, 0),
	/* s3 port cfg */
	SOC_SINGLE("S3 IF CLK EN",
		HI6402_S3_FS_CFG_L, HI6402_PORT_CLK_EN, 1, 0),
	SOC_SINGLE("S3 IF FS CFG",
		HI6402_S3_FS_CFG_L, HI6402_PORT_FS_CFG, 7, 0),
	/* s4 port cfg */
	SOC_SINGLE("S4 IF CLK EN",
		HI6402_S4_FS_CFG_L, HI6402_PORT_CLK_EN, 1, 0),
	SOC_SINGLE("S4 IF FS CFG",
		HI6402_S4_FS_CFG_L, HI6402_PORT_FS_CFG, 7, 0),
	/* s1 i pga gain kcontrol */
	SOC_SINGLE("S1 IL PGA GAIN",
		HI6402_S1_PGA_IL_GAIN_CFG_REG, HI6402_S1_PGA_IL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S1 IR PGA GAIN",
		HI6402_S1_PGA_IR_GAIN_CFG_REG, HI6402_S1_PGA_IR_GAIN_BIT, 255, 0),
	/* s2 i pga gain kcontrol */
	SOC_SINGLE("S2 IL PGA GAIN",
		HI6402_S2_PGA_IL_GAIN_CFG_REG, HI6402_S2_PGA_IL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S2 IR PGA GAIN",
		HI6402_S2_PGA_IR_GAIN_CFG_REG, HI6402_S2_PGA_IR_GAIN_BIT, 255, 0),
	/* s3 i pga gain kcontrol */
	SOC_SINGLE("S3 IL PGA GAIN",
		HI6402_S3_PGA_IL_GAIN_CFG_REG, HI6402_S3_PGA_IL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S3 IR PGA GAIN",
		HI6402_S3_PGA_IR_GAIN_CFG_REG, HI6402_S3_PGA_IR_GAIN_BIT, 255, 0),
	/* s4 i pga gain kcontrol */
	SOC_SINGLE("S4 IL PGA GAIN",
		HI6402_S4_PGA_IL_GAIN_CFG_REG, HI6402_S4_PGA_IL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S4 IR PGA GAIN",
		HI6402_S4_PGA_IR_GAIN_CFG_REG, HI6402_S4_PGA_IR_GAIN_BIT, 255, 0),
	/* s1 o pga gain kcontrol */
	SOC_SINGLE("S1 OL PGA GAIN",
		HI6402_S1_PGA_OL_GAIN_CFG_REG, HI6402_S1_PGA_OL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S1 OR PGA GAIN",
		HI6402_S1_PGA_OR_GAIN_CFG_REG, HI6402_S1_PGA_OR_GAIN_BIT, 255, 0),
	/* s2 o pga gain kcontrol */
	SOC_SINGLE("S2 OL PGA GAIN",
		HI6402_S2_PGA_OL_GAIN_CFG_REG, HI6402_S2_PGA_OL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S2 OR PGA GAIN",
		HI6402_S2_PGA_OR_GAIN_CFG_REG, HI6402_S2_PGA_OR_GAIN_BIT, 255, 0),
	/* s3 o pga gain kcontrol */
	SOC_SINGLE("S3 OL PGA GAIN",
		HI6402_S3_PGA_OL_GAIN_CFG_REG, HI6402_S3_PGA_OL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S3 OR PGA GAIN",
		HI6402_S3_PGA_OR_GAIN_CFG_REG, HI6402_S3_PGA_OR_GAIN_BIT, 255, 0),
	/* s4 o pga gain kcontrol */
	SOC_SINGLE("S4 OL PGA GAIN",
		HI6402_S4_PGA_OL_GAIN_CFG_REG, HI6402_S4_PGA_OL_GAIN_BIT, 255, 0),
	SOC_SINGLE("S4 OR PGA GAIN",
		HI6402_S4_PGA_OR_GAIN_CFG_REG, HI6402_S4_PGA_OR_GAIN_BIT, 255, 0),
	/* side pga gain kcontrol */
	SOC_SINGLE("SIDE PGA GAIN",
		HI6402_SIDE_PGA_GAIN_CFG_REG, HI6402_SIDE_PGA_GAIN_BIT, 255, 0),
	/* dac pga gain kcontrol */
	SOC_SINGLE("DACL PGA GAIN",
		HI6402_DACL_PGA_GAIN_CFG_REG, HI6402_DACL_PGA_GAIN_BIT, 255, 0),
	SOC_SINGLE("DACR PGA GAIN",
		HI6402_DACR_PGA_GAIN_CFG_REG, HI6402_DACR_PGA_GAIN_BIT, 255, 0),
	/* lineinl pga gain kcontrol */
	SOC_SINGLE_TLV("LINEL PGA GAIN",
		HI6402_LINEL_PGA_SEL_REG, HI6402_LINEL_PGA_GAIN_BIT, 28, 0, lineinl_mic_tlv),
	/* lineinr pga gain kcontrol */
	SOC_SINGLE_TLV("LINER PGA GAIN",
		HI6402_LINER_PGA_SEL_REG, HI6402_LINER_PGA_GAIN_BIT, 28, 0, lineinr_mic_tlv),
	/* aux pga gain kcontrol */
	SOC_SINGLE_TLV("AUX PGA GAIN",
		HI6402_AUX_PGA_SEL_REG, HI6402_AUX_PGA_GAIN_BIT, 18, 0, aux_mic_tlv),
	/* main pga gain kcontrol */
	SOC_SINGLE_TLV("MAIN PGA GAIN",
		HI6402_MAIN_PGA_SEL_REG, HI6402_MAIN_PGA_GAIN_BIT, 18, 0, main_mic_tlv),
	/* lol pga gain kcontrol */
	SOC_SINGLE_TLV("LOL PGA GAIN",
		HI6402_LOL_PGA_CFG_REG, HI6402_LOL_PGA_GAIN_BIT, 18, 0, lol_pga_tlv),
	SOC_SINGLE("LOL PGA MUTE",
		HI6402_LOL_PGA_CFG_REG, HI6402_LOL_PGA_MUTE_BIT, 1, 1),
	/* lor pga gain kcontrol */
	SOC_SINGLE_TLV("LOR PGA GAIN",
		HI6402_LOR_PGA_CFG_REG, HI6402_LOR_PGA_GAIN_BIT, 18, 0, lor_pga_tlv),
	SOC_SINGLE("LOR PGA MUTE",
		HI6402_LOR_PGA_CFG_REG, HI6402_LOR_PGA_MUTE_BIT, 1, 1),
	/* hpl pga gain kcontrol */
	SOC_SINGLE("HPL PGA GAIN",
		HI6402_HPL_PGA_CFG_REG, HI6402_HPL_PGA_GAIN_BIT, 33, 0),
	SOC_SINGLE("HPL PGA MUTE",
		HI6402_HPL_PGA_CFG_REG, HI6402_HPL_PGA_MUTE_BIT, 1, 1),
	/* hpr pga gain kcontrol */
	SOC_SINGLE("HPR PGA GAIN",
		HI6402_HPR_PGA_CFG_REG, HI6402_HPR_PGA_GAIN_BIT, 33, 0),
	SOC_SINGLE("HPR PGA MUTE",
		HI6402_HPR_PGA_CFG_REG, HI6402_HPR_PGA_MUTE_BIT, 1, 1),
	/* ep pga gain kcontrol */
	SOC_SINGLE_TLV("EP PGA GAIN",
		HI6402_EP_PGA_CFG_REG, HI6402_EP_PGA_GAIN_BIT, 18, 0, ep_pga_tlv),
	SOC_SINGLE("EP PGA MUTE",
		HI6402_EP_PGA_CFG_REG, HI6402_EP_PGA_MUTE_BIT, 1, 1),
	/* s1 il src kcontrol */
	SOC_SINGLE("S1 IL SRC EN",
		HI6402_S1_MODULE_CLK_REG, HI6402_S1_SRC_IL_EN_BIT, 1, 0),
	SOC_SINGLE("S1 IL SRC MODE",
		HI6402_S1_SRC_IN_MODE_CGF, HI6402_S1_SRC_IL_MODE_BIT, 7, 0),
	/* s1 ir src kcontrol */
	SOC_SINGLE("S1 IR SRC EN",
		HI6402_S1_MODULE_CLK_REG, HI6402_S1_SRC_IR_EN_BIT, 1, 0),
	SOC_SINGLE("S1 IR SRC MODE",
		HI6402_S1_SRC_IN_MODE_CGF, HI6402_S1_SRC_IR_MODE_BIT, 7, 0),
	/* s1 ol src kcontrol */
	SOC_SINGLE("S1 OL SRC EN",
		HI6402_S1_MODULE_CLK_REG, HI6402_S1_SRC_OL_EN_BIT, 1, 0),
	SOC_SINGLE("S1 OL SRC MODE",
		HI6402_S1_SRC_OUT_MODE_CGF, HI6402_S1_SRC_OL_MODE_BIT, 3, 0),
	/* s1 or src kcontrol */
	SOC_SINGLE("S1 OR SRC EN",
		HI6402_S1_MODULE_CLK_REG, HI6402_S1_SRC_OR_EN_BIT, 1, 0),
	SOC_SINGLE("S1 OR SRC MODE",
		HI6402_S1_SRC_OUT_MODE_CGF, HI6402_S1_SRC_OR_MODE_BIT, 3, 0),
	/* s2 il src kcontrol */
	SOC_SINGLE("S2 IL SRC EN",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_SRC_IL_EN_BIT, 1, 0),
	SOC_SINGLE("S2 IL SRC MODE",
		HI6402_S2_SRC_IN_MODE_CGF, HI6402_S2_SRC_IL_MODE_BIT, 7, 0),
	/* s2 ir src kcontrol */
	SOC_SINGLE("S2 IR SRC EN",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_SRC_IR_EN_BIT, 1, 0),
	SOC_SINGLE("S2 IR SRC MODE",
		HI6402_S2_SRC_IN_MODE_CGF, HI6402_S2_SRC_IR_MODE_BIT, 7, 0),
	/* s2 ol src kcontrol */
	SOC_SINGLE("S2 OL SRC EN",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_SRC_OL_EN_BIT, 1, 0),
	SOC_SINGLE("S2 OL SRC MODE",
		HI6402_S2_SRC_OUT_MODE_CGF, HI6402_S2_SRC_OL_MODE_BIT, 3, 0),
	/* s2 or src kcontrol */
	SOC_SINGLE("S2 OR SRC EN",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_SRC_OR_EN_BIT, 1, 0),
	SOC_SINGLE("S2 OR SRC MODE",
		HI6402_S2_SRC_OUT_MODE_CGF, HI6402_S2_SRC_OR_MODE_BIT, 3, 0),
	/* s3 il src kcontrol */
	SOC_SINGLE("S3 IL SRC EN",
		HI6402_S3_MODULE_CLK_REG, HI6402_S3_SRC_IL_EN_BIT, 1, 0),
	SOC_SINGLE("S3 IL SRC MODE",
		HI6402_S3_SRC_IN_MODE_CGF, HI6402_S3_SRC_IL_MODE_BIT, 7, 0),
	/* s3 ir src kcontrol */
	SOC_SINGLE("S3 IR SRC EN",
		HI6402_S3_MODULE_CLK_REG, HI6402_S3_SRC_IR_EN_BIT, 1, 0),
	SOC_SINGLE("S3 IR SRC MODE",
		HI6402_S3_SRC_IN_MODE_CGF, HI6402_S3_SRC_IR_MODE_BIT, 7, 0),
	/* s3 ol src kcontrol */
	SOC_SINGLE("S3 OL SRC EN",
		HI6402_S3_MODULE_CLK_REG, HI6402_S3_SRC_OL_EN_BIT, 1, 0),
	SOC_SINGLE("S3 OL SRC MODE",
		HI6402_S3_SRC_OUT_MODE_CGF, HI6402_S3_SRC_OL_MODE_BIT, 3, 0),
	/* s3 or src kcontrol */
	SOC_SINGLE("S3 OR SRC EN",
		HI6402_S3_MODULE_CLK_REG, HI6402_S3_SRC_OR_EN_BIT, 1, 0),
	SOC_SINGLE("S3 OR SRC MODE",
		HI6402_S3_SRC_OUT_MODE_CGF, HI6402_S3_SRC_OR_MODE_BIT, 3, 0),
	/* s4 il src kcontrol */
	SOC_SINGLE("S4 IL SRC EN",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_SRC_IL_EN_BIT, 1, 0),
	SOC_SINGLE("S4 IL SRC MODE",
		HI6402_S4_SRC_IN_MODE_CGF, HI6402_S4_SRC_IL_MODE_BIT, 7, 0),
	/* s4 ir src kcontrol */
	SOC_SINGLE("S4 IR SRC EN",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_SRC_IR_EN_BIT, 1, 0),
	SOC_SINGLE("S4 IR SRC MODE",
		HI6402_S4_SRC_IN_MODE_CGF, HI6402_S4_SRC_IR_MODE_BIT, 7, 0),
	/* s4 ol src kcontrol */
	SOC_SINGLE("S4 OL SRC EN",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_SRC_OL_EN_BIT, 1, 0),
	SOC_SINGLE("S4 OL SRC MODE",
		HI6402_S4_SRC_OUT_MODE_CGF, HI6402_S4_SRC_OL_MODE_BIT, 3, 0),
	/* s4 or src kcontrol */
	SOC_SINGLE("S4 OR SRC EN",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_SRC_OR_EN_BIT, 1, 0),
	SOC_SINGLE("S4 OR SRC MODE",
		HI6402_S4_SRC_OUT_MODE_CGF, HI6402_S4_SRC_OR_MODE_BIT, 3, 0),
	/* sidetone src kcontrol */
	SOC_SINGLE("SIDETONE SRC EN",
		HI6402_MDM_SRC_SEL, HI6402_SIDE_SRC_EN_BIT, 1, 0),
	SOC_SINGLE("SIDETONE SRC MODE",
		HI6402_SIDE_MDM_SRC_MODE_REG, HI6402_SIDETONE_SRC_MODE_BIT, 3, 0),
	/* mdm src kcontrol */
	SOC_SINGLE("MDM SRC EN",
		HI6402_MDM_SRC_SEL, HI6402_MDM_SRC_EN_BIT, 1, 0),
	SOC_SINGLE("MDM SRC MODE",
		HI6402_SIDE_MDM_SRC_MODE_REG, HI6402_MDM_SRC_MODE_BIT, 3, 0),
	/* dac src kcontrol */
	SOC_SINGLE("DACL SRC EN",
		HI6402_DAC_SRC_CLK_REG, HI6402_DACL_SRC_EN_BIT, 1, 0),
	SOC_SINGLE("DACL SRC MODE",
		HI6402_DAC_SRC_MODE_REG, HI6402_DACL_SRC_MODE_BIT, 7, 0),
	SOC_SINGLE("DACR SRC EN",
		HI6402_DAC_SRC_CLK_REG, HI6402_DACR_SRC_EN_BIT, 1, 0),
	SOC_SINGLE("DACR SRC MODE",
		HI6402_DAC_SRC_MODE_REG, HI6402_DACR_SRC_MODE_BIT, 7, 0),
	/* dac dacs src up16 kcontrol */
	SOC_SINGLE("DACL SRC UP16 EN",
		HI6402_EQ_SM_CLK_REG, HI6402_SRC_UP16L_EN_BIT, 1, 0),
	SOC_SINGLE("DACL SRC UP16 MODE",
		HI6402_DAC_FILTER_OUTL_MUX_SEL, HI6402_DAC_SRC_UP16_MODE_BIT, 15, 0),
	SOC_SINGLE("DACR SRC UP16 EN",
		HI6402_EQ_SM_CLK_REG, HI6402_SRC_UP16R_EN_BIT, 1, 0),
	SOC_SINGLE("DACR SRC UP16 MODE",
		HI6402_DAC_FILTER_OUTR_MUX_SEL, HI6402_DAC_SRC_UP16_MODE_BIT, 15, 0),
	/* HP DAC MUTE */
	SOC_SINGLE("HP DACL MUTE",
		HI6402_DAC_HP_PD_REG, HI6402_DAC_HPL_MUTE_PD_BIT, 1, 1),
	SOC_SINGLE("HP DACR MUTE",
		HI6402_DAC_HP_PD_REG, HI6402_DAC_HPR_MUTE_PD_BIT, 1, 1),
	/* ANA ADC MUTE */
	SOC_SINGLE("MAINPGA MUTE1",
		HI6402_ADC_PGA_MUTE1_SEL_REG, HI6402_MAIN_PGA_MUTE1_BIT, 1, 1),
	SOC_SINGLE("MAINPGA MUTE2",
		HI6402_MAIN_PGA_SEL_REG, HI6402_MAIN_PGA_MUTE2_BIT, 1, 1),
	SOC_SINGLE("AUXPGA MUTE1",
		HI6402_AUX_PGA_SEL_REG, HI6402_AUX_PGA_MUTE1_BIT, 1, 1),
	SOC_SINGLE("AUXPGA MUTE2",
		HI6402_AUX_PGA_SEL_REG, HI6402_AUX_PGA_MUTE2_BIT, 1, 1),
	SOC_SINGLE("LINELPGA MUTE1",
		HI6402_ADC_PGA_MUTE1_SEL_REG, HI6402_LINEL_PGA_MUTE1_BIT, 1, 1),
	SOC_SINGLE("LINELPGA MUTE2",
		HI6402_LINEL_PGA_SEL_REG, HI6402_LINEL_PGA_MUTE2_BIT, 1, 1),
	SOC_SINGLE("LINERPGA MUTE1",
		HI6402_ADC_PGA_MUTE1_SEL_REG, HI6402_LINER_PGA_MUTE1_BIT, 1, 1),
	SOC_SINGLE("LINERPGA MUTE2",
		HI6402_LINER_PGA_SEL_REG, HI6402_LINER_PGA_MUTE2_BIT, 1, 1),
	/* DACL SRC MIXER GAIN */
	SOC_SINGLE("DACL MIXER GAIN0",
		HI6402_DACSL_MIXER_GAIN_REG, HI6402_DACSL_MIXER_0_GAIN_BIT, 3, 0),
	SOC_SINGLE("DACL MIXER GAIN1",
		HI6402_DACSL_MIXER_GAIN_REG, HI6402_DACSL_MIXER_1_GAIN_BIT, 3, 0),
	/* DACR SRC MIXER GAIN */
	SOC_SINGLE("DACR MIXER GAIN0",
		HI6402_DACSR_MIXER_GAIN_REG, HI6402_DACSR_MIXER_0_GAIN_BIT, 3, 0),
	SOC_SINGLE("DACR MIXER GAIN1",
		HI6402_DACSR_MIXER_GAIN_REG, HI6402_DACSR_MIXER_1_GAIN_BIT, 3, 0),
	/* SHARE MIXER GAIN */
	SOC_SINGLE("SHARE MIXER GAIN1",
		HI6402_SHARE_MIXER_GAIN_REG, HI6402_SHARE_MIXER_GAIN1_BIT, 3, 0),
	SOC_SINGLE("SHARE MIXER GAIN2",
		HI6402_SHARE_MIXER_GAIN_REG, HI6402_SHARE_MIXER_GAIN2_BIT, 3, 0),
	SOC_SINGLE("SHARE MIXER GAIN3",
		HI6402_SHARE_MIXER_GAIN_REG, HI6402_SHARE_MIXER_GAIN3_BIT, 3, 0),
	SOC_SINGLE("SHARE MIXER GAIN4",
		HI6402_SHARE_MIXER_GAIN_REG, HI6402_SHARE_MIXER_GAIN4_BIT, 3, 0),
	/* DACL MIXER GAIN */
	SOC_SINGLE("MIXERL GAIN1",
		HI6402_DACL_MIXER_GAIN_REG, HI6402_DACL_MIXER_S1_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERL GAIN2",
		HI6402_DACL_MIXER_GAIN_REG, HI6402_DACL_MIXER_S2L_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERL GAIN3",
		HI6402_DACL_MIXER_GAIN_REG, HI6402_DACL_MIXER_MDM_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERL GAIN4",
		HI6402_DACL_MIXER_GAIN_REG, HI6402_DACL_MIXER_SIDETONE_GAIN_BIT, 3, 0),
	/* DACR MIXER GAIN */
	SOC_SINGLE("MIXERR GAIN1",
		HI6402_DACR_MIXER_GAIN_REG, HI6402_DACR_MIXER_S1_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERR GAIN2",
		HI6402_DACR_MIXER_GAIN_REG, HI6402_DACR_MIXER_S2R_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERR GAIN3",
		HI6402_DACR_MIXER_GAIN_REG, HI6402_DACR_MIXER_MDM_GAIN_BIT, 3, 0),
	SOC_SINGLE("MIXERR GAIN4",
		HI6402_DACR_MIXER_GAIN_REG, HI6402_DACR_MIXER_SIDETONE_GAIN_BIT, 3, 0),
	/* BOOST */
	SOC_SINGLE("MAIN MIC BOOST",
		HI6402_ANA_MIC_BOOST_REG, HI6402_ANA_MAINMIC_BOOST_BIT, 1, 0),
	SOC_SINGLE("AUX MIC BOOST",
		HI6402_ANA_MIC_BOOST_REG, HI6402_ANA_AUXMIC_BOOST_BIT, 1, 0),
	SOC_SINGLE("LINEINL BOOST",
		HI6402_ANA_LINEIN_BOOST_REG, HI6402_ANA_LINEINL_BOOST_BIT, 1, 0),
	SOC_SINGLE("LINEINR BOOST",
		HI6402_ANA_LINEIN_BOOST_REG, HI6402_ANA_LINEINR_BOOST_BIT, 1, 0),
	SOC_ENUM_EXT("HAC",
		hac_switch_enum[0], hac_switch_get, hac_switch_put),
};

/* SWITCH */
/* DACSL */
static const struct snd_kcontrol_new hi6402_dapm_dacsl_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_DAC_ADC_CLK_REG, HI6402_DACSL_EN_BIT, 1, 0);
/* DACSR */
static const struct snd_kcontrol_new hi6402_dapm_dacsr_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_DAC_ADC_CLK_REG, HI6402_DACSR_EN_BIT, 1, 0);
/* HPDAC_I2V SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_hpdac_i2v_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_DAC_HPL_I2V_CFG_REG, 7, 1, 1);
/* MAD SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_mad_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S1_MODULE_CLK_MM_REG, HI6402_S1_SRC_OL_EN_MM_BIT, 1, 0);
/* S1 OL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s1_ol_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S1_MODULE_CLK_MM_REG, HI6402_S1_PGA_OL_EN_MM_BIT, 1, 0);
/* S1 OR SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s1_or_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S1_MODULE_CLK_MM_REG, HI6402_S1_PGA_OR_EN_MM_BIT, 1, 0);
/* S2 OL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s2_ol_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_PGA_OL_EN_BIT, 1, 0);
/* S2 OR SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s2_or_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S2_MODULE_CLK_REG, HI6402_S2_PGA_OR_EN_BIT, 1, 0);
/* S3 OL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s3_ol_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S3_MODULE_CLK_MM_REG, HI6402_S3_PGA_OL_EN_MM_BIT, 1, 0);
/* S3 OR SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s3_or_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S3_MODULE_CLK_MM_REG, HI6402_S3_PGA_OR_EN_MM_BIT, 1, 0);
/* S4 OL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s4_ol_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_OL_EN_BIT, 1, 0);
/* S4 OR SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s4_or_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_OR_EN_BIT, 1, 0);
/* S3IL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_s3il_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S3IL_MM_REG, HI6402_S3IL_EN_MM_BIT, 1, 0);

/* MODEM AUDIO 8K SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_modem_audio_8k_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_MODEM_AUDIO_8K_EN_MM_BIT, 1, 0);

/* MODEM AUDIO 16K SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_modem_audio_16k_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_MODEM_AUDIO_16K_EN_MM_BIT, 1, 0);
/* SP IL SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_sp_il_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_IL_EN_BIT, 1, 0);
/* SP IR SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_sp_ir_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_IR_EN_BIT, 1, 0);
/* EP SWITCH */
static const struct snd_kcontrol_new hi6402_dapm_ep_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6402_DAC_LT_MUX_SEL, HI6402_DAC_EP_MUX_H_BIT, 1, 1);
/* audio capture */
static const struct snd_kcontrol_new hi6402_dapm_audio_capture_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_AUDIO_CAPTURE_EN_MM_BIT, 1, 0);
/* voice up 16k */
static const struct snd_kcontrol_new hi6402_dapm_voiceup_16k_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_VOICEUP_16K_EN_MM_BIT, 1, 0);
/* voice up 8k */
static const struct snd_kcontrol_new hi6402_dapm_voiceup_8k_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_VOICEUP_8K_EN_MM_BIT, 1, 0);
/* fm */
static const struct snd_kcontrol_new hi6402_dapm_fm_controls =
	SOC_DAPM_SINGLE("SWITCH",
		BASE_ADDR_PAGE_MM, HI6402_FM_MM_BIT, 1, 0);

/* APL MUX 0x7208 */
static const char *hi6402_apl_mux_texts[] = {
	"ADC0L",
	"ADC1L",
	"DACSL",
	"DACL_48",
	"S1L",
	"S2L",
	"S3L",
	"S4L",
	"MDM",
	"BT0",
	"MDM0",
	"MDM2",
};
static const struct soc_enum hi6402_apl_mux_enum =
	SOC_ENUM_SINGLE(HI6402_AP_MUX_SEL, HI6402_APL_MUX_BIT,
		ARRAY_SIZE(hi6402_apl_mux_texts),hi6402_apl_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_apl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_apl_mux_enum);

/* APR MUX 0x7208 */
static const char *hi6402_apr_mux_texts[] = {
	"ADC0R",
	"ADC1R",
	"DACSR",
	"DACR_48",
	"S1R",
	"S2R",
	"S3R",
	"S4R",
	"MDM",
	"BT1",
	"MDM1",
	"MDM3",
};
static const struct soc_enum hi6402_apr_mux_enum =
	SOC_ENUM_SINGLE(HI6402_AP_MUX_SEL, HI6402_APR_MUX_BIT,
		ARRAY_SIZE(hi6402_apr_mux_texts), hi6402_apr_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_apr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_apr_mux_enum);

/* BTL MUX 0x720A */
static const char *hi6402_btl_mux_texts[] = {
	"ADC0L",
	"ADC1L",
	"DACSL",
	"DACL_48",
	"S1L",
	"S2L",
	"S3L",
	"S4L",
	"MDM",
	"AP0",
	"MDM0",
	"MDM2",
};
static const struct soc_enum hi6402_btl_mux_enum =
	SOC_ENUM_SINGLE(HI6402_BT_MUX_SEL, HI6402_BTL_MUX_BIT,
		ARRAY_SIZE(hi6402_btl_mux_texts),hi6402_btl_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_btl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_btl_mux_enum);

/* BTR MUX 0x720A */
static const char *hi6402_btr_mux_texts[] = {
	"ADC0R",
	"ADC1R",
	"DACSR",
	"DACR_48",
	"S1R",
	"S2R",
	"S3R",
	"S4R",
	"MDM",
	"AP1",
	"MDM1",
	"MDM3",
};
static const struct soc_enum hi6402_btr_mux_enum =
	SOC_ENUM_SINGLE(HI6402_BT_MUX_SEL, HI6402_BTR_MUX_BIT,
		ARRAY_SIZE(hi6402_btr_mux_texts), hi6402_btr_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_btr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_btr_mux_enum);

/* M0L MUX 0x7209 */
static const char *hi6402_m0l_mux_texts[] = {
	"ADC0L",
	"ADC1L",
	"DACSL",
	"DACL_48",
	"S1L",
	"S2L",
	"S3L",
	"S4L",
	"MDM",
	"AP0",
	"BT0",
	"MDM2",
};
static const struct soc_enum hi6402_m0l_mux_enum =
	SOC_ENUM_SINGLE(HI6402_M0_MUX_SEL, HI6402_M0L_MUX_BIT,
		ARRAY_SIZE(hi6402_m0l_mux_texts),hi6402_m0l_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_m0l_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_m0l_mux_enum);

/* M0R MUX 0x7209 */
static const char *hi6402_m0r_mux_texts[] = {
	"ADC0R",
	"ADC1R",
	"DACSR",
	"DACR_48",
	"S1R",
	"S2R",
	"S3R",
	"S4R",
	"MDM",
	"AP1",
	"BT1",
	"MDM3",
};
static const struct soc_enum hi6402_m0r_mux_enum =
	SOC_ENUM_SINGLE(HI6402_M0_MUX_SEL, HI6402_M0R_MUX_BIT,
		ARRAY_SIZE(hi6402_m0r_mux_texts), hi6402_m0r_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_m0r_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_m0r_mux_enum);

/* M1L MUX 0x720B */
static const char *hi6402_m1l_mux_texts[] = {
	"ADC0L",
	"ADC1L",
	"DACSL",
	"DACL_48",
	"S1L",
	"S2L",
	"S3L",
	"S4L",
	"MDM",
	"AP0",
	"BT0",
	"MDM0",
};
static const struct soc_enum hi6402_m1l_mux_enum =
	SOC_ENUM_SINGLE(HI6402_M1_MUX_SEL, HI6402_M1L_MUX_BIT,
		ARRAY_SIZE(hi6402_m1l_mux_texts),hi6402_m1l_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_m1l_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_m1l_mux_enum);

/* M1R MUX 0x720B */
static const char *hi6402_m1r_mux_texts[] = {
	"ADC0R",
	"ADC1R",
	"DACSR",
	"DACR_48",
	"S1R",
	"S2R",
	"S3R",
	"S4R",
	"MDM",
	"AP1",
	"BT1",
	"MDM1",
};
static const struct soc_enum hi6402_m1r_mux_enum =
	SOC_ENUM_SINGLE(HI6402_M1_MUX_SEL, HI6402_M1R_MUX_BIT,
		ARRAY_SIZE(hi6402_m1r_mux_texts), hi6402_m1r_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_m1r_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_m1r_mux_enum);

/* MIXERL S1 MUX 0x7210 */
static const char *hi6402_dacl_mixer_mux_texts[] = {
	"S1 IL",
	"S2 IL",
	"S3 IL",
	"S4 IL",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacl_mixer_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_MIXER_MUX_SEL, HI6402_DACL_MIXER_MUX_BIT,
		ARRAY_SIZE(hi6402_dacl_mixer_mux_texts), hi6402_dacl_mixer_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacl_mixer_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacl_mixer_mux_enum);

/* MIXERR S1 MUX 0x7210 */
static const char *hi6402_dacr_mixer_mux_texts[] = {
	"S1 IR",
	"S2 IR",
	"S3 IR",
	"S4 IR",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacr_mixer_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_MIXER_MUX_SEL, HI6402_DACR_MIXER_MUX_BIT,
		ARRAY_SIZE(hi6402_dacr_mixer_mux_texts), hi6402_dacr_mixer_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacr_mixer_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacr_mixer_mux_enum);

/* MDM MUX 0x7212 */
static const char *hi6402_mdm_src_mux_texts[] = {
	"S1 IL",
	"S2 IL",
	"S3 IL",
	"S4 IL",
	"ADC0L",
	"ADC0R",
	"ADC1L",
	"ADC1R",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_mdm_src_mux_enum =
	SOC_ENUM_SINGLE(HI6402_MDM_SRC_MUX_SEL, HI6402_MDM_SRC_MUX_BIT,
		ARRAY_SIZE(hi6402_mdm_src_mux_texts), hi6402_mdm_src_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_mdm_src_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_mdm_src_mux_enum);

/* SIDETONE MUX 0x7212 */
static const char *hi6402_sidetone_src_mux_texts[] = {
	"S1 IL",
	"S2 IL",
	"S3 IL",
	"S4 IL",
	"ADC0L",
	"ADC0R",
	"ADC1L",
	"ADC1R",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_sidetone_src_mux_enum =
	SOC_ENUM_SINGLE(HI6402_SIDETONE_SRC_MUX_SEL, HI6402_SIDETONE_SRC_MUX_BIT,
		ARRAY_SIZE(hi6402_sidetone_src_mux_texts), hi6402_sidetone_src_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_sidetone_src_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_sidetone_src_mux_enum);

/* DACSL MUX 0x7215 */
static const char *hi6402_dacsl_mux_texts[] = {
	"DSP IF8 OUT",
	"S1 L",
	"S2 L",
	"S3 L",
	"S4 L",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacsl_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DACS_MUX_SEL, HI6402_DACSL_MUX_BIT,
		ARRAY_SIZE(hi6402_dacsl_mux_texts), hi6402_dacsl_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacsl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacsl_mux_enum);

/* DACSR MUX 0x7215 */
static const char *hi6402_dacsr_mux_texts[] = {
	"DSP IF8 OUT",
	"S1 R",
	"S2 R",
	"S3 R",
	"S4 R",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacsr_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DACS_MUX_SEL, HI6402_DACSR_MUX_BIT,
		ARRAY_SIZE(hi6402_dacsr_mux_texts), hi6402_dacsr_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacsr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacsr_mux_enum);

/* DACSL MUX 0x7271 */
static const char *hi6402_dacsl_s1l_mux_texts[] = {
	"S1 L",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacsl_s1l_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DACSL_S1L_MUX_SEL, HI6402_DACSL_S1L_MUX_BIT,
		ARRAY_SIZE(hi6402_dacsl_s1l_mux_texts), hi6402_dacsl_s1l_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacsl_s1l_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacsl_s1l_mux_enum);

/* DACSL MUX 0x7274 */
static const char *hi6402_dacsr_s1r_mux_texts[] = {
	"S1 R",
	"SHARE MIXER",
};
static const struct soc_enum hi6402_dacsr_s1r_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DACSR_S1R_MUX_SEL, HI6402_DACSR_S1R_MUX_BIT,
		ARRAY_SIZE(hi6402_dacsr_s1r_mux_texts), hi6402_dacsr_s1r_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacsr_s1r_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacsr_s1r_mux_enum);

/* DACL MUX 0x7215 */
static const char *hi6402_dacl_src_mixer_mux_texts[] = {
	"DSP IF8 OUT",
	"DSP IF8 IN",
};
static const struct soc_enum hi6402_dacl_src_mixer_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_SRC_MIXER_MUX_SEL, HI6402_DACL_SRC_MIXER_MUX_BIT,
		ARRAY_SIZE(hi6402_dacl_src_mixer_mux_texts), hi6402_dacl_src_mixer_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacl_src_mixer_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacl_src_mixer_mux_enum);

/* DACR MUX 0x7215 */
static const char *hi6402_dacr_src_mixer_mux_texts[] = {
	"DSP IF8 OUT",
	"DSP IF8 IN",
};
static const struct soc_enum hi6402_dacr_src_mixer_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_SRC_MIXER_MUX_SEL, HI6402_DACR_SRC_MIXER_MUX_BIT,
		ARRAY_SIZE(hi6402_dacr_src_mixer_mux_texts), hi6402_dacr_src_mixer_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dacr_src_mixer_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dacr_src_mixer_mux_enum);

/* HPL HPR LOL LOR MUX 0x728E-0x728F */
static const char *hi6402_dac_mux_texts[] = {
	"DACL",
	"DACR",
	"Off",
};
static const char *hi6402_dacs_mux_texts[] = {
	"DACL",
	"DACSL",
	"DACR",
	"DACSR",
	"Off",
};
static const char *hi6402_ep_dac_mux_texts[] = {
	"DACL",
	"DACSL",
	"DACR",
	"DACSR",
};
static const struct soc_enum hi6402_dac_hpl_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_HP_MUX_SEL, HI6402_DAC_HPL_MUX_BIT,
		ARRAY_SIZE(hi6402_dac_mux_texts), hi6402_dac_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dac_hpl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dac_hpl_mux_enum);

static const struct soc_enum hi6402_dac_hpr_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_HP_MUX_SEL, HI6402_DAC_HPR_MUX_BIT,
		ARRAY_SIZE(hi6402_dac_mux_texts), hi6402_dac_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dac_hpr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dac_hpr_mux_enum);

static const struct soc_enum hi6402_dac_ep_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_EP_MUX_SEL, HI6402_DAC_EP_MUX_BIT,
		ARRAY_SIZE(hi6402_ep_dac_mux_texts), hi6402_ep_dac_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dac_ep_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dac_ep_mux_enum);

static const struct soc_enum hi6402_dac_ltl_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_LT_MUX_SEL, HI6402_DAC_LTL_MUX_BIT,
		ARRAY_SIZE(hi6402_dacs_mux_texts), hi6402_dacs_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dac_ltl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dac_ltl_mux_enum);

static const struct soc_enum hi6402_dac_ltr_mux_enum =
	SOC_ENUM_SINGLE(HI6402_DAC_LT_MUX_SEL, HI6402_DAC_LTR_MUX_BIT,
		ARRAY_SIZE(hi6402_dacs_mux_texts), hi6402_dacs_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_dac_ltr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_dac_ltr_mux_enum);

/* ADCL0 MUX 0x7294 */
static const char *hi6402_adc_mux_texts[] = {
	"MAINMIC",
	"AUXMIC",
	"LINEINL",
	"LINEINR",
	"DMIC0L",
	"DMIC0R",
	"DMIC1L",
	"DMIC1R",
	"IO INPUT",
};
static const struct soc_enum hi6402_adcl0_mux_enum =
	SOC_ENUM_SINGLE(HI6402_ADC0_MUX_SEL, HI6402_ADCL0_MUX_BIT,
		ARRAY_SIZE(hi6402_adc_mux_texts), hi6402_adc_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_adcl0_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_adcl0_mux_enum);

/* ADCR0 MUX 0x7294 */
static const struct soc_enum hi6402_adcr0_mux_enum =
	SOC_ENUM_SINGLE(HI6402_ADC0_MUX_SEL, HI6402_ADCR0_MUX_BIT,
		ARRAY_SIZE(hi6402_adc_mux_texts), hi6402_adc_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_adcr0_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_adcr0_mux_enum);

/* ADCL1 MUX 0x7295 */
static const struct soc_enum hi6402_adcl1_mux_enum =
	SOC_ENUM_SINGLE(HI6402_ADC1_MUX_SEL, HI6402_ADCL1_MUX_BIT,
		ARRAY_SIZE(hi6402_adc_mux_texts), hi6402_adc_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_adcl1_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_adcl1_mux_enum);

/* ADCR0 MUX 0x7295 */
static const struct soc_enum hi6402_adcr1_mux_enum =
	SOC_ENUM_SINGLE(HI6402_ADC1_MUX_SEL, HI6402_ADCR1_MUX_BIT,
		ARRAY_SIZE(hi6402_adc_mux_texts), hi6402_adc_mux_texts);
static const struct snd_kcontrol_new hi6402_dapm_adcr1_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6402_adcr1_mux_enum);

/* LINEL PGA SEL 0x70A6*/
static const char *hi6402_linel_pga_sel_texts[] = {
	"LINEIN1",
	"LINEIN2",
	"LINEOUT",
	"MIC2",
};
static const struct soc_enum hi6402_linel_pga_sel_enum =
	SOC_ENUM_SINGLE(HI6402_LINEL_PGA_SEL_REG, HI6402_LINEL_PGA_SEL_BIT,
		ARRAY_SIZE(hi6402_linel_pga_sel_texts), hi6402_linel_pga_sel_texts);
static const struct snd_kcontrol_new hi6402_dapm_linel_pga_sel_controls =
	SOC_DAPM_ENUM("Mux", hi6402_linel_pga_sel_enum);

/* LINER PGA SEL 0x70A7 */
static const char *hi6402_liner_pga_sel_texts[] = {
	"LINEIN1",
	"LINEIN2",
	"LINEOUT",
	"MIC3",
};
static const struct soc_enum hi6402_liner_pga_sel_enum =
	SOC_ENUM_SINGLE(HI6402_LINER_PGA_SEL_REG, HI6402_LINER_PGA_SEL_BIT,
		ARRAY_SIZE(hi6402_liner_pga_sel_texts), hi6402_liner_pga_sel_texts);
static const struct snd_kcontrol_new hi6402_dapm_liner_pga_sel_controls =
	SOC_DAPM_ENUM("Mux", hi6402_liner_pga_sel_enum);

/* MIC MUX 0x70A9 */
static const char *hi6402_main_pga_sel_texts[] = {
	"HS MIC",
	"MAIN MIC",
};
static const struct soc_enum hi6402_main_pga_sel_enum =
	SOC_ENUM_SINGLE(HI6402_MAIN_PGA_SEL_REG, HI6402_MAIN_PGA_SEL_BIT,
		ARRAY_SIZE(hi6402_main_pga_sel_texts), hi6402_main_pga_sel_texts);
static const struct snd_kcontrol_new hi6402_dapm_main_pga_sel_controls =
	SOC_DAPM_ENUM("Mux", hi6402_main_pga_sel_enum);


/* MIXER */

/* DACL MIXER */
static const struct snd_kcontrol_new hi6402_dacl_mixer_controls[] = {
	SOC_DAPM_SINGLE("S1L MUX SWITCH",
		HI6402_DACL_MIXER_SEL_0, HI6402_DACL_MIXER_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("S2L SWITCH",
		HI6402_DACL_MIXER_SEL_0, HI6402_DACL_MIXER_S2L_BIT, 1, 1),
	SOC_DAPM_SINGLE("MDM SWITCH",
		HI6402_DACL_MIXER_SEL_0_MM_REG, HI6402_DACL_MIXER_MDM_BIT_MM_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACL_MIXER_SEL_1, HI6402_DACL_MIXER_SIDETONE_BIT, 1, 1),
};

/* DACR MIXER */
static const struct snd_kcontrol_new hi6402_dacr_mixer_controls[] = {
	SOC_DAPM_SINGLE("S1R MUX SWITCH",
		HI6402_DACR_MIXER_SEL_0, HI6402_DACR_MIXER_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("S2R SWITCH",
		HI6402_DACR_MIXER_SEL_0, HI6402_DACR_MIXER_S2R_BIT, 1, 1),
	SOC_DAPM_SINGLE("MDM SWITCH",
		HI6402_DACR_MIXER_SEL_0_MM_REG, HI6402_DACR_MIXER_MDM_BIT_MM_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACR_MIXER_SEL_1, HI6402_DACR_MIXER_SIDETONE_BIT, 1, 1),
};

/* DACSL MIXER */
static const struct snd_kcontrol_new hi6402_dacsl_mixer_controls[] = {
	SOC_DAPM_SINGLE("S1L MUX SWITCH",
		HI6402_DACSL_MIXER_SEL_0, HI6402_DACSL_MIXER_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("L SWITCH",
		HI6402_DACSL_MIXER_SEL_0, HI6402_DACSL_MIXER_L_BIT, 1, 1),
	SOC_DAPM_SINGLE("R SWITCH",
		HI6402_DACSL_MIXER_SEL_0, HI6402_DACSL_MIXER_R_BIT, 1, 1),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACSL_MIXER_SEL_1, HI6402_DACSL_MIXER_SIDETONE_BIT, 1, 1),
};

/* DACSR MIXER */
static const struct snd_kcontrol_new hi6402_dacsr_mixer_controls[] = {
	SOC_DAPM_SINGLE("S1R MUX SWITCH",
		HI6402_DACSR_MIXER_SEL_0, HI6402_DACSR_MIXER_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("L SWITCH",
		HI6402_DACSR_MIXER_SEL_0, HI6402_DACSR_MIXER_L_BIT, 1, 1),
	SOC_DAPM_SINGLE("R SWITCH",
		HI6402_DACSR_MIXER_SEL_0, HI6402_DACSR_MIXER_R_BIT, 1, 1),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACSR_MIXER_SEL_1, HI6402_DACSR_MIXER_SIDETONE_BIT, 1, 1),
};

/* SHARE MIXER */
static const struct snd_kcontrol_new hi6402_share_mixer_controls[] = {
	SOC_DAPM_SINGLE("S1L SWITCH",
		HI6402_SHARE_MIXER_SEL_0, HI6402_SHARE_MIXER_0_BIT, 1, 1),
	SOC_DAPM_SINGLE("S1R SWITCH",
		HI6402_SHARE_MIXER_SEL_0, HI6402_SHARE_MIXER_1_BIT, 1, 1),
};

/* DACL SRC MIXER */
static const struct snd_kcontrol_new hi6402_dacl_src_mixer_controls[] = {
	SOC_DAPM_SINGLE("DSP IF8 SWITCH",
		HI6402_DACSL_MIXER_SEL, HI6402_DACSL_MIXER_0_BIT, 1, 1),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACSL_MIXER_SEL, HI6402_DACSL_MIXER_1_BIT, 1, 1),
};

/* DACR SRC MIXER */
static const struct snd_kcontrol_new hi6402_dacr_src_mixer_controls[] = {
	SOC_DAPM_SINGLE("DSP IF8 SWITCH",
		HI6402_DACSR_MIXER_SEL, HI6402_DACSR_MIXER_0_BIT, 1, 1),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6402_DACSR_MIXER_SEL, HI6402_DACSR_MIXER_1_BIT, 1, 1),
};

/* DAPM WIDGETS */
static const struct snd_soc_dapm_widget hi6402_dapm_widgets[] = {
	/* INPUT */
	SND_SOC_DAPM_INPUT("LINEIN1"),
	SND_SOC_DAPM_INPUT("LINEIN2"),
	SND_SOC_DAPM_INPUT("LINE OUTL"),
	SND_SOC_DAPM_INPUT("LINE OUTR"),
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("AUXMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),
	SND_SOC_DAPM_INPUT("UP IN"),

	SND_SOC_DAPM_INPUT("S1L IN"),
	SND_SOC_DAPM_INPUT("S1R IN"),
	SND_SOC_DAPM_INPUT("S2L IN"),
	SND_SOC_DAPM_INPUT("S2R IN"),
	SND_SOC_DAPM_INPUT("S3L IN"),
	SND_SOC_DAPM_INPUT("S3R IN"),
	SND_SOC_DAPM_INPUT("S4L IN"),
	SND_SOC_DAPM_INPUT("S4R IN"),
	SND_SOC_DAPM_INPUT("ECL IN"),
	SND_SOC_DAPM_INPUT("ECR IN"),

	SND_SOC_DAPM_INPUT("DIGMIC0"),
	SND_SOC_DAPM_INPUT("DIGMIC1"),

	SND_SOC_DAPM_INPUT("HP HIGH IN"),

	/* OUTPUT */
	/* ANA OUT */
	SND_SOC_DAPM_OUTPUT("EAR OUT"),
	SND_SOC_DAPM_OUTPUT("HPL OUT"),
	SND_SOC_DAPM_OUTPUT("HPR OUT"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L"),
	SND_SOC_DAPM_OUTPUT("LINEOUT R"),
	/* DIG OUT */
	SND_SOC_DAPM_OUTPUT("MAD OUT"),
	SND_SOC_DAPM_OUTPUT("S1L OUT"),
	SND_SOC_DAPM_OUTPUT("S1R OUT"),
	SND_SOC_DAPM_OUTPUT("S2L OUT"),
	SND_SOC_DAPM_OUTPUT("S2R OUT"),
	SND_SOC_DAPM_OUTPUT("S3L OUT"),
	SND_SOC_DAPM_OUTPUT("S3R OUT"),
	SND_SOC_DAPM_OUTPUT("S4L OUT"),
	SND_SOC_DAPM_OUTPUT("S4R OUT"),
	SND_SOC_DAPM_OUTPUT("ECL OUT"),
	SND_SOC_DAPM_OUTPUT("ECR OUT"),

	/* SMART PA OUT */
	SND_SOC_DAPM_OUTPUT("SP L OUT"),
	SND_SOC_DAPM_OUTPUT("SP R OUT"),

	SND_SOC_DAPM_OUTPUT("HP HIGH OUT"),
	SND_SOC_DAPM_OUTPUT("UP OUT"),

	/* MICS */
	SND_SOC_DAPM_MIC("MAIN MIC", hi6402_main_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("AUX MIC", hi6402_aux_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("HS MIC", hi6402_hs_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("MIC2 IN", hi6402_mic2_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("MIC3 IN", hi6402_mic3_micbias_power_mode_event),

	/* SUPPLY */
	SND_SOC_DAPM_SUPPLY_S("PLL CLK",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_pll_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("MAD CLK",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_mad_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("REC CLK",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_rec_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("AUDIO CLK",
		2, SND_SOC_NOPM, 0, 0,
		hi6402_audio_clk_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("S1 TX CLK",
		4, SND_SOC_NOPM, 0, 0,
		hi6402_s1_tx_clk_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("S1 RX CLK",
		4, SND_SOC_NOPM, 0, 0,
		hi6402_s1_rx_clk_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("S1 INTERFACE CLK",
		3, SND_SOC_NOPM, 0, 0,
		hi6402_s1_interface_clk_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("S2 TX CLK",
		4, HI6402_S2_PORT_CFG_L, HI6402_IF_TX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY_S("S2 RX CLK",
		4, HI6402_S2_PORT_CFG_L, HI6402_IF_RX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY_S("S2 INTERFACE CLK",
		3, HI6402_S2_FS_CFG_L, HI6402_PORT_CLK_EN, 0,
		NULL, 0),

	SND_SOC_DAPM_SUPPLY_S("S3 INTERFACE CLK",
		3, SND_SOC_NOPM, 0, 0,
		hi6402_s3_interface_clk_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	SND_SOC_DAPM_SUPPLY_S("S4 TX CLK",
		4, HI6402_S4_PORT_CFG_L, HI6402_IF_TX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY_S("S4 RX CLK",
		4, HI6402_S4_PORT_CFG_L, HI6402_IF_RX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY_S("S4 INTERFACE CLK",
		3, HI6402_S4_FS_CFG_L, HI6402_PORT_CLK_EN, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY_S("CP1",
		3, SND_SOC_NOPM, 0, 0,
		hi6402_cp1_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SUPPLY_S("CP2",
		4, SND_SOC_NOPM, 0, 0,
		hi6402_cp2_power_mode_event,
		(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* ANALOG PGA */
	SND_SOC_DAPM_PGA_S("MAINMIC PGA",
		0, SND_SOC_NOPM, 0, 0,
		hi6402_mainmic_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("AUXMIC PGA",
		0, SND_SOC_NOPM, 0, 0,
		hi6402_auxmic_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("LINEINL PGA",
		0, SND_SOC_NOPM, 0, 0,
		hi6402_lineinl_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("LINEINR PGA",
		0, SND_SOC_NOPM, 0, 0,
		hi6402_lineinr_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* OUT DRIVER */
	SND_SOC_DAPM_OUT_DRV_E("HPL DRV",
		SND_SOC_NOPM, 0, 0,
		NULL, 0, hi6402_hpl_drv_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUT_DRV_E("HPR DRV",
		SND_SOC_NOPM, 0, 0,
		NULL, 0, hi6402_hpr_drv_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUT_DRV_E("EP DRV",
		SND_SOC_NOPM, 0, 0,
		NULL, 0, hi6402_ep_drv_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUT_DRV_E("LOL DRV",
		SND_SOC_NOPM, 0, 0,
		NULL, 0, hi6402_lol_drv_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUT_DRV_E("LOR DRV",
		SND_SOC_NOPM, 0, 0,
		NULL, 0, hi6402_lor_drv_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),


	/* DIGITAL PGA */
	/* PGA OF S1-S4 */
	SND_SOC_DAPM_PGA_S("S1 IL PGA",
		0, HI6402_S1_MODULE_CLK_REG, HI6402_S1_PGA_IL_EN_BIT, 0,
		hi6402_slimbus_port01_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("S1 IR PGA",
		0, HI6402_S1_MODULE_CLK_REG, HI6402_S1_PGA_IR_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA_S("S3 IL PGA",
		0, HI6402_S3_MODULE_CLK_REG, HI6402_S3_PGA_IL_EN_BIT, 0,
		hi6402_slimbus_port89_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("S3 IR PGA",
		0, HI6402_S3_MODULE_CLK_REG, HI6402_S3_PGA_IR_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA_S("S4 IL PGA",
		0, HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_IL_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA_S("S4 IR PGA",
		0, HI6402_S4_MODULE_CLK_REG, HI6402_S4_PGA_IR_EN_BIT, 0,
		NULL, 0),

	/* PGA FOR DAC */
	SND_SOC_DAPM_PGA_S("DACL PGA",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_dacl_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("DACR PGA",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_dacr_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* PGA FOR ADC */
	SND_SOC_DAPM_PGA_S("ADC1R",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_adc1r_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("ADC1L",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_adc1l_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("ADC0R",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_adc0r_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("ADC0L",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_adc0l_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* PGA FOR SIDETONE PGA */
	SND_SOC_DAPM_PGA_S("SIDE PGA",
		2, SND_SOC_NOPM, 0, 0,
		hi6402_side_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* PGA FOR PDM */
	SND_SOC_DAPM_PGA("PDM",
		HI6402_MDM_SRC_SEL, HI6402_PDM_EN_BIT, 0,
		NULL, 0),

	/* PGA FOR DAC */
	SND_SOC_DAPM_PGA_S("DACSL PGA",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_dacsl_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_PGA_S("DACSR PGA",
		1, SND_SOC_NOPM, 0, 0,
		hi6402_dacsr_pga_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* SWITCH FOR  S1-S4 OUT */
	SND_SOC_DAPM_SWITCH_E("MAD SWITCH",
		HI6402_SC_MAD_CTRL_18, HI6402_MAD_EN, 0,
		&hi6402_dapm_mad_switch_controls,
		hi6402_mad_src_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH_E("S1 OL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s1_ol_switch_controls,
		hi6402_s1_ol_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH_E("S1 OR SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s1_or_switch_controls,
		hi6402_s1_or_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH("S2 OL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s2_ol_switch_controls),
	SND_SOC_DAPM_SWITCH("S2 OR SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s2_or_switch_controls),
	SND_SOC_DAPM_SWITCH_E("S3 OL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s3_ol_switch_controls,
		hi6402_s3_ol_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH_E("S3 OR SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s3_or_switch_controls,
		hi6402_s3_or_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH_E("S4 OL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s4_ol_switch_controls,
		hi6402_slimbus_port1415_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_SWITCH("S4 OR SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s4_or_switch_controls),

	SND_SOC_DAPM_SWITCH("S3IL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_s3il_switch_controls),

	/* SWITCH FOR MODEM AUDIO 8K TEST */
	SND_SOC_DAPM_SWITCH_E("MODEM AUDIO 8K SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_modem_audio_8k_switch_controls,
		hi6402_modem_audio_8k_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* SWITCH FOR MODEM AUDIO 16K TEST */
	SND_SOC_DAPM_SWITCH_E("MODEM AUDIO 16K SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_modem_audio_16k_switch_controls,
		hi6402_modem_audio_16k_switch_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* SWITCH FOR HPDAC_I2V CFG */
	SND_SOC_DAPM_SWITCH_E("HPDAC_I2V",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_hpdac_i2v_switch_controls,
		hi6402_hpdac_i2v_cfg_power_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* SWITCH FOR SMART PA */
	SND_SOC_DAPM_SWITCH("SP IL SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_sp_il_switch_controls),
	SND_SOC_DAPM_SWITCH("SP IR SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_sp_ir_switch_controls),

	/* SWITCH FOR EP DAC MUX */
	SND_SOC_DAPM_SWITCH("EP SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_ep_switch_controls),

	/* virtual switch for audio capture */
	SND_SOC_DAPM_SWITCH_E("AUDIO CAPTURE SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_audio_capture_controls,
		hi6402_audio_capture_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* virtual switch for voiceup 16k */
	SND_SOC_DAPM_SWITCH_E("VOICEUP 16K SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_voiceup_16k_controls,
		hi6402_voiceup_16k_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* virtual switch for voiceup 8k */
	SND_SOC_DAPM_SWITCH_E("VOICEUP 8K SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_voiceup_8k_controls,
		hi6402_voiceup_8k_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* virtual switch for fm */
	SND_SOC_DAPM_SWITCH_E("FM SWITCH",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_fm_controls,
		hi6402_fm_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

	/* MUX */
	SND_SOC_DAPM_MUX("APL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_apl_mux_controls),
	SND_SOC_DAPM_MUX("APR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_apr_mux_controls),
	SND_SOC_DAPM_MUX("BTL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_btl_mux_controls),
	SND_SOC_DAPM_MUX("BTR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_btr_mux_controls),
	SND_SOC_DAPM_MUX("M0L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_m0l_mux_controls),
	SND_SOC_DAPM_MUX("M0R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_m0r_mux_controls),
	SND_SOC_DAPM_MUX("M1L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_m1l_mux_controls),
	SND_SOC_DAPM_MUX("M1R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_m1r_mux_controls),

	SND_SOC_DAPM_MUX("MIXERL S1 MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacl_mixer_mux_controls),
	SND_SOC_DAPM_MUX("MIXERR S1 MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacr_mixer_mux_controls),

	SND_SOC_DAPM_MUX("MDM MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_mdm_src_mux_controls),
	SND_SOC_DAPM_MUX("SIDETONE MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_sidetone_src_mux_controls),

	SND_SOC_DAPM_MUX("DACSL S1L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacsl_s1l_mux_controls),

	SND_SOC_DAPM_MUX("DACSR S1R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacsr_s1r_mux_controls),

	SND_SOC_DAPM_MUX("DACL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacl_src_mixer_mux_controls),
	SND_SOC_DAPM_MUX("DACR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dacr_src_mixer_mux_controls),

	SND_SOC_DAPM_MUX("HPL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dac_hpl_mux_controls),
	SND_SOC_DAPM_MUX("HPR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dac_hpr_mux_controls),

	SND_SOC_DAPM_MUX("EP MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dac_ep_mux_controls),

	SND_SOC_DAPM_MUX("LOL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dac_ltl_mux_controls),
	SND_SOC_DAPM_MUX("LOR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_dac_ltr_mux_controls),

	SND_SOC_DAPM_MUX("ADC0L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_adcl0_mux_controls),
	SND_SOC_DAPM_MUX("ADC0R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_adcr0_mux_controls),
	SND_SOC_DAPM_MUX("ADC1L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_adcl1_mux_controls),
	SND_SOC_DAPM_MUX("ADC1R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_adcr1_mux_controls),

	SND_SOC_DAPM_MUX("LIL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_linel_pga_sel_controls),
	SND_SOC_DAPM_MUX("LIR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_liner_pga_sel_controls),
	SND_SOC_DAPM_MUX("MIC MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6402_dapm_main_pga_sel_controls),

	/* MIXER */
	SND_SOC_DAPM_MIXER("MIXERL",
		HI6402_DAC_MIXER_CLK_REG, HI6402_DACL_MIXER_EN_BIT, 0,
		hi6402_dacl_mixer_controls,
		ARRAY_SIZE(hi6402_dacl_mixer_controls)),
	SND_SOC_DAPM_MIXER("MIXERR",
		HI6402_DAC_MIXER_CLK_REG, HI6402_DACR_MIXER_EN_BIT, 0,
		hi6402_dacr_mixer_controls,
		ARRAY_SIZE(hi6402_dacr_mixer_controls)),
	SND_SOC_DAPM_MIXER("SHARE MIXER",
		HI6402_EQ_SM_CLK_REG, HI6402_SHARE_MIXER_EN_BIT, 0,
		hi6402_share_mixer_controls,
		ARRAY_SIZE(hi6402_share_mixer_controls)),
	SND_SOC_DAPM_MIXER("DACL MIXER",
		HI6402_DAC_SRC_MIXER_CLK_REG, HI6402_DACL_SRC_MIXER_EN_BIT, 0,
		hi6402_dacl_src_mixer_controls,
		ARRAY_SIZE(hi6402_dacl_src_mixer_controls)),
	SND_SOC_DAPM_MIXER("DACR MIXER",
		HI6402_DAC_SRC_MIXER_CLK_REG, HI6402_DACR_SRC_MIXER_EN_BIT, 0,
		hi6402_dacr_src_mixer_controls,
		ARRAY_SIZE(hi6402_dacr_src_mixer_controls)),
	SND_SOC_DAPM_MIXER("DACSL MIXER",
		HI6402_DAC_MIXER_CLK_REG, HI6402_DACSL_MIXER_EN_BIT, 0,
		hi6402_dacsl_mixer_controls,
		ARRAY_SIZE(hi6402_dacsl_mixer_controls)),
	SND_SOC_DAPM_MIXER("DACSR MIXER",
		HI6402_DAC_MIXER_CLK_REG, HI6402_DACSR_MIXER_EN_BIT, 0,
		hi6402_dacsr_mixer_controls,
		ARRAY_SIZE(hi6402_dacsr_mixer_controls)),
};

static const struct snd_soc_dapm_route i2s_route_map[] = {
	{"S1L IN",		NULL,			"S1 RX CLK"},
	{"S1R IN",		NULL,			"S1 RX CLK"},
	{"S1L OUT",		NULL,			"S1 TX CLK"},
	{"S1R OUT",		NULL,			"S1 TX CLK"},
	{"S1 TX CLK",		NULL,			"S1 INTERFACE CLK"},
	{"S1 RX CLK",		NULL,			"S1 INTERFACE CLK"},

	{"S3L IN",		NULL,			"S3 INTERFACE CLK"},
	{"S3R IN",		NULL,			"S3 INTERFACE CLK"},
	{"S3L OUT",		NULL,			"S3 INTERFACE CLK"},
	{"S3R OUT",		NULL,			"S3 INTERFACE CLK"},
};

static const struct snd_soc_dapm_route route_map[] = {
	{"S1 IL PGA",		NULL,			"S1L IN"},
	{"S1 IR PGA",		NULL,			"S1R IN"},
	{"S3 IL PGA",		NULL,			"S3L IN"},
	{"S3 IR PGA",		NULL,			"S3R IN"},
	{"S4 IL PGA",		NULL,			"S4L IN"},
	{"S4 IR PGA",		NULL,			"S4R IN"},

	{"MAD OUT",		NULL,			"MAD SWITCH"},
	{"S1L OUT",		NULL,			"S1 OL SWITCH"},
	{"S1R OUT",		NULL,			"S1 OR SWITCH"},
	{"S2L OUT",		NULL,			"S2 OL SWITCH"},
	{"S2R OUT",		NULL,			"S2 OR SWITCH"},
	{"S3L OUT",		NULL,			"S3 OL SWITCH"},
	{"S3R OUT",		NULL,			"S3 OR SWITCH"},
	{"S4L OUT",		NULL,			"S4 OL SWITCH"},
	{"S4R OUT",		NULL,			"S4 OR SWITCH"},

	{"ECL OUT",		NULL,			"S4 OL SWITCH"},
	{"ECR OUT",		NULL,			"S4 OR SWITCH"},
	/* CLK SUPPLY */
	{"S2L IN",		NULL,			"S2 RX CLK"},
	{"S2R IN",		NULL,			"S2 RX CLK"},
	{"S2L OUT",		NULL,			"S2 TX CLK"},
	{"S2R OUT",		NULL,			"S2 TX CLK"},
	{"S2 TX CLK",		NULL,			"S2 INTERFACE CLK"},
	{"S2 RX CLK",		NULL,			"S2 INTERFACE CLK"},

	{"S4L IN",		NULL,			"S4 RX CLK"},
	{"S4R IN",		NULL,			"S4 RX CLK"},
	{"S4L OUT",		NULL,			"S4 TX CLK"},
	{"S4R OUT",		NULL,			"S4 TX CLK"},
	{"S4 TX CLK",	NULL,			"PLL CLK"},
	{"S4 RX CLK",	NULL,			"PLL CLK"},
	{"S4 TX CLK",	NULL,			"AUDIO CLK"},
	{"S4 RX CLK",	NULL,			"AUDIO CLK"},

	{"S1L IN",				NULL,			"AUDIO CLK"},
	{"S1R IN",				NULL,			"AUDIO CLK"},
	{"S2 INTERFACE CLK",		NULL,			"AUDIO CLK"},
	{"S3L IN",				NULL,			"AUDIO CLK"},
	{"S3R IN",				NULL,			"AUDIO CLK"},
	{"S4 INTERFACE CLK",		NULL,			"AUDIO CLK"},
	{"S1L IN",				NULL,			"PLL CLK"},
	{"S1R IN",				NULL,			"PLL CLK"},
	{"S2 INTERFACE CLK",		NULL,			"PLL CLK"},
	{"S3L IN",				NULL,			"PLL CLK"},
	{"S3R IN",				NULL,			"PLL CLK"},
	{"S4 INTERFACE CLK",		NULL,			"PLL CLK"},
	{"S1L OUT",				NULL,			"AUDIO CLK"},
	{"S1R OUT",				NULL,			"AUDIO CLK"},
	{"S3L OUT",				NULL,			"AUDIO CLK"},
	{"S3R OUT",				NULL,			"AUDIO CLK"},
	{"S3L OUT",				NULL,			"S3IL SWITCH"},
	{"S1L OUT",			NULL,			"REC CLK"},
	{"S1R OUT",			NULL,			"REC CLK"},
	{"MAD OUT",			NULL,			"MAD CLK"},
	{"MAD OUT",			NULL,			"AUDIO CLK"},

	{"MAD SWITCH",		"SWITCH",		"APL MUX"},
	{"S1 OL SWITCH",		"SWITCH",		"APL MUX"},
	{"S1 OR SWITCH",		"SWITCH",		"APR MUX"},
	{"S2 OL SWITCH",		"SWITCH",		"BTL MUX"},
	{"S2 OR SWITCH",		"SWITCH",		"BTR MUX"},
	{"S3 OL SWITCH",		"SWITCH",		"M0L MUX"},
	{"S3 OR SWITCH",		"SWITCH",		"M0R MUX"},
	{"S4 OL SWITCH",		"SWITCH",		"M1L MUX"},
	{"S4 OR SWITCH",		"SWITCH",		"M1R MUX"},

	/* SHARE MIXER */
	{"SHARE MIXER",		"S1L SWITCH",		"S1 IL PGA"},
	{"SHARE MIXER",		"S1R SWITCH",		"S1 IR PGA"},

	/* DAC MIXER MUX */
	{"MIXERL S1 MUX",		"S1 IL",		"S1 IL PGA"},
	{"MIXERL S1 MUX",		"S2 IL",		"S2L IN"},
	{"MIXERL S1 MUX",		"S3 IL",		"S3 IL PGA"},
	{"MIXERL S1 MUX",		"S4 IL",		"S4 IL PGA"},
	{"MIXERL S1 MUX",		"SHARE MIXER",		"SHARE MIXER"},

	{"MIXERR S1 MUX",		"S1 IR",		"S1 IR PGA"},
	{"MIXERR S1 MUX",		"S2 IR",		"S2R IN"},
	{"MIXERR S1 MUX",		"S3 IR",		"S3 IR PGA"},
	{"MIXERR S1 MUX",		"S4 IR",		"S4 IR PGA"},
	{"MIXERR S1 MUX",		"SHARE MIXER",		"SHARE MIXER"},

	/* DAC MIXER */
	{"MIXERL",		"S1L MUX SWITCH",		"MIXERL S1 MUX"},
	{"MIXERL",		"S2L SWITCH",			"S2L IN"},
	{"MIXERL",		"MDM SWITCH",			"MDM MUX"},
	{"MIXERL",		"SIDETONE SWITCH",		"SIDE PGA"},

	{"MIXERR",		"S1R MUX SWITCH",		"MIXERR S1 MUX"},
	{"MIXERR",		"S2R SWITCH",			"S2R IN"},
	{"MIXERR",		"MDM SWITCH",			"MDM MUX"},
	{"MIXERR",		"SIDETONE SWITCH",		"SIDE PGA"},

	/* DAC SRC MIXER MUX */
	{"DACL MUX",		"DSP IF8 IN",			"MIXERL"},
	{"DACL MUX",		"DSP IF8 OUT",			"MIXERL"},

	{"DACR MUX",		"DSP IF8 IN",			"MIXERR"},
	{"DACR MUX",		"DSP IF8 OUT",			"MIXERR"},

	/* DAC SRC MIXER */
	{"DACL MIXER",		"DSP IF8 SWITCH",		"DACL MUX"},
	{"DACL MIXER",		"SIDETONE SWITCH",		"SIDE PGA"},

	{"DACR MIXER",		"DSP IF8 SWITCH",		"DACR MUX"},
	{"DACR MIXER",		"SIDETONE SWITCH",		"SIDE PGA"},
	/* DACS MUX */
	{"DACSL MIXER",		"S1L MUX SWITCH",		"DACSL S1L MUX"},
	{"DACSL MIXER",		"L SWITCH",				"MIXERL"},
	{"DACSL MIXER",		"R SWITCH",				"MIXERR"},
	{"DACSL MIXER",		"SIDETONE SWITCH",		"SIDE PGA"},

	{"DACSR MIXER",		"S1R MUX SWITCH",		"DACSR S1R MUX"},
	{"DACSR MIXER",		"L SWITCH",				"MIXERL"},
	{"DACSR MIXER",		"R SWITCH",				"MIXERR"},
	{"DACSR MIXER",		"SIDETONE SWITCH",		"SIDE PGA"},

	{"DACSL S1L MUX",		"S1 L",					"S1 IL PGA"},
	{"DACSL S1L MUX",		"SHARE MIXER",			"SHARE MIXER"},

	{"DACSR S1R MUX",		"S1 R",					"S1 IR PGA"},
	{"DACSR S1R MUX",		"SHARE MIXER",			"SHARE MIXER"},

	/* DACL PGA */
	{"DACL PGA",		NULL,		"DACL MIXER"},
	{"DACR PGA",		NULL,		"DACR MIXER"},
	{"DACSL PGA",		NULL,		"DACSL MIXER"},
	{"DACSR PGA",		NULL,		"DACSR MIXER"},

	{"DACL PGA",		NULL,		"AUDIO CLK"},
	{"DACR PGA",		NULL,		"AUDIO CLK"},
	{"DACSL PGA",		NULL,		"AUDIO CLK"},
	{"DACSR PGA",		NULL,		"AUDIO CLK"},
	{"DACL PGA",		NULL,		"PLL CLK"},
	{"DACR PGA",		NULL,		"PLL CLK"},
	{"DACSL PGA",		NULL,		"PLL CLK"},
	{"DACSR PGA",		NULL,		"PLL CLK"},

	{"HP HIGH OUT",		NULL,		"HPDAC_I2V"},
	{"HPDAC_I2V",		"SWITCH",	"HP HIGH IN"},

	{"UP OUT",          NULL,       "AUDIO CAPTURE SWITCH"},
	{"AUDIO CAPTURE SWITCH",   "SWITCH",   "UP IN"},

	{"UP OUT",          NULL,       "VOICEUP 8K SWITCH"},
	{"VOICEUP 8K SWITCH",   "SWITCH",   "UP IN"},

	{"UP OUT",          NULL,       "VOICEUP 16K SWITCH"},
	{"VOICEUP 16K SWITCH",   "SWITCH",   "UP IN"},

	{"UP OUT",          NULL,       "MODEM AUDIO 8K SWITCH"},
	{"MODEM AUDIO 8K SWITCH",   "SWITCH",   "UP IN"},

	{"UP OUT",          NULL,       "MODEM AUDIO 16K SWITCH"},
	{"MODEM AUDIO 16K SWITCH",   "SWITCH",   "UP IN"},

	{"UP OUT",          NULL,       "FM SWITCH"},
	{"FM SWITCH",   "SWITCH",   "UP IN"},

	/* HPL MUX */
	{"HPL MUX",		"DACL",		"DACL PGA"},
	{"HPL MUX",		"DACR",		"DACR PGA"},

	/* HPR MUX */
	{"HPR MUX",		"DACL",		"DACL PGA"},
	{"HPR MUX",		"DACR",		"DACR PGA"},

	/* EP MUX */
	{"EP MUX",		"DACL",		"DACL PGA"},
	{"EP MUX",		"DACSL",		"DACSL PGA"},
	{"EP MUX",		"DACR",		"DACR PGA"},
	{"EP MUX",		"DACSR",	"DACSR PGA"},

	/* LOL MUX */
	{"LOL MUX",		"DACL",		"DACL PGA"},
	{"LOL MUX",		"DACSL",		"DACSL PGA"},
	{"LOL MUX",		"DACR",		"DACR PGA"},
	{"LOL MUX",		"DACSR",	"DACSR PGA"},

	/* LOR MUX */
	{"LOR MUX",		"DACL",		"DACL PGA"},
	{"LOR MUX",		"DACSL",		"DACSL PGA"},
	{"LOR MUX",		"DACR",		"DACR PGA"},
	{"LOR MUX",		"DACSR",	"DACSR PGA"},

	/* OUT DRIVER */
	{"HPL DRV",		NULL,		"HPL MUX"},
	{"HPR DRV",		NULL,		"HPR MUX"},

	{"EP DRV",		NULL,		"EP SWITCH"},
	{"EP SWITCH",	"SWITCH",	"EP MUX"},

	{"LOL DRV",		NULL,		"LOL MUX"},
	{"LOR DRV",		NULL,		"LOR MUX"},

	/* OUTPUT */
	{"EAR OUT",		NULL,		"EP DRV"},
	{"HPL OUT",		NULL,		"HPL DRV"},
	{"HPR OUT",		NULL,		"HPR DRV"},
	{"LINEOUT L",		NULL,		"LOL DRV"},
	{"LINEOUT R",		NULL,		"LOR DRV"},

	{"HPL DRV",		NULL,		"CP2"},
	{"HPR DRV",		NULL,		"CP2"},
	{"EP DRV",		NULL,		"CP1"},

	{"CP2",			NULL,		"CP1"},
	{"CP1",			NULL,		"PLL CLK"},

	/* SIDETONE MUX */
	{"SIDETONE MUX",		"S1 IL",		"S1 IL PGA"},
	{"SIDETONE MUX",		"S2 IL",		"S2L IN"},
	{"SIDETONE MUX",		"S3 IL",		"S3 IL PGA"},
	{"SIDETONE MUX",		"S4 IL",		"S4 IL PGA"},
	{"SIDETONE MUX",		"ADC0L",		"ADC0L"},
	{"SIDETONE MUX",		"ADC0R",		"ADC0R"},
	{"SIDETONE MUX",		"ADC1L",		"ADC1L"},
	{"SIDETONE MUX",		"ADC1R",		"ADC1R"},
	{"SIDETONE MUX",		"SHARE MIXER",		"SHARE MIXER"},

	/* MDM MUX */
	{"MDM MUX",		"S1 IL",		"S1 IL PGA"},
	{"MDM MUX",		"S2 IL",		"S2L IN"},
	{"MDM MUX",		"S3 IL",		"S3 IL PGA"},
	{"MDM MUX",		"S4 IL",		"S4 IL PGA"},
	{"MDM MUX",		"ADC0L",		"ADC0L"},
	{"MDM MUX",		"ADC0R",		"ADC0R"},
	{"MDM MUX",		"ADC1L",		"ADC1L"},
	{"MDM MUX",		"ADC1R",		"ADC1R"},
	{"MDM MUX",		"SHARE MIXER",		"SHARE MIXER"},
	{"S3IL SWITCH", 	"SWITCH",	"MDM MUX"},

	/* SIDE PGA */
	{"SIDE PGA",		NULL,		"SIDETONE MUX"},

	/* APL MUX */
	{"APL MUX",		"ADC0L",		"ADC0L"},
	{"APL MUX",		"ADC1L",		"ADC1L"},
	{"APL MUX",		"DACSL",		"DACSL MIXER"},
	{"APL MUX",		"DACL_48",		"DACL MIXER"},
	{"APL MUX",		"S1L",			"S1 IL PGA"},
	{"APL MUX",		"S2L",			"S2L IN"},
	{"APL MUX",		"S3L",			"S3 IL PGA"},
	{"APL MUX",		"S4L",			"S4 IL PGA"},
	{"APL MUX",		"MDM",			"MDM MUX"},
	{"APL MUX",		"BT0",			"S2 OL SWITCH"},
	{"APL MUX",		"MDM0",			"S3 OL SWITCH"},
	{"APL MUX",		"MDM2",			"S4 OL SWITCH"},

	/* APR MUX */
	{"APR MUX",		"ADC0R",		"ADC0R"},
	{"APR MUX",		"ADC1R",		"ADC1R"},
	{"APR MUX",		"DACSR",		"DACSR MIXER"},
	{"APR MUX",		"DACR_48",		"DACR MIXER"},
	{"APR MUX",		"S1R",			"S1 IR PGA"},
	{"APR MUX",		"S2R",			"S2R IN"},
	{"APR MUX",		"S3R",			"S3 IR PGA"},
	{"APR MUX",		"S4R",			"S4 IR PGA"},
	{"APR MUX",		"MDM",			"MDM MUX"},
	{"APR MUX",		"BT1",			"S2 OR SWITCH"},
	{"APR MUX",		"MDM1",			"S3 OR SWITCH"},
	{"APR MUX",		"MDM3",			"S4 OR SWITCH"},

	/* BTL MUX */
	{"BTL MUX",		"ADC0L",		"ADC0L"},
	{"BTL MUX",		"ADC1L",		"ADC1L"},
	{"BTL MUX",		"DACSL",		"DACSL MIXER"},
	{"BTL MUX",		"DACL_48",		"DACL MIXER"},
	{"BTL MUX",		"S1L",			"S1 IL PGA"},
	{"BTL MUX",		"S2L",			"S2L IN"},
	{"BTL MUX",		"S3L",			"S3 IL PGA"},
	{"BTL MUX",		"S4L",			"S4 IL PGA"},
	{"BTL MUX",		"MDM",			"MDM MUX"},
	{"BTL MUX",		"AP0",			"S1 OL SWITCH"},
	{"BTL MUX",		"MDM0",			"S3 OL SWITCH"},
	{"BTL MUX",		"MDM2",			"S4 OL SWITCH"},

	/* BTR MUX */
	{"BTR MUX",		"ADC0R",		"ADC0R"},
	{"BTR MUX",		"ADC1R",		"ADC1R"},
	{"BTR MUX",		"DACSR",		"DACSR MIXER"},
	{"BTR MUX",		"DACR_48",		"DACR MIXER"},
	{"BTR MUX",		"S1R",			"S1 IR PGA"},
	{"BTR MUX",		"S2R",			"S2R IN"},
	{"BTR MUX",		"S3R",			"S3 IR PGA"},
	{"BTR MUX",		"S4R",			"S4 IR PGA"},
	{"BTR MUX",		"MDM",			"MDM MUX"},
	{"BTR MUX",		"AP1",			"S1 OR SWITCH"},
	{"BTR MUX",		"MDM1",			"S3 OR SWITCH"},
	{"BTR MUX",		"MDM3",			"S4 OR SWITCH"},

	/* M0L MUX */
	{"M0L MUX",		"ADC0L",		"ADC0L"},
	{"M0L MUX",		"ADC1L",		"ADC1L"},
	{"M0L MUX",		"DACSL",		"DACSL MIXER"},
	{"M0L MUX",		"DACL_48",		"DACL MIXER"},
	{"M0L MUX",		"S1L",			"S1 IL PGA"},
	{"M0L MUX",		"S2L",			"S2L IN"},
	{"M0L MUX",		"S3L",			"S3 IL PGA"},
	{"M0L MUX",		"S4L",			"S4 IL PGA"},
	{"M0L MUX",		"MDM",			"MDM MUX"},
	{"M0L MUX",		"AP0",			"S1 OL SWITCH"},
	{"M0L MUX",		"BT0",			"S2 OL SWITCH"},
	{"M0L MUX",		"MDM2",			"S4 OL SWITCH"},

	/* M0R MUX */
	{"M0R MUX",		"ADC0R",		"ADC0R"},
	{"M0R MUX",		"ADC1R",		"ADC1R"},
	{"M0R MUX",		"DACSR",		"DACSR MIXER"},
	{"M0R MUX",		"DACR_48",		"DACR MIXER"},
	{"M0R MUX",		"S1R",			"S1 IR PGA"},
	{"M0R MUX",		"S2R",			"S2R IN"},
	{"M0R MUX",		"S3R",			"S3 IR PGA"},
	{"M0R MUX",		"S4R",			"S4 IR PGA"},
	{"M0R MUX",		"MDM",			"MDM MUX"},
	{"M0R MUX",		"AP1",			"S1 OR SWITCH"},
	{"M0R MUX",		"BT1",			"S2 OR SWITCH"},
	{"M0R MUX",		"MDM3",			"S4 OR SWITCH"},

	/* M1L MUX */
	{"M1L MUX",		"ADC0L",		"ADC0L"},
	{"M1L MUX",		"ADC1L",		"ADC1L"},
	{"M1L MUX",		"DACSL",		"DACSL MIXER"},
	{"M1L MUX",		"DACL_48",		"DACL MIXER"},
	{"M1L MUX",		"DACL_48",		"ECL IN"},
	{"M1L MUX",		"S1L",			"S1 IL PGA"},
	{"M1L MUX",		"S2L",			"S2L IN"},
	{"M1L MUX",		"S3L",			"S3 IL PGA"},
	{"M1L MUX",		"S4L",			"S4 IL PGA"},
	{"M1L MUX",		"MDM",			"MDM MUX"},
	{"M1L MUX",		"AP0",			"S1 OL SWITCH"},
	{"M1L MUX",		"MDM0",			"S2 OL SWITCH"},
	{"M1L MUX",		"MDM0",			"S4 OL SWITCH"},

	/* M1R MUX */
	{"M1R MUX",		"ADC0R",		"ADC0R"},
	{"M1R MUX",		"ADC1R",		"ADC1R"},
	{"M1R MUX",		"DACSR",		"DACSR MIXER"},
	{"M1R MUX",		"DACR_48",		"DACR MIXER"},
	{"M1R MUX",		"DACR_48",		"ECR IN"},
	{"M1R MUX",		"S1R",			"S1 IR PGA"},
	{"M1R MUX",		"S2R",			"S2R IN"},
	{"M1R MUX",		"S3R",			"S3 IR PGA"},
	{"M1R MUX",		"S4R",			"S4 IR PGA"},
	{"M1R MUX",		"MDM",			"MDM MUX"},
	{"M1R MUX",		"AP1",			"S1 OR SWITCH"},
	{"M1R MUX",		"MDM1",			"S2 OR SWITCH"},
	{"M1R MUX",		"MDM1",			"S4 OR SWITCH"},

	/* ADC */
	{"ADC0L",		NULL,		"ADC0L MUX"},
	{"ADC0R",		NULL,		"ADC0R MUX"},
	{"ADC1L",		NULL,		"ADC1L MUX"},
	{"ADC1R",		NULL,		"ADC1R MUX"},


	/* ADC MUX */
	{"ADC0L MUX",		"MAINMIC",		"MAINMIC PGA"},
	{"ADC0L MUX",		"AUXMIC",		"AUXMIC PGA"},
	{"ADC0L MUX",		"LINEINL",		"LINEINL PGA"},
	{"ADC0L MUX",		"LINEINR",		"LINEINR PGA"},
	{"ADC0L MUX",		"DMIC0L",		"DIGMIC0"},
	{"ADC0L MUX",		"DMIC0R",		"DIGMIC0"},
	{"ADC0L MUX",		"DMIC1L",		"DIGMIC1"},
	{"ADC0L MUX",		"DMIC1R",		"DIGMIC1"},

	{"ADC0R MUX",		"MAINMIC",		"MAINMIC PGA"},
	{"ADC0R MUX",		"AUXMIC",		"AUXMIC PGA"},
	{"ADC0R MUX",		"LINEINL",		"LINEINL PGA"},
	{"ADC0R MUX",		"LINEINR",		"LINEINR PGA"},
	{"ADC0R MUX",		"DMIC0L",		"DIGMIC0"},
	{"ADC0R MUX",		"DMIC0R",		"DIGMIC0"},
	{"ADC0R MUX",		"DMIC1L",		"DIGMIC1"},
	{"ADC0R MUX",		"DMIC1R",		"DIGMIC1"},

	{"ADC1L MUX",		"MAINMIC",		"MAINMIC PGA"},
	{"ADC1L MUX",		"AUXMIC",		"AUXMIC PGA"},
	{"ADC1L MUX",		"LINEINL",		"LINEINL PGA"},
	{"ADC1L MUX",		"LINEINR",		"LINEINR PGA"},
	{"ADC1L MUX",		"DMIC0L",		"DIGMIC0"},
	{"ADC1L MUX",		"DMIC0R",		"DIGMIC0"},
	{"ADC1L MUX",		"DMIC1L",		"DIGMIC1"},
	{"ADC1L MUX",		"DMIC1R",		"DIGMIC1"},

	{"ADC1R MUX",		"MAINMIC",		"MAINMIC PGA"},
	{"ADC1R MUX",		"AUXMIC",		"AUXMIC PGA"},
	{"ADC1R MUX",		"LINEINL",		"LINEINL PGA"},
	{"ADC1R MUX",		"LINEINR",		"LINEINR PGA"},
	{"ADC1R MUX",		"DMIC0L",		"DIGMIC0"},
	{"ADC1R MUX",		"DMIC0R",		"DIGMIC0"},
	{"ADC1R MUX",		"DMIC1L",		"DIGMIC1"},
	{"ADC1R MUX",		"DMIC1R",		"DIGMIC1"},

	{"MAINMIC PGA",			NULL,		"MIC MUX"},
	{"LINEINL PGA",			NULL,		"LIL MUX"},
	{"LINEINR PGA",			NULL,		"LIR MUX"},
	{"AUXMIC PGA",			NULL,		"AUXMIC"},

	{"LIL MUX",		"LINEIN1",		"LINEIN1"},
	{"LIL MUX",		"LINEIN2",		"LINEIN2"},
	{"LIL MUX",		"LINEOUT",		"LINE OUTL"},
	{"LIL MUX",		"MIC2",			"MIC2"},

	{"LIR MUX",		"LINEIN1",		"LINEIN1"},
	{"LIR MUX",		"LINEIN2",		"LINEIN2"},
	{"LIR MUX",		"LINEOUT",		"LINE OUTR"},
	{"LIR MUX",		"MIC3",			"MIC3"},

	{"MIC MUX",			"MAIN MIC",		"MAINMIC"},
	{"MIC MUX",			"HS MIC",		"HSMIC"},

	/* ANA IN */
	{"MAINMIC",			NULL,		"MAIN MIC"},
	{"HSMIC",			NULL,		"HS MIC"},
	{"AUXMIC",			NULL,		"AUX MIC"},
	{"MIC2",			NULL,		"MIC2 IN"},
	{"MIC3",			NULL,		"MIC3 IN"},

	/* SMART PA ROUTE */
	{"SP IL SWITCH",		"SWITCH",		"S4L IN"},
	{"SP IR SWITCH",		"SWITCH",		"S4R IN"},

	{"SP L OUT",			NULL,			"SP IL SWITCH"},
	{"SP R OUT",			NULL,			"SP IL SWITCH"},
};

static bool hi6402_reg_peri_dev(unsigned int reg)
{
	unsigned int reg_mask;

	reg_mask = reg & 0xFFFFF000;

	/* peri device: timer0, timer1, wd, gpio, sctrl, uart, ios, dma */
	if (0x20000000 == reg_mask || 0x20001000 == reg_mask
		|| 0x20002000 == reg_mask || 0x20003000 == reg_mask
		|| 0x20004000 == reg_mask || 0x20005000 == reg_mask
		|| 0x20006000 == reg_mask || 0x20008000 == reg_mask
		|| 0x20009000 == reg_mask || 0x2000a000 == reg_mask
		|| 0x2000b000 == reg_mask) {
		return true;
	} else {
		return false;
	}
}

static unsigned int hi6402_reg_read(struct snd_soc_codec *codec,
		unsigned int reg)
{
	unsigned int ret;
	unsigned int reg_mask;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	bool peri_reg = false;

	BUG_ON(NULL == priv);

	reg_mask = reg & 0xFFFFF000;
	if (0x7000 == reg_mask || 0x1000 == reg_mask) {
		reg = reg | 0x20000000;
	} else if (0xc000 == reg_mask ) {
		mutex_lock(&priv->rw_mutex);
		ret = priv->mm_reg;
		mutex_unlock(&priv->rw_mutex);
		return ret;
	} else {

	}

	if (hi6402_reg_peri_dev(reg)) {
		peri_reg = true;
		hi64xx_hifi_misc_peri_lock();
	}

	hi64xx_resmgr_request_reg_access(priv->resmgr, reg);
	ret = hi_cdcctrl_reg_read(priv->cdc_ctrl, reg);
	hi64xx_resmgr_release_reg_access(priv->resmgr, reg);

	if (peri_reg) {
		hi64xx_hifi_misc_peri_unlock();
	}

	return ret;
}

static int hi6402_reg_write(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int value)
{
	int ret = 0;
	unsigned int reg_mask;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	bool peri_reg = false;

	BUG_ON(NULL == priv);

#ifdef CONFIG_DEBUG_FS
	/*record reg*/
	hi64xx_reg_wr_cache(reg, value);
#endif

	reg_mask = reg & 0xFFFFF000;
	if (0x7000 == reg_mask || 0x1000 == reg_mask) {
		reg = reg | 0x20000000;
	} else if (0xc000 == reg_mask ) {
		mutex_lock(&priv->rw_mutex);
		priv->mm_reg = value;
		mutex_unlock(&priv->rw_mutex);
		return ret;
	} else {

	}

	if (hi6402_reg_peri_dev(reg)) {
		peri_reg = true;
		hi64xx_hifi_misc_peri_lock();
	}

	hi64xx_resmgr_request_reg_access(priv->resmgr, reg);
	ret = hi_cdcctrl_reg_write(priv->cdc_ctrl, reg, value);
	hi64xx_resmgr_release_reg_access(priv->resmgr, reg);

	if (peri_reg) {
		hi64xx_hifi_misc_peri_unlock();
	}

	return ret;
}

static void hi6402_init_chip(struct snd_soc_codec *codec)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	/* check chip id */
	/* S1-S4 I2S INIT */
	hi64xx_update_bits(codec, 0x1000, 0x000000F0, 0x000000A0);

	hi64xx_update_bits(codec, HI6402_AUD_CLK_EN_PAGE, 1 << HI6402_AUD_CLK_EN_BIT, 1 << HI6402_AUD_CLK_EN_BIT);
	snd_soc_write(codec, HI6402_S_PORT_IN_SEL, 0x33);

	snd_soc_write(codec, 0x1238, 0x000000C4);
	snd_soc_write(codec, 0x1258, 0x000000C4);

	/* GPIO 0 CFG */
	hi64xx_update_bits(codec, HI6402_GPIO_0_CFG_REG, 1 << HI6402_GPIO_PD_BIT, 1 << HI6402_GPIO_PD_BIT);

	/* SLIMBUS UPLINK MUX INIT */
	snd_soc_write(codec, HI6402_CODEC_MUX_SEL4_0, 0x00);
	snd_soc_write(codec, HI6402_CODEC_MUX_SEL4_1, 0x11);
	snd_soc_write(codec, HI6402_CODEC_MUX_SEL4_2, 0x22);
	snd_soc_write(codec, HI6402_CODEC_MUX_SEL4_3, 0x33);

	/* S1 PORT IN */
	snd_soc_write(codec, HI6402_S1_PORT_CFG_L, 0x00);
	snd_soc_write(codec, HI6402_S1_PORT_CFG_H, 0x70);

	/* S1 FS INIT */
	hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 0x07, 0x04);

	/* S1-S4 MUX FOR SRC */
	snd_soc_write(codec, HI6402_S_PORT_SRC_IN_SEL0, 0x00);
	snd_soc_write(codec, HI6402_S_PORT_SRC_IN_SEL1, 0x00);

	/* S1 SRC */
	hi64xx_update_bits(codec, HI6402_S1_SRC_IN_MODE_CGF, 0xEE, 0x00);
	hi64xx_update_bits(codec, HI6402_S1_MODULE_CLK_REG, 0x0C, 0x00);

	/* MUX FOR EQ */
	hi64xx_update_bits(codec, HI6402_EQ_MUX_SEL, 0x03, 0x00);
	hi64xx_update_bits(codec, HI6402_EQ_MUX_SEL, 0x0C, 0x00);
	hi64xx_update_bits(codec, HI6402_SHARE_MUX_SEL, 1 << 3, 0);

	/* S2 PORT IN */
	snd_soc_write(codec, HI6402_S2_PORT_CFG_L, 0x00);
	snd_soc_write(codec, HI6402_S2_PORT_CFG_H, 0x40);

	/* S2 FS INIT */
	hi64xx_update_bits(codec, HI6402_S2_FS_CFG_L, 0x07, 0x04);

	/* S2 SRC */
	hi64xx_update_bits(codec, HI6402_S2_SRC_IN_MODE_CGF, 0xEE, 0x00);
	hi64xx_update_bits(codec, HI6402_S2_MODULE_CLK_REG, 0x0C, 0x00);

	/* S3 PORT IN */
	snd_soc_write(codec, HI6402_S3_PORT_CFG_L, 0x00);
	snd_soc_write(codec, HI6402_S3_PORT_CFG_H, 0x40);

	/* S3 FS INIT */
	hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x04);

	/* S3 SRC */
	hi64xx_update_bits(codec, HI6402_S3_SRC_IN_MODE_CGF, 0xEE, 0x00);
	hi64xx_update_bits(codec, HI6402_S3_MODULE_CLK_REG, 0x0C, 0x00);

	/* S4 PORT IN */
	snd_soc_write(codec, HI6402_S4_PORT_CFG_L, 0x00);

	/* under stereo smartpa , set the I2S4 port to 24bit */
	if (priv->board_cfg.use_stereo_smartpa) {
		snd_soc_write(codec, HI6402_S4_PORT_CFG_H, 0x70);
	} else {
		snd_soc_write(codec, HI6402_S4_PORT_CFG_H, 0x40);
	}

	/* S4 FS INIT */
	hi64xx_update_bits(codec, HI6402_S4_FS_CFG_L, 0x07, 0x04);

	/* S4 SRC */
	hi64xx_update_bits(codec, HI6402_S4_SRC_IN_MODE_CGF, 0xEE, 0x00);
	hi64xx_update_bits(codec, HI6402_S4_MODULE_CLK_REG, 0x0C, 0x00);

	/* DSP IF BYPASS INIT */
	hi64xx_update_bits(codec, HI6402_S1_DSP_IF_SEL, 0xC0, 0xC0);
	hi64xx_update_bits(codec, HI6402_S2_DSP_IF_SEL, 0xC0, 0xC0);
	hi64xx_update_bits(codec, HI6402_S3_DSP_IF_SEL, 0xC0, 0xC0);
	hi64xx_update_bits(codec, HI6402_S4_DSP_IF_SEL, 0xC0, 0xC0);
	hi64xx_update_bits(codec, HI6402_DSP_IF8_SEL, 0x10, 0x10);

	/* DAC SRC MODE x2 */
	snd_soc_write(codec, HI6402_DAC_SRC_MODE_REG, 0x88);

	/* DAC DEEMP BYPASS */
	hi64xx_update_bits(codec, HI6402_DAC_FILTER_OUTR_MUX_SEL, 1 << HI6402_DAC_DEEMP_BYPASS_BIT, 1 << HI6402_DAC_DEEMP_BYPASS_BIT);
	hi64xx_update_bits(codec, HI6402_DAC_FILTER_OUTL_MUX_SEL, 1 << HI6402_DAC_DEEMP_BYPASS_BIT, 1 << HI6402_DAC_DEEMP_BYPASS_BIT);

	/* DSP IF8 & SIDETONE SRC & MDM SRC FS CFG */
	snd_soc_write(codec, HI6402_FS_DSM_CFG_REG, 0x42);

	/* S1 DSP IF FS CFG */
	snd_soc_write(codec, HI6402_S1_DSP_IF_FS_CFG_REG, 0x44);

	/* MIXER MUTE INT */
	hi64xx_update_bits(codec, HI6402_DACL_MIXER_SEL_0, 0xE0, 0xE0);
	hi64xx_update_bits(codec, HI6402_DACL_MIXER_SEL_1, 0x20, 0x20);

	hi64xx_update_bits(codec, HI6402_DACR_MIXER_SEL_0, 0xE0, 0xE0);
	hi64xx_update_bits(codec, HI6402_DACR_MIXER_SEL_1, 0x20, 0x20);

	hi64xx_update_bits(codec, HI6402_SHARE_MIXER_SEL_0, 0x60, 0x60);

	hi64xx_update_bits(codec, HI6402_DACSL_MIXER_SEL, 0x60, 0x60);
	hi64xx_update_bits(codec, HI6402_DACSR_MIXER_SEL, 0x60, 0x60);

	/* MIXER GAIN */
	hi64xx_update_bits(codec, HI6402_DACSL_MIXER_GAIN_REG, 0x0F, 0x0F);
	hi64xx_update_bits(codec, HI6402_DACSR_MIXER_GAIN_REG, 0x0F, 0x0F);
	snd_soc_write(codec, HI6402_DACS_L_MIXER_GAIN_REG, 0xD7);
	snd_soc_write(codec, HI6402_DACS_R_MIXER_GAIN_REG, 0xFF);

	hi64xx_update_bits(codec, HI6402_DACL_MIXER_GAIN_REG, 0xFF, 0xFF);
	hi64xx_update_bits(codec, HI6402_DACR_MIXER_GAIN_REG, 0xFF, 0xFF);

	hi64xx_update_bits(codec, HI6402_SHARE_MIXER_GAIN_REG, 0x0F, 0x0F);

	/* MUX FOR IN2 OF MIXER4  */
	hi64xx_update_bits(codec, HI6402_IN_OUT_MIXER4_MUX_SEL, 0x03, 0x01);
	hi64xx_update_bits(codec, HI6402_IN_OUT_MIXER4_MUX_SEL, 0x0c, 0x04);

	/* MUX OF MIXER4 OUT */
	hi64xx_update_bits(codec, HI6402_IN_OUT_MIXER4_MUX_SEL, 0x30, 0x10);

	/* MUX OF FILTER OUT */
	hi64xx_update_bits(codec, HI6402_DAC_FILTER_OUTL_MUX_SEL, 1 << 7, 0);
	hi64xx_update_bits(codec, HI6402_DAC_FILTER_OUTR_MUX_SEL, 1 << 7, 0);

	/* MUX FOR SDM */
	hi64xx_update_bits(codec, HI6402_DAC_SDM_MUX_SEL, 0x03, 0x00);
	hi64xx_update_bits(codec, HI6402_DACS_SDM_MUX_SEL, 0xF0, 0x00);

	/* MUX FOR SRCDN */
	snd_soc_write(codec, HI6402_SRCDN_MUX_SEL, 0x00);

	/* MUX OF SRC OUT */
	hi64xx_update_bits(codec, HI6402_SHARE_MUX_SEL, 0xF0, 0x00);

	/* MUX OF ANADAC OUT */
	snd_soc_write(codec, HI6402_DAC_HP_MUX_SEL, 0x12);
	snd_soc_write(codec, HI6402_DAC_LT_MUX_SEL, 0x49);

	/* MUX FOR DAC SRC MIXER2 */
	hi64xx_update_bits(codec, HI6402_DAC_SRC_MIXER_MUX_SEL, 1 << HI6402_DACL_SRC_MIXER_MUX_BIT, 1 << HI6402_DACL_SRC_MIXER_MUX_BIT);
	hi64xx_update_bits(codec, HI6402_DAC_SRC_MIXER_MUX_SEL, 1 << HI6402_DACR_SRC_MIXER_MUX_BIT, 1 << HI6402_DACR_SRC_MIXER_MUX_BIT);

	/* DIG PGA */
	snd_soc_write(codec, HI6402_S1_PGA_IL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S1_PGA_IR_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S1_PGA_OL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S1_PGA_OR_GAIN_CFG_REG, 0x0);

	snd_soc_write(codec, HI6402_S2_PGA_IL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S2_PGA_IR_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S2_PGA_OL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S2_PGA_OR_GAIN_CFG_REG, 0x0);

	snd_soc_write(codec, HI6402_S3_PGA_IL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S3_PGA_IR_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S3_PGA_OL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S3_PGA_OR_GAIN_CFG_REG, 0x0);

	snd_soc_write(codec, HI6402_S4_PGA_IL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S4_PGA_IR_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S4_PGA_OL_GAIN_CFG_REG, 0x0);
	snd_soc_write(codec, HI6402_S4_PGA_OR_GAIN_CFG_REG, 0x0);

	/* MAINMIC PGA GAIN */
	hi64xx_update_bits(codec, HI6402_MAIN_PGA_SEL_REG, 0x1F<<HI6402_MAIN_PGA_GAIN_BIT, 0x40);
	/* AUXMIC PGA GAIN */
	hi64xx_update_bits(codec, HI6402_AUX_PGA_SEL_REG, 0x1F<<HI6402_AUX_PGA_GAIN_BIT, 0x80);

	/* MAIN AUX MICBIAS VALUE */
	hi64xx_update_bits(codec, HI6402_MAIN_AUX_MICBIAS_VALUE_REG, 0x3F, 0x36);

	/* HS MICBIAS VALUE */
	hi64xx_update_bits(codec, HI6402_HS_MICBIAS_VALUE_REG, 0x07, 0x06);
	/* MAIN AUX MICBIAS VALUE */
	hi64xx_update_bits(codec, HI6402_MAIN_AUX_MICBIAS_VALUE_REG, 0x3F, 0x36);
	/* MIC2 MIC3 MICBIAS VALUE */
	hi64xx_update_bits(codec, HI6402_MIC2_MIC3_MICBIAS_VALUE_REG, 0x3F, 0x36);
	/* HP PGA GAIN to -15.5dB */
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 0x3F, 0x0F);
	hi64xx_update_bits(codec, HI6402_HPR_PGA_CFG_REG, 0x3F, 0x0F);

	/* i2v cfg */
	/* i2v 8k & 3/4 current & 1/8 ibias */
	snd_soc_write(codec, HI6402_DAC_HPL_I2V_CFG_REG, 0x92);
	snd_soc_write(codec, HI6402_DAC_HPR_I2V_CFG_REG, 0x92);

	/* DIG PGA GAIN -9dB */
	snd_soc_write(codec, HI6402_DACL_PGA_GAIN_CFG_REG, 0xF7);
	snd_soc_write(codec, HI6402_DACR_PGA_GAIN_CFG_REG, 0xF7);

	/* pop cfg */
	hi64xx_update_bits(codec, HI6402_HPL_POP_CFG1_REG, 0x3F, 0x013);
	snd_soc_write(codec, HI6402_HPL_POP_CFG2_REG, 0xE2);
	hi64xx_update_bits(codec, HI6402_HPL_PGA_CFG_REG, 1 << HI6402_HP_POP_D_BIT, 1 << HI6402_HP_POP_D_BIT);

	/* DAC CTR */
	hi64xx_update_bits(codec, HI6402_ANA_DAC_CTR_REG, 0xC0, 0xC0);

	/* ISO release */
	hi64xx_update_bits(codec, HI6402_ISO_REG, 1 << HI6402_ISO_A18_REG_BIT, 1 << HI6402_ISO_A18_REG_BIT);
	hi64xx_update_bits(codec, HI6402_ISO_REG, 1 << HI6402_ISO_A33_REG_BIT, 1 << HI6402_ISO_A33_REG_BIT);

	/* HS DET TIME CFG */
	snd_soc_write(codec, HI6402_HS_DET_TIME_CFG, 0x14);

	/* uplink ADC fix in LOWPOWER MODE  */
	snd_soc_write(codec, HI6402_ANA_REG29, 0x0);
	snd_soc_write(codec, HI6402_ANA_REG30, 0x0);
	snd_soc_write(codec, HI6402_ANA_REG31, 0x7);
	snd_soc_write(codec, HI6402_ANA_REG35, 0x0);

	/* cp2 clk init */
	snd_soc_write(codec, HI6402_CP2_CLK_PD_REG, 0xED);
	snd_soc_write(codec, HI6402_HPLR_CTRL_REG, 0x4B);

	/* cp2 clk -> 48k */
	hi64xx_update_bits(codec, HI6402_CP2_CLK_PD_REG, 0x01C, 0x1C);

	/* cp clk div */
	hi64xx_update_bits(codec, HI6402_CP_CLK_SEL_REG, 0x7, 0x3);

	/* fade back cp init */
	snd_soc_write(codec, HI6402_FADE_BACK_REG, 0xFF);

	/* s2 pga always on */
	hi64xx_update_bits(codec, HI6402_S2_MODULE_CLK_REG, 1 << HI6402_S2_PGA_IL_EN_BIT, 1 << HI6402_S2_PGA_IL_EN_BIT);
	hi64xx_update_bits(codec, HI6402_S2_MODULE_CLK_REG, 1 << HI6402_S2_PGA_IR_EN_BIT, 1 << HI6402_S2_PGA_IR_EN_BIT);

	/* enable dac pga fadein/fadeout */
	snd_soc_write(codec, HI6402_DACL_PGA_MODE_CFG_REG1,0x80);
	snd_soc_write(codec, HI6402_DACR_PGA_MODE_CFG_REG1,0x80);
}

int hi6402_low_pll_turn_on(struct snd_soc_codec *codec)
{
	/* 32k -> pll clk */
	hi64xx_update_bits(codec, HI6402_PLL_CLK_SEL_REG, 1 <<  HI6402_PLL_CLK_SEL_REG_BIT, 1 <<  HI6402_PLL_CLK_SEL_REG_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_SEL, 1 <<  HI6402_PLL_SEL_BIT, 1 <<  HI6402_PLL_SEL_BIT);
	snd_soc_write(codec, HI6402_PLL_FCW_17_10, 0x05);
	snd_soc_write(codec, HI6402_PLL_FCW_9_2, 0xdc);
	hi64xx_update_bits(codec, HI6402_PLL_FCW_1_0, 0x3<<HI6402_PLL_FCW_1_0_BIT,  0x0<<HI6402_PLL_FCW_1_0_BIT);
	snd_soc_write(codec, HI6402_PLL_PDIV_AD, 0x87);
	snd_soc_write(codec, HI6402_PLL_LPF_PI, 0x25);
	snd_soc_write(codec, HI6402_PLL_DCO_INIT, 0x80);
	snd_soc_write(codec, HI6402_PLL_PHE_SH, 0x01);
	hi64xx_update_bits(codec, HI6402_PLL_CLKTEST_EN, 1 << HI6402_PLL_CLKTEST_EN_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PHE_THR_SEL, 1 << HI6402_PLL_PHE_THR_SEL_BIT, 1 << HI6402_PLL_PHE_THR_SEL_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_CAL_START, 1 << HI6402_PLL_CAL_START_BIT, 1 << HI6402_PLL_CAL_START_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_PD_REG, 1 << HI6402_PLL_PD_BIT,  0);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 0xDD, 0x00);
	udelay(1);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REG, 1 << HI6402_PLL_RSTN_REG_BIT, 1 << HI6402_PLL_RSTN_REG_BIT);
	udelay(1);
	hi64xx_update_bits(codec, HI6402_PLL_RUN_START, 1 << HI6402_PLL_RUN_START_BIT, 1 << HI6402_PLL_RUN_START_BIT);
	udelay(100);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVA_EN, 1 << HI6402_PLL_PDIVA_EN_BIT, 1 << HI6402_PLL_PDIVA_EN_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_ISO_18_REG, 1 << HI6402_PLL_ISO_18_REG_BIT, 1 << HI6402_PLL_ISO_18_REG_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_BYPASS, 1 << HI6402_PLL_BYPASS_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_ISO_12_REG, 1 << HI6402_PLL_ISO_12_REG_BIT, 1 << HI6402_PLL_ISO_12_REG_BIT);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 <<  HI6402_PLL_DIG_EN, 1 <<  HI6402_PLL_DIG_EN);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVD_EN, 1 <<  HI6402_PLL_PDIVD_EN_BIT, 1 <<  HI6402_PLL_PDIVD_EN_BIT);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 <<  HI6402_DCO_DIG_EN, 1 <<  HI6402_DCO_DIG_EN);
	hi64xx_update_bits(codec, HI6402_AUD_CLK_EN, 0x03, 0x03);
	return 0;
}

int hi6402_low_pll_turn_off(struct snd_soc_codec *codec)
{
	hi64xx_update_bits(codec, HI6402_AUD_CLK_EN, 0x03, 0x00);

	/* shutdown cp clk before clk switch*/
	hi64xx_update_bits(codec, HI6402_POP_IRQ_CLK_PD_REG, 1 << 0 , 1 << 0);
	/* PLL BYPASS */
	hi64xx_update_bits(codec, HI6402_PLL_BYPASS, 1 << HI6402_PLL_BYPASS_BIT, 1 << HI6402_PLL_BYPASS_BIT);
	/* 32k -> pll clk */
	hi64xx_update_bits(codec, HI6402_PLL_CLK_SEL_REG, 1 << HI6402_PLL_CLK_SEL_REG_BIT, 1 << HI6402_PLL_CLK_SEL_REG_BIT);

	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 << HI6402_DCO_DIG_EN, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVA_EN, 1 << HI6402_PLL_PDIVA_EN_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVD_EN, 1 << HI6402_PLL_PDIVD_EN_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PD_REG, 1 << HI6402_PLL_PD_BIT, 1 << HI6402_PLL_PD_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REG, 1 << HI6402_PLL_RSTN_REG_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REFDIV, 1 << HI6402_PLL_RSTN_REFDIV_BIT, 0);
	return 0;
}

int hi6402_high_pll_turn_on(struct snd_soc_codec *codec)
{
	/* 19.2M -> pll clk */
	hi64xx_update_bits(codec, HI6402_PLL_CLK_SEL_REG, 1 << HI6402_PLL_CLK_SEL_REG_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_SEL, 1 << HI6402_PLL_SEL_BIT, 0);
	/* set fs div */
	snd_soc_write(codec, HI6402_PLL_FCW_17_10, 0x5C);
	snd_soc_write(codec, HI6402_PLL_FCW_9_2, 0x29);
	hi64xx_update_bits(codec, HI6402_PLL_FCW_1_0, 0x3<<HI6402_PLL_FCW_1_0_BIT, 0x0<<HI6402_PLL_FCW_1_0_BIT);
	snd_soc_write(codec, HI6402_PLL_PDIV_AD, 0xCB);
	snd_soc_write(codec, HI6402_PLL_LPF_PI, 0x46);
	hi64xx_update_bits(codec, HI6402_PLL_PHE_THR_SEL, 1 << HI6402_PLL_PHE_THR_SEL_BIT, 1 << HI6402_PLL_PHE_THR_SEL_BIT);

	hi64xx_update_bits(codec, HI6402_PLL_CAL_START, 1 << HI6402_PLL_CAL_START_BIT, 1 << HI6402_PLL_CAL_START_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_PD_REG, 1 << HI6402_PLL_PD_BIT, 0);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 0xDD, 0x00);
	udelay(1);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REG, 1 << HI6402_PLL_RSTN_REG_BIT, 1 << HI6402_PLL_RSTN_REG_BIT);
	udelay(1);
	hi64xx_update_bits(codec, HI6402_PLL_RUN_START, 1 << HI6402_PLL_RUN_START_BIT, 1 << HI6402_PLL_RUN_START_BIT);
	udelay(100);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVA_EN, 1 << HI6402_PLL_PDIVA_EN_BIT, 1 << HI6402_PLL_PDIVA_EN_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_ISO_18_REG, 1 << HI6402_PLL_ISO_18_REG_BIT, 1 << HI6402_PLL_ISO_18_REG_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_BYPASS, 1 << HI6402_PLL_BYPASS_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_ISO_12_REG,1 << HI6402_PLL_ISO_12_REG_BIT, 1 << HI6402_PLL_ISO_12_REG_BIT);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 << HI6402_PLL_DIG_EN, 1 << HI6402_PLL_DIG_EN);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVD_EN, 1 << HI6402_PLL_PDIVD_EN_BIT, 1 << HI6402_PLL_PDIVD_EN_BIT);
	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 << HI6402_DCO_DIG_EN, 1 << HI6402_DCO_DIG_EN);
	hi64xx_update_bits(codec, HI6402_AUD_CLK_EN, 0x03, 0x03);
	return 0;
}

int hi6402_high_pll_turn_off(struct snd_soc_codec *codec)
{
	hi64xx_update_bits(codec, HI6402_AUD_CLK_EN, 0x03, 0x00);

	/* shutdown cp clk before clk switch*/
	hi64xx_update_bits(codec, HI6402_POP_IRQ_CLK_PD_REG, 1 << 0 , 1 << 0);
	/* PLL BYPASS */
	hi64xx_update_bits(codec, HI6402_PLL_BYPASS, 1 << HI6402_PLL_BYPASS_BIT, 1 << HI6402_PLL_BYPASS_BIT);
	/* 32k -> pll clk */
	hi64xx_update_bits(codec, HI6402_PLL_CLK_SEL_REG, 1 << HI6402_PLL_CLK_SEL_REG_BIT, 1 << HI6402_PLL_CLK_SEL_REG_BIT);

	hi64xx_update_bits(codec, HI6402_ANA_REG69, 1 << HI6402_DCO_DIG_EN, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVA_EN, 1 << HI6402_PLL_PDIVA_EN_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PDIVD_EN, 1 << HI6402_PLL_PDIVD_EN_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_PD_REG, 1 << HI6402_PLL_PD_BIT, 1 << HI6402_PLL_PD_BIT);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REG, 1 << HI6402_PLL_RSTN_REG_BIT, 0);
	hi64xx_update_bits(codec, HI6402_PLL_RSTN_REFDIV, 1 << HI6402_PLL_RSTN_REFDIV_BIT, 0);
	return 0;
}

static bool hi6402_pll_is_locked(struct snd_soc_codec *codec)
{
	int i = 0;

	for (i = 0; i < HI6402_WAIT_PLL_LOCK_TIME; i++) {
		usleep_range(500,550);
		if (0 != (snd_soc_read(codec, HI6402_PLL_LOCK) & HI6402_PLL_LOCK_STATUS))
			break;
	}

	if (HI6402_WAIT_PLL_LOCK_TIME == i) {
		pr_err("pll can not lock in 5ms\n");
		return false;
	}

	for (i = 0; i < HI6402_ENSURE_PLL_LOCK_TIME; i++) {
		if (0 != (snd_soc_read(codec, HI6402_PLL_LOCK) & HI6402_PLL_LOCK_STATUS))
			udelay(5);
		else
			return false;
	}

	return true;
}

enum hi64xx_pll_type hi6402_pll_for_reg_access(struct snd_soc_codec *codec, unsigned int reg)
{
	if ((reg >= HI6402_CODEC_CORE_BEGIN && reg <= HI6402_CODEC_CORE_END) ||
		(reg >= HI6402_CODEC_CORE_CLK_BEGIN && reg <= HI6402_CODEC_CORE_CLK_END)) {
		return PLL_HIGH;
	} else {
		return PLL_NONE;
	}
}

 /* functions to enable/disable micbias */
int hi6402_enable_micbias(struct snd_soc_codec *codec)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	/* mask btn irqs */
	hi64xx_irq_mask_btn_irqs(priv->mbhc);

	/* eco off & normal auto saradc on */
	/* eco off */
	hi64xx_update_bits(codec, HI6402_MIC_DISCHG_CFG_REG, 1 << HI6402_HS_ECO_EN_BIT, 0);
	dev_info(codec->dev, "%s : eco disable \n", __FUNCTION__);
	/* mbhc cmp on */
	hi64xx_update_bits(codec, HI6402_HSMIC_CFG_REG, 1 << HI6402_COMP_PD_BIT, 0);
	/* hsmic on */
	hi64xx_update_bits(codec, HI6402_HSMIC_CFG_REG, 1 << HI6402_HSMIC_PD_BIT, 0);
	dev_info(codec->dev, "%s : hs micbias enable \n", __FUNCTION__);
	msleep(20);

	/* unmask btn irqs */
	hi64xx_irq_unmask_btn_irqs(priv->mbhc);
	return 0;
}

int hi6402_disable_micbias(struct snd_soc_codec *codec)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	/* mask btn irqs */
	hi64xx_irq_mask_btn_irqs(priv->mbhc);
	/* hsmic pd */
	hi64xx_update_bits(codec, HI6402_HSMIC_CFG_REG, 1 << HI6402_HSMIC_PD_BIT, 1 << HI6402_HSMIC_PD_BIT);
	/* hsmic dischg */
	hi64xx_update_bits(codec, HI6402_MIC_DISCHG_CFG_REG, 1 << HI6402_HSMIC_DISCHG_BIT, 1 << HI6402_HSMIC_DISCHG_BIT);
	msleep(15);
	/* hsmic chg */
	hi64xx_update_bits(codec, HI6402_MIC_DISCHG_CFG_REG, 1 << HI6402_HSMIC_DISCHG_BIT, 0);
	dev_info(codec->dev, "%s : hs micbias disable \n", __FUNCTION__);
	/* eco on & eco auto saradc on */
	/* mbhc cmp off */
	hi64xx_update_bits(codec, HI6402_HSMIC_CFG_REG, 1 << HI6402_COMP_PD_BIT, 1 << HI6402_COMP_PD_BIT);
	/* eco on */
	hi64xx_update_bits(codec, HI6402_MIC_DISCHG_CFG_REG, 1 << HI6402_HS_ECO_EN_BIT, 1 << HI6402_HS_ECO_EN_BIT);
	dev_info(codec->dev, "%s : eco enable \n", __FUNCTION__);
	msleep(20);

	/* unmask btn irqs */
	hi64xx_irq_unmask_btn_irqs(priv->mbhc);
	return 0;
}

/* functions to enable/disable ibias */
int hi6402_enable_ibias(struct snd_soc_codec *codec)
{
	/* vref_ibias_on */
	hi64xx_update_bits(codec, HI6402_VREF_SEL, 0x03<<HI6402_VREF_SEL_BIT, HI6402_VREF_SEL_1K<<HI6402_VREF_SEL_BIT);
	hi64xx_update_bits(codec, HI6402_VREF_FAST, 1 << HI6402_VREF_FAST_BIT, 1 << HI6402_VREF_FAST_BIT);
	mdelay(30);
	hi64xx_update_bits(codec, HI6402_VREF_FAST, 1 << HI6402_VREF_FAST_BIT, 0);
	hi64xx_update_bits(codec, HI6402_VREF_SEL, 0x03<<HI6402_VREF_SEL_BIT,  HI6402_VREF_SEL_100K << HI6402_VREF_SEL_BIT);
	hi64xx_update_bits(codec, HI6402_IBIAS_PD, 1 << HI6402_IBIAS_PD_BIT, 0);
	return 0;
}

int hi6402_disable_ibias(struct snd_soc_codec *codec)
{
	hi64xx_update_bits(codec, HI6402_IBIAS_PD, 1 << HI6402_IBIAS_PD_BIT, 1 << HI6402_IBIAS_PD_BIT);
	hi64xx_update_bits(codec, HI6402_VREF_SEL, 0x03<<HI6402_VREF_SEL_BIT, HI6402_VREF_SEL_PD<<HI6402_VREF_SEL_BIT);
	return 0;
}


static void hi6402_mad_set_param(struct snd_soc_codec *codec)
{
	//ana_stable_l time 6ms
	snd_soc_write(codec, HI6402_MAD_ANA_TIME_L, 0xC1);
	//pll stable time
	snd_soc_write(codec, HI6402_MAD_PLL_TIME_L, 0x01);
	//adc stable time 5ms
	snd_soc_write(codec, HI6402_MAD_ADC_TIME_L, 0xB1);
	//mad_omit_samp 2ms
	snd_soc_write(codec, HI6402_MAD_OMIT_SAMP, 0x20);
	//rms_number 1
	snd_soc_write(codec, HI6402_MAD_RMS_NUM, 0x01);
	//mad_auto_act_number
	snd_soc_write(codec, HI6402_MAD_AUTO_ACT_NUMBER, 0x0);
	//mad_rms_mode & ana_stable_h
	snd_soc_write(codec, HI6402_MAD_RMS_MODE, 0xC0);
	//mad_sleep_time0 5ms
	snd_soc_write(codec, HI6402_MAD_SLEEP_TIME0, 0xA0);
	//mad_sleep_time1
	snd_soc_write(codec, HI6402_MAD_SLEEP_TIME1, 0x0);
	//mad_rms_int_en
	hi64xx_update_bits(codec, HI6402_MAD_RMS_INT_EN,
			1 << HI6402_MAD_RMS_INT_EN_BIT, 1 << HI6402_MAD_RMS_INT_EN_BIT);
	//mad_rms_thre 30 0x23280
	snd_soc_write(codec, HI6402_MAD_RMS_THRE0, 0x80);
	//mad_rms_thre
	snd_soc_write(codec, HI6402_MAD_RMS_THRE1, 0x32);
	//mad_rms_thre
	snd_soc_write(codec, HI6402_MAD_RMS_THRE2, 0x02);
	//mad_rms_thre
	snd_soc_write(codec, HI6402_MAD_RMS_THRE3, 0x00);
	//mad_rms_time 10ms
	snd_soc_write(codec, HI6402_MAD_RMS_TIME0, 0xA0);
	//mad_rms_time
	snd_soc_write(codec, HI6402_MAD_RMS_TIME1, 0x00);
	//mad_rms_diff_thre
	snd_soc_write(codec, HI6402_MAD_RMS_DIFF_THRE0, 0x49);
	//mad_rms_diff_thre
	snd_soc_write(codec, HI6402_MAD_RMS_DIFF_THRE1, 0x28);
	//mad_filter_id
	hi64xx_update_bits(codec, HI6402_MAD_FILTER_ID,
			0x7 << HI6402_MAD_FILTER_ID_BIT, 0x1 << HI6402_MAD_FILTER_ID_BIT);
	//mad_filter_id1
	hi64xx_update_bits(codec, HI6402_MAD_FILTER_ID1,
			0x7<<HI6402_MAD_FILTER_ID1_BIT, 0x3<<HI6402_MAD_FILTER_ID1_BIT);

	return;
}


static void hi6402_dump_reg(char *buf, unsigned int dump_size)
{
	int len = 0;
	unsigned int i = 0;

	if (NULL == buf) {
		pr_err("hi6402_dump_reg buf NULL!\n");
		return;
	}

	len = strlen(buf);
	len += snprintf(buf + len, dump_size - len,  "%#04x-%#04x\n", HI6402_IRQ_REG_IOMUX,
		snd_soc_read(g_hi6402_codec, HI6402_IRQ_REG_IOMUX -CODEC_BASE_ADDR));
	if (len >= dump_size)
		return;

	for (i = BASE_ADDR_PAGE_CFG + 0x00; i <= BASE_ADDR_PAGE_CFG + 0xff; i++)
	{
		if ((i >= BASE_ADDR_PAGE_CFG + 0x41) && (i <= BASE_ADDR_PAGE_CFG + 0x4c)) {
			i = BASE_ADDR_PAGE_CFG + 0x4c;
			continue;
		}
		len += snprintf(buf + len, dump_size - len, "%#04x-%#04x\n", CODEC_BASE_ADDR | i, snd_soc_read(g_hi6402_codec, i));
		if (len >= dump_size)
			return;
	}

	for (i = BASE_ADDR_PAGE_CFG + 0x41; i <= BASE_ADDR_PAGE_CFG + 0x4c; i++)
	{
		len += snprintf(buf + len, dump_size - len, "%#04x-%#04x\n", CODEC_BASE_ADDR | i, snd_soc_read(g_hi6402_codec, i));
		if (len >= dump_size)
			return;
	}

	for (i = BASE_ADDR_PAGE_DIG + 0x00; i <= BASE_ADDR_PAGE_DIG + 0x1FF; i++)
	{
		len += snprintf(buf + len, dump_size - len, "%#04x-%#04x\n", CODEC_BASE_ADDR | i, snd_soc_read(g_hi6402_codec, i));
		if (len >= dump_size)
			return;
	}
	len = strlen(buf);
	snprintf(buf + len, dump_size - len, "\n");
}


static int hi6402_irq_init(struct hi64xx_irq *irq_data)
{
	struct hi64xx_irq_map irqmap;
	int ret = 0;

	if (HI64XX_MAX_IRQ_REGS_NUM >= 4) {
		irqmap.irq_regs[0] = HI64xx_REG_IRQ_0;
		irqmap.irq_regs[1] = HI64xx_REG_IRQ_1;
		irqmap.irq_regs[2] = HI64xx_REG_IRQ_2;
		irqmap.irq_regs[3] = HI64xx_REG_IRQ_3;
		irqmap.irq_mask_regs[0] = HI64xx_REG_IRQM_0;
		irqmap.irq_mask_regs[1] = HI64xx_REG_IRQM_1;
		irqmap.irq_mask_regs[2] = HI64xx_REG_IRQM_2;
		irqmap.irq_mask_regs[3] = HI64xx_REG_IRQM_3;
		irqmap.irq_num = HI6402_IRQ_NUM;

		ret = hi64xx_irq_init_irq(irq_data, &irqmap);
	} else {
		pr_err("%s: array size extend! \n", __FUNCTION__);
		ret = -ENOENT;
	}

	return ret;
}

static int hi6402_resmgr_init(struct hi6402_platform_data *pd)
{
	int ret = 0;
	struct resmgr_config cfg;

	cfg.pll_num = 2;
	cfg.pfn_pll_ctrls[PLL_LOW].turn_on = hi6402_low_pll_turn_on;
	cfg.pfn_pll_ctrls[PLL_LOW].turn_off = hi6402_low_pll_turn_off;
	cfg.pfn_pll_ctrls[PLL_LOW].is_locked = hi6402_pll_is_locked;
	cfg.pfn_pll_ctrls[PLL_HIGH].turn_on = hi6402_high_pll_turn_on;
	cfg.pfn_pll_ctrls[PLL_HIGH].turn_off = hi6402_high_pll_turn_off;
	cfg.pfn_pll_ctrls[PLL_HIGH].is_locked = hi6402_pll_is_locked;
	cfg.pll_for_reg_access = hi6402_pll_for_reg_access;
	cfg.enable_ibias = hi6402_enable_ibias;
	cfg.disable_ibias = hi6402_disable_ibias;
	cfg.enable_micbias = hi6402_enable_micbias;
	cfg.disable_micbias = hi6402_disable_micbias;
	ret = hi64xx_resmgr_init(pd->codec, pd->cdc_ctrl, pd->irqmgr, &cfg, &pd->resmgr);

	return ret;
}

static int hi6402_utils_init(struct hi6402_platform_data *pd)
{
	int ret = 0;
	struct utils_config cfg;

	cfg.hi64xx_dump_reg = hi6402_dump_reg;
	ret = hi64xx_utils_init(pd->codec, pd->cdc_ctrl, &cfg, pd->resmgr);

	return ret;
}

static int hi6402_codec_probe(struct snd_soc_codec *codec)
{
	int ret = 0;
	struct hi6402_platform_data *hi6402_pd = NULL;

	hi6402_pd = snd_soc_codec_get_drvdata(codec);
	if (!hi6402_pd) {
		dev_err(codec->dev, "%s:get hi6402 platform data fail \n", __FUNCTION__);
		return -ENOENT;
	} else {
		hi6402_pd->codec = codec;
		g_hi6402_codec = codec;
		hi6402_pd->ref_voice_clk = 0;
		hi6402_pd->ref_audio_tx = 0;
		hi6402_pd->ref_audio_rx = 0;
		hi6402_pd->capture_state = TRACK_FREE;
		hi6402_pd->voiceup_8k_state = TRACK_FREE;
		hi6402_pd->voiceup_16k_state = TRACK_FREE;
		hi6402_pd->s1s3_up_state = S1S3_UP_NULL;
		hi6402_pd->voicedown_state = TRACK_FREE;
		hi6402_pd->mm_reg = 0;
		mutex_init(&hi6402_pd->rw_mutex);
		mutex_init(&hi6402_pd->ref_mutex);
	}

	ret = hi6402_resmgr_init(hi6402_pd);
	if (0 != ret) {
		dev_err(codec->dev, "%s: hi6402_resmgr_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto resmgr_init_err_exit;
	}

	hi6402_init_chip(codec);

	ret = hi64xx_mbhc_init(codec, hi6402_pd->node, &hi6402_mbhc_reg,
		hi6402_pd->resmgr, hi6402_pd->irqmgr, &hi6402_pd->mbhc);
	if (0 != ret) {
		dev_err(codec->dev, "%s: hi6402_mbhc_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto mbhc_init_err_exit;
	}

	hi6402_mad_set_param(codec);

	ret = hi6402_hifi_config_init(codec, hi6402_pd->resmgr, hi6402_pd->irqmgr);
	if (0 != ret) {
		dev_err(codec->dev, "%s: hi6402_hifi_config_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto misc_init_err_exit;
	}

	ret = hi64xx_vad_init(codec, hi6402_pd->irqmgr);
	if (0 != ret) {
		dev_err(codec->dev, "%s: hi6402_vad_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto vad_init_err_exit;
	}

	ret = hi6402_utils_init(hi6402_pd);
	if (0 != ret) {
		dev_err(codec->dev, "%s: hi6402_utils_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto utils_init_err_exit;
	}

	dev_info(codec->dev, "%s: OK.\n", __FUNCTION__);
	return ret;

utils_init_err_exit:
	hi64xx_vad_deinit();
vad_init_err_exit:
	hi6402_hifi_config_deinit();
misc_init_err_exit:
	hi64xx_mbhc_deinit(hi6402_pd->mbhc);
mbhc_init_err_exit:
	hi64xx_resmgr_deinit(hi6402_pd->resmgr);
resmgr_init_err_exit:
	mutex_destroy(&hi6402_pd->rw_mutex);
	mutex_destroy(&hi6402_pd->ref_mutex);
	dev_err(codec->dev, "%s: fail\n",__FUNCTION__);
	return ret;
}

static int hi6402_codec_remove(struct snd_soc_codec *codec)
{
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);

	hi64xx_vad_deinit();
	hi6402_hifi_config_deinit();
	hi64xx_mbhc_deinit(priv->mbhc);
	hi64xx_resmgr_deinit(priv->resmgr);
	mutex_destroy(&priv->rw_mutex);
	mutex_destroy(&priv->ref_mutex);

	return 0;
}

void hi6402_digital_clk_disable(void)
{
	pr_info("%s\n",__func__);
	/* disable audio clk */
	hi64xx_update_bits(g_hi6402_codec, HI6402_CODEC_DP_CLKEN, 1 << HI6402_CODEC_DP_CLKEN_BIT, 0);
}

void hi6402_digital_clk_enable(void)
{
	pr_info("%s\n",__func__);
	/* enable audio clk */
	hi64xx_update_bits(g_hi6402_codec, HI6402_CODEC_DP_CLKEN, 1 << HI6402_CODEC_DP_CLKEN_BIT, 1 << HI6402_CODEC_DP_CLKEN_BIT);
}

void hi6402_3mic_fade_out(void)
{
	pr_info("%s++\n",__func__);
	/* -60db */
	snd_soc_write(g_hi6402_codec, HI6402_DACL_PGA_GAIN_CFG_REG, 0xC4);
	snd_soc_write(g_hi6402_codec, HI6402_DACR_PGA_GAIN_CFG_REG, 0xC4);
	mdelay(70);

	/* enable headphone mute */
	hi64xx_update_bits(g_hi6402_codec, HI6402_HPL_PGA_CFG_REG, 1 << HI6402_HPL_PGA_MUTE_BIT, 1 << HI6402_HPL_PGA_MUTE_BIT);
	hi64xx_update_bits(g_hi6402_codec, HI6402_HPR_PGA_CFG_REG, 1 << HI6402_HPR_PGA_MUTE_BIT, 1 << HI6402_HPR_PGA_MUTE_BIT);

	pr_info("%s--\n",__func__);
}
EXPORT_SYMBOL(hi6402_3mic_fade_out);

void hi6402_3mic_audio_clk(int mode)
{
	pr_info("%s++:mode:%d\n",__func__,mode);

	if(mode & (1<<HI6402_DP_CLK_BIT)) {
		/* enable dp clk */
		hi6402_digital_clk_enable();

		/* -9db */
		snd_soc_write(g_hi6402_codec, HI6402_DACL_PGA_GAIN_CFG_REG, 0xF7);
		snd_soc_write(g_hi6402_codec, HI6402_DACR_PGA_GAIN_CFG_REG, 0xF7);
		/* disable headphone mute */
		hi64xx_update_bits(g_hi6402_codec, HI6402_HPL_PGA_CFG_REG, 1 << HI6402_HPL_PGA_MUTE_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_HPR_PGA_CFG_REG, 1 << HI6402_HPR_PGA_MUTE_BIT, 0);
	} else {
		/* disable dac clk */
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG,
								1 << HI6402_ADC0L_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG,
								1 << HI6402_ADC0R_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG,
								1 << HI6402_ADC1L_EN_BIT, 0);

		/* disable i2s src clk */
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG,
								1 << HI6402_S1_SRC_OL_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG,
								1 << HI6402_S1_SRC_OR_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG,
								1 << HI6402_S3_SRC_OL_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG,
								1 << HI6402_S3_SRC_OR_EN_BIT, 0);

		/* disable i2s pga clk */
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG,
								1 << HI6402_S1_PGA_OL_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG,
								1 << HI6402_S1_PGA_OR_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG,
								1 << HI6402_S3_PGA_OL_EN_BIT, 0);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG,
								1 << HI6402_S3_PGA_OR_EN_BIT, 0);

		/* disable dp clk */
		hi6402_digital_clk_disable();

		/* enable dac clk */
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0L_EN_BIT, 1 << HI6402_ADC0L_EN_BIT);
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC0R_EN_BIT, 1 << HI6402_ADC0R_EN_BIT);
		hi64xx_update_bits(g_hi6402_codec, HI6402_DAC_ADC_CLK_REG, 1 << HI6402_ADC1L_EN_BIT, 1 << HI6402_ADC1L_EN_BIT);
		if(!(mode & (1<<HI6402_3MIC_SENCE_BIT))) {
			/* enable i2s src clk */
			hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_SRC_OL_EN_BIT, 1 << HI6402_S1_SRC_OL_EN_BIT);
			hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_SRC_OR_EN_BIT, 1 << HI6402_S1_SRC_OR_EN_BIT);
			hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_SRC_OL_EN_BIT, 1 << HI6402_S3_SRC_OL_EN_BIT);
			hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_SRC_OR_EN_BIT, 1 << HI6402_S3_SRC_OR_EN_BIT);
		}
		/* enable i2s pga clk */
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OL_EN_BIT, 1 << HI6402_S1_PGA_OL_EN_BIT);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S1_MODULE_CLK_REG, 1 << HI6402_S1_PGA_OR_EN_BIT, 1 << HI6402_S1_PGA_OR_EN_BIT);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OL_EN_BIT, 1 << HI6402_S3_PGA_OL_EN_BIT);
		hi64xx_update_bits(g_hi6402_codec, HI6402_S3_MODULE_CLK_REG, 1 << HI6402_S3_PGA_OR_EN_BIT, 1 << HI6402_S3_PGA_OR_EN_BIT);
	}

	pr_info("%s--:mode:%d\n",__func__,mode);
}
EXPORT_SYMBOL(hi6402_3mic_audio_clk);

static int hi6402_audio_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	int rate = 0;
	int ret = 0;

	BUG_ON(NULL == codec);
	BUG_ON(NULL == priv);

	rate = params_rate(params);

	switch (rate) {
	case 8000:
	case 11250:
	case 16000:
	case 22500:
	case 32000:
	case 44100:
	case 48000:
		break;
	case 88200:
	case 96000:
		break;
	default:
		pr_err("unknown rate : %d!\n", rate);
		ret = -1;
		break;
	}

	return ret;
}

static int hi6402_audio_hw_free(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	BUG_ON(NULL == priv);

	return ret;
}

struct snd_soc_dai_ops hi6402_audio_dai_ops = {
	.hw_params = hi6402_audio_hw_params,
	.hw_free = hi6402_audio_hw_free,
};

static int hi6402_voice_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	slimbus_track_param_t  *slimbus_params = NULL;
	slimbus_track_type_t    track = SLIMBUS_TRACK_VOICE_DOWN;
	int rate = 0;
	int ret = 0;

	BUG_ON(NULL == codec);

	BUG_ON(NULL == priv);

	slimbus_params = &(priv->voice_params);
	rate = params_rate(params);

	memset(slimbus_params, 0, sizeof(slimbus_track_param_t));
	slimbus_params->rate = rate;
	slimbus_params->channels = params_channels(params);

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		priv->voicedown_state = TRACK_STARTUP;
		track = SLIMBUS_TRACK_VOICE_DOWN;
		slimbus_param_set(SLIMBUS_DEVICE_HI6402, track, slimbus_params);
	}

	switch (rate) {
	case 8000:
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_H, 0x77, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_SRC_IN_MODE_CGF, 0xEE, 0xAA);
		hi64xx_update_bits(codec, HI6402_S3_SRC_OUT_MODE_CGF, 0x36, 0x24);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 1 << HI6402_S3_IL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 1 << HI6402_S3_OL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 1 << HI6402_S3_OR_SRC_BIT);
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OL_SRC_BIT, 0);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OR_SRC_BIT, 0);
			hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 0x07, 0x00);
			hi64xx_update_bits(codec, HI6402_S1_FS_CFG_H, 0x70, 0x00);
			hi64xx_update_bits(codec, HI6402_S1_SRC_OUT_MODE_CGF, 0x36, 0x24);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OL_SRC_BIT, 1 << HI6402_S1_OL_SRC_BIT);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OR_SRC_BIT, 1 << HI6402_S1_OR_SRC_BIT);
		} else {

		}
		break;
	case 16000:
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x01);
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_H, 0x77, 0x11);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 0);
		hi64xx_update_bits(codec, HI6402_S3_SRC_IN_MODE_CGF, 0xEE, 0x22);
		hi64xx_update_bits(codec, HI6402_S3_SRC_OUT_MODE_CGF, 0x36, 0x00);
		hi64xx_update_bits(codec, HI6402_S3_IN_SRC_SEL, 1 << HI6402_S3_IL_SRC_BIT, 1 << HI6402_S3_IL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OL_SRC_BIT, 1 << HI6402_S3_OL_SRC_BIT);
		hi64xx_update_bits(codec, HI6402_S3_OUT_SRC_SEL, 1 << HI6402_S3_OR_SRC_BIT, 1 << HI6402_S3_OR_SRC_BIT);
		if (3 == priv->board_cfg.mic_num || 4 == priv->board_cfg.mic_num) {
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OL_SRC_BIT, 0);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OR_SRC_BIT, 0);
			hi64xx_update_bits(codec, HI6402_S1_FS_CFG_L, 0x07, 0x01);
			hi64xx_update_bits(codec, HI6402_S1_FS_CFG_H, 0x70, 0x10);
			hi64xx_update_bits(codec, HI6402_S1_SRC_OUT_MODE_CGF, 0x36, 0x00);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OL_SRC_BIT, 1 << HI6402_S1_OL_SRC_BIT);
			hi64xx_update_bits(codec, HI6402_S1_OUT_SRC_SEL, 1 << HI6402_S1_OR_SRC_BIT, 1 << HI6402_S1_OR_SRC_BIT);
		} else {

		}
		break;
	case 32000:
		hi64xx_update_bits(codec, HI6402_S3_FS_CFG_L, 0x07, 0x02);
		break;
	default:
		dev_err(codec->dev, "unknown rate : %d!\n", rate);
		ret = -1;
		break;
	}

	return ret;
}

static int hi6402_voice_hw_free(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct hi6402_platform_data *priv = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	BUG_ON(NULL == priv);

	dev_info(codec->dev, "free voice\n");
	return ret;
}

struct snd_soc_dai_ops hi6402_voice_dai_ops = {
	.hw_params = hi6402_voice_hw_params,
	.hw_free = hi6402_voice_hw_free,
};

struct snd_soc_dai_driver hi6402_dai[] = {
	{
		.name = "hi6402-audio-dai",
		.playback = {
			.stream_name	= "Playback",
			.channels_min	= 2,
			.channels_max = 2,
			.rates = HI6402_RATES,
			.formats = HI6402_FORMATS},
		.capture = {
			.stream_name	= "Capture",
			.channels_min	= 1,
			.channels_max = 5,
			.rates = HI6402_RATES,
			.formats = HI6402_FORMATS},
		.ops = &hi6402_audio_dai_ops,
	},
	{
		.name = "hi6402-voice-dai",
		.playback = {
			.stream_name	= "Down",
			.channels_min	= 1,
			.channels_max = 2,
			.rates = HI6402_RATES,
			.formats	= HI6402_FORMATS},
		.capture = {
			.stream_name = "Up",
			.channels_min = 1,
			.channels_max = 5,
			.rates = HI6402_RATES,
			.formats = HI6402_FORMATS},
		.ops = &hi6402_voice_dai_ops,
	},
	{
		.name = "hi6402-fm-dai",
		.playback = {
			.stream_name	= "FM",
			.channels_min	= 1,
			.channels_max = 2,
			.rates = HI6402_RATES,
			.formats	= HI6402_FORMATS},
	},
};

static struct snd_soc_codec_driver hi6402_codec_driver = {
	.probe = hi6402_codec_probe,
	.remove = hi6402_codec_remove,
	.read = hi6402_reg_read,
	.write = hi6402_reg_write,

	.controls = hi6402_snd_controls,
	.num_controls = ARRAY_SIZE(hi6402_snd_controls),
	.dapm_widgets = hi6402_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(hi6402_dapm_widgets),
	.dapm_routes = route_map,
	.num_dapm_routes = ARRAY_SIZE(route_map),
};

static const struct of_device_id hi6402_platform_match[] = {
	{.compatible = "hisilicon,hi6402-codec",},
	{},
};
MODULE_DEVICE_TABLE(of, hi6402_platform_match);

static void hi6402_get_board_cfg(struct device_node *node, struct hi6402_board_cfg *board_cfg)
{
	int val = 0;

	/* get board defination */
	if (!of_property_read_u32(node, "micbias1_mic2", &val)) {
		board_cfg->mic2_source = val;
	} else {
		board_cfg->mic2_source = 0;
	}

	if (!of_property_read_u32(node, "hisilicon,mic_num", &val)) {
		board_cfg->mic_num = val;
	} else {
		board_cfg->mic_num = 2;
	}

	if (!of_property_read_u32(node, "hisilicon,hac_gpio", &val)) {
		board_cfg->hac_gpio = val;
	} else {
		board_cfg->hac_gpio = 0;
	}

	/* read the mask to distinguish different product */
	if (!of_property_read_u32(node, "use_stereo_smartpa", &val)){
		if(val){
			board_cfg->use_stereo_smartpa = true;
		} else {
			board_cfg->use_stereo_smartpa = false;
		}
	} else {
		board_cfg->use_stereo_smartpa = false;
	}
}

static void hi6402_init_codec_device(struct hi_cdc_ctrl* cdc)
{
	if (cdc->bus_sel == BUSTYPE_SELECT_SLIMBUS) {
		hi_cdcctrl_reg_write(cdc, HI6402_IRQ_REG_IOMUX, 0x1024);
		hi_cdcctrl_reg_update_bits(cdc, HI6402_IRQ_REG_GPIO5, 1 << 6, 1 << 6);
		hi_cdcctrl_reg_update_bits(cdc, HI6402_IRQ_REG_UART_TX, 1 << 6, 1 << 6);
		hi_cdcctrl_reg_update_bits(cdc, HI6402_IRQ_REG_UART_RX, 0x60, 0x20);
		/* slimbus MCLK enable */
		hi_cdcctrl_reg_write(cdc, HI6402_CFG_CLK_CTRL, 0x02);
	} else if (cdc->bus_sel == BUSTYPE_SELECT_SSI) {
		hi_cdcctrl_reg_write(cdc, HI6402_IRQ_REG_IOMUX, 0x10a6);
		/* IOSHARE */
		hi_cdcctrl_reg_write(cdc, HI6402_IOS_IOM_CTRL7, 0x14C);
		hi_cdcctrl_reg_write(cdc, HI6402_IOS_IOM_CTRL8, 0x14D);
		/* slimbus_data & slimbus_clk enable */
		hi_cdcctrl_reg_update_bits(cdc, HI6402_IOS_AF_CTRL0, 1 << 1, 1 << 1);
		/* slimbus MCLK & SSI MCLK */
		hi_cdcctrl_reg_write(cdc, HI6402_CFG_CLK_CTRL, 0x03);
	} else {
		pr_err("%s : no such bus type \n", __FUNCTION__);
	}

	hi_cdcctrl_reg_write(cdc, HI6402_SLIM_CTRL0, 0x83);

	/* ISO release */
	hi_cdcctrl_reg_update_bits(cdc, HI6402_ISO_A18_D12_REG, 1 << 1, 1 << 1);
	hi_cdcctrl_reg_update_bits(cdc, HI6402_ISO_A33_D12_REG, 1 << 0, 1 << 0);

	/* power optimize */
	hi_cdcctrl_reg_write(cdc, HI6402_DSP_CTRL6_DMAC, HI6402_DSP_CTRL6_DMAC_INIT);
	hi_cdcctrl_reg_write(cdc, HI6402_DSP_AXI_CLKEN1, HI6402_DSP_AXI_CLKEN1_INIT);
	hi_cdcctrl_reg_write(cdc, HI6402_APB_CLK_CFG_REG, HI6402_DSP_APB_CLK_INIT);
	hi_cdcctrl_reg_write(cdc, HI6402_IOS_IOM_CTRL33, 0x104);
	hi_cdcctrl_reg_write(cdc, HI6402_IRQ_REG_IRQ_CTRL, 0x84);
}

static int hi6402_platform_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi6402_platform_data *priv = NULL;
	const struct of_device_id *match = NULL;
	int ret = 0;

	priv = devm_kzalloc(dev, sizeof(struct hi6402_platform_data), GFP_KERNEL);
	if (NULL == priv) {
		dev_err(dev, "%s : kzalloc failed\n", __FUNCTION__);
		return -ENOMEM;
	}
	priv->node = dev->of_node;
	match = of_match_device(hi6402_platform_match, dev);
	if (!match) {
		dev_err(dev, "%s : get device info err\n", __FUNCTION__);
		ret = -ENOENT;
		goto free_platform_data;
	} else {
		hi6402_get_board_cfg(priv->node, &(priv->board_cfg));
		hac_en_gpio = priv->board_cfg.hac_gpio;
		dev_info(dev, "%s : mic_num %d , use_stereo_smartpa %d, hac_gpio %d\n",
			__FUNCTION__, priv->board_cfg.mic_num,
			priv->board_cfg.use_stereo_smartpa,
			priv->board_cfg.hac_gpio);
	}

	priv->irqmgr = (struct hi64xx_irq *)dev_get_drvdata(pdev->dev.parent);
	priv->cdc_ctrl = (struct hi_cdc_ctrl*)dev_get_drvdata(pdev->dev.parent->parent);

	ret = hi_cdcctrl_reg_read(priv->cdc_ctrl, HI64xx_VERSION_REG);
	if (ret != HI6402_VERSION_VALUE) {
		ret = -ENODEV;
		dev_err(dev, "[%s:%d]: read hi6402 version fail, ret=0x%x\n", __FUNCTION__, __LINE__, ret);
		goto free_platform_data;
	}

	platform_set_drvdata(pdev, priv);

	dev_set_name(dev, "hi6402-codec");

	ret = hi6402_irq_init(priv->irqmgr);
	if (0 != ret) {
		dev_err(dev, "%s: hi64xx_irq_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto free_platform_data;
	}

	ret = hi64xx_compat_init(priv->cdc_ctrl, priv->irqmgr);
	if (0 != ret) {
		dev_err(dev, "%s: hi64xx_compat_init fail. err code is %x .\n", __FUNCTION__, ret);
		goto compat_init_err_exit;
	}

	hi6402_init_codec_device(priv->cdc_ctrl);

	ret = snd_soc_register_codec(dev, &hi6402_codec_driver,
			hi6402_dai, ARRAY_SIZE(hi6402_dai));
	if (0 != ret) {
		dev_err(dev, "%s : snd_soc_register_codec create failed! err code 0x%x . \n", __FUNCTION__, ret);
		goto codec_register_err_exit;
	}

	if (!hac_en_gpio) {
		dev_err(dev, "%s : hac is not support.\n", __FUNCTION__);
		return ret;
	}

	if (gpio_request(hac_en_gpio, "hac_en_gpio")) {
		dev_err(dev, "%s : hac_en_gpio request failed!\n", __FUNCTION__);
		return ret;
	}

	if (gpio_direction_output(hac_en_gpio, 0)) {
		dev_err(dev, "%s: hac_en_gpio set output failed!\n", __FUNCTION__);
	}

	return ret;

codec_register_err_exit:
	hi64xx_compat_deinit();
compat_init_err_exit:
free_platform_data:
	if (priv) {
		devm_kfree(dev, priv);
	}
	dev_err(dev, "%s: init failed\n", __FUNCTION__);

	return ret;
}

static int hi6402_platform_remove(struct platform_device *pdev)
{
	struct hi6402_platform_data *priv =
		(struct hi6402_platform_data *)platform_get_drvdata(pdev);

	if (hac_en_gpio) {
		gpio_free(hac_en_gpio);
	}

	hi64xx_irq_deinit_irq(priv->irqmgr);
	hi64xx_compat_deinit();
	hi64xx_utils_deinit();
	return 0;
}

static void hi6402_platform_shutdown(struct platform_device *pdev)
{
}

static int hi6402_platform_resume(struct platform_device *pdev)
{
	return 0;
}

static int hi6402_platform_suspend(struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static struct platform_driver hi6402_platform_driver = {
	.probe = hi6402_platform_probe,
	.remove = hi6402_platform_remove,
	.shutdown = hi6402_platform_shutdown,
	.driver = {
		.owner = THIS_MODULE,
		.name = "hi6402-codec",
		.of_match_table = of_match_ptr(hi6402_platform_match),
	},
	.resume = hi6402_platform_resume,
	.suspend = hi6402_platform_suspend,
};

static int __init hi6402_platform_init(void)
{
	return platform_driver_register(&hi6402_platform_driver);
}

static void __exit hi6402_platform_exit(void)
{
	platform_driver_unregister(&hi6402_platform_driver);
}
fs_initcall_sync(hi6402_platform_init);
module_exit(hi6402_platform_exit);

MODULE_DESCRIPTION("hi6402");
MODULE_AUTHOR("guzhengming <guzhengming@hisilicon.com>");
MODULE_LICENSE("GPL");
