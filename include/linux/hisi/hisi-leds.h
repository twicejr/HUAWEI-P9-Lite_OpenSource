/*
 * leds-k3.h - platform data structure for k3 led controller
 *
 * Copyright (C) 2009 Antonio Ospite <hisik3>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __LINUX_LEDS_k3_H
#define __LINUX_LEDS_k3_H
#include <linux/leds.h>
#define HISI_LEDS "hisi_leds"

#define HISI_LED0 0
#define HISI_LED1 1
#define HISI_LED2 2


#define HISI_LEDS_MAX 3

#define DR_LED_CTRL   (0x98) /* DR3,4,5 control registers */
#define DR_OUT_CTRL   (0x99) /* DR3,4,5 out_put control registers */

#define DR3_ISET      (0x9A) /* DR3 current select */
#define DR3_START_DEL (0x9B) /* dr3 start delay */
#define DR3_TIM_CONF0 (0xA0) /* dr3 delay_on and delay_off */
#define DR3_TIM_CONF1 (0xA1) /* dr3  rise and fall */

#define DR4_ISET      (0x9C) /* DR4 current select */
#define DR4_START_DEL (0x9D) /* dr4 start delay */
#define DR4_TIM_CONF0 DR3_TIM_CONF0 /* dr4 delay_on and delay_off */
#define DR4_TIM_CONF1 DR3_TIM_CONF1 /* dr4  rise and fall */

#define DR5_ISET      (0x9E)  /* DR4 current select */
#define DR5_START_DEL (0x9F)  /* dr5 start delay */
#define DR5_TIM_CONF0 DR3_TIM_CONF0 /* dr5 delay_on and delay_off */
#define	DR5_TIM_CONF1 DR3_TIM_CONF1 /* dr5  rise and fall */

#define	DELAY_ON		1
#define	DELAY_OFF		0

#define	DEL_0			0
#define	DEL_1			1
#define	DEL_250			250
#define DEL_512			512
#define DEL_500			500
#define DEL_1000		1000
#define DEL_2000		2000
#define DEL_TIME		3000
#define DEL_4000		4000
#define DEL_6000		6000
#define DEL_8000		8000
#define DEL_12000		12000
#define DEL_14000		14000
#define DEL_16000		16000


#define	DR_DEL01		0x01
#define	DR_DEL02		0x02
#define	DR_DEL03		0x03
#define	DR_DEL04		0x04
#define	DR_DEL05		0x05
#define	DR_DEL06		0x06
#define	DR_DEL07		0x07
#define	DR_DEL08		0x08
#define	DR_DEL09		0x09
#define	DR_DELAY_ON		0xF0

#define	DR3_ENABLE		0x01  /* dr3 enable */
#define	DR3_DISABLE		0xFE  /* dr3 disable */

#define	DR4_ENABLE		0x02  /* dr4 enable  */
#define	DR4_DISABLE		0xFD  /* dr4 disable */

#define	DR5_ENABLE		0x04  /* dr5 enable */
#define	DR5_DISABLE		0xFB  /* dr5 disable */

#define	DR3_OUT_ENABLE	0xFC  /* dr3 out_put enable */
#define	DR4_OUT_ENABLE	0xF3  /* dr4 out_put enable */
#define	DR5_OUT_ENABLE	0xCF  /* dr5 out_put enable */

#define	DR_BRIGHTNESS_HALF	0x1  /* dr3,4,5 half_brightness config */
#define	DR_BRIGHTNESS_FULL	0x7  /* dr3,4,5 full_brightness config */

#define	DR_START_DEL_512    0x03 /* start_delay */

#define	DR_CONTR_DISABLE	0xF8 /* dr3,4,5 disable */

struct led_set_config {
	u8 brightness_set;
	u32 hisi_led_iset_address;
	u32 hisi_led_start_address;
	u32 hisi_led_tim_address;
	u32 hisi_led_tim1_address;
	unsigned long hisi_led_dr_ctl;
	unsigned long hisi_led_dr_out_ctl;
};

struct led_status {
	enum led_brightness brightness;
	unsigned long delay_on;
	unsigned long delay_off;
};

struct hisi_led_data {
	u8 id;

	struct led_classdev ldev;
	struct led_status status;
};

struct hisi_led_drv_data {
	struct mutex lock;
	struct clk	*clk;
	void __iomem *hisi_led_base;
	struct hisi_led_data leds[HISI_LEDS_MAX];
};

struct hisi_led {
	const char *name;
	enum led_brightness brightness;
	unsigned long delay_on;
	unsigned long delay_off;
	char *default_trigger;
};

struct hisi_led_platform_data {
	struct hisi_led leds[HISI_LEDS_MAX];
	u8 leds_size;
};

#endif /* __LINUX_LEDS_K3_H */

