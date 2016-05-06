/*
 * axierr irq support.
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define CONFIG_HISI_AXI_TEST

#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/cpu.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#ifdef CONFIG_HISI_AXI_TEST
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/io.h>
#include <linux/io.h>
#include <asm/cacheflush.h>
#endif

#define A53_cluster0_cpu0		(0)
#define A53_cluster1_cpu4		(4)

#define AXI_ERROR_CLUSTER0_EN_MASK        (1 << 14)
#define AXI_ERROR_CLUSTER1_EN_MASK        (1 << 15)

static struct device_node *node;
static int axi_cluster0_irq_num;
static int axi_cluster1_irq_num;

static irqreturn_t irq_handler_axierr_A53(int irq, void *dev_id)
{
	pr_err("AXI or CHI asynchronous error has occurred!!\n");
#ifdef CONFIG_ARM64
	/**
	 *write register L2ECTLR_EL1,clear irq
	 */
	asm volatile ("mrs x0, S3_1_C11_C0_3\n"
		      "mov x1, #(0x2<<28)\n"
		      "bic x0, x0, x1\n"
		      "msr S3_1_C11_C0_3, x0\n");
	pr_err("64AXI or CHI asynchronous error end!\n");
#else
	/**
	 *write register L2ECTLR_EL1,clear irq
	 */
	asm volatile ("	mov r0, #0x0\n"
		      "	mcr p15, 1, r0, c9, c0, 3\n");
	pr_err("32AXI or CHI asynchronous error end!\n");
#endif
	return IRQ_HANDLED;
}

static int hisi_axi_suspend(struct platform_device *pdev, pm_message_t state)
{
	pr_info("hisi axi suspend!\n");
	return 0;
}

static int hisi_axi_request_irq(void)
{
	int ret;
	void __iomem *acpu_sctrl_base_virt;
	void *axi_err_irq_en_addr;
	int axi_enable_offset = 0x0;
	int axi_err_irq_en = 0x0;

	/**
	 * affinity cluster0's axi err interrupt
	 */
	if (cpu_online(A53_cluster0_cpu0)) {
		ret = request_irq(axi_cluster0_irq_num, irq_handler_axierr_A53,
				  IRQF_TRIGGER_RISING, "axierr_cluster0", NULL);
		if (ret) {
			pr_err("%s: cannot register IRQ %d for A53. Line: %d\n",
			       __func__, axi_cluster0_irq_num, __LINE__);
			return ret;
		}
	}

	/**
	 * affinity cluster1's axi err interrupt
	 */
	if (cpu_online(A53_cluster1_cpu4)) {
		ret = request_irq(axi_cluster1_irq_num, irq_handler_axierr_A53,
				  IRQF_TRIGGER_RISING, "axierr_cluster1", NULL);
		if (ret) {
			pr_err("%s: cannot register IRQ %d for A53. Line: %d\n",
			       __func__, axi_cluster1_irq_num, __LINE__);
			return ret;
		}
	}

	/**
	 * hi6xxx need enable axi error irq, hi3xxx no need
	 */
	if (of_property_read_bool(node, "need-enable-axi-irq")) {
		acpu_sctrl_base_virt = of_iomap(node, 0);
		if (acpu_sctrl_base_virt) {
			ret = of_property_read_u32_index(node, "offset", 0,
						       &axi_enable_offset);
			if (ret) {
				pr_err("read axi_enable_offset is failed!\n");
				return ret;
			}

			axi_err_irq_en_addr =
			    (char *)acpu_sctrl_base_virt + axi_enable_offset;
			axi_err_irq_en = readl_relaxed(axi_err_irq_en_addr);
			axi_err_irq_en |=
			    AXI_ERROR_CLUSTER0_EN_MASK +
			    AXI_ERROR_CLUSTER1_EN_MASK;
			writel_relaxed(axi_err_irq_en, axi_err_irq_en_addr);
		}
	}

	return 0;

}

static int hisi_axi_set_affinity(void)
{
	int ret;

	/**
	 * affinity cluster0's axi err interrupt
	 */
	if (cpu_online(A53_cluster0_cpu0)) {
		ret = irq_set_affinity(axi_cluster0_irq_num,
				     cpumask_of(A53_cluster0_cpu0));
		if (ret < 0) {
			pr_err("hisi axi init failed: cluster0_0 irq affinity register failed\n");
			free_irq(axi_cluster0_irq_num, NULL);
			return ret;
		}
	}

	/**
	 * affinity cluster1's axi err interrupt
	 */
	if (cpu_online(A53_cluster1_cpu4)) {
		ret = irq_set_affinity(axi_cluster1_irq_num,
				     cpumask_of(A53_cluster1_cpu4));
		if (ret < 0) {
			pr_err("hisi axi init failed: cluster1_0 irq affinity register failed\n");
			free_irq(axi_cluster1_irq_num, NULL);
			return ret;
		}
	}

	return 0;

}

static int hisi_axi_resume(struct platform_device *pdev)
{
	int ret = 0;

	pr_info("hisi axi resume start!\n");

	ret = hisi_axi_set_affinity();
	if (ret < 0) {
		pr_err("hisi axi resume failed.\n");
		return ret;
	}

	pr_info("hisi axi resume finished.\n");
	return 0;
}

#ifdef CONFIG_HISI_AXI_TEST
static void *mapped_address(unsigned long phy_addr, size_t size, pgprot_t prot)
{
	struct page **pages;
	void *ioremap_base;

	pages = kmalloc(sizeof(struct page *) * 1, GFP_KERNEL);
	if (!pages) {
		pr_err("%s: Failed to allocate array for %u pages\n", __func__,
		       1);
		return NULL;
	}

	pages[0] = phys_to_page(phy_addr);
	ioremap_base = vmap(pages, 1, VM_MAP, prot);
	kfree(pages);

	return ioremap_base;
}

static void unmap_address(const void *addr)
{
	vunmap(addr);
}

/*
test condition
configure the addr(0x38000000) as UNSEC_Read in fastboot
trigger UNSEC_Write somewhere
*/
void hisi_axi_test(void)
{
	void *ioremap_base;

	ioremap_base =
	    mapped_address(0x38000000, 0x1000, __pgprot(PROT_NORMAL));
	if (NULL == ioremap_base) {
		pr_err("%s: mapped_address fail\n", __func__);
		return;
	}
	writel(1, ioremap_base);
	flush_cache_all();
	unmap_address(ioremap_base);
}
#endif

static int hisi_axi_probe(struct platform_device *pdev)
{
	int ret = 0;
	node = pdev->dev.of_node;

	pr_info("axi init begin!\n");

	axi_cluster0_irq_num = irq_of_parse_and_map(node, 0);
	axi_cluster1_irq_num = irq_of_parse_and_map(node, 1);

	ret = hisi_axi_request_irq();
	if (ret < 0) {
		pr_err("hisi axi init failed.r\n");
		return ret;
	}

	ret = hisi_axi_set_affinity();
	if (ret < 0) {
		pr_err("hisi axi init failed.a\n");
		return ret;
	}

	pr_info("hisi axi init finished.\n");

	return ret;
}

static struct of_device_id of_axi_match_tbl[] = {
	{
	 .compatible = "hisi,hi6xxx-axi",
	 },
	{
	 .compatible = "hisi,hi3xxx-axi",
	 },
	{ /* end */ }
};

static struct platform_driver hisi_axi_driver = {
	.driver = {
		   .owner = THIS_MODULE,
		   .name = "hisi-axi",
		   .of_match_table = of_axi_match_tbl,
		   },
	.probe = hisi_axi_probe,
#ifdef CONFIG_PM
	.suspend = hisi_axi_suspend,
	.resume = hisi_axi_resume,
#endif
};

static int __init hisi_axi_init(void)
{
	return platform_driver_register(&hisi_axi_driver);
}

module_init(hisi_axi_init);
