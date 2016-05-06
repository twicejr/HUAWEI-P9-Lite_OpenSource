/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_glb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:06
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_GLB.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_GLB_INTERFACE_H__
#define __SOC_DSS_GLB_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_GLB
 ****************************************************************************/
/* 寄存器说明：dss版本号
   位域定义UNION结构:  SOC_DSS_GLB_DSS_TAG_UNION */
#define SOC_DSS_GLB_DSS_TAG_ADDR(base)                ((base) + (0x0000))

/* 寄存器说明：配置控制寄存器
   位域定义UNION结构:  SOC_DSS_GLB_APB_CTL_UNION */
#define SOC_DSS_GLB_APB_CTL_ADDR(base)                ((base) + (0x0004))

/* 寄存器说明：像素0的2分频时钟门控使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_ADDR(base)        ((base) + (0x0100))

/* 寄存器说明：像素0的4分频时钟门控使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_ADDR(base)        ((base) + (0x104))

/* 寄存器说明：像素0的时钟门控使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_GT_EN_ADDR(base)             ((base) + (0x108))

/* 寄存器说明：DSI时钟对应的dsi时钟门控信号
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_ADDR(base)         ((base) + (0x10C))

/* 寄存器说明：像素0的几分频的配置
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DIVXCFG_UNION */
#define SOC_DSS_GLB_PXL0_DIVXCFG_ADDR(base)           ((base) + (0x110))

/* 寄存器说明：DSI1的时钟选择
   位域定义UNION结构:  SOC_DSS_GLB_DSI1_CLK_SEL_UNION */
#define SOC_DSS_GLB_DSI1_CLK_SEL_ADDR(base)           ((base) + (0x114))

/* 寄存器说明：axi总线时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_DSS_AXI_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_AXI_RST_EN_ADDR(base)         ((base) + (0x118))

/* 寄存器说明：apb总线时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_DSS_APB_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_APB_RST_EN_ADDR(base)         ((base) + (0x11C))

/* 寄存器说明：core时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_DSS_CORE_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_CORE_RST_EN_ADDR(base)        ((base) + (0x120))

/* 寄存器说明：像素0的2分频时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_ADDR(base)       ((base) + (0x124))

/* 寄存器说明：像素0的4分频时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_ADDR(base)       ((base) + (0x128))

/* 寄存器说明：像素0时钟域的软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_RST_EN_ADDR(base)            ((base) + (0x12C))

/* 寄存器说明：像素0对应的DSI时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_ADDR(base)        ((base) + (0x130))

/* 寄存器说明：像素1时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_ADDR(base)        ((base) + (0x134))

/* 寄存器说明：DSI1的复位选择
   位域定义UNION结构:  SOC_DSS_GLB_DSI1_RST_SEL_UNION */
#define SOC_DSS_GLB_DSI1_RST_SEL_ADDR(base)           ((base) + (0x138))

/* 寄存器说明：MMBUF axi总线时钟域软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION */
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_ADDR(base)      ((base) + (0x13C))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_ADDR(base)       ((base) + (0x140))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_ADDR(base)       ((base) + (0x144))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_ADDR(base)       ((base) + (0x148))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_ADDR(base)       ((base) + (0x14C))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_ADDR(base)       ((base) + (0x150))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_ADDR(base)       ((base) + (0x154))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_ADDR(base)       ((base) + (0x158))

/* 寄存器说明：AFBCD IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_ADDR(base)       ((base) + (0x15C))

/* 寄存器说明：AFBCE IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_ADDR(base)       ((base) + (0x160))

/* 寄存器说明：AFBCE IP软复位使能
   位域定义UNION结构:  SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_ADDR(base)       ((base) + (0x164))

/* 寄存器说明：MCU像素0中断指示
   位域定义UNION结构:  SOC_DSS_GLB_MCU_ITF0_INTS_UNION */
#define SOC_DSS_GLB_MCU_ITF0_INTS_ADDR(base)          ((base) + (0x0170))

/* 寄存器说明：MCU像素0中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_ADDR(base)       ((base) + (0x0174))

/* 寄存器说明：MCU像素1中断指示
   位域定义UNION结构:  SOC_DSS_GLB_MCU_ITF1_INTS_UNION */
#define SOC_DSS_GLB_MCU_ITF1_INTS_ADDR(base)          ((base) + (0x0178))

/* 寄存器说明：MCU像素1中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_ADDR(base)       ((base) + (0x017C))

/* 寄存器说明：CPU像素0中断指示
   位域定义UNION结构:  SOC_DSS_GLB_CPU_ITF0_INTS_UNION */
#define SOC_DSS_GLB_CPU_ITF0_INTS_ADDR(base)          ((base) + (0x0180))

/* 寄存器说明：CPU像素0中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_ADDR(base)       ((base) + (0x0184))

/* 寄存器说明：CPU像素1中断指示
   位域定义UNION结构:  SOC_DSS_GLB_CPU_ITF1_INTS_UNION */
#define SOC_DSS_GLB_CPU_ITF1_INTS_ADDR(base)          ((base) + (0x0188))

/* 寄存器说明：CPU像素1中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_ADDR(base)       ((base) + (0x018C))

/* 寄存器说明：CPU响应的DPP中断指示
   位域定义UNION结构:  SOC_DSS_GLB_DPP_INTS_UNION */
#define SOC_DSS_GLB_DPP_INTS_ADDR(base)               ((base) + (0x0190))

/* 寄存器说明：CPU响应的DPP中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_DPP_INT_MSK_UNION */
#define SOC_DSS_GLB_DPP_INT_MSK_ADDR(base)            ((base) + (0x0194))

/* 寄存器说明：CPU响应的RCH CE中断指示
   位域定义UNION结构:  SOC_DSS_GLB_RCH_CE_INTS_UNION */
#define SOC_DSS_GLB_RCH_CE_INTS_ADDR(base)            ((base) + (0x198))

/* 寄存器说明：CPU响应的RCH CE中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_RCH_CE_INT_MSK_UNION */
#define SOC_DSS_GLB_RCH_CE_INT_MSK_ADDR(base)         ((base) + (0x19C))

/* 寄存器说明：MCU主屏中断指示
   位域定义UNION结构:  SOC_DSS_GLB_MCU_PDP_INTS_UNION */
#define SOC_DSS_GLB_MCU_PDP_INTS_ADDR(base)           ((base) + (0x20C))

/* 寄存器说明：MCU主屏中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_ADDR(base)        ((base) + (0x210))

/* 寄存器说明：MCU副屏中断指示
   位域定义UNION结构:  SOC_DSS_GLB_MCU_SDP_INTS_UNION */
#define SOC_DSS_GLB_MCU_SDP_INTS_ADDR(base)           ((base) + (0x214))

/* 寄存器说明：MCU副屏中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_ADDR(base)        ((base) + (0x218))

/* 寄存器说明：MCU离线中断指示
   位域定义UNION结构:  SOC_DSS_GLB_MCU_OFF_INTS_UNION */
#define SOC_DSS_GLB_MCU_OFF_INTS_ADDR(base)           ((base) + (0x21C))

/* 寄存器说明：MCU离线中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_ADDR(base)        ((base) + (0x220))

/* 寄存器说明：CPU主屏中断指示
   位域定义UNION结构:  SOC_DSS_GLB_CPU_PDP_INTS_UNION */
#define SOC_DSS_GLB_CPU_PDP_INTS_ADDR(base)           ((base) + (0x224))

/* 寄存器说明：CPU主屏中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_ADDR(base)        ((base) + (0x228))

/* 寄存器说明：CPU副屏中断指示
   位域定义UNION结构:  SOC_DSS_GLB_CPU_SDP_INTS_UNION */
#define SOC_DSS_GLB_CPU_SDP_INTS_ADDR(base)           ((base) + (0x22C))

/* 寄存器说明：CPU副屏中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_ADDR(base)        ((base) + (0x230))

/* 寄存器说明：CPU离线中断指示
   位域定义UNION结构:  SOC_DSS_GLB_CPU_OFF_INTS_UNION */
#define SOC_DSS_GLB_CPU_OFF_INTS_ADDR(base)           ((base) + (0x234))

/* 寄存器说明：CPU离线中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_ADDR(base)        ((base) + (0x238))

/* 寄存器说明：主控中断指示
   位域定义UNION结构:  SOC_DSS_GLB_DBG_MCTL_INTS_UNION */
#define SOC_DSS_GLB_DBG_MCTL_INTS_ADDR(base)          ((base) + (0x23C))

/* 寄存器说明：主控中断屏蔽
   位域定义UNION结构:  SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_ADDR(base)       ((base) + (0x240))

/* 寄存器说明：写通道0中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_WCH0_INTS_UNION */
#define SOC_DSS_GLB_DBG_WCH0_INTS_ADDR(base)          ((base) + (0x244))

/* 寄存器说明：写通道0中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_ADDR(base)       ((base) + (0x248))

/* 寄存器说明：写通道1中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_WCH1_INTS_UNION */
#define SOC_DSS_GLB_DBG_WCH1_INTS_ADDR(base)          ((base) + (0x24C))

/* 寄存器说明：写通道1中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_ADDR(base)       ((base) + (0x250))

/* 寄存器说明：读通道0中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH0_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH0_INTS_ADDR(base)          ((base) + (0x254))

/* 寄存器说明：读通道0中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_ADDR(base)       ((base) + (0x258))

/* 寄存器说明：读通道1中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH1_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH1_INTS_ADDR(base)          ((base) + (0x25C))

/* 寄存器说明：读通道1中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_ADDR(base)       ((base) + (0x260))

/* 寄存器说明：读通道2中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH2_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH2_INTS_ADDR(base)          ((base) + (0x264))

/* 寄存器说明：读通道2中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_ADDR(base)       ((base) + (0x268))

/* 寄存器说明：读通道3中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH3_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH3_INTS_ADDR(base)          ((base) + (0x26C))

/* 寄存器说明：读通道3中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_ADDR(base)       ((base) + (0x270))

/* 寄存器说明：读通道4中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH4_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH4_INTS_ADDR(base)          ((base) + (0x274))

/* 寄存器说明：读通道4中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_ADDR(base)       ((base) + (0x278))

/* 寄存器说明：读通道5中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH5_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH5_INTS_ADDR(base)          ((base) + (0x27C))

/* 寄存器说明：读通道5中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_ADDR(base)       ((base) + (0x280))

/* 寄存器说明：读通道6中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH6_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH6_INTS_ADDR(base)          ((base) + (0x284))

/* 寄存器说明：读通道6中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_ADDR(base)       ((base) + (0x288))

/* 寄存器说明：读通道7中断指示（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH7_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH7_INTS_ADDR(base)          ((base) + (0x28C))

/* 寄存器说明：读通道7中断屏蔽（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_ADDR(base)       ((base) + (0x290))

/* 寄存器说明：GLB中断（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_INTS_UNION */
#define SOC_DSS_GLB_INTS_ADDR(base)                   ((base) + (0x294))

/* 寄存器说明：GLB中断（调试用）
   位域定义UNION结构:  SOC_DSS_GLB_INT_MSK_UNION */
#define SOC_DSS_GLB_INT_MSK_ADDR(base)                ((base) + (0x298))

/* 寄存器说明：一级模块软件时钟选择信号
   位域定义UNION结构:  SOC_DSS_GLB_MODULE_CLK_SEL_UNION */
#define SOC_DSS_GLB_MODULE_CLK_SEL_ADDR(base)         ((base) + (0x0300))

/* 寄存器说明：一级模块软件时钟使能信号
   位域定义UNION结构:  SOC_DSS_GLB_MODULE_CLK_EN_UNION */
#define SOC_DSS_GLB_MODULE_CLK_EN_ADDR(base)          ((base) + (0x304))

/* 寄存器说明：一级模块软件时钟选择信号
   位域定义UNION结构:  SOC_DSS_GLB_MODULE1_CLK_SEL_UNION */
#define SOC_DSS_GLB_MODULE1_CLK_SEL_ADDR(base)        ((base) + (0x308))

/* 寄存器说明：一级模块软件时钟使能信号
   位域定义UNION结构:  SOC_DSS_GLB_MODULE1_CLK_EN_UNION */
#define SOC_DSS_GLB_MODULE1_CLK_EN_ADDR(base)         ((base) + (0x30C))

/* 寄存器说明：调试寄存器
   位域定义UNION结构:  SOC_DSS_GLB_GLB0_DBG_SEL_UNION */
#define SOC_DSS_GLB_GLB0_DBG_SEL_ADDR(base)           ((base) + (0x310))

/* 寄存器说明：调试寄存器
   位域定义UNION结构:  SOC_DSS_GLB_GLB1_DBG_SEL_UNION */
#define SOC_DSS_GLB_GLB1_DBG_SEL_ADDR(base)           ((base) + (0x314))

/* 寄存器说明：CPU中断调试寄存器
   位域定义UNION结构:  SOC_DSS_GLB_DBG_IRQ_CPU_UNION */
#define SOC_DSS_GLB_DBG_IRQ_CPU_ADDR(base)            ((base) + (0x320))

/* 寄存器说明：MCU中断调试寄存器
   位域定义UNION结构:  SOC_DSS_GLB_DBG_IRQ_MCU_UNION */
#define SOC_DSS_GLB_DBG_IRQ_MCU_ADDR(base)            ((base) + (0x324))

/* 寄存器说明：TP选择信号
   位域定义UNION结构:  SOC_DSS_GLB_TP_SEL_UNION */
#define SOC_DSS_GLB_TP_SEL_ADDR(base)                 ((base) + (0x0400))

/* 寄存器说明：LDI0的crc校验结果
   位域定义UNION结构:  SOC_DSS_GLB_CRC_DBG_LDI0_UNION */
#define SOC_DSS_GLB_CRC_DBG_LDI0_ADDR(base)           ((base) + (0x0404))

/* 寄存器说明：LDI1的crc校验结果
   位域定义UNION结构:  SOC_DSS_GLB_CRC_DBG_LDI1_UNION */
#define SOC_DSS_GLB_CRC_DBG_LDI1_ADDR(base)           ((base) + (0x0408))

/* 寄存器说明：LDI0的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_GLB_CRC_LDI0_EN_UNION */
#define SOC_DSS_GLB_CRC_LDI0_EN_ADDR(base)            ((base) + (0x040C))

/* 寄存器说明：LDI0上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_GLB_CRC_LDI0_FRM_UNION */
#define SOC_DSS_GLB_CRC_LDI0_FRM_ADDR(base)           ((base) + (0x0410))

/* 寄存器说明：LDI1的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_GLB_CRC_LDI1_EN_UNION */
#define SOC_DSS_GLB_CRC_LDI1_EN_ADDR(base)            ((base) + (0x0414))

/* 寄存器说明：LDI1上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_GLB_CRC_LDI1_FRM_UNION */
#define SOC_DSS_GLB_CRC_LDI1_FRM_ADDR(base)           ((base) + (0x0418))

/* 寄存器说明：CPU读写memory使能寄存器
   位域定义UNION结构:  SOC_DSS_GLB_DSS_MEM_CTRL_UNION */
#define SOC_DSS_GLB_DSS_MEM_CTRL_ADDR(base)           ((base) + (0x0600))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_GLB_DSS_PM_CTRL_UNION */
#define SOC_DSS_GLB_DSS_PM_CTRL_ADDR(base)            ((base) + (0x0604))





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
                     (1/1) reg_GLB
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_TAG_UNION
 结构说明  : DSS_TAG 寄存器结构定义。地址偏移量:0x0000，初值:0x14100703，宽度:32
 寄存器说明: dss版本号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_tag : 32; /* bit[0-31]: dss版本号 */
    } reg;
} SOC_DSS_GLB_DSS_TAG_UNION;
#endif
#define SOC_DSS_GLB_DSS_TAG_dss_tag_START  (0)
#define SOC_DSS_GLB_DSS_TAG_dss_tag_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_APB_CTL_UNION
 结构说明  : APB_CTL 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 配置控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_cpu_force : 1;  /* bit[0]   : 1:强制选择CPU配置DSS寄存器
                                                        0:由DSS自动仲裁选择来自CPU或者command list配置寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_APB_CTL_UNION;
#endif
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_START  (0)
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION
 结构说明  : PXL0_DIV2_GT_EN 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 像素0的2分频时钟门控使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div2_gt_en : 1;  /* bit[0-0] : 1：开启pxl0的2分频时钟
                                                          0：关闭pxl0的2分频时钟 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION
 结构说明  : PXL0_DIV4_GT_EN 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 像素0的4分频时钟门控使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div4_gt_en : 1;  /* bit[0-0] : 1：开启pxl0的4分频时钟
                                                          0：关闭pxl0的4分频时钟 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_GT_EN_UNION
 结构说明  : PXL0_GT_EN 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 像素0的时钟门控使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_gt_en : 1;  /* bit[0-0] : 1：开启pxl0的时钟
                                                     0：关闭pxl0的时钟 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION
 结构说明  : PXL0_DSI_GT_EN 寄存器结构定义。地址偏移量:0x10C，初值:0x00000001，宽度:32
 寄存器说明: DSI时钟对应的dsi时钟门控信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_dsi_gt_en : 2;  /* bit[0-1] : 2’bx0，关闭pxl0生成的dsi时钟
                                                         2’b01，开启pxl0生成的dsi时钟，选通没有分频的时钟。
                                                         2’b11，开始pxl0生成的dsi时钟，选通1~8分频的时钟。 */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DIVXCFG_UNION
 结构说明  : PXL0_DIVXCFG 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 像素0的几分频的配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_divxcfg : 3;  /* bit[0-2] : 对输入pxl0时钟时钟进行分频配置。
                                                       1：表示2分频
                                                       2：表示3分频
                                                       3：表示4分频
                                                       4：表示5分频
                                                       5：表示6分频
                                                       6：表示7分频
                                                       7：表示8分频 */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DIVXCFG_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_START  (0)
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSI1_CLK_SEL_UNION
 结构说明  : DSI1_CLK_SEL 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: DSI1的时钟选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_clk_sel : 1;  /* bit[0]   : 0：表示选择pxl0的时钟
                                                       1：表示选择pxl1的时钟 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSI1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_START  (0)
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_AXI_RST_EN_UNION
 结构说明  : DSS_AXI_RST_EN 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: axi总线时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_axi_rst_en : 1;  /* bit[0-0] : 1：软件复位axi总线
                                                         0：软件解复位axi总线 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSS_AXI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_APB_RST_EN_UNION
 结构说明  : DSS_APB_RST_EN 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: apb总线时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_apb_rst_en : 1;  /* bit[0-0] : 1：软件复位apb总线
                                                         0：软件解复位apb总线 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSS_APB_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_CORE_RST_EN_UNION
 结构说明  : DSS_CORE_RST_EN 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: core时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_core_rst_en : 1;  /* bit[0-0] : 1：软件复位dss core时钟域
                                                          0：软件解复位dss core时钟域 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSS_CORE_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION
 结构说明  : PXL0_DIV2_RST_EN 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: 像素0的2分频时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div2_rst_en : 1;  /* bit[0-0] : 1：软件复位pxl0 2分频时钟域
                                                           0：软件解复位pxl0 2分频时钟域 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION
 结构说明  : PXL0_DIV4_RST_EN 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: 像素0的4分频时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div4_rst_en : 1;  /* bit[0-0] : 1：软件复位pxl0 4分频时钟域
                                                           0：软件解复位pxl0 4分频时钟域 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_RST_EN_UNION
 结构说明  : PXL0_RST_EN 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: 像素0时钟域的软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_rst_en : 1;  /* bit[0-0] : 1：软件复位pxl0时钟域
                                                      0：软件解复位pxl0时钟域 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION
 结构说明  : PXL0_DSI_RST_EN 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: 像素0对应的DSI时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_dsi_rst_en : 1;  /* bit[0]   : 1：软件复位dsi分频时钟域
                                                          0：软件解复位dsi分频时钟域 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION
 结构说明  : DSS_PXL1_RST_EN 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: 像素1时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_pxl1_rst_en : 1;  /* bit[0-0] : 1：软件复pxl1时钟域，生成的复位信号为异步复位同步撤离。
                                                          0：软件解复位pxl1时钟域 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSI1_RST_SEL_UNION
 结构说明  : DSI1_RST_SEL 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: DSI1的复位选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_rst_sel : 1;  /* bit[0]   : 0：表示选择pxl0的复位信号
                                                       1：表示选择pxl1的复位信号 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DSI1_RST_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_START  (0)
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION
 结构说明  : MM_AXI_CLK_RST_EN 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: MMBUF axi总线时钟域软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mm_axi_clk_rst_en : 1;  /* bit[0-0] : 1：软件复位mmbuf的axi总线
                                                            0：软件解复位mmbuf的axi总线 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_START  (0)
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION
 结构说明  : AFBCD0_IP_RST_EN 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd0_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION
 结构说明  : AFBCD1_IP_RST_EN 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd1_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION
 结构说明  : AFBCD2_IP_RST_EN 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd2_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION
 结构说明  : AFBCD3_IP_RST_EN 寄存器结构定义。地址偏移量:0x14C，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd3_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION
 结构说明  : AFBCD4_IP_RST_EN 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd4_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION
 结构说明  : AFBCD5_IP_RST_EN 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd5_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION
 结构说明  : AFBCD6_IP_RST_EN 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd6_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION
 结构说明  : AFBCD7_IP_RST_EN 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: AFBCD IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd7_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbcd mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION
 结构说明  : AFBCE0_IP_RST_EN 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: AFBCE IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce0_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbce mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION
 结构说明  : AFBCE1_IP_RST_EN 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: AFBCE IP软复位使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce1_ip_rst_en : 1;  /* bit[0-0] : 1：软件复位afbce mali ip
                                                           0：软件解复位afbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_ITF0_INTS_UNION
 结构说明  : MCU_ITF0_INTS 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: MCU像素0中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf0_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_START  (0)
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION
 结构说明  : MCU_ITF0_INT_MSK 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: MCU像素0中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf0_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_ITF1_INTS_UNION
 结构说明  : MCU_ITF1_INTS 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: MCU像素1中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf1_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_START  (0)
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION
 结构说明  : MCU_ITF1_INT_MSK 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: MCU像素1中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf1_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_ITF0_INTS_UNION
 结构说明  : CPU_ITF0_INTS 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: CPU像素0中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf0_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_START  (0)
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION
 结构说明  : CPU_ITF0_INT_MSK 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: CPU像素0中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf0_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_ITF1_INTS_UNION
 结构说明  : CPU_ITF1_INTS 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: CPU像素1中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf1_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_START  (0)
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION
 结构说明  : CPU_ITF1_INT_MSK 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: CPU像素1中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf1_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DPP_INTS_UNION
 结构说明  : DPP_INTS 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: CPU响应的DPP中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_ints : 8;  /* bit[0-7] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                   bit7: strength_intp, SBL处理强度中断，当SBL处理强度发生变化时置1
                                                   bit6: backlight_intp, SBL背光强度中断，当SBL计算的背光数值发生变化时置1
                                                   bit5: ce_end_ind, ACM_CE统计完成中断
                                                   bit4: ce_cancel_ind, ACM_CE取消统计中断
                                                   bit3: ce_lut1_rw_collide_ind, ACM_CE LUT1读写冲突
                                                   bit2: ce_lut0_rw_collide_ind, ACM_CE LUT0读写冲突
                                                   bit1: ce_hist1_rw_collide_ind, ACM_CE 直方图memory1读写冲突
                                                   bit0: ce_hist0_rw_collide_ind, ACM_CE 直方图memory0读写冲突 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DPP_INTS_UNION;
#endif
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_START  (0)
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DPP_INT_MSK_UNION
 结构说明  : DPP_INT_MSK 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: CPU响应的DPP中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_int_msk : 8;  /* bit[0-7] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                      bit7: strength_intp, SBL处理强度中断，当SBL处理强度发生变化时置1
                                                      bit6: backlight_intp, SBL背光强度中断，当SBL计算的背光数值发生变化时置1
                                                      bit5: ce_end_ind, ACM_CE统计完成中断
                                                      bit4: ce_cancel_ind, ACM_CE取消统计中断
                                                      bit3: ce_lut1_rw_collide_ind, ACM_CE LUT1读写冲突
                                                      bit2: ce_lut0_rw_collide_ind, ACM_CE LUT0读写冲突
                                                      bit1: ce_hist1_rw_collide_ind, ACM_CE 直方图memory1读写冲突
                                                      bit0: ce_hist0_rw_collide_ind, ACM_CE 直方图memory0读写冲突 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DPP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_START  (0)
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_RCH_CE_INTS_UNION
 结构说明  : RCH_CE_INTS 寄存器结构定义。地址偏移量:0x198，初值:0x00000000，宽度:32
 寄存器说明: CPU响应的RCH CE中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ce_ints : 4;  /* bit[0-3] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                      bit3:RCH4的ce_end
                                                      bit2:RCH4的ce_cancle
                                                      bit1:RCH2的ce_end
                                                      bit0:RCH2的ce_cancle */
        unsigned int  reserved    : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_GLB_RCH_CE_INTS_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_START  (0)
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_RCH_CE_INT_MSK_UNION
 结构说明  : RCH_CE_INT_MSK 寄存器结构定义。地址偏移量:0x19C，初值:0x00000000，宽度:32
 寄存器说明: CPU响应的RCH CE中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ce_int_msk : 4;  /* bit[0-3] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                         bit3:RCH4的ce_end
                                                         bit2:RCH4的ce_cancle
                                                         bit1:RCH2的ce_end
                                                         bit0:RCH2的ce_cancle */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_GLB_RCH_CE_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_START  (0)
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_PDP_INTS_UNION
 结构说明  : MCU_PDP_INTS 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: MCU主屏中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_pdp_ints : 31; /* bit[0-30]: 中断状态寄存器，1表示有中断，0表示没有中断
                                                       bit30:dss_glb_ints中断
                                                       bit29:mmu_irpt_s,mmu安全中断
                                                       bit28:mmu_irpt_ns,mmu非安全中断
                                                       bit27:dbg_mctl_ints
                                                       bit26:dbg_wch1_ints
                                                       bit25:dbg_wch0_ints
                                                       bit24:dbg_rch7_ints
                                                       bit23:dbg_rch6_ints
                                                       bit22:dbg_rch5_ints
                                                       bit21:dbg_rch4_ints
                                                       bit20:dbg_rch3_ints
                                                       bit19:dbg_rch2_ints
                                                       bit18:dbg_rch1_ints
                                                       bit17:dbg_rch0_ints
                                                       bit16:itf0_ints
                                                       bit15:dpp_ints
                                                       bit14:cmdlist第13通道的中断
                                                       bit13:cmdlist第12通道的中断
                                                       bit12:cmdlist第11通道的中断
                                                       bit11:cmdlist第10通道的中断
                                                       bit10:cmdlist第9通道的中断
                                                       bit9:cmdlist第8通道的中断
                                                       bit8:cmdlist第7通道的中断
                                                       bit7:cmdlist第6通道的中断
                                                       bit6:cmdlist第5通道的中断
                                                       bit5:cmdlist第4通道的中断
                                                       bit4:cmdlist第3通道的中断
                                                       bit3:cmdlist第2通道的中断
                                                       bit2:cmdlist第1通道的中断
                                                       bit1:cmdlist第0通道的中断
                                                       bit0:rch_ce_ints */
        unsigned int  reserved     : 1;  /* bit[31]  : 保留 */
    } reg;
} SOC_DSS_GLB_MCU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_START  (0)
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION
 结构说明  : MCU_PDP_INT_MSK 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: MCU主屏中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_pdp_int_msk : 31; /* bit[0-30]: 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                          bit30:dss_glb_ints中断
                                                          bit29:mmu_irpt_s,mmu安全中断
                                                          bit28:mmu_irpt_ns,mmu非安全中断
                                                          bit27:dbg_mctl_ints
                                                          bit26:dbg_wch1_ints
                                                          bit25:dbg_wch0_ints
                                                          bit24:dbg_rch7_ints
                                                          bit23:dbg_rch6_ints
                                                          bit22:dbg_rch5_ints
                                                          bit21:dbg_rch4_ints
                                                          bit20:dbg_rch3_ints
                                                          bit19:dbg_rch2_ints
                                                          bit18:dbg_rch1_ints
                                                          bit17:dbg_rch0_ints
                                                          bit16:itf0_ints
                                                          bit15:dpp_ints
                                                          bit14:cmdlist第13通道的中断
                                                          bit13:cmdlist第12通道的中断
                                                          bit12:cmdlist第11通道的中断
                                                          bit11:cmdlist第10通道的中断
                                                          bit10:cmdlist第9通道的中断
                                                          bit9:cmdlist第8通道的中断
                                                          bit8:cmdlist第7通道的中断
                                                          bit7:cmdlist第6通道的中断
                                                          bit6:cmdlist第5通道的中断
                                                          bit5:cmdlist第4通道的中断
                                                          bit4:cmdlist第3通道的中断
                                                          bit3:cmdlist第2通道的中断
                                                          bit2:cmdlist第1通道的中断
                                                          bit1:cmdlist第0通道的中断
                                                          bit0:rch_ce_ints */
        unsigned int  reserved        : 1;  /* bit[31]  : 保留 */
    } reg;
} SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_SDP_INTS_UNION
 结构说明  : MCU_SDP_INTS 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: MCU副屏中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_sdp_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                        bit29:dss_glb_ints中断
                                                        bit28:mmu_irpt_s,mmu安全中断
                                                        bit27:mmu_irpt_ns,mmu非安全中断
                                                        bit26:dbg_mctl_ints
                                                        bit25:dbg_wch1_ints
                                                        bit24:dbg_wch0_ints
                                                        bit23:dbg_rch7_ints
                                                        bit22:dbg_rch6_ints
                                                        bit21:dbg_rch5_ints
                                                        bit20:dbg_rch4_ints
                                                        bit19:dbg_rch3_ints
                                                        bit18:dbg_rch2_ints
                                                        bit17:dbg_rch1_ints
                                                        bit16:dbg_rch0_ints
                                                        bit15:itf1_ints
                                                        bit14:cmdlist第13通道的中断
                                                        bit13:cmdlist第12通道的中断
                                                        bit12:cmdlist第11通道的中断
                                                        bit11:cmdlist第10通道的中断
                                                        bit10:cmdlist第9通道的中断
                                                        bit9:cmdlist第8通道的中断
                                                        bit8:cmdlist第7通道的中断
                                                        bit7:cmdlist第6通道的中断
                                                        bit6:cmdlist第5通道的中断
                                                        bit5:cmdlist第4通道的中断
                                                        bit4:cmdlist第3通道的中断
                                                        bit3:cmdlist第2通道的中断
                                                        bit2:cmdlist第1通道的中断
                                                        bit1:cmdlist第0通道的中断
                                                        bit0:rch_ce_ints */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_START  (0)
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION
 结构说明  : MCU_SDP_INT_MSK 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: MCU副屏中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_sdp_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                           bit29:dss_glb_ints中断
                                                           bit28:mmu_irpt_s,mmu安全中断
                                                           bit27:mmu_irpt_ns,mmu非安全中断
                                                           bit26:dbg_mctl_ints
                                                           bit25:dbg_wch1_ints
                                                           bit24:dbg_wch0_ints
                                                           bit23:dbg_rch7_ints
                                                           bit22:dbg_rch6_ints
                                                           bit21:dbg_rch5_ints
                                                           bit20:dbg_rch4_ints
                                                           bit19:dbg_rch3_ints
                                                           bit18:dbg_rch2_ints
                                                           bit17:dbg_rch1_ints
                                                           bit16:dbg_rch0_ints
                                                           bit15:itf1_ints
                                                           bit14:cmdlist第13通道的中断
                                                           bit13:cmdlist第12通道的中断
                                                           bit12:cmdlist第11通道的中断
                                                           bit11:cmdlist第10通道的中断
                                                           bit10:cmdlist第9通道的中断
                                                           bit9:cmdlist第8通道的中断
                                                           bit8:cmdlist第7通道的中断
                                                           bit7:cmdlist第6通道的中断
                                                           bit6:cmdlist第5通道的中断
                                                           bit5:cmdlist第4通道的中断
                                                           bit4:cmdlist第3通道的中断
                                                           bit3:cmdlist第2通道的中断
                                                           bit2:cmdlist第1通道的中断
                                                           bit1:cmdlist第0通道的中断
                                                           bit0:rch_ce_ints */
        unsigned int  reserved        : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_OFF_INTS_UNION
 结构说明  : MCU_OFF_INTS 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: MCU离线中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_off_ints : 32; /* bit[0-31]: 中断状态寄存器，1表示有中断，0表示没有中断
                                                       bit31:dss_glb_ints中断
                                                       bit30:mmu_irpt_s,mmu安全中断
                                                       bit29:mmu_irpt_ns,mmu非安全中断
                                                       bit28:dbg_mctl_ints
                                                       bit27:dbg_wch1_ints
                                                       bit26:dbg_wch0_ints
                                                       bit25:dbg_rch7_ints
                                                       bit24:dbg_rch6_ints
                                                       bit23:dbg_rch5_ints
                                                       bit22:dbg_rch4_ints
                                                       bit21:dbg_rch3_ints
                                                       bit10:dbg_rch2_ints
                                                       bit19:dbg_rch1_ints
                                                       bit18:dbg_rch0_ints
                                                       bit17:wch1_ints wch1的frm_end中断
                                                       bit16:wch0_ints wch0的frm_end中断
                                                       bit15:wch0和wch1同时frm_end时产生的中断
                                                       bit14:cmdlist第13通道的中断
                                                       bit13:cmdlist第12通道的中断
                                                       bit12:cmdlist第11通道的中断
                                                       bit11:cmdlist第10通道的中断
                                                       bit10:cmdlist第9通道的中断
                                                       bit9:cmdlist第8通道的中断
                                                       bit8:cmdlist第7通道的中断
                                                       bit7:cmdlist第6通道的中断
                                                       bit6:cmdlist第5通道的中断
                                                       bit5:cmdlist第4通道的中断
                                                       bit4:cmdlist第3通道的中断
                                                       bit3:cmdlist第2通道的中断
                                                       bit2:cmdlist第1通道的中断
                                                       bit1:cmdlist第0通道的中断
                                                       bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_MCU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_START  (0)
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION
 结构说明  : MCU_OFF_INT_MSK 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: MCU离线中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_off_int_msk : 32; /* bit[0-31]: 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                          bit31:dss_glb_ints中断
                                                          bit30:mmu_irpt_s,mmu安全中断
                                                          bit29:mmu_irpt_ns,mmu非安全中断
                                                          bit28:dbg_mctl_ints
                                                          bit27:dbg_wch1_ints
                                                          bit26:dbg_wch0_ints
                                                          bit25:dbg_rch7_ints
                                                          bit24:dbg_rch6_ints
                                                          bit23:dbg_rch5_ints
                                                          bit22:dbg_rch4_ints
                                                          bit21:dbg_rch3_ints
                                                          bit10:dbg_rch2_ints
                                                          bit19:dbg_rch1_ints
                                                          bit18:dbg_rch0_ints
                                                          bit17:wch1_ints wch1的frm_end中断
                                                          bit16:wch0_ints wch0的frm_end中断
                                                          bit15:wch0和wch1同时frm_end时产生的中断
                                                          bit14:cmdlist第13通道的中断
                                                          bit13:cmdlist第12通道的中断
                                                          bit12:cmdlist第11通道的中断
                                                          bit11:cmdlist第10通道的中断
                                                          bit10:cmdlist第9通道的中断
                                                          bit9:cmdlist第8通道的中断
                                                          bit8:cmdlist第7通道的中断
                                                          bit7:cmdlist第6通道的中断
                                                          bit6:cmdlist第5通道的中断
                                                          bit5:cmdlist第4通道的中断
                                                          bit4:cmdlist第3通道的中断
                                                          bit3:cmdlist第2通道的中断
                                                          bit2:cmdlist第1通道的中断
                                                          bit1:cmdlist第0通道的中断
                                                          bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_PDP_INTS_UNION
 结构说明  : CPU_PDP_INTS 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: CPU主屏中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_pdp_ints : 31; /* bit[0-30]: 中断状态寄存器，1表示有中断，0表示没有中断
                                                       bit30:dss_glb_ints中断
                                                       bit29:mmu_irpt_s,mmu安全中断
                                                       bit28:mmu_irpt_ns,mmu非安全中断
                                                       bit27:dbg_mctl_ints
                                                       bit26:dbg_wch1_ints
                                                       bit25:dbg_wch0_ints
                                                       bit24:dbg_rch7_ints
                                                       bit23:dbg_rch6_ints
                                                       bit22:dbg_rch5_ints
                                                       bit21:dbg_rch4_ints
                                                       bit20:dbg_rch3_ints
                                                       bit19:dbg_rch2_ints
                                                       bit18:dbg_rch1_ints
                                                       bit17:dbg_rch0_ints
                                                       bit16:itf0_ints
                                                       bit15:dpp_ints
                                                       bit14:cmdlist第13通道的中断
                                                       bit13:cmdlist第12通道的中断
                                                       bit12:cmdlist第11通道的中断
                                                       bit11:cmdlist第10通道的中断
                                                       bit10:cmdlist第9通道的中断
                                                       bit9:cmdlist第8通道的中断
                                                       bit8:cmdlist第7通道的中断
                                                       bit7:cmdlist第6通道的中断
                                                       bit6:cmdlist第5通道的中断
                                                       bit5:cmdlist第4通道的中断
                                                       bit4:cmdlist第3通道的中断
                                                       bit3:cmdlist第2通道的中断
                                                       bit2:cmdlist第1通道的中断
                                                       bit1:cmdlist第0通道的中断
                                                       bit0:rch_ce_ints */
        unsigned int  reserved     : 1;  /* bit[31]  : 保留 */
    } reg;
} SOC_DSS_GLB_CPU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_START  (0)
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION
 结构说明  : CPU_PDP_INT_MSK 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: CPU主屏中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_pdp_int_msk : 31; /* bit[0-30]: 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                          bit30:dss_glb_ints中断
                                                          bit29:mmu_irpt_s,mmu安全中断
                                                          bit28:mmu_irpt_ns,mmu非安全中断
                                                          bit27:dbg_mctl_ints
                                                          bit26:dbg_wch1_ints
                                                          bit25:dbg_wch0_ints
                                                          bit24:dbg_rch7_ints
                                                          bit23:dbg_rch6_ints
                                                          bit22:dbg_rch5_ints
                                                          bit21:dbg_rch4_ints
                                                          bit20:dbg_rch3_ints
                                                          bit19:dbg_rch2_ints
                                                          bit18:dbg_rch1_ints
                                                          bit17:dbg_rch0_ints
                                                          bit16:itf0_ints
                                                          bit15:dpp_ints
                                                          bit14:cmdlist第13通道的中断
                                                          bit13:cmdlist第12通道的中断
                                                          bit12:cmdlist第11通道的中断
                                                          bit11:cmdlist第10通道的中断
                                                          bit10:cmdlist第9通道的中断
                                                          bit9:cmdlist第8通道的中断
                                                          bit8:cmdlist第7通道的中断
                                                          bit7:cmdlist第6通道的中断
                                                          bit6:cmdlist第5通道的中断
                                                          bit5:cmdlist第4通道的中断
                                                          bit4:cmdlist第3通道的中断
                                                          bit3:cmdlist第2通道的中断
                                                          bit2:cmdlist第1通道的中断
                                                          bit1:cmdlist第0通道的中断
                                                          bit0:rch_ce_ints */
        unsigned int  reserved        : 1;  /* bit[31]  : 保留 */
    } reg;
} SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_SDP_INTS_UNION
 结构说明  : CPU_SDP_INTS 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: CPU副屏中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_sdp_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                        bit29:dss_glb_ints中断
                                                        bit28:mmu_irpt_s,mmu安全中断
                                                        bit27:mmu_irpt_ns,mmu非安全中断
                                                        bit26:dbg_mctl_ints
                                                        bit25:dbg_wch1_ints
                                                        bit24:dbg_wch0_ints
                                                        bit23:dbg_rch7_ints
                                                        bit22:dbg_rch6_ints
                                                        bit21:dbg_rch5_ints
                                                        bit20:dbg_rch4_ints
                                                        bit19:dbg_rch3_ints
                                                        bit18:dbg_rch2_ints
                                                        bit17:dbg_rch1_ints
                                                        bit16:dbg_rch0_ints
                                                        bit15:itf1_ints
                                                        bit14:cmdlist第13通道的中断
                                                        bit13:cmdlist第12通道的中断
                                                        bit12:cmdlist第11通道的中断
                                                        bit11:cmdlist第10通道的中断
                                                        bit10:cmdlist第9通道的中断
                                                        bit9:cmdlist第8通道的中断
                                                        bit8:cmdlist第7通道的中断
                                                        bit7:cmdlist第6通道的中断
                                                        bit6:cmdlist第5通道的中断
                                                        bit5:cmdlist第4通道的中断
                                                        bit4:cmdlist第3通道的中断
                                                        bit3:cmdlist第2通道的中断
                                                        bit2:cmdlist第1通道的中断
                                                        bit1:cmdlist第0通道的中断
                                                        bit0:rch_ce_ints */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_START  (0)
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION
 结构说明  : CPU_SDP_INT_MSK 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: CPU副屏中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_sdp_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                           bit29:dss_glb_ints中断
                                                           bit28:mmu_irpt_s,mmu安全中断
                                                           bit27:mmu_irpt_ns,mmu非安全中断
                                                           bit26:dbg_mctl_ints
                                                           bit25:dbg_wch1_ints
                                                           bit24:dbg_wch0_ints
                                                           bit23:dbg_rch7_ints
                                                           bit22:dbg_rch6_ints
                                                           bit21:dbg_rch5_ints
                                                           bit20:dbg_rch4_ints
                                                           bit19:dbg_rch3_ints
                                                           bit18:dbg_rch2_ints
                                                           bit17:dbg_rch1_ints
                                                           bit16:dbg_rch0_ints
                                                           bit15:itf1_ints
                                                           bit14:cmdlist第13通道的中断
                                                           bit13:cmdlist第12通道的中断
                                                           bit12:cmdlist第11通道的中断
                                                           bit11:cmdlist第10通道的中断
                                                           bit10:cmdlist第9通道的中断
                                                           bit9:cmdlist第8通道的中断
                                                           bit8:cmdlist第7通道的中断
                                                           bit7:cmdlist第6通道的中断
                                                           bit6:cmdlist第5通道的中断
                                                           bit5:cmdlist第4通道的中断
                                                           bit4:cmdlist第3通道的中断
                                                           bit3:cmdlist第2通道的中断
                                                           bit2:cmdlist第1通道的中断
                                                           bit1:cmdlist第0通道的中断
                                                           bit0:rch_ce_ints */
        unsigned int  reserved        : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_OFF_INTS_UNION
 结构说明  : CPU_OFF_INTS 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: CPU离线中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_off_ints : 32; /* bit[0-31]: 中断状态寄存器，1表示有中断，0表示没有中断
                                                       bit31:dss_glb_ints中断
                                                       bit30:mmu_irpt_s,mmu安全中断
                                                       bit29:mmu_irpt_ns,mmu非安全中断
                                                       bit28:dbg_mctl_ints
                                                       bit27:dbg_wch1_ints
                                                       bit26:dbg_wch0_ints
                                                       bit25:dbg_rch7_ints
                                                       bit24:dbg_rch6_ints
                                                       bit23:dbg_rch5_ints
                                                       bit22:dbg_rch4_ints
                                                       bit21:dbg_rch3_ints
                                                       bit10:dbg_rch2_ints
                                                       bit19:dbg_rch1_ints
                                                       bit18:dbg_rch0_ints
                                                       bit17:wch1_ints wch1的frm_end中断
                                                       bit16:wch0_ints wch0的frm_end中断
                                                       bit15:wch0和wch1同时frm_end时产生的中断
                                                       bit14:cmdlist第13通道的中断
                                                       bit13:cmdlist第12通道的中断
                                                       bit12:cmdlist第11通道的中断
                                                       bit11:cmdlist第10通道的中断
                                                       bit10:cmdlist第9通道的中断
                                                       bit9:cmdlist第8通道的中断
                                                       bit8:cmdlist第7通道的中断
                                                       bit7:cmdlist第6通道的中断
                                                       bit6:cmdlist第5通道的中断
                                                       bit5:cmdlist第4通道的中断
                                                       bit4:cmdlist第3通道的中断
                                                       bit3:cmdlist第2通道的中断
                                                       bit2:cmdlist第1通道的中断
                                                       bit1:cmdlist第0通道的中断
                                                       bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_CPU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_START  (0)
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION
 结构说明  : CPU_OFF_INT_MSK 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: CPU离线中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_off_int_msk : 32; /* bit[0-31]: 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                          bit31:dss_glb_ints中断
                                                          bit30:mmu_irpt_s,mmu安全中断
                                                          bit29:mmu_irpt_ns,mmu非安全中断
                                                          bit28:dbg_mctl_ints
                                                          bit27:dbg_wch1_ints
                                                          bit26:dbg_wch0_ints
                                                          bit25:dbg_rch7_ints
                                                          bit24:dbg_rch6_ints
                                                          bit23:dbg_rch5_ints
                                                          bit22:dbg_rch4_ints
                                                          bit21:dbg_rch3_ints
                                                          bit10:dbg_rch2_ints
                                                          bit19:dbg_rch1_ints
                                                          bit18:dbg_rch0_ints
                                                          bit17:wch1_ints wch1的frm_end中断
                                                          bit16:wch0_ints wch0的frm_end中断
                                                          bit15:wch0和wch1同时frm_end时产生的中断
                                                          bit14:cmdlist第13通道的中断
                                                          bit13:cmdlist第12通道的中断
                                                          bit12:cmdlist第11通道的中断
                                                          bit11:cmdlist第10通道的中断
                                                          bit10:cmdlist第9通道的中断
                                                          bit9:cmdlist第8通道的中断
                                                          bit8:cmdlist第7通道的中断
                                                          bit7:cmdlist第6通道的中断
                                                          bit6:cmdlist第5通道的中断
                                                          bit5:cmdlist第4通道的中断
                                                          bit4:cmdlist第3通道的中断
                                                          bit3:cmdlist第2通道的中断
                                                          bit2:cmdlist第1通道的中断
                                                          bit1:cmdlist第0通道的中断
                                                          bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_MCTL_INTS_UNION
 结构说明  : DBG_MCTL_INTS 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: 主控中断指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_mctl_ints : 8;  /* bit[0-7] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                        bti7:ctl7_start
                                                        bti6:ctl6_start
                                                        bti5:ctl5_start
                                                        bti4:ctl4_start
                                                        bti3:ctl3_start
                                                        bti2:ctl2_start
                                                        bti1:ctl1_start
                                                        bti0:ctl0_start */
        unsigned int  reserved      : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_START  (0)
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION
 结构说明  : DBG_MCTL_INT_MSK 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 主控中断屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_mctl_int_msk : 8;  /* bit[0-7] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                           bti7:ctl7_start
                                                           bti6:ctl6_start
                                                           bti5:ctl5_start
                                                           bti4:ctl4_start
                                                           bti3:ctl3_start
                                                           bti2:ctl2_start
                                                           bti1:ctl1_start
                                                           bti0:ctl0_start */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_WCH0_INTS_UNION
 结构说明  : DBG_WCH0_INTS 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 写通道0中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch0_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13: wch块结束中断
                                                         bit12~2: reserve
                                                         bit1: dma帧结束中断
                                                         bit0: afbce的resp_err中断上报 */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_START  (0)
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION
 结构说明  : DBG_WCH0_INT_MSK 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 写通道0中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch0_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13: wch块结束中断
                                                            bit12~2: reserve
                                                            bit1: dma帧结束中断
                                                            bit0: afbce的resp_err中断上报 */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_WCH1_INTS_UNION
 结构说明  : DBG_WCH1_INTS 寄存器结构定义。地址偏移量:0x24C，初值:0x00000000，宽度:32
 寄存器说明: 写通道1中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch1_ints : 14; /* bit[0-13] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit13: wch块结束中断
                                                         bit12~2: reserve
                                                         bit1: dma帧结束中断
                                                         bit0: afbce的resp_err中断上报 */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_START  (0)
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION
 结构说明  : DBG_WCH1_INT_MSK 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: 写通道1中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch1_int_msk : 14; /* bit[0-13] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit13: wch块结束中断
                                                            bit12~2: reserve
                                                            bit1: dma帧结束中断
                                                            bit0: afbce的resp_err中断上报 */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH0_INTS_UNION
 结构说明  : DBG_RCH0_INTS 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: 读通道0中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch0_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION
 结构说明  : DBG_RCH0_INT_MSK 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: 读通道0中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch0_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH1_INTS_UNION
 结构说明  : DBG_RCH1_INTS 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: 读通道1中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch1_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION
 结构说明  : DBG_RCH1_INT_MSK 寄存器结构定义。地址偏移量:0x260，初值:0x00000000，宽度:32
 寄存器说明: 读通道1中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch1_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH2_INTS_UNION
 结构说明  : DBG_RCH2_INTS 寄存器结构定义。地址偏移量:0x264，初值:0x00000000，宽度:32
 寄存器说明: 读通道2中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch2_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION
 结构说明  : DBG_RCH2_INT_MSK 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: 读通道2中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch2_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH3_INTS_UNION
 结构说明  : DBG_RCH3_INTS 寄存器结构定义。地址偏移量:0x26C，初值:0x00000000，宽度:32
 寄存器说明: 读通道3中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch3_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION
 结构说明  : DBG_RCH3_INT_MSK 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: 读通道3中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch3_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH4_INTS_UNION
 结构说明  : DBG_RCH4_INTS 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: 读通道4中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch4_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION
 结构说明  : DBG_RCH4_INT_MSK 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: 读通道4中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch4_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH5_INTS_UNION
 结构说明  : DBG_RCH5_INTS 寄存器结构定义。地址偏移量:0x27C，初值:0x00000000，宽度:32
 寄存器说明: 读通道5中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch5_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION
 结构说明  : DBG_RCH5_INT_MSK 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: 读通道5中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch5_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH6_INTS_UNION
 结构说明  : DBG_RCH6_INTS 寄存器结构定义。地址偏移量:0x284，初值:0x00000000，宽度:32
 寄存器说明: 读通道6中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch6_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION
 结构说明  : DBG_RCH6_INT_MSK 寄存器结构定义。地址偏移量:0x288，初值:0x00000000，宽度:32
 寄存器说明: 读通道6中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch6_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH7_INTS_UNION
 结构说明  : DBG_RCH7_INTS 寄存器结构定义。地址偏移量:0x28C，初值:0x00000000，宽度:32
 寄存器说明: 读通道7中断指示（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch7_ints : 30; /* bit[0-29] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                         bit14~29: reserve
                                                         bit13: CE LUT1读写冲突
                                                         bit12: CE LUT0读写冲突
                                                         bit11: CE 直方图1读写冲突
                                                         bit10: CE 直方图0读写冲突
                                                         bit9: rdma帧结束中断
                                                         bit8: rch帧结束中断
                                                         bit5~7:rdma内部err中断
                                                         bit4: rdma的resp_err中断
                                                         bit0~3:afbcd的中断 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION
 结构说明  : DBG_RCH7_INT_MSK 寄存器结构定义。地址偏移量:0x290，初值:0x00000000，宽度:32
 寄存器说明: 读通道7中断屏蔽（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch7_int_msk : 30; /* bit[0-29] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                            bit14~29: reserve
                                                            bit13: CE LUT1读写冲突
                                                            bit12: CE LUT0读写冲突
                                                            bit11: CE 直方图1读写冲突
                                                            bit10: CE 直方图0读写冲突
                                                            bit9: rdma帧结束中断
                                                            bit8: rch帧结束中断
                                                            bit5~7:rdma内部err中断
                                                            bit4: rdma的resp_err中断
                                                            bit0~3:afbcd的中断 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_INTS_UNION
 结构说明  : INTS 寄存器结构定义。地址偏移量:0x294，初值:0x00000000，宽度:32
 寄存器说明: GLB中断（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_ints : 6;  /* bit[0-5] : 中断状态寄存器，1表示有中断，0表示没有中断
                                                       bit5:bus_dbg_int GLB内部的BUS_DBG模块中断
                                                       bit4:crc_sum_int GLB内部的CRC模块中断
                                                       bit3:crc_itf1_int GLB内部的CRC模块中断
                                                       bit2:crc_itf0_int GLB内部的CRC模块中断
                                                       bit1:crc_ov1_int GLB内部的CRC模块中断
                                                       bit0:crc_ov0_int GLB内部的CRC模块中断 */
        unsigned int  reserved     : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_GLB_INTS_UNION;
#endif
#define SOC_DSS_GLB_INTS_dss_glb_ints_START  (0)
#define SOC_DSS_GLB_INTS_dss_glb_ints_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_INT_MSK_UNION
 结构说明  : INT_MSK 寄存器结构定义。地址偏移量:0x298，初值:0x00000000，宽度:32
 寄存器说明: GLB中断（调试用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_int_msk : 6;  /* bit[0-5] : 中断屏蔽寄存器，1表示屏蔽中断，0表示不屏蔽中断
                                                          bit5:bus_dbg_int GLB内部的BUS_DBG模块中断
                                                          bit4:crc_sum_int GLB内部的CRC模块中断
                                                          bit3:crc_itf1_int GLB内部的CRC模块中断
                                                          bit2:crc_itf0_int GLB内部的CRC模块中断
                                                          bit1:crc_ov1_int GLB内部的CRC模块中断
                                                          bit0:crc_ov0_int GLB内部的CRC模块中断 */
        unsigned int  reserved        : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_GLB_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_START  (0)
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MODULE_CLK_SEL_UNION
 结构说明  : MODULE_CLK_SEL 寄存器结构定义。地址偏移量:0x0300，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块软件时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                         1：表示强制打开时钟。
                                                         0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                         bit0: cmdlist模块的axi时钟域
                                                         bit1：vbif模块的core时钟域
                                                         bit2：vbif模块的axi时钟域
                                                         bit3：apb模块的pclk时钟域
                                                         bit4：apb模块的pxl0时钟域
                                                         bit5：apb模块的axi时钟域
                                                         bit6：apb模块的pxl1时钟域
                                                         bit7：apb模块的core时钟域
                                                         bit8：rch0模块的core时钟域
                                                         bit9：rch1模块的core时钟域
                                                         bit10：rch2模块的core时钟域
                                                         bit11：rch3模块的core时钟域
                                                         bit12：rch4模块的core时钟域
                                                         bit13：rch5模块的core时钟域
                                                         bit14：rch6模块的core时钟域
                                                         bit15：rch7模块的core时钟域
                                                         bit16：wch0模块的core时钟域
                                                         bit17：wch1模块的core时钟域
                                                         bit18：mctl模块的core时钟域
                                                         bit19：sw0模块的core时钟域
                                                         bit20：sw1模块的core时钟域
                                                         bit21：ov0模块的core时钟域
                                                         bit22：ov1模块的core时钟域
                                                         bit23：ov2模块的core时钟域
                                                         bit24：ov3模块的core时钟域
                                                         bit25：vbif1模块的axi时钟域
                                                         bit26：vbif1模块的core时钟域
                                                         bit27：dbg模块的core/axi/apb时钟域
                                                         bit28~31：reserve */
    } reg;
} SOC_DSS_GLB_MODULE_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_START  (0)
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MODULE_CLK_EN_UNION
 结构说明  : MODULE_CLK_EN 寄存器结构定义。地址偏移量:0x304，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块软件时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                        1：表示软件时钟使能有效，允许硬件开钟
                                                        0：表示软件时钟使能无效，禁止硬件开钟
                                                        bit0: cmdlist模块的axi时钟域
                                                        bit1：vbif模块的core时钟域
                                                        bit2：vbif模块的axi时钟域
                                                        bit3：apb模块的pclk时钟域
                                                        bit4：apb模块的pxl0时钟域
                                                        bit5：apb模块的axi时钟域
                                                        bit6：apb模块的pxl1时钟域
                                                        bit7：apb模块的core时钟域
                                                        bit8：rch0模块的core时钟域
                                                        bit9：rch1模块的core时钟域
                                                        bit10：rch2模块的core时钟域
                                                        bit11：rch3模块的core时钟域
                                                        bit12：rch4模块的core时钟域
                                                        bit13：rch5模块的core时钟域
                                                        bit14：rch6模块的core时钟域
                                                        bit15：rch7模块的core时钟域
                                                        bit16：wch0模块的core时钟域
                                                        bit17：wch1模块的core时钟域
                                                        bit18：mctl模块的core时钟域
                                                        bit19：sw0模块的core时钟域
                                                        bit20：sw1模块的core时钟域
                                                        bit21：ov0模块的core时钟域
                                                        bit22：ov1模块的core时钟域
                                                        bit23：ov2模块的core时钟域
                                                        bit24：ov3模块的core时钟域
                                                        bit25：vbif1模块的axi时钟域
                                                        bit26：vbif1模块的core时钟域
                                                        bit27：dbg模块的core/axi/apb时钟域
                                                        bit28~31：reserve */
    } reg;
} SOC_DSS_GLB_MODULE_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_START  (0)
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MODULE1_CLK_SEL_UNION
 结构说明  : MODULE1_CLK_SEL 寄存器结构定义。地址偏移量:0x308，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块软件时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module1_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                          1：表示强制打开时钟。
                                                          0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                          bit0~bit1：保留
                                                          bit2：vscf模块的core时钟域
                                                          bit3：dbuf0模块的core时钟域
                                                          bit4：dbuf1模块的core时钟域
                                                          bit5：dbuf0模块的pxl0时钟域
                                                          bit6：dpp模块的pxl0时钟域
                                                          bit7：ifbc模块的pxl0时钟域
                                                          bit8：ifbc模块的pxl0 2分频时钟域
                                                          bit9：ifbc模块的pxl0 4分频时钟域
                                                          bit10：dbuf模块的pxl1时钟域
                                                          bit11：dbg模块的pxl0/pxl1时钟域 */
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_START  (0)
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_MODULE1_CLK_EN_UNION
 结构说明  : MODULE1_CLK_EN 寄存器结构定义。地址偏移量:0x30C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块软件时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module1_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                         1：表示软件时钟使能有效，允许硬件开钟
                                                         0：表示软件时钟使能无效，禁止硬件开钟
                                                         bit0~bit1：保留
                                                         bit2：vscf模块的core时钟域
                                                         bit3：dbuf0模块的core时钟域
                                                         bit4：dbuf1模块的core时钟域
                                                         bit5：dbuf0模块的pxl0时钟域
                                                         bit6：dpp模块的pxl0时钟域
                                                         bit7：ifbc模块的pxl0时钟域
                                                         bit8：ifbc模块的pxl0 2分频时钟域
                                                         bit9：ifbc模块的pxl0 4分频时钟域
                                                         bit10：dbuf模块的pxl1时钟域
                                                         bit11：dbg模块的pxl0/pxl1时钟域 */
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_START  (0)
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_GLB0_DBG_SEL_UNION
 结构说明  : GLB0_DBG_SEL 寄存器结构定义。地址偏移量:0x310，初值:0x00000000，宽度:32
 寄存器说明: 调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb0_core_dbg_sel : 4;  /* bit[0-3]  : core时钟域debug信号选择。
                                                             0：选择ov2 dbg输出
                                                             1：选择ov3 dbg输出
                                                             2：选择rch0 dbg输出
                                                             3：选择rch1 dbg输出
                                                             4：选择rch2 dbg输出
                                                             5：选择rch3 dbg输出
                                                             6：选择rch4 dbg输出
                                                             7：选择rch5 dbg输出
                                                             8：选择rch6 dbg输出
                                                             9：选择rch7 dbg输出
                                                             10：选择wch0 dbg输出
                                                             11：选择wch1 dbg输出
                                                             12：选择ov2 dbg输出
                                                             13：选择ov3 dbg输出
                                                             14：选择vbif core时钟域dbg输出
                                                             其它：选择vbif1 core时钟域dbg输出 */
        unsigned int  dss_sum_dbg_sel   : 2;  /* bit[4-5]  : 按时钟域，再和DISP输入的disp_dbg一起进行debug信号选择。
                                                             0：core时钟域dbg输出
                                                             1：axi时钟域dbg输出
                                                             2：axi_mm时钟域dbg输出
                                                             其它：disp的dbg输出 */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  glb0_axi_dbg_sel  : 2;  /* bit[8-9]  : axi时钟域debug信号选择。
                                                             0：选择vbif axi时钟域dbg输出
                                                             其它：选择cmdlist dbg输出 */
        unsigned int  reserved_1        : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_DSS_GLB_GLB0_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_START  (0)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_END    (3)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_START    (4)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_END      (5)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_START   (8)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_END     (9)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_GLB1_DBG_SEL_UNION
 结构说明  : GLB1_DBG_SEL 寄存器结构定义。地址偏移量:0x314，初值:0x00000000，宽度:32
 寄存器说明: 调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb1_core_dbg_sel : 2;  /* bit[0-1]  : core时钟域debug信号选择。
                                                             0：选择scf dbg输出
                                                             1：选择dbuf0 dbg输出
                                                             其它：选择dbuf1 dbg输出 */
        unsigned int  glb1_clk_dbg_sel  : 2;  /* bit[2-3]  : 按时钟域进行debug信号选择。
                                                             0：core时钟域dbg输出
                                                             1：pxl0时钟域dbg输出
                                                             其它：pxl1时钟域dbg输出 */
        unsigned int  reserved_0        : 4;  /* bit[4-7]  : 保留 */
        unsigned int  glb1_pxl0_dbg_sel : 2;  /* bit[8-9]  : pxl0时钟域debug信号选择。
                                                             0：选择dpp dbg输出
                                                             1：选择ifbc dbg输出
                                                             其它：选择itf1 dbg输出 */
        unsigned int  reserved_1        : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_DSS_GLB_GLB1_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_START  (0)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_END    (1)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_START   (2)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_END     (3)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_START  (8)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_IRQ_CPU_UNION
 结构说明  : DBG_IRQ_CPU 寄存器结构定义。地址偏移量:0x320，初值:0x00000000，宽度:32
 寄存器说明: CPU中断调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_cpu : 3;  /* bit[0-2] : bit0:dbg_cpu_pdp;
                                                      bit1:dbg_cpu_sdp;
                                                      bit2:dbg_cpu_offline; */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_IRQ_CPU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_START  (0)
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DBG_IRQ_MCU_UNION
 结构说明  : DBG_IRQ_MCU 寄存器结构定义。地址偏移量:0x324，初值:0x00000000，宽度:32
 寄存器说明: MCU中断调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_mcu : 3;  /* bit[0-2] : bit0:dbg_mcu_pdp;
                                                      bit1:dbg_mcu_sdp;
                                                      bit2:dbg_mcu_offline; */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_GLB_DBG_IRQ_MCU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_START  (0)
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_TP_SEL_UNION
 结构说明  : TP_SEL 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: TP选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_sel   : 2;  /* bit[0-1] : 0：表示不选通数据输出
                                                   1：表示选通dsi1的数据
                                                   2：表示选通dsi0的数据 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_GLB_TP_SEL_UNION;
#endif
#define SOC_DSS_GLB_TP_SEL_tp_sel_START    (0)
#define SOC_DSS_GLB_TP_SEL_tp_sel_END      (1)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_DBG_LDI0_UNION
 结构说明  : CRC_DBG_LDI0 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: LDI0的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ldi0 : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI0_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_START  (0)
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_DBG_LDI1_UNION
 结构说明  : CRC_DBG_LDI1 寄存器结构定义。地址偏移量:0x0408，初值:0x00000000，宽度:32
 寄存器说明: LDI1的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ldi1 : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI1_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_START  (0)
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_LDI0_EN_UNION
 结构说明  : CRC_LDI0_EN 寄存器结构定义。地址偏移量:0x040C，初值:0x00000000，宽度:32
 寄存器说明: LDI0的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi0_en : 1;  /* bit[0-0] : 保留 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_LDI0_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_START  (0)
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_LDI0_FRM_UNION
 结构说明  : CRC_LDI0_FRM 寄存器结构定义。地址偏移量:0x0410，初值:0x00000000，宽度:32
 寄存器说明: LDI0上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi0_frm : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_LDI0_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_START  (0)
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_LDI1_EN_UNION
 结构说明  : CRC_LDI1_EN 寄存器结构定义。地址偏移量:0x0414，初值:0x00000000，宽度:32
 寄存器说明: LDI1的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi1_en : 1;  /* bit[0-0] : 保留 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_LDI1_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_START  (0)
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_CRC_LDI1_FRM_UNION
 结构说明  : CRC_LDI1_FRM 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: LDI1上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi1_frm : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_GLB_CRC_LDI1_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_START  (0)
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_MEM_CTRL_UNION
 结构说明  : DSS_MEM_CTRL 寄存器结构定义。地址偏移量:0x0600，初值:0x01A800A8，宽度:32
 寄存器说明: CPU读写memory使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_spram_ctrl : 16; /* bit[0-15] : 调试用寄存器
                                                          Single Port类型MEM低功耗软件配置：
                                                          [15:11]:reserved;
                                                          [10:9]:SPMB_WTSEL，默认为2'b00;
                                                          [8:7]: SPMB_RTSEL，默认为2'b01;
                                                          [6:5]: SPSB WTSEL,默认为2'b01;
                                                          [4:3]: SPSB RTSEL,默认为2'b01;
                                                          [2:0]: reserved; */
        unsigned int  dss_tpram_ctrl : 16; /* bit[16-31]: 调试用寄存器
                                                          Two Port类型MEM低功耗软件配置：
                                                          [15:10]:reserved;
                                                          [9:7]: KP,默认为3'b011;
                                                          [6:5]: WCT,默认为2'b01;
                                                          [4:3]: RCT,默认为2'b01;
                                                          [2:0]: reserved; */
    } reg;
} SOC_DSS_GLB_DSS_MEM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_START  (0)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_END    (15)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_START  (16)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_GLB_DSS_PM_CTRL_UNION
 结构说明  : DSS_PM_CTRL 寄存器结构定义。地址偏移量:0x0604，初值:0x00002009，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_pm_ctrl : 31; /* bit[0-30]: 调试用寄存器
                                                      [30] slp_mode 模式选择，1 slp模式，0 dslp模式
                                                      [29:26]:reserved;
                                                      [25:23] SLP/DSLP模式t(d)slp延时寄存器，参考配置为0（1个cycle） 
                                                      [22:20] SLP/DSLP模式t(d)slpx延时寄存器，参考配置为0（1个cycle） 
                                                      [19:17] SLP/DSLP模式tx(d)slp延时寄存器，参考配置为0（1个cycle） 
                                                      [16:13] SLP/DSLP模式t(d)slpwk延时寄存器，参考配置为1（2个cycle） 
                                                      [12:10] SD模式tsd延时寄存器，参考配置为0（1个cycle） 
                                                      [9:7] SD模式tsdx延时寄存器，参考配置为0 （1个cycle） 
                                                      [6:4] SD模式txsd延时寄存器，参考配置为0 （1个cycle） 
                                                      [3:0] SD模式tsdwk延时寄存器，参考配置为9（10个cycle）  */
        unsigned int  reserved    : 1;  /* bit[31]  : 保留 */
    } reg;
} SOC_DSS_GLB_DSS_PM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_START  (0)
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_END    (30)






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

#endif /* end of soc_dss_glb_interface.h */
