
#include <hi_psam.h>
#include <bsp_psam.h>
#include <osl_common.h>
#include <libfdt.h>

#define BIT(x)						(1 << (x))
#define PSAM_SRST_BIT				BIT(0)
#define PSAM_IDLE_BIT				BIT(1)

#define ERROR						(-1)
#define PSAM_BAK_BASE_REGS_CNT			19
#define PSAM_BAK_ADDR_LIMIT_REGS_CNT	10


void *g_psam_reg_base = NULL;
static unsigned int psam_addr_limit = 0;

#ifndef CONFIG_IPF_PROPERTY_MBB
//先这样写，为了适应类似IPF 在m3分配空间或者v7上用share ddr空间
__ao_data unsigned int g_u32_psam_setting_bak_space[PSAM_BAK_BASE_REGS_CNT];
__ao_data unsigned int g_u32_psam_addr_limit_bak_space[PSAM_BAK_ADDR_LIMIT_REGS_CNT];

__ao_data unsigned int* g_u32_psam_setting_bak_addr = g_u32_psam_setting_bak_space;
__ao_data unsigned int* g_u32_psam_addr_limit_bak_addr = g_u32_psam_addr_limit_bak_space;

#else
__ao_data unsigned int* g_u32_psam_setting_bak_addr = (unsigned int*)PSAM_BASE_CRG_BAK_ADDR;
__ao_data unsigned int* g_u32_psam_addr_limit_bak_addr = (unsigned int*)PSAM_ADDR_LIMIT_BAK_ADDR;

#endif


__ao_data unsigned int g_psam_setting_table[] =
{
	HI_PSAM_CONFIG_OFFSET,
	HI_PSAM_INT0_MASK_OFFSET,
	HI_PSAM_INT1_MASK_OFFSET,
	//cipher
	HI_PSAM_CRDQ_CTRL_OFFSET,
	//restore by cipher call psam func(bsp_psam_cipher_ch_srst())
#if 0
	HI_PSAM_CBDQ_CONFIG_OFFSET,
	HI_PSAM_CBDQ_BADDR_OFFSET,
	HI_PSAM_CBDQ_SIZE_OFFSET,
	HI_PSAM_CBDQ_WPTR_ADDR_OFFSET,
	HI_PSAM_CRDQ_RPTR_ADDR_OFFSET,
#endif
	//ibdq
	HI_PSAM_IBDQ_BADDR_OFFSET,
	HI_PSAM_IBDQ_SIZE_OFFSET,
	HI_PSAM_IBDQ_WPTR_ADDR_OFFSET,
	HI_PSAM_IBDQ_RPTR_ADDR_OFFSET,
	HI_PSAM_IBDQ_RPTR_TIMER_OFFSET,
	HI_PSAM_IBDQ_PKT_CNT_OFFSET,
	//lbdq
	HI_PSAM_LBDQ_BADDR_OFFSET,
	HI_PSAM_LBDQ_SIZE_OFFSET,
	//adq
	HI_PSAM_ADQ_CTRL_OFFSET,
	HI_PSAM_ADQ0_BASE_OFFSET,
	HI_PSAM_ADQ0_RPTR_OFFSET, 
	HI_PSAM_ADQ0_WPTR_OFFSET, 
	HI_PSAM_ADQ1_BASE_OFFSET,
	HI_PSAM_ADQ1_WPTR_OFFSET,
	HI_PSAM_ADQ1_RPTR_OFFSET
};

__ao_data unsigned int g_psam_addr_limit_table[] =
{
	//addr limit
	HI_PSAM_ADQ_PADDR_ERR_OFFSET,
	HI_PSAM_ADQ_PADDR_STR0_OFFSET,
	HI_PSAM_ADQ_PADDR_END0_OFFSET,
	HI_PSAM_ADQ_PADDR_STR1_OFFSET,
	HI_PSAM_ADQ_PADDR_END1_OFFSET,
	HI_PSAM_ADQ_PADDR_STR2_OFFSET,
	HI_PSAM_ADQ_PADDR_END2_OFFSET,
	HI_PSAM_ADQ_PADDR_STR3_OFFSET,
	HI_PSAM_ADQ_PADDR_END3_OFFSET,
	HI_PSAM_ADQ_PADDR_CTRL_OFFSET
};


int	bsp_psam_init(void)
{
    struct device_node *node;
	node = of_find_compatible_node(NULL, NULL, "hisilicon,psam_balong_m3");
	if (!node)
	{
		return ERROR;
	}

	g_psam_reg_base = of_iomap(node, 0);
	if (NULL == g_psam_reg_base)
	{
		return ERROR;
	}

	(void)of_property_read_u32_array(node, "addr_limit", &psam_addr_limit, 1);
	
	return 0;
}


static unsigned int psam_idle(void)
{
	unsigned int status;
	status = readl((unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
	status &= PSAM_IDLE_BIT;
	
	return status;
}


static int psam_sw_srst(void)
{
	unsigned int count = 10000;
	unsigned int reg_v = 1;

	writel(reg_v, (unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
	while(reg_v & PSAM_SRST_BIT){
		reg_v = readl((unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
		if(count == 0){
			return ERROR;
		}
		count--;
	}
	return 0;
}


int psam_bakup_reg(void)
{
    unsigned int* u32_addr = NULL;
    unsigned int i = 0;
    unsigned int u32_total = 0;

    /* idle */  	    
    if(psam_idle() != PSAM_IDLE_BIT)
    {
        return ERROR;
    }

	/*ad 不用disable 因为ad预取没有改变ad的读指针*/
    /* 保存必要的寄存器 */
    u32_total = sizeof(g_psam_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_psam_setting_bak_addr;
    
    for(i=0; i<u32_total; i++)
    {
        *u32_addr = readl((unsigned int)g_psam_reg_base + g_psam_setting_table[i]);
        u32_addr ++;
    }

	//addr limit regs bak
	if(psam_addr_limit){
		u32_total = sizeof(g_psam_addr_limit_table)/sizeof(unsigned int);
	    u32_addr = g_u32_psam_addr_limit_bak_addr;
	    
	    for(i=0; i<u32_total; i++)
	    {
	        *u32_addr = readl((unsigned int)g_psam_reg_base + g_psam_addr_limit_table[i]);
	        u32_addr ++;
	    }
	}

    return 0;
}



void psam_restore_reg(void)
{
    unsigned int* u32_addr = NULL;
    unsigned int i = 0;
    unsigned int u32_total = 0;

	writel(0, (unsigned int)g_psam_reg_base + HI_PSAM_EN_OFFSET);
//reset psam
    psam_sw_srst();

//restore registers
    u32_total = sizeof(g_psam_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_psam_setting_bak_addr;

    for(i=0; i<u32_total; i++)
    {
        writel(*u32_addr, (unsigned int)g_psam_reg_base + g_psam_setting_table[i]);        
        u32_addr ++;
    }

//restore addr limit regs
	if(psam_addr_limit){
		u32_total = sizeof(g_psam_addr_limit_table)/sizeof(unsigned int);
	    u32_addr = g_u32_psam_addr_limit_bak_addr;

		for(i=0; i<u32_total; i++)
		{
			writel(*u32_addr, (unsigned int)g_psam_reg_base + g_psam_addr_limit_table[i]); 	   
			u32_addr ++;
		}
	}

//psam enable after restore all psam registers
    writel(1, (unsigned int)g_psam_reg_base + HI_PSAM_EN_OFFSET);        
}

