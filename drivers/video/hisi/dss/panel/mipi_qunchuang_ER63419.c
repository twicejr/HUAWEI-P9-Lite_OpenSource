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

#define DTS_COMP_MIPI_QUNCHUANG_ER63419	"hisilicon,mipi_qunchuang_ER63419"

static struct hisi_fb_panel_data	g_panel_data;
static int g_lcd_fpga_flag = 0;

#define LCD_POWER_STATUS_CHECK	(0)


/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
static char adrsft1[] = {
	0xB0,
	0x04,
};

static char adrsft2[] = {
	0xD6,
	0x01,
};

 //Host I/F Setting
static char adrsft3[] = {
	0xB3,
	0x00,0x00,0x00,
};

static char adrsft4[] = {
	0xB4,
	0x00,
};

static char adr_comp3x[] = {
	0xEB,
	0x00,0x83,
};

// setting DPHY bps : 960Mbps
static char dsi_clk_div[] = {
	0xB6,
	0x3A,0xD3,
};
/*
// setting DPHY bps : 240Mbps
static char dsi_clk_div[] = {
	0xB6,
	0x39,0x93,
};
*/
static char adrsft6[] = {
	0xBE,
	0x04,
};

static char adrsft7[] = {
	0xC3,
	0x00,0x00,0x00,
};

static char adrsft8[] = {
	0xC5,
	0x00,
};

static char adrsft9[] = {
	0xEE,
	0x00,0x32,0x00,0x00,
};

static char adrsft10[] = {
	0xC5,
	0x00,
};

static char adrsft11[] = {
	0xEF,
	0x40,0x10,
};

//Panel Driving Setting
static char adrsft12[] = {
	0xC0,
	0x00,0x00,0x00,0x00,
};

static char adrsft13[] = {
	0xC1,
	0x80, 0x61, 0x00, 0xC1, 0x8C,
	0x83, 0x4A, 0x72, 0x0D, 0x56,
	0x7B, 0xE9, 0x94, 0x72, 0xD2,
	0x6B, 0x2B, 0x6C, 0xAE, 0x20,
	0x32, 0x8C, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x62, 0x02,
	0x23, 0x01, 0x00, 0x01, 0x11,
};

 static char adrsft14[] = {
	0xC2,
	0x09, 0x0A, 0x00, 0x08, 0x08,
	0xF0,0x00,0x08,
};

 static char adrsft15[] = {
	0xC4,
	0x70, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x05, 0x01,
};

static char adrsft16[] = {
	0xC6,
	0x5A, 0x04, 0x56, 0x04, 0x4C,
	0x00, 0x00, 0x01, 0x01, 0x01,
	0x01, 0x04, 0x4C, 0x04, 0x4C,
	0x00, 0x00, 0x04, 0x12, 0x08,
	0x5A,
};

static char adrsft17[] = {
	0xCB,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xE1,
	0x87, 0x00, 0xE0, 0x00, 0x00,
};

static char adrsft18[] = {
	0xCC,
	0x15,
};

static char adrsft19[] = {
	0xD7,
	0xFA, 0xFF, 0x21, 0x8E, 0x8C,
	0xF1, 0x87, 0x3F, 0x7E, 0x10,
	0x00, 0x00, 0x8F,
};

static char adrsft20[] = {
	0xD9,
	0x00, 0x00,
};

//Power Setting (Except Gamma Setting)
static char adrsft21[] = {
	0xD0,
	0x11,0x1E,0x0A,0xFD,
};

static char adrsft22[] = {
	0xD2,
	0x0F, 0x53, 0x53, 0x33, 0x12,
	0x33, 0x33, 0x33, 0x77, 0x77,
	0x33, 0x33, 0x33, 0x00, 0x00,
	0x00,
};

static char adrsft23[] = {
	0xD5,
	0x06, 0x00, 0x00, 0x01, 0x08,
	0x01, 0x08,
};

 //Gamma Setting
static char adrsft24[] = {
	0xC7,
	0x01, 0x0C, 0x13, 0x1D, 0x2C,
	0x3C, 0x47, 0x58, 0x3C, 0x44,
	0x4F, 0x5C, 0x65, 0x6C, 0x75,
	0x01, 0x0C, 0x13, 0x1D, 0x2B,
	0x39, 0x43, 0x54, 0x38, 0x41,
	0x4D, 0x5A, 0x63, 0x6A, 0x74,
};

static char adrsft25[] = {
	0xC8,
	0x01, 0x00, 0xff, 0x00, 0x00,
	0xFC, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0xFC, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0xFC,0x0F,
};

static char adrsft26[] = {
	0x2A,
	0x00, 0x00, 0x05, 0x9F,
};

static char adrsft27[] = {
	0x2B,
	0x00, 0x00, 0x09, 0xFF,
};

static char tear_on[] = {
	0x35,
	0x00,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};

/*******************************************************************************
** Power OFF Sequence(Normal to power off)
*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static struct dsi_cmd_desc lcd_display_on_cmd[] = {
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft1), adrsft1},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft2), adrsft2},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft3), adrsft3},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft4), adrsft4},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(dsi_clk_div), dsi_clk_div},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft6), adrsft6},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft7), adrsft7},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft8), adrsft8},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft9), adrsft9},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft10), adrsft10},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft11), adrsft11},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft12), adrsft12},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft13), adrsft13},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft14), adrsft14},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft15), adrsft15},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft16), adrsft16},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft17), adrsft17},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(adrsft18), adrsft18},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft19), adrsft19},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft20), adrsft20},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft21), adrsft21},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft22), adrsft22},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft23), adrsft23},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft24), adrsft24},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft25), adrsft25},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft26), adrsft26},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adrsft27), adrsft27},
	{DTYPE_GEN_WRITE2, 0, 10, WAIT_TYPE_US, sizeof(tear_on), tear_on},
	{DTYPE_DCS_WRITE, 0, 50, WAIT_TYPE_MS, sizeof(display_on), display_on},
	{DTYPE_DCS_WRITE, 0, 150, WAIT_TYPE_MS, sizeof(exit_sleep), exit_sleep},
};

static struct dsi_cmd_desc lcd_ifbc_rsp3x_en_cmd[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US, sizeof(adr_comp3x), adr_comp3x},
};

static struct dsi_cmd_desc lcd_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 20, WAIT_TYPE_MS, sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 80, WAIT_TYPE_MS, sizeof(enter_sleep), enter_sleep}
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
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDIO_NAME, &vcc_lcdio, 1800000, 1800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc lcd_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
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
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"
#define GPIO_LCD_N5V5_ENABLE_NAME 	"gpio_lcd_n5v5_enable"

static uint32_t	gpio_lcd_vcc1v8;
static uint32_t	gpio_lcd_bl_enable;
static uint32_t	gpio_lcd_reset;
static uint32_t	gpio_lcd_p5v5_enable;
static uint32_t	gpio_lcd_n5v5_enable;

static struct gpio_desc fpga_lcd_gpio_request_cmds[] = {
	/* vcc1v8 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
};

static struct gpio_desc fpga_lcd_gpio_free_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* vcc1v8 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
};

static struct gpio_desc fpga_lcd_gpio_normal_cmds[] = {
	/* vcc1v8 enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 1},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 1,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
};

static struct gpio_desc fpga_lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* vcc1v8 disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* backlight enable input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* vcc1v8 disable */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
};

static struct gpio_desc asic_lcd_gpio_request_cmds[] = {
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
};

static struct gpio_desc asic_lcd_gpio_free_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct gpio_desc asic_lcd_gpio_normal_cmds[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
};

static struct gpio_desc asic_lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},

	/* backlight enable input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};


/*******************************************************************************
**
*/
static int mipi_qunchuang_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (g_lcd_fpga_flag == 0) {
		// lcd pinctrl normal
		pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
			ARRAY_SIZE(lcd_pinctrl_normal_cmds));

		// lcd gpio request
		gpio_cmds_tx(asic_lcd_gpio_request_cmds,
			ARRAY_SIZE(asic_lcd_gpio_request_cmds));
	} else {
		// lcd gpio request
		gpio_cmds_tx(fpga_lcd_gpio_request_cmds,
			ARRAY_SIZE(fpga_lcd_gpio_request_cmds));
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_qunchuang_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
#if LCD_POWER_STATUS_CHECK
	uint32_t status = 0;
	uint32_t try_times = 0;
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (g_lcd_fpga_flag == 1)
		mipi_dsi0_base = hisifd->mipi_dsi1_base;
	else
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		if (g_lcd_fpga_flag == 0) {
			// lcd vcc enable
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
				ARRAY_SIZE(lcd_vcc_enable_cmds));
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
		if (g_lcd_fpga_flag == 0) {
			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
				ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			// lcd gpio request
			gpio_cmds_tx(asic_lcd_gpio_request_cmds, \
				ARRAY_SIZE(asic_lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(asic_lcd_gpio_normal_cmds, \
				ARRAY_SIZE(asic_lcd_gpio_normal_cmds));
		} else {
			// lcd gpio request
			gpio_cmds_tx(fpga_lcd_gpio_request_cmds, \
				ARRAY_SIZE(fpga_lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(fpga_lcd_gpio_normal_cmds, \
				ARRAY_SIZE(fpga_lcd_gpio_normal_cmds));
		}

		// lcd display on sequence
		mipi_dsi_cmds_tx(lcd_display_on_cmd, \
			ARRAY_SIZE(lcd_display_on_cmd), mipi_dsi0_base);

		if (pinfo->ifbc_type == IFBC_TYPE_RSP3X)
			mipi_dsi_cmds_tx(lcd_ifbc_rsp3x_en_cmd, \
				ARRAY_SIZE(lcd_ifbc_rsp3x_en_cmd), mipi_dsi0_base);

	#if LCD_POWER_STATUS_CHECK
		//check lcd power status
		outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0x0A06);
		status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		while (status & 0x10) {
			udelay(50);
			if (++try_times > 100) {
				try_times = 0;
				HISI_FB_ERR("Read lcd power status timeout!\n");
				break;
			}

			status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		}
		status = inp32(mipi_dsi0_base + MIPIDSI_GEN_PLD_DATA_OFFSET);
		HISI_FB_INFO("LCD Power State = 0x%x.\n", status);
	#endif

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_qunchuang_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	if (g_lcd_fpga_flag == 1)
		mipi_dsi0_base = hisifd->mipi_dsi1_base;
	else
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

	// backlight off
	hisi_lcd_backlight_off(pdev);

	// lcd display off sequence
	mipi_dsi_cmds_tx(lcd_display_off_cmds, \
		ARRAY_SIZE(lcd_display_off_cmds), mipi_dsi0_base);

	if (g_lcd_fpga_flag == 0) {
		// lcd gpio lowpower
		gpio_cmds_tx(asic_lcd_gpio_lowpower_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_lowpower_cmds));
		// lcd gpio free
		gpio_cmds_tx(asic_lcd_gpio_free_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_free_cmds));

		// lcd pinctrl lowpower
		pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
			ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

		mdelay(3);
		// lcd vcc disable
		vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
			ARRAY_SIZE(lcd_vcc_disable_cmds));
	} else {
		// lcd gpio lowpower
		gpio_cmds_tx(fpga_lcd_gpio_lowpower_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_lowpower_cmds));
		// lcd gpio free
		gpio_cmds_tx(fpga_lcd_gpio_free_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_free_cmds));
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_qunchuang_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (g_lcd_fpga_flag == 0) {
		// lcd vcc finit
		vcc_cmds_tx(pdev, lcd_vcc_finit_cmds,
			ARRAY_SIZE(lcd_vcc_finit_cmds));

		// lcd pinctrl finit
		pinctrl_cmds_tx(pdev, lcd_pinctrl_finit_cmds,
			ARRAY_SIZE(lcd_pinctrl_finit_cmds));

		HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_qunchuang_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc lcd_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	}else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		if (g_lcd_fpga_flag == 1)
			mipi_dsi0_base = hisifd->mipi_dsi1_base;
		else
			mipi_dsi0_base = hisifd->mipi_dsi0_base;

		bl_level_adjust[1] = bl_level * 255 / hisifd->panel_info.bl_max;
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
			ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
			hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00, 0x04, 0x37
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00, 0x07, 0x7F
};

static struct dsi_cmd_desc set_display_address[] = {
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x},
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y},
};

static int mipi_qunchuang_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	if (g_lcd_fpga_flag == 1)
		mipi_dsi0_base = hisifd->mipi_dsi1_base;
	else
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

	pinfo = &(hisifd->panel_info);

	if ((dirty->x != 0) || (dirty->w != pinfo->xres) ||
		(dirty->y % 2 != 0) || (dirty->h % 2 != 0) || (dirty->h < 8) ||
		(dirty->x >= pinfo->xres) || (dirty->w > pinfo->xres) || ((dirty->x + dirty->w) > pinfo->xres) ||
		(dirty->y >= pinfo->yres) || (dirty->h > pinfo->yres) || ((dirty->y + dirty->h) > pinfo->yres)) {
		HISI_FB_ERR("dirty_region(%d,%d, %d,%d) not support!\n",
			dirty->x, dirty->y, dirty->w, dirty->h);

		BUG_ON(1);
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
		ARRAY_SIZE(set_display_address), mipi_dsi0_base);

	return 0;
}


/*******************************************************************************
**
*/
static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_qunchuang_panel_set_fastboot,
	.on = mipi_qunchuang_panel_on,
	.off = mipi_qunchuang_panel_off,
	.remove = mipi_qunchuang_panel_remove,
	.set_backlight = mipi_qunchuang_panel_set_backlight,
	.set_display_region = mipi_qunchuang_panel_set_display_region,
};


/*******************************************************************************
**
*/
static int mipi_qunchuang_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;
	uint32_t lcd_ifbc_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_MIPI_QUNCHUANG_ER63419);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_MIPI_QUNCHUANG_ER63419);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_DUAL_MIPI_CMD;
	}

	ret = of_property_read_u32(np, LCD_IFBC_TYPE_NAME, &lcd_ifbc_type);
	if (ret) {
		HISI_FB_ERR("get ifbc_type failed!\n");
		lcd_ifbc_type = IFBC_TYPE_NONE;
	}

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_MIPI_QUNCHUANG_ER63419);

	ret = of_property_read_u32(np, FPGA_FLAG_NAME, &g_lcd_fpga_flag);
	if (ret) {
		HISI_FB_WARNING("need to get g_lcd_fpga_flag resource in fpga, not needed in asic!\n");
	}

	if (g_lcd_fpga_flag == 1) {
		//gpio_5_3
		gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 0);
		//gpio_5_7
		gpio_lcd_vcc1v8 = of_get_named_gpio(np, "gpios", 1);
		//gpio_9_4
		gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3);
		//gpio_9_5
		gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 4);
		//gpio_9_6
		gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 5);
	} else {
		//gpio_1_1
		gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 0);
		//gpio_1_2
		gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 1);
		// gpio_1_7
		gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 2);
		//gpio_2_4
		gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3);
	}

	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1440;
	pinfo->yres = 2560;
	pinfo->width  = 68;
	pinfo->height = 120;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 0;

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

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;

	//sbl
	pinfo->sbl_support = 0;
	pinfo->smart_bl.strength_limit = 0xff;
	pinfo->smart_bl.calibration_a = 0;
	pinfo->smart_bl.calibration_b = 0;
	pinfo->smart_bl.calibration_c = 0;
	pinfo->smart_bl.calibration_d = 0;
	pinfo->smart_bl.t_filter_control = 0;
	pinfo->smart_bl.backlight_min = 0;
	pinfo->smart_bl.backlight_max = 0;
	pinfo->smart_bl.backlight_scale = 0xffff;
	pinfo->smart_bl.ambient_light_min = 0;
	pinfo->smart_bl.filter_a = 0;
	pinfo->smart_bl.filter_b = 0;

	if (g_lcd_fpga_flag == 1) {
		// setting DPHY bps : 240Mbps
		dsi_clk_div[0] = 0xB6;
		dsi_clk_div[1] = 0x39;
		dsi_clk_div[2] = 0x93;

		//ldi
		pinfo->ldi.h_back_porch = 40; //P264\P305
		pinfo->ldi.h_front_porch = 105;
		pinfo->ldi.h_pulse_width = 10;
		pinfo->ldi.v_back_porch = 12;
		pinfo->ldi.v_front_porch = 14;
		pinfo->ldi.v_pulse_width = 4;

		pinfo->mipi.dsi_bit_clk = 120;
		pinfo->mipi.dsi_bit_clk_val1 = 110; //110.4
		pinfo->mipi.dsi_bit_clk_val2 = 120;
		pinfo->mipi.dsi_bit_clk_val3 = 130; //129.6
		pinfo->mipi.dsi_bit_clk_val4 = 140; //139.2
		pinfo->mipi.dsi_bit_clk_val5 = 150; //148.8
		pinfo->dsi_bit_clk_upt_support = 1;
		pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

		//non_continue amend : measured in UI
		pinfo->mipi.clk_post_adjust = 0;
		pinfo->mipi.clk_pre_adjust= 0;
		pinfo->mipi.clk_t_hs_prepare_adjust= 0;
		pinfo->mipi.clk_t_lpx_adjust= 0;
		pinfo->mipi.clk_t_hs_trial_adjust= 0;
		pinfo->mipi.clk_t_hs_exit_adjust= 0;
		pinfo->mipi.clk_t_hs_zero_adjust= 0;
		pinfo->mipi.non_continue_en = 0;

		pinfo->pxl_clk_rate = 20 * 1000000; //40 * 1000000;
	} else {
		// setting DPHY bps : 960Mbps
		dsi_clk_div[0] = 0xB6;
		dsi_clk_div[1] = 0x3A;
		dsi_clk_div[2] = 0xC3;

		//ldi
		//65.7fps
		pinfo->ldi.h_back_porch = 96;
		pinfo->ldi.h_front_porch = 108;
		pinfo->ldi.h_pulse_width = 48;
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
		pinfo->dsi_bit_clk_upt_support = 0;
		pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

		//non_continue amend : measured in UI
		pinfo->mipi.clk_post_adjust = 0;
		pinfo->mipi.clk_pre_adjust= 0;
		pinfo->mipi.clk_t_hs_prepare_adjust= 0;
		pinfo->mipi.clk_t_lpx_adjust= 0;
		pinfo->mipi.clk_t_hs_trial_adjust= 0;
		pinfo->mipi.clk_t_hs_exit_adjust= 0;
		pinfo->mipi.clk_t_hs_zero_adjust= 0;
		pinfo->mipi.non_continue_en = 0;

		// pxl_clk_rate * bits_per_pixel <= dsi_bit_clk * 2 * lane_nums
		pinfo->pxl_clk_rate = 288 * 1000000;
	}

	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->pxl_clk_rate_div = 2;

	pinfo->vsync_ctrl_type = 0; //VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
	pinfo->dirty_region_updt_support = 0;
	pinfo->dirty_region_info.left_align = -1;
	pinfo->dirty_region_info.right_align = -1;
	pinfo->dirty_region_info.top_align = 2;
	pinfo->dirty_region_info.bottom_align = 2;
	pinfo->dirty_region_info.w_align = -1;
	pinfo->dirty_region_info.h_align = -1;
	pinfo->dirty_region_info.w_min = pinfo->xres;
	pinfo->dirty_region_info.h_min = 8;
	pinfo->dirty_region_info.top_start = -1;
	pinfo->dirty_region_info.bottom_start = -1;

	if (pinfo->ifbc_type == IFBC_TYPE_RSP3X) {
		pinfo->ifbc_cmp_dat_rev0 = 0;
		pinfo->ifbc_cmp_dat_rev1 = 0;
		pinfo->ifbc_auto_sel = 1;

		pinfo->pxl_clk_rate_div *= 3;
	}

	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}

	if (g_lcd_fpga_flag == 0) {
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
		.compatible = DTS_COMP_MIPI_QUNCHUANG_ER63419,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_qunchuang_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_qunchuang_ER63419",
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_qunchuang_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_qunchuang_panel_init);
