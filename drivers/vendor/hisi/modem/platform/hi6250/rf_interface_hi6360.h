#ifndef __RFINTERFACE_H_
#define __RFINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_interface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/************************** RF寄存器地址 ************************************/
/******************** Transceiver Operational Control ***********************/
#define HAL_RF_TDD_CONFIG1_ADDR_HI6360                             ( 0x00 )            /* TDD Datapath Configuration */
#define HAL_RF_TDD_CONFIG2_ADDR_HI6360                             ( 0x01 )            /* TDD Datapath Configuration */
#define HAL_RF_FDD_TX_CONFIG_ADDR_HI6360                           ( 0x02 )            /* FDD TX Operational Mode and Band Selection */
#define HAL_RF_TX_AGC_ADDR_HI6360                                  ( 0x03 )            /* TX Gain Control */
#define HAL_RF_FDD_RX_CONFIG_ADDR_HI6360                           ( 0x04 )            /* FDD RX Datapath Configuration */
#define HAL_RF_RX_MAIN_AGC_ADDR_HI6360                             ( 0x05 )            /* RX Main Gain Control */
#define HAL_RF_RX_DVTY_AGC_ADDR_HI6360                             ( 0x06 )            /* RXIF Diversity Gain Control */
#define HAL_RF_RX_MAIN_DCOC_VALUE_ADDR_HI6360                      ( 0x07 )            /* RX Main DCOC Offset/Correction Value */
#define HAL_RF_RX_DVTY_DCOC_VALUE_ADDR_HI6360                      ( 0x08 )            /* RX Diversity DCOC Offset/Correction Value */
#define HAL_RF_RX_MAIN_IIP2_CAL_ADDR_HI6360                        ( 0x09 )            /* RX Main IIP2 Calibration */
#define HAL_RF_RX_DVTY_IIP2_CAL_ADDR_HI6360                        ( 0x0A )            /* RX Diversity IIP2 Calibration */
#define HAL_RF_CFIX_ADDR_HI6360                                    ( 0x0B )            /* RF CFIX */
#define HAL_RF_REG10H_ADDR_HI6360                                  ( 0x10 )
#define HAL_RF_REG11H_ADDR_HI6360                                  ( 0x11 )
#define HAL_RF_TX_FEEDBACK_CONTROL_ADDR_HI6360                     ( 0x12 )            /* TX Feeedback control register  */
#define HAL_RF_TX_FEEDBACK_DATA_1_ADDR_HI6360                      ( 0x13 )            /* TX Feedback ADC readback data */
#define HAL_RF_OPERATING_BANDGROUP_ADDR_HI6360                     ( 0x14 )            /* Transceiver Operating Band */
#define HAL_RF_RX_TX_TUNING_ADDR_HI6360                            ( 0x15 )            /* RX / TX Datapath Tuning */
#define HAL_RF_XO_AFC_CTL_ADDR_HI6360                              ( 0x16 )            /* XTAL Frequency Calibration  */
#define HAL_RF_RXRF_LNA_CTUNE_LUT_LB_ADDR_HI6360                   ( 0x17 )            /* LNA Input Capacitor Tuning Look Up Table 1 for Low Band RF */
#define HAL_RF_RXRF_LNA_CTUNE_LUT_HB_ADDR_HI6360                   ( 0x18 )            /* LNA Input Capacitor Tuning Look Up Table 1 for High Band RF */
#define HAL_RF_RXRF_LNA_CTUNE_LUT_UHB_ADDR_HI6360                  ( 0x19 )            /* LNA Input Capacitor Tuning Look Up Table 2 for UltraHigh Band RF */
#define HAL_RF_RXRF_TANKTUNE_LUT_ADDR_HI6360                       ( 0x1A )            /* RX Balun Tuning LUT */
#define HAL_RF_TXRF_LOADTUNE_LUT_1_ADDR_HI6360                     ( 0x1B )            /* TX Load  Tuning LUT */
#define HAL_RF_TXRF_LOADTUNE_LUT_2_ADDR_HI6360                     ( 0x1C )            /* TX Load  Tuning LUT */
#define HAL_RF_TXRF_LOADTUNE_LUT_3_ADDR_HI6360                     ( 0x1D )            /* TX Load  Tuning LUT */
#define HAL_RF_TXRF_LOADTUNE_LUT_4_ADDR_HI6360                     ( 0x1E )            /* TX Load  Tuning LUT */
#define HAL_RF_TXRF_LOADTUNE_LUT_5_ADDR_HI6360                     ( 0x1F )            /* TX Load  Tuning LUT */
#define HAL_RF_RFIC_IO_CTRL_ADDR_HI6360                            ( 0x20 )            /* RFIC Digital IO Control */

/********************  Transceiver Misc Controls ******************* *****/
#define HAL_RF_RFIC_CLK_CTRL_ADDR_HI6360                           ( 0x21 )            /* RFIC Clock Domain Control */
#define HAL_RF_GPIO_CTRL_ADDR_HI6360                               ( 0x22 )            /* GPIO control */
#define HAL_RF_GPIO_STATUS_ADDR_HI6360                             ( 0x23 )            /* GPIO Status */
#define HAL_RF_RFIC_DEBUG_CFG_ADDR_HI6360                          ( 0x24 )            /* RFIC Debug Controls */
#define HAL_RF_RFIC_CHIP_ID_ADDR_HI6360                            ( 0x25 )            /* Chip ID register */
#define HAL_RF_RFIC_PULSEGEN_ADDR_HI6360                           ( 0x26 )            /* Pulse generator for debug or other use */
#define HAL_RF_RFIC_TESTSEL1_ADDR_HI6360                           ( 0x27 )            /* Control IO muxing for TESTMUX */
#define HAL_RF_RFIC_TESTSEL2_ADDR_HI6360                           ( 0x28 )            /* Control IO muxing for Digital test mux which feeds the analog testmux */
#define HAL_RF_RFIC_TESTMUX_ADDR_HI6360                            ( 0x29 )            /* TESTMUX */
#define HAL_RF_RFIC_ANALOG_TESTMUX_ADDR_HI6360                     ( 0x2A )            /* Analog TestMux Select */

/********************  Top Calibration Control **************************/
#define HAL_RF_REXTCAL_CTRL_ADDR_HI6360                            ( 0x2B )            /* CAL_TOP BandGap and R-Cal Control  */
#define HAL_RF_REXTCAL_DATA_ADDR_HI6360                            ( 0x2C )            /* R-Cal Engine Status Bits (read-only) */
#define HAL_RF_RCCAL_CTRL_ADDR_HI6360                              ( 0x2D )            /* RC Calibration Control for RX and TX path */
#define HAL_RF_RCCAL_DATA_ADDR_HI6360                              ( 0x2E )            /* RC Calibration words to RX and TX path */

/******************** TDD Registers *************************************/
#define HAL_RF_TDD_2G_FSM_TIME_ADDR_HI6360                         ( 0x30 )            /* TDD Sequencer Timer Values for 2G Mode */
#define HAL_RF_TDD_3G4G_FSM_TIME_ADDR_HI6360                       ( 0x31 )             /* TDD Sequencer Timer Values for 3G/4G Mode */

/******************** TX Registers *************************************/
#define HAL_RF_TX_EN_ADDR_HI6360                                   ( 0x38 )            /* TX Debug Configuration : Enable & mode selection */
#define HAL_RF_TX_BIAS_CFG_ADDR_HI6360                             ( 0x39 )            /* TX Configuration : RF Tuned Circuit Control */
#define HAL_RF_TX_FSM_TIME_ADDR_HI6360                             ( 0x3A )            /* TX State Machine Timer Values */
#define HAL_RF_TX_DEBUG_CFG_ADDR_HI6360                            ( 0x3B )            /* TX Test Control and Debug Mode Override */
#define HAL_RF_TX_FEEDBACK_DEBUG_ADDR_HI6360                       ( 0x3C )            /* Non-user controls for the TX FB circuits */
#define HAL_RF_TX_SPARE_1_ADDR_HI6360                              ( 0x3D )            /* Spare register for TX Analog/RF control */
#define HAL_RF_TX_FEEDBACK_DEBUG1_ADDR_HI6360                      ( 0x3E )
#define HAL_RF_TX_FEEDBACK_DEBUG2_ADDR_HI6360                      ( 0x3F )
#define HAL_RF_TXRF_IQMOD_IBIAS_LUT_1_HI6360                       ( 0x41 )
#define HAL_RF_TXRF_IQMOD_IBIAS_LUT_2_HI6360                       ( 0x42 )
/****************** IRCAL Control **************************************/
#define HAL_RF_IRCAL_PHASE_CORRECTION_ADDR_HI6360                  ( 0x50 )            /* IRCAL phase correction values */

/****************** RX Registers **************************************/
#define HAL_RF_RX_DEBUG_ADDR_HI6360                                ( 0x60 )            /* RX Datapath Controls - Bandgap and LDO Enables */
#define HAL_RF_RX_CTRL_ADDR_HI6360                                 ( 0x61 )            /* RX Datapath Controls -  Mixer/DCOC */
#define HAL_RF_RX_LNA_ADDR_HI6360                                  ( 0X62 )
#define HAL_RF_RX_FREQUENCY_CONTROL_ADDR_HI6360                    ( 0x63 )            /* RX Frequency/Bandwidth Control */
#define HAL_RF_RX_2G_FSM_TIME_ADDR_HI6360                          ( 0x64 )            /* RX DC Offset Correction (RESERVED in Hi6360V110) */
#define HAL_RF_RX_3G4G_FSM_TIME_ADDR_HI6360                        ( 0x65 )            /* RX DC Offset Correction (RESERVED in Hi6360V110) */
#define HAL_RF_RX_MAIN_LNA_ADDR_HI6360                             ( 0x68 )            /* RXRF main path LNA settings */
#define HAL_RF_RX_MAIN_DCOC_OUT_ADDR_HI6360                        ( 0x69 )            /* The computed DC output offset of the I and Q channel of RX A (RESERVED in Hi6360V110) */
#define HAL_RF_RX_DVTY_LNA_ADDR_HI6360                             ( 0x70 )            /* RXRF Diversity path LNA settings */
#define HAL_RF_RX_DVTY_DCOC_OUT_ADDR_HI6360                        ( 0x71 )            /* The computed DC output offset of the I and Q channel of RX B (RESERVED in Hi6360V110) */
#define HAL_RF_RX_SPARE0_REG_ADDR_HI6360                           ( 0x78 )            /* RX Spare Register for analog use */
#define HAL_RF_RX_SPARE1_REG_ADDR_HI6360                           ( 0x79 )            /* RX Spare Register for digital use */

/****************** FNPLL-TX Registers ********************************/
#define HAL_RF_PLLTX_MODE_ADDR_HI6360                              ( 0x80 )            /* PLL Calibration/Mode Register  */
#define HAL_RF_PLLTX_FREQ1_ADDR_HI6360                             ( 0x81 )            /* TX Frequency Register 1 (must write FREQ2 to trigger data transfer to FREQ1 and FREQ2) */
#define HAL_RF_PLLTX_FREQ2_ADDR_HI6360                             ( 0x82 )            /* TX Frequency Register 2 (triggers write to both FREQ1 and FREQ2) */
#define HAL_RF_PLLTX_PWR_LDO_ADDR_HI6360                           ( 0x83 )            /* TX PLL LDO voltage selection field(s) */
#define HAL_RF_PLLTX_PWR_VCO_ADDR_HI6360                           ( 0x84 )            /* TX PLL VCO VReg Configuration */
#define HAL_RF_PLLTX_CTRL_FSM_ADDR_HI6360                          ( 0x85 )            /* TX PLL Sequencer Sub-Block Control */
#define HAL_RF_PLLTX_VCO_ATEMP_ADDR_HI6360                         ( 0x86 )            /* TX VCO ATEMP Mode Control Register  */
#define HAL_RF_PLLTX_CP_ADDR_HI6360                                ( 0x87 )            /* Tx Charge Pump settings */
#define HAL_RF_PLLTX_LPF_ADDR_HI6360                               ( 0x89 )            /* TX Loop filter switch control.  There are 5 switches in each loop filter.  0: Switch open, 1: Switch closed */
#define HAL_RF_PLLTX_CTL_ADDR_HI6360                               ( 0x8A )            /* TX PLL Loop Controller Configuration */
#define HAL_RF_PLLTX_RCCAL_ADDR_HI6360                             ( 0x8B )            /* Tx RC Calibration settings */
#define HAL_RF_PLLTX_CT_1_ADDR_HI6360                              ( 0x8C )            /* Tx Coarse tuning settings, register 1 */
#define HAL_RF_PLLTX_CT_2_ADDR_HI6360                              ( 0x8D )            /* TX Coarse tuning settings, register 2 */
#define HAL_RF_PLLTX_CT_3_ADDR_HI6360                              ( 0x8E )            /* TX Coarse tuning settings, register 3 */
#define HAL_RF_PLLTX_KVCAL_1_ADDR_HI6360                           ( 0x8F )            /* TX Kv calibration settings, register 1 */
#define HAL_RF_PLLTX_KVCAL_2_ADDR_HI6360                           ( 0x90 )            /* TX Kv calibration settings, register 2 */
#define HAL_RF_PLLTX_PHZ_SLIP_ADDR_HI6360                          ( 0x91 )            /* TX PLL Phase Slipper Control */
#define HAL_RF_PLLTX_CTC_ADDR_HI6360                               ( 0x92 )            /* TX PLL Coarse Tune Check Thresholds */
#define HAL_RF_PLLTX_WAIT_TIME_ADDR_HI6360                         ( 0x93 )            /* TX PLL WarmUp and Lock Times */
#define HAL_RF_PLLTX_TEST_1_ADDR_HI6360                            ( 0x98 )            /* PLL Test Mux and Feedback Control */
#define HAL_RF_PLLTX_TEST_2_ADDR_HI6360                            ( 0x99 )            /* PLL Control signals to pause the loop state machines at a specified state. */
#define HAL_RF_PLLTX_VCO_COUNT_RD_ADDR_HI6360                      ( 0xA0 )            /* TX LFSR BIST count readback */
#define HAL_RF_PLLTX_FREQERRFLAG_RD_ADDR_HI6360                    ( 0xA1 )            /* TX LFSR BIST frequency error flag */
#define HAL_RF_PLLTX_RC_VAL_RD_ADDR_HI6360                         ( 0xA2 )            /* Tx RC calibration values */
#define HAL_RF_PLLTX_KV_FREQ_RD_ADDR_HI6360                        ( 0xA3 )            /* TX Kv compensation F0 Frequency Measurement */
#define HAL_RF_PLLTX_KV_CP_VAL_RD_ADDR_HI6360                      ( 0xA4 )            /* Kv compensation result: charge pump value */
#define HAL_RF_PLLTX_CT_VAL_RD_ADDR_HI6360                         ( 0xA5 )            /* TX Coarse Tuning Result */
#define HAL_RF_PLLTX_RSM_STATE_RD_ADDR_HI6360                      ( 0xA6 )            /* PLL State Machine State */
#define HAL_RF_PLLTX_SPARE0_REG_ADDR_HI6360                        ( 0xA7 )            /* control register */

/****************** FNPLL-RX Registers ******************************/
#define HAL_RF_PLLRX_MODE_ADDR_HI6360                              ( 0xC0 )            /* PLL Calibration/Mode Register  */
#define HAL_RF_PLLRX_FREQ1_ADDR_HI6360                             ( 0xC1 )            /* RX Frequency Register 1 (must write FREQ2 to trigger data transfer to FREQ1 and FREQ2) */
#define HAL_RF_PLLRX_FREQ2_ADDR_HI6360                             ( 0xC2 )            /* RX Frequency Register 2 (triggers write to both FREQ1 and FREQ2) */
#define HAL_RF_PLLRX_PWR_LDO_ADDR_HI6360                           ( 0xC3 )            /* RX PLL LDO voltage selection field(s) */
#define HAL_RF_PLLRX_PWR_VCO_ADDR_HI6360                           ( 0xC4 )            /* RX PLL VCO VReg Configuration */
#define HAL_RF_PLLRX_CTRL_FSM_ADDR_HI6360                          ( 0xC5 )            /* RX PLL Sequencer Sub-Block Control */
#define HAL_RF_PLLRX_VCO_ATEMP_ADDR_HI6360                         ( 0xC6 )            /* RX Charge Pump settings */
#define HAL_RF_PLLRX_CP_ADDR_HI6360                                ( 0xC7 )            /* RX Charge Pump settings */
#define HAL_RF_PLLRX_LPF_ADDR_HI6360                               ( 0xC9 )            /* RX Loop filter switch control.  There are 5 switches in each loop filter.  0: Switch open, 1: Switch closed */
#define HAL_RF_PLLRX_CTL_ADDR_HI6360                               ( 0xCA )            /* RX PLL Loop Controller Configuration */
#define HAL_RF_PLLRX_RCCAL_ADDR_HI6360                             ( 0xCB )            /* RX RC Calibration settings */
#define HAL_RF_PLLRX_CT_1_ADDR_HI6360                              ( 0xCC )            /* RX coarse tuning settings, register 1 */
#define HAL_RF_PLLRX_CT_2_ADDR_HI6360                              ( 0xCD )            /* RX Coarse tuning settings, register 2 */
#define HAL_RF_PLLRX_CT_3_ADDR_HI6360                              ( 0xCE )            /* RX Coarse tuning settings, register 3 */
#define HAL_RF_PLLRX_KVCAL_1_ADDR_HI6360                           ( 0xCF )            /* RX Kv calibration settings, register 1 */
#define HAL_RF_PLLRX_KVCAL_2_ADDR_HI6360                           ( 0xD0 )            /* RX Kv calibration settings, register 2 */
#define HAL_RF_PLLRX_PHZ_SLIP_ADDR_HI6360                          ( 0xD1 )            /* TX PLL Phase Slipper Control */
#define HAL_RF_PLLRX_CTC_ADDR_HI6360                               ( 0xD2 )            /* RX PLL Coarse Tune Check Thresholds */
#define HAL_RF_PLLRX_WAIT_TIME_ADDR_HI6360                         ( 0xD3 )            /* RX PLL WarmUp and Lock Times */
#define HAL_RF_PLLRX_TEST_1_ADDR_HI6360                            ( 0xD8 )            /* PLL Test Mux and Feedback Control */
#define HAL_RF_PLLRX_TEST_2_ADDR_HI6360                            ( 0xD9 )            /* PLL Control signals to pause the loop state machines at a specified state. */
#define HAL_RF_PLLRX_VCO_COUNT_RD_ADDR_HI6360                      ( 0xE0 )            /* RX LFSR BIST count readback */
#define HAL_RF_PLLRX_FREQERRFLAG_RD_ADDR_HI6360                    ( 0xE1 )            /* RX LFSR BIST frequency error flag readback */
#define HAL_RF_PLLRX_RC_VAL_RD_ADDR_HI6360                         ( 0xE2 )            /* RX RC calibration values */
#define HAL_RF_PLLRX_KV_FREQ_RD_ADDR_HI6360                        ( 0xE3 )            /* RX Kv compensation F0 Frequency Measurement */
#define HAL_RF_PLLRX_KV_CP_VAL_RD_ADDR_HI6360                      ( 0xE4 )            /* Kv compensation result: charge pump value */
#define HAL_RF_PLLRX_CT_VAL_RD_ADDR_HI6360                         ( 0xE5 )            /* RX Coarse Tuning Result */
#define HAL_RF_PLLRX_RSM_STATE_RD_ADDR_HI6360                      ( 0xE6 )            /* PLL State Machine State */
#define HAL_RF_PLLRX_SPARE0_REG_ADDR_HI6360                        ( 0xE7 )            /* control register */


/*****************************************************************************
  3 枚举定义
******************************************************************************/


/*****************************************************************************
 枚举名    : RF_RX_MAIN_CHANNEL_ID_ENUM_UINT16_HI6360
 枚举说明  :
*****************************************************************************/
/*定义RF_CHANNEL_ID*/
enum RF_RX_MAIN_CHANNEL_ID_ENUM_HI6360
{
    RX_LB2A                             = 0,
    RX_LB1A                                ,
    RX_HB2A                                ,
    RX_HB1A                                ,
    RX_UHB2A                               ,
    RX_UHB1A                               ,
    RX_OFF_A                               ,
    RX_MAIN_CHANNELID_BUTT_HI6360
};
typedef unsigned short RF_RX_MAIN_CHANNEL_ID_ENUM_UINT16_HI6360;


/*****************************************************************************
 枚举名    : RF_RX_DVTY_CHANNEL_ID_ENUM_UINT16_HI6360
 枚举说明  :
*****************************************************************************/
/*定义RF_CHANNEL_ID*/
enum RF_RX_DVTY_CHANNEL_ID_ENUM_HI6360
{
    RX_LB2B                             = 0,
    RX_LB1B                                ,
    RX_HB2B                                ,
    RX_HB1B                                ,
    RX_UHB2B                               ,
    RX_UHB1B                               ,
    RX_OFF_B                               ,
    RX_DVTY_CHANNELID_BUTT_HI6360
};
typedef unsigned short RF_RX_DVTY_CHANNEL_ID_ENUM_UINT16_HI6360;


/*****************************************************************************
 枚举名    : RF_TX_CHANNEL_ID_ENUM_UINT16_HI6360
 枚举说明  : 定义RF_CHANNEL_ID
*****************************************************************************/
enum RF_TX_CHANNEL_ID_ENUM_HI6360
{
    TX_2G_LB                            = 0,
    TX_2G_HB                               ,
    TX_3G_LB1                              ,
    TX_3G_LB2                              ,
    TX_3G_HB1                              ,
    TX_3G_HB2                              ,
    TX_3G_HB3                              ,
    TX_3G_MB                               ,
    TX_3G_UHB1                             ,
    TX_3G_UHB2                             ,
    TX_CHANNELID_BUTT_HI6360
};
typedef unsigned short RF_TX_CHANNEL_ID_ENUM_UINT16_HI6360;



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
 协议表格  :
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
 联合名    : HAL_RF_TDD_CONFIG1_UNION_HI6360
 联合说明  : TDD_CONFIG1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tdd_op_mode         : 3;                /* "TDD Operational Mode */
        unsigned short                      tdd_rx_path_select  : 2;                /* "RX Datapath selection for TDD operation */
        unsigned short                      unassigned          : 1;                /* unassigned */
        unsigned short                      tdd_if_config       : 4;                /* "TX IF Datapath Configuration */
        unsigned short                      tdd_lna_sel_b       : 3;                /* "LNA Input Selection - Diversity Datapath (B) */
        unsigned short                      tdd_lna_sel_a       : 3;                /* "LNA Input Selection - Main Datapath (A) */
    }stReg;
}HAL_RF_TDD_CONFIG1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TDD_CONFIG2_UNION_HI6360
 联合说明  : TDD_CONFIG2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      unassigned          : 12;               /* unassigned */
        unsigned short                      tdd_txrf_output_sel : 4;                /* "Enable RF Output Buffer. */
    }stReg;
}HAL_RF_TDD_CONFIG2_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_FDD_TX_CONFIG_UNION_HI6360
 联合说明  : FDD_TX_CONFIG寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      fdd_tx_op_mode      : 2;                /* "TX Operational Mode */
        unsigned short                      unassigned          : 4;                /* unassigned */
        unsigned short                      fdd_txif_config     : 4;                /* "TX IF Datapath Configuration */
        unsigned short                      unassigned1         : 2;                /* unassigned */
        unsigned short                      fdd_txrf_output_sel : 4;                /* "Enable RF Output Buffer. */
    }stReg;
}HAL_RF_FDD_TX_CONFIG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_AGC_UNION_HI6360
 联合说明  : TX_AGC寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txif_bb_atten       : 4;                /* "TX baseband attenuation Control */
        unsigned short                      unassigned          : 4;                /* unassigned */
        unsigned short                      txrf_mod_atten      : 4;                /* "TX Modulator Attenuation settings (dB) */
        unsigned short                      txrf_r2r_atten      : 4;                /* "TX RF path (R2R) attenuation (dB) */
    }stReg;
}HAL_RF_TX_AGC_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_FDD_RX_CONFIG_UNION_HI6360
 联合说明  : FDD_RX_CONFIG寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      fdd_rx_op_mode      : 2;                /* "RX Operational Mode */
        unsigned short                      unassigned          : 1;                /* unassigned */
        unsigned short                      fdd_rx_path_select  : 2;                /* "RX Path Select */
        unsigned short                      fdd_rx_2g_tmin_en   : 1;                /* Rx 2G Min Time-To-Ready Enable */
        unsigned short                      fdd_rxif_config     : 4;                /* "RX Datapath Bandwidth Configuration */
        unsigned short                      fdd_lna_sel_dvty    : 3;                /* "LNA Input Selection - Diversity Datapath (B) */
        unsigned short                      fdd_lna_sel_main    : 3;                /* "LNA Input Selection - Main Datapath (A) */
    }stReg;
}HAL_RF_FDD_RX_CONFIG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_MAIN_AGC_UNION_HI6360
 联合说明  : RX_MAIN_AGC寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxif_vga_gain_main      : 3;            /* "VGA gain Control */
        unsigned short                      rxif_postatt_gain_main  : 3;            /* "post IF attenuator control   */
        unsigned short                      reserved                : 1;            /* "bessel gain control  */
        unsigned short                      rxif_preatt_gain_main   : 2;            /* "pre IF attenuator control */
        unsigned short                      rxif_pma_gain_main      : 4;            /* "pma gain control   */
        unsigned short                      rxrf_lna_gain_main      : 3;            /* "select LNA GM stage gain (main path) */
    }stReg;
}HAL_RF_RX_MAIN_AGC_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_DVTY_AGC_UNION_HI6360
 联合说明  : RX_DVTY_AGC寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxif_vga_gain_main      : 3;            /* "VGA gain Control */
        unsigned short                      rxif_postatt_gain_main  : 3;            /* "post IF attenuator control   */
        unsigned short                      reserved                : 1;            /* "bessel gain control  */
        unsigned short                      rxif_preatt_gain_main   : 2;            /* "pre IF attenuator control */
        unsigned short                      rxif_pma_gain_main      : 4;            /* "pma gain control   */
        unsigned short                      rxrf_lna_gain_main      : 3;            /* "select LNA GM stage gain (main path) */
    }stReg;
}HAL_RF_RX_DVTY_AGC_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_MAIN_DCOC_VALUE_UNION_HI6360
 联合说明  : RX_MAIN_DCOC_VALUE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxif_coarse_dcoc_offset_i   : 8;        /* "DCOC Main I Channel Correction Value */
        unsigned short                      rxif_coarse_dcoc_offset_q   : 8;        /* "DCOC Main Q Channel Correction Value */
    }stReg;
}HAL_RF_RX_MAIN_DCOC_VALUE_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_RX_DVTY_DCOC_VALUE_UNION_HI6360
 联合说明  : RX_DVTY_DCOC_VALUE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxif_dvty_coarse_dcoc_offset_i  : 8;    /* "DCOC Diversity I Channel Correction Value */
        unsigned short                      rxif_dvty_coarse_dcoc_offset_q  : 8;    /* "DCOC Diversity Q Channel Correction Value */
    }stReg;
}HAL_RF_RX_DVTY_DCOC_VALUE_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_MAIN_IIP2_CAL_UNION_HI6360
 联合说明  : RX_MAIN_IIP2_CAL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      q_iip2_main_cal     : 8;                /* control bits for IIP2 correction for Q channel in the main path */
        unsigned short                      i_iip2_main_cal     : 8;                /* control bits for IIP2 correction for I channel in the main path */
    }stReg;
}HAL_RF_RX_MAIN_IIP2_CAL_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_DVTY_IIP2_CAL_UNION_HI6360
 联合说明  : RX_DVTY_IIP2_CAL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      q_iip2_dvty_cal     : 8;                /* control bits for IIP2 correction for Q channel in the diversity path */
        unsigned short                      i_iip2_dvty_cal     : 8;                /* control bits for IIP2 correction for I channel in the diversity path */
    }stReg;
}HAL_RF_RX_DVTY_IIP2_CAL_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_FEEDBACK_CONTROL_UNION_HI6360
 联合说明  : TX_FEEDBACK_CONTROL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txfb_pd_en                  : 1;        /* "TxFB ADC Power Detection mode. */
        unsigned short                      txfb_adc_en                 : 1;        /* "TxFB ADC circuit enable */
        unsigned short                      txfb_en                     : 1;        /* "TX Feedback LDO enable */
        unsigned short                      txfb_adc_pd_accum_req       : 1;        /* "Self Clearing Bit. */
        unsigned short                      txfb_adc_pd_accum_mode      : 1;        /* "Tx Feedback Accuulation Mode */
        unsigned short                      txfb_adc_pd_accum_length    : 2;        /* "Tx Feedback Accumulation Length */
        unsigned short                      txfb_rms_gain_adj           : 3;        /* "Tx Feedbcak RMS Gain Adjust */
        unsigned short                      unassigned                  : 6;        /* unassigned */
    }stReg;
}HAL_RF_TX_FEEDBACK_CONTROL_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_FEEDBACK_DATA_1_UNION_HI6360
 联合说明  : TX_FEEDBACK_DATA_1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txfb_adc_out            : 15;           /* "Accumulated ADC output for Tx power detector feedback.  19200 or 512 samples (see field ""txfb_adc_accum_length"") of the 5 bit TxFB ADC output are accumulated, then the most significant bits are reported in this field.  Note that this value is an accumulation, not an average. */
        unsigned short                      txfb_adc_out_toggle     : 1;            /* Toggles every time the data in [14:0] changes.  This allows the DBB to poll this register and know when the ADC value has been updated.  Note that the DBB must poll at least once per ADC output update, or it will not see every toggle of this bit. */
    }stReg;
}HAL_RF_TX_FEEDBACK_DATA_1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_OPERATING_BANDGROUP_UNION_HI6360
 联合说明  : 寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tcvr_operating_band     : 6;            /* Operating Frequency Band (Illegal bands are ignored e.g. Band 29. Programming an illegal band value maintains previously selected band) */
        unsigned short                      unassigned              : 10;
    }stReg;
}HAL_RF_OPERATING_BANDGROUP_UNION_HI6360;


/*****************************************************************************
 联合名    :
 联合说明  : 寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txrf_iqmod_ctune_sec    : 3;            /* TX balun tuning bits. Secondary side capacitor tuning (Debug) */
        unsigned short                      txrf_iqmod_ctune_prim   : 3;            /* TX balun tuning bits. Primary side capacitor tuning (Debug) */
        unsigned short                      rxrf_tank_tune          : 2;            /* LNA Tank Tuning for Main + Dvty (Debug) */
        unsigned short                      lna_cap_dvty            : 2;            /* Selects LNA Capacitor value for Frequency Tuning for Dvty (Debug) */
        unsigned short                      lna_cap_main            : 2;            /* Selects LNA Capacitor value for Frequency Tuning for Main (Debug) */
        unsigned short                      unassigned              : 4;
    }stReg;
}HAL_RF_RX_TX_TUNING_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_XO_AFC_CTL_ADDR_UNION_HI6360
 联合说明  : XO_AFC_CTL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      xo_afc              : 14;               /* Automatic frequency Control word */
        unsigned short                      unassigned          : 2;
    }stReg;
}HAL_RF_XO_AFC_CTL_ADDR_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RFIC_IO_CTRL_ADDR_UNION_HI6360
 联合说明  : RFIC_IO_CTRL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      iodig_sr_int        : 2;                /* "Digital IO slew rate control */
        unsigned short                      iodig_mode          : 2;                /* "Sets the operation or DFT modes for the digital pads on the IC: */
        unsigned short                      xo_fref_out_sr      : 2;                /* Clock Reference Output Pad Slew Rate Control - Fastest slew rate selected by default */
        unsigned short                      xo_fref_out_en_n    : 1;                /* Reference Clock Off-chip Buffer Enable (active low)- enable for the pad clock driver going back to the DBB */
        unsigned short                      unassigned0         : 1;                /* unassigned */
        unsigned short                      xo_c_trim           : 2;                /* XO Frequency Trim Capacitor - frequency trim to account for bond and other parasitic capacitance */
        unsigned short                      xo_i_trim           : 2;                /* XO Core Oscillator Trim Current - used to adjust the oscillator startup time */
        unsigned short                      unassigned1         : 3;                /* unassigned */
        unsigned short                      tcvr_fsm_en         : 1;                /* "RFIC State Machine Enable */
    }stReg;
}HAL_RF_RFIC_IO_CTRL_ADDR_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_MODE_UNION_HI6360
 联合说明  : PLLTX_MODE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_pllen            : 1;                /* TX PLL Enable */
        unsigned short                      unassigned0         : 2;                /* unassigned */
        unsigned short                      tx_vco_atemp_en     : 1;                /* "Enable for Atemp Compensation Loop */
        unsigned short                      tx_vco_div_sel      : 2;                /* "PLLTX VCO Core Divider */
        unsigned short                      unassigned1         : 1;                /* unassigned */
        unsigned short                      tx_core_sel_1_2b    : 1;                /* Select between low-frequency VCO (Core #1 == 1) or high frequency (Core #2 == 0) */
        unsigned short                      tx_lpf_sel_2g       : 1;                /* PLL-TX Loop filter selection. 0 : 3G/4G mode 1 : 2G mode */
        unsigned short                      tx_lpf_gain         : 1;                /* PLL-TX Loop filter gain 0 : High Gain 1 : Low Gain */
        unsigned short                      unassigned2         : 6;                /* unassigned */
    }stReg;
}HAL_RF_PLLTX_MODE_UNION_HI6360;

/*****************************************************************************
 联合名    : HAL_RF_PLLTX_MODE_V210_UNION_HI6360
 联合说明  : V210 PLLTX_MODE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_pllen            : 1;                /* TX PLL Enable */
        unsigned short                      tx_vco_core1_ibit   : 2;                /* PLL-TX VCO Core1 Tail Current Supply 0 : 14mA  1 :  15.75mA 2 :  17.5mA  3 :  19.25mA   */
        unsigned short                      tx_vco_atemp_en     : 1;                /* "Enable for Atemp Compensation Loop */
        unsigned short                      tx_lo_div_sel       : 2;                /* "PLLTX VCO Core Divider */
        unsigned short                      tx_ft_en            : 1;                /* PLL-TX FineTune Enable */
        unsigned short                      tx_core_sel_1_2b    : 1;                /* Select between low-frequency VCO (Core #1 == 1) or high frequency (Core #2 == 0) */
        unsigned short                      tx_vco_atemp_gain_set :1;               /* PLL-TX Atemp Gain Control 0 : 20dB 1 : 40dB */
        unsigned short                      tx_lpf_sel_2g       : 1;                /* PLL-TX Loop Filter Selection */
        unsigned short                      tx_lpf_sel_rcrc_2g  : 1;                /* PLL-TX Loop Filter Adjustment */
        unsigned short                      tx_cpo              : 2;                /* PLL-TX Charge Pump Offset Current Ratio */
        unsigned short                      tx_pd_en            : 1;                /* Charge Pump Down Enable */
        unsigned short                      tx_pu_en            : 1;                /* Charge Pump Up Enable */
        unsigned short                      tx_cp_offset_pol    : 1;                /* Charge Pump Offset Current Polarity Selection */
    }stReg;
}HAL_RF_PLLTX_MODE_V210_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_MODE_V210_UNION_HI6360
 联合说明  : V210 PLLRX_MODE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_pllen                : 1;            /* PLL-RX Enable */
        unsigned short                      rx_vco_mode_volt_curb   : 1;            /* PLL-RX VCO Core : Voltage vs. Current Mode Operation Select */
        unsigned short                      rx_vco_vreg_ctrl1_sel   : 1;            /* PLL-RX VCO Core1 VCO Vreg A/B Selection */
        unsigned short                      rx_vco_atemp_en         : 1;            /* PLL-RX Atemp Compensation  */
        unsigned short                      rx_lo_div_sel           : 2;            /* RX LO Divider Selection */
        unsigned short                      rx_ft_en                : 1;            /* PLL-RX FineTune Enable */
        unsigned short                      rx_core_sel_1_2b        : 1;            /* PLL-RX VCO Core Selection */
        unsigned short                      rx_vco_atemp_gain_set   : 1;            /* PLL-RX Atemp Gain Control */
        unsigned short                      rx_lpf_sel_2g           : 1;            /* PLL-RX Loop Filter Selection. */
        unsigned short                      rx_lpf_sel_rcrc_2g      : 1;            /* PLL-RX Loop Filter Adjustment */
        unsigned short                      rx_cpo                  : 2;            /* PLL-RX Charge Pump Offset Current Ratio */
        unsigned short                      rx_pd_en                : 1;            /* PLL-RX Charge Pump Down Enable */
        unsigned short                      rx_pu_en                : 1;            /* PLL-RX Charge Pump Up Enable */
        unsigned short                      rx_cp_offset_pol        : 1;            /* PLL-RX Charge Pump Offset Current Polarity Selection */
    }stReg;
}HAL_RF_PLLRX_MODE_V210_UNION_HI6360;

/*****************************************************************************
 联合名    : HAL_RF_RX_2G_FSM_TIME_UNION_HI6360
 联合说明  : RX_2G_FSM_TIME寄存器定义
*****************************************************************************/
typedef union
{

    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_2g_idle_cal_wait_time    : 4;        /* FDD 2G Idle-to-RXCal Wait Time */
        unsigned short                      rx_2g_idle_stdby_wait_time  : 4;        /* FDD 2G Idle-to-RXStandBy Wait Time */
        unsigned short                      rx_2g_idle_rxon_wait_time   : 4;        /* FDD 2G Idle-to-RXOn Wait Time */
        unsigned short                      unassigned                  : 3;
        unsigned short                      rx_wait_time_double_time    : 1;
    }stReg;
}HAL_RF_RX_2G_FSM_TIME_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_FDD_RX_CONFIG_V210_UNION_HI6360
 联合说明  : V210 FDD_RX_CONFIG寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      fdd_rx_op_mode      : 2;                /* "RX Operational Mode */
        unsigned short                      unassigned          : 1;                /* unassigned */
        unsigned short                      fdd_rx_path_select  : 2;                /* RX Path Select */
        unsigned short                      fdd_rx_agc_sync_bypass : 1;             /* FDD-RX AGC and DCOC Synchronization Mode Bypass */
        unsigned short                      fdd_rxif_config     : 4;                /* "RX Datapath Bandwidth Configuration */
        unsigned short                      fdd_lna_sel_dvty    : 3;                /* "LNA Input Selection - Diversity Datapath (B) */
        unsigned short                      fdd_lna_sel_main    : 3;                /* "LNA Input Selection - Main Datapath (A) */
    }stReg;
}HAL_RF_FDD_RX_CONFIG_V210_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_IIP2_LO_CAL_UNION_HI6360
 联合说明  : 主分集 RX_IIP2_LO_CAL 寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rf_rf_iip2cal_lo_i_value    : 8;        /* value */
        unsigned short                      rf_rf_iip2cal_lo_q_value    : 8;        /* value */
    }stReg;
}HAL_RF_RX_IIP2_LO_CAL_UNION_HI6360;

/*****************************************************************************
 联合名    : HAL_RF_TX_FEEDBACK_CONTROL_V210_UNION_HI6360
 联合说明  : V210 TX_FEEDBACK_CONTROL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txfb_pd_en              : 1;            /* "TxFB ADC Power Detection mode. */
        unsigned short                      txfb_adc_en             : 1;            /* "TxFB ADC circuit enable */
        unsigned short                      txfb_en                 : 1;            /* "TX Feedback LDO enable */
        unsigned short                      txfb_adc_pd_accum_req   : 1;            /* "Self Clearing Bit */
        unsigned short                      txfb_adc_pd_accum_mode  : 1;            /* "Tx Feedback Accuulation Mode */
        unsigned short                      txfb_adc_pd_accum_length: 2;           /* "Tx Feedback Accumulation Length */
        unsigned short                      txfb_rms_gain_adj       : 4;            /* "Tx Feedbcak RMS Gain Adjust */
        unsigned short                      txfb_rf_atten_sel       : 1;            /* Tx Feedback RMS Power Detector RF Attenuation */
        unsigned short                      txfb_accum_leftshift2   : 1;            /* Allows the DBB to tell the TxFB ADC output accumulator to shift the accumulated sum left by 2 bits before inserting it into the txfb_adc_out[14:0] register for readback.  */
        unsigned short                      unassigned              : 3;
    }stReg;
}HAL_RF_TX_FEEDBACK_CONTROL_V210_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_FEEDBACK_DEBUG2_UNION_HI6360
 联合说明  : TX_FEEDBACK_DEBUG2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txfb_rms_tcomp_adj          : 3;    /* TXFB RMS detector temperature compensation adjustment */
        unsigned short                      txfb_rms_voutdc_adj         : 4;    /* TXFB RMS detector DC output voltage adjustment */
        unsigned short                      txfb_rms_lpf_adj            : 1;    /* TXFB RMS detector lowpass filter adjustment */
        unsigned short                      unassigned                  : 8;    /* unassigned */
    }stReg;
}HAL_RF_TX_FEEDBACK_DEBUG2_UNION_HI6360;

/*****************************************************************************
 联合名    : HAL_RF_RFIC_CHIP_ID_UNION_HI6360
 联合说明  : RFIC_CHIP_ID寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      meta_version        : 5;                /* meta_version */
        unsigned short                      product_revise      : 5;                /* product_revise */
        unsigned short                      product_id          : 6;                /* product_id */
    }stReg;
}HAL_RF_RFIC_CHIP_ID_UNION_HI6360;




/*****************************************************************************
 联合名    : HAL_RF_PLLTX_FREQ1_UNION_HI6360
 联合说明  : PLLTX_FREQ1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_num              : 8;                /* 8 MSBs of the Tx frequency fraction */
        unsigned short                      tx_n                : 8;                /* TX frequency integer.  POR Value is 3628MHz when Fref=19.2MHz (N=94.4792). */
    }stReg;
}HAL_RF_PLLTX_FREQ1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_FREQ2_UNION_HI6360
 联合说明  : PLLTX_FREQ2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_num              : 16;               /* 16 LSBs of the Tx  frequency fraction */
    }stReg;
}HAL_RF_PLLTX_FREQ2_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_MODE_UNION_HI6360
 联合说明  : PLLRX_MODE寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_pllen            : 1;                /* RX PLL Enable */
        unsigned short                      unassigned0         : 2;                /* unassigned */
        unsigned short                      rx_vco_atemp_en     : 1;                /* "Enable for Atemp Compensation Loop */
        unsigned short                      rx_vco_div_sel      : 2;                /* "PLLRX VCO Core Divider */
        unsigned short                      unassigned1         : 1;                /* unassigned */
        unsigned short                      rx_core_sel_1_2b    : 1;                /* Select between low-frequency VCO (Core #1 == 1) or high frequency (Core #2 == 0) */
        unsigned short                      rx_lpf_sel_2g       : 1;                /* PLL-RX Loop filter selection. 0 : 3G/4G mode 1 : 2G mode */
        unsigned short                      rx_lpf_gain         : 1;                /* PLL-RX Loop filter gain 0 : High Gain 1 : Low Gain */
        unsigned short                      unassigned          : 6;                /* unassigned */
    }stReg;
}HAL_RF_PLLRX_MODE_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_FREQ1_UNION_HI6360
 联合说明  : PLLRX_FREQ1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_num              : 8;                /* 8 MSBs of the RX frequency fraction */
        unsigned short                      rx_n                : 8;                /* RX frequency integer.  POR Value is 4501MHz when Fref=19.2MHz (N=117.2135417). */
    }stReg;
}HAL_RF_PLLRX_FREQ1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_FREQ2_UNION_HI6360
 联合说明  : PLLRX_FREQ2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_num              : 16;               /* 16 LSBs of the RX frequency fraction */
    }stReg;
}HAL_RF_PLLRX_FREQ2_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TDD_3G4G_FSM_TIME_REG_UNION_HI6360
 联合说明  : 3G4G定时器寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tdd_idle_cal_wait_time      : 4;        /* "TDD Idle-to-Cal Wait Time (80us minimum, 5us resolution) */
        unsigned short                      tdd_idle_stdby_wait_time    : 4;        /* "TDD Idle-to-StandBy Wait Time (80us minimum, 5us resolution) */
        unsigned short                      tdd_idle_rxon_wait_time     : 4;        /* "TDD Idle-to-RXOn Wait Time (80us minimum, 5us resolution) */
        unsigned short                      tdd_idle_txon_wait_time     : 4;        /* "TDD Idle-to-TXOn Wait Time (80us minimum, 5us resolution) */
    }stReg;
}HAL_RF_TDD_3G4G_FSM_TIME_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_FSM_TIME_REG_UNION_HI6360
 联合说明  : 发送定时器寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_idle_cal_wait_time       : 4;        /* "FDD Idle-to-TXCal Wait Time (80us minimum, 5us resolution) */
        unsigned short                      tx_idle_stdby_wait_time     : 4;        /* "FDD Idle-to-TXStandBy Wait Time (80us minimum, 5us resolution) */
        unsigned short                      unassigned                  : 4;        /* unassigned */
        unsigned short                      tx_idle_txon_wait_time      : 4;        /* "FDD Idle-to-TXOn Wait Time (80us minimum, 5us resolution) */
    }stReg;
}HAL_RF_TX_FSM_TIME_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_TX_BIAS_CFG_REG_UNION_HI6360
 联合说明  : 发送bias寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      txrf_iqmod_ibias            : 3;        /* "TX Modulator  Biasing */
        unsigned short                      txrf_iqmod_ctune_sec        : 3;        /* "TX balun tuning bits. Secondary side capacitor tuning */
        unsigned short                      txrf_iqmod_ctune_prim       : 3;        /* "TX balun tuning bits. Primary side capacitor tuning */
        unsigned short                      txrf_iqmod_locm_vtune       : 3;        /* "TX IQ Modulator common mode voltage adjust on LO port */
        unsigned short                      txrf_bias_cfg_debug         : 1;        /* "This bit will be used to disable the decoding used in the txrf4g_top which automatically sets the appropriate values for the primary tuning capacitors, secondary tuning capacitors, and the iqmod_ibias, based on the RF band in use. */
        unsigned short                      txrf_rcfbuffer_bw_vctrl     : 1;        /* This bit will be used to maintain a constant rcf buffer -3dB bandwidth when testing the Hi6360V110 at VDD_TXRF = 2.2V [Bit Value=0] and VDD_TXRF = 2.8V [Bit Value=1].  */
        unsigned short                      unassigned                  : 2;        /* unassigned */
    }stReg;
}HAL_RF_TX_BIAS_CFG_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_FSM_TIME_REG_UNION_HI6360
 联合说明  : 发送bias寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_idle_cal_wait_time       : 4;        /* "FDD Idle-to-RXCal Wait Time (80us minimum, 5us resolution) */
        unsigned short                      rx_idle_stdby_wait_time     : 4;        /* "FDD Idle-to-RXStandBy Wait Time (80us minimum, 5us resolution) */
        unsigned short                      rx_idle_rxon_wait_time      : 4;        /* "FDD Idle-to-RXOn Wait Time (80us minimum, 5us resolution) */
        unsigned short                      unassigned                  : 4;        /* unassigned */
    }stReg;
}HAL_RF_RX_FSM_TIME_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_RX_MAIN_LNA_REG_UNION_HI6360
 联合说明  : 接收主通道寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      lna_bias_ptat_main          : 4;        /* "Main LNA Bias PTAT Control */
        unsigned short                      lna_bias_bg_main            : 4;        /* "Main LNA Bandgap Bias Current Value */
        unsigned short                      unassigned0                 : 5;        /* unassigned */
        unsigned short                      lna_en                      : 2;        /* "LNA Enable (Debug) */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
    }stReg;
}HAL_RF_RX_MAIN_LNA_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_RX_DVTY_LNA_REG_UNION_HI6360
 联合说明  : 接收分通道寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      lna_bias_ptat_dvty          : 4;        /* "Diversity LNA Bias PTAT Control */
        unsigned short                      lna_bias_bg_dvty            : 4;        /* "Diversity LNA Bandgap Bias Current Value */
        unsigned short                      unassigned                  : 8;        /* unassigned */
    }stReg;
}HAL_RF_RX_DVTY_LNA_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_PWR_LDO_REG_UNION_HI6360
 联合说明  : 发送PLL功率LDO寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_ldo10_vset               : 2;        /* "Voltage regulator 10 Output Level  */
        unsigned short                      tx_ldo7_vset                : 2;        /* "Voltage regulator 7 Output Level - UNUSED */
        unsigned short                      unassigned                  : 6;        /* unassigned */
        unsigned short                      tx_ldo_en_ctrl              : 2;        /* "TX PLL Controller LDO Enable Control  */
        unsigned short                      tx_bg_fs_ctrl               : 2;        /* "TX PLL BandGap Fast On  */
        unsigned short                      tx_bg_en                    : 2;        /* "TX PLL BandGap Enable  */
    }stReg;
}HAL_RF_PLLTX_PWR_LDO_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLTX_PWR_VCO_REG_UNION_HI6360
 联合说明  : 发送PLL功率VCO寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_vco_div_vreg_outputi_en  : 1;        /* "Tx VCO HB/LB Divider VREG Output Bias Shunt Enable */
        unsigned short                      tx_vco_div_vreg_lownoise_en : 1;        /* Tx VCO HB/LB divider voltage regulator low noise mode enable */
        unsigned short                      tx_vco_lo_buf_highp_en      : 1;        /* "TX VCO Output Divider High Power Enable */
        unsigned short                      unassigned0                 : 1;        /* unassigned */
        unsigned short                      tx_vco_div_vreg_ctrl        : 3;        /* "Tx VCO HB/LB divider voltage regulator voltage control */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
        unsigned short                      tx_vco_vreg_outputi_en      : 1;        /* "Tx VCO VREG Output Bias Shunt Enable */
        unsigned short                      tx_vco_vreg_lownoise_en     : 1;        /* Tx VCO voltage regulator low noise mode enable */
        unsigned short                      unassigned                  : 2;        /* unassigned */
        unsigned short                      tx_vco_vreg_ctrl            : 4;        /* "Tx VCO voltage regulator voltage control */
    }stReg;
}HAL_RF_PLLTX_PWR_VCO_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLTX_CTL_REG_UNION_HI6360
 联合说明  : 发送PLL功率CTL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_cprs_ctrl                : 2;        /* "TX Charge Pump Reset (StartUp) */
        unsigned short                      tx_pll_cp_ctrl              : 2;        /* "TX PLL ChargePump High Gain Mode Period */
        unsigned short                      tx_tstart                   : 4;        /* "TX PLL Acquistion/Settle Time */
        unsigned short                      tx_n_pw                     : 1;        /* "TX PLL N-divider output Pulse Width adjustment. */
        unsigned short                      unassigned                  : 1;        /* unassigned */
        unsigned short                      tx_cpd                      : 1;        /* "TX PLL Force charge pump to pump down */
        unsigned short                      tx_cpu                      : 1;        /* "TX PLL Force charge pump to pump up  */
        unsigned short                      tx_pd_en                    : 1;        /* "Charge Pump Down Enable */
        unsigned short                      tx_pu_en                    : 1;        /* "Charge Pump Up Enable */
        unsigned short                      tx_cp_offset_pol            : 1;        /* "Charge Pump Offset Current Polarity Selection */
        unsigned short                      tx_intnen                   : 1;        /* "PLL Integer Mode (SigmaDelta disable) */
    }stReg;
}HAL_RF_PLLTX_CTL_REG_UNION_HI6360;




/*****************************************************************************
 联合名    : HAL_RF_PLLTX_KVCAL_1_REG_UNION_HI6360
 联合说明  : 发送PLL功率KVCAL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_tft                      : 4;        /* "TX FineTune Settle Time */
        unsigned short                      tx_nmbr_ft_avgs             : 2;        /* "Number of samples averaged to calculate FineTune DAC value */
        unsigned short                      tx_nmbr_fmeas_avgs          : 2;        /* "Number of samples averaged to calculate VCO frequency for KV calibration */
        unsigned short                      tx_ft_gain                  : 2;        /* "TX FineTune FLL loop filter gain: */
        unsigned short                      tx_ft_en                    : 1;        /* "TX FineTune Enable */
        unsigned short                      tx_kv_rx1                   : 1;        /* "KV R1 High Gain Selection */
        unsigned short                      tx_kv_dac_step              : 3;        /* "KV DeltaV value for F0, F1 Frequency Measurements */
        unsigned short                      tx_kv_en                    : 1;        /* "TX KV Calibration Enable: 0=disable, 1=enabled  <1,1,u> */
    }stReg;
}HAL_RF_PLLTX_KVCAL_1_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_WAIT_TIME_REG_UNION_HI6360
 联合说明  : 发送PLL功率等待时间寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_tvco                     : 7;        /* "TX VCO WarmUp Time */
        unsigned short                      unassigned0                 : 1;        /* unassigned */
        unsigned short                      tx_tlock                    : 7;        /* "TX PLL Lock Time */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
    }stReg;
}HAL_RF_PLLTX_WAIT_TIME_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLRX_PWR_LDO_REG_UNION_HI6360
 联合说明  : 接收PLL功率LDO寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_ldo10_vset               : 2;        /* "Voltage regulator 10 Output Level  */
        unsigned short                      rx_ldo7_vset                : 2;        /* "Voltage regulator 7 Output Level - UNUSED */
        unsigned short                      rx_vco_i                    : 3;        /* "VCO core current control bits. */
        unsigned short                      unassigned                  : 3;        /* unassigned */
        unsigned short                      rx_ldo_en_ctrl              : 2;        /* "RX PLL Controller LDO Enable Control  */
        unsigned short                      rx_bg_fs_ctrl               : 2;        /* "RX PLL BandGap Fast On  */
        unsigned short                      rx_bg_en                    : 2;        /* "RX PLL BandGap Enable  */
    }stReg;
}HAL_RF_PLLRX_PWR_LDO_REG_UNION_HI6360;




/*****************************************************************************
 联合名    : HAL_RF_PLLRX_CTL_REG_UNION_HI6360
 联合说明  : 接收PLL CTL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_cprs_ctrl                : 2;        /* "RX PLL Charge Pump Reset (StartUp) */
        unsigned short                      rx_pll_cp_ctrl              : 2;        /* "RX PLL ChargePump High Gain Mode Period */
        unsigned short                      rx_tstart                   : 4;        /* "RX PLL Acquistion/Settle Time */
        unsigned short                      rx_n_pw                     : 1;        /* "RX PLL N-divider output Pulse Width adjustment */
        unsigned short                      unassigned                  : 1;        /* unassigned */
        unsigned short                      rx_cpd                      : 1;        /* "RX PLL Force charge pump to pump down */
        unsigned short                      rx_cpu                      : 1;        /* "RX PLL Force charge pump to pump up  */
        unsigned short                      rx_pd_en                    : 1;        /* "Charge Pump Down Enable */
        unsigned short                      rx_pu_en                    : 1;        /* "Charge Pump Up Enable */
        unsigned short                      rx_cp_offset_pol            : 1;        /* "Charge Pump Offset Current Polarity Selection */
        unsigned short                      rx_intnen                   : 1;        /* "PLL Integer Mode (SigmaDelta disable) */
    }stReg;
}HAL_RF_PLLRX_CTL_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_KVCAL_1_REG_UNION_HI6360
 联合说明  : 接收PLL KVCAL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_tft                      : 4;        /* "RX FineTune Settle Time */
        unsigned short                      rx_nmbr_ft_avgs             : 2;        /* "Number of samples averaged to calculate FineTune DAC value */
        unsigned short                      rx_nmbr_fmeas_avgs          : 2;        /* "Number of samples averaged to calculate VCO frequency for KV calibration */
        unsigned short                      rx_ft_gain                  : 2;        /* "TX FineTune FLL loop filter gain: */
        unsigned short                      rx_ft_en                    : 1;        /* "RX FineTune Enable */
        unsigned short                      rx_kv_rx1                   : 1;        /* "KV R1 High Gain Selection */
        unsigned short                      rx_kv_dac_step              : 3;        /* "KV DeltaV value for F0, F1 Frequency Measurements */
        unsigned short                      rx_kv_en                    : 1;        /* "RX KV Calibration Enable: 0=disable, 1=enabled  <1,1,u> */
    }stReg;
}HAL_RF_PLLRX_KVCAL_1_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_WAIT_TIME_REG_UNION_HI6360
 联合说明  : 接收PLL等待时间寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_tvco                     : 7;        /* "RX VCO WarmUp Time */
        unsigned short                      unassigned0                 : 1;        /* unassigned */
        unsigned short                      rx_tlock                    : 7;        /* "RX PLL Lock Time */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
    }stReg;
}HAL_RF_PLLRX_WAIT_TIME_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_PWR_VCO_REG_UNION_HI6360
 联合说明  : 接收PLL功率VCO寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_vco_div_vreg_outputi_en  : 1;        /* "RX VCO HB/LB Divider VREG Output Bias Shunt Enable */
        unsigned short                      rx_vco_div_vreg_lownoise_en : 1;        /* RX VCO HB/LB divider voltage regulator low noise mode enable */
        unsigned short                      rx_vco_lo_buf_highp_en      : 1;        /* "RX VCO Output Divider High Power Enable */
        unsigned short                      unassigned0                 : 1;        /* unassigned */
        unsigned short                      rx_vco_div_vreg_ctrl        : 3;        /* "RX VCO HB/LB divider voltage regulator voltage control */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
        unsigned short                      rx_vco_vreg_outputi_en      : 1;        /* "RX VCO VREG Output Bias Shunt Enable */
        unsigned short                      rx_vco_vreg_lownoise_en     : 1;        /* RX VCO voltage regulator low noise mode enable */
        unsigned short                      unassigned2                 : 2;        /* unassigned */
        unsigned short                      rx_vco_vreg_ctrl            : 4;        /* "RX VCO voltage regulator voltage control */
    }stReg;
}HAL_RF_PLLRX_PWR_VCO_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLRX_CTRL_FSM_REG_UNION_HI6360
 联合说明  : 接收PLL功率CTRL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_vco_pll_en               : 2;        /* "RX PLL Feedback Buffer Enable */
        unsigned short                      rx_vco_lo_en                : 2;        /* "RX VCO Output Divider Enable */
        unsigned short                      unassigned                  : 2;        /* unassigned */
        unsigned short                      rx_vco_div_vreg_faston_en   : 2;        /* "RX VCO HB/LB divider voltage regulator FastTurnOn Enable Override */
        unsigned short                      rx_vco_vreg_faston_en       : 2;        /* "RX VCO Supply Filter Bypass (FastOn Startup) */
        unsigned short                      rx_vco_rc_su_en             : 2;        /* "RX VCO Core Supply Filter Enable */
        unsigned short                      rx_vco_faston_en            : 2;        /* "RX VCO Voltage Reference FastTurnOn Enable */
        unsigned short                      rx_vco_en                   : 2;        /* "RX VCO Enable */
    }stReg;
}HAL_RF_PLLRX_CTRL_FSM_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLRX_VCO_ATEMP_REG_UNION_HI6360
 联合说明  : 接收PLL功率VCO ATEMP寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_vco_atemp_preloadswitch_en   : 2;    /* "Atemp Preload Voltage Enable (Atemp Loop Initialization) */
        unsigned short                      rx_vco_atemp_faston_en          : 2;    /* "Atemp LPF Bypass (Fast Loop Initialization) */
        unsigned short                      rx_vco_atemp_vtune_ref          : 4;    /* "Control bits that set the reference voltage for the temperature compensation loop.  This level will set where in the primary tuning varactor range the PLL will lock. */
        unsigned short                      rx_vco_atemp_vptat_vconst       : 3;    /* "VCO ATEMP Constant Voltage Selection */
        unsigned short                      rx_vco_atemp_bypass             : 1;    /* "Atemp Compensation Bypass */
        unsigned short                      rx_vco_atemp_vptat_pllfreq      : 2;    /* "VPTAT Slope Selection Test Override Control */
        unsigned short                      rx_vco_atemp_vptat_test_en      : 1;    /* "Atemp VPTAT Test Enable */
        unsigned short                      rx_vco_atemp_vptatout_en        : 1;    /* "VPTAT Output Selection */
    }stReg;
}HAL_RF_PLLRX_VCO_ATEMP_REG_UNION_HI6360;




/*****************************************************************************
 联合名    : HAL_RF_PLLRX_CT_1_REG_UNION_HI6360
 联合说明  : 接收PLL功率CT寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_tct                      : 5;        /* "RX Coarse Tune Settle Time */
        unsigned short                      unassigned                  : 1;        /* unassigned */
        unsigned short                      rx_nmbr_ct_avgs             : 2;        /* "Number of samples averaged to calculate RX VCO coarse tuning setting: */
        unsigned short                      rx_ct_dac_def               : 5;        /* "LPF DAC Default value */
        unsigned short                      rx_ct_gain                  : 3;        /* "RX coarse tuning FLL loop filter gain: */
    }stReg;
}HAL_RF_PLLRX_CT_1_REG_UNION_HI6360;




/*****************************************************************************
 联合名    : HAL_RF_RX_EN_REG_UNION_HI6360
 联合说明  : 接收EN寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxrf_ldo1p2_cnt             : 2;        /* "RxRF 1.2V LDO Output Voltage Level (NOQC supply) */
        unsigned short                      rxrf_ldo1p9v_dvty_en        : 1;        /* "RxRF 1.9V LDO Enable for diversity path (Debug) */
        unsigned short                      rxrf_ldo1p9v_main_en        : 1;        /* "RxRF 1.9V LDO Enable for main path (Debug) */
        unsigned short                      rxrf_ldo1p2v_dvty_en        : 1;        /* "RxRF 1.2V LDO Enable for diversity path (Debug) */
        unsigned short                      rxrf_ldo1p2v_main_en        : 1;        /* "RxRF 1.2V LDO Enable for main path (Debug) */
        unsigned short                      rxif_dvty_ldo1p9_en         : 1;        /* "RxIF 1.9V LDO Enable for diversity path (Debug) */
        unsigned short                      rxif_ldo1p9_en              : 1;        /* "RxIF 1.9V LDO Enable for main path (Debug) */
        unsigned short                      rxrf_tia_dvty_en            : 1;        /* "Enable TIA in RXRF diversity path (Debug) */
        unsigned short                      rxrf_tia_main_en            : 1;        /* "Enable TIA in RXRF main path (Debug) */
        unsigned short                      rxrf_dvty_en                : 1;        /* "Enable Bias current in RxRF Diversity path section (Debug) */
        unsigned short                      rxrf_main_en                : 1;        /* "Enable Bias current in RxRF Main path section (Debug) */
        unsigned short                      unassigned                  : 2;        /* unassigned */
        unsigned short                      rx_speedup                  : 1;        /* "RX Initialization SpeedUp (Debug) */
        unsigned short                      rxbg_enable                 : 1;        /* "RX BandGap Enable (Debug) */
    }stReg;
}HAL_RF_RX_EN_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_CTRL_REG_UNION_HI6360
 联合说明  : 接收CTRL寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rxif_vga_low_vcm            : 1;        /* "Select Common Mode Voltage for RxIF VGA off-chip output */
        unsigned short                      unassigned0                 : 1;        /* unassigned */
        unsigned short                      rxif_dcoc_range             : 1;        /* "DCOC Dac Gain Bias Control */
        unsigned short                      unassigned1                 : 1;        /* unassigned */
        unsigned short                      rxrf_noqc_dvty_en           : 1;        /* "RX Non Overlapping Quadature Clock (NOQC) Enable on Diverstiy path (Debug) */
        unsigned short                      rxrf_noqc_main_en           : 1;        /* "RX Non Overlapping Quadature Clock (NOQC) Enable on Main path (Debug) */
        unsigned short                      unassigned2                 : 2;        /* unassigned */
        unsigned short                      rx_dcoc_dac_dvty_en         : 1;        /* "Enable Diversity DCOC DAC */
        unsigned short                      rx_dcoc_dac_main_en         : 1;        /* "Enable Main DCOC DAC */
        unsigned short                      unassigned3                 : 2;        /* unassigned */
        unsigned short                      rxif_dvty_en                : 1;        /* "RxIF Diversity Datapath Enable (Debug)  */
        unsigned short                      rxif_main_en                : 1;        /* "RxIF Main Datapath Enable (Debug)  */
        unsigned short                      unassigned4                 : 2;        /* unassigned */
    }stReg;
}HAL_RF_RX_CTRL_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_LFSR_REG_UNION_HI6360
 联合说明  : 发送PLL LFSR寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_lfsr_div2_en             : 1;        /* "LFSR Input Clock Selection  */
        unsigned short                      tx_lfsr_clk_pol             : 1;        /* "TX LFSR clock polarity */
        unsigned short                      tx_lfsr_on                  : 1;        /* Forces TX LFSR enable and clock on */
        unsigned short                      tx_lfsr_test_trig           : 1;        /* "TX LFSR BIST and frequency counter Stsrt Bit */
        unsigned short                      unassigned                  : 12;       /* unassigned */
    }stReg;
}HAL_RF_PLLTX_LFSR_REG_UNION_HI6360;



/*****************************************************************************
 联合名    : HAL_RF_PLLRX_LFSR_REG_UNION_HI6360
 联合说明  : 接收PLL LFSR寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      rx_lfsr_div2_en             : 1;        /* "LFSR Input Clock Selection  */
        unsigned short                      rx_lfsr_clk_pol             : 1;        /* "RX LFSR clock polarity */
        unsigned short                      rx_lfsr_on                  : 1;        /* Forces RX LFSR enable and clock on */
        unsigned short                      rx_lfsr_test_trig           : 1;        /* "RX LFSR BIST and frequency counter Stsrt Bit */
        unsigned short                      unassigned                  : 12;       /* unassigned */
    }stReg;
}HAL_RF_PLLRX_LFSR_REG_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_RX_LNA_UNION_HI6360
 联合说明  : RX_LNA寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short uhwValue;

    struct
    {
        unsigned short                      rxrf_lna_bias_ptat      : 4;
        unsigned short                      rxrf_lna_bias_bg        : 4;
        unsigned short                      rxrf_lnacas_ldo_vout    : 2;
        unsigned short                      unassigned              : 6;
    }stReg;
}HAL_RF_RX_LNA_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLRX_KVCAL_1_UNION_HI6360
 联合说明  : PLLRX_KVCAL_1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short uhwValue;

    struct
    {
        unsigned short                      rx_tft                  : 4;            /* "TX FineTune Settle Time */
        unsigned short                      rx_nmbr_ft_avgs         : 2;            /* "Number of samples averaged to calculate FineTune DAC value */
        unsigned short                      rx_nmbr_fmeas_avgs      : 2;            /* "Number of samples averaged to calculate VCO frequency for KV calibration */
        unsigned short                      rx_ft_gain              : 2;            /* "TX FineTune FLL loop filter gain: */
        unsigned short                      rx_ft_en                : 1;            /* "TX FineTune Enable */
        unsigned short                      rx_kv_rx1               : 1;            /* "KV R1 High Gain Selection */
        unsigned short                      rx_kv_dac_step          : 3;            /* "KV DeltaV value for F0, F1 Frequency Measurements */
        unsigned short                      rx_kv_en                : 1;            /* "TX KV Calibration Enable: 0=disable, 1=enabled  <1,1,u> */
    }stReg;
}HAL_RF_PLLRX_KVCAL_1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_LPF_UNION_HI6360
 联合说明  : PLLTX_LPF寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_lpf_rpl_cap_sel      : 1;
        unsigned short                      tx_lpf_int_cap_sel      : 1;
        unsigned short                      tx_lpf_debug_cap_sel    : 1;
        unsigned short                      tx_lpf_int_cap_bypass   : 1;
        unsigned short                      tx_lpf_unity_gain_sel   : 2;
        unsigned short                      tx_lpf_fs               : 2;
        unsigned short                      tx_lpf_testout_sel      : 3;
        unsigned short                      unassigned              : 5;
    }stReg;
}HAL_RF_PLLTX_LPF_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_CT_1_UNION_HI6360
 联合说明  : PLLTX_CT_1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      unassigned0             : 1;
        unsigned short                      tx_lfsr_clk_pol         : 1;
        unsigned short                      tx_lfsr_on              : 1;
        unsigned short                      tx_lfsr_test_trig       : 1;
        unsigned short                      unassigned1             : 3;
        unsigned short                      tx_ct_half_rate         : 1;
        unsigned short                      tx_tct2                 : 4;
        unsigned short                      tx_tct1                 : 4;
    }stReg;
}HAL_RF_PLLTX_CT_1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_CT_2_UNION_HI6360
 联合说明  : PLLTX_CT_2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_ct_dac_def2          : 5;
        unsigned short                      tx_ct_gain2             : 3;
        unsigned short                      tx_ct_dac_def1          : 5;
        unsigned short                      tx_ct_gain1             : 3;
    }stReg;
}HAL_RF_PLLTX_CT_2_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_KVCAL_1_UNION_HI6360
 联合说明  : PLLTX_KVCAL_1寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short uhwValue;

    struct
    {
        unsigned short                      tx_tft                  : 4;            /* "TX FineTune Settle Time */
        unsigned short                      tx_nmbr_ft_avgs         : 2;            /* "Number of samples averaged to calculate FineTune DAC value */
        unsigned short                      tx_nmbr_fmeas_avgs      : 2;            /* "Number of samples averaged to calculate VCO frequency for KV calibration */
        unsigned short                      tx_ft_gain              : 2;            /* "TX FineTune FLL loop filter gain: */
        unsigned short                      tx_ft_en                : 1;            /* "TX FineTune Enable */
        unsigned short                      tx_kv_rx1               : 1;            /* "KV R1 High Gain Selection */
        unsigned short                      tx_kv_dac_step          : 3;            /* "KV DeltaV value for F0, F1 Frequency Measurements */
        unsigned short                      tx_kv_en                : 1;            /* "TX KV Calibration Enable: 0=disable, 1=enabled  <1,1,u> */
    }stReg;
}HAL_RF_PLLTX_KVCAL_1_UNION_HI6360;


/*****************************************************************************
 联合名    : HAL_RF_PLLTX_KVCAL_2_UNION_HI6360
 联合说明  : PLLTX_KVCAL_2寄存器定义
*****************************************************************************/
typedef union
{
    unsigned short                          uhwValue;

    struct
    {
        unsigned short                      tx_kv_bw_2g             : 8;            /* Target Bandwidth in KHz for 2G */
        unsigned short                      tx_kv_bw_3g4g           : 8;            /* Target Bandwidth in KHz for 3G/4G */
    }stReg;
}HAL_RF_PLLTX_KVCAL_2_UNION_HI6360;


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

#endif