/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_dft.c
  版 本 号   : 初稿
  作    者   : z00237171
  生成日期   : 2014年8月13日
  最近修改   :
  功能描述   : 维测功能相关定义和实现
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "oam_ext_if.h"
#include "hal_ext_if.h"
#include "hal_witp_pa_reg.h"
#include "hal_witp_phy_reg.h"
#include "mac_resource.h"
#include "dmac_dft.h"
#include "dmac_ext_if.h"
#include "hal_hi1102_phy_reg.h"
#include "hal_hi1102_mac_reg.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "oal_mem.h"
#include "frw_event_main.h"
#include "pm_extern.h"
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#endif
#endif
#include "dmac_config.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DFT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

/* PHY内置LNA增益与档位的对应表,单位是1dB, 真实值是小数，以下做了乘100处理，第一个值0为无效值 */
OAL_STATIC oal_int32   g_al_intlna_gain[DMAC_DFT_PHY_INTLAN_GAIN_NUM] =
{0, -310, 290, 890, 1490, 2090, 2690, 3290};

/* PHY VGA增益与档位的对应表，单位是1dB, 做乘100处理 */
OAL_STATIC oal_int32   g_al_vga_gain[DMAC_DFT_PHY_VGA_GAIN_NUM] =
{0, 100, 200, 300, 400, 500, 600, 700, 800, 900,
1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900,
2000, 2100, 2200, 2300, 2400, 2500, 2600, -500, -400, -300,
-200, -100};

#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_dft_set_phy_stat_node
 功能描述  : 设置phy的统计节点，phy有16个统计节点，但是每次只有4个可以工作
             ，需要指定工作的节点的idx,配置phy寄存器
 输入参数  : oam_stats_phy_node_idx_stru: 保存phy当前使能的统计节点idx的结构指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    hal_dft_set_phy_stat_node(pst_device->pst_device_stru,pst_phy_node_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_adc_pin
 功能描述  : 获取phy ADC口功率, 可能是小数，做乘100处理转化成整数，界面显示再
             转化成小数.由于从寄存器中读取出来的值单位是0.25dB，因此还要做除4
             处理
 输入参数  : ul_adc_pin_code_rpt:PHY bank2 ADC_PIN_CODE_RPT寄存器的值,
                                 AGC ADC口功率与输出档位值上报
 输出参数  : pl_adc_pin:phy ADC口功率
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_adc_pin(oal_uint32 ul_adc_pin_code_rpt,
                                                  oal_int32 *pl_adc_pin)
{
    oal_int32       l_adc_pin_phy;       /* 从phy寄存器中读取出来的adc口功率值，此时单位是0.25dB */

    /* ul_adc_pin_code_rpt的低9bit值是ADC口功率，有符号数，单位0.25dB,根据符号位
       来确定真实值
    */
    if (BIT8 != (BIT8 & ul_adc_pin_code_rpt))
    {
        /* 正数，直接转化为单位为1dB的值,然后乘以100保证接下来处理的是整数 */
        *pl_adc_pin = (ul_adc_pin_code_rpt & 0x1FF) * 100 / 4;
    }
    else
    {

        l_adc_pin_phy = (oal_int32)ul_adc_pin_code_rpt;
        /*lint -e701*//*lint -e702*/
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy << 23);
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy >> 23);
        /*lint +e701*//*lint +e702*/
        *pl_adc_pin = l_adc_pin_phy * 100 / 4;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_extlna_gain
 功能描述  : 获取外置LNA增益
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_extlna_gain(mac_device_stru *pst_macdev,
                                                      oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_extlna_gain)
{
    oal_uint32          ul_extlna_gain0_cfg = 0;
    oal_uint32          ul_extlna_gain1_cfg = 0;
    oal_int32           l_extlna_gain0_cfg;
    oal_int32           l_extlna_gain1_cfg;
    oal_uint8           uc_lna_code_out_3;
    oal_int32           l_extlna_gain;

    /* 读取外置LNA为0和1时增益 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_EXTLNA_GAIN0_CFG_REG, &ul_extlna_gain0_cfg);
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_EXTLNA_GAIN1_CFG_REG, &ul_extlna_gain1_cfg);
    /*lint -e701*//*lint -e702*/
    /* 计算外置LNA为0时的增益值 */
    l_extlna_gain0_cfg = (oal_int32)(ul_extlna_gain0_cfg);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg << 22);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg >> 22);

    /* 计算外置LNA为1时的增益值 */
    l_extlna_gain1_cfg = (oal_int32)(ul_extlna_gain1_cfg);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg << 22);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg >> 22);
    /*lint +e701*//*lint +e702*/
    /* 获取外置LNA档位值 */
    uc_lna_code_out_3 = (ul_adc_pin_code_rpt & BIT15) >> 15;

    /* 计算外置LNA增益 */
    l_extlna_gain = (uc_lna_code_out_3 == 0) ? l_extlna_gain0_cfg : l_extlna_gain1_cfg;

    *pl_extlna_gain = l_extlna_gain * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_intlna_gain
 功能描述  : 获取内置LNA增益
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_intlna_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_intlna_gain)
{
    oal_uint8       uc_lna_code_out_0_2;

    /* 获取内置LNA档位值，并计算内置LNA增益 */
    uc_lna_code_out_0_2 = (ul_adc_pin_code_rpt & (BIT12 | BIT13 | BIT14)) >> 12;

    if (0 == uc_lna_code_out_0_2 || DMAC_DFT_PHY_INTLAN_GAIN_NUM <= uc_lna_code_out_0_2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_intlna_gain:: lna_code_out[2:0] val=[%d] invalid.}",
                         uc_lna_code_out_0_2);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_intlna_gain = g_al_intlna_gain[uc_lna_code_out_0_2];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_vga_gain
 功能描述  : 计算获取vga增益值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_vga_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                   oal_int32 *pl_vga_gain)
{
    oal_uint8       uc_vga_coude_out_0_4;

    /* 获取VGA档位值，并计算VGA增益 */
    uc_vga_coude_out_0_4 = (ul_adc_pin_code_rpt & (BIT16 | BIT17 | BIT18 | BIT19 | BIT20)) >> 16;

    if (DMAC_DFT_PHY_VGA_GAIN_NUM <= uc_vga_coude_out_0_4)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_vga_gain:: vga_coude_out[4:0] val=[%d] invalid.}",
                         uc_vga_coude_out_0_4);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_vga_gain = g_al_vga_gain[uc_vga_coude_out_0_4];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_reference0
 功能描述  : 获取接收天线口功率参考值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_reference0(mac_device_stru *pst_macdev,
                                                     oal_int32 *pl_reference0)
{
    oal_uint32      ul_cfg_power0_ref = 0;
    oal_int32       l_cfg_power0_ref;

    /* 计算接收天线口功率计算参考值 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_POWER0_REF_REG, &ul_cfg_power0_ref);
    /*lint -e701*//*lint -e702*/
    l_cfg_power0_ref = (oal_int32)ul_cfg_power0_ref;
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref << 24);
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref >> 24);
    /*lint +e701*//*lint +e702*/
    *pl_reference0 = l_cfg_power0_ref * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_calcu_antenna_power
 功能描述  : tbtt中断到来的时候，计算天线口功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月29日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev)
{
    oal_uint32          ul_adc_pin_code_rpt;       /* PHY bank2 ADC_PIN_CODE_RPT寄存器的值 */
    oal_int32           l_adc_pin = 0;
    oal_int32           l_extlna_gain = 0;             /* 外置LNA增益 */
    oal_int32           l_intlna_gain = 0;             /* 内置LNA增益 */
    oal_int32           l_vga_gain = 0;                /* VGA增益 */
    oal_int32           l_reference0 = 0;              /* 接收天线口功率计算参考值 */

    /* phy提供的底噪计算公式: adc_pin - (extlna_gain + intlna_gain + vga_gain + reference_0)*/

    /* 读取PHY AGC ADC口功率与输出档位值 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_ADC_PIN_CODE_RPT_REG, &ul_adc_pin_code_rpt);

    /* 获取ADC口功率 */
    dmac_dft_get_adc_pin(ul_adc_pin_code_rpt, &l_adc_pin);

    /* 获取外置LNA增益 */
    dmac_dft_get_extlna_gain(pst_macdev, ul_adc_pin_code_rpt, &l_extlna_gain);

    /* 获取内置LNA增益 */
    dmac_dft_get_intlna_gain(ul_adc_pin_code_rpt, &l_intlna_gain);

    /* 获取VGA增益 */
    dmac_dft_get_vga_gain(ul_adc_pin_code_rpt, &l_vga_gain);

    /* 获取接收天线口功率计算参考值 */
    dmac_dft_get_reference0(pst_macdev, &l_reference0);

    /* 存到device下，供维测获取 */
    pst_macdev->st_dbb_env_param_ctx.s_ant_power = (oal_int16)(l_adc_pin - (l_extlna_gain + l_intlna_gain + l_vga_gain + l_reference0));
}


/*****************************************************************************
 函 数 名  : dmac_dft_get_antenna_power
 功能描述  : 获取天线口功率,计算方法参考<<Hi1151 V100 DFT软件设计说明书>>
             "3.5.7.3	DBB PHY天线口功率上报"
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_get_antenna_power(mac_device_stru *pst_macdev,
                                                          oal_int32 *pl_antenna_power)
{
    *pl_antenna_power = (oal_int32)pst_macdev->st_dbb_env_param_ctx.s_ant_power;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_chan_stat_result
 功能描述  : 获取mac和phy信道测量的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_chan_stat_result(
                                    mac_device_stru  *pst_macdev,
                                    oam_stats_dbb_env_param_stru  *pst_dbb_env_param)
{
    oal_uint32       ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_CH_LOAD_STAT_PERIOD_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_stats_period_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_20M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri20_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_40M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri40_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_80M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri80_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_rx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_tx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_FREE_ACCUM_WIN_REG, &ul_reg_value);
    pst_dbb_env_param->uc_phy_ch_estimate_time_ms = (oal_uint8)(ul_reg_value & 0xF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI20_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri20_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI40_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri40_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI80_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri80_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dbb_env_param
 功能描述  : 获取统计数据，上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_dbb_env_param(mac_device_stru *pst_macdev)
{
    oam_stats_dbb_env_param_stru        st_dbb_env_param;
    oal_uint32                          ul_beacon_miss_num;
    oal_uint8                           uc_loop;
    oal_uint32                          ul_clear_reg_val = 0;

    OAL_MEMZERO(&st_dbb_env_param, OAL_SIZEOF(oam_stats_dbb_env_param_stru));

    /* 获取接收到非本机地址的帧个数，单位是: 个/s */
    st_dbb_env_param.ul_non_directed_frame_num = (pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num
                                               * DMAC_DFT_REPORT_TO_COLLECT_TIMES) >> 1;
    /* 清零超时次数和非本机地址帧个数 */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    /* 获取每一个ap beacon miss最大次数 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_BEACON_MISS_NUM_REG, &ul_beacon_miss_num);
    for (uc_loop = 0; uc_loop < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_loop++)
    {
        DMAC_DFT_AP_BEACON_MISS_MAX_NUM(uc_loop, ul_beacon_miss_num, &st_dbb_env_param.aul_beacon_miss_max_num[uc_loop]);
    }

    /* 清零mac统计ap beacon miss最大次数 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, &ul_clear_reg_val);
    hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, ul_clear_reg_val | BIT23);

    /* 获取MAC PHY测量信道结果 */
    dmac_dft_get_chan_stat_result(pst_macdev, &st_dbb_env_param);

    /* 上报参数 */
    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_dbb_env_param,(oal_uint16)OAL_SIZEOF(oam_stats_dbb_env_param_stru), OAM_OTA_TYPE_DBB_ENV_PARAM);

}


/*****************************************************************************
 函 数 名  : dmac_dft_collect_dbb_env_param_timeout
 功能描述  : 空口环境维测参数采集定时器超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_collect_dbb_env_param_timeout(oal_void *p_arg)
{
    mac_device_stru         *pst_macdev;
    oal_uint32               ul_reg_tmp_val;

    pst_macdev = (mac_device_stru *)p_arg;

    /* 增加超时次数的计数 */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt++;

    /* 如果本次是第98次超时，通知DBB MAC开始统计CCA空闲率，DBB PHY开始统计信道空闲功率 */
    if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 2 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置DBB MAC统计周期,20ms */
        hal_set_ch_statics_period(pst_macdev->pst_device_stru, DMAC_DFT_MAC_CHAN_STAT_PERIOD);

        /* 配置DBB PHY统计周期 */
        hal_set_ch_measurement_period(pst_macdev->pst_device_stru, DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD);

        /* 使能DBB MAC和DBB PHY开始统计 */
        hal_enable_ch_statics(pst_macdev->pst_device_stru, 1);

        return OAL_SUCC;
    }
    /* 如果本次是第99次超时，开始收集一个周期(20ms)数据(接收到非本机地址的帧个数) */
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 1 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置mac不过滤，持续20ms */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val & (~(BIT11 | BIT13)));

        return OAL_SUCC;
    }
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置mac过滤 */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val | (BIT11 | BIT13));

        return dmac_dft_report_dbb_env_param(pst_macdev);
    }
    else
    {
        return OAL_SUCC;
    }
}


/*****************************************************************************
 函 数 名  : dmac_dft_start_report_dbb_env
 功能描述  : 开始上报空口环境类维测参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 启动采集维测参数定时器，定时器超时100次的时候上报维测参数 */
    FRW_TIMER_CREATE_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer,
                           dmac_dft_collect_dbb_env_param_timeout,
                           DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT,
                           (oal_void *)pst_device,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_device->ul_core_id);

    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = OAL_TRUE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_stop_report_dbb_env
 功能描述  : 停止上报空口环境类的维测参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 删除定时器 */
    if (OAL_TRUE == pst_device->st_dbb_env_param_ctx.st_collect_period_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer);
    }

    /* 清零计数器 */
    pst_device->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_device->st_dbb_env_param_ctx.s_ant_power           = 0;
    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = 0;
    pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_dft_mgmt_stat_incr
 功能描述  : 管理帧统计计数加1
 输入参数  : puc_mac_hdr_addr: 帧头地址
             en_type         : 统计类型(位置:发送，发送完成，接收)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月1日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type)
{
    oal_uint8           uc_subtype;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_mac_hdr_addr || OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::param is null. puc_mac_hdr_addr = [%d],\
                       mac_dev = [%d]}", puc_mac_hdr_addr, pst_mac_dev);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_DEV_MGMT_STAT_TYPE_BUTT <= en_type)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::en_type exceeds! en_type = [%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_MANAGEMENT == mac_frame_get_type_value(puc_mac_hdr_addr))
    {
        uc_subtype = mac_frame_get_subtype_value(puc_mac_hdr_addr);
        if (uc_subtype >= WLAN_MGMT_SUBTYPE_BUTT)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::uc_subtype exceeds! uc_subtype = [%d].}",
                           uc_subtype);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        switch (en_type)
        {
            case MAC_DEV_MGMT_STAT_TYPE_TX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_soft[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_RX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_rx_mgmt[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_TX_COMPLETE:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_hardware[uc_subtype]);
            break;

            default:
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_machw_stat_info
 功能描述  : 从mac寄存器获取收发包数目统计值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat)
{
#if 0
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev || OAL_PTR_NULL == pst_machw_stat))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_get_machw_stat_info:: pst_dev = [%d], \
                       pst_machw_stat = [%d]}", pst_dev, pst_machw_stat);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hal_dft_get_machw_stat_info(pst_dev,pst_machw_stat);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_print_all_Para
 功能描述  : 日志方式上报维测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_print_mac_phy_rf(mac_device_stru *pst_mac_dev)
{
    /* 打印mac维测信息，上报寄存器可增加*/
    hal_dft_print_machw_stat(pst_mac_dev->pst_device_stru);

    /* 打印phy维测信息，上报寄存器可增加*/
    hal_dft_print_phyhw_stat(pst_mac_dev->pst_device_stru);

    /* 打印rf维测信息，上报寄存器可增加*/
    hal_dft_print_rfhw_stat(pst_mac_dev->pst_device_stru);
}

/*****************************************************************************
 函 数 名  : dmac_dft_print_all_Para
 功能描述  : 日志方式上报维测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月8日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_print_all_para(dmac_vap_stru *pst_dmac_sta, oal_bool_enum_uint8 en_all_info)
{
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_dmac_sta->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_dft_report_all_ota_state::dev is null!}");
        return;
    }

    /*打印当前的信号状况和link_loss计数*/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    OAM_WARNING_LOG2(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "now linkloss:bt state is bt_on/off =%d, linkloss_old_bt_on/off =%d",
        pst_dmac_sta->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on,
        pst_dmac_sta->st_linkloss_info.en_old_bt_on);
#endif
    OAM_WARNING_LOG4(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "signal = %d,dbac_runing = %d, link_loss_cnt =%d, linkloss_threshold = %d",
        pst_dmac_sta->st_query_stats.ul_signal,
        pst_mac_dev->en_dbac_running,
        pst_dmac_sta->st_linkloss_info.us_link_loss,
        pst_dmac_sta->st_linkloss_info.us_linkloss_threshold);

    /*打印当前ac队列信息*/
    OAM_WARNING_LOG_ALTER(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{mpdu num:total = %d, be = %d, bk = %d, vi = %d, vo = %d}",
                     5,
                     pst_mac_dev->us_total_mpdu_num,
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_VO]);

    if (OAL_FALSE == en_all_info)
    {
        return;
    }

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* 协议的关键计数 */
    dmac_pm_key_info_dump(pst_dmac_sta);

    /* 平台的睡眠计数*/
    PM_WLAN_DumpSleepCnt();
#endif


    /*linkloss打印mac维测信息，上报寄存器可增加*/
    hal_dft_print_machw_stat(pst_mac_dev->pst_device_stru);

    /*linkloss打印phy维测信息，上报寄存器可增加*/
    hal_dft_print_phyhw_stat(pst_mac_dev->pst_device_stru);

    /*linkloss打印rf维测信息，上报寄存器可增加*/
    hal_dft_print_rfhw_stat(pst_mac_dev->pst_device_stru);
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_all_ota_state
 功能描述  : 通过OTA上报统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月8日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta)
{
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_mac_sta->uc_device_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_sta->uc_vap_id, OAM_SF_ANY, "{dmac_dft_report_all_ota_state::dev is null!}");
        return;
    }

    hal_dft_report_all_reg_state(pst_mac_dev->pst_device_stru);
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_all_para
 功能描述  : 异常上报维测信息,包括日志打印和OTA上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月8日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch)
{

    /*打印维测信息*/
    dmac_dft_print_all_para(pst_dmac_sta, (oal_bool_enum_uint8 )uc_ota_switch);
    /*OTA上报维测信息*/
    if(OAL_TRUE == uc_ota_switch)
    {
        dmac_dft_report_all_ota_state(&pst_dmac_sta->st_vap_base_info);
    }
}

//oal_module_symbol(dmac_dft_report_all_para);

/*****************************************************************************
 函 数 名  : dmac_dft_set_simple_vap_info
 功能描述  : 设置OTA上报的vap结构体信息
 输入参数  : dmac_vap_dft_stru *pst_dmac_vap_dft, mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_dft_set_simple_vap_info(dmac_vap_dft_stru *pst_dmac_vap_dft, mac_vap_stru  *pst_mac_vap)
{
    dmac_vap_stru       *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_dmac_vap_dft) || (OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_set_simple_vap_info:: input params is invalid, [%p] [%p]!}",
                       pst_dmac_vap_dft, pst_mac_vap);
        return;
    }

    /* 获取dmac vap */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_set_simple_vap_info:: dmac vap[%d] is null!}",
                       pst_mac_vap->uc_vap_id);
        return;
    }

    OAL_MEMZERO(pst_dmac_vap_dft, OAL_SIZEOF(dmac_vap_dft_stru));

    /* dmac_vap_dft_stru结构体赋值 */
    /* 以下赋值从mac_vap_stru结构体中取值 */
    pst_dmac_vap_dft->uc_vap_id    = pst_mac_vap->uc_vap_id;
    pst_dmac_vap_dft->uc_device_id = pst_mac_vap->uc_device_id;
    pst_dmac_vap_dft->uc_chip_id   = pst_mac_vap->uc_vap_id;
    pst_dmac_vap_dft->en_vap_mode  = pst_mac_vap->en_vap_mode;
    pst_dmac_vap_dft->en_vap_state = pst_mac_vap->en_vap_state;
    pst_dmac_vap_dft->en_protocol  = pst_mac_vap->en_protocol;
    pst_dmac_vap_dft->bit_has_user_bw_limit  = pst_mac_vap->bit_has_user_bw_limit;
    pst_dmac_vap_dft->bit_vap_bw_limit       = pst_mac_vap->bit_vap_bw_limit;
    pst_dmac_vap_dft->uc_tx_power            = pst_mac_vap->uc_tx_power;
    pst_dmac_vap_dft->en_p2p_mode            = pst_mac_vap->en_p2p_mode;
    pst_dmac_vap_dft->uc_p2p_gocl_hal_vap_id = pst_mac_vap->uc_p2p_gocl_hal_vap_id;
    pst_dmac_vap_dft->us_user_nums           = pst_mac_vap->us_user_nums;
    pst_dmac_vap_dft->us_multi_user_idx      = pst_mac_vap->us_multi_user_idx;

    oal_memcopy(pst_dmac_vap_dft->auc_bssid, pst_mac_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_channel,
                (oal_uint8 *)&pst_mac_vap->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_cap_flag,
                (oal_uint8 *)&pst_mac_vap->st_cap_flag, OAL_SIZEOF(mac_cap_flag_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_protection,
                (oal_uint8 *)&pst_mac_vap->st_protection, OAL_SIZEOF(mac_protection_stru));

    /* 以下赋值从dmac_vap_stru结构体中取值 */
    pst_dmac_vap_dft->uc_ps_user_num     = pst_dmac_vap->uc_ps_user_num;
    pst_dmac_vap_dft->uc_dtim_count      = pst_dmac_vap->uc_dtim_count;
    pst_dmac_vap_dft->uc_uapsd_max_depth = pst_dmac_vap->uc_uapsd_max_depth;

    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_linkloss_info,
                (oal_uint8 *)&pst_dmac_vap->st_linkloss_info, OAL_SIZEOF(dmac_vap_linkloss_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_alg,
                (oal_uint8 *)&pst_dmac_vap->st_tx_alg, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_data_mcast,
                (oal_uint8 *)&pst_dmac_vap->st_tx_data_mcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_data_bcast,
                (oal_uint8 *)&pst_dmac_vap->st_tx_data_bcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->ast_tx_mgmt_ucast,
                (oal_uint8 *)&pst_dmac_vap->ast_tx_mgmt_ucast, OAL_SIZEOF(hal_tx_txop_alg_stru) * WLAN_BAND_BUTT);
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->ast_tx_mgmt_bmcast,
                (oal_uint8 *)&pst_dmac_vap->ast_tx_mgmt_bmcast, OAL_SIZEOF(hal_tx_txop_alg_stru) * WLAN_BAND_BUTT);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dmac_vap_info
 功能描述  : OTA上报dmac vap结构体信息
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_dmac_vap_info(mac_vap_stru  *pst_mac_vap)
{
    dmac_vap_dft_stru   st_dmac_vap_dft;

    /* ota上报的dmac_vap_dft_stru结构体赋值 */
    dmac_dft_set_simple_vap_info(&st_dmac_vap_dft, pst_mac_vap);

    /* 上报dmac vap信息 */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)&st_dmac_vap_dft,
                          (oal_uint16)OAL_SIZEOF(dmac_vap_dft_stru),
                          OAM_OTA_TYPE_DMAC_VAP);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_set_simple_user_info
 功能描述  : 设置OTA上报的dmac user结构体信息
 输入参数  : dmac_user_dft_stru *pst_dmac_user_dft, dmac_user_stru  *pst_dmac_user
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_dft_set_simple_user_info(dmac_user_dft_stru *pst_dmac_user_dft, dmac_user_stru  *pst_dmac_user)
{
    mac_user_stru       *pst_mac_user;

    if ((OAL_PTR_NULL == pst_dmac_user_dft) || (OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_set_simple_user_info:: input params is invalid, [%p] [%p]!}",
                       pst_dmac_user_dft, pst_dmac_user);
        return;
    }

    OAL_MEMZERO(pst_dmac_user_dft, OAL_SIZEOF(dmac_user_dft_stru));

    /* dmac_user_dft_stru结构体赋值 */
    /* 以下赋值从mac_user_stru结构体下取值 */
    pst_mac_user = &pst_dmac_user->st_user_base_info;
    pst_dmac_user_dft->us_assoc_id      = pst_mac_user->us_assoc_id;
    pst_dmac_user_dft->uc_device_id     = pst_mac_user->uc_device_id;
    pst_dmac_user_dft->en_is_multi_user = pst_mac_user->en_is_multi_user;
    pst_dmac_user_dft->uc_vap_id        = pst_mac_user->uc_vap_id;
    pst_dmac_user_dft->uc_chip_id       = pst_mac_user->uc_chip_id;
    pst_dmac_user_dft->en_protocol_mode            = pst_mac_user->en_protocol_mode;
    pst_dmac_user_dft->en_avail_protocol_mode      = pst_mac_user->en_avail_protocol_mode;
    pst_dmac_user_dft->en_cur_protocol_mode        = pst_mac_user->en_cur_protocol_mode;
    pst_dmac_user_dft->uc_avail_num_spatial_stream = pst_mac_user->uc_avail_num_spatial_stream;
    pst_dmac_user_dft->uc_num_spatial_stream       = pst_mac_user->uc_num_spatial_stream;
    pst_dmac_user_dft->uc_avail_bf_num_spatial_stream = pst_mac_user->uc_avail_bf_num_spatial_stream;
    pst_dmac_user_dft->en_port_valid      = pst_mac_user->en_port_valid;
    pst_dmac_user_dft->en_bandwidth_cap   = pst_mac_user->en_bandwidth_cap;
    pst_dmac_user_dft->en_avail_bandwidth = pst_mac_user->en_avail_bandwidth;
    pst_dmac_user_dft->en_cur_bandwidth   = pst_mac_user->en_cur_bandwidth;
    pst_dmac_user_dft->en_user_asoc_state = pst_mac_user->en_user_asoc_state;

    oal_memcopy(pst_dmac_user_dft->auc_user_mac_addr, pst_mac_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_avail_op_rates,
                (oal_uint8 *)&pst_mac_user->st_avail_op_rates, OAL_SIZEOF(mac_rate_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_user_tx_info,
                (oal_uint8 *)&pst_mac_user->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_cap_info,
                (oal_uint8 *)&pst_mac_user->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_ht_hdl,
                (oal_uint8 *)&pst_mac_user->st_ht_hdl, OAL_SIZEOF(mac_user_ht_hdl_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_vht_hdl,
                (oal_uint8 *)&pst_mac_user->st_vht_hdl, OAL_SIZEOF(mac_vht_hdl_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_key_info,
                (oal_uint8 *)&pst_mac_user->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));

    /* 以下赋值从dmac_user_stru结构体下取值 */
    pst_dmac_user_dft->uc_lut_index     = pst_dmac_user->uc_lut_index;
    pst_dmac_user_dft->uc_uapsd_flag    = pst_dmac_user->uc_uapsd_flag;
    pst_dmac_user_dft->uc_max_key_index = pst_dmac_user->uc_max_key_index;

    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_tx_data_mcast,
                (oal_uint8 *)&pst_dmac_user->st_tx_data_mcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_tx_data_bcast,
                (oal_uint8 *)&pst_dmac_user->st_tx_data_bcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_uapsd_status,
                (oal_uint8 *)&pst_dmac_user->st_uapsd_status, OAL_SIZEOF(mac_user_uapsd_status_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_user_rate_info,
                (oal_uint8 *)&pst_dmac_user->st_user_rate_info, OAL_SIZEOF(dmac_user_rate_info_stru));

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dmac_user_info
 功能描述  : OTA上报dmac user结构体信息
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_dmac_user_info(mac_vap_stru  *pst_mac_vap)
{
    oal_dlist_head_stru     *pst_entry;
    dmac_user_stru          *pst_dmac_user;
    dmac_user_dft_stru       st_dmac_user_dft;

    /* 遍历vap下所有用户 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_dmac_user = (dmac_user_stru *)pst_entry;

        /* ota上报的dmac_user_dft_stru结构体赋值 */
        dmac_dft_set_simple_user_info(&st_dmac_user_dft, pst_dmac_user);

        oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                              (oal_uint8 *)&st_dmac_user_dft,
                              (oal_uint16)OAL_SIZEOF(dmac_user_dft_stru),
                              OAM_OTA_TYPE_DMAC_USER);
    }

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dmac_event_info
 功能描述  : OTA上报dmac事件信息
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_dmac_event_info(mac_vap_stru  *pst_mac_vap)
{
    frw_event_mgmt_stru    *pst_event_mgmt;
    frw_event_queue_stru    ast_event_queue[WLAN_FRW_MAX_NUM_CORES * FRW_EVENT_MAX_NUM_QUEUES];
    oal_uint32              ul_core_id;

    /* 遍历每个核的每个vap对应的事件队列 */
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        /* 根据核找到相应的核上的事件管理结构体 */
        pst_event_mgmt = &g_ast_event_manager[ul_core_id];

        oal_memcopy((oal_uint8 *)(&ast_event_queue[ul_core_id * FRW_EVENT_MAX_NUM_QUEUES]),
                    (oal_uint8 *)pst_event_mgmt->st_event_queue, OAL_SIZEOF(pst_event_mgmt->st_event_queue));
    }

    /* 上报当前存在的所有事件队列信息 */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)ast_event_queue,
                          (oal_uint16)OAL_SIZEOF(ast_event_queue),
                          OAM_OTA_TYPE_EVENT_QUEUE);

    return;
}

extern oal_netbuf_pool_stru g_st_netbuf_pool;
/*****************************************************************************
 函 数 名  : dmac_dft_report_dmac_memory_info
 功能描述  : OTA上报dmac事件信息
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_dmac_memory_info(mac_vap_stru  *pst_mac_vap)
{
    mem_pool_dft_stru          ast_mem_poop_dft_info[OAL_MEM_POOL_ID_BUTT];
    mem_pool_dft_stru         *pst_mem_poop_dft;
    mem_subpool_dft_stru      *pst_mem_subpool_dft;
    oal_mem_pool_stru         *pst_mem_pool;
    oal_mem_subpool_stru      *pst_mem_subpool;
    oal_netbuf_pool_stru      *pst_netbuf_pool;
    oal_netbuf_subpool_stru   *pst_netbuf_subpool;
    oal_uint32                 ul_pool_id = 0;
    oal_uint32                 ul_sub_pool_id = 0;
    oal_uint32                 ul_sub_pool_cnt = 0;

    /* OTA上报内存使用情况的信息清零 */
    OAL_MEMZERO(ast_mem_poop_dft_info, OAL_SIZEOF(ast_mem_poop_dft_info));

    oal_irq_disable();

    for(ul_pool_id = 0; ul_pool_id < OAL_MEM_POOL_ID_NETBUF; ul_pool_id++)
    {
        /* 获取内存池 */
        pst_mem_pool = oal_mem_get_pool((oal_uint8)ul_pool_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mem_pool))
        {
            oal_irq_enable();
            return;
        }

        /* 将内存池的使用情况进行赋值，用于上报 */
        pst_mem_poop_dft = &(ast_mem_poop_dft_info[ul_pool_id]);
        pst_mem_poop_dft->uc_pool_id = (oal_uint8)ul_pool_id;
        pst_mem_poop_dft->uc_subpool_cnt   = pst_mem_pool->uc_subpool_cnt;
        pst_mem_poop_dft->us_max_byte_len  = pst_mem_pool->us_max_byte_len;
        pst_mem_poop_dft->us_mem_total_cnt = pst_mem_pool->us_mem_total_cnt;
        pst_mem_poop_dft->us_mem_used_cnt  = pst_mem_pool->us_mem_used_cnt;

        /* 获取当前内存池的子池个数 */
        ul_sub_pool_cnt = (oal_uint32)pst_mem_poop_dft->uc_subpool_cnt;
        for (ul_sub_pool_id = 0; ul_sub_pool_id < ul_sub_pool_cnt; ul_sub_pool_id++)
        {
            pst_mem_subpool = &(pst_mem_pool->ast_subpool_table[ul_sub_pool_id]);

            /* 将本内存池的子内存池的使用情况进行赋值，用于上报 */
            pst_mem_subpool_dft = &(pst_mem_poop_dft->ast_subpool_table[ul_sub_pool_id]);
            pst_mem_subpool_dft->uc_sub_pool_id = (oal_uint8)ul_sub_pool_id;
            pst_mem_subpool_dft->us_total_cnt   = pst_mem_subpool->us_total_cnt;
            pst_mem_subpool_dft->us_free_cnt    = pst_mem_subpool->us_free_cnt;
        }

    }

    /* nebuf内存池使用情况赋值，用于上报 */
    pst_netbuf_pool = &g_st_netbuf_pool;

    pst_mem_poop_dft = &(ast_mem_poop_dft_info[OAL_MEM_POOL_ID_NETBUF]);
    pst_mem_poop_dft->uc_pool_id       = OAL_MEM_POOL_ID_NETBUF;
    pst_mem_poop_dft->us_max_byte_len  = pst_netbuf_pool->us_max_byte_len;
    pst_mem_poop_dft->us_mem_total_cnt = pst_netbuf_pool->us_mem_total_cnt;
    pst_mem_poop_dft->us_mem_used_cnt  = pst_netbuf_pool->us_mem_used_cnt;

    ul_sub_pool_cnt = pst_netbuf_pool->uc_subpool_cnt;
    for (ul_sub_pool_id = 0; ul_sub_pool_id < ul_sub_pool_cnt; ul_sub_pool_id++)
    {
        pst_netbuf_subpool = &(pst_netbuf_pool->ast_subpool_table[ul_sub_pool_id]);

        /* netbuf内存子池的使用情况进行赋值，用于上报 */
        pst_mem_subpool_dft = &(pst_mem_poop_dft->ast_subpool_table[ul_sub_pool_id]);
        pst_mem_subpool_dft->uc_sub_pool_id = (oal_uint8)ul_sub_pool_id;
        pst_mem_subpool_dft->us_total_cnt   = pst_netbuf_subpool->us_total_cnt;
        pst_mem_subpool_dft->us_free_cnt    = pst_netbuf_subpool->us_free_cnt;
    }

    oal_irq_enable();

    /* 上报当前内存池的使用情况 */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)ast_mem_poop_dft_info,
                          (oal_uint16)OAL_SIZEOF(ast_mem_poop_dft_info),
                          OAM_OTA_TYPE_MEMPOOL);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_mac_hardware_info
 功能描述  : OTA上报mac硬件相关信息
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_mac_hardware_info(mac_vap_stru  *pst_mac_vap)
{
    hal_device_dft_stru          st_hal_device_info;
    mac_device_stru             *pst_mac_device;
    hal_to_dmac_device_stru     *pst_hal_to_dmac_device;
    oal_uint32                   ul_fake_id = 0;

    /* 获取mac device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
                         "{dmac_dft_report_mac_hardware_info:: mac device[%d] is null!}", pst_mac_vap->uc_device_id);
        return;
    }

    pst_hal_to_dmac_device = pst_mac_device->pst_device_stru;

    /* OTA上报hal device信息清零 */
    OAL_MEMZERO(&st_hal_device_info, OAL_SIZEOF(hal_device_dft_stru));

    /* 上报硬件信息赋值 */
    st_hal_device_info.uc_chip_id       = pst_hal_to_dmac_device->uc_chip_id;
    st_hal_device_info.uc_device_id     = pst_hal_to_dmac_device->uc_device_id;
    st_hal_device_info.uc_mac_device_id = pst_hal_to_dmac_device->uc_mac_device_id;
    st_hal_device_info.uc_curr_state    = pst_hal_to_dmac_device->uc_curr_state;
    st_hal_device_info.ul_core_id       = pst_hal_to_dmac_device->ul_core_id;

    /* 拷贝发送、接收、虚假队列中的信息，用于ota上报 */
    oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_rx_dscr_queue),
                (oal_uint8 *)pst_hal_to_dmac_device->ast_rx_dscr_queue, OAL_SIZEOF(st_hal_device_info.ast_rx_dscr_queue));
    oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_tx_dscr_queue),
                (oal_uint8 *)pst_hal_to_dmac_device->ast_tx_dscr_queue, OAL_SIZEOF(st_hal_device_info.ast_tx_dscr_queue));

    /* 拷贝虚假队列中的内容 */
    for (ul_fake_id = 0; ul_fake_id < HAL_TX_FAKE_QUEUE_NUM; ul_fake_id++)
    {
        oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_tx_dscr_queue_fake[ul_fake_id]),
                    (oal_uint8 *)pst_hal_to_dmac_device->ast_tx_dscr_queue_fake[ul_fake_id],
                    OAL_SIZEOF(hal_tx_dscr_queue_header_stru) * HAL_TX_QUEUE_NUM);
    }

    /* 上报当前mac硬件相关信息，主要包括硬件发送、接收队列、虚假队列信息 */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)(&st_hal_device_info),
                          (oal_uint16)OAL_SIZEOF(st_hal_device_info),
                          OAM_OTA_TYPE_HARDWARE_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dmac_queue_info
 功能描述  : OTA上报队列相关信息(TID队列，省电队列报文信息)
 输入参数  : mac_vap_stru  *pst_mac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_dft_report_dmac_queue_info(mac_vap_stru  *pst_mac_vap)
{
    oal_dlist_head_stru                    *pst_entry;
    dmac_user_stru                         *pst_dmac_user;
    dmac_user_queue_info_dft_stru           st_queue_info;

    /* 遍历vap下所有用户 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_dmac_user = (dmac_user_stru *)pst_entry;

        oal_memcopy((oal_uint8 *)st_queue_info.ast_tx_tid_queue,
                    (oal_uint8 *)pst_dmac_user->ast_tx_tid_queue, OAL_SIZEOF(st_queue_info.ast_tx_tid_queue));

        #ifdef _PRE_WLAN_FEATURE_UAPSD
        oal_memcopy((oal_uint8 *)&st_queue_info.st_uapsd_stru,
                    (oal_uint8 *)&pst_dmac_user->st_uapsd_stru, OAL_SIZEOF(st_queue_info.st_uapsd_stru));
        #endif

        oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                              (oal_uint8 *)&st_queue_info,
                              (oal_uint16)OAL_SIZEOF(st_queue_info),
                              OAM_OTA_TYPE_USER_QUEUE_INFO);
    }

    return;
}

#else
/*****************************************************************************
 函 数 名  : dmac_dft_set_phy_stat_node
 功能描述  : 设置phy的统计节点，phy有16个统计节点，但是每次只有4个可以工作
             ，需要指定工作的节点的idx,配置phy寄存器
 输入参数  : oam_stats_phy_node_idx_stru: 保存phy当前使能的统计节点idx的结构指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    oal_uint8           uc_loop;
    oal_uint32          ul_phy_stat_node0_en;
    oal_uint32          ul_phy_stat_node1_en;
    oal_uint32          ul_phy_stat_node2_en;
    oal_uint32          ul_phy_stat_node3_en;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device || OAL_PTR_NULL == pst_phy_node_idx))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_phy_stat_node_init::param is null!}.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_loop = 0; uc_loop < OAM_PHY_STAT_NODE_ENABLED_MAX_NUM; uc_loop++)
    {
        pst_phy_node_idx->auc_node_idx[uc_loop]--;
    }

    /* 配置使能之前，先把之前的统计值清零，从配置生效开始的统计值才有意义 */
    hal_reg_write(pst_device->pst_device_stru, (oal_uint32)WITP_PHY_STAT_CLR_REG, 0xFFFFFFFF);

    /* 计算phy的4个统计使能节点需要赋的值 */
    ul_phy_stat_node0_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_0_BASE + pst_phy_node_idx->auc_node_idx[0]);
    ul_phy_stat_node1_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_1_BASE + pst_phy_node_idx->auc_node_idx[1]);
    ul_phy_stat_node2_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_2_BASE + pst_phy_node_idx->auc_node_idx[2]);
    ul_phy_stat_node3_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_3_BASE + pst_phy_node_idx->auc_node_idx[3]);

    /* 配置phy统计使能节点0、1 */
    hal_reg_write(pst_device->pst_device_stru,
                  (oal_uint32)WITP_PHY_PHY_STA_01_EN_REG,
                  ul_phy_stat_node0_en | ul_phy_stat_node1_en);

    /* 配置phy统计使能节点2、3 */
    hal_reg_write(pst_device->pst_device_stru,
                  (oal_uint32)WITP_PHY_PHY_STA_23_EN_REG,
                  ul_phy_stat_node2_en | ul_phy_stat_node3_en);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_adc_pin
 功能描述  : 获取phy ADC口功率, 可能是小数，做乘100处理转化成整数，界面显示再
             转化成小数.由于从寄存器中读取出来的值单位是0.25dB，因此还要做除4
             处理
 输入参数  : ul_adc_pin_code_rpt:PHY bank2 ADC_PIN_CODE_RPT寄存器的值,
                                 AGC ADC口功率与输出档位值上报
 输出参数  : pl_adc_pin:phy ADC口功率
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_adc_pin(oal_uint32 ul_adc_pin_code_rpt,
                                                  oal_int32 *pl_adc_pin)
{
    oal_int32       l_adc_pin_phy;       /* 从phy寄存器中读取出来的adc口功率值，此时单位是0.25dB */

    /* ul_adc_pin_code_rpt的低9bit值是ADC口功率，有符号数，单位0.25dB,根据符号位
       来确定真实值
    */
    if (BIT8 != (BIT8 & ul_adc_pin_code_rpt))
    {
        /* 正数，直接转化为单位为1dB的值,然后乘以100保证接下来处理的是整数 */
        *pl_adc_pin = (ul_adc_pin_code_rpt & 0x1FF) * 100 / 4;
    }
    else
    {
         /*lint -e701*//*lint -e702*/ /* 注释掉有符号数移位错误 */
        l_adc_pin_phy = (oal_int32)ul_adc_pin_code_rpt;
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy << 23);
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy >> 23);
        /*lint +e701*//*lint +e702*/

        *pl_adc_pin = l_adc_pin_phy * 100 / 4;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_extlna_gain
 功能描述  : 获取外置LNA增益
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_extlna_gain(mac_device_stru *pst_macdev,
                                                      oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_extlna_gain)
{
    oal_uint32          ul_extlna_gain0_cfg = 0;
    oal_uint32          ul_extlna_gain1_cfg = 0;
    oal_int32           l_extlna_gain0_cfg;
    oal_int32           l_extlna_gain1_cfg;
    oal_uint8           uc_lna_code_out_3;
    oal_int32           l_extlna_gain;

    /* 读取外置LNA为0和1时增益 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_EXTLNA_GAIN0_CFG_REG, &ul_extlna_gain0_cfg);
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_EXTLNA_GAIN1_CFG_REG, &ul_extlna_gain1_cfg);

    /*lint -e701*//*lint -e702*/
    /* 计算外置LNA为0时的增益值 */
    l_extlna_gain0_cfg = (oal_int32)(ul_extlna_gain0_cfg);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg << 22);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg >> 22);

    /* 计算外置LNA为1时的增益值 */
    l_extlna_gain1_cfg = (oal_int32)(ul_extlna_gain1_cfg);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg << 22);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg >> 22);
    /*lint +e701*//*lint +e702*/

    /* 获取外置LNA档位值 */
    uc_lna_code_out_3 = (ul_adc_pin_code_rpt & BIT15) >> 15;

    /* 计算外置LNA增益 */
    l_extlna_gain = (uc_lna_code_out_3 == 0) ? l_extlna_gain0_cfg : l_extlna_gain1_cfg;

    *pl_extlna_gain = l_extlna_gain * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_intlna_gain
 功能描述  : 获取内置LNA增益
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_intlna_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_intlna_gain)
{
    oal_uint8       uc_lna_code_out_0_2;

    /* 获取内置LNA档位值，并计算内置LNA增益 */
    uc_lna_code_out_0_2 = (ul_adc_pin_code_rpt & (BIT12 | BIT13 | BIT14)) >> 12;

    if (0 == uc_lna_code_out_0_2 || DMAC_DFT_PHY_INTLAN_GAIN_NUM <= uc_lna_code_out_0_2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_intlna_gain:: lna_code_out[2:0] val=[%d] invalid.}",
                         uc_lna_code_out_0_2);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_intlna_gain = g_al_intlna_gain[uc_lna_code_out_0_2];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_vga_gain
 功能描述  : 计算获取vga增益值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_vga_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                   oal_int32 *pl_vga_gain)
{
    oal_uint8       uc_vga_coude_out_0_4;

    /* 获取VGA档位值，并计算VGA增益 */
    uc_vga_coude_out_0_4 = (ul_adc_pin_code_rpt & (BIT16 | BIT17 | BIT18 | BIT19 | BIT20)) >> 16;

    if (DMAC_DFT_PHY_VGA_GAIN_NUM <= uc_vga_coude_out_0_4)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_vga_gain:: vga_coude_out[4:0] val=[%d] invalid.}",
                         uc_vga_coude_out_0_4);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_vga_gain = g_al_vga_gain[uc_vga_coude_out_0_4];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_reference0
 功能描述  : 获取接收天线口功率参考值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_reference0(mac_device_stru *pst_macdev,
                                                     oal_int32 *pl_reference0)
{
    oal_uint32      ul_cfg_power0_ref = 0;
    oal_int32       l_cfg_power0_ref;

    /* 计算接收天线口功率计算参考值 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_POWER0_REF_REG, &ul_cfg_power0_ref);

    /*lint -e701*//*lint -e702*/
    l_cfg_power0_ref = (oal_int32)ul_cfg_power0_ref;
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref << 24);
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref >> 24);
    /*lint +e701*//*lint +e702*/

    *pl_reference0 = l_cfg_power0_ref * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_calcu_antenna_power
 功能描述  : tbtt中断到来的时候，计算天线口功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月29日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev)
{
    oal_uint32          ul_adc_pin_code_rpt;       /* PHY bank2 ADC_PIN_CODE_RPT寄存器的值 */
    oal_int32           l_adc_pin = 0;
    oal_int32           l_extlna_gain = 0;             /* 外置LNA增益 */
    oal_int32           l_intlna_gain = 0;             /* 内置LNA增益 */
    oal_int32           l_vga_gain = 0;                /* VGA增益 */
    oal_int32           l_reference0 = 0;              /* 接收天线口功率计算参考值 */

    /* phy提供的底噪计算公式: adc_pin - (extlna_gain + intlna_gain + vga_gain + reference_0)*/

    /* 读取PHY AGC ADC口功率与输出档位值 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_ADC_PIN_CODE_RPT, &ul_adc_pin_code_rpt);

    /* 获取ADC口功率 */
    dmac_dft_get_adc_pin(ul_adc_pin_code_rpt, &l_adc_pin);

    /* 获取外置LNA增益 */
    dmac_dft_get_extlna_gain(pst_macdev, ul_adc_pin_code_rpt, &l_extlna_gain);

    /* 获取内置LNA增益 */
    dmac_dft_get_intlna_gain(ul_adc_pin_code_rpt, &l_intlna_gain);

    /* 获取VGA增益 */
    dmac_dft_get_vga_gain(ul_adc_pin_code_rpt, &l_vga_gain);

    /* 获取接收天线口功率计算参考值 */
    dmac_dft_get_reference0(pst_macdev, &l_reference0);

    /* 存到device下，供维测获取 */
    pst_macdev->st_dbb_env_param_ctx.s_ant_power = (oal_int16)(l_adc_pin - (l_extlna_gain + l_intlna_gain + l_vga_gain + l_reference0));
}


/*****************************************************************************
 函 数 名  : dmac_dft_get_antenna_power
 功能描述  : 获取天线口功率,计算方法参考<<Hi1151 V100 DFT软件设计说明书>>
             "3.5.7.3	DBB PHY天线口功率上报"
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_get_antenna_power(mac_device_stru *pst_macdev,
                                                          oal_int32 *pl_antenna_power)
{
    *pl_antenna_power = (oal_int32)pst_macdev->st_dbb_env_param_ctx.s_ant_power;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_chan_stat_result
 功能描述  : 获取mac和phy信道测量的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_chan_stat_result(
                                    mac_device_stru  *pst_macdev,
                                    oam_stats_dbb_env_param_stru  *pst_dbb_env_param)
{
    oal_uint32       ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_CH_LOAD_STAT_PERIOD_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_stats_period_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_20M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri20_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_40M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri40_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_80M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri80_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_rx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_TX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_tx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_FREE_ACCUM_WIN_REG, &ul_reg_value);
    pst_dbb_env_param->uc_phy_ch_estimate_time_ms = (oal_uint8)(ul_reg_value & 0xF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI20_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri20_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI40_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri40_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI80_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri80_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_dbb_env_param
 功能描述  : 获取统计数据，上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_dbb_env_param(mac_device_stru *pst_macdev)
{
    oam_stats_dbb_env_param_stru        st_dbb_env_param;
    oal_uint32                          ul_beacon_miss_num;
    oal_uint8                           uc_loop;
    oal_uint32                          ul_clear_reg_val = 0;

    OAL_MEMZERO(&st_dbb_env_param, OAL_SIZEOF(oam_stats_dbb_env_param_stru));

    /* 获取接收到非本机地址的帧个数，单位是: 个/s */
    st_dbb_env_param.ul_non_directed_frame_num = (pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num
                                               * DMAC_DFT_REPORT_TO_COLLECT_TIMES) >> 1;
    /* 清零超时次数和非本机地址帧个数 */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    /* 获取每一个ap beacon miss最大次数 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_BEACON_MISS_NUM_REG, &ul_beacon_miss_num);
    for (uc_loop = 0; uc_loop < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_loop++)
    {
        DMAC_DFT_AP_BEACON_MISS_MAX_NUM(uc_loop, ul_beacon_miss_num, &st_dbb_env_param.aul_beacon_miss_max_num[uc_loop]);
    }

    /* 清零mac统计ap beacon miss最大次数 */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, &ul_clear_reg_val);
    hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, ul_clear_reg_val | BIT23);

    /* 获取MAC PHY测量信道结果 */
    dmac_dft_get_chan_stat_result(pst_macdev, &st_dbb_env_param);

    /* 上报参数 */
    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_dbb_env_param,(oal_uint16)OAL_SIZEOF(oam_stats_dbb_env_param_stru), OAM_OTA_TYPE_DBB_ENV_PARAM);

}


/*****************************************************************************
 函 数 名  : dmac_dft_collect_dbb_env_param_timeout
 功能描述  : 空口环境维测参数采集定时器超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_collect_dbb_env_param_timeout(oal_void *p_arg)
{
    mac_device_stru         *pst_macdev;
    oal_uint32               ul_reg_tmp_val;

    pst_macdev = (mac_device_stru *)p_arg;

    /* 增加超时次数的计数 */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt++;

    /* 如果本次是第98次超时，通知DBB MAC开始统计CCA空闲率，DBB PHY开始统计信道空闲功率 */
    if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 2 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置DBB MAC统计周期,20ms */
        hal_set_ch_statics_period(pst_macdev->pst_device_stru, DMAC_DFT_MAC_CHAN_STAT_PERIOD);

        /* 配置DBB PHY统计周期 */
        hal_set_ch_measurement_period(pst_macdev->pst_device_stru, DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD);

        /* 使能DBB MAC和DBB PHY开始统计 */
        hal_enable_ch_statics(pst_macdev->pst_device_stru, 1);

        return OAL_SUCC;
    }
    /* 如果本次是第99次超时，开始收集一个周期(20ms)数据(接收到非本机地址的帧个数) */
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 1 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置mac不过滤，持续20ms */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, ul_reg_tmp_val & (~(BIT11 | BIT13)));

        return OAL_SUCC;
    }
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* 配置mac过滤 */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, ul_reg_tmp_val | (BIT11 | BIT13));

        return dmac_dft_report_dbb_env_param(pst_macdev);
    }
    else
    {
        return OAL_SUCC;
    }
}


/*****************************************************************************
 函 数 名  : dmac_dft_start_report_dbb_env
 功能描述  : 开始上报空口环境类维测参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 启动采集维测参数定时器，定时器超时100次的时候上报维测参数 */
    FRW_TIMER_CREATE_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer,
                           dmac_dft_collect_dbb_env_param_timeout,
                           DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT,
                           (oal_void *)pst_device,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_device->ul_core_id);

    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = OAL_TRUE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_stop_report_dbb_env
 功能描述  : 停止上报空口环境类的维测参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月16日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    pst_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 删除定时器 */
    if (OAL_TRUE == pst_device->st_dbb_env_param_ctx.st_collect_period_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer);
    }

    /* 清零计数器 */
    pst_device->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_device->st_dbb_env_param_ctx.s_ant_power           = 0;
    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = 0;
    pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_clear_usr_queue_stat
 功能描述  : 清零用户队列统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_clear_usr_queue_stat(dmac_user_stru  *pst_dmac_user)
{
    oal_uint8    uc_tid_no;

    /* 清零节能队列统计信息 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->st_ps_structure.pst_psm_stats
        || OAL_PTR_NULL == pst_dmac_user->st_uapsd_stru.pst_uapsd_statis))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_clear_usr_queue_stat::ps stats is null! psm=[%d],uapsd=[%d].}",
                       (oal_uint32)pst_dmac_user->st_ps_structure.pst_psm_stats,
                       (oal_uint32)pst_dmac_user->st_uapsd_stru.pst_uapsd_statis);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(pst_dmac_user->st_ps_structure.pst_psm_stats, OAL_SIZEOF(dmac_user_psm_stats_stru));
    OAL_MEMZERO(pst_dmac_user->st_uapsd_stru.pst_uapsd_statis, OAL_SIZEOF(dmac_usr_uapsd_statis_stru));

    /* 清零tid队列统计信息 */
    for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_clear_usr_queue_stat::pst_tid_stats is null.tid_no=[%d].}",
                           uc_tid_no);
            return OAL_ERR_CODE_PTR_NULL;
        }

        OAL_MEMZERO(pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats, OAL_SIZEOF(dmac_tid_stats_stru));
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_usr_queue_stat
 功能描述  : 上报用户队列统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_report_usr_queue_stat(dmac_user_stru  *pst_dmac_user)
{
    oam_stats_usr_queue_stat_stru       st_usr_queue_stats;
    oal_uint8                           uc_tid_no;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->st_ps_structure.pst_psm_stats
        || OAL_PTR_NULL == pst_dmac_user->st_uapsd_stru.pst_uapsd_statis))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_report_usr_queue_stat::ps stats is null! psm=[%d],uapsd=[%d].}",
                       (oal_uint32)pst_dmac_user->st_ps_structure.pst_psm_stats,
                       (oal_uint32)pst_dmac_user->st_uapsd_stru.pst_uapsd_statis);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_usr_queue_stats, OAL_SIZEOF(oam_stats_usr_queue_stat_stru));

    /* 获取用户uapsd队列下的统计信息 */
    oal_memcopy(st_usr_queue_stats.aul_uapsd_stat,
                pst_dmac_user->st_uapsd_stru.pst_uapsd_statis,
                OAL_SIZEOF(oal_uint32) * OAM_UAPSD_STAT_CNT);

    /* 获取用户psm队列下的统计信息 */
    oal_memcopy(st_usr_queue_stats.aul_psm_stat,
                pst_dmac_user->st_ps_structure.pst_psm_stats,
                OAL_SIZEOF(oal_uint32) * OAM_PSM_STAT_CNT);

    /* 获取用户tid队列下的统计信息 */
    for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_report_usr_queue_stat::tid_stats is null! tid_no=[%d].}", uc_tid_no);
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_memcopy(&st_usr_queue_stats.aul_tid_stat[uc_tid_no][0],
                    pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats,
                    OAL_SIZEOF(oal_uint32) * OAM_TID_STAT_CNT);
    }

    return oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                 (oal_uint8 *)&st_usr_queue_stats,
                                 (oal_uint16)OAL_SIZEOF(oam_stats_usr_queue_stat_stru),
                                 OAM_OTA_TYPE_USR_QUEUE_STAT);
}

/*****************************************************************************
 函 数 名  : dmac_dft_mgmt_stat_incr
 功能描述  : 管理帧统计计数加1
 输入参数  : puc_mac_hdr_addr: 帧头地址
             en_type         : 统计类型(位置:发送，发送完成，接收)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月1日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type)
{
    oal_uint8           uc_subtype;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_mac_hdr_addr || OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::param is null. puc_mac_hdr_addr = [%d],\
                       mac_dev = [%d]}", puc_mac_hdr_addr, pst_mac_dev);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_DEV_MGMT_STAT_TYPE_BUTT <= en_type)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::en_type exceeds! en_type = [%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_MANAGEMENT == mac_frame_get_type_value(puc_mac_hdr_addr))
    {
        uc_subtype = mac_frame_get_subtype_value(puc_mac_hdr_addr);
        if (uc_subtype >= WLAN_MGMT_SUBTYPE_BUTT)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::uc_subtype exceeds! uc_subtype = [%d].}",
                           uc_subtype);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        switch (en_type)
        {
            case MAC_DEV_MGMT_STAT_TYPE_TX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_soft[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_RX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_rx_mgmt[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_TX_COMPLETE:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_hardware[uc_subtype]);
            break;

            default:
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_get_machw_stat_info
 功能描述  : 从mac寄存器获取收发包数目统计值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev || OAL_PTR_NULL == pst_machw_stat))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_get_machw_stat_info:: pst_dev = [%d], \
                       pst_machw_stat = [%d]}", pst_dev, pst_machw_stat);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 依次读取MAC 的收发包数目统计寄存器 */
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_AMPDU_COUNT_REG, &pst_machw_stat->ul_machw_rx_ampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PASSED_MPDU_IN_AMPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_passed_mpdu_in_ampdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FAILED_MPDU_IN_AMPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_failed_mpdu_in_ampdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_OCTECTS_IN_AMPDU_REG, &pst_machw_stat->ul_machw_rx_octects_in_ampdu);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_DELIMIT_FAIL_COUNT_REG, &pst_machw_stat->ul_machw_rx_delimit_fail_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_DUP_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_dup_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PASSED_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_passed_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FAILED_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_failed_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_BCN_CNT_REG, &pst_machw_stat->ul_machw_rx_bcn_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_ERR_MAC_PASSED_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_err_mac_passed_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_LONGER_ERR_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_longer_err_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_SHORTER_ERR_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_shorter_err_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FILTERED_CNT_REG, &pst_machw_stat->ul_machw_rx_filtered_cnt);

    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, &pst_machw_stat->ul_machw_tx_hi_pri_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_NORMAL_PRI_MPDU_CNT_REG, &pst_machw_stat->ul_machw_tx_normal_pri_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_AMPDU_COUNT_REG, &pst_machw_stat->ul_machw_tx_ampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_MPDU_INAMPDU_COUNT_REG, &pst_machw_stat->ul_machw_tx_mpdu_inampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_OCTECTS_IN_AMPDU_REG, &pst_machw_stat->ul_machw_tx_octects_in_ampdu);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_BCN_COUNT_REG, &pst_machw_stat->ul_machw_tx_bcn_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_NORMAL_PRI_RETRY_CNT_REG, &pst_machw_stat->ul_machw_tx_normal_pri_retry_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_HI_PRI_RETRY_CNT_REG, &pst_machw_stat->ul_machw_tx_hi_pri_retry_cnt);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_dft_report_all_ota_state
 功能描述  : 通过OTA上报统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月8日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta)
{
}

oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch)
{
    /* TBD */
}

#endif
#if 0
/*****************************************************************************
 函 数 名  : dmac_dft_report_vap_stat
 功能描述  : 周期上报vap吞吐统计信息超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_vap_stat(oal_void *p_arg)
{
    mac_vap_stru            *pst_mac_vap;
    oam_stats_vap_stat_stru  st_vap_dft_stats;
    oal_uint8                auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_vap = (mac_vap_stru  *)p_arg;

    OAL_MEMZERO(&st_vap_dft_stats, OAL_SIZEOF(oam_stats_vap_stat_stru));

    /* 先停止统计 */
    pst_mac_vap->st_vap_dft.ul_flg = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap->st_vap_dft.pst_vap_dft_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_vap_stat:: vap_dft_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&st_vap_dft_stats,
                pst_mac_vap->st_vap_dft.pst_vap_dft_stats,
                OAL_SIZEOF(mac_vap_dft_stats_stru));
    OAL_MEMZERO(pst_mac_vap->st_vap_dft.pst_vap_dft_stats, OAL_SIZEOF(mac_vap_dft_stats_stru));

    /* 计算5个平均速率,单位是 kbps，上报周期是2s */
    st_vap_dft_stats.ul_lan_tx_rate = st_vap_dft_stats.ul_lan_tx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_drv_tx_rate = st_vap_dft_stats.ul_drv_tx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_hw_tx_rate  = st_vap_dft_stats.ul_hw_tx_bytes  / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_drv_rx_rate = st_vap_dft_stats.ul_drv_rx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_lan_rx_rate = st_vap_dft_stats.ul_lan_rx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;

    pst_mac_vap->st_vap_dft.ul_flg = OAL_TRUE;

    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_vap_dft_stats, OAM_OTA_TYPE_VAP_STAT);
}


/*****************************************************************************
 函 数 名  : dmac_dft_start_report_vap_stat
 功能描述  : 开始统计vap吞吐统计信息，并启动定时器周期上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_start_report_vap_stat(mac_vap_stru *pst_mac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 置标志位，业务流程开始统计 */
    pst_mac_vap->st_vap_dft.ul_flg = 1;

    /* 申请内存 */
    pst_mac_vap->st_vap_dft.pst_vap_dft_stats = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                              OAL_SIZEOF(mac_vap_dft_stats_stru),
                                                              OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap->st_vap_dft.pst_vap_dft_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::alloc fail.}");
        pst_mac_vap->st_vap_dft.ul_flg = 0;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    OAL_MEMZERO(pst_mac_vap->st_vap_dft.pst_vap_dft_stats, OAL_SIZEOF(mac_vap_dft_stats_stru));

    /* 启动周期上报定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_mac_vap->st_vap_dft.st_vap_dft_timer,
                           dmac_dft_report_vap_stat,
                           DMAC_DFT_REPORT_VAP_STAT_TIMEOUT,
                           (oal_void *)pst_mac_vap,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_vap->ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_stop_report_vap_stat
 功能描述  : 停止上报vap吞吐统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_vap_stat(mac_vap_stru *pst_mac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return mac_vap_dft_stat_clear(pst_mac_vap);
}
#endif
#endif
#ifdef  _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : dmac_dft_report_all_ampdu_stat
 功能描述  : 上报或者清零某一个用户所有tid下ampdu业务流程统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月27日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_report_all_ampdu_stat(dmac_user_stru  *pst_dmac_user,
                                                   oal_uint8        uc_param)
{
    oal_uint8                  uc_tid_no;
    dmac_tid_stru             *pst_tid;
    oam_stats_ampdu_stat_stru  st_ampdu_stat;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_all_ampdu_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == uc_param)
    {
        for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
        {
            pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_no];

            if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
            {
                OAL_MEMZERO(&st_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
                oal_memcopy(&st_ampdu_stat, pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));

                oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                      (oal_uint8 *)&st_ampdu_stat,
                                      (oal_uint16)OAL_SIZEOF(oam_stats_ampdu_stat_stru),
                                      OAM_OTA_TYPE_AMPDU_STAT);
            }

        }
    }
    else
    {
        for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
        {
            pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_no];

            if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
            {
                OAL_MEMZERO(pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
            }

        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_dft_report_ampdu_stat
 功能描述  : 上报获取清零某一个tid的ampdu业务流程统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月27日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dft_report_ampdu_stat(dmac_tid_stru  *pst_tid,
                                               oal_uint8      auc_macaddr[],
                                               oal_uint8      uc_param)
{
    oam_stats_ampdu_stat_stru  st_ampdu_stat;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_ampdu_stat::pst_tid is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == uc_param)
    {
        if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
        {
            OAL_MEMZERO(&st_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
            oal_memcopy(&st_ampdu_stat, pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));

            oam_report_dft_params(auc_macaddr,
                                  (oal_uint8 *)&st_ampdu_stat,
                                  (oal_uint16)OAL_SIZEOF(oam_stats_ampdu_stat_stru),
                                  OAM_OTA_TYPE_AMPDU_STAT);
        }


    }
    else
    {
        if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
        {
            OAL_MEMZERO(pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
        }
    }

    return OAL_SUCC;
}

#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

