/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ivp32_dsp_subsys_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:21
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_IVP32_DSP_SUBSYS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IVP32_DSP_SUBSYS_INTERFACE_H__
#define __SOC_IVP32_DSP_SUBSYS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/2) IVP32_CFG_NON_SEC_REG
 ****************************************************************************/
/* 寄存器说明：IVP32 DSP CORE的ID。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_PRID_UNION */
#define SOC_IVP32_DSP_SUBSYS_PRID_ADDR(base)          ((base) + (0x0000))

/* 寄存器说明：On chip debug配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION */
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：片外片内启动模式选择。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：DSP CORE pipeline工作使能。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION */
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_ADDR(base)      ((base) + (0x000C))

/* 寄存器说明：DSP CORE的空闲状态寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION */
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_ADDR(base)     ((base) + (0x0010))

/* 寄存器说明：DSP CORE的外部输入中断状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION */
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_ADDR(base)    ((base) + (0x0100))

/* 寄存器说明：写NMI中断。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_NMI_UNION */
#define SOC_IVP32_DSP_SUBSYS_NMI_ADDR(base)           ((base) + (0x0104))

/* 寄存器说明：DSP CORE的软复位使能配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_ADDR(base) ((base) + (0x0200))

/* 寄存器说明：DSP CORE的软复位撤离配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_ADDR(base) ((base) + (0x0204))

/* 寄存器说明：DSP CORE的软复位状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_ADDR(base) ((base) + (0x0208))

/* 寄存器说明：Timer和WDG的参考时钟选择。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_ADDR(base) ((base) + (0x020C))

/* 寄存器说明：Timer和WDG接口和CNT的工作时钟软门控。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_ADDR(base) ((base) + (0x0210))

/* 寄存器说明：总线自动门控使能。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION */
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ADDR(base) ((base) + (0x0214))

/* 寄存器说明：Timer0~1和WatchDog的软复位使能配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_ADDR(base) ((base) + (0x0218))

/* 寄存器说明：Timer0~1和WatchDog的软复撤离配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_ADDR(base) ((base) + (0x021C))

/* 寄存器说明：Timer0~1和WatchDog的软复状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_ADDR(base) ((base) + (0x0220))

/* 寄存器说明：DSP CORE的软门控。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ADDR(base)  ((base) + (0x0224))

/* 寄存器说明：DSP CORE的软门控状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ADDR(base) ((base) + (0x0228))

/* 寄存器说明：AXI interconnect总线端口优先等级配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ADDR(base) ((base) + (0x030C))

/* 寄存器说明：IVP32 DSP SYSTEM的master接口QoS等级静态配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_ADDR(base) ((base) + (0x0310))

/* 寄存器说明：memory控制信号。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_ADDR(base)     ((base) + (0x0320))

/* 寄存器说明：memory控制信号。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_ADDR(base)     ((base) + (0x0324))

/* 寄存器说明：memory控制信号。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_ADDR(base)     ((base) + (0x0328))

/* 寄存器说明：CRG输出的Timer0~1和WatchDog的接口时钟和计数器软门控状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_ADDR(base) ((base) + (0x032C))

/* 寄存器说明：SMMU的S和prog接口的Awakeup功能Bypass配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_ADDR(base) ((base) + (0x0330))

/* 寄存器说明：SMMU低功耗握手状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_ADDR(base) ((base) + (0x033C))

/* 寄存器说明：Timer0~1和WatchDog的APB接口防挂死逻辑BYPASS配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_ADDR(base) ((base) + (0x0340))

/* 寄存器说明：Address Monitor工作使能配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_ADDR(base)   ((base) + (0x0400))

/* 寄存器说明：Address Monitor中断清除寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_ADDR(base)  ((base) + (0x0404))

/* 寄存器说明：Address Monitor中断使能配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_ADDR(base) ((base) + (0x0408))

/* 寄存器说明：Address Monitor中断状态寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_ADDR(base) ((base) + (0x040C))

/* 寄存器说明：Address Monitor0非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_ADDR(base) ((base) + (0x0410))

/* 寄存器说明：Address Monitor0非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_ADDR(base) ((base) + (0x0414))

/* 寄存器说明：Address Monitor0锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_ADDR(base) ((base) + (0x0418))

/* 寄存器说明：Address Monitor0锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_ADDR(base) ((base) + (0x041C))

/* 寄存器说明：Address Monitor1非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_ADDR(base) ((base) + (0x0420))

/* 寄存器说明：Address Monitor1非法地址访问监控的地址空间大小配置寄存器
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_ADDR(base) ((base) + (0x0424))

/* 寄存器说明：Address Monitor1锁存的写操作非法访问的地址；
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_ADDR(base) ((base) + (0x0428))

/* 寄存器说明：Address Monitor1锁存的读操作非法访问的地址；
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_ADDR(base) ((base) + (0x042C))

/* 寄存器说明：Address Monitor2非法地址访问监控的起始地址配置寄存器
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_ADDR(base) ((base) + (0x0430))

/* 寄存器说明：Address Monitor2非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_ADDR(base) ((base) + (0x0434))

/* 寄存器说明：Address Monitor2锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_ADDR(base) ((base) + (0x0438))

/* 寄存器说明：Address Monitor2锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_ADDR(base) ((base) + (0x043C))

/* 寄存器说明：Address Monitor3非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_ADDR(base) ((base) + (0x0440))

/* 寄存器说明：Address Monitor3非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_ADDR(base) ((base) + (0x0444))

/* 寄存器说明：Address Monitor3锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_ADDR(base) ((base) + (0x0448))

/* 寄存器说明：Address Monitor3锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_ADDR(base) ((base) + (0x044C))

/* 寄存器说明：Address Monitor4非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_ADDR(base) ((base) + (0x0450))

/* 寄存器说明：Address Monitor4非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_ADDR(base) ((base) + (0x0454))

/* 寄存器说明：Address Monitor4锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_ADDR(base) ((base) + (0x0458))

/* 寄存器说明：Address Monitor4锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_ADDR(base) ((base) + (0x045C))

/* 寄存器说明：Address Monitor5非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_ADDR(base) ((base) + (0x0460))

/* 寄存器说明：Address Monitor5非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_ADDR(base) ((base) + (0x0464))

/* 寄存器说明：Address Monitor5锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_ADDR(base) ((base) + (0x0468))

/* 寄存器说明：Address Monitor5锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_ADDR(base) ((base) + (0x046C))

/* 寄存器说明：Address Monitor6非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_ADDR(base) ((base) + (0x0470))

/* 寄存器说明：Address Monitor6非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_ADDR(base) ((base) + (0x0474))

/* 寄存器说明：Address Monitor6锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_ADDR(base) ((base) + (0x0478))

/* 寄存器说明：Address Monitor6锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_ADDR(base) ((base) + (0x047C))

/* 寄存器说明：Address Monitor7非法地址访问监控的起始地址配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_ADDR(base) ((base) + (0x0480))

/* 寄存器说明：Address Monitor7非法地址访问监控的地址空间大小配置寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_ADDR(base) ((base) + (0x0484))

/* 寄存器说明：Address Monitor7锁存的写操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_ADDR(base) ((base) + (0x0488))

/* 寄存器说明：Address Monitor7锁存的读操作非法访问的地址。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_ADDR(base) ((base) + (0x048C))

/* 寄存器说明：SMMU500的TBU和TCU软门控。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_ADDR(base)    ((base) + (0x0500))

/* 寄存器说明：SMMU的TBU和TCU的门控状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_ADDR(base)    ((base) + (0x0504))

/* 寄存器说明：SMMU的TBU和TCU硬件自动门控延时计数器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_ADDR(base) ((base) + (0x050C))

/* 寄存器说明：SMMU的TBU和TCU的软复位使能。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_ADDR(base)   ((base) + (0x0510))

/* 寄存器说明：SMMU的TBU和TCU的软复位撤离。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_ADDR(base)  ((base) + (0x0514))

/* 寄存器说明：SMMU的TBU和TCU的软复位状态。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_ADDR(base)   ((base) + (0x0518))

/* 寄存器说明：子系统版本寄存器。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION */
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_ADDR(base) ((base) + (0x0800))



/****************************************************************************
                     (2/2) IVP32_CFG_SEC_REG
 ****************************************************************************/
/* 寄存器说明：IVP32 DSP的slave接口的安全属性配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ADDR(base) ((base) + (0x0300))

/* 寄存器说明：IVP32 DSP的master接口的安全属性配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_ADDR(base) ((base) + (0x0304))

/* 寄存器说明：APB接口外设安全属性选择。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_ADDR(base) ((base) + (0x0308))

/* 寄存器说明：IVP32 DSP SYSTEM的master接口地址remap起始地址静态配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_ADDR(base) ((base) + (0x0314))

/* 寄存器说明：IVP32 DSP SYSTEM的master接口地址remap大小选择静态配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION */
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_ADDR(base)  ((base) + (0x0318))

/* 寄存器说明：IVP32 DSP SYSTEM的master接口地址remap至DDR的基地址静态配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ADDR(base) ((base) + (0x031C))

/* 寄存器说明：地址remap寄存器安全属性配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ADDR(base) ((base) + (0x0334))

/* 寄存器说明：DSP CORE和Micro-DMA的MID配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_ADDR(base) ((base) + (0x0338))

/* 寄存器说明：SMMU的integ_sec_override信号配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_ADDR(base) ((base) + (0x051C))

/* 寄存器说明：SMMU的spniden信号的配置。
   位域定义UNION结构:  SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_ADDR(base)  ((base) + (0x0520))





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
                     (1/2) IVP32_CFG_NON_SEC_REG
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_PRID_UNION
 结构说明  : PRID 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: IVP32 DSP CORE的ID。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prid     : 16; /* bit[0-15] : processor ID，在多核DSP系统中用于配置DSP的ID；
                                                    我们的系统中只有一个DSP CORE，故可将该信号通过寄存器配置为任意值； */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_PRID_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_PRID_prid_START      (0)
#define SOC_IVP32_DSP_SUBSYS_PRID_prid_END        (15)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION
 结构说明  : OCDHALTONRESET 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: On chip debug配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ocdhaltonreset : 1;  /* bit[0]   : 在Breset撤离时，用于选择DSP CORE的工作模式：
                                                          0：正常模式；
                                                          1：OCDHaltMode，用于debug；
                                                         该信号当processor撤离复位后，工作在normal模式下时，变化没有任何影响； */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ocdhaltonreset_START  (0)
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ocdhaltonreset_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION
 结构说明  : STATVECTORSEL 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 片外片内启动模式选择。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statvectorsel : 1;  /* bit[0]   : 在Breset撤离时，用于选择DSP CORE默认启动方式：
                                                         0：Iram启动；
                                                         1：DDR启动；
                                                        该信号需要在Breset信号拉低前至少10CYCLES稳定，并在Breset信号拉低后至少保持10个CYCLES稳定，否则会导致DSP CORE发生不可预期的状况； */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_statvectorsel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_statvectorsel_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION
 结构说明  : RUNSTALL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000001，宽度:32
 寄存器说明: DSP CORE pipeline工作使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  runstall : 1;  /* bit[0]   : 在Dreset信号拉低后的两拍前，该信号如果高有效，会使processor停止运行；此时，外部的AXI master可以通过IVP32 DSP的AXI slave接口访问Iram和Dram；
                                                   该信号在复位撤离后，并在DSP正常工作一段时间后，如果拉高，也会使DSP的pipeline停止工作，但是不会造成总线挂死。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_runstall_START  (0)
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_runstall_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION
 结构说明  : PWAITMODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: DSP CORE的空闲状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwaitmode : 1;  /* bit[0]   :  */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_pwaitmode_START  (0)
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_pwaitmode_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION
 结构说明  : BINTERRUPT 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: DSP CORE的外部输入中断状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_normal_ns_ipc : 1;  /* bit[0]    : 非安全IPC普通中断状态，高有效 */
        unsigned int  intr0_ns_ipc       : 1;  /* bit[1]    : 非安全IPC快速中断0状态，高有效 */
        unsigned int  intr1_ns_ipc       : 1;  /* bit[2]    : 非安全IPC快速中断1状态，高有效 */
        unsigned int  intr_normal_s_ipc  : 1;  /* bit[3]    : 安全IPC普通中断状态，高有效 */
        unsigned int  intr0_s_ipc        : 1;  /* bit[4]    : 安全IPC快速中断0状态，高有效 */
        unsigned int  intr1_s_ipc        : 1;  /* bit[5]    : 安全IPC快速中断1状态，高有效 */
        unsigned int  intr_timer0_0      : 1;  /* bit[6]    : Timer0_0中断状态，高有效 */
        unsigned int  intr_timer0_1      : 1;  /* bit[7]    : Timer0_1中断状态，高有效 */
        unsigned int  reserved_0         : 1;  /* bit[8]    : 保留 */
        unsigned int  reserved_1         : 1;  /* bit[9]    : 保留 */
        unsigned int  reserved_2         : 1;  /* bit[10]   : 保留 */
        unsigned int  reserved_3         : 1;  /* bit[11]   : 保留 */
        unsigned int  intr_uart_print    : 1;  /* bit[12]   : 打印串口中断状态，高有效 */
        unsigned int  reserved_4         : 1;  /* bit[13]   : 保留 */
        unsigned int  reserved_5         : 1;  /* bit[14]   : 保留 */
        unsigned int  reserved_6         : 1;  /* bit[15]   : 保留 */
        unsigned int  reserved_7         : 1;  /* bit[16]   : 保留 */
        unsigned int  reserved_8         : 1;  /* bit[17]   : 保留 */
        unsigned int  intr_wdg           : 1;  /* bit[18]   : WatchDog中断状态，高有效 */
        unsigned int  intr_timer1_0      : 1;  /* bit[19]   : Timer1_0中断状态，高有效 */
        unsigned int  intr_timer1_1      : 1;  /* bit[20]   : Timer1_1中断状态，高有效 */
        unsigned int  intr_isp           : 1;  /* bit[21]   : ISP中断状态，高有效 */
        unsigned int  reserved_9         : 1;  /* bit[22]   : 保留 */
        unsigned int  reserved_10        : 1;  /* bit[23]   : 保留 */
        unsigned int  reserved_11        : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_ns_ipc_START  (0)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_ns_ipc_END    (0)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_ns_ipc_START        (1)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_ns_ipc_END          (1)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_ns_ipc_START        (2)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_ns_ipc_END          (2)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_s_ipc_START   (3)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_s_ipc_END     (3)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_s_ipc_START         (4)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_s_ipc_END           (4)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_s_ipc_START         (5)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_s_ipc_END           (5)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_0_START       (6)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_0_END         (6)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_1_START       (7)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_1_END         (7)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_uart_print_START     (12)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_uart_print_END       (12)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_wdg_START            (18)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_wdg_END              (18)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_0_START       (19)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_0_END         (19)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_1_START       (20)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_1_END         (20)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_isp_START            (21)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_isp_END              (21)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_NMI_UNION
 结构说明  : NMI 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 写NMI中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nmi      : 16; /* bit[0-15] : 将改寄存器的值按位相或是IVP32 DSP的NMI中断，高有效 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_NMI_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_NMI_nmi_START       (0)
#define SOC_IVP32_DSP_SUBSYS_NMI_nmi_END         (15)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION
 结构说明  : DSP_CORE_RESET_EN 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: DSP CORE的软复位使能配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_en     : 1;  /* bit[0]   : 只有向该寄存器写1，才能软复位DSP CORE的debug逻辑；
                                                           写0无任何意义； */
        unsigned int  rst_processor_en : 1;  /* bit[1]   : 只有向该寄存器写1，才能软复位DSP CORE的processor逻辑；
                                                           写0无任何意义； */
        unsigned int  rst_jtag_en      : 1;  /* bit[2]   : 只有向该寄存器写1，才能软复位DSP CORE的jtag逻辑；
                                                           写0无任何意义； */
        unsigned int  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_debug_en_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_debug_en_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_processor_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_processor_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_jtag_en_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_jtag_en_END         (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION
 结构说明  : DSP_CORE_RESET_DIS 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: DSP CORE的软复位撤离配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_dis     : 1;  /* bit[0]   : 只有向该寄存器写1，才能撤离位DSP CORE的debug逻辑的软复位；
                                                            写0无任何意义； */
        unsigned int  rst_processor_dis : 1;  /* bit[1]   : 只有向该寄存器写1，才能撤离位DSP CORE的processor的软复位；
                                                            写0无任何意义； */
        unsigned int  rst_jtag_dis      : 1;  /* bit[2]   : 只有向该寄存器写1，才能撤离位DSP CORE的jtag的软复位；
                                                            写0无任何意义； */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_debug_dis_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_debug_dis_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_processor_dis_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_processor_dis_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_jtag_dis_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_jtag_dis_END         (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION
 结构说明  : DSP_CORE_RESET_STATUS 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: DSP CORE的软复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_st     : 1;  /* bit[0]   : DSP CORE debug逻辑的复位状态：
                                                           0：复位撤离；
                                                           1：复位有效 */
        unsigned int  rst_processor_st : 1;  /* bit[1]   : DSP CORE processor的复位状态：
                                                           0：复位撤离；
                                                           1：复位有效 */
        unsigned int  rst_jtag_st      : 1;  /* bit[2]   : DSP CORE jtag的复位状态：
                                                           0：复位撤离；
                                                           1：复位有效 */
        unsigned int  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_debug_st_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_debug_st_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_processor_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_processor_st_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_jtag_st_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_jtag_st_END         (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION
 结构说明  : REF_CLOCK_SEL 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
 寄存器说明: Timer和WDG的参考时钟选择。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclk_sel_timer0_0 : 1;  /* bit[0]   : Timer0_0计数器的参考时钟选择：
                                                              0:32KHz参考时钟；
                                                              1:19.2MHz参考时钟； */
        unsigned int  refclk_sel_timer0_1 : 1;  /* bit[1]   : Timer0_1计数器的参考时钟选择：
                                                              0:32KHz参考时钟；
                                                              1:19.2MHz参考时钟； */
        unsigned int  refclk_sel_timer1_0 : 1;  /* bit[2]   : Timer1_0计数器的参考时钟选择：
                                                              0:32KHz参考时钟；
                                                              1:19.2MHz参考时钟； */
        unsigned int  refclk_sel_timer1_1 : 1;  /* bit[3]   : Timer1_1计数器的参考时钟选择：
                                                              0:32KHz参考时钟；
                                                              1:19.2MHz参考时钟； */
        unsigned int  refclk_sel_wdg      : 1;  /* bit[4]   : WatchDog计数器的参考时钟选择：
                                                              0:32KHz参考时钟；
                                                              1:APB 接口时钟，125MHz； */
        unsigned int  reserved            : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_0_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_0_END    (0)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_1_START  (1)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_1_END    (1)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_0_START  (2)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_0_END    (2)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_1_START  (3)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_1_END    (3)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_wdg_START       (4)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_wdg_END         (4)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION
 结构说明  : APB_GATE_CLOCK 寄存器结构定义。地址偏移量:0x0210，初值:0x0000003F，宽度:32
 寄存器说明: Timer和WDG接口和CNT的工作时钟软门控。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_wdg_if     : 1;  /* bit[0]   : WDG接口时钟软门控，用于低功耗，当WDG不使用，或者无访问时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  gt_pclk_wdg_cnt    : 1;  /* bit[1]   : WDG计数器时钟软门控，用于低功耗，当WDG不使用时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  gt_pclk_timer0_if  : 1;  /* bit[2]   : Timer0接口时钟软门控，用于低功耗，当Timer不使用，或者无访问时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  gt_pclk_timer0_cnt : 1;  /* bit[3]   : Timer0计数器时钟软门控，当Timer不使用时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  gt_pclk_timer1_if  : 1;  /* bit[4]   : Timer1接口时钟软门控，用于低功耗，当Timer不使用，或者无访问时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  gt_pclk_timer1_cnt : 1;  /* bit[5]   : Timer1计数器时钟软门控，当Timer不使用时，关闭时钟达到低功耗的目的
                                                             0:关闭时钟；
                                                             1:打开时钟； */
        unsigned int  reserved           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_if_START      (0)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_if_END        (0)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_cnt_START     (1)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_cnt_END       (1)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_if_START   (2)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_if_END     (2)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_cnt_START  (3)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_cnt_END    (3)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_if_START   (4)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_if_END     (4)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_cnt_START  (5)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_cnt_END    (5)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION
 结构说明  : BUS_GATE_CLOCK 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: 总线自动门控使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dw_axi_m1_cg_en      : 1;  /* bit[0]    : dw_axi总线m1接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_m2_cg_en      : 1;  /* bit[1]    : dw_axi总线m2接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_s1_cg_en      : 1;  /* bit[2]    : dw_axi总线s1接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_s2_cg_en      : 1;  /* bit[3]    : dw_axi总线s2接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_s3_cg_en      : 1;  /* bit[4]    : dw_axi总线s3接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_s4_cg_en      : 1;  /* bit[5]    : dw_axi总线s4接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  dw_axi_s5_cg_en      : 1;  /* bit[6]    : dw_axi总线s5接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  defaut_slv_cg_en     : 1;  /* bit[7]    : dw_axi总线default slave接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  x2p_pclk_cg_en       : 1;  /* bit[8]    : x2p桥APB接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  x2p_aclk_cg_en       : 1;  /* bit[9]    : x2p桥AXI接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  ivp32_cfg_pclk_cg_en : 1;  /* bit[10]   : ivp32_cfg模块APB接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控；
                                                                自动门控只负责控制寄存器读写逻辑的时钟，不会门控同步打拍逻辑的时钟； */
        unsigned int  x2x_aclk_cg_en       : 1;  /* bit[11]   : x2x同步桥接口自动门控，属于低功耗设计
                                                                0:关闭自动门控；
                                                                1:打开自动门控； */
        unsigned int  reserved             : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m1_cg_en_START       (0)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m1_cg_en_END         (0)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m2_cg_en_START       (1)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m2_cg_en_END         (1)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s1_cg_en_START       (2)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s1_cg_en_END         (2)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s2_cg_en_START       (3)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s2_cg_en_END         (3)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s3_cg_en_START       (4)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s3_cg_en_END         (4)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s4_cg_en_START       (5)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s4_cg_en_END         (5)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s5_cg_en_START       (6)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s5_cg_en_END         (6)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_defaut_slv_cg_en_START      (7)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_defaut_slv_cg_en_END        (7)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_pclk_cg_en_START        (8)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_pclk_cg_en_END          (8)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_aclk_cg_en_START        (9)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_aclk_cg_en_END          (9)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ivp32_cfg_pclk_cg_en_START  (10)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ivp32_cfg_pclk_cg_en_END    (10)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2x_aclk_cg_en_START        (11)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2x_aclk_cg_en_END          (11)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION
 结构说明  : TIMER_WDG_RST_EN 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: Timer0~1和WatchDog的软复位使能配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_en   : 1;  /* bit[0]   : 只有向该寄存器写1，才能软复位Timer0；
                                                            写0无任何意义； */
        unsigned int  reset_timer1_en   : 1;  /* bit[1]   : 只有向该寄存器写1，才能软复位Timer1；
                                                            写0无任何意义； */
        unsigned int  reset_watchdog_en : 1;  /* bit[2]   : 只有向该寄存器写1，才能软复位WatchDog；
                                                            写0无任何意义； */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer0_en_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer0_en_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer1_en_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer1_en_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_watchdog_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_watchdog_en_END    (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION
 结构说明  : TIMER_WDG_RST_DIS 寄存器结构定义。地址偏移量:0x021C，初值:0x00000000，宽度:32
 寄存器说明: Timer0~1和WatchDog的软复撤离配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_dis   : 1;  /* bit[0]   : 只有向该寄存器写1，才能撤离位Timer0的软复位；
                                                             写0无任何意义； */
        unsigned int  reset_timer1_dis   : 1;  /* bit[1]   : 只有向该寄存器写1，才能撤离位Timer1的软复位；
                                                             写0无任何意义； */
        unsigned int  reset_watchdog_dis : 1;  /* bit[2]   : 只有向该寄存器写1，才能撤离位WatchDog的软复位；
                                                             写0无任何意义； */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer0_dis_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer0_dis_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer1_dis_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer1_dis_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_watchdog_dis_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_watchdog_dis_END    (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION
 结构说明  : TIMER_WDG_RST_STATUS 寄存器结构定义。地址偏移量:0x0220，初值:0x00000007，宽度:32
 寄存器说明: Timer0~1和WatchDog的软复状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_status   : 1;  /* bit[0]   : Timer0的复位状态：
                                                                0：复位有效；
                                                                1：复位撤离 */
        unsigned int  reset_timer1_status   : 1;  /* bit[1]   : Timer1的复位状态：
                                                                0：复位有效；
                                                                1：复位撤离 */
        unsigned int  reset_watchdog_status : 1;  /* bit[2]   : WatchDog的复位状态：
                                                                0：复位有效；
                                                                1：复位撤离 */
        unsigned int  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer0_status_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer0_status_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer1_status_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer1_status_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_watchdog_status_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_watchdog_status_END    (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION
 结构说明  : DSPCORE_GATE 寄存器结构定义。地址偏移量:0x0224，初值:0x00000001，宽度:32
 寄存器说明: DSP CORE的软门控。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_dspcore_gt : 1;  /* bit[0]   : DSP CORE的时钟软门控：
                                                           0:关闭时钟；
                                                           1:打开时钟； */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ivp32_dspcore_gt_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ivp32_dspcore_gt_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION
 结构说明  : DSPCRE_GATE_ST 寄存器结构定义。地址偏移量:0x0228，初值:0x00000001，宽度:32
 寄存器说明: DSP CORE的软门控状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_dspcore_gate_st : 1;  /* bit[0]   : DSP CORE的时钟软门控状态：
                                                                0:关闭时钟；
                                                                1:打开时钟； */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ivp32_dspcore_gate_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ivp32_dspcore_gate_st_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION
 结构说明  : INTERCONNECT_PRIORITY_CFG 寄存器结构定义。地址偏移量:0x030C，初值:0x00000000，宽度:32
 寄存器说明: AXI interconnect总线端口优先等级配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_slv_priority  : 3;  /* bit[0-2]  : 配置AXI interconnect的S1口（连接VIP32 DSP CORE）priority等级，配置在SUBSYS内部slave端口response返回的优先等级：
                                                               3'h0，是最低优先等级，3'h7是最高优先等级； */
        unsigned int  ddr_priority        : 3;  /* bit[3-5]  : 配置AXI interconnect的S2口（连接DDR端口）priority等级，配置在SUBSYS内部该slave端口response返回的优先等级：
                                                               3'h0，是最低优先等级，3'h7是最高优先等级； */
        unsigned int  peri_priority       : 3;  /* bit[6-8]  : 配置AXI interconnect的S3口（连接VTimer0~1、WatchDog和CFG模块）priority等级，配置在SUBSYS内部该slave端口response返回的优先等级：
                                                               3'h0，是最低优先等级，3'h7是最高优先等级； */
        unsigned int  smmu_cfg_priority   : 3;  /* bit[9-11] : 配置AXI interconnect的S4口（连接SMMU配置口）priority等级，配置在SUBSYS内部该slave端口response返回的优先等级：
                                                               3'h0，是最低优先等级，3'h7是最高优先等级； */
        unsigned int  ap_cfg_priority     : 3;  /* bit[12-14]: 配置AXI interconnect的S5口（连接SYS_BUS总线）priority等级，配置在SUBSYS内部该slave端口response返回的优先等级：
                                                               3'h0，是最低优先等级，3'h7是最高优先等级； */
        unsigned int  ivp32_mst_priority  : 1;  /* bit[15]   : 配置AXI interconnect的M1口（连接IVP32_DSP_subsys的master接口）priority等级，配置在SUBSYS内部该master端口访问interconnect S口的优先等级：
                                                               1'b0，是最低优先等级，1'b1是最高优先等级； */
        unsigned int  subsys_cfg_priority : 1;  /* bit[16]   : 配置AXI interconnect的M2口（连接ISYS_BUS的master口）priority等级，配置在SUBSYS内部该master端口访问interconnect S口的优先等级：
                                                               1'b0，是最低优先等级，1'b1是最高优先等级； */
        unsigned int  reserved            : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_slv_priority_START   (0)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_slv_priority_END     (2)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ddr_priority_START         (3)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ddr_priority_END           (5)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_peri_priority_START        (6)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_peri_priority_END          (8)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_smmu_cfg_priority_START    (9)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_smmu_cfg_priority_END      (11)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ap_cfg_priority_START      (12)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ap_cfg_priority_END        (14)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_mst_priority_START   (15)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_mst_priority_END     (15)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_subsys_cfg_priority_START  (16)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_subsys_cfg_priority_END    (16)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION
 结构说明  : IVP32_SYSTEM_QOS_CFG 寄存器结构定义。地址偏移量:0x0310，初值:0x00000000，宽度:32
 寄存器说明: IVP32 DSP SYSTEM的master接口QoS等级静态配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  processor_wr_qos : 4;  /* bit[0-3]  : IVP32 SYSTEM DSP CORE的写通道的QoS等级静态配置 */
        unsigned int  processor_rd_qos : 4;  /* bit[4-7]  : IVP32 SYSTEM DSP CORE的读通道的QoS等级静态配置 */
        unsigned int  micro_dma_wr_qos : 4;  /* bit[8-11] : IVP32 SYSTEM Micro-DMA的写通道的QoS等级静态配置 */
        unsigned int  micro_dma_rd_qos : 4;  /* bit[12-15]: IVP32 SYSTEM Micro-DMA的读通道的QoS等级静态配置 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_wr_qos_START  (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_wr_qos_END    (3)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_rd_qos_START  (4)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_rd_qos_END    (7)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_wr_qos_START  (8)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_wr_qos_END    (11)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_rd_qos_START  (12)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_rd_qos_END    (15)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION
 结构说明  : MEM_CTRL0 寄存器结构定义。地址偏移量:0x0320，初值:0x00A800A8，宽度:32
 寄存器说明: memory控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram1_mem_ctrls : 16; /* bit[0-15] : 同上 */
        unsigned int  iram_mem_ctrls  : 16; /* bit[16-31]: iram的memory controller信号：
                                                           bit0：sleep mode，高有效；
                                                           bit1：deep sleep mode，高有效；deep sleep模式，不会使memory丢失存储内容，只是从deep sleep模式唤醒后需要几个ns的时间才可以使用；
                                                           bit2：shut down，高有效；
                                                           该3bit信号任何bit高有效，则memory处于无效状态，此时对memory的读写是无效的，仿真中读数据为不定态；
                                                           bit3~bit10：值保持不变，不要轻易修改，否则导致memory无法使用；
                                                           bit11~bit15：reserve，无任何意义； */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_dram1_mem_ctrls_START  (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_dram1_mem_ctrls_END    (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_iram_mem_ctrls_START   (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_iram_mem_ctrls_END     (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION
 结构说明  : MEM_CTRL1 寄存器结构定义。地址偏移量:0x0324，初值:0x00A800A8，宽度:32
 寄存器说明: memory控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itag_mem_ctrls  : 16; /* bit[0-15] : 同上 */
        unsigned int  dram0_mem_ctrls : 16; /* bit[16-31]: 同上 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_itag_mem_ctrls_START   (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_itag_mem_ctrls_END     (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_dram0_mem_ctrls_START  (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_dram0_mem_ctrls_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION
 结构说明  : MEM_CTRL2 寄存器结构定义。地址偏移量:0x0328，初值:0x00A800A8，宽度:32
 寄存器说明: memory控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_mem_ctrls   : 16; /* bit[0-15] : 同上 */
        unsigned int  icache_mem_ctrls : 16; /* bit[16-31]: 同上 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_smmu_mem_ctrls_START    (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_smmu_mem_ctrls_END      (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_icache_mem_ctrls_START  (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_icache_mem_ctrls_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION
 结构说明  : CRG_PERI_GT_ST 寄存器结构定义。地址偏移量:0x032C，初值:0x0000003F，宽度:32
 寄存器说明: CRG输出的Timer0~1和WatchDog的接口时钟和计数器软门控状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crg_wdg_if_gt_st     : 1;  /* bit[0]   : WatchDog的APB接口时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  crg_wdg_cnt_gt_st    : 1;  /* bit[1]   : WatchDog的计数器时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  crg_timer0_if_gt_st  : 1;  /* bit[2]   : Timer0的APB接口时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  crg_timer0_cnt_gt_st : 1;  /* bit[3]   : Timer0的计数器时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  crg_timer1_if_gt_st  : 1;  /* bit[4]   : Timer1的APB接口时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  crg_timer1_cnt_gt_st : 1;  /* bit[5]   : Timer1的计数器时钟软门控状态：
                                                               0：时钟处于关闭状态；
                                                               1：时钟处于打开状态； */
        unsigned int  reserved             : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_if_gt_st_START      (0)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_if_gt_st_END        (0)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_cnt_gt_st_START     (1)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_cnt_gt_st_END       (1)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_if_gt_st_START   (2)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_if_gt_st_END     (2)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_cnt_gt_st_START  (3)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_cnt_gt_st_END    (3)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_if_gt_st_START   (4)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_if_gt_st_END     (4)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_cnt_gt_st_START  (5)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_cnt_gt_st_END    (5)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION
 结构说明  : SMMU_AWAKEBYPASS 寄存器结构定义。地址偏移量:0x0330，初值:0x0000000F，宽度:32
 寄存器说明: SMMU的S和prog接口的Awakeup功能Bypass配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_tbu_awake_bypass : 1;  /* bit[0]   : TBU awakeup功能Bypass使能：
                                                                0：使用awakeup功能；
                                                                1：Bypassawakeup功能； */
        unsigned int  smmu_tcu_awake_bypass : 1;  /* bit[1]   : TCU awakeup功能Bypass使能：
                                                                0：使用awakeup功能；
                                                                1：Bypassawakeup功能； */
        unsigned int  smmu_tbu_hwgt_bypass  : 1;  /* bit[2]   : TBU 自动门控功能Bypass使能：
                                                                0：使能自动门控功能（且当smmu_tbu_awake_bypass配置为0时，自动门控才能有效）；
                                                                1：Bypass 自动门控； */
        unsigned int  smmu_tcu_hwgt_bypass  : 1;  /* bit[3]   : TCU 自动门控功能Bypass使能：
                                                                0：使能自动门控功能（且当smmu_tcu_awake_bypass配置为0时，自动门控才能有效）；
                                                                1：Bypass 自动门控； */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_awake_bypass_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_awake_bypass_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_awake_bypass_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_awake_bypass_END    (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_hwgt_bypass_START   (2)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_hwgt_bypass_END     (2)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_hwgt_bypass_START   (3)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_hwgt_bypass_END     (3)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION
 结构说明  : SMMU_PWR_HANDSHAKE_ST 寄存器结构定义。地址偏移量:0x033C，初值:0x00000003，宽度:32
 寄存器说明: SMMU低功耗握手状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_tbu_pwr_handshake_st : 1;  /* bit[0]   : TBU 低功耗握手状态：
                                                                    0：进入低功耗状态；
                                                                    1：退出低功耗状态； */
        unsigned int  smmu_tcu_pwr_handshake_st : 1;  /* bit[1]   : TCU 低功耗握手状态：
                                                                    0：进入低功耗状态；
                                                                    1：退出低功耗状态； */
        unsigned int  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tbu_pwr_handshake_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tbu_pwr_handshake_st_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tcu_pwr_handshake_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tcu_pwr_handshake_st_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION
 结构说明  : APB_IF_DLOCK_BYPASS 寄存器结构定义。地址偏移量:0x0340，初值:0x00000000，宽度:32
 寄存器说明: Timer0~1和WatchDog的APB接口防挂死逻辑BYPASS配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dlock_bp_timer0 : 1;  /* bit[0]   : Timer0的APB接口防挂死逻辑BYPAAS配置：
                                                          0：使能防挂死逻辑；
                                                          1：BYPASS防挂死逻辑； */
        unsigned int  dlock_bp_timer1 : 1;  /* bit[1]   : Timer1的APB接口防挂死逻辑BYPAAS配置：
                                                          0：使能防挂死逻辑；
                                                          1：BYPASS防挂死逻辑； */
        unsigned int  dlock_bp_wdg    : 1;  /* bit[2]   : WatchDog的APB接口防挂死逻辑BYPAAS配置：
                                                          0：使能防挂死逻辑；
                                                          1：BYPASS防挂死逻辑； */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer0_START  (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer0_END    (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer1_START  (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer1_END    (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_wdg_START     (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_wdg_END       (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION
 结构说明  : ADDR_MON_EN 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor工作使能配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_en : 1;  /* bit[0]   : Address Monitor0工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon1_en : 1;  /* bit[1]   : Address Monitor1工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon2_en : 1;  /* bit[2]   : Address Monitor2工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon3_en : 1;  /* bit[3]   : Address Monitor3工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon4_en : 1;  /* bit[4]   : Address Monitor4工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon5_en : 1;  /* bit[5]   : Address Monitor5工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon6_en : 1;  /* bit[6]   : Address Monitor6工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  addr_mon7_en : 1;  /* bit[7]   : Address Monitor7工作使能配置：
                                                       0：Disable Address Monitor；
                                                       1：Enable Address Monitor； */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon0_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon0_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon1_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon1_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon2_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon2_en_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon3_en_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon3_en_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon4_en_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon4_en_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon5_en_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon5_en_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon6_en_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon6_en_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon7_en_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon7_en_END    (7)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION
 结构说明  : ADDR_MON_CLR 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon_clr : 1;  /* bit[0]   : 向改寄存器写“1”，能够清除Address Monitor的中断以及中断状态寄存器的值，同时清除addr_monx_hit_axaddr的值；
                                                       该寄存器不可读； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_addr_mon_clr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_addr_mon_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION
 结构说明  : ADDR_MON_INTR_EN 寄存器结构定义。地址偏移量:0x0408，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor中断使能配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_intr_en : 1;  /* bit[0]   : 同上 */
        unsigned int  addr_mon1_intr_en : 1;  /* bit[1]   : 同上 */
        unsigned int  addr_mon2_intr_en : 1;  /* bit[2]   : 同上 */
        unsigned int  addr_mon3_intr_en : 1;  /* bit[3]   : 同上 */
        unsigned int  addr_mon4_intr_en : 1;  /* bit[4]   : 同上 */
        unsigned int  addr_mon5_intr_en : 1;  /* bit[5]   : 同上 */
        unsigned int  addr_mon6_intr_en : 1;  /* bit[6]   : 同上 */
        unsigned int  addr_mon7_intr_en : 1;  /* bit[7]   : Address Monitor7中断使能配置：
                                                            0：Disable Address Monitor0的中断输出；
                                                            1：Enable Address Monitor的中断输出；
                                                            Address Monitor的中断addr_mon_intr=(addr_mon7_intr_en&(addr_mon7_awhit|addr_mon7_arhit))|(addr_mon6_intr_en&(addr_mon6_awhit|addr_mon6_arhit))|…|(addr_mon0_intr_en&(addr_mon0_awhit|addr_mon0_arhit))；
                                                            即只有address monitor7的中断输出使能有效时，当address monitor7统计到非法地址访问时，addr_mon_intr会拉高有效；当中断使出使能无效时，即使address monitor7统计到非法地址访问，addr_mon_intr仍然不会有效（当其他address monitor没有统计到非法地址访问，或者中断输出使能无效）； */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon0_intr_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon0_intr_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon1_intr_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon1_intr_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon2_intr_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon2_intr_en_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon3_intr_en_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon3_intr_en_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon4_intr_en_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon4_intr_en_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon5_intr_en_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon5_intr_en_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon6_intr_en_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon6_intr_en_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon7_intr_en_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon7_intr_en_END    (7)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION
 结构说明  : ADDR_MON_INTR_STAT 寄存器结构定义。地址偏移量:0x040C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_arhit : 1;  /* bit[0]    : 同上 */
        unsigned int  addr_mon7_awhit : 1;  /* bit[1]    : 同上 */
        unsigned int  addr_mon6_arhit : 1;  /* bit[2]    : 同上 */
        unsigned int  addr_mon6_awhit : 1;  /* bit[3]    : 同上 */
        unsigned int  addr_mon5_arhit : 1;  /* bit[4]    : 同上 */
        unsigned int  addr_mon5_awhit : 1;  /* bit[5]    : 同上 */
        unsigned int  addr_mon4_arhit : 1;  /* bit[6]    : 同上 */
        unsigned int  addr_mon4_awhit : 1;  /* bit[7]    : 同上 */
        unsigned int  addr_mon3_arhit : 1;  /* bit[8]    : 同上 */
        unsigned int  addr_mon3_awhit : 1;  /* bit[9]    : 同上 */
        unsigned int  addr_mon2_arhit : 1;  /* bit[10]   : 同上 */
        unsigned int  addr_mon2_awhit : 1;  /* bit[11]   : 同上 */
        unsigned int  addr_mon1_arhit : 1;  /* bit[12]   : 同上 */
        unsigned int  addr_mon1_awhit : 1;  /* bit[13]   : 同上 */
        unsigned int  addr_mon0_arhit : 1;  /* bit[14]   : Address Monitor0读通道是否有对非法地址的访问命中Address Monitor0的监控范围：
                                                           0：无；
                                                           1：有； */
        unsigned int  addr_mon0_awhit : 1;  /* bit[15]   : Address Monitor0写通道是否有对非法地址的访问命中Address Monitor0的监控范围：
                                                           0：无；
                                                           1：有； */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_arhit_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_arhit_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_awhit_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_awhit_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_arhit_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_arhit_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_awhit_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_awhit_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_arhit_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_arhit_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_awhit_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_awhit_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_arhit_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_arhit_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_awhit_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_awhit_END    (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_arhit_START  (8)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_arhit_END    (8)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_awhit_START  (9)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_awhit_END    (9)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_arhit_START  (10)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_arhit_END    (10)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_awhit_START  (11)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_awhit_END    (11)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_arhit_START  (12)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_arhit_END    (12)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_awhit_START  (13)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_awhit_END    (13)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_arhit_START  (14)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_arhit_END    (14)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_awhit_START  (15)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_awhit_END    (15)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION
 结构说明  : ADDR_MON0_ADDR_BASE 寄存器结构定义。地址偏移量:0x0410，初值:0x000E8000，宽度:32
 寄存器说明: Address Monitor0非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_addr_base : 20; /* bit[0-19] : Address Monitor0非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon0_addr_base，且小于等于addr_mon0_addr_base+addr_mon0_addr_len（Address Monitor0的监控范围）时，则会触发addr_mon0_awhit/addr_mon0_arhit有效；否则，addr_mon0_awhit/addr_mon0_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_addr_mon0_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_addr_mon0_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION
 结构说明  : ADDR_MON0_ADDR_LEN 寄存器结构定义。地址偏移量:0x0414，初值:0x000003FF，宽度:32
 寄存器说明: Address Monitor0非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_addr_len : 20; /* bit[0-19] : Address Monitor0非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon0_addr_base，且小于等于addr_mon0_addr_base+addr_mon0_addr_len（Address Monitor0的监控范围）时，则会触发addr_mon0_awhit/addr_mon0_arhit有效；否则，addr_mon0_awhit/addr_mon0_arhit的值保持不变；
                                                              addr_mon0_addr_len的单位是4KB，即Address Monitor0的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_addr_mon0_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_addr_mon0_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION
 结构说明  : ADDR_MON0_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor0锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_hit_awaddr : 32; /* bit[0-31]: Address Monitor0锁存的写操作非法访问的地址；
                                                               只有当addr_mon0_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_addr_mon0_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_addr_mon0_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION
 结构说明  : ADDR_MON0_HIT_ARADDR 寄存器结构定义。地址偏移量:0x041C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor0锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_hit_araddr : 32; /* bit[0-31]: Address Monitor0锁存的读操作非法访问的地址；
                                                               只有当addr_mon0_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_addr_mon0_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_addr_mon0_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION
 结构说明  : ADDR_MON1_ADDR_BASE 寄存器结构定义。地址偏移量:0x0420，初值:0x000E8500，宽度:32
 寄存器说明: Address Monitor1非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_addr_base : 20; /* bit[0-19] : Address Monitor1非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon1_addr_base，且小于等于addr_mon1_addr_base+addr_mon1_addr_len（Address Monitor1的监控范围）时，则会触发addr_mon1_awhit/addr_mon1_arhit有效；否则，addr_mon1_awhit/addr_mon1_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_addr_mon1_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_addr_mon1_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION
 结构说明  : ADDR_MON1_ADDR_LEN 寄存器结构定义。地址偏移量:0x0424，初值:0x0000010F，宽度:32
 寄存器说明: Address Monitor1非法地址访问监控的地址空间大小配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_addr_len : 20; /* bit[0-19] : Address Monitor1非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon1_addr_base，且小于等于addr_mon1_addr_base+addr_mon1_addr_len（Address Monitor1的监控范围）时，则会触发addr_mon1_awhit/addr_mon1_arhit有效；否则，addr_mon1_awhit/addr_mon1_arhit的值保持不变；
                                                              addr_mon1_addr_len的单位是4KB，即Address Monitor1的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_addr_mon1_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_addr_mon1_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION
 结构说明  : ADDR_MON1_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0428，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor1锁存的写操作非法访问的地址；
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_hit_awaddr : 32; /* bit[0-31]: Address Monitor1锁存的写操作非法访问的地址；
                                                               只有当addr_mon1_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_addr_mon1_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_addr_mon1_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION
 结构说明  : ADDR_MON1_HIT_ARADDR 寄存器结构定义。地址偏移量:0x042C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor1锁存的读操作非法访问的地址；
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_hit_araddr : 32; /* bit[0-31]: Address Monitor1锁存的读操作非法访问的地址；
                                                               只有当addr_mon1_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_addr_mon1_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_addr_mon1_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION
 结构说明  : ADDR_MON2_ADDR_BASE 寄存器结构定义。地址偏移量:0x0430，初值:0x000E8612，宽度:32
 寄存器说明: Address Monitor2非法地址访问监控的起始地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_addr_base : 20; /* bit[0-19] : Address Monitor2非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon2_addr_base，且小于等于addr_mon2_addr_base+addr_mon2_addr_len（Address Monitor2的监控范围）时，则会触发addr_mon2_awhit/addr_mon2_arhit有效；否则，addr_mon2_awhit/addr_mon2_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_addr_mon2_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_addr_mon2_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION
 结构说明  : ADDR_MON2_ADDR_LEN 寄存器结构定义。地址偏移量:0x0434，初值:0x000005ED，宽度:32
 寄存器说明: Address Monitor2非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_addr_len : 20; /* bit[0-19] : Address Monitor2非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon2_addr_base，且小于等于addr_mon2_addr_base+addr_mon2_addr_len（Address Monitor2的监控范围）时，则会触发addr_mon2_awhit/addr_mon2_arhit有效；否则，addr_mon2_awhit/addr_mon2_arhit的值保持不变；
                                                              addr_mon2_addr_len的单位是4KB，即Address Monitor2的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_addr_mon2_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_addr_mon2_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION
 结构说明  : ADDR_MON2_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0438，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor2锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_hit_awaddr : 32; /* bit[0-31]: Address Monitor2锁存的写操作非法访问的地址；
                                                               只有当addr_mon2_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_addr_mon2_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_addr_mon2_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION
 结构说明  : ADDR_MON2_HIT_ARADDR 寄存器结构定义。地址偏移量:0x043C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor2锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_hit_araddr : 32; /* bit[0-31]: Address Monitor2锁存的读操作非法访问的地址；
                                                               只有当addr_mon2_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_addr_mon2_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_addr_mon2_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION
 结构说明  : ADDR_MON3_ADDR_BASE 寄存器结构定义。地址偏移量:0x0440，初值:0x000E8C00，宽度:32
 寄存器说明: Address Monitor3非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_addr_base : 20; /* bit[0-19] : Address Monitor3非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon3_addr_base，且小于等于addr_mon3_addr_base+addr_mon3_addr_len（Address Monitor3的监控范围）时，则会触发addr_mon3_awhit/addr_mon3_arhit有效；否则，addr_mon3_awhit/addr_mon3_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_addr_mon3_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_addr_mon3_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION
 结构说明  : ADDR_MON3_ADDR_LEN 寄存器结构定义。地址偏移量:0x0444，初值:0x0000017F，宽度:32
 寄存器说明: Address Monitor3非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_addr_len : 20; /* bit[0-19] : Address Monitor3非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon3_addr_base，且小于等于addr_mon3_addr_base+addr_mon3_addr_len（Address Monitor3的监控范围）时，则会触发addr_mon3_awhit/addr_mon3_arhit有效；否则，addr_mon3_awhit/addr_mon3_arhit的值保持不变；
                                                              addr_mon3_addr_len的单位是4KB，即Address Monitor3的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_addr_mon3_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_addr_mon3_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION
 结构说明  : ADDR_MON3_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0448，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor3锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_hit_awaddr : 32; /* bit[0-31]: Address Monitor3锁存的写操作非法访问的地址；
                                                               只有当addr_mon3_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_addr_mon3_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_addr_mon3_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION
 结构说明  : ADDR_MON3_HIT_ARADDR 寄存器结构定义。地址偏移量:0x044C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor3锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_hit_araddr : 32; /* bit[0-31]: Address Monitor3锁存的读操作非法访问的地址；
                                                               只有当addr_mon3_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_addr_mon3_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_addr_mon3_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION
 结构说明  : ADDR_MON4_ADDR_BASE 寄存器结构定义。地址偏移量:0x0450，初值:0x000E8D84，宽度:32
 寄存器说明: Address Monitor4非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_addr_base : 20; /* bit[0-19] : Address Monitor4非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon4_addr_base，且小于等于addr_mon4_addr_base+addr_mon4_addr_len（Address Monitor4的监控范围）时，则会触发addr_mon4_awhit/addr_mon4_arhit有效；否则，addr_mon4_awhit/addr_mon4_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_addr_mon4_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_addr_mon4_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION
 结构说明  : ADDR_MON4_ADDR_LEN 寄存器结构定义。地址偏移量:0x0454，初值:0x0000007B，宽度:32
 寄存器说明: Address Monitor4非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_addr_len : 20; /* bit[0-19] : Address Monitor4非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon4_addr_base，且小于等于addr_mon4_addr_base+addr_mon4_addr_len（Address Monitor4的监控范围）时，则会触发addr_mon4_awhit/addr_mon4_arhit有效；否则，addr_mon4_awhit/addr_mon4_arhit的值保持不变；
                                                              addr_mon4_addr_len的单位是4KB，即Address Monitor4的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_addr_mon4_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_addr_mon4_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION
 结构说明  : ADDR_MON4_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0458，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor4锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_hit_awaddr : 32; /* bit[0-31]: Address Monitor4锁存的写操作非法访问的地址；
                                                               只有当addr_mon4_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_addr_mon4_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_addr_mon4_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION
 结构说明  : ADDR_MON4_HIT_ARADDR 寄存器结构定义。地址偏移量:0x045C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor4锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_hit_araddr : 32; /* bit[0-31]: Address Monitor4锁存的读操作非法访问的地址；
                                                               只有当addr_mon4_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_addr_mon4_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_addr_mon4_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION
 结构说明  : ADDR_MON5_ADDR_BASE 寄存器结构定义。地址偏移量:0x0460，初值:0x000E8E00，宽度:32
 寄存器说明: Address Monitor5非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_addr_base : 20; /* bit[0-19] : Address Monitor5非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon5_addr_base，且小于等于addr_mon5_addr_base+addr_mon5_addr_len（Address Monitor5的监控范围）时，则会触发addr_mon5_awhit/addr_mon5_arhit有效；否则，addr_mon5_awhit/addr_mon5_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_addr_mon5_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_addr_mon5_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION
 结构说明  : ADDR_MON5_ADDR_LEN 寄存器结构定义。地址偏移量:0x0464，初值:0x0001622F，宽度:32
 寄存器说明: Address Monitor5非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_addr_len : 20; /* bit[0-19] : Address Monitor5非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon5_addr_base，且小于等于addr_mon5_addr_base+addr_mon5_addr_len（Address Monitor5的监控范围）时，则会触发addr_mon5_awhit/addr_mon5_arhit有效；否则，addr_mon5_awhit/addr_mon5_arhit的值保持不变；
                                                              addr_mon5_addr_len的单位是4KB，即Address Monitor5的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_addr_mon5_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_addr_mon5_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION
 结构说明  : ADDR_MON5_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0468，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor5锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_hit_awaddr : 32; /* bit[0-31]: Address Monitor5锁存的写操作非法访问的地址；
                                                               只有当addr_mon5_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_addr_mon5_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_addr_mon5_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION
 结构说明  : ADDR_MON5_HIT_ARADDR 寄存器结构定义。地址偏移量:0x046C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor5锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_hit_araddr : 32; /* bit[0-31]: Address Monitor5锁存的读操作非法访问的地址；
                                                               只有当addr_mon5_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_addr_mon5_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_addr_mon5_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION
 结构说明  : ADDR_MON6_ADDR_BASE 寄存器结构定义。地址偏移量:0x0470，初值:0x000FF031，宽度:32
 寄存器说明: Address Monitor6非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_addr_base : 20; /* bit[0-19] : Address Monitor6非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon6_addr_base，且小于等于addr_mon6_addr_base+addr_mon6_addr_len（Address Monitor6的监控范围）时，则会触发addr_mon6_awhit/addr_mon6_arhit有效；否则，addr_mon6_awhit/addr_mon6_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_addr_mon6_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_addr_mon6_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION
 结构说明  : ADDR_MON6_ADDR_LEN 寄存器结构定义。地址偏移量:0x0474，初值:0x00000FCE，宽度:32
 寄存器说明: Address Monitor6非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_addr_len : 20; /* bit[0-19] : Address Monitor6非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon6_addr_base，且小于等于addr_mon6_addr_base+addr_mon6_addr_len（Address Monitor6的监控范围）时，则会触发addr_mon6_awhit/addr_mon6_arhit有效；否则，addr_mon6_awhit/addr_mon6_arhit的值保持不变；
                                                              addr_mon6_addr_len的单位是4KB，即Address Monitor6的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_addr_mon6_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_addr_mon6_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION
 结构说明  : ADDR_MON6_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0478，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor6锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_hit_awaddr : 32; /* bit[0-31]: Address Monitor6锁存的写操作非法访问的地址；
                                                               只有当addr_mon6_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_addr_mon6_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_addr_mon6_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION
 结构说明  : ADDR_MON6_HIT_ARADDR 寄存器结构定义。地址偏移量:0x047C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor6锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_hit_araddr : 32; /* bit[0-31]: Address Monitor6锁存的读操作非法访问的地址；
                                                               只有当addr_mon6_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_addr_mon6_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_addr_mon6_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION
 结构说明  : ADDR_MON7_ADDR_BASE 寄存器结构定义。地址偏移量:0x0480，初值:0x000E8000，宽度:32
 寄存器说明: Address Monitor7非法地址访问监控的起始地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_addr_base : 20; /* bit[0-19] : Address Monitor7非法地址访问监控的起始地址，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon7_addr_base，且小于等于addr_mon7_addr_base+addr_mon7_addr_len（Address Monitor7的监控范围）时，则会触发addr_mon7_awhit/addr_mon7_arhit有效；否则，addr_mon7_awhit/addr_mon7_arhit的值保持不变； */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_addr_mon7_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_addr_mon7_addr_base_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION
 结构说明  : ADDR_MON7_ADDR_LEN 寄存器结构定义。地址偏移量:0x0484，初值:0x00000BFF，宽度:32
 寄存器说明: Address Monitor7非法地址访问监控的地址空间大小配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_addr_len : 20; /* bit[0-19] : Address Monitor7非法地址访问监控的地址空间大小，当IVP32 DSP的master接口的访问地址awaddr/araddr的高20bit大于等于addr_mon7_addr_base，且小于等于addr_mon7_addr_base+addr_mon7_addr_len（Address Monitor7的监控范围）时，则会触发addr_mon7_awhit/addr_mon7_arhit有效；否则，addr_mon7_awhit/addr_mon7_arhit的值保持不变；
                                                              addr_mon7_addr_len的单位是4KB，即Address Monitor7的地址监控的精度为4KB； */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_addr_mon7_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_addr_mon7_addr_len_END    (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION
 结构说明  : ADDR_MON7_HIT_AWADDR 寄存器结构定义。地址偏移量:0x0488，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor7锁存的写操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_hit_awaddr : 32; /* bit[0-31]: Address Monitor7锁存的写操作非法访问的地址；
                                                               只有当addr_mon7_awhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_addr_mon7_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_addr_mon7_hit_awaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION
 结构说明  : ADDR_MON7_HIT_ARADDR 寄存器结构定义。地址偏移量:0x048C，初值:0x00000000，宽度:32
 寄存器说明: Address Monitor7锁存的读操作非法访问的地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_hit_araddr : 32; /* bit[0-31]: Address Monitor7锁存的读操作非法访问的地址；
                                                               只有当addr_mon7_arhit有效（等于1）时，该寄存器的值才是有效地。 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_addr_mon7_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_addr_mon7_hit_araddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION
 结构说明  : SMMU_SW_GT 寄存器结构定义。地址偏移量:0x0500，初值:0x00000003，宽度:32
 寄存器说明: SMMU500的TBU和TCU软门控。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_bclk_smmu_soft : 1;  /* bit[0]   : TBU时钟软门控：
                                                            0:关闭时钟；
                                                            1:打开时钟； */
        unsigned int  gt_cclk_smmu_soft : 1;  /* bit[1]   : TCU时钟软门控：
                                                            0:关闭时钟；
                                                            1:打开时钟； */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_bclk_smmu_soft_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_bclk_smmu_soft_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_cclk_smmu_soft_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_cclk_smmu_soft_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION
 结构说明  : SMMU_GT_ST 寄存器结构定义。地址偏移量:0x0504，初值:0x00000003，宽度:32
 寄存器说明: SMMU的TBU和TCU的门控状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_smmu_bclk : 1;  /* bit[0]   : SMMU的TBU的门控状态：
                                                       0：时钟处于关闭状态；
                                                       1：时钟处于打开状态； */
        unsigned int  st_smmu_cclk : 1;  /* bit[1]   : SMMU的TCU的门控状态：
                                                       0：时钟处于关闭状态；
                                                       1：时钟处于打开状态； */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_bclk_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_bclk_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_cclk_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_cclk_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION
 结构说明  : SMMU_HW_GT_CNT 寄存器结构定义。地址偏移量:0x050C，初值:0x00000000，宽度:32
 寄存器说明: SMMU的TBU和TCU硬件自动门控延时计数器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_smmu_bclk_cnt : 6;  /* bit[0-5]  : 用于配置SMMU在自动门控使能时，当TBU空闲时，时钟保持打开状态的时间。 */
        unsigned int  cactive_smmu_cclk_cnt : 6;  /* bit[6-11] : 用于配置SMMU在自动门控使能时，当TCU空闲时，时钟保持打开状态的时间。 */
        unsigned int  reserved              : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_bclk_cnt_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_bclk_cnt_END    (5)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_cclk_cnt_START  (6)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_cclk_cnt_END    (11)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION
 结构说明  : SMMU_RST_EN 寄存器结构定义。地址偏移量:0x0510，初值:0x00000003，宽度:32
 寄存器说明: SMMU的TBU和TCU的软复位使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_en : 1;  /* bit[0]   : 只有向该寄存器写1，才能软复位TBU；
                                                       写0无任何意义； */
        unsigned int  crst_smmu_en : 1;  /* bit[1]   : 只有向该寄存器写1，才能软复位TCU；
                                                       写0无任何意义； */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_brst_smmu_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_brst_smmu_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_crst_smmu_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_crst_smmu_en_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION
 结构说明  : SMMU_RST_DIS 寄存器结构定义。地址偏移量:0x0514，初值:0x00000003，宽度:32
 寄存器说明: SMMU的TBU和TCU的软复位撤离。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_dis : 1;  /* bit[0]   : 只有向该寄存器写1，才能撤离位TBU软复位；
                                                        写0无任何意义； */
        unsigned int  crst_smmu_dis : 1;  /* bit[1]   : 只有向该寄存器写1，才能撤离位TCU软复位；
                                                        写0无任何意义； */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_brst_smmu_dis_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_brst_smmu_dis_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_crst_smmu_dis_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_crst_smmu_dis_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION
 结构说明  : SMMU_RST_ST 寄存器结构定义。地址偏移量:0x0518，初值:0x00000003，宽度:32
 寄存器说明: SMMU的TBU和TCU的软复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_st : 1;  /* bit[0]   : TBU的复位状态：
                                                       0：复位有效；
                                                       1：复位撤离 */
        unsigned int  crst_smmu_st : 1;  /* bit[1]   : TCU的复位状态：
                                                       0：复位有效；
                                                       1：复位撤离 */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_brst_smmu_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_brst_smmu_st_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_crst_smmu_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_crst_smmu_st_END    (1)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION
 结构说明  : SUBSYS_VERSION_NUM 寄存器结构定义。地址偏移量:0x0800，初值:0x0304000D，宽度:32
 寄存器说明: 子系统版本寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subsys_version_num : 32; /* bit[0-31]: 版本寄存器，与版本发布记录的版本序号对应； */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_subsys_version_num_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_subsys_version_num_END    (31)




/****************************************************************************
                     (2/2) IVP32_CFG_SEC_REG
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION
 结构说明  : IVP32_SLV_SEC_SEL 寄存器结构定义。地址偏移量:0x0300，初值:0x00000001，宽度:32
 寄存器说明: IVP32 DSP的slave接口的安全属性配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_slv_sec_sel : 1;  /* bit[0]   : 配置IVP32 DSP的slave接口的安全属性：
                                                            0：安全；
                                                            1：非安全 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ivp32_slv_sec_sel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ivp32_slv_sec_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION
 结构说明  : IVP32_MST_SEC_SEL 寄存器结构定义。地址偏移量:0x0304，初值:0x0000000F，宽度:32
 寄存器说明: IVP32 DSP的master接口的安全属性配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rd_sec_sel       : 1;  /* bit[0]   : 配置Micro-DMA读通道的安全属性：
                                                               0：安全；
                                                               1：非安全 */
        unsigned int  dma_wr_sec_sel       : 1;  /* bit[1]   : 配置Micro-DMA写通道的安全属性：
                                                               0：安全；
                                                               1：非安全 */
        unsigned int  processor_rd_sec_sel : 1;  /* bit[2]   : 配置DSP CORE读通道的安全属性：
                                                               0：安全；
                                                               1：非安全 */
        unsigned int  process_wr_sec_sel   : 1;  /* bit[3]   : 配置DSP CORE写通道的安全属性：
                                                               0：安全；
                                                               1：非安全 */
        unsigned int  reserved             : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_rd_sec_sel_START        (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_rd_sec_sel_END          (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_wr_sec_sel_START        (1)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_wr_sec_sel_END          (1)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_processor_rd_sec_sel_START  (2)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_processor_rd_sec_sel_END    (2)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_process_wr_sec_sel_START    (3)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_process_wr_sec_sel_END      (3)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION
 结构说明  : APB_IF_SEC_SEL 寄存器结构定义。地址偏移量:0x0308，初值:0x000F000F，宽度:32
 寄存器说明: APB接口外设安全属性选择。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer0_if_sec_sel       : 1;  /* bit[0]    : 配置Timer0 APB接口的安全属性：
                                                                   0：安全；
                                                                   1：非安全 */
        unsigned int  timer1_if_sec_sel       : 1;  /* bit[1]    : 配置Timer1 APB接口的安全属性：
                                                                   0：安全；
                                                                   1：非安全 */
        unsigned int  wdg_if_sec_sel          : 1;  /* bit[2]    : 配置WatchDog APB接口的安全属性：
                                                                   0：安全；
                                                                   1：非安全 */
        unsigned int  cfg_if_sec_sel          : 1;  /* bit[3]    : 配置CFG APB接口的安全属性：
                                                                   0：安全；
                                                                   1：非安全 */
        unsigned int  reserved_0              : 12; /* bit[4-15] : 保留 */
        unsigned int  timer0_if_sec_sel_wr_en : 1;  /* bit[16]   : timer0_if_sec_sel寄存器写使能，只有在写该timer0_if_sec_sel寄存器的同时对该bit写1，才可以修改timer0_if_sec_sel的值 */
        unsigned int  timer1_if_sec_sel_wr_en : 1;  /* bit[17]   : timer1_if_sec_sel寄存器写使能，只有在写该timer1_if_sec_sel寄存器的同时对该bit写1，才可以修改timer1_if_sec_sel的值 */
        unsigned int  wdg_if_sec_sel_wr_en    : 1;  /* bit[18]   : wdg_if_sec_sel寄存器写使能，只有在写该wdg_if_sec_sel寄存器的同时对该bit写1，才可以修改wdg_if_sec_sel的值 */
        unsigned int  cfg_if_sec_sel_wr_en    : 1;  /* bit[19]   : cfg_if_sec_sel寄存器写使能，只有在写该cfg_if_sec_sel寄存器的同时对该bit写1，才可以修改cfg_if_sec_sel的值 */
        unsigned int  reserved_1              : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_START        (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_END          (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_START        (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_END          (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_START           (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_END             (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_START           (3)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_END             (3)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_wr_en_START  (16)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_wr_en_END    (16)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_wr_en_START  (17)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_wr_en_END    (17)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_wr_en_START     (18)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_wr_en_END       (18)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_wr_en_START     (19)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_wr_en_END       (19)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION
 结构说明  : START_REMAP_ADDR 寄存器结构定义。地址偏移量:0x0314，初值:0x00000E00，宽度:32
 寄存器说明: IVP32 DSP SYSTEM的master接口地址remap起始地址静态配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_remap_addr : 12; /* bit[0-11] : 该寄存器的值通过与IVP32 DSP SYSTEM的master接口地址ivp32_dsp_mst_addr_base的高12bit比较，来选择remap地址的起点，remap地址精度为1MB：
                                                            默认值为0xE00，表示remap的起始地址为0xE0000000；
                                                            remap逻辑如下：
                                                            if ((ivp32_dsp_mst_addr_base[31:20] >= tart_remap_addr[31:20] ) && (ivp32_dsp_mst_addr_base[31:20] <= start_remap_addr + remap_length) ) 
                                                             ivp32_dsp_mst_addr = ddr_remap_addr + ivp32_dsp_mst_addr_base - start_remap_addr ) else
                                                             ivp32_dsp_mst_addr = ivp32_dsp_mst_addr_base
                                                            其中remap_length和ddr_remap_addr见本表中的寄存器描述。
                                                            注意：
                                                             1.如果从DDR启动IVP，则需要约束该寄存器的配置值必须为0xe00，所以建议该寄存器的默认值最好不要修改；
                                                             2.软件约束的地址范围，即start_remap_addr + remap_length 必须是小于等于0xe7f； */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_start_remap_addr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_start_remap_addr_END    (11)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION
 结构说明  : REMAP_LENGTH 寄存器结构定义。地址偏移量:0x0318，初值:0x0000007F，宽度:32
 寄存器说明: IVP32 DSP SYSTEM的master接口地址remap大小选择静态配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 8;  /* bit[0-7] : 用于配置IVP32 DSP SYSTEM的master接口地址remap的空间大小，单位为1MB；
                                                       如果配置值为n则表示remap的地址范围为(n+1)MB； */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_remap_length_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_remap_length_END    (7)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION
 结构说明  : DDR_REMAP_ADDR 寄存器结构定义。地址偏移量:0x031C，初值:0x00000800，宽度:32
 寄存器说明: IVP32 DSP SYSTEM的master接口地址remap至DDR的基地址静态配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_remap_addr : 12; /* bit[0-11] : 用于配置IVP32 DSP SYSTEM的master接口地址remap至DDR的基地址，精度为1MB；
                                                          默认值为0x800，表示将IVP32 DSP SYSTEM的master接口地址remap至基地址为0x800的DDR地址空间；
                                                          注意：
                                                           remap至DDR的地址空间，即ddr_remap_addr + remap_length 必须是小于等于0xdff； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ddr_remap_addr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ddr_remap_addr_END    (11)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION
 结构说明  : REMAP_SECURITY_CFG 寄存器结构定义。地址偏移量:0x0334，初值:0x00000007，宽度:32
 寄存器说明: 地址remap寄存器安全属性配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_remap_addr_sec_sel : 1;  /* bit[0]   : ddr_remap_addr寄存器安全属性配置：
                                                                   0：安全；
                                                                   1：非安全； */
        unsigned int  remap_length_sec_sel     : 1;  /* bit[1]   : remap_length寄存器安全属性配置：
                                                                   0：安全；
                                                                   1：非安全； */
        unsigned int  ddr_remap_addr_sec_sel   : 1;  /* bit[2]   : start_remap_addr寄存器安全属性配置：
                                                                   0：安全；
                                                                   1：非安全； */
        unsigned int  reserved                 : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_start_remap_addr_sec_sel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_start_remap_addr_sec_sel_END    (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_remap_length_sec_sel_START      (1)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_remap_length_sec_sel_END        (1)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ddr_remap_addr_sec_sel_START    (2)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ddr_remap_addr_sec_sel_END      (2)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION
 结构说明  : IVP32_MST_MID_CFG 寄存器结构定义。地址偏移量:0x0338，初值:0x00000359，宽度:32
 寄存器说明: DSP CORE和Micro-DMA的MID配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_dsp_core_mid  : 5;  /* bit[0-4]  : 配置DSP CORE的MID； */
        unsigned int  cfg_micro_dma_mid : 5;  /* bit[5-9]  : 配置Micro-DMA的MID； */
        unsigned int  reserved          : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_dsp_core_mid_START   (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_dsp_core_mid_END     (4)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_micro_dma_mid_START  (5)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_micro_dma_mid_END    (9)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION
 结构说明  : SMMU_INTEG_SEC_OVERRIDE 寄存器结构定义。地址偏移量:0x051C，初值:0x00000001，宽度:32
 寄存器说明: SMMU的integ_sec_override信号配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  integ_sec_override : 1;  /* bit[0]   : SMMU的integ_sec_override信号，用于安全控制：
                                                             如果配置为0：
                                                              a.TBU接口（IVP32访问DDR）的安全属性可以被透传；
                                                             如果配置为1（此时需要配置spniden寄存器为0）：
                                                              a.所有的集成寄存器可以被非安全操作访问，包括ACR寄存器和DEBUG寄存器；
                                                              b.安全属性寄存器不可被访问；
                                                              c.TBU接口（IVP32访问DDR）的所有操作均被视为非安全操作；
                                                             备注：该信号的值，只有在SMMU复位撤离时刻被采样，复位撤离后再配置，没有任何意义。 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_integ_sec_override_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_integ_sec_override_END    (0)


/*****************************************************************************
 结构名    : SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION
 结构说明  : SMMU_SPNIDEN 寄存器结构定义。地址偏移量:0x0520，初值:0x00000000，宽度:32
 寄存器说明: SMMU的spniden信号的配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spniden  : 1;  /* bit[0]   : SMMU的spniden信号，用于安全操作计数控制：
                                                   0：不对安全操作进行计数；
                                                   1：对安全操作进行计数； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_spniden_START   (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_spniden_END     (0)






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

#endif /* end of soc_ivp32_dsp_subsys_interface.h */
