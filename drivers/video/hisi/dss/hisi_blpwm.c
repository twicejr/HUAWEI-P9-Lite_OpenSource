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
#ifdef CONFIG_HISI_FB_3650
#include "backlight_linear_to_exponential.h"
#include "backlight/lm36923.h"
#endif

#include <linux/timer.h>
#include <linux/delay.h>

/* default pwm clk */
#define DEFAULT_PWM_CLK_RATE	(120 * 1000000L)
static char __iomem *hisifd_blpwm_base;
static struct clk *g_dss_blpwm_clk;
static struct platform_device *g_blpwm_pdev;
static int g_blpwm_on;
static int g_blpwm_fpga_flag;

static struct pinctrl_data blpwmpctrl;

static struct pinctrl_cmd_desc blpwm_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &blpwmpctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &blpwmpctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &blpwmpctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc blpwm_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &blpwmpctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc blpwm_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &blpwmpctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc blpwm_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &blpwmpctrl, 0},
};


#define BLPWM_OUT_CTRL	(0x100)
#define BLPWM_OUT_DIV	(0x104)
#define BLPWM_OUT_CFG	(0x108)

#define BLPWM_OUT_PRECISION_DEFAULT	(800)
#define BLPWM_OUT_PRECISION	(10000)
#define BLPWM_OUT_PRECISION_2048	(2047)
#define BLPWM_BL_LEVEL_MIN	(4)

//BLPWM input address
#define PWM_IN_CTRL_OFFSET	(0x000)
#define PWM_IN_DIV_OFFSET	(0x004)
#define PWM_IN_NUM_OFFSET	(0x008)
#define PWM_IN_PRECISION_DEFAULT	(512)
#define PWM_IN_SENSITY	(2)

#define CABC_DIMMING_STEP_TOTAL_NUM    32
static struct task_struct *cabc_pwm_task;

struct bl_info{
	int32_t bl_max;
	int32_t bl_min;
	int32_t ap_brightness;
	int32_t index_cabc_dimming;
	int32_t cabc_pwm;
	int32_t prev_cabc_pwm;
	int32_t current_cabc_pwm;
	int32_t cabc_pwm_in;
	int32_t last_bl_level;
#ifdef CONFIG_HISI_FB_3650
	int32_t bl_ic_ctrl_mode;
#endif
	uint32_t blpwm_input_precision;
	uint32_t blpwm_out_precision;
	struct semaphore bl_semaphore;
};

static struct bl_info g_bl_info;

#ifdef CONFIG_HISI_FB_3650
#define BL_LVL_MAP_SIZE	(2047)
static int bl_lvl_map(int level)
{
	int ret = 0;
	int idx = 0;

	if (level < 0 || level > 10000) {
		HISI_FB_ERR("Need Valid Data! level = %d", level);
		return ret;
	}

	for (idx = 0; idx <= BL_LVL_MAP_SIZE; idx++) {
		if (level_map[idx] >= level) {
			if (level_map[idx] > level) {
				idx = idx - 1;
			}
			break;
		}
	}

	return idx;
}
#endif

static void init_bl_info(struct hisi_panel_info *pinfo)
{
	g_bl_info.bl_max = pinfo->bl_max;
	g_bl_info.bl_min = pinfo->bl_min;
	g_bl_info.ap_brightness = 0;

	if (pinfo->blpwm_input_precision == 0)
		pinfo->blpwm_input_precision = PWM_IN_PRECISION_DEFAULT;

	pinfo->blpwm_in_num = 0xFFFF0000;
	g_bl_info.blpwm_input_precision = pinfo->blpwm_input_precision;
	g_bl_info.index_cabc_dimming = 0;

	g_bl_info.last_bl_level =0;
	if (pinfo->blpwm_precision_type == BLPWM_PRECISION_10000_TYPE) {
		g_bl_info.blpwm_out_precision = BLPWM_OUT_PRECISION;
		outp32(hisifd_blpwm_base + BLPWM_OUT_DIV, 0);
	} else if (pinfo->blpwm_precision_type == BLPWM_PRECISION_2048_TYPE) {
		g_bl_info.blpwm_out_precision = BLPWM_OUT_PRECISION_2048;
		outp32(hisifd_blpwm_base + BLPWM_OUT_DIV, 0x2);
	} else {
		g_bl_info.blpwm_out_precision = BLPWM_OUT_PRECISION_DEFAULT;
		outp32(hisifd_blpwm_base + BLPWM_OUT_DIV, 0x2);
	}
	g_bl_info.cabc_pwm = g_bl_info.blpwm_input_precision;
	g_bl_info.prev_cabc_pwm = g_bl_info.blpwm_input_precision;
	g_bl_info.current_cabc_pwm = g_bl_info.blpwm_input_precision;
	g_bl_info.cabc_pwm_in = g_bl_info.blpwm_input_precision;
	sema_init(&g_bl_info.bl_semaphore, 1);
#ifdef CONFIG_HISI_FB_3650
	g_bl_info.bl_ic_ctrl_mode = pinfo->bl_ic_ctrl_mode;
#endif
	return ;
}

static void update_backlight(uint32_t backlight)
{
	char __iomem *blpwm_base = NULL;
	uint32_t brightness = 0;
	uint32_t bl_level = (backlight * g_bl_info.blpwm_out_precision) / g_bl_info.bl_max;
	HISI_FB_DEBUG("cabc8:bl_level=%d, backlight=%d, blpwm_out_precision=%d, bl_max=%d\n",
			bl_level, backlight, g_bl_info.blpwm_out_precision, g_bl_info.bl_max);
	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return;
	}

#ifdef CONFIG_HISI_FB_3650
	if (REG_ONLY_MODE == g_bl_info.bl_ic_ctrl_mode) {
		bl_level = backlight;
		bl_level = bl_lvl_map(bl_level);
		HISI_FB_DEBUG("cabc9:bl_level=%d\n",bl_level);
		/* lm36923_ramp_brightness(bl_level); */
		lm36923_set_backlight_reg(bl_level);
		return;
	}
#endif

	brightness = (bl_level << 16) | (g_bl_info.blpwm_out_precision - bl_level);
	outp32(blpwm_base + BLPWM_OUT_CFG, brightness);
}

static int cabc_pwm_thread(void *p)
{
	int32_t delta_cabc_pwm = 0;
	int32_t pwm_duty = 0;
	int32_t backlight = 0;

	while(!kthread_should_stop()) {
		HISI_FB_DEBUG("cabc3:jump while\n");
		if (g_bl_info.index_cabc_dimming > CABC_DIMMING_STEP_TOTAL_NUM) {
			HISI_FB_DEBUG("cabc4:dimming 32 time\n");
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
			g_bl_info.index_cabc_dimming = 1;
		} else {
			down(&g_bl_info.bl_semaphore);
			HISI_FB_DEBUG("cabc5:dimming time=%d, g_bl_info.cabc_pwm_in=%d\n", g_bl_info.index_cabc_dimming, g_bl_info.cabc_pwm_in);
			if (g_bl_info.cabc_pwm_in != 0) {
				g_bl_info.cabc_pwm = g_bl_info.cabc_pwm_in;
				g_bl_info.cabc_pwm_in = 0;
				g_bl_info.index_cabc_dimming = 1;
				g_bl_info.prev_cabc_pwm = g_bl_info.current_cabc_pwm;
				HISI_FB_DEBUG("cabc6:cabc_pwm=%d, cabc_pwm_in=%d, prev_cabc_pwm=%d\n",
					g_bl_info.cabc_pwm, g_bl_info.cabc_pwm_in, g_bl_info.prev_cabc_pwm);
			}
			delta_cabc_pwm = g_bl_info.cabc_pwm - g_bl_info.prev_cabc_pwm;
			pwm_duty = delta_cabc_pwm*g_bl_info.index_cabc_dimming/32 + delta_cabc_pwm *g_bl_info.index_cabc_dimming % 32 /16;

			g_bl_info.current_cabc_pwm = g_bl_info.prev_cabc_pwm + pwm_duty;
			backlight = g_bl_info.current_cabc_pwm * g_bl_info.ap_brightness / g_bl_info.blpwm_input_precision;
			if (backlight > 0 && backlight < g_bl_info.bl_min) {
				backlight = g_bl_info.bl_min;
			}
			HISI_FB_DEBUG("cabc7:g_bl_info.ap_brightness=%d, g_bl_info.last_bl_level=%d, backlight=%d,\n\
					g_bl_info.current_cabc_pwm=%d, pwm_duty=%d, g_bl_info.cabc_pwm=%d, g_bl_info.prev_cabc_pwm=%d, delta_cabc_pwm=%d,\n",
					g_bl_info.ap_brightness, g_bl_info.last_bl_level, backlight, g_bl_info.current_cabc_pwm, pwm_duty, g_bl_info.cabc_pwm,
					g_bl_info.prev_cabc_pwm, delta_cabc_pwm);
			if (g_bl_info.ap_brightness != 0 && backlight != g_bl_info.last_bl_level) {
				update_backlight(backlight);
				g_bl_info.last_bl_level = backlight;
			}

			g_bl_info.index_cabc_dimming++;
			up(&g_bl_info.bl_semaphore);
			msleep(16);
		}
	}
	return 0;
}

int hisi_cabc_set_backlight(uint32_t cabc_pwm_in)
{
	HISI_FB_DEBUG("cabc2:cabc_pwm_in=%d,g_bl_info.ap_brightness=%d,if null=%d\n",
			cabc_pwm_in, g_bl_info.ap_brightness, cabc_pwm_task == NULL);
	if (cabc_pwm_task == NULL) {
		return 0;
	}

	if (g_bl_info.ap_brightness == 0) {
	     g_bl_info.current_cabc_pwm = cabc_pwm_in;
	     return 0;
	}

	g_bl_info.cabc_pwm_in = cabc_pwm_in;
	HISI_FB_DEBUG("cabc2:g_bl_info.cabc_pwm_in:%d\n", cabc_pwm_in);
	wake_up_process(cabc_pwm_task);
	return 0;
}

static int hisi_blpwm_input_enable(struct hisi_fb_data_type *hisifd)
{
	char __iomem *blpwm_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	outp32(blpwm_base + PWM_IN_CTRL_OFFSET, 1);
	outp32(blpwm_base + PWM_IN_DIV_OFFSET, 0x02);

	cabc_pwm_task = kthread_create(cabc_pwm_thread, NULL, "cabc_pwm_task");
	if(IS_ERR(cabc_pwm_task)) {
		HISI_FB_ERR("Unable to start kernel cabc_pwm_task./n");
		cabc_pwm_task = NULL;
		return -EINVAL;
	}

	return 0;
}

static int hisi_blpwm_input_disable(struct hisi_fb_data_type *hisifd)
{
	char __iomem *blpwm_base = NULL;

	BUG_ON(hisifd == NULL);

	if (cabc_pwm_task) {
		kthread_stop(cabc_pwm_task);
		cabc_pwm_task = NULL;
	}

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	outp32(blpwm_base + PWM_IN_CTRL_OFFSET, 0);

	return 0;
}

int updateCabcPwm(struct hisi_fb_data_type *hisifd)
{
	char __iomem *blpwm_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	uint32_t pwm_in_num	= 0;
	uint32_t pwm_in_high_num = 0;
	uint32_t pwm_in_low_num  = 0;
	uint32_t pwm_in_duty = 0;
	uint32_t pre_pwm_in_num	= 0;
	uint32_t pre_pwm_in_high_num = 0;
	uint32_t pre_pwm_in_low_num  = 0;
	uint32_t pre_pwm_in_duty = 0;
	int delta_duty = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	if (!g_blpwm_on || !hisifd->bl_level || !hisifd->backlight.bl_updated)
		return 0;

	pwm_in_num = inp32(blpwm_base + PWM_IN_NUM_OFFSET);
	if (!pwm_in_num) {
		HISI_FB_ERR("pwm_in_num is null!\n");
		return -EINVAL;
	}
	pwm_in_high_num = pwm_in_num >> 16;
	pwm_in_low_num  = pwm_in_num & 0xFFFF;
	pwm_in_duty = pinfo->blpwm_input_precision * pwm_in_high_num / (pwm_in_high_num + pwm_in_low_num);

	HISI_FB_DEBUG("cabc0:pwm_in_numall=%d, pwm_in_high_num=%d, pwm_in_low_num=%d\n",
				pwm_in_high_num + pwm_in_low_num, pwm_in_high_num, pwm_in_low_num);
	pre_pwm_in_num = pinfo->blpwm_in_num;
	pre_pwm_in_high_num = pre_pwm_in_num >> 16;
	pre_pwm_in_low_num  = pre_pwm_in_num & 0xFFFF;
	pre_pwm_in_duty = pinfo->blpwm_input_precision * pre_pwm_in_high_num / (pre_pwm_in_high_num + pre_pwm_in_low_num);

	delta_duty = pwm_in_duty - pre_pwm_in_duty;
	HISI_FB_DEBUG("cabc1:Previous pwm in duty:%d, Current pwm in duty:%d, delta_duty:%d,pwm_in_num=%d\n",
			pre_pwm_in_duty, pwm_in_duty, delta_duty, pwm_in_num);
	if (delta_duty > PWM_IN_SENSITY || delta_duty < (-PWM_IN_SENSITY)) {
		pinfo->blpwm_in_num = pwm_in_num;
		hisi_cabc_set_backlight(pwm_in_duty);
	}

	return 0;
}

int hisi_blpwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *blpwm_base = NULL;
	uint32_t brightness = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	if (g_blpwm_on == 0) {
		HISI_FB_ERR("blpwm is not on, return!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (pinfo->bl_max < 1) {
		HISI_FB_ERR("bl_max(%d) is out of range!!", pinfo->bl_max);
		return -EINVAL;
	}

	if (bl_level > pinfo->bl_max) {
		bl_level = pinfo->bl_max;
	}

	//allow backlight zero
	if (bl_level < pinfo->bl_min && bl_level) {
		bl_level = pinfo->bl_min;
	}

	HISI_FB_DEBUG("cabc:fb%d, bl_level=%d, blpwm_input_ena=%d, blpwm_in_num=%d\n",
					hisifd->index, bl_level, pinfo->blpwm_input_ena, pinfo->blpwm_in_num);
	down(&g_bl_info.bl_semaphore);
	g_bl_info.ap_brightness = bl_level;
	if (pinfo->blpwm_input_ena && pinfo->blpwm_in_num) {

		if(bl_level > 0){
			bl_level= bl_level * g_bl_info.current_cabc_pwm / pinfo->blpwm_input_precision;
			bl_level =  bl_level < g_bl_info.bl_min ? g_bl_info.bl_min : bl_level ;
		}
		g_bl_info.last_bl_level = bl_level;
		HISI_FB_DEBUG("cabc:ap_brightness=%d, current_cabc_pwm=%d, blpwm_input_precision=%d, bl_level=%d\n",
				g_bl_info.ap_brightness, g_bl_info.current_cabc_pwm,
				pinfo->blpwm_input_precision, bl_level);
	}

#ifdef CONFIG_HISI_FB_3650
	if (REG_ONLY_MODE == pinfo->bl_ic_ctrl_mode) {
		bl_level = bl_lvl_map(bl_level);
		HISI_FB_DEBUG("cabc:bl_level=%d\n",bl_level);
		/* lm36923_ramp_brightness(bl_level); */
		lm36923_set_backlight_reg(bl_level);
		up(&g_bl_info.bl_semaphore);
		return 0;
	}
#endif

	bl_level = (bl_level * g_bl_info.blpwm_out_precision) / pinfo->bl_max;

	brightness = (bl_level << 16) | (g_bl_info.blpwm_out_precision - bl_level);
	outp32(blpwm_base + BLPWM_OUT_CFG, brightness);
	HISI_FB_DEBUG("cabc:ap_brightness=%d, current_cabc_pwm=%d, blpwm_input_precision=%d, \
				blpwm_out_precision=%d, bl_level=%d,\
				brightness=%d\n", g_bl_info.ap_brightness, g_bl_info.current_cabc_pwm,
				pinfo->blpwm_input_precision, g_bl_info.blpwm_out_precision, bl_level, brightness);
	up(&g_bl_info.bl_semaphore);
	return 0;
}

int hisi_blpwm_on(struct platform_device *pdev)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;
	char __iomem *blpwm_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	if (g_blpwm_on == 1)
		return 0;

	clk_tmp = g_dss_blpwm_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("dss_blpwm_clk clk_prepare failed, error=%d!\n", ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("dss_blpwm_clk clk_enable failed, error=%d!\n", ret);
			return -EINVAL;
		}
	}

	ret = pinctrl_cmds_tx(g_blpwm_pdev, blpwm_pinctrl_normal_cmds,
		ARRAY_SIZE(blpwm_pinctrl_normal_cmds));

	//if enable BLPWM, please set IOMG_003, IOMG_004 in IOC_AO module
	// set IOMG_003: select BLPWM_CABC
	// set IOMG_004: select BLPWM_BL

	outp32(blpwm_base + BLPWM_OUT_CTRL, 0x1);
	init_bl_info(pinfo);
	if (pinfo->blpwm_input_ena) {
		hisi_blpwm_input_enable(hisifd);
	}

	g_blpwm_on = 1;

	return ret;
}

int hisi_blpwm_off(struct platform_device *pdev)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;
	char __iomem *blpwm_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	blpwm_base = hisifd_blpwm_base;
	if (!blpwm_base) {
		HISI_FB_ERR("blpwm_base is null!\n");
		return -EINVAL;
	}

	if (g_blpwm_on == 0)
		return 0;

	outp32(blpwm_base + BLPWM_OUT_CTRL, 0x0);

	ret = pinctrl_cmds_tx(g_blpwm_pdev, blpwm_pinctrl_lowpower_cmds,
		ARRAY_SIZE(blpwm_pinctrl_lowpower_cmds));

	clk_tmp = g_dss_blpwm_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}

	if (pinfo->blpwm_input_ena) {
		hisi_blpwm_input_disable(hisifd);
	}

	g_blpwm_on = 0;

	return ret;
}

static int hisi_blpwm_probe(struct platform_device *pdev)
{
	struct device_node *np = NULL;
	int ret = 0;

	HISI_FB_DEBUG("+.\n");

	BUG_ON(pdev == NULL);

	g_blpwm_pdev = pdev;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_BLPWM_NAME);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_BLPWM_NAME);
		ret = -ENXIO;
		goto err_return;
	}

	/* get blpwm reg base */
	hisifd_blpwm_base = of_iomap(np, 0);
	if (!hisifd_blpwm_base) {
		HISI_FB_ERR("failed to get blpwm_base resource.\n");
		ret = -ENXIO;
		goto err_return;
	}

	ret = of_property_read_u32(np, "fpga_flag", &g_blpwm_fpga_flag);
	if (ret) {
		HISI_FB_ERR("failed to get fpga_flag resource.\n");
		ret = -ENXIO;
		goto err_return;
	}

	if (g_blpwm_fpga_flag == 0) {
		/* blpwm pinctrl init */
		ret = pinctrl_cmds_tx(pdev, blpwm_pinctrl_init_cmds,
				ARRAY_SIZE(blpwm_pinctrl_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("Init blpwm pinctrl failed! ret=%d.\n", ret);
			goto err_return;
		}

		/* get blpwm clk resource */
		g_dss_blpwm_clk = of_clk_get(np, 0);
		if (IS_ERR(g_dss_blpwm_clk)) {
			HISI_FB_ERR("%s clock not found: %d!\n",
					np->name, (int)PTR_ERR(g_dss_blpwm_clk));
			ret = -ENXIO;
			goto err_return;
		}

#if 0
		ret = clk_set_rate(g_dss_blpwm_clk, DEFAULT_PWM_CLK_RATE);
		if (ret < 0) {
			HISI_FB_ERR("dss_blpwm_clk clk_set_rate(%lu) failed, error=%d!\n",
					DEFAULT_PWM_CLK_RATE, ret);
			ret = -EINVAL;
			goto err_return;
		}
#endif

		HISI_FB_INFO("dss_blpwm_clk:[%lu]->[%lu].\n",
				DEFAULT_PWM_CLK_RATE, clk_get_rate(g_dss_blpwm_clk));
	}

	hisi_fb_device_set_status0(DTS_PWM_READY);

	HISI_FB_DEBUG("-.\n");

	return 0;

err_return:
	return ret;
}

static int hisi_blpwm_remove(struct platform_device *pdev)
{
	struct clk *clk_tmp = NULL;
	int ret = 0;

	ret = pinctrl_cmds_tx(pdev, blpwm_pinctrl_finit_cmds,
		ARRAY_SIZE(blpwm_pinctrl_finit_cmds));

	clk_tmp = g_dss_blpwm_clk;
	if (clk_tmp) {
		clk_put(clk_tmp);
		clk_tmp = NULL;
	}

	return ret;
}

static const struct of_device_id hisi_blpwm_match_table[] = {
	{
		.compatible = DTS_COMP_BLPWM_NAME,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_blpwm_match_table);

static struct platform_driver this_driver = {
	.probe = hisi_blpwm_probe,
	.remove = hisi_blpwm_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_BLPWM,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_blpwm_match_table),
	},
};

static int __init hisi_blpwm_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(hisi_blpwm_init);
