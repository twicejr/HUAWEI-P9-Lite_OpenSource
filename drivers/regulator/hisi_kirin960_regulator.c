/*
 * Device driver for regulators in IP IC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <linux/mfd/hisi_ip_pmic.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/clk-private.h>
#include <linux/interrupt.h>
#include <linux/clk-private.h>
#include <linux/hwspinlock.h>
#include <linux/hisi/hisi_rproc.h>

#include <soc_crgperiph_interface.h>
#include <soc_sctrl_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_asp_cfg_interface.h>

#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#endif
#define	REGULATOR_HWLOCK_ID	4
#define	REGULATOR_LOCK_TIMEOUT	1000
static struct hwspinlock	*regulator_hwlock;

#if 1
#define BRAND_DEBUG(args...) pr_debug(args);
#else
#define BRAND_DEBUG(args...)
#endif

#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
extern void enable_err_probe_by_name(const char *name);
#endif

#ifdef CONFIG_HISI_FREQ_AUTODOWN
extern int hisi_freq_autodown_clk_set(char *freq_name, u32 control_flag);
#endif

enum ip_regulator_id {
	VIVOBUS_ID = 0,
	DSSSUBSYS_ID,
	VCODECSUBSYS_ID,
	VDEC_ID,
	VENC_ID,
	ISPSUBSYS_ID,
	IVP_ID,
	G3D_ID,
	ASP_ID,
	ISP_SRT_ID,
	PCIE_ID,
	MMBUF_ID,
};

/******************************macro parameter*********************************/
enum ip_regulator_flag {
	MTCMOS_FLAG = 1,
	SOFTRESET_FLAG,
	ISO_FLAG,
	TOPCSSYS_FLAG,
	CLOCK_FLAG,
	SYSCTRL_FLAG = 6,
	NOCIDLEMODE_FLAG,
	RECLOCK_FLAG,
};

enum ip_regulator_dts {
	MTCMOST_DTS = 1,
	SOTFREST_DTS,
	ISO_DTS,
	TOPCSSYS_DTS,
	CLOCK_DTS,
};

enum ip_regulator_addr_flag {
	CRGPERI_ADDR_FLAG = 0,
	DSS_ADDR_FLAG,
	SCTRL_ADDR_FLAG,
};

enum {
	REGULATOR_DISABLE = 0,
	REGULATOR_ENABLE
};
/******************************pmc/dss/sctrl parameter***************************/
/*********************noc contrl begin*********************************/
#define PMC_NOC_POWER_IDLEREQ		0x380
#define PMC_NOC_POWER_IDLEACK		0x384
#define PMC_NOC_POWER_IDLE			0x388
#define SET_NOC_IDLE_MOD_MASK		16

#define PMC_NOC_CODECSUBSYS_IDLE		(1 << 4)
#define PMC_NOC_VDEC_IDLE				(1 << 10)
#define PMC_NOC_VENC_IDLE				(1 << 11)
/*********************noc contrl end*********************************/
#define WORK_STEP_NUM					8
#define CRGPERI_ADDR_OFFSET			0x04
#define SCTRL_ADDR_OFFSET			0x04
#define AP_TO_LPM3_MSG_NUM			2
/*********************clock num begin*********************************/
#define VCODECSUBSYS_CLOCK_NUM		3
#define VDEC_CLOCK_NUM				3
#define VENC_CLOCK_NUM				3
#define SEC_P_CLOCK_NUM				1
#define PERF_ID_CLOCK_NUM			3
#define USBOTG_CLOCK_NUM			2
#define PCIE_ID_CLOCK_NUM			6
/*********************clock num end*********************************/
#define VDEC_REPAIR_DISABLE         18
#define VENC_REPAIR_DISABLE         19
/*****************************ip struct parameter*****************************/
struct hisi_regulator_ip_register_info {
	u32 mtcmos_state_reg;
	u32 mtcmos_state_mask;
	u32 mtcmos_state_addr;
	u32 mtcmos_en_reg;
	u32 mtcmos_en_mask;
	u32 mtcmos_en_addr;
	u32 swrest_en_reg;
	u32 swrest_en_mask;
	u32 swrest_en_addr;
	u32 iso_en_reg;
	u32 iso_en_mask;
	u32 iso_en_addr;
	u32 top_cssys_reg;
	u32 top_cssys_mask;
	u32 top_cssys_addr;
};

struct hisi_regulator_ip {
	const char *name;
	struct hisi_regulator_ip_register_info register_info;
	struct timeval last_off_time;
	u32 off_on_delay;
	u32 eco_uA;
	struct regulator_desc rdesc;
	int (*dt_parse)(struct hisi_regulator_ip *, struct platform_device *);
	int regulator_id;
	struct mutex regulator_lock;
	unsigned int g_enable_work_info[2][WORK_STEP_NUM];
	unsigned int g_disable_work_info[2][WORK_STEP_NUM];
	u32 lpm3_enable_value[AP_TO_LPM3_MSG_NUM];
	u32 lpm3_disable_value[AP_TO_LPM3_MSG_NUM];
	struct device_node *np;
#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
	const char *noc_node_name;
#endif
	u32 regulator_enalbe_flag;
    int regulator_fake;
};
struct hisi_regulator_addr {
	void __iomem *pmc_reg;
	void __iomem *sctrl_reg;
	void __iomem *crgperi_reg;
};
static struct hisi_regulator_addr g_regu;
/**************************control interface***************************************/
#ifdef CONFIG_HISI_FREQ_AUTODOWN
int hisi_regulator_freq_autodown_clk(int regulator_id, u32 flag)
{
	int ret = 0;

	BRAND_DEBUG("<[%s]: begin regulator_id=%d, flag=%d>\n", __func__, regulator_id, flag);
	switch (regulator_id) {
	case VCODECSUBSYS_ID:
		ret = hisi_freq_autodown_clk_set("vcodecbus", flag);
		break;
	case VDEC_ID:
		ret = hisi_freq_autodown_clk_set("vdecbus", flag);
		break;
	case VENC_ID:
		ret = hisi_freq_autodown_clk_set("vencbus", flag);
		break;
	default:
		pr_err("[%s]:Input regulator ID is not exist.", __func__);
		return -1;
	}
	BRAND_DEBUG("<[%s]: end regulator_id=%d>\n", __func__, regulator_id);
	return ret;
}
#endif
static void set_noc_enter_idle_mode(unsigned int value)
{
	unsigned int  pmc_value, pmc_value1, pmc_value2;

	pmc_value = value | (value << SET_NOC_IDLE_MOD_MASK);
	BRAND_DEBUG("<[%s]: [0X380]=0x%x>\n", __func__, pmc_value);
	writel(pmc_value, g_regu.pmc_reg + PMC_NOC_POWER_IDLEREQ);

	while (1) {
		pmc_value1 = readl(g_regu.pmc_reg + PMC_NOC_POWER_IDLEACK);
		BRAND_DEBUG("<[%s]: [0X384]=0x%x>\n", __func__, pmc_value1);
		pmc_value2 = readl(g_regu.pmc_reg + PMC_NOC_POWER_IDLE);
		BRAND_DEBUG("<[%s]: [0X388]=0x%x>\n", __func__, pmc_value2);
		if (((pmc_value1 & value) != 0) && ((pmc_value2 & value) != 0))
			break;
		udelay(1);
	}
	return ;
}
static void set_noc_exit_idle_mode(unsigned int value)
{
	unsigned int  pmc_value, pmc_value1, pmc_value2;

	pmc_value = value << SET_NOC_IDLE_MOD_MASK;
	pmc_value &=  (~value);
	BRAND_DEBUG("<[%s]: [0X380]=0x%x>\n", __func__, pmc_value);
	writel(pmc_value, g_regu.pmc_reg + PMC_NOC_POWER_IDLEREQ);

	while (1) {
		pmc_value1 = readl(g_regu.pmc_reg + PMC_NOC_POWER_IDLEACK);
		BRAND_DEBUG("<[%s]: [0X384]=0x%x>\n", __func__, pmc_value1);
		pmc_value2 = readl(g_regu.pmc_reg + PMC_NOC_POWER_IDLE);
		BRAND_DEBUG("<[%s]: [0X388]=0x%x>\n", __func__, pmc_value2);
		if (((pmc_value1 & value) == 0) && ((pmc_value2 & value) == 0))
			break;
		udelay(1);
	}
	return ;
}

static unsigned int  hisi_sctrl_regu_read(unsigned int reg)
{
	return readl(g_regu.sctrl_reg + reg);
}
static void hisi_sctrl_regu_write(unsigned int val, unsigned int reg)
{
	writel(val, g_regu.sctrl_reg + reg);
}

static void set_sctrl_memory(unsigned int repair_disable_val)
{

	/*chicago is not support memory repair function*/
	return ;
}

/*************************************************************************/
static inline struct hisi_regulator_ip_core *rdev_to_ip_core(struct regulator_dev *dev)
{
	/* regulator_dev parent to->
	 * hisi ip regulator platform device_dev parent to->
	 * hisi ip pmic platform device_dev
	 */
	return dev_get_drvdata(rdev_get_dev(dev)->parent->parent);
}

static void enable_mtcmos(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.mtcmos_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.mtcmos_en_reg,
						sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.mtcmos_en_reg,
				sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg + 0x08]=0x%x>\n", __func__,
				hisi_regulator_ip_core_read(pmic, sreg->register_info.mtcmos_en_reg + 0x08));
	} else if (sreg->register_info.mtcmos_en_addr == SCTRL_ADDR_FLAG) {
		hisi_sctrl_regu_write(sreg->register_info.mtcmos_en_mask, sreg->register_info.mtcmos_en_reg);
		BRAND_DEBUG("<[%s]: [reg:0x%x] [value:0x%x]>\n", __func__, sreg->register_info.mtcmos_en_reg, sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [reg + 0x08]=0x%x>\n", __func__, hisi_sctrl_regu_read(sreg->register_info.mtcmos_en_reg + 0x08));
	} else
		pr_err("Input addr not exist!\n\r");

	return;
}
static void disable_mtcmos(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.mtcmos_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.mtcmos_en_reg + CRGPERI_ADDR_OFFSET,
						sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.mtcmos_en_reg + CRGPERI_ADDR_OFFSET,
				sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg + 0x04]=0x%x>\n", __func__,
				hisi_regulator_ip_core_read(pmic, (sreg->register_info.mtcmos_en_reg + CRGPERI_ADDR_OFFSET + 0x04)));
	} else if (sreg->register_info.mtcmos_en_addr == SCTRL_ADDR_FLAG) {
		hisi_sctrl_regu_write(sreg->register_info.mtcmos_en_mask, sreg->register_info.mtcmos_en_reg + SCTRL_ADDR_OFFSET);
		BRAND_DEBUG("<[%s]: [reg:0x%x] [value:0x%x]>\n", __func__, sreg->register_info.mtcmos_en_reg, sreg->register_info.mtcmos_en_mask);
		BRAND_DEBUG("<[%s]: [reg + 0x08]=0x%x>\n", __func__, hisi_sctrl_regu_read(sreg->register_info.mtcmos_en_reg + 0x08));
	} else
		pr_err("Input addr not exist!\n\r");

	return;
}

static void enable_softrst(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.swrest_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.swrest_en_reg,
						sreg->register_info.swrest_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.swrest_en_reg,
				sreg->register_info.swrest_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg+ 0x08]=0x%x>\n", __func__,
				hisi_regulator_ip_core_read(pmic, sreg->register_info.swrest_en_reg + 0x08));

	} else if (sreg->register_info.swrest_en_addr == DSS_ADDR_FLAG) {
		/*bypass*/
	} else
		pr_err("Input addr not exist!\n\r");

	return;
}
static void disable_softrst(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.swrest_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.swrest_en_reg + CRGPERI_ADDR_OFFSET,
						sreg->register_info.swrest_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.swrest_en_reg + CRGPERI_ADDR_OFFSET,
				sreg->register_info.swrest_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg + 0x04]=0x%x>\n", __func__,
				hisi_regulator_ip_core_read(pmic, (sreg->register_info.swrest_en_reg + CRGPERI_ADDR_OFFSET + 0x04)));
	} else if (sreg->register_info.swrest_en_addr == DSS_ADDR_FLAG) {
		/*bypass*/
	} else {
		pr_err("Input addr not exist!\n\r");
	}
	return;
}
static inline void enable_iso(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.iso_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.iso_en_reg,
						sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.iso_en_reg, sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg + 0x08]=0x%x>\n", __func__, hisi_regulator_ip_core_read(pmic, sreg->register_info.iso_en_reg + 0x08));
	} else if (sreg->register_info.iso_en_addr == SCTRL_ADDR_FLAG) {
		hisi_sctrl_regu_write(sreg->register_info.iso_en_mask, sreg->register_info.iso_en_reg);
		BRAND_DEBUG("<[%s]: [reg:0x%x] [value:0x%x]>\n", __func__, sreg->register_info.iso_en_reg, sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [reg + 0x08]=0x%x>\n", __func__, hisi_sctrl_regu_read(sreg->register_info.iso_en_reg + 0x08));
	} else
		pr_err("Input addr not exist!\n\r");

	return;
}

static inline void disable_iso(struct hisi_regulator_ip_core *pmic, struct hisi_regulator_ip *sreg)
{
	if (pmic == NULL || sreg ==  NULL)
		return;

	if (sreg->register_info.iso_en_addr == CRGPERI_ADDR_FLAG) {
		hisi_regulator_ip_core_write(pmic, sreg->register_info.iso_en_reg + CRGPERI_ADDR_OFFSET,
						sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [pmic:0x%p] [reg:0x%x] [value:0x%x]>\n", __func__, pmic->regs, sreg->register_info.iso_en_reg + CRGPERI_ADDR_OFFSET,
				sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [pmic + reg + 0x04]=0x%x>\n", __func__,
				hisi_regulator_ip_core_read(pmic, (sreg->register_info.iso_en_reg + CRGPERI_ADDR_OFFSET + 0x04)));
	} else if (sreg->register_info.iso_en_addr == SCTRL_ADDR_FLAG) {
		hisi_sctrl_regu_write(sreg->register_info.iso_en_mask, sreg->register_info.iso_en_reg + SCTRL_ADDR_OFFSET);
		BRAND_DEBUG("<[%s]: [reg:0x%x] [value:0x%x]>\n", __func__, sreg->register_info.iso_en_reg, sreg->register_info.iso_en_mask);
		BRAND_DEBUG("<[%s]: [reg + 0x08]=0x%x>\n", __func__, hisi_sctrl_regu_read(sreg->register_info.iso_en_reg + 0x08));
	} else
		pr_err("Input addr not exist!\n\r");

	return;
}

void set_top_cssys_softreset_off(struct hisi_regulator_ip_core *pmic,
												struct hisi_regulator_ip *sreg)
{
	return;
}

static struct clk *of_regulator_clk_get(struct device_node *node , int index)
{
	struct clk *clk;
	const char *clk_name;
	int ret = 0;
	ret = of_property_read_string_index(node, "clock-names", index, &clk_name);
	if (ret != 0) {
		pr_err("failed to get regulator clk resource! ret=%d.\n", ret);
		return ERR_PTR(-EINVAL);
	}
	clk = clk_get(NULL, clk_name);
	if (IS_ERR(clk)) {
		pr_err(" %s: %s %d get failed!\n", __func__ , clk_name, __LINE__);
		return ERR_PTR(-EINVAL);
	}

	return clk;
}

static int  hisi_ip_clock_step(struct hisi_regulator_ip *sreg, int clock_num, int flag)
{
	struct clk *temp_clock;
	int i, ret = 0;
	for (i = 0; i < clock_num; i++) {
		temp_clock = of_regulator_clk_get(sreg->np, i);
		if (IS_ERR(temp_clock)) {
			temp_clock = NULL;
			return -EINVAL;
		}
		/*flag: 0 disable clock; 1 enable clock*/
		if (flag == REGULATOR_ENABLE) {
			ret = clk_prepare_enable(temp_clock);
			BRAND_DEBUG("<[%s]: clock enable clock_name=%s>\n", __func__, temp_clock->name);
			if (ret) {
				pr_err("Regulator ip:regulator_id[%d],clock_id[%d] enable failed\r\n", sreg->regulator_id, i);
				clk_put(temp_clock);
				return ret;
			}
		} else {
			BRAND_DEBUG("<[%s]: clock disable clock_name=%s>\n", __func__, temp_clock->name);
			clk_disable_unprepare(temp_clock);
			clk_put(temp_clock);
		}
	}
	return ret;
}

static int hisi_ip_clock_work(struct hisi_regulator_ip *sreg, int flag)
{
	int ret = 0;

	if (sreg->regulator_id == VCODECSUBSYS_ID) {
		hisi_ip_clock_step(sreg, VCODECSUBSYS_CLOCK_NUM, flag);
		BRAND_DEBUG("<[%s]: clock addr[0xD0]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0xD0));
		BRAND_DEBUG("<[%s]: clock addr[0xF8]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0xF8));
		BRAND_DEBUG("<[%s]: clock addr[0x418]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0x418));
		BRAND_DEBUG("<[%s]: clock addr[0x008]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0x008));
	} else if (sreg->regulator_id == VDEC_ID) {
		hisi_ip_clock_step(sreg, VDEC_CLOCK_NUM, flag);
		BRAND_DEBUG("<[%s]: clock addr[0xF0]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0xF0));
		BRAND_DEBUG("<[%s]: clock addr[0x38]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0x38));
	} else if (sreg->regulator_id == VENC_ID) {
		hisi_ip_clock_step(sreg, VENC_CLOCK_NUM, flag);
		BRAND_DEBUG("<[%s]: clock addr[0xF4]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0xF4));
		BRAND_DEBUG("<[%s]: clock addr[0x38]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0x38));
	} else if (sreg->regulator_id == PCIE_ID) {
		hisi_ip_clock_step(sreg, PCIE_ID_CLOCK_NUM, flag);
		BRAND_DEBUG("<[%s]: clock addr[0x268]=0x%x>\n", __func__, readl(g_regu.sctrl_reg + 0x268));
		BRAND_DEBUG("<[%s]: clock addr[0x428]=0x%x>\n", __func__, readl(g_regu.crgperi_reg + 0x428));
		BRAND_DEBUG("<[%s]: clock addr[0x198]=0x%x>\n", __func__, readl(g_regu.sctrl_reg + 0x198));
	} else {
		/*bypass*/
	}
	return ret;
}

#define CHANGE_FUNC_TYPE  void (*) (struct hisi_regulator_ip_core *, struct hisi_regulator_ip *)

static void(*g_enable_func[])(struct hisi_regulator_ip_core *, struct hisi_regulator_ip *) = {
	[MTCMOS_FLAG]		= enable_mtcmos,
	[SOFTRESET_FLAG]	= disable_softrst,
	[ISO_FLAG]			= disable_iso,
	[TOPCSSYS_FLAG]			= set_top_cssys_softreset_off,
	[SYSCTRL_FLAG]		= (CHANGE_FUNC_TYPE) set_sctrl_memory,
	[NOCIDLEMODE_FLAG]	= (CHANGE_FUNC_TYPE) set_noc_exit_idle_mode,
};
static void(*g_disable_func[])(struct hisi_regulator_ip_core *, struct hisi_regulator_ip *) = {
	[MTCMOS_FLAG]		= disable_mtcmos,
	[SOFTRESET_FLAG]	= enable_softrst,
	[ISO_FLAG]			= enable_iso,
	[NOCIDLEMODE_FLAG]	= (CHANGE_FUNC_TYPE) set_noc_enter_idle_mode,
};

/*******************************regulator interface********************************/
static int hisi_ip_is_enabled(struct regulator_dev *dev)
{
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	struct hisi_regulator_ip_core *pmic = rdev_to_ip_core(dev);

	if (sreg == NULL || pmic == NULL) {
		pr_err("[%s]regulator get  para is err!\n", __func__);
		return -EINVAL;
	}

	return sreg->regulator_enalbe_flag;
}

static int hisi_ip_regulator_enabled(struct regulator_dev *dev)
{
	int i;
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	struct hisi_regulator_ip_core *pmic = rdev_to_ip_core(dev);
#ifdef CONFIG_HISI_FREQ_AUTODOWN
    int ret = 0;
#endif
	if (sreg == NULL || pmic == NULL) {
		pr_err("[%s]regulator get  para is err!\n", __func__);
		return -EINVAL;
	}

    if (sreg->regulator_fake) {
        sreg->regulator_enalbe_flag = 1;
        return 0;
	}

#ifdef CONFIG_HISI_FREQ_AUTODOWN
	if (sreg->regulator_id == VCODECSUBSYS_ID ||\
		sreg->regulator_id == VDEC_ID ||\
		sreg->regulator_id == VENC_ID) {
		ret = hisi_regulator_freq_autodown_clk(sreg->regulator_id, REGULATOR_DISABLE);
		if (ret) {
			pr_err("[%s]hisi freq auto down is failed. ret[%d]!\n", __func__, ret);
		}
	}
#endif

	mutex_lock(&sreg->regulator_lock);
	BRAND_DEBUG("\n<[%s]: begin regulator_id=%d>\n", __func__, sreg->regulator_id);
	for (i = 0; i < WORK_STEP_NUM; i++) {
		if (sreg->g_enable_work_info[0][i] == 0)
			break;

		if (TOPCSSYS_FLAG >= sreg->g_enable_work_info[0][i]) {
			g_enable_func[sreg->g_enable_work_info[0][i]](pmic, sreg);
			if (0 != sreg->g_enable_work_info[1][i])
				udelay(sreg->g_enable_work_info[1][i]);
		}

		if (sreg->g_enable_work_info[0][i] == SYSCTRL_FLAG) {
			if (sreg->regulator_id == VDEC_ID) {
				((void (*) (unsigned int)) g_enable_func[SYSCTRL_FLAG])(VDEC_REPAIR_DISABLE);
			} else if (sreg->regulator_id == VENC_ID) {
				((void (*) (unsigned int)) g_enable_func[SYSCTRL_FLAG])(VENC_REPAIR_DISABLE);
			} else {
				/*bypass*/
			}
			if (0 != sreg->g_enable_work_info[1][i])
				udelay(sreg->g_enable_work_info[1][i]);
		}

		if (sreg->g_enable_work_info[0][i] == NOCIDLEMODE_FLAG) {
			if (sreg->regulator_id == VCODECSUBSYS_ID) {
				((void (*) (unsigned int)) g_enable_func[NOCIDLEMODE_FLAG])(PMC_NOC_CODECSUBSYS_IDLE);
			} else if (sreg->regulator_id == VDEC_ID) {
				((void (*) (unsigned int)) g_enable_func[NOCIDLEMODE_FLAG])(PMC_NOC_VDEC_IDLE);
			} else if (sreg->regulator_id == VENC_ID) {
				((void (*) (unsigned int)) g_enable_func[NOCIDLEMODE_FLAG])(PMC_NOC_VENC_IDLE);
			} else {
				/*bypass*/
			}
			if (0 != sreg->g_enable_work_info[1][i])
				udelay(sreg->g_enable_work_info[1][i]);
		}

		if (sreg->g_enable_work_info[0][i] == CLOCK_FLAG) {
			hisi_ip_clock_work(sreg, REGULATOR_ENABLE);
			if (0 != sreg->g_enable_work_info[1][i])
				udelay(sreg->g_enable_work_info[1][i]);
		}

		if (sreg->g_enable_work_info[0][i] == RECLOCK_FLAG) {
			hisi_ip_clock_work(sreg, REGULATOR_ENABLE);
			udelay(1);
			hisi_ip_clock_work(sreg, REGULATOR_DISABLE);
			udelay(1);
		}
	}

#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
	/* enable errprobe  */
	if (sreg->noc_node_name)
			enable_err_probe_by_name(sreg->noc_node_name);
#endif

#ifdef CONFIG_HISI_FREQ_AUTODOWN
	if (sreg->regulator_id == VCODECSUBSYS_ID ||\
		sreg->regulator_id == VDEC_ID ||\
		sreg->regulator_id == VENC_ID) {
		ret = hisi_regulator_freq_autodown_clk(sreg->regulator_id, REGULATOR_ENABLE);
		if (ret) {
			pr_err("[%s]hisi freq auto down is failed. ret[%d]!\n", __func__, ret);
		}
	}
#endif

	sreg->regulator_enalbe_flag = 1;
	BRAND_DEBUG("<[%s]: end regulator_id=%d>\n", __func__, sreg->regulator_id);
	mutex_unlock(&sreg->regulator_lock);

	return 0;
}

static int hisi_ip_regulator_disabled(struct regulator_dev *dev)
{
	int  i;
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	struct hisi_regulator_ip_core *pmic = rdev_to_ip_core(dev);
#ifdef CONFIG_HISI_FREQ_AUTODOWN
    int ret = 0;
#endif
	if (sreg == NULL || pmic == NULL) {
		pr_err("[%s]: regulator get  para is err!\n", __func__);
		return -EINVAL;
	}

    if (sreg->regulator_fake) {
        sreg->regulator_enalbe_flag = 0;
        return 0;
	}

	mutex_lock(&sreg->regulator_lock);
	BRAND_DEBUG("\n<[%s]: begin regulator_id=%d>\n", __func__, sreg->regulator_id);
#ifdef CONFIG_HISI_FREQ_AUTODOWN
	if (sreg->regulator_id == VCODECSUBSYS_ID ||\
		sreg->regulator_id == VDEC_ID ||\
		sreg->regulator_id == VENC_ID) {
		ret = hisi_regulator_freq_autodown_clk(sreg->regulator_id, REGULATOR_DISABLE);
		if (ret) {
			pr_err("[%s]hisi freq auto down is failed. ret[%d]!\n", __func__, ret);
		}
	}
#endif
	for (i = 0; i < WORK_STEP_NUM; i++) {
		if (sreg->g_disable_work_info[0][i] == 0)
			break;

		if (ISO_FLAG >= sreg->g_disable_work_info[0][i]) {
			g_disable_func[sreg->g_disable_work_info[0][i]](pmic, sreg);
			if (0 != sreg->g_disable_work_info[1][i])
				udelay(sreg->g_disable_work_info[1][i]);
		}

		if (sreg->g_disable_work_info[0][i] == NOCIDLEMODE_FLAG) {
			if (sreg->regulator_id == VCODECSUBSYS_ID) {
				((void (*) (unsigned int)) g_disable_func[NOCIDLEMODE_FLAG])(PMC_NOC_CODECSUBSYS_IDLE);
			} else if (sreg->regulator_id == VDEC_ID) {
				((void (*) (unsigned int)) g_disable_func[NOCIDLEMODE_FLAG])(PMC_NOC_VDEC_IDLE);
			} else if (sreg->regulator_id == VENC_ID) {
				((void (*) (unsigned int)) g_disable_func[NOCIDLEMODE_FLAG])(PMC_NOC_VENC_IDLE);
			} else {
				/*bypass*/
			}
			if (0 != sreg->g_disable_work_info[1][i])
				udelay(sreg->g_disable_work_info[1][i]);
		}

		if (sreg->g_disable_work_info[0][i] == CLOCK_FLAG) {
			hisi_ip_clock_work(sreg, REGULATOR_DISABLE);
			if (0 != sreg->g_disable_work_info[1][i])
				udelay(sreg->g_disable_work_info[1][i]);
		}
	}
	sreg->regulator_enalbe_flag = 0;
	BRAND_DEBUG("<[%s]: end regulator_id=%d>\n", __func__, sreg->regulator_id);
	mutex_unlock(&sreg->regulator_lock);
	return 0;
}

/**************************remote processor control****************************************/
#if defined(CONFIG_HISI_RPROC)
static int hisi_ip_regulator_cmd_send(struct regulator_dev *dev, int cmd)
{
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	rproc_msg_t ack_buffer[2] = {0};
	rproc_msg_t *tx_buffer = NULL;
	int err = 0;

	if (sreg == NULL) {
		pr_err("[%s]regulator get  para is err!\n", __func__);
		return -EINVAL;
	}

	if (REGULATOR_ENABLE == cmd)
		tx_buffer = sreg->lpm3_enable_value;
	else
		tx_buffer = sreg->lpm3_disable_value;

	BRAND_DEBUG("<[%s]: send msg to  tx_buffer[0]=0x%x>\n", __func__, tx_buffer[0]);
	BRAND_DEBUG("<[%s]: send msg to  tx_buffer[1]=0x%x>\n", __func__, tx_buffer[1]);

	err = RPROC_SYNC_SEND(HISI_RPROC_LPM3_MBX14, tx_buffer,
		AP_TO_LPM3_MSG_NUM, ack_buffer, AP_TO_LPM3_MSG_NUM);
	if (err || (ack_buffer[0] != tx_buffer[0]) || ((ack_buffer[1] >> 24) != 0x0)) {
		pr_err("%s: regulator ID[%d] rproc sync send err!\n",
						__func__, sreg->regulator_id);
		return -EINVAL;
	}

	return 0;
}

/**************************g3d****************************************/
static int hisi_ip_to_lpm3_is_enabled(struct regulator_dev *dev)
{
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	struct hisi_regulator_ip_core *pmic = rdev_to_ip_core(dev);

	if (sreg == NULL || pmic == NULL) {
		pr_err("[%s]regulator get  para is err!\n", __func__);
		return -EINVAL;
	}

	return sreg->regulator_enalbe_flag;
}

static int hisi_ip_lpm3_enabled(struct regulator_dev *dev)
{
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	int ret = 0;
	BRAND_DEBUG("\n<[%s]: begin regulator_id=%d>\n", __func__, sreg->regulator_id);

    if (sreg->regulator_fake) {
        sreg->regulator_enalbe_flag = 1;
        return 0;
	}

	ret = hisi_ip_regulator_cmd_send(dev, REGULATOR_ENABLE);
	if (!ret) {
		sreg->regulator_enalbe_flag = 1;
	} else {
		pr_err("%s:hisi ip send enable ldo[%s] to lpm3 failled!\n\r", __func__, sreg->name);
	}
#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
	/* enable noc errprobe */
	if (sreg->noc_node_name)
		enable_err_probe_by_name(sreg->noc_node_name);
#endif
	BRAND_DEBUG("<[%s]: end regulator_id=%d>\n", __func__, sreg->regulator_id);
	return ret;
}

static int hisi_ip_lpm3_disabled(struct regulator_dev *dev)
{
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(dev);
	int ret = 0;

	BRAND_DEBUG("\n<[%s]: begin regulator_id=%d>\n", __func__, sreg->regulator_id);

    if (sreg->regulator_fake) {
        sreg->regulator_enalbe_flag = 0;
        return 0;
	}

	ret = hisi_ip_regulator_cmd_send(dev, REGULATOR_DISABLE);
	if (!ret || (-ETIMEOUT == ret)) {
		sreg->regulator_enalbe_flag = 0;
		ret = 0;
	} else {
		pr_err("%s:hisi ip send disable ldo[%s] to lpm3 failled!\n\r", __func__, sreg->name);
	}
	BRAND_DEBUG("<[%s]: end regulator_id=%d>\n", __func__, sreg->regulator_id);
	return ret;
}
#else
static int hisi_ip_to_lpm3_is_enabled(struct regulator_dev *dev)
{
	return 0;
}

static int hisi_ip_lpm3_enabled(struct regulator_dev *dev)
{
	return 0;
}
static int hisi_ip_lpm3_disabled(struct regulator_dev *dev)
{
	return 0;
}
#endif
/******************************resolve ip dtsv interface************************/
static int hisi_mtcmos_dt_parse_common(struct hisi_regulator_ip *sreg,
					struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	unsigned int register_info[3] = {0};
	int ret = 0;
	/* parse .hisi mtcmos state.ctrl_reg */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-mtcmos-state-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi mtcmos state property set\n");
		goto dt_parse_common_end;
	}
	sreg->register_info.mtcmos_state_reg = register_info[0];
	sreg->register_info.mtcmos_state_mask = register_info[1];
	sreg->register_info.mtcmos_state_addr = register_info[2];

	/* parse .hisi mtcmos enable.ctrl_reg */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-mtcmos-en-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi mtcmos enable property set\n");
		goto dt_parse_common_end;
	}
	sreg->register_info.mtcmos_en_reg = register_info[0];
	sreg->register_info.mtcmos_en_mask = register_info[1];
	sreg->register_info.mtcmos_en_addr = register_info[2];
	return 0;
dt_parse_common_end:
	return ret;

}

static int hisi_swreset_dt_parse_common(struct hisi_regulator_ip *sreg,
					struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	unsigned int register_info[3] = {0};
	int ret = 0;

	/* parse .hisi software reset enable.ctrl_reg */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-sw-reset-en-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi software reset enable property set\n");
		goto dt_parse_common_end;
	}
	sreg->register_info.swrest_en_reg = register_info[0];
	sreg->register_info.swrest_en_mask = register_info[1];
	sreg->register_info.swrest_en_addr = register_info[2];
	return 0;
dt_parse_common_end:
	return ret;
}
static int hisi_isocontrol_dt_parse_common(struct hisi_regulator_ip *sreg,
					struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	unsigned int register_info[3] = {0};
	int ret = 0;

	/* parse .hisi iso enable.ctrl_reg */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-iso-en-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi iso enable property set\n");
		goto dt_parse_common_end;
	}
	sreg->register_info.iso_en_reg = register_info[0];
	sreg->register_info.iso_en_mask = register_info[1];
	sreg->register_info.iso_en_addr = register_info[2];
	return 0;
dt_parse_common_end:
	return ret;
}
static int hisi_topcssyscontrol_dt_parse_common(struct hisi_regulator_ip *sreg,
					struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	unsigned int register_info[3] = {0};
	int ret = 0;

	/* parse .hisi top cssys ctrl_reg */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-top-cssys-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi iso disable property set\n");
		goto dt_parse_common_end;
	}
	sreg->register_info.top_cssys_reg = register_info[0];
	sreg->register_info.top_cssys_mask = register_info[1];
	sreg->register_info.top_cssys_addr = register_info[2];

	return 0;
dt_parse_common_end:
	return ret;
}

static int hisi_regulatorid_dt_parse_common(struct hisi_regulator_ip *sreg,
					struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int id = 0, fake= 0;
	int ret = 0;

	/* regulator-id */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-regulator-id",
						&id, 1);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi-regulator-id property set\n");
		goto dt_parse_common_end;
	}
	sreg->regulator_id = id;

    /* regulator-fake */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-regulator-is-fake",
						&fake, 1);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi-regulator-is-fake property set\n");
		goto dt_parse_common_end;
	}
	sreg->regulator_fake = fake;

	return 0;
dt_parse_common_end:
	return ret;
}

#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
static int hisi_noc_dt_parse(struct hisi_regulator_ip *sreg,
				struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret = 0;

	/* noc_node_name */
	ret = of_property_read_string(np, "hisi,noc-node-name", &sreg->noc_node_name);
	if (ret) {
		pr_debug("no hisi,noc-node-name property found\n");
	}

	return ret;
}
#endif

static int(*g_dts_func[])(struct hisi_regulator_ip *, struct platform_device *) = {
	[MTCMOST_DTS]	= hisi_mtcmos_dt_parse_common,
	[SOTFREST_DTS]	= hisi_swreset_dt_parse_common,
	[ISO_DTS]		= hisi_isocontrol_dt_parse_common,
	[TOPCSSYS_DTS]	= hisi_topcssyscontrol_dt_parse_common,
};

/************************* dts solve***************************************/
static int hisi_regualtor_dt_parse_common(struct hisi_regulator_ip *sreg,
				struct platform_device *pdev)
{
	struct device *dev = NULL;
	struct device_node *np = NULL;
	unsigned int register_info0[WORK_STEP_NUM] = {0};
	unsigned int register_info1[WORK_STEP_NUM] = {0};
	int i;
	int ret = 0;
	if (sreg == NULL || pdev == NULL) {
		pr_err("[%s]regulator get dt para is err!\n", __func__);
		return -EINVAL;
	}

	dev = &pdev->dev;
	np = dev->of_node;

	/* regulator-id */
	ret = hisi_regulatorid_dt_parse_common(sreg, pdev);
	if (ret) {
		pr_err("[%s] regulatorid get error!\n", __func__);
		goto dt_parse_common_end;
	}

	ret = of_property_read_u32_array(np, "ip_regulator_operation_enable_step",
						register_info0, WORK_STEP_NUM);
	if (ret) {
		dev_err(dev, "no ip regulator operation enable step\n");
		goto dt_parse_common_end;
	}
	ret = of_property_read_u32_array(np, "ip_regulator_enable_delay_time",
						register_info1, WORK_STEP_NUM);
	if (ret) {
		dev_err(dev, "no ip regulator enable delay time\n");
		goto dt_parse_common_end;
	}

	for (i = 0; i < WORK_STEP_NUM; i++) {
		sreg->g_enable_work_info[0][i] = register_info0[i];
		sreg->g_enable_work_info[1][i] = register_info1[i];
	}

	for (i = 0; i < WORK_STEP_NUM; i++) {
		if (sreg->g_enable_work_info[0][i] == CLOCK_FLAG ||/*clock*/
					sreg->g_enable_work_info[0][i] == SYSCTRL_FLAG ||/*sysctrl*/
					sreg->g_enable_work_info[0][i] == NOCIDLEMODE_FLAG ||/*nocidlemode*/
					sreg->g_enable_work_info[0][i] == RECLOCK_FLAG)/*repeat clock*/
			continue;

		if (sreg->g_enable_work_info[0][i] != 0) {
			ret = g_dts_func[sreg->g_enable_work_info[0][i]](sreg, pdev);
			if (ret) {
				pr_err("[%s] mtcmos control error!\n", __func__);
				goto dt_parse_common_end;
			}
		} else {
			break;
		}
	}

	ret = of_property_read_u32_array(np, "ip_regulator_operation_disable_step",
						register_info0, WORK_STEP_NUM);
	if (ret) {
		dev_err(dev, "no ip regulator operation disable step\n");
		goto dt_parse_common_end;
	}
	ret = of_property_read_u32_array(np, "ip_regulator_disable_delay_time",
						register_info1, WORK_STEP_NUM);
	if (ret) {
		dev_err(dev, "no ip regulator disable delay time\n");
		goto dt_parse_common_end;
	}
	for (i = 0; i < WORK_STEP_NUM; i++) {
		sreg->g_disable_work_info[0][i] = register_info0[i];
		sreg->g_disable_work_info[1][i] = register_info1[i];
	}

#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
	hisi_noc_dt_parse(sreg, pdev);
#endif

	return 0;

dt_parse_common_end:
	return ret;
}

static int hisi_dt_parse_ip_lpm3(struct hisi_regulator_ip *sreg,
				struct platform_device *pdev)
{
	struct device *dev = NULL;
	struct device_node *np = NULL;
	int id = 0, fake = 0;
	unsigned int register_info[2] = {0};
	int ret = 0;

	if (sreg == NULL || pdev == NULL) {
		pr_err("[%s]regulator get  dt para is err!\n", __func__);
		return -EINVAL;
	}

	dev = &pdev->dev;
	np = dev->of_node;

	/* parse .hisi top cssys ctrl_reg */
	ret = of_property_read_u32_array(np, "ip_to_lpm3_enable_step",
						register_info, AP_TO_LPM3_MSG_NUM);
	if (ret) {
		dev_err(dev, "no hisilicon, ip to lpm3 enable property set\n");
		goto dt_parse_common_end;
	}
	sreg->lpm3_enable_value[0] = register_info[0];
	sreg->lpm3_enable_value[1] = register_info[1];

	/* parse .hisi top cssys ctrl_reg */
	ret = of_property_read_u32_array(np, "ip_to_lpm3_disable_step",
						register_info, AP_TO_LPM3_MSG_NUM);
	if (ret) {
		dev_err(dev, "no hisilicon,ip to lpm3 disable property set\n");
		goto dt_parse_common_end;
	}
	sreg->lpm3_disable_value[0] = register_info[0];
	sreg->lpm3_disable_value[1] = register_info[1];

	ret = of_property_read_u32_array(np, "hisilicon,hisi-regulator-id",
						&id, 1);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi-regulator-id property set\n");
		goto dt_parse_common_end;
	}
	sreg->regulator_id = id;

	/* regulator-fake */
	ret = of_property_read_u32_array(np, "hisilicon,hisi-regulator-is-fake",
						&fake, 1);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi-regulator-is-fake property set\n");
		goto dt_parse_common_end;
	}
	sreg->regulator_fake = fake;

#ifdef CONFIG_HISI_NOC_HI3660_PLATFORM
	hisi_noc_dt_parse(sreg, pdev);
#endif
dt_parse_common_end:
	return ret;
}

/******************************ip voltage region ops*************************/
struct regulator_ops hisi_ip_regulator_rops = {
	.is_enabled = hisi_ip_is_enabled,
	.enable = hisi_ip_regulator_enabled,
	.disable = hisi_ip_regulator_disabled,
};
struct regulator_ops hisi_ip_lpm3_rops = {
	.is_enabled = hisi_ip_to_lpm3_is_enabled,
	.enable = hisi_ip_lpm3_enabled,
	.disable = hisi_ip_lpm3_disabled,
};

/******************************hisi_regulator_ip******************************/
static const struct hisi_regulator_ip hisi_regulator_ip_regulator = {
	.rdesc = {
		.ops = &hisi_ip_regulator_rops,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	},
	.dt_parse = hisi_regualtor_dt_parse_common,
};

static const struct hisi_regulator_ip hisi_regulator_ip_lpm3 = {
	.rdesc = {
		.ops = &hisi_ip_lpm3_rops,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	},
	.dt_parse = hisi_dt_parse_ip_lpm3,
};

/*********************of_hisi_regulator_ip_match_tbl***************************/
static struct of_device_id of_hisi_regulator_ip_match_tbl[] = {
	{
		.compatible = "ip-regulator-type1",
		.data = &hisi_regulator_ip_regulator,
	},
	{
		.compatible = "ip-regulator-type2",
		.data = &hisi_regulator_ip_lpm3,
	},
	{ /* end */ }
};
#ifdef CONFIG_DEBUG_FS
static int dbg_control_vcc_show(struct seq_file *s, void *data)
{
	pr_info("dbg_control_hisi_ip_show \n\r");
	return 0;
}
static ssize_t dbg_control_vcc_set_value(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		if (index == 0) {

		} else if (index == 1) {

		} else {
			pr_info("ERRR~\n");
		}
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

static int dbg_control_vcc_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return single_open(file, dbg_control_vcc_show, &inode->i_private);
}

static const struct file_operations set_control_vcc_fops = {
	.open		= dbg_control_vcc_open,
	.read		= seq_read,
	.write		= dbg_control_vcc_set_value,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif

static int hisi_regulator_ip_probe(struct platform_device *pdev)
{
	struct device *dev = NULL;
	struct device_node *np = NULL;
	struct regulator_desc *rdesc;
	struct regulator_dev *rdev;
	struct hisi_regulator_ip *sreg = NULL;
	struct regulator_init_data *initdata;
	struct regulator_config config = { };
	const struct of_device_id *match;
	const struct hisi_regulator_ip *temp = NULL;
	int ret = 0;
	static int regulator_flag;
	const char *supplyname = NULL;
#ifdef CONFIG_DEBUG_FS
	struct dentry *d;
#endif

	if (pdev == NULL) {
		pr_err("[%s]regulator get  platform device para is err!\n", __func__);
		return -EINVAL;
	}

	dev = &pdev->dev;
	np = dev->of_node;

	/* to check which type of regulator this is */
	match = of_match_device(of_hisi_regulator_ip_match_tbl, &pdev->dev);
	if (NULL == match) {
		pr_err("get hi6421 regulator fail!\n\r");
		return -EINVAL;
	}

	temp = match->data;

	initdata = of_get_regulator_init_data(dev, np);
	if (NULL == initdata) {
		pr_err("get regulator init data error !\n");
		return -EINVAL;
	}

	sreg = kmemdup(temp, sizeof(*sreg), GFP_KERNEL);
	if (!sreg)
		return -ENOMEM;

	sreg->name = initdata->constraints.name;
	rdesc = &sreg->rdesc;
	rdesc->name = sreg->name;

	supplyname = of_get_property(np, "hisilicon,supply_name", NULL);
	if (supplyname != NULL) {
		initdata->supply_regulator = supplyname;
	}

	memset(sreg->g_enable_work_info, 0, sizeof(sreg->g_enable_work_info));
	memset(sreg->g_disable_work_info, 0, sizeof(sreg->g_disable_work_info));

	mutex_init(&(sreg->regulator_lock));
	/* to parse device tree data for regulator specific */
	ret = sreg->dt_parse(sreg, pdev);
	if (ret) {
		dev_err(dev, "device tree parameter parse error!\n");
		goto hisi_ip_probe_end;
	}

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = sreg;
	config.of_node = pdev->dev.of_node;
	sreg->np = np;
	sreg->regulator_enalbe_flag = 0;

	/* register regulator */
	rdev = regulator_register(rdesc, &config);
	if (IS_ERR(rdev)) {
		dev_err(dev, "failed to register %s\n",
			rdesc->name);
		ret = PTR_ERR(rdev);
		goto hisi_ip_probe_end;
	}

	if (regulator_flag == 0) {
		np = of_find_node_by_name(NULL, "crgctrl");
		BUG_ON(!np);
		g_regu.crgperi_reg = of_iomap(np, 0);
		BUG_ON(!g_regu.crgperi_reg);

		np = of_find_node_by_name(NULL, "pmctrl");
		BUG_ON(!np);
		g_regu.pmc_reg = of_iomap(np, 0);
		BUG_ON(!g_regu.pmc_reg);

		np = of_find_node_by_name(NULL, "sysctrl");
		BUG_ON(!np);
		g_regu.sctrl_reg = of_iomap(np, 0);
		BUG_ON(!g_regu.sctrl_reg);

		regulator_hwlock = hwspin_lock_request_specific(REGULATOR_HWLOCK_ID);
		if (regulator_hwlock == NULL) {
			dev_err(dev, "Request hwspin lock failed !\n");
			ret = -ENOMEM;
			goto hwspin_lock_err1;
		}

#ifdef CONFIG_DEBUG_FS
		d = debugfs_create_dir("hisi_ip_debugfs", NULL);
		if (!d) {
			dev_err(dev, "failed to create ip regulator debugfs dir !\n");
			ret = -ENOMEM;
			goto hisi_ip_probe_debugfs;
		}
		(void) debugfs_create_file("control_vcc", S_IRUSR, d, NULL, &set_control_vcc_fops);
#endif
		regulator_flag = 1;
	}

	platform_set_drvdata(pdev, rdev);

	return 0;
#ifdef CONFIG_DEBUG_FS
hisi_ip_probe_debugfs:
	ret = hwspin_lock_free(regulator_hwlock);
	if (ret)
		pr_err("%s: hwspin lock free fail, ret = [%d]\n", __func__, ret);
#endif
hwspin_lock_err1:
	regulator_unregister(rdev);
hisi_ip_probe_end:
	kfree(sreg);
	return ret;
}

static int hisi_regulator_ip_remove(struct platform_device *pdev)
{
	struct regulator_dev *rdev = platform_get_drvdata(pdev);
	struct hisi_regulator_ip *sreg = rdev_get_drvdata(rdev);
	unsigned int ret;

	ret = hwspin_lock_free(regulator_hwlock);
	if (ret)
		pr_err("%s: hwspin lock free fail, ret = [%d]\n", __func__, ret);

	regulator_unregister(rdev);
	/* TODO: should i worry about that? devm_kzalloc */
	if (sreg->rdesc.volt_table)
		devm_kfree(&pdev->dev, (unsigned int *)sreg->rdesc.volt_table);

	kfree(sreg);
	return 0;
}

static struct platform_driver hisi_regulator_ip_driver = {
	.driver = {
		.name	= "hisi_regulator_ip",
		.owner  = THIS_MODULE,
		.of_match_table = of_hisi_regulator_ip_match_tbl,
	},
	.probe	= hisi_regulator_ip_probe,
	.remove	= hisi_regulator_ip_remove,
};

static int __init hisi_regulator_ip_init(void)
{
	return platform_driver_register(&hisi_regulator_ip_driver);
}
fs_initcall(hisi_regulator_ip_init);

static void __exit hisi_regulator_ip_exit(void)
{
	platform_driver_unregister(&hisi_regulator_ip_driver);
}
module_exit(hisi_regulator_ip_exit);

MODULE_DESCRIPTION("Hisi regulator ip driver");
MODULE_LICENSE("GPL v2");
