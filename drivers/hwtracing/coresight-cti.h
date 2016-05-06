/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _LINUX_CORESIGHT_CTI_H
#define _LINUX_CORESIGHT_CTI_H

#include <linux/list.h>

#define cti_writel(drvdata, val, off)	writel_relaxed((val), drvdata->base + off)
#define cti_readl(drvdata, off)		readl_relaxed(drvdata->base + off)

#define CTI_LOCK(drvdata)		CS_LOCK(drvdata->base)
#define CTI_UNLOCK(drvdata)	CS_UNLOCK(drvdata->base)

#define CTICONTROL		(0x000)
#define CTIINTACK		(0x010)
#define CTIAPPSET		(0x014)
#define CTIAPPCLEAR		(0x018)
#define CTIAPPPULSE		(0x01C)
#define CTIINEN(n)		(0x020 + (n * 4))
#define CTIOUTEN(n)		(0x0A0 + (n * 4))
#define CTITRIGINSTATUS		(0x130)
#define CTITRIGOUTSTATUS	(0x134)
#define CTICHINSTATUS		(0x138)
#define CTICHOUTSTATUS		(0x13C)
#define CTIGATE			(0x140)
#define ASICCTL			(0x144)
#define ITCHINACK		(0xEDC)
#define ITTRIGINACK		(0xEE0)
#define ITCHOUT			(0xEE4)
#define ITTRIGOUT		(0xEE8)
#define ITCHOUTACK		(0xEEC)
#define ITTRIGOUTACK		(0xEF0)
#define ITCHIN			(0xEF4)
#define ITTRIGIN		(0xEF8)

#define CTI_MAX_TRIGGERS	(8)
#define CTI_MAX_CHANNELS	(4)
#define BM(lsb, msb)		((BIT(msb) - BIT(lsb)) + BIT(msb))
#define BVAL(val, n)		((val & BIT(n)) >> n)
#define MAX_CTI_DEV (10)
#define ETM_STOP_CH (0)
#define ETM_STOP_RES (3)

#define to_cti_drvdata(c) container_of(c, struct cti_drvdata, cti)
struct coresight_cti_data {
	int nr_ctis;
	const char **names;
};

struct coresight_cti {
	const char *name;
	struct list_head link;
};
struct cti_state {
	unsigned int cticontrol;
	unsigned int ctiappset;
	unsigned int ctigate;
	unsigned int ctiinen[CTI_MAX_TRIGGERS];
	unsigned int ctiouten[CTI_MAX_TRIGGERS];
};

struct cti_pctrl {
	struct pinctrl *pctrl;
	int trig;
};

struct cti_drvdata {
	void __iomem *base;
	struct device *dev;
	struct coresight_device *csdev;
	struct clk *clk;
	spinlock_t spinlock;
	struct mutex mutex;
	struct coresight_cti cti;
	int refcnt;
	int cpu;
	bool cti_save;
	bool cti_hwclk;
	bool l2_off;
	struct cti_state *state;
};

#define CONFIG_CORESIGHT_CTI
#ifdef CONFIG_CORESIGHT_CTI
extern struct coresight_cti *coresight_cti_get(const char *name);
extern void coresight_cti_put(struct coresight_cti *cti);
extern int coresight_cti_map_trigin(struct coresight_cti *cti, int trig,
				    int ch);
extern int coresight_cti_map_trigout(struct coresight_cti *cti, int trig,
				     int ch);
extern void coresight_cti_unmap_trigin(struct coresight_cti *cti, int trig,
				       int ch);
extern void coresight_cti_unmap_trigout(struct coresight_cti *cti, int trig,
					int ch);
extern void coresight_cti_reset(struct coresight_cti *cti);
extern int coresight_cti_set_trig(struct coresight_cti *cti, int ch);
extern void coresight_cti_clear_trig(struct coresight_cti *cti, int ch);
extern int coresight_cti_pulse_trig(struct coresight_cti *cti, int ch);
extern int coresight_cti_enable_gate(struct coresight_cti *cti, int ch);
extern void coresight_cti_disable_gate(struct coresight_cti *cti, int ch);
extern void coresight_cti_ctx_save(void);
extern void coresight_cti_ctx_restore(void);
extern int coresight_cti_ack_trig(struct coresight_cti *cti, int trig);
extern struct coresight_cti *coresight_cti_get_bycpuid(int cpu);
extern int coresight_cti_debug_msg(struct coresight_cti *cti);
#else
static inline struct coresight_cti *coresight_cti_get(const char *name)
{
	return NULL;
}

static inline void coresight_cti_put(struct coresight_cti *cti)
{
}

static inline int coresight_cti_map_trigin(struct coresight_cti *cti, int trig,
					   int ch)
{
	return -ENOSYS;
}

static inline int coresight_cti_map_trigout(struct coresight_cti *cti, int trig,
					    int ch)
{
	return -ENOSYS;
}

static inline void coresight_cti_unmap_trigin(struct coresight_cti *cti,
					      int trig, int ch)
{
}

static inline void coresight_cti_unmap_trigout(struct coresight_cti *cti,
					       int trig, int ch)
{
}

static inline void coresight_cti_reset(struct coresight_cti *cti)
{
}

static inline int coresight_cti_set_trig(struct coresight_cti *cti, int ch)
{
	return -ENOSYS;
}

static inline void coresight_cti_clear_trig(struct coresight_cti *cti, int ch)
{
}

static inline int coresight_cti_pulse_trig(struct coresight_cti *cti, int ch)
{
	return -ENOSYS;
}

static inline int coresight_cti_enable_gate(struct coresight_cti *cti, int ch)
{
	return -ENOSYS;
}

static inline void coresight_cti_disable_gate(struct coresight_cti *cti, int ch)
{
}

static inline void coresight_cti_ctx_save(void)
{
}

static inline void coresight_cti_ctx_restore(void)
{
}

static inline int coresight_cti_ack_trig(struct coresight_cti *cti, int trig)
{
	return -ENOSYS;
}
#endif

#endif
