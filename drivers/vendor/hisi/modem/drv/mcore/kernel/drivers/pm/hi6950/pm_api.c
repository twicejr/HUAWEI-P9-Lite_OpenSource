/*----------------------------------------------------------------------------
 *      balongv7r5 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r5 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_irq.h"
#include <hi_base.h>
#include "soc_interrupts_m3.h"
#include "drv_edma_enum.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "bsp_dsp.h"
#include "bsp_shared_ddr.h"
#include "bsp_softtimer.h"
#include "bsp_hardtimer.h"
#include "bsp_tsensor.h"
#include "edma_balong.h"
#include "dpm_balong.h"
#include "ios_pd.h"
#include "wdt_balong.h"
#include "m3_cpufreq.h"
#include "m3_pm.h"
#include "pm_api.h"
#include "cpufreq_api.h"
#include "bsp_dfs_training.h"

/*lint --e{40, 63, 409, 438} */
extern T_PM_ST gPmSt;
extern T_PM_BAKEUP_ST gPmBakeupSt;
extern T_PM_COUNT_ST gPmCountSt;
extern T_PM_ERROR_ST gPmErrorSt;
extern DRV_NV_PM_TYPE gPmNvSt;
extern u32 sys_initial;
extern u32 uart_delay_flag;
extern struct m3_pm_stamp *m3_pm_stamps;

//#include "bsp_pm_om.h"
#ifndef bsp_pm_log_type
#define bsp_pm_log_type(a,b,c,d)
#endif

struct crg_clk_bak
{
    u32 crg_dfs1_ctrl1;
    u32 crg_dfs1_ctrl2;
    u32 crg_dfs1_ctrl3;
    u32 pd_crg_clkdiv2;
};

u32 tcxo = 0;
struct crg_clk_bak clk_bak = {0};
u32 m3_record_num = 0;
u32 m3_wakeup_flag = 0;
u32 g_buck3on_txco_on = 1;

T_PM_DDRC gddrreg;

extern DRV_DRX_DELAY_STRU gNvDrxDelaySt;

static void pm_mcu_bakeup_debug(void);
static void pm_mcu_wakeup_debug(void);




/* irqs that can wakeup from deepsleep */
u32 pm_deepsleep_irq[]={M3_TIMER7_INT,/*35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,*/\
M3_CCPU_WAKEUP_INTR,M3_ACPU_WAKEUP_INTR/*,M3_CM3_DBG_WAKE_INT*/}; // todo need or not ?
#define DS_IRQ_NUM sizeof(pm_deepsleep_irq)/sizeof(pm_deepsleep_irq[0])

/*PWR_CTRL16 , PWR_CTRL17*/  /*0x1FFFE0  -- all timer*/
u32 pm_mcore_wsrc[WSRC_REG_NUM]={\
                M3_WSRC_0_TIMER7\
                ,/*M3_WSRC_1_DEBUG|*/M3_WSRC_1_CCPU|M3_WSRC_1_ACPU\
                };
/*PWR_CTRL24 , PWR_CTRL25*/
u32 pm_acore_wsrc[WSRC_REG_NUM]={\
                APPA9_WSRC_0_IPC0|APPA9_WSRC_0_IPC1|APPA9_WSRC_0_RTC\
                |APPA9_WSRC_0_IPF1|APPA9_WSRC_0_TIMER0|APPA9_WSRC_0_TIMER2|APPA9_WSRC_0_PMU\
                ,/*APPA9_WSRC_1_DEBUG|*/APPA9_WSRC_1_GPIO_0|APPA9_WSRC_1_PSAM_0\
                };
/*PWR_CTRL30 , PWR_CTRL31*/
u32 pm_ccore_wsrc[WSRC_REG_NUM]={\
                MDMA9_WSRC_0_IPF0|MDMA9_WSRC_0_TIMER1|MDMA9_WSRC_0_TIMER3\
                |MDMA9_WSRC_0_TIMER4|MDMA9_WSRC_0_LDRX_CPU\
                |MDMA9_WSRC_0_TDRX_CPU|MDMA9_WSRC_0_G1_CPU|MDMA9_WSRC_0_G2_CPU\
                |MDMA9_WSRC_0_W_CPU\
                ,/*MDMA9_WSRC_1_DEBUG|*/MDMA9_WSRC_1_IPC0|MDMA9_WSRC_1_IPC1\
                };

TCM_DFS_TRAINING *pm_ddr_train = NULL;

void pm_debug_udelay (u32 ms, u32 flag)
{
    u32 start = 0;
    u32 end = 0;
    u32 tmp = 0;

    if(flag == 1)
    {
        start = bsp_get_slice_value();
        do
        {
            end = bsp_get_slice_value();
            tmp = end - start;
        }while(tmp<(ms*32));
    }

}
u32 pm_stamp_value(void)
{
    return bsp_get_slice_value();
}

/* ldo32 给 ddrphy_io 供电方案 
    睡眠时在ddr_pdown之后，先关ldo32再关buck2
    唤醒时在ddr_pup之前  ，先开buck2再开ldo32 */
void pm_ldo32_enable(void)
{
    u32 reg_value = 0;
    u32 tmp,tmp1;
    
    if(0x20 == readl(0x9001a000 + (0x5 << 2))) /* pmu version v520*/
    {
        /*buck2*/
        reg_value = readl(0x9001a000 + (0x9c << 2));
        reg_value |= (0x1<<1);
        writel(reg_value,0x9001a000 + (0x9c << 2));
        
        /* slow consume time: 28~53 slice/19.2M = 1us */
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp &= (~0x7);
        tmp |= 0x2;
        writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
        do
        {
            tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
            tmp = (tmp >> 3)&0x7;
        }while(tmp != 0x2);
        
        udelay(240-1);
        
        /*ldo32*/
        reg_value = readl(0x9001a000 + (0x96 << 2));
        reg_value |= (0x1<<1);
        writel(reg_value,0x9001a000 + (0x96 << 2));
        
        /* normal consume time: 479~512 slice/19.2M = 24us */
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp &= (~0x7);
        tmp |= 0x4;
        do{
        writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
            tmp1 = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
            tmp1 = (tmp1 & 0x78) >> 3;
        }while((tmp1 != 0x4));
        
        udelay(130-24);
    }
    
}
void pm_ldo32_disable(void)
{
    u32 reg_value = 0;
    if(0x20 == readl(0x9001a000 + (0x5 << 2))) /* pmu version v520*/
    {
        /*ldo32*/
        reg_value = readl(0x9001a000 + (0x96 << 2));
        reg_value &= ~(0x1<<1);
        writel(reg_value,0x9001a000 + (0x96 << 2));
    	/*buck2*/
        reg_value = readl(0x9001a000 + (0x9c << 2));
        reg_value &= ~(0x1<<1);
        writel(reg_value,0x9001a000 + (0x9c << 2));
    }
}

void pm_wsrc_init(void)
{
    u32 i = 0;
    
    /* wake_src is set up by PWR_CTRL for m3 */
    for(i = 0; i < WSRC_REG_NUM; i++)
    {
        writel(pm_mcore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL16+i*4);
    }
    
    /* wake_src is set up by PWR_CTRL for m3,acore,ccore */
    for(i = 0; i < WSRC_REG_NUM; i++)
    {
        writel(pm_acore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL24+i*4);
        writel(pm_ccore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL30+i*4);
    }
    (void)request_irq(M3_ACPU_WAKEUP_INTR, IntAcoreHandler, IRQF_DISABLED, "acore irq", 0);/*lint !e713*/
    (void)request_irq(M3_CCPU_WAKEUP_INTR, IntCcoreHandler, IRQF_DISABLED, "ccore irq", 0);/*lint !e713*/

    
    /*  only one wake_src: ipc. hifi do not have PWR_CTRLxx regs to set up wake_src.*/
    (void)request_irq(M3_IPCM2HIFI_0     , IntHiFiHandler, IRQF_DISABLED, "hifi irq", 0);/*lint !e713*/


}


void pm_mdma9_wsrc_set(u32 lvl)
{
    u32 val;
    switch(lvl)
    {
        /* drx timer ,timer5, irq=40 */
        case M3_TIMER5_INT:
            val = readl(M3PM_SC_BASE_AO+PWR_CTRL30);
            val |= MDMA9_WSRC_0_TIMER5;
            writel(val, M3PM_SC_BASE_AO+PWR_CTRL30);
            break;
        default:
            printk("mdma9_wsrc_set %d err\n",lvl);
            break;
    }
    return;
}
void pm_mdma9_wsrc_unset(u32 lvl)
{
    u32 val;
    switch(lvl)
    {
        /* drx timer ,timer5, irq=40 */
        case M3_TIMER5_INT:
            val = readl(M3PM_SC_BASE_AO+PWR_CTRL30);
            val &= ~(MDMA9_WSRC_0_TIMER5);
            writel(val, M3PM_SC_BASE_AO+PWR_CTRL30);
            break;
        default:
            printk("mdma9_wsrc_unset %d err\n",lvl);
            break;
    }
    return;
}



void pm_appa9_nvic_enable(void)
{
    clear_pending_irq(M3_ACPU_WAKEUP_INTR);
    enable_irq(M3_ACPU_WAKEUP_INTR);
}

void pm_appa9_nvic_disable(void)
{
    disable_irq(M3_ACPU_WAKEUP_INTR);
}

void pm_mdma9_nvic_enable(void)
{
    clear_pending_irq(M3_CCPU_WAKEUP_INTR);
    enable_irq(M3_CCPU_WAKEUP_INTR);
}

void pm_mdma9_nvic_disable(void)
{
    disable_irq(M3_CCPU_WAKEUP_INTR);
}

void pm_hifi_nvic_enable(void)
{
    clear_pending_irq(M3_IPCM2HIFI_0);
    enable_irq(M3_IPCM2HIFI_0);
}

void pm_hifi_nvic_disable(void)
{
    disable_irq(M3_IPCM2HIFI_0);
}

void pm_mdma9_pdown(void)
{
#ifndef CFG_CONFIG_M3PM_TEST
    u32 temp = 0;
    do{
        temp = readl(M3PM_SC_BASE_AO + PWR_STAT0);
    }while(!(temp&(0x1<<10)));
#endif
    /* disable clk */
    writel(0x1<<3, M3PM_SC_BASE_MDM + MDM_CRG_CLKDIS0);
    /* reset */
    writel(0x80C0, M3PM_SC_BASE_MDM + MDM_CRG_SRSTEN0);
}
void pm_mdma9_pup(void)
{
    /* enable clk */
    writel(0x1<<3, M3PM_SC_BASE_MDM + MDM_CRG_CLKEN0);
    /* unreset */
    writel(0x80C0, M3PM_SC_BASE_MDM + MDM_CRG_SRSTDIS0);
}

void pm_appa9_pdown(void)
{
#ifndef CFG_CONFIG_M3PM_TEST
    u32 temp = 0;
    do{
        temp = readl(M3PM_SC_BASE_AO + PWR_STAT0);
    }while(!(temp&(0x1<<12)));
#endif
    /* disable clk */
    writel(0x1<<26, M3PM_SC_BASE_PD + PD_CRG_CLKDIS3);
    /* iso ctrl enable */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL4);
    /* reset */
    writel(0x4001, M3PM_SC_BASE_PD + PD_CRG_SRSTEN1);
    /* mtcmos power down */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL7);
}
void pm_appa9_pup(void)
{
    u32 tmp = 0;
    /* mtcmos power up and wait for complete*/
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL6);
    do{
        tmp = readl(M3PM_SC_BASE_AO + PWR_STAT1);
        tmp = tmp & 0x1;
    }while(!tmp);
    udelay(30);

    /* enable clk */
    writel(0x1<<26, M3PM_SC_BASE_PD + PD_CRG_CLKEN3);
    /* iso ctrl disable */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL5);
    /* unreset */
    writel(0x4001, M3PM_SC_BASE_PD + PD_CRG_SRSTDIS1);
}

u32 g_hifi_pll_open_vote = 1U<<PM_PWR_VOTE_ACORE;
void pm_hifi_pll_close(u32 vote)
{
    u32 tmp = 0;
    int irq_flags = 0;

    if ((vote != PM_PWR_VOTE_ACORE) && (vote != PM_PWR_VOTE_HIFI))
        return;

    local_irq_save(irq_flags);
    g_hifi_pll_open_vote &= ~(1U << vote);
    if (!g_hifi_pll_open_vote)
    {
    	tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    	tmp |= 0x1;
    	writel(tmp, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    }
    local_irq_restore(irq_flags);
}

void pm_hifi_pll_open(u32 vote)
{
    u32 tmp = 0;
    int irq_flags = 0;

    if ((vote != PM_PWR_VOTE_ACORE) && (vote != PM_PWR_VOTE_HIFI))
        return;

    local_irq_save(irq_flags);
    if(!g_hifi_pll_open_vote)
    {
        tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
        tmp &= ~0x3E00;
        writel(tmp, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
        writel(0x28, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
        do{
    		tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    		tmp &= ((u32)0x1<<31);
    	}while(!tmp);

        tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
        tmp |= 0x200;
        writel(tmp, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    }
    g_hifi_pll_open_vote |= (1U << vote);
    local_irq_restore(irq_flags);
}

void pm_hifi_pdown(void)
{
    /* no reg to check wfi */
    /* disable clk */
    writel((0x1<<31), M3PM_SC_BASE_PD + PD_CRG_CLKDIS3);
    /* reset */
    writel((0x3<<19), M3PM_SC_BASE_PD + PD_CRG_SRSTEN2);

}
void pm_hifi_pup(void)
{
    /* unreset */
    writel((0x3<<19), M3PM_SC_BASE_PD + PD_CRG_SRSTDIS2);
    /* enable clk */
    writel((0x1<<31), M3PM_SC_BASE_PD + PD_CRG_CLKEN3);
}


/* todo: main.c 初始化时有调用*/
void pm_dsp_pll_open(u32 vote)
{
    UNUSED(vote);
    return;
}


void pm_acore_sleep()
{
    pm_appa9_pdown();
    bsp_wdt_stop_awdt();
    pm_hifi_pll_close(PM_PWR_VOTE_ACORE);
    pm_appa9_nvic_enable();
    cpufreq_set_sleepflag(CPUFREAQ_ACORE, 1);
    gPmCountSt.Acore.SleepTimes++;
}
void pm_ccore_sleep()
{
    pm_mdma9_pdown();
//    pm_dsp_pll_close((u32)PM_PWR_VOTE_CCORE);
    bsp_wdt_stop_cwdt();
    pm_mdma9_nvic_enable();
    cpufreq_set_sleepflag(CPUFREAQ_CCORE, 1);
    gPmCountSt.Ccore.SleepTimes++;
}
void pm_hifi_sleep()
{
    (void)bsp_hifi_stop();
    pm_hifi_pdown();
    pm_hifi_pll_close(PM_PWR_VOTE_HIFI);
    pm_hifi_nvic_enable();
    gPmCountSt.HiFi.SleepTimes++;
}

void pm_acore_wake()
{
    pm_hifi_pll_open(PM_PWR_VOTE_ACORE);
    bsp_wdt_restart_awdt();
    pm_appa9_pup();
    cpufreq_acore_cti_init();
    cpufreq_set_sleepflag(CPUFREAQ_ACORE, 0);
    bsp_pm_log_type(PM_OM_PMM,ACORE_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.Acore);
}
void print_acore_wsrc(void)
{
    printk("A wsrc :0x%x,0x%x\n"
        ,readl(M3PM_SC_BASE_AO + PWR_STAT16)
        ,readl(M3PM_SC_BASE_AO + PWR_STAT17));
}
void pm_ccore_wake()
{
    bsp_wdt_restart_cwdt();
//    pm_dsp_pll_open((u32)PM_PWR_VOTE_CCORE);
    pm_mdma9_pup();
    cpufreq_ccore_cti_init();
    cpufreq_set_sleepflag(CPUFREAQ_CCORE, 0);
    bsp_pm_log_type(PM_OM_PMM,CCORE_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.Ccore);
}
void print_ccore_wsrc(void)
{
    printk("C wsrc:0x%x,0x%x\n"
        ,readl(M3PM_SC_BASE_AO + PWR_STAT23)
        ,readl(M3PM_SC_BASE_AO + PWR_STAT24));
}

void pm_hifi_wake()
{
    pm_hifi_pll_open(PM_PWR_VOTE_HIFI);
    pm_hifi_pup();
    (void)bsp_hifi_restore();
    (void)bsp_hifi_run();
    bsp_pm_log_type(PM_OM_PMM,HIFI_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.HiFi);
}

u32 ddr_hit_addr = 0;
static void ddr_hit_set(void)
{
    u32 temp = 0;
    
    if(0==ddr_hit_addr)
    {
        return;
    }
    temp = 0x12345678;
    writel(temp, ddr_hit_addr);
}

static void ddr_hit_test(void)
{
    u32 temp = 0;
    if(0==ddr_hit_addr)
    {
        return;
    }
    temp = readl(ddr_hit_addr);
    if(temp != 0x12345678)
    {
        m3_pm_stamps->ddr_hit_test_out_cnt = 0x12345678;
        __asm__ __volatile__("b .");
    }
    writel(temp, ddr_hit_addr);
    temp = readl(ddr_hit_addr);
    if(temp!=0x12345678)
    {
        m3_pm_stamps->ddr_hit_test_out_cnt = 0x87654321;
        __asm__ __volatile__("b .");
    }
    m3_pm_stamps->ddr_hit_test_out_cnt++;
}


static void pm_ddr_out_sref()
{
    u32 tmp = 0;
    u32 times = 20;

    writel(0x0, MDDRC_SREFCTRL);
    do{
    tmp = readl(MDDRC_STATUS);
    tmp &= 0x1;
    }while(tmp);

    while(times)
    {
        times--;
    }
    
}
#if 1


#define M3PM_MDDRC_BASE   0x90040000
#define M3PM_DDRPHY_BASE  0x9004E000

/* store - restore */
u32 DDRC_PACK_IMPSTATUS;
u32 DDRC_PACK_RANK0DXNRDQSGDLY[4];
u32 DDRC_PACK_RANK1DXNRDQSGDLY[4];
u32 DDRC_PACK_DXNGDS[4];
u32 DDRC_PACK_DXNRDQSDLY[4];
u32 DDRC_PACK_ADDRPHBOUND;
u32 DDRC_PACK_ACADDRBDL0     ;
u32 DDRC_PACK_ACADDRBDL1     ;
u32 DDRC_PACK_ACADDRBDL2     ;
u32 DDRC_PACK_ACADDRBDL3     ;
u32 DDRC_PACK_ACADDRBDL4     ;
u32 DDRC_PACK_DXNWDQNBDL0[4] ;
u32 DDRC_PACK_DXNWDQNBDL1[4] ;
u32 DDRC_PACK_DXNWDQNBDL2[4] ;
u32 DDRC_PACK_DXNRDQNBDL0[4] ;
u32 DDRC_PACK_DXNRDQNBDL1[4] ;
u32 DDRC_PACK_DXNOEBDL[4]    ;
u32 DDRC_PACK_DXNWDQSDLY[4]  ;
u32 DDRC_PACK_DXNWDQDLY[4]   ;
u32 DDRC_PACK_DXNWLSL[4]     ;

enum dram_type{
    dram_type_lpddr2 = 2,
    dram_type_lpddr3 = 3,
};
enum dram_type get_dram_type(void)
{
#ifdef BSP_CONFIG_LPDDR2
    /* udp only support lpddr2 */
    return dram_type_lpddr2;
#elif defined(BSP_CONFIG_LPDDR3)
    return dram_type_lpddr3;
#endif    
}

u32 ddr_freq = 0;
enum tagPLL_DIV_CTRL ddr_freq_enum = DDR_FREQ_MAX;
enum ddr_mode ddr_byp_mode = 0;
u32 ddr_pdown_stamps[6];
u32 ddr_pup_stamps[12];

void get_ddr_freq_before_pdown(void)
{
    ddr_byp_mode = dfs_get_cur_mode(&ddr_freq);
    ddr_freq_enum = ddr_freq;
}

void ddr_pdown(void)
{
    u32 rd_val = 0;
    u32 n = 0;
    
    ddr_hit_set();
    get_ddr_freq_before_pdown();

    ddr_pdown_stamps[0] = pm_stamp_value();

    /* 1 */
    /* DDRC_CFG_DDRPHY phy_upden=0 */
    rd_val = readl( 0x90048200 );
    rd_val = rd_val & (~(0x1<<12));
    writel( rd_val, 0x90048200 );
    /* DDRC_CFG_LP lp_en=0 */
    rd_val = readl( 0x9004801c );
    rd_val = rd_val & (~0x1);
    writel( rd_val, 0x9004801c );
    /* DDRC_CFG_PD pd_en=0 */
    rd_val = readl( 0x90048028 );
    rd_val = rd_val & (~0x1);
    writel( rd_val, 0x90048028 );
    
    /* wait for a REFRESH_ALL cmd to lpddr(before SREF re-entr) */
    udelay(30); 

    /* 2  sref and wait&check */
    /* DDRC_CTRL_SREF sref_req=1 */
    rd_val = readl( 0x90048000);
    rd_val = rd_val|0x1;
    writel( rd_val, 0x90048000);
    
    ddr_pdown_stamps[1] = pm_stamp_value();
    
    /* DDRC_CURR_FUNC in_sref==1 */
    do{
        rd_val = readl( 0x90048294 );
    }while( (rd_val&0x1)!=0x1 );

    ddr_pdown_stamps[2] = pm_stamp_value();

    /* 3 SYSCTRL_AO(wo)  io_ddr_ret en */
    writel(0x1<<24, M3PM_SC_BASE_AO + PWR_CTRL4);

    ddr_pdown_stamps[3] = pm_stamp_value();

    /* 4  保存DDRPHY 输出阻抗、部分DLL 寄存器  */
    /* for both byp and mission mode */
    DDRC_PACK_IMPSTATUS           = readl(M3PM_DDRPHY_BASE + IMPSTATUS)                   ;
    for (n = 0; n < 4; n++)
    {
        DDRC_PACK_RANK0DXNRDQSGDLY[n] = readl(M3PM_DDRPHY_BASE + DXNRDQSGDLY + n*0x80)        ;
        DDRC_PACK_RANK1DXNRDQSGDLY[n] = readl(M3PM_DDRPHY_BASE + DXNRDQSGDLY + 0x400 + n*0x80);
        DDRC_PACK_DXNGDS[n]           = readl(M3PM_DDRPHY_BASE + DXNGDS + n*0x80)             ;
        DDRC_PACK_DXNRDQSDLY[n]       = readl(M3PM_DDRPHY_BASE + DXNRDQSDLY + n*0x80)         ;
    }
    DDRC_PACK_ADDRPHBOUND         = readl(M3PM_DDRPHY_BASE + ADDRPHBOUND)                 ;
    /* for mission mode only */
    if( mission_mode == ddr_byp_mode )
    {
        DDRC_PACK_ACADDRBDL0     = readl(M3PM_DDRPHY_BASE + ACADDRBDL0)          ;
        DDRC_PACK_ACADDRBDL1     = readl(M3PM_DDRPHY_BASE + ACADDRBDL1)          ;
        DDRC_PACK_ACADDRBDL2     = readl(M3PM_DDRPHY_BASE + ACADDRBDL2)          ;
        DDRC_PACK_ACADDRBDL3     = readl(M3PM_DDRPHY_BASE + ACADDRBDL3)          ;
        DDRC_PACK_ACADDRBDL4     = readl(M3PM_DDRPHY_BASE + ACADDRBDL4)          ;
        for(n = 0; n < 4; n++)
        {
            DDRC_PACK_DXNWDQNBDL0[n] = readl(M3PM_DDRPHY_BASE + DXNWDQNBDL0 + n*0x80);
            DDRC_PACK_DXNWDQNBDL1[n] = readl(M3PM_DDRPHY_BASE + DXNWDQNBDL1 + n*0x80);
            DDRC_PACK_DXNWDQNBDL2[n] = readl(M3PM_DDRPHY_BASE + DXNWDQNBDL2 + n*0x80);
            DDRC_PACK_DXNRDQNBDL0[n] = readl(M3PM_DDRPHY_BASE + DXNRDQNBDL0 + n*0x80);
            DDRC_PACK_DXNRDQNBDL1[n] = readl(M3PM_DDRPHY_BASE + DXNRDQNBDL1 + n*0x80);
            DDRC_PACK_DXNOEBDL[n]    = readl(M3PM_DDRPHY_BASE + DXNOEBDL    + n*0x80);
            DDRC_PACK_DXNWDQSDLY[n]  = readl(M3PM_DDRPHY_BASE + DXNWDQSDLY  + n*0x80);
            DDRC_PACK_DXNWDQDLY[n]   = readl(M3PM_DDRPHY_BASE + DXNWDQDLY   + n*0x80);
            DDRC_PACK_DXNWLSL[n]     = readl(M3PM_DDRPHY_BASE + DXNWLSL     + n*0x80);
        }
    }
    
    ddr_pdown_stamps[4] = pm_stamp_value();
    
    pm_ldo32_disable();
    
    ddr_pdown_stamps[5] = pm_stamp_value();
}

u32 pm_stamp_value(void);
void ddr_pup(void)
{
    u32 rd_val = 0;
    u32 byp_code = 0;
    u32 i = 0;
    u32 n = 0;
    u32 cfg_value = 0;

    u32 DDRC_PACK_PHYTIMER0 = 0;
    u32 DDRC_PACK_PHYTIMER1 = 0;

    ddr_pup_stamps[0] = pm_stamp_value();

	/* 1 mddrc up with peri_pd */
    /* 2 ddr support including clk,reset,bypass mode */
    /* = ddr init 1 */
    writel(0x7C0  , M3PM_SC_BASE_PD + PD_CRG_CLKEN2);
    writel(0x60000, M3PM_SC_BASE_PD + PD_CRG_SRSTEN1);
    writel(0x60000, M3PM_SC_BASE_PD + PD_CRG_SRSTDIS1);

    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val | (1<<13);
    writel(rd_val,  0x9004E000 + 0x4 );
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val & (~(1<<13));
    writel(rd_val,  0x9004E000 + 0x4 );
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val | (1<<15);
    writel(rd_val,  0x9004E000 + 0x4 );
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val & (~(1<<15));
    writel(rd_val,  0x9004E000 + 0x4 );
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val | (1<<14);
    writel(rd_val,  0x9004E000 + 0x4 );
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val & (~(1<<14));
    writel(rd_val,  0x9004E000 + 0x4 );
    
	
    rd_val = readl( 0x9004E000 + 0x80 );
    rd_val = rd_val & (~(0x1<<13));
    writel(rd_val,  0x9004E000 + 0x80 );
	
	
    /* todo 根据ddr 的频点做恢复 */
    rd_val = readl(M3PM_SC_BASE_PD + SC_TOP_CTRL21);
    if( mission_mode == ddr_byp_mode )
    {
        rd_val = rd_val & (~0x1);
    }
    else
    {
        rd_val = rd_val | 0x1;
    }
    writel(rd_val, M3PM_SC_BASE_PD + SC_TOP_CTRL21);

    /* 3 */
    rd_val = (DDRC_PACK_DXNRDQSDLY[0]&0x1FF);
    byp_code = rd_val<255? rd_val:255;/* min{DXNRDQSDLY(PACK).rdqsbdl,255}; */
    if( bypass_mode == ddr_byp_mode )
    {
    
        /* ACPHYCTL0 (AC_Static_reg) */
        rd_val = readl(0x9004F000 + 0x54);
        rd_val = rd_val & (~0x1FF00);
        rd_val = rd_val | (byp_code<<8);
        rd_val = rd_val | (0x1<<7);
        writel(rd_val, 0x9004F000 + 0x54);
        /* DXNDCC (DX_Static_reg) */
        for(i=0; i<4; i++)
        {
            rd_val = readl(0x9004F000 + 0x250 +  i*0x80);
            rd_val = rd_val & (~0x1FF000);
            rd_val = rd_val | (byp_code<<12);
            writel(rd_val, 0x9004F000 + 0x250 + i*0x80);
        }
        /* DXNMISCCTRL2 (DX_Static_reg) */
        for(i=0; i<4; i++)
        {
            rd_val = readl(0x9004F000 + 0x248 +  i*0x80);
            rd_val = rd_val | (1<<27);
            writel(rd_val, 0x9004F000 + 0x248 + i*0x80);
        }
    }
    
    ddr_pup_stamps[1] = pm_stamp_value();
    
    /* 3 PHYCLKGATED (PACK) close PHY clk gate */
    rd_val = readl( 0x9004E000 + 0xC );
    rd_val = rd_val & (~0x80005F0F);
    rd_val = rd_val | 0x8000430F;
    writel(rd_val, 0x9004E000 + 0xC );
    
    /* 4 PHYCLKGATED byp_pll_lock=0*/
    rd_val = readl( 0x9004E000 + 0xC );
    rd_val = rd_val & (~(0x1<<31));
    writel(rd_val,  0x9004E000 + 0xC );
    
    /* 5 close phy pll pll_pwdn=3'h7, both mode */
    rd_val = readl( 0x9004E000 + 0x18 );
    rd_val = rd_val | 0x7;
    writel(rd_val,  0x9004E000 + 0x18 );

    /* 6 PHY PLL para config */
    rd_val = readl( 0x9004F000 + 0x1C );
    rd_val = rd_val & (~0xDF00000);
    rd_val = rd_val | 0x1200000;
    writel(rd_val,  0x9004F000 + 0x1C );
    
    rd_val = readl( 0x9004F000 + 0x10 );
    rd_val = rd_val | (0x1<<11);
    writel(rd_val,  0x9004F000 + 0x10 );

    rd_val = readl( 0x9004F000 + 0x20 );
    rd_val = rd_val & (~0x3F);
    rd_val = rd_val | 0x2;
    writel(rd_val,  0x9004F000 + 0x20 );
    
    rd_val = readl(0x9004F000 + 0x234 + 0*0x100);
    rd_val = rd_val & (~0xDF0);
    rd_val = rd_val | (0x120);
    writel(rd_val, 0x9004F000 + 0x234 + 0*0x100);
    rd_val = readl(0x9004F000 + 0x234 + 1*0x100);
    rd_val = rd_val & (~0xDF0);
    rd_val = rd_val | (0x120);
    writel(rd_val, 0x9004F000 + 0x234 + 1*0x100);

    rd_val = readl(0x9004F000 + 0x210 + 0*0x100);
    rd_val = rd_val & (~0x3F);
    rd_val = rd_val | (0x2);
    writel(rd_val, 0x9004F000 + 0x210 + 0*0x100);
    rd_val = readl(0x9004F000 + 0x210 + 1*0x100);
    rd_val = rd_val & (~0x3F);
    rd_val = rd_val | (0x2);
    writel(rd_val, 0x9004F000 + 0x210 + 1*0x100);

    rd_val = readl(0x9004F000 + 0x220 + 0*0x100);
    rd_val = rd_val | (0x1<<10);
    writel(rd_val, 0x9004F000 + 0x220 + 0*0x100);
    rd_val = readl(0x9004F000 + 0x220 + 1*0x100);
    rd_val = rd_val | (0x1<<10);
    writel(rd_val, 0x9004F000 + 0x220 + 1*0x100);
 
    /* 6 ODT & Resistor & VREF */
 
    rd_val = readl(0x9004F000 + 0x204 + 0*0x100);
    rd_val = rd_val | (0x1F800);
    writel(rd_val, 0x9004F000 + 0x204 + 0*0x100);
    rd_val = readl(0x9004F000 + 0x204 + 1*0x100);
    rd_val = rd_val | (0x1F800);
    writel(rd_val, 0x9004F000 + 0x204 + 1*0x100);
    
    rd_val = readl(0x9004F000 + 0x18);
    rd_val = rd_val | (0x3FE0000);
    writel(rd_val, 0x9004F000 + 0x18);
    
    rd_val = readl(0x9004F000 + 0x24);
    rd_val = rd_val & (~0x3);
    writel(rd_val, 0x9004F000 + 0x24);
    
    rd_val = readl(0x9004F000 + 0x28);
    rd_val = rd_val & (~0xCC3000);
    rd_val = rd_val | (0xC3);
    writel(rd_val, 0x9004F000 + 0x28);
 
    rd_val = readl(0x9004F000 + 0x218 + 0*0x100);
    rd_val = rd_val & (~0x3);
    writel(rd_val, 0x9004F000 + 0x218 + 0*0x100);
    rd_val = readl(0x9004F000 + 0x218 + 1*0x100);
    rd_val = rd_val & (~0x3);
    writel(rd_val, 0x9004F000 + 0x218 + 1*0x100);
 
    rd_val = readl(0x9004F000 + 0x21C + 0*0x100);
    rd_val = rd_val & (~0x30C3000);
    rd_val = rd_val | (0xC3);
    writel(rd_val, 0x9004F000 + 0x21C + 0*0x100);
    rd_val = readl(0x9004F000 + 0x21C + 1*0x100);
    rd_val = rd_val & (~0x30C3000);
    rd_val = rd_val | (0xC3);
    writel(rd_val, 0x9004F000 + 0x21C + 1*0x100);

    /* 7  config PHY   */
    /*PHYCTRL0  sel_pos_rx=1 */
    rd_val = readl( 0x9004E000 + 0x78 );
    rd_val = rd_val | (0x1<<2);
    writel(rd_val,  0x9004E000 + 0x78 );
    /* PLLTIMER t_pll_lock=0x1000,t_pll_rst=0xA0 */
    rd_val = readl( 0x9004E000 + 0x1C );
    rd_val = rd_val & (~0xFFFF00FF);
    rd_val = rd_val | (0x100000A0);
    writel(rd_val,  0x9004E000 + 0x1C );
    /* DLYMEASCTRL dly_meas_type=0*/
    rd_val = readl( 0x9004E000 + 0x20 );
    rd_val = rd_val & (~0x1);
    writel(rd_val,  0x9004E000 + 0x20 );
    
    rd_val = readl( 0x9004E000 + 0x1D4 );
    rd_val = rd_val & (~(0x1F<<16));
    rd_val = rd_val | (0xC<<16);
    writel(rd_val,  0x9004E000 + 0x1D4 );
    /* PHYTIMER0 */
    rd_val = readl( 0x9004E000 + 0x10 );
    rd_val = rd_val & (~(0xFFFFF<<12));
    rd_val = rd_val | (0x7000<<12);
    writel(rd_val,  0x9004E000 + 0x10 );
    /* PHYTIMER1 */
    rd_val = readl( 0x9004E000 + 0x14 );
    rd_val = rd_val & (~0xFFFFF);
    rd_val = rd_val | (0x10);
    writel(rd_val,  0x9004E000 + 0x14 );
    /* LPCTRL t_dram_clk_disable /t_dram_clk_enable =0 */
    rd_val = readl( 0x9004E000 + 0x1E4 );
    rd_val = rd_val & (~0xFF);
    writel(rd_val,  0x9004E000 + 0x1E4 );
    /* DRAMCFG dram_type=0x5: lpddr 2/3*/
    rd_val = readl( 0x9004E000 + 0x2C );
    rd_val = rd_val & (~0x7);
    rd_val = rd_val | (0x5);
    writel(rd_val,  0x9004E000 + 0x2C );

#if 1
    if(ddr_freq_enum>=DDR_FREQ_MAX)
    {
        ddr_pup_stamps[2] = pm_stamp_value();
        __asm__ __volatile__ ("b .");
        /* for coverity OVERRUN :ddr_freq_enum>=DDR_FREQ_MAX
           add "return" after "b." */
        return; 
    }
    
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer0, M3PM_DDRPHY_BASE + DRAMTIMER0);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer1, M3PM_DDRPHY_BASE + DRAMTIMER1);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer2, M3PM_DDRPHY_BASE + DRAMTIMER2);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer3, M3PM_DDRPHY_BASE + DRAMTIMER3);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer4, M3PM_DDRPHY_BASE + DRAMTIMER4);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].dramtimer5, M3PM_DDRPHY_BASE + DRAMTIMER5);
    writel(pm_ddr_train->TIMING[ddr_freq_enum].modereg01 , M3PM_DDRPHY_BASE + MODEREG01 );
    writel(pm_ddr_train->TIMING[ddr_freq_enum].modereg23 , M3PM_DDRPHY_BASE + MODEREG23 );
    writel(pm_ddr_train->TIMING[ddr_freq_enum].misc      , M3PM_DDRPHY_BASE + MISC      );

    writel(pm_ddr_train->TIMING[ddr_freq_enum].dmsel     , M3PM_DDRPHY_BASE + DMSEL     );
    writel(pm_ddr_train->TIMING[ddr_freq_enum].ioctrl3   , M3PM_DDRPHY_BASE + IOCTL3    );
#else
    /* 533 */
    writel(0x51D87852, M3PM_DDRPHY_BASE + DRAMTIMER0);
    writel(0xA714236 , M3PM_DDRPHY_BASE + DRAMTIMER1);
    writel(0x20091477, M3PM_DDRPHY_BASE + DRAMTIMER2);
    writel(0x80534E16, M3PM_DDRPHY_BASE + DRAMTIMER3);
    writel(0x0       , M3PM_DDRPHY_BASE + DRAMTIMER4);
    writel(0x4       , M3PM_DDRPHY_BASE + DRAMTIMER5);
    writel(0x106C3   , M3PM_DDRPHY_BASE + MODEREG01 );
    writel(0xFF0A0000, M3PM_DDRPHY_BASE + MODEREG23 );
    writel(0x20440705, M3PM_DDRPHY_BASE + MISC      );
     /* 533 */           
    writel(0x24704A00, M3PM_DDRPHY_BASE + DMSEL     );
    writel(0xC000    , M3PM_DDRPHY_BASE + IOCTL3    );
#endif

    /* 8 set dterrstop */
    /* TRAINCTRL0 dtrerrstop bit30 */
    rd_val = readl( 0x9004E000 + 0x48 );
    if( mission_mode == ddr_byp_mode )
        rd_val = rd_val | (0x1<<30);
    else
        rd_val = rd_val & (~(0x1<<30));
    writel(rd_val,  0x9004E000 + 0x48 );
    /* TRAINCTRL3 */
    rd_val = readl( 0x9004E000 + 0xDC );
    if( mission_mode == ddr_byp_mode )
        rd_val = rd_val | (0x1<<29);
    else
        rd_val = rd_val & (~(0x1<<29));
    rd_val = rd_val | (0x1<<21);
    writel(rd_val,  0x9004E000 + 0xDC );
    /* TRAINCTRL6 */
    rd_val = readl( 0x9004E000 + 0xE8 );
    if( mission_mode == ddr_byp_mode )
        rd_val = rd_val & (~(0x1<<23));
    else
        rd_val = rd_val | (0x1<<23);
    rd_val = rd_val | (0xF<<16);
    writel(rd_val,  0x9004E000 + 0xE8 );

    /* 9 set phy dynamic dqsen */
    /* 手册配置顺序, bit 5->4->6 是否需要严格按照顺序 ?*/
    /* bu yaoqiu */
    rd_val = readl( 0x9004E000 + 0x20 );
    rd_val = rd_val & (~(0x1<<4));
    rd_val = rd_val | (0x60);
    writel(rd_val,  0x9004E000 + 0x20 );
    /* 9 set dfi */
    rd_val = readl( 0x9004E000 + 0x80 );
    rd_val = rd_val & (0x1<<15);
    rd_val = rd_val | (0x4000400);
    writel(rd_val,  0x9004E000 + 0x80 );

    /* 10 enable phy DQSG_extend */
    /* DXNMISCCTRL0 + i*0x80  extend_en=1,extend_2T_en=1 */
    for(i=0; i<4; i++)
    {
        rd_val = readl( 0x9004F000 + 0x238 + i*0x80 );
        rd_val = rd_val | (0x3<<28);
        writel(rd_val,  0x9004F000 + 0x238 + i*0x80 );
    }
    /* TRAINCTRL0 dqsgrt_chk=2 dqsgrt_shift=2 dqsgl_mrgn=16,1cycle */
    rd_val = readl( 0x9004E000 + 0x48 );
    rd_val = rd_val & (~0x3FFFF0);
    rd_val = rd_val | 0x20900; 
    writel(rd_val,  0x9004E000 + 0x48 );

    /* new  freq point in mission, phy_pll need re-lock*/
    if(mission_mode == ddr_byp_mode)
    {
        ddr_pup_stamps[3] = pm_stamp_value();

        /* pll_pwdn =7, =0 */
        rd_val = readl( 0x9004E000 + 0x18 );
        rd_val = rd_val | 0x7; 
        writel(rd_val,  0x9004E000 + 0x18 );
        udelay(1);
        rd_val = readl( 0x9004E000 + 0x18 );
        rd_val = rd_val & (~0x7);
        writel(rd_val,  0x9004E000 + 0x18 );
        /* wait 20us and wait pll lock */
        udelay(20);
        do{
            rd_val = readl( 0x9004E000 + 0x98 );
        }while(((rd_val>>31)&0x1)!=0x1); 
        
        ddr_pup_stamps[4] = pm_stamp_value();
        
        do{
            rd_val = readl( 0x9004E000 + 0x9C );
        }while(((rd_val>>28)&0xF)!=0xF); 
        
        ddr_pup_stamps[5] = pm_stamp_value();
    }
    

    /* 11 PHYINITCTRL zcal_en=0,dlymeas_en=0,pll_init_en=0 */
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val & (~0xE); 
    writel(rd_val,  0x9004E000 + 0x4 );

    /* 12 */
    writel(DDRC_PACK_IMPSTATUS          , M3PM_DDRPHY_BASE + IMPSTATUS                   );
    for (n = 0; n < 4; n++)
    {
        writel(DDRC_PACK_RANK0DXNRDQSGDLY[n], M3PM_DDRPHY_BASE + DXNRDQSGDLY + n*0x80        );
        writel(DDRC_PACK_RANK1DXNRDQSGDLY[n], M3PM_DDRPHY_BASE + DXNRDQSGDLY + 0x400 + n*0x80);
        writel(DDRC_PACK_DXNGDS[n]          , M3PM_DDRPHY_BASE + DXNGDS + n*0x80             );
        writel(DDRC_PACK_DXNRDQSDLY[n]      , M3PM_DDRPHY_BASE + DXNRDQSDLY + n*0x80         );
    }
    writel(DDRC_PACK_ADDRPHBOUND        , M3PM_DDRPHY_BASE + ADDRPHBOUND                 );

    if( mission_mode == ddr_byp_mode )
    {
        writel(DDRC_PACK_ACADDRBDL0    , M3PM_DDRPHY_BASE + ACADDRBDL0)          ;
        writel(DDRC_PACK_ACADDRBDL1    , M3PM_DDRPHY_BASE + ACADDRBDL1)          ;
        writel(DDRC_PACK_ACADDRBDL2    , M3PM_DDRPHY_BASE + ACADDRBDL2)          ;
        writel(DDRC_PACK_ACADDRBDL3    , M3PM_DDRPHY_BASE + ACADDRBDL3)          ;
        writel(DDRC_PACK_ACADDRBDL4    , M3PM_DDRPHY_BASE + ACADDRBDL4)          ;
        for (n = 0; n < 4; n++)
        {
            writel(DDRC_PACK_DXNWDQNBDL0[n], M3PM_DDRPHY_BASE + DXNWDQNBDL0 + n*0x80);
            writel(DDRC_PACK_DXNWDQNBDL1[n], M3PM_DDRPHY_BASE + DXNWDQNBDL1 + n*0x80);
            writel(DDRC_PACK_DXNWDQNBDL2[n], M3PM_DDRPHY_BASE + DXNWDQNBDL2 + n*0x80);
            writel(DDRC_PACK_DXNRDQNBDL0[n], M3PM_DDRPHY_BASE + DXNRDQNBDL0 + n*0x80);
            writel(DDRC_PACK_DXNRDQNBDL1[n], M3PM_DDRPHY_BASE + DXNRDQNBDL1 + n*0x80);
            writel(DDRC_PACK_DXNOEBDL[n]   , M3PM_DDRPHY_BASE + DXNOEBDL    + n*0x80);
            writel(DDRC_PACK_DXNWDQSDLY[n] , M3PM_DDRPHY_BASE + DXNWDQSDLY  + n*0x80);
            writel(DDRC_PACK_DXNWDQDLY[n]  , M3PM_DDRPHY_BASE + DXNWDQDLY   + n*0x80);
            writel(DDRC_PACK_DXNWLSL[n]    , M3PM_DDRPHY_BASE + DXNWLSL     + n*0x80);
        }
    }

    /* 13 */
    /* MISC cfg_dlyupd=1, =0 */
    rd_val = readl( 0x9004E000 + 0x70 );
    rd_val = rd_val | (1<<19);
    writel(rd_val,  0x9004E000 + 0x70 );
    udelay(1);
    rd_val = readl( 0x9004E000 + 0x70 );
    rd_val = rd_val & (~(1<<19));
    writel(rd_val,  0x9004E000 + 0x70 );

    /* 14 */
    /* PHYINITCTRL phyconn_rst =1， =0 */
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val | (1<<15);
    writel(rd_val,  0x9004E000 + 0x4 );
    udelay(1);
    
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val & (~(1<<15));
    writel(rd_val,  0x9004E000 + 0x4 );

    /* new save DDR_PACK_PHYTIMERx */
    DDRC_PACK_PHYTIMER0 = readl( 0x9004E000 + 0x10 ); /* save t_dram_cke_high/t_dram_reset */
    DDRC_PACK_PHYTIMER1 = readl( 0x9004E000 + 0x14 ); /* save t_dram_cke_low */

    /* new set DDR_PACK_PHYTIMERx */
    writel(DDRC_PACK_PHYTIMER0&0xF00, 0x9004E000 + 0x10 ); /* t_dram_cke_high=0,t_dram_reset=0 */
    writel(DDRC_PACK_PHYTIMER1&0xFFF00000, 0x9004E000 + 0x14 ); /* t_dram_cke_low=0 */
    /* new high pack CKE dram_rst =1 init en = 1 */
    rd_val = readl( 0x9004E000 + 0x4 );
    rd_val = rd_val | 0x1001;
    writel(rd_val,  0x9004E000 + 0x4 );


    /* 15 = init 11+12 23+24 */
    /* init 11 config DMC work mode and para */
    rd_val = readl( 0x90048000 + 0x50 );
    rd_val = rd_val & (~0x30013F);
    rd_val = rd_val | (0x2<<4);  /* mem_witdh */
    rd_val = rd_val | (get_dram_type()); /* bit[3:0]*/
    rd_val = rd_val | (1<<8);  /* todo  1(SDR) / 0(HDR)*/
    rd_val = rd_val | (0<<20);   /* 0:1rank, 1:2rand v7r5 lpddr2 use one rank, lpddr3 not sure */
    writel(rd_val,  0x90048000 + 0x50 );

#ifdef BSP_CONFIG_LPDDR2
    cfg_value = 0x131;
#elif defined(BSP_CONFIG_LPDDR3)
    cfg_value = 0x142;
#else
#endif
    rd_val = readl( 0x90048000 + 0x60 );
    rd_val = rd_val & (~0x377);
    rd_val = rd_val | cfg_value;
    writel(rd_val,  0x90048000 + 0x60 );
    rd_val = readl( 0x90048000 + 0x60 +0x4 );
    rd_val = rd_val & (~0x377);
    rd_val = rd_val | cfg_value;
    writel(rd_val,  0x90048000 + 0x60 +0x4 );
    
    rd_val = readl( 0x90048000 + 0x200 );
    rd_val = rd_val & (~0x1F0000);
    /* wr_busy_dly, set to wl+4 for power control, lpddr2:8,lpddr3:0xA */
#ifdef BSP_CONFIG_LPDDR2
    rd_val = rd_val | (0x8<<16);
#elif defined(BSP_CONFIG_LPDDR3)
     rd_val = rd_val | (0xa<<16);
#endif
    writel(rd_val,  0x90048000 + 0x200 );

    /* init 12 config DMC timing  from table.xls */

        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing0, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING0);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing1, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING1);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing2, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING2);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing3, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING3);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing4, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING4);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing5, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING5);
        writel(pm_ddr_train->TIMING[ddr_freq_enum].timing6, M3PM_MDDRC_BASE+0x8000 + DDRC_CFG_TIMING6);/* todo part of reg*/


    /* init 23 config AXI_IF memmap mode */
    /* AXI_ACTION donot set for now */
    /*writel(xxx, 0x90040000 + 0x20 );*/
    rd_val = readl( 0x90040000 + 0x100 );
    rd_val = rd_val & (~0x17FF);
    rd_val = rd_val | (0x1640);
    writel(rd_val,  0x90040000 + 0x100 );
    
    rd_val = readl( 0x90040000 + 0x104 );
    rd_val = rd_val & (~0x7307FF3F);
    rd_val = rd_val | (0x41040004);
    writel(rd_val,  0x90040000 + 0x104 );
    /* init 24 ignore for now, config according to requests */

    ddr_pup_stamps[6] = pm_stamp_value();

    /* new */
    do{
        rd_val = readl( 0x9004E000 + 0x4 );
    }while((rd_val&0x1)!=0x0); /* init_en=0 */
    
    ddr_pup_stamps[7] = pm_stamp_value();
    
    /* new2  dont need bit-oprate, PHYTIMER0:[11~8] ro, PHYTIMER1:[31~20] ro */
    writel(DDRC_PACK_PHYTIMER0, 0x9004E000 + 0x10);
    writel(DDRC_PACK_PHYTIMER1, 0x9004E000 + 0x14);

    /* 16 ios dis */
    writel(0x1<<24, M3PM_SC_BASE_AO + PWR_CTRL5);

    /* 17 = init 25~28 */
#if 1
    /* init 25  */
/* open after debug is stable */
    /* enable pd/ asref/ lp*/
    rd_val = readl( 0x90048000 + 0x28 );
    rd_val = rd_val & (~0xFFFFFFF5);
    rd_val = rd_val | (0x110201);
    writel(rd_val,  0x90048000 + 0x28 );
    
    /* enable auto ref */
    rd_val = readl( 0x90048000 + 0x2c );
    rd_val = rd_val & (~0x64);
    rd_val = rd_val | (0x44);
    writel(rd_val,  0x90048000 + 0x2c );

    rd_val = readl( 0x90048000 + 0x20 );
    rd_val = rd_val & (~0xFFFF0003);
    rd_val = rd_val | (0x30003);
    writel(rd_val,  0x90048000 + 0x20 );
    
    /* DDRC_CFG_DDRMODE enable asref_zqc_en sref_zqc_en zqc_en */
    rd_val = readl( 0x90048000 + 0x50 );
    rd_val = rd_val | (0xC10000);
    writel(rd_val,  0x90048000 + 0x50 );

    rd_val = readl( 0x9004E000 + 0x1E4 );
    rd_val = rd_val & (~0x1E0FF00);
    rd_val = rd_val | (0x7600);
    writel(rd_val,  0x9004E000 + 0x1E4 );
    
    rd_val = readl( 0x90048000 + 0x1C );
    rd_val = rd_val & (~0xFFF01);
    rd_val = rd_val | (0xAF001);
    writel(rd_val,  0x90048000 + 0x1C );

    rd_val = readl( 0x9004E000 + 0x80 );
    rd_val = rd_val | (0x1<<13);
    writel(rd_val,  0x9004E000 + 0x80 );

#endif
    
    /* init 26 out sref */
    rd_val = readl( 0x90048000 + 0x0 );
    rd_val = rd_val & (~0x3);
    writel(rd_val,  0x90048000 + 0x0 );

    ddr_pup_stamps[8] = pm_stamp_value();

    /* init 27 ensure not sref*/
    do{
        rd_val = readl( 0x90048000 + 0x294 );
    }while((rd_val&0x1)!=0x0);

    ddr_pup_stamps[9] = pm_stamp_value();
    
    /* init 28 DDRC_CTRL_SREF sref_done=1 */
    rd_val = readl( 0x90048000 + 0x0 );
    rd_val = rd_val | (0x1<<1);
    writel(rd_val,  0x90048000 + 0x0 );
    
    /*29、LPDDR2 读mr8自适应修改 row/col 宽度配置信息 (兼容美光由两个 1Gddr拼接的 2Gddr) */
#ifdef BSP_CONFIG_LPDDR2
    writel(0x10000      , 0x90048000 + 0x218);
    writel(0x40000087   , 0x90048000 + 0x210);
    writel(0x1          , 0x90048000 + 0xC);
    do{
        rd_val = readl( 0x90048000 + 0xC );
    }while((rd_val&0x1)!=0x0);

    ddr_pup_stamps[10] = pm_stamp_value();

    rd_val = readl( 0x90048000 + 0x4a8 );
    rd_val = rd_val&0xFF;
    if(0x50 == rd_val)
    {
        rd_val = readl( 0x90048000 + 0x60 + 0x4*0 );
        rd_val = rd_val & (~0x377);
        rd_val = rd_val | (0x122);
        writel(rd_val,  0x90048000 + 0x60 + 0x4*0 );
        
        rd_val = readl( 0x90048000 + 0x60 + 0x4*1 );
        rd_val = rd_val & (~0x377);
        rd_val = rd_val | (0x122);
        writel(rd_val,  0x90048000 + 0x60 + 0x4*1 );
    }
#endif

    /* 16 = init 25 - 29  - end */

    ddr_hit_test();
    ddr_pup_stamps[11] = pm_stamp_value();

}
#endif

#if 0
/* ddr config for porting */
#define _CFG_CLK_CPU_M3_ (120*1000*1000)

void ddrc_init_udelay(unsigned int us)
{
    while(us--) {
        unsigned long t = (_CFG_CLK_CPU_M3_/3)/1000000;
        while(t--)
            __asm__ __volatile__("nop");
    }
}

void v7r5_porting_mddrc_init_lpddr2()
{
    writel(0x20000, 0x90000064);/*dis reset mddrc*/
    writel(0x03f7f1f1, 0x90000454);/*set ddrphy_pll bypass mode*/

    /* Base Configuration of MDDRC */
    writel(0x20, HI_MDDRC_REGBASE_ADDR + 0x8040);
    writel(0x000122, HI_MDDRC_REGBASE_ADDR + 0x8050);/*rank_num:1, lpddr2*/
    writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x8060);
    writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x8064);
    writel(0x10081000, HI_MDDRC_REGBASE_ADDR + 0x8200);
    writel(0x63210b07, HI_MDDRC_REGBASE_ADDR + 0x8100);  
    writel(0x0862181d, HI_MDDRC_REGBASE_ADDR + 0x8104);/*twl:3(wl)+1,trl:6(rl)*/  
    writel(0x43009000, HI_MDDRC_REGBASE_ADDR + 0x8108);  /*cfg taref=0 in init*/
    writel(0xaf444035, HI_MDDRC_REGBASE_ADDR + 0x810c);
    writel(0x600000, HI_MDDRC_REGBASE_ADDR + 0x8110);
    writel(0x1080708, HI_MDDRC_REGBASE_ADDR + 0x8114);
    writel(0x44, HI_MDDRC_REGBASE_ADDR + 0x8118);
    writel(0x1640, HI_MDDRC_REGBASE_ADDR + 0x0100);
    writel(0x41010004, HI_MDDRC_REGBASE_ADDR + 0x0104);
    writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8000);
    writel(0x2, HI_MDDRC_REGBASE_ADDR + 0x8000);    
    while((readl(HI_MDDRC_REGBASE_ADDR+0x8294) & 0x1) != 0x0)
    {};

    /*mrw start*/
    ddrc_init_udelay(2); /* 2us */
    writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x400003f2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr63:LMR->reset lpddr3*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
    writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x40043012, HI_MDDRC_REGBASE_ADDR + 0x8210);/*nWR:6;BL:8;mr1;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
    writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x40004022, HI_MDDRC_REGBASE_ADDR + 0x8210);/*R1:6,W1:3;mr2;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
    writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x400ff0a2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr10 calibration code:0xff;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/    
    ddrc_init_udelay(10); /* 10us */
    /*mrw end*/
    
    writel(0x4500901f, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0x1f after init_done*/
}

/* ddr config for emu */
void mddrc_init_emu()
{
    /*A9 CLK switch to peri-pll,ddr:533M*/
    writel(0x8, 0x90000030);/*open peri-pll clk enable*/
    writel(0x8, 0x90000144);/*A9 CLK switch to peri-pll*/
    writel(0x181|readl(0x90000208),0x90000208);/*A9 pll powerdown,bypass*/
    writel(0x855555, 0x90000200);/*a9pll_postdiv=1066m*/
    writel(0x1101037, 0x90000204);
    writel(0x28,0x90000208);/*only enable pll postdivout*/
    while((readl(0x90000208) & 0x80000000) != 0x80000000)/*wait lock*/
    {};
    writel(0x40001300, 0x90000104);/*div cpu:fast:slow=1:2:4*/
    writel(0x1, 0x90000144);/*A9 CLK switch to a9-pll*/
    writel(0x8, 0x90000034);/*close peri-pll clk enable*/

    writel(0xffffffff, 0x90000010);/*enable clk*/
    writel(0x60000|readl(0x90000064),0x90000064);/*ddrphy srst*/
    writel(0x100|readl(0x9000080c),0x9000080c);/*mddrc open clk*/

    /*mddrc init start*/
    writel(0x60000, 0x90000060);/*reset mddrc*/
    writel(0x60000, 0x90000064);/*dis reset mddrc*/
    writel(0x03f7f1f1, 0x90000454);/*set ddrphy_pll bypass mode*/

    /* Base Configuration of MDDRC */
    writel(0x20, HI_MDDRC_REGBASE_ADDR + 0x8040);
    writel(0x100122, HI_MDDRC_REGBASE_ADDR + 0x8050);/*rank_num:1, lpddr2*/
    writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8060);
    writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8064);
    writel(0x10081000, HI_MDDRC_REGBASE_ADDR + 0x8200);
    
    /*for 533*/
    writel(0x677b6718, HI_MDDRC_REGBASE_ADDR + 0x8100);  
    writel(0x1e821871, HI_MDDRC_REGBASE_ADDR + 0x8104);/*twl:3(wl)+1,trl:6(rl)*/  
    writel(0x95021000, HI_MDDRC_REGBASE_ADDR + 0x8108);  /*cfg taref=0 in init*/
    writel(0xaf50c057, HI_MDDRC_REGBASE_ADDR + 0x810c);
    writel(0x600000, HI_MDDRC_REGBASE_ADDR + 0x8110);
    writel(0x3181908, HI_MDDRC_REGBASE_ADDR + 0x8114);
    writel(0x44, HI_MDDRC_REGBASE_ADDR + 0x8118);
    
    writel(0x1700, HI_MDDRC_REGBASE_ADDR + 0x0100);
    writel(0x71040004, HI_MDDRC_REGBASE_ADDR + 0x0104);
    writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8000);
    writel(0x2, HI_MDDRC_REGBASE_ADDR + 0x8000);    
    while((readl(HI_MDDRC_REGBASE_ADDR+0x8294) & 0x1) != 0x0)
    {};

    /*mrw start*/
    writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x400003f2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr63:LMR->reset lpddr3*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/    
    while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
    {};
    writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x400ff0a2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr10 calibration code:0xff;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/    
    while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
    {};
    writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x40043012, HI_MDDRC_REGBASE_ADDR + 0x8210);/*nWR:6;BL:8;mr1;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
    while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
    {};
    writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
    writel(0x40004022, HI_MDDRC_REGBASE_ADDR + 0x8210);/*R1:6,W1:3;mr2;LMR*/
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
    while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
    {};
    /*mrw end*/
    
    writel(0x9502107e, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0x1f after init_done*/        
}

#define V7R5_PORTING        0x6950A100
#define V7R5_ASIC           0x69500100
#define EMU_PALADIN         0x6950E100
#define EMU_ZEBU            0x6950E1A0

void mddrc_init()
{
    unsigned reg = 0;
    
    reg = readl(0x90000f00);
    switch(reg)
    {
        case V7R5_PORTING:
            v7r5_porting_mddrc_init_lpddr2();
            break;
        case V7R5_ASIC:
            break;
        case EMU_PALADIN:
            mddrc_init_emu();
            break;
        case EMU_ZEBU:
            v7r5_porting_mddrc_init_lpddr2();
            break;
        default:
            v7r5_porting_mddrc_init_lpddr2();
            break;    
    }
}
#endif

struct sys_reg_need_bak
{
    u32 start;
    u32 end;
};

struct sys_reg_need_set
{
    u32 from;
};
#define SYS_REG_BAK_NUM 9
#define SYS_REG_SET_NUM 11
struct sys_reg_bak_cfg
{
    struct sys_reg_need_bak bak[SYS_REG_BAK_NUM];
    struct sys_reg_need_set set[SYS_REG_SET_NUM];
};

/*
SC_BASE_MDM    0x80200000
SC_BASE_PD       0x90000000
SC_BASE_AO       0x20000000

SYS_PD:     0x400-0x468    0x800-0x884
SYS_MDM:  0x400-0x540    0x590-0x5A4

PD_CRG:     clk[0x0] x 4, srst[0x60] x 3
                 0x100-0x10c, 0x114-0x11c, 0x140-0x148, 0x200-0x220, 0x230-0x244
                 
MDM_CRG:  clk[0x0] x 2, srst[0x20] x 2, 0x40-0x44,0x60
*/
u32 sys_reg_bak_cfgs[512];
void sys_bak_data_init(void)
{
    struct sys_reg_bak_cfg * cfg = 0;

    cfg = (struct sys_reg_bak_cfg*)(sys_reg_bak_cfgs);

    /*SYS_PD:     0x400-0x468    0x800-0x884*/
    cfg->bak[0].start = 0x90000400;
    cfg->bak[0].end   = 0x90000468;
    cfg->bak[1].start = 0x90000800;
    cfg->bak[1].end   = 0x90000884;
    /*SYS_MDM:  0x400-0x540    0x590-0x5A4*/
    cfg->bak[2].start = 0x80200400;
    cfg->bak[2].end   = 0x80200540;
    cfg->bak[3].start = 0x80200590;
    cfg->bak[3].end   = 0x802005A4;
    /*PD_CRG:   0x100-0x10c, 0x114-0x11c, 0x140-0x148, 0x200-0x220, 0x230-0x244*/
    cfg->bak[4].start = 0x90000100;
    cfg->bak[4].end   = 0x9000010c;
    cfg->bak[5].start = 0x90000114;
    cfg->bak[5].end   = 0x9000011c;
    cfg->bak[6].start = 0x9000020C;
    cfg->bak[6].end   = 0x90000210;
#if 0
    cfg->bak[6].start = 0x90000140;
    cfg->bak[6].end   = 0x90000148;
    cfg->bak[7].start = 0x90000200;
    cfg->bak[7].end   = 0x90000220;
    cfg->bak[8].start = 0x90000230;
    cfg->bak[8].end   = 0x90000244;
#endif
    /*MDM_CRG:  0x40-0x44,0x60*/
    cfg->bak[7].start = 0x80200040;
    cfg->bak[7].end   = 0x80200044;
    cfg->bak[8].start = 0x80200060;
    cfg->bak[8].end   = 0x80200060;
    /*PD_CRG:   clk[0x0] x 4, srst[0x60] x 3
      MDM_CRG:  clk[0x0] x 2, srst[0x20] x 2, 
                writle (val) enable, writel ~(val) disable*/
    cfg->set[0].from = 0x90000008;
    cfg->set[1].from = 0x90000018;
    cfg->set[2].from = 0x90000028;
    cfg->set[3].from = 0x90000038;
    cfg->set[4].from = 0x90000068;
    cfg->set[5].from = 0x90000074;
    cfg->set[6].from = 0x90000080;
    cfg->set[7].from = 0x80200008;
    cfg->set[8].from = 0x80200018;
    cfg->set[9].from = 0x80200028;
    cfg->set[10].from= 0x80200038;
    
}


void sys_reg_bak()
{
    struct sys_reg_bak_cfg * cfg = 0;
    u32 * regs_bak = 0;
    u32 i = 0;
    u32 * temp_reg = 0;

    cfg = (struct sys_reg_bak_cfg*)(sys_reg_bak_cfgs);
    regs_bak = (u32*) ((u32)cfg + sizeof(struct sys_reg_bak_cfg));

    for(i=0;i<SYS_REG_BAK_NUM;i++)
    {
        for(temp_reg = (u32*)cfg->bak[i].start; temp_reg <= (u32*)cfg->bak[i].end; temp_reg++)
        {
            *regs_bak = *temp_reg;
            regs_bak++;
        }
    }
    for(i=0;i<SYS_REG_SET_NUM;i++)
    {
        temp_reg = (u32*)cfg->set[i].from;
        *regs_bak = *temp_reg;
        regs_bak++;
    }
}
void sys_reg_restore()
{
    struct sys_reg_bak_cfg * cfg = 0;
    u32 *regs_bak = 0;
    u32 i = 0;
    u32 * temp_reg = 0;
    u32 reg_val;

    cfg = (struct sys_reg_bak_cfg*)(sys_reg_bak_cfgs);
    regs_bak = (u32*) ((u32)cfg + sizeof(struct sys_reg_bak_cfg));

    for(i=0;i<SYS_REG_BAK_NUM;i++)
    {
        for(temp_reg = (u32*)cfg->bak[i].start; temp_reg <= (u32*)cfg->bak[i].end; temp_reg++)
        {
            *temp_reg = *regs_bak;
            regs_bak++;
        }
    }
    for(i=0;i<SYS_REG_SET_NUM;i++)
    {
        temp_reg = (u32*)cfg->set[i].from;
        *(temp_reg-2) = *regs_bak;
        *(temp_reg-1) = ~(*regs_bak);
        regs_bak++;
    }
    /* open dsp pll */
    reg_val = readl(0x90000214);
    writel(reg_val&(~0x11),0x90000214);
    do{
		reg_val = readl(0x90000214);
		reg_val &= ((u32)0x1<<31);
	}while(!reg_val);
    /* dsp clk_src in enable */
    writel(0x30000000,0x90000030);
    /* dsp clk_src switch to peri pll (default dsp pll) */
    writel(0x2,0x90000148);
    
    /* close dsp pll */
    reg_val = readl(0x90000214);
    writel(reg_val|0x1,0x90000214);
}

s32 sram_bak(void)
{
    s32 ret = 0;
    u32 val = 0;
    
    /* open edma clk */
    val = readl(0x8020000C);
    val = val&(0x1<<18);
    if(!val)
        writel(0x1<<18,0x80200000);
    
    ret = bsp_edma_m2m_channel(0, (u32)(HI_SRAM_MEM_BASE_ADDR), (u32)(SHM_BASE_ADDR + SHM_OFFSET_SRAM_BAK), HI_SRAM_MEM_SIZE);
    if(ret != 0)
    {
        gPmErrorSt.u32AxiBakeupErrTimes++;
        if(!val)
            writel(0x1<<18,0x80200004);
        return 1;
    }
	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);
    
    /* close edma clk */
    if(!val)
        writel(0x1<<18,0x80200004);

    return ret;
}
s32 sram_restore(void)
{
    s32 ret = 0;
    u32 val = 0;
    
    /* open edma clk */
    val = readl(0x8020000C);
    val = val&(0x1<<18);
    if(!val)
        writel(0x1<<18,0x80200000);
    
    ret = bsp_edma_m2m_channel(0, (u32)(SHM_BASE_ADDR + SHM_OFFSET_SRAM_BAK), (u32)(HI_SRAM_MEM_BASE_ADDR), HI_SRAM_MEM_SIZE);
    if(ret != 0)
    {
        gPmErrorSt.u32AxiRestoreErrTimes++;
        if(!val)
            writel(0x1<<18,0x80200004);
        return 1;
    }
	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);

    /* close edma clk */
    if(!val)
        writel(0x1<<18,0x80200004);

    return ret;
}


static void pm_set_bbpwakeup_flag(void)
{

    u32 tmp = 0;

    tmp = readl( M3PM_SC_BASE_AO + PWR_STAT23 );
    tmp = tmp & MDMA9_WSRC_0_LDRX_CPU;  /* todo only lte in old version, tds---? */
    if(tmp){
        writel(1, PM_SHM_TIMESTAMP_ADDR);
    }
    else{
        writel(0, PM_SHM_TIMESTAMP_ADDR);
    }
    writel(readl(M3PM_SC_BASE_AO + 0x8 ), PWR_SRAM_CRG_REG);
    writel(readl(M3PM_SC_BASE_AO + 0x14), PWR_SRAM_CRG_REG + 0x4);
    writel(readl(M3PM_SC_BASE_AO + 0x20), PWR_SRAM_CRG_REG + 0x8);
    writel(readl(M3PM_SC_BASE_AO + 0x2c), PWR_SRAM_CRG_REG + 0xC);
    writel(readl(M3PM_SC_BASE_AO + 0x38), PWR_SRAM_CRG_REG + 0x10);
    writel(readl(M3PM_SC_BASE_AO + 0xe04), PWR_SRAM_CRG_REG + 0x14);
}

/* T32 trace int wakeup */
irqreturn_t trace_int_handler(int irq, void* data)
{
    printk("t32 int\n");
    return IRQ_HANDLED;
}


void pm_config_init(void)
{

	pm_ddr_train = (TCM_DFS_TRAINING *)DFS_DDR_TRAINING_DATA_ADDR;

    ddr_hit_addr = SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT-4;/* todo ddr addr */

    sys_bak_data_init();
    (void)request_irq(M3_CM3_DBG_WAKE_INT, trace_int_handler, 0, "cm3_debug_wake", 0);/*lint !e713*/
    /* wakeup src clean*/
    /*m3*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL16);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL17);
    /*appa9*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL24);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL25);
    /*mdma9*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL30);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL31);
}

static void pm_config_init_buck3off(void)
{
    u32 tmp = 0;

    /* 3 */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp |= 0x2C00400;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 4 tcxo*/
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL2);
    tmp &= 0xA00000;
    tmp = tmp | 0x1404FFE5;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL2);

    /* 5 */
    writel(0x1FFF0FFF, M3PM_SC_BASE_AO + PWR_CTRL8);

    /* 6 m3 tcm */
    writel(0x20011, M3PM_SC_BASE_AO + PWR_CTRL12);
    writel(0x20011, M3PM_SC_BASE_AO + PWR_CTRL38);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL10);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL11);

    /* 7 pmu pwr down, close clk */
    writel(0x10FE1, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 8 peri power down */
    if(1 == gPmNvSt.peridown_flag)
    {
        writel(0x20000000, M3PM_SC_BASE_AO + PWR_CTRL9);
    }
}




/*lint -save -e737*/
void pm_mcu_buck3off_pdown(void)
{
    u32 tmp = 0;
    u32 i = 0;

    /* 9 todo */
    for(i = 0; i < 8; i++)
    {
        gPmBakeupSt.u32NvicEnable[i] = NVIC->ISER[i];
        NVIC->ICER[i] = 0xFFFFFFFF;
    } 

    /* 唤醒源未配置 */
#if 1
    for(i = 0; i < DS_IRQ_NUM; i++)
    {
        enable_irq(pm_deepsleep_irq[i]);
    }
#endif
    /* 10 bak for power down */
    
    ios_suspend();

    bsp_tsensor_disable();
    m3_pm_stamps->buck3off.after_ios_suspend = pm_stamp_value();
    sys_reg_bak();
    m3_pm_stamps->buck3off.after_sysreg_suspend = pm_stamp_value();
    (void)sram_bak();
    m3_pm_stamps->buck3off.after_sram_suspend = pm_stamp_value();
    
    clk_bak.crg_dfs1_ctrl1 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    clk_bak.crg_dfs1_ctrl2 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    clk_bak.crg_dfs1_ctrl3 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    clk_bak.pd_crg_clkdiv2 = readl(M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    
    /* 11 ddr  pdown */

    ddr_pdown();

    m3_pm_stamps->buck3off.after_ddr_sref = pm_stamp_value();

    /* 12   normal io retention */
    writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL4);

    if(gPmCountSt.u32PwrRegbakFlag)
    {
        pm_mcu_bakeup_debug();
    }

    m3_pm_stamps->buck3off.before_sram_retention= pm_stamp_value();

    set_cpu_dbg_suspend(cm3_debug_suspend_bit,1);

    /* 13 slow */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x2;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
    do
    {
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp = (tmp >> 3)&0x7;
    }while(tmp != 0x2);
    /* 14 */
    writel(0x0, M3PM_SC_BASE_PD +  + PD_CRG_CLKDIV2);

    /* 15 cpu sleep */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 16 dummy: to make sure */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);

    ISB();

    /* wfi */
    if(!gPmCountSt.u32SleepWithoutWfiFlag)
    WFI();
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
}

void pm_mcu_buck3off_pup(void)
{
    u32 tmp = 0;
    u32 tmp1 = 0;
    u32 i = 0;
    u32 arm_boot_type = 0;

    /* 12 : normal io out retention here for debug */
    //writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL5);

    /* 1 a9 pll */
    writel(clk_bak.crg_dfs1_ctrl1, M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    writel(clk_bak.crg_dfs1_ctrl2, M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    writel(clk_bak.crg_dfs1_ctrl3, M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);

    /* new added */
    writel( 0x2C, M3PM_SC_BASE_PD + CRG_DFS5_CTRL3);
    
    /* 2 clk div */
    writel(clk_bak.pd_crg_clkdiv2, M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    /* 3 normal */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x4;
    do{
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = (tmp1 & 0x78) >> 3;
    }while((tmp1 != 0x4));

    m3_pm_stamps->buck3off.after_sram_out_retention= bsp_get_slice_value();
    
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_0);

    slice_resume(); /* udelay timer init , needed by ddr pup */

    m3_pm_stamps->buck3off.before_sysreg_resume= pm_stamp_value();
    sys_reg_restore();

    m3_pm_stamps->buck3off.after_ios_resume = pm_stamp_value();

    /* 11 ios resume */
    ios_resume();

    /* 12 normal io out retention */
    writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL5);
    m3_pm_stamps->buck3off.after_rf_resetn = pm_stamp_value();

    pm_ldo32_enable();

    /* 4 check arm_boot_type */
    arm_boot_type = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    if(arm_boot_type & (0x1UL<<30))
    {
        m3_pm_stamps->buck3off.before_ddr_restore = pm_stamp_value();
        /* 5 restore ddr */
        ddr_pup();
        /* 10 clear arm_boot_type */
        arm_boot_type &= ~(0x1UL<<30);
        writel(arm_boot_type, M3PM_SC_BASE_AO + PWR_CTRL0);
        m3_pm_stamps->buck3off.after_ddr_restore = pm_stamp_value();
        cpufreq_m3_cti_init();  /* cti for ddr sref buserr */
    }
    else
    {
        m3_pm_stamps->buck3off.no_boot_not_ddr_restore= pm_stamp_value();
        m3_pm_stamps->buck3off.no_sm_cnt++;

        /* 6 ddr io */
        writel((0x1<<24), M3PM_SC_BASE_AO + PWR_CTRL5);
        
        /* 7 wait pll lock */
        if((readl(M3PM_SC_BASE_PD + SC_TOP_CTRL21)&0x1) == 0)
        { /* bit0 = 0 mission mode */
            /* wait pll lock*/
            udelay(20);
            do{
                tmp  = readl(0x9004E098)&0x1; /* wait ac_pll lock */
                tmp1 = readl(0x9004E09C);     /* wait dx_pll lock */
                tmp1 = (tmp1>>28) & 0xf;
            }while((tmp != 0x0)||(tmp1)!=0xf);
        }
        
        /* 8 ddr out sref */
        pm_ddr_out_sref();

        m3_pm_stamps->buck3off.after_ddr_out_sref = pm_stamp_value();
        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_2);

        tmp = readl(0x90048000); tmp |= 0x1<<1; writel(tmp, 0x90048000);

        /*9 ddrc restore : 0x9004_8028 bit0=1,0x9004_801c bit0=1,0x9004_8200 bit12=1 */
        tmp = readl(0x90048028); tmp |= 0x1;    writel(tmp, 0x90048028);
        tmp = readl(0x9004801c); tmp |= 0x1;    writel(tmp, 0x9004801c);
        tmp = readl(0x90048200); tmp |= 0x1<<12;writel(tmp, 0x90048200);

        ddr_hit_test();
    }

    m3_pm_stamps->buck3off.before_sram_resume= pm_stamp_value();
    (void)sram_restore();

    bsp_tsensor_enable();
    
    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_3);

    pm_mcu_wakeup_debug();

    pm_set_bbpwakeup_flag();

    /* 13 */
    for(i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ISER[i] = gPmBakeupSt.u32NvicEnable[i];
    }
    m3_pm_stamps->buck3off.buck3off_pup_end = pm_stamp_value();

}

static void pm_config_init_buck3on(void)
{
    u32 tmp = 0;

    /* 3 */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp |= 0x2C00400;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 4 tcxo*/
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL2);
    tmp &= 0xA00000;
    tmp = tmp | 0x1404FFE5;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL2);

    /* 5 */
    writel(0x1FFF0FFF, M3PM_SC_BASE_AO + PWR_CTRL8);

    /* 6 m3 tcm */
    writel(0x20011, M3PM_SC_BASE_AO + PWR_CTRL12);
    writel(0x20011, M3PM_SC_BASE_AO + PWR_CTRL38);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL10);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL11);

    /* 7 pmu pwr down, close clk */
    writel(0x10FE1, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 7 pmu  NO pwr down, but close clk */
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 8 peri power down */
    if(1 == gPmNvSt.peridown_flag)
    {
        writel(0x20000000, M3PM_SC_BASE_AO + PWR_CTRL9);
    }

}


void pm_mcu_buck3on_pdown(void)
{


    u32 tmp = 0;
    u32 i = 0;

    /* 10 close pll DSP/HIFI/USB/BBP  */
#if 0
    //todo: should be closed in a/c core  or not
/* DSP */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS2_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS2_CTRL3);
    /* HIFI */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS3_CTRL3);
    /* PERI USB */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS6_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS6_CTRL3);
    /* PERI  bbp pll in ABB, config ABB_regs*/
#endif

    /* 9 todo */
    for(i = 0; i < 8; i++)
    {
        gPmBakeupSt.u32NvicEnable[i] = NVIC->ISER[i];
        NVIC->ICER[i] = 0xFFFFFFFF;
    }

    /* 唤醒源未配置 */
    for(i = 0; i < DS_IRQ_NUM; i++)
    {
        enable_irq(pm_deepsleep_irq[i]);
    }
    
    /* 10 bak for power down */
    
    ios_suspend();
    bsp_tsensor_disable();
    m3_pm_stamps->buck3on.after_gpio_suspend = pm_stamp_value();
    sys_reg_bak();
    m3_pm_stamps->buck3on.after_sysreg_suspend = pm_stamp_value();
    (void)sram_bak();
    m3_pm_stamps->buck3on.after_sram_suspend = pm_stamp_value();
    
    clk_bak.crg_dfs1_ctrl1 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    clk_bak.crg_dfs1_ctrl2 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    clk_bak.crg_dfs1_ctrl3 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    clk_bak.pd_crg_clkdiv2 = readl(M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    
    /* 13  ddr pdown  */
    ddr_pdown();

    m3_pm_stamps->buck3on.after_ddr_sref = pm_stamp_value();

    if(gPmCountSt.u32PwrRegbakFlag)
    {
        pm_mcu_bakeup_debug();
    }

    m3_pm_stamps->buck3on.before_sram_retention= pm_stamp_value();

    set_cpu_dbg_suspend(cm3_debug_suspend_bit,1);
            
    /* 13 slow */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x2;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
    do
    {
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp = (tmp >> 3)&0x7;
    }while(tmp != 0x2);
    /* 14 */
    writel(0x0, M3PM_SC_BASE_PD +  + PD_CRG_CLKDIV2);

    /* 15 cpu sleep */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 16 dummy: to make sure */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);

    ISB();

    /* wfi */
    if(!gPmCountSt.u32SleepWithoutWfiFlag)
    WFI();
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
}

void pm_mcu_buck3on_pup(void)
{

    u32 tmp = 0;
    u32 tmp1 = 0;
    u32 i = 0;
    u32 arm_boot_type = 0;
    //__asm__ __volatile__ ("b .");  // debug for pmu ldo27 overload

    /* 1 a9 pll */
    writel(clk_bak.crg_dfs1_ctrl1, M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    writel(clk_bak.crg_dfs1_ctrl2, M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    writel(clk_bak.crg_dfs1_ctrl3, M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    
    /* new added --- todo, 后续buck3on可以不需要 - guoliang */
    writel( 0x2C, M3PM_SC_BASE_PD + CRG_DFS5_CTRL3);
    
    /* 2 clk div */
    writel(clk_bak.pd_crg_clkdiv2, M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    /* 3 normal */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x4;
    do{
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = (tmp1 & 0x78) >> 3;
    }while((tmp1 != 0x4));

    m3_pm_stamps->buck3off.after_sram_out_retention= bsp_get_slice_value();
    
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_0);

    slice_resume(); /* udelay timer init , needed by ddr pup */

    pm_ldo32_enable();

    /* 4 check arm_boot_type */
    arm_boot_type = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    if(arm_boot_type & (0x1UL<<30))
    {
        m3_pm_stamps->buck3on.before_ddr_restore = pm_stamp_value();
        /* 5 ddr power up */
        ddr_pup();

        m3_pm_stamps->buck3on.after_ddr_restore = pm_stamp_value();
        /* 10 clear arm_boot_type */
        arm_boot_type &= ~(0x1UL<<30);
        writel(arm_boot_type, M3PM_SC_BASE_AO + PWR_CTRL0);
    }
    else
    {
        m3_pm_stamps->buck3on.no_boot_not_ddr_restore= pm_stamp_value();
        m3_pm_stamps->buck3on.no_sm_cnt++;

        /* 6 ddr io */
        writel((0x1<<24), M3PM_SC_BASE_AO + PWR_CTRL5);
        /* 7 wait pll lock */
        if((readl(M3PM_SC_BASE_PD + SC_TOP_CTRL21)&0x1) == 0)
        { /* bit0 = 0 mission mode */
            /* wait pll lock*/
            udelay(20);
            do{
                tmp  = readl(0x9004E098)&0x1; /* wait ac_pll lock */
                tmp1 = readl(0x9004E09C);     /* wait dx_pll lock */
                tmp1 = (tmp1>>28) & 0xf;
            }while((tmp != 0x0)||(tmp1)!=0xf);
        }
        /* 8 ddr out sref */
        pm_ddr_out_sref();

        m3_pm_stamps->buck3on.after_ddr_out_sref = pm_stamp_value();
        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_2);

        tmp = readl(0x90048000); tmp |= 0x1<<1; writel(tmp, 0x90048000);

        /*9 ddrc restore including 0x9004_8028 bit0=1,0x9004_801c bit0=1,0x9004_8200 bit12=1 */
        tmp = readl(0x90048028); tmp |= 0x1;    writel(tmp, 0x90048028);
        tmp = readl(0x9004801c); tmp |= 0x1;    writel(tmp, 0x9004801c);
        tmp = readl(0x90048200); tmp |= 0x1<<12;writel(tmp, 0x90048200);
        
        ddr_hit_test();

    }

    m3_pm_stamps->buck3on.before_sysreg_resume = pm_stamp_value();
    sys_reg_restore();
    m3_pm_stamps->buck3on.after_sysreg_resume = pm_stamp_value();
    (void)sram_restore();
    m3_pm_stamps->buck3on.after_sram_resume = pm_stamp_value();

    bsp_tsensor_enable();
    /* 11 ios resume */
    ios_resume();
    m3_pm_stamps->buck3on.after_gpio_resume = pm_stamp_value();

    /* 12 normal io out retention no need */
    /* writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL5);*/

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_3);

    pm_mcu_wakeup_debug();

    pm_set_bbpwakeup_flag();

    /* 11 */
    for(i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ISER[i] = gPmBakeupSt.u32NvicEnable[i];
    }
    m3_pm_stamps->buck3on.buck3on_pup_end = pm_stamp_value();


}

static void pm_mcu_bakeup_debug(void)
{
// todo
}

static void pm_mcu_wakeup_debug(void)
{
// todo
}

/*lint -restore +e737*/
static void pm_mcu_process(void)
{
    u32 buck3offflag = ACORE_BUCK3_ONOFF_FLAG | CCORE_BUCK3_ONOFF_FLAG;
    s32 ret = 0;

    pm_dfs_bak();
    m3_pm_stamps->after_dfs_bak = pm_stamp_value();

    if((1 == gPmNvSt.buck3off_flag)&&(buck3offflag == 0))
    {
        m3_pm_stamps->buck3off.buck3off_cnt++;
        m3_pm_stamps->buck3off.in_buck3off_branch = pm_stamp_value();
        
        ret = dpm_suspend_buck3off();
        
        m3_pm_stamps->buck3off.after_dpm_suspend_buck3off= pm_stamp_value();
        
        if(ret == 0 )
        {
            pm_config_init_buck3off();
            m3_pm_stamps->buck3off.after_buck3off_init = pm_stamp_value();
            pm_mcu_buck3off_pdown();
            pm_mcu_buck3off_pup();

            ret = dpm_resume_buck3off() ;
            m3_pm_stamps->buck3off.after_dpm_resume_buck3off= pm_stamp_value();
            if(ret != 0 )
            {
                __asm__ __volatile__ ("b .");
            }
                pm_debug_udelay(5,gNvDrxDelaySt.lpm3_4);
        }
        else
        {
            __asm__ __volatile__ ("b .");
        }
    }
    else
    {
        m3_pm_stamps->buck3on.buck3on_cnt++;
        m3_pm_stamps->buck3on.in_buck3on_branch = pm_stamp_value();
        
        pm_config_init_buck3on();
        pm_mcu_buck3on_pdown();
        pm_mcu_buck3on_pup();
    }
}

/*lint --e{718,732,746}*/
void pm_normal_wfi(void)
{
    int irqlock;
    u32 sleeptime = 0;
    u32 tc = 0;
    u32 tmp = 0;
    u32 btime = 0;
    u32 ftime = 0;

    local_irq_save(irqlock);

    tc = rt_suspend();
    if(tc>1)
    {
        gPmCountSt.u32NormalWfiTimes++;
        m3_pm_stamps->wfi_cnt = gPmCountSt.u32NormalWfiTimes;
        btime = pm_stamp_value();

        /* pwr_ctrl0 bit25 bit26 set 0*/
        /*
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp &= ~0x6000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);
            */
        /* pwr_ctrl0 bit25 set 1*/
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp |= 0x2000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);

/* pwr_ctrl0 bit25 bit26 set 0*/
tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
tmp &= ~0x6000000;
writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);



        /* m3 will be wakeup by debug when connected to emulator */
        /* disable irq can only stop irq respond*/
        set_cpu_dbg_suspend(cm3_debug_suspend_bit,1); 
        /*enable_irq(M3_CM3_DBG_WAKE_INT);*/
        
        WFI();
/*
        disable_irq(M3_CM3_DBG_WAKE_INT);
        clear_pending_irq(M3_CM3_DBG_WAKE_INT);
*/
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

/* pwr_ctrl0 bit25 bit26 set 1*/
tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
tmp |= 0x6000000;
writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

        /* pwr_ctrl0 bit25 bit26 set 1
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp |= 0x6000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);
        */

        ftime = pm_stamp_value();
        sleeptime = (ftime - btime)* 1000 / PM_MCU_TIMER_CLK;
    }
    else
    {
        sleeptime = 0;
    }
    rt_resume(sleeptime);

    local_irq_restore(irqlock);

}

void pm_deepsleep(void)
{
    int irqlock;
    u32 sleeptime = 0;
    u32 tc = 0;
    s32 tmp = 0;
    u32 btime = 0;
    u32 ftime = 0;

    local_irq_save(irqlock);
    
    m3_pm_stamps->before_dpm_suspend = pm_stamp_value();
    tmp = dpm_suspend();
    m3_pm_stamps->after_dpm_suspend = pm_stamp_value();
    if(tmp == DPM_OK)
    {
        gPmSt.u32SleepFlag = 1;
        tc = rt_suspend();
        if(tc>1)
        {
            gPmCountSt.u32DeepSleepTimes++;
            m3_pm_stamps->deepsleep_cnt = gPmCountSt.u32DeepSleepTimes;
            btime = pm_stamp_value();

            pm_mcu_process();

            ftime = pm_stamp_value();
            sleeptime = (ftime - btime)* 1000 / PM_MCU_TIMER_CLK;
        }
        else
        {
            sleeptime = 0;
        }
        rt_resume(sleeptime);
        gPmSt.u32SleepFlag = 0;
        m3_pm_stamps->before_dpm_resume = pm_stamp_value();

        tmp = dpm_resume();
        /* amon do sr only when amon is running
         in this condition the init func is called again after deepsleep */
        amon_init_dfs();
        m3_pm_stamps->after_dpm_resume = pm_stamp_value();

        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_4);

        if(tmp != DPM_OK)
        {
            gPmErrorSt.u32DpmResumeErrTimes++;
            __asm__ __volatile__ ("b ."); /*err not allowed*/
        }
    }
    else
    {
        gPmErrorSt.u32DpmSuspendErrTimes++;
        m3_pm_stamps->dpm_fail_cnt = gPmErrorSt.u32DpmSuspendErrTimes;
    }

    local_irq_restore(irqlock);

}

void idle_task(void)
{

    int irqlock;

    local_irq_save(irqlock);

    bsp_wdt_feed();

    //udelay(2000); /* todo for test */

    /* deepsleep 0投票睡眠，1反对睡眠 */
    if((!(gPmSt.u32VoteMap & gPmSt.u32VoteMask)) && (1 == gPmNvSt.deepsleep_flag)
       && (*(u32*)(SRAM_BASE_ADDR+SRAM_OFFSET_TLDSP_SHARED) != 1))
    {
        pm_deepsleep();
    }
    else if((sys_initial==1) && ((1 == gPmNvSt.normalwfi_flag)))
    {
        pm_normal_wfi();
    }
    
    local_irq_restore(irqlock);
}
#if 0
void pm_print_wsrc(void)
{
    u32 i = 0;
    u32 j = 0;
    u32 tmp = 0;

    printk("ISER 0x%x 0x%x 0x%x 0x%x\n", NVIC->ISER[0], NVIC->ISER[1], NVIC->ISER[2], NVIC->ISER[3]);

    for(j = 0; j < 4; j++)
    {
        printk("wsrc num%d:",j);
        tmp = readl(PWR_CTRL16+j*4);
        for(i = 0; i < 32; i++)
        {
            if(tmp & ((u32)0x1<<i))
            {
                printk(" %d ",i+j*32+16);
            }
        }
        printk("\n");
    }

    pm_print_wakeup_debug();
}

static void pm_print_wakeup_debug(void)
{
    u32 i = 0;
    u32 j = 0;
    u32 tmp = 0;

    if(gPmCountSt.u32WakeupDebugFlag)
    {
        for(j = 0; j < 4; j++)
        {
            printk("wakeup num%d:",j);
            tmp = readl(PWR_SRAM_WAKEUP_REG+m3_record_num*0x20+0x10+j*4);
            for(i = 0; i < 32; i++)
            {
                if(tmp & ((u32)0x1<<i))
                {
                    printk(" %d ",i+j*32+16);
                }
            }
            printk("\n");
        }
    }
}
#endif
static void pm_set_peri_down(u32 flag)
{
    if(flag)
    {
        writel(0x20000000, PWR_CTRL9);
    }
    else
    {
        writel(0x40000000, PWR_CTRL9);
    }
}

void pm_set_debug(u32 type, u32 flag)
{
    switch(type)
    {
        case 1:
            gPmNvSt.normalwfi_flag = (BSP_U8)flag;
            break;
        case 2:
            gPmNvSt.deepsleep_flag = (BSP_U8)flag;
            break;
        case 3:
            if(0 == gPmNvSt.buck3off_flag)
            {
                gPmNvSt.peridown_flag = (BSP_U8)flag;
                pm_set_peri_down(flag);
            }
            else
            {
                printk("buckoff\n");
            }
            break;
        case 4:
            gPmCountSt.u32PwrRegbakFlag = flag;
            break;
        case 5:
            gPmCountSt.u32WakeupDebugFlag = flag;
            break;
        case 6:
            gPmCountSt.u32PrintIrqWsrcFlag = flag;
            break;
        case 7:
            gPmCountSt.u32SleepWithoutWfiFlag= flag;
            break;
        default:
            printk("inputErr\n");
            break;
    }
}


