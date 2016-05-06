/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_abb.c
*
*   作    者 :  z00227143
*
*   描    述 :  本文件主要完成ABB的初始化，并提供ABB寄存器的读写接口
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/

/*lint --e{522,534,537} */
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_malloc.h>
#include <osl_spinlock.h>

#include <securec.h>

#include <mdrv_pm.h>

#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_dpm.h>
#include <bsp_abb.h>
#include <bsp_hardtimer.h>


#if defined(ABB_BUILD_ALL) || defined(ABB_BUILD_TV310)

static spinlock_t g_abb_tv310_spin_lock;

static struct abb_config g_abb_cfg_tv310[] =
{
    {0x409    ,0x40},
    {0x481    ,0x08},
    {0x4C1    ,0x08},
    {0xC66    ,0x0C},
    {0xCE6    ,0x0C},
    {0x204    ,0x3B},
    {0x20A    ,0x3B},
    {0x211    ,0x3B},
    {0x214    ,0x3B},
    {0x229    ,0x3B},
    {0x22C    ,0x3B},
    {0x404    ,0x03},
    {0x405    ,0x30},
    {0x412    ,0x20},
    {0x415    ,0x20},
};

int bsp_abb_tv310_init(u32 abb_version, u32 *is_supported);

void bsp_abb_tv310_init_later(void)
{
    u32 i = 0;
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_gpll) {
        bsp_abb_read(0x814, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x814, value);
    }

    if (g_abb_pm_switch.drx_abb_scpll) {
        bsp_abb_read(0x800, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x800, value);
    }

    for (i = 0; i < sizeof(g_abb_cfg_tv310) / sizeof(g_abb_cfg_tv310[0]); i++)
        bsp_abb_write(g_abb_cfg_tv310[i].addr, g_abb_cfg_tv310[i].value);
}

static u32 g_abb_pm_tuning_value = 0;

int bsp_abb_tv310_suspend(struct dpm_device *dev)
{
    bsp_abb_read(0x891, &g_abb_pm_tuning_value);

    return 0;
}

int bsp_abb_tv310_resume(struct dpm_device *dev)
{
    bsp_abb_deassert_reset();

    /* reset VREF*/
    bsp_abb_write(0x88C, 0x10);
    udelay(1);
    bsp_abb_write(0x88C, 0x00);

    bsp_abb_tv310_init_later();

    bsp_abb_write(0x891, g_abb_pm_tuning_value);
    bsp_abb_write(0xC6F, g_abb_pm_tuning_value);
    bsp_abb_write(0xCEF, g_abb_pm_tuning_value);

    return 0;
}

int bsp_abb_tv310_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv310_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv310_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return (int)PWRCTRL_COMM_ON;
}

static u32 bsp_abb_tv310_g_pll_vote = 0;
static u32 bsp_abb_tv310_sc_pll_vote = 0;
static void bsp_abb_tv310_g_pll_ctrl(u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_gpll)
        return;

    if (is_enable) {
        bsp_abb_read(0x814, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x814, value);

        do {
            bsp_abb_read(0x814, &value);
            value &= 0x01U << 0x05U;
        } while (value != (0x01U << 0x05U));
    } else {
        bsp_abb_read(0x814, &value);
        value &= ~(0x01U << 0x00U);
        bsp_abb_write(0x814, value);
        bsp_abb_read(0x815, &value);
        value &= ~(0x01U << 0x00U);
        bsp_abb_write(0x815, value);
    }
}

static void bsp_abb_tv310_sc_pll_ctrl(u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_scpll)
        return;

    if (is_enable) {
        bsp_abb_read(0x800, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x800, value);

        do {
            bsp_abb_read(0x800, &value);
            value &= 0x01U << 0x05U;
        } while (value != (0x01U << 0x05U));
    } else {
        bsp_abb_read(0x800, &value);
        value &= ~(0x01U << 0x00U);
        bsp_abb_write(0x800, value);
    }
}

int bsp_abb_tv310_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv310_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_enable_stamp);

        if (!bsp_abb_tv310_g_pll_vote)
            bsp_abb_tv310_g_pll_ctrl(1);

        bsp_abb_tv310_g_pll_vote |= 0x01U << (u32)enModemId;

        writel(bsp_abb_tv310_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_lock_stamp);
    } else {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_enable_stamp);

        if (!bsp_abb_tv310_sc_pll_vote)
            bsp_abb_tv310_sc_pll_ctrl(1);

        bsp_abb_tv310_sc_pll_vote |= 0x01U << (u32)enCommMode;

        writel(bsp_abb_tv310_sc_pll_vote, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_lock_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv310_spin_lock, flags);

    return 0;
}
int bsp_abb_tv310_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv310_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_tv310_g_pll_vote &= ~(0x01U << (u32)enModemId);

        if (!bsp_abb_tv310_g_pll_vote)
            bsp_abb_tv310_g_pll_ctrl(0);

        writel(bsp_abb_tv310_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_disable_stamp);
    } else {
        bsp_abb_tv310_sc_pll_vote &= ~(0x01U << (u32)enCommMode);

        if (!bsp_abb_tv310_sc_pll_vote)
            bsp_abb_tv310_sc_pll_ctrl(0);

        writel(bsp_abb_tv310_sc_pll_vote, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_disable_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv310_spin_lock, flags);

    return 0;
}
int bsp_abb_tv310_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    u32 value = 0;
    unsigned long flags = 0;
    int ret = (int)PWRCTRL_COMM_ON;

    spin_lock_irqsave(&g_abb_tv310_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_read(0x814, &value);
        ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
    } else {
        bsp_abb_read(0x800, &value);
        ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
    }

    spin_unlock_irqrestore(&g_abb_tv310_spin_lock, flags);

    return ret;
}

int bsp_abb_tv310_init(u32 abb_version, u32 *is_supported)
{
    u32 value = 0;
    u32 is_timeout = 0;
    u32 start_stamp = 0;

    if (COMSTARTV310 != abb_version)
        return 0;

    if (is_supported)
        *is_supported = 1;

    /* reset VREF*/
    bsp_abb_write(0x88C, 0x10);
    udelay(1);
    bsp_abb_write(0x88C, 0x00);

    /* start ABB calibration */
    bsp_abb_write(0x88D, 0x00);
    bsp_abb_write(0x88D, 0x01);
    start_stamp = bsp_get_slice_value();
    do {
        bsp_abb_read(0x8A0, &value);
        if (get_timer_slice_delta(start_stamp, bsp_get_slice_value()) > 6) {
            is_timeout = 1;
            break;
        }
    }while (!(value & 0x01));

    if (is_timeout)
        value = 0x40;
    else
        bsp_abb_read(0x8A1, &value);

    bsp_abb_write(0x891, value);
    bsp_abb_write(0xC6F, value);
    bsp_abb_write(0xCEF, value);

    bsp_abb_tv310_init_later();

    if (!g_abb_inited) {
        spin_lock_init(&g_abb_tv310_spin_lock);
        g_abb_ops.abb_suspend       = bsp_abb_tv310_suspend;
        g_abb_ops.abb_resume        = bsp_abb_tv310_resume;
        g_abb_ops.abb_power_up      = bsp_abb_tv310_power_up;
        g_abb_ops.abb_power_down    = bsp_abb_tv310_power_down;
        g_abb_ops.abb_power_status  = bsp_abb_tv310_power_status;
        g_abb_ops.abb_pll_enable    = bsp_abb_tv310_pll_enable;
        g_abb_ops.abb_pll_disable   = bsp_abb_tv310_pll_disable;
        g_abb_ops.abb_pll_status    = bsp_abb_tv310_pll_status;
    }

    return 0;
}

#else

int bsp_abb_tv310_init(u32 abb_version, u32 *is_supported)
{
    return 0;
}

#endif

