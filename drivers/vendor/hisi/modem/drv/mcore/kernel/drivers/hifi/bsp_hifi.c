/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_hifi.c
*
*   作    者 :  z00227143
*
*   描    述 :  本文件主要完成HIFI的低功耗处理
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/

/*lint --e{537} */

#include <cmsis_os.h>

#include <product_config.h>

#include <osl_types.h>
#include <osl_bio.h>
#include <mdrv_ipc.h>
#include <bsp_sram.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <bsp_dsp.h>
#include <bsp_version.h>
#include <bsp_hardtimer.h>
#include <m3_pm.h>

#if 0 /*CONFIG_OF不采用DTS方式*/
#include "sysctrl_interface.h"
#else
#include <hi_hifi.h>

/*#include <hi_base.h>

#include <hi_syssc.h>
#include <hi_syscrg.h>
#include <hi_pwrctrl.h>
#include <hi_dsp.h>
#include <hi_syssc_interface.h>
#include <hi_pwrctrl_interface.h>
#include <hi_syscrg_interface.h>*/

#endif


#ifdef CONFIG_HIFI


int bsp_hifi_run(void)
{
   hifi_run();
   return 0;
}

int bsp_hifi_stop(void)
{
    hifi_stop();
    return 0;
}

int bsp_hifi_power_on(void)
{
    hifi_power_on();
    udelay(30);
    hifi_iso_dis();
    return 0;
}

int bsp_hifi_power_off(void)
{
    hifi_iso_en();
    hifi_power_off();
    return 0;
}

int bsp_hifi_clock_enable(void)
{
    hifi_clock_enable();
    return 0;
}

int bsp_hifi_clock_disable(void)
{
    hifi_clock_disable();
    return 0;
}

int bsp_hifi_unreset(void)
{
    hifi_unreset();
    return 0;
}

int bsp_hifi_reset(void)
{
	hifi_reset();
    return 0;
}

int bsp_hifi_restore(void)
{
    u32 i;
    u32 flag;
    u32 length;
    struct drv_hifi_sec_load_info *section_info = (struct drv_hifi_sec_load_info *)(SHM_BASE_ADDR + SHM_OFFSET_HIFI);

    if (section_info->sec_magic != HIFI_MEM_BEGIN_CHECK32_DATA && (HIFI_STRESS_MAGIC != section_info->sec_magic))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "HIFI image not found\r\n");
        return -1;
    }

    for (i = 0; i < section_info->sec_num; i++)
    {
        for (length = 0; length < section_info->sec_addr_info[i].sec_length; length += 4)
        {
            flag = readl(section_info->sec_addr_info[i].sec_source_addr + length);
            writel(flag, section_info->sec_addr_info[i].sec_dest_addr + length);
        }
    }

	if(HIFI_STRESS_MAGIC == section_info->sec_magic)
	{
		writel(DDR_HIFI_ADDR, HIFI_DATA_TCM_ADDR + 0x8004);
		writel(DDR_HIFI_SIZE, HIFI_DATA_TCM_ADDR + 0x8008);

		writel(SHM_BASE_ADDR + SHM_OFFSET_HIFI, HIFI_DATA_TCM_ADDR + 0x800c);
		writel(SHM_SIZE_HIFI, HIFI_DATA_TCM_ADDR + 0x8010);

		writel(HIFI_TCM_START_ADDR + 0xf000, HIFI_DATA_TCM_ADDR + 0x8014);
		writel(0x1000, HIFI_DATA_TCM_ADDR + 0x8018);	
		
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "HIFI stress arg config\n");
	}

    return 0;
}

int bsp_hifi_store(void)
{
    return 0;
}

void bsp_hifi_resume(u32 value)
{
    int ret = 0;

    pm_hifi_pll_open(PM_PWR_VOTE_HIFI);

    ret |= bsp_ipc_int_disable(IPC_MCU_INT_SRC_HIFI_PU);

    ret |= bsp_hifi_power_on();
    ret |= bsp_hifi_clock_enable();
    ret |= bsp_hifi_unreset();
    ret |= bsp_hifi_restore();
    ret |= bsp_hifi_run();

    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to resume hifi\r\n");
    }
    else
    {
        pm_wake_lock(PM_PWR_VOTE_HIFI);
    }
}

void bsp_hifi_suspend(u32 value)
{
    int ret = 0;

    ret |= bsp_hifi_stop();
    ret |= bsp_hifi_reset();
    ret |= bsp_hifi_clock_enable();
    ret |= bsp_hifi_power_off();

    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to suspend hifi\r\n");
    }
}

void bsp_hifi_init(void)
{
    int ret = 0;

    pm_wake_unlock(PM_PWR_VOTE_HIFI);

    ret |= bsp_ipc_int_connect(IPC_MCU_INT_SRC_HIFI_PU, bsp_hifi_resume, 0);

    ret |= bsp_ipc_int_enable(IPC_MCU_INT_SRC_HIFI_PU);
    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to init hifi\r\n");
        return;
    }
}

#else

void bsp_hifi_init(void)
{
    pm_wake_unlock(PM_PWR_VOTE_HIFI);
}

int bsp_hifi_restore(void)
{
    return 0;
}

int bsp_hifi_run(void)
{
    return 0;
}

int bsp_hifi_stop(void)
{
    return 0;
}

#endif


