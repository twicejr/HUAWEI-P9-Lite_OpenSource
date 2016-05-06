/*----------------------------------------------------------------------------
 *      k3v3 m3 modem pm
 *----------------------------------------------------------------------------
 *      Name:    m3_dpm_modem.c
 *----------------------------------------------------------------------------
 *      This code is part of k3v3 modem PWR.
 *---------------------------------------------------------------------------*/

#include <soc_memmap_m3.h>
#include <osl_common.h>
#include <hi_base.h>
#include <hi_syssc.h>
#include <bsp_shared_ddr.h>
#include <m3_pm_modem.h>
#include <m3_cpufreq_modem.h>
#include <dpm_balong.h>
#include <bsp_hardtimer.h>
#include <edma_balong.h>
#include <m3_dpm_modem.h>
#include <m3_pm_modem.h>
#include <drv_nv_def.h>
#include <modem_start.h>

extern DRV_DRX_DELAY_STRU gNvDrxDelaySt;

__ao_data T_PM_SYSCTRL_ST g_sysctrl_table[] =
{
    {HI_SYSCTRL_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET, HI_CRG_CLKEN3_OFFSET, HI_CRG_CLKDIS3_OFFSET, RESUME_UNUSED_ADDR, 0x5000000},
    {HI_SYSCTRL_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET, HI_CRG_CLKEN4_OFFSET, HI_CRG_CLKDIS4_OFFSET, RESUME_UNUSED_ADDR, 0x527B06},
    {HI_SYSCTRL_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET, HI_CRG_CLKEN5_OFFSET, HI_CRG_CLKDIS5_OFFSET, RESUME_UNUSED_ADDR, 0x7000FF},
    {HI_SYSCTRL_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET, HI_CRG_SRSTEN3_OFFSET, HI_CRG_SRSTDIS3_OFFSET, RESUME_UNUSED_ADDR, 0x80000000},
    {HI_SYSCTRL_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_CRG_CLK_SEL3_OFFSET, 0x72},
    {HI_SYSCTRL_BASE_ADDR, HI_SC_CTRL20_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_SC_CTRL20_OFFSET, 0x9140006B},
    {HI_SYSCTRL_BASE_ADDR, HI_SC_CTRL21_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_SC_CTRL21_OFFSET, 0x17EAC10},
    {HI_SYSCTRL_BASE_ADDR, HI_SC_CTRL69_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_SC_CTRL69_OFFSET, 0x69},
    {HI_SYSCTRL_BASE_ADDR, HI_SC_CTRL103_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_SC_CTRL103_OFFSET, 0xFFFFFFFF},
    {HI_SYSCTRL_BASE_ADDR, HI_SC_CTRL105_OFFSET, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, HI_SC_CTRL105_OFFSET, 0xFFFFFFFF}
};

#define SYSCTRL_SAVE_NUM   sizeof(g_sysctrl_table)/sizeof(T_PM_SYSCTRL_ST)

__ao_data u32 g_sysctrl_save[SYSCTRL_SAVE_NUM];

__ao_data T_PM_SYSCTRL_ST g_ap_sysctrl_table[] =
{
    {HI_PCTRL_REGBASE_ADDR, 0xC18, RESUME_UNUSED_ADDR, RESUME_UNUSED_ADDR, 0xC18, 0x0000FFFF}
};

#define AP_SYSCTRL_SAVE_NUM   sizeof(g_ap_sysctrl_table)/sizeof(T_PM_SYSCTRL_ST)

__ao_data u32 g_ap_sysctrl_save[SYSCTRL_SAVE_NUM];

__ao_data T_DPM_COUNT_ST g_dpm_count_st = {0};

__ao_data char modem_string[9] = {'m', '_', 'r', 'e', 's', 'u', 'm', 'e'};

void modem_sysctrl_suspend(void)
{
    u32 i = 0;

    memset((void*)&g_sysctrl_save, 0x0, sizeof(g_sysctrl_save));

    for(i=0; i<SYSCTRL_SAVE_NUM; i++)
    {
        g_sysctrl_save[i] = readl(g_sysctrl_table[i].base_addr + g_sysctrl_table[i].suspend_offset);
    }
}

__ao_func void modem_sysctrl_resume(void)
{
    u32 i = 0;
    u32 tmp = 0;

    /* cpufreq */
    /* 3,4,5 */
    mdm_a9pll_init();

    mdm_bbepll_init();

    /* 12  a9 ref_clk enable*/
    writel(0x1<<25, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKEN3_OFFSET);

     /* 13 bus div: 0,0,3*/
    writel(0x40040300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

    /* 14 */
    writel(0x40010300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

    for(i=0; i<SYSCTRL_SAVE_NUM; i++)
    {
        if(g_sysctrl_table[i].resume_en_offset != RESUME_UNUSED_ADDR)
        {
            tmp = g_sysctrl_save[i] & g_sysctrl_table[i].bitmap;
            writel(tmp, g_sysctrl_table[i].base_addr + g_sysctrl_table[i].resume_en_offset);
        }
        if(g_sysctrl_table[i].resume_dis_offset != RESUME_UNUSED_ADDR)
        {
            tmp = (~g_sysctrl_save[i]) & g_sysctrl_table[i].bitmap;
            writel(tmp, g_sysctrl_table[i].base_addr + g_sysctrl_table[i].resume_dis_offset);
        }
        if(g_sysctrl_table[i].resume_all_offset != RESUME_UNUSED_ADDR)
        {
            tmp = readl(g_sysctrl_table[i].base_addr + g_sysctrl_table[i].resume_all_offset);
            tmp = (tmp & (~g_sysctrl_table[i].bitmap)) | (g_sysctrl_save[i] & g_sysctrl_table[i].bitmap);
            writel(tmp, g_sysctrl_table[i].base_addr + g_sysctrl_table[i].resume_all_offset);
        }
    }
}

void ap_sysctrl_suspend(void)
{
    u32 i = 0;

    memset((void*)&g_ap_sysctrl_save, 0x0, sizeof(g_ap_sysctrl_save));

    for(i=0; i<AP_SYSCTRL_SAVE_NUM; i++)
    {
        g_ap_sysctrl_save[i] = readl(g_ap_sysctrl_table[i].base_addr + g_ap_sysctrl_table[i].suspend_offset);
    }
}

__ao_func void ap_sysctrl_resume(void)
{
    u32 i = 0;
    u32 tmp = 0;

    modem_subsys_init();

    /* ap pctrl */
    for(i=0; i<AP_SYSCTRL_SAVE_NUM; i++)
    {
        if(g_ap_sysctrl_table[i].resume_en_offset != RESUME_UNUSED_ADDR)
        {
            tmp = g_ap_sysctrl_save[i] & g_ap_sysctrl_table[i].bitmap;
            writel(tmp, g_ap_sysctrl_table[i].base_addr + g_ap_sysctrl_table[i].resume_en_offset);
        }
        if(g_ap_sysctrl_table[i].resume_dis_offset != RESUME_UNUSED_ADDR)
        {
            tmp = (~g_ap_sysctrl_save[i]) & g_ap_sysctrl_table[i].bitmap;
            writel(tmp, g_ap_sysctrl_table[i].base_addr + g_ap_sysctrl_table[i].resume_dis_offset);
        }
        if(g_ap_sysctrl_table[i].resume_all_offset != RESUME_UNUSED_ADDR)
        {
            tmp = readl(g_ap_sysctrl_table[i].base_addr + g_ap_sysctrl_table[i].resume_all_offset);
            tmp = (tmp & (~g_ap_sysctrl_table[i].bitmap)) | (g_ap_sysctrl_save[i] & g_ap_sysctrl_table[i].bitmap);
            writel(tmp, g_ap_sysctrl_table[i].base_addr + g_ap_sysctrl_table[i].resume_all_offset);
        }
    }
}

#define HI_AP_SRAM_MEM_BASE_ADDR             (0xE0800000)
#define PM_SHM_MEM_RESTORE_AXI_ADDR         (SHM_BASE_ADDR+SHM_OFFSET_MEM_RESTORE_AXI)
s32 sram_suspend(void)
{
    s32 ret = 0;

    ret = bsp_edma_m2m_channel(0, HI_AP_SRAM_MEM_BASE_ADDR, PM_SHM_MEM_RESTORE_AXI_ADDR+0x20000000, SHM_MEM_RESTORE_AXI_SIZE);
    if(ret != 0)
    {
        g_dpm_count_st.suspend_dma_start_times++;
        return 1;
    }
	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);

    return ret;
}

__ao_func void sram_resume_start(void)
{
    s32 ret = 0;

    ret = bsp_edma_m2m_channel(0, PM_SHM_MEM_RESTORE_AXI_ADDR+0x20000000, HI_AP_SRAM_MEM_BASE_ADDR,  SHM_MEM_RESTORE_AXI_SIZE);
    if(ret != 0)
    {
        g_dpm_count_st.resume_dma_start_times++;
		while(1);
    }
}

void sram_resume_ok(void)
{
    s32 ret = 0;

	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);
}

s32 modem_suspend(void)
{
    s32 ret = 0;

	memcpy((void*)(PWR_TCM_MODEM_SUSPEND_ADDR), "m_suspend", sizeof("m_suspend"));
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_SUSPEND_ADDR + 0x10);
    pm_modem_to_a9pll();
    ret = dpm_suspend();
    if(ret != DPM_OK)
    {
        goto err0;
    }
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_SUSPEND_ADDR + 0x14);
    ret = sram_suspend();
    if(ret != 0)
    {
        goto err1;
    }
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_SUSPEND_ADDR + 0x18);
    cpufreq_suspend();
    modem_sysctrl_suspend();
    pm_modem_to_192();
    ap_sysctrl_suspend();
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_SUSPEND_ADDR + 0x1C);
    return 0;

err1:
    (void)dpm_resume();
err0:
    pm_modem_to_192();
    return 1;
}

__ao_func void modem_resume(void)
{
    u32 status;
	status = SCINT_STATUS;
    if(status & 0xc00000)
    {
        writel(0x12345678, PM_SHM_TIMESTAMP_ADDR);
    }
    else
    {
        writel(0x87654321, PM_SHM_TIMESTAMP_ADDR);
    }
    mdm_udelay(5, gNvDrxDelaySt.lpm3_0);
	memcpy((void*)(PWR_TCM_MODEM_RESUME_ADDR), modem_string, 8);
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_RESUME_ADDR + 0x10);
    /* modem use a9 pll */
    ap_sysctrl_resume();
    modem_sysctrl_resume();
    sram_resume_start();
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_RESUME_ADDR + 0x14);
    mdm_udelay(5, gNvDrxDelaySt.lpm3_1);
}

void modem_resume_ok(void)
{
    mdm_udelay(5, gNvDrxDelaySt.lpm3_2);
	memcpy((void*)(PWR_TCM_MODEM_RESUME_ADDR + 0x20), "m_resume_ok", sizeof("m_resume_ok"));
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_RESUME_ADDR + 0x30);
    sram_resume_ok();
	cpufreq_resume();
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_RESUME_ADDR + 0x34);
	(void)dpm_resume();
	writel(bsp_get_slice_value(), PWR_TCM_MODEM_RESUME_ADDR + 0x38);
    mdm_udelay(5, gNvDrxDelaySt.lpm3_3);
}

/* 1:lte bbp wakeup     0:not lte bbp wakeup */
void modem_set_bbpwakeup_flag(u32 flag)
{
    writel(flag, PM_SHM_TIMESTAMP_ADDR);
}

void modem_save_drx_timestamp(void)
{
    u32 tmp = 0;

    tmp = readl(PM_SHM_TIMESTAMP_ADDR);
    if(tmp == 1)
    {
        writel(*(u32*)(0x2300c), PM_SHM_TIMESTAMP_ADDR + 0x10);
		writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x10), PM_SHM_TIMESTAMP_ADDR + 0x14);
		writel(*(u32*)(PWR_TCM_MODEM_RESUME_ADDR + 0x30), PM_SHM_TIMESTAMP_ADDR + 0x18);
		writel(*(u32*)(PWR_TCM_MODEM_UP_ADDR + 0x10), PM_SHM_TIMESTAMP_ADDR + 0x1C);
    }
}
