/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"
#include <huawei_platform/log/log_jank.h>
#include <linux/hisi/hw_cmdline_parse.h>

#define DTS_COMP_SAMSUNG_S6E3HA3X01 "hisilicon,mipi_samsung_S6E3HA3X01"
#define AMOLED_CHECK_INT

static struct hisi_fb_panel_data samsung_s6e3fa3x01_panel_data;
static bool g_debug_enable = false;

#define LCD_POWER_STATUS_CHECK  (0)


/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode) begin
*/

static char test_key_enable[] = {
	0xF0,
	0x5A,0x5A,
};

static char dual_dsi[] = {
	0xF2,
	0x03,0x40,
};

static char mic_control[] = {
	0xF9,
	0x0A,
};

static char psr_off[] = {
	0xB9,
	0x00,
};

static char test_key_disable[] = {
	0xF0,
	0xA5,0xA5,
};

//TE
static char tear_on[] = {
	0x35,
	0x00,
};
//PenPen Tile Setting
static char pentile_setting[] = {
	0xC0,
	0x00,0x0f,0xD8,0xD8,
};

static char test_key_enable_0xfc[] = {
	0xFC,
	0x5A,0x5A,
};

static char global_para[] = {
	0xB0,
	0x20,
};
static char poc_setting[] = {
	0xFE,
	0x08,
};
static char setup_margin[] = {
	0xFF,
	0x00,0x00,0x00,0x08,
};
static char test_key_disable_0xfc[] = {
	0xFC,
	0xA5,0xA5,
};

//brightness setting
static char gamma_2_2[] = {
	0xCA,
	0x01,0x00,0x01,0x00,0x01,0x00,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x80,0x80,0x80,
	0x00,0x00,0x00,
};
static char aid_setting[] = {
	0xB2,
	0x00,0x0A,
};
static char aid_update[] = {
	0xF7,
	0x00,0x03,
};

static char opr_overage[] = {
	0xB5,
	0x41,
};

static char acl_setting[] = {
	0x55,
	0x00,
};

static char bl_enable[] = {
	0x53,
	0x28,
};

static char Delay_TE[] = {
	0x44,
	0x07, 0x80,
};

static char scan_dir[] = {
	0x36,
	0xC0,
};
static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};
/*******************************************************************************
** Power OFF Sequence(Normal to power off) begin
*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static struct dsi_cmd_desc display_on_cmds[] = {
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable), test_key_enable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(dual_dsi), dual_dsi},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(mic_control), mic_control},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(psr_off), psr_off},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable), test_key_disable},
	//exit sleep
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},
	//interface setting
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable), test_key_enable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(dual_dsi), dual_dsi},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(mic_control), mic_control},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(psr_off), psr_off},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable), test_key_disable},
	//common setting
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(tear_on), tear_on},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable), test_key_enable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(pentile_setting), pentile_setting},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable), test_key_disable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable), test_key_enable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable_0xfc), test_key_enable_0xfc},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(global_para), global_para},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(poc_setting), poc_setting},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(setup_margin), setup_margin},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable), test_key_disable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable_0xfc), test_key_disable_0xfc},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_enable), test_key_enable},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(gamma_2_2), gamma_2_2},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(aid_setting), aid_setting},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(aid_update), aid_update},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(opr_overage), opr_overage},
	{DTYPE_DCS_WRITE1, 0,10, WAIT_TYPE_US,
		sizeof(acl_setting), acl_setting},
	{DTYPE_GEN_LWRITE, 0,10, WAIT_TYPE_US,
		sizeof(test_key_disable), test_key_disable},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	//{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
	//	sizeof(Delay_TE), Delay_TE},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
};

static struct dsi_cmd_desc display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 50, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
};

/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME		"lcdio-vcc"
#define VCC_LCDANALOG_NAME	"lcdanalog-vcc"

static struct regulator *vcc_io;
static struct regulator *vcc_analog;

static struct vcc_desc samsung_s6e3ha3x01_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_io, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_analog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_analog, 3300000, 3300000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc samsung_s6e3ha3x01_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_io, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_analog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc samsung_s6e3ha3x01_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_analog, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_io, 0, 0, WAIT_TYPE_MS, 10},
};

static struct vcc_desc samsung_s6e3ha3x01_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_io, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_analog, 0, 0, WAIT_TYPE_MS, 3},
};


/*******************************************************************************
** LCD IOMUX
*/
static struct pinctrl_data pctrl;

static struct pinctrl_cmd_desc samsung_s6e3ha3x01_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc samsung_s6e3ha3x01_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc samsung_s6e3ha3x01_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc samsung_s6e3ha3x01_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pctrl, 0},
};


/*******************************************************************************
** LCD GPIO
*/
#define GPIO_RESET_NAME	"gpio_amoled_reset"
#define GPIO_ID_NAME	"gpio_amoled_id"
#define GPIO_VDDIO_ENABLE_NAME "gpio_amoled_vddio_enable"
#define GPIO_PCD_NAME  "gpio_amoled_pcd"
#define GPIO_ERR_FLAG  "gpio_amoled_err_flag"
#define GPIO_LCD_VDD3 "gpio_lcd_vdd3"
#define GPIO_LCD_VDDR "gpio_lcd_vddr"

static uint32_t gpio_reset;  /*gpio_053*/
static uint32_t gpio_id;  /*gpio_4_6, gpio_038*/
static uint32_t gpio_vddio_enable; /*gpio_15_4, gpio_124*/
static uint32_t gpio_pcd; /*UL:gpio_039;CL:codec_gpio_024*/
static uint32_t gpio_err_flag; /*gpio_5_1, gpio_041*/
static uint32_t gpio_lcd_vdd3;//GPIO_015
static uint32_t gpio_lcd_vddr;//GPIO_012

/***panel on**/
static struct gpio_desc samsung_s6e3ha3x01_gpio_request_cmds[] = {
	/*pcd*/
    //{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
    //	GPIO_PCD_NAME, &gpio_pcd, 0},
    ///*err flag*/
    //{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
    //	GPIO_ERR_FLAG, &gpio_err_flag, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RESET_NAME, &gpio_reset, 0},
	/* id */
    //{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
    //	GPIO_ID_NAME, &gpio_id, 0},
    ///*vddio_enable*/
    //{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
    //	GPIO_VDDIO_ENABLE_NAME, &gpio_vddio_enable, 0},
	//vddr
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDDR, &gpio_lcd_vddr, 0},
	//vdd3
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDD3, &gpio_lcd_vdd3, 0},
};

static struct gpio_desc samsung_s6e3ha3x01_gpio_normal_0_cmds[] = {
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_VDD3, &gpio_lcd_vdd3, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_VDDR, &gpio_lcd_vddr, 1},
};

static struct gpio_desc samsung_s6e3ha3x01_gpio_normal_cmds[] = {
	/*vddio enable*/
    //{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
    //	GPIO_VDDIO_ENABLE_NAME, &gpio_vddio_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_RESET_NAME, &gpio_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_RESET_NAME, &gpio_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_RESET_NAME, &gpio_reset, 1},
    ///* id */
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 1,
    //	GPIO_ID_NAME, &gpio_id, 0},
    ///*pcd*/
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 1,
    //	GPIO_PCD_NAME, &gpio_pcd, 0},
    ///*err flag*/
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 1,
    //	GPIO_ERR_FLAG, &gpio_err_flag, 0},
};

/***panel off***/
static struct gpio_desc samsung_s6e3ha3x01_gpio_lowpower_cmds[] = {
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDDR, &gpio_lcd_vddr, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDD3, &gpio_lcd_vdd3, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_RESET_NAME, &gpio_reset, 0},
	/*vddio disable*/
    //{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
    //	GPIO_VDDIO_ENABLE_NAME, &gpio_vddio_enable, 0},
    ///* reset input */
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
    //	GPIO_RESET_NAME, &gpio_reset, 0},
    ///*vddio_enable input*/
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
    //	GPIO_VDDIO_ENABLE_NAME, &gpio_vddio_enable, 0},
};

static struct gpio_desc samsung_s6e3ha3x01_gpio_free_cmds[] = {
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDDR, &gpio_lcd_vddr, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_VDD3, &gpio_lcd_vdd3, 0},
	
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RESET_NAME, &gpio_reset, 0},
    ///* id */
    //{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
    //	GPIO_ID_NAME, &gpio_id, 0},
    ///*pcd*/
    //{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
    //	GPIO_PCD_NAME, &gpio_pcd, 0},
    ///*err flag*/
    //{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
    //	GPIO_ERR_FLAG, &gpio_err_flag, 0},
    ///*vddio_enable*/
    //{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
    //	GPIO_VDDIO_ENABLE_NAME, &gpio_vddio_enable, 0},
};

#ifdef AMOLED_CHECK_INT
static irqreturn_t pcd_irq_isr_func(int irq, void *handle)
{
	if(gpio_get_value_cansleep(gpio_pcd) == 0)
		HISI_FB_INFO("pcd irq!\n");
	else
		HISI_FB_DEBUG("bad pcd irq!\n");

	return IRQ_HANDLED;
}

static irqreturn_t errflag_irq_isr_func(int irq, void *handle)
{
	if(gpio_get_value_cansleep(gpio_err_flag) == 1)
		HISI_FB_INFO("err_flag irq!\n");
	else
		HISI_FB_DEBUG("bad err_flag irq!\n");

	return IRQ_HANDLED;
}

static void amoled_irq_enable(void)
{
//	enable_irq(gpio_to_irq(gpio_pcd));
//	enable_irq(gpio_to_irq(gpio_err_flag));
}

static void amoled_irq_disable(void)
{
//	disable_irq(gpio_to_irq(gpio_pcd));
//	disable_irq(gpio_to_irq(gpio_err_flag));
}
#endif
/*******************************************************************************
**
*/
static int mipi_samsung_s6e3ha3x01_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	/* pinctrl normal */
	pinctrl_cmds_tx(pdev, samsung_s6e3ha3x01_pinctrl_normal_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_pinctrl_normal_cmds));

	/* gpio request */
	gpio_cmds_tx(samsung_s6e3ha3x01_gpio_request_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_gpio_request_cmds));

	/* backlight on */	
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_samsung_s6e3ha3x01_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;

#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_status_reg[] = {
		{0x0A, 0x9C, 0xFF, "lcd power state"},
	};
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
		/* vcc enable */
		vcc_cmds_tx(pdev, samsung_s6e3ha3x01_vcc_enable_cmds,
			ARRAY_SIZE(samsung_s6e3ha3x01_vcc_enable_cmds));
		
		/* pinctrl normal */
		pinctrl_cmds_tx(pdev, samsung_s6e3ha3x01_pinctrl_normal_cmds,
			ARRAY_SIZE(samsung_s6e3ha3x01_pinctrl_normal_cmds));
		/* gpio request */
		gpio_cmds_tx(samsung_s6e3ha3x01_gpio_request_cmds, \
			ARRAY_SIZE(samsung_s6e3ha3x01_gpio_request_cmds));

		gpio_cmds_tx(samsung_s6e3ha3x01_gpio_normal_0_cmds, \
			ARRAY_SIZE(samsung_s6e3ha3x01_gpio_normal_0_cmds)); //vdd3 vddr enable

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {

		mdelay(10);

		/* gpio normal */
		gpio_cmds_tx(samsung_s6e3ha3x01_gpio_normal_cmds, \
			ARRAY_SIZE(samsung_s6e3ha3x01_gpio_normal_cmds));

		mipi_dsi_cmds_tx(display_on_cmds, \
			ARRAY_SIZE(display_on_cmds), mipi_dsi0_base);

#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(lcd_status_reg, \
			ARRAY_SIZE(lcd_status_reg), mipi_dsi0_base);
#endif
		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		/* backlight on */
		hisi_lcd_backlight_on(pdev);
		g_debug_enable = true;
#ifdef AMOLED_CHECK_INT
		amoled_irq_enable();
#endif
	} else {
		HISI_FB_ERR("failed to init!\n");
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_samsung_s6e3ha3x01_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	LOG_JANK_D(JLID_KERNEL_LCD_POWER_OFF, "%s", "JL_KERNEL_LCD_POWER_OFF");

#ifdef AMOLED_CHECK_INT
	amoled_irq_disable();
#endif
	/* display off sequence */
	mipi_dsi_cmds_tx(display_off_cmds, \
		ARRAY_SIZE(display_off_cmds), hisifd->mipi_dsi0_base);

	/* gpio lowpower */
	gpio_cmds_tx(samsung_s6e3ha3x01_gpio_lowpower_cmds, \
		ARRAY_SIZE(samsung_s6e3ha3x01_gpio_lowpower_cmds));
	/* gpio free */
	gpio_cmds_tx(samsung_s6e3ha3x01_gpio_free_cmds, \
		ARRAY_SIZE(samsung_s6e3ha3x01_gpio_free_cmds));

	/* pinctrl lowpower */
	pinctrl_cmds_tx(pdev, samsung_s6e3ha3x01_pinctrl_lowpower_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_pinctrl_lowpower_cmds));
	/* vcc disable */
	vcc_cmds_tx(pdev, samsung_s6e3ha3x01_vcc_disable_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_vcc_disable_cmds));

	//if (hisifd->hisi_fb_shutdown) {
	//	ts_thread_stop_notify();
	//}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_samsung_s6e3ha3x01_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	/* vcc finit */
	vcc_cmds_tx(pdev, samsung_s6e3ha3x01_vcc_finit_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_vcc_finit_cmds));

	/* pinctrl finit */
	pinctrl_cmds_tx(pdev, samsung_s6e3ha3x01_pinctrl_finit_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_pinctrl_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_samsung_s6e3ha3x01_set_brightness(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	char payload[2] = {0, 0};
	struct dsi_cmd_desc bl_cmd[] = {
		{DTYPE_DCS_WRITE1, 0, 500, WAIT_TYPE_US,
			sizeof(payload), payload},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (unlikely(g_debug_enable)) {
		HISI_FB_INFO("Set brightness to %d\n", hisifd->bl_level);
		LOG_JANK_D(JLID_KERNEL_LCD_BACKLIGHT_ON, "JL_KERNEL_LCD_BACKLIGHT_ON,%u", hisifd->bl_level);
		g_debug_enable = false;
	}

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		//ret = hisi_pwm_set_backlight(hisifd);
		HISI_FB_INFO("set brightness by BL_SET_BY_PWM to %d \n", hisifd->bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		//ret = hisi_blpwm_set_backlight(hisifd);
		HISI_FB_INFO("set brightness by BL_SET_BY_BLPWM to %d \n", hisifd->bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		HISI_FB_INFO("set brightness by mipi to %d \n", hisifd->bl_level);
		bl_cmd[0].payload[0] = 0x51;
		bl_cmd[0].payload[1] = hisifd->bl_level;

		mipi_dsi_cmds_tx(bl_cmd, ARRAY_SIZE(bl_cmd), hisifd->mipi_dsi0_base);
	} else {
		HISI_FB_ERR("No such bl_set_type!\n");
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

/******************************************************************************/
static ssize_t mipi_samsung_s6e3ha3x01_model_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;

	ret = snprintf(buf, PAGE_SIZE, "samsung-s6e3ha3x01\n");
	return ret;
}

static ssize_t mipi_samsung_pcd_errflag_check(struct platform_device *pdev,
	char *buf)
{
	int pcd_gpio = 0;
	int errflag_gpio = 0;
	ssize_t ret = 0;
	u8 result_value = 0;

	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		HISI_FB_ERR("hisifd is null\n");
		ret = snprintf(buf, PAGE_SIZE, "%d\n", result_value);
		return ret;
	}

	if (!hisifd->panel_power_on){
		HISI_FB_INFO("panel is poweroff\n");
		ret = snprintf(buf, PAGE_SIZE, "%d\n", result_value);
		return ret;
	}

	pcd_gpio = gpio_get_value_cansleep(gpio_pcd);
	errflag_gpio = gpio_get_value_cansleep(gpio_err_flag);

	HISI_FB_INFO("pcd:%d, errflag:%d\n", pcd_gpio, errflag_gpio);

	if ((pcd_gpio == 1) && (errflag_gpio == 0)) {
		result_value = 0; // PCD_ERR_FLAG_SUCCESS
	} else if ((pcd_gpio == 0) && (errflag_gpio == 0)) {
		result_value = 1; //only  PCD_FAIL
	} else if ((pcd_gpio == 1) && (errflag_gpio == 1)) {
		result_value = 2; //only ERRFLAG FAIL
	} else if ((pcd_gpio == 0) && (errflag_gpio == 1)) {
		result_value = 3; //PCD_ERR_FLAG_FAIL
	} else
		result_value = 0;

	ret = snprintf(buf, PAGE_SIZE, "%d\n", result_value);
	return ret;
}

static int mipi_samsung_s6e3ha3x01_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	return 0;
}

#if 0
static ssize_t mipi_samsung_s6e3ha3x01_check_reg_show(struct platform_device *pdev, char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char lcd_reg_CC[] = {0xCC};
	int read_value = 0;
	ssize_t ret = 0;
	char __iomem *mipi_dsi0_base = NULL;

	struct dsi_cmd_desc lcd_check_reg[] = {
		{DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_CC), lcd_reg_CC},
	};

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	ret = mipi_dsi_cmds_rx(&read_value, lcd_check_reg, ARRAY_SIZE(lcd_check_reg), mipi_dsi0_base);

	HISI_FB_ERR("lcd_reg_CC: %d", read_value);
	ret = snprintf(buf, PAGE_SIZE, "lcd_reg_CC: %d", read_value);

	return ret ;
}
#endif

static struct hisi_panel_info samsung_s6e3ha3x01_panel_info = {0};
static struct hisi_fb_panel_data samsung_s6e3ha3x01_panel_data = {
	.panel_info = &samsung_s6e3ha3x01_panel_info,
	.set_fastboot = mipi_samsung_s6e3ha3x01_set_fastboot,
	.on = mipi_samsung_s6e3ha3x01_on,
	.off = mipi_samsung_s6e3ha3x01_off,
	.remove = mipi_samsung_s6e3ha3x01_remove,
	.set_backlight = mipi_samsung_s6e3ha3x01_set_brightness,

	.lcd_model_show = mipi_samsung_s6e3ha3x01_model_show,
//	.amoled_pcd_errflag_check = mipi_samsung_pcd_errflag_check,
	.set_display_region = mipi_samsung_s6e3ha3x01_set_display_region,
//	.lcd_check_reg = mipi_samsung_s6e3ha3x01_check_reg_show,
	.set_display_resolution = NULL,
};


/*******************************************************************************
**
*/
static int mipi_samsung_s6e3ha3x01_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;

	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;


	HISI_FB_INFO("+.\n");

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SAMSUNG_S6E3HA3X01);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_SAMSUNG_S6E3HA3X01);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_DUAL_MIPI_CMD;
	}

	lcd_display_type = PANEL_DUAL_MIPI_CMD;
	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);
	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}
	gpio_reset = of_get_named_gpio(np, "gpios", 2);  /*gpio_4_5, gpio_037*/
	gpio_lcd_vdd3 = of_get_named_gpio(np, "gpios", 0);
	gpio_lcd_vddr = of_get_named_gpio(np, "gpios", 1);

	pdev->id = 1;
	/* init panel info */
	pinfo = samsung_s6e3ha3x01_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1600;
	pinfo->yres = 2560;
	pinfo->width = 75;
	pinfo->height = 133;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type; //BL_SET_BY_MIPI;

	pinfo->bl_min = 1;
	pinfo->bl_max = 255;
	pinfo->vsync_ctrl_type = 0; //(VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS);
		
	pinfo->type = lcd_display_type;
	pinfo->bl_default = 102;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;
	pinfo->dirty_region_updt_support = 0;

	if(runmode_is_factory()) {
		pinfo->sbl_support = 0;
	} else {
		pinfo->sbl_support = 0;
	}

	pinfo->color_temperature_support = 1;
	pinfo->smart_bl.strength_limit = 128;
	pinfo->smart_bl.calibration_a = 60;
	pinfo->smart_bl.calibration_b = 95;
	pinfo->smart_bl.calibration_c = 5;
	pinfo->smart_bl.calibration_d = 1;
	pinfo->smart_bl.t_filter_control = 5;
	pinfo->smart_bl.backlight_min = 480;
	pinfo->smart_bl.backlight_max = 4096;
	pinfo->smart_bl.backlight_scale = 0xff;
	pinfo->smart_bl.ambient_light_min = 14;
	pinfo->smart_bl.filter_a = 1738;
	pinfo->smart_bl.filter_b = 6;
	pinfo->smart_bl.logo_left = 0;
	pinfo->smart_bl.logo_top = 0;

	pinfo->ifbc_type = IFBC_TYPE_NONE;

	pinfo->ldi.h_back_porch = 96;  //136;
	pinfo->ldi.h_front_porch = 108; //188;
	pinfo->ldi.h_pulse_width = 48;
	pinfo->ldi.v_back_porch = 12; //16;
	pinfo->ldi.v_front_porch = 14; //18;
	pinfo->ldi.v_pulse_width = 4;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.dsi_bit_clk = 450;
	pinfo->dsi_bit_clk_upt_support = 0;
	pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

	pinfo->pxl_clk_rate = 288*1000000UL;
	
	//is dual_mipi or single_mipi
	if (is_dual_mipi_panel_ext(pinfo))  {
		pinfo->ifbc_type = IFBC_TYPE_NONE;
		pinfo->pxl_clk_rate_div = 2;
		HISI_FB_INFO("PANEL_DUAL_MIPI_CMD: 8 lane \n");
	} else {

	}

	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}

	/* vcc init */
	ret = vcc_cmds_tx(pdev, samsung_s6e3ha3x01_vcc_init_cmds,
		ARRAY_SIZE(samsung_s6e3ha3x01_vcc_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("vcc init failed!\n");
		goto err_return;
	}

#if 0 //AMOLED_CHECK_INT
	ret = request_threaded_irq(gpio_to_irq(gpio_pcd), NULL, pcd_irq_isr_func,
			IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
			"pcd_irq", (void *)pdev);
	if (ret != 0) {
		HISI_FB_ERR("request_irq failed, irq_no=%d error=%d!\n", gpio_to_irq(gpio_pcd), ret);
	}

	ret = request_threaded_irq(gpio_to_irq(gpio_err_flag), NULL, errflag_irq_isr_func,
			IRQF_ONESHOT | IRQF_TRIGGER_RISING,
			"errflag_irq", (void *)pdev);
	if (ret != 0) {
		HISI_FB_ERR("request_irq failed, irq_no=%d error=%d!\n", gpio_to_irq(gpio_err_flag), ret);
	}
#endif

	/* pinctrl init */
	ret = pinctrl_cmds_tx(pdev, samsung_s6e3ha3x01_pinctrl_init_cmds,
			ARRAY_SIZE(samsung_s6e3ha3x01_pinctrl_init_cmds));
	if (ret != 0) {
	        HISI_FB_ERR("Init pinctrl failed, defer\n");
		goto err_return;
	}

	if (is_fastboot_display_enable()) {
		vcc_cmds_tx(pdev, samsung_s6e3ha3x01_vcc_enable_cmds,
			ARRAY_SIZE(samsung_s6e3ha3x01_vcc_enable_cmds));
	}
	/* alloc panel device data */
	ret = platform_device_add_data(pdev, &samsung_s6e3ha3x01_panel_data,
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("platform_device_add_data failed!\n");
		goto err_device_put;
	}

	hisi_fb_add_device(pdev);

	HISI_FB_INFO("-.\n");

	return 0;

err_device_put:
	platform_device_put(pdev);
err_return:
	return ret;
err_probe_defer:
	return -EPROBE_DEFER;
}

static const struct of_device_id hisi_panel_match_table[] = {
    {
        .compatible = DTS_COMP_SAMSUNG_S6E3HA3X01,
        .data = NULL,
    },
    {},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_samsung_s6e3ha3x01_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_samsung_S6E3HA3X01",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_samsung_s6e3ha3x01_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_samsung_s6e3ha3x01_init);
