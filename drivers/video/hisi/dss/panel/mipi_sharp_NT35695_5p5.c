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
#include "mipi_sharp_NT35695_5p5.h"
#include <huawei_platform/log/log_jank.h>
#include <linux/hisi/hw_cmdline_parse.h>
#include "display_effect_sharp_NT35695_5p5.h"

#define DTS_COMP_SHARP_NT35695_5P5 "hisilicon,mipi_sharp_NT35695_5P5"
#define LCD_VDDIO_TYPE_NAME	"lcd-vddio-type"
#define CABC_OFF	(0)
#define CABC_UI_MODE	(1)
#define CABC_STILL_MODE	(2)
#define CABC_MOVING_MODE	(3)
#define CHECKSUM_SIZE	(8)
#define CHECKSUM_PIC_NUM  (10)
#define CHECKSUM_PIC_N  (4)
#define PACKET_PIXELS_SIZE	(216)
#define PACKET_SIZE	(PACKET_PIXELS_SIZE*3+1)
#define BACKLIGHT_PRINT_TIMES	10

static int checksum_pic_n = 0;
static uint32_t expected_checksum[CHECKSUM_PIC_N][CHECKSUM_SIZE] = {
	{0x5B, 0x5E, 0x8E, 0xEB, 0xE5, 0x2B, 0x46, 0xF9}, //mmi
	{0xBE, 0x8A, 0x67, 0x5C, 0x6, 0xFA, 0xFB, 0xDB}, //runningtest1
	{0xFB, 0xCE, 0x5C, 0x3D, 0x4D, 0x0F, 0x41, 0x6}, //runningtest2
	{0xA6, 0x91, 0x1B, 0xD7, 0x71, 0x44, 0x3F, 0x75}, //runningtest3
};

static struct hisi_fb_panel_data g_panel_data;

static int hkadc_buf = 0;
static bool checksum_enable_ctl = false;
static int checksum_pic_num = 0;
static int g_debug_enable = 0;
static int g_cabc_mode = 2;

static bool g_lp2hs_mipi_test = false;
static bool g_lp2hs_mipi_test_result = false;

#ifdef CONFIG_HUAWEI_TS
#define TP_RS_CALL 1
extern bool gesture_func;
extern bool g_lcd_control_tp_power;
#endif
extern unsigned int g_led_rg_para1;
extern unsigned int g_led_rg_para2;

#define LCD_ID_BUF_SIZE		20
static int panel_lcd_id_buf[LCD_ID_BUF_SIZE];
static uint32_t new_lcd_supported = 0;
static int panel_lcd_id = 0;

extern u8 color_temp_cal_buf[32];
#define SCALING_UP_FUNC (0)

static uint32_t expected_checksum_crc[CHECKSUM_PIC_NUM][CHECKSUM_SIZE] = {
	{0x23, 0xFD, 0xDE, 0x5B, 0x56, 0x54, 0x01, 0xCD}, //blue
	{0xA4, 0xEE, 0x4D, 0x01, 0xF3, 0xA6, 0x61, 0x65}, //colorbar
	{0x97, 0xCC, 0x66, 0x82, 0xDD, 0x2D, 0x55, 0xE6}, //family_people
	{0x08, 0x1F, 0x21, 0xA4, 0xDB, 0x30, 0x21, 0x1D}, //gaussin
	{0x2E, 0x2B, 0xD1, 0x0C, 0xBA, 0x0B, 0x3B, 0xCB}, //green
	{0xED, 0x6D, 0xC5, 0x69, 0x31, 0x1B, 0x7F, 0x77}, //radiation_color
	{0x96, 0x96, 0x10, 0x7A, 0xAB, 0x42, 0x2A, 0x3A}, //red
	{0x6B, 0xDD, 0xBB, 0xB8, 0x91, 0x53, 0xE4, 0xF6}, //trees
	{0xAC, 0xA2, 0x5C, 0x90, 0x7D, 0x6C, 0xF1, 0xB6}, //v_grad
	{0x9B, 0x40, 0x1F, 0x2D, 0x47, 0x1D, 0x10, 0x3C}, //white
};

static int mipi_sharp_panel_set_display_region(struct platform_device *pdev, struct dss_rect *dirty);

/*******************************************************************************
** Scaling up function
*/
#if SCALING_UP_FUNC
static char ena_scale[] = {
	0x50,
	0x01,
};
#endif

/*******************************************************************************
** Partial update setting
*/
static char partial_setting_1[] = {
	0xFF,
	0x10,
};

static char partial_setting_2[] = {
	0xFB,
	0x01,
};

static char partial_setting_3[] = {
	0xC9,
	0x4B,0x04,0x21,0x00,0x0F,0x03,0x19,0x01,0x97,0x10,0xF0,
};

/*******************************************************************************
** sequence for ifbc func
*/
static char vesa_dsc0[] = {
	0xFF,
	0x10,
};

//0x03:vesa enable, 0x00: disable
static char vesa_dsc1[] = {
	0xC0,
	0x03,
};

static char vesa_dsc2[] = {
	0xC1,
	0x09,0x20,0x00,0x10,0x02,
	0x00,0x03,0x1C,0x02,0x05,
	0x00,0x0F,0x06,0x67,0x03,
	0x2E,
};

static char vesa_dsc3[] = {
	0xC2,
	0x10,0xF0,
};

static char vesa_dsc4[] = {
	0xFB,
	0x01,
};

/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
static char caset_data[] = {
	0x2A,
	0x00,0x00,0x04, 0x37,
};

static char paset_data[] = {
	0x2B,
	0x00,0x00,0x07,0x7F,
};

static char non_reload[] = {
	0XFB,
	0x01,
};

#if 0
//cut3.1 does no need software solution for snow defect any more
static char page_E_select[] = {
	0XFF,
	0xE0,
};

static char sram_solution[] = {
	0XB8,
	0xAD,
};

static char page_1_select[] = {
	0XFF,
	0x10,
};
#endif
static char mipi_crc_ecc_cmd[] = {
	0xB0,
	0x03,
};

static char set_display_mode[] = {
	0xBB,
	0x10,	//command
};

static char tear_on[] = {
	0x35,
	0x00,
};

static char display_on[] = {
	0x29,
};

static char exit_sleep[] = {
	0x11,
};

static char bl_enable[] = {
	0x53,
	0x24,
};

static char te_line[] = {
	0x44,
	0x07, 0x78,
};

//select mipi lane numbers, 0x00:1 lane, 0x01: 2 lane, and so on. Default 4 lanes
static char lane_nums[] = {
	0xBA,
	0x03,
};

/*******************************************************************************
** setting PWM frequency to 58KHZ
*/
static char set_page3[] = {
	0xFF,
	0x23,
};

static char set_pwm_freq[] = {
	0x08,
	0x03,
};

static char set_page0[] = {
	0xFF,
	0x10,
};

/*for lp2hs_mipi test*/

static char lp2hs_mipi[] = {
	0x36, 0x08,
};

static struct dsi_cmd_desc sharp_lp2hs_mipi_cmds[] = {
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(lp2hs_mipi), lp2hs_mipi},
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

static struct dsi_cmd_desc lcd_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(tear_on), tear_on},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(caset_data), caset_data},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(paset_data), paset_data},
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(mipi_crc_ecc_cmd), mipi_crc_ecc_cmd},
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(set_display_mode), set_display_mode},
#if 0
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(set_page3), set_page3},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(non_reload), non_reload},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(set_pwm_freq), set_pwm_freq},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(set_page0), set_page0},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(non_reload), non_reload},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(lane_nums), lane_nums},
#endif
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(te_line), te_line},
	{DTYPE_DCS_WRITE, 0, 105, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 0, 45, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
};

static struct dsi_cmd_desc lcd_vesa3x_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(vesa_dsc0), vesa_dsc0},
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(vesa_dsc1), vesa_dsc1},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(vesa_dsc2), vesa_dsc2},
	{DTYPE_DCS_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(vesa_dsc3), vesa_dsc3},
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(vesa_dsc4), vesa_dsc4},
};

static struct dsi_cmd_desc lcd_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 60, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
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



static struct dsi_cmd_desc lcd_partial_updt_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(partial_setting_1), partial_setting_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(partial_setting_2), partial_setting_2},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(partial_setting_3), partial_setting_3},
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
	/*vddio enable*/
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
	/* vci enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc lcd_vci_disable_cmds[] = {
	/* vci disable */
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 15},
};

static struct vcc_desc lcd_vddio_disable_cmds[] = {
	/* vddio disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 15},
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
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"	//oversea verison:gpio31, all net version:gpio136   for  EVA
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"		//gpio 53	for EVA
#define GPIO_LCD_N5V5_ENABLE_NAME "gpio_lcd_n5v5_enable"	//gpio 52	for EVA
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"	//gpio20	for EVA
#define GPIO_LCD_ID0_NAME	"gpio_lcd_id0"		//oversea version:gpio19, all net version:gpio67	for EVA
#define GPIO_LCD_ID1_NAME "gpio_lcd_id1"		//oversea version:gpio29, all net version:gpio9		for EVA

static uint32_t gpio_lcd_bl_enable;
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
	/* lcd reset */
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
	/*lcd reset */
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
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* lcd reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 3,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
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

static struct gpio_desc lcd_gpio_lowpower_cmd1[] = {
	/* backlight disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
};

static struct gpio_desc lcd_gpio_lowpower_cmd2[] = {
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
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
	/* lcd id0 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &gpio_lcd_id0, 0},
	/* lcd id1 */
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
};

static struct gpio_desc lcd_gpio_sleep_lp_cmds[] = {
	/* backlight disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 1,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

static struct gpio_desc lcd_gpio_bl_disable_cmds[] = {
	/* backlight disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

static struct gpio_desc lcd_gpio_bl_enable_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
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
static int mipi_sharp_panel_set_fastboot(struct platform_device *pdev)
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

static int mipi_sharp_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_status_reg[] = {
		{0x0A, 0x9C, 0xFF, "lcd power state"},
		{0x0E, 0x80, 0xC1, "lcd signal mode"},
	};
#endif
	u32 lp2hs_mipi_check_read_value[1] = {0};
	u32 lp2hs_mipi_check_expected_value[1] = {0x08};
	u32 lp2hs_mipi_check_read_mask[1] = {0xFF};
	char* lp2hs_mipi_check_reg_name[1] = {"power mode"};
	char lp2hs_mipi_check_lcd_reg_36[] = {0x36};

	struct dsi_cmd_desc lp2hs_mipi_check_lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lp2hs_mipi_check_lcd_reg_36), lp2hs_mipi_check_lcd_reg_36},
	};

	struct mipi_dsi_read_compare_data g_lp2hs_mipi_check_data = {
		.read_value = lp2hs_mipi_check_read_value,
		.expected_value = lp2hs_mipi_check_expected_value,
		.read_mask = lp2hs_mipi_check_read_mask,
		.reg_name = lp2hs_mipi_check_reg_name,
		.log_on = 1,
		.cmds = lp2hs_mipi_check_lcd_check_reg,
		.cnt = ARRAY_SIZE(lp2hs_mipi_check_lcd_check_reg),
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		g_debug_enable = BACKLIGHT_PRINT_TIMES;
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
		if (!gesture_func && !g_debug_enable_lcd_sleep_in) {
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
		//update mipi lane numbers
		lane_nums[1] = pinfo->mipi.lane_nums;

		// lcd display effect sequence
		if (pinfo->panel_effect_support) {
			mipi_dsi_cmds_tx(sharp_display_effect_on_cmds, \
				ARRAY_SIZE(sharp_display_effect_on_cmds), mipi_dsi0_base);
		}

		if (pinfo->dirty_region_updt_support) {
			// NT35695 partial update sequence
			mipi_dsi_cmds_tx(lcd_partial_updt_cmds, \
				ARRAY_SIZE(lcd_partial_updt_cmds), mipi_dsi0_base);
		}

		// lcd display on sequence
		mipi_dsi_cmds_tx(lcd_display_on_cmds, \
			ARRAY_SIZE(lcd_display_on_cmds), mipi_dsi0_base);

		if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_SINGLE) {
			// NT35695 partial update sequence
			mipi_dsi_cmds_tx(lcd_vesa3x_on_cmds, \
				ARRAY_SIZE(lcd_vesa3x_on_cmds), mipi_dsi0_base);
		}

		if ((pinfo->bl_set_type & BL_SET_BY_BLPWM) || (pinfo->bl_set_type & BL_SET_BY_SH_BLPWM)) {
			mipi_dsi_cmds_tx(pwm_out_on_cmds, \
				ARRAY_SIZE(pwm_out_on_cmds), mipi_dsi0_base);
		}
		g_cabc_mode = 2;
#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(lcd_status_reg, \
			ARRAY_SIZE(lcd_status_reg), mipi_dsi0_base);
#endif

		HISI_FB_INFO("enable bl_en gpio.\n");
		gpio_cmds_tx(lcd_gpio_normal_cmds_sub2, \
			ARRAY_SIZE(lcd_gpio_normal_cmds_sub2));

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		if (g_lp2hs_mipi_test) {
			HISI_FB_INFO("downloading code for lp2hs check\n");
			mipi_dsi_cmds_tx(sharp_lp2hs_mipi_cmds, ARRAY_SIZE(sharp_lp2hs_mipi_cmds), mipi_dsi0_base);
			mdelay(50);
			if (!mipi_dsi_read_compare(&g_lp2hs_mipi_check_data, mipi_dsi0_base)) {
				HISI_FB_INFO("lp2hs test OK\n");
				g_lp2hs_mipi_test_result = true;
			} else {
				HISI_FB_INFO("lp2hs test fail\n");
				g_lp2hs_mipi_test_result = false;
			}
		}
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	/* backlight on */
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_sharp_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_esd_detect[] = {
		{0x05, 0x00, 0xFF, "lcd esd detect"},
	};
#endif

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
		mipi_dsi_cmds_tx(lcd_display_off_cmds, \
			ARRAY_SIZE(lcd_display_off_cmds), hisifd->mipi_dsi0_base);

		pinfo->lcd_uninit_step = LCD_UNINIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_uninit_step = LCD_UNINIT_POWER_OFF;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_POWER_OFF) {
		if (!hisifd->fb_shutdown)  {
#ifdef CONFIG_HUAWEI_TS
			if (TP_RS_CALL != g_debug_enable_lcd_sleep_in) {
				HISI_FB_INFO("TP before suspend and suspend\n");
				error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
				error = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
			}
#endif
			if (!gesture_func && !g_debug_enable_lcd_sleep_in) {	//lcd panel shutdown
				HISI_FB_INFO("display off(regulator disabling).\n");
				// bl_en,vsn,vsp disable
				gpio_cmds_tx(lcd_gpio_lowpower_cmd1, \
					ARRAY_SIZE(lcd_gpio_lowpower_cmd1));

				// lcd vci disable
				vcc_cmds_tx(pdev, lcd_vci_disable_cmds, \
					ARRAY_SIZE(lcd_vci_disable_cmds));

				// lcd reset set to L
				gpio_cmds_tx(lcd_gpio_lowpower_cmd2, \
					ARRAY_SIZE(lcd_gpio_lowpower_cmd2));

				// lcd vddio disable
				vcc_cmds_tx(pdev, lcd_vddio_disable_cmds, \
					ARRAY_SIZE(lcd_vddio_disable_cmds));

				// lcd gpio free
				gpio_cmds_tx(lcd_gpio_free_cmds, \
					ARRAY_SIZE(lcd_gpio_free_cmds));

				// lcd pinctrl lowpower
				pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
					ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));
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
		}else {
#ifdef CONFIG_HUAWEI_TS
			ts_thread_stop_notify();					//tp shutdown
#endif
			HISI_FB_INFO("display shutting down(regulator disabling).\n");				//lcd panel shutdown
			// bl_en,vsn,vsp disable
			gpio_cmds_tx(lcd_gpio_lowpower_cmd1, \
				ARRAY_SIZE(lcd_gpio_lowpower_cmd1));

			// lcd vci disable
			vcc_cmds_tx(pdev, lcd_vci_disable_cmds, \
				ARRAY_SIZE(lcd_vci_disable_cmds));

			// lcd reset set to L
			gpio_cmds_tx(lcd_gpio_lowpower_cmd2, \
				ARRAY_SIZE(lcd_gpio_lowpower_cmd2));

			// lcd vddio disable
			vcc_cmds_tx(pdev, lcd_vddio_disable_cmds, \
				ARRAY_SIZE(lcd_vddio_disable_cmds));

			// lcd gpio free
			gpio_cmds_tx(lcd_gpio_free_cmds, \
				ARRAY_SIZE(lcd_gpio_free_cmds));

			// lcd pinctrl lowpower
			pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
				ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));
		}

		checksum_enable_ctl = false;
	} else {
		HISI_FB_ERR("failed to uninit lcd!\n");
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_sharp_panel_remove(struct platform_device *pdev)
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

static int mipi_sharp_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
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

	if (new_lcd_supported) {
		if (0x05 == panel_lcd_id) {
			if (255 == hisifd->panel_info.bl_max) {
				if(bl_level > 207) {
					HISI_FB_INFO("bl_level over 207, set to 207\n");
					bl_level = 207;
				}
			} else {
				if (bl_level > 8085) {
					HISI_FB_INFO("bl_level over 8085, set to 8085\n");
					bl_level = 8085;
				}
			}
		} else {
			if (255 == hisifd->panel_info.bl_max) {
				if (bl_level > 198) {
					HISI_FB_INFO("bl_level over 198, set to 198\n");
					bl_level = 198;
				}
			} else {
				if (bl_level > 7680) {
					HISI_FB_INFO("bl_level over 7680, set to 7680\n");
					bl_level = 7680;
				}
			}
		}
	}

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

		bl_level_adjust[1] = bl_level  * 255 / hisifd->panel_info.bl_max;
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
static ssize_t mipi_sharp_panel_lcd_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "sharp_NT35695 5.2' CMD TFT 1080 x 1920\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_cabc_mode_show(struct platform_device *pdev,
	char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", g_cabc_mode);
}

static ssize_t mipi_sharp_panel_lcd_cabc_mode_store(struct platform_device *pdev,
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
              mipi_dsi_cmds_tx(sharp_cabc_off_cmds, \
                               ARRAY_SIZE(sharp_cabc_off_cmds),\
                               mipi_dsi0_base);
	}else  if (flag==CABC_UI_MODE) {
              g_cabc_mode=1;
              mipi_dsi_cmds_tx(sharp_cabc_ui_on_cmds, \
                               ARRAY_SIZE(sharp_cabc_ui_on_cmds),\
                               mipi_dsi0_base);
	} else if (flag==CABC_STILL_MODE ){
              g_cabc_mode=2;
              mipi_dsi_cmds_tx(sharp_cabc_still_on_cmds, \
                               ARRAY_SIZE(sharp_cabc_still_on_cmds),\
                               mipi_dsi0_base);
	}else if (flag==CABC_MOVING_MODE ){
              g_cabc_mode=3;
              mipi_dsi_cmds_tx(sharp_cabc_moving_on_cmds, \
                               ARRAY_SIZE(sharp_cabc_moving_on_cmds),\
                               mipi_dsi0_base);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, count, "%d\n", g_cabc_mode);
}

static ssize_t mipi_sharp_panel_lcd_check_reg_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[5] = {0};
	uint32_t expected_value[5] = {0x9c, 0x00, 0x77, 0x00, 0x00};
	uint32_t read_mask[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
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

static ssize_t mipi_sharp_panel_lcd_mipi_detect_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[3] = {0};
	uint32_t expected_value[3] = {0x80, 0x00, 0x00};
	uint32_t read_mask[3] = {0xFF, 0xFF, 0xFFFF};
	char* reg_name[3] = {"signal mode", "dsi error number", "MIPI error report"};
	char lcd_reg_0e[] = {0x0e};
	char lcd_reg_05[] = {0x05};
	char lcd_reg_ab[] = {0xab};

	struct dsi_cmd_desc set_read_size[] = {
		{DTYPE_MAX_PKTSIZE, 0, 10, WAIT_TYPE_US,
			0x2, NULL},
	};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0e), lcd_reg_0e},
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_05), lcd_reg_05},
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

	mipi_dsi_max_return_packet_size(set_read_size, mipi_dsi0_base);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (!mipi_dsi_read_compare(&data, mipi_dsi0_base)) {
		ret = snprintf(buf, PAGE_SIZE, "OK\n");
	} else {
		ret = snprintf(buf, PAGE_SIZE, "ERROR\n");
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_hkadc_debug_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = snprintf(buf, PAGE_SIZE, "%d\n", hkadc_buf*4);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_hkadc_debug_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	int channel = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = sscanf(buf, "%u", &channel);
	if(ret <= 0) {
		HISI_FB_ERR("Sscanf return invalid, ret = %d\n", ret);
		return count;
	}

	hkadc_buf = hisi_adc_get_value(channel);
	HISI_FB_INFO("channel[%d] value is %d\n", channel, hkadc_buf);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t mipi_sharp_panel_lcd_gram_check_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t rd[CHECKSUM_SIZE] = {0};
	int i = 0;
	char cmdF_page0_select[] = {0xFF, 0xF0};
	char cmd1_page0_select[] = {0xFF, 0x10};
	char checksum_read[] = {0x73};
	int checksum_result = 1; //0:success; 1:fail

	struct dsi_cmd_desc packet_size_set_cmd = {DTYPE_MAX_PKTSIZE, 0, 10, WAIT_TYPE_US, 1, NULL};

	struct dsi_cmd_desc lcd_checksum_select_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select},
	};

	struct dsi_cmd_desc lcd_checksum_dis_select_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
	};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 20, WAIT_TYPE_US,
			sizeof(checksum_read), checksum_read},
	};

	if (!checksum_enable_ctl) {
		HISI_FB_INFO("Checksum disabled\n");
		return ret;
	}

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	mipi_dsi_max_return_packet_size(&packet_size_set_cmd, mipi_dsi0_base);

	mipi_dsi_cmds_tx(lcd_checksum_select_cmds, \
		ARRAY_SIZE(lcd_checksum_select_cmds), mipi_dsi0_base);
	for (i = 0; i < CHECKSUM_SIZE; i++) {
		char *data = lcd_check_reg[0].payload;
		*data = 0x73 + i;
		mipi_dsi_cmds_rx((rd + i), lcd_check_reg, \
			ARRAY_SIZE(lcd_check_reg), mipi_dsi0_base);
		if (rd[i] != expected_checksum[checksum_pic_n][i]) {
			HISI_FB_ERR("rd[%d] = 0x%x, pic_num=%d, expected = 0x%x\n", i, rd[i], checksum_pic_n,
				expected_checksum[checksum_pic_n][i]);
			checksum_result = 1;
			break;
		}
		checksum_result = 0;
	}

	ret = snprintf(buf, PAGE_SIZE, "%d\n", checksum_result);

	HISI_FB_INFO("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x, pic_num=%d\n", \
			rd[0], rd[1], rd[2], rd[3], rd[4], rd[5], rd[6], rd[7], checksum_pic_n);

	mipi_dsi_cmds_tx(lcd_checksum_dis_select_cmds, \
		ARRAY_SIZE(lcd_checksum_dis_select_cmds), mipi_dsi0_base);

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_gram_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = -1;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *lcp_base = NULL;
	char __iomem *gamma_base = NULL;
	char cmdF_page0_select[] = {0xFF, 0xF0};
	char checksum_init[] = {0x7B, 0x00};
	char checksum_ena[] = {0x92, 0x01};
	char checksum_dis[] = {0x92, 0x00};
	char cmd1_page0_select[] = {0xFF, 0x10};
	unsigned long val = 0;

	struct dsi_cmd_desc lcd_checksum_enable_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_init), checksum_init},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_ena), checksum_ena},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
	};

	struct dsi_cmd_desc lcd_checksum_disable_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_dis), checksum_dis},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;
	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
	gamma_base = hisifd->dss_base + DSS_DPP_GAMMA_OFFSET;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		return ret;
	}
	HISI_FB_INFO("val=%d\n", val);
	if(1 == val) {
		if(checksum_enable_ctl == true) {
			HISI_FB_INFO("checksum_enable_ctl is alredy enable\n");
			return 0;
		}
		checksum_enable_ctl = true;
	} else if(0 == val){
		if(checksum_enable_ctl == false) {
			HISI_FB_INFO("checksum_enable_ctl is alredy disable\n");
			return 0;
		}
		checksum_enable_ctl = false;
	} else if(val > 0 && val < 6){
		checksum_pic_n = val - 2;
		HISI_FB_INFO("checksum_pic_n is %d\n",checksum_pic_n);
		return 0;
	} else {
		HISI_FB_INFO("val is invaild\n");
	}

	if(checksum_enable_ctl == true) {
		mipi_dsi_cmds_tx(lcd_checksum_enable_cmds, \
			ARRAY_SIZE(lcd_checksum_enable_cmds), mipi_dsi0_base);
		HISI_FB_INFO("Enable checksum\n");

		if (pinfo->gamma_support == 1)
			set_reg(gamma_base + GAMA_BYPASS_EN, 0x1, 1, 0);	//disable gamma
		if (pinfo->gmp_support == 1)
			set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x1, 1, 0);	//disable gmp
		if (pinfo->xcc_support == 1)
			set_reg(lcp_base + LCP_XCC_BYPASS_EN, 0x1, 1, 0);	//disable xcc
	} else {
		mipi_dsi_cmds_tx(lcd_checksum_disable_cmds, \
			ARRAY_SIZE(lcd_checksum_disable_cmds), mipi_dsi0_base);
		HISI_FB_INFO("Disable checksum\n");

		if (pinfo->gamma_support == 1)
			set_reg(gamma_base + GAMA_BYPASS_EN, 0x0, 1, 0);	//enable gamma
		if (pinfo->gmp_support == 1)
			set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x0, 1, 0);	//enable gmp
		if (pinfo->xcc_support == 1)
			set_reg(lcp_base + LCP_XCC_BYPASS_EN, 0x0, 1, 0);	//enable xcc
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t mipi_sharp_panel_lcd_dynamic_sram_checksum_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t rd[CHECKSUM_SIZE] = {0};
	int i = 0;
	char cmdf_page0_select[] = {0xFF, 0xF0};
	char cmd1_page0_select[] = {0xFF, 0x10};
	char checksum_read[] = {0x73};
	int checksum_result = 1;  //1:success; 0:fail

	struct dsi_cmd_desc packet_size_set_cmd = {DTYPE_MAX_PKTSIZE, 0, 10, WAIT_TYPE_US, 1, NULL};

	struct dsi_cmd_desc lcd_checksum_select_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdf_page0_select), cmdf_page0_select},
	};

	struct dsi_cmd_desc lcd_checksum_dis_select_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
	};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 20, WAIT_TYPE_US,
			sizeof(checksum_read), checksum_read},
	};

	if (!checksum_enable_ctl) {
		HISI_FB_INFO("Checksum disabled\n");
		return ret;
	}

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	mipi_dsi_max_return_packet_size(&packet_size_set_cmd, mipi_dsi0_base);

	mipi_dsi_cmds_tx(lcd_checksum_select_cmds, \
		ARRAY_SIZE(lcd_checksum_select_cmds), mipi_dsi0_base);
	for (i = 0; i < CHECKSUM_SIZE; i++) {
		char *data = lcd_check_reg[0].payload;
		*data = 0x73 + i;
		mipi_dsi_cmds_rx((rd + i), lcd_check_reg, \
			ARRAY_SIZE(lcd_check_reg), mipi_dsi0_base);
		if (rd[i] != expected_checksum_crc[checksum_pic_num][i]) {
			HISI_FB_ERR("rd[%d] = 0x%x, pic_num=%d, expected = 0x%x\n", i, rd[i], checksum_pic_num,
				expected_checksum_crc[checksum_pic_num][i]);
			checksum_result = 0;
			break;
		}
	}

	ret = snprintf(buf, PAGE_SIZE, "%d\n", checksum_result);

	HISI_FB_DEBUG("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x, pic_num=%d\n", \
			rd[0], rd[1], rd[2], rd[3], rd[4], rd[5], rd[6], rd[7], checksum_pic_num);

	mipi_dsi_cmds_tx(lcd_checksum_dis_select_cmds, \
		ARRAY_SIZE(lcd_checksum_dis_select_cmds), mipi_dsi0_base);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_dynamic_sram_checksum_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *lcp_base = NULL;
	char __iomem *gamma_base = NULL;
	char checksum_pic;
	char cmdf_page0_select[] = {0xFF, 0xF0};
	char checksum_sel[] = {0x7B, 0x00};
	char checksum_ena[] = {0x92, 0x01};
	char checksum_dis[] = {0x92, 0x00};
	char cmd1_page0_select[] = {0xFF, 0x10};
	char reload_cmd1[] = {0xFB, 0x01};

	struct dsi_cmd_desc lcd_checksum_enable_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdf_page0_select), cmdf_page0_select},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_sel), checksum_sel},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_ena), checksum_ena},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
	};

	struct dsi_cmd_desc lcd_checksum_disable_cmds[] = {
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select},
		{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(reload_cmd1), reload_cmd1},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;
	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
	gamma_base = hisifd->dss_base + DSS_DPP_GAMMA_OFFSET;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if ((!*buf) ||(!strchr("yY1nN0", *buf))) {
		HISI_FB_ERR("Input param is error(valid: yY1nN0): %s. \n",buf);
		return -EINVAL;
	}

	checksum_pic_num = (int)(buf[1] - '0');
	checksum_enable_ctl = !!strchr("yY1", *buf);
	if (checksum_enable_ctl == true) {
		if (0 <= checksum_pic_num && checksum_pic_num < CHECKSUM_PIC_NUM) {
			mipi_dsi_cmds_tx(lcd_checksum_enable_cmds, \
				ARRAY_SIZE(lcd_checksum_enable_cmds), mipi_dsi0_base);
		} else {
			HISI_FB_ERR("Input param is invalid: %s, pic_num=%d. \n", buf, checksum_pic_num);
			return -EINVAL;
		}
		HISI_FB_DEBUG("Enable checksum\n");
	} else {
		mipi_dsi_cmds_tx(lcd_checksum_disable_cmds, \
			ARRAY_SIZE(lcd_checksum_disable_cmds), mipi_dsi0_base);
		HISI_FB_DEBUG("Disable checksum\n");
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static int bist_read_and_check(struct platform_device *pdev, int step)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	u32 D8_value = 0xFF, D9_value = 0xFF, BC_value = 0xFF;
	int ret = LCD_BIST_CHECK_PASS;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	mipi_dsi0_base = hisifd->dss_base + DSS_MIPI_DSI0_OFFSET;

	outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0xD806);
	if (!mipi_dsi_read(&D8_value, mipi_dsi0_base)) {
		HISI_FB_ERR("LCD bist check read register D8 timeout\n");
		ret = LCD_BIST_CHECK_TIMEOUT;
		goto read_reg_failed;
	}

	outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0xD906);
	if (!mipi_dsi_read(&D9_value, mipi_dsi0_base)) {
		HISI_FB_ERR("LCD bist check read register D9 timeout\n");
		ret = LCD_BIST_CHECK_TIMEOUT;
		goto read_reg_failed;
	}

	outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0xBC06);
	if (!mipi_dsi_read(&BC_value, mipi_dsi0_base)) {
		HISI_FB_ERR("LCD bist check read register BC timeout\n");
		ret = LCD_BIST_CHECK_TIMEOUT;
		goto read_reg_failed;
	}

	HISI_FB_INFO("D8:%x, D9:%x, BC:%x\n", D8_value, D9_value, BC_value);

	if (step <= 7) {
		D8_value &= 0xFF;
		D9_value &= 0xFF;
		BC_value &= 0x60;
		ret = ((D8_value == 0x3F) && (D9_value == 0x00) && (BC_value == 0x60)) ? \
					LCD_BIST_CHECK_PASS : LCD_BIST_CHECK_FAIL;
	}

	if (step == 8) {
		BC_value &= 0x60;
		ret = (BC_value == 0x60) ? \
					LCD_BIST_CHECK_PASS : LCD_BIST_CHECK_FAIL;
	}

read_reg_failed:
	return ret;
}

static ssize_t mipi_sharp_panel_lcd_bist_check_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int ret = LCD_BIST_CHECK_PASS;
	int final_ret = LCD_BIST_CHECK_PASS;
	int i, j;
	int error;
	struct dss_rect disp_rect = {0};
	int sent_pixels = 0;
	int remain_pixels = 0;
	char lcd_pattern_packet[PACKET_SIZE] = {0};

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
	remain_pixels = pinfo->xres * pinfo->yres;
	disp_rect.w = pinfo->xres;
	disp_rect.h = pinfo->yres;
#ifdef CONFIG_HUAWEI_TS
	error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Disable touchscreen during test.\n");
#endif

	// lcd display off sequence
	mipi_dsi_cmds_tx(lcd_display_off_cmds, \
		ARRAY_SIZE(lcd_display_off_cmds), mipi_dsi0_base);

	j = 0;
	for (i = j; i<ARRAY_SIZE(sharp_display_bist_check_cmds); i++) {
		HISI_FB_INFO("TEST %d\n", i+1);
		mipi_dsi_cmds_tx(sharp_display_bist_check_cmds[i], \
			bist_check_cmds_size[i], mipi_dsi0_base);
		ret = bist_read_and_check(pdev, i + 1);
		if (ret != LCD_BIST_CHECK_PASS) {
			HISI_FB_ERR("check failed\n");
			final_ret = ret;
		}
	}

	if (final_ret == LCD_BIST_CHECK_PASS)
		ret = snprintf(buf, PAGE_SIZE, "pass\n");
	else
		ret = snprintf(buf, PAGE_SIZE, "fail\n");

	mipi_dsi_cmds_tx(sharp_display_bist_check_end, \
		ARRAY_SIZE(sharp_display_bist_check_end), mipi_dsi0_base);

	// lcd gpio bl disable
	gpio_cmds_tx(lcd_gpio_bl_disable_cmds, \
		ARRAY_SIZE(lcd_gpio_bl_disable_cmds));

	// lcd display on sequence
	mipi_dsi_cmds_tx(lcd_display_on_cmds, \
		ARRAY_SIZE(lcd_display_on_cmds), mipi_dsi0_base);

	mipi_sharp_panel_set_display_region(pdev, &disp_rect);
	memset(lcd_pattern_packet, 0, PACKET_SIZE);
	while (remain_pixels > 0) {
		lcd_pattern_packet[0] = (sent_pixels == 0) ? 0x2c : 0x3c;

		mipi_dsi_cmds_tx(lcd_write_pattern, \
			ARRAY_SIZE(lcd_write_pattern), mipi_dsi0_base);

		remain_pixels -= PACKET_PIXELS_SIZE;
		sent_pixels += PACKET_PIXELS_SIZE;
	}

	// lcd gpio bl enable
	gpio_cmds_tx(lcd_gpio_bl_enable_cmds, \
		ARRAY_SIZE(lcd_gpio_bl_enable_cmds));

#ifdef CONFIG_HUAWEI_TS
	if (!error)
		error = ts_power_control_notify(TS_AFTER_RESUME, SHORT_SYNC_TIMEOUT);
	HISI_FB_INFO("Enable touchscreen after test.\n");
#endif
	hisifd->lcd_self_testing = false;

	return ret;
}

static ssize_t mipi_sharp_panel_lcd_sleep_ctrl_show(struct platform_device *pdev, char *buf)
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

/*for LCD powerdown or not*/
static ssize_t mipi_sharp_panel_lcd_sleep_ctrl_store(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	unsigned long val = 0;

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	g_debug_enable_lcd_sleep_in = val;

	/*if g_debug_enable_lcd_sleep_in==1, it means don't turn off TP/LCD power,but lcd sleep, tp work.
	 **if g_debug_enable_lcd_sleep_in==2, it means don't turn off TP/LCD power,but tp sleep, lcd work.
	*/
	if (g_debug_enable_lcd_sleep_in == 2) {
		HISI_FB_INFO("LCD power off and Touch goto sleep\n");
		g_tp_power_ctrl = 1;	//g_tp_power_ctrl =1: TP sleep. in for lcd current test
	} else {
		HISI_FB_INFO("g_debug_enable_lcd_sleep_in is %d\n", g_debug_enable_lcd_sleep_in);
		g_tp_power_ctrl = 0;
	}

	return ret;
}

/*for esd check*/
static int mipi_sharp_panel_check_esd(struct platform_device* pdev)
{
	int ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	uint32_t read_value[1] = {0};
	uint32_t expected_value[1] = {0x9c};
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

static int mipi_sharp_panel_set_display_region(struct platform_device *pdev,
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

#define LCD_CMD_NAME_MAX 100
static char lcd_cmd_now[LCD_CMD_NAME_MAX] = {0};
static ssize_t mipi_sharp_panel_lcd_test_config_show(struct platform_device *pdev,
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
	} else if (!strncmp(lcd_cmd_now, "CHECKSUM", strlen("CHECKSUM"))) { /* CHECKSUM */
		return snprintf(buf, PAGE_SIZE, "/sys/class/graphics/fb0/lcd_checksum");
	} else {
		return snprintf(buf, PAGE_SIZE, "INVALID");
	}
}

static ssize_t mipi_sharp_panel_lcd_test_config_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
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
static ssize_t mipi_sharp_panel_lcd_support_mode_show(struct platform_device *pdev,
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

static ssize_t mipi_sharp_panel_lcd_support_mode_store(struct platform_device *pdev,
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

static ssize_t mipi_sharp_panel_lcd_support_checkmode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "checksum:1;lp2hs_mipi_check:1\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_sharp_panel_lp2hs_mipi_check_show(struct platform_device *pdev,
	char *buf)
{
	if (g_lp2hs_mipi_test_result) {
		return snprintf(buf, PAGE_SIZE, "OK\n");
	} else {
		return snprintf(buf, PAGE_SIZE, "FAIL\n");
	}
}

#define LP2HS_MIPI_TEST_ON		1
#define LP2HS_MIPI_TEST_OFF	0
static ssize_t mipi_sharp_panel_lp2hs_mipi_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag = -1;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
		return ret;

	flag = (int)val;

	if (flag == LP2HS_MIPI_TEST_OFF) {
		g_lp2hs_mipi_test = false;
		g_lp2hs_mipi_test_result = false;
		hisifd->lcd_self_testing = false;
		HISI_FB_INFO("lp2hs_mipi test OFF\n");
	} else  if (flag == LP2HS_MIPI_TEST_ON) {
		g_lp2hs_mipi_test = true;
		hisifd->lcd_self_testing = true;
		HISI_FB_INFO("lp2hs_mipi test ON\n");
	}

	return count;
}

static ssize_t mipi_sharp_panel_sharpness2d_table_store(struct platform_device *pdev,
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
			HISI_FB_DEBUG("sharp2d_table[%d] = 0x%x \n", i, ((uint32_t*)(hisifd->panel_info.sharp2d_table))[i]);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t mipi_sharp_panel_sharpness2d_table_show(struct platform_device *pdev,	 char *buf)
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

static ssize_t mipi_sharp_panel_info_show(struct platform_device *pdev, char *buf)
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
		HISI_FB_INFO("VN1 and later, panel_info.bl_max is %d, panel_lcd_id is %d\n", hisifd->panel_info.bl_max, panel_lcd_id);
		if (0x05 == panel_lcd_id) {
			HISI_FB_INFO("1in1 function\n");
			if(255 == hisifd->panel_info.bl_max) {
				bl_max_val = 207;
			} else {
				bl_max_val = 8085;
			}
		} else {
			HISI_FB_INFO("2in1 function\n");
			if(255 == hisifd->panel_info.bl_max) {
				bl_max_val = 198;
			} else {
				bl_max_val = 7680;
			}
		}
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
				bl_max_val, bl_min_val, "LCD", bl_device_level);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_sharp_panel_set_fastboot,
	.on = mipi_sharp_panel_on,
	.off = mipi_sharp_panel_off,
	.remove = mipi_sharp_panel_remove,
	.set_backlight = mipi_sharp_panel_set_backlight,
	.lcd_model_show = mipi_sharp_panel_lcd_model_show,
	.lcd_cabc_mode_show = mipi_sharp_panel_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_sharp_panel_lcd_cabc_mode_store,
	.lcd_check_reg = mipi_sharp_panel_lcd_check_reg_show,
	.lcd_mipi_detect = mipi_sharp_panel_lcd_mipi_detect_show,
	.lcd_hkadc_debug_show = mipi_sharp_panel_lcd_hkadc_debug_show,
	.lcd_hkadc_debug_store = mipi_sharp_panel_lcd_hkadc_debug_store,
	.lcd_gram_check_show = mipi_sharp_panel_lcd_gram_check_show,
	.lcd_gram_check_store = mipi_sharp_panel_lcd_gram_check_store,
	.lcd_dynamic_sram_checksum_show = mipi_sharp_panel_lcd_dynamic_sram_checksum_show,
	.lcd_dynamic_sram_checksum_store = mipi_sharp_panel_lcd_dynamic_sram_checksum_store,
	.lcd_bist_check = mipi_sharp_panel_lcd_bist_check_show,
	.lcd_sleep_ctrl_show = mipi_sharp_panel_lcd_sleep_ctrl_show,
	.lcd_sleep_ctrl_store = mipi_sharp_panel_lcd_sleep_ctrl_store,
	.esd_handle = mipi_sharp_panel_check_esd,
	.set_display_region = mipi_sharp_panel_set_display_region,
	.lcd_test_config_show = mipi_sharp_panel_lcd_test_config_show,
	.lcd_test_config_store = mipi_sharp_panel_lcd_test_config_store,
	.lcd_support_mode_show = mipi_sharp_panel_lcd_support_mode_show,
	.lcd_support_mode_store = mipi_sharp_panel_lcd_support_mode_store,
	.lcd_support_checkmode_show = mipi_sharp_panel_lcd_support_checkmode_show,
	.lcd_lp2hs_mipi_check_show = mipi_sharp_panel_lp2hs_mipi_check_show,
	.lcd_lp2hs_mipi_check_store = mipi_sharp_panel_lp2hs_mipi_check_store,
	.set_display_resolution = NULL,
	.sharpness2d_table_store = mipi_sharp_panel_sharpness2d_table_store,
	.sharpness2d_table_show = mipi_sharp_panel_sharpness2d_table_show,
	.panel_info_show = mipi_sharp_panel_info_show,
};

/*******************************************************************************
**
*/
static int mipi_sharp_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;
	uint32_t lcd_ifbc_type = 0;

	panel_lcd_id = (int)simple_strtol(panel_lcd_id_buf, NULL, 0);
#ifdef CONFIG_HUAWEI_TS
	g_lcd_control_tp_power = true;	//not use fb_notify to control touch timing.
#endif
	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SHARP_NT35695_5P5);
	if (!np) {
		HISI_FB_ERR("not found device node %s!\n", DTS_COMP_SHARP_NT35695_5P5);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_CMD;
	}
	HISI_FB_INFO("lcd_display_type=%u!\n", lcd_display_type);

	ret = of_property_read_u32(np, LCD_IFBC_TYPE_NAME, &lcd_ifbc_type);
	if (ret) {
		HISI_FB_ERR("get ifbc_type failed!\n");
		lcd_ifbc_type = IFBC_TYPE_NONE;
	}
	HISI_FB_INFO("lcd_ifbc_type=%u!\n", lcd_ifbc_type);

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type))
		goto err_probe_defer;


	HISI_FB_INFO("%s, lcd id is 0x%x\n", DTS_COMP_SHARP_NT35695_5P5, panel_lcd_id);

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
	pinfo->bl_min = 117;
	pinfo->bl_max = 9960;
	pinfo->bl_default = 4000;
	pinfo->blpwm_precision_type = BLPWM_PRECISION_10000_TYPE;
#else
	pinfo->bl_min = 3;
	pinfo->bl_max = 255;
	pinfo->bl_default = 102;
#endif

	pinfo->type = lcd_display_type;
	pinfo->ifbc_type = IFBC_TYPE_NONE;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;
	pinfo->esd_skip_mipi_check = 0;
	pinfo->lcd_uninit_step_support = 1;

	pinfo->color_temperature_support = 1;
	pinfo->comform_mode_support = 1;
	pinfo->panel_effect_support = 1;
	g_support_mode = COMFORM_MODE | LED_RG_COLOR_TEMP_MODE | GAMMA_MAP;
	g_led_rg_para1 = 7;
	g_led_rg_para2 = 30983;

	if(color_temp_cal_buf[0] == 1){
		pinfo->color_temp_rectify_support = 0;
	}else{
		HISI_FB_INFO("need to rectify RGB!\n");
		pinfo->color_temp_rectify_support = 1;
	}
	pinfo->color_temp_rectify_R = 31980; /*0.976-0.989*/
	pinfo->color_temp_rectify_G = 32768; /*1*/
	pinfo->color_temp_rectify_B = 31625; /*0.965-0.984*/

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
	pinfo->ldi.h_back_porch = 23;//50;
	pinfo->ldi.h_front_porch = 50;//132;
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

	//non_continue adjust : measured in UI
	//sharp requires clk_post >= 60ns + 252ui, so need a clk_post_adjust more than 200ui. Here 215 is used.
	pinfo->mipi.clk_post_adjust = 215;
	pinfo->mipi.clk_pre_adjust= 0;
	pinfo->mipi.clk_t_hs_prepare_adjust= 0;
	pinfo->mipi.clk_t_lpx_adjust= 0;
	pinfo->mipi.clk_t_hs_trial_adjust= 0;
	pinfo->mipi.clk_t_hs_exit_adjust= 0;
	pinfo->mipi.clk_t_hs_zero_adjust= 0;
	pinfo->mipi.non_continue_en = 1;

	pinfo->pxl_clk_rate = 144 * 1000000UL;

	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.lane_nums_select_support = DSI_1_LANES_SUPPORT | DSI_2_LANES_SUPPORT |
		DSI_3_LANES_SUPPORT | DSI_4_LANES_SUPPORT;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->pxl_clk_rate_div = 1;

	pinfo->vsync_ctrl_type = VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
	pinfo->dirty_region_updt_support = 1;
	pinfo->dirty_region_info.left_align = -1;
	pinfo->dirty_region_info.right_align = -1;
	pinfo->dirty_region_info.top_align = 32;
	pinfo->dirty_region_info.bottom_align = 32;
	pinfo->dirty_region_info.w_align = -1;
	pinfo->dirty_region_info.h_align = -1;
	pinfo->dirty_region_info.w_min = 1080;
	pinfo->dirty_region_info.h_min = -1;
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
		pinfo->ifbc_type = IFBC_TYPE_NONE;
		pinfo->blpwm_input_ena = 0;
		pinfo->blpwm_precision_type = BLPWM_PRECISION_DEFAULT_TYPE;
		pinfo->bl_min = 3;
		pinfo->bl_max = 255;
		pinfo->comform_mode_support = 0;
		pinfo->panel_effect_support = 0;
		pinfo->color_temp_rectify_support = 0;
		g_support_mode = 0;
		pinfo->color_temp_rectify_R = 32408; /*0.989*/
		pinfo->color_temp_rectify_B = 32244; /*0.984*/
		pinfo->gamma_lut_table_R = gamma_lut_table_R_default;
		pinfo->gamma_lut_table_G = gamma_lut_table_G_default;
		pinfo->gamma_lut_table_B = gamma_lut_table_B_default;
		pinfo->igm_lut_table_R = igm_lut_table_R_default;
		pinfo->igm_lut_table_G = igm_lut_table_G_default;
		pinfo->igm_lut_table_B = igm_lut_table_B_default;
		pinfo->gmp_lut_table_low32bit = &gmp_lut_table_low32bit_default[0][0][0];
	}

	if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_SINGLE) {
		pinfo->pxl_clk_rate_div = 3;

		//ldi
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;

		//dsc parameter info
		pinfo->vesa_dsc.bits_per_component = 8;
		pinfo->vesa_dsc.bits_per_pixel = 8;
		pinfo->vesa_dsc.slice_width = 1079;
		pinfo->vesa_dsc.slice_height = 15;

		pinfo->vesa_dsc.initial_xmit_delay = 512;
		pinfo->vesa_dsc.first_line_bpg_offset = 12;
		pinfo->vesa_dsc.mux_word_size = 48;

		// DSC_CTRL
		pinfo->vesa_dsc.block_pred_enable = 1;
		pinfo->vesa_dsc.linebuf_depth = 9;

		//RC_PARAM3
		pinfo->vesa_dsc.initial_offset = 6144;

		//FLATNESS_QP_TH
		pinfo->vesa_dsc.flatness_min_qp = 3;
		pinfo->vesa_dsc.flatness_max_qp = 12;

		//DSC_PARAM4
		pinfo->vesa_dsc.rc_edge_factor= 0x6;
		pinfo->vesa_dsc.rc_model_size = 8192;

		//DSC_RC_PARAM5: 0x330b0b
		pinfo->vesa_dsc.rc_tgt_offset_lo = (0x330b0b >> 20) & 0xF;
		pinfo->vesa_dsc.rc_tgt_offset_hi = (0x330b0b >> 16) & 0xF;
		pinfo->vesa_dsc.rc_quant_incr_limit1 = (0x330b0b >> 8) & 0x1F;
		pinfo->vesa_dsc.rc_quant_incr_limit0 = (0x330b0b >> 0) & 0x1F;

		//DSC_RC_BUF_THRESH0: 0xe1c2a38
		pinfo->vesa_dsc.rc_buf_thresh0 = (0xe1c2a38 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh1 = (0xe1c2a38 >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh2 = (0xe1c2a38 >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh3 = (0xe1c2a38 >> 0) & 0xFF;

		//DSC_RC_BUF_THRESH1: 0x46546269
		pinfo->vesa_dsc.rc_buf_thresh4 = (0x46546269 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh5 = (0x46546269 >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh6 = (0x46546269 >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh7 = (0x46546269 >> 0) & 0xFF;

		//DSC_RC_BUF_THRESH2: 0x7077797b
		pinfo->vesa_dsc.rc_buf_thresh8 = (0x7077797b >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh9 = (0x7077797b >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh10 = (0x7077797b >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh11 = (0x7077797b >> 0) & 0xFF;

		//DSC_RC_BUF_THRESH3: 0x7d7e0000
		pinfo->vesa_dsc.rc_buf_thresh12 = (0x7d7e0000 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh13 = (0x7d7e0000 >> 16) & 0xFF;

		//DSC_RC_RANGE_PARAM0: 0x1020100
		pinfo->vesa_dsc.range_min_qp0 = (0x1020100 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp0 = (0x1020100 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset0 = (0x1020100 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp1 = (0x1020100 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp1 = (0x1020100 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset1 = (0x1020100 >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM1: 0x94009be,
		pinfo->vesa_dsc.range_min_qp2 = (0x94009be >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp2 = (0x94009be >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset2 = (0x94009be >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp3 = (0x94009be >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp3 = (0x94009be >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset3 = (0x94009be >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM2, 0x19fc19fa,
		pinfo->vesa_dsc.range_min_qp4 = (0x19fc19fa >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp4 = (0x19fc19fa >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset4 = (0x19fc19fa >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp5 = (0x19fc19fa >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp5 = (0x19fc19fa >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset5 = (0x19fc19fa >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM3, 0x19f81a38,
		pinfo->vesa_dsc.range_min_qp6 = (0x19f81a38 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp6 = (0x19f81a38 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset6 = (0x19f81a38 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp7 = (0x19f81a38 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp7 = (0x19f81a38 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset7 = (0x19f81a38 >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM4, 0x1a781ab6,
		pinfo->vesa_dsc.range_min_qp8 = (0x1a781ab6 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp8 = (0x1a781ab6 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset8 = (0x1a781ab6 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp9 = (0x1a781ab6 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp9 = (0x1a781ab6 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset9 = (0x1a781ab6 >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM5, 0x2af62b34,
		pinfo->vesa_dsc.range_min_qp10 = (0x2af62b34 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp10 = (0x2af62b34 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset10 = (0x2af62b34 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp11 = (0x2af62b34 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp11 = (0x2af62b34 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset11 = (0x2af62b34 >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM6, 0x2b743b74,
		pinfo->vesa_dsc.range_min_qp12 = (0x2b743b74 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp12 = (0x2b743b74 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset12 = (0x2b743b74 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp13 = (0x2b743b74 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp13 = (0x2b743b74 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset13 = (0x2b743b74 >> 0) & 0x3F;

		//DSC_RC_RANGE_PARAM7, 0x6bf40000,
		pinfo->vesa_dsc.range_min_qp14 = (0x6bf40000 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp14 = (0x6bf40000 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset14 = (0x6bf40000 >> 16) & 0x3F;
	};

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
		.compatible = DTS_COMP_SHARP_NT35695_5P5,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_sharp_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_sharp_NT35695_5P5",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_sharp_panel_init(void)
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

module_init(mipi_sharp_panel_init);
