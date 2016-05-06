/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dsp.c
*
*   作    者 :  z00227143
*
*   描    述 :  本文件主要完成DSP镜像的加载及低功耗处理
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
/*lint --e{537} */
#include <product_config.h>
#include "securec.h"
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_wait.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>

#include <hi_base.h>
#include <hi_pwrctrl.h>
#include <hi_dsp.h>

#include <bsp_shared_ddr.h>

#include <bsp_om.h>
#include <bsp_edma.h>
#include <bsp_dpm.h>
#include <bsp_dsp.h>
#include <bsp_version.h>
#include <bsp_sysctrl.h>
#include <bsp_hardtimer.h>
#include <bsp_memrepair.h>
#include <bsp_pm_om.h>
#include <bsp_hw_spinlock.h>
#include <bsp_rsracc.h>
#include <hi_pwrctrl_interface.h>
#include <mdrv_pm.h>

#include <of.h>

#include "dsp_balong.h"
#include <socp_balong.h>
#include <bsp_reset.h>

#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"

/* #define BSP_BBE_STATE_CHECK */
#define BSP_DSP_WITH_EDMA

struct dsp_state
{
    spinlock_t spin_lock;
    u32 store_edma_channel_id_lte;
    u32 store_edma_channel_id_tds;
    u32 restore_edma_channel_id_lte;
    u32 restore_edma_channel_id_tds;
    u32 dsp_power_on_count;
    u32 dsp_unreset_count;
    u32 dsp_clock_enable_count;
    u32 dsp_suspend_count;
    u32 dsp_resume_count;
    u32 dsp_sem_up_count;
    u32 dsp_sem_down_count;
    u32 dsp_run_count;
    u32 dsp_stop_count;
    u32 dsp_restore_count;      /*dsp加载次数*/
    u32 dsp_restore_succ_count; /*dsp加载成功次数*/
    u32 dsp_store_count;        /*dsp备份次数*/
    u32 dsp_store_succ_count;   /*dsp备份成功次数*/
    u32 is_dsp_load_muti: 1;    /*1:协议栈调用了bsp_bbe_load_muti接口 0:协议栈没有调用bsp_bbe_load_muti接口*/
    u32 is_dsp_power_on:1;      /* 1 for power on */
    u32 is_dsp_clock_enable:1;  /* 1 for clock enable */
    u32 is_dsp_unreset: 1;      /* 1 for unreset */
    u32 is_bbe_power_on:1;      /* 1 for power on */
    u32 is_bbe_clock_enable:1;  /* 1 for clock enable */
    u32 is_bbe_unreset: 1;      /* 1 for unreset */
    u32 is_image_loaded:1;
    u32 is_image_dirty: 1;  /* is the image in DTCM different form DDR */
    u32 is_dsp_running: 1;
    u32 is_dsp_deep_sleep: 1;
    u32 is_image_need_store: 1;
    u32 is_image_has_store: 1;
    u32 is_msp_restoring:   1;
    u32 is_msp_storing:     1;
    u32 reserved: 17;
};

struct dsp_info{
    struct dsp_ctrl dsp_ctrl;
    struct dsp_sysctrl dsp_sysctrl[DSP_DTS_REG_BUTT];
    struct dsp_pwc_ctrl dsp_pwc_ctrl;
    struct dsp_state dsp_state;
    struct dsp_pm_om_qos_log dsp_timedump;
    struct dsp_pm_om_qos_log *dsp_timedump_addr;
};

struct dsp_info g_dsp_info;

struct dsp_drx_debug{
    u32 drx_bbe16_pd;
    u32 drx_bbe16_pll;
};

struct dsp_drx_debug g_dsp_drx = {0};

void bsp_dsp_state_init(void)
{
    g_dsp_info.dsp_state.store_edma_channel_id_lte    = 0;
    g_dsp_info.dsp_state.store_edma_channel_id_tds    = 0;
    g_dsp_info.dsp_state.restore_edma_channel_id_lte    = 0;
    g_dsp_info.dsp_state.restore_edma_channel_id_tds    = 0;
    g_dsp_info.dsp_state.dsp_power_on_count     = 1;
    g_dsp_info.dsp_state.dsp_unreset_count  = 1;
    g_dsp_info.dsp_state.dsp_clock_enable_count = 1;
    g_dsp_info.dsp_state.dsp_suspend_count  = 0;
    g_dsp_info.dsp_state.dsp_resume_count   = 0;
    g_dsp_info.dsp_state.dsp_sem_up_count   = 0;
    g_dsp_info.dsp_state.dsp_sem_down_count = 0;
    g_dsp_info.dsp_state.dsp_run_count      = 0;
    g_dsp_info.dsp_state.dsp_stop_count     = 0;
    g_dsp_info.dsp_state.dsp_restore_count  = 0;
    g_dsp_info.dsp_state.dsp_restore_succ_count  = 0;
    g_dsp_info.dsp_state.dsp_store_count    = 0;
    g_dsp_info.dsp_state.dsp_store_succ_count  = 0;
    g_dsp_info.dsp_state.is_dsp_load_muti   = 0;
    g_dsp_info.dsp_state.is_dsp_power_on    = 0;
    g_dsp_info.dsp_state.is_dsp_clock_enable= 0;
    g_dsp_info.dsp_state.is_dsp_unreset     = 0;
    g_dsp_info.dsp_state.is_bbe_power_on    = 0;
    g_dsp_info.dsp_state.is_bbe_clock_enable= 0;
    g_dsp_info.dsp_state.is_bbe_unreset     = 0;
    g_dsp_info.dsp_state.is_image_loaded    = 0;
    g_dsp_info.dsp_state.is_image_dirty     = 0;
    g_dsp_info.dsp_state.is_dsp_running     = 0;
    g_dsp_info.dsp_state.is_dsp_deep_sleep  = 1;
    g_dsp_info.dsp_state.is_image_need_store= 0;
    g_dsp_info.dsp_state.is_image_has_store = 0;
    g_dsp_info.dsp_state.is_msp_restoring   = 0;
    g_dsp_info.dsp_state.is_msp_storing     = 0;
    g_dsp_info.dsp_state.reserved           = 0;
}

static inline void hi_dsp_get_reg(unsigned int *value,unsigned int base,unsigned int offset,unsigned int lowbit,unsigned int highbit)
 {
     unsigned int mask = 0;
     unsigned int temp = 0;
     unsigned int reg    = base + offset;

     temp   = readl(reg);
     mask   = ((1U << (highbit - lowbit + 1)) -1) << lowbit;
     *value = temp & mask;
     *value = (*value) >> lowbit;
 }

 static inline void hi_dsp_set_reg(unsigned int value,unsigned int base,unsigned int offset,unsigned int lowbit,unsigned highbit)
 {
     unsigned int reg    = base + offset;
     unsigned int temp   = 0;
     unsigned int mask   = 0;

     temp   = readl(reg);
     mask   = ((1U << (highbit - lowbit + 1)) -1) << lowbit;
     value  = (temp & (~mask)) | ((value <<lowbit) & mask);
     writel(value  ,reg);
 }

int bsp_bbe_load_muti(void)
{
    /* bbe从深睡中恢复 */
    int ret = 0;
    u32 tmp_time = 0;

    g_dsp_info.dsp_state.is_dsp_load_muti = 1;


    if(!g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {

        ret  = bsp_bbe_power_on();
        ret |= bsp_dsp_clock_enable();
        ret |= bsp_dsp_unreset();

    }

    ret |= bsp_bbe_clock_enable();
    ret |= bsp_bbe_unreset();

    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[TLDSP]TLDSP fail to setup bbe16\r\n");
        return -1;
    }

    /* 开机时向tcm中拷数据之前做打点 */
    tmp_time = bsp_get_slice_value();
    writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->load_start);

    ret = bsp_bbe_restore();

    ret |= bsp_bbe_wait_restore_ok();

    /* 开机时向tcm中拷数据之后做打点 */
    tmp_time = bsp_get_slice_value();
    writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->load_end);

    g_dsp_info.dsp_state.is_dsp_deep_sleep = 0;
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[TLDSP]TLDSP Load Success!\r\n");
    return ret;
}

int bsp_bbe_is_muti_loaded(void)
{
    int ret = 0;

    ret = bsp_bbe_is_tcm_accessible();
    ret &= (int)(!g_dsp_info.dsp_state.is_dsp_deep_sleep);
    return ret;
}
int bsp_bbe_run(void)
{
    /* 让bbe开始工作 */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].offset, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].start_bit, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].end_bit);
    }

    g_dsp_info.dsp_state.is_dsp_running = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_is_run(void)
{
    int ret = 0;

    ret = (int)g_dsp_info.dsp_state.is_dsp_running;
    return ret;
}
int bsp_bbe_stop(void)
{
    /* 让bbe停止工作 */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);


    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].offset, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].start_bit, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].end_bit);
    }

    g_dsp_info.dsp_state.is_dsp_running = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_store(void)
{
    int ret = 0;
    u32 size_align = 0;
    /* save public image's data */
#ifdef BSP_DSP_WITH_EDMA
    if((g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size & (0x1fff)) == 0)
    {
        size_align = SZ_8K;
    }
    else
    {
        size_align = SZ_1K;
    }
    g_dsp_info.dsp_state.store_edma_channel_id_lte =
        (u32)bsp_edma_channel_init(EDMA_PWC_LDSP_TCM, NULL, 0, 0);

    ret |= bsp_edma_channel_set_config(g_dsp_info.dsp_state.store_edma_channel_id_lte, EDMA_M2M,
        EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);

    ret |= bsp_edma_channel_2vec_start(g_dsp_info.dsp_state.store_edma_channel_id_lte,
        (u32)g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
        (u32)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
        g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size, size_align);
#else
    memcpy_s((void*)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
            g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size,
           g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
           g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size);
#endif
    g_dsp_info.dsp_state.dsp_store_count++;
    return ret;
}

int bsp_bbe_store_dtcm(void)
{
    int ret = 0;
    u32 size_align = 0;
    /* save dtcm */
#ifdef BSP_DSP_WITH_EDMA
    u32 len = g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE;
    if((len&0x1fff) == 0)
    {
        size_align = SZ_8K;
    }
    else if((len&0xfff) == 0)
    {
        size_align = SZ_4K;
    }
    else
    {
        size_align = SZ_1K;
    }
    g_dsp_info.dsp_state.store_edma_channel_id_lte =
        (u32)bsp_edma_channel_init(EDMA_PWC_LDSP_TCM, NULL, 0, 0);

    ret |= bsp_edma_channel_set_config(g_dsp_info.dsp_state.store_edma_channel_id_lte, EDMA_M2M,
        EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);

    ret |= bsp_edma_channel_2vec_start(g_dsp_info.dsp_state.store_edma_channel_id_lte,
        (u32)g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
        (u32)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
        g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE, size_align);
#else
    memcpy_s((void*)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
            g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE,
           (void *)g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
           g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE);
#endif
    return ret;
}

int bsp_bbe_store_itcm(void)
{
    int ret = 0;
    u32 size_align = 0;
    /* save public itcm */
#ifdef BSP_DSP_WITH_EDMA
    u32 len = g_dsp_info.dsp_ctrl.lphy_pub_itcm_size + LPHY_PRV_ITCM_SIZE;
    if((len & 0x1fff) == 0)
    {
        size_align = SZ_8K;
    }
    else if((len & 0xfff) == 0)
    {
        size_align = SZ_4K;
    }
    else
    {
        size_align = SZ_1K;
    }
    g_dsp_info.dsp_state.store_edma_channel_id_tds =
        (u32)bsp_edma_channel_init(EDMA_PWC_TDSP_TCM, NULL, 0, 0);

    ret |= bsp_edma_channel_set_config(g_dsp_info.dsp_state.store_edma_channel_id_tds, EDMA_M2M,
        EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);

    ret |= bsp_edma_channel_2vec_start(g_dsp_info.dsp_state.store_edma_channel_id_tds,
        (u32)g_dsp_info.dsp_ctrl.tcm_itcm_base_addr,
        (u32)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr + g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE,
        g_dsp_info.dsp_ctrl.lphy_pub_itcm_size + LPHY_PRV_ITCM_SIZE, size_align);
#else
    memcpy_s((void*)(g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr + g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size + LPHY_PRV_DTCM_SIZE),
            g_dsp_info.dsp_ctrl.lphy_pub_itcm_size + LPHY_PRV_ITCM_SIZE,
           g_dsp_info.dsp_ctrl.tcm_itcm_base_addr,
           g_dsp_info.dsp_ctrl.lphy_pub_itcm_size + LPHY_PRV_ITCM_SIZE);
#endif
    return ret;
}

int bsp_bbe_wait_store_ok(void)
{
    int ret = 0;
#ifdef BSP_DSP_WITH_EDMA
        while(!bsp_edma_channel_is_idle(g_dsp_info.dsp_state.store_edma_channel_id_lte)) ;

        ret = bsp_edma_channel_free(g_dsp_info.dsp_state.store_edma_channel_id_lte);
#endif
    g_dsp_info.dsp_state.dsp_store_succ_count++;
    return ret;
}

int bsp_bbe_wait_store_itcm_ok(void)
{
    int ret = 0;
#ifdef BSP_DSP_WITH_EDMA
        while(!bsp_edma_channel_is_idle(g_dsp_info.dsp_state.store_edma_channel_id_tds)) ;

        ret = bsp_edma_channel_free(g_dsp_info.dsp_state.store_edma_channel_id_tds);
#endif

    return ret;
}

int bsp_bbe_restore(void)
{
    int ret = 0;
    u32 size_align = 0;
#ifdef BSP_DSP_WITH_EDMA
        if((g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size & (0x1fff)) == 0)
        {
            size_align = SZ_8K;
        }
        else
        {
            size_align = SZ_1K;
        }
        g_dsp_info.dsp_state.restore_edma_channel_id_lte =
            (u32)bsp_edma_channel_init(EDMA_PWC_LDSP_TCM, NULL, 0, 0);

        ret |= bsp_edma_channel_set_config(g_dsp_info.dsp_state.restore_edma_channel_id_lte, EDMA_M2M,
            EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);

        ret |= bsp_edma_channel_2vec_start(g_dsp_info.dsp_state.restore_edma_channel_id_lte,
            (u32)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
            (u32)g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
            g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size, size_align);

        if((g_dsp_info.dsp_ctrl.lphy_pub_itcm_size & (0x1fff)) == 0)
        {
            size_align = SZ_8K;
        }
        else
        {
            size_align = SZ_1K;
        }

        g_dsp_info.dsp_state.restore_edma_channel_id_tds =
            (u32)bsp_edma_channel_init(EDMA_PWC_TDSP_TCM, NULL, 0, 0);

        ret |= bsp_edma_channel_set_config(g_dsp_info.dsp_state.restore_edma_channel_id_tds, EDMA_M2M,
            EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);

        ret |= bsp_edma_channel_2vec_start(g_dsp_info.dsp_state.restore_edma_channel_id_tds,
            (u32)g_dsp_info.dsp_ctrl.bbe_ddr_pub_itcm_addr,
            (u32)g_dsp_info.dsp_ctrl.tcm_itcm_base_addr,
            g_dsp_info.dsp_ctrl.lphy_pub_itcm_size, size_align);
#else
        memcpy_s((void*)g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr,
                g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size,
               (void*)g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr,
               g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size);

        memcpy_s((void*)g_dsp_info.dsp_ctrl.tcm_itcm_base_addr,
                g_dsp_info.dsp_ctrl.lphy_pub_itcm_size,
               (void*)g_dsp_info.dsp_ctrl.bbe_ddr_pub_itcm_addr,
               g_dsp_info.dsp_ctrl.lphy_pub_itcm_size);
#endif
    g_dsp_info.dsp_state.dsp_restore_count++;
    return ret;
}

int bsp_bbe_wait_restore_ok(void)
{
    int ret = 0;

#ifdef BSP_DSP_WITH_EDMA
        while(!bsp_edma_channel_is_idle(g_dsp_info.dsp_state.restore_edma_channel_id_lte)) ;
        while(!bsp_edma_channel_is_idle(g_dsp_info.dsp_state.restore_edma_channel_id_tds)) ;

        ret = bsp_edma_channel_free(g_dsp_info.dsp_state.restore_edma_channel_id_lte);
        ret |= bsp_edma_channel_free(g_dsp_info.dsp_state.restore_edma_channel_id_tds);
        if (ret)
        {
            ret = -1;
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to free edma channel\r\n");
        }
#endif
    g_dsp_info.dsp_state.dsp_restore_succ_count++;
    return ret;
}

int bsp_bbe_clock_enable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* enable clock */

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE_CORE_CLK_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE_CORE_CLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE_CORE_CLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE_CORE_CLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE_CORE_CLK_EN].end_bit);
    }

    g_dsp_info.dsp_state.is_bbe_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_clock_disable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* disable clock */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[DSP0_CORE_CLK_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[DSP0_CORE_CLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[DSP0_CORE_CLK_DIS].offset, g_dsp_info.dsp_sysctrl[DSP0_CORE_CLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[DSP0_CORE_CLK_DIS].end_bit);
    }

    g_dsp_info.dsp_state.is_bbe_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_unreset(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* unreset BBE16 */

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_DIS].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_DIS].end_bit);
    }

    g_dsp_info.dsp_state.is_bbe_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_reset(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* reset BBE16 */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].end_bit);
    }

    g_dsp_info.dsp_state.is_bbe_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_is_unreset(void)
{
    int ret = 0;

    ret = (int)g_dsp_info.dsp_state.is_bbe_unreset;
    return ret;
}
/*lint -save -e539*/
int bsp_bbe_power_on(void)
{
    unsigned long irq_flags;
    int ret = 0;
    unsigned int  tmp;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_EN].end_bit);
    }

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].base_addr))
    {
        hi_dsp_get_reg(&tmp, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].base_addr, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].offset, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].start_bit, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].end_bit);
        while(!tmp)
        {
            hi_dsp_get_reg(&tmp, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].base_addr, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].offset, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].start_bit, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_RDY_STAT].end_bit);
        }
    }

    udelay(30);
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_DIS].offset, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_DIS].end_bit);
    }

    /*memrepair*/
    ret = bsp_modem_memrepair(MODEM_MEMREPAIR_DSP);
    if(BSP_OK!=ret){
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "memrepair fail !\n");
    }

    g_dsp_info.dsp_state.is_dsp_power_on = 1;
    g_dsp_info.dsp_state.is_bbe_power_on = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return ret;
}
/*lint -restore*/
int bsp_bbe_power_off(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_ISO_CTRL_EN].end_bit);
    }
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_DIS].offset, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE16_MTCMOS_CTRL_DIS].end_bit);
    }
    g_dsp_info.dsp_state.is_dsp_power_on = 0;
    g_dsp_info.dsp_state.is_bbe_power_on = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_is_clock_enable(void)
{
    return (int)g_dsp_info.dsp_state.is_bbe_clock_enable;
}

int bsp_bbe_is_power_on(void)
{
    return (int)g_dsp_info.dsp_state.is_bbe_power_on;
}

int bsp_bbe_power_status(void)
{
    int ret = PWRCTRL_COMM_ON;
    if(1 == g_dsp_drx.drx_bbe16_pd)
    {
        return PWRCTRL_COMM_ON;
    }
    else
    {
        ret = bsp_bbe_is_power_on();
        if(0 == ret)
            return PWRCTRL_COMM_OFF;
        else
            return PWRCTRL_COMM_ON;
    }
}

int bsp_bbe_power_up(void)
{
    int ret = 0;
    u32 tmp_time = 0;
    if(!g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
       ret =  bsp_bbe_power_on();
       ret |= bsp_dsp_clock_enable();
       ret |= bsp_dsp_unreset();

        /* 将dsp上电时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->poweron);
    }
    return ret;
}

int bsp_bbe_power_down(void)
{
    int ret = 0;
    u32 tmp_time = 0;
    if(1 == g_dsp_drx.drx_bbe16_pd)
    {
        return ret;
    }
    else
    {
        if(!g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
        {
           ret  = bsp_dsp_reset();
           ret |= bsp_dsp_clock_disable();
           ret |= bsp_bbe_power_off();

            /* 将dsp下电时间打点*/
            tmp_time = bsp_get_slice_value();
            writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->poweroff);
        }
        return ret;
    }
}

int bsp_bbe_is_tcm_accessible(void)
{
    int ret = 0;

    ret = (int)(g_dsp_info.dsp_state.is_dsp_power_on &&
                g_dsp_info.dsp_state.is_dsp_clock_enable &&
                g_dsp_info.dsp_state.is_dsp_unreset &&
                g_dsp_info.dsp_state.is_bbe_power_on &&
                g_dsp_info.dsp_state.is_bbe_clock_enable &&
                g_dsp_info.dsp_state.is_bbe_unreset);

    return ret;
}

int bsp_bbe_waiti_enable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    //配置V7R5 DSP WAITI模式分频比
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_WAITI_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_WAITI_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_WAITI_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_WAITI_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_WAITI_DIV].end_bit);
        udelay(1);
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_WAITI_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_WAITI_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_WAITI_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_WAITI_EN].end_bit);
    }

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clock_enable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* enable clock */

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_EN].end_bit);
    }
    //sc_dsp_clock_enable(1);

    g_dsp_info.dsp_state.is_dsp_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clock_disable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* disable clock */

    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_DIS].offset, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE16_PD_CLK_DIS].end_bit);
    }

    g_dsp_info.dsp_state.is_dsp_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_unreset(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* unreset BBE16 */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_DIS].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_DIS].offset, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_DIS].end_bit);
    }

    g_dsp_info.dsp_state.is_dsp_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_reset(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    /* reset BBE16 */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].base_addr))
    {
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].end_bit);
    }

    g_dsp_info.dsp_state.is_dsp_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_status(void)
{
    unsigned int data = 0;
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PLL_EN].base_addr))
    {
        //K3、V7R5
        hi_dsp_get_reg(&data, g_dsp_info.dsp_sysctrl[PLL_LOCK].base_addr, g_dsp_info.dsp_sysctrl[PLL_LOCK].offset, g_dsp_info.dsp_sysctrl[PLL_LOCK].start_bit, g_dsp_info.dsp_sysctrl[PLL_LOCK].end_bit);
    }
    return (int)data;
}

int bsp_dsp_pll_enable(void)
{
    unsigned long irq_flags;
    unsigned int data;
    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);
    /* open dsp pll */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PLL_EN].base_addr))
    {
        //K3、V7R5
        /* V722 dsp/hifi/mmc共用pll，硬件实现了投票，当需要开启pll时，就需要对pd和clk_gt投票 */
        if(CHIP_K3V5 == bsp_get_version_info()->chip_type)
        {
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
        else if((CHIP_V750 == bsp_get_version_info()->chip_type) || (CHIP_V722 == bsp_get_version_info()->chip_type))
        {
            hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
        else if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
        {
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_BP].base_addr, g_dsp_info.dsp_sysctrl[PLL_BP].offset, g_dsp_info.dsp_sysctrl[PLL_BP].start_bit, g_dsp_info.dsp_sysctrl[PLL_BP].end_bit);
        if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PLL_POSTDIVPD].base_addr))
        {
            hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_POSTDIVPD].base_addr, g_dsp_info.dsp_sysctrl[PLL_POSTDIVPD].offset, g_dsp_info.dsp_sysctrl[PLL_POSTDIVPD].start_bit, g_dsp_info.dsp_sysctrl[PLL_POSTDIVPD].end_bit);
        }
        hi_dsp_get_reg(&data, g_dsp_info.dsp_sysctrl[PLL_LOCK].base_addr, g_dsp_info.dsp_sysctrl[PLL_LOCK].offset, g_dsp_info.dsp_sysctrl[PLL_LOCK].start_bit, g_dsp_info.dsp_sysctrl[PLL_LOCK].end_bit);
        while(!data)
        {
            hi_dsp_get_reg(&data, g_dsp_info.dsp_sysctrl[PLL_LOCK].base_addr, g_dsp_info.dsp_sysctrl[PLL_LOCK].offset, g_dsp_info.dsp_sysctrl[PLL_LOCK].start_bit, g_dsp_info.dsp_sysctrl[PLL_LOCK].end_bit);
        }
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].base_addr, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].offset, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].start_bit, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].end_bit);
    }
    else if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PD].base_addr))
    {
        //P532
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PD].base_addr, g_dsp_info.dsp_sysctrl[PD].offset, g_dsp_info.dsp_sysctrl[PD].start_bit, g_dsp_info.dsp_sysctrl[PD].end_bit);
    }
    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_disable(void)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_info.dsp_state.spin_lock), irq_flags);
    /* close dsp dfs */
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PLL_EN].base_addr))
    {
        //k3、V7R5
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].base_addr, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].offset, g_dsp_info.dsp_sysctrl[PLL_CLK_GT].start_bit, g_dsp_info.dsp_sysctrl[PLL_CLK_GT  ].end_bit);
        if(CHIP_K3V5 == bsp_get_version_info()->chip_type)
        {
            hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
        else if((CHIP_V750 == bsp_get_version_info()->chip_type) || (CHIP_V722 == bsp_get_version_info()->chip_type))
        {
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
        else if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
        {
            hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[PLL_EN].base_addr, g_dsp_info.dsp_sysctrl[PLL_EN].offset, g_dsp_info.dsp_sysctrl[PLL_EN].start_bit, g_dsp_info.dsp_sysctrl[PLL_EN].end_bit);
        }
    }
    else if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[PD].base_addr))
    {
        //P532
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[PD].base_addr, g_dsp_info.dsp_sysctrl[PD].offset, g_dsp_info.dsp_sysctrl[PD].start_bit, g_dsp_info.dsp_sysctrl[PD].end_bit);
    }
    spin_unlock_irqrestore(&(g_dsp_info.dsp_state.spin_lock), irq_flags);

    return 0;
}

void bsp_bbe_refclk_enable(void)
{
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr))
    {
        //k3
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].end_bit);
    }
}

void bsp_bbe_refclk_disable(void)
{
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr))
    {
        //k3
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].end_bit);
    }
}

void bsp_bbe_peri_refclk_enable(void)
{
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr))
    {
        //V7R5在C核唤醒时打开 peri 参考时钟
        hi_dsp_set_reg(0x2, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].end_bit);
    }
}

void bsp_bbe_peri_refclk_disable(void)
{
    if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr))
    {
        //V7R5在C核睡眠时关闭 peri 参考时钟
        hi_dsp_set_reg(0x2, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].end_bit);
    }
}


/* 0:dsp pll   1:ccpu/peri pll*/
void bsp_bbe_chose_pll(u32 flag)
{
    u32 tmp = 0;
    if(0 == flag)
    {
        if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            tmp = readl(g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
            /* first: bbe sel dsp pll */
            tmp &= ~0x30;
            tmp |= 0x300020;
            writel(tmp, g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=1 */
            tmp &= ~0xF;
            tmp |= 0xF0000;
            writel(tmp, g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5、V722
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].end_bit);
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].base_addr, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].offset, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].start_bit, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].end_bit);
            if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V722 == bsp_get_version_info()->chip_type)
            {
                hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
                hi_dsp_set_reg(3, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
            }
            else if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V750 == bsp_get_version_info()->chip_type)
            {
                hi_dsp_set_reg(2, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
                hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
            }
            hi_dsp_set_reg(0x2, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].end_bit);
        }
    }
    else
    {
        if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            tmp = readl(g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=2 */
            tmp &= ~0xF;
            tmp |= 0xF0001;
            writel(tmp, g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
            udelay(1);
            /* bbe sel ccpu pll */
            tmp &= ~0x30;
            tmp |= 0x300010;
            writel(tmp, g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_info.dsp_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5、V722
            hi_dsp_set_reg(0x2, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_EN].end_bit);
            if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V722 == bsp_get_version_info()->chip_type)
            {
                hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
                hi_dsp_set_reg(3, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
            }
            else if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V750 == bsp_get_version_info()->chip_type)
            {
                hi_dsp_set_reg(2, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
                hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
            }
            udelay(1);
            hi_dsp_set_reg(0x2, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].base_addr, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].offset, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].start_bit, g_dsp_info.dsp_sysctrl[DSP0_REFCLK_SW].end_bit);
            hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].base_addr, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].offset, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].start_bit, g_dsp_info.dsp_sysctrl[BBE_REFCLK_DIS].end_bit);
        }
    }
}

int bsp_dsp_dfs_pll_status(void)
{
    int ret = PWRCTRL_COMM_ON;
    if(1 == g_dsp_drx.drx_bbe16_pll)
    {
        return PWRCTRL_COMM_ON;
    }
    else
    {
        ret = bsp_dsp_pll_status();
        if(ret == 1)
        {
            ret = PWRCTRL_COMM_ON;
        }
        else
        {
            ret = PWRCTRL_COMM_OFF;
        }
        return ret;
    }
}


int bsp_dsp_dfs_pll_enable(void)
{
    int ret = 0;
    if(g_dsp_info.dsp_pwc_ctrl.can_switch_pll)
    {
        if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V8R5 == bsp_get_version_info()->chip_type)
        {
            return ret;
        }
        else
        {
            ret = bsp_dsp_pll_enable();
            bsp_bbe_chose_pll(0);
        }
    }
    if(PLAT_FPGA == bsp_get_version_info()->plat_type && CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        /*适配V7R5 sft环境，在访问TCM空间之前，必须把dsp_freqmode分频比置为0，否则会挂死*/
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
    }
    if(PLAT_FPGA == bsp_get_version_info()->plat_type && CHIP_V722 == bsp_get_version_info()->chip_type)
    {
        /*适配V722 sft环境，在访问TCM空间之前，必须把dsp_freqmode和BBE16_CORE_CLK_DIV分频比置为0，否则会挂死*/
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
    }
    return ret;
}

int bsp_dsp_dfs_pll_disable(void)
{
    int ret = 0;
    if(1 == g_dsp_drx.drx_bbe16_pll)
    {
        return ret;
    }
    else
    {
        if(g_dsp_info.dsp_pwc_ctrl.can_switch_pll)
        {
            if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V8R5 == bsp_get_version_info()->chip_type)
            {
                return ret;
            }
            else
            {
                bsp_bbe_chose_pll(1);
                ret = bsp_dsp_pll_disable();
            }
        }
        return ret;
    }
}

void bsp_dsp_om_log(void)
{
    (void)bsp_pm_log(PM_OM_DSP, sizeof(struct dsp_pm_om_qos_log), g_dsp_info.dsp_timedump_addr);
}

int bsp_msp_bbe_store(void)
{
    u32 tmp_time = 0;
    int ret = 0;

    g_dsp_info.dsp_state.is_image_need_store = 1;
    g_dsp_info.dsp_state.is_dsp_deep_sleep = 1;
    g_dsp_info.dsp_state.is_image_has_store = 0;

    if(!g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret |= bsp_bbe_store();
        g_dsp_info.dsp_state.is_image_need_store = 0;
        g_dsp_info.dsp_state.is_msp_storing = 1;
    }
    /* msp 记录保存标记时间打点*/
    tmp_time = bsp_get_slice_value();
    writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->msp_store);
    bsp_dsp_om_log();
    return ret;
}

int bsp_msp_bbe_is_stored(void)
{
    int ret = 0;

    if(!g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
       ret = (int)(g_dsp_info.dsp_state.is_image_need_store &&
                g_dsp_info.dsp_state.is_dsp_deep_sleep &&
                !g_dsp_info.dsp_state.is_image_has_store);
    }
    else
    {
        ret = (int)( !g_dsp_info.dsp_state.is_image_need_store &&
                g_dsp_info.dsp_state.is_dsp_deep_sleep &&
                g_dsp_info.dsp_state.is_image_has_store);
    }

    return ret;
}
u32 bbe_restore_print = 0;
int bsp_msp_bbe_restore(void)
{
    int ret = 0;
    u32 stamp_start = 0;
    u32 stamp_end = 0;
    u32 tmp_time = 0;
    /* 下电处理在msp中处理的产品形态，条件恒为真 */
    if(g_dsp_info.dsp_state.is_image_has_store)
    {
        stamp_start = bsp_get_slice_value();
        ret = bsp_bbe_restore();
        g_dsp_info.dsp_state.is_msp_restoring = 1;

        /* msp 记录tcm 恢复时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dsp_restore);

        stamp_end = bsp_get_slice_value();
        if(bbe_restore_print)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "bbe restore: %d .\r\n",stamp_end-stamp_start);
        }
    }

    /* msp 记录恢复时间打点*/
    tmp_time = bsp_get_slice_value();
    writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->msp_restore);

    g_dsp_info.dsp_state.is_image_need_store = 0;
    g_dsp_info.dsp_state.is_dsp_deep_sleep = 0;

    return ret;
}

int bsp_msp_bbe_is_restored(void)
{
    int ret = 0;

    ret = (int)(!g_dsp_info.dsp_state.is_image_need_store &&
                !g_dsp_info.dsp_state.is_dsp_deep_sleep);

    return ret;
}

int bsp_msp_wait_edma_ok(void)
{
    int ret = 0;
    u32 tmp_time = 0;
    if (g_dsp_info.dsp_state.is_msp_restoring)
    {
        ret = bsp_bbe_wait_restore_ok();

        /* msp 记录恢复完成时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->msp_restore_ok);

        g_dsp_info.dsp_state.is_image_has_store = 0;
        g_dsp_info.dsp_state.is_msp_restoring   = 0;
    }
    else if(g_dsp_info.dsp_state.is_msp_storing)
    {
        ret = bsp_bbe_wait_store_ok();

        /*msp记录备份完成时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dsp_store_end);

        g_dsp_info.dsp_state.is_image_has_store = 1;
        g_dsp_info.dsp_state.is_msp_storing     = 0;
    }
    return ret;
}

int bsp_msp_is_edma_ok(void)
{
    int ret = 0;

    ret = (int)(!g_dsp_info.dsp_state.is_image_has_store &&
                !g_dsp_info.dsp_state.is_msp_restoring);

    return ret;
}

int bsp_bbe_dpm_prepare(struct dpm_device *dev)
{
    /* bbe下电前存储 */
    int ret = 0;
    u32 tmp_time = 0;

    if(g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        /* dpm保存tcm之前时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dpm_store);

        if (g_dsp_info.dsp_state.is_image_need_store && !g_dsp_info.dsp_state.is_image_has_store)
        {
            ret = bsp_bbe_clock_enable();
            ret |= bsp_bbe_unreset();


            /* save public image's data */
            ret |= bsp_bbe_store();
            /* dpm保存tcm开始之后时间打点*/
            tmp_time = bsp_get_slice_value();
            writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dsp_store);
        }
    }

    return ret;
}

int bsp_bbe_dpm_suspend_late(struct dpm_device *dev)
{
    /* 在设备进入睡眠模式之前判断是否真的存储完成，如果完成，则将bbe下电 */
    int ret = 0;
    u32 tmp_time = 0;
    if(g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        if (g_dsp_info.dsp_state.is_image_need_store && !g_dsp_info.dsp_state.is_image_has_store)
        {
            ret = bsp_bbe_wait_store_ok();
            g_dsp_info.dsp_state.is_image_has_store = 1;
            /* dpm保存tcm完成之后时间打点*/
            tmp_time = bsp_get_slice_value();
            writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dsp_store_end);
            ret |= bsp_bbe_reset();
            ret |= bsp_bbe_clock_disable();
        }

        ret |= bsp_dsp_reset();
        ret |= bsp_dsp_clock_disable();
#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_disable();
#else
        ret |= bsp_dsp_pll_disable();
#endif

        if (g_dsp_info.dsp_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_off();
        }

        /* dpm下电之前时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->poweroff);
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        /* K3V5路径，bbe16单独上下电，DPM只负责关闭bbp子系统参考时钟 */
        bsp_bbe_refclk_disable();
#else
        /* V7R5路径，bbe16单独上下电，DPM只负责关闭bbp子系统参考时钟 ，此时bbp子系统使用的时钟源是peri pll，所以需要关闭peri 参考时钟*/
        bsp_bbe_peri_refclk_disable();
#endif
    }

    return ret;
}

int bsp_bbe_dpm_resume_early(struct dpm_device *dev)
{
    /* dsp上电 */
    int ret = 0;
    u32 tmp_time = 0;

    if(g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        if (g_dsp_info.dsp_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_on();
        }

#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_enable();
#else
        ret |= bsp_dsp_pll_enable();
#endif
        ret |= bsp_dsp_clock_enable();
        ret |= bsp_dsp_unreset();

        /* dpm上电恢复之后时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->poweron);
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        /* K3V5路径，bbe16单独上下电，DPM只负责打开bbp子系统参考时钟 */
        bsp_bbe_refclk_enable();
#else
        /* V7R5路径，bbe16单独上下电，DPM只负责打开bbp子系统参考时钟 ，此时bbp子系统使用的时钟源是peri pll，所以需要打开peri 参考时钟*/
        bsp_bbe_peri_refclk_enable();
#endif
    }

    return ret;
}

int bsp_bbe_dpm_complete(struct dpm_device *dev)
{
    /* dsp上电后关bbe */
    int ret = 0;
    u32 tmp_time = 0;

    if(g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        if (g_dsp_info.dsp_state.is_image_need_store && !g_dsp_info.dsp_state.is_image_has_store)
        {
            ret = bsp_bbe_wait_store_ok();
            /* dpm恢复之前等待store完成时间打点*/
            tmp_time = bsp_get_slice_value();
            writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dpm_wait_store_ok);
            ret |= bsp_bbe_reset();
            ret |= bsp_bbe_clock_disable();
        }
        /* dpm恢复之后时间打点*/
        tmp_time = bsp_get_slice_value();
        writel(tmp_time, (u32)&g_dsp_info.dsp_timedump_addr->dpm_restore);
    }

    return ret;
}

#ifdef CONFIG_CCORE_PM
static struct dpm_device g_bbe_dpm_device={
    .device_name = "bbe_dpm",
    .prepare = bsp_bbe_dpm_prepare,
    .suspend_early = NULL,
    .suspend = NULL,
    .suspend_late = bsp_bbe_dpm_suspend_late,
    .resume_early = bsp_bbe_dpm_resume_early,
    .resume = NULL,
    .resume_late = NULL,
    .complete = bsp_bbe_dpm_complete,
};
#endif

void bsp_dsp_rsracc_suspend_end(rsr_acc_description *bd_descri)
{	
    (void)bsp_bbe_dpm_suspend_late(NULL);
}	

void bsp_dsp_rsracc_resume_begin(rsr_acc_description *bd_descri)
{	
    (void)bsp_bbe_dpm_resume_early(NULL);	
}

struct rsracc_cb_s g_dsp_rsracc_ops =
{	
    .suspend_begin  = NULL,
    .suspend_end    = bsp_dsp_rsracc_suspend_end,
    .resume_begin   = bsp_dsp_rsracc_resume_begin,
    .resume_end     = NULL,
};

struct bd_desc_s g_dsp_rsracc_device =
{	
    .level = rsracc_bd_level_3,
    .name = "dsp_rsracc",
    .ops = &g_dsp_rsracc_ops,
    .only_ops_in_bd = true,	
};

int bsp_dsp_store_tcm(void)
{
    int ret = 0;
    struct dsp_dump_proc_flag *flag;
    
    flag = (struct dsp_dump_proc_flag *)((unsigned int)SHM_BASE_ADDR + SHM_OFFSET_DSP_FLAG);
    flag->dsp_dump_flag = 0;

    ret = (int)(g_dsp_info.dsp_state.is_dsp_power_on &&
                g_dsp_info.dsp_state.is_dsp_clock_enable &&
                g_dsp_info.dsp_state.is_dsp_unreset &&
                g_dsp_info.dsp_state.is_bbe_power_on &&
                g_dsp_info.dsp_state.is_bbe_clock_enable &&
                g_dsp_info.dsp_state.is_bbe_unreset);

    if (!ret)
    {
        //bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "in dpm!\r\n");
        return (-1);
    }

    flag->dsp_dump_flag = SAVE_TCM_BEGIN;
    ret = bsp_bbe_stop();
    ret |= bsp_bbe_store_dtcm();
    ret |= bsp_bbe_store_itcm();
    ret |= bsp_bbe_wait_store_ok();
    ret |= bsp_bbe_wait_store_itcm_ok();
    if (ret)
    {
        //bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to store tcm\r\n");
        return (-1);
    }
    flag->dsp_dump_flag = SAVE_TCM_END;

    return ret;

}

/*****************************************************************************
 函 数 名  : ccpu_reset_bbe16_and_wait_idle
 功能描述  : c核复位后关闭并等bbe16进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_bbe16_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_halt_bbe16_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;

    bsp_reset_timestamp(0x1, STAMP_RESET_BBE16_ENTER_IDLE);

    /*halt*/
    //hi_dsp_get_reg(&regvalue, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].offset, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].start_bit, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].end_bit);

    /*if (!regvalue)
    {*/
        /*(void)bsp_ipc_int_send(IPC_CORE_LDSP, IPC_DSP_INT_SRC_CCPU_RESET);*/

	    /*wait for holding*/
	    /*u32slicebegin = bsp_get_slice_value();
	    do{
	    }while(CHECK_TIMEOUT(u32slicebegin));*/

        //bsp_reset_timestamp(0x2, STAMP_RESET_BBE16_ENTER_IDLE);

        /*stop bbe16*/
        hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].base_addr, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].offset, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].start_bit, g_dsp_info.dsp_sysctrl[BBE16_RUNSTALL].end_bit);


	    u32slicebegin = bsp_get_slice_value();
	    do{
	    }while(CHECK_TIMEOUT(u32slicebegin));
    /*}*/

    bsp_reset_timestamp(0x2, STAMP_RESET_BBE16_ENTER_IDLE);
	/* stop socp channel to prevent data transferring when bbe16 powered down */
	regvalue = readl(SOCP_REG_BASEADDR + SOCP_REG_ENCSRC_BUFCFG1(SOCP_CODER_SRC_LDSP1));
	writel((regvalue & 0xfffffffe), (SOCP_REG_BASEADDR + SOCP_REG_ENCSRC_BUFCFG1(SOCP_CODER_SRC_LDSP1)));
	while(readl(SOCP_REG_BASEADDR + SOCP_REG_ENCSTAT) & (1 << (SOCP_CODER_SRC_LDSP1)))
	{

	}

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_BBE16_ENTER_IDLE);

    return 0;
}

int ccpu_reset_bbe16_sysbus(void)
{
    /*reset bbe16 and sysbus*/
    hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_SRST_EN].end_bit);
    hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_PD_SRST_EN].end_bit);
    hi_dsp_set_reg(1, g_dsp_info.dsp_sysctrl[BBE16_DBG_SRST_EN].base_addr, g_dsp_info.dsp_sysctrl[BBE16_DBG_SRST_EN].offset, g_dsp_info.dsp_sysctrl[BBE16_DBG_SRST_EN].start_bit, g_dsp_info.dsp_sysctrl[BBE16_DBG_SRST_EN].end_bit);
    return 0;
}

/*lint -save -e525*/
void bsp_dsp_init(void)
{
    int ret = 0;
    int i = 0;
    char *reg_name[DSP_DTS_REG_BUTT] = {
                            "bbe16_pd_clk_en",
                            "bbe16_pd_clk_dis",
                            "bbe16_pd_srst_dis",
                            "bbe16_pd_srst_en",
                            "bbe16_core_srst_dis",
                            "bbe16_dbg_srst_dis",
                            "bbe16_core_srst_en",
                            "bbe16_dbg_srst_en",
                            "pd",
                            "bbe16_runstall",
                            "bbe_refclk_en",
                            "bbe_refclk_dis",
                            "pll_lock",
                            "pll_en",
                            "pll_bp",
                            "pll_postdivpd",
                            "pll_clk_gt",
                            "pll_dfs1",
                            "pll_dfs2",
                            "div_modem_bbe16",
                            "sel_modem_bbe16",
                            "clkdivmasken",
                            "dsp0_core_clk_dis",
                            "dsp0_dbg_clk_dis",
                            "bbe_core_clk_en",
                            "dsp0_dbg_clk_en",
                            "bbe16_mtcmos_ctrl_en",
                            "bbe16_mtcmos_rdy_stat",
                            "bbe16_iso_ctrl_dis",
                            "bbe16_mtcmos_ctrl_dis",
                            "bbe16_iso_ctrl_en",
                            "bbe16_waiti_en",
                            "bbe16_waiti_div",
                            "bbe16_core_clk_div",
                            "dsp0_freqmode",
                            "dsp0_refclk_sw"
                            };
    u32 reg_addr[4];

    char* node_name[2] = {
        "hisilicon,dsp_balong_dtcm",
        "hisilicon,dsp_balong_itcm"
    };

    struct device_node *dev_node = NULL;
    struct dsp_pm_om_qos_log *dump_addr = NULL;
    ST_PWC_SWITCH_STRU cfg;

    bsp_dsp_state_init();

    (void)bsp_register_master_idle(BBE16_IDLE, ccpu_halt_bbe16_and_wait_idle);
    (void)bsp_register_master_idle(BBE16_SYSBUS, ccpu_reset_bbe16_sysbus);

    dump_addr = bsp_pm_dump_get(PM_OM_DSP, sizeof(struct dsp_pm_om_qos_log));
    if(dump_addr == NULL)
    {
        g_dsp_info.dsp_timedump_addr = &g_dsp_info.dsp_timedump;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp get dump space failed!\n");
    }
    else
    {
        g_dsp_info.dsp_timedump_addr = dump_addr;
        ret = memset_s(g_dsp_info.dsp_timedump_addr, sizeof(struct dsp_pm_om_qos_log), 0, sizeof(struct dsp_pm_om_qos_log));
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_timedump memset fail\n");
        }
    }

    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)&cfg, sizeof(ST_PWC_SWITCH_STRU)))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Bsp_dsp get NV_ID_DRV_NV_PWC_SWITCH failed!\n");
	}
    else
    {
        g_dsp_drx.drx_bbe16_pd = cfg.drx_bbe16_pd;
        g_dsp_drx.drx_bbe16_pll =  cfg.drx_bbe16_pll;
    }

    dev_node = of_find_compatible_node(NULL,NULL,node_name[0]);
    if(!dev_node)
    {

        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "get dsp_balong_dtcm node failed!\n");
        return;
    }

    /* 内存映射，获得基址 */
    g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_balong_dtcm iomap fail\n");
        return;
    }
    g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size = LPHY_PUB_DTCM_SIZE;

    ret  = of_property_read_u32(dev_node, "is_pmctrl_in_dpm", &g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm);
    ret |= of_property_read_u32(dev_node, "can_switch_pll", &g_dsp_info.dsp_pwc_ctrl.can_switch_pll);
    ret |= of_property_read_u32(dev_node, "can_switch_waiti", &g_dsp_info.dsp_pwc_ctrl.can_switch_waiti);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dev_node read fail\n");
        return;
    }
    dev_node = NULL;
    dev_node = of_find_compatible_node(NULL,NULL,node_name[1]);
    if(!dev_node)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "get dsp_balong_itcm node failed!\n");
        return;
    }

    /* 内存映射，获得基址 */
    g_dsp_info.dsp_ctrl.tcm_itcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_info.dsp_ctrl.tcm_itcm_base_addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_balong_itcm iomap fail\n");
        return;
    }
    g_dsp_info.dsp_ctrl.lphy_pub_itcm_size = LPHY_PUB_ITCM_SIZE;

    g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr = (int)ioremap_wc((MMU_VA_T)DDR_TLPHY_IMAGE_ADDR, DDR_TLPHY_IMAGE_SIZE);
    g_dsp_info.dsp_ctrl.bbe_ddr_pub_itcm_addr = g_dsp_info.dsp_ctrl.bbe_ddr_pub_dtcm_addr + LPHY_PUB_DTCM_SIZE;

    for(i = 0; i < DSP_DTS_REG_BUTT; i++)
    {
        ret = of_property_read_u32_array(dev_node, reg_name[i], reg_addr, DSP_ADDR_BUTT);
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dev_node reg read fail\n");
            return;
        }
        g_dsp_info.dsp_sysctrl[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[DSP_BASE_ADDR]);
        g_dsp_info.dsp_sysctrl[i].offset = reg_addr[DSP_OFFSET];
        g_dsp_info.dsp_sysctrl[i].start_bit = reg_addr[DSP_START_BIT];
        g_dsp_info.dsp_sysctrl[i].end_bit = reg_addr[DSP_END_BIT];
//        printf("[dsp]: %s 0x%x 0x%x\n", reg_name[i], reg_addr[DSP_BASE_ADDR], g_dsp_info.dsp_sysctrl[i].base_addr);
    }

    if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        ret = bsp_dsp_dfs_pll_disable();
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_dfs_pll_disable fail\n");
            return;
        }
        /* 配置dsp pll的分频系数，使得dsp pll初始输出为900MHz */
        writel(0xe00000, g_dsp_info.dsp_sysctrl[PLL_DFS1].base_addr + g_dsp_info.dsp_sysctrl[PLL_DFS1].offset);
        writel(0x110102e, g_dsp_info.dsp_sysctrl[PLL_DFS2].base_addr + g_dsp_info.dsp_sysctrl[PLL_DFS2].offset);
    }

    if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V722 == bsp_get_version_info()->chip_type)
    {
        ret = bsp_dsp_dfs_pll_disable();
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_dfs_pll_disable fail\n");
            return;
        }
    }

    if(PLAT_FPGA == bsp_get_version_info()->plat_type && CHIP_V722 == bsp_get_version_info()->chip_type)
    {
        /*适配V722 sft环境，在访问TCM空间之前，必须把dsp_freqmode和BBE16_CORE_CLK_DIV分频比置为0，否则会挂死*/
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].base_addr, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].offset, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].start_bit, g_dsp_info.dsp_sysctrl[DSP0_FREQMODE].end_bit);
        hi_dsp_set_reg(0, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].base_addr, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].offset, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].start_bit, g_dsp_info.dsp_sysctrl[BBE16_CORE_CLK_DIV].end_bit);
    }

    spin_lock_init(&(g_dsp_info.dsp_state.spin_lock));


    if(g_dsp_info.dsp_pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret  = bsp_bbe_power_on();
        ret |= bsp_dsp_clock_enable();
        ret |= bsp_dsp_unreset();

        ret |= bsp_bbe_reset();
        ret |= bsp_bbe_clock_disable();
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[TLdsp]fail to init\n");
        }
    }

    if(g_dsp_info.dsp_pwc_ctrl.can_switch_waiti)
    {
        //配置V7R5 DSP WAITI模式分频比
        ret = bsp_bbe_waiti_enable();
    }

    if(bsp_rsracc_support())
    {
        ret = bsp_rsracc_register(&g_dsp_rsracc_device, 1);
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[TLdsp]fail to register rsracc\n");
        }
    }
    else
    {
#ifdef CONFIG_CCORE_PM
        ret = bsp_device_pm_add(&g_bbe_dpm_device);
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[TLdsp]fail to add pm device\n");
        }
#endif
    }
}

/*lint -restore*/

/* print the statistics info of dsp */
int bsp_dsp_info(void)
{
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "BBE16 Show Statistics Info:\n");

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "bsp_bbe_load_muti is called: %d\n", g_dsp_info.dsp_state.is_dsp_load_muti);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp restore count: %d\n", g_dsp_info.dsp_state.dsp_restore_count);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp restore succ count: %d\n", g_dsp_info.dsp_state.dsp_restore_succ_count);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp store count: %d\n", g_dsp_info.dsp_state.dsp_store_count);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp store succ count: %d\n", g_dsp_info.dsp_state.dsp_store_succ_count);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp is run: %d\n", g_dsp_info.dsp_state.is_dsp_running);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp power is on: %d\n", g_dsp_info.dsp_state.is_dsp_power_on);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp pd_clk is on: %d\n", g_dsp_info.dsp_state.is_dsp_clock_enable);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp bbe_clk is on: %d\n", g_dsp_info.dsp_state.is_bbe_clock_enable);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp pd_unreset is on: %d\n", g_dsp_info.dsp_state.is_dsp_unreset);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp bbe_unreset is on: %d\n", g_dsp_info.dsp_state.is_bbe_unreset);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "DDR_TLPHY_IMAGE_ADDR is : 0x%x\n", DDR_TLPHY_IMAGE_ADDR);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "TCM_DTCM_BASE_ADDR is : 0x%p\n", g_dsp_info.dsp_ctrl.tcm_dtcm_base_addr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "lphy_pub_dtcm_size is : 0x%x\n", g_dsp_info.dsp_ctrl.lphy_pub_dtcm_size);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "TCM_ITCM_BASE_ADDR is : 0x%p\n", g_dsp_info.dsp_ctrl.tcm_itcm_base_addr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "lphy_pub_itcm_size is : 0x%x\n", g_dsp_info.dsp_ctrl.lphy_pub_itcm_size);

    return 0;
}


