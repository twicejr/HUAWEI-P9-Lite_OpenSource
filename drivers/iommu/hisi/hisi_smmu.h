#ifndef HISI_SMMU_H
#define HISI_SMMU_H

/*#define IOMMU_DEBUG*/
#ifdef IOMMU_DEBUG
#define dbg(format, arg...)  pr_err("[iommu]"format, ##arg);
#else
#define dbg(format, arg...)
#endif

#define SMMU_PHY_PTRS_PER_PTE (256)
/*#define SMMU_PHY_PTRS_PER_PGD (4096)*/
#define SMMU_PTRS_PER_PGD     (4)
#define SMMU_PTRS_PER_PMD     (512)
#define SMMU_PTRS_PER_PTE     (512)
#define SMMU_PAGE_SHIFT       (12)

#define PAGE_TABLE_ADDR_MASK  (UL(0xFFFFFFF) << SMMU_PAGE_SHIFT)

#define SMMU_PAGE_SIZE        BIT(SMMU_PAGE_SHIFT)
#define SMMU_PAGE_MASK	      (~(SMMU_PAGE_SIZE-1))

#define SMMU_PGDIR_SHIFT	  (30)
#define SMMU_PGDIR_SIZE		  BIT(SMMU_PGDIR_SHIFT)
#define SMMU_PGDIR_MASK		  (~(SMMU_PGDIR_SIZE-1))

#define SMMU_PMDIR_SHIFT      (21)
#define SMMU_PMDIR_SIZE        BIT(SMMU_PMDIR_SHIFT)
#define SMMU_PMDIR_MASK       (~(SMMU_PMDIR_SIZE-1))
#define SMMU_PGD_TYPE         (BIT(0) | BIT(1))
#define SMMU_PMD_TYPE         (BIT(0) | BIT(1))
#define SMMU_PTE_TYPE         (BIT(0) | BIT(1))

#define SMMU_PGD_NS           BIT(63)
#define SMMU_PMD_NS           BIT(63)
#define SMMU_PTE_NS           BIT(5)

#define SMMU_PTE_PXN          BIT(53)           /* Privileged XN */
#define SMMU_PTE_UXN          BIT(54)           /* User XN */
#define SMMU_PTE_USER         BIT(6)            /* AP[1] */
#define SMMU_PTE_RDONLY       BIT(7)            /* AP[2] */
#define SMMU_PTE_SHARED       (BIT(8) | BIT(9)) /* SH[1:0]inner shareable */
#define SMMU_PTE_AF           BIT(10)           /* Access Flag */
#define SMMU_PTE_NG	          BIT(11)           /* nG */
#define SMMU_PTE_ATTRINDX(t)  ((t) << 2)
/*
 * Memory types available.
 */
#define MT_DEVICE_nGnRnE	0
#define MT_DEVICE_nGnRE		1
#define MT_DEVICE_GRE		2
#define MT_NORMAL_NC		3
#define MT_NORMAL           4

#define SMMU_PROT_DEFAULT       (SMMU_PTE_TYPE | SMMU_PTE_AF | SMMU_PTE_SHARED)
#define SMMU_PAGE_DEFAULT       (SMMU_PROT_DEFAULT | SMMU_PTE_ATTRINDX(MT_NORMAL))

#define SMMU_PROT_DEVICE_nGnRE  (SMMU_PROT_DEFAULT | SMMU_PTE_PXN | SMMU_PTE_UXN | SMMU_PTE_ATTRINDX(MT_DEVICE_nGnRE))
#define SMMU_PROT_NORMAL_NC     (SMMU_PROT_DEFAULT | SMMU_PTE_PXN | SMMU_PTE_UXN | SMMU_PTE_ATTRINDX(MT_NORMAL_NC))
#define SMMU_PROT_NORMAL        (SMMU_PROT_DEFAULT | SMMU_PTE_PXN | SMMU_PTE_UXN | SMMU_PTE_ATTRINDX(MT_NORMAL))

#define SMMU_PAGE_READONLY      (SMMU_PAGE_DEFAULT | SMMU_PTE_USER | SMMU_PTE_NG | SMMU_PTE_PXN | SMMU_PTE_UXN)
#define SMMU_PAGE_READONLY_EXEC (SMMU_PAGE_DEFAULT | SMMU_PTE_USER | SMMU_PTE_NG | SMMU_PTE_PXN)

#define smmu_pte_index(addr)    (((addr) >> SMMU_PAGE_SHIFT) & (SMMU_PTRS_PER_PTE - 1))
#define smmu_pmd_index(addr)    (((addr) >> SMMU_PMDIR_SHIFT) & (SMMU_PTRS_PER_PMD - 1))
#define smmu_pgd_index(addr)    (((addr) >> SMMU_PGDIR_SHIFT) & (SMMU_PTRS_PER_PGD - 1))
#define SMMU_PAGE_ALIGN(addr)   ALIGN(addr, PAGE_SIZE)

typedef u64 smmu_pgd_t;
typedef u64 smmu_pmd_t;
typedef u64 smmu_pte_t;

/*smmu device object*/
struct hisi_smmu_device_lpae {
	struct device      *dev;
	struct list_head   domain_list;
	unsigned int       ref_count;
	spinlock_t         lock;
	unsigned long      va_pgtable_addr;
	phys_addr_t        smmu_phy_pgtable_addr;
	smmu_pgd_t         smmu_pgd[4];
};

struct hisi_map_tile_position_lpae {
	struct scatterlist *sg;
	unsigned long offset;
};

extern struct hisi_smmu_device_lpae *hisi_smmu_dev;

static inline unsigned int smmu_pgd_none_lpae(smmu_pgd_t pgd)
{
	return !(pgd ? pgd : 0);
}

static inline unsigned int smmu_pmd_none_lpae(smmu_pmd_t pmd)
{
	return !(pmd ? pmd : 0);
}

static inline unsigned int smmu_pte_none_lpae(smmu_pte_t pte)
{
	return !(pte ? pte : 0);
}

static inline unsigned int pte_is_valid_lpae(smmu_pte_t *ptep)
{
	return (*(ptep)&SMMU_PTE_TYPE) ? 1 : 0;
}

/* Find an entry in the second-level page table.. */
static inline void *smmu_pmd_page_vaddr_lpae(smmu_pmd_t *pgd)
{
	return phys_to_virt(*pgd & PAGE_TABLE_ADDR_MASK);
}

/* Find an entry in the third-level page table.. */
static inline void *smmu_pte_page_vaddr_lpae(smmu_pmd_t *pmd)
{
	return phys_to_virt(*pmd & PAGE_TABLE_ADDR_MASK);
}


/*fill the pgd entry, pgd value must be 64bit */
static inline void smmu_set_pgd_lpae(smmu_pgd_t *pgdp, u64 pgd)
{
	*pgdp = pgd;
	dsb(ishst);
	isb();
}

/*fill the pmd entry, pgd value must be 64bit */
static inline void smmu_set_pmd_lpae(smmu_pgd_t *pmdp, u64 pmd)
{
	dbg("smmu_set_pmd_lpae: pmd = 0x%lx\n", pmd);
	*pmdp = pmd;
	dsb(ishst);
	isb();
}

static inline void smmu_pmd_populate_lpae(smmu_pmd_t *pmdp,
		pgtable_t ptep, pgdval_t prot)
{
	smmu_set_pmd_lpae(pmdp, (u64)(page_to_phys(ptep) | prot));
}

static inline void smmu_pgd_populate_lpae(smmu_pgd_t *pgdp,
		pgtable_t pmdp, pgdval_t prot)
{
	smmu_set_pgd_lpae(pgdp, (u64)(page_to_phys(pmdp) | prot));
}

static inline unsigned long  smmu_pgd_addr_end_lpae(unsigned long addr,
		unsigned long end)
{
	unsigned long boundary = (addr + SMMU_PGDIR_SIZE) & SMMU_PGDIR_MASK;
	return (boundary - 1 < end - 1) ? boundary : end;
}

static inline unsigned long  smmu_pmd_addr_end_lpae(unsigned long addr,
		unsigned long end)
{
	unsigned long boundary = (addr + SMMU_PMDIR_SIZE) & SMMU_PMDIR_MASK;
	return (boundary - 1 < end - 1) ? boundary : end;
}

int hisi_smmu_handle_mapping_lpae(struct iommu_domain *domain,
		unsigned long iova, phys_addr_t paddr,
		size_t size, int prot);

unsigned int hisi_smmu_handle_unmapping_lpae(struct iommu_domain *domain,
		unsigned long iova, size_t size);

#endif
