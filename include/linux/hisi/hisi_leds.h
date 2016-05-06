/*
 * hisi_leds.h - platform data structure for hisi led controller
 *
 * Copyright (c) 2011-2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __LINUX_LEDS_hisi_H
#define __LINUX_LEDS_hisi_H
#include <linux/leds.h>
#define HISI_LEDS "hisi_leds"

#define LED_OUT_CTRL_VAL(id) (~((0x1 << (id * 2)) | (0x1 << (id * 2 + 1))))

#define HISI_LED0 		0
#define HISI_LED1 		1
#define HISI_LED2 		2

#define HISI_LEDS_MAX 	3

#define LED_DTS_ATTR_LEN 32

#define DELAY_ON		1
#define DELAY_OFF	0

#define DEL_0		0
#define DEL_500		500
#define DEL_1000		1000
#define DEL_2000		2000
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
#define DR_DELAY_ON	    0xF0

#define	DR_BRIGHTNESS_HALF	0x1  /* dr3,4,5 half_brightness config */
#define	DR_BRIGHTNESS_FULL	0x7  /* dr3,4,5 full_brightness config */

#define DR_START_DEL_512    0x03	/* start_delay */

#define DR_CONTR_DISABLE    0xF8	/* dr3,4,5 disable */

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
	struct mutex 		lock;
	struct clk		*clk;
	void __iomem 	*hisi_led_base;
	struct hisi_led_data leds[HISI_LEDS_MAX];
};

struct hisi_led {
	const char *name;
	enum led_brightness brightness;
	unsigned long delay_on;
	unsigned long delay_off;
	char *default_trigger;
    unsigned int dr_start_del;
	unsigned int dr_iset;
	unsigned int each_maxdr_iset;
	unsigned int dr_time_config0;
	unsigned int dr_time_config1;
};

struct hisi_led_platform_data {
	struct hisi_led leds[HISI_LEDS_MAX];
	unsigned int dr_led_ctrl;
	unsigned int dr_out_ctrl;
	unsigned int max_iset;
	u8 leds_size;
};

#endif /* __LINUX_LEDS_HISI_H */

