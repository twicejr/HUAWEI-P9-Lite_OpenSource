/*
 * Hisilicon clock driver
 *
 * Copyright (c) 2013-2015 Hisilicon Limited.
 *
 *Author: zhaokai <zhaokai1@hisilicon.com>
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
#include <linux/hwspinlock.h>
#include <soc_sctrl_interface.h>

#ifndef CONFIG_HISI_CLK_ALWAYS_ON
/*lint -e750 -esym(750,*)*/
#define hi3xxx_CLK_GATE_DISABLE_OFFSET		0x4
#endif

#define hi3xxx_CLK_GATE_STATUS_OFFSET		0x8

/* reset register offset */
#define hi3xxx_RST_DISABLE_REG_OFFSET		0x4

#define CLK_GATE_ALWAYS_ON_MASK			0x4

#define WIDTH_TO_MASK(width)	((1 << (width)) - 1)

#define MAX_FREQ_NUM			       8

#define CLK_HWLOCK_TIMEOUT			1000
#define PPLLCTRL0(n)                  	(0x030 + ((n) << 3))
#define PPLLCTRL1(n)                  	(0x034 + ((n) << 3))
/*lint -e750 +esym(750,*)*/
#define PPLLCTRL0_EN			 		0
#define PPLLCTRL0_BP			 		1
#define PPLLCTRL0_LOCK		 		26
#define PPLLCTRL1_GT		 	 		26
#define ABB_SCBAKDATA(BASE)		SOC_SCTRL_SCBAKDATA12_ADDR(BASE);
#define PPLL3_SCBAKDATA(BASE)		SOC_SCTRL_SCBAKDATA11_ADDR(BASE);
#define AP_POLL_EN			 		0
#define LPM3_POLL_EN			 		1
#define AP_ABB_EN			 		0
#define LPM3_ABB_EN			 		1
#define AP_PPLL3_STABLE_TIME          1000
#define AP_ABB_CODEC_LOCK		9
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

enum {
	PPLL0 = 0,
	PPLL1,
	PPLL2,
	PPLL3,
	PPLLMAX,
};

struct hi3xxx_periclk {
	struct clk_hw	hw;
	void __iomem	*enable;	/* enable register */
	void __iomem	*reset;		/* reset register */
	u32		ebits;		/* bits in enable/disable register */
	u32		rbits;		/* bits in reset/unreset register */
	void __iomem		*sctrl;   /*sysctrl addr*/
	const char 	*friend;
	spinlock_t	*lock;
	u32		flags;
	struct hwspinlock	*clk_hwlock;
	u32		always_on;
};

struct hi3xxx_muxclk {
	struct clk_hw	hw;
	void __iomem	*reg;		/* mux register */
	u8		shift;
	u8		width;
	u32		mbits;		/* mask bits in mux register */
	spinlock_t	*lock;
};

struct hi3xxx_divclk {
	struct clk_hw	hw;
	void __iomem	*reg;		/* divider register */
	u8		shift;
	u8		width;
	u32		mbits;		/* mask bits in divider register */
	const struct clk_div_table	*table;
	spinlock_t	*lock;
};

/* ppll0 */
struct hi3xxx_ppll_clk {
	struct clk_hw	hw;
	u32				ref_cnt;	/* reference count */
	u32				en_cmd[LPM3_CMD_LEN];
	u32				dis_cmd[LPM3_CMD_LEN];
	void __iomem		*addr;   /*base addr*/
	void __iomem		*sctrl;   /*sysctrl addr*/
	u32		flags;
	struct hwspinlock	*clk_hwlock;
	spinlock_t		*lock;
};

struct hi3xxx_ppll2_clk {
	struct clk_hw	hw;
	void __iomem	*powerdown_reg;
	void __iomem	*gateen_reg;

	u8		powerdown_bit;
	u8		lock_bit;
	u8		gate_bit;
	u8		bp_bit;

	spinlock_t	*lock;
};

struct hi3xxx_xfreq_clk {
	struct clk_hw	hw;
	void __iomem	*reg;	/* ctrl register */

	u32		id;
	u32		set_rate_cmd[LPM3_CMD_LEN];
	u32		get_rate_cmd[LPM3_CMD_LEN];
	u32		freq[MAX_FREQ_NUM];
	u32		volt[MAX_FREQ_NUM];

	u32		rate;
};

struct hi3xxx_xfreq_pll {
	struct clk_hw	hw;
	void __iomem	*reg;	/* pll ctrl0 register */
};

struct hi3xxx_mclk {
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
static struct hwspinlock	*clk_hwlock_9;
static void __iomem __init *hs_clk_get_base(struct device_node *np);

static struct hs_clk hs_clk = {
	.lock = __SPIN_LOCK_UNLOCKED(hs_clk.lock),
};

extern int IS_FPGA(void);
extern int __clk_prepare(struct clk *clk);
extern int __clk_enable(struct clk *clk);
static int hi3xxx_clkgate_enable(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	struct clk *friend_clk;
	int ret = 0;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);
	if (pclk->enable)
		writel(pclk->ebits, pclk->enable);

	/* disable reset register */
	if (pclk->reset)
		writel(pclk->rbits, pclk->reset + hi3xxx_RST_DISABLE_REG_OFFSET);

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
static void hi3xxx_clkgate_disable(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	struct clk *friend_clk;
	pclk = container_of(hw, struct hi3xxx_periclk, hw);

	/* reset the ip, then disalbe clk */
	if (pclk->reset)
		writel(pclk->rbits, pclk->reset);

#ifndef CONFIG_HISI_CLK_ALWAYS_ON
	if (pclk->enable) {
		if (!pclk->always_on)
			writel(pclk->ebits, pclk->enable + hi3xxx_CLK_GATE_DISABLE_OFFSET);
	}
#endif

#ifndef CONFIG_HISI_CLK_ALWAYS_ON
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

static int hi3xxx_clkgate_is_enabled(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	u32 reg = 0;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);

	if (pclk->enable) {
#ifdef CONFIG_HISI_HI6250_CLK
		if ((!strcmp(hw->clk->name, "clk_dss_axi_mm"))
				|| (!strcmp(hw->clk->name, "pclk_mmbuf"))
				|| (!strcmp(hw->clk->name, "aclk_mmbuf")))
			reg = readl(pclk->enable + 0x18);
		else{
			reg = readl(pclk->enable + hi3xxx_CLK_GATE_STATUS_OFFSET);
		}
#else
		reg = readl(pclk->enable + hi3xxx_CLK_GATE_STATUS_OFFSET);
#endif
	} else
		return 2;

	reg &= pclk->ebits;

	return reg ? 1 : 0;
}

static void __iomem *hi3xxx_clkgate_get_reg(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	void __iomem	*ret = NULL;
	u32 val = 0;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);

	if (pclk->enable) {
		ret = pclk->enable + hi3xxx_CLK_GATE_STATUS_OFFSET;
		val = readl(ret);
		val &= pclk->ebits;
		pr_info("\n[%s]: reg = 0x%p, bits = 0x%x, regval = 0x%x\n",
			hw->clk->name, ret, pclk->ebits, val);
	}

	return ret;
}
#endif

#ifdef CONFIG_HISI_CLK_HI3660
static long clk_gate_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	return rate;
}
#endif

static struct clk_ops hi3xxx_clkgate_ops = {
	.enable		= hi3xxx_clkgate_enable,
	.disable	= hi3xxx_clkgate_disable,
#ifdef CONFIG_HISI_CLK_HI3660
	.round_rate = clk_gate_round_rate,
#endif
#ifdef CONFIG_HISI_CLK_DEBUG
	.is_enabled = hi3xxx_clkgate_is_enabled,
	.get_reg  = hi3xxx_clkgate_get_reg,
#endif
};

static void __init hi3xxx_clkgate_setup(struct device_node *np)
{
	struct hi3xxx_periclk *pclk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *name, *clk_friend, *parent_names;
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
	if (of_property_read_u32_array(np, "hisilicon,hi3xxx-clkgate",
				       &gdata[0], 2)) {
		pr_err("[%s] %s node doesn't have hi3xxx-clkgate property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_string(np, "clock-friend-names", &clk_friend))
		clk_friend = NULL;

	if (IS_FPGA()) {
		if (NULL != of_find_property(np, "clock-fpga", NULL)) {
			if (of_property_read_string(np, "clock-fpga", &parent_names)) {
				pr_err("[%s] %s node clock-fpga value is NULL!\n",
					__func__, np->name);
				return;
			}
		} else {
			 parent_names = of_clk_get_parent_name(np, 0);
		}
	} else {
		parent_names = of_clk_get_parent_name(np, 0);
	}

	pclk = kzalloc(sizeof(struct hi3xxx_periclk), GFP_KERNEL);
	if (!pclk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		return;
	}

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3xxx_clkgate_ops;
	init->flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED;
	init->parent_names = &parent_names;
	init->num_parents = 1;

	if (of_property_read_u32_array(np, "hisilicon,hi3xxx-clkreset",
				       &rdata[0], 2)) {
		pclk->reset = NULL;
		pclk->rbits = 0;
	} else {
		pclk->reset = reg_base + rdata[0];
		pclk->rbits = rdata[1];
	}

	if (of_property_read_bool(np, "always_on"))
		pclk->always_on = 1;
	else
		pclk->always_on = 0;

	/* if gdata[1] is 0, represents the enable reg is fake */
	if (gdata[1] == 0)
			pclk->enable = NULL;
	else
			pclk->enable = reg_base + gdata[0];

	pclk->ebits = gdata[1];
	pclk->lock = &hs_clk.lock;
	pclk->hw.init = init;
	pclk->friend = clk_friend;
	pclk->flags = 0;
	pclk->clk_hwlock = NULL;
	pclk->sctrl = NULL;

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
	init = NULL;
err_init:
	kfree(pclk);
	pclk = NULL;
	return;
}

static int hi3xxx_muticore_clkgate_prepare(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);
	if (AP_ABB_CODEC_LOCK == pclk->flags) {
		if (NULL == clk_hwlock_9) {
			clk_hwlock_9 = hwspin_lock_request_specific(pclk->flags);
			if (NULL == clk_hwlock_9) {
				pr_err("pmu clk request hwspin lock failed !\n");
				return -ENODEV;
			}
		}
		pclk->clk_hwlock = clk_hwlock_9;
	} else {
		pclk->clk_hwlock = hwspin_lock_request_specific(pclk->flags);
		if (NULL == pclk->clk_hwlock) {
			pr_err("muticore clk request hwspin lock failed !\n");
			return -ENODEV;
		}
	}

	return 0;
}

static int hi3xxx_muticore_clkgate_enable(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	int val = 0;
	pclk = container_of(hw, struct hi3xxx_periclk, hw);

	if (hwspin_lock_timeout(pclk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
		pr_err("muticore enable hwspinlock timout!\n");
		return -ENOENT;
	}

	if (pclk->enable) {
		val = readl(pclk->enable);
		val |= pclk->ebits;
		writel(val, pclk->enable);
	}

	hwspin_unlock(pclk->clk_hwlock);
	return 0;
}

static void hi3xxx_muticore_clkgate_disable(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	int val = 0;
	pclk = container_of(hw, struct hi3xxx_periclk, hw);

#ifndef CONFIG_HISI_CLK_ALWAYS_ON
	if (hwspin_lock_timeout(pclk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
		pr_err("muticore disable hwspinlock timout!\n");
		return;
	}

	if (pclk->enable) {
		if (!pclk->always_on) {
			val = readl(pclk->enable);
			val &= (~pclk->ebits);
			writel(val, pclk->enable);
		}
	}
	hwspin_unlock(pclk->clk_hwlock);
	return;
#endif
}

static void hi3xxx_muticore_clkgate_unprepare(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);
	if (AP_ABB_CODEC_LOCK != pclk->flags) {
		if (hwspin_lock_free(pclk->clk_hwlock)) {
			pr_err("muticore hwspinlock free %d failed!\n", hwspin_lock_get_id(pclk->clk_hwlock));
			return;
		}
		pclk->clk_hwlock = NULL;
	}
	return;
}

static struct clk_ops hi3xxx_pmu_clkgate_ops = {
	.prepare        = hi3xxx_muticore_clkgate_prepare,
	.unprepare      = hi3xxx_muticore_clkgate_unprepare,
	.enable		= hi3xxx_muticore_clkgate_enable,
	.disable        = hi3xxx_muticore_clkgate_disable,
};

static int hi3xxx_muticore_abb_clkgate_prepare(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	u32 val = 0;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);
	if (NULL == clk_hwlock_9) {
		clk_hwlock_9 = hwspin_lock_request_specific(pclk->flags);
		if (NULL == clk_hwlock_9) {
			pr_err("abb clk request hwspin lock failed !\n");
			return -ENODEV;
		}


	}
	pclk->clk_hwlock = clk_hwlock_9;
	if (hwspin_lock_timeout(pclk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
		pr_err("abb clk enable hwspinlock timout!\n");
		return -ENOENT;
	}

	val = readl(pclk->sctrl);
	if ((0 == (val & BIT(AP_ABB_EN)))) {
		if (0 == (val & BIT(LPM3_ABB_EN))) {
			/* open abb clk */
			val = readl(pclk->enable);
			val |= pclk->ebits;
			writel(val, pclk->enable);
		}
		/* write 0x344 register */
		val = readl(pclk->sctrl);
		val |= BIT(AP_ABB_EN);
		writel(val, pclk->sctrl);
	}

	hwspin_unlock(pclk->clk_hwlock);
	mdelay(1);
	return 0;
}

static void hi3xxx_muticore_abb_clkgate_unprepare(struct clk_hw *hw)
{
	struct hi3xxx_periclk *pclk;
	u32 val = 0;

	pclk = container_of(hw, struct hi3xxx_periclk, hw);

#ifndef CONFIG_HISI_CLK_ALWAYS_ON
	if (hwspin_lock_timeout(pclk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
		pr_err("abb clk disable hwspinlock timout!\n");
		return;
	}

	val = readl(pclk->sctrl);
	if (1 == (val & BIT(AP_ABB_EN))) {
		if (0 == (val & BIT(LPM3_ABB_EN))) {
			if (!pclk->always_on) {
				/* close abb clk */
				val = readl(pclk->enable);
				val &= (~pclk->ebits);
				writel(val, pclk->enable);
			}
		}
		/* write 0x344 register */
		val = readl(pclk->sctrl);
		val &= (~BIT(AP_ABB_EN));
		writel(val, pclk->sctrl);
	}
	hwspin_unlock(pclk->clk_hwlock);
#endif
	return;
}

static struct clk_ops hi3xxx_abb_clkgate_ops = {
	.prepare        = hi3xxx_muticore_abb_clkgate_prepare,
	.unprepare      = hi3xxx_muticore_abb_clkgate_unprepare,
};
static void __init hi3xxx_pmu_clkgate_setup(struct device_node *np)
{
	struct hi3xxx_periclk *pclk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *name, *clk_friend, *parent_names;
	void __iomem *reg_base;
	u32 rdata[2] = {0};
	u32 gdata[2] = {0};
	u32 lock_id = 0;
	struct device_node *sctrl_np;

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
	if (of_property_read_u32_array(np, "hisilicon,clkgate", &gdata[0], 2)) {
		pr_err("[%s] %s node doesn't have hisilicon,clkgate property!\n",
			 __func__, np->name);
		return;
	}
	if (of_property_read_u32_array(np, "hwspinlock-id", &lock_id, 1)) {
		pr_err("[%s] %s node doesn't have hwspinliock-id property!\n",
			 __func__, np->name);
		return;
	}

	if (of_property_read_string(np, "clock-friend-names", &clk_friend))
		clk_friend = NULL;

	if (IS_FPGA()) {
		if (NULL != of_find_property(np, "clock-fpga", NULL)) {
			if (of_property_read_string(np, "clock-fpga", &parent_names)) {
				pr_err("[%s] %s node clock-fpga value is NULL!\n",
					__func__, np->name);
				return;
			}
		} else {
			 parent_names = of_clk_get_parent_name(np, 0);
		}
	} else {
		parent_names = of_clk_get_parent_name(np, 0);
	}

	pclk = kzalloc(sizeof(struct hi3xxx_periclk), GFP_KERNEL);
	if (!pclk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		return;
	}

	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);

	if (!strcmp(clk_name, "clk_abb_192")) {
		init->ops = &hi3xxx_abb_clkgate_ops;
	} else {
		init->ops = &hi3xxx_pmu_clkgate_ops;
	}
	init->flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED;
	init->parent_names = &parent_names;
	init->num_parents = 1;

	if (of_property_read_u32_array(np, "hisilicon,hi3xxx-clkreset",
				       &rdata[0], 2)) {
		pclk->reset = NULL;
		pclk->rbits = 0;
	} else {
		pclk->reset = reg_base + rdata[0];
		pclk->rbits = rdata[1];
	}

	if (of_property_read_bool(np, "always_on"))
		pclk->always_on = 1;
	else
		pclk->always_on = 0;

	sctrl_np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (NULL == sctrl_np) {
		pr_err("[%s] fail to find sctrl node!\n", __func__);
		goto err_sctr;
	}
	pclk->sctrl = of_iomap(sctrl_np, 0);
	if (!pclk->sctrl) {
		pr_err("[%s]failed to iomap!\n", __func__);
		goto no_iomap;
	}
	pclk->sctrl = ABB_SCBAKDATA(pclk->sctrl);/*only for abb clk*/
	pclk->enable = reg_base + (gdata[0] << 2);
	pclk->ebits = BIT(gdata[1]);
	pclk->lock = &hs_clk.lock;
	pclk->hw.init = init;
	pclk->friend = clk_friend;
	pclk->flags = lock_id;
	pclk->clk_hwlock = NULL;

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
	iounmap(pclk->sctrl);
	pclk->sctrl = NULL;
no_iomap:
	of_node_put(sctrl_np);
err_sctr:
	kfree(init);
	init = NULL;
err_init:
	kfree(pclk);
	pclk = NULL;
	return;
}

static int ppll_enable_open(void *base, int ppll)
{
	u32 val;

	/* open ppll */
	val = readl(base + PPLLCTRL0(ppll));
	val |= BIT(PPLLCTRL0_EN);
	val &= (~(BIT(PPLLCTRL0_BP)));
	writel(val, (base + PPLLCTRL0(ppll)));

	return 0;
}

static int ppll_enable_ready(void *base, int ppll)
{
	u32 val;
	u32 timeout;
	timeout = 0;
	/*waiting lock*/
	do {
		val = readl(base + PPLLCTRL0(ppll));
		val &= BIT(PPLLCTRL0_LOCK);
		timeout++;
		if (AP_PPLL3_STABLE_TIME < timeout) {
		    pr_err("%s: ppll3 enable is timeout\n", __func__);
		}
	} while (!val);
	/* disable gate*/
	val = readl(base + PPLLCTRL1(ppll));
	val |= BIT(PPLLCTRL1_GT);
	writel(val, (base + PPLLCTRL1(ppll)));
	return 0;
}

static void ppll_disable(void *base, int ppll)
{
	u32 val;
	/* gate ppll */
	val = readl(base + PPLLCTRL1(ppll));
	val &= (~(BIT(PPLLCTRL1_GT)));
	writel(val, (base + PPLLCTRL1(ppll)));
	/* shutdown ppll */
	val = readl(base + PPLLCTRL0(ppll));
	val &= (~(BIT(PPLLCTRL0_EN)));
	val |= BIT(PPLLCTRL0_BP);
	writel(val, (base + PPLLCTRL0(ppll)));
}

static int hi3xxx_muticore_ppll_prepare(struct clk_hw *hw)
{
	struct hi3xxx_ppll_clk *ppll_clk;

	ppll_clk = container_of(hw, struct hi3xxx_ppll_clk, hw);

	if (PPLL0 == ppll_clk->en_cmd[1])
		return 0;
	ppll_clk->clk_hwlock = hwspin_lock_request_specific(ppll_clk->flags);
	if (NULL == ppll_clk->clk_hwlock) {
		pr_err("ppll request hwspin lock failed !\n");
		return -ENODEV;
	}
	return 0;
}

static int hi3xxx_muticore_ppll_enable(struct clk_hw *hw)
{
	struct hi3xxx_ppll_clk *ppll_clk;
	u32 ret;

	ppll_clk = container_of(hw, struct hi3xxx_ppll_clk, hw);

	/*for debug*/
	ppll_clk->ref_cnt++;

	if (PPLL0 == ppll_clk->en_cmd[1])
		return 0;
	if (1 == ppll_clk->ref_cnt) {
		if (hwspin_lock_timeout(ppll_clk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
			ppll_clk->ref_cnt--;
			pr_err("ppll hwspinlock timout!\n");
			return -ENOENT;
		}

		ppll_enable_open(ppll_clk->addr, ppll_clk->en_cmd[1]);

		ret = readl(ppll_clk->sctrl);
		ret  |= BIT(AP_POLL_EN);
		writel(ret, ppll_clk->sctrl);

		hwspin_unlock(ppll_clk->clk_hwlock);

		ppll_enable_ready(ppll_clk->addr, ppll_clk->en_cmd[1]);
	}
	return 0;
}

static void hi3xxx_muticore_ppll_disable(struct clk_hw *hw)
{
	struct hi3xxx_ppll_clk *ppll_clk;
	u32 ret;

	ppll_clk = container_of(hw, struct hi3xxx_ppll_clk, hw);

	/*for debug*/
	ppll_clk->ref_cnt--;

	if (PPLL0 == ppll_clk->dis_cmd[1])
		return ;
  #ifndef CONFIG_HISI_CLK_ALWAYS_ON
	if (!ppll_clk->ref_cnt) {
		if (hwspin_lock_timeout(ppll_clk->clk_hwlock, CLK_HWLOCK_TIMEOUT)) {
			ppll_clk->ref_cnt++;
			pr_err("ppll hwspinlock timout!\n");
			return;
		}

		ret = readl(ppll_clk->sctrl);
		if ((1 == (ret & BIT(AP_POLL_EN))) && (0 == (ret & BIT(LPM3_POLL_EN))))
			ppll_disable(ppll_clk->addr, ppll_clk->dis_cmd[1]);

		ret  &= (~(BIT(AP_POLL_EN)));
		writel(ret, ppll_clk->sctrl);

		hwspin_unlock(ppll_clk->clk_hwlock);
	}
  #endif
}

static void hi3xxx_muticore_ppll_unprepare(struct clk_hw *hw)
{
	struct hi3xxx_ppll_clk *ppll_clk;

	ppll_clk = container_of(hw, struct hi3xxx_ppll_clk, hw);

	if (PPLL0 == ppll_clk->en_cmd[1])
		return;
	if (hwspin_lock_free(ppll_clk->clk_hwlock)) {
		pr_err("hwspinlock free %d failed!\n", hwspin_lock_get_id(ppll_clk->clk_hwlock));
		return;
	}
	ppll_clk->clk_hwlock = NULL;
}

static struct clk_ops hi3xxx_ppll_ops = {
	.prepare         = hi3xxx_muticore_ppll_prepare,
	.unprepare      = hi3xxx_muticore_ppll_unprepare,
	.enable		= hi3xxx_muticore_ppll_enable,
	.disable		= hi3xxx_muticore_ppll_disable,
};

static void __init hi3xxx_ppll_setup(struct device_node *np)
{
	struct hi3xxx_ppll_clk *ppll_clk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *parent_names;
	u32 en_cmd[LPM3_CMD_LEN] = {0};
	u32 dis_cmd[LPM3_CMD_LEN] = {0};
	void __iomem *reg_base;
	struct device_node *sctrl_np;
	u32 lock_id = 0;
	u32 i;

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
	if (of_property_read_u32_array(np, "hisilicon,ipc-lpm3-cmd-en", &en_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] %s node doesn't have hisilicon,ipc-lpm3-cmd property!\n",
			 __func__, np->name);
		return;
	}
	if (of_property_read_u32_array(np, "hisilicon,ipc-lpm3-cmd-dis", &dis_cmd[0], LPM3_CMD_LEN)) {
		pr_err("[%s] %s node doesn't have hisilicon,ipc-lpm3-cmd property!\n",
			 __func__, np->name);
		return;
	}
	if (of_property_read_bool(np, "hwspinlock-id")) {
		if (of_property_read_u32_array(np, "hwspinlock-id", &lock_id, 1)) {
			pr_err("[%s] %s node doesn't have hwspinlock-id property!\n", __func__, np->name);
			return;
		}
	}
	parent_names = of_clk_get_parent_name(np, 0);

	ppll_clk = kzalloc(sizeof(struct hi3xxx_ppll_clk), GFP_KERNEL);
	if (!ppll_clk) {
		pr_err("[%s] fail to alloc pclk!\n", __func__);
		goto err_ppll_clk;
	}
	/* initialize the reference count */
	ppll_clk->ref_cnt = 0;
	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &hi3xxx_ppll_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = &parent_names;
	init->num_parents = 1;

	for (i = 0; i < LPM3_CMD_LEN; i++) {
		ppll_clk->en_cmd[i] = en_cmd[i];
		ppll_clk->dis_cmd[i] = dis_cmd[i];
	}
	sctrl_np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (NULL == sctrl_np) {
		pr_err("[%s] fail to find sctrl node!\n", __func__);
		goto err_sctr;
	}
	ppll_clk->lock = &hs_clk.lock;
	ppll_clk->hw.init = init;
	ppll_clk->addr = reg_base;
	ppll_clk->sctrl = of_iomap(sctrl_np, 0);
	if (!ppll_clk->sctrl) {
		pr_err("[%s]failed to iomap!\n", __func__);
		goto no_iomap;
	}
	ppll_clk->sctrl = PPLL3_SCBAKDATA(ppll_clk->sctrl);
	ppll_clk->flags = lock_id;
	ppll_clk->clk_hwlock = NULL;

	clk = clk_register(NULL, &ppll_clk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to reigister clk %s!\n",
			__func__, clk_name);
		goto err_clk;
	}

	clk_register_clkdev(clk, clk_name, NULL);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	return;

err_clk:
	iounmap(ppll_clk->sctrl);
	ppll_clk->sctrl = NULL;
no_iomap:
	of_node_put(sctrl_np);
err_sctr:
	kfree(init);
	init = NULL;
err_init:
	kfree(ppll_clk);
	ppll_clk = NULL;
err_ppll_clk:
	return;
}

static void hi3xxx_ppll2_disable(struct clk_hw *hw)
{
	struct hi3xxx_ppll2_clk *ppll2_clk;
	unsigned long flags = 0;
	unsigned long val;
	ppll2_clk = container_of(hw, struct hi3xxx_ppll2_clk, hw);

	if (ppll2_clk->lock)
		spin_lock_irqsave(ppll2_clk->lock, flags);
#ifndef CONFIG_HISI_CLK_ALWAYS_ON
	/* gate ppll2 */
	val = readl(ppll2_clk->gateen_reg);
	val &= ~(1 << ppll2_clk->gate_bit);
	writel(val, ppll2_clk->gateen_reg);

	/* shutdown ppll2 */
	val = readl(ppll2_clk->powerdown_reg);
	val &= ~(1 << ppll2_clk->powerdown_bit);
	val |= (1 << ppll2_clk->bp_bit);
	writel(val, ppll2_clk->powerdown_reg);
#endif
	if (ppll2_clk->lock)
		spin_unlock_irqrestore(ppll2_clk->lock, flags);
}


static int hi3xxx_ppll2_enable(struct clk_hw *hw)
{
	struct hi3xxx_ppll2_clk *ppll2_clk;
	unsigned long flags = 0;
	unsigned long val;
	ppll2_clk = container_of(hw, struct hi3xxx_ppll2_clk, hw);

	if (ppll2_clk->lock)
		spin_lock_irqsave(ppll2_clk->lock, flags);

#ifndef CONFIG_HISI_HI6250_CLK
	/*change ppll2 to 1G Hz for IVP 2015/6/18*/
	writel(0x2155555, ppll2_clk->gateen_reg);
	writel(0x903405, ppll2_clk->powerdown_reg);
#endif

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


static struct clk_ops hi3xxx_ppll2_ops = {
	.enable		= hi3xxx_ppll2_enable,
	.disable	= hi3xxx_ppll2_disable,
};

static void __init hi3xxx_ppll2_setup(struct device_node *np)
{
	struct hi3xxx_ppll2_clk *ppll2_clk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *parent_names;
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


	parent_names = of_clk_get_parent_name(np, 0);

	ppll2_clk = kzalloc(sizeof(struct hi3xxx_ppll2_clk), GFP_KERNEL);
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
	init->ops = &hi3xxx_ppll2_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = &parent_names;
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
	init = NULL;
err_init:
	kfree(ppll2_clk);
	ppll2_clk = NULL;
err_ppll2_clk:
	return;
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

static void __init hi3xxx_clkmux_setup(struct device_node *np)
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
	kfree(parent_names);
	parent_names = NULL;

	return;
err_clk:
	kfree(parent_names);
	parent_names = NULL;
	return;
}

static void __init hs_clkgate_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, *parent_names;
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
	if (of_property_read_bool(np, "always_on"))
		flags |= CLK_GATE_ALWAYS_ON_MASK;
	if (of_property_read_bool(np, "pmu32khz"))
		data[0] = data[0] << 2;

	/* gate only has the fixed parent */
	if (IS_FPGA()) {
		if (NULL != of_find_property(np, "clock-fpga", NULL)) {
			if (of_property_read_string(np, "clock-fpga", &parent_names)) {
				pr_err("[%s] %s node clock-fpga value is NULL!\n", __func__, np->name);
				return;
			}
		} else {
			parent_names = of_clk_get_parent_name(np, 0);
		}
	} else {
		parent_names = of_clk_get_parent_name(np, 0);
	}

	clk = clk_register_gate(NULL, clk_name, parent_names,
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
	return;
}

static unsigned int hi3xxx_get_table_maxdiv(const struct clk_div_table *table)
{
	unsigned int maxdiv = 0;
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div > maxdiv)
			maxdiv = clkt->div;
	return maxdiv;
}

static unsigned int hi3xxx_get_table_div(const struct clk_div_table *table,
							unsigned int val)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->val == val)
			return clkt->div;
	return 0;
}

static unsigned int hi3xxx_get_table_val(const struct clk_div_table *table,
					 unsigned int div)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div == div)
			return clkt->val;
	return 0;
}

static unsigned long hi3xxx_clkdiv_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi3xxx_divclk *dclk = container_of(hw, struct hi3xxx_divclk, hw);
	unsigned int div, val;

	val = readl(dclk->reg) >> dclk->shift;
	val &= WIDTH_TO_MASK(dclk->width);

	div = hi3xxx_get_table_div(dclk->table, val);
	if (!div) {
		pr_warn("%s: Invalid divisor for clock %s\n", __func__,
			   __clk_get_name(hw->clk));
		return parent_rate;
	}

	return parent_rate / div;
}

static bool hi3xxx_is_valid_table_div(const struct clk_div_table *table,
				      unsigned int div)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div == div)
			return true;
	return false;
}

static int hi3xxx_clkdiv_bestdiv(struct clk_hw *hw, unsigned long rate,
				 unsigned long *best_parent_rate)
{
	struct hi3xxx_divclk *dclk = container_of(hw, struct hi3xxx_divclk, hw);
	struct clk *clk_parent = __clk_get_parent(hw->clk);
	int i, bestdiv = 0;
	unsigned long parent_rate, best = 0, now, maxdiv;

	maxdiv = hi3xxx_get_table_maxdiv(dclk->table);

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
		if (!hi3xxx_is_valid_table_div(dclk->table, i))
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
		bestdiv = hi3xxx_get_table_maxdiv(dclk->table);
		*best_parent_rate = __clk_round_rate(clk_parent, 1);
	}

	return bestdiv;
}

static long hi3xxx_clkdiv_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	int div;

	if (!rate)
		rate = 1;
	div = hi3xxx_clkdiv_bestdiv(hw, rate, prate);

	return *prate / div;
}

static int hi3xxx_clkdiv_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct hi3xxx_divclk *dclk = container_of(hw, struct hi3xxx_divclk, hw);
	unsigned int div, value;
	unsigned long flags = 0;
	u32 data;

	div = parent_rate / rate;
	value = hi3xxx_get_table_val(dclk->table, div);

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
static int hi3xxx_divreg_check(struct clk_hw *hw)
{
	unsigned long rate;
	struct clk *clk = hw->clk;
	struct clk *pclk = clk_get_parent(clk);

	rate = hi3xxx_clkdiv_recalc_rate(hw, clk_get_rate(pclk));
	if (rate == clk_get_rate(clk))
		return 1;
	else
		return 0;
}

static void __iomem *hi3xxx_clkdiv_get_reg(struct clk_hw *hw)
{
	struct hi3xxx_divclk *dclk;
	void __iomem	*ret = NULL;
	u32 val = 0;

	dclk = container_of(hw, struct hi3xxx_divclk, hw);

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

static struct clk_ops hi3xxx_clkdiv_ops = {
	.recalc_rate = hi3xxx_clkdiv_recalc_rate,
	.round_rate = hi3xxx_clkdiv_round_rate,
	.set_rate = hi3xxx_clkdiv_set_rate,
#ifdef CONFIG_HISI_CLK_DEBUG
	.check_divreg = hi3xxx_divreg_check,
	.get_reg = hi3xxx_clkdiv_get_reg,
#endif
};

void __init hi3xxx_clkdiv_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, *parent_names;
	struct clk_init_data *init;
	struct clk_div_table *table;
	struct hi3xxx_divclk *dclk;
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

	if (IS_FPGA()) {
		if (NULL != of_find_property(np, "clock-fpga", NULL)) {
			if (of_property_read_string(np, "clock-fpga", &parent_names)) {
				pr_err("[%s] %s node clock-fpga value is NULL!\n",
									__func__, np->name);
				goto err_dclk;
		}
		} else {
				parent_names = of_clk_get_parent_name(np, 0);
		}
	} else {
		parent_names = of_clk_get_parent_name(np, 0);
	}

	dclk = kzalloc(sizeof(struct hi3xxx_divclk), GFP_KERNEL);
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
	init->ops = &hi3xxx_clkdiv_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = &parent_names;
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
	init = NULL;
err_init:
	kfree(dclk);
	dclk = NULL;
err_dclk:
	kfree(table);
	table = NULL;
	return;
}

static struct device_node *of_get_clk_cpu_node(int cluster)
{
	struct device_node *np = NULL, *parent;
	const u32 *mpidr;

	parent = of_find_node_by_path("/cpus");
	if (!parent) {
		pr_err("failed to find OF /cpus\n");
		return NULL;
	}

	/*
	*Get first cluster node ; big or little custer core0 must
	*contain reg and operating-points node
	*/
	for_each_child_of_node(parent, np) {
		mpidr = of_get_property(np, "reg", NULL);
		if (!mpidr) {
			pr_err("%s missing reg property\n", np->full_name);
			of_node_put(np);
			np = NULL;
			break;
		} else if (((be32_to_cpup(mpidr + 1) >> 8) & 0xff) == cluster) {
			if (!of_get_property(np, "operating-points", NULL)) {
				of_node_put(np);
				np = NULL;
			}
			break;
		}
	}

	of_node_put(parent);
	return np;
}

static struct device_node *of_get_xfreq_node(const char *xfreq)
{
	struct device_node *np;

	if (!strcmp(xfreq, "ddrfreq")) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,ddr_devfreq");
	} else if (!strcmp(xfreq, "gpufreq")) {
		np = of_find_compatible_node(NULL, NULL, "arm,mali-midgard");
	} else if (!strcmp(xfreq, "sysctrl")) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	} else {
		return NULL;
	}
	return np;
}

int xfreq_clk_table_init(struct device_node *np, u32 *freqtable, u32 *volttable)
{
	const struct property *prop;
	const __be32 *val;
	int nr;
	int k = 0;

	prop = of_find_property(np, "operating-points", NULL);
	if (!prop)
		return -ENODEV;
	if (!prop->value)
		return -ENODATA;

	/*
	 * Each OPP is a set of tuples consisting of frequency and
	 * voltage like <freq-kHz vol-uV>.
	 */
	nr = prop->length / sizeof(u32);
	if (nr % 2) {
		pr_err("%s: Invalid OPP list\n", __func__);
		return -EINVAL;
	}

	val = prop->value;
	while (nr) {
		unsigned int freq = be32_to_cpup(val++);
		unsigned int volt = be32_to_cpup(val++);
		freqtable[k] = freq;
		volttable[k] = volt;
		pr_debug("[%s]: the OPP k %d,freq %d\n", __func__, k, freq);
		nr -= 2;
		k++;
	}

	return 0;
}

static unsigned long hi3xxx_xfreq_clk_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi3xxx_xfreq_clk *xfreq_clk = container_of(hw, struct hi3xxx_xfreq_clk, hw);
	u32 rate;
	int freq_index;

	/*sysctrl SCBAKDATA4
		bit 0-3		LITTLE Cluster
		bit 4-7		BIG Cluster
		bit 8-11	DDR
		bit 12-15	GPU*/
#define MASK_CLUSTER0	0xf
#define MASK_CLUSTER1   0xf0
#define MASK_DDR	0xf00
#define MASK_GPU	0xf000

	switch (xfreq_clk->id) {
	/* cpu core0 */
	case 0:
		freq_index = readl(xfreq_clk->reg);
		freq_index &= MASK_CLUSTER0;
		rate = xfreq_clk->freq[freq_index]*1000;
        if (!rate)
		    pr_err("[%s]0 idx=%d rate=%d, xfreq_clk_addr =%p\n", __func__, freq_index, rate, xfreq_clk);
		break;
	/* cpu core1 */
	case 1:
		freq_index = readl(xfreq_clk->reg);
		freq_index &= MASK_CLUSTER1;
		freq_index = freq_index >> 4;
		rate = xfreq_clk->freq[freq_index]*1000;
        if (!rate)
		    pr_err("[%s]1 idx=%d rate=%d, xfreq_clk_addr =%p\n", __func__, freq_index, rate, xfreq_clk);
		break;
	case 2:
		freq_index = readl(xfreq_clk->reg);
		freq_index &= MASK_GPU;
		freq_index = freq_index >> 12;
		rate = xfreq_clk->freq[freq_index]*1000;
		break;
	/* DDR get freq */
	case 3:
		freq_index = readl(xfreq_clk->reg);
		freq_index &= MASK_DDR;
		freq_index = freq_index >> 8;
		rate = xfreq_clk->freq[freq_index]*1000;
		pr_debug("[%s]3 idx=%d rate=%d\n", __func__, freq_index, rate);
		break;
	/* DDR set min */
	case 4:
	default:
		rate = xfreq_clk->rate;
	}

	return rate;
}

static long hi3xxx_xfreq_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	return rate;
}

static long hi3xxx_xfreq_clk_determine_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *best_parent_rate,
					struct clk **best_parent_clk)
{
	return rate;
}

static int hi3xxx_xfreq_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct hi3xxx_xfreq_clk *xfreq_clk = container_of(hw, struct hi3xxx_xfreq_clk, hw);
	unsigned long new_rate = rate/1000000;
	int ret = 0;

	pr_debug("[%s] set rate = %ldMHZ\n", __func__, new_rate);
	xfreq_clk->set_rate_cmd[1] = new_rate;
#ifdef CONFIG_HISI_CLK_MAILBOX_SUPPORT
	ret = hisi_clkmbox_send_msg(xfreq_clk->set_rate_cmd);
	if (ret < 0) {
		pr_err("[%s]core id:%d fail to send msg to LPM3!\n",
					__func__, xfreq_clk->id);

		return -EINVAL;
	}
#endif

	xfreq_clk->rate = rate;
	return ret;
}

static struct clk_ops hi3xxx_xfreq_clk_ops = {
	.recalc_rate = hi3xxx_xfreq_clk_recalc_rate,
	.determine_rate = hi3xxx_xfreq_clk_determine_rate,
	.round_rate = hi3xxx_xfreq_clk_round_rate,
	.set_rate = hi3xxx_xfreq_clk_set_rate,
};

/*
 * xfreq_clk is used for cpufreq & devfreq.
 */
void __init hi3xxx_xfreq_clk_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, *parent_names;
	struct clk_init_data *init;
	struct hi3xxx_xfreq_clk *xfreqclk;
	u32 get_rate_cmd[LPM3_CMD_LEN], set_rate_cmd[LPM3_CMD_LEN] = {0};
	u32 device_id = 0, i = 0;
	u32 scbacdata = 0;
	void __iomem *reg_base;
	struct device_node *xfreq_np;
	int k, temp = 0;

	reg_base = hs_clk_get_base(np);
	if (!reg_base) {
		pr_err("[%s] fail to get reg_base!\n", __func__);
		return;
	}

	if (NULL == of_clk_get_parent_name(np, 0))
		parent_names = NULL;
	else
		parent_names = of_clk_get_parent_name(np, 0);

	if (of_property_read_u32(np, "hisilicon,hi3xxx-xfreq-devid", &device_id)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
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
	if (of_property_read_u32(np, "hisilicon,hi3xxx-xfreq-scbakdata", &scbacdata)) {
		pr_err("[%s] node %s doesn't hi3xxx-xfreq-scbakdata property!\n",
			__func__, np->name);
		goto err_prop;
	}

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		goto err_prop;
	}

	xfreqclk = kzalloc(sizeof(struct hi3xxx_xfreq_clk), GFP_KERNEL);
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
	init->ops = &hi3xxx_xfreq_clk_ops;
	init->parent_names = (parent_names ? &parent_names : NULL);
	init->num_parents = (parent_names ? 1 : 0);
	init->flags = CLK_IS_ROOT | CLK_GET_RATE_NOCACHE;

	for (i = 0; i < LPM3_CMD_LEN; i++) {
		xfreqclk->set_rate_cmd[i] = set_rate_cmd[i];
		xfreqclk->get_rate_cmd[i] = get_rate_cmd[i];
	}

	switch (device_id) {
	case 0:
		xfreq_np = of_get_clk_cpu_node(device_id);
		xfreq_clk_table_init(xfreq_np, &xfreqclk->freq[0], &xfreqclk->volt[0]);
		break;
	case 1:
		xfreq_np = of_get_clk_cpu_node(device_id);
		xfreq_clk_table_init(xfreq_np, &xfreqclk->freq[0], &xfreqclk->volt[0]);
		break;
	case 2:
		xfreq_np = of_get_xfreq_node("gpufreq");
	       xfreq_clk_table_init(xfreq_np, &xfreqclk->freq[0], &xfreqclk->volt[0]);
		xfreqclk->rate = 360000000;
		break;
	case 3:
	case 4:
	case 5:
		xfreq_np = of_get_xfreq_node("ddrfreq");
		xfreq_clk_table_init(xfreq_np, &xfreqclk->freq[0], &xfreqclk->volt[0]);
		/*sort lowtohigh*/
		for (i = 0; i < MAX_FREQ_NUM - 1; i++) {
			for (k = MAX_FREQ_NUM - 1; k > i; k--) {
				if (xfreqclk->freq[k] < xfreqclk->freq[k-1]) {
					temp = xfreqclk->freq[k];
					xfreqclk->freq[k] = xfreqclk->freq[k-1];
					xfreqclk->freq[k-1] = temp;
				}
			}
		}

		k = 0;
		for (i = 0; i < MAX_FREQ_NUM; i++) {
			pr_debug("1xfreqclk->freq[i]=%d\n", xfreqclk->freq[i]);
			if (xfreqclk->freq[i] == 0) {
				k++;
				continue;
			}
			xfreqclk->freq[i-k] = xfreqclk->freq[i];
		}
		if (k > 0) {
			for (i = MAX_FREQ_NUM - 1; i > MAX_FREQ_NUM - k - 1; i--)
				xfreqclk->freq[i] = 0;
		}
		for (i = 0; i < MAX_FREQ_NUM; i++)
			pr_debug("2xfreqclk->freq[i]=%d\n", xfreqclk->freq[i]);
		break;
	default:
		pr_err("[%s]dev_id is error!\n", __func__);
		goto err_clk;
	}

	xfreq_np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	xfreqclk->reg = of_iomap(xfreq_np, 0);
	xfreqclk->reg += scbacdata;
	xfreqclk->hw.init = init;
	xfreqclk->id = device_id;

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
	init = NULL;
err_init:
	kfree(xfreqclk);
	xfreqclk = NULL;
err_prop:
	return;
}

static int hi3xxx_mclk_prepare(struct clk_hw *hw)
{
	struct hi3xxx_mclk *mclk;
#ifdef CONFIG_HISI_CLK_MAILBOX_SUPPORT
	s32 ret;
#endif
	mclk = container_of(hw, struct hi3xxx_mclk, hw);
	mclk->ref_cnt++;

#ifdef CONFIG_HISI_CLK_MAILBOX_SUPPORT
	/* notify m3 when the ref_cnt of mclk is 1 */
	if (mclk->ref_cnt < 2) {
		ret = hisi_clkmbox_send_msg_sync(&mclk->en_cmd[0]);
		if (ret)
			pr_err("[%s] fail to enable clk, ret = %d!\n", __func__, ret);
	}
#endif

	return 0;
}

static void hi3xxx_mclk_unprepare(struct clk_hw *hw)
{
	struct hi3xxx_mclk *mclk;
#ifdef CONFIG_HISI_CLK_MAILBOX_SUPPORT
	s32 ret;
#endif
	mclk = container_of(hw, struct hi3xxx_mclk, hw);
	mclk->ref_cnt--;

#ifdef CONFIG_HISI_CLK_MAILBOX_SUPPORT
	/* notify m3 when the ref_cnt of gps_clk is 0 */
	if (!mclk->ref_cnt) {
		ret = hisi_clkmbox_send_msg_sync(&mclk->dis_cmd[0]);
		if (ret)
			pr_err("[%s] fail to disable clk, ret = %d!\n", __func__, ret);
	}
#endif
}

static struct clk_ops hi3xxx_mclk_ops = {
	.prepare	= hi3xxx_mclk_prepare,
	.unprepare	= hi3xxx_mclk_unprepare,
};

static void __init hi3xxx_mclk_setup(struct device_node *np)
{
	struct hi3xxx_mclk *mclk;
	struct clk_init_data *init;
	struct clk *clk;
	const char *clk_name, *parent_names;
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


	parent_names = of_clk_get_parent_name(np, 0);

	mclk = kzalloc(sizeof(struct hi3xxx_mclk), GFP_KERNEL);
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
	init->ops = &hi3xxx_mclk_ops;
	init->flags = CLK_SET_RATE_PARENT;
	init->parent_names = &parent_names;
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
	init = NULL;
err_init:
	kfree(mclk);
	mclk = NULL;
err_mclk:
	return;
}

CLK_OF_DECLARE(hi3xxx_mux, "hisilicon,hi3xxx-clk-mux", hi3xxx_clkmux_setup)
CLK_OF_DECLARE(hi3xxx_div, "hisilicon,hi3xxx-clk-div", hi3xxx_clkdiv_setup)
CLK_OF_DECLARE(hs_gate, "hisilicon,clk-gate", hs_clkgate_setup)
CLK_OF_DECLARE(hi3xxx_pmu_gate, "hisilicon,clk-pmu-gate", hi3xxx_pmu_clkgate_setup)
CLK_OF_DECLARE(hi3xxx_gate, "hisilicon,hi3xxx-clk-gate", hi3xxx_clkgate_setup)
CLK_OF_DECLARE(hi3xxx_ppll, "hisilicon,ppll-ctrl", hi3xxx_ppll_setup)
CLK_OF_DECLARE(hi3xxx_ppll2, "hisilicon,ppll2", hi3xxx_ppll2_setup)
CLK_OF_DECLARE(hi3xxx_cpu, "hisilicon,hi3xxx-xfreq-clk", hi3xxx_xfreq_clk_setup)
CLK_OF_DECLARE(hi3xxx_mclk, "hisilicon,interactive-clk", hi3xxx_mclk_setup)

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
	switch ((unsigned long)match->data) {
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
