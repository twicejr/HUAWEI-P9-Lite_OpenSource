/*
 * arch/arm/mach-hi6620/dev_modem_ctl.c
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
#include <mach/balong_power.h>
#include <linux/platform_device.h>

static struct balong_power_plat_data  balong_plat_data = {
    .modem_state = MODEM_NOT_READY,
};

static struct platform_device balong_power_device = {
	.name		= "balong_power",
	.id = -1,
	.dev = {
		.platform_data = &balong_plat_data,
	},
};
static int __init balong_power_dev_init(void)
{
    int ret = 0;
    ret = platform_device_register(&balong_power_device);
    return ret;
}
static void __init balong_power_dev_exit(void)
{
    platform_device_unregister(&balong_power_device);
}
module_init(balong_power_dev_init);
module_exit(balong_power_dev_exit);
