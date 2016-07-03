#ifndef __ABB_INTERFACE_V200_H__
#define __ABB_INTERFACE_V200_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/



#include "wg_type_define.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/********************************** ABB寄存器地址 ***************************/

/********************************* 版本寄存器 *******************************/
#define HAL_ABB_WG_VERSION_LTE_ADDR     ( 0x80 )                                /* version寄存器 */

/********************************* 模式寄存器 *******************************/
#define HAL_ABB_WG_RX_2G_DIG_1_ADDR     ( 0x81 )                                /* RX 2g 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_2G_DIG_2_ADDR     ( 0x82 )                                /* RX 2g 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_2G_DIG_1_ADDR     ( 0x83 )                                /* TX 2g 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_2G_DIG_2_ADDR     ( 0x84 )                                /* TX 2g 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_3G_DIG_1_ADDR     ( 0x85 )                                /* RX 3g 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_3G_DIG_2_ADDR     ( 0x86 )                                /* RX 3g 模式配置寄存器2由线控决定是否起作用 */
#define HAL_ABB_WG_TX_3G_DIG_1_ADDR     ( 0x87 )                                /* TX 3g 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_3G_DIG_2_ADDR     ( 0x88 )                                /* TX 3g 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_4G_DIG_1_ADDR     ( 0x89 )                                /* RX 4G 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_4G_DIG_2_ADDR     ( 0x8A )                                /* RX 4G 模式配置寄存器2，，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_4G_DIG_1_ADDR     ( 0x8B )                                /* TX 4g 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_4G_DIG_2_ADDR     ( 0x8C )                                /* TX 4g 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_IDLE_DIG_1_ADDR   ( 0x8D )                                /* RX idle 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_RX_IDLE_DIG_2_ADDR   ( 0x8E )                                /* RX idle 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_IDLE_DIG_1_ADDR   ( 0x8F )                                /* TX idle 模式配置寄存器1，由线控决定是否起作用 */
#define HAL_ABB_WG_TX_IDLE_DIG_2_ADDR   ( 0x90 )                                /* TX idle 模式配置寄存器2，由线控决定是否起作用 */
#define HAL_ABB_WG_TESTMODE_ADDR        ( 0x91 )                                /* 调试用寄存器 */
#define HAL_ABB_WG_AD_OUT_CFG_ADDR      ( 0x92 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_DA_IN_CFG_ADDR       ( 0x93 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_RX_DELAY_ADDR        ( 0x94 )                                /* rx时钟delay选择 */
#define HAL_ABB_WG_LINE_CTRL_SEL_ADDR   ( 0x95 )                                /* LTE线控选择 */
#define HAL_ABB_WG_TX_I_OFFSET_ADDR     ( 0x96 )                                /* TX I通道offset */
#define HAL_ABB_WG_TX_Q_OFFSET_ADDR     ( 0x97 )                                /* TX Q通道offset */
#define HAL_ABB_WG_RXA_BLOCKING_ADDR    ( 0x98 )                                /* rxa blocking_output */
#define HAL_ABB_WG_RXB_BLOCKING_ADDR    ( 0x99 )                                /* rxb blocking_output */
#define HAL_ABB_WG_RX_2G_ANA_ADDR       ( 0x9A )                                /* RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00 */
#define HAL_ABB_WG_TX_2G_ANA_ADDR       ( 0x9B )                                /* TX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr01 */
#define HAL_ABB_WG_RX_3G_ANA_ADDR       ( 0x9C )                                /* RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00 */
#define HAL_ABB_WG_TX_3G_ANA_ADDR       ( 0x9D )                                /* TX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr01 */
#define HAL_ABB_WG_RX_4G_ANA_ADDR       ( 0x9E )                                /* RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00 */
#define HAL_ABB_WG_TX_4G_ANA_ADDR       ( 0x9F )                                /* TX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr01 */
#define HAL_ABB_WG_RX_IDLE_ANA_ADDR     ( 0xA0 )                                /* RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00 */
#define HAL_ABB_WG_TX_IDLE_ANA_ADDR     ( 0xA1 )                                /* TX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr01 */

/***************************** 控制寄存器 ***************************/
#define HAL_ABB_WG_REG_ANALOG_WR02_ADDR ( 0xA2 )                                /* Power Down控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR03_ADDR ( 0xA3 )                                /* ADC测试控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR04_ADDR ( 0xA4 )                                /* Other控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR05_ADDR ( 0xA5 )                                /* ADC第一级积分器电容tuning寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR06_ADDR ( 0xA6 )                                /* ADC第二级积分器电容tuning寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR07_ADDR ( 0xA7 )                                /* ADC第三级积分器电容tuning寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR08_ADDR ( 0xA8 )                                /* DAC Tuning控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR09_ADDR ( 0xA9 )                                /* DAC Tuning控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR10_ADDR ( 0xAA )                                /* DAC Tuning控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR11_ADDR ( 0xAB )                                /* 时钟模式控制寄存器    */
#define HAL_ABB_WG_REG_ANALOG_WR12_ADDR ( 0xAC )                                /* PLLV1控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR13_ADDR ( 0xAD )                                /* VCO1电流控制控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR14_ADDR ( 0xAE )                                /* PLLV1控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR15_ADDR ( 0xAF )                                /* PLLV2控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR16_ADDR ( 0xB0 )                                /* VCO2电流控制控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR17_ADDR ( 0xB1 )                                /* PLLV2控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR18_ADDR ( 0xB2 )                                /* AUX电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR19_ADDR ( 0xB3 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR20_ADDR ( 0xB4 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR21_ADDR ( 0xB5 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR22_ADDR ( 0xB6 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR23_ADDR ( 0xB7 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR24_ADDR ( 0xB8 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR25_ADDR ( 0xB9 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR26_ADDR ( 0xBA )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR27_ADDR ( 0xBB )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR28_ADDR ( 0xBC )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR29_ADDR ( 0xBD )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR30_ADDR ( 0xBE )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR31_ADDR ( 0xBF )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR32_ADDR ( 0xC0 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR33_ADDR ( 0xC1 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR34_ADDR ( 0xC2 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR35_ADDR ( 0xC3 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR36_ADDR ( 0xC4 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR37_ADDR ( 0xC5 )                                /* 电流控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_WR38_ADDR ( 0xC6 )                                /* 共模电平控制寄存器 */

/******************************* 数字数据控制寄存器 *****************************/
#define HAL_ABB_WG_REG_ANALOG_RO0_ADDR  ( 0xD0 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_RO1_ADDR  ( 0xD1 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_RO2_ADDR  ( 0xD2 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_RO3_ADDR  ( 0xD3 )                                /* 数字数据控制寄存器 */
#define HAL_ABB_WG_REG_ANALOG_RO4_ADDR  ( 0xD4 )                                /* 数字数据控制寄存器 */

/******************************* 数字调试寄存器 *****************************/
#define HAL_ABB_WG_REG_DEBUG_DIG0_ADDR  ( 0xD5 )                                /* 数字调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_DIG1_ADDR  ( 0xD6 )                                /* 数字调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_DIG2_ADDR  ( 0xD7 )                                /* 数字调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_DIG3_ADDR  ( 0xD8 )                                /* 数字调试寄存器 */

/******************************* 模拟调试寄存器 *****************************/
#define HAL_ABB_WG_REG_DEBUG_ANA0_ADDR  ( 0xD9 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA1_ADDR  ( 0xDA )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA2_ADDR  ( 0xDB )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA3_ADDR  ( 0xDC )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA4_ADDR  ( 0xDD )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA5_ADDR  ( 0xDE )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA6_ADDR  ( 0xDF )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA7_ADDR  ( 0xE0 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA8_ADDR  ( 0xE1 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA9_ADDR  ( 0xE2 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA10_ADDR ( 0xE3 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA11_ADDR ( 0xE4 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA12_ADDR ( 0xE5 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA13_ADDR ( 0xE6 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA14_ADDR ( 0xE7 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA15_ADDR ( 0xE8 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA16_ADDR ( 0xE9 )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA17_ADDR ( 0xEA )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA18_ADDR ( 0xEB )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA19_ADDR ( 0xEC )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA20_ADDR ( 0xED )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ANA21_ADDR ( 0xEE )                                /* 模拟调试寄存器 */
#define HAL_ABB_WG_REG_DEBUG_ARO0_ADDR  ( 0xEF )                                /* 模拟调试只读寄存器 */
#define HAL_ABB_REG_ABB_MODE_ADDR       ( 0xf0 )                                /* ABB双模多待指示寄存器 */



/*****************************************************************************
  3 枚举定义
******************************************************************************/

/*****************************************************************************
 枚举名    :
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/


/*****************************************************************************
 枚举名    :
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/





/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    :
 结构说明  :
*****************************************************************************/


/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
 联合名    : HAL_ABB_WG_RXA_BLOCKING_UNION
 联合说明  : WG_RXA_BLOCKING寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      coeff               : 5;                /* rxa blocking result = power * 2^coeff */
        PHY_UINT16                      power               : 3;
        PHY_UINT16                      reserved            : 8;
    }stReg;
}HAL_ABB_WG_RXA_BLOCKING_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_RXB_BLOCKING_UNION
 联合说明  : WG_RXB_BLOCKING寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      coeff               : 5;                /* rxb blocking result = power * 2^coeff */
        PHY_UINT16                      power               : 3;
        PHY_UINT16                      reserved            : 8;
    }stReg;
}HAL_ABB_WG_RXB_BLOCKING_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_AD_OUT_CFG_UNION
 联合说明  : 数字数据控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rx_sync_polarity    : 1;                /* 1'b0：rx_sync低有效  1'b1：rx_sync高有效 */
        PHY_UINT16                      rx_i_first          : 1;                /* 1'b0：Q路数据在前，I路数据在后 1'b1：I路数据在前，Q路数据在后 */
        PHY_UINT16                      rxbit_weight        : 1;                /* 1'b0：先奇后偶 1'b1：先偶后奇 */
        PHY_UINT16                      reserved0           : 1;                /* reserved */
        PHY_UINT16                      rx_dout_limit       : 1;                /* Rx 方向输出给DBB数据进行对称限幅控制 0：不进行对称限幅 1：进行对称限幅 */
        PHY_UINT16                      rx_clk_inv          : 1;                /* rx_clk输出反向控制 1'b0：rx_clk bypass输出 1'b1：rx_clk反向输出 */
        PHY_UINT16                      rx_clk_delay_bp     : 1;                /* 1'b0：rx_clk 输出delay 不bypass 1'b1：rx_clk 输出delay bypass */
        PHY_UINT16                      reserved1           : 9;                /* reserved */
    }stReg;
}HAL_ABB_WG_AD_OUT_CFG_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_DA_IN_CFG_UNION
 联合说明  : 数字数据控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      tx_sync_polarity    : 1;                /* 1'b0：tx_sync低有效  1'b1：tx_sync高有效 */
        PHY_UINT16                      tx_i_first          : 1;                /* 1'b0：Q路数据在前，I路数据在后 1'b1：I路数据在前，Q路数据在后 */
        PHY_UINT16                      txbit_weight        : 1;                /* 1'b0：先奇后偶 1'b1：先偶后奇 */
        PHY_UINT16                      Reserved1           : 1;                /* reserved */
        PHY_UINT16                      tx_din_limit        : 1;                /* 'Tx 方向DBB输入数据进行对称限幅控制 0：不进行对称限幅 1：进行对称限幅 */
        PHY_UINT16                      Reserved2           : 11;               /* reserved */
    }stReg;
}HAL_ABB_WG_DA_IN_CFG_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_I_OFFSET_UNION
 联合说明  : TX I通道offset
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      tx_i_offset         : 8;                /* tx_i通道dc offset设置 */
        PHY_UINT16                      Reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_TX_I_OFFSET_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_Q_OFFSET_UNION
 联合说明  : TX Q通道offset
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      tx_q_offset         : 8;                /* tx_q通道dc offset设置 */
        PHY_UINT16                      Reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_TX_Q_OFFSET_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_ANALOG_WR02_UNION
 联合说明  : Power Down控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      AUXDAC2_PD          : 1;                /* AUXDAC2 Power Down控制，受线控控制 0:Power On 1:Power Down（默认）*/
        PHY_UINT16                      AUXDAC1_PD          : 1;                /* AUXDAC1 Power Down控制，受线控控制 0:Power On 1:Power Down（默认） */
        PHY_UINT16                      PLL624_PD           : 1;                /* G PLLV2 Power Down控制 0:Power On 1:Power Down（默认） */
        PHY_UINT16                      PLL6144_PD          : 1;                /* W/L PLLV1 Power Down控制 0:Power On（默认） 1:Power Down */
        PHY_UINT16                      BIAS_PD             : 1;                /* BIAS Power Down控制 0:Power On 1:Power Down（默认） */
        PHY_UINT16                      REF_PD              : 1;                /* Reference Voltage Power Down 0:Power On 1:Power Down（默认） */
        PHY_UINT16                      FS                  : 1;                /* Fast start up mode 0:fast start up disable（默认） 1:fast start up enable */
        PHY_UINT16                      reserved            : 9;                /* reserved */
    }stReg;
}HAL_ABB_WG_REG_ANALOG_WR02_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_ANALOG_WR03_UNION
 联合说明  : ADC测试控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      Reserved            : 3;                /* Reserved */
        PHY_UINT16                      TX_CLKD_CTRL        : 1;                /* TX 采样时钟沿选择 0: 正沿 1: 反沿（默认） */
        PHY_UINT16                      CLK_61D44M_PD       : 1;                /* CLK_61D44M Power Down控制 0:Power On 1:Power Down（默认）*/
        PHY_UINT16                      CLK_52M_PD          : 1;                /* CLK_52M Power Down控制 0:Power On 1:Power Down（默认） */
        PHY_UINT16                      RX_CLK2D_CTRL       : 1;                /* ADC采样沿控制：0: 正沿 1: 反沿（默认） */
        PHY_UINT16                      ORDER_CTRL          : 1;                /* ADC阶数控制：0: 3阶（默认）1: 2阶 */
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_REG_ANALOG_WR03_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_ANALOG_WR38_UNION
 联合说明  : 共模电平控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      Reserved            : 3;                /* Reserved */
        PHY_UINT16                      OFFSET_CAL_DAC_EN   : 1;                /* TX adc offset calibration enable output 1 enable; 0 disable（默认）*/
        PHY_UINT16                      SARADC_REF_RANGE    : 1;                /* 0 the sar ref range is 2.5V（默认） 1 the sar ref range is 1.65v*/
        PHY_UINT16                      TX_CM_CON_MODE      : 2;                /* sink rf current value                              '00  28uA  gsm(low gain)                                01  32uA  gsm(high gain)                                10  48uA  wcdma                                  11   0     pwr down the wg circuits（默认） */
        PHY_UINT16                      RX_ADC_CM_CON_EN    : 1;                /* RX_ADC_CM_CON_EN使能控制 0:下拉共模电平无效（默认）1:下拉共模电平有效 */
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_REG_ANALOG_WR38_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_ANALOG_WR04_UNION
 联合说明  : 'Other控制寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      EN_CAL              : 1;                /* Calibration enable（默认为0）上升沿启动Calibration过程 */
        PHY_UINT16                      CAL_PD              : 1;                /* CAL Power Down控制0:Power On 1:Power Down（默认） */
        PHY_UINT16                      TX_AUTO_TUNE        : 1;                /* TX ADC自动tuning控制 0：手动tuning，tuning选择TX_TUNE1,TX_TUNE2,TX_TUNE3的值（默认） 1：自动tuning，TX通道的calibration值为CAL_VALUE*/
        PHY_UINT16                      RX_AUTO_TUNE        : 1;                /* RX ADC自动tuning控制0：手动tuning，tuning选择RX_TUNE1,RX_TUNE2,RX_TUNE3的值（默认）1：自动tuning，RX通道的calibration值为CAL_VALUE */
        PHY_UINT16                      reserved            : 12;               /* reserved */
    }stReg;
}HAL_ABB_WG_REG_ANALOG_WR04_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_RX_3G_DIG_1_UNION
 联合说明  : 'RX 3g 模式配置寄存器1，由线控决定是否起作用
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rx_comp_bp          : 1;                /* RX通道补偿滤波器bypass控制：0：不bypass（默认）1：bypass */
        PHY_UINT16                      rx_comp_sel         : 1;                /* RX补偿滤波器选择：0：2G/4G补偿滤波器1：3G补偿滤波器 */
        PHY_UINT16                      rx_hb_bp            : 1;                /* RX通道半带滤波器的bypass信号0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认）1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        PHY_UINT16                      rx_rate             : 2;                /* RX 速率控制：'RX CIC滤波器输出速率控制：    2G，     3G_SC，     4G，   3G_DC
                                                                                    0 2.167MHz,15.36MHz, 61.44MHz, 30.72MHz（默认）
                                                                                    1 --------,--------, 30.72MHz, 15.36MHz
                                                                                    2 --------,---------,15.36MHz,----------
                                                                                    3  ------ ,---------, 7.68MHz,----------*/

        PHY_UINT16                      rx_mode_dig         : 2;                /* RX模式控制：00：2G 01：3G（默认）10：4G 11：3G_DC */
        PHY_UINT16                      reserved            : 9;                /* reserved */
    }stReg;
}HAL_ABB_WG_RX_3G_DIG_1_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_2G_DIG_1_UNION
 联合说明  : TX 2g 模式配置寄存器1，由线控决定是否起作用
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      tx_pd               : 1;                /*  */
        PHY_UINT16                      tx_comp_bp          : 1;                /*  */
        PHY_UINT16                      tx_hb_bp            : 1;                /*  */
        PHY_UINT16                      tx_rate             : 3;                /* */

        PHY_UINT16                      tx_mode_dig         : 2;                /*  */
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_TX_2G_DIG_1_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_WG_RX_3G_ANA_UNION
 联合说明  : RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      DEM_EN              : 1;                /* ADC DEM Bypass控制：0: Bypass1: 正常工作（默认） */
        PHY_UINT16                      RX_MODE_CLK         : 2;                /* 模式控制：00：4G01：3G（默认）10：3G_DC11：2G */
        PHY_UINT16                      RX_MODE_ANA         : 1;                /* ADC Mode 选则：0: LTE1: 2G/3G（默认）*/
        PHY_UINT16                      RXB_Q_PD            : 1;                /* RXB_Q ADC Power Down控制0:Power On1:Power Down（默认）(!RXB_Q_PD)|W_RXB_EN = 1时工作，否则关闭 */
        PHY_UINT16                      RXB_I_PD            : 1;                /* RXB_I ADC Power Down控制0:Power On1:Power Down（默认）(!RXB_I_PD)|W_RXB_EN = 1时工作，否则关闭 */
        PHY_UINT16                      RXA_Q_PD            : 1;                /* RXA_Q ADC Power Down控制0:Power On1:Power Down（默认）(!RXA_Q_PD)|W_RXA_EN = 1时工作，否则关闭 */
        PHY_UINT16                      RXA_I_PD            : 1;                /* RXA_I ADC Power Down控制0:Power On1:Power Down（默认）(!RXA_I_PD)|W_RXA_EN = 1时工作，否则关闭 */
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_RX_3G_ANA_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_RX_IDLE_ANA_UNION
 联合说明  : RX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr00
*****************************************************************************/
typedef HAL_ABB_WG_RX_3G_ANA_UNION      HAL_ABB_RX_IDLE_ANA_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_LINE_CTRL_SEL_UNION
 联合说明  : LTE线控选择
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      g_en_sel            : 1;                /* 0: tie to 0 1: from line control */
        PHY_UINT16                      w_en_sel            : 1;                /* 0: tie to 0 1: from line control */
        PHY_UINT16                      lte_en_sel          : 1;                /* 0: tie to 0 1: from line control */
        PHY_UINT16                      reserved            : 15;               /* reserved */
    }stReg;
}HAL_ABB_WG_LINE_CTRL_SEL_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_2G_ANA_UNION
 联合说明  : TX Mode控制寄存器，经过线控逻辑后后送至reg_analog_wr01
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      TX_MODE_CLK         : 2;                /* "模式控制：00：4G01：3G10：--11：2G（默认）"*/
        PHY_UINT16                      TX_MODE_ANA         : 1;                /* Reserved */
        PHY_UINT16                      TX_Q_PD             : 1;                /* "TX_Q DAC Power Down控制0:Power On1:Power Down（默认） */
        PHY_UINT16                      TX_I_PD             : 1;                /* "TX_I DAC Power Down控制0:Power On1:Power Down（默认） */
        PHY_UINT16                      TX_DIV_MODE         : 2;                /* "TX Mode 时钟控制：00: 1分频（默认）01: 2分频10: 3分频11: 4分频" */
        PHY_UINT16                      FC                  : 1;
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_TX_2G_ANA_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_ANALOG_RO0_UNION
 联合说明  : 读取校准是否完成
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      CAL_CNT             : 5;
        PHY_UINT16                      CAL_DONE            : 1;
        PHY_UINT16                      LOCK2               : 1;
        PHY_UINT16                      LOCK1               : 1;
        PHY_UINT16                                          : 8;
    }stReg;
}HAL_ABB_WG_REG_ANALOG_RO0_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_3G_DIG_1_UNION
 联合说明  : 3G Tx Dig寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      tx_pd               : 1;                /*  */
        PHY_UINT16                      tx_comp_bp          : 1;                /*  */
        PHY_UINT16                      tx_hb_bp            : 1;                /*  */
        PHY_UINT16                      tx_rate             : 3;                /* */
        PHY_UINT16                      tx_mode_dig         : 2;                /*  */
        PHY_UINT16                      reserved            : 8;                /* reserved */
    }stReg;
}HAL_ABB_WG_TX_3G_DIG_1_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_4G_DIG_1_UNION
 联合说明  : 4G Tx Dig寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_3G_DIG_1_UNION    HAL_ABB_WG_TX_4G_DIG_1_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_4G_DIG_1_UNION
 联合说明  : Tx Idle Dig1寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_3G_DIG_1_UNION    HAL_ABB_TX_IDLE_DIG_1_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_3G_DIG_1_UNION
 联合说明  : 3G Tx Dig寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      TX_MODE_CLK         : 2;                /* "模式控制：00：4G01：3G10：--11：2G（默认）"*/
        PHY_UINT16                      TX_MODE_ANA         : 1;                /* Reserved */
        PHY_UINT16                      TX_Q_PD             : 1;                /* "TX_Q DAC Power Down控制0:Power On1:Power Down（默认） */
        PHY_UINT16                      TX_I_PD             : 1;                /* "TX_I DAC Power Down控制0:Power On1:Power Down（默认） */
        PHY_UINT16                      TX_DIV_MODE         : 2;                /* "TX Mode 时钟控制：00: 1分频（默认）01: 2分频10: 3分频11: 4分频" */
        PHY_UINT16                      FC                  : 1;                /* reserved */
        PHY_UINT16                                          : 8;
    }stReg;
}HAL_ABB_WG_TX_3G_ANA_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_4G_DIG_1_UNION
 联合说明  : 4G Tx Dig寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_3G_ANA_UNION      HAL_ABB_WG_TX_4G_ANA_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_TX_IDLE_ANA_UNION
 联合说明  : Tx IDle Ana寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_3G_ANA_UNION HAL_ABB_TX_IDLE_ANA_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_2G_DIG_2_UNION
 联合说明  : 2G Tx Dig 2 寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      dem_const           : 3;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      tx_ddr_sdr          : 1;                /* "1'b0：SDR 1'b1：DDR" */
        PHY_UINT16                      dem_prg_en          : 1;                /* "TX DEM中PRG控制：0：DEM不进行PRG（默认）1：DEM进行PRG" */
        PHY_UINT16                      dem_dwa_en          : 1;                /* "TX DEM中DWA模式控制：0：DEM不使用DWA模式（默认）1：DEM使用DWA模式 " */
        PHY_UINT16                      lsb_dem_bp          : 1;                /* "LSB 'TX DEM中bypass：0：DEM打开（默认）1：DEM bypass" */
        PHY_UINT16                      msb_dem_bp          : 1;                /* TX DEM中bypass：0：DEM打开（默认）1：DEM bypass" */
    }stReg;
}HAL_ABB_WG_TX_2G_DIG_2_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_3G_DIG_2_UNION
 联合说明  : 3G Tx Dig 2 寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_2G_DIG_2_UNION    HAL_ABB_WG_TX_3G_DIG_2_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_TX_4G_DIG_2_UNION
 联合说明  : 4G Tx Dig 2 寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_2G_DIG_2_UNION    HAL_ABB_WG_TX_4G_DIG_2_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_TX_IDLE_DIG_2_UNION
 联合说明  : Tx Idle Dig 2 寄存器
*****************************************************************************/
typedef HAL_ABB_WG_TX_2G_DIG_2_UNION    HAL_ABB_TX_IDLE_DIG_2_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_WG_RX_4G_DIG_1_UNION
 联合说明  : 4G Rx Dig 1 寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rx_comp_bp          : 1;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      rx_comp_sel         : 1;                /* "1'b0：SDR 1'b1：DDR" */
        PHY_UINT16                      rx_hb_bp            : 1;                /* "TX DEM中PRG控制：0：DEM不进行PRG（默认）1：DEM进行PRG" */
        PHY_UINT16                      rx_rate             : 2;                /* "TX DEM中DWA模式控制：0：DEM不使用DWA模式（默认）1：DEM使用DWA模式 " */
        PHY_UINT16                      rx_mode_dig         : 2;                /* "LSB 'TX DEM中bypass：0：DEM打开（默认）1：DEM bypass" */
    }stReg;
}HAL_ABB_WG_RX_4G_DIG_1_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_REG_ANALOG_WR18_UNION
 联合说明  : REG_ANALOG_WR18寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                                          : 2;
        PHY_UINT16                      IB_AUXVCM           : 2;                /*  "AUXDAC电流控制:00:4u 01:5u 10:6u 11:7u" */
        PHY_UINT16                      IB_AUXVBP           : 2;                /* "AUXDAC电流控制:00:4u 01:5u 10:6u 11:7u" */
        PHY_UINT16                      IB_AUXI2V           : 2;                /* "AUXDAC电流控制:00:4u 01:5u 10:6u 11:7u */
    }stReg;
}HAL_ABB_REG_ANALOG_WR18_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_REG_ANALOG_WR37_UNION
 联合说明  : REG_ANALOG_WR37寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      ADJ26               : 3;
        PHY_UINT16                                          : 1;
        PHY_UINT16                      ADJ25               : 3;
        PHY_UINT16                                          : 1;
    }stReg;
}HAL_ABB_REG_ANALOG_WR37_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA6_UNION
 联合说明  : 模拟调试 寄存器6
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      TCXO_RSVD           : 7;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      HLOD_BG             : 1;                /* "1'b0：SDR 1'b1：DDR" */
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA6_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA15_UNION
 联合说明  : 模拟调试 寄存器15
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      CLKGEN_DELAY        : 8;                /* TX DEM const系数（默认为0）*/
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA15_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA20_UNION
 联合说明  : 模拟调试 寄存器20
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      Reserved            : 4;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      EXT_BG_EN           : 1;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      CAP_MULT            : 2;                /* TX DEM const系数（默认为0）*/
        PHY_UINT16                      CAP_SEL             : 1;                /* TX DEM const系数（默认为0）*/
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA20_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_TESTMODE_UNION
 联合说明  : TESTMODE寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rx_code_sel         : 1;                /*  "RX模拟测试模式下编码选择：*/
        PHY_UINT16                      rx_chnl_sel         : 2;                /*"RX模拟测试模式下通道选择：*/
        PHY_UINT16                      test_mode           : 3;                /*  "测试模式控制：*/
        PHY_UINT16                      sw_rst              : 1;                /*  "配置的软复位信号：0：软件不启动软复位（默认）1：软件启动软复位" */
        PHY_UINT16                      pad_ds              : 1;
        PHY_UINT16                                          : 8;
    }stReg;
}HAL_ABB_TESTMODE_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_TESTMODE_UNION
 联合说明  : TESTMODE寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rxa_pd              : 1;                /*  "RX模拟测试模式下编码选择：*/
        PHY_UINT16                      rxb_pd              : 1;                /*"RX模拟测试模式下通道选择：*/
        PHY_UINT16                      gain_sel            : 2;                /*  "测试模式控制：*/
        PHY_UINT16                      rx_ddr_sdr          : 1;                /*  "配置的软复位信号：0：软件不启动软复位（默认）1：软件启动软复位" */
        PHY_UINT16                      Reserved            : 3;
        PHY_UINT16                                          : 8;
    }stReg;
}HAL_ABB_WG_RX_4G_DIG_2_UNION;

/*****************************************************************************
 联合名    : HAL_ABB_REG_ABB_MODE_UNION
 联合说明  : ABB双模多待指示寄存器
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      rx_sel              : 2;                /* rx */
        PHY_UINT16                      tx_sel              : 2;                /* tx */
        PHY_UINT16                      reserved1           : 12;               /* reserved */
    }stReg;
}HAL_ABB_REG_ABB_MODE_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_RX_2G_ANA_UNION
 联合说明  : 模拟调试 寄存器6
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      DEM_MOD_B0          : 1;                /* RX DEM Mode Selection,bit 0 */
        PHY_UINT16                      RX_MODE_CLK         : 2;                /* 模式控制 00:4G;01:3G;10:3G_DC;11:2G(默认) */
        PHY_UINT16                      DEM_MOD_B1          : 1;                /* RX DEM Mode Selection,bit 1 */
        PHY_UINT16                      RXB_Q_PD            : 1;                /* RXB_Q ADC Power Down控制 */
        PHY_UINT16                      RXB_I_PD            : 1;                /* RXB_I ADC Power Down控制 */
        PHY_UINT16                      RXA_Q_PD            : 1;                /* RXA_Q ADC Power Down控制 */
        PHY_UINT16                      RXA_I_PD            : 1;                /* RXA_I ADC Power Down控制 */
        PHY_UINT16                      reserved1           : 8;                /* 保留 */
    }stReg;
}HAL_ABB_WG_RX_2G_ANA_UNION;



/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA10_UNION
 联合说明  : 模拟调试 寄存器6
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      DAC_DUM_B1          : 1;                /* RX方向sub_DAC Dummy单元控制,DAC2 */
        PHY_UINT16                      DAC_DUM_B2          : 1;                /* RX方向sub_DAC Dummy单元控制,DAC3 */
        PHY_UINT16                      ADC_PUP_CTRL0       : 1;                /* ADC中第一级积分器电容复位控制 */
        PHY_UINT16                      ADC_PUP_CTRL1       : 1;                /* ADC中第二级积分器电容复位控制 */
        PHY_UINT16                      ADC_PUP_CTRL2       : 1;                /* ADC中第三级积分器电容复位控制 */
        PHY_UINT16                      ADC_PUP_CTRL3       : 1;                /* ADC中CKGEN模块Powerup控制 */
        PHY_UINT16                      ADC_PUP_CTRL4       : 1;                /* ADC中OP模块Powerup控制 */
        PHY_UINT16                      ADC_PUP_CTRL5       : 1;                /* ADC中DAC模块Powerup控制 */
        PHY_UINT16                      reserved1           : 8;                /* 保留 */
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA10_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA15_V220_UNION
 联合说明  : 模拟调试 寄存器6
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      Reserved            : 2;                /* 保留 */
        PHY_UINT16                      QT_DELAY            : 2;                /* 量化器时钟延迟寄存器 */
        PHY_UINT16                      DAC3_DELAY          : 2;                /* DAC3时钟延迟寄存器 */
        PHY_UINT16                      DAC12_DELAY         : 2;                /* DAC1和DAC2时钟延迟寄存器 */
        PHY_UINT16                      reserved1           : 8;                /* 保留 */
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA15_V220_UNION;


/*****************************************************************************
 联合名    : HAL_ABB_WG_REG_DEBUG_ANA7_UNION
 联合说明  : 模拟调试 寄存器6
*****************************************************************************/
typedef union
{
    PHY_UINT16                          uhwValue;

    struct
    {
        PHY_UINT16                      DRVBUF_CT           : 3;                /* L/W/G 共用ADC 差分Buffer电流调节控制 */
        PHY_UINT16                      IREF_CTRL           : 3;                /* 基带参考电流控制 */
        PHY_UINT16                      reserved1           : 10;               /* 保留 */
    }stReg;
}HAL_ABB_WG_REG_DEBUG_ANA7_UNION;








/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/




/*****************************************************************************
  10 函数声明
*****************************************************************************/











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /*  */

