/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "hisi_fb.h"
#include <linux/huawei/hisi_adc.h>
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#include "hw_lcd_panel.h"
#include "hw_lcd_effects.h"
#include <huawei_platform/log/log_jank.h>

static bool checksum_enable_ctl = false;
static int hkadc_buf = 0;


/***********************************************************
*platform driver definition
***********************************************************/
/*
*probe match table
*/
static struct of_device_id hw_lcd_match_table[] = {
	{
		.compatible = "hisilicon,auo_otm1901a_5p2_1080p_video",//default is tianma-nt35521
		.data = NULL,
	},
	{},
};

/*
*panel platform driver
*/
static struct platform_driver this_driver = {
	.probe = hw_lcd_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "hw_mipi_panel",
		.of_match_table = hw_lcd_match_table,
	},
};

/***********************************************************
*variable definition
***********************************************************/
static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00, 0x04, 0x37
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00, 0x07, 0x7F
};

static struct dsi_cmd_desc set_display_address[] = {
	{
		DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x
	},
	{
		DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y
	},
};

/***********************************************************
*function definition
***********************************************************/
/*
*name:hw_lcd_parse_array_data
*function:parse panel data from dtsi
*@np:device tree node
*@name:parse name
*@out:output data
*/
static int hw_lcd_parse_array_data(struct device_node* np, char* name, struct array_data* out)
{
	const char* data;
	int blen = 0;
	char* buf;
	int i;

	data = of_get_property(np, name, &blen);

	if (!data) {
		HISI_FB_ERR("Parse array name: %s, fail\n", name);
		return -ENOMEM;
	}

	/*The property is 4bytes long per element in cells: <>*/
	blen = blen / 4;
	/*If use bype property: [], this division should be removed*/
	buf = kzalloc(sizeof(char) * blen, GFP_KERNEL);

	if (!buf) {
		HISI_FB_ERR("Allocate memory fail: buf\n");
		return -ENOMEM;
	}

	//For use byte property: []
	//memcpy(buf, data, blen);

	//For use cells property: <>
	for (i = 0; i < blen; i++) {
		buf[i] = data[i * 4 + 3];
	}

	out->buf = buf;
	out->cnt = blen;
	return 0;
}

/*
*name:hw_lcd_parse_dcs_cmds
*function:parse panel dcs cmds from dtsi
*@np:device tree node
*@cmd_name:parse name
*@cmd_set:output dsi command
*/
static int hw_lcd_parse_dcs_cmds(struct device_node* np, char* cmd_name, struct dsi_cmd_set* cmd_set)
{
	const char* data;
	int blen = 0, len, cmd_len;
	char* buf, *bp;
	int i, cnt;
	struct dsi_cmd_desc* dsi_cmds;
	const int len_cmd_hdr = 5;
	const int index_cmd_dlen = 4;
	const int index_cmd_waittype = 3;
	const int index_cmd_wait = 2;
	const int index_cmd_vc = 1;
	const int index_cmd_dtype = 0;

	data = of_get_property(np, cmd_name, &blen);

	if (!data) {
		HISI_FB_ERR("Parse panel dcs commands: %s, fail\n", cmd_name);
		return -ENOMEM;
	}

	/*The property is 4bytes long per element in cells: <>*/
	blen = blen / 4;
	/*If use bype property: [], this division should be removed*/
	buf = kzalloc(sizeof(char) * blen, GFP_KERNEL);

	if (!buf) {
		HISI_FB_ERR("Allocate memory fail: buf\n");
		return -ENOMEM;
	}

	//For use byte property: []
	//memcpy(buf, data, blen);

	//For use cells property: <>
	for (i = 0; i < blen; i++) {
		buf[i] = data[i * 4 + 3];
	}

	/* scan dcs commands */
	bp = buf;
	len = blen;
	cnt = 0;

	while (len >= len_cmd_hdr) {
		cmd_len = (int) * (bp + index_cmd_dlen);

		if ((cmd_len + len_cmd_hdr) > len) {
			HISI_FB_ERR("DSC commands: %s, at %dth command with len=%d, WRONG\n", cmd_name, cnt + 1, cmd_len);
			goto exit_free;
		}

		bp += (cmd_len + len_cmd_hdr);
		len -= (cmd_len + len_cmd_hdr);
		cnt++;
	}

	if (len != 0) {
		HISI_FB_ERR("DSC commands incomplete!");
		goto exit_free;
	}

	dsi_cmds = kzalloc(cnt * sizeof(struct dsi_cmd_desc), GFP_KERNEL);

	if (!dsi_cmds) {
		HISI_FB_ERR("Allocate memory fail: dsi_cmd_desc\n");
		goto exit_free;
	}

	bp = buf;

	for (i = 0; i < cnt; i++) {
		dsi_cmds[i].dtype = (int) * (bp + index_cmd_dtype);
		dsi_cmds[i].vc = (int) * (bp + index_cmd_vc);
		dsi_cmds[i].wait = (int) * (bp + index_cmd_wait);
		dsi_cmds[i].waittype = (int) * (bp + index_cmd_waittype);
		dsi_cmds[i].dlen = (int) * (bp + index_cmd_dlen);
		dsi_cmds[i].payload = bp + len_cmd_hdr;
		bp += (dsi_cmds[i].dlen + len_cmd_hdr);
	}

	//TODO: return the dynamic allocate memory: buf, for future clean up.
	cmd_set->buf = buf;
	cmd_set->size_buf = blen;
	cmd_set->cmd_set = dsi_cmds;
	cmd_set->cmd_cnt = cnt;

	return 0;


exit_free:
	kfree(buf);
	return -ENOMEM;

}

/*
*name:hw_lcd_parse_dts
*function:parse dts data
*@np:device tree node
*/
static int hw_lcd_parse_dts(struct device_node* np)
{
	int ret = 0;

	/*Parse panel on cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-on-cmds", &lcd_info.display_on_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-on-cmds failed!\n");
		return -ENOMEM;
	}

	/*Parse panel off cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-off-cmds", &lcd_info.display_off_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-off-cmds failed!\n");
		return -ENOMEM;
	}

	/*Parse cabc off cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-cabc-off-mode", &lcd_info.cabc_off_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-cabc-off-mode failed!\n");
		return -ENOMEM;
	}

	/*Parse cabc ui cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-cabc-ui-mode", &lcd_info.cabc_ui_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-cabc-ui-mode failed!\n");
		return -ENOMEM;
	}

	/*Parse cabc still cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-cabc-still-mode", &lcd_info.cabc_still_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-cabc-still-mode failed!\n");
		return -ENOMEM;
	}

	/*Parse cabc moving cmds*/
	ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-cabc-moving-mode", &lcd_info.cabc_moving_cmds);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-cabc-moving-mode failed!\n");
		return -ENOMEM;
	}

	/*esd check*/
	ret = hw_lcd_parse_array_data(np, "hisilicon,dss-esd-reg", &lcd_info.esd_reg);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-esd-reg failed!\n");
		return -ENOMEM;
	}
	ret = hw_lcd_parse_array_data(np, "hisilicon,dss-esd-value", &lcd_info.esd_value);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-esd-value failed!\n");
		return -ENOMEM;
	}

	/*mipi check reg*/
	ret = hw_lcd_parse_array_data(np, "hisilicon,dss-mipi-check-reg", &lcd_info.mipi_check_reg);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-mipi-check-reg failed!\n");
		return -ENOMEM;
	}

	ret = hw_lcd_parse_array_data(np, "hisilicon,dss-mipi-check-value", &lcd_info.mipi_check_value);
	if (ret) {
		HISI_FB_ERR("parse hisilicon,dss-mipi-check-value failed!\n");
		return -ENOMEM;
	}

	return 0;
}

/*
*name:hw_lcd_info_init
*function:parse panel info from dtsi
*@np:device tree node
*@pinfo:lcd panel info
*/
static int hw_lcd_info_init(struct device_node* np, struct hisi_panel_info* pinfo)
{
	int ret = 0;

	/*parse panel name*/
	lcd_info.panel_name = (char*)of_get_property(np, "hisilicon,dss-panel-name", NULL);
	/*parse panel info*/
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-xres", &pinfo->xres);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-yres", &pinfo->yres);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-width", &pinfo->width);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-height", &pinfo->height);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-orientation", &pinfo->orientation);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-bpp", &pinfo->bpp);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-bgrfmt", &pinfo->bgr_fmt);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-bl-type", &pinfo->bl_set_type);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-blmin", &pinfo->bl_min);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-blmax", &pinfo->bl_max);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-bl-def", &pinfo->bl_default);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-type", &pinfo->type);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-ifbc-type", &pinfo->ifbc_type);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-bl-pwm-preci-type", &pinfo->blpwm_precision_type);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-frc-enable", &pinfo->frc_enable);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-esd-enable", &pinfo->esd_enable);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-esd-skip-mipi-check", &pinfo->esd_skip_mipi_check);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-lcd-ajust-support", &pinfo->lcd_adjust_support);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-pxl-clk", &pinfo->pxl_clk_rate);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-pxl-clk-div", &pinfo->pxl_clk_rate_div);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-dirt-updt-support", &pinfo->dirty_region_updt_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-dsi-upt-support", &pinfo->dsi_bit_clk_upt_support);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-panel-vsyn-ctr-type", &pinfo->vsync_ctrl_type);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-panel-step-support", &pinfo->lcd_uninit_step_support);

	/*effect info*/
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-sbl-support", &pinfo->sbl_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-gamma-support", &pinfo->gamma_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-gmp-support", &pinfo->gmp_support);

	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-color-temp-support", &pinfo->color_temperature_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-xcc-support", &pinfo->xcc_support);

	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-prefix-ce-support", &pinfo->prefix_ce_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-prefix-sharp-one-d-support", &pinfo->prefix_sharpness1D_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-prefix-sharp-two-d-support", &pinfo->prefix_sharpness2D_support);

	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-acm-support", &pinfo->acm_support);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-acm-ce-support", &pinfo->acm_ce_support);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-valid-num", &pinfo->acm_valid_num);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh0", &pinfo->r0_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh0", &pinfo->r0_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh1", &pinfo->r1_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh1", &pinfo->r1_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh2", &pinfo->r2_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh2", &pinfo->r2_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh3", &pinfo->r3_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh3", &pinfo->r3_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh4", &pinfo->r4_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh4", &pinfo->r4_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh5", &pinfo->r5_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh5", &pinfo->r5_lh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_hh6", &pinfo->r6_hh);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-acm-r_lh6", &pinfo->r6_lh);

	/*sbl info*/
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-stren-limit", &pinfo->smart_bl.strength_limit);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-cal-a", &pinfo->smart_bl.calibration_a);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-cal-b", &pinfo->smart_bl.calibration_b);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-cal-c", &pinfo->smart_bl.calibration_c);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-cal-d", &pinfo->smart_bl.calibration_d);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-tf-ctl", &pinfo->smart_bl.t_filter_control);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-blmin", &pinfo->smart_bl.backlight_min);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-blmax", &pinfo->smart_bl.backlight_max);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-bl-scale", &pinfo->smart_bl.backlight_scale);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-am-light-min", &pinfo->smart_bl.ambient_light_min);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-filter-a", &pinfo->smart_bl.filter_a);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-filter-b", &pinfo->smart_bl.filter_b);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-logo-left", &pinfo->smart_bl.logo_left);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-logo-top", &pinfo->smart_bl.logo_top);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-variance-intensity-space", &pinfo->smart_bl.variance_intensity_space);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-slope-max", &pinfo->smart_bl.slope_max);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-sbl-slope-min", &pinfo->smart_bl.slope_min);

	/*ldi info*/
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-h-back-porch", &pinfo->ldi.h_back_porch);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-h-front-porch", &pinfo->ldi.h_front_porch);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-h-pulse-width", &pinfo->ldi.h_pulse_width);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-v-back-porch", &pinfo->ldi.v_back_porch);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-v-front-porch", &pinfo->ldi.v_front_porch);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-v-pulse-width", &pinfo->ldi.v_pulse_width);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-ldi-v-pulse-width", &pinfo->ldi.v_pulse_width);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-ldi-hsync-plr", &pinfo->ldi.hsync_plr);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-ldi-vsync-plr", &pinfo->ldi.vsync_plr);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-ldi-pixel-clk-plr", &pinfo->ldi.pixelclk_plr);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-ldi-data-en-plr", &pinfo->ldi.data_en_plr);

	/*mipi info*/
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-mipi-lane-nums", &pinfo->mipi.lane_nums);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-mipi-color-mode", &pinfo->mipi.color_mode);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-mipi-vc", &pinfo->mipi.vc);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-burst-mode", &pinfo->mipi.burst_mode);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk", &pinfo->mipi.dsi_bit_clk);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-max-esc-clk", &pinfo->mipi.max_tx_esc_clk);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-val-a", &pinfo->mipi.dsi_bit_clk_val1);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-val-b", &pinfo->mipi.dsi_bit_clk_val2);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-val-c", &pinfo->mipi.dsi_bit_clk_val3);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-val-d", &pinfo->mipi.dsi_bit_clk_val4);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-val-e", &pinfo->mipi.dsi_bit_clk_val5);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-dsi-bit-clk-upt", &pinfo->mipi.dsi_bit_clk_upt);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-rg-vcm-adjust", &pinfo->mipi.rg_vrefsel_vcm_adjust);
	OF_PROPERTY_READ_U8_RETURN(np, "hisilicon,dss-mipi-non-continue-enable", &pinfo->mipi.non_continue_en);
	OF_PROPERTY_READ_U32_RETURN(np, "hisilicon,dss-mipi-clk-post-adjust", &pinfo->mipi.clk_post_adjust);

	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-left-align", &pinfo->dirty_region_info.left_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-right-align", &pinfo->dirty_region_info.right_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-top-align", &pinfo->dirty_region_info.top_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-bott-align", &pinfo->dirty_region_info.bottom_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-width-align", &pinfo->dirty_region_info.w_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-height-align", &pinfo->dirty_region_info.h_align);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-width-min", &pinfo->dirty_region_info.w_min);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-height-min", &pinfo->dirty_region_info.h_min);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-top-start", &pinfo->dirty_region_info.top_start);
	OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, "hisilicon,dss-dirt-bott-start", &pinfo->dirty_region_info.bottom_start);

	/*lcd info*/
	OF_PROPERTY_READ_U32_RETURN(np, "lcdanalog-vcc", &lcd_info.lcdanalog_vcc);
	OF_PROPERTY_READ_U32_RETURN(np, "lcdio-vcc", &lcd_info.lcdio_vcc);
	OF_PROPERTY_READ_U32_RETURN(np, "lcd-bias", &lcd_info.lcd_bias);
	OF_PROPERTY_READ_U32_RETURN(np, "lcd-vsp", &lcd_info.lcd_vsp);
	OF_PROPERTY_READ_U32_RETURN(np, "lcd-vsn", &lcd_info.lcd_vsn);
	OF_PROPERTY_READ_U8_RETURN(np, "lcd-rst-first-high", &lcd_info.reset_step1_H);
	OF_PROPERTY_READ_U8_RETURN(np, "lcd-rst-low", &lcd_info.reset_L);
	OF_PROPERTY_READ_U8_RETURN(np, "lcd-rst-second-hight", &lcd_info.reset_step2_H);
	OF_PROPERTY_READ_U8_RETURN(np, "iovcc-on-is-need-reset", &lcd_info.is_need_reset);
	OF_PROPERTY_READ_U8_RETURN(np, "iovcc-off-is-need-delay", &lcd_info.is_need_delay);
	OF_PROPERTY_READ_U8_RETURN(np, "lcd-ctrl-tp-power", &g_lcd_control_tp_power);
	OF_PROPERTY_READ_U8_RETURN(np, "lock-cmd-support", &lcd_info.lock_cmd_support);
	OF_PROPERTY_READ_U8_RETURN(np, "read-power-status", &lcd_info.read_power_status);

	pinfo->pxl_clk_rate *= 1000000UL;
	pinfo->mipi.max_tx_esc_clk *= 1000000;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM) {
		pinfo->blpwm_input_ena = 0;
	}

	if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X) {
		pinfo->ifbc_cmp_dat_rev0 = 0;
		pinfo->ifbc_cmp_dat_rev1 = 0;
		pinfo->ifbc_auto_sel = 1;
		pinfo->ifbc_orise_ctr = 1;

		//FIXME:
		pinfo->pxl_clk_rate_div = 3;

		pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_FRAME;
	}

	/*ce rely on acm*/
	if (pinfo->acm_support == 0) {
		pinfo->acm_ce_support = 0;
	}

	return ret;
}

/*
*name:hw_lcd_vcc_init
*function:init lcd vcc parameter
*@cmds:vcc cmds
*@cnt:vcc number
*/
static void hw_lcd_vcc_init(struct vcc_desc* cmds, int cnt)
{
	int i = 0;
	struct vcc_desc* cm = NULL;

	cm = cmds;
	for (i = 0; i < cnt; i++) {
		if (cm->dtype == DTYPE_VCC_SET_VOLTAGE) {
			if (0 == strncmp(cm->id, HW_LCD_VCC_LCDANALOG_NAME, strlen(cm->id))) {
				cm->min_uV = lcd_info.lcdanalog_vcc;
				cm->max_uV = lcd_info.lcdanalog_vcc;
			} else if (0 == strncmp(cm->id, HW_LCD_VCC_LCDIO_NAME, strlen(cm->id))) {
				cm->min_uV = lcd_info.lcdio_vcc;
				cm->max_uV = lcd_info.lcdio_vcc;
			} else if (0 == strncmp(cm->id, VCC_LCDBIAS_NAME, strlen(cm->id))) {
				cm->min_uV = lcd_info.lcd_bias;
				cm->max_uV = lcd_info.lcd_bias;
			} else if (0 == strncmp(cm->id, VCC_LCD_VSP_NAME, strlen(cm->id))) {
				cm->min_uV = lcd_info.lcd_bias;
				cm->max_uV = lcd_info.lcd_bias;
			} else if (0 == strncmp(cm->id, VCC_LCD_VSN_NAME, strlen(cm->id))) {
				cm->min_uV = lcd_info.lcd_bias;
				cm->max_uV = lcd_info.lcd_bias;
			}
		}
		cm++;
	}
}

/*
*name:hw_lcd_vcc_init
*function:init lcd vcc parameter
*@cmds:vcc cmds
*@cnt:vcc number
*/
static void hw_lcd_reset_init(struct gpio_desc* cmds)
{
	struct gpio_desc* cm = NULL;

	cm = cmds;
	cm->wait = lcd_info.reset_step1_H;
	cm++;
	cm->wait = lcd_info.reset_L;
	cm++;
	cm->wait = lcd_info.reset_step2_H;
}


/*
*name:hw_lcd_get_id
*function:power on panel
*@pdev:platform device
*/
static int hw_lcd_get_id(struct platform_device* pdev)
{
	int pulldown_value = 0;
	int pullup_value = 0;
	int lcd_status = 0;
	int lcd_id0 = 0;
	int lcd_id1 = 0;

	/*set gpio direction to out, set id0 to low*/
	gpio_cmds_tx(hw_lcd_gpio_id0_low_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id0_low_cmds));
	/*set gpio direction to input*/
	gpio_cmds_tx(hw_lcd_gpio_id0_input_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id0_input_cmds));
	/*read id0 value*/
	pulldown_value = gpio_get_value(lcd_info.lcd_id0);

	/*set gpio direction to out, set id0 to high*/
	gpio_cmds_tx(hw_lcd_gpio_id0_high_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id0_high_cmds));
	/*set gpio direction to input*/
	gpio_cmds_tx(hw_lcd_gpio_id0_input_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id0_input_cmds));
	/*read id0 value*/
	pullup_value = gpio_get_value(lcd_info.lcd_id0);

	if (pulldown_value != pullup_value) {
		lcd_id0 = 2; //floating
	} else {
		lcd_id0 = pulldown_value; //high or low
	}

	/*set gpio direction to out, set id1 to low*/
	gpio_cmds_tx(hw_lcd_gpio_id1_low_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id1_low_cmds));
	/*set gpio direction to input*/
	gpio_cmds_tx(hw_lcd_gpio_id1_input_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id1_input_cmds));
	/*read id1 value*/
	pulldown_value = gpio_get_value(lcd_info.lcd_id1);

	/*set gpio direction to out, set id1 to low*/
	gpio_cmds_tx(hw_lcd_gpio_id1_high_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id1_high_cmds));
	/*set gpio direction to input*/
	gpio_cmds_tx(hw_lcd_gpio_id1_input_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id1_input_cmds));
	/*read id1 value*/
	pullup_value = gpio_get_value(lcd_info.lcd_id1);

	if (pulldown_value != pullup_value) {
		lcd_id1 = 2; //floating
	} else {
		lcd_id1 = pulldown_value; //high or low
	}

	lcd_status = (lcd_id0 | (lcd_id1 << 2));
	HISI_FB_INFO("lcd_id0:%d, lcd_id1:%d, lcd_status = 0x%x.\n", lcd_id0, lcd_id1, lcd_status);
	return lcd_status;
}

/*
*name:hw_lcd_on
*function:power on panel
*@pdev:platform device
*/
static int hw_lcd_on(struct platform_device* pdev)
{
	struct hisi_fb_data_type* hisifd = NULL;
	struct hisi_panel_info* pinfo = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	int error = 0;
#if HW_LCD_POWER_STATUS_CHECK
	uint32_t status = 0;
	uint32_t try_times = 0;
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

#if HW_LCD_DEBUG
	if(is_enable_mipiclk_debug()){
		hisifd->panel_info.mipi.dsi_bit_clk = get_mipiclk_debug();
		hisifd->panel_info.mipi.dsi_bit_clk_upt = get_mipiclk_debug();
	}
#endif
	pinfo = &(hisifd->panel_info);

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		g_debug_enable = BACKLIGHT_PRINT_TIMES;
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
#if HW_LCD_DEBUG
	if (is_enable_vsp_vsn_debug()){
		lcd_debug_set_vsp_vsn(hw_lcd_scharger_vcc_set_cmds, ARRAY_SIZE(hw_lcd_scharger_vcc_set_cmds));
			/*set scharger vcc*/
		vcc_cmds_tx(NULL, hw_lcd_scharger_vcc_set_cmds, \
					ARRAY_SIZE(hw_lcd_scharger_vcc_set_cmds));
	}
#endif
		if (false == gesture_func && !g_debug_enable_lcd_sleep_in) {
			//lcd vcc enable
			if (g_lcd_control_tp_power) {
				vcc_cmds_tx(pdev, hw_lcdanalog_vcc_enable_cmds,
				            ARRAY_SIZE(hw_lcdanalog_vcc_enable_cmds));
			}

			vcc_cmds_tx(pdev, hw_lcdio_vcc_enable_cmds,
						ARRAY_SIZE(hw_lcdio_vcc_enable_cmds));

			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_normal_cmds,
							ARRAY_SIZE(hw_lcd_pinctrl_normal_cmds));

			// lcd gpio request
			gpio_cmds_tx(hw_lcd_gpio_request_cmds, \
						 ARRAY_SIZE(hw_lcd_gpio_request_cmds));

			if (lcd_info.is_need_reset) {
				// lcd gpio normal
				gpio_cmds_tx(hw_lcd_gpio_normal_cmds, \
							 ARRAY_SIZE(hw_lcd_gpio_normal_cmds));
			}

			//vsp/vsn enable
			vcc_cmds_tx(NULL, hw_lcd_scharger_vcc_enable_cmds, \
						ARRAY_SIZE(hw_lcd_scharger_vcc_enable_cmds));

		} else {
			HISI_FB_DEBUG("GESTURE&&PT STATION TEST\n");
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
#ifdef CONFIG_HUAWEI_TS
		if (g_lcd_control_tp_power) {
			error = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts resume device err\n");
		}
#endif
		/*after LP11 delay 12ms*/
		mdelay(12);

		// lcd gpio normal
		gpio_cmds_tx(hw_lcd_gpio_normal_cmds, \
					 ARRAY_SIZE(hw_lcd_gpio_normal_cmds));

#if HW_LCD_DEBUG
		if(is_enable_initcode_debug()) {
			mipi_dsi_cmds_tx(g_panel_cmds.cmds, \
			                g_panel_cmds.cmd_cnt, mipi_dsi0_base);
		} else
#endif
		mipi_dsi_cmds_tx(lcd_info.display_on_cmds.cmd_set, \
		                lcd_info.display_on_cmds.cmd_cnt, mipi_dsi0_base);

		lcd_info.cabc_mode = CABC_UI_MODE;

#if HW_LCD_POWER_STATUS_CHECK
		// check lcd power state
		if (lcd_info.read_power_status) {
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
			HISI_FB_INFO("Read LCD panel status, 0x0A = 0x%x.\n", status);
		}
#endif
		HISI_FB_INFO("lcd name = %s.\n", lcd_info.panel_name);

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
#ifdef CONFIG_HUAWEI_TS
		if (g_lcd_control_tp_power) {
			error = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts after resume err\n");
		}
#endif
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}


/*
*name:hw_lcd_off
*function:power off panel
*@pdev:platform device
*/
static int hw_lcd_off(struct platform_device* pdev)
{
	struct hisi_fb_data_type* hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int error = 0;

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

		// backlight off
		hisi_lcd_backlight_off(pdev);

		// lcd display off sequence
		mipi_dsi_cmds_tx(lcd_info.display_off_cmds.cmd_set, \
		                 lcd_info.display_off_cmds.cmd_cnt, hisifd->mipi_dsi0_base);
		pinfo->lcd_uninit_step = LCD_UNINIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_uninit_step = LCD_UNINIT_POWER_OFF;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_POWER_OFF) {
		if (((false == gesture_func) || hisifd->fb_shutdown) && !g_debug_enable_lcd_sleep_in) {

			//vsp/vsn disable
			vcc_cmds_tx(NULL, hw_lcd_scharger_vcc_disable_cmds, \
			            ARRAY_SIZE(hw_lcd_scharger_vcc_disable_cmds));

			// lcd gpio lowpower
			gpio_cmds_tx(hw_lcd_gpio_lowpower_cmds, \
			             ARRAY_SIZE(hw_lcd_gpio_lowpower_cmds));

			// lcd gpio free
			gpio_cmds_tx(hw_lcd_gpio_free_cmds, \
			             ARRAY_SIZE(hw_lcd_gpio_free_cmds));

			// lcd pinctrl lowpower
			pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_lowpower_cmds,
			                ARRAY_SIZE(hw_lcd_pinctrl_lowpower_cmds));

			mdelay(3);

			//lcd vcc disable
			vcc_cmds_tx(pdev, hw_lcdio_vcc_disable_cmds,
					ARRAY_SIZE(hw_lcdio_vcc_disable_cmds));

			if (g_lcd_control_tp_power) {
				vcc_cmds_tx(pdev, hw_lcdanalog_vcc_disable_cmds,
				            ARRAY_SIZE(hw_lcdanalog_vcc_disable_cmds));
			}

		} else {

			// lcd gpio lowpower
			gpio_cmds_tx(hw_lcd_gpio_lowpower_cmds, \
			             ARRAY_SIZE(hw_lcd_gpio_lowpower_cmds));

			// lcd gpio free
			gpio_cmds_tx(hw_lcd_gpio_free_cmds, \
			             ARRAY_SIZE(hw_lcd_gpio_free_cmds));

			// lcd pinctrl lowpower
			pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_lowpower_cmds,
			                ARRAY_SIZE(hw_lcd_pinctrl_lowpower_cmds));
		}
#ifdef CONFIG_HUAWEI_TS
		//if g_debug_enable_lcd_sleep_in == 1, it means don't turn off TP/LCD power
		//but only let lcd get into sleep.
		if (g_lcd_control_tp_power && !hisifd->fb_shutdown) {
			error = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts before suspend err\n");

			error = ts_power_control_notify(TS_SUSPEND_DEVICE, NO_SYNC_TIMEOUT);
			if (error)
				HISI_FB_ERR("ts suspend device err\n");
		}

		if (lcd_info.is_need_delay) {
			mdelay(200);
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


/*
*name:hw_lcd_remove
*function:panel remove
*@pdev:platform device
*/
static int hw_lcd_remove(struct platform_device* pdev)
{
	struct hisi_fb_data_type* hisifd = NULL;

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
	vcc_cmds_tx(pdev, hw_lcd_vcc_finit_cmds,
	            ARRAY_SIZE(hw_lcd_vcc_finit_cmds));

	// scharger vcc finit
	vcc_cmds_tx(pdev, hw_lcd_scharger_vcc_put_cmds,
	            ARRAY_SIZE(hw_lcd_scharger_vcc_put_cmds));

	// lcd pinctrl finit
	pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_finit_cmds,
	                ARRAY_SIZE(hw_lcd_pinctrl_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

/*
*name:hw_lcd_set_backlight
*function:set backlight level
*@pdev:platform device
*/
static int hw_lcd_set_backlight(struct platform_device* pdev, uint32_t bl_level)
{
	int ret = 0;
	char __iomem* mipi_dsi0_base = NULL;
	struct hisi_fb_data_type* hisifd = NULL;
	static char last_bl_level = 255;
	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc lcd_bl_level_adjust[] = {
		{
			DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust
		},
	};

	char unlock_payload[3] = {
		0x99,
		0x95, 0x27
	};

	struct dsi_cmd_desc unlock_cmd[] = {
		{
			DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(unlock_payload), unlock_payload
		},
	};

	char lock_payload[3] = {
		0x99,
		0x00, 0x00
	};

	struct dsi_cmd_desc lock_cmd[] = {
		{
			DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lock_payload), lock_payload
		},
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

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (unlikely(g_debug_enable)) {
		HISI_FB_INFO("Set backlight to %d. (remain times of backlight print: %d)\n", hisifd->bl_level, g_debug_enable);
		if (g_debug_enable == BACKLIGHT_PRINT_TIMES)
			LOG_JANK_D(JLID_KERNEL_LCD_BACKLIGHT_ON, "JL_KERNEL_LCD_BACKLIGHT_ON,%u", hisifd->bl_level);

		g_debug_enable = (g_debug_enable > 0) ? (g_debug_enable - 1) : 0;
	}

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

		bl_level = (bl_level < hisifd->panel_info.bl_max) ? bl_level : hisifd->panel_info.bl_max;
		bl_level_adjust[1] = bl_level  * 255 / hisifd->panel_info.bl_max;
		/*unlock command one*/
		if (lcd_info.lock_cmd_support) {
			mipi_dsi_cmds_tx(unlock_cmd, \
				ARRAY_SIZE(unlock_cmd), mipi_dsi0_base);
		}
		/*set bl command*/
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
			ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
		/*lock command one*/
		if (lcd_info.lock_cmd_support) {
			mipi_dsi_cmds_tx(lock_cmd, \
				ARRAY_SIZE(lock_cmd), mipi_dsi0_base);
		}
		/*enable/disable backlight*/
		down(&lcd_info.bl_sem);
		if (bl_level == 0 && last_bl_level != 0) {
			vcc_cmds_tx(NULL, hw_lcd_scharger_bl_disable_cmds, \
					ARRAY_SIZE(hw_lcd_scharger_bl_disable_cmds));
		} else if (last_bl_level == 0 && bl_level != 0) {
			vcc_cmds_tx(NULL, hw_lcd_scharger_bl_enable_cmds, \
					ARRAY_SIZE(hw_lcd_scharger_bl_enable_cmds));
		}
		last_bl_level = bl_level;
		up(&lcd_info.bl_sem);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
		            hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

/*
*name:hw_lcd_set_fastboot
*function:set fastboot display
*@pdev:platform device
*/
static int hw_lcd_set_fastboot(struct platform_device* pdev)
{
	struct hisi_fb_data_type* hisifd = NULL;

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

	/*set scharger vcc*/
	vcc_cmds_tx(NULL, hw_lcd_scharger_vcc_set_cmds, \
	            ARRAY_SIZE(hw_lcd_scharger_vcc_set_cmds));

	/*scharger vcc enable*/
	vcc_cmds_tx(NULL, hw_lcd_scharger_vcc_enable_cmds, \
	            ARRAY_SIZE(hw_lcd_scharger_vcc_enable_cmds));

	/*scharger bl enable*/
	vcc_cmds_tx(NULL, hw_lcd_scharger_bl_enable_cmds, \
	            ARRAY_SIZE(hw_lcd_scharger_bl_enable_cmds));

	// lcd pinctrl normal
	pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_normal_cmds,
	                ARRAY_SIZE(hw_lcd_pinctrl_normal_cmds));

	// lcd gpio request
	gpio_cmds_tx(hw_lcd_gpio_request_cmds,
	             ARRAY_SIZE(hw_lcd_gpio_request_cmds));

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

/******************************************************************************/
static ssize_t hw_lcd_model_show(struct platform_device* pdev,
                                 char* buf)
{
	struct hisi_fb_data_type* hisifd = NULL;
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

	ret = snprintf(buf, PAGE_SIZE, "%s\n", lcd_info.panel_name);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t hw_lcd_cabc_mode_show(struct platform_device* pdev,
                                     char* buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", lcd_info.cabc_mode);
}

static ssize_t hw_lcd_cabc_mode_store(struct platform_device* pdev,
                                      const char* buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int mode = -1;
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

	mode = (int)val;
	if (mode == CABC_OFF ) {
			  lcd_info.cabc_mode = CABC_OFF;
			  mipi_dsi_cmds_tx(lcd_info.cabc_off_cmds.cmd_set, \
							   lcd_info.cabc_off_cmds.cmd_cnt,\
							   mipi_dsi0_base);
	}else  if (mode == CABC_UI_MODE) {
			  lcd_info.cabc_mode = CABC_UI_MODE;
			  mipi_dsi_cmds_tx(lcd_info.cabc_ui_cmds.cmd_set, \
							   lcd_info.cabc_ui_cmds.cmd_cnt,\
							   mipi_dsi0_base);
	} else if (mode == CABC_STILL_MODE ) {
			  lcd_info.cabc_mode = CABC_STILL_MODE;
			  mipi_dsi_cmds_tx(lcd_info.cabc_still_cmds.cmd_set, \
							   lcd_info.cabc_still_cmds.cmd_cnt,\
							   mipi_dsi0_base);
	}else if (mode == CABC_MOVING_MODE ) {
			  lcd_info.cabc_mode = CABC_MOVING_MODE;
			  mipi_dsi_cmds_tx(lcd_info.cabc_moving_cmds.cmd_set, \
							   lcd_info.cabc_moving_cmds.cmd_cnt,\
							   mipi_dsi0_base);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}



static ssize_t hw_lcd_inversion_store(struct platform_device* pdev,
                                      const char* buf, size_t count)
{
	ssize_t ret = 0;
	unsigned long val = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	struct device_node* np = NULL;
	static int para_parse_flag = 0;
	char __iomem *ldi_base = NULL;

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

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	lcd_info.inversion_mode = (int)val;

	if (!para_parse_flag) {
		para_parse_flag = 1;
		np = of_find_compatible_node(NULL, NULL, lcd_info.lcd_type);
		if (!np) {
			HISI_FB_ERR("NOT FOUND device node %s!\n", lcd_info.lcd_type);
			ret = -1;
			return ret;
		}

		/*Parse mipi tr dot inversion cmds*/
		ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-dot-inversion", &lcd_info.dot_inversion_cmds);
		if (ret) {
			HISI_FB_ERR("parse hisilicon,dss-dot-inversion failed!\n");
			ret = -1;
			return ret;
		}

		/*Parse mipi tr column inversion cmds*/
		ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-column-inversion", &lcd_info.column_inversion_cmds);
		if (ret) {
			HISI_FB_ERR("parse hisilicon,dss-column-inversion failed!\n");
			ret = -1;
			return ret;
		}
	}

	//switch to low-power mode
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 14);
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 9);
	} else {
		set_reg(mipi_dsi0_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x1, 1, 15);
	}

	//switch dot and column inversion
	if (lcd_info.inversion_mode == INVERSION_COLUMN ) {
		mipi_dsi_cmds_tx(lcd_info.column_inversion_cmds.cmd_set, \
		                 lcd_info.column_inversion_cmds.cmd_cnt, mipi_dsi0_base);
	} else  if (lcd_info.inversion_mode == INVERSION_DOT) {
		mipi_dsi_cmds_tx(lcd_info.dot_inversion_cmds.cmd_set, \
		                 lcd_info.dot_inversion_cmds.cmd_cnt, mipi_dsi0_base);
	}

	//switch to high-speed mode
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 14);
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 9);
	} else {
		set_reg(mipi_dsi0_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x0, 1, 15);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t hw_lcd_inversion_show(struct platform_device* pdev, char* buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", lcd_info.inversion_mode);
}

static ssize_t hw_lcd_scan_store(struct platform_device* pdev,
                                      const char* buf, size_t count)
{
	ssize_t ret = 0;
	unsigned long val = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	struct device_node* np = NULL;
	static int para_parse_flag = 0;
	char __iomem *ldi_base = NULL;

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

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	lcd_info.scan_mode = (int)val;

	if (!para_parse_flag) {
		para_parse_flag = 1;
		np = of_find_compatible_node(NULL, NULL, lcd_info.lcd_type);
		if (!np) {
			HISI_FB_ERR("NOT FOUND device node %s!\n", lcd_info.lcd_type);
			ret = -1;
			return ret;
		}

		/*Parse mipi tr revert scan cmds*/
		ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-revert-scan", &lcd_info.revert_scan_cmds);
		if (ret) {
			HISI_FB_ERR("parse hisilicon,dss-revert-scan failed!\n");
			ret = -1;
			return ret;
		}

		/*Parse mipi tr forword scan cmds*/
		ret = hw_lcd_parse_dcs_cmds(np, "hisilicon,dss-forword-scan", &lcd_info.forword_scan_cmds);
		if (ret) {
			HISI_FB_ERR("parse hisilicon,dss-forword-scan failed!\n");
			ret = -1;
			return ret;
		}
	}

	//switch to low-power mode
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 14);
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 9);
	} else {
		set_reg(mipi_dsi0_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x1, 1, 15);
	}

	//switch revert and scan mode
	if (lcd_info.scan_mode == SCAN_TYPE_FORWORD) {
		mipi_dsi_cmds_tx(lcd_info.forword_scan_cmds.cmd_set, \
		                 lcd_info.forword_scan_cmds.cmd_cnt, mipi_dsi0_base);
	} else  if (lcd_info.scan_mode == SCAN_TYPE_REVERT) {
		mipi_dsi_cmds_tx(lcd_info.revert_scan_cmds.cmd_set, \
		                 lcd_info.revert_scan_cmds.cmd_cnt, mipi_dsi0_base);
	}

	//switch to high-speed mode
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 14);
		set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 9);
	} else {
		set_reg(mipi_dsi0_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x0, 1, 15);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t hw_lcd_scan_show(struct platform_device* pdev, char* buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", lcd_info.scan_mode);
}


static ssize_t hw_lcd_check_reg_show(struct platform_device* pdev, char* buf)
{
	int ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	uint32_t read_value = 0, expect_value = 0;
	uint32_t i = 0;
	char lcd_reg[] = {0x00};
	char* reg_ptr = NULL, *expect_ptr = NULL;


	struct dsi_cmd_desc lcd_check_reg[] = {
		{
			DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg), lcd_reg
		}
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

	if (is_mipi_cmd_panel(hisifd)) {
		lcd_check_reg[0].dtype = DTYPE_DCS_READ;
	} else {
		lcd_check_reg[0].dtype = DTYPE_GEN_READ1;
	}

	reg_ptr = lcd_info.mipi_check_reg.buf;
	expect_ptr = lcd_info.mipi_check_value.buf;
	for (i = 0; i < lcd_info.mipi_check_reg.cnt; i++) {
		lcd_check_reg[0].payload = reg_ptr++;
		ret = mipi_dsi_cmds_rx(&read_value, lcd_check_reg, sizeof(lcd_reg), mipi_dsi0_base);
		if (ret) {
			HISI_FB_ERR("Read error number: %d\n", ret);
			break;
		}
		expect_value = *expect_ptr++;
		if (read_value != expect_value) {
			HISI_FB_ERR("Read reg does not match expect value,read value: %d, expect value:%d\n", read_value, expect_value);
			ret = 1;
			break;
		} else {
			HISI_FB_DEBUG("Read success, read value: %d, expect value:%d\n", read_value, expect_value);
		}
	}
	if (!ret) {
		ret = snprintf(buf, PAGE_SIZE, "OK\n");
	} else {
		ret = snprintf(buf, PAGE_SIZE, "ERROR\n");
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t hw_lcd_mipi_detect_show(struct platform_device* pdev, char* buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	uint32_t read_value[2] = {0};
	uint32_t expected_value[2] = {0x80, 0x00};
	uint32_t read_mask[2] = {0xFF, 0xFF};
	char* reg_name[2] = {"signal mode", "dsi error number"};
	char lcd_reg_0e[] = {0x0e};
	char lcd_reg_05[] = {0x05};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{
			DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_0e), lcd_reg_0e
		},
		{
			DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg_05), lcd_reg_05
		},
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

static ssize_t hw_lcd_hkadc_debug_show(struct platform_device* pdev, char* buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;

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
	ret = snprintf(buf, PAGE_SIZE, "%d\n", hkadc_buf * 4);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t hw_lcd_hkadc_debug_store(struct platform_device* pdev,
                                        const char* buf, size_t count)
{
	int ret = 0;
	int channel = 0;
	struct hisi_fb_data_type* hisifd = NULL;

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

	ret = sscanf(buf, "%u", &channel);
	if (ret <= 0) {
		HISI_FB_ERR("Sscanf return invalid, ret = %d\n", ret);
		return count;
	}

	hkadc_buf = hisi_adc_get_value(channel);
	HISI_FB_INFO("channel[%d] value is %d\n", channel, hkadc_buf);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t hw_lcd_gram_check_show(struct platform_device* pdev, char* buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	uint32_t rd[CHECKSUM_SIZE] = {0};
	int i = 0;
	char cmdF_page0_select[] = {0xFF, 0xF0};
	char cmd1_page0_select[] = {0xFF, 0x10};
	char checksum_read[] = {0x73};

	struct dsi_cmd_desc packet_size_set_cmd = {DTYPE_MAX_PKTSIZE, 0, 10, WAIT_TYPE_US, 1, NULL};

	struct dsi_cmd_desc lcd_checksum_select_cmds[] = {
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select
		},
	};

	struct dsi_cmd_desc lcd_checksum_dis_select_cmds[] = {
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select
		},
	};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{
			DTYPE_DCS_READ, 0, 20, WAIT_TYPE_US,
			sizeof(checksum_read), checksum_read
		},
	};

	if (!checksum_enable_ctl) {
		HISI_FB_INFO("Checksum disabled\n");
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

	if (NULL == hisifd->mipi_dsi0_base) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	mipi_dsi_max_return_packet_size(&packet_size_set_cmd, mipi_dsi0_base);

	mipi_dsi_cmds_tx(lcd_checksum_select_cmds, \
	                 ARRAY_SIZE(lcd_checksum_select_cmds), mipi_dsi0_base);
	for (i = 0; i < CHECKSUM_SIZE; i++) {
		char* data = lcd_check_reg[0].payload;
		*data = 0x73 + i;
		mipi_dsi_cmds_rx((rd + i), lcd_check_reg, \
		                 ARRAY_SIZE(lcd_check_reg), mipi_dsi0_base);
	}

	ret = snprintf(buf, PAGE_SIZE, "%d %d %d %d %d %d %d %d\n", \
	               rd[0], rd[1], rd[2], rd[3], rd[4], rd[5], rd[6], rd[7]);
	HISI_FB_INFO("%d %d %d %d %d %d %d %d\n", \
	             rd[0], rd[1], rd[2], rd[3], rd[4], rd[5], rd[6], rd[7]);

	mipi_dsi_cmds_tx(lcd_checksum_dis_select_cmds, \
	                 ARRAY_SIZE(lcd_checksum_dis_select_cmds), mipi_dsi0_base);

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t hw_lcd_gram_check_store(struct platform_device* pdev,
                                       const char* buf, size_t count)
{
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	char cmdF_page0_select[] = {0xFF, 0xF0};
	char checksum_init[] = {0x7B, 0x00};
	char checksum_ena[] = {0x92, 0x01};
	char checksum_dis[] = {0x92, 0x00};
	char cmd1_page0_select[] = {0xFF, 0x10};

	struct dsi_cmd_desc lcd_checksum_enable_cmds[] = {
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select
		},
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_init), checksum_init
		},
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_ena), checksum_ena
		},
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select
		},
	};

	struct dsi_cmd_desc lcd_checksum_disable_cmds[] = {
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmdF_page0_select), cmdF_page0_select
		},
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(checksum_dis), checksum_dis
		},
		{
			DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
			sizeof(cmd1_page0_select), cmd1_page0_select
		},
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

	if ((!*buf) || (!strchr("yY1nN0", *buf))) {
		HISI_FB_ERR("Input param is error(valid: yY1nN0): %s. \n", buf);
		return -EINVAL;
	}

	checksum_enable_ctl = !!strchr("yY1", *buf);
	if (checksum_enable_ctl == true) {
		mipi_dsi_cmds_tx(lcd_checksum_enable_cmds, \
		                 ARRAY_SIZE(lcd_checksum_enable_cmds), mipi_dsi0_base);
		HISI_FB_INFO("Enable checksum\n");
	} else {
		mipi_dsi_cmds_tx(lcd_checksum_disable_cmds, \
		                 ARRAY_SIZE(lcd_checksum_disable_cmds), mipi_dsi0_base);
		HISI_FB_INFO("Disable checksum\n");
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static int hw_lcd_set_display_region(struct platform_device* pdev,
                                     struct dss_rect* dirty)
{
	struct hisi_fb_data_type* hisifd = NULL;

	char unlock_payload[3] = {0x99, 0x95, 0x27};
	struct dsi_cmd_desc unlock_cmd[] = {
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(unlock_payload), unlock_payload},
	};
	char lock_payload[3] = {0x99, 0x00, 0x00};
	struct dsi_cmd_desc lock_cmd[] = {
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lock_payload), lock_payload},
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

	lcd_disp_x[1] = (dirty->x >> 8) & 0xff;
	lcd_disp_x[2] = dirty->x & 0xff;
	lcd_disp_x[3] = ((dirty->x + dirty->w - 1) >> 8) & 0xff;
	lcd_disp_x[4] = (dirty->x + dirty->w - 1) & 0xff;
	lcd_disp_y[1] = (dirty->y >> 8) & 0xff;
	lcd_disp_y[2] = dirty->y & 0xff;
	lcd_disp_y[3] = ((dirty->y + dirty->h - 1) >> 8) & 0xff;
	lcd_disp_y[4] = (dirty->y + dirty->h - 1) & 0xff;

	if (lcd_info.lock_cmd_support) {
		mipi_dsi_cmds_tx(unlock_cmd, ARRAY_SIZE(unlock_cmd), hisifd->mipi_dsi0_base);
	}
	mipi_dsi_cmds_tx(set_display_address, \
	                 ARRAY_SIZE(set_display_address), hisifd->mipi_dsi0_base);
	if (lcd_info.lock_cmd_support) {
		mipi_dsi_cmds_tx(lock_cmd, ARRAY_SIZE(lock_cmd), hisifd->mipi_dsi0_base);
	}
	return 0;
}


static ssize_t hw_lcd_sleep_ctrl_show(struct platform_device* pdev, char* buf)
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

static ssize_t hw_lcd_sleep_ctrl_store(struct platform_device* pdev,
                                      const char* buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
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

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	if (hisifd->panel_info.lcd_adjust_support) {
		g_debug_enable_lcd_sleep_in = val;
	}

	if (g_debug_enable_lcd_sleep_in == 2) {
		HISI_FB_DEBUG("Both LCD  and Touch goto sleep\n");
		g_tp_power_ctrl = 1;	//used for pt  current test, tp sleep
	} else {
		HISI_FB_DEBUG("g_debug_enable_lcd_sleep_in is %d\n", g_debug_enable_lcd_sleep_in);
		g_tp_power_ctrl = 0;	//used for pt  current test, tp power off
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

#if HW_LCD_DEBUG
static int hw_lcd_esd_debug(struct hisi_fb_data_type* hisifd)
{
	int ret = 0;
	uint32_t i = 0;
	uint32_t read_value = 0;
	char lcd_reg[] = {0x00};
	char bl_enable[2] = {
		0x53,
		0x24,
	};

	struct dsi_cmd_desc lcd_bl_enable[] = {
		{
			DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_enable), bl_enable
		},
	};

	struct dsi_cmd_desc lcd_check_reg[] = {
		{
			DTYPE_GEN_READ1, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg), lcd_reg
		}
	};

	if (is_mipi_cmd_panel(hisifd)) {
		lcd_check_reg[0].dtype = DTYPE_DCS_READ;
	} else {
		lcd_check_reg[0].dtype = DTYPE_GEN_READ1;
	}

	/*check reg, read reg and compire the expect value*/
	for (i = 0; i < g_esd_debug.check_count; i++) {
		lcd_check_reg[0].payload = &g_esd_debug.esd_check_reg[i];
		ret = mipi_dsi_cmds_rx(&read_value, lcd_check_reg, sizeof(lcd_reg), hisifd->mipi_dsi0_base);
		if (ret) {
			HISI_FB_ERR("Read error number: %d\n", ret);
			ret = 0;
			continue;
		}

		if (g_esd_debug.esd_check_reg[i] == 0x0e) {
			if (read_value&0x80) {
				HISI_FB_DEBUG("Esd debug:Read reg:0x0e success, read value: %d\n", read_value);
			} else {
				HISI_FB_ERR("Esd debug:Read reg:0x0e failed, read value: %d\n", read_value);
				ret = 1;
				break;
			}
		} else {
			if (read_value != g_esd_debug.esd_reg_value[i]) {
				HISI_FB_ERR("Esd debug:Read reg 0x%x does not match expect value,read value: 0x%x, expect value:0x%x\n", g_esd_debug.esd_check_reg[i], read_value, g_esd_debug.esd_reg_value[i]);
				ret = 1;
				break;
			} else {
				HISI_FB_DEBUG("Esd debug:Read 0x%x success, read value: 0x%x, expect value:0x%x\n", g_esd_debug.esd_check_reg[i], read_value, g_esd_debug.esd_reg_value[i]);
			}
		}
	}

	/*set backlight per 5s*/
	if (g_esd_debug.esd_bl_set) {
		hw_lcd_set_backlight(hisifd->pdev, hisifd->bl_level);
	}

	/*set bl enable per 5s*/
	if (g_esd_debug.esd_bl_enable) {
		mipi_dsi_cmds_tx(lcd_bl_enable, \
		                 ARRAY_SIZE(lcd_bl_enable), hisifd->mipi_dsi0_base);
	}

	return ret;
}
#endif

static int hw_lcd_check_esd(struct platform_device* pdev)
{
	int ret = 0;
	struct hisi_fb_data_type* hisifd = NULL;
	char __iomem* mipi_dsi0_base = NULL;
	uint32_t read_value = 0, expect_value = 0;
	uint32_t i = 0;
	char lcd_reg[] = {0x00};
	char* reg_ptr = NULL, *expect_ptr = NULL;
	struct dsi_cmd_desc lcd_check_reg[] = {
		{
			DTYPE_DCS_READ, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_reg), lcd_reg
		}
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

	/*esd debug*/
#if HW_LCD_DEBUG
	if (g_esd_debug.esd_enable == 1) {
		ret = hw_lcd_esd_debug(hisifd);
		return ret;
	}

	if (g_esd_debug.esd_recover_test) {
		return -1;
	}
#endif

	if (!lcd_info.esd_reg.buf || !lcd_info.esd_value.buf) {
		HISI_FB_ERR("esd reg or esd value is null\n");
		return -1;
	}

	if (is_mipi_cmd_panel(hisifd)) {
		lcd_check_reg[0].dtype = DTYPE_DCS_READ;
	} else {
		lcd_check_reg[0].dtype = DTYPE_GEN_READ1;
	}

	reg_ptr = lcd_info.esd_reg.buf;
	expect_ptr = lcd_info.esd_value.buf;
	for (i = 0; i < lcd_info.esd_reg.cnt; i++) {
		lcd_check_reg[0].payload = reg_ptr++;
		ret = mipi_dsi_cmds_rx(&read_value, lcd_check_reg, sizeof(lcd_reg), mipi_dsi0_base);
		if (ret) {
			HISI_FB_ERR("Read error number: %d\n", ret);
			ret = 0;
			continue;
		}
		expect_value = *expect_ptr++;
		if (read_value != expect_value) {
			HISI_FB_ERR("Read reg 0x%x does not match expect value,read value: 0x%x, expect value:0x%x\n", lcd_info.esd_reg.buf[i], read_value, expect_value);
			ret = 1;
			break;
		} else {
			HISI_FB_DEBUG("Read reg 0x%x success, read value: 0x%x, expect value:0x%x\n", lcd_info.esd_reg.buf[i], read_value, expect_value);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

/*******************************************************************************
**
*/
static struct hisi_panel_info hw_lcd_info = {0};
static struct hisi_fb_panel_data hw_lcd_data = {
	.panel_info = &hw_lcd_info,
	.set_fastboot = hw_lcd_set_fastboot,
	.on = hw_lcd_on,
	.off = hw_lcd_off,
	.remove = hw_lcd_remove,
	.set_backlight = hw_lcd_set_backlight,
	.lcd_model_show = hw_lcd_model_show,
	.lcd_cabc_mode_show = hw_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = hw_lcd_cabc_mode_store,
	.lcd_check_reg = hw_lcd_check_reg_show,
	.lcd_mipi_detect = hw_lcd_mipi_detect_show,
	.lcd_hkadc_debug_show = hw_lcd_hkadc_debug_show,
	.lcd_hkadc_debug_store = hw_lcd_hkadc_debug_store,
	.lcd_gram_check_show = hw_lcd_gram_check_show,
	.lcd_gram_check_store = hw_lcd_gram_check_store,
	.set_display_region = hw_lcd_set_display_region,
	.set_display_resolution = NULL,
	.lcd_inversion_store = hw_lcd_inversion_store,
	.lcd_inversion_show = hw_lcd_inversion_show,
	.lcd_sleep_ctrl_show = hw_lcd_sleep_ctrl_show,
	.lcd_sleep_ctrl_store = hw_lcd_sleep_ctrl_store,
	.esd_handle = hw_lcd_check_esd,
	.get_lcd_id = hw_lcd_get_id,
};

/*
*name:hw_lcd_probe
*function:panel driver probe
*@pdev:platform device
*/
static int __init hw_lcd_probe(struct platform_device* pdev)
{
	struct hisi_panel_info* pinfo = NULL;
	struct device_node* np = NULL;
	int ret = 0;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;
	uint32_t lcd_ifbc_type = 0;

	HISI_FB_INFO("enter succ!!!!\n");

	np = of_find_compatible_node(NULL, NULL, lcd_info.lcd_type);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", lcd_info.lcd_type);
		ret = -1;
		return ret;
	}

	ret = of_property_read_u32(np, "hisilicon,dss-panel-type", &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_CMD;
	}

	ret = of_property_read_u32(np, "hisilicon,dss-panel-ifbc-type", &lcd_ifbc_type);
	if (ret) {
		HISI_FB_ERR("get ifbc_type failed!\n");
		lcd_ifbc_type = IFBC_TYPE_NONE;
	}

	ret = of_property_read_u32(np, "hisilicon,dss-panel-bl-type", &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}

	/*init sem*/
	sema_init(&lcd_info.bl_sem, 1);

	//gpio_2_4
	gpio_lcd_reset = of_get_named_gpio(np, "gpios", 1);
	/*get id0*/
	lcd_info.lcd_id0 = of_get_named_gpio(np, "gpios", 0);
	/*get id1*/
	lcd_info.lcd_id1 = of_get_named_gpio(np, "gpios", 3);

	pdev->id = 1;
	pinfo = hw_lcd_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	/*Parse panel info*/
	hw_lcd_info_init(np, pinfo);

	/*effect init*/
	hw_lcd_effect_get_data(hw_lcd_get_panel_id(lcd_info.lcd_type), pinfo);

	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}

	/*Parse data from dtsi*/
	ret = hw_lcd_parse_dts(np);
	if (ret) {
		HISI_FB_ERR("parse dtsi failed!\n");
		goto err_probe_defer;
	}

	if(runmode_is_factory()) {
		pinfo->esd_enable = 0;
	}

	/*init bias/vsp/vsn*/
	hw_lcd_vcc_init(hw_lcd_scharger_vcc_set_cmds, ARRAY_SIZE(hw_lcd_scharger_vcc_set_cmds));

	/*init lcdio vcc*/
	hw_lcd_vcc_init(hw_lcdio_vcc_init_cmds, ARRAY_SIZE(hw_lcdio_vcc_init_cmds));
	ret = vcc_cmds_tx(pdev, hw_lcdio_vcc_init_cmds,
	                  ARRAY_SIZE(hw_lcdio_vcc_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("LCD vcc init failed!\n");
		goto err_return;
	}
	/*init lcdanalog vcc*/
	if (g_lcd_control_tp_power) {
		hw_lcd_vcc_init(hw_lcdanalog_vcc_init_cmds, ARRAY_SIZE(hw_lcdanalog_vcc_init_cmds));
		ret = vcc_cmds_tx(pdev, hw_lcdanalog_vcc_init_cmds,
		                  ARRAY_SIZE(hw_lcdanalog_vcc_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("LCD vcc init failed!\n");
			goto err_return;
		}
	}
	hw_lcd_reset_init(hw_lcd_gpio_normal_cmds);

	// lcd pinctrl init
	ret = pinctrl_cmds_tx(pdev, hw_lcd_pinctrl_init_cmds,
	                      ARRAY_SIZE(hw_lcd_pinctrl_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("Init pinctrl failed, defer\n");
		goto err_return;
	}

	/* lcd scharger vcc get*/
	vcc_cmds_tx(pdev, hw_lcd_scharger_vcc_get_cmds, \
	            ARRAY_SIZE(hw_lcd_scharger_vcc_get_cmds));

	// lcd vcc enable
	if (is_fastboot_display_enable()) {
		if (g_lcd_control_tp_power) {
			vcc_cmds_tx(pdev, hw_lcdanalog_vcc_enable_cmds,
			            ARRAY_SIZE(hw_lcdanalog_vcc_enable_cmds));
		}
		vcc_cmds_tx(pdev, hw_lcdio_vcc_enable_cmds,
				ARRAY_SIZE(hw_lcdio_vcc_enable_cmds));
	}
	/*id0 && id1 gpio request*/
	gpio_cmds_tx(hw_lcd_gpio_id_request_cmds, \
				 ARRAY_SIZE(hw_lcd_gpio_id_request_cmds));

	// alloc panel device data
	ret = platform_device_add_data(pdev, &hw_lcd_data,
	                               sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("platform_device_add_data failed!\n");
		goto err_device_put;
	}

	hisi_fb_add_device(pdev);
	HISI_FB_INFO("exit succ!!!!\n");
#if HW_LCD_DEBUG
	lcd_debugfs_init();
#endif
	return 0;

err_device_put:
	platform_device_put(pdev);
err_return:
	return ret;
err_probe_defer:
	return -EPROBE_DEFER;

	return ret;
}

/*
*name:hw_lcd_init
*function:panel init
*/
static int __init hw_lcd_init(void)
{
	int ret = 0, len = 0;
	struct device_node* np = NULL;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_LCD_PANEL_TYPE);
	if (!np) {
		HISI_FB_WARNING("NOT FOUND device node %s!\n", DTS_COMP_LCD_PANEL_TYPE);
		ret = -1;
		return ret;
	}

	memset(&lcd_info, 0, sizeof(struct hw_lcd_information));
	lcd_info.lcd_type = (char*)of_get_property(np, "lcd_panel_type", NULL);
	if (!lcd_info.lcd_type) {
		HISI_FB_INFO("Is not normal lcd and return\n");
		return ret;
	} else {
		len = strlen(lcd_info.lcd_type);
		memset(this_driver.driver.of_match_table->compatible, 0, PANEL_COMP_LENGTH);
		strncpy(this_driver.driver.of_match_table->compatible, lcd_info.lcd_type, (len > PANEL_COMP_LENGTH ? PANEL_COMP_LENGTH : len));
		HISI_FB_INFO("g_lcd_type=%s, len = %d!\n", lcd_info.lcd_type, strlen(lcd_info.lcd_type));
	}
	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}
	return ret;
}

module_init(hw_lcd_init);
