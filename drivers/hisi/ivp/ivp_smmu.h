
#ifndef _IVP_SMMU_H_
#define _IVP_SMMU_H_

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/mm.h>
#include <linux/iommu.h>
#include <linux/hisi/hisi-iommu.h>
#include <dsm/dsm_pub.h>



enum smmu_arch_version {
	SMMU_ARCH_VER_10 = 1,   //SMMU arch v1.0
	SMMU_ARCH_VER_20,       //SMMU arch v2.0
};

enum smmu_state {
	SMMU_STATE_DISABLE,     //SMMU disable
	SMMU_STATE_ENABLE,      //SMMU enable
};
      
struct ivp_smmu_dev{
    struct iommu_domain *domain;
    struct device  *dev;
	void __iomem   *reg_base;
    unsigned long   reg_size;
	unsigned long   pgd_base;
    spinlock_t      spinlock;
	irq_handler_t   isr;
	unsigned int    version;
	unsigned int    irq;
	unsigned int    state;
	unsigned int    cbidx;  //context bank index
	unsigned int	vmid;   //virtual machine id
	unsigned int	cbar;   //context bank attribute
};

#ifdef CONFIG_IVP_SMMU
int  ivp_smmu_invalid_tlb(struct ivp_smmu_dev *smmu_dev, unsigned int vmid);
void ivp_smmu_flush_pgtable(struct ivp_smmu_dev *smmu_dev, void *addr, size_t size);
int  ivp_smmu_trans_enable(struct ivp_smmu_dev *smmu_dev);
int  ivp_smmu_trans_disable(struct ivp_smmu_dev *smmu_dev);
int  ivp_smmu_set_pgd_base(struct ivp_smmu_dev *smmu_dev, unsigned long pgd_base);
struct ivp_smmu_dev *ivp_smmu_get_device(unsigned long select);
#else
static inline int ivp_smmu_invalid_tlb(struct ivp_smmu_dev *smmu_dev, 
        unsigned int vmid)
{
    return -1;
}

static inline void ivp_smmu_flush_pgtable(struct ivp_smmu_dev *smmu_dev, void *addr, size_t size)
{
    return;
}

static inline int ivp_smmu_trans_enable(struct ivp_smmu_dev *smmu_dev)
{
    return -1;
}

static inline int ivp_smmu_trans_disable(struct ivp_smmu_dev *smmu_dev)
{
    return;
}

static inline struct ivp_smmu_dev *ivp_smmu_get_device(unsigned long select)
{
    return NULL;
}

int  ivp_smmu_set_pgd_base(struct ivp_smmu_dev *smmu_dev, unsigned long pgd_base)
{
    return -1;
}
#endif
#endif /* _IVP_SMMU_H_  */
