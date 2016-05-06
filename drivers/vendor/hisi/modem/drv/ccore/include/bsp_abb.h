/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_abb.h
*
*   作    者 :  z00227143
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
#ifndef __BSP_ABB_H__
#define __BSP_ABB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <product_config.h>
#include <osl_types.h>
#include <mdrv_pm.h>
#include <bsp_dpm.h>
#include <hi_abb.h>

#include <bsp_nvim.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>


/* only this version is supported */
#define COMSTARV500 (0xA0)
#define COMSTARV510 (0xA4)
#define COMSTARV511 (0xA5)
#define COMSTARV530 (0xAC)
#define COMSTARV532 (0xAE)
#define COMSTARV550 (0xB4)
#define COMSTARTV201 (0x08)
#define COMSTARTV210 (0x0C)
#define COMSTARTV220 (0x10)
#define COMSTARTV230 (0x1C)
#define COMSTARTV260 (0x18)
#define COMSTARTV300 (0x14)
#define COMSTARTV310 (0x16)


#define V7R2_ABB_VERSION    COMSTARV530
#define V711_ABB_VERSION    COMSTARV532
#define K3V3_ABB_VERSION    COMSTARV550
#define K3V5_ABB_VERSION    COMSTARTV210
#define V7R5_ABB_VERSION    COMSTARTV220
#define V8R5_ABB_VERSION    COMSTARTV230
#define V722_ABB_VERSION    COMSTARTV310


struct abb_config
{
    u32 addr;
    u32 value;
};

struct abb_om_info {
    u32 suspend_start_stamp;
    u32 suspend_end_stamp;
    u32 resume_start_stamp;
    u32 resume_end_stamp;
    u32 gpll_vote;
    u32 gpll_enable_stamp;
    u32 gpll_lock_stamp;
    u32 gpll_disable_stamp;
    u32 scpll_vote;
    u32 scpll_enable_stamp;
    u32 scpll_lock_stamp;
    u32 scpll_disable_stamp;
};

struct abb_ops {
    int (*abb_suspend)(struct dpm_device *dev);
    int (*abb_resume)(struct dpm_device *dev);
    int (*abb_power_up)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    int (*abb_power_down)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    int (*abb_power_status)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    int (*abb_pll_enable)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    int (*abb_pll_disable)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    int (*abb_pll_status)(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
    struct abb_om_info *abb_om;
};


#ifdef CONFIG_ABB
extern u32 g_abb_inited;
extern struct abb_ops g_abb_ops;
extern NV_ABB_INIT_CFG g_abb_init_cfg;
extern ST_PWC_SWITCH_STRU g_abb_pm_switch;

void bsp_abb_init(void);
int bsp_abb_read(u32 addr, u32 *value);
int bsp_abb_write(u32 addr, u32 value);

void bsp_abb_deassert_reset(void);

int bsp_abb_suspend(struct dpm_device *dev);
int bsp_abb_resume(struct dpm_device *dev);

int bsp_abb_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_abb_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_abb_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

int bsp_abb_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_abb_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_abb_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

#else
static inline void bsp_abb_init(void)
{
    return;
}

static inline int bsp_abb_read(u32 addr, u32 *value)
{
    return 0;
}
static inline int bsp_abb_write(u32 addr, u32 value)
{
    return 0;
}

static inline int bsp_abb_suspend(struct dpm_device *dev)
{
    return 0;
}
static inline int bsp_abb_resume(struct dpm_device *dev)
{
    return 0;
}

static inline int bsp_abb_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
static inline int bsp_abb_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return MDRV_OK;
}
static inline int bsp_abb_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
     return (int)PWRCTRL_COMM_ON;
}

static inline int bsp_abb_pll_enable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
static inline int bsp_abb_pll_disable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
static inline int bsp_abb_pll_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return (int)PWRCTRL_COMM_ON;
}

#endif


#ifdef __cplusplus
}
#endif

#endif

