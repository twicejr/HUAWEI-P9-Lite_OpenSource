/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tcxo_balong.c
  版 本 号   : 初稿
  作    者   : 徐经翠x00221564
  生成日期   : 2013年8月26日
  最近修改   :
  功能描述   : tcxo_balong.c头文件
  函数列表   :
  修改历史   :
  1.日    期   :  徐经翠x00221564
    作    者   : 2013年8月26日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TCXO_BALONG_H__
#define __TCXO_BALONG_H__

#include <mdrv_pm.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <osl_irq.h>
#include <bsp_hardtimer.h>
#include <bsp_softtimer.h>
#include <hi_pwrctrl_interface.h>
#include <product_config.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_memmap.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PWC_TCXO_INITED 1
#define PWC_TCXO_UNINITED 0

#define TCXO_STABLE_TIME 0x5            /*150us*/
#define TCXO_STABLE_TIME_SCLICE_NUM 5   /*150us*/

/*计算对应的msk值*/
#define CALC_REG_MSK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum tagPWC_TCXO_CFG_E
{
    PWC_TCXO_CFG_DCARD_SFUNC_SEL_0,  /*V7R2 bit 00配置*/ /*双卡单待,channel 0使用tcxo0，channel 1使用tcxo0*/
    PWC_TCXO_CFG_DCARD_DFUNC_SEL_1,                               /*双卡双待,channel 0使用tcxo1，channel 1使用tcxo0*/
    PWC_TCXO_CFG_DCARD_DFUNC_SEL_0,  /*V7R2 bit 10配置*/ /*双卡双待,channel 0使用tcxo0，channel 1使用tcxo1*/
    PWC_TCXO_CFG_DCARD_SFUNC_SEL_1,                               /*双卡单待,channel 0使用tcxo1，channel 1使用tcxo1*/
    PWC_TCXO_CFG_SCARD_SFUNC_SEL_0,                               /*单卡单待,channel 0使用tcxo0，channel 1使用tcxo0*/
    PWC_TCXO_CFG_SCARD_SFUNC_SEL_1,                               /*单卡单待,channel 0使用tcxo1，channel 1使用tcxo1*/
    PWC_TCXO_CFG_BUTT
}PWC_TCXO_CFG_E;

typedef enum tagPWC_TCXO_TIMER_STATUS_E
{
    PWC_TCXO_TIMER_RUNNING,
    PWC_TCXO_TIMER_STOP,
    PWC_TCXO_TIMER_BUTT
}PWC_TCXO_TIMER_STATUS_E;

typedef enum tagPWC_TCXO_ID_E
{
    PWC_TCXO_ID_0,
    PWC_TCXO_ID_1,
    PWC_TCXO_ID_BUTT
}PWC_TCXO_ID_E;

typedef enum tagPWC_PMU_TCXO_EN
{
    RFIC1_ID_0,
    TCXO1_ID_1,
    TCXO_ID_BUTT
}PMU_TCXO_EN;

/*****************************************************************************
  STRUCT定义
*****************************************************************************/
struct tcxo_timer_callback{
    PWC_TCXO_FUNCPTR  routine;             /* timer超时回调函数 */
    BSP_S32                   arg;                   /* timer超时回调参数 */
    BSP_U32                   timerValue;        /* 计数值 ms*/
};

/*
*TCXO信息结构体
*g_stTcxoTimerStru:该TCXO的timer回调信息
*timer:软timer信息
*timer_status:软timer的运行状态
*tcxo_status:该TCXO的状态
*/
struct tcxo_info{
    struct tcxo_timer_callback        g_stTcxoTimerStru[ PWC_COMM_MODE_BUTT];
    PWC_TCXO_TIMER_STATUS_E    timer_status;
    int                                         tcxo_status;
};

/*TCXO初始化配置*/
int tcxo_init_configure(void);

/*tcxo debug*/
void debug_tcxo_function(PWC_COMM_MODEM_E  tcxoId, PWC_COMM_MODE_E enModeType);
void debug_tcxo(void);
void debug_pastar_dpm(void);

/***************************************************************************
 函 数 名  : bsp_pmu_tcxo1_en_enable
 功能描述  :使能PMU TCXO1 EN
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
void bsp_pmu_tcxo1_en_enable(PMU_TCXO_EN bit_value);

/***************************************************************************
 函 数 名  : bsp_pmu_tcxo1_en_disable
 功能描述  :去使能PMU TCXO1 EN
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
void bsp_pmu_tcxo1_en_disable(PMU_TCXO_EN bit_value);

#if defined(CONFIG_K3V3_CLK_CRG)
void bsp_tcxo1_set_flag(unsigned int flag);
void bsp_tcxo1_enable_first(void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of tcxo_balong.h */

