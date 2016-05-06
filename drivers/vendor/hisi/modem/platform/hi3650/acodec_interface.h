/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hissc_v8_audio_codec_nmanager_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-03-19 09:38:31
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月19日
    作    者   : s00212991
    修改内容   : 从《Balong_V8_Audio_CODEC_nManager.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __AUDIO_CODEC_INTERFACE_H__
#define __AUDIO_CODEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/****************************************************************************
                     (1/2) SoC CODEC
 ****************************************************************************/
/* 寄存器说明：逻辑电路软复位，除寄存器外，复位所有功能逻辑，CRG及寄存器除外。 */
#define HISSC_SW_RST_N_ADDR                           ((PAGE_SoCCODEC) + (0x00))
/* 软件复位CODEC内部所有功能逻辑。
0：复位有效；
1：正常工作。 */
#define    HISSC_SW_RST_N_BIT_START   (0)
#define    HISSC_SW_RST_N_BIT_END     (0)
/* reserved RO Registers */
#define    HISSC_DIG_RO_00_BIT_START  (1)
#define    HISSC_DIG_RO_00_BIT_END    (7)
/* 版本寄存器 */
#define    HISSC_VERSION_BIT_START    (8)
#define    HISSC_VERSION_BIT_END      (15)

/* 寄存器说明：APB IF/DMIC IF/SIF/I2S接口相关模块时钟使能配置 */
#define HISSC_IF_CLK_EN_CFG_ADDR                      ((PAGE_SoCCODEC) + (0x04))
/* STEREO上行左通道异步FIFO时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_STEREO_UPLINK_L_EN_BIT_START  (0)
#define    HISSC_STEREO_UPLINK_L_EN_BIT_END    (0)
/* STEREO上行右通道异步FIFO时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_STEREO_UPLINK_R_EN_BIT_START  (1)
#define    HISSC_STEREO_UPLINK_R_EN_BIT_END    (1)
/* VOICE上行左通道异步FIFO时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_VOICE_UPLINK_L_EN_BIT_START   (2)
#define    HISSC_VOICE_UPLINK_L_EN_BIT_END     (2)
/* VOICE上行右通道异步FIFO时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_VOICE_UPLINK_R_EN_BIT_START   (3)
#define    HISSC_VOICE_UPLINK_R_EN_BIT_END     (3)
/* STEREO下行左通道异步FIFO及PGA时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_STEREO_DLINK_L_EN_BIT_START   (4)
#define    HISSC_STEREO_DLINK_L_EN_BIT_END     (4)
/* STEREO下行右通道异步FIFO及PGA时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_STEREO_DLINK_R_EN_BIT_START   (5)
#define    HISSC_STEREO_DLINK_R_EN_BIT_END     (5)
/* VOICE下行通道异步FIFO及PGA时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_VOICE_DLINK_EN_BIT_START      (6)
#define    HISSC_VOICE_DLINK_EN_BIT_END        (6)
/* VOICE下行通道SRC使能，同时控制src的bypass：
0：关闭时钟，src bypass；
1：打开时钟，src 正常工作。 */
#define    HISSC_VOICE_DLINK_SRC_EN_BIT_START  (7)
#define    HISSC_VOICE_DLINK_SRC_EN_BIT_END    (7)
/* S1 I2S接口采样时钟使能。
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_S1_IF_CLK_EN_BIT_START        (8)
#define    HISSC_S1_IF_CLK_EN_BIT_END          (8)
/* I2S S1接口（Digital FM）接口左输入通道PGA时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S1_IL_PGA_EN_BIT_START        (9)
#define    HISSC_S1_IL_PGA_EN_BIT_END          (9)
/* I2S S1接口（Digital FM）接口右输入通道PGA时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S1_IR_PGA_EN_BIT_START        (10)
#define    HISSC_S1_IR_PGA_EN_BIT_END          (10)
/* I2S S2接口（BT）接口左输入通道PGA时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S2_IL_PGA_EN_BIT_START        (12)
#define    HISSC_S2_IL_PGA_EN_BIT_END          (12)
/* I2S S2接口（BT）接口右输入通道PGA时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S2_IR_PGA_EN_BIT_START        (13)
#define    HISSC_S2_IR_PGA_EN_BIT_END          (13)
/* I2S S2接口（BT）接口左输出通道SRC时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S2_OL_SRC_EN_BIT_START        (14)
#define    HISSC_S2_OL_SRC_EN_BIT_END          (14)
/* I2S S2接口（BT）接口左输出通道MIXER时钟使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_S2_OL_MIXER_EN_BIT_START      (15)
#define    HISSC_S2_OL_MIXER_EN_BIT_END        (15)
/* S2 I2S接口采样时钟使能。
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_S2_IF_CLK_EN_BIT_START        (16)
#define    HISSC_S2_IF_CLK_EN_BIT_END          (16)
/* S3 I2S接口采样时钟使能。
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_S3_IF_CLK_EN_BIT_START        (20)
#define    HISSC_S3_IF_CLK_EN_BIT_END          (20)
/* 第三方MODEAM下行通道异步FIFO及PGA时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_THIRDMD_DLINK_EN_BIT_START    (24)
#define    HISSC_THIRDMD_DLINK_EN_BIT_END      (24)
/* 第三方MODEAM上行通道异步FIFO时钟使能:
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_THIRDMD_UPLINK_EN_BIT_START   (25)
#define    HISSC_THIRDMD_UPLINK_EN_BIT_END     (25)


/* 寄存器说明：数字滤波器通道相关模块时钟使能配置，包括DACL/DACR/ ADCL/ADCR通道 */
#define HISSC_DIG_FILTER_CLK_EN_CFG_ADDR              ((PAGE_SoCCODEC) + (0x08))
/* ADCL通道PGA模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_ADCL_PGA_EN_BIT_START      (0)
#define    HISSC_ADCL_PGA_EN_BIT_END        (0)
/* ADCL通道HPF模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCL_HPF_EN_BIT_START      (1)
#define    HISSC_ADCL_HPF_EN_BIT_END        (1)
/* ADCL通道HBFVD模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCL_HBFVD_EN_BIT_START    (2)
#define    HISSC_ADCL_HBFVD_EN_BIT_END      (2)
/* ADCL通道HBF2D模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCL_HBF2D_EN_BIT_START    (3)
#define    HISSC_ADCL_HBF2D_EN_BIT_END      (3)
/* ADCL通道COMPD模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCL_COMPD_EN_BIT_START    (4)
#define    HISSC_ADCL_COMPD_EN_BIT_END      (4)
/* ADCL通道CIC模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_ADCL_CIC_EN_BIT_START      (5)
#define    HISSC_ADCL_CIC_EN_BIT_END        (5)
/* SIDETONE PGA模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SIDETONE_PGA_EN_BIT_START  (6)
#define    HISSC_SIDETONE_PGA_EN_BIT_END    (6)
/* ADCR通道PGA模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_ADCR_PGA_EN_BIT_START      (8)
#define    HISSC_ADCR_PGA_EN_BIT_END        (8)
/* ADCR通道HPF模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCR_HPF_EN_BIT_START      (9)
#define    HISSC_ADCR_HPF_EN_BIT_END        (9)
/* ADCR通道HBFVD模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCR_HBFVD_EN_BIT_START    (10)
#define    HISSC_ADCR_HBFVD_EN_BIT_END      (10)
/* ADCR通道HBF2D模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCR_HBF2D_EN_BIT_START    (11)
#define    HISSC_ADCR_HBF2D_EN_BIT_END      (11)
/* ADCR通道COMPD模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_ADCR_COMPD_EN_BIT_START    (12)
#define    HISSC_ADCR_COMPD_EN_BIT_END      (12)
/* ADCR通道CIC模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_ADCR_CIC_EN_BIT_START      (13)
#define    HISSC_ADCR_CIC_EN_BIT_END        (13)
/* DACL通道AGC模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACL_AGC_EN_BIT_START      (16)
#define    HISSC_DACL_AGC_EN_BIT_END        (16)
/* DACL通道MIXER模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACL_MIXER_EN_BIT_START    (17)
#define    HISSC_DACL_MIXER_EN_BIT_END      (17)
/* DACL通道DEEMP模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACL_DEEMP_EN_BIT_START    (18)
#define    HISSC_DACL_DEEMP_EN_BIT_END      (18)
/* DACL通道HBF1I模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACL_HBF1I_EN_BIT_START    (19)
#define    HISSC_DACL_HBF1I_EN_BIT_END      (19)
/* DACL通道HBF2I模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACL_HBF2I_EN_BIT_START    (20)
#define    HISSC_DACL_HBF2I_EN_BIT_END      (20)
/* DACL通道COMPI模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACL_COMPI_EN_BIT_START    (21)
#define    HISSC_DACL_COMPI_EN_BIT_END      (21)
/* DACL通道SDM模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACL_SDM_EN_BIT_START      (22)
#define    HISSC_DACL_SDM_EN_BIT_END        (22)
/* DACR通道AGC模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACR_AGC_EN_BIT_START      (24)
#define    HISSC_DACR_AGC_EN_BIT_END        (24)
/* DACR通道MIXER模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACR_MIXER_EN_BIT_START    (25)
#define    HISSC_DACR_MIXER_EN_BIT_END      (25)
/* DACR通道DEEMP模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACR_DEEMP_EN_BIT_START    (26)
#define    HISSC_DACR_DEEMP_EN_BIT_END      (26)
/* DACR通道HBF1I模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACR_HBF1I_EN_BIT_START    (27)
#define    HISSC_DACR_HBF1I_EN_BIT_END      (27)
/* DACR通道HBF2I模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACR_HBF2I_EN_BIT_START    (28)
#define    HISSC_DACR_HBF2I_EN_BIT_END      (28)
/* DACR通道COMPI模块时钟使能：
0：关闭时钟，bypass；
1：打开时钟。 */
#define    HISSC_DACR_COMPI_EN_BIT_START    (29)
#define    HISSC_DACR_COMPI_EN_BIT_END      (29)
/* DACR通道SDM模块时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_DACR_SDM_EN_BIT_START      (30)
#define    HISSC_DACR_SDM_EN_BIT_END        (30)


/* 寄存器说明：采样率配置 */
#define HISSC_FS_CFG_ADDR                             ((PAGE_SoCCODEC) + (0x0C))
/* VOICE下行通道采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_VOICE_DLINK_BIT_START     (0)
#define    HISSC_FS_VOICE_DLINK_BIT_END       (2)
/* STEREO下行左通道采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_STEREO_DLINK_L_BIT_START  (4)
#define    HISSC_FS_STEREO_DLINK_L_BIT_END    (6)
/* STEREO下行右通道采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_STEREO_DLINK_R_BIT_START  (8)
#define    HISSC_FS_STEREO_DLINK_R_BIT_END    (10)
/* dacl和dacr通道输入侧采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_DACLR_BIT_START           (16)
#define    HISSC_FS_DACLR_BIT_END             (18)
/* adcl和adcr通道输出侧采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_ADCLR_BIT_START           (20)
#define    HISSC_FS_ADCLR_BIT_END             (22)
/* S1接口采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_S1_BIT_START              (24)
#define    HISSC_FS_S1_BIT_END                (26)
/* S2接口采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_S2_BIT_START              (28)
#define    HISSC_FS_S2_BIT_END                (30)


/* 寄存器说明：S1/S2接口配置寄存器 */
#define HISSC_I2S_CFG_ADDR                            ((PAGE_SoCCODEC) + (0x10))
/* S1接口模式选择：
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
其他：保留 */
#define    HISSC_S1_FUNC_MODE_BIT_START            (0)
#define    HISSC_S1_FUNC_MODE_BIT_END              (2)
/* S1接口Codec ADC/DAC数据格式选择。
0：表示二进制补码；
1：表示二进制码（binary offset）。 */
#define    HISSC_S1_CODEC_DATA_FORMAT_BIT_START    (3)
#define    HISSC_S1_CODEC_DATA_FORMAT_BIT_END      (3)
/* S1接口RX方向时钟选择：
1'b0:BCLK上升沿接收数据
1'b1:BCLK下降沿接收数据 */
#define    HISSC_S1_RX_CLK_SEL_BIT_START           (4)
#define    HISSC_S1_RX_CLK_SEL_BIT_END             (4)
/* S1接口TX方向时钟选择：
1'b0:BCLK上升沿打出数据
1'b1:BCLK下降沿打出数据 */
#define    HISSC_S1_TX_CLK_SEL_BIT_START           (5)
#define    HISSC_S1_TX_CLK_SEL_BIT_END             (5)
/* S1 I2S接口环回模式选择。
2'b00：正常工作模式；
2'b01：Sdin->Sdout。
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: 保留 */
#define    HISSC_S1_DIRECT_LOOP_BIT_START          (6)
#define    HISSC_S1_DIRECT_LOOP_BIT_END            (7)
/* S1接口位数控制。
00：16bit；
01：18bit；
10：20bit；
11：24bit。 */
#define    HISSC_S1_CODEC_IO_WORDLENGTH_BIT_START  (8)
#define    HISSC_S1_CODEC_IO_WORDLENGTH_BIT_END    (9)
/* S1接口声道配置：
1'b0:左声道在前
1'b1:右声道在前 */
#define    HISSC_S1_CHNNL_MODE_BIT_START           (10)
#define    HISSC_S1_CHNNL_MODE_BIT_END             (10)
/* S1接口帧同步信号左右声道选择：
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S1_LRCLK_MODE_BIT_START           (11)
#define    HISSC_S1_LRCLK_MODE_BIT_END             (11)
/* S1接口Master/Slave模式选择：
1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
1'b1:Slave模式 */
#define    HISSC_S1_MST_SLV_BIT_START              (12)
#define    HISSC_S1_MST_SLV_BIT_END                (12)
/* S1接口I2S模式下帧格式配置：
1'b0:I2S模式下64bit frame，PCM模式下32bit frame
1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
#define    HISSC_S1_FRAME_MODE_BIT_START           (13)
#define    HISSC_S1_FRAME_MODE_BIT_END             (13)
/* S1接口RX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S1_IF_RX_ENA_BIT_START            (14)
#define    HISSC_S1_IF_RX_ENA_BIT_END              (14)
/* S1接口TX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S1_IF_TX_ENA_BIT_START            (15)
#define    HISSC_S1_IF_TX_ENA_BIT_END              (15)
/* S2接口模式选择：
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
其他：保留 */
#define    HISSC_S2_FUNC_MODE_BIT_START            (16)
#define    HISSC_S2_FUNC_MODE_BIT_END              (18)
/* S2接口Codec ADC/DAC数据格式选择。
0：表示二进制补码；
1：表示二进制码（binary offset）。 */
#define    HISSC_S2_CODEC_DATA_FORMAT_BIT_START    (19)
#define    HISSC_S2_CODEC_DATA_FORMAT_BIT_END      (19)
/* S2接口RX方向时钟选择：
1'b0:BCLK上升沿接收数据
1'b1:BCLK下降沿接收数据 */
#define    HISSC_S2_RX_CLK_SEL_BIT_START           (20)
#define    HISSC_S2_RX_CLK_SEL_BIT_END             (20)
/* S2接口TX方向时钟选择：
1'b0:BCLK上升沿打出数据
1'b1:BCLK下降沿打出数据 */
#define    HISSC_S2_TX_CLK_SEL_BIT_START           (21)
#define    HISSC_S2_TX_CLK_SEL_BIT_END             (21)
/* S2 I2S接口环回模式选择。
2'b00：正常工作模式；
2'b01：Sdin->Sdout。
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: 保留 */
#define    HISSC_S2_DIRECT_LOOP_BIT_START          (22)
#define    HISSC_S2_DIRECT_LOOP_BIT_END            (23)
/* S2接口位数控制。
00：16bit；
01：18bit；
10：20bit；
11：24bit。 */
#define    HISSC_S2_CODEC_IO_WORDLENGTH_BIT_START  (24)
#define    HISSC_S2_CODEC_IO_WORDLENGTH_BIT_END    (25)
/* S2接口声道配置：
1'b0:左声道在前
1'b1:右声道在前 */
#define    HISSC_S2_CHNNL_MODE_BIT_START           (26)
#define    HISSC_S2_CHNNL_MODE_BIT_END             (26)
/* S2接口帧同步信号左右声道选择：
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S2_LRCLK_MODE_BIT_START           (27)
#define    HISSC_S2_LRCLK_MODE_BIT_END             (27)
/* S2接口Master/Slave模式选择：
1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
1'b1:Slave模式 */
#define    HISSC_S2_MST_SLV_BIT_START              (28)
#define    HISSC_S2_MST_SLV_BIT_END                (28)
/* S2接口I2S模式下帧格式配置：
1'b0:I2S模式下64bit frame，PCM模式下32bit frame
1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
#define    HISSC_S2_FRAME_MODE_BIT_START           (29)
#define    HISSC_S2_FRAME_MODE_BIT_END             (29)
/* S2接口RX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S2_IF_RX_ENA_BIT_START            (30)
#define    HISSC_S2_IF_RX_ENA_BIT_END              (30)
/* S2接口TX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S2_IF_TX_ENA_BIT_START            (31)
#define    HISSC_S2_IF_TX_ENA_BIT_END              (31)


/* 寄存器说明：DAC/ADC通道内部MIXER、模块BYPASS模式配置寄存器。 */
#define HISSC_DIG_FILTER_MODULE_CFG_ADDR              ((PAGE_SoCCODEC) + (0x14))
/* ADCR通道CIC滤波器及回环路径控制。
000：CIC输入为ADC路径输入；
001：CIC输入为DACL路径输入；
010：CIC输入为DACR路径输入；
011：reserved；
100：CIC输入为DMIC PORT0路径输入；
101：reserved；
其他值：ADC路径输入。 */
#define    HISSC_RM_CODEC_DAC2ADC_BIT_START     (0)
#define    HISSC_RM_CODEC_DAC2ADC_BIT_END       (2)
/* ADCL通道CIC滤波器及回环路径控制。
000：CIC输入为ADC路径输入；
001：CIC输入为DACL路径输入；
010：CIC输入为DACR路径输入；
011：reserved；
100：CIC输入为DMIC PORT0路径输入；
101：reserved；
其他值：ADC路径输入。 */
#define    HISSC_LM_CODEC_DAC2ADC_BIT_START     (4)
#define    HISSC_LM_CODEC_DAC2ADC_BIT_END       (6)
/* DACL SDM dither配置。
1：dither电路有效；
0：dither电路无效。 */
#define    HISSC_SW_DACL_SDM_DITHER_BIT_START   (8)
#define    HISSC_SW_DACL_SDM_DITHER_BIT_END     (8)
/* DACR SDM dither配置。
1：dither电路有效；
0：dither电路无效。 */
#define    HISSC_SW_DACR_SDM_DITHER_BIT_START   (9)
#define    HISSC_SW_DACR_SDM_DITHER_BIT_END     (9)
/* DACL通道mixer的mute使能：
1'b1:voice dlink src输出mute
1'b0:正常输入 */
#define    HISSC_DACL_MIXER_IN1_MUTE_BIT_START  (16)
#define    HISSC_DACL_MIXER_IN1_MUTE_BIT_END    (16)
/* DACL通道mixer的mute使能：
1'b1:stereo dlink左通道pga输出mute
1'b0:正常输入
master:dacl_mixer_en */
#define    HISSC_DACL_MIXER_IN2_MUTE_BIT_START  (17)
#define    HISSC_DACL_MIXER_IN2_MUTE_BIT_END    (17)
/* DACL通道mixer的 mute使能：
1'b1:s1左输入通道pga输出mute
1'b0:正常输入 */
#define    HISSC_DACL_MIXER_IN3_MUTE_BIT_START  (18)
#define    HISSC_DACL_MIXER_IN3_MUTE_BIT_END    (18)
/* DACL通道mixer mute使能：
1'b1:sidetone pga 输出mute
1'b0:正常输入 */
#define    HISSC_DACL_MIXER_IN4_MUTE_BIT_START  (19)
#define    HISSC_DACL_MIXER_IN4_MUTE_BIT_END    (19)
/* DACL通道MIXER的增益配置：
2'b00:1
2'b01:乘以1/2
2'b10:乘以1/4
2'b11:保留 */
#define    HISSC_DACL_MIXER_GAIN_BIT_START      (20)
#define    HISSC_DACL_MIXER_GAIN_BIT_END        (21)
/* DACR通道mixer的mute使能：
1'b1:voice dlink src输出mute
1'b0:正常输入 */
#define    HISSC_DACR_MIXER_IN1_MUTE_BIT_START  (24)
#define    HISSC_DACR_MIXER_IN1_MUTE_BIT_END    (24)
/* DACR通道mixer的mute使能：
1'b1:stereo dlink右通道pga输出mute
1'b0:正常输入 */
#define    HISSC_DACR_MIXER_IN2_MUTE_BIT_START  (25)
#define    HISSC_DACR_MIXER_IN2_MUTE_BIT_END    (25)
/* DACR通道mixer的 mute使能：
1'b1:s1右输入通道pga输出mute
1'b0:正常输入 */
#define    HISSC_DACR_MIXER_IN3_MUTE_BIT_START  (26)
#define    HISSC_DACR_MIXER_IN3_MUTE_BIT_END    (26)
/* DACR通道mixer mute使能：
1'b1:sidetone pga 输出mutemute
1'b0:正常输入 */
#define    HISSC_DACR_MIXER_IN4_MUTE_BIT_START  (27)
#define    HISSC_DACR_MIXER_IN4_MUTE_BIT_END    (27)
/* DACR通道MIXER的增益配置：
2'b00:1
2'b01:乘以1/2
2'b10:乘以1/4
2'b11:保留 */
#define    HISSC_DACR_MIXER_GAIN_BIT_START      (28)
#define    HISSC_DACR_MIXER_GAIN_BIT_END        (29)


/* 寄存器说明：MUX_TOP中相关模块配置及状态 */
#define HISSC_MUX_TOP_MODULE_CFG_ADDR                 ((PAGE_SoCCODEC) + (0x18))
/* VOICE下行通道SRC MODE选择：
3'b001: 12 interpolation
3'b010: 6 interpolation
3'b011: 2 interpolation
3'b100: 3 interpolation
other: reserved, not work */
#define    HISSC_VOICE_DLINK_SRC_MODE_BIT_START        (0)
#define    HISSC_VOICE_DLINK_SRC_MODE_BIT_END          (2)
/* VOICE下行通道SRC READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中（软件不关心该寄存器则至多丢失一个采样点） */
#define    HISSC_VOICE_DLINK_SRC_RDY_BIT_START         (3)
#define    HISSC_VOICE_DLINK_SRC_RDY_BIT_END           (3)
/* S2 I2S接口SRC MODE选择：
2'b00: 3倍降采样
2'b01:12倍降采样
2'b10:6倍降采样
2'b11:2倍降采样 */
#define    HISSC_S2_OL_SRC_MODE_BIT_START              (4)
#define    HISSC_S2_OL_SRC_MODE_BIT_END                (5)
/* S2 I2S接口左输入通道SRC READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中（软件不关心该寄存器则至多丢失一个采样点） */
#define    HISSC_S2_OL_SRC_RDY_BIT_START               (6)
#define    HISSC_S2_OL_SRC_RDY_BIT_END                 (6)
/* S2接口输出左通道mixer输出mute使能：
1'b1: DACL mixer 输出mute
1'b0:正常输入 */
#define    HISSC_S2_OL_MIXER_IN1_MUTE_BIT_START        (8)
#define    HISSC_S2_OL_MIXER_IN1_MUTE_BIT_END          (8)
/* S2接口输出左通道mixer输出mute使能：
1'b1:DACR mixer 输出mute
1'b0:正常输入 */
#define    HISSC_S2_OL_MIXER_IN2_MUTE_BIT_START        (9)
#define    HISSC_S2_OL_MIXER_IN2_MUTE_BIT_END          (9)
/* S2左输出通道MIXER的增益配置：
2'b00:1
2'b01:乘以1/2
2'b10:保留
2'b11:保留 */
#define    HISSC_S2_OL_MIXER_GAIN_BIT_START            (10)
#define    HISSC_S2_OL_MIXER_GAIN_BIT_END              (11)
/* voice downlink 通道mixer输出mute使能：
1'b1: DACL mixer 输出mute
1'b0:正常输入 */
#define    HISSC_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START  (12)
#define    HISSC_VOICE_DLINK_MIXER_IN1_MUTE_BIT_END    (12)
/* voice downlink 通道mixer输出mute使能：
1'b1:DACR mixer 输出mute
1'b0:正常输入 */
#define    HISSC_VOICE_DLINK_MIXER_IN2_MUTE_BIT_START  (13)
#define    HISSC_VOICE_DLINK_MIXER_IN2_MUTE_BIT_END    (13)
/* voice downlink 通道MIXER的增益配置：
2'b00:1
2'b01:乘以1/2
2'b10:保留
2'b11:保留 */
#define    HISSC_VOICE_DLINK_MIXER_GAIN_BIT_START      (14)
#define    HISSC_VOICE_DLINK_MIXER_GAIN_BIT_END        (15)


/* 寄存器说明：ADC通道PGA模块配置 */
#define HISSC_ADC_PGA_CFG_ADDR                        ((PAGE_SoCCODEC) + (0x1C))
/* ADCL pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_ADCL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_ADCL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* ADCL pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_ADCL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_ADCL_PGA_FRAC_CONFIG_BIT_END       (8)
/* ADCL pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_ADCL_PGA_MUTE_BIT_START            (9)
#define    HISSC_ADCL_PGA_MUTE_BIT_END              (9)
/* ADCL pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_ADCL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_ADCL_PGA_THR_CONFIG_BIT_END        (13)
/* ADCR pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_ADCR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_ADCR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* ADCR pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_ADCR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_ADCR_PGA_FRAC_CONFIG_BIT_END       (24)
/* ADCR pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_ADCR_PGA_MUTE_BIT_START            (25)
#define    HISSC_ADCR_PGA_MUTE_BIT_END              (25)
/* ADCR pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_ADCR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_ADCR_PGA_THR_CONFIG_BIT_END        (29)


/* 寄存器说明：S1接口输入通道PGA配置 */
#define HISSC_S1_INPUT_PGA_CFG_ADDR                   ((PAGE_SoCCODEC) + (0x20))
/* S1 I2S接口左输入通道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_S1_IL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_S1_IL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* S1接口 左输入通道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_S1_IL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_S1_IL_PGA_FRAC_CONFIG_BIT_END       (8)
/* S1接口左输入通道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_S1_IL_PGA_MUTE_BIT_START            (9)
#define    HISSC_S1_IL_PGA_MUTE_BIT_END              (9)
/* S1接口左输入通道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_S1_IL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_S1_IL_PGA_THR_CONFIG_BIT_END        (13)
/* S1 I2S接口右输入通道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_S1_IR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_S1_IR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* S1接口右输入通道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_S1_IR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_S1_IR_PGA_FRAC_CONFIG_BIT_END       (24)
/* S1接口右输入通道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_S1_IR_PGA_MUTE_BIT_START            (25)
#define    HISSC_S1_IR_PGA_MUTE_BIT_END              (25)
/* S1接口右输入通道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_S1_IR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_S1_IR_PGA_THR_CONFIG_BIT_END        (29)


/* 寄存器说明：S2接口输入通道PGA配置 */
#define HISSC_S2_INPUT_PGA_CFG_ADDR                   ((PAGE_SoCCODEC) + (0x24))
/* S2 I2S接口左输入通道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_S2_IL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_S2_IL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* S2接口 左输入通道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_S2_IL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_S2_IL_PGA_FRAC_CONFIG_BIT_END       (8)
/* S2接口左输入通道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_S2_IL_PGA_MUTE_BIT_START            (9)
#define    HISSC_S2_IL_PGA_MUTE_BIT_END              (9)
/* S2接口左输入通道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_S2_IL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_S2_IL_PGA_THR_CONFIG_BIT_END        (13)
/* S2 I2S接口右输入通道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_S2_IR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_S2_IR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* S2接口右输入通道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_S2_IR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_S2_IR_PGA_FRAC_CONFIG_BIT_END       (24)
/* S2接口右输入通道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_S2_IR_PGA_MUTE_BIT_START            (25)
#define    HISSC_S2_IR_PGA_MUTE_BIT_END              (25)
/* S2接口右输入通道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_S2_IR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_S2_IR_PGA_THR_CONFIG_BIT_END        (29)


/* 寄存器说明：STEREO下行通道PGA配置 */
#define HISSC_STEREO_DLINK_PGA_CFG_ADDR               ((PAGE_SoCCODEC) + (0x28))
/* stereo下行左声道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_END    (7)
/* stereo下行左声道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_END       (8)
/* stereo下行左声道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_STEREO_DLINK_L_PGA_MUTE_BIT_START            (9)
#define    HISSC_STEREO_DLINK_L_PGA_MUTE_BIT_END              (9)
/* stereo下行左声道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_END        (13)
/* stereo下行右声道pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_END    (23)
/* stereo下行右声道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_END       (24)
/* stereo下行右声道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_STEREO_DLINK_R_PGA_MUTE_BIT_START            (25)
#define    HISSC_STEREO_DLINK_R_PGA_MUTE_BIT_END              (25)
/* stereo下行右声道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_END        (29)


/* 寄存器说明：VOICE下行通道PGA及SIDETONE PGA配置 */
#define HISSC_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR       ((PAGE_SoCCODEC) + (0x2C))
/* VOICE下行通道pga输入增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。 */
#define    HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_END    (7)
/* VOICE下行通道pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_END       (8)
/* voice下行声道pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_VOICE_DLINK_PGA_MUTE_BIT_START            (9)
#define    HISSC_VOICE_DLINK_PGA_MUTE_BIT_END              (9)
/* voice dlink通道pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_VOICE_DLINK_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_VOICE_DLINK_PGA_THR_CONFIG_BIT_END        (13)
/* SIDETONE pga输入增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。 */
#define    HISSC_SIDETONE_PGA_INTEGER_CONFIG_BIT_START     (16)
#define    HISSC_SIDETONE_PGA_INTEGER_CONFIG_BIT_END       (23)
/* SIDETONE pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_SIDETONE_PGA_FRAC_CONFIG_BIT_START        (24)
#define    HISSC_SIDETONE_PGA_FRAC_CONFIG_BIT_END          (24)
/* SIDETONE pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_SIDETONE_PGA_MUTE_BIT_START               (25)
#define    HISSC_SIDETONE_PGA_MUTE_BIT_END                 (25)
/* sidetone pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_SIDETONE_PGA_THR_CONFIG_BIT_START         (28)
#define    HISSC_SIDETONE_PGA_THR_CONFIG_BIT_END           (29)


/* 寄存器说明：APB IF中AFIFO配置及状态信号 */
#define HISSC_APB_AFIFO_CFG_1_ADDR                    ((PAGE_SoCCODEC) + (0x30))
/* STEREO UPLINK左通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_STEREO_UPLINK_L_FIFO_CLR_BIT_START     (0)
#define    HISSC_STEREO_UPLINK_L_FIFO_CLR_BIT_END       (0)
/* STEREO UPLINK右通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_STEREO_UPLINK_R_FIFO_CLR_BIT_START     (1)
#define    HISSC_STEREO_UPLINK_R_FIFO_CLR_BIT_END       (1)
/* VOICE UPLINK左通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_VOICE_UPLINK_L_FIFO_CLR_BIT_START      (2)
#define    HISSC_VOICE_UPLINK_L_FIFO_CLR_BIT_END        (2)
/* VOICE UPLINK右通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_VOICE_UPLINK_R_FIFO_CLR_BIT_START      (3)
#define    HISSC_VOICE_UPLINK_R_FIFO_CLR_BIT_END        (3)
/* STEREO DLINK左通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_STEREO_DLINK_L_FIFO_CLR_BIT_START      (4)
#define    HISSC_STEREO_DLINK_L_FIFO_CLR_BIT_END        (4)
/* STEREO DLINK右通道AFIFO清空配置：
1'b1: clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_STEREO_DLINK_R_FIFO_CLR_BIT_START      (5)
#define    HISSC_STEREO_DLINK_R_FIFO_CLR_BIT_END        (5)
/* VOICE DLINK通道AFIFO清空配置：
1'b1:clr有效，清除FIFO数据
1'b0: clr无效 */
#define    HISSC_VOICE_DLINK_FIFO_CLR_BIT_START         (6)
#define    HISSC_VOICE_DLINK_FIFO_CLR_BIT_END           (6)
/*  */
#define    HISSC_THIRDMD_DLINK_FIFO_CLR_BIT_START       (7)
#define    HISSC_THIRDMD_DLINK_FIFO_CLR_BIT_END         (7)
/*  */
#define    HISSC_THIRDMD_UPLINK_FIFO_CLR_BIT_START      (8)
#define    HISSC_THIRDMD_UPLINK_FIFO_CLR_BIT_END        (8)
/* STEREO UPLINK左通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_UPLINK_L_FIFO_WERROR_BIT_START  (16)
#define    HISSC_STEREO_UPLINK_L_FIFO_WERROR_BIT_END    (16)
/* STEREO UPLINK右通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_UPLINK_R_FIFO_WERROR_BIT_START  (17)
#define    HISSC_STEREO_UPLINK_R_FIFO_WERROR_BIT_END    (17)
/* VOICE UPLINK左通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_VOICE_UPLINK_L_FIFO_WERROR_BIT_START   (18)
#define    HISSC_VOICE_UPLINK_L_FIFO_WERROR_BIT_END     (18)
/* VOICE UPLINK右通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_VOICE_UPLINK_R_FIFO_WERROR_BIT_START   (19)
#define    HISSC_VOICE_UPLINK_R_FIFO_WERROR_BIT_END     (19)
/* STEREO DLINK左通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_DLINK_L_FIFO_WERROR_BIT_START   (20)
#define    HISSC_STEREO_DLINK_L_FIFO_WERROR_BIT_END     (20)
/* STEREO DLINK右通道AFIFO写error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_DLINK_R_FIFO_WERROR_BIT_START   (21)
#define    HISSC_STEREO_DLINK_R_FIFO_WERROR_BIT_END     (21)
/* VOICE DLINK通道AFIFO写error
1'b1: FIFO满时写数据
1'b0: 正常 */
#define    HISSC_VOICE_DLINK_FIFO_WERROR_BIT_START      (22)
#define    HISSC_VOICE_DLINK_FIFO_WERROR_BIT_END        (22)
/* STEREO UPLINK左通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_UPLINK_L_FIFO_RERROR_BIT_START  (24)
#define    HISSC_STEREO_UPLINK_L_FIFO_RERROR_BIT_END    (24)
/* STEREO UPLINK右通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_UPLINK_R_FIFO_RERROR_BIT_START  (25)
#define    HISSC_STEREO_UPLINK_R_FIFO_RERROR_BIT_END    (25)
/* VOICE UPLINK左通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_VOICE_UPLINK_L_FIFO_RERROR_BIT_START   (26)
#define    HISSC_VOICE_UPLINK_L_FIFO_RERROR_BIT_END     (26)
/* VOICE UPLINK右通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_VOICE_UPLINK_R_FIFO_RERROR_BIT_START   (27)
#define    HISSC_VOICE_UPLINK_R_FIFO_RERROR_BIT_END     (27)
/* STEREO DLINK左通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_DLINK_L_FIFO_RERROR_BIT_START   (28)
#define    HISSC_STEREO_DLINK_L_FIFO_RERROR_BIT_END     (28)
/* STEREO DLINK右通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_STEREO_DLINK_R_FIFO_RERROR_BIT_START   (29)
#define    HISSC_STEREO_DLINK_R_FIFO_RERROR_BIT_END     (29)
/* VOICE DLINK通道AFIFO读error
1'b1: FIFO空时读数据
1'b0: 正常 */
#define    HISSC_VOICE_DLINK_FIFO_RERROR_BIT_START      (30)
#define    HISSC_VOICE_DLINK_FIFO_RERROR_BIT_END        (30)


/* 寄存器说明：APB IF中AFIFO配置及状态信号 */
#define HISSC_APB_AFIFO_CFG_2_ADDR                    ((PAGE_SoCCODEC) + (0x34))
/* VOICE DLINK通道AFIFO将满阈值，fifo中有效数值个数高于该值时，FIFO almost full信号有效 */
#define    HISSC_VOICE_DLINK_FIFO_AFULL_TH_BIT_START     (0)
#define    HISSC_VOICE_DLINK_FIFO_AFULL_TH_BIT_END       (4)
/* VOICE DLINK通道AFIFO将空阈值，fifo中有效数值个数低于该值时，FIFO almost empty信号有效 */
#define    HISSC_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_START    (8)
#define    HISSC_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_END      (12)
/* STEREO UPLINK左通道AFIFO输入数据选择：
1'b1:ADCL通道输出数据
1'b0:S1接口输入左声道 */
#define    HISSC_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_START  (16)
#define    HISSC_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_END    (16)
/* STEREO UPLINK右通道AFIFO输入数据选择：
1'b1:ADCR通道输出数据
1'b0:S1接口输入右声道 */
#define    HISSC_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_START  (17)
#define    HISSC_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_END    (17)
/* VOICE UPLINK左通道AFIFO输入数据选择：
1'b1:ADCL通道输出数据
1'b0:S2接口输入左声道 */
#define    HISSC_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_START   (18)
#define    HISSC_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_END     (18)
/* VOICE UPLINK右通道AFIFO输入数据选择：
1'b1:ADCR通道输出数据
1'b0:S2接口输入右声道 */
#define    HISSC_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_START   (19)
#define    HISSC_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_END     (19)
/* 第三方MODEM UPLINK通道AFIFO输入数据选择：
1'b1:ADCR通道输出数据
1'b0:S3接口输入数据 */
#define    HISSC_THIRDMD_UPLINK_DIN_SEL_BIT_START        (20)
#define    HISSC_THIRDMD_UPLINK_DIN_SEL_BIT_END          (20)


/* 寄存器说明：STEREO下行通道AFIFO 空满水线配置 */
#define HISSC_STEREO_DLINK_FIFO_TH_CFG_ADDR           ((PAGE_SoCCODEC) + (0x38))
/* STEREO DLINK左通道AFIFO将满阈值，同上。 */
#define    HISSC_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* STEREO DLINK左通道AFIFO将空阈值，同上。 */
#define    HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* STEREO DLINK右通道AFIFO将满阈值，同上。 */
#define    HISSC_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_END     (20)
/* STEREO DLINK右通道AFIFO将空阈值，同上。 */
#define    HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* 寄存器说明：STEREO上行通道AFIFO 空满水线配置 */
#define HISSC_STEREO_UPLINK_FIFO_TH_CFG_ADDR          ((PAGE_SoCCODEC) + (0x3C))
/* STEREO UPLINK左通道AFIFO将满阈值，同上。 */
#define    HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* STEREO UPLINK左通道AFIFO将空阈值，同上。 */
#define    HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* STEREO UPLINK右通道AFIFO将满阈值，同上。 */
#define    HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_END     (20)
/* STEREO UPLINK右通道AFIFO将空阈值，同上。 */
#define    HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* 寄存器说明：VOICE上行通道AFIFO 空满水线配置 */
#define HISSC_VOICE_UPLINK_FIFO_TH_CFG_ADDR           ((PAGE_SoCCODEC) + (0x40))
/* VOICE UPLINK左通道AFIFO将满阈值，同上。 */
#define    HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* VOICE UPLINK左通道AFIFO将空阈值，同上。 */
#define    HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* reserved */
#define    HISSC___B1___RIGHT____BIT_START                (13)
#define    HISSC___B1___RIGHT____BIT_END                  (15)
/* VOICE UPLINK右通道AFIFO将满阈值，同上。 */
#define    HISSC___B0___LEFT____BIT_START                 (16)
#define    HISSC___B0___LEFT____BIT_END                   (20)
/* VOICE UPLINK右通道AFIFO将空阈值，同上。 */
#define    HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* 寄存器说明：中断屏蔽寄存器 */
#define HISSC_CODEC_IRQ_MASK_ADDR                     ((PAGE_SoCCODEC) + (0x44))
/* 中断屏蔽位：
[5]: thirdmd uplink中断屏蔽
[4]: thirdmd dlink 中断屏蔽
[3]: voice uplink中断屏蔽
[2]: stereo uplink中断屏蔽
[1]: stereo dlink中断屏蔽
[0]: voice dlink中断屏蔽 */
#define    HISSC_CODEC_DATA_INTRP_MASK_BIT_START  (0)
#define    HISSC_CODEC_DATA_INTRP_MASK_BIT_END    (5)


/* 寄存器说明：中断状态寄存器 */
#define HISSC_CODEC_IRQ_ADDR                          ((PAGE_SoCCODEC) + (0x48))
/* 中断状态位：
[5]: thirdmd uplink中断，为1时表示thirdmd uplink请求Master读数据
[4]: thirdmd dlink 中断，为1时表示thirdmd dlink 请求Master读数据
[3]: voice uplink中断，为1时表示voice uplink请求Master读数据
[2]: stereo uplink中断，为1时表示voice uplink请求Master读数据
[1]: stereo dlink中断，为1时表示stereo dplink请求Master送数据
[0]: voice dlink中断，为1时表示voice uplink请求Master送数据 */
#define    HISSC_CODEC_DATA_INTRP_BIT_START  (0)
#define    HISSC_CODEC_DATA_INTRP_BIT_END    (5)


/* 寄存器说明：DACL AGC (自动增益控制)配置寄存器1。 */
#define HISSC_DACL_AGC_CFG_1_ADDR                     ((PAGE_SoCCODEC) + (0x4C))
/* AGC立即下调电平窗口增益配置。
00：3.5dB；
01：5.5dB；
10：9dB；
11：15dB。 */
#define    HISSC_DACL_AGC_GWIN_CONFIG_BIT_START      (0)
#define    HISSC_DACL_AGC_GWIN_CONFIG_BIT_END        (1)
/* AGC低电平门限增益配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_DACL_AGC_LEVELLOW_CONFIG_BIT_START  (2)
#define    HISSC_DACL_AGC_LEVELLOW_CONFIG_BIT_END    (3)
/* AGC增益下调的步长增益配置。
00：0.5dB；
01：1dB；
10：1.5dB；
11：2dB； */
#define    HISSC_DACL_AGC_GSTEPD_CONFIG_BIT_START    (4)
#define    HISSC_DACL_AGC_GSTEPD_CONFIG_BIT_END      (5)
/* AGC静音等待时间配置。
采样频率为48KHz：
00：187.5ms；
01：375ms；
10：750ms；
11：1.5s；
采样频率为96KHz：
00：N/A；
01：187.5ms；
10：375ms；
11：750ms。  */
#define    HISSC_DACL_AGC_TIMEMUTE_CONFIG_BIT_START  (6)
#define    HISSC_DACL_AGC_TIMEMUTE_CONFIG_BIT_END    (7)
/* AGC噪声判断迟滞增益窗配置。
00：0dB；
01：1dB；
10：2dB；
11：4dB。 */
#define    HISSC_DACL_AGC_NGW_CONFIG_BIT_START       (8)
#define    HISSC_DACL_AGC_NGW_CONFIG_BIT_END         (9)
/* AGC输出信号目标增益幅度配置。
000：-4dB；
001：-6dB；
010：-9dB；
011：-12dB；
100：-15dB；
101：-18dB；
110：-21dB；
111：-24dB。 */
#define    HISSC_DACL_AGC_YTARGET_CONFIG_BIT_START   (10)
#define    HISSC_DACL_AGC_YTARGET_CONFIG_BIT_END     (12)
/* AGC增益下调的最小时间间隔配置。
采样频率为48KHz：
00：1/24ms；
01：0.125ms；
10：0.75ms；
11：1.5ms。
采样频率为96KHz：
00：1/48ms；
01：0.0625ms；
10：0.375ms；
11：0.75ms。 */
#define    HISSC_DACL_AGC_T_AMIN_CONFIG_BIT_START    (13)
#define    HISSC_DACL_AGC_T_AMIN_CONFIG_BIT_END      (14)
/* AGC增益压缩使能标志配置。
0：非压缩；
1：压缩。 */
#define    HISSC_DACL_AGC_GSUPPRESS_BIT_START        (15)
#define    HISSC_DACL_AGC_GSUPPRESS_BIT_END          (15)
/* AGC中包络检测慢速下降速率选择。
00：选择1/2^(10)速率；
01：选择1/2^(11)速率；
10：选择1/2^(12)速率；
11：选择1/2^(13)速率。 */
#define    HISSC_DACL_AGC_KFSLOW_BIT_START           (16)
#define    HISSC_DACL_AGC_KFSLOW_BIT_END             (17)
/* AGC中包络检测快速下降速率选择。
00：选择1/2^(6)速率；
01：选择1/2^(7)速率；
10：选择1/2^(8)速率；
11：选择1/2^(9)速率。 */
#define    HISSC_DACL_AGC_KFRAPID_BIT_START          (18)
#define    HISSC_DACL_AGC_KFRAPID_BIT_END            (19)
/* AGC噪声阈值最低值配置。
00：等于噪声阈值初始值配置；
01：等于噪声阈值初始值配置减去6dB；
10：等于噪声阈值初始值配置减去18dB；
11：等于-90dB。 */
#define    HISSC_DACL_AGC_NGL_CONFIG_BIT_START       (20)
#define    HISSC_DACL_AGC_NGL_CONFIG_BIT_END         (21)
/* AGC噪声阈值最大值配置。
00：等于噪声阈值初始值配置；
01：等于噪声阈值初始值配置加12dB；
10：等于噪声阈值初始值配置加18dB；
11：等于-24dB。 */
#define    HISSC_DACL_AGC_NGH_CONFIG_BIT_START       (22)
#define    HISSC_DACL_AGC_NGH_CONFIG_BIT_END         (23)
/* AGC时间选择配置。
采样频率为48KHz时：
000：96个采样周期；
001：192个采样周期；
010：384个采样周期；
b011：768个采样周期；
100：1536个采样周期；
101：3072个采样周期；
110：6144个采样周期；
111：12288个采样周期。
采样频率为96KHz时：
000：N/A；
001：96个采样周期；
010：192个采样周期；
011：384个采样周期；
100：768个采样周期；
101：1536个采样周期；
110：3072个采样周期；
111：6144个采样周期。 */
#define    HISSC_DACL_AGC_TIMER_BIT_START            (24)
#define    HISSC_DACL_AGC_TIMER_BIT_END              (26)
/* AGC噪声阈值初始值增益配置。
000：-72dB；
001：-66dB；
010：-60dB；
011：-54dB；
100：-51dB；
101：-48dB；
110：-42dB；
111：-36dB。 */
#define    HISSC_DACL_AGC_NGI_CONFIG_BIT_START       (27)
#define    HISSC_DACL_AGC_NGI_CONFIG_BIT_END         (29)
/* AGC噪声阈值更新时间配置。
采样频率为48KHz：
00：时间选择配置的1.5倍；
01：时间选择配置的2倍；
10：时间选择配置的4倍；
11：选择2秒。
采样频率为96KHz：
00：时间选择配置的1.5倍；
01：时间选择配置的2倍；
10：时间选择配置的4倍；
11：选择1秒 */
#define    HISSC_DACL_AGC_TIMENNG_CONFIG_BIT_START   (30)
#define    HISSC_DACL_AGC_TIMENNG_CONFIG_BIT_END     (31)


/* 寄存器说明：DACL AGC (自动增益控制)配置寄存器2。 */
#define HISSC_DACL_AGC_CFG_2_ADDR                     ((PAGE_SoCCODEC) + (0x50))
/* AGC每次上调增益的时间间隔配置。
采样频率为48KHz：
00：时间选择配置的1/4；
01：时间选择配置的1/8；
10：时间选择配置的1/16；
11：0.25ms。
采样频率为96KHz：
00：时间选择配置的1/4；
01：时间选择配置的1/8；
10：时间选择配置的1/16；
11：0.125ms。 */
#define    HISSC_DACL_AGC_TIMEDECAY_CONFIG_BIT_START  (0)
#define    HISSC_DACL_AGC_TIMEDECAY_CONFIG_BIT_END    (1)
/* AGC增益上调之前的等待时间配置。
00：时间选择配置的1/8；
01：时间选择配置的1/4；
10：时间选择配置的1/2；
11：时间选择配置的3/4。 */
#define    HISSC_DACL_AGC_TIMEGHOLD_CONFIG_BIT_START  (2)
#define    HISSC_DACL_AGC_TIMEGHOLD_CONFIG_BIT_END    (3)
/* AGC静音状态下的增益配置。
00：0dB；
01：-12dB；
10：-24dB；
11：-42dB。 */
#define    HISSC_DACL_AGC_GMUTE_CONFIG_BIT_START      (4)
#define    HISSC_DACL_AGC_GMUTE_CONFIG_BIT_END        (5)
/* AGC静音功能禁止标志配置。
0：禁止；
1：开启。 */
#define    HISSC_DACL_AGC_MUTE_BYPASS_BIT_START       (6)
#define    HISSC_DACL_AGC_MUTE_BYPASS_BIT_END         (6)
/* AGC功能bypass使能信号。
1：AGC功能禁止；
0：采用自动增益控制。 */
#define    HISSC_DACL_AGC_BYPASS_BIT_START            (7)
#define    HISSC_DACL_AGC_BYPASS_BIT_END              (7)
/* AGC功能bypass时，用户输入增益配置系数。与dB乘法器一样，为整数位配置。
默认：0dB；普通增益调节模块的增益范围：-72dB～+36dB，即：
0010_0100：36dB；
0010_0011：35dB；
……
1011_1000：-72dB。
步长为1dB，补码表示。 */
#define    HISSC_DACL_AGC_USR_GDB_INTEGER_BIT_START   (8)
#define    HISSC_DACL_AGC_USR_GDB_INTEGER_BIT_END     (15)
/* DACL AGC用户输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_DACL_AGC_USR_GDB_FRAC_BIT_START      (16)
#define    HISSC_DACL_AGC_USR_GDB_FRAC_BIT_END        (16)
/* DACL通道AGC软复位配置。
0：无效；
1：复位。 */
#define    HISSC_DACL_AGC_SW_CLR_BIT_START            (17)
#define    HISSC_DACL_AGC_SW_CLR_BIT_END              (17)


/* 寄存器说明：DACR AGC (自动增益控制)配置寄存器1。 */
#define HISSC_DACR_AGC_CFG_1_ADDR                     ((PAGE_SoCCODEC) + (0x54))
/* AGC立即下调电平窗口增益配置。
00：3.5dB；
01：5.5dB；
10：9dB；
11：15dB。 */
#define    HISSC_DACR_AGC_GWIN_CONFIG_BIT_START      (0)
#define    HISSC_DACR_AGC_GWIN_CONFIG_BIT_END        (1)
/* AGC低电平门限增益配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_DACR_AGC_LEVELLOW_CONFIG_BIT_START  (2)
#define    HISSC_DACR_AGC_LEVELLOW_CONFIG_BIT_END    (3)
/* AGC增益下调的步长增益配置。
00：0.5dB；
01：1dB；
10：1.5dB；
11：2dB； */
#define    HISSC_DACR_AGC_GSTEPD_CONFIG_BIT_START    (4)
#define    HISSC_DACR_AGC_GSTEPD_CONFIG_BIT_END      (5)
/* AGC静音等待时间配置。
采样频率为48KHz：
00：187.5ms；
01：375ms；
10：750ms；
11：1.5s；
采样频率为96KHz：
00：N/A；
01：187.5ms；
10：375ms；
11：750ms。  */
#define    HISSC_DACR_AGC_TIMEMUTE_CONFIG_BIT_START  (6)
#define    HISSC_DACR_AGC_TIMEMUTE_CONFIG_BIT_END    (7)
/* AGC噪声判断迟滞增益窗配置。
增益范围:0dB~4dB。
步长为1dB。
00：0dB；
01：1dB；
10：2dB；
11：4dB。 */
#define    HISSC_DACR_AGC_NGW_CONFIG_BIT_START       (8)
#define    HISSC_DACR_AGC_NGW_CONFIG_BIT_END         (9)
/* AGC输出信号目标增益幅度配置。
增益范围:-24dB~-4dB。
步长为2dB。
000：-4dB；
001：-6dB；
010：-9dB；
011：-12dB；
100：-15dB；
101：-18dB；
110：-21dB；
111：-24dB。 */
#define    HISSC_DACR_AGC_YTARGET_CONFIG_BIT_START   (10)
#define    HISSC_DACR_AGC_YTARGET_CONFIG_BIT_END     (12)
/* AGC增益下调的最小时间间隔配置。
采样频率为48KHz：
00：1/24ms；
01：0.125ms；
10：0.75ms；
11：1.5ms。
采样频率为96KHz：
00：1/48ms；
01：0.0625ms；
10：0.375ms；
11：0.75ms。 */
#define    HISSC_DACR_AGC_T_AMIN_CONFIG_BIT_START    (13)
#define    HISSC_DACR_AGC_T_AMIN_CONFIG_BIT_END      (14)
/* AGC增益压缩使能标志配置。
0：非压缩；
1：压缩。 */
#define    HISSC_DACR_AGC_GSUPPRESS_BIT_START        (15)
#define    HISSC_DACR_AGC_GSUPPRESS_BIT_END          (15)
/* AGC中包络检测慢速下降速率选择。
00：选择1/2^(10)速率；
01：选择1/2^(11)速率；
10：选择1/2^(12)速率；
11：选择1/2^(13)速率。 */
#define    HISSC_DACR_AGC_KFSLOW_BIT_START           (16)
#define    HISSC_DACR_AGC_KFSLOW_BIT_END             (17)
/* AGC中包络检测快速下降速率选择。
00：选择1/2^(6)速率；
01：选择1/2^(7)速率；
10：选择1/2^(8)速率；
11：选择1/2^(9)速率。 */
#define    HISSC_DACR_AGC_KFRAPID_BIT_START          (18)
#define    HISSC_DACR_AGC_KFRAPID_BIT_END            (19)
/* AGC噪声阈值最低值配置。
00：等于噪声阈值初始值配置；
01：等于噪声阈值初始值配置减去6dB；
10：等于噪声阈值初始值配置减去18dB；
11：等于-90dB。 */
#define    HISSC_DACR_AGC_NGL_CONFIG_BIT_START       (20)
#define    HISSC_DACR_AGC_NGL_CONFIG_BIT_END         (21)
/* AGC噪声阈值最大值配置。
00：等于噪声阈值初始值配置；
01：等于噪声阈值初始值配置加12dB；
10：等于噪声阈值初始值配置加18dB；
11：等于-24dB。 */
#define    HISSC_DACR_AGC_NGH_CONFIG_BIT_START       (22)
#define    HISSC_DACR_AGC_NGH_CONFIG_BIT_END         (23)
/* AGC时间选择配置。
采样频率为48KHz时：
000：96个采样周期；
001：192个采样周期；
010：384个采样周期；
b011：768个采样周期；
100：1536个采样周期；
101：3072个采样周期；
110：6144个采样周期；
111：12288个采样周期。
采样频率为96KHz时：
000：N/A；
001：96个采样周期；
010：192个采样周期；
011：384个采样周期；
100：768个采样周期；
101：1536个采样周期；
110：3072个采样周期；
111：6144个采样周期。 */
#define    HISSC_DACR_AGC_TIMER_BIT_START            (24)
#define    HISSC_DACR_AGC_TIMER_BIT_END              (26)
/* AGC噪声阈值初始值增益配置。
增益范围:-72dB~-36dB。
步长为6dB。
000：-72dB；
001：-66dB；
010：-60dB；
011：-54dB；
100：-51dB；
101：-48dB；
110：-42dB；
111：-36dB。 */
#define    HISSC_DACR_AGC_NGI_CONFIG_BIT_START       (27)
#define    HISSC_DACR_AGC_NGI_CONFIG_BIT_END         (29)
/* AGC噪声阈值更新时间配置。
采样频率为48KHz：
00：时间选择配置的1.5倍；
01：时间选择配置的2倍；
10：时间选择配置的4倍；
11：选择2秒。
采样频率为96KHz：
00：时间选择配置的1.5倍；
01：时间选择配置的2倍；
10：时间选择配置的4倍；
11：选择1秒 */
#define    HISSC_DACR_AGC_TIMENNG_CONFIG_BIT_START   (30)
#define    HISSC_DACR_AGC_TIMENNG_CONFIG_BIT_END     (31)


/* 寄存器说明：DACR AGC (自动增益控制)配置寄存器2。 */
#define HISSC_DACR_AGC_CFG_2_ADDR                     ((PAGE_SoCCODEC) + (0x58))
/* AGC每次上调增益的时间间隔配置。
采样频率为48KHz：
00：时间选择配置的1/4；
01：时间选择配置的1/8；
10：时间选择配置的1/16；
11：0.25ms。
采样频率为96KHz：
00：时间选择配置的1/4；
01：时间选择配置的1/8；
10：时间选择配置的1/16；
11：0.125ms。 */
#define    HISSC_DACR_AGC_TIMEDECAY_CONFIG_BIT_START  (0)
#define    HISSC_DACR_AGC_TIMEDECAY_CONFIG_BIT_END    (1)
/* AGC增益上调之前的等待时间配置。
00：时间选择配置的1/8；
01：时间选择配置的1/4；
10：时间选择配置的1/2；
11：时间选择配置的3/4。 */
#define    HISSC_DACR_AGC_TIMEGHOLD_CONFIG_BIT_START  (2)
#define    HISSC_DACR_AGC_TIMEGHOLD_CONFIG_BIT_END    (3)
/* AGC静音状态下的增益配置。
00：0dB；
01：-12dB；
10：-24dB；
11：-42dB。 */
#define    HISSC_DACR_AGC_GMUTE_CONFIG_BIT_START      (4)
#define    HISSC_DACR_AGC_GMUTE_CONFIG_BIT_END        (5)
/* AGC静音功能禁止标志配置。
0：禁止；
1：开启。 */
#define    HISSC_DACR_AGC_MUTE_BYPASS_BIT_START       (6)
#define    HISSC_DACR_AGC_MUTE_BYPASS_BIT_END         (6)
/* AGC功能bypass使能信号。
1：AGC功能禁止；
0：采用自动增益控制。 */
#define    HISSC_DACR_AGC_BYPASS_BIT_START            (7)
#define    HISSC_DACR_AGC_BYPASS_BIT_END              (7)
/* AGC功能bypass时，用户输入增益配置系数。与dB乘法器一样，为整数位配置。
默认：0dB；普通增益调节模块的增益范围：-72dB～+36dB，即：
0010_0100：36dB；
0010_0011：35dB；
……
1011_1000：-72dB。
步长为1dB，补码表示。 */
#define    HISSC_DACR_AGC_USR_GDB_INTEGER_BIT_START   (8)
#define    HISSC_DACR_AGC_USR_GDB_INTEGER_BIT_END     (15)
/* DACR AGC用户输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_DACR_AGC_USR_GDB_FRAC_BIT_START      (16)
#define    HISSC_DACR_AGC_USR_GDB_FRAC_BIT_END        (16)
/* DACR通道AGC软复位配置。
0：无效；
1：复位。 */
#define    HISSC_DACR_AGC_SW_CLR_BIT_START            (17)
#define    HISSC_DACR_AGC_SW_CLR_BIT_END              (17)


/* 寄存器说明：DMIC接口和Serial接口配置 */
#define HISSC_DMIC_SIF_CFG_ADDR                       ((PAGE_SoCCODEC) + (0x5C))
/* SIF ADCL方向使能：
1：接收串行接口送进来数据
0：不接收数据 */
#define    HISSC_SIF_ADCL_EN_BIT_START       (0)
#define    HISSC_SIF_ADCL_EN_BIT_END         (0)
/* SIF ADCR方向使能：
1：接收串行接口送进来数据
0：不接收数据 */
#define    HISSC_SIF_ADCR_EN_BIT_START       (1)
#define    HISSC_SIF_ADCR_EN_BIT_END         (1)
/* SIF DACL方向使能：
1：向串行接口发送数据
0：不发送数据 */
#define    HISSC_SIF_DACL_EN_BIT_START       (2)
#define    HISSC_SIF_DACL_EN_BIT_END         (2)
/* SIF DACR方向使能：
1：向串行接口发送数据
0：不发送数据 */
#define    HISSC_SIF_DACR_EN_BIT_START       (3)
#define    HISSC_SIF_DACR_EN_BIT_END         (3)
/* SIF 数据环回：
1：ADC并行输出环回到DAC的并行输入
0：不环回 */
#define    HISSC_DAC_P2S_LOOPBACK_BIT_START  (4)
#define    HISSC_DAC_P2S_LOOPBACK_BIT_END    (4)
/* SIF串行输出数据环回使能：
1：DAC串行输出环回到ADC串行输入
0：不环回 */
#define    HISSC_SIF_S2P_LOOPBACK_BIT_START  (5)
#define    HISSC_SIF_S2P_LOOPBACK_BIT_END    (5)
/* sif模块时钟沿选择：
1'b1: SIF时钟与输入的49.152M时钟反相
1'b0: SIF时钟与输入的49.152M时钟同相 */
#define    HISSC_SIF_EDGE_SEL_BIT_START      (6)
#define    HISSC_SIF_EDGE_SEL_BIT_END        (6)
/* 与smartStar接口使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_SIF_EN_BIT_START            (7)
#define    HISSC_SIF_EN_BIT_END              (7)
/* DMIC声道配置。
0：不交换左右声道；
1：交换左右声道。 */
#define    HISSC_SW_DMIC_MODE_BIT_START      (16)
#define    HISSC_SW_DMIC_MODE_BIT_END        (16)
/* DMIC输入编码配置。
0：0 -> -4, 1 -> +4；
1：0 -> +4, 1 -> -4。 */
#define    HISSC_DMIC_REVERSE_BIT_START      (17)
#define    HISSC_DMIC_REVERSE_BIT_END        (17)
/* DMIC时钟配置。
2'b00：关闭时钟；
2'b01：2分频；
2'b10：3分频；
2'b11：4分频。 */
#define    HISSC_FS_DMIC_BIT_START           (18)
#define    HISSC_FS_DMIC_BIT_END             (19)
/* DMIC接口使能：
0：关闭时钟
1：打开时钟 */
#define    HISSC_DMIC_EN_BIT_START           (20)
#define    HISSC_DMIC_EN_BIT_END             (20)


/* 寄存器说明：Misc Config */
#define HISSC_MISC_CFG_ADDR                           ((PAGE_SoCCODEC) + (0x60))
/* S2接口（BT接口）左输出通道输出数据第一级选择，MUX6：
1'b0: 选择降采样SRC3输出；
1'b1: 选择voice dlink通道pga输出； */
#define    HISSC_S2_DOUT_LEFT_SEL_BIT_START                 (0)
#define    HISSC_S2_DOUT_LEFT_SEL_BIT_END                   (0)
/* S1输出通道数据选择，左右声道均受其控制，MUX8/MUX9：
1'b0: 左声道选择DACL MIXER输出；右声道选择DACR MIXER输出；
1'b1: 左声道选择adcl数字滤波器通道输出;右声道选择adcr数字滤波器通道输出 */
#define    HISSC_S1_DOUT_TEST_SEL_BIT_START                 (1)
#define    HISSC_S1_DOUT_TEST_SEL_BIT_END                   (1)
/* S2接口（BT接口）输出通道输出数据第二级选择，改变左声道输出，MUX7：
1'b0: 选择功能路径数据（voice dlink pga或者S2降采样输出）；
1'b1: 选择DACL MIXER输出； */
#define    HISSC_S2_DOUT_TEST_SEL_BIT_START                 (2)
#define    HISSC_S2_DOUT_TEST_SEL_BIT_END                   (2)
/* STEREO DLINK通道输入数据选择，MUX11/MUX12：
1'b0:来自于APB总线
1'b1:S1接口左声道输入stereo_dlink_l ,S1接口右声道输入stereo_dlink_r */
#define    HISSC_STEREO_DLINK_TEST_SEL_BIT_START            (4)
#define    HISSC_STEREO_DLINK_TEST_SEL_BIT_END              (4)
/* VOICE DLINK通道输入数据选择：
1'b0:来自于APB总线
1'b1:S3接口输入左声道 */
#define    HISSC_VOICE_DLINK_DIN_SEL_BIT_START              (6)
#define    HISSC_VOICE_DLINK_DIN_SEL_BIT_END                (6)
/* VOICE DLINK通道输入数据选择，MUX10
1'b0:来自于前级选择FrontSel输出
1'b1:S2接口输入左声道 */
#define    HISSC_VOICE_DLINK_TEST_SEL_BIT_START             (7)
#define    HISSC_VOICE_DLINK_TEST_SEL_BIT_END               (7)
/* VOICE下行通道SRC模块输出采样率选择：
1'b0: 输出为48kHz
1'b1: 输出为96kHz */
#define    HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_START  (8)
#define    HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_END    (8)
/* s3输入选择：
1'b0: 选择Left声道；
1'b1: 选择Right声道； */
#define    HISSC_S3_DIN_TEST_SEL_BIT_START                  (12)
#define    HISSC_S3_DIN_TEST_SEL_BIT_END                    (12)
/* S3接口左输出通道选择信号：
1'b0: thirdmd dlink pga输出；
1'b1: adcl通道pga输出 */
#define    HISSC_S3_DOUT_LEFT_SEL_BIT_START                 (13)
#define    HISSC_S3_DOUT_LEFT_SEL_BIT_END                   (13)
/* S3接口右输出通道选择信号：
2'b00: thirdmd dlink pga输出；
2'b01: adcr通道pga输出;
other: 0; */
#define    HISSC_S3_DOUT_RIGHT_SEL_BIT_START                (14)
#define    HISSC_S3_DOUT_RIGHT_SEL_BIT_END                  (15)
/* thirdmd_dlink通道输入数据选择输入：
1'b0: APB thirdmd下行通道
1'b1: S2左输入声道 */
#define    HISSC_THIRDMD_DLINK_DIN_SEL_BIT_START            (16)
#define    HISSC_THIRDMD_DLINK_DIN_SEL_BIT_END              (16)
/* thirdmd_dlink通道测试数据选择输入：
1'b0: 从APB thirdmd下行通道或S2输入中选择
1'b1: S3输入 */
#define    HISSC_THIRDMD_DLINK_TEST_SEL_BIT_START           (17)
#define    HISSC_THIRDMD_DLINK_TEST_SEL_BIT_END             (17)


/* 寄存器说明：S2接口SRC模块配置 */
#define HISSC_S2_SRC_CFG_ADDR                         ((PAGE_SoCCODEC) + (0x64))
/* S2接口左输入通道SRC升采样滤波器时能信号：
1'b1：时钟使能；
1'b0：bypass */
#define    HISSC_S2_IL_SRC_UP_EN_BIT_START         (0)
#define    HISSC_S2_IL_SRC_UP_EN_BIT_END           (0)
/* S2接口左输入通道SRC降采样滤波器时能信号：
1'b1：时钟使能；
1'b0：bypass */
#define    HISSC_S2_IL_SRC_DOWN_EN_BIT_START       (1)
#define    HISSC_S2_IL_SRC_DOWN_EN_BIT_END         (1)
/* S2接口左输入通道SRC升采样滤波器时能信号：
1'b1：时钟使能；
1'b0：bypass */
#define    HISSC_S2_IR_SRC_UP_EN_BIT_START         (2)
#define    HISSC_S2_IR_SRC_UP_EN_BIT_END           (2)
/* S2接口左输入通道SRC降采样滤波器时能信号：
1'b1：时钟使能；
1'b0：bypass */
#define    HISSC_S2_IR_SRC_DOWN_EN_BIT_START       (3)
#define    HISSC_S2_IR_SRC_DOWN_EN_BIT_END         (3)
/* S2 I2S接口左输入通道SRC升采样模块READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中 */
#define    HISSC_S2_IL_SRC_UP_SRC_RDY_BIT_START    (4)
#define    HISSC_S2_IL_SRC_UP_SRC_RDY_BIT_END      (4)
/* S2 I2S接口左输入通道SRC降采样模块READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中 */
#define    HISSC_S2_IL_SRC_DOWN_SRC_RDY_BIT_START  (5)
#define    HISSC_S2_IL_SRC_DOWN_SRC_RDY_BIT_END    (5)
/* S2 I2S接口右输入通道SRC升采样模块READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中 */
#define    HISSC_S2_IR_SRC_UP_SRC_RDY_BIT_START    (6)
#define    HISSC_S2_IR_SRC_UP_SRC_RDY_BIT_END      (6)
/* S2 I2S接口右输入通道SRC降采样模块READY信号：
1'b1:SRC RAM初始化完成
1'b0:SRC RAM初始化进行中 */
#define    HISSC_S2_IR_SRC_DOWN_SRC_RDY_BIT_START  (7)
#define    HISSC_S2_IR_SRC_DOWN_SRC_RDY_BIT_END    (7)


/* 寄存器说明：memory配置信号 */
#define HISSC_MEM_CFG_ADDR                            ((PAGE_SoCCODEC) + (0x68))
/* SRC中单口memory控制信号 */
#define    HISSC_MEM_CTRL_S_BIT_START      (0)
#define    HISSC_MEM_CTRL_S_BIT_END        (15)
/* AFIFO中双口memory控制信号 */
#define    HISSC_MEM_CTRL_D1W2R_BIT_START  (16)
#define    HISSC_MEM_CTRL_D1W2R_BIT_END    (31)


/* 寄存器说明：第三方modem的I2S */
#define HISSC_THIRDMD_PCM_PGA_CFG_ADDR                ((PAGE_SoCCODEC) + (0x6C))
/* S1接口模式选择：
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
其他：保留 */
#define    HISSC_S3_FUNC_MODE_BIT_START                      (0)
#define    HISSC_S3_FUNC_MODE_BIT_END                        (2)
/* S1接口Codec ADC/DAC数据格式选择。
0：表示二进制补码；
1：表示二进制码（binary offset）。 */
#define    HISSC_S3_CODEC_DATA_FORMAT_BIT_START              (3)
#define    HISSC_S3_CODEC_DATA_FORMAT_BIT_END                (3)
/* S1接口RX方向时钟选择：
1'b0:BCLK上升沿接收数据
1'b1:BCLK下降沿接收数据 */
#define    HISSC_S3_RX_CLK_SEL_BIT_START                     (4)
#define    HISSC_S3_RX_CLK_SEL_BIT_END                       (4)
/* S1接口TX方向时钟选择：
1'b0:BCLK上升沿打出数据
1'b1:BCLK下降沿打出数据 */
#define    HISSC_S3_TX_CLK_SEL_BIT_START                     (5)
#define    HISSC_S3_TX_CLK_SEL_BIT_END                       (5)
/* S1 I2S接口环回模式选择。
2'b00：正常工作模式；
2'b01：Sdin->Sdout。
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: 保留 */
#define    HISSC_S3_DIRECT_LOOP_BIT_START                    (6)
#define    HISSC_S3_DIRECT_LOOP_BIT_END                      (7)
/* S1接口位数控制。
00：16bit；
01：18bit；
10：20bit；
11：24bit。 */
#define    HISSC_S3_CODEC_IO_WORDLENGTH_BIT_START            (8)
#define    HISSC_S3_CODEC_IO_WORDLENGTH_BIT_END              (9)
/* S1接口声道配置：
1'b0:左声道在前
1'b1:右声道在前 */
#define    HISSC_S3_CHNNL_MODE_BIT_START                     (10)
#define    HISSC_S3_CHNNL_MODE_BIT_END                       (10)
/* S1接口帧同步信号左右声道选择：
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S3_LRCLK_MODE_BIT_START                     (11)
#define    HISSC_S3_LRCLK_MODE_BIT_END                       (11)
/* S1接口Master/Slave模式选择：
1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
1'b1:Slave模式 */
#define    HISSC_S3_MST_SLV_BIT_START                        (12)
#define    HISSC_S3_MST_SLV_BIT_END                          (12)
/* S1接口I2S模式下帧格式配置：
1'b0:I2S模式下64bit frame，PCM模式下32bit frame
1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
#define    HISSC_S3_FRAME_MODE_BIT_START                     (13)
#define    HISSC_S3_FRAME_MODE_BIT_END                       (13)
/* S1接口RX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S3_IF_RX_ENA_BIT_START                      (14)
#define    HISSC_S3_IF_RX_ENA_BIT_END                        (14)
/* S1接口TX方向使能：
1'b1:使能
1'b0:关闭 */
#define    HISSC_S3_IF_TX_ENA_BIT_START                      (15)
#define    HISSC_S3_IF_TX_ENA_BIT_END                        (15)
/* S1接口采样率配置
0：8KHz； 1：16KHz；
2：32KHz； 3：保留
4：48KHz； 5：96KHz；
6：192KHz；7：保留 */
#define    HISSC_FS_S3_BIT_START                             (16)
#define    HISSC_FS_S3_BIT_END                               (18)
/* 第三方modem下行通道 pga增益控制整数部分:
默认：0dB
增益范围:-72dB~+36dB。
即：
0010_0100:36dB
0010_0011:35dB
……
1011_1000：-72dB
步长为1dB,补码表示。
算法不支持配置增益范围外的值，配置范围外的值该模块行为不可预测，不建议配置。
可以通过将该寄存器配置为0x80来实现静音。 */
#define    HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_START  (20)
#define    HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_END    (27)
/* 第三方modem下行通道 pga输入增益小数位配置。
0：0.0dB；
1：0.5dB。 */
#define    HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_START     (28)
#define    HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_END       (28)
/* 第三方modem下行通道 pga mute使能：
1'b1: mute有效，输出0
1'b0: 关闭mute */
#define    HISSC_THIRDMD_DLINK_PGA_MUTE_BIT_START            (29)
#define    HISSC_THIRDMD_DLINK_PGA_MUTE_BIT_END              (29)
/* 第三方modem下行通道 pga过零检测低电平门限配置。
00：-60dB；
01：-72dB；
10：-90dB；
11：-120dB； */
#define    HISSC_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_START      (30)
#define    HISSC_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_END        (31)


/* 寄存器说明：第三方Modem下行通道AFIFO水线 */
#define HISSC_THIRD_MODEM_FIFO_TH_ADDR                ((PAGE_SoCCODEC) + (0x70))
/* Third Modem DLINK通道AFIFO将满阈值，fifo中有效数值个数高于该值时，FIFO almost full信号有效 */
#define    HISSC_THIRDMD_DLINK_FIFO_AFULL_TH_BIT_START    (0)
#define    HISSC_THIRDMD_DLINK_FIFO_AFULL_TH_BIT_END      (4)
/* Third Modem DLINK通道AFIFO将空阈值，fifo中有效数值个数低于该值时，FIFO almost empty信号有效 */
#define    HISSC_THIRDMD_DLINK_FIFO_AEMPTY_TH_BIT_START   (8)
#define    HISSC_THIRDMD_DLINK_FIFO_AEMPTY_TH_BIT_END     (12)
/* Third Modem UPLINK右通道AFIFO将满阈值，同上。 */
#define    HISSC_THIRDMD_UPLINK_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_THIRDMD_UPLINK_FIFO_AFULL_TH_BIT_END     (20)
/* Third Modem UPLINK右通道AFIFO将空阈值，同上。 */
#define    HISSC_THIRDMD_UPLINK_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_THIRDMD_UPLINK_FIFO_AEMPTY_TH_BIT_END    (28)


/* 寄存器说明：S3接口抗频偏模块TX方向计数器 */
#define HISSC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x74))
/* S3接口tx方向上溢计数器，读取清除。
有计数时，表明S3接口TX方向缓存中数据个数到达下水线，需要HiFi插入数据个数，意味着外部时钟快。 */
#define    HISSC_S3_TX_INC_CNT_BIT_START  (0)
#define    HISSC_S3_TX_INC_CNT_BIT_END    (7)


/* 寄存器说明：S3接口抗频偏模块TX方向计数器 */
#define HISSC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x78))
/* S3接口tx方向下溢计数器，读取清除。
有计数时，表明S3接口TX方向缓存中数据个数到达上水线，需要HiFi丢弃数据个数，意味着外部时钟慢。 */
#define    HISSC_S3_TX_DEC_CNT_BIT_START  (0)
#define    HISSC_S3_TX_DEC_CNT_BIT_END    (7)


/* 寄存器说明：S3接口抗频偏模块RX方向计数器 */
#define HISSC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x7C))
/* S3接口rx方向上溢计数器，读取清除。
有计数时，表明S3接口RX方向缓存中数据个数到达上水线，需要HiFi丢弃数据个数，意味着外部时钟快。 */
#define    HISSC_S3_RX_INC_CNT_BIT_START  (0)
#define    HISSC_S3_RX_INC_CNT_BIT_END    (7)


/* 寄存器说明：S3接口抗频偏模块RX方向计数器 */
#define HISSC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x80))
/* S3接口rx方向下溢计数器，读取清除。
有计数时，表明S3接口RX方向缓存中数据个数到达下水线，需要HiFi插入数据个数，意味着外部时钟慢。 */
#define    HISSC_S3_RX_DEC_CNT_BIT_START  (0)
#define    HISSC_S3_RX_DEC_CNT_BIT_END    (7)


/* 寄存器说明：抗频偏模块使能使能 */
#define HISSC_ANTI_FREQ_JITTER_EN_ADDR                ((PAGE_SoCCODEC) + (0x84))
/* S3接口TX方向ANTI_FREQ_JITTER模块使能 */
#define    HISSC_S3_TX_ANTI_FREQ_JITTER_EN_BIT_START  (0)
#define    HISSC_S3_TX_ANTI_FREQ_JITTER_EN_BIT_END    (0)
/* S3接口RX方向ANTI_FREQ_JITTER模块使能 */
#define    HISSC_S3_RX_ANTI_FREQ_JITTER_EN_BIT_START  (1)
#define    HISSC_S3_RX_ANTI_FREQ_JITTER_EN_BIT_END    (1)


/* 寄存器说明：12.288M时钟来源选择 */
#define HISSC_CLK_SEL_ADDR                            ((PAGE_SoCCODEC) + (0x88))
/* 外部12.288M时钟选择：
1'b1: 选择片外送入的，12.288M时钟
1'b0: 选择内部分频产生的12.288M时钟 */
#define    HISSC_EXTERNAL_12288K_SEL_BIT_START  (0)
#define    HISSC_EXTERNAL_12288K_SEL_BIT_END    (0)


/* 寄存器说明：第三方Modem下行通道 */
#define HISSC_THIRDMD_DLINK_CHANNEL_ADDR              ((PAGE_SoCCODEC) + (0xE8))
/*  */
#define    HISSC_THIRDMD_DLINK_WDATA_BIT_START  (0)
#define    HISSC_THIRDMD_DLINK_WDATA_BIT_END    (31)


/* 寄存器说明：第三方Modem上行通道 */
#define HISSC_THIRDMD_UPLINK_CHANNEL_ADDR             ((PAGE_SoCCODEC) + (0xEC))
/*  */
#define    HISSC_THIRDMD_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_THIRDMD_UPLINK_RDATA_BIT_END    (31)


/* 寄存器说明：VOICE下行通道 */
#define HISSC_VOICE_DLINK_CHANNEL_ADDR                ((PAGE_SoCCODEC) + (0xF0))
/*  */
#define    HISSC_VOICE_DLINK_WDATA_BIT_START  (0)
#define    HISSC_VOICE_DLINK_WDATA_BIT_END    (31)


/* 寄存器说明：音频下行通道 */
#define HISSC_STEREO_DLINK_CHANNEL_ADDR               ((PAGE_SoCCODEC) + (0xF4))
/* 左右声道交替进行操作 */
#define    HISSC_STEREO_DLINK_WDATA_BIT_START  (0)
#define    HISSC_STEREO_DLINK_WDATA_BIT_END    (31)


/* 寄存器说明：音频上行通道 */
#define HISSC_STEREO_UPLINK_CHANNEL_ADDR              ((PAGE_SoCCODEC) + (0xF8))
/* 左右声道交替进行操作 */
#define    HISSC_STEREO_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_STEREO_UPLINK_RDATA_BIT_END    (31)


/* 寄存器说明：VOICE上行通道 */
#define HISSC_VOICE_UPLINK_CHANNEL_ADDR               ((PAGE_SoCCODEC) + (0xFC))
/* 左右声道交替进行操作 */
#define    HISSC_VOICE_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_VOICE_UPLINK_RDATA_BIT_END    (31)




/****************************************************************************
                     (2/2) smartStar CODEC
 ****************************************************************************/
/* 寄存器说明：版本寄存器 */
#define HISSC_SMT_VERSION_ADDR                        ((PAGE_SmartStarCODEC) + (0x1B0))
/* 版本寄存器，表示版本为100 */
#define    HISSC_SMT_VERSION_BIT_START  (0)
#define    HISSC_SMT_VERSION_BIT_END    (7)


/* 寄存器说明：时钟使能配置寄存器 */
#define HISSC_SMT_CLK_EN_CFG_ADDR                     ((PAGE_SmartStarCODEC) + (0x1B1))
/* DACL时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SMT_DACL_EN_BIT_START   (0)
#define    HISSC_SMT_DACL_EN_BIT_END     (0)
/* DACR时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SMT_DACR_EN_BIT_START   (1)
#define    HISSC_SMT_DACR_EN_BIT_END     (1)
/* ADCL时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SMT_ADCL_EN_BIT_START   (2)
#define    HISSC_SMT_ADCL_EN_BIT_END     (2)
/* ADCR时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SMT_ADCR_EN_BIT_START   (3)
#define    HISSC_SMT_ADCR_EN_BIT_END     (3)
/* SIF时钟使能：
0：关闭时钟；
1：打开时钟。 */
#define    HISSC_SMT_SIF_EN_BIT_START    (4)
#define    HISSC_SMT_SIF_EN_BIT_END      (4)


/* 寄存器说明：数模接口时钟沿选择 */
#define HISSC_SMT_CLK_EDGE_CFG_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B2))
/* DACL时钟沿选择：
0：反沿；
1：与模拟部分分频时钟同沿。 */
#define    HISSC_SMT_DACL_CLK_EDGE_SEL_BIT_START  (0)
#define    HISSC_SMT_DACL_CLK_EDGE_SEL_BIT_END    (0)
/* DACR时钟沿选择：
0：反沿；
1：与模拟部分分频时钟同沿。 */
#define    HISSC_SMT_DACR_CLK_EDGE_SEL_BIT_START  (1)
#define    HISSC_SMT_DACR_CLK_EDGE_SEL_BIT_END    (1)
/* ADCL时钟沿选择：
0：反沿；
1：与模拟部分分频时钟同沿。 */
#define    HISSC_SMT_ADCL_CLK_EDGE_SEL_BIT_START  (2)
#define    HISSC_SMT_ADCL_CLK_EDGE_SEL_BIT_END    (2)
/* ADCR时钟沿选择：
0：反沿；
1：与模拟部分分频时钟同沿。 */
#define    HISSC_SMT_ADCR_CLK_EDGE_SEL_BIT_START  (3)
#define    HISSC_SMT_ADCR_CLK_EDGE_SEL_BIT_END    (3)


/* 寄存器说明：环回控制 */
#define HISSC_SMT_LOOPBACK_CFG_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B3))
/* DAC通道数据环回控制：
1'b0：数据来自于串行接口；
1'b1：DACL并行数据来自于模拟ADCL并行输入，DACR并行数据来自于模拟ADCR并行输入 */
#define    HISSC_SMT_DAC_LOOPBACK_BIT_START      (0)
#define    HISSC_SMT_DAC_LOOPBACK_BIT_END        (0)
/* ADC通道数据环回控制：
1'b0：adc并行数据来自于模拟并行输入；
1'b1：adc并行数据来自于dac的并行输出 */
#define    HISSC_SMT_ADC_LOOPBACK_BIT_START      (1)
#define    HISSC_SMT_ADC_LOOPBACK_BIT_END        (1)
/* SIF串行输出数据环回使能：
1：ADC串行输出环回到DAC串行输入
0：不环回 */
#define    HISSC_SMT_SIF_S2P_LOOPBACK_BIT_START  (2)
#define    HISSC_SMT_SIF_S2P_LOOPBACK_BIT_END    (2)


/* 寄存器说明：模拟中断原始状态寄存器 */
#define HISSC_SMT_ANA_IRQ_SIG_STAT_ADDR               ((PAGE_SmartStarCODEC) + (0x1B4))
/* 正常模式下，耳机按键中断1，检测上升和下降沿均有效；
1：耳机在位时，但是无耳机按键操作；
0：耳机在位时，有耳机按键操作； */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_BIT_START  (0)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_BIT_END    (0)
/* 正常模式下，耳机按键中断2，检测上升和下降沿均有效；
1：耳机在位时，但是无耳机按键操作；
0：耳机在位时，有耳机按键操作； */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_BIT_START  (1)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_BIT_END    (1)
/* ECO模式下，耳机按键中断，检测上升和下降沿均有效；
1：耳机在位时，但是无耳机按键操作；
0：耳机在位时，有耳机按键操作； */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_BIT_START   (2)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_BIT_END     (2)
/* 耳机插入检测中断，检测上升和下降沿均有效；
1：检测上升沿后，且读值为“1”时，表示有耳机插入；
0：检测下降沿后，且读值为“0”时，表示耳机拔出； */
#define    HISSC_SMT_HS_DET_IRQ_BIT_START       (3)
#define    HISSC_SMT_HS_DET_IRQ_BIT_END         (3)


/* 寄存器说明：ANA_IRQ_REG中断屏蔽寄存器 */
#define HISSC_SMT_ANA_IRQM_REG0_ADDR                  ((PAGE_SmartStarCODEC) + (0x1B5))
/* [7]:耳机拔出检测中断屏蔽位：
[6]:耳机插入检测中断屏蔽位：
[5]:ECO模式下按键按下中断屏蔽位：
[4]:ECO模式下按键释放中断屏蔽位：
[3]:耳机按键2按下中断屏蔽位：
[2]:耳机按键2释放中断屏蔽位：
[1]:耳机按键1按下中断屏蔽位：
[0]:耳机按键1释放中断屏蔽位：
1：屏蔽中断；
0：正常输出中断。 */
#define    HISSC_SMT_ANA_IRQ_MASK_BIT_START  (0)
#define    HISSC_SMT_ANA_IRQ_MASK_BIT_END    (7)


/* 寄存器说明：模拟中断寄存器0，写1清，读上报中断信息 */
#define HISSC_SMT_ANA_IRQ_REG0_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B6))
/* 耳机按键释放中断，检测高电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_POS_BIT_START  (0)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_POS_BIT_END    (0)
/* 耳机按键按下中断，检测低电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_NEG_BIT_START  (1)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_NEG_BIT_END    (1)
/* 耳机按键释放中断，检测高电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_POS_BIT_START  (2)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_POS_BIT_END    (2)
/* 耳机按键按下中断，检测低电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_NEG_BIT_START  (3)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_NEG_BIT_END    (3)
/* ECO模式下按键释放中断，检测高电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_POS_BIT_START   (4)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_POS_BIT_END     (4)
/* ECO模式下按键按下中断，检测低电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_NEG_BIT_START   (5)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_NEG_BIT_END     (5)
/* 耳机插入检测中断，检测高电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_DET_IRQ_POS_BIT_START       (6)
#define    HISSC_SMT_HS_DET_IRQ_POS_BIT_END         (6)
/* 耳机拔出检测中断，检测低电平有效；
1：写1时清除中断，查询时表示中断有效；
0：查询时表示中断无效。 */
#define    HISSC_SMT_HS_DET_IRQ_NEG_BIT_START       (7)
#define    HISSC_SMT_HS_DET_IRQ_NEG_BIT_END         (7)


/* 寄存器说明：hs_det_irq去抖配置 */
#define HISSC_SMT_DEB_CNT_HS_DET_CFG_ADDR             ((PAGE_SmartStarCODEC) + (0x1B7))
/* 去抖动周期计数器，以32k时钟计数
周期为1ms*计数值。
默认周期为20*1ms = 20ms
延时范围：0~32ms */
#define    HISSC_SMT_DEB_CNT_HS_DET_IRQ_BIT_START     (0)
#define    HISSC_SMT_DEB_CNT_HS_DET_IRQ_BIT_END       (4)
/* 旁路hs_det_irq中断去抖动功能。
0：去抖动功能有效；
1：去抖动功能无效。 */
#define    HISSC_SMT_BYPASS_DEB_HS_DET_IRQ_BIT_START  (5)
#define    HISSC_SMT_BYPASS_DEB_HS_DET_IRQ_BIT_END    (5)


/* 寄存器说明：hs_mic_irq去抖配置 */
#define HISSC_SMT_DEB_CNT_HS_MIC_CFG_ADDR             ((PAGE_SmartStarCODEC) + (0x1B8))
/* 去抖动周期计数器，以32k时钟计数
周期为1ms*计数值。
默认周期为10*1ms = 10ms
延时范围：0~32ms */
#define    HISSC_SMT_DEB_CNT_HS_MIC_IRQ_BIT_START     (0)
#define    HISSC_SMT_DEB_CNT_HS_MIC_IRQ_BIT_END       (4)
/* 旁路hs_mic_irq中断去抖动功能。
0：去抖动功能有效；
1：去抖动功能无效。 */
#define    HISSC_SMT_BYPASS_DEB_HS_MIC_IRQ_BIT_START  (5)
#define    HISSC_SMT_BYPASS_DEB_HS_MIC_IRQ_BIT_END    (5)


/* 寄存器说明：reserved */
#define HISSC_SMT_CODEC_DIG_RES02_ADDR                ((PAGE_SmartStarCODEC) + (0x1B9))


/* 寄存器说明：reserved */
#define HISSC_SMT_CODEC_DIG_RES03_ADDR                ((PAGE_SmartStarCODEC) + (0x1BA))


/* 寄存器说明：ADC通路PD信号 */
#define HISSC_SMT_CODEC_ANA_RW01_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BB))
/* LINEPGAR_PD控制信号(LINEPGAR_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_LINEPGAR_PD_BIT_START  (0)
#define    HISSC_SMT_LINEPGAR_PD_BIT_END    (0)
/* LINEPGAL_PD控制信号(LINEPGAL_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_LINEPGAL_PD_BIT_START  (1)
#define    HISSC_SMT_LINEPGAL_PD_BIT_END    (1)
/* AUXPGA_PD控制信号(AUXPGAR_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_AUXPGA_PD_BIT_START    (2)
#define    HISSC_SMT_AUXPGA_PD_BIT_END      (2)
/* MAINPGA_PD控制信号(MAINPGAR_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_MAINPGA_PD_BIT_START   (3)
#define    HISSC_SMT_MAINPGA_PD_BIT_END     (3)
/* ADCR PD控制信号(ADCR_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_ADCR_PD_BIT_START      (4)
#define    HISSC_SMT_ADCR_PD_BIT_END        (4)
/* ADCL PD控制信号(ADCL_PD):
0：正常工作；
1：PD */
#define    HISSC_SMT_ADCL_PD_BIT_START      (5)
#define    HISSC_SMT_ADCL_PD_BIT_END        (5)


/* 寄存器说明：MICBIAS,MBHD信号 */
#define HISSC_SMT_CODEC_ANA_RW02_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BC))
/* 整个芯片的Ibias的上电控制信号(IBIAS_PD)：
0：正常工作；
1：PD； */
#define    HISSC_SMT_IBIAS_PD_BIT_START      (0)
#define    HISSC_SMT_IBIAS_PD_BIT_END        (0)
/* MBHD buff上电控制信号(MBHD_BUFF_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_MBHD_BUFF_PD_BIT_START  (4)
#define    HISSC_SMT_MBHD_BUFF_PD_BIT_END    (4)
/* MBHD comp上电控制信号(MBHD_COMP_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_MBHD_COMP_PD_BIT_START  (5)
#define    HISSC_SMT_MBHD_COMP_PD_BIT_END    (5)
/* 耳机MICBIAS上电控制信号(HSMICB_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_HSMICB_PD_BIT_START     (6)
#define    HISSC_SMT_HSMICB_PD_BIT_END       (6)
/* MICBIAS1上电控制信号(MICB1_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_MICB1_PD_BIT_START      (7)
#define    HISSC_SMT_MICB1_PD_BIT_END        (7)


/* 寄存器说明：Headphone和MIXEROUT的PD信号 */
#define HISSC_SMT_CODEC_ANA_RW03_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BD))
/* HeadphoneR上电控制信号(HSR_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_HSR_PD_BIT_START         (1)
#define    HISSC_SMT_HSR_PD_BIT_END           (1)
/* HeadphoneL上电控制信号(HSL_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_HSL_PD_BIT_START         (2)
#define    HISSC_SMT_HSL_PD_BIT_END           (2)
/* MIXOUT_HSR上电控制信号(MIXOUT_HSR_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_MIXOUT_HSR_PD_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_HSR_PD_BIT_END    (4)
/* MIXOUT_HSL上电控制信号(MIXOUT_HSL_PD)：
0：正常工作；
1：PD */
#define    HISSC_SMT_MIXOUT_HSL_PD_BIT_START  (5)
#define    HISSC_SMT_MIXOUT_HSL_PD_BIT_END    (5)


/* 寄存器说明：VREF电阻选择信号 */
#define HISSC_SMT_CODEC_ANA_RW04_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BE))
/* VREF 电阻选择信号（VREFSEL<1:0>）;
00:无效；
01: 100kohm 分压电阻
10: 500kohm 分压电阻
11: 1kohm 分压电阻 */
#define    HISSC_SMT_VREFSEL_BIT_START   (0)
#define    HISSC_SMT_VREFSEL_BIT_END     (1)


/* 寄存器说明：LINEPGAL通路选择及增益控制信号 */
#define HISSC_SMT_CODEC_ANA_RW05_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BF))
/* LINEPGAL的通路MUTE信号(LINEPGAL_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_LINEPGAL_MUTE_BIT_START  (0)
#define    HISSC_SMT_LINEPGAL_MUTE_BIT_END    (0)
/* LINEPGAL的通路增益信号(LINEPGAL_GAIN<3:0>)；
增益范围:-14dB~16dB。
步长为2dB。
0000:-14dB；
0001:-12dB；
0010：-10dB；
……
0111:0dB；
……
1110:14dB；
1111:16dB； */
#define    HISSC_SMT_LINEPGAL_GAIN_BIT_START  (1)
#define    HISSC_SMT_LINEPGAL_GAIN_BIT_END    (4)
/* LINEPGAL的通路选择信号(LINEPGAL_SEL<1:0>)；
01:LINEINL和LINEINR组成差分输入；
10:LINEINL和VCM组成单端输入；
other：等效于MUTE; */
#define    HISSC_SMT_LINEPGAL_SEL_BIT_START   (5)
#define    HISSC_SMT_LINEPGAL_SEL_BIT_END     (6)


/* 寄存器说明：LINEPGAR通路选择及增益控制控制信号 */
#define HISSC_SMT_CODEC_ANA_RW06_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C0))
/* LINEPGAR的通路MUTE信号(LINEPGAR_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_LINEPGAR_MUTE_BIT_START  (0)
#define    HISSC_SMT_LINEPGAR_MUTE_BIT_END    (0)
/* LINEPGAR的通路增益信号(LINEPGAR_GAIN<3:0>)；
增益范围:-14dB~16dB。
步长为2dB。
0000:-14dB；
0001:-12dB；
0010：-10dB；
……
0111:0dB；
……
1110:14dB；
1111:16dB； */
#define    HISSC_SMT_LINEPGAR_GAIN_BIT_START  (1)
#define    HISSC_SMT_LINEPGAR_GAIN_BIT_END    (4)
/* LINEPGAR的通路选择信号(LINEPGAR_SEL<1:0>)；
01:LINEINR和LINEINL组成差分输入；
10:LINEINR和VCM组成单端输入；
other：等效于MUTE; */
#define    HISSC_SMT_LINEPGAR_SEL_BIT_START   (5)
#define    HISSC_SMT_LINEPGAR_SEL_BIT_END     (6)


/* 寄存器说明：AUXPGAR通路选择及增益控制控制信号 */
#define HISSC_SMT_CODEC_ANA_RW07_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C1))
/* AUXPGA的通路选择信号(AUXPGA_SEL<1:0>)；
00:PD有效
01:AUXMIC输入
10:选择VCM输入；
11：等效于MUTE； */
#define    HISSC_SMT_AUXPGA_SEL_BIT_START         (0)
#define    HISSC_SMT_AUXPGA_SEL_BIT_END           (1)
/* AUXPGA的通路MUTE信号(AUXPGA_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_AUXPGA_MUTE_BIT_START        (2)
#define    HISSC_SMT_AUXPGA_MUTE_BIT_END          (2)
/* AUXPGA的通路增益信号(AUXPGA_GAIN<2:0>)；
增益范围:0dB~14dB。
步长为2dB。
000: 0dB；
001: 2dB；
010: 4dB；
011: 6dB；
100: 8dB；
101: 10dB；
110: 12dB；
111: 14dB； */
#define    HISSC_SMT_AUXPGA_GAIN_BIT_START        (3)
#define    HISSC_SMT_AUXPGA_GAIN_BIT_END          (5)
/* AUXPGA的BOOST控制信号(AUXPGA_BOOST)；
0:正常增益；
1:26dB增益； */
#define    HISSC_SMT_AUXPGA_BOOST_BIT_START       (6)
#define    HISSC_SMT_AUXPGA_BOOST_BIT_END         (6)
/* MICPGA防死锁控制信号（MICPGA_UNLOCK_BPS）；
0:防死锁有效；
1:防死锁无效； */
#define    HISSC_SMT_MICPGA_UNLOCK_BPS_BIT_START  (7)
#define    HISSC_SMT_MICPGA_UNLOCK_BPS_BIT_END    (7)


/* 寄存器说明：MAINPGAR通路选择及增益控制控制信号 */
#define HISSC_SMT_CODEC_ANA_RW08_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C2))
/* MAINPGA的通路MUTE信号(MAINPGA_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_MAINPGA_MUTE_BIT_START   (0)
#define    HISSC_SMT_MAINPGA_MUTE_BIT_END     (0)
/* MAINPGA的通路增益信号(MAINPGA_GAIN<2:0>)；
增益范围:0dB~14dB。
步长为2dB。
000: 0dB；
001: 2dB；
010: 4dB；
011: 6dB；
100: 8dB；
101: 10dB；
110: 12dB；
111: 14dB； */
#define    HISSC_SMT_MAINPGA_GAIN_BIT_START   (1)
#define    HISSC_SMT_MAINPGA_GAIN_BIT_END     (3)
/*  */
#define    HISSC_SMT_MAINPGA_BOOST_BIT_START  (4)
#define    HISSC_SMT_MAINPGA_BOOST_BIT_END    (4)
/* MAINPGA的通路选择信号(MAINPGA_SEL)；
01：选择手机MIC输入；
10:选择耳机HP MIC输入；
others：等效于MUTE； */
#define    HISSC_SMT_MAINPGA_SEL_BIT_START    (5)
#define    HISSC_SMT_MAINPGA_SEL_BIT_END      (6)


/* 寄存器说明：ADCR_MIXIN通路选择信号 */
#define HISSC_SMT_CODEC_ANA_RW09_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C3))
/* ADCR_MIXIN的输入信号通路选择控制信号(ADCR_MIXIN<5:0>):
XXXXX1:AUXPGA的输出信号；
XXXX1X:MAINPGA的输出信号；
XXX1XX:LINEINR的输出信号；
XX1XXX:LINEINL的输出信号；
X1XXXX:DACR的输出信号；
1XXXXX:DACL的输出信号；
master:adcr_pd */
#define    HISSC_SMT_ADCR_MIXIN_BIT_START  (0)
#define    HISSC_SMT_ADCR_MIXIN_BIT_END    (5)


/* 寄存器说明：ADCL_MIXIN通路选择信号 */
#define HISSC_SMT_CODEC_ANA_RW10_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C4))
/* ADCL_MIXIN的输入信号通路选择控制信号(ADCL_MIXIN<5:0>):
XXXXX1:AUXPGA的输出信号；
XXXX1X:MAINPGA的输出信号；
XXX1XX:LINEINR的输出信号；
XX1XXX:LINEINL的输出信号；
X1XXXX:DACR的输出信号；
1XXXXX:DACL的输出信号；
master:adcl_pd */
#define    HISSC_SMT_ADCL_MIXIN_BIT_START  (0)
#define    HISSC_SMT_ADCL_MIXIN_BIT_END    (5)


/* 寄存器说明：ADCL时序控制信号 */
#define HISSC_SMT_CODEC_ANA_RW11_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C5))
/* ADCL通路DWA Baypass控制信号(ADCL_DWA_BPS):
0:打开DWA；
1:Baypass DWA功能； */
#define    HISSC_SMT_ADCL_DWA_BPS_BIT_START      (0)
#define    HISSC_SMT_ADCL_DWA_BPS_BIT_END        (0)
/* ADCL的FlashADC的参考电压选择信号(ADCL_FLSTN<1:0>):
00:参考电压为1.05倍；
01:参考电压为1倍；
10:参考电压为0.95倍；
11:参考电压为0.9倍； */
#define    HISSC_SMT_ADCL_FLSTN_BIT_START        (1)
#define    HISSC_SMT_ADCL_FLSTN_BIT_END          (2)
/* ADCL的反馈DAC的偏置选择信号(ADCL_DAC_BIAS<1:0>):
00:偏置电压为0.9倍；
01:偏置电压为0.95倍；
10:偏置电压为1倍；
11:偏置电压为1.1倍； */
#define    HISSC_SMT_ADCL_DAC_BIAS_BIT_START     (3)
#define    HISSC_SMT_ADCL_DAC_BIAS_BIT_END       (4)
/* ADCL_CLK_DELAY<0>:ADCL内部CLK时序(CLK_TIMING_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCL_CLK_DELAY_0_BIT_START  (5)
#define    HISSC_SMT_ADCL_CLK_DELAY_0_BIT_END    (5)
/* ADCL_CLK_DELAY<1>:ADCL内部CLK延时(CLK_DELAY_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCL_CLK_DELAY_1_BIT_START  (6)
#define    HISSC_SMT_ADCL_CLK_DELAY_1_BIT_END    (6)
/* ADCL_CLK_DELAY<2>:ADCL的输出数据的时(DOUT_TIMING_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCL_CLK_DELAY_2_BIT_START  (7)
#define    HISSC_SMT_ADCL_CLK_DELAY_2_BIT_END    (7)


/* 寄存器说明：ADCR时序控制信号 */
#define HISSC_SMT_CODEC_ANA_RW12_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C6))
/* ADCR通路DWA Baypass控制信号(ADCR_DWA_BPS):
0:打开DWA；
1:Baypass DWA功能； */
#define    HISSC_SMT_ADCR_DWA_BPS_BIT_START      (0)
#define    HISSC_SMT_ADCR_DWA_BPS_BIT_END        (0)
/* ADCR的FlashADC的参考电压选择信号(ADCR_FLSTN<1:0>):
00:参考电压为1.05倍；
01:参考电压为1倍；
10:参考电压为0.95倍；
11:参考电压为0.9倍； */
#define    HISSC_SMT_ADCR_FLSTN_BIT_START        (1)
#define    HISSC_SMT_ADCR_FLSTN_BIT_END          (2)
/* ADCR的反馈DAC的偏置选择信号(ADCR_DAC_BIAS<1:0>):
00:偏置电压为0.9倍；
01:偏置电压为0.95倍；
10:偏置电压为1倍；
11:偏置电压为1.1倍； */
#define    HISSC_SMT_ADCR_DAC_BIAS_BIT_START     (3)
#define    HISSC_SMT_ADCR_DAC_BIAS_BIT_END       (4)
/* ADCR_CLK_DELAY<0>:ADCR内部CLK时序(CLK_TIMING_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCR_CLK_DELAY_0_BIT_START  (5)
#define    HISSC_SMT_ADCR_CLK_DELAY_0_BIT_END    (5)
/* ADCR_CLK_DELAY<1>:ADCR内部CLK延时(CLK_DELAY_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCR_CLK_DELAY_1_BIT_START  (6)
#define    HISSC_SMT_ADCR_CLK_DELAY_1_BIT_END    (6)
/*
ADCR_CLK_DELAY<2>:ADCR的输出数据的时序(DOUT_TIMING_SEL)；
0: 默认延时
1: 增加延时 */
#define    HISSC_SMT_ADCR_CLK_DELAY_2_BIT_START  (7)
#define    HISSC_SMT_ADCR_CLK_DELAY_2_BIT_END    (7)


/* 寄存器说明：MIXOUT_HSL，MIXOUT_HSR通路选择信号 */
#define HISSC_SMT_CODEC_ANA_RW13_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C7))
/* MIXOUT_HSR的输入信号通路选择控制信号(MIXOUT_HSR<3:0>):
XXX1:LINEINR的输出信号；
XX1X:LINEINL的输出信号；
X1XX:DACR的输出信号；
1XXX:DACL的输出信号；
master:mixout_hsr_pd */
#define    HISSC_SMT_MIXOUT_HSR_BIT_START  (0)
#define    HISSC_SMT_MIXOUT_HSR_BIT_END    (3)
/* MIXOUT_HSL的输入信号通路选择控制信号(MIXOUT_HSL<3:0>):
XXX1:LINEINR的输出信号；
XX1X:LINEINL的输出信号；
X1XX:DACR的输出信号；
1XXX:DACL的输出信号；
master:mixout_hsl_pd */
#define    HISSC_SMT_MIXOUT_HSL_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_HSL_BIT_END    (7)


/* 寄存器说明：MIXOUT_EAR通路选择信号，增益选择信号 */
#define HISSC_SMT_CODEC_ANA_RW14_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C8))
/* MIXOUT_EAR的0dB,-6dB选择控制信号(CR_MIXF<3:0>):
XXX1:LINEINR支路0dB；XXX0:LINEINR支路-6dB
XX1X:LINEINL支路0dB；XX0X:LINEINL支路-6dB
X1XX:DACR支路0dB；X0XX:DACR支路-6dB
1XXX:DACL支路0dB；0XXX:DACL支路-6dB； */
#define    HISSC_SMT_CR_MIXF_BIT_START     (0)
#define    HISSC_SMT_CR_MIXF_BIT_END       (3)
/* MIXOUT_EAR的输入信号通路选择控制信号(MIXOUT_EAR<3:0>):
XXX1:LINEINR的输出信号；
XX1X:LINEINL的输出信号；
X1XX:DACR的输出信号；
1XXX:DACL的输出信号；
master:mixout_ear_pd */
#define    HISSC_SMT_MIXOUT_EAR_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_EAR_BIT_END    (7)


/* 寄存器说明：DACICELL电流控制信号，ChargePump死区时间控制信号 */
#define HISSC_SMT_CODEC_ANA_RW15_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C9))
/* Charge Pump三相时钟死区时间控制信号（CP_DTC_3<1:0>)；
00:10ns（默认）
01:20ns
10:30ns
11:50ns */
#define    HISSC_SMT_CP_DTC_3_BIT_START    (0)
#define    HISSC_SMT_CP_DTC_3_BIT_END      (1)
/* Charge Pump两相时钟死区时间控制信号（CP_DTC_2<1:0>)；
00:10ns（默认）
01:20ns
10:30ns
11:50ns */
#define    HISSC_SMT_CP_DTC_2_BIT_START    (2)
#define    HISSC_SMT_CP_DTC_2_BIT_END      (3)
/* DACR ICELLS的电流控制信号(DACR_ICTRL<1:0>):
00:电流变为0.9倍；
01:正常电流；
10:电流变为1.1倍；
11:电流变为1.2倍； */
#define    HISSC_SMT_DACR_ICTRL_BIT_START  (4)
#define    HISSC_SMT_DACR_ICTRL_BIT_END    (5)
/* DACL ICELLS的电流控制信号(DACL_ICTRL<1:0>):
00:电流变为0.9倍；
01:正常电流；
10:电流变为1.1倍；
11:电流变为1.2倍； */
#define    HISSC_SMT_DACL_ICTRL_BIT_START  (6)
#define    HISSC_SMT_DACL_ICTRL_BIT_END    (7)


/* 寄存器说明：Headphonesoft使能信号，ChargePump控制信号 */
#define HISSC_SMT_CODEC_ANA_RW16_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CA))
/* Change Pump 导通开关驱动能力选择（CP_DR_CTRL<1:0>);
00: 最小驱动（默认）
01: 较小驱动
10: 较大驱动
11:最大驱动 */
#define    HISSC_SMT_CP_DR_CTRL_BIT_START  (0)
#define    HISSC_SMT_CP_DR_CTRL_BIT_END    (1)
/* CLASSG模式下输入幅度的参考选择信号(CLASSG_REF<1:0>):
00: VREF为200mV；
01: VREF为400mV；
10: VREF为300mV；
11: VREF为500mV； */
#define    HISSC_SMT_CLASSG_REF_BIT_START  (2)
#define    HISSC_SMT_CLASSG_REF_BIT_END    (3)
/* Charge Pump的输出电压的模式控制信号(CP_MODE<1:0>):
00:固定输出正负1.8V的电源；
01:固定输出正负0.9V的电源；
10:CLASSG模式，输出电压随输入信号可调；
11:CLASSG模式，输出电压随输入信号可调； */
#define    HISSC_SMT_CP_MODE_BIT_START     (4)
#define    HISSC_SMT_CP_MODE_BIT_END       (5)
/* Headphone正常模式，CLASSG模式偏置管调整信号（EN_CP_MODE）:
0: 偏置管标准模式；
1: 偏置管叠加模式； */
#define    HISSC_SMT_EN_CP_MODE_BIT_START  (6)
#define    HISSC_SMT_EN_CP_MODE_BIT_END    (6)
/* Headphone soft使能控制信号(HP_SOFT_EN):
0: 正常使能；
1: soft使能； */
#define    HISSC_SMT_HP_SOFT_EN_BIT_START  (7)
#define    HISSC_SMT_HP_SOFT_EN_BIT_END    (7)


/* 寄存器说明：HeadphoneL增益控制信号 */
#define HISSC_SMT_CODEC_ANA_RW17_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CB))
/* HeadphoneL的通路最小增益选择信号(HSL_MIN_GAIN)；
0:最小增益(-26dB)无效；
1：最小增益(-26dB)有效; */
#define    HISSC_SMT_HSL_MIN_GAIN_BIT_START  (0)
#define    HISSC_SMT_HSL_MIN_GAIN_BIT_END    (0)
/* HeadphoneL的通路增益信号(HSL_GAIN<3:0>)；
增益范围:-20dB~-0dB。
步长为1.5dB。
0000:-20dB；
0001:-18dB；
0010：-16.5dB；
0011: -15dB;
0100:-13.5dB;
0101:-12dB;
0110:-10.5dB;
0111:-9.5dB;
1000:-8.5dB;
1001:-7.5dB;
1010:-6.5dB;
1011:-5.5dB;
1100:-4.5dB;
1101:-3dB;
1110:-1.5dB;
1111:0dB; */
#define    HISSC_SMT_HSL_GAIN_BIT_START      (1)
#define    HISSC_SMT_HSL_GAIN_BIT_END        (4)
/* HeadphoneL的通路MUTE信号(HSL_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_HSL_MUTE_BIT_START      (5)
#define    HISSC_SMT_HSL_MUTE_BIT_END        (5)
/* HeadphoneL的POP小环路MUTE信号(HS_LIT_LP_L)；
0：小环路MUTE不使能 ，此时小环路的mute由hsl_mute控制；
1：小环路MUTE使能; */
#define    HISSC_SMT_HS_LIT_LP_L_BIT_START   (6)
#define    HISSC_SMT_HS_LIT_LP_L_BIT_END     (6)


/* 寄存器说明：HeadphonR增益控制信号 */
#define HISSC_SMT_CODEC_ANA_RW18_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CC))
/* HeadphoneR的通路最小增益选择信号(HSR_MIN_GAIN)；
0:最小增益(-26dB)无效；
1：最小增益(-26dB)有效; */
#define    HISSC_SMT_HSR_MIN_GAIN_BIT_START  (0)
#define    HISSC_SMT_HSR_MIN_GAIN_BIT_END    (0)
/* HeadphoneR的通路增益信号(HSR_GAIN<3:0>)；
增益范围:-20dB~-0dB。
步长为1.5dB。
0000:-20dB；
0001:-18dB；
0010：-16.5dB；
0011: -15dB;
0100:-13.5dB;
0101:-12dB;
0110:-10.5dB;
0111:-9.5dB;
1000:-8.5dB;
1001:-7.5dB;
1010:-6.5dB;
1011:-5.5dB;
1100:-4.5dB;
1101:-3dB;
1110:-1.5dB;
1111:0dB; */
#define    HISSC_SMT_HSR_GAIN_BIT_START      (1)
#define    HISSC_SMT_HSR_GAIN_BIT_END        (4)
/* HeadphoneR的通路MUTE信号(HSR_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_HSR_MUTE_BIT_START      (5)
#define    HISSC_SMT_HSR_MUTE_BIT_END        (5)
/* HeadphoneR的POP小环路MUTE信号(HS_LIT_LP_R)；
0：小环路MUTE不使能 ，此时小环路的mute由hsl_mute控制；
1：小环路MUTE使能; */
#define    HISSC_SMT_HS_LIT_LP_R_BIT_START   (6)
#define    HISSC_SMT_HS_LIT_LP_R_BIT_END     (6)


/* 寄存器说明：Earphone增益控制信号 */
#define HISSC_SMT_CODEC_ANA_RW19_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CD))
/* EAR的共模控制信号(EAR_CM_CTRL):
0:输出经过500欧姆电阻到VCM；
1:输出经过30K欧姆电阻到VCM； */
#define    HISSC_SMT_EAR_CM_CTRL_BIT_START  (0)
#define    HISSC_SMT_EAR_CM_CTRL_BIT_END    (0)
/* EAR的通路增益信号(EAR_GAIN<5:0>)；
增益范围:-20dB~-6dB。
步长为2dB。
0000:-20dB；
0001:-18dB；
0010：-16dB；
0011: -14dB;
0100:-12dB;
0101:-10dB;
0110:-8dB;
0111:-6dB;
1000:-4dB;
1001:-2dB;
1010:-0dB;
1011:2dB;
1100:4dB;
1101:6dB;
orther: mute */
#define    HISSC_SMT_EAR_GAIN_BIT_START     (1)
#define    HISSC_SMT_EAR_GAIN_BIT_END       (4)
/* EAR的通路MUTE信号(EAR_MUTE)；
0:通路正常工作；
1：通路MUTE; */
#define    HISSC_SMT_EAR_MUTE_BIT_START     (5)
#define    HISSC_SMT_EAR_MUTE_BIT_END       (5)


/* 寄存器说明：POP音延时控制信号，ramp产生电路控制信号 */
#define HISSC_SMT_CODEC_ANA_RW20_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CE))
/* ramp产生电路,输入clk选择(POP_RAMP_CT<2:0>：
000：48k
001：48k/2
010：48k/4
011：48k/8
1*0：48k/16
1*1：48k/32 */
#define    HISSC_SMT_POP_RAMP_CT_2_0_BIT_START  (0)
#define    HISSC_SMT_POP_RAMP_CT_2_0_BIT_END    (2)
/* ramp产生电路,脉宽控制(POP_RAMP_CT<3>)：
0：normal；（正常使用）
1：mormal*1.5 */
#define    HISSC_SMT_POP_RAMP_CT_3_BIT_START    (3)
#define    HISSC_SMT_POP_RAMP_CT_3_BIT_END      (3)
/* ramp产生电路,cap选择(POP_RAMP_CT<4>)：
0：normal；（正常使用）
1：mormal*1.5 */
#define    HISSC_SMT_POP_RAMP_CT_4_BIT_START    (4)
#define    HISSC_SMT_POP_RAMP_CT_4_BIT_END      (4)
/* POP音上电延时控制(CLK_DL)：(clk_sel=0，括号中为clk_sel=1)

000：7.98m (15.96m )
001：13.34m (26.68m)
010：18.68m (37.36m)
011：23.98m (47.96m)
100：29.28m (58.56m)
101：34.58m (69.16m)
110：39.88m (79.96m)
111：45.18m (90.36m) */
#define    HISSC_SMT_CLK_DL_BIT_START           (5)
#define    HISSC_SMT_CLK_DL_BIT_END             (7)


/* 寄存器说明：防POP电路控制信号 */
#define HISSC_SMT_CODEC_ANA_RW21_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CF))
/* RST HP右通路 POP音控制模块(RST_N_R)：
0：RST 有效
1：Normal； */
#define    HISSC_SMT_RST_N_R_BIT_START   (0)
#define    HISSC_SMT_RST_N_R_BIT_END     (0)
/* RST HP左通路 POP音控制模块(RST_N_L)：
0：RST 有效
1：Normal； */
#define    HISSC_SMT_RST_N_L_BIT_START   (1)
#define    HISSC_SMT_RST_N_L_BIT_END     (1)
/* POP音控制模块byass选项(POP_DIS)：
0：enable POP音控制电路；
1：bypass POP音控制电路； */
#define    HISSC_SMT_POP_DIS_BIT_START   (2)
#define    HISSC_SMT_POP_DIS_BIT_END     (2)
/* POP音延时控制电路,clk选择(CLK_SEL)：（与1E7<7:5>配合使用）
0:188Hz；
1:94Hz； */
#define    HISSC_SMT_CLK_SEL_BIT_START   (3)
#define    HISSC_SMT_CLK_SEL_BIT_END     (3)
/* HP PD信号delay 控制(PDD_EN)：
0：PD信号直接输出到HP模块；
1：PD信号经过delay输出到HP模块；（正常模式） */
#define    HISSC_SMT_PDD_EN_BIT_START    (4)
#define    HISSC_SMT_PDD_EN_BIT_END      (4)

#define    HISSC_SMT_POP_NEW_BYPASS_BIT_START    (5)
#define    HISSC_SMT_POP_NEW_BYPASS_BIT_END      (5)

/* 寄存器说明：HSMICBIAS，MICBIAS1输出偏置电压控制信号 */
#define HISSC_SMT_CODEC_ANA_RW22_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D0))
/* MICBIAS1输出偏置电压控制信号(MICB1_ADJ<2:0>):
000: 2.1V；
001: 2.2V；
010: 2.3V；
011: 2.4V；
100: 2.5V；
101: 2.6V；
110: 2.7V；
111: 2.8V； */
#define    HISSC_SMT_MICB1_ADJ_BIT_START   (0)
#define    HISSC_SMT_MICB1_ADJ_BIT_END     (2)
/* HSMICBIAS输出偏置电压控制信号(HSMICB_ADJ<2:0>):
000: 2.1V；
001: 2.2V；
010: 2.3V；
011: 2.4V；
100: 2.5V；
101: 2.6V；
110: 2.7V；
111: 2.8V； */
#define    HISSC_SMT_HSMICB_ADJ_BIT_START  (3)
#define    HISSC_SMT_HSMICB_ADJ_BIT_END    (5)


/* 寄存器说明：HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1放电使能信号，MBHD使能信号 */
#define HISSC_SMT_CODEC_ANA_RW23_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D1))
/* ECO模式下，MBHD使能信号(MBHD_ECO_EN):
0:不使能；
1:使能； */
#define    HISSC_SMT_MBHD_ECO_EN_BIT_START   (0)
#define    HISSC_SMT_MBHD_ECO_EN_BIT_END     (0)
/* MICBIAS1放电使能信号(MICB1_DSCHG):
0:不使能；
1:使能； */
#define    HISSC_SMT_MICB1_DSCHG_BIT_START   (1)
#define    HISSC_SMT_MICB1_DSCHG_BIT_END     (1)
/* HSMICBIAS放电使能信号(HSMICB_DSCHG):
0:不使能；
1:使能； */
#define    HISSC_SMT_HSMICB_DSCHG_BIT_START  (2)
#define    HISSC_SMT_HSMICB_DSCHG_BIT_END    (2)
/* HSD EN 控制(HSD_CTRL<0>)：
0: HS 模块不使能；
1：HS 模块使能；（正常模式） */
#define    HISSC_SMT_HSD_CTRL_0_BIT_START    (3)
#define    HISSC_SMT_HSD_CTRL_0_BIT_END      (3)
/* HSD INV 控制(HSD_CTRL<1>)：
0: HS 输出反向；（正常模式）
1：HS 输出不反向； */
#define    HISSC_SMT_HSD_CTRL_1_BIT_START    (4)
#define    HISSC_SMT_HSD_CTRL_1_BIT_END      (4)
/* HSD POLLDOWN 控制（HSD_CTRL<2>)：
0: Headset 模块正常工作；（正常模式）
1：HSD 输入下拉； */
#define    HISSC_SMT_HSD_CTRL_2_BIT_START    (5)
#define    HISSC_SMT_HSD_CTRL_2_BIT_END      (5)


/* 寄存器说明：MBHD_VREF_CTRL<7:0> */
#define HISSC_SMT_CODEC_ANA_RW24_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D2))
/* Normal模式下，COMPL比较器电压阈值，档位分配(mbhd_vref_ctrl<1:0>：
00: 600mV
01: 700mV
10: 800mV
11: 900mV */
#define    HISSC_SMT_MBHD_VREF_CTRL_1_0_BIT_START  (0)
#define    HISSC_SMT_MBHD_VREF_CTRL_1_0_BIT_END    (1)
/* Normal模式下，COMPH比较器电压阈值，档位分配(mbhd_vref_ctrl<3:2>)：
00:80%*Vmicbias;
01:85%*Vmicbias;
10:90%Vmicbias;
11:95%*Vmicbias */
#define    HISSC_SMT_MBHD_VREF_CTRL_3_2_BIT_START  (2)
#define    HISSC_SMT_MBHD_VREF_CTRL_3_2_BIT_END    (3)
/* ECO模式下，ECO_COMP比较器电压阈值，档位分配(mbhd_vref_ctrl<6:4>)：
000：100mV
001：125mV
010: 150mV
011: 175mV
100: 200mV
101: 225mV
110: 250mV
111：275mV */
#define    HISSC_SMT_MBHD_VREF_CTRL_6_4_BIT_START  (4)
#define    HISSC_SMT_MBHD_VREF_CTRL_6_4_BIT_END    (6)
/* 按键检测模块比较器分压电阻PD信号(mbhd_vref_pd)：
0：VREF及比较器正常工作；
1：VREF及比较器PD；（在无耳机在位状态下，开启PD=1） */
#define    HISSC_SMT_MBHD_VREF_PD_BIT_START        (7)
#define    HISSC_SMT_MBHD_VREF_PD_BIT_END          (7)


/* 寄存器说明：CP_CLK_CTRL<7:0> */
#define HISSC_SMT_CODEC_ANA_RW25_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D3))
/* ChargePump输出电源域切换延时控制信号(CP_DET_SEL<1:0>):
00: 375Hz；
01: 187.5Hz；
10: 94Hz；
11: 47Hz； */
#define    HISSC_SMT_CP_DET_SEL_BIT_START     (0)
#define    HISSC_SMT_CP_DET_SEL_BIT_END       (1)
/* ChargePump输出电源域切换延时控制信号PD（CP_DET_CLK_PD）:
0：正常输出时钟；
1：PD */
#define    HISSC_SMT_CP_DET_CLK_PD_BIT_START  (2)
#define    HISSC_SMT_CP_DET_CLK_PD_BIT_END    (2)
/* ChargePump开关时钟控制信号（CP_CLK_PD）:
0：正常输出时钟；
1：PD */
#define    HISSC_SMT_CP_CLK_PD_BIT_START      (3)
#define    HISSC_SMT_CP_CLK_PD_BIT_END        (3)
/* ChargePump开关频率选择信号(CP_SEL<2:0>):
000: 6.144MHz；
001: 3.072MHz；
010: 1.536MHz；
011: 768KHz；
100: 384KHz；
101: 192KHz；
110: 96KHz；
111: 48KHz； */
#define    HISSC_SMT_CP_SEL_BIT_START         (4)
#define    HISSC_SMT_CP_SEL_BIT_END           (6)
/* Headphone 系统时钟PD信号（HS_SYS_CLK_PD）
0：正常输出时钟；
1：PD */
#define    HISSC_SMT_HS_SYS_CLK_PD_BIT_START  (7)
#define    HISSC_SMT_HS_SYS_CLK_PD_BIT_END    (7)


/* 寄存器说明：ADC，DAC时钟沿选择信号，ADC，DACchopper时钟选择信号 */
#define HISSC_SMT_CODEC_ANA_RW26_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D4))
/* DAC的chopper时钟选择信号(DAC_CHOP_CLK_SEL<1:0>):
00: 3MHz；
01: 1.5MHz；
10: 750KHz；
11: 375KHz； */
#define    HISSC_SMT_DAC_CHOP_CLK_SEL_BIT_START    (0)
#define    HISSC_SMT_DAC_CHOP_CLK_SEL_BIT_END      (1)
/* ADC的chopper时钟选择信号(ADC_CHOP_CLK_SEL<1:0>):
00: 384KHz；
01: 192KHz；
10: 96KHz；
11: 48KHz； */
#define    HISSC_SMT_ADC_CHOP_CLK_SEL_BIT_START    (2)
#define    HISSC_SMT_ADC_CHOP_CLK_SEL_BIT_END      (3)
/* DAC时钟相位选择信号(DAC_CLK_SYS_EDG_0):
0:DAC时钟选择二分频后同相时钟
1:DAC时钟选择二分频后反相时钟 */
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_0_BIT_START  (4)
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_0_BIT_END    (4)
/* DAC时钟沿选择信号(DAC_CLK_SYS_EDG_1):
0:DAC时钟沿同输入12.288MHz时钟沿反沿；
1:DAC时钟沿同输入12.288MHz时钟沿同沿； */
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_1_BIT_START  (5)
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_1_BIT_END    (5)
/* ADC时钟相位选择信号(ADC_CLK_SYS_EDG_0):
0:ADC时钟选择二分频后同相时钟
1:ADC时钟选择二分频后反相时钟 */
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_0_BIT_START  (6)
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_0_BIT_END    (6)
/* ADC时钟沿选择信号(ADC_CLK_SYS_EDG_1):
0:ADC时钟沿同输入12.288MHz时钟沿反沿；
1:ADC时钟沿同输入12.288MHz时钟沿同沿； */
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_1_BIT_START  (7)
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_1_BIT_END    (7)


/* 寄存器说明：RX，ADC_SDM,LINEIN,MICPGA,CTCM，chopperbaypass信号 */
#define HISSC_SMT_CODEC_ANA_RW27_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D5))
/* CTCM Chopper Baypass控制信号(CTCM_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_CTCM_CHOP_BPS_BIT_START     (0)
#define    HISSC_SMT_CTCM_CHOP_BPS_BIT_END       (0)
/* MICPGA Chopper Baypass控制信号(MICPGA_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_MICPGA_CHOP_BPS_BIT_START   (1)
#define    HISSC_SMT_MICPGA_CHOP_BPS_BIT_END     (1)
/* LINEIN Chopper Baypass控制信号(LINEIN_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_LINEIN_CHOP_BPS_BIT_START   (2)
#define    HISSC_SMT_LINEIN_CHOP_BPS_BIT_END     (2)
/* ADC_SDM Chopper Baypass控制信号(ADC_SDM_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_ADC_SDM_CHOP_BPS_BIT_START  (3)
#define    HISSC_SMT_ADC_SDM_CHOP_BPS_BIT_END    (3)
/* RX Chopper Baypass控制信号(RX_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_RX_CHOP_BPS_BIT_START       (4)
#define    HISSC_SMT_RX_CHOP_BPS_BIT_END         (4)


/* 寄存器说明：TX，DAC，MIXER_EAR,MIXER_HP，chopperbaypass信号 */
#define HISSC_SMT_CODEC_ANA_RW28_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D6))
/* MIXER FOR Headphone Chopper Baypass控制信号(HS_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_HS_CHOP_BPS_BIT_START       (0)
#define    HISSC_SMT_HS_CHOP_BPS_BIT_END         (0)
/* MIXER FOR Earphone and Classd Chopper Baypass控制信号(EAR_CLD_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_EAR_CLD_CHOP_BPS_BIT_START  (1)
#define    HISSC_SMT_EAR_CLD_CHOP_BPS_BIT_END    (1)
/* DAC Chopper Baypass控制信号(DAC_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_DAC_CHOP_BPS_BIT_START      (2)
#define    HISSC_SMT_DAC_CHOP_BPS_BIT_END        (2)
/* TX Chopper Baypass控制信号(TX_CHOP_BPS):
0:打开Chopper功能；
1:Baypass Chopper功能； */
#define    HISSC_SMT_TX_CHOP_BPS_BIT_START       (3)
#define    HISSC_SMT_TX_CHOP_BPS_BIT_END         (3)


/* 寄存器说明：CODEC_IBIAS_ADJ1（HeadphoneMIXER_HP电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW29_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D7))
/* MIXER_HP的电流控制信号:
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_MIXER_HP_BIT_START  (0)
#define    HISSC_SMT_IB05_MIXER_HP_BIT_END    (2)
/* Headphone_amp的电流控制信号:
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_HP_BIT_START        (3)
#define    HISSC_SMT_IB05_HP_BIT_END          (5)


/* 寄存器说明：CODEC_IBIAS_ADJ2（DAC，ADC_OPA1电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW30_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D8))
/* IB05_ADC_OPA1的电流控制信号(IB05_ADC_OPA1):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_ADC_OPA1_BIT_START  (0)
#define    HISSC_SMT_IB05_ADC_OPA1_BIT_END    (2)
/* DAC的电流控制信号(IB05_DAC):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_DAC_BIT_START       (3)
#define    HISSC_SMT_IB05_DAC_BIT_END         (5)


/* 寄存器说明：CODEC_IBIAS_ADJ3（ADC_OPA2，ADC_COMP电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW31_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D9))
/* IB05_ADC_COMP的电流控制信号(IB05_ADC_COMP):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_ADC_COMP_BIT_START  (0)
#define    HISSC_SMT_IB05_ADC_COMP_BIT_END    (2)
/* IB05_ADC_OPA2的电流控制信号(IB05_ADC_OPA2):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_ADC_OPA2_BIT_START  (3)
#define    HISSC_SMT_IB05_ADC_OPA2_BIT_END    (5)


/* 寄存器说明：CODEC_IBIAS_ADJ4（LINEIN，MICBIAS电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW32_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DA))
/* IB05_MICBIAS的电流控制信号(IB05_MICBIAS):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_MICBIAS_BIT_START     (0)
#define    HISSC_SMT_IB05_MICBIAS_BIT_END       (2)
/* IB05_ADC_LINEIN的电流控制信号(IB05_ADC_LINEIN):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_ADC_LINEIN_BIT_START  (3)
#define    HISSC_SMT_IB05_ADC_LINEIN_BIT_END    (5)


/* 寄存器说明：CODEC_IBIAS_ADJ5（reserved，AUXMIC电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW33_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DB))
/* IB05_AUXMIC的电流控制信号(IB05_AUXMIC):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_AUXMIC_BIT_START  (0)
#define    HISSC_SMT_IB05_AUXMIC_BIT_END    (2)
/* IB05_CTCM的电流控制信号(IB05_CTCM):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_REV_BIT_START     (3)
#define    HISSC_SMT_IB05_REV_BIT_END       (5)


/* 寄存器说明：CODEC_IBIAS_ADJ6（MAINMIC，MIXER_EAR电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW34_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DC))
/* IB05_MIXER_EAR的电流控制信号(IB05_MIXER_EAR):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_MIXER_EAR_BIT_START  (0)
#define    HISSC_SMT_IB05_MIXER_EAR_BIT_END    (2)
/* IB05_MAINMIC的电流控制信号(IB05_MAINMIC):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_MAINMIC_BIT_START    (3)
#define    HISSC_SMT_IB05_MAINMIC_BIT_END      (5)


/* 寄存器说明：CODEC_IBIAS_ADJ7（EAR，CODEC全局电流控制信号） */
#define HISSC_SMT_CODEC_ANA_RW35_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DD))
/* CODEC的全局电流控制信号(CODEC_IBIAS_ADJ):
0:5uA；
1:7.5uA； */
#define    HISSC_SMT_CODEC_BIAS_ADJ_BIT_START  (0)
#define    HISSC_SMT_CODEC_BIAS_ADJ_BIT_END    (0)
/* IB05_EAR的电流控制信号(IB05_EAR):
000: 2.5uA；
001: 3uA；
010: 3.5uA；
011: 4uA；
100: 4.5uA；
101: 5uA；
110: 7uA；
111: 9uA； */
#define    HISSC_SMT_IB05_EAR_BIT_START        (1)
#define    HISSC_SMT_IB05_EAR_BIT_END          (3)


/* 寄存器说明：ADC_DAC模拟环回控制信号 */
#define HISSC_SMT_CODEC_ANA_RW36_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DE))
/* CODEC模拟ADC_DAC环回控制信号(ANALOG_LOOP):
0:不环回；
1:环回；(ADCL_DACL,ADCR_DACR) */
#define    HISSC_SMT_ANALOG_LOOP_BIT_START  (0)
#define    HISSC_SMT_ANALOG_LOOP_BIT_END    (0)

/* 寄存器说明：HP_BIAS_PD 、CP_PD、CP_DET_PD控制信号 */
#define HISSC_SMT_CODEC_ANA_RW37_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DF))
/* ChargePump Detect上电控制信号(CP_DET_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_CP_DET_PU_BIT_START   (0)
#define    HISSC_SMT_CP_DET_PU_BIT_END     (0)
/* ChargePump上电控制信号(CP_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_CP_PU_BIT_START       (1)
#define    HISSC_SMT_CP_PU_BIT_END         (1)
/* Headphone ibias上电控制信号（HP_BIAS_PD）
0：PD；
1：正常工作; */
#define    HISSC_SMT_HP_BIAS_PU_BIT_START  (2)
#define    HISSC_SMT_HP_BIAS_PU_BIT_END    (2)

/* 寄存器说明：DACL_PD、DACR_PD */
#define HISSC_SMT_CODEC_ANA_RW38_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E0))
/* DACR上电控制信号(DACR_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_DACR_PU_BIT_START   (0)
#define    HISSC_SMT_DACR_PU_BIT_END     (0)
/* DACL上电控制信号(DACL_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_DACL_PU_BIT_START   (1)
#define    HISSC_SMT_DACL_PU_BIT_END     (1)


/* 寄存器说明：MIXOUT_EAR_PD、EAR_PD */
#define HISSC_SMT_CODEC_ANA_RW39_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E1))
/* EAR上电控制信号(EAR_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_EAR_PU_BIT_START         (0)
#define    HISSC_SMT_EAR_PU_BIT_END           (0)
/* MIXOUT_EAR上电控制信号(MIXOUT_EAR_PD)：
0：PD；
1：正常工作; */
#define    HISSC_SMT_MIXOUT_EAR_PU_BIT_START  (1)
#define    HISSC_SMT_MIXOUT_EAR_PU_BIT_END    (1)

/* 寄存器说明：CODEC_ANA_RW40 */
#define HISSC_SMT_CODEC_ANA_RW40_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E2))
/*  */
#define    HISSC_SMT_CODEC_ANA_REG40_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_REG40_BIT_END    (7)


/* 寄存器说明：CODEC_ANA_RO01 */
#define HISSC_SMT_CODEC_ANA_RO01_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E3))
/*  */
#define    HISSC_SMT_CODEC_ANA_RO01_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_RO01_BIT_END    (7)


/* 寄存器说明：CODEC_ANA_RO02 */
#define HISSC_SMT_CODEC_ANA_RO02_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E4))
/*  */
#define    HISSC_SMT_CODEC_ANA_RO02_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_RO02_BIT_END    (7)

/* 寄存器说明：CODEC_ANA_RW41 */
#define HISSC_SMT_CODEC_ANA_RW41_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E5))

/* 寄存器说明：CODEC_ANA_RW42 */
#define HISSC_SMT_CODEC_ANA_RW42_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E6))

/* 寄存器说明：CODEC_CLASSD_CTRL3 */
#define HISSC_PMU_CODEC_CLASSD_CTRL3_ADDR             ((PAGE_PMCTRL) + (0x6B))
#define    HISSC_PMU_CODEC_CLASSD_DRV_EN_BIT  (4)
#define    HISSC_PMU_CODEC_EN_CLASSD_INT_BIT  (3)

/* 寄存器说明：CODEC_CLASSD_CTRL1 */
#define HISSC_PMU_CODEC_CLASSD_CTRL1_ADDR             ((PAGE_PMCTRL) + (0x69))
#define    HISSC_PMU_CODEC_CLASSD_GAIN_BIT_START  (0)
#define    HISSC_PMU_CODEC_CLASSD_GAIN_BIT_END    (1)
#define    HISSC_PMU_CODEC_CLASSD_I_OCP_BIT_START (2)
#define    HISSC_PMU_CODEC_CLASSD_I_OCP_BIT_END   (3)
#define    HISSC_PMU_CODEC_CLASSD_MUTE_SEL_BIT    (4)
#define    HISSC_PMU_CODEC_CLASSD_MUTE_BIT        (5)
/*****************************************************************************
  3 枚举定义
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
  7 UNION定义
*****************************************************************************/



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

#endif /* end of __AUDIO_CODEC_INTERFACE_H__ */
