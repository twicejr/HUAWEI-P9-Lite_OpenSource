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

#define DTS_COMP_MIPI_FAKE_PANEL "hisilicon,mipi_fake_panel"

#define GPIO_VSP	"gpio_lcd_vsp"
#define GPIO_VSN	"gpio_lcd_vsn"
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"

static struct hisi_fb_panel_data g_panel_data;

static int hkadc_buf = 0;
static uint32_t gpio_lcd_bl_enable;
struct ldo_ops {
	void(*hisi_vsp)(bool en);
	void(*hisi_vsn)(bool en);
	void(*hisi_vddio)(bool en);
	void(*hisi_vci)(bool en);
};

struct voltage_node {
	unsigned int vsn_gpio;
	unsigned int vsp_gpio;
};

static struct voltage_node volt = {0};
static struct ldo_ops ldo_en;

static struct gpio_desc fake_lcd_gpio_request_cmds[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_VSP, &volt.vsp_gpio, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_VSN, &volt.vsn_gpio, 0},
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

/*******************************************************************************
**
*/
static int mipi_fake_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_fake_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	/* backlight on */
	//hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_fake_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);
	/* backlight off */
	//hisi_lcd_backlight_off(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_fake_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	/*BUG_ON(hisifd == NULL);*/

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_fake_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_fake_panel_bl_update(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	if (bl_level > 0) {
		/*enable bl gpio*/
		gpio_direction_output(gpio_lcd_bl_enable, 1);
		mdelay(2);
		/* backlight on */
		hisi_lcd_backlight_on(pdev);

		HISI_FB_INFO("set backlight to %d\n", bl_level);
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else {
		ret = hisi_blpwm_set_backlight(hisifd, 0);
		/* backlight off */
		hisi_lcd_backlight_off(pdev);
		/*disable bl gpio*/
		gpio_direction_output(gpio_lcd_bl_enable, 0);
	}

	return 0;
}

static ssize_t mipi_fake_panel_lcd_hkadc_debug_show(struct platform_device *pdev, char *buf)
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

static ssize_t mipi_fake_panel_lcd_hkadc_debug_store(struct platform_device *pdev,
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

static void hisi_vsp_enable(bool en)
{
	HISI_FB_INFO("vsp enable(%d)\n", en);

	if(en)
		gpio_direction_output(volt.vsp_gpio, 1);
	else
		gpio_direction_output(volt.vsp_gpio, 0);
}

static void hisi_vsn_enable(bool en)
{
	HISI_FB_INFO("vsn enable(%d)\n", en);

	if(en)
		gpio_direction_output(volt.vsn_gpio, 1);
	else
		gpio_direction_output(volt.vsn_gpio, 0);
}

static void hisi_vddio_enable(bool en)
{
	HISI_FB_INFO("obsolescent\n");

}

static void hisi_vci_enable(bool en)
{
	HISI_FB_INFO("obsolescent\n");

}

static ssize_t mipi_fake_panel_lcd_voltage_enable_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	char command[10] = {0};
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t bl_value = 0;
	char bl_value_buf[10] = {0};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (!sscanf(buf, "%s", command)) {
		HISI_FB_INFO("bad command(%s)\n", command);
		return count;
	}

	HISI_FB_INFO("command(%s)\n", command);
	if (!strncmp("vsp:", command, strlen("vsp:"))) {
		if('0' == command[strlen("vsp:")])
			ldo_en.hisi_vsp(false);
		else
			ldo_en.hisi_vsp(true);
	}

	if (!strncmp("vsn:", command, strlen("vsn:"))) {
		if('0' == command[strlen("vsn:")])
			ldo_en.hisi_vsn(false);
		else
			ldo_en.hisi_vsn(true);
	}

	if (!strncmp("vddio:", command, strlen("vddio:"))) {
		if('0' == command[strlen("vddio:")])
			ldo_en.hisi_vddio(false);
		else
			ldo_en.hisi_vddio(true);
	}

	if (!strncmp("vci:", command, strlen("vci:"))) {
		if('0' == command[strlen("vci:")])
			ldo_en.hisi_vci(false);
		else
			ldo_en.hisi_vci(true);
	}

	if (!strncmp("bl:", command, strlen("bl:"))) {
		if (((strlen(command) - strlen("bl:")) > 0) &&((strlen(command) - strlen("bl:")) < sizeof(bl_value_buf))) {
			memcpy(bl_value_buf, &command[strlen("bl:")], strlen(command)-strlen("bl:"));
			bl_value = simple_strtoul(bl_value_buf, NULL, 0);
			HISI_FB_INFO("bl_value_buf is %s, bl_value is %d\n", bl_value_buf, bl_value);
		} else {
			bl_value = 0;
		}

		mipi_fake_panel_bl_update(pdev, bl_value);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static struct hisi_panel_info mipi_fake_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &mipi_fake_panel_info,
	.set_fastboot = mipi_fake_panel_set_fastboot,
	.on = mipi_fake_panel_on,
	.off = mipi_fake_panel_off,
	.remove = mipi_fake_panel_remove,
	.set_backlight = mipi_fake_panel_set_backlight,
	.lcd_hkadc_debug_show = mipi_fake_panel_lcd_hkadc_debug_show,
	.lcd_hkadc_debug_store = mipi_fake_panel_lcd_hkadc_debug_store,
	.lcd_voltage_enable_store = mipi_fake_panel_lcd_voltage_enable_store,
};


/*******************************************************************************
**
*/
static int mipi_fake_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;

	if (hisi_fb_device_probe_defer(PANEL_MIPI_VIDEO, BL_SET_BY_NONE)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_MIPI_FAKE_PANEL);

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_MIPI_FAKE_PANEL);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_MIPI_FAKE_PANEL);
		goto err_return;
	}

	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width = 62;
	pinfo->height = 110;
	pinfo->type = PANEL_MIPI_VIDEO;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = BL_SET_BY_BLPWM;

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

	pinfo->sbl_support = 0;
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

	pinfo->ldi.h_back_porch = 40;
	pinfo->ldi.h_front_porch = 90;
	pinfo->ldi.h_pulse_width = 20;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 4;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->mipi.dsi_bit_clk = 480;

	pinfo->pxl_clk_rate = 144 * 1000000;

	volt.vsp_gpio = of_get_named_gpio(np, "gpios", 2);  // gpio_1_7
	volt.vsn_gpio = of_get_named_gpio(np, "gpios", 0);  //gpio_1_1

	ldo_en.hisi_vsp = hisi_vsp_enable;
	ldo_en.hisi_vsn = hisi_vsn_enable;
	ldo_en.hisi_vci = hisi_vci_enable;
	ldo_en.hisi_vddio = hisi_vddio_enable;

	gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 1);

	HISI_FB_INFO("gpio_lcd_bl_enable is %d, bl_set_type is %d\n", gpio_lcd_bl_enable, pinfo->bl_set_type);
	/* lcd gpio request */
	gpio_cmds_tx(fake_lcd_gpio_request_cmds, \
		ARRAY_SIZE(fake_lcd_gpio_request_cmds));

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
}

static const struct of_device_id hisi_panel_match_table[] = {
	{
		.compatible = DTS_COMP_MIPI_FAKE_PANEL,
		.data = NULL,
	},
	{},
};

MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_fake_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_fake_panel",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_fake_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_fake_panel_init);
