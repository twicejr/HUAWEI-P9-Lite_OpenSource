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
#include <of.h>

#include "securec.h"

#include <osl_bio.h>
#include <osl_types.h>

#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_pm_om.h>
#include <bsp_rsracc.h>
#include <bsp_sysctrl.h>
#include <bsp_hardtimer.h>

#include <bsp_abb.h>


struct abb_ops g_abb_ops;
struct abb_om_info g_abb_om_info;

NV_ABB_INIT_CFG g_abb_init_cfg;
ST_PWC_SWITCH_STRU g_abb_pm_switch;

u32 g_abb_inited = 0;
void* g_abb_base_addr = NULL;

int bsp_abb_read(u32 addr, u32 *value)
{
    *value = readl((u32)g_abb_base_addr + (addr << 2));
    return 0;
}

int bsp_abb_write(u32 addr, u32 value)
{
    writel(value, (u32)g_abb_base_addr + (addr << 2));
    return 0;
}

#ifdef CONFIG_CCORE_PM
static struct dpm_device g_abb_dpm_device={
    .device_name = "abb_dpm",
    .prepare = NULL,
    .suspend_early= bsp_abb_suspend,
    .suspend = NULL,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume = NULL,
    .resume_late = bsp_abb_resume,
    .complete = NULL,
};
#endif

s32 bsp_abb_rsracc_suspend_begin(rsr_acc_description *bd_descri)
{
    return (s32)bsp_abb_suspend(NULL);
}

void bsp_abb_rsracc_resume_end(rsr_acc_description *bd_descri)
{
    (void)bsp_abb_resume(NULL);
}

static struct rsracc_cb_s g_abb_rsracc_ops =
{
    .suspend_begin  = bsp_abb_rsracc_suspend_begin,
    .suspend_end    = NULL,
    .resume_begin   = NULL,
    .resume_end     = bsp_abb_rsracc_resume_end,
};

static struct bd_desc_s g_abb_rsracc_device =
{
    .level = rsracc_bd_level_1,
    .name = "abb_rsracc",
    .ops = &g_abb_rsracc_ops,
    .only_ops_in_bd = true,
};


void bsp_abb_deassert_reset(void)
{
    struct device_node *dev = NULL;
    const char *name = "hisilicon,abb_balong_mdm_for_sysc";
    static u32 addr = 0;
    static u32 offset = 0;

    if (!g_abb_inited) {
        dev = of_find_compatible_node(NULL, NULL, name);
        if(NULL == dev) {
             bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB device node not found\n");
             return;
        }
        of_property_read_u32_index(dev, "abb_srst_dis", 0, &addr);
        of_property_read_u32_index(dev, "abb_srst_dis", 1, &offset);

        if (addr)
            addr = (u32)bsp_sysctrl_addr_get((void *)addr);
    }

    if (addr)
        writel(0x01U << offset, addr);
}

void bsp_abb_init(void)
{
    int ret = 0;

    u32 abb_version = 0;
    u32 is_supported = 0;

    bsp_abb_deassert_reset();

    if (!g_abb_inited) {
        g_abb_base_addr = bsp_bbp_part_addr_get(BBP_ABB);

        ret = (int)bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8*)&g_abb_pm_switch, sizeof(g_abb_pm_switch));
        if (ret) {
            (void)memset_s((void *)&g_abb_pm_switch, sizeof(g_abb_pm_switch), 0, sizeof(g_abb_pm_switch));
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB read nv fail, ret = %d\n", ret);
        }
    }

    if (!g_abb_base_addr) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "fail to get abb base address\n");
        return;
    }

    (void)bsp_abb_read(ABB_VERSION_ADDR, &abb_version);

extern int bsp_abb_tv201_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv201_init(abb_version, &is_supported);

extern int bsp_abb_tv210_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv210_init(abb_version, &is_supported);

extern int bsp_abb_tv220_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv220_init(abb_version, &is_supported);

extern int bsp_abb_tv230_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv230_init(abb_version, &is_supported);

extern int bsp_abb_tv260_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv260_init(abb_version, &is_supported);

extern int bsp_abb_tv300_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv300_init(abb_version, &is_supported);

extern int bsp_abb_tv310_init(u32 abb_version, u32 *is_supported);
    ret |= bsp_abb_tv310_init(abb_version, &is_supported);

    if (bsp_rsracc_support()) {
        ret |= bsp_rsracc_register(&g_abb_rsracc_device, 1);
    } else {
#ifdef CONFIG_CCORE_PM
        if (!g_abb_inited) {
            ret |= bsp_device_pm_add(&g_abb_dpm_device);
            if (ret) {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "fail to add abb dpm device\r\n");
                return;
            }
        }
#endif
    }

    if (ret) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");
        return;
    }

    if (!is_supported) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "don't support this ABB version: 0x%x\n", abb_version);
        return;
    }

    if (!g_abb_inited) {
        g_abb_inited = 1;
        g_abb_ops.abb_om = (struct abb_om_info*)bsp_pm_dump_get(PM_OM_ABB, sizeof(struct abb_om_info));
        if (!g_abb_ops.abb_om)
            g_abb_ops.abb_om = &g_abb_om_info;

        (void)memset_s((void *)(g_abb_ops.abb_om), sizeof(struct abb_om_info), 0, sizeof(struct abb_om_info));

        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init ok, version: 0x%x\n", abb_version);
    }
}

int bsp_abb_suspend(struct dpm_device *dev)
{
    int ret = 0;

    writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->suspend_start_stamp);

    if (g_abb_inited)
        ret = g_abb_ops.abb_suspend(dev);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->suspend_end_stamp);

    return ret;
}

int bsp_abb_resume(struct dpm_device *dev)
{
    int ret = 0;

    writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->resume_start_stamp);

    if (g_abb_inited)
        ret = g_abb_ops.abb_resume(dev);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    writel(bsp_get_slice_value(), (u32)&g_abb_ops.abb_om->resume_end_stamp);

    return ret;
}

int bsp_abb_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_power_up(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

int bsp_abb_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_power_down(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

int bsp_abb_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_power_status(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

int bsp_abb_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_pll_enable(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

int bsp_abb_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_pll_disable(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

int bsp_abb_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    if (g_abb_inited)
        ret = g_abb_ops.abb_pll_status(enCommMode, enModemId, enChannel);
    else
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ABB, "ABB init fail\n");

    return ret;
}

