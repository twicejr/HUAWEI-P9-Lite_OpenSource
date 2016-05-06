/*********************************************************************************************
  physical registers read, write functions
*********************************************************************************************/

#ifndef __VIDEO_REG_OPS_H__
#define __VIDEO_REG_OPS_H__

/* Header file */
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include "linux/printk.h"

#include "linux/io.h"
#include "linux/spinlock.h"
#include <linux/vmalloc.h>


/* Macro define */
#define CALC_REG_OFFSET 0

#define CALC_REG_MASK(bit_start, bit_end) \
    (((0x1L << (bit_end - bit_start + 1)) - 1) << bit_start)

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
    u8 __iomem * comm_base_addr = 0;
    unsigned long flags;
    static spinlock_t reg_lock = SPIN_LOCK_UNLOCKED;

    comm_base_addr = (u8 __iomem *)HISI_VA_ADDRESS(base_addr);
    //comm_base_addr = ioremap(base_addr);

    WARN_ON(0 == comm_base_addr);

    spin_lock_irqsave(&reg_lock, flags);
    //read_val = readl(comm_base_addr + reg_offset) & ~(CALC_REG_MASK(start_bit, end_bit));
    read_val = readl((comm_base_addr + reg_offset)) & ~(CALC_REG_MASK(start_bit, end_bit));
    read_val |= (CALC_REG_MASK(start_bit, end_bit) & (val << start_bit));
    //writel(read_val, comm_base_addr + reg_offset);
    writel(read_val, (comm_base_addr + reg_offset));

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
    u8 __iomem *comm_base_addr = 0;

    comm_base_addr = (u8 __iomem *)HISI_VA_ADDRESS(base_addr);
   // comm_base_addr = ioremap(base_addr);

    WARN_ON(0 == comm_base_addr);

    //val = readl(comm_base_addr + reg_offset);
    val = readl(comm_base_addr + reg_offset);
    val &= CALC_REG_MASK(start_bit, end_bit);

    return val >> start_bit;
}

static inline void *mem_remap_type(unsigned long phys_addr, size_t size, pgprot_t pgprot)
{
	int i;
	u8* vaddr = NULL;
	int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
	unsigned long offset = phys_addr & (PAGE_SIZE - 1);
	struct page **pages;

	pages = vmalloc(sizeof(struct page *) * npages);
	if (!pages)
	{
		printk(KERN_ERR "%s: vmalloc return NULL!\n", __FUNCTION__);
		return NULL;
	}

	pages[0] = phys_to_page(phys_addr);

	for (i = 0; i < npages - 1 ; i++) {
		pages[i + 1] = pages[i] + 1;
	}

	vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot);
	if(vaddr == NULL)
	{
		printk(KERN_ERR "%s: vmap return NULL!\n", __FUNCTION__);
	}
	else
	{
		vaddr += offset;
	}
	
	vfree(pages);
	printk(KERN_DEBUG "%s: phys_addr:0x%08lx size:0x%08lx npages:%d vaddr:%p offset:0x%08lx\n",
        __FUNCTION__, phys_addr, (unsigned long)size, npages, vaddr, offset);

	return (void *)vaddr;
}
#define video_ioremap_nocache(phys_addr, size) mem_remap_type(phys_addr, size, pgprot_noncached(PAGE_KERNEL))
#define video_ioremap(phys_addr, size) mem_remap_type(phys_addr, size, PAGE_KERNEL)
#define video_iounmap(vaddr) vunmap(vaddr)

#endif

