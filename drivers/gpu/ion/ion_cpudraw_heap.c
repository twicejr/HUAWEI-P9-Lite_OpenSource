/*
 * drivers/gpu/ion/ion_cpudraw_heap.c
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
#include <linux/spinlock.h>

#include <linux/err.h>
#include <linux/genalloc.h>
#include <linux/io.h>
#include <linux/ion.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include "ion_priv.h"

#include "hisi/hisi_cpudraw_alloc.h"

#include <linux/hisi/ion-iommu.h>

struct ion_cpudraw_heap {
	struct ion_heap heap;
	struct gen_pool *pool;
	ion_phys_addr_t base;
};

static void* packing_vaddr = 0;
static ion_phys_addr_t packing_paddr = 0;

static int ion_cpudraw_alloc_table(struct sg_table **table, int nents)
{
	struct sg_table * tb;
	struct scatterlist *sg;
	int ret;

	tb = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (NULL == tb)
		return -ENOMEM;

	sg = kzalloc(nents * sizeof(struct scatterlist), GFP_KERNEL);
	if (NULL == sg) {
		ret = -ENOMEM;
		goto err_free_tb;
	}

	sg_init_table(sg, nents);
	tb->nents = nents;
	tb->sgl = sg;

	*table = tb;

	return 0;

err_free_tb:
	kfree(tb);
	return ret;
}

static void ion_cpudraw_free_table(struct sg_table *table)
{
	kfree(table->sgl);
	table->sgl = NULL;
	kfree(table);
	return;
}

static ion_phys_addr_t ion_cpudraw_allocate(struct ion_heap *heap,
				      unsigned long size,
				      unsigned long align)
{
	struct ion_cpudraw_heap *cpudraw_heap =
		container_of(heap, struct ion_cpudraw_heap, heap);
	unsigned int byte_w = align & 0xffff ;
	unsigned int byte_h = (align >> 16) & 0xffff ;
	unsigned long offset = cpubuffer_alloc(cpudraw_heap->pool, size, byte_w, byte_h);
	//memlist_dump();

	if (!offset)
		return ION_CARVEOUT_ALLOCATE_FAIL;

	return offset;
}

static void ion_cpudraw_free(struct ion_heap *heap, ion_phys_addr_t addr,
		       unsigned long size)
{
	struct ion_cpudraw_heap *cpudraw_heap =
		container_of(heap, struct ion_cpudraw_heap, heap);

	if (addr == ION_CARVEOUT_ALLOCATE_FAIL)
		return;
	cpubuffer_free(cpudraw_heap->pool, addr);
	//memlist_dump();
}

static int ion_cpudraw_heap_phys(struct ion_heap *heap,
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

static int ion_cpudraw_heap_allocate(struct ion_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long size, unsigned long align,
				      unsigned long flags)
{
#define CPU_DRAW_STRIDE (SZ_16K)
	struct sg_table *table;
	struct sg_table *cpudraw_table = NULL;
	struct scatterlist *sg;
	struct scatterlist *cpudraw_sg;
	ion_phys_addr_t paddr;
	int ret;
	unsigned int byte_w;
	unsigned int h;
	unsigned int packing_len;
	int table_nents;
	int i;

	byte_w = align & 0xffff;
	h = (align >> 16) & 0xffff;

	if (byte_w % SZ_4K != 0 || byte_w > SZ_16K) {
		return -EINVAL;
	}

	//real buffer size
	buffer->cpu_buffer_size = byte_w * h;

	/*calc packing len*/
	packing_len = CPU_DRAW_STRIDE - byte_w;

	/*
	* if no need to packing, sglist count is the same as height
	* if need, packing sglist count is also the same as height, so total will be double
	*/
	table_nents = packing_len ? (h * 2) : h;

	ret = ion_cpudraw_alloc_table(&table, table_nents);
	if (ret != 0) {
		return -ENOMEM;
	}

	if (packing_len != 0) {
		/*need store real memory to flush cache & clear buffer*/
		ret = ion_cpudraw_alloc_table(&cpudraw_table, h);
		if (ret != 0) {
			ret = -ENOMEM;
			goto err_free_table;
		}
	}

	//alloc cpudraw buffer
	paddr = ion_cpudraw_allocate(heap, size, align);
	if (paddr == ION_CARVEOUT_ALLOCATE_FAIL) {
		ret = -ENOMEM;
		goto err_free_cpudraw_table;
	}

	sg = table->sgl;
	if (NULL == cpudraw_table) {		
		return -EINVAL;
	}
	
	cpudraw_sg = packing_len ? cpudraw_table->sgl : NULL;
	if (NULL == cpudraw_sg) 
		return -EINVAL;
	
	for (i = 0; i < h; i++) {
		//byte_w is 4K aligned, so it's ok here
		sg_set_page(sg, pfn_to_page(PFN_DOWN(paddr)), byte_w, 0);
		sg = sg_next(sg);

		if (packing_len != 0) {
			//fill packing memory sglist & real Cpu draw memory sglist
			sg_set_page(cpudraw_sg, pfn_to_page(PFN_DOWN(paddr)), byte_w, 0);
			sg_dma_address(cpudraw_sg) = sg_phys(cpudraw_sg);
			cpudraw_sg = sg_next(cpudraw_sg);
			sg_set_page(sg, pfn_to_page(PFN_DOWN(packing_paddr)), packing_len, 0);
			//dma address will be set later in ion_buffer_create
			sg = sg_next(sg);
		}
		/*stride is 16k , move to the next line*/
		paddr += CPU_DRAW_STRIDE;
	}

	buffer->priv_virt = table;
	buffer->cpudraw_sg_table = cpudraw_table;
	return 0;
err_free_cpudraw_table:
	ion_cpudraw_free_table(cpudraw_table);
err_free_table:
	ion_cpudraw_free_table(table);
	return ret;
}

static void ion_cpudraw_heap_free(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	ion_phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));
//zero buffer when allocation
#if 0
	/*only zero valid part*/
	ion_heap_cpudraw_buffer_zero(buffer);

	if (ion_buffer_cached(buffer))
		dma_sync_sg_for_device(NULL, buffer->cpudraw_sg_table->sgl, buffer->cpudraw_sg_table->nents,
							DMA_BIDIRECTIONAL);
#endif
	ion_cpudraw_free(heap, paddr, buffer->size);

	ion_cpudraw_free_table(table);
	if (NULL != buffer->cpudraw_sg_table)
		ion_cpudraw_free_table(buffer->cpudraw_sg_table);

	buffer->priv_virt = NULL;
	buffer->cpudraw_sg_table = NULL;
}

static struct sg_table *ion_cpudraw_heap_map_dma(struct ion_heap *heap,
					      struct ion_buffer *buffer)
{
	return buffer->priv_virt;
}

static void ion_cpudraw_heap_unmap_dma(struct ion_heap *heap,
				 struct ion_buffer *buffer)
{
	return;
}

static void ion_cpudraw_heap_buffer_zero(struct ion_buffer *buffer)
{
	struct sg_table *table = NULL;
	ion_heap_cpudraw_buffer_zero(buffer);

	table = buffer->cpudraw_sg_table ? buffer->cpudraw_sg_table : buffer->priv_virt;

	if (ion_buffer_cached(buffer))
		dma_sync_sg_for_device(NULL, table->sgl, table->nents,
							DMA_BIDIRECTIONAL);

	return;
}

int ion_cpudraw_heap_map_user(struct ion_heap *heap, struct ion_buffer *buffer,
			       struct vm_area_struct *vma)
{
	return remap_pfn_range(vma, vma->vm_start,
			       __phys_to_pfn(buffer->priv_phys) + vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}

static int ion_cpudraw_heap_map_iommu(struct ion_buffer *buffer,
			struct ion_iommu_map *map_data)
{
	struct sg_table *table = buffer->sg_table;
	return hisi_iommu_map_domain(table->sgl, &map_data->format);
}

static void ion_cpudraw_heap_unmap_iommu(struct ion_iommu_map *map_data)
{
	int ret = 0;

	ret = hisi_iommu_unmap_domain(&map_data->format);
	if (ret) {
		WARN(1, "[%s]hisi_iommu_unmap_domain failed!\n", __func__);
	}
}

static struct ion_heap_ops cpudraw_heap_ops = {
	.allocate = ion_cpudraw_heap_allocate,
	.free = ion_cpudraw_heap_free,
	.phys = ion_cpudraw_heap_phys,
	.map_dma = ion_cpudraw_heap_map_dma,
	.unmap_dma = ion_cpudraw_heap_unmap_dma,
	.map_user = ion_cpudraw_heap_map_user,
	.map_kernel = ion_cpudraw_heap_map_kernel,
	.unmap_kernel = ion_cpudraw_heap_unmap_kernel,
	.map_iommu = ion_cpudraw_heap_map_iommu,
	.unmap_iommu = ion_cpudraw_heap_unmap_iommu,
};

struct ion_heap *ion_cpudraw_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_cpudraw_heap *cpudraw_heap;

	int ret;

	struct page *page;
	size_t size;

	page = pfn_to_page(PFN_DOWN(heap_data->base));
	size = heap_data->size;

	ion_pages_sync_for_device(NULL, page, size, DMA_BIDIRECTIONAL);

	ret = ion_heap_pages_zero(page, size, pgprot_writecombine(PAGE_KERNEL));
	if (ret)
		return ERR_PTR(ret);

	cpudraw_heap = kzalloc(sizeof(struct ion_cpudraw_heap), GFP_KERNEL);
	if (!cpudraw_heap)
		return ERR_PTR(-ENOMEM);

	packing_vaddr = kzalloc(SZ_16K, GFP_KERNEL);
	if (!packing_vaddr) {
		kfree(cpudraw_heap);
		return ERR_PTR(-ENOMEM);
	}

	packing_paddr = virt_to_phys(packing_vaddr);

	memlist_init();
	cpudraw_heap->pool = gen_pool_create(12, -1);
	if (!cpudraw_heap->pool) {
		kfree(cpudraw_heap);
		return ERR_PTR(-ENOMEM);
	}
	cpudraw_heap->base = heap_data->base;
	gen_pool_add(cpudraw_heap->pool, cpudraw_heap->base, heap_data->size,
		     -1);
	cpudraw_heap->heap.ops = &cpudraw_heap_ops;
	cpudraw_heap->heap.type = ION_HEAP_TYPE_CPUDRAW;

	return &cpudraw_heap->heap;
}

void ion_cpudraw_heap_destroy(struct ion_heap *heap)
{
	struct ion_cpudraw_heap *cpudraw_heap =
	     container_of(heap, struct  ion_cpudraw_heap, heap);

	kfree(packing_vaddr);

	gen_pool_destroy(cpudraw_heap->pool);
	kfree(cpudraw_heap);
	cpudraw_heap = NULL;
}
