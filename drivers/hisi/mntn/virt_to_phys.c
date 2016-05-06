/*
 *	drivers/hisi/mntn/virt_to_phys.c
 *
 * Copyright (C) 2013 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/slab.h>

#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <linux/mm_types.h>
#include <linux/rwsem.h>

#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/of_address.h>

#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/pgtable-hwdef.h>
/*lint -e451*/
#include <asm/current.h>
/*lint +e451*/
#include <linux/thread_info.h>

#include <linux/kernel_stat.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/io.h>
#include <asm/pgalloc.h>
#include <asm/tlb.h>
#include <asm/tlbflush.h>

static unsigned long virt_addr;
static unsigned int virt_len;
static unsigned int pid;

static ssize_t show_phys_pte(char *buf, ssize_t size, struct mm_struct *mm,
			     unsigned long addr)
{
	pgd_t *pgd;
	ssize_t temp = size;

	size += snprintf(buf + size, PAGE_SIZE - size, "pgd = %p\n", mm->pgd);
	pgd = pgd_offset(mm, addr);
	size += snprintf(buf + size, PAGE_SIZE - size, "[%08lx] *pgd=%08llx",
			 addr, (long long)pgd_val(*pgd));

	do {
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		if (pgd_none(*pgd))
			break;

		if (pgd_bad(*pgd)) {
			size += snprintf(buf + size, PAGE_SIZE - size, "(bad)");
			break;
		}

		pud = pud_offset(pgd, addr);
		if (PTRS_PER_PUD != 1)
			size += snprintf(buf + size, PAGE_SIZE - size,
				     ", *pud=%08llx", (long long)pud_val(*pud));

		if (pud_none(*pud))
			break;

		if (pud_bad(*pud)) {
			size += snprintf(buf + size, PAGE_SIZE - size, "(bad)");
			break;
		}

		pmd = pmd_offset(pud, addr);
		if (PTRS_PER_PMD != 1)
			size += snprintf(buf + size, PAGE_SIZE - size,
				     ", *pmd=%08llx", (long long)pmd_val(*pmd));

		if (pmd_none(*pmd))
			break;

		if (pmd_bad(*pmd)) {
			size += snprintf(buf + size, PAGE_SIZE - size, "(bad)");
			break;
		}

		/* We must not map this if we have highmem enabled */
		if (PageHighMem(pfn_to_page(pmd_val(*pmd) >> PAGE_SHIFT)))
			break;

		pte = pte_offset_map(pmd, addr);
		size += snprintf(buf + size, PAGE_SIZE - size, ", *pte=%08llx",
			     (long long)pte_val(*pte));
		pte_unmap(pte);
	} while (0);

	size += snprintf(buf + size, PAGE_SIZE - size, "\n");

	return size - temp;
}

static ssize_t show_phys_addr(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	ssize_t size;
	unsigned long va_addr = virt_addr;
	struct task_struct *tgt_task = NULL;

	if (!buf) {
		pr_err("[%s]:%d buf is null!\n", __func__, __LINE__);
		return -1;
	}

	size = snprintf(buf, PAGE_SIZE, "%u, 0x%lx, %u\n", pid, virt_addr,
		     virt_len);

	if (pid == 0) {
		tgt_task = current;
	} else {
		tgt_task = pid_task(find_vpid(pid), PIDTYPE_PID);
	}
	/*tgt_task = find_task_by_vpid(pid); */

	if (!tgt_task) {
		size += snprintf(buf + size, PAGE_SIZE - size,
			     "[virt_to_phys] tgt_task is NULL!\n");
		return -1;
	}

	if (!find_vma(tgt_task->mm, va_addr)) {
		size += snprintf(buf + size, PAGE_SIZE - size,
			     "[virt_to_phys] cannot find vma!\n");
		return -1;
	}
	size += snprintf(buf + size, PAGE_SIZE - size, "[virt_to_phys]:");

	size += show_phys_pte(buf, size, tgt_task->mm, va_addr);

	return size;
}

static ssize_t store_virt_addr(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t count)
{
	unsigned int args = 0, argl = 0;
	unsigned int len = count;
	const char *head = buf;
	char *p;

	if (!buf) {
		pr_err("[%s]:%d buf is null!\n", __func__, __LINE__);
		return -1;
	}

	while ((len > 0) && (args < 3)) {
		p = memchr(head, ' ', len);
		argl = p ? p - head : 0;

		switch (args) {
		case 0:
			if (1 != sscanf(head, "%u", &pid)) {
				return -1;
			}
			break;
		case 1:
			if (1 != sscanf(head, "%lx", &virt_addr)) {
				return -1;
			}
			break;
		case 2:
			if (1 != sscanf(head, "%u", &virt_len)) {
				return -1;
			}
			break;
		default:
			pr_err("[%s]:%d invalid args!\n", __func__, __LINE__);
		}

		head = head + argl + 1;
		len = len - argl - 1;
		args++;
	}

	return count;
}

static DEVICE_ATTR(virt_to_phys, 0640, show_phys_addr, store_virt_addr);

static struct attribute *virt_to_phys_attrs[] = {
	&dev_attr_virt_to_phys.attr,
	NULL,
};

static struct attribute_group virt_to_phys_attr_grp = {
	.attrs = virt_to_phys_attrs,
};

static int virt_to_phys_probe(struct platform_device *pdev)
{
	int ret;

	pr_info("[%s]:%d enter.\n", __func__, __LINE__);

	ret = sysfs_create_group(&(pdev->dev.kobj), &virt_to_phys_attr_grp);
	if (ret) {
		pr_err("Failed to create sysfs virt_to_phys_attr_grp\n");
		return ret;
	}

	pr_info("[%s]:%d leave.\n", __func__, __LINE__);

	return ret;
}

static int virt_to_phys_remove(struct platform_device *pdev)
{
	return 0;
}

#define MODULE_NAME		"hisilicon,virt_to_phys"

static const struct of_device_id virt_to_phys_match[] = {
	{.compatible = MODULE_NAME},
	{},
};

static struct platform_driver virt_to_phys_drv = {
	.probe = virt_to_phys_probe,
	.remove = virt_to_phys_remove,
	.driver = {
		   .name = "virt_to_phys",
		   .of_match_table = of_match_ptr(virt_to_phys_match),
		   },
};

static int __init virt_to_phys_init(void)
{
	return platform_driver_register(&virt_to_phys_drv);
}

module_init(virt_to_phys_init);

static void __exit virt_to_phys_exit(void)
{
	platform_driver_unregister(&virt_to_phys_drv);
}

module_exit(virt_to_phys_exit);

MODULE_AUTHOR("cuiyong1@huawei.com>");
MODULE_DESCRIPTION("VIRT TO PHYS MODULE");
MODULE_LICENSE("GPL v2");
