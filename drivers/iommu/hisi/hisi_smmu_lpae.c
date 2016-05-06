
/*
 * hisi_smmu_lpae.c -- 3 layer pagetable
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/iommu.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <asm/pgalloc.h>
#include <linux/debugfs.h>
#include <linux/hisi/hisi-iommu.h>
#include <asm/uaccess.h>
#include <linux/bitops.h>
#include "hisi_smmu.h"

struct hisi_smmu_device_lpae *hisi_smmu_dev;

/*transfer 64bit pte table pointer to struct page*/
static pgtable_t smmu_pgd_to_pte_lpae(unsigned int ppte_table)
{
	unsigned long page_table_addr;
	if (!ppte_table) {
		dbg("error: the pointer of pte_table is NULL \n");
		return NULL;
	}
	page_table_addr = (unsigned long)ppte_table;
	return phys_to_page(page_table_addr);
}

/*transfer 64bit pte table pointer to struct page*/
static pgtable_t smmu_pmd_to_pte_lpae(unsigned long ppte_table)
{
	struct page *table = NULL;
	if (!ppte_table) {
		dbg("error: the pointer of pte_table is NULL \n");
		return NULL;
	}
	table = phys_to_page(ppte_table);
	return table;
}

static int get_domain_data_lpae(struct device_node *np, struct iommu_domain_data *data)
{
	struct device_node *node = NULL;
	int ret = 0;
	data->phy_pgd_base = hisi_smmu_dev->smmu_phy_pgtable_addr;
	if (np) {
		node = of_find_node_by_name(np, "iommu_info");
		if (!node) {
			dbg("find iommu_info node error \n");
			return -ENODEV;
		}
		ret = of_property_read_u32(node, "start-addr", &data->iova_start);
		if (ret) {
			dbg("read iova start address error \n");
			goto read_error;
		}
		ret = of_property_read_u32(node, "size", &data->iova_size);
		if (ret) {
			dbg("read iova size error \n");
			goto read_error;
		}
		dbg("%s:start_addr 0x%x, size 0x%x \n", __func__, data->iova_start, data->iova_size);
	}
read_error:
	return ret;
}

static int hisi_smmu_domain_init_lpae(struct iommu_domain *domain)
{
	return 0;
}


static void hisi_smmu_flush_pgtable_lpae(void *addr, size_t size)
{
	__flush_dcache_area(addr, size);
}

static void hisi_smmu_free_ptes_lpae(smmu_pgd_t pmd)
{
	pgtable_t table = smmu_pgd_to_pte_lpae(pmd);
	if (!table) {
		dbg("pte table is null \n");
		return ;
	}
	pgtable_page_dtor(table);
	__free_page(table);
	smmu_set_pmd_lpae(&pmd, 0);
}


static void hisi_smmu_free_pmds_lpae(smmu_pgd_t pgd)
{
	pgtable_t table = smmu_pmd_to_pte_lpae(pgd);
	if (!table) {
		dbg("pte table is null \n");
		return ;
	}
	pgtable_page_dtor(table);
	__free_page(table);
	smmu_set_pgd_lpae(&pgd, 0);
}

static void hisi_smmu_free_pgtables_lpae(unsigned long *page_table_addr)
{
	int i, j;
	smmu_pgd_t *pgd;
	smmu_pmd_t *pmd;
	unsigned long flags;

	pgd = (smmu_pgd_t *)page_table_addr;
	pmd = (smmu_pmd_t *)page_table_addr;

	spin_lock_irqsave(&hisi_smmu_dev->lock, flags);
	for (i = 0; i < SMMU_PTRS_PER_PGD; ++i) {
		if ((smmu_pgd_none_lpae(*pgd)) & (smmu_pmd_none_lpae(*pmd)))
			continue;
		for (j = 0; j < SMMU_PTRS_PER_PMD; ++j) {
			hisi_smmu_free_pmds_lpae(*pgd);
			pmd++;
		}
		hisi_smmu_free_ptes_lpae(*pmd);
		pgd++;
	}
	memset((void *)page_table_addr, 0, PAGE_SIZE);
	spin_unlock_irqrestore(&hisi_smmu_dev->lock, flags);
}

static void hisi_smmu_domain_destroy_lpae(struct iommu_domain *domain)
{
	if (list_empty(&hisi_smmu_dev->domain_list)) {
		hisi_smmu_free_pgtables_lpae((unsigned long *)hisi_smmu_dev->va_pgtable_addr);
	}
	if (domain) {
		kfree(domain);
	}
}

static int hisi_smmu_alloc_init_pte_lpae(smmu_pmd_t *ppmd,
		unsigned long addr, unsigned long end,
		unsigned long pfn, u64 prot)
{
	smmu_pte_t *pte, *start;
	pgtable_t table;
	u64 pteval = SMMU_PTE_TYPE;

	if (smmu_pmd_none_lpae(*ppmd)) {
		/* Allocate a new set of tables */
		dbg("%s: alloc new page table for pmd entry \n", __func__);
		table = alloc_page(GFP_ATOMIC|__GFP_ZERO|__GFP_DMA);
		if (!table) {
			dbg("%s: alloc page fail \n", __func__);
			return -ENOMEM;
		}
		hisi_smmu_flush_pgtable_lpae(page_address(table), SMMU_PAGE_SIZE);
		pgtable_page_ctor(table);
		if (prot & IOMMU_SEC)
			smmu_pmd_populate_lpae(ppmd, table, SMMU_PMD_TYPE);
		else
			smmu_pmd_populate_lpae(ppmd, table, SMMU_PMD_TYPE|SMMU_PMD_NS);
		hisi_smmu_flush_pgtable_lpae(ppmd, sizeof(*ppmd));
	}
	start = (smmu_pte_t *)smmu_pte_page_vaddr_lpae(ppmd) + smmu_pte_index(addr);
	pte = start;
	if (!prot) {
		pteval |= SMMU_PROT_NORMAL;
		pteval |= SMMU_PTE_NS;
	} else {
		if (prot & IOMMU_DEVICE) {
			pteval |= SMMU_PROT_DEVICE_nGnRE;
		} else {
			if (prot & IOMMU_CACHE)
				pteval |= SMMU_PROT_NORMAL;
			else
				pteval |= SMMU_PROT_NORMAL_NC;

			if ((prot & IOMMU_READ) && (prot & IOMMU_WRITE))
				pteval |= SMMU_PROT_NORMAL_NC ;
			else if ((prot & IOMMU_READ) && !(prot & IOMMU_WRITE))
				pteval |= SMMU_PAGE_READONLY ;
			else
				WARN_ON("carefully,you maybe not set readable attribute!");

			if (prot & IOMMU_EXEC)
				pteval |= SMMU_PAGE_READONLY_EXEC;
		}
		if (!(prot & IOMMU_SEC)) {
			pteval |= SMMU_PTE_NS;
		}
	}
	do {
		if (!pte_is_valid_lpae(pte)) {
			*pte = (u64)(__pfn_to_phys(pfn)|pteval);
		} else {
			/*dbg("%s:pte:%p is be mapped more times \n",__func__,pte);*/
			WARN_ONCE(1, "map the same address more times! \n");
		}
	} while (pte++, pfn++, addr += SMMU_PAGE_SIZE, addr < end);

	hisi_smmu_flush_pgtable_lpae(start, sizeof(*pte) * (pte - start));
	return 0;
}

static int hisi_smmu_alloc_init_pmd_lpae(smmu_pgd_t *ppgd,
		unsigned long addr, unsigned long end,
		unsigned long paddr, int prot)
{
	int ret = 0;
	smmu_pmd_t *ppmd, *start;
	u64 next;
	pgtable_t table;

	if (smmu_pgd_none_lpae(*ppgd)) {
		dbg("%s: alloc new page table for pgd entry \n", __func__);
		table = alloc_page(GFP_ATOMIC|__GFP_ZERO|__GFP_DMA);
		if (!table) {
			dbg("%s: alloc page fail \n", __func__);
			return -ENOMEM;
		}
		hisi_smmu_flush_pgtable_lpae(page_address(table), SMMU_PAGE_SIZE);
		pgtable_page_ctor(table);
		if (prot & IOMMU_SEC)
			smmu_pgd_populate_lpae(ppgd, table, SMMU_PGD_TYPE);
		else
			smmu_pgd_populate_lpae(ppgd, table, SMMU_PGD_TYPE|SMMU_PGD_NS);
		hisi_smmu_flush_pgtable_lpae(ppgd, sizeof(*ppgd));
	}
	start = (smmu_pmd_t *)smmu_pmd_page_vaddr_lpae(ppgd) + smmu_pmd_index(addr);
	ppmd = start;

	do {
		next = smmu_pmd_addr_end_lpae(addr, end);
		/*dbg("%s: next = 0x%lx , addr= %p\n",__func__, next, addr);*/
		ret = hisi_smmu_alloc_init_pte_lpae(ppmd, addr, next, __phys_to_pfn(paddr), prot);
		if (ret)
			goto error;
			paddr += (next - addr);
			addr = next;
		} while (ppmd++, addr < end);
error:
	return ret;
}

int hisi_smmu_handle_mapping_lpae(struct iommu_domain *domain,
		unsigned long iova, phys_addr_t paddr,
		size_t size, int prot)
{
	int ret;
	unsigned long end;
	unsigned long next;
	unsigned long flags;
	smmu_pgd_t *pgd = (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr;
	if (!pgd) {
		dbg("pgd is null \n");
		return -EINVAL;
	}
	iova = ALIGN(iova, SMMU_PAGE_SIZE);
	size = ALIGN(size, SMMU_PAGE_SIZE);
	spin_lock_irqsave(&hisi_smmu_dev->lock, flags);
	pgd += smmu_pgd_index(iova);
	end = iova + size;
	/*dbg("%s: end = 0x%lx \n",__func__,end);*/
	do {
		next = smmu_pgd_addr_end_lpae(iova, end);
		/*dbg("%s: next = 0x%lx , pgd= %p\n",__func__, next, pgd);*/
		ret = hisi_smmu_alloc_init_pmd_lpae(pgd, iova, next, paddr, prot);
		if (ret)
			goto out_unlock;
		paddr += next - iova;
		iova = next;
	} while (pgd++, iova < end);
out_unlock:
	spin_unlock_irqrestore(&hisi_smmu_dev->lock, flags);
	return ret;
}

static int hisi_smmu_map_lpae(struct iommu_domain *domain, unsigned long iova,
		phys_addr_t paddr, size_t size, int prot)
{
	unsigned long max_iova;
	struct iommu_domain_data *data;
	if (!domain) {
		dbg("domain is null \n");
		return -ENODEV;
	}
	data = domain->priv;
	max_iova = data->iova_start + data->iova_size;
	if (iova < data->iova_start) {
		dbg("iova failed: iova = 0x%lx, start = 0x%8x \n", iova, data->iova_start);
		goto error;
	}
	if ((iova+size) > max_iova) {
		dbg("iova exccess the domain range, iova+size = 0x%lx, end = 0x%lx \n", iova+size, max_iova);
		goto error;
	}
	return hisi_smmu_handle_mapping_lpae(domain, iova, paddr, size, prot);
error:
	dbg("iova is not in this range \n");
	return -EINVAL;
}

static unsigned int hisi_smmu_clear_pte_lpae(smmu_pgd_t *pmdp, unsigned int iova, unsigned int end)
{
	smmu_pte_t *ptep = NULL;
	smmu_pte_t *ppte = NULL;
	unsigned int size = end - iova;
	ptep = smmu_pte_page_vaddr_lpae(pmdp);
	ppte = ptep + smmu_pte_index(iova);
	do {
		*ppte = (unsigned int)0;
	} while (ppte++, iova += SMMU_PAGE_SIZE, iova < end);

	return size;
}

static unsigned int hisi_smmu_clear_pmd_lpae(smmu_pgd_t *pgdp, unsigned int iova, unsigned int end)
{
	smmu_pmd_t *pmdp = NULL;
	smmu_pmd_t *ppmd = NULL;
	unsigned int next = 0;
	unsigned int size = end - iova;
	pmdp = smmu_pmd_page_vaddr_lpae(pgdp);
	ppmd = pmdp + smmu_pmd_index(iova);
	do {
		next = smmu_pmd_addr_end_lpae(iova, end);
		hisi_smmu_clear_pte_lpae(ppmd, iova, next);
		iova = next ;
		dbg("%s: iova=0x%lx, end=0x%lx \n", __func__, iova, end);
	} while (ppmd++, iova < end);

	return size;
}

unsigned int hisi_smmu_handle_unmapping_lpae(struct iommu_domain *domain, unsigned long iova, size_t size)
{
	smmu_pgd_t *pgdp = NULL;
	unsigned int end = 0;
	unsigned int next = 0;
	unsigned int unmap_size = 0;
	unsigned long flags;

	iova = SMMU_PAGE_ALIGN(iova);
	size = SMMU_PAGE_ALIGN(size);
	pgdp = (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr;
	end = iova + size;
	dbg("%s:end=0x%x \n", __func__, end);
	pgdp += smmu_pgd_index(iova);
	spin_lock_irqsave(&hisi_smmu_dev->lock, flags);
	do {
		next = smmu_pgd_addr_end_lpae(iova, end);
		unmap_size += hisi_smmu_clear_pmd_lpae(pgdp, iova, next);
		iova = next ;
		dbg("%s: pgdp=%p, iova=0x%lx \n", __func__, pgdp, iova);
	} while (pgdp++, iova < end);
	spin_unlock_irqrestore(&hisi_smmu_dev->lock, flags);
	return unmap_size;
}

static size_t hisi_smmu_unmap_lpae(struct iommu_domain *domain, unsigned long iova,
		size_t size)
{
	unsigned long max_iova;
	unsigned int ret;
	struct iommu_domain_data *data;

	if (!domain) {
		dbg("domain is null \n");
		return -ENODEV;
	}
	data = domain->priv;
	/*caculate the max io virtual address */
	max_iova = data->iova_start + data->iova_size;
	/*check the iova */
	if (iova < data->iova_start) {
		goto error;
	}
	if ((iova+size) > max_iova) {
		dbg("iova exccess the domain range, iova+size = 0x%lx, end = 0x%lx \n", iova+size, max_iova);
		goto error;
	}
	/*unmapping the range of iova*/
	ret = hisi_smmu_handle_unmapping_lpae(domain, iova, size);
	if (ret == size) {
		dbg("%s:unmap size:0x%x \n", __func__, (unsigned int)size);
		return size;
	} else {
		return 0;
	}
error:
	dbg("%s:the range of io address is wrong \n", __func__);
	return -EINVAL;
}

static phys_addr_t hisi_smmu_iova_to_phys_lpae(struct iommu_domain *domain, dma_addr_t iova)
{
	smmu_pgd_t *pgdp, pgd;
	smmu_pmd_t pmd;
	smmu_pte_t pte;

	pgdp = (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr;
	if (!pgdp)
		return 0;

	pgd = *(pgdp + smmu_pgd_index(iova));
	if (smmu_pgd_none_lpae(pgd))
		return 0;

	pmd = *((smmu_pmd_t *)smmu_pmd_page_vaddr_lpae(&pgd) + smmu_pmd_index(iova));
	if (smmu_pmd_none_lpae(pmd))
		return 0;

	pte = *((u64 *)smmu_pte_page_vaddr_lpae(&pmd) + smmu_pte_index(iova));
	if (smmu_pte_none_lpae(pte))
		return 0;

	return __pfn_to_phys(pte_pfn(pte)) | (iova & ~SMMU_PAGE_MASK);
}

static int hisi_attach_dev_lpae(struct iommu_domain *domain, struct device *dev)
{
	struct device_node *np = dev->of_node;
	int ret = 0;
	struct iommu_domain_data *iommu_info = NULL;
	iommu_info = kzalloc(sizeof(struct iommu_domain_data), GFP_KERNEL);
	if (!iommu_info) {
		dbg("alloc iommu_domain_data fail \n");
		return -EINVAL;
	}
	list_add(&iommu_info->list, &hisi_smmu_dev->domain_list);
	domain->priv = iommu_info;
	ret = get_domain_data_lpae(np, domain->priv);
	return ret;
}

static void hisi_detach_dev_lpae(struct iommu_domain *domain,
		struct device *dev)
{
	struct iommu_domain_data *data ;
	data = (struct iommu_domain_data *)domain->priv;
	if (data) {
		list_del(&data->list);
		domain->priv = NULL;
		if (data) {
			kfree(data);
		}
	} else {
		dbg("%s:error! data entry has been delected \n", __func__);
	}
}

static dma_addr_t get_phys_addr_lpae(struct scatterlist *sg)
{
	dma_addr_t dma_addr = sg_dma_address(sg);
	if (!dma_addr)
		dma_addr = sg_phys(sg);
	return dma_addr;
}

static int hisi_smmu_map_range_lpae(struct iommu_domain *domain, unsigned long
		iova, struct scatterlist *sg, size_t size, int prot)
{
	phys_addr_t phys_addr;
	size_t mapped_size = 0;
	int ret = 0;

	while (sg) {
		dbg("to map a sg: iova: 0x%lx, sg: %p, maped size: 0x%x\n",
				iova, sg, mapped_size);
		phys_addr = get_phys_addr_lpae(sg);

		dbg("phys_addr: 0x%x\n", phys_addr);

		ret = hisi_smmu_map_lpae(domain, iova, phys_addr, sg->length, prot);
		if (ret) {
			dbg("hisi_smmu_map failed!\n");
			break;
		}

		iova += (unsigned long)ALIGN(sg->length, PAGE_SIZE);

		mapped_size += (size_t)ALIGN(sg->length, PAGE_SIZE);

		if (mapped_size >= size) {
			break;
		}
		sg = sg_next(sg);
	};
	return ret;
}

static size_t hisi_smmu_unmap_range_lpae(struct iommu_domain *domain, unsigned long iova,
		size_t size)
{
	size_t ret = 0;
	ret = hisi_smmu_unmap_lpae(domain, iova, size);
	if (!ret) {
		dbg("[%s] unmap iova fail! \n", __func__);
		return 0;
	}
	return ret;
}

/*
 *iova: the start address for tile mapping
 *size: the physical memory size
 *sg: the node of scatter list where are the start node of physical memory
 *sg_offset:the physical memory offset in the sg node ,where is the start
 position of physical memory
 *port: the pape property of virtual memory
 * this function complete one row mapping.
 */
static size_t hisi_map_tile_row_lpae(struct iommu_domain *domain, unsigned long
		iova, size_t size, struct scatterlist *sg, size_t sg_offset,
		struct hisi_map_tile_position_lpae *map_position,
		unsigned int prot){

	unsigned long map_size; /*the memory size that will be mapped*/
	unsigned long phys_addr;
	unsigned long mapped_size = 0; /*memory size that has been mapped*/
	int ret;

	while (1) {
		/*
		 *get the remain memory,if current sg node is not enough memory,
		 *we map the remain memory firstly.
		 */
		map_size = size - mapped_size;
		if (map_size > (sg->length - sg_offset)) {
			map_size = (sg->length - sg_offset);
		}
		/*get the start physical address*/
		phys_addr = (unsigned long)get_phys_addr_lpae(sg) + sg_offset;
		ret = hisi_smmu_map_lpae(domain, iova + mapped_size, phys_addr, map_size, prot);
		if (ret) {
			dbg("[%s] hisi_smmu_map failed!\n", __func__);
			break;
		}
		/*update mapped memory size*/
		mapped_size += map_size;
		/*
		 * if finished mapping,we update the memory offset of current node and
		 * save the memory position. otherwise we clean the sg_offset
		 * to zero and get next sg node.
		 */
		if (mapped_size < size) {
			sg_offset = 0;
			sg = sg_next(sg);
			if (!sg) {
				dbg("[%s] error physical memory not enough \n", __func__);
				break;
			}
		} else {
			sg_offset += map_size;
			/*if physcial memory of this node is exhausted, we choose next node*/
			if (sg_offset == sg->length) {
				sg_offset = 0;
				sg = sg_next(sg);
			}
			break;
		}
	}
	/*save current position*/
	map_position->sg = sg ;
	map_position->offset = sg_offset ;

	return mapped_size;
}

/*
 *domain:the iommu domain for mapping
 *iova:the start virtual address
 *sg: the scatter list of physical memory
 *size:the total size of all virtual memory
 *port:the property of page table of virtual memory
 *format:the parameter of tile mapping
 *this function map physical memory in tile mode
 */
static int hisi_smmu_map_tile_lpae(struct iommu_domain *domain, unsigned long iova,
		struct scatterlist *sg, size_t size, int prot,
		struct tile_format *format){

	unsigned int phys_length;
	struct scatterlist *sg_node;
	unsigned int row_number, row;
	unsigned int size_virt, size_phys;
	unsigned int sg_offset;
	int ret = 0;
	unsigned int mapped_size , header_size;
	struct hisi_map_tile_position_lpae map_position;

	/* calculate the whole length of phys mem */
	for (phys_length = 0, sg_node = sg; sg_node; sg_node = sg_next(sg_node)) {
		phys_length += ALIGN(sg_node->length, PAGE_SIZE);
	}
	header_size = format->header_size ;

	/* calculate the number of raws*/
	row_number = ((phys_length - header_size) / PAGE_SIZE) / format->phys_page_line;
	dbg("phys_length: 0x%x, rows: 0x%x, header_size: 0x%x \n", phys_length, row_number, header_size);

	/*caculate the need physical memory and virtual memory for one row*/
	size_phys = (format->phys_page_line * PAGE_SIZE);
	size_virt = (format->virt_page_line * PAGE_SIZE);

	sg_offset = 0;
	sg_node = sg;

	/*set start position*/
	map_position.sg = sg ;
	map_position.offset = 0 ;

	/*map header*/
	if (header_size) {
		mapped_size = hisi_map_tile_row_lpae(domain, iova, header_size, sg_node, sg_offset, &map_position, prot);
		if (mapped_size != header_size) {
			WARN(1, "map head fail \n");
			ret = -EINVAL;
			goto error;
		}
		iova += ALIGN(header_size , size_virt);
	}
	/* map row by row */
	for (row = 0; row < row_number; row++) {
		/* get physical memory position */
		if (map_position.sg) {
			sg_node = map_position.sg;
			sg_offset = map_position.offset;
		} else {
			dbg("[%s]:physical memory is not enough \n", __func__);
			break;
		}
		/* map one row*/
		mapped_size = hisi_map_tile_row_lpae(domain, iova + (size_virt * row), size_phys, sg_node, sg_offset, &map_position, prot);
		if (mapped_size != size_phys) {
			WARN(1, "hisi_map_tile_row failed!\n");
			ret = -EINVAL;
			break;
		}
	};
error:
	return ret;
}

static size_t hisi_smmu_unmap_tile_lpae(struct iommu_domain *domain, unsigned long iova,
		size_t size)
{
	return hisi_smmu_unmap_range_lpae(domain, iova, size);
}

static struct iommu_ops hisi_smmu_ops = {
	.domain_init	= hisi_smmu_domain_init_lpae,
	.domain_destroy	= hisi_smmu_domain_destroy_lpae,
	.map		= hisi_smmu_map_lpae,
	.unmap		= hisi_smmu_unmap_lpae,
	.attach_dev = hisi_attach_dev_lpae,
	.detach_dev = hisi_detach_dev_lpae,
	.iova_to_phys	= hisi_smmu_iova_to_phys_lpae,
	.pgsize_bitmap	= SMMU_PAGE_SIZE ,
	.map_range = hisi_smmu_map_range_lpae,
	.unmap_range = hisi_smmu_unmap_range_lpae,
	.map_tile = hisi_smmu_map_tile_lpae,
	.unmap_tile = hisi_smmu_unmap_tile_lpae,
};

static int hisi_smmu_probe_lpae(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	dbg("enter %s\n", __func__);
	hisi_smmu_dev = devm_kzalloc(dev, sizeof(struct hisi_smmu_device_lpae), GFP_KERNEL);
	if (!hisi_smmu_dev) {
		dev_err(dev, "failed to allocate arm_smmu_device\n");
		goto smmu_device_error;
	}
	hisi_smmu_dev->dev = dev;
	INIT_LIST_HEAD(&hisi_smmu_dev->domain_list);
	spin_lock_init(&hisi_smmu_dev->lock);

	hisi_smmu_dev->smmu_phy_pgtable_addr = virt_to_phys(hisi_smmu_dev->smmu_pgd);
    hisi_smmu_dev->va_pgtable_addr = (unsigned long)hisi_smmu_dev->smmu_pgd;
	bus_set_iommu(&platform_bus_type, &hisi_smmu_ops);
	return 0;

smmu_device_error:
	return -ENOMEM;
}

static int hisi_smmu_remove_lpae(struct platform_device *pdev)
{
	return 0;
}

static struct of_device_id hisi_smmu_of_match_lpae[] = {
	{ .compatible = "hisi,hisi-smmu-lpae"},
	{ },
};
MODULE_DEVICE_TABLE(of, hisi_smmu_of_match_lpae);

static struct platform_driver hisi_smmu_driver_lpae = {
	.driver	= {
		.owner		= THIS_MODULE,
		.name		= "hisi-smmu-lpae",
		.of_match_table	= of_match_ptr(hisi_smmu_of_match_lpae),
	},
	.probe	= hisi_smmu_probe_lpae,
	.remove	= hisi_smmu_remove_lpae,
};

static int __init hisi_smmu_init_lpae(void)
{
	int ret = 0;

	ret = platform_driver_register(&hisi_smmu_driver_lpae);
	return ret;
}

static void __exit hisi_smmu_exit_lpae(void)
{
	return platform_driver_unregister(&hisi_smmu_driver_lpae);
}

subsys_initcall(hisi_smmu_init_lpae);
module_exit(hisi_smmu_exit_lpae);

MODULE_DESCRIPTION("IOMMU API for HI3660 architected SMMU implementations");
MODULE_AUTHOR("huawei hisilicon company");
MODULE_LICENSE("GPL v2");


