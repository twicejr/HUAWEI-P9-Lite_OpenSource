

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef WIN32
#include <linux/string.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/memory.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <mach/irqs.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/arm_timer.h>
#include <linux/slab.h>
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <mach/io.h>
#include <mach/platform.h>
#include "product_config.h"
#endif
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>
#include <mach/pwrctrl/pwrctrl_dfs.h>
#include "drv_timer.h"
#if defined(CHIP_BB_HI6210)
#include"soc_peri_sctrl_interface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if defined(CHIP_BB_HI6210)
int g_tmp = 0;
ST_PWC_SWITCH_STRU * g_stAcpuPwcSwitch = &g_tmp;
#else
ST_PWC_SWITCH_STRU * g_stAcpuPwcSwitch = NULL;
#endif
PWRCTRL_ACPU_EXC_LOG_STRU * g_stAcpuPwcExcLog = NULL;
PWC_MCU_EXC_LOG_STRU * g_stMcuLogExt = NULL;


struct wake_lock g_ulTstwakelock;

u32_t   g_ulPwcDebugTrace = 0;

u32_t g_ulpwrctrl_print_switch = 0;

u32_t g_pwc_init_flag = 0;

extern s32_t pwrctrl_timer_addr_remap(void);

/*****************************************************************************
  3 函数实现
*****************************************************************************/


void pwrctrl_print_switch_set(unsigned int flag,int mode)
{
    /*bit模式*/
    if(0 == mode)
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_print_switch_set,old value:0x%x\n",g_ulpwrctrl_print_switch,0,0,0,0,0);
        g_ulpwrctrl_print_switch |= (1<<flag);
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_print_switch_set,new value:0x%x\n",g_ulpwrctrl_print_switch,0,0,0,0,0);
    }
    else/*一次设置模式*/
    {
        g_ulpwrctrl_print_switch = flag;
    }
}

u32_t pwrctrl_print_switch_get(void)
{
    return g_ulpwrctrl_print_switch;
}

u32_t  pwrctrl_get_slice_time( void_t )
{
    return BSP_GetSliceValue();
}


s32_t __init pwrctrl_early_init(void_t)
{
  	g_stAcpuPwcSwitch =(ST_PWC_SWITCH_STRU *)IO_ADDRESS(SOC_PERI_SCTRL_SC_RESERVED8_ADDR(SOC_PERI_SCTRL_BASE_ADDR));

    LOG_IF(pwrctrl_dfs_init() != RET_OK);
    LOG_IF(pwrctrl_timer_addr_remap() != RET_OK);

    /*******拷贝低功耗代码至SARM********/
    pwrctrl_asm_mem_copy();

}

s32_t __init pwrctrl_common_initial ( void_t )
{
/*lint -e553*/
#if 1/*(FEATURE_POWER_DRV == FEATURE_ON)*/
/*lint +e553*/
    local_t u32_t startTm=0;
    u32_t tmpTm = 0;

    g_stAcpuPwcExcLog = (PWRCTRL_ACPU_EXC_LOG_STRU *)(EXCH_ACPU_CORE_PWC_ADDR_V);
    pwrctrl_write_reg32(IO_ADDRESS(EXCH_A_CORE_POWRCTRL_CONV_ADDR), EXCH_ACPU_CORE_PWC_ADDR);

#if 0
    g_stMcuLogExt = (PWC_MCU_EXC_LOG_STRU *)ioremap(pwrctrl_read_reg32(MEMORY_AXI_MCU_LOG_ADDR), 0x1000);
#endif
    /*保存SLICE TIMER 基地址*/
#if defined(CHIP_BB_HI6210) /*B020 Modify*/
#else
    pwrctrl_write_reg32(PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR, IO_ADDRESS(SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR(SOC_SC_ON_BASE_ADDR)));
#endif
    wake_lock_init(&g_ulTstwakelock,WAKE_LOCK_SUSPEND,"pwrctrl_tst");
    pwrctrl_sleep_initial();
    pwrctrl_sleep_mgr_sleep_init();

    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_ASLEEP))
    {
        wake_lock(&g_ulTstwakelock);
        PWC_TRACE(PWC_LOG_MAX, "MCU: pwc_common_initial,msleep not support!\r\n",0,0,0,0,0,0);
    }
    else
    {
        /*lint*/
    }

    /* 低功耗初始化完成*/
    PWC_TRACE(PWC_LOG_MAX, "ACPU: Enter pwrctrl initial routing! \n",0,0,0,0,0,0);

    register_reboot_notifier(&pm_reboot_nb);
    pwrctrl_write_reg32(IO_ADDRESS(MEMORY_AXI_SEC_CORE_BOOT_TEST_ADDR), 0);
    printk("sec core boot test addr:0x%x\n", MEMORY_AXI_SEC_CORE_BOOT_TEST_ADDR);	
#endif
    g_pwc_init_flag = PWRCTRL_INIT_FLAG;

    return RET_OK;
}

int g_acpu_pm_test_flag = 0;

void set_acpu_pm_test_flag(int flag)
{
	printk("%s old:%d new:%d\n", __FUNCTION__, g_acpu_pm_test_flag, flag);
	g_acpu_pm_test_flag = flag;
}

void acpu_pm_test()
{
	if(0 == g_acpu_pm_test_flag)
	{
		wake_lock(&g_ulTstwakelock);
       }		
}

void release_acpu_test_wakelock()
{
	printk("%s wake unlock\n", __FUNCTION__);
	wake_unlock(&g_ulTstwakelock);
}

s32_t pwrctrl_timer_delay (u32_t time)
{
    u32_t uDecValue = (u32_t)(time * PWRCTRL_SLICE_CLK) / PWRCTRL_SLICE_UNIT_CONV;
    u32_t uCurValue, uTargValue;

    /* 读Timer的当前计数值 */
    uCurValue = pwrctrl_get_slice_time();
    PWC_TRACE(PWC_LOG_DEBUG, "Current TIME Value1 = 0x%x\n", uCurValue, 0, 0, 0, 0, 0);

    /* 求Timer的递减目标值 */
    if (uDecValue <= uCurValue)
    {
        uTargValue = uCurValue - uDecValue;
    }
    else
    {
        uTargValue = PWRCTRL_SLICETIMER_XLOAD - (uDecValue - uCurValue);
    }

    /* 读取，并比较 */
    for (;;)
    {
        uCurValue = pwrctrl_get_slice_time();
        if (uCurValue <= uTargValue)
        {
            PWC_TRACE(PWC_LOG_DEBUG, "Curent,TIME Value2 = 0x%x\n", uCurValue, 0, 0, 0, 0, 0);
            break;
        }
    }
    return RET_OK;
}


s32_t pwrctrl_write_reg32( u32_t ulRegAddr, u32_t ulRegVal)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_write_reg32 Address: 0x%x not aligned.\r\n", (int)ulRegAddr,0,0,0,0,0);
        return RET_ERR;
    }

    *(volatile u32_t *)ulRegAddr = ulRegVal;
    return RET_OK;
}

u32_t pwrctrl_read_reg32 ( u32_t ulRegAddr )
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_read_reg32 Address: 0x%x not aligned.\r\n", (int)ulRegAddr,0,0,0,0,0);
        return 0;
    }

    return *(volatile u32_t *)ulRegAddr;
}


void pwrctrl_write_reg32_mask (u32_t ulRegAddr, u32_t ulRegVal, u32_t ulMask)
{
    u32_t reg_val = pwrctrl_read_reg32(ulRegAddr);

    pwrctrl_clr_bits((u32_t)&reg_val, ulMask);

    pwrctrl_set_bits((u32_t)&reg_val, ulRegVal & ulMask);

    pwrctrl_write_reg32(ulRegAddr, reg_val);
}


u32_t pwrctrl_read_reg32_mask(u32_t ulRegAddr, u32_t ulMask)
{
    return pwrctrl_read_reg32(ulRegAddr) & ulMask;
}


s32_t pwrctrl_set_bits (u32_t ulRegAddr, u32_t ulMask)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_set_bits Address: 0x%x not aligned.\r\n", (int)ulRegAddr,0,0,0,0,0);
        return RET_ERR;
    }

    pwrctrl_write_reg32(ulRegAddr, pwrctrl_read_reg32(ulRegAddr)|ulMask);
    return RET_OK;
}


s32_t pwrctrl_clr_bits (u32_t ulRegAddr, u32_t ulMask)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_clr_bits Address: 0x%x not aligned.\r\n", (int)ulRegAddr,0,0,0,0,0);
        return RET_ERR;
    }

    pwrctrl_write_reg32(ulRegAddr, pwrctrl_read_reg32(ulRegAddr)&(~ulMask));
    return RET_OK;
}


bool_t pwrctrl_is_bits_set(u32_t ulRegAddr, u32_t ulMask)
{
    LOG_IF (0 != (ulRegAddr & 0x03));

    return (pwrctrl_read_reg32(ulRegAddr) & ulMask) == ulMask;
}


bool_t pwrctrl_is_bits_clr(u32_t ulRegAddr, u32_t ulMask)
{
    LOG_IF (0 != (ulRegAddr & 0x03));

    return (pwrctrl_read_reg32(ulRegAddr) & ulMask) == 0x0;
}


u32_t pwrctrl_is_bit_set ( u32_t addr,  u32_t offset)
{
    if ((pwrctrl_read_reg32(addr) & (1<<offset)) == (1<<offset))
    {
        return PWRCTRL_TRUE ;
    }
    else
    {
        return PWRCTRL_FALSE;
    }
}



s32_t pwrctrl_is_func_on ( EM_PWC_SWITCH funId )
{
    if (pwrctrl_is_bit_set((u32_t)(g_stAcpuPwcSwitch),funId))
    {
        return RET_OK;
    }
    else
    {
        return RET_ERR;
    }
}


s32_t pwrctrl_mem_cpy ( void_t * dest, void_t * src, u32_t size )
{
    u32_t length = 0;
    u32_t * tDest = (u32_t *)(dest);
    u32_t * tSrc = (u32_t *)(src);

    for(; length<size; length++)
    {
        pwrctrl_write_reg32((u32_t)tDest,pwrctrl_read_reg32((u32_t)tSrc));
        tDest ++;
        tSrc ++;
    }

    return RET_OK;
}

s32_t pwrctrl_debug_info_show( void_t )
{
    PWC_TRACE(PWC_LOG_MAX, "################################ A核 core0 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠次数: 0x%x, 唤醒次数: 0x%x      \n", \
         g_stAcpuPwcExcLog->core0.SlpCnt, g_stAcpuPwcExcLog->core0.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠开始时间:0x%x, 睡眠时间:0x%x, 唤醒时间:0x%x , 唤醒结束时间:0x%x \n", \
         g_stAcpuPwcExcLog->core0.SlpMgrSTm, g_stAcpuPwcExcLog->core0.SlpSTm, \
         g_stAcpuPwcExcLog->core0.WkSTm, g_stAcpuPwcExcLog->core0.WkMgrSTm, 0, 0);

#if 0
    PWC_TRACE(PWC_LOG_MAX, "################################ A核 core1 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠次数: 0x%x, 唤醒次数: 0x%x      \n", \
         g_stAcpuPwcExcLog->core1.SlpCnt, g_stAcpuPwcExcLog->core1.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠开始时间:0x%x, 睡眠时间:0x%x, 唤醒时间:0x%x , 唤醒结束时间:0x%x \n", \
         g_stAcpuPwcExcLog->core1.SlpMgrSTm, g_stAcpuPwcExcLog->core1.SlpSTm, \
         g_stAcpuPwcExcLog->core1.WkSTm, g_stAcpuPwcExcLog->core1.WkMgrSTm, 0, 0);

    PWC_TRACE(PWC_LOG_MAX, "################################ A核 core2 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠次数: 0x%x, 唤醒次数: 0x%x      \n", \
         g_stAcpuPwcExcLog->core2.SlpCnt, g_stAcpuPwcExcLog->core2.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠开始时间:0x%x, 睡眠时间:0x%x, 唤醒时间:0x%x , 唤醒结束时间:0x%x \n", \
         g_stAcpuPwcExcLog->core2.SlpMgrSTm, g_stAcpuPwcExcLog->core2.SlpSTm, \
         g_stAcpuPwcExcLog->core2.WkSTm, g_stAcpuPwcExcLog->core2.WkMgrSTm, 0, 0);

    PWC_TRACE(PWC_LOG_MAX, "################################ A核 core3 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠次数: 0x%x, 唤醒次数: 0x%x      \n", \
         g_stAcpuPwcExcLog->core3.SlpCnt, g_stAcpuPwcExcLog->core3.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "睡眠开始时间:0x%x, 睡眠时间:0x%x, 唤醒时间:0x%x , 唤醒结束时间:0x%x \n", \
         g_stAcpuPwcExcLog->core3.SlpMgrSTm, g_stAcpuPwcExcLog->core3.SlpSTm, \
         g_stAcpuPwcExcLog->core3.WkSTm, g_stAcpuPwcExcLog->core3.WkMgrSTm, 0, 0);
#endif

    return RET_OK;
}


s32_t pwrctrl_mcu_debug_info_show( void_t )
{
    int i;
    PWC_TRACE(PWC_LOG_ERROR, "Current slice: 0x%x \r\n", pwrctrl_get_slice_time());

    for(i = 0; i < PERI_SLEEP_STATE_MAX; i++)
    {
    	PWC_TRACE(PWC_LOG_ERROR, "############# SYSTEM  ######## \r\n", 0, 0, 0, 0, 0, 0);
    	PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         	g_stMcuLogExt->peri[i].SleepCount, g_stMcuLogExt->peri[i].WakeCount, 0, 0, 0, 0);
    	PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         	g_stMcuLogExt->peri[i].SleepSliceTime, g_stMcuLogExt->peri[i].WakeSliceTime, 0, 0, 0, 0);
    	PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, \r\n", \
         	g_stMcuLogExt->peri[i].wakesrc0, g_stMcuLogExt->peri[i].wakesrc1, 0, 0, 0, 0);
    }

    PWC_TRACE(PWC_LOG_ERROR, "############# C core ########### \r\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_stMcuLogExt->ccpu.SleepCount, g_stMcuLogExt->ccpu.WakeCount, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_stMcuLogExt->ccpu.SleepSliceTime, g_stMcuLogExt->ccpu.WakeSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, wfi wait fail slice:0x%x, \r\n", \
         g_stMcuLogExt->ccpu.WfiFailCount, g_stMcuLogExt->ccpu.WfiFailSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, \r\n", \
         g_stMcuLogExt->ccpu.wakesrc0, g_stMcuLogExt->ccpu.wakesrc1, 0, 0, 0, 0);


    PWC_TRACE(PWC_LOG_ERROR, "############# A core ###### \r\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_stMcuLogExt->acpu0.SleepCount, g_stMcuLogExt->acpu0.WakeCount, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_stMcuLogExt->acpu0.SleepSliceTime, g_stMcuLogExt->acpu0.WakeSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, wfi wait fail slice:0x%x, \r\n", \
         g_stMcuLogExt->acpu0.WfiFailCount, g_stMcuLogExt->acpu0.WfiFailSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, \r\n", \
         g_stMcuLogExt->acpu0.wakesrc0, g_stMcuLogExt->acpu0.wakesrc1, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "IPC wake status: 0x%x, \r\n", \
         g_stMcuLogExt->acpu0.wakesrcIPC, 0, 0, 0, 0);


    PWC_TRACE(PWC_LOG_ERROR, "############# HIFI ######## \r\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_stMcuLogExt->hifi.SleepCount, g_stMcuLogExt->hifi.WakeCount, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_stMcuLogExt->hifi.SleepSliceTime, g_stMcuLogExt->hifi.WakeSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, wfi wait fail slice:0x%x, \r\n", \
         g_stMcuLogExt->hifi.WfiFailCount, g_stMcuLogExt->hifi.WfiFailSliceTime, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, \r\n", \
         g_stMcuLogExt->hifi.wakesrc0, g_stMcuLogExt->hifi.wakesrc1, 0, 0, 0, 0);

    return RET_OK;
}


s32_t pwrctrl_mem_show( u32_t addr )
{
    u32_t *addrV=0;

    addrV = (u32_t *)ioremap(addr, 0x1000);

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         addr, *(addrV++), *(addrV++), *(addrV++), *(addrV++), 0);

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x10), *(addrV++), *(addrV++), *(addrV++), *(addrV++), 0);

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x20), *(addrV++), *(addrV++), *(addrV++), *(addrV++), 0);

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x30), *(addrV++), *(addrV++), *(addrV++), *(addrV++), 0);

    iounmap(addrV);

    return RET_OK;
}




void_t pwrctrl_log_mem(u8_t* info, void_t* addr, u32_t size)
{
    u32_t idx;

    if(!info || !addr)
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_log_mem: null parameters.", 0, 0, 0, 0, 0, 0);

        return ;
    }

    PWC_TRACE(PWC_LOG_INFO, "%s, 0x%ux, %u", info, (u32_t)addr, size, 0, 0, 0);

    for(idx = 0; idx < size; idx = idx + 16)
    {
        PWC_TRACE(PWC_LOG_INFO, " 0x%.8X:  0x%.8X  0x%.8X  0x%.8X  0x%.8X ", (int)addr + idx,
            *(int*)((int)addr + idx), *(int*)((int)addr + idx + 0x4), *(int*)((int)addr + idx + 0x8), *(int*)((int)addr + idx + 0xC), 0);
    }

}




late_initcall(pwrctrl_common_initial);

arch_initcall(pwrctrl_early_init);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

