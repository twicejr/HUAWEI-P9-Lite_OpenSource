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


#if defined(ABB_BUILD_ALL) || defined(ABB_BUILD_TV300)

#define COMMON_MODE_VOLTAGE_TX_500mV
//#define COMMON_MODE_VOLTAGE_RX_500mV

static spinlock_t g_abb_tv300_spin_lock;

static struct abb_config g_abb_cfg_tv300[] =
{
    {0x611    ,0x00},
    {0x602    ,0x01},
    {0x198    ,0x00},
    {0x19E    ,0x00},
    {0x1A4    ,0x00},
    {0x1B1    ,0x00},
    {0x1B7    ,0x00},
    {0x612    ,0x00},
    {0x608    ,0x01},
    {0x605    ,0x15},
    {0x609    ,0x10},
    {0x606    ,0x40},
    {0x607    ,0x00},
    {0x60A    ,0x00},
    {0x60B    ,0x00},
    {0x60C    ,0x00},
    {0x604    ,0x0B},
    {0x60E    ,0x07},
    {0x0E0    ,0x72},
    {0x0E3    ,0x78},
    {0x0E4    ,0x70},
    {0x0E6    ,0x6D},
    {0x0D1    ,0x00},
    {0x000    ,0x02},
    {0x024    ,0xF3},
    {0x025    ,0x02},
    {0x103    ,0x00},
    {0x104    ,0x10},
    {0x105    ,0x30},
    {0x18F    ,0x20},
    {0x190    ,0x04},
    {0x191    ,0x70},
    {0x193    ,0x0F},
    {0x194    ,0x09},
    {0x002    ,0x02},
    {0x026    ,0x0F},
    {0x027    ,0x72},
    {0x100    ,0x18},
    {0x00F    ,0x83},
    {0x030    ,0xF2},
    {0x031    ,0x56},
    {0x115    ,0x00},
    {0x116    ,0x10},
    {0x117    ,0x20},
    {0x1A1    ,0xEF},
    {0x1A2    ,0x0D},
    {0x1A3    ,0x60},
    {0x1A5    ,0x0C},
    {0x1A6    ,0x18},
    {0x011    ,0x60},
    {0x032    ,0x0D},
    {0x033    ,0x72},
    {0x112    ,0x18},
    {0x005    ,0x27},
    {0x028    ,0xF1},
    {0x029    ,0x02},
    {0x109    ,0x00},
    {0x10A    ,0x10},
    {0x10B    ,0x30},
    {0x195    ,0x20},
    {0x196    ,0x04},
    {0x197    ,0x70},
    {0x199    ,0x0C},
    {0x19A    ,0x11},
    {0x007    ,0x20},
    {0x02A    ,0x0D},
    {0x02B    ,0x72},
    {0x180    ,0x27},
    {0x185    ,0xF1},
    {0x186    ,0x02},
    {0x187    ,0x00},
    {0x188    ,0x10},
    {0x189    ,0x30},
    {0x1AD    ,0x20},
    {0x1AE    ,0x04},
    {0x1AF    ,0x70},
    {0x1B2    ,0x0C},
    {0x1B3    ,0x11},
    {0x182    ,0x20},
    {0x18A    ,0x0D},
    {0x18B    ,0x72},
    {0x00A    ,0x42},
    {0x02C    ,0xF0},
    {0x02D    ,0xA9},
    {0x10F    ,0x11},
    {0x110    ,0x00},
    {0x111    ,0x10},
    {0x19B    ,0xEF},
    {0x19C    ,0x0D},
    {0x19D    ,0x40},
    {0x19F    ,0x0C},
    {0x1A0    ,0x18},
    {0x00C    ,0x40},
    {0x02E    ,0x4C},
    {0x02F    ,0x66},
    {0x01A    ,0x42},
    {0x038    ,0xF0},
    {0x039    ,0xA9},
    {0x11B    ,0x11},
    {0x11C    ,0x00},
    {0x11D    ,0x10},
    {0x1B4    ,0xEF},
    {0x1B5    ,0x0D},
    {0x1B6    ,0x40},
    {0x1B8    ,0x0C},
    {0x1B9    ,0x18},
    {0x01C    ,0x40},
    {0x03A    ,0x4C},
    {0x03B    ,0x66},
    {0x405    ,0xF5},
    {0x406    ,0x56},
    {0x407    ,0x00},
    {0x408    ,0x10},
    {0x409    ,0x2A},
    {0x40A    ,0xEF},
    {0x40B    ,0x0D},
    {0x40C    ,0x60},
    {0x40E    ,0x05},
    {0x40F    ,0x18},
    {0x410    ,0x0C},
    {0x411    ,0x72},
    {0x412    ,0x18},
    {0x198    ,0x00},
    {0x40D    ,0x80},
    {0x0EE    ,0x00},
    {0x08E    ,0x00},
    {0x0EF    ,0x3D},
    {0x08F    ,0x3D},
    {0x099    ,0x00},
    {0x0F9    ,0x00},
    {0x0E9    ,0x00},
    {0x089    ,0x00},
    {0x0EA    ,0x00},
    {0x08A    ,0x00},
    {0x610    ,0x01},
    {0x613    ,0x80},
    {0x614    ,0x00},
    {0x615    ,0x80},
    {0x616    ,0x00},
    {0x617    ,0x80},
    {0x618    ,0x00},
    {0x619    ,0x80},
    {0x61A    ,0x00},
    {0x61B    ,0x80},
    {0x61C    ,0x00},
    {0x61D    ,0x80},
    {0x61E    ,0x00},
    {0x61F    ,0x80},
    {0x620    ,0x00},
    {0x621    ,0x80},
    {0x622    ,0x00},
    {0x1C1    ,0x5B},
    {0x1C0    ,0x33},
};

int bsp_abb_tv300_init(u32 abb_version, u32 *is_supported);

void bsp_abb_tv300_init_later(u32 offset)
{
    u32 i = 0;
    u32 value = 0;

    bsp_abb_read(ABB_VERSION_ADDR + offset, &value);
    if ((offset) && (value != COMSTARTV300)) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "there may be only one ComStar TV300\n");
        return;
    }

    /* reset VREF*/
    bsp_abb_write(offset + 0x085, 0x80);
    udelay(1);
    bsp_abb_write(offset + 0x085, 0x00);
    bsp_abb_write(offset + 0x0E5, 0x80);
    udelay(1);
    bsp_abb_write(offset + 0x0E5, 0x00);

    /* start ABB calibration */
    bsp_abb_read(offset + 0x072, &value);
    value &= ~0x01;
    bsp_abb_write(offset + 0x072, value);
    bsp_abb_write(offset + 0x072, 0x0D);
    do {
        bsp_abb_read(offset + 0x07B, &value);
    } while (!(value & 0x20));

    bsp_abb_read(offset + 0x0D2, &value);
    value &= ~0x01;
    bsp_abb_write(offset + 0x0D2, value);
    bsp_abb_write(offset + 0x0D2, 0x0D);
    do {
        bsp_abb_read(offset + 0x0DB, &value);
    } while (!(value & 0x20));

    bsp_abb_read(offset + 0x0CB, &value);
    value &= ~(0x01 << 0x05U);
    bsp_abb_write(offset + 0x0CB, value);
    bsp_abb_read(offset + 0x06B, &value);
    value &= ~(0x01 << 0x05U);
    bsp_abb_write(offset + 0x06B, value);

    bsp_abb_read(offset + 0x07C, &value);
    bsp_abb_write(offset + 0x096, value);
    bsp_abb_write(offset + 0x0DC, value);
    bsp_abb_write(offset + 0x0F6, value);

    if (g_abb_pm_switch.drx_abb_gpll) {
        bsp_abb_write(offset + 0x0D0, 0x0B);
    }

    if (g_abb_pm_switch.drx_abb_scpll) {
        bsp_abb_read(offset + 0x604, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(offset + 0x604, value);
    }

    for (i = 0; i < sizeof(g_abb_cfg_tv300) / sizeof(g_abb_cfg_tv300[0]); i++)
        bsp_abb_write(offset + g_abb_cfg_tv300[i].addr, g_abb_cfg_tv300[i].value);
}

static struct abb_config g_abb_data_tv300[] =
{
    {0x611  ,0x00},
    {0x602  ,0x00},
    {0x19E  ,0x00},
    {0x1A4  ,0x00},
    {0x1B7  ,0x00},
    {0x612  ,0x00},
};

int bsp_abb_tv300_suspend(struct dpm_device *dev)
{
    u32 i = 0;

    for (i = 0; i < sizeof(g_abb_data_tv300) / sizeof(g_abb_data_tv300[0]); i++)
        bsp_abb_read(g_abb_data_tv300[i].addr, &g_abb_data_tv300[i].value);

    return 0;
}

int bsp_abb_tv300_resume(struct dpm_device *dev)
{
    u32 i = 0;

    bsp_abb_deassert_reset();

    bsp_abb_tv300_init(COMSTARTV300, NULL);

    for (i = 0; i < sizeof(g_abb_data_tv300) / sizeof(g_abb_data_tv300[0]); i++)
        bsp_abb_write(g_abb_data_tv300[i].addr, g_abb_data_tv300[i].value);

    return 0;
}

int bsp_abb_tv300_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv300_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv300_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return (int)PWRCTRL_COMM_ON;
}

static u32 bsp_abb_tv300_g_pll_vote = 0;
static u32 bsp_abb_tv300_sc_pll_vote = 0;
static void bsp_abb_tv300_g_pll_ctrl(u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_gpll)
        return;

    if (is_enable) {
        bsp_abb_write(0x0D0, 0x0B);

        do {
            bsp_abb_read(0x602, &value);
            value &= 0x01U << 0x01U;
        } while (value != (0x01U << 0x01U));
    } else {
        bsp_abb_write(0xD0, 0x0F);
    }
}

static void bsp_abb_tv300_sc_pll_ctrl(u32 is_enable)
{
    u32 value = 0;

    if (g_abb_pm_switch.drx_abb_scpll)
        return;

    if (is_enable) {
        bsp_abb_read(0x604, &value);
        value |= 0x01U << 0x00U;
        bsp_abb_write(0x604, value);

        do {
            bsp_abb_read(0x604, &value);
            value &= 0x01U << 0x04U;
        } while (value != (0x01U << 0x04U));
    } else {
        bsp_abb_read(0x604, &value);
        value &= ~(0x01U << 0x00U);
        bsp_abb_write(0x604, value);
    }
}

int bsp_abb_tv300_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv300_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_enable_stamp);

        if (!bsp_abb_tv300_g_pll_vote)
            bsp_abb_tv300_g_pll_ctrl(1);

        bsp_abb_tv300_g_pll_vote |= 0x01U << (u32)enModemId;

        writel(bsp_abb_tv300_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_lock_stamp);
    } else {
        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_enable_stamp);

        if (!bsp_abb_tv300_sc_pll_vote)
            bsp_abb_tv300_sc_pll_ctrl(1);

        bsp_abb_tv300_sc_pll_vote |= 0x01U << (u32)enCommMode;

        writel(bsp_abb_tv300_sc_pll_vote, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_lock_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv300_spin_lock, flags);

    return 0;
}
int bsp_abb_tv300_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&g_abb_tv300_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_tv300_g_pll_vote &= ~(0x01U << (u32)enModemId);

        if (!bsp_abb_tv300_g_pll_vote)
            bsp_abb_tv300_g_pll_ctrl(0);

        writel(bsp_abb_tv300_g_pll_vote, (u32)&g_abb_ops.abb_om->gpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->gpll_disable_stamp);
    } else {
        bsp_abb_tv300_sc_pll_vote &= ~(0x01U << (u32)enCommMode);

        if (!bsp_abb_tv300_sc_pll_vote)
            bsp_abb_tv300_sc_pll_ctrl(0);

        writel(bsp_abb_tv300_sc_pll_vote, (u32)&g_abb_ops.abb_om->scpll_vote);

        writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->scpll_disable_stamp);
    }

    spin_unlock_irqrestore(&g_abb_tv300_spin_lock, flags);

    return 0;
}
int bsp_abb_tv300_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    u32 value = 0;
    unsigned long flags = 0;
    int ret = (int)PWRCTRL_COMM_ON;

    spin_lock_irqsave(&g_abb_tv300_spin_lock, flags);

    if ((enCommMode == PWC_COMM_MODE_GSM) || (enCommMode == PWC_COMM_MODE_REMOTE_CLK_G)) {
        bsp_abb_read(0xD0, &value);
        ret = value & (0x01U << 0x02U) ? (int)PWRCTRL_COMM_OFF : (int)PWRCTRL_COMM_ON;
    } else {
        bsp_abb_read(0x604, &value);
        ret = value & (0x01U << 0x00U) ? (int)PWRCTRL_COMM_ON : (int)PWRCTRL_COMM_OFF;
    }

    spin_unlock_irqrestore(&g_abb_tv300_spin_lock, flags);

    return ret;
}

int bsp_abb_tv300_init(u32 abb_version, u32 *is_supported)
{
    if (COMSTARTV300 != abb_version)
        return 0;

    if (is_supported)
        *is_supported = 1;

    bsp_abb_tv300_init_later(0);
    bsp_abb_tv300_init_later(0x800);

    if (!g_abb_inited) {
        spin_lock_init(&g_abb_tv300_spin_lock);
        g_abb_ops.abb_suspend       = bsp_abb_tv300_suspend;
        g_abb_ops.abb_resume        = bsp_abb_tv300_resume;
        g_abb_ops.abb_power_up      = bsp_abb_tv300_power_up;
        g_abb_ops.abb_power_down    = bsp_abb_tv300_power_down;
        g_abb_ops.abb_power_status  = bsp_abb_tv300_power_status;
        g_abb_ops.abb_pll_enable    = bsp_abb_tv300_pll_enable;
        g_abb_ops.abb_pll_disable   = bsp_abb_tv300_pll_disable;
        g_abb_ops.abb_pll_status    = bsp_abb_tv300_pll_status;
    }

    return 0;
}

#else

int bsp_abb_tv300_init(u32 abb_version, u32 *is_supported)
{
    return 0;
}

#endif

