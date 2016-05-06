/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asp_hdmi_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASP_HDMI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_HDMI_INTERFACE_H__
#define __SOC_ASP_HDMI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：发送通道TX3控制寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_TX3_UNION */
#define SOC_ASP_HDMI_ASP_TX3_ADDR(base)               ((base) + (0x000))

/* 寄存器说明：ASP DMA使能寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_DER_UNION */
#define SOC_ASP_HDMI_ASP_DER_ADDR(base)               ((base) + (0x004))

/* 寄存器说明：ASP DMA停止使能寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_DSTOP_UNION */
#define SOC_ASP_HDMI_ASP_DSTOP_ADDR(base)             ((base) + (0x008))

/* 寄存器说明：ASP全局中断状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_ASS_ISR_UNION */
#define SOC_ASP_HDMI_ASP_ASS_ISR_ADDR(base)           ((base) + (0x00C))

/* 寄存器说明：ASP原始状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_IRSR_UNION */
#define SOC_ASP_HDMI_ASP_IRSR_ADDR(base)              ((base) + (0x010))

/* 寄存器说明：ASP中断使能寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_IER_UNION */
#define SOC_ASP_HDMI_ASP_IER_ADDR(base)               ((base) + (0x014))

/* 寄存器说明：ASP屏蔽后状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_IMSR_UNION */
#define SOC_ASP_HDMI_ASP_IMSR_ADDR(base)              ((base) + (0x018))

/* 寄存器说明：ASP中断清零寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_ICR_UNION */
#define SOC_ASP_HDMI_ASP_ICR_ADDR(base)               ((base) + (0x01C))

/* 寄存器说明：通道新歌起始寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_PCMNSSR_UNION */
#define SOC_ASP_HDMI_ASP_PCMNSSR_ADDR(base)           ((base) + (0x020))

/* 寄存器说明：PCM3通道0声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P30CGR_UNION */
#define SOC_ASP_HDMI_ASP_P30CGR_ADDR(base)            ((base) + (0x028))

/* 寄存器说明：PCM3通道1声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P31CGR_UNION */
#define SOC_ASP_HDMI_ASP_P31CGR_ADDR(base)            ((base) + (0x02C))

/* 寄存器说明：PCM3通道2声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P32CGR_UNION */
#define SOC_ASP_HDMI_ASP_P32CGR_ADDR(base)            ((base) + (0x030))

/* 寄存器说明：PCM3通道3声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P33CGR_UNION */
#define SOC_ASP_HDMI_ASP_P33CGR_ADDR(base)            ((base) + (0x034))

/* 寄存器说明：PCM3通道4声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P34CGR_UNION */
#define SOC_ASP_HDMI_ASP_P34CGR_ADDR(base)            ((base) + (0x038))

/* 寄存器说明：PCM3通道5声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P35CGR_UNION */
#define SOC_ASP_HDMI_ASP_P35CGR_ADDR(base)            ((base) + (0x03C))

/* 寄存器说明：PCM3通道6声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P36CGR_UNION */
#define SOC_ASP_HDMI_ASP_P36CGR_ADDR(base)            ((base) + (0x040))

/* 寄存器说明：PCM3通道7声道增益寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P37CGR_UNION */
#define SOC_ASP_HDMI_ASP_P37CGR_ADDR(base)            ((base) + (0x044))

/* 寄存器说明：PCM3A通道搬运起始地址寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3ASAR_UNION */
#define SOC_ASP_HDMI_ASP_P3ASAR_ADDR(base)            ((base) + (0x048))

/* 寄存器说明：PCM3A通道搬运长度寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3ADLR_UNION */
#define SOC_ASP_HDMI_ASP_P3ADLR_ADDR(base)            ((base) + (0x04C))

/* 寄存器说明：PCM3B通道搬运起始地址寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3BSAR_UNION */
#define SOC_ASP_HDMI_ASP_P3BSAR_ADDR(base)            ((base) + (0x050))

/* 寄存器说明：PCM3B通道搬运长度寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3BDLR_UNION */
#define SOC_ASP_HDMI_ASP_P3BDLR_ADDR(base)            ((base) + (0x054))

/* 寄存器说明：混音数据播放接口选择寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_SPDIFSEL_UNION */
#define SOC_ASP_HDMI_ASP_SPDIFSEL_ADDR(base)          ((base) + (0x058))

/* 寄存器说明：DMA停止时PCM3A通道搬运长度状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3ADLS_UNION */
#define SOC_ASP_HDMI_ASP_P3ADLS_ADDR(base)            ((base) + (0x05C))

/* 寄存器说明：DMA停止时PCM3B通道搬运长度状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3BDLS_UNION */
#define SOC_ASP_HDMI_ASP_P3BDLS_ADDR(base)            ((base) + (0x060))

/* 寄存器说明：DMA搬运数据缓存FIFO状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_FDS_UNION */
#define SOC_ASP_HDMI_ASP_FDS_ADDR(base)               ((base) + (0x064))

/* 寄存器说明：PCM3A通道DMA搬运剩余长度状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3ADL_UNION */
#define SOC_ASP_HDMI_ASP_P3ADL_ADDR(base)             ((base) + (0x068))

/* 寄存器说明：PCM3B通道DMA搬运剩余长度状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_P3BDL_UNION */
#define SOC_ASP_HDMI_ASP_P3BDL_ADDR(base)             ((base) + (0x06C))

/* 寄存器说明：ASP_HDMI模块安全寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_ASP_SECURE_UNION */
#define SOC_ASP_HDMI_ASP_SECURE_ADDR(base)            ((base) + (0x070))

/* 寄存器说明：MIXCTL寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_RESERVED1_UNION */
#define SOC_ASP_HDMI_RESERVED1_ADDR(base)             ((base) + (0x074))

/* 寄存器说明：SIO1音频接口选择寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION */
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_ADDR(base)        ((base) + (0x400))

/* 寄存器说明：SIO1中断原始状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_RAW_INT_UNION */
#define SOC_ASP_HDMI_SIO1_RAW_INT_ADDR(base)          ((base) + (0x408))

/* 寄存器说明：SIO1中断清零寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_INT_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_INT_CLR_ADDR(base)          ((base) + (0x40C))

/* 寄存器说明：SIO1中断使能寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION */
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_ADDR(base)       ((base) + (0x410))

/* 寄存器说明：SIO1中断屏蔽后状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION */
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_ADDR(base) ((base) + (0x414))

/* 寄存器说明：SIO1 I2S模式设置
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_I2S_SET_UNION */
#define SOC_ASP_HDMI_SIO1_I2S_SET_ADDR(base)          ((base) + (0x41C))

/* 寄存器说明：SIO1 I2S模式设置清除
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_I2S_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_I2S_CLR_ADDR(base)          ((base) + (0x420))

/* 寄存器说明：SIO1 发送通道状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TX_STA_UNION */
#define SOC_ASP_HDMI_SIO1_TX_STA_ADDR(base)           ((base) + (0x42C))

/* 寄存器说明：SIO1中fifo清零寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_CLR_ADDR(base)              ((base) + (0x438))

/* 寄存器说明：SIO1发送0声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_ADDR(base)     ((base) + (0x440))

/* 寄存器说明：SIO1发送1声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_ADDR(base)     ((base) + (0x444))

/* 寄存器说明：SIO1发送2声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_ADDR(base)     ((base) + (0x448))

/* 寄存器说明：SIO1发送3声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_ADDR(base)     ((base) + (0x44C))

/* 寄存器说明：SIO1发送4声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_ADDR(base)     ((base) + (0x450))

/* 寄存器说明：SIO1发送5声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_ADDR(base)     ((base) + (0x454))

/* 寄存器说明：SIO1发送6声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_ADDR(base)     ((base) + (0x458))

/* 寄存器说明：SIO1发送7声道测试数据
   位域定义UNION结构:  SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_ADDR(base)     ((base) + (0x45C))

/* 寄存器说明：SPDIF控制寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CTRL_UNION */
#define SOC_ASP_HDMI_SPDIF_CTRL_ADDR(base)            ((base) + (0x800))

/* 寄存器说明：SPDIF配置寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CONFIG_UNION */
#define SOC_ASP_HDMI_SPDIF_CONFIG_ADDR(base)          ((base) + (0x804))

/* 寄存器说明：SPDIF屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_INTRUPT_UNION */
#define SOC_ASP_HDMI_SPDIF_INTRUPT_ADDR(base)         ((base) + (0x808))

/* 寄存器说明：SPDIF中断屏蔽寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION */
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_ADDR(base)       ((base) + (0x80C))

/* 寄存器说明：SPDIF FIFO状态寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION */
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_ADDR(base)      ((base) + (0x810))

/* 寄存器说明：信道状态信息寄存器1
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ADDR(base)      ((base) + (0x820))

/* 寄存器说明：信道状态信息寄存器2
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ADDR(base)      ((base) + (0x824))

/* 寄存器说明：信道状态信息寄存器3
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ADDR(base)      ((base) + (0x828))

/* 寄存器说明：信道状态信息寄存器4
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ADDR(base)      ((base) + (0x82C))

/* 寄存器说明：信道状态信息寄存器5
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ADDR(base)      ((base) + (0x830))

/* 寄存器说明：用户数据寄存器1
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_ADDR(base)      ((base) + (0x840))

/* 寄存器说明：用户数据寄存器2
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_ADDR(base)      ((base) + (0x844))

/* 寄存器说明：用户数据寄存器3
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_ADDR(base)      ((base) + (0x848))

/* 寄存器说明：用户数据寄存器4
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_ADDR(base)      ((base) + (0x84C))

/* 寄存器说明：用户数据寄存器5
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_ADDR(base)      ((base) + (0x850))

/* 寄存器说明：版本信息寄存器
   位域定义UNION结构:  SOC_ASP_HDMI_SPDIF_EDITION_UNION */
#define SOC_ASP_HDMI_SPDIF_EDITION_ADDR(base)         ((base) + (0x8F0))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_TX3_UNION
 结构说明  : ASP_TX3 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 发送通道TX3控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3en                 : 1;  /* bit[0]    : TX3通道使能。
                                                                  0：不使能；
                                                                  1：使能。 */
        unsigned int  pcm3ge                 : 1;  /* bit[1]    : TX3通道增益使能。
                                                                  0：不使能；
                                                                  1：使能。 */
        unsigned int  pcm3tsen               : 1;  /* bit[2]    : TX3 透传使能。
                                                                  0：不使能；
                                                                  1：使能。 */
        unsigned int  pcm3_data_in_width     : 3;  /* bit[3-5]  : TX3通道音频数据位宽选择。
                                                                  000－16bit；
                                                                  001－18bit；
                                                                  010－20bit；
                                                                  011－24bit；
                                                                  100－8bit。 */
        unsigned int  pcm3_halfword_align_en : 1;  /* bit[6]    : TX3 16位字对齐使能。
                                                                  0：不使能，32位字对齐；
                                                                  1：使能，16位字对齐。
                                                                  注意：音频数据位宽为8bit时，只支持16位字对齐；
                                                                  音频数据位宽为18bit、20bit、24bit时，只支持32位字对齐。 */
        unsigned int  pcm3_ch_num            : 3;  /* bit[7-9]  : TX3通道声道数目选择。
                                                                  000－1声道；
                                                                  001－2声道；
                                                                  010－3声道；
                                                                  011－4声道；
                                                                  100－5声道；
                                                                  101－6声道；
                                                                  110－7声道；
                                                                  111－8声道。
                                                                  注意：音频数据位宽为8bit时，声道数目只能选择1声道或2声道；
                                                                  音频数据位宽为16bit时，声道数目可选1声道、2声道、4声道、6声道、8声道；
                                                                  音频数据位宽为18bit、20bit、24bit时，声道数目可选2声道、4声道、6声道、8声道。 */
        unsigned int  pcm3_8bit_usymb        : 1;  /* bit[10]   : TX3 8bit数据的符号支持。
                                                                  0：有符号数；
                                                                  1：无符号数。 */
        unsigned int  pcm3_big_endian        : 1;  /* bit[11]   : TX3通道音频数据大小端选择。
                                                                  0：小端；
                                                                  1：大端。
                                                                  注意：只有两种情况支持大小端可配：8bit位宽的音频、16位字对齐的单声道16bit位宽的音频。 */
        unsigned int  pcm3_switch_order      : 1;  /* bit[12]   : TX3通道音频数据声道顺序交换使能。
                                                                  0：不使能声道顺序交换；
                                                                  1：0和1声道数据交换，2和3声道数据交换，4和5声道数据交换，6和7声道数据交换。 */
        unsigned int  reserved               : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_TX3_UNION;
#endif
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_START                  (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_END                    (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_START                  (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_END                    (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_START                (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_END                  (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_START      (3)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_END        (5)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_START  (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_END    (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_START             (7)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_END               (9)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_START         (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_END           (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_START         (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_END           (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_START       (12)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_END         (12)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_DER_UNION
 结构说明  : ASP_DER 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: ASP DMA使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3ade  : 1;  /* bit[0]   : PCM3通道A组DMA使能。
                                                   0：DMA不使能；
                                                   1：DMA使能。
                                                   注意：该寄存器软件写“1”，硬件清零，软件写“0”无效。 */
        unsigned int  pcm3bde  : 1;  /* bit[1]   : PCM3通道B组DMA使能。
                                                   0：DMA不使能；
                                                   1：DMA使能。
                                                   注意：该寄存器软件写“1”，硬件清零，软件写“0”无效。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_DER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_START   (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_END     (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_START   (1)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_END     (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_DSTOP_UNION
 结构说明  : ASP_DSTOP 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: ASP DMA停止使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3ads  : 1;  /* bit[0]   : PCM3通道A组DMA停止使能。
                                                   0：DMA停止不使能；
                                                   1：DMA停止。
                                                   注意：该寄存器软件写“1”，硬件清零，软件写“0”无效。 */
        unsigned int  pcm3bds  : 1;  /* bit[1]   : PCM3通道B组DMA停止使能。
                                                   0：DMA停止不使能；
                                                   1：DMA停止。
                                                   注意：该寄存器软件写“1”，硬件清零，软件写“0”无效。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_DSTOP_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_START   (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_END     (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_START   (1)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_END     (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_ASS_ISR_UNION
 结构说明  : ASP_ASS_ISR 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: ASP全局中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1is   : 1;  /* bit[0]   : 音频SIO1接口部分模块中断状态。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  spdifis  : 1;  /* bit[1]   : 音频SPDIF接口部分模块中断状态。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  aspis    : 1;  /* bit[2]   : ASP部分模块中断状态。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_ASS_ISR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_START    (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_END      (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_START   (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_END     (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_START     (2)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_END       (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_IRSR_UNION
 结构说明  : ASP_IRSR 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: ASP原始状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfirs : 1;  /* bit[0]   : PCM3通道A组DMA结束原始中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  p3bdfirs : 1;  /* bit[1]   : PCM3通道B组DMA结束原始中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  aberirs  : 1;  /* bit[2]   : ASP模块总线error响应原始中断。
                                                   0：无中断；
                                                   1：有中断。
                                                   注意：ASP的AHB master发出总线访问请求，总线上的Slave返回HRESP响应类型为ERROR时，产生该中断。例如，向RO类型地址作写操作等。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_IRSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_START  (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_END    (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_START  (1)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_END    (1)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_START   (2)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_END     (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_IER_UNION
 结构说明  : ASP_IER 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: ASP中断使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfie  : 1;  /* bit[0]   : PCM3通道A组DMA结束中断使能。
                                                   0：不使能；
                                                   1：使能。 */
        unsigned int  p3bdfie  : 1;  /* bit[1]   : PCM3通道B组DMA结束中断使能。
                                                   0：不使能；
                                                   1：使能。 */
        unsigned int  aberie   : 1;  /* bit[2]   : ASP模块总线error响应中断使能。
                                                   0：不使能；
                                                   1：使能。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_IER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IER_p3adfie_START   (0)
#define SOC_ASP_HDMI_ASP_IER_p3adfie_END     (0)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_START   (1)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_END     (1)
#define SOC_ASP_HDMI_ASP_IER_aberie_START    (2)
#define SOC_ASP_HDMI_ASP_IER_aberie_END      (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_IMSR_UNION
 结构说明  : ASP_IMSR 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: ASP屏蔽后状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfims : 1;  /* bit[0]   : PCM3通道A组DMA结束屏蔽后中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  p3bdfims : 1;  /* bit[1]   : PCM3通道B组DMA结束屏蔽后中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  aberims  : 1;  /* bit[2]   : ASP模块总线error响应屏蔽后中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_IMSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_START  (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_END    (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_START  (1)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_END    (1)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_START   (2)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_END     (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_ICR_UNION
 结构说明  : ASP_ICR 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: ASP中断清零寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adficr : 1;  /* bit[0]   : PCM3通道A组DMA结束中断清零。
                                                   0：不清零；
                                                   1：清零。
                                                   注意：该寄存器软件写“1”才能清中断，软件写“0”无效。 */
        unsigned int  p3bdficr : 1;  /* bit[1]   : PCM3通道B组DMA结束中断清零。
                                                   0：不清零；
                                                   1：清零。
                                                   注意：该寄存器软件写“1”才能清中断，软件写“0”无效。 */
        unsigned int  abericr  : 1;  /* bit[2]   : ASP模块总线error响应中断清零。
                                                   0：不清零；
                                                   1：清零。
                                                   注意：该寄存器软件写“1”才能清中断，软件写“0”无效。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_ICR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_START  (0)
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_END    (0)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_START  (1)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_END    (1)
#define SOC_ASP_HDMI_ASP_ICR_abericr_START   (2)
#define SOC_ASP_HDMI_ASP_ICR_abericr_END     (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_PCMNSSR_UNION
 结构说明  : ASP_PCMNSSR 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 通道新歌起始寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3dsr    : 1;  /* bit[0]   : PCM3通道新歌起始。
                                                   0：无效；
                                                   1：新歌起始。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_PCMNSSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_START     (0)
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_END       (0)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P30CGR_UNION
 结构说明  : ASP_P30CGR 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道0声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p30cgr   : 16; /* bit[0-15] : PCM3通道0声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P30CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P31CGR_UNION
 结构说明  : ASP_P31CGR 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道1声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p31cgr   : 16; /* bit[0-15] : PCM3通道1声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P31CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P32CGR_UNION
 结构说明  : ASP_P32CGR 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道2声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p32cgr   : 16; /* bit[0-15] : PCM3通道2声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P32CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P33CGR_UNION
 结构说明  : ASP_P33CGR 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道3声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p33cgr   : 16; /* bit[0-15] : PCM3通道3声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P33CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P34CGR_UNION
 结构说明  : ASP_P34CGR 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道4声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p34cgr   : 16; /* bit[0-15] : PCM3通道4声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P34CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P35CGR_UNION
 结构说明  : ASP_P35CGR 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道5声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p35cgr   : 16; /* bit[0-15] : PCM3通道5声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P35CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P36CGR_UNION
 结构说明  : ASP_P36CGR 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道6声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p36cgr   : 16; /* bit[0-15] : PCM3通道6声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P36CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P37CGR_UNION
 结构说明  : ASP_P37CGR 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: PCM3通道7声道增益寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p37cgr   : 16; /* bit[0-15] : PCM3通道7声道增益大小设置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P37CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_END      (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3ASAR_UNION
 结构说明  : ASP_P3ASAR 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: PCM3A通道搬运起始地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3asar : 32; /* bit[0-31]: PCM3通道A组DMA起始地址。
                                                 注意：bit[1:0]必须配置为2'b0，推荐bit[3:0]配置为4'h0。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3ASAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_START  (0)
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3ADLR_UNION
 结构说明  : ASP_P3ADLR 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: PCM3A通道搬运长度寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adlr   : 20; /* bit[0-19] : PCM3通道A组DMA长度，以字节为单位。
                                                    注意：bit[4:0]必须配置为5'b0。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_START    (0)
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_END      (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3BSAR_UNION
 结构说明  : ASP_P3BSAR 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: PCM3B通道搬运起始地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bsar : 32; /* bit[0-31]: PCM3通道B组DMA起始地址。
                                                 注意：bit[1:0]必须配置为2'b0，推荐bit[3:0]配置为4'h0。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3BSAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_START  (0)
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3BDLR_UNION
 结构说明  : ASP_P3BDLR 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: PCM3B通道搬运长度寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdlr   : 20; /* bit[0-19] : PCM3通道B组DMA长度，以字节为单位。
                                                    注意：bit[4:0]必须配置为5'b0。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_START    (0)
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_END      (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_SPDIFSEL_UNION
 结构说明  : ASP_SPDIFSEL 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 混音数据播放接口选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdifsel : 1;  /* bit[0]   : 混音播放接口选择。
                                                   0：HDMI接口；
                                                   1：SPDIF接口。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_SPDIFSEL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_START  (0)
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3ADLS_UNION
 结构说明  : ASP_P3ADLS 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: DMA停止时PCM3A通道搬运长度状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adls   : 20; /* bit[0-19] : PCM3通道A组DMA停止使能时，剩余未完成搬运的DMA长度信息，单位为字节。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_START    (0)
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_END      (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3BDLS_UNION
 结构说明  : ASP_P3BDLS 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: DMA停止时PCM3B通道搬运长度状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdls   : 20; /* bit[0-19] : PCM3通道B组DMA停止使能时，剩余未完成搬运的DMA长度信息，单位为字节。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_START    (0)
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_END      (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_FDS_UNION
 结构说明  : ASP_FDS 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: DMA搬运数据缓存FIFO状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3_fds : 6;  /* bit[0-5] : PCM3通道DMA搬运数据缓存FIFO深度状态信息。 */
        unsigned int  reserved : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_FDS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_START  (0)
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_END    (5)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3ADL_UNION
 结构说明  : ASP_P3ADL 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: PCM3A通道DMA搬运剩余长度状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adl    : 20; /* bit[0-19] : PCM3通道A组DMA剩余未搬运的DMA长度信息，单位为字节。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_START     (0)
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_END       (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_P3BDL_UNION
 结构说明  : ASP_P3BDL 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: PCM3B通道DMA搬运剩余长度状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdl    : 20; /* bit[0-19] : PCM3通道B组DMA剩余未搬运的DMA长度信息，单位为字节。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_START     (0)
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_END       (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_ASP_SECURE_UNION
 结构说明  : ASP_SECURE 寄存器结构定义。地址偏移量:0x070，初值:0x00000003，宽度:32
 寄存器说明: ASP_HDMI模块安全寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_secure_en_n      : 1;  /* bit[0]   : asp处于安全状态的使能寄存器，低有效，只能由安全处理器配置 */
        unsigned int  asp_addr_secure_en_n : 1;  /* bit[1]   : asp dma地址处于安全状态的使能寄存器，低有效，只能由安全处理器配置 */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_ASP_SECURE_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_START       (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_END         (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_START  (1)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_RESERVED1_UNION
 结构说明  : RESERVED1 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: MIXCTL寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 2;  /* bit[0-1] :  */
        unsigned int  reserved_1: 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_HDMI_RESERVED1_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION
 结构说明  : SIO1_ASPIF_SEL 寄存器结构定义。地址偏移量:0x400，初值:0x00000001，宽度:32
 寄存器说明: SIO1音频接口选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  access_ctrl : 1;  /* bit[0]   : SIO1测试模式选择。
                                                      0：测试模式，测试模式下CPU可读取发送和接收FIFO中的数据；
                                                      1：正常功能模式。
                                                      注意：正常应用时，该寄存器必须写“1”，不能写“0”。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_START  (0)
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_RAW_INT_UNION
 结构说明  : SIO1_RAW_INT 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: SIO1中断原始状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   :  */
        unsigned int  tx_int   : 1;  /* bit[1]   : SIO1发送中断。
                                                   0：无中断；
                                                   1：有中断。
                                                   注意：发送FIFO中剩余数据低于水线时产生中断，SIO1_INT_CLR寄存器对应位写1时中断清零。 */
        unsigned int  reserved_1: 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_RAW_INT_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_START    (1)
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_END      (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_INT_CLR_UNION
 结构说明  : SIO1_INT_CLR 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: SIO1中断清零寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0 : 1;  /* bit[0]   :  */
        unsigned int  tx_int_clr : 1;  /* bit[1]   : SIO1发送中断清零。
                                                     0：无效；
                                                     1：清零tx_int。
                                                     注意：该寄存器软件写“1”才能清中断，软件写“0”无效。 */
        unsigned int  reserved_1 : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION
 结构说明  : SIO1_INT_ENABLE 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: SIO1中断使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0]   :  */
        unsigned int  tx_int_enable : 1;  /* bit[1]   : 发送中断使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  reserved_1    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION
 结构说明  : SIO1_INT_MASKED_STATUS 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: SIO1中断屏蔽后状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 1;  /* bit[0]   :  */
        unsigned int  tx_int_mask : 1;  /* bit[1]   : 中断屏蔽后的发送通道中断。
                                                      0：无中断；
                                                      1：有中断。
                                                      注意：SIO1_INT_CLR寄存器对应位写1时中断清零。 */
        unsigned int  reserved_1  : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_I2S_SET_UNION
 结构说明  : SIO1_I2S_SET 寄存器结构定义。地址偏移量:0x41C，初值:0x0008000C，宽度:32
 寄存器说明: SIO1 I2S模式设置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 2;  /* bit[0-1]  :  */
        unsigned int  tx_ws_sel         : 1;  /* bit[2]    : 发送同步信号选择。
                                                             1：选择外部同步；
                                                             0：无变化。
                                                             注意：1、只支持外部时钟，该位只能写“1”，禁止写“0”。2、配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  tx_clk_sel        : 1;  /* bit[3]    : 发送时钟选择。
                                                             1：选择外部时钟；
                                                             0：无变化。
                                                             注意：1、只支持外部时钟，该位只能写“1”，禁止写“0”。2、配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  tx_fifo_threshold : 5;  /* bit[4-8]  : 发送FIFO阈值，实际值等于设置值加1。
                                                             注意：配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  reserved_1        : 5;  /* bit[9-13] :  */
        unsigned int  tx_fifo_disable   : 1;  /* bit[14]   : 发送FIFO Disable。禁止FIFO时，不使用FIFO缓存发送数据，FIFO被旁路。
                                                             0：不禁止；
                                                             1：禁止。
                                                             注意：1、正常应用时，该位推荐配置为“0”。2、配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  reserved_2        : 1;  /* bit[15]   :  */
        unsigned int  tx_enable         : 1;  /* bit[16]   : 发送通道使能。
                                                             0：不使能；
                                                             1：使能。
                                                             注意：配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  reserved_3        : 1;  /* bit[17]   :  */
        unsigned int  dsp_mode          : 1;  /* bit[18]   : 该位只能写“0”，禁止写“1”。
                                                             注意：配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  tx_rx_reset_n     : 1;  /* bit[19]   : 该位只能写“1”，禁止写“0”。
                                                             注意：配置前必须先使用SIO1_I2S_CLR寄存器的对应比特作清零操作，否则会导致配置失败。 */
        unsigned int  reserved_4        : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_SET_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_START          (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_END            (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_START         (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_END           (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_START  (4)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_END    (8)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_START    (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_END      (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_START          (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_END            (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_START           (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_END             (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_START      (19)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_END        (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_I2S_CLR_UNION
 结构说明  : SIO1_I2S_CLR 寄存器结构定义。地址偏移量:0x420，初值:0x0008000C，宽度:32
 寄存器说明: SIO1 I2S模式设置清除
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 2;  /* bit[0-1]  :  */
        unsigned int  tx_ws_sel_clr         : 1;  /* bit[2]    : 该位只能写“0”，禁止写“1”。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  tx_clk_sel_clr        : 1;  /* bit[3]    : 该位只能写“0”，禁止写“1”。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  tx_fifo_threshold_clr : 5;  /* bit[4-8]  : 发送FIFO阈值清除。每一比特与接收FIFO阈值的每一比特一一对应。
                                                                 0：清零无效；
                                                                 1：清零tx_fifo_disable。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  reserved_1            : 5;  /* bit[9-13] :  */
        unsigned int  tx_fifo_disable_clr   : 1;  /* bit[14]   : 发送FIFO Disable清除。
                                                                 0：清零无效；
                                                                 1：清零tx_fifo_disable。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  reserved_2            : 1;  /* bit[15]   :  */
        unsigned int  tx_enable_clr         : 1;  /* bit[16]   : 发送通道使能清零。
                                                                 0：清零无效；
                                                                 1：清零tx_enable。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  reserved_3            : 1;  /* bit[17]   :  */
        unsigned int  dsp_mode_clr          : 1;  /* bit[18]   : 该位只能写“0”，禁止写“1”。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  tx_rx_reset_n_clr     : 1;  /* bit[19]   : 该位只能写“0”，禁止写“1”。
                                                                 注意：该寄存器软件写“1”才能实现清零，软件写“0”无效。 */
        unsigned int  reserved_4            : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_START          (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_END            (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_START         (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_END           (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_START  (4)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_END    (8)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_START    (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_END      (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_START          (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_END            (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_START           (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_END             (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_START      (19)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_END        (19)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TX_STA_UNION
 结构说明  : SIO1_TX_STA 寄存器结构定义。地址偏移量:0x42C，初值:0x00000000，宽度:32
 寄存器说明: SIO1 发送通道状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_rfifo_over  : 1;  /* bit[0]    : 右声道发送FIFO空溢出告警。
                                                          0：无告警；
                                                          1：有告警。
                                                          注意：该比特为历史告警，读清。 */
        unsigned int  tx_lfifo_over  : 1;  /* bit[1]    : 左声道发送FIFO空溢出告警。
                                                          0：无告警；
                                                          1：有告警。
                                                          注意：该比特为历史告警，读清。 */
        unsigned int  tx_rfifo_depth : 6;  /* bit[2-7]  : 右声道发送FIFO剩余数据个数。 */
        unsigned int  tx_lfifo_depth : 6;  /* bit[8-13] : 左声道发送FIFO剩余数据个数。 */
        unsigned int  reserved       : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TX_STA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_START   (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_END     (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_START   (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_END     (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_START  (2)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_END    (7)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_START  (8)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_END    (13)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_CLR_UNION
 结构说明  : SIO1_CLR 寄存器结构定义。地址偏移量:0x438，初值:0x00000000，宽度:32
 寄存器说明: SIO1中fifo清零寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_clr   : 1;  /* bit[0]   : TX通道fifo清零寄存器。
                                                   0：无效；
                                                   1：发送通道fifo清零。
                                                   注意：该寄存器软件写“1”，硬件清零，软件写“0”无效。 */
        unsigned int  reserved_0: 1;  /* bit[1]   :  */
        unsigned int  reserved_1: 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_START    (0)
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_END      (0)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION
 结构说明  : SIO1_TST_TX0_DATA 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送0声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx0_data : 24; /* bit[0-23] : SIO1发送0声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION
 结构说明  : SIO1_TST_TX1_DATA 寄存器结构定义。地址偏移量:0x444，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送1声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx1_data : 24; /* bit[0-23] : SIO1发送1声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION
 结构说明  : SIO1_TST_TX2_DATA 寄存器结构定义。地址偏移量:0x448，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送2声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx2_data : 24; /* bit[0-23] : SIO1发送2声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION
 结构说明  : SIO1_TST_TX3_DATA 寄存器结构定义。地址偏移量:0x44C，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送3声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx3_data : 24; /* bit[0-23] : SIO1发送3声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION
 结构说明  : SIO1_TST_TX4_DATA 寄存器结构定义。地址偏移量:0x450，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送4声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx4_data : 24; /* bit[0-23] : SIO1发送4声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION
 结构说明  : SIO1_TST_TX5_DATA 寄存器结构定义。地址偏移量:0x454，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送5声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx5_data : 24; /* bit[0-23] : SIO1发送5声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION
 结构说明  : SIO1_TST_TX6_DATA 寄存器结构定义。地址偏移量:0x458，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送6声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx6_data : 24; /* bit[0-23] : SIO1发送6声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION
 结构说明  : SIO1_TST_TX7_DATA 寄存器结构定义。地址偏移量:0x45C，初值:0x00000000，宽度:32
 寄存器说明: SIO1发送7声道测试数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx7_data : 24; /* bit[0-23] : SIO1发送7声道测试数据，用于SIO1接口调试。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CTRL_UNION
 结构说明  : SPDIF_CTRL 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: SPDIF控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdif_en     : 1;  /* bit[0]   : SPDIF使能。
                                                       0：不使能；
                                                       1：使能。
                                                       注意：不使能时，会对FIFO作复位操作。 */
        unsigned int  afifo_wlevel : 3;  /* bit[1-3] : FIFO空门限。
                                                       000：门限值为4；
                                                       001：门限值为8；
                                                       010：门限值为16；
                                                       011：门限值为24；
                                                       100：门限值为28；
                                                       其它：保留。
                                                       注意：FIFO中空位个数大于空门限时，允许向FIFO中写入数据；否则，停止写入数据。 */
        unsigned int  intr_en      : 1;  /* bit[4]   : 中断输出使能。
                                                       0：不使能；
                                                       1：使能。
                                                       注意：正常应用时，该中断推荐配置为不使能。 */
        unsigned int  dma_en       : 1;  /* bit[5]   : DMA请求输出使能信号。
                                                       0：不使能；
                                                       1：使能。
                                                       注意：该寄存器保留，只能配置为“0”。 */
        unsigned int  reserved     : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CTRL_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_START      (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_END        (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_START  (1)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_END    (3)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_START       (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_END         (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_START        (5)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_END          (5)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CONFIG_UNION
 结构说明  : SPDIF_CONFIG 寄存器结构定义。地址偏移量:0x804，初值:0x00000000，宽度:32
 寄存器说明: SPDIF配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  validity_info : 1;  /* bit[0]   : 音频数据可靠性位。
                                                        0：音频数据可靠（传输的音频数据已经稳定）；
                                                        1：音频数据不可靠（传输的音频数据尚未稳定）或音频数据不是线性PCM码。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CONFIG_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_START  (0)
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_INTRUPT_UNION
 结构说明  : SPDIF_INTRUPT 寄存器结构定义。地址偏移量:0x808，初值:0x00000001，宽度:32
 寄存器说明: SPDIF屏蔽后中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr  : 1;  /* bit[0]   : FIFO由不空变为空时给出的中断。
                                                            0：无中断；
                                                            1：有中断。
                                                            注意：写1清中断，写0无效，支持单比特操作。 */
        unsigned int  afifo_single_intr : 1;  /* bit[1]   : FIFO由满变为有空位时给出的中断。
                                                            0：无中断；
                                                            1：有中断。
                                                            注意：写1清中断，写0无效，支持单比特操作。SPDIF使能时才能产生中断。 */
        unsigned int  dma_burstintr     : 1;  /* bit[2]   : FIFO空位个数由不大于FIFO空门限变为大于FIFO空门限时给出的中断。
                                                            0：无中断；
                                                            1：有中断。
                                                            注意：写1清中断，写0无效，支持单比特操作。SPDIF使能时才能产生中断。 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_INTRUPT_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_START   (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_END     (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_START  (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_END    (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_START      (2)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_END        (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION
 结构说明  : SPDIF_INTR_MASK 寄存器结构定义。地址偏移量:0x80C，初值:0x00000000，宽度:32
 寄存器说明: SPDIF中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr_mask  : 1;  /* bit[0]   : afifo_empty_intr中断屏蔽。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned int  afifo_single_intr_mask : 1;  /* bit[1]   : afifo_single_intr中断屏蔽。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned int  dma_burstintr_mask     : 1;  /* bit[2]   : dma_burstintr中断屏蔽。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_START   (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_END     (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_START  (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_END    (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_START      (2)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_END        (2)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION
 结构说明  : SPDIF_FIFO_STATE 寄存器结构定义。地址偏移量:0x810，初值:0x00000001，宽度:32
 寄存器说明: SPDIF FIFO状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr_state  : 1;  /* bit[0]   : FIFO空状态。
                                                                  0：FIFO不空；
                                                                  1：FIFO空。 */
        unsigned int  afifo_single_intr_state : 1;  /* bit[1]   : FIFO有空位，允许写FIFO。
                                                                  0：FIFO满，不允许写FIFO；
                                                                  1：FIFO有空位，允许写FIFO。
                                                                  注意：SPDIF使能时，才允许写FIFO。 */
        unsigned int  dma_burstintr_state     : 1;  /* bit[2]   : FIFO空位大于FIFO空门限，允许写FIFO。
                                                                  0：FIFO空位不大于FIFO门限，不允许写FIFO；
                                                                  1：FIFO空位大于FIFO门限，允许写FIFO。
                                                                  注意：SPDIF使能时，才允许写FIFO。 */
        unsigned int  afifo_depth             : 5;  /* bit[3-7] : FIFO深度状态信息。 */
        unsigned int  reserved                : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_START   (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_END     (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_START  (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_END    (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_START      (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_END        (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_START              (3)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_END                (7)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION
 结构说明  : SPDIF_CH_STATUS1 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: 信道状态信息寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status1_0  : 1;  /* bit[0]    : 左声道应用类别。
                                                         0：消费类应用；
                                                         1：专业应用。 */
        unsigned int  ch_status1_1  : 1;  /* bit[1]    : 左声道音频采样字类别。
                                                         0：线性PCM采样；
                                                         1：其它。 */
        unsigned int  ch_status1_2  : 1;  /* bit[2]    : 左声道数据是否存在版权保护。
                                                         0：存在；
                                                         1：不存在。 */
        unsigned int  ch_status1_5  : 3;  /* bit[3-5]  : 左声道传送的音频数据是否经过预加重。
                                                         000：无预加重；
                                                         100：预加重为50μs/15μs；
                                                         其它：保留。 */
        unsigned int  ch_status1_7  : 2;  /* bit[6-7]  : 左声道信道状态信息位。
                                                         00：信道状态按照消费应用类数据格式配置。
                                                         其它：保留。 */
        unsigned int  ch_status1_8  : 1;  /* bit[8]    : 右声道应用类别。
                                                         0：消费类应用；
                                                         1：专业应用。 */
        unsigned int  ch_status1_9  : 1;  /* bit[9]    : 右声道音频采样字类别。
                                                         0：线性PCM采样；
                                                         1：其它。 */
        unsigned int  ch_status1_10 : 1;  /* bit[10]   : 右声道数据是否存在版权保护。
                                                         0：存在；
                                                         1：不存在。 */
        unsigned int  ch_status1_13 : 3;  /* bit[11-13]: 右声道传送的音频数据是否经过预加重。
                                                         000：无预加重；
                                                         100：预加重为50μs/15μs；
                                                         其它：保留。 */
        unsigned int  ch_status1    : 2;  /* bit[14-15]: 右声道信道状态信息位。
                                                         00：信道状态按照消费应用类数据格式配置。
                                                         其它：保留。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_END     (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_START   (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_END     (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_START   (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_END     (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_START   (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_END     (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_START   (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_START   (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_END     (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_START   (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_END     (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_START  (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_END    (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_START  (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_END    (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_START     (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_END       (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION
 结构说明  : SPDIF_CH_STATUS2 寄存器结构定义。地址偏移量:0x824，初值:0x00000000，宽度:32
 寄存器说明: 信道状态信息寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status2_7  : 8;  /* bit[0-7]  : 左声道选择产生音频接口信号的设备。
                                                         0x02：产生数字音频接口信号的设备为PCM encoder/decoder；
                                                         0x19：产生数字音频接口信号的设备为DVD设备。
                                                         还有很多其它应用，更多信息请参考IEC 60958协议。 */
        unsigned int  ch_status2_15 : 8;  /* bit[8-15] : 右声道选择产生音频接口信号的设备。
                                                         0x02：产生数字音频接口信号的设备为PCM encoder/decoder；
                                                         0x19：产生数字音频接口信号的设备为DVD（Digital Versatile Disc）设备。
                                                         还有很多其它应用，更多信息请参考IEC 60958协议。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION
 结构说明  : SPDIF_CH_STATUS3 寄存器结构定义。地址偏移量:0x828，初值:0x00000000，宽度:32
 寄存器说明: 信道状态信息寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status3_3  : 4;  /* bit[0-3]  : 左声道配置。
                                                         0x0：源数。
                                                         本音频接口固定采用这种配置，使用其它情况请参考IEC 60958协议。 */
        unsigned int  ch_status3_7  : 4;  /* bit[4-7]  : 左声道类型。
                                                         0x1：立体声格式的左声道。
                                                         本音频接口固定采用这种配置，使用其它情况请参考IEC 60958协议。 */
        unsigned int  ch_status3_11 : 4;  /* bit[8-11] : 右声道配置。
                                                         0x0：源数。
                                                         本音频接口固定采用这种配置，使用其它情况请参考IEC 60958协议。 */
        unsigned int  ch_status3_15 : 4;  /* bit[12-15]: 右声道类型。
                                                         0x2：立体声格式的右声道。
                                                         本音频接口固定采用这种配置，使用其它情况请参考IEC 60958协议，并修改软件方案。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION
 结构说明  : SPDIF_CH_STATUS4 寄存器结构定义。地址偏移量:0x82C，初值:0x00000000，宽度:32
 寄存器说明: 信道状态信息寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status4_3  : 4;  /* bit[0-3]  : 左声道采样频率。
                                                         0x0：44.1kHz；
                                                         0x2：48kHz；
                                                         0x3：32kHz；
                                                         0xA：96kHz。
                                                         其它采样率请参考IEC 60958协议。 */
        unsigned int  ch_status4_5  : 2;  /* bit[4-5]  : 左声道时钟精度。
                                                         00：二级；
                                                         01：三级；
                                                         10：一级。
                                                         11：接口帧速率和采样率不匹配。 */
        unsigned int  ch_status4_7  : 2;  /* bit[6-7]  : 左声道协议的保留位，固定设为00。 */
        unsigned int  ch_status4_11 : 4;  /* bit[8-11] : 右声道采样频率。
                                                         0x0：44.1kHz；
                                                         0x2：48kHz；
                                                         0x3：32kHz；
                                                         0xA：96kHz。
                                                         其它采样率请参考IEC 60958协议。 */
        unsigned int  ch_status4_13 : 2;  /* bit[12-13]: 右声道时钟精度。
                                                         00：二级；
                                                         01：三级；
                                                         10：一级。
                                                         11：接口帧速率和采样率不匹配。 */
        unsigned int  ch_status4_15 : 2;  /* bit[14-15]: 右声道协议的保留位，固定为00。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_END     (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_START   (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_END    (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_START  (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION
 结构说明  : SPDIF_CH_STATUS5 寄存器结构定义。地址偏移量:0x830，初值:0x00000000，宽度:32
 寄存器说明: 信道状态信息寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status5_0  : 1;  /* bit[0]    : 左声道最大音频采样字长度选择。
                                                         0：最大音频采样字长度是20；
                                                         1：最大音频采样字长度是24。 */
        unsigned int  ch_status5_3  : 3;  /* bit[1-3]  : 左声道音频采样字的长度。
                                                         当最大音频采样字为24时音频采样字的长度：
                                                         001：20bit；
                                                         101：24bit。
                                                         其它长度参照IEC 60958协议。
                                                         当最大音频采样字为20时音频采样字的长度：
                                                         001：16bit；
                                                         101：20bit。
                                                         其它长度参照IEC 60958协议。 */
        unsigned int  ch_status5_7  : 4;  /* bit[4-7]  : 左声道源采样率。
                                                         0x5：96kHz；
                                                         0xC：32kHz；
                                                         0xD：48kHz；
                                                         0xF：44.1kHz。
                                                         其它采样率请参考IEC 60958协议。 */
        unsigned int  ch_status5_8  : 1;  /* bit[8]    : 右声道最大音频采样字长度选择。
                                                         0：最大音频采样字长度是20；
                                                         1：最大音频采样字长度是24。 */
        unsigned int  ch_status5_11 : 3;  /* bit[9-11] : 右声道音频采样字的长度。
                                                         当最大音频采样字为24时：
                                                         001：20bit；
                                                         110：21bit；
                                                         010：22bit；
                                                         100：23bit；
                                                         101：24bit。
                                                         其它：保留，不可用。
                                                         当最大音频采样字为20时：
                                                         001：16bit；
                                                         110：17bit；
                                                         010：18bit；
                                                         100：19bit；
                                                         101：20bit。
                                                         其它：保留，不可用。 */
        unsigned int  ch_status5_15 : 4;  /* bit[12-15]: 右声道源采样率。
                                                         0x5：96kHz；
                                                         0xC：32kHz；
                                                         0xD：48kHz；
                                                         0xF：44.1kHz。
                                                         其它采样率请参考IEC 60958协议。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_END     (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_START   (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_START   (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_END     (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_START  (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION
 结构说明  : SPDIF_USER_DATA1 寄存器结构定义。地址偏移量:0x840，初值:0x00000000，宽度:32
 寄存器说明: 用户数据寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data1_lc : 8;  /* bit[0-7]  : 左声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  user_data1_rc : 8;  /* bit[8-15] : 右声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION
 结构说明  : SPDIF_USER_DATA2 寄存器结构定义。地址偏移量:0x844，初值:0x00000000，宽度:32
 寄存器说明: 用户数据寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data2_lc : 8;  /* bit[0-7]  : 左声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  user_data2_rc : 8;  /* bit[8-15] : 右声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION
 结构说明  : SPDIF_USER_DATA3 寄存器结构定义。地址偏移量:0x848，初值:0x00000000，宽度:32
 寄存器说明: 用户数据寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data3_lc : 8;  /* bit[0-7]  : 左声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  user_data3_rc : 8;  /* bit[8-15] : 右声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION
 结构说明  : SPDIF_USER_DATA4 寄存器结构定义。地址偏移量:0x84C，初值:0x00000000，宽度:32
 寄存器说明: 用户数据寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data4_lc : 8;  /* bit[0-7]  : 左声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  user_data4_rc : 8;  /* bit[8-15] : 右声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION
 结构说明  : SPDIF_USER_DATA5 寄存器结构定义。地址偏移量:0x850，初值:0x00000000，宽度:32
 寄存器说明: 用户数据寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data5_lc : 8;  /* bit[0-7]  : 左声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  user_data5_rc : 8;  /* bit[8-15] : 右声道用户数据信息。
                                                         默认为0x00，在没有声明的情况下按默认情形配置此寄存器。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_HDMI_SPDIF_EDITION_UNION
 结构说明  : SPDIF_EDITION 寄存器结构定义。地址偏移量:0x8F0，初值:0x00000021，宽度:32
 寄存器说明: 版本信息寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdif_edition : 8;  /* bit[0-7] : SPDIF版本寄存器。 */
        unsigned int  reserved      : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_ASP_HDMI_SPDIF_EDITION_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_START  (0)
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_END    (7)






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

#endif /* end of soc_asp_hdmi_interface.h */
