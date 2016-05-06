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

/*-----------unit test for page table--------*/
unsigned int iova_start ;
unsigned int map_size ;
static struct sg_table *table;

struct iommu_page_info {
	struct page *page;
		unsigned int order;
		struct list_head list;
};

ssize_t smmu_do_map(void)
{
	unsigned int i;
	struct scatterlist *sg = NULL ;
	unsigned int temp;
	/*get parameter from buffer*/
	dbg("%s: iova_start: 0x%x", __func__, iova_start);
	temp = iova_start;
	if (table) {
		for_each_sg(table->sgl, sg, table->nents, i) {
			hisi_smmu_handle_mapping_lpae(NULL, temp, page_to_phys(sg_page(sg)), sg->length, 0);
			temp += sg->length;
		}
	}
	return 0;
}

ssize_t smmu_alloc_memory_and_map(void)
{
	unsigned int sum = 0, ret = 0;
	struct list_head pages;
	struct iommu_page_info *info, *tmp_info;
	unsigned int i = 0;
	struct page *page;
	struct scatterlist *sg = NULL;
	unsigned int order = 8;

	INIT_LIST_HEAD(&pages);
	dbg("%s: map_size=0x%x \n", __func__, map_size);
			do {
				info = kmalloc(sizeof(struct iommu_page_info), GFP_KERNEL);
				if (!info) {
					dbg("%s: kmalloc info failed!\n", __func__);
					return -ENOMEM;
				}
				page = alloc_pages(GFP_KERNEL, order); /*alloc 4kb each time*/
				if (!page) {
					dbg("alloc page error order = %d \n", order);
					kfree(info);
					order-- ;
					continue;
				}
				info->page = page;
				info->order = order;
				INIT_LIST_HEAD(&info->list);
				list_add_tail(&info->list, &pages);
				sum += (1 << info->order) * PAGE_SIZE;
				i++;
			} while (sum < map_size);

			table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
			if (!table) {
				return -ENOMEM;
			}
			ret = sg_alloc_table(table, i, GFP_KERNEL);
			if (ret) {
				return -ENOMEM;
			}
			sg = table->sgl;
			list_for_each_entry_safe(info, tmp_info, &pages, list) {
				struct page *page = info->page;
				sg_set_page(sg, page, (1 << info->order) * PAGE_SIZE, 0);
				sg = sg_next(sg);
				list_del(&info->list);
				kfree(info);
			}
			dbg("sg list_headist is ok \n");
			smmu_do_map();
			return map_size;
}

int smmu_do_unmap_and_free(void)
{
	struct scatterlist *sg;
	unsigned int i = 0;
	unsigned int mem_size = 0;

	hisi_smmu_handle_unmapping_lpae(NULL, iova_start, map_size);

	/*free physicalical memory*/
	if (table) {
		for_each_sg(table->sgl, sg, table->nents, i) {
			__free_pages(sg_page(sg), get_order(sg->length));
			mem_size += sg->length;
		}
	    dbg("%s:free total memory 0x%x \n", __func__, mem_size);
		sg_free_table(table);
		kfree(table);
	}
	table = NULL;
	return 0;
}

/*show page table*/
smmu_pte_t  hisi_dbg_show_ptb_lpae(unsigned int iova, smmu_pgd_t *pgdp)
{
	smmu_pgd_t pgd;
	smmu_pmd_t pmd;
	smmu_pte_t pte;
	if (!pgdp) {
		dbg("pgd pointer is null \n");
		return 0;
	}
	pgd = *(pgdp + smmu_pgd_index(iova));
	if (smmu_pgd_none_lpae(pgd)) {
		dbg("pgd entery is null,offset=%d \n", smmu_pgd_index(iova));
		return 0;
	}

	pmd = *((smmu_pmd_t*)smmu_pmd_page_vaddr_lpae(&pgd) + smmu_pmd_index(iova));
	if (smmu_pmd_none_lpae(pmd))
	{
		dbg("pmd entery is null,offset=%d \n", smmu_pmd_index(iova));
		return 0;
	}

	pte = *((smmu_pte_t *)smmu_pte_page_vaddr_lpae(&pmd) + smmu_pte_index(iova));
	return pte;
}

smmu_pgd_t hisi_dbg_show_pgd_lpae(unsigned int iova, smmu_pgd_t *pgdp)
{
    return *(pgdp + smmu_pgd_index(iova));
}

smmu_pmd_t hisi_dbg_show_pmd_lpae(unsigned int iova, smmu_pgd_t *pgdp)
{
    smmu_pgd_t pgd;
	smmu_pmd_t pmd;
    pgd = *(pgdp + smmu_pgd_index(iova));
	if (smmu_pgd_none_lpae(pgd)) {
		dbg("pgd entery is null,offset=%d \n", smmu_pgd_index(iova));
		return 0;
	}

	pmd = *((smmu_pmd_t *)smmu_pmd_page_vaddr_lpae(&pgd) + smmu_pmd_index(iova));
	return pmd;
}

int  smmu_print_pgtable(void)
{
	unsigned int io_addr = 0, iova_end = 0;
	unsigned char buf[128] = {0};
	static unsigned int num;
	unsigned long len;
	struct file *smmu_file = NULL;
	mm_segment_t   fs;
	loff_t  pos = 0;
	char file_name[64] = {0};
	unsigned buf_len = 0;

	iova_end = iova_start + map_size ;
	snprintf(file_name, sizeof(file_name), "/data/smmu_pagetable_%d.txt", num++);

	smmu_file = filp_open(file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (IS_ERR(smmu_file)) {
		dbg("create smmu file error!");
		return -EINVAL;
	} else {
		dbg("open file ok \n");
	}
	fs = get_fs();
	set_fs(KERNEL_DS);

	buf_len = snprintf(buf, sizeof(buf), "[pgbase=0x%lx] \n", hisi_smmu_dev->va_pgtable_addr);
	len = vfs_write(smmu_file, (void *)buf, buf_len, &pos);
	if (!len) {
		dbg("write file error \n");
	}
	for (io_addr=iova_start; io_addr < iova_end; io_addr += SMMU_PAGE_SIZE) {
		memset(buf,0,sizeof(buf));
		buf_len = snprintf(buf, sizeof(buf), "pgd[%d]=0x%llx,pmd[%d]=0x%llx, pte[%d]=0x%llx \n",
				smmu_pgd_index(io_addr), hisi_dbg_show_pgd_lpae(io_addr, (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr),
				smmu_pmd_index(io_addr), hisi_dbg_show_pmd_lpae(io_addr, (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr),
				smmu_pte_index(io_addr), hisi_dbg_show_ptb_lpae(io_addr, (smmu_pgd_t *)hisi_smmu_dev->va_pgtable_addr)); 
		len = vfs_write(smmu_file, (void*)buf, buf_len, &pos);
        if (!len) {
		    dbg("write file error \n");
	    }
	}
	filp_close(smmu_file, NULL);
	set_fs(fs);
	return 0;
}

void set_smmu_param(unsigned int start, unsigned int size)
{
   iova_start = start;
	map_size = size;
}

int smmu_lpae_test(unsigned int start, unsigned int size)
{
	dbg("enter \n");
	set_smmu_param(start, size);
	smmu_alloc_memory_and_map();
	smmu_print_pgtable();
	smmu_do_unmap_and_free();
	smmu_print_pgtable();
    return 0;

}
