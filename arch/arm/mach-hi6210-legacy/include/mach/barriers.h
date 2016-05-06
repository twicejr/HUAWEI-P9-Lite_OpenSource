/*
 *
 * arch/arm/mach-k3v2/include/mach/barriers.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */

#ifndef __MACH_BARRIERS_H
#define __MACH_BARRIERS_H

#include <asm/outercache.h>

#define rmb()		dmb()
#define wmb()		do { dsb(); outer_sync(); } while (0)
#define mb()		wmb()

#endif
