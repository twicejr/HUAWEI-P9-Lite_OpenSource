/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ddrc_dmc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:46
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DDRC_DMC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DDRC_DMC_INTERFACE_H__
#define __SOC_DDRC_DMC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_DDRC_DMC
 ****************************************************************************/
/* 寄存器说明：DDRC_CTRL_SREF是DDRC自刷新控制寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_SREF_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_ADDR(base)        ((base) + (0x000))

/* 寄存器说明：DDRC_CTRL_INIT是DDRC初始化控制寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_INIT_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_ADDR(base)        ((base) + (0x004))

/* 寄存器说明：DDRC_CTRL_DDRRST是DDR3 复位控制寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_DDRRST_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ADDR(base)      ((base) + (0x008))

/* 寄存器说明：DDRC_CTRL_SFC是DDRC软件配置DDR命令启动寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_SFC_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_ADDR(base)         ((base) + (0x00C))

/* 寄存器说明：DDRC_CTRL_PERF是DDRC性能统计使能寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_PERF_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_ADDR(base)        ((base) + (0x010))

/* 寄存器说明：DDRC_CTRL_MTEST是DDRC软件配置MEMTEST启动寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_MTEST_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_ADDR(base)       ((base) + (0x014))

/* 寄存器说明：DDRC_CTRL_MCLR是DDRC软件配置MEMCLR启动寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CTRL_MCLR_UNION */
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_ADDR(base)        ((base) + (0x018))

/* 寄存器说明：DDRC_CFG_LP是dfi的lp接口的相关配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_LP_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_LP_ADDR(base)           ((base) + (0x01C))

/* 寄存器说明：DDRC_CFG_SREF是DDR自刷新配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SREF_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SREF_ADDR(base)         ((base) + (0x020))

/* 寄存器说明：DDRC_CFG_INIT是DDR初始化配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_INIT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_INIT_ADDR(base)         ((base) + (0x024))

/* 寄存器说明：DDRC_CFG_PD是DDR低功耗PowerDown状态配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_PD_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_PD_ADDR(base)           ((base) + (0x028))

/* 寄存器说明：DDRC_CFG_AREF是DDRC自动刷新模式配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_AREF_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_AREF_ADDR(base)         ((base) + (0x02C))

/* 寄存器说明：DDRC_CFG_ECC是DDRC ECC配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_ECC_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ADDR(base)          ((base) + (0x030))

/* 寄存器说明：DDRC_CFG_ERRINJ是DDRC ECC错误注入配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_ERRINJ_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_ADDR(base)       ((base) + (0x034))

/* 寄存器说明：DDRC_CFG_FIFO_ERRINJ
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_ADDR(base)  ((base) + (0x038))

/* 寄存器说明：DDRC_CFG_WORKMODE是DDRC工作模式配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_WORKMODE_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_ADDR(base)     ((base) + (0x040))

/* 寄存器说明：DDRC_CFG_WORKMODE2是DDRC工作模式配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_ADDR(base)    ((base) + (0x044))

/* 寄存器说明：DDRC_CFG_WORKMODE3是DDRC工作模式配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_ADDR(base)    ((base) + (0x048))

/* 寄存器说明：DDRC_CFG_DDRMODE是DDR工作模式配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DDRMODE_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR(base)      ((base) + (0x050))

/* 寄存器说明：DDRC_CFG_DIMM是对接DIMM时工作模式配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DIMM_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_ADDR(base)         ((base) + (0x054))

/* 寄存器说明：DDRC_CFG_SCRAMB是DDR数据加扰配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SCRAMB_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_ADDR(base)       ((base) + (0x058))

/* 寄存器说明：DDRC_CFG_LVCTRL是写命令低电平控制寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_LVCTRL_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_ADDR(base)       ((base) + (0x05C))

/* 寄存器说明：DDRC_CFG_RNKVOL是DDRC控制的每个RANK的DDR容量配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_RNKVOL_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(base, rnks)  ((base) + (0x060+0x4*(rnks)))

/* 寄存器说明：DDRC_CFG_ODT是DDR的ODT特性配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_ODT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_ODT_ADDR(base, rnks)    ((base) + (0x0A0+0x4*(rnks)))

/* 寄存器说明：DDRC_CFG_CA_ODT是LPDDR4的CA_ODT的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CA_ODT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ADDR(base)       ((base) + (0x0E0))

/* 寄存器说明：DDRC_CFG_EMRS01是DDR的模式寄存器0和模式寄存器1的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EMRS01_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_ADDR(base)       ((base) + (0x0F0))

/* 寄存器说明：DDRC_CFG_EMRS23是DDR的模式寄存器2和模式寄存器3的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EMRS23_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_ADDR(base)       ((base) + (0x0F4))

/* 寄存器说明：DDRC_CFG_EMRS45是DDR的模式寄存器4和模式寄存器5的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EMRS45_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_ADDR(base)       ((base) + (0x0F8))

/* 寄存器说明：DDRC_CFG_EMRS67是DDR的模式寄存器6和模式寄存器7的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EMRS67_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_ADDR(base)       ((base) + (0x0FC))

/* 寄存器说明：DDRC_CFG_TIMING0是DDRC的时序参数寄存器0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_ADDR(base)      ((base) + (0x100))

/* 寄存器说明：DDRC_CFG_TIMING1是DDRC的时序参数寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_ADDR(base)      ((base) + (0x104))

/* 寄存器说明：DDRC_CFG_TIMING2是DDRC的时序参数寄存器2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING2_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_ADDR(base)      ((base) + (0x108))

/* 寄存器说明：DDRC_CFG_TIMING3是DDRC的时序参数寄存器3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING3_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_ADDR(base)      ((base) + (0x10C))

/* 寄存器说明：DDRC_CFG_TIMING4是DDRC的时序参数寄存器4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING4_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_ADDR(base)      ((base) + (0x110))

/* 寄存器说明：DDRC_CFG_TIMING5是DDRC的时序参数寄存器5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING5_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_ADDR(base)      ((base) + (0x114))

/* 寄存器说明：DDRC_CFG_TIMING6是DDRC的时序参数寄存器6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING6_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_ADDR(base)      ((base) + (0x118))

/* 寄存器说明：DDRC_CFG_TIMING7是DDRC的时序参数寄存器7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING7_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_ADDR(base)      ((base) + (0x11C))

/* 寄存器说明：DDRC_CFG_TIMING8是DDRC的时序参数寄存器8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMING8_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_ADDR(base)      ((base) + (0x120))

/* 寄存器说明：DDRC_CFG_NXT_TIMING0是用于频率切换DDRC的时序参数寄存器0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_ADDR(base)  ((base) + (0x124))

/* 寄存器说明：DDRC_CFG_NXT_TIMING1是用于频率切换的DDRC的时序参数寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_ADDR(base)  ((base) + (0x128))

/* 寄存器说明：DDRC_CFG_NXT_TIMING2是用于频率切换的DDRC的时序参数寄存器2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_ADDR(base)  ((base) + (0x12C))

/* 寄存器说明：DDRC_CFG_TIMING3是用于频率切换的DDRC的时序参数寄存器3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_ADDR(base)  ((base) + (0x130))

/* 寄存器说明：DDRC_CFG_NXT_TIMING4是用于频率切换的DDRC的时序参数寄存器4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_ADDR(base)  ((base) + (0x134))

/* 寄存器说明：DDRC_CFG_NXT_TIMING5是用于频率切换的DDRC的时序参数寄存器5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_ADDR(base)  ((base) + (0x138))

/* 寄存器说明：DDRC_CFG_NXT_TIMING6是用于频率切换的DDRC的时序参数寄存器6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_ADDR(base)  ((base) + (0x13C))

/* 寄存器说明：DDRC_CFG_NXT_TIMING7是用于频率切换的DDRC的时序参数寄存器7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_ADDR(base)  ((base) + (0x140))

/* 寄存器说明：DDRC_CFG_NXT_TIMING8是DDRC的时序参数寄存器8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_ADDR(base)  ((base) + (0x144))

/* 寄存器说明：DDRC_CFG_BLDATA是DDRC写数据预接收写数据配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_BLDATA_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_ADDR(base)       ((base) + (0x148))

/* 寄存器说明：DDRC_CFG_DMCLVL是DDR控制器命令队列深度水线配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DMCLVL_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_ADDR(base)       ((base) + (0x14C))

/* 寄存器说明：DDRC_CFG_TIMEOUT是命令TIMEOUT配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_ADDR(base)      ((base) + (0x150))

/* 寄存器说明：DDRC_CFG_QOS是命令QOS配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_QOS_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ADDR(base)          ((base) + (0x154))

/* 寄存器说明：DDRC_CFG_EXMBIST_CMD是EXMBIST模块的命令配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_ADDR(base)  ((base) + (0x158))

/* 寄存器说明：DDRC_CFG_EXMBIST_DAT模块的数据DIN数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_ADDR(base)  ((base) + (0x15C))

/* 寄存器说明：DDRC_CFG_MBIST是MBIST的最高地址配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MBIST_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_ADDR(base)        ((base) + (0x160))

/* 寄存器说明：DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_ADDR(base) ((base) + (0x164))

/* 寄存器说明：DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_ADDR(base) ((base) + (0x168))

/* 寄存器说明：DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_ADDR(base) ((base) + (0x16C))

/* 寄存器说明：DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_ADDR(base) ((base) + (0x170))

/* 寄存器说明：DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_ADDR(base) ((base) + (0x174))

/* 寄存器说明：DDRC_CFG_OSC_PRD是Oscillator的读取间隔配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_ADDR(base)      ((base) + (0x178))

/* 寄存器说明：DDRC_CFG_OSC_CFG是Oacillator的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_ADDR(base)      ((base) + (0x17C))

/* 寄存器说明：DDRC_CFG_TRAIN是训练
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TRAIN_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_ADDR(base)        ((base) + (0x180))

/* 寄存器说明：DDRC_CFG_DFI_LAT0是dfi接口时序配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_ADDR(base)     ((base) + (0x184))

/* 寄存器说明：DDRC_CFG_DFI_LAT1是dfi接口时序配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_ADDR(base)     ((base) + (0x188))

/* 寄存器说明：DDRC_CFG_REC0是DDR4错误恢复配置寄存器0。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_REC0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_REC0_ADDR(base)         ((base) + (0x190))

/* 寄存器说明：DDRC_CFG_REC1是DDR4错误恢复配置寄存器1。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_REC1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_REC1_ADDR(base)         ((base) + (0x194))

/* 寄存器说明：DDRC_CFG_CRC是DDR4 CRC配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CRC_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ADDR(base)          ((base) + (0x198))

/* 寄存器说明：DDRC_CFG_CRC_ERRINJ0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_ADDR(base)  ((base) + (0x1A0))

/* 寄存器说明：DDRC_CFG_CRC_ERRINJ1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_ADDR(base)  ((base) + (0x1A4))

/* 寄存器说明：DDRC_CFG_PAR_ERRINJ0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_ADDR(base)  ((base) + (0x1A8))

/* 寄存器说明：DDRC_CFG_PAR_ERRINJ1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_ADDR(base)  ((base) + (0x1AC))

/* 寄存器说明：DDRC_CFG_DDRIO是DDR IO配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DDRPHY_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_ADDR(base)       ((base) + (0x200))

/* 寄存器说明：DDRC_CFG_AGING是PHY的防老化配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_AGING_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_AGING_ADDR(base)        ((base) + (0x204))

/* 寄存器说明：DDRC_CFG_SFCMASK是DDRC软件配置DDR命令MPC MASK寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_ADDR(base)     ((base) + (0x208))

/* 寄存器说明：DDRC_CFG_SFC_TIM是DDRC软件配置DDR命令的时序寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_ADDR(base)      ((base) + (0x20C))

/* 寄存器说明：DDRC_CTRL_SFC是DDRC软件配置DDR命令属性命令。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR(base)          ((base) + (0x210))

/* 寄存器说明：DDRC_CFG_SFC_ADDR0是SFC命令Que的配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_ADDR(base)    ((base) + (0x214))

/* 寄存器说明：DDRC_CFG_SFC_ADDR1是SFC读写memory地址配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_ADDR(base)    ((base) + (0x218))

/* 寄存器说明：DDRC_CFG_SFC_WDATA0是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_ADDR(base)   ((base) + (0x21C))

/* 寄存器说明：DDRC_CFG_SFC_WDATA1是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_ADDR(base)   ((base) + (0x220))

/* 寄存器说明：DDRC_CFG_SFC_WDATA2是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_ADDR(base)   ((base) + (0x224))

/* 寄存器说明：DDRC_CFG_SFC_WDATA3是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_ADDR(base)   ((base) + (0x228))

/* 寄存器说明：DDRC_CFG_SFC_WDATA4是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_ADDR(base)   ((base) + (0x22C))

/* 寄存器说明：DDRC_CFG_SFC_WDATA5是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_ADDR(base)   ((base) + (0x230))

/* 寄存器说明：DDRC_CFG_SFC_WDATA6是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_ADDR(base)   ((base) + (0x234))

/* 寄存器说明：DDRC_CFG_SFC_WDATA7是SFC写数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_ADDR(base)   ((base) + (0x238))

/* 寄存器说明：DDRC_CFG_SFC_WDATA_ECC是SFC写ECC数据配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_ADDR(base) ((base) + (0x23C))

/* 寄存器说明：DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测周期配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TMON_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TMON_ADDR(base)         ((base) + (0x240))

/* 寄存器说明：DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测RANK配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_ADDR(base)    ((base) + (0x244))

/* 寄存器说明：DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测刷新配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_ADDR(base)    ((base) + (0x248))

/* 寄存器说明：DDRC_CFG_MRR_MAP是单板连接重映射配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_ADDR(base)      ((base) + (0x250))

/* 寄存器说明：DDRC_CFG_STADAT是DDRC数据统计使能寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_STADAT_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR(base)       ((base) + (0x254))

/* 寄存器说明：DDRC_CFG_DATMIN是DMC命令计数的最小阀值寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DATMIN_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_ADDR(base)       ((base) + (0x258))

/* 寄存器说明：DDRC_CFG_DATMAX是DMC命令计数的最大阀值寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DATMAX_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_ADDR(base)       ((base) + (0x25C))

/* 寄存器说明：DDRC_CFG_STACMD是DDRC性能统计使能寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR(base)       ((base) + (0x260))

/* 寄存器说明：DDRC_CFG_CMDMIN是DMC命令计数的最小阀值寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CMDMIN_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_ADDR(base)       ((base) + (0x264))

/* 寄存器说明：DDRC_CFG_CMDMAX是DMC命令计数的最大阀值寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_CMDMAX_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_ADDR(base)       ((base) + (0x268))

/* 寄存器说明：DDRC_CFG_PERF是DDR性能统计的模式配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_PERF_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_PERF_ADDR(base)         ((base) + (0x26C))

/* 寄存器说明：DDRC_CFG_STAID是DDR性能统计的命令ID配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_STAID_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_STAID_ADDR(base)        ((base) + (0x270))

/* 寄存器说明：DDRC_CFG_STAID是DDR性能统计的命令ID MASK配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(base)     ((base) + (0x274))

/* 寄存器说明：DDRC_CFG_DUM_EN是DDR的dummy read开关控制寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DUM_EN_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_ADDR(base)       ((base) + (0x278))

/* 寄存器说明：DDRC_CFG_DUM_CFG是DDR的dummy read功能的配置寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_UNION */
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_ADDR(base)      ((base) + (0x27C))

/* 寄存器说明：DDRC_INTMSK是DDRC中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_INTMSK_UNION */
#define SOC_DDRC_DMC_DDRC_INTMSK_ADDR(base)           ((base) + (0x280))

/* 寄存器说明：DDRC_RINT是DDRC原始中断寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_RINT_UNION */
#define SOC_DDRC_DMC_DDRC_RINT_ADDR(base)             ((base) + (0x284))

/* 寄存器说明：DDRC_INTSTS是DDRC中断状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_INTSTS_UNION */
#define SOC_DDRC_DMC_DDRC_INTSTS_ADDR(base)           ((base) + (0x288))

/* 寄存器说明：DDRC_CURR_STATUS是DDRC状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_STATUS_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_ADDR(base)      ((base) + (0x290))

/* 寄存器说明：DDRC_CURR_FUNC是DDRC FUNC模块状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_FUNC_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_ADDR(base)        ((base) + (0x294))

/* 寄存器说明：DDRC_CURR_FUNC2是DDRC FUNC模块状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_FUNC2_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_ADDR(base)       ((base) + (0x298))

/* 寄存器说明：DDRC_CURR_FUNC3是DDRC FUNC模块状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_FUNC3_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_ADDR(base)       ((base) + (0x29C))

/* 寄存器说明：DDRC_CURR_EXECST是DDRC命令状态机状态。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_EXECST_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_ADDR(base)      ((base) + (0x2A0))

/* 寄存器说明：DDRC_CURR_WGFIFOST是DDRC写FIFO空满状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_UNION */
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_ADDR(base)    ((base) + (0x2A4))

/* 寄存器说明：DDRC_HIS_SERRADR0是DDRC ECC单比特错误低位地址状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_ADDR(base)    ((base) + (0x2D0))

/* 寄存器说明：DDRC_HIS_SERRADR1是DDRC ECC单比特错误高位地址状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_ADDR(base)    ((base) + (0x2D4))

/* 寄存器说明：DDRC_HIS_SERR_RDATA0是DDR ECC单比特错误读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_ADDR(base)  ((base) + (0x2D8))

/* 寄存器说明：DDRC_HIS_SERR_RDATA1是DDR ECC单比特错误读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_ADDR(base)  ((base) + (0x2DC))

/* 寄存器说明：DDRC_HIS_SERR_RDATA2是DDR ECC单比特错误读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_ADDR(base)  ((base) + (0x2E0))

/* 寄存器说明：DDRC_HIS_SERR_RDATA3是DDR ECC单比特错误读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_ADDR(base)  ((base) + (0x2E4))

/* 寄存器说明：DDRC_HIS_SERR_RDATA4是DDR ECC单比特错误读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_ADDR(base)  ((base) + (0x2E8))

/* 寄存器说明：DDRC_HIS_SERR_RDATA5是DDR ECC单比特错误读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_ADDR(base)  ((base) + (0x2EC))

/* 寄存器说明：DDRC_HIS_SERR_RDATA6是DDR ECC单比特错误读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_ADDR(base)  ((base) + (0x2F0))

/* 寄存器说明：DDRC_HIS_SERR_RDATA7是DDR ECC单比特错误读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_ADDR(base)  ((base) + (0x2F4))

/* 寄存器说明：DDRC_HIS_SERR_RDATA8是DDR ECC单比特错误读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_ADDR(base)  ((base) + (0x2F8))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA0是DDR ECC单比特错误时期望的正确读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_ADDR(base) ((base) + (0x2FC))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA1是DDR ECC单比特错误时期望的正确读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_ADDR(base) ((base) + (0x300))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA2是DDR ECC单比特错误时期望的正确读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_ADDR(base) ((base) + (0x304))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA3是DDR ECC单比特错误时期望的正确读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_ADDR(base) ((base) + (0x308))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA4是DDR ECC单比特错误时期望的正确读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_ADDR(base) ((base) + (0x30C))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA5是DDR ECC单比特错误时期望的正确读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_ADDR(base) ((base) + (0x310))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA6是DDR ECC单比特错误时期望的正确读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_ADDR(base) ((base) + (0x314))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA7是DDR ECC单比特错误时期望的正确读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_ADDR(base) ((base) + (0x318))

/* 寄存器说明：DDRC_HIS_SERR_EXPDATA8是DDR ECC单比特错误时期望的正确读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_ADDR(base) ((base) + (0x31C))

/* 寄存器说明：DDRC_HIS_MERRADR0是DDRC ECC多比特错误低位地址状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_ADDR(base)    ((base) + (0x320))

/* 寄存器说明：DDRC_HIS_MERRADR1是DDRC ECC多比特错误高位地址状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_ADDR(base)    ((base) + (0x324))

/* 寄存器说明：DDRC_HIS_MERRADR1是DDRC ECC多比特错误ID寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_ID_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_ADDR(base)      ((base) + (0x328))

/* 寄存器说明：DDRC_HIS_MERR_RDATA0是DDR ECC多比特错误读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_ADDR(base)  ((base) + (0x330))

/* 寄存器说明：DDRC_HIS_MERR_RDATA1是DDR ECC多比特错误读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_ADDR(base)  ((base) + (0x334))

/* 寄存器说明：DDRC_HIS_MERR_RDATA2是DDR ECC多比特错误读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_ADDR(base)  ((base) + (0x338))

/* 寄存器说明：DDRC_HIS_MERR_RDATA3是DDR ECC多比特错误读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_ADDR(base)  ((base) + (0x33C))

/* 寄存器说明：DDRC_HIS_MERR_RDATA4是DDR ECC多比特错误读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_ADDR(base)  ((base) + (0x340))

/* 寄存器说明：DDRC_HIS_MERR_RDATA5是DDR ECC多比特错误读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_ADDR(base)  ((base) + (0x344))

/* 寄存器说明：DDRC_HIS_MERR_RDATA6是DDR ECC多比特错误读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_ADDR(base)  ((base) + (0x348))

/* 寄存器说明：DDRC_HIS_MERR_RDATA7是DDR ECC多比特错误读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_ADDR(base)  ((base) + (0x34C))

/* 寄存器说明：DDRC_HIS_MERR_RDATA8是DDR ECC多比特错误读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_ADDR(base)  ((base) + (0x350))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA0是DDR ECC多比特错误时期望的正确读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_ADDR(base) ((base) + (0x354))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA1是DDR ECC多比特错误时期望的正确读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_ADDR(base) ((base) + (0x358))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA2是DDR ECC多比特错误时期望的正确读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_ADDR(base) ((base) + (0x35C))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA3是DDR ECC多比特错误时期望的正确读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_ADDR(base) ((base) + (0x360))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA4是DDR ECC多比特错误时期望的正确读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_ADDR(base) ((base) + (0x364))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA5是DDR ECC多比特错误时期望的正确读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_ADDR(base) ((base) + (0x368))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA6是DDR ECC多比特错误时期望的正确读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_ADDR(base) ((base) + (0x36C))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA7是DDR ECC多比特错误时期望的正确读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_ADDR(base) ((base) + (0x370))

/* 寄存器说明：DDRC_HIS_MERR_EXPDATA8是DDR ECC多比特错误时期望的正确读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_ADDR(base) ((base) + (0x374))

/* 寄存器说明：DDRC_HIS_SERRCNT是DDRC的ECC错误统计寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SERRCNT_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_ADDR(base)      ((base) + (0x378))

/* 寄存器说明：DDRC_HIS_SERRCNT是DDRC的ECC错误统计寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MERRCNT_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_ADDR(base)      ((base) + (0x37C))

/* 寄存器说明：DDRC_HIS_FLUX_WR是DDRC所有写命令流量统计寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_ADDR(base)      ((base) + (0x380))

/* 寄存器说明：DDRC_HIS_FLUX_RD是DDRC所有读命令流量统计寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_ADDR(base)      ((base) + (0x384))

/* 寄存器说明：DDRC_HIS_FLUX_WCMD是DDRC所有写命令数目
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_ADDR(base)    ((base) + (0x0388))

/* 寄存器说明：DDRC_HIS_FLUX_RCMD是DDRC所有读命令数目
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_ADDR(base)    ((base) + (0x038C))

/* 寄存器说明：DDRC_HIS_FLUXID_WR是DDRC指定ID写流量统计寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_ADDR(base)    ((base) + (0x390))

/* 寄存器说明：DDRC_HIS_FLUXID_RD是DDRC指定ID读流量统计寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_ADDR(base)    ((base) + (0x394))

/* 寄存器说明：DDRC_HIS_FLUXID_WCMD是DDRC所有写命令数目
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_ADDR(base)  ((base) + (0x0398))

/* 寄存器说明：DDRC_HIS_FLUX_RCMD是DDRC所有读命令数目
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_ADDR(base)  ((base) + (0x039C))

/* 寄存器说明：DDRC_HIS_WLATCNT0是DDRC指定ID的写命令Latency统计寄存器0。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_ADDR(base)     ((base) + (0x3A0))

/* 寄存器说明：DDRC_HIS_WLATCNT1是DDRC指定ID的写命令Latency统计寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_ADDR(base)     ((base) + (0x3A4))

/* 寄存器说明：DDRC_HIS_RLATCNT0是DDRC指定ID的读命令Latency统计寄存器0。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_ADDR(base)     ((base) + (0x3A8))

/* 寄存器说明：DDRC_HIS_RLATCNT1是DDRC指定ID的读命令Latency统计寄存器1。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_ADDR(base)     ((base) + (0x3AC))

/* 寄存器说明：DDRC_HIS_INHERE_RLAT_CNT是读通道固有延时寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_ADDR(base) ((base) + (0x3B0))

/* 寄存器说明：DDRC_STAT_RPT是DMC命令计数的累积寄存器的读指针
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_STAT_RPT_UNION */
#define SOC_DDRC_DMC_DDRC_STAT_RPT_ADDR(base)         ((base) + (0x3B4))

/* 寄存器说明：DDRC_HIS_CMD_SUM是DMC命令计数的累积寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_ADDR(base)      ((base) + (0x3B8))

/* 寄存器说明：DDRC_HIS_DAT_SUM是DMC命令计数的累积寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_ADDR(base)      ((base) + (0x3BC))

/* 寄存器说明：DDRC_HIS_PRE_CMD是DDRC所有统计的PRECHARGE命令个数
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_ADDR(base)      ((base) + (0x3C0))

/* 寄存器说明：DDRC_HIS_ACT_CMD是DDRC所有统计的ACTIVE命令个数
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_ADDR(base)      ((base) + (0x3C4))

/* 寄存器说明：DDRC_HIS_BNK_CHG是DDRC所有统计的BANK切换次数
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_ADDR(base)      ((base) + (0x3C8))

/* 寄存器说明：DDRC_HIS_RNK_CHG是DDRC所有统计的读写命令片选切换次数
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_ADDR(base)      ((base) + (0x3CC))

/* 寄存器说明：DDRC_HIS_RW_CHG是DDRC所有统计的读写命令切换次数
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RW_CHG_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_ADDR(base)       ((base) + (0x3D0))

/* 寄存器说明：DDRC_HIS_TMON_ERR是DMC循环读取LPDDR2/LPDDR3温度的错误状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_ADDR(base)     ((base) + (0x3E0))

/* 寄存器说明：DDRC_HIS_RERR_ADDRL是访问DMC禁止的RANK错误地址寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_ADDR(base)   ((base) + (0x3F0))

/* 寄存器说明：DDRC_HIS_RERR_ADDRH是访问DMC禁止的RANK错误地址寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_ADDR(base)   ((base) + (0x3F4))

/* 寄存器说明：DDRC_HIS_RERR_ID是访问DMC禁止的RANK错误ID寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RERR_ID_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_ADDR(base)      ((base) + (0x3F8))

/* 寄存器说明：DDRC_HIS_RERR_CNT是访问DMC禁止的RANK累积错误个数寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_ADDR(base)     ((base) + (0x3FC))

/* 寄存器说明：DDRC_HIS_REC_ERR0是DMC错误恢复过程中错误信息寄存器0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_ADDR(base)     ((base) + (0x400))

/* 寄存器说明：DDRC_HIS_REC_ERR0是DMC错误恢复过程中错误信息寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_ADDR(base)     ((base) + (0x404))

/* 寄存器说明：DDRC_HIS_EXMBIST_STATUS是EXMBIST模块的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_ADDR(base) ((base) + (0x40C))

/* 寄存器说明：DDRC_HIS_MTEST_ERR_INFO是MTEST错误指示寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_ADDR(base) ((base) + (0x410))

/* 寄存器说明：DDRC_HIS_RLATCNT0是Memory Test错误的地址
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_ADDR(base) ((base) + (0x414))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA0是DDR MTEST错误时期望的正确读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_ADDR(base) ((base) + (0x418))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA1是DDR MTEST多比特错误时期望的正确读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_ADDR(base) ((base) + (0x41C))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA2是DDR MTEST错误时期望的正确读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_ADDR(base) ((base) + (0x420))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA3是DDR MTEST多比特错误时期望的正确读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_ADDR(base) ((base) + (0x424))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA4是DDR MTEST错误时期望的正确读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_ADDR(base) ((base) + (0x428))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA5是DDR MTEST多比特错误时期望的正确读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_ADDR(base) ((base) + (0x42C))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA6是DDR MTEST错误时期望的正确读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_ADDR(base) ((base) + (0x430))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA7是DDR MTEST多比特错误时期望的正确读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_ADDR(base) ((base) + (0x434))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA8是DDR MTEST错误时期望的正确读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_ADDR(base) ((base) + (0x438))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA9是DDR MTEST多比特错误时期望的正确读数据9
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_ADDR(base) ((base) + (0x43C))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA10是DDR MTEST错误时期望的正确读数据10
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_ADDR(base) ((base) + (0x440))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA11是DDR MTEST多比特错误时期望的正确读数据11
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_ADDR(base) ((base) + (0x444))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA12是DDR MTEST错误时期望的正确读数据12
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_ADDR(base) ((base) + (0x448))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA13是DDR MTEST多比特错误时期望的正确读数据13
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_ADDR(base) ((base) + (0x44C))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA14是DDR MTEST错误时期望的正确读数据14
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_ADDR(base) ((base) + (0x450))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA15是DDR MTEST多比特错误时期望的正确读数据15
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_ADDR(base) ((base) + (0x454))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA16是DDR MTEST错误时期望的正确读数据16
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_ADDR(base) ((base) + (0x458))

/* 寄存器说明：DDRC_HIS_MTEST_EXPDATA17是DDR MTEST多比特错误时期望的正确读数据17
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_ADDR(base) ((base) + (0x45C))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA0是DDR MTEST错误时读数据0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_ADDR(base) ((base) + (0x460))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA1是DDR MTEST错误时读数据1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_ADDR(base) ((base) + (0x464))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA2是DDR MTEST错误时读数据2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_ADDR(base) ((base) + (0x468))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA3是DDR MTEST错误时读数据3
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_ADDR(base) ((base) + (0x46C))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA4是DDR MTEST错误时读数据4
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_ADDR(base) ((base) + (0x470))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA5是DDR MTEST错误时读数据5
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_ADDR(base) ((base) + (0x474))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA6是DDR MTEST错误时读数据6
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_ADDR(base) ((base) + (0x478))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA7是DDR MTEST错误时读数据7
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_ADDR(base) ((base) + (0x47C))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA8是DDR MTEST错误时读数据8
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_ADDR(base) ((base) + (0x480))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA9是DDR MTEST错误时读数据9
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_ADDR(base) ((base) + (0x484))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA10是DDR MTEST错误时读数据10
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_ADDR(base) ((base) + (0x488))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA11是DDR MTEST错误时读数据11
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_ADDR(base) ((base) + (0x48C))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA12是DDR MTEST错误时读数据12
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_ADDR(base) ((base) + (0x490))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA13是DDR MTEST错误时读数据13
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_ADDR(base) ((base) + (0x494))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA14是DDR MTEST错误时读数据14
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_ADDR(base) ((base) + (0x498))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA15是DDR MTEST错误时读数据15
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_ADDR(base) ((base) + (0x49C))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA16是DDR MTEST错误时读数据16
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_ADDR(base) ((base) + (0x4A0))

/* 寄存器说明：DDRC_HIS_MTEST_ERRDATA16是DDR MTEST错误时读数据16
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_ADDR(base) ((base) + (0x4A4))

/* 寄存器说明：DDRC_HIS_SFC_RDATA0是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_ADDR(base)   ((base) + (0x4A8))

/* 寄存器说明：DDRC_HIS_SFC_RDATA1是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_ADDR(base)   ((base) + (0x4AC))

/* 寄存器说明：DDRC_HIS_SFC_RDATA2是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_ADDR(base)   ((base) + (0x4B0))

/* 寄存器说明：DDRC_HIS_SFC_RDATA3是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_ADDR(base)   ((base) + (0x4B4))

/* 寄存器说明：DDRC_HIS_SFC_RDATA4是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_ADDR(base)   ((base) + (0x4B8))

/* 寄存器说明：DDRC_HIS_SFC_RDATA5是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_ADDR(base)   ((base) + (0x4BC))

/* 寄存器说明：DDRC_HIS_SFC_RDATA6是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_ADDR(base)   ((base) + (0x4C0))

/* 寄存器说明：DDRC_HIS_SFC_RDATA7是SFC读数据寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_ADDR(base)   ((base) + (0x4C4))

/* 寄存器说明：DDRC_HIS_SFC_RDATA_ECC是SFC读数据ECC寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_ADDR(base) ((base) + (0x4C8))

/* 寄存器说明：DDRC_HIS_SFC_RDATA_DBI是读数据对应的DBI寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_ADDR(base) ((base) + (0x4CC))

/* 寄存器说明：DDRC_HIS_SFC_RDATA_ECC_DBI是读ECC数据对应的DBI寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_UNION */
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_ADDR(base) ((base) + (0x4D0))

/* 寄存器说明：DDRC_FUNC_STAT0是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT0_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_ADDR(base)       ((base) + (0x4D4))

/* 寄存器说明：DDRC_FUNC_STAT1是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT1_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_ADDR(base)       ((base) + (0x4D8))

/* 寄存器说明：DDRC_FUNC_STAT2是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT2_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_ADDR(base)       ((base) + (0x4DC))

/* 寄存器说明：DDRC_FUNC_STAT3是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT3_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_ADDR(base)       ((base) + (0x4E0))

/* 寄存器说明：DDRC_FUNC_STAT4是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT4_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_ADDR(base)       ((base) + (0x4E4))

/* 寄存器说明：DDRC_FUNC_STAT5是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT5_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_ADDR(base)       ((base) + (0x4E8))

/* 寄存器说明：DDRC_FUNC_STAT6是fun的握手状态寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT6_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_ADDR(base)       ((base) + (0x4EC))

/* 寄存器说明：DDRC_FUNC_STAT7是fun的子模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT7_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_ADDR(base)       ((base) + (0x4F0))

/* 寄存器说明：DDRC_FUNC_STAT8是fun的子模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT8_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_ADDR(base)       ((base) + (0x4F4))

/* 寄存器说明：DDRC_FUNC_STAT9是fun的子模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT9_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_ADDR(base)       ((base) + (0x4F8))

/* 寄存器说明：DDRC_FUNC_STAT10是fun的子模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT10_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_ADDR(base)      ((base) + (0x4FC))

/* 寄存器说明：DDRC_FUNC_STAT11是fun的子模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_FUNC_STAT11_UNION */
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_ADDR(base)      ((base) + (0x500))

/* 寄存器说明：DDRC_FUNC_STAT11是主通路模块状态机寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_STAT12_UNION */
#define SOC_DDRC_DMC_STAT12_ADDR(base)                ((base) + (0x504))

/* 寄存器说明：DDRC_TEST_TMOD是DDR 中RAM的测试模式配置寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_UNION */
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ADDR(base)    ((base) + (0x508))

/* 寄存器说明：DDRC_TEST_RTL_CFG0是DDRC RTL参数信息寄存器0
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_UNION */
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_ADDR(base)    ((base) + (0x510))

/* 寄存器说明：DDRC_TEST_RTL_CFG1是DDRC RTL参数信息寄存器1
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_UNION */
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_ADDR(base)    ((base) + (0x514))

/* 寄存器说明：DDRC_TEST_RTL_CFG2是DDRC RTL参数信息寄存器2
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_UNION */
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_ADDR(base)    ((base) + (0x518))

/* 寄存器说明：DDRC_OSC_COUNT是Oscillator回读的值及基准寄存器的值。
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_OSC_COUNT_UNION */
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_ADDR(base, rnks)  ((base) + (0x520+0x4*(rnks)))

/* 寄存器说明：DDRC_EDXN_DQMAP是偶数rank的DQ MAP寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_EDXN_DQMAP_UNION */
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_ADDR(base, blanes)  ((base) + (0x580+0x8*(blanes)))

/* 寄存器说明：DDRC_ODXN_DQMAP是奇数rank的DQ MAP寄存器
   位域定义UNION结构:  SOC_DDRC_DMC_DDRC_ODXN_DQMAP_UNION */
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_ADDR(base, blanes)  ((base) + (0x584+0x8*(blanes)))





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
                     (1/1) register_DDRC_DMC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_SREF_UNION
 结构说明  : DDRC_CTRL_SREF 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: DDRC_CTRL_SREF是DDRC自刷新控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sref_req  : 1;  /* bit[0]   : SDRAM自刷新请求。
                                                    1：进入自刷新状态；
                                                    0：退出自刷新状态。 */
        unsigned int  sref_done : 1;  /* bit[1]   : DDRPHY自刷新操作完成。
                                                    1:配置从0到1的跳变表示DDRPHY完成所有自刷新退出后必须的操作，DMC可以接受新的请求； */
        unsigned int  reserved  : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_SREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_req_START   (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_req_END     (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_done_START  (1)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_done_END    (1)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_INIT_UNION
 结构说明  : DDRC_CTRL_INIT 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_INIT是DDRC初始化控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  init_req       : 1;  /* bit[0]   : 初始化启动。
                                                         1：启动SDRAM初始化操作；
                                                         0：完成初始化或处于正常工作状态。 */
        unsigned int  dfi_init_start : 1;  /* bit[1]   : DFI初始化启动。
                                                         1：启动DFI接口初始化，控制PHY进行相关的控制流程。
                                                         0：正常状态。
                                                         注意：这个bit在初始化完成以后，硬件自动清零。 */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_INIT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_init_req_START        (0)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_init_req_END          (0)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_dfi_init_start_START  (1)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_dfi_init_start_END    (1)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_DDRRST_UNION
 结构说明  : DDRC_CTRL_DDRRST 寄存器结构定义。地址偏移量:0x008，初值:0x00000001，宽度:32
 寄存器说明: DDRC_CTRL_DDRRST是DDR3 复位控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr3_rst_n : 1;  /* bit[0]   : DDR3 SDRAM复位。
                                                     1：复位无效；
                                                     0：复位有效。
                                                     注意：仅对DDR3 SDRAM有效，默认配置为1。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_DDRRST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_START  (0)
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_SFC_UNION
 结构说明  : DDRC_CTRL_SFC 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_SFC是DDRC软件配置DDR命令启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_req  : 1;  /* bit[0]   : 控制器配置命令执行请求。
                                                   1：请求执行命令；
                                                   0：不执行命令或者当命令执行完成后，自动将该参数清零。这时再次写一后操作将生效 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_SFC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_cmd_req_START   (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_cmd_req_END     (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_PERF_UNION
 结构说明  : DDRC_CTRL_PERF 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_PERF是DDRC性能统计使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perf_en  : 1;  /* bit[0]   : 性能统计使能。
                                                   1：使能；
                                                   0：禁止。
                                                    注意：在perf_mode=0时，此位使能表示性能统计寄存器将开始循环技术。在perf_mode=1时，完成一次统计之后，该位自动清零 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_PERF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_perf_en_START   (0)
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_perf_en_END     (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_MTEST_UNION
 结构说明  : DDRC_CTRL_MTEST 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_MTEST是DDRC软件配置MEMTEST启动寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_start : 1;  /* bit[0]   : 控制器配置命令执行请求。
                                                      1：请求执行命令；
                                                      0：不执行命令或者当命令执行完成后，自动将该参数清零。
                                                      
                                                      注意：如果选用EXMBIST模块，则该bit表示dmc的反压开始，EXMBIST是否真正运行取决于最后一条指令什么时候配置。当EXMBIST执行完后，该bit不会自动清零，需要软件将其配置为0来撤销反压。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_MTEST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_mtest_start_START  (0)
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_mtest_start_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CTRL_MCLR_UNION
 结构说明  : DDRC_CTRL_MCLR 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_MCLR是DDRC软件配置MEMCLR启动寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_start : 1;  /* bit[0]   : 控制器配置命令执行请求。
                                                     1：请求执行命令；
                                                     0：不执行命令或者当命令执行完成后，自动将该参数清零。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_MCLR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_mclr_start_START  (0)
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_mclr_start_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_LP_UNION
 结构说明  : DDRC_CFG_LP 寄存器结构定义。地址偏移量:0x01C，初值:0x000AF000，宽度:32
 寄存器说明: DDRC_CFG_LP是dfi的lp接口的相关配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lp_en      : 1;  /* bit[0]    : 硬件使能dfi的lp接口。
                                                      1：使能硬件自动控制LP接口；
                                                      0：由软件控制LP接口 */
        unsigned int  reserved_0 : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  lp_soft_en : 1;  /* bit[4]    : 软件请求PHY进入LP状态
                                                      1：软件请求PHY进入LP状态；
                                                      0：软件请求退出LP状态；
                                                      注意，当lp_en为0时，LP接口完全由软件控制，默认状态由软件控制，且软件处于未提请求的状态。 */
        unsigned int  lp_ack     : 1;  /* bit[5]    : lp接口的ack状态。
                                                      1：表示PHY处于Power down状态；
                                                      0：表示PHY处于非Power down状态。 */
        unsigned int  reserved_1 : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  tlp_wakeup : 4;  /* bit[8-11] : LP接口的tlp_wake时间,其档位与DFI协议一一对应。
                                                      'b0000: 16cycles
                                                      'b0001: 32cycles
                                                      'b0010: 64cycles
                                                      'b0011: 128cycles
                                                      'b0100: 256cycles
                                                      'b0101: 512cycles
                                                      'b0110: 1024cycles
                                                      'b0111: 2048cycles
                                                      'b1000: 4096cycles
                                                      'b1001: 8192cycles
                                                      'b1010: 16384cycles
                                                      'b1011: 32768cycles
                                                      'b1100: 65536cycles
                                                      'b1101: 131072cycles
                                                      'b1110: 262144cycles
                                                      'b1111: is unlimited
                                                      注意：PHY不一定支持所有的阀值，需要根据PHY的要求进行配置。 */
        unsigned int  tlp_resp   : 4;  /* bit[12-15]: LP接口的tlp_resp时间
                                                      0x0～0x1：1个时钟周期；
                                                      0x2～0xF：n个时钟周期。 */
        unsigned int  t_wcke     : 4;  /* bit[16-19]: 从cke拉低到phy进入低功耗所需等待时间。
                                                      0x0～0x1：1个时钟周期；
                                                      0x2～0xF：n个时钟周期。
                                                      因为在dmc侧将cke拉低后，cke需要穿过pub和phy，最终才能到达ddr。故在最终到达ddr之前，不能将iopowerdown或clk gating掉。 该参数根据不同的PHY会有所不同，针对G2 MultiPHY,在control SDR模式下该值需要使用0xa；如果pd_prd配置的值大于(bl/2+tcl+2)，则该值可以配置成0xa-(pd_prd-(bl/2+tcl+2)).对于control HDR模式，上述值配置可减半。 */
        unsigned int  reserved_2 : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_LP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_en_START       (0)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_en_END         (0)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_soft_en_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_soft_en_END    (4)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_ack_START      (5)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_ack_END        (5)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_wakeup_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_wakeup_END    (11)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_resp_START    (12)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_resp_END      (15)
#define SOC_DDRC_DMC_DDRC_CFG_LP_t_wcke_START      (16)
#define SOC_DDRC_DMC_DDRC_CFG_LP_t_wcke_END        (19)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SREF_UNION
 结构说明  : DDRC_CFG_SREF 寄存器结构定义。地址偏移量:0x020，初值:0x00000008，宽度:32
 寄存器说明: DDRC_CFG_SREF是DDR自刷新配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sref_cc           : 1;  /* bit[0]    : 自刷新模式，SDRAM时钟控制。
                                                             1：关断SDRAM时钟；
                                                             0：不关断SDRAM时钟。 */
        unsigned int  asref_fast_wakeup : 1;  /* bit[1]    : AUTO SELFREFRESH快速唤醒使能。
                                                             1：使能；
                                                             0：禁止。 */
        unsigned int  sref_pd           : 1;  /* bit[2]    : LPDDR4模式下，是否允许在自刷新下进入Powerdown */
        unsigned int  init_xsref        : 1;  /* bit[3]    : LPDDR4模式式，SREF模块是退出自刷新还是退出PD控制。
                                                             1：表示退出自刷新；
                                                             0：表示退出powerdown。
                                                             
                                                             注意：由于lpddr4退出自刷新和退出powerdown命令不一样，在初始化流程中要求是退出powerdown，在掉电流程中要求的是退出自刷新。 */
        unsigned int  sref_odis         : 1;  /* bit[4]    : 自刷新模式，DDR命令和数据IO的输出关断配置。
                                                             1：关断管脚输出；
                                                             0：不关断管脚输出。
                                                             注意：此配置为静态配置。建议当配置DDR进入self_refresh后，可配置为1，关断DDR命令和数据IO的输出。在配置DDR退出self_refresh前，配置为0，打开DDR命令和数据IO的输出。 */
        unsigned int  reserved_0        : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  clk_switch        : 1;  /* bit[8]    : DDRC低功耗时钟切换控制。DDRC进入低功耗状态（DDR Self Refresh）状态是否反压AXI接口命令。
                                                             1：反压接口命令，时钟切换完成后，继续执行原有命令；
                                                             0：不反压命令，直接返回OK响应，但数据是错误的。
                                                             
                                                             注：由于mddrc采用fast resp的方式。即对于写命令，在axi端口完成多路仲裁后就会返回resp，对于dmc侧的error无法识别。所以设计时这里无法采用返回err的方式。 */
        unsigned int  reserved_1        : 3;  /* bit[9-11] : 保留。 */
        unsigned int  sref_arefnum      : 4;  /* bit[12-15]: DDRn SDRAM在DFS流程中，退出自刷新后发出的自动刷新操作次数。
                                                             0x0：不发送自动刷新操作。
                                                             0x1～0xF：n次。 */
        unsigned int  asref_en          : 16; /* bit[16-31]: SDRAM自动进入SELFREFRESH使能。
                                                             1：使能；
                                                             0：禁止。
                                                             注意，每个RANK对应一个控制位，当DDRC_CFG_PD[PD_EN]有效，且RANK对应的asref_en有效时，这个RANK才能自动进入SELF REFRESH。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_cc_START            (0)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_cc_END              (0)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_fast_wakeup_START  (1)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_fast_wakeup_END    (1)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_pd_START            (2)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_pd_END              (2)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_init_xsref_START         (3)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_init_xsref_END           (3)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_odis_START          (4)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_odis_END            (4)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_clk_switch_START         (8)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_clk_switch_END           (8)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_arefnum_START       (12)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_arefnum_END         (15)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_en_START           (16)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_en_END             (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_INIT_UNION
 结构说明  : DDRC_CFG_INIT 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_INIT是DDR初始化配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  init_arefnum : 8;  /* bit[0-7] : DDRn SDRAM初始化过程中发出的自动刷新操作次数。
                                                       0x0～0x2：2次；
                                                       0x3～0xF：n次。 */
        unsigned int  wrlvl_en     : 1;  /* bit[8]   : DDR3初始化时，Write Leveling硬件自动控制使能。
                                                       1：使能；
                                                       0：禁止。
                                                       注意：仅针对DDR3有效。使能此配置后，会在完成DDR3初始化后，启动Write leveling流程。 */
        unsigned int  reserved     : 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_INIT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_INIT_init_arefnum_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_init_arefnum_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_wrlvl_en_START      (8)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_wrlvl_en_END        (8)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_PD_UNION
 结构说明  : DDRC_CFG_PD 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_PD是DDR低功耗PowerDown状态配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_en     : 1;  /* bit[0]    : SDRAM自动低功耗使能。
                                                     1：使能；
                                                     0：禁止。 */
        unsigned int  pd_ac     : 1;  /* bit[1]    : 低功耗模式（PowerDown），SDRAM 地址命令动态关断控制。
                                                     1：关断管脚输出；
                                                     0：不关断管脚输出。
                                                     注意：在pd_en使能下有效，控制管脚不包括CKE、ODT、CSN和RESET_N。 */
        unsigned int  pd_cc     : 1;  /* bit[2]    : 低功耗模式（PowerDown），SDRAM时钟控制。
                                                     1：关断SDRAM时钟；
                                                     0：不关断SDRAM时钟。
                                                     注意：该参数仅在外接DDR为LPDDR/LPDDR2 SDRAM时有效。 */
        unsigned int  reserved  : 1;  /* bit[3]    : 保留。 */
        unsigned int  pd_prd    : 12; /* bit[4-15] : SDRAM低功耗（Power Down）周期配置。当DDRC在连续的pd_prd个周期内没有接受到命令，则控制SDRAM进入到低功耗状态，当新命令到来，则控制SDRAM退出低功耗状态。
                                                     0x00：不进入power down状态；
                                                     0x01～0xFFF：n个时钟周期。
                                                     注意：该参数仅在pd_en为1时有效。 */
        unsigned int  t_clk_cke : 4;  /* bit[16-19]: CLK与CKE关系设置。
                                                     0x0~0x7：PHY关闭时钟相对CKE的延时，跟具体的DDRPHY相关。
                                                     例如SNPS G2 MULTIPHY配置为5；
                                                     SNPS 32PHY配置为0。 */
        unsigned int  asref_prd : 12; /* bit[20-31]: SDRAM低功耗（Auto Selfrefresh）周期配置。当DDRC在连续的asref_prd个周期内没有接受到命令，则控制SDRAM进入到自刷新状态，当新命令到来，则控制SDRAM退出低功耗状态。
                                                     0x0～0xFFF：nx1024个时钟周期。
                                                     注意：该参数仅在asref_en为1时有效。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_en_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_en_END        (0)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_ac_START      (1)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_ac_END        (1)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_cc_START      (2)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_cc_END        (2)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_prd_START     (4)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_prd_END       (15)
#define SOC_DDRC_DMC_DDRC_CFG_PD_t_clk_cke_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_PD_t_clk_cke_END    (19)
#define SOC_DDRC_DMC_DDRC_CFG_PD_asref_prd_START  (20)
#define SOC_DDRC_DMC_DDRC_CFG_PD_asref_prd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_AREF_UNION
 结构说明  : DDRC_CFG_AREF 寄存器结构定义。地址偏移量:0x02C，初值:0x00080000，宽度:32
 寄存器说明: DDRC_CFG_AREF是DDRC自动刷新模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 2;  /* bit[0-1]  : 保留。 */
        unsigned int  aref_opt       : 1;  /* bit[2]    : auto refresh优化使能。
                                                          1：使能自动刷新优化；
                                                          0：禁止自动刷新优化。
                                                          使能该功能时，aref_mode建议配置为11。DMC会在每次auto refreshi时动态检测DDR是否空闲，如果空闲，则发送AREF命令，否则将等待，直到AREF周期累积到9个AREF周期时，强行终止DDR访问，插入AREF命令。 */
        unsigned int  aref_dual_rank : 1;  /* bit[3]    : AREF模块发送REF命令的模式选择。
                                                          0：每次只向一个rank发送REF命令
                                                          1：每次会向两个rank发送REF命令。
                                                          
                                                          注意：该配置位只允许在初始化时配置，不支持在访问过程中动态切换。 */
        unsigned int  aref_alarm_en  : 1;  /* bit[4]    : 启动AREF功能中丢auto refresh进入自刷新功能，当丢失的个数达到aref_alarm_num+1个时：
                                                          1：使能；
                                                          0：不使能。 */
        unsigned int  pstpnd_level   : 2;  /* bit[5-6]  : 优化自动刷新模式的水线配置。
                                                          11：postponed命令水线为8；
                                                          10：postponed命令水线为4；
                                                          01：postponed命令水线为2；
                                                          00：postponed命令水线为1；
                                                          注意：如果在LPDDR2/LPDDR3模式下，如果tREFI<7.8us，由于tREFBW参数的限制，postponed必须小于等于4。 */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留。 */
        unsigned int  aref_alarm_num : 8;  /* bit[8-15] : 配置当无法发若干个auto refresh命令后，则会上报中断。
                                                          0x0~0xFF：（n+1）个auto refresh。(注意，但n=255时，由于计数器为8位，则进位后高位丢失，相当于1） */
        unsigned int  phyupd_level   : 4;  /* bit[16-19]: 当发起PHYUPD时，如果postponed的水线超过该寄存器配置的范围，则要将其排空到小于等于该水线。 */
        unsigned int  modified_mode  : 1;  /* bit[20]   : LPDDR4模式下postponed计数是使用modified mode还是legacy mode.
                                                          1: modified mode；
                                                          0:legacy mode。 */
        unsigned int  reserved_2     : 11; /* bit[21-31]:  */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_AREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_opt_START        (2)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_opt_END          (2)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_dual_rank_START  (3)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_dual_rank_END    (3)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_END     (4)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_pstpnd_level_START    (5)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_pstpnd_level_END      (6)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_phyupd_level_START    (16)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_phyupd_level_END      (19)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_modified_mode_START   (20)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_modified_mode_END     (20)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_ECC_UNION
 结构说明  : DDRC_CFG_ECC 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_ECC是DDRC ECC配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ecc_en   : 1;  /* bit[0]    : 表示外部是否连接ECC器件。
                                                    1：使能；
                                                    0：禁止。 */
        unsigned int  reserved_0: 3;  /* bit[1-3]  : 保留。 */
        unsigned int  eccwb_en : 1;  /* bit[4]    : ECC回写使能。
                                                    1：使能；
                                                    0：禁止。
                                                    当使能eccwb_en后，当发现ECC单比特错误时。DDRC将自动回写ECC校验后的数值，将DDR中存储的错误数据纠正。 */
        unsigned int  reserved_1: 3;  /* bit[5-7]  : 保留。 */
        unsigned int  ecc_byp  : 1;  /* bit[8]    : DDRC ECC Bypass 使能配置。
                                                    1：ECC Bypass使能；
                                                    0：ECC Bypass禁止。
                                                    正常模式时，配置为0,校验ECC数据；配置为1，不会校验ECC数据。在在ecc_en等于0时，硬件会强制将ecc_byp置1。 */
        unsigned int  ecc_msk  : 1;  /* bit[9]    : DDRPHY ECC 数据mask使能。
                                                    1：使能；
                                                    0：禁止。
                                                    当使能时，ecc数据不能写入内存，可以用于软件注入错误。 */
        unsigned int  reserved_2: 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_en_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_en_END      (0)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_eccwb_en_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_eccwb_en_END    (4)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_byp_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_byp_END     (8)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_msk_START   (9)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_msk_END     (9)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_ERRINJ_UNION
 结构说明  : DDRC_CFG_ERRINJ 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_ERRINJ是DDRC ECC错误注入配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_inject_mode : 2;  /* bit[0-1]  : ECC错误注入模式：
                                                           00：正常功能模式；
                                                           01：单次注入，通过第0bit的0->1跳变触发；
                                                           10：连续注入。 */
        unsigned int  reserved_0      : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  err_inject_bl0  : 5;  /* bit[4-8]  : ECC错误注入的Bytelane0。 */
        unsigned int  err_inject_bl1  : 5;  /* bit[9-13] : ECC错误注入的Bytelane1。 */
        unsigned int  reserved_1      : 2;  /* bit[14-15]: 保留。 */
        unsigned int  err_inject_mask : 16; /* bit[16-31]: 每个Bytelane内，ECC错误注入的位置(有9个bytelane）。
                                                           1：对该比特数据错误注入；
                                                           0：不处理。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ERRINJ_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_END    (1)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl0_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl0_END     (8)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl1_START   (9)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl1_END     (13)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_UNION
 结构说明  : DDRC_CFG_FIFO_ERRINJ 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_FIFO_ERRINJ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sbram_err_inj  : 2;  /* bit[0-1]  : SBRAM ECC注入模式：
                                                          00：正常模式；
                                                          01：1bit错误注入；
                                                          10：1bit错误注入；
                                                          11：2bit错误注入。
                                                          此寄存器配置后会连续注入错误，需要软件清零。 */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  rpram_err_inj  : 2;  /* bit[4-5]  : RPRAM ECC注入模式：
                                                          00：正常模式；
                                                          01：1bit错误注入；
                                                          10：1bit错误注入；
                                                          11：2bit错误注入。
                                                          此寄存器配置后会连续注入错误，需要软件清零。 */
        unsigned int  reserved_1     : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  recram_err_inj : 2;  /* bit[8-9]  : RECRAM ECC注入模式：
                                                          00：正常模式；
                                                          01：1bit错误注入；
                                                          10：1bit错误注入；
                                                          11：2bit错误注入。
                                                          此寄存器配置后会连续注入错误，需要软件清零。 */
        unsigned int  reserved_2     : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_END     (1)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_END     (5)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_recram_err_inj_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_recram_err_inj_END    (9)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_WORKMODE_UNION
 结构说明  : DDRC_CFG_WORKMODE 寄存器结构定义。地址偏移量:0x040，初值:0x00000020，宽度:32
 寄存器说明: DDRC_CFG_WORKMODE是DDRC工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_ratio     : 1;  /* bit[0]    : 控制器工作模式。
                                                         当clk_ratio2配置为0时：
                                                         1：DDRC与PHY频率比为1：2；
                                                         0：DDRC与PHY频率比为1：1。
                                                         
                                                         当clk_ratio2配置为1时：
                                                         1：保留；
                                                         0：DDRC与PHY频率比为1：4。 */
        unsigned int  cmd_clkon     : 1;  /* bit[1]    : 命令通道时钟开关：
                                                         1：强制打开时钟；
                                                         0：内部自动控制时钟。 */
        unsigned int  data_clkon    : 1;  /* bit[2]    : 数据通道时钟开关：
                                                         1：强制打开时钟；
                                                         0：内部自动控制时钟。 */
        unsigned int  func_clkon    : 1;  /* bit[3]    : 功能模块时钟开关：
                                                         1：强制打开时钟；
                                                         0：内部自动控制时钟。 */
        unsigned int  apre_en       : 1;  /* bit[4]    : Auto Precharge功能使能：
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  exmbist_clkon : 1;  /* bit[5]    : exmbist模块时钟开关：
                                                         1：强制打开时钟；
                                                         0：强制关闭时钟。 */
        unsigned int  reserved_0    : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  wrap_en       : 1;  /* bit[8]    : WRAP命令优化处理使能。
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  intlv_en      : 1;  /* bit[9]    : DMC BURST间插使能。
                                                         0：禁止；
                                                         1：使能。
                                                         在DDR4模式下，配置为1可以获得最高性能，其他模式建议配置为0。
                                                         
                                                         注意：在选用exmbist模块时，如果dmc与ddr接口位宽在SDR时不是2：1，在HDR时不是4：1，则禁止使能该位。 */
        unsigned int  addr_mode     : 2;  /* bit[10-11]: DDR地址线翻转模式选择。
                                                         00：IDLE时回到1状态；
                                                         01：IDLE时保持前一个命令的状态；
                                                         10：IDLE时与前一次状态取反；
                                                         11：IDLE时回到0状态。 */
        unsigned int  read_mode     : 1;  /* bit[12]   : 控制器读模式选择。
                                                         0：随路读模式；
                                                         1：延迟读模式。
                                                         随路读模式，是指控制器根据PHY送出的数据有效信号完成数据采样。
                                                         延迟读模式，是指控制器内部延迟等待完成对PHY送出数据的采样。
                                                         注意：该值在DDRC_DTRCTRL[train_mode]配置为0时，必须配置为0。 */
        unsigned int  hdr_mode      : 1;  /* bit[13]   : DFI接口模式选择。
                                                         0：SDR模式；
                                                         1：HDR模式。
                                                         改参数需要时钟和对应的DDRPHY工作模式配合。 */
        unsigned int  wr_intlv_en   : 1;  /* bit[14]   : DDR写BURST间插使能。
                                                         0：禁止；
                                                         1：使能。
                                                         在LPDDR4模式下，MASK WRITE会占用较多时间，如果一个DMC的BURST会转换成多个DDR MASK WRITE，使能此开关能够提升性能。 */
        unsigned int  clk_ratio2    : 1;  /* bit[15]   : 控制器与DDR器件时钟频率比例配置。
                                                         与clk_ratio共同作用。
                                                         0：基本模式；
                                                         1：扩展模式。 */
        unsigned int  qos_mode      : 1;  /* bit[16]   : 控制器QOS控制模式。
                                                         0：最低优先级流控模式；
                                                         1：普通模式。
                                                         配置为0时，进入DMC的优先级为7的命令被认为是流量溢出的命令，DMC调度时如果发现有其他优先级的命令，则会控制流量溢出的命令主动避让，保证带宽合理分配。 */
        unsigned int  reserved_1    : 1;  /* bit[17]   : 保留。 */
        unsigned int  wr_otf_en     : 1;  /* bit[18]   : LPDDR4模式下，写操作BL32/BL16 OTF使能。
                                                         0：禁止；
                                                         1：使能。
                                                         只有在配置LPDDR4为BL32，且lpddr4_bl32标记有效，并且brst_len,brst_len2的配置正确的前提下，rd_otf_en才允许配置为1。
                                                         其他模式下，必须配置为0。
                                                         
                                                         注意：该bit在运行过程中不能动态改变，如果是由于DFS时，由于brst_len/brst_len2改变后而需要相应调整，则需要先配置该位为合适的值，然后再配置brst_len/brst_len2. */
        unsigned int  rd_otf_en     : 1;  /* bit[19]   : LPDDR4模式下，读操作BL32/BL16 OTF使能。
                                                         0：禁止；
                                                         1：使能。
                                                         只有在配置LPDDR4为BL32，且lpddr4_bl32标记有效，并且brst_len,brst_len2的配置正确的前提下，rd_otf_en才允许配置为1。
                                                         其他模式下，必须配置为0。
                                                         
                                                         注意：该bit在运行过程中不能动态改变，如果是由于DFS时，由于brst_len/brst_len2改变后而需要相应调整，则需要先配置该位为合适的值，然后再配置brst_len/brst_len2. */
        unsigned int  reorder_en    : 1;  /* bit[20]   : 双通道读乱序使能：
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  reserved_2    : 3;  /* bit[21-23]: 保留。 */
        unsigned int  exclu_en      : 1;  /* bit[24]   : 排它命令使能。
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  reserved_3    : 3;  /* bit[25-27]: 保留。 */
        unsigned int  wr_rcv_mode   : 1;  /* bit[28]   : DDRC AXI端口写命令接收模式选择：
                                                         0：写命令直接接收模式；
                                                         1：写命令需要等待与其对应的写数据到来后，才被接收。 */
        unsigned int  reserved_4    : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_END        (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_START      (1)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_END        (1)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_START     (2)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_END       (2)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_START     (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_END       (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_apre_en_START        (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_apre_en_END          (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exmbist_clkon_START  (5)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exmbist_clkon_END    (5)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_START        (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_END          (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_intlv_en_START       (9)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_intlv_en_END         (9)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_addr_mode_START      (10)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_addr_mode_END        (11)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_read_mode_START      (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_read_mode_END        (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_START       (13)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_END         (13)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_intlv_en_START    (14)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_intlv_en_END      (14)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio2_START     (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio2_END       (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_qos_mode_START       (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_qos_mode_END         (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_otf_en_START      (18)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_otf_en_END        (18)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_rd_otf_en_START      (19)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_rd_otf_en_END        (19)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_START     (20)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_END       (20)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_START       (24)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_END         (24)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_START    (28)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_END      (28)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_UNION
 结构说明  : DDRC_CFG_WORKMODE2 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_WORKMODE2是DDRC工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rank_disable  : 16; /* bit[0-15] : RANK禁止开关：
                                                         1：禁止某个RANK的AUTO REFRESH/POWER DOWN/SELFREFRESH功能
                                                         0：正常工作模式。 */
        unsigned int  openpage_time : 14; /* bit[16-29]: OPEN PAGE延时控制：
                                                         0x0~0x1：禁止OPEN PAGE功能；
                                                         0x2~0x3fff：OPEN PAGE延时时间。
                                                         注意：DDRC_CFG_WORKMODE.apre_en使能时，OPEN PAGE功能失效 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_rank_disable_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_rank_disable_END     (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_openpage_time_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_openpage_time_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_UNION
 结构说明  : DDRC_CFG_WORKMODE3 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_WORKMODE3是DDRC工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tdbi     : 4;  /* bit[0-3]  : DBI功能使能时，器件的读数据返回延时。按DDR时钟域配置。 */
        unsigned int  tpl      : 4;  /* bit[4-7]  : DDR4模式下，使能CA PARITY以后，器件的parity latency。按DDR时钟域配置。 */
        unsigned int  tcal     : 4;  /* bit[8-11] : DDR4模式下，使能CAL功能时，器件的command address latency参数。按DDR时钟域配置。 */
        unsigned int  twrcslat : 4;  /* bit[12-15]: DFI接口WDATA_CS和RDATA_CS相对于wdata_en提前的拍数。按DDR时钟域配置。 */
        unsigned int  trdcslat : 4;  /* bit[16-19]: DFI接口WDATA_CS和RDATA_CS相对于rdata_en提前的拍数。按DDR时钟域配置。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tdbi_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tdbi_END        (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tpl_START       (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tpl_END         (7)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tcal_START      (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tcal_END        (11)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_twrcslat_START  (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_twrcslat_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_trdcslat_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_trdcslat_END    (19)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DDRMODE_UNION
 结构说明  : DDRC_CFG_DDRMODE 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DDRMODE是DDR工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram_type    : 4;  /* bit[0-3]  : 外部存储器类型。
                                                        0000：保留；
                                                        0001：LPDDR；
                                                        0010：LPDDR2； 
                                                        0011：LPDDR3；
                                                        0100：DDR；
                                                        0101：DDR2；
                                                        0110：DDR3；
                                                        0111：DDR4；
                                                        1000：LPDDR4；
                                                        其他：保留。 */
        unsigned int  mem_width    : 2;  /* bit[4-5]  : 存储数据总线位宽。
                                                        00： 8bit；
                                                        01： 16bit；
                                                        10： 32bit；
                                                        11： 64bit。 */
        unsigned int  reserved_0   : 1;  /* bit[6]    : 保留。 */
        unsigned int  brstlen2     : 1;  /* bit[7]    : 控制器Burst Length2配置。
                                                        1：扩展模式；
                                                        0：基本模式。
                                                        与brstlen共同作用。 */
        unsigned int  brstlen      : 1;  /* bit[8]    : 控制器Burst Length配置。
                                                        当brstlen2配置为0时，
                                                        1：BL8；
                                                        0：BL4。
                                                        当brstlen2配置为1时，
                                                        1：BL32；
                                                        0：BL16。
                                                        
                                                        DDR2可配置为Burst4和Burst8。
                                                        DDR3/4只能配置为Burst8模式。
                                                        LPDDR4可配置为Burst16和Burst32。
                                                        
                                                        注意：这里的burst len与dmc与phy的clk ratio有关系。其配置值应该是BLx/n(其中x表示4/8/16/32这几种burst类型，n表示dmc与phy的时钟关系为1:n）. 以clk ratio=1：2为例，如果要配置ddr bl32,只需要配置brstlen=0;brstlen2=1即可。 */
        unsigned int  wr_2t_pre    : 1;  /* bit[9]    : DDR4写方向2T PREAMBLE使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  rd_2t_pre    : 1;  /* bit[10]   : DDR4读方向2T PREAMBLE使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  cmd_2t_en    : 1;  /* bit[11]   : DDR 命令线2T TIMING 模式。
                                                        1：使能；
                                                        0：禁止。
                                                        注意，只对DDR2/DDR3/DDR4有效，其他模式下必须配置为0。配置为1时，命令延时会增加1拍。
                                                        当MDDRC代码配置为SDR模式时，必须要在系统中产生合适的tdm_en信号，否则此功能不能使用；当代码配置为HDR模式时，可以使用。 */
        unsigned int  bc_en        : 1;  /* bit[12]   : DDR3 Burst Chop模式使能。
                                                        1：使能；
                                                        0：禁止。
                                                        注意：只针对DDR3有效。 */
        unsigned int  lpddr4_bl32  : 1;  /* bit[13]   : LPDDR4 BURST32模式指示。
                                                        0：BL16；
                                                        1：BL32。
                                                        这个寄存器是用来表示LPDDR4处在哪种工作模式下，给DMC作为OTF的切换标记。它不能代替brst_len和brst_len2的配置。并且这些配置必须保持统一。
                                                        
                                                        注意：该bit在运行过程中不能动态改变，如果是由于DFS时，由于brst_len/brst_len2的改变而需要相应调整，则需要先配置该位为合适的值，然后再配置brst_len/brst_len2. */
        unsigned int  scramb_en    : 1;  /* bit[14]   : 数据加扰使能（使用地址作为种子产生扰码，然后与数据进行异或，以减少同步翻转）。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  crc_en       : 1;  /* bit[15]   : DDR4写数据CRC使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  zqc_en       : 1;  /* bit[16]   : Aref模块的SDRAM ZQ使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  odt_on       : 1;  /* bit[17]   : 输出给SDRAM的ODT信号为固定值。
                                                        0：由DDRC自动控制；
                                                        1：固定输出为rank0的wodt配置。 */
        unsigned int  rank_mode    : 2;  /* bit[18-19]: RANK交织模式。
                                                        00：单RANK模式；
                                                        01：单RANK模式；
                                                        10：双RANK交织；
                                                        11：四RANK交织。
                                                        注意：多RANK交织只有在RANK的配置完全相同时才能使用。否则将会出现不可预知的错误。 */
        unsigned int  rank         : 2;  /* bit[20-21]: 控制器Rank配置。
                                                        00：1个rank；
                                                        01：2个rank；
                                                        10：3个rank；
                                                        11：4个rank。
                                                        注意：当外接DDR器件大于4个RANK时，此控制位同时用于0-3,4-7,8-11,12-16四组RANK的控制 */
        unsigned int  sref_zqc_en  : 1;  /* bit[22]   : SREF退出时的SDRAM ZQ使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  asref_zqc_en : 1;  /* bit[23]   : asref退出时的SDRAM ZQ使能。
                                                        1：使能；
                                                        0：禁止。 */
        unsigned int  bank_xor     : 2;  /* bit[24-25]: BANK地址与ROW地址加扰使能。
                                                        0：禁止；
                                                        1：BANK与偏移地址0加扰；
                                                        2：BANK与偏移地址1加扰；
                                                        3：BANK与偏移地址2加扰； */
        unsigned int  reserved_1   : 2;  /* bit[26-27]: 保留。 */
        unsigned int  bank_mode    : 3;  /* bit[28-30]: BANK交织模式。
                                                        存储总线位宽为8bit时：
                                                        000:8byte交织；
                                                        001:16byte交织；
                                                        …
                                                        111:1kbyte交织。
                                                        存储总线位宽为16bit时：
                                                        000:16byte交织；
                                                        001:32byte交织；
                                                        …
                                                        111:2kbyte交织。
                                                        存储总线位宽为32bit时：
                                                        000:32byte交织；
                                                        001:64byte交织；
                                                        …
                                                        111:4kbyte交织。
                                                        存储总线位宽为64bit时：
                                                        000:64byte交织；
                                                        001:128byte交织；
                                                        …
                                                        111:8kbyte交织。
                                                        注意：当AXI的配置为非零时，这个域必须配置为000,以AXI配置模式工作。当AXI配置为000时，以DMC配置模式工作。 */
        unsigned int  reserved_2   : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DDRMODE_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_dram_type_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_dram_type_END       (3)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_mem_width_START     (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_mem_width_END       (5)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen2_START      (7)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen2_END        (7)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen_END         (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_wr_2t_pre_START     (9)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_wr_2t_pre_END       (9)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rd_2t_pre_START     (10)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rd_2t_pre_END       (10)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_cmd_2t_en_START     (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_cmd_2t_en_END       (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bc_en_START         (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bc_en_END           (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_lpddr4_bl32_START   (13)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_lpddr4_bl32_END     (13)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_scramb_en_START     (14)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_scramb_en_END       (14)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_crc_en_START        (15)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_crc_en_END          (15)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_START        (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_END          (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_odt_on_START        (17)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_odt_on_END          (17)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_mode_START     (18)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_mode_END       (19)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_START          (20)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_END            (21)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_sref_zqc_en_START   (22)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_sref_zqc_en_END     (22)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_asref_zqc_en_START  (23)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_asref_zqc_en_END    (23)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_xor_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_xor_END        (25)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_mode_START     (28)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_mode_END       (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DIMM_UNION
 结构说明  : DDRC_CFG_DIMM 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DIMM是对接DIMM时工作模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mirror   : 1;  /* bit[0]    : DDR3 DIMM的地址镜像使能。
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  reserved_0    : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  parity_en     : 1;  /* bit[4]    : DIMM奇偶校验使能。
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  reserved_1    : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  cke_share_map : 2;  /* bit[8-9]  : DIMM多RANK共享模式。
                                                         11:RANK0,3共享1个CKE管脚，
                                                         RANK1,2共享1个CKE管脚；
                                                         10：RANK0,2共享1个CKE管脚，RANK1,3共享1个CKE管脚；
                                                         01：RANK0,1共享1个CKE管脚，RANK2,3共享1个CKE管脚；
                                                         00：每个RANK单独1个CKE管脚；
                                                         其它保留。 */
        unsigned int  reserved_2    : 2;  /* bit[10-11]: 保留。 */
        unsigned int  par_dly       : 1;  /* bit[12]   : 根据DIMM的要求配置是否要延一个cycel.
                                                         0:表示parity_in信号不延时；
                                                         1:表示parity_in信号延时一个cycle */
        unsigned int  reserved_3    : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DIMM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_addr_mirror_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_addr_mirror_END      (0)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_parity_en_START      (4)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_parity_en_END        (4)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_cke_share_map_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_cke_share_map_END    (9)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_par_dly_START        (12)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_par_dly_END          (12)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SCRAMB_UNION
 结构说明  : DDRC_CFG_SCRAMB 寄存器结构定义。地址偏移量:0x058，初值:0x0008FC00，宽度:32
 寄存器说明: DDRC_CFG_SCRAMB是DDR数据加扰配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scramb_seed_sort : 3;  /* bit[0-2]  : 用于加扰的地址排列方式。
                                                            000：CS_BA_COL排列；
                                                            001：CS_COL_BA排列；
                                                            010：COL_CS_BA排列；
                                                            011：COL_BA_CS排列；
                                                            100：BA_CS_COL排列；
                                                            101：BA_COL_CS排列；
                                                            其他：保留。 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留。 */
        unsigned int  scramb_seed_type : 1;  /* bit[4]    : 用于加扰的地址模式。
                                                            0：用片选和BA加扰；
                                                            1：用片选、BA、和低位列地址加扰。 */
        unsigned int  reserved_1       : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  dmi_pattern      : 8;  /* bit[8-15] : dbi和dm同时使能时，当mask有效时，DQ上的pattern。该寄存器的[1:0]必须为0，其它6位1的个数不少于5。 */
        unsigned int  wr_dbi_en        : 1;  /* bit[16]   : 写方向DBI使能。
                                                            0：禁止；
                                                            1：使能。 */
        unsigned int  rd_dbi_en        : 1;  /* bit[17]   : 读方向DBI使能。
                                                            0：禁止；
                                                            1：使能。 */
        unsigned int  dbi_low_act      : 1;  /* bit[18]   : DBI有效电平。
                                                            0：高有效；
                                                            1：低有效。 */
        unsigned int  mrr_dbi_byp      : 1;  /* bit[19]   : 是否bypass读模式寄存器的DBI功能。
                                                            1：bypass mrr的dbi功能；
                                                            0：打开mrr的dbi功能。 */
        unsigned int  reserved_2       : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SCRAMB_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_sort_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_sort_END    (2)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_type_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_type_END    (4)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dmi_pattern_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dmi_pattern_END         (15)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_wr_dbi_en_START         (16)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_wr_dbi_en_END           (16)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_rd_dbi_en_START         (17)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_rd_dbi_en_END           (17)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dbi_low_act_START       (18)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dbi_low_act_END         (18)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_mrr_dbi_byp_START       (19)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_mrr_dbi_byp_END         (19)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_LVCTRL_UNION
 结构说明  : DDRC_CFG_LVCTRL 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_LVCTRL是写命令低电平控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lv_ctrl_en        : 1;  /* bit[0]    : 写命令间插低电平控制。即当连续N拍写数据后，可以间插低电平。
                                                             1：间插低电平使能（且lv_ctrl_threshold不为0）；
                                                             0：间插低电平关闭。
                                                             
                                                             注意，要先配置lv_ctrl_threshold，然后再使能lv_ctrl_en寄存器。 */
        unsigned int  lv_wren_ext       : 1;  /* bit[1]    : 是否使能wrdata_en的extended。
                                                             1：使能extended；
                                                             0：关闭extended功能；
                                                             
                                                             当lpddr4配置成支持1.5T的postamble时，就可以关闭extended功能。因为postamble就可以保证DQs上会多一拍0.但是仍然要将lv_ctrl_en置1，保证在多出的一个周期里写数据为0. */
        unsigned int  reserved          : 14; /* bit[2-15] : 保留。 */
        unsigned int  lv_ctrl_threshold : 16; /* bit[16-31]: 写命令间插低电平的时间。
                                                             0：表示关低该功能。
                                                             1~N：表示连续2^N个写命令。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_LVCTRL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_en_START         (0)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_en_END           (0)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_wren_ext_START        (1)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_wren_ext_END          (1)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_threshold_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_threshold_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_RNKVOL_UNION
 结构说明  : DDRC_CFG_RNKVOL 寄存器结构定义。地址偏移量:0x060+0x4*(rnks)，初值:0x00000022，宽度:32
 寄存器说明: DDRC_CFG_RNKVOL是DDRC控制的每个RANK的DDR容量配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_col       : 3;  /* bit[0-2]  : 单片SDRAM列地址位宽配置。
                                                         000：8 bit；
                                                         001：9 bit；
                                                         010：10 bit；
                                                         011：11 bit；
                                                         100：12 bit；
                                                         其它保留。
                                                         注意：DDRC不支持col地址小于8的器件（即32bit位宽，总容量64Mbit的LPDDR2器件）。 */
        unsigned int  reserved_0    : 1;  /* bit[3]    : 保留。 */
        unsigned int  mem_row       : 3;  /* bit[4-6]  : 单片SDRAM行地址位宽配置。
                                                         000：11 bit；
                                                         001：12 bit；
                                                         010：13 bit；
                                                         011：14 bit；
                                                         100：15 bit；
                                                         101：16 bit；
                                                         110: 17 bit；
                                                         111: 18 bit； */
        unsigned int  reserved_1    : 1;  /* bit[7]    : 保留。 */
        unsigned int  mem_bank      : 2;  /* bit[8-9]  : 单片SDRAM Bank数。
                                                         0：4 Bank；
                                                         1：8 Bank；
                                                         2：16 BANK；
                                                         3：保留。
                                                         
                                                         注意：对于DDR4，这里是配置成所有bank group中的bank之和。 */
        unsigned int  mem_bankgroup : 2;  /* bit[10-11]: 单片SDRAM Bank Group数。
                                                         0：1个Bank Group；
                                                         1：2个Bank Group；
                                                         2：4个Bank Group；
                                                         3：保留。
                                                         注意：只有在DDR4模式下有效。 */
        unsigned int  mem_map       : 2;  /* bit[12-13]: 保留。
                                                         
                                                         注意：目前地址映射固定采用R(rank)R(row)CBC的方式。其中Rank地址与Row地址的低位可以根据rank_mode的配置进行调换，以实现rank交织。Bank地址在列地址的中间，根据bank_mode完成不同粒度的交织。 */
        unsigned int  reserved_2    : 2;  /* bit[14-15]: 保留。 */
        unsigned int  mem_x4        : 1;  /* bit[16]   : 外接器件为4bit器件拼接模式。
                                                         0：外部由8/16/32bit器件拼接组成；
                                                         1：外部由4bit器件拼接组成。 */
        unsigned int  reserved_3    : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_RNKVOL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_col_START        (0)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_col_END          (2)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_row_START        (4)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_row_END          (6)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_END         (9)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bankgroup_START  (10)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bankgroup_END    (11)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_map_START        (12)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_map_END          (13)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_x4_START         (16)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_x4_END           (16)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_ODT_UNION
 结构说明  : DDRC_CFG_ODT 寄存器结构定义。地址偏移量:0x0A0+0x4*(rnks)，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_ODT是DDR的ODT特性配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wodt : 16; /* bit[0-15] : 当前RANK发送写命令时，其他RANK的ODT配置。
                                                1：使能写ODT；
                                                0：禁止写ODT。 */
        unsigned int  rodt : 16; /* bit[16-31]: 当前RANK发送读命令时，其他RANK的ODT配置。
                                                1：使能读ODT；
                                                0：禁止读ODT。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ODT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ODT_wodt_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_wodt_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_rodt_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_rodt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CA_ODT_UNION
 结构说明  : DDRC_CFG_CA_ODT 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CA_ODT是LPDDR4的CA_ODT的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ca_odt   : 16; /* bit[0-15] : 该寄存器直接控制LPDDR4的CA_ODT管脚。
                                                    注意：其位宽与当前DMC配置的rank个数相同，最大可以配置16个rank。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CA_ODT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ca_odt_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ca_odt_END      (15)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EMRS01_UNION
 结构说明  : DDRC_CFG_EMRS01 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EMRS01是DDR的模式寄存器0和模式寄存器1的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrs   : 16; /* bit[0-15] : DDRn SDRAM模式寄存器。 */
        unsigned int  emrs1 : 16; /* bit[16-31]: DDRn SDRAM扩展模式寄存器1。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS01_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_mrs_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_mrs_END      (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_emrs1_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_emrs1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EMRS23_UNION
 结构说明  : DDRC_CFG_EMRS23 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EMRS23是DDR的模式寄存器2和模式寄存器3的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emrs2 : 16; /* bit[0-15] : DDRn SDRAM扩展模式寄存器2。 */
        unsigned int  emrs3 : 16; /* bit[16-31]: DDRn SDRAM扩展模式寄存器3。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS23_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs2_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs2_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs3_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EMRS45_UNION
 结构说明  : DDRC_CFG_EMRS45 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EMRS45是DDR的模式寄存器4和模式寄存器5的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emrs4 : 16; /* bit[0-15] : DDRn SDRAM扩展模式寄存器4。 */
        unsigned int  emrs5 : 16; /* bit[16-31]: DDRn SDRAM扩展模式寄存器5。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS45_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs4_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs4_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs5_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EMRS67_UNION
 结构说明  : DDRC_CFG_EMRS67 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EMRS67是DDR的模式寄存器6和模式寄存器7的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emrs6 : 16; /* bit[0-15] : DDRn SDRAM扩展模式寄存器6。 */
        unsigned int  emrs7 : 16; /* bit[16-31]: DDRn SDRAM扩展模式寄存器7。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS67_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs6_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs6_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs7_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING0_UNION
 结构说明  : DDRC_CFG_TIMING0 寄存器结构定义。地址偏移量:0x100，初值:0xFFFFFF3F，宽度:32
 寄存器说明: DDRC_CFG_TIMING0是DDRC的时序参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tras     : 6;  /* bit[0-5]  : 同BANK的激活命令到到关闭命令（ACT to PRE）的等待周期。
                                                    0x00～0x01：1个时钟周期；
                                                    0x02～0x0F：n个时钟周期。 */
        unsigned int  reserved : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  trc      : 6;  /* bit[8-13] : 同BANK的激活命令到激活命令（active a bank to active a bank）的等待周期。
                                                    0x00～0x01：1个时钟周期；
                                                    0x02～0x3F：n个时钟周期。 */
        unsigned int  trcd     : 5;  /* bit[14-18]: 同BANK激活到读或写（ACT to READ or WRITE）命令的等待周期。
                                                    0x0～0x3：3时钟周期；
                                                    0x4～0xF：n时钟周期。 */
        unsigned int  trp_pb   : 5;  /* bit[19-23]: Per Bank关闭（PRE period）命令的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
        unsigned int  trrd     : 4;  /* bit[24-27]: 打开BANK A 到打开BANK B的（ACT bank a to ACT bank b）等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
        unsigned int  tmrd     : 4;  /* bit[28-31]: 模式寄存器加载（LMR）命令的等待周期(在DDR2，LPDDR2时候配置值为tMOD和tMRD的最大值，在DDR3时配置为tMRD）。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tras_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tras_END        (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trc_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trc_END         (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trcd_START      (14)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trcd_END        (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trp_pb_START    (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trp_pb_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trrd_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trrd_END        (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tmrd_START      (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tmrd_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING1_UNION
 结构说明  : DDRC_CFG_TIMING1 寄存器结构定义。地址偏移量:0x104，初值:0xFF200405，宽度:32
 寄存器说明: DDRC_CFG_TIMING1是DDRC的时序参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcl      : 6;  /* bit[0-5]  : DDR的读命令到读数据的延迟（CAS Latency）。
                                                    0x0～0x1： 1个时钟周期；
                                                    0x2～0xF： n个时钟周期。
                                                    如果是RDIMM模式CL应该配置为器件CL+1。 */
        unsigned int  reserved_0: 2;  /* bit[6-7]  : 保留。 */
        unsigned int  twl      : 6;  /* bit[8-13] : 写命令到写数据的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。
                                                    如：0x3：3个时钟周期。
                                                    注意：DDR2模式，twl配置为tcl-1，twl配置时应满足twl –taond >＝1。
                                                    如果是RDIMM模式WL应配置为器件WL+1。
                                                    注意：在LPDDR2/LPDDR3模式下，由于协议定义的WL比实际的延时小1cycle，所以需要配置为模式寄存器的值+1。 */
        unsigned int  tmrri    : 5;  /* bit[14-18]: LPDDR4模式下，tXP结束后，到MRR需要额外等待的时间。 */
        unsigned int  reserved_1: 1;  /* bit[19]   : 保留。 */
        unsigned int  trtw     : 4;  /* bit[20-23]: 最后一个读数据到第一个写数据延迟。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n+1个时钟周期。
                                                    注意：在DDR2/DDR3模式下，trtw参数主要考虑单板、封装、IO的延时；在LPDDR/LPDDR2/LPDDR3模式下，除了单板、封装、IO的延时，还需要加上tdqsckmax。 */
        unsigned int  tsre     : 8;  /* bit[24-31]: 退出自刷新（Self-Refresh）到读命令的等待周期。
                                                    0x0： 保留；
                                                    0x01～0xFF：n×4个时钟周期。
                                                    DDR3 SDRAM时，该值配置tXSDLL和tXS的最大值。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tcl_START       (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tcl_END         (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_twl_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_twl_END         (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tmrri_START     (14)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tmrri_END       (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_trtw_START      (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_trtw_END        (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tsre_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tsre_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING2_UNION
 结构说明  : DDRC_CFG_TIMING2 寄存器结构定义。地址偏移量:0x108，初值:0xF3FFF000，宽度:32
 寄存器说明: DDRC_CFG_TIMING2是DDRC的时序参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  taref    : 11; /* bit[0-10] : 自动刷新周期。
                                                    0x000：自动刷新禁止；
                                                    0x001～0x7FF：SDRAM刷新周期时间为16×n时钟周期。
                                                    如0x008：128个时钟周期（16×8）。
                                                    配置间隔时间为tREFI = 7800/16/tclk。Tclk为DMC域时钟的运行周期（注意，只有在clk ratio为1：1时，才与sdram的时钟周期相同）。 */
        unsigned int  reserved : 1;  /* bit[11]   : 保留。 */
        unsigned int  tfaw     : 6;  /* bit[12-17]: 连续4个激活命令周期。
                                                    0x00～0x3F：n个时钟周期；
                                                    如：0x14：20个时钟周期。 */
        unsigned int  trtrrd   : 6;  /* bit[18-23]: lpddr4协议中MPC读到普通读或是普通读到MPC读之间的时间参数。 */
        unsigned int  twtr     : 4;  /* bit[24-27]: 写操作最后一个写数据到读命令（write to read）的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xf：n个时钟周期。
                                                    如0x3：3个时钟周期。 */
        unsigned int  tcke     : 4;  /* bit[28-31]: 低功耗状态维持的最短时间。
                                                    0x0：保留；
                                                    0x1～0xF：n个时钟周期。
                                                    该值需要配置tCKESR, tCKSRE, tCKSRX, tCKE，tCPDED几个值中的最大值。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_taref_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_taref_END       (10)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tfaw_START      (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tfaw_END        (17)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_trtrrd_START    (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_trtrrd_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_twtr_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_twtr_END        (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tcke_START      (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tcke_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING3_UNION
 结构说明  : DDRC_CFG_TIMING3 寄存器结构定义。地址偏移量:0x10C，初值:0xFFFFE0F2，宽度:32
 寄存器说明: DDRC_CFG_TIMING3是DDRC的时序参数寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trtp    : 4;  /* bit[0-3]  : 读命令到关闭命令的等待延迟。
                                                   000～010：2个时钟周期；
                                                   011～111：n个时钟周期。
                                                   Trtp的计算公式如下：
                                                   DDR2:tRTP
                                                   DDR3:tRTP
                                                   DDR4:tRTP
                                                   LPDDR2:BL/2+max(2,RU(tRTP/tCK))-2;
                                                   LPDDR3:BL/2+max(4,RU(tRTP/tCK))-4;
                                                   LPDDR4:BL/2+max(8,RU(tRTP/tCK))-8;
                                                   
                                                   注意：这里的BL/2由硬件自动叠加上去，软件配置时不需要考虑。 */
        unsigned int  txard   : 4;  /* bit[4-7]  : 退出DDR低功耗状态等待周期。
                                                   0x0～0xF：n个时钟周期，n代表十进制数；
                                                   如：0x7：为7个时钟周期。
                                                   取{tXP,tXARD,tXARDS,tXS}中的最大值。
                                                   在DDR3模式下，取（tXP，tCKE的最大值）。 */
        unsigned int  taond   : 5;  /* bit[8-12] : ODT（On-die termination）打开和关闭周期。
                                                   DDR2模式下（taond/taofd）：
                                                   0x0：2/2.5；
                                                   0x1：3/3.5；
                                                   0x2：4/4.5；
                                                   0x3：5/5.5；
                                                   其它： 保留。
                                                   在DDR3模式下，该值配置为tWL-1；如果是1：2模式，则需要配成tWL-2。但是台研的phy已经单独处理，仍然采用tWL-1的配置。
                                                   在LPDDR3模式下，该值配置为tODTon(max)/tCK。 */
        unsigned int  tzqinit : 9;  /* bit[13-21]: ZQ初始化延迟周期。
                                                   0x0～0x1ff：nx4个时钟周期。
                                                   该值配置tZQINIT，tDLLK的最大值。 */
        unsigned int  tzq_prd : 10; /* bit[22-31]: ZQCS命令周期。
                                                   0x000：ZQCS命令禁止；
                                                   0x001～0x3FF： n×128个AREF周期。
                                                   ZQCS命令周期时间为n×128个taref时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_trtp_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_trtp_END       (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_txard_START    (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_txard_END      (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_taond_START    (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_taond_END      (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzqinit_START  (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzqinit_END    (21)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_START  (22)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING4_UNION
 结构说明  : DDRC_CFG_TIMING4 寄存器结构定义。地址偏移量:0x110，初值:0x11FF2018，宽度:32
 寄存器说明: DDRC_CFG_TIMING4是DDRC的时序参数寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tccdmw16  : 6;  /* bit[0-5]  : LPDDR4 BL16 MASK WRITE TCCD参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x3F： n个时钟周期。 */
        unsigned int  reserved_0: 2;  /* bit[6-7]  : 保留。 */
        unsigned int  tccdmw32  : 6;  /* bit[8-13] : LPDDR4 BL32 MASK WRITE TCCD参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x3F： n个时钟周期。 */
        unsigned int  reserved_1: 2;  /* bit[14-15]: 保留。 */
        unsigned int  twlo      : 4;  /* bit[16-19]: DDR3 WriteLevel状态延迟参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0xF：n个时钟周期。
                                                     该参数为twlo+twloe之和。 */
        unsigned int  tmod      : 5;  /* bit[20-24]: MRS命令到ODT和ZQCL有效的延时参数。
                                                     0x0~0x1:1个时钟周期；
                                                     02~0x1F:n个时钟周期。 */
        unsigned int  reserved_2: 3;  /* bit[25-27]: 保留。 */
        unsigned int  trodt_ext : 3;  /* bit[28-30]: LPDDR3模式，trodt_ext需与twodt配置相同。
                                                     对DDR4而言，用于在读数据时，使能其它rank的odt。由于在打开crc_en时，odt的打开会提前一拍，而对于读odt来说本身并没有因为crc的使能打开而自动扩展，故需要在该寄存器进行扩展。 */
        unsigned int  reserved_3: 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw16_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw16_END     (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw32_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw32_END     (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_twlo_START       (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_twlo_END         (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tmod_START       (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tmod_END         (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_trodt_ext_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_trodt_ext_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING5_UNION
 结构说明  : DDRC_CFG_TIMING5 寄存器结构定义。地址偏移量:0x114，初值:0x1113FF1F，宽度:32
 寄存器说明: DDRC_CFG_TIMING5是DDRC的时序参数寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  twr       : 5;  /* bit[0-4]  : 写恢复（write recovery）等待周期。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x1f：n个时钟周期。
                                                     注意：在有DFS的需求下，tWR参数需要按照DFS中芯片可能使用最高频率配置。并且不能随DDR的频率变化修改tWR的配置。 */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : 保留。 */
        unsigned int  tzqcs     : 8;  /* bit[8-15] : ZQCS校准延迟周期。
                                                     0x0～0xff：nx2个时钟周期。
                                                     由于dmc的设计，该值需要约束为大于等于10 */
        unsigned int  trnk2rnk  : 4;  /* bit[16-19]: RANK到RANK间的延时参数。
                                                     0000~1111:n个时钟周期。
                                                     注意：在DDR2/DDR3模式下，trtw参数主要考虑单板、封装、IO的延时；在LPDDR/LPDDR2/LPDDR3模式下，除了单板、封装、IO的延时，还需要加上tdqsckmax。 */
        unsigned int  tdqsck    : 3;  /* bit[20-22]: DQS相对于CK的输出访问时间，仅针对LPDDR2/3/4。该值用于计算Read latency，在LPDDR2/3/4模式下会自动叠加到RL上。 */
        unsigned int  reserved_1: 1;  /* bit[23]   : 保留。 */
        unsigned int  tdqsckmax : 3;  /* bit[24-26]: DQS相对于CK的最大输出访问时间，仅针对LPDDR2/3/4。该参数在LPDDR2/3模式下会自动叠加到所有读到其它命令的参数上。 */
        unsigned int  reserved_2: 1;  /* bit[27]   :  */
        unsigned int  twodt_ext : 3;  /* bit[28-30]: 仅对LPDDR3有效，在异步ODT下需要展宽ODT脚管的打开窗口。展宽的长度为(tODTon/off(max)-tODTon/off(min))/tCK。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x7：n个时钟周期。 */
        unsigned int  reserved_3: 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twr_START        (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twr_END          (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tzqcs_START      (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tzqcs_END        (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_START   (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_END     (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsck_START     (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsck_END       (22)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_END    (26)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twodt_ext_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twodt_ext_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING6_UNION
 结构说明  : DDRC_CFG_TIMING6 寄存器结构定义。地址偏移量:0x118，初值:0x000000FF，宽度:32
 寄存器说明: DDRC_CFG_TIMING6是DDRC的时序参数寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcksre   : 4;  /* bit[0-3]  : ddr3或ddr4的tCKSRE参数。在进入自刷新后时钟需要保持的拍数。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF： n个时钟周期。 */
        unsigned int  tcksrx   : 4;  /* bit[4-7]  : ddr3或ddr4的tCKSRX参数。在退出自刷新之前时钟需要提前的有效拍数。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF： n个时钟周期。 */
        unsigned int  todt_sft : 4;  /* bit[8-11] : LPDDR3模式ODT延时控制，主要用于补偿POP LPDDR3中ODT IO上DDRPHY的延时。
                                                    0x0~0xF: n个时钟周期。
                                                    ODT的延时=tWL-taond+todt_sft，注意ODT的最大延时不能超过0xF */
        unsigned int  tccd_l   : 4;  /* bit[12-15]: Bank Group之内的tccd等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。 */
        unsigned int  twtr_l   : 4;  /* bit[16-19]: Bank Group之内的twtr等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。 */
        unsigned int  trrd_l   : 4;  /* bit[20-23]: Bank Group之内的trrd等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。 */
        unsigned int  tccd_nsr : 4;  /* bit[24-27]: 在使用2T preamble或者2T postamble的情况下，两个非连续的读操作之间的最小间隔。
                                                    0x0~0x1:1个时钟周期；
                                                    0x2~0xf:n个时钟周期。 */
        unsigned int  tccd_nsw : 4;  /* bit[28-31]: 在使用2T preamble或者2T postamble的情况下，两个非连续的写操作之间的最小间隔。
                                                    0x0~0x1:1个时钟周期；
                                                    0x2~0xf:n个时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksre_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksre_END      (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksrx_START    (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksrx_END      (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_todt_sft_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_todt_sft_END    (11)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_l_START    (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_l_END      (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_twtr_l_START    (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_twtr_l_END      (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_trrd_l_START    (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_trrd_l_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsr_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsr_END    (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsw_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsw_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING7_UNION
 结构说明  : DDRC_CFG_TIMING7 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TIMING7是DDRC的时序参数寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnk_twtr  : 4;  /* bit[0-3]  : RANK间写到读的延时。 */
        unsigned int  rnk_trtw  : 4;  /* bit[4-7]  : RANK间读到写的延时。 */
        unsigned int  rnk_twtw  : 4;  /* bit[8-11] : RANK间写到写的延时。 */
        unsigned int  rnk_trtr  : 4;  /* bit[12-15]: RANK间读到读的延时。 */
        unsigned int  dimm_twtw : 4;  /* bit[16-19]: DIMM间写到写切换基于rnk_twtw额外增加的延时。用于匹配DIMM间的最大skew。 */
        unsigned int  dimm_trtr : 4;  /* bit[20-23]: DIMM间读到读切换基于rnk_trtr额外增加的延时。用于匹配DIMM间的最大skew。 */
        unsigned int  tckehcmd  : 4;  /* bit[24-27]: lpddr4在退出powerdown到退自刷新的时间参数。 */
        unsigned int  tescke    : 4;  /* bit[28-31]: lpddr4在进入自刷新后到进入powerdown的时间参数。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtr_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtr_END     (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtw_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtw_END     (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtw_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtw_END     (11)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtr_START   (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtr_END     (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_twtw_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_twtw_END    (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_trtr_START  (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_trtr_END    (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tckehcmd_START   (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tckehcmd_END     (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tescke_START     (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tescke_END       (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMING8_UNION
 结构说明  : DDRC_CFG_TIMING8 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TIMING8是DDRC的时序参数寄存器8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trp_ab   : 5;  /* bit[0-4]  : all bank的precharge命令的时间参数。 */
        unsigned int  tsr      : 5;  /* bit[5-9]  : LPDDR4的进入自刷新的最小时间的时间参数。 */
        unsigned int  trfc_pb  : 9;  /* bit[10-18]: per bank的自刷新周期时间参数。 */
        unsigned int  trfc_ab  : 9;  /* bit[19-27]: 自动刷新命令周期和自动刷新到激活（AREF period or AREF to ACT）命令的等待周期。该寄存器选择配置max{trfc,tzqcs}的大值。
                                                    0x00：保留；
                                                    0x01～0x1FF：n个时钟周期。 */
        unsigned int  reserved : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trp_ab_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trp_ab_END      (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_tsr_START       (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_tsr_END         (9)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_pb_START   (10)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_pb_END     (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_ab_START   (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_ab_END     (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_UNION
 结构说明  : DDRC_CFG_NXT_TIMING0 寄存器结构定义。地址偏移量:0x124，初值:0xFFFFFF3F，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING0是用于频率切换DDRC的时序参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tras     : 6;  /* bit[0-5]  : 同BANK的激活命令到到关闭命令（ACT to PRE）的等待周期。
                                                    0x00～0x01：1个时钟周期；
                                                    0x02～0x0F：n个时钟周期。 */
        unsigned int  reserved : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  trc      : 6;  /* bit[8-13] : 同BANK的激活命令到激活命令（active a bank to active a bank）的等待周期。
                                                    0x00～0x01：1个时钟周期；
                                                    0x02～0x3F：n个时钟周期。 */
        unsigned int  trcd     : 5;  /* bit[14-18]: 同BANK激活到读或写（ACT to READ or WRITE）命令的等待周期。
                                                    0x0～0x3：3时钟周期；
                                                    0x4～0xF：n时钟周期。 */
        unsigned int  trp_pb   : 5;  /* bit[19-23]: Per Bank关闭（PRE period）命令的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
        unsigned int  trrd     : 4;  /* bit[24-27]: 打开BANK A 到打开BANK B的（ACT bank a to ACT bank b）等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
        unsigned int  tmrd     : 4;  /* bit[28-31]: 模式寄存器加载（LMR）命令的等待周期(在DDR2，LPDDR2时候配置值为tMOD和tMRD的最大值，在DDR3时配置为tMRD）。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_END        (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_END         (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_START      (14)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_END        (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_pb_START    (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_pb_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_END        (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_START      (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_UNION
 结构说明  : DDRC_CFG_NXT_TIMING1 寄存器结构定义。地址偏移量:0x128，初值:0xFF200405，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING1是用于频率切换的DDRC的时序参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcl      : 6;  /* bit[0-5]  : DDR的读命令到读数据的延迟（CAS Latency）。
                                                    0x0～0x1： 1个时钟周期；
                                                    0x2～0xF： n个时钟周期。
                                                    如果是RDIMM模式CL应该配置为器件CL+1。 */
        unsigned int  reserved_0: 2;  /* bit[6-7]  : 保留。 */
        unsigned int  twl      : 6;  /* bit[8-13] : 写命令到写数据的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n个时钟周期。
                                                    如：0x3：3个时钟周期。
                                                    注意：DDR2模式，twl配置为tcl-1，twl配置时应满足twl –taond >＝1。
                                                    如果是RDIMM模式WL应配置为器件WL+1。
                                                    注意：在LPDDR2/LPDDR3模式下，由于协议定义的WL比实际的延时小1cycle，所以需要配置为模式寄存器的值+1。 */
        unsigned int  tmrri    : 5;  /* bit[14-18]: LPDDR4模式下，tXP结束后，到MRR需要额外等待的时间。 */
        unsigned int  reserved_1: 1;  /* bit[19]   : 保留。 */
        unsigned int  trtw     : 4;  /* bit[20-23]: 最后一个读数据到第一个写数据延迟。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF：n+1个时钟周期。
                                                    注意：在DDR2/DDR3模式下，trtw参数主要考虑单板、封装、IO的延时；在LPDDR/LPDDR2/LPDDR3模式下，除了单板、封装、IO的延时，还需要加上tdqsckmax。 */
        unsigned int  tsre     : 8;  /* bit[24-31]: 退出自刷新（Self-Refresh）到读命令的等待周期。
                                                    0x0： 保留；
                                                    0x01～0xFF：n×4个时钟周期。
                                                    DDR3 SDRAM时，该值配置tXSDLL和tXS的最大值。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_START       (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_END         (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_END         (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tmrri_START     (14)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tmrri_END       (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_START      (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_END        (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_UNION
 结构说明  : DDRC_CFG_NXT_TIMING2 寄存器结构定义。地址偏移量:0x12C，初值:0xF3FFF000，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING2是用于频率切换的DDRC的时序参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  taref    : 11; /* bit[0-10] : 自动刷新周期。
                                                    0x000：自动刷新禁止；
                                                    0x001～0x7FF：SDRAM刷新周期时间为16×n时钟周期。
                                                    如0x008：128个时钟周期（16×8）。
                                                    配置间隔时间为tREFI = 7800/16/tclk。Tclk为DMC域时钟的运行周期（注意，只有在clk ratio为1：1时，才与sdram的时钟周期相同）。 */
        unsigned int  reserved : 1;  /* bit[11]   : 保留。 */
        unsigned int  tfaw     : 6;  /* bit[12-17]: 连续4个激活命令周期。
                                                    0x00～0x3F：n个时钟周期；
                                                    如：0x14：20个时钟周期。 */
        unsigned int  trtrrd   : 6;  /* bit[18-23]: lpddr4协议中MPC读到普通读或是普通读到MPC读之间的时间参数。 */
        unsigned int  twtr     : 4;  /* bit[24-27]: 写操作最后一个写数据到读命令（write to read）的等待周期。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xf：n个时钟周期。
                                                    如0x3：3个时钟周期。 */
        unsigned int  tcke     : 4;  /* bit[28-31]: 低功耗状态维持的最短时间。
                                                    0x0：保留；
                                                    0x1～0xF：n个时钟周期。
                                                    该值需要配置tCKESR, tCKSRE, tCKSRX, tCKE，tCPDED几个值中的最大值。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_END       (10)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_START      (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_END        (17)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_trtrrd_START    (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_trtrrd_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_START      (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_END        (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_START      (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_UNION
 结构说明  : DDRC_CFG_NXT_TIMING3 寄存器结构定义。地址偏移量:0x130，初值:0xFFFFE0F2，宽度:32
 寄存器说明: DDRC_CFG_TIMING3是用于频率切换的DDRC的时序参数寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trtp    : 4;  /* bit[0-3]  : 读命令到关闭命令的等待延迟。
                                                   0000～0010：2个时钟周期；
                                                   0011～1111：n个时钟周期。
                                                   Trtp的计算公式是AL+BL/2+Max(trtp,2)-2 */
        unsigned int  txard   : 4;  /* bit[4-7]  : 退出DDR低功耗状态等待周期。
                                                   0x0～0xF：n x 2个时钟周期，n代表十进制数；
                                                   如：0x7：为14个时钟周期。
                                                   取{tXP,tXARD,tXARDS,tXS}中的最大值。
                                                   在DDR3模式下，该寄存器作为tXS配置时，txard只需要配置为10ns的等价时钟周期即可。 */
        unsigned int  taond   : 5;  /* bit[8-12] : ODT（On-die termination）打开和关闭周期。
                                                   DDR2模式下（taond/taofd）：
                                                   0x0：2/2.5；
                                                   0x1：3/3.5；
                                                   0x2：4/4.5；
                                                   0x3：5/5.5；
                                                   其它： 保留。
                                                   在DDR3模式下，该值配置为tWL-1。如果是1：2模式，则需要配成tWL-2。但是台研的phy已经单独处理，仍然采用tWL-1的配置。
                                                   在LPDDR3模式下，该值配置为tODTon(max)/tCK。 */
        unsigned int  tzqinit : 9;  /* bit[13-21]: ZQ初始化延迟周期。
                                                   0x0～0x1ff：nx4个时钟周期。
                                                   该值配置tZQINIT，tDLLK的最大值。 */
        unsigned int  tzq_prd : 10; /* bit[22-31]: ZQCS命令周期。
                                                   0x000：ZQCS命令禁止；
                                                   0x001～0x3FF： n×128个AREF周期。
                                                   ZQCS命令周期时间为n×128个taref时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_END       (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_START    (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_END      (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_START    (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_END      (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_START  (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_END    (21)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_START  (22)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_UNION
 结构说明  : DDRC_CFG_NXT_TIMING4 寄存器结构定义。地址偏移量:0x134，初值:0x11FF2018，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING4是用于频率切换的DDRC的时序参数寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tccdmw16  : 6;  /* bit[0-5]  : LPDDR4 BL16 MASK WRITE TCCD参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x3F： n个时钟周期。 */
        unsigned int  reserved_0: 2;  /* bit[6-7]  : 保留。 */
        unsigned int  tccdmw32  : 6;  /* bit[8-13] : LPDDR4 BL32 MASK WRITE TCCD参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x3F： n个时钟周期。 */
        unsigned int  reserved_1: 2;  /* bit[14-15]: 保留。 */
        unsigned int  twlo      : 4;  /* bit[16-19]: DDR3 WriteLevel状态延迟参数。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0xF：n个时钟周期。
                                                     该参数为twlo+twloe之和。 */
        unsigned int  tmod      : 5;  /* bit[20-24]: MRS命令到ODT有效的延时参数。
                                                     0x0~0x1:1个时钟周期；
                                                     02~0x1F:n个时钟周期。 */
        unsigned int  reserved_2: 3;  /* bit[25-27]: 保留。 */
        unsigned int  trodt_ext : 3;  /* bit[28-30]: LPDDR3模式，trodt_ext需与twodt配置相同。
                                                     对DDR4而言，用于在读数据时，使能其它rank的odt。由于在打开crc_en时，odt的打开会提前一拍，而对于读odt来说本身并没有因为crc的使能打开而自动扩展，故需要在该寄存器进行扩展。 */
        unsigned int  reserved_3: 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw16_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw16_END     (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw32_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw32_END     (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_START       (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_END         (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_START       (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_END         (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_trodt_ext_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_trodt_ext_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_UNION
 结构说明  : DDRC_CFG_NXT_TIMING5 寄存器结构定义。地址偏移量:0x138，初值:0x1113FF1F，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING5是用于频率切换的DDRC的时序参数寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  twr       : 5;  /* bit[0-4]  : 写恢复（write recovery）等待周期。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x1f：n个时钟周期。
                                                     注意：在有DFS的需求下，tWR参数需要按照DFS中芯片可能使用最高频率配置。并且不能随DDR的频率变化修改tWR的配置。 */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : 保留。 */
        unsigned int  tzqcs     : 8;  /* bit[8-15] : ZQCS校准延迟周期。
                                                     0x0～0xff：nx2个时钟周期。 */
        unsigned int  trnk2rnk  : 4;  /* bit[16-19]: RANK到RANK间的延时参数。
                                                     0000~1111:n个时钟周期。 */
        unsigned int  tdqsck    : 3;  /* bit[20-22]: DQS相对于CK的输出访问时间，仅针对LPDDR2/3。该值用于计算Read latency，在LPDDR2/3模式下会自动叠加到RL上。 */
        unsigned int  reserved_1: 1;  /* bit[23]   : 保留。 */
        unsigned int  tdqsckmax : 3;  /* bit[24-26]: DQS相对于CK的最大输出访问时间，仅针对LPDDR2/3。该参数在LPDDR2/3模式下会自动叠加到所有读到其它命令的参数上。 */
        unsigned int  reserved_2: 1;  /* bit[27]   :  */
        unsigned int  twodt_ext : 3;  /* bit[28-30]: 仅对LPDDR3有效，在异步ODT下需要展宽ODT脚管的打开窗口。展宽的长度为(tODTon/off(max)-tODTon/off(min))/tCK。
                                                     0x0～0x1：1个时钟周期；
                                                     0x2～0x7：n个时钟周期。 */
        unsigned int  reserved_3: 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_START        (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_END          (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_START      (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_END        (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_START   (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_END     (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_START     (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_END       (22)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_END    (26)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twodt_ext_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twodt_ext_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_UNION
 结构说明  : DDRC_CFG_NXT_TIMING6 寄存器结构定义。地址偏移量:0x13C，初值:0x000000FF，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING6是用于频率切换的DDRC的时序参数寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcksre   : 4;  /* bit[0-3]  : ddr3或ddr4的tCKSRE参数。在进入自刷新后时钟需要保持的拍数。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF： n个时钟周期。 */
        unsigned int  tcksrx   : 4;  /* bit[4-7]  : ddr3或ddr4的tCKSRX参数。在退出自刷新之前时钟需要提前有效拍数。
                                                    0x0～0x1：1个时钟周期；
                                                    0x2～0xF： n个时钟周期。 */
        unsigned int  todt_sft : 4;  /* bit[8-11] : LPDDR3模式ODT延时控制，主要用于补偿POP LPDDR3中ODT IO上DDRPHY的延时。
                                                    0x0~0xF: n个时钟周期。
                                                    ODT的延时=tWL-taond+todt_sft，注意ODT的最大延时不能超过0xF */
        unsigned int  tccd_l   : 4;  /* bit[12-15]: Bank Group之内的tccd等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。
                                                    注意：此参数配置为DDR时钟域的周期数。 */
        unsigned int  twtr_l   : 4;  /* bit[16-19]: Bank Group之内的twtr等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。 */
        unsigned int  trrd_l   : 4;  /* bit[20-23]: Bank Group之内的trrd等待周期。
                                                    0x0~0x1：1个时钟周期
                                                    0x2~0xf：n个时钟周期。 */
        unsigned int  tccd_nsr : 4;  /* bit[24-27]: 在使用2T preamble或者2T postamble的情况下，两个非连续的读操作之间的最小间隔。
                                                    0x0~0x1:1个时钟周期；
                                                    0x2~0xf:n个时钟周期。 */
        unsigned int  tccd_nsw : 4;  /* bit[28-31]: 在使用2T preamble或者2T postamble的情况下，两个非连续的写操作之间的最小间隔。
                                                    0x0~0x1:1个时钟周期；
                                                    0x2~0xf:n个时钟周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_END      (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_START    (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_END      (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_END    (11)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_l_START    (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_l_END      (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_twtr_l_START    (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_twtr_l_END      (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_trrd_l_START    (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_trrd_l_END      (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsr_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsr_END    (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsw_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsw_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_UNION
 结构说明  : DDRC_CFG_NXT_TIMING7 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING7是用于频率切换的DDRC的时序参数寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnk_twtr  : 4;  /* bit[0-3]  : RANK间写到读的延时。
                                                     在HDR模式下，使能CRC时，如果要用到RODT，rnk_twtr必须>=2。 */
        unsigned int  rnk_trtw  : 4;  /* bit[4-7]  : RANK间读到写的延时。 */
        unsigned int  rnk_twtw  : 4;  /* bit[8-11] : RANK间写到写的延时。 */
        unsigned int  rnk_trtr  : 4;  /* bit[12-15]: RANK间读到读的延时。 */
        unsigned int  dimm_twtw : 4;  /* bit[16-19]: DIMM间写到写切换基于rnk_twtw额外增加的延时。用于匹配DIMM间的最大skew。 */
        unsigned int  dimm_trtr : 4;  /* bit[20-23]: DIMM间读到读切换基于rnk_trtr额外增加的延时。用于匹配DIMM间的最大skew。 */
        unsigned int  reserved  : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtr_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtr_END     (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtw_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtw_END     (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtw_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtw_END     (11)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtr_START   (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtr_END     (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_twtw_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_twtw_END    (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_trtr_START  (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_trtr_END    (23)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_UNION
 结构说明  : DDRC_CFG_NXT_TIMING8 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_NXT_TIMING8是DDRC的时序参数寄存器8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trp_ab   : 5;  /* bit[0-4]  : all bank的precharge命令的时间参数。 */
        unsigned int  tsr      : 5;  /* bit[5-9]  : LPDDR4的进入自刷新的最小时间的时间参数。 */
        unsigned int  trfc_pb  : 9;  /* bit[10-18]: per bank的自刷新周期时间参数。 */
        unsigned int  trfc_ab  : 9;  /* bit[19-27]: 自动刷新命令周期和自动刷新到激活（AREF period or AREF to ACT）命令的等待周期。该寄存器选择配置max{trfc,tzqcs}的大值。
                                                    0x00：保留；
                                                    0x01～0x1FF：n个时钟周期。 */
        unsigned int  reserved : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trp_ab_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trp_ab_END      (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_tsr_START       (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_tsr_END         (9)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_pb_START   (10)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_pb_END     (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_ab_START   (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_ab_END     (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_BLDATA_UNION
 结构说明  : DDRC_CFG_BLDATA 寄存器结构定义。地址偏移量:0x148，初值:0x00000002，宽度:32
 寄存器说明: DDRC_CFG_BLDATA是DDRC写数据预接收写数据配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bl_data  : 4;  /* bit[0-3] : 当前模式下，每个DDR命令对应的DMC数据拍数。
                                                   0x0~0xF：n拍。 */
        unsigned int  reserved : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_BLDATA_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_bl_data_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_bl_data_END     (3)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DMCLVL_UNION
 结构说明  : DDRC_CFG_DMCLVL 寄存器结构定义。地址偏移量:0x14C，初值:0x00000108，宽度:32
 寄存器说明: DDRC_CFG_DMCLVL是DDR控制器命令队列深度水线配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  que_level       : 5;  /* bit[0-4]  : DMC中，命令寄存器FIFO的深度。
                                                           0x1～0x10： n个命令深度。
                                                           其它保留。
                                                           
                                                           注意：默认值为dmc que有配置深度。即该默认值会随着具体项目的配置不同而不同。 */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  mbist_que_level : 5;  /* bit[8-12] : MTEST功能时，DMC启动的命令BUFFER个数。
                                                           0x0：1个。
                                                           0x1~0x10:1~16个，最大值跟代码配置有关。
                                                           
                                                           注意：该配置保对Mbist起作用，不对Mclr起作用。因为在Mclr时，会尽可能多的使用queue，以提供效率。 */
        unsigned int  reserved_1      : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DMCLVL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_que_level_START        (0)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_que_level_END          (4)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_END    (12)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_UNION
 结构说明  : DDRC_CFG_TIMEOUT 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TIMEOUT是命令TIMEOUT配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_en    : 1;  /* bit[0]    : DDRC timeout使能配置。
                                                         1：使能；
                                                         0：禁止。 */
        unsigned int  reserved_0    : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  timeout_level : 4;  /* bit[4-7]  : DDRC timeout 水线配置。
                                                         命令的优先级大于等于timeout_level的采用timeout0的值；小于timeout_level的采用timeout1的配置值。 */
        unsigned int  timeout0      : 10; /* bit[8-17] : 命令timeout0配置。
                                                         0x1～0x3FF：n个时钟周期；
                                                         其它：保留。 */
        unsigned int  reserved_1    : 2;  /* bit[18-19]: 保留。 */
        unsigned int  timeout1      : 10; /* bit[20-29]: 命令timeout1配置。
                                                         0x1～0x3FF：n个时钟周期；
                                                         其它：保留。 */
        unsigned int  reserved_2    : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_END       (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_START       (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_END         (17)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_START       (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_END         (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_QOS_UNION
 结构说明  : DDRC_CFG_QOS 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_QOS是命令QOS配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ageprd   : 4;  /* bit[0-3] : 命令老化时间配置。
                                                   0x1～0xF：N×16个时钟周期；
                                                   0x0：禁止Aging功能。 */
        unsigned int  priadpt  : 4;  /* bit[4-7] : 命令优先级自适应配置。
                                                   0x1～0xF：N×16个时钟周期；
                                                   0x0：禁止优先级自适应功能。 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_QOS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ageprd_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ageprd_END      (3)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_priadpt_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_priadpt_END     (7)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_UNION
 结构说明  : DDRC_CFG_EXMBIST_CMD 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EXMBIST_CMD是EXMBIST模块的命令配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exmbist_cmd : 32; /* bit[0-31]: EXMBIST模块的命令配置寄存器。具体格式请见EMBIST模块的寄存器说明。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_exmbist_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_exmbist_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_UNION
 结构说明  : DDRC_CFG_EXMBIST_DAT 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_EXMBIST_DAT模块的数据DIN数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exmbist_din : 32; /* bit[0-31]: EXMBIST模块的数据配置寄存器。具体格式请见EMBIST模块的寄存器说明。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_exmbist_din_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_exmbist_din_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MBIST_UNION
 结构说明  : DDRC_CFG_MBIST 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MBIST是MBIST的最高地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mbist_top_addr : 28; /* bit[0-27] : MTEST或者MCLR进行扫描的RANK最高地址。其配置与DMC的位宽及HDR和SDR模式有关。
                                                          
                                                          如果DMC宏定义成HDR模式，则地址空间为：
                                                          DMC位宽256: N*64;
                                                          DMC位宽128: N*32;
                                                          DMC位宽128: N*16;
                                                          
                                                          如果DMC宏定义为SDR模式，则地址空间为：
                                                          DMC位宽256: N*128;
                                                          DMC位宽128: N*64;
                                                          DMC位宽128: N*32;
                                                          
                                                          以Balongv8r1为例，DMC=128bit，宏定义配置成了HDR模式，则其配置如下。
                                                          0x2：64Byte地址空间；
                                                          …
                                                          0xN：N*32Byte地址空间。
                                                          注意在进行MTEST时候，最高地址必须为2的n次方。另外，由于算法的限制，N必须从2开始。 */
        unsigned int  mbist_rank     : 4;  /* bit[28-31]: MTEST或者MCLR进行扫瞄的RANK选择。
                                                          0：RANK0；
                                                          1：RANK1；
                                                          2：RANK2；
                                                          3：RANK3。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MBIST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_END    (27)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_rank_START      (28)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_rank_END        (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_UNION
 结构说明  : DDRC_CFG_MCLR_PATTERN0 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_pattern0 : 32; /* bit[0-31]: Memory Clean数据样式的0bit~31bit
                                                        注意：用于RASC时，必须为0 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_UNION
 结构说明  : DDRC_CFG_MCLR_PATTERN1 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_pattern1 : 32; /* bit[0-31]: Memory Clean数据样式的32bit~63bit
                                                        注意：用于RASC时，必须为0 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_UNION
 结构说明  : DDRC_CFG_MCLR_PATTERN2 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_pattern2 : 32; /* bit[0-31]: Memory Clean数据样式的64bit~95bit
                                                        注意：用于RASC时，必须为0 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_UNION
 结构说明  : DDRC_CFG_MCLR_PATTERN3 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_pattern3 : 32; /* bit[0-31]: Memory Clean数据样式的96bit~127bit
                                                        注意：用于RASC时，必须为0 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_UNION
 结构说明  : DDRC_CFG_MCLR_PATTERN4 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_MCLR_PATTEN0是Memory格式化的数据样式寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclr_pattern4 : 32; /* bit[0-31]: Memory Clean数据样式的128bit~144bit
                                                        注意：用于RASC时，必须为0xFF1144CC
                                                        当用于ECC时，高16位应该等于低16位 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_UNION
 结构说明  : DDRC_CFG_OSC_PRD 寄存器结构定义。地址偏移量:0x178，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_OSC_PRD是Oscillator的读取间隔配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  osc_prd  : 28; /* bit[0-27] : Oscillator的读取间隔配置寄存器。其间隔为n*16，即每配置1代表16个cycle。当该寄存器配置为0时，表示Oscillator的读取功能关闭。
                                                    
                                                    注意：由于该寄存器为非0其实是使能Oscillator读取功能，故在配置该寄存器之前需要先配置osc_threshold/osc_run_time寄存器。 */
        unsigned int  reserved : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_osc_prd_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_osc_prd_END     (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_UNION
 结构说明  : DDRC_CFG_OSC_CFG 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_OSC_CFG是Oacillator的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  osc_run_time  : 16; /* bit[0-15] : Oscillator在OSCstart后到停止的时间间隔。要配置值要根据MR23的配置值来确定。同时需要加上tOSCO参数。 */
        unsigned int  osc_threshold : 16; /* bit[16-31]: Oscillator的阀值。即将读回的Oscillator的值与Base count的值进行比较，如果超出该寄存器设定的范围，则上报中断，同时通知Pack进行retraining. */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_run_time_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_run_time_END     (15)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_threshold_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_threshold_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TRAIN_UNION
 结构说明  : DDRC_CFG_TRAIN 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TRAIN是训练
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  train_en : 1;  /* bit[0]   : DDRC训练使能。
                                                   1：训练使能；
                                                   0：训练禁止。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TRAIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_train_en_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_train_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_UNION
 结构说明  : DDRC_CFG_DFI_LAT0 寄存器结构定义。地址偏移量:0x184，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DFI_LAT0是dfi接口时序配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyif_tim_oven : 7;  /* bit[0-6]  : dfi接口时序接口over ride模式。
                                                          0：表示采用每个phy默认的时序；
                                                          1：采用over ride模式。
                                                          其中每bit对应的时序参数如下：
                                                          [0] -> phyif_tim_wodt
                                                          [1] -> phyif_tim_rodt
                                                          [2] -> phyif_tim_wden
                                                          [3] -> phyif_tim_wdcs
                                                          [4] -> phyif_tim_wdda
                                                          [5] -> phyif_tim_rden
                                                          [6] -> phyif_tim_rdcs */
        unsigned int  reserved       : 1;  /* bit[7]    : 保留。 */
        unsigned int  phyif_tim_wodt : 8;  /* bit[8-15] : wodt延时的拍数
                                                          注意：当前只有[12:8]位有效。 */
        unsigned int  phyif_tim_rodt : 8;  /* bit[16-23]: rodt延时的拍数
                                                          注意：当前只有[20:16]位有效。 */
        unsigned int  phyif_tim_wden : 8;  /* bit[24-31]: dfi_wdata_en延时的拍数
                                                          
                                                          注意：当前只有[28:24]位有效。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_oven_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_oven_END    (6)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wodt_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wodt_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_rodt_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_rodt_END    (23)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wden_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wden_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_UNION
 结构说明  : DDRC_CFG_DFI_LAT1 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DFI_LAT1是dfi接口时序配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyif_tim_wdcs : 8;  /* bit[0-7]  : dfi_wrdata_cs_n延时的拍数
                                                          注意：当前只有[4:0]位有效。 */
        unsigned int  phyif_tim_wdda : 8;  /* bit[8-15] : dfi_wrdata延时的拍数
                                                          注意：当前只有[12:8]位有效。 */
        unsigned int  phyif_tim_rden : 8;  /* bit[16-23]: dfi_rddata_en延时的拍数
                                                          注意：当前只有[21:16]位有效。 */
        unsigned int  phyif_tim_rdcs : 8;  /* bit[24-31]: dfi_rddata_cs_n延时的拍数
                                                          注意：当前只有[29:24]位有效。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdcs_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdcs_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdda_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdda_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rden_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rden_END    (23)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rdcs_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rdcs_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_REC0_UNION
 结构说明  : DDRC_CFG_REC0 寄存器结构定义。地址偏移量:0x190，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_REC0是DDR4错误恢复配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rec_en      : 1;  /* bit[0]    : Error recovery是否使能
                                                       0：禁止；
                                                       1：使能。 */
        unsigned int  rec_ref_en  : 1;  /* bit[1]    : 错误恢复前是否发送auto refresh命令
                                                       0：禁止；
                                                       1：使能。 */
        unsigned int  rec_upd_en  : 1;  /* bit[2]    : REC模块是否发送upd握手信号
                                                       0：禁止；
                                                       1：使能。 */
        unsigned int  reserved_0  : 1;  /* bit[3]    : 保留。 */
        unsigned int  rec_ref_num : 4;  /* bit[4-7]  : 错误恢复前发送auto refresh的次数
                                                       0~15：n+1 */
        unsigned int  rec_max_num : 4;  /* bit[8-11] : 在一次纠错过程中允许最大错误次数，超过错误次数后，rec将停止发送错误恢复命令，上报错误中断 */
        unsigned int  crc_liminal : 6;  /* bit[12-17]: CRC错误Alert_n拉低周期数阈值，在同时使能CRC错误和CA Parity错误时Alert_n拉低周期数大于阈值则判定为CA Parity错误，小于该阈值则判定为CRC 错误 */
        unsigned int  reserved_1  : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_REC0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_en_START       (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_en_END         (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_en_START   (1)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_en_END     (1)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_upd_en_START   (2)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_upd_en_END     (2)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_num_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_num_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_max_num_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_max_num_END    (11)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_crc_liminal_START  (12)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_crc_liminal_END    (17)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_REC1_UNION
 结构说明  : DDRC_CFG_REC1 寄存器结构定义。地址偏移量:0x194，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_REC1是DDR4错误恢复配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  talert_syn  : 4;  /* bit[0-3]  : Alert_n信号同步逻辑延迟时间 */
        unsigned int  tio2phy_dly : 5;  /* bit[4-8]  : 读数据从IO到phy dfi接口最大延迟时间 */
        unsigned int  reserved_0  : 3;  /* bit[9-11] : 保留。 */
        unsigned int  tpar_alert  : 5;  /* bit[12-16]: CA Parity错误到Alert_n拉低时间，包含器件手册中tPAR_UNKNOWN和tPAR_ALERT_ON参数 */
        unsigned int  reserved_1  : 3;  /* bit[17-19]: 保留。 */
        unsigned int  tcrc_alert  : 5;  /* bit[20-24]: CRC错误到Alert_n拉低时间，包含器件手册中tCRC_ALERT参数 */
        unsigned int  tphy2io_dly : 5;  /* bit[25-29]: 命令从phy模块到IO最大延迟时间 */
        unsigned int  reserved_2  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_REC1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_REC1_talert_syn_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_talert_syn_END     (3)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tio2phy_dly_START  (4)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tio2phy_dly_END    (8)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tpar_alert_START   (12)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tpar_alert_END     (16)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tcrc_alert_START   (20)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tcrc_alert_END     (24)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tphy2io_dly_START  (25)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tphy2io_dly_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CRC_UNION
 结构说明  : DDRC_CFG_CRC 寄存器结构定义。地址偏移量:0x198，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CRC是DDR4 CRC配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  device_x8_x4    : 18; /* bit[0-17] : 当前Bytelane的器件类型，每个Bytelane可以单独配置
                                                           0： X8或X16器件
                                                           1： X4器件 */
        unsigned int  reserved_0      : 2;  /* bit[18-19]: 保留。 */
        unsigned int  crc_pipe_bypass : 1;  /* bit[20]   : CRC PIPELINE bypass使能，在DDR3场景且CWL<8时，建议配置为1，DDR4场景需要配置为0 */
        unsigned int  reserved_1      : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_device_x8_x4_START     (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_device_x8_x4_END       (17)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_crc_pipe_bypass_START  (20)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_crc_pipe_bypass_END    (20)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_UNION
 结构说明  : DDRC_CFG_CRC_ERRINJ0 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CRC_ERRINJ0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_err_inj     : 1;  /* bit[0]    : CRC错误注入模式：
                                                           0：正常功能模式；
                                                           1：注错模式，写1触发一次注错脉冲，一个注错脉冲可以触发多个错误注入 */
        unsigned int  crc_inject_mask : 1;  /* bit[1]    : 是否过滤rec_mode下的写数据注错功能
                                                           0： 不过滤rec_mode下写数据注错
                                                           1： 过滤rec_mode下写数据注错 */
        unsigned int  reserved_0      : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  crc_inject_dm   : 1;  /* bit[4]    : 错误注入到DM中 */
        unsigned int  reserved_1      : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  crc_inject_pat  : 8;  /* bit[8-15] : 注入错误pattern，可以同时注入多bit错误，当为X4器件时，高4bit和低4bit分别注入到高低X4 */
        unsigned int  crc_inject_num  : 5;  /* bit[16-20]: 注入错误个数
                                                           1：2个错误
                                                           2：3个错误
                                                           ...
                                                           N：N+1个错误
                                                           （0，31: 保留） */
        unsigned int  reserved_2      : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_err_inj_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_err_inj_END        (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_mask_START  (1)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_mask_END    (1)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_dm_START    (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_dm_END      (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_pat_START   (8)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_pat_END     (15)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_num_START   (16)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_num_END     (20)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_UNION
 结构说明  : DDRC_CFG_CRC_ERRINJ1 寄存器结构定义。地址偏移量:0x1A4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CRC_ERRINJ1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_inject_burst : 4;  /* bit[0-3]  : 错误注入到Burst中的位置
                                                            0-7： Burst的第1到7个字节
                                                            8： Burst中CRC校验码位置
                                                            9-15：保留。 */
        unsigned int  crc_inject_bl    : 18; /* bit[4-21] : 错误注入的Bytelane，可以多个Bytelane同时注错 */
        unsigned int  reserved         : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_burst_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_burst_END    (3)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_bl_START     (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_bl_END       (21)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_UNION
 结构说明  : DDRC_CFG_PAR_ERRINJ0 寄存器结构定义。地址偏移量:0x1A8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_PAR_ERRINJ0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  par_err_inj     : 1;  /* bit[0]    : PAR错误注入模式：
                                                           0：正常功能模式；
                                                           1：注错模式，写1触发一次注错脉冲，一个脉冲可以触发多个错误注入 */
        unsigned int  par_inject_mask : 1;  /* bit[1]    : 是否过滤rec_mode下的注错功能
                                                           0： 不过滤rec_mode下的据注错
                                                           1： 过滤rec_mode下的注错 */
        unsigned int  reserved_0      : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  par_inject_num  : 5;  /* bit[4-8]  : 连续注入错误个数
                                                           0-31: N次 */
        unsigned int  reserved_1      : 3;  /* bit[9-11] : 保留。 */
        unsigned int  par_inject_cmd  : 8;  /* bit[12-19]: 对哪些类型的命令注错
                                                           bit[19] 0: 不使能对ZQ命令注错， 1：使能对ZQ命令注错
                                                           bit[18] 0: 不使能对Read命令注错， 1：使能对Read命令注错
                                                           bit[17] 0: 不使能对Write命令注错， 1：使能对Write命令注错
                                                           bit[16] 0: 不使能对ACT命令注错， 1：使能对ACT命令注错
                                                           bit[15] 0: 不使能对PRE/PREA命令注错， 1：使能对PRE/PREA命令注错
                                                           bit[14] 0: 不使能对SRE命令注错， 1：使能对SRE命令注错
                                                           bit[13] 0: 不使能对AREF命令注错， 1：使能对AREF命令注错
                                                           bit[12] 0：不使能对MRS命令注错， 1：使能对MRS命令注错 */
        unsigned int  reserved_2      : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_err_inj_START      (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_err_inj_END        (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_mask_START  (1)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_mask_END    (1)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_num_START   (4)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_num_END     (8)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_cmd_START   (12)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_cmd_END     (19)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_UNION
 结构说明  : DDRC_CFG_PAR_ERRINJ1 寄存器结构定义。地址偏移量:0x1AC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_PAR_ERRINJ1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  par_inject_pos : 6;  /* bit[0-5] : 错误注入位置
                                                         0： 错误注入到parity
                                                         1: 错误注入到act_n
                                                         2: 错误注入到ras_n
                                                         3: 错误注入到cas_n
                                                         4: 错误注入到we_n
                                                         8:5 注入到Bank （根据bank定义位宽调整）
                                                         10:9 注入到Bank group (根据Bank， Bank Group定义位宽调整）
                                                         28:11 注入到addr（根据Bank, Bank Group, Addr定义位宽调整） */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_par_inject_pos_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_par_inject_pos_END    (5)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DDRPHY_UNION
 结构说明  : DDRC_CFG_DDRPHY 寄存器结构定义。地址偏移量:0x200，初值:0x103F1000，宽度:32
 寄存器说明: DDRC_CFG_DDRIO是DDR IO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rcv_pdr           : 1;  /* bit[0]    : DDR接收IO动态Power Down控制使能。使能时DDRC会在非读状态关断DDR数据IO的接收Buffer。
                                                             1：使能；
                                                             0：禁止。
                                                             需要和trdlat配合使用 */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  phy_zqen          : 1;  /* bit[4]    : 控制器发起DDRPHY dfi_ctrlupd_req。
                                                             0：禁止；
                                                             1：使能。 */
        unsigned int  reserved_1        : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  trdlat            : 4;  /* bit[8-11] : DDRPHY固有延迟。
                                                             0x0～0xF：n+1个周期。
                                                             使用synopsys3/2phy时需要配置为8。 */
        unsigned int  phy_upden         : 1;  /* bit[12]   : 控制器响应DDRPHY发起dfi_phyupd_en。
                                                             0：禁止；
                                                             1：使能。 */
        unsigned int  reserved_2        : 3;  /* bit[13-15]: 保留。 */
        unsigned int  wr_busy_dly       : 6;  /* bit[16-21]: PHY内部用作数据打拍的门控信号。
                                                             必须配置大于WL+2。
                                                             对功耗不敏感的场景，可配置为0x1F。 */
        unsigned int  reserved_3        : 2;  /* bit[22-23]: 保留。 */
        unsigned int  phyupd_n_pre      : 1;  /* bit[24]   : phy update的no precharge功能使能。
                                                             0：关闭no precharge功能，即所有type的update在返回dfi_phyupd_ack前都需要发送precharge all命令。
                                                             1：打开no precharge功能。即当phy的update type与指定的phy_n_pre_type相同，则不发送precharge all命令，否则发送precharge all功能。 */
        unsigned int  reserved_4        : 3;  /* bit[25-27]: 保留。 */
        unsigned int  phyupd_n_pre_type : 2;  /* bit[28-29]: no precharge指定的type类型。即当phyupd_n_pre有效时，当该值与phy发送过来的dfi_phyupd_type相等，则不发送precharge。 */
        unsigned int  reserved_5        : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DDRPHY_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_START            (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_END              (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_START           (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_END             (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_trdlat_START             (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_trdlat_END               (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_START          (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_END            (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_wr_busy_dly_START        (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_wr_busy_dly_END          (21)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_START       (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_END         (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_type_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_type_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_AGING_UNION
 结构说明  : DDRC_CFG_AGING 寄存器结构定义。地址偏移量:0x204，初值:0x00000400，宽度:32
 寄存器说明: DDRC_CFG_AGING是PHY的防老化配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  age_ent_prd : 8;  /* bit[0-7]  : 防老化模式进入周期配置。即dmc idle的计数拍数，计数周期到达后通知phy进入防老化模式。
                                                       0x0～0x1：1K个时钟周期；
                                                       0x1～0xFF：1K*n个时钟周期。 */
        unsigned int  age_ext_prd : 8;  /* bit[8-15] : 退出防老化模式后计数的周期数，计数到达后才允许dmc有读写访问。 */
        unsigned int  age_en      : 1;  /* bit[16]   : 防老化功能使用控制。
                                                       0：关闭防老化功能；
                                                       1：打开防老化功能。 */
        unsigned int  reserved    : 15; /* bit[17-31]:  */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_AGING_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ent_prd_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ent_prd_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ext_prd_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ext_prd_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_en_START       (16)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_en_END         (16)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_UNION
 结构说明  : DDRC_CFG_SFC_MASK 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFCMASK是DDRC软件配置DDR命令MPC MASK寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sfc_mask : 32; /* bit[0-31]: 针对lpddr4的mpc命令所对应的mask配置。
                                                   
                                                   注意：该寄存器对应每拍DMC数据的每个byte。比如128bit的DMC，该寄存器为16bit。如256bit的DMC，则为32bit. */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_sfc_mask_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_sfc_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_UNION
 结构说明  : DDRC_CFG_SFC_TIM 寄存器结构定义。地址偏移量:0x20C，初值:0x0000003F，宽度:32
 寄存器说明: DDRC_CFG_SFC_TIM是DDRC软件配置DDR命令的时序寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wait_time   : 6;  /* bit[0-5]  : 在执行完DDR的读命令以后，等待的时间。
                                                       
                                                       注意：这个wait的时间是对所有读命令都会有效，如果PHY超出这个时间没有回数据，则DMC会上报rdtimeout_rint的中断。该配置值不会受wait_en的开关影响。 */
        unsigned int  reserved    : 10; /* bit[6-15] : 保留。 */
        unsigned int  wait_tlast  : 8;  /* bit[16-23]: SFC的备选时序参数。比如最后一个命令发完后，不确定DMC主通路会发送什么命令，就可以通过加载该参数，按所有最大的可能计算。 */
        unsigned int  wait_reserv : 8;  /* bit[24-31]: SFC的备选时间参数。可能存在一些未考虑到的时间参数，可能通过加载该时间参数。该时间参数为N*256，即最小粒度为256个周期。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_time_START    (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_time_END      (5)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_tlast_START   (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_tlast_END     (23)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_reserv_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_reserv_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_UNION
 结构说明  : DDRC_CFG_SFC 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CTRL_SFC是DDRC软件配置DDR命令属性命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sfc_que_rptr  : 8;  /* bit[0-7]  : SFC CMD Que的读指针。每从DDRC_CFG_SFC_ADDR0中读取一个数据，则读指针会自动加1。也可以通过软件改写该读指针，用于读取指定的queue的位置。
                                                         
                                                         注意：该指针的位宽由queue的深度决定，比如queue的深度为16时，该寄存器域的有效位宽为4bit. */
        unsigned int  infinite_loop : 1;  /* bit[8]    : 无限循环配置位。
                                                         1：sfc cmd queue中的命令会被重复执行。
                                                         0：sfc cmd queue中的命令只会执行一次。
                                                         
                                                         注意：开始infinite_loop的流程只需要把infinite_loop置1，然后再将cmd_req置1。停止infinite_loop的流程应该是先将infinite_loop清0，然后查询cmd_req变为0. */
        unsigned int  sfc_que_clr   : 1;  /* bit[9]    : sfc queue清除控制。
                                                         1：将sfc cmd queue中的写指针清零；
                                                         0：写指针根据写入的命令自动递增。 */
        unsigned int  sfc_msk_ctrl  : 1;  /* bit[10]   : SFC模块的DMI信息控制位。
                                                         1：表示DMI使用sfc_mask的配置值；
                                                         0：表示sfc模块根据数据拍数自动产生mask. */
        unsigned int  reserved_0    : 1;  /* bit[11]   : 保留。 */
        unsigned int  cmd_mrs       : 4;  /* bit[12-15]: 在RDMRS或者RD操作时，用来控制需要返回的数据拍数。
                                                         0：表示DMC位宽的第0拍数据；
                                                         1：表示DMC位宽的第1拍数据；
                                                         2~15：以此类推。 */
        unsigned int  reserved_1    : 15; /* bit[16-30]: 保留。 */
        unsigned int  wait_en       : 1;  /* bit[31]   : 当读数据在wait_time指定的时间没有返回，选择是否返回假数据。
                                                         1：timeout后返回假数据；
                                                         0：timeout不作任何处理。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_rptr_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_rptr_END     (7)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_infinite_loop_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_infinite_loop_END    (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_clr_START    (9)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_clr_END      (9)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_msk_ctrl_START   (10)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_msk_ctrl_END     (10)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_cmd_mrs_START        (12)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_cmd_mrs_END          (15)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_wait_en_START        (31)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_wait_en_END          (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_UNION
 结构说明  : DDRC_CFG_SFC_ADDR0 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_ADDR0是SFC命令Que的配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sfc_cmd_que : 32; /* bit[0-31]: SFC模块CMD Que的入口寄存器。该寄器存器是SFC CMD Que的入口，只要写该地址写入命令，内部写指针会自动递增。如果有多个命令，则往该寄存器多次写入。命令的格式请见详细设计。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_cmd_que_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_cmd_que_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_UNION
 结构说明  : DDRC_CFG_SFC_ADDR1 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_ADDR1是SFC读写memory地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 16; /* bit[0-15] : 保留。 */
        unsigned int  sfc_rank : 16; /* bit[16-31]: 执行命令的DDR RANK。
                                                    0：不执行配置命令；
                                                    1：执行配置命令。
                                                    注意：每比特对应一个RANK的控制。例如，cmd_rank[0]控制DDR RANK0
                                                    
                                                    对于DDR4来说，由于需要根据sfc_rank选择bank group的，所以如果每个rank的bank group不一样，则不能同时对多个rank发送写模式寄存器或写数据。而只能对一个rank操作。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_rank_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_rank_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_UNION
 结构说明  : DDRC_CFG_SFC_WDATA0 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA0是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata0 : 32; /* bit[0-31]: SFC写数据[31:0]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_UNION
 结构说明  : DDRC_CFG_SFC_WDATA1 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA1是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata1 : 32; /* bit[0-31]: SFC写数据[63:32]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_UNION
 结构说明  : DDRC_CFG_SFC_WDATA2 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA2是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata2 : 32; /* bit[0-31]: SFC写数据[95:64]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_UNION
 结构说明  : DDRC_CFG_SFC_WDATA3 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA3是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata3 : 32; /* bit[0-31]: SFC写数据[127:96]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_UNION
 结构说明  : DDRC_CFG_SFC_WDATA4 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA4是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata4 : 32; /* bit[0-31]: SFC写数据[159:128]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_UNION
 结构说明  : DDRC_CFG_SFC_WDATA5 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA5是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata5 : 32; /* bit[0-31]: SFC写数据[191:160]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_UNION
 结构说明  : DDRC_CFG_SFC_WDATA6 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA6是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata6 : 32; /* bit[0-31]: SFC写数据[223:192]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_UNION
 结构说明  : DDRC_CFG_SFC_WDATA7 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA7是SFC写数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata7 : 32; /* bit[0-31]: SFC写数据[255:224]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_UNION
 结构说明  : DDRC_CFG_SFC_WDATA_ECC 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_SFC_WDATA_ECC是SFC写ECC数据配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdata_ecc0 : 8;  /* bit[0-7]  : SFC写数据[63:0]的8bit ECC数据。 */
        unsigned int  wdata_ecc1 : 8;  /* bit[8-15] : SFC写数据[127:64]的8bit ECC数据。 */
        unsigned int  wdata_ecc2 : 8;  /* bit[16-23]: SFC写数据[191:128]的8bit ECC数据。 */
        unsigned int  wdata_ecc3 : 8;  /* bit[24-31]: SFC写数据[255:192]的8bit ECC数据。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_END    (7)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_START  (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_END    (15)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_START  (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_END    (23)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TMON_UNION
 结构说明  : DDRC_CFG_TMON 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tmon_prd : 32; /* bit[0-31]: 读取器件温度的周期。
                                                   0x0：禁止循环读取器件温度；
                                                   0x1~0xffffffff：以n x 1024cycle为周期读取器件温度，每次读取一个RANK。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_tmon_prd_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_tmon_prd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_UNION
 结构说明  : DDRC_CFG_TMON_RANK 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测RANK配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tmon_rank : 16; /* bit[0-15] : 读取对应RANK的温度。
                                                     每个bit对应一个RANK。 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_tmon_rank_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_tmon_rank_END    (15)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_UNION
 结构说明  : DDRC_CFG_TMON_AREF 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_TMON是LPDDR2/LPDDR3器件温度检测刷新配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aref_rate : 32; /* bit[0-31]: 每个RANK对应的AREF周期。
                                                    00：1xtREFI
                                                    01：2xtREFI
                                                    10：4xtREFI
                                                    11：保留
                                                    每2bit对应一个RANK。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_aref_rate_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_aref_rate_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_UNION
 结构说明  : DDRC_CFG_MRR_MAP 寄存器结构定义。地址偏移量:0x250，初值:0x00FAC688，宽度:32
 寄存器说明: DDRC_CFG_MRR_MAP是单板连接重映射配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrr_map  : 24; /* bit[0-23] : 模式寄存器BYTE0对应器件的bit位置。
                                                    Bit[2:0]对应PHY DQ[0]。
                                                    000：PHY连接的DQ[0]对应DDR DQ[0]
                                                    001：PHY连接的DQ[0]对应DDR DQ[1]
                                                    …
                                                    111：PHY连接的DQ[0]对应DDR DQ[7]
                                                    Bit[5:3]对应PHY DQ[1]。
                                                    …
                                                    Bit[23:21]对应PHY DQ[7]。 */
        unsigned int  mrr_byte : 5;  /* bit[24-28]: 模式寄存器BYTE0对应器件的byte位置。
                                                    默认BYTE0是对应物理器件的BYTE0，当单板连接在BYTE间调序时，需要重新映射。 */
        unsigned int  reserved : 3;  /* bit[29-31]:  */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_map_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_map_END     (23)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_byte_START  (24)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_byte_END    (28)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_STADAT_UNION
 结构说明  : DDRC_CFG_STADAT 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_STADAT是DDRC数据统计使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dat_stat_prd  : 28; /* bit[0-27] : 数据统计周期。
                                                         0x0~0x1：无效配置。
                                                         0x2～0xFFFFFFF：统计周期。
                                                         实际统计周期为load_stat_prd*16*tclk（Tclk为DDRC总线时钟周期）。
                                                         注意：此配置只在load_stat_mode=2'b01或2'b10时有效。当load_stat_mode=0的连续统计模式下，性能统计相关计数器会一直计数。 */
        unsigned int  dat_stat_mode : 2;  /* bit[28-29]: 数据统计模式。
                                                         2'b00：连续触发模式。性能统计相关计数器连续计数。可保证连续统计模式下，1s内统计不溢出（1GHZMHz）。
                                                         2'b01：单次触发模式。性能统计时间计满perf_prd后，统计结果保持，并停止统计。统计周期到达上报中断。
                                                         2'b10：基于阀值触发。当统计周期到达后，如果在规定的阀值范围内，则不上报中断，同时重新启动一次统计，直到超出规定的阀值范围，并上报中断。超出阀值范围后停止计数。
                                                         注意：在dat_stat_mode为2'b01和2'b10时，当统计值溢出后保持；在dat_stat_mode为2'b00时，统计值溢出后会回绕。 */
        unsigned int  dat_stat_en   : 1;  /* bit[30]   : ddr数据统计使能。
                                                         1：使能；
                                                         0：禁止。
                                                          注意：在stat_mode=0时，此位使能表示性能统计寄存器将开始循环计数。在load_stat_mode=1时，完成一次统计之后，该位自动清零 */
        unsigned int  reserved      : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STADAT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_prd_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_prd_END     (27)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_mode_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_mode_END    (29)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_en_START    (30)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_en_END      (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DATMIN_UNION
 结构说明  : DDRC_CFG_DATMIN 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DATMIN是DMC命令计数的最小阀值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_dat_min : 28; /* bit[0-27] : 数据统计阀值寄存器，当命令小于或等于该阀值时，上报中断。
                                                       
                                                       注意：这里阀值以32为单位，即如果配置为n，则最终阀值为n*32. */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DATMIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_dmc_dat_min_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_dmc_dat_min_END    (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DATMAX_UNION
 结构说明  : DDRC_CFG_DATMAX 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DATMAX是DMC命令计数的最大阀值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_dat_max : 28; /* bit[0-27] : 数据统计阀值寄存器，当命令在大于或等于该阀值时，上报中断。
                                                       
                                                       注意：这里阀值以32为单位，即如果配置为n，则最终阀值为n*32. */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DATMAX_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_dmc_dat_max_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_dmc_dat_max_END    (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION
 结构说明  : DDRC_CFG_STACMD 寄存器结构定义。地址偏移量:0x260，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_STACMD是DDRC性能统计使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  load_stat_prd  : 28; /* bit[0-27] : 负载统计周期。
                                                          0x0~0x1：无效配置。
                                                          0x2～0xFFFFFFF：统计周期。
                                                          实际统计周期为load_stat_prd*16*tclk（Tclk为DDRC总线时钟周期）。
                                                          注意：此配置只在load_stat_mode=2'b01或2'b10时有效。当load_stat_mode=0的连续统计模式下，性能统计相关计数器会一直计数。 */
        unsigned int  load_stat_mode : 2;  /* bit[28-29]: 负载统计模式。
                                                          2'b00：连续触发模式。性能统计相关计数器连续计数。可保证连续统计模式下，1s内统计不溢出（1GHZMHz）。
                                                          2'b01：单次触发模式。性能统计时间计满perf_prd后，统计结果保持，并停止统计。统计周期到达上报中断。
                                                          2'b10：基于阀值触发。当统计周期到达后，如果在规定的阀值范围内，则不上报中断，同时重新启动一次统计，直到超出规定的阀值范围，并上报中断。超出阀值范围后停止计数。
                                                          注意：如果负载统计的结果超出最大计数范围，则会溢出后回绕。 */
        unsigned int  load_stat_en   : 1;  /* bit[30]   : ddr负载统计使能。
                                                          1：使能；
                                                          0：禁止。
                                                           注意：在stat_mode=0时，此位使能表示性能统计寄存器将开始循环计数。在load_stat_mode=1时，完成一次统计之后，该位自动清零 */
        unsigned int  reserved       : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_prd_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_prd_END     (27)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_mode_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_mode_END    (29)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_en_START    (30)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_en_END      (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CMDMIN_UNION
 结构说明  : DDRC_CFG_CMDMIN 寄存器结构定义。地址偏移量:0x264，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CMDMIN是DMC命令计数的最小阀值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cmd_min : 28; /* bit[0-27] : 命令统计阀值寄存器，当命令小于或等于该阀值时，上报中断。
                                                       
                                                       注意：这里阀值以32为单位，即如果配置为n，则最终阀值为n*32. */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CMDMIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_dmc_cmd_min_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_dmc_cmd_min_END    (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_CMDMAX_UNION
 结构说明  : DDRC_CFG_CMDMAX 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_CMDMAX是DMC命令计数的最大阀值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cmd_max : 28; /* bit[0-27] : 命令统计阀值寄存器，当命令在大于或等于该阀值时，上报中断。
                                                       
                                                       注意：这里阀值以32为单位，即如果配置为n，则最终阀值为n*32. */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CMDMAX_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_dmc_cmd_max_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_dmc_cmd_max_END    (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_PERF_UNION
 结构说明  : DDRC_CFG_PERF 寄存器结构定义。地址偏移量:0x26C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_PERF是DDR性能统计的模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perf_prd  : 28; /* bit[0-27] : 性能统计周期。
                                                     0x0~0x1：无效配置。
                                                     0x2～0xFFFFFFF：统计周期。
                                                     实际统计周期为perf_prd*16*tclk（Tclk为DDRC总线时钟周期）。
                                                     注意：此配置只在perf_mode=1时有效。当perf_mode=0的连续统计模式下，性能统计相关计数器会一直计数。 */
        unsigned int  perf_mode : 1;  /* bit[28]   : 性能统计模式。
                                                     0：连续触发模式。性能统计相关计数器连续计数。可保证在连续统计模式下，1s内统计不溢出（1GHZMHz）。
                                                     1：单次触发模式。性能统计时间计满perf_prd后，统计结果保持，并停止统计。
                                                     注意：当统计值溢出后保持。 */
        unsigned int  flux_en   : 1;  /* bit[29]   : DMC流量监测使能。
                                                     0：流量监测关闭。
                                                     1：流量监测使能。
                                                     使能流量监测时，统计模块会将DDR接口占用的周期数按ID号反馈给各请求端口。配合端口的流量设置可以进行流量控制。 */
        unsigned int  reserved  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PERF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_prd_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_prd_END     (27)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_mode_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_mode_END    (28)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_flux_en_START    (29)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_flux_en_END      (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_STAID_UNION
 结构说明  : DDRC_CFG_STAID 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_STAID是DDR性能统计的命令ID配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sta_id : 32; /* bit[0-31]: 配置对指定的ID，进行性能统计。与sta_idmask配合使用。
                                                 
                                                 注意：这个id包括了mid，实际上mid在整个id的高位部分。另外，该寄存器的位宽由MID+ID+PID(4bit)决定。超出部分为只读。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STAID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STAID_sta_id_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_STAID_sta_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_UNION
 结构说明  : DDRC_CFG_STAIDMSK 寄存器结构定义。地址偏移量:0x274，初值:0xFFFFFFFF，宽度:32
 寄存器说明: DDRC_CFG_STAID是DDR性能统计的命令ID MASK配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sta_idmask : 32; /* bit[0-31]: 配置对指定的ID屏蔽信号。
                                                     DDRC中的性能统计相关寄存器，仅对特定ID的命令进行统计。Cmd_id&sta_idmask=sta_id。
                                                     
                                                     另外，该寄存器的位宽由MID+ID+PID(4bit)决定。超出部分为只读。其默认值为{MID+ID+PID{1'b1}}. */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DUM_EN_UNION
 结构说明  : DDRC_CFG_DUM_EN 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DUM_EN是DDR的dummy read开关控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dummy_rd_en : 1;  /* bit[0]   : Dummy rd使能控制寄存器。
                                                      1：使能dummy read功能；
                                                      0：关闭dummy read功能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DUM_EN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_dummy_rd_en_START  (0)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_dummy_rd_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_UNION
 结构说明  : DDRC_CFG_DUM_CFG 寄存器结构定义。地址偏移量:0x27C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CFG_DUM_CFG是DDR的dummy read功能的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dummy_rd_cnt  : 28; /* bit[0-27] : dummy read的读取间隔计数器。其计数间隔为n*16，最每配置1，代表16个cycle.
                                                         
                                                         注意：由于dummy read每个rank在读取时存在发送active及读命令等时间及状态机的开销，其最小配置值建议不能小于(rank个数x8),即每个rank至少要128个周期。 */
        unsigned int  dummy_rd_mode : 2;  /* bit[28-29]: dummy read读取模式控制。
                                                         00：普通的读；
                                                         01：MPC的读；
                                                         10：mrr的读取；
                                                         11：reserve. */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_cnt_START   (0)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_cnt_END     (27)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_mode_START  (28)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_mode_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_INTMSK_UNION
 结构说明  : DDRC_INTMSK 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: DDRC_INTMSK是DDRC中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_int_mask         : 1;  /* bit[0]    : DDR ECC单比错误特中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  flux_int_mask         : 1;  /* bit[1]    : DDR FLUX统计周期到达中断屏蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断； */
        unsigned int  rec_int_mask          : 1;  /* bit[2]    : DDR REC错误恢复完成中断屏蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  rec_err_int_mask      : 1;  /* bit[3]    : DDR REC异常中断屏蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  merr_int_mask         : 1;  /* bit[4]    : DDR ECC多比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  sref_err_int_mask     : 1;  /* bit[5]    : DDR 自刷新时接口有命令访问错误。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  tmon_err_int_mask     : 1;  /* bit[6]    : LP DDR 器件温度轮询异常中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  tmon_upd_int_mask     : 1;  /* bit[7]    : LP DDR 器件温度轮询更新中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  dimm_parity_int_mask  : 1;  /* bit[8]    : DDR DIMM奇偶校验错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  stacmd_min_int_mask   : 1;  /* bit[9]    : DDR LOAD统计周期到或下溢中断蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断； */
        unsigned int  stacmd_max_int_mask   : 1;  /* bit[10]   : DDR LOAD统计上溢中断蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断； */
        unsigned int  reserved_0            : 1;  /* bit[11]   : 保留。 */
        unsigned int  rdtimeout_int_mask    : 1;  /* bit[12]   : DDRPHY 读数据超时中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  stadat_min_int_mask   : 1;  /* bit[13]   : DDR 数据统计周期到或下溢中断蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断； */
        unsigned int  stadat_max_int_mask   : 1;  /* bit[14]   : DDR 数据统计上溢中断蔽使能
                                                                 1：屏蔽中断；
                                                                 0：使能中断； */
        unsigned int  reserved_1            : 1;  /* bit[15]   : 保留。 */
        unsigned int  aref_alarm_int_mask   : 1;  /* bit[16]   : DDR AREF命令错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  osc_rd_int_mask       : 1;  /* bit[17]   : Oscillator读取中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  osc_ovth_int_mask     : 1;  /* bit[18]   : Oscillator超出阀值中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  osc_overflow_int_mask : 1;  /* bit[19]   : Oscillator run time count溢出中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  sbram_serr_int_mask   : 1;  /* bit[20]   : SBRAM单比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  reserved_2            : 3;  /* bit[21-23]: 保留。 */
        unsigned int  sbram_merr_int_mask   : 1;  /* bit[24]   : SBRAM多比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  reserved_3            : 3;  /* bit[25-27]: 保留。 */
        unsigned int  rpram_serr_int_mask   : 1;  /* bit[28]   : RPRAM单比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  recram_serr_int_mask  : 1;  /* bit[29]   : RECRAM单比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  recram_merr_int_mask  : 1;  /* bit[30]   : RECRAM多比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
        unsigned int  rpram_merr_int_mask   : 1;  /* bit[31]   : RPRAM多比特错误中断屏蔽使能。
                                                                 1：屏蔽中断；
                                                                 0：使能中断。 */
    } reg;
} SOC_DDRC_DMC_DDRC_INTMSK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_INTMSK_serr_int_mask_START          (0)
#define SOC_DDRC_DMC_DDRC_INTMSK_serr_int_mask_END            (0)
#define SOC_DDRC_DMC_DDRC_INTMSK_flux_int_mask_START          (1)
#define SOC_DDRC_DMC_DDRC_INTMSK_flux_int_mask_END            (1)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_int_mask_START           (2)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_int_mask_END             (2)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_err_int_mask_START       (3)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_err_int_mask_END         (3)
#define SOC_DDRC_DMC_DDRC_INTMSK_merr_int_mask_START          (4)
#define SOC_DDRC_DMC_DDRC_INTMSK_merr_int_mask_END            (4)
#define SOC_DDRC_DMC_DDRC_INTMSK_sref_err_int_mask_START      (5)
#define SOC_DDRC_DMC_DDRC_INTMSK_sref_err_int_mask_END        (5)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_err_int_mask_START      (6)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_err_int_mask_END        (6)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_upd_int_mask_START      (7)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_upd_int_mask_END        (7)
#define SOC_DDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_START   (8)
#define SOC_DDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_END     (8)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_min_int_mask_START    (9)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_min_int_mask_END      (9)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_max_int_mask_START    (10)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_max_int_mask_END      (10)
#define SOC_DDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_START     (12)
#define SOC_DDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_END       (12)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_min_int_mask_START    (13)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_min_int_mask_END      (13)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_max_int_mask_START    (14)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_max_int_mask_END      (14)
#define SOC_DDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_START    (16)
#define SOC_DDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_END      (16)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_rd_int_mask_START        (17)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_rd_int_mask_END          (17)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_ovth_int_mask_START      (18)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_ovth_int_mask_END        (18)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_overflow_int_mask_START  (19)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_overflow_int_mask_END    (19)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_START    (20)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_END      (20)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_START    (24)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_END      (24)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_START    (28)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_END      (28)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_serr_int_mask_START   (29)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_serr_int_mask_END     (29)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_merr_int_mask_START   (30)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_merr_int_mask_END     (30)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_START    (31)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_END      (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_RINT_UNION
 结构说明  : DDRC_RINT 寄存器结构定义。地址偏移量:0x284，初值:0x00000000，宽度:32
 寄存器说明: DDRC_RINT是DDRC原始中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rint         : 1;  /* bit[0]    : DDR ECC单比错误特原始中断。写1中断清除 */
        unsigned int  flux_rint         : 1;  /* bit[1]    : DDR FLUX统计周期到达中断。写1中断清除。 */
        unsigned int  rec_rint          : 1;  /* bit[2]    : DDR REC错误恢复完成中断。写1中断清除 */
        unsigned int  rec_err_rint      : 1;  /* bit[3]    : DDR REC异常错误中断。写1中断清除 */
        unsigned int  merr_rint         : 1;  /* bit[4]    : DDR ECC多比特错误原始中断。写1中断清除 */
        unsigned int  sref_err_rint     : 1;  /* bit[5]    : 自刷新接口有命令访问中断。写1中断清除。 */
        unsigned int  tmon_err_rint     : 1;  /* bit[6]    : LP DDR 器件温度轮询异常中断。写1中断清除。 */
        unsigned int  tmon_upd_rint     : 1;  /* bit[7]    : LP DDR 器件温度轮询更新中断。写1中断清除。 */
        unsigned int  dimm_parity_rint  : 1;  /* bit[8]    : DDR DIMM奇偶校验错误原始中断。写1中断清除。 */
        unsigned int  stacmd_min_rint   : 1;  /* bit[9]    : DDR LOAD统计周期到达中断或超出阀值中断(下溢）。写1中断清除 */
        unsigned int  stacmd_max_rint   : 1;  /* bit[10]   : DDR LOAD超出阀值中断(上溢）。写1中断清除 */
        unsigned int  reserved_0        : 1;  /* bit[11]   : 保留。 */
        unsigned int  rdtimeout_rint    : 1;  /* bit[12]   : DDRPHY 读数据超时原始中断。写1中断清除 */
        unsigned int  stadat_min_rint   : 1;  /* bit[13]   : DDR 数据统计周期到达中断或超出阀值中断(下溢）。写1中断清除 */
        unsigned int  stadat_max_rint   : 1;  /* bit[14]   : DDR 数据统计超出阀值中断(上溢）。写1中断清除 */
        unsigned int  reserved_1        : 1;  /* bit[15]   : 保留。 */
        unsigned int  aref_alarm_rint   : 1;  /* bit[16]   : DDR AREF命令错误原始中断。写1中断清除 */
        unsigned int  osc_rd_rint       : 1;  /* bit[17]   : Oscillator读取中断。写1中断清除。 */
        unsigned int  osc_ovth_rint     : 1;  /* bit[18]   : Oscillator超出阀值中断。写1中断清除。 */
        unsigned int  osc_overflow_rint : 1;  /* bit[19]   : Oscillator的runtime count溢出中断。写1清除。 */
        unsigned int  sbram_serr_rint   : 1;  /* bit[20]   : SBRAM单比特错误中断。写1中断清除。 */
        unsigned int  reserved_2        : 3;  /* bit[21-23]: 保留。 */
        unsigned int  sbram_merr_rint   : 1;  /* bit[24]   : SBRAM多比特错误中断。写1中断清除。 */
        unsigned int  reserved_3        : 3;  /* bit[25-27]: 保留。 */
        unsigned int  rpram_serr_rint   : 1;  /* bit[28]   : RPRAM单比特错误中断。写1中断清除。 */
        unsigned int  recram_serr_rint  : 1;  /* bit[29]   : RECRAM单比特错误中断。写1中断清除。 */
        unsigned int  recram_merr_rint  : 1;  /* bit[30]   : RECRAM多比特错误中断。写1中断清除。 */
        unsigned int  rpram_merr_rint   : 1;  /* bit[31]   : RPRAM多比特错误中断。写1中断清除。 */
    } reg;
} SOC_DDRC_DMC_DDRC_RINT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_RINT_serr_rint_START          (0)
#define SOC_DDRC_DMC_DDRC_RINT_serr_rint_END            (0)
#define SOC_DDRC_DMC_DDRC_RINT_flux_rint_START          (1)
#define SOC_DDRC_DMC_DDRC_RINT_flux_rint_END            (1)
#define SOC_DDRC_DMC_DDRC_RINT_rec_rint_START           (2)
#define SOC_DDRC_DMC_DDRC_RINT_rec_rint_END             (2)
#define SOC_DDRC_DMC_DDRC_RINT_rec_err_rint_START       (3)
#define SOC_DDRC_DMC_DDRC_RINT_rec_err_rint_END         (3)
#define SOC_DDRC_DMC_DDRC_RINT_merr_rint_START          (4)
#define SOC_DDRC_DMC_DDRC_RINT_merr_rint_END            (4)
#define SOC_DDRC_DMC_DDRC_RINT_sref_err_rint_START      (5)
#define SOC_DDRC_DMC_DDRC_RINT_sref_err_rint_END        (5)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_err_rint_START      (6)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_err_rint_END        (6)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_upd_rint_START      (7)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_upd_rint_END        (7)
#define SOC_DDRC_DMC_DDRC_RINT_dimm_parity_rint_START   (8)
#define SOC_DDRC_DMC_DDRC_RINT_dimm_parity_rint_END     (8)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_min_rint_START    (9)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_min_rint_END      (9)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_max_rint_START    (10)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_max_rint_END      (10)
#define SOC_DDRC_DMC_DDRC_RINT_rdtimeout_rint_START     (12)
#define SOC_DDRC_DMC_DDRC_RINT_rdtimeout_rint_END       (12)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_min_rint_START    (13)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_min_rint_END      (13)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_max_rint_START    (14)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_max_rint_END      (14)
#define SOC_DDRC_DMC_DDRC_RINT_aref_alarm_rint_START    (16)
#define SOC_DDRC_DMC_DDRC_RINT_aref_alarm_rint_END      (16)
#define SOC_DDRC_DMC_DDRC_RINT_osc_rd_rint_START        (17)
#define SOC_DDRC_DMC_DDRC_RINT_osc_rd_rint_END          (17)
#define SOC_DDRC_DMC_DDRC_RINT_osc_ovth_rint_START      (18)
#define SOC_DDRC_DMC_DDRC_RINT_osc_ovth_rint_END        (18)
#define SOC_DDRC_DMC_DDRC_RINT_osc_overflow_rint_START  (19)
#define SOC_DDRC_DMC_DDRC_RINT_osc_overflow_rint_END    (19)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_serr_rint_START    (20)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_serr_rint_END      (20)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_merr_rint_START    (24)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_merr_rint_END      (24)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_serr_rint_START    (28)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_serr_rint_END      (28)
#define SOC_DDRC_DMC_DDRC_RINT_recram_serr_rint_START   (29)
#define SOC_DDRC_DMC_DDRC_RINT_recram_serr_rint_END     (29)
#define SOC_DDRC_DMC_DDRC_RINT_recram_merr_rint_START   (30)
#define SOC_DDRC_DMC_DDRC_RINT_recram_merr_rint_END     (30)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_merr_rint_START    (31)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_merr_rint_END      (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_INTSTS_UNION
 结构说明  : DDRC_INTSTS 寄存器结构定义。地址偏移量:0x288，初值:0x00000000，宽度:32
 寄存器说明: DDRC_INTSTS是DDRC中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_intsts         : 1;  /* bit[0]    : DDR ECC单比错误特中断。 */
        unsigned int  flux_intsts         : 1;  /* bit[1]    : DDR FLUX统计周期到达中断 */
        unsigned int  rec_intsts          : 1;  /* bit[2]    : DDR REC错误恢复完成中断 */
        unsigned int  rec_err_intsts      : 1;  /* bit[3]    : DDR REC异常中断 */
        unsigned int  merr_intsts         : 1;  /* bit[4]    : DDR ECC多比特错误中断。 */
        unsigned int  sref_err_intsts     : 1;  /* bit[5]    : 自刷新接口有命令访问中断。 */
        unsigned int  tmon_err_intsts     : 1;  /* bit[6]    : LP DDR 器件温度轮询异常中断。 */
        unsigned int  tmon_upd_intsts     : 1;  /* bit[7]    : LP DDR 器件温度轮询更新中断。 */
        unsigned int  dimm_parity_intsts  : 1;  /* bit[8]    : DDR DIMM奇偶校验错误中断。 */
        unsigned int  stacmd_min_intsts   : 1;  /* bit[9]    : DDR LOAD统计周期到达或下溢中断。 */
        unsigned int  stacmd_max_intsts   : 1;  /* bit[10]   : DDR LOAD统计上溢中断。 */
        unsigned int  reserved_0          : 1;  /* bit[11]   : 保留。 */
        unsigned int  rdtimeout_intsts    : 1;  /* bit[12]   : DDRPHY 读数据超时中断。 */
        unsigned int  stadat_min_intsts   : 1;  /* bit[13]   : DDR 数据统计周期到达或下溢中断。 */
        unsigned int  stadat_max_intsts   : 1;  /* bit[14]   : DDR 数据统计上溢中断。 */
        unsigned int  reserved_1          : 1;  /* bit[15]   : 保留。 */
        unsigned int  aref_alarm_intsts   : 1;  /* bit[16]   : DDR AREF命令错误中断。 */
        unsigned int  osc_rd_intsts       : 1;  /* bit[17]   : Oscillator读取中断。 */
        unsigned int  osc_ovth_intsts     : 1;  /* bit[18]   : Oscillator超出阀值中断。 */
        unsigned int  osc_overflow_intsts : 1;  /* bit[19]   : Oscillator run time count溢出中断。 */
        unsigned int  sbram_serr_intsts   : 1;  /* bit[20]   : SBRAM单比特错误中断。 */
        unsigned int  reserved_2          : 3;  /* bit[21-23]: 保留。 */
        unsigned int  sbram_merr_intsts   : 1;  /* bit[24]   : SBRAM多比特错误中断。 */
        unsigned int  reserved_3          : 3;  /* bit[25-27]: 保留。 */
        unsigned int  rpram_serr_intsts   : 1;  /* bit[28]   : RPRAM单比特错误中断。 */
        unsigned int  recram_serr_intsts  : 1;  /* bit[29]   : RECRAM单比特错误中断。 */
        unsigned int  recram_merr_intsts  : 1;  /* bit[30]   : RECRAM多比特错误中断。 */
        unsigned int  rpram_merr_intsts   : 1;  /* bit[31]   : RPRAM多比特错误中断。 */
    } reg;
} SOC_DDRC_DMC_DDRC_INTSTS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_INTSTS_serr_intsts_START          (0)
#define SOC_DDRC_DMC_DDRC_INTSTS_serr_intsts_END            (0)
#define SOC_DDRC_DMC_DDRC_INTSTS_flux_intsts_START          (1)
#define SOC_DDRC_DMC_DDRC_INTSTS_flux_intsts_END            (1)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_intsts_START           (2)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_intsts_END             (2)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_err_intsts_START       (3)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_err_intsts_END         (3)
#define SOC_DDRC_DMC_DDRC_INTSTS_merr_intsts_START          (4)
#define SOC_DDRC_DMC_DDRC_INTSTS_merr_intsts_END            (4)
#define SOC_DDRC_DMC_DDRC_INTSTS_sref_err_intsts_START      (5)
#define SOC_DDRC_DMC_DDRC_INTSTS_sref_err_intsts_END        (5)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_err_intsts_START      (6)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_err_intsts_END        (6)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_upd_intsts_START      (7)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_upd_intsts_END        (7)
#define SOC_DDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_START   (8)
#define SOC_DDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_END     (8)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_min_intsts_START    (9)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_min_intsts_END      (9)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_max_intsts_START    (10)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_max_intsts_END      (10)
#define SOC_DDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_START     (12)
#define SOC_DDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_END       (12)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_min_intsts_START    (13)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_min_intsts_END      (13)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_max_intsts_START    (14)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_max_intsts_END      (14)
#define SOC_DDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_START    (16)
#define SOC_DDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_END      (16)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_rd_intsts_START        (17)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_rd_intsts_END          (17)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_ovth_intsts_START      (18)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_ovth_intsts_END        (18)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_overflow_intsts_START  (19)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_overflow_intsts_END    (19)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_START    (20)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_END      (20)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_START    (24)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_END      (24)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_START    (28)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_END      (28)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_serr_intsts_START   (29)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_serr_intsts_END     (29)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_merr_intsts_START   (30)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_merr_intsts_END     (30)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_START    (31)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_END      (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_STATUS_UNION
 结构说明  : DDRC_CURR_STATUS 寄存器结构定义。地址偏移量:0x290，初值:0x00000101，宽度:32
 寄存器说明: DDRC_CURR_STATUS是DDRC状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  busy      : 1;  /* bit[0]   : DDRC总体忙状态寄存器。
                                                    1：命令处理中；
                                                    0：空闲。 */
        unsigned int  reserved_0: 3;  /* bit[1-3] : 保留。 */
        unsigned int  busy_dmc  : 1;  /* bit[4]   : DDRC DMC模块的忙状态寄存器。
                                                    1：命令处理中；
                                                    0：空闲。 */
        unsigned int  reserved_1: 3;  /* bit[5-7] : 保留。 */
        unsigned int  busy_func : 1;  /* bit[8]   : DDRC FUNC模块的忙状态寄存器。（复位处于sref状态）
                                                    1：命令处理中；
                                                    0：空闲。 */
        unsigned int  reserved_2: 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_STATUS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_START       (0)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_END         (0)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_dmc_START   (4)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_dmc_END     (4)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_func_START  (8)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_func_END    (8)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_FUNC_UNION
 结构说明  : DDRC_CURR_FUNC 寄存器结构定义。地址偏移量:0x294，初值:0x00000001，宽度:32
 寄存器说明: DDRC_CURR_FUNC是DDRC FUNC模块状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  in_sref           : 1;  /* bit[0]    : DDRC自刷新状态。
                                                             1：自刷新状态；
                                                             0：正常状态。 */
        unsigned int  in_tmon           : 1;  /* bit[1]    : DDRC处于读取刷新率过程当中。
                                                             1：正在读取刷新率真；
                                                             0：空闲状态。 */
        unsigned int  reserved_0        : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  in_init           : 1;  /* bit[4]    : DDRC初始化状态。
                                                             1：初始化状态；
                                                             0：正常状态。 */
        unsigned int  dfi_init_complete : 1;  /* bit[5]    : DFI初始化状态。
                                                             1：正常工作状态；
                                                             0：DFI初始化过程中。 */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留。 */
        unsigned int  aref_opt_stat     : 1;  /* bit[8]    : 自动刷新优化模式状态指示。
                                                             1：表示处理优化模式；
                                                             0：表示已经退出优化模式。
                                                             
                                                             注意：在软件配置或通过csysreq接口请求进入自刷新前，需要确保已经退出自动刷新优化模式。因为处于自刷新优化模式时，可能会有未发送的postponed命令。 */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留。 */
        unsigned int  in_sfc            : 1;  /* bit[12]   : DDRC SFC状态寄存器。
                                                             1：SFC命令处理中；
                                                             0：空闲。 */
        unsigned int  reserved_3        : 3;  /* bit[13-15]: 保留。 */
        unsigned int  in_eccwb          : 1;  /* bit[16]   : DDRC ECC Write Back状态寄存器。
                                                             1：ECC Write Back命令处理中；
                                                             0：空闲。 */
        unsigned int  reserved_4        : 3;  /* bit[17-19]: 保留。 */
        unsigned int  in_mtest          : 1;  /* bit[20]   : DDRC Memory Test状态寄存器。
                                                             1：Memory Test处理中；
                                                             0：空闲。 */
        unsigned int  reserved_5        : 3;  /* bit[21-23]: 保留。 */
        unsigned int  in_mclr           : 1;  /* bit[24]   : DDRC Memory Clean状态寄存器。
                                                             1：Memory Clean处理中；
                                                             0：空闲。 */
        unsigned int  in_rec            : 1;  /* bit[25]   : DDRC REC状态寄存器
                                                             1： Error Recovery处理中；
                                                             0： 空闲。 */
        unsigned int  reserved_6        : 2;  /* bit[26-27]: 保留。 */
        unsigned int  in_phyupd         : 1;  /* bit[28]   : DDRC PHYUPD状态寄存器。
                                                             1：PHY进行Update；
                                                             0：空闲。 */
        unsigned int  in_srpd           : 1;  /* bit[29]   : DDRC SREFPD状态(LPDDR4模式）。
                                                             1：SREFPD状态；
                                                             0：正常状态。 */
        unsigned int  reserved_7        : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sref_START            (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sref_END              (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_tmon_START            (1)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_tmon_END              (1)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_init_START            (4)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_init_END              (4)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_dfi_init_complete_START  (5)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_dfi_init_complete_END    (5)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_aref_opt_stat_START      (8)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_aref_opt_stat_END        (8)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sfc_START             (12)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sfc_END               (12)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_eccwb_START           (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_eccwb_END             (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mtest_START           (20)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mtest_END             (20)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mclr_START            (24)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mclr_END              (24)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_rec_START             (25)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_rec_END               (25)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_phyupd_START          (28)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_phyupd_END            (28)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_srpd_START            (29)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_srpd_END              (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_FUNC2_UNION
 结构说明  : DDRC_CURR_FUNC2 寄存器结构定义。地址偏移量:0x298，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CURR_FUNC2是DDRC FUNC模块状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  in_pd    : 16; /* bit[0-15] : DDRC PowerDown状态。
                                                    1：PowerDown状态；
                                                    0：正常状态。
                                                    每一比特代表1个Rank。 */
        unsigned int  in_asref : 16; /* bit[16-31]: DDRC Auto Selfrefresh状态。
                                                    1：Auto Selfrefresh状态；
                                                    0：正常状态。
                                                    每一比特代表1个Rank。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_pd_START     (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_pd_END       (15)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_asref_START  (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_asref_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_FUNC3_UNION
 结构说明  : DDRC_CURR_FUNC3 寄存器结构定义。地址偏移量:0x29C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CURR_FUNC3是DDRC FUNC模块状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  in_dummy_rd : 16; /* bit[0-15] : DDRC 处于dummy read状态。
                                                       1.dummy read状态；
                                                       0.正常状态。
                                                       注意：实际位宽由rank数决定。 */
        unsigned int  in_osc      : 16; /* bit[16-31]: DDRC 处于读oscillator状态。
                                                       1.oscillator状态；
                                                       0.正常状态。
                                                       注意：实际位宽由rank数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_dummy_rd_START  (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_dummy_rd_END    (15)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_osc_START       (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_osc_END         (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_EXECST_UNION
 结构说明  : DDRC_CURR_EXECST 寄存器结构定义。地址偏移量:0x2A0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_CURR_EXECST是DDRC命令状态机状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cv : 16; /* bit[0-15] : 控制器命令是否有效。
                                                  0：表示没有命令；
                                                  1：表示命令有效。 */
        unsigned int  dmc_ct : 16; /* bit[16-31]: 控制器命令类型。
                                                  0:表示读命令；
                                                  1：表示写命令。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_EXECST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_cv_START  (0)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_cv_END    (15)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_ct_START  (16)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_ct_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_UNION
 结构说明  : DDRC_CURR_WGFIFOST 寄存器结构定义。地址偏移量:0x2A4，初值:0x00000001，宽度:32
 寄存器说明: DDRC_CURR_WGFIFOST是DDRC写FIFO空满状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wgntfifo_e : 1;  /* bit[0]   : WGNT_FIFO空满状态，空表示所有写数据已经接收完毕，非空表示写数据没有接收完成。
                                                     1：FIFO空；
                                                     0：FIFO非空。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_START  (0)
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_UNION
 结构说明  : DDRC_HIS_SERR_ADR0 寄存器结构定义。地址偏移量:0x2D0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERRADR0是DDRC ECC单比特错误低位地址状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_adr0 : 32; /* bit[0-31]: DDRC ECC单比特错误低位地址寄存器。
                                                    注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。
                                                    [17：0]为列地址；
                                                    [31：18]为行地址。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_UNION
 结构说明  : DDRC_HIS_SERR_ADR1 寄存器结构定义。地址偏移量:0x2D4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERRADR1是DDRC ECC单比特错误高位地址状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_adr1 : 12; /* bit[0-11] : DDRC ECC单比特错误高位地址寄存器。
                                                     注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。
                                                     [3：0]为行地址
                                                     [7:4]为bank地址
                                                     [11：8]为片选。 */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_END    (11)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_UNION
 结构说明  : DDRC_HIS_SERR_RDATA0 寄存器结构定义。地址偏移量:0x2D8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA0是DDR ECC单比特错误读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata0 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据31~0bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_UNION
 结构说明  : DDRC_HIS_SERR_RDATA1 寄存器结构定义。地址偏移量:0x2DC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA1是DDR ECC单比特错误读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata1 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据63~32bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_UNION
 结构说明  : DDRC_HIS_SERR_RDATA2 寄存器结构定义。地址偏移量:0x2E0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA2是DDR ECC单比特错误读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata2 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据95~64bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_UNION
 结构说明  : DDRC_HIS_SERR_RDATA3 寄存器结构定义。地址偏移量:0x2E4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA3是DDR ECC单比特错误读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata3 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据127~96bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_UNION
 结构说明  : DDRC_HIS_SERR_RDATA4 寄存器结构定义。地址偏移量:0x2E8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA4是DDR ECC单比特错误读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata4 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据159~128bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_UNION
 结构说明  : DDRC_HIS_SERR_RDATA5 寄存器结构定义。地址偏移量:0x2EC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA5是DDR ECC单比特错误读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata5 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据191~160bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_UNION
 结构说明  : DDRC_HIS_SERR_RDATA6 寄存器结构定义。地址偏移量:0x2F0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA6是DDR ECC单比特错误读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata6 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据223~192bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_UNION
 结构说明  : DDRC_HIS_SERR_RDATA7 寄存器结构定义。地址偏移量:0x2F4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA7是DDR ECC单比特错误读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata7 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据255~224bit寄存器。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_UNION
 结构说明  : DDRC_HIS_SERR_RDATA8 寄存器结构定义。地址偏移量:0x2F8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_RDATA8是DDR ECC单比特错误读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_rdata8 : 32; /* bit[0-31]: DDRC ECC单比特错误读数据287~256bit寄存器（ECC校验位）。
                                                      注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA0 寄存器结构定义。地址偏移量:0x2FC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA0是DDR ECC单比特错误时期望的正确读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata0 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据31~0bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA1 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA1是DDR ECC单比特错误时期望的正确读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata1 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据63~32bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA2 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA2是DDR ECC单比特错误时期望的正确读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata2 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据95~64bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA3 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA3是DDR ECC单比特错误时期望的正确读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata3 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据127~96bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA4 寄存器结构定义。地址偏移量:0x30C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA4是DDR ECC单比特错误时期望的正确读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata4 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据159~128bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA5 寄存器结构定义。地址偏移量:0x310，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA5是DDR ECC单比特错误时期望的正确读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata5 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据191~160bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA6 寄存器结构定义。地址偏移量:0x314，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA6是DDR ECC单比特错误时期望的正确读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata6 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据223~192bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA7 寄存器结构定义。地址偏移量:0x318，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA7是DDR ECC单比特错误时期望的正确读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata7 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据255~224bit寄存器。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_UNION
 结构说明  : DDRC_HIS_SERR_EXPDATA8 寄存器结构定义。地址偏移量:0x31C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERR_EXPDATA8是DDR ECC单比特错误时期望的正确读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_expdata8 : 32; /* bit[0-31]: DDRC ECC单比特错误时期望的正确读数据287~256bit寄存器（ECC校验位）。
                                                        注意：此寄存器记录第一次发生单比特错误的数据低位地址。当清除对应的单比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_UNION
 结构说明  : DDRC_HIS_MERR_ADR0 寄存器结构定义。地址偏移量:0x320，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERRADR0是DDRC ECC多比特错误低位地址状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_adr0 : 32; /* bit[0-31]: DDRC ECC多比特错误低低地址寄存器。
                                                    注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_UNION
 结构说明  : DDRC_HIS_MERR_ADR1 寄存器结构定义。地址偏移量:0x324，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERRADR1是DDRC ECC多比特错误高位地址状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_adr1 : 12; /* bit[0-11] : DDRC ECC多比特错误高位地址寄存器。
                                                     注意：此寄存器记录第一次发生多比特错误的数据高位地址。当清除对应的多比特错误中断时，解除锁定。 */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_END    (11)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_ID_UNION
 结构说明  : DDRC_HIS_MERR_ID 寄存器结构定义。地址偏移量:0x328，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERRADR1是DDRC ECC多比特错误ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_id : 32; /* bit[0-31]: DDRC ECC多比特错误ID寄存器。
                                                  注意：此寄存器记录第一次发生多比特错误的ID，当清楚多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_merr_id_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_merr_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_UNION
 结构说明  : DDRC_HIS_MERR_RDATA0 寄存器结构定义。地址偏移量:0x330，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA0是DDR ECC多比特错误读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata0 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据31~0bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_UNION
 结构说明  : DDRC_HIS_MERR_RDATA1 寄存器结构定义。地址偏移量:0x334，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA1是DDR ECC多比特错误读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata1 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据63~32bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_UNION
 结构说明  : DDRC_HIS_MERR_RDATA2 寄存器结构定义。地址偏移量:0x338，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA2是DDR ECC多比特错误读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata2 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据95~64bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_UNION
 结构说明  : DDRC_HIS_MERR_RDATA3 寄存器结构定义。地址偏移量:0x33C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA3是DDR ECC多比特错误读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata3 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据127~96bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_UNION
 结构说明  : DDRC_HIS_MERR_RDATA4 寄存器结构定义。地址偏移量:0x340，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA4是DDR ECC多比特错误读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata4 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据159~128bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_UNION
 结构说明  : DDRC_HIS_MERR_RDATA5 寄存器结构定义。地址偏移量:0x344，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA5是DDR ECC多比特错误读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata5 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据191~160bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_UNION
 结构说明  : DDRC_HIS_MERR_RDATA6 寄存器结构定义。地址偏移量:0x348，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA6是DDR ECC多比特错误读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata6 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据223~192bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_UNION
 结构说明  : DDRC_HIS_MERR_RDATA7 寄存器结构定义。地址偏移量:0x34C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA7是DDR ECC多比特错误读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata7 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据255~224bit寄存器。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_UNION
 结构说明  : DDRC_HIS_MERR_RDATA8 寄存器结构定义。地址偏移量:0x350，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_RDATA8是DDR ECC多比特错误读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_rdata8 : 32; /* bit[0-31]: DDRC ECC多比特错误读数据287~256bit寄存器（ECC校验位）。
                                                      注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA0 寄存器结构定义。地址偏移量:0x354，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA0是DDR ECC多比特错误时期望的正确读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata0 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据31~0bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_expdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_expdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA1 寄存器结构定义。地址偏移量:0x358，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA1是DDR ECC多比特错误时期望的正确读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata1 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据63~32bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_expdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_expdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA2 寄存器结构定义。地址偏移量:0x35C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA2是DDR ECC多比特错误时期望的正确读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata2 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据95~64bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_expdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_expdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA3 寄存器结构定义。地址偏移量:0x360，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA3是DDR ECC多比特错误时期望的正确读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata3 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据127~96bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_expdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_expdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA4 寄存器结构定义。地址偏移量:0x364，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA4是DDR ECC多比特错误时期望的正确读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata4 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据159~128bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_expdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_expdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA5 寄存器结构定义。地址偏移量:0x368，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA5是DDR ECC多比特错误时期望的正确读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata5 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据191~160bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_expdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_expdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA6 寄存器结构定义。地址偏移量:0x36C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA6是DDR ECC多比特错误时期望的正确读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata6 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据223~192bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_expdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_expdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA7 寄存器结构定义。地址偏移量:0x370，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA7是DDR ECC多比特错误时期望的正确读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata7 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据255~224bit寄存器。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_expdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_expdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_UNION
 结构说明  : DDRC_HIS_MERR_EXPDATA8 寄存器结构定义。地址偏移量:0x374，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MERR_EXPDATA8是DDR ECC多比特错误时期望的正确读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_expdata8 : 32; /* bit[0-31]: DDRC ECC多比特错误时期望的正确读数据287~256bit寄存器（ECC校验位）。
                                                        注意：此寄存器记录第一次发生多比特错误的数据低位地址。当清除对应的多比特错误中断时，解除锁定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_expdata8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_expdata8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SERRCNT_UNION
 结构说明  : DDRC_HIS_SERRCNT 寄存器结构定义。地址偏移量:0x378，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERRCNT是DDRC的ECC错误统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  serr_cnt : 32; /* bit[0-31]: 单比特ECC数据错误统计值饱和计数 。
                                                   注意：此寄存器为读清。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERRCNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MERRCNT_UNION
 结构说明  : DDRC_HIS_MERRCNT 寄存器结构定义。地址偏移量:0x37C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SERRCNT是DDRC的ECC错误统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merr_cnt : 32; /* bit[0-31]: 多比特数据错误统计值饱和计数 。
                                                   注意：此寄存器为读清。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERRCNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_UNION
 结构说明  : DDRC_HIS_FLUX_WR 寄存器结构定义。地址偏移量:0x380，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUX_WR是DDRC所有写命令流量统计寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_wr : 32; /* bit[0-31]: DDRC所有ID的MASTER写流量统计。在有效统计周期内计数。
                                                  单位为DMC位宽。
                                                  在perf_mode=1 时溢出后维持。
                                                  在perf_mode=0 时溢出后卷绕。
                                                  当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_UNION
 结构说明  : DDRC_HIS_FLUX_RD 寄存器结构定义。地址偏移量:0x384，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUX_RD是DDRC所有读命令流量统计寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_rd : 32; /* bit[0-31]: DDRC所有ID的MASTER读流量统计。在有效统计周期内计数。
                                                  单位为DMC位宽。
                                                  在perf_mode=1 时溢出后维持。
                                                  在perf_mode=0 时溢出后卷绕。
                                                  当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_UNION
 结构说明  : DDRC_HIS_FLUX_WCMD 寄存器结构定义。地址偏移量:0x0388，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUX_WCMD是DDRC所有写命令数目
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_wr_cmd : 32; /* bit[0-31]: DDRC所有ID的MASTER写命令个数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_UNION
 结构说明  : DDRC_HIS_FLUX_RCMD 寄存器结构定义。地址偏移量:0x038C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUX_RCMD是DDRC所有读命令数目
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_rd_cmd : 32; /* bit[0-31]: DDRC所有ID的MASTER读命令个数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_UNION
 结构说明  : DDRC_HIS_FLUXID_WR 寄存器结构定义。地址偏移量:0x390，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUXID_WR是DDRC指定ID写流量统计寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fluxid_wr : 32; /* bit[0-31]: DDRC指定ID的MASTER写流量统计。在有效统计周期内计数。
                                                    单位为DMC位宽。
                                                    在perf_mode=1 时溢出后维持。
                                                    在perf_mode=0 时溢出后卷绕。
                                                    当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_UNION
 结构说明  : DDRC_HIS_FLUXID_RD 寄存器结构定义。地址偏移量:0x394，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUXID_RD是DDRC指定ID读流量统计寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fluxid_rd : 32; /* bit[0-31]: DDRC指定ID的MASTER读流量统计。在有效统计周期内计数。
                                                    单位为DMC位宽。
                                                    在perf_mode=1 时溢出后维持。
                                                    在perf_mode=0 时溢出后卷绕。
                                                    当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_UNION
 结构说明  : DDRC_HIS_FLUXID_WCMD 寄存器结构定义。地址偏移量:0x0398，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUXID_WCMD是DDRC所有写命令数目
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fluxid_wr_cmd : 32; /* bit[0-31]: DDRC指定ID的MASTER写命令个数统计。在有效统计周期内计数。
                                                        单位为DMC位宽。
                                                        在perf_mode=1 时溢出后维持。
                                                        在perf_mode=0 时溢出后卷绕。
                                                        当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_UNION
 结构说明  : DDRC_HIS_FLUXID_RCMD 寄存器结构定义。地址偏移量:0x039C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_FLUX_RCMD是DDRC所有读命令数目
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fluxid_rd_cmd : 32; /* bit[0-31]: DDRC指定ID的MASTER读命令个数统计。在有效统计周期内计数。
                                                        在perf_mode=1 时溢出后维持。
                                                        在perf_mode=0 时溢出后卷绕。
                                                        当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_UNION
 结构说明  : DDRC_HIS_WLATCNT0 寄存器结构定义。地址偏移量:0x3A0，初值:0x0000FFFF，宽度:32
 寄存器说明: DDRC_HIS_WLATCNT0是DDRC指定ID的写命令Latency统计寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wlatcnt_min : 16; /* bit[0-15] : DDRC指定ID的写命令最小Latency统计。如果溢出维持最大值。当下一次统计开始时，清零。 */
        unsigned int  wlatcnt_max : 16; /* bit[16-31]: DDRC指定ID的写命令最大Latency统计。
                                                       下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_END    (15)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_START  (16)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_UNION
 结构说明  : DDRC_HIS_WLATCNT1 寄存器结构定义。地址偏移量:0x3A4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_WLATCNT1是DDRC指定ID的写命令Latency统计寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wlatcnt_all : 32; /* bit[0-31]: 在统计周期内，指定ID的写命令的Latency累加值（忽略低4位的结果）。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当一下次统计开始时，清零。
                                                      注意：软件可利用(wlatcnt_all)/fluxid_wr_cmd得到指定ID的写命令的平均latency。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_UNION
 结构说明  : DDRC_HIS_RLATCNT0 寄存器结构定义。地址偏移量:0x3A8，初值:0x0000FFFF，宽度:32
 寄存器说明: DDRC_HIS_RLATCNT0是DDRC指定ID的读命令Latency统计寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlatcnt_min : 16; /* bit[0-15] : DDRC指定ID的读命令最小Latency统计
                                                       。
                                                       注意：真正读最小延时为rlatcnt_min+
                                                       inhere_rlatcnt.
                                                       如果溢出维持最大值。当下一次统计开始时，清零。 */
        unsigned int  rlatcnt_max : 16; /* bit[16-31]: DDRC指定ID的读命令最大Latency统计。
                                                       真正读最大延时为rlatcnt_max+
                                                       inhere_rlatcnt.
                                                       
                                                       如果溢出维持最大值。当下一次统计开始时，清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_END    (15)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_START  (16)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_UNION
 结构说明  : DDRC_HIS_RLATCNT1 寄存器结构定义。地址偏移量:0x3AC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RLATCNT1是DDRC指定ID的读命令Latency统计寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlatcnt_all : 32; /* bit[0-31]: 在统计周期内，指定ID的读命令的Latency累加值（忽略低4位的结果）。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。一下次统计开始时，清零。
                                                      注意：软件可利用(rlatcnt_all/fluxid_rd_cmd+inhere_rlatcnt得到指定ID的读命令的平均latency。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_UNION
 结构说明  : DDRC_HIS_INHERE_RLAT_CNT 寄存器结构定义。地址偏移量:0x3B0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_INHERE_RLAT_CNT是读通道固有延时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inhere_rlatcnt : 16; /* bit[0-15] : 表示DDRC和PHY对读数据通道的固有延时;此寄存器要和rlatcnt_min,rlatcnt_max,rlatcnt_all,fluxid_rd_cmd配合使用得到真正的latency。 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_STAT_RPT_UNION
 结构说明  : DDRC_STAT_RPT 寄存器结构定义。地址偏移量:0x3B4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_STAT_RPT是DMC命令计数的累积寄存器的读指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_rpt : 3;  /* bit[0-2] : 当统计处于基于阀值统计时会保存最近的8次统计结果。该指针用于指示DDRC_HIS_CMD_SUM或DDRC_HIS_DAT_SUM读的结果指向第几次统计结果。
                                                   3'b000:最近一次；
                                                   3'b001:次近一次；
                                                    。。。
                                                   3'b111:最近第7次统计结果。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_STAT_RPT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_STAT_RPT_stat_rpt_START  (0)
#define SOC_DDRC_DMC_DDRC_STAT_RPT_stat_rpt_END    (2)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION
 结构说明  : DDRC_HIS_CMD_SUM 寄存器结构定义。地址偏移量:0x3B8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_CMD_SUM是DMC命令计数的累积寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cmd_sum : 32; /* bit[0-31]: 当前DMC暂存命令的值按周期累积，溢出卷绕 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_UNION
 结构说明  : DDRC_HIS_DAT_SUM 寄存器结构定义。地址偏移量:0x3BC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_DAT_SUM是DMC命令计数的累积寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_dat_sum : 32; /* bit[0-31]: 当前DMC暂存数据统计的值按周期累积，溢出卷绕 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_dmc_dat_sum_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_dmc_dat_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_UNION
 结构说明  : DDRC_HIS_PRE_CMD 寄存器结构定义。地址偏移量:0x3C0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_PRE_CMD是DDRC所有统计的PRECHARGE命令个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_pre_cmd : 32; /* bit[0-31]: 对指定ID的MASTER PRECHARGE命令个数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。
                                                      
                                                      注意：如果要统计所有ID的master,可以通过将sta_id/sta_idmask全部配置为0来实现。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_dmc_pre_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_dmc_pre_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_UNION
 结构说明  : DDRC_HIS_ACT_CMD 寄存器结构定义。地址偏移量:0x3C4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_ACT_CMD是DDRC所有统计的ACTIVE命令个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_act_cmd : 32; /* bit[0-31]: 对指定ID的MASTER ACTIVE命令个数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。
                                                      
                                                      注意：如果要统计所有ID的master,可以通过将sta_id/sta_idmask全部配置为0来实现。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_dmc_act_cmd_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_dmc_act_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_UNION
 结构说明  : DDRC_HIS_BNK_CHG 寄存器结构定义。地址偏移量:0x3C8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_BNK_CHG是DDRC所有统计的BANK切换次数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_bnk_chg : 32; /* bit[0-31]: 对指定ID的MASTER BANK切换的命令个数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。
                                                      
                                                      注意：如果要统计所有ID的master,可以通过将sta_id/sta_idmask全部配置为0来实现。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_dmc_bnk_chg_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_dmc_bnk_chg_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_UNION
 结构说明  : DDRC_HIS_RNK_CHG 寄存器结构定义。地址偏移量:0x3CC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RNK_CHG是DDRC所有统计的读写命令片选切换次数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_rnk_chg : 32; /* bit[0-31]: 对指定ID的MASTER 读写命令RANK切换次数统计。在有效统计周期内计数。
                                                      在perf_mode=1 时溢出后维持。
                                                      在perf_mode=0 时溢出后卷绕。
                                                      当下一次统计开始时，清零。
                                                      
                                                      注意：如果要统计所有ID的master,可以通过将sta_id/sta_idmask全部配置为0来实现。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_dmc_rnk_chg_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_dmc_rnk_chg_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RW_CHG_UNION
 结构说明  : DDRC_HIS_RW_CHG 寄存器结构定义。地址偏移量:0x3D0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RW_CHG是DDRC所有统计的读写命令切换次数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_rw_chg : 32; /* bit[0-31]: 对指定ID的MASTER 读写E命令切换次数统计。在有效统计周期内计数。
                                                     在perf_mode=1 时溢出后维持。
                                                     在perf_mode=0 时溢出后卷绕。
                                                     当下一次统计开始时，清零。
                                                     
                                                     注意：如果要统计所有ID的master,可以通过将sta_id/sta_idmask全部配置为0来实现。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RW_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_dmc_rw_chg_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_dmc_rw_chg_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_UNION
 结构说明  : DDRC_HIS_TMON_ERR 寄存器结构定义。地址偏移量:0x3E0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_TMON_ERR是DMC循环读取LPDDR2/LPDDR3温度的错误状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tmon_err      : 8;  /* bit[0-7]  : 从LPDDR2/LPDDR3读取的异常温度值。
                                                         记录第一次错误的值，当温度错误终端清空以后，重新记录下一次异常值。 */
        unsigned int  reserved      : 8;  /* bit[8-15] : 保留。 */
        unsigned int  tmon_err_rank : 16; /* bit[16-31]: 从LPDDR2/LPDDR3读取的异常数据对应的RANK。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_START       (0)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_END         (7)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_rank_START  (16)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_rank_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_UNION
 结构说明  : DDRC_HIS_RERR_ADDRL 寄存器结构定义。地址偏移量:0x3F0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RERR_ADDRL是访问DMC禁止的RANK错误地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rerr_addrl : 32; /* bit[0-31]: 当系统访问的地址指向禁止的rank时（通过disable_rank指定），记录错误地址的低32bit。
                                                     该寄存器不带复位端，写DDRC_HIS_RERR_CNT寄存器清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_rerr_addrl_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_rerr_addrl_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_UNION
 结构说明  : DDRC_HIS_RERR_ADDRH 寄存器结构定义。地址偏移量:0x3F4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RERR_ADDRH是访问DMC禁止的RANK错误地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rerr_addrh : 32; /* bit[0-31]: 当系统访问的地址指向禁止的rank时（通过disable_rank指定），记录错误地址的高位地址。
                                                     该寄存器不带复位端，写DDRC_HIS_RERR_CNT寄存器清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_rerr_addrh_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_rerr_addrh_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RERR_ID_UNION
 结构说明  : DDRC_HIS_RERR_ID 寄存器结构定义。地址偏移量:0x3F8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RERR_ID是访问DMC禁止的RANK错误ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rerr_id   : 31; /* bit[0-30]: 当系统访问的地址指向禁止的rank时（通过disable_rank指定），记录错误操作的ID。
                                                    该寄存器不带复位端，写DDRC_HIS_RERR_CNT寄存器清零。 */
        unsigned int  rerr_type : 1;  /* bit[31]  : 当系统访问的地址指向禁止的rank时（通过disable_rank指定），记录错误操作的burst类型。
                                                    0：读操作；
                                                    1：写操作。
                                                    该寄存器不带复位端，写DDRC_HIS_RERR_CNT寄存器清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_id_START    (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_id_END      (30)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_type_START  (31)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_type_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_UNION
 结构说明  : DDRC_HIS_RERR_CNT 寄存器结构定义。地址偏移量:0x3FC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RERR_CNT是访问DMC禁止的RANK累积错误个数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rerr_cnt : 32; /* bit[0-31]: 当系统访问的地址指向禁止的rank时（通过disable_rank指定），记录错误操作的累积个数。
                                                   该寄存器不带复位端，写DDRC_HIS_RERR_CNT寄存器清零。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_rerr_cnt_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_rerr_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_UNION
 结构说明  : DDRC_HIS_REC_ERR0 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_REC_ERR0是DMC错误恢复过程中错误信息寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crcerr_cnt : 16; /* bit[0-15] : 供发生CRC错误的次数，在crc_en使能时，Alert_n拉低一次的时间小于设定的阈值则判定为一次CRC错误,写DDRC_HIS_REC_ERR0寄存器清零 */
        unsigned int  parerr_cnt : 16; /* bit[16-31]: 共发生CA Parity错误的次数，在parity_en使能时，Alert_n拉低一次的时间超过设定的阈值则判定为一次CA Parity错误,写DDRC_HIS_REC_ERR0寄存器清零 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_crcerr_cnt_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_crcerr_cnt_END    (15)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_parerr_cnt_START  (16)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_parerr_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_UNION
 结构说明  : DDRC_HIS_REC_ERR1 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_REC_ERR0是DMC错误恢复过程中错误信息寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overnum_cnt   : 8;  /* bit[0-7]  : 判定为CRC错误但是错误窗口中没有写命令错误的次数,写DDRC_HIS_REC_ERR1寄存器清零 */
        unsigned int  crc_no_wr_cnt : 8;  /* bit[8-15] : 判定为CRC错误但是错误窗口中没有写命令错误的次数,写DDRC_HIS_REC_ERR1寄存器清零 */
        unsigned int  rec_cnt       : 4;  /* bit[16-19]: 当前恢复过程中共发生的嵌套错误个数 */
        unsigned int  overnum_err   : 1;  /* bit[20]   : 当前恢复过程中是否发生嵌套错误次数超过设定值（嵌套错误指恢复错误过程中又出现了错误，直到恢复错误完成） */
        unsigned int  crc_no_wr     : 1;  /* bit[21]   : 当前恢复过程中发生了判定为CRC错误但是错误窗口中没有写命令错误 */
        unsigned int  reseverd      : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_cnt_START    (0)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_cnt_END      (7)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_cnt_START  (8)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_cnt_END    (15)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_rec_cnt_START        (16)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_rec_cnt_END          (19)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_err_START    (20)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_err_END      (20)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_START      (21)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_END        (21)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_reseverd_START       (22)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_reseverd_END         (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_UNION
 结构说明  : DDRC_HIS_EXMBIST_STATUS 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_EXMBIST_STATUS是EXMBIST模块的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_done      : 1;  /* bit[0]    : 表示EXMBIST的工作状态。
                                                          1 : current execution finished, 
                                                          0 : current execution in progress */
        unsigned int  bist_pass      : 1;  /* bit[1]    : Bist操作是否正确。
                                                          1 : test passes, no errors found, 
                                                          0 : found errors */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  parity_error   : 1;  /* bit[4]    : Parity状态指示。
                                                          1 : parity error detected on the internal FIFOs, 
                                                          0 : no parity error
                                                          Note: for FIFOs that are implemented using flops, as in the cases of SD5883/5890/5815, no parity check logic is instantiated and this bit is tied to 0.  */
        unsigned int  watchdog_error : 1;  /* bit[5]    : watchdog状态指示。
                                                          1 : watchdog error fired, 
                                                          0 : not fired */
        unsigned int  diag_fifo_last : 1;  /* bit[6]    : Diag_fifo的状态指示。
                                                          1 ： have reached the last element in the DIAG FIFO, 
                                                          0 ： not yet */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留。 */
        unsigned int  diag_ip        : 3;  /* bit[8-10] : Instruction # that catches the current fault (saved in the Diag FIFO) */
        unsigned int  reserved_2     : 1;  /* bit[11]   : 保留。 */
        unsigned int  fingerprint    : 4;  /* bit[12-15]: tie to 4’b0101, used for sanity check */
        unsigned int  iter_cnt       : 16; /* bit[16-31]: # of iterations that have been executed, meaningful when cfg_loop_en=1 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_done_START       (0)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_done_END         (0)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_pass_START       (1)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_pass_END         (1)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_parity_error_START    (4)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_parity_error_END      (4)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_watchdog_error_START  (5)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_watchdog_error_END    (5)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_fifo_last_START  (6)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_fifo_last_END    (6)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_ip_START         (8)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_ip_END           (10)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_fingerprint_START     (12)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_fingerprint_END       (15)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_iter_cnt_START        (16)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_iter_cnt_END          (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_UNION
 结构说明  : DDRC_HIS_MTEST_ERR_INFO 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERR_INFO是MTEST错误指示寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err     : 1;  /* bit[0]    : mtest错误指示。
                                                         0：没有错误，
                                                         1：有错误。 */
        unsigned int  reserved_0    : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  mtest_bg_cnt  : 4;  /* bit[4-7]  : 当mtest_err为高时，此域表示发生错误时，正在测试第几组背景数。
                                                         0：第一组背景数；
                                                         1：第一组背景数；
                                                         N：第N组背景数。 */
        unsigned int  mtest_element : 3;  /* bit[8-10] : 当mtest_err为高时，比域表示发生错误时，是在测试的第几步。
                                                         1：第一步；
                                                         2：第二步；
                                                         N：第N步；
                                                         0：保留； */
        unsigned int  reserved_1    : 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_START      (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_END        (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_START   (4)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_END     (7)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_START  (8)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_END    (10)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_UNION
 结构说明  : DDRC_HIS_MTEST_ERRADDR 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_RLATCNT0是Memory Test错误的地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_addr : 28; /* bit[0-27] : mtest错误地址，在mtest Error时候有效。
                                                          实际表示{mtest_err_addr,6'b0}地址开始的64byte数据中有错误。 */
        unsigned int  reserved       : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_END    (27)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA0 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA0是DDR MTEST错误时期望的正确读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data0 : 32; /* bit[0-31]: mtest测试期望数据【31：0】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA1 寄存器结构定义。地址偏移量:0x41C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA1是DDR MTEST多比特错误时期望的正确读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data1 : 32; /* bit[0-31]: mtest测试期望数据【63：32】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA2 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA2是DDR MTEST错误时期望的正确读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data2 : 32; /* bit[0-31]: mtest测试期望数据【95：64】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA3 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA3是DDR MTEST多比特错误时期望的正确读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data3 : 32; /* bit[0-31]: mtest测试期望数据【127：96】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA4 寄存器结构定义。地址偏移量:0x428，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA4是DDR MTEST错误时期望的正确读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data4 : 32; /* bit[0-31]: mtest测试期望数据【159：128】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA5 寄存器结构定义。地址偏移量:0x42C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA5是DDR MTEST多比特错误时期望的正确读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data5 : 32; /* bit[0-31]: mtest测试期望数据【191：160】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA6 寄存器结构定义。地址偏移量:0x430，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA6是DDR MTEST错误时期望的正确读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data6 : 32; /* bit[0-31]: mtest测试期望数据【223：192】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA7 寄存器结构定义。地址偏移量:0x434，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA7是DDR MTEST多比特错误时期望的正确读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data7 : 32; /* bit[0-31]: mtest测试期望数据【255：224】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA8 寄存器结构定义。地址偏移量:0x438，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA8是DDR MTEST错误时期望的正确读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data8 : 32; /* bit[0-31]: mtest测试期望数据【287：256】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA9 寄存器结构定义。地址偏移量:0x43C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA9是DDR MTEST多比特错误时期望的正确读数据9
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data9 : 32; /* bit[0-31]: mtest测试期望数据【319：288】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA10 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA10是DDR MTEST错误时期望的正确读数据10
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data10 : 32; /* bit[0-31]: mtest测试期望数据【351：320】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA11 寄存器结构定义。地址偏移量:0x444，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA11是DDR MTEST多比特错误时期望的正确读数据11
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data11 : 32; /* bit[0-31]: mtest测试期望数据【383：352】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA12 寄存器结构定义。地址偏移量:0x448，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA12是DDR MTEST错误时期望的正确读数据12
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data12 : 32; /* bit[0-31]: mtest测试期望数据【415：384】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA13 寄存器结构定义。地址偏移量:0x44C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA13是DDR MTEST多比特错误时期望的正确读数据13
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data13 : 32; /* bit[0-31]: mtest测试期望数据【447：416】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA14 寄存器结构定义。地址偏移量:0x450，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA14是DDR MTEST错误时期望的正确读数据14
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data14 : 32; /* bit[0-31]: mtest测试期望数据【479：448】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA15 寄存器结构定义。地址偏移量:0x454，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA15是DDR MTEST多比特错误时期望的正确读数据15
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data15 : 32; /* bit[0-31]: mtest测试期望数据【511：480】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA16 寄存器结构定义。地址偏移量:0x458，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA16是DDR MTEST错误时期望的正确读数据16
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data16 : 32; /* bit[0-31]: mtest测试期望数据【543：512】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_UNION
 结构说明  : DDRC_HIS_MTEST_EXPDATA17 寄存器结构定义。地址偏移量:0x45C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_EXPDATA17是DDR MTEST多比特错误时期望的正确读数据17
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_exp_data17 : 32; /* bit[0-31]: mtest测试期望数据【575：544】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA0 寄存器结构定义。地址偏移量:0x460，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA0是DDR MTEST错误时读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data0 : 32; /* bit[0-31]: mtest测试错误数据【31：0】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA1 寄存器结构定义。地址偏移量:0x464，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA1是DDR MTEST错误时读数据1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data1 : 32; /* bit[0-31]: mtest测试错误数据【63：32】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA2 寄存器结构定义。地址偏移量:0x468，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA2是DDR MTEST错误时读数据2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data2 : 32; /* bit[0-31]: mtest测试错误数据【95：64】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA3 寄存器结构定义。地址偏移量:0x46C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA3是DDR MTEST错误时读数据3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data3 : 32; /* bit[0-31]: mtest测试错误数据【127：96】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA4 寄存器结构定义。地址偏移量:0x470，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA4是DDR MTEST错误时读数据4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data4 : 32; /* bit[0-31]: mtest测试错误数据【159：128】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA5 寄存器结构定义。地址偏移量:0x474，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA5是DDR MTEST错误时读数据5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data5 : 32; /* bit[0-31]: mtest测试错误数据【191：160】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA6 寄存器结构定义。地址偏移量:0x478，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA6是DDR MTEST错误时读数据6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data6 : 32; /* bit[0-31]: mtest测试错误数据【223：192】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA7 寄存器结构定义。地址偏移量:0x47C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA7是DDR MTEST错误时读数据7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data7 : 32; /* bit[0-31]: mtest测试错误数据【255：224】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA8 寄存器结构定义。地址偏移量:0x480，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA8是DDR MTEST错误时读数据8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data8 : 32; /* bit[0-31]: mtest测试错误数据【287：256】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA9 寄存器结构定义。地址偏移量:0x484，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA9是DDR MTEST错误时读数据9
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data9 : 32; /* bit[0-31]: mtest测试错误数据【319：288】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA10 寄存器结构定义。地址偏移量:0x488，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA10是DDR MTEST错误时读数据10
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data10 : 32; /* bit[0-31]: mtest测试错误数据【351：320】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA11 寄存器结构定义。地址偏移量:0x48C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA11是DDR MTEST错误时读数据11
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data11 : 32; /* bit[0-31]: mtest测试错误数据【383：352】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA12 寄存器结构定义。地址偏移量:0x490，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA12是DDR MTEST错误时读数据12
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data12 : 32; /* bit[0-31]: mtest测试错误数据【415：384】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA13 寄存器结构定义。地址偏移量:0x494，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA13是DDR MTEST错误时读数据13
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data13 : 32; /* bit[0-31]: mtest测试错误数据【447：416】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA14 寄存器结构定义。地址偏移量:0x498，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA14是DDR MTEST错误时读数据14
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data14 : 32; /* bit[0-31]: mtest测试错误数据【479：448】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA15 寄存器结构定义。地址偏移量:0x49C，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA15是DDR MTEST错误时读数据15
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data15 : 32; /* bit[0-31]: mtest测试错误数据【511：480】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA16 寄存器结构定义。地址偏移量:0x4A0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA16是DDR MTEST错误时读数据16
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data16 : 32; /* bit[0-31]: mtest测试错误数据【543：512】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_UNION
 结构说明  : DDRC_HIS_MTEST_ERRDATA17 寄存器结构定义。地址偏移量:0x4A4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_MTEST_ERRDATA16是DDR MTEST错误时读数据16
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mtest_err_data17 : 32; /* bit[0-31]: mtest测试错误数据【575：544】bit。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_UNION
 结构说明  : DDRC_HIS_SFC_RDATA0 寄存器结构定义。地址偏移量:0x4A8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA0是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata0 : 32; /* bit[0-31]: SFC读数据[31:0]；
                                                 其中[7:0]在RD_MRS模式下为回读LP DDR2 MRS的寄存器值 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_UNION
 结构说明  : DDRC_HIS_SFC_RDATA1 寄存器结构定义。地址偏移量:0x4AC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA1是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata1 : 32; /* bit[0-31]: SFC读数据[63:32]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_UNION
 结构说明  : DDRC_HIS_SFC_RDATA2 寄存器结构定义。地址偏移量:0x4B0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA2是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata2 : 32; /* bit[0-31]: SFC读数据[95:64]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_UNION
 结构说明  : DDRC_HIS_SFC_RDATA3 寄存器结构定义。地址偏移量:0x4B4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA3是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata3 : 32; /* bit[0-31]: SFC读数据[127:96]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_UNION
 结构说明  : DDRC_HIS_SFC_RDATA4 寄存器结构定义。地址偏移量:0x4B8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA4是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata4 : 32; /* bit[0-31]: SFC读数据[159:128]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_UNION
 结构说明  : DDRC_HIS_SFC_RDATA5 寄存器结构定义。地址偏移量:0x4BC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA5是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata5 : 32; /* bit[0-31]: SFC读数据[191:160]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_UNION
 结构说明  : DDRC_HIS_SFC_RDATA6 寄存器结构定义。地址偏移量:0x4C0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA6是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata6 : 32; /* bit[0-31]: SFC读数据[223:192]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_UNION
 结构说明  : DDRC_HIS_SFC_RDATA7 寄存器结构定义。地址偏移量:0x4C4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA7是SFC读数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata7 : 32; /* bit[0-31]: SFC读数据[255:224]。 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_UNION
 结构说明  : DDRC_HIS_SFC_RDATA_ECC 寄存器结构定义。地址偏移量:0x4C8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA_ECC是SFC读数据ECC寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata_ecc0 : 8;  /* bit[0-7]  : SFC读数据[63:0]的8bit ECC数据 */
        unsigned int  rdata_ecc1 : 8;  /* bit[8-15] : SFC读数据[127:64]的8bit ECC数据 */
        unsigned int  rdata_ecc2 : 8;  /* bit[16-23]: SFC读数据[191:128]的8bit ECC数据 */
        unsigned int  rdata_ecc3 : 8;  /* bit[24-31]: SFC读数据[255:192]的8bit ECC数据 */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_END    (7)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_START  (8)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_END    (15)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_START  (16)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_END    (23)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_START  (24)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_UNION
 结构说明  : DDRC_HIS_SFC_RDATA_DBI 寄存器结构定义。地址偏移量:0x4CC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA_DBI是读数据对应的DBI寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata_dbi : 32; /* bit[0-31]: SFC读数据每个Byte对应的DBI信号。
                                                    SFC读数据[7:0]对应rdata_dbi[0];
                                                    SFC读数据[15:8]对应rdata_dbi[1];
                                                    ….
                                                    SFC读数据[255:248]对应rdata_dbi[31];
                                                    
                                                    注意，该寄存器的实际位宽取决于DMC的位宽。比如当DMC为128bit时，该寄存器为16bit. */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_rdata_dbi_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_rdata_dbi_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_UNION
 结构说明  : DDRC_HIS_SFC_RDATA_ECC_DBI 寄存器结构定义。地址偏移量:0x4D0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_HIS_SFC_RDATA_ECC_DBI是读ECC数据对应的DBI寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdata_ecc_dbi : 32; /* bit[0-31]: SFC读数据的ECC每个byte对应的DBI信号。
                                                        SFC读ECC数据[7:0]对应rdata_ecc_dbi[0];
                                                        SFC读ECC数据[15:8]对应rdata_ecc_dbi[1];
                                                        SFC读ECC数据[23:16]对应rdata_ecc_dbi[2];
                                                        SFC读ECC数据[31:24]对应rdata_ecc_dbi[3];
                                                        注意，该寄存器的实际位宽取决于DMC的位宽，比如当DMC为128bit时，该寄存器的位宽为2；当DMC为256bit时，该寄存器为4bit. */
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_rdata_ecc_dbi_START  (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_rdata_ecc_dbi_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT0_UNION
 结构说明  : DDRC_FUNC_STAT0 寄存器结构定义。地址偏移量:0x4D4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT0是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aref_farb_req   : 16; /* bit[0-15] : aref_farb_req的状态信息。
                                                           注意：实际位宽由rank个数决定。 */
        unsigned int  farb_aref_grant : 16; /* bit[16-31]: farb_aref_grant的状态信息。
                                                           注意：实际位宽由rank个数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_aref_farb_req_START    (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_aref_farb_req_END      (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_farb_aref_grant_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_farb_aref_grant_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT1_UNION
 结构说明  : DDRC_FUNC_STAT1 寄存器结构定义。地址偏移量:0x4D8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT1是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aref_farb_bp     : 16; /* bit[0-15] : aref_farb_bp的状态信息。
                                                            注意：实际位宽由rank个数决定。 */
        unsigned int  farb_aref_bpidle : 16; /* bit[16-31]: farb_aref_bpidle的状态信息。
                                                            注意：实际位宽由rank个数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_aref_farb_bp_START      (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_aref_farb_bp_END        (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_farb_aref_bpidle_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_farb_aref_bpidle_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT2_UNION
 结构说明  : DDRC_FUNC_STAT2 寄存器结构定义。地址偏移量:0x4DC，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT2是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_farb_req   : 16; /* bit[0-15] : pd_farb_req的状态信息。
                                                         注意：实际位宽由rank个数决定。 */
        unsigned int  farb_pd_grant : 16; /* bit[16-31]: farb_pd_grant的状态信息。
                                                         注意：实际位宽由rank个数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_pd_farb_req_START    (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_pd_farb_req_END      (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_farb_pd_grant_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_farb_pd_grant_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT3_UNION
 结构说明  : DDRC_FUNC_STAT3 寄存器结构定义。地址偏移量:0x4E0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT3是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_farb_bp     : 16; /* bit[0-15] : pd_farb_bp的状态信息。
                                                          注意：实际位宽由rank个数决定。 */
        unsigned int  farb_pd_bpidle : 16; /* bit[16-31]: farb_pd_bpidle的状态信息。
                                                          注意：实际位宽由rank个数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_pd_farb_bp_START      (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_pd_farb_bp_END        (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_farb_pd_bpidle_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_farb_pd_bpidle_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT4_UNION
 结构说明  : DDRC_FUNC_STAT4 寄存器结构定义。地址偏移量:0x4E4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT4是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_farb_creq   : 16; /* bit[0-15] : pd_farb_creq的状态信息。
                                                          注意：实际位宽由rank个数决定。 */
        unsigned int  aref_farb_creq : 1;  /* bit[16]   : aref_farb_creq的状态信息。 */
        unsigned int  reserved       : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_pd_farb_creq_START    (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_pd_farb_creq_END      (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_aref_farb_creq_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_aref_farb_creq_END    (16)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT5_UNION
 结构说明  : DDRC_FUNC_STAT5 寄存器结构定义。地址偏移量:0x4E8，初值:0x00000001，宽度:32
 寄存器说明: DDRC_FUNC_STAT5是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  farb_cmd_idle    : 1;  /* bit[0]   : farb_cmd_idle的状态信息。 */
        unsigned int  aref_farb_req_ex : 1;  /* bit[1]   : aref_farb_req_ex的状态信息。 */
        unsigned int  farb_aref_ack    : 1;  /* bit[2]   : farb_aref_ack的状态信息。 */
        unsigned int  farb_cbug_grant  : 29; /* bit[3-31]: farb_cbug_grant的状态信息。
                                                           注意：实际位宽由（rank+1）个。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cmd_idle_START     (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cmd_idle_END       (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_aref_farb_req_ex_START  (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_aref_farb_req_ex_END    (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_aref_ack_START     (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_aref_ack_END       (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cbug_grant_START   (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cbug_grant_END     (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT6_UNION
 结构说明  : DDRC_FUNC_STAT6 寄存器结构定义。地址偏移量:0x4EC，初值:0x03000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT6是fun的握手状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sref_farb_req     : 1;  /* bit[0]    : sref_farb_req的状态信息。 */
        unsigned int  farb_sref_grant   : 1;  /* bit[1]    : farb_sref_grant的状态信息。 */
        unsigned int  sref_farb_flush   : 1;  /* bit[2]    : sref_farb_flush的状态信息。 */
        unsigned int  farb_sref_idle    : 1;  /* bit[3]    : farb_sref_idle的状态信息。 */
        unsigned int  sref_farb_creq    : 1;  /* bit[4]    : sref_farb_creq的状态信息。 */
        unsigned int  sfc_farb_req      : 1;  /* bit[5]    : sfc_farb_req的状态信息。 */
        unsigned int  farb_sfc_grant    : 1;  /* bit[6]    : farb_sfc_grant的状态信息。 */
        unsigned int  sfc_farb_bp       : 1;  /* bit[7]    : sfc_farb_bp的状态信息。 */
        unsigned int  farb_sfc_ack      : 1;  /* bit[8]    : farb_sfc_ack的状态信息。 */
        unsigned int  farb_sfc_bpidle   : 1;  /* bit[9]    : farb_sfc_bpidle的状态信息。 */
        unsigned int  sfc_farb_creq     : 1;  /* bit[10]   : sfc_farb_creq的状态信息。 */
        unsigned int  eccwb_farb_req    : 1;  /* bit[11]   : eccwb_farb_req的状态信息。 */
        unsigned int  farb_eccwb_grant  : 1;  /* bit[12]   : farb_eccwb_grant的状态信息。 */
        unsigned int  eccwb_farb_bp     : 1;  /* bit[13]   : eccwb_farb_bp的状态信息。 */
        unsigned int  farb_eccwb_ack    : 1;  /* bit[14]   : farb_eccwb_ack的状态信息。 */
        unsigned int  eccwb_farb_creq   : 1;  /* bit[15]   : eccwb_farb_creq的状态信息。 */
        unsigned int  phyupd_farb_req   : 1;  /* bit[16]   : phyupd_farb_req的状态信息。 */
        unsigned int  farb_phyupd_grant : 1;  /* bit[17]   : farb_phyupd_grant的状态信息。 */
        unsigned int  phyupd_farb_bp    : 1;  /* bit[18]   : phyupd_farb_bp的状态信息。 */
        unsigned int  farb_phyupd_ack   : 1;  /* bit[19]   : farb_phyupd_ack的状态信息。 */
        unsigned int  phyupd_farb_creq  : 1;  /* bit[20]   : phyupd_farb_creq的状态信息。 */
        unsigned int  reserved_0        : 2;  /* bit[21-22]: 保留。 */
        unsigned int  que_func_ack      : 1;  /* bit[23]   : que_func_ack的状态信息。 */
        unsigned int  func_que_flush    : 1;  /* bit[24]   : func_que_flush的状态信息。 */
        unsigned int  que_func_idle     : 1;  /* bit[25]   : que_func_idle的状态信息。 */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_req_START      (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_req_END        (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_grant_START    (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_grant_END      (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_flush_START    (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_flush_END      (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_idle_START     (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_idle_END       (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_creq_START     (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_creq_END       (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_req_START       (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_req_END         (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_grant_START     (6)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_grant_END       (6)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_bp_START        (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_bp_END          (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_ack_START       (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_ack_END         (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_bpidle_START    (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_bpidle_END      (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_creq_START      (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_creq_END        (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_req_START     (11)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_req_END       (11)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_grant_START   (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_grant_END     (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_bp_START      (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_bp_END        (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_ack_START     (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_ack_END       (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_creq_START    (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_creq_END      (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_req_START    (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_req_END      (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_grant_START  (17)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_grant_END    (17)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_bp_START     (18)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_bp_END       (18)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_ack_START    (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_ack_END      (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_creq_START   (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_creq_END     (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_ack_START       (23)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_ack_END         (23)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_func_que_flush_START     (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_func_que_flush_END       (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_idle_START      (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_idle_END        (25)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT7_UNION
 结构说明  : DDRC_FUNC_STAT7 寄存器结构定义。地址偏移量:0x4F0，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT7是fun的子模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_state_rnk0 : 5;  /* bit[0-4]  : pd模块Rank0的状态机 */
        unsigned int  pd_state_rnk1 : 5;  /* bit[5-9]  : pd模块Rank1的状态机 */
        unsigned int  pd_state_rnk2 : 5;  /* bit[10-14]: pd模块Rank2的状态机 */
        unsigned int  pd_state_rnk3 : 5;  /* bit[15-19]: pd模块Rank3的状态机 */
        unsigned int  pd_state_rnk4 : 5;  /* bit[20-24]: pd模块Rank4的状态机 */
        unsigned int  pd_state_rnk5 : 5;  /* bit[25-29]: pd模块Rank5的状态机 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk0_START  (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk0_END    (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk1_START  (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk1_END    (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk2_START  (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk2_END    (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk3_START  (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk3_END    (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk4_START  (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk4_END    (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk5_START  (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk5_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT8_UNION
 结构说明  : DDRC_FUNC_STAT8 寄存器结构定义。地址偏移量:0x4F4，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT8是fun的子模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_state_rnk6  : 5;  /* bit[0-4]  : pd模块Rank6的状态机 */
        unsigned int  pd_state_rnk7  : 5;  /* bit[5-9]  : pd模块Rank7的状态机 */
        unsigned int  pd_state_rnk8  : 5;  /* bit[10-14]: pd模块Rank8的状态机 */
        unsigned int  pd_state_rnk9  : 5;  /* bit[15-19]: pd模块Rank9的状态机 */
        unsigned int  pd_state_rnk10 : 5;  /* bit[20-24]: pd模块Rank10的状态机 */
        unsigned int  pd_state_rnk11 : 5;  /* bit[25-29]: pd模块Rank11的状态机 */
        unsigned int  reserved       : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk6_START   (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk6_END     (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk7_START   (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk7_END     (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk8_START   (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk8_END     (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk9_START   (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk9_END     (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk10_START  (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk10_END    (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk11_START  (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk11_END    (29)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT9_UNION
 结构说明  : DDRC_FUNC_STAT9 寄存器结构定义。地址偏移量:0x4F8，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT9是fun的子模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_state_rnk12 : 5;  /* bit[0-4]  : pd模块Rank12的状态机 */
        unsigned int  pd_state_rnk13 : 5;  /* bit[5-9]  : pd模块Rank13的状态机 */
        unsigned int  pd_state_rnk14 : 5;  /* bit[10-14]: pd模块Rank14的状态机 */
        unsigned int  pd_state_rnk15 : 5;  /* bit[15-19]: pd模块Rank15的状态机 */
        unsigned int  reserved       : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk12_START  (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk12_END    (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk13_START  (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk13_END    (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk14_START  (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk14_END    (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk15_START  (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk15_END    (19)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT10_UNION
 结构说明  : DDRC_FUNC_STAT10 寄存器结构定义。地址偏移量:0x4FC，初值:0x00000050，宽度:32
 寄存器说明: DDRC_FUNC_STAT10是fun的子模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aref_state   : 4;  /* bit[0-3]  : aref模块的状态机 */
        unsigned int  sref_state   : 4;  /* bit[4-7]  : sref模块的状态机 */
        unsigned int  sfc_state    : 5;  /* bit[8-12] : sfc模块的状态机 */
        unsigned int  phyupd_state : 4;  /* bit[13-16]: phyupd模块的状态机 */
        unsigned int  reserved     : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_aref_state_START    (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_aref_state_END      (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sref_state_START    (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sref_state_END      (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sfc_state_START     (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sfc_state_END       (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_phyupd_state_START  (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_phyupd_state_END    (16)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_FUNC_STAT11_UNION
 结构说明  : DDRC_FUNC_STAT11 寄存器结构定义。地址偏移量:0x500，初值:0x00000000，宽度:32
 寄存器说明: DDRC_FUNC_STAT11是fun的子模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_zq_req   : 16; /* bit[0-15] : pd_zq_req的状态信息。
                                                       
                                                       注意：实际位宽由rank数决定。 */
        unsigned int  pd_zq_grant : 16; /* bit[16-31]: pd_zq_grant的状态信息。
                                                       注意：实际位宽由rank数决定。 */
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_req_START    (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_req_END      (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_grant_START  (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_grant_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_STAT12_UNION
 结构说明  : STAT12 寄存器结构定义。地址偏移量:0x504，初值:0x0000000A，宽度:32
 寄存器说明: DDRC_FUNC_STAT11是主通路模块状态机寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sb_fifo_full  : 1;  /* bit[0]   : sb_fifo_full的状态信息。 */
        unsigned int  sb_fifo_empty : 1;  /* bit[1]   : sb_fifo_empty的状态信息。 */
        unsigned int  rp_fifo_full  : 1;  /* bit[2]   : rp_fifo_full的状态信息。 */
        unsigned int  rp_fifo_empty : 1;  /* bit[3]   : rp_fifo_empty的状态信息。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_STAT12_UNION;
#endif
#define SOC_DDRC_DMC_STAT12_sb_fifo_full_START   (0)
#define SOC_DDRC_DMC_STAT12_sb_fifo_full_END     (0)
#define SOC_DDRC_DMC_STAT12_sb_fifo_empty_START  (1)
#define SOC_DDRC_DMC_STAT12_sb_fifo_empty_END    (1)
#define SOC_DDRC_DMC_STAT12_rp_fifo_full_START   (2)
#define SOC_DDRC_DMC_STAT12_rp_fifo_full_END     (2)
#define SOC_DDRC_DMC_STAT12_rp_fifo_empty_START  (3)
#define SOC_DDRC_DMC_STAT12_rp_fifo_empty_END    (3)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_UNION
 结构说明  : DDRC_TEST_RAM_TMOD 寄存器结构定义。地址偏移量:0x508，初值:0x000001A8，宽度:32
 寄存器说明: DDRC_TEST_TMOD是DDR 中RAM的测试模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_tmod : 32; /* bit[0-31]: 该寄存器由宏定义配置决定其值。 */
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_START  (0)
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_UNION
 结构说明  : DDRC_TEST_RTL_CFG0 寄存器结构定义。地址偏移量:0x510，初值:0x10470520，宽度:32
 寄存器说明: DDRC_TEST_RTL_CFG0是DDRC RTL参数信息寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mddrc_dmc_version : 16; /* bit[0-15] : DMC版本号。
                                                             'h0520：表示HiMDDRCV520版本 */
        unsigned int  mddrc_dmc_width   : 4;  /* bit[16-19]: DMC数据通路位宽。
                                                             0:1位；
                                                             1:2位；
                                                             2:4位；
                                                             3:8位；
                                                             4:16位；
                                                             5:32位；
                                                             6:64位；
                                                             7:128位；
                                                             8:256位；
                                                             9:512位；
                                                             其他：保留。 */
        unsigned int  mddrc_ecc_width   : 4;  /* bit[20-23]: DMC ECC数据位宽。
                                                             0:1位；
                                                             1:2位；
                                                             2:4位；
                                                             3:8位；
                                                             4:16位；
                                                             5:32位；
                                                             6:64位；
                                                             其他：保留。 */
        unsigned int  mddrc_cfifo_num   : 8;  /* bit[24-31]: DMC命令BUF个数。 */
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_version_START  (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_version_END    (15)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_width_START    (16)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_width_END      (19)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_ecc_width_START    (20)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_ecc_width_END      (23)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_cfifo_num_START    (24)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_cfifo_num_END      (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_UNION
 结构说明  : DDRC_TEST_RTL_CFG1 寄存器结构定义。地址偏移量:0x514，初值:0x00100601，宽度:32
 寄存器说明: DDRC_TEST_RTL_CFG1是DDRC RTL参数信息寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mddrc_rank_num     : 4;  /* bit[0-3]  : DMC支持的最大RANK数。
                                                              0~0xf：n+1个RANK。 */
        unsigned int  mddrc_addr_width   : 4;  /* bit[4-7]  : DMC地址总线位宽。
                                                              0~0xf：n+32位。 */
        unsigned int  mddrc_phy_type     : 8;  /* bit[8-15] : 对接的DDRPHY类型。
                                                              0：保留；
                                                              1：SNPS 40LP multiPHY；
                                                              2：SNPS 40LP/28HPM 32PHY/G2 MULTIPHY；
                                                              3：HISI S40LL TWPHY；
                                                              4：保留；
                                                              5：IBM 45GS 21GPHY；
                                                              6：HISI 28HPM TWPHY；
                                                              7：CDNS 28HPM HSPHY；
                                                              8：SNPS 28HPM DDR4 multiPHY；
                                                              其他：保留。 */
        unsigned int  mddrc_bank_xor_pos : 5;  /* bit[16-20]: BANK加扰起始地址。 */
        unsigned int  reserved_0         : 3;  /* bit[21-23]: 保留。 */
        unsigned int  mddrc_mbist_type   : 2;  /* bit[24-25]: DMC内部集成的MBIST模块类型。
                                                              0：无MBIST；
                                                              1：MarchIC MBIST；
                                                              2：OLMBIST 可编程MBIST模块；
                                                              其他：保留。 */
        unsigned int  reserved_1         : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_rank_num_START      (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_rank_num_END        (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_addr_width_START    (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_addr_width_END      (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_phy_type_START      (8)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_phy_type_END        (15)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_bank_xor_pos_START  (16)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_bank_xor_pos_END    (20)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_mbist_type_START    (24)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_mbist_type_END      (25)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_UNION
 结构说明  : DDRC_TEST_RTL_CFG2 寄存器结构定义。地址偏移量:0x518，初值:0x00000500，宽度:32
 寄存器说明: DDRC_TEST_RTL_CFG2是DDRC RTL参数信息寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mddrc_rlast_en     : 1;  /* bit[0]    : DMC RLAST_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_ffbyp_en     : 1;  /* bit[1]    : DMC FFBYP_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_phy_in_flop  : 1;  /* bit[2]    : DMC PHY_IN_FLOP使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_ecc_en       : 1;  /* bit[3]    : DMC ECC_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_debug_bus    : 1;  /* bit[4]    : DMC DEBUG_BUS使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_crc_pipe_en  : 1;  /* bit[5]    : DMC CRC_PIPE_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_ram_ecc_en   : 1;  /* bit[6]    : DMC RAM_ECC_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_rec_en       : 1;  /* bit[7]    : DMC REC_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  mddrc_hdr_mode     : 2;  /* bit[8-9]  : DMC DFI接口模式。
                                                              0：SDR模式；
                                                              1：SDR/HDR模式。
                                                              其他：保留。 */
        unsigned int  mddrc_dasw_pipe_en : 1;  /* bit[10]   : DMC DASW_PIPE_EN使能。
                                                              0：禁止；
                                                              1：使能。 */
        unsigned int  reserved           : 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rlast_en_START      (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rlast_en_END        (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ffbyp_en_START      (1)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ffbyp_en_END        (1)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_phy_in_flop_START   (2)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_phy_in_flop_END     (2)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ecc_en_START        (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ecc_en_END          (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_debug_bus_START     (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_debug_bus_END       (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_crc_pipe_en_START   (5)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_crc_pipe_en_END     (5)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ram_ecc_en_START    (6)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ram_ecc_en_END      (6)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rec_en_START        (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rec_en_END          (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_hdr_mode_START      (8)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_hdr_mode_END        (9)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_dasw_pipe_en_START  (10)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_dasw_pipe_en_END    (10)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_OSC_COUNT_UNION
 结构说明  : DDRC_OSC_COUNT 寄存器结构定义。地址偏移量:0x520+0x4*(rnks)，初值:0x00000000，宽度:32
 寄存器说明: DDRC_OSC_COUNT是Oscillator回读的值及基准寄存器的值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  osc_count      : 16; /* bit[0-15] : Osc的值，dmc会在初始化完成后自动从器件中读取，在update时也会自动更新 */
        unsigned int  osc_count_base : 16; /* bit[16-31]: 基准寄存器，用于保证每次update后的osc的值，软件也可以改写。 */
    } reg;
} SOC_DDRC_DMC_DDRC_OSC_COUNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_START       (0)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_END         (15)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_base_START  (16)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_base_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_EDXN_DQMAP_UNION
 结构说明  : DDRC_EDXN_DQMAP 寄存器结构定义。地址偏移量:0x580+0x8*(blanes)，初值:0x76543210，宽度:32
 寄存器说明: DDRC_EDXN_DQMAP是偶数rank的DQ MAP寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edxn_dq0_map : 3;  /* bit[0-2]  : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_0   : 1;  /* bit[3]    : 保留。 */
        unsigned int  edxn_dq1_map : 3;  /* bit[4-6]  : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_1   : 1;  /* bit[7]    : 保留。 */
        unsigned int  edxn_dq2_map : 3;  /* bit[8-10] : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_2   : 1;  /* bit[11]   : 保留。 */
        unsigned int  edxn_dq3_map : 3;  /* bit[12-14]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_3   : 1;  /* bit[15]   : 保留。 */
        unsigned int  edxn_dq4_map : 3;  /* bit[16-18]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_4   : 1;  /* bit[19]   : 保留。 */
        unsigned int  edxn_dq5_map : 3;  /* bit[20-22]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_5   : 1;  /* bit[23]   : 保留。 */
        unsigned int  edxn_dq6_map : 3;  /* bit[24-26]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_6   : 1;  /* bit[27]   : 保留。 */
        unsigned int  edxn_dq7_map : 3;  /* bit[28-30]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_7   : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_EDXN_DQMAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq0_map_START  (0)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq0_map_END    (2)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq1_map_START  (4)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq1_map_END    (6)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq2_map_START  (8)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq2_map_END    (10)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq3_map_START  (12)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq3_map_END    (14)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq4_map_START  (16)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq4_map_END    (18)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq5_map_START  (20)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq5_map_END    (22)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq6_map_START  (24)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq6_map_END    (26)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq7_map_START  (28)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq7_map_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_DMC_DDRC_ODXN_DQMAP_UNION
 结构说明  : DDRC_ODXN_DQMAP 寄存器结构定义。地址偏移量:0x584+0x8*(blanes)，初值:0x76543210，宽度:32
 寄存器说明: DDRC_ODXN_DQMAP是奇数rank的DQ MAP寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odxn_dq0_map : 3;  /* bit[0-2]  : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_0   : 1;  /* bit[3]    : 保留。 */
        unsigned int  odxn_dq1_map : 3;  /* bit[4-6]  : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_1   : 1;  /* bit[7]    : 保留。 */
        unsigned int  odxn_dq2_map : 3;  /* bit[8-10] : 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_2   : 1;  /* bit[11]   : 保留。 */
        unsigned int  odxn_dq3_map : 3;  /* bit[12-14]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_3   : 1;  /* bit[15]   : 保留。 */
        unsigned int  odxn_dq4_map : 3;  /* bit[16-18]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_4   : 1;  /* bit[19]   : 保留。 */
        unsigned int  odxn_dq5_map : 3;  /* bit[20-22]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_5   : 1;  /* bit[23]   : 保留。 */
        unsigned int  odxn_dq6_map : 3;  /* bit[24-26]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_6   : 1;  /* bit[27]   : 保留。 */
        unsigned int  odxn_dq7_map : 3;  /* bit[28-30]: 器件DQ对应控制器的位置，注意：使能CRC时必须按照实际的映射关系配置，配置时以器件端为基准
                                                        0： dq0
                                                        1： dq1
                                                        2: dq2
                                                        3: dq3
                                                        4: dq4
                                                        5: dq5
                                                        6： dq6
                                                        7： dq7 */
        unsigned int  reserved_7   : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_DMC_DDRC_ODXN_DQMAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq0_map_START  (0)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq0_map_END    (2)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq1_map_START  (4)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq1_map_END    (6)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq2_map_START  (8)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq2_map_END    (10)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq3_map_START  (12)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq3_map_END    (14)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq4_map_START  (16)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq4_map_END    (18)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq5_map_START  (20)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq5_map_END    (22)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq6_map_START  (24)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq6_map_END    (26)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq7_map_START  (28)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq7_map_END    (30)






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

#endif /* end of soc_ddrc_dmc_interface.h */
