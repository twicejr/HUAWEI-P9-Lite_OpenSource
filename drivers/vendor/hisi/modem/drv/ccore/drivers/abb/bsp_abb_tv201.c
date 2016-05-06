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

/*lint --e{522,534,537,551} */
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_malloc.h>
#include <osl_spinlock.h>

#include <mdrv_pm.h>

#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_dpm.h>
#include <bsp_abb.h>
#include <bsp_hardtimer.h>


#if defined(ABB_BUILD_ALL) || defined(ABB_BUILD_TV201)

void* g_abb_ctu_base_addr = NULL;
static spinlock_t g_abb_tv201_spin_lock;

static struct abb_config g_abb_cfg_tv201[] =
{
    {0x08A    ,0x00},
    {0x100    ,0x40},
    {0x180    ,0x18},
    {0x182    ,0x10},
    {0x201    ,0x03},
    {0x401    ,0x03},
    {0x601    ,0x03},
    {0x206    ,0x2C},
    {0x406    ,0x2C},
    {0x606    ,0x2C},
    {0x218    ,0xCF},
    {0x418    ,0xCF},
    {0x618    ,0xCF},
    {0x219    ,0x03},
    {0x419    ,0x03},
    {0x619    ,0x03},
    {0x21F    ,0x03},
    {0x41F    ,0x03},
    {0x61F    ,0x03},
    {0x24B    ,0x04},
    {0x44B    ,0x04},
    {0x64B    ,0x04},
    {0x303    ,0x40},
    {0x503    ,0x40},
    {0x703    ,0x40},
    {0x304    ,0x0C},
    {0x504    ,0x0C},
    {0x704    ,0x0C},
    {0x305    ,0x80},
    {0x505    ,0x80},
    {0x705    ,0x80},
    {0x306    ,0x0F},
    {0x506    ,0x0F},
    {0x706    ,0x0F},
    {0x309   ,0x03},
    {0x509   ,0x03},
    {0x709   ,0x03},
    {0x30A   ,0x17},
    {0x50A   ,0x17},
    {0x70A   ,0x17},
    {0x313   ,0x40},
    {0x513   ,0x40},
    {0x713   ,0x40},
    {0x315   ,0x80},
    {0x515   ,0x80},
    {0x715   ,0x80},
    {0x316   ,0x0F},
    {0x516   ,0x0F},
    {0x716   ,0x0F},
    {0x319   ,0x03},
    {0x519   ,0x03},
    {0x719   ,0x03},
    {0x31A   ,0x17},
    {0x51A   ,0x17},
    {0x71A   ,0x17},
    {0x321   ,0x54},
    {0x521   ,0x54},
    {0x721   ,0x54},
    {0x323   ,0x00},
    {0x523   ,0x00},
    {0x723   ,0x00},
    {0x324   ,0x0C},
    {0x524   ,0x0C},
    {0x724   ,0x0C},
    {0x326   ,0x91},
    {0x526   ,0x91},
    {0x726   ,0x91},
    {0x329   ,0x43},
    {0x529   ,0x43},
    {0x729   ,0x43},
    {0x32A   ,0x14},
    {0x52A   ,0x14},
    {0x72A   ,0x14},
    {0x333   ,0x40},
    {0x533   ,0x40},
    {0x733   ,0x40},
    {0x334   ,0x0C},
    {0x534   ,0x0C},
    {0x734   ,0x0C},
    {0x336   ,0x0F},
    {0x536   ,0x0F},
    {0x736   ,0x0F},
    {0x339   ,0x03},
    {0x539   ,0x03},
    {0x739   ,0x03},
    {0x33A   ,0x17},
    {0x53A   ,0x17},
    {0x73A   ,0x17},
    {0x343   ,0x40},
    {0x543   ,0x40},
    {0x743   ,0x40},
    {0x344   ,0x0C},
    {0x544   ,0x0C},
    {0x744   ,0x0C},
    {0x346   ,0x0F},
    {0x546   ,0x0F},
    {0x746   ,0x0F},
    {0x349   ,0x03},
    {0x549   ,0x03},
    {0x749   ,0x03},
    {0x34A   ,0x17},
    {0x54A   ,0x17},
    {0x74A   ,0x17},
    {0x202   ,0x01},
    {0x402   ,0x01},
    {0x602   ,0x01},
    {0x208   ,0x01},
    {0x408   ,0x01},
    {0x608   ,0x01},
    {0x21A   ,0x09},
    {0x41A   ,0x09},
    {0x61A   ,0x09},
    {0x220   ,0x01},
    {0x420   ,0x01},
    {0x620   ,0x01},
    {0x325   ,0x80},
    {0x525   ,0x80},
    {0x725   ,0x80},
    {0x335   ,0x80},
    {0x535   ,0x80},
    {0x735   ,0x80},
    {0x355   ,0x80},
    {0x555   ,0x80},
    {0x755   ,0x80},
    {0x215   ,0x20},
    {0x415   ,0x20},
    {0x615   ,0x20},
    {0x008   ,0x04},
    {0x101   ,0x44},
    {0x36A   ,0x17},
    {0x56A   ,0x17},
    {0x76A   ,0x17},
    {0x372   ,0x8D},
    {0x572   ,0x8D},
    {0x772   ,0x8D},
};

int bsp_abb_tv201_init(u32 abb_version, u32 *is_supported);

static int bsp_ctu_write(u32 addr, u32 value)
{
    writel(value, (u32)g_abb_ctu_base_addr + addr);
    return 0;
}

void bsp_abb_tv201_tcxo_init(void)
{
}

void bsp_abb_tv201_init_rxadc_op1_offset(u32 offset)
{
    if (0 == offset) {
        bsp_ctu_write(0x1214, 0x07);
        bsp_ctu_write(0x1244, 0x07);
    } else {
        bsp_ctu_write(0x1274, 0x07);
        bsp_ctu_write(0x12A4, 0x07);
    }
    bsp_abb_write(0x370 + offset, 0x22);
    bsp_abb_write(0x371 + offset, 0x10);
    bsp_abb_write(0x570 + offset, 0x22);
    bsp_abb_write(0x571 + offset, 0x10);
    if (0 == offset) {
        bsp_ctu_write(0x1214, 0x37);
        bsp_ctu_write(0x1244, 0x37);
    } else {
        bsp_ctu_write(0x1274, 0x37);
        bsp_ctu_write(0x12A4, 0x37);
    }
    bsp_abb_write(0x372 + offset, 0x9B);
    bsp_abb_write(0x372 + offset, 0x9F);
    bsp_abb_write(0x572 + offset, 0x9B);
    bsp_abb_write(0x572 + offset, 0x9F);

    udelay(15);

    if (0 == offset) {
        bsp_ctu_write(0x1214, 0x07);
        bsp_ctu_write(0x1244, 0x07);
    } else {
        bsp_ctu_write(0x1274, 0x07);
        bsp_ctu_write(0x12A4, 0x07);
    }
    bsp_abb_write(0x372 + offset, 0x8D);
    bsp_abb_write(0x572 + offset, 0x8D);
    bsp_abb_write(0x370 + offset, 0x20);
    bsp_abb_write(0x371 + offset, 0x00);
    bsp_abb_write(0x570 + offset, 0x20);
    bsp_abb_write(0x571 + offset, 0x00);
    if (0 == offset) {
        bsp_ctu_write(0x1214, 0x00);
        bsp_ctu_write(0x1244, 0x00);
    } else {
        bsp_ctu_write(0x1274, 0x00);
        bsp_ctu_write(0x12A4, 0x00);
    }
}

void bsp_abb_tv201_init_later(u32 offset)
{
    u32 i = 0;
    u32 value = 0;

    bsp_abb_read(ABB_VERSION_ADDR + offset, &value);
    if ((offset) && (value != COMSTARTV201)) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "there may be only one ComStar TV201\n");
        return;
    }

    bsp_abb_tv201_tcxo_init();

    /* reset VREF*/
    bsp_abb_write(0x08C + offset, 0x02);
    udelay(1);
    bsp_abb_write(0x08C + offset, 0x00);

    /* start ABB calibration */
    bsp_abb_write(0x08C + offset, 0x00);
    bsp_abb_write(0x08C + offset, 0x01);
    do {
        bsp_abb_read(0x09E + offset, &value);
    }while (!(value & 0x10));

    bsp_abb_read(0x09F + offset, &value);
    bsp_abb_write(0x386 + offset, value);
    bsp_abb_write(0x586 + offset, value);
    bsp_abb_write(0x786 + offset, value);

    for (i = 0; i < sizeof(g_abb_cfg_tv201) / sizeof(g_abb_cfg_tv201[0]); i++)
        bsp_abb_write(g_abb_cfg_tv201[i].addr + offset, g_abb_cfg_tv201[i].value);

    /*  rxadc_op1_offset  */
    bsp_abb_tv201_init_rxadc_op1_offset(offset);

    //open scpll and gpll
    bsp_abb_write(0x089 + offset, 0x06);
    bsp_abb_write(0x0A5 + offset, 0x15);
}

int bsp_abb_tv201_suspend(struct dpm_device *dev)
{
    return 0;
}

int bsp_abb_tv201_resume(struct dpm_device *dev)
{
    return bsp_abb_tv201_init(COMSTARTV201, NULL);
}

int bsp_abb_tv201_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv201_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
int bsp_abb_tv201_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return (int)PWRCTRL_COMM_ON;
}

int bsp_abb_tv201_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int bsp_abb_tv201_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int bsp_abb_tv201_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return (int)PWRCTRL_COMM_ON;
}

int bsp_abb_tv201_init(u32 abb_version, u32 *is_supported)
{
    if (COMSTARTV201 != abb_version)
        return 0;

    if (is_supported)
        *is_supported = 1;

    g_abb_ctu_base_addr = bsp_bbp_part_addr_get(BBP_CTU);
    if (!g_abb_ctu_base_addr) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "fail to get abb ctu base address\n");
        return -1;
    }

    bsp_abb_tv201_init_later(0);
    bsp_abb_tv201_init_later(0x800);

    if (!g_abb_inited) {
        spin_lock_init(&g_abb_tv201_spin_lock);
        g_abb_ops.abb_suspend       = bsp_abb_tv201_suspend;
        g_abb_ops.abb_resume        = bsp_abb_tv201_resume;
        g_abb_ops.abb_power_up      = bsp_abb_tv201_power_up;
        g_abb_ops.abb_power_down    = bsp_abb_tv201_power_down;
        g_abb_ops.abb_power_status  = bsp_abb_tv201_power_status;
        g_abb_ops.abb_pll_enable    = bsp_abb_tv201_pll_enable;
        g_abb_ops.abb_pll_disable   = bsp_abb_tv201_pll_disable;
        g_abb_ops.abb_pll_status    = bsp_abb_tv201_pll_status;
    }

    return 0;
}

#else

int bsp_abb_tv201_init(u32 abb_version, u32 *is_supported)
{
    return 0;
}

#endif

