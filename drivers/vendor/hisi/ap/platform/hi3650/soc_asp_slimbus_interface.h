/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asp_slimbus_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:17
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASP_SLIMBUS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_SLIMBUS_INTERFACE_H__
#define __SOC_ASP_SLIMBUS_INTERFACE_H__

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
/* 寄存器说明：set the required operation mode of the SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_MODE_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ADDR(base)        ((base) + (0x000))

/* 寄存器说明：change Enumeration Address of the SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_EA_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_EA_ADDR(base)          ((base) + (0x004))

/* 寄存器说明：set Present Rates and Transport Protocols supported by the Generic device implemented in the SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_PR_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_PR_ADDR(base)          ((base) + (0x008))

/* 寄存器说明：to change configuration of the Framer device implemented in SLIMBUS_MANAGER.
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_FR_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_FR_ADDR(base)          ((base) + (0x00C))

/* 寄存器说明：change configuration data ports of the Generic device implemented in SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_DPORT_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_ADDR(base)       ((base) + (0x010))

/* 寄存器说明：change configuration cports of the Generic device implemented in SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_CPORT_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_ADDR(base)       ((base) + (0x014))

/* 寄存器说明：change part of Enumeration address of each of device implemented in SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_EA2_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_EA2_ADDR(base)         ((base) + (0x018))

/* 寄存器说明：define DMA thresholds for Source and Sink data ports.
   位域定义UNION结构:  SOC_ASP_SLIMBUS_CONFIG_THR_UNION */
#define SOC_ASP_SLIMBUS_CONFIG_THR_ADDR(base)         ((base) + (0x01C))

/* 寄存器说明：control RX_FIFO, TX_FIFO, control the UNFREEZE function, and confirm the IP configuration programmed using CONFIG registers
   位域定义UNION结构:  SOC_ASP_SLIMBUS_COMMAND_UNION */
#define SOC_ASP_SLIMBUS_COMMAND_ADDR(base)            ((base) + (0x020))

/* 寄存器说明：check the SLIMBUS_MANAGER status
   位域定义UNION结构:  SOC_ASP_SLIMBUS_STATE_UNION */
#define SOC_ASP_SLIMBUS_STATE_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：check status of Core and Device-specific Information Elements implemented in SLIMBUS_MANAGER
   位域定义UNION结构:  SOC_ASP_SLIMBUS_IE_STATE_UNION */
#define SOC_ASP_SLIMBUS_IE_STATE_ADDR(base)           ((base) + (0x028))

/* 寄存器说明：notify about current level of bandwidth used in the Message Channel, and to configure number of superframes in a row for which messages channel usage is being monitored to not exceed 75% bandwidth.
   位域定义UNION结构:  SOC_ASP_SLIMBUS_MCH_USAGE_UNION */
#define SOC_ASP_SLIMBUS_MCH_USAGE_ADDR(base)          ((base) + (0x02C))

/* 寄存器说明：defines which interrupt sources, related with TX_FIFO and RX_FIFO and internal state of the IP are enabled. This register also contains the main interrupt enable bit which enables/disables all interrupt sources
   位域定义UNION结构:  SOC_ASP_SLIMBUS_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_INT_EN_ADDR(base)             ((base) + (0x038))

/* 寄存器说明：shows the interrupt status of the SLIMBUS_MANAGER. It contains the interrupt requests related with TX_FIFO and RX_FIFO, Data Ports and the IP internal state
   位域定义UNION结构:  SOC_ASP_SLIMBUS_INT_UNION */
#define SOC_ASP_SLIMBUS_INT_ADDR(base)                ((base) + (0x03C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_SLIMBUS_MC_FIFO_UNION */
#define SOC_ASP_SLIMBUS_MC_FIFO_ADDR(base)            ((base) + (0x040～0x07C))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P0_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P0_INT_EN_ADDR(base)          ((base) + (0x080))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P4_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P4_INT_EN_ADDR(base)          ((base) + (0x084))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P8_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P8_INT_EN_ADDR(base)          ((base) + (0x088))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P12_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P12_INT_EN_ADDR(base)         ((base) + (0x08C))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P16_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P16_INT_EN_ADDR(base)         ((base) + (0x090))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P20_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P20_INT_EN_ADDR(base)         ((base) + (0x094))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P24_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P24_INT_EN_ADDR(base)         ((base) + (0x098))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P28_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P28_INT_EN_ADDR(base)         ((base) + (0x09C))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P32_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P32_INT_EN_ADDR(base)         ((base) + (0x0A0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P36_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P36_INT_EN_ADDR(base)         ((base) + (0x0A4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P40_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P40_INT_EN_ADDR(base)         ((base) + (0x0A8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P44_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P44_INT_EN_ADDR(base)         ((base) + (0x0AC))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P48_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P48_INT_EN_ADDR(base)         ((base) + (0x0B0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P52_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P52_INT_EN_ADDR(base)         ((base) + (0x0B4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P56_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P56_INT_EN_ADDR(base)         ((base) + (0x0B8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P60_INT_EN_UNION */
#define SOC_ASP_SLIMBUS_P60_INT_EN_ADDR(base)         ((base) + (0x0BC))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P0_INT_UNION */
#define SOC_ASP_SLIMBUS_P0_INT_ADDR(base)             ((base) + (0x0C0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P4_INT_UNION */
#define SOC_ASP_SLIMBUS_P4_INT_ADDR(base)             ((base) + (0x0C4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P8_INT_UNION */
#define SOC_ASP_SLIMBUS_P8_INT_ADDR(base)             ((base) + (0x0C8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P12_INT_UNION */
#define SOC_ASP_SLIMBUS_P12_INT_ADDR(base)            ((base) + (0x0CC))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P16_INT_UNION */
#define SOC_ASP_SLIMBUS_P16_INT_ADDR(base)            ((base) + (0x0D0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P20_INT_UNION */
#define SOC_ASP_SLIMBUS_P20_INT_ADDR(base)            ((base) + (0x0D4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P24_INT_UNION */
#define SOC_ASP_SLIMBUS_P24_INT_ADDR(base)            ((base) + (0x0D8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P28_INT_UNION */
#define SOC_ASP_SLIMBUS_P28_INT_ADDR(base)            ((base) + (0x0DC))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P32_INT_UNION */
#define SOC_ASP_SLIMBUS_P32_INT_ADDR(base)            ((base) + (0x0E0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P36_INT_UNION */
#define SOC_ASP_SLIMBUS_P36_INT_ADDR(base)            ((base) + (0x0E4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P40_INT_UNION */
#define SOC_ASP_SLIMBUS_P40_INT_ADDR(base)            ((base) + (0x0E8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P44_INT_UNION */
#define SOC_ASP_SLIMBUS_P44_INT_ADDR(base)            ((base) + (0x0EC))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P48_INT_UNION */
#define SOC_ASP_SLIMBUS_P48_INT_ADDR(base)            ((base) + (0x0F0))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P52_INT_UNION */
#define SOC_ASP_SLIMBUS_P52_INT_ADDR(base)            ((base) + (0x0F4))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P56_INT_UNION */
#define SOC_ASP_SLIMBUS_P56_INT_ADDR(base)            ((base) + (0x0F8))

/* 寄存器说明：each register contains data for 4 consecutive data ports
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P60_INT_UNION */
#define SOC_ASP_SLIMBUS_P60_INT_ADDR(base)            ((base) + (0x0FC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P0_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P0_STATE_0_ADDR(base)         ((base) + (0x100))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P0_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P0_STATE_1_ADDR(base)         ((base) + (0x104))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P1_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P1_STATE_0_ADDR(base)         ((base) + (0x108))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P1_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P1_STATE_1_ADDR(base)         ((base) + (0x10C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P2_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P2_STATE_0_ADDR(base)         ((base) + (0x110))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P2_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P2_STATE_1_ADDR(base)         ((base) + (0x114))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P3_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P3_STATE_0_ADDR(base)         ((base) + (0x118))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P3_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P3_STATE_1_ADDR(base)         ((base) + (0x11C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P4_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P4_STATE_0_ADDR(base)         ((base) + (0x120))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P4_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P4_STATE_1_ADDR(base)         ((base) + (0x124))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P5_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P5_STATE_0_ADDR(base)         ((base) + (0x128))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P5_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P5_STATE_1_ADDR(base)         ((base) + (0x12C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P6_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P6_STATE_0_ADDR(base)         ((base) + (0x130))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P6_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P6_STATE_1_ADDR(base)         ((base) + (0x134))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P7_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P7_STATE_0_ADDR(base)         ((base) + (0x138))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P7_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P7_STATE_1_ADDR(base)         ((base) + (0x13C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P8_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P8_STATE_0_ADDR(base)         ((base) + (0x140))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P8_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P8_STATE_1_ADDR(base)         ((base) + (0x144))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P9_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P9_STATE_0_ADDR(base)         ((base) + (0x148))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P9_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P9_STATE_1_ADDR(base)         ((base) + (0x14C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P10_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P10_STATE_0_ADDR(base)        ((base) + (0x150))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P10_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P10_STATE_1_ADDR(base)        ((base) + (0x154))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P11_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P11_STATE_0_ADDR(base)        ((base) + (0x158))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P11_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P11_STATE_1_ADDR(base)        ((base) + (0x15C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P12_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P12_STATE_0_ADDR(base)        ((base) + (0x160))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P12_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P12_STATE_1_ADDR(base)        ((base) + (0x164))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P13_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P13_STATE_0_ADDR(base)        ((base) + (0x168))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P13_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P13_STATE_1_ADDR(base)        ((base) + (0x16C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P14_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P14_STATE_0_ADDR(base)        ((base) + (0x170))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P14_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P14_STATE_1_ADDR(base)        ((base) + (0x174))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P15_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P15_STATE_0_ADDR(base)        ((base) + (0x178))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P15_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P15_STATE_1_ADDR(base)        ((base) + (0x17C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P16_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P16_STATE_0_ADDR(base)        ((base) + (0x180))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P16_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P16_STATE_1_ADDR(base)        ((base) + (0x184))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P17_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P17_STATE_0_ADDR(base)        ((base) + (0x188))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P17_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P17_STATE_1_ADDR(base)        ((base) + (0x18C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P18_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P18_STATE_0_ADDR(base)        ((base) + (0x190))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P18_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P18_STATE_1_ADDR(base)        ((base) + (0x194))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P19_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P19_STATE_0_ADDR(base)        ((base) + (0x198))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P19_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P19_STATE_1_ADDR(base)        ((base) + (0x19C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P20_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P20_STATE_0_ADDR(base)        ((base) + (0x1A0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P20_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P20_STATE_1_ADDR(base)        ((base) + (0x1A4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P21_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P21_STATE_0_ADDR(base)        ((base) + (0x1A8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P21_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P21_STATE_1_ADDR(base)        ((base) + (0x1AC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P22_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P22_STATE_0_ADDR(base)        ((base) + (0x1B0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P22_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P22_STATE_1_ADDR(base)        ((base) + (0x1B4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P23_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P23_STATE_0_ADDR(base)        ((base) + (0x1B8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P23_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P23_STATE_1_ADDR(base)        ((base) + (0x1BC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P24_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P24_STATE_0_ADDR(base)        ((base) + (0x1C0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P24_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P24_STATE_1_ADDR(base)        ((base) + (0x1C4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P25_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P25_STATE_0_ADDR(base)        ((base) + (0x1C8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P25_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P25_STATE_1_ADDR(base)        ((base) + (0x1CC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P26_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P26_STATE_0_ADDR(base)        ((base) + (0x1D0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P26_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P26_STATE_1_ADDR(base)        ((base) + (0x1D4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P27_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P27_STATE_0_ADDR(base)        ((base) + (0x1D8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P27_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P27_STATE_1_ADDR(base)        ((base) + (0x1DC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P28_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P28_STATE_0_ADDR(base)        ((base) + (0x1E0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P28_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P28_STATE_1_ADDR(base)        ((base) + (0x1E4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P29_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P29_STATE_0_ADDR(base)        ((base) + (0x1E8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P29_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P29_STATE_1_ADDR(base)        ((base) + (0x1EC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P30_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P30_STATE_0_ADDR(base)        ((base) + (0x1F0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P30_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P30_STATE_1_ADDR(base)        ((base) + (0x1F4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P31_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P31_STATE_0_ADDR(base)        ((base) + (0x1F8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P31_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P31_STATE_1_ADDR(base)        ((base) + (0x1FC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P32_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P32_STATE_0_ADDR(base)        ((base) + (0x200))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P32_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P32_STATE_1_ADDR(base)        ((base) + (0x204))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P33_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P33_STATE_0_ADDR(base)        ((base) + (0x208))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P33_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P33_STATE_1_ADDR(base)        ((base) + (0x20C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P34_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P34_STATE_0_ADDR(base)        ((base) + (0x210))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P34_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P34_STATE_1_ADDR(base)        ((base) + (0x214))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P35_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P35_STATE_0_ADDR(base)        ((base) + (0x218))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P35_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P35_STATE_1_ADDR(base)        ((base) + (0x21C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P36_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P36_STATE_0_ADDR(base)        ((base) + (0x220))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P36_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P36_STATE_1_ADDR(base)        ((base) + (0x224))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P37_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P37_STATE_0_ADDR(base)        ((base) + (0x228))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P37_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P37_STATE_1_ADDR(base)        ((base) + (0x22C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P38_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P38_STATE_0_ADDR(base)        ((base) + (0x230))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P38_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P38_STATE_1_ADDR(base)        ((base) + (0x234))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P39_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P39_STATE_0_ADDR(base)        ((base) + (0x238))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P39_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P39_STATE_1_ADDR(base)        ((base) + (0x23C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P40_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P40_STATE_0_ADDR(base)        ((base) + (0x240))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P40_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P40_STATE_1_ADDR(base)        ((base) + (0x244))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P41_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P41_STATE_0_ADDR(base)        ((base) + (0x248))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P41_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P41_STATE_1_ADDR(base)        ((base) + (0x24C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P42_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P42_STATE_0_ADDR(base)        ((base) + (0x250))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P42_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P42_STATE_1_ADDR(base)        ((base) + (0x254))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P43_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P43_STATE_0_ADDR(base)        ((base) + (0x258))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P43_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P43_STATE_1_ADDR(base)        ((base) + (0x25C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P44_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P44_STATE_0_ADDR(base)        ((base) + (0x260))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P44_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P44_STATE_1_ADDR(base)        ((base) + (0x264))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P45_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P45_STATE_0_ADDR(base)        ((base) + (0x268))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P45_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P45_STATE_1_ADDR(base)        ((base) + (0x26C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P46_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P46_STATE_0_ADDR(base)        ((base) + (0x270))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P46_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P46_STATE_1_ADDR(base)        ((base) + (0x274))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P47_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P47_STATE_0_ADDR(base)        ((base) + (0x278))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P47_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P47_STATE_1_ADDR(base)        ((base) + (0x27C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P48_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P48_STATE_0_ADDR(base)        ((base) + (0x280))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P48_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P48_STATE_1_ADDR(base)        ((base) + (0x284))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P49_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P49_STATE_0_ADDR(base)        ((base) + (0x288))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P49_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P49_STATE_1_ADDR(base)        ((base) + (0x28C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P50_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P50_STATE_0_ADDR(base)        ((base) + (0x290))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P50_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P50_STATE_1_ADDR(base)        ((base) + (0x294))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P51_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P51_STATE_0_ADDR(base)        ((base) + (0x298))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P51_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P51_STATE_1_ADDR(base)        ((base) + (0x29C))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P52_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P52_STATE_0_ADDR(base)        ((base) + (0x2A0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P52_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P52_STATE_1_ADDR(base)        ((base) + (0x2A4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P53_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P53_STATE_0_ADDR(base)        ((base) + (0x2A8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P53_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P53_STATE_1_ADDR(base)        ((base) + (0x2AC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P54_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P54_STATE_0_ADDR(base)        ((base) + (0x2B0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P54_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P54_STATE_1_ADDR(base)        ((base) + (0x2B4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P55_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P55_STATE_0_ADDR(base)        ((base) + (0x2B8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P55_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P55_STATE_1_ADDR(base)        ((base) + (0x2BC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P56_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P56_STATE_0_ADDR(base)        ((base) + (0x2C0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P56_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P56_STATE_1_ADDR(base)        ((base) + (0x2C4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P57_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P57_STATE_0_ADDR(base)        ((base) + (0x2C8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P57_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P57_STATE_1_ADDR(base)        ((base) + (0x2CC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P58_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P58_STATE_0_ADDR(base)        ((base) + (0x2D0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P58_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P58_STATE_1_ADDR(base)        ((base) + (0x2D4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P59_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P59_STATE_0_ADDR(base)        ((base) + (0x2D8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P59_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P59_STATE_1_ADDR(base)        ((base) + (0x2DC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P60_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P60_STATE_0_ADDR(base)        ((base) + (0x2E0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P60_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P60_STATE_1_ADDR(base)        ((base) + (0x2E4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P61_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P61_STATE_0_ADDR(base)        ((base) + (0x2E8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P61_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P61_STATE_1_ADDR(base)        ((base) + (0x2EC))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P62_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P62_STATE_0_ADDR(base)        ((base) + (0x2F0))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P62_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P62_STATE_1_ADDR(base)        ((base) + (0x2F4))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P63_STATE_0_UNION */
#define SOC_ASP_SLIMBUS_P63_STATE_0_ADDR(base)        ((base) + (0x2F8))

/* 寄存器说明：Content of these registers presents status of each data port
   位域定义UNION结构:  SOC_ASP_SLIMBUS_P63_STATE_1_UNION */
#define SOC_ASP_SLIMBUS_P63_STATE_1_ADDR(base)        ((base) + (0x2FC))





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
 结构名    : SOC_ASP_SLIMBUS_CONFIG_MODE_UNION
 结构说明  : CONFIG_MODE 寄存器结构定义。地址偏移量:0x000，初值:0x00000400，宽度:32
 寄存器说明: set the required operation mode of the SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ENABLE           : 1;  /* bit[0]    : If HIGH, the functionality of the whole SLIMBUS_MANAGER component is enabled. */
        unsigned int  MANAGER_MODE     : 1;  /* bit[1]    : If HIGH, the Manager functionality is enabled. In this mode the IP responses to messages targeted to Active Manager (LA=0xFF) and stores them in RX_FIFO. */
        unsigned int  SNIFFER_MODE     : 1;  /* bit[2]    : If HIGH, the Sniffer functionality is enabled. In this mode all messages tracked in the message channel are written to RX_FIFO, regardless of response status. */
        unsigned int  FR_EN            : 1;  /* bit[3]    : If HIGH, the internal Framer device is enabled.
                                                            If set LOW, the internal Framer device is disabled. */
        unsigned int  DEV_EN           : 1;  /* bit[4]    : If HIGH, the internal Generic device is enabled. If set LOW, the internal Generic device is disabled. */
        unsigned int  GO_ABSENT        : 1;  /* bit[5]    : If HIGH, initiates generation of REPORT_ABSENT and results in detaching component from the SLIMbus? (after PACK received to REPORT_ABSENT).
                                                            If change from into LOW state is detected than REPORT_PRESENT is retransmitted.
                                                            Change of this bit does not require confirmation using CFG_STROBE bit. */
        unsigned int  reserved_0       : 2;  /* bit[6-7]  : unused, fixed to 0 */
        unsigned int  RETRY_LMT        : 4;  /* bit[8-11] : Maximum number of retransmissions in case of collision or not positive acknowledgement. */
        unsigned int  REPORT_AT_EVENT  : 1;  /* bit[12]   : When HIGH, REPORT_INFORMATION message is transmitted independent on state of Information Element before the event occurrence (i.e. Information Element does not have to be cleared to enable next generation of corresponding REPORT_INFORMATION). */
        unsigned int  CRC_CALC_DISABLE : 1;  /* bit[13]   : If HIGH, CRC fields in the messages transmitted from TX_FIFO hardware calculation of CRC is disabled (CRC is expected to be calculated by CPU).
                                                            If LOW, CRC fields are calculated automatically in the IP. */
        unsigned int  LMTD_REPORT      : 1;  /* bit[14]   : If HIGH, reporting using REPORT_INFORMATION is limited only to mandatory reporting.
                                                            I.e. only REPORT_INFORMATION messages related with Information Elements specific for the Interface Device Class are supported (MC_TX_COL, LOST_FS, LOST_SFS, LOST_MS, DATA_SLOT_OVERLAP) */
        unsigned int  RECONF_TX_DIS    : 1;  /* bit[15]   : If LOW, after transmission of valid RECONFIGURE_NOW message resulting in reconfiguration, the Manager waits until reconfiguration boundary before transmitting next messages from TX_FIFO.
                                                            If HIGH, above functionality is disabled. In such case there is a risk that BEGIN_RECONFIGURATION message will be transmitted between RECONFIGURE_NOW and the reconfiguration boundary what will violate the standard. */
        unsigned int  reserved_1       : 16; /* bit[16-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_MODE_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ENABLE_START            (0)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ENABLE_END              (0)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_MANAGER_MODE_START      (1)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_MANAGER_MODE_END        (1)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_SNIFFER_MODE_START      (2)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_SNIFFER_MODE_END        (2)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_FR_EN_START             (3)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_FR_EN_END               (3)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_DEV_EN_START            (4)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_DEV_EN_END              (4)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_GO_ABSENT_START         (5)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_GO_ABSENT_END           (5)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RETRY_LMT_START         (8)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RETRY_LMT_END           (11)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_REPORT_AT_EVENT_START   (12)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_REPORT_AT_EVENT_END     (12)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_CRC_CALC_DISABLE_START  (13)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_CRC_CALC_DISABLE_END    (13)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_LMTD_REPORT_START       (14)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_LMTD_REPORT_END         (14)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RECONF_TX_DIS_START     (15)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RECONF_TX_DIS_END       (15)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_EA_UNION
 结构说明  : CONFIG_EA 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: change Enumeration Address of the SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PRODUCT_ID   : 16; /* bit[0-15] : Product ID.
                                                        Part of SLIMbus? Enumeration Address. */
        unsigned int  INSTANCE_VAL : 8;  /* bit[16-23]: Instance Value.
                                                        Part of SLIMbus? Enumeration Address. */
        unsigned int  reserved     : 8;  /* bit[24-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_EA_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_EA_PRODUCT_ID_START    (0)
#define SOC_ASP_SLIMBUS_CONFIG_EA_PRODUCT_ID_END      (15)
#define SOC_ASP_SLIMBUS_CONFIG_EA_INSTANCE_VAL_START  (16)
#define SOC_ASP_SLIMBUS_CONFIG_EA_INSTANCE_VAL_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_PR_UNION
 结构说明  : CONFIG_PR 寄存器结构定义。地址偏移量:0x008，初值:0x07FFFFFF，宽度:32
 寄存器说明: set Present Rates and Transport Protocols supported by the Generic device implemented in the SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PR_SUPP  : 24; /* bit[0-23] : Presence Rates supported by Generic device.
                                                    Each bit of this vector corresponds to one of 24 not reserved values of the Presence Rate specified by the SLIMbus? standard, range b0000000…b0010111 is considered.
                                                    When the bit is HIGH then the corresponding Presence Rate is supported by the Generic device implemented in SLIMBUS_MANAGER.
                                                    When bit is LOW then the corresponding Presence Rate is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with corresponding Presence Rate will result in EX_ERROR. */
        unsigned int  TP_SUPP  : 3;  /* bit[24-26]: Transport Protocols supported by Generic device.
                                                    Each bit of this vector corresponds to one Trasnport Protocol implemented in the SLIMBUS_MANAGER.
                                                    · bit.0 – Isochronous
                                                    · bit.1 – Pushed
                                                    · bit.2 – Pulled
                                                    When the particular bit is HIGH then the corresponding Transport protocol is supported by the Generic device implemented in SLIMBUS_MANAGER.
                                                    When the bit is LOW then the corresponding Transport Protocol is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with corresponding Transport protocol will result in EX_ERROR. */
        unsigned int  reserved : 5;  /* bit[27-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_PR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_PR_PR_SUPP_START   (0)
#define SOC_ASP_SLIMBUS_CONFIG_PR_PR_SUPP_END     (23)
#define SOC_ASP_SLIMBUS_CONFIG_PR_TP_SUPP_START   (24)
#define SOC_ASP_SLIMBUS_CONFIG_PR_TP_SUPP_END     (26)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_FR_UNION
 结构说明  : CONFIG_FR 寄存器结构定义。地址偏移量:0x00C，初值:0x0000FFFF，宽度:32
 寄存器说明: to change configuration of the Framer device implemented in SLIMBUS_MANAGER.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RF_SUPP         : 16; /* bit[0-15] : Each bit of this vector corresponds to one of 16 Root Frequencies specified by the SLIMbus? standard, Range (b0000…b1111).
                                                           When the bit is HIGH then the corresponding Root Frequency is supported by the Framer device implemented in SLIMBUS_MANAGER.
                                                           When bit is LOW then the corresponding Root Frequency is not supported, and the attempt of reconfiguration SLIMBUS_MANAGER using that Root Frequency will result in RECONFIG_OBJECTION. */
        unsigned int  QUALITY         : 2;  /* bit[16-17]: This two bits contain the number which is used to set quality of the CLK signal that is generated by the FRAMER device implemented in SLIMBUS_MANAGER. */
        unsigned int  PAUSE_AT_RFCHNG : 1;  /* bit[18]   : When HIGH and the FRAMER device change the Root Frequency, after reconfiguration boundary the Framer stops the SLIMbus? clock leaving the SLIMbus? clock line at LOW state (i.e. SLIMbus? suspends at the falling edge of the last cell of last cell of last superframe). To start toggle the clock line, the UNFREEZE bit in the COMMAND register must be set.
                                                           When LOW the FRAMER device change the Root Frequency without stopping the clock line. */
        unsigned int  reserved        : 13; /* bit[19-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_FR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_FR_RF_SUPP_START          (0)
#define SOC_ASP_SLIMBUS_CONFIG_FR_RF_SUPP_END            (15)
#define SOC_ASP_SLIMBUS_CONFIG_FR_QUALITY_START          (16)
#define SOC_ASP_SLIMBUS_CONFIG_FR_QUALITY_END            (17)
#define SOC_ASP_SLIMBUS_CONFIG_FR_PAUSE_AT_RFCHNG_START  (18)
#define SOC_ASP_SLIMBUS_CONFIG_FR_PAUSE_AT_RFCHNG_END    (18)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_DPORT_UNION
 结构说明  : CONFIG_DPORT 寄存器结构定义。地址偏移量:0x010，初值:0x00000600，宽度:32
 寄存器说明: change configuration data ports of the Generic device implemented in SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SINK_START_LVL  : 8;  /* bit[0-7]  : Level of FIFO at which sink port starts releasing data. Must be lower than DATA_FIFO_SIZE. Recommended value, for DATA_FIFO_SIZE = 4 is 2. */
        unsigned int  DPORT_CLK_PRESC : 4;  /* bit[8-11] : This 4-bit number defining prescaler used for Data Port clock (dport_clock) generation.
                                                           For each data port, SLIMBUS_MANAGER generates data port clock with frequency related with data channel segment rate. And the ratio between segment rate and generated data port clock is defined as 2DPORT_CLK_PRESC .
                                                           Accepted values: 2 (4?b0010) to 8 (4?b1000).
                                                           For values 0 and 1, functionality is the same as for value 2.
                                                           For values 9 and above, functionality is not specified. */
        unsigned int  REFCLK_SEL      : 2;  /* bit[12-13]: Defines the reference clock generated out of the SLIMbus? clock.
                                                           ?b00 corresponds to Clock Gear 6?
                                                           ?b01 corresponds to Clock Gear 7?
                                                           ?b10 corresponds to Clock Gear 8?
                                                           ?b11 corresponds to Clock Gear 9? */
        unsigned int  reserved        : 18; /* bit[14-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_DPORT_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_SINK_START_LVL_START   (0)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_SINK_START_LVL_END     (7)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_DPORT_CLK_PRESC_START  (8)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_DPORT_CLK_PRESC_END    (11)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_REFCLK_SEL_START       (12)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_REFCLK_SEL_END         (13)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_CPORT_UNION
 结构说明  : CONFIG_CPORT 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: change configuration cports of the Generic device implemented in SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPORT_CLK_DIV : 3;  /* bit[0-2] : Used for generation of cport_clk_o.
                                                        Frequency of cport_clk_o = sb_clk_i_n frequency divided by {CPORT_CLK_DIV+1}. */
        unsigned int  reserved      : 29; /* bit[3-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_CPORT_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_CPORT_CLK_DIV_START  (0)
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_CPORT_CLK_DIV_END    (2)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_EA2_UNION
 结构说明  : CONFIG_EA2 寄存器结构定义。地址偏移量:0x018，初值:0x00010200，宽度:32
 寄存器说明: change part of Enumeration address of each of device implemented in SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DEVICE_ID_1 : 8;  /* bit[0-7]  : Device ID of the Interface device - part of Enumeration Address. */
        unsigned int  DEVICE_ID_2 : 8;  /* bit[8-15] : Device ID of the Generic device - part of Enumeration Address. */
        unsigned int  DEVICE_ID_3 : 8;  /* bit[16-23]: Device ID of the Framer device - part of Enumeration Address. */
        unsigned int  reserved    : 8;  /* bit[24-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_EA2_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_1_START  (0)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_1_END    (7)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_2_START  (8)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_2_END    (15)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_3_START  (16)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_3_END    (23)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_CONFIG_THR_UNION
 结构说明  : CONFIG_THR 寄存器结构定义。地址偏移量:0x01C，初值:0x001F0000，宽度:32
 寄存器说明: define DMA thresholds for Source and Sink data ports.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SRC_THR  : 8;  /* bit[0-7]  : When level of Source Data Port FIFO falls below that threshold then DMA request is generated for Source data ports, and if enabled, DMA request interrupt is generated. */
        unsigned int  reserved_0: 8;  /* bit[8-15] : unused, fixed to 0 */
        unsigned int  SINK_THR : 5;  /* bit[16-20]: When level of Sink Data Port FIFO exceeds that threshold then DMA request is generated for Sink data ports, and if enabled, DMA request interrupt is generated. */
        unsigned int  reserved_1: 11; /* bit[21-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_THR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_THR_SRC_THR_START   (0)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SRC_THR_END     (7)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SINK_THR_START  (16)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SINK_THR_END    (20)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_COMMAND_UNION
 结构说明  : COMMAND 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: control RX_FIFO, TX_FIFO, control the UNFREEZE function, and confirm the IP configuration programmed using CONFIG registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TX_PUSH        : 1;  /* bit[0]   : Writing ?1? on this bit, indicates end of message write to TX_FIFO – i.e. push the message to TX_FIFO. */
        unsigned int  RX_PULL        : 1;  /* bit[1]   : Writing ?1? on this bit, indicates end of message read from RX_FIFO – i.e. pull the message from RX_FIFO. */
        unsigned int  TX_CLR         : 1;  /* bit[2]   : Writing ?1? on this bit clears TX_FIFO from all messages and stop retransmission of current message. */
        unsigned int  UNFREEZE       : 1;  /* bit[3]   : Writing ?1? on this bit activates the UNFREEZE function.
                                                         When the IP is in PAUSE state, and the Framer function is enabled, then writing ?1? on this bit forces to generate a toggle at SLIMbus? data line, what in turn wakes-up SLIMbus? from PAUSE state.
                                                         When the Framer function is enabled, internal Framer is active and pausing at RF change is enabled using CONFIG_FR.PAUSE_AT_RFCHNG bit, then writing ?1? on this resumes the operation of the Framer after change of RF. */
        unsigned int  CFG_STROBE     : 1;  /* bit[4]   : Writing ?1? on this bit confirms all configuration that have been previously programmed in CONFIG registers. */
        unsigned int  CFG_STROBE_CLR : 1;  /* bit[5]   : Writing '1' on this bit cancels pending configuration(clears CFG_STROBE) */
        unsigned int  reserved       : 26; /* bit[6-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_COMMAND_UNION;
#endif
#define SOC_ASP_SLIMBUS_COMMAND_TX_PUSH_START         (0)
#define SOC_ASP_SLIMBUS_COMMAND_TX_PUSH_END           (0)
#define SOC_ASP_SLIMBUS_COMMAND_RX_PULL_START         (1)
#define SOC_ASP_SLIMBUS_COMMAND_RX_PULL_END           (1)
#define SOC_ASP_SLIMBUS_COMMAND_TX_CLR_START          (2)
#define SOC_ASP_SLIMBUS_COMMAND_TX_CLR_END            (2)
#define SOC_ASP_SLIMBUS_COMMAND_UNFREEZE_START        (3)
#define SOC_ASP_SLIMBUS_COMMAND_UNFREEZE_END          (3)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_START      (4)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_END        (4)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_CLR_START  (5)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_CLR_END    (5)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_STATE_UNION
 结构说明  : STATE 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: check the SLIMBUS_MANAGER status
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TX_FULL       : 1;  /* bit[0]    : If HIGH, then the TX_FIFO is full and each subsequent message sent by CPU will not be written. */
        unsigned int  TX_NOTEMPTY   : 1;  /* bit[1]    : If HIGH, then there is at least one message in TX_FIFO. */
        unsigned int  RX_NOTEMPTY   : 1;  /* bit[2]    : If HIGH, there is at least one message in RX_FIFO. */
        unsigned int  reserved_0    : 1;  /* bit[3]    : unused, fixed to 0 */
        unsigned int  TX_PUSH       : 1;  /* bit[4]    : If HIGH, the TX_PUSH command is still in progress and the TX_FULL and TX_NOTEMPTY bits are not valid. */
        unsigned int  RX_PULL       : 1;  /* bit[5]    : If HIGH, the RX_PULL command is still in progress and the RX_NOTEMPTY bit is not valid. */
        unsigned int  reserved_1    : 2;  /* bit[6-7]  : unused, fixed to 0 */
        unsigned int  F_SYNC        : 1;  /* bit[8]    : If HIGH, the SLIMBUS_MANAGER achieved frame synchronization. */
        unsigned int  SF_SYNC       : 1;  /* bit[9]    : If HIGH, the SLIMBUS_MANAGER achieved superframe synchronization. */
        unsigned int  M_SYNC        : 1;  /* bit[10]   : If HIGH, the SLIMBUS_MANAGER achieved message synchronization. */
        unsigned int  SFB_SYNC      : 1;  /* bit[11]   : If HIGH, the SLIMBUS_MANAGER achieved superframe block synchronization */
        unsigned int  PH_SYNC       : 1;  /* bit[12]   : If HIGH, the SLIMBUS_MANAGER achieved phase synchronization and clock signal generated by the Generic device is valid. */
        unsigned int  reserved_2    : 2;  /* bit[13-14]: unused, fixed to 0 */
        unsigned int  DETACHED      : 1;  /* bit[15]   : If HIGH, the SLIMBUS_MANAGER is detached from the bus after successful transmission of REPORT_ABSENT message. */
        unsigned int  SUBFRAME_MODE : 5;  /* bit[16-20]: This register contains the Subframe Mode read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMBUS_MANAGER). */
        unsigned int  reserved_3    : 3;  /* bit[21-23]: unused, fixed to 0 */
        unsigned int  CLOCK_GEAR    : 4;  /* bit[24-27]: This register contains the Clock Gear read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMBUS_MANAGER). */
        unsigned int  ROOT_FR       : 4;  /* bit[28-31]: This register contains the Root Frequency read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMBUS_MANAGER). */
    } reg;
} SOC_ASP_SLIMBUS_STATE_UNION;
#endif
#define SOC_ASP_SLIMBUS_STATE_TX_FULL_START        (0)
#define SOC_ASP_SLIMBUS_STATE_TX_FULL_END          (0)
#define SOC_ASP_SLIMBUS_STATE_TX_NOTEMPTY_START    (1)
#define SOC_ASP_SLIMBUS_STATE_TX_NOTEMPTY_END      (1)
#define SOC_ASP_SLIMBUS_STATE_RX_NOTEMPTY_START    (2)
#define SOC_ASP_SLIMBUS_STATE_RX_NOTEMPTY_END      (2)
#define SOC_ASP_SLIMBUS_STATE_TX_PUSH_START        (4)
#define SOC_ASP_SLIMBUS_STATE_TX_PUSH_END          (4)
#define SOC_ASP_SLIMBUS_STATE_RX_PULL_START        (5)
#define SOC_ASP_SLIMBUS_STATE_RX_PULL_END          (5)
#define SOC_ASP_SLIMBUS_STATE_F_SYNC_START         (8)
#define SOC_ASP_SLIMBUS_STATE_F_SYNC_END           (8)
#define SOC_ASP_SLIMBUS_STATE_SF_SYNC_START        (9)
#define SOC_ASP_SLIMBUS_STATE_SF_SYNC_END          (9)
#define SOC_ASP_SLIMBUS_STATE_M_SYNC_START         (10)
#define SOC_ASP_SLIMBUS_STATE_M_SYNC_END           (10)
#define SOC_ASP_SLIMBUS_STATE_SFB_SYNC_START       (11)
#define SOC_ASP_SLIMBUS_STATE_SFB_SYNC_END         (11)
#define SOC_ASP_SLIMBUS_STATE_PH_SYNC_START        (12)
#define SOC_ASP_SLIMBUS_STATE_PH_SYNC_END          (12)
#define SOC_ASP_SLIMBUS_STATE_DETACHED_START       (15)
#define SOC_ASP_SLIMBUS_STATE_DETACHED_END         (15)
#define SOC_ASP_SLIMBUS_STATE_SUBFRAME_MODE_START  (16)
#define SOC_ASP_SLIMBUS_STATE_SUBFRAME_MODE_END    (20)
#define SOC_ASP_SLIMBUS_STATE_CLOCK_GEAR_START     (24)
#define SOC_ASP_SLIMBUS_STATE_CLOCK_GEAR_END       (27)
#define SOC_ASP_SLIMBUS_STATE_ROOT_FR_START        (28)
#define SOC_ASP_SLIMBUS_STATE_ROOT_FR_END          (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_IE_STATE_UNION
 结构说明  : IE_STATE 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: check status of Core and Device-specific Information Elements implemented in SLIMBUS_MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EX_ERROR_IF       : 1;  /* bit[0]    : Interface Device - EX_ERROR */
        unsigned int  reserved_0        : 1;  /* bit[1]    : unused, fixed to 0 */
        unsigned int  UNSPRTD_MSG_IF    : 1;  /* bit[2]    : Interface Device - UNSPRTD_MSG */
        unsigned int  MC_TX_COL         : 1;  /* bit[3]    : Interface Device - MC_TX_COL */
        unsigned int  LOST_FS           : 1;  /* bit[4]    : Interface Device - LOST_FS */
        unsigned int  LOST_SFS          : 1;  /* bit[5]    : Interface Device - LOST_SFS */
        unsigned int  LOST_MS           : 1;  /* bit[6]    : Interface Device - LOST_MS */
        unsigned int  DATA_SLOT_OVERLAP : 1;  /* bit[7]    : Interface Device - DATA_SLOT_OVERLAP */
        unsigned int  EX_ERROR_FR       : 1;  /* bit[8]    : Framer Device - EX_ERROR */
        unsigned int  RCFG_OBJECTION    : 1;  /* bit[9]    : Framer Device - RECONFIG_OBJECTION */
        unsigned int  UNSPRTD_MSG_FR    : 1;  /* bit[10]   : Framer Device - UNSPRTD_MSG */
        unsigned int  ACTIVE_FRAMER     : 1;  /* bit[11]   : Framer Device - ACTIVE_FRAMER */
        unsigned int  FS_TX_COL         : 1;  /* bit[12]   : Framer Device - FS_TX_COL */
        unsigned int  FI_TX_COL         : 1;  /* bit[13]   : Framer Device - FI_TX_COL */
        unsigned int  GC_TX_COL         : 1;  /* bit[14]   : Framer Device - GC_TX_COL */
        unsigned int  reserved_1        : 1;  /* bit[15]   : unused, fixed to 0 */
        unsigned int  EX_ERROR_DEV      : 1;  /* bit[16]   : Generic Device - EX_ERROR */
        unsigned int  DATA_TX_COL       : 1;  /* bit[17]   : Generic Device - DATA_TX_COL */
        unsigned int  UNSPRTD_MSG_DEV   : 1;  /* bit[18]   : Generic Device - UNSPRTD_MSG */
        unsigned int  reserved_2        : 13; /* bit[19-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_IE_STATE_UNION;
#endif
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_IF_START        (0)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_IF_END          (0)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_IF_START     (2)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_IF_END       (2)
#define SOC_ASP_SLIMBUS_IE_STATE_MC_TX_COL_START          (3)
#define SOC_ASP_SLIMBUS_IE_STATE_MC_TX_COL_END            (3)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_FS_START            (4)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_FS_END              (4)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_SFS_START           (5)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_SFS_END             (5)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_MS_START            (6)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_MS_END              (6)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_SLOT_OVERLAP_START  (7)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_SLOT_OVERLAP_END    (7)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_FR_START        (8)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_FR_END          (8)
#define SOC_ASP_SLIMBUS_IE_STATE_RCFG_OBJECTION_START     (9)
#define SOC_ASP_SLIMBUS_IE_STATE_RCFG_OBJECTION_END       (9)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_FR_START     (10)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_FR_END       (10)
#define SOC_ASP_SLIMBUS_IE_STATE_ACTIVE_FRAMER_START      (11)
#define SOC_ASP_SLIMBUS_IE_STATE_ACTIVE_FRAMER_END        (11)
#define SOC_ASP_SLIMBUS_IE_STATE_FS_TX_COL_START          (12)
#define SOC_ASP_SLIMBUS_IE_STATE_FS_TX_COL_END            (12)
#define SOC_ASP_SLIMBUS_IE_STATE_FI_TX_COL_START          (13)
#define SOC_ASP_SLIMBUS_IE_STATE_FI_TX_COL_END            (13)
#define SOC_ASP_SLIMBUS_IE_STATE_GC_TX_COL_START          (14)
#define SOC_ASP_SLIMBUS_IE_STATE_GC_TX_COL_END            (14)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_DEV_START       (16)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_DEV_END         (16)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_TX_COL_START        (17)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_TX_COL_END          (17)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_DEV_START    (18)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_DEV_END      (18)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_MCH_USAGE_UNION
 结构说明  : MCH_USAGE 寄存器结构定义。地址偏移量:0x02C，初值:0x05EE0000，宽度:32
 寄存器说明: notify about current level of bandwidth used in the Message Channel, and to configure number of superframes in a row for which messages channel usage is being monitored to not exceed 75% bandwidth.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MCH_USAGE    : 11; /* bit[0-10] : 11-bit vector informing about current (in the last superframe) level of bandwidth used in the Message Channel. */
        unsigned int  reserved     : 5;  /* bit[11-15]: unused, fixed to 0 */
        unsigned int  MCH_CAPACITY : 11; /* bit[16-26]: 11-bit vector informing about maximum available bandwidth in the Message Channel, available for current (in the last superframe) Subframe Mode. */
        unsigned int  MCH_LAPSE    : 5;  /* bit[27-31]: 4-bit vector defining number of superframes for which messages channel usage is being monitored to not exceed 75% bandwidth. */
    } reg;
} SOC_ASP_SLIMBUS_MCH_USAGE_UNION;
#endif
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_USAGE_START     (0)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_USAGE_END       (10)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_CAPACITY_START  (16)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_CAPACITY_END    (26)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_LAPSE_START     (27)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_LAPSE_END       (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_INT_EN_UNION
 结构说明  : INT_EN 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: defines which interrupt sources, related with TX_FIFO and RX_FIFO and internal state of the IP are enabled. This register also contains the main interrupt enable bit which enables/disables all interrupt sources
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IN_EN        : 1;  /* bit[0]   : If LOW, disables generation of any interrupts, regardless of setting of the other interrupt enable bits. */
        unsigned int  RX_INT_EN    : 1;  /* bit[1]   : If HIGH, enables generation of interrupt when RX_FIFO is not empty. */
        unsigned int  TX_INT_EN    : 1;  /* bit[2]   : If HIGH, enables generation of interrupt when TX_FIFO becomes empty (after transmitting all messages). */
        unsigned int  TX_ERR_EN    : 1;  /* bit[3]   : If HIGH, enables generation of interrupt when any message from TX_FIFO is not transmitted successfully. */
        unsigned int  SYNC_LOST_EN : 1;  /* bit[4]   : If HIGH, enables generation of interrupt when
                                                       any of main synchronization bits (F_SYNC, SF_SYNC, M_SYNC) toggles into LOW, and the IP is not detached due to REPORT_ABSENT message. */
        unsigned int  RCFG_INT_EN  : 1;  /* bit[5]   : If HIGH, enables generation of interrupt at the reconfiguration boundary. */
        unsigned int  MCH_INT_EN   : 1;  /* bit[6]   : If HIGH, enables generation of interrupt when usage of message channel exceeded 75% in ?MCH_LAPSE+1? superframes in a row. */
        unsigned int  reserved     : 25; /* bit[7-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_INT_EN_IN_EN_START         (0)
#define SOC_ASP_SLIMBUS_INT_EN_IN_EN_END           (0)
#define SOC_ASP_SLIMBUS_INT_EN_RX_INT_EN_START     (1)
#define SOC_ASP_SLIMBUS_INT_EN_RX_INT_EN_END       (1)
#define SOC_ASP_SLIMBUS_INT_EN_TX_INT_EN_START     (2)
#define SOC_ASP_SLIMBUS_INT_EN_TX_INT_EN_END       (2)
#define SOC_ASP_SLIMBUS_INT_EN_TX_ERR_EN_START     (3)
#define SOC_ASP_SLIMBUS_INT_EN_TX_ERR_EN_END       (3)
#define SOC_ASP_SLIMBUS_INT_EN_SYNC_LOST_EN_START  (4)
#define SOC_ASP_SLIMBUS_INT_EN_SYNC_LOST_EN_END    (4)
#define SOC_ASP_SLIMBUS_INT_EN_RCFG_INT_EN_START   (5)
#define SOC_ASP_SLIMBUS_INT_EN_RCFG_INT_EN_END     (5)
#define SOC_ASP_SLIMBUS_INT_EN_MCH_INT_EN_START    (6)
#define SOC_ASP_SLIMBUS_INT_EN_MCH_INT_EN_END      (6)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_INT_UNION
 结构说明  : INT 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: shows the interrupt status of the SLIMBUS_MANAGER. It contains the interrupt requests related with TX_FIFO and RX_FIFO, Data Ports and the IP internal state
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : unused, fixed to 0 */
        unsigned int  RX_INT    : 1;  /* bit[1]   : Set HIGH when enabled and RX_FIFO is not empty.
                                                    Cleared after writing 1. */
        unsigned int  TX_INT    : 1;  /* bit[2]   : Set HIGH when enabled and TX_FIFO becomes empty (after transmitting all messages).
                                                    Cleared after writing 1. */
        unsigned int  TX_ERR    : 1;  /* bit[3]   : Set HIGH when enabled and when message from TX_FIFO is not transmitted successfully.
                                                    Cleared after writing 1. */
        unsigned int  SYNC_LOST : 1;  /* bit[4]   : Set HIGH when enabled and when any of main synchronization bits (F_SYNC, SF_SYNC, M_SYNC) toggles into LOW, and the IP is not detached due to REPORT_ABSENT message.
                                                    Cleared after writing 1. */
        unsigned int  RCFG_INT  : 1;  /* bit[5]   : Set HIGH when enabled and reconfiguration boundary occurs.
                                                    Cleared after writing 1. */
        unsigned int  MCH_INT   : 1;  /* bit[6]   : Set HIGH when enabled and when usage of message channel exceeded 75% in ?MCH_LAPSE+1? superframes in a row.
                                                    Cleared after writing 1. */
        unsigned int  PORT_INT  : 1;  /* bit[7]   : HIGH when bit of PINT register is HIGH.
                                                    LOW when all bits of PINT register are LOW. */
        unsigned int  reserved_1: 24; /* bit[8-31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_INT_RX_INT_START     (1)
#define SOC_ASP_SLIMBUS_INT_RX_INT_END       (1)
#define SOC_ASP_SLIMBUS_INT_TX_INT_START     (2)
#define SOC_ASP_SLIMBUS_INT_TX_INT_END       (2)
#define SOC_ASP_SLIMBUS_INT_TX_ERR_START     (3)
#define SOC_ASP_SLIMBUS_INT_TX_ERR_END       (3)
#define SOC_ASP_SLIMBUS_INT_SYNC_LOST_START  (4)
#define SOC_ASP_SLIMBUS_INT_SYNC_LOST_END    (4)
#define SOC_ASP_SLIMBUS_INT_RCFG_INT_START   (5)
#define SOC_ASP_SLIMBUS_INT_RCFG_INT_END     (5)
#define SOC_ASP_SLIMBUS_INT_MCH_INT_START    (6)
#define SOC_ASP_SLIMBUS_INT_MCH_INT_END      (6)
#define SOC_ASP_SLIMBUS_INT_PORT_INT_START   (7)
#define SOC_ASP_SLIMBUS_INT_PORT_INT_END     (7)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_MC_FIFO_UNION
 结构说明  : MC_FIFO 寄存器结构定义。地址偏移量:0x040～0x07C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MSG_SIZE     : 6;  /* bit[0-5]  : Size of received message that is currently
                                                        accessed through AHB, in bytes. */
        unsigned int  reserved     : 2;  /* bit[6-7]  : unused, fixed to 0 */
        unsigned int  RX_OVERFLOW  : 1;  /* bit[8]    : Overflow indication – at least 1 message has
                                                        been lost due to overflow in RX_FIFO. */
        unsigned int  TX_ERR       : 7;  /* bit[9-15] : unused, fixed to 0 */
        unsigned int  LOST_MSG_NUM : 16; /* bit[16-31]: Number of lost message due to overflow. */
    } reg;
} SOC_ASP_SLIMBUS_MC_FIFO_UNION;
#endif
#define SOC_ASP_SLIMBUS_MC_FIFO_MSG_SIZE_START      (0)
#define SOC_ASP_SLIMBUS_MC_FIFO_MSG_SIZE_END        (5)
#define SOC_ASP_SLIMBUS_MC_FIFO_RX_OVERFLOW_START   (8)
#define SOC_ASP_SLIMBUS_MC_FIFO_RX_OVERFLOW_END     (8)
#define SOC_ASP_SLIMBUS_MC_FIFO_TX_ERR_START        (9)
#define SOC_ASP_SLIMBUS_MC_FIFO_TX_ERR_END          (15)
#define SOC_ASP_SLIMBUS_MC_FIFO_LOST_MSG_NUM_START  (16)
#define SOC_ASP_SLIMBUS_MC_FIFO_LOST_MSG_NUM_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P0_INT_EN_UNION
 结构说明  : P0_INT_EN 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int_en0  : 1;  /* bit[0] : Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en0  : 1;  /* bit[1] : Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en0 : 1;  /* bit[2] : Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en0  : 1;  /* bit[3] : Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en0  : 1;  /* bit[4] : Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en0  : 1;  /* bit[5] : Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr0    : 1;  /* bit[6] : FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en0   : 1;  /* bit[7] : Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en1  : 1;  /* bit[8] : Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en1  : 1;  /* bit[9] : Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en1 : 1;  /* bit[10]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en1  : 1;  /* bit[11]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en1  : 1;  /* bit[12]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en1  : 1;  /* bit[13]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr1    : 1;  /* bit[14]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en1   : 1;  /* bit[15]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en2  : 1;  /* bit[16]: Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en2  : 1;  /* bit[17]: Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en2 : 1;  /* bit[18]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en2  : 1;  /* bit[19]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en2  : 1;  /* bit[20]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en2  : 1;  /* bit[21]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr2    : 1;  /* bit[22]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en2   : 1;  /* bit[23]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en3  : 1;  /* bit[24]: Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en3  : 1;  /* bit[25]: Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en3 : 1;  /* bit[26]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en3  : 1;  /* bit[27]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en3  : 1;  /* bit[28]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en3  : 1;  /* bit[29]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr3    : 1;  /* bit[30]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en3   : 1;  /* bit[31]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
    } reg;
} SOC_ASP_SLIMBUS_P0_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en0_START   (0)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en0_END     (0)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en0_START   (1)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en0_END     (1)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en0_START  (2)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en0_END    (2)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en0_START   (3)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en0_END     (3)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en0_START   (4)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en0_END     (4)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en0_START   (5)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en0_END     (5)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr0_START     (6)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr0_END       (6)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en0_START    (7)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en0_END      (7)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en1_START   (8)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en1_END     (8)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en1_START   (9)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en1_END     (9)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en1_START  (10)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en1_END    (10)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en1_START   (11)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en1_END     (11)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en1_START   (12)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en1_END     (12)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en1_START   (13)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en1_END     (13)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr1_START     (14)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr1_END       (14)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en1_START    (15)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en1_END      (15)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en2_START   (16)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en2_END     (16)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en2_START   (17)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en2_END     (17)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en2_START  (18)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en2_END    (18)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en2_START   (19)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en2_END     (19)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en2_START   (20)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en2_END     (20)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en2_START   (21)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en2_END     (21)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr2_START     (22)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr2_END       (22)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en2_START    (23)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en2_END      (23)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en3_START   (24)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en3_END     (24)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en3_START   (25)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en3_END     (25)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en3_START  (26)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en3_END    (26)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en3_START   (27)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en3_END     (27)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en3_START   (28)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en3_END     (28)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en3_START   (29)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en3_END     (29)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr3_START     (30)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr3_END       (30)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en3_START    (31)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en3_END      (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P4_INT_EN_UNION
 结构说明  : P4_INT_EN 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int_en4  : 1;  /* bit[0] : Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en4  : 1;  /* bit[1] : Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en4 : 1;  /* bit[2] : Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en4  : 1;  /* bit[3] : Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en4  : 1;  /* bit[4] : Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en4  : 1;  /* bit[5] : Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr4    : 1;  /* bit[6] : FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en4   : 1;  /* bit[7] : Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en5  : 1;  /* bit[8] : Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en5  : 1;  /* bit[9] : Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en5 : 1;  /* bit[10]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en5  : 1;  /* bit[11]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en5  : 1;  /* bit[12]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en5  : 1;  /* bit[13]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr5    : 1;  /* bit[14]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en5   : 1;  /* bit[15]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en6  : 1;  /* bit[16]: Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en6  : 1;  /* bit[17]: Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en6 : 1;  /* bit[18]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en6  : 1;  /* bit[19]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en6  : 1;  /* bit[20]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en6  : 1;  /* bit[21]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr6    : 1;  /* bit[22]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en6   : 1;  /* bit[23]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en7  : 1;  /* bit[24]: Channel activation
                                                     If HIGH, enables generation of interrupt when
                                                     channel connected with Data Port # is being
                                                     activated or being deactivated.
                                                     Data Port is regarded to be activated if it is
                                                     connected, configured and activated.
                                                     Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en7  : 1;  /* bit[25]: Channel content definition
                                                     If HIGH, enables generation of interrupt when
                                                     content definition of the channel connected
                                                     with Data Port # is being changed
                                                     (consequence of NEXT_DEFINE_CONTENT or
                                                     CHANGE_CONTENT message). */
        unsigned int  chan_int_en7 : 1;  /* bit[26]: Channel definition
                                                     If HIGH, enables generation of interrupt when
                                                     definition of the channel connected with Data
                                                     Port # is being changed (consequence of
                                                     NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en7  : 1;  /* bit[27]: Data Port DMA request
                                                     If HIGH, enables generation of interrupt when
                                                     DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en7  : 1;  /* bit[28]: Data Port FIFO overflow
                                                     If HIGH, enables generation of interrupt when
                                                     overflow occurs at Data Port #.
                                                     Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en7  : 1;  /* bit[29]: Data port FIFO underrun
                                                     If HIGH, enables generation of interrupt when
                                                     underrun occurs at Data Port #.
                                                     Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr7    : 1;  /* bit[30]: FIFO clear
                                                     Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en7   : 1;  /* bit[31]: Presence Rate Generation
                                                     If HIGH, enables automatic generation of Presence Rate at Port #.
                                                     In such case:
                                                     · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                     · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
    } reg;
} SOC_ASP_SLIMBUS_P4_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en4_START   (0)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en4_END     (0)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en4_START   (1)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en4_END     (1)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en4_START  (2)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en4_END    (2)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en4_START   (3)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en4_END     (3)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en4_START   (4)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en4_END     (4)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en4_START   (5)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en4_END     (5)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr4_START     (6)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr4_END       (6)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en4_START    (7)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en4_END      (7)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en5_START   (8)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en5_END     (8)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en5_START   (9)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en5_END     (9)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en5_START  (10)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en5_END    (10)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en5_START   (11)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en5_END     (11)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en5_START   (12)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en5_END     (12)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en5_START   (13)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en5_END     (13)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr5_START     (14)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr5_END       (14)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en5_START    (15)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en5_END      (15)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en6_START   (16)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en6_END     (16)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en6_START   (17)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en6_END     (17)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en6_START  (18)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en6_END    (18)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en6_START   (19)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en6_END     (19)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en6_START   (20)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en6_END     (20)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en6_START   (21)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en6_END     (21)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr6_START     (22)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr6_END       (22)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en6_START    (23)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en6_END      (23)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en7_START   (24)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en7_END     (24)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en7_START   (25)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en7_END     (25)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en7_START  (26)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en7_END    (26)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en7_START   (27)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en7_END     (27)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en7_START   (28)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en7_END     (28)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en7_START   (29)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en7_END     (29)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr7_START     (30)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr7_END       (30)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en7_START    (31)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en7_END      (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P8_INT_EN_UNION
 结构说明  : P8_INT_EN 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int_en8   : 1;  /* bit[0] : Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en8   : 1;  /* bit[1] : Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en8  : 1;  /* bit[2] : Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en8   : 1;  /* bit[3] : Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en8   : 1;  /* bit[4] : Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en8   : 1;  /* bit[5] : Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr8     : 1;  /* bit[6] : FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en8    : 1;  /* bit[7] : Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en9   : 1;  /* bit[8] : Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en9   : 1;  /* bit[9] : Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en9  : 1;  /* bit[10]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en9   : 1;  /* bit[11]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en9   : 1;  /* bit[12]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en9   : 1;  /* bit[13]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr9     : 1;  /* bit[14]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en9    : 1;  /* bit[15]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en10  : 1;  /* bit[16]: Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en10  : 1;  /* bit[17]: Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en10 : 1;  /* bit[18]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en10  : 1;  /* bit[19]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en10  : 1;  /* bit[20]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en10  : 1;  /* bit[21]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr10    : 1;  /* bit[22]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en10   : 1;  /* bit[23]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en11  : 1;  /* bit[24]: Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en11  : 1;  /* bit[25]: Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en11 : 1;  /* bit[26]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en11  : 1;  /* bit[27]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en11  : 1;  /* bit[28]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en11  : 1;  /* bit[29]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr11    : 1;  /* bit[30]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en11   : 1;  /* bit[31]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
    } reg;
} SOC_ASP_SLIMBUS_P8_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en8_START    (0)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en8_END      (0)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en8_START    (1)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en8_END      (1)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en8_START   (2)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en8_END     (2)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en8_START    (3)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en8_END      (3)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en8_START    (4)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en8_END      (4)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en8_START    (5)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en8_END      (5)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr8_START      (6)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr8_END        (6)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en8_START     (7)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en8_END       (7)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en9_START    (8)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en9_END      (8)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en9_START    (9)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en9_END      (9)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en9_START   (10)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en9_END     (10)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en9_START    (11)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en9_END      (11)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en9_START    (12)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en9_END      (12)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en9_START    (13)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en9_END      (13)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr9_START      (14)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr9_END        (14)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en9_START     (15)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en9_END       (15)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en10_START   (16)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en10_END     (16)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en10_START   (17)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en10_END     (17)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en10_START  (18)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en10_END    (18)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en10_START   (19)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en10_END     (19)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en10_START   (20)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en10_END     (20)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en10_START   (21)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en10_END     (21)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr10_START     (22)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr10_END       (22)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en10_START    (23)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en10_END      (23)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en11_START   (24)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en11_END     (24)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en11_START   (25)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en11_END     (25)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en11_START  (26)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en11_END    (26)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en11_START   (27)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en11_END     (27)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en11_START   (28)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en11_END     (28)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en11_START   (29)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en11_END     (29)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr11_START     (30)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr11_END       (30)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en11_START    (31)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en11_END      (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P12_INT_EN_UNION
 结构说明  : P12_INT_EN 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int_en12  : 1;  /* bit[0] : Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en12  : 1;  /* bit[1] : Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en12 : 1;  /* bit[2] : Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en12  : 1;  /* bit[3] : Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en12  : 1;  /* bit[4] : Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en12  : 1;  /* bit[5] : Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr12    : 1;  /* bit[6] : FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en12   : 1;  /* bit[7] : Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en13  : 1;  /* bit[8] : Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en13  : 1;  /* bit[9] : Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en13 : 1;  /* bit[10]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en13  : 1;  /* bit[11]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en13  : 1;  /* bit[12]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en13  : 1;  /* bit[13]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr13    : 1;  /* bit[14]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en13   : 1;  /* bit[15]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en14  : 1;  /* bit[16]: Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en14  : 1;  /* bit[17]: Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en14 : 1;  /* bit[18]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en14  : 1;  /* bit[19]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en14  : 1;  /* bit[20]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en14  : 1;  /* bit[21]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr14    : 1;  /* bit[22]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en14   : 1;  /* bit[23]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
        unsigned int  act_int_en15  : 1;  /* bit[24]: Channel activation
                                                      If HIGH, enables generation of interrupt when
                                                      channel connected with Data Port # is being
                                                      activated or being deactivated.
                                                      Data Port is regarded to be activated if it is
                                                      connected, configured and activated.
                                                      Otherwise it is regarded as deactivated. */
        unsigned int  con_int_en15  : 1;  /* bit[25]: Channel content definition
                                                      If HIGH, enables generation of interrupt when
                                                      content definition of the channel connected
                                                      with Data Port # is being changed
                                                      (consequence of NEXT_DEFINE_CONTENT or
                                                      CHANGE_CONTENT message). */
        unsigned int  chan_int_en15 : 1;  /* bit[26]: Channel definition
                                                      If HIGH, enables generation of interrupt when
                                                      definition of the channel connected with Data
                                                      Port # is being changed (consequence of
                                                      NEXT_DEFINE_CHANNEL message). */
        unsigned int  dma_int_en15  : 1;  /* bit[27]: Data Port DMA request
                                                      If HIGH, enables generation of interrupt when
                                                      DMA request is raised for Data Port #. */
        unsigned int  ovf_int_en15  : 1;  /* bit[28]: Data Port FIFO overflow
                                                      If HIGH, enables generation of interrupt when
                                                      overflow occurs at Data Port #.
                                                      Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface. */
        unsigned int  und_int_en15  : 1;  /* bit[29]: Data port FIFO underrun
                                                      If HIGH, enables generation of interrupt when
                                                      underrun occurs at Data Port #.
                                                      Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate. */
        unsigned int  fifo_clr15    : 1;  /* bit[30]: FIFO clear
                                                      Writing '1' on this bit clears data port FIFO.Used when Data Port FIFO is accessed through AHB. */
        unsigned int  pr_gen_en15   : 1;  /* bit[31]: Presence Rate Generation
                                                      If HIGH, enables automatic generation of Presence Rate at Port #.
                                                      In such case:
                                                      · source data ports working in PUSHED protocol automatically generates P (presence) bit in data channel segments; according to current RF, CG and configured SR and PR
                                                      · sink data ports working in PULLED protocol automatically generates SRQ (sample request) bit in data channel segments; according to current RF, CG and configured SR and PR */
    } reg;
} SOC_ASP_SLIMBUS_P12_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en12_START   (0)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en12_END     (0)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en12_START   (1)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en12_END     (1)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en12_START  (2)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en12_END    (2)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en12_START   (3)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en12_END     (3)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en12_START   (4)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en12_END     (4)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en12_START   (5)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en12_END     (5)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr12_START     (6)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr12_END       (6)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en12_START    (7)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en12_END      (7)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en13_START   (8)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en13_END     (8)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en13_START   (9)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en13_END     (9)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en13_START  (10)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en13_END    (10)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en13_START   (11)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en13_END     (11)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en13_START   (12)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en13_END     (12)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en13_START   (13)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en13_END     (13)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr13_START     (14)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr13_END       (14)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en13_START    (15)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en13_END      (15)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en14_START   (16)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en14_END     (16)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en14_START   (17)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en14_END     (17)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en14_START  (18)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en14_END    (18)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en14_START   (19)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en14_END     (19)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en14_START   (20)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en14_END     (20)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en14_START   (21)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en14_END     (21)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr14_START     (22)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr14_END       (22)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en14_START    (23)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en14_END      (23)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en15_START   (24)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en15_END     (24)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en15_START   (25)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en15_END     (25)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en15_START  (26)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en15_END    (26)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en15_START   (27)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en15_END     (27)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en15_START   (28)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en15_END     (28)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en15_START   (29)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en15_END     (29)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr15_START     (30)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr15_END       (30)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en15_START    (31)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en15_END      (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P16_INT_EN_UNION
 结构说明  : P16_INT_EN 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P16_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P20_INT_EN_UNION
 结构说明  : P20_INT_EN 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P20_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P24_INT_EN_UNION
 结构说明  : P24_INT_EN 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P24_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P28_INT_EN_UNION
 结构说明  : P28_INT_EN 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P28_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P32_INT_EN_UNION
 结构说明  : P32_INT_EN 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P32_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P36_INT_EN_UNION
 结构说明  : P36_INT_EN 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P36_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P40_INT_EN_UNION
 结构说明  : P40_INT_EN 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P40_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P44_INT_EN_UNION
 结构说明  : P44_INT_EN 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P44_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P48_INT_EN_UNION
 结构说明  : P48_INT_EN 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P48_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P52_INT_EN_UNION
 结构说明  : P52_INT_EN 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P52_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P56_INT_EN_UNION
 结构说明  : P56_INT_EN 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P56_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P60_INT_EN_UNION
 结构说明  : P60_INT_EN 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[1] : unused, fixed to 0 */
        unsigned int  reserved_2: 1;  /* bit[2] : unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[3] : unused, fixed to 0 */
        unsigned int  reserved_4: 1;  /* bit[4] : unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[5] : unused, fixed to 0 */
        unsigned int  reserved_6: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  reserved_8: 1;  /* bit[8] : unused, fixed to 0 */
        unsigned int  reserved_9: 1;  /* bit[9] : unused, fixed to 0 */
        unsigned int  reserved_10: 1;  /* bit[10]: unused, fixed to 0 */
        unsigned int  reserved_11: 1;  /* bit[11]: unused, fixed to 0 */
        unsigned int  reserved_12: 1;  /* bit[12]: unused, fixed to 0 */
        unsigned int  reserved_13: 1;  /* bit[13]: unused, fixed to 0 */
        unsigned int  reserved_14: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_15: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  reserved_16: 1;  /* bit[16]: unused, fixed to 0 */
        unsigned int  reserved_17: 1;  /* bit[17]: unused, fixed to 0 */
        unsigned int  reserved_18: 1;  /* bit[18]: unused, fixed to 0 */
        unsigned int  reserved_19: 1;  /* bit[19]: unused, fixed to 0 */
        unsigned int  reserved_20: 1;  /* bit[20]: unused, fixed to 0 */
        unsigned int  reserved_21: 1;  /* bit[21]: unused, fixed to 0 */
        unsigned int  reserved_22: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_23: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  reserved_24: 1;  /* bit[24]: unused, fixed to 0 */
        unsigned int  reserved_25: 1;  /* bit[25]: unused, fixed to 0 */
        unsigned int  reserved_26: 1;  /* bit[26]: unused, fixed to 0 */
        unsigned int  reserved_27: 1;  /* bit[27]: unused, fixed to 0 */
        unsigned int  reserved_28: 1;  /* bit[28]: unused, fixed to 0 */
        unsigned int  reserved_29: 1;  /* bit[29]: unused, fixed to 0 */
        unsigned int  reserved_30: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_31: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P60_INT_EN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P0_INT_UNION
 结构说明  : P0_INT 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int0  : 1;  /* bit[0] : Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int0  : 1;  /* bit[1] : Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int0 : 1;  /* bit[2] : Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int0  : 1;  /* bit[3] : Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int0  : 1;  /* bit[4] : Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int0  : 1;  /* bit[5] : Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int1  : 1;  /* bit[8] : Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int1  : 1;  /* bit[9] : Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int1 : 1;  /* bit[10]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int1  : 1;  /* bit[11]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int1  : 1;  /* bit[12]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int1  : 1;  /* bit[13]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int2  : 1;  /* bit[16]: Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int2  : 1;  /* bit[17]: Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int2 : 1;  /* bit[18]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int2  : 1;  /* bit[19]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int2  : 1;  /* bit[20]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int2  : 1;  /* bit[21]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int3  : 1;  /* bit[24]: Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int3  : 1;  /* bit[25]: Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int3 : 1;  /* bit[26]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int3  : 1;  /* bit[27]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int3  : 1;  /* bit[28]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int3  : 1;  /* bit[29]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P0_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_INT_act_int0_START   (0)
#define SOC_ASP_SLIMBUS_P0_INT_act_int0_END     (0)
#define SOC_ASP_SLIMBUS_P0_INT_con_int0_START   (1)
#define SOC_ASP_SLIMBUS_P0_INT_con_int0_END     (1)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int0_START  (2)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int0_END    (2)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int0_START   (3)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int0_END     (3)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int0_START   (4)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int0_END     (4)
#define SOC_ASP_SLIMBUS_P0_INT_und_int0_START   (5)
#define SOC_ASP_SLIMBUS_P0_INT_und_int0_END     (5)
#define SOC_ASP_SLIMBUS_P0_INT_act_int1_START   (8)
#define SOC_ASP_SLIMBUS_P0_INT_act_int1_END     (8)
#define SOC_ASP_SLIMBUS_P0_INT_con_int1_START   (9)
#define SOC_ASP_SLIMBUS_P0_INT_con_int1_END     (9)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int1_START  (10)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int1_END    (10)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int1_START   (11)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int1_END     (11)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int1_START   (12)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int1_END     (12)
#define SOC_ASP_SLIMBUS_P0_INT_und_int1_START   (13)
#define SOC_ASP_SLIMBUS_P0_INT_und_int1_END     (13)
#define SOC_ASP_SLIMBUS_P0_INT_act_int2_START   (16)
#define SOC_ASP_SLIMBUS_P0_INT_act_int2_END     (16)
#define SOC_ASP_SLIMBUS_P0_INT_con_int2_START   (17)
#define SOC_ASP_SLIMBUS_P0_INT_con_int2_END     (17)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int2_START  (18)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int2_END    (18)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int2_START   (19)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int2_END     (19)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int2_START   (20)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int2_END     (20)
#define SOC_ASP_SLIMBUS_P0_INT_und_int2_START   (21)
#define SOC_ASP_SLIMBUS_P0_INT_und_int2_END     (21)
#define SOC_ASP_SLIMBUS_P0_INT_act_int3_START   (24)
#define SOC_ASP_SLIMBUS_P0_INT_act_int3_END     (24)
#define SOC_ASP_SLIMBUS_P0_INT_con_int3_START   (25)
#define SOC_ASP_SLIMBUS_P0_INT_con_int3_END     (25)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int3_START  (26)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int3_END    (26)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int3_START   (27)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int3_END     (27)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int3_START   (28)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int3_END     (28)
#define SOC_ASP_SLIMBUS_P0_INT_und_int3_START   (29)
#define SOC_ASP_SLIMBUS_P0_INT_und_int3_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P4_INT_UNION
 结构说明  : P4_INT 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int4  : 1;  /* bit[0] : Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int4  : 1;  /* bit[1] : Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int4 : 1;  /* bit[2] : Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int4  : 1;  /* bit[3] : Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int4  : 1;  /* bit[4] : Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int4  : 1;  /* bit[5] : Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0: 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1: 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int5  : 1;  /* bit[8] : Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int5  : 1;  /* bit[9] : Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int5 : 1;  /* bit[10]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int5  : 1;  /* bit[11]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int5  : 1;  /* bit[12]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int5  : 1;  /* bit[13]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2: 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3: 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int6  : 1;  /* bit[16]: Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int6  : 1;  /* bit[17]: Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int6 : 1;  /* bit[18]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int6  : 1;  /* bit[19]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int6  : 1;  /* bit[20]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int6  : 1;  /* bit[21]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4: 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5: 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int7  : 1;  /* bit[24]: Channel activation
                                                  Set when channel connected with Data Port # is being activated or being deactivated.
                                                  Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  con_int7  : 1;  /* bit[25]: Channel content definition
                                                  Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  chan_int7 : 1;  /* bit[26]: Channel definition
                                                  Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  dma_int7  : 1;  /* bit[27]: Data Port DMA request
                                                  Set when DMA request is raised for Data Port #.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int7  : 1;  /* bit[28]: Data Port FIFO overflow
                                                  Set when overflow occurs at Data Port #.
                                                  Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  und_int7  : 1;  /* bit[29]: Data port FIFO underrun
                                                  Set when underrun occurs at Data Port #.
                                                  Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                  Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6: 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7: 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P4_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_INT_act_int4_START   (0)
#define SOC_ASP_SLIMBUS_P4_INT_act_int4_END     (0)
#define SOC_ASP_SLIMBUS_P4_INT_con_int4_START   (1)
#define SOC_ASP_SLIMBUS_P4_INT_con_int4_END     (1)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int4_START  (2)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int4_END    (2)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int4_START   (3)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int4_END     (3)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int4_START   (4)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int4_END     (4)
#define SOC_ASP_SLIMBUS_P4_INT_und_int4_START   (5)
#define SOC_ASP_SLIMBUS_P4_INT_und_int4_END     (5)
#define SOC_ASP_SLIMBUS_P4_INT_act_int5_START   (8)
#define SOC_ASP_SLIMBUS_P4_INT_act_int5_END     (8)
#define SOC_ASP_SLIMBUS_P4_INT_con_int5_START   (9)
#define SOC_ASP_SLIMBUS_P4_INT_con_int5_END     (9)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int5_START  (10)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int5_END    (10)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int5_START   (11)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int5_END     (11)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int5_START   (12)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int5_END     (12)
#define SOC_ASP_SLIMBUS_P4_INT_und_int5_START   (13)
#define SOC_ASP_SLIMBUS_P4_INT_und_int5_END     (13)
#define SOC_ASP_SLIMBUS_P4_INT_act_int6_START   (16)
#define SOC_ASP_SLIMBUS_P4_INT_act_int6_END     (16)
#define SOC_ASP_SLIMBUS_P4_INT_con_int6_START   (17)
#define SOC_ASP_SLIMBUS_P4_INT_con_int6_END     (17)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int6_START  (18)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int6_END    (18)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int6_START   (19)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int6_END     (19)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int6_START   (20)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int6_END     (20)
#define SOC_ASP_SLIMBUS_P4_INT_und_int6_START   (21)
#define SOC_ASP_SLIMBUS_P4_INT_und_int6_END     (21)
#define SOC_ASP_SLIMBUS_P4_INT_act_int7_START   (24)
#define SOC_ASP_SLIMBUS_P4_INT_act_int7_END     (24)
#define SOC_ASP_SLIMBUS_P4_INT_con_int7_START   (25)
#define SOC_ASP_SLIMBUS_P4_INT_con_int7_END     (25)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int7_START  (26)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int7_END    (26)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int7_START   (27)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int7_END     (27)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int7_START   (28)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int7_END     (28)
#define SOC_ASP_SLIMBUS_P4_INT_und_int7_START   (29)
#define SOC_ASP_SLIMBUS_P4_INT_und_int7_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P8_INT_UNION
 结构说明  : P8_INT 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int8   : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int8   : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int8  : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int8   : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int8   : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int8   : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int9   : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int9   : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int9  : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int9   : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int9   : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int9   : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int10  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int10  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int10 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int10  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int10  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int10  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int11  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int11  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int11 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int11  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int11  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int11  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P8_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_INT_act_int8_START    (0)
#define SOC_ASP_SLIMBUS_P8_INT_act_int8_END      (0)
#define SOC_ASP_SLIMBUS_P8_INT_con_int8_START    (1)
#define SOC_ASP_SLIMBUS_P8_INT_con_int8_END      (1)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int8_START   (2)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int8_END     (2)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int8_START    (3)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int8_END      (3)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int8_START    (4)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int8_END      (4)
#define SOC_ASP_SLIMBUS_P8_INT_und_int8_START    (5)
#define SOC_ASP_SLIMBUS_P8_INT_und_int8_END      (5)
#define SOC_ASP_SLIMBUS_P8_INT_act_int9_START    (8)
#define SOC_ASP_SLIMBUS_P8_INT_act_int9_END      (8)
#define SOC_ASP_SLIMBUS_P8_INT_con_int9_START    (9)
#define SOC_ASP_SLIMBUS_P8_INT_con_int9_END      (9)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int9_START   (10)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int9_END     (10)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int9_START    (11)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int9_END      (11)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int9_START    (12)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int9_END      (12)
#define SOC_ASP_SLIMBUS_P8_INT_und_int9_START    (13)
#define SOC_ASP_SLIMBUS_P8_INT_und_int9_END      (13)
#define SOC_ASP_SLIMBUS_P8_INT_act_int10_START   (16)
#define SOC_ASP_SLIMBUS_P8_INT_act_int10_END     (16)
#define SOC_ASP_SLIMBUS_P8_INT_con_int10_START   (17)
#define SOC_ASP_SLIMBUS_P8_INT_con_int10_END     (17)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int10_START  (18)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int10_END    (18)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int10_START   (19)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int10_END     (19)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int10_START   (20)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int10_END     (20)
#define SOC_ASP_SLIMBUS_P8_INT_und_int10_START   (21)
#define SOC_ASP_SLIMBUS_P8_INT_und_int10_END     (21)
#define SOC_ASP_SLIMBUS_P8_INT_act_int11_START   (24)
#define SOC_ASP_SLIMBUS_P8_INT_act_int11_END     (24)
#define SOC_ASP_SLIMBUS_P8_INT_con_int11_START   (25)
#define SOC_ASP_SLIMBUS_P8_INT_con_int11_END     (25)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int11_START  (26)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int11_END    (26)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int11_START   (27)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int11_END     (27)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int11_START   (28)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int11_END     (28)
#define SOC_ASP_SLIMBUS_P8_INT_und_int11_START   (29)
#define SOC_ASP_SLIMBUS_P8_INT_und_int11_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P12_INT_UNION
 结构说明  : P12_INT 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int12  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int12  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int12 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int12  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int12  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int12  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int13  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int13  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int13 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int13  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int13  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int13  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int14  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int14  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int14 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int14  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int14  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int14  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int15  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int15  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int15 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int15  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int15  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int15  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P12_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_INT_act_int12_START   (0)
#define SOC_ASP_SLIMBUS_P12_INT_act_int12_END     (0)
#define SOC_ASP_SLIMBUS_P12_INT_con_int12_START   (1)
#define SOC_ASP_SLIMBUS_P12_INT_con_int12_END     (1)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int12_START  (2)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int12_END    (2)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int12_START   (3)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int12_END     (3)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int12_START   (4)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int12_END     (4)
#define SOC_ASP_SLIMBUS_P12_INT_und_int12_START   (5)
#define SOC_ASP_SLIMBUS_P12_INT_und_int12_END     (5)
#define SOC_ASP_SLIMBUS_P12_INT_act_int13_START   (8)
#define SOC_ASP_SLIMBUS_P12_INT_act_int13_END     (8)
#define SOC_ASP_SLIMBUS_P12_INT_con_int13_START   (9)
#define SOC_ASP_SLIMBUS_P12_INT_con_int13_END     (9)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int13_START  (10)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int13_END    (10)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int13_START   (11)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int13_END     (11)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int13_START   (12)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int13_END     (12)
#define SOC_ASP_SLIMBUS_P12_INT_und_int13_START   (13)
#define SOC_ASP_SLIMBUS_P12_INT_und_int13_END     (13)
#define SOC_ASP_SLIMBUS_P12_INT_act_int14_START   (16)
#define SOC_ASP_SLIMBUS_P12_INT_act_int14_END     (16)
#define SOC_ASP_SLIMBUS_P12_INT_con_int14_START   (17)
#define SOC_ASP_SLIMBUS_P12_INT_con_int14_END     (17)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int14_START  (18)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int14_END    (18)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int14_START   (19)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int14_END     (19)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int14_START   (20)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int14_END     (20)
#define SOC_ASP_SLIMBUS_P12_INT_und_int14_START   (21)
#define SOC_ASP_SLIMBUS_P12_INT_und_int14_END     (21)
#define SOC_ASP_SLIMBUS_P12_INT_act_int15_START   (24)
#define SOC_ASP_SLIMBUS_P12_INT_act_int15_END     (24)
#define SOC_ASP_SLIMBUS_P12_INT_con_int15_START   (25)
#define SOC_ASP_SLIMBUS_P12_INT_con_int15_END     (25)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int15_START  (26)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int15_END    (26)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int15_START   (27)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int15_END     (27)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int15_START   (28)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int15_END     (28)
#define SOC_ASP_SLIMBUS_P12_INT_und_int15_START   (29)
#define SOC_ASP_SLIMBUS_P12_INT_und_int15_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P16_INT_UNION
 结构说明  : P16_INT 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int16  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int16  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int16 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int16  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int16  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int16  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int17  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int17  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int17 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int17  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int17  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int17  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int18  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int18  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int18 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int18  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int18  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int18  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int19  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int19  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int19 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int19  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int19  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int19  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P16_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_INT_act_int16_START   (0)
#define SOC_ASP_SLIMBUS_P16_INT_act_int16_END     (0)
#define SOC_ASP_SLIMBUS_P16_INT_con_int16_START   (1)
#define SOC_ASP_SLIMBUS_P16_INT_con_int16_END     (1)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int16_START  (2)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int16_END    (2)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int16_START   (3)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int16_END     (3)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int16_START   (4)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int16_END     (4)
#define SOC_ASP_SLIMBUS_P16_INT_und_int16_START   (5)
#define SOC_ASP_SLIMBUS_P16_INT_und_int16_END     (5)
#define SOC_ASP_SLIMBUS_P16_INT_act_int17_START   (8)
#define SOC_ASP_SLIMBUS_P16_INT_act_int17_END     (8)
#define SOC_ASP_SLIMBUS_P16_INT_con_int17_START   (9)
#define SOC_ASP_SLIMBUS_P16_INT_con_int17_END     (9)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int17_START  (10)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int17_END    (10)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int17_START   (11)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int17_END     (11)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int17_START   (12)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int17_END     (12)
#define SOC_ASP_SLIMBUS_P16_INT_und_int17_START   (13)
#define SOC_ASP_SLIMBUS_P16_INT_und_int17_END     (13)
#define SOC_ASP_SLIMBUS_P16_INT_act_int18_START   (16)
#define SOC_ASP_SLIMBUS_P16_INT_act_int18_END     (16)
#define SOC_ASP_SLIMBUS_P16_INT_con_int18_START   (17)
#define SOC_ASP_SLIMBUS_P16_INT_con_int18_END     (17)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int18_START  (18)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int18_END    (18)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int18_START   (19)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int18_END     (19)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int18_START   (20)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int18_END     (20)
#define SOC_ASP_SLIMBUS_P16_INT_und_int18_START   (21)
#define SOC_ASP_SLIMBUS_P16_INT_und_int18_END     (21)
#define SOC_ASP_SLIMBUS_P16_INT_act_int19_START   (24)
#define SOC_ASP_SLIMBUS_P16_INT_act_int19_END     (24)
#define SOC_ASP_SLIMBUS_P16_INT_con_int19_START   (25)
#define SOC_ASP_SLIMBUS_P16_INT_con_int19_END     (25)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int19_START  (26)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int19_END    (26)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int19_START   (27)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int19_END     (27)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int19_START   (28)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int19_END     (28)
#define SOC_ASP_SLIMBUS_P16_INT_und_int19_START   (29)
#define SOC_ASP_SLIMBUS_P16_INT_und_int19_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P20_INT_UNION
 结构说明  : P20_INT 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int20  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int20  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int20 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int20  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int20  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int20  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int21  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int21  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int21 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int21  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int21  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int21  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int22  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int22  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int22 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int22  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int22  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int22  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int23  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int23  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int23 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int23  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int23  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int23  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P20_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_INT_act_int20_START   (0)
#define SOC_ASP_SLIMBUS_P20_INT_act_int20_END     (0)
#define SOC_ASP_SLIMBUS_P20_INT_con_int20_START   (1)
#define SOC_ASP_SLIMBUS_P20_INT_con_int20_END     (1)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int20_START  (2)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int20_END    (2)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int20_START   (3)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int20_END     (3)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int20_START   (4)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int20_END     (4)
#define SOC_ASP_SLIMBUS_P20_INT_und_int20_START   (5)
#define SOC_ASP_SLIMBUS_P20_INT_und_int20_END     (5)
#define SOC_ASP_SLIMBUS_P20_INT_act_int21_START   (8)
#define SOC_ASP_SLIMBUS_P20_INT_act_int21_END     (8)
#define SOC_ASP_SLIMBUS_P20_INT_con_int21_START   (9)
#define SOC_ASP_SLIMBUS_P20_INT_con_int21_END     (9)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int21_START  (10)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int21_END    (10)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int21_START   (11)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int21_END     (11)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int21_START   (12)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int21_END     (12)
#define SOC_ASP_SLIMBUS_P20_INT_und_int21_START   (13)
#define SOC_ASP_SLIMBUS_P20_INT_und_int21_END     (13)
#define SOC_ASP_SLIMBUS_P20_INT_act_int22_START   (16)
#define SOC_ASP_SLIMBUS_P20_INT_act_int22_END     (16)
#define SOC_ASP_SLIMBUS_P20_INT_con_int22_START   (17)
#define SOC_ASP_SLIMBUS_P20_INT_con_int22_END     (17)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int22_START  (18)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int22_END    (18)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int22_START   (19)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int22_END     (19)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int22_START   (20)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int22_END     (20)
#define SOC_ASP_SLIMBUS_P20_INT_und_int22_START   (21)
#define SOC_ASP_SLIMBUS_P20_INT_und_int22_END     (21)
#define SOC_ASP_SLIMBUS_P20_INT_act_int23_START   (24)
#define SOC_ASP_SLIMBUS_P20_INT_act_int23_END     (24)
#define SOC_ASP_SLIMBUS_P20_INT_con_int23_START   (25)
#define SOC_ASP_SLIMBUS_P20_INT_con_int23_END     (25)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int23_START  (26)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int23_END    (26)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int23_START   (27)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int23_END     (27)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int23_START   (28)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int23_END     (28)
#define SOC_ASP_SLIMBUS_P20_INT_und_int23_START   (29)
#define SOC_ASP_SLIMBUS_P20_INT_und_int23_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P24_INT_UNION
 结构说明  : P24_INT 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int24  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int24  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int24 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int24  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int24  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int24  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int25  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int25  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int25 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int25  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int25  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int25  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int26  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int26  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int26 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int26  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int26  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int26  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int27  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int27  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int27 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int27  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int27  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int27  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P24_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_INT_act_int24_START   (0)
#define SOC_ASP_SLIMBUS_P24_INT_act_int24_END     (0)
#define SOC_ASP_SLIMBUS_P24_INT_con_int24_START   (1)
#define SOC_ASP_SLIMBUS_P24_INT_con_int24_END     (1)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int24_START  (2)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int24_END    (2)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int24_START   (3)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int24_END     (3)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int24_START   (4)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int24_END     (4)
#define SOC_ASP_SLIMBUS_P24_INT_und_int24_START   (5)
#define SOC_ASP_SLIMBUS_P24_INT_und_int24_END     (5)
#define SOC_ASP_SLIMBUS_P24_INT_act_int25_START   (8)
#define SOC_ASP_SLIMBUS_P24_INT_act_int25_END     (8)
#define SOC_ASP_SLIMBUS_P24_INT_con_int25_START   (9)
#define SOC_ASP_SLIMBUS_P24_INT_con_int25_END     (9)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int25_START  (10)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int25_END    (10)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int25_START   (11)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int25_END     (11)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int25_START   (12)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int25_END     (12)
#define SOC_ASP_SLIMBUS_P24_INT_und_int25_START   (13)
#define SOC_ASP_SLIMBUS_P24_INT_und_int25_END     (13)
#define SOC_ASP_SLIMBUS_P24_INT_act_int26_START   (16)
#define SOC_ASP_SLIMBUS_P24_INT_act_int26_END     (16)
#define SOC_ASP_SLIMBUS_P24_INT_con_int26_START   (17)
#define SOC_ASP_SLIMBUS_P24_INT_con_int26_END     (17)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int26_START  (18)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int26_END    (18)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int26_START   (19)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int26_END     (19)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int26_START   (20)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int26_END     (20)
#define SOC_ASP_SLIMBUS_P24_INT_und_int26_START   (21)
#define SOC_ASP_SLIMBUS_P24_INT_und_int26_END     (21)
#define SOC_ASP_SLIMBUS_P24_INT_act_int27_START   (24)
#define SOC_ASP_SLIMBUS_P24_INT_act_int27_END     (24)
#define SOC_ASP_SLIMBUS_P24_INT_con_int27_START   (25)
#define SOC_ASP_SLIMBUS_P24_INT_con_int27_END     (25)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int27_START  (26)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int27_END    (26)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int27_START   (27)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int27_END     (27)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int27_START   (28)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int27_END     (28)
#define SOC_ASP_SLIMBUS_P24_INT_und_int27_START   (29)
#define SOC_ASP_SLIMBUS_P24_INT_und_int27_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P28_INT_UNION
 结构说明  : P28_INT 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int28  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int28  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int28 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int28  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int28  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int28  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int29  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int29  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int29 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int29  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int29  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int29  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int30  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int30  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int30 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int30  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int30  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int30  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int31  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int31  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int31 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int31  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int31  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int31  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P28_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_INT_act_int28_START   (0)
#define SOC_ASP_SLIMBUS_P28_INT_act_int28_END     (0)
#define SOC_ASP_SLIMBUS_P28_INT_con_int28_START   (1)
#define SOC_ASP_SLIMBUS_P28_INT_con_int28_END     (1)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int28_START  (2)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int28_END    (2)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int28_START   (3)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int28_END     (3)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int28_START   (4)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int28_END     (4)
#define SOC_ASP_SLIMBUS_P28_INT_und_int28_START   (5)
#define SOC_ASP_SLIMBUS_P28_INT_und_int28_END     (5)
#define SOC_ASP_SLIMBUS_P28_INT_act_int29_START   (8)
#define SOC_ASP_SLIMBUS_P28_INT_act_int29_END     (8)
#define SOC_ASP_SLIMBUS_P28_INT_con_int29_START   (9)
#define SOC_ASP_SLIMBUS_P28_INT_con_int29_END     (9)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int29_START  (10)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int29_END    (10)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int29_START   (11)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int29_END     (11)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int29_START   (12)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int29_END     (12)
#define SOC_ASP_SLIMBUS_P28_INT_und_int29_START   (13)
#define SOC_ASP_SLIMBUS_P28_INT_und_int29_END     (13)
#define SOC_ASP_SLIMBUS_P28_INT_act_int30_START   (16)
#define SOC_ASP_SLIMBUS_P28_INT_act_int30_END     (16)
#define SOC_ASP_SLIMBUS_P28_INT_con_int30_START   (17)
#define SOC_ASP_SLIMBUS_P28_INT_con_int30_END     (17)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int30_START  (18)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int30_END    (18)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int30_START   (19)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int30_END     (19)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int30_START   (20)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int30_END     (20)
#define SOC_ASP_SLIMBUS_P28_INT_und_int30_START   (21)
#define SOC_ASP_SLIMBUS_P28_INT_und_int30_END     (21)
#define SOC_ASP_SLIMBUS_P28_INT_act_int31_START   (24)
#define SOC_ASP_SLIMBUS_P28_INT_act_int31_END     (24)
#define SOC_ASP_SLIMBUS_P28_INT_con_int31_START   (25)
#define SOC_ASP_SLIMBUS_P28_INT_con_int31_END     (25)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int31_START  (26)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int31_END    (26)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int31_START   (27)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int31_END     (27)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int31_START   (28)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int31_END     (28)
#define SOC_ASP_SLIMBUS_P28_INT_und_int31_START   (29)
#define SOC_ASP_SLIMBUS_P28_INT_und_int31_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P32_INT_UNION
 结构说明  : P32_INT 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int32  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int32  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int32 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int32  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int32  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int32  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int33  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int33  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int33 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int33  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int33  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int33  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int34  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int34  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int34 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int34  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int34  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int34  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int35  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int35  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int35 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int35  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int35  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int35  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P32_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_INT_act_int32_START   (0)
#define SOC_ASP_SLIMBUS_P32_INT_act_int32_END     (0)
#define SOC_ASP_SLIMBUS_P32_INT_con_int32_START   (1)
#define SOC_ASP_SLIMBUS_P32_INT_con_int32_END     (1)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int32_START  (2)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int32_END    (2)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int32_START   (3)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int32_END     (3)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int32_START   (4)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int32_END     (4)
#define SOC_ASP_SLIMBUS_P32_INT_und_int32_START   (5)
#define SOC_ASP_SLIMBUS_P32_INT_und_int32_END     (5)
#define SOC_ASP_SLIMBUS_P32_INT_act_int33_START   (8)
#define SOC_ASP_SLIMBUS_P32_INT_act_int33_END     (8)
#define SOC_ASP_SLIMBUS_P32_INT_con_int33_START   (9)
#define SOC_ASP_SLIMBUS_P32_INT_con_int33_END     (9)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int33_START  (10)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int33_END    (10)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int33_START   (11)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int33_END     (11)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int33_START   (12)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int33_END     (12)
#define SOC_ASP_SLIMBUS_P32_INT_und_int33_START   (13)
#define SOC_ASP_SLIMBUS_P32_INT_und_int33_END     (13)
#define SOC_ASP_SLIMBUS_P32_INT_act_int34_START   (16)
#define SOC_ASP_SLIMBUS_P32_INT_act_int34_END     (16)
#define SOC_ASP_SLIMBUS_P32_INT_con_int34_START   (17)
#define SOC_ASP_SLIMBUS_P32_INT_con_int34_END     (17)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int34_START  (18)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int34_END    (18)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int34_START   (19)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int34_END     (19)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int34_START   (20)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int34_END     (20)
#define SOC_ASP_SLIMBUS_P32_INT_und_int34_START   (21)
#define SOC_ASP_SLIMBUS_P32_INT_und_int34_END     (21)
#define SOC_ASP_SLIMBUS_P32_INT_act_int35_START   (24)
#define SOC_ASP_SLIMBUS_P32_INT_act_int35_END     (24)
#define SOC_ASP_SLIMBUS_P32_INT_con_int35_START   (25)
#define SOC_ASP_SLIMBUS_P32_INT_con_int35_END     (25)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int35_START  (26)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int35_END    (26)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int35_START   (27)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int35_END     (27)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int35_START   (28)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int35_END     (28)
#define SOC_ASP_SLIMBUS_P32_INT_und_int35_START   (29)
#define SOC_ASP_SLIMBUS_P32_INT_und_int35_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P36_INT_UNION
 结构说明  : P36_INT 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int36  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int36  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int36 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int36  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int36  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int36  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int37  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int37  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int37 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int37  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int37  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int37  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int38  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int38  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int38 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int38  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int38  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int38  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int39  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int39  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int39 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int39  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int39  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int39  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P36_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_INT_act_int36_START   (0)
#define SOC_ASP_SLIMBUS_P36_INT_act_int36_END     (0)
#define SOC_ASP_SLIMBUS_P36_INT_con_int36_START   (1)
#define SOC_ASP_SLIMBUS_P36_INT_con_int36_END     (1)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int36_START  (2)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int36_END    (2)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int36_START   (3)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int36_END     (3)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int36_START   (4)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int36_END     (4)
#define SOC_ASP_SLIMBUS_P36_INT_und_int36_START   (5)
#define SOC_ASP_SLIMBUS_P36_INT_und_int36_END     (5)
#define SOC_ASP_SLIMBUS_P36_INT_act_int37_START   (8)
#define SOC_ASP_SLIMBUS_P36_INT_act_int37_END     (8)
#define SOC_ASP_SLIMBUS_P36_INT_con_int37_START   (9)
#define SOC_ASP_SLIMBUS_P36_INT_con_int37_END     (9)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int37_START  (10)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int37_END    (10)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int37_START   (11)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int37_END     (11)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int37_START   (12)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int37_END     (12)
#define SOC_ASP_SLIMBUS_P36_INT_und_int37_START   (13)
#define SOC_ASP_SLIMBUS_P36_INT_und_int37_END     (13)
#define SOC_ASP_SLIMBUS_P36_INT_act_int38_START   (16)
#define SOC_ASP_SLIMBUS_P36_INT_act_int38_END     (16)
#define SOC_ASP_SLIMBUS_P36_INT_con_int38_START   (17)
#define SOC_ASP_SLIMBUS_P36_INT_con_int38_END     (17)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int38_START  (18)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int38_END    (18)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int38_START   (19)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int38_END     (19)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int38_START   (20)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int38_END     (20)
#define SOC_ASP_SLIMBUS_P36_INT_und_int38_START   (21)
#define SOC_ASP_SLIMBUS_P36_INT_und_int38_END     (21)
#define SOC_ASP_SLIMBUS_P36_INT_act_int39_START   (24)
#define SOC_ASP_SLIMBUS_P36_INT_act_int39_END     (24)
#define SOC_ASP_SLIMBUS_P36_INT_con_int39_START   (25)
#define SOC_ASP_SLIMBUS_P36_INT_con_int39_END     (25)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int39_START  (26)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int39_END    (26)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int39_START   (27)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int39_END     (27)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int39_START   (28)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int39_END     (28)
#define SOC_ASP_SLIMBUS_P36_INT_und_int39_START   (29)
#define SOC_ASP_SLIMBUS_P36_INT_und_int39_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P40_INT_UNION
 结构说明  : P40_INT 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int40  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int40  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int40 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int40  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int40  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int40  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int41  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int41  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int41 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int41  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int41  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int41  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int42  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int42  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int42 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int42  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int42  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int42  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int43  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int43  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int43 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int43  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int43  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int43  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P40_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_INT_act_int40_START   (0)
#define SOC_ASP_SLIMBUS_P40_INT_act_int40_END     (0)
#define SOC_ASP_SLIMBUS_P40_INT_con_int40_START   (1)
#define SOC_ASP_SLIMBUS_P40_INT_con_int40_END     (1)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int40_START  (2)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int40_END    (2)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int40_START   (3)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int40_END     (3)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int40_START   (4)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int40_END     (4)
#define SOC_ASP_SLIMBUS_P40_INT_und_int40_START   (5)
#define SOC_ASP_SLIMBUS_P40_INT_und_int40_END     (5)
#define SOC_ASP_SLIMBUS_P40_INT_act_int41_START   (8)
#define SOC_ASP_SLIMBUS_P40_INT_act_int41_END     (8)
#define SOC_ASP_SLIMBUS_P40_INT_con_int41_START   (9)
#define SOC_ASP_SLIMBUS_P40_INT_con_int41_END     (9)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int41_START  (10)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int41_END    (10)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int41_START   (11)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int41_END     (11)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int41_START   (12)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int41_END     (12)
#define SOC_ASP_SLIMBUS_P40_INT_und_int41_START   (13)
#define SOC_ASP_SLIMBUS_P40_INT_und_int41_END     (13)
#define SOC_ASP_SLIMBUS_P40_INT_act_int42_START   (16)
#define SOC_ASP_SLIMBUS_P40_INT_act_int42_END     (16)
#define SOC_ASP_SLIMBUS_P40_INT_con_int42_START   (17)
#define SOC_ASP_SLIMBUS_P40_INT_con_int42_END     (17)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int42_START  (18)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int42_END    (18)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int42_START   (19)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int42_END     (19)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int42_START   (20)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int42_END     (20)
#define SOC_ASP_SLIMBUS_P40_INT_und_int42_START   (21)
#define SOC_ASP_SLIMBUS_P40_INT_und_int42_END     (21)
#define SOC_ASP_SLIMBUS_P40_INT_act_int43_START   (24)
#define SOC_ASP_SLIMBUS_P40_INT_act_int43_END     (24)
#define SOC_ASP_SLIMBUS_P40_INT_con_int43_START   (25)
#define SOC_ASP_SLIMBUS_P40_INT_con_int43_END     (25)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int43_START  (26)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int43_END    (26)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int43_START   (27)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int43_END     (27)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int43_START   (28)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int43_END     (28)
#define SOC_ASP_SLIMBUS_P40_INT_und_int43_START   (29)
#define SOC_ASP_SLIMBUS_P40_INT_und_int43_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P44_INT_UNION
 结构说明  : P44_INT 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int44  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int44  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int44 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int44  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int44  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int44  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int45  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int45  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int45 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int45  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int45  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int45  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int46  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int46  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int46 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int46  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int46  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int46  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int47  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int47  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int47 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int47  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int47  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int47  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P44_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_INT_act_int44_START   (0)
#define SOC_ASP_SLIMBUS_P44_INT_act_int44_END     (0)
#define SOC_ASP_SLIMBUS_P44_INT_con_int44_START   (1)
#define SOC_ASP_SLIMBUS_P44_INT_con_int44_END     (1)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int44_START  (2)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int44_END    (2)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int44_START   (3)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int44_END     (3)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int44_START   (4)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int44_END     (4)
#define SOC_ASP_SLIMBUS_P44_INT_und_int44_START   (5)
#define SOC_ASP_SLIMBUS_P44_INT_und_int44_END     (5)
#define SOC_ASP_SLIMBUS_P44_INT_act_int45_START   (8)
#define SOC_ASP_SLIMBUS_P44_INT_act_int45_END     (8)
#define SOC_ASP_SLIMBUS_P44_INT_con_int45_START   (9)
#define SOC_ASP_SLIMBUS_P44_INT_con_int45_END     (9)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int45_START  (10)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int45_END    (10)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int45_START   (11)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int45_END     (11)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int45_START   (12)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int45_END     (12)
#define SOC_ASP_SLIMBUS_P44_INT_und_int45_START   (13)
#define SOC_ASP_SLIMBUS_P44_INT_und_int45_END     (13)
#define SOC_ASP_SLIMBUS_P44_INT_act_int46_START   (16)
#define SOC_ASP_SLIMBUS_P44_INT_act_int46_END     (16)
#define SOC_ASP_SLIMBUS_P44_INT_con_int46_START   (17)
#define SOC_ASP_SLIMBUS_P44_INT_con_int46_END     (17)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int46_START  (18)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int46_END    (18)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int46_START   (19)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int46_END     (19)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int46_START   (20)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int46_END     (20)
#define SOC_ASP_SLIMBUS_P44_INT_und_int46_START   (21)
#define SOC_ASP_SLIMBUS_P44_INT_und_int46_END     (21)
#define SOC_ASP_SLIMBUS_P44_INT_act_int47_START   (24)
#define SOC_ASP_SLIMBUS_P44_INT_act_int47_END     (24)
#define SOC_ASP_SLIMBUS_P44_INT_con_int47_START   (25)
#define SOC_ASP_SLIMBUS_P44_INT_con_int47_END     (25)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int47_START  (26)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int47_END    (26)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int47_START   (27)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int47_END     (27)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int47_START   (28)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int47_END     (28)
#define SOC_ASP_SLIMBUS_P44_INT_und_int47_START   (29)
#define SOC_ASP_SLIMBUS_P44_INT_und_int47_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P48_INT_UNION
 结构说明  : P48_INT 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int48  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int48  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int48 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int48  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int48  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int48  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int49  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int49  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int49 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int49  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int49  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int49  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int50  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int50  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int50 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int50  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int50  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int50  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int51  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int51  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int51 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int51  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int51  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int51  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P48_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_INT_act_int48_START   (0)
#define SOC_ASP_SLIMBUS_P48_INT_act_int48_END     (0)
#define SOC_ASP_SLIMBUS_P48_INT_con_int48_START   (1)
#define SOC_ASP_SLIMBUS_P48_INT_con_int48_END     (1)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int48_START  (2)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int48_END    (2)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int48_START   (3)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int48_END     (3)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int48_START   (4)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int48_END     (4)
#define SOC_ASP_SLIMBUS_P48_INT_und_int48_START   (5)
#define SOC_ASP_SLIMBUS_P48_INT_und_int48_END     (5)
#define SOC_ASP_SLIMBUS_P48_INT_act_int49_START   (8)
#define SOC_ASP_SLIMBUS_P48_INT_act_int49_END     (8)
#define SOC_ASP_SLIMBUS_P48_INT_con_int49_START   (9)
#define SOC_ASP_SLIMBUS_P48_INT_con_int49_END     (9)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int49_START  (10)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int49_END    (10)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int49_START   (11)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int49_END     (11)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int49_START   (12)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int49_END     (12)
#define SOC_ASP_SLIMBUS_P48_INT_und_int49_START   (13)
#define SOC_ASP_SLIMBUS_P48_INT_und_int49_END     (13)
#define SOC_ASP_SLIMBUS_P48_INT_act_int50_START   (16)
#define SOC_ASP_SLIMBUS_P48_INT_act_int50_END     (16)
#define SOC_ASP_SLIMBUS_P48_INT_con_int50_START   (17)
#define SOC_ASP_SLIMBUS_P48_INT_con_int50_END     (17)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int50_START  (18)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int50_END    (18)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int50_START   (19)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int50_END     (19)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int50_START   (20)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int50_END     (20)
#define SOC_ASP_SLIMBUS_P48_INT_und_int50_START   (21)
#define SOC_ASP_SLIMBUS_P48_INT_und_int50_END     (21)
#define SOC_ASP_SLIMBUS_P48_INT_act_int51_START   (24)
#define SOC_ASP_SLIMBUS_P48_INT_act_int51_END     (24)
#define SOC_ASP_SLIMBUS_P48_INT_con_int51_START   (25)
#define SOC_ASP_SLIMBUS_P48_INT_con_int51_END     (25)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int51_START  (26)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int51_END    (26)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int51_START   (27)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int51_END     (27)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int51_START   (28)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int51_END     (28)
#define SOC_ASP_SLIMBUS_P48_INT_und_int51_START   (29)
#define SOC_ASP_SLIMBUS_P48_INT_und_int51_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P52_INT_UNION
 结构说明  : P52_INT 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int52  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int52  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int52 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int52  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int52  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int52  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int53  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int53  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int53 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int53  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int53  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int53  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int54  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int54  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int54 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int54  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int54  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int54  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int55  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int55  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int55 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int55  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int55  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int55  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P52_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_INT_act_int52_START   (0)
#define SOC_ASP_SLIMBUS_P52_INT_act_int52_END     (0)
#define SOC_ASP_SLIMBUS_P52_INT_con_int52_START   (1)
#define SOC_ASP_SLIMBUS_P52_INT_con_int52_END     (1)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int52_START  (2)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int52_END    (2)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int52_START   (3)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int52_END     (3)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int52_START   (4)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int52_END     (4)
#define SOC_ASP_SLIMBUS_P52_INT_und_int52_START   (5)
#define SOC_ASP_SLIMBUS_P52_INT_und_int52_END     (5)
#define SOC_ASP_SLIMBUS_P52_INT_act_int53_START   (8)
#define SOC_ASP_SLIMBUS_P52_INT_act_int53_END     (8)
#define SOC_ASP_SLIMBUS_P52_INT_con_int53_START   (9)
#define SOC_ASP_SLIMBUS_P52_INT_con_int53_END     (9)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int53_START  (10)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int53_END    (10)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int53_START   (11)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int53_END     (11)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int53_START   (12)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int53_END     (12)
#define SOC_ASP_SLIMBUS_P52_INT_und_int53_START   (13)
#define SOC_ASP_SLIMBUS_P52_INT_und_int53_END     (13)
#define SOC_ASP_SLIMBUS_P52_INT_act_int54_START   (16)
#define SOC_ASP_SLIMBUS_P52_INT_act_int54_END     (16)
#define SOC_ASP_SLIMBUS_P52_INT_con_int54_START   (17)
#define SOC_ASP_SLIMBUS_P52_INT_con_int54_END     (17)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int54_START  (18)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int54_END    (18)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int54_START   (19)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int54_END     (19)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int54_START   (20)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int54_END     (20)
#define SOC_ASP_SLIMBUS_P52_INT_und_int54_START   (21)
#define SOC_ASP_SLIMBUS_P52_INT_und_int54_END     (21)
#define SOC_ASP_SLIMBUS_P52_INT_act_int55_START   (24)
#define SOC_ASP_SLIMBUS_P52_INT_act_int55_END     (24)
#define SOC_ASP_SLIMBUS_P52_INT_con_int55_START   (25)
#define SOC_ASP_SLIMBUS_P52_INT_con_int55_END     (25)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int55_START  (26)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int55_END    (26)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int55_START   (27)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int55_END     (27)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int55_START   (28)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int55_END     (28)
#define SOC_ASP_SLIMBUS_P52_INT_und_int55_START   (29)
#define SOC_ASP_SLIMBUS_P52_INT_und_int55_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P56_INT_UNION
 结构说明  : P56_INT 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int56  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int56  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int56 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int56  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int56  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int56  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int57  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int57  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int57 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int57  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int57  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int57  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int58  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int58  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int58 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int58  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int58  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int58  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int59  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int59  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int59 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int59  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int59  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int59  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P56_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_INT_act_int56_START   (0)
#define SOC_ASP_SLIMBUS_P56_INT_act_int56_END     (0)
#define SOC_ASP_SLIMBUS_P56_INT_con_int56_START   (1)
#define SOC_ASP_SLIMBUS_P56_INT_con_int56_END     (1)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int56_START  (2)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int56_END    (2)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int56_START   (3)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int56_END     (3)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int56_START   (4)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int56_END     (4)
#define SOC_ASP_SLIMBUS_P56_INT_und_int56_START   (5)
#define SOC_ASP_SLIMBUS_P56_INT_und_int56_END     (5)
#define SOC_ASP_SLIMBUS_P56_INT_act_int57_START   (8)
#define SOC_ASP_SLIMBUS_P56_INT_act_int57_END     (8)
#define SOC_ASP_SLIMBUS_P56_INT_con_int57_START   (9)
#define SOC_ASP_SLIMBUS_P56_INT_con_int57_END     (9)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int57_START  (10)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int57_END    (10)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int57_START   (11)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int57_END     (11)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int57_START   (12)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int57_END     (12)
#define SOC_ASP_SLIMBUS_P56_INT_und_int57_START   (13)
#define SOC_ASP_SLIMBUS_P56_INT_und_int57_END     (13)
#define SOC_ASP_SLIMBUS_P56_INT_act_int58_START   (16)
#define SOC_ASP_SLIMBUS_P56_INT_act_int58_END     (16)
#define SOC_ASP_SLIMBUS_P56_INT_con_int58_START   (17)
#define SOC_ASP_SLIMBUS_P56_INT_con_int58_END     (17)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int58_START  (18)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int58_END    (18)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int58_START   (19)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int58_END     (19)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int58_START   (20)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int58_END     (20)
#define SOC_ASP_SLIMBUS_P56_INT_und_int58_START   (21)
#define SOC_ASP_SLIMBUS_P56_INT_und_int58_END     (21)
#define SOC_ASP_SLIMBUS_P56_INT_act_int59_START   (24)
#define SOC_ASP_SLIMBUS_P56_INT_act_int59_END     (24)
#define SOC_ASP_SLIMBUS_P56_INT_con_int59_START   (25)
#define SOC_ASP_SLIMBUS_P56_INT_con_int59_END     (25)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int59_START  (26)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int59_END    (26)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int59_START   (27)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int59_END     (27)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int59_START   (28)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int59_END     (28)
#define SOC_ASP_SLIMBUS_P56_INT_und_int59_START   (29)
#define SOC_ASP_SLIMBUS_P56_INT_und_int59_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P60_INT_UNION
 结构说明  : P60_INT 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: each register contains data for 4 consecutive data ports
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  act_int60  : 1;  /* bit[0] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int60  : 1;  /* bit[1] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int60 : 1;  /* bit[2] : Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int60  : 1;  /* bit[3] : Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int60  : 1;  /* bit[4] : Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int60  : 1;  /* bit[5] : Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_0 : 1;  /* bit[6] : unused, fixed to 0 */
        unsigned int  reserved_1 : 1;  /* bit[7] : unused, fixed to 0 */
        unsigned int  act_int61  : 1;  /* bit[8] : Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int61  : 1;  /* bit[9] : Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int61 : 1;  /* bit[10]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int61  : 1;  /* bit[11]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int61  : 1;  /* bit[12]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int61  : 1;  /* bit[13]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_2 : 1;  /* bit[14]: unused, fixed to 0 */
        unsigned int  reserved_3 : 1;  /* bit[15]: unused, fixed to 0 */
        unsigned int  act_int62  : 1;  /* bit[16]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int62  : 1;  /* bit[17]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int62 : 1;  /* bit[18]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int62  : 1;  /* bit[19]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int62  : 1;  /* bit[20]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int62  : 1;  /* bit[21]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_4 : 1;  /* bit[22]: unused, fixed to 0 */
        unsigned int  reserved_5 : 1;  /* bit[23]: unused, fixed to 0 */
        unsigned int  act_int63  : 1;  /* bit[24]: Channel activation
                                                   Set when channel connected with Data Port # is being activated or being deactivated.
                                                   Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  con_int63  : 1;  /* bit[25]: Channel content definition
                                                   Set when content definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  chan_int63 : 1;  /* bit[26]: Channel definition
                                                   Set when definition of the channel connected with Data Port # is being changed (consequence of NEXT_DEFINE_CHANNEL message).
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  dma_int63  : 1;  /* bit[27]: Data Port DMA request
                                                   Set when DMA request is raised for Data Port #.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  ovf_int63  : 1;  /* bit[28]: Data Port FIFO overflow
                                                   Set when overflow occurs at Data Port #.
                                                   Overflow condition may occur, for Sink Data Ports, for Isochronous or Pushed protocol when Data Segment rate is higher than the rate of outgoing data at the Data Port interface.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  und_int63  : 1;  /* bit[29]: Data port FIFO underrun
                                                   Set when underrun occurs at Data Port #.
                                                   Underrun condition may occur, for Source Data Ports, for Isochronous protocol when rate of incoming data at the Data Port interface is lower than Data Segment rate.
                                                   Cleared when writing 1 to the same bit. */
        unsigned int  reserved_6 : 1;  /* bit[30]: unused, fixed to 0 */
        unsigned int  reserved_7 : 1;  /* bit[31]: unused, fixed to 0 */
    } reg;
} SOC_ASP_SLIMBUS_P60_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_INT_act_int60_START   (0)
#define SOC_ASP_SLIMBUS_P60_INT_act_int60_END     (0)
#define SOC_ASP_SLIMBUS_P60_INT_con_int60_START   (1)
#define SOC_ASP_SLIMBUS_P60_INT_con_int60_END     (1)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int60_START  (2)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int60_END    (2)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int60_START   (3)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int60_END     (3)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int60_START   (4)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int60_END     (4)
#define SOC_ASP_SLIMBUS_P60_INT_und_int60_START   (5)
#define SOC_ASP_SLIMBUS_P60_INT_und_int60_END     (5)
#define SOC_ASP_SLIMBUS_P60_INT_act_int61_START   (8)
#define SOC_ASP_SLIMBUS_P60_INT_act_int61_END     (8)
#define SOC_ASP_SLIMBUS_P60_INT_con_int61_START   (9)
#define SOC_ASP_SLIMBUS_P60_INT_con_int61_END     (9)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int61_START  (10)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int61_END    (10)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int61_START   (11)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int61_END     (11)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int61_START   (12)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int61_END     (12)
#define SOC_ASP_SLIMBUS_P60_INT_und_int61_START   (13)
#define SOC_ASP_SLIMBUS_P60_INT_und_int61_END     (13)
#define SOC_ASP_SLIMBUS_P60_INT_act_int62_START   (16)
#define SOC_ASP_SLIMBUS_P60_INT_act_int62_END     (16)
#define SOC_ASP_SLIMBUS_P60_INT_con_int62_START   (17)
#define SOC_ASP_SLIMBUS_P60_INT_con_int62_END     (17)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int62_START  (18)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int62_END    (18)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int62_START   (19)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int62_END     (19)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int62_START   (20)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int62_END     (20)
#define SOC_ASP_SLIMBUS_P60_INT_und_int62_START   (21)
#define SOC_ASP_SLIMBUS_P60_INT_und_int62_END     (21)
#define SOC_ASP_SLIMBUS_P60_INT_act_int63_START   (24)
#define SOC_ASP_SLIMBUS_P60_INT_act_int63_END     (24)
#define SOC_ASP_SLIMBUS_P60_INT_con_int63_START   (25)
#define SOC_ASP_SLIMBUS_P60_INT_con_int63_END     (25)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int63_START  (26)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int63_END    (26)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int63_START   (27)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int63_END     (27)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int63_START   (28)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int63_END     (28)
#define SOC_ASP_SLIMBUS_P60_INT_und_int63_START   (29)
#define SOC_ASP_SLIMBUS_P60_INT_und_int63_END     (29)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P0_STATE_0_UNION
 结构说明  : P0_STATE_0 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P0_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P0_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P0_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P0_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P0_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P0_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P0_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P0_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P0_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P0_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P0_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P0_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P0_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P0_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P0_STATE_1_UNION
 结构说明  : P0_STATE_1 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P0_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P0_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P0_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P0_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P0_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P0_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P0_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P0_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P1_STATE_0_UNION
 结构说明  : P1_STATE_0 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P1_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P1_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P1_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P1_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P1_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P1_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P1_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P1_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P1_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P1_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P1_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P1_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P1_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P1_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P1_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P1_STATE_1_UNION
 结构说明  : P1_STATE_1 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P1_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P1_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P1_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P1_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P1_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P1_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P1_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P1_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P1_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P2_STATE_0_UNION
 结构说明  : P2_STATE_0 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P2_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P2_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P2_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P2_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P2_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P2_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P2_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P2_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P2_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P2_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P2_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P2_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P2_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P2_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P2_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P2_STATE_1_UNION
 结构说明  : P2_STATE_1 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P2_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P2_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P2_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P2_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P2_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P2_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P2_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P2_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P2_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P3_STATE_0_UNION
 结构说明  : P3_STATE_0 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P3_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P3_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P3_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P3_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P3_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P3_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P3_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P3_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P3_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P3_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P3_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P3_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P3_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P3_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P3_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P3_STATE_1_UNION
 结构说明  : P3_STATE_1 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P3_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P3_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P3_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P3_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P3_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P3_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P3_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P3_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P3_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P4_STATE_0_UNION
 结构说明  : P4_STATE_0 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P4_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P4_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P4_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P4_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P4_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P4_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P4_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P4_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P4_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P4_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P4_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P4_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P4_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P4_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P4_STATE_1_UNION
 结构说明  : P4_STATE_1 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P4_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P4_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P4_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P4_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P4_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P4_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P4_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P4_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P5_STATE_0_UNION
 结构说明  : P5_STATE_0 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P5_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P5_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P5_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P5_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P5_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P5_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P5_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P5_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P5_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P5_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P5_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P5_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P5_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P5_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P5_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P5_STATE_1_UNION
 结构说明  : P5_STATE_1 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P5_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P5_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P5_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P5_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P5_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P5_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P5_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P5_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P5_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P6_STATE_0_UNION
 结构说明  : P6_STATE_0 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P6_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P6_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P6_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P6_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P6_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P6_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P6_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P6_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P6_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P6_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P6_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P6_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P6_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P6_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P6_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P6_STATE_1_UNION
 结构说明  : P6_STATE_1 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P6_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P6_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P6_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P6_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P6_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P6_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P6_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P6_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P6_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P7_STATE_0_UNION
 结构说明  : P7_STATE_0 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P7_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P7_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P7_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P7_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P7_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P7_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P7_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P7_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P7_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P7_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P7_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P7_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P7_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P7_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P7_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P7_STATE_1_UNION
 结构说明  : P7_STATE_1 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P7_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P7_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P7_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P7_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P7_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P7_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P7_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P7_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P7_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P8_STATE_0_UNION
 结构说明  : P8_STATE_0 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  reserved_0      : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_1      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_2      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P8_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P8_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P8_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P8_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P8_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P8_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P8_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P8_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P8_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P8_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P8_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P8_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P8_STATE_1_UNION
 结构说明  : P8_STATE_1 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P8_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P8_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P8_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P8_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P8_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P8_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P8_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P8_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P9_STATE_0_UNION
 结构说明  : P9_STATE_0 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P9_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P9_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P9_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P9_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P9_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P9_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P9_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P9_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P9_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P9_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P9_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P9_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P9_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P9_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P9_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P9_STATE_1_UNION
 结构说明  : P9_STATE_1 寄存器结构定义。地址偏移量:0x14C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P9_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P9_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P9_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P9_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P9_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P9_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P9_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P9_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P9_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P10_STATE_0_UNION
 结构说明  : P10_STATE_0 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P10_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P10_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P10_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P10_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P10_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P10_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P10_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P10_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P10_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P10_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P10_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P10_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P10_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P10_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P10_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P10_STATE_1_UNION
 结构说明  : P10_STATE_1 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P10_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P10_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P10_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P10_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P10_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P10_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P10_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P10_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P10_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P11_STATE_0_UNION
 结构说明  : P11_STATE_0 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P11_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P11_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P11_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P11_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P11_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P11_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P11_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P11_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P11_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P11_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P11_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P11_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P11_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P11_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P11_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P11_STATE_1_UNION
 结构说明  : P11_STATE_1 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P11_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P11_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P11_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P11_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P11_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P11_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P11_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P11_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P11_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P12_STATE_0_UNION
 结构说明  : P12_STATE_0 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P12_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P12_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P12_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P12_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P12_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P12_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P12_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P12_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P12_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P12_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P12_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P12_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P12_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P12_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P12_STATE_1_UNION
 结构说明  : P12_STATE_1 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P12_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P12_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P12_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P12_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P12_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P12_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P12_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P12_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P13_STATE_0_UNION
 结构说明  : P13_STATE_0 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P13_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P13_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P13_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P13_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P13_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P13_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P13_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P13_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P13_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P13_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P13_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P13_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P13_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P13_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P13_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P13_STATE_1_UNION
 结构说明  : P13_STATE_1 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P13_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P13_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P13_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P13_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P13_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P13_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P13_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P13_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P13_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P14_STATE_0_UNION
 结构说明  : P14_STATE_0 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P14_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P14_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P14_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P14_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P14_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P14_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P14_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P14_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P14_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P14_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P14_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P14_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P14_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P14_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P14_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P14_STATE_1_UNION
 结构说明  : P14_STATE_1 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P14_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P14_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P14_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P14_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P14_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P14_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P14_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P14_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P14_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P15_STATE_0_UNION
 结构说明  : P15_STATE_0 寄存器结构定义。地址偏移量:0x178，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P15_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P15_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P15_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P15_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P15_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P15_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P15_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P15_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P15_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P15_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P15_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P15_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P15_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P15_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P15_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P15_STATE_1_UNION
 结构说明  : P15_STATE_1 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P15_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P15_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P15_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P15_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P15_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P15_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P15_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P15_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P15_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P16_STATE_0_UNION
 结构说明  : P16_STATE_0 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P16_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P16_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P16_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P16_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P16_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P16_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P16_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P16_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P16_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P16_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P16_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P16_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P16_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P16_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P16_STATE_1_UNION
 结构说明  : P16_STATE_1 寄存器结构定义。地址偏移量:0x184，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P16_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P16_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P16_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P16_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P16_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P16_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P16_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P16_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P17_STATE_0_UNION
 结构说明  : P17_STATE_0 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P17_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P17_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P17_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P17_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P17_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P17_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P17_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P17_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P17_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P17_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P17_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P17_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P17_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P17_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P17_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P17_STATE_1_UNION
 结构说明  : P17_STATE_1 寄存器结构定义。地址偏移量:0x18C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P17_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P17_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P17_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P17_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P17_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P17_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P17_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P17_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P17_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P18_STATE_0_UNION
 结构说明  : P18_STATE_0 寄存器结构定义。地址偏移量:0x190，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P18_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P18_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P18_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P18_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P18_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P18_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P18_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P18_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P18_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P18_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P18_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P18_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P18_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P18_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P18_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P18_STATE_1_UNION
 结构说明  : P18_STATE_1 寄存器结构定义。地址偏移量:0x194，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P18_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P18_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P18_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P18_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P18_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P18_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P18_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P18_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P18_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P19_STATE_0_UNION
 结构说明  : P19_STATE_0 寄存器结构定义。地址偏移量:0x198，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P19_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P19_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P19_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P19_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P19_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P19_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P19_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P19_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P19_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P19_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P19_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P19_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P19_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P19_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P19_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P19_STATE_1_UNION
 结构说明  : P19_STATE_1 寄存器结构定义。地址偏移量:0x19C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P19_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P19_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P19_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P19_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P19_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P19_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P19_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P19_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P19_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P20_STATE_0_UNION
 结构说明  : P20_STATE_0 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P20_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P20_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P20_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P20_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P20_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P20_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P20_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P20_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P20_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P20_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P20_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P20_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P20_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P20_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P20_STATE_1_UNION
 结构说明  : P20_STATE_1 寄存器结构定义。地址偏移量:0x1A4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P20_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P20_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P20_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P20_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P20_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P20_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P20_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P20_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P21_STATE_0_UNION
 结构说明  : P21_STATE_0 寄存器结构定义。地址偏移量:0x1A8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P21_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P21_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P21_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P21_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P21_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P21_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P21_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P21_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P21_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P21_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P21_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P21_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P21_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P21_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P21_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P21_STATE_1_UNION
 结构说明  : P21_STATE_1 寄存器结构定义。地址偏移量:0x1AC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P21_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P21_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P21_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P21_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P21_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P21_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P21_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P21_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P21_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P22_STATE_0_UNION
 结构说明  : P22_STATE_0 寄存器结构定义。地址偏移量:0x1B0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P22_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P22_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P22_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P22_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P22_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P22_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P22_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P22_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P22_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P22_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P22_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P22_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P22_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P22_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P22_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P22_STATE_1_UNION
 结构说明  : P22_STATE_1 寄存器结构定义。地址偏移量:0x1B4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P22_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P22_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P22_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P22_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P22_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P22_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P22_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P22_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P22_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P23_STATE_0_UNION
 结构说明  : P23_STATE_0 寄存器结构定义。地址偏移量:0x1B8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P23_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P23_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P23_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P23_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P23_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P23_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P23_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P23_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P23_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P23_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P23_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P23_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P23_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P23_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P23_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P23_STATE_1_UNION
 结构说明  : P23_STATE_1 寄存器结构定义。地址偏移量:0x1BC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P23_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P23_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P23_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P23_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P23_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P23_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P23_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P23_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P23_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P24_STATE_0_UNION
 结构说明  : P24_STATE_0 寄存器结构定义。地址偏移量:0x1C0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P24_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P24_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P24_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P24_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P24_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P24_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P24_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P24_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P24_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P24_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P24_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P24_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P24_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P24_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P24_STATE_1_UNION
 结构说明  : P24_STATE_1 寄存器结构定义。地址偏移量:0x1C4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P24_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P24_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P24_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P24_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P24_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P24_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P24_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P24_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P25_STATE_0_UNION
 结构说明  : P25_STATE_0 寄存器结构定义。地址偏移量:0x1C8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P25_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P25_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P25_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P25_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P25_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P25_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P25_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P25_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P25_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P25_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P25_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P25_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P25_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P25_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P25_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P25_STATE_1_UNION
 结构说明  : P25_STATE_1 寄存器结构定义。地址偏移量:0x1CC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P25_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P25_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P25_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P25_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P25_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P25_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P25_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P25_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P25_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P26_STATE_0_UNION
 结构说明  : P26_STATE_0 寄存器结构定义。地址偏移量:0x1D0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P26_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P26_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P26_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P26_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P26_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P26_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P26_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P26_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P26_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P26_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P26_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P26_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P26_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P26_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P26_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P26_STATE_1_UNION
 结构说明  : P26_STATE_1 寄存器结构定义。地址偏移量:0x1D4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P26_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P26_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P26_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P26_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P26_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P26_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P26_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P26_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P26_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P27_STATE_0_UNION
 结构说明  : P27_STATE_0 寄存器结构定义。地址偏移量:0x1D8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P27_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P27_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P27_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P27_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P27_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P27_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P27_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P27_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P27_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P27_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P27_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P27_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P27_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P27_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P27_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P27_STATE_1_UNION
 结构说明  : P27_STATE_1 寄存器结构定义。地址偏移量:0x1DC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P27_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P27_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P27_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P27_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P27_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P27_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P27_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P27_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P27_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P28_STATE_0_UNION
 结构说明  : P28_STATE_0 寄存器结构定义。地址偏移量:0x1E0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P28_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P28_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P28_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P28_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P28_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P28_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P28_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P28_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P28_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P28_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P28_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P28_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P28_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P28_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P28_STATE_1_UNION
 结构说明  : P28_STATE_1 寄存器结构定义。地址偏移量:0x1E4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P28_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P28_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P28_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P28_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P28_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P28_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P28_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P28_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P29_STATE_0_UNION
 结构说明  : P29_STATE_0 寄存器结构定义。地址偏移量:0x1E8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P29_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P29_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P29_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P29_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P29_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P29_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P29_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P29_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P29_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P29_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P29_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P29_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P29_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P29_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P29_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P29_STATE_1_UNION
 结构说明  : P29_STATE_1 寄存器结构定义。地址偏移量:0x1EC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P29_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P29_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P29_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P29_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P29_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P29_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P29_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P29_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P29_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P30_STATE_0_UNION
 结构说明  : P30_STATE_0 寄存器结构定义。地址偏移量:0x1F0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P30_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P30_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P30_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P30_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P30_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P30_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P30_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P30_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P30_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P30_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P30_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P30_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P30_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P30_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P30_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P30_STATE_1_UNION
 结构说明  : P30_STATE_1 寄存器结构定义。地址偏移量:0x1F4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P30_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P30_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P30_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P30_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P30_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P30_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P30_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P30_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P30_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P31_STATE_0_UNION
 结构说明  : P31_STATE_0 寄存器结构定义。地址偏移量:0x1F8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P31_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P31_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P31_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P31_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P31_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P31_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P31_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P31_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P31_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P31_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P31_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P31_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P31_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P31_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P31_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P31_STATE_1_UNION
 结构说明  : P31_STATE_1 寄存器结构定义。地址偏移量:0x1FC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P31_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P31_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P31_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P31_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P31_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P31_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P31_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P31_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P31_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P32_STATE_0_UNION
 结构说明  : P32_STATE_0 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P32_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P32_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P32_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P32_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P32_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P32_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P32_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P32_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P32_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P32_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P32_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P32_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P32_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P32_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P32_STATE_1_UNION
 结构说明  : P32_STATE_1 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P32_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P32_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P32_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P32_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P32_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P32_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P32_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P32_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P33_STATE_0_UNION
 结构说明  : P33_STATE_0 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P33_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P33_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P33_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P33_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P33_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P33_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P33_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P33_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P33_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P33_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P33_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P33_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P33_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P33_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P33_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P33_STATE_1_UNION
 结构说明  : P33_STATE_1 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P33_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P33_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P33_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P33_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P33_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P33_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P33_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P33_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P33_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P34_STATE_0_UNION
 结构说明  : P34_STATE_0 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P34_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P34_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P34_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P34_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P34_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P34_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P34_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P34_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P34_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P34_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P34_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P34_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P34_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P34_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P34_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P34_STATE_1_UNION
 结构说明  : P34_STATE_1 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P34_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P34_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P34_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P34_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P34_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P34_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P34_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P34_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P34_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P35_STATE_0_UNION
 结构说明  : P35_STATE_0 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P35_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P35_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P35_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P35_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P35_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P35_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P35_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P35_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P35_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P35_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P35_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P35_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P35_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P35_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P35_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P35_STATE_1_UNION
 结构说明  : P35_STATE_1 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P35_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P35_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P35_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P35_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P35_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P35_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P35_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P35_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P35_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P36_STATE_0_UNION
 结构说明  : P36_STATE_0 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P36_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P36_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P36_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P36_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P36_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P36_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P36_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P36_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P36_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P36_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P36_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P36_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P36_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P36_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P36_STATE_1_UNION
 结构说明  : P36_STATE_1 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P36_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P36_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P36_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P36_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P36_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P36_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P36_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P36_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P37_STATE_0_UNION
 结构说明  : P37_STATE_0 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P37_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P37_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P37_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P37_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P37_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P37_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P37_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P37_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P37_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P37_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P37_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P37_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P37_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P37_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P37_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P37_STATE_1_UNION
 结构说明  : P37_STATE_1 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P37_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P37_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P37_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P37_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P37_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P37_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P37_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P37_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P37_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P38_STATE_0_UNION
 结构说明  : P38_STATE_0 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P38_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P38_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P38_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P38_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P38_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P38_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P38_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P38_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P38_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P38_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P38_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P38_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P38_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P38_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P38_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P38_STATE_1_UNION
 结构说明  : P38_STATE_1 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P38_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P38_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P38_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P38_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P38_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P38_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P38_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P38_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P38_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P39_STATE_0_UNION
 结构说明  : P39_STATE_0 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P39_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P39_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P39_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P39_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P39_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P39_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P39_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P39_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P39_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P39_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P39_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P39_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P39_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P39_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P39_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P39_STATE_1_UNION
 结构说明  : P39_STATE_1 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P39_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P39_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P39_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P39_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P39_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P39_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P39_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P39_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P39_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P40_STATE_0_UNION
 结构说明  : P40_STATE_0 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P40_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P40_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P40_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P40_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P40_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P40_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P40_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P40_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P40_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P40_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P40_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P40_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P40_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P40_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P40_STATE_1_UNION
 结构说明  : P40_STATE_1 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P40_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P40_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P40_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P40_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P40_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P40_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P40_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P40_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P41_STATE_0_UNION
 结构说明  : P41_STATE_0 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P41_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P41_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P41_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P41_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P41_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P41_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P41_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P41_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P41_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P41_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P41_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P41_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P41_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P41_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P41_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P41_STATE_1_UNION
 结构说明  : P41_STATE_1 寄存器结构定义。地址偏移量:0x24C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P41_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P41_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P41_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P41_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P41_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P41_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P41_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P41_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P41_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P42_STATE_0_UNION
 结构说明  : P42_STATE_0 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P42_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P42_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P42_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P42_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P42_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P42_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P42_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P42_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P42_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P42_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P42_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P42_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P42_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P42_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P42_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P42_STATE_1_UNION
 结构说明  : P42_STATE_1 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P42_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P42_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P42_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P42_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P42_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P42_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P42_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P42_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P42_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P43_STATE_0_UNION
 结构说明  : P43_STATE_0 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P43_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P43_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P43_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P43_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P43_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P43_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P43_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P43_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P43_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P43_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P43_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P43_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P43_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P43_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P43_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P43_STATE_1_UNION
 结构说明  : P43_STATE_1 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P43_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P43_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P43_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P43_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P43_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P43_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P43_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P43_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P43_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P44_STATE_0_UNION
 结构说明  : P44_STATE_0 寄存器结构定义。地址偏移量:0x260，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P44_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P44_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P44_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P44_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P44_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P44_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P44_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P44_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P44_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P44_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P44_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P44_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P44_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P44_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P44_STATE_1_UNION
 结构说明  : P44_STATE_1 寄存器结构定义。地址偏移量:0x264，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P44_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P44_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P44_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P44_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P44_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P44_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P44_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P44_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P45_STATE_0_UNION
 结构说明  : P45_STATE_0 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P45_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P45_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P45_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P45_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P45_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P45_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P45_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P45_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P45_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P45_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P45_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P45_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P45_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P45_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P45_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P45_STATE_1_UNION
 结构说明  : P45_STATE_1 寄存器结构定义。地址偏移量:0x26C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P45_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P45_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P45_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P45_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P45_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P45_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P45_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P45_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P45_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P46_STATE_0_UNION
 结构说明  : P46_STATE_0 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P46_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P46_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P46_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P46_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P46_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P46_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P46_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P46_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P46_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P46_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P46_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P46_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P46_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P46_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P46_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P46_STATE_1_UNION
 结构说明  : P46_STATE_1 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P46_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P46_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P46_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P46_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P46_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P46_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P46_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P46_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P46_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P47_STATE_0_UNION
 结构说明  : P47_STATE_0 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P47_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P47_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P47_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P47_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P47_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P47_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P47_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P47_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P47_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P47_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P47_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P47_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P47_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P47_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P47_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P47_STATE_1_UNION
 结构说明  : P47_STATE_1 寄存器结构定义。地址偏移量:0x27C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P47_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P47_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P47_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P47_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P47_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P47_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P47_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P47_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P47_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P48_STATE_0_UNION
 结构说明  : P48_STATE_0 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P48_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P48_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P48_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P48_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P48_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P48_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P48_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P48_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P48_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P48_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P48_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P48_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P48_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P48_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P48_STATE_1_UNION
 结构说明  : P48_STATE_1 寄存器结构定义。地址偏移量:0x284，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P48_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P48_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P48_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P48_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P48_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P48_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P48_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P48_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P49_STATE_0_UNION
 结构说明  : P49_STATE_0 寄存器结构定义。地址偏移量:0x288，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P49_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P49_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P49_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P49_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P49_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P49_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P49_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P49_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P49_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P49_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P49_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P49_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P49_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P49_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P49_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P49_STATE_1_UNION
 结构说明  : P49_STATE_1 寄存器结构定义。地址偏移量:0x28C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P49_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P49_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P49_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P49_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P49_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P49_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P49_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P49_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P49_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P50_STATE_0_UNION
 结构说明  : P50_STATE_0 寄存器结构定义。地址偏移量:0x290，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P50_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P50_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P50_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P50_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P50_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P50_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P50_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P50_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P50_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P50_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P50_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P50_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P50_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P50_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P50_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P50_STATE_1_UNION
 结构说明  : P50_STATE_1 寄存器结构定义。地址偏移量:0x294，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P50_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P50_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P50_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P50_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P50_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P50_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P50_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P50_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P50_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P51_STATE_0_UNION
 结构说明  : P51_STATE_0 寄存器结构定义。地址偏移量:0x298，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P51_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P51_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P51_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P51_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P51_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P51_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P51_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P51_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P51_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P51_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P51_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P51_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P51_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P51_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P51_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P51_STATE_1_UNION
 结构说明  : P51_STATE_1 寄存器结构定义。地址偏移量:0x29C，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P51_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P51_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P51_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P51_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P51_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P51_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P51_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P51_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P51_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P52_STATE_0_UNION
 结构说明  : P52_STATE_0 寄存器结构定义。地址偏移量:0x2A0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P52_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P52_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P52_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P52_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P52_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P52_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P52_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P52_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P52_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P52_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P52_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P52_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P52_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P52_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P52_STATE_1_UNION
 结构说明  : P52_STATE_1 寄存器结构定义。地址偏移量:0x2A4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P52_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P52_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P52_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P52_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P52_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P52_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P52_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P52_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P53_STATE_0_UNION
 结构说明  : P53_STATE_0 寄存器结构定义。地址偏移量:0x2A8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P53_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P53_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P53_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P53_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P53_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P53_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P53_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P53_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P53_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P53_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P53_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P53_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P53_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P53_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P53_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P53_STATE_1_UNION
 结构说明  : P53_STATE_1 寄存器结构定义。地址偏移量:0x2AC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P53_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P53_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P53_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P53_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P53_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P53_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P53_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P53_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P53_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P54_STATE_0_UNION
 结构说明  : P54_STATE_0 寄存器结构定义。地址偏移量:0x2B0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P54_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P54_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P54_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P54_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P54_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P54_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P54_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P54_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P54_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P54_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P54_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P54_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P54_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P54_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P54_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P54_STATE_1_UNION
 结构说明  : P54_STATE_1 寄存器结构定义。地址偏移量:0x2B4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P54_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P54_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P54_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P54_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P54_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P54_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P54_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P54_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P54_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P55_STATE_0_UNION
 结构说明  : P55_STATE_0 寄存器结构定义。地址偏移量:0x2B8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P55_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P55_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P55_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P55_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P55_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P55_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P55_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P55_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P55_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P55_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P55_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P55_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P55_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P55_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P55_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P55_STATE_1_UNION
 结构说明  : P55_STATE_1 寄存器结构定义。地址偏移量:0x2BC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P55_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P55_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P55_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P55_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P55_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P55_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P55_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P55_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P55_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P56_STATE_0_UNION
 结构说明  : P56_STATE_0 寄存器结构定义。地址偏移量:0x2C0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P56_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P56_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P56_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P56_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P56_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P56_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P56_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P56_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P56_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P56_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P56_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P56_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P56_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P56_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P56_STATE_1_UNION
 结构说明  : P56_STATE_1 寄存器结构定义。地址偏移量:0x2C4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P56_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P56_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P56_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P56_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P56_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P56_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P56_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P56_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P57_STATE_0_UNION
 结构说明  : P57_STATE_0 寄存器结构定义。地址偏移量:0x2C8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P57_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P57_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P57_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P57_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P57_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P57_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P57_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P57_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P57_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P57_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P57_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P57_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P57_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P57_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P57_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P57_STATE_1_UNION
 结构说明  : P57_STATE_1 寄存器结构定义。地址偏移量:0x2CC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P57_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P57_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P57_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P57_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P57_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P57_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P57_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P57_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P57_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P58_STATE_0_UNION
 结构说明  : P58_STATE_0 寄存器结构定义。地址偏移量:0x2D0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P58_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P58_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P58_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P58_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P58_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P58_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P58_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P58_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P58_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P58_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P58_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P58_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P58_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P58_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P58_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P58_STATE_1_UNION
 结构说明  : P58_STATE_1 寄存器结构定义。地址偏移量:0x2D4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P58_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P58_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P58_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P58_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P58_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P58_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P58_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P58_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P58_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P59_STATE_0_UNION
 结构说明  : P59_STATE_0 寄存器结构定义。地址偏移量:0x2D8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P59_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P59_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P59_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P59_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P59_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P59_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P59_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P59_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P59_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P59_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P59_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P59_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P59_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P59_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P59_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P59_STATE_1_UNION
 结构说明  : P59_STATE_1 寄存器结构定义。地址偏移量:0x2DC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P59_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P59_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P59_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P59_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P59_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P59_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P59_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P59_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P59_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P60_STATE_0_UNION
 结构说明  : P60_STATE_0 寄存器结构定义。地址偏移量:0x2E0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P60_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P60_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P60_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P60_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P60_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P60_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P60_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P60_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P60_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P60_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P60_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P60_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P60_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P60_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P60_STATE_1_UNION
 结构说明  : P60_STATE_1 寄存器结构定义。地址偏移量:0x2E4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P60_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P60_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P60_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P60_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P60_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P60_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P60_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P60_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P61_STATE_0_UNION
 结构说明  : P61_STATE_0 寄存器结构定义。地址偏移量:0x2E8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P61_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P61_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P61_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P61_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P61_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P61_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P61_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P61_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P61_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P61_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P61_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P61_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P61_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P61_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P61_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P61_STATE_1_UNION
 结构说明  : P61_STATE_1 寄存器结构定义。地址偏移量:0x2EC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P61_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P61_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P61_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P61_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P61_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P61_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P61_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P61_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P61_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P62_STATE_0_UNION
 结构说明  : P62_STATE_0 寄存器结构定义。地址偏移量:0x2F0，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P62_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P62_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P62_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P62_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P62_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P62_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P62_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P62_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P62_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P62_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P62_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P62_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P62_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P62_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P62_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P62_STATE_1_UNION
 结构说明  : P62_STATE_1 寄存器结构定义。地址偏移量:0x2F4，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P62_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P62_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P62_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P62_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P62_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P62_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P62_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P62_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P62_STATE_1_CH_LINK_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P63_STATE_0_UNION
 结构说明  : P63_STATE_0 寄存器结构定义。地址偏移量:0x2F8，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ACTIVE          : 1;  /* bit[0]    : Channel activated
                                                           HIGH if Data Port is activated.
                                                           Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
        unsigned int  CONTENT_DEFINED : 1;  /* bit[1]    : Channel content defined
                                                           HIGH if content the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
        unsigned int  CHANNEL_DEFINED : 1;  /* bit[2]    : Channel defined
                                                           HIGH if the channel connected with Data Port is defined
                                                           (consequence of NEXT_DEFINE_CHANNEL message). */
        unsigned int  SINK            : 1;  /* bit[3]    : Sink direction
                                                           HIGH if Data Port is connected as Sink.
                                                           LOW if Data Port is disconnected or connected as Source. */
        unsigned int  OVF             : 1;  /* bit[4]    : Overflow
                                                           HIGH if overflow occurred for Data Port. */
        unsigned int  UND             : 1;  /* bit[5]    : Underrun
                                                           HIGH if underrun occurred for Data Port. */
        unsigned int  DPORT_READY     : 1;  /* bit[6]    : Data Port ready
                                                           Implemented only when access to the Data Port is selected through AHB.
                                                           In such case it notifies about one of the following conditions:
                                                           - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data).
                                                           - Corresponding Data Port FIFO is not empty.
                                                           When access to the Data Port is selected through Direct interface then tis bit is fixed to 0. */
        unsigned int  reserved_0      : 9;  /* bit[7-15] : unused, fixed to 0 */
        unsigned int  S_INTERVAL      : 11; /* bit[16-26]: Segment Interval
                                                           Segment Interval decoded from Segment Distribution defined for the connected channel.
                                                           Part of Channel Definition. */
        unsigned int  reserved_1      : 1;  /* bit[27]   : unused, fixed to 0 */
        unsigned int  TR_PROTOCOL     : 4;  /* bit[28-31]: Transport Protocol
                                                           Transport Protocol defined for the connected channel.
                                                           Part of Channel Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P63_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P63_STATE_0_ACTIVE_START           (0)
#define SOC_ASP_SLIMBUS_P63_STATE_0_ACTIVE_END             (0)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CONTENT_DEFINED_START  (1)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CONTENT_DEFINED_END    (1)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CHANNEL_DEFINED_START  (2)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CHANNEL_DEFINED_END    (2)
#define SOC_ASP_SLIMBUS_P63_STATE_0_SINK_START             (3)
#define SOC_ASP_SLIMBUS_P63_STATE_0_SINK_END               (3)
#define SOC_ASP_SLIMBUS_P63_STATE_0_OVF_START              (4)
#define SOC_ASP_SLIMBUS_P63_STATE_0_OVF_END                (4)
#define SOC_ASP_SLIMBUS_P63_STATE_0_UND_START              (5)
#define SOC_ASP_SLIMBUS_P63_STATE_0_UND_END                (5)
#define SOC_ASP_SLIMBUS_P63_STATE_0_DPORT_READY_START      (6)
#define SOC_ASP_SLIMBUS_P63_STATE_0_DPORT_READY_END        (6)
#define SOC_ASP_SLIMBUS_P63_STATE_0_S_INTERVAL_START       (16)
#define SOC_ASP_SLIMBUS_P63_STATE_0_S_INTERVAL_END         (26)
#define SOC_ASP_SLIMBUS_P63_STATE_0_TR_PROTOCOL_START      (28)
#define SOC_ASP_SLIMBUS_P63_STATE_0_TR_PROTOCOL_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_SLIMBUS_P63_STATE_1_UNION
 结构说明  : P63_STATE_1 寄存器结构定义。地址偏移量:0x2FC，初值:0x00000000，宽度:32
 寄存器说明: Content of these registers presents status of each data port
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  P_RATE      : 7;  /* bit[0-6]  : Presence Rate
                                                       Presence Rate defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  FR_LOCK     : 1;  /* bit[7]    : Frequency Lock
                                                       FR bit defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  DATA_TYPE   : 4;  /* bit[8-11] : Data Type
                                                       Data Type defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: unused, fixed to 0 */
        unsigned int  DATA_LENGTH : 6;  /* bit[16-21]: Data Length
                                                       Data Length defined for the connected channel.
                                                       Part of Content Definition. */
        unsigned int  reserved_1  : 2;  /* bit[22-23]: unused, fixed to 0 */
        unsigned int  PORT_LINKED : 6;  /* bit[24-29]: Number of Linked Port
                                                       This field contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH.
                                                       Value 6?b111111 (63) may indicate that the linked port has not been found despite of CH_LINK=1.
                                                       Part of Content Definition. */
        unsigned int  reserved_2  : 1;  /* bit[30]   : unused, fixed to 0 */
        unsigned int  CH_LINK     : 1;  /* bit[31]   : Channel Link
                                                       CL bit defined for the connected channel.
                                                       Part of Content Definition. */
    } reg;
} SOC_ASP_SLIMBUS_P63_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P63_STATE_1_P_RATE_START       (0)
#define SOC_ASP_SLIMBUS_P63_STATE_1_P_RATE_END         (6)
#define SOC_ASP_SLIMBUS_P63_STATE_1_FR_LOCK_START      (7)
#define SOC_ASP_SLIMBUS_P63_STATE_1_FR_LOCK_END        (7)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_TYPE_START    (8)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_TYPE_END      (11)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_LENGTH_START  (16)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_LENGTH_END    (21)
#define SOC_ASP_SLIMBUS_P63_STATE_1_PORT_LINKED_START  (24)
#define SOC_ASP_SLIMBUS_P63_STATE_1_PORT_LINKED_END    (29)
#define SOC_ASP_SLIMBUS_P63_STATE_1_CH_LINK_START      (31)
#define SOC_ASP_SLIMBUS_P63_STATE_1_CH_LINK_END        (31)






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

#endif /* end of soc_asp_slimbus_interface.h */
