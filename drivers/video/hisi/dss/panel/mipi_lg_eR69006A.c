/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"
#include <linux/huawei/hisi_adc.h>
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#include <huawei_platform/log/log_jank.h>
#include <linux/hisi/hw_cmdline_parse.h>

#define DTS_COMP_LG_ER69006A "hisilicon,mipi_lg_eR69006A"
#define LCD_VDDIO_TYPE_NAME	"lcd-vddio-type"
#define CABC_OFF	(0)
#define CABC_UI_MODE	(1)
#define CABC_STILL_MODE	(2)
#define CABC_MOVING_MODE	(3)
#define PACKET_PIXELS_SIZE	(216)
#define PACKET_SIZE	(PACKET_PIXELS_SIZE*3+1)
#define PATTERN_PIXELS_X_SIZE	1080
#define PATTERN_PIXELS_Y_SIZE	1920
#define GPIO_TE0 21
#define BACKLIGHT_PRINT_TIMES	10
static struct hisi_fb_panel_data g_panel_data;
static int g_debug_enable = 0;
static int g_cabc_mode = 1;

extern bool gesture_func;
extern bool g_lcd_control_tp_power;
extern unsigned int g_led_rg_para1;
extern unsigned int g_led_rg_para2;

/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
#if 0
/*DSI control: 2rd para
*0xD3 740~1000M, normal
*0x93 180~280M, for FPGA
*/
static char DSI_control[] = {
	0xB6,
	0x3B, 0xD3, 0x00,
};

static char manual_cmd_access_protect[] = {
	0xB0,
	0x03,
};

//display address set
static char address_mode[] = {
	0x36,
	0x00,
};

static char te_line[] = {
	0x44,
	0x03, 0x80,
};
#endif

static char te_enable[] = {
	0x35,
	0x00,
};

static char bl_enable[] = {
	0x53,
	0x24,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};

static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static char lg_pwm_freq[] = {
	0xCE,
	0x5D, 0x40, 0x43, 0x49, 0x55, 0x62, 0x71, 0x82,
	0x94, 0xA8, 0xB9, 0xCB, 0xDB, 0xE9, 0xF5, 0xFC,
	0xFF, 0x00, 0xE3, 0x04, 0x04, 0x00, 0x00, 0x00,
};

static char MCAP[] = {
	0xB0,
	0x00,
};

static struct dsi_cmd_desc lg_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},
#if 0
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(te_line), te_line},
#endif
	{DTYPE_DCS_WRITE, 0, 30, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},
};

static struct dsi_cmd_desc lg_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 52, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 102, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep},
};

static struct dsi_cmd_desc lg_pwm_freq_cmd[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(MCAP), MCAP},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(lg_pwm_freq), lg_pwm_freq},
};

/******************************************************************************
*
** Display Effect Sequence(smart color, edge enhancement, smart contrast, cabc)
*/
static char PWM_OUT_0x51[] = {
	0x51,
	0xFE,
};

static struct dsi_cmd_desc pwm_out_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(PWM_OUT_0x51), PWM_OUT_0x51},
};
static char cabc_off[] = {
	0x55,
	0x00,
};

static char cabc_set_mode_UI[] = {
	0x55,
	0x01,
};

static char cabc_set_mode_STILL[] = {
	0x55,
	0x02,
};

static char cabc_set_mode_MOVING[] = {
	0x55,
	0x03,
};

static char cabc_set_min_value[] = {
	0x5E,
	0x30,
};

static char cabc_set_UI_para[] = {
	0xB8,
	0x07,
	0x90,
	0x0A,
	0x00,
	0x10,
	0x29,
};

static char cabc_set_still_para[] = {
	0xB9,
	0x05,
	0x98,
	0x00,
	0x04,
	0x00,
	0x00,
};

static char cabc_set_Moving_para[] = {
	0xBA,
	0x07,
	0x9E,
	0x20,
	0x16,
	0x20,
	0x8F,
};

static struct dsi_cmd_desc lg_cabc_off_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_off), cabc_off},
};

static struct dsi_cmd_desc lg_cabc_ui_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_UI), cabc_set_mode_UI},
};

static struct dsi_cmd_desc lg_cabc_still_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_STILL), cabc_set_mode_STILL},
};

static struct dsi_cmd_desc lg_cabc_moving_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_MOVING), cabc_set_mode_MOVING},
};

static struct dsi_cmd_desc cabc_mode_paras[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_UI_para), cabc_set_UI_para},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_still_para), cabc_set_still_para},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_Moving_para), cabc_set_Moving_para},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_min_value), cabc_set_min_value},
};
/******************************************************************************
*
** SRAM test sequence
*/
static char test_reg_F1h[] = {
	0xF1,
	0x10,
};

static char test_reg_E0h[] = {
	0xE0,
	0x60,
};

static char test_reg_FEh[] = {
	0xFE,
	0x00, 0x04, 0x0D, 0x00, 0x00, 0x38,
};

static char test_reg_FCh[] = {
	0xFC,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x82, 0x10, 0xC0, 0x00, 0x02,
};

static struct dsi_cmd_desc sram_test_pre_cmds[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(MCAP), MCAP},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_F1h), test_reg_F1h},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_E0h), test_reg_E0h},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_FEh), test_reg_FEh},
};

static struct dsi_cmd_desc sram_test_post_cmds[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_FCh), test_reg_FCh},
};


/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME		"lcdio-vcc"
#define VCC_LCDANALOG_NAME	"lcdanalog-vcc"

static struct regulator *vcc_lcdio;
static struct regulator *vcc_lcdanalog;

static struct vcc_desc lcd_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 3100000, 3100000, WAIT_TYPE_MS, 0},
	/* io set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDIO_NAME, &vcc_lcdio, 1850000, 1850000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 2},
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 2},
};

static struct vcc_desc lcd_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 2},
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 2},
};

/*******************************************************************************
** LCD IOMUX
*/
static struct pinctrl_data pctrl;

static struct pinctrl_cmd_desc lcd_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc lcd_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc lcd_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc lcd_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pctrl, 0},
};

/*******************************************************************************
** LCD GPIO
*/
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"
#define GPIO_LCD_VCC3V1_NAME	"gpio_lcd_vcc3v1"
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"
#define GPIO_LCD_N5V5_ENABLE_NAME "gpio_lcd_n5v5_enable"
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME	"gpio_lcd_id0"

static uint32_t gpio_lcd_bl_enable;
static uint32_t gpio_lcd_vcc3v1;
static uint32_t gpio_lcd_p5v5_enable;
static uint32_t gpio_lcd_n5v5_enable;
static uint32_t gpio_lcd_reset;
static uint32_t gpio_lcd_id0;

static struct gpio_desc lcd_gpio_request_cmds[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* id0 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_free_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* id0 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_normal_cmds_sub1[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 3,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
};

static struct gpio_desc lcd_gpio_normal_cmds_sub2[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
	/* id0 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 3,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 3,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* backlight enable input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};


static struct gpio_desc lcd_gpio_sleep_request_cmds[] = {
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* id0 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_sleep_free_cmds[] = {
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* lcd id */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_sleep_normal_cmds[] = {
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
	/* lcd id */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
};

static struct gpio_desc lcd_gpio_sleep_lp_cmds[] = {
	/* backlight disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

/*******************************************************************************
** ACM
*/
static u32 acm_lut_hue_table[] = {
	0x0000, 0x0001, 0x0002, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0x0011, 0x0012,
	0x0013, 0x0014, 0x0015, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024,
	0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035,
	0x0036, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f, 0x0040, 0x0041, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
	0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
	0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x0060, 0x0061, 0x0062, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066,
	0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006c, 0x006d, 0x006e, 0x006f, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075,
	0x0076, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f, 0x007f, 0x0080, 0x0081, 0x0082, 0x0083,
	0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f, 0x0090, 0x0091, 0x0092,
	0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009c, 0x009d, 0x009e, 0x009f, 0x00a0,
	0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
	0x00b0, 0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd,
	0x00be, 0x00bf, 0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc,
	0x00cc, 0x00cd, 0x00ce, 0x00cf, 0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da,
	0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df, 0x00e0, 0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9,
	0x00ea, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef, 0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
	0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff, 0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107,
	0x0108, 0x0108, 0x0109, 0x010a, 0x010b, 0x010c, 0x010d, 0x010e, 0x010f, 0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116,
	0x0117, 0x0118, 0x0119, 0x011a, 0x011b, 0x011c, 0x011d, 0x011e, 0x011f, 0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126,
	0x0126, 0x0127, 0x0128, 0x0129, 0x012a, 0x012b, 0x012c, 0x012d, 0x012e, 0x012f, 0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135,
	0x0136, 0x0137, 0x0138, 0x0139, 0x013a, 0x013b, 0x013c, 0x013d, 0x013e, 0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146,
	0x0147, 0x0148, 0x0149, 0x014a, 0x014b, 0x014c, 0x014d, 0x014e, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157,
	0x0158, 0x0159, 0x015a, 0x015b, 0x015c, 0x015d, 0x015e, 0x015f, 0x0160, 0x0162, 0x0163, 0x0164, 0x0165, 0x0166, 0x0167, 0x0168,
	0x0169, 0x016a, 0x016b, 0x016c, 0x016d, 0x016e, 0x016f, 0x0170, 0x0172, 0x0173, 0x0174, 0x0175, 0x0176, 0x0177, 0x0178, 0x0179,
	0x017a, 0x017b, 0x017c, 0x017d, 0x017e, 0x017f, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186, 0x0187, 0x0188, 0x0189, 0x018a,
	0x018c, 0x018d, 0x018e, 0x018f, 0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0198, 0x0199, 0x019a, 0x019b, 0x019c,
	0x019d, 0x019e, 0x019f, 0x01a0, 0x01a1, 0x01a2, 0x01a4, 0x01a5, 0x01a6, 0x01a7, 0x01a8, 0x01a9, 0x01aa, 0x01ab, 0x01ac, 0x01ad,
	0x01ae, 0x01b0, 0x01b1, 0x01b2, 0x01b3, 0x01b4, 0x01b5, 0x01b6, 0x01b7, 0x01b8, 0x01b9, 0x01bb, 0x01bc, 0x01bd, 0x01be, 0x01bf,
	0x01c0, 0x01c1, 0x01c2, 0x01c3, 0x01c4, 0x01c5, 0x01c6, 0x01c7, 0x01c8, 0x01c9, 0x01ca, 0x01cb, 0x01cc, 0x01cd, 0x01ce, 0x01cf,
	0x01d0, 0x01d1, 0x01d2, 0x01d3, 0x01d4, 0x01d5, 0x01d6, 0x01d7, 0x01d8, 0x01d9, 0x01da, 0x01db, 0x01dc, 0x01dd, 0x01de, 0x01df,
	0x01e0, 0x01e1, 0x01e2, 0x01e3, 0x01e4, 0x01e5, 0x01e6, 0x01e7, 0x01e8, 0x01e9, 0x01ea, 0x01eb, 0x01ec, 0x01ed, 0x01ee, 0x01ef,
	0x01f0, 0x01f1, 0x01f2, 0x01f3, 0x01f4, 0x01f5, 0x01f6, 0x01f7, 0x01f8, 0x01f9, 0x01fa, 0x01fb, 0x01fc, 0x01fd, 0x01fe, 0x01ff,
	0x0200, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0208, 0x0209, 0x020a, 0x020b, 0x020c, 0x020d, 0x020e, 0x020f, 0x0210,
	0x0211, 0x0212, 0x0213, 0x0214, 0x0216, 0x0217, 0x0218, 0x0219, 0x021a, 0x021b, 0x021c, 0x021d, 0x021e, 0x021f, 0x0220, 0x0221,
	0x0222, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0x0229, 0x022a, 0x022b, 0x022c, 0x022d, 0x022e, 0x022f, 0x0231, 0x0232, 0x0233,
	0x0234, 0x0235, 0x0236, 0x0237, 0x0238, 0x0239, 0x023a, 0x023b, 0x023c, 0x023d, 0x023f, 0x0240, 0x0241, 0x0242, 0x0243, 0x0244,
	0x0245, 0x0246, 0x0247, 0x0248, 0x0249, 0x024a, 0x024b, 0x024c, 0x024d, 0x024e, 0x024f, 0x0250, 0x0251, 0x0252, 0x0253, 0x0254,
	0x0255, 0x0256, 0x0257, 0x0258, 0x0259, 0x025a, 0x025b, 0x025c, 0x025d, 0x025e, 0x025f, 0x0260, 0x0261, 0x0262, 0x0263, 0x0264,
	0x0266, 0x0267, 0x0268, 0x0269, 0x026a, 0x026b, 0x026c, 0x026d, 0x026e, 0x026f, 0x0270, 0x0271, 0x0272, 0x0273, 0x0274, 0x0275,
	0x0276, 0x0277, 0x0278, 0x0279, 0x027a, 0x027b, 0x027c, 0x027d, 0x027e, 0x027f, 0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285,
	0x0286, 0x0287, 0x0288, 0x0289, 0x028a, 0x028b, 0x028c, 0x028d, 0x028e, 0x028f, 0x0290, 0x0290, 0x0291, 0x0292, 0x0293, 0x0294,
	0x0295, 0x0296, 0x0297, 0x0298, 0x0299, 0x029a, 0x029b, 0x029c, 0x029d, 0x029e, 0x029f, 0x02a0, 0x02a1, 0x02a2, 0x02a3, 0x02a4,
	0x02a4, 0x02a5, 0x02a6, 0x02a7, 0x02a8, 0x02a9, 0x02aa, 0x02ab, 0x02ac, 0x02ad, 0x02ae, 0x02af, 0x02b0, 0x02b1, 0x02b2, 0x02b3,
	0x02b4, 0x02b5, 0x02b6, 0x02b7, 0x02b8, 0x02b9, 0x02b9, 0x02ba, 0x02bb, 0x02bc, 0x02bd, 0x02be, 0x02bf, 0x02c0, 0x02c1, 0x02c2,
	0x02c3, 0x02c4, 0x02c5, 0x02c6, 0x02c7, 0x02c8, 0x02c9, 0x02ca, 0x02cb, 0x02cc, 0x02cd, 0x02cd, 0x02ce, 0x02cf, 0x02d0, 0x02d1,
	0x02d2, 0x02d3, 0x02d4, 0x02d5, 0x02d6, 0x02d7, 0x02d8, 0x02d9, 0x02da, 0x02db, 0x02dc, 0x02dd, 0x02de, 0x02df, 0x02e0, 0x02e1,
	0x02e2, 0x02e2, 0x02e3, 0x02e4, 0x02e5, 0x02e6, 0x02e7, 0x02e8, 0x02e9, 0x02ea, 0x02eb, 0x02ec, 0x02ed, 0x02ee, 0x02ef, 0x02f0,
	0x02f1, 0x02f2, 0x02f3, 0x02f4, 0x02f5, 0x02f6, 0x02f6, 0x02f7, 0x02f8, 0x02f9, 0x02fa, 0x02fb, 0x02fc, 0x02fd, 0x02fe, 0x02ff,
	0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a, 0x030b, 0x030c, 0x030d, 0x030e, 0x030f,
	0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 0x0318, 0x0319, 0x031a, 0x031b, 0x031c, 0x031d, 0x031e, 0x031f,
	0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 0x0328, 0x0329, 0x032a, 0x032b, 0x032c, 0x032d, 0x032e, 0x032f,
	0x0330, 0x0331, 0x0332, 0x0333, 0x0334, 0x0335, 0x0336, 0x0337, 0x0338, 0x0339, 0x033a, 0x033b, 0x033c, 0x033d, 0x033e, 0x033f,
	0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0345, 0x0346, 0x0347, 0x0348, 0x0349, 0x034a, 0x034b, 0x034c, 0x034d, 0x034e, 0x034f,
	0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 0x0358, 0x0359, 0x035a, 0x035b, 0x035c, 0x035d, 0x035e, 0x035f,
	0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 0x0368, 0x0369, 0x036a, 0x036b, 0x036c, 0x036d, 0x036e, 0x036f,
	0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 0x0378, 0x0379, 0x037a, 0x037b, 0x037c, 0x037d, 0x037e, 0x037f,
	0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389, 0x038a, 0x038b, 0x038c, 0x038d, 0x038e, 0x038f,
	0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d, 0x039e, 0x039f,
	0x03a0, 0x03a1, 0x03a2, 0x03a3, 0x03a4, 0x03a5, 0x03a6, 0x03a7, 0x03a8, 0x03a9, 0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03ae, 0x03af,
	0x03b0, 0x03b1, 0x03b2, 0x03b3, 0x03b4, 0x03b5, 0x03b6, 0x03b7, 0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bc, 0x03bd, 0x03be, 0x03bf,
	0x03c0, 0x03c1, 0x03c2, 0x03c3, 0x03c4, 0x03c5, 0x03c6, 0x03c7, 0x03c8, 0x03c9, 0x03ca, 0x03cb, 0x03cc, 0x03cd, 0x03ce, 0x03cf,
	0x03d0, 0x03d1, 0x03d2, 0x03d3, 0x03d4, 0x03d5, 0x03d6, 0x03d7, 0x03d8, 0x03d9, 0x03da, 0x03db, 0x03dc, 0x03dd, 0x03de, 0x03df,
	0x03e0, 0x03e1, 0x03e2, 0x03e3, 0x03e4, 0x03e5, 0x03e6, 0x03e7, 0x03e8, 0x03e9, 0x03ea, 0x03eb, 0x03ec, 0x03ed, 0x03ee, 0x03ef,
	0x03f0, 0x03f1, 0x03f2, 0x03f3, 0x03f4, 0x03f5, 0x03f6, 0x03f7, 0x03f8, 0x03f9, 0x03fa, 0x03fb, 0x03fc, 0x03fd, 0x03fe, 0x03ff,
};

static u32 acm_lut_sata_table[] = {
	0x0069, 0x006c, 0x006e, 0x0071, 0x0074, 0x0077, 0x007a, 0x007c, 0x007f, 0x0081, 0x0083, 0x0085, 0x0088, 0x008a, 0x008c, 0x008e,
	0x0090, 0x0090, 0x0090, 0x008f, 0x008f, 0x008f, 0x008e, 0x008e, 0x008e, 0x008c, 0x008a, 0x0089, 0x0087, 0x0085, 0x0084, 0x0082,
	0x0080, 0x007d, 0x0079, 0x0076, 0x0072, 0x006f, 0x006c, 0x0068, 0x0065, 0x0060, 0x005b, 0x0056, 0x0050, 0x004b, 0x0046, 0x0041,
	0x003c, 0x0038, 0x0033, 0x002f, 0x002a, 0x0026, 0x0022, 0x001d, 0x0019, 0x0016, 0x0013, 0x0010, 0x000c, 0x0009, 0x0006, 0x0003,
	0x0000, 0x0006, 0x000b, 0x0010, 0x0016, 0x001c, 0x0021, 0x0026, 0x002c, 0x002e, 0x0030, 0x0032, 0x0034, 0x0037, 0x0039, 0x003b,
	0x003d, 0x003b, 0x0038, 0x0036, 0x0034, 0x0032, 0x0030, 0x002d, 0x002b, 0x0026, 0x0020, 0x001b, 0x0016, 0x0010, 0x000b, 0x0005,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0002, 0x0004, 0x0006, 0x0008, 0x0009, 0x000b, 0x000d, 0x000f, 0x0012, 0x0015, 0x0018, 0x001a, 0x001d, 0x0020, 0x0023,
	0x0026, 0x0027, 0x0028, 0x002a, 0x002b, 0x002c, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0034, 0x0035, 0x0036,
	0x0037, 0x0037, 0x0038, 0x0038, 0x0038, 0x0039, 0x0039, 0x003a, 0x003a, 0x003a, 0x0039, 0x0039, 0x0038, 0x0038, 0x0038, 0x0037,
	0x0037, 0x0036, 0x0036, 0x0035, 0x0034, 0x0034, 0x0033, 0x0033, 0x0032, 0x0031, 0x0030, 0x002f, 0x002e, 0x002c, 0x002b, 0x002a,
	0x0029, 0x0027, 0x0026, 0x0024, 0x0022, 0x0021, 0x001f, 0x001e, 0x001c, 0x001b, 0x001a, 0x0018, 0x0017, 0x0016, 0x0014, 0x0013,
	0x0012, 0x0010, 0x000e, 0x000b, 0x0009, 0x0007, 0x0004, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0006, 0x000c, 0x0012, 0x0018, 0x001e, 0x0024, 0x002a, 0x0030, 0x0033, 0x0036, 0x0039, 0x003c, 0x0040, 0x0043, 0x0046,
	0x0049, 0x004c, 0x004f, 0x0052, 0x0054, 0x0057, 0x005a, 0x005d, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0066, 0x0067, 0x0068,
};

static u32 acm_lut_satr_table[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00ff, 0x00fd, 0x00fc, 0x00fa, 0x00f9, 0x00f7, 0x00f6, 0x00f6, 0x00f6,
	0x00f6, 0x00f7, 0x00f7, 0x00f7, 0x00f7, 0x00f7, 0x00f7, 0x00f8, 0x00f8, 0x00f8, 0x00f8, 0x00f8, 0x00f8, 0x00f8, 0x00f9, 0x00f9,
	0x00f9, 0x00f9, 0x00f9, 0x00f9, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fb, 0x00fb, 0x00fb, 0x00fb, 0x00fb, 0x00fc,
	0x00fc, 0x00fc, 0x00fc, 0x00fd, 0x00fd, 0x00fd, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000,
	0x0000, 0x00ff, 0x00fe, 0x00fe, 0x00fd, 0x00fc, 0x00fb, 0x00fb, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00f9, 0x00f9, 0x00f9, 0x00f9,
	0x00f9, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fa, 0x00fb, 0x00fb, 0x00fb, 0x00fb, 0x00fb, 0x00fb, 0x00fc, 0x00fc, 0x00fc,
	0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fd, 0x00fd, 0x00fd, 0x00fd, 0x00fd, 0x00fd, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe,
	0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0003, 0x0004, 0x0004, 0x0005, 0x0005, 0x0006, 0x0006, 0x0006, 0x0006,
	0x0006, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0003, 0x0003,
	0x0003, 0x0003, 0x0003, 0x0003, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
	0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002,
	0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0003, 0x0003,
	0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003,
	0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
	0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00fe, 0x00fe, 0x00fe, 0x00fd, 0x00fd, 0x00fc, 0x00fc, 0x00fb, 0x00fb, 0x00fb, 0x00fb,
	0x00fb, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fc, 0x00fd, 0x00fd, 0x00fd, 0x00fd, 0x00fd, 0x00fd,
	0x00fd, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00fe, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
	0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

/*******************************************************************************
** GAMMA
*/
static u32 gamma_lut_table_R[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff,
};

static u32 gamma_lut_table_G[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff,
};

static u32 gamma_lut_table_B[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff,
};

/*******************************************************************************
** IGM
*/
static u32 igm_lut_table_R[] = {
    0x0000, 0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080, 0x0090, 0x00a0, 0x00b0, 0x00c0, 0x00d0, 0x00e0, 0x00f0,
    0x0100, 0x0110, 0x0120, 0x0130, 0x0140, 0x0150, 0x0160, 0x0170, 0x0180, 0x0190, 0x01a0, 0x01b0, 0x01c0, 0x01d0, 0x01e0, 0x01f0,
    0x0200, 0x0210, 0x0220, 0x0230, 0x0240, 0x0250, 0x0260, 0x0270, 0x0280, 0x0290, 0x02a0, 0x02b0, 0x02c0, 0x02d0, 0x02e0, 0x02f0,
    0x0300, 0x0310, 0x0320, 0x0330, 0x0340, 0x0350, 0x0360, 0x0370, 0x0380, 0x0390, 0x03a0, 0x03b0, 0x03c0, 0x03d0, 0x03e0, 0x03f0,
    0x0400, 0x0410, 0x0420, 0x0430, 0x0440, 0x0450, 0x0460, 0x0470, 0x0480, 0x0490, 0x04a0, 0x04b0, 0x04c0, 0x04d0, 0x04e0, 0x04f0,
    0x0500, 0x0510, 0x0520, 0x0530, 0x0540, 0x0550, 0x0560, 0x0570, 0x0580, 0x0590, 0x05a0, 0x05b0, 0x05c0, 0x05d0, 0x05e0, 0x05f0,
    0x0600, 0x0610, 0x0620, 0x0630, 0x0640, 0x0650, 0x0660, 0x0670, 0x0680, 0x0690, 0x06a0, 0x06b0, 0x06c0, 0x06d0, 0x06e0, 0x06f0,
    0x0700, 0x0710, 0x0720, 0x0730, 0x0740, 0x0750, 0x0760, 0x0770, 0x0780, 0x0790, 0x07a0, 0x07b0, 0x07c0, 0x07d0, 0x07e0, 0x07f0,
    0x0800, 0x0810, 0x0820, 0x0830, 0x0840, 0x0850, 0x0860, 0x0870, 0x0880, 0x0890, 0x08a0, 0x08b0, 0x08c0, 0x08d0, 0x08e0, 0x08f0,
    0x0900, 0x0910, 0x0920, 0x0930, 0x0940, 0x0950, 0x0960, 0x0970, 0x0980, 0x0990, 0x09a0, 0x09b0, 0x09c0, 0x09d0, 0x09e0, 0x09f0,
    0x0a00, 0x0a10, 0x0a20, 0x0a30, 0x0a40, 0x0a50, 0x0a60, 0x0a70, 0x0a80, 0x0a90, 0x0aa0, 0x0ab0, 0x0ac0, 0x0ad0, 0x0ae0, 0x0af0,
    0x0b00, 0x0b10, 0x0b20, 0x0b30, 0x0b40, 0x0b50, 0x0b60, 0x0b70, 0x0b80, 0x0b90, 0x0ba0, 0x0bb0, 0x0bc0, 0x0bd0, 0x0be0, 0x0bf0,
    0x0c00, 0x0c10, 0x0c20, 0x0c30, 0x0c40, 0x0c50, 0x0c60, 0x0c70, 0x0c80, 0x0c90, 0x0ca0, 0x0cb0, 0x0cc0, 0x0cd0, 0x0ce0, 0x0cf0,
    0x0d00, 0x0d10, 0x0d20, 0x0d30, 0x0d40, 0x0d50, 0x0d60, 0x0d70, 0x0d80, 0x0d90, 0x0da0, 0x0db0, 0x0dc0, 0x0dd0, 0x0de0, 0x0df0,
    0x0e00, 0x0e10, 0x0e20, 0x0e30, 0x0e40, 0x0e50, 0x0e60, 0x0e70, 0x0e80, 0x0e90, 0x0ea0, 0x0eb0, 0x0ec0, 0x0ed0, 0x0ee0, 0x0ef0,
    0x0f00, 0x0f10, 0x0f20, 0x0f30, 0x0f40, 0x0f50, 0x0f60, 0x0f70, 0x0f80, 0x0f90, 0x0fa0, 0x0fb0, 0x0fc0, 0x0fd0, 0x0fe0, 0x0ff0,
};

static u32 igm_lut_table_G[] = {
    0x0000, 0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080, 0x0090, 0x00a0, 0x00b0, 0x00c0, 0x00d0, 0x00e0, 0x00f0,
    0x0100, 0x0110, 0x0120, 0x0130, 0x0140, 0x0150, 0x0160, 0x0170, 0x0180, 0x0190, 0x01a0, 0x01b0, 0x01c0, 0x01d0, 0x01e0, 0x01f0,
    0x0200, 0x0210, 0x0220, 0x0230, 0x0240, 0x0250, 0x0260, 0x0270, 0x0280, 0x0290, 0x02a0, 0x02b0, 0x02c0, 0x02d0, 0x02e0, 0x02f0,
    0x0300, 0x0310, 0x0320, 0x0330, 0x0340, 0x0350, 0x0360, 0x0370, 0x0380, 0x0390, 0x03a0, 0x03b0, 0x03c0, 0x03d0, 0x03e0, 0x03f0,
    0x0400, 0x0410, 0x0420, 0x0430, 0x0440, 0x0450, 0x0460, 0x0470, 0x0480, 0x0490, 0x04a0, 0x04b0, 0x04c0, 0x04d0, 0x04e0, 0x04f0,
    0x0500, 0x0510, 0x0520, 0x0530, 0x0540, 0x0550, 0x0560, 0x0570, 0x0580, 0x0590, 0x05a0, 0x05b0, 0x05c0, 0x05d0, 0x05e0, 0x05f0,
    0x0600, 0x0610, 0x0620, 0x0630, 0x0640, 0x0650, 0x0660, 0x0670, 0x0680, 0x0690, 0x06a0, 0x06b0, 0x06c0, 0x06d0, 0x06e0, 0x06f0,
    0x0700, 0x0710, 0x0720, 0x0730, 0x0740, 0x0750, 0x0760, 0x0770, 0x0780, 0x0790, 0x07a0, 0x07b0, 0x07c0, 0x07d0, 0x07e0, 0x07f0,
    0x0800, 0x0810, 0x0820, 0x0830, 0x0840, 0x0850, 0x0860, 0x0870, 0x0880, 0x0890, 0x08a0, 0x08b0, 0x08c0, 0x08d0, 0x08e0, 0x08f0,
    0x0900, 0x0910, 0x0920, 0x0930, 0x0940, 0x0950, 0x0960, 0x0970, 0x0980, 0x0990, 0x09a0, 0x09b0, 0x09c0, 0x09d0, 0x09e0, 0x09f0,
    0x0a00, 0x0a10, 0x0a20, 0x0a30, 0x0a40, 0x0a50, 0x0a60, 0x0a70, 0x0a80, 0x0a90, 0x0aa0, 0x0ab0, 0x0ac0, 0x0ad0, 0x0ae0, 0x0af0,
    0x0b00, 0x0b10, 0x0b20, 0x0b30, 0x0b40, 0x0b50, 0x0b60, 0x0b70, 0x0b80, 0x0b90, 0x0ba0, 0x0bb0, 0x0bc0, 0x0bd0, 0x0be0, 0x0bf0,
    0x0c00, 0x0c10, 0x0c20, 0x0c30, 0x0c40, 0x0c50, 0x0c60, 0x0c70, 0x0c80, 0x0c90, 0x0ca0, 0x0cb0, 0x0cc0, 0x0cd0, 0x0ce0, 0x0cf0,
    0x0d00, 0x0d10, 0x0d20, 0x0d30, 0x0d40, 0x0d50, 0x0d60, 0x0d70, 0x0d80, 0x0d90, 0x0da0, 0x0db0, 0x0dc0, 0x0dd0, 0x0de0, 0x0df0,
    0x0e00, 0x0e10, 0x0e20, 0x0e30, 0x0e40, 0x0e50, 0x0e60, 0x0e70, 0x0e80, 0x0e90, 0x0ea0, 0x0eb0, 0x0ec0, 0x0ed0, 0x0ee0, 0x0ef0,
    0x0f00, 0x0f10, 0x0f20, 0x0f30, 0x0f40, 0x0f50, 0x0f60, 0x0f70, 0x0f80, 0x0f90, 0x0fa0, 0x0fb0, 0x0fc0, 0x0fd0, 0x0fe0, 0x0ff0,
};

static u32 igm_lut_table_B[] = {
    0x0000, 0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080, 0x0090, 0x00a0, 0x00b0, 0x00c0, 0x00d0, 0x00e0, 0x00f0,
    0x0100, 0x0110, 0x0120, 0x0130, 0x0140, 0x0150, 0x0160, 0x0170, 0x0180, 0x0190, 0x01a0, 0x01b0, 0x01c0, 0x01d0, 0x01e0, 0x01f0,
    0x0200, 0x0210, 0x0220, 0x0230, 0x0240, 0x0250, 0x0260, 0x0270, 0x0280, 0x0290, 0x02a0, 0x02b0, 0x02c0, 0x02d0, 0x02e0, 0x02f0,
    0x0300, 0x0310, 0x0320, 0x0330, 0x0340, 0x0350, 0x0360, 0x0370, 0x0380, 0x0390, 0x03a0, 0x03b0, 0x03c0, 0x03d0, 0x03e0, 0x03f0,
    0x0400, 0x0410, 0x0420, 0x0430, 0x0440, 0x0450, 0x0460, 0x0470, 0x0480, 0x0490, 0x04a0, 0x04b0, 0x04c0, 0x04d0, 0x04e0, 0x04f0,
    0x0500, 0x0510, 0x0520, 0x0530, 0x0540, 0x0550, 0x0560, 0x0570, 0x0580, 0x0590, 0x05a0, 0x05b0, 0x05c0, 0x05d0, 0x05e0, 0x05f0,
    0x0600, 0x0610, 0x0620, 0x0630, 0x0640, 0x0650, 0x0660, 0x0670, 0x0680, 0x0690, 0x06a0, 0x06b0, 0x06c0, 0x06d0, 0x06e0, 0x06f0,
    0x0700, 0x0710, 0x0720, 0x0730, 0x0740, 0x0750, 0x0760, 0x0770, 0x0780, 0x0790, 0x07a0, 0x07b0, 0x07c0, 0x07d0, 0x07e0, 0x07f0,
    0x0800, 0x0810, 0x0820, 0x0830, 0x0840, 0x0850, 0x0860, 0x0870, 0x0880, 0x0890, 0x08a0, 0x08b0, 0x08c0, 0x08d0, 0x08e0, 0x08f0,
    0x0900, 0x0910, 0x0920, 0x0930, 0x0940, 0x0950, 0x0960, 0x0970, 0x0980, 0x0990, 0x09a0, 0x09b0, 0x09c0, 0x09d0, 0x09e0, 0x09f0,
    0x0a00, 0x0a10, 0x0a20, 0x0a30, 0x0a40, 0x0a50, 0x0a60, 0x0a70, 0x0a80, 0x0a90, 0x0aa0, 0x0ab0, 0x0ac0, 0x0ad0, 0x0ae0, 0x0af0,
    0x0b00, 0x0b10, 0x0b20, 0x0b30, 0x0b40, 0x0b50, 0x0b60, 0x0b70, 0x0b80, 0x0b90, 0x0ba0, 0x0bb0, 0x0bc0, 0x0bd0, 0x0be0, 0x0bf0,
    0x0c00, 0x0c10, 0x0c20, 0x0c30, 0x0c40, 0x0c50, 0x0c60, 0x0c70, 0x0c80, 0x0c90, 0x0ca0, 0x0cb0, 0x0cc0, 0x0cd0, 0x0ce0, 0x0cf0,
    0x0d00, 0x0d10, 0x0d20, 0x0d30, 0x0d40, 0x0d50, 0x0d60, 0x0d70, 0x0d80, 0x0d90, 0x0da0, 0x0db0, 0x0dc0, 0x0dd0, 0x0de0, 0x0df0,
    0x0e00, 0x0e10, 0x0e20, 0x0e30, 0x0e40, 0x0e50, 0x0e60, 0x0e70, 0x0e80, 0x0e90, 0x0ea0, 0x0eb0, 0x0ec0, 0x0ed0, 0x0ee0, 0x0ef0,
    0x0f00, 0x0f10, 0x0f20, 0x0f30, 0x0f40, 0x0f50, 0x0f60, 0x0f70, 0x0f80, 0x0f90, 0x0fa0, 0x0fb0, 0x0fc0, 0x0fd0, 0x0fe0, 0x0ff0,
};

/*******************************************************************************
** GMT
*/
static u32 gmp_lut_table_low32bit[9][9][9] = {
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000a00, 0x00000c00, 0x00000e00, 0x00000ff0, },
        {0x00200000, 0x00200200, 0x00200400, 0x00200600, 0x00200800, 0x00200a00, 0x00200c00, 0x00200e00, 0x00200ff0, },
        {0x00400000, 0x00400200, 0x00400400, 0x00400600, 0x00400800, 0x00400a00, 0x00400c00, 0x00400e00, 0x00400ff0, },
        {0x00600000, 0x00600200, 0x00600400, 0x00600600, 0x00600800, 0x00600a00, 0x00600c00, 0x00600e00, 0x00600ff0, },
        {0x00800000, 0x00800200, 0x00800400, 0x00800600, 0x00800800, 0x00800a00, 0x00800c00, 0x00800e00, 0x00800ff0, },
        {0x00a00000, 0x00a00200, 0x00a00400, 0x00a00600, 0x00a00800, 0x00a00a00, 0x00a00c00, 0x00a00e00, 0x00a00ff0, },
        {0x00c00000, 0x00c00200, 0x00c00400, 0x00c00600, 0x00c00800, 0x00c00a00, 0x00c00c00, 0x00c00e00, 0x00c00ff0, },
        {0x00e00000, 0x00e00200, 0x00e00400, 0x00e00600, 0x00e00800, 0x00e00a00, 0x00e00c00, 0x00e00e00, 0x00e00ff0, },
        {0x00ff0000, 0x00ff0200, 0x00ff0400, 0x00ff0600, 0x00ff0800, 0x00ff0a00, 0x00ff0c00, 0x00ff0e00, 0x00ff0ff0, },
    },
    {
        {0xf0000000, 0xf0000200, 0xf0000400, 0xf0000600, 0xf0000800, 0xf0000a00, 0xf0000c00, 0xf0000e00, 0xf0000ff0, },
        {0xf0200000, 0xf0200200, 0xf0200400, 0xf0200600, 0xf0200800, 0xf0200a00, 0xf0200c00, 0xf0200e00, 0xf0200ff0, },
        {0xf0400000, 0xf0400200, 0xf0400400, 0xf0400600, 0xf0400800, 0xf0400a00, 0xf0400c00, 0xf0400e00, 0xf0400ff0, },
        {0xf0600000, 0xf0600200, 0xf0600400, 0xf0600600, 0xf0600800, 0xf0600a00, 0xf0600c00, 0xf0600e00, 0xf0600ff0, },
        {0xf0800000, 0xf0800200, 0xf0800400, 0xf0800600, 0xf0800800, 0xf0800a00, 0xf0800c00, 0xf0800e00, 0xf0800ff0, },
        {0xf0a00000, 0xf0a00200, 0xf0a00400, 0xf0a00600, 0xf0a00800, 0xf0a00a00, 0xf0a00c00, 0xf0a00e00, 0xf0a00ff0, },
        {0xf0c00000, 0xf0c00200, 0xf0c00400, 0xf0c00600, 0xf0c00800, 0xf0c00a00, 0xf0c00c00, 0xf0c00e00, 0xf0c00ff0, },
        {0xf0e00000, 0xf0e00200, 0xf0e00400, 0xf0e00600, 0xf0e00800, 0xf0e00a00, 0xf0e00c00, 0xf0e00e00, 0xf0e00ff0, },
        {0xf0ff0000, 0xf0ff0200, 0xf0ff0400, 0xf0ff0600, 0xf0ff0800, 0xf0ff0a00, 0xf0ff0c00, 0xf0ff0e00, 0xf0ff0ff0, },
    },
};

static u32 gmp_lut_table_high4bit[9][9][9] = {
    {
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, },
    },
    {
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
        {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, },
    },
    {
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
        {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, },
    },
    {
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
        {0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, },
    },
    {
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
        {0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, },
    },
    {
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
        {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, },
    },
    {
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
        {0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, },
    },
    {
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
        {0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, },
    },
    {
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
        {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, },
    },
};

/*******************************************************************************
** XCC
*/
static u32 xcc_table[12] = {0x0, 0x8000, 0x0,0x0,0x0,0x0,0x8000,0x0,0x0,0x0,0x0,0x8000,};

/*******************************************************************************
** 2d sharpness
*/
static sharp2d_t sharp2d_table = {
	.sharp_en = 1, .sharp_mode = 0,
	.flt0_c0 = 0xf0, .flt0_c1 = 0xf0, .flt0_c2 = 0xf0,
	.flt1_c0 = 0xf0, .flt1_c1 = 0x1c, .flt1_c2 = 0x1c,
	.flt2_c0 = 0xf0, .flt2_c1 = 0x1c, .flt2_c2 = 0x20,
	.ungain = 0x64, .ovgain = 0x64,
	.lineamt1 = 0x100, .linedeten = 0x1, .linethd2 = 0x4, .linethd1 = 0x6,
	.sharpthd1 = 0x8, .sharpthd1mul = 0x200, .sharpamt1 = 0x100,
	.edgethd1 = 0x8, .edgethd1mul = 0x200, .edgeamt1 = 0x100,
};

/*******************************************************************************
**
*/
static int mipi_lg_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// lcd pinctrl normal
	pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
		ARRAY_SIZE(lcd_pinctrl_normal_cmds));

	// lcd gpio request
	gpio_cmds_tx(lcd_gpio_request_cmds,
		ARRAY_SIZE(lcd_gpio_request_cmds));

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_status_reg[] = {
		{0x0A, 0x1C, 0xFF, "lcd power state"},
		{0x0E, 0x80, 0xC1, "lcd signal mode"},
		{0x05, 0x00, 0xFF, "mipi dsi error number"},
		{0xDA, 0x00, 0x00, "RDID1"},
	};
#endif

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		g_debug_enable = BACKLIGHT_PRINT_TIMES;
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
		if (false == gesture_func && !g_debug_enable_lcd_sleep_in) {
			// lcd vcc enable
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
				ARRAY_SIZE(lcd_vcc_enable_cmds));

			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
				ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			// lcd gpio request
			gpio_cmds_tx(lcd_gpio_request_cmds, \
				ARRAY_SIZE(lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(lcd_gpio_normal_cmds_sub1, \
				ARRAY_SIZE(lcd_gpio_normal_cmds_sub1));
		} else {
			HISI_FB_INFO("power on (gesture_func:%d)\n", gesture_func);

			gpio_cmds_tx(lcd_gpio_sleep_request_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_request_cmds));

			gpio_cmds_tx(lcd_gpio_sleep_normal_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_normal_cmds));
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
#ifdef CONFIG_HUAWEI_TS
		if ((g_lcd_control_tp_power || pinfo->esd_recover_step == LCD_ESD_RECOVER_POWER_ON) &&
			!g_debug_enable_lcd_sleep_in) {
			error = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts resume device err\n");
		}
#endif

		if (false == gesture_func && !g_debug_enable_lcd_sleep_in) {
			// lcd gpio normal
			gpio_cmds_tx(lcd_gpio_normal_cmds_sub2, \
				ARRAY_SIZE(lcd_gpio_normal_cmds_sub2));
		} else {
			msleep(50);
			HISI_FB_INFO("lp send sequence (gesture_func:%d)\n", gesture_func);
		}

		// lcd display on sequence
//		mipi_dsi_cmds_tx(lg_initial_set, \
//			ARRAY_SIZE(lg_initial_set), mipi_dsi0_base);
//		mipi_dsi_cmds_tx(lg_power_supply_set, \
//			ARRAY_SIZE(lg_power_supply_set), mipi_dsi0_base);
		mipi_dsi_cmds_tx(lg_display_on_cmds, \
			ARRAY_SIZE(lg_display_on_cmds), mipi_dsi0_base);

		// lcd display effect sequence
		mipi_dsi_cmds_tx(lg_pwm_freq_cmd, \
			ARRAY_SIZE(lg_pwm_freq_cmd), mipi_dsi0_base);

		mipi_dsi_cmds_tx(cabc_mode_paras, \
			ARRAY_SIZE(cabc_mode_paras), mipi_dsi0_base);

		mipi_dsi_cmds_tx(lg_cabc_ui_on_cmds, \
			ARRAY_SIZE(lg_cabc_ui_on_cmds), mipi_dsi0_base);

		if ((pinfo->bl_set_type & BL_SET_BY_BLPWM) || (pinfo->bl_set_type & BL_SET_BY_SH_BLPWM)) {
			mipi_dsi_cmds_tx(pwm_out_on_cmds, \
				ARRAY_SIZE(pwm_out_on_cmds), mipi_dsi0_base);
		}
		g_cabc_mode = 1;
#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(lcd_status_reg, \
			ARRAY_SIZE(lcd_status_reg), mipi_dsi0_base);
#endif

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
#ifdef CONFIG_HUAWEI_TS
		if ((g_lcd_control_tp_power || pinfo->esd_recover_step == LCD_ESD_RECOVER_POWER_ON) &&
			!g_debug_enable_lcd_sleep_in) {
			error = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts after resume err\n");
		}
#endif
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	/* backlight on */
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	uint32_t read_value[1] = {0};
	uint32_t expected_value[1] = {0x00};
	uint32_t read_mask[1] = {0xFF};
	char* reg_name[1] = {"Number on DSI"};

	//static struct lcd_reg_read_t lcd_status_reg[] = {
	//	{0x05, 0x00, 0xFF, "dsi error number"},
	//};

	char lcd_reg_dsi_error[] = {0x05};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_dsi_error), lcd_reg_dsi_error},
	};

	struct mipi_dsi_read_compare_data data = {
		.read_value = read_value,
		.expected_value = expected_value,
		.read_mask = read_mask,
		.reg_name = reg_name,
		.log_on = 1,
		.cmds = lcd_check_reg,
		.cnt = ARRAY_SIZE(lcd_check_reg),
	};
#endif;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_HS_SEND_SEQUENCE) {
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_OFF, "%s", "JL_KERNEL_LCD_POWER_OFF");

#if defined (CONFIG_HUAWEI_DSM)
		mipi_dsi_read_compare(&data, hisifd->mipi_dsi0_base);

		//panel_check_status_and_report_by_dsm(lcd_status_reg, \
		//	ARRAY_SIZE(lcd_status_reg), hisifd->mipi_dsi0_base);
#endif

		/* backlight off */
		hisi_lcd_backlight_off(pdev);

		// lcd display off sequence
		mipi_dsi_cmds_tx(lg_display_off_cmds, \
			ARRAY_SIZE(lg_display_off_cmds), hisifd->mipi_dsi0_base);

		pinfo->lcd_uninit_step = LCD_UNINIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_uninit_step = LCD_UNINIT_POWER_OFF;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_POWER_OFF) {
		if (((false == gesture_func) || hisifd->fb_shutdown) && !g_debug_enable_lcd_sleep_in) {
			// lcd gpio lowpower
			gpio_cmds_tx(lcd_gpio_lowpower_cmds, \
				ARRAY_SIZE(lcd_gpio_lowpower_cmds));
			// lcd gpio free
			gpio_cmds_tx(lcd_gpio_free_cmds, \
				ARRAY_SIZE(lcd_gpio_free_cmds));

			// lcd pinctrl lowpower
			pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
				ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

			mdelay(3);
			// lcd vcc disable
			vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
				ARRAY_SIZE(lcd_vcc_disable_cmds));
		} else {
			HISI_FB_INFO("display_off (gesture_func:%d)\n", gesture_func);
			/*backlights disable*/
			gpio_cmds_tx(lcd_gpio_sleep_lp_cmds, \
				ARRAY_SIZE(lcd_gpio_sleep_lp_cmds));

			/* lcd gpio free */
			gpio_cmds_tx(lcd_gpio_sleep_free_cmds, \
				ARRAY_SIZE(lcd_gpio_sleep_free_cmds));
		}

#ifdef CONFIG_HUAWEI_TS
		//if g_debug_enable_lcd_sleep_in == 1, it means don't turn off TP/LCD power
		//but only let lcd get into sleep.
		if ((g_lcd_control_tp_power || pinfo->esd_recover_step == LCD_ESD_RECOVER_POWER_OFF)
			&& !hisifd->fb_shutdown && !g_debug_enable_lcd_sleep_in) {
			error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts before suspend err\n");

			error = ts_power_control_notify(TS_SUSPEND_DEVICE, NO_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts suspend device err\n");
		}

		if (hisifd->fb_shutdown) {
			ts_thread_stop_notify();
		}
#endif

	} else {
		HISI_FB_ERR("failed to uninit lcd!\n");
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = platform_get_drvdata(pdev);
	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// lcd vcc finit
	vcc_cmds_tx(pdev, lcd_vcc_finit_cmds,
		ARRAY_SIZE(lcd_vcc_finit_cmds));

	// lcd pinctrl finit
	pinctrl_cmds_tx(pdev, lcd_pinctrl_finit_cmds,
		ARRAY_SIZE(lcd_pinctrl_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	static char last_bl_level=0;
	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc lcd_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust},
	};

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (unlikely(g_debug_enable)) {
		HISI_FB_INFO("Set backlight to %d. (remain times of backlight print: %d)\n", hisifd->bl_level, g_debug_enable);
		if (g_debug_enable == BACKLIGHT_PRINT_TIMES)
			LOG_JANK_D(JLID_KERNEL_LCD_BACKLIGHT_ON, "JL_KERNEL_LCD_BACKLIGHT_ON,%u", hisifd->bl_level);

		g_debug_enable = (g_debug_enable > 0) ? (g_debug_enable - 1) : 0;
	}

	if (!bl_level) {
		HISI_FB_INFO("Set backlight to 0 !!!\n");
	}

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		if (NULL == hisifd->mipi_dsi0_base) {
			HISI_FB_ERR("NULL Pointer\n");
			return -EINVAL;
		}
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

		bl_level_adjust[1] = bl_level * 255 / hisifd->panel_info.bl_max;
		if (last_bl_level != bl_level_adjust[1]){
			last_bl_level = bl_level_adjust[1];
			mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
				ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
		}
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
			hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


/******************************************************************************/
static ssize_t mipi_lg_panel_lcd_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "LG_eR69006A 6' CMD TFT\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lg_panel_lcd_cabc_mode_show(struct platform_device *pdev,
	char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", g_cabc_mode);
}

static ssize_t mipi_lg_panel_lcd_cabc_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag=-1;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base =hisifd->mipi_dsi0_base;

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
               return ret;

	flag=(int)val;
	if (flag==CABC_OFF ){
              g_cabc_mode=0;
              mipi_dsi_cmds_tx(lg_cabc_off_cmds, \
                               ARRAY_SIZE(lg_cabc_off_cmds),\
                               mipi_dsi0_base);
	}else  if (flag==CABC_UI_MODE) {
              g_cabc_mode=1;
              mipi_dsi_cmds_tx(lg_cabc_ui_on_cmds, \
                               ARRAY_SIZE(lg_cabc_ui_on_cmds),\
                               mipi_dsi0_base);
	} else if (flag==CABC_STILL_MODE ){
              g_cabc_mode=2;
              mipi_dsi_cmds_tx(lg_cabc_still_on_cmds, \
                               ARRAY_SIZE(lg_cabc_still_on_cmds),\
                               mipi_dsi0_base);
	}else if (flag==CABC_MOVING_MODE ){
              g_cabc_mode=3;
              mipi_dsi_cmds_tx(lg_cabc_moving_on_cmds, \
                               ARRAY_SIZE(lg_cabc_moving_on_cmds),\
                               mipi_dsi0_base);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, PAGE_SIZE, "%d\n", g_cabc_mode);
}

static ssize_t mipi_lg_panel_lcd_check_reg_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[4] = {0};
	uint32_t expected_value[4] = {0x1c, 0x00, 0x07, 0x00};
	uint32_t read_mask[4] = {0xFF, 0xFF, 0x07, 0xFF};
	char* reg_name[4] = {"power mode", "MADCTR", "pixel format", "image mode"};
	char lcd_reg_0a[] = {0x0a};
	char lcd_reg_0b[] = {0x0b};
	char lcd_reg_0c[] = {0x0c};
	char lcd_reg_0d[] = {0x0d};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0a), lcd_reg_0a},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0b), lcd_reg_0b},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0c), lcd_reg_0c},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0d), lcd_reg_0d},
	};

	struct mipi_dsi_read_compare_data data = {
		.read_value = read_value,
		.expected_value = expected_value,
		.read_mask = read_mask,
		.reg_name = reg_name,
		.log_on = 1,
		.cmds = lcd_check_reg,
		.cnt = ARRAY_SIZE(lcd_check_reg),
	};

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (!mipi_dsi_read_compare(&data, mipi_dsi0_base)) {
		ret = snprintf(buf, PAGE_SIZE, "OK\n");
	} else {
		ret = snprintf(buf, PAGE_SIZE, "ERROR\n");
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lg_panel_lcd_mipi_detect_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[2] = {0};
	uint32_t expected_value[2] = {0x80, 0x00};
	uint32_t read_mask[4] = {0xFF, 0xFF};
	char* reg_name[4] = {"signal mode", "dsi error number"};
	char lcd_reg_0e[] = {0x0e};
	char lcd_reg_05[] = {0x05};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0e), lcd_reg_0e},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_05), lcd_reg_05},
	};

	struct mipi_dsi_read_compare_data data = {
		.read_value = read_value,
		.expected_value = expected_value,
		.read_mask = read_mask,
		.reg_name = reg_name,
		.log_on = 1,
		.cmds = lcd_check_reg,
		.cnt = ARRAY_SIZE(lcd_check_reg),
	};

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (!mipi_dsi_read_compare(&data, mipi_dsi0_base)) {
		ret = snprintf(buf, PAGE_SIZE, "OK\n");
	} else {
		ret = snprintf(buf, PAGE_SIZE, "ERROR\n");
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00,0x04,0x37
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00,0x07,0x7F
};

static struct dsi_cmd_desc set_display_address[] = {
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x},
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y},
};

static int mipi_lg_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev || NULL == dirty) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	lcd_disp_x[1] = (dirty->x >> 8) & 0xff;
	lcd_disp_x[2] = dirty->x & 0xff;
	lcd_disp_x[3] = ((dirty->x + dirty->w - 1) >> 8) & 0xff;
	lcd_disp_x[4] = (dirty->x + dirty->w - 1) & 0xff;
	lcd_disp_y[1] = (dirty->y >> 8) & 0xff;
	lcd_disp_y[2] = dirty->y & 0xff;
	lcd_disp_y[3] = ((dirty->y + dirty->h - 1) >> 8) & 0xff;
	lcd_disp_y[4] = (dirty->y + dirty->h - 1) & 0xff;

	mipi_dsi_cmds_tx(set_display_address, \
		ARRAY_SIZE(set_display_address), hisifd->mipi_dsi0_base);

	return 0;
}


static int sram_test_feedback = 0;
irqreturn_t mipi_lg_panel_lcd_bist_check_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	sram_test_feedback = 1;
	HISI_FB_INFO("Get a te interrupt\n");

	return IRQ_HANDLED;
}

static ssize_t mipi_lg_panel_lcd_bist_check_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	struct dss_rect disp_rect = {0};
	ssize_t ret, error, error_pw = 0;
	uint32_t te0_vs_wd = 0;
	int irq_id = 0;
	int i = 0;
	int x, y = 0;
	int val = 0;
	int sent_pixels = 0;
	int remain_pixels = PATTERN_PIXELS_X_SIZE * PATTERN_PIXELS_Y_SIZE;
	char lcd_pattern_packet[PACKET_SIZE] = {0};

	disp_rect.w = PATTERN_PIXELS_X_SIZE;
	disp_rect.h = PATTERN_PIXELS_Y_SIZE;

	struct dsi_cmd_desc lcd_write_pattern[] = {
		{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_pattern_packet), lcd_pattern_packet},
	};

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->dss_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->dss_base + DSS_MIPI_DSI0_OFFSET;
	hisifd->lcd_self_testing = true;

#ifdef CONFIG_HUAWEI_TS
	error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
	error_pw = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Disable touchscreen during test.\n");
#endif

	// lcd display off sequence
	mipi_dsi_cmds_tx(lg_display_off_cmds, \
		ARRAY_SIZE(lg_display_off_cmds), mipi_dsi0_base);

	mipi_lg_panel_set_display_region(pdev, &disp_rect);

	mipi_dsi_cmds_tx(sram_test_pre_cmds, \
		ARRAY_SIZE(sram_test_pre_cmds), mipi_dsi0_base);

	mdelay(3);

	while (remain_pixels > 0) {
		lcd_pattern_packet[0] = (sent_pixels == 0) ? 0x2c : 0x3c;
		for (i = 0; i < PACKET_PIXELS_SIZE; i++) {
			y = (sent_pixels + i)/PATTERN_PIXELS_X_SIZE;
			x = (sent_pixels + i)%PATTERN_PIXELS_X_SIZE;
			val = y % 4;
			val = (val == 0 || val == 1) ? 0x55 : 0xAA;
			lcd_pattern_packet[i * 3 + 1] = val;
			lcd_pattern_packet[i * 3 + 2] = val;
			lcd_pattern_packet[i * 3 + 3] = val;
		}

/* Fail test
		if (sent_pixels == 0) {
			lcd_pattern_packet[1] = 0xff;
			lcd_pattern_packet[2] = 0xff;
			lcd_pattern_packet[3] = 0xff;
		}
*/

		mipi_dsi_cmds_tx(lcd_write_pattern, \
			ARRAY_SIZE(lcd_write_pattern), mipi_dsi0_base);

		remain_pixels -= PACKET_PIXELS_SIZE;
		sent_pixels += PACKET_PIXELS_SIZE;
	}

	sram_test_feedback = 0;

	// lcd pinctrl lowpower
	pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
		ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

	ret = gpio_request(GPIO_TE0, "gpio_te0");
	if(ret < 0){
		HISI_FB_INFO("could not reuquest gpio-%d \n",  GPIO_TE0);
		goto err_gpio_request;
	}

	gpio_direction_input(GPIO_TE0);
	irq_id = gpio_to_irq(GPIO_TE0);
	ret = request_irq(irq_id, mipi_lg_panel_lcd_bist_check_isr, IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND, "gpio_te0_irq", (void *)hisifd);
	if (ret) {
		HISI_FB_INFO("gpio irq register failed\n");
		goto err_irq_request;
	}

	mipi_dsi_cmds_tx(sram_test_post_cmds, \
		ARRAY_SIZE(sram_test_post_cmds), mipi_dsi0_base);

	mdelay(5);

	free_irq(irq_id, (void *)hisifd);

err_irq_request:
	gpio_free(GPIO_TE0);

err_gpio_request:
	if (sram_test_feedback == 0)
		ret = snprintf(buf, PAGE_SIZE, "pass\n");
	else
		ret = snprintf(buf, PAGE_SIZE, "fail\n");

	pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
		ARRAY_SIZE(lcd_pinctrl_normal_cmds));

	hisifd->off_fnc(hisifd);

	mdelay(500);

	hisifd->on_fnc(hisifd);


#if 0
	// lcd display on sequence
	mipi_dsi_cmds_tx(lg_initial_set, \
		ARRAY_SIZE(lg_initial_set), mipi_dsi0_base);
	mipi_dsi_cmds_tx(lg_power_supply_set, \
		ARRAY_SIZE(lg_power_supply_set), mipi_dsi0_base);
	mipi_dsi_cmds_tx(lg_display_on_cmds, \
		ARRAY_SIZE(lg_display_on_cmds), mipi_dsi0_base);


	sent_pixels = 0;
	remain_pixels = PATTERN_PIXELS_X_SIZE * PATTERN_PIXELS_Y_SIZE;
	memset(lcd_pattern_packet, 0, PACKET_SIZE);
	while (remain_pixels > 0) {
		lcd_pattern_packet[0] = (sent_pixels == 0) ? 0x2c : 0x3c;

		mipi_dsi_cmds_tx(lcd_write_pattern, \
			ARRAY_SIZE(lcd_write_pattern), mipi_dsi0_base);

		remain_pixels -= PACKET_PIXELS_SIZE;
		sent_pixels += PACKET_PIXELS_SIZE;
	}
#endif

#ifdef CONFIG_HUAWEI_TS
	if (!error_pw)
		error_pw = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
	if (!error)
		error = ts_power_control_notify(TS_AFTER_RESUME, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Enable touchscreen after test.\n");
#endif

	mipi_lg_panel_set_backlight(pdev, hisifd->bl_level);
	hisifd->lcd_self_testing = false;

	return ret;
}

static ssize_t mipi_lg_panel_lcd_sleep_ctrl_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = snprintf(buf, PAGE_SIZE, "enable_lcd_sleep_in=%d, pinfo->lcd_adjust_support=%d\n",
		g_debug_enable_lcd_sleep_in, hisifd->panel_info.lcd_adjust_support);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lg_panel_lcd_sleep_ctrl_store(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	unsigned long val = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.lcd_adjust_support) {
		g_debug_enable_lcd_sleep_in = val;
	}

	if (g_debug_enable_lcd_sleep_in == 2) {
		HISI_FB_INFO("LCD power off and Touch goto sleep\n");
		g_tp_power_ctrl = 1;	//used for pt  current test, tp sleep
	} else {
		HISI_FB_INFO("g_debug_enable_lcd_sleep_in is %d\n", g_debug_enable_lcd_sleep_in);
		g_tp_power_ctrl = 0;	//used for pt  current test, tp power off
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

/*for esd check*/
#if 0
static int error_cnt = 0;	//esd test
#endif
static int mipi_lg_panel_check_esd(struct platform_device* pdev)
{
	int ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	uint32_t read_value[1] = {0};
	uint32_t expected_value[1] = {0x1c};
	uint32_t read_mask[1] = {0x1c};
	char* reg_name[1] = {"power mode"};
	char lcd_reg_0a[] = {0x0a};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0a), lcd_reg_0a},
	};

	struct mipi_dsi_read_compare_data data = {
		.read_value = read_value,
		.expected_value = expected_value,
		.read_mask = read_mask,
		.reg_name = reg_name,
		.log_on = 0,
		.cmds = lcd_check_reg,
		.cnt = ARRAY_SIZE(lcd_check_reg),
	};

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = (struct hisi_fb_data_type*)platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = mipi_dsi_read_compare(&data, hisifd->mipi_dsi0_base);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

#if 0
	error_cnt = (error_cnt + 1) % 5;
	if ( error_cnt == 0) {
		HISI_FB_INFO("error_cnt = %d!!!!!++++++++++++++++++++++\n", error_cnt);
		return 1;
	}
	else {
		HISI_FB_INFO("error_cnt = %d!!!!!-----------------------\n", error_cnt);
		return 0;
	}
#endif

	return ret;
}

#define LCD_CMD_NAME_MAX 100
static char lcd_cmd_now[LCD_CMD_NAME_MAX] = {0};
static ssize_t mipi_lg_panel_lcd_test_config_show(struct platform_device *pdev,
	char *buf)
{
	if (!strncmp(lcd_cmd_now, "LCD_INCOME0", strlen("LCD_INCOME0")) || /* incoming sence0 config */
		!strncmp(lcd_cmd_now, "MMI0", strlen("MMI0")) || /* mmi sence0 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST0", strlen("RUNNINGTEST0")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU0", strlen("PROJECT_MENU0"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_0");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME1", strlen("LCD_INCOME1")) || /* incoming sence1 config */
		!strncmp(lcd_cmd_now, "MMI1", strlen("MMI1")) || /* mmi sence1 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST1", strlen("RUNNINGTEST1")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU1", strlen("PROJECT_MENU1"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_1");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME2", strlen("LCD_INCOME2")) || /* incoming sence2 config */
		!strncmp(lcd_cmd_now, "MMI2", strlen("MMI2")) || /* mmi sence2 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST2", strlen("RUNNINGTEST2")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU2", strlen("PROJECT_MENU2"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_2");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME3", strlen("LCD_INCOME3")) || /* incoming sence3 config */
		!strncmp(lcd_cmd_now, "MMI3", strlen("MMI3")) || /* mmi sence3 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST3", strlen("RUNNINGTEST3")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU3", strlen("PROJECT_MENU3"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_3");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME4", strlen("LCD_INCOME4")) || /* incoming sence4 config */
		!strncmp(lcd_cmd_now, "MMI4", strlen("MMI4")) || /* mmi sence4 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST4", strlen("RUNNINGTEST4")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU4", strlen("PROJECT_MENU4"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_4");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_0", strlen("CURRENT1_0"))) { /* current1 @ Color.WHITE */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5390000,5601000,1,9999999,8000,100000");//vol_min,vol_max,power_min,power_max,curr_min,curr_max
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_1", strlen("CURRENT1_1"))) { /* current1 @ Color.BLACK */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5390000,5601000,1,9999999,8000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_2", strlen("CURRENT1_2"))) { /* current1 @ Color.RED */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5390000,5601000,1,9999999,8000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_3", strlen("CURRENT1_3"))) { /* current1 @ Color.GREEN */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5390000,5601000,1,9999999,8000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_4", strlen("CURRENT1_4"))) { /* current1 @ Color.BLUE */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5390000,5601000,1,9999999,8000,100000");
	} else {
		return snprintf(buf, PAGE_SIZE, "INVALID");
	}
}

static ssize_t mipi_lg_panel_lcd_test_config_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base =hisifd->mipi_dsi0_base;

	if (strlen(buf) < LCD_CMD_NAME_MAX) {
		memcpy(lcd_cmd_now, buf, strlen(buf) + 1);
		HISI_FB_INFO("current test cmd:%s\n", lcd_cmd_now);
	} else {
		memcpy(lcd_cmd_now, "INVALID", strlen("INVALID") + 1);
		HISI_FB_INFO("invalid test cmd:%s\n");
	}

	return count;
}

static int g_support_mode = 0;
static ssize_t mipi_lg_panel_lcd_support_mode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "%d\n", g_support_mode);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lg_panel_lcd_support_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag = -1;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
               return ret;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	flag = (int)val;

	g_support_mode = flag;

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, PAGE_SIZE, "%d\n", g_support_mode);
}

static ssize_t mipi_lg_panel_lcd_support_checkmode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "checksum:0;lp2hs_mipi_check:0\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lg_panel_sharpness2d_table_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	sharp2d_t* sharp2d;
	int i = 0;
	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.sharp2d_table && buf) {
		sharp2d = (sharp2d_t*)buf;
		memcpy((void *)hisifd->panel_info.sharp2d_table, (void *)sharp2d, sizeof(sharp2d_t));

		for (i = 0; i < sizeof(sharp2d_t)/sizeof(uint32_t); i++) {
			HISI_FB_DEBUG("sharp2d_table[%d] = 0x%x \n", i, ((uint32_t*)hisifd->panel_info.sharp2d_table)[i]);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t mipi_lg_panel_sharpness2d_table_show(struct platform_device *pdev,	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;
	int i = 0;
	int buf_len = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (hisifd->panel_info.sharp2d_table && buf) {
		for (i = 0; i < sizeof(sharp2d_t)/sizeof(uint32_t); i++) {
			ret = snprintf(buf + buf_len, PAGE_SIZE, "sharp2d_table[%d] = 0x%x\n", i, ((uint32_t*)hisifd->panel_info.sharp2d_table)[i]);
			if (ret < 0) break;
			buf_len += ret;
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return buf_len;
}


static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_lg_panel_set_fastboot,
	.on = mipi_lg_panel_on,
	.off = mipi_lg_panel_off,
	.remove = mipi_lg_panel_remove,
	.set_backlight = mipi_lg_panel_set_backlight,
	.lcd_model_show = mipi_lg_panel_lcd_model_show,
	.lcd_cabc_mode_show = mipi_lg_panel_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_lg_panel_lcd_cabc_mode_store,
	.lcd_check_reg = mipi_lg_panel_lcd_check_reg_show,
	.lcd_mipi_detect = mipi_lg_panel_lcd_mipi_detect_show,
	.lcd_hkadc_debug_show = NULL,
	.lcd_hkadc_debug_store = NULL,
	.lcd_gram_check_show = NULL,
	.lcd_gram_check_store = NULL,
	.lcd_bist_check = mipi_lg_panel_lcd_bist_check_show,
	.set_display_region = mipi_lg_panel_set_display_region,
	.lcd_sleep_ctrl_show = mipi_lg_panel_lcd_sleep_ctrl_show,
	.lcd_sleep_ctrl_store = mipi_lg_panel_lcd_sleep_ctrl_store,
	.esd_handle = mipi_lg_panel_check_esd,
	.lcd_test_config_show = mipi_lg_panel_lcd_test_config_show,
	.lcd_test_config_store = mipi_lg_panel_lcd_test_config_store,
	.lcd_support_mode_show = mipi_lg_panel_lcd_support_mode_show,
	.lcd_support_mode_store = mipi_lg_panel_lcd_support_mode_store,
	.lcd_support_checkmode_show = mipi_lg_panel_lcd_support_checkmode_show,
	.set_display_resolution = NULL,
	.sharpness2d_table_store = mipi_lg_panel_sharpness2d_table_store,
	.sharpness2d_table_show = mipi_lg_panel_sharpness2d_table_show,
};


/*******************************************************************************
**
*/
static int mipi_lg_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	const char *lcd_bl_ic_name;
	char lcd_bl_ic_name_buf[LCD_BL_IC_NAME_MAX];

	g_lcd_control_tp_power = true;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_LG_ER69006A);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_LG_ER69006A);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	ret = of_property_read_string_index(np, "lcd-bl-ic-name", 0, &lcd_bl_ic_name);
	if (ret != 0) {
		memcpy(lcd_bl_ic_name_buf, "INVALID", strlen("INVALID"));
	} else {
		memcpy(lcd_bl_ic_name_buf, lcd_bl_ic_name, strlen(lcd_bl_ic_name) + 1);
	}
	HISI_FB_INFO("lcd_bl_ic_name=%s!\n", lcd_bl_ic_name_buf);

	if (hisi_fb_device_probe_defer(PANEL_MIPI_CMD, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_LG_ER69006A);

	//gpio_1_1
	gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 0);
	//gpio_1_2
	gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 1);
	// gpio_1_7
	gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 2);
	//gpio_2_4
	gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3);
	//gpio_24_5
	gpio_lcd_id0 = of_get_named_gpio(np, "gpios", 4);

	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width = 75;
	pinfo->height = 133;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 1;

	if (!strncmp(lcd_bl_ic_name_buf, "LM36923YFFR", strlen("LM36923YFFR"))) {
		pinfo->bl_min = 13;
		pinfo->bl_max = 1636;
		pinfo->bl_default = 819;
		pinfo->blpwm_precision_type = BLPWM_PRECISION_2048_TYPE;
		pinfo->bl_ic_ctrl_mode = REG_ONLY_MODE;
	} else {
		#ifdef CONFIG_BACKLIGHT_10000
		pinfo->bl_min = 157;
		pinfo->bl_max = 9960;
		pinfo->bl_default = 4000;
		pinfo->blpwm_precision_type = BLPWM_PRECISION_10000_TYPE;
		#else
		pinfo->bl_min = 1;
		pinfo->bl_max = 255;
		pinfo->bl_default = 102;
		#endif
	}
	pinfo->frc_enable = 0;
	pinfo->esd_enable = 1;
	pinfo->esd_skip_mipi_check = 1;
	pinfo->lcd_uninit_step_support = 1;
	pinfo->lcd_adjust_support = 1;

	pinfo->color_temperature_support = 1;
	pinfo->comform_mode_support = 1;
	g_support_mode = COMFORM_MODE | LED_RG_COLOR_TEMP_MODE;
	g_led_rg_para1 = 7;
	g_led_rg_para2 = 30983;

	//prefix ce & sharpness
	pinfo->prefix_ce_support = 0;
	pinfo->prefix_sharpness1D_support = 1;
	pinfo->prefix_sharpness2D_support = 1;
	pinfo->sharp2d_table = &sharp2d_table;

	//sbl
	pinfo->sbl_support = 1;
	pinfo->smart_bl.strength_limit = 128;
	pinfo->smart_bl.calibration_a = 25;
	pinfo->smart_bl.calibration_b = 95;
	pinfo->smart_bl.calibration_c = 3;
	pinfo->smart_bl.calibration_d = 0;
	pinfo->smart_bl.t_filter_control = 5;
	pinfo->smart_bl.backlight_min = 480;
	pinfo->smart_bl.backlight_max = 4096;
	pinfo->smart_bl.backlight_scale = 0xff;
	pinfo->smart_bl.ambient_light_min = 14;
	pinfo->smart_bl.filter_a = 1738;
	pinfo->smart_bl.filter_b = 6;
	pinfo->smart_bl.logo_left = 0;
	pinfo->smart_bl.logo_top = 0;
	pinfo->smart_bl.variance_intensity_space = 145;
	pinfo->smart_bl.slope_max = 54;
	pinfo->smart_bl.slope_min = 160;

	//ACM
	pinfo->acm_support = 1;
	if (pinfo->acm_support == 1) {
		pinfo->acm_lut_hue_table = acm_lut_hue_table;
		pinfo->acm_lut_hue_table_len = ARRAY_SIZE(acm_lut_hue_table);
		pinfo->acm_lut_sata_table = acm_lut_sata_table;
		pinfo->acm_lut_sata_table_len = ARRAY_SIZE(acm_lut_sata_table);
		pinfo->acm_lut_satr_table = acm_lut_satr_table;
		pinfo->acm_lut_satr_table_len = ARRAY_SIZE(acm_lut_satr_table);
		pinfo->acm_valid_num = 7;
		pinfo->r0_hh = 0x7f;
		pinfo->r0_lh = 0x0;
		pinfo->r1_hh = 0xff;
		pinfo->r1_lh = 0x80;
		pinfo->r2_hh = 0x17f;
		pinfo->r2_lh = 0x100;
		pinfo->r3_hh = 0x1ff;
		pinfo->r3_lh = 0x180;
		pinfo->r4_hh = 0x27f;
		pinfo->r4_lh = 0x200;
		pinfo->r5_hh = 0x2ff;
		pinfo->r5_lh = 0x280;
		pinfo->r6_hh = 0x37f;
		pinfo->r6_lh = 0x300;

		//ACM_CE
		pinfo->acm_ce_support = 1;
	}

	// Contrast Algorithm
	if (pinfo->prefix_ce_support == 1 || pinfo->acm_ce_support == 1) {
		pinfo->ce_alg_param.iDiffMaxTH = 900;
		pinfo->ce_alg_param.iDiffMinTH = 100;
		pinfo->ce_alg_param.iFlatDiffTH = 500;
		pinfo->ce_alg_param.iAlphaMinTH = 16;
		pinfo->ce_alg_param.iBinDiffMaxTH = 40000;

		pinfo->ce_alg_param.iDarkPixelMinTH = 16;
		pinfo->ce_alg_param.iDarkPixelMaxTH = 24;
		pinfo->ce_alg_param.iDarkAvePixelMinTH = 40;
		pinfo->ce_alg_param.iDarkAvePixelMaxTH = 80;
		pinfo->ce_alg_param.iWhitePixelTH = 236;
		pinfo->ce_alg_param.fweight = 42;
		pinfo->ce_alg_param.fDarkRatio = 51;
		pinfo->ce_alg_param.fWhiteRatio = 51;

		pinfo->ce_alg_param.iDarkPixelTH = 64;
		pinfo->ce_alg_param.fDarkSlopeMinTH = 149;
		pinfo->ce_alg_param.fDarkSlopeMaxTH = 161;
		pinfo->ce_alg_param.fDarkRatioMinTH = 18;
		pinfo->ce_alg_param.fDarkRatioMaxTH = 38;

		pinfo->ce_alg_param.iBrightPixelTH = 192;
		pinfo->ce_alg_param.fBrightSlopeMinTH = 149;
		pinfo->ce_alg_param.fBrightSlopeMaxTH = 174;
		pinfo->ce_alg_param.fBrightRatioMinTH = 20;
		pinfo->ce_alg_param.fBrightRatioMaxTH = 36;

		pinfo->ce_alg_param.iZeroPos0MaxTH = 120;
		pinfo->ce_alg_param.iZeroPos1MaxTH = 128;

		pinfo->ce_alg_param.iDarkFMaxTH = 16;
		pinfo->ce_alg_param.iDarkFMinTH = 12;
		pinfo->ce_alg_param.iPos0MaxTH = 120;
		pinfo->ce_alg_param.iPos0MinTH = 96;

		pinfo->ce_alg_param.fKeepRatio = 61;
	}

	//Gama LCP
	pinfo->gamma_support = 1;
	if (pinfo->gamma_support == 1) {
		pinfo->gamma_lut_table_R = gamma_lut_table_R;
		pinfo->gamma_lut_table_G = gamma_lut_table_G;
		pinfo->gamma_lut_table_B = gamma_lut_table_B;
		pinfo->gamma_lut_table_len = ARRAY_SIZE(gamma_lut_table_R);
		pinfo->igm_lut_table_R = igm_lut_table_R;
		pinfo->igm_lut_table_G = igm_lut_table_G;
		pinfo->igm_lut_table_B = igm_lut_table_B;
		pinfo->igm_lut_table_len = ARRAY_SIZE(igm_lut_table_R);

		pinfo->gmp_support = 1;
		pinfo->gmp_lut_table_low32bit = &gmp_lut_table_low32bit[0][0][0];
		pinfo->gmp_lut_table_high4bit = &gmp_lut_table_high4bit[0][0][0];
		pinfo->gmp_lut_table_len = ARRAY_SIZE(gmp_lut_table_low32bit);

		pinfo->xcc_support = 1;
		pinfo->xcc_table = xcc_table;
		pinfo->xcc_table_len = ARRAY_SIZE(xcc_table);
	}

	//ldi
	pinfo->ldi.h_back_porch = 23;
	pinfo->ldi.h_front_porch = 50;
	pinfo->ldi.h_pulse_width = 20;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 4;

	//mipi
	pinfo->mipi.dsi_bit_clk = 480;
	pinfo->mipi.dsi_bit_clk_val1 = 471;
	pinfo->mipi.dsi_bit_clk_val2 = 480;
	pinfo->mipi.dsi_bit_clk_val3 = 490;
	pinfo->mipi.dsi_bit_clk_val4 = 500;
	//pinfo->mipi.dsi_bit_clk_val5 = ;
	pinfo->dsi_bit_clk_upt_support = 1;
	pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

	pinfo->pxl_clk_rate = 144 * 1000000UL;

	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;
	pinfo->mipi.non_continue_en = 1;

	pinfo->pxl_clk_rate_div = 1;

	pinfo->type = PANEL_MIPI_CMD;
	pinfo->ifbc_type = IFBC_TYPE_NONE;
	pinfo->vsync_ctrl_type = VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
	pinfo->dirty_region_updt_support = 1;
	pinfo->dirty_region_info.left_align = 8;
	pinfo->dirty_region_info.right_align = 8;
	pinfo->dirty_region_info.top_align = 2;
	pinfo->dirty_region_info.bottom_align = 2;
	pinfo->dirty_region_info.w_align = -1;
	pinfo->dirty_region_info.h_align = -1;
	pinfo->dirty_region_info.w_min = 24;
	pinfo->dirty_region_info.h_min = 16;
	pinfo->dirty_region_info.top_start = -1;
	pinfo->dirty_region_info.bottom_start = -1;

	if(runmode_is_factory()) {
		HISI_FB_INFO("Factory mode, disable features: dirty update etc.\n");
		pinfo->dirty_region_updt_support = 0;
		pinfo->prefix_ce_support = 0;
		pinfo->prefix_sharpness1D_support = 0;
		pinfo->prefix_sharpness2D_support = 0;
		pinfo->sbl_support = 0;
		pinfo->acm_support = 0;
		pinfo->acm_ce_support = 0;
		pinfo->esd_enable = 0;
		pinfo->blpwm_input_ena = 0;
		pinfo->blpwm_precision_type = BLPWM_PRECISION_DEFAULT_TYPE;

		if (strncmp(lcd_bl_ic_name_buf, "LM36923YFFR", strlen("LM36923YFFR"))) {
			pinfo->bl_min = 1;
			pinfo->bl_max = 255;
		}

		pinfo->comform_mode_support = 0;
		g_support_mode = 0;
	}

	//The host processor must wait for more than 15us from the end of write data transfer to a command 2Ah/2Bh
	if (pinfo->dirty_region_updt_support == 1)
		pinfo->mipi.hs_wr_to_time = 17000;        // measured in nS

	// lcd vcc init
	ret = vcc_cmds_tx(pdev, lcd_vcc_init_cmds,
		ARRAY_SIZE(lcd_vcc_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("LCD vcc init failed!\n");
		goto err_return;
	}

	// lcd pinctrl init
	ret = pinctrl_cmds_tx(pdev, lcd_pinctrl_init_cmds,
		ARRAY_SIZE(lcd_pinctrl_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("Init pinctrl failed, defer\n");
		goto err_return;
	}

	// lcd vcc enable
	if (is_fastboot_display_enable()) {
		vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
			ARRAY_SIZE(lcd_vcc_enable_cmds));
	}

	// alloc panel device data
	ret = platform_device_add_data(pdev, &g_panel_data,
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("platform_device_add_data failed!\n");
		goto err_device_put;
	}

	hisi_fb_add_device(pdev);

	HISI_FB_DEBUG("-.\n");

	return 0;

err_device_put:
	platform_device_put(pdev);
err_return:
	return ret;
err_probe_defer:
	return -EPROBE_DEFER;

	return ret;
}

static const struct of_device_id hisi_panel_match_table[] = {
	{
		.compatible = DTS_COMP_LG_ER69006A,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_lg_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_lg_eR69006A",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_lg_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_lg_panel_init);
