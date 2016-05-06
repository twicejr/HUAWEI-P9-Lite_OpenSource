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
#include "display_effect_jdi_R63452_5p5.h"

#define DTS_COMP_JDI_R63452_5P2 "hisilicon,mipi_jdi_R63452_5P2"
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
#define TP_RS_CALL 1
static struct hisi_fb_panel_data g_panel_data;
static int g_debug_enable = 0;
static int g_cabc_mode = 1;
#ifdef CONFIG_HUAWEI_TS
extern bool gesture_func;
extern bool g_lcd_control_tp_power;
#endif
extern unsigned int g_led_rg_para1;
extern unsigned int g_led_rg_para2;

#define LCD_ID_BUF_SIZE		20
static int panel_lcd_id_buf[LCD_ID_BUF_SIZE];
static uint32_t new_lcd_supported = 0;
/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
static char nvm_access_protect[] = {
	0xB0,
	0x04,
};

static char te_enable[] = {
	0x35,
	0x00,
};

static char esd_check_enable[] = {
	0xF7,
	0x20,
};

//open cabc func
static char set_b0_cmd[] = {
	0xB0,
	0x00,
};

static char te_line[] = {
	0x44,
	0x03, 0x80,
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

static struct dsi_cmd_desc jdi_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(esd_check_enable), esd_check_enable},
//	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
//		sizeof(te_line), te_line},
	{DTYPE_DCS_WRITE, 0, 125, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep },
	{DTYPE_DCS_WRITE, 0, 45, WAIT_TYPE_MS,
		sizeof(display_on), display_on },
};

static struct dsi_cmd_desc jdi_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 52, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 102, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep},
};

static struct dsi_cmd_desc nvm_access_protect_cmd[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(nvm_access_protect), nvm_access_protect},
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


/******************************************************************************
*
** SRAM test sequence
*/
static char MCAP[] = {
	0xB0,
	0x04,
};

static char test_reg_F1h[] = {
	0xF1,
	0x20,
};

static char test_reg_E0h[] = {
	0xE0,
	0x90,
};

static char test_reg_FBh[] = {
	0xFB,
	0x30,
};

static char test_reg_FCh[] = {
	0xFC,
	0x04, 0x64, 0x00, 0x10, 0x06, 0x00, 0x20,
};

static struct dsi_cmd_desc sram_test_pre_cmds[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(MCAP), MCAP},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_F1h), test_reg_F1h},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_E0h), test_reg_E0h},
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_FBh), test_reg_FBh},
};

static struct dsi_cmd_desc sram_test_post_cmds[] = {
	{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(test_reg_FCh), test_reg_FCh},
};


/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME		"lcdio-vcc"		//ldo4
#define VCC_LCDANALOG_NAME	"lcdanalog-vcc"		//ldo17

static struct regulator *vcc_lcdio;
static struct regulator *vcc_lcdanalog;

static struct vcc_desc lcd_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 3300000, 3300000, WAIT_TYPE_MS, 0},
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
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"	//oversea verison:gpio31, all net version:gpio136
#define GPIO_LCD_VCC3V1_NAME	"gpio_lcd_vcc3v1"
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"		//gpio 53
#define GPIO_LCD_N5V5_ENABLE_NAME "gpio_lcd_n5v5_enable"	//gpio 52
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"	//gpio20
#define GPIO_LCD_ID0_NAME	"gpio_lcd_id0"		//oversea version:gpio19, all net version:gpio67
#define GPIO_LCD_ID1_NAME "gpio_lcd_id1"		//oversea version:gpio29, all net version:gpio9

static uint32_t gpio_lcd_bl_enable;
static uint32_t gpio_lcd_vcc3v1;
static uint32_t gpio_lcd_vcc1v8;
static uint32_t gpio_lcd_p5v5_enable;
static uint32_t gpio_lcd_n5v5_enable;
static uint32_t gpio_lcd_reset;
static uint32_t gpio_lcd_id0;
static uint32_t gpio_lcd_id1;

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
	/* id1 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc lcd_gpio_free_cmds[] = {
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
	/* id0 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
	/* id1 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
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
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 3,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
};

static struct gpio_desc lcd_gpio_normal_cmds_sub2[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 1,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
	/* id0 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
	/* id1 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 7,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* backlight enable input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset input */
	/*{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},*/
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
	/* id1 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
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
	/* lcd id */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc lcd_gpio_sleep_normal_cmds[] = {
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 1,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
	/* lcd id0 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
	/* lcd id1 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc lcd_gpio_sleep_lp_cmds[] = {
	/* backlight disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 1,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};


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
static int mipi_jdi_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

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

static int mipi_jdi_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_status_reg[] = {
		{0x0A, 0x38, 0xFF, "lcd power state"},
	};
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		g_debug_enable = BACKLIGHT_PRINT_TIMES;
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
		if (!gesture_func && (!g_debug_enable_lcd_sleep_in)) {
			HISI_FB_INFO("Init power on(regulator enabling).\n");
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
			HISI_FB_INFO("Init power on(regulator has enabled).\n");
			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
				ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			gpio_cmds_tx(lcd_gpio_sleep_request_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_request_cmds));

			gpio_cmds_tx(lcd_gpio_sleep_normal_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_normal_cmds));
			msleep(50);
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
#ifdef CONFIG_HUAWEI_TS
		if (TP_RS_CALL != g_debug_enable_lcd_sleep_in) {
			HISI_FB_INFO("TP resume and after resume\n");
			error = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
			error = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
		}
#endif
		//init code
		mipi_dsi_cmds_tx(jdi_display_on_cmds, \
			ARRAY_SIZE(jdi_display_on_cmds), mipi_dsi0_base);

		mipi_dsi_cmds_tx(nvm_access_protect_cmd, \
			ARRAY_SIZE(nvm_access_protect_cmd), mipi_dsi0_base);

		// lcd display effect sequence
		if (pinfo->panel_effect_support) {
			mipi_dsi_cmds_tx(jdi_display_effect_on_cmds, \
				ARRAY_SIZE(jdi_display_effect_on_cmds), mipi_dsi0_base);
		}

		if ((pinfo->bl_set_type & BL_SET_BY_BLPWM) || (pinfo->bl_set_type & BL_SET_BY_SH_BLPWM)) {
			mipi_dsi_cmds_tx(pwm_out_on_cmds, \
				ARRAY_SIZE(pwm_out_on_cmds), mipi_dsi0_base);
		}
		g_cabc_mode = 1;
#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(lcd_status_reg, \
			ARRAY_SIZE(lcd_status_reg), mipi_dsi0_base);
#endif
		HISI_FB_INFO("enable bl_en gpio.\n");
		mdelay(12);	//time of mipi on to lcd reset on shoud be larger than 10ms
		// lcd gpio normal
		gpio_cmds_tx(lcd_gpio_normal_cmds_sub2, \
			ARRAY_SIZE(lcd_gpio_normal_cmds_sub2));
		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {

	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	/* backlight on */
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_esd_detect[] = {
		{0xFA, 0x00, 0x01, "lcd esd detect"},
	};
#endif;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_HS_SEND_SEQUENCE) {
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_OFF, "%s", "JL_KERNEL_LCD_POWER_OFF");
		HISI_FB_INFO("display off(download display off sequence).\n");
#if defined (CONFIG_HUAWEI_DSM)
		panel_status_report_by_dsm(lcd_esd_detect, \
			ARRAY_SIZE(lcd_esd_detect), hisifd->mipi_dsi0_base, 10);
#endif
		/* backlight off */
		hisi_lcd_backlight_off(pdev);

		// lcd display off sequence
		mipi_dsi_cmds_tx(jdi_display_off_cmds, \
			ARRAY_SIZE(jdi_display_off_cmds), hisifd->mipi_dsi0_base);

		pinfo->lcd_uninit_step = LCD_UNINIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_uninit_step = LCD_UNINIT_POWER_OFF;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_POWER_OFF) {
		if (!hisifd->fb_shutdown) {
			if (!gesture_func && !g_debug_enable_lcd_sleep_in) {
				HISI_FB_INFO("display off(regulator disabling).\n");
				// lcd gpio lowpower
				gpio_cmds_tx(lcd_gpio_lowpower_cmds, \
					ARRAY_SIZE(lcd_gpio_lowpower_cmds));
				// lcd gpio free
				gpio_cmds_tx(lcd_gpio_free_cmds, \
					ARRAY_SIZE(lcd_gpio_free_cmds));

				// lcd pinctrl lowpower
				pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
					ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

				// lcd vcc disable
				vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
					ARRAY_SIZE(lcd_vcc_disable_cmds));
			} else {
				HISI_FB_INFO("display off(regulator not need disabling).\n");
				/*backlights disable*/
				gpio_cmds_tx(lcd_gpio_sleep_lp_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_lp_cmds));

				/* lcd gpio free */
				gpio_cmds_tx(lcd_gpio_sleep_free_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_free_cmds));

				/* lcd pinctrl normal */
				pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
					ARRAY_SIZE(lcd_pinctrl_normal_cmds));
			}
#ifdef CONFIG_HUAWEI_TS
			if (TP_RS_CALL != g_debug_enable_lcd_sleep_in) {
				HISI_FB_INFO("TP before suspend and suspend\n");
				error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
				error = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
			}
#endif
		}else {
			HISI_FB_INFO("display shutting down(regulator disabling).\n");
			// lcd gpio lowpower
			gpio_cmds_tx(lcd_gpio_lowpower_cmds, \
				ARRAY_SIZE(lcd_gpio_lowpower_cmds));
			// lcd gpio free
			gpio_cmds_tx(lcd_gpio_free_cmds, \
				ARRAY_SIZE(lcd_gpio_free_cmds));

			// lcd pinctrl lowpower
			pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
				ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

			// lcd vcc disable
			vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
				ARRAY_SIZE(lcd_vcc_disable_cmds));
#ifdef CONFIG_HUAWEI_TS
			ts_thread_stop_notify();
#endif
		}
	} else {
			HISI_FB_ERR("failed to uninit lcd!\n");
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
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

static int mipi_jdi_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
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

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

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
static ssize_t mipi_jdi_panel_lcd_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "jdi_R63452 5.2' CMD TFT 1080 x 1920\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_jdi_panel_lcd_cabc_mode_show(struct platform_device *pdev,
	char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", g_cabc_mode);
}

static ssize_t mipi_jdi_panel_lcd_cabc_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag=-1;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	mipi_dsi0_base =hisifd->mipi_dsi0_base;

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
               return ret;

	flag=(int)val;
	if (flag==CABC_OFF ){
              g_cabc_mode=0;
              mipi_dsi_cmds_tx(jdi_cabc_off_cmds, \
                               ARRAY_SIZE(jdi_cabc_off_cmds),\
                               mipi_dsi0_base);
	}else  if (flag==CABC_UI_MODE) {
              g_cabc_mode=1;
              mipi_dsi_cmds_tx(jdi_cabc_ui_on_cmds, \
                               ARRAY_SIZE(jdi_cabc_ui_on_cmds),\
                               mipi_dsi0_base);
	} else if (flag==CABC_STILL_MODE ){
              g_cabc_mode=2;
              mipi_dsi_cmds_tx(jdi_cabc_still_on_cmds, \
                               ARRAY_SIZE(jdi_cabc_still_on_cmds),\
                               mipi_dsi0_base);
	}else if (flag==CABC_MOVING_MODE ){
              g_cabc_mode=3;
              mipi_dsi_cmds_tx(jdi_cabc_moving_on_cmds, \
                               ARRAY_SIZE(jdi_cabc_moving_on_cmds),\
                               mipi_dsi0_base);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, count, "%d\n", g_cabc_mode);
}

static ssize_t mipi_jdi_panel_lcd_check_reg_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[5] = {0};
	uint32_t expected_value[5] = {0x38, 0x00, 0x07, 0x00, 0x00};
	uint32_t read_mask[5] = {0xFF, 0xFF, 0x07, 0xFF, 0xFF};
	char* reg_name[5] = {"power mode", "MADCTR", "pixel format", "image mode", "mipi error"};
	char lcd_reg_0a[] = {0x0a};
	char lcd_reg_0b[] = {0x0b};
	char lcd_reg_0c[] = {0x0c};
	char lcd_reg_0d[] = {0x0d};
	char lcd_reg_ab[] = {0xab};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0a), lcd_reg_0a},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0b), lcd_reg_0b},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0c), lcd_reg_0c},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0d), lcd_reg_0d},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_ab), lcd_reg_ab},
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

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (!mipi_dsi_read_compare(&data, mipi_dsi0_base)) {
		ret = snprintf(buf, PAGE_SIZE, "P-0x0a:0x%x, 0x0b:0x%x, 0x0c:0x%x, 0x0d:0x%x, 0xab:0x%x\n",
			data.read_value[0], data.read_value[1], data.read_value[2], data.read_value[3], data.read_value[4]);
	} else {
		ret = snprintf(buf, PAGE_SIZE, "F-0x0a:0x%x, 0x0b:0x%x, 0x0c:0x%x, 0x0d:0x%x, 0xab:0x%x\n",
			data.read_value[0], data.read_value[1], data.read_value[2], data.read_value[3], data.read_value[4]);
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_jdi_panel_lcd_mipi_detect_show(struct platform_device *pdev, char *buf)
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

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

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

static int mipi_jdi_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

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
static int bist_test_count = 0;
static irqreturn_t mipi_jdi_panel_lcd_bist_check_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	sram_test_feedback = 1;
	HISI_FB_INFO("Get a te interrupt\n");

	return IRQ_HANDLED;
}

static ssize_t mipi_jdi_panel_lcd_gram_check_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;

	ret = snprintf(buf, PAGE_SIZE, "0\n");

	return ret;
}

static ssize_t mipi_jdi_panel_lcd_gram_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	return count;
}

static ssize_t mipi_jdi_panel_lcd_bist_check_show(struct platform_device *pdev,
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
	int j = 0;
	int x, y = 0;
	int value = 0;
	int sent_pixels = 0;
	int remain_pixels = PATTERN_PIXELS_X_SIZE * PATTERN_PIXELS_Y_SIZE;
	char lcd_pattern_packet[PACKET_SIZE] = {0};
	int line_packet_remain = PATTERN_PIXELS_X_SIZE;

	disp_rect.w = PATTERN_PIXELS_X_SIZE;
	disp_rect.h = PATTERN_PIXELS_Y_SIZE;

	struct dsi_cmd_desc lcd_write_pattern[] = {
		{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_pattern_packet), lcd_pattern_packet},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->dss_base + DSS_MIPI_DSI0_OFFSET;
	hisifd->lcd_self_testing = true;

#ifdef CONFIG_HUAWEI_TS
	error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
	error_pw = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Disable touchscreen during test.\n");
#endif

	//lcd display off sequence
	mipi_dsi_cmds_tx(jdi_display_off_cmds, \
		ARRAY_SIZE(jdi_display_off_cmds), mipi_dsi0_base);

	mipi_jdi_panel_set_display_region(pdev, &disp_rect);

	mipi_dsi_cmds_tx(sram_test_pre_cmds, \
		ARRAY_SIZE(sram_test_pre_cmds), mipi_dsi0_base);

	mdelay(3);

	while (remain_pixels > 0) {
		lcd_pattern_packet[0] = (sent_pixels == 0) ? 0x2c : 0x3c;
		for (i = 0; i < PACKET_PIXELS_SIZE; i++) {
			y = (sent_pixels + i)/PATTERN_PIXELS_X_SIZE;
			x = (sent_pixels + i)%PATTERN_PIXELS_X_SIZE;
			value = (x /8)%2;
			value = (value == 0) ? 0x55 : 0xAA;

			lcd_pattern_packet[i*3+1]=value;
			lcd_pattern_packet[i*3+2]=value;
			lcd_pattern_packet[i*3+3]=value;
		}

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
	ret = request_irq(irq_id, mipi_jdi_panel_lcd_bist_check_isr, IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND, "gpio_te0_irq", (void *)hisifd);
	if (ret) {
		HISI_FB_INFO("gpio irq register failed\n");
		goto err_irq_request;
	}

	mipi_dsi_cmds_tx(sram_test_post_cmds, \
		ARRAY_SIZE(sram_test_post_cmds), mipi_dsi0_base);

	mdelay(6);

	disable_irq(irq_id);
	free_irq(irq_id, (void *)hisifd);

err_irq_request:
	gpio_free(GPIO_TE0);

err_gpio_request:
	if (1 == bist_test_count) {
		HISI_FB_INFO("another bist test\n");
		sram_test_feedback = 0;
	}

	if (sram_test_feedback == 0)
		ret = snprintf(buf, PAGE_SIZE, "pass\n");
	else
		ret = snprintf(buf, PAGE_SIZE, "fail\n");

	bist_test_count = 1;
	pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
		ARRAY_SIZE(lcd_pinctrl_normal_cmds));

	hisifd->off_fnc(hisifd);

	mdelay(500);

	hisifd->on_fnc(hisifd);

#ifdef CONFIG_HUAWEI_TS
	if (!error_pw)
		error_pw = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
	if (!error)
		error = ts_power_control_notify(TS_AFTER_RESUME, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Enable touchscreen after test.\n");
#endif

	mipi_jdi_panel_set_backlight(pdev, hisifd->bl_level);
	hisifd->lcd_self_testing = false;

	return ret;
}

static ssize_t mipi_jdi_panel_lcd_sleep_ctrl_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = snprintf(buf, PAGE_SIZE, "enable_lcd_sleep_in=%d\n", g_debug_enable_lcd_sleep_in);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

#define SLEEP_IN	0
#define SLEEP_OUT	1
static ssize_t mipi_jdi_panel_lcd_sleep_ctrl_store(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	unsigned long val = 0;

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	g_debug_enable_lcd_sleep_in = val;

	if (g_debug_enable_lcd_sleep_in == 2) {
		HISI_FB_INFO("LCD power off and Touch goto sleep\n");
		g_tp_power_ctrl = 1;
	} else {
		HISI_FB_INFO("g_debug_enable_lcd_sleep_in is %d\n", g_debug_enable_lcd_sleep_in);
		g_tp_power_ctrl = 0;
	}
	return ret;
}

/*for esd check*/
#if 0
static int error_cnt = 0;	//esd test
#endif
static int mipi_jdi_panel_check_esd(struct platform_device* pdev)
{
	int ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	uint32_t read_value[1] = {0};
	uint32_t expected_value[1] = {0x38};
	uint32_t read_mask[1] = {0xFF};
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

	BUG_ON(pdev == NULL);
	hisifd = (struct hisi_fb_data_type*)platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

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
static ssize_t mipi_jdi_panel_lcd_test_config_show(struct platform_device *pdev,
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
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME5", strlen("LCD_INCOME5")) || /* incoming sence5 config */
		!strncmp(lcd_cmd_now, "MMI5", strlen("MMI5")) || /* mmi sence5 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST5", strlen("RUNNINGTEST5")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU5", strlen("PROJECT_MENU5"))) {
		return snprintf(buf, PAGE_SIZE, "CURRENT1_5");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME6", strlen("LCD_INCOME6")) || /* incoming sence6 config */
		!strncmp(lcd_cmd_now, "MMI6", strlen("MMI6")) || /* mmi sence6 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST6", strlen("RUNNINGTEST6")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU6", strlen("PROJECT_MENU6"))) {
			return snprintf(buf, PAGE_SIZE, "CHECKSUM1");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME7", strlen("LCD_INCOME7")) || /* incoming sence7 config */
		!strncmp(lcd_cmd_now, "MMI7", strlen("MMI7")) || /* mmi sence7 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST7", strlen("RUNNINGTEST7")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU7", strlen("PROJECT_MENU7"))) {
		return snprintf(buf, PAGE_SIZE, "CHECKSUM2");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME8", strlen("LCD_INCOME8")) || /* incoming sence8 config */
		!strncmp(lcd_cmd_now, "MMI8", strlen("MMI8")) || /* mmi sence8 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST8", strlen("RUNNINGTEST8")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU8", strlen("PROJECT_MENU8"))) {
		return snprintf(buf, PAGE_SIZE, "CHECKSUM3");
	} else if (!strncmp(lcd_cmd_now, "LCD_INCOME9", strlen("LCD_INCOME9")) || /* incoming sence9 config */
		!strncmp(lcd_cmd_now, "MMI9", strlen("MMI9")) || /* mmi sence9 config */
		!strncmp(lcd_cmd_now, "RUNNINGTEST9", strlen("RUNNINGTEST9")) ||
		!strncmp(lcd_cmd_now, "PROJECT_MENU9", strlen("PROJECT_MENU9"))) {
		return snprintf(buf, PAGE_SIZE, "CHECKSUM4");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_0", strlen("CURRENT1_0"))) { /* current1 @ Color.WHITE */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");//vol_min,vol_max,power_min,power_max,curr_min,curr_max
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_1", strlen("CURRENT1_1"))) { /* current1 @ Color.BLACK */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_2", strlen("CURRENT1_2"))) { /* current1 @ Color.RED */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_3", strlen("CURRENT1_3"))) { /* current1 @ Color.GREEN */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_4", strlen("CURRENT1_4"))) { /* current1 @ Color.BLUE */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");
	} else if (!strncmp(lcd_cmd_now, "CURRENT1_5", strlen("CURRENT1_5"))) { /* current1 @ Smile */
		return snprintf(buf, PAGE_SIZE, "/sys/class/ina231/ina231_0/ina231_set,"
										"/sys/class/ina231/ina231_0/ina231_value,"
										"5000000,18000000,1,9999999,-820000,100000");
	} else if (!strncmp(lcd_cmd_now, "CHECKSUM", strlen("CHECKSUM"))) { /* CHECKSUM */
		return snprintf(buf, PAGE_SIZE, "/sys/class/graphics/fb0/lcd_checksum");
	} else {
		return snprintf(buf, PAGE_SIZE, "INVALID");
	}
}

static ssize_t mipi_jdi_panel_lcd_test_config_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
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
static ssize_t mipi_jdi_panel_lcd_support_mode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "%d\n", g_support_mode);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_jdi_panel_lcd_support_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag = -1;
	struct hisi_fb_data_type *hisifd = NULL;
	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
               return ret;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	flag = (int)val;

	g_support_mode = flag;

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, count, "%d\n", g_support_mode);
}

static ssize_t mipi_jdi_panel_lcd_support_checkmode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "checksum:0;lp2hs_mipi_check:0\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_jdi_panel_sharpness2d_table_store(struct platform_device *pdev,
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

static ssize_t mipi_jdi_panel_sharpness2d_table_show(struct platform_device *pdev, char *buf)
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

static ssize_t mipi_jdi_panel_info_show(struct platform_device *pdev, char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;
	uint32_t bl_max_val = 0;
	uint32_t bl_min_val = 0;
	uint32_t bl_device_level = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("pdev NULL pointer\n");
		return 0;
	};
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("hisifd NULL pointer\n");
		return 0;
	}

	if (new_lcd_supported) {
		HISI_FB_INFO("VN1 and later, panel_info.bl_max is %d\n", hisifd->panel_info.bl_max);
		if(255 == hisifd->panel_info.bl_max)
			bl_max_val = 198;
		else
			bl_max_val = 7680;
		bl_min_val = hisifd->panel_info.bl_min;
		bl_device_level = 10000;	//MPS bl ic
	} else {
		bl_max_val = hisifd->panel_info.bl_max;
		bl_min_val = hisifd->panel_info.bl_min;
		bl_device_level = 255;		//TI bl ic
	}

	if (255 == hisifd->panel_info.bl_max) {
		HISI_FB_INFO("factory version\n");
		bl_device_level = 255;	//factory version bldevicelevel is set to 255 level
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (buf) {
		ret = snprintf(buf, PAGE_SIZE, "blmax:%u,blmin:%u,lcdtype:%s,bldevicelevel:%u,\n",
				bl_max_val, bl_min_val, "LCD",bl_device_level);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_jdi_panel_set_fastboot,
	.on = mipi_jdi_panel_on,
	.off = mipi_jdi_panel_off,
	.remove = mipi_jdi_panel_remove,
	.set_backlight = mipi_jdi_panel_set_backlight,
	.lcd_model_show = mipi_jdi_panel_lcd_model_show,
	.lcd_cabc_mode_show = mipi_jdi_panel_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_jdi_panel_lcd_cabc_mode_store,
	.lcd_check_reg = mipi_jdi_panel_lcd_check_reg_show,
	.lcd_mipi_detect = mipi_jdi_panel_lcd_mipi_detect_show,
	.lcd_hkadc_debug_show = NULL,
	.lcd_hkadc_debug_store = NULL,
	.lcd_gram_check_show = mipi_jdi_panel_lcd_gram_check_show,
	.lcd_gram_check_store = mipi_jdi_panel_lcd_gram_check_store,
	.lcd_bist_check = mipi_jdi_panel_lcd_bist_check_show,
	.set_display_region = mipi_jdi_panel_set_display_region,
	.lcd_sleep_ctrl_show = mipi_jdi_panel_lcd_sleep_ctrl_show,
	.lcd_sleep_ctrl_store = mipi_jdi_panel_lcd_sleep_ctrl_store,
	.esd_handle = mipi_jdi_panel_check_esd,
	.lcd_test_config_show = mipi_jdi_panel_lcd_test_config_show,
	.lcd_test_config_store = mipi_jdi_panel_lcd_test_config_store,
	.lcd_support_mode_show = mipi_jdi_panel_lcd_support_mode_show,
	.lcd_support_mode_store = mipi_jdi_panel_lcd_support_mode_store,
	.lcd_support_checkmode_show = mipi_jdi_panel_lcd_support_checkmode_show,
	.set_display_resolution = NULL,
	.sharpness2d_table_store = mipi_jdi_panel_sharpness2d_table_store,
	.sharpness2d_table_show = mipi_jdi_panel_sharpness2d_table_show,
	.panel_info_show = mipi_jdi_panel_info_show,
};


/*******************************************************************************
**
*/
static int mipi_jdi_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
#ifdef CONFIG_HUAWEI_TS
	g_lcd_control_tp_power = true;	//not use fb_notify to control touch timing.
#endif
	int panel_lcd_id = 0;

	panel_lcd_id = (int)simple_strtol(panel_lcd_id_buf, NULL, 0);

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_JDI_R63452_5P2);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_JDI_R63452_5P2);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(PANEL_MIPI_CMD, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_INFO("%s, lcd_id is 0x%x\n", DTS_COMP_JDI_R63452_5P2, panel_lcd_id);

	ret = of_property_read_u32(np, "new_lcd_supported", &new_lcd_supported);
	if (ret) {
		HISI_FB_INFO("not define new_lcd_supported, set to 0!\n");
		new_lcd_supported = 0;
	}

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

	gpio_lcd_id1 = of_get_named_gpio(np, "gpios", 5);

	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width = 64;
	pinfo->height = 114;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 1;

#ifdef CONFIG_BACKLIGHT_10000
	pinfo->bl_min = 157;
	pinfo->bl_max = 9960;
	pinfo->bl_default = 4000;
	pinfo->blpwm_precision_type = BLPWM_PRECISION_10000_TYPE;
#else
	pinfo->bl_min = 4;
	pinfo->bl_max = 255;
	pinfo->bl_default = 102;
#endif

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 1;
	pinfo->esd_skip_mipi_check = 1;
	pinfo->lcd_uninit_step_support = 1;

	pinfo->color_temperature_support = 1;
	pinfo->comform_mode_support = 1;
	pinfo->panel_effect_support = 1;
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
		pinfo->acm_valid_num = acm_valid_num;
		pinfo->r0_hh = acm_r0_hh;
		pinfo->r0_lh = acm_r0_lh;
		pinfo->r1_hh = acm_r1_hh;
		pinfo->r1_lh = acm_r1_lh;
		pinfo->r2_hh = acm_r2_hh;
		pinfo->r2_lh = acm_r2_lh;
		pinfo->r3_hh = acm_r3_hh;
		pinfo->r3_lh = acm_r3_lh;
		pinfo->r4_hh = acm_r4_hh;
		pinfo->r4_lh = acm_r4_lh;
		pinfo->r5_hh = acm_r5_hh;
		pinfo->r5_lh = acm_r5_lh;
		pinfo->r6_hh = acm_r6_hh;
		pinfo->r6_lh = acm_r6_lh;

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
		pinfo->comform_mode_support = 0;
		pinfo->blpwm_input_ena = 0;
		pinfo->blpwm_precision_type = BLPWM_PRECISION_DEFAULT_TYPE;
		pinfo->bl_min = 4;
		pinfo->bl_max = 255;
		pinfo->panel_effect_support = 0;
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
		.compatible = DTS_COMP_JDI_R63452_5P2,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_jdi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_jdi_R63452_5P2",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_jdi_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

static int __init early_parse_lcd_id_cmdline(char *arg)
{
	int len = 0;
	memset(panel_lcd_id_buf, 0, sizeof(panel_lcd_id_buf));
	if (arg) {
		len = strlen(arg);

		if (len > sizeof(panel_lcd_id_buf)) {
			len = sizeof(panel_lcd_id_buf);
		}
		memcpy(panel_lcd_id_buf, arg, len);
	} else {
		HISI_FB_INFO("%s : arg is NULL\n", __func__);
	}

	return 0;
}
early_param("LCD_ID", early_parse_lcd_id_cmdline);

module_init(mipi_jdi_panel_init);
