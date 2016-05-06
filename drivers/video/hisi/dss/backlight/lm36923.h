/*
* Simple driver for Texas Instruments LM3630 LED Flash driver chip
* Copyright (C) 2012 Texas Instruments
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*/

#ifndef __LINUX_LM36923_H
#define __LINUX_LM36923_H

#define LM36923_NAME "lm36923"
#define DTS_COMP_TI_LM36923 "ti,lm36923"
#define LM36923_CTRL_MODE "lm36923-ctrl-mode"
#define TI_LM36923_ENABLE_REG "enable-reg"
#define TI_LM36923_PROTECT_DISABLE "protect-disable"

#define REG_MAX 0x1F
#define MAX_RATE_NUM 9
/* base reg */
#define REG_REVISION 0x00
#define REG_SOFT_REST 0x01
#define REG_ENABLE 0x10
#define REG_BRT_CTR 0x11
#define REG_PWM_CTR 0x12
#define REG_BOOST_CTR1 0x13
#define REG_BOOST_CTR2 0x14
#define REG_BRT_VAL_L 0x18
#define REG_BRT_VAL_M 0x19
#define REG_FAULT_CTR 0x1E
#define REG_FAULT_FLAG 0x1F

/* mask code */
#define MASK_DEV_RST 0x01
#define MASK_DEV_EN 0x01
#define MASK_LED_STR 0x0E
#define MASK_CHANGE_MODE 0xFF
#define MASK_MAP_MODE 0x80
#define MASK_BRT_MODE 0x60
#define MASK_RAMP_EN 0x10
#define MASK_RAMP_RATE 0x0E
#define MASK_ADJ_POL 0x01
#define MASK_PWM_S_RATE 0xC0
#define MASK_PWM_IN_POL 0x20
#define MASK_PWM_HYS 0x1C
#define MASK_PWM_FILTER 0x03
#define MASK_BL_LSB 0x07

#define BL_MIN 0
#define BL_MAX 2047

#define LM36923_EMERG(msg, ...)    \
	do { if (lm36923_msg_level > 0)  \
		printk(KERN_EMERG "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_ALERT(msg, ...)    \
	do { if (lm36923_msg_level > 1)  \
		printk(KERN_ALERT "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_CRIT(msg, ...)    \
	do { if (lm36923_msg_level > 2)  \
		printk(KERN_CRIT "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_ERR(msg, ...)    \
	do { if (lm36923_msg_level > 3)  \
		printk(KERN_ERR "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_WARNING(msg, ...)    \
	do { if (lm36923_msg_level > 4)  \
		printk(KERN_WARNING "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_NOTICE(msg, ...)    \
	do { if (lm36923_msg_level > 5)  \
		printk(KERN_NOTICE "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_INFO(msg, ...)    \
	do { if (lm36923_msg_level > 6)  \
		printk(KERN_INFO "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)
#define LM36923_DEBUG(msg, ...)    \
	do { if (lm36923_msg_level > 7)  \
		printk(KERN_DEBUG "[lm36923]%s: "msg, __func__, ## __VA_ARGS__); } while (0)

//0x12
enum lm36923_pwm_filter{
	LM36923_PWM_FILTER_100 = 0x01,
	LM36923_PWM_FILTER_150 = 0x02,
	LM36923_PWM_FILTER_200 = 0x03,
};

enum lm36923_pwm_hys {
	LM36923_PWM_HYS_NONE = 0x00,
	LM36923_PWM_HYS_1LSB = 0x04,
	LM36923_PWM_HYS_2LSB = 0x08,
	LM36923_PWM_HYS_3LSB = 0x0C,
	LM36923_PWM_HYS_4LSB = 0x10,
	LM36923_PWM_HYS_5LSB = 0x14,
	LM36923_PWM_HYS_6LSB = 0x18,
};

enum lm36923_pwm_in_pol {
	LM36923_PWM_IN_POL_L = 0x00,
	LM36923_PWM_IN_POL_H = 0x20,
};

enum lm36923_pwm_sample_rate {
	LM36923_PWM_SAMPLE_RATE_8 = 0x00,
	LM36923_PWM_SAMPLE_RATE_40 = 0x40,
	LM36923_PWM_SAMPLE_RATE_240 = 0x80,
};
//0x10
enum lm36923_bleds {
	LM36923_BLED_DIASBLE_ALL = 0x00,
	LM36923_BLED_EN_1 = 0x02,
	LM36923_BLED_EN_2 = 0x04,
	LM36923_BLED_EN_3 = 0x08,
	LM36923_BLED_EN_ALL = 0x0E,
};
enum lm36923_bled_mode {
	LM36923_BLED_MODE_EXPONETIAL = 0x80,
	LM36923_BLED_MODE_LINEAR = 0x00,
};
//0x11
enum lm36923_brt_mode {
	BRT_REG_ONLY = 0x00,
	BRT_PWM_ONLY = 0x20,
	BRT_MUL_RAMP = 0x40,
	BRT_RAMP_MUL = 0x60,
};

enum lm36923_brt_case {
	BRT_REG_ONLY_MODE = 0,
	BRT_PWM_ONLY_MODE = 1,
	BRT_MUL_RAMP_MODE = 2,
	BRT_RAMP_MUL_MODE = 3,
};


#define LM36923_ENABLE 0x01
#define LM36923_DISABLE 0x00

#define LM36923_RAMP_EN 0x10
#define LM36923_RAMP_DIS 0x00

enum lm36923_ramp_rate{
	RAMP_RATE_0125 = 0x00,
	RAMP_RATE_025 = 0x02,
	RAMP_RATE_05 = 0x04,
	RAMP_RATE_1 = 0x06,
	RAMP_RATE_2 = 0x08,
	RAMP_RATE_4 = 0x0A,
	RAMP_RATE_8 = 0x0C,
	RAMP_RATE_16 = 0x0E,
};

#define BL_ADJ_HIGHT 	0x01
#define BL_ADJ_LOW		0x00
#define OVP_OCP_SHUTDOWN_ENABLE 0x04
#define OVP_OCP_SHUTDOWN_DISABLE 0x07

struct lm36923_chip_data {
	struct device *dev;
	struct i2c_client *client;
	struct regmap *regmap;
};

struct lm36923_platform_data {
	unsigned int max_brt_led;
	unsigned int init_brt_led;

	enum lm36923_bleds bled_pins;
	enum lm36923_bled_mode bled_mode;
	enum lm36923_brt_mode brt_mode;

	void (*pwm_set_intensity) (int brightness, int max_brightness);
	int (*pwm_get_intensity) (void);
};

ssize_t lm36923_set_backlight_reg(uint32_t bl_level);

#endif /* __LINUX_LM36923_H */

