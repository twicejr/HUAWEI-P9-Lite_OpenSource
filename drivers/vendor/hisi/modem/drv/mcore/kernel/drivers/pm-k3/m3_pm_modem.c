/*----------------------------------------------------------------------------
 *      k3v3 m3 modem pm
 *----------------------------------------------------------------------------
 *      Name:    m3_pm_modem.c
 *----------------------------------------------------------------------------
 *      This code is part of k3v3 modem PWR.
 *---------------------------------------------------------------------------*/

#include <cmsis_os.h>
#include <osl_common.h>
#include <soc_memmap_m3.h>
#include <hi_base.h>
#include <hi_syssc.h>
#include <bsp_shared_ddr.h>
#include <mdrv_ipc.h>
#include <ipc_balong.h>
#include <wdt_balong.h>
#include <bsp_icc.h>
#include <m3_cpufreq_modem.h>
#include <m3_modem.h>
#include <wakelock.h>
#include <bsp_hardtimer.h>
#include <m3_dpm_modem.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_pmu_hi6561.h>
#include <m3_pm_modem.h>

__ao_data T_PM_ST gPmSt;
__ao_data T_PM_COUNT_ST gPmCountSt;
__ao_data extern T_DPM_COUNT_ST g_dpm_count_st;
__ao_data DRV_DRX_DELAY_STRU gNvDrxDelaySt;

u32 gCcoreWsrc[]={M3_IPC_M2C_INT0, M3_IPC_M2C_INT1, M3_TIMER20_INT, M3_TIMER31_INT, \
                  M3_TDS_DRX_ARM_WAKEUP_INT, M3_LTE_ARM_WAKEUP_INT, M3_W_ARM_INT_02, \
				  M3_G1_INT_BBP_TO_CPU_32K, M3_G2_INT_BBP_TO_CPU_32K, M3_IPF_INT0};
#define PM_CCORE_WSRC_NUM          (sizeof(gCcoreWsrc) / sizeof(u32))

#define K3_NVIC    ((NVIC_Type *)(0xE000E100))


void IntIpcModemHandler(u32 irq)
{
    pm_debug_clr_timer();
	pm_modem_down();
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_DOWN_ADDR + 0x18);
}

void IntCcoreHandler(void)
{
    u32 irq = 0;

    irq =  get_irq();
    if(((irq-16) == M3_LTE_ARM_WAKEUP_INT)||((irq-16) == M3_TDS_DRX_ARM_WAKEUP_INT))
    {
        if(readl(PM_SHM_TIMESTAMP_ADDR) == 0x12345678)
        {
            writel(1, PM_SHM_TIMESTAMP_ADDR);
            writel(*(u32*)(TICKMARK_BASE + 0x0), PM_SHM_TIMESTAMP_ADDR + 0x10);
            writel(*(u32*)(TICKMARK_BASE + 0x4), PM_SHM_TIMESTAMP_ADDR + 0x14);
            writel(*(u32*)(TICKMARK_BASE + 0x8), PM_SHM_TIMESTAMP_ADDR + 0x18);
            writel(*(u32*)(TICKMARK_BASE + 0xC), PM_SHM_TIMESTAMP_ADDR + 0x1c);
            writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x10), PM_SHM_TIMESTAMP_ADDR + 0x20);
            writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x14), PM_SHM_TIMESTAMP_ADDR + 0x24);
            writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x30), PM_SHM_TIMESTAMP_ADDR + 0x28);
            writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x34), PM_SHM_TIMESTAMP_ADDR + 0x2C);
            writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x38), PM_SHM_TIMESTAMP_ADDR + 0x30);
            writel(bsp_get_slice_value(), PM_SHM_TIMESTAMP_ADDR + 0x34);
        }
    }
	pm_modem_up();

	if(gPmCountSt.u32PrintIrqWsrcFlag)
	{
		MODEM_PM_PRINT("mdma9 wsrc irq=%d\n", irq);
	}
}

s32 pm_wsrc_icc_read(u32 id , u32 len, void* context)
{
	s32 ret = 0;
	T_PM_MAIL psmail;

    if((len == 0) || (len > sizeof(T_CPUFREQ_MAIL)))
    {
        MODEM_PM_PRINT("icc err\n");
        return -1;
    }

	ret = bsp_icc_read(id, (u8*)&psmail, len);
	if(len != ret)
	{
		return -1;
	}

    switch(psmail.type)
	{
        case PM_TYEP_CSET_WSRC:
			pm_mdma9_wsrc_set(psmail.addr);
			break;
        case PM_TYEP_CUNSET_WSRC:
			pm_mdma9_wsrc_unset(psmail.addr);
			break;
        default:
			break;
    }

	return 0;
}

void pm_wsrc_set_init(void)
{
	u32 ret;
	u32 channel_id_set = 0;

	/* m3 ccore icc */
	channel_id_set = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_WSRC;
	ret = bsp_icc_event_register(channel_id_set, pm_wsrc_icc_read, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
        MODEM_PM_PRINT("pm_wsrc_set_init icc err\n");
		return;
	}
}

void pm_modem_init(void)
{
    u32 i = 0;
    u32 j = 0;
    u32 flag = 0;
    u32 ret = 0;

    if(get_modem_init_flag() == MODEM_ALREADY_INIT_MAGIC)
    {
        flag = 1;
    }

    if(flag == 0)
    {
        memset((void*)&gPmSt, 0x0, sizeof(T_PM_ST));
        memset((void*)&gPmCountSt, 0x0, sizeof(T_PM_COUNT_ST));

	    ret = bsp_nvm_read(NV_ID_DRV_DRX_DELAY, (u8 *)&gNvDrxDelaySt, sizeof(DRV_DRX_DELAY_STRU));
	    if(ret != NV_OK)
	    {
		    printk("nv read err\n");
            memset((void*)&gNvDrxDelaySt, 0x0, sizeof(DRV_DRX_DELAY_STRU));
	    }

        for(i = 0; i < PM_CCORE_WSRC_NUM; i++)
	    {
		    pm_mdma9_wsrc_set(gCcoreWsrc[i]);
	    }
        MODEM_WAKE_SOURCE_SET(DRX_SRC(0) | DRX_SRC(1) | DRX_SRC(2) | DRX_SRC(3) | DRX_SRC(4)) ;
    }
    else if(flag == 1)
    {
        for(i = 0; i < MAX_NVIC_GROUP_NUM; i++)
        {
            for(j = 0; j < 32; j++)
            {
                if(gPmSt.u32CcoreWsrc[i] & (0x1<<j))
                {
                    (void)request_irq(32*i + j, IntCcoreHandler, IRQF_DISABLED, "ccore irq", 0);
                    if(is_wake(MODEM_MASK) == 0)
                    {
                        enable_irq(32*i + j);
                    }
                }
            }
        }
    }

    if(bsp_ipc_int_connect(IPC_MCU_INT_SRC_CCPU_PD, IntIpcModemHandler, 0) != OK)
    {
        MODEM_PM_PRINT("init connect ccpu err\n");
    }

    if(bsp_ipc_int_enable(IPC_MCU_INT_SRC_CCPU_PD) != OK)
    {
        MODEM_PM_PRINT("init enable ccpu err\n");
    }
    pm_wsrc_set_init();

    if(flag == 0)
    {
        MODEM_PM_PRINT("init OK\n");
    }
}

__ao_func void pm_modem_to_192(void)
{
    u32 tmp = 0;
    int irqlock = 0;

	local_irq_save(irqlock);
    /* a9 sleep */
    if(is_wake(MODEM_MASK) == 0)
    {  
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
	    tmp &= ~0x70000;
	    tmp |= 0x40000;
	    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

        /* close a9 pll */
        /* bit[26] = 0 */
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
        tmp &= ~0x4000000;
        writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

        /* bit[0] = 0 bit[1] = 1 */
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
        tmp &= ~0x1;
        writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
        tmp |= 0x2;
        writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);    
    }
	local_irq_restore(irqlock);
}

__ao_func void pm_modem_to_a9pll(void)
{
	u32 tmp = 0;
    int irqlock = 0;

    local_irq_save(irqlock);
    /* open a9 pll */
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
    tmp |= 0x1;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
    tmp &= ~0x2;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

    do
    {
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
        tmp = (tmp >> 26) & 0x1;
    }while(!tmp);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
    tmp |= (0x1<<26);
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
	tmp &= ~0x70000;
	tmp |= 0x10000;
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    local_irq_restore(irqlock);
}

void pm_mdma9_pdown(void)
{
	/* disable a9 and l2 clk */
	writel(0x3<<3, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIS4_OFFSET);

	/* iso ctrl enable */
	writel(0x2, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL4_OFFSET);

	/* reset bit[15] bit[6] */
	writel(0x8040, HI_SYSCTRL_BASE_ADDR + HI_CRG_SRSTEN1_OFFSET);

	/* mtcmos power down */
	writel(0x2, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL7_OFFSET);
}

void pm_mdma9_pup(void)
{
	u32 tmp = 0;

	/* mtcmos power up and wait for complete*/
	writel(0x2, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL6_OFFSET);
	do
	{
		tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_PWR_STAT1_OFFSET);
		tmp = (tmp >> 1) & 0x1;
	}while(!tmp);
    udelay(30);

	/* enable a9 and l2 clk */
	writel((0x3<<3), HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKEN4_OFFSET);

	/* iso ctrl disable */
	writel(0x2, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL5_OFFSET);

	/* unreset  bit[15] bit[6] */
	writel(0x8040, HI_SYSCTRL_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET);
}

void pm_mdma9_wsrc_set(u32 lvl)
{
	u32 groupnum = 0;
	u32 bitnum = 0;

	groupnum = lvl/32;
	bitnum = lvl%32;

    if(groupnum < MAX_NVIC_GROUP_NUM)
    {
	    /* 通过记录的全局变量的值，配置寄存器 */
	    gPmSt.u32CcoreWsrc[groupnum] |= 0x1<<bitnum;
	    (void)request_irq(lvl, IntCcoreHandler, IRQF_DISABLED, "ccore irq", 0);
        switch(lvl)
    	{
            case M3_TIMER20_INT:
                MODEM_WAKE_SOURCE_SET(TIMER_SRC(4));
                break;
            case M3_TIMER30_INT:
                MODEM_WAKE_SOURCE_SET(TIMER_SRC(6));
                break;
            case M3_TIMER31_INT:
                MODEM_WAKE_SOURCE_SET(TIMER_SRC(7));
                break;
            default:
                break;
        }
    }
    else
    {
        MODEM_PM_PRINT("pm_mdma9_wsrc_set lvl = %d\n", lvl);
    }
}

void pm_mdma9_wsrc_unset(u32 lvl)
{
    u32 groupnum = 0;
    u32 bitnum = 0;

    groupnum = lvl/32;
    bitnum = lvl%32;

    if(groupnum < MAX_NVIC_GROUP_NUM)
    {
	    /* 通过记录的全局变量的值，配置寄存器 */
	    gPmSt.u32CcoreWsrc[groupnum] &= ~((u32)0x1<<bitnum);
	    free_irq(lvl, 0);
        switch(lvl)
    	{
            case M3_TIMER20_INT:
                MODEM_WAKE_SOURCE_CLEAR(TIMER_SRC(4));
                break;
            case M3_TIMER30_INT:
                MODEM_WAKE_SOURCE_CLEAR(TIMER_SRC(6));
                break;
            case M3_TIMER31_INT:
                MODEM_WAKE_SOURCE_CLEAR(TIMER_SRC(7));
                break;
            default:
                break;
        }
    }
    else
    {
        MODEM_PM_PRINT("pm_mdma9_wsrc_unset lvl = %d\n", lvl);
    }
}

void pm_mdma9_nvic_enable(void)
{
	u32 tmp = 0;
	u32 i = 0;
    int irqlock = 0;

    local_irq_save(irqlock);
	for(i = 0; i < MAX_NVIC_GROUP_NUM; i++)
	{
		tmp = gPmSt.u32CcoreWsrc[i];
		K3_NVIC->ICPR[i] = tmp;
		K3_NVIC->ISER[i] = tmp;
	}
    local_irq_restore(irqlock);
}

void pm_mdma9_nvic_disable(void)
{
	u32 tmp = 0;
	u32 i = 0;
    int irqlock = 0;

    local_irq_save(irqlock);
	for(i = 0; i < MAX_NVIC_GROUP_NUM; i++)
	{
		tmp = gPmSt.u32CcoreWsrc[i];
		K3_NVIC->ICER[i] = tmp;
	}
    local_irq_restore(irqlock);
}

void pm_modem_up(void)
{
    int irqlock = 0;

    local_irq_save(irqlock);

    memcpy((void*)(PWR_TCM_MODEM_UP_ADDR), "ma9_up", sizeof("ma9_up"));
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_UP_ADDR + 0x10);
    gPmCountSt.u32CcoreWakeTimes++;
    pm_modem_to_a9pll();
	pastar_resume_early();  /* pastar enable,放在pm_mdma9_pup()之前。pastar enable和init之间有2ms延时，所以enable尽量早些 */
    pm_mdma9_nvic_disable();
    pm_dfs_bak(M3_MAX_CPUFREQ_PROFILE);
    bsp_wdt_restart_cwdt();
    mdm_udelay(5, gNvDrxDelaySt.lpm3_4);
	pm_mdma9_pup();
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_UP_ADDR + 0x14);
    wake_lock(MODEM_MASK);

    local_irq_restore(irqlock);
}

void pm_modem_down(void)
{
    int irqlock = 0;
    s32 ret = 0;

    local_irq_save(irqlock);
	memcpy((void*)(PWR_TCM_MODEM_DOWN_ADDR), "ma9_down", sizeof("ma9_down"));
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_DOWN_ADDR + 0x10);
    pm_mdma9_pdown();
    pastar_suspend_late();  /* pastar disable,放在pm_mdma9_pdown()之后 */
    bsp_wdt_stop_cwdt();
	pm_mdma9_nvic_enable();
    gPmCountSt.u32CcoreSleepTimes++;
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_DOWN_ADDR + 0x14);
    wake_unlock(MODEM_MASK);
    pm_modem_to_192();
    ret = modem_request_ddr(0);
    if(ret != 0)
    {
        gPmCountSt.u32CcoreDdrDfsErrTimes++;
    }
    local_irq_restore(irqlock);
}


s32 pm_wakeup_ccore(void)
{
	u32 channel_id = (ICC_CHN_MCORE_CCORE << 16) | MCORE_CCORE_FUNC_WAKEUP;
	s32 ret = 0;
    u32 pm_msg;
	u32 msglen = sizeof(pm_msg);

	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)
	{
		return -1;
	}
    return 0;
}

void pm_debug_clr_timer(void)
{
	writel(0x0, PWR_SRAM_TIMER0);
	writel(0x0, PWR_SRAM_TIMER1);
	writel(0x0, PWR_SRAM_TIMER2);
	writel(0x0, PWR_SRAM_TIMER3);
}

void pm_set_debug(u32 type, u32 flag)
{
	switch(type)
	{
		case 6:
			gPmCountSt.u32PrintIrqWsrcFlag = flag;
			break;
		default:
			printk(" input error\n");
			break;
	}
}

__ao_func void mdm_udelay (u32 ms, u32 flag)
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

void pm_print_debug(void)
{
	printk("ccore sleep time:%d\n", gPmCountSt.u32CcoreSleepTimes);
    printk("ccore wake time:%d\n", gPmCountSt.u32CcoreWakeTimes);
    printk("ccore ddrdfs err time:%d\n", gPmCountSt.u32CcoreDdrDfsErrTimes);
	printk("PrintIrqWsrcFlag:%d\n", gPmCountSt.u32PrintIrqWsrcFlag);
	printk("s_dma_start_times:%d\n", g_dpm_count_st.suspend_dma_start_times);
	printk("s_dma_check_times:%d\n", g_dpm_count_st.suspend_dma_check_times);
	printk("r_dma_start_times:%d\n", g_dpm_count_st.resume_dma_start_times);
	printk("r_dma_check_times:%d\n", g_dpm_count_st.resume_dma_check_times);
}


