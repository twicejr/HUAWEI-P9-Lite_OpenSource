/*
 * hisi_hi6421-leds.h - platform data structure for k3 led controller
 *
 * Copyright (c) 2011-2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __LINUX_LEDS_k3_H
#define __LINUX_LEDS_k3_H
#include <linux/leds.h>
#define K3_LEDS "k3_leds"

#define K3_LED0 		0
#define K3_LED1 		1
#define K3_LED2 		2


#define K3_LEDS_MAX 	3

#define DR_LED_CTRL   (0xCD << 2) 		/* DR3,4,5 control registers */
#define DR_LED_ISET   (0xCE << 2) 		/* DR4,5 iset regulate registers */
#define DR_OUT_CTRL   (0xCF << 2)		/* DR3,4,5 out_put control registers */

#define DR3_START_DEL (0xD0 << 2) 		/* dr3 start delay */
#define DR3_TIM_CONF0 (0xD1 << 2)		/* dr3 delay_on and delay_off */
#define DR3_TIM_CONF1 (0xD2 << 2)		/* dr3 rise and fall */

#define DR4_START_DEL (0xD3 << 2)		/* dr4 start delay */
#define DR4_TIM_CONF0 (0xD4 << 2)		/* dr4 delay_on and delay_off */
#define DR4_TIM_CONF1 (0xD5 << 2)		/* dr4 rise and fall */

#define DR5_START_DEL (0xD6 << 2)		/* dr5 start delay */
#define DR5_TIM_CONF0 (0xD7 << 2)		/* dr5 delay_on and delay_off */
#define DR5_TIM_CONF1 (0xD8 << 2)		/* dr5 rise and fall */

#define DELAY_ON		1
#define DELAY_OFF	0

#define DEL_0		0
#define DEL_125		125
#define DEL_250		250
#define DEL_500		500
#define DEL_1000		1000
#define DEL_2000		2000
#define DEL_2850		2850
#define DEL_3000		3000
#define DEL_4000		4000
#define DEL_6000		6000
#define DEL_8000		8000
#define DEL_12000		12000
#define DEL_14000		14000
#define DEL_16000		16000

#define DR_DEL00		0x00
#define DR_DEL01		0x01
#define DR_DEL02		0x02
#define DR_DEL03		0x03
#define DR_DEL04		0x04
#define DR_DEL05		0x05
#define DR_DEL06		0x06
#define DR_DEL07		0x07
#define DR_DEL08		0x08
#define DR_DEL09		0x09
#define DR_DEL10		0x0A
#define DR_DEL11		0x0B
#define DR_DEL12		0x0C
#define DR_DEL13		0x0D
#define DR_DELAY_ON	0xF0

#define DR3_ENABLE		0x01	/* dr3 enable */
#define DR3_DISABLE		0xFE	/* dr3 disable */

#define DR4_ENABLE		0x02	/* dr4 enable  */
#define DR4_DISABLE		0xFD	/* dr4 disable */

#define DR5_ENABLE		0x04	/* dr5 enable */
#define DR5_DISABLE		0xFB	/* dr5 disable */

#define DR3_OUT_ENABLE	0xFC		/* dr3 out_put enable */
#define DR4_OUT_ENABLE	0xF3		/* dr4 out_put enable */
#define DR5_OUT_ENABLE	0xCF		/* dr5 out_put enable */

#define DR35_BRIGHTNESS_HALF	0x0	/* dr3,5 half_brightness config */
#define DR35_BRIGHTNESS_FULL	0x20	/* dr3,5 full_brightness config */
#define DR4_BRIGHTNESS_HALF	0x0	/* dr4 half_brightness config */
#define DR4_BRIGHTNESS_FULL	0x02	/* dr4 full_brightness config */

#define DR35_BRIGHTNESS_CLR	0x8F	/* clear dr3,5 brightness */

#define DR4_BRIGHTNESS_CLR     0xF8    /* clear dr4 brightness */

#define DR_START_DEL_512    0x03	/* start_delay */

#define DR_CONTR_DISABLE    0xF8	/* dr3,4,5 disable */

struct led_set_config {
	u32 k3_led_start_address;
	u32 k3_led_tim_address;
	unsigned long k3_led_dr_ctl;
	unsigned long k3_led_dr_iset;
	unsigned long k3_led_dr_out_ctl;
};

struct led_status {
	enum led_brightness brightness;
	unsigned long delay_on;
	unsigned long delay_off;
};

struct k3_led_data {
	u8 id;

	struct led_classdev ldev;
	struct led_status status;
};

struct k3_led_drv_data {
	struct mutex 		lock;
	struct clk		*clk;
	void __iomem 	*k3_led_base;
	struct k3_led_data leds[K3_LEDS_MAX];
};

struct k3_led {
	const char *name;
	enum led_brightness brightness;
	unsigned long delay_on;
	unsigned long delay_off;
	char *default_trigger;
};

struct k3_led_platform_data {
	struct k3_led leds[K3_LEDS_MAX];
	u8 leds_size;
};

/* read register  */
#define K3_LED_REG_R(reg) readl(k3_led_pdata->k3_led_base + (reg))
/*wirte register  */
#define K3_LED_REG_W(set_val, reg) do {\
	writel((set_val), k3_led_pdata->k3_led_base + (reg)); \
} while (0)

#endif /* __LINUX_LEDS_K3_H */
