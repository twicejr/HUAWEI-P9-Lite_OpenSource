/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_sleep.c
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : 低功耗睡眠底层模块
  函数列表   :
              pwrctrl_check_irq_pending_status
              pwrctrl_deep_sleep
              pwrctrl_l2c_disable
              pwrctrl_l2c_enable
              pwrctrl_restore_ip_reg
              pwrctrl_sleep_initial
              pwrctrl_sleep_tele_vote_lock
              pwrctrl_sleep_tele_vote_unlock
              pwrctrl_sleep_tele_vote_wake_status
              pwrctrl_store_ip_reg

  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef WIN32
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <asm/memory.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <asm/mach/time.h>
#include <mach/irqs.h>
#include <mach/hipm.h>
#include <mach/early-debug.h>
#include <linux/android_pmem.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/arm_timer.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <mach/io.h>
#include <mach/gpio.h>
#include <linux/clk.h>
#endif
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>

#include <asm/cacheflush.h>
#include "pwrctrl_multi_memcfg.h"
#include "drv_ipcm.h"
extern void l2x0_flush_all(void);
extern void l2x0_clean_all(void);
extern void l2x0_inv_all(void);


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
u32_t g_aAcpuStoreReg[PWC_STORE_MEM_SIZE] = {0};

u32_t g_aAcpuHwVoteBaseAddr[] =
{
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCPU_VOTEEN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_PERI_VOTEEN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_ACPU_VOTEEN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTEEN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE1EN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2EN_ADDR(SOC_AO_SCTRL_BASE_ADDR)),
#else
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_PERI_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_ACPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE1EN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2EN0_ADDR(SOC_SC_ON_BASE_ADDR)),
#endif

};

ST_STORE_REG_ADDR_INFO g_aAcpuSocRegTable[] =
{
#if defined(CHIP_BB_HI6210)

#else
    /*SCU*/
    {(ACPU_SCU_BASE_VA),             (2)},
#endif

    /* GIC */
    {(ACPU_GIC_ICCEOIR_VA),          (1)},
    {(ACPU_GIC_ICABPR_VA),           (1)},
    {(ACPU_GIC_ICDISR_VA),           (5)},
    {(ACPU_GIC_ICDISER_VA),          (5)},
    {(ACPU_GIC_ICDISPR_VA),          (5)},
    {(ACPU_GIC_ICDIPR_VA),           (40)},
    {(ACPU_GIC_ICDSGIR_VA),          (1)},
    {(ACPU_GIC_ICDIPTR_VA),          (64*2)},
    {(ACPU_GIC_ICCICR_VA),           (3)},
    {(ACPU_GIC_ICDDCR_VA),           (1)},

#if defined(CHIP_BB_HI6210)

#else
    /* L2 cache */
    {(ACPU_L2CC_AUX_CTRL_VA),        (1)},
    {(ACPU_L2CC_DLTNCY_CTRL_VA),     (1)},
    {(ACPU_L2CC_PREFETCH_CTRL_VA),   (1)},
    {(ACPU_L2CC_PWR_CTRL_VA),        (1)},
#endif
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : pwrctrl_sleep_initial
 功能描述  : 低功耗底层初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_initial ( void_t )
{

    pwrctrl_arm_init();

    /*修改掉电后重启后pc指向的位置:*/
    pwrctrl_write_reg32(IO_ADDRESS(PWRCTRL_ACPU_ASM_SPACE_ADDR), PWRCTRL_JMP_INSTRUCTION);


    /*remap to sram*/
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
   pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(SOC_AO_SCTRL_BASE_ADDR)), \
                    BIT(SOC_AO_SCTRL_SC_SYS_CTRL1_remap_sram_aarm_START) |                                      \
                     BIT(SOC_AO_SCTRL_SC_SYS_CTRL1_remap_sram_aarm_msk_START));
#else
    pwrctrl_set_bits(IO_ADDRESS(SOC_AO_SCTRL_SC_SECURITY_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)), \
                     BIT(SOC_AO_SCTRL_SC_SECURITY_CTRL2_remap_sram_aarm_START));
#endif/*默认使能，删除配置 w00176398 2013-11-26*/
#if 0/*defined(CHIP_BB_HI6210)*//*A7 feature, support hardware invalid cache*/
    pwrctrl_set_bits(IO_ADDRESS(SOC_ACPU_SCTRL_ACPU_SC_CPU0_CTRL_ADDR(SOC_ACPU_SC_BASE_ADDR)),\
                     BIT(SOC_ACPU_SCTRL_ACPU_SC_CPU0_CTRL_l1rstdisable0_START));
    pwrctrl_set_bits(IO_ADDRESS(SOC_ACPU_SCTRL_ACPU_SC_CPU1_CTRL_ADDR(SOC_ACPU_SC_BASE_ADDR)),\
                     BIT(SOC_ACPU_SCTRL_ACPU_SC_CPU1_CTRL_l1rstdisable1_START));
    pwrctrl_set_bits(IO_ADDRESS(SOC_ACPU_SCTRL_ACPU_SC_CPU2_CTRL_ADDR(SOC_ACPU_SC_BASE_ADDR)),\
                     BIT(SOC_ACPU_SCTRL_ACPU_SC_CPU2_CTRL_l1rstdisable2_START));
    pwrctrl_set_bits(IO_ADDRESS(SOC_ACPU_SCTRL_ACPU_SC_CPU3_CTRL_ADDR(SOC_ACPU_SC_BASE_ADDR)),\
                     BIT(SOC_ACPU_SCTRL_ACPU_SC_CPU3_CTRL_l1rstdisable3_START));
    pwrctrl_set_bits(IO_ADDRESS(SOC_ACPU_SCTRL_ACPU_SC_CPU_CTRL_ADDR(SOC_ACPU_SC_BASE_ADDR)),\
                     BIT(SOC_ACPU_SCTRL_ACPU_SC_CPU_CTRL_l2rstdisable_START));
#endif
    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_store_ip_reg
 功能描述  : 备份soc下电区ip的寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_store_ip_reg ( u32_t * addr )
{
    u32_t * ulbakAddr;
    u32_t i;

    ulbakAddr = addr;
    for (i = 0; i < (sizeof(g_aAcpuSocRegTable) / sizeof(ST_STORE_REG_ADDR_INFO)); i++)
    {
        pwrctrl_mem_cpy((void *)ulbakAddr, (void *)g_aAcpuSocRegTable[i].ulStartAddr, g_aAcpuSocRegTable[i].ulLength);
        ulbakAddr += g_aAcpuSocRegTable[i].ulLength;
    }

    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_restore_ip_reg
 功能描述  : 恢复soc下电区ip的寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_restore_ip_reg( u32_t * addr)
{
    u32_t * ulbakAddr;
    u32_t i;

    ulbakAddr = addr;
    for (i = 0; i < (sizeof(g_aAcpuSocRegTable) / sizeof(ST_STORE_REG_ADDR_INFO)); i++)
    {
        pwrctrl_mem_cpy((void *)g_aAcpuSocRegTable[i].ulStartAddr, (void *)ulbakAddr, g_aAcpuSocRegTable[i].ulLength);
        ulbakAddr += g_aAcpuSocRegTable[i].ulLength;
    }

    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_l2c_disable
 功能描述  : l2cach disable
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数(需要修改arm/mm下的cache-l2x0.c文件)

*****************************************************************************/
s32_t pwrctrl_l2c_disable( void_t )
{
#ifdef CONFIG_CACHE_L2X0
#ifdef CHIP_BB_HI6210
    /*no need*/
#else
    /* flush cache all */
    /*l2x0_flush_all();*/
    outer_flush_all();

    /* disable l2x0 cache */
    pwrctrl_write_reg32(ACPU_L2CC_CTRL_VA,PWRCTRL_SWITCH_OFF);

    /* barrier */
    dmb();
#endif
#endif
    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_l2c_enable
 功能描述  : l2cach enable
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数(需要修改arm/mm下的cache-l2x0.c文件)

*****************************************************************************/
s32_t pwrctrl_l2c_enable( void_t )
{
#ifdef CONFIG_CACHE_L2X0

#ifdef CHIP_BB_HI6210
    /*no need*/
#else
	/* invalidate l2x0 cache */
   /* l2x0_inv_all();*/
   outer_inv_all();

    /* enable l2x0 cache */
    pwrctrl_write_reg32(ACPU_L2CC_CTRL_VA,PWRCTRL_SWITCH_ON);

    mb();
 #endif
#endif
    return RET_OK;
}


/*****************************************************************************
 函 数 名  : PWRCTRL_CheckIrqPendingStatus
 功能描述  : 检查中断状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TRUE:无中断；FALSE:有中断

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_check_irq_pending_status ( void_t )
{
    u32_t i, j;
    u32_t pendings32_tNum = ACPU_GIC_MAX_NUM;
    u32_t gicIcdIsprRegValue = 0;
    u32_t key = 0;

    local_irq_save(key);
    for (i = 0; i < ACPU_GIC_ICDABR_NUM; i++)
    {
        gicIcdIsprRegValue = PWRCTRL_GET_GIC_STATUS(i);
        if (0 == gicIcdIsprRegValue)
        {
            continue;
        }
        else
        {
            for (j = 0; j < sizeof(u32_t); j++)
            {
                if ((gicIcdIsprRegValue & (1 << j)))
                {
                    pendings32_tNum = ((i * sizeof(u32_t)) + j);
                    PWC_TRACE(PWC_LOG_DEBUG, "GIC Pending %d  ... \n", pendings32_tNum, 0, 0, 0, 0, 0);
                }
            }
        }
    }

    local_irq_restore(key);

    /*忽略Com ARM内置DEBUG模块的通道发送请求中断*/
    if (((ACPU_COMMTX_CORE0 <= pendings32_tNum) && (ACPU_COMMTX_CORE3 >= pendings32_tNum)) \
     || (ACPU_GIC_MAX_NUM == pendings32_tNum))
    {
        return PWRCTRL_TRUE;
    }
    else
    {
        PWC_TRACE(PWC_LOG_DEBUG, "Can't sleep: GIC Pending %d  ... \n", pendings32_tNum, 0, 0, 0, 0, 0);
        return PWRCTRL_FALSE;
    }
}


/*****************************************************************************
 函 数 名  : pwrctrl_deep_sleep
 功能描述  : ARM 进入休眠唤醒
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t  pwrctrl_deep_sleep( void_t )
{
    u32_t key = 0;

    /*SOC下电区IP寄存器保存地址*/
    u32_t * pulSocRegBakAddr = (u32_t *)g_aAcpuStoreReg;

    if (RET_OK != pwrctrl_is_func_on(PWC_SWITCH_ASLEEP))
    {
        return RET_ERR;
    }

    BSP_IPC_SpinLock(IPC_SEM_SMP_CPU0);
    g_stAcpuPwcExcLog->core0.SlpCnt ++;
    g_stAcpuPwcExcLog->core0.SlpMgrSTm = pwrctrl_get_slice_time();

    local_irq_save(key);

    /*读中断pending寄存器，有中断就退出睡眠*/
    if (PWRCTRL_TRUE == pwrctrl_check_irq_pending_status())
    {

        pwrctrl_l2c_disable();
#ifdef CHIP_BB_HI6210

#else
        __cpuc_flush_kern_all();
#endif
        /*__cpuc_flush_user_all();*/
        /*__cpuc_flush_icache_all();*/

        pwrctrl_store_ip_reg(pulSocRegBakAddr);

        /*PD ENTRY*/
        pwrctrl_asm_deep_sleep_entry();

        pwrctrl_restore_ip_reg(pulSocRegBakAddr);
        pulSocRegBakAddr = NULL;

        pwrctrl_l2c_enable();

    }
    else
    {
        /*just for pclint*/
    }

    /* unlock  s32_terrupt   */
    local_irq_restore(key);

    g_stAcpuPwcExcLog->core0.WkCnt ++;
    g_stAcpuPwcExcLog->core0.WkMgrSTm = pwrctrl_get_slice_time();
    BSP_IPC_SpinUnLock(IPC_SEM_SMP_CPU0);
    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_sleep_tele_vote_lock
 功能描述  : 远程投票禁止睡眠接口
 输入参数  : teleModeId         远程模块ID
             enClientId         投票模块ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_tele_vote_lock(u32_t teleModeId, u32_t enClientId)
{
    ST_VOTE_HW_INFO * pStVoteInfo = NULL ;

    pStVoteInfo = (ST_VOTE_HW_INFO *)g_aAcpuHwVoteBaseAddr[teleModeId];
    pwrctrl_set_bits(&(pStVoteInfo->voteEn), BIT(enClientId));

    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_sleep_tele_vote_unlock
 功能描述  : 远程投票允许睡眠接口
 输入参数  : teleModeId         远程模块ID
             enClientId         投票模块ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_tele_vote_unlock( u32_t teleModeId, u32_t enClientId )
{
    ST_VOTE_HW_INFO * pStVoteInfo = NULL ;

    pStVoteInfo = (ST_VOTE_HW_INFO *)g_aAcpuHwVoteBaseAddr[teleModeId];
    pwrctrl_set_bits(&(pStVoteInfo->voteDis), BIT(enClientId));

    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_sleep_tele_vote_wake_status
 功能描述  : 远程投票的唤醒投票状态检查
 输入参数  : teleModeId         远程模块ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月10日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_tele_vote_wake_status(u32_t teleModeId)
{
    ST_VOTE_HW_INFO * pStVoteInfo = NULL ;

    pStVoteInfo = (ST_VOTE_HW_INFO *)g_aAcpuHwVoteBaseAddr[teleModeId];
    return pwrctrl_read_reg32(&(pStVoteInfo->voteWakeStat));

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

