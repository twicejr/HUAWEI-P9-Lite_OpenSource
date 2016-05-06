/*********************************************************************************************
  physical registers read, write functions
*********************************************************************************************/

#ifndef __REG_OPS_H__
#define __REG_OPS_H__

/* Header file */
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include "linux/printk.h"

#include "linux/io.h"
#include "linux/spinlock.h"
#include "soc_baseaddr_interface.h"


/* Macro define */
#define CALC_REG_OFFSET 0

#define CALC_REG_MASK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)


/* Function declaration */
/**********************************************
 * write value to physic registers
 * base_addr: physical register base addr
        Range{ SOC_SC_OFF_BASE_ADDR,
               SOC_SC_ON_BASE_ADDR,
               SOC_PMCTRL_BASE_ADDR,
               SOC_IOC_ON_BASE_ADDR }
 * reg_offset: offset of the register
 * start_bit: write value start bit
 * end_bit: write value end bit
 * val: write value
 *********************************************/
static inline void phy_reg_writel(unsigned int base_addr,
		     unsigned int reg_offset,
		     unsigned char start_bit,
		     unsigned char end_bit,
		     unsigned int val)
{
    int read_val = 0;
    unsigned int comm_base_addr = 0;
    unsigned long flags;
    static spinlock_t reg_lock = SPIN_LOCK_UNLOCKED;

    comm_base_addr = HISI_VA_ADDRESS(base_addr);
    //comm_base_addr = ioremap(base_addr);

    WARN_ON(0 == comm_base_addr);

    spin_lock_irqsave(&reg_lock, flags);
    //read_val = readl(comm_base_addr + reg_offset) & ~(CALC_REG_MASK(start_bit, end_bit));
    read_val = readl((unsigned int*)(comm_base_addr + reg_offset)) & ~(CALC_REG_MASK(start_bit, end_bit));
    read_val |= (CALC_REG_MASK(start_bit, end_bit) & (val << start_bit));
    //writel(read_val, comm_base_addr + reg_offset);
    writel(read_val, (unsigned int*)(comm_base_addr + reg_offset));

    spin_unlock_irqrestore(&reg_lock, flags);

    return;
}


/**********************************************
 * read value from physical registers
 * base_addr: physical register base addr
        Range{ SOC_SC_OFF_BASE_ADDR,
               SOC_SC_ON_BASE_ADDR,
               SOC_PMCTRL_BASE_ADDR,
               SOC_IOC_ON_BASE_ADDR }
 * reg_offset: offset of the register
 * start_bit: read value start bit
 * end_bit: read value end bit
 *********************************************/
static inline unsigned int phy_reg_readl(unsigned int base_addr,
			    unsigned int reg_offset,
			    unsigned char start_bit,
			    unsigned char end_bit)
{
    unsigned int val = 0;
    unsigned int comm_base_addr = 0;

    comm_base_addr = HISI_VA_ADDRESS(base_addr);
   // comm_base_addr = ioremap(base_addr);

    WARN_ON(0 == comm_base_addr);

    //val = readl(comm_base_addr + reg_offset);
    val = readl((unsigned int*)(comm_base_addr + reg_offset));
    val &= CALC_REG_MASK(start_bit, end_bit);

    return val >> start_bit;
}

#endif

