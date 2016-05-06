/*
 *
 * arch/arm/mach-k3v2/include/mach/clock.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * Clock definitions and inline macros
 *
 */
#ifndef __MACH_CLOCK_H
#define __MACH_CLOCK_H

#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/clkdev.h>
#include <asm/clkdev.h>

#define DISABLE_REG_OFFSET 0x04
#define ENASTAT_REG_OFFSET 0x08

struct clk;
struct clksel {
	struct clk	*sel_parent;
	/* the value should be set to the registers' enable bit */
	int	sel_val;
	int	parent_min;
	int	parent_max;
};

enum clk_state {
	UNINITIALIZED = 0,
	ON,
	OFF,
};

struct clk_ops {
	void	(*init)(struct clk *);
	int	(*enable)(struct clk *clk);
	int	(*disable)(struct clk *clk);
	long	(*round_rate)(struct clk *clk, long rate);
	int	(*set_rate)(struct clk *clk, unsigned rate);
	int	(*set_parent)(struct clk *clk, struct clk *parent);
	int	(*is_enabled)(struct clk *clk);
	void	(*reset)(struct clk *, bool);
#ifdef CONFIG_DEBUG_FS
	char *(*check_enreg)(struct clk *clk);
	char *(*check_selreg)(struct clk *clk);
	char *(*check_divreg)(struct clk *clk);
#endif
};

struct clk {
#ifdef CONFIG_DEBUG_FS
	struct dentry	*dent;
	struct dentry	*parent_dent;
#endif
	char	*name;
	unsigned int	refcnt;
	enum clk_state	state;
	unsigned long	rate;
	unsigned int	min_rate;
	unsigned int	max_rate;
	bool 	set;

	struct clk	*parent;
	struct clksel	*sel_parents;
	struct clk	**friends;

	struct clk_ops	*ops;

	void __iomem	*enable_reg;
	u8	enable_bit;

	void __iomem	*clksel_reg;
	u32	clksel_mask;
	u32	clksel_set_valid;

	void __iomem	*clkdiv_reg;
	u32	clkdiv_mask;
	s8	clkdiv_set_valid;

	spinlock_t	spinlock;
	struct list_head	node;
};

struct k3v2_clk_init_table {
	char *name;
	char *parent;
	unsigned long rate;
	bool enabled;
};

#define MACRO_CLK(_clk, _clkname, _state, _rate, _min_rate, _max_rate, _parent, \
		  _friends, _sel_parents, _enable_reg, _enable_bit, _clksel_reg, _clksel_mask, \
		  _clksel_set_valid, _clkdiv_reg, _clkdiv_mask, _clkdiv_set_valid) \
static struct clk _clk = {\
    .name = _clkname,\
	.refcnt = 0,\
	.state = _state,\
	.rate = _rate,\
	.min_rate = _min_rate,\
	.max_rate = _max_rate,\
	.parent = _parent,\
	.friends = _friends,\
	.ops = &clock_ops,\
	.sel_parents = _sel_parents,\
	.enable_reg = (void __iomem	*)_enable_reg,\
	.enable_bit = _enable_bit,\
	.clksel_reg = (void __iomem	*)_clksel_reg,\
	.clksel_mask = _clksel_mask,\
	.clksel_set_valid = _clksel_set_valid,\
	.clkdiv_reg = (void __iomem	*)_clkdiv_reg,\
	.clkdiv_mask = _clkdiv_mask,\
	.clkdiv_set_valid = _clkdiv_set_valid,\
	.set = false\
};

#define PLL_CLK(_clk, _clkname, _state, _rate, _min_rate, _max_rate, _enable_reg, _enable_bit) \
static struct clk _clk = {\
    .name = _clkname,\
	.refcnt = 0,\
	.state = _state,\
	.rate = _rate,\
	.min_rate = _min_rate,\
	.max_rate = _max_rate,\
	.ops = &pll_clock_ops,\
	.enable_reg = (void __iomem	*)_enable_reg,\
	.enable_bit = _enable_bit,\
	.set = false\
};

#define PMU_CLK(_clk, _clkname, _state, _rate, _min_rate, _max_rate, _enable_reg, _enable_bit) \
static struct clk _clk = {\
    .name = _clkname,\
	.refcnt = 0,\
	.state = _state,\
	.rate = _rate,\
	.min_rate = _min_rate,\
	.max_rate = _max_rate,\
	.ops = &pmu_clock_ops,\
	.enable_reg = (void __iomem	*)_enable_reg,\
	.enable_bit = _enable_bit,\
	.set = false\
};

#ifdef CONFIG_DEBUG_FS
char *k3v2_enabled_check(struct clk *c);
char *k3v2_source_check(struct clk *c);
char *k3v2_rate_check(struct clk *c);
#endif

int clk_enable_set(struct clk *clk);
int clk_disable_set(struct clk *clk);

int k3v2_clk_enable(struct clk *clk);
int k3v2_clk_disable(struct clk *clk);
int k3v2_clk_set_parent(struct clk *clk, struct clk *parent);
long k3v2_clk_round_rate(struct clk *clk, long rate);
int k3v2_clk_set_rate(struct clk *clk, unsigned rate);

extern struct clk_ops clock_ops;

extern struct clk_ops pll_clock_ops;

extern struct clk_ops pmu_clock_ops;

extern struct clk_lookup k3v2_clk_lookups[];

void k3v2_clk_init_from_table(struct k3v2_clk_init_table *table);
void k3v2_init_clocks(void);
void clk_init(struct clk *clk);
void k3v2_init_clock(void);
struct clk *k3v2_get_clock_by_name(const char *name);

#endif
