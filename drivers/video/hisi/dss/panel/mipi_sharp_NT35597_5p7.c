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
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#include <huawei_platform/log/log_jank.h>
#include "include/mipi_sharp_NT35597_5p7.h"

static int mipi_lcd_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
		ARRAY_SIZE(lcd_pinctrl_normal_cmds));

	gpio_cmds_tx(lcd_gpio_request_cmds, \
		ARRAY_SIZE(lcd_gpio_request_cmds));

	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lcd_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	int error = 0;
#if defined (CONFIG_HUAWEI_DSM)
	static struct lcd_reg_read_t lcd_status_reg[] = {
		{0x0A, 0x9C, 0xFF, "lcd power state"},
		{0x0E, 0x80, 0xC1, "lcd signal mode"},
		{0x05, 0x00, 0xFF, "mipi dsi error number"},
		{0xDA, 0x00, 0x00, "RDID1"},
		{0x0A, 0x9C, 0xFF, "lcd power state", true},
		{0x0B, 0x00, 0xFF, "lcd address state", true},
		{0x0C, 0x77, 0xFF, "lcd pixedl format", true},
		{0x0D, 0x00, 0xFF, "lcd regsiter 0x0D", true},
		{0x0E, 0x80, 0xC1, "lcd signal mode", true},
		{0x0F, 0xC0, 0xFF, "lcd diagnostic result", true},
		{0x05, 0x00, 0xFF, "mipi dsi error number",true},
	};

	static struct lcd_reg_read_t check_reg_before_11[] = {
		{0x0A, 0x08, 0xFF, "lcd power 0x08 state"},
		{0x0A, 0x08, 0xFF, "lcd power 0x08 state",true},
		{0xAB, 0x00, 0xFF, "mipi_error_report",true},
	};

	static struct lcd_reg_read_t check_reg_between_11_29[] = {
		{0x0A, 0x98, 0xFF, "lcd power 0x98 state"},
		{0x0A, 0x98, 0xFF, "lcd power 0x98 state",true},
		{0xAB, 0x00, 0xFF, "mipi_error_report",true},
	};
#endif

	if (pdev == NULL) {
		return -1;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}

	HISI_FB_INFO("[%s]fb%d, +!\n", DRIVER_NAME,hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		g_debug_enable = BACKLIGHT_PRINT_TIMES;
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_ON, "%s", "JL_KERNEL_LCD_POWER_ON");
		if (!gesture_func && !g_debug_enable_lcd_sleep_in) {
			HISI_FB_INFO("Init power on(regulator enabling).\n");

			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
				ARRAY_SIZE(lcd_vcc_enable_cmds));

			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
				ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			gpio_cmds_tx(lcd_gpio_request_cmds, \
				ARRAY_SIZE(lcd_gpio_request_cmds));

			gpio_cmds_tx(lcd_gpio_normal_cmds_sub1, \
				ARRAY_SIZE(lcd_gpio_normal_cmds_sub1));
		} else {
			HISI_FB_INFO("power on (gesture_func:%d)\n", gesture_func);
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
		/* after LP11 delay 12ms */
		mdelay(12);

		/* IC spec requir LCD reset signal after MIPI come into LP11 */
		gpio_cmds_tx(lcd_gpio_normal_cmds_sub2, \
			ARRAY_SIZE(lcd_gpio_normal_cmds_sub2));
#ifdef CONFIG_HUAWEI_TS
		/* control touch timing */
		if (TP_RS_CALL != g_debug_enable_lcd_sleep_in) {
			HISI_FB_INFO("TP resume and after resume\n");
			error = ts_power_control_notify(TS_RESUME_DEVICE,
						SHORT_SYNC_TIMEOUT);
			if (error) {
				HISI_FB_ERR("ts resume device err\n");
			}
			error = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
			if (error) {
				HISI_FB_ERR("ts resume device err\n");
			}
		}
#endif
		mipi_dsi_cmds_tx(lcd_add_rgb_seq_cmd, \
			ARRAY_SIZE(lcd_add_rgb_seq_cmd), mipi_dsi0_base);

		mipi_dsi_cmds_tx(lcd_display_init_cmd, \
			ARRAY_SIZE(lcd_display_init_cmd), mipi_dsi0_base);

		mipi_dsi_cmds_tx(crc_func_off_cmd, \
			ARRAY_SIZE(crc_func_off_cmd), mipi_dsi0_base);

		if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_DUAL) {
			mipi_dsi_cmds_tx(lcd_ifbc_vesa3x_en_cmd, \
				ARRAY_SIZE(lcd_ifbc_vesa3x_en_cmd), mipi_dsi0_base);
		} else {
			mipi_dsi_cmds_tx(lcd_ifbc_vesa3x_dis_cmd, \
				ARRAY_SIZE(lcd_ifbc_vesa3x_dis_cmd), mipi_dsi0_base);
		}

		if (pinfo->panel_effect_support) {
			mipi_dsi_cmds_tx(lcd_display_effect_on_cmd, \
				ARRAY_SIZE(lcd_display_effect_on_cmd), mipi_dsi0_base);
		}

#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(check_reg_before_11, \
			ARRAY_SIZE(check_reg_before_11), mipi_dsi0_base);
#endif

		mipi_dsi_cmds_tx(lcd_display_on_cmd, \
			ARRAY_SIZE(lcd_display_on_cmd), mipi_dsi0_base);

#if defined (CONFIG_HUAWEI_DSM)
		panel_check_status_and_report_by_dsm(check_reg_between_11_29, \
			ARRAY_SIZE(check_reg_between_11_29), mipi_dsi0_base);
#endif

		mipi_dsi_cmds_tx(lcd_display_on_29_cmd, \
			ARRAY_SIZE(lcd_display_on_29_cmd), mipi_dsi0_base);

		if ((pinfo->bl_set_type & BL_SET_BY_BLPWM)
			|| (pinfo->bl_set_type & BL_SET_BY_SH_BLPWM)) {
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
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("[%s]fb%d, -!\n", DRIVER_NAME,hisifd->index);

	return 0;
}

static int mipi_lcd_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int error = 0;

	if (pdev == NULL) {
		return -1;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}

	HISI_FB_INFO("[%s]fb%d, +!\n", DRIVER_NAME,hisifd->index);

	pinfo = &(hisifd->panel_info);

	if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_HS_SEND_SEQUENCE) {
		LOG_JANK_D(JLID_KERNEL_LCD_POWER_OFF, "%s", "JL_KERNEL_LCD_POWER_OFF");

		hisi_lcd_backlight_off(pdev);

		mipi_dsi_cmds_tx(lcd_display_off_cmd, \
			ARRAY_SIZE(lcd_display_off_cmd), hisifd->mipi_dsi0_base);

		pinfo->lcd_uninit_step = LCD_UNINIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_MIPI_LP_SEND_SEQUENCE) {
		pinfo->lcd_uninit_step = LCD_UNINIT_POWER_OFF;
	} else if (pinfo->lcd_uninit_step == LCD_UNINIT_POWER_OFF) {
		if (!hisifd->fb_shutdown) {
			if (!gesture_func && !g_debug_enable_lcd_sleep_in) {
				HISI_FB_INFO("display off(regulator disabling).\n");

				gpio_cmds_tx(lcd_gpio_lowpower_cmds, \
					ARRAY_SIZE(lcd_gpio_lowpower_cmds));

				gpio_cmds_tx(lcd_gpio_free_cmds, \
					ARRAY_SIZE(lcd_gpio_free_cmds));

				pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
					ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

				vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
					ARRAY_SIZE(lcd_vcc_disable_cmds));
			} else {
				HISI_FB_INFO("display_off (gesture_func:%d)\n", gesture_func);

				gpio_cmds_tx(lcd_gpio_sleep_free_cmds, \
					ARRAY_SIZE(lcd_gpio_sleep_free_cmds));

				pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
					ARRAY_SIZE(lcd_pinctrl_normal_cmds));
		}

#ifdef CONFIG_HUAWEI_TS
			/*if g_debug_enable_lcd_sleep_in == 1,
			**it means don't turn off TP/LCD power
			**but only let lcd get into sleep.
			*/
			if (TP_RS_CALL != g_debug_enable_lcd_sleep_in) {
				HISI_FB_INFO("TP before suspend and suspend\n");
				error = ts_power_control_notify(TS_BEFORE_SUSPEND,
							SHORT_SYNC_TIMEOUT);
				if (error) {
					HISI_FB_ERR("ts before suspend err\n");
				}
				error = ts_power_control_notify(TS_SUSPEND_DEVICE,
					SHORT_SYNC_TIMEOUT);
				if (error) {
					HISI_FB_ERR("ts suspend device err\n");
				}
			}
#endif
			/* Delay 200ms to make sure 1.8V completely to 0 */
			mdelay(200);
		}else {
			HISI_FB_INFO("display shutting down(regulator disabling).\n");

			gpio_cmds_tx(lcd_gpio_lowpower_cmds, \
				ARRAY_SIZE(lcd_gpio_lowpower_cmds));

			gpio_cmds_tx(lcd_gpio_free_cmds, \
				ARRAY_SIZE(lcd_gpio_free_cmds));

			pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
				ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

			vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
				ARRAY_SIZE(lcd_vcc_disable_cmds));

			/* delay 200ms to make sure 1.8V completely to 0 */
			mdelay(200);

#ifdef CONFIG_HUAWEI_TS
			ts_thread_stop_notify();
#endif
		}

	} else {
		HISI_FB_ERR("failed to uninit lcd!\n");
	}

	HISI_FB_INFO("[%s]fb%d, -!\n", DRIVER_NAME,hisifd->index);

	return 0;
}

static ssize_t mipi_lcd_panel_gram_check_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t rd[CHECKSUM_SIZE] = {0};
	int i = 0;
	char cmdF_page0_select[] = {0xFF, 0xF0};
	char cmd1_page0_select[] = {0xFF, 0x10};
	char checksum_read[] = {0x73};

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

static ssize_t mipi_lcd_panel_gram_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
/*
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

	if ((!*buf) ||(!strchr("yY1nN0", *buf))) {
		HISI_FB_ERR("Input param is error(valid: yY1nN0): %s. \n",buf);
		return -EINVAL;
	}

	checksum_enable_ctl = !!strchr("yY1", *buf);
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
*/
	return count;
}

static int mipi_lcd_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	vcc_cmds_tx(pdev, lcd_vcc_finit_cmds,
		ARRAY_SIZE(lcd_vcc_finit_cmds));

	pinctrl_cmds_tx(pdev, lcd_pinctrl_finit_cmds,
		ARRAY_SIZE(lcd_pinctrl_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lcd_panel_set_backlight(struct platform_device *pdev,
	uint32_t bl_level)
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

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (unlikely(g_debug_enable)) {
		HISI_FB_INFO("Set backlight to %d. (remain times of backlight print: %d)\n",
			hisifd->bl_level, g_debug_enable);

		if (g_debug_enable == BACKLIGHT_PRINT_TIMES) {
			LOG_JANK_D(JLID_KERNEL_LCD_BACKLIGHT_ON,
			"JL_KERNEL_LCD_BACKLIGHT_ON,%u", hisifd->bl_level);
		}

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
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
			ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
			hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "sharp_NT35597_WQHD 5.7' CMD TFT\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_cabc_mode_show(struct platform_device *pdev,
	char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", g_cabc_mode);
}

static ssize_t mipi_lcd_panel_cabc_mode_store(struct platform_device *pdev,
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

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
		return ret;

	flag = (int)val;

	if (flag < CABC_OFF || flag > CABC_MOVING_MODE)
		return -EINVAL;

	if (flag == CABC_OFF){
		g_cabc_mode=0;
		mipi_dsi_cmds_tx(lcd_cabc_off_cmds, \
			ARRAY_SIZE(lcd_cabc_off_cmds),\
			mipi_dsi0_base);
	}else if (flag == CABC_UI_MODE) {
		g_cabc_mode=1;
		mipi_dsi_cmds_tx(lcd_cabc_still_on_cmds, \
			ARRAY_SIZE(lcd_cabc_still_on_cmds),\
			mipi_dsi0_base);
	} else if (flag == CABC_STILL_MODE ) {
		g_cabc_mode=2;
		mipi_dsi_cmds_tx(lcd_cabc_ui_on_cmds, \
			ARRAY_SIZE(lcd_cabc_ui_on_cmds),\
			mipi_dsi0_base);
	} else if (flag == CABC_MOVING_MODE ){
		g_cabc_mode=3;
		mipi_dsi_cmds_tx(lcd_cabc_moving_on_cmds, \
			ARRAY_SIZE(lcd_cabc_moving_on_cmds),\
			mipi_dsi0_base);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, count, "%d\n", g_cabc_mode);
}

static ssize_t mipi_lcd_panel_check_reg_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t read_value[4] = {0};
	uint32_t expected_value[4] = {0x9c, 0x00, 0x77, 0x00};
	uint32_t read_mask[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	char* reg_name[4] = {
		"power mode",
		"MADCTR",
		"pixel format",
		"image mode"
	};
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

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (!mipi_dsi_read_compare(&data, mipi_dsi0_base)) {
		ret = snprintf(buf, PAGE_SIZE, "P-0x0a:0x%x, 0x0b:0x%x, 0x0c:0x%x, 0x0d:0x%x\n",
			data.read_value[0], data.read_value[1], data.read_value[2], data.read_value[3]);
	} else {
		ret = snprintf(buf, PAGE_SIZE, "F-0x0a:0x%x, 0x0b:0x%x, 0x0c:0x%x, 0x0d:0x%x\n",
			data.read_value[0], data.read_value[1], data.read_value[2], data.read_value[3]);
	}
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_mipi_detect_show(struct platform_device *pdev,
	char *buf)
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

static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00, 0x04, 0x37,
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00, 0x07, 0x7F,
};

static struct dsi_cmd_desc set_display_address[] = {
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x},
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y},
};

static int mipi_lcd_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	if (((dirty->x % pinfo->dirty_region_info.left_align) != 0)
		|| (dirty->w < pinfo->dirty_region_info.w_min)
		|| ((dirty->w % pinfo->dirty_region_info.w_align) != 0)
		|| ((dirty->y % pinfo->dirty_region_info.top_align) != 0)
		|| ((dirty->h % pinfo->dirty_region_info.h_align) != 0)
		|| (dirty->h < pinfo->dirty_region_info.h_min)
		|| (dirty->x >= pinfo->xres) || (dirty->w > pinfo->xres)
		|| ((dirty->x + dirty->w) > pinfo->xres)
		|| (dirty->y >= pinfo->yres) || (dirty->h > pinfo->yres)
		|| ((dirty->y + dirty->h) > pinfo->yres)) {
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
		ARRAY_SIZE(set_display_address), hisifd->mipi_dsi0_base);

	return 0;
}

static ssize_t mipi_lcd_panel_sleep_ctrl_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (pdev == NULL) {
		return -1;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = snprintf(buf, PAGE_SIZE,
			"enable_lcd_sleep_in=%d,pinfo->lcd_adjust_support=%d\n",
			g_debug_enable_lcd_sleep_in, hisifd->panel_info.lcd_adjust_support);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_sleep_ctrl_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	unsigned long val = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	ret = strict_strtoul(buf, 0, &val);
	if (ret) {
		HISI_FB_ERR("strict_strtoul error, buf=%s", buf);
		return ret;
	}

	if (pdev == NULL) {
		return -1;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}
	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.lcd_adjust_support) {
		g_debug_enable_lcd_sleep_in = val;
	}

	if (g_debug_enable_lcd_sleep_in == 2) {
		HISI_FB_INFO("LCD power off and Touch goto sleep\n");
		g_tp_power_ctrl = 1;
	} else {
		HISI_FB_INFO("g_debug_enable_lcd_sleep_in is %d\n",
			g_debug_enable_lcd_sleep_in);
		g_tp_power_ctrl = 0;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int mipi_lcd_panel_check_esd(struct platform_device* pdev)
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
	hisifd = (struct hisi_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = mipi_dsi_read_compare(&data, hisifd->mipi_dsi0_base);
#if defined (CONFIG_HUAWEI_DSM)
	if (ret) {
		HISI_FB_ERR("ESD ERROR:ret = %d\n", ret);
		ret = dsm_client_ocuppy(lcd_dclient);
		if ( !ret ) {
			dsm_client_record(lcd_dclient, "ESD ERROR:ret = %d\n", ret);
			dsm_client_notify(lcd_dclient, DSM_LCD_ESD_RECOVERY_NO);
		}else{
			HISI_FB_ERR("dsm_client_ocuppy ERROR:retVal = %d\n", ret);
		}
	}
#endif
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_test_config_show(struct platform_device *pdev,
	char *buf)
{
	int i = 0;

	for(i = 0;i < SENCE_ARRAY_SIZE;i++) {
		if (!strncmp(lcd_cmd_now, sence_array[i], strlen(sence_array[i]))) {
			HISI_FB_INFO("current test cmd:%s,return cmd:%s\n",
						lcd_cmd_now,cmd_array[i]);
			return snprintf(buf, PAGE_SIZE, cmd_array[i]);
		}
	}

	HISI_FB_INFO("cmd invaild,current test cmd:%s\n", lcd_cmd_now);
	return snprintf(buf, PAGE_SIZE, "INVALID");
}

static ssize_t mipi_lcd_panel_test_config_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (strlen(buf) < LCD_CMD_NAME_MAX) {
		memcpy(lcd_cmd_now, buf, strlen(buf) + 1);
		HISI_FB_INFO("current test cmd:%s\n", lcd_cmd_now);
	} else {
		memcpy(lcd_cmd_now, "INVALID", strlen("INVALID") + 1);
		HISI_FB_INFO("invalid test cmd:%s\n", lcd_cmd_now);
	}

	return count;
}

static int g_support_mode = 0;

static ssize_t mipi_lcd_panel_support_mode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	if (pdev == NULL) {
		return -1;
	}

	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "%d\n", g_support_mode);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_lcd_panel_support_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;
	int flag = -1;
	struct hisi_fb_data_type *hisifd = NULL;

	if (pdev == NULL) {
		return -1;
	}

	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return -1;
	}

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
		return ret;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	flag = (int)val;

	g_support_mode = flag;

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return snprintf((char *)buf, count, "%d\n", g_support_mode);
}

static ssize_t mipi_lcd_panel_info_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("pdev NULL pointer\n");
		return 0;
	};
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("hisifd NULL pointer\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	if (buf) {
		ret = snprintf(buf, PAGE_SIZE, "blmax:%u,blmin:%u,lcdtype:%s,\n",
				hisifd->panel_info.bl_max, hisifd->panel_info.bl_min, "LCD");
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_lcd_panel_set_fastboot,
	.on = mipi_lcd_panel_on,
	.off = mipi_lcd_panel_off,
	.remove = mipi_lcd_panel_remove,
	.set_backlight = mipi_lcd_panel_set_backlight,
	.lcd_model_show = mipi_lcd_panel_model_show,
	.lcd_cabc_mode_show = mipi_lcd_panel_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_lcd_panel_cabc_mode_store,
	.lcd_check_reg = mipi_lcd_panel_check_reg_show,
	.lcd_mipi_detect = mipi_lcd_panel_mipi_detect_show,
	.lcd_gram_check_show = mipi_lcd_panel_gram_check_show,
	.lcd_gram_check_store = mipi_lcd_panel_gram_check_store,
	.set_display_region = mipi_lcd_panel_set_display_region,
	.lcd_sleep_ctrl_show = mipi_lcd_panel_sleep_ctrl_show,
	.lcd_sleep_ctrl_store = mipi_lcd_panel_sleep_ctrl_store,
	.esd_handle = mipi_lcd_panel_check_esd,
	.lcd_test_config_show = mipi_lcd_panel_test_config_show,
	.lcd_test_config_store = mipi_lcd_panel_test_config_store,
	.lcd_support_mode_show = mipi_lcd_panel_support_mode_show,
	.lcd_support_mode_store = mipi_lcd_panel_support_mode_store,
	.panel_info_show = mipi_lcd_panel_info_show,
};

static int mipi_lcd_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;
	uint32_t support_mode = 0;
#ifdef CONFIG_HUAWEI_TS
	/* not use fb_notify to control touch timing. */
	g_lcd_control_tp_power = true;
#endif

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SHARP_KNT_NT35597);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_SHARP_KNT_NT35597);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_CMD;
	}
	HISI_FB_INFO("lcd_display_type=%u!\n", lcd_display_type);

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

	HISI_FB_INFO("%s\n", DTS_COMP_SHARP_KNT_NT35597);

	gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 0);
	gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 1);
	gpio_lcd_reset = of_get_named_gpio(np, "gpios", 2);

	HISI_FB_INFO("enn=%d,enp=%d,rst=%d",gpio_lcd_n5v5_enable,
		gpio_lcd_p5v5_enable,gpio_lcd_reset);
	pdev->id = 1;

	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1440;
	pinfo->yres = 2560;
	pinfo->width = 75;
	pinfo->height = 133;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;
	pinfo->type = lcd_display_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 1;

#ifdef CONFIG_BACKLIGHT_2048
	pinfo->bl_min = 63;
	pinfo->bl_max = 7992;
	pinfo->bl_default = 4000;
	pinfo->blpwm_precision_type = BLPWM_PRECISION_2048_TYPE;
	pinfo->bl_ic_ctrl_mode = REG_ONLY_MODE;
#else
	pinfo->bl_min = 4;
	pinfo->bl_max = 255;
	pinfo->bl_default = 102;
#endif

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;
	pinfo->esd_skip_mipi_check = 0;
	pinfo->lcd_uninit_step_support = 1;
	pinfo->lcd_adjust_support = 1;
	pinfo->color_temperature_support = 1;

	/* prefix ce & sharpness */
	pinfo->prefix_ce_support = 0;
	pinfo->prefix_sharpness1D_support = 0;
	pinfo->prefix_sharpness2D_support = 0;

	/* sbl */
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

	/* ACM */
	pinfo->acm_support = 1;
	if (pinfo->acm_support == 1) {
		pinfo->acm_lut_hue_table = acm_lut_hue_table;
		pinfo->acm_lut_hue_table_len = ARRAY_SIZE(acm_lut_hue_table);
		pinfo->acm_lut_sata_table = acm_lut_sata_table;
		pinfo->acm_lut_sata_table_len = ARRAY_SIZE(acm_lut_sata_table);
		pinfo->acm_lut_satr_table = acm_lut_satr_table;
		pinfo->acm_lut_satr_table_len = ARRAY_SIZE(acm_lut_satr_table);
		/*for cinema mode */
		pinfo->cinema_acm_lut_hue_table = cinema_acm_lut_hue_table;
		pinfo->cinema_acm_lut_hue_table_len
			= ARRAY_SIZE(cinema_acm_lut_hue_table);
		pinfo->cinema_acm_lut_sata_table
			= cinema_acm_lut_sata_table;
		pinfo->cinema_acm_lut_sata_table_len
			= ARRAY_SIZE(cinema_acm_lut_sata_table);
		pinfo->cinema_acm_lut_satr_table
			= cinema_acm_lut_satr_table;
		pinfo->cinema_acm_lut_satr_table_len
			= ARRAY_SIZE(cinema_acm_lut_satr_table);

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
		/*for cinema mode */
		pinfo->cinema_acm_valid_num = 7;
		pinfo->cinema_r0_hh = 0x7f;
		pinfo->cinema_r0_lh = 0x0;
		pinfo->cinema_r1_hh = 0xff;
		pinfo->cinema_r1_lh = 0x80;
		pinfo->cinema_r2_hh = 0x17f;
		pinfo->cinema_r2_lh = 0x100;
		pinfo->cinema_r3_hh = 0x1ff;
		pinfo->cinema_r3_lh = 0x180;
		pinfo->cinema_r4_hh = 0x27f;
		pinfo->cinema_r4_lh = 0x200;
		pinfo->cinema_r5_hh = 0x2ff;
		pinfo->cinema_r5_lh = 0x280;
		pinfo->cinema_r6_hh = 0x37f;
		pinfo->cinema_r6_lh = 0x300;
		/* ACM_CE */
		pinfo->acm_ce_support = 1;
	}

	/* Contrast Algorithm */
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

	/* Gama LCP */
	pinfo->gamma_support = 1;
	if (pinfo->gamma_support == 1) {
		pinfo->gamma_lut_table_R = gamma_lut_table_R;
		pinfo->gamma_lut_table_G = gamma_lut_table_G;
		pinfo->gamma_lut_table_B = gamma_lut_table_B;
		pinfo->gamma_lut_table_len = ARRAY_SIZE(gamma_lut_table_R);

		pinfo->cinema_gamma_lut_table_R = cinema_gamma_lut_table_R;
		pinfo->cinema_gamma_lut_table_G = cinema_gamma_lut_table_G;
		pinfo->cinema_gamma_lut_table_B = cinema_gamma_lut_table_B;
		pinfo->cinema_gamma_lut_table_len
			= ARRAY_SIZE(cinema_gamma_lut_table_R);

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
		pinfo->comform_mode_support = 1;
		pinfo->cinema_mode_support = 1;
	}

	if(pinfo->comform_mode_support == 1){
		support_mode = (support_mode | COMFORM_MODE);
	}
	if(pinfo->cinema_mode_support == 1){
		support_mode = (support_mode | CINEMA_MODE);
	}
	g_support_mode = support_mode | LED_RG_COLOR_TEMP_MODE;
	pinfo->color_temp_rectify_support = 1;
	/* 95.66 percent */
	pinfo->color_temp_rectify_R = 31346;
	/* 100 percent */
	pinfo->color_temp_rectify_G = 32768;
	/* 98.37 percent */
	pinfo->color_temp_rectify_B = 32234;
	g_led_rg_para1 = 6;
	g_led_rg_para2 = 31238;
	pinfo->panel_effect_support = 1;

	/* ldi */
	pinfo->ldi.h_back_porch = 96;
	pinfo->ldi.h_front_porch = 108;
	pinfo->ldi.h_pulse_width = 48;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 4;
	pinfo->pxl_clk_rate = 288 * 1000000UL;

	/* mipi clock begin */
	pinfo->mipi.dsi_bit_clk = 480;
	pinfo->mipi.dsi_bit_clk_val1 = 471;
	pinfo->mipi.dsi_bit_clk_val2 = 480;
	pinfo->mipi.dsi_bit_clk_val3 = 490;
	pinfo->mipi.dsi_bit_clk_val4 = 500;
	/* pinfo->mipi.dsi_bit_clk_val5 = ; */
	pinfo->dsi_bit_clk_upt_support = 1;
	pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	/* non_continue adjust : measured in UI
	* sharp requires clk_post >= 60ns + 252ui,
	* Here 300 is used,300 means about 400ns measure
	* by oscilloscope.
	*/
	pinfo->mipi.clk_post_adjust = 300;
	pinfo->mipi.clk_pre_adjust= 0;
	pinfo->mipi.clk_t_hs_prepare_adjust= 0;
	pinfo->mipi.clk_t_lpx_adjust= 0;
	pinfo->mipi.clk_t_hs_trial_adjust= 0;
	pinfo->mipi.clk_t_hs_exit_adjust= 0;
	pinfo->mipi.clk_t_hs_zero_adjust= 0;
	pinfo->mipi.non_continue_en = 1;
	pinfo->pxl_clk_rate_div = 1;
	pinfo->vsync_ctrl_type = VSYNC_CTRL_ISR_OFF
		| VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
	/* mipi clock end */

	/* Dirty Region Update begin */
	pinfo->dirty_region_updt_support = 1;
	pinfo->dirty_region_info.left_align = -1;
	pinfo->dirty_region_info.right_align = -1;
	pinfo->dirty_region_info.top_align = 32;
	pinfo->dirty_region_info.bottom_align = 32;
	pinfo->dirty_region_info.w_align = -1;
	pinfo->dirty_region_info.h_align = -1;
	pinfo->dirty_region_info.w_min = pinfo->xres;
	pinfo->dirty_region_info.h_min = -1;
	pinfo->dirty_region_info.top_start = -1;
	pinfo->dirty_region_info.bottom_start = -1;


	pinfo->ifbc_type = IFBC_TYPE_VESA3X_DUAL;
	pinfo->pxl_clk_rate_div = 3;

	/* IFBC Setting begin */
	/* dsc parameter info */
	pinfo->vesa_dsc.bits_per_component = 8;
	pinfo->vesa_dsc.bits_per_pixel = 8;
	pinfo->vesa_dsc.slice_width = 719;
	pinfo->vesa_dsc.slice_height = 31;

	pinfo->vesa_dsc.initial_xmit_delay = 512;
	pinfo->vesa_dsc.first_line_bpg_offset = 12;
	pinfo->vesa_dsc.mux_word_size = 48;

	/*  DSC_CTRL */
	pinfo->vesa_dsc.block_pred_enable = 1;
	pinfo->vesa_dsc.linebuf_depth = 9;

	/* RC_PARAM3 */
	pinfo->vesa_dsc.initial_offset = 6144;

	/* FLATNESS_QP_TH */
	pinfo->vesa_dsc.flatness_min_qp = 3;
	pinfo->vesa_dsc.flatness_max_qp = 12;

	/* DSC_PARAM4 */
	pinfo->vesa_dsc.rc_edge_factor= 0x6;
	pinfo->vesa_dsc.rc_model_size = 8192;

	/* DSC_RC_PARAM5: 0x330b0b */
	pinfo->vesa_dsc.rc_tgt_offset_lo = (0x330b0b >> 20) & 0xF;
	pinfo->vesa_dsc.rc_tgt_offset_hi = (0x330b0b >> 16) & 0xF;
	pinfo->vesa_dsc.rc_quant_incr_limit1 = (0x330b0b >> 8) & 0x1F;
	pinfo->vesa_dsc.rc_quant_incr_limit0 = (0x330b0b >> 0) & 0x1F;

	/* DSC_RC_BUF_THRESH0: 0xe1c2a38 */
	pinfo->vesa_dsc.rc_buf_thresh0 = (0xe1c2a38 >> 24) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh1 = (0xe1c2a38 >> 16) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh2 = (0xe1c2a38 >> 8) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh3 = (0xe1c2a38 >> 0) & 0xFF;

	/* DSC_RC_BUF_THRESH1: 0x46546269 */
	pinfo->vesa_dsc.rc_buf_thresh4 = (0x46546269 >> 24) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh5 = (0x46546269 >> 16) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh6 = (0x46546269 >> 8) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh7 = (0x46546269 >> 0) & 0xFF;

	/* DSC_RC_BUF_THRESH2: 0x7077797b */
	pinfo->vesa_dsc.rc_buf_thresh8 = (0x7077797b >> 24) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh9 = (0x7077797b >> 16) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh10 = (0x7077797b >> 8) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh11 = (0x7077797b >> 0) & 0xFF;

	/* DSC_RC_BUF_THRESH3: 0x7d7e0000 */
	pinfo->vesa_dsc.rc_buf_thresh12 = (0x7d7e0000 >> 24) & 0xFF;
	pinfo->vesa_dsc.rc_buf_thresh13 = (0x7d7e0000 >> 16) & 0xFF;

	/* DSC_RC_RANGE_PARAM0: 0x1020100 */
	pinfo->vesa_dsc.range_min_qp0 = (0x1020100 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp0 = (0x1020100 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset0 = (0x1020100 >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp1 = (0x1020100 >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp1 = (0x1020100 >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset1 = (0x1020100 >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM1: 0x94009be */
	pinfo->vesa_dsc.range_min_qp2 = (0x94009be >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp2 = (0x94009be >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset2 = (0x94009be >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp3 = (0x94009be >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp3 = (0x94009be >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset3 = (0x94009be >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM2, 0x19fc19fa */
	pinfo->vesa_dsc.range_min_qp4 = (0x19fc19fa >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp4 = (0x19fc19fa >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset4 = (0x19fc19fa >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp5 = (0x19fc19fa >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp5 = (0x19fc19fa >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset5 = (0x19fc19fa >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM3, 0x19f81a38 */
	pinfo->vesa_dsc.range_min_qp6 = (0x19f81a38 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp6 = (0x19f81a38 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset6 = (0x19f81a38 >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp7 = (0x19f81a38 >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp7 = (0x19f81a38 >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset7 = (0x19f81a38 >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM4, 0x1a781ab6 */
	pinfo->vesa_dsc.range_min_qp8 = (0x1a781ab6 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp8 = (0x1a781ab6 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset8 = (0x1a781ab6 >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp9 = (0x1a781ab6 >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp9 = (0x1a781ab6 >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset9 = (0x1a781ab6 >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM5, 0x2af62b34 */
	pinfo->vesa_dsc.range_min_qp10 = (0x2af62b34 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp10 = (0x2af62b34 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset10 = (0x2af62b34 >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp11 = (0x2af62b34 >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp11 = (0x2af62b34 >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset11 = (0x2af62b34 >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM6, 0x2b743b74 */
	pinfo->vesa_dsc.range_min_qp12 = (0x2b743b74 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp12 = (0x2b743b74 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset12 = (0x2b743b74 >> 16) & 0x3F;
	pinfo->vesa_dsc.range_min_qp13 = (0x2b743b74 >> 11) & 0x1F;
	pinfo->vesa_dsc.range_max_qp13 = (0x2b743b74 >> 6) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset13 = (0x2b743b74 >> 0) & 0x3F;

	/* DSC_RC_RANGE_PARAM7, 0x6bf40000 */
	pinfo->vesa_dsc.range_min_qp14 = (0x6bf40000 >> 27) & 0x1F;
	pinfo->vesa_dsc.range_max_qp14 = (0x6bf40000 >> 22) & 0x1F;
	pinfo->vesa_dsc.range_bpg_offset14 = (0x6bf40000 >> 16) & 0x3F;


	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}
	/* IFBC Setting end */

	ret = vcc_cmds_tx(pdev, lcd_vcc_init_cmds,
		ARRAY_SIZE(lcd_vcc_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("LCD vcc init failed!\n");
		goto err_return;
	}

	ret = pinctrl_cmds_tx(pdev, lcd_pinctrl_init_cmds,
		ARRAY_SIZE(lcd_pinctrl_init_cmds));
	if (ret != 0) {
		HISI_FB_ERR("Init pinctrl failed, defer\n");
		goto err_return;
	}

	if (is_fastboot_display_enable()) {
		vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
			ARRAY_SIZE(lcd_vcc_enable_cmds));
	}

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
		.compatible = DTS_COMP_SHARP_KNT_NT35597,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_lcd_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_sharp_knt_NT35597",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_lcd_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_lcd_panel_init);
