
#include <linux/mtd/hisi_nve_number.h>

#define ETB_NVE_NUMBER NVE_ETB_NUM

#define UNLOCK_MAGIC	(0xC5ACCE55)
#define TIMEOUT (100000)
#define ALWAYS_TRUE (0x6F)

#define SOC_Modem_A9_ROM_TABLE_BASE_ADDR	(0xF6600000)
#define SOC_ACPU_ROM_TABLE_BASE_ADDR	(0xF6500000) 
#define SOC_SC_ON_BASE_ADDR		(0xF7410000)
/*Ê±ÖÓ·ÖÆµ¼Ä´æÆ÷ATB DAP TPIU*/
#define SC_CLKCFG8BIT9 (0xF711ACC8)

/****cpu_base****/
#define CCPU_BASE SOC_Modem_A9_ROM_TABLE_BASE_ADDR
#define ACPU_BASE SOC_ACPU_ROM_TABLE_BASE_ADDR

/*******ETM_base*********/
#define	ETM_BASE (0x1C000)

/*******main control register**************/
#define ETM_ETMCR(base) ( (base)  +  (0x000))
#define ETM_ETMSR(base) ( (base)+  (0x010))
#define ETM_ETMTRIGGER(base) ((base) + (0x008))
#define ETM_ETMSCR(base) ( (base) +  (0x014))

#define ETM_ETMTRACEIDR(base) ((base) + (0x200))

#define ETM_ETMPDCR(base) ((base) + (0x310))

/******TraceEnable Configuration*******/
#define	ETM_ETMTSSCR(base)	((base) + (0x018))
#define	ETM_ETMTEEVR(base)	((base) + (0x020))
#define	ETM_ETMTECR1(base)	((base) + (0x024))

/******COUNTER************/
#define COUNTER_VALUE1 (0x1F4)

#define ETM_ETMCNTRLDVR1(base)	((base) + (0x140))
#define ETM_ETMCNTENR1(base)	((base) + (0x150))
#define ETM_ETMCNTRELDEVR1(base)	((base) + (0x160))
#define ETM_ETMCNTVR1(base)	((base) + (0x170))

#define COUNTER_VALUE2 (0xFFFF)
#define ETM_ETMCNTRLDVR2(base)	((base) + (0x144))
#define ETM_ETMCNTENR2(base)	((base) + (0x154))
#define ETM_ETMCNTRELDEVR2(base)	((base) + (0x164))
#define ETM_ETMCNTVR2(base)	((base) + (0x174))

/******lock**********/
#define ETM_ETMLAR(base)	((base) + (0xFB0))
#define ETM_ETMLSR(base)	((base) + (0xFB4))
/******Timestamp Event Register*****/
#define ETM_ETMTSEVR(base)	((base) + (0x1F8))

/********484***********/
//#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR(base) ((base) + (0x484)) 
#define ETM_SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR \
	SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)


/*************************/
#define BIT(nr) (1UL << (nr))

#define REG_SET_BIT(reg, bit)	do{writel((readl(reg) |BIT(bit)),reg);}while(0)
#define REG_CLEAR_BIT(reg, bit)	do{writel((readl(reg) & ~(BIT(bit))),reg);}while(0)
#define REG_TEST_BIT(reg, bit)	(readl(reg) & (BIT(bit)))

#define ETMPDCR_POWERUP (3)
#define ETMCR_POWERDOWN (0)
#define ETMCR_PROGBIT (10)
#define ETMCR_TIMESTAMPENABLE (28)
#define ETMSR_PROGBIT (1)

#define etm_unlock(base) do{writel(UNLOCK_MAGIC,ETM_ETMLAR(base));}while(0)
#define etm_lock(base) do{writel(0x0,ETM_ETMLAR(base));}while(0)

struct etb_platform_data
{
	phys_addr_t iobase;     /*etm register physical address*/
	size_t size;            /*etm register space size*/
};

void  enable_etm_reset(void);


