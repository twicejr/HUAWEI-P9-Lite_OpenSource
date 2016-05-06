//******************************************************************************
// Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
// Project name   : hiaspv300
// File name      : reg_offset.h
// Author         : hexiangnan
// Abstract       : The offset address definition for the module ASP_HDMI
// Others         : Generated automatically by nManager 
//------------------------------------------------------------------------------
// Modification History: 
// 
//******************************************************************************

/* ASP_HDMI 模块寄存器基地址 */
#define HI3650_ASP_HDMI_BASE                      (0xe804e400)

/******************************************************************************/
/*                      hiaspv300 ASP_HDMI 寄存器定义                         */
/******************************************************************************/
#define HI3650_ASP_HDMI_TX3_REG               (HI3650_ASP_HDMI_BASE + 0x0)    /* 发送通道TX3控制寄存器 */
#define HI3650_ASP_HDMI_DER_REG               (HI3650_ASP_HDMI_BASE + 0x4)    /* ASP DMA使能寄存器 */
#define HI3650_ASP_HDMI_DSTOP_REG             (HI3650_ASP_HDMI_BASE + 0x8)    /* ASP DMA停止使能寄存器 */
#define HI3650_ASP_HDMI_ASS_ISR_REG           (HI3650_ASP_HDMI_BASE + 0xC)    /* ASP全局中断状态寄存器 */
#define HI3650_ASP_HDMI_IRSR_REG              (HI3650_ASP_HDMI_BASE + 0x10)   /* ASP原始状态寄存器 */
#define HI3650_ASP_HDMI_IER_REG               (HI3650_ASP_HDMI_BASE + 0x14)   /* ASP中断使能寄存器 */
#define HI3650_ASP_HDMI_IMSR_REG              (HI3650_ASP_HDMI_BASE + 0x18)   /* ASP屏蔽后状态寄存器 */
#define HI3650_ASP_HDMI_ICR_REG               (HI3650_ASP_HDMI_BASE + 0x1C)   /* ASP中断清零寄存器 */
#define HI3650_ASP_HDMI_PCMNSSR_REG           (HI3650_ASP_HDMI_BASE + 0x20)   /* 通道新歌起始寄存器 */
#define HI3650_ASP_HDMI_P30CGR_REG            (HI3650_ASP_HDMI_BASE + 0x28)   /* PCM3通道0声道增益寄存器 */
#define HI3650_ASP_HDMI_P31CGR_REG            (HI3650_ASP_HDMI_BASE + 0x2C)   /* PCM3通道1声道增益寄存器 */
#define HI3650_ASP_HDMI_P32CGR_REG            (HI3650_ASP_HDMI_BASE + 0x30)   /* PCM3通道2声道增益寄存器 */
#define HI3650_ASP_HDMI_P33CGR_REG            (HI3650_ASP_HDMI_BASE + 0x34)   /* PCM3通道3声道增益寄存器 */
#define HI3650_ASP_HDMI_P34CGR_REG            (HI3650_ASP_HDMI_BASE + 0x38)   /* PCM3通道4声道增益寄存器 */
#define HI3650_ASP_HDMI_P35CGR_REG            (HI3650_ASP_HDMI_BASE + 0x3C)   /* PCM3通道5声道增益寄存器 */
#define HI3650_ASP_HDMI_P36CGR_REG            (HI3650_ASP_HDMI_BASE + 0x40)   /* PCM3通道6声道增益寄存器 */
#define HI3650_ASP_HDMI_P37CGR_REG            (HI3650_ASP_HDMI_BASE + 0x44)   /* PCM3通道7声道增益寄存器 */
#define HI3650_ASP_HDMI_P3ASAR_REG            (HI3650_ASP_HDMI_BASE + 0x48)   /* PCM3A通道搬运起始地址寄存器 */
#define HI3650_ASP_HDMI_P3ADLR_REG            (HI3650_ASP_HDMI_BASE + 0x4C)   /* PCM3A通道搬运长度寄存器 */
#define HI3650_ASP_HDMI_P3BSAR_REG            (HI3650_ASP_HDMI_BASE + 0x50)   /* PCM3B通道搬运起始地址寄存器 */
#define HI3650_ASP_HDMI_P3BDLR_REG            (HI3650_ASP_HDMI_BASE + 0x54)   /* PCM3B通道搬运长度寄存器 */
#define HI3650_ASP_HDMI_SPDIFSEL_REG          (HI3650_ASP_HDMI_BASE + 0x58)   /* 混音数据播放接口选择寄存器 */
#define HI3650_ASP_HDMI_P3ADLS_REG            (HI3650_ASP_HDMI_BASE + 0x5C)   /* DMA停止时PCM3A通道搬运长度状态寄存器 */
#define HI3650_ASP_HDMI_P3BDLS_REG            (HI3650_ASP_HDMI_BASE + 0x60)   /* DMA停止时PCM3B通道搬运长度状态寄存器 */
#define HI3650_ASP_HDMI_FDS_REG               (HI3650_ASP_HDMI_BASE + 0x64)   /* DMA搬运数据缓存FIFO状态寄存器 */
#define HI3650_ASP_HDMI_P3ADL_REG             (HI3650_ASP_HDMI_BASE + 0x68)   /* PCM3A通道DMA搬运剩余长度状态寄存器 */
#define HI3650_ASP_HDMI_P3BDL_REG             (HI3650_ASP_HDMI_BASE + 0x6C)   /* PCM3B通道DMA搬运剩余长度状态寄存器 */
#define HI3650_ASP_HDMI_SECURE_REG            (HI3650_ASP_HDMI_BASE + 0x70)   /* ASP_HDMI模块安全寄存器 */
#define HI3650_ASP_HDMI_SIO1_ASPIF_SEL_REG        (HI3650_ASP_HDMI_BASE + 0x400)  /* SIO1音频接口选择寄存器 */
#define HI3650_ASP_HDMI_SIO1_RAW_INT_REG          (HI3650_ASP_HDMI_BASE + 0x408)  /* SIO1中断原始状态寄存器 */
#define HI3650_ASP_HDMI_SIO1_INT_CLR_REG          (HI3650_ASP_HDMI_BASE + 0x40C)  /* SIO1中断清零寄存器 */
#define HI3650_ASP_HDMI_SIO1_INT_ENABLE_REG       (HI3650_ASP_HDMI_BASE + 0x410)  /* SIO1中断使能寄存器 */
#define HI3650_ASP_HDMI_SIO1_INT_MASKED_STATUS_REG  (HI3650_ASP_HDMI_BASE + 0x414)  /* SIO1中断屏蔽后状态寄存器 */
#define HI3650_ASP_HDMI_SIO1_I2S_SET_REG          (HI3650_ASP_HDMI_BASE + 0x41C)  /* SIO1 I2S模式设置 */
#define HI3650_ASP_HDMI_SIO1_I2S_CLR_REG          (HI3650_ASP_HDMI_BASE + 0x420)  /* SIO1 I2S模式设置清除 */
#define HI3650_ASP_HDMI_SIO1_TX_STA_REG           (HI3650_ASP_HDMI_BASE + 0x42C)  /* SIO1 发送通道状态寄存器 */
#define HI3650_ASP_HDMI_SIO1_CLR_REG              (HI3650_ASP_HDMI_BASE + 0x438)  /* SIO1中fifo清零寄存器 */
#define HI3650_ASP_HDMI_SIO1_TST_TX0_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x440)  /* SIO1发送0声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX1_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x444)  /* SIO1发送1声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX2_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x448)  /* SIO1发送2声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX3_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x44C)  /* SIO1发送3声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX4_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x450)  /* SIO1发送4声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX5_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x454)  /* SIO1发送5声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX6_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x458)  /* SIO1发送6声道测试数据 */
#define HI3650_ASP_HDMI_SIO1_TST_TX7_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x45C)  /* SIO1发送7声道测试数据 */
#define HI3650_ASP_HDMI_SPDIF_CTRL_REG            (HI3650_ASP_HDMI_BASE + 0x800)  /* SPDIF控制寄存器 */
#define HI3650_ASP_HDMI_SPDIF_CONFIG_REG          (HI3650_ASP_HDMI_BASE + 0x804)  /* SPDIF配置寄存器 */
#define HI3650_ASP_HDMI_SPDIF_INTRUPT_REG         (HI3650_ASP_HDMI_BASE + 0x808)  /* SPDIF屏蔽后中断状态寄存器 */
#define HI3650_ASP_HDMI_SPDIF_INTR_MASK_REG       (HI3650_ASP_HDMI_BASE + 0x80C)  /* SPDIF中断屏蔽寄存器 */
#define HI3650_ASP_HDMI_SPDIF_FIFO_STATE_REG      (HI3650_ASP_HDMI_BASE + 0x810)  /* SPDIF FIFO状态寄存器 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS1_REG      (HI3650_ASP_HDMI_BASE + 0x820)  /* 信道状态信息寄存器1 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS2_REG      (HI3650_ASP_HDMI_BASE + 0x824)  /* 信道状态信息寄存器2 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS3_REG      (HI3650_ASP_HDMI_BASE + 0x828)  /* 信道状态信息寄存器3 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS4_REG      (HI3650_ASP_HDMI_BASE + 0x82C)  /* 信道状态信息寄存器4 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS5_REG      (HI3650_ASP_HDMI_BASE + 0x830)  /* 信道状态信息寄存器5 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA1_REG      (HI3650_ASP_HDMI_BASE + 0x840)  /* 用户数据寄存器1 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA2_REG      (HI3650_ASP_HDMI_BASE + 0x844)  /* 用户数据寄存器2 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA3_REG      (HI3650_ASP_HDMI_BASE + 0x848)  /* 用户数据寄存器3 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA4_REG      (HI3650_ASP_HDMI_BASE + 0x84C)  /* 用户数据寄存器4 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA5_REG      (HI3650_ASP_HDMI_BASE + 0x850)  /* 用户数据寄存器5 */
#define HI3650_ASP_HDMI_SPDIF_EDITION_REG         (HI3650_ASP_HDMI_BASE + 0x8F0)  /* 版本信息寄存器 */
