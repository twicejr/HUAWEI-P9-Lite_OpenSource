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
#include <linux/hisi/hisi-iommu.h>
#include "ivp_smmu.h"

#define D(format, arg...) printk(KERN_INFO "[smmutest] " format, ##arg);
#define IS_PAGE_ALIGNED(x)		(!(x & (PAGE_SIZE - 1)))
#define BUF_SZ            (128)

struct smmu_test {
	struct ivp_smmu_dev *smmu_dev;
	struct list_head     map_list;
	void *priv1;
};

struct map_unit {
	struct page *pages;
	struct list_head list;
	unsigned int va;
	unsigned int pa;
	unsigned int sz;
	unsigned int prot;
};

/**
 * str1: options
 * str2: option to find
 */
static unsigned int getopt(const char *str1, const char *str2)
{
	char *p = NULL;
	unsigned int value = 0;

	p = strstr(str1, str2);
	if (!p) {
		return 0;
    }
    
	for (; *p; p++) {
		if (*p == '=') {
			if (sscanf(p + 1, "%x", &value) == 0) {
				value = 0;
            }

			break;
		}
	}

	return value;
}

/* ------------------------------------------------------------------------- */

static int is_mapped(struct smmu_test *test, unsigned int iova, unsigned int size)
{
	struct iommu_domain* domain = test->smmu_dev->domain;
	phys_addr_t ret = 0;

	while (size) {
		ret = iommu_iova_to_phys(domain, iova); 
		if (ret) {
			return 1;
		}
		iova += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	return 0;
}

static ssize_t map_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	return snprintf(buf, BUF_SZ, "usage: echo iova=0x?,size=0x?,prot=0x?,phya=0x? > map\n");
}

static ssize_t map_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct smmu_test *test = dev_get_drvdata(dev);
	struct map_unit *node;
	ktime_t time_start, time_end;
	unsigned int iova_start = 0;
	unsigned int map_size = 0;
	unsigned int prot = 0;
	phys_addr_t  phy_addr = 0;
	struct page *pages = NULL;
	int order, ret;
	s64 diff;

	iova_start = getopt(buf, "iova");
	map_size   = getopt(buf, "size");
	prot       = getopt(buf, "prot");
    phy_addr   = getopt(buf, "phya");

	iova_start = (iova_start >> PAGE_SHIFT) << PAGE_SHIFT;
	map_size = (map_size >> PAGE_SHIFT) << PAGE_SHIFT;
	
	/* DO TEST */
	time_start = ktime_get();

    if (!phy_addr) {
        /* alloc "map_size" space for test */
    	order = get_order(map_size);
    	pages = alloc_pages(GFP_KERNEL, order);
    	if (!pages) {
    		pr_err("%s: alloc_pages fail\n", __func__);
            goto err;
        }
        phy_addr = page_to_phys(pages);
    }

	D("%s: iova[0x%x], phy[0x%lx], size[0x%x], prot[0x%x]\n", __func__, 
            iova_start, (unsigned long)phy_addr, map_size, prot);
	
    /* do mapping and invalid the TLB */
    ret = iommu_map(test->smmu_dev->domain, iova_start, phy_addr, map_size, prot);
	if (ret < 0) {
		pr_err("%s: iommu_map fail ret[0x%x]\n", __func__, ret);
        goto err;
	}


	list_for_each_entry(node, &test->map_list, list) {
        if (node->va == iova_start) {
            pr_err("map more than once. %#x\n", node->va);
	        time_end = ktime_get();
	        diff = ktime_to_us(ktime_sub(time_end, time_start));
            D("%s: mapping time is 0x%lx \n", __func__, (unsigned long)diff);
            return size;
        }
	}

	node = kzalloc(sizeof(struct map_unit), GFP_KERNEL);
	if (!node) {
		pr_err("%s: alloc map_unit fail\n", __func__);
        goto err;
	}
	node->va = iova_start;
	node->sz = map_size;
	node->pa = phy_addr;
	node->pages = pages;
	node->prot  = prot;
	list_add_tail(&node->list, &test->map_list);
	
	time_end = ktime_get();
	diff = ktime_to_us(ktime_sub(time_end, time_start));
    D("%s: mapping time is 0x%lx \n", __func__, (unsigned long)diff);
	return size;
err:
    if (pages) {
	    free_pages((unsigned long)page_address(pages), order);
    }
    return 0;
}

static DEVICE_ATTR(map, (S_IRUGO | S_IWUSR), map_show, map_store);

/* ------------------------------------------------------------------------- */
static ssize_t unmap_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	return snprintf(buf, BUF_SZ, "usage: echo iova=0x?,size=0x? > unmap\n");
}

static ssize_t unmap_store(struct device *dev, 
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct smmu_test *test = dev_get_drvdata(dev);
	struct ivp_smmu_dev *smmu_dev = test->smmu_dev;
	struct map_unit *node = NULL;
	unsigned int iova_start = 0;
	unsigned int unmap_size = 0;
	size_t ret = 0;

	iova_start = getopt(buf, "iova");
	unmap_size = getopt(buf, "size");

	if (!IS_PAGE_ALIGNED(iova_start) || !IS_PAGE_ALIGNED(unmap_size)){
		pr_err("%s: unmap fail for unaligned iova[0x%x] size[0x%x]\n", 
				__func__, iova_start, unmap_size);
		return size;
	}

	D("%s: iova_start[0x%x], size[0x%x] \n", __func__, iova_start, unmap_size);

	list_for_each_entry(node, &test->map_list, list) {
        if (node->va == iova_start) {
            if (node->sz != unmap_size) {
                pr_err("%s: unmap fail, size should be[0x%x]\n", 
        				__func__, node->sz);
                return size;
            }
            goto unmap;
        }
	}

    pr_err("%s: unmap fail for invalid va or size\n", __func__);
    return size;

unmap:
	ret = iommu_unmap(smmu_dev->domain, iova_start, unmap_size);
	if (ret <= 0) {
		pr_err("%s: iommu_map fail ret[0x%lx]\n", __func__, ret);
		return ret;
	}

	list_for_each_entry(node, &test->map_list, list) {
        if (node->va == iova_start) {
	    	ret = is_mapped(test, node->va, node->sz);
	    	if (!ret) {
	    		D("%s: node unmapped, iova[0x%x], size[0x%x] \n", __func__, 
	    				node->va, node->sz);
	    	    list_del(&node->list);
                if (node->pages) {
	    	        free_pages((unsigned long)page_address(node->pages), get_order(node->sz));
                }
	    	    kfree(node);
                break;
	    	}
	    }
    }

	return size;
}
static DEVICE_ATTR(unmap, (S_IRUGO | S_IWUSR), unmap_show, unmap_store);

/* ------------------------------------------------------------------------- */
static ssize_t inv_tlb_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	return snprintf(buf, 64, "usage: echo vmid=0x? > inv_tlb\n");
}

static ssize_t inv_tlb_store(struct device *dev, 
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct smmu_test *test = dev_get_drvdata(dev);
	unsigned int vmid = 0;

	vmid = getopt(buf, "vmid");

	D("%s: vmid[0x%x] \n", __func__, vmid);

	ivp_smmu_invalid_tlb(test->smmu_dev, vmid);

	return size;
}
static DEVICE_ATTR(inv_tlb, (S_IRUGO | S_IWUSR), inv_tlb_show, inv_tlb_store);

/* ------------------------------------------------------------------------- */
static ssize_t mapped_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct smmu_test *test = dev_get_drvdata(dev);
	struct map_unit *node = NULL;
    int cnt = 0;
    int idx = 0;

	list_for_each_entry(node, &test->map_list, list) {
		cnt += printk("node[%3d]: va[0x%8x] pa[0x%8x] sz[0x%8x] prot[0x%4x]\n",
				idx++, node->va, node->pa, node->sz, node->prot);
	}
    return cnt;
}

static ssize_t mapped_store(struct device *dev, 
		struct device_attribute *attr, const char *buf, size_t size)
{
	return size;
}
static DEVICE_ATTR(mapped, (S_IRUGO | S_IWUSR), mapped_show, mapped_store);

/* ------------------------------------------------------------------------- */
static ssize_t v2p_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	return snprintf(buf, 32, "usage: echo iova=0x? > v2p\n");
}

static ssize_t v2p_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	struct smmu_test *test = dev_get_drvdata(dev);
	unsigned int iova_addr;
	unsigned int phys_addr;

	iova_addr = getopt(buf, "iova");
	phys_addr = iommu_iova_to_phys(test->smmu_dev->domain, iova_addr);
	
	D("iova_addr=[0x%x], phys_addr=[0x%x]\n", iova_addr, phys_addr);
	return size;
}
static DEVICE_ATTR(v2p, (S_IRUGO | S_IWUSR), v2p_show, v2p_store);

/* ------------------------------------------------------------------------- */


/*----------------------------------------------------------------------*/
static int create_attr_file(struct device *dev)
{
    int ret = 0;
    pr_info("=========%s==========\n", __func__);
	ret |= device_create_file(dev, &dev_attr_map);
	ret |= device_create_file(dev, &dev_attr_unmap);
	ret |= device_create_file(dev, &dev_attr_v2p);
	ret |= device_create_file(dev, &dev_attr_inv_tlb);
	ret |= device_create_file(dev, &dev_attr_mapped);

	if (ret) {
		D("create attr file error!\n");
	}
	return ret;
}

static void remove_attr_file(struct device *dev){}

static int ivp_smmutest_probe(struct platform_device *pdev)
{
	struct smmu_test *test;
    struct ivp_smmu_dev *smmu_dev = NULL;

    pr_info("=========%s==========\n", __func__);
	test = devm_kzalloc(&pdev->dev, sizeof(struct smmu_test), GFP_KERNEL);
	if (!test) {
        pr_err("%s: devm_kzalloc is failed\n", __func__);
		return -ENOMEM;
    }

    /* get smmu device */
    smmu_dev = ivp_smmu_get_device(0);
    if (!smmu_dev) {
		pr_err("%s: smmu get fail\n", __func__);
		return -ENODEV;
    }
	test->smmu_dev = smmu_dev;
	INIT_LIST_HEAD(&test->map_list);
	
	dev_set_drvdata(&pdev->dev, test);
	create_attr_file(&pdev->dev);

	return 0;
}
static int ivp_smmutest_remove(struct platform_device *pdev)
{
	remove_attr_file(&pdev->dev);
	return 0;
}

#define SMMUTEST_DEV_NUM 1
struct platform_device ivp_smmutest_dev[SMMUTEST_DEV_NUM];

struct platform_driver ivp_smmutest_drv = {
	.probe = ivp_smmutest_probe,
	.remove = ivp_smmutest_remove,
	.driver = {
		.name = "ivp-smmu-test",
	},
};

static int __init ivp_smmutest_init(void)
{
	int i;

	for (i = 0; i < SMMUTEST_DEV_NUM; i++) {
		ivp_smmutest_dev[i].id = i;
		ivp_smmutest_dev[i].name = "ivp-smmu-test";
		platform_device_register(&ivp_smmutest_dev[i]);
	}

	platform_driver_register(&ivp_smmutest_drv);

	return 0;
}
module_init(ivp_smmutest_init);

