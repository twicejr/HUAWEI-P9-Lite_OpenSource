/*
 * Hisilicon Hi3620 MIPI DSI clock driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 * Copyright (c) 2012-2013 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <linux/kernel.h>
#include <linux/clk-provider.h>
#include <linux/clk-private.h>
#include <linux/clkdev.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/platform_data/hi3620-dsi.h>

#define DSI_CLKMGR_CFG		0x908
#define DSI_PHY_RSTZ		0x954

enum {
	HI3620_EDC,
};

struct clk_phy {
	struct clk_hw	hw;
	void __iomem	*reg_base;
	unsigned int	mult;
	unsigned int	div;
};

struct clk_esc {
	struct clk_hw	hw;
	void __iomem	*reg_base;
	unsigned int	div;
};

struct hs_clk {
	void __iomem	*edc;
	spinlock_t	lock;
};

static void __iomem __init *hi3620_init_clocks(struct device_node *np);

static struct hs_clk hi3620_clk;

struct phy_mult {
	int	mult;
	int	cp_current;
	int	lpf_ctrl;
};

static unsigned long clk_phy_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_phy *phy = container_of(hw, struct clk_phy, hw);
	unsigned long long int rate;

	if (!phy->div)
		return 0;
	rate = (unsigned long long int)parent_rate * phy->mult;
	do_div(rate, phy->div);
	return (unsigned long)rate;
}

static long clk_phy_round_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *prate)
{
	struct clk_phy *phy = container_of(hw, struct clk_phy, hw);
	struct clk *clk_parent;
	unsigned long long int mult, new_rate;

	clk_parent = __clk_get_parent(hw->clk);
	*prate = __clk_get_rate(clk_parent);
	mult = (unsigned long long int)rate * phy->div;
	do_div(mult, *prate);
	new_rate = *prate * mult;
	do_div(new_rate, phy->div);
	return (unsigned long)new_rate;
}

static int clk_phy_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_phy *phy = container_of(hw, struct clk_phy, hw);
	void __iomem *base = phy->reg_base;
	unsigned long long int mult;
	unsigned char cp_current, lpf_ctrl;
	int i;
	struct phy_mult m[] = {	{32, 0x6, 0x10}, {64, 0x6, 0x10},
				{128, 0xc, 0x8}, {256, 0x4, 0x4},
				{512, 0x0, 0x1}, {768, 0x1, 0x1},
				{1000, 0x2, 0x1}, };
	mult = (unsigned long long int)rate * phy->div;
	do_div(mult, parent_rate);
	phy->mult = (unsigned int)mult;

	for (i = 0; i < ARRAY_SIZE(m); i++) {
		if (phy->mult <= m[i].mult) {
			cp_current = m[i].cp_current;
			lpf_ctrl = m[i].lpf_ctrl;
			break;
		}
	}
	if (i >= ARRAY_SIZE(m))
		return -EINVAL;
	lpf_ctrl |= 0xc0;	/* bypass CP & LPF default values */
	/* write CP current */
	hi3620_dsi_phy_write(base, 0x11, cp_current);
	/* write LPF control */
	hi3620_dsi_phy_write(base, 0x12, lpf_ctrl);
	/* configure N and M factors effectively */
	hi3620_dsi_phy_write(base, 0x19, 0x33);
	/* write N divider */
	hi3620_dsi_phy_write(base, 0x17, phy->div - 1);
	/* write M multiplier 1 */
	hi3620_dsi_phy_write(base, 0x18, (phy->mult - 1) & 0x1f);
	/* write M multiplier 2 */
	hi3620_dsi_phy_write(base, 0x18, ((phy->mult - 1) >> 5) | 0x80);
	/* set PLL unlocking filter */
	hi3620_dsi_phy_write(base, 0x16, 0xff);
	return 0;
}

struct clk_ops clk_phy_ops = {
	.round_rate = clk_phy_round_rate,
	.set_rate = clk_phy_set_rate,
	.recalc_rate = clk_phy_recalc_rate,
};

static struct clk *clk_phy_register(struct device *dev, const char *name,
				    const char *parent_name, void __iomem *reg,
				    unsigned long flags)
{
	struct clk_phy *phy;
	struct clk_init_data init;
	struct clk *clk;

	phy = kzalloc(sizeof(*phy), GFP_KERNEL);
	if (!phy) {
		pr_err("%s: could not allocate dsi phy clk\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	/* struct clk_phy assignments */
	phy->hw.init = &init;
	phy->div = 13;	/* since parent rate is always 26MHz */
	phy->reg_base = reg;

	init.name = name;
	init.ops = &clk_phy_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_register(dev, &phy->hw);

	if (IS_ERR(clk))
		kfree(phy);

	return clk;
}

void __init hi3620_phy_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	void __iomem *reg_base;

	reg_base = hi3620_init_clocks(np);
	if (!reg_base)
		return;
	if (of_property_read_string(np, "clock-output-names", &clk_name))
		return;
	/* gate only has the fixed parent */
	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names)
		return;
	parent_names[0] = of_clk_get_parent_name(np, 0);

	clk = clk_phy_register(NULL, clk_name, parent_names[0], reg_base, 0);
	if (IS_ERR(clk))
		goto err;
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;
err:
	kfree(parent_names);
}

static int find_best_esc_divider(unsigned long parent_rate)
{
	unsigned int max_rate = 20000000;	/* 20MHz */
	unsigned int target_rate = 10000000;	/* 10MHz */
	unsigned int div, out_rate;

	div = parent_rate / target_rate;
	for (; div > 0; div--) {
		out_rate = parent_rate / div;
		if (out_rate < max_rate)
			break;
	}
	if (div <= 0)
		return 0;
	return div;
}

static unsigned long clk_esc_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_esc *esc = container_of(hw, struct clk_esc, hw);
	unsigned int div;

	if (!esc->div)
		div = find_best_esc_divider(parent_rate);
	else
		div = esc->div;
	if (!div)
		return 0;
	return parent_rate / div;
}

static long clk_esc_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct clk *clk_parent;
	unsigned int div;

	clk_parent = __clk_get_parent(hw->clk);
	*prate = __clk_get_rate(clk_parent);

	div = find_best_esc_divider(*prate);
	return *prate / div;
}

static int clk_esc_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_esc *esc = container_of(hw, struct clk_esc, hw);
	unsigned int data;

	esc->div = parent_rate / rate;
	data = readl_relaxed(esc->reg_base + DSI_CLKMGR_CFG);
	data &= ~0xff;
	writel_relaxed(data | esc->div, esc->reg_base + DSI_CLKMGR_CFG);
	return 0;
}

struct clk_ops clk_esc_ops = {
	.round_rate = clk_esc_round_rate,
	.set_rate = clk_esc_set_rate,
	.recalc_rate = clk_esc_recalc_rate,
};

static struct clk *clk_esc_register(struct device *dev, const char *name,
				    const char *parent_name, void __iomem *reg,
				    unsigned long flags)
{
	struct clk_esc *esc;
	struct clk_init_data init;
	struct clk *clk;

	esc = kzalloc(sizeof(*esc), GFP_KERNEL);
	if (!esc) {
		pr_err("%s: could not allocate dsi esc clk\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	/* struct clk_esc assignments */
	esc->hw.init = &init;
	esc->reg_base = reg;

	init.name = name;
	init.ops = &clk_esc_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_register(dev, &esc->hw);

	if (IS_ERR(clk))
		kfree(esc);

	return clk;
}

void __init hi3620_esc_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	void __iomem *reg_base;

	reg_base = hi3620_init_clocks(np);
	if (!reg_base)
		return;
	if (of_property_read_string(np, "clock-output-names", &clk_name))
		return;
	/* gate only has the fixed parent */
	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names)
		return;
	parent_names[0] = of_clk_get_parent_name(np, 0);

	clk = clk_esc_register(NULL, clk_name, parent_names[0], reg_base, 0);
	if (IS_ERR(clk))
		goto err;
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;
err:
	kfree(parent_names);
}

CLK_OF_DECLARE(hi3620_dsi_pll, "hisilicon,hi3620-phy", hi3620_phy_setup)
CLK_OF_DECLARE(hi3620_dsi_esc, "hisilicon,hi3620-phy-esc", hi3620_esc_setup)

static const struct of_device_id hi3620_of_match[] = {
	{ .compatible = "hisilicon,hi3620-fb",	.data = (void *)HI3620_EDC, },
};

static void __iomem __init *hi3620_init_clocks(struct device_node *np)
{
	struct device_node *parent;
	const struct of_device_id *match;
	void __iomem *ret = NULL;

	parent = of_get_parent(np);
	if (!parent)
		goto out;
	match = of_match_node(hi3620_of_match, parent);
	if (!match)
		goto out;
	switch ((unsigned int)match->data) {
	case HI3620_EDC:
		if (!hi3620_clk.edc) {
			ret = of_iomap(parent, 0);
			WARN_ON(!ret);
			hi3620_clk.edc = ret;
		} else {
			ret = hi3620_clk.edc;
		}
		break;
	}
out:
	return ret;
}
