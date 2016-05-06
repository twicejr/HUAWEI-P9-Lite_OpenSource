#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/ion-iommu.h>
#include <linux/genalloc.h>
#include <linux/err.h>
#include <linux/dma-mapping.h>
#include <linux/list.h>

#include "ion_priv.h"

#ifndef DEBUG
#define D(format, arg...)
#else
#define D(format, arg...) pr_err("[%s]"format, __func__, ##arg)
#endif

#define MAX_CMA_POOL_SIZE (4 * 1024 * 1024)
#define CMA_POOL_ALLOC_ALIGN (4 * 1024)

struct ion_cma_pool_heap {
	struct ion_heap heap;
	struct list_head pools_list;
	struct mutex lock;
};

#define to_cma_pool_heap(x) container_of(x, struct ion_cma_pool_heap, heap)

struct ion_cma_pool {
	struct gen_pool *pool;
	struct ion_cma_pool_heap *heap;
	struct list_head list_node;
	struct list_head buffers_list;
};

struct ion_cma_buffer {
	struct ion_buffer *buffer;
	struct ion_cma_pool *cma_pool;
	struct list_head list_node;
	void *virt_addr;
	dma_addr_t dma_addr;
	unsigned int len;
};

static void *cma_heap_alloc_chunk(struct ion_cma_pool *cma_pool, size_t size,
		dma_addr_t *dma_addr)
{
	void *addr = NULL;

	addr = dma_alloc_coherent(NULL, size, dma_addr, GFP_KERNEL);
	if (!addr) {
		printk(KERN_ERR "[%s]dma_alloc_coherent failed!\n", __func__);
	}

	pr_debug("[%s]addr: %p, size: 0x%lx, dma_addr: %p\n", __func__,
		addr, (unsigned long)size, dma_addr);

	return addr;
}

static void cma_heap_free_chunk(struct ion_cma_pool *cma_pool, size_t size,
		void *addr, dma_addr_t dma_addr)
{
	pr_debug("[%s]addr: %p, size: 0x%lx, dma_addr: 0x%lx\n", __func__,
		addr, (unsigned long)size, (unsigned long)dma_addr);
	dma_free_coherent(NULL, size, addr, dma_addr);
}

static int cma_heap_add_chunk(struct ion_cma_pool *cma_pool)
{
	void *virt_addr = NULL;
	dma_addr_t dma_addr = 0;
	size_t chunk_size = MAX_CMA_POOL_SIZE;

	virt_addr = cma_heap_alloc_chunk(cma_pool, chunk_size, &dma_addr);
	if (!virt_addr) {
		return -ENOMEM;
	}

	gen_pool_add_virt(cma_pool->pool, (unsigned long)virt_addr,
			(phys_addr_t)dma_addr, chunk_size, -1);
	return 0;
}
static void __free_chunk(struct gen_pool *pool, struct gen_pool_chunk *chunk,
		void *data)
{
	struct ion_cma_pool *cma_pool = data;
	void *addr = (void *)chunk->start_addr; // type: unsigned long -> void *
	phys_addr_t phys_addr = chunk->phys_addr;
	size_t size = (chunk->end_addr - chunk->start_addr);

	D("+\n");

	if (size)
		cma_heap_free_chunk(cma_pool, size, addr, phys_addr);

	chunk->end_addr = chunk->start_addr = chunk->phys_addr = 0;

	D("-\n");
}
static void cma_heap_del_chunk(struct ion_cma_pool *cma_pool)
{
	struct gen_pool *pool = cma_pool->pool;
	struct gen_pool_chunk *chunk;
#if 0
	gen_pool_for_each_chunk(pool, __free_chunk, cma_pool);
#else
	/* because there is only one chunk for a gen_pool,
	   so we deal with first chunk only */
	chunk = list_first_entry(&pool->chunks,
			struct gen_pool_chunk, next_chunk);
	__free_chunk(pool, chunk, cma_pool);
#endif
}

static struct ion_cma_pool *cma_heap_create_pool(void)
{
	struct gen_pool *pool;
	struct ion_cma_pool *cma_pool;

	cma_pool = kzalloc(sizeof(*cma_pool), GFP_KERNEL);
	if (!cma_pool) {
		pr_err("[%s]allocate cma pool failed!\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	/* create cma pool */
	pool = gen_pool_create(order_base_2(CMA_POOL_ALLOC_ALIGN), -1);
	if (!pool) {
		pr_err("[%s]gen_pool_create failed!\n", __func__);
		kfree(cma_pool);
		return ERR_PTR(-ENOMEM);
	}

	gen_pool_set_algo(pool, gen_pool_best_fit, NULL);

	cma_pool->pool = pool;

	INIT_LIST_HEAD(&cma_pool->buffers_list);
	INIT_LIST_HEAD(&cma_pool->list_node);

	return cma_pool;
}
static void cma_heap_destory_pool(struct ion_cma_pool *cma_pool)
{
	gen_pool_destroy(cma_pool->pool);
	kfree(cma_pool);
}

static int add_cma_pool(struct ion_cma_pool_heap *cma_heap)
{
	int ret = 0;
	struct ion_cma_pool *cma_pool;
	D("+\n");

	cma_pool = cma_heap_create_pool();
	if (IS_ERR_OR_NULL(cma_pool)) {
		pr_err("[%s]failed to create cma pool\n", __func__);
		ret = PTR_ERR(cma_pool);
		return ret;
	}

	/* allocate memory */
	ret = cma_heap_add_chunk(cma_pool);
	if (ret) {
		pr_err("cma_heap_add_chunk failed!\n");
		cma_heap_destory_pool(cma_pool);
		return ret;
	}

	/* attatch pool to heap */
	list_add(&cma_pool->list_node, &cma_heap->pools_list);
	cma_pool->heap = cma_heap;
	D("cma_pool: %p\n", cma_pool);
	D("-\n");
	return 0;
}

static void del_cma_pool(struct ion_cma_pool_heap *cma_heap)
{
	struct ion_cma_pool *cma_pool;

	D("+\n");

	if (list_empty(&cma_heap->pools_list)) {
		WARN(1, "should at least one pool!\n");
		return;
	}

	/* free the last node */
	cma_pool = list_entry(cma_heap->pools_list.prev, struct ion_cma_pool,
			list_node);

	/* free pool only when no buffer */
	if (list_empty(&cma_pool->buffers_list)) {
		list_del_init(&cma_pool->list_node);
		cma_heap_del_chunk(cma_pool);
		cma_heap_destory_pool(cma_pool);
		cma_pool = NULL;
	}
	D("-\n");
}

static struct ion_cma_pool *find_cma_pool(struct ion_cma_pool_heap *cma_heap)
{
	struct ion_cma_pool *pool;

	if (list_empty(&cma_heap->pools_list)) {
		D("no pool yet!\n");
		return NULL;
	}

	pool = list_first_entry(&cma_heap->pools_list, struct ion_cma_pool,
		list_node);

	D("find pool: %p\n", pool);

	return pool;
}

/**
 * allocate a buffer from pool, return vitr addr, output phys addr by phys_addr
 */
static unsigned long cma_pool_alloc(struct ion_cma_pool *cma_pool, size_t size,
		unsigned long align, phys_addr_t *phys_addr)
{
	struct gen_pool *pool;
	unsigned long addr;
	D("+\n");

	if (!cma_pool) {
		WARN(1, "No CMA pool!\n");
		return 0;
	}

	pool = cma_pool->pool;

	if (align > (1 << pool->min_alloc_order)) {
		WARN(1, "CMA pool can not align to 0x%lx\n", align);
		return 0;
	}

	addr = gen_pool_alloc(pool, size);
	if (!addr) {
		WARN(1, "gen_pool_alloc failed!\n");
		return 0;

	}

	*phys_addr = gen_pool_virt_to_phys(pool, addr);

	D("addr: 0x%x, phys: 0x%x\n", addr, *phys_addr);

	D("-\n");
	return addr;
}

static void cma_pool_free(struct ion_cma_pool *cma_pool, unsigned long addr,
	size_t size)
{
	gen_pool_free(cma_pool->pool, addr, size);
}

static struct sg_table *bind_to_sgtabl(struct ion_cma_buffer *buffer_info)
{
	struct sg_table *table;

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table) {
		pr_err("[%s]alloc table failed!\n", __func__);
		return NULL;
	}

	if (sg_alloc_table(table, 1, GFP_KERNEL)) {
		pr_err("[%s]sg_alloc_table failed!\n", __func__);
		kfree(table);
		return NULL;
	}

	sg_set_buf(table->sgl, buffer_info->virt_addr, buffer_info->len);

	return table;
}

static struct sg_table *bind_to_sgtable_per_page(struct ion_cma_buffer *buf)
{
	struct sg_table *table;
	struct scatterlist *sg;
	struct page *page;
	unsigned int sg_nents = (PAGE_ALIGN(buf->len) / PAGE_SIZE);
	unsigned int i;

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table) {
		pr_err("[%s]alloc table failed!\n", __func__);
		return NULL;
	}

	D("sg_nents: %d, table: %p\n", sg_nents, table);

	if (sg_alloc_table(table, sg_nents, GFP_KERNEL)) {
		kfree(table);
		pr_err("[%s]sg_alloc_table failed!\n", __func__);
		return NULL;
	}

	for_each_sg(table->sgl, sg, table->nents, i) {
		page = virt_to_page(buf->virt_addr + (i * PAGE_SIZE));
		sg_set_page(sg, page, PAGE_SIZE, 0);
	}

	return table;
}

static int ion_cma_pool_heap_allocate(struct ion_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long len,
				      unsigned long align,
				      unsigned long flags)
{
	int ret = 0;
	void *virt_addr;
	dma_addr_t dma_addr;
	struct sg_table *table = NULL;
	struct ion_cma_pool_heap *cma_heap = to_cma_pool_heap(heap);
	struct ion_cma_pool *cma_pool = NULL;
	struct ion_cma_buffer *cma_buffer = NULL;

	D("+\n");

	if (!IS_ALIGNED(len, PAGE_SIZE)) {
		pr_err("[%s]Support only size aligned to PAGE_SIZE", __func__);
		return -EINVAL;
	}

	if (len > MAX_CMA_POOL_SIZE) {
		pr_err("[%s]len should less then 4M\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&cma_heap->lock);

	/* create buffer info */
	cma_buffer = kzalloc(sizeof(*cma_buffer), GFP_KERNEL);
	if (!cma_buffer) {
		ret = -ENOMEM;
		goto error;
	}

	/* get a pool */
	cma_pool = find_cma_pool(cma_heap);
	if (!cma_pool) {
		ret = add_cma_pool(cma_heap);
		if (!ret) {
			cma_pool = find_cma_pool(cma_heap);
		} else {
			pr_err("ion_cam_pool_heap: add_cma_pool failed!\n");
			ret = -ENOMEM;
			goto error;
		}
	}

	/* allocate buffer from pool */
	virt_addr = (void *)cma_pool_alloc(cma_pool, len, align, &dma_addr);
	if (0 == virt_addr) {
		D("alloc buffer failed, create a new pool!\n");

		ret = add_cma_pool(cma_heap);
		if(!ret) {
			cma_pool = find_cma_pool(cma_heap);
		} else {
			pr_err("ion_cam_pool_heap: add_cma_pool failed!\n");
			ret = -ENOMEM;
			goto error;
		}

		virt_addr = (void *)cma_pool_alloc(cma_pool, len, align, &dma_addr);
		if (0 == virt_addr) {
			pr_err("alloc buffer failed again!\n");
			ret = -ENOMEM;
			goto error;
		}
	}

	D("alloc buffer form pool: virt_addr: %p, dma_addr: 0x%x, len: 0x%lx\n",
			virt_addr, dma_addr, len);

	cma_buffer->buffer = buffer;
	cma_buffer->virt_addr = virt_addr;
	cma_buffer->dma_addr = dma_addr;
	cma_buffer->len = len;
	cma_buffer->cma_pool = cma_pool;
	list_add(&cma_buffer->list_node, &cma_pool->buffers_list);

	buffer->priv_virt = cma_buffer;

	if (ion_buffer_fault_user_mappings(buffer)) {
		table = bind_to_sgtable_per_page(cma_buffer);
	} else {
		table = bind_to_sgtabl(cma_buffer);
	}
	if (!table) {
		ret = -ENOMEM;
		goto error;
	} else {
		buffer->sg_table = table;
	}

	mutex_unlock(&cma_heap->lock);

	D("-\n");
	return 0;

error:
	D("failed!\n");
	if (table)
		kfree(table);

	if (cma_buffer)
		kfree(cma_buffer);

	mutex_unlock(&cma_heap->lock);

	return ret;
}

static void ion_cma_pool_heap_free(struct ion_buffer *buffer)
{
	struct ion_cma_buffer *cma_buffer = buffer->priv_virt;
	struct ion_cma_pool *cma_pool = cma_buffer->cma_pool;
	struct ion_cma_pool_heap *cma_heap = cma_pool->heap;
	D("+\n");

	mutex_lock(&cma_heap->lock);
#ifdef DEBUG
	WARN_ON(list_empty(&cma_buffer->list_node));
#endif
	/* free the buffer */
	list_del_init(&cma_buffer->list_node);
	cma_pool_free(cma_pool, (unsigned long)cma_buffer->virt_addr, cma_buffer->len);
	kfree(cma_buffer);
	buffer->priv_virt = NULL;

	/* unmap dma */
	sg_free_table(buffer->sg_table);
	kfree(buffer->sg_table);
	buffer->sg_table = NULL;

	/* delete pool */
	del_cma_pool(cma_heap);

	mutex_unlock(&cma_heap->lock);
	D("-\n");
}

static int ion_cma_pool_heap_phys(struct ion_heap *heap,
				  struct ion_buffer *buffer,
				  ion_phys_addr_t *addr, size_t *len)
{
	*addr = sg_phys(buffer->sg_table->sgl);
	*len = sg_dma_len(buffer->sg_table->sgl);
	return 0;
}

static struct sg_table *ion_cma_pool_heap_map_dma(struct ion_heap *heap,
					      struct ion_buffer *buffer)
{
	return buffer->sg_table;
}

static void ion_cma_pool_heap_unmap_dma(struct ion_heap *heap,
				 struct ion_buffer *buffer)
{
}

static int ion_cma_pool_heap_map_user(struct ion_heap *heap,
		struct ion_buffer *buffer, struct vm_area_struct *vma)
{
	struct ion_cma_buffer *buf = buffer->priv_virt;
	return dma_mmap_coherent(NULL, vma, buf->virt_addr, buf->dma_addr,
				 buffer->size);
}

static void *ion_cma_pool_heap_map_kernel(struct ion_heap *heap,
				   struct ion_buffer *buffer)
{
	struct ion_cma_buffer *cma_buffer;
	cma_buffer = buffer->priv_virt;
	return cma_buffer->virt_addr;
}

static void ion_cma_pool_heap_unmap_kernel(struct ion_heap *heap,
				    struct ion_buffer *buffer)
{
}


static int ion_cma_pool_heap_map_iommu(struct ion_buffer *buffer,
			struct ion_iommu_map *map_data)
{
	struct sg_table *table = buffer->sg_table;
	struct iommu_map_format *fmt = &map_data->format;
	int ret;

	pr_debug("is_tile: %ld, phys_page_line: 0x%lx, virt_page_line: 0x%lx\n",
		fmt->is_tile, fmt->phys_page_line, fmt->virt_page_line);

	ret = hisi_iommu_map_domain(table->sgl, &map_data->format);

	pr_debug("iova_start: 0x%lx, iova_size: 0x%lx, "
		"iommu_ptb_base: 0x%lx, iommu_iova_base: 0x%lx\n",
		fmt->iova_start, fmt->iova_size,
		fmt->iommu_ptb_base, fmt->iommu_iova_base);

	return ret;
}

static void ion_cma_pool_heap_unmap_iommu(struct ion_iommu_map *map_data)
{
	int ret = 0;

	pr_debug("iova_start: 0x%lx, iova_size: 0x%lx, "
		"iommu_ptb_base: 0x%lx, iommu_iova_base: 0x%lx\n",
		map_data->format.iova_start,
		map_data->format.iova_size,
		map_data->format.iommu_ptb_base,
		map_data->format.iommu_iova_base);

	ret = hisi_iommu_unmap_domain(&map_data->format);
	if (ret) {
		WARN(1, "[%s]hisi_iommu_unmap_domain failed!\n", __func__);
	}
}


static struct ion_heap_ops ion_cma_pool_heap_ops = {
	.allocate = ion_cma_pool_heap_allocate,
	.free = ion_cma_pool_heap_free,
	.phys = ion_cma_pool_heap_phys,
	.map_dma = ion_cma_pool_heap_map_dma,
	.unmap_dma = ion_cma_pool_heap_unmap_dma,
	.map_user = ion_cma_pool_heap_map_user,
	.map_kernel = ion_cma_pool_heap_map_kernel,
	.unmap_kernel = ion_cma_pool_heap_unmap_kernel,

	.map_iommu = ion_cma_pool_heap_map_iommu,
	.unmap_iommu = ion_cma_pool_heap_unmap_iommu,
};

struct ion_heap *ion_cma_pool_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_cma_pool_heap *cma_heap;
	D("+\n");

	cma_heap = kzalloc(sizeof(struct ion_cma_pool_heap), GFP_KERNEL);
	if (!cma_heap) {
		pr_err("[%s]create cma_heap failed!\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	cma_heap->heap.ops = &ion_cma_pool_heap_ops;
	cma_heap->heap.type = ION_HEAP_TYPE_DMA_POOL;

	INIT_LIST_HEAD(&cma_heap->pools_list);

	mutex_init(&cma_heap->lock);

	D("-\n");
	return &cma_heap->heap;
}

void ion_cma_pool_heap_destroy(struct ion_heap *heap)
{
	struct ion_cma_pool_heap *cma_heap = to_cma_pool_heap(heap);

	kfree(cma_heap);
}
