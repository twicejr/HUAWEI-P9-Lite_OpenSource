#ifndef __HI64xx_mbhc_H__
#define __HI64xx_mbhc_H__
#include <sound/jack.h>
#include <linux/switch.h>
#include <linux/wakelock.h>
#include <linux/hisi/hi64xx/hi64xx_irq.h>
#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/hisi/hi64xx/hi64xx_resmgr.h>


enum hisi_jack_states {
	HISI_JACK_NONE = 0,	/* unpluged */
	HISI_JACK_HEADSET,	/* pluged 4-pole headset */
	HISI_JACK_HEADPHONE,	/* pluged 3-pole headphone */
	HISI_JACK_INVERT,	/* pluged invert 4-pole headset */
};

struct hi64xx_mbhc_config {
	/* board defination */
	int hs_det_inv;
	int hs_btn_num;
	int hs_3_pole_min_voltage;
	int hs_3_pole_max_voltage;
	int hs_4_pole_min_voltage;
	int hs_4_pole_max_voltage;
	int btn_play_min_voltage;
	int btn_play_max_voltage;
	int btn_volume_up_min_voltage;
	int btn_volume_up_max_voltage;
	int btn_volume_down_min_voltage;
	int btn_volume_down_max_voltage;
	unsigned int hs_ctrl;
	unsigned int coefficient; /* voltage coefficient*/
};

struct mbhc_reg {
	unsigned int irq_source_reg;
	unsigned int irq_mbhc_2_reg;
	unsigned int ana_60_reg;
	unsigned int saradc_value_reg;
	unsigned int mbhc_vref_reg;
	unsigned int sar_cfg_reg;
	unsigned int micbias_eco_reg;
	unsigned int hsdet_ctrl_reg;
};

/* defination of public data */
struct hi64xx_mbhc {
};

extern int hi64xx_mbhc_init(struct snd_soc_codec *codec,
			struct device_node *node,
			struct mbhc_reg *mbhc_reg,
			struct hi64xx_resmgr *resmgr,
			struct hi64xx_irq *irqmgr,
			struct hi64xx_mbhc **mbhc);

extern void hi64xx_mbhc_deinit(struct hi64xx_mbhc *mbhc);

extern void hi64xx_irq_mask_btn_irqs(struct hi64xx_mbhc *mbhc);
extern void hi64xx_irq_unmask_btn_irqs(struct hi64xx_mbhc *mbhc);
#endif