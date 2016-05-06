/*
 * hi6401.c -- ALSA SoC HI6401 codec driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
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
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>

#include <asm/io.h>

#include <linux/switch.h>
#include <linux/wakelock.h>

#include <linux/mfd/hi6401_irq.h>

#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#include <sound/jack.h>

#include "hi6401.h"

#ifdef CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif
#include <linux/huawei/hisi_adc.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <huawei_platform/log/log_exception.h>

#define GET_VOLTAGE(value)	(value * 2700 / 0xFF)	/* saradc range 0 ~ 2700mV */

#define STEP_DELAY	mdelay(5)

enum hi6401_jack_states {
	HI6401_JACK_NONE	= 0,	/* unpluged */
	HI6401_JACK_HEADSET	= 1,	/* pluged 4-pole headset */
	HI6401_JACK_HEADPHONE	= 2,	/* pluged 3-pole headphone */
	HI6401_JACK_INVERT	= 3,	/* pluged invert 4-pole headset */
};

enum vref_mode {
	VREF_PD		= 0,
	VREF_NORMAL	= 1,
	VREF_LOWPOWER	= 2,
	VREF_QUICK_PU	= 3,
	VREF_BANDGAP	= 4,
};

enum interface_mode {
	I2S_64BIT	= 0,
	I2S_32BIT	= 1,
	PCM_32BIT	= 2,
	PCM_16BIT	= 3,
};

enum btn_irq_mode {
	BTN_IRQ_OFF	= 0,
	BTN_IRQ_ECO	= 1,
	BTN_IRQ_NORMAL	= 2,
};

enum anc_hs_mode {
	ANC_HS_CHARGE_OFF	= 0,
	ANC_HS_CHARGE_ON	= 1,
	ANC_HS_CHARGE_SWITCHING	= 2,
	ANC_HS_RECOGNITION	= 3,
};

enum switch_chip_status {
	SWITCH_CHIP_HSBIAS	                   = 0,
	SWITCH_CHIP_5VBOOST	                   = 1,
};

/*note: start from 2501 to 3000*/
enum ANC_HS_ERRNO {
	ANC_HS_CALIBRATION_ERR                 = 2998,
	ANC_HS_NOT_IN_CHARGING                 = 2999,
	ANC_HS_NOT_SUPPORT                     = 3000,
};

#define  ANC_HS_LIMIT_MIN                  20
#define  ANC_HS_LIMIT_MAX                  200
#define  ANC_CHIP_WARM_STARTUP_TIME        160
#define  ANC_CHIP_COLD_STARTUP_TIME        380
#define  NO_CHARGE_DETECT_PERIOD_TIME      (1 * 60 * 60 * 1000)  // 1 hours
#define  ADC_CALIBRATION_TIMES             10
#define  ADC_READ_COUNT                    3
#define  ADC_NORMAL_LIMIT_MIN              -500
#define  ADC_NORMAL_LIMIT_MAX              500

#define FLASHLIGHT_CALLER 0
#define TINYMIX_CALLER 1
#define LINEOUT_GAIN_MASK 0x7F
static unsigned int g_new_val = 0;
bool flg_flashlight  = false;

/* HI6401 CODEC */
static struct snd_soc_codec *g_codec = NULL;
#ifdef CONFIG_DEBUG_FS
static struct dentry *debug_dir;

#define HI6401_PAGE_0_START	(BASE_ADDR_PAGE_0 + 0x1b0)
#define HI6401_PAGE_0_END	(BASE_ADDR_PAGE_0 + 0x1ff)
#define HI6401_PAGE_1_START	(BASE_ADDR_PAGE_1 + 0x1b0)
#define HI6401_PAGE_1_END	(BASE_ADDR_PAGE_1 + 0x1ff)
#endif

#define HI6401_CODEC_TOOL

#ifdef HI6401_CODEC_TOOL
static struct snd_soc_codec *g_codec_for_tool = NULL;
#endif

#ifdef CONFIG_HUAWEI_DSM
static struct dsm_dev dsm_anc_hs = {
	.name = "dsm_anc_hs",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};
static struct dsm_client *anc_hs_dclient = NULL;
#endif

struct anc_hs_data {
	int anc_hs_mode;
	struct regulator_bulk_data	regu_boost5v;
	int gpio_mic_sw;
	int mic_irq_gpio;
	int mic_irq;
	int channel_pwl_h;
	int channel_pwl_l;
	int anc_hs_limit_min;
	int anc_hs_limit_max;
	bool irq_flag;
	bool boost_flag;
	int no_charge_detect_period;
	int sleep_time;
	bool mic_used;
	int anc_resistence_level;

	int adc_calibration_base;
	bool calibration_done;
	int debug_sleep_time;

	struct mutex charge_lock;
	spinlock_t		irq_lock;

	struct workqueue_struct * anc_hs_btn_delay_wq;
	struct delayed_work anc_hs_btn_delay_work;

	struct workqueue_struct * anc_hs_charge_delay_wq;
	struct delayed_work anc_hs_charge_delay_work;
};

/* codec private data */
struct hi6401_priv {
	struct snd_soc_codec * codec;
	struct hi6401_irq * p_irq;
	struct regulator_bulk_data regu;
	struct clk * pmu_audio_clk;
	int irq[8];

	/* headset status */
	enum hi6401_jack_states hs_status;
	struct snd_soc_jack hs_jack;
#ifdef CONFIG_SWITCH
	struct switch_dev sdev;
#endif
	int report;
	int hs_btn_type;

	spinlock_t lock;
	struct wake_lock wake_lock;
	struct mutex mutex;
	struct mutex ibias_mutex;
	struct mutex plug_mutex;
	struct mutex saradc_mutex;
	struct mutex hs_micbias_mutex;
	struct mutex lineout_mutex;

	struct mutex dapm_mutex;
	unsigned int ref_pll;
	unsigned int ref_audio_clk;
	unsigned int ref_voice_clk;
	unsigned int ref_audio_stream;
	unsigned int ref_audio_tx;
	unsigned int ref_audio_rx;

	/* board defination */
	int hs_det;
	int hs_btn_num;
	int hs_3_pole_max_voltage;
	int hs_4_pole_min_voltage;
	int hs_4_pole_max_voltage;
	int btn_play_min_voltage;
	int btn_play_max_voltage;
	int btn_volume_up_min_voltage;
	int btn_volume_up_max_voltage;
	int btn_volume_down_min_voltage;
	int btn_volume_down_max_voltage;

	bool audio_master;
	bool bt_master;
	bool voice_master;
	bool aux_master;

	int audio_mode;
	int bt_mode;
	int voice_mode;
	int aux_mode;

	unsigned int hs_micbias_work;
	bool hs_micbias_saradc;
	unsigned int ibias_work;
	bool ibias_saradc;

	bool hsr_power_on;
	bool hsl_power_on;

	bool need_report_up_event;

	/* anc headset defination*/
	bool anc_hs_enable;
	struct anc_hs_data p_anc_hs;
	int button_pressed;

	struct workqueue_struct * headset_plug_in_delay_wq;
	struct delayed_work headset_plug_in_delay_work;
	struct workqueue_struct * headset_plug_out_delay_wq;
	struct delayed_work headset_plug_out_delay_work;

	struct workqueue_struct * headset_btn_up_delay_wq;
	struct delayed_work headset_btn_up_delay_work;
	struct workqueue_struct * headset_btn_down_delay_wq;
	struct delayed_work headset_btn_down_delay_work;
};

static void hi6401_enable_ibias(struct snd_soc_codec *codec, bool enable);
static void hi6401_hs_micbias_saradc_enable(struct snd_soc_codec *codec, bool enable);
static void hi6401_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable);
static void hi6401_ibias_saradc_enable(struct snd_soc_codec *codec, bool enable);
static void hi6401_ibias_work_enable(struct snd_soc_codec *codec, bool enable);
static bool need_charging(struct anc_hs_data *anc_hs);
static void anc_hs_adc_calibration(struct anc_hs_data *p_anc_hs);

#define SOC_ADC_INFO_EXT(xname, xhandler_get, xmin, xmax) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = anc_hs_adc_info, \
	.get = xhandler_get, .put = anc_hs_adc_set_value, \
	.private_value = (unsigned long) &(struct soc_mixer_control) \
	{.min = xmin, .max = xmax} \
}

static inline unsigned int hi6401_reg_read(struct snd_soc_codec *codec,
		unsigned int reg)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->p_irq);

	return hi6401_irq_read(priv->p_irq, reg);
}

static inline int hi6401_reg_write(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int value)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->p_irq);

	hi6401_irq_write(priv->p_irq, reg, value);

	return 0;
}

static void hi6401_reg_set_bit(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int offset)
{
	unsigned int val = 0;
	unsigned long flags = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == codec);

	spin_lock_irqsave(&priv->lock, flags);
	val = hi6401_reg_read(codec, reg) | (1 << offset);
	hi6401_reg_write(codec, reg, val);
	spin_unlock_irqrestore(&priv->lock, flags);
}

void hi6401_reg_clr_bit(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int offset)
{
	unsigned int val = 0;
	unsigned long flags = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == codec);

	spin_lock_irqsave(&priv->lock, flags);
	val = hi6401_reg_read(codec, reg) & ~(1 << offset);
	hi6401_reg_write(codec, reg, val);
	spin_unlock_irqrestore(&priv->lock, flags);
}

static void hi6401_reg_write_bits(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int value, unsigned int mask)
{
	unsigned int val = 0;
	unsigned long flags = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == codec);

	spin_lock_irqsave(&priv->lock, flags);
	val = hi6401_reg_read(codec, reg);
	val &= ~mask;
	val |= value & mask;
	hi6401_reg_write(codec, reg, val);
	spin_unlock_irqrestore(&priv->lock, flags);
}

static void hi6401_set_lineout_gain(int type)
{
	if (type == TINYMIX_CALLER) {
		if(flg_flashlight){
			/* flashlight doing */
			return;
		} else {
			/* flashlight done or not start */
			hi6401_reg_write_bits(g_codec, HI6401_LINEOUTLPGA_REG, g_new_val << 1, LINEOUT_GAIN_MASK);
		}
	} else if (type == FLASHLIGHT_CALLER) {
		if(flg_flashlight){
			/* flashlight start */
			hi6401_reg_write_bits(g_codec, HI6401_LINEOUTLPGA_REG, 0 << 1, LINEOUT_GAIN_MASK);
		} else {
			hi6401_reg_write_bits(g_codec, HI6401_LINEOUTLPGA_REG, g_new_val << 1 , LINEOUT_GAIN_MASK);
		}
	} else {
		pr_err("%s,error type:%d!", __FUNCTION__, type);
	}
}

void hi6401_set_gain_for_flashlight(bool enable)
{
#ifdef CONFIG_HISI_6421_SPK
	struct hi6401_priv *priv = dev_get_drvdata(g_codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->lineout_mutex);

	if (flg_flashlight == enable) {
		mutex_unlock(&priv->lineout_mutex);
		return;
	}

	flg_flashlight = enable;

	hi6401_set_lineout_gain(FLASHLIGHT_CALLER);
	mutex_unlock(&priv->lineout_mutex);
#endif
}
EXPORT_SYMBOL(hi6401_set_gain_for_flashlight);

int hi6401_set_gain_for_tinymix(struct snd_kcontrol *kc,
					struct snd_ctl_elem_value *uc)
{
	struct hi6401_priv *priv = dev_get_drvdata(g_codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->lineout_mutex);
	g_new_val = uc->value.integer.value[0];
	hi6401_set_lineout_gain(TINYMIX_CALLER);
	mutex_unlock(&priv->lineout_mutex);
	return 0;
}

#ifdef HI6401_CODEC_TOOL
/* provide to tools use only */
unsigned int codec_reg_read(unsigned int reg)
{
	return hi6401_reg_read(g_codec_for_tool, reg);
}

/* provide to tools use only */
void codec_reg_write(unsigned int reg, unsigned int value)
{
	hi6401_reg_write(g_codec_for_tool, reg, value);
}
#endif

/* VOLUME CONTROLS */
/*
* MAIN MIC GAIN volume control:
* from 0 to 22 dB in 2 dB steps
* MAX VALUE is 11
*/
static DECLARE_TLV_DB_SCALE(main_mic_tlv, 0, 200, 0);

/*
* SUB MIC GAIN volume control:
* from 0 to 22 dB in 2 dB steps
* MAX VALUE is 11
*/
static DECLARE_TLV_DB_SCALE(sub_mic_tlv, 0, 200, 0);

/*
* SIDE MIC GAIN volume control:
* from -30 to 16 dB in 2 dB steps
* MAX VALUE is 23
*/
static DECLARE_TLV_DB_SCALE(side_mic_tlv, -3000, 200, 0);

/*
* LINEIN GAIN volume control:
* from -30 to 16 dB in 2 dB steps
* MAX VALUE is 23
*/
static DECLARE_TLV_DB_SCALE(linein_tlv, -3000, 200, 0);

/*
* LINEOUT GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(lineout_tlv, -4200, 150, 0);

/*
* EARPIECE GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(earpiece_tlv, -4200, 150, 0);

/*
* HEADSET GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(headset_tlv, -4200, 150, 0);

static void anc_hs_dump(struct anc_hs_data *p_anc_hs)
{
	struct hi6401_priv *priv = container_of(p_anc_hs,
						struct hi6401_priv,
						p_anc_hs);

	pr_info("%s: mode:%d,irq:%d,boost:%d,sleep_time:%d,mic_used:%d,pressed:%d,switch:%d\n",
		__FUNCTION__,
		p_anc_hs->anc_hs_mode,
		p_anc_hs->irq_flag,
		p_anc_hs->boost_flag,
		p_anc_hs->sleep_time,
		p_anc_hs->mic_used,
		priv->button_pressed,
		gpio_get_value(p_anc_hs->gpio_mic_sw));

}

static int anc_hs_adc_info(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_info *uinfo)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int max = mc->max;
	int min = mc->min;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = min;
	uinfo->value.integer.max = max;
	return 0;
}

static int	anc_hs_adc_set_value(struct snd_kcontrol *kc,
					struct snd_ctl_elem_value *uc)
{
	//not supported
	return 0;
}

static int anc_hs_adc_h_value(struct snd_kcontrol *kc,
					struct snd_ctl_elem_value *uc)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kc);
	struct hi6401_priv *priv;

	BUG_ON(NULL == codec);

	priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	if(!priv->anc_hs_enable) {
		uc->value.integer.value[0] = ANC_HS_NOT_SUPPORT;
		return 0;
	}

	if(priv->p_anc_hs.anc_hs_mode == ANC_HS_CHARGE_ON ||
		priv->p_anc_hs.anc_hs_mode == ANC_HS_CHARGE_SWITCHING) {
		uc->value.integer.value[0] = hisi_adc_get_value(priv->p_anc_hs.channel_pwl_h);
		if(uc->value.integer.value[0] < 0) {
			pr_err("%s : read adc_h value err = %ld\n", __FUNCTION__, uc->value.integer.value[0]);
			anc_hs_dump(&priv->p_anc_hs);
			uc->value.integer.value[0] = 0;
		}
	}else {
		pr_info("%s : anc_hs adc h = %d\n", __FUNCTION__,
			hisi_adc_get_value(priv->p_anc_hs.channel_pwl_h));
		uc->value.integer.value[0] = ANC_HS_NOT_IN_CHARGING;
	}

	return 0;
}

static int anc_hs_adc_l_value(struct snd_kcontrol *kc,
					struct snd_ctl_elem_value *uc)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kc);
	struct hi6401_priv *priv;

	BUG_ON(NULL == codec);

	priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	if(!priv->anc_hs_enable) {
		uc->value.integer.value[0] = ANC_HS_NOT_SUPPORT;
		return 0;
	}

	if(priv->p_anc_hs.anc_hs_mode == ANC_HS_CHARGE_ON ||
		priv->p_anc_hs.anc_hs_mode == ANC_HS_CHARGE_SWITCHING){
		uc->value.integer.value[0] = hisi_adc_get_value(priv->p_anc_hs.channel_pwl_l);
		if(uc->value.integer.value[0] < 0) {
			pr_err("%s : read adc_l value err = %ld\n", __FUNCTION__, uc->value.integer.value[0]);
			anc_hs_dump(&priv->p_anc_hs);
			uc->value.integer.value[0] = 0;
		}
	}else {
		pr_info("%s : anc_hs adc l = %d\n", __FUNCTION__,
			hisi_adc_get_value(priv->p_anc_hs.channel_pwl_l));
		uc->value.integer.value[0] = ANC_HS_NOT_IN_CHARGING;
	}
	return 0;
}

static int anc_hs_adc_base(struct snd_kcontrol *kc,
					struct snd_ctl_elem_value *uc)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kc);
	struct hi6401_priv *priv;

	BUG_ON(NULL == codec);

	priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	if(!priv->anc_hs_enable) {
		uc->value.integer.value[0] = ANC_HS_NOT_SUPPORT;
	} else {
		if(priv->p_anc_hs.calibration_done)
			uc->value.integer.value[0] = priv->p_anc_hs.adc_calibration_base;
		else
			uc->value.integer.value[0] = ANC_HS_CALIBRATION_ERR;
	}

	return 0;
}

/* ANC HS KCONTROLS */
static const struct snd_kcontrol_new anc_hs_controls[] = {
	/* only for mmi test interface */
	SOC_ADC_INFO_EXT("ANC_HS_ADC_H", anc_hs_adc_h_value, 0, 3000),
	SOC_ADC_INFO_EXT("ANC_HS_ADC_L", anc_hs_adc_l_value, 0, 3000),
	SOC_ADC_INFO_EXT("ANC_HS_ADC_BASE", anc_hs_adc_base, -100, 3000),
};

/* SOUND KCONTROLS */
static const struct snd_kcontrol_new hi6401_snd_controls[] = {
	/* VOLUME */
	/* DBGAIN INT */
	SOC_SINGLE("HI6401_S1_IL_GAIN_INT",
		HI6401_S1_IL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S1_IR_GAIN_INT",
		HI6401_S1_IR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),

	SOC_SINGLE("HI6401_S2_IL_GAIN_INT",
		HI6401_S2_IL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S2_IR_GAIN_INT",
		HI6401_S2_IR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S2_OL_GAIN_INT",
		HI6401_S2_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S2_OR_GAIN_INT",
		HI6401_S2_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),

	SOC_SINGLE("HI6401_S3_I_GAIN_INT",
		HI6401_S3_I_GAIN_INT_REG,  HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S3_OL_GAIN_INT",
		HI6401_S3_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S3_OR_GAIN_INT",
		HI6401_S3_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),

	SOC_SINGLE("HI6401_S4_I_GAIN_INT",
		HI6401_S4_I_GAIN_INT_REG,  HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S4_OL_GAIN_INT",
		HI6401_S4_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_S4_OR_GAIN_INT",
		HI6401_S4_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),

	SOC_SINGLE_TLV("MAINMIC PGA VOLUME",
		HI6401_MAINPGA_REG, HI6401_MAINPGA_GAIN_BIT,
		11, /* MAX VALUE(11) SEE IN MAIN MIC GAIN NOTE */
		0, main_mic_tlv),
	SOC_SINGLE_TLV("SUBMIC PGA VOLUME",
		HI6401_AUXPGA_REG, HI6401_AUXPGA_GAIN_BIT,
		11, /* MAX VALUE(11) SEE IN SUB MIC GAIN NOTE */
		0, sub_mic_tlv),
	SOC_SINGLE_TLV("SIDETONE PGA VOLUME",
		HI6401_SIDEPGA_REG, HI6401_SIDEPGA_GAIN_BIT,
		23, /* MAX VALUE(23) SEE IN SIDE MIC GAIN NOTE */
		0, side_mic_tlv),

	SOC_SINGLE_TLV("EARPIECE PGA VOLUME",
		HI6401_EARPGA_REG, HI6401_EARPGA_GAIN_BIT,
		32, /* MAX VALUE(32) SEE IN EARPIECE GAIN NOTE */
		0, earpiece_tlv),
	SOC_SINGLE_TLV("LINEINL PGA VOLUME",
		HI6401_LINEINLPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
		23, /* MAX VALUE(23) SEE IN LINEIN GAIN NOTE */
		0, linein_tlv),
	SOC_SINGLE_TLV("LINEINR PGA VOLUME",
		HI6401_LINEINRPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
		23, /* MAX VALUE(23) SEE IN LINEIN GAIN NOTE */
		0, linein_tlv),

	SOC_SINGLE_EXT_TLV("LINEOUTL PGA VOLUME",
		HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
		32, /* MAX VALUE(32) SEE IN LINEOUT GAIN NOTE */
		0, snd_soc_get_volsw, hi6401_set_gain_for_tinymix, lineout_tlv),

	SOC_SINGLE_TLV("LINEOUTR PGA VOLUME",
		HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
		32, /* MAX VALUE(32) SEE IN LINEOUT GAIN NOTE */
		0, lineout_tlv),
	SOC_SINGLE_TLV("HEADSETL PGA VOLUME",
		HI6401_HSLPGA_REG, HI6401_HSPGA_GAIN_BIT,
		32, /* MAX VALUE(32) SEE IN HEADSET GAIN NOTE */
		0, headset_tlv),
	SOC_SINGLE_TLV("HEADSETR PGA VOLUME",
		HI6401_HSRPGA_REG, HI6401_HSPGA_GAIN_BIT,
		32, /* MAX VALUE(32) SEE IN HEADSET GAIN NOTE */
		0, headset_tlv),

	SOC_SINGLE("MAINMIC PGA BOOST",
		HI6401_MAINPGA_REG, HI6401_MAINPGA_BOOST_BIT, 1, 0),
	SOC_SINGLE("MAINMIC PGA MUTE",
		HI6401_MAINPGA_REG, HI6401_MAINPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("SUBMIC PGA BOOST",
		HI6401_AUXPGA_REG, HI6401_AUXPGA_BOOST_BIT, 1, 0),
	SOC_SINGLE("SUBMIC PGA MUTE",
		HI6401_AUXPGA_REG, HI6401_AUXPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("SIDETONE PGA MUTE",
		HI6401_SIDEPGA_REG, HI6401_SIDEPGA_MUTE_BIT, 1, 0),

	SOC_SINGLE("EARPIECE PGA MUTE",
		HI6401_EARPGA_REG, HI6401_EARPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("LINEINL PGA MUTE",
		HI6401_LINEINLPGA_REG, HI6401_LINEINPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("LINEINR PGA MUTE",
		HI6401_LINEINRPGA_REG, HI6401_LINEINPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("LINEOUTL PGA MUTE",
		HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("LINEOUTR PGA MUTE",
		HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("HEADSETL PGA MUTE",
		HI6401_HSLPGA_REG, HI6401_HSPGA_MUTE_BIT, 1, 0),
	SOC_SINGLE("HEADSETR PGA MUTE",
		HI6401_HSRPGA_REG, HI6401_HSPGA_MUTE_BIT, 1, 0),

	/* INTERFACE */
	/* S1 CONFIG */
	SOC_SINGLE("INTERFACE S1 FRAMEMODE",
		HI6401_S1_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 MASTERSLAVE",
		HI6401_S1_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 LRCLOCK",
		HI6401_S1_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 CHANNEL",
		HI6401_S1_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 WORDLENGTH",
		HI6401_S1_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),
	SOC_SINGLE("INTERFACE S1 DIRECTLOOP",
		HI6401_S1_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
	SOC_SINGLE("INTERFACE S1 TX CLK SEL",
		HI6401_S1_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 RX CLK SEL",
		HI6401_S1_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 DATAFORMAT",
		HI6401_S1_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S1 FUNCMODE",
		HI6401_S1_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

	/* S2 CONFIG */
	SOC_SINGLE("INTERFACE S2 FRAMEMODE",
		HI6401_S2_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 MASTERSLAVE",
		HI6401_S2_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 LRCLOCK",
		HI6401_S2_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 CHANNEL",
		HI6401_S2_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 WORDLENGTH",
		HI6401_S2_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),
	SOC_SINGLE("INTERFACE S2 DIRECTLOOP",
		HI6401_S2_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
	SOC_SINGLE("INTERFACE S2 TX CLK SEL",
		HI6401_S2_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 RX CLK SEL",
		HI6401_S2_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 DATAFORMAT",
		HI6401_S2_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S2 FUNCMODE",
		HI6401_S2_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

	/* S3 CONFIG */
	SOC_SINGLE("INTERFACE S3 FRAMEMODE",
		HI6401_S3_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 MASTERSLAVE",
		HI6401_S3_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 LRCLOCK",
		HI6401_S3_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 CHANNEL",
		HI6401_S3_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 WORDLENGTH",
		HI6401_S3_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),
	SOC_SINGLE("INTERFACE S3 DIRECTLOOP",
		HI6401_S3_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
	SOC_SINGLE("INTERFACE S3 TX CLK SEL",
		HI6401_S3_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 RX CLK SEL",
		HI6401_S3_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 DATAFORMAT",
		HI6401_S3_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S3 FUNCMODE",
		HI6401_S3_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

	/* S4 CONFIG */
	SOC_SINGLE("INTERFACE S4 FRAMEMODE",
		HI6401_S4_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 MASTERSLAVE",
		HI6401_S4_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 LRCLOCK",
		HI6401_S4_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 CHANNEL",
		HI6401_S4_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 WORDLENGTH",
		HI6401_S4_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),
	SOC_SINGLE("INTERFACE S4 DIRECTLOOP",
		HI6401_S4_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
	SOC_SINGLE("INTERFACE S4 TX CLK SEL",
		HI6401_S4_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 RX CLK SEL",
		HI6401_S4_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 DATAFORMAT",
		HI6401_S4_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
	SOC_SINGLE("INTERFACE S4 FUNCMODE",
		HI6401_S4_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

	/* FS S1/S2/S3/S4 */
	SOC_SINGLE("INTERFACE S1 FS",
		HI6401_FS_S1_S2_REG, HI6401_FS_S1_BIT, 6, 0),
	SOC_SINGLE("INTERFACE S2 FS",
		HI6401_FS_S1_S2_REG, HI6401_FS_S2_BIT, 6, 0),
	SOC_SINGLE("INTERFACE S3 FS",
		HI6401_FS_S3_S4_REG, HI6401_FS_S3_BIT, 6, 0),
	SOC_SINGLE("INTERFACE S4 FS",
		HI6401_FS_S3_S4_REG, HI6401_FS_S4_BIT, 6, 0),

	/* S2/S3/S4 SRC MODE */
	SOC_SINGLE("HI6401_S2_SRC_MODE",
		HI6401_SRC_MODE, HI6401_S2_SRC_MODE_BIT, 3, 0),
	SOC_SINGLE("HI6401_S3_SRC_MODE",
		HI6401_SRC_MODE, HI6401_S3_SRC_MODE_BIT, 3, 0),
	SOC_SINGLE("HI6401_S4_SRC_MODE",
		HI6401_SRC_MODE, HI6401_S4_SRC_MODE_BIT, 3, 0),

	/* FS DACLR/DACV/ADCLR & FIR CONFIGS */
	SOC_SINGLE("HI6401_FS_DACLR",
		HI6401_FS_DAC_REG, HI6401_FS_DACLR_BIT, 6, 0),
	SOC_SINGLE("HI6401_FS_DACV",
		HI6401_FS_DAC_REG, HI6401_FS_DACV_BIT, 6, 0),
	SOC_SINGLE("HI6401_FS_ADCLR",
		HI6401_FS_ADCLR_REG, HI6401_FS_ADCLR_BIT, 6, 0),

	SOC_SINGLE("HI6401_BYPASS_DACL_HBF1I",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_HBF1I_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_DACL_HBF2I",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_HBF2I_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_DACR_HBF1I",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_HBF1I_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_DACR_HBF2I",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_HBF2I_BIT, 1, 0),

	SOC_SINGLE("HI6401_BYPASS_DACV_HBF2I",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACV_HBF2I_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_DACV_HBFVI",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACV_HBFVI_BIT, 1, 0),

	SOC_SINGLE("HI6401_BYPASS_ADCL_HBF2D",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HBF2D_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_ADCL_HBFVD",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HBFVD_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_HPF",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HPF_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_ADCR_HBF2D",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HBF2D_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_ADCR_HBFVD",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HBFVD_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_HPF",
		HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HPF_BIT, 1, 0),

	/* SDM DITHER */
	SOC_SINGLE("HI6401_DACL_SDM_DITHER",
		HI6401_DAC_DITHER_CFG, HI6401_DACL_SDM_DITHER_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACR_SDM_DITHER",
		HI6401_DAC_DITHER_CFG, HI6401_DACR_SDM_DITHER_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACV_SDM_DITHER",
		HI6401_DAC_DITHER_CFG, HI6401_DACV_SDM_DITHER_BIT, 1, 0),

	/* DEEMP */
	SOC_SINGLE("HI6401_BYPASS_DACL_DEEMP",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_DEEMP_BIT, 1, 0),
	SOC_SINGLE("HI6401_BYPASS_DACR_DEEMP",
		HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_DEEMP_BIT, 1, 0),

	/* DAC MIXER GAIN */
	SOC_SINGLE("HI6401_DACL_MIXER_GAIN",
		HI6401_DAC_MIXER_GAIN_REG, HI6401_DACL_MIXER_GAIN_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACR_MIXER_GAIN",
		HI6401_DAC_MIXER_GAIN_REG, HI6401_DACR_MIXER_GAIN_BIT, 1, 0),

	/* S2 S4 MIXER GAIN */
	SOC_SINGLE("HI6401_S2_OL_MIXER_GAIN",
		HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S2_OL_MIXER_GAIN_BIT, 2, 0),
	SOC_SINGLE("HI6401_S2_OR_MIXER_GAIN",
		HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S2_OR_MIXER_GAIN_BIT, 2, 0),
	SOC_SINGLE("HI6401_S4_OL_MIXER_GAIN",
		HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S4_OL_MIXER_GAIN_BIT, 2, 0),
	SOC_SINGLE("HI6401_S4_OR_MIXER_GAIN",
		HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S4_OR_MIXER_GAIN_BIT, 2, 0),

	/* DMIC CONFIG */
	SOC_SINGLE("HI6401_DMIC_REVERSE",
		HI6401_DMIC_CFG, HI6401_DMIC_REVERSE_BIT, 1, 0),
	SOC_SINGLE("HI6401_DMIC_MODE",
		HI6401_DMIC_CFG, HI6401_DMIC_MODE_BIT, 1, 0),

	/* DACL AGC CONFIG */
	SOC_SINGLE("HI6401_DACL_AGC_TIMENNG",
		HI6401_DACL_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_NGI",
		HI6401_DACL_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACL_AGC_TIMER",
		HI6401_DACL_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACL_AGC_NGH",
		HI6401_DACL_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_NGL",
		HI6401_DACL_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_KFRAPID",
		HI6401_DACL_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_KFSLOW",
		HI6401_DACL_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_GSUPPRESS",
		HI6401_DACL_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACL_AGC_T_AMIN",
		HI6401_DACL_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_YTARGET",
		HI6401_DACL_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACL_AGC_NGW",
		HI6401_DACL_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_TIMEMUTE",
		HI6401_DACL_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_GSTEPD",
		HI6401_DACL_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_LEVELLOW",
		HI6401_DACL_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_GWIN",
		HI6401_DACL_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_BYPASS",
		HI6401_DACL_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACL_AGC_MUTE_BYPASS",
		HI6401_DACL_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACL_AGC_GMUTE",
		HI6401_DACL_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_TIMEHOLD",
		HI6401_DACL_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_TIMEDECAY",
		HI6401_DACL_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACL_AGC_USER",
		HI6401_DACL_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

	/* DACR AGC CONFIG*/
	SOC_SINGLE("HI6401_DACR_AGC_TIMENNG",
		HI6401_DACR_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_NGI",
		HI6401_DACR_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACR_AGC_TIMER",
		HI6401_DACR_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACR_AGC_NGH",
		HI6401_DACR_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_NGL",
		HI6401_DACR_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_KFRAPID",
		HI6401_DACR_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_KFSLOW",
		HI6401_DACR_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_GSUPPRESS",
		HI6401_DACR_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACR_AGC_T_AMIN",
		HI6401_DACR_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_YTARGET",
		HI6401_DACR_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_DACR_AGC_NGW",
		HI6401_DACR_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_TIMEMUTE",
		HI6401_DACR_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_GSTEPD",
		HI6401_DACR_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_LEVELLOW",
		HI6401_DACR_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_GWIN",
		HI6401_DACR_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_BYPASS",
		HI6401_DACR_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACR_AGC_MUTE_BYPASS",
		HI6401_DACR_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_DACR_AGC_GMUTE",
		HI6401_DACR_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_TIMEHOLD",
		HI6401_DACR_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_TIMEDECAY",
		HI6401_DACR_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_DACR_AGC_USER",
		HI6401_DACR_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

	/* ADCL AGC CONFIG */
	SOC_SINGLE("HI6401_ADCL_AGC_TIMENNG",
		HI6401_ADCL_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_NGI",
		HI6401_ADCL_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_TIMER",
		HI6401_ADCL_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_NGH",
		HI6401_ADCL_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_NGL",
		HI6401_ADCL_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_KFRAPID",
		HI6401_ADCL_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_KFSLOW",
		HI6401_ADCL_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_GSUPPRESS",
		HI6401_ADCL_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_T_AMIN",
		HI6401_ADCL_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_YTARGET",
		HI6401_ADCL_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_NGW",
		HI6401_ADCL_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_TIMEMUTE",
		HI6401_ADCL_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_GSTEPD",
		HI6401_ADCL_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_LEVELLOW",
		HI6401_ADCL_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_GWIN",
		HI6401_ADCL_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_BYPASS",
		HI6401_ADCL_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_MUTE_BYPASS",
		HI6401_ADCL_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_GMUTE",
		HI6401_ADCL_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_TIMEHOLD",
		HI6401_ADCL_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_TIMEDECAY",
		HI6401_ADCL_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCL_AGC_USER",
		HI6401_ADCL_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

	/* ADCR AGC CONFIG */
	SOC_SINGLE("HI6401_ADCR_AGC_TIMENNG",
		HI6401_ADCR_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_NGI",
		HI6401_ADCR_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_TIMER",
		HI6401_ADCR_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_NGH",
		HI6401_ADCR_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_NGL",
		HI6401_ADCR_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_KFRAPID",
		HI6401_ADCR_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_KFSLOW",
		HI6401_ADCR_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_GSUPPRESS",
		HI6401_ADCR_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_T_AMIN",
		HI6401_ADCR_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_YTARGET",
		HI6401_ADCR_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_NGW",
		HI6401_ADCR_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_TIMEMUTE",
		HI6401_ADCR_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_GSTEPD",
		HI6401_ADCR_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_LEVELLOW",
		HI6401_ADCR_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_GWIN",
		HI6401_ADCR_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_BYPASS",
		HI6401_ADCR_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_MUTE_BYPASS",
		HI6401_ADCR_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_GMUTE",
		HI6401_ADCR_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_TIMEHOLD",
		HI6401_ADCR_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_TIMEDECAY",
		HI6401_ADCR_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),
	SOC_SINGLE("HI6401_ADCR_AGC_USER",
		HI6401_ADCR_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),
	SOC_SINGLE("HI6401_BIAS_2_ANALOG_LOOP",
		HI6401_BIAS_2, HI6401_BIAS_2_ANALOG_LOOP_BIT, 1, 0),
};

/* DAPM KCONTROLS */

/* OUT EAR MIXERPICE*/
static const struct snd_kcontrol_new hi6401_mixerout_ear_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6401_MIXOUT_EAR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* HEADSETL MIXER*/
static const struct snd_kcontrol_new hi6401_mixerout_hsl_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6401_MIXOUT_HSL, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* HEADSETR MIXER*/
static const struct snd_kcontrol_new hi6401_mixerout_hsr_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6401_MIXOUT_HSR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* MIXER OUT LINEOUT LEFT*/
static const struct snd_kcontrol_new hi6401_mixerout_lineoutl_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* MIXER OUT LINEOUT RIGHT*/
static const struct snd_kcontrol_new hi6401_mixerout_lineoutr_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("SIDETONE SWITCH",
		HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* ADCL MIXER */
static const struct snd_kcontrol_new hi6401_mixerin_left_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("MAINMIC SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_MAINPGA_BIT, 1, 0),
	SOC_DAPM_SINGLE("SUBMIC SWITCH",
		HI6401_MIXINL, HI6401_MIXIN_AUXPGA_BIT, 1, 0),
};

/* ADCR MIXER */
static const struct snd_kcontrol_new hi6401_mixerin_right_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_DACL_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_DACR_BIT, 1, 0),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_DACV_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIL SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_LINEINL_BIT, 1, 0),
	SOC_DAPM_SINGLE("LIR SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_LINEINR_BIT, 1, 0),
	SOC_DAPM_SINGLE("MAINMIC SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_MAINPGA_BIT, 1, 0),
	SOC_DAPM_SINGLE("SUBMIC SWITCH",
		HI6401_MIXINR, HI6401_MIXIN_AUXPGA_BIT, 1, 0),
};

/* MIXER DACL */
static const struct snd_kcontrol_new hi6401_mixer_dacl_controls[] = {
	SOC_DAPM_SINGLE("S1L SWITCH",
		HI6401_DAC_MIXER, HI6401_MIXER_DACL_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("S2L SWITCH",
		HI6401_DAC_MIXER, HI6401_MIXER_DACL_S2_BIT, 1, 1),
};

/* MIXER DACR */
static const struct snd_kcontrol_new hi6401_mixer_dacr_controls[] = {
	SOC_DAPM_SINGLE("S1R SWITCH",
		HI6401_DAC_MIXER, HI6401_MIXER_DACR_S1_BIT, 1, 1),
	SOC_DAPM_SINGLE("S2R SWITCH",
		HI6401_DAC_MIXER, HI6401_MIXER_DACR_S2_BIT, 1, 1),
};

/* MIXER S2L */
static const struct snd_kcontrol_new hi6401_mixer_s2l_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OL_DACL_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADCL SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OL_ADCL_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OL_DACV_BIT, 1, 1),
	SOC_DAPM_SINGLE("S1LR SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OL_S1LR_BIT, 1, 1),
};

/* MIXER S2R */
static const struct snd_kcontrol_new hi6401_mixer_s2r_controls[] = {
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OR_DACR_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADCR SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OR_ADCR_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OR_DACV_BIT, 1, 1),
	SOC_DAPM_SINGLE("S1LR SWITCH",
		HI6401_S2_MIXER, HI6401_S2_MIXER_OR_S1LR_BIT, 1, 1),
};

/* MIXER S4L */
static const struct snd_kcontrol_new hi6401_mixer_s4l_controls[] = {
	SOC_DAPM_SINGLE("DACL SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OL_DACL_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADCL SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OL_ADCL_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OL_DACV_BIT, 1, 1),
	SOC_DAPM_SINGLE("S1LR SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OL_S1LR_BIT, 1, 1),
};

/* MIXER S4R */
static const struct snd_kcontrol_new hi6401_mixer_s4r_controls[] = {
	SOC_DAPM_SINGLE("DACR SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OR_DACR_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADCR SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OR_ADCR_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACV SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OR_DACV_BIT, 1, 1),
	SOC_DAPM_SINGLE("S1LR SWITCH",
		HI6401_S4_MIXER, HI6401_S4_MIXER_OR_S1LR_BIT, 1, 1),
};


static const char *hi6401_mic_mux_texts[] = {
	"MIC OFF",	/* 00/11 : mute */
	"MIC MAIN",	/* 01 : enable mainmic */
	"MIC HS",	/* 10 : enable hs_mic */
};
static const struct soc_enum hi6401_mic_mux_enum =
	SOC_ENUM_SINGLE(HI6401_MAINPGA_REG, HI6401_MAINPGA_SEL_BIT,
		ARRAY_SIZE(hi6401_mic_mux_texts), hi6401_mic_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_mic_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_mic_mux_enum);

static const char *hi6401_chn_mux_texts[] = {
	"LEFT",		/* 0 : LEFT */
	"RIGHT",	/* 1 : RIGHT */
};
static const struct soc_enum hi6401_s3_chn_mux_enum =
	SOC_ENUM_SINGLE(HI6401_MONO_MUX_SEL, HI6401_S3_CHN_SEL,
		ARRAY_SIZE(hi6401_chn_mux_texts), hi6401_chn_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s3_chn_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_s3_chn_mux_enum);

static const struct soc_enum hi6401_s4_chn_mux_enum =
	SOC_ENUM_SINGLE(HI6401_MONO_MUX_SEL, HI6401_S4_CHN_SEL,
		ARRAY_SIZE(hi6401_chn_mux_texts), hi6401_chn_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4_chn_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_s4_chn_mux_enum);

static const char *hi6401_dacv_mux_texts[] = {
	"S3MODEM",	/* 0 : S3 MODEM */
	"S4MODEM",	/* 1 : S4 MODEM */
};
static const struct soc_enum hi6401_dacv_mux_enum =
	SOC_ENUM_SINGLE(HI6401_MONO_MUX_SEL, HI6401_DACV_CHN_SEL,
		ARRAY_SIZE(hi6401_dacv_mux_texts), hi6401_dacv_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_dacv_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_dacv_mux_enum);


static const char *hi6401_adc_agc_mux_texts[] = {
	"ADCL",		/* 0 : ADCL */
	"ADCR",		/* 1 : ADCR */
	"S2L",		/* 2 : S2L  */
	"S2R",		/* 3 : S2R  */
	"S3MODEM",	/* 4 : S3MODEM */
	"S4MODEM",	/* 5 : S4MODEM */
};

static const struct soc_enum hi6401_adc_agcl_mux_enum =
	SOC_ENUM_SINGLE(HI6401_S1_MUX_SEL, HI6401_S1_OL_BIT,
		ARRAY_SIZE(hi6401_adc_agc_mux_texts), hi6401_adc_agc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_agcl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_adc_agcl_mux_enum);

static const struct soc_enum hi6401_adc_agcr_mux_enum =
	SOC_ENUM_SINGLE(HI6401_S1_MUX_SEL, HI6401_S1_OR_BIT,
		ARRAY_SIZE(hi6401_adc_agc_mux_texts), hi6401_adc_agc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_agcr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_adc_agcr_mux_enum);

static const char *hi6401_uplinkl_mux_texts[] = {
	"S1L",		/* 0 : S1L */
	"S1LR",		/* 1 : S1LR */
	"S2L",		/* 2 : S2L */
	"DACL",		/* 3 : DACL */
	"ADCL",		/* 4 : ADCL */
	"S4MODEM",	/* 5 : S4MODEM */
};
static const struct soc_enum hi6401_uplinkl_mux_enum =
	SOC_ENUM_SINGLE(HI6403_S3_MUX_SEL, HI6401_S3_OL_BIT,
		ARRAY_SIZE(hi6401_uplinkl_mux_texts), hi6401_uplinkl_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_uplinkl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_uplinkl_mux_enum);

static const char *hi6401_uplinkr_mux_texts[] = {
	"S1R",		/* 0 : S1R */
	"S1LR",		/* 1 : S1LR */
	"S2R",		/* 2 : S2R */
	"DACR",		/* 3 : DACR */
	"ADCR",		/* 4 : ADCR */
	"S4MODEM",	/* 5 : S4MODEM */
};
static const struct soc_enum hi6401_uplinkr_mux_enum =
	SOC_ENUM_SINGLE(HI6403_S3_MUX_SEL, HI6401_S3_OR_BIT,
		ARRAY_SIZE(hi6401_uplinkr_mux_texts), hi6401_uplinkr_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_uplinkr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_uplinkr_mux_enum);


static const char *hi6401_s4l_mux_texts[] = {
	"UPLINKL",	/* 0 : UPLINKL */
	"S4MIXERL",	/* 1 : S4MIXERL */
	"S4MIXERLR",	/* 2 : S4MIXERLR */
};
static const struct soc_enum hi6401_s4l_mux_enum =
	SOC_ENUM_SINGLE(HI6404_S4_MUX_SEL, HI6401_S4_OL_BIT,
		ARRAY_SIZE(hi6401_s4l_mux_texts), hi6401_s4l_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4l_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_s4l_mux_enum);

static const char *hi6401_s4r_mux_texts[] = {
	"UPLINKR",	/* 0 : UPLINKR */
	"S4MIXERR",	/* 1 : S4MIXERR */
	"S4MIXERLR",	/* 2 : S4MIXERLR */
};
static const struct soc_enum hi6401_s4r_mux_enum =
	SOC_ENUM_SINGLE(HI6404_S4_MUX_SEL, HI6401_S4_OR_BIT,
		ARRAY_SIZE(hi6401_s4r_mux_texts), hi6401_s4r_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4r_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_s4r_mux_enum);

/* ADC FLITER LEFT & RIGHT MUX */
static const char *hi6401_adc_mux_texts[] = {
	"ADC",	/* 0 : ADC FILTER Mux choose ADC */
	"DACL",	/* 1 : ADC FILTER Mux choose DAC Filter L */
	"DACR",	/* 2 : ADC FILTER Mux choose DAC Filter R */
	"DACV",	/* 3 : ADC FILTER Mux choose DAC Filter V */
	"DMIC",	/* 4 : ADC FILTER Mux choose Digital Mic */
};

static const struct soc_enum hi6401_adcl_mux_enum =
	SOC_ENUM_SINGLE(HI6401_ADC_MUX_CFG, HI6401_ADCL_MUX_BIT,
		ARRAY_SIZE(hi6401_adc_mux_texts), hi6401_adc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_adcl_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_adcl_mux_enum);

static const struct soc_enum hi6401_adcr_mux_enum =
	SOC_ENUM_SINGLE(HI6401_ADC_MUX_CFG, HI6401_ADCR_MUX_BIT,
		ARRAY_SIZE(hi6401_adc_mux_texts), hi6401_adc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_adcr_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_adcr_mux_enum);

/* DIGITAL MIC MUX */
static const char *hi6401_digmic_mux_texts[] = {
	"OFF",	/* 0 : off the clock */
	"2FD",	/* 1 : 2 frequency division */
	"3FD",	/* 2 : 3 frequency division */
	"4FD",	/* 3 : 4 frequency division */
};

static const struct soc_enum hi6401_digmic_mux_enum =
	SOC_ENUM_SINGLE(HI6401_DMIC_CFG, HI6401_DMIC_CLK_BIT,
		ARRAY_SIZE(hi6401_digmic_mux_texts), hi6401_digmic_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_digmic_mux_controls =
	SOC_DAPM_ENUM("Mux", hi6401_digmic_mux_enum);

/* S1 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_s1_outl_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S1_MODULE_CLK_REG, HI6401_S1_AGC_OL_EN_BIT, 1, 0);

/* S1 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_s1_outr_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S1_MODULE_CLK_REG, HI6401_S1_AGC_OR_EN_BIT, 1, 0);

/* S3 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S3_outl_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_OL_EN_BIT, 1, 0);

/* S3 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S3_outr_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_OR_EN_BIT, 1, 0);

/* S4 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S4_outl_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_OL_EN_BIT, 1, 0);

/* S4 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S4_outr_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_OR_EN_BIT, 1, 0);

/* DACL FILTER */
static const struct snd_kcontrol_new hi6401_dapm_dacl_filter_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_CHANNEL_CLK_REG, HI6401_DACL_CLK_EN_BIT, 1, 0);

/* DACR FILTER */
static const struct snd_kcontrol_new hi6401_dapm_dacr_filter_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_CHANNEL_CLK_REG, HI6401_DACR_CLK_EN_BIT, 1, 0);

/* DACV FILTER */
static const struct snd_kcontrol_new hi6401_dapm_dacv_filter_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_CHANNEL_CLK_REG, HI6401_DACV_CLK_EN_BIT, 1, 0);

/* ADCL FILTER */
static const struct snd_kcontrol_new hi6401_dapm_adcl_filter_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_CHANNEL_CLK_REG, HI6401_ADCL_CLK_EN_BIT, 1, 0);

/* ADCR FILTER */
static const struct snd_kcontrol_new hi6401_dapm_adcr_filter_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_CHANNEL_CLK_REG, HI6401_ADCR_CLK_EN_BIT, 1, 0);

/* EARPIECE */
static const struct snd_kcontrol_new hi6401_dapm_earpiece_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_EAR_PD_REG, HI6401_EAR_PD_BIT, 1, 1);

/* HEADPHONE LEFT */
static const struct snd_kcontrol_new hi6401_dapm_hsl_switch_controls =
	SOC_DAPM_SINGLE("SWITCH", 0x11b3, 0, 1, 1);

/* HEADPHONE RIGHT */
static const struct snd_kcontrol_new hi6401_dapm_hsr_switch_controls =
	SOC_DAPM_SINGLE("SWITCH", 0x11b3, 1, 1, 1);

/* LINEOUT LEFT */
static const struct snd_kcontrol_new hi6401_dapm_lol_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_LOL_PD_REG, HI6401_LOL_PD_BIT, 1, 1);

/* LINEOUT RIGHT */
static const struct snd_kcontrol_new hi6401_dapm_lor_switch_controls =
	SOC_DAPM_SINGLE("SWITCH",
		HI6401_LOR_PD_REG, HI6401_LOR_PD_BIT, 1, 1);

static void hi6401_pll_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->p_irq);

	mutex_lock(&priv->dapm_mutex);
	if (enable) {
		if (0 == priv->ref_pll) {
			hi6401_ibias_work_enable(codec, true);
			ret = clk_prepare_enable(priv->pmu_audio_clk);
			if (0 != ret) {
				pr_err("pmu_audio_clk :clk prepare enable failed !\n");
				mutex_unlock(&priv->dapm_mutex);
				return;
			}

			hi6401_reg_clr_bit(codec, HI6401_PLL_PD_REG, HI6401_PLL_PD_BIT);
			usleep_range(200, 250);
			hi6401_reg_set_bit(codec, HI6401_PLL_EN_REG, HI6401_PLL_EN_BIT);

			hi6401_pll_check_enable(priv->p_irq, true);
		}
		++priv->ref_pll;
	} else {
		--priv->ref_pll;
		if (0 == priv->ref_pll) {
			hi6401_pll_check_enable(priv->p_irq, false);

			hi6401_reg_clr_bit(codec, HI6401_PLL_EN_REG, HI6401_PLL_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_PLL_PD_REG, HI6401_PLL_PD_BIT);

			clk_disable_unprepare(priv->pmu_audio_clk);
			hi6401_ibias_work_enable(codec, false);
		}
	}
	mutex_unlock(&priv->dapm_mutex);
}

static void hi6401_audio_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->dapm_mutex);
	if (enable) {
		if (0 == priv->ref_audio_clk) {
			hi6401_reg_clr_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S1_HZ_BIT);
			hi6401_reg_set_bit(codec, HI6401_IF_CLK_REG, HI6401_S1_IF_CLK_EN_BIT);
		}
		++priv->ref_audio_clk;
	} else {
		--priv->ref_audio_clk;
		if (0 == priv->ref_audio_clk) {
			hi6401_reg_clr_bit(codec, HI6401_IF_CLK_REG, HI6401_S1_IF_CLK_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S1_HZ_BIT);
		}
	}
	mutex_unlock(&priv->dapm_mutex);
}

static void hi6401_audio_rx_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->dapm_mutex);
	if (enable) {
		if (0 == priv->ref_audio_rx)
			hi6401_reg_set_bit(codec, HI6401_S1_CONFIG_1, HI6401_IF_RX_EN_BIT);
		++priv->ref_audio_rx;
	} else {
		--priv->ref_audio_rx;
		if (0 == priv->ref_audio_rx)
			hi6401_reg_clr_bit(codec, HI6401_S1_CONFIG_1, HI6401_IF_RX_EN_BIT);
	}
	mutex_unlock(&priv->dapm_mutex);
}

static void hi6401_audio_tx_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	mutex_lock(&priv->dapm_mutex);
	if (enable) {
		if (0 == priv->ref_audio_tx)
			hi6401_reg_set_bit(codec, HI6401_S1_CONFIG_1, HI6401_IF_TX_EN_BIT);
		++priv->ref_audio_tx;
	} else {
		--priv->ref_audio_tx;
		if (0 == priv->ref_audio_tx)
			hi6401_reg_clr_bit(codec, HI6401_S1_CONFIG_1, HI6401_IF_TX_EN_BIT);
	}
	mutex_unlock(&priv->dapm_mutex);
}

static void hi6401_voice_clk_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->dapm_mutex);
	if (enable) {
		if (0 == priv->ref_voice_clk) {
			hi6401_reg_clr_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S3_HZ_BIT);
			hi6401_reg_set_bit(codec, HI6401_IF_CLK_REG, HI6401_S3_IF_CLK_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_S3_CONFIG_1, HI6401_IF_TX_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_S3_CONFIG_1, HI6401_IF_RX_EN_BIT);
		}
		++priv->ref_voice_clk;
	} else {
		--priv->ref_voice_clk;
		if (0 == priv->ref_voice_clk) {
			hi6401_reg_clr_bit(codec, HI6401_S3_CONFIG_1, HI6401_IF_RX_EN_BIT);
			hi6401_reg_clr_bit(codec, HI6401_S3_CONFIG_1, HI6401_IF_TX_EN_BIT);
			hi6401_reg_clr_bit(codec, HI6401_IF_CLK_REG, HI6401_S3_IF_CLK_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S3_HZ_BIT);
		}
	}
	mutex_unlock(&priv->dapm_mutex);
}

int hi6401_main_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_clr_bit(codec, HI6401_MAINMICBIAS_PD_REG, HI6401_MAINMICBIAS_PD_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_set_bit(codec, HI6401_MAINMICBIAS_PD_REG, HI6401_MAINMICBIAS_PD_BIT);
		hi6401_reg_set_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_MAINMICB_DSCHG_BIT);
		msleep(5);
		hi6401_reg_clr_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_MAINMICB_DSCHG_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_sub_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_clr_bit(codec, HI6401_SUBMICBIAS_PD_REG, HI6401_SUBMICBIAS_PD_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_set_bit(codec, HI6401_SUBMICBIAS_PD_REG, HI6401_SUBMICBIAS_PD_BIT);
		hi6401_reg_set_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_SUBMICB_DSCHG_BIT);
		msleep(5);
		hi6401_reg_clr_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_SUBMICB_DSCHG_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_hs_micbias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_hs_micbias_work_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_hs_micbias_work_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void hi6401_hs_power_on(struct snd_soc_codec *codec)
{
	unsigned int hsl_reg_value = 0;
	unsigned int hsr_reg_value = 0;
	unsigned int hsl_pga_value = 0;
	unsigned int hsr_pga_value = 0;
	unsigned int cm_ctrl_l = 0;
	unsigned int cm_ctrl_r = 0;
	unsigned int min_pga = 0;
	int i = 0;

	mdelay(1);

	/* chargepump */
	hi6401_reg_clr_bit(codec, HI6401_CP_PD_REG, HI6401_CP_PD_BIT);
	hi6401_reg_clr_bit(codec, HI6401_CP_PD_REG, HI6401_CP_DET_PD_BIT);

	/* config pop control */
	hi6401_reg_write(codec, HI6401_POP_CTRL1, 0xE1);
	hi6401_reg_write(codec, HI6401_POP_CTRL2, 0x6C);

	hsl_reg_value = hi6401_reg_read(codec, HI6401_HSLPGA_REG);
	hsr_reg_value = hi6401_reg_read(codec, HI6401_HSRPGA_REG);
	hsl_pga_value = hsl_reg_value & 0x7E;
	hsr_pga_value = hsr_reg_value & 0x7E;
	cm_ctrl_l = hsl_reg_value & 0x80;
	cm_ctrl_r = hsr_reg_value & 0x80;

	/* mute hs pga */
	hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x01);
	hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x01);

	/* zero cross */
	hi6401_reg_set_bit(codec, HI6401_ZC_EN, HI6401_HSL_ZCD_EN_BIT);
	hi6401_reg_set_bit(codec, HI6401_ZC_EN, HI6401_HSR_ZCD_EN_BIT);
	mdelay(7);

	/* power on hs pga */
	hi6401_reg_clr_bit(codec, HI6401_HSL_PD_REG, HI6401_HSL_PD_BIT);
	hi6401_reg_clr_bit(codec, HI6401_HSR_PD_REG, HI6401_HSR_PD_BIT);
	mdelay(70);

	/* power on mixer */
	hi6401_reg_clr_bit(codec, HI6401_MIXOUT_HSL_PD_REG, HI6401_MIXOUT_HSL_PD_BIT);
	hi6401_reg_clr_bit(codec, HI6401_MIXOUT_HSR_PD_REG, HI6401_MIXOUT_HSR_PD_BIT);

	min_pga = (hsl_pga_value < hsr_pga_value) ? hsl_pga_value : hsr_pga_value;

	/* unmute hs pga & step up */
	hi6401_reg_write(codec, HI6401_HSLPGA_REG, cm_ctrl_l);
	hi6401_reg_write(codec, HI6401_HSRPGA_REG, cm_ctrl_r);

	if (0x10 <= min_pga) {
		hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x10 | cm_ctrl_l);
		hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x10 | cm_ctrl_r);
		STEP_DELAY;
		i = 0x10;
	}

	if (0x18 <= min_pga) {
		hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x18 | cm_ctrl_l);
		hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x18 | cm_ctrl_r);
		STEP_DELAY;
		i = 0x18;
	}

	for(i += 2; i <= min_pga; i += 2) {
		hi6401_reg_write(codec, HI6401_HSLPGA_REG, i | cm_ctrl_l);
		hi6401_reg_write(codec, HI6401_HSRPGA_REG, i | cm_ctrl_r);
		STEP_DELAY;
	}

	/* in case of hsl & hsr pga is not same */
	/* do not change the value of i */
	if (hsl_pga_value > hsr_pga_value) {
		for (;i < hsl_pga_value; i += 2) {
			hi6401_reg_write(codec, HI6401_HSLPGA_REG, i | cm_ctrl_l);
			STEP_DELAY;
		}
	} else if (hsl_pga_value < hsr_pga_value) {
		for (;i < hsr_pga_value; i += 2) {
			hi6401_reg_write(codec, HI6401_HSRPGA_REG, i | cm_ctrl_r);
			STEP_DELAY;
		}
	} else {
		/* do nothing */
	}
}

static void hi6401_hs_power_off(struct snd_soc_codec *codec)
{
	unsigned int hsl_reg_value = 0;
	unsigned int hsr_reg_value = 0;
	unsigned int hsl_pga_value = 0;
	unsigned int hsr_pga_value = 0;
	unsigned int cm_ctrl_l = 0;
	unsigned int cm_ctrl_r = 0;
	unsigned int min_pga = 0;
	int i = 0;

	hsl_reg_value = hi6401_reg_read(codec, HI6401_HSLPGA_REG);
	hsr_reg_value = hi6401_reg_read(codec, HI6401_HSRPGA_REG);
	hsl_pga_value = hsl_reg_value & 0x7E;
	hsr_pga_value = hsr_reg_value & 0x7E;
	cm_ctrl_l = hsl_reg_value & 0x80;
	cm_ctrl_r = hsr_reg_value & 0x80;
	min_pga = (hsl_pga_value < hsr_pga_value) ? hsl_pga_value : hsr_pga_value;

	/* in case of hsl & hsr pga is not same */
	if (hsl_pga_value > hsr_pga_value) {
		for (i = hsl_pga_value; i > min_pga; i -= 2) {
			hi6401_reg_write(codec, HI6401_HSLPGA_REG, i | cm_ctrl_l);
			STEP_DELAY;
		}
	} else if (hsl_pga_value < hsr_pga_value) {
		for (i = hsr_pga_value; i > min_pga; i -= 2) {
			hi6401_reg_write(codec, HI6401_HSRPGA_REG, i | cm_ctrl_r);
			STEP_DELAY;;
		}
	} else {
		/* do nothing */
	}

	/* step dowm & mute hs pga */
	for (i = min_pga; i >= 0x18; i -= 2) {
		hi6401_reg_write(codec, HI6401_HSLPGA_REG, i | cm_ctrl_l);
		hi6401_reg_write(codec, HI6401_HSRPGA_REG, i | cm_ctrl_r);
		STEP_DELAY;
	}

	if (0x10 <= min_pga) {
		hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x10);
		hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x10);
		STEP_DELAY;
	}

	hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x00);
	hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x00);
	STEP_DELAY;
	hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x01);
	hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x01);

	/* power off mixer */
	hi6401_reg_set_bit(codec, HI6401_MIXOUT_HSL_PD_REG, HI6401_MIXOUT_HSL_PD_BIT);
	hi6401_reg_set_bit(codec, HI6401_MIXOUT_HSR_PD_REG, HI6401_MIXOUT_HSR_PD_BIT);

	/* config pop control */
	hi6401_reg_write(codec, HI6401_POP_CTRL2, 0x5C);

	/* power off hp pga */
	hi6401_reg_set_bit(codec, HI6401_HSL_PD_REG, HI6401_HSL_PD_BIT);
	hi6401_reg_set_bit(codec, HI6401_HSR_PD_REG, HI6401_HSR_PD_BIT);
	mdelay(70);

	/* zero cross */
	hi6401_reg_clr_bit(codec, HI6401_ZC_EN, HI6401_HSL_ZCD_EN_BIT);
	hi6401_reg_clr_bit(codec, HI6401_ZC_EN, HI6401_HSR_ZCD_EN_BIT);

	/* chargerpump */
	hi6401_reg_set_bit(codec, HI6401_CP_PD_REG, HI6401_CP_DET_PD_BIT);
	hi6401_reg_set_bit(codec, HI6401_CP_PD_REG, HI6401_CP_PD_BIT);
}

int hi6401_hsl_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6401_priv *priv = NULL;

	BUG_ON(NULL == codec);
	priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->hsl_power_on = true;
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6401_hs_power_on(codec);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6401_hs_power_off(codec);
		priv->hsl_power_on = false;
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_hsr_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct hi6401_priv *priv = NULL;

	BUG_ON(NULL == codec);
	priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->hsr_power_on = true;
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6401_hs_power_on(codec);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (priv->hsl_power_on && priv->hsr_power_on)
			hi6401_hs_power_off(codec);
		priv->hsr_power_on = false;
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_ear_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_set_bit(codec, HI6401_EARPGA_REG, HI6401_EARPGA_MUTE_BIT);
		hi6401_reg_set_bit(codec, HI6401_ZC_EN, HI6401_EAR_ZCD_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMU:
		hi6401_reg_clr_bit(codec, HI6401_EARPGA_REG, HI6401_EARPGA_MUTE_BIT);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		hi6401_reg_set_bit(codec, HI6401_EARPGA_REG, HI6401_EARPGA_MUTE_BIT);
		msleep(5);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_clr_bit(codec, HI6401_ZC_EN, HI6401_EAR_ZCD_EN_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_lol_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_set_bit(codec, HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		hi6401_reg_set_bit(codec, HI6401_ZC_EN, HI6401_LOL_ZCD_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMU:
		hi6401_reg_clr_bit(codec, HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		hi6401_reg_set_bit(codec, HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		msleep(5);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_clr_bit(codec, HI6401_ZC_EN, HI6401_LOL_ZCD_EN_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_lor_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_set_bit(codec, HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		hi6401_reg_set_bit(codec, HI6401_ZC_EN, HI6401_LOR_ZCD_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMU:
		hi6401_reg_clr_bit(codec, HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		hi6401_reg_set_bit(codec, HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT);
		msleep(5);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_clr_bit(codec, HI6401_ZC_EN, HI6401_LOR_ZCD_EN_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

/* IBIAS EVENT */
int hi6401_ibias_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_ibias_work_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_ibias_work_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_pll_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_pll_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_pll_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

/* INTERFACE CLK EVENT */
int hi6401_s1_rx_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_audio_rx_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_audio_rx_clk_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_s1_tx_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_audio_tx_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_audio_tx_clk_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_s1_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_audio_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_audio_clk_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_s2_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_clr_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S2_HZ_BIT);
		hi6401_reg_set_bit(codec, HI6401_IF_CLK_REG, HI6401_S2_IF_CLK_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_clr_bit(codec, HI6401_IF_CLK_REG, HI6401_S2_IF_CLK_EN_BIT);
		hi6401_reg_set_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S2_HZ_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_s3_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_voice_clk_enable(codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_voice_clk_enable(codec, false);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

int hi6401_s4_interface_clk_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	BUG_ON(NULL == codec);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6401_reg_clr_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S4_HZ_BIT);
		hi6401_reg_set_bit(codec, HI6401_IF_CLK_REG, HI6401_S4_IF_CLK_EN_BIT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6401_reg_clr_bit(codec, HI6401_IF_CLK_REG, HI6401_S4_IF_CLK_EN_BIT);
		hi6401_reg_set_bit(codec, HI6401_INTERFACE_HZ_CONFIG, HI6401_S4_HZ_BIT);
		break;
	default :
		pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

/* DAPM WIDGETS */
static const struct snd_soc_dapm_widget hi6401_dapm_widgets[] = {
	/* INPUT */
	SND_SOC_DAPM_INPUT("LINEINL"),
	SND_SOC_DAPM_INPUT("LINEINR"),
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),

	SND_SOC_DAPM_INPUT("ANALOG DACL"),
	SND_SOC_DAPM_INPUT("ANALOG DACR"),
	SND_SOC_DAPM_INPUT("ANALOG DACV"),

	SND_SOC_DAPM_INPUT("S1L IN"),
	SND_SOC_DAPM_INPUT("S1R IN"),
	SND_SOC_DAPM_INPUT("S2L IN"),
	SND_SOC_DAPM_INPUT("S2R IN"),
	SND_SOC_DAPM_INPUT("S3 IN"),
	SND_SOC_DAPM_INPUT("S4 IN"),
	SND_SOC_DAPM_INPUT("DIGMIC"),
	SND_SOC_DAPM_INPUT("DIGITAL ADCL"),
	SND_SOC_DAPM_INPUT("DIGITAL ADCR"),
	SND_SOC_DAPM_INPUT("AUDIO_IN"),
	SND_SOC_DAPM_OUTPUT("AUDIO_OUT"),

	/* OUTPUT */
	SND_SOC_DAPM_OUTPUT("OUT EAR"),
	SND_SOC_DAPM_OUTPUT("OUT HSL"),
	SND_SOC_DAPM_OUTPUT("OUT HSR"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L"),
	SND_SOC_DAPM_OUTPUT("LINEOUT R"),
	SND_SOC_DAPM_OUTPUT("ANALOG ADCL"),
	SND_SOC_DAPM_OUTPUT("ANALOG ADCR"),

	SND_SOC_DAPM_OUTPUT("S1L OUT"),
	SND_SOC_DAPM_OUTPUT("S1R OUT"),
	SND_SOC_DAPM_OUTPUT("S2L OUT"),
	SND_SOC_DAPM_OUTPUT("S2R OUT"),
	SND_SOC_DAPM_OUTPUT("S3L OUT"),
	SND_SOC_DAPM_OUTPUT("S3R OUT"),
	SND_SOC_DAPM_OUTPUT("S4L OUT"),
	SND_SOC_DAPM_OUTPUT("S4R OUT"),
	SND_SOC_DAPM_OUTPUT("DIGITAL DACL"),
	SND_SOC_DAPM_OUTPUT("DIGITAL DACR"),
	SND_SOC_DAPM_OUTPUT("DIGITAL DACV"),

	/* MICS */
	SND_SOC_DAPM_MIC("MAIN MIC", hi6401_main_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("SUB MIC", hi6401_sub_micbias_power_mode_event),
	SND_SOC_DAPM_MIC("HS MIC", hi6401_hs_micbias_power_mode_event),

	/* SUPPLY */
	SND_SOC_DAPM_SUPPLY("S1 TX CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s1_tx_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("S1 RX CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s1_rx_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("S1 INTERFACE CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s1_interface_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("S2 TX CLK",
		HI6401_S2_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY("S2 RX CLK",
		HI6401_S2_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY("S2 INTERFACE CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s2_interface_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("S3 INTERFACE CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s3_interface_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("S4 TX CLK",
		HI6401_S4_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY("S4 RX CLK",
		HI6401_S4_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_SUPPLY("S4 INTERFACE CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_s4_interface_clk_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("PLL CLK",
		SND_SOC_NOPM, 0, 0,
		hi6401_pll_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("IBIAS",
		SND_SOC_NOPM, 0, 0,
		hi6401_ibias_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* PGA */
	SND_SOC_DAPM_PGA("MAINMIC PGA",
		HI6401_MAINPGA_PD_REG, HI6401_MAINPGA_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("SUBMIC PGA",
		HI6401_AUXPGA_PD_REG, HI6401_AUXPGA_PD_BIT, 1,
		NULL, 0),

	SND_SOC_DAPM_PGA("SIDETONE PGA",
		HI6401_SIDEPGA_PD_REG, HI6401_SIDEPGA_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("LINEINL PGA",
		HI6401_LINEINLPGA_PD_REG, HI6401_LINEINLPGA_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("LINEINR PGA",
		HI6401_LINEINRPGA_PD_REG, HI6401_LINEINRPGA_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("DACL",
		HI6401_DACL_PD_REG, HI6401_DACL_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("DACR",
		HI6401_DACR_PD_REG, HI6401_DACR_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("DACV",
		HI6401_DACV_PD_REG, HI6401_DACV_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("ADC L",
		HI6401_ADCL_PD_REG, HI6401_ADCL_PD_BIT, 1,
		NULL, 0),
	SND_SOC_DAPM_PGA("ADC R",
		HI6401_ADCR_PD_REG, HI6401_ADCR_PD_BIT, 1,
		NULL, 0),

	SND_SOC_DAPM_PGA("DACL AGC",
		HI6401_DAC_AGC_CLK_REG, HI6401_DACL_AGC_CLK_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("DACR AGC",
		HI6401_DAC_AGC_CLK_REG, HI6401_DACR_AGC_CLK_EN_BIT, 0,
		NULL, 0),

	/* PGA FOR LR MIXER */
	SND_SOC_DAPM_PGA("S1 FIX PGA",
		SND_SOC_NOPM, 0, 0,
		NULL, 0),

	SND_SOC_DAPM_PGA("S1 IL PGA",
		HI6401_S1_MODULE_CLK_REG, HI6401_S1_PGA_IL_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S1 IR PGA",
		HI6401_S1_MODULE_CLK_REG, HI6401_S1_PGA_IR_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S2 IL PGA",
		HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_IL_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S2 IR PGA",
		HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_IR_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S2 OL PGA",
		HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_OL_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S2 OR PGA",
		HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_OR_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S3 I PGA",
		HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_I_EN_BIT, 0,
		NULL, 0),
	SND_SOC_DAPM_PGA("S4 I PGA",
		HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_I_EN_BIT, 0,
		NULL, 0),

	SND_SOC_DAPM_SWITCH_E("EARPIECE",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_earpiece_switch_controls,
		hi6401_ear_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("HEADSETL",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_hsl_switch_controls,
		hi6401_hsl_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("HEADSETR",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_hsr_switch_controls,
		hi6401_hsr_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("LINEOUTL",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_lol_switch_controls,
		hi6401_lol_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH_E("LINEOUTR",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_lor_switch_controls,
		hi6401_lor_power_mode_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

	/* MUX */
	SND_SOC_DAPM_MUX("MIC MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_mic_mux_controls),
	SND_SOC_DAPM_MUX("S3 CHN MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s3_chn_mux_controls),
	SND_SOC_DAPM_MUX("S4 CHN MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s4_chn_mux_controls),
	SND_SOC_DAPM_MUX("DACV MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_dacv_mux_controls),
	SND_SOC_DAPM_MUX("ADCL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_adcl_mux_controls),
	SND_SOC_DAPM_MUX("ADCR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_adcr_mux_controls),
	SND_SOC_DAPM_MUX("AGCL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_agcl_mux_controls),
	SND_SOC_DAPM_MUX("AGCR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_agcr_mux_controls),
	SND_SOC_DAPM_MUX("UPLINKL MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_uplinkl_mux_controls),
	SND_SOC_DAPM_MUX("UPLINKR MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_uplinkr_mux_controls),
	SND_SOC_DAPM_MUX("S4L MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s4l_mux_controls),
	SND_SOC_DAPM_MUX("S4R MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s4r_mux_controls),
	SND_SOC_DAPM_MUX("DIGMIC MUX",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_digmic_mux_controls),

	/* MIXERS */
	SND_SOC_DAPM_MIXER("EAR MIXER",
		HI6401_MIXOUT_EAR_PD_REG, HI6401_MIXOUT_EAR_PD_BIT, 1,
		hi6401_mixerout_ear_controls,
		ARRAY_SIZE(hi6401_mixerout_ear_controls)),
	SND_SOC_DAPM_MIXER("HEADSETL MIXER",
		SND_SOC_NOPM, 0, 0,
		hi6401_mixerout_hsl_controls,
		ARRAY_SIZE(hi6401_mixerout_hsl_controls)),
	SND_SOC_DAPM_MIXER("HEADSETR MIXER",
		SND_SOC_NOPM, 0, 0,
		hi6401_mixerout_hsr_controls,
		ARRAY_SIZE(hi6401_mixerout_hsr_controls)),
	SND_SOC_DAPM_MIXER("ADCL MIXER",
		HI6401_MIXINL_PD_REG, HI6401_MIXINL_PD_BIT, 1,
		hi6401_mixerin_left_controls,
		ARRAY_SIZE(hi6401_mixerin_left_controls)),
	SND_SOC_DAPM_MIXER("ADCR MIXER",
		HI6401_MIXINR_PD_REG, HI6401_MIXINR_PD_BIT, 1,
		hi6401_mixerin_right_controls,
		ARRAY_SIZE(hi6401_mixerin_right_controls)),
	SND_SOC_DAPM_MIXER("LINEOUTL MIXER",
		HI6401_MIXOUT_LINEOUTL_PD_REG, HI6401_MIXOUT_LINEOUTL_PD_BIT, 1,
		hi6401_mixerout_lineoutl_controls,
		ARRAY_SIZE(hi6401_mixerout_lineoutl_controls)),
	SND_SOC_DAPM_MIXER("LINEOUTR MIXER",
		HI6401_MIXOUT_LINEOUTR_PD_REG, HI6401_MIXOUT_LINEOUTR_PD_BIT, 1,
		hi6401_mixerout_lineoutr_controls,
		ARRAY_SIZE(hi6401_mixerout_lineoutr_controls)),

	SND_SOC_DAPM_MIXER("S2L MIXER",
		HI6401_MIXER_CLK_REG, HI6401_S2_L_MIXER_EN_BIT, 0,
		hi6401_mixer_s2l_controls,
		ARRAY_SIZE(hi6401_mixer_s2l_controls)),
	SND_SOC_DAPM_MIXER("S2R MIXER",
		HI6401_MIXER_CLK_REG, HI6401_S2_R_MIXER_EN_BIT, 0,
		hi6401_mixer_s2r_controls,
		ARRAY_SIZE(hi6401_mixer_s2r_controls)),
	SND_SOC_DAPM_MIXER("S4L MIXER",
		HI6401_MIXER_CLK_REG, HI6401_S4_L_MIXER_EN_BIT, 0,
		hi6401_mixer_s4l_controls,
		ARRAY_SIZE(hi6401_mixer_s4l_controls)),
	SND_SOC_DAPM_MIXER("S4R MIXER",
		HI6401_MIXER_CLK_REG, HI6401_S4_R_MIXER_EN_BIT, 0,
		hi6401_mixer_s4r_controls,
		ARRAY_SIZE(hi6401_mixer_s4r_controls)),
	SND_SOC_DAPM_MIXER("DACL MIXER",
		HI6401_MIXER_CLK_REG, HI6401_DACL_MIXER_EN_BIT, 0,
		hi6401_mixer_dacl_controls,
		ARRAY_SIZE(hi6401_mixer_dacl_controls)),
	SND_SOC_DAPM_MIXER("DACR MIXER",
		HI6401_MIXER_CLK_REG, HI6401_DACR_MIXER_EN_BIT, 0,
		hi6401_mixer_dacr_controls,
		ARRAY_SIZE(hi6401_mixer_dacr_controls)),

	/* SWITCH */
	SND_SOC_DAPM_SWITCH("S1 OUT L",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s1_outl_switch_controls),
	SND_SOC_DAPM_SWITCH("S1 OUT R",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_s1_outr_switch_controls),
	SND_SOC_DAPM_SWITCH("S3 OUT L",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_S3_outl_switch_controls),
	SND_SOC_DAPM_SWITCH("S3 OUT R",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_S3_outr_switch_controls),
	SND_SOC_DAPM_SWITCH("S4 OUT L",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_S4_outl_switch_controls),
	SND_SOC_DAPM_SWITCH("S4 OUT R",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_S4_outr_switch_controls),

	SND_SOC_DAPM_SWITCH("DACL FILTER",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_dacl_filter_switch_controls),
	SND_SOC_DAPM_SWITCH("DACR FILTER",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_dacr_filter_switch_controls),
	SND_SOC_DAPM_SWITCH("DACV FILTER",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_dacv_filter_switch_controls),
	SND_SOC_DAPM_SWITCH("ADCL FILTER",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_adcl_filter_switch_controls),
	SND_SOC_DAPM_SWITCH("ADCR FILTER",
		SND_SOC_NOPM, 0, 0,
		&hi6401_dapm_adcr_filter_switch_controls),
};

static const struct snd_soc_dapm_route route_map[] = {
	{"S1 IL PGA",		NULL,			"S1L IN"},
	{"S1 IR PGA",		NULL,			"S1R IN"},
	{"S2 IL PGA",		NULL,			"S2L IN"},
	{"S2 IR PGA",		NULL,			"S2R IN"},
	{"S3 I PGA",		NULL,			"S3 CHN MUX"},
	{"S4 I PGA",		NULL,			"S4 CHN MUX"},

	{"S1 FIX PGA",		NULL,			"S1 IL PGA"},
	{"S1 FIX PGA",		NULL,			"S1 IR PGA"},

	{"S1L OUT",		NULL,			"S1 OUT L"},
	{"S1R OUT",		NULL,			"S1 OUT R"},
	{"S2L OUT",		NULL,			"S2 OL PGA"},
	{"S2R OUT",		NULL,			"S2 OR PGA"},
	{"S3L OUT",		NULL,			"S3 OUT L"},
	{"S3R OUT",		NULL,			"S3 OUT R"},
	{"S4L OUT",		NULL,			"S4 OUT L"},
	{"S4R OUT",		NULL,			"S4 OUT R"},

	{"S1 OUT L",		"SWITCH",		"AGCL MUX"},
	{"S1 OUT R",		"SWITCH",		"AGCR MUX"},
	{"S2 OL PGA",		"SWITCH",		"S2L MIXER"},
	{"S2 OR PGA",		"SWITCH",		"S2R MIXER"},
	{"S3 OUT L",		"SWITCH",		"UPLINKL MUX"},
	{"S3 OUT R",		"SWITCH",		"UPLINKR MUX"},
	{"S4 OUT L",		"SWITCH",		"S4L MUX"},
	{"S4 OUT R",		"SWITCH",		"S4R MUX"},

	{"DACL AGC",		NULL,			"DACL MIXER"},
	{"DACR AGC",		NULL,			"DACR MIXER"},

	{"DACL FILTER",		"SWITCH",		"DACL AGC"},
	{"DACR FILTER",		"SWITCH",		"DACR AGC"},
	{"DACV FILTER",		"SWITCH",		"DACV MUX"},
	{"ADCL FILTER",		"SWITCH",		"ADCL MUX"},
	{"ADCR FILTER",		"SWITCH",		"ADCR MUX"},

	{"DIGITAL DACL",	NULL,			"DACL FILTER"},
	{"DIGITAL DACR",	NULL,			"DACR FILTER"},
	{"DIGITAL DACV",	NULL,			"DACV FILTER"},

	/*MUX*/
	{"S3 CHN MUX",		"LEFT",			"S3 IN"},
	{"S3 CHN MUX",		"RIGHT",		"S3 IN"},
	{"S4 CHN MUX",		"LEFT",			"S4 IN"},
	{"S4 CHN MUX",		"RIGHT",		"S4 IN"},

	{"DIGMIC MUX",		"OFF",			"DIGMIC"},
	{"DIGMIC MUX",		"2FD",			"DIGMIC"},
	{"DIGMIC MUX",		"3FD",			"DIGMIC"},
	{"DIGMIC MUX",		"4FD",			"DIGMIC"},

	{"AGCL MUX",		"ADCL",			"ADCL FILTER"},
	{"AGCL MUX",		"ADCR",			"ADCR FILTER"},
	{"AGCL MUX",		"S2L",			"S2 IL PGA"},
	{"AGCL MUX",		"S2R",			"S2 IR PGA"},
	{"AGCL MUX",		"S3MODEM",		"S3 I PGA"},
	{"AGCL MUX",		"S4MODEM",		"S4 I PGA"},

	{"AGCR MUX",		"ADCL",			"ADCL FILTER"},
	{"AGCR MUX",		"ADCR",			"ADCR FILTER"},
	{"AGCR MUX",		"S2L",			"S2 IL PGA"},
	{"AGCR MUX",		"S2R",			"S2 IR PGA"},
	{"AGCR MUX",		"S3MODEM",		"S3 I PGA"},
	{"AGCR MUX",		"S4MODEM",		"S4 I PGA"},

	{"DACV MUX",		"S3MODEM",		"S3 I PGA"},
	{"DACV MUX",		"S4MODEM",		"S4 I PGA"},
	{"UPLINKL MUX",		"S1L",			"S1 IL PGA"},
	{"UPLINKL MUX",		"S1LR",			"S1 FIX PGA"},
	{"UPLINKL MUX",		"S2L",			"S2 IL PGA"},
	{"UPLINKL MUX",		"DACL",			"DACL AGC"},
	{"UPLINKL MUX",		"ADCL",			"ADCL FILTER"},
	{"UPLINKL MUX",		"S4MODEM",		"S4 I PGA"},

	{"UPLINKR MUX",		"S1R",			"S1 IR PGA"},
	{"UPLINKR MUX",		"S1LR",			"S1 FIX PGA"},
	{"UPLINKR MUX",		"S2R",			"S2 IR PGA"},
	{"UPLINKR MUX",		"DACR",			"DACR AGC"},
	{"UPLINKR MUX",		"ADCR",			"ADCR FILTER"},
	{"UPLINKR MUX",		"S4MODEM",		"S4 I PGA"},

	{"S4L MUX",		"UPLINKL",		"UPLINKL MUX"},
	{"S4L MUX",		"S4MIXERL",		"S4L MIXER"},
	{"S4L MUX",		"S4MIXERLR",		"S4L MIXER"},
	{"S4L MUX",		"S4MIXERLR",		"S4R MIXER"},

	{"S4R MUX",		"UPLINKR",		"UPLINKR MUX"},
	{"S4R MUX",		"S4MIXERR",		"S4R MIXER"},
	{"S4R MUX",		"S4MIXERLR",		"S4L MIXER"},
	{"S4R MUX",		"S4MIXERLR",		"S4R MIXER"},

	{"ADCL MUX",		"ADC",			"DIGITAL ADCL"},
	{"ADCL MUX",		"DACL",			"DIGITAL DACL"},
	{"ADCL MUX",		"DACR",			"DIGITAL DACR"},
	{"ADCL MUX",		"DACV",			"DIGITAL DACV"},
	{"ADCL MUX",		"DMIC",			"DIGMIC MUX"},

	{"ADCR MUX",		"ADC",			"DIGITAL ADCR"},
	{"ADCR MUX",		"DACL",			"DIGITAL DACL"},
	{"ADCR MUX",		"DACR",			"DIGITAL DACR"},
	{"ADCR MUX",		"DACV",			"DIGITAL DACV"},
	{"ADCR MUX",		"DMIC",			"DIGMIC MUX"},

	/*MIXER*/
	{"S2L MIXER",		"DACL SWITCH",		"DACL AGC"},
	{"S2L MIXER",		"ADCL SWITCH",		"ADCL FILTER"},
	{"S2L MIXER",		"DACV SWITCH",		"DACV MUX"},
	{"S2L MIXER",		"S1LR SWITCH",		"S1 FIX PGA"},

	{"S2R MIXER",		"DACR SWITCH",		"DACR AGC"},
	{"S2R MIXER",		"ADCR SWITCH",		"ADCR FILTER"},
	{"S2R MIXER",		"DACV SWITCH",		"DACV MUX"},
	{"S2R MIXER",		"S1LR SWITCH",		"S1 FIX PGA"},

	{"S4L MIXER",		"DACL SWITCH",		"DACL AGC"},
	{"S4L MIXER",		"ADCL SWITCH",		"ADCL FILTER"},
	{"S4L MIXER",		"DACV SWITCH",		"DACV MUX"},
	{"S4L MIXER",		"S1LR SWITCH",		"S1 FIX PGA"},

	{"S4R MIXER",		"DACR SWITCH",		"DACR AGC"},
	{"S4R MIXER",		"ADCR SWITCH",		"ADCR FILTER"},
	{"S4R MIXER",		"DACV SWITCH",		"DACV MUX"},
	{"S4R MIXER",		"S1LR SWITCH",		"S1 FIX PGA"},

	{"DACL MIXER",		"S1L SWITCH",		"S1 IL PGA"},
	{"DACL MIXER",		"S2L SWITCH",		"S2 IL PGA"},

	{"DACR MIXER",		"S1R SWITCH",		"S1 IR PGA"},
	{"DACR MIXER",		"S2R SWITCH",		"S2 IR PGA"},

	/* CLOCK SUPPLY */
	{"S1L IN",		NULL,			"S1 RX CLK"},
	{"S1R IN",		NULL,			"S1 RX CLK"},
	{"S1L OUT",		NULL,			"S1 TX CLK"},
	{"S1R OUT",		NULL,			"S1 TX CLK"},
	{"S1 TX CLK",		NULL,			"S1 INTERFACE CLK"},
	{"S1 RX CLK",		NULL,			"S1 INTERFACE CLK"},

	{"S2L IN",		NULL,			"S2 RX CLK"},
	{"S2R IN",		NULL,			"S2 RX CLK"},
	{"S2L OUT",		NULL,			"S2 TX CLK"},
	{"S2R OUT",		NULL,			"S2 TX CLK"},
	{"S2 TX CLK",		NULL,			"S2 INTERFACE CLK"},
	{"S2 RX CLK",		NULL,			"S2 INTERFACE CLK"},

	{"S3 IN",		NULL,			"S3 INTERFACE CLK"},
	{"S3L OUT",		NULL,			"S3 INTERFACE CLK"},
	{"S3R OUT",		NULL,			"S3 INTERFACE CLK"},

	{"S4 IN",		NULL,			"S4 RX CLK"},
	{"S4L OUT",		NULL,			"S4 TX CLK"},
	{"S4R OUT",		NULL,			"S4 TX CLK"},
	{"S4 TX CLK",		NULL,			"S4 INTERFACE CLK"},
	{"S4 RX CLK",		NULL,			"S4 INTERFACE CLK"},

	{"S1 INTERFACE CLK",	NULL,			"PLL CLK"},
	{"S2 INTERFACE CLK",	NULL,			"PLL CLK"},
	{"S3 INTERFACE CLK",	NULL,			"PLL CLK"},
	{"S4 INTERFACE CLK",	NULL,			"PLL CLK"},
	{"PLL CLK",		NULL,			"IBIAS"},

	/*ADC*/
	{"ANALOG ADCL",		NULL,			"ADC L"},
	{"ANALOG ADCR",		NULL,			"ADC R"},

	/* DAC */
	{"DACL",		NULL,			"ANALOG DACL"},
	{"DACR",		NULL,			"ANALOG DACR"},
	{"DACV",		NULL,			"ANALOG DACV"},

	{"LINEINL PGA",		NULL,			"LINEINL"},
	{"LINEINR PGA",		NULL,			"LINEINR"},

	/* MIXER */
	{"EAR MIXER",		"DACL SWITCH",		"DACL"},
	{"EAR MIXER",		"DACR SWITCH",		"DACR"},
	{"EAR MIXER",		"DACV SWITCH",		"DACV"},
	{"EAR MIXER",		"LIL SWITCH",		"LINEINL PGA"},
	{"EAR MIXER",		"LIR SWITCH",		"LINEINR PGA"},
	{"EAR MIXER",		"SIDETONE SWITCH",	"SIDETONE PGA"},

	{"HEADSETL MIXER",	"DACL SWITCH",		"DACL"},
	{"HEADSETL MIXER",	"DACR SWITCH",		"DACR"},
	{"HEADSETL MIXER",	"DACV SWITCH",		"DACV"},
	{"HEADSETL MIXER",	"LIL SWITCH",		"LINEINL PGA"},
	{"HEADSETL MIXER",	"LIR SWITCH",		"LINEINR PGA"},
	{"HEADSETL MIXER",	"SIDETONE SWITCH",	"SIDETONE PGA"},

	{"HEADSETR MIXER",	"DACL SWITCH",		"DACL"},
	{"HEADSETR MIXER",	"DACR SWITCH",		"DACR"},
	{"HEADSETR MIXER",	"DACV SWITCH",		"DACV"},
	{"HEADSETR MIXER",	"LIL SWITCH",		"LINEINL PGA"},
	{"HEADSETR MIXER",	"LIR SWITCH",		"LINEINR PGA"},
	{"HEADSETR MIXER",	"SIDETONE SWITCH",	"SIDETONE PGA"},

	{"LINEOUTL MIXER",	"DACL SWITCH",		"DACL"},
	{"LINEOUTL MIXER",	"DACR SWITCH",		"DACR"},
	{"LINEOUTL MIXER",	"DACV SWITCH",		"DACV"},
	{"LINEOUTL MIXER",	"LIL SWITCH",		"LINEINL PGA"},
	{"LINEOUTL MIXER",	"LIR SWITCH",		"LINEINR PGA"},
	{"LINEOUTL MIXER",	"SIDETONE SWITCH",	"SIDETONE PGA"},

	{"LINEOUTR MIXER",	"DACL SWITCH",		"DACL"},
	{"LINEOUTR MIXER",	"DACR SWITCH",		"DACR"},
	{"LINEOUTR MIXER",	"DACV SWITCH",		"DACV"},
	{"LINEOUTR MIXER",	"LIL SWITCH",		"LINEINL PGA"},
	{"LINEOUTR MIXER",	"LIR SWITCH",		"LINEINR PGA"},
	{"LINEOUTR MIXER",	"SIDETONE SWITCH",	"SIDETONE PGA"},

	{"ADCL MIXER",		"DACL SWITCH",		"DACL"},
	{"ADCL MIXER",		"DACR SWITCH",		"DACR"},
	{"ADCL MIXER",		"DACV SWITCH",		"DACV"},
	{"ADCL MIXER",		"LIL SWITCH",		"LINEINL PGA"},
	{"ADCL MIXER",		"LIR SWITCH",		"LINEINR PGA"},
	{"ADCL MIXER",		"MAINMIC SWITCH",	"MAINMIC PGA"},
	{"ADCL MIXER",		"SUBMIC SWITCH",	"SUBMIC PGA"},

	{"ADCR MIXER",		"DACL SWITCH",		"DACL"},
	{"ADCR MIXER",		"DACR SWITCH",		"DACR"},
	{"ADCR MIXER",		"DACV SWITCH",		"DACV"},
	{"ADCR MIXER",		"LIL SWITCH",		"LINEINL PGA"},
	{"ADCR MIXER",		"LIR SWITCH",		"LINEINR PGA"},
	{"ADCR MIXER",		"MAINMIC SWITCH",	"MAINMIC PGA"},
	{"ADCR MIXER",		"SUBMIC SWITCH",	"SUBMIC PGA"},

	/* MICS */
	{"MAINMIC",		NULL,			"MAIN MIC"},
	{"SUBMIC",		NULL,			"SUB MIC"},
	{"HSMIC",		NULL,			"HS MIC"},

	/* MUX */
	{"MIC MUX",		"MIC MAIN",		"MAINMIC"},
	{"MIC MUX",		"MIC HS",		"HSMIC"},

	{"MAINMIC PGA",		NULL,			"MIC MUX"},
	{"SUBMIC PGA",		NULL,			"SUBMIC"},
	{"SIDETONE PGA",	NULL,			"MAINMIC PGA"},

	/* OUTPUT */
	{"OUT EAR",		NULL,			"EAR MIXER"},
	{"OUT HSL",		NULL,			"HEADSETL MIXER"},
	{"OUT HSR",		NULL,			"HEADSETR MIXER"},
	{"LINEOUT L",		NULL,			"LINEOUTL MIXER"},
	{"LINEOUT R",		NULL,			"LINEOUTR MIXER"},
	{"ADC L",		NULL,			"ADCL MIXER"},
	{"ADC R",		NULL,			"ADCR MIXER"},

	{"EARPIECE",		"SWITCH",		"AUDIO_IN"},
	{"HEADSETL",		"SWITCH",		"AUDIO_IN"},
	{"HEADSETR",		"SWITCH",		"AUDIO_IN"},
	{"LINEOUTL",		"SWITCH",		"AUDIO_IN"},
	{"LINEOUTR",		"SWITCH",		"AUDIO_IN"},
	{"AUDIO_OUT",		NULL,			"EARPIECE"},
	{"AUDIO_OUT",		NULL,			"HEADSETL"},
	{"AUDIO_OUT",		NULL,			"HEADSETR"},
	{"AUDIO_OUT",		NULL,			"LINEOUTL"},
	{"AUDIO_OUT",		NULL,			"LINEOUTR"},

	/* IBIAS SUPPLY */
	{"EAR MIXER",		NULL,			"IBIAS"},
	{"HEADSETL MIXER",	NULL,			"IBIAS"},
	{"HEADSETR MIXER",	NULL,			"IBIAS"},
	{"ADCL MIXER",		NULL,			"IBIAS"},
	{"ADCR MIXER",		NULL,			"IBIAS"},
	{"LINEOUTL MIXER",	NULL,			"IBIAS"},
	{"LINEOUTR MIXER",	NULL,			"IBIAS"},
};


#define HI6401_FORMATS	( SNDRV_PCM_FMTBIT_S16_LE | \
			  SNDRV_PCM_FMTBIT_S16_BE | \
			  SNDRV_PCM_FMTBIT_S24_LE | \
			  SNDRV_PCM_FMTBIT_S24_BE )

#define HI6401_RATES	SNDRV_PCM_RATE_8000_96000

#define FS_8000		0x0
#define FS_16000	0x1
#define FS_32000	0x2
#define FS_48000	0x4
#define FS_96000	0x5

#define SRC_8000	0x1
#define SRC_16000	0x2

static int hi6401_audio_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;

	BUG_ON(NULL == codec);

	hi6401_pll_enable(codec, true);
	hi6401_audio_clk_enable(codec, true);

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
		hi6401_audio_rx_clk_enable(codec, true);
	else
		hi6401_audio_tx_clk_enable(codec, true);

	return 0;
}

static void hi6401_audio_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;

	BUG_ON(NULL == codec);

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		hi6401_audio_rx_clk_enable(codec, false);
	} else {
		hi6401_audio_tx_clk_enable(codec, false);
		hi6401_reg_clr_bit(codec, HI6401_S1_MODULE_CLK_REG, HI6401_S1_SRC_OL_EN_BIT);
		hi6401_reg_clr_bit(codec, HI6401_S1_MODULE_CLK_REG, HI6401_S1_SRC_OR_EN_BIT);
	}

	hi6401_audio_clk_enable(codec, false);
	hi6401_pll_enable(codec, false);
}

static int hi6401_audio_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	int rate = 0;
	int ret = 0;

	rate = params_rate(params);
	switch (rate) {
	case 8000:
	case 11250:
	case 16000:
	case 22500:
	case 32000:
	case 44100:
	case 48000:
		hi6401_reg_write_bits(codec, HI6401_FS_S1_S2_REG, FS_48000, 0xF);
		if (SNDRV_PCM_STREAM_CAPTURE == substream->stream) {
			hi6401_reg_set_bit(codec, HI6401_S1_MODULE_CLK_REG, HI6401_S1_SRC_OL_EN_BIT);
			hi6401_reg_set_bit(codec, HI6401_S1_MODULE_CLK_REG, HI6401_S1_SRC_OR_EN_BIT);
		}
		break;
	case 88200:
	case 96000:
		hi6401_reg_write_bits(codec, HI6401_FS_S1_S2_REG, FS_96000, 0xF);
		break;
	default:
		pr_err("unknown rate : %d", rate);
		ret = -1;
		break;
	}

	return ret;
}

struct snd_soc_dai_ops hi6401_audio_dai_ops = {
	.startup   = hi6401_audio_startup,
	.shutdown  = hi6401_audio_shutdown,
	.hw_params = hi6401_audio_hw_params,
};

static int hi6401_voice_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;

	BUG_ON(NULL == codec);

	hi6401_pll_enable(codec, true);
	hi6401_voice_clk_enable(codec, true);

	return 0;
}

static void hi6401_voice_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;

	BUG_ON(NULL == codec);

	hi6401_voice_clk_enable(codec, false);
	hi6401_pll_enable(codec, false);
	hi6401_reg_clr_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OL_EN_BIT);
	hi6401_reg_clr_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OR_EN_BIT);
}

static int hi6401_voice_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	int rate = 0;
	int ret = 0;

	rate = params_rate(params);
	switch (rate) {
	case 8000:
		hi6401_reg_write_bits(codec, HI6401_FS_S3_S4_REG, FS_8000, 0xF);
		hi6401_reg_write_bits(codec, HI6401_FS_DAC_REG, FS_8000, 0x7);
		hi6401_reg_write_bits(codec, HI6401_SRC_MODE, SRC_8000 << 2, 0xC);
		hi6401_reg_set_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OL_EN_BIT);
		hi6401_reg_set_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OR_EN_BIT);
		break;
	case 16000:
		hi6401_reg_write_bits(codec, HI6401_FS_S3_S4_REG, FS_16000, 0xF);
		hi6401_reg_write_bits(codec, HI6401_FS_DAC_REG, FS_16000, 0x7);
		hi6401_reg_write_bits(codec, HI6401_SRC_MODE, SRC_16000 << 2, 0xC);
		hi6401_reg_set_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OL_EN_BIT);
		hi6401_reg_set_bit(codec, HI6401_S3_MODULE_CLK_REG, HI6401_S3_SRC_OR_EN_BIT);
		break;
	default:
		pr_err("unknown rate : %d", rate);
		ret = -1;
		break;
	}

	return ret;
}

struct snd_soc_dai_ops hi6401_voice_dai_ops = {
	.startup   = hi6401_voice_startup,
	.shutdown  = hi6401_voice_shutdown,
	.hw_params = hi6401_voice_hw_params,
};

struct snd_soc_dai_driver hi6401_dai[] = {
	{
		.name = "hi6401-audio-dai",
		.playback = {
			.stream_name	= "Playback",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= HI6401_RATES,
			.formats	= HI6401_FORMATS},
		.capture = {
			.stream_name	= "Capture",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= HI6401_RATES,
			.formats	= HI6401_FORMATS},
		.ops = &hi6401_audio_dai_ops,
	},
	{
		.name = "hi6401-voice-dai",
		.playback = {
			.stream_name	= "Downlink",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= HI6401_RATES,
			.formats	= HI6401_FORMATS},
		.capture = {
			.stream_name	= "Uplink",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= HI6401_RATES,
			.formats	= HI6401_FORMATS},
		.ops = &hi6401_voice_dai_ops,
	},
	{
		.name = "hi6401-fm-dai",
		.playback = {
			.stream_name	= "FM",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= HI6401_RATES,
			.formats	= HI6401_FORMATS},
	},
};

static void hi6401_set_vref(struct snd_soc_codec *codec, enum vref_mode mode)
{
	int value = 0;
	unsigned long flags = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == codec);

	spin_lock_irqsave(&priv->lock, flags);
	value = hi6401_reg_read(codec, HI6401_VREF_IBIAS_PD);
	value &= ~(3 << HI6401_VREF_SEL_BIT);
	value |= (mode << HI6401_VREF_SEL_BIT);
	hi6401_reg_write(codec, HI6401_VREF_IBIAS_PD, value);
	spin_unlock_irqrestore(&priv->lock, flags);
	hi6401_reg_clr_bit(codec, HI6401_VREF_IBIAS_PD, HI6401_VREF_MUX_BIT);
	hi6401_reg_set_bit(codec, HI6401_VREF_IBIAS_PD, HI6401_BG_PD_BIT);

}

static void hi6401_enable_ibias(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);
	int ret = 0;

	BUG_ON(NULL == priv);

	if (enable) {
		if (!priv->ibias_saradc && (0 == priv->ibias_work)) {
			/* enable ldo8 */
#if 0
			ret = regulator_bulk_enable(1, &priv->regu);
			if (0 != ret) {
				pr_err("%s : couldn't enable regulators %d\n",
						__FUNCTION__, ret);
				return;
			}
#endif
			hi6401_reg_clr_bit(codec, HI6401_VREF_IBIAS_PD, HI6401_IBIAS_PD_BIT);
			hi6401_set_vref(codec, VREF_QUICK_PU);
			msleep(30);
			hi6401_set_vref(codec, VREF_NORMAL);
		}
	} else {
		if (!priv->ibias_saradc && (0 == priv->ibias_work)) {
			hi6401_set_vref(codec, VREF_PD);
			hi6401_reg_set_bit(codec, HI6401_VREF_IBIAS_PD, HI6401_IBIAS_PD_BIT);
#if 0
			regulator_bulk_disable(1, &priv->regu);
#endif
		}
	}
}

static void hi6401_ibias_work_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->ibias_mutex);
	if (enable) {
		if (0 == priv->ibias_work)
			hi6401_enable_ibias(codec, true);
		++priv->ibias_work;
	} else {
		--priv->ibias_work;
		if (0 == priv->ibias_work)
			hi6401_enable_ibias(codec, false);
	}
	mutex_unlock(&priv->ibias_mutex);
}

static void hi6401_ibias_saradc_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->ibias_mutex);
	if (enable) {
		if (!priv->ibias_saradc) {
			hi6401_enable_ibias(codec, true);
			priv->ibias_saradc = true;
		}
	} else {
		if (priv->ibias_saradc) {
			priv->ibias_saradc = false;
			hi6401_enable_ibias(codec, false);
		}
	}
	mutex_unlock(&priv->ibias_mutex);
}

static inline bool check_headset_pluged_in(struct snd_soc_codec *codec)
{
	/*
	 * read codec status, HI6401_HS_DET_BIT
	 * 0 : means headset is pluged out
	 * 1 : means headset is pluged in
	 */
	return (0 != (hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STATE) & (1 << HI6401_HS_DET_BIT)));
}

static void anc_dsm_report(struct anc_hs_data *p_anc_hs, int anc_errno, int sys_errno)
{
#ifdef CONFIG_HUAWEI_DSM
	struct hi6401_priv *priv = container_of(p_anc_hs,
						struct hi6401_priv,
						p_anc_hs);

	if(!dsm_client_ocuppy(anc_hs_dclient)){
		dsm_client_record(anc_hs_dclient,
			"mode:%d,irq:%d,boost:%d,sleep_time:%d,mic_used:%d,pressed:%d,switch:%d,errno\n",
		p_anc_hs->anc_hs_mode,
		p_anc_hs->irq_flag,
		p_anc_hs->boost_flag,
		p_anc_hs->sleep_time,
		p_anc_hs->mic_used,
		priv->button_pressed,
		gpio_get_value(p_anc_hs->gpio_mic_sw),
		sys_errno);
		dsm_client_notify(anc_hs_dclient, anc_errno);
	}
#endif
}

static inline void anc_hs_enable_irq(struct anc_hs_data *p_anc_hs)
{
	unsigned long flags;

	spin_lock_irqsave(&p_anc_hs->irq_lock, flags);
	if(!p_anc_hs->irq_flag){
		enable_irq(p_anc_hs->mic_irq);
		p_anc_hs->irq_flag = true;
	}
	spin_unlock_irqrestore(&p_anc_hs->irq_lock, flags);
}

static inline void anc_hs_disable_irq(struct anc_hs_data *p_anc_hs)
{
	unsigned long flags;

	spin_lock_irqsave(&p_anc_hs->irq_lock, flags);
	if(p_anc_hs->irq_flag){
		disable_irq_nosync(p_anc_hs->mic_irq);
		p_anc_hs->irq_flag = false;
	}
	spin_unlock_irqrestore(&p_anc_hs->irq_lock, flags);
}

/*
 * IRQ & IRQMASK
 * HI6401_ANA_IRQM_0 for irq 0~7;
 * HI6401_ANA_IRQM_1 for irq 8~15(reserved);
 */
static inline void hi6401_clr_irq(struct snd_soc_codec *codec, int offset)
{
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQ_0, offset);
}

static inline void hi6401_mask_irq(struct snd_soc_codec *codec, int offset)
{
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQM_0, offset);
}

static inline void hi6401_unmask_irq(struct snd_soc_codec *codec, int offset)
{
	hi6401_reg_clr_bit(codec, HI6401_ANA_IRQM_0, offset);
}

static inline void hi6401_clr_btn_irqs(struct snd_soc_codec *codec)
{
	hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0xF);
}

static inline void hi6401_mask_btn_irqs(struct snd_soc_codec *codec)
{
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQM_0, HI6401_IRQ_BTNDOWN);
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQM_0, HI6401_IRQ_BTNUP);
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQM_0, HI6401_IRQ_BTNDOWN_ECO);
	hi6401_reg_set_bit(codec, HI6401_ANA_IRQM_0, HI6401_IRQ_BTNUP_ECO);
}

static inline void hi6401_unmask_btn_irqs(struct snd_soc_codec *codec)
{
	hi6401_reg_write_bits(codec, HI6401_ANA_IRQM_0, 0x0, 0xF);
}

static inline void hi6401_mbhd_comp3_enable(struct snd_soc_codec *codec, bool enable)
{
	if (enable)
		hi6401_reg_clr_bit(codec, HI6401_MBHD_VREF_CTRL, HI6401_MBHD_VREF_CTRL_EN_BIT);
	else
		hi6401_reg_set_bit(codec, HI6401_MBHD_VREF_CTRL, HI6401_MBHD_VREF_CTRL_EN_BIT);
}

static inline void hi6401_hs_eco_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);

	BUG_ON(NULL == priv);

	if (HI6401_JACK_HEADSET == priv->hs_status || HI6401_JACK_INVERT == priv->hs_status) {
		if (enable) {
			pr_info("%s: enter eco mode\n", __FUNCTION__);
			hi6401_reg_set_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_MBHD_ECO_EN_BIT);
			msleep(20);
			hi6401_clr_btn_irqs(codec);
			hi6401_unmask_irq(codec, HI6401_IRQ_BTNDOWN_ECO);
			hi6401_unmask_irq(codec, HI6401_IRQ_BTNUP_ECO);
		} else {
			pr_info("%s: exit eco mode\n", __FUNCTION__);
			hi6401_reg_clr_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_MBHD_ECO_EN_BIT);
			hi6401_clr_btn_irqs(codec);
			hi6401_unmask_irq(codec, HI6401_IRQ_BTNDOWN);
			hi6401_unmask_irq(codec, HI6401_IRQ_BTNUP);
		}
	}
}

static void hi6401_hs_micbias_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);
	bool first = 0;
	bool secend = 0;

	BUG_ON(NULL == priv);

	if ((0 == priv->hs_micbias_work) && !priv->hs_micbias_saradc) {
		hi6401_mask_btn_irqs(codec);
		if (enable) {
			first = (0 == (hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STATE) & (1 << HI6401_HS_BTN_ECO_BIT)));
			hi6401_ibias_saradc_enable(codec, true);
			hi6401_reg_clr_bit(codec, HI6401_HSMICBIAS_PD_REG, HI6401_HSMICBIAS_PD_BIT);
			msleep(6);
			hi6401_clr_btn_irqs(codec);
			hi6401_hs_eco_enable(codec, false);
			secend = (0 == (hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STATE) & (1 << HI6401_HS_BTN_BIT)));
			if (!priv->need_report_up_event)
				priv->need_report_up_event = (first && !secend);
		} else {
			first = (0 == (hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STATE) & (1 << HI6401_HS_BTN_BIT)));
			hi6401_reg_set_bit(codec, HI6401_HSMICBIAS_PD_REG, HI6401_HSMICBIAS_PD_BIT);
			hi6401_reg_set_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_HSMICB_DSCHG_BIT);
			msleep(15);
			hi6401_reg_clr_bit(codec, HI6401_MICBIAS_ECO_EN, HI6401_HSMICB_DSCHG_BIT);
			hi6401_clr_btn_irqs(codec);
			hi6401_hs_eco_enable(codec, true);
			hi6401_ibias_saradc_enable(codec, false);
			secend = (0 == (hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STATE) & (1 << HI6401_HS_BTN_ECO_BIT)));
			if (!priv->need_report_up_event)
				priv->need_report_up_event = (first && !secend);
		}
	}
}

static void anc_hs_charging_control(struct hi6401_priv *priv)
{
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	int ret;

	if(!priv->anc_hs_enable)
		return ;

	if (1 == priv->hs_micbias_work ) {
		mutex_lock(&p_anc_hs->charge_lock);
		if(p_anc_hs->anc_hs_mode == ANC_HS_CHARGE_ON) {
			gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
			anc_hs_disable_irq(p_anc_hs);
			flush_work(&p_anc_hs->anc_hs_btn_delay_work.work);

			pr_info("%s(%u) : stop charging for anc hs !\n", __FUNCTION__, __LINE__);
			p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
			p_anc_hs->mic_used = true;
		}else if(p_anc_hs->anc_hs_mode == ANC_HS_CHARGE_SWITCHING) {
			pr_info("%s(%u) : stop anc charge switching charging !\n", __FUNCTION__, __LINE__);
			p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
			p_anc_hs->mic_used = true;
			gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
		}else {
			if(gpio_get_value(p_anc_hs->gpio_mic_sw) == SWITCH_CHIP_5VBOOST){
				pr_err("%s(%u) : gpio status is not right !\n", __FUNCTION__, __LINE__);
#ifdef CONFIG_HUAWEI_DSM
				anc_dsm_report(p_anc_hs, ANC_HS_MIC_WITH_GPIO_ERR, 0);
#endif
			}
		}
		anc_hs_dump(p_anc_hs);
		mutex_unlock(&p_anc_hs->charge_lock);
	}else if (0 == priv->hs_micbias_work){
		mutex_lock(&p_anc_hs->charge_lock);
		if(p_anc_hs->mic_used) {
			p_anc_hs->mic_used = false;
			if (!check_headset_pluged_in(priv->codec)) {
				pr_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
				anc_hs_dump(p_anc_hs);
			}else {
				ret = queue_delayed_work(p_anc_hs->anc_hs_charge_delay_wq,
						&p_anc_hs->anc_hs_charge_delay_work,
						0);
				if(!ret) {
					pr_info("%s(%u) : queue work failed\n", __FUNCTION__, __LINE__);
#ifdef CONFIG_HUAWEI_DSM
					anc_dsm_report(p_anc_hs, ANC_HS_QUEUE_WORK_ERR, 0);
#endif
				}
				pr_info("%s(%u) : resume charging for anc hs =%d!\n", __FUNCTION__, __LINE__,ret);
			}
		}
		mutex_unlock(&p_anc_hs->charge_lock);
	}
}

static void hi6401_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->hs_micbias_mutex);
	if (enable) {
		if (0 == priv->hs_micbias_work)
			hi6401_hs_micbias_enable(codec, true);
		++priv->hs_micbias_work;
	} else {
		--priv->hs_micbias_work;
		if (0 == priv->hs_micbias_work)
			hi6401_hs_micbias_enable(codec, false);
	}

	anc_hs_charging_control(priv);

	mutex_unlock(&priv->hs_micbias_mutex);
}

static void hi6401_hs_micbias_saradc_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6401_priv *priv = dev_get_drvdata(codec->dev);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->hs_micbias_mutex);
	if (enable) {
		if (!priv->hs_micbias_saradc) {
			hi6401_hs_micbias_enable(codec, true);
			priv->hs_micbias_saradc = true;
		}
	} else {
		if (priv->hs_micbias_saradc) {
			priv->hs_micbias_saradc = false;
			hi6401_hs_micbias_enable(codec, false);
		}
	}
	mutex_unlock(&priv->hs_micbias_mutex);
}

static inline bool check_saradc_value_ready(struct snd_soc_codec *codec)
{
	/* read codec status */
	int value = hi6401_reg_read(codec, HI6401_ANA_IRQ_0) & (1 << HI6401_IRQ_SARADC);

	if (0 == value)
		return false;

	hi6401_reg_write(codec, HI6401_ANA_IRQ_0, value);/* clr irq status */

	return true;
}

static int hi6401_read_saradc_value(struct snd_soc_codec *codec)
{
	int retry = 3;
	int reg_value = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	mutex_lock(&priv->saradc_mutex);

	/* power up saradc */
	hi6401_reg_clr_bit(codec, HI6401_SARADC_VREF_SEL, HI6401_SARADC_PD);
	hi6401_reg_set_bit(codec, HI6401_SARADC_CTRL, HI6401_SARADC_START);


	while(retry--) {
		usleep_range(1000, 1100);
		if (check_saradc_value_ready(codec)) {
			reg_value = hi6401_reg_read(codec, HI6401_SARADC_DATA);
			//pr_info("%s : saradc value is %#x\n", __FUNCTION__, reg_value);
			break;
		}
	}

	if (0 > retry)
		pr_err("%s : get saradc value err, set as 0\n", __FUNCTION__);

	/* power down saradc */
	hi6401_reg_clr_bit(codec, HI6401_SARADC_CTRL, HI6401_SARADC_START);
	hi6401_reg_set_bit(codec, HI6401_SARADC_VREF_SEL, HI6401_SARADC_PD);

	mutex_unlock(&priv->saradc_mutex);

	return GET_VOLTAGE(reg_value);
}

void hi6401_btn_report(struct hi6401_priv *priv)
{
	int mask = 0;

	switch (priv->hs_btn_num) {
	case 3:
		mask |= SND_JACK_BTN_1 | SND_JACK_BTN_2;
		/* fallthrough */
	case 1:
		mask |= SND_JACK_BTN_0;
		break;
	case 0:
	default:
		pr_info("headset button number %d is not support\n", priv->hs_btn_num);
		break;
	}

	snd_soc_jack_report(&priv->hs_jack, priv->report, mask);
}

void hi6401_jack_report(struct hi6401_priv *priv)
{
	enum hi6401_jack_states jack_status = HI6401_JACK_NONE;

	/* report invert 4-pole headset as 3-pole headphone */
	if (HI6401_JACK_INVERT == priv->hs_status)
		jack_status = HI6401_JACK_HEADPHONE;
	else
		jack_status = priv->hs_status;

	hi6401_btn_report(priv);/* clear btn event */
	snd_soc_jack_report(&priv->hs_jack, priv->report, HI6401_JACK_HEADSET);
#ifdef CONFIG_SWITCH
	switch_set_state(&priv->sdev, jack_status);
#endif
}

static int enable_boost(struct anc_hs_data *p_anc_hs, bool enable)
{
	int ret = 0;

	if(enable) {
		if(!p_anc_hs->boost_flag) {
			ret = regulator_bulk_enable(1, &p_anc_hs->regu_boost5v);
			if (ret != 0) {
				pr_err("%s(%u) : regulator_bulk_enable fail err = %d\n",
					__FUNCTION__, __LINE__, ret);
				return ret;
			}
			p_anc_hs->boost_flag = true;
		}
	}else {
		if(p_anc_hs->boost_flag) {
			ret = regulator_bulk_disable(1, &p_anc_hs->regu_boost5v);
			if (ret != 0) {
				pr_err("%s(%u) : regulator_bulk_disable fail err = %d\n",
					__FUNCTION__, __LINE__, ret);
				return ret;
			}
			p_anc_hs->boost_flag = false;
		}
	}
	return ret;
}

static bool need_charging(struct anc_hs_data *anc_hs)
{
	int ear_pwr_h,ear_pwr_l;
	int delta = 0, count, fail_count = 0;
	int loop = ADC_READ_COUNT;
	int temp;

	while(loop) {
		loop--;
		msleep(1);
		ear_pwr_h = hisi_adc_get_value(anc_hs->channel_pwl_h);
		if(ear_pwr_h < 0) {
			pr_err("%s(%u) : get ear_pwr_h hkadc error err = %d\n", __FUNCTION__, __LINE__, ear_pwr_h);
#ifdef CONFIG_HUAWEI_DSM
			anc_dsm_report(anc_hs, ANC_HS_ADCH_READ_ERR, ear_pwr_h);
#endif
			fail_count++;
			continue;
		}
		ear_pwr_l = hisi_adc_get_value(anc_hs->channel_pwl_l);
		if(ear_pwr_l < 0) {
			pr_err("%s(%u) : get ear_pwr_h hkadc error err = %d\n", __FUNCTION__, __LINE__, ear_pwr_l);
#ifdef CONFIG_HUAWEI_DSM
			anc_dsm_report(anc_hs, ANC_HS_ADC_FULL_ERR, ear_pwr_l);
#endif
			fail_count++;
			continue;
		}
		pr_info("%s(%u) : ear_pwr_h = %d,ear_pwr_l = %d\n", __FUNCTION__, __LINE__, ear_pwr_h, ear_pwr_l);

		temp = ear_pwr_h - ear_pwr_l - anc_hs->adc_calibration_base;
		if((temp > ADC_NORMAL_LIMIT_MAX) || (temp < ADC_NORMAL_LIMIT_MIN) ){
			fail_count++;
			continue;
		}

		delta += temp;
	}

	count = ADC_READ_COUNT -loop -fail_count;
	if(count == 0) {
		pr_err("%s(%u) : get anc_hs hkadc failed \n", __FUNCTION__, __LINE__);
		return false;
	}
	delta /= count;
	pr_info("%s(%u) : fianal adc value= %d  count=%d\n", __FUNCTION__, __LINE__, delta, count);
	if((delta >= anc_hs->anc_hs_limit_min) &&
		(delta <= anc_hs->anc_hs_limit_max))
		return true;
	else
		return false;
}

void start_charging(struct hi6401_priv *priv)
{
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	int ret;

	if(!priv->anc_hs_enable)
		return ;

	//enable 5vboost first
	pr_info("%s(%u) :enable 5vboost first\n", __FUNCTION__, __LINE__);
	ret = enable_boost(p_anc_hs, true);
	if(ret){
#ifdef CONFIG_HUAWEI_DSM
		anc_dsm_report(p_anc_hs, ANC_HS_OPEN_BOOST_ERR, ret);
#endif
	}
	msleep(5);    //FIXME:delay time can be optimazed

	mutex_lock(&p_anc_hs->charge_lock);
	gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
	p_anc_hs->anc_hs_mode = ANC_HS_RECOGNITION;
	mutex_unlock(&p_anc_hs->charge_lock);

	anc_hs_dump(p_anc_hs);
}

void control_regulator_by_headset_type(struct hi6401_priv *priv, int saradc_value)
{
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	int ret;

	if(!priv->anc_hs_enable)
		return;

	//calibration adc resistance
	anc_hs_adc_calibration(p_anc_hs);

	//wait all pending and running work finished
	ret = cancel_delayed_work_sync(&p_anc_hs->anc_hs_charge_delay_work);
	if(ret) {
		pr_info("%s(%u) : clear all pending and running work!\n", __FUNCTION__, __LINE__);
		cancel_delayed_work(&p_anc_hs->anc_hs_charge_delay_work);
	}

	mutex_lock(&p_anc_hs->charge_lock);
	p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
	mutex_unlock(&p_anc_hs->charge_lock);

	if (priv->hs_4_pole_min_voltage <= saradc_value &&
			priv->hs_4_pole_max_voltage >= saradc_value) {
		/* 4-pole headset */
		if(p_anc_hs->anc_resistence_level >= saradc_value)
			return;

		pr_info("%s : start anc hs charging control\n", __FUNCTION__);
		p_anc_hs->sleep_time = ANC_CHIP_COLD_STARTUP_TIME;
		//queue a delay work for charge control
		queue_delayed_work(p_anc_hs->anc_hs_charge_delay_wq,
			&p_anc_hs->anc_hs_charge_delay_work,
			0);
	} else {
		/* not 4-pole headset */
		pr_info("%s : no need enable 5vboost for non-4-pole headset\n", __FUNCTION__);
		// It is not anc headset
		ret = enable_boost(p_anc_hs, false);
		if(ret){
#ifdef CONFIG_HUAWEI_DSM
			anc_dsm_report(p_anc_hs, ANC_HS_CLOSE_BOOST_ERR, ret);
#endif
		}
	}

}

void hi6401_plug_in_detect(struct hi6401_priv *priv)
{
	int saradc_value = 0;
	struct snd_soc_codec *codec;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	codec = priv->codec;

	if (!check_headset_pluged_in(codec)) {
		pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
		return;
	}

	mutex_lock(&priv->plug_mutex);

	start_charging(priv);

	hi6401_mask_irq(codec, HI6401_IRQ_PLUGOUT);

	/* power on hs-micbias */
	hi6401_hs_micbias_saradc_enable(codec, true);
	hi6401_mask_btn_irqs(codec);
	hi6401_mbhd_comp3_enable(codec, true);
	msleep(150);


	/* get saradc value */
	saradc_value = hi6401_read_saradc_value(codec);
	pr_info("%s : get saradc value return %d\n", __FUNCTION__, saradc_value);

	if (!check_headset_pluged_in(codec)) {
		pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
		goto exit;
	}

	/*detect hs type*/
	mutex_lock(&priv->mutex);

	if (priv->hs_3_pole_max_voltage >= saradc_value) {
		/* 3-pole headphone */
		pr_info("%s : 3 pole is pluged in\n", __FUNCTION__);
		priv->hs_status = HI6401_JACK_HEADPHONE;
		priv->report = SND_JACK_HEADPHONE;
	} else if (priv->hs_4_pole_min_voltage <= saradc_value &&
			priv->hs_4_pole_max_voltage >= saradc_value) {
		/* 4-pole headset */
		pr_info("%s : 4 pole is pluged in\n", __FUNCTION__);
		priv->hs_status = HI6401_JACK_HEADSET;
		priv->report = SND_JACK_HEADSET;
	} else {
		/* invert 4-pole headset */
		pr_info("%s : need further detect, report as 3-pole headphone\n", __FUNCTION__);
		priv->hs_status = HI6401_JACK_INVERT;
		priv->report = SND_JACK_HEADPHONE;
	}

	mutex_unlock(&priv->mutex);

	control_regulator_by_headset_type(priv, saradc_value);

exit:
	hi6401_clr_irq(codec, HI6401_IRQ_PLUGOUT);
	hi6401_unmask_irq(codec, HI6401_IRQ_PLUGOUT);
	if (!check_headset_pluged_in(codec)) {
		pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
		mutex_lock(&priv->mutex);
		priv->hs_status = HI6401_JACK_NONE;
		priv->report = 0;
		mutex_unlock(&priv->mutex);
	}

	if (HI6401_JACK_HEADPHONE == priv->hs_status || HI6401_JACK_NONE == priv->hs_status)
		hi6401_mbhd_comp3_enable(codec, false);

	hi6401_hs_micbias_saradc_enable(codec, false);

	hi6401_jack_report(priv);

	mutex_unlock(&priv->plug_mutex);
}

void hi6401_plug_in_workfunc(struct work_struct *work)
{
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						headset_plug_in_delay_work.work);

	wake_lock(&priv->wake_lock);
	hi6401_plug_in_detect(priv);
	wake_unlock(&priv->wake_lock);
}

void anc_hs_plug_out(struct hi6401_priv *priv)
{
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	int ret;

	if(!priv->anc_hs_enable)
		return ;

	pr_info("%s : anc hs plut out\n", __FUNCTION__);

	anc_hs_disable_irq(p_anc_hs);
	cancel_delayed_work(&p_anc_hs->anc_hs_btn_delay_work);
	ret = cancel_delayed_work_sync(&p_anc_hs->anc_hs_charge_delay_work);
	if(ret) {
		pr_info("%s(%u) : make sure no job pending in the queue!\n", __FUNCTION__, __LINE__);
		cancel_delayed_work(&p_anc_hs->anc_hs_charge_delay_work);
	}

	//It is proper to wait btn event to be finished
	flush_work(&p_anc_hs->anc_hs_btn_delay_work.work);

	mutex_lock(&p_anc_hs->charge_lock);
	ret = enable_boost(p_anc_hs, false);
	if(ret){
#ifdef CONFIG_HUAWEI_DSM
		anc_dsm_report(p_anc_hs, ANC_HS_CLOSE_BOOST_ERR, ret);
#endif
	}
	gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
	p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
	//may plug out with button pressed
	priv->button_pressed = 0;

	mutex_unlock(&p_anc_hs->charge_lock);
	pr_info("%s : anc hs plut out sucess\n", __FUNCTION__);
}

void hi6401_plug_out_workfunc(struct work_struct *work)
{
	struct snd_soc_codec *codec;
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						headset_plug_out_delay_work.work);

	pr_info("%s : hs pluged out\n", __FUNCTION__);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	codec = priv->codec;

	wake_lock(&priv->wake_lock);
	mutex_lock(&priv->plug_mutex);

	hi6401_mask_btn_irqs(codec);
	hi6401_mbhd_comp3_enable(codec, false);
	hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0x0F);
	mutex_lock(&priv->mutex);
	priv->hs_status = HI6401_JACK_NONE;
	priv->report = 0;
	mutex_unlock(&priv->mutex);

	anc_hs_plug_out(priv);

	hi6401_jack_report(priv);

	mutex_unlock(&priv->plug_mutex);
	wake_unlock(&priv->wake_lock);
}

void anc_hs_btn_judge(struct work_struct *work)
{
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						p_anc_hs.anc_hs_btn_delay_work.work);
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	struct hi6401_irq *hi6401_irq;

	BUG_ON(NULL == priv);
	hi6401_irq = priv->p_irq;
	BUG_ON(NULL == hi6401_irq);

	pr_info("%s(%u) : in anc_hs_btn_judge !\n", __FUNCTION__, __LINE__);

	wake_lock(&priv->wake_lock);
	mutex_lock(&hi6401_irq->sr_mutex);

	//enable irq here
	anc_hs_enable_irq(p_anc_hs);
	mutex_lock(&priv->mutex);

	if(!gpio_get_value(p_anc_hs->mic_irq_gpio) && (priv->button_pressed == 0)) {
		/*button down event*/
		pr_info("%s(%u) : button down event !\n", __FUNCTION__, __LINE__);

		priv->hs_jack.jack->type = SND_JACK_BTN_0;
		priv->report |= SND_JACK_BTN_0;
		priv->button_pressed = 1;

		if (!check_headset_pluged_in(priv->codec)) {
			pr_info("%s(%u) :anc hs has plug out!\n", __FUNCTION__, __LINE__);
			anc_hs_disable_irq(p_anc_hs);
			goto end2;
		}
		hi6401_btn_report(priv);

	} else if(priv->button_pressed == 1) {
		/*button up event*/
		pr_info("%s(%u) : button up event !\n", __FUNCTION__, __LINE__);

		priv->hs_jack.jack->type = SND_JACK_BTN_0;
		priv->report = 0;
		priv->button_pressed = 0;

		hi6401_btn_report(priv);
	}
	if (!check_headset_pluged_in(priv->codec)) {
		pr_info("%s(%u) :anc hs has plug out!\n", __FUNCTION__, __LINE__);
		anc_hs_disable_irq(p_anc_hs);
	}
end2:
	mutex_unlock(&priv->mutex);
	mutex_unlock(&hi6401_irq->sr_mutex);
	wake_unlock(&priv->wake_lock);

	return;
}

void  anc_hs_charge_workfunc(struct work_struct *work)
{
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						p_anc_hs.anc_hs_charge_delay_work.work);
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	struct snd_soc_codec *codec;
	codec = priv->codec;

	BUG_ON(NULL == priv);

	wake_lock(&priv->wake_lock);

	pr_info("%s(%u) : anc hs charge !\n", __FUNCTION__, __LINE__);

	if (!check_headset_pluged_in(priv->codec)) {
		pr_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
		anc_hs_dump(p_anc_hs);
		wake_unlock(&priv->wake_lock);
		return ;
	}

	mutex_lock(&priv->hs_micbias_mutex);
	if(priv->hs_micbias_work > 0) {
		/* hs mic is in using*/
		pr_info("%s(%u) :hs mic is in using!\n", __FUNCTION__, __LINE__);
		p_anc_hs->mic_used = true;
		mutex_unlock(&priv->hs_micbias_mutex);
		wake_unlock(&priv->wake_lock);
		return ;
	}

	mutex_lock(&p_anc_hs->charge_lock);
	if(p_anc_hs->anc_hs_mode == ANC_HS_RECOGNITION) {
		pr_info("%s(%u) : It is in headset recognition!\n", __FUNCTION__, __LINE__);
		anc_hs_dump(p_anc_hs);
		mutex_unlock(&p_anc_hs->charge_lock);
		mutex_unlock(&priv->hs_micbias_mutex);
		wake_unlock(&priv->wake_lock);
		return ;
	}
	if(p_anc_hs->anc_hs_mode == ANC_HS_CHARGE_OFF) {
		p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_SWITCHING;
	}
	gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_5VBOOST);
	mutex_unlock(&p_anc_hs->charge_lock);
	mutex_unlock(&priv->hs_micbias_mutex);

	/* waiting for anc chip start up*/
	pr_info("%s(%u) : delay %d ms to wait anc chip start up!\n", __FUNCTION__, __LINE__,
	p_anc_hs->debug_sleep_time?p_anc_hs->debug_sleep_time:p_anc_hs->sleep_time);
	if(p_anc_hs->debug_sleep_time)
		msleep(p_anc_hs->debug_sleep_time);
	else
		msleep(p_anc_hs->sleep_time);
	p_anc_hs->sleep_time = ANC_CHIP_WARM_STARTUP_TIME;

	mutex_lock(&p_anc_hs->charge_lock);
	if(p_anc_hs->anc_hs_mode == ANC_HS_RECOGNITION) {
		pr_info("%s(%u) : It is in headset recognition!\n", __FUNCTION__, __LINE__);
		goto exit ;
	}
	if((priv->hs_micbias_work <= 0) && need_charging(p_anc_hs)){
		if(p_anc_hs->anc_hs_mode == ANC_HS_CHARGE_SWITCHING) {
			/* make sure hi6401 btn work has been completed*/
			flush_work(&priv->headset_btn_down_delay_work.work);
			flush_work(&priv->headset_btn_up_delay_work.work);

			pr_info("%s(%u) : anc_hs_enable_irq !\n", __FUNCTION__, __LINE__);
			anc_hs_enable_irq(p_anc_hs);

			p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_ON;
		}
	} else {
		if(p_anc_hs->anc_hs_mode == ANC_HS_CHARGE_ON) {
			/* make sure anc hs btn work has been completed*/
			anc_hs_disable_irq(p_anc_hs);
			flush_work(&p_anc_hs->anc_hs_btn_delay_work.work);

			pr_info("%s(%u) : anc_hs_disable_irq !\n", __FUNCTION__, __LINE__);
		}

		if(!p_anc_hs->mic_used) {
			int ret;
			ret = queue_delayed_work(p_anc_hs->anc_hs_charge_delay_wq,
				&p_anc_hs->anc_hs_charge_delay_work,
				msecs_to_jiffies(p_anc_hs->no_charge_detect_period));
			pr_info("%s(%u) : charge detect again, ret:%d !\n", __FUNCTION__, __LINE__, ret);
		}
		gpio_set_value(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
		p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
	}

exit:
	anc_hs_dump(p_anc_hs);

	mutex_unlock(&p_anc_hs->charge_lock);
	wake_unlock(&priv->wake_lock);

	return;
}


void  hi6401_btnup_workfunc(struct work_struct *work)
{
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						headset_btn_up_delay_work.work);

	BUG_ON(NULL == priv);

	pr_info("%s(%u) : btn up !\n", __FUNCTION__, __LINE__);

	if (1 == priv->hs_btn_num)
		priv->hs_jack.jack->type = SND_JACK_BTN_0;
	else
		priv->hs_jack.jack->type = SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2;

	priv->report = 0;
	if(priv->anc_hs_enable) {
		priv->button_pressed = 0;
	}

	hi6401_btn_report(priv);

	return;
}

void hi6401_btndown_workfunc(struct work_struct *work)
{
	int saradc_value = 0;
	struct snd_soc_codec *codec;
	struct hi6401_priv *priv = container_of(work,
						struct hi6401_priv,
						headset_btn_down_delay_work.work);

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	codec = priv->codec;
	hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0x0F);

	if (!check_headset_pluged_in(priv->codec)) {
		pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
		return;
	}

	wake_lock(&priv->wake_lock);

	if (HI6401_JACK_HEADSET == priv->hs_status) {
		/* power on hs-micbias */
		hi6401_hs_micbias_saradc_enable(codec, true);
		saradc_value = hi6401_read_saradc_value(codec);
		pr_info("%s(%u) :saradc_value: %d \n", __FUNCTION__, __LINE__, saradc_value);
		hi6401_hs_micbias_saradc_enable(codec, false);

		if (!check_headset_pluged_in(priv->codec)) {
			pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
			goto end;
		}

		if ((saradc_value >= priv->hs_4_pole_min_voltage) && (saradc_value <= priv->hs_4_pole_max_voltage)) {
			pr_info("%s(%u) : process as btn up! \n", __FUNCTION__, __LINE__);
			mutex_lock(&priv->mutex);
			priv->hs_jack.jack->type = SND_JACK_BTN_0;
			priv->report |= 0;
			priv->hs_btn_type = 0;
			if(priv->anc_hs_enable) {
				priv->button_pressed= 0;
			}
			mutex_unlock(&priv->mutex);
		} else if ((saradc_value >= priv->btn_play_min_voltage) && (saradc_value <= priv->btn_play_max_voltage)) {
			mutex_lock(&priv->mutex);
			priv->hs_jack.jack->type = SND_JACK_BTN_0;
			priv->report |= SND_JACK_BTN_0;
			priv->hs_btn_type = SND_JACK_BTN_0;
			if(priv->anc_hs_enable) {
				priv->button_pressed = 1;
			}
			mutex_unlock(&priv->mutex);
		} else if (priv->btn_volume_up_min_voltage < saradc_value && saradc_value <= priv->btn_volume_up_max_voltage) {
			mutex_lock(&priv->mutex);
			priv->hs_jack.jack->type = SND_JACK_BTN_1;
			priv->report |= SND_JACK_BTN_1;
			priv->hs_btn_type = SND_JACK_BTN_1;
			mutex_unlock(&priv->mutex);
		} else if (priv->btn_volume_down_min_voltage < saradc_value && saradc_value <= priv->btn_volume_down_max_voltage) {
			mutex_lock(&priv->mutex);
			priv->hs_jack.jack->type = SND_JACK_BTN_2;
			priv->report |= SND_JACK_BTN_2;
			priv->hs_btn_type = SND_JACK_BTN_2;
			mutex_unlock(&priv->mutex);
		} else {
			msleep(30);
			hi6401_plug_in_detect(priv);
			goto end;
		}

		if (!check_headset_pluged_in(priv->codec)) {
			pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
			goto end;
		}

		/*report key event*/
		pr_info("%s(%u): report type = 0x%x, status=0x%x\n", __FUNCTION__, __LINE__, priv->report, priv->hs_status);
		hi6401_btn_report(priv);
		if (priv->need_report_up_event) {
			priv->need_report_up_event = false;
			queue_delayed_work(priv->headset_btn_up_delay_wq,
					&priv->headset_btn_up_delay_work,
					msecs_to_jiffies(30));
		}
	}
end:
	wake_unlock(&priv->wake_lock);

	return;
}

static irqreturn_t anc_hs_btn_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	wake_lock_timeout(&priv->wake_lock, 50);

	anc_hs_disable_irq(p_anc_hs);

	queue_delayed_work(p_anc_hs->anc_hs_btn_delay_wq,
			&p_anc_hs->anc_hs_btn_delay_work,
			msecs_to_jiffies(20));

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_btnup_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	if (!check_headset_pluged_in(priv->codec))
		return IRQ_HANDLED;

	wake_lock_timeout(&priv->wake_lock, 100);

	if (HI6401_JACK_INVERT == priv->hs_status) {
		pr_info("%s: further detect\n", __FUNCTION__);
		/* further detect */
		queue_delayed_work(priv->headset_plug_in_delay_wq,
				&priv->headset_plug_in_delay_work,
				msecs_to_jiffies(50));
	} else if (0 == priv->hs_btn_type){
		return IRQ_HANDLED;
	} else {
		queue_delayed_work(priv->headset_btn_up_delay_wq,
				&priv->headset_btn_up_delay_work,
				msecs_to_jiffies(60));
		priv->hs_btn_type = 0;
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_btndown_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	if (!check_headset_pluged_in(priv->codec))
		return IRQ_HANDLED;

	wake_lock_timeout(&priv->wake_lock, 50);

	queue_delayed_work(priv->headset_btn_down_delay_wq,
				&priv->headset_btn_down_delay_work,
				msecs_to_jiffies(30));

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_btnup_eco_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	if (!check_headset_pluged_in(priv->codec))
		return IRQ_HANDLED;

	wake_lock_timeout(&priv->wake_lock, 100);

	if (HI6401_JACK_INVERT == priv->hs_status) {
		pr_err("%s: further detect\n", __FUNCTION__);
		/* further detect */
		queue_delayed_work(priv->headset_plug_in_delay_wq,
				&priv->headset_plug_in_delay_work,
				msecs_to_jiffies(50));
	} else if (0 == priv->hs_btn_type){
		return IRQ_HANDLED;
	} else {
		queue_delayed_work(priv->headset_btn_up_delay_wq,
				&priv->headset_btn_up_delay_work,
				msecs_to_jiffies(30));
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_btndown_eco_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	if (!check_headset_pluged_in(priv->codec))
		return IRQ_HANDLED;

	wake_lock_timeout(&priv->wake_lock, 50);

	queue_delayed_work(priv->headset_btn_down_delay_wq,
				&priv->headset_btn_down_delay_work,
				msecs_to_jiffies(20));

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_plugin_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	wake_lock_timeout(&priv->wake_lock, 900);

	queue_delayed_work(priv->headset_plug_in_delay_wq,
			&priv->headset_plug_in_delay_work,
			msecs_to_jiffies(800));

	return IRQ_HANDLED;
}

static irqreturn_t hi6401_plugout_handler(int irq, void *data)
{
	struct hi6401_priv *priv = (struct hi6401_priv *)data;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == priv->codec);

	/* do not take care of irq, it cleared in hi6401_irq handle */

	if (0 < priv->hs_micbias_work)
		hi6401_reg_set_bit(priv->codec, HI6401_MAINPGA_REG, HI6401_MAINPGA_MUTE_BIT);

	wake_lock_timeout(&priv->wake_lock, 30);

	queue_delayed_work(priv->headset_plug_out_delay_wq,
			&priv->headset_plug_out_delay_work,
			msecs_to_jiffies(0));

	return IRQ_HANDLED;
}

static void hi6401_init_chip(struct snd_soc_codec *codec)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	/* init registers */
	/* enable otp */
	hi6401_reg_write(codec, HI6401_VREF_IBIAS_PD, 0x19);

	/* close analog path */
	hi6401_reg_write(codec, HI6401_ADC_PD, 0x7F);
	hi6401_reg_write(codec, HI6401_ANA_IRQM_0, 0xFF);
	hi6401_reg_write(codec, HI6401_ANA_IRQM_1, 0xFF);
	hi6401_reg_write(codec, HI6401_FS_ADCLR_REG, 0x5);

	/* pop control */
	hi6401_reg_write(codec, HI6401_POP_CTRL1, 0xE1);
	hi6401_reg_write(codec, HI6401_POP_CTRL2, 0x6C);

	/* mixer */
	hi6401_reg_write(codec, HI6401_MIXOUT_EAR, 0);
	hi6401_reg_write(codec, HI6401_MIXOUT_HSL, 0);
	hi6401_reg_write(codec, HI6401_MIXOUT_HSR, 0);
	hi6401_reg_write(codec, HI6401_MIXOUT_LINEOUTL, 0);
	hi6401_reg_write(codec, HI6401_MIXOUT_LINEOUTR, 0);
	hi6401_reg_write(codec, HI6401_MIXINL, 0);
	hi6401_reg_write(codec, HI6401_MIXINR, 0);

	hi6401_reg_write(codec, HI6401_PLL_FCW_0, 0x02);
	hi6401_reg_write(codec, HI6401_PLL_FCW_1, 0x8F);
	hi6401_reg_write(codec, HI6401_PLL_FCW_2, 0x5C);

	hi6401_reg_write(codec, HI6401_MBHD_VREF_CTRL, 0x92);
	hi6401_reg_write(codec, HI6401_MICBIAS_ECO_EN, 0x84);/* submic 2.5v */
	hi6401_reg_write(codec, HI6401_MICBIAS1_HSMICB_ADJ, 0x26);/* mainmic 2.5v hsmic 2.7v */
	hi6401_reg_write(codec, HI6401_DEB_HS_DET, 0x50);/* 20ms */
	hi6401_reg_write(codec, HI6401_DEB_HS_BTN_DET, 0x14);/* 20ms */

	/* chopper, default value */
	hi6401_reg_write(codec, HI6401_CHOPPER_SEL, 0x6C);/* 0x69 */

	hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x01);
	hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x01);

	hi6401_reg_write(codec, HI6401_S1_PGA_FRC, 0x30);/* 0.5dB */

	/* init saradc */
	hi6401_reg_write(codec, HI6401_SARADC_CTRL, 0xCE);
	hi6401_reg_write(codec, HI6401_SARADC_VREF_SEL, 0x6);

	/* hs_det invert */
	if (1 == priv->hs_det)
		hi6401_reg_set_bit(codec, HI6401_HS_CTRL, HI6401_HS_DET_INV);

	hi6401_reg_write(codec, HI6401_S1_CONFIG_2, 0x20);
	hi6401_reg_write(codec, HI6401_S2_CONFIG_2, 0x20);
	hi6401_reg_write(codec, HI6401_S3_CONFIG_2, 0x20);
	hi6401_reg_write(codec, HI6401_S4_CONFIG_2, 0x20);

	/* s1,s2,s3,s4 set fs 96kHz to avoid sync_div problem */
	hi6401_reg_write(codec, HI6401_FS_S1_S2_REG, 0x55);
	hi6401_reg_write(codec, HI6401_FS_S3_S4_REG, 0x55);
}

static int hi6401_register_jack(struct snd_soc_codec *codec)
{
	int ret = -1;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(NULL == priv);

	/* register headset jack */
	ret = snd_soc_jack_new(codec, "Headset Jack", SND_JACK_HEADSET, &priv->hs_jack);
	if (ret) {
		pr_err("%s : jack new error, errornum = %d\n", __FUNCTION__, ret);
		return ret;
	}

	/* register headset button */
	switch (priv->hs_btn_num) {
	case 3:
		snd_jack_set_key(priv->hs_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
		snd_jack_set_key(priv->hs_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
		/* fallthrough */
	case 1:
		snd_jack_set_key(priv->hs_jack.jack, SND_JACK_BTN_0, KEY_MEDIA);
		break;
	case 0:
	default:
		pr_info("headset button number %d is not support\n", priv->hs_btn_num);
		break;
	}

	/* init hs & hs_btn status */
	priv->report = 0;
	priv->hs_status = HI6401_JACK_NONE;

	return 0;
}


#ifdef CONFIG_DEBUG_FS
static ssize_t hs_info_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	struct hi6401_priv *priv = container_of(p_anc_hs,
					struct hi6401_priv,
					p_anc_hs);

	#define HS_INFO_SIZE 256
	int ret = 0;
	char *buf=(char*)kmalloc(sizeof(char)*HS_INFO_SIZE, GFP_KERNEL);
	memset(buf, 0, HS_INFO_SIZE);

	if(!buf) {
		pr_err("%s : couldn't malloc buffer.\n",__FUNCTION__);
		return -1;
	}

	snprintf(buf, HS_INFO_SIZE, "%sanc_hs_limit_min: %d\n", buf, p_anc_hs->anc_hs_limit_min);
	snprintf(buf, HS_INFO_SIZE, "%sanc_hs_limit_max: %d\n", buf, p_anc_hs->anc_hs_limit_max);
	snprintf(buf, HS_INFO_SIZE, "%sanc_hs_mode: %d\n", buf, p_anc_hs->anc_hs_mode);
	snprintf(buf, HS_INFO_SIZE, "%sirq_flag: %d\n", buf, p_anc_hs->irq_flag);
	snprintf(buf, HS_INFO_SIZE, "%schannel_pwl_h: %d\n", buf, p_anc_hs->channel_pwl_h);
	snprintf(buf, HS_INFO_SIZE, "%schannel_pwl_l: %d\n", buf, p_anc_hs->channel_pwl_l);
	snprintf(buf, HS_INFO_SIZE, "%sboost_flag: %d\n", buf, p_anc_hs->boost_flag);
	snprintf(buf, HS_INFO_SIZE, "%sgpio_mic_sw: %d\n", buf, gpio_get_value(p_anc_hs->gpio_mic_sw));
	snprintf(buf, HS_INFO_SIZE, "%smic_used: %d\n", buf, p_anc_hs->mic_used);
	snprintf(buf, HS_INFO_SIZE, "%sbutton_pressed: %d\n", buf, priv->button_pressed);
	snprintf(buf, HS_INFO_SIZE, "%sadc_calibration_base: %d\n", buf, p_anc_hs->adc_calibration_base);
	snprintf(buf, HS_INFO_SIZE, "%scalibration_current: %d\n", buf,
		(hisi_adc_get_value(p_anc_hs->channel_pwl_h) - hisi_adc_get_value(p_anc_hs->channel_pwl_l)));

	snprintf(buf, HS_INFO_SIZE, "%sadc_h: %d\n", buf, hisi_adc_get_value(p_anc_hs->channel_pwl_h));
	snprintf(buf, HS_INFO_SIZE, "%sadc_l: %d\n", buf, hisi_adc_get_value(p_anc_hs->channel_pwl_l));
	snprintf(buf, HS_INFO_SIZE, "%sanc_resistence_level: %d\n", buf, p_anc_hs->anc_resistence_level);

	ret = simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));

	kfree(buf);
	return ret;
}

static ssize_t detect_limit_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	memset(buf,0,32);

	snprintf(buf, 32, "%d\n",p_anc_hs->anc_hs_limit_min);

	return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static ssize_t detect_limit_write(struct file *file,
		const char __user *user_buf, size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	size_t buf_size;
	int ret;

	memset(buf,0,32);
	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;
	ret = kstrtoint(buf, 10, &(p_anc_hs->anc_hs_limit_min));
	if(ret) {
		pr_err("%s : convert to int type failed\n",__FUNCTION__);
		return ret;
	}

	return buf_size;
}

static ssize_t detect_period_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	memset(buf,0,32);
	snprintf(buf, 32, "%d\n", p_anc_hs->no_charge_detect_period);

	return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static ssize_t detect_period_write(struct file *file,
		const char __user *user_buf, size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	size_t buf_size;
	int ret = 0;

	memset(buf,0,32);
	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;

	ret = kstrtoint(buf, 10, &(p_anc_hs->no_charge_detect_period));
	if(ret) {
		pr_err("%s : convert to int type failed\n",__FUNCTION__);
		return ret;
	}

	return buf_size;
}

static ssize_t gpio_sw_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	memset(buf,0,32);

	snprintf(buf, 32, "%d\n",gpio_get_value(p_anc_hs->gpio_mic_sw));

	return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static ssize_t gpio_sw_write(struct file *file,
		const char __user *user_buf, size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	size_t buf_size;
	int value;
	int ret;

	memset(buf,0,32);
	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;
	ret = kstrtoint(buf, 10, &value);
	if(ret) {
		pr_err("%s : convert to int type failed\n",__FUNCTION__);
		return ret;
	}

	if(value) {
		gpio_set_value(p_anc_hs->gpio_mic_sw, 1);
	} else {
		gpio_set_value(p_anc_hs->gpio_mic_sw, 0);
	}

	return buf_size;
}

static ssize_t sleep_time_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	memset(buf,0,32);

	if(p_anc_hs->debug_sleep_time) {
		snprintf(buf, 32, "%d\n",p_anc_hs->debug_sleep_time);
	}else {
		snprintf(buf, 32, "%d\n",p_anc_hs->sleep_time);
	}

	return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static ssize_t sleep_time_write(struct file *file,
		const char __user *user_buf, size_t count, loff_t *ppos)
{
	struct anc_hs_data *p_anc_hs = file->private_data;
	char buf[32];
	size_t buf_size;
	int value;
	int ret;

	memset(buf,0,32);
	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;
	ret = kstrtoint(buf, 10, &value);
	if(ret) {
		pr_err("%s : convert to int type failed\n",__FUNCTION__);
		return ret;
	}

	p_anc_hs->debug_sleep_time = value;
	return buf_size;
}

static const struct file_operations hs_info_fops = {
	.read =     hs_info_read,
	.open =     simple_open,
	.llseek =   default_llseek,
};
static const struct file_operations detect_limit_fops = {
	.read =     detect_limit_read,
	.write =    detect_limit_write,
	.open =     simple_open,
	.llseek =   default_llseek,
};
static const struct file_operations detect_period_fops = {
	.read =     detect_period_read,
	.write =    detect_period_write,
	.open =     simple_open,
	.llseek =   default_llseek,
};

static const struct file_operations gpio_sw_fops = {
	.read =     gpio_sw_read,
	.write =    gpio_sw_write,
	.open =     simple_open,
	.llseek =   default_llseek,
};

static const struct file_operations sleep_time_fops = {
	.read =     sleep_time_read,
	.write =    sleep_time_write,
	.open =     simple_open,
	.llseek =   default_llseek,
};
#endif

static const struct of_device_id anc_hs_match[] = {
	{ .compatible = "hisilicon,anc_headset", },
	{},
};
MODULE_DEVICE_TABLE(of, anc_hs_match);

static void anc_hs_adc_calibration(struct anc_hs_data *p_anc_hs)
{
	int loop = ADC_CALIBRATION_TIMES;
	int count,fail_count = 0;
	p_anc_hs->calibration_done = true;
	p_anc_hs->adc_calibration_base = 0;

	while(loop) {
		int adc_h, adc_l;
		loop--;
		msleep(1);
		adc_h = hisi_adc_get_value(p_anc_hs->channel_pwl_h);
		if(adc_h < 0) {
			pr_err("[anc_hs] get adc value failed,adc_h = %d\n", adc_h);
			fail_count ++;
			continue;
		}
		adc_l = hisi_adc_get_value(p_anc_hs->channel_pwl_l);
		if(adc_l < 0) {
			pr_err("[anc_hs] get adc value failed,adc_l = %d\n", adc_l);
			fail_count ++;
			continue;
		}

		//completely unnormal
		if((adc_h - adc_l < -100) || (adc_h - adc_l > 100)){
			pr_err("[anc_hs] adc value is not expect, %d\n", adc_h - adc_l);
			fail_count ++;
			continue;
		}
		p_anc_hs->adc_calibration_base += (adc_h - adc_l);
	}

	count = ADC_CALIBRATION_TIMES - loop - fail_count;
	if(count == 0) {
		p_anc_hs->adc_calibration_base = 0;
		p_anc_hs->calibration_done = false;
		pr_err("[anc_hs] calibration whole failed\n");
	}else {
		p_anc_hs->adc_calibration_base /= count;
		pr_info("anc_hs: adc_calibration_base = %d with %d times\n", p_anc_hs->adc_calibration_base, count);

		if(p_anc_hs->adc_calibration_base > 50 ||
			p_anc_hs->adc_calibration_base < -50) {
			p_anc_hs->adc_calibration_base = 0;
			p_anc_hs->calibration_done = false;
			pr_err("[anc_hs] calibration value is not illegal, error occured\n");
		}
	}
}

static int anc_hs_init(struct anc_hs_data *p_anc_hs)
{
	struct device_node *node;
	struct hi6401_priv *priv = container_of(p_anc_hs,
						struct hi6401_priv,
						p_anc_hs);
	struct snd_soc_codec *codec = priv->codec;
	int temp;
	int ret;

	mutex_init(&p_anc_hs->charge_lock);
	spin_lock_init(&p_anc_hs->irq_lock);

	p_anc_hs->anc_hs_mode = ANC_HS_CHARGE_OFF;
	p_anc_hs->irq_flag = true;
	p_anc_hs->boost_flag = false;
	p_anc_hs->mic_used = false;
	p_anc_hs->sleep_time = ANC_CHIP_WARM_STARTUP_TIME;
	p_anc_hs->debug_sleep_time = 0;
	p_anc_hs->adc_calibration_base = 0;
	p_anc_hs->no_charge_detect_period = NO_CHARGE_DETECT_PERIOD_TIME;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,anc_headset");
	if (!node) {
		dev_err(codec->dev, "find hisilicon,anc_headset fail\n");
		return -ENODEV;
	}

	p_anc_hs->regu_boost5v.supply = "anc_hs_charge";
	
#if 0
	ret = devm_regulator_bulk_get(codec->dev, 1, &(p_anc_hs->regu_boost5v));
	if (0 != ret) {
		dev_err(codec->dev, "couldn't get regulators(boost5v) %d\n", ret);
		return -ENODEV;
	}
#endif
	p_anc_hs->gpio_mic_sw =  of_get_named_gpio(node, "gpios", 0);
	if(p_anc_hs->gpio_mic_sw < 0) {
		dev_err(codec->dev, "gpio_mic_sw is unvalid!\n");
		return -ENOENT;
	}

	if (!gpio_is_valid(p_anc_hs->gpio_mic_sw)) {
		dev_err(codec->dev, "gpio is unvalid!\n");
		return -ENOENT;
	}

	p_anc_hs->mic_irq_gpio = of_get_named_gpio(node, "gpios", 1);
	if(p_anc_hs->mic_irq_gpio < 0) {
		dev_err(codec->dev, "mic_irq_gpio is unvalid!\n");
		return -ENOENT;
	}

	if (!gpio_is_valid(p_anc_hs->mic_irq_gpio)) {
		dev_err(codec->dev, "gpio is unvalid!\n");
		return -EINVAL;
	}

	ret = gpio_request(p_anc_hs->mic_irq_gpio, "gpio_mic_irq");
	if (ret) {
		dev_err(codec->dev, "error request GPIO for mic_irq_gpio fail %d\n", ret);
		return -ENODEV;
	}
	gpio_direction_input(p_anc_hs->mic_irq_gpio);

	p_anc_hs->mic_irq = gpio_to_irq(p_anc_hs->mic_irq_gpio);

	ret = gpio_request(p_anc_hs->gpio_mic_sw, "gpio_mic_sw");
	if (ret) {
		dev_err(codec->dev, "error request GPIO for mic_sw fail %d\n", ret);
		goto gpio_mic_sw_err;
	}
	gpio_direction_output(p_anc_hs->gpio_mic_sw, SWITCH_CHIP_HSBIAS);

	if (!of_property_read_u32(node, "adc_channel_h", &temp))
		p_anc_hs->channel_pwl_h = temp;
	else
		p_anc_hs->channel_pwl_h = 15;
	if (!of_property_read_u32(node, "adc_channel_l", &temp))
		p_anc_hs->channel_pwl_l = temp;
	else
		p_anc_hs->channel_pwl_l = 14;
	if (!of_property_read_u32(node, "anc_hs_limit_min", &temp))
		p_anc_hs->anc_hs_limit_min = temp;
	else
		p_anc_hs->anc_hs_limit_min = ANC_HS_LIMIT_MIN;
	if (!of_property_read_u32(node, "anc_hs_limit_max", &temp))
		p_anc_hs->anc_hs_limit_max = temp;
	else
		p_anc_hs->anc_hs_limit_max = ANC_HS_LIMIT_MAX;

	if (!of_property_read_u32(node, "anc_resistence_level", &temp))
		p_anc_hs->anc_resistence_level = temp;
	else
		p_anc_hs->anc_resistence_level = 0;
	pr_info("%s : anc_resistence_level = %d\n", __FUNCTION__, p_anc_hs->anc_resistence_level);

	p_anc_hs->anc_hs_btn_delay_wq =
			create_singlethread_workqueue("anc_hs_btn_delay_wq");
	if (!(p_anc_hs->anc_hs_btn_delay_wq)) {
		pr_err("%s : anc_hs_btn_delay_wq create failed\n", __FUNCTION__);
		ret = -ENOMEM;
		goto anc_hs_btn_wq_err;
	}
	INIT_DELAYED_WORK(&p_anc_hs->anc_hs_btn_delay_work, anc_hs_btn_judge);

	p_anc_hs->anc_hs_charge_delay_wq =
			create_singlethread_workqueue("anc_hs_charge_delay_wq");
	if (!(p_anc_hs->anc_hs_charge_delay_wq)) {
		pr_err("%s : anc_hs_charge_delay_wq create failed\n", __FUNCTION__);
		ret = -ENOMEM;
		goto anc_hs_charge_wq_err;
	}
	INIT_DELAYED_WORK(&p_anc_hs->anc_hs_charge_delay_work, anc_hs_charge_workfunc);

	/*anc hs irq request */
	ret = request_irq(p_anc_hs->mic_irq,
			  anc_hs_btn_handler,
			  IRQF_DISABLED|IRQF_TRIGGER_RISING|
			  IRQF_TRIGGER_FALLING|IRQF_NO_SUSPEND, "anc_hs_btn", priv);
	if (0 > ret)
		goto anc_hs_btn_err;
	anc_hs_disable_irq(p_anc_hs);

	/* add new controls*/
	snd_soc_add_codec_controls(codec, anc_hs_controls,
				     ARRAY_SIZE(anc_hs_controls));

#ifdef CONFIG_HUAWEI_DSM
	if (!anc_hs_dclient) {
		anc_hs_dclient = dsm_register_client(&dsm_anc_hs);
	}
#endif

#ifdef CONFIG_DEBUG_FS
	debug_dir = debugfs_create_dir("anc_hs", NULL);
	if(!debug_dir) {
		pr_err("anc_hs: Failed to create anc_hs debugfs dir\n");
		return 0;
	}
	if (!debugfs_create_file("hs_info", 0440, debug_dir, p_anc_hs,
				&hs_info_fops)) {
		pr_err("anc_hs: Failed to create hs_info debugfs file\n");
	}
	if (!debugfs_create_file("detect_limit", 0660, debug_dir, p_anc_hs,
				&detect_limit_fops)) {
		pr_err("anc_hs: Failed to create detect_limit debugfs file\n");
	}
	if (!debugfs_create_file("detect_period", 0660, debug_dir, p_anc_hs,
				&detect_period_fops)) {
		pr_err("anc_hs: Failed to create detect_period debugfs file\n");
	}
	if (!debugfs_create_file("gpio_sw", 0660, debug_dir, p_anc_hs,
				&gpio_sw_fops)) {
		pr_err("anc_hs: Failed to create gpio_sw debugfs file\n");
	}
	if (!debugfs_create_file("sleep_time", 0660, debug_dir, p_anc_hs,
				&sleep_time_fops)) {
		pr_err("anc_hs: Failed to create sleep_time debugfs file\n");
	}
#endif

	return 0;

anc_hs_btn_err:
	if(p_anc_hs->anc_hs_charge_delay_wq) {
		ret = cancel_delayed_work_sync(&p_anc_hs->anc_hs_charge_delay_work);
		if(ret) {
			pr_info("%s(%u) : make sure no job pending in the queue!\n", __FUNCTION__, __LINE__);
			cancel_delayed_work(&p_anc_hs->anc_hs_charge_delay_work);
		}
		flush_workqueue(p_anc_hs->anc_hs_charge_delay_wq);
		destroy_workqueue(p_anc_hs->anc_hs_charge_delay_wq);
	}
anc_hs_charge_wq_err:
	if(p_anc_hs->anc_hs_btn_delay_wq) {
		cancel_delayed_work(&p_anc_hs->anc_hs_btn_delay_work);
		flush_workqueue(p_anc_hs->anc_hs_btn_delay_wq);
		destroy_workqueue(p_anc_hs->anc_hs_btn_delay_wq);
	}
anc_hs_btn_wq_err:
	gpio_free(p_anc_hs->gpio_mic_sw);
gpio_mic_sw_err:
	gpio_free(p_anc_hs->mic_irq_gpio);
	return ret;
}

static const struct of_device_id hi6401_codec_match[] = {
	{ .compatible = "hisilicon,hi6401-codec", },
	{},
};
MODULE_DEVICE_TABLE(of, hi6401_codec_mach);

static int hi6401_soc_probe(struct snd_soc_codec *codec)
{
	int ret = 0;
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
	const struct of_device_id *match;

	if (!priv) {
		pr_err("get driver data is NULL\n");
		return -ENOENT;
	}

	snd_soc_codec_set_drvdata(codec, priv);

	priv->codec = codec;

	match = of_match_device(hi6401_codec_match, codec->dev);
	if (!match) {
		pr_err("get device info err\n");
		return -ENOENT;
	} else {
		struct device_node *node = codec->dev->of_node;
		int temp;

		/* get board defination */
		if (!of_property_read_u32(node, "hisilicon,hs_det", &temp))
			priv->hs_det = temp;
		else
			priv->hs_det = 0;

		if (!of_property_read_u32(node, "hisilicon,hs_btn_num", &temp))
			priv->hs_btn_num = temp;
		else
			priv->hs_btn_num = 0;

		if (!of_property_read_u32(node, "hisilicon,hs_3_pole_max_voltage", &temp))
			priv->hs_3_pole_max_voltage = temp;
		else
			priv->hs_3_pole_max_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,hs_4_pole_min_voltage", &temp))
			priv->hs_4_pole_min_voltage = temp;
		else
			priv->hs_4_pole_min_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,hs_4_pole_max_voltage", &temp))
			priv->hs_4_pole_max_voltage = temp;
		else
			priv->hs_4_pole_max_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_play_min_voltage", &temp))
			priv->btn_play_min_voltage = temp;
		else
			priv->btn_play_min_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_play_max_voltage", &temp))
			priv->btn_play_max_voltage = temp;
		else
			priv->btn_play_max_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_volume_up_min_voltage", &temp))
			priv->btn_volume_up_min_voltage = temp;
		else
			priv->btn_volume_up_min_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_volume_up_max_voltage", &temp))
			priv->btn_volume_up_max_voltage = temp;
		else
			priv->btn_volume_up_max_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_volume_down_min_voltage", &temp))
			priv->btn_volume_down_min_voltage = temp;
		else
			priv->btn_volume_down_min_voltage = 0;

		if (!of_property_read_u32(node, "hisilicon,btn_volume_down_max_voltage", &temp))
			priv->btn_volume_down_max_voltage = temp;
		else
			priv->btn_volume_down_max_voltage = 0;
	}

	hi6401_init_chip(codec);

	/* init irq mask */
	hi6401_reg_write(codec, HI6401_ANA_IRQM_0, 0xFF);

	/* clr all irqs */
	hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0xFF);

#ifdef CONFIG_SWITCH
	priv->sdev.name = "h2w";
	ret = switch_dev_register(&priv->sdev);
	if (ret) {
		pr_err("%s : error registering switch device %d\n", __FUNCTION__, ret);
		return ret;
	}
#endif

	hi6401_register_jack(codec);

	/* init hi6401_codec_platform_data */
	wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hi6401");
	spin_lock_init(&priv->lock);
	mutex_init(&priv->mutex);
	mutex_init(&priv->ibias_mutex);
	mutex_init(&priv->saradc_mutex);
	mutex_init(&priv->plug_mutex);
	mutex_init(&priv->hs_micbias_mutex);
	mutex_init(&priv->lineout_mutex);
	mutex_init(&priv->dapm_mutex);
	priv->ref_pll = 0;
	priv->ref_audio_clk = 0;
	priv->ref_voice_clk = 0;
	priv->ref_audio_stream = 0;
	priv->ref_audio_tx = 0;
	priv->ref_audio_rx = 0;

	priv->hs_micbias_work = 0;
	priv->hs_micbias_saradc = false;
	priv->ibias_work = 0;
	priv->ibias_saradc = false;
	priv->hsl_power_on = false;
	priv->hsr_power_on = false;
	priv->hs_btn_type = 0;
	priv->anc_hs_enable = false;

	if(!anc_hs_init(&priv->p_anc_hs)) {
		priv->button_pressed = 0;
		priv->anc_hs_enable = true;
		pr_info("%s : anc headset has been supported\n", __FUNCTION__);
	}

	priv->headset_plug_in_delay_wq =
			create_singlethread_workqueue("headset_plug_in_delay_wq");
	if (!(priv->headset_plug_in_delay_wq)) {
		pr_err("%s : headset_plug_in_delay_wq create failed", __FUNCTION__);
		ret = -ENOMEM;
		goto headset_plug_in_wq_err;
	}
	INIT_DELAYED_WORK(&priv->headset_plug_in_delay_work, hi6401_plug_in_workfunc);

	priv->headset_plug_out_delay_wq =
			create_singlethread_workqueue("headset_plug_out_delay_wq");
	if (!(priv->headset_plug_out_delay_wq)) {
		pr_err("%s : headset_plug_out_delay_wq create failed", __FUNCTION__);
		ret = -ENOMEM;
		goto headset_plug_out_wq_err;
	}
	INIT_DELAYED_WORK(&priv->headset_plug_out_delay_work, hi6401_plug_out_workfunc);

	priv->headset_btn_up_delay_wq =
			create_singlethread_workqueue("headset_btn_up_delay_wq");
	if (!(priv->headset_btn_up_delay_wq)) {
		pr_err("%s : headset_btn_up_delay_wq create failed", __FUNCTION__);
		ret = -ENOMEM;
		goto headset_btn_up_wq_err;
	}
	INIT_DELAYED_WORK(&priv->headset_btn_up_delay_work, hi6401_btnup_workfunc);

	priv->headset_btn_down_delay_wq =
			create_singlethread_workqueue("headset_btn_down_delay_wq");
	if (!(priv->headset_btn_down_delay_wq)) {
		pr_err("%s : headset_btn_down_delay_wq create failed", __FUNCTION__);
		ret = -ENOMEM;
		goto headset_btn_down_wq_err;
	}
	INIT_DELAYED_WORK(&priv->headset_btn_down_delay_work, hi6401_btndown_workfunc);

	/* irq request : button up */
	ret = request_irq(priv->irq[HI6401_IRQ_BTNUP],
			  hi6401_btnup_handler,
			  IRQF_DISABLED, "btnup", priv);
	if (0 > ret)
		goto btnup_err;

	/* irq request : button down */
	ret = request_irq(priv->irq[HI6401_IRQ_BTNDOWN],
			  hi6401_btndown_handler,
			  IRQF_DISABLED, "btndown", priv);
	if (0 > ret)
		goto btndown_err;

	/* irq request : button up(eco mode) */
	ret = request_irq(priv->irq[HI6401_IRQ_BTNUP_ECO],
			  hi6401_btnup_eco_handler,
			  IRQF_DISABLED, "btnup_eco", priv);
	if (0 > ret)
		goto btnup_eco_err;

	/* irq request : button down(eco mode) */
	ret = request_irq(priv->irq[HI6401_IRQ_BTNDOWN_ECO],
			  hi6401_btndown_eco_handler,
			  IRQF_DISABLED, "btndown_eco", priv);
	if (0 > ret)
		goto btndown_eco_err;

	/* irq request : plugin */
	ret = request_irq(priv->irq[HI6401_IRQ_PLUGIN],
			  hi6401_plugin_handler,
			  IRQF_DISABLED, "plugin", priv);
	if (0 > ret)
		goto plugin_err;

	/* irq request : plugout */
	ret = request_irq(priv->irq[HI6401_IRQ_PLUGOUT],
			  hi6401_plugout_handler,
			  IRQF_DISABLED, "plugout", priv);
	if (0 > ret)
		goto plugout_err;


	/* check jack at first time */
	if (check_headset_pluged_in(codec))
		hi6401_plug_in_detect(priv);

	hi6401_clr_irq(codec, HI6401_IRQ_PLUGOUT);
	hi6401_unmask_irq(codec, HI6401_IRQ_PLUGOUT);
	hi6401_clr_irq(codec, HI6401_IRQ_PLUGIN);
	hi6401_unmask_irq(codec, HI6401_IRQ_PLUGIN);

	g_codec = codec;

#ifdef HI6401_CODEC_TOOL
g_codec_for_tool = codec;
#endif

	return ret;

plugout_err:
	free_irq(priv->irq[HI6401_IRQ_PLUGIN], priv);
plugin_err:
	free_irq(priv->irq[HI6401_IRQ_BTNDOWN_ECO], priv);
btndown_eco_err:
	free_irq(priv->irq[HI6401_IRQ_BTNUP_ECO], priv);
btnup_eco_err:
	free_irq(priv->irq[HI6401_IRQ_BTNDOWN], priv);
btndown_err:
	free_irq(priv->irq[HI6401_IRQ_BTNUP], priv);
btnup_err:
	if(priv->headset_btn_down_delay_wq) {
		cancel_delayed_work(&priv->headset_btn_down_delay_work);
		flush_workqueue(priv->headset_btn_down_delay_wq);
		destroy_workqueue(priv->headset_btn_down_delay_wq);
	}
headset_btn_down_wq_err:
	if(priv->headset_btn_up_delay_wq) {
		cancel_delayed_work(&priv->headset_btn_up_delay_work);
		flush_workqueue(priv->headset_btn_up_delay_wq);
		destroy_workqueue(priv->headset_btn_up_delay_wq);
	}
headset_btn_up_wq_err:
	if(priv->headset_plug_out_delay_wq) {
		cancel_delayed_work(&priv->headset_plug_out_delay_work);
		flush_workqueue(priv->headset_plug_out_delay_wq);
		destroy_workqueue(priv->headset_plug_out_delay_wq);
	}
headset_plug_out_wq_err:
	if(priv->headset_plug_in_delay_wq) {
		cancel_delayed_work(&priv->headset_plug_in_delay_work);
		flush_workqueue(priv->headset_plug_in_delay_wq);
		destroy_workqueue(priv->headset_plug_in_delay_wq);
	}
headset_plug_in_wq_err:
	return ret;

}

static int hi6401_soc_remove(struct snd_soc_codec *codec)
{
	struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
	struct anc_hs_data *p_anc_hs = &priv->p_anc_hs;
	int ret;

	BUG_ON(NULL == priv);

	if(priv->headset_btn_down_delay_wq) {
		cancel_delayed_work(&priv->headset_btn_down_delay_work);
		flush_workqueue(priv->headset_btn_down_delay_wq);
		destroy_workqueue(priv->headset_btn_down_delay_wq);
	}
	if(priv->headset_btn_up_delay_wq) {
		cancel_delayed_work(&priv->headset_btn_up_delay_work);
		flush_workqueue(priv->headset_btn_up_delay_wq);
		destroy_workqueue(priv->headset_btn_up_delay_wq);
	}
	if(priv->headset_plug_out_delay_wq) {
		cancel_delayed_work(&priv->headset_plug_out_delay_work);
		flush_workqueue(priv->headset_plug_out_delay_wq);
		destroy_workqueue(priv->headset_plug_out_delay_wq);
	}
	if(priv->headset_plug_in_delay_wq) {
		cancel_delayed_work(&priv->headset_plug_in_delay_work);
		flush_workqueue(priv->headset_plug_in_delay_wq);
		destroy_workqueue(priv->headset_plug_in_delay_wq);
	}
	if(priv->anc_hs_enable) {
		if(p_anc_hs->anc_hs_charge_delay_wq) {
			ret = cancel_delayed_work_sync(&p_anc_hs->anc_hs_charge_delay_work);
			if(ret) {
				pr_info("%s(%u) : make sure no job pending in the queue!\n", __FUNCTION__, __LINE__);
				cancel_delayed_work(&p_anc_hs->anc_hs_charge_delay_work);
			}
			flush_workqueue(p_anc_hs->anc_hs_charge_delay_wq);
			destroy_workqueue(p_anc_hs->anc_hs_charge_delay_wq);
		}
		if(p_anc_hs->anc_hs_btn_delay_wq) {
			cancel_delayed_work(&p_anc_hs->anc_hs_btn_delay_work);
			flush_workqueue(p_anc_hs->anc_hs_btn_delay_wq);
			destroy_workqueue(p_anc_hs->anc_hs_btn_delay_wq);
		}

		gpio_free(p_anc_hs->gpio_mic_sw);
		gpio_free(p_anc_hs->mic_irq_gpio);
		free_irq(p_anc_hs->mic_irq, priv);

#ifdef CONFIG_DEBUG_FS
		debugfs_remove_recursive(debug_dir);
#endif
	}
	free_irq(priv->irq[HI6401_IRQ_PLUGIN], priv);
	free_irq(priv->irq[HI6401_IRQ_PLUGOUT], priv);
	free_irq(priv->irq[HI6401_IRQ_BTNDOWN_ECO], priv);
	free_irq(priv->irq[HI6401_IRQ_BTNUP_ECO], priv);
	free_irq(priv->irq[HI6401_IRQ_BTNDOWN], priv);
	free_irq(priv->irq[HI6401_IRQ_BTNUP], priv);
	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_hi6401 = {
	.probe = hi6401_soc_probe,
	.remove = hi6401_soc_remove,
//	.suspend = hi6401_soc_suspend,
//	.resume = hi6401_soc_resume,
	.read = hi6401_reg_read,
	.write = hi6401_reg_write,

	.controls = hi6401_snd_controls,
	.num_controls = ARRAY_SIZE(hi6401_snd_controls),
	.dapm_widgets = hi6401_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(hi6401_dapm_widgets),
	.dapm_routes = route_map,
	.num_dapm_routes = ARRAY_SIZE(route_map),
};

#ifdef CONFIG_DEBUG_FS
static int hi6401_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	#define Hi6401_SIZE_MAX 2048
	unsigned int i = 0;
	int ret = 0;
	char *buf=(char*)kmalloc(sizeof(char)*Hi6401_SIZE_MAX, GFP_KERNEL);

	if(!buf)
	{
		pr_err("%s : couldn't malloc buffer.\n",__FUNCTION__);
		return -1;
	}

	pr_info("===========hi6401 Page 0 start ===========\n");
	memset( buf, 0, Hi6401_SIZE_MAX);
	for (i = HI6401_PAGE_0_START; i <= HI6401_PAGE_0_END; i++)
	{
		pr_info("%#04x : %#04x", i, hi6401_reg_read(g_codec, i));
		snprintf(buf, Hi6401_SIZE_MAX, "%s%#04x--%#04x\n", buf, i, hi6401_reg_read(g_codec, i));
	}
	snprintf(buf, Hi6401_SIZE_MAX, "%s\n", buf);
	pr_info("===========hi6401 Page 0 end ===========\n");

	pr_info("===========hi6401 Page 1 start ===========\n");
	for (i = HI6401_PAGE_1_START; i <= HI6401_PAGE_1_END; i++)
	{
		pr_info("%#04x : %#04x", i, hi6401_reg_read(g_codec, i));
		snprintf(buf, Hi6401_SIZE_MAX, "%s%#04x--%#04x\n", buf, i, hi6401_reg_read(g_codec, i));
	}
	snprintf(buf, Hi6401_SIZE_MAX, "%s\n", buf);
	pr_info("===========hi6401 Page 1 end ===========\n");
	ret = simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
	kfree(buf);
	return ret;
}

static const struct file_operations hi6401_list_fops = {
	.read =     hi6401_read,
};
#endif

static int hi6401_codec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi6401_priv *priv = NULL;
	int ret = 0;
			
	if (!dev) {
		pr_err("platform_device has no device\n");
		return -ENOENT;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv){
		dev_err(dev, "cannot allocate hi6401 codec platform data\n");
		return -ENOMEM;
	}

	priv->p_irq = dev_get_drvdata(pdev->dev.parent);
	if (!priv->p_irq) {
		dev_err(dev, "get parend device error\n");
		return -ENOENT;
	}

#if 0
	priv->regu.supply = "hi6401-codec";
	ret = devm_regulator_bulk_get(dev, 1, &(priv->regu));
	if (0 != ret) {
		dev_err(dev, "couldn't get regulators %d\n", ret);
		return -ENOENT;
	}
#endif

	priv->irq[HI6401_IRQ_BTNUP] = platform_get_irq_byname(pdev, "btnup");
	if (0 > priv->irq[HI6401_IRQ_BTNUP])
		return -ENOENT;

	priv->irq[HI6401_IRQ_BTNDOWN] = platform_get_irq_byname(pdev, "btndown");
	if (0 > priv->irq[HI6401_IRQ_BTNDOWN])
		return -ENOENT;

	priv->irq[HI6401_IRQ_BTNUP_ECO] = platform_get_irq_byname(pdev, "btnup_eco");
	if (0 > priv->irq[HI6401_IRQ_BTNUP_ECO])
		return -ENOENT;

	priv->irq[HI6401_IRQ_BTNDOWN_ECO] = platform_get_irq_byname(pdev, "btndown_eco");
	if (0 > priv->irq[HI6401_IRQ_BTNDOWN_ECO])
		return -ENOENT;

	priv->irq[HI6401_IRQ_PLUGIN] = platform_get_irq_byname(pdev, "plugin");
	if (0 > priv->irq[HI6401_IRQ_PLUGIN])
		return -ENOENT;

	priv->irq[HI6401_IRQ_PLUGOUT] = platform_get_irq_byname(pdev, "plugout");
	if (0 > priv->irq[HI6401_IRQ_PLUGOUT])
		return -ENOENT;

	/* get pmu audio clk */
	priv->pmu_audio_clk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR(priv->pmu_audio_clk)) {
		pr_err("_clk_get: pmu_audio_clk not found!\n");
		ret = PTR_ERR(priv->pmu_audio_clk);
		return ret;
	}

	priv->need_report_up_event = false;

	platform_set_drvdata(pdev, priv);

	dev_set_name(dev, "hi6401-codec");

#ifdef CONFIG_DEBUG_FS
	if (!debugfs_create_file("hi6401", 0644, NULL, NULL,
				&hi6401_list_fops))
	pr_err("hi6401: Failed to create hi6401 debugfs file\n");
#endif

	return snd_soc_register_codec(dev, &soc_codec_dev_hi6401,
			hi6401_dai, ARRAY_SIZE(hi6401_dai));
}

static int hi6401_codec_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi6401_priv *priv = platform_get_drvdata(pdev);
	devm_clk_put(dev, priv->pmu_audio_clk);
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static void hi6401_codec_shutdown(struct platform_device *pdev)
{
	struct hi6401_priv *priv = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = NULL;

	BUG_ON(NULL == priv);
	codec = priv->codec;
	BUG_ON(NULL == codec);

	if (check_headset_pluged_in(codec)){
		pr_info("hi6401_codec_shutdown with headset\n");
		hi6401_hs_power_off(codec);
	} else {
		pr_info("hi6401_codec_shutdown without headset\n");
	}
}

static struct platform_driver hi6401_codec_driver = {
	.probe	= hi6401_codec_probe,
	.remove	= hi6401_codec_remove,
	.shutdown = hi6401_codec_shutdown,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi6401-codec",
		.of_match_table = of_match_ptr(hi6401_codec_match),
	},
};

module_platform_driver(hi6401_codec_driver);

MODULE_DESCRIPTION("ASoC hi6401 codec driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
