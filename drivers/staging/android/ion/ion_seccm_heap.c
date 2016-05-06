/*
 * /ion/ion_seccm_heap.c
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#define pr_fmt(fmt) "seccm: " fmt

#include <linux/slab.h>
#include <linux/err.h>
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>
#include <linux/dma-contiguous.h>
#include <linux/mutex.h>
#include <linux/genalloc.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/delay.h>
#include "ion.h"
#include "ion_priv.h"

#define MAX_SECCM_HEAP_MAX  (6)
#define ION_SECCM_HEAP_ID_BASE ION_DRM_GRALLOC_HEAP_ID

extern int atfd_hisi_service_access_register_smc(u64 main_fun_id, u64 buff_addr_phy, u64 data_len, u64 sub_fun_id);
extern void create_mapping_late(phys_addr_t phys, unsigned long virt,phys_addr_t size, pgprot_t prot);
extern struct device *hisi_get_cma_device(char *name);
extern struct page *__dma_alloc_from_contiguous(struct device *dev, int count,unsigned int align);
extern void ion_flush_all_cpus_caches(void);

enum heap_status{
	CREAT  = 0,
	ALLOC  = 1,
};

struct ion_seccm_heap {
	struct ion_heap heap;
	struct gen_pool *pool;
	struct device *dev;
	unsigned long heap_status;
	unsigned long base;
	size_t size;
	int order;
	int ddr_port;
};

static DEFINE_MUTEX(ion_seccm_mutex);

static int seccm_sz2order(size_t size)
{
	int order = 0;
	size_t tmp_sz = size >> PAGE_SHIFT;

	for (order = 0; order < 64; order++){
		tmp_sz = tmp_sz >> 1;
		if (!tmp_sz){
			break;
		}
	}

	if (order == 64){
		return -1;
	}

	return order;
}

static struct page* seccm_dma_alloc_from_contiguous(struct device *dev, int count,
				       unsigned int align, int trynum)
{
	int i;
	struct page *page = NULL;

	for(i=0; i<trynum; i++){
		page = __dma_alloc_from_contiguous(dev,count,align);
		if (page){
			break;
		}
		mdelay(10);
	}

	return page;
}

static ion_phys_addr_t seccm_alloc(struct ion_heap *heap,
						      unsigned long size,
						      unsigned long align)
{
	unsigned long offset;
	struct ion_seccm_heap *seccm_heap =
		container_of(heap, struct ion_seccm_heap, heap);
	struct page* page = NULL;

	mutex_lock(&ion_seccm_mutex);
	if (seccm_heap->heap_status == CREAT){
		page = seccm_dma_alloc_from_contiguous(seccm_heap->dev,
					seccm_heap->size >> PAGE_SHIFT,
					seccm_heap->order,3);
		if (!page){
			pr_err("seccm_heap->alloc_func alloc failed\n");
			mutex_unlock(&ion_seccm_mutex);
			return ION_CARVEOUT_ALLOCATE_FAIL;
		}
		seccm_heap->base = page_to_phys(page);

		ion_flush_all_cpus_caches();
		create_mapping_late(seccm_heap->base,
				(unsigned long)phys_to_virt(seccm_heap->base),
				seccm_heap->size,__pgprot(PROT_DEVICE_nGnRE));

		seccm_heap->pool = gen_pool_create(12, -1);
		if (seccm_heap->pool == NULL) {
			return ION_CARVEOUT_ALLOCATE_FAIL;
		}
		(void)gen_pool_add(seccm_heap->pool, seccm_heap->base, seccm_heap->size, -1);
		seccm_heap->heap_status = ALLOC;
	}
	offset = gen_pool_alloc(seccm_heap->pool, size);
	mutex_unlock(&ion_seccm_mutex);
	if (!offset){
		pr_err("seccm_alloc size 0x%lx avail size 0x%lx\n",size,gen_pool_avail(seccm_heap->pool));
		return ION_CARVEOUT_ALLOCATE_FAIL;
	}
	return offset;
}

static void seccm_free(struct ion_heap *heap, ion_phys_addr_t addr,
		       unsigned long size)
{
	struct ion_seccm_heap *seccm_heap =
		container_of(heap, struct ion_seccm_heap, heap);

	if (addr == ION_CARVEOUT_ALLOCATE_FAIL)
		return;

	mutex_lock(&ion_seccm_mutex);
	gen_pool_free(seccm_heap->pool, addr, size);
	if (gen_pool_avail(seccm_heap->pool) == seccm_heap->size){
		if (seccm_heap->heap_status == ALLOC){
			create_mapping_late(seccm_heap->base,
					(unsigned long)phys_to_virt(seccm_heap->base),
					seccm_heap->size,__pgprot(PAGE_KERNEL));

			(void)dma_release_from_contiguous(seccm_heap->dev,
							phys_to_page(seccm_heap->base),
							seccm_heap->size>>PAGE_SHIFT);
			gen_pool_destroy(seccm_heap->pool);
			seccm_heap->pool = NULL;
			seccm_heap->heap_status = CREAT;
		}
	}

	mutex_unlock(&ion_seccm_mutex);

}

static int ion_seccm_heap_allocate(struct ion_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long size, unsigned long align,
				      unsigned long flags)
{
	struct sg_table *table;
	ion_phys_addr_t paddr;
	int ret;

	if (align > PAGE_SIZE)
		return -EINVAL;

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table)
		return -ENOMEM;
	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret)
		goto err_free;

	paddr = seccm_alloc(heap, size, align);
	if (paddr == ION_CARVEOUT_ALLOCATE_FAIL) {
		ret = -ENOMEM;
		goto err_free_table;
	}

	sg_set_page(table->sgl, pfn_to_page(PFN_DOWN(paddr)), size, 0);
	buffer->priv_virt = table;

	return 0;

err_free_table:
	sg_free_table(table);
err_free:
	kfree(table);
	return ret;
}

static void ion_seccm_heap_free(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	ion_phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));
	seccm_free(heap, paddr, buffer->size);
	sg_free_table(table);
	kfree(table);
}

static int ion_seccm_heap_phys(struct ion_heap *heap,
				  struct ion_buffer *buffer,
				  ion_phys_addr_t *addr, size_t *len)
{
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	ion_phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));

	*addr = paddr;
	*len = buffer->size;

	return 0;
}


static struct sg_table *ion_seccm_heap_map_dma(struct ion_heap *heap,
						  struct ion_buffer *buffer)
{
	return buffer->priv_virt;
}

static void ion_seccm_heap_unmap_dma(struct ion_heap *heap,
					struct ion_buffer *buffer)
{
	return;
}
/*
static void ion_seccm_heap_buffer_zero(struct ion_buffer *buffer)
{
	struct sg_table *table = buffer->priv_virt;
	ion_heap_buffer_zero(buffer);

	return;
}
*/
static struct ion_heap_ops seccm_heap_ops = {
	.allocate = ion_seccm_heap_allocate,
	.free = ion_seccm_heap_free,
	.phys = ion_seccm_heap_phys,
	.map_dma = ion_seccm_heap_map_dma,
	.unmap_dma = ion_seccm_heap_unmap_dma,
	.map_user = NULL,//ion_heap_map_user,
	.map_kernel = NULL,//ion_heap_map_kernel,
	.unmap_kernel = NULL,//ion_heap_unmap_kernel,
	.map_iommu = NULL,//ion_heap_map_iommu,
	.unmap_iommu = NULL,//ion_heap_unmap_iommu,
	.buffer_zero = NULL,//ion_seccm_heap_buffer_zero,
};

struct ion_heap *ion_seccm_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_seccm_heap *seccm_heap;

	seccm_heap = kzalloc(sizeof(*seccm_heap), GFP_KERNEL);
	if (!seccm_heap)
		return ERR_PTR(-ENOMEM);

	pr_err("heap_data->name is %s\n",heap_data->name);

	seccm_heap->dev = hisi_get_cma_device((char *)heap_data->name);
	seccm_heap->size = heap_data->size;

	seccm_heap->order = seccm_sz2order(heap_data->size);
	pr_err("seccm_heap->order is %d\n",seccm_heap->order);

	seccm_heap->heap.ops = &seccm_heap_ops;
	seccm_heap->heap.type = ION_HEAP_TYPE_SECCM;

	return &seccm_heap->heap;
}

void ion_seccm_heap_destroy(struct ion_heap *heap)
{
	struct ion_seccm_heap *seccm_heap =
	     container_of(heap, struct  ion_seccm_heap, heap);

	if (seccm_heap->heap_status == ALLOC){
		gen_pool_destroy(seccm_heap->pool);
		seccm_heap->pool = NULL;
	}

	kfree(seccm_heap);
}

