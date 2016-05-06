/*
 *
 * arch/arm/mach-k3v2/include/mach/clkdev.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * Clockdev definitions and inline macros
 *
 */
#ifndef __MACH_K3V2_CLKDEV_H
#define __MACH_K3V2_CLKDEV_H


struct clk;

#define __clk_get(clk) ({ 1; })
#define __clk_put(clk) do { } while (0)

#endif
