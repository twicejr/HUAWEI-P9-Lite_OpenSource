

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_CODEC_INTERFACE_H__
#define __SOC_ASP_CODEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) SoC CODEC
 ****************************************************************************/
/* 寄存器说明：逻辑电路软复位，除寄存器外，复位所有功能逻辑，CRG及寄存器除外。
   位域定义UNION结构:  SOC_ASP_CODEC_SW_RST_N_UNION */
#define SOC_ASP_CODEC_SW_RST_N_ADDR(base)             ((base) + (0x00))

/* 寄存器说明：APB IF/DMIC IF/SIF/I2S接口相关模块时钟使能配置
   位域定义UNION结构:  SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION */
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_ADDR(base)        ((base) + (0x04))

/* 寄存器说明：数字滤波器通道相关模块时钟使能配置，包括DACL/DACR/ ADCL/ADCR通道
   位域定义UNION结构:  SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION */
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_ADDR(base) ((base) + (0x08))

/* 寄存器说明：采样率配置
   位域定义UNION结构:  SOC_ASP_CODEC_FS_CFG_UNION */
#define SOC_ASP_CODEC_FS_CFG_ADDR(base)               ((base) + (0x0C))

/* 寄存器说明：S1/S2接口配置寄存器
   位域定义UNION结构:  SOC_ASP_CODEC_I2S_CFG_UNION */
#define SOC_ASP_CODEC_I2S_CFG_ADDR(base)              ((base) + (0x10))

/* 寄存器说明：DAC/ADC通道内部MIXER、模块BYPASS模式配置寄存器。
   位域定义UNION结构:  SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION */
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_ADDR(base) ((base) + (0x14))

/* 寄存器说明：MUX_TOP中相关模块配置及状态
   位域定义UNION结构:  SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION */
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_ADDR(base)   ((base) + (0x18))

/* 寄存器说明：ADC通道PGA模块配置
   位域定义UNION结构:  SOC_ASP_CODEC_ADC_PGA_CFG_UNION */
#define SOC_ASP_CODEC_ADC_PGA_CFG_ADDR(base)          ((base) + (0x1C))

/* 寄存器说明：S1接口输入通道PGA配置
   位域定义UNION结构:  SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION */
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_ADDR(base)     ((base) + (0x20))

/* 寄存器说明：S2接口输入通道PGA配置
   位域定义UNION结构:  SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION */
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_ADDR(base)     ((base) + (0x24))

/* 寄存器说明：STEREO下行通道PGA配置
   位域定义UNION结构:  SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_ADDR(base) ((base) + (0x28))

/* 寄存器说明：VOICE下行通道PGA及SIDETONE PGA配置
   位域定义UNION结构:  SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION */
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR(base) ((base) + (0x2C))

/* 寄存器说明：APB IF中AFIFO配置及状态信号
   位域定义UNION结构:  SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION */
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_ADDR(base)      ((base) + (0x30))

/* 寄存器说明：APB IF中AFIFO配置及状态信号
   位域定义UNION结构:  SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION */
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_ADDR(base)      ((base) + (0x34))

/* 寄存器说明：STEREO下行通道AFIFO 空满水线配置
   位域定义UNION结构:  SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x38))

/* 寄存器说明：STEREO上行通道AFIFO 空满水线配置
   位域定义UNION结构:  SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x3C))

/* 寄存器说明：VOICE上行通道AFIFO 空满水线配置
   位域定义UNION结构:  SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x40))

/* 寄存器说明：中断屏蔽寄存器
   位域定义UNION结构:  SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION */
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_ADDR(base)       ((base) + (0x44))

/* 寄存器说明：中断状态寄存器
   位域定义UNION结构:  SOC_ASP_CODEC_CODEC_IRQ_UNION */
#define SOC_ASP_CODEC_CODEC_IRQ_ADDR(base)            ((base) + (0x48))

/* 寄存器说明：DACL AGC (自动增益控制)配置寄存器1。
   位域定义UNION结构:  SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION */
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_ADDR(base)       ((base) + (0x4C))

/* 寄存器说明：DACL AGC (自动增益控制)配置寄存器2。
   位域定义UNION结构:  SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION */
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_ADDR(base)       ((base) + (0x50))

/* 寄存器说明：DACR AGC (自动增益控制)配置寄存器1。
   位域定义UNION结构:  SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION */
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_ADDR(base)       ((base) + (0x54))

/* 寄存器说明：DACR AGC (自动增益控制)配置寄存器2。
   位域定义UNION结构:  SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION */
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_ADDR(base)       ((base) + (0x58))

/* 寄存器说明：DMIC接口和Serial接口配置
   位域定义UNION结构:  SOC_ASP_CODEC_DMIC_SIF_CFG_UNION */
#define SOC_ASP_CODEC_DMIC_SIF_CFG_ADDR(base)         ((base) + (0x5C))

/* 寄存器说明：Misc Config
   位域定义UNION结构:  SOC_ASP_CODEC_MISC_CFG_UNION */
#define SOC_ASP_CODEC_MISC_CFG_ADDR(base)             ((base) + (0x60))

/* 寄存器说明：S2接口SRC模块配置
   位域定义UNION结构:  SOC_ASP_CODEC_S2_SRC_CFG_UNION */
#define SOC_ASP_CODEC_S2_SRC_CFG_ADDR(base)           ((base) + (0x64))

/* 寄存器说明：memory配置信号
   位域定义UNION结构:  SOC_ASP_CODEC_MEM_CFG_UNION */
#define SOC_ASP_CODEC_MEM_CFG_ADDR(base)              ((base) + (0x68))

/* 寄存器说明：第三方modem的I2S
   位域定义UNION结构:  SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION */
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_ADDR(base)  ((base) + (0x6C))

/* 寄存器说明：第三方Modem下行通道AFIFO水线
   位域定义UNION结构:  SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION */
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_ADDR(base)  ((base) + (0x70))

/* 寄存器说明：S3接口抗频偏模块TX方向计数器
   位域定义UNION结构:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_ADDR(base) ((base) + (0x74))

/* 寄存器说明：S3接口抗频偏模块TX方向计数器
   位域定义UNION结构:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_ADDR(base) ((base) + (0x78))

/* 寄存器说明：S3接口抗频偏模块RX方向计数器
   位域定义UNION结构:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_ADDR(base) ((base) + (0x7C))

/* 寄存器说明：S3接口抗频偏模块RX方向计数器
   位域定义UNION结构:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_ADDR(base) ((base) + (0x80))

/* 寄存器说明：抗频偏模块使能使能
   位域定义UNION结构:  SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION */
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_ADDR(base)  ((base) + (0x84))

/* 寄存器说明：12.288M时钟来源选择
   位域定义UNION结构:  SOC_ASP_CODEC_CLK_SEL_UNION */
#define SOC_ASP_CODEC_CLK_SEL_ADDR(base)              ((base) + (0x88))

/* 寄存器说明：下行通路到上行通路还回选择
   位域定义UNION结构:  SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION */
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_ADDR(base)      ((base) + (0x8C))

/* 寄存器说明：第三方Modem下行通道
   位域定义UNION结构:  SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_ADDR(base) ((base) + (0xE8))

/* 寄存器说明：第三方Modem上行通道
   位域定义UNION结构:  SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_ADDR(base) ((base) + (0xEC))

/* 寄存器说明：VOICE下行通道
   位域定义UNION结构:  SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_ADDR(base)  ((base) + (0xF0))

/* 寄存器说明：音频下行通道
   位域定义UNION结构:  SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_ADDR(base) ((base) + (0xF4))

/* 寄存器说明：音频上行通道
   位域定义UNION结构:  SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_ADDR(base) ((base) + (0xF8))

/* 寄存器说明：VOICE上行通道
   位域定义UNION结构:  SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_ADDR(base) ((base) + (0xFC))





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

/****************************************************************************
                     (1/1) SoC CODEC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ASP_CODEC_SW_RST_N_UNION
 结构说明  : SW_RST_N 寄存器结构定义。地址偏移量:0x00，初值:0x00000201，宽度:32
 寄存器说明: 逻辑电路软复位，除寄存器外，复位所有功能逻辑，CRG及寄存器除外。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_rst_n  : 1;  /* bit[0]    : 软件复位CODEC内部所有功能逻辑。
                                                     0：复位有效；
                                                     1：正常工作。 */
        unsigned int  dig_ro_00 : 7;  /* bit[1-7]  : [7:3]:reserved RO Registers
                                                     [1]: 第三方Modem场景时，TX方向的抗频偏计数器中断状态，计数器不为0就会发中断
                                                     [0]: 第三方Modem场景时，RX方向的抗频偏计数器中断状态，计数器不为0就会发中断 */
        unsigned int  version   : 8;  /* bit[8-15] : 版本寄存器 */
        unsigned int  dig_rw_00 : 16; /* bit[16-31]: [31]: 第三方Modem场景时，RX方向的抗频偏计数器中断使能
                                                     [30]: 第三方Modem场景时，TX方向的抗频偏计数器中断使能
                                                     [29:28]: stereo_uplink_wordlength
                                                     [27:26]: thirdmd_uplink_wordlength
                                                     [25:24]: voice_uplink_wordlength
                                                     [23:22]: reserved
                                                     [21:20]: stereo_dlink_wordlength
                                                     [19:18]: thirdmd_dlink_wordlength
                                                     [17:16]: voice_dlink_wordlength
                                                     通道数据位宽配置:
                                                     2'b00: 16bit 
                                                     2'b01: 18bit
                                                     2'b10: 20bit 
                                                     2'b11: 24bit */
    } reg;
} SOC_ASP_CODEC_SW_RST_N_UNION;
#endif
#define SOC_ASP_CODEC_SW_RST_N_sw_rst_n_START   (0)
#define SOC_ASP_CODEC_SW_RST_N_sw_rst_n_END     (0)
#define SOC_ASP_CODEC_SW_RST_N_dig_ro_00_START  (1)
#define SOC_ASP_CODEC_SW_RST_N_dig_ro_00_END    (7)
#define SOC_ASP_CODEC_SW_RST_N_version_START    (8)
#define SOC_ASP_CODEC_SW_RST_N_version_END      (15)
#define SOC_ASP_CODEC_SW_RST_N_dig_rw_00_START  (16)
#define SOC_ASP_CODEC_SW_RST_N_dig_rw_00_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION
 结构说明  : IF_CLK_EN_CFG 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: APB IF/DMIC IF/SIF/I2S接口相关模块时钟使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_en : 1;  /* bit[0]    : STEREO上行左通道异步FIFO时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  stereo_uplink_r_en : 1;  /* bit[1]    : STEREO上行右通道异步FIFO时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  voice_uplink_l_en  : 1;  /* bit[2]    : VOICE上行左通道异步FIFO时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  voice_uplink_r_en  : 1;  /* bit[3]    : VOICE上行右通道异步FIFO时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  stereo_dlink_l_en  : 1;  /* bit[4]    : STEREO下行左通道异步FIFO及PGA时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  stereo_dlink_r_en  : 1;  /* bit[5]    : STEREO下行右通道异步FIFO及PGA时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  voice_dlink_en     : 1;  /* bit[6]    : VOICE下行通道异步FIFO及PGA时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  voice_dlink_src_en : 1;  /* bit[7]    : VOICE下行通道SRC使能，同时控制src的bypass：
                                                              0：关闭时钟，src bypass；
                                                              1：打开时钟，src 正常工作。 */
        unsigned int  s1_if_clk_en       : 1;  /* bit[8]    : S1 I2S接口采样时钟使能。
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  s1_il_pga_en       : 1;  /* bit[9]    : I2S S1接口（Digital FM）接口左输入通道PGA时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  s1_ir_pga_en       : 1;  /* bit[10]   : I2S S1接口（Digital FM）接口右输入通道PGA时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  reserved_0         : 1;  /* bit[11]   : reserved */
        unsigned int  s2_il_pga_en       : 1;  /* bit[12]   : I2S S2接口（BT）接口左输入通道PGA时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  s2_ir_pga_en       : 1;  /* bit[13]   : I2S S2接口（BT）接口右输入通道PGA时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  s2_ol_src_en       : 1;  /* bit[14]   : I2S S2接口（BT）接口左输出通道SRC时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  s2_ol_mixer_en     : 1;  /* bit[15]   : I2S S2接口（BT）接口左输出通道MIXER时钟使能：
                                                              0：关闭时钟
                                                              1：打开时钟 */
        unsigned int  s2_if_clk_en       : 1;  /* bit[16]   : S2 I2S接口采样时钟使能。
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  reserved_1         : 3;  /* bit[17-19]: reserved */
        unsigned int  s3_if_clk_en       : 1;  /* bit[20]   : S3 I2S接口采样时钟使能。
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: reserved */
        unsigned int  thirdmd_dlink_en   : 1;  /* bit[24]   : 第三方MODEAM下行通道异步FIFO及PGA时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  thirdmd_uplink_en  : 1;  /* bit[25]   : 第三方MODEAM上行通道异步FIFO时钟使能:
                                                              0：关闭时钟；
                                                              1：打开时钟。 */
        unsigned int  reserved_3         : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION;
#endif
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_l_en_START  (0)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_l_en_END    (0)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_r_en_START  (1)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_r_en_END    (1)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_l_en_START   (2)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_l_en_END     (2)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_r_en_START   (3)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_r_en_END     (3)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_l_en_START   (4)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_l_en_END     (4)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_r_en_START   (5)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_r_en_END     (5)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_en_START      (6)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_en_END        (6)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_src_en_START  (7)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_src_en_END    (7)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_if_clk_en_START        (8)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_if_clk_en_END          (8)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_il_pga_en_START        (9)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_il_pga_en_END          (9)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_ir_pga_en_START        (10)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_ir_pga_en_END          (10)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_il_pga_en_START        (12)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_il_pga_en_END          (12)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ir_pga_en_START        (13)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ir_pga_en_END          (13)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_src_en_START        (14)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_src_en_END          (14)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_mixer_en_START      (15)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_mixer_en_END        (15)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_if_clk_en_START        (16)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_if_clk_en_END          (16)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s3_if_clk_en_START        (20)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s3_if_clk_en_END          (20)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_dlink_en_START    (24)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_dlink_en_END      (24)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_uplink_en_START   (25)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_uplink_en_END     (25)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION
 结构说明  : DIG_FILTER_CLK_EN_CFG 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 数字滤波器通道相关模块时钟使能配置，包括DACL/DACR/ ADCL/ADCR通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adcl_pga_en     : 1;  /* bit[0]    : ADCL通道PGA模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  adcl_hpf_en     : 1;  /* bit[1]    : ADCL通道HPF模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcl_hbfvd_en   : 1;  /* bit[2]    : ADCL通道HBFVD模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcl_hbf2d_en   : 1;  /* bit[3]    : ADCL通道HBF2D模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcl_compd_en   : 1;  /* bit[4]    : ADCL通道COMPD模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcl_cic_en     : 1;  /* bit[5]    : ADCL通道CIC模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  sidetone_pga_en : 1;  /* bit[6]    : SIDETONE PGA模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  reserved_0      : 1;  /* bit[7]    : reserved */
        unsigned int  adcr_pga_en     : 1;  /* bit[8]    : ADCR通道PGA模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  adcr_hpf_en     : 1;  /* bit[9]    : ADCR通道HPF模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcr_hbfvd_en   : 1;  /* bit[10]   : ADCR通道HBFVD模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcr_hbf2d_en   : 1;  /* bit[11]   : ADCR通道HBF2D模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcr_compd_en   : 1;  /* bit[12]   : ADCR通道COMPD模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  adcr_cic_en     : 1;  /* bit[13]   : ADCR通道CIC模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  reserved_1      : 2;  /* bit[14-15]: reserved */
        unsigned int  dacl_agc_en     : 1;  /* bit[16]   : DACL通道AGC模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  dacl_mixer_en   : 1;  /* bit[17]   : DACL通道MIXER模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  dacl_deemp_en   : 1;  /* bit[18]   : DACL通道DEEMP模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacl_hbf1i_en   : 1;  /* bit[19]   : DACL通道HBF1I模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacl_hbf2i_en   : 1;  /* bit[20]   : DACL通道HBF2I模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  dacl_compi_en   : 1;  /* bit[21]   : DACL通道COMPI模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacl_sdm_en     : 1;  /* bit[22]   : DACL通道SDM模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  reserved_2      : 1;  /* bit[23]   : reserved */
        unsigned int  dacr_agc_en     : 1;  /* bit[24]   : DACR通道AGC模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  dacr_mixer_en   : 1;  /* bit[25]   : DACR通道MIXER模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  dacr_deemp_en   : 1;  /* bit[26]   : DACR通道DEEMP模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacr_hbf1i_en   : 1;  /* bit[27]   : DACR通道HBF1I模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacr_hbf2i_en   : 1;  /* bit[28]   : DACR通道HBF2I模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacr_compi_en   : 1;  /* bit[29]   : DACR通道COMPI模块时钟使能：
                                                           0：关闭时钟，bypass；
                                                           1：打开时钟。 */
        unsigned int  dacr_sdm_en     : 1;  /* bit[30]   : DACR通道SDM模块时钟使能：
                                                           0：关闭时钟；
                                                           1：打开时钟。 */
        unsigned int  reserved_3      : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_pga_en_START      (0)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_pga_en_END        (0)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hpf_en_START      (1)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hpf_en_END        (1)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbfvd_en_START    (2)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbfvd_en_END      (2)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbf2d_en_START    (3)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbf2d_en_END      (3)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_compd_en_START    (4)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_compd_en_END      (4)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_cic_en_START      (5)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_cic_en_END        (5)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_sidetone_pga_en_START  (6)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_sidetone_pga_en_END    (6)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_pga_en_START      (8)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_pga_en_END        (8)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hpf_en_START      (9)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hpf_en_END        (9)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbfvd_en_START    (10)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbfvd_en_END      (10)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbf2d_en_START    (11)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbf2d_en_END      (11)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_compd_en_START    (12)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_compd_en_END      (12)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_cic_en_START      (13)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_cic_en_END        (13)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_agc_en_START      (16)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_agc_en_END        (16)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_mixer_en_START    (17)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_mixer_en_END      (17)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_deemp_en_START    (18)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_deemp_en_END      (18)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf1i_en_START    (19)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf1i_en_END      (19)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf2i_en_START    (20)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf2i_en_END      (20)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_compi_en_START    (21)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_compi_en_END      (21)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_sdm_en_START      (22)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_sdm_en_END        (22)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_agc_en_START      (24)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_agc_en_END        (24)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_mixer_en_START    (25)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_mixer_en_END      (25)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_deemp_en_START    (26)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_deemp_en_END      (26)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf1i_en_START    (27)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf1i_en_END      (27)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf2i_en_START    (28)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf2i_en_END      (28)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_compi_en_START    (29)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_compi_en_END      (29)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_sdm_en_START      (30)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_sdm_en_END        (30)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_FS_CFG_UNION
 结构说明  : FS_CFG 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 采样率配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fs_voice_dlink    : 3;  /* bit[0-2]  : VOICE下行通道采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_0        : 1;  /* bit[3]    : reserved */
        unsigned int  fs_stereo_dlink_l : 3;  /* bit[4-6]  : STEREO下行左通道采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_1        : 1;  /* bit[7]    : reserved */
        unsigned int  fs_stereo_dlink_r : 3;  /* bit[8-10] : STEREO下行右通道采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_2        : 5;  /* bit[11-15]: reserved */
        unsigned int  fs_daclr          : 3;  /* bit[16-18]: dacl和dacr通道输入侧采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_3        : 1;  /* bit[19]   : reserved */
        unsigned int  fs_adclr          : 3;  /* bit[20-22]: adcl和adcr通道输出侧采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_4        : 1;  /* bit[23]   : reserved */
        unsigned int  fs_s1             : 3;  /* bit[24-26]: S1接口采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_5        : 1;  /* bit[27]   : reserved */
        unsigned int  fs_s2             : 3;  /* bit[28-30]: S2接口采样率配置
                                                             0：8KHz； 1：16KHz；
                                                             2：32KHz； 3：保留
                                                             4：48KHz； 5：96KHz；
                                                             6：192KHz；7：保留 */
        unsigned int  reserved_6        : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_ASP_CODEC_FS_CFG_UNION;
#endif
#define SOC_ASP_CODEC_FS_CFG_fs_voice_dlink_START     (0)
#define SOC_ASP_CODEC_FS_CFG_fs_voice_dlink_END       (2)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_l_START  (4)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_l_END    (6)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_r_START  (8)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_r_END    (10)
#define SOC_ASP_CODEC_FS_CFG_fs_daclr_START           (16)
#define SOC_ASP_CODEC_FS_CFG_fs_daclr_END             (18)
#define SOC_ASP_CODEC_FS_CFG_fs_adclr_START           (20)
#define SOC_ASP_CODEC_FS_CFG_fs_adclr_END             (22)
#define SOC_ASP_CODEC_FS_CFG_fs_s1_START              (24)
#define SOC_ASP_CODEC_FS_CFG_fs_s1_END                (26)
#define SOC_ASP_CODEC_FS_CFG_fs_s2_START              (28)
#define SOC_ASP_CODEC_FS_CFG_fs_s2_END                (30)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_I2S_CFG_UNION
 结构说明  : I2S_CFG 寄存器结构定义。地址偏移量:0x10，初值:0x03200320，宽度:32
 寄存器说明: S1/S2接口配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s1_func_mode           : 3;  /* bit[0-2]  : S1接口模式选择：
                                                                  3'b000:I2S
                                                                  3'b010:PCM STD
                                                                  3'b011:PCM USER Defined
                                                                  3'b100:Left Justified
                                                                  3'b101:Right Justified
                                                                  其他：保留 */
        unsigned int  s1_codec_data_format   : 1;  /* bit[3]    : S1接口Codec ADC/DAC数据格式选择。
                                                                  0：表示二进制补码；
                                                                  1：表示二进制码（binary offset）。 */
        unsigned int  s1_rx_clk_sel          : 1;  /* bit[4]    : S1接口RX方向时钟选择：
                                                                  1'b0:BCLK上升沿接收数据
                                                                  1'b1:BCLK下降沿接收数据 */
        unsigned int  s1_tx_clk_sel          : 1;  /* bit[5]    : S1接口TX方向时钟选择：
                                                                  1'b0:BCLK上升沿打出数据
                                                                  1'b1:BCLK下降沿打出数据 */
        unsigned int  s1_direct_loop         : 2;  /* bit[6-7]  : S1 I2S接口环回模式选择。
                                                                  2'b00：正常工作模式；
                                                                  2'b01：Sdin->Sdout。
                                                                  2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                  2'b11: SDOUT -> SDIN */
        unsigned int  s1_codec_io_wordlength : 2;  /* bit[8-9]  : S1接口位数控制。
                                                                  00：16bit；
                                                                  01：18bit；
                                                                  10：20bit；
                                                                  11：24bit。 */
        unsigned int  s1_chnnl_mode          : 1;  /* bit[10]   : S1接口声道配置：
                                                                  1'b0:左声道在前
                                                                  1'b1:右声道在前 */
        unsigned int  s1_lrclk_mode          : 1;  /* bit[11]   : S1接口帧同步信号左右声道选择：
                                                                  1'b0:low -> left channel
                                                                  1'b1:low -> right channel */
        unsigned int  s1_mst_slv             : 1;  /* bit[12]   : S1接口Master/Slave模式选择：
                                                                  1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
                                                                  1'b1:Slave模式 */
        unsigned int  s1_frame_mode          : 1;  /* bit[13]   : S1接口I2S模式下帧格式配置：
                                                                  1'b0:I2S模式下64bit frame，PCM模式下32bit frame
                                                                  1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
        unsigned int  s1_if_rx_ena           : 1;  /* bit[14]   : S1接口RX方向使能：
                                                                  1'b1:使能
                                                                  1'b0:关闭 */
        unsigned int  s1_if_tx_ena           : 1;  /* bit[15]   : S1接口TX方向使能：
                                                                  1'b1:使能
                                                                  1'b0:关闭 */
        unsigned int  s2_func_mode           : 3;  /* bit[16-18]: S2接口模式选择：
                                                                  3'b000:I2S
                                                                  3'b010:PCM STD
                                                                  3'b011:PCM USER Defined
                                                                  3'b100:Left Justified
                                                                  3'b101:Right Justified
                                                                  其他：保留 */
        unsigned int  s2_codec_data_format   : 1;  /* bit[19]   : S2接口Codec ADC/DAC数据格式选择。
                                                                  0：表示二进制补码；
                                                                  1：表示二进制码（binary offset）。 */
        unsigned int  s2_rx_clk_sel          : 1;  /* bit[20]   : S2接口RX方向时钟选择：
                                                                  1'b0:BCLK上升沿接收数据
                                                                  1'b1:BCLK下降沿接收数据 */
        unsigned int  s2_tx_clk_sel          : 1;  /* bit[21]   : S2接口TX方向时钟选择：
                                                                  1'b0:BCLK上升沿打出数据
                                                                  1'b1:BCLK下降沿打出数据 */
        unsigned int  s2_direct_loop         : 2;  /* bit[22-23]: S2 I2S接口环回模式选择。
                                                                  2'b00：正常工作模式；
                                                                  2'b01：Sdin->Sdout。
                                                                  2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                  2'b11: SDOUT -> SDIN */
        unsigned int  s2_codec_io_wordlength : 2;  /* bit[24-25]: S2接口位数控制。
                                                                  00：16bit；
                                                                  01：18bit；
                                                                  10：20bit；
                                                                  11：24bit。 */
        unsigned int  s2_chnnl_mode          : 1;  /* bit[26]   : S2接口声道配置：
                                                                  1'b0:左声道在前
                                                                  1'b1:右声道在前 */
        unsigned int  s2_lrclk_mode          : 1;  /* bit[27]   : S2接口帧同步信号左右声道选择：
                                                                  1'b0:low -> left channel
                                                                  1'b1:low -> right channel */
        unsigned int  s2_mst_slv             : 1;  /* bit[28]   : S2接口Master/Slave模式选择：
                                                                  1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
                                                                  1'b1:Slave模式 */
        unsigned int  s2_frame_mode          : 1;  /* bit[29]   : S2接口I2S模式下帧格式配置：
                                                                  1'b0:I2S模式下64bit frame，PCM模式下32bit frame
                                                                  1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
        unsigned int  s2_if_rx_ena           : 1;  /* bit[30]   : S2接口RX方向使能：
                                                                  1'b1:使能
                                                                  1'b0:关闭 */
        unsigned int  s2_if_tx_ena           : 1;  /* bit[31]   : S2接口TX方向使能：
                                                                  1'b1:使能
                                                                  1'b0:关闭 */
    } reg;
} SOC_ASP_CODEC_I2S_CFG_UNION;
#endif
#define SOC_ASP_CODEC_I2S_CFG_s1_func_mode_START            (0)
#define SOC_ASP_CODEC_I2S_CFG_s1_func_mode_END              (2)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_data_format_START    (3)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_data_format_END      (3)
#define SOC_ASP_CODEC_I2S_CFG_s1_rx_clk_sel_START           (4)
#define SOC_ASP_CODEC_I2S_CFG_s1_rx_clk_sel_END             (4)
#define SOC_ASP_CODEC_I2S_CFG_s1_tx_clk_sel_START           (5)
#define SOC_ASP_CODEC_I2S_CFG_s1_tx_clk_sel_END             (5)
#define SOC_ASP_CODEC_I2S_CFG_s1_direct_loop_START          (6)
#define SOC_ASP_CODEC_I2S_CFG_s1_direct_loop_END            (7)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_io_wordlength_START  (8)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_io_wordlength_END    (9)
#define SOC_ASP_CODEC_I2S_CFG_s1_chnnl_mode_START           (10)
#define SOC_ASP_CODEC_I2S_CFG_s1_chnnl_mode_END             (10)
#define SOC_ASP_CODEC_I2S_CFG_s1_lrclk_mode_START           (11)
#define SOC_ASP_CODEC_I2S_CFG_s1_lrclk_mode_END             (11)
#define SOC_ASP_CODEC_I2S_CFG_s1_mst_slv_START              (12)
#define SOC_ASP_CODEC_I2S_CFG_s1_mst_slv_END                (12)
#define SOC_ASP_CODEC_I2S_CFG_s1_frame_mode_START           (13)
#define SOC_ASP_CODEC_I2S_CFG_s1_frame_mode_END             (13)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_rx_ena_START            (14)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_rx_ena_END              (14)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_tx_ena_START            (15)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_tx_ena_END              (15)
#define SOC_ASP_CODEC_I2S_CFG_s2_func_mode_START            (16)
#define SOC_ASP_CODEC_I2S_CFG_s2_func_mode_END              (18)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_data_format_START    (19)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_data_format_END      (19)
#define SOC_ASP_CODEC_I2S_CFG_s2_rx_clk_sel_START           (20)
#define SOC_ASP_CODEC_I2S_CFG_s2_rx_clk_sel_END             (20)
#define SOC_ASP_CODEC_I2S_CFG_s2_tx_clk_sel_START           (21)
#define SOC_ASP_CODEC_I2S_CFG_s2_tx_clk_sel_END             (21)
#define SOC_ASP_CODEC_I2S_CFG_s2_direct_loop_START          (22)
#define SOC_ASP_CODEC_I2S_CFG_s2_direct_loop_END            (23)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_io_wordlength_START  (24)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_io_wordlength_END    (25)
#define SOC_ASP_CODEC_I2S_CFG_s2_chnnl_mode_START           (26)
#define SOC_ASP_CODEC_I2S_CFG_s2_chnnl_mode_END             (26)
#define SOC_ASP_CODEC_I2S_CFG_s2_lrclk_mode_START           (27)
#define SOC_ASP_CODEC_I2S_CFG_s2_lrclk_mode_END             (27)
#define SOC_ASP_CODEC_I2S_CFG_s2_mst_slv_START              (28)
#define SOC_ASP_CODEC_I2S_CFG_s2_mst_slv_END                (28)
#define SOC_ASP_CODEC_I2S_CFG_s2_frame_mode_START           (29)
#define SOC_ASP_CODEC_I2S_CFG_s2_frame_mode_END             (29)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_rx_ena_START            (30)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_rx_ena_END              (30)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_tx_ena_START            (31)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_tx_ena_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION
 结构说明  : DIG_FILTER_MODULE_CFG 寄存器结构定义。地址偏移量:0x14，初值:0x0F0F0000，宽度:32
 寄存器说明: DAC/ADC通道内部MIXER、模块BYPASS模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rm_codec_dac2adc    : 3;  /* bit[0-2]  : ADCR通道CIC滤波器及回环路径控制。
                                                               000：CIC输入为ADC路径偏移后（减4）输入；；
                                                               001：CIC输入为DACL路径输入；
                                                               010：CIC输入为DACR路径输入；
                                                               011：CIC输入为ADC路径输入（环回使用）；
                                                               100：CIC输入为DMIC PORT0路径输入；
                                                               101：reserved；
                                                               其他值：CIC输入为ADC路径偏移后（减4）输入；。 */
        unsigned int  reserved_0          : 1;  /* bit[3]    : reserved */
        unsigned int  lm_codec_dac2adc    : 3;  /* bit[4-6]  : ADCL通道CIC滤波器及回环路径控制。
                                                               000：CIC输入为ADC路径偏移后（减4）输入；
                                                               001：CIC输入为DACL路径输入；
                                                               010：CIC输入为DACR路径输入；
                                                               011：CIC输入为ADC路径输入（环回使用）；
                                                               100：CIC输入为DMIC PORT0路径输入；
                                                               101：reserved；
                                                               其他值：CIC输入为ADC路径偏移后（减4）输入； */
        unsigned int  reserved_1          : 1;  /* bit[7]    : reserved */
        unsigned int  sw_dacl_sdm_dither  : 1;  /* bit[8]    : DACL SDM dither配置。 
                                                               1：dither电路有效； 
                                                               0：dither电路无效。 */
        unsigned int  sw_dacr_sdm_dither  : 1;  /* bit[9]    : DACR SDM dither配置。 
                                                               1：dither电路有效； 
                                                               0：dither电路无效。 */
        unsigned int  reserved_2          : 6;  /* bit[10-15]: reserved */
        unsigned int  dacl_mixer_in1_mute : 1;  /* bit[16]   : DACL通道mixer的mute使能：
                                                               1'b1:voice dlink src输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacl_mixer_in2_mute : 1;  /* bit[17]   : DACL通道mixer的mute使能：
                                                               1'b1:stereo dlink左通道pga输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacl_mixer_in3_mute : 1;  /* bit[18]   : DACL通道mixer的 mute使能：
                                                               1'b1:s1左输入通道pga输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacl_mixer_in4_mute : 1;  /* bit[19]   : DACL通道mixer mute使能：
                                                               1'b1:sidetone pga 输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacl_mixer_gain     : 2;  /* bit[20-21]: DACL通道MIXER的增益配置：
                                                               2'b00:1
                                                               2'b01:乘以1/2
                                                               2'b10:乘以1/4
                                                               2'b11:保留 */
        unsigned int  reserved_3          : 2;  /* bit[22-23]: reserved */
        unsigned int  dacr_mixer_in1_mute : 1;  /* bit[24]   : DACR通道mixer的mute使能：
                                                               1'b1:voice dlink src输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacr_mixer_in2_mute : 1;  /* bit[25]   : DACR通道mixer的mute使能：
                                                               1'b1:stereo dlink右通道pga输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacr_mixer_in3_mute : 1;  /* bit[26]   : DACR通道mixer的 mute使能：
                                                               1'b1:s1右输入通道pga输出mute
                                                               1'b0:正常输入 */
        unsigned int  dacr_mixer_in4_mute : 1;  /* bit[27]   : DACR通道mixer mute使能：
                                                               1'b1:sidetone pga 输出mutemute
                                                               1'b0:正常输入 */
        unsigned int  dacr_mixer_gain     : 2;  /* bit[28-29]: DACR通道MIXER的增益配置：
                                                               2'b00:1
                                                               2'b01:乘以1/2
                                                               2'b10:乘以1/4
                                                               2'b11:保留 */
        unsigned int  reserved_4          : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_rm_codec_dac2adc_START     (0)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_rm_codec_dac2adc_END       (2)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_lm_codec_dac2adc_START     (4)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_lm_codec_dac2adc_END       (6)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacl_sdm_dither_START   (8)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacl_sdm_dither_END     (8)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacr_sdm_dither_START   (9)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacr_sdm_dither_END     (9)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in1_mute_START  (16)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in1_mute_END    (16)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in2_mute_START  (17)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in2_mute_END    (17)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in3_mute_START  (18)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in3_mute_END    (18)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in4_mute_START  (19)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in4_mute_END    (19)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_gain_START      (20)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_gain_END        (21)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in1_mute_START  (24)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in1_mute_END    (24)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in2_mute_START  (25)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in2_mute_END    (25)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in3_mute_START  (26)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in3_mute_END    (26)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in4_mute_START  (27)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in4_mute_END    (27)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_gain_START      (28)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_gain_END        (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION
 结构说明  : MUX_TOP_MODULE_CFG 寄存器结构定义。地址偏移量:0x18，初值:0x00003300，宽度:32
 寄存器说明: MUX_TOP中相关模块配置及状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_src_mode       : 3;  /* bit[0-2]  : VOICE下行通道SRC MODE选择：
                                                                      3'b001: 12 interpolation
                                                                      3'b010: 6 interpolation
                                                                      3'b011: 2 interpolation
                                                                      3'b100: 3 interpolation
                                                                      other: reserved, not work */
        unsigned int  voice_dlink_src_rdy        : 1;  /* bit[3]    : VOICE下行通道SRC READY信号：
                                                                      1'b1:SRC RAM初始化完成
                                                                      1'b0:SRC RAM初始化进行中（软件不关心该寄存器则至多丢失一个采样点） */
        unsigned int  s2_ol_src_mode             : 2;  /* bit[4-5]  : S2 I2S接口SRC MODE选择：
                                                                      2'b00: 3倍降采样
                                                                      2'b01:12倍降采样
                                                                      2'b10:6倍降采样
                                                                      2'b11:2倍降采样 */
        unsigned int  s2_ol_src_rdy              : 1;  /* bit[6]    : S2 I2S接口左输入通道SRC READY信号：
                                                                      1'b1:SRC RAM初始化完成
                                                                      1'b0:SRC RAM初始化进行中（软件不关心该寄存器则至多丢失一个采样点） */
        unsigned int  reserved_0                 : 1;  /* bit[7]    : reserved */
        unsigned int  s2_ol_mixer_in1_mute       : 1;  /* bit[8]    : S2接口输出左通道mixer输出mute使能：
                                                                      1'b1: DACL mixer 输出mute
                                                                      1'b0:正常输入 */
        unsigned int  s2_ol_mixer_in2_mute       : 1;  /* bit[9]    : S2接口输出左通道mixer输出mute使能：
                                                                      1'b1:DACR mixer 输出mute
                                                                      1'b0:正常输入 */
        unsigned int  s2_ol_mixer_gain           : 2;  /* bit[10-11]: S2左输出通道MIXER的增益配置：
                                                                      2'b00:1
                                                                      2'b01:乘以1/2
                                                                      2'b10:保留
                                                                      2'b11:保留 */
        unsigned int  voice_dlink_mixer_in1_mute : 1;  /* bit[12]   : voice downlink 通道mixer输出mute使能：
                                                                      1'b1: DACL mixer 输出mute
                                                                      1'b0:正常输入 */
        unsigned int  voice_dlink_mixer_in2_mute : 1;  /* bit[13]   : voice downlink 通道mixer输出mute使能：
                                                                      1'b1:DACR mixer 输出mute
                                                                      1'b0:正常输入 */
        unsigned int  voice_dlink_mixer_gain     : 2;  /* bit[14-15]: voice downlink 通道MIXER的增益配置：
                                                                      2'b00:1
                                                                      2'b01:乘以1/2
                                                                      2'b10:保留
                                                                      2'b11:保留 */
        unsigned int  reserved_1                 : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_mode_START        (0)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_mode_END          (2)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_rdy_START         (3)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_rdy_END           (3)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_mode_START              (4)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_mode_END                (5)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_rdy_START               (6)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_rdy_END                 (6)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in1_mute_START        (8)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in1_mute_END          (8)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in2_mute_START        (9)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in2_mute_END          (9)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_gain_START            (10)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_gain_END              (11)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in1_mute_START  (12)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in1_mute_END    (12)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in2_mute_START  (13)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in2_mute_END    (13)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_gain_START      (14)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_gain_END        (15)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_ADC_PGA_CFG_UNION
 结构说明  : ADC_PGA_CFG 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: ADC通道PGA模块配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adcl_pga_integer_config : 8;  /* bit[0-7]  : ADCL pga增益控制整数部分:
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
        unsigned int  adcl_pga_frac_config    : 1;  /* bit[8]    : ADCL pga输入增益小数位配置。
                                                                   0：0.0dB；
                                                                   1：0.5dB。 */
        unsigned int  adcl_pga_mute           : 1;  /* bit[9]    : ADCL pga mute使能：
                                                                   1'b1: mute有效，输出0
                                                                   1'b0: 关闭mute */
        unsigned int  reserved_0              : 2;  /* bit[10-11]: reserved */
        unsigned int  adcl_pga_thr_config     : 2;  /* bit[12-13]: ADCL pga过零检测低电平门限配置。 
                                                                   00：-60dB； 
                                                                   01：-72dB； 
                                                                   10：-90dB； 
                                                                   11：-120dB； */
        unsigned int  reserved_1              : 2;  /* bit[14-15]: reserved */
        unsigned int  adcr_pga_integer_config : 8;  /* bit[16-23]: ADCR pga增益控制整数部分:
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
        unsigned int  adcr_pga_frac_config    : 1;  /* bit[24]   : ADCR pga输入增益小数位配置。
                                                                   0：0.0dB；
                                                                   1：0.5dB。 */
        unsigned int  adcr_pga_mute           : 1;  /* bit[25]   : ADCR pga mute使能：
                                                                   1'b1: mute有效，输出0
                                                                   1'b0: 关闭mute */
        unsigned int  reserved_2              : 2;  /* bit[26-27]: reserved */
        unsigned int  adcr_pga_thr_config     : 2;  /* bit[28-29]: ADCR pga过零检测低电平门限配置。 
                                                                   00：-60dB； 
                                                                   01：-72dB； 
                                                                   10：-90dB； 
                                                                   11：-120dB； */
        unsigned int  reserved_3              : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_ADC_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_mute_START            (9)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_mute_END              (9)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_mute_START            (25)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_mute_END              (25)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_thr_config_END        (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION
 结构说明  : S1_INPUT_PGA_CFG 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: S1接口输入通道PGA配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s1_il_pga_integer_config : 8;  /* bit[0-7]  : S1 I2S接口左输入通道pga增益控制整数部分:
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
        unsigned int  s1_il_pga_frac_config    : 1;  /* bit[8]    : S1接口 左输入通道pga输入增益小数位配置。
                                                                    0：0.0dB；
                                                                    1：0.5dB。 */
        unsigned int  s1_il_pga_mute           : 1;  /* bit[9]    : S1接口左输入通道pga mute使能：
                                                                    1'b1: mute有效，输出0
                                                                    1'b0: 关闭mute */
        unsigned int  reserved_0               : 2;  /* bit[10-11]: reserved */
        unsigned int  s1_il_pga_thr_config     : 2;  /* bit[12-13]: S1接口左输入通道pga过零检测低电平门限配置。 
                                                                    00：-60dB； 
                                                                    01：-72dB； 
                                                                    10：-90dB； 
                                                                    11：-120dB； */
        unsigned int  reserved_1               : 2;  /* bit[14-15]: reserved */
        unsigned int  s1_ir_pga_integer_config : 8;  /* bit[16-23]: S1 I2S接口右输入通道pga增益控制整数部分:
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
        unsigned int  s1_ir_pga_frac_config    : 1;  /* bit[24]   : S1接口右输入通道pga输入增益小数位配置。
                                                                    0：0.0dB；
                                                                    1：0.5dB。 */
        unsigned int  s1_ir_pga_mute           : 1;  /* bit[25]   : S1接口右输入通道pga mute使能：
                                                                    1'b1: mute有效，输出0
                                                                    1'b0: 关闭mute */
        unsigned int  reserved_2               : 2;  /* bit[26-27]: reserved */
        unsigned int  s1_ir_pga_thr_config     : 2;  /* bit[28-29]: S1接口右输入通道pga过零检测低电平门限配置。 
                                                                    00：-60dB； 
                                                                    01：-72dB； 
                                                                    10：-90dB； 
                                                                    11：-120dB； */
        unsigned int  reserved_3               : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_mute_START            (9)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_mute_END              (9)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_mute_START            (25)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_mute_END              (25)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_thr_config_END        (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION
 结构说明  : S2_INPUT_PGA_CFG 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: S2接口输入通道PGA配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_il_pga_integer_config : 8;  /* bit[0-7]  : S2 I2S接口左输入通道pga增益控制整数部分:
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
        unsigned int  s2_il_pga_frac_config    : 1;  /* bit[8]    : S2接口 左输入通道pga输入增益小数位配置。
                                                                    0：0.0dB；
                                                                    1：0.5dB。 */
        unsigned int  s2_il_pga_mute           : 1;  /* bit[9]    : S2接口左输入通道pga mute使能：
                                                                    1'b1: mute有效，输出0
                                                                    1'b0: 关闭mute */
        unsigned int  reserved_0               : 2;  /* bit[10-11]: reserved */
        unsigned int  s2_il_pga_thr_config     : 2;  /* bit[12-13]: S2接口左输入通道pga过零检测低电平门限配置。 
                                                                    00：-60dB； 
                                                                    01：-72dB； 
                                                                    10：-90dB； 
                                                                    11：-120dB； */
        unsigned int  reserved_1               : 2;  /* bit[14-15]: reserved */
        unsigned int  s2_ir_pga_integer_config : 8;  /* bit[16-23]: S2 I2S接口右输入通道pga增益控制整数部分:
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
        unsigned int  s2_ir_pga_frac_config    : 1;  /* bit[24]   : S2接口右输入通道pga输入增益小数位配置。
                                                                    0：0.0dB；
                                                                    1：0.5dB。 */
        unsigned int  s2_ir_pga_mute           : 1;  /* bit[25]   : S2接口右输入通道pga mute使能：
                                                                    1'b1: mute有效，输出0
                                                                    1'b0: 关闭mute */
        unsigned int  reserved_2               : 2;  /* bit[26-27]: reserved */
        unsigned int  s2_ir_pga_thr_config     : 2;  /* bit[28-29]: S2接口右输入通道pga过零检测低电平门限配置。 
                                                                    00：-60dB； 
                                                                    01：-72dB； 
                                                                    10：-90dB； 
                                                                    11：-120dB； */
        unsigned int  reserved_3               : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_mute_START            (9)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_mute_END              (9)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_mute_START            (25)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_mute_END              (25)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_thr_config_END        (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION
 结构说明  : STEREO_DLINK_PGA_CFG 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: STEREO下行通道PGA配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_l_pga_integer_config : 8;  /* bit[0-7]  : stereo下行左声道pga增益控制整数部分:
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
        unsigned int  stereo_dlink_l_pga_frac_config    : 1;  /* bit[8]    : stereo下行左声道pga输入增益小数位配置。
                                                                             0：0.0dB；
                                                                             1：0.5dB。 */
        unsigned int  stereo_dlink_l_pga_mute           : 1;  /* bit[9]    : stereo下行左声道pga mute使能：
                                                                             1'b1: mute有效，输出0
                                                                             1'b0: 关闭mute */
        unsigned int  reserved_0                        : 2;  /* bit[10-11]: reserved */
        unsigned int  stereo_dlink_l_pga_thr_config     : 2;  /* bit[12-13]: stereo下行左声道pga过零检测低电平门限配置。 
                                                                             00：-60dB； 
                                                                             01：-72dB； 
                                                                             10：-90dB； 
                                                                             11：-120dB； */
        unsigned int  reserved_1                        : 2;  /* bit[14-15]: reserved */
        unsigned int  stereo_dlink_r_pga_integer_config : 8;  /* bit[16-23]: stereo下行右声道pga增益控制整数部分:
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
        unsigned int  stereo_dlink_r_pga_frac_config    : 1;  /* bit[24]   : stereo下行右声道pga输入增益小数位配置。
                                                                             0：0.0dB；
                                                                             1：0.5dB。 */
        unsigned int  stereo_dlink_r_pga_mute           : 1;  /* bit[25]   : stereo下行右声道pga mute使能：
                                                                             1'b1: mute有效，输出0
                                                                             1'b0: 关闭mute */
        unsigned int  reserved_2                        : 2;  /* bit[26-27]: reserved */
        unsigned int  stereo_dlink_r_pga_thr_config     : 2;  /* bit[28-29]: stereo下行右声道pga过零检测低电平门限配置。 
                                                                             00：-60dB； 
                                                                             01：-72dB； 
                                                                             10：-90dB； 
                                                                             11：-120dB； */
        unsigned int  reserved_3                        : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_mute_START            (9)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_mute_END              (9)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_mute_START            (25)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_mute_END              (25)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_thr_config_END        (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION
 结构说明  : VOICE_SIDETONE_DLINK_PGA_CFG 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: VOICE下行通道PGA及SIDETONE PGA配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_pga_integer_config : 8;  /* bit[0-7]  : VOICE下行通道pga输入增益控制整数部分:
                                                                          默认：0dB
                                                                          增益范围:-72dB~+36dB。
                                                                          即：
                                                                          0010_0100:36dB
                                                                          0010_0011:35dB
                                                                          ……
                                                                          1011_1000：-72dB
                                                                          步长为1dB,补码表示。 */
        unsigned int  voice_dlink_pga_frac_config    : 1;  /* bit[8]    : VOICE下行通道pga输入增益小数位配置。
                                                                          0：0.0dB；
                                                                          1：0.5dB。 */
        unsigned int  voice_dlink_pga_mute           : 1;  /* bit[9]    : voice下行声道pga mute使能：
                                                                          1'b1: mute有效，输出0
                                                                          1'b0: 关闭mute */
        unsigned int  reserved_0                     : 2;  /* bit[10-11]: reserved */
        unsigned int  voice_dlink_pga_thr_config     : 2;  /* bit[12-13]: voice dlink通道pga过零检测低电平门限配置。 
                                                                          00：-60dB； 
                                                                          01：-72dB； 
                                                                          10：-90dB； 
                                                                          11：-120dB； */
        unsigned int  reserved_1                     : 2;  /* bit[14-15]: reserved */
        unsigned int  sidetone_pga_integer_config    : 8;  /* bit[16-23]: SIDETONE pga输入增益控制整数部分:
                                                                          默认：0dB
                                                                          增益范围:-72dB~+36dB。
                                                                          即：
                                                                          0010_0100:36dB
                                                                          0010_0011:35dB
                                                                          ……
                                                                          1011_1000：-72dB
                                                                          步长为1dB,补码表示。 */
        unsigned int  sidetone_pga_frac_config       : 1;  /* bit[24]   : SIDETONE pga输入增益小数位配置。
                                                                          0：0.0dB；
                                                                          1：0.5dB。 */
        unsigned int  sidetone_pga_mute              : 1;  /* bit[25]   : SIDETONE pga mute使能：
                                                                          1'b1: mute有效，输出0
                                                                          1'b0: 关闭mute */
        unsigned int  reserved_2                     : 2;  /* bit[26-27]: reserved */
        unsigned int  sidetone_pga_thr_config        : 2;  /* bit[28-29]: sidetone pga过零检测低电平门限配置。 
                                                                          00：-60dB； 
                                                                          01：-72dB； 
                                                                          10：-90dB； 
                                                                          11：-120dB； */
        unsigned int  reserved_3                     : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_mute_START            (9)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_mute_END              (9)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_integer_config_START     (16)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_integer_config_END       (23)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_frac_config_START        (24)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_frac_config_END          (24)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_mute_START               (25)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_mute_END                 (25)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_thr_config_START         (28)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_thr_config_END           (29)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION
 结构说明  : APB_AFIFO_CFG_1 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: APB IF中AFIFO配置及状态信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_fifo_clr    : 1;  /* bit[0]   : STEREO UPLINK左通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  stereo_uplink_r_fifo_clr    : 1;  /* bit[1]   : STEREO UPLINK右通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  voice_uplink_l_fifo_clr     : 1;  /* bit[2]   : VOICE UPLINK左通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  voice_uplink_r_fifo_clr     : 1;  /* bit[3]   : VOICE UPLINK右通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  stereo_dlink_l_fifo_clr     : 1;  /* bit[4]   : STEREO DLINK左通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  stereo_dlink_r_fifo_clr     : 1;  /* bit[5]   : STEREO DLINK右通道AFIFO清空配置：
                                                                      1'b1: clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  voice_dlink_fifo_clr        : 1;  /* bit[6]   : VOICE DLINK通道AFIFO清空配置：
                                                                      1'b1:clr有效，清除FIFO数据
                                                                      1'b0: clr无效 */
        unsigned int  thirdmd_dlink_fifo_clr      : 1;  /* bit[7]   :  */
        unsigned int  thirdmd_uplink_fifo_clr     : 1;  /* bit[8]   :  */
        unsigned int  reserved_0                  : 7;  /* bit[9-15]: reserved */
        unsigned int  stereo_uplink_l_fifo_werror : 1;  /* bit[16]  : STEREO UPLINK左通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_uplink_r_fifo_werror : 1;  /* bit[17]  : STEREO UPLINK右通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_uplink_l_fifo_werror  : 1;  /* bit[18]  : VOICE UPLINK左通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_uplink_r_fifo_werror  : 1;  /* bit[19]  : VOICE UPLINK右通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_dlink_l_fifo_werror  : 1;  /* bit[20]  : STEREO DLINK左通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_dlink_r_fifo_werror  : 1;  /* bit[21]  : STEREO DLINK右通道AFIFO写error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_dlink_fifo_werror     : 1;  /* bit[22]  : VOICE DLINK通道AFIFO写error
                                                                      1'b1: FIFO满时写数据
                                                                      1'b0: 正常 */
        unsigned int  reserved_1                  : 1;  /* bit[23]  : reserved */
        unsigned int  stereo_uplink_l_fifo_rerror : 1;  /* bit[24]  : STEREO UPLINK左通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_uplink_r_fifo_rerror : 1;  /* bit[25]  : STEREO UPLINK右通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_uplink_l_fifo_rerror  : 1;  /* bit[26]  : VOICE UPLINK左通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_uplink_r_fifo_rerror  : 1;  /* bit[27]  : VOICE UPLINK右通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_dlink_l_fifo_rerror  : 1;  /* bit[28]  : STEREO DLINK左通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  stereo_dlink_r_fifo_rerror  : 1;  /* bit[29]  : STEREO DLINK右通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  voice_dlink_fifo_rerror     : 1;  /* bit[30]  : VOICE DLINK通道AFIFO读error
                                                                      1'b1: FIFO空时读数据
                                                                      1'b0: 正常 */
        unsigned int  reserved_2                  : 1;  /* bit[31]  : reserved */
    } reg;
} SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_clr_START     (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_clr_END       (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_clr_START     (1)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_clr_END       (1)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_clr_START      (2)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_clr_END        (2)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_clr_START      (3)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_clr_END        (3)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_clr_START      (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_clr_END        (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_clr_START      (5)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_clr_END        (5)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_clr_START         (6)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_clr_END           (6)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_dlink_fifo_clr_START       (7)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_dlink_fifo_clr_END         (7)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_uplink_fifo_clr_START      (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_uplink_fifo_clr_END        (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_werror_START  (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_werror_END    (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_werror_START  (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_werror_END    (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_werror_START   (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_werror_END     (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_werror_START   (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_werror_END     (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_werror_START   (20)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_werror_END     (20)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_werror_START   (21)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_werror_END     (21)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_werror_START      (22)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_werror_END        (22)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_rerror_START  (24)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_rerror_END    (24)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_rerror_START  (25)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_rerror_END    (25)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_rerror_START   (26)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_rerror_END     (26)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_rerror_START   (27)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_rerror_END     (27)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_rerror_START   (28)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_rerror_END     (28)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_rerror_START   (29)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_rerror_END     (29)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_rerror_START      (30)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_rerror_END        (30)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION
 结构说明  : APB_AFIFO_CFG_2 寄存器结构定义。地址偏移量:0x34，初值:0x000F101E，宽度:32
 寄存器说明: APB IF中AFIFO配置及状态信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_fifo_afull_th    : 5;  /* bit[0-4]  : VOICE DLINK通道AFIFO将满阈值，fifo中有效数值个数高于该值时，FIFO almost full信号有效 */
        unsigned int  reserved_0                   : 3;  /* bit[5-7]  : reserved */
        unsigned int  voice_dlink_fifo_aempty_th   : 5;  /* bit[8-12] : VOICE DLINK通道AFIFO将空阈值，fifo中有效数值个数低于该值时，FIFO almost empty信号有效 */
        unsigned int  reserved_1                   : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_uplink_l_fifo_din_sel : 1;  /* bit[16]   : STEREO UPLINK左通道AFIFO输入数据选择：
                                                                        1'b1:ADCL通道输出数据
                                                                        1'b0:S1接口输入左声道 */
        unsigned int  stereo_uplink_r_fifo_din_sel : 1;  /* bit[17]   : STEREO UPLINK右通道AFIFO输入数据选择：
                                                                        1'b1:ADCR通道输出数据
                                                                        1'b0:S1接口输入右声道 */
        unsigned int  voice_uplink_l_fifo_din_sel  : 1;  /* bit[18]   : VOICE UPLINK左通道AFIFO输入数据选择：
                                                                        1'b1:ADCL通道输出数据
                                                                        1'b0:S2接口输入左声道 */
        unsigned int  voice_uplink_r_fifo_din_sel  : 1;  /* bit[19]   : VOICE UPLINK右通道AFIFO输入数据选择：
                                                                        1'b1:ADCR通道输出数据
                                                                        1'b0:S2接口输入右声道 */
        unsigned int  reserved_2                   : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_afull_th_START     (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_afull_th_END       (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_aempty_th_START    (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_aempty_th_END      (12)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_l_fifo_din_sel_START  (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_l_fifo_din_sel_END    (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_r_fifo_din_sel_START  (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_r_fifo_din_sel_END    (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_l_fifo_din_sel_START   (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_l_fifo_din_sel_END     (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_r_fifo_din_sel_START   (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_r_fifo_din_sel_END     (19)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION
 结构说明  : STEREO_DLINK_FIFO_TH_CFG 寄存器结构定义。地址偏移量:0x38，初值:0x101E101E，宽度:32
 寄存器说明: STEREO下行通道AFIFO 空满水线配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_l_fifo_afull_th  : 5;  /* bit[0-4]  : STEREO DLINK左通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  stereo_dlink_l_fifo_aempty_th : 5;  /* bit[8-12] : STEREO DLINK左通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_dlink_r_fifo_afull_th  : 5;  /* bit[16-20]: STEREO DLINK右通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  stereo_dlink_r_fifo_aempty_th : 5;  /* bit[24-28]: STEREO DLINK右通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION
 结构说明  : STEREO_UPLINK_FIFO_TH_CFG 寄存器结构定义。地址偏移量:0x3C，初值:0x01100110，宽度:32
 寄存器说明: STEREO上行通道AFIFO 空满水线配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_fifo_afull_th  : 5;  /* bit[0-4]  : STEREO UPLINK左通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_0                     : 3;  /* bit[5-7]  : reserved */
        unsigned int  stereo_uplink_l_fifo_aempty_th : 5;  /* bit[8-12] : STEREO UPLINK左通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_1                     : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_uplink_r_fifo_afull_th  : 5;  /* bit[16-20]: STEREO UPLINK右通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_2                     : 3;  /* bit[21-23]: reserved */
        unsigned int  stereo_uplink_r_fifo_aempty_th : 5;  /* bit[24-28]: STEREO UPLINK右通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_3                     : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION
 结构说明  : VOICE_UPLINK_FIFO_TH_CFG 寄存器结构定义。地址偏移量:0x40，初值:0x01100110，宽度:32
 寄存器说明: VOICE上行通道AFIFO 空满水线配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_uplink_l_fifo_afull_th  : 5;  /* bit[0-4]  : VOICE UPLINK左通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  voice_uplink_l_fifo_aempty_th : 5;  /* bit[8-12] : VOICE UPLINK左通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  voice_uplink_r_fifo_afull_th  : 5;  /* bit[16-20]: VOICE UPLINK右通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  voice_uplink_r_fifo_aempty_th : 5;  /* bit[24-28]: VOICE UPLINK右通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION
 结构说明  : CODEC_IRQ_MASK 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  codec_data_intrp_mask : 6;  /* bit[0-5] : 中断屏蔽位：
                                                                [5]: thirdmd uplink中断屏蔽
                                                                [4]: thirdmd dlink 中断屏蔽
                                                                [3]: voice uplink中断屏蔽
                                                                [2]: stereo uplink中断屏蔽
                                                                [1]: stereo dlink中断屏蔽
                                                                [0]: voice dlink中断屏蔽 */
        unsigned int  reserved              : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION;
#endif
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_codec_data_intrp_mask_START  (0)
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_codec_data_intrp_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_CODEC_IRQ_UNION
 结构说明  : CODEC_IRQ 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  codec_data_intrp : 6;  /* bit[0-5] : 中断状态位：
                                                           [5]: thirdmd uplink中断，为1时表示thirdmd uplink请求Master读数据
                                                           [4]: thirdmd dlink 中断，为1时表示thirdmd dlink 请求Master读数据
                                                           [3]: voice uplink中断，为1时表示voice uplink请求Master读数据
                                                           [2]: stereo uplink中断，为1时表示voice uplink请求Master读数据
                                                           [1]: stereo dlink中断，为1时表示voice uplink请求Master读数据
                                                           [0]: voice dlink中断，为1时表示voice uplink请求Master送数据 */
        unsigned int  reserved         : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ASP_CODEC_CODEC_IRQ_UNION;
#endif
#define SOC_ASP_CODEC_CODEC_IRQ_codec_data_intrp_START  (0)
#define SOC_ASP_CODEC_CODEC_IRQ_codec_data_intrp_END    (5)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION
 结构说明  : DACL_AGC_CFG_1 寄存器结构定义。地址偏移量:0x4C，初值:0x249AAE51，宽度:32
 寄存器说明: DACL AGC (自动增益控制)配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacl_agc_gwin_config     : 2;  /* bit[0-1]  : AGC立即下调电平窗口增益配置。
                                                                    00：3.5dB；
                                                                    01：5.5dB；
                                                                    10：9dB；
                                                                    11：15dB。 */
        unsigned int  dacl_agc_levellow_config : 2;  /* bit[2-3]  : AGC低电平门限增益配置。
                                                                    00：-60dB；
                                                                    01：-72dB；
                                                                    10：-90dB；
                                                                    11：-120dB； */
        unsigned int  dacl_agc_gstepd_config   : 2;  /* bit[4-5]  : AGC增益下调的步长增益配置。
                                                                    00：0.5dB；
                                                                    01：1dB；
                                                                    10：1.5dB；
                                                                    11：2dB； */
        unsigned int  dacl_agc_timemute_config : 2;  /* bit[6-7]  : AGC静音等待时间配置。
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
        unsigned int  dacl_agc_ngw_config      : 2;  /* bit[8-9]  : AGC噪声判断迟滞增益窗配置。
                                                                    00：0dB；
                                                                    01：1dB；
                                                                    10：2dB；
                                                                    11：4dB。 */
        unsigned int  dacl_agc_ytarget_config  : 3;  /* bit[10-12]: AGC输出信号目标增益幅度配置。
                                                                    000：-4dB；
                                                                    001：-6dB；
                                                                    010：-9dB；
                                                                    011：-12dB；
                                                                    100：-15dB；
                                                                    101：-18dB；
                                                                    110：-21dB；
                                                                    111：-24dB。 */
        unsigned int  dacl_agc_t_amin_config   : 2;  /* bit[13-14]: AGC增益下调的最小时间间隔配置。
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
        unsigned int  dacl_agc_gsuppress       : 1;  /* bit[15]   : AGC增益压缩使能标志配置。
                                                                    0：非压缩；
                                                                    1：压缩。 */
        unsigned int  dacl_agc_kfslow          : 2;  /* bit[16-17]: AGC中包络检测慢速下降速率选择。
                                                                    00：选择1/2^(10)速率；
                                                                    01：选择1/2^(11)速率；
                                                                    10：选择1/2^(12)速率；
                                                                    11：选择1/2^(13)速率。 */
        unsigned int  dacl_agc_kfrapid         : 2;  /* bit[18-19]: AGC中包络检测快速下降速率选择。
                                                                    00：选择1/2^(6)速率；
                                                                    01：选择1/2^(7)速率；
                                                                    10：选择1/2^(8)速率；
                                                                    11：选择1/2^(9)速率。 */
        unsigned int  dacl_agc_ngl_config      : 2;  /* bit[20-21]: AGC噪声阈值最低值配置。
                                                                    00：等于噪声阈值初始值配置；
                                                                    01：等于噪声阈值初始值配置减去6dB；
                                                                    10：等于噪声阈值初始值配置减去18dB；
                                                                    11：等于-90dB。 */
        unsigned int  dacl_agc_ngh_config      : 2;  /* bit[22-23]: AGC噪声阈值最大值配置。
                                                                    00：等于噪声阈值初始值配置；
                                                                    01：等于噪声阈值初始值配置加12dB；
                                                                    10：等于噪声阈值初始值配置加18dB；
                                                                    11：等于-24dB。 */
        unsigned int  dacl_agc_timer           : 3;  /* bit[24-26]: AGC时间选择配置。
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
        unsigned int  dacl_agc_ngi_config      : 3;  /* bit[27-29]: AGC噪声阈值初始值增益配置，增益范围：-72dB~-36dB，步长为6dB。
                                                                    000：-72dB；
                                                                    001：-66dB；
                                                                    010：-60dB；
                                                                    011：-54dB；
                                                                    100：-51dB；
                                                                    101：-48dB；
                                                                    110：-42dB；
                                                                    111：-36dB。 */
        unsigned int  dacl_agc_timenng_config  : 2;  /* bit[30-31]: AGC噪声阈值更新时间配置。
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
    } reg;
} SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gwin_config_START      (0)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gwin_config_END        (1)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_levellow_config_START  (2)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_levellow_config_END    (3)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gstepd_config_START    (4)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gstepd_config_END      (5)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timemute_config_START  (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timemute_config_END    (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngw_config_START       (8)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngw_config_END         (9)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ytarget_config_START   (10)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ytarget_config_END     (12)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_t_amin_config_START    (13)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_t_amin_config_END      (14)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gsuppress_START        (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gsuppress_END          (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfslow_START           (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfslow_END             (17)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfrapid_START          (18)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfrapid_END            (19)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngl_config_START       (20)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngl_config_END         (21)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngh_config_START       (22)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngh_config_END         (23)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timer_START            (24)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timer_END              (26)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngi_config_START       (27)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngi_config_END         (29)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timenng_config_START   (30)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timenng_config_END     (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION
 结构说明  : DACL_AGC_CFG_2 寄存器结构定义。地址偏移量:0x50，初值:0x00000059，宽度:32
 寄存器说明: DACL AGC (自动增益控制)配置寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacl_agc_timedecay_config : 2;  /* bit[0-1]  : AGC每次上调增益的时间间隔配置。
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
        unsigned int  dacl_agc_timeghold_config : 2;  /* bit[2-3]  : AGC增益上调之前的等待时间配置。
                                                                     00：时间选择配置的1/8；
                                                                     01：时间选择配置的1/4；
                                                                     10：时间选择配置的1/2；
                                                                     11：时间选择配置的3/4。 */
        unsigned int  dacl_agc_gmute_config     : 2;  /* bit[4-5]  : AGC静音状态下的增益配置。
                                                                     00：0dB；
                                                                     01：-12dB；
                                                                     10：-24dB；
                                                                     11：-42dB。 */
        unsigned int  dacl_agc_mute_bypass      : 1;  /* bit[6]    : AGC静音功能禁止标志配置。
                                                                     0：AGC Mute使能；
                                                                     1：AGC Mute bypass */
        unsigned int  dacl_agc_bypass           : 1;  /* bit[7]    : AGC功能bypass使能信号。
                                                                     1：AGC功能禁止；
                                                                     0：采用自动增益控制。 */
        unsigned int  dacl_agc_usr_gdb_integer  : 8;  /* bit[8-15] : AGC功能bypass时，用户输入增益配置系数。与dB乘法器一样，为整数位配置。
                                                                     默认：0dB；普通增益调节模块的增益范围：-72dB～+36dB，即：
                                                                     0010_0100：36dB；
                                                                     0010_0011：35dB；
                                                                     ……
                                                                     1011_1000：-72dB。
                                                                     步长为1dB，补码表示。 */
        unsigned int  dacl_agc_usr_gdb_frac     : 1;  /* bit[16]   : DACL AGC用户输入增益小数位配置。
                                                                     0：0.0dB；
                                                                     1：0.5dB。 */
        unsigned int  dacl_agc_sw_clr           : 1;  /* bit[17]   : DACL通道AGC软复位配置。
                                                                     0：无效； 
                                                                     1：复位。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timedecay_config_START  (0)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timedecay_config_END    (1)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timeghold_config_START  (2)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timeghold_config_END    (3)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_gmute_config_START      (4)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_gmute_config_END        (5)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_mute_bypass_START       (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_mute_bypass_END         (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_bypass_START            (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_bypass_END              (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_integer_START   (8)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_integer_END     (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_frac_START      (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_frac_END        (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_sw_clr_START            (17)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_sw_clr_END              (17)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION
 结构说明  : DACR_AGC_CFG_1 寄存器结构定义。地址偏移量:0x54，初值:0x249AAE51，宽度:32
 寄存器说明: DACR AGC (自动增益控制)配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacr_agc_gwin_config     : 2;  /* bit[0-1]  : AGC立即下调电平窗口增益配置。
                                                                    00：3.5dB；
                                                                    01：5.5dB；
                                                                    10：9dB；
                                                                    11：15dB。 */
        unsigned int  dacr_agc_levellow_config : 2;  /* bit[2-3]  : AGC低电平门限增益配置。
                                                                    00：-60dB；
                                                                    01：-72dB；
                                                                    10：-90dB；
                                                                    11：-120dB； */
        unsigned int  dacr_agc_gstepd_config   : 2;  /* bit[4-5]  : AGC增益下调的步长增益配置。
                                                                    00：0.5dB；
                                                                    01：1dB；
                                                                    10：1.5dB；
                                                                    11：2dB； */
        unsigned int  dacr_agc_timemute_config : 2;  /* bit[6-7]  : AGC静音等待时间配置。
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
        unsigned int  dacr_agc_ngw_config      : 2;  /* bit[8-9]  : AGC噪声判断迟滞增益窗配置。
                                                                    00：0dB；
                                                                    01：1dB；
                                                                    10：2dB；
                                                                    11：4dB。 */
        unsigned int  dacr_agc_ytarget_config  : 3;  /* bit[10-12]: AGC输出信号目标增益幅度配置。
                                                                    000：-4dB；
                                                                    001：-6dB；
                                                                    010：-9dB；
                                                                    011：-12dB；
                                                                    100：-15dB；
                                                                    101：-18dB；
                                                                    110：-21dB；
                                                                    111：-24dB。 */
        unsigned int  dacr_agc_t_amin_config   : 2;  /* bit[13-14]: AGC增益下调的最小时间间隔配置。
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
        unsigned int  dacr_agc_gsuppress       : 1;  /* bit[15]   : AGC增益压缩使能标志配置。
                                                                    0：非压缩；
                                                                    1：压缩。 */
        unsigned int  dacr_agc_kfslow          : 2;  /* bit[16-17]: AGC中包络检测慢速下降速率选择。
                                                                    00：选择1/2^(10)速率；
                                                                    01：选择1/2^(11)速率；
                                                                    10：选择1/2^(12)速率；
                                                                    11：选择1/2^(13)速率。 */
        unsigned int  dacr_agc_kfrapid         : 2;  /* bit[18-19]: AGC中包络检测快速下降速率选择。
                                                                    00：选择1/2^(6)速率；
                                                                    01：选择1/2^(7)速率；
                                                                    10：选择1/2^(8)速率；
                                                                    11：选择1/2^(9)速率。 */
        unsigned int  dacr_agc_ngl_config      : 2;  /* bit[20-21]: AGC噪声阈值最低值配置。
                                                                    00：等于噪声阈值初始值配置；
                                                                    01：等于噪声阈值初始值配置减去6dB；
                                                                    10：等于噪声阈值初始值配置减去18dB；
                                                                    11：等于-90dB。 */
        unsigned int  dacr_agc_ngh_config      : 2;  /* bit[22-23]: AGC噪声阈值最大值配置。
                                                                    00：等于噪声阈值初始值配置；
                                                                    01：等于噪声阈值初始值配置加12dB；
                                                                    10：等于噪声阈值初始值配置加18dB；
                                                                    11：等于-24dB。 */
        unsigned int  dacr_agc_timer           : 3;  /* bit[24-26]: AGC时间选择配置。
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
        unsigned int  dacr_agc_ngi_config      : 3;  /* bit[27-29]: AGC噪声阈值初始值增益配置，增益范围：-72dB~-36dB，步长为6dB。
                                                                    000：-72dB；
                                                                    001：-66dB；
                                                                    010：-60dB；
                                                                    011：-54dB；
                                                                    100：-51dB；
                                                                    101：-48dB；
                                                                    110：-42dB；
                                                                    111：-36dB。 */
        unsigned int  dacr_agc_timenng_config  : 2;  /* bit[30-31]: AGC噪声阈值更新时间配置。
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
    } reg;
} SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gwin_config_START      (0)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gwin_config_END        (1)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_levellow_config_START  (2)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_levellow_config_END    (3)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gstepd_config_START    (4)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gstepd_config_END      (5)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timemute_config_START  (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timemute_config_END    (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngw_config_START       (8)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngw_config_END         (9)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ytarget_config_START   (10)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ytarget_config_END     (12)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_t_amin_config_START    (13)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_t_amin_config_END      (14)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gsuppress_START        (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gsuppress_END          (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfslow_START           (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfslow_END             (17)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfrapid_START          (18)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfrapid_END            (19)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngl_config_START       (20)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngl_config_END         (21)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngh_config_START       (22)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngh_config_END         (23)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timer_START            (24)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timer_END              (26)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngi_config_START       (27)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngi_config_END         (29)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timenng_config_START   (30)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timenng_config_END     (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION
 结构说明  : DACR_AGC_CFG_2 寄存器结构定义。地址偏移量:0x58，初值:0x00000059，宽度:32
 寄存器说明: DACR AGC (自动增益控制)配置寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacr_agc_timedecay_config : 2;  /* bit[0-1]  : AGC每次上调增益的时间间隔配置。
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
        unsigned int  dacr_agc_timeghold_config : 2;  /* bit[2-3]  : AGC增益上调之前的等待时间配置。
                                                                     00：时间选择配置的1/8；
                                                                     01：时间选择配置的1/4；
                                                                     10：时间选择配置的1/2；
                                                                     11：时间选择配置的3/4。 */
        unsigned int  dacr_agc_gmute_config     : 2;  /* bit[4-5]  : AGC静音状态下的增益配置。
                                                                     00：0dB；
                                                                     01：-12dB；
                                                                     10：-24dB；
                                                                     11：-42dB。 */
        unsigned int  dacr_agc_mute_bypass      : 1;  /* bit[6]    : AGC静音功能禁止标志配置。
                                                                     0：AGC Mute使能；
                                                                     1：AGC Mute bypass */
        unsigned int  dacr_agc_bypass           : 1;  /* bit[7]    : AGC功能bypass使能信号。
                                                                     1：AGC功能禁止；
                                                                     0：采用自动增益控制。 */
        unsigned int  dacr_agc_usr_gdb_integer  : 8;  /* bit[8-15] : AGC功能bypass时，用户输入增益配置系数。与dB乘法器一样，为整数位配置。
                                                                     默认：0dB；普通增益调节模块的增益范围：-72dB～+36dB，即：
                                                                     0010_0100：36dB；
                                                                     0010_0011：35dB；
                                                                     ……
                                                                     1011_1000：-72dB。
                                                                     步长为1dB，补码表示。 */
        unsigned int  dacr_agc_usr_gdb_frac     : 1;  /* bit[16]   : DACR AGC用户输入增益小数位配置。
                                                                     0：0.0dB；
                                                                     1：0.5dB。 */
        unsigned int  dacr_agc_sw_clr           : 1;  /* bit[17]   : DACR通道AGC软复位配置。
                                                                     0：无效； 
                                                                     1：复位。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timedecay_config_START  (0)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timedecay_config_END    (1)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timeghold_config_START  (2)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timeghold_config_END    (3)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_gmute_config_START      (4)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_gmute_config_END        (5)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_mute_bypass_START       (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_mute_bypass_END         (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_bypass_START            (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_bypass_END              (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_integer_START   (8)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_integer_END     (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_frac_START      (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_frac_END        (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_sw_clr_START            (17)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_sw_clr_END              (17)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_DMIC_SIF_CFG_UNION
 结构说明  : DMIC_SIF_CFG 寄存器结构定义。地址偏移量:0x5C，初值:0x0000000F，宽度:32
 寄存器说明: DMIC接口和Serial接口配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sif_adcl_en      : 1;  /* bit[0]    : SIF ADCL方向使能：
                                                            1：接收串行接口送进来数据
                                                            0：不接收数据 */
        unsigned int  sif_adcr_en      : 1;  /* bit[1]    : SIF ADCR方向使能：
                                                            1：接收串行接口送进来数据
                                                            0：不接收数据 */
        unsigned int  sif_dacl_en      : 1;  /* bit[2]    : SIF DACL方向使能：
                                                            1：向串行接口发送数据
                                                            0：不发送数据 */
        unsigned int  sif_dacr_en      : 1;  /* bit[3]    : SIF DACR方向使能：
                                                            1：向串行接口发送数据
                                                            0：不发送数据 */
        unsigned int  dac_p2s_loopback : 1;  /* bit[4]    : SIF 数据环回：
                                                            1：ADC并行输出环回到DAC的并行输入
                                                            0：不环回 */
        unsigned int  sif_s2p_loopback : 1;  /* bit[5]    : SIF串行输出数据环回使能：
                                                            1：DAC串行输出环回到ADC串行输入
                                                            0：不环回 */
        unsigned int  sif_edge_sel     : 1;  /* bit[6]    : sif模块时钟沿选择：
                                                            1'b1: SIF时钟与输入的49.152M时钟反相
                                                            1'b0: SIF时钟与输入的49.152M时钟同相 */
        unsigned int  sif_en           : 1;  /* bit[7]    : 与smartStar接口使能：
                                                            0：关闭时钟
                                                            1：打开时钟 */
        unsigned int  reserved_0       : 8;  /* bit[8-15] : reserved */
        unsigned int  sw_dmic_mode     : 1;  /* bit[16]   : DMIC声道配置。 
                                                            0：不交换左右声道； 
                                                            1：交换左右声道。 */
        unsigned int  dmic_reverse     : 1;  /* bit[17]   : DMIC输入编码配置。 
                                                            0：0 -> -4, 1 -> +4； 
                                                            1：0 -> +4, 1 -> -4。 */
        unsigned int  fs_dmic          : 2;  /* bit[18-19]: DMIC时钟配置。
                                                            2'b00：关闭时钟；
                                                            2'b01：2分频；
                                                            2'b10：3分频；
                                                            2'b11：4分频。 */
        unsigned int  dmic_en          : 1;  /* bit[20]   : DMIC接口使能：
                                                            0：关闭时钟
                                                            1：打开时钟 */
        unsigned int  reserved_1       : 11; /* bit[21-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DMIC_SIF_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcl_en_START       (0)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcl_en_END         (0)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcr_en_START       (1)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcr_en_END         (1)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacl_en_START       (2)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacl_en_END         (2)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacr_en_START       (3)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacr_en_END         (3)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dac_p2s_loopback_START  (4)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dac_p2s_loopback_END    (4)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_s2p_loopback_START  (5)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_s2p_loopback_END    (5)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_edge_sel_START      (6)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_edge_sel_END        (6)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_en_START            (7)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_en_END              (7)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sw_dmic_mode_START      (16)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sw_dmic_mode_END        (16)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_reverse_START      (17)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_reverse_END        (17)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_fs_dmic_START           (18)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_fs_dmic_END             (19)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_en_START           (20)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_en_END             (20)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_MISC_CFG_UNION
 结构说明  : MISC_CFG 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: Misc Config
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_dout_left_sel                : 1;  /* bit[0]    : S2接口（BT接口）左输出通道输出数据第一级选择，MUX6：
                                                                           1'b1: 选择voice dlink通道pga输出；
                                                                           1'b0: 选择降采样SRC3输出； */
        unsigned int  s1_dout_test_sel                : 1;  /* bit[1]    : S1输出通道数据选择，左右声道均受其控制，MUX8/MUX9：
                                                                           1'b1: 左声道选择adcl数字滤波器通道输出，右声道选择adcr数字滤波器通道输出
                                                                           1'b0: 左声道选择DACL MIXER输出，右声道选择DACR MIXER输出； */
        unsigned int  s2_dout_test_sel                : 1;  /* bit[2]    : S2接口（BT接口）输出通道输出数据第二级选择，改变左声道输出，MUX7：
                                                                           1'b1: 选择DACL MIXER输出；
                                                                           1'b0: 选择功能路径数据（voice dlink pga或者S2降采样输出）； */
        unsigned int  s2_dout_right_sel               : 1;  /* bit[3]    : S2接口（BT接口）右输出通道输出数据选择：
                                                                           1'b1: 0；
                                                                           1'b0: 选择DACR通道Mixer输出； */
        unsigned int  stereo_dlink_test_sel           : 1;  /* bit[4]    : STEREO DLINK通道输入数据选择，MUX11/MUX12：
                                                                           1'b0:来自于APB总线
                                                                           1'b1:S1接口左声道输入stereo_dlink_l ,S1接口右声道输入stereo_dlink_r */
        unsigned int  reserved_0                      : 1;  /* bit[5]    : reserved */
        unsigned int  voice_dlink_din_sel             : 1;  /* bit[6]    : VOICE DLINK通道输入数据选择：
                                                                           1'b0:来自于APB总线
                                                                           1'b1:S3接口输入左声道 */
        unsigned int  voice_dlink_test_sel            : 1;  /* bit[7]    : VOICE DLINK通道输入数据选择，MUX10：
                                                                           1'b0:来自于前级选择输出(取决于voice_dlink_din_sel配置)
                                                                           1'b1:S2接口输入左声道 */
        unsigned int  voice_dlink_src_up_dout_vld_sel : 1;  /* bit[8]    : VOICE下行通道SRC模块输出采样率选择：
                                                                           1'b1: 输出为96kHz
                                                                           1'b0: 输出为48kHz */
        unsigned int  reserved_1                      : 3;  /* bit[9-11] : reserved */
        unsigned int  s3_din_test_sel                 : 1;  /* bit[12]   : s3输入选择：
                                                                           1'b0: 选择Left声道；
                                                                           1'b1: 选择Right声道； */
        unsigned int  s3_dout_left_sel                : 1;  /* bit[13]   : S3接口左输出通道选择信号：
                                                                           1'b0: thirdmd dlink pga输出；
                                                                           1'b1: adcl通道pga输出 */
        unsigned int  s3_dout_right_sel               : 2;  /* bit[14-15]: S3接口右输出通道选择信号：
                                                                           2'b00: thirdmd dlink pga输出；
                                                                           2'b01: adcr通道pga输出;
                                                                           other: 0; */
        unsigned int  thirdmd_dlink_din_sel           : 1;  /* bit[16]   : thirdmd_dlink通道输入数据选择输入：
                                                                           1'b0: APB thirdmd下行通道
                                                                           1'b1: S2左输入声道 */
        unsigned int  thirdmd_dlink_test_sel          : 1;  /* bit[17]   : thirdmd_dlink通道测试数据选择输入：
                                                                           1'b0: 从APB thirdmd下行通道或S2输入中选择
                                                                           1'b1: S3输入 */
        unsigned int  reserved_2                      : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_MISC_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_left_sel_START                 (0)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_left_sel_END                   (0)
#define SOC_ASP_CODEC_MISC_CFG_s1_dout_test_sel_START                 (1)
#define SOC_ASP_CODEC_MISC_CFG_s1_dout_test_sel_END                   (1)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_test_sel_START                 (2)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_test_sel_END                   (2)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_right_sel_START                (3)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_right_sel_END                  (3)
#define SOC_ASP_CODEC_MISC_CFG_stereo_dlink_test_sel_START            (4)
#define SOC_ASP_CODEC_MISC_CFG_stereo_dlink_test_sel_END              (4)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_din_sel_START              (6)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_din_sel_END                (6)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_test_sel_START             (7)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_test_sel_END               (7)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_src_up_dout_vld_sel_START  (8)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_src_up_dout_vld_sel_END    (8)
#define SOC_ASP_CODEC_MISC_CFG_s3_din_test_sel_START                  (12)
#define SOC_ASP_CODEC_MISC_CFG_s3_din_test_sel_END                    (12)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_left_sel_START                 (13)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_left_sel_END                   (13)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_right_sel_START                (14)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_right_sel_END                  (15)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_din_sel_START            (16)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_din_sel_END              (16)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_test_sel_START           (17)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_test_sel_END             (17)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S2_SRC_CFG_UNION
 结构说明  : S2_SRC_CFG 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: S2接口SRC模块配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_il_src_up_en        : 1;  /* bit[0]   : S2接口左输入通道SRC升采样滤波器时能信号：
                                                                 1'b1：时钟使能；
                                                                 1'b0：bypass */
        unsigned int  s2_il_src_down_en      : 1;  /* bit[1]   : S2接口左输入通道SRC降采样滤波器时能信号：
                                                                 1'b1：时钟使能；
                                                                 1'b0：bypass */
        unsigned int  s2_ir_src_up_en        : 1;  /* bit[2]   : S2接口左输入通道SRC升采样滤波器时能信号：
                                                                 1'b1：时钟使能；
                                                                 1'b0：bypass */
        unsigned int  s2_ir_src_down_en      : 1;  /* bit[3]   : S2接口左输入通道SRC降采样滤波器时能信号：
                                                                 1'b1：时钟使能；
                                                                 1'b0：bypass */
        unsigned int  s2_il_src_up_src_rdy   : 1;  /* bit[4]   : S2 I2S接口左输入通道SRC升采样模块READY信号：
                                                                 1'b1:SRC RAM初始化完成
                                                                 1'b0:SRC RAM初始化进行中 */
        unsigned int  s2_il_src_down_src_rdy : 1;  /* bit[5]   : S2 I2S接口左输入通道SRC降采样模块READY信号：
                                                                 1'b1:SRC RAM初始化完成
                                                                 1'b0:SRC RAM初始化进行中 */
        unsigned int  s2_ir_src_up_src_rdy   : 1;  /* bit[6]   : S2 I2S接口右输入通道SRC升采样模块READY信号：
                                                                 1'b1:SRC RAM初始化完成
                                                                 1'b0:SRC RAM初始化进行中 */
        unsigned int  s2_ir_src_down_src_rdy : 1;  /* bit[7]   : S2 I2S接口右输入通道SRC降采样模块READY信号：
                                                                 1'b1:SRC RAM初始化完成
                                                                 1'b0:SRC RAM初始化进行中 */
        unsigned int  reserved               : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S2_SRC_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_en_START         (0)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_en_END           (0)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_en_START       (1)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_en_END         (1)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_en_START         (2)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_en_END           (2)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_en_START       (3)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_en_END         (3)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_src_rdy_START    (4)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_src_rdy_END      (4)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_src_rdy_START  (5)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_src_rdy_END    (5)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_src_rdy_START    (6)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_src_rdy_END      (6)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_src_rdy_START  (7)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_src_rdy_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_MEM_CFG_UNION
 结构说明  : MEM_CFG 寄存器结构定义。地址偏移量:0x68，初值:0x01A800A8，宽度:32
 寄存器说明: memory配置信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s     : 16; /* bit[0-15] : SRC中单口memory控制信号 */
        unsigned int  mem_ctrl_d1w2r : 16; /* bit[16-31]: AFIFO中双口memory控制信号 */
    } reg;
} SOC_ASP_CODEC_MEM_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_s_START      (0)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_s_END        (15)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_d1w2r_START  (16)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_d1w2r_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION
 结构说明  : THIRDMD_PCM_PGA_CFG 寄存器结构定义。地址偏移量:0x6C，初值:0x00000320，宽度:32
 寄存器说明: 第三方modem的I2S
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_func_mode                     : 3;  /* bit[0-2]  : S1接口模式选择：
                                                                            3'b000:I2S
                                                                            3'b010:PCM STD
                                                                            3'b011:PCM USER Defined
                                                                            3'b100:Left Justified
                                                                            3'b101:Right Justified
                                                                            其他：保留 */
        unsigned int  s3_codec_data_format             : 1;  /* bit[3]    : S1接口Codec ADC/DAC数据格式选择。
                                                                            0：表示二进制补码；
                                                                            1：表示二进制码（binary offset）。 */
        unsigned int  s3_rx_clk_sel                    : 1;  /* bit[4]    : S1接口RX方向时钟选择：
                                                                            1'b0:BCLK上升沿接收数据
                                                                            1'b1:BCLK下降沿接收数据 */
        unsigned int  s3_tx_clk_sel                    : 1;  /* bit[5]    : S1接口TX方向时钟选择：
                                                                            1'b0:BCLK上升沿打出数据
                                                                            1'b1:BCLK下降沿打出数据 */
        unsigned int  s3_direct_loop                   : 2;  /* bit[6-7]  : S1 I2S接口环回模式选择。
                                                                            2'b00：正常工作模式；
                                                                            2'b01：Sdin->Sdout。
                                                                            2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                            2'b11: SDOUT -> SDIN */
        unsigned int  s3_codec_io_wordlength           : 2;  /* bit[8-9]  : S1接口位数控制。
                                                                            00：16bit；
                                                                            01：18bit；
                                                                            10：20bit；
                                                                            11：24bit。 */
        unsigned int  s3_chnnl_mode                    : 1;  /* bit[10]   : S1接口声道配置：
                                                                            1'b0:左声道在前
                                                                            1'b1:右声道在前 */
        unsigned int  s3_lrclk_mode                    : 1;  /* bit[11]   : S1接口帧同步信号左右声道选择：
                                                                            1'b0:low -> left channel
                                                                            1'b1:low -> right channel */
        unsigned int  s3_mst_slv                       : 1;  /* bit[12]   : S1接口Master/Slave模式选择：
                                                                            1'b0:Mater模式，在master模式下BCLK/SYNC才可以输出
                                                                            1'b1:Slave模式 */
        unsigned int  s3_frame_mode                    : 1;  /* bit[13]   : S1接口I2S模式下帧格式配置：
                                                                            1'b0:I2S模式下64bit frame，PCM模式下32bit frame
                                                                            1'b1:I2S模式下32bit frame，PCM模式下16bit frame */
        unsigned int  s3_if_rx_ena                     : 1;  /* bit[14]   : S1接口RX方向使能：
                                                                            1'b1:使能
                                                                            1'b0:关闭 */
        unsigned int  s3_if_tx_ena                     : 1;  /* bit[15]   : S1接口TX方向使能：
                                                                            1'b1:使能
                                                                            1'b0:关闭 */
        unsigned int  fs_s3                            : 3;  /* bit[16-18]: S1接口采样率配置
                                                                            0：8KHz； 1：16KHz；
                                                                            2：32KHz； 3：保留
                                                                            4：48KHz； 5：96KHz；
                                                                            6：192KHz；7：保留 */
        unsigned int  reserved                         : 1;  /* bit[19]   : reserved */
        unsigned int  thirdmd_dlink_pga_integer_config : 8;  /* bit[20-27]: 第三方modem下行通道 pga增益控制整数部分:
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
        unsigned int  thirdmd_dlink_pga_frac_config    : 1;  /* bit[28]   : 第三方modem下行通道 pga输入增益小数位配置。
                                                                            0：0.0dB；
                                                                            1：0.5dB。 */
        unsigned int  thirdmd_dlink_pga_mute           : 1;  /* bit[29]   : 第三方modem下行通道 pga mute使能：
                                                                            1'b1: mute有效，输出0
                                                                            1'b0: 关闭mute */
        unsigned int  thirdmd_dlink_pga_thr_config     : 2;  /* bit[30-31]: 第三方modem下行通道 pga过零检测低电平门限配置。 
                                                                            00：-60dB； 
                                                                            01：-72dB； 
                                                                            10：-90dB； 
                                                                            11：-120dB； */
    } reg;
} SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_func_mode_START                      (0)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_func_mode_END                        (2)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_data_format_START              (3)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_data_format_END                (3)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_rx_clk_sel_START                     (4)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_rx_clk_sel_END                       (4)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_tx_clk_sel_START                     (5)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_tx_clk_sel_END                       (5)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_direct_loop_START                    (6)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_direct_loop_END                      (7)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_io_wordlength_START            (8)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_io_wordlength_END              (9)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_chnnl_mode_START                     (10)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_chnnl_mode_END                       (10)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_lrclk_mode_START                     (11)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_lrclk_mode_END                       (11)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_mst_slv_START                        (12)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_mst_slv_END                          (12)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_frame_mode_START                     (13)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_frame_mode_END                       (13)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_rx_ena_START                      (14)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_rx_ena_END                        (14)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_tx_ena_START                      (15)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_tx_ena_END                        (15)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_fs_s3_START                             (16)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_fs_s3_END                               (18)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_integer_config_START  (20)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_integer_config_END    (27)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_frac_config_START     (28)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_frac_config_END       (28)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_mute_START            (29)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_mute_END              (29)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_thr_config_START      (30)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_thr_config_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION
 结构说明  : THIRD_MODEM_FIFO_TH 寄存器结构定义。地址偏移量:0x70，初值:0x0110101E，宽度:32
 寄存器说明: 第三方Modem下行通道AFIFO水线
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_dlink_fifo_afull_th   : 5;  /* bit[0-4]  : Third Modem DLINK通道AFIFO将满阈值，fifo中有效数值个数高于该值时，FIFO almost full信号有效 */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  thirdmd_dlink_fifo_aempty_th  : 5;  /* bit[8-12] : Third Modem DLINK通道AFIFO将空阈值，fifo中有效数值个数低于该值时，FIFO almost empty信号有效 */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  thirdmd_uplink_fifo_afull_th  : 5;  /* bit[16-20]: Third Modem UPLINK右通道AFIFO将满阈值，同上。 */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  thirdmd_uplink_fifo_aempty_th : 5;  /* bit[24-28]: Third Modem UPLINK右通道AFIFO将空阈值，同上。 */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION;
#endif
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_afull_th_START    (0)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_afull_th_END      (4)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_aempty_th_START   (8)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_aempty_th_END     (12)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_aempty_th_END    (28)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION
 结构说明  : S3_ANTI_FREQ_JITTER_TX_INC_CNT 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: S3接口抗频偏模块TX方向计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_inc_cnt : 8;  /* bit[0-7] : S3接口tx方向上溢计数器，读取清除。
                                                        有计数时，表明S3接口TX方向缓存中数据个数到达下水线，需要HiFi插入数据个数，意味着外部时钟快。 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_s3_tx_inc_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_s3_tx_inc_cnt_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION
 结构说明  : S3_ANTI_FREQ_JITTER_TX_DEC_CNT 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: S3接口抗频偏模块TX方向计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_dec_cnt : 8;  /* bit[0-7] : S3接口tx方向下溢计数器，读取清除。
                                                        有计数时，表明S3接口TX方向缓存中数据个数到达上水线，需要HiFi丢弃数据个数，意味着外部时钟慢。 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_s3_tx_dec_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_s3_tx_dec_cnt_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION
 结构说明  : S3_ANTI_FREQ_JITTER_RX_INC_CNT 寄存器结构定义。地址偏移量:0x7C，初值:0x00000000，宽度:32
 寄存器说明: S3接口抗频偏模块RX方向计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_rx_inc_cnt : 8;  /* bit[0-7] : S3接口rx方向上溢计数器，读取清除。
                                                        有计数时，表明S3接口RX方向缓存中数据个数到达上水线，需要HiFi丢弃数据个数，意味着外部时钟快。 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_s3_rx_inc_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_s3_rx_inc_cnt_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION
 结构说明  : S3_ANTI_FREQ_JITTER_RX_DEC_CNT 寄存器结构定义。地址偏移量:0x80，初值:0x00000000，宽度:32
 寄存器说明: S3接口抗频偏模块RX方向计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_rx_dec_cnt : 8;  /* bit[0-7] : S3接口rx方向下溢计数器，读取清除。
                                                        有计数时，表明S3接口RX方向缓存中数据个数到达下水线，需要HiFi插入数据个数，意味着外部时钟慢。 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_s3_rx_dec_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_s3_rx_dec_cnt_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION
 结构说明  : ANTI_FREQ_JITTER_EN 寄存器结构定义。地址偏移量:0x84，初值:0x00000000，宽度:32
 寄存器说明: 抗频偏模块使能使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_anti_freq_jitter_en : 1;  /* bit[0]   : S3接口TX方向ANTI_FREQ_JITTER模块使能 */
        unsigned int  s3_rx_anti_freq_jitter_en : 1;  /* bit[1]   : S3接口RX方向ANTI_FREQ_JITTER模块使能 */
        unsigned int  reserved                  : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION;
#endif
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_tx_anti_freq_jitter_en_START  (0)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_tx_anti_freq_jitter_en_END    (0)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_rx_anti_freq_jitter_en_START  (1)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_rx_anti_freq_jitter_en_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_CLK_SEL_UNION
 结构说明  : CLK_SEL 寄存器结构定义。地址偏移量:0x88，初值:0x00000000，宽度:32
 寄存器说明: 12.288M时钟来源选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  external_12288k_sel : 1;  /* bit[0-0]  : 外部12.288M时钟选择：
                                                               1'b1: 选择片外送入的，12.288M时钟
                                                               1'b0: 选择内部分频产生的12.288M时钟 */
        unsigned int  i2s_bt_fm_sel       : 1;  /* bit[1-1]  : I2S接口复用选择：
                                                               1'b0: 给BT I2S(S2)用;
                                                               1'b1: 给FM I2S(S1)用. */
        unsigned int  reserved            : 14; /* bit[2-15] : reserved */
        unsigned int  dig_rw_01           : 16; /* bit[16-31]: dig_rw_01 */
    } reg;
} SOC_ASP_CODEC_CLK_SEL_UNION;
#endif
#define SOC_ASP_CODEC_CLK_SEL_external_12288k_sel_START  (0)
#define SOC_ASP_CODEC_CLK_SEL_external_12288k_sel_END    (0)
#define SOC_ASP_CODEC_CLK_SEL_i2s_bt_fm_sel_START        (1)
#define SOC_ASP_CODEC_CLK_SEL_i2s_bt_fm_sel_END          (1)
#define SOC_ASP_CODEC_CLK_SEL_dig_rw_01_START            (16)
#define SOC_ASP_CODEC_CLK_SEL_dig_rw_01_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION
 结构说明  : UPLINK_TEST_SEL 寄存器结构定义。地址偏移量:0x8C，初值:0x00000000，宽度:32
 寄存器说明: 下行通路到上行通路还回选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_r_test_sel  : 1;  /* bit[0]   : Stereo_Right下行通道到上行通道还回选择
                                                                    1'b0: 选择“ADCR通道输出数据”或“S1接口输入右声道”;
                                                                    1'b1: 选择从sstereo_right_dnlink到stereo_right_uplink的还回通道; */
        unsigned int  stereo_uplink_l_test_sel  : 1;  /* bit[1]   : Stereo_Left下行通道到上行通道还回选择
                                                                    1'b0: 选择“ADCL通道输出数据”或“S1接口输入左声道”;
                                                                    1'b1: 选择从stereo_left_dnlink到stereo_left_uplink的还回通道; */
        unsigned int  voice_uplink_l_test_sel   : 1;  /* bit[2]   : Voice下行通道到上行通道还回选择
                                                                    1'b0: 选择“ADCL通道输出数据”或“S2接口输入左声道”;
                                                                    1'b1: 选择从voice_left_dnlink到voice_left_uplink的还回通道; */
        unsigned int  thirdmd_uplink_l_test_sel : 1;  /* bit[3]   : 第三方Modem下行通道到上行通道还回选择
                                                                    1'b0: 选择“S3接口输入数据”或“S1接口输入左声道”；
                                                                    1'b1: 选择thirdmd_dnlink到thirdmd_uplink的还回通道； */
        unsigned int  smart_pa_fb_sel           : 1;  /* bit[4]   : SmartPA反馈通路选择
                                                                    1'b0: 选择S3接口输入数据;
                                                                    1'b1: 选择S1接口输入左声道； */
        unsigned int  reserved                  : 27; /* bit[5-31]: reserved */
    } reg;
} SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION;
#endif
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_r_test_sel_START   (0)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_r_test_sel_END     (0)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_l_test_sel_START   (1)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_l_test_sel_END     (1)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_voice_uplink_l_test_sel_START    (2)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_voice_uplink_l_test_sel_END      (2)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_thirdmd_uplink_l_test_sel_START  (3)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_thirdmd_uplink_l_test_sel_END    (3)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_smart_pa_fb_sel_START            (4)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_smart_pa_fb_sel_END              (4)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION
 结构说明  : THIRDMD_DLINK_CHANNEL 寄存器结构定义。地址偏移量:0xE8，初值:0x00000000，宽度:32
 寄存器说明: 第三方Modem下行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_dlink_wdata : 32; /* bit[0-31]: 第三方Modem下行通道 */
    } reg;
} SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_thirdmd_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_thirdmd_dlink_wdata_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION
 结构说明  : THIRDMD_UPLINK_CHANNEL 寄存器结构定义。地址偏移量:0xEC，初值:0x00000000，宽度:32
 寄存器说明: 第三方Modem上行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_uplink_rdata : 32; /* bit[0-31]: 第三方Modem上行通道 */
    } reg;
} SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_thirdmd_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_thirdmd_uplink_rdata_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION
 结构说明  : VOICE_DLINK_CHANNEL 寄存器结构定义。地址偏移量:0xF0，初值:0x00000000，宽度:32
 寄存器说明: VOICE下行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_wdata : 32; /* bit[0-31]: VOICE下行通道 */
    } reg;
} SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_voice_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_voice_dlink_wdata_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION
 结构说明  : STEREO_DLINK_CHANNEL 寄存器结构定义。地址偏移量:0xF4，初值:0x00000000，宽度:32
 寄存器说明: 音频下行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_wdata : 32; /* bit[0-31]: 左右声道交替进行操作 */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_stereo_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_stereo_dlink_wdata_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION
 结构说明  : STEREO_UPLINK_CHANNEL 寄存器结构定义。地址偏移量:0xF8，初值:0x00000000，宽度:32
 寄存器说明: 音频上行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_rdata : 32; /* bit[0-31]: 左右声道交替进行操作 */
    } reg;
} SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_stereo_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_stereo_uplink_rdata_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION
 结构说明  : VOICE_UPLINK_CHANNEL 寄存器结构定义。地址偏移量:0xFC，初值:0x00000000，宽度:32
 寄存器说明: VOICE上行通道
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_uplink_rdata : 32; /* bit[0-31]: 左右声道交替进行操作 */
    } reg;
} SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_voice_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_voice_uplink_rdata_END    (31)






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

#endif /* end of soc_asp_codec_interface.h */
