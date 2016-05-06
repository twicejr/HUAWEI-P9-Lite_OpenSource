/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
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


#define DTS_COMP_HDMI_FAKE_PANEL	"hisilicon,hdmi_fake_panel"


static struct hisi_panel_info fake_panel_info = {0};
static struct hisi_fb_panel_data fake_panel_data = {
	.panel_info = &fake_panel_info,
	.set_fastboot = NULL,
	.on = NULL,
	.off = NULL,
	.remove = NULL,
	.set_backlight = NULL,
};

static int hdmi_fake_panel_probe(struct platform_device *pdev)
{
	int ret = 0;
	uint32_t is_fake_hdmi = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;

	if (hisi_fb_device_probe_defer(PANEL_HDMI, BL_SET_BY_NONE)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_HDMI_FAKE_PANEL);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_HDMI_FAKE_PANEL);
		goto err_return;
	}

	ret = of_property_read_u32(np, "fake_hdmi", &is_fake_hdmi);
	if (ret) {
		HISI_FB_DEBUG("dts get fake_hdmi fail");
		is_fake_hdmi = 0;
	}
	HISI_FB_INFO("is_fake_hdmi=%d.\n", is_fake_hdmi);

	pdev->id = 1;
	/* init lcd info */
	pinfo = fake_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width  = 61;
	pinfo->height = 109;
	pinfo->type = PANEL_HDMI;
	pinfo->orientation = LCD_LANDSCAPE;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = BL_SET_BY_NONE;

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


	pinfo->ifbc_type = IFBC_TYPE_NONE;
	pinfo->fake_hdmi = is_fake_hdmi;

	pinfo->vsync_ctrl_type = 0;
	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;
	pinfo->dirty_region_updt_support = 0;

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

	pinfo->ldi.h_back_porch = 23;
	pinfo->ldi.h_front_porch = 50;
	pinfo->ldi.h_pulse_width = 20;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 4;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.dsi_bit_clk = 480;

	pinfo->pxl_clk_rate = 27 * 1000000UL;

	/* alloc panel device data */
	ret = platform_device_add_data(pdev, &fake_panel_data,
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
		.compatible = DTS_COMP_HDMI_FAKE_PANEL,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = hdmi_fake_panel_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "hdmi_fake_panel",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init hdmi_fake_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(hdmi_fake_panel_init);
