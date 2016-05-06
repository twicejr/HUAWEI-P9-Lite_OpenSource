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


#if defined(ABB_BUILD_ALL) || defined(ABB_BUILD_TV260)

#define COMMON_MODE_VOLTAGE_TX_500mV
//#define COMMON_MODE_VOLTAGE_RX_500mV

static spinlock_t g_abb_tv260_spin_lock;

int bsp_abb_tv260_init(u32 abb_version, u32 *is_supported);

void bsp_abb_tv260_init_later(u32 offset)
{
    u32 i = 0;
    u32 value = 0;

    bsp_abb_read(ABB_VERSION_ADDR + offset, &value);
    if ((offset) && (value != COMSTARTV260)) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "there may be only one ComStar TV260\n");
        return;
    }

    /* reset VREF*/
    bsp_abb_write(offset + 0x80C, 0x10);
    udelay(1);
    bsp_abb_write(offset + 0x80C, 0x00);

    /* start ABB calibration */
    bsp_abb_write(offset + 0x80D, 0x00);
    bsp_abb_write(offset + 0x80D, 0x01);
    do {
        bsp_abb_read(offset + 0x830, &value);
    } while (!(value & 0x01));

    bsp_abb_read(offset + 0x831, &value);
    bsp_abb_write(offset + 0x810, value);
    bsp_abb_write(offset + 0x811, value);
    bsp_abb_write(offset + 0x812, value);
    bsp_abb_write(offset + 0x813, value);

    for (i = 0; i < ABB_INIT_NV_NUM; i++) {
        if (g_abb_init_cfg.cfg[i].addr != 0xFFFF)
            bsp_abb_write(offset + g_abb_init_cfg.cfg[i].addr, g_abb_init_cfg.cfg[i].value);
        else
            break;
    }

    if (g_abb_pm_switch.drx_abb_gpll) {
        bsp_abb_read(offset + 0x014, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(offset + 0x014, value);
    }

    if (g_abb_pm_switch.drx_abb_scpll) {
        bsp_abb_read(offset + 0x000, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(offset + 0x000, value);

        bsp_abb_read(offset + 0x00A, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(offset + 0x00A, value);
    }
}

static struct abb_config g_abb_data_tv260[] =
{
    {0x611  ,0x00},
    {0x602  ,0x00},
    {0x19E  ,0x00},
    {0x1A4  ,0x00},
    {0x1B7  ,0x00},
    {0x612  ,0x00},
};

int bsp_abb_tv260_suspend(struct dpm_device *dev)
{
    u32 i = 0;

    for (i = 0; i < sizeof(g_abb_data_tv260) / sizeof(g_abb_data_tv260[0]); i++)
        bsp_abb_read(g_abb_data_tv260[i].addr, &g_abb_data_tv260[i].value);

    return 0;
}

int bsp_abb_tv260_resume(struct dpm_device *dev)
{
    u32 i = 0;

    bsp_abb_deassert_reset();

    bsp_abb_tv260_init(COMSTARTV260, NULL);

    for (i = 0; i < sizeof(g_abb_data_tv260) / sizeof(g_abb_data_tv260[0]); i++)
        bsp_abb_write(g_abb_data_tv260[i].addr, g_abb_data_tv260[i].value);

    return 0;
}

int bsp_abb_tv260_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv260_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv260_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return (int)PWRCTRL_COMM_ON;
}

static u32 bsp_abb_tv260_g_pll_vote = 0;
static u32 bsp_abb_tv260_sc_pll_vote[2] = {0, 0};
static void bsp_abb_tv260_g_pll_ctrl(u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_gpll)
        return;

    if (is_enable) {
        bsp_abb_read(0x014, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x014, value);

        do {
            bsp_abb_read(0x834, &value);
            value &= 0x01U << 0x00U;
        } while (value != (0x01U << 0x00U));
    } else {
        bsp_abb_read(0x014, &value);
        value &= ~(0x01U << 0x00U);
        bsp_abb_write(0x014, value);
    }
}

static void bsp_abb_tv260_sc_pll_ctrl(u32 modem_id, u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_scpll)
        return;

    if (modem_id == 0) {
        if (is_enable) {
            bsp_abb_read(0x000, &value);
            value |= 0x01U << 0x00U;
            bsp_abb_write(0x000, value);

            do {
                bsp_abb_read(0x000, &value);
                value &= 0x01U << 0x06U;
            } while (value != (0x01U << 0x06U));
        } else {
            bsp_abb_read(0x000, &value);
            value &= ~(0x01U << 0x00U);
            bsp_abb_write(0x000, value);
        }
    } else {
        if (is_enable) {
            bsp_abb_read(0x00A, &value);
            value |= 0x01U << 0x00U;
            bsp_abb_write(0x00A, value);

            do {
                bsp_abb_read(0x00A, &value);
                value &= 0x01U << 0x06U;
            } while (value != (0x01U << 0x06U));
        } else {
            bsp_abb_read(0x00A, &value);
            value &= ~(0x01U << 0x00U);
            bsp_abb_write(0x00A, value);
        }
    }
}

int bsp_abb_tv260_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv260_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_enable_stamp);

        if (!bsp_abb_tv260_g_pll_vote)
            bsp_abb_tv260_g_pll_ctrl(1);

        bsp_abb_tv260_g_pll_vote |= 0x01U << (u32)enModemId;

        writel(bsp_abb_tv260_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_lock_stamp);
    } else {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_enable_stamp);

        if (!bsp_abb_tv260_sc_pll_vote[enModemId])
            bsp_abb_tv260_sc_pll_ctrl((u32)enModemId, 1);

        bsp_abb_tv260_sc_pll_vote[enModemId] |= 0x01U << (u32)enCommMode;

        writel(bsp_abb_tv260_sc_pll_vote[0] | bsp_abb_tv260_sc_pll_vote[1] << 16U, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_lock_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv260_spin_lock, flags);

    return 0;
}
int bsp_abb_tv260_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv260_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_tv260_g_pll_vote &= ~(0x01U << (u32)enModemId);

        if (!bsp_abb_tv260_g_pll_vote)
            bsp_abb_tv260_g_pll_ctrl(0);

        writel(bsp_abb_tv260_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_disable_stamp);
    } else {
        bsp_abb_tv260_sc_pll_vote[enModemId] &= ~(0x01U << (u32)enCommMode);

        if (!bsp_abb_tv260_sc_pll_vote[enModemId])
            bsp_abb_tv260_sc_pll_ctrl((u32)enModemId, 0);

        writel(bsp_abb_tv260_sc_pll_vote[0] | bsp_abb_tv260_sc_pll_vote[1] << 16U, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_disable_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv260_spin_lock, flags);

    return 0;
}
int bsp_abb_tv260_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    u32 value = 0;
    unsigned long flags = 0;
    int ret = (int)PWRCTRL_COMM_ON;

    spin_lock_irqsave(&g_abb_tv260_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_read(0x014, &value);
        ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
    } else {
        if (enModemId == PWC_COMM_MODEM_0) {
            bsp_abb_read(0x000, &value);
            ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
        } else {
            bsp_abb_read(0x00A, &value);
            ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
        }
    }

    spin_unlock_irqrestore(&g_abb_tv260_spin_lock, flags);

    return ret;
}

int bsp_abb_tv260_init(u32 abb_version, u32 *is_supported)
{
    int ret = 0;

    if (COMSTARTV260 != abb_version)
        return 0;

    if (is_supported)
        *is_supported = 1;

    if (!g_abb_inited) {
        ret = (int)bsp_nvm_read(NV_ID_DRV_ABB_INIT_CFG, (u8*)&g_abb_init_cfg, sizeof(g_abb_init_cfg));
        if (ret) {
            (void)memset_s((void *)&g_abb_init_cfg, sizeof(g_abb_init_cfg), 0, sizeof(g_abb_init_cfg));
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB read nv fail, ret = %d\n", ret);
        }
    }

    bsp_abb_tv260_init_later(0);
    bsp_abb_tv260_init_later(0x2000);

    if (!g_abb_inited) {
        spin_lock_init(&g_abb_tv260_spin_lock);
        g_abb_ops.abb_suspend       = bsp_abb_tv260_suspend;
        g_abb_ops.abb_resume        = bsp_abb_tv260_resume;
        g_abb_ops.abb_power_up      = bsp_abb_tv260_power_up;
        g_abb_ops.abb_power_down    = bsp_abb_tv260_power_down;
        g_abb_ops.abb_power_status  = bsp_abb_tv260_power_status;
        g_abb_ops.abb_pll_enable    = bsp_abb_tv260_pll_enable;
        g_abb_ops.abb_pll_disable   = bsp_abb_tv260_pll_disable;
        g_abb_ops.abb_pll_status    = bsp_abb_tv260_pll_status;
    }

    return 0;
}

#else

int bsp_abb_tv260_init(u32 abb_version, u32 *is_supported)
{
    return 0;
}

#endif

