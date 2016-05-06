/*
 * Device driver for regulators in Hi6421 IC
 *
 * Copyright (C) 2013 Linaro Ltd. Guodong Xu <guodong.xu@linaro.org>
 *
 * Porting to hisi platform by Young Choi.
 * Copyright (C) 2014 Hisilicon, Young Choi <cuiyong1@hisilicon.com>
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
#include <linux/io.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/hisi/pasr.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/hwspinlock.h>
#include "../../../atfdriver/atfdriver.h"

/*#define PASR_DEBUG pr_err*/
/*lint -e750 -esym(750,*) */
#define PASR_DEBUG(...)

#define DDR_RANK_SIZE_512M                  (0x20000000)
#define DDR_RANK_SIZE_1024M                 (0x40000000)
#define DDR_RANK_SIZE_1536M                 (0x60000000)
#define DDR_RANK_SIZE_2048M                 (0x80000000)
#define DDR_HWLOCK_ID                       (22)
#define DDR_HWLOCK_TIMEOUT                  (1000)

/* new macro start */
#include <soc_acpu_baseaddr_interface.h>
#include <soc_sctrl_interface.h>

/* new macro end */

struct pasr_fw {
	struct pasr_map *map;
};
extern struct pasr_fw pasr;

enum DDR_TYPE
{
	DDR_TYPE_LPDDR3=3,
	DDR_TYPE_LPDDR4=4,
	DDR_TYPE_UNKNOWN,
};

struct ddr_rank_info {
	u32 addr;
	u32 size;
	u32 memreg;
};

static u32 ddr_type=DDR_TYPE_UNKNOWN;

static struct hwspinlock *ddr_hwlock = NULL;
static void __iomem *sctrl_base = 0;
static spinlock_t pasr_lock;


static long long rank_nr = 0;
static struct ddr_rank_info rank_info[PASR_MAX_DIE_NR];

static ssize_t show_mem_regs(struct device *dev,
			struct device_attribute *devattr, char *buf);

static DEVICE_ATTR(memregs, S_IRUGO, show_mem_regs, NULL);

static struct attribute *hisi_pasr_attributes[] = {
	&dev_attr_memregs.attr,
	NULL,
};

static const struct attribute_group hisi_attr_group = {
	.attrs = hisi_pasr_attributes,
};

static ssize_t show_mem_regs(struct device *dev,
			struct device_attribute *devattr, char *buf)
{
	struct ddr_rank_info *info;
	int size = 0;
	long long i;

	for(i = 0; i < rank_nr; i++) {
		info = &rank_info[i];
		size += snprintf(buf + size, PAGE_SIZE / rank_nr,
			"%s: rank%lld addr=0x%08x, size = 0x%08x, mem_reg = 0x%08x\n",
			__func__, i, info->addr, info->size, info->memreg);
	}

	return size;
}

static u32 hisi_pasr_mask_reserved_ddr_region(unsigned int value, int rank)
{
	unsigned int ret = 0;

	if (rank == 0) {
		switch (rank_info[rank].size) {
		case DDR_RANK_SIZE_1024M:
			ret = value & 0x3C;
			break;
		case DDR_RANK_SIZE_1536M:
			ret = value & 0xF6;
			break;
		case DDR_RANK_SIZE_2048M:
			ret = value & 0xF6;
			break;
		}
	} else {
		switch (rank_info[rank].size) {
		case DDR_RANK_SIZE_1024M:
			ret = value & 0x7F;
			break;
		case DDR_RANK_SIZE_1536M:
			ret = value & 0x1F;
			break;
		case DDR_RANK_SIZE_2048M:
			ret = value & 0x7F;
			break;
		}
	}

	return ret;
}

static void hisi_pasr_apply_mask(u32 *mem_reg, void *cookie)
{
	long long rank = (long long)cookie;
	int ret;
	u32 value = *mem_reg, flags;
	PASR_DEBUG("%s: [%d,0x%x]\n", __func__, rank, value);
	if ((rank >= rank_nr) || (rank < 0)) {
		pr_err("%s: invalid rank value %lld.\n",
				__func__, rank);
		return ;
	}

	rank_info[rank].memreg = value;
	value = hisi_pasr_mask_reserved_ddr_region(value, rank);

	if (ddr_hwlock != NULL) {
		spin_lock_irqsave(&pasr_lock, flags);
		ret = hwspin_lock_timeout(ddr_hwlock, DDR_HWLOCK_TIMEOUT);
		BUG_ON(IS_ERR(ret));
		(void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, value, rank, ACCESS_REGISTER_FN_SUB_ID_DDR_PASR);
		hwspin_unlock(ddr_hwlock);
		spin_unlock_irqrestore(&pasr_lock, flags);
	}
}

static void hisi_pasr_get_rank_info(void)
{
	long long i;
	rank_nr = (long long)(pasr.map)->nr_dies;
	for(i = 0; i < rank_nr; i++) {
		rank_info[i].addr =	(pasr.map)->die[i].start;
		rank_info[i].size = (pasr.map)->die[i].nr_sections * (pasr.map)->die[i].section_size;
	}

}

static int hisi_pasr_probe(struct platform_device *pdev)
{
	struct device_node *np;
	struct device *dev = &pdev->dev;
	int err;
	long long i;
	unsigned int reg_val;

	dev_crit(dev, "%s: enter\n", __func__);
	PASR_DEBUG("%s: enter\n", __func__);

	np = dev->of_node;

	sctrl_base = (void *)ioremap(SOC_ACPU_SCTRL_BASE_ADDR, SZ_4K);
	if (sctrl_base == NULL) {
		dev_err(dev, "failed to iomap sctrl regs!\n");
		return -ENXIO;
	}

	reg_val = readl(SOC_SCTRL_SCBAKDATA4_ADDR(sctrl_base)) & 0x1<<31;
	if (reg_val == 0x0) {
		ddr_type = DDR_TYPE_LPDDR3;
	} else {
		ddr_type = DDR_TYPE_LPDDR4;
	}

	PASR_DEBUG("ddr_type: ddr%d\n", ddr_type);

	spin_lock_init(&pasr_lock);

	ddr_hwlock = hwspin_lock_request_specific(DDR_HWLOCK_ID);
	if (ddr_hwlock == NULL) {
		dev_err(dev, "pasr get hwspin_lock failed\n");
		return -EBUSY;
	}

	hisi_pasr_get_rank_info();

	for (i = 0; i < rank_nr; i++) {
		if (pasr_register_mask_function(rank_info[i].addr,
					&hisi_pasr_apply_mask, (void *)i)) {
			dev_err(dev, "pasr register failed, rank %lld\n", i);
		}
	}

	err = sysfs_create_group(&pdev->dev.kobj, &hisi_attr_group);
	if (err < 0) {
		dev_err(dev, "create sysfs group failed (%d)\n", err);
		return err;
	}

	dev_crit(dev, "%s: exit\n", __func__);

	return 0;
}

static int hisi_pasr_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id of_hisi_pasr_match_tbl[] = {
	{
		.compatible = "hisilicon,hisi-pasr",
	},
	{ /* end */ }
};
MODULE_DEVICE_TABLE(of, of_hisi_pasr_match_tbl);
#endif

static struct platform_driver hisi_pasr_driver = {
	.driver = {
		.name	= "hisi-pasr",
		.owner	= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(of_hisi_pasr_match_tbl),
#endif
	},
	.probe	= hisi_pasr_probe,
	.remove	= hisi_pasr_remove,
};
module_platform_driver(hisi_pasr_driver);

MODULE_AUTHOR("Young Choi <crux.cuiyong@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon PASR driver");
MODULE_LICENSE("GPL v2");

/*lint +e750 +esym(750,*) */
