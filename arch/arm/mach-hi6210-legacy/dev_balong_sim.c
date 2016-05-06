/*
 * arch/arm/mach-hi6620/dev_balong_sim.c
 *
 * Copyright (C) 2013 Hisilicon Co. Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <mach/balong_sim.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>

static struct balong_sim_plat_data  balong_sim1_plat_data = {
    .name = SIM1,
    .sim_status = 0,
#ifdef SIM_HPD
    .sim_hpd_out_f = SIM1_HPD_OUT_F_TYPE,
    .sim_hpd_in_f = SIM1_HPD_IN_F_TYPE,
#endif
};

static struct balong_sim_plat_data  balong_sim2_plat_data = {
    .name = SIM2,
    .sim_status = 0,
#ifdef SIM_HPD
    .sim_hpd_out_f = SIM2_HPD_OUT_F_TYPE,
    .sim_hpd_in_f = SIM2_HPD_IN_F_TYPE,
#endif
};

static struct platform_device balong_sim1_device = {
	.name		= "balong_sim",
	.id = 1,
	.dev = {
		.platform_data = &balong_sim1_plat_data,
	},
};

static struct platform_device balong_sim2_device = {
	.name		= "balong_sim",
	.id = 2,
	.dev = {
		.platform_data = &balong_sim2_plat_data,
	},
};

static struct platform_device *plat_sim_dev[] __initdata = {
	&balong_sim1_device,
	&balong_sim2_device
};

static int __init balong_sim_dev_init(void)
{
    int ret = 0;
    ret = platform_add_devices(plat_sim_dev, ARRAY_SIZE(plat_sim_dev));
    return ret;
}

arch_initcall(balong_sim_dev_init);
