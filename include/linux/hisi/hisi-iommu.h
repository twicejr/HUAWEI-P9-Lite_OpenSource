#ifndef _HI36XX_SMMU_H
#define _HI36XX_SMMU_H

#include <linux/types.h>
struct iommu_domain_data {
	unsigned int     iova_start;
	unsigned int     iova_size;
	phys_addr_t      phy_pgd_base;
	struct list_head list;
};

#endif
