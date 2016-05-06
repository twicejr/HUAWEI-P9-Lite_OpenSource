/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/export.h>
#include <linux/err.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/rwsem.h>
#include <linux/uaccess.h>
#include <linux/dma-mapping.h>
#include <linux/dma-contiguous.h>
#include <asm/cacheflush.h>
#include <linux/compat.h>
#include <ion_priv.h>

#include <global_ddr_map.h>

#define CLUSTER0_RESUME_BIT 	0xfff0A334
#define CLUSTER1_RESUME_BIT 	0xfff0A338

static struct ion_device *idev;
static int num_heaps;
static struct ion_heap **heaps;
static void __iomem * cluster0_resume_bit;
static void __iomem * cluster1_resume_bit;

struct ion_device *get_ion_device(void) {
	return idev;
}

static void ion_pm_init(void)
{
	cluster0_resume_bit = ioremap(CLUSTER0_RESUME_BIT,sizeof(int));
	cluster1_resume_bit = ioremap(CLUSTER1_RESUME_BIT,sizeof(int));
}

void hisi_ion_flush_cache_all(void *dummy)
{
	flush_cache_all();
	return;
}

void ion_flush_cache_all(void)
{
	int cpu;
	unsigned int cluster0_stat;
	unsigned int cluster1_stat;
	unsigned int stat;
	cpumask_t mask;
	preempt_disable();
	cluster0_stat = readl(cluster0_resume_bit) & 0x0f;
	cluster1_stat = readl(cluster1_resume_bit) & 0x0f;

	stat = ~(cluster0_stat | cluster1_stat << 4) & 0xff;
	if (cluster1_stat == 0x0f)
		stat |= BIT(4);
	if (cluster0_stat == 0x0f)
		stat |= BIT(0);

	cpumask_clear(&mask);
	for_each_online_cpu(cpu) {
		if(stat & (1 << cpu))
			cpumask_set_cpu(cpu, &mask);
	}

	on_each_cpu_mask(&mask, hisi_ion_flush_cache_all, NULL, 1);
	preempt_enable();
	return;
}

struct ion_client *hisi_ion_client_create(const char *name)
{
	return ion_client_create(idev, name);
}

EXPORT_SYMBOL(hisi_ion_client_create);

static void free_pdata(const struct ion_platform_data *pdata)
{
	kfree(pdata);
}

static struct ion_platform_heap hisi_ion_heaps[] = {
	{
		.type = ION_HEAP_TYPE_SYSTEM,
		.id = ION_SYSTEM_HEAP_ID,
		.name = "system-heap",
	},
	{
		.type = ION_HEAP_TYPE_SYSTEM_CONTIG,
		.id = ION_SYSTEM_CONTIG_HEAP_ID,
		.name = "system-contig-heap",
	},
	{
		.type = ION_HEAP_TYPE_CARVEOUT,
		.id = ION_GRALLOC_HEAP_ID,
		.name = "carveout-heap",
		.base = HISI_RESERVED_GRAPHIC_PHYMEM_BASE,
		.size = HISI_RESERVED_GRAPHIC_PHYMEM_SIZE,
	},
	{
		.type = ION_HEAP_TYPE_DMA,
		.id = ION_DMA_HEAP_ID,
		.name = "ion-dma-heap",
	},
	/*
	{
		.type = ION_HEAP_TYPE_SECCM,
		.id = ION_DRM_GRALLOC_HEAP_ID,
		.name = "drm-gralloc-heap",
		.size = 0x4000000,
	},
	{
		.type = ION_HEAP_TYPE_SECCM,
		.id = ION_DRM_VCODEC_HEAP_ID,
		.name = "drm-vcodec-heap",
		.size = 0x2000000,
	},
	*/
    {
		.type = ION_HEAP_TYPE_SECCM,
		.id = ION_TUI_HEAP_ID,
		.name = "tui-heap",
		.size = HISI_RESERVED_TUI_CMA_PHYMEM_SIZE,
    },
};

#ifndef CONFIG_ARM64
static int check_vaddr_bounds(unsigned long start, unsigned long end)
{
	struct mm_struct *mm = current->active_mm;
	struct vm_area_struct *vma;
	int ret = 1;

	if (end < start)
		goto out;

	vma = find_vma(mm, start);
	if (vma && vma->vm_start < end) {
		if (start < vma->vm_start)
			goto out;
		if (end > vma->vm_end)
			goto out;
		ret = 0;
	}

out:
	return ret;
}

static int ion_no_pages_cache_ops(struct ion_client *client,
			struct ion_handle *handle,
			void *vaddr,
			unsigned int offset, unsigned int length,
			unsigned int cmd)
{
	unsigned long size_to_vmap, total_size;
	int i, j, ret;
	void *ptr = NULL;
	ion_phys_addr_t buff_phys = 0;
	ion_phys_addr_t buff_phys_start = 0;
	size_t buf_length = 0;

	ret = ion_phys(client, handle, &buff_phys_start, &buf_length);
	if (ret)
		return -EINVAL;

	buff_phys = buff_phys_start;

	if (!vaddr) {
		/*
		 * Split the vmalloc space into smaller regions in
		 * order to clean and/or invalidate the cache.
		 */
		size_to_vmap = ((VMALLOC_END - VMALLOC_START)/8);
		total_size = buf_length;

		for (i = 0; i < total_size; i += size_to_vmap) {
			size_to_vmap = min(size_to_vmap, total_size - i);
			for (j = 0; j < 10 && size_to_vmap; ++j) {
				ptr = ioremap(buff_phys, size_to_vmap);
				if (ptr) {
					switch (cmd) {
					case ION_HISI_CLEAN_CACHES:
						dmac_clean_range(ptr,
							ptr + size_to_vmap);
						break;
					case ION_HISI_INV_CACHES:
						dmac_inv_range(ptr,
							ptr + size_to_vmap);
						break;
					case ION_HISI_CLEAN_INV_CACHES:
						dmac_flush_range(ptr,
							ptr + size_to_vmap);
						break;
					default:
						return -EINVAL;
					}
					buff_phys += size_to_vmap;
					break;
				} else {
					size_to_vmap >>= 1;
				}
			}
			if (!ptr) {
				pr_err("Couldn't io-remap the memory\n");
				return -EINVAL;
			}
			iounmap(ptr);
		}
	} else {
		switch (cmd) {
		case ION_HISI_CLEAN_CACHES:
			dmac_clean_range(vaddr, vaddr + length);
			break;
		case ION_HISI_INV_CACHES:
			dmac_inv_range(vaddr, vaddr + length);
			break;
		case ION_HISI_CLEAN_INV_CACHES:
			dmac_flush_range(vaddr, vaddr + length);
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}

static int ion_pages_cache_ops(struct ion_client *client,
			struct ion_handle *handle,
			void *vaddr, unsigned int offset, unsigned int length,
			unsigned int cmd)
{
	struct sg_table *table = NULL;

	table = ion_sg_table(client, handle);
	if (IS_ERR_OR_NULL(table))
		return PTR_ERR(table);

	switch (cmd) {
	case ION_HISI_CLEAN_CACHES:
		if (!vaddr)
			dma_sync_sg_for_device(NULL, table->sgl,
				table->nents, DMA_TO_DEVICE);
		else
			dmac_clean_range(vaddr, vaddr + length);
		break;
	case ION_HISI_INV_CACHES:
		if (!vaddr)
			dma_sync_sg_for_cpu(NULL, table->sgl,
				table->nents, DMA_FROM_DEVICE);
		else
			dmac_inv_range(vaddr, vaddr + length);
		break;
	case ION_HISI_CLEAN_INV_CACHES:
		if (!vaddr) {
			dma_sync_sg_for_device(NULL, table->sgl,
				table->nents, DMA_TO_DEVICE);
			dma_sync_sg_for_cpu(NULL, table->sgl,
				table->nents, DMA_FROM_DEVICE);
		} else {
			dmac_flush_range(vaddr, vaddr + length);
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

int ion_do_cache_op(struct ion_client *client, struct ion_handle *handle,
			void *uaddr, unsigned long offset, unsigned long len,
			unsigned int cmd)
{
	int ret = -EINVAL;
	unsigned long flags;
	struct sg_table *table;
	struct page *page;

	ret = ion_handle_get_flags(client, handle, &flags);
	if (ret)
		return -EINVAL;

	if (!ION_IS_CACHED(flags))
		return 0;

	table = ion_sg_table(client, handle);

	if (IS_ERR_OR_NULL(table))
		return PTR_ERR(table);

	page = sg_page(table->sgl);

	if (page)
		ret = ion_pages_cache_ops(client, handle, uaddr,
					offset, len, cmd);
	else
		ret = ion_no_pages_cache_ops(client, handle, uaddr,
					offset, len, cmd);

	return ret;

}
#endif

static long hisi_ion_custom_ioctl(struct ion_client *client,
				unsigned int cmd,
				unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
	case ION_HISI_CUSTOM_PHYS:
	{
		struct ion_phys_data data;
		struct ion_handle *handle;
		ion_phys_addr_t phys_addr;
		size_t size;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}

		handle = ion_import_dma_buf(client, data.fd_buffer);
		if (IS_ERR(handle)) {
			return PTR_ERR(handle);
	        }
		ret = ion_phys(client, handle, &phys_addr, &size);
		if (ret) {
			ion_free(client, handle);
			return ret;
		}

		data.size = size & 0xffffffff;
		data.phys_l = phys_addr & 0xffffffff;
		data.phys_h = (phys_addr >> 32) & 0xffffffff;

		if (copy_to_user((void __user *)arg, &data, sizeof(data))) {
			ion_free(client, handle);
			return -EFAULT;
		}
		ion_free(client, handle);

		break;
	}
	case ION_HISI_CUSTOM_SET_FLAG:
	{
		struct ion_flag_data data;
		struct ion_handle *handle;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}

        if ( (data.flags != 0) && (data.flags != (ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC)) ) {
			return -EINVAL;
		}
		handle = ion_import_dma_buf(client, data.shared_fd);

		if (IS_ERR(handle)) {
			pr_err("%s %d : handle %p fd 0x%x\n", __FUNCTION__,
				   __LINE__, handle, (unsigned int)data.shared_fd);
			return PTR_ERR(handle);
		}

		ret = ion_change_flags(client, handle, data.flags);
		ion_free(client, handle);

		break;
	}
#ifdef CONFIG_ARM64
	case ION_HISI_CLEAN_CACHES:
	case ION_HISI_CLEAN_INV_CACHES:
	{
		struct ion_flush_data data;
		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}
		ret = ion_sync_for_device(client, data.fd);
		break;
	}
	case ION_HISI_INV_CACHES:
	{
		struct ion_flush_data data;
		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}
		ret = ion_sync_for_cpu(client, data.fd);
		break;
	}
#else
	case ION_HISI_CLEAN_CACHES:
	case ION_HISI_INV_CACHES:
	case ION_HISI_CLEAN_INV_CACHES:
	{
		struct ion_flush_data data;
		unsigned long start, end;
		struct ion_handle *handle = NULL;
		struct mm_struct *mm = current->active_mm;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}

		handle = ion_import_dma_buf(client, data.fd);
		if (IS_ERR(handle)) {
			pr_info("%s: Could not import handle: %p\n",
				__func__, handle);
			return -EINVAL;
		}

		down_read(&mm->mmap_sem);

		start = (unsigned long) data.vaddr;
		end = (unsigned long) data.vaddr
			+ data.length;

		if (start && check_vaddr_bounds(start, end)) {
			pr_err("%s: virtual address %p is out of bounds\n",
				__func__, data.vaddr);
			ret = -EINVAL;
		} else {
			ret = ion_do_cache_op(
				client, handle, data.vaddr,
				data.offset,
				data.length, cmd);
		}
		up_read(&mm->mmap_sem);

		ion_free(client, handle);

		if (ret < 0)
			return ret;
		break;
	}
#endif
	default:
		return -ENOTTY;
	}

	return ret;
}

#ifdef CONFIG_COMPAT

struct compat_ion_flush_data {
	compat_int_t fd;
	compat_ulong_t vaddr;
	compat_int_t offset;
	compat_int_t length;
};

static int compat_get_ion_flush_data(struct compat_ion_flush_data __user *data32,
	struct ion_flush_data __user *data)
{
	compat_int_t fd;
	compat_ulong_t vaddr;
	compat_int_t offset;
	compat_int_t length;
	int err;

	err = get_user(fd, &data32->fd);
	err |= put_user(fd, &data->fd);
	err |= get_user(vaddr, &data32->vaddr);
	err |= put_user(vaddr, &data->vaddr);
	err |= get_user(offset, &data32->offset);
	err |= put_user(offset, &data->offset);
	err |= get_user(length, &data32->length);
	err |= put_user(length, &data->length);

	return err;
}

static int compat_put_ion_flush_data(struct compat_ion_flush_data __user *data32,
	struct ion_flush_data __user *data)
{
	compat_int_t fd;
	compat_ulong_t vaddr;
	compat_int_t offset;
	compat_int_t length;
	int err;

	err = get_user(fd, &data->fd);
	err |= put_user(fd, &data32->fd);
	err |= get_user(vaddr, &data->vaddr);
	err |= put_user(vaddr, &data32->vaddr);
	err |= get_user(offset, &data->offset);
	err |= put_user(offset, &data32->offset);
	err |= get_user(length, &data->length);
	err |= put_user(length, &data32->length);

	return err;
}

static long __attribute__((unused)) compat_hisi_ion_custom_ioctl(struct ion_client *client,
				unsigned int cmd,
				unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
	case ION_HISI_CUSTOM_PHYS:
		return hisi_ion_custom_ioctl(client, cmd, arg);
	case ION_HISI_CLEAN_CACHES:
	case ION_HISI_INV_CACHES:
	case ION_HISI_CLEAN_INV_CACHES:
	{
		struct compat_ion_flush_data __user *data32;
		struct ion_flush_data __user *data;
		int err;

		data32 = compat_ptr(arg);
		data = compat_alloc_user_space(sizeof(*data));
		if (data == NULL) {
			pr_err("%s: compat_alloc_user_space failed!\n", __func__);
			return -EFAULT;
		}

		err = compat_get_ion_flush_data(data32, data);
		if (err) {
			pr_err("%s: compat_get_ion_flush_data failed!\n", __func__);
			return err;
		}

		ret = hisi_ion_custom_ioctl(client, cmd, (unsigned long)data);

		err = compat_put_ion_flush_data(data32, data);

		return ret ? ret : err;

	}
	default:
		return -ENOTTY;
	}

	return ret;
}

#endif

extern int hisi_ion_enable_iommu(struct platform_device *pdev);

static int hisi_ion_probe(struct platform_device *pdev)
{
	struct ion_platform_data *pdata;
	int err = -1;
	int i;

	printk(KERN_ERR"%s,\n",__func__);
	pdata = kzalloc(sizeof(*pdata), GFP_KERNEL);
	if (IS_ERR_OR_NULL(pdata)) {
		err = PTR_ERR(pdata);
		goto out;
	}

	pdata->nr = ARRAY_SIZE(hisi_ion_heaps);
	pdata->heaps = hisi_ion_heaps;

	num_heaps = pdata->nr;
	dev_info(&pdev->dev, "num_heaps: %d\n", num_heaps);

	heaps = kcalloc(pdata->nr, sizeof(struct ion_heap *), GFP_KERNEL);
	if (!heaps) {
		err = -ENOMEM;
		free_pdata(pdata);
		goto out;
	}
	if (hisi_ion_enable_iommu(pdev)) {
		dev_info(&pdev->dev, "enable iommu fail \n");
		err = -EINVAL;
		goto freeheaps;
	}
	idev = ion_device_create(hisi_ion_custom_ioctl);
	if (IS_ERR_OR_NULL(idev)) {
		err = PTR_ERR(idev);
		goto freeheaps;
	}
	dev_info(&pdev->dev, "idev: %p\n", idev);

	/* create the heaps as specified in the board file */
	for (i = 0; i < num_heaps; i++) {
		struct ion_platform_heap *heap_data = &pdata->heaps[i];

		dev_info(&pdev->dev, "create heap %d "
			" ---> type: %d, id: %d, name: %s,"
			" base: 0x%lx, size: 0x%lx\n", i,
			heap_data->type, heap_data->id, heap_data->name,
			heap_data->base, heap_data->size);

		heap_data->priv = &pdev->dev;

		heaps[i] = ion_heap_create(heap_data);
		if (IS_ERR_OR_NULL(heaps[i])) {
			heaps[i] = 0;
			continue;
		} else {
			if (heap_data->size)
				pr_info("ION heap %s created at %lx "
					"with size %lx\n", heap_data->name,
							  heap_data->base,
							  heap_data->size);
			else
				pr_info("ION heap %s created\n",
							  heap_data->name);
		}

		ion_device_add_heap(idev, heaps[i]);
	}

	free_pdata(pdata);

	platform_set_drvdata(pdev, idev);
	ion_pm_init();
	return 0;

freeheaps:
	kfree(heaps);
	free_pdata(pdata);
out:
	return err;
}

static int hisi_ion_remove(struct platform_device *pdev)
{
	struct ion_device *idev = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < num_heaps; i++)
		ion_heap_destroy(heaps[i]);
	if (idev)
		ion_device_destroy(idev);
	kfree(heaps);
	return 0;
}

static struct of_device_id hisi_ion_match_table[] = {
	{.compatible = "hisi,k3v2-ion"},
	{.compatible = "hisi,k3v3-ion"},
	{.compatible = "hisi,k3v5-ion"},
	{.compatible = "hisi,k3v3plus-ion"},
	{},
};

static struct platform_driver hisi_ion_driver = {
	.probe = hisi_ion_probe,
	.remove = hisi_ion_remove,
	.driver = {
		.name = "ion-hisi",
		.of_match_table = hisi_ion_match_table,
	},
};

static int __init hisi_ion_init(void)
{
	printk(KERN_ERR"%s,\n",__func__);
	return platform_driver_register(&hisi_ion_driver);
}

static void __exit hisi_ion_exit(void)
{
	platform_driver_unregister(&hisi_ion_driver);
}

subsys_initcall(hisi_ion_init);
module_exit(hisi_ion_exit);
