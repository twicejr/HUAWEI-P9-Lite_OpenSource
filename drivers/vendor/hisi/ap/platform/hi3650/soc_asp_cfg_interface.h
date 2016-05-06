/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asp_cfg_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:05
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASP_CFG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_CFG_INTERFACE_H__
#define __SOC_ASP_CFG_INTERFACE_H__

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
/* 寄存器说明：外设软复位使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_RST_CTRLEN_UNION */
#define SOC_ASP_CFG_R_RST_CTRLEN_ADDR(base)           ((base) + (0x0000))

/* 寄存器说明：外设软复位撤离寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_RST_CTRLDIS_UNION */
#define SOC_ASP_CFG_R_RST_CTRLDIS_ADDR(base)          ((base) + (0x0004))

/* 寄存器说明：外设软复位状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_RST_CTRLSTAT_UNION */
#define SOC_ASP_CFG_R_RST_CTRLSTAT_ADDR(base)         ((base) + (0x0008))

/* 寄存器说明：时钟使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_GATE_EN_UNION */
#define SOC_ASP_CFG_R_GATE_EN_ADDR(base)              ((base) + (0x000C))

/* 寄存器说明：时钟禁止寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_GATE_DIS_UNION */
#define SOC_ASP_CFG_R_GATE_DIS_ADDR(base)             ((base) + (0x0010))

/* 寄存器说明：时钟使能状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_GATE_CLKEN_UNION */
#define SOC_ASP_CFG_R_GATE_CLKEN_ADDR(base)           ((base) + (0x0014))

/* 寄存器说明：时钟最终状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_GATE_CLKSTAT_UNION */
#define SOC_ASP_CFG_R_GATE_CLKSTAT_ADDR(base)         ((base) + (0x0018))

/* 寄存器说明：时钟分频器门控使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION */
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_ADDR(base)       ((base) + (0x001C))

/* 寄存器说明：分频比控制寄存器1
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK1_DIV_UNION */
#define SOC_ASP_CFG_R_CLK1_DIV_ADDR(base)             ((base) + (0x0020))

/* 寄存器说明：分频比控制寄存器2
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK2_DIV_UNION */
#define SOC_ASP_CFG_R_CLK2_DIV_ADDR(base)             ((base) + (0x0024))

/* 寄存器说明：分频比控制寄存器3
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK3_DIV_UNION */
#define SOC_ASP_CFG_R_CLK3_DIV_ADDR(base)             ((base) + (0x0028))

/* 寄存器说明：分频比控制寄存器4
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK4_DIV_UNION */
#define SOC_ASP_CFG_R_CLK4_DIV_ADDR(base)             ((base) + (0x002C))

/* 寄存器说明：分频比控制寄存器5
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK5_DIV_UNION */
#define SOC_ASP_CFG_R_CLK5_DIV_ADDR(base)             ((base) + (0x0030))

/* 寄存器说明：分频比控制寄存器6
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK6_DIV_UNION */
#define SOC_ASP_CFG_R_CLK6_DIV_ADDR(base)             ((base) + (0x0034))

/* 寄存器说明：时钟选择寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK_SEL_UNION */
#define SOC_ASP_CFG_R_CLK_SEL_ADDR(base)              ((base) + (0x0038))

/* 寄存器说明：DSP NMI中断产生寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_NMI_UNION */
#define SOC_ASP_CFG_R_DSP_NMI_ADDR(base)              ((base) + (0x003C))

/* 寄存器说明：DSP PRID设置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_PRID_UNION */
#define SOC_ASP_CFG_R_DSP_PRID_ADDR(base)             ((base) + (0x0040))

/* 寄存器说明：DSP RUNSTALL设置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_RUNSTALL_UNION */
#define SOC_ASP_CFG_R_DSP_RUNSTALL_ADDR(base)         ((base) + (0x0044))

/* 寄存器说明：DSP STATVECTORSEL设置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION */
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_ADDR(base)    ((base) + (0x0048))

/* 寄存器说明：DSP OCDHALTONRESET设置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION */
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_ADDR(base)   ((base) + (0x004C))

/* 寄存器说明：DSP 状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_STATUS_UNION */
#define SOC_ASP_CFG_R_DSP_STATUS_ADDR(base)           ((base) + (0x0050))

/* 寄存器说明：DMAC通道选择寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DMAC_SEL_UNION */
#define SOC_ASP_CFG_R_DMAC_SEL_ADDR(base)             ((base) + (0x0054))

/* 寄存器说明：总线优先级配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_BUS_PRIORITY_UNION */
#define SOC_ASP_CFG_R_BUS_PRIORITY_ADDR(base)         ((base) + (0x0058))

/* 寄存器说明：自动门控使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_CG_EN_UNION */
#define SOC_ASP_CFG_R_CG_EN_ADDR(base)                ((base) + (0x005C))

/* 寄存器说明：ocram低功耗配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_OCRAM_RET_UNION */
#define SOC_ASP_CFG_R_OCRAM_RET_ADDR(base)            ((base) + (0x0060))

/* 寄存器说明：非安全中断原始状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_NS_INI_UNION */
#define SOC_ASP_CFG_R_INTR_NS_INI_ADDR(base)          ((base) + (0x0064))

/* 寄存器说明：非安全中断使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_NS_EN_UNION */
#define SOC_ASP_CFG_R_INTR_NS_EN_ADDR(base)           ((base) + (0x0068))

/* 寄存器说明：非安全中断屏蔽后状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_NS_MASK_UNION */
#define SOC_ASP_CFG_R_INTR_NS_MASK_ADDR(base)         ((base) + (0x006C))

/* 寄存器说明：付强桥DBG信号设置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION */
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_ADDR(base)      ((base) + (0x0070))

/* 寄存器说明：付强桥DBG信号状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION */
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_ADDR(base)   ((base) + (0x0074))

/* 寄存器说明：总线防挂死bypass寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DLOCK_BP_UNION */
#define SOC_ASP_CFG_R_DLOCK_BP_ADDR(base)             ((base) + (0x0078))

/* 寄存器说明：上报到hifi dsp的中断信号只读寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION */
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ADDR(base)       ((base) + (0x007C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_RAM_RET_UNION */
#define SOC_ASP_CFG_R_DSP_RAM_RET_ADDR(base)          ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_CFG_R_TZ_SECURE_N_UNION */
#define SOC_ASP_CFG_R_TZ_SECURE_N_ADDR(base)          ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION */
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ADDR(base)         ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION */
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_ADDR(base)    ((base) + (0x0108))

/* 寄存器说明：安全中断原始状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_S_INI_UNION */
#define SOC_ASP_CFG_R_INTR_S_INI_ADDR(base)           ((base) + (0x010C))

/* 寄存器说明：安全中断使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_S_EN_UNION */
#define SOC_ASP_CFG_R_INTR_S_EN_ADDR(base)            ((base) + (0x0110))

/* 寄存器说明：安全中断屏蔽后状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_S_MASK_UNION */
#define SOC_ASP_CFG_R_INTR_S_MASK_ADDR(base)          ((base) + (0x0114))

/* 寄存器说明：dsp地址重映射使能寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_ADDR(base)     ((base) + (0x0118))

/* 寄存器说明：DSP 地址重映射寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_ADDR(base) ((base) + (0x011C))

/* 寄存器说明：DSP 地址重映射寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ADDR(base) ((base) + (0x0120))

/* 寄存器说明：DDR与Harq Memory remap控制寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_ADDR(base)    ((base) + (0x124))

/* 寄存器说明：DDR与Harq Memory remap源基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x128))

/* 寄存器说明：DDR与Harq Memory remap目标基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x12C))

/* 寄存器说明：DDR与MMBUF remap控制寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_ADDR(base)   ((base) + (0x130))

/* 寄存器说明：DDR与MMBUF remap源基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x134))

/* 寄存器说明：DDR与MMBUF remap目标基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x138))

/* 寄存器说明：DDR与OCRAM remap控制寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_ADDR(base)   ((base) + (0x13C))

/* 寄存器说明：DDR与OCRAM remap源基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x140))

/* 寄存器说明：DDR与OCRAM remap目标基地址寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x144))

/* 寄存器说明：MMBUF CTRL配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_MMBUF_CTRL_UNION */
#define SOC_ASP_CFG_R_MMBUF_CTRL_ADDR(base)           ((base) + (0x0148))

/* 寄存器说明：HIFIDSP时钟频率自动调频配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION */
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_ADDR(base) ((base) + (0x014C))

/* 寄存器说明：频偏记录模块配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION */
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_ADDR(base) ((base) + (0x0150))

/* 寄存器说明：内存监控模块使能配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_ADDR(base) ((base) + (0x0160))

/* 寄存器说明：内存监控模块中断清零配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_ADDR(base) ((base) + (0x0164))

/* 寄存器说明：内存监控模块中断使能配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_ADDR(base) ((base) + (0x0168))

/* 寄存器说明：内存监控模块中断状态寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_ADDR(base) ((base) + (0x016C))

/* 寄存器说明：内存监控模块0基地址配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_ADDR(base) ((base) + (0x0170))

/* 寄存器说明：内存监控模块0地址长度配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_ADDR(base) ((base) + (0x0174))

/* 寄存器说明：内存监控模块0越界的写地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_ADDR(base) ((base) + (0x0178))

/* 寄存器说明：内存监控模块0越界的读地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_ADDR(base) ((base) + (0x017C))

/* 寄存器说明：内存监控模块1基地址配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_ADDR(base) ((base) + (0x0180))

/* 寄存器说明：内存监控模块1地址长度配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：内存监控模块1越界的写地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_ADDR(base) ((base) + (0x0188))

/* 寄存器说明：内存监控模块1越界的读地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_ADDR(base) ((base) + (0x018C))

/* 寄存器说明：内存监控模块2基地址配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_ADDR(base) ((base) + (0x0190))

/* 寄存器说明：内存监控模块2地址长度配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_ADDR(base) ((base) + (0x0194))

/* 寄存器说明：内存监控模块2越界的写地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_ADDR(base) ((base) + (0x0198))

/* 寄存器说明：内存监控模块2越界的读地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_ADDR(base) ((base) + (0x019C))

/* 寄存器说明：内存监控模块3基地址配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_ADDR(base) ((base) + (0x01A0))

/* 寄存器说明：内存监控模块3地址长度配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_ADDR(base) ((base) + (0x01A4))

/* 寄存器说明：内存监控模块3越界的写地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_ADDR(base) ((base) + (0x01A8))

/* 寄存器说明：内存监控模块3越界的读地址记录寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_ADDR(base) ((base) + (0x01AC))

/* 寄存器说明：memory控制配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_MEMORY_CTRL_UNION */
#define SOC_ASP_CFG_R_MEMORY_CTRL_ADDR(base)          ((base) + (0x01B0))

/* 寄存器说明：slimbus primary配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION */
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_ADDR(base) ((base) + (0x01B4))

/* 寄存器说明：slimbus id配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION */
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_ADDR(base)      ((base) + (0x01B8))

/* 寄存器说明：slimbus数据格式配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION */
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_ADDR(base)     ((base) + (0x01BC))

/* 寄存器说明：slimbus数据通道配置寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION */
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_ADDR(base)    ((base) + (0x01C0))

/* 寄存器说明：分频比控制寄存器0
   位域定义UNION结构:  SOC_ASP_CFG_R_CLK0_DIV_UNION */
#define SOC_ASP_CFG_R_CLK0_DIV_ADDR(base)             ((base) + (0x01D0))

/* 寄存器说明：安全访问属性控制寄存器
   位域定义UNION结构:  SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION */
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_ADDR(base)  ((base) + (0x0200))





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
 结构名    : SOC_ASP_CFG_R_RST_CTRLEN_UNION
 结构说明  : R_RST_CTRLEN 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio_n     : 1;  /* bit[0]    : sio_audio模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voice模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_bt模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modem模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dsp模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dsp模块的debug软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipc模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmi模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmac模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocram模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dog模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbus模块base时钟域软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbus模块总线时钟域软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : 付强桥h2x模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpio模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1模块软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB接口软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG接口软复位使能：
                                                               0：软复位使能状态不变；
                                                               1：软复位使能。 */
        unsigned int  reserved_2          : 1;  /* bit[21]   : 保留 */
        unsigned int  reserved_3          : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLEN_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_audio_n_START      (0)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_audio_n_END        (0)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_RST_CTRLDIS_UNION
 结构说明  : R_RST_CTRLDIS 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio       : 1;  /* bit[0]    : sio_audio模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voice模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_bt模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modem模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dsp模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dsp模块的debug软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipc模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmi模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmac模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocram模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dog模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbus模块base时钟域软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbus模块总线时钟域软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : 付强桥h2x模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpio模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1模块软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB接口软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG接口软复位撤离：
                                                               0：软复位使能状态不变；
                                                               1：软复位撤离。 */
        unsigned int  reserved_2          : 1;  /* bit[21]   : 保留 */
        unsigned int  reserved_3          : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLDIS_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_audio_START        (0)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_audio_END          (0)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_RST_CTRLSTAT_UNION
 结构说明  : R_RST_CTRLSTAT 寄存器结构定义。地址偏移量:0x0008，初值:0x001FFFFF，宽度:32
 寄存器说明: 外设软复位状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio_n     : 1;  /* bit[0]    : sio_audio模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voice模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_bt模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modem模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dsp模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dsp模块的debug软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipc模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmi模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmac模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocram模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dog模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbus模块base时钟域软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbus模块总线时钟域软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : 付强桥h2x模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpio模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1模块软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB接口软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG接口软复位使能状态：
                                                               0：软复位使能撤销；
                                                               1：软复位使能。 */
        unsigned int  reserved_2          : 1;  /* bit[21]   : 保留 */
        unsigned int  reserved_3          : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLSTAT_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_audio_n_START      (0)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_audio_n_END        (0)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_GATE_EN_UNION
 结构说明  : R_GATE_EN 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 时钟使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dsp时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk输出时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audio时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk输出时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voice时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk输出时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_bt时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk输出时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modem时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipc时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmac时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocram时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dog时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmi模块spdifclk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmi模块bclk时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpio时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : 送给AOCRG的硬线控制信号，控制送给audio_subsys做slimbus时钟分频的clk_ppll0时钟门控：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_EN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_EN_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_EN_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_EN_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_EN_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_EN_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_EN_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_EN_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_EN_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_EN_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_EN_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_EN_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_EN_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_EN_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_EN_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_EN_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_EN_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_EN_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_EN_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_EN_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_EN_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_EN_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_EN_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_EN_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_EN_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_EN_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_EN_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_EN_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_EN_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_EN_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_EN_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_EN_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_EN_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_GATE_DIS_UNION
 结构说明  : R_GATE_DIS 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 时钟禁止寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dsp时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk输出时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audio时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk输出时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voice时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk输出时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_bt时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk输出时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modem时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipc时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmac时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocram时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dog时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmi模块spdifclk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmi模块bclk时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpio时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : 送给AOCRG的硬线控制信号，控制送给audio_subsys做slimbus时钟分频的clk_ppll0时钟门控：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_DIS_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_DIS_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_DIS_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_DIS_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_DIS_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_DIS_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_DIS_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_DIS_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_DIS_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_DIS_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_DIS_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_DIS_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_DIS_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_DIS_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_DIS_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_DIS_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_DIS_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_DIS_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_DIS_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_DIS_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_DIS_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_DIS_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_GATE_CLKEN_UNION
 结构说明  : R_GATE_CLKEN 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 时钟使能状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dsp时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk输出时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audio时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk输出时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voice时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk输出时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_bt时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk输出时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modem时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipc时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmac时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocram时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dog时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmi模块spdifclk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmi模块bclk时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpio时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : 送给AOCRG的硬线控制信号，控制送给audio_subsys做slimbus时钟分频的clk_ppll0时钟门控：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKEN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_GATE_CLKSTAT_UNION
 结构说明  : R_GATE_CLKSTAT 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 时钟最终状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_hifidspclk       : 1;  /* bit[0] : dsp时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_audiobclk_out    : 1;  /* bit[1] : sio_audio bclk输出时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_audiobclk        : 1;  /* bit[2] : sio_audio bclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_voicebclk_out    : 1;  /* bit[3] : sio_voice bclk输出时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_siovoice         : 1;  /* bit[4] : sio_voice bclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_btbclk_out       : 1;  /* bit[5] : sio_bt bclk输出时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_siobt            : 1;  /* bit[6] : sio_bt bclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_modembclk_out    : 1;  /* bit[7] : sio_modem bclk输出时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_siomodem         : 1;  /* bit[8] : sio_modem bclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_ipchclk          : 1;  /* bit[9] : ipc时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_hdmihclk         : 1;  /* bit[10]: asp_hdmi hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_dmachclk0        : 1;  /* bit[11]: asp_dmac hclk0时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_dmachclk1        : 1;  /* bit[12]: asp_dmac hclk1时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  reserved_0          : 1;  /* bit[13]:  */
        unsigned int  reserved_1          : 1;  /* bit[14]:  */
        unsigned int  st_ocramhclk        : 1;  /* bit[15]: ocram时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_wdhclk           : 1;  /* bit[16]: watch dog时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_slimbushclk      : 1;  /* bit[17]: slimbus hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_slimbus_base_clk : 1;  /* bit[18]: slimbus base clk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_hdmimclk         : 1;  /* bit[19]: hdmi mclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_spdifclk         : 1;  /* bit[20]: asp_hdmi模块spdifclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_hdmiref          : 1;  /* bit[21]: asp_hdmi模块refclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_asp_h2x          : 1;  /* bit[22]: 付强桥h2x时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_audiohclk        : 1;  /* bit[23]: sio_audio hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_voicehclk        : 1;  /* bit[24]: sio_voice hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_bthclk           : 1;  /* bit[25]: sio_bt hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_modemhclk        : 1;  /* bit[26]: sio_modem hclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_gpiohclk         : 1;  /* bit[27]: gpio时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_timer0hclk       : 1;  /* bit[28]: timer0时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_timer1hclk       : 1;  /* bit[29]: timer1时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  st_hdmibclk         : 1;  /* bit[30]: hdmi bclk时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  reserved_2          : 1;  /* bit[31]: 整个寄存器的复位值由asp_cfg的输入时钟最终状态信号的复位值来定。 */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKSTAT_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hifidspclk_START        (0)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hifidspclk_END          (0)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_out_START     (1)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_out_END       (1)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_START         (2)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_END           (2)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_voicebclk_out_START     (3)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_voicebclk_out_END       (3)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siovoice_START          (4)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siovoice_END            (4)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_btbclk_out_START        (5)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_btbclk_out_END          (5)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siobt_START             (6)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siobt_END               (6)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_modembclk_out_START     (7)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_modembclk_out_END       (7)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siomodem_START          (8)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siomodem_END            (8)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ipchclk_START           (9)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ipchclk_END             (9)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmihclk_START          (10)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmihclk_END            (10)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk0_START         (11)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk0_END           (11)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk1_START         (12)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk1_END           (12)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ocramhclk_START         (15)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ocramhclk_END           (15)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_wdhclk_START            (16)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_wdhclk_END              (16)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbushclk_START       (17)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbushclk_END         (17)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbus_base_clk_START  (18)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbus_base_clk_END    (18)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmimclk_START          (19)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmimclk_END            (19)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_spdifclk_START          (20)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_spdifclk_END            (20)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmiref_START           (21)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmiref_END             (21)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_asp_h2x_START           (22)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_asp_h2x_END             (22)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiohclk_START         (23)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiohclk_END           (23)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_voicehclk_START         (24)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_voicehclk_END           (24)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_bthclk_START            (25)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_bthclk_END              (25)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_modemhclk_START         (26)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_modemhclk_END           (26)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_gpiohclk_START          (27)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_gpiohclk_END            (27)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer0hclk_START        (28)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer0hclk_END          (28)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer1hclk_START        (29)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer1hclk_END          (29)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmibclk_START          (30)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmibclk_END            (30)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION
 结构说明  : R_GATE_CLKDIV_EN 寄存器结构定义。地址偏移量:0x001C，初值:0x000001FF，宽度:32
 寄存器说明: 时钟分频器门控使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hdmimclk_div       : 1;  /* bit[0]   : hdmi mclk小数分频器时钟使能（小数分频器请参见R_CLK2_DIV寄存器的说明）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果要让asp_hdmi工作（无论是spdif输出还是多声道i2s输出），则需要使能此时钟。 */
        unsigned int  gt_hdmiref_div        : 1;  /* bit[1]   : hdmi refclk 2分频器时钟使能：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果要让asp_hdmi在多声道i2s输出情况下工作，则需要使能此时钟。 */
        unsigned int  gt_siobclk_div        : 1;  /* bit[2]   : 小数分频器siobclk_div的输入时钟使能（小数分频器请参见R_CLK1_DIV寄存器的说明）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果要让sio_audio、sio_voice、sio_bt、sio_modem中的任意一个在master模式下工作，则需要使能此时钟；
                                                                如果要让slimbus base clk选择小数分频器siobclk_div的输出时钟，则需要使能此寄存器。 */
        unsigned int  gt_sio_audio_bclk_div : 1;  /* bit[3]   : sio_audio bclk 整数分频器时钟使能（整数分频器请参见R_CLK3_DIV寄存器的div_sio_audio_bclk位）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果需要让sio_audio在master模式下工作，则需要使能此时钟。 */
        unsigned int  gt_sio_voice_bclk_div : 1;  /* bit[4]   : sio_voice bclk 整数分频器时钟使能（整数分频器请参见R_CLK3_DIV寄存器的div_sio_audio_bclk位）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果需要让sio_audio在master模式下工作，则需要使能此时钟。 */
        unsigned int  gt_sio_bt_bclk_div    : 1;  /* bit[5]   : sio_bt bclk 整数分频器时钟使能（整数分频器请参见R_CLK3_DIV寄存器的div_sio_audio_bclk位）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果需要让sio_audio在master模式下工作，则需要使能此时钟。 */
        unsigned int  gt_sio_modem_bclk_div : 1;  /* bit[6]   : sio_modem bclk 整数分频器时钟使能（整数分频器请参见R_CLK3_DIV寄存器的div_sio_audio_bclk位）：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果需要让sio_audio在master模式下工作，则需要使能此时钟。 */
        unsigned int  gt_asp_tcxo_div       : 1;  /* bit[7]   : 晶振19.2M时钟的固定4分频器时钟使能：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果要让asp的timer在4.8M频率下工作，则需要使能此时钟。 */
        unsigned int  gt_slimbus_clk_div    : 1;  /* bit[8]   : ppll0小数分频器时钟使能：
                                                                0：IP时钟禁止；
                                                                1：IP时钟使能。
                                                                如果要让asp的slimbus时钟从ppll0小数分频得到，则需要使能此时钟。 */
        unsigned int  reserved              : 23; /* bit[9-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmimclk_div_START        (0)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmimclk_div_END          (0)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmiref_div_START         (1)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmiref_div_END           (1)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_siobclk_div_START         (2)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_siobclk_div_END           (2)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_audio_bclk_div_START  (3)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_audio_bclk_div_END    (3)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_voice_bclk_div_START  (4)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_voice_bclk_div_END    (4)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_bt_bclk_div_START     (5)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_bt_bclk_div_END       (5)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_modem_bclk_div_START  (6)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_modem_bclk_div_END    (6)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_asp_tcxo_div_START        (7)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_asp_tcxo_div_END          (7)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_slimbus_clk_div_START     (8)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_slimbus_clk_div_END       (8)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK1_DIV_UNION
 结构说明  : R_CLK1_DIV 寄存器结构定义。地址偏移量:0x0020，初值:0x0147AE14，宽度:32
 寄存器说明: 分频比控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_siobclk : 27; /* bit[0-26] : 小数分频系数div_siobclk[26:0]，用于产生siobclk_div；
                                                       分频时钟频率=div_siobclk[26:0]/2^27*源时钟频率；
                                                       源时钟是19.2M或者480M，其选择请参见R_CLK_SEL寄存器的siobclk_sel位；
                                                       源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_siobclk_div位门控； */
        unsigned int  reserved    : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK1_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK1_DIV_div_siobclk_START  (0)
#define SOC_ASP_CFG_R_CLK1_DIV_div_siobclk_END    (26)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK2_DIV_UNION
 结构说明  : R_CLK2_DIV 寄存器结构定义。地址偏移量:0x0024，初值:0x01179EC9，宽度:32
 寄存器说明: 分频比控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_hdmimclk : 27; /* bit[0-26] : 小数分频系数div_hdmimclk[26:0]，用于产生hdmimclk_in
                                                        分频时钟频率=div_hdmimclk[26:0]/2^27*源时钟频率；
                                                        源时钟是480M；
                                                        源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_hdmimclk_div位门控； */
        unsigned int  reserved     : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK2_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK2_DIV_div_hdmimclk_START  (0)
#define SOC_ASP_CFG_R_CLK2_DIV_div_hdmimclk_END    (26)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK3_DIV_UNION
 结构说明  : R_CLK3_DIV 寄存器结构定义。地址偏移量:0x0028，初值:0x00001707，宽度:32
 寄存器说明: 分频比控制寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_audio_bclk : 8;  /* bit[0-7]  : 整数分频系数div_sio_audio_bclk，用于产生master模式下的sio_audio_bclk：
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是siobclk_div，siobclk_div请参见R_CLK1_DIV寄存器的说明；
                                                              源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_sio_audio_bclk_div位门控； */
        unsigned int  div_sio_voice_bclk : 8;  /* bit[8-15] : 整数分频系数div_sio_voice_bclk，用于产生master模式下的sio_voice_bclk：
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是siobclk_div，siobclk_div请参见R_CLK1_DIV寄存器的说明；
                                                              源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_sio_voice_bclk_div位门控； */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK3_DIV每个比特位的写使能位：
                                                              只有当write_en对应的比特位为1'b1，对R_CLK3_DIV相应的比特位的写操作才起作用。write_en[0]就是R_CLK3_DIV[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CLK3_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_audio_bclk_START  (0)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_audio_bclk_END    (7)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_voice_bclk_START  (8)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_voice_bclk_END    (15)
#define SOC_ASP_CFG_R_CLK3_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK3_DIV_write_en_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK4_DIV_UNION
 结构说明  : R_CLK4_DIV 寄存器结构定义。地址偏移量:0x002C，初值:0x00001717，宽度:32
 寄存器说明: 分频比控制寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_bt_bclk    : 8;  /* bit[0-7]  : 整数分频系数div_sio_bt_bclk，用于产生master模式下的sio_bt_bclk：
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是siobclk_div，siobclk_div请参见R_CLK1_DIV寄存器的说明；
                                                              源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_sio_bt_bclk_div位门控； */
        unsigned int  div_sio_modem_bclk : 8;  /* bit[8-15] : 整数分频系数div_sio_modem_bclk，用于产生master模式下的sio_modem_bclk：
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是siobclk_div，siobclk_div请参见R_CLK1_DIV寄存器的说明；
                                                              源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_sio_modem_bclk_div位门控； */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK4_DIV每个比特位的写使能位：
                                                              只有当write_en对应的比特位为1'b1，对R_CLK4_DIV相应的比特位的写操作才起作用。write_en[0]就是R_CLK4_DIV[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CLK4_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_bt_bclk_START     (0)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_bt_bclk_END       (7)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_modem_bclk_START  (8)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_modem_bclk_END    (15)
#define SOC_ASP_CFG_R_CLK4_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK4_DIV_write_en_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK5_DIV_UNION
 结构说明  : R_CLK5_DIV 寄存器结构定义。地址偏移量:0x0030，初值:0x00003F3F，宽度:32
 寄存器说明: 分频比控制寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_audio_adws : 8;  /* bit[0-7]  : 整数分频系数div_sio_audio_adws，用于产生master模式下的sio_audio_adws
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是sio_audio_bclk，sio_audio_bclk请参见R_CLK3_DIV寄存器div_sio_audio_bclk位的说明； */
        unsigned int  div_sio_voice_adws : 8;  /* bit[8-15] : 整数分频系数div_sio_voice_adws，用于产生master模式下的sio_voice_adws
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是sio_voice_bclk，sio_voice_bclk请参见R_CLK3_DIV寄存器div_sio_voice_bclk位的说明； */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK5_DIV每个比特位的写使能位：
                                                              只有当write_en对应的比特位为1'b1，对R_CLK5_DIV相应的比特位的写操作才起作用。write_en[0]就是R_CLK5_DIV[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CLK5_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_audio_adws_START  (0)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_audio_adws_END    (7)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_voice_adws_START  (8)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_voice_adws_END    (15)
#define SOC_ASP_CFG_R_CLK5_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK5_DIV_write_en_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK6_DIV_UNION
 结构说明  : R_CLK6_DIV 寄存器结构定义。地址偏移量:0x0034，初值:0x00003F3F，宽度:32
 寄存器说明: 分频比控制寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_bt_adws    : 8;  /* bit[0-7]  : 整数分频系数div_sio_bt_adws，用于产生master模式下的sio_bt_adws
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是sio_bt_bclk，sio_bt_bclk请参见R_CLK4_DIV寄存器div_sio_bt_bclk位的说明； */
        unsigned int  div_sio_modem_adws : 8;  /* bit[8-15] : 整数分频系数div_sio_modem_adws，用于产生master模式下的sio_modem_adws
                                                              8'h0:1；
                                                              8'h1:2；
                                                              8'h2:3；
                                                              …
                                                              8'hFE:255；
                                                              8'hFF:256；
                                                              源时钟是sio_modem_bclk，sio_modem_bclk请参见R_CLK4_DIV寄存器div_sio_modem_bclk位的说明； */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK6_DIV每个比特位的写使能位：
                                                              只有当write_en对应的比特位为1'b1，对R_CLK6_DIV相应的比特位的写操作才起作用。write_en[0]就是R_CLK6_DIV[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CLK6_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_bt_adws_START     (0)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_bt_adws_END       (7)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_modem_adws_START  (8)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_modem_adws_END    (15)
#define SOC_ASP_CFG_R_CLK6_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK6_DIV_write_en_END              (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK_SEL_UNION
 结构说明  : R_CLK_SEL 寄存器结构定义。地址偏移量:0x0038，初值:0x0000000F，宽度:32
 寄存器说明: 时钟选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_audio_slave_en   : 1;  /* bit[0]    : sio audio的master或slave模式选择寄存器：
                                                                0：master模式；
                                                                1：slave模式。
                                                                此寄存器同时也是sio audio相关的双向IO管脚I2S_XCLK和I2S_XFS的输入或输出选择：
                                                                0：输出模式；
                                                                1：输入模式。 */
        unsigned int  sio_voice_slave_en   : 1;  /* bit[1]    : sio voice的master或slave模式选择寄存器：
                                                                0：master模式；
                                                                1：slave模式。
                                                                此寄存器同时也是sio voice相关的双向IO管脚I2S_XCLK和I2S_XFS的输入或输出选择：
                                                                0：输出模式；
                                                                1：输入模式。 */
        unsigned int  sio_bt_slave_en      : 1;  /* bit[2]    : sio bt的master或slave模式选择寄存器：
                                                                0：master模式；
                                                                1：slave模式。
                                                                此寄存器同时也是sio bt相关的双向IO管脚I2S_XCLK和I2S_XFS的输入或输出选择：
                                                                0：输出模式；
                                                                1：输入模式。 */
        unsigned int  sio_modem_slave_en   : 1;  /* bit[3]    : sio modem的master或slave模式选择寄存器：
                                                                0：master模式；
                                                                1：slave模式。
                                                                此寄存器同时也是sio modem相关的双向IO管脚I2S_XCLK和I2S_XFS的输入或输出选择：
                                                                0：输出模式；
                                                                1：输入模式。 */
        unsigned int  siobclk_sel          : 1;  /* bit[4]    : 小数分频器siobclk_div的输入源时钟频率选择寄存器：
                                                                0：19.2M；
                                                                1：480M。
                                                                （小数分频器siobclk_div相关介绍还可参看R_CLK1_DIV寄存器的介绍） */
        unsigned int  slimbus_base_clk_sel : 2;  /* bit[5-6]  : slimbus base clk的时钟信号选择寄存器：
                                                                0：晶振19.2MHz；
                                                                1：来自外设区crg的clk_slimbus信号，此信号为49.152MHz\24.576MHz；
                                                                2和3：小数分频器siobclk_div的输出，小数分频器siobclk_div相关介绍还可参看R_CLK1_DIV寄存器的介绍； */
        unsigned int  watchdog_clken_sel   : 1;  /* bit[7]    : watchdog的时钟使能信号频率选择寄存器：
                                                                0：32kHz；
                                                                1：常为1。 */
        unsigned int  timer0_1_clken_sel   : 1;  /* bit[8]    : timer0_1的时钟使能信号频率选择寄存器：
                                                                0：32kHz；
                                                                1：4.8MHZ。 */
        unsigned int  timer0_2_clken_sel   : 1;  /* bit[9]    : timer0_2的时钟使能信号频率选择寄存器：
                                                                0：32kHz；
                                                                1：4.8MHZ。 */
        unsigned int  timer1_1_clken_sel   : 1;  /* bit[10]   : timer1_1的时钟使能信号频率选择寄存器：
                                                                0：32kHz；
                                                                1：4.8MHZ。 */
        unsigned int  timer1_2_clken_sel   : 1;  /* bit[11]   : timer1_2的时钟使能信号频率选择寄存器：
                                                                0：32kHz；
                                                                1：4.8MHZ。 */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  hifidsp_clk_sel      : 1;  /* bit[14]   : 整数分频器hifidsp_clk_div的输入源时钟频率选择寄存器：
                                                                0：19.2M；
                                                                1：480M。
                                                                （整数分频器hifidsp_clk_div的输出时钟即是hifidsp的core时钟） */
        unsigned int  slimbus_clk_sel      : 1;  /* bit[15]   : slimbus时钟选择寄存器：
                                                                0：ppll0小数分频得到的slimbus clk(49.152MHz\24.576MHz)；
                                                                1：peri crg输入的slimbus clk(49.152MHz\24.576MHz)； */
        unsigned int  write_en             : 16; /* bit[16-31]: R_CLK_SEL每个比特位的写使能位：
                                                                只有当write_en对应的比特位为1'b1，对R_CLK_SEL相应的比特位的写操作才起作用。write_en[0]就是R_CLK_SEL[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CLK_SEL_UNION;
#endif
#define SOC_ASP_CFG_R_CLK_SEL_sio_audio_slave_en_START    (0)
#define SOC_ASP_CFG_R_CLK_SEL_sio_audio_slave_en_END      (0)
#define SOC_ASP_CFG_R_CLK_SEL_sio_voice_slave_en_START    (1)
#define SOC_ASP_CFG_R_CLK_SEL_sio_voice_slave_en_END      (1)
#define SOC_ASP_CFG_R_CLK_SEL_sio_bt_slave_en_START       (2)
#define SOC_ASP_CFG_R_CLK_SEL_sio_bt_slave_en_END         (2)
#define SOC_ASP_CFG_R_CLK_SEL_sio_modem_slave_en_START    (3)
#define SOC_ASP_CFG_R_CLK_SEL_sio_modem_slave_en_END      (3)
#define SOC_ASP_CFG_R_CLK_SEL_siobclk_sel_START           (4)
#define SOC_ASP_CFG_R_CLK_SEL_siobclk_sel_END             (4)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_base_clk_sel_START  (5)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_base_clk_sel_END    (6)
#define SOC_ASP_CFG_R_CLK_SEL_watchdog_clken_sel_START    (7)
#define SOC_ASP_CFG_R_CLK_SEL_watchdog_clken_sel_END      (7)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_1_clken_sel_START    (8)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_1_clken_sel_END      (8)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_2_clken_sel_START    (9)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_2_clken_sel_END      (9)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_1_clken_sel_START    (10)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_1_clken_sel_END      (10)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_2_clken_sel_START    (11)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_2_clken_sel_END      (11)
#define SOC_ASP_CFG_R_CLK_SEL_hifidsp_clk_sel_START       (14)
#define SOC_ASP_CFG_R_CLK_SEL_hifidsp_clk_sel_END         (14)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_clk_sel_START       (15)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_clk_sel_END         (15)
#define SOC_ASP_CFG_R_CLK_SEL_write_en_START              (16)
#define SOC_ASP_CFG_R_CLK_SEL_write_en_END                (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_NMI_UNION
 结构说明  : R_DSP_NMI 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: DSP NMI中断产生寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_dsp_nmi : 16; /* bit[0-15] : 此寄存器16个比特位或，产生发给dsp的nmi中断 */
        unsigned int  reserved  : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_NMI_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_NMI_r_dsp_nmi_START  (0)
#define SOC_ASP_CFG_R_DSP_NMI_r_dsp_nmi_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_PRID_UNION
 结构说明  : R_DSP_PRID 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: DSP PRID设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_prid : 16; /* bit[0-15] : dsp processor id标示，用于多核的场景。 */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_PRID_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_PRID_dsp_prid_START  (0)
#define SOC_ASP_CFG_R_DSP_PRID_dsp_prid_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_RUNSTALL_UNION
 结构说明  : R_DSP_RUNSTALL 寄存器结构定义。地址偏移量:0x0044，初值:0x00000001，宽度:32
 寄存器说明: DSP RUNSTALL设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_runstall : 1;  /* bit[0]   : runstall=1，停止dsp 的pipeline，可关掉部分内部逻辑，降低功耗；
                                                       Runstall=0，dsp恢复pipeline的正常执行； */
        unsigned int  reserved     : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_RUNSTALL_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_RUNSTALL_dsp_runstall_START  (0)
#define SOC_ASP_CFG_R_DSP_RUNSTALL_dsp_runstall_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION
 结构说明  : R_DSP_STATVECTORSEL 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: DSP STATVECTORSEL设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_statvectorsel : 1;  /* bit[0]   : dsp启动地址选择：
                                                            dsp_statvectorsel=0，dsp从ITCM启动；
                                                            dsp_statvectorsel=1，dsp从DDR启动； */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_dsp_statvectorsel_START  (0)
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_dsp_statvectorsel_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION
 结构说明  : R_DSP_OCDHALTONRESET 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: DSP OCDHALTONRESET设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_ocdhaltonreset : 1;  /* bit[0]   : Ocdhaltonreset=1，强制dsp进入OCDHaltMode；
                                                             Ocdhaltonreset=0，dsp处于正常工作模式； */
        unsigned int  reserved           : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_dsp_ocdhaltonreset_START  (0)
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_dsp_ocdhaltonreset_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_STATUS_UNION
 结构说明  : R_DSP_STATUS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: DSP 状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_xocdmode  : 1;  /* bit[0]   : xocdmode=0，dsp没有处于OCD halt 模式；
                                                        xocdmode=1，dsp处于OCD halt 模式； */
        unsigned int  dsp_pwaitmode : 1;  /* bit[1]   : pwaitmode=0，dsp没有处于sleep mode模式；
                                                        pwaitmode=1，dsp处于sleep mode模式； */
        unsigned int  reserved      : 30; /* bit[2-31]: 整个寄存器的复位值由asp_cfg的输入dsp状态信号的复位值来定。 */
    } reg;
} SOC_ASP_CFG_R_DSP_STATUS_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_xocdmode_START   (0)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_xocdmode_END     (0)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_pwaitmode_START  (1)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_pwaitmode_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DMAC_SEL_UNION
 结构说明  : R_DMAC_SEL 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: DMAC通道选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]    :  */
        unsigned int  reserved_1: 1;  /* bit[1]    :  */
        unsigned int  reserved_2: 1;  /* bit[2]    :  */
        unsigned int  reserved_3: 1;  /* bit[3]    :  */
        unsigned int  reserved_4: 1;  /* bit[4]    :  */
        unsigned int  reserved_5: 1;  /* bit[5]    :  */
        unsigned int  reserved_6: 1;  /* bit[6]    :  */
        unsigned int  reserved_7: 1;  /* bit[7]    :  */
        unsigned int  reserved_8: 2;  /* bit[8-9]  :  */
        unsigned int  reserved_9: 6;  /* bit[10-15]:  */
        unsigned int  write_en : 16; /* bit[16-31]: R_DMAC_SEL每个比特位的写使能位：
                                                    只有当write_en对应的比特位为1'b1，对R_DMAC_SEL相应的比特位的写操作才起作用。write_en[0]就是R_DMAC_SEL[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_DMAC_SEL_UNION;
#endif
#define SOC_ASP_CFG_R_DMAC_SEL_write_en_START  (16)
#define SOC_ASP_CFG_R_DMAC_SEL_write_en_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_BUS_PRIORITY_UNION
 结构说明  : R_BUS_PRIORITY 寄存器结构定义。地址偏移量:0x0058，初值:0x853E4000，宽度:32
 寄存器说明: 总线优先级配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_ar_qos       : 2;  /* bit[0-1]  : dsp的axi master的ar通道的qos信号； */
        unsigned int  dsp_aw_qos       : 2;  /* bit[2-3]  : dsp的axi master的aw通道的qos信号； */
        unsigned int  dma_ar_qos       : 2;  /* bit[4-5]  : asp dmac的axi master的ar通道的qos信号； */
        unsigned int  dma_aw_qos       : 2;  /* bit[6-7]  : asp dmac的axi master的aw通道的qos信号； */
        unsigned int  ahb2axi_ar_qos   : 2;  /* bit[8-9]  : 付强桥axi master的ar通道的qos信号； */
        unsigned int  ahb2axi_aw_qos   : 2;  /* bit[10-11]: 付强桥axi master的aw通道的qos信号； */
        unsigned int  asp_slv_priority : 2;  /* bit[12-13]: NOC访问asp的端口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  dsp_mst_priority : 2;  /* bit[14-15]: dsp的master口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  dmac_priority    : 2;  /* bit[16-17]: dmac的master口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  ahb2axi_priority : 2;  /* bit[18-19]: 付强桥的master口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  asp_mst_priority : 3;  /* bit[20-22]: asp访问NOC的端口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  dsp_slv_priority : 3;  /* bit[23-25]: dsp的slave口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  ocram_priority   : 3;  /* bit[26-28]: ocram的slave口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
        unsigned int  x2h_priority     : 3;  /* bit[29-31]: x2h桥的slave口在dw_axi总线上的优先级信号；
                                                            值越高则优先级越高； */
    } reg;
} SOC_ASP_CFG_R_BUS_PRIORITY_UNION;
#endif
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_ar_qos_START        (0)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_ar_qos_END          (1)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_aw_qos_START        (2)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_aw_qos_END          (3)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_ar_qos_START        (4)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_ar_qos_END          (5)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_aw_qos_START        (6)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_aw_qos_END          (7)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_ar_qos_START    (8)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_ar_qos_END      (9)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_aw_qos_START    (10)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_aw_qos_END      (11)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_slv_priority_START  (12)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_slv_priority_END    (13)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_mst_priority_START  (14)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_mst_priority_END    (15)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dmac_priority_START     (16)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dmac_priority_END       (17)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_priority_START  (18)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_priority_END    (19)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_mst_priority_START  (20)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_mst_priority_END    (22)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_slv_priority_START  (23)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_slv_priority_END    (25)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ocram_priority_START    (26)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ocram_priority_END      (28)
#define SOC_ASP_CFG_R_BUS_PRIORITY_x2h_priority_START      (29)
#define SOC_ASP_CFG_R_BUS_PRIORITY_x2h_priority_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CG_EN_UNION
 结构说明  : R_CG_EN 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 自动门控使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dw_axi_m1_cg_en  : 1;  /* bit[0]    : dw_axi master1口（NOC配置asp的端口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_m2_cg_en  : 1;  /* bit[1]    : dw_axi master2口（对接dsp master口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_m3_cg_en  : 1;  /* bit[2]    : dw_axi master3口（对接asp dmac master口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_m4_cg_en  : 1;  /* bit[3]    : dw_axi master4口（对接付强桥master口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_s1_cg_en  : 1;  /* bit[4]    : dw_axi slave1口（asp访问NOC的端口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_s2_cg_en  : 1;  /* bit[5]    : dw_axi slave2口（对接dsp slave口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_s3_cg_en  : 1;  /* bit[6]    : dw_axi slave3口（对接ocram slave口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_s4_cg_en  : 1;  /* bit[7]    : dw_axi slave4口（对接x2h桥slave口）的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dw_axi_s0_cg_en  : 1;  /* bit[8]    : dw_axi slave0口的自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  reserved_0       : 1;  /* bit[9]    : 保留。 */
        unsigned int  dmac_hclk0_cg_en : 1;  /* bit[10]   : dmac hclk0模块自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  dmac_hclk1_cg_en : 1;  /* bit[11]   : dmac hclk1模块自动门控使能：
                                                            0：自动门控不使能；
                                                            1：自动门控使能。 */
        unsigned int  reserved_1       : 1;  /* bit[12]   :  */
        unsigned int  reserved_2       : 3;  /* bit[13-15]:  */
        unsigned int  write_en         : 16; /* bit[16-31]: R_CG_EN每个比特位的写使能位：
                                                            只有当write_en对应的比特位为1'b1，对R_CG_EN相应的比特位的写操作才起作用。write_en[0]就是R_CG_EN[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_CG_EN_UNION;
#endif
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m1_cg_en_START   (0)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m1_cg_en_END     (0)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m2_cg_en_START   (1)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m2_cg_en_END     (1)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m3_cg_en_START   (2)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m3_cg_en_END     (2)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m4_cg_en_START   (3)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m4_cg_en_END     (3)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s1_cg_en_START   (4)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s1_cg_en_END     (4)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s2_cg_en_START   (5)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s2_cg_en_END     (5)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s3_cg_en_START   (6)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s3_cg_en_END     (6)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s4_cg_en_START   (7)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s4_cg_en_END     (7)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s0_cg_en_START   (8)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s0_cg_en_END     (8)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk0_cg_en_START  (10)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk0_cg_en_END    (10)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk1_cg_en_START  (11)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk1_cg_en_END    (11)
#define SOC_ASP_CFG_R_CG_EN_write_en_START          (16)
#define SOC_ASP_CFG_R_CG_EN_write_en_END            (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_OCRAM_RET_UNION
 结构说明  : R_OCRAM_RET 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: ocram低功耗配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slp      : 3;  /* bit[0-2]  : OCRAM每片RAM通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                    默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                    如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                    
                                                    SLP: OCRAM Power Gating控制信号SLP；
                                                    bit[2]：控制OCRAM 片选2（128KB-192KB）的SLP；默认为1'b0
                                                    bit[1]：控制OCRAM 片选1（64KB-128KB）的SLP；默认为1'b0
                                                    bit[0]：控制OCRAM 片选0（0-64KB）的SLP；默认为1'b0 */
        unsigned int  reserved_0: 1;  /* bit[3]    : 保留。 */
        unsigned int  dslp     : 3;  /* bit[4-6]  : OCRAM每片RAM通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                    默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                    如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                    
                                                    DSLP: OCRAM Power Gating控制信号DSLP；
                                                    bit[2]：控制OCRAM 片选2（128KB-192KB）的DSLP；默认为1'b0
                                                    bit[1]：控制OCRAM 片选1（64KB-128KB）的DSLP；默认为1'b0
                                                    bit[0]：控制OCRAM 片选0（0-64KB）的DSLP；默认为1'b0 */
        unsigned int  reserved_1: 1;  /* bit[7]    : 保留。 */
        unsigned int  sd       : 3;  /* bit[8-10] : OCRAM每片RAM通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                    默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                    如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                    
                                                    SD: OCRAM Power Gating控制信号SD；
                                                    bit[2]：控制OCRAM 片选2（128KB-192KB）的SD；默认为1'b0
                                                    bit[1]：控制OCRAM 片选1（64KB-128KB）的SD；默认为1'b0
                                                    bit[0]：控制OCRAM 片选0（0-64KB）的SD；默认为1'b0 */
        unsigned int  reserved_2: 1;  /* bit[11]   : 保留。 */
        unsigned int  reserved_3: 4;  /* bit[12-15]: 保留。 */
        unsigned int  write_en : 16; /* bit[16-31]: R_OCRAM_RET每个比特位的写使能位：
                                                    只有当write_en对应的比特位为1'b1，对R_OCRAM_RET相应的比特位的写操作才起作用。write_en[0]就是R_OCRAM_RET[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_OCRAM_RET_UNION;
#endif
#define SOC_ASP_CFG_R_OCRAM_RET_slp_START       (0)
#define SOC_ASP_CFG_R_OCRAM_RET_slp_END         (2)
#define SOC_ASP_CFG_R_OCRAM_RET_dslp_START      (4)
#define SOC_ASP_CFG_R_OCRAM_RET_dslp_END        (6)
#define SOC_ASP_CFG_R_OCRAM_RET_sd_START        (8)
#define SOC_ASP_CFG_R_OCRAM_RET_sd_END          (10)
#define SOC_ASP_CFG_R_OCRAM_RET_write_en_START  (16)
#define SOC_ASP_CFG_R_OCRAM_RET_write_en_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_NS_INI_UNION
 结构说明  : R_INTR_NS_INI 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 非安全中断原始状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int : 1;  /* bit[0]   : asp_hdmi原始非安全中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_0   : 1;  /* bit[1]   :  */
        unsigned int  reserved_1   : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr : 1;  /* bit[3]   : slimbus原始非安全中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_2   : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_INI_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_INI_asp_hdmi_int_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_INI_asp_hdmi_int_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_INI_slimbus_intr_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_INI_slimbus_intr_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_NS_EN_UNION
 结构说明  : R_INTR_NS_EN 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 非安全中断使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_en : 1;  /* bit[0]   : asp_hdmi非安全中断使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  reserved_0      : 1;  /* bit[1]   :  */
        unsigned int  reserved_1      : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr_en : 1;  /* bit[3]   : slimbus非安全中断使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  reserved_2      : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_EN_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_EN_asp_hdmi_int_en_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_EN_asp_hdmi_int_en_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_EN_slimbus_intr_en_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_EN_slimbus_intr_en_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_NS_MASK_UNION
 结构说明  : R_INTR_NS_MASK 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 非安全中断屏蔽后状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_mask : 1;  /* bit[0]   : asp_hdmi屏蔽后非安全中断。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  reserved_0        : 1;  /* bit[1]   :  */
        unsigned int  reserved_1        : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr_mask : 1;  /* bit[3]   : slimbus屏蔽后非安全中断。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  reserved_2        : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_MASK_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_MASK_asp_hdmi_int_mask_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_MASK_asp_hdmi_int_mask_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_MASK_slimbus_intr_mask_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_MASK_slimbus_intr_mask_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION
 结构说明  : R_DBG_SET_AHB2AXI 寄存器结构定义。地址偏移量:0x0070，初值:0x01011111，宽度:32
 寄存器说明: 付强桥DBG信号设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wfq_weight_port2 : 4;  /* bit[0-3]  :  */
        unsigned int  dbg_wfq_weight_port1 : 4;  /* bit[4-7]  :  */
        unsigned int  dbg_wfq_weight_port0 : 4;  /* bit[8-11] : 端口调度采用的是WFQ算法，dbg_wfq_weight_port0~dbg_wfq_weight_port2信号用于配置3个AHB端口的权重，典型配置值：
                                                                a，若各个端口的权重值全为0x0，则采用SP算法按照严格优先级调度，0端口优先级最高，一次3端口优先级最低；
                                                                b，若各个端口的权重值相等且不为0，则采用RR算法各端口轮询调度；
                                                                c，若各个端口的权重值不等，则权重值最小的优先级最高 */
        unsigned int  dbg_rd_outstd        : 4;  /* bit[12-15]: 用于配置读操作的outstanding深度，支持动态配置  */
        unsigned int  dbg_wr_outstd        : 4;  /* bit[16-19]: 用于配置写操作的outstanding深度，支持动态配置  */
        unsigned int  dbg_port_sel         : 4;  /* bit[20-23]: h2x端口状态选择，用于选择dbg_status接口输出哪个端口的值（dbg_port_sel=x，则输出x端口的状态值） */
        unsigned int  dbg_incr_spen        : 1;  /* bit[24]   : INCR命令拆分使能，低有效时，会使能将AHB端口的INCR类型burst拆分为AXI端口的INCR类型burst，可提高带宽。反之，不会拆分。 */
        unsigned int  dbg_h2x_sel          : 1;  /* bit[25]   : h2x状态片选 */
        unsigned int  dbg_stat_clr         : 1;  /* bit[26]   : debug状态清除使能 */
        unsigned int  reserved             : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION;
#endif
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port2_START  (0)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port2_END    (3)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port1_START  (4)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port1_END    (7)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port0_START  (8)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port0_END    (11)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_rd_outstd_START         (12)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_rd_outstd_END           (15)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wr_outstd_START         (16)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wr_outstd_END           (19)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_port_sel_START          (20)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_port_sel_END            (23)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_incr_spen_START         (24)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_incr_spen_END           (24)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_h2x_sel_START           (25)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_h2x_sel_END             (25)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_stat_clr_START          (26)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_stat_clr_END            (26)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION
 结构说明  : R_DBG_STATUS_AHB2AXI 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 付强桥DBG信号状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlast_bresp_err : 1;  /* bit[0]    : AXI总线读数据或者rlast传输错误
                                                           0：没有发送读数据传输错误；
                                                           1：AHB接口没有发送读命令的状态下，接收到了总线返回的读数据；bresp错误，AHB没有发送写命令的状态下，接收到了总线返回的rlast信号；
                                                           在port_sel8时，为表示写传输数据超时状态，目前定义为16'hffff为超时时间
                                                           0：没有发生过超时；
                                                           1：发送了超时；
                                                           该状态可以被stat_clr清除 */
        unsigned int  rdata_err       : 1;  /* bit[1]    : AXI总线读数据或者bresp传输错误
                                                           0：没有发送读数据传输错误；
                                                           1：AHB接口没有发送读命令的状态下，接收到了总线返回的读数据；bresp错误，AHB没有发送写命令的状态下，接收到了总线返回的bresp信号；
                                                           在port_sel8时，为表示写传输数据超时状态，目前定义为16'hffff为超时时间
                                                           0：没有发生过超时；
                                                           1：发送了超时；
                                                           该状态可以被stat_clr清除 */
        unsigned int  rdcmd_gnt       : 1;  /* bit[2]    : AHB命令允许状态
                                                           0：没有获得AXI总线；
                                                           1：获得AXI总线，可以发送命令
                                                           在port_sel为8时，表示写传输命令超时状态，目前定义为16'hffff为超时时间
                                                           0：没有发送超时；
                                                           1：发送了超时；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  rdcmd_rearb     : 1;  /* bit[3]    : AHB内部命令重新仲裁使能
                                                           0：不允许重新仲裁；
                                                           1：可以重新仲裁；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  wrcmd_nt        : 1;  /* bit[4]    : AHB命令允许状态
                                                           0：没有获得AXI总线；
                                                           1：获得AXI总线，可以发送命令
                                                           该状态不可以被stat_clr清除 */
        unsigned int  wrcmd_rearb     : 1;  /* bit[5]    : AHB内部命令重新仲裁使能
                                                           0：不允许重新仲裁；
                                                           1：可以重新仲裁；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  cmd_arrdy       : 1;  /* bit[6]    : AHB内部接口状态
                                                           0：cmdbuf模块有读命令正在处理；
                                                           1：cmdbuf模块处于IDLE状态；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  cmd_awrdy       : 1;  /* bit[7]    : AHB内部接口状态
                                                           0：cmdbuf模块有写命令正在处理；
                                                           1：cmdbuf模块处于IDLE状态；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  rdfifo_full     : 1;  /* bit[8]    : AHB接口rdfifo满状态
                                                           0：rdfifo非满；
                                                           1：rdfifo满；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  rdfifo_empty    : 1;  /* bit[9]    : AHB接口rdfifo空状态
                                                           0：wrfifo非空；
                                                           1：wrfifo空，无缓存数据。
                                                           该状态不可以被stat_clr清除 */
        unsigned int  wrfifo_alfull   : 1;  /* bit[10]   : AHB接口wrfifo将满状态
                                                           0：wrfifo非将满；
                                                           1：wrfifo达到将满状态。
                                                           该状态不可以被stat_clr清除 */
        unsigned int  wrfifo_empty    : 1;  /* bit[11]   : AHB接口wrfifo空状态
                                                           0：wrfifo非空；
                                                           1：wrfifo空，无缓存数据；
                                                           该状态不可以被stat_clr清除 */
        unsigned int  rdfifo_rerr     : 1;  /* bit[12]   : AHB接口rdfifo的读错误指示
                                                           0：表示没有发生读错误；
                                                           1：表示发生了rdfifo空的情况下，对rdfifo写的场景
                                                           该状态可以被stat_clr清除 */
        unsigned int  rdfifo_werr     : 1;  /* bit[13]   : AHB接口rdfifo的写错误指示
                                                           0：表示没有发生写错误；
                                                           1：表示发生了rdfifo满的情况下，对rdfifo写的场景
                                                           该状态可以被stat_clr清除 */
        unsigned int  wrfifo_rerr     : 1;  /* bit[14]   : AHB接口wrfifo的读错误指示
                                                           0：表示没有发生读错误；
                                                           1：表示发生了rdfifo满的情况下，对rdfifo写的场景
                                                           该状态可以被stat_clr清除 */
        unsigned int  wrfifo_werr     : 1;  /* bit[15]   : AHB接口wrfifo的写错误指示
                                                           0：表述没有发生写错误；
                                                           1：表示发生了wrfifo满的情况下，对wrfifo写的场景。
                                                           该状态可以被stat_clr清除 */
        unsigned int  rdcmd_cnt       : 4;  /* bit[16-19]: AHB接口发送读命令对应的读数据个数
                                                           0x0~0xf:表述n个发送数，该状态不能被stat_clr清除 */
        unsigned int  rddata_cnt      : 4;  /* bit[20-23]: AHB接口读数据个数
                                                           0x0~0xf:表述n个读数据，该状态不能被stat_clr清除 */
        unsigned int  wrcmd_cnt       : 4;  /* bit[24-27]: AHB接口发送的写命令对应的写数据个数
                                                           0x0~0xf:表述n个发送数，该状态不能被stat_clr清除 */
        unsigned int  wrdata_cnt      : 4;  /* bit[28-31]: AHB接口写数据个数技术。
                                                           0x0~0xf:表示n个发送数据。
                                                           该状态不能被stat_clr清除 */
    } reg;
} SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION;
#endif
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rlast_bresp_err_START  (0)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rlast_bresp_err_END    (0)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdata_err_START        (1)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdata_err_END          (1)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_gnt_START        (2)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_gnt_END          (2)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_rearb_START      (3)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_rearb_END        (3)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_nt_START         (4)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_nt_END           (4)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_rearb_START      (5)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_rearb_END        (5)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_arrdy_START        (6)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_arrdy_END          (6)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_awrdy_START        (7)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_awrdy_END          (7)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_full_START      (8)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_full_END        (8)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_empty_START     (9)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_empty_END       (9)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_alfull_START    (10)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_alfull_END      (10)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_empty_START     (11)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_empty_END       (11)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_rerr_START      (12)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_rerr_END        (12)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_werr_START      (13)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_werr_END        (13)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_rerr_START      (14)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_rerr_END        (14)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_werr_START      (15)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_werr_END        (15)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_cnt_START        (16)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_cnt_END          (19)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rddata_cnt_START       (20)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rddata_cnt_END         (23)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_cnt_START        (24)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_cnt_END          (27)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrdata_cnt_START       (28)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrdata_cnt_END         (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DLOCK_BP_UNION
 结构说明  : R_DLOCK_BP 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 总线防挂死bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]    :  */
        unsigned int  reserved_1        : 1;  /* bit[1]    :  */
        unsigned int  dlock_bp_h2p      : 1;  /* bit[2]    : h2p桥防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_asphdmi  : 1;  /* bit[3]    : asp_hdmi模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_sioaudio : 1;  /* bit[4]    : sioaudio模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_siovoice : 1;  /* bit[5]    : siovoice模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_siobt    : 1;  /* bit[6]    : siobt模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_siomodem : 1;  /* bit[7]    : siomodem模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_slimbus  : 1;  /* bit[8]    : slimbus模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_edmac    : 1;  /* bit[9]    : asp dmac模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_ipc      : 1;  /* bit[10]   : asp ipc模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_watchdog : 1;  /* bit[11]   : watchdog模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_cfg      : 1;  /* bit[12]   : asp_cfg模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_gpio     : 1;  /* bit[13]   : gpio模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_timer0   : 1;  /* bit[14]   : timer0模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  dlock_bp_timer1   : 1;  /* bit[15]   : timer1模块防挂死bypass寄存器：
                                                             0：防挂死功能生效；
                                                             1：防挂死功能被bypass。 */
        unsigned int  write_en          : 16; /* bit[16-31]: R_DLOCK_BP每个比特位的写使能位：
                                                             只有当write_en对应的比特位为1'b1，对R_DLOCK_BP相应的比特位的写操作才起作用。write_en[0]就是R_DLOCK_BP[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_DLOCK_BP_UNION;
#endif
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_h2p_START       (2)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_h2p_END         (2)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_asphdmi_START   (3)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_asphdmi_END     (3)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_sioaudio_START  (4)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_sioaudio_END    (4)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siovoice_START  (5)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siovoice_END    (5)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siobt_START     (6)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siobt_END       (6)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siomodem_START  (7)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siomodem_END    (7)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_slimbus_START   (8)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_slimbus_END     (8)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_edmac_START     (9)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_edmac_END       (9)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_ipc_START       (10)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_ipc_END         (10)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_watchdog_START  (11)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_watchdog_END    (11)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_cfg_START       (12)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_cfg_END         (12)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_gpio_START      (13)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_gpio_END        (13)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer0_START    (14)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer0_END      (14)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer1_START    (15)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer1_END      (15)
#define SOC_ASP_CFG_R_DLOCK_BP_write_en_START           (16)
#define SOC_ASP_CFG_R_DLOCK_BP_write_en_END             (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION
 结构说明  : R_DSP_BINTERRUPT 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 上报到hifi dsp的中断信号只读寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_dsp_nmi          : 1;  /* bit[0]    : dsp nmi中断 */
        unsigned int  intr0_nonsecure_ipc   : 1;  /* bit[1]    : 系统非安全IPC给hifi的IPC_NS_int4中断 */
        unsigned int  intr1_nonsecure_ipc   : 1;  /* bit[2]    : 系统非安全IPC给hifi的IPC_NS_mbx18中断 */
        unsigned int  intr0_secure_ipc      : 1;  /* bit[3]    : 系统安全IPC给hifi的IPC_S_int4中断 */
        unsigned int  intr1_secure_ipc      : 1;  /* bit[4]    : 系统安全IPC给hifi的IPC_S_mbx18中断 */
        unsigned int  intr_asp_timer0_0     : 1;  /* bit[5]    : asp timer0模块给hifi的第0个中断 */
        unsigned int  intr_asp_timer0_1     : 1;  /* bit[6]    : asp timer0模块给hifi的第1个中断 */
        unsigned int  intr_asp_timer1_0     : 1;  /* bit[7]    : asp timer1模块给hifi的第0个中断 */
        unsigned int  intr_asp_timer1_1     : 1;  /* bit[8]    : asp timer1模块给hifi的第1个中断 */
        unsigned int  intr_sio_audio        : 1;  /* bit[9]    : sio_audio模块给hifi的中断 */
        unsigned int  intr_sio_voice        : 1;  /* bit[10]   : sio_voice模块给hifi的中断 */
        unsigned int  intr_sio_bt           : 1;  /* bit[11]   : sio_bt模块给hifi的中断 */
        unsigned int  intr_sio_modem        : 1;  /* bit[12]   : sio_modem模块给hifi的中断 */
        unsigned int  asp_hdmi_int          : 1;  /* bit[13]   : asp_hdmi模块给hifi的中断，组合了安全与非安全中断 */
        unsigned int  dma_intr              : 1;  /* bit[14]   : asp dmac模块给hifi的安全中断 */
        unsigned int  dma_intr_ns           : 1;  /* bit[15]   : asp dmac模块给hifi的非安全中断 */
        unsigned int  ldrx2hifi_time_int    : 1;  /* bit[16]   : ldrx2hifi的定时中断 */
        unsigned int  intr_addr_monitor     : 1;  /* bit[17]   : 内存保护模块上报给hifi的中断 */
        unsigned int  intr_watch_dog        : 1;  /* bit[18]   : asp watch dog模块给hifi的中断 */
        unsigned int  ipc_int               : 1;  /* bit[19]   : asp ipc模块给hifi的中断 */
        unsigned int  slimbus_intr          : 1;  /* bit[20]   : slimbus模块给hifi的中断 */
        unsigned int  mcpu_hifi_intr        : 1;  /* bit[21]   : modem cpu模块给hifi的中断 */
        unsigned int  bbe16_hifi_intr       : 1;  /* bit[22]   : bbe16模块给hifi的中断 */
        unsigned int  i2c_hifi_intr         : 1;  /* bit[23]   : i2c4模块给hifi的中断 */
        unsigned int  intr_gpio_hifi        : 1;  /* bit[24]   : asp gpio模块给hifi的中断 */
        unsigned int  tds_hifi_intr         : 1;  /* bit[25]   : tdscdma模块给hifi的中断 */
        unsigned int  intr_freq_offset      : 1;  /* bit[26]   : 频偏记录模块给hifi的中断 */
        unsigned int  freq_offset_intr_flag : 1;  /* bit[27]   : 频偏记录模块给hifi的中断指示信号
                                                                 1'b1：表示Soc侧- modem侧>=阈值（表示下行加点、上行减点）
                                                                 1'b0：表示modem侧-Soc侧>=阈值（表示上行加点、下行减点） */
        unsigned int  reserved              : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_dsp_nmi_START           (0)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_dsp_nmi_END             (0)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_nonsecure_ipc_START    (1)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_nonsecure_ipc_END      (1)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_nonsecure_ipc_START    (2)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_nonsecure_ipc_END      (2)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_secure_ipc_START       (3)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_secure_ipc_END         (3)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_secure_ipc_START       (4)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_secure_ipc_END         (4)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_0_START      (5)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_0_END        (5)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_1_START      (6)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_1_END        (6)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_0_START      (7)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_0_END        (7)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_1_START      (8)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_1_END        (8)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_audio_START         (9)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_audio_END           (9)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_voice_START         (10)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_voice_END           (10)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_bt_START            (11)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_bt_END              (11)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_modem_START         (12)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_modem_END           (12)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_asp_hdmi_int_START           (13)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_asp_hdmi_int_END             (13)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_START               (14)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_END                 (14)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_ns_START            (15)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_ns_END              (15)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ldrx2hifi_time_int_START     (16)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ldrx2hifi_time_int_END       (16)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_addr_monitor_START      (17)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_addr_monitor_END        (17)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_watch_dog_START         (18)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_watch_dog_END           (18)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ipc_int_START                (19)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ipc_int_END                  (19)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_slimbus_intr_START           (20)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_slimbus_intr_END             (20)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_mcpu_hifi_intr_START         (21)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_mcpu_hifi_intr_END           (21)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_bbe16_hifi_intr_START        (22)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_bbe16_hifi_intr_END          (22)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_i2c_hifi_intr_START          (23)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_i2c_hifi_intr_END            (23)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_gpio_hifi_START         (24)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_gpio_hifi_END           (24)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_tds_hifi_intr_START          (25)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_tds_hifi_intr_END            (25)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_freq_offset_START       (26)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_freq_offset_END         (26)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_freq_offset_intr_flag_START  (27)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_freq_offset_intr_flag_END    (27)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_RAM_RET_UNION
 结构说明  : R_DSP_RAM_RET 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram0_pgt_ctrl : 3;  /* bit[0-2]  : DSP DRAM0通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                          默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                          如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                          bit[2]:SD
                                                          bit[1]:DSLP
                                                          bit[0]:SLP */
        unsigned int  dram1_pgt_ctrl : 3;  /* bit[3-5]  : DSP DRAM1通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                          默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                          如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                          bit[5]:SD
                                                          bit[4]:DSLP
                                                          bit[3]:SLP */
        unsigned int  iram0_pgt_ctrl : 3;  /* bit[6-8]  : DSP IRAM0通过3个信号（SD、DSLP、SLP）控制其功耗模式。
                                                          默认为Normal Mode(SD=0，DSLP=0，SLP=0)
                                                          如果某片RAM在不需要使用的时候，可以通过软件配置按照模式切换时序进入Power Down模式(SD=1，DSLP=0，SLP=0)，以节省功耗。
                                                          bit[8]:SD
                                                          bit[7]:DSLP
                                                          bit[6]:SLP */
        unsigned int  reserved       : 7;  /* bit[9-15] : 保留。 */
        unsigned int  write_en       : 16; /* bit[16-31]: R_DSP_RAM_RET每个比特位的写使能位：
                                                          只有当write_en对应的比特位为1'b1，对R_DSP_RAM_RET相应的比特位的写操作才起作用。write_en[0]就是R_DSP_RAM_RET[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_DSP_RAM_RET_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram0_pgt_ctrl_START  (0)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram0_pgt_ctrl_END    (2)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram1_pgt_ctrl_START  (3)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram1_pgt_ctrl_END    (5)
#define SOC_ASP_CFG_R_DSP_RAM_RET_iram0_pgt_ctrl_START  (6)
#define SOC_ASP_CFG_R_DSP_RAM_RET_iram0_pgt_ctrl_END    (8)
#define SOC_ASP_CFG_R_DSP_RAM_RET_write_en_START        (16)
#define SOC_ASP_CFG_R_DSP_RAM_RET_write_en_END          (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_TZ_SECURE_N_UNION
 结构说明  : R_TZ_SECURE_N 寄存器结构定义。地址偏移量:0x0100，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 1;  /* bit[0]    :  */
        unsigned int  reserved_1           : 1;  /* bit[1]    :  */
        unsigned int  tz_secure_asphdmi_n  : 1;  /* bit[2]    : asp hdmi模块的安全属性；
                                                                0：asp hdmi只能被安全配置；
                                                                1：asp hdmi可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_sioaudio_n : 1;  /* bit[3]    : asp sio_audio模块的安全属性；
                                                                0：asp sio_audio只能被安全配置；
                                                                1：asp sio_audio可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_siovoice_n : 1;  /* bit[4]    : asp sio_voice模块的安全属性；
                                                                0：asp sio_voice只能被安全配置；
                                                                1：asp sio_voice可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_siobt_n    : 1;  /* bit[5]    : asp sio_bt模块的安全属性；
                                                                0：asp sio_bt只能被安全配置；
                                                                1：asp sio_bt可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_siomodem_n : 1;  /* bit[6]    : asp sio_modem模块的安全属性；
                                                                0：asp sio_modem只能被安全配置；
                                                                1：asp sio_modem可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_slimbus_n  : 1;  /* bit[7]    : asp slimbus模块的安全属性；
                                                                0：asp slimbus只能被安全配置；
                                                                1：asp slimbus可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_edamc_n    : 1;  /* bit[8]    : asp dmac模块的安全属性；
                                                                0：asp dmac只能被安全配置；
                                                                1：asp dmac可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_ipc_n      : 1;  /* bit[9]    : asp ipc模块的安全属性；
                                                                0：asp ipc只能被安全配置；
                                                                1：asp ipc可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_watchdog_n : 1;  /* bit[10]   : asp watchdog模块的安全属性；
                                                                0：asp watchdog只能被安全配置；
                                                                1：asp watchdog可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_dsp_n      : 1;  /* bit[11]   : dsp模块slave端口（即ITCM/DTCM）的安全属性；
                                                                0：dsp模块slave端口只能被安全配置；
                                                                1：dsp模块slave端口可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_gpio_n     : 1;  /* bit[12]   : asp gpio模块的安全属性；
                                                                0：asp gpio只能被安全配置；
                                                                1：asp gpio可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_timer0_n   : 1;  /* bit[13]   : asp timer0模块的安全属性；
                                                                0：asp timer0只能被安全配置；
                                                                1：asp timer0可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  tz_secure_timer1_n   : 1;  /* bit[14]   : asp timer1模块的安全属性；
                                                                0：asp timer1只能被安全配置；
                                                                1：asp timer1可以被非安全配置；
                                                                此寄存器只有安全可配； */
        unsigned int  dsp_mst_secure_n     : 1;  /* bit[15]   : dsp模块master端口的安全属性；
                                                                0：dsp模块master端口发出的操作是安全的；
                                                                1：dsp模块master端口发出的操作是非安全的；
                                                                此寄存器只有安全可配； */
        unsigned int  write_en             : 16; /* bit[16-31]: R_TZ_SECURE_N每个比特位的写使能位：
                                                                只有当write_en对应的比特位为1'b1，对R_TZ_SECURE_相应的比特位的写操作才起作用。write_en[0]就是R_TZ_SECURE_[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_TZ_SECURE_N_UNION;
#endif
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_asphdmi_n_START   (2)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_asphdmi_n_END     (2)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_sioaudio_n_START  (3)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_sioaudio_n_END    (3)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siovoice_n_START  (4)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siovoice_n_END    (4)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siobt_n_START     (5)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siobt_n_END       (5)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siomodem_n_START  (6)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siomodem_n_END    (6)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_slimbus_n_START   (7)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_slimbus_n_END     (7)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_edamc_n_START     (8)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_edamc_n_END       (8)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_ipc_n_START       (9)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_ipc_n_END         (9)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_watchdog_n_START  (10)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_watchdog_n_END    (10)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_dsp_n_START       (11)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_dsp_n_END         (11)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_gpio_n_START      (12)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_gpio_n_END        (12)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer0_n_START    (13)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer0_n_END      (13)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer1_n_START    (14)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer1_n_END      (14)
#define SOC_ASP_CFG_R_TZ_SECURE_N_dsp_mst_secure_n_START      (15)
#define SOC_ASP_CFG_R_TZ_SECURE_N_dsp_mst_secure_n_END        (15)
#define SOC_ASP_CFG_R_TZ_SECURE_N_write_en_START              (16)
#define SOC_ASP_CFG_R_TZ_SECURE_N_write_en_END                (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION
 结构说明  : R_OCRAM_R0SIZE 寄存器结构定义。地址偏移量:0x0104，初值:0x000003FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ocram_r0size : 10; /* bit[0-9]  : OCRAM安全区域的粒度以4KB为单位，r0size[9]=1'b1则整个OCRAM为安全，r0size[9]=1'b0时，则安全区域的大小为4KB*r0size[8:0]；
                                                        此寄存器只有安全可配； */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION;
#endif
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ocram_r0size_START  (0)
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ocram_r0size_END    (9)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION
 结构说明  : R_SIO_LOOP_SECURE_N 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_audio_loop_secure_n : 1;  /* bit[0]   : sio audio的loop使能寄存器的安全属性；
                                                                  0：sio audio的loop使能寄存器只能被安全配置；
                                                                  1：sio audio的loop使能寄存器可以被非安全配置；
                                                                  此寄存器只有安全可配； */
        unsigned int  sio_voice_loop_secure_n : 1;  /* bit[1]   : sio voice的loop使能寄存器的安全属性；
                                                                  0：sio voice的loop使能寄存器只能被安全配置；
                                                                  1：sio voice的loop使能寄存器可以被非安全配置；
                                                                  此寄存器只有安全可配； */
        unsigned int  sio_bt_loop_secure_n    : 1;  /* bit[2]   : sio bt的loop使能寄存器的安全属性；
                                                                  0：sio bt的loop使能寄存器只能被安全配置；
                                                                  1：sio bt的loop使能寄存器可以被非安全配置；
                                                                  此寄存器只有安全可配； */
        unsigned int  sio_modem_loop_secure_n : 1;  /* bit[3]   : sio modem的loop使能寄存器的安全属性；
                                                                  0：sio modem的loop使能寄存器只能被安全配置；
                                                                  1：sio modem的loop使能寄存器可以被非安全配置；
                                                                  此寄存器只有安全可配； */
        unsigned int  reserved                : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION;
#endif
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_audio_loop_secure_n_START  (0)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_audio_loop_secure_n_END    (0)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_voice_loop_secure_n_START  (1)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_voice_loop_secure_n_END    (1)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_bt_loop_secure_n_START     (2)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_bt_loop_secure_n_END       (2)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_modem_loop_secure_n_START  (3)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_modem_loop_secure_n_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_S_INI_UNION
 结构说明  : R_INTR_S_INI 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 安全中断原始状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure : 1;  /* bit[0]   : asp_hdmi原始安全中断。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned int  reserved_0          : 1;  /* bit[1]   :  */
        unsigned int  reserved_1          : 1;  /* bit[2]   :  */
        unsigned int  reserved_2          : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_INI_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_INI_asp_hdmi_int_secure_START  (0)
#define SOC_ASP_CFG_R_INTR_S_INI_asp_hdmi_int_secure_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_S_EN_UNION
 结构说明  : R_INTR_S_EN 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 安全中断使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure_en : 1;  /* bit[0]   : asp_hdmi安全中断使能。
                                                                 0：不使能；
                                                                 1：使能。
                                                                 此寄存器只有安全可配； */
        unsigned int  reserved_0             : 1;  /* bit[1]   :  */
        unsigned int  reserved_1             : 1;  /* bit[2]   :  */
        unsigned int  reserved_2             : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_EN_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_EN_asp_hdmi_int_secure_en_START  (0)
#define SOC_ASP_CFG_R_INTR_S_EN_asp_hdmi_int_secure_en_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_S_MASK_UNION
 结构说明  : R_INTR_S_MASK 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 安全中断屏蔽后状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure_mask : 1;  /* bit[0]   : asp_hdmi屏蔽后安全中断。
                                                                   0：无中断；
                                                                   1：有中断。 */
        unsigned int  reserved_0               : 1;  /* bit[1]   :  */
        unsigned int  reserved_1               : 1;  /* bit[2]   :  */
        unsigned int  reserved_2               : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_MASK_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_MASK_asp_hdmi_int_secure_mask_START  (0)
#define SOC_ASP_CFG_R_INTR_S_MASK_asp_hdmi_int_secure_mask_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION
 结构说明  : R_DSP_REMAPPING_EN 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: dsp地址重映射使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length          : 8;  /* bit[0-7] : remaping 地址长度；地址范围为1MB *（ remap_length+1）
                                                                此寄存器安全属性可配； */
        unsigned int  dsp_addr_remapping_en : 1;  /* bit[8]   : dsp address remapping enable
                                                                0：disable address remapping；
                                                                1：enable address remapping；
                                                                此寄存器安全属性可配； */
        unsigned int  reserved              : 23; /* bit[9-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_remap_length_START           (0)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_remap_length_END             (7)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_dsp_addr_remapping_en_START  (8)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_dsp_addr_remapping_en_END    (8)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION
 结构说明  : R_DSP_REMAPPING_SRC_BASE_ADDR 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: DSP 地址重映射寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                : 20; /* bit[0-19] : 保留 */
        unsigned int  asp_reserved_start_addr : 12; /* bit[20-31]: asp 预留的remapping起始地址；
                                                                   此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_asp_reserved_start_addr_START  (20)
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_asp_reserved_start_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION
 结构说明  : R_DSP_REMAPPING_DES_BASE_ADDR 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: DSP 地址重映射寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved       : 20; /* bit[0-19] : 保留 */
        unsigned int  ddr_start_addr : 12; /* bit[20-31]: remapping目标地址的起始地址；
                                                          此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ddr_start_addr_START  (20)
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ddr_start_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION
 结构说明  : R_DDR_HARQ_REMAP_EN 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: DDR与Harq Memory remap控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR与Harq Memory remap地址范围配置，地址范围为4kB * remap_length
                                                        此寄存器安全属性可配； */
        unsigned int  remap_en     : 1;  /* bit[9]    : 从DSP的视角，DDR与Harq Memory remap使能控制
                                                        1：使能
                                                        0：不使能
                                                        此寄存器安全属性可配； */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION
 结构说明  : R_DDR_HARQ_REMAP_SRC_BASE_ADDR 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: DDR与Harq Memory remap源基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : 保留 */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR与Harq Memory remap源基地址；实际的地址为：4kB * src_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION
 结构说明  : R_DDR_HARQ_REMAP_DES_BASE_ADDR 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: DDR与Harq Memory remap目标基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR与Harq Memory remap目标基地址；实际的地址为：4kB * des_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION
 结构说明  : R_DDR_MMBUF_REMAP_EN 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: DDR与MMBUF remap控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR与MMBUF remap地址范围配置，地址范围为4kB * remap_length
                                                        此寄存器安全属性可配； */
        unsigned int  remap_en     : 1;  /* bit[9]    : 从DSP的视角，DDR与MMBUF remap使能控制
                                                        1：使能
                                                        0：不使能
                                                        此寄存器安全属性可配； */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION
 结构说明  : R_DDR_MMBUF_REMAP_SRC_BASE_ADDR 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: DDR与MMBUF remap源基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : 保留 */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR与MMBUF remap源基地址；实际的地址为：4kB * src_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION
 结构说明  : R_DDR_MMBUF_REMAP_DES_BASE_ADDR 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: DDR与MMBUF remap目标基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR与MMBUF remap目标基地址；实际的地址为：4kB * des_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION
 结构说明  : R_DDR_OCRAM_REMAP_EN 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: DDR与OCRAM remap控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR与OCRAM remap地址范围配置，地址范围为4kB * remap_length
                                                        此寄存器安全属性可配； */
        unsigned int  remap_en     : 1;  /* bit[9]    : 从DSP的视角，DDR与OCRAM remap使能控制
                                                        1：使能
                                                        0：不使能
                                                        此寄存器安全属性可配； */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION
 结构说明  : R_DDR_OCRAM_REMAP_SRC_BASE_ADDR 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: DDR与OCRAM remap源基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : 保留 */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR与OCRAM remap源基地址；实际的地址为：4kB * src_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION
 结构说明  : R_DDR_OCRAM_REMAP_DES_BASE_ADDR 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: DDR与OCRAM remap目标基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR与OCRAM remap目标基地址；实际的地址为：4kB * des_base_addr
                                                         此寄存器安全属性可配； */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_MMBUF_CTRL_UNION
 结构说明  : R_MMBUF_CTRL 寄存器结构定义。地址偏移量:0x0148，初值:0x000000FD，宽度:32
 寄存器说明: MMBUF CTRL配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_en      : 1;  /* bit[0]    : PPLl0开关控制：
                                                         1：打开 0：关闭 */
        unsigned int  fll_en        : 1;  /* bit[1]    : FLL开关控制：
                                                         1：打开 0：关闭 */
        unsigned int  mmbuf_clk_en  : 1;  /* bit[2]    : MMBUF时钟门控：
                                                         1：打开 0：关闭 */
        unsigned int  aobus_clk_en  : 1;  /* bit[3]    : AOBUS时钟门控：
                                                         1：打开 0：关闭 */
        unsigned int  mmbuf_clk_sel : 2;  /* bit[4-5]  : MMBUF时钟选择：
                                                         1X：ppll0 
                                                         01：fll
                                                         00：tcxo */
        unsigned int  aobus_clk_sel : 2;  /* bit[6-7]  : AOBUS时钟选择：
                                                         11：ppll0 
                                                         10：ddrpll 
                                                         01：fll
                                                         00：tcxo */
        unsigned int  reserved      : 8;  /* bit[8-15] : 保留。 */
        unsigned int  write_en      : 16; /* bit[16-31]: R_MMBUF_CTRL每个比特位的写使能位：
                                                         只有当write_en对应的比特位为1'b1，对R_MMBUF_CTRL相应的比特位的写操作才起作用。write_en[0]就是R_MMBUF_CTRL[0]的写使能位。写1有效。 */
    } reg;
} SOC_ASP_CFG_R_MMBUF_CTRL_UNION;
#endif
#define SOC_ASP_CFG_R_MMBUF_CTRL_ppll0_en_START       (0)
#define SOC_ASP_CFG_R_MMBUF_CTRL_ppll0_en_END         (0)
#define SOC_ASP_CFG_R_MMBUF_CTRL_fll_en_START         (1)
#define SOC_ASP_CFG_R_MMBUF_CTRL_fll_en_END           (1)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_en_START   (2)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_en_END     (2)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_en_START   (3)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_en_END     (3)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_sel_START  (4)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_sel_END    (5)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_sel_START  (6)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_sel_END    (7)
#define SOC_ASP_CFG_R_MMBUF_CTRL_write_en_START       (16)
#define SOC_ASP_CFG_R_MMBUF_CTRL_write_en_END         (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION
 结构说明  : R_HIFIDSP_CLK_DIV_AUTO 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: HIFIDSP时钟频率自动调频配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hifidsp_idle_time_cfgcnt : 8;  /* bit[0-7]  : 
                                                                    HIFIDSP WFI信号有效之后等待周期配置，当实际等待周期大于等于配置周期之后，硬件开始自动调频；
                                                                    等待周期0~255可配； */
        unsigned int  div_hifidsp_clk_auto     : 3;  /* bit[8-10] : HIFIDSP CORE时钟降频配置，总线时钟会随CORE时钟一起降频
                                                                    0：不降频,DIV为软件配置值；
                                                                    1：DIV降为软件配置频率的1/2；
                                                                    2：DIV降为软件配置频率的1/4；
                                                                    3：DIV降为软件配置频率的1/8；
                                                                    4：DIV降为软件配置频率的1/16；
                                                                    5：DIV降为软件配置频率的1/32；
                                                                    6、7：DIV降为6'h3F；
                                                                    注：自动降频之后最低只能为源时钟的1/64;如果软件配置div叠加自动降频配置之后超过1/64，则默认降至1/64； */
        unsigned int  reserved_0               : 1;  /* bit[11]   : 保留 */
        unsigned int  reserved_1               : 1;  /* bit[12]   : 保留 */
        unsigned int  reserved_2               : 1;  /* bit[13]   : 保留 */
        unsigned int  dsp_pwaitmode_bypass     : 1;  /* bit[14]   : dsp pwaitmode状态bypass配置
                                                                    0：bypass无效
                                                                    1：bypass有效 */
        unsigned int  dw_axi_m1_st_bypass      : 1;  /* bit[15]   : dw_axi总线mst1接口状态bypass配置
                                                                    0：bypass无效
                                                                    1：bypass有效 */
        unsigned int  dw_axi_m2_st_bypass      : 1;  /* bit[16]   : dw_axi总线mst2接口状态bypass配置
                                                                    0：bypass无效
                                                                    1：bypass有效 */
        unsigned int  dw_axi_m3_st_bypass      : 1;  /* bit[17]   : dw_axi总线mst3接口状态bypass配置
                                                                    0：bypass无效
                                                                    1：bypass有效 */
        unsigned int  dw_axi_m4_st_bypass      : 1;  /* bit[18]   : dw_axi总线mst4接口状态bypass配置
                                                                    0：bypass无效
                                                                    1：bypass有效 */
        unsigned int  reserved_3               : 13; /* bit[19-31]:  */
    } reg;
} SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION;
#endif
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_hifidsp_idle_time_cfgcnt_START  (0)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_hifidsp_idle_time_cfgcnt_END    (7)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_div_hifidsp_clk_auto_START      (8)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_div_hifidsp_clk_auto_END        (10)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dsp_pwaitmode_bypass_START      (14)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dsp_pwaitmode_bypass_END        (14)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m1_st_bypass_START       (15)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m1_st_bypass_END         (15)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m2_st_bypass_START       (16)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m2_st_bypass_END         (16)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m3_st_bypass_START       (17)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m3_st_bypass_END         (17)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m4_st_bypass_START       (18)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m4_st_bypass_END         (18)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION
 结构说明  : R_INTR_FREQ_OFFSET_CFG 寄存器结构定义。地址偏移量:0x0150，初值:0x00000110，宽度:32
 寄存器说明: 频偏记录模块配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq_offset_en       : 1;  /* bit[0]    : 频偏记录模块使能：
                                                                0：不使能；
                                                                1：使能； */
        unsigned int  freq_offset_cnt_freq : 2;  /* bit[1-2]  : 频偏记录模块计数频率配置：
                                                                0：以8KHz计数；
                                                                1：以16KHz计数；
                                                                2：以32KHz计数；
                                                                3：以48KHz计数； */
        unsigned int  intr_freq_offset_clr : 1;  /* bit[3]    : 频偏记录模块中断写清，检测上升沿清中断：
                                                                0：无效；
                                                                1：中断清零； */
        unsigned int  intr_freq_offset_msk : 1;  /* bit[4]    : 频偏记录模块中断屏蔽：
                                                                0：屏蔽无效；
                                                                1：屏蔽有效。 */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  freq_offset_limen    : 8;  /* bit[8-15] : 频偏记录模块阈值门限配置。当差值>=阈值时，上报中断。不允许配0。
                                                                配置范围1~255。 */
        unsigned int  reserved_1           : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_en_START        (0)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_en_END          (0)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_cnt_freq_START  (1)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_cnt_freq_END    (2)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_clr_START  (3)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_clr_END    (3)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_msk_START  (4)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_msk_END    (4)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_limen_START     (8)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_limen_END       (15)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR_EN_ADDR 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块使能配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_en : 1;  /* bit[0]   : 内存监控使能：
                                                           0：不使能；
                                                           1：使能； */
        unsigned int  addr_monitor1_en : 1;  /* bit[1]   : 内存监控使能：
                                                           0：不使能；
                                                           1：使能； */
        unsigned int  addr_monitor2_en : 1;  /* bit[2]   : 内存监控使能：
                                                           0：不使能；
                                                           1：使能； */
        unsigned int  addr_monitor3_en : 1;  /* bit[3]   : 内存监控使能：
                                                           0：不使能；
                                                           1：使能； */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor0_en_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor0_en_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor1_en_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor1_en_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor2_en_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor2_en_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor3_en_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor3_en_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块中断清零配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor_intr_clr : 1;  /* bit[0]   : 内存监控中断清零：
                                                                0：无效；
                                                                1：清零； */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_addr_monitor_intr_clr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_addr_monitor_intr_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR 寄存器结构定义。地址偏移量:0x0168，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块中断使能配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_intr_en : 1;  /* bit[0]   : 内存监控中断使能：
                                                                0：不使能；
                                                                1：使能； */
        unsigned int  addr_monitor1_intr_en : 1;  /* bit[1]   : 内存监控中断使能：
                                                                0：不使能；
                                                                1：使能； */
        unsigned int  addr_monitor2_intr_en : 1;  /* bit[2]   : 内存监控中断使能：
                                                                0：不使能；
                                                                1：使能； */
        unsigned int  addr_monitor3_intr_en : 1;  /* bit[3]   : 内存监控中断使能：
                                                                0：不使能；
                                                                1：使能； */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor0_intr_en_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor0_intr_en_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor1_intr_en_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor1_intr_en_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor2_intr_en_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor2_intr_en_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor3_intr_en_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor3_intr_en_END    (3)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR 寄存器结构定义。地址偏移量:0x016C，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_arhit_intr_stat : 1;  /* bit[0]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor0_awhit_intr_stat : 1;  /* bit[1]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor1_arhit_intr_stat : 1;  /* bit[2]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor1_awhit_intr_stat : 1;  /* bit[3]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor2_arhit_intr_stat : 1;  /* bit[4]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor2_awhit_intr_stat : 1;  /* bit[5]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor3_arhit_intr_stat : 1;  /* bit[6]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  addr_monitor3_awhit_intr_stat : 1;  /* bit[7]   : 内存监控中断原始状态：
                                                                        0：中断无效；
                                                                        1：中断有效； */
        unsigned int  reserved                      : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_arhit_intr_stat_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_arhit_intr_stat_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_awhit_intr_stat_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_awhit_intr_stat_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_arhit_intr_stat_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_arhit_intr_stat_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_awhit_intr_stat_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_awhit_intr_stat_END    (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_arhit_intr_stat_START  (4)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_arhit_intr_stat_END    (4)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_awhit_intr_stat_START  (5)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_awhit_intr_stat_END    (5)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_arhit_intr_stat_START  (6)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_arhit_intr_stat_END    (6)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_awhit_intr_stat_START  (7)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_awhit_intr_stat_END    (7)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR0_BASE_ADDR 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块0基地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor0_base : 20; /* bit[12-31]: 内存监控模块0基地址：实际的地址为：4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_addr_monitor0_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_addr_monitor0_base_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR0_LEN_ADDR 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块0地址长度配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor0_len : 20; /* bit[12-31]: 内存监控模块0地址长度：实际为：4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_addr_monitor0_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_addr_monitor0_len_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR0_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块0越界的写地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_hit_awaddr : 32; /* bit[0-31]: 内存监控模块0越界的写地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_addr_monitor0_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_addr_monitor0_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR0_HIT_ARADDR 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块0越界的读地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_hit_araddr : 32; /* bit[0-31]: 内存监控模块0越界的读地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_addr_monitor0_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_addr_monitor0_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR1_BASE_ADDR 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块1基地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor1_base : 20; /* bit[12-31]: 内存监控模块1基地址：实际的地址为：4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_addr_monitor1_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_addr_monitor1_base_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR1_LEN_ADDR 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块1地址长度配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor1_len : 20; /* bit[12-31]: 内存监控模块1地址长度：实际为：4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_addr_monitor1_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_addr_monitor1_len_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR1_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块1越界的写地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor1_hit_awaddr : 32; /* bit[0-31]: 内存监控模块1越界的写地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_addr_monitor1_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_addr_monitor1_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR1_HIT_ARADDR 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块1越界的读地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor1_hit_araddr : 32; /* bit[0-31]: 内存监控模块1越界的读地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_addr_monitor1_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_addr_monitor1_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR2_BASE_ADDR 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块2基地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor2_base : 20; /* bit[12-31]: 内存监控模块2基地址：实际的地址为：4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_addr_monitor2_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_addr_monitor2_base_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR2_LEN_ADDR 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块2地址长度配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor2_len : 20; /* bit[12-31]: 内存监控模块2地址长度：实际为：4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_addr_monitor2_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_addr_monitor2_len_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR2_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块2越界的写地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor2_hit_awaddr : 32; /* bit[0-31]: 内存监控模块2越界的写地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_addr_monitor2_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_addr_monitor2_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR2_HIT_ARADDR 寄存器结构定义。地址偏移量:0x019C，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块2越界的读地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor2_hit_araddr : 32; /* bit[0-31]: 内存监控模块2越界的读地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_addr_monitor2_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_addr_monitor2_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR3_BASE_ADDR 寄存器结构定义。地址偏移量:0x01A0，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块3基地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor3_base : 20; /* bit[12-31]: 内存监控模块3基地址：实际的地址为：4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_addr_monitor3_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_addr_monitor3_base_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR3_LEN_ADDR 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块3地址长度配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : 保留 */
        unsigned int  addr_monitor3_len : 20; /* bit[12-31]: 内存监控模块3地址长度：实际为：4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_addr_monitor3_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_addr_monitor3_len_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR3_HIT_AWADDR 寄存器结构定义。地址偏移量:0x01A8，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块3越界的写地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor3_hit_awaddr : 32; /* bit[0-31]: 内存监控模块3越界的写地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_addr_monitor3_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_addr_monitor3_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION
 结构说明  : R_ACCESS_ADDR_MONITOR3_HIT_ARADDR 寄存器结构定义。地址偏移量:0x01AC，初值:0x00000000，宽度:32
 寄存器说明: 内存监控模块3越界的读地址记录寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor3_hit_araddr : 32; /* bit[0-31]: 内存监控模块3越界的读地址 */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_addr_monitor3_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_addr_monitor3_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_MEMORY_CTRL_UNION
 结构说明  : R_MEMORY_CTRL 寄存器结构定义。地址偏移量:0x01B0，初值:0x01A800A8，宽度:32
 寄存器说明: memory控制配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s  : 16; /* bit[0-15] : sram控制寄存器[15:0] 
                                                       （注：除OCRAM和DSP中各有3片RAM是分别由R_OCRAM_RET、R_DSP_RAM_RET寄存器控制，其余memory控制均由该寄存器控制）
                                                       [0]:slp
                                                       [1]:dslp
                                                       [2]:sd
                                                       [4:3]:rtsel(SPSB RAM)
                                                       [6:5]:wtsel(SPSB RAM)
                                                       [8:7]:rtsel(SPMB RAM)
                                                       [10:9]:wtsel(SPMB RAM)
                                                       [15:11]:reserved */
        unsigned int  mem_ctrl_tp : 16; /* bit[16-31]: tpram控制寄存器[15:0]
                                                       （注：除OCRAM和DSP中各有3片RAM是分别由R_OCRAM_RET、R_DSP_RAM_RET寄存器控制，其余memory控制均由该寄存器控制）
                                                       [0]:slp
                                                       [1]:dslp
                                                       [2]:sd
                                                       [4:3]:rct
                                                       [6:5]:wct
                                                       [8:7]:kp
                                                       [15:10]:reserved */
    } reg;
} SOC_ASP_CFG_R_MEMORY_CTRL_UNION;
#endif
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_s_START   (0)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_s_END     (15)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_tp_START  (16)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_tp_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION
 结构说明  : R_SLIMBUS_PRIMARY_ADDR 寄存器结构定义。地址偏移量:0x01B4，初值:0x00000001，宽度:32
 寄存器说明: slimbus primary配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slimbus_primary : 1;  /* bit[0]   : 用于在上电复位的时候由framer输出slimbus时钟 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_slimbus_primary_START  (0)
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_slimbus_primary_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION
 结构说明  : R_SLIMBUS_ID_ADDR 寄存器结构定义。地址偏移量:0x01B8，初值:0x00000000，宽度:32
 寄存器说明: slimbus id配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slimbus_id : 16; /* bit[0-15] : 用于识别制造商，由slimbus组织分配，每个厂商的值不同 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_slimbus_id_START  (0)
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_slimbus_id_END    (15)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION
 结构说明  : R_SLIM_DAT_FMT_CFG 寄存器结构定义。地址偏移量:0x01BC，初值:0x00000000，宽度:32
 寄存器说明: slimbus数据格式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dat_fmt_cfg_0 : 2;  /* bit[0-1]  : 配置DPORT1和DPORT0的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_1 : 2;  /* bit[2-3]  : 配置DPORT3和DPORT2的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_2 : 2;  /* bit[4-5]  : 配置DPORT5和DPORT4的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_3 : 2;  /* bit[6-7]  : 配置DPORT7和DPORT6的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_4 : 2;  /* bit[8-9]  : 配置DPORT9和DPORT8的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_5 : 2;  /* bit[10-11]: 配置DPORT11和DPORT10的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_6 : 2;  /* bit[12-13]: 配置DPORT13和DPORT12的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dat_fmt_cfg_7 : 2;  /* bit[14-15]: 配置DPORT15和DPORT14的数据格式
                                                         00:保持普通的AHB传输，不做数据处理；
                                                         01: Data format1；
                                                         10: Data format2；
                                                         11: Data format3；该格式也为SLIMbus支持的数据格式。不用做数据格式转换； */
        unsigned int  dma_mask_clr  : 8;  /* bit[16-23]: 状态清除寄存器。配置16个DPROT中每一对DPORT，当该bit为1时可以清除这一对DPORT的Mask信号的状态；在不同的配置切换时，用该寄存器进行初始化；其中dat_fmt_cfg [23]代表DPORT15和DPROT14的配置；dat_chnl_cfg [16]代表DPORT1和DPROT0的配置
                                                         1：代表清除对应DPORT的mask信号的状态；
                                                         0：正常工作； */
        unsigned int  reserved      : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_0_START  (0)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_0_END    (1)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_1_START  (2)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_1_END    (3)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_2_START  (4)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_2_END    (5)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_3_START  (6)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_3_END    (7)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_4_START  (8)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_4_END    (9)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_5_START  (10)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_5_END    (11)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_6_START  (12)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_6_END    (13)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_7_START  (14)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_7_END    (15)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dma_mask_clr_START   (16)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dma_mask_clr_END     (23)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION
 结构说明  : R_SLIM_DAT_CHNL_CFG 寄存器结构定义。地址偏移量:0x01C0，初值:0x00000000，宽度:32
 寄存器说明: slimbus数据通道配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass       : 1;  /* bit[0]    : bypass功能，是否使能数据格式转换模块
                                                        1'b0:使能数据转换模块；
                                                        1'b1:bypass数据转换模块，数据不作转换； */
        unsigned int  reserved     : 7;  /* bit[1-7]  : 保留。 */
        unsigned int  chl_rght_fst : 8;  /* bit[8-15] : 配置16个DPROT中每一对DPORT中右声道的位置。其中chl_rght_fst [7]代表DPORT15和DPROT14的配置；依次类推，chl_rght_fst [0]代表DPORT1和DPROT0的配置；每bit的含义如下：
                                                        1：代表偶数DPORT为右声道；
                                                        0：代表奇数DPORT为右声道； */
        unsigned int  dat_rght_msb : 8;  /* bit[16-23]: 在数据格式为16bit交织时，配置16个DPROT中每一对DPORT输入数据的左右声道格式。其中dat_rght_msb [7]代表DPORT15和DPROT14的配置；依次类推，dat_rght_msb [0]代表DPORT1和DPROT0的配置；每bit的含义如下：
                                                        1：代表右声道数据在AHB总线32bit位宽输入数据的[31:16]；
                                                        0：代表右声道数据在AHB总线32bit位宽输入数据的[15:0]； */
        unsigned int  dat_rght_fst : 8;  /* bit[24-31]: 在数据格式为24bit数据交织时，配置16个DPROT中每一对DPORT输入左右声道数据的顺序。其中dat_rght_fst [7]代表DPORT15和DPROT14的配置；以此类推dat_rght_fst [0]代表DPORT1和DPROT0的配置；每bit的含义如下：
                                                        1：代表先输入右声道的数据；
                                                        0：代表先输入左声道的数据； */
    } reg;
} SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_bypass_START        (0)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_bypass_END          (0)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_chl_rght_fst_START  (8)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_chl_rght_fst_END    (15)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_msb_START  (16)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_msb_END    (23)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_fst_START  (24)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_fst_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_CLK0_DIV_UNION
 结构说明  : R_CLK0_DIV 寄存器结构定义。地址偏移量:0x01D0，初值:0x0045E7B2，宽度:32
 寄存器说明: 分频比控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_slimbus_clk : 27; /* bit[0-26] : 小数分频系div_slimbus_clk[26:0]，用于产生slimbus_clk_div；
                                                           分频时钟频率=div_slimbus_clk[26:0]/2^27*源时钟频率；
                                                           源时钟是1440M，其选择请参见R_CLK_SEL寄存器的slimbus_clk_sel位；
                                                           源时钟可以被R_GATE_CLKDIV_EN寄存器的gt_slimbus_clk_div位门控； */
        unsigned int  reserved        : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK0_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK0_DIV_div_slimbus_clk_START  (0)
#define SOC_ASP_CFG_R_CLK0_DIV_div_slimbus_clk_END    (26)


/*****************************************************************************
 结构名    : SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION
 结构说明  : R_SECURE_AUTHORITY_EN 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 安全访问属性控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  secure_en_ddr_remap       : 1;  /* bit[0]   : dsp ddr remap相关寄存器的安全访问属性控制
                                                                    1'b0:允许非安全操作配置 ddr remap相关寄存器
                                                                    1'b1:只允许安全操作配置 ddr remap相关寄存器 */
        unsigned int  secure_en_ddr_harq_remap  : 1;  /* bit[1]   : dsp ddr harqp remap相关寄存器的安全访问属性控制
                                                                    1'b0:允许非安全操作配置 ddr harq remap相关寄存器
                                                                    1'b1:只允许安全操作配置 ddr harq remap相关寄存器 */
        unsigned int  secure_en_ddr_mmbuf_remap : 1;  /* bit[2]   : dsp ddr mmbuf remap相关寄存器的安全访问属性控制
                                                                    1'b0:允许非安全操作配置 ddr mmbuf remap相关寄存器
                                                                    1'b1:只允许安全操作配置 ddr mmbuf remap相关寄存器 */
        unsigned int  secure_en_ddr_ocram_remap : 1;  /* bit[3]   : dsp ddr ocram remap相关寄存器的安全访问属性控制
                                                                    1'b0:允许非安全操作配置 ddr ocram remap相关寄存器
                                                                    1'b1:只允许安全操作配置 ddr ocram remap相关寄存器 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION;
#endif
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_remap_START        (0)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_remap_END          (0)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_harq_remap_START   (1)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_harq_remap_END     (1)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_mmbuf_remap_START  (2)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_mmbuf_remap_END    (2)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_ocram_remap_START  (3)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_ocram_remap_END    (3)






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

#endif /* end of soc_asp_cfg_interface.h */
