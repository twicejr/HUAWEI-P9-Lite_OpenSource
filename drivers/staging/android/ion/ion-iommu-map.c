/*
 * Copyright (C) 20013-2013 hisilicon. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/genalloc.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/sizes.h>
#include <linux/iommu.h>
#include <linux/platform_device.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/hisi/ion-iommu.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/of.h>
#include <linux/of_address.h>

#define DBG_BUF_SIZE       (4096)
#ifdef IOMMU_DEBUG
#define dbg(format, arg...)    \
	do {                 \
		printk(KERN_INFO "[hisi_iommu_domain]"format, ##arg); \
	} while (0)
#else
#define dbg(format, arg...)
#endif

static unsigned int dump_chunk_switch;

struct hisi_iommu_debug_info {
	unsigned int alloc_iova_count;
	unsigned int free_iova_count;
} dbg_inf;

struct map_result {
	unsigned long iova_start;
	unsigned long iova_size;
	unsigned long iommu_ptb_base;
	unsigned long iommu_iova_base;
	unsigned long is_tile;
};

static struct hisi_iommu_domain* hisi_iommu_domain_p;
DEFINE_MUTEX(iova_pool_mutex);

/**
 * get the whole size of genpool
 */
static size_t hisi_iova_size(struct gen_pool *pool)
{
	size_t size;
	mutex_lock(&iova_pool_mutex);
	size = gen_pool_size(pool);
	mutex_unlock(&iova_pool_mutex);
	return size;
}


/*only be uesed to test*/
size_t hisi_iommu_iova_size(void)
{
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	return hisi_iova_size(hisi_domain->iova_pool);
}
EXPORT_SYMBOL_GPL(hisi_iommu_iova_size);


/**
 * get the available size of genpool
 */
static size_t hisi_iova_available(struct gen_pool *pool)
{
	size_t avail;
	mutex_lock(&iova_pool_mutex);
	avail = gen_pool_avail(pool);
	mutex_unlock(&iova_pool_mutex);
	return avail;
}
/*only be used to test*/
static void dump_chunk(struct gen_pool *pool,
		struct gen_pool_chunk *chunk, void *data)
{
	int i;
	int nbits = (chunk->end_addr - chunk->start_addr) >> pool->min_alloc_order;
	int nlong = BITS_TO_LONGS(nbits);
	if(dump_chunk_switch){
		printk(KERN_INFO "chunk allocate map: nlong: %d\n", nlong);
		for (i = nlong; i >0; i -= 4) {
			printk(KERN_INFO " %08lx %08lx %08lx %08lx\n",
					chunk->bits[i-1],
					chunk->bits[i-2],
					chunk->bits[i-3],
					chunk->bits[i-4]);
		}
	}
}
/*only be used to test*/
size_t hisi_iommu_iova_available(void)
{
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	if(!hisi_domain->iova_pool){
		return -EINVAL;
	}
	gen_pool_for_each_chunk(hisi_domain->iova_pool, dump_chunk, NULL);
	return hisi_iova_available(hisi_domain->iova_pool);
}
EXPORT_SYMBOL_GPL(hisi_iommu_iova_available);


/**
 * free a rage of space back to genpool
 */
static void hisi_free_iova(struct gen_pool *pool,
		unsigned long iova, size_t size)
{
	mutex_lock(&iova_pool_mutex);
	gen_pool_free(pool, iova, size);

	dbg_inf.free_iova_count++;

	mutex_unlock(&iova_pool_mutex);
}

void hisi_iommu_free_iova(unsigned long iova, size_t size)
{
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	hisi_free_iova(hisi_domain->iova_pool, iova, size);
}
EXPORT_SYMBOL_GPL(hisi_iommu_free_iova);


/**
 * get a rage of space from genpool
 */
static unsigned long hisi_alloc_iova(struct gen_pool *pool,
		unsigned long size, unsigned long align)
{
	unsigned long iova = 0;

	mutex_lock(&iova_pool_mutex);

	iova = gen_pool_alloc(pool, size);
	if (!iova) {
		printk(KERN_ERR "hisi iommu gen_pool_alloc failed!\n");
		mutex_unlock(&iova_pool_mutex);
		return 0;
	}

	if (align > (1 << pool->min_alloc_order)) {
		WARN(1, "hisi iommu domain cant align to 0x%lx\n", align);
	}

	dbg_inf.alloc_iova_count++;

	mutex_unlock(&iova_pool_mutex);
	return iova;
}

unsigned long hisi_iommu_alloc_iova(size_t size, unsigned long align)
{
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	return hisi_alloc_iova(hisi_domain->iova_pool, size, align);
}
EXPORT_SYMBOL_GPL(hisi_iommu_alloc_iova);


static struct gen_pool *iova_pool_setup(unsigned long start,
		unsigned long end, unsigned long align)
{
	struct gen_pool *pool = NULL;
	int ret = 0;

	pool = gen_pool_create(order_base_2(align), -1);
	if (!pool) {
		printk(KERN_ERR "Create gen pool failed!\n");
		return NULL;
	}
	/* iova start should not be 0, because return
	   0 when alloc iova is considered as error */
	if (0 == start) {
		WARN(1, "iova start should not be 0!\n");
	}

	ret = gen_pool_add(pool, start, (end - start), -1);
	if (ret) {
		printk(KERN_ERR "Gen pool add failed!\n");
		gen_pool_destroy(pool);
		return NULL;
	}

	return pool;
}


static void iova_pool_destory(struct gen_pool *pool)
{
	gen_pool_destroy(pool);
}

int hisi_iommu_get_info(unsigned int *iova_start, unsigned int *pgtbl_base)
{
	struct iommu_domain_capablity data;
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;

	if(!hisi_domain || iommu_domain_get_attr(hisi_domain->domain, DOMAIN_ATTR_CAPABLITY, &data)){
		return 1;
	}
	*iova_start = data.iova_start;
	*pgtbl_base = data.pgtbl_base;

	return 0;
}
EXPORT_SYMBOL_GPL(hisi_iommu_get_info);

static int do_iommu_domain_map(struct hisi_iommu_domain *hisi_domain,struct scatterlist *sgl,
		struct iommu_map_format *format, struct map_result *result)
{
	int ret;
	unsigned long phys_len, iova_size;
	unsigned long iova_start;

	struct gen_pool *pool;
	struct iommu_domain *domain;
	struct scatterlist *sg;
	struct tile_format fmt;
	/* calculate whole phys mem length */
	for (phys_len = 0, sg = sgl; sg; sg = sg_next(sg)) {
		phys_len += (unsigned long)ALIGN(sg->length, PAGE_SIZE);
	}

	/* get io virtual address size */
	if (format->is_tile) {
		unsigned long lines;
		unsigned long body_size;
		body_size = phys_len - format->header_size;
		lines = body_size / (format->phys_page_line * PAGE_SIZE);

		/*header need more lines virtual space*/
		if ( format->header_size ){
			unsigned long header_size;
			header_size = ALIGN(format->header_size ,format->virt_page_line * PAGE_SIZE);
			lines +=  header_size / (format->virt_page_line * PAGE_SIZE);
		}

		iova_size = lines * format->virt_page_line * PAGE_SIZE ;
	} else {
		iova_size = phys_len;
	}

	/* alloc iova */
	pool = hisi_domain->iova_pool;
	domain = hisi_domain->domain;
	iova_start = hisi_alloc_iova(pool,iova_size,hisi_domain->range.align);
	if (!iova_start) {
		printk("[%s]hisi_alloc_iova alloc 0x%lx failed!\n", __func__, iova_size);
		printk("[%s]dump iova pool begain--------------------------\n", __func__);
		printk("iova available: 0x%x\n",(unsigned int)hisi_iommu_iova_available());
		printk("alloc count: %d, free count: %d\n",
				dbg_inf.alloc_iova_count, dbg_inf.free_iova_count);
		printk("[%s]dump iova pool end   --------------------------\n", __func__);
		return -EINVAL;
	}

	if (0x100000000 < (iova_start + iova_size)) {
		pr_err("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "
				"hisi iommu can not deal with iova 0x%lx size 0x%lx\n",
				iova_start, iova_size);
	}

	/* do map */
	if (format->is_tile) {
		fmt.is_tile = format->is_tile;
		fmt.phys_page_line = format->phys_page_line;
		fmt.virt_page_line = format->virt_page_line;
		fmt.header_size = format->header_size ;
		ret = iommu_map_tile(domain, iova_start, sgl, iova_size, 0,&fmt);
	} else {
		ret = iommu_map_range(domain, iova_start,sgl,(size_t)iova_size,format->prot);
	}

	if (ret) {
		printk(KERN_ERR "[%s]map failed!\n", __func__);
		hisi_free_iova(pool, iova_start, iova_size);
		return ret;
	}else {
		/* out put result */
		result->iova_start = iova_start;
		result->iova_size = iova_size;
	}
	return 0;
}

int hisi_iommu_map_domain(struct scatterlist *sgl,struct iommu_map_format *format)
{
	int ret = 0;
	struct map_result result;
	struct hisi_iommu_domain *hisi_domain;
	hisi_domain = hisi_iommu_domain_p;

	memset(&result, 0, sizeof(result));

	ret = do_iommu_domain_map(hisi_domain,sgl,format,&result);
	if (ret){
		dbg("alloc iova fail\n");
		return ret;
	}
	format->iova_start = result.iova_start;
	format->iova_size = result.iova_size;

	/* get value which write into iommu register */
	return ret;
}
EXPORT_SYMBOL_GPL(hisi_iommu_map_domain);

static int do_iommu_domain_unmap(struct map_result *result)
{
	unsigned long unmaped_size;
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	struct gen_pool *pool = hisi_domain->iova_pool;
	/* unmap tile equals to unmpa range */
	if (result->is_tile){
		unmaped_size = iommu_unmap_tile(hisi_domain->domain,
		result->iova_start,result->iova_size);

	}else{
		unmaped_size = iommu_unmap_range(hisi_domain->domain,
				result->iova_start, result->iova_size);
	}
	if (unmaped_size != result->iova_size) {
		dbg("[%s]unmap failed!\n", __func__);
		return -EINVAL;
	}
	/* free iova */
	if(pool){
		hisi_free_iova(pool, result->iova_start, result->iova_size);
	}
	return 0;
}

#ifdef CONFIG_ARM64_64K_PAGES
#error hisi iommu can not deal with 64k pages!
#endif

int hisi_iommu_unmap_domain(struct iommu_map_format *format)
{
	struct map_result result;
	result.iova_start = format->iova_start;
	result.iova_size = format->iova_size;
	result.is_tile = format->is_tile;
	return do_iommu_domain_unmap(&result);
}
EXPORT_SYMBOL_GPL(hisi_iommu_unmap_domain);
/*only used to test*/
phys_addr_t hisi_iommu_domain_iova_to_phys(unsigned long iova)
{
	struct iommu_domain *domain ;
	domain = hisi_iommu_domain_p->domain;
	return iommu_iova_to_phys(domain, iova);
}
EXPORT_SYMBOL_GPL(hisi_iommu_domain_iova_to_phys);

unsigned int hisi_iommu_page_size(void)
{
	return SZ_4K;
}
EXPORT_SYMBOL_GPL(hisi_iommu_page_size);


bool hisi_iommu_off_on(void)
{
	struct hisi_iommu_domain *hisi_domain = hisi_iommu_domain_p;
	struct iommu_domain_capablity data;
	if(iommu_domain_get_attr(hisi_domain->domain, DOMAIN_ATTR_CAPABLITY,&data)){
		return false;
	}
	return data.off_on;
}
EXPORT_SYMBOL_GPL(hisi_iommu_off_on);

static int read_node(struct device_node* np,struct section_info* section, const char* name)
{
    struct device_node *node = NULL;
	int ret ;
	node = of_find_node_by_name(np,name);
	if(!node){
		dbg("%s:find node error \n",__func__);
	}
	ret = of_property_read_u32(node, "start-addr", &section->iova_start);
	if (ret) {
		dbg("%s:read iova start address error \n",__func__);
		goto read_error;
	}
	ret = of_property_read_u32(node, "size", &section->iova_size);
	if (ret) {
		dbg("%s:read iova start address error \n",__func__);
		goto read_error;
	}
	ret = of_property_read_u32(node, "page-size", &section->page_size);
	if (ret) {
		dbg("%s:read iova start address error \n",__func__);
		goto read_error;
	}
	ret = of_property_read_u32(node, "page-align", &section->align);
	if (ret) {
		dbg("%s:read iova start address error \n",__func__);
		goto read_error;
	}
	return 0;
read_error:
   return -ENODEV;
}

static int get_range_info(struct device_node* np,
		struct hisi_iommu_domain *domain,
		struct iommu_domain_capablity *data)
{
	int ret;
	ret = read_node(np,&domain->range,"linear");
	if(ret){
		printk("%s: read linear device node error \n",__func__);
	}

	/*save address range for ion allocator*/
	data->iova_start = domain->range.iova_start;
	data->iova_end  = domain->range.iova_start + domain->range.iova_size;
	data->iova_align = domain->range.align;
	printk("%s:iova_start=0x%x,iova_end=0x%x, iova_align=0x%x \n",
			__func__,data->iova_start,data->iova_end, data->iova_align);
	return 0;
}

int hisi_ion_enable_iommu(struct platform_device *pdev)
{
	int ret;
	struct iommu_domain_capablity data;
	struct device *dev = &pdev->dev;
	struct hisi_iommu_domain *hisi_domain;
	struct device_node *np = pdev->dev.of_node;

	printk(KERN_ERR"in %s start \n",__func__);
	hisi_domain = kzalloc(sizeof(*hisi_domain), GFP_KERNEL);
	if (!hisi_domain) {
		dbg("alloc hisi_domain object fail \n");
		return -ENOMEM;
	}
	if (!iommu_present(dev->bus)) {
		dbg("iommu not found\n");
		kfree(hisi_domain);
		return 0;
	}

	/* create iommu domain */
	hisi_domain->domain = iommu_domain_alloc(dev->bus);
	if (!hisi_domain->domain) {
		ret = -EINVAL;
		goto error;
	}
	iommu_attach_device(hisi_domain->domain,dev);
	get_range_info(np,hisi_domain,&data);
	/* align mean in this pool allocation buffer is aligned by iommu align request*/
	hisi_domain->iova_pool = iova_pool_setup(data.iova_start,
			data.iova_end, data.iova_align);
	if (!hisi_domain->iova_pool) {
		ret = -EINVAL;
		goto error;
	}

	/* this is a global pointer */
	hisi_iommu_domain_p = hisi_domain;

	dbg("in %s end \n",__func__);
	return 0;

error:
	WARN(1, "hisi_iommu_domain_init failed!\n");
	if (hisi_domain->iova_pool)
		iova_pool_destory(hisi_domain->iova_pool);
	if (hisi_domain->domain)
		iommu_domain_free(hisi_domain->domain);
	if (hisi_domain)
		kfree(hisi_domain);

	return ret;
}
EXPORT_SYMBOL(hisi_ion_enable_iommu);
