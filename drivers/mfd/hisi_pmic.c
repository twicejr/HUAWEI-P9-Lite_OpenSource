/*
 * Device driver for regulators in HISI PMIC IC
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
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/mfd/hisi_pmic.h>
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#include <pmic_interface.h>
#endif
#include <linux/irq.h>

#ifndef NO_IRQ
#define NO_IRQ       0
#endif
/* 8-bit register offset in PMIC */
#define HISI_MASK_STATE			0xff

#if defined (CONFIG_HUAWEI_DSM)
static struct dsm_dev dsm_pmic_irq = {
       .name = "dsm_pmu_irq",
       .device_name = NULL,
       .ic_name = NULL,
       .module_name = NULL,
       .fops = NULL,
       .buff_size = 1024,
};
static struct dsm_client *pmic_irq_dclient = NULL;
char *pmic_irq1_name[] = {  //IRQ1: 0x121 bit[7:2]
    [7] = " ",
    [6] = "thsd_otmp140_d1mr",
    [5] = "vsys_pwroff_deb_d80mr",
    [4] = "vsys_pwroff_abs_2d",
    [3] = " ",
    [2] = "vsys_ov_d200ur",
    [1] = " ",
    [0] = " ",
};
#define HISI_PMIC_IRQ1_MASK_STATE 0x74  //IRQ1: 0x121 bit[6,5,4,2]

#define PMIC_VER_BASE_ADDR			(PMIC_VERSION0_ADDR(0))
#define PMIC_VER_LEN				(4)
static unsigned char g_hi6421v500_ver[PMIC_VER_LEN] = {0x36, 0x34,0x32,0x31};
static unsigned char g_pmic_ver[PMIC_VER_LEN] = {0x00, 0x00, 0x00, 0x00};
#define PMIC_IS_HI6421V500 (memcmp(g_pmic_ver, g_hi6421v500_ver, PMIC_VER_LEN) == 0)
#endif

#define HISI_IRQ_KEY_NUM		0
#define HISI_IRQ_KEY_VALUE		0xc0
#define HISI_IRQ_KEY_DOWN		7
#define HISI_IRQ_KEY_UP			6

/*#define HISI_NR_IRQ			25*/
#define HISI_MASK_FIELD		0xFF
#define HISI_BITS			8
#define PMIC_FPGA_FLAG          1

#define DEAD_DATA		(0xdead)

static unsigned int g_pmic_uv_mntn;
static struct bit_info g_pmic_uv_mntn_resered = {DEAD_DATA, DEAD_DATA};
static struct bit_info g_pmic_uv_mntn_irq = {DEAD_DATA, DEAD_DATA};
static u32 buck_boost_alwayson = 0;

#ifndef BIT
#define BIT(x)		(0x1U << (x))
#endif

static struct of_device_id of_hisi_pmic_child_match_tbl[] = {
	/* regulators */
	{
		.compatible = "hisilicon,hisi-ldo",
	},
	{
		.compatible = "hisilicon,hi6421v500_coul",
	},
	{ /* end */ }
};

static struct of_device_id of_hisi_pmic_match_tbl[] = {
	{
		.compatible = "hisilicon,hisi-pmic",
	},
	{ /* end */ }
};

/*
 * The PMIC register is only 8-bit.
 * Hisilicon SoC use hardware to map PMIC register into SoC mapping.
 * At here, we are accessing SoC register with 32-bit.
 */
u32 hisi_pmic_read(struct hisi_pmic *pmic, int reg)
{
	u32 ret;

	ret = readl(pmic->regs + (reg << 2));

	return ret;
}
EXPORT_SYMBOL(hisi_pmic_read);

void hisi_pmic_write(struct hisi_pmic *pmic, int reg, u32 val)
{
	unsigned long flags;
	spin_lock_irqsave(&pmic->lock, flags);
	writel(val, pmic->regs + (reg << 2));
	spin_unlock_irqrestore(&pmic->lock, flags);
}
EXPORT_SYMBOL(hisi_pmic_write);

void hisi_pmic_rmw(struct hisi_pmic *pmic, int reg,
		     u32 mask, u32 bits)
{
	u32 data;
	unsigned long flags;

	spin_lock_irqsave(&pmic->lock, flags);
	data = readl(pmic->regs + (reg << 2)) & ~mask;
	data |= mask & bits;
	writel(data, pmic->regs + (reg << 2));
	spin_unlock_irqrestore(&pmic->lock, flags);
}
EXPORT_SYMBOL(hisi_pmic_rmw);
static void __iomem *g_pmussi_baseaddr = NULL;
#define PMUSSI_REG(addr)        (((addr)<<2) + (char *)g_pmussi_baseaddr)

unsigned int hisi_pmic_reg_read(int addr)
{
	unsigned char regval;
	regval =  *(volatile unsigned char*)PMUSSI_REG(addr);
	return regval;
}

void hisi_pmic_reg_write(int addr, int val)
{
	*(volatile unsigned char*)PMUSSI_REG(addr) = val;
}

int hisi_pmic_array_read(int addr, char *buff, unsigned int len)
{
	int i;

	if ((len > 32) || (NULL == buff)) {
		return -EINVAL;
	}

	/*
	 * Here is a bug in the pmu die.
	 * the coul driver will read 4 bytes,
	 * but the ssi bus only read 1 byte, and the pmu die
	 * will make sampling 1/10669us about vol cur,so the driver
	 * read the data is not the same sampling
	 */
	for (i = 0; i < len; i++) {
		*(buff + i) = hisi_pmic_reg_read(addr+i);
	}

	return 0;
}

int hisi_pmic_array_write(int addr, char *buff, unsigned int len)
{
    int i;

	if ((len > 32) || (NULL == buff)) {
		return -EINVAL;
	}

	for (i = 0; i < len; i++) {
		hisi_pmic_reg_write(addr+i, *(buff + i));
	}

	return 0;
}

unsigned int get_uv_mntn_status(void)
{
	return g_pmic_uv_mntn;
}

void clear_uv_mntn_resered_reg_bit(void)
{
	unsigned int reg_val = 0;
	if (DEAD_DATA == g_pmic_uv_mntn_resered.addr)
		return ;

	reg_val = hisi_pmic_reg_read(g_pmic_uv_mntn_resered.addr);
	reg_val &= (~BIT(g_pmic_uv_mntn_resered.bit));
	hisi_pmic_reg_write(g_pmic_uv_mntn_resered.addr, reg_val);
}

void set_uv_mntn_resered_reg_bit(void)
{
	unsigned int reg_val = 0;
	if (DEAD_DATA == g_pmic_uv_mntn_resered.addr)
		return ;

	reg_val = hisi_pmic_reg_read(g_pmic_uv_mntn_resered.addr);
	reg_val |= BIT(g_pmic_uv_mntn_resered.bit);
	hisi_pmic_reg_write(g_pmic_uv_mntn_resered.addr, reg_val);
}

static irqreturn_t hisi_irq_handler(int irq, void *data)
{
	struct hisi_pmic *pmic = (struct hisi_pmic *)data;
	unsigned long pending;
	int i, offset;

	for (i = 0; i < pmic->irqarray; i++) {
		pending = readl(pmic->regs + ((i + pmic->irq_addr.start_addr) << 2));
		pending &= HISI_MASK_FIELD;
		if (pending != 0) {
			pr_info("pending[%d]=0x%lx\n\r", i, pending);
		}

		if (g_pmic_uv_mntn) {
			if ((g_pmic_uv_mntn_irq.addr != DEAD_DATA)
				&& (g_pmic_uv_mntn_irq.addr == (i + pmic->irq_addr.start_addr))
				&& (pending & BIT(g_pmic_uv_mntn_irq.bit))) {
				set_uv_mntn_resered_reg_bit();
			}
		}

		writel(pending, pmic->regs + ((i + pmic->irq_addr.start_addr) << 2));

		/*solve powerkey order*/
		if ((HISI_IRQ_KEY_NUM == i) && ((pending & HISI_IRQ_KEY_VALUE) == HISI_IRQ_KEY_VALUE)) {
			generic_handle_irq(pmic->irqs[HISI_IRQ_KEY_DOWN]);
			generic_handle_irq(pmic->irqs[HISI_IRQ_KEY_UP]);
			pending &= (~HISI_IRQ_KEY_VALUE);
		}

		if (pending) {
			for_each_set_bit(offset, &pending, HISI_BITS)
				generic_handle_irq(pmic->irqs[offset + i * HISI_BITS]);
		}
	}

	return IRQ_HANDLED;
}

static void hisi_irq_mask(struct irq_data *d)
{
	struct hisi_pmic *pmic = irq_data_get_irq_chip_data(d);
	u32 data, offset;
	unsigned long flags;

	offset = ((irqd_to_hwirq(d) >> 3) + pmic->irq_mask_addr.start_addr) << 2;
	spin_lock_irqsave(&pmic->lock, flags);
	data = readl(pmic->regs + offset);
	data |= (1 << (irqd_to_hwirq(d) & 0x07));
	writel(data, pmic->regs + offset);
	spin_unlock_irqrestore(&pmic->lock, flags);
}

static void hisi_irq_unmask(struct irq_data *d)
{
	struct hisi_pmic *pmic = irq_data_get_irq_chip_data(d);
	u32 data, offset;
	unsigned long flags;

	offset = ((irqd_to_hwirq(d) >> 3) + pmic->irq_mask_addr.start_addr) << 2;
	spin_lock_irqsave(&pmic->lock, flags);
	data = readl(pmic->regs + offset);
	data &= ~(1 << (irqd_to_hwirq(d) & 0x07));
	writel(data, pmic->regs + offset);
	spin_unlock_irqrestore(&pmic->lock, flags);
}

static struct irq_chip hisi_pmu_irqchip = {
	.name		= "hisi-irq",
	.irq_mask	= hisi_irq_mask,
	.irq_unmask	= hisi_irq_unmask,
	.irq_disable	= hisi_irq_mask,
	.irq_enable	= hisi_irq_unmask,
};

static int hisi_irq_map(struct irq_domain *d, unsigned int virq,
			  irq_hw_number_t hw)
{
	struct hisi_pmic *pmic = d->host_data;

	irq_set_chip_and_handler_name(virq, &hisi_pmu_irqchip,
				      handle_simple_irq, "hisi");
	irq_set_chip_data(virq, pmic);
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}

static struct irq_domain_ops hisi_domain_ops = {
	.map	= hisi_irq_map,
	.xlate	= irq_domain_xlate_twocell,
};

static int get_pmic_device_tree_data(struct device_node *np, struct hisi_pmic *pmic)
{
	u32 ret = 0;

	/*get pmic irq num*/
	ret = of_property_read_u32_array(np, "hisilicon,hisi-pmic-irq-num",
						&(pmic->irqnum), 1);
	if (ret) {
		pr_err("no hisilicon,hisi-pmic-irq-num property set\n");
		ret = -ENODEV;
		return ret;
	}

	/*get pmic irq array number*/
	ret = of_property_read_u32_array(np, "hisilicon,hisi-pmic-irq-array",
						&(pmic->irqarray), 1);
	if (ret) {
		pr_err("no hisilicon,hisi-pmic-irq-array property set\n");
		ret = -ENODEV;
		return ret;
	}

	/*SOC_PMIC_IRQ_MASK_0_ADDR*/
	ret = of_property_read_u32_array(np, "hisilicon,hisi-pmic-irq-mask-addr",
						(int *)&pmic->irq_mask_addr, 2);
	if (ret) {
		pr_err("no hisilicon,hisi-pmic-irq-mask-addr property set\n");
		ret = -ENODEV;
		return ret;
	}

	/*SOC_PMIC_IRQ0_ADDR*/
	ret = of_property_read_u32_array(np, "hisilicon,hisi-pmic-irq-addr",
						(int *)&pmic->irq_addr, 2);
	if (ret) {
		pr_err("no hisilicon,hisi-pmic-irq-addr property set\n");
		ret = -ENODEV;
		return ret;
	}

	/* do not need the return val,because other platforms may not have the properties */
	of_property_read_u32_array(np, "hisilicon,hisi-pmic-uv-irq-bit",
		(u32 *)&g_pmic_uv_mntn_irq, 2);

	of_property_read_u32_array(np, "hisilicon,hisi-pmic-uv-resered-bit",
		(u32 *)&g_pmic_uv_mntn_resered, 2);

	of_property_read_u32(np, "hisilicon,hisi-pmic-uv-mntn", (u32 *)&g_pmic_uv_mntn);

	return ret;
}

static int hisi_pmic_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hisi_pmic *pmic = NULL;
	enum of_gpio_flags flags;
	unsigned int register_info[3], ocp_ctrl_reg, ocp_buck_delay, ocp_ldo_delay;
	int ret, i;
	int fpga_flag = 0;
	unsigned int virq;
	int pmic_irq_error_offset;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic) {
		dev_err(dev, "cannot allocate hisi_pmic device info\n");
		return -ENOMEM;
	}

	/* get resources */
	pmic->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pmic->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	if (!devm_request_mem_region(dev, pmic->res->start,
				     resource_size(pmic->res),
				     pdev->name)) {
		dev_err(dev, "cannot claim register memory\n");
		return -ENOMEM;
	}

	pmic->regs = devm_ioremap(dev, pmic->res->start,
				  resource_size(pmic->res));
	if (!pmic->regs) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}

	/*TODO: get pmic dts info*/
	ret = get_pmic_device_tree_data(np, pmic);
	if (ret) {
		dev_err(&pdev->dev, "Error reading hisi pmic dts \n");
		return ret;
	}

	/* TODO: get and enable clk request */
	spin_lock_init(&pmic->lock);

	ret = of_property_read_u32(np, "buck_boost_alwayson", &buck_boost_alwayson);
	if (ret < 0){
		dev_err(&pdev->dev, "get buck_boost_alwayson error");
	}
	dev_info(&pdev->dev, "buck_boost_alwayson = %d", buck_boost_alwayson);
	if (buck_boost_alwayson){
		hisi_pmic_write(pmic, 0xA4, 0x01);
	}
	of_property_read_u32_array(np, "hisilicon,pmic_fpga_flag", &fpga_flag, 1);

	if (PMIC_FPGA_FLAG == fpga_flag) {
		goto after_irq_register;
	}

	pmic->gpio = of_get_gpio_flags(np, 0, &flags);
	if (pmic->gpio < 0)
		return pmic->gpio;

	if (!gpio_is_valid(pmic->gpio))
		return -EINVAL;

	ret = gpio_request_one(pmic->gpio, GPIOF_IN, "pmic");
	if (ret < 0) {
		dev_err(dev, "failed to request gpio%d\n", pmic->gpio);
		return ret;
	}

	pmic->irq = gpio_to_irq(pmic->gpio);
	/* mask && clear IRQ status */
	for (i = 0 ; i < pmic->irq_mask_addr.array; i++) {
		hisi_pmic_write(pmic, pmic->irq_mask_addr.start_addr + i, HISI_MASK_STATE);
	}

#if defined (CONFIG_HUAWEI_DSM)
	for (i = 0; i < PMIC_VER_LEN; i++)
		g_pmic_ver[i] = hisi_pmic_read(pmic, (PMIC_VER_BASE_ADDR + i));

	if (PMIC_IS_HI6421V500) {
		if (!pmic_irq_dclient) {
			pmic_irq_dclient = dsm_register_client(&dsm_pmic_irq);
			if (NULL == pmic_irq_dclient) {
				pr_err("%s:dsm_register_client register fail.\n", __func__);
			}
		}
	}
#endif

	for (i = 0 ; i < pmic->irq_addr.array; i++) {
		unsigned int pending = hisi_pmic_read(pmic, pmic->irq_addr.start_addr + i);
		pr_debug("PMU IRQ address value:irq[0x%x] = 0x%x\n", pmic->irq_addr.start_addr + i, pending);
#if defined (CONFIG_HUAWEI_DSM)
		if (PMIC_IS_HI6421V500) {
			if ((1 == i) && (pending & HISI_PMIC_IRQ1_MASK_STATE)) {
				for(pmic_irq_error_offset = 2; pmic_irq_error_offset < 8; pmic_irq_error_offset++) {
					if (dsm_client_ocuppy(pmic_irq_dclient)) {
						pr_err("pmic_irq_dclient dsm_client_ocuppy failed");
					} else if(pmic_irq_error_offset & HISI_PMIC_IRQ1_MASK_STATE) {
						pr_err("pmic %s happened, please pay attention!\n\r", pmic_irq1_name[pmic_irq_error_offset]);
						dsm_client_record(pmic_irq_dclient, "pmic %s happened, please pay attention!\n", \
						pmic_irq1_name[pmic_irq_error_offset]);
						dsm_client_notify(pmic_irq_dclient, DSM_PMU_IRQ_ERROR_NO + pmic_irq_error_offset);
					} else {
					/*do nothing*/
					}
				}
			}
		}
#endif
		hisi_pmic_write(pmic, pmic->irq_addr.start_addr + i, HISI_MASK_STATE);
	}

	pmic->irqs = (unsigned int *)devm_kmalloc(dev, pmic->irqnum * sizeof(int), GFP_KERNEL);
	if (!pmic->irqs) {
		pr_err("%s:Failed to alloc memory for pmic irq number!\n", __func__);
		goto irq_malloc;
	}
	memset(pmic->irqs, 0, pmic->irqnum);

	pmic->domain = irq_domain_add_simple(np, pmic->irqnum, 0,
					     &hisi_domain_ops, pmic);
	if (!pmic->domain) {
		dev_err(dev, "failed irq domain add simple!\n");
		ret = -ENODEV;
		goto irq_domain;
	}

	for (i = 0; i < pmic->irqnum; i++) {
		virq = irq_create_mapping(pmic->domain, i);
		if (virq == NO_IRQ) {
			pr_debug("Failed mapping hwirq\n");
			ret = -ENOSPC;
			goto irq_create_mapping;
		}
		pmic->irqs[i] = virq;
		pr_debug("[%s]. pmic->irqs[%d] = %d\n", __func__, i, pmic->irqs[i]);
	}

	ret = request_threaded_irq(pmic->irq, hisi_irq_handler, NULL,
				IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND,
				   "pmic", pmic);
	if (ret < 0) {
		dev_err(dev, "could not claim pmic %d\n", ret);
		ret = -ENODEV;
		goto request_theaded_irq;
	}

	/*if there is a ldo current over,support ocp qudou*/
	ret = of_property_read_u32_array(np, "hisilicon,hisi-ocp-deb-ctrl",
						register_info, 3);
	if (ret) {
		dev_err(dev, "no hisilicon,hisi-ldo-ocp-deb-ctrl property set\n");
		ret = -ENODEV;
		goto read_u32_array;
	}
	ocp_ctrl_reg = register_info[0];
	ocp_buck_delay = register_info[1];
	ocp_ldo_delay = register_info[2];
	hisi_pmic_write(pmic, ocp_ctrl_reg, (ocp_buck_delay | ocp_ldo_delay));

after_irq_register:
	g_pmussi_baseaddr = pmic->regs;
	platform_set_drvdata(pdev, pmic);

	/* populate sub nodes */
	of_platform_populate(np, of_hisi_pmic_child_match_tbl, NULL, dev);

	return 0;

read_u32_array:
	free_irq(pmic->irq, pmic);
request_theaded_irq:
irq_create_mapping:
irq_domain:
irq_malloc:
	gpio_free(pmic->gpio);
	return ret;
}

static int hisi_pmic_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hisi_pmic *pmic = platform_get_drvdata(pdev);

	free_irq(pmic->irq, pmic);
	gpio_free(pmic->gpio);
	devm_iounmap(dev, pmic->regs);
	devm_release_mem_region(dev, pmic->res->start,
				resource_size(pmic->res));
	devm_kfree(dev, pmic);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static struct platform_driver hisi_pmic_driver = {
	.driver = {
		.name	= "hisi_pmic",
		.owner  = THIS_MODULE,
		.of_match_table = of_hisi_pmic_match_tbl,
	},
	.probe	= hisi_pmic_probe,
	.remove	= hisi_pmic_remove,
};
/*module_platform_driver(hisi_pmic_driver);*/
static int __init hisi_pmic_init(void)
{
	return platform_driver_register(&hisi_pmic_driver);
}

static void __exit hisi_pmic_exit(void)
{
	platform_driver_unregister(&hisi_pmic_driver);
}

fs_initcall(hisi_pmic_init);
module_exit(hisi_pmic_exit);

MODULE_AUTHOR("Guodong Xu <guodong.xu@linaro.org>");
MODULE_DESCRIPTION("PMIC driver");
MODULE_LICENSE("GPL v2");
