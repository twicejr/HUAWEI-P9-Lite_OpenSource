/*--------------------------------------------------------------------------------------------------------------------------
*此文件主要是实现简缩系统的启动
*说明功能:完成L1\L2cache的初始化并打开L2
*         设置页表并将页表放置在低端，开启MMU
*         启动L2筛片用例
*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file main_mini.c
*
*
* 描述：启动流程主程序。
*/

#include "l2cache_screening.h"

#define MMU_BUFFERABLE       (1<<2)
#define MMU_BUFFERABLE_NOT   (0<<2)
#define MMU_CACHEABLE        (1<<3)
#define MMU_CACHEABLE_NOT    (0<<3)
#define MMU_WRITE_ALLOC      (1<<12)
#define MMU_WRITEABLE        ((1<<10)|(0<<11))
#define MMU_WRITEABLE_NOT    ((0<<10)|(0<<11))
#define MMU_SECT_SIZE        (0x100000)

#define ROUND_UP(x, align)	(((int) (x) + (align - 1)) & ~(align - 1))

/*映射相关结构体*/
typedef struct
{
    unsigned int viraddr;    /*虚拟地址*/
    unsigned int phyaddr;    /*物理地址*/
    unsigned int memsize;    /*空间大小*/
    unsigned int bitconfig;  /*地址空间的属性*/
}MMU_DES_CONFIG;

const MMU_DES_CONFIG mmu_desc_array[]=
{
    {
        DDR_MCORE_ADDR,
        DDR_MCORE_ADDR,
        ROUND_UP (DDR_MCORE_SIZE, MMU_SECT_SIZE),
        (MMU_WRITEABLE) | (MMU_CACHEABLE) | (MMU_BUFFERABLE) | (MMU_WRITE_ALLOC)
    },
#ifdef CONFIG_BALONG_L2CACHE
    {
        L2_CTRL_BASE,
        L2_CTRL_BASE,
        ROUND_UP(MMU_SECT_SIZE, MMU_SECT_SIZE),
        (MMU_WRITEABLE)
    },
#endif
    {
        HI_MDM_GIC_BASE_ADDR, /* MPCore functions including SCU */
        HI_MDM_GIC_BASE_ADDR,
        ROUND_UP(MMU_SECT_SIZE, MMU_SECT_SIZE),
        (MMU_WRITEABLE)
    }
};

#ifdef CONFIG_BALONG_L2CACHE
void  set_a9_aux_ctrl( unsigned int bit , unsigned int bool)
{
    unsigned int reg = 0;
    MINI_OS_ASM("mrc p15, 0, %0, c1, c0, 1" : "=r" (reg) );

    if(bool==1)
        { reg = reg|(0x1<<bit);}
    else
        { reg = reg &(~(0x1<<bit)) ;}
    MINI_OS_ASM("mcr p15, 0, %0, c1, c0, 1" : : "r" (reg));

	MINI_OS_ASM("dsb" : : : "memory");
	MINI_OS_ASM("isb" : : : "memory");

}
void l2cache_sync_mini(void)
{
	ARMA9CTX_REGISTER_WRITE(L2_CACHE_SYNC, 0);
	MINI_OS_ASM ("dsb" : : : "memory");
	MINI_OS_ASM ("isb" : : : "memory");
}
void l2cache_flush_mini(void)
{
    ARMA9CTX_REGISTER_WRITE(L2_CLEAN_WAY, L2_WAY_ALL);

    /* poll state until the background flush operation  is complete */

    while (ARMA9CTX_REGISTER_READ(L2_CLEAN_WAY) & L2_WAY_ALL);

    l2cache_sync_mini();
}

void l2cache_enable_mini(void)
{
    /* invalidate the whole L2 cache */
    ARMA9CTX_REGISTER_WRITE(L2_INVALIDATE_WAY, L2_WAY_ALL);

    l2cache_sync_mini();

    /* poll state until the background invalidate operation is complete */
    while (ARMA9CTX_REGISTER_READ(L2_INVALIDATE_WAY) & L2_WAY_ALL);

    l2cache_sync_mini();

    /* clear all pending interrupts */
    ARMA9CTX_REGISTER_WRITE(L2_INT_CLEAR,L2_INT_CLEAR_ALL);

    /* mask all interrupts */
    ARMA9CTX_REGISTER_WRITE(L2_INT_MASK,L2_INT_MASK_ALL);
     /* enable L2 cache */
    ARMA9CTX_REGISTER_WRITE(L2_CONTROL,L2_CONTROL_ENABLE);
    MINI_OS_ASM("dsb" : : : "memory");
	MINI_OS_ASM("isb" : : : "memory");
}

void l2cache_init_mini(void)
{
    unsigned int uwsctrl = 0;
    unsigned int reg = 0;
    unsigned int scu_reg_base = 0;

   /*disable L1 cache*/
   MINI_OS_ASM("mrc p15,0,%0,c1,c0,0 \n\
             bic %0,%0,#(1 << 2) \n\
             bic %0,%0,#(1 << 12) \n\
             ":"+r"(uwsctrl)::"memory");
             
   /*disable L2 cache*/
    ARMA9CTX_REGISTER_WRITE(L2_CONTROL, 0x0); /* disable L2 cache */
    (void)l1cache_inv_all_mini();

    /* invalidate the whole L2 cache through way operation  */
    ARMA9CTX_REGISTER_WRITE(L2_INVALIDATE_WAY, L2_WAY_ALL);
    
    /* poll state until the background invalidate operation  is complete */
    while (ARMA9CTX_REGISTER_READ(L2_INVALIDATE_WAY) & L2_WAY_ALL);
    
    l2cache_sync_mini();
    
    /* clear all pending interrupts */
    ARMA9CTX_REGISTER_WRITE(L2_INT_CLEAR, L2_INT_CLEAR_ALL);
    
    /* mask all interrupts */
    ARMA9CTX_REGISTER_WRITE(L2_INT_MASK, L2_INT_MASK_ALL);
    l1cache_enable_mini();

    /*enable L2cache*/
    /* l2cache config for optimize*/
    reg = ARMA9CTX_REGISTER_READ(L2_AUX_CONTROL);
    reg = reg|AUX_INSTR_PREFETCH|AUX_DATA_PREFETCH|AUX_EARLY_BRESP;
    reg = reg|AUX_FULL_LINE_OF_ZERO; /*AUX_FULL_LINE_OF_ZERO*/
    ARMA9CTX_REGISTER_WRITE(L2_AUX_CONTROL, reg);

    reg = ARMA9CTX_REGISTER_READ(L2_PREFETCH_CTRL);
    reg = reg|PREF_DOUBLE_LINEFILL|PREF_INSTR_PREFETCH|PREF_DATA_PREFETCH|PREF_PREFETCH_OFFSET|PREF_PREFETCH_DROP;
    ARMA9CTX_REGISTER_WRITE(L2_PREFETCH_CTRL, reg);

    reg = ARMA9CTX_REGISTER_READ(L2_POWER_CTRL);
    reg = reg|POWER_CLK_GATING|POWER_STANDBY_MODE;
    ARMA9CTX_REGISTER_WRITE(L2_POWER_CTRL, reg);

    /*enable SCU*/
    MINI_OS_ASM("mrc p15, 4, %0, c15, c0, 0" : "=r" (scu_reg_base) );
    scu_reg_base &= 0xffffe000; /* get scu reg base - bit[31:13]*/

    reg = ARMA9CTX_REGISTER_READ(scu_reg_base+SCU_CTRL_OFFSET);
    reg= reg|SCU_CTRL_CONFIG;
    ARMA9CTX_REGISTER_WRITE(scu_reg_base+SCU_CTRL_OFFSET, reg);
	MINI_OS_ASM("dsb" : : : "memory");
	MINI_OS_ASM("isb" : : : "memory");
    ARMA9CTX_REGISTER_WRITE(L2_CONTROL, L2_CONTROL_ENABLE); /* enable L2 cache */
	MINI_OS_ASM("dsb" : : : "memory");

    /* after l2 full line zero enabled */
    set_a9_aux_ctrl(BIT_A9_FULL_LINE, 1); /*AUX_FULL_LINE_OF_ZERO*/

    set_a9_aux_ctrl(BIT_A9_L2_PREFETCH_HINTS, 1); /*  */
    set_a9_aux_ctrl(BIT_A9_L1_PREFETCH, 1); /* config anywhere */
	MINI_OS_ASM("dsb" : : : "memory");
	MINI_OS_ASM("isb" : : : "memory");
}
#else
void l1_cache_init_mini(void)
{
    unsigned int uwsctrl = 0;
   /*disable L1 cache*/
   MINI_OS_ASM("mrc p15,0,%0,c1,c0,0 \n\
             bic %0,%0,#(1 << 2) \n\
             bic %0,%0,#(1 << 12) \n\
             ":"+r"(uwsctrl)::"memory");
  (void)l1cache_inv_all_mini();
  l1cache_enable_mini();
}
#endif
void mmu_table_set_mini(void)
{
    unsigned int i,j;
    unsigned int tablenum;
    unsigned int sectdescriptor;
    unsigned int *desaddr;
    unsigned int secttblsize = 0x4000;
    unsigned int ulMmuTlbBaseAddr;
    unsigned int ulMmuSectDesNum = sizeof(mmu_desc_array)/sizeof(MMU_DES_CONFIG);

    /* tlb addr must be 16KB aligned */
    ulMmuTlbBaseAddr = (unsigned int )MINI_TLB_BASE_ADDR;

    /*clear the baseaddr area to 0*/
    desaddr= (unsigned int *)ulMmuTlbBaseAddr;
    memset_s((void*)(ulMmuTlbBaseAddr),secttblsize,0,secttblsize);

    for (i = 0; i < ulMmuSectDesNum; i++) {
        tablenum = mmu_desc_array[i].memsize/MMU_SECT_SIZE;

        for (j = 0; j < tablenum; j++) {
               desaddr = (unsigned int *)(ulMmuTlbBaseAddr |
                          (((mmu_desc_array[i].viraddr +
                          (j*MMU_SECT_SIZE))>>18) & 0x00003ffc));
                sectdescriptor = (mmu_desc_array[i].phyaddr +
                                 (j*MMU_SECT_SIZE)) |
                                 mmu_desc_array[i].bitconfig | 0x02;
                *desaddr = sectdescriptor;
        }
    }
}
void mmu_enable_mini(unsigned int tlb_address)
{
    /*write DACR in MMU*/
	MINI_OS_ASM ("mov r2,#1");
	MINI_OS_ASM ("mcr p15,0,r2,c3,c0,0");
	MINI_OS_ASM ("isb");

	/*write TTBCR*/
	MINI_OS_ASM ("mov r2,#0");
	MINI_OS_ASM ("mcr p15,0,r2,c2,c0,2");
	MINI_OS_ASM ("isb");

	/*set TTBR0,r0 from input*/
	MINI_OS_ASM ("mcr p15,0,r0,c2,c0,0");
	MINI_OS_ASM ("isb");

	/*set SCTRL disable TRE and AFE*/
	MINI_OS_ASM ("mrc p15,0,r0,c1,c0,0");
	MINI_OS_ASM ("isb");
	MINI_OS_ASM ("bic r0,r0,#0x10000000");
	MINI_OS_ASM ("bic r0,r0,#0x20000000");
	MINI_OS_ASM ("mcr p15,0,r0,c1,c0,0");
	MINI_OS_ASM ("isb");

	/*invalidate entire unified TLB*/
	MINI_OS_ASM ("mov r0,#0");
	MINI_OS_ASM ("mcr p15,0,r0,c8,c7,0");
	MINI_OS_ASM ("isb");
    /*enable MMU*/
    MINI_OS_ASM ("mrc p15,0,r0,c1,c0,0");
	MINI_OS_ASM ("isb");
    MINI_OS_ASM ("orr r0,r0,#0x01");
	MINI_OS_ASM ("mcr p15,0,r0,c1,c0,0");
}


void main_mini(void)
{
    mmu_table_set_mini();
    mmu_enable_mini((unsigned int)MINI_TLB_BASE_ADDR);
#ifdef CONFIG_BALONG_L2CACHE
	l2cache_init_mini();
#else
    l1_cache_init_mini();
#endif
    cache_screening_case();
}

