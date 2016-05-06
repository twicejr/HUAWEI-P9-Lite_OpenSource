/*
 * Copyright (C) 2013-2013 ...
 * ...
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/iommu.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>

#include <linux/hisi/hi3xxx/global_ddr_map.h>
#include <linux/hisi/ion-iommu.h>

#ifdef IOMMU_DEBUG
#define D(format, arg...) \
	do {\
		printk(KERN_INFO "[iommutest] " format, ##arg);\
	} while(0)
#else
#define D(format, arg...)
#endif

#define HISI_IOMMU_PGTABLE_ADDR (HISI_RESERVED_SMMU_PHYMEM_BASE)
#define HISI_IOMMU_PGTABLE_SIZE (HISI_RESERVED_SMMU_PHYMEM_SIZE)

struct iommu_test {
	void *map_priv;
	void *priv2;
	void *priv3;
	void *priv4;
};

/**
 * str1: options
 * str2: option to find
 */
static unsigned long getopt(const char *str1, const char *str2)
{
	char *p = NULL;
	unsigned long value = 0;

	p = strstr(str1, str2);
	if (!p)
		return 0;

	for (; *p; p++) {
		if (*p == '=') {
			if (sscanf(p + 1, "%x", &value) == 0)
				value = 0;

			break;
		}
	}

	return value;
}

void dump_map_format(struct iommu_map_format *fmt)
{

	if (fmt->is_tile) {
		D("format:\n"
		"-----------------------------------------------------\n"
		"| iova_start: 0x%lx, iova_size: 0x%lx\n"
		"| iommu_ptb_base: 0x%lx, iommu_iova_base: 0x%lx\n"
		"| phys_page_line: 0x%lx, virt_page_line: 0x%lx\n"
		"| is_tile: 0x%lx\n"
		"-----------------------------------------------------\n",
		fmt->iova_start, fmt->iova_size,
		fmt->iommu_ptb_base, fmt->iommu_iova_base,
		fmt->phys_page_line, fmt->virt_page_line,
		fmt->is_tile);
	} else {
		D("format:\n"
		"-----------------------------------------------------\n"
		"| iova_start: 0x%lx, iova_size: 0x%lx\n"
		"| iommu_ptb_base: 0x%lx, iommu_iova_base: 0x%lx\n"
		"-----------------------------------------------------\n",
		fmt->iova_start, fmt->iova_size,
		fmt->iommu_ptb_base, fmt->iommu_iova_base);
	}
}

/* ------------------------------------------------------------------------- */

struct maptest_info {
	struct scatterlist sg;
	struct iommu_map_format format;
};
static void do_unmap(struct maptest_info *info)
{
	struct scatterlist *sg = &info->sg;
	struct page *page;
	unsigned int len;
	int ret;

	/* iommu unmap */
	ret = hisi_iommu_unmap_domain(&info->format);
	if (ret) {
		D("hisi iommu unmap domain failed!\n");
	}

	page = sg_page(sg);
	len = sg->length;
	__free_pages(page, get_order(len));

	D("test result: %s\n"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
		ret ? "failed" : "pass");
}

static void do_map(struct maptest_info *info, unsigned int len)
{

	struct page *page;
	int ret;
	int i;

	page = alloc_pages(GFP_KERNEL, get_order(len));
	sg_init_table(&info->sg, 1);
	sg_set_page(&info->sg, page, len, 0);

	/* map */
	ret = hisi_iommu_map_domain(&info->sg, &info->format);
	if (ret) {
		D("iommu map domain failed\n");
	}

	/* dump map result */
	D("check map result:\n")
	for (i = 0; i < (len >> PAGE_SHIFT); i++) {
		unsigned long tmp_iova = info->format.iova_start + i * PAGE_SIZE;
		D(" 0x%lx ---- 0x%lx\n", tmp_iova,
				hisi_iommu_domain_iova_to_phys(tmp_iova));
		if (i > 20)
			break;
	}

	D("test result: %s\n"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
		ret ? "failed" : "pass");
}

static ssize_t map_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	return snprintf(buf, PAGE_SIZE, "usage: map=0x?, echo len=0x?, is_tile=0x? "
		"phys_len=0x?, virt_len=0x? > map\n");
}

static ssize_t map_store(struct device *pdev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	struct iommu_test *test_data = dev_get_drvdata(pdev);
	unsigned int map = 0; /* 1: map, 0: unmap */
	unsigned int len = 0;
	unsigned int is_tile = 0;
	unsigned int phys_len = 0, virt_len = 0;
	struct maptest_info *info;

	map = getopt(buf, "map");

	len = getopt(buf, "len");
	if ((map == 1) && (len == 0)) {
		D("len should not be 0\n");
		return size;
	}

	is_tile = getopt(buf, "is_tile");
	if (is_tile) {
		phys_len = getopt(buf, "phys_len");
		virt_len = getopt(buf, "virt_len");
		if ((phys_len == 0) || (virt_len == 0)) {
			D("phys_len and virt_len should not be 0\n");
			return size;
		}
	}

	D("map: 0x%x, len: 0x%x, is_tile: 0x%x, phys_len: 0x%x, virt_len: 0x%x, ",
		map, len, is_tile, phys_len,virt_len);

	/* DO TEST */
	if (map) {
		info = kzalloc(sizeof(*info), GFP_KERNEL);
		if (info) {
			info->format.is_tile = is_tile;
			info->format.phys_page_line = phys_len;
			info->format.virt_page_line = virt_len;

			test_data->map_priv = info;
			do_map(info, len);
			dump_map_format(&info->format);
		}
	} else {
		info = test_data->map_priv;
		dump_map_format(&info->format);
		do_unmap(info);
		kfree(info);
		test_data->map_priv = NULL;
	}

	D("do %s done\n\n\n", map ? "map" : "unmap");

	return size;
}

static DEVICE_ATTR(map, S_IRUGO | S_IWUSR, map_show, map_store);

/* ------------------------------------------------------------------------- */

static ssize_t dump_pgtbl_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	return snprintf(buf, PAGE_SIZE, "usage: echo a=0xXXXX, l=0xXXXX > dump_pgtbl!\n");
}
static ssize_t dump_pgtbl_store(struct device *pdev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	const char *p;
	unsigned int a = 0;
	unsigned int l = 0x10;
	unsigned int i = 0;
	void __iomem * pgtbl_addr;

	for (p = buf; *p; p++) {
		if ((*p == 'a') && (*(p + 1) == '=')) {
			if (sscanf(p + 2, "%x", &a) != 0)
				printk("a: 0x%x\n", a);
			p += 2;
		}

		if ((*p == 'l') && (*(p + 1) == '=')) {
			if (sscanf(p + 2, "%x", &l) != 0)
				printk("l: 0x%x\n", l);
			p += 2;
		}
	}

	a = a & (~3);
	l = l & (~3);

	if ((a + l) > HISI_IOMMU_PGTABLE_SIZE) {
		printk("ilegal a/l\n");
		return size;
	}

	pgtbl_addr = ioremap_nocache(HISI_IOMMU_PGTABLE_ADDR, HISI_IOMMU_PGTABLE_SIZE);
	if (!pgtbl_addr) {
		printk("ioremap failed!\n");
		return size;
	}

	for (i = a; i <= (a + l); i += 0x10) {
		printk("0x%08x: 0x%08x  0x%08x  0x%08x  0x%08x\n",
			(HISI_IOMMU_PGTABLE_ADDR + i),
			*(unsigned *)(pgtbl_addr + i),
			*(unsigned *)(pgtbl_addr + i + 4),
			*(unsigned *)(pgtbl_addr + i + 8),
			*(unsigned *)(pgtbl_addr + i + 0xC));
	}

	iounmap(pgtbl_addr);

	return size;
}
static DEVICE_ATTR(dump_pgtbl, S_IRUGO | S_IWUSR, dump_pgtbl_show, dump_pgtbl_store);

/* ------------------------------------------------------------------------- */

static ssize_t ptbspeed_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t size)
{
	struct timespec stamp1, stamp2;
	struct scatterlist sg;
	unsigned long iova;
	unsigned long iova_size;
	s64 ns_passed;
	int i;

	iova_size = getopt(buf, "len");
	if (iova_size <= 0) {
		printk(KERN_ERR "getopt failed!\n");
		return 0;
	}

	/* init sg */
	sg_init_table(&sg, 1);
	sg.dma_address = 0x40000000;
	sg.length = iova_size;

	/* alloc iova */
	iova = hisi_iommu_alloc_iova(iova_size, 0);

	/* do test */
	getnstimeofday(&stamp1);
	for (i = 0; i < 1; i++) {
		/* call iommu_map_range */
		hisi_iommu_map_range(iova, &sg, iova_size);

		/* unmap */
		hisi_iommu_unmap_range(iova, iova_size);
	}
	getnstimeofday(&stamp2);

	stamp1 = timespec_sub(stamp2, stamp1);
	ns_passed = timespec_to_ns(&stamp1);

	hisi_iommu_free_iova(iova, iova_size);

	printk(KERN_INFO "iommu map unmap 0x%lx needs %lld ns\n",
			iova_size, ns_passed);
	return size;
}
static DEVICE_ATTR(ptbspeed, S_IWUSR, NULL, ptbspeed_store);

/* ------------------------------------------------------------------------- */

static ssize_t iovapoolinfo_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	int ret = 0;
	size_t size, available;
	size = hisi_iommu_iova_size();
	available = hisi_iommu_iova_available();
	
	printk(KERN_INFO "iova pool info: size: 0x%lx, available: 0x%lx\n",
			size, available);

	ret += snprintf(buf, PAGE_SIZE, "iova pool info: size: 0x%lx, available: 0x%lx\n", 
		size, available);
	return ret;
}
static DEVICE_ATTR(iovapoolinfo, S_IRUGO, iovapoolinfo_show, NULL);

/* ------------------------------------------------------------------------- */

static int create_attr_file(struct device *dev)
{
	int ret = 0;
	ret |= device_create_file(dev, &dev_attr_map);
	ret |= device_create_file(dev, &dev_attr_dump_pgtbl);
	ret |= device_create_file(dev, &dev_attr_ptbspeed);
	ret |= device_create_file(dev, &dev_attr_iovapoolinfo);

	if (ret) {
		D("create attr file error!\n");
	}
	return ret;
}

static void remove_attr_file(struct device *dev){}

static int hisi_iommutest_probe(struct platform_device *pdev)
{
	struct iommu_test *test;

	test = devm_kzalloc(&pdev->dev, sizeof(struct iommu_test), GFP_KERNEL);
	if (!test)
		return -ENOMEM;
	dev_set_drvdata(&pdev->dev, test);
	create_attr_file(&pdev->dev);

	return 0;
}
static int hisi_iommutest_remove(struct platform_device *pdev)
{

	remove_attr_file(&pdev->dev);

	return 0;
}

#define IOMMUTEST_DEV_NUM 1
struct platform_device iommutest_dev[IOMMUTEST_DEV_NUM];

struct platform_driver hisi_iommutest_drv = {
	.probe = hisi_iommutest_probe,
	.remove = hisi_iommutest_remove,
	.driver = {
		.name = "hisi-iommu-test",
	},
};

int init_iommt_test(void)
{
	int i;
	int ret;

	for (i = 0; i < IOMMUTEST_DEV_NUM; i++) {
		iommutest_dev[i].id = i;
		iommutest_dev[i].name = "hisi-iommu-test";
		ret = platform_device_register(&iommutest_dev[i]);
		if (ret) {
			printk(KERN_ERR "init_iommt_test device register is failed!: %d\n", ret);
			return ret;
		}
	}

	ret = platform_driver_register(&hisi_iommutest_drv);
	if (ret) {
			printk(KERN_ERR "init_iommt_test device register is failed!: %d\n", ret);
			return ret;
		}

	return ret;
}
