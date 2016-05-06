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
#include <linux/hisi/hisi_ion.h>
#include <linux/hisi/ion-iommu.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/of.h>

/*#define IOMMU_DEBUG*/
#ifdef IOMMU_DEBUG
#define D(format, arg...) \
	do {\
		printk(KERN_ERR "[iommutest] " format, ##arg);\
	} while (0)
#else
#define D(format, arg...)
#endif
#undef IOMMU_DEBUG


static struct sg_table *table;

enum {
	IOMMU_TEST,
	ION_TEST,
	TILE_TEST
};

struct smmu_tester{
	struct ion_handle *ion_handle;
	struct ion_client *ion_client;
	struct iommu_domain *domain;
};

struct iommu_page_info {
	struct page *page;
	unsigned int order;
	struct list_head list;
};

static struct iommu_domain_data *info;
static struct sg_table *table;
struct smmu_tester *smmu_tester;

/*
 *iova:the start io virtual address.
 *size:the size of io virtual memory.
 *this function unmap a section io virtual memory
 */
static int iommu_unmap_test(unsigned int iova, unsigned int size)
{
	int ret;
	if (!smmu_tester->domain) {
		D("domain is null");
		return -EINVAL;
	}
	/* iommu unmap */
	ret = iommu_unmap(smmu_tester->domain, iova, size);
	if (!ret) {
		D("hisi iommu unmap domain failed!\n");
	}
	return ret;
}

/*this function do iommu map*/
ssize_t iommu_map_test(unsigned int start , unsigned int size)
{
	unsigned int iova_start = 0;
	unsigned int map_size = 0;
	unsigned int i;
	struct scatterlist *sg = NULL ;
	ktime_t time_start, time_end;
	unsigned long diff;
	int ret = 0;

	/*get parameter from buffer*/
	iova_start = start;
	map_size = size;

	D("%s: iova_start: 0x%x, size: 0x%x ", __func__, iova_start, map_size);
	time_start = ktime_get();

	if (smmu_tester->domain && table) {
		for_each_sg(table->sgl, sg, table->nents, i){
			ret = iommu_map(smmu_tester->domain, iova_start, page_to_phys(sg_page(sg)), sg->length, IOMMU_READ|IOMMU_WRITE|IOMMU_CACHE);
			if (ret) {
				D("failed to map devmem: %d\n",ret);
					goto out;
			}
			iova_start += sg->length;
		}
	}

	time_end = ktime_get();
	diff = ktime_to_us(ktime_sub(time_end,time_start));
	D("%s: mapping time is 0x%lx \n", __func__, diff);
	return size;

out:
	return -ENOSPC;
}

/*get physical address according to io vritual address*/
ssize_t iova_to_phy(void)
{
	unsigned int iova_addr = 0;
	unsigned int phys_addr;

	phys_addr = iommu_iova_to_phys(smmu_tester->domain, iova_addr);
	D("iova_addr=0x%x and phys_addr=0x%x\n", iova_addr, phys_addr);
	return 0;
}

/*free physical memory*/
static int free_memory(void)
{
	int i;
	struct scatterlist *sg = NULL;
	unsigned int mem_size;
	if (table) {
		for_each_sg(table->sgl, sg, table->nents, i) {
			__free_pages(sg_page(sg), get_order(sg->length));
			mem_size += sg->length;
		}
		D("%s:free total memory 0x%x \n", __func__, mem_size);
		sg_free_table(table);
		kfree(table);
	}
	table = NULL;
	return 0;
}

/*
 *this function allocate physical memory,
 *and make them to scatter lista.
 *table is global .
 */
static struct iommu_page_info *create_node(void)
{
	struct iommu_page_info *info = NULL;
	struct page *page = NULL ;
	info = kmalloc(sizeof(struct iommu_page_info), GFP_KERNEL);
	if (!info) {
		D("%s: kmalloc info failed!\n", __func__);
		return NULL;
	}
	page = alloc_pages(GFP_KERNEL, 1);
	/*alloc 8kb each
	 * time*/
	if (!page) {
		D("alloc page error \n");
		kfree(info);
		return NULL;
	}
	info->page = page;
	info->order = 0;
	INIT_LIST_HEAD(&info->list);
	return info;
}

static int alloc_memory (unsigned int size)
{
	int map_size = 0;
	unsigned int sum = 0;
	struct list_head pages;
	struct iommu_page_info *info, *tmp_info;
	unsigned int i = 0, ret = 0;
	struct scatterlist *sg = NULL;

	INIT_LIST_HEAD(&pages);
	map_size  = size;

	if (map_size < 0)
		return -EINVAL;
	D("%s: map_size=0x%x \n", __func__, map_size);
	do {
		info = create_node();
		if (!info)
			goto error;
		list_add_tail(&info->list, &pages);
		sum += (1 << info->order) *PAGE_SIZE;
		i++;
	} while (sum < map_size);

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table) {
			goto error;
		}

	ret = sg_alloc_table(table,i, GFP_KERNEL);
	if (ret) {
			kfree(table);
			goto error;
		}
	sg = table->sgl;
	list_for_each_entry_safe(info, tmp_info, &pages, list)
	{
		struct page *page = info->page;
		sg_set_page(sg, page, (1 << info->order)*PAGE_SIZE, 0);
		sg = sg_next(sg);
		list_del(&info->list);
		kfree(info);
	}
	D("sglist is ok \n");
	return map_size;
error:
	list_for_each_entry_safe(info, tmp_info, &pages, list)
	{
		list_del(&info->list);
		kfree(info);
	}
	return 0;
}
/*
 *test mapping address from ion device
 */
int test_smmu_ion_tile_map(unsigned int global_map_start, unsigned int global_map_size)
{
	int ret;
	struct iommu_map_format format = {0};
	format.iova_size = global_map_size;
	format.phys_page_line = 60;
	format.virt_page_line = 64;
	format.is_tile = 0x01;
	format.prot = 0xff;

	smmu_tester->ion_handle = ion_alloc(smmu_tester->ion_client, global_map_size, SZ_4K, ION_HEAP(ION_SYSTEM_HEAP_ID),0x0);
	if (IS_ERR(smmu_tester->ion_handle)) {
		D("alloc is fail\n");
		return 0;
	}

	ret = ion_map_iommu(smmu_tester->ion_client, smmu_tester->ion_handle, &format);
	if (ret)
	{
		D("ion map iommu is failed\n");
		return 0;
	}
	D("%s end\n", __func__);
	return format.iova_start;
}

/*
 * test unmapping address from ion device
 */
static int test_smmu_ion_tile_unmap(void)
{
	printk(KERN_ERR"%s start\n", __func__);
	ion_unmap_iommu(smmu_tester->ion_client, smmu_tester->ion_handle);
	return 0;
}

int test_smmu_ion_map(unsigned int global_map_start, unsigned int global_map_size)
{
	int ret;
	unsigned int size = global_map_size;
	struct iommu_map_format format = {0};
	unsigned int align = SZ_4K;
	format.iova_size = size;
	format.prot = 0xff;
	smmu_tester->ion_handle = ion_alloc(smmu_tester->ion_client, size,align, ION_HEAP(ION_SYSTEM_HEAP_ID), 0x0);
	if (IS_ERR(smmu_tester->ion_handle)) {
		pr_err("alloc is fail\n");
		return 0;
	}
	ret = ion_map_iommu(smmu_tester->ion_client, smmu_tester->ion_handle, &format);
	if (ret) {
		pr_err("ion_map_iommu is failed\n");
		return 0;
	}
	return format.iova_start;
}

int test_smmu_ion_unmap(void)
{
	D("%s start\n", __func__);
	ion_unmap_iommu(smmu_tester->ion_client, smmu_tester->ion_handle);
	return 1;
}

extern void smmu_print_pgtable(void);
extern void set_smmu_param(unsigned int start, unsigned int size);
ssize_t smmu_test_main(int type, unsigned int global_map_size, unsigned int global_map_start)
{
	unsigned int ret = 0;

	ret = alloc_memory(global_map_size);
	if (!ret) {
		D("ret = %d\n", ret);
		return -ENOMEM;
	}
	switch (type) {
	case IOMMU_TEST:
		iommu_map_test(global_map_start, global_map_size);
		set_smmu_param(global_map_start, global_map_size);
		smmu_print_pgtable();
		iommu_unmap_test(global_map_start, global_map_size);
		smmu_print_pgtable();
		break;
	case ION_TEST:
		ret = test_smmu_ion_map(global_map_start, global_map_size);
		set_smmu_param(ret, global_map_size);
		smmu_print_pgtable();
		test_smmu_ion_unmap();
		smmu_print_pgtable();
		break;
	case TILE_TEST:
		ret = test_smmu_ion_tile_map(global_map_start, global_map_size);
		set_smmu_param(ret, global_map_size);
		smmu_print_pgtable();
		test_smmu_ion_tile_unmap();
		smmu_print_pgtable();
		break;
	default:
		return -EINVAL;
		break;
	};
	free_memory();
	return 0;
}

static int hisi_iommutest_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	smmu_tester = devm_kzalloc(&pdev->dev, sizeof(struct smmu_tester), GFP_KERNEL);
	if (!smmu_tester) {
		D("in %s devm_kzalloc is failed\n", __func__);
		return -ENOMEM;
	}

	smmu_tester->ion_client = hisi_ion_client_create("smmu_test");
	if (IS_ERR(smmu_tester->ion_client)) {
		D("hisi ion client create failed \n");
		return -ENODEV;
	}
	smmu_tester->domain = iommu_domain_alloc(dev->bus);
	if (!smmu_tester->domain) {
		D("create domain fail \n");
		return -ENOMEM;
	} else {
		iommu_attach_device(smmu_tester->domain, dev);
		info = (struct iommu_domain_data *)smmu_tester->domain->priv;
		D("%s,iova_start=0x%lx,iova_size=0x%lx \n", __func__,
					info->iova_start,
					info->iova_size);
	}
	return 0;
}


static struct of_device_id hisi_smmu_of_table[] = {
	{ .compatible = "hisi,hisi-smmu-tester"},
	{ },
};
MODULE_DEVICE_TABLE(of, hisi_smmu_of_table);

static struct platform_driver hisi_iommutest_drv = {
	.driver	= {
		.owner		= THIS_MODULE,
		.name		= "hisi-smmu-tester",
		.of_match_table	= of_match_ptr(hisi_smmu_of_table),
	},
	.probe	= hisi_iommutest_probe,
};

/*the inital function for iommu test module*/
static int __init init_iommu_test(void)
{
	int err = -EBUSY;
	err = platform_driver_register(&hisi_iommutest_drv);
	if (err)
		D("register device error \n");

	return 0;

}
module_init(init_iommu_test);

