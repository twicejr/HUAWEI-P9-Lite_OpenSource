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


/* default pwm clk */
#define DEFAULT_PWM_CLK_RATE	(120 * 1000000L)

static char __iomem *hisifd_pwm_base;
static struct clk *g_pwm_clk;
static struct platform_device *g_pwm_pdev;
static int g_pwm_on;
static int g_pwm_fpga_flag;

static struct pinctrl_data pwmpctrl;


static struct pinctrl_cmd_desc pwm_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pwmpctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pwmpctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pwmpctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc pwm_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pwmpctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc pwm_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pwmpctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc pwm_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pwmpctrl, 0},
};


#define PWM_LOCK_OFFSET	(0x0000)
#define PWM_CTL_OFFSET	(0X0004)
#define PWM_CFG_OFFSET	(0x0008)
#define PWM_PR0_OFFSET	(0x0100)
#define PWM_PR1_OFFSET	(0x0104)
#define PWM_C0_MR_OFFSET	(0x0300)
#define PWM_C0_MR0_OFFSET	(0x0304)

#define PWM_OUT_PRECISION	(800)


int hisi_pwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *pwm_base = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	pwm_base = hisifd_pwm_base;
	if (!pwm_base) {
		HISI_FB_ERR("pwm_base is null!\n");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (pinfo->bl_max < 1) {
		HISI_FB_ERR("bl_max(%d) is out of range!!", pinfo->bl_max);
		return -EINVAL;
	}

	if (bl_level > pinfo->bl_max) {
		bl_level = pinfo->bl_max;
	}

	if ((bl_level < pinfo->bl_min) && bl_level) {
		bl_level = pinfo->bl_min;
	}

	bl_level = (bl_level * PWM_OUT_PRECISION) / pinfo->bl_max;

	outp32(pwm_base + PWM_LOCK_OFFSET, 0x1acce551);
	outp32(pwm_base + PWM_CTL_OFFSET, 0x0);
	outp32(pwm_base + PWM_CFG_OFFSET, 0x2);
	outp32(pwm_base + PWM_PR0_OFFSET, 0x1);
	outp32(pwm_base + PWM_PR1_OFFSET, 0x2);
	outp32(pwm_base + PWM_CTL_OFFSET, 0x1);
	outp32(pwm_base + PWM_C0_MR_OFFSET, (PWM_OUT_PRECISION - 1));
	outp32(pwm_base + PWM_C0_MR0_OFFSET, bl_level);

	return 0;
}

int hisi_pwm_on(struct platform_device *pdev)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;
	char __iomem *pwm_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	pwm_base = hisifd_pwm_base;
	if (!pwm_base) {
		HISI_FB_ERR("pwm_base is null!\n");
		return -EINVAL;
	}

	if (g_pwm_on == 1)
		return 0;

	// dis-reset pwm
	outp32(hisifd->peri_crg_base + PERRSTDIS2, 0x1);

	clk_tmp = g_pwm_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("dss_pwm_clk clk_prepare failed, error=%d!\n", ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("dss_pwm_clk clk_enable failed, error=%d!\n", ret);
			return -EINVAL;
		}

		HISI_FB_INFO("lw dss_pwm_clk clk_enable successed, ret=%d!\n", ret);
	}

	ret = pinctrl_cmds_tx(g_pwm_pdev, pwm_pinctrl_normal_cmds,
		ARRAY_SIZE(pwm_pinctrl_normal_cmds));

	//if enable PWM, please set IOMG_004 in IOC_AO module
	//set IOMG_004: select PWM_OUT0

	g_pwm_on = 1;

	return ret;
}

int hisi_pwm_off(struct platform_device *pdev)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;
	char __iomem *pwm_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pwm_base = hisifd_pwm_base;
	if (!pwm_base) {
		HISI_FB_ERR("pwm_base is null!\n");
		return -EINVAL;
	}

	if (g_pwm_on == 0)
		return 0;

	ret = pinctrl_cmds_tx(g_pwm_pdev, pwm_pinctrl_lowpower_cmds,
		ARRAY_SIZE(pwm_pinctrl_lowpower_cmds));

	clk_tmp = g_pwm_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}

	//reset pwm
	outp32(hisifd->peri_crg_base + PERRSTEN2, 0x1);

	g_pwm_on = 0;

	return ret;
}

static int hisi_pwm_probe(struct platform_device *pdev)
{
	struct device_node *np = NULL;
	int ret = 0;

	HISI_FB_DEBUG("+.\n");

	BUG_ON(pdev == NULL);

	g_pwm_pdev = pdev;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_PWM_NAME);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_PWM_NAME);
		ret = -ENXIO;
		goto err_return;
	}

	/* get pwm reg base */
	hisifd_pwm_base = of_iomap(np, 0);
	if (!hisifd_pwm_base) {
		HISI_FB_ERR("failed to get pwm_base resource.\n");
		return -ENXIO;
	}

	ret = of_property_read_u32(np, "fpga_flag", &g_pwm_fpga_flag);
	if (ret) {
		HISI_FB_ERR("failed to get fpga_flag resource.\n");
		return -ENXIO;
	}

	if (g_pwm_fpga_flag == 0) {
		/* pwm pinctrl init */
		ret = pinctrl_cmds_tx(pdev, pwm_pinctrl_init_cmds,
			ARRAY_SIZE(pwm_pinctrl_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("Init pwm pinctrl failed! ret=%d.\n", ret);
			goto err_return;
		}

		/* get pwm clk resource */
		g_pwm_clk = of_clk_get(np, 0);
		if (IS_ERR(g_pwm_clk)) {
			HISI_FB_ERR("%s clock not found: %d!\n",
				np->name, (int)PTR_ERR(g_pwm_clk));
			ret = -ENXIO;
			goto err_return;
		}

	#if 0
		ret = clk_set_rate(g_pwm_clk, DEFAULT_PWM_CLK_RATE);
		if (ret != 0) {
			HISI_FB_ERR("dss_pwm_clk clk_set_rate(%lu) failed, error=%d!\n",
				DEFAULT_PWM_CLK_RATE, ret);
			ret = -EINVAL;
			goto err_return;
		}
	#endif

		HISI_FB_INFO("dss_pwm_clk:[%lu]->[%lu].\n",
			DEFAULT_PWM_CLK_RATE, clk_get_rate(g_pwm_clk));
	}

	hisi_fb_device_set_status0(DTS_PWM_READY);

	HISI_FB_DEBUG("-.\n");

	return 0;

err_return:
	return ret;
}

static int hisi_pwm_remove(struct platform_device *pdev)
{
	struct clk *clk_tmp = NULL;
	int ret = 0;

	ret = pinctrl_cmds_tx(pdev, pwm_pinctrl_finit_cmds,
		ARRAY_SIZE(pwm_pinctrl_finit_cmds));

	clk_tmp = g_pwm_clk;
	if (clk_tmp) {
		clk_put(clk_tmp);
		clk_tmp = NULL;
	}

	return ret;
}

static const struct of_device_id hisi_pwm_match_table[] = {
	{
		.compatible = DTS_COMP_PWM_NAME,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_pwm_match_table);

static struct platform_driver this_driver = {
	.probe = hisi_pwm_probe,
	.remove = hisi_pwm_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_PWM,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_pwm_match_table),
	},
};

static int __init hisi_pwm_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(hisi_pwm_init);
