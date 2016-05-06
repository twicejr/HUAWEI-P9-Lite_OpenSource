/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  rf_power.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  用于管理射频器件供电
*
*   修改记录 :  2015年3月23日  v1.00  zuofenghua  创建
*
*************************************************************************/

#ifndef __RF_POWER_H__
#define __RF_POWER_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif            /* __cplusplus */

#include <product_config.h>
#include <osl_spinlock.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <bsp_rf_balong.h>

#define PA_PWR_NUM  2 /*每个pa两路电源*/
#define RF_PWR_NUM  4 /*每个RF两路电源*/
#define FEM_PWR_NUM 1 /*每组fem 1 路电源*/
#define RF_CLK_NUM  2 /*pmu给rfclk buffer提供的时钟*/

#define RF_PWR_SEM_FULL   1/*信号量初始化*/
#define RF_PWR_SEM_EMPUTY 0

#define RF_PWR_MODE_NUM  6
#define RF_PWR_MODEM_NUM PWC_COMM_MODEM_BUTT
#define RF_PWR_CHN_NUM   PWC_COMM_CHANNEL_BUTT

#define NV_PWC_ALLWAYS_ON 1

/*****************类型定义begin*********************/
/*供电器件枚举*/
typedef enum PWR_CONSUMER{
    RF_VIO = 0,    /*[00] 1.8v初始化打开，suspend close,resume open*/
    RFIC0_ANALOG0, /*[01] 1.29v*/
    RFIC0_ANALOG1, /*[02] 1.85v,*/
    RFIC0_ANALOG2, /*[03] 2.4v 状态机控制*/
    RFIC0_DIGITAL, /*[04] 底软不操作,all ways on*/
    RFIC1_ANALOG0, /*[05] k3v5空，v7r5 LDO22, 1.29v*/
    RFIC1_ANALOG1, /*[06] 1.85v,*/
    RFIC1_ANALOG2, /*[07] 2.4v 状态机控制*/
    RFIC1_DIGITAL, /*[08] 底软不操作,all ways on*/
    RFIC2_ANALOG0, /*[09]1.29v*/
    RFIC2_ANALOG1, /*[10]1.85v,*/
    RFIC2_ANALOG2, /*[11]2.4v 状态机控制*/
    RFIC2_DIGITAL, /*[12]底软不操作,all ways on*/
    TULPA0_VBIAS,  /*[13]vbat 软件不控,LDO23,状态机; etmodulator mipi接口与vcc一致*/
    TULPA0_VCC,    /*[14]vbat 软件不控,dcdc gpio (chip back),etmodulator mipi接口与dsp确认*/
    TULPA1_VBIAS,  /*[15]austin不用，v7r5与TUL PA0一致,ldo23?遗留*/
    TULPA1_VCC,    /*[16]austin不用，v7r5与TUL PA0一致*/
    TULPA2_VBIAS,  /*[17]vbat*/
    TULPA2_VCC,    /*[18]vbat*/
    GPA0_VBIAS,    /*[19]vbat*/
    GPA0_VCC,      /*[20]vbat (CHIPBACK),外置DCDC*/
    GPA1_VBIAS,    /*[21]vbat*/
    GPA1_VCC,      /*[22]vbat(CHIPBACK),外置DCDC*/
    GPA2_VBIAS,    /*[23]vbat*/
    GPA2_VCC,      /*[24]vbat(CHIPBACK),外置DCDC*/
    FEM_VCC,       /*[25]LDO14,双modem关机关闭，不需要考虑外置modem*/   
    PWR_CONSUMER_NUM,/*[26]*/
}RFFE_POWER_ID_E;

/*debug info*/
struct onoff_detail{
    u64 vote;
    u32 hw_stat;
    unsigned int on_cnt[PWC_COMM_MODE_BUTT];
    unsigned int off_cnt[PWC_COMM_MODE_BUTT];
    unsigned int on_stamp[PWC_COMM_MODE_BUTT];
    unsigned int off_stamp[PWC_COMM_MODE_BUTT];
    unsigned int true_on_cnt[PWC_COMM_MODE_BUTT];
    unsigned int true_off_cnt[PWC_COMM_MODE_BUTT];
    unsigned int true_on_stamp[PWC_COMM_MODE_BUTT];
    unsigned int true_off_stamp[PWC_COMM_MODE_BUTT];
};

/*enum debug info*/
typedef enum pwr_dbg{
    PWR_RFIC = 0,
    PWR_FEM,
    PWR_PA,
    CLK_RFIC,
    PWR_DBG_NUM
}PWR_DBG_E;

/*debug info*/
struct rf_pwr_clk_debug{
    struct onoff_detail info[PWC_COMM_CHANNEL_BUTT];
};
/*dts配置表信息*/
struct pwr_base_info {
    const char * name;       /*regulator node name*/
    unsigned int pwr_id;
    unsigned int init_on;    /*init power on*/
    unsigned int dpm_off;    /*dpm power off*/
    unsigned int disable_off;/*power off interface disable*/
    osl_sem_id   sem;

    u64          vote;
    unsigned int voltage;
    unsigned int valid;
    struct regulator *regu;
};

/*rf clk info*/
struct clk_base_info{
    osl_sem_id  sem;
    u64         vote;
};

struct pmu_apt_info{
    u32 enable_cnt;
    u32 disable_cnt;
    u32 *enable_reg;
    u32 *enable_val;
    u32 *disable_reg;
    u32 *disable_val;
    spinlock_t       lock;
};
/*apt info*/
struct pmu_apt_cfg{
    u32 pmu_base;
    u32 chn_cnt;
    struct pmu_apt_info *info;
};
#ifdef CONFIG_RFFE_POWER
/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件设置电压
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_rfpower_set_voltage( EX_RFFE_POWER_ID_E consumer_id, u32 voltage_mv , PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件查询电压
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_rfpower_get_voltage( EX_RFFE_POWER_ID_E consumer_id, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_pa_power_on
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
/*****************************************************************************
* 函 数    : balong_pa_power_off
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA供电各模投票状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA供电物理状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfic_power_on
* 功 能    : rfic上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfic_power_off
* 功 能    : rfic下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根据chn号确定
*****************************************************************************/
int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfic_power_status
* 功 能    : rfic供电投票状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfic_power_status
* 功 能    : rfic供电物理状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_fem_power_on
* 功 能    : fem上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_fem_power_off
* 功 能    : fem下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_fem_power_hw_status
* 功 能    : fem供电状态查询，物理状态
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_fem_power_status
* 功 能    : fem供电状态查询，投票状态
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rf_power_resume
* 功 能    : 低或耗恢复时，把需要打开的电源上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_resume(void);

/*****************************************************************************
* 函 数    : balong_rf_power_suspend
* 功 能    : 低或耗睡眠前，把需要关闭的电源下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_suspend(void);

/*****************************************************************************
* 函 数    : bsp_rf_power_init
* 功 能    : 射频供电初始化
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_init(void);

/*****************************************************************************
* 函 数    : balong_rfclk_enable
* 功 能    : 打开pmu给rfclk提供的时钟 
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

/*****************************************************************************
* 函 数    : balong_rfclk_disable
* 功 能    : 关闭pmu给rfclk提供的时钟 
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
/*****************************************************************************
* 函 数    : balong_rfclk_hw_status
* 功 能    : 查询pmu给rfclk提供的时钟状态
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

int balong_rfpower_apt_enable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);
int balong_rfpower_apt_disable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);
int balong_rfpower_get_apt_status(PWC_COMM_CHANNEL_E chn);

#else
/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件设置电压
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    : z00228752
* 说 明    : pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_rfpower_set_voltage( EX_RFFE_POWER_ID_E consumer_id, u32 voltage_mv, PWC_COMM_CHANNEL_E chn )
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件查询电压
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_rfpower_get_voltage( EX_RFFE_POWER_ID_E consumer_id, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_pa_power_on
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


/*****************************************************************************
* 函 数    : balong_pa_power_off
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA供电物理状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
static inline int balong_pa_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}
/*****************************************************************************
* 函 数    : balong_rfic_power_on
* 功 能    : rfic上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
static inline int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_off
* 功 能    : rfic下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根据chn号确定
*****************************************************************************/
static inline int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_status
* 功 能    : rfic上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
static inline int balong_rfic_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_status
* 功 能    : rfic供电物理状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
static inline int balong_rfic_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}
/*****************************************************************************
* 函 数    : balong_fem_power_on
* 功 能    : fem上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
static inline int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_fem_power_off
* 功 能    : fem下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
static inline int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_fem_power_status
* 功 能    : fem下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
static inline int balong_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}

/*****************************************************************************
* 函 数    : balong_fem_power_hw_status
* 功 能    : fem供电状态查询，物理状态
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
static inline int balong_fem_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}

/*****************************************************************************
* 函 数    : balong_vio_power_off
* 功 能    : 低或耗恢复时，把需要打开的电源上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
static inline int balong_rf_power_resume(void)
{
    return RFFE_OK;
}
/*****************************************************************************
* 函 数    : balong_vio_power_off
* 功 能    : 低或耗睡眠前，把需要关闭的电源下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
static inline int balong_rf_power_suspend(void)
{
    return RFFE_OK;
}

/*debug*/

/*****************************************************************************
* 函 数    : balong_rf_power_init
* 功 能    : 射频供电初始化
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
static inline int balong_rf_power_init(void)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfclk_enable
* 功 能    : 打开pmu给rfclk提供的时钟 
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
static inline int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

/*****************************************************************************
* 函 数    : balong_rfclk_disable
* 功 能    : 关闭pmu给rfclk提供的时钟 
* 输 入    : 无
* 输 出    : 无
* 返 回    : 
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
static inline int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

/*****************************************************************************
* 函 数    : balong_rfclk_hw_status
* 功 能    : 查询pmu给rfclk提供的时钟状态
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : clk的编号根chn号确定
*****************************************************************************/
static inline int balong_rfclk_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}

static inline int balong_rfpower_apt_enable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

static inline int balong_rfpower_apt_disable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

static inline int balong_rfpower_get_apt_status(PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

#endif


/*****************类型定义over*********************/

#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */

