/*
 * arch/arm/mach-k3v2/k3v2_clocks_ops.c
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */

#include "mach/clock.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <mach/platform.h>
#include <mach/boardid.h>
#include <linux/clkdev.h>
#include <asm/clkdev.h>
#include <mach/early-debug.h>
#include <mach/pmussi_drv.h>

static LIST_HEAD(clocks);

/*
 * this function is used to check whether the parent clock
 * is this clock's source, and get the clksel
 */
static struct clksel *k3v2_getclksel_by_parent(struct clk *clk,
	struct clk *parent_clk)
{
	struct clksel *clks = clk->sel_parents;

	if (clks) {
		while (clks->sel_parent) {
			if (clks->sel_parent == parent_clk)
				break;
			clks++;
		}

		if (!clks->sel_parent) {
			pr_err(" Could not find parent clock for %s.\r\n", clk->name);
			return NULL;
		}
	}

	return clks;
}

#ifdef CONFIG_DEBUG_FS
static char g_clk_status[5][10] = {"NOREG", "OK", "ERR", "uninit", "NODIV"};

char *k3v2_enabled_check(struct clk *c)
{
	int regvalue = 0;

	if (!c->enable_reg)
		return g_clk_status[0];

	if (c->refcnt > 0) {
		regvalue = readl(c->enable_reg + ENASTAT_REG_OFFSET)
			& (1 << c->enable_bit);
		regvalue = regvalue >> c->enable_bit;

		if (regvalue == 0x01)
			return g_clk_status[1];
		else if (regvalue == 0x00)
			return g_clk_status[2];

	} else if (c->refcnt == 0) {
		if ((c->state != ON) && (c->state != OFF)) {
			return g_clk_status[3];
		} else {
			regvalue = readl(c->enable_reg + ENASTAT_REG_OFFSET)
				& (1 << c->enable_bit);
			regvalue = regvalue >> c->enable_bit;
			if (regvalue == 0x01)
				return g_clk_status[2];
			else
				return g_clk_status[1];
		}
	}

	return g_clk_status[2];
}

char *k3v2_source_check(struct clk *c)
{
	int regvalue = 0;
	char *result = g_clk_status[2];
	struct clksel *clks = c->sel_parents;

	if (!c->clksel_reg)
		return g_clk_status[0];

	if ((c->state != ON) && (c->state != OFF))
		return g_clk_status[3];

	regvalue = readl(c->clksel_reg) & c->clksel_mask;
	regvalue = regvalue >> __ffs(c->clksel_mask);

	if (clks) {
		while (clks->sel_parent) {
			if (clks->sel_parent == c->parent)
				break;
			clks++;
		}

		if (regvalue == clks->sel_val)
			result = g_clk_status[1];
		else
			result = g_clk_status[2];
	}

	return result;
}

char *k3v2_rate_check(struct clk *c)
{
	int regvalue = 0;
	int div_value;
	char *result = NULL;
	struct clksel *clks = c->sel_parents;

	if (!c->clkdiv_reg)
		return g_clk_status[0];

	if ((c->state != ON) && (c->state != OFF))
		return g_clk_status[3];

	if (clks) {
		while (clks->sel_parent) {
			if (clks->sel_parent == c->parent)
				break;
			clks++;
		}
	}

	if (clks && (clks->parent_min == clks->parent_max))
		return g_clk_status[4];

	regvalue = readl(c->clkdiv_reg) & c->clkdiv_mask;
	regvalue = regvalue >> __ffs(c->clkdiv_mask);

	/* h0:1,h1:2,...... */
	div_value = c->parent->rate / c->rate - 1;

	if (regvalue == div_value)
		result = g_clk_status[1];
	else
		result = g_clk_status[2];

	return result;
}
#endif

int pll_enable_set(struct clk *clk)
{
	int i = 0;
	int val = 0;
	int ret = 0;

	if (clk->enable_reg == NULL) {
		pr_warning("CLOCK:%s's enable register is NULL.\n", clk->name);

		return -1;
	}

	while (clk->friends && clk->friends[i]) {
		ret = clk_enable(clk->friends[i++]);
		if (ret) {
			WARN(1, "CLOCK:Disable friend failed.\r\n");
		}
	}

	i = 1000;

	/* enable clock with protecting other enable bits  */
    pr_warning("CLOCK:%s's reg:0x%x.\n", clk->name,clk->enable_reg);
    val = readl(clk->enable_reg);
	val |= 1 << clk->enable_bit;
    writel(val, clk->enable_reg);

    udelay(100);

	/* check status */
	while (!val && i) {
		val = readl(clk->enable_reg) & (1 << 28);
        udelay(100);
		i--;
	}

	if (i == 0) {
		WARN(1, "CLOCK:Attempting to write clock enable register 1000 times.\r\n");
		return -1;
	}

	return 0;
}

int pll_disable_set(struct clk *clk)
{
	int i = 1000;
	int val = 0;

	if (clk->enable_reg == NULL) {
		pr_warning("CLOCK:%s's disable register is NULL.\n", clk->name);

		return -1;
	}

	/* disable clock with protecting other enable bits  */
    val = readl(clk->enable_reg);
	val &= ~(1 << clk->enable_bit);
    writel(val, clk->enable_reg);

    udelay(200);

	/* no check status */
	while (clk->friends && clk->friends[i]) {
		clk_disable(clk->friends[i++]);
	}

	return 0;
}

int pll_clk_enable(struct clk *clk)
{
	BUG_ON(clk == NULL);

	/* enable clock */
	int ret = pll_enable_set(clk);

	return ret;
}

int pll_clk_disable(struct clk *clk)
{
	BUG_ON(clk == NULL);

	/* disable clock */
	int ret = pll_disable_set(clk);

	return ret;
}

int pmu_clk_enable(struct clk *clk)
{
	unsigned char regval;

	BUG_ON(clk == NULL);

	/* enable clock */
	regval = pmussi_reg_read((unsigned int)clk->enable_reg);

	regval |= (0x1 << clk->enable_bit);

	pmussi_reg_write((unsigned int)clk->enable_reg,regval);

	return 0;
}

int pmu_clk_disable(struct clk *clk)
{
	unsigned char regval;

	BUG_ON(clk == NULL);

	/* disable clock */
	regval = pmussi_reg_read((unsigned int)clk->enable_reg);

	regval &= ~(0x1 << clk->enable_bit);

	pmussi_reg_write((unsigned int)clk->enable_reg,regval);

	return 0;
}

int clk_enable_set(struct clk *clk)
{
	int i = 0;
	int val = 0;
	int ret = 0;

	if (clk->enable_reg == NULL) {
		pr_warning("CLOCK:%s's enable register is NULL.\n", clk->name);

		return -1;
	}

	while (clk->friends && clk->friends[i]) {
		ret = clk_enable(clk->friends[i++]);
		if (ret) {
			WARN(1, "CLOCK:Disable friend failed.\r\n");
		}
	}

	i = 1000;

	/* enable clock with protecting other enable bits  */
	val = 1 << clk->enable_bit;
    	writel(val, clk->enable_reg);
	val = readl(clk->enable_reg + ENASTAT_REG_OFFSET)
		& (1 << clk->enable_bit);

#if defined(RUN_IN_VPA)
#else
	/* check status */
	while (!val && i) {
		val = 1 << clk->enable_bit;
     	writel(val, clk->enable_reg);
		val = readl(clk->enable_reg + ENASTAT_REG_OFFSET)
			& (1 << clk->enable_bit);

		i--;
	}

	if (i == 0) {
		WARN(1, "CLOCK:Attempting to write clock enable register 1000 times.\r\n");
		return -1;
	}
#endif

	return 0;
}

int clk_disable_set(struct clk *clk)
{
	int i = 1000;
	int val = 0;

	if (clk->enable_reg == NULL) {
		pr_warning("CLOCK:%s's disable register is NULL.\n", clk->name);

		return -1;
	}

	/* disable clock with protecting other enable bits  */
	val = 1 << clk->enable_bit;
    writel(val, clk->enable_reg + DISABLE_REG_OFFSET);
	val = readl(clk->enable_reg + ENASTAT_REG_OFFSET) & (1<<clk->enable_bit);

#if defined(RUN_IN_VPA)
#else
	/* check status */
	while (val && i) {
		val = 1 << clk->enable_bit;
		writel(val, clk->enable_reg + DISABLE_REG_OFFSET);
		val = readl(clk->enable_reg + ENASTAT_REG_OFFSET) & (1 << clk->enable_bit);

		i--;
	}

	if (i == 0) {
		WARN(1, "CLOCK:Attempting to write clock disable register 1000 times.\r\n");
		return -1;
	}
#endif

	i = 0;
	while (clk->friends && clk->friends[i]) {
		clk_disable(clk->friends[i++]);
	}

	return 0;
}

int k3v2_clk_enable(struct clk *clk)
{
	BUG_ON(clk == NULL);

	/* enable clock */
	int ret = clk_enable_set(clk);

	return ret;
}

int k3v2_clk_disable(struct clk *clk)
{
	BUG_ON(clk == NULL);

	/* disable clock */
	int ret = clk_disable_set(clk);

	return ret;
}

int k3v2_clk_write_sel_register(struct clk *clk, struct clk *parent)
{
	u32 v;
	struct clksel *clks = NULL;

	BUG_ON(clk == NULL || parent == NULL);

	/* if there is no parent, parent setting is a invalid operation ,return -1 as error number. */
	if (clk->parent == NULL) {
		pr_warning("CLOCK:%s has no parent, it's a source clock.\n", clk->name);

		return -1;
	}

	/* if there is only one parent, the clksel_reg must be NULL */
	if (clk->clksel_reg == NULL) {
		if (clk->parent == parent) {
			return 0;
		} else { /* the parent is not this clock's source, this is a invalid operation */
			pr_warning("CLOCK:there is only one parent,"
				"can't set the parent as %s.\n", parent->name);

			return -1;
		}
	}

	/* find clksel from the clock source */
	clks = k3v2_getclksel_by_parent(clk, parent);
	if (!clks) {
		pr_err("CLOCK:%s is not %s's parent.\r\n", parent->name, clk->name);

		return -1;/*this clock is not the parent*/
	}

	//pr_err("clksel_set_valid 0x%x\n mask: 0x%x\n sel: 0x%x\n",clk->clksel_set_valid,clk->clksel_mask,clks->sel_val);
	/* set the register's bit and valid-bit to get the clock source */
	if (clk->clksel_set_valid != -1) {
		v = (clks->sel_val << __ffs(clk->clksel_mask))
			| (clk->clksel_set_valid);
	} else {
		v = (clks->sel_val << __ffs(clk->clksel_mask));
	}

	writel(v, clk->clksel_reg);

	if (!clk->clkdiv_reg)
	{
	    	clk->rate = parent->rate;
	}
	else
	{
	    	v = readl(clk->clkdiv_reg) | clk->clkdiv_mask;
	    	clk->rate = parent->rate / (v + 1);
	}

	return 0;
}

int k3v2_clk_set_parent(struct clk *clk, struct clk *parent)
{
	int ret = k3v2_clk_write_sel_register(clk, parent);

	if (ret < 0) {
		pr_warning("CLOCK: %s set parent clock source fail.\n", clk->name);

		return -1;
	}
	clk->parent = parent;

	if (clk->clkdiv_reg == NULL)
		clk->rate = clk->parent->rate;

	return 0;
}

/* this function is used to find the right parent which can provide the rate */
static struct clk *k3v2_clk_find_parent_from_selparents(struct clk *clk, unsigned rate)
{
	struct clksel *clks = NULL;
	struct clk *clkparent = NULL;

	BUG_ON(clk == NULL);
	BUG_ON(clk->sel_parents == NULL);

	for (clks = clk->sel_parents; clks->sel_parent; clks++) {

		/* this rate can be brought by this parent */
		if (rate <= clks->parent_max && rate >= clks->parent_min) {
			clkparent = clks->sel_parent;
			break; /* Found the requested parent */
		}
	}

	return clkparent;
}

long _k3v2_clk_round_rate(struct clk *clk, long rate)
{
	int ret = 0;
	struct clk *clkparent = NULL;

	printk("entering _k3v2_clk_round_rate\n");
	/* find parent */
	clkparent = k3v2_clk_find_parent_from_selparents(clk, rate);

	/* no parent can offer this rate */
	if (clkparent == NULL) {
		pr_warning("CLOCK:no parent can offer rate:%ld to %s.\r\n",
			rate, clk->name);

		return -1;
	}

	/*check whether this clock has been enabled*/
	if (clk->refcnt == 0)
		ret = -1;

	/* change the parent , if the clk->sel_parents == NULL,
	 * clk->parent must be the same as clkparent.
	 */
	if (ret >= 0) {
		if (clk->parent != clkparent) {
			/* disable current parents */
			clk_disable(clk->parent);
			ret = clk_enable(clkparent);
			if (ret >= 0) {
				if (!clk->ops || !clk->ops->set_parent) {
					pr_warning("CLOCK:%s has no parent \
						ops.\n", clk->name);
					return -1;
				}
				clk->ops->set_parent(clk, clkparent);
			}
		}
	} else { /* if clock has't enabled,don't need to count */
		if (!clk->ops || !clk->ops->set_parent) {
			pr_warning("CLOCK:%s has no parent ops.\n", clk->name);
			return -1;
		}
		clk->ops->set_parent(clk, clkparent);
	}
	printk("exit _k3v2_clk_round_rate\n");

	return 0;
}

/* get the right rate */
long k3v2_clk_round_rate(struct clk *clk, long rate)
{
	int ret = 0;
	unsigned int div = 0;
	unsigned int modvalue = 0;
	struct clksel *clks = NULL;

	/*printk("entering k3v2_clk_round_rate\n");*/

	BUG_ON(clk == NULL);

	/*printk("clk != NULL\n");*/

	if (rate < clk->min_rate || rate > clk->max_rate) {
		pr_err("CLOCK:%ld is invalid for %s.\n", rate, clk->name);

		return -1;
	}

	if (!clk->parent) {
		pr_err("CLOCK:%s has no parent, don't need to set rate.\n", clk->name);

		return -1;
	}

	/* the clock's parent clock is responsible for switch source clock  */
	if (!clk->sel_parents && clk->parent->sel_parents)
	{
		clks = k3v2_getclksel_by_parent(clk->parent, clk->parent->parent);
	    if (clks && rate > clks->parent_max)
	    {
	    	ret = _k3v2_clk_round_rate(clk->parent, rate);

	    	if (ret < 0)
				return ret;
			else
				goto round_rate;
	    }
	}

	/*printk("--------------------------\n");*/

	/*
	 * check whether the current parent provide this rate,
	 * if can't , find another one.
	 */

	if (clk->sel_parents)
	{
		clks = k3v2_getclksel_by_parent(clk, clk->parent);
		if (clks && rate >= clks->parent_min && rate <= clks->parent_max)
			goto round_rate;

		ret = _k3v2_clk_round_rate(clk, rate);
	}

	if (ret < 0)
		return ret;

round_rate:
	div = clk->parent->rate / rate;
	modvalue = clk->parent->rate % rate;
	if (modvalue != 0)
		rate = clk->parent->rate / (div + 1);
	else
		rate = clk->parent->rate / div;

	return rate;
}

/* set the div for the rate ,the parent must be set firstly */
int k3v2_clk_set_rate(struct clk *clk, unsigned rate)
{
	unsigned int div = 0;
	u32 v = 0;
	struct clksel *clks = NULL;

	clks = k3v2_getclksel_by_parent(clk, clk->parent);
	if (clks) {
		if (clks->parent_min == clks->parent_max) {
			pr_warning("CLOCK:the source clock can't be divided  "
			"the rate is constant.\n");
			clk->rate = clk->parent->rate;
			return 0;
		}
	}

	if (clk->clkdiv_reg != NULL) {

		/* calculate the div */
		div = clk->parent->rate / rate;

		/* protect other bits of clkdiv_reg */
		v = readl(clk->clkdiv_reg);
		v &= ~clk->clkdiv_mask;

		/* set division into clock division register with valid-bit */
		if (clk->clkdiv_set_valid != -1) {
			/* the function __ffs() is used to find the first non zero bit,
		 	* and it is defined at include/asm-generic/bitops/__ffs.h
		 	*/
			v = ((div - 1) << (__ffs(clk->clkdiv_mask)))
				| (1 << clk->clkdiv_set_valid);
		} else { /* only set division into clock division register */
			v = ((div - 1) << (__ffs(clk->clkdiv_mask)));
		}
		writel(v, clk->clkdiv_reg);

		clk->rate = rate;

                /*pr_info("CLOCK:%s's rate has been set as %ld.\n", clk->name, clk->rate);*/

		return 0;
	}
	pr_warning("CLOCK:%s rate set failed.\r\n", clk->name);

	return -1;
}

unsigned int k3v2_clk_get_rate(struct clk *clk)
{
	return clk->rate;
}

struct clk_ops clock_ops = {
	.enable = k3v2_clk_enable,
	.disable = k3v2_clk_disable,
	.round_rate = k3v2_clk_round_rate,
	.set_rate = k3v2_clk_set_rate,
	.set_parent = k3v2_clk_set_parent,
#ifdef CONFIG_DEBUG_FS
	.check_enreg = k3v2_enabled_check,
	.check_selreg = k3v2_source_check,
	.check_divreg = k3v2_rate_check,
#endif
};

struct clk_ops pll_clock_ops = {
	.enable = pll_clk_enable,
	.disable = pll_clk_disable,
};

struct clk_ops pmu_clock_ops = {
	.enable = pmu_clk_enable,
	.disable = pmu_clk_disable,
};

void __init k3v2_init_clocks(void)
{
	int i = 0;

	struct clk_lookup *cl_lookups = &k3v2_clk_lookups[0];
	struct clk_lookup *cl = NULL;

	while((cl_lookups[i].clk != NULL) ) {
		//printk("clk name:%s\n", cl_lookups[i].clk->name);
		cl = &cl_lookups[i++];
		clk_init(cl->clk);
		clkdev_add(cl);
	}
}

