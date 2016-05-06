/*
 * Device driver for PMU DRIVER	 in HI6xxx SOC
 *
 * Copyright (c) 2011 Hisilicon Co. Ltd
 *
 * information about chip-hi6552 which not in hixxx_pmic dts
 *
 */
 #ifndef __HISI_FREQ_AUTODOWN_H__
#define __HISI_FREQ_AUTODOWN_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/of_platform.h>
#include <linux/string.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/device.h>
#include <linux/spinlock.h>
#define FREQ_AUTODOWN_DTS_ATTR_LEN 64
#define FREQ_AUTODOWN_DTS_REG_NUM 2
#define CRGPERI_ADDR_OFFSET			0x04
#define CRGPERI_ADDR_STATE			0x08
#define INVALID_REG_ADDR 0xDEAD
#ifndef BIT
#define BIT(n)	(1 << (n))
#endif
#define BITMSK(x)                   (BIT(x) << 16)

#if 1
#define BRAND_DEBUG(fmt, ...) pr_info("[Info]:%s(%d): " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define BRAND_DEBUG(fmt, ...)
#endif

enum enable_state {
	DISABLE,
	ENABLE,
};

enum open_state {
	CLOSE,
	OPEN,
};

struct freq_autodown_info {
    u32 disable_bypass_reg;
	u32 disable_bypass_bit;
    u32 enable_clock_reg;
	u32 enable_clock_bit;
};

typedef struct freq_autodown_desc
{
	struct resource	*res;
	struct device *dev;
	void __iomem *regs;
	struct freq_autodown_info *freq_info;
    unsigned int freq_autodown_num;
    unsigned int freq_autodown_state;
    char** freq_autodown_name;
    spinlock_t      lock;
}FREQ_AUTODOWN_DESC;

#endif

