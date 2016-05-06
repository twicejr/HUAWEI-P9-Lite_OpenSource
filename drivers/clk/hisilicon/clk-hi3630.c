/*
 * Hisilicon clock driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *	   Xin Li <li.xin@linaro.org>
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
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_rproc.h>

#include "hisi-clk-mailbox.h"

#define HI3630_CLK_GATE_DISABLE_OFFSET		0x4
#define HI3630_CLK_GATE_STATUS_OFFSET		0x8

/* reset register offset */
#define HI3630_RST_DISABLE_REG_OFFSET		0x4

#define WIDTH_TO_MASK(width)	((1 << (width)) - 1)

#define MAX_READ_DDRFREQ_TRY                   3

/*
 * The reverse of DIV_ROUND_UP: The maximum number which
 * divided by m is r
 */
#define MULT_ROUND_UP(r, m) ((r) * (m) + (m) - 1)

enum {
	HS_PMCTRL,
	HS_SYSCTRL,
	HS_CRGCTRL,
	HS_PMUCTRL,
};

struct hi3630_periclk {
	struct clk_hw	hw;
	void __iomem	*enable;	/* enable register */
	void __iomem	*reset;		/* reset register */
	u32		ebits;		/* bits in enable/disable register */
	u32		rbits;		/* bits in reset/unreset register */
	const char 	*friend;
	spinlock_t	*lock;
};

struct hi3630_muxclk {
	struct clk_hw	hw;
	void __iomem	*reg;		/* mux register */
	u8		shift;
	u8		width;
	u32		mbits;		/* mask bits in mux register */
	spinlock_t	*lock;
};

struct hi3630_divclk {
	struct clk_hw	hw;
	void __iomem	*reg;		/* divider register */
	u8		shift;
	u8		width;
	u32		mbits;		/* mask bits in divider register */
	const struct clk_div_table	*table;
	spinlock_t	*lock;
};

/* ppll0 */
struct hi3630_ppll0_clk {
	struct clk_hw	hw;
	u32				ref_cnt;	/* reference count */
	u32				cmd[LPM3_CMD_LEN];
	spinlock_t		*lock;
};

struct hi3630_ppll2_clk {
	struct clk_hw	hw;
	void __iomem	*powerdown_reg;
	void __iomem	*gateen_reg;

	u8		powerdown_bit;
	u8		lock_bit;
	u8		gate_bit;
	u8		bp_bit;

	spinlock_t	*lock;
};

struct hi3630_xfreq_clk {
	struct clk_hw	hw;
	void __iomem	*reg;	/* ctrl register */

	/* 0: A7; 1: A15;  2: gpu; 3:ddr */
	u32		id;
	u32		set_rate_cmd[LPM3_CMD_LEN];
	u32		get_rate_cmd[LPM3_CMD_LEN];

	void __iomem	*pll_sel_reg;
	u32		pll_sel_mask;
	void __iomem	*pll_div_reg;
	u32		pll_div_mask;
	u32		pll_div_aclk_mask;
	u32 	pll_div_busclk_mask;

	u32		rate;
};

struct hi3630_xfreq_pll {
	struct clk_hw	hw;
	void __iomem	*reg;	/* pll ctrl0 register */
};
#define PLL_CTRL1_OFFSET	0x04

struct hi3630_mclk {
	struct clk_hw	hw;
	u32				ref_cnt;	/* reference count */
	u32				en_cmd[LPM3_CMD_LEN];
	u32				dis_cmd[LPM3_CMD_LEN];
	spinlock_t		*lock;
};

struct hs_clk {
	void __iomem	*pmctrl;
	void __iomem	*sctrl;
	void __iomem	*crgctrl;
	void __iomem	*pmuctrl;
	spinlock_t	lock;
};

static void __iomem __init *hs_clk_get_base(struct device_node *np);

static struct hs_clk hs_clk = {
	.lock = __SPIN_LOCK_UNLOCKED(hs_clk.lock),
};

extern int __clk_prepare(struct clk *clk);
extern int __clk_enable(struct clk *clk);
static int hi3630_clkgate_enable(struct clk_hw *hw)
{
	struct hi3630_periclk *pclk;
	struct clk *friend_clk;
	int ret = 0;

	pclk = container_of(hw, struct hi3630_periclk, hw);
	if (pclk->enable)
		writel(pclk->ebits, pclk->enable);

	/* disable reset register */
	if (pclk->reset)
		writel(pclk->rbits, pclk->reset + HI3630_RST_DISABLE_REG_OFFSET);

	/*if friend clk exist,enable it*/
	if (pclk->friend) {
		friend_clk = __clk_lookup(pclk->friend);
		if (IS_ERR_OR_NULL(friend_clk)) {
			pr_err("%s get failed!\n", pclk->friend);
			return -1;
		}
		ret = __clk_prepare(friend_clk);
		if (ret) {
			pr_err("[%s], friend clock prepare faild!", __func__);
			return ret;
		}
		ret = __clk_enable(friend_clk);
		if (ret) {
			__clk_unprepare(friend_clk);
			pr_err("[%s], friend clock enable faild!", __func__);
			return ret;
		}
	}

	return 0;
}

extern int __clk_disable(struct clk *clk);
extern void __clk_unprepare(struct clk *clk);
static void hi3630_clkgate_disable(struct clk_hw *hw)
{
	struct hi3630_periclk *pclk;
	struct clk *friend_clk;
	pclk = container_of(hw, struct hi3630_periclk, hw);

	/* reset the ip, then disalbe clk */
	if (pclk->reset)
		writel(pclk->rbits, pclk->reset);

#ifndef CONFIG_HI3630_CLK_ALWAYS_ON
	if (pclk->enable)
		writel(pclk->ebits, pclk->enable + HI3630_CLK_GATE_DISABLE_OFFSET);
#endif

#ifndef CONFIG_HI3630_CLK_ALWAYS_ON
	/*if friend clk exist, disable it .*/
	if (pclk->friend) {
		friend_clk = __clk_lookup(pclk->friend);
		if (IS_ERR_OR_NULL(friend_clk)) {
			pr_err("%s get failed!\n", pclk->friend);
		}
		__clk_disable(friend_clk);
		__clk_unprepare(friend_clk);
	}
#endif
}

#ifdef CONFIG_HISI_CLK_DEBUG

static int hi3630_clkgate_is_enabled(struct clk_hw *hw)
{
	struct hi3630_periclk *pclk;
	u32 reg = 0;

	pclk = container_of(hw, struct hi3630_periclk, hw);

	if (pclk->enable)
		reg = readl(pclk->enable + HI3630_CLK_GATE_STATUS_OFFSET);
	else
		return 2;

	reg &= pclk->ebits;

	return reg ? 1 : 0;
}

static void __iomem *hi3630_clkgate_get_reg(struct clk_hw *hw)
{
	struct hi3630_periclk *pclk;
	void __iomem	*ret = NULL;
	u32 val = 0;

	pclk = container_of(hw, struct hi3630_periclk, hw);

	if (pclk->enable) {
		ret = pclk->enable + HI3630_CLK_GATE_STATUS_OFFSET;
		val = readl(ret);
		val &= pclk->ebits;
		pr_info("\n[%s]: reg = 0x%p, bits = 0x%x, regval = 0x%x\n",
			hw->clk->name, ret, pclk->ebits, val);
	}

	return ret;
}
#endif



static struct clk_ops hi3630_clkgate_ops = {
	.enable		= hi3630_clkgate_enable,
	.disable	= hi3630_clkgate_disable,
#ifdef CONFIG_HISI_CLK_DEBUG
	.is_enabled = hi3630_clkgate_is_enabled,
	.get_reg  = hi3630_clkgate_get_reg,
#endif
};

static void __init hi3630_clkgate_setup(struct device_node *np)
{
	struct hi3630_periclk *pclk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *name, *clk_friend, **parent_names;
	void __iomem *reg_base;
	u32 rdata[2] = {0};
	u32 gdata[2] = {0};

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] %s node doesn't have clock-output-name property!\n",
			 __func__, np->name);
		return;
	}
	if (of_property_read_u32_array(np, "hisilicon,hi3630-clkgate",
				       &gdata[0], 2)) {
		pr_err("[%s] %s node doesn't have hi3630-clkgate property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_string(np, "clock-friend-names", &clk_friend))
		clk_friend = NULL;

	/* gate only has the fixed parent */
	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parents_names!\n", __func__);
		return;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	pclk = kzalloc(sizeof(struct hi3630_periclk), GFP_KERNEL);
	if (!pclk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		goto err_pclk;
	}

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_clkgate_ops;
	init->flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED;
	init->parent_names = parent_names;
	init->num_parents = 1;

	if (of_property_read_u32_array(np, "hisilicon,hi3630-clkreset",
				       &rdata[0], 2)) {
		pclk->reset = NULL;
		pclk->rbits = 0;
	} else {
		pclk->reset = reg_base + rdata[0];
		pclk->rbits = rdata[1];
	}

	/* if gdata[1] is 0, represents the enable reg is fake */
	if (gdata[1] == 0)
			pclk->enable = NULL;
	else
			pclk->enable = reg_base + gdata[0];

	pclk->ebits = gdata[1];
	pclk->lock = &hs_clk.lock;
	pclk->hw.init = init;
	pclk->friend = clk_friend;

	clk = clk_register(NULL, &pclk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to reigister clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}
	if (!of_property_read_string(np, "clock-output-names", &name))
		clk_register_clkdev(clk, name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;
err_clk:
	kfree(init);
err_init:
	kfree(pclk);
err_pclk:
	kfree(parent_names);
}

static int hi3630_ppll0_enable(struct clk_hw *hw)
{
	struct hi3630_ppll0_clk *ppll0_clk;

	ppll0_clk = container_of(hw, struct hi3630_ppll0_clk, hw);

	ppll0_clk->ref_cnt++;

	return 0;
}

static void hi3630_ppll0_disable(struct clk_hw *hw)
{
	struct hi3630_ppll0_clk *ppll0_clk;
#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	int ret;
#endif

	ppll0_clk = container_of(hw, struct hi3630_ppll0_clk, hw);

	ppll0_clk->ref_cnt--;

#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	/* notify lpm3 when the ref_cnt of ppll0 is 0 */
	if (!ppll0_clk->ref_cnt) {
		ret = hisi_clkmbox_send_msg(&ppll0_clk->cmd[0], NULL);
		pr_err("[%s] fail to sync ppll0 ref_cnt with lpm3.\n", __func__);
	}
#endif
}

static struct clk_ops hi3630_ppll0_ops = {
	.enable		= hi3630_ppll0_enable,
	.disable	= hi3630_ppll0_disable,
};

static void __init hi3630_ppll0_setup(struct device_node *np)
{
	struct hi3630_ppll0_clk *ppll0_clk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, **parent_names;
	u32 cmd[LPM3_CMD_LEN] = {0};
	u32 i;

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] %s node doesn't have clock-output-name property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_u32_array(np, "hisilicon,ipc-lpm3-cmd", &cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] %s node doesn't have hisilicon,ipc-lpm3-cmd property!\n",
			 __func__, np->name);
		return;
	}

	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parents_names!\n", __func__);
		return;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	ppll0_clk = kzalloc(sizeof(struct hi3630_ppll0_clk), GFP_KERNEL);
	if (!ppll0_clk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		goto err_ppll0_clk;
	}

	/* initialize the reference count */
	ppll0_clk->ref_cnt = 0;

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_ppll0_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = parent_names;
	init->num_parents = 1;

	for (i = 0; i < LPM3_CMD_LEN; i++)
		ppll0_clk->cmd[i] = cmd[i];

	ppll0_clk->lock = &hs_clk.lock;
	ppll0_clk->hw.init = init;

	clk = clk_register(NULL, &ppll0_clk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to reigister clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);

	return;

err_clk:
	kfree(init);
err_init:
	kfree(ppll0_clk);
err_ppll0_clk:
	kfree(parent_names);
}

static void hi3630_ppll2_disable(struct clk_hw *hw)
{
	struct hi3630_ppll2_clk *ppll2_clk;
	unsigned long flags = 0;
	unsigned long val;
	ppll2_clk = container_of(hw, struct hi3630_ppll2_clk, hw);

	if (ppll2_clk->lock)
		spin_lock_irqsave(ppll2_clk->lock, flags);
	/* gate ppll2 */
	val = readl(ppll2_clk->gateen_reg);
	val &= ~(1 << ppll2_clk->gate_bit);
	writel(val, ppll2_clk->gateen_reg);

	/* shutdown ppll2 */
	val = readl(ppll2_clk->powerdown_reg);
	val &= ~(1 << ppll2_clk->powerdown_bit);
	val |= (1 << ppll2_clk->bp_bit);
	writel(val, ppll2_clk->powerdown_reg);

	if (ppll2_clk->lock)
		spin_unlock_irqrestore(ppll2_clk->lock, flags);
}


static int hi3630_ppll2_enable(struct clk_hw *hw)
{
	struct hi3630_ppll2_clk *ppll2_clk;
	unsigned long flags = 0;
	unsigned long val;
	ppll2_clk = container_of(hw, struct hi3630_ppll2_clk, hw);

	if (ppll2_clk->lock)
		spin_lock_irqsave(ppll2_clk->lock, flags);

	/* open ppll2 */
	val = readl(ppll2_clk->powerdown_reg);
	val |= (1 << ppll2_clk->powerdown_bit);
	val &= (~(1 << ppll2_clk->bp_bit));
	writel(val, ppll2_clk->powerdown_reg);

	do {
		val = readl(ppll2_clk->powerdown_reg);
		val &= (1 << ppll2_clk->lock_bit);
	} while (!val);

	/* disable gate ppll2 */
	val = readl(ppll2_clk->gateen_reg);
	val |= (1 << ppll2_clk->gate_bit);
	writel(val, ppll2_clk->gateen_reg);

	if (ppll2_clk->lock)
		spin_unlock_irqrestore(ppll2_clk->lock, flags);

	return 0;
}


static struct clk_ops hi3630_ppll2_ops = {
	.enable		= hi3630_ppll2_enable,
	.disable	= hi3630_ppll2_disable,
};

static void __init hi3630_ppll2_setup(struct device_node *np)
{
	struct hi3630_ppll2_clk *ppll2_clk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, **parent_names;
	u32 data[3] = {0};
	void __iomem *reg_base;

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] %s node doesn't have clock-output-name property!\n",
			 __func__, np->name);
		return;
	}

	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parents_names!\n", __func__);
		return;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	ppll2_clk = kzalloc(sizeof(struct hi3630_ppll2_clk), GFP_KERNEL);
	if (!ppll2_clk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		goto err_ppll2_clk;
	}

	if (of_property_read_u32_array(np, "hisilicon,ppll2-powerdown",
				       &data[0], 3)) {
		pr_err("[%s] %s node doesn't have ppll2-powerdown property!\n",
			 __func__, np->name);
		goto err_ppll2_clk;
	}
	ppll2_clk->powerdown_reg = reg_base + data[0];
	ppll2_clk->powerdown_bit = data[1];
	ppll2_clk->lock_bit = data[2];

	if (of_property_read_u32_array(np, "hisilicon,ppll2-gateen",
				      &data[0], 2)) {
		pr_err("[%s] %s node doesn't have ppll2-powerdown property!\n",
			 __func__, np->name);
		goto err_ppll2_clk;
	}
	ppll2_clk->gateen_reg = reg_base + data[0];
	ppll2_clk->bp_bit = data[1];
	ppll2_clk->gate_bit = data[2];

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_ppll2_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = parent_names;
	init->num_parents = 1;

	ppll2_clk->lock = &hs_clk.lock;
	ppll2_clk->hw.init = init;

	clk = clk_register(NULL, &ppll2_clk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to reigister clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;

err_clk:
	kfree(init);
err_init:
	kfree(ppll2_clk);
err_ppll2_clk:
	kfree(parent_names);
}

static int __init hi3xxx_parse_mux(struct device_node *np,
				   u8 *num_parents)
{
	int i, cnt;

	/* get the count of items in mux */
	for (i = 0, cnt = 0;; i++, cnt++) {
		/* parent's #clock-cells property is always 0 */
		if (!of_parse_phandle(np, "clocks", i))
			break;
	}

	for (i = 0; i < cnt; i++) {
		if (!of_clk_get_parent_name(np, i)) {
			pr_err("[%s] cannot get %dth parent_clk name!\n",
				__func__, i);
			return -ENOENT;
		}
	}
	*num_parents = cnt;

	return 0;
}

static void __init hi3630_clkmux_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names = NULL;
	u32 rdata[2] = {0};
	u32 width = 0;
	u8 num_parents, shift, flag = 0;
	void __iomem *reg, *base;
	int i, ret;

	base = hs_clk_get_base(np);
	if (!base) {
		pr_err("[%s] fail to get base!\n", __func__);
		return;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] %s node doesn't have clock-output-name property!\n",
				__func__, np->name);
		return;
	}
	if (of_property_read_u32_array(np, "hisilicon,clkmux-reg",
				       &rdata[0], 2)) {
		pr_err("[%s] %s node doesn't have clkmux-reg property!\n",
				__func__, np->name);
		return;
	}

	if (of_property_read_bool(np, "hiword"))
		flag = CLK_MUX_HIWORD_MASK;

	ret = hi3xxx_parse_mux(np, &num_parents);
	if (ret) {
		pr_err("[%s] %s node cannot get num_parents!\n",
			__func__, np->name);
		return;
	}

	parent_names = kzalloc(sizeof(char *) * num_parents, GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parent_names!\n", __func__);
		return;
	}
	for (i = 0; i < num_parents; i++)
		parent_names[i] = of_clk_get_parent_name(np, i);

	reg = base + rdata[0];
	shift = ffs(rdata[1]) - 1;
	width = fls(rdata[1]) - ffs(rdata[1]) + 1;

	clk = clk_register_mux(NULL, clk_name, parent_names, num_parents,
				     CLK_SET_RATE_PARENT, reg, shift, width,
				     flag, &hs_clk.lock);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register mux clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);

	return;
err_clk:
	kfree(parent_names);
}

static void __init hs_clkgate_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	unsigned long flags = 0;
	void __iomem *reg_base;
	u32 data[2] = {0};

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}
	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		return;
	}
	if (of_property_read_u32_array(np, "hisilicon,clkgate",
				       &data[0], 2)) {
		pr_err("[%s] node %s doesn't have clkgate property!\n",
			__func__, np->name);
		return;
	}
	if (of_property_read_bool(np, "hisilicon,clkgate-inverted"))
		flags = CLK_GATE_SET_TO_DISABLE;
	if (of_property_read_bool(np, "hiword"))
		flags |= CLK_GATE_HIWORD_MASK;

	if (of_property_read_bool(np, "pmu32khz"))
		data[0] = data[0] << 2;

	/* gate only has the fixed parent */
	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parent_names!\n", __func__);
		return;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	clk = clk_register_gate(NULL, clk_name, parent_names[0],
				CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED, reg_base + data[0],
				(u8)data[1], flags, &hs_clk.lock);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register gate clk %s!\n",
			__func__, clk_name);
		goto err;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;
err:
	kfree(parent_names);
}

static unsigned int hi3630_get_table_maxdiv(const struct clk_div_table *table)
{
	unsigned int maxdiv = 0;
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div > maxdiv)
			maxdiv = clkt->div;
	return maxdiv;
}

static unsigned int hi3630_get_table_div(const struct clk_div_table *table,
							unsigned int val)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->val == val)
			return clkt->div;
	return 0;
}

static unsigned int hi3630_get_table_val(const struct clk_div_table *table,
					 unsigned int div)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div == div)
			return clkt->val;
	return 0;
}

static unsigned long hi3630_clkdiv_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi3630_divclk *dclk = container_of(hw, struct hi3630_divclk, hw);
	unsigned int div, val;

	val = readl(dclk->reg) >> dclk->shift;
	val &= WIDTH_TO_MASK(dclk->width);

	div = hi3630_get_table_div(dclk->table, val);
	if (!div) {
		pr_warn("%s: Invalid divisor for clock %s\n", __func__,
			   __clk_get_name(hw->clk));
		return parent_rate;
	}

	return parent_rate / div;
}

static bool hi3630_is_valid_table_div(const struct clk_div_table *table,
				      unsigned int div)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div == div)
			return true;
	return false;
}

static int hi3630_clkdiv_bestdiv(struct clk_hw *hw, unsigned long rate,
				 unsigned long *best_parent_rate)
{
	struct hi3630_divclk *dclk = container_of(hw, struct hi3630_divclk, hw);
	struct clk *clk_parent = __clk_get_parent(hw->clk);
	int i, bestdiv = 0;
	unsigned long parent_rate, best = 0, now, maxdiv;

	maxdiv = hi3630_get_table_maxdiv(dclk->table);

	if (!(__clk_get_flags(hw->clk) & CLK_SET_RATE_PARENT)) {
		parent_rate = *best_parent_rate;
		bestdiv = DIV_ROUND_UP(parent_rate, rate);
		bestdiv = bestdiv == 0 ? 1 : bestdiv;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		return bestdiv;
	}

	/*
	 * The maximum divider we can use without overflowing
	 * unsigned long in rate * i below
	 */
	maxdiv = min(ULONG_MAX / rate, maxdiv);

	for (i = 1; i <= maxdiv; i++) {
		if (!hi3630_is_valid_table_div(dclk->table, i))
			continue;
		parent_rate = __clk_round_rate(clk_parent,
					       MULT_ROUND_UP(rate, i));
		now = parent_rate / i;
		if (now <= rate && now > best) {
			bestdiv = i;
			best = now;
			*best_parent_rate = parent_rate;
		}
	}

	if (!bestdiv) {
		bestdiv = hi3630_get_table_maxdiv(dclk->table);
		*best_parent_rate = __clk_round_rate(clk_parent, 1);
	}

	return bestdiv;
}

static long hi3630_clkdiv_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	int div;

	if (!rate)
		rate = 1;
	div = hi3630_clkdiv_bestdiv(hw, rate, prate);

	return *prate / div;
}

static int hi3630_clkdiv_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct hi3630_divclk *dclk = container_of(hw, struct hi3630_divclk, hw);
	unsigned int div, value;
	unsigned long flags = 0;
	u32 data;

	div = parent_rate / rate;
	value = hi3630_get_table_val(dclk->table, div);

	if (value > WIDTH_TO_MASK(dclk->width))
		value = WIDTH_TO_MASK(dclk->width);

	if (dclk->lock)
		spin_lock_irqsave(dclk->lock, flags);

	data = readl(dclk->reg);
	data &= ~(WIDTH_TO_MASK(dclk->width) << dclk->shift);
	data |= value << dclk->shift;
	data |= dclk->mbits;
	writel(data, dclk->reg);

	if (dclk->lock)
		spin_unlock_irqrestore(dclk->lock, flags);

	return 0;
}

#ifdef CONFIG_HISI_CLK_DEBUG
static int hi3630_divreg_check(struct clk_hw *hw)
{
	unsigned long rate;
	struct clk *clk = hw->clk;
	struct clk *pclk = clk_get_parent(clk);

	rate = hi3630_clkdiv_recalc_rate(hw, clk_get_rate(pclk));
	if (rate == clk_get_rate(clk))
		return 1;
	else
		return 0;
}

static void __iomem *hi3630_clkdiv_get_reg(struct clk_hw *hw)
{
	struct hi3630_divclk *dclk;
	void __iomem	*ret = NULL;
	u32 val = 0;

	dclk = container_of(hw, struct hi3630_divclk, hw);

	if (dclk->reg) {
		ret = dclk->reg;
		val = readl(ret);
		val &= dclk->mbits;
		pr_info("\n[%s]: reg = 0x%p, bits = 0x%x, regval = 0x%x\n",
			hw->clk->name, ret, dclk->mbits, val);
	}

	return ret;
}
#endif

static struct clk_ops hi3630_clkdiv_ops = {
	.recalc_rate = hi3630_clkdiv_recalc_rate,
	.round_rate = hi3630_clkdiv_round_rate,
	.set_rate = hi3630_clkdiv_set_rate,
#ifdef CONFIG_HISI_CLK_DEBUG
	.check_divreg = hi3630_divreg_check,
	.get_reg = hi3630_clkdiv_get_reg,
#endif
};

void __init hi3630_clkdiv_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	struct clk_init_data *init;
	struct clk_div_table *table;
	struct hi3630_divclk *dclk;
	void __iomem *reg_base;
	unsigned int table_num;
	int i;
	u32 data[2] = {0};
	unsigned int max_div, min_div;

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		return;
	}

	/* process the div_table */
	if (of_property_read_u32_array(np, "hisilicon,clkdiv-table",
				       &data[0], 2)) {
		pr_err("[%s] node %s doesn't have clkdiv-table property!\n",
			__func__, np->name);
		return;
	}

	max_div = (u8)data[0];
	min_div = (u8)data[1];

	if (of_property_read_u32_array(np, "hisilicon,clkdiv",
								&data[0], 2)) {
		pr_err("[%s] node %s doesn't have clkdiv property!\n",
			__func__, np->name);
		return;
	}

	table_num = max_div - min_div + 1;

	/* table ends with <0, 0>, so plus one to table_num */
	table = kzalloc(sizeof(struct clk_div_table) * (table_num + 1), GFP_KERNEL);
	if (!table) {
		pr_err("[%s] fail to alloc table!\n", __func__);
		return;
	}

	for (i = 0; i < table_num; i++) {
		table[i].div = min_div + i;
		table[i].val = table[i].div - 1;
	}

	/* mux has the fixed parent */
	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parent_names!\n", __func__);
		goto err_par;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	dclk = kzalloc(sizeof(struct hi3630_divclk), GFP_KERNEL);
	if (!dclk) {
		pr_err("[%s] fail to alloc dclk!\n", __func__);
		goto err_dclk;
	}
	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_clkdiv_ops;
	init->parent_names = parent_names;
	init->num_parents = 1;

	dclk->reg = reg_base + data[0];
	dclk->shift = ffs(data[1]) - 1;
	dclk->width = fls(data[1]) - ffs(data[1]) + 1;
	dclk->mbits = data[1] << 16;
	dclk->lock = &hs_clk.lock;
	dclk->hw.init = init;
	dclk->table = table;
	clk = clk_register(NULL, &dclk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register div clk %s!\n",
				__func__, clk_name);
		goto err_clk;
	}
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_register_clkdev(clk, clk_name, NULL);
	return;
err_clk:
	kfree(init);
err_init:
	kfree(dclk);
err_dclk:
	kfree(parent_names);
err_par:
	kfree(table);
}

char *xfreq_devname[] = {
	"XFREQ_A15_CPU",
	"XFREQ_A7_CPU",
	"XFREQ_GPU",
	"XFREQ_DDR"
};

#define BITS(i,n) (i & (1 << n))

unsigned long pll_freq(unsigned long param0, unsigned long param1)
{
       if (!BITS(param0,0) || !BITS(param1,26) || !BITS(param1,25)) {
		return 0;
       } else if (BITS(param0,0) & BITS(param0,1)) {
		return 192;
       } else
		return (((((192 * ((param0 & 0xFFF00) + ((param1 >> 16) & 0xFF))) / (((param0 >> 2) & 0x3F) * ((param0 >> 23) & 0x07) * ((param0 >> 20) & 0x07))) + 0x80) >> 8));
}

static unsigned long hi3630_xfreq_clk_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi3630_xfreq_clk *xfreq_clk = container_of(hw, struct hi3630_xfreq_clk, hw);
	u32 rate, pll_sel,pllreg,pllreg2 = 0;
	u32 rate2,ddrdiv,ddrdiv2 = 0;
	char clk_name[20] = {0};
	struct clk *clk;
	u32 ddrc_div, aclk_div, busclk_div;
	int loop = MAX_READ_DDRFREQ_TRY;

	switch(xfreq_clk->id) {
	/* A15 */
	case 0:
	/* A7 */
	case 1:
		pll_sel = readl(xfreq_clk->pll_sel_reg) & xfreq_clk->pll_sel_mask;

		if (pll_sel > 2)
				pll_sel = 2;

		strncpy(clk_name, "clk_appll0", 10);
		clk_name[strlen(clk_name) - 1] = pll_sel + '0';

		clk = __clk_lookup(clk_name);
		if (IS_ERR_OR_NULL(clk)) {
			if (xfreq_clk->rate == 0)
				xfreq_clk->rate = clk_get_rate(hw->clk->parent);

			rate = xfreq_clk->rate;
			break;
		}

		rate = clk_get_rate(clk);
		break;

	/* DDR get freq */
	case 3:
		/*according the process of the ddr Freq and that signal sequence.
		 * the dynamicly process of ddr Freq refer to the register of ppll0,
		 * ppll1 ,ddr sel and ddr div. the ppll0 is fixed,but ppll1 is changeable.
		 * the signal sequence of ddr Freq in LPM3 contain the 60us rasing or failing
		 * signal which is intermediate state seting ddr freq,and the 20ms
		 * stable state.
		*/
		strncpy(clk_name, "ddrc_ppll0", 10);
		do {
			pllreg = readl(xfreq_clk->pll_sel_reg);
			pll_sel = pllreg & xfreq_clk->pll_sel_mask;
			pll_sel = pll_sel >> (ffs(xfreq_clk->pll_sel_mask) - 1);
			pll_sel = ffs(pll_sel) - 1;

			ddrdiv = readl(xfreq_clk->pll_div_reg);

			clk_name[strlen(clk_name) - 1] = pll_sel + '0';
			clk = __clk_lookup(clk_name);
			if (IS_ERR_OR_NULL(clk)) {
				pr_err("[%s]get ddrc_ppll failed pll_sel 0x%x\n",__func__, pll_sel);
				rate = xfreq_clk->rate;
				return rate;
			}
			rate = clk_get_rate(clk);
			udelay(100);

			dsb();
			/*reback read*/
			pllreg2 = readl(xfreq_clk->pll_sel_reg);
			pll_sel = pllreg2 & xfreq_clk->pll_sel_mask;
			pll_sel = pll_sel >> (ffs(xfreq_clk->pll_sel_mask) - 1);
			pll_sel = ffs(pll_sel) - 1;

			ddrdiv2 = readl(xfreq_clk->pll_div_reg);

			clk_name[strlen(clk_name) - 1] = pll_sel + '0';
			clk = __clk_lookup(clk_name);
			if (IS_ERR_OR_NULL(clk)) {
				pr_err("[%s]get ddrc_ppll failed pll_sel 0x%x\n",__func__, pll_sel);
				rate2 = xfreq_clk->rate;
				return rate2;
			}
			rate2 = clk_get_rate(clk);

			loop--;
		}while((pllreg2 != pllreg || rate2 != rate || rate == 0 || ddrdiv2 != ddrdiv)  && loop > 0);

		ddrc_div = ddrdiv;
		aclk_div = ddrdiv & xfreq_clk->pll_div_aclk_mask;
		busclk_div = ddrdiv & xfreq_clk->pll_div_busclk_mask;

		ddrc_div = ddrc_div & xfreq_clk->pll_div_mask;
		ddrc_div = ddrc_div + 1;
		aclk_div = aclk_div >> (ffs(xfreq_clk->pll_div_aclk_mask) - 1);
		aclk_div = aclk_div + 1;
		busclk_div = busclk_div >> (ffs(xfreq_clk->pll_div_busclk_mask) - 1);
		busclk_div = busclk_div + 1;

		if (busclk_div == 1)
			rate = (2 *rate) / (ddrc_div * aclk_div);
		else
			rate = rate / (ddrc_div * aclk_div);

		break;
	/* DDR set min */
	case 4:
	default:
		rate = xfreq_clk->rate;
	}

	return rate;
}

static long hi3630_xfreq_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	return rate;
}

static long hi3630_xfreq_clk_determine_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *best_parent_rate,
					struct clk **best_parent_clk)
{
	return rate;
}

static int hi3630_xfreq_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct hi3630_xfreq_clk *xfreq_clk = container_of(hw, struct hi3630_xfreq_clk, hw);
	unsigned long new_rate = rate/1000000;
	int ret = 0;

	pr_debug("[%s] %s set rate = %ldMHZ\n", __func__,
				xfreq_devname[xfreq_clk->id], new_rate);
	xfreq_clk->set_rate_cmd[1] = new_rate;

#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	ret = hisi_clkmbox_send_msg(xfreq_clk->set_rate_cmd, NULL);
	if (ret < 0) {
		pr_err("[%s] %s fail to send msg to LPM3!\n",
					__func__, xfreq_devname[xfreq_clk->id]);

		return -EINVAL;
	}
#endif

	xfreq_clk->rate = rate;
	return ret;
}

static struct clk_ops hi3630_xfreq_clk_ops = {
	.recalc_rate = hi3630_xfreq_clk_recalc_rate,
	.determine_rate = hi3630_xfreq_clk_determine_rate,
	.round_rate = hi3630_xfreq_clk_round_rate,
	.set_rate = hi3630_xfreq_clk_set_rate,
};

/*
 * xfreq_clk is used for cpufreq & devfreq.
 */
void __init hi3630_xfreq_clk_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	struct clk_init_data *init;
	struct hi3630_xfreq_clk *xfreqclk;
	u32 get_rate_cmd[LPM3_CMD_LEN], set_rate_cmd[LPM3_CMD_LEN] = {0};
	u32 device_id, i = 0;
	void __iomem *reg_base;
	u32 pll_sel_array[2], pll_div_array[4] = {0};

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parent_names!\n", __func__);
		goto err;
	}
	if (NULL == of_clk_get_parent_name(np, 0))
		parent_names = NULL;
	else
		parent_names[0] = of_clk_get_parent_name(np, 0);

	if (of_property_read_u32(np, "hisilicon,hi3630-xfreq-devid", &device_id)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_u32_array(np, "hisilicon,pll-sel", &pll_sel_array[0], 2)) {
		pr_err("[%s] node %s doesn't hisilicon,pll-sel property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_u32_array(np, "hisilicon,pll-div", &pll_div_array[0], 4)) {
		pr_err("[%s] node %s doesn't hisilicon,pll-div property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_u32_array(np, "hisilicon,get-rate-ipc-cmd", &get_rate_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] node %s doesn't get-rate-ipc-cmd property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_u32_array(np, "hisilicon,set-rate-ipc-cmd", &set_rate_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] node %s doesn't set-rate-ipc-cmd property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		goto err_prop;
	}

	xfreqclk = kzalloc(sizeof(struct hi3630_xfreq_clk), GFP_KERNEL);
	if (!xfreqclk) {
		pr_err("[%s] fail to alloc xfreqclk!\n", __func__);
		goto err_prop;
	}
	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_xfreq_clk_ops;
	init->parent_names = (parent_names ? parent_names: NULL);
	init->num_parents = (parent_names ? 1 : 0);
	init->flags = CLK_IS_ROOT | CLK_GET_RATE_NOCACHE;

	for (i = 0; i < LPM3_CMD_LEN; i++) {
		xfreqclk->set_rate_cmd[i] = set_rate_cmd[i];
		xfreqclk->get_rate_cmd[i] = get_rate_cmd[i];
	}

	if (2 == device_id)
		xfreqclk->rate = 360000000;

	xfreqclk->hw.init = init;
	xfreqclk->id = device_id;
	xfreqclk->pll_sel_reg = reg_base + pll_sel_array[0];
	xfreqclk->pll_sel_mask = pll_sel_array[1];
	xfreqclk->pll_div_reg = reg_base + pll_div_array[0];
	xfreqclk->pll_div_mask = pll_div_array[1];
	xfreqclk->pll_div_aclk_mask = pll_div_array[2];
	xfreqclk->pll_div_busclk_mask = pll_div_array[3];

	clk = clk_register(NULL, &xfreqclk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register xfreqclk %s!\n",
				__func__, clk_name);
		goto err_clk;
	}

	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_register_clkdev(clk, clk_name, NULL);

	return;

err_clk:
	kfree(init);
err_init:
	kfree(xfreqclk);
err_prop:
	kfree(parent_names);
err:
	return;
}

static unsigned long hi3630_xfreq_pll_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi3630_xfreq_pll *xfreq_pll = container_of(hw, struct hi3630_xfreq_pll, hw);
	unsigned long val1, val2, rate;

	val1 = readl(xfreq_pll->reg);
	val2 = readl(xfreq_pll->reg + PLL_CTRL1_OFFSET);

	rate = pll_freq(val1, val2) * 100000;

	return 	rate;
}

static long hi3630_xfreq_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	return rate;
}

static long hi3630_xfreq_pll_determine_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *best_parent_rate,
					struct clk **best_parent_clk)
{
	return rate;
}

static int hi3630_xfreq_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	return 0;
}

static struct clk_ops hi3630_xfreq_pll_ops = {
	.recalc_rate = hi3630_xfreq_pll_recalc_rate,
	.determine_rate = hi3630_xfreq_pll_determine_rate,
	.round_rate = hi3630_xfreq_pll_round_rate,
	.set_rate = hi3630_xfreq_pll_set_rate,
};

/*
 * xfreq_clk is used for cpufreq & devfreq.
 */
void __init hi3630_xfreq_pll_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name,**parent_names;
	struct clk_init_data *init;
	struct hi3630_xfreq_pll *xfreqpll;
	u32 ctrl0_reg = 0;
	void __iomem *reg_base;

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parent_names!\n", __func__);
		goto err;
	}
	if (NULL == of_clk_get_parent_name(np, 0))
		parent_names = NULL;
	else
		parent_names[0] = of_clk_get_parent_name(np, 0);

	if (of_property_read_u32(np, "hisilicon,pll-ctrl-reg", &ctrl0_reg)) {
		pr_err("[%s] node %s doesn't have hisilicon,pll-ctrl-reg property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		goto err_prop;
	}

	xfreqpll = kzalloc(sizeof(struct hi3630_xfreq_pll), GFP_KERNEL);
	if (!xfreqpll) {
		pr_err("[%s] fail to alloc xfreqpll!\n", __func__);
		goto err_prop;
	}
	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_xfreq_pll_ops;
	init->parent_names = (parent_names ? parent_names: NULL);
	init->num_parents = (parent_names ? 1 : 0);
	init->flags = CLK_IS_ROOT | CLK_GET_RATE_NOCACHE;

	xfreqpll->hw.init = init;
	xfreqpll->reg = ctrl0_reg + reg_base;

	clk = clk_register(NULL, &xfreqpll->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register xfreqpll %s!\n",
				__func__, clk_name);
		goto err_clk;
	}

	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_register_clkdev(clk, clk_name, NULL);

	return;

err_clk:
	kfree(init);
err_init:
	kfree(xfreqpll);
err_prop:
	kfree(parent_names);
err:
	return;
}

static int hi3630_mclk_enable(struct clk_hw *hw)
{
	struct hi3630_mclk *mclk;
#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	s32 ret;
#endif
	mclk = container_of(hw, struct hi3630_mclk, hw);
	mclk->ref_cnt++;

#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	/* notify m3 when the ref_cnt of mclk is 1 */
	if (mclk->ref_cnt < 2) {
		ret = hisi_clkmbox_send_msg(&mclk->en_cmd[0], NULL);
		if (ret)
			pr_err("[%s] fail to enable clk, ret = %d!\n",__func__, ret);
	}
#endif

	return 0;
}

static void hi3630_mclk_disable(struct clk_hw *hw)
{
	struct hi3630_mclk *mclk;
#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	s32 ret;
#endif
	mclk = container_of(hw, struct hi3630_mclk, hw);
	mclk->ref_cnt--;

#ifdef CONFIG_HI3630_CLK_MAILBOX_SUPPORT
	/* notify m3 when the ref_cnt of gps_clk is 0 */
	if (!mclk->ref_cnt) {
		ret = hisi_clkmbox_send_msg(&mclk->dis_cmd[0], NULL);
		if (ret)
			pr_err("[%s] fail to disable clk, ret = %d!\n",__func__, ret);
	}
#endif
}

static struct clk_ops hi3630_mclk_ops = {
	.enable		= hi3630_mclk_enable,
	.disable	= hi3630_mclk_disable,
};

static void __init hi3630_mclk_setup(struct device_node *np)
{
	struct hi3630_mclk *mclk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, **parent_names;
	u32 en_cmd[LPM3_CMD_LEN] = {0};
	u32 dis_cmd[LPM3_CMD_LEN] = {0};
	u32 i;

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] %s node doesn't have clock-output-name property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_u32_array(np, "hisilicon,ipc-lpm3-cmd-en", &en_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] %s node doesn't have hisilicon,ipc-modem-cmd property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_u32_array(np, "hisilicon,ipc-lpm3-cmd-dis", &dis_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] %s node doesn't have hisilicon,ipc-modem-cmd property!\n",
			 __func__, np->name);
		return;
	}

	parent_names = kzalloc(sizeof(char *), GFP_KERNEL);
	if (!parent_names) {
		pr_err("[%s] fail to alloc parents_names!\n", __func__);
		return;
	}
	parent_names[0] = of_clk_get_parent_name(np, 0);

	mclk = kzalloc(sizeof(struct hi3630_mclk), GFP_KERNEL);
	if (!mclk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		goto err_mclk;
	}

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3630_mclk_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = parent_names;
	init->num_parents = 1;

	for (i = 0; i < LPM3_CMD_LEN; i++)
		mclk->en_cmd[i] = en_cmd[i];
	for (i = 0; i < LPM3_CMD_LEN; i++)
		mclk->dis_cmd[i] = dis_cmd[i];

	/* initialize the reference count */
	mclk->ref_cnt = 0;
	mclk->lock = &hs_clk.lock;
	mclk->hw.init = init;

	clk = clk_register(NULL, &mclk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to reigister clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);

	return;

err_clk:
	kfree(init);
err_init:
	kfree(mclk);
err_mclk:
	kfree(parent_names);
}

CLK_OF_DECLARE(hi3630_mux, "hisilicon,hi3630-clk-mux", hi3630_clkmux_setup)
CLK_OF_DECLARE(hi3630_div, "hisilicon,hi3630-clk-div", hi3630_clkdiv_setup)
CLK_OF_DECLARE(hs_gate, "hisilicon,clk-gate", hs_clkgate_setup)
CLK_OF_DECLARE(hi3630_gate, "hisilicon,hi3630-clk-gate", hi3630_clkgate_setup)
CLK_OF_DECLARE(hi3630_ppll0, "hisilicon,ppll0", hi3630_ppll0_setup)
CLK_OF_DECLARE(hi3630_ppll2, "hisilicon,ppll2", hi3630_ppll2_setup)
CLK_OF_DECLARE(hi3630_cpu, "hisilicon,hi3630-xfreq-clk", hi3630_xfreq_clk_setup)
CLK_OF_DECLARE(hi3630_xfreq_pll, "hisilicon,hi3630-xfreq-pll", hi3630_xfreq_pll_setup)
CLK_OF_DECLARE(hi3630_mclk, "hisilicon,modem-clk", hi3630_mclk_setup)

static const struct of_device_id hs_of_match[] = {
	{ .compatible = "hisilicon,clk-pmctrl",	.data = (void *)HS_PMCTRL, },
	{ .compatible = "hisilicon,clk-sctrl",	.data = (void *)HS_SYSCTRL, },
	{ .compatible = "hisilicon,clk-crgctrl",	.data = (void *)HS_CRGCTRL, },
	{ .compatible = "hisilicon,hi6421pmic",	.data = (void *)HS_PMUCTRL, },
};

static void __iomem __init *hs_clk_get_base(struct device_node *np)
{
	struct device_node *parent;
	const struct of_device_id *match;
	void __iomem *ret = NULL;

	parent = of_get_parent(np);
	if (!parent) {
		pr_err("[%s] node %s doesn't have parent node!\n", __func__, np->name);
		goto out;
	}
	match = of_match_node(hs_of_match, parent);
	if (!match) {
		pr_err("[%s] parent node %s doesn't match!\n", __func__, parent->name);
		goto out;
	}
	switch ((unsigned int)match->data) {
	case HS_PMCTRL:
		if (!hs_clk.pmctrl) {
			ret = of_iomap(parent, 0);
			WARN_ON(!ret);
			hs_clk.pmctrl = ret;
		} else {
			ret = hs_clk.pmctrl;
		}
		break;
	case HS_SYSCTRL:
		if (!hs_clk.sctrl) {
			ret = of_iomap(parent, 0);
			WARN_ON(!ret);
			hs_clk.sctrl = ret;
		} else {
			ret = hs_clk.sctrl;
		}
		break;
	case HS_CRGCTRL:
		if (!hs_clk.crgctrl) {
			ret = of_iomap(parent, 0);
			WARN_ON(!ret);
			hs_clk.crgctrl = ret;
		} else {
			ret = hs_clk.crgctrl;
		}
		break;
	case HS_PMUCTRL:
		if (!hs_clk.pmuctrl) {
			ret = of_iomap(parent, 0);
			WARN_ON(!ret);
			hs_clk.pmuctrl = ret;
		} else {
			ret = hs_clk.pmuctrl;
		}
		break;

	default:
		pr_err("[%s] cannot find the match node!\n", __func__);
		ret = NULL;
	}
out:
	return ret;
}
