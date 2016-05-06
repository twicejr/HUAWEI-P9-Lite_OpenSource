/*
 * arch/arm/mach-k3v2/include/mach/dev_bt.h
 *
 * Copyright (C) 2012 Hisilicon Co. Ltd.
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

#ifndef DEV_BT_H
#define DEV_BT_H

struct bt_dev_info
{
    unsigned bt_en;             /* BT enable pin */
    unsigned bt_rst;            /* BT reset pin */
    unsigned bt_wake_host;      /* BT wakeup host pin */
    unsigned host_wake_bt;      /* host wakeup BT pin */
    char *iomux_pwr;
    char *iomux_pm;
    char *clock_name;
    char *regulator_name;
};

#endif
