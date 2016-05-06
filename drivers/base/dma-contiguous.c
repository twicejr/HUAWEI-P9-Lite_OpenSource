/*
 * Contiguous Memory Allocator for DMA mapping framework
 * Copyright (c) 2010-2011 by Samsung Electronics.
 * Written by:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *	Michal Nazarewicz <mina86@mina86.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License or (at your optional) any later version of the license.
 */

#define pr_fmt(fmt) "cma: " fmt

#ifdef CONFIG_CMA_DEBUG
#ifndef DEBUG
#  define DEBUG
#endif
#endif

#include <asm/page.h>
#include <asm/dma-contiguous.h>

#include <linux/memblock.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/mutex.h>
#include <linux/page-isolation.h>
#include <linux/sizes.h>
#include <linux/slab.h>
#include <linux/swap.h>
#include <linux/mm_types.h>
#include <linux/dma-contiguous.h>

#if (defined(CONFIG_OF) && defined(CONFIG_HISI_CMA_RESERVE_MEMORY))
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/kernel.h>
static  int __init cma_reserve_mem_fdt_scan(unsigned long node, const char *uname,int depth, void *data);
static void __init hisi_cma_dev_init(void);
#else
static void __init hisi_cma_dev_init(void){}
#endif

struct cma {
	unsigned long	base_pfn;
	unsigned long	count;
	unsigned long	*bitmap;
};

struct hisi_cma {
	struct device *dev;
	char *name;
	struct cma *cma_area;
	int sec_prot;
	int dynamic;
};

struct cma *dma_contiguous_default_area;

#ifdef CONFIG_CMA_SIZE_MBYTES
#define CMA_SIZE_MBYTES CONFIG_CMA_SIZE_MBYTES
#else
#define CMA_SIZE_MBYTES 0
#endif

/*
 * Default global CMA area size can be defined in kernel's .config.
 * This is usefull mainly for distro maintainers to create a kernel
 * that works correctly for most supported systems.
 * The size can be set in bytes or as a percentage of the total memory
 * in the system.
 *
 * Users, who want to set the size of global CMA area for their system
 * should use cma= kernel parameter.
 */
static const phys_addr_t size_bytes = CMA_SIZE_MBYTES * SZ_1M;
static phys_addr_t size_cmdline = -1;

static int __init early_cma(char *p)
{
	pr_debug("%s(%s)\n", __func__, p);
	size_cmdline = memparse(p, &p);
	return 0;
}
early_param("cma", early_cma);

#ifdef CONFIG_CMA_SIZE_PERCENTAGE

static phys_addr_t __init __maybe_unused cma_early_percent_memory(void)
{
	struct memblock_region *reg;
	unsigned long total_pages = 0;

	/*
	 * We cannot use memblock_phys_mem_size() here, because
	 * memblock_analyze() has not been called yet.
	 */
	for_each_memblock(memory, reg)
		total_pages += memblock_region_memory_end_pfn(reg) -
			       memblock_region_memory_base_pfn(reg);

	return (total_pages * CONFIG_CMA_SIZE_PERCENTAGE / 100) << PAGE_SHIFT;
}

#else

static inline __maybe_unused phys_addr_t cma_early_percent_memory(void)
{
	return 0;
}

#endif

/**
 * dma_contiguous_reserve() - reserve area(s) for contiguous memory handling
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory.
 */
void __init dma_contiguous_reserve(phys_addr_t limit)
{
	phys_addr_t selected_size = 0;

	pr_debug("%s(limit %08lx)\n", __func__, (unsigned long)limit);

	if (size_cmdline != -1) {
		selected_size = size_cmdline;
	} else {
#ifdef CONFIG_CMA_SIZE_SEL_MBYTES
		selected_size = size_bytes;
#elif defined(CONFIG_CMA_SIZE_SEL_PERCENTAGE)
		selected_size = cma_early_percent_memory();
#elif defined(CONFIG_CMA_SIZE_SEL_MIN)
		selected_size = min(size_bytes, cma_early_percent_memory());
#elif defined(CONFIG_CMA_SIZE_SEL_MAX)
		selected_size = max(size_bytes, cma_early_percent_memory());
#endif
	}

	if (selected_size && !dma_contiguous_default_area) {
		pr_debug("%s: reserving %ld MiB for global area\n", __func__,
			 (unsigned long)selected_size / SZ_1M);

		dma_contiguous_reserve_area(selected_size, 0, limit,
					    &dma_contiguous_default_area);
	}

#if (defined(CONFIG_OF) && defined(CONFIG_HISI_CMA_RESERVE_MEMORY))
	of_scan_flat_dt(cma_reserve_mem_fdt_scan, NULL);
#endif
};

static DEFINE_MUTEX(cma_mutex);

static int __init cma_activate_area(struct cma *cma)
{
	int bitmap_size = BITS_TO_LONGS(cma->count) * sizeof(long);
	unsigned long base_pfn = cma->base_pfn, pfn = base_pfn;
	unsigned i = cma->count >> pageblock_order;
	struct zone *zone;

	cma->bitmap = kzalloc(bitmap_size, GFP_KERNEL);

	if (!cma->bitmap)
		return -ENOMEM;

	WARN_ON_ONCE(!pfn_valid(pfn));
	zone = page_zone(pfn_to_page(pfn));

	do {
		unsigned j;
		base_pfn = pfn;
		for (j = pageblock_nr_pages; j; --j, pfn++) {
			WARN_ON_ONCE(!pfn_valid(pfn));
			if (page_zone(pfn_to_page(pfn)) != zone)
				return -EINVAL;
		}
		init_cma_reserved_pageblock(pfn_to_page(base_pfn));
	} while (--i);

	return 0;
}

static struct cma cma_areas[MAX_CMA_AREAS];
static unsigned cma_area_count;
static struct hisi_cma hisi_cma_areas[MAX_CMA_AREAS];
static unsigned hisi_cma_area_count;
struct device hisi_cma_dev[MAX_CMA_AREAS];

#if (defined(CONFIG_OF) && defined(CONFIG_HISI_CMA_RESERVE_MEMORY))
extern void create_mapping_late(phys_addr_t phys, unsigned long virt,
				  phys_addr_t size, pgprot_t prot);

static void __init hisi_cma_dev_init(void)
{
	struct cma *cma;
	struct page *page = NULL;
	int i;
#ifdef CONFIG_HISI_KERNELDUMP
	int k;
	struct page *tmp_page = NULL;
#endif

	for(i = 0 ; i < hisi_cma_area_count; i++){
		cma = hisi_cma_areas[i].cma_area;
		if (cma == NULL)
			continue;
		dev_set_cma_area(&hisi_cma_dev[i], cma);
		hisi_cma_areas[i].dev = &hisi_cma_dev[i];
		/* when is 0 mean it is static*/
		if (hisi_cma_areas[i].dynamic == 0){

			page = dma_alloc_from_contiguous(&hisi_cma_dev[i], cma->count, SZ_1M);

#ifdef CONFIG_HISI_KERNELDUMP
			if (page != NULL) {
				tmp_page = page;
				for (k=0;k < cma->count;k++){
					SetPageMemDump(tmp_page);
					tmp_page++;
				}
			}
#endif
			if (hisi_cma_areas[i].sec_prot){
				create_mapping_late(__pfn_to_phys(cma->base_pfn),
									__phys_to_virt(__pfn_to_phys(cma->base_pfn)),
									cma->count * PAGE_SIZE, __pgprot(PROT_DEVICE_nGnRE));
			}
			pr_err("%s:%d page addr 0x%llx size %lu\n", __func__,
					__LINE__, page_to_phys(page),(cma->count<<PAGE_SHIFT)/SZ_1M);
		}
	}
}

struct device *hisi_get_cma_device(char *name)
{
        int i;
        for(i = 0 ; i < hisi_cma_area_count; i++){

                if (!hisi_cma_areas[i].cma_area)
                        continue;
                if (!hisi_cma_areas[i].dynamic)
                        continue;
                if (!strcmp(hisi_cma_areas[i].name,name))
                        break;
        }

        if (hisi_cma_area_count == i)
                return NULL;

        return hisi_cma_areas[i].dev;
}

#endif

static int __init cma_init_reserved_areas(void)
{
	int i;

	for (i = 0; i < cma_area_count; i++) {
		int ret = cma_activate_area(&cma_areas[i]);
		if (ret)
			return ret;
		pr_err("cma base %llx  cma size %lu\n",
				__pfn_to_phys(cma_areas[i].base_pfn),
				(cma_areas[i].count<<PAGE_SHIFT)/SZ_1M);
	}

	hisi_cma_dev_init();

	return 0;
}
core_initcall(cma_init_reserved_areas);

/**
 * dma_contiguous_reserve_area() - reserve custom contiguous area
 * @size: Size of the reserved area (in bytes),
 * @base: Base address of the reserved area optional, use 0 for any
 * @limit: End address of the reserved memory (optional, 0 for any).
 * @res_cma: Pointer to store the created cma region.
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory. This function allows to create custom reserved areas for specific
 * devices.
 */
#if (defined(CONFIG_OF) && defined(CONFIG_HISI_CMA_RESERVE_MEMORY))

int __init __dma_contiguous_reserve_area(phys_addr_t size, phys_addr_t base,
				       phys_addr_t limit, char *name, struct cma **res_cma,int prot,int is_dynamic)
{
	struct cma *cma = &cma_areas[cma_area_count];
	struct hisi_cma *hisi_cma = &hisi_cma_areas[hisi_cma_area_count];

	phys_addr_t alignment;

	/* Sanity checks */
	if (cma_area_count == ARRAY_SIZE(cma_areas)) {
		pr_err("Not enough slots for CMA reserved regions!\n");
		return -ENOSPC;
	}

	if (!size)
		return -EINVAL;

	/**
	 * Sanitise input arguments
	 * CMA area base must 4M align
	 * CMA area size must 4M align
	 */
	alignment = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);
	WARN_ON_ONCE(base != ALIGN(base, alignment));
	WARN_ON_ONCE(size != ALIGN(size, alignment));

	cma->base_pfn = PFN_DOWN(base);
	cma->count = size >> PAGE_SHIFT;
	cma_area_count++;

	hisi_cma->sec_prot = prot;
	hisi_cma->name = name;
	hisi_cma->cma_area = cma;
	hisi_cma->dynamic = is_dynamic;
	hisi_cma_area_count++;

	pr_info("CMA: reserved %ld MiB at %08lx\n", (unsigned long)size / SZ_1M,
		(unsigned long)base);

	return 0;
}

int __init cma_reserve_mem_fdt_scan(unsigned long node, const char *uname,
				int depth, void *data)
{
	static int found;
	phys_addr_t base, size;
	int len;
	int sec_prot = 0;
	int dynamic_prot = 0;
	const __be32 *prop;
	unsigned long size_cells = dt_root_size_cells;
	unsigned long addr_cells = dt_root_addr_cells;
	char *status;
	char *cma_name = NULL;
	if (!found && depth == 1 && strcmp(uname, "reserved-memory") == 0) {
		prop = of_get_flat_dt_prop(node, "#size-cells", NULL);
		if (prop)
			size_cells = be32_to_cpup(prop);

		prop = of_get_flat_dt_prop(node, "#address-cells", NULL);
		if (prop)
			addr_cells = be32_to_cpup(prop);

		found = 1;
		/* scan next node */
		return 0;
	} else if (!found) {
		/* scan next node */
		return 0;
	} else if (found && depth < 2) {
		/* scanning of /reserved-memory has been finished */
		return 1;
	}

	status = (char *)of_get_flat_dt_prop(node, "status", NULL);
	/*
	 * Yes, we actually want strncmp here to check for a prefix
	 * ok vs. okay
	 */
	if (status && (strncmp(status, "ok", 2) != 0))
		return 0;

	if (!of_get_flat_dt_prop(node, "hisi,cma-mem", NULL))
		return 0;

	if (of_get_flat_dt_prop(node, "hisi,sec-mem", NULL))
		sec_prot = 1;

	if (of_get_flat_dt_prop(node, "hisi,cma-dynamic", NULL))
		dynamic_prot = 1;

	prop = (const __be32 *)of_get_flat_dt_prop(node, "reg", &len);
	if (!prop&&(depth != 2))
		return 0;

	cma_name =  (char *)of_get_flat_dt_prop(node, "hisi,cma-name", NULL);

	base = (phys_addr_t)dt_mem_next_cell(addr_cells, &prop);
	size = (phys_addr_t)dt_mem_next_cell(size_cells, &prop);

	pr_err("size is %lu base 0x%lu cma_name %s\n",
			(unsigned long)size / SZ_1M, (unsigned long)base, cma_name);
	__dma_contiguous_reserve_area(size, base, SZ_4M, cma_name, NULL,sec_prot,dynamic_prot);

	return 0;
}
#endif

int __init dma_contiguous_reserve_area(phys_addr_t size, phys_addr_t base,
				       phys_addr_t limit, struct cma **res_cma)
{
	struct cma *cma = &cma_areas[cma_area_count];
	phys_addr_t alignment;
	int ret = 0;

	pr_debug("%s(size %lx, base %08lx, limit %08lx)\n", __func__,
		 (unsigned long)size, (unsigned long)base,
		 (unsigned long)limit);

	/* Sanity checks */
	if (cma_area_count == ARRAY_SIZE(cma_areas)) {
		pr_err("Not enough slots for CMA reserved regions!\n");
		return -ENOSPC;
	}

	if (!size)
		return -EINVAL;

	/* Sanitise input arguments */
	alignment = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);
	base = ALIGN(base, alignment);
	size = ALIGN(size, alignment);
	limit &= ~(alignment - 1);

	/* Reserve memory */
	if (base) {
		if (memblock_is_region_reserved(base, size) ||
		    memblock_reserve(base, size) < 0) {
			ret = -EBUSY;
			goto err;
		}
	} else {
		/*
		 * Use __memblock_alloc_base() since
		 * memblock_alloc_base() panic()s.
		 */
		phys_addr_t addr = __memblock_alloc_base(size, alignment, limit);
		if (!addr) {
			ret = -ENOMEM;
			goto err;
		} else {
			base = addr;
		}
	}

	/*
	 * Each reserved area must be initialised later, when more kernel
	 * subsystems (like slab allocator) are available.
	 */
	cma->base_pfn = PFN_DOWN(base);
	cma->count = size >> PAGE_SHIFT;
	*res_cma = cma;
	cma_area_count++;

	pr_err("CMA: reserved %ld MiB at %08lx\n", (unsigned long)size / SZ_1M,
		(unsigned long)base);

	/* Architecture specific contiguous memory fixup. */
	dma_contiguous_early_fixup(base, size);
	return 0;
err:
	return ret;
}

/**
 * dma_alloc_from_contiguous() - allocate pages from contiguous area
 * @dev:   Pointer to device for which the allocation is performed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 *
 * This function allocates memory buffer for specified device. It uses
 * device specific contiguous memory area if available or the default
 * global one. Requires architecture specific get_dev_cma_area() helper
 * function.
 */
struct page *dma_alloc_from_contiguous(struct device *dev, int count,
				       unsigned int align)
{
	unsigned long mask, pfn, pageno, start = 0;
	struct cma *cma = dev_get_cma_area(dev);
	struct page *page = NULL;
	int ret;

	if (!cma || !cma->count)
		return NULL;

	if (align > CONFIG_CMA_ALIGNMENT)
		align = CONFIG_CMA_ALIGNMENT;

	if (!count)
		return NULL;

	mask = (1 << align) - 1;

	mutex_lock(&cma_mutex);

	for (;;) {
		pageno = bitmap_find_next_zero_area(cma->bitmap, cma->count,
						    start, count, mask);
		if (pageno >= cma->count)
			break;

		pfn = cma->base_pfn + pageno;
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA);
		if (ret == 0) {
			bitmap_set(cma->bitmap, pageno, count);
			page = pfn_to_page(pfn);
			break;
		} else if (ret != -EBUSY) {
			break;
		}
		/* try again with a bit different memory target */
		start = pageno + mask + 1;
	}

	mutex_unlock(&cma_mutex);
	return page;
}

struct page *__dma_alloc_from_contiguous(struct device *dev, int count,
				       unsigned int align)
{
	unsigned long mask, pfn, pageno, start = 0;
	struct cma *cma = dev_get_cma_area(dev);
	struct page *page = NULL;
	int ret;

	if (!cma || !cma->count)
		return NULL;

	if (!count)
		return NULL;

	mask = (1 << align) - 1;

	mutex_lock(&cma_mutex);

	for (;;) {
		pageno = bitmap_find_next_zero_area(cma->bitmap, cma->count,
						    start, count, mask);
		if (pageno >= cma->count)
			break;

		pfn = cma->base_pfn + pageno;
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA);
		if (ret == 0) {
			bitmap_set(cma->bitmap, pageno, count);
			page = pfn_to_page(pfn);
			break;
		} else if (ret != -EBUSY) {
			break;
		}
		/* try again with a bit different memory target */
		start = pageno + mask + 1;
	}

	mutex_unlock(&cma_mutex);
	return page;
}
/**
 * dma_release_from_contiguous() - release allocated pages
 * @dev:   Pointer to device for which the pages were allocated.
 * @pages: Allocated pages.
 * @count: Number of allocated pages.
 *
 * This function releases memory allocated by dma_alloc_from_contiguous().
 * It returns false when provided pages do not belong to contiguous area and
 * true otherwise.
 */
bool dma_release_from_contiguous(struct device *dev, struct page *pages,
				 int count)
{
	struct cma *cma = dev_get_cma_area(dev);
	unsigned long pfn;

	if (!cma || !pages){
		pr_err("cma is null\n");
		return false;
	}

	pfn = page_to_pfn(pages);

	if (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count){
		pr_err("pfn:%lx cma->base_pfn:%lx cma->count:%lx\n",
				pfn, cma->base_pfn, cma->count);
		return false;
	}

	VM_BUG_ON(pfn + count > cma->base_pfn + cma->count);

	mutex_lock(&cma_mutex);
	bitmap_clear(cma->bitmap, pfn - cma->base_pfn, count);
	free_contig_range(pfn, count);
	mutex_unlock(&cma_mutex);

	return true;
}

#ifdef CONFIG_DEBUG_PAGEALLOC
bool is_cma_area(struct page *page)
{
	int i;
	phys_addr_t start;
	phys_addr_t cma_start;
	phys_addr_t cma_end;

	start = page_to_phys(page);
	
	for (i = 0; i < cma_area_count; i++) {
		cma_start = __pfn_to_phys(cma_areas[i].base_pfn);
		cma_end = cma_start + cma_areas[i].count<<PAGE_SHIFT;

		if (start >= cma_start && start <= cma_end) {
			//pr_err("is_cma_area %lx \n", start);
			return true;
		}
	}

	return false;
}
#endif

