#ifndef _IVP_CORE_H_
#define _IVP_CORE_H_

#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/miscdevice.h>
#include <linux/regulator/consumer.h>

struct ivp_iomem_res {
    char __iomem *cfg_base_addr;
    char __iomem *pctrl_base_addr;
    char __iomem *pericrg_base_addr;
    char __iomem *gic_base_addr;
};

struct ivp_device {
    struct ivp_iomem_res io_res;
    struct clk * clk;
    unsigned int clk_rate;
    unsigned int wdg_irq;
    atomic_t wdg_sleep;
    unsigned int dwaxi_dlock_irq;
    struct semaphore wdg_sem;
    int sect_count;
    struct ivp_sect_info *sects;
    struct dentry *debugfs;
    struct miscdevice device;
    struct regulator *regulator;
    unsigned long       smmu_pgd_base;
    struct ivp_smmu_dev *smmu_dev;
    atomic_t accessible;
};

extern u32 ivp_reg_read(unsigned int off);
extern void ivp_reg_write(unsigned int off, u32 val);
extern u32 ivp_wdg_reg_read(unsigned int off);
extern void ivp_wdg_reg_write(unsigned int off, u32 val);
extern u32 ivp_smmu_reg_read(unsigned int off);
extern u32 ivp_pctrl_reg_read(unsigned int off);

#endif /* _IVP_CORE_H_ */
