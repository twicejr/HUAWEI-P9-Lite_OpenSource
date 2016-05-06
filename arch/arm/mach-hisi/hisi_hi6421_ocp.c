/*
 * hi6421_ocp.c - Hisilicon Hi6421 PMIC ocp driver
 *
 * Copyright (C) 2013 Hisilicon Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/err.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/mfd/hi3xxx_hi6421v300.h>
#include "mach/hisi_hi6421_ocp.h"

struct hi6421_ocp_info {
	int	irq;
	struct hi6421_pmic *pmic;
	struct workqueue_struct *regulator_ocp_wq;
	struct work_struct regulator_ocp_wk;
	u32 ocp_mask_val[7];
};

char *pmuocp_name1[] = {
	[BUCK0]			= "buck0",
	[BUCK1]			= "buck1",
	[BUCK2]			= "buck2",
	[BUCK3]			= "buck3",
	[BUCK4]			= "buck4",
	[BUCK5]			= "buck5",
	[BUCK6]			= "buck6",
	[LDO0_2]			= "ldo0_2",
	[LDO1]	 		= "ldo1",
	[LDO2]	 		= "ldo2",
	[LDO3]	 		= "ldo3",
	[LDO4]	 		= "ldo4",
	[LDO5]	 		= "ldo5",
	[LDO6]	 		= "ldo6",
	[LDO7]	 		= "ldo7",
	[LDO8]	 		= "ldo8",
	[LDO9]	 		= "ldo9",
	[LDO10]	 		= "ldo10",
	[LDO11]	 		= "ldo11",
	[LDO12]	 		= "ldo12",
	[LDO12]	 		= "ldo12",
	[LDO13]	 		= "ldo13",
	[LDO14]	 		= "ldo14",
	[LDO15]	 		= "ldo15",
	[LDO16]	 		= "ldo16",
	[LDO17]	 		= "ldo17",
	[LDO18]	 		= "ldo18",
	[LDO19]	 		= "ldo19",
	[LDO20]	 		= "ldo20",
	[LDO21]	 		= "ldo21",
	[LDO22]	 		= "ldo22",
	[LDO23]	 		= "ldo23",
	[LDO24]	 		= "ldo24",
};
char *pmuocp_name2[] = {
	[LDO25]	 		= "ldo25",
	[LDO26]	 		= "ldo26",
	[LSW50]	 		= "lsw50",
	[LSW51]	 		= "lsw51",
	[LSW52]	 		= "lsw52",
	[LSW53]	 		= "lsw53",
	[DCDR2]	 		= "dcdr2",
	[ACDR2]	 		= "acdr2",
	[BST]	 		= "bst",
	[CLASSD]	 		= "classd",
	[BSTSHORT]		= "bstshort",
	[BUCK0SHORT]	= "buck0short",
	[BUCK12SHORT]	= "buck12short",
	[BUCK3SHORT]	= "buck3short",
	[BUCK4SHORT]	= "buck4short",
	[BUCK5SHORT]	= "buck5short",
	[BUCK6SHORT]	= "buck6short",
};
#define PMU_OCP_IRQ	49

#define	OCP_CONTRL_INT1	(0x125 << 2)
#define	OCP_CONTRL_INT2	(0x126 << 2)
#define	OCP_CONTRL_INT3	(0x127 << 2)
#define	OCP_CONTRL_INT4	(0x128 << 2)

#define	OCP_CONTRL_INT5	(0x129 << 2)
#define	OCP_CONTRL_INT6	(0x12A << 2)
#define	OCP_CONTRL_INT7	(0x12B << 2)

#define	OCP_STATE1    (0x03 << 2)
#define	OCP_STATE2    (0x04 << 2)
#define	OCP_STATE3    (0x05 << 2)
#define	OCP_STATE4    (0x06 << 2)
#define	OCP_STATE5    (0x07 << 2)
#define	OCP_STATE6    (0x08 << 2)

static void hi6421_ocp_mask_irq(struct hi6421_ocp_info *info, bool mask)
{
	struct irq_desc *hi6421_irq_desc;

	hi6421_irq_desc = irq_to_desc(info->irq);
	if (!hi6421_irq_desc) {
		pr_err("%s : irq_to_desc error\n", __FUNCTION__);
		return;
	}

	if (mask) {
		/* mask interrupts */
		hi6421_irq_desc->irq_data.chip->irq_mask(&hi6421_irq_desc->irq_data);
	} else {
		/* unmask interrupts */
		hi6421_irq_desc->irq_data.chip->irq_unmask(&hi6421_irq_desc->irq_data);
	}
}

static void inquiry_hi6421_ocp_reg(struct work_struct *work)
{
	struct hi6421_ocp_info *ocp_info = container_of(work, struct hi6421_ocp_info, regulator_ocp_wk);
	u8 ocp_status1_bef, ocp_status2_bef, ocp_status3_bef, ocp_status4_bef, ocp_status5_bef, ocp_status6_bef, ocp_status7_bef;
	u8 ocp_status1, ocp_status2, ocp_status3, ocp_status4, ocp_status5, ocp_status6, ocp_status7;
	int i;
	u32 ocp_status_all1, ocp_status_all2, ocp_status_all1_bef, ocp_status_all2_bef;
	/*get ocp state*/
	ocp_status1 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT1);
	ocp_status2 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT2);
	ocp_status3 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT3);
	ocp_status4 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT4);
	ocp_status5 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT5);
	ocp_status6 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT6);
	ocp_status7 = ioread8(ocp_info->pmic->regs + OCP_CONTRL_INT7);

	ocp_status_all1 = ocp_status1 | (ocp_status2 << 8) | (ocp_status3 << 16) | (ocp_status4 << 24);
	ocp_status_all2 = ocp_status5 | (ocp_status6 << 8) | (ocp_status7 << 16);
	/*judgement ocp state and clean interrupt*/
	for (i = 0; i < 32; i++) {
		if (ocp_status_all1 & (0x01 << i))
			pr_warn("hi6421 %s ocp happened, please attention!\n\r", pmuocp_name1[i]);
	}

	for (i = 0; i < 24; i++) {
		if (ocp_status_all2 & (0x01 << i))
			pr_warn("hi6421 %s ocp happened, please attention!\n\r", pmuocp_name2[i]);
	}

	iowrite8(ocp_status1, ocp_info->pmic->regs + OCP_CONTRL_INT1);
	iowrite8(ocp_status2, ocp_info->pmic->regs + OCP_CONTRL_INT2);
	iowrite8(ocp_status3, ocp_info->pmic->regs + OCP_CONTRL_INT3);
	iowrite8(ocp_status4, ocp_info->pmic->regs + OCP_CONTRL_INT4);
	iowrite8(ocp_status5, ocp_info->pmic->regs + OCP_CONTRL_INT5);
	iowrite8(ocp_status6, ocp_info->pmic->regs + OCP_CONTRL_INT6);
	iowrite8(ocp_status7, ocp_info->pmic->regs + OCP_CONTRL_INT7);

	hi6421_ocp_mask_irq(ocp_info, 0);

	ocp_status1_bef = ocp_status1 & (~ocp_info->ocp_mask_val[0]);
	ocp_status2_bef = ocp_status2 & (~ocp_info->ocp_mask_val[1]);
	ocp_status3_bef = ocp_status3 & (~ocp_info->ocp_mask_val[2]);
	ocp_status4_bef = ocp_status4 & (~ocp_info->ocp_mask_val[3]);
	ocp_status5_bef = ocp_status5 & (~ocp_info->ocp_mask_val[4]);
	ocp_status6_bef = ocp_status6 & (~ocp_info->ocp_mask_val[5]);
	ocp_status7_bef = ocp_status7 & (~ocp_info->ocp_mask_val[6]);

	ocp_status_all1_bef = ocp_status1_bef | (ocp_status2_bef << 8) | (ocp_status3_bef << 16) | (ocp_status4_bef << 24);
	ocp_status_all2_bef = ocp_status5_bef | (ocp_status6_bef << 8) | (ocp_status7_bef << 16);

	if (ocp_status_all1_bef || ocp_status_all2_bef) {
		BUG_ON(1);
	}
}

static irqreturn_t hi6421_regulator_current_over_support(int irq, void *data)
{
	struct hi6421_ocp_info *hi6421_ocp_info = data;
	hi6421_ocp_mask_irq(hi6421_ocp_info, 1);
	queue_work(hi6421_ocp_info->regulator_ocp_wq, &hi6421_ocp_info->regulator_ocp_wk);

	return IRQ_HANDLED;
}
static int get_ocp_dt_parse(struct hi6421_ocp_info *info, struct device_node *np)
{
	unsigned int register_info[7] = {0};
	int ret = 0;

	/* parse ocp irq mask ctrl_reg */
	ret = of_property_read_u32_array(np, "hisi-ocp-mask",
						register_info, 7);
	if (ret) {
		pr_err("no hisi-ocp-mask set\n");
		return ret;
	}
	info->ocp_mask_val[0] = register_info[0];
	info->ocp_mask_val[1] = register_info[1];
	info->ocp_mask_val[2] = register_info[2];
	info->ocp_mask_val[3] = register_info[3];
	info->ocp_mask_val[4] = register_info[4];
	info->ocp_mask_val[5] = register_info[5];
	info->ocp_mask_val[6] = register_info[6];

	return ret;
}
static int hi6421_ocp_probe(struct platform_device *pdev)
{
	struct hi6421_ocp_info *info;
	struct device_node *np = NULL;
	struct device *dev = NULL;
	int ret = 0;

	if (pdev == NULL) {
		pr_err("[%s]ocp get  platform device para is err!\n", __func__);
		return -EINVAL;
	}
	dev = &pdev->dev;
	np = dev->of_node;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info) {
		dev_err(&pdev->dev, "failed to allocate memory\n");
		return -ENOMEM;
	}

	info->pmic = dev_get_drvdata(pdev->dev.parent);
	if (info->pmic == NULL) {
		dev_err(&pdev->dev, "failed to get parent resource!\n");
		return -ENOMEM;
	}

	ret = get_ocp_dt_parse(info, np);
	if (ret) {
		dev_err(&pdev->dev, "get ocp dt parse fail!\n");
		return -ENOMEM;
	}

	info->irq = platform_get_irq_byname(pdev, "ocpirq");
	if (info->irq < 0)
		return -ENOENT;

	info->regulator_ocp_wq = create_singlethread_workqueue("hi6421_regulator_ocp");
	if (info->regulator_ocp_wq == NULL) {
		dev_err(&pdev->dev, "failed to create work queue\n");
		return -ENOMEM;
	}
	INIT_WORK(&info->regulator_ocp_wk, (void *)inquiry_hi6421_ocp_reg);

	ret = devm_request_irq(&pdev->dev, info->irq, hi6421_regulator_current_over_support,
			       IRQF_DISABLED, "ocpirq", info);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to requset irq!\n");
		goto free_charger_wq;
	}


	platform_set_drvdata(pdev, info);

	return ret;

free_charger_wq:
	destroy_workqueue(info->regulator_ocp_wq);
	return ret;
}

static int hi6421_ocp_remove(struct platform_device *pdev)
{
	struct hi6421_ocp_info *info;

	/*get hi6421_ocp_info*/
	info = platform_get_drvdata(pdev);
	if (NULL == info) {
		pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
		return -1;
	}

	if (info->regulator_ocp_wq)
		destroy_workqueue(info->regulator_ocp_wq);

	return 0;
}

static struct of_device_id hi6421_ocp_of_match[] = {
	{ .compatible = "hisilicon,hi6421-ocpirq", },
	{ },
};
MODULE_DEVICE_TABLE(of, hi6421_ocp_of_match);

static struct platform_driver hi6421_ocp_driver = {
	.probe		= hi6421_ocp_probe,
	.remove		= hi6421_ocp_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= "hi6421-ocp",
		.of_match_table	= hi6421_ocp_of_match,
	},
};

int __init hi6421_ocp_init(void)
{
	return platform_driver_register(&hi6421_ocp_driver);
}

static void __exit hi6421_ocp_exit(void)
{
	platform_driver_unregister(&hi6421_ocp_driver);
}

late_initcall(hi6421_ocp_init);
module_exit(hi6421_ocp_exit);

MODULE_DESCRIPTION("Hi6421 PMIC ocp driver");
MODULE_LICENSE("GPL v2");
