/*
 * hi64xx_mbhc.c -- hi64xx mbhc driver
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <linux/switch.h>
#include <dsm/dsm_pub.h>
#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/hisi/hi64xx/hi64xx_mbhc.h>
#include <linux/hisi/hi64xx/hi64xx_regs.h>
#include "huawei_platform/audio/anc_hs_interface.h"
#include "huawei_platform/audio/invert_hs.h"

#include "../../../sound/soc/codecs/hs_auto_calib/hs_auto_calib.h"
/*lint -e750*/
#define HI64xx_BTN_MASK	(SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2)

static int hi64xx_btn_bits[] = {
	IRQ_BTNUP_COMP1,
	IRQ_BTNDOWN_COMP1,
	IRQ_BTNUP_COMP2,
	IRQ_BTNDOWN_COMP2,
	IRQ_BTNUP_ECO,
	IRQ_BTNDOWN_ECO,
};

/* defination of private data */
struct hi64xx_mbhc_priv {
	struct hi64xx_mbhc mbhc_pub;
	struct snd_soc_codec *codec;
	struct hi64xx_resmgr *resmgr;
	struct hi64xx_irq *irqmgr;
	struct miscdevice miscdev;
	struct wake_lock wake_lock;
	struct wake_lock micbias_wake_lock;
	struct mutex plug_mutex;
	struct mutex status_mutex;
	struct mutex saradc_mutex;
	struct workqueue_struct *micbias_delay_wq;
	struct delayed_work micbias_delay_work;
	bool	mbhc_micbias_work;
	/* headset status */
	enum hisi_jack_states hs_status;
	int btn_report;
	int need_match_micbias;

#ifdef CONFIG_SWITCH
	struct switch_dev sdev;
#endif
	/* board defination */
	struct hi64xx_mbhc_config mbhc_config;
	struct mbhc_reg mbhc_reg;
};

static struct snd_soc_jack hs_jack;
void hi64xx_soc_jack_report(int report, int mask)
{
	snd_soc_jack_report(&hs_jack, report, mask);
}

void hi64xx_irq_mask_btn_irqs(struct hi64xx_mbhc *mbhc)
{
	int irq_num = sizeof(hi64xx_btn_bits)/sizeof(int);
	int *phy_irqs = hi64xx_btn_bits;

	struct hi64xx_mbhc_priv *priv =
		(struct hi64xx_mbhc_priv*)mbhc;

	if (priv == NULL) {
		pr_err("%s: null pointer \n", __FUNCTION__);
		return;
	}

	hi64xx_irq_disable_irqs(priv->irqmgr, irq_num, phy_irqs);
}

void hi64xx_irq_unmask_btn_irqs(struct hi64xx_mbhc *mbhc)
{
	int irq_num = sizeof(hi64xx_btn_bits)/sizeof(int);
	int *phy_irqs = hi64xx_btn_bits;

	struct hi64xx_mbhc_priv *priv =
		(struct hi64xx_mbhc_priv*)mbhc;

	if (priv == NULL) {
		pr_err("%s: null pointer \n", __FUNCTION__);
		return;
	}

	hi64xx_irq_enable_irqs(priv->irqmgr, irq_num, phy_irqs);
}

void hi64xx_micbias_work_func(struct work_struct *work)
{
	struct hi64xx_mbhc_priv *priv = container_of(work, struct hi64xx_mbhc_priv, micbias_delay_work.work);
	/* hs micbias off */
	hi64xx_resmgr_release_micbias(priv->resmgr);
}

void hi64xx_irq_micbias_mbhc_enable(struct hi64xx_mbhc_priv *priv, bool enable)
{
	int ret = 0;
	if (enable) {
		/* hs micbias on */
		hi64xx_resmgr_request_micbias(priv->resmgr);
	} else {
		/* hs micbias pd */
		wake_lock_timeout(&priv->micbias_wake_lock, msecs_to_jiffies(3500));
		ret = mod_delayed_work(priv->micbias_delay_wq,
			&priv->micbias_delay_work,
			msecs_to_jiffies(3000));
		if (ret != 0) {
			hi64xx_resmgr_release_micbias(priv->resmgr);
		}
	}

	return;
}

void hi64xx_jack_report(struct hi64xx_mbhc_priv *priv)
{
	enum hisi_jack_states jack_status = priv->hs_status;
	int jack_report = 0;

	switch(priv->hs_status) {
	case HISI_JACK_NONE:
		jack_report = 0;
		pr_info("%s : plug out\n", __FUNCTION__);
		break;
	case HISI_JACK_HEADSET:
		jack_report = SND_JACK_HEADSET;
		pr_info("%s : 4-pole headset plug in\n", __FUNCTION__);
		break;
	case HISI_JACK_INVERT:
		jack_report = SND_JACK_HEADPHONE;
		pr_info("%s : invert headset plug in\n", __FUNCTION__);
		break;
	case HISI_JACK_HEADPHONE:
		jack_report = SND_JACK_HEADPHONE;
		pr_info("%s : 3-pole headphone plug in\n", __FUNCTION__);
		break;
	default:
		pr_err("%s : error hs_status(%d)\n", __FUNCTION__, priv->hs_status);
		break;
	}

	/* clear btn event */
	hi64xx_soc_jack_report(0, HI64xx_BTN_MASK);
	/* btn_report jack status */
	hi64xx_soc_jack_report(jack_report, SND_JACK_HEADSET);

#ifdef CONFIG_SWITCH
	switch_set_state(&priv->sdev, jack_status);
#endif
}

static inline bool check_headset_pluged_in(struct hi64xx_mbhc_priv *priv)
{
#ifdef CONFIG_ANC_HS_INTERFACE
	int ret = anc_hs_interface_check_headset_pluged_in();

	if(ret == NO_MAX14744) {
		/*
		* 0 : means headset is pluged out
		* 1 : means headset is pluged in
		*/
		pr_info("max14744 NO_MAX14744");
		return (0 != (snd_soc_read(priv->codec, priv->mbhc_reg.irq_source_reg) & (1 << HI64xx_PLUGIN_IRQ_BIT)));
	} else if(ret == HANDSET_PLUG_IN) {
		pr_info("max14744 HANDSET_PLUG_IN");
		return true;
	} else{
		pr_info("max14744 HANDSET_PLUG_OUT");
		return false;
	}
#else
	return (0 != (snd_soc_read(priv->codec, priv->mbhc_reg.irq_source_reg) & (1 << HI64xx_PLUGIN_IRQ_BIT)));
#endif

}

static inline bool check_saradc_value_ready_detect(struct hi64xx_mbhc_priv *priv)
{
	/* read codec status */
	int value = snd_soc_read(priv->codec, priv->mbhc_reg.irq_mbhc_2_reg) & (1 << HI64xx_SARADC_RD_BIT);

	/*clr irq*/
	snd_soc_write(priv->codec, priv->mbhc_reg.irq_mbhc_2_reg, 0x04);

	if (0 == value)
		return false;

	return true;
}

static int hi64xx_read_saradc_value_detect(struct hi64xx_mbhc_priv *priv)
{
	int retry = 3;
	int reg_value = 0;

	mutex_lock(&priv->saradc_mutex);

	/* saradc on */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_SARADC_PD_BIT, 0);
	/* start saradc */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_SAR_START_BIT, 1 << HI64xx_SAR_START_BIT);

	while(retry--) {
		usleep_range(1000, 1100);
		if (check_saradc_value_ready_detect(priv)) {
			reg_value = snd_soc_read(priv->codec, priv->mbhc_reg.saradc_value_reg);
			pr_info("%s : saradc value is %#x\n", __FUNCTION__, reg_value);
			break;
		}
	}

	if (0 > retry)
		pr_err("%s : get saradc value err, set as 0\n", __FUNCTION__);

	/* end saradc */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_SAR_START_BIT, 0);
	/* saradc pd */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_SARADC_PD_BIT, 1 << HI64xx_SARADC_PD_BIT);

	mutex_unlock(&priv->saradc_mutex);

	return (reg_value * (priv->mbhc_config.coefficient) / 0xFF);
}

void hi64xx_mbhc_on(struct hi64xx_mbhc_priv *priv)
{
	/* mask btn irqs */
	hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);

	/* open mbhc */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.mbhc_vref_reg, 1 << HI64xx_MBHC_VREF_BIT, 0);
	/* saradc cfg */
	snd_soc_write(priv->codec,  priv->mbhc_reg.sar_cfg_reg, 0x7C);
	/* mbhc on */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_MBHC_ON_BIT, 0);

	msleep(30);

	/* unmask btn irqs */
	hi64xx_irq_unmask_btn_irqs(&priv->mbhc_pub);

	msleep(120);

	return;
}

void hi64xx_plug_in_detect(struct hi64xx_mbhc_priv *priv)
{
	int saradc_value = 0;
	int anc_type = ANC_HS_REVERT_4POLE;

	if (!check_headset_pluged_in(priv))
		return;

	wake_lock(&priv->wake_lock);
	mutex_lock(&priv->plug_mutex);

#ifdef CONFIG_ANC_HS_INTERFACE
	if(check_anc_hs_interface_support()) {
		//mask btn irqs while control boost
		hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);
		anc_hs_interface_start_charge();
	}
#endif

	/* micbias on */
	hi64xx_irq_micbias_mbhc_enable(priv, true);

	/* mbhc on (normal not auto) */
	hi64xx_mbhc_on(priv);
	/* read hs value */
	saradc_value = hi64xx_read_saradc_value_detect(priv);

	mutex_lock(&priv->status_mutex);

	if (priv->mbhc_config.hs_3_pole_max_voltage >= saradc_value) {
		/* 3-pole headphone */
		pr_info("%s : 3 pole is pluged in\n", __FUNCTION__);
		priv->hs_status = HISI_JACK_HEADPHONE;
		anc_type = ANC_HS_NORMAL_3POLE;
	} else if (priv->mbhc_config.hs_4_pole_min_voltage <= saradc_value &&
			priv->mbhc_config.hs_4_pole_max_voltage >= saradc_value) {
		/* 4-pole headset */
		pr_info("%s : 4 pole is pluged in\n", __FUNCTION__);
		priv->hs_status = HISI_JACK_HEADSET;
		anc_type = ANC_HS_NORMAL_4POLE;
	} else {
		/* invert 4-pole headset */
		pr_info("%s : need further detect, report as 3-pole headphone,adc_v:%d\n", __FUNCTION__, saradc_value);
		priv->hs_status = HISI_JACK_INVERT;
		anc_type = ANC_HS_REVERT_4POLE;

#ifdef INVERT_HEADSET
		/* real invert headset */
		if(priv->mbhc_config.hs_4_pole_min_voltage > saradc_value) {
			invert_hs_control(INVERT_HS_MIC_GND_CONNECT);
		}
#endif
	}

	mutex_unlock(&priv->status_mutex);

#ifdef CONFIG_ANC_HS_INTERFACE
	if(check_anc_hs_interface_support()  && priv->hs_status == HISI_JACK_HEADSET) {
		//mask btn irqs while control boost
		hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);
		anc_hs_interface_charge_detect(saradc_value, anc_type);
		hi64xx_irq_unmask_btn_irqs(&priv->mbhc_pub);
	}

	anc_hs_interface_refresh_headset_type(anc_type);
	/* real invert headset */
	if((priv->mbhc_config.hs_4_pole_min_voltage > saradc_value) && (priv->hs_status == HISI_JACK_INVERT)) {
		anc_hs_interface_invert_hs_control(ANC_HS_MIC_GND_CONNECT);
	}
#endif
	if(priv->need_match_micbias == 1) {
		hi64xx_irq_micbias_mbhc_enable(priv, false);
		priv->need_match_micbias = 0;
	}

	if(priv->mbhc_config.hs_4_pole_max_voltage > saradc_value) {
		hi64xx_jack_report(priv);
		/* micbias off */
		hi64xx_irq_micbias_mbhc_enable(priv, false);
	} else {
		priv->need_match_micbias = 1;
	}

	mutex_unlock(&priv->plug_mutex);
	wake_unlock(&priv->wake_lock);
}

void hi64xx_btn_down(struct hi64xx_mbhc_priv *priv)
{
	int saradc_value = 0;

	if (!check_headset_pluged_in(priv)) {
		pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
		return;
	}

	wake_lock(&priv->wake_lock);

	if (HISI_JACK_HEADSET == priv->hs_status) {
		/* micbias on */
		hi64xx_irq_micbias_mbhc_enable(priv, true);

		/* auto read */
		saradc_value = hi64xx_read_saradc_value_detect(priv);

		/* micbias off */
		hi64xx_irq_micbias_mbhc_enable(priv, false);

		msleep(30);

		if (!check_headset_pluged_in(priv)) {
			pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
			goto end;
		}

		if ((saradc_value >= priv->mbhc_config.hs_4_pole_min_voltage) && (saradc_value <= priv->mbhc_config.hs_4_pole_max_voltage)) {
			pr_info("%s(%u) : process as btn up! \n", __FUNCTION__, __LINE__);
			mutex_lock(&priv->status_mutex);
			priv->btn_report = 0;
			mutex_unlock(&priv->status_mutex);
		} else if ((saradc_value >= priv->mbhc_config.btn_play_min_voltage) && (saradc_value <= priv->mbhc_config.btn_play_max_voltage)) {
			mutex_lock(&priv->status_mutex);
			priv->btn_report = SND_JACK_BTN_0;
			mutex_unlock(&priv->status_mutex);
		} else if (priv->mbhc_config.btn_volume_up_min_voltage < saradc_value && saradc_value <= priv->mbhc_config.btn_volume_up_max_voltage) {
			mutex_lock(&priv->status_mutex);
			priv->btn_report = SND_JACK_BTN_1;
			mutex_unlock(&priv->status_mutex);
		} else if (priv->mbhc_config.btn_volume_down_min_voltage < saradc_value && saradc_value <= priv->mbhc_config.btn_volume_down_max_voltage) {
			mutex_lock(&priv->status_mutex);
			priv->btn_report = SND_JACK_BTN_2;
			mutex_unlock(&priv->status_mutex);
		} else {
			msleep(30);
			hi64xx_plug_in_detect(priv);
			goto end;
		}

		if (!check_headset_pluged_in(priv)) {
			pr_info("%s(%u) : hs pluged out \n", __FUNCTION__, __LINE__);
			goto end;
		}
		startup_FSM(REC_JUDGE, saradc_value, &(priv->btn_report));
		/*btn_report key event*/
		pr_info("%s(%u): btn_report type = 0x%x, status=0x%x\n",
				__FUNCTION__, __LINE__, priv->btn_report, priv->hs_status);
		hi64xx_soc_jack_report(priv->btn_report, HI64xx_BTN_MASK);
	}

end:
	wake_unlock(&priv->wake_lock);

	return;
}

static irqreturn_t hi64xx_plugin_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	msleep(800);

	hi64xx_plug_in_detect(priv);

	return IRQ_HANDLED;
}

void hi64xx_plug_out_detect(struct hi64xx_mbhc_priv *priv)
{
	BUG_ON(NULL == priv);

	if (check_headset_pluged_in(priv)) {
		pr_info("%s : hs still plugin \n", __FUNCTION__);
		return;
	}

	mutex_lock(&priv->plug_mutex);

	cancel_delayed_work(&priv->micbias_delay_work);
	flush_workqueue(priv->micbias_delay_wq);

	hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);

#ifdef INVERT_HEADSET
	invert_hs_control(INVERT_HS_MIC_GND_DISCONNECT);
#endif

	//stop charge first
#ifdef CONFIG_ANC_HS_INTERFACE
	anc_hs_interface_stop_charge();

	anc_hs_interface_invert_hs_control(ANC_HS_MIC_GND_DISCONNECT);
#endif

	/* eco off */
	hi64xx_update_bits(priv->codec,  priv->mbhc_reg.micbias_eco_reg,  1 << HI64xx_MICBIAS_ECO_ON_BIT, 0);

	hi64xx_resmgr_force_release_micbias(priv->resmgr);
	priv->need_match_micbias = 0;

	hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);

	/* eco off */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.micbias_eco_reg,  1 << HI64xx_MICBIAS_ECO_ON_BIT, 0);
	pr_info("%s : eco disable \n", __FUNCTION__);
	/* vref off */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.mbhc_vref_reg, 1 << HI64xx_MBHC_VREF_BIT, 1 << HI64xx_MBHC_VREF_BIT);
	/* mbhc cmp off */
	hi64xx_update_bits(priv->codec, priv->mbhc_reg.ana_60_reg, 1 << HI64xx_MBHC_ON_BIT, 1 << HI64xx_MBHC_ON_BIT);

	mutex_lock(&priv->status_mutex);
	priv->hs_status = HISI_JACK_NONE;
	priv->btn_report = 0;
	mutex_unlock(&priv->status_mutex);
	headset_auto_calib_reset_interzone();
	hi64xx_jack_report(priv);

	mutex_unlock(&priv->plug_mutex);
}

static irqreturn_t hi64xx_plugout_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	hi64xx_plug_out_detect(priv);

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btnup_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	if (!check_headset_pluged_in(priv))
		return IRQ_HANDLED;

	if (HISI_JACK_INVERT == priv->hs_status) {
		pr_info("%s: further detect\n", __FUNCTION__);
		/* further detect */
		hi64xx_plug_in_detect(priv);
	} else if (0 == priv->btn_report) {
		if (HISI_JACK_HEADSET != priv->hs_status) {
			/* further detect */
			hi64xx_plug_in_detect(priv);
		}
		return IRQ_HANDLED;
	} else {
		mutex_lock(&priv->status_mutex);
		priv->btn_report = 0;
		hi64xx_soc_jack_report(priv->btn_report, HI64xx_BTN_MASK);
		mutex_unlock(&priv->status_mutex);
		pr_info("%s(%u) : btn up !\n", __FUNCTION__, __LINE__);
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btndown_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	pr_err("%s: btn down \n", __FUNCTION__);

	hi64xx_btn_down(priv);

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btnup_comp2_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	pr_info("%s: btn up comp2 \n", __FUNCTION__);

	if(priv->hs_status == HISI_JACK_HEADSET) {
		msleep(30);
		hi64xx_plug_in_detect(priv);
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btndown_comp2_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	pr_info("%s: btn down comp2 \n", __FUNCTION__);

	if(priv->hs_status == HISI_JACK_INVERT) {
		msleep(30);
		hi64xx_plug_in_detect(priv);
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btnup_eco_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	if (!check_headset_pluged_in(priv))
		return IRQ_HANDLED;

	wake_lock_timeout(&priv->wake_lock, 100);

	if (HISI_JACK_INVERT == priv->hs_status) {
		pr_err("%s: further detect\n", __FUNCTION__);
		/* further detect */
		hi64xx_plug_in_detect(priv);
	} else if (0 == priv->btn_report){
		if (HISI_JACK_HEADSET != priv->hs_status) {
			/* further detect */
			hi64xx_plug_in_detect(priv);
		}
		return IRQ_HANDLED;
	} else {
		mutex_lock(&priv->status_mutex);
		priv->btn_report = 0;
		hi64xx_soc_jack_report(priv->btn_report, HI64xx_BTN_MASK);
		mutex_unlock(&priv->status_mutex);
		pr_info("%s(%u) : btn up !\n", __FUNCTION__, __LINE__);
	}

	return IRQ_HANDLED;
}

static irqreturn_t hi64xx_btndown_eco_handler(int irq, void *data)
{
	struct hi64xx_mbhc_priv *priv =
			(struct hi64xx_mbhc_priv *)data;

	BUG_ON(NULL == priv);

	pr_err("%s: btn down \n", __FUNCTION__);

	hi64xx_btn_down(priv);

	return IRQ_HANDLED;
}

static bool hi64xx_check_headset_in(void *priv)
{
	return check_headset_pluged_in((struct hi64xx_mbhc_priv *)priv);
}

/* ToDo: this interface will be omitted */
static void hi64xx_resume_lock(void *priv, bool lock)
{

}

static void plug_in_detect(void *priv)
{
    struct hi64xx_mbhc_priv * di = (struct hi64xx_mbhc_priv *)priv;

	hi64xx_irq_resume_wait(di->irqmgr);
    hi64xx_plug_in_detect(di);
}

static void plug_out_detect(void *priv)
{
    struct hi64xx_mbhc_priv * di = (struct hi64xx_mbhc_priv *)priv;

	hi64xx_irq_resume_wait(di->irqmgr);
    hi64xx_plug_out_detect(di);
}

#ifdef CONFIG_ANC_HS_INTERFACE
static struct anc_hs_dev anc_dev = {
	.name = "anc_hs",
	.ops = {
		.check_headset_in = hi64xx_check_headset_in,
		.btn_report = hi64xx_soc_jack_report,
		.codec_resume_lock = hi64xx_resume_lock,
		.plug_in_detect = plug_in_detect,
		.plug_out_detect = plug_out_detect,
	},
};
#endif

static void hi64xx_mbhc_config_set(struct device_node *node, struct hi64xx_mbhc_config *mbhc_config)
{
	int temp = 0;

	if (!of_property_read_u32(node, "hisilicon,hs_det", &temp))
		mbhc_config->hs_det_inv = temp;
	else
		mbhc_config->hs_det_inv = 0;

	if (!of_property_read_u32(node, "hisilicon,hs_ctrl", &temp))
		mbhc_config->hs_ctrl = temp;
	else
		mbhc_config->hs_ctrl = 0x19;

	if (!of_property_read_u32(node, "hisilicon,coefficient", &temp))
		mbhc_config->coefficient = temp;
	else
		mbhc_config->coefficient = 2800; /* saradc range 0 ~ 2800mV */

	if (!of_property_read_u32(node, "hisilicon,hs_3_pole_min_voltage", &temp))
		mbhc_config->hs_3_pole_min_voltage = temp;
	else
		mbhc_config->hs_3_pole_min_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,hs_3_pole_max_voltage", &temp))
		mbhc_config->hs_3_pole_max_voltage = temp;
	else
		mbhc_config->hs_3_pole_max_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,hs_4_pole_min_voltage", &temp))
		mbhc_config->hs_4_pole_min_voltage = temp;
	else
		mbhc_config->hs_4_pole_min_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,hs_4_pole_max_voltage", &temp))
		mbhc_config->hs_4_pole_max_voltage = temp;
	else
		mbhc_config->hs_4_pole_max_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_play_min_voltage", &temp))
		mbhc_config->btn_play_min_voltage = temp;
	else
		mbhc_config->btn_play_min_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_play_max_voltage", &temp))
		mbhc_config->btn_play_max_voltage = temp;
	else
		mbhc_config->btn_play_max_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_volume_up_min_voltage", &temp))
		mbhc_config->btn_volume_up_min_voltage = temp;
	else
		mbhc_config->btn_volume_up_min_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_volume_up_max_voltage", &temp))
		mbhc_config->btn_volume_up_max_voltage = temp;
	else
		mbhc_config->btn_volume_up_max_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_volume_down_min_voltage", &temp))
		mbhc_config->btn_volume_down_min_voltage = temp;
	else
		mbhc_config->btn_volume_down_min_voltage = 0;

	if (!of_property_read_u32(node, "hisilicon,btn_volume_down_max_voltage", &temp))
		mbhc_config->btn_volume_down_max_voltage = temp;
	else
		mbhc_config->btn_volume_down_max_voltage = 0;

	headset_auto_calib_init(node);
}

int hi64xx_mbhc_init(struct snd_soc_codec *codec,
		struct device_node *node,
		struct mbhc_reg *mbhc_reg,
		struct hi64xx_resmgr *resmgr,
		struct hi64xx_irq *irqmgr,
		struct hi64xx_mbhc **mbhc)
{
	int ret = 0;
	struct hi64xx_mbhc_priv *priv = kzalloc(sizeof(struct hi64xx_mbhc_priv), GFP_KERNEL);
	if (!priv) {
		ret = -ENOMEM;
		return ret;
	}

	memcpy(&priv->mbhc_reg, mbhc_reg, sizeof(struct mbhc_reg));
	hi64xx_mbhc_config_set(node, &priv->mbhc_config);
	priv->codec = codec;
	priv->resmgr = resmgr;
	priv->irqmgr = irqmgr;
	*mbhc = &priv->mbhc_pub;

	priv->need_match_micbias = 0;

#ifdef CONFIG_SWITCH
	priv->sdev.name = "h2w";
	ret = switch_dev_register(&priv->sdev);
	if (ret) {
		pr_err("%s : error registering switch device %d\n", __FUNCTION__, ret);
		goto err_exit;
	}
#endif

	wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hisi-64xx-mbhc");
	wake_lock_init(&priv->micbias_wake_lock, WAKE_LOCK_SUSPEND, "hisi-64xx-mbhc-micbias");
	mutex_init(&priv->plug_mutex);
	mutex_init(&priv->status_mutex);
	mutex_init(&priv->saradc_mutex);

	priv->micbias_delay_wq = create_singlethread_workqueue("hi64xx_micbias_delay_wq");
	if (!(priv->micbias_delay_wq)) {
		pr_err("%s(%u) : workqueue create failed", __FUNCTION__,__LINE__);
		goto mic_delay_wq_exit;
	}
	INIT_DELAYED_WORK(&priv->micbias_delay_work, hi64xx_micbias_work_func);
	priv->mbhc_micbias_work = false;

	/* register anc hs first */
#ifdef CONFIG_ANC_HS_INTERFACE
	anc_hs_interface_dev_register(&anc_dev, priv);
#endif

	/* register headset jack */
	ret = snd_soc_jack_new(codec, "Headset Jack", SND_JACK_HEADSET, &hs_jack);
	if (ret) {
		pr_err("%s %d: jack error, errornum = %d\n", __FUNCTION__, __LINE__, ret);
		goto jack_exit;
	}

	/* register headset button */
	ret = snd_jack_set_key(hs_jack.jack, SND_JACK_BTN_0, KEY_MEDIA);
	if (ret) {
		pr_err("%s %d: jack error, errornum = %d\n", __FUNCTION__,  __LINE__, ret);
		goto jack_exit;
	}
	ret = snd_jack_set_key(hs_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	if (ret) {
		pr_err("%s %d: jack error, errornum = %d\n", __FUNCTION__,  __LINE__, ret);
		goto jack_exit;
	}
	ret = snd_jack_set_key(hs_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	if (ret) {
		pr_err("%s %d: jack error, errornum = %d\n", __FUNCTION__,  __LINE__, ret);
		goto jack_exit;
	}
	/* for sound triger */
	ret = snd_jack_set_key(hs_jack.jack, SND_JACK_BTN_5, KEY_F14);
	if (ret) {
		pr_err("%s %d: jack error, errornum = %d\n", __FUNCTION__,  __LINE__, ret);
		goto jack_exit;
	}

	/* irq request : plugout */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_PLUGOUT, hi64xx_plugout_handler, "plugout", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_plugout_exit;
	}

	/* irq request : plugin */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_PLUGIN, hi64xx_plugin_handler, "plugin", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_plugin_exit;
	}

	/* irq request : button up(eco mode) */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNUP_ECO, hi64xx_btnup_eco_handler, "btnup_eco", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btnupeco_exit;
	}

	/* irq request : button down(eco mode) */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNDOWN_ECO, hi64xx_btndown_eco_handler, "btndown_eco", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btndowneco_exit;
	}

	/* irq request : button down */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNDOWN_COMP1, hi64xx_btndown_handler, "btndown_comp1", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btndowncomp1_exit;
	}

	/* irq request : button up */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNUP_COMP1, hi64xx_btnup_handler, "btnup_comp1", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btnupcomp1_exit;
	}

	/* irq request : comp2 button down */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNDOWN_COMP2, hi64xx_btndown_comp2_handler, "btndown_comp2", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btndowncomp2_exit;
	}

	/* irq request : comp2 button up */
	ret = hi64xx_irq_request_irq(irqmgr, IRQ_BTNUP_COMP2, hi64xx_btnup_comp2_handler, "btnup_comp2", priv);
	if (0 != ret) {
		pr_err("%s %d: hi64xx_irq_request_irq fail. err code is %x .\n", __FUNCTION__, __LINE__, ret);
		goto irq_btnupcomp2_exit;
	}

	/* mask btn irqs */
	hi64xx_irq_mask_btn_irqs(&priv->mbhc_pub);
	/* enable hsdet */
	snd_soc_write(codec, priv->mbhc_reg.hsdet_ctrl_reg, priv->mbhc_config.hs_ctrl);
	snd_soc_write(codec, priv->mbhc_reg.mbhc_vref_reg, 0x8E);

	/* check jack at first time */
	if (check_headset_pluged_in(priv))
		hi64xx_plug_in_detect(priv);

	return ret;

irq_btnupcomp2_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNDOWN_COMP2, priv);
irq_btndowncomp2_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNUP_COMP1, priv);
irq_btnupcomp1_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNDOWN_COMP1, priv);
irq_btndowncomp1_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNDOWN_ECO, priv);
irq_btndowneco_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNUP_ECO, priv);
irq_btnupeco_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLUGIN, priv);
irq_plugin_exit:
	hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLUGOUT, priv);
irq_plugout_exit:
jack_exit:
	if (NULL != priv->micbias_delay_wq) {
		cancel_delayed_work(&priv->micbias_delay_work);
		flush_workqueue(priv->micbias_delay_wq);
		destroy_workqueue(priv->micbias_delay_wq);
		priv->micbias_delay_wq = NULL;
	}
mic_delay_wq_exit:
	wake_lock_destroy(&priv->wake_lock);
	mutex_destroy(&priv->plug_mutex);
	mutex_destroy(&priv->status_mutex);
	mutex_destroy(&priv->saradc_mutex);
err_exit:
	kfree(priv);
	return ret;
}

void hi64xx_mbhc_deinit(struct hi64xx_mbhc *mbhc)
{
	struct hi64xx_mbhc_priv* priv =
		(struct hi64xx_mbhc_priv*)mbhc;

	if (priv == NULL)
		return;

	if (priv->irqmgr) {
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLUGOUT, priv);
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLUGIN, priv);
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNUP_ECO, priv);
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNDOWN_ECO, priv);
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNDOWN_COMP1, priv);
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_BTNUP_COMP1, priv);
	}

	wake_lock_destroy(&priv->wake_lock);
	mutex_destroy(&priv->plug_mutex);
	mutex_destroy(&priv->status_mutex);
	mutex_destroy(&priv->saradc_mutex);

	if (NULL != priv->micbias_delay_wq) {
		cancel_delayed_work(&priv->micbias_delay_work);
		flush_workqueue(priv->micbias_delay_wq);
		destroy_workqueue(priv->micbias_delay_wq);
		priv->micbias_delay_wq = NULL;
	}

	kfree(priv);
}

MODULE_DESCRIPTION("hi64xx_mbhc");
MODULE_AUTHOR("guzhengming <guzhengming@hisilicon.com>");
MODULE_LICENSE("GPL");
