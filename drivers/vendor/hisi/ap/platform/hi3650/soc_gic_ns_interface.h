/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_gic_ns_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-11 10:13:55
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月11日
    作    者   : w00140341
    修改内容   : 从《Hi3650V100 SOC寄存器手册_GIC_NS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_GIC_NS_INTERFACE_H__
#define __SOC_GIC_NS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) GIC400_NS
 ****************************************************************************/
/* 寄存器说明：Distributor的使能控制
   位域定义UNION结构:  SOC_GIC_NS_GICD_CTLR_NS_UNION */
#define SOC_GIC_NS_GICD_CTLR_NS_ADDR(base)            ((base) + (0x1000))

/* 寄存器说明：中断控制器类型寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_TYPER_UNION */
#define SOC_GIC_NS_GICD_TYPER_ADDR(base)              ((base) + (0x1004))

/* 寄存器说明：分发器集成识别寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_IIDR_UNION */
#define SOC_GIC_NS_GICD_IIDR_ADDR(base)               ((base) + (0x1008))

/* 寄存器说明：中断使能寄存器0（SGI/PPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ISENABLER0_UNION */
#define SOC_GIC_NS_GICD_ISENABLER0_ADDR(base)         ((base) + (0x1100))

/* 寄存器说明：中断使能寄存器（SPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ISENABLERN_UNION */
#define SOC_GIC_NS_GICD_ISENABLERN_ADDR(base, N)      ((base) + (0x1104+(4*(N))))

/* 寄存器说明：中断清除寄存器0（SGI/PPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICENABLER0_UNION */
#define SOC_GIC_NS_GICD_ICENABLER0_ADDR(base)         ((base) + (0x1180))

/* 寄存器说明：中断清除寄存器（SPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICENABLERn_UNION */
#define SOC_GIC_NS_GICD_ICENABLERn_ADDR(base, N)      ((base) + (0x1184+(4*(N))))

/* 寄存器说明：中断Pending设置寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_ISPENDRN_UNION */
#define SOC_GIC_NS_GICD_ISPENDRN_ADDR(base, N)        ((base) + (0x1200+(4*(N))))

/* 寄存器说明：中断Pending清除寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICPENDRn_UNION */
#define SOC_GIC_NS_GICD_ICPENDRn_ADDR(base, N)        ((base) + (0x1280+(4*(N))))

/* 寄存器说明：中断Active设置寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_ISACTIVERn_UNION */
#define SOC_GIC_NS_GICD_ISACTIVERn_ADDR(base, N)      ((base) + (0x1300+(4*(N))))

/* 寄存器说明：中断Active清除寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICACTIVERn_UNION */
#define SOC_GIC_NS_GICD_ICACTIVERn_ADDR(base, N)      ((base) + (0x1380+(4*(N))))

/* 寄存器说明：中断优先级设置寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_IPRIORITYRn_UNION */
#define SOC_GIC_NS_GICD_IPRIORITYRn_ADDR(base, N)     ((base) + (0x1400+(4*(N))))

/* 寄存器说明：中断目标处理器寄存器（SGI and PPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ITARGETSR0_7_UNION */
#define SOC_GIC_NS_GICD_ITARGETSR0_7_ADDR(base, N)    ((base) + (0x1800+(4*(N))))

/* 寄存器说明：中断目标处理器寄存器（SPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ITARGETSRn_UNION */
#define SOC_GIC_NS_GICD_ITARGETSRn_ADDR(base, N)      ((base) + (0x1820+(4*(N))))

/* 寄存器说明：中断配置寄存器（SGI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICFGR0_UNION */
#define SOC_GIC_NS_GICD_ICFGR0_ADDR(base)             ((base) + (0x1C00))

/* 寄存器说明：中断配置寄存器（PPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICFGR1_UNION */
#define SOC_GIC_NS_GICD_ICFGR1_ADDR(base)             ((base) + (0x1C04))

/* 寄存器说明：中断配置寄存器（SPI）
   位域定义UNION结构:  SOC_GIC_NS_GICD_ICFGRn_UNION */
#define SOC_GIC_NS_GICD_ICFGRn_ADDR(base, N)          ((base) + (0x1C08+(4*(N))))

/* 寄存器说明：PPI中断状态寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PPISR_UNION */
#define SOC_GIC_NS_GICD_PPISR_ADDR(base)              ((base) + (0x1D00))

/* 寄存器说明：SPI中断状态寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_SPISRn_UNION */
#define SOC_GIC_NS_GICD_SPISRn_ADDR(base, N)          ((base) + (0x1D04+(4*(N))))

/* 寄存器说明：SGI中断寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_SGIR_UNION */
#define SOC_GIC_NS_GICD_SGIR_ADDR(base)               ((base) + (0x1F00))

/* 寄存器说明：SGI Clear-Pending Registers
   位域定义UNION结构:  SOC_GIC_NS_GICD_CPENDSGIRn_UNION */
#define SOC_GIC_NS_GICD_CPENDSGIRn_ADDR(base, N)      ((base) + (0x1F10+(4*(N))))

/* 寄存器说明：SGI Set-Pending Registers
   位域定义UNION结构:  SOC_GIC_NS_GICD_SPENDSGIRn_UNION */
#define SOC_GIC_NS_GICD_SPENDSGIRn_ADDR(base, N)      ((base) + (0x1F20+(4*(N))))

/* 寄存器说明：外设ID4寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR4_UNION */
#define SOC_GIC_NS_GICD_PIDR4_ADDR(base)              ((base) + (0x1FD0))

/* 寄存器说明：外设ID5寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR5_UNION */
#define SOC_GIC_NS_GICD_PIDR5_ADDR(base)              ((base) + (0x1FD4))

/* 寄存器说明：外设ID6寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR6_UNION */
#define SOC_GIC_NS_GICD_PIDR6_ADDR(base)              ((base) + (0x1FD8))

/* 寄存器说明：外设ID7寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR7_UNION */
#define SOC_GIC_NS_GICD_PIDR7_ADDR(base)              ((base) + (0x1FDC))

/* 寄存器说明：外设ID0寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR0_UNION */
#define SOC_GIC_NS_GICD_PIDR0_ADDR(base)              ((base) + (0x1FE0))

/* 寄存器说明：外设ID1寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR1_UNION */
#define SOC_GIC_NS_GICD_PIDR1_ADDR(base)              ((base) + (0x1FE4))

/* 寄存器说明：外设ID2寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR2_UNION */
#define SOC_GIC_NS_GICD_PIDR2_ADDR(base)              ((base) + (0x1FE8))

/* 寄存器说明：外设ID3寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_PIDR3_UNION */
#define SOC_GIC_NS_GICD_PIDR3_ADDR(base)              ((base) + (0x1FEC))

/* 寄存器说明：模块ID0寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_CIDR0_UNION */
#define SOC_GIC_NS_GICD_CIDR0_ADDR(base)              ((base) + (0x1FF0))

/* 寄存器说明：模块ID1寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_CIDR1_UNION */
#define SOC_GIC_NS_GICD_CIDR1_ADDR(base)              ((base) + (0x1FF4))

/* 寄存器说明：模块ID2寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_CIDR2_UNION */
#define SOC_GIC_NS_GICD_CIDR2_ADDR(base)              ((base) + (0x1FF8))

/* 寄存器说明：模块ID3寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICD_CIDR3_UNION */
#define SOC_GIC_NS_GICD_CIDR3_ADDR(base)              ((base) + (0x1FFC))

/* 寄存器说明：CPU Interface使能以及顶层控制寄存器。（特别注意：GICC_CTLR是banked。此寄存器是在secure access下的备份。和在non_secure 的备份的位分配不一样）。
   位域定义UNION结构:  SOC_GIC_NS_GICC_CTLR_NS_UNION */
#define SOC_GIC_NS_GICC_CTLR_NS_ADDR(base)            ((base) + (0x2000))

/* 寄存器说明：CPU接口优先级屏蔽寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_PMR_UNION */
#define SOC_GIC_NS_GICC_PMR_ADDR(base)                ((base) + (0x2004))

/* 寄存器说明：CPU接口BPR寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_BPR_NS_UNION */
#define SOC_GIC_NS_GICC_BPR_NS_ADDR(base)             ((base) + (0x2008))

/* 寄存器说明：CPU接口中断确认寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_IAR_UNION */
#define SOC_GIC_NS_GICC_IAR_ADDR(base)                ((base) + (0x200C))

/* 寄存器说明：CPU接口中断结束寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_EOIR_UNION */
#define SOC_GIC_NS_GICC_EOIR_ADDR(base)               ((base) + (0x2010))

/* 寄存器说明：CPU接口Running优先级寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_RPR_UNION */
#define SOC_GIC_NS_GICC_RPR_ADDR(base)                ((base) + (0x2014))

/* 寄存器说明：CPU接口最高优先级pending中断寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_HPPIR_UNION */
#define SOC_GIC_NS_GICC_HPPIR_ADDR(base)              ((base) + (0x2018))

/* 寄存器说明：CPU接口识别寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_IIDR_UNION */
#define SOC_GIC_NS_GICC_IIDR_ADDR(base)               ((base) + (0x20FC))

/* 寄存器说明：CPU接口中断Deactivate寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICC_DIR_UNION */
#define SOC_GIC_NS_GICC_DIR_ADDR(base)                ((base) + (0x3000))

/* 寄存器说明：Hypervisor控制寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_HCR_UNION */
#define SOC_GIC_NS_GICH_HCR_ADDR(base)                ((base) + (0x4000))

/* 寄存器说明：VGIC类型寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_VTR_UNION */
#define SOC_GIC_NS_GICH_VTR_ADDR(base)                ((base) + (0x4004))

/* 寄存器说明：Virtual machine控制寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_VMCR_UNION */
#define SOC_GIC_NS_GICH_VMCR_ADDR(base)               ((base) + (0x4008))

/* 寄存器说明：Maintenance中断状态寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_MISR_UNION */
#define SOC_GIC_NS_GICH_MISR_ADDR(base)               ((base) + (0x4010))

/* 寄存器说明：EOI状态寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_EISR0_UNION */
#define SOC_GIC_NS_GICH_EISR0_ADDR(base)              ((base) + (0x4020))

/* 寄存器说明：空list register状态寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_ELSR0_UNION */
#define SOC_GIC_NS_GICH_ELSR0_ADDR(base)              ((base) + (0x4030))

/* 寄存器说明：活跃优先级寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICH_APR0_UNION */
#define SOC_GIC_NS_GICH_APR0_ADDR(base)               ((base) + (0x40F0))

/* 寄存器说明：list register 0
   位域定义UNION结构:  SOC_GIC_NS_GICH_LR0_UNION */
#define SOC_GIC_NS_GICH_LR0_ADDR(base)                ((base) + (0x4100))

/* 寄存器说明：list register 1
   位域定义UNION结构:  SOC_GIC_NS_GICH_LR1_UNION */
#define SOC_GIC_NS_GICH_LR1_ADDR(base)                ((base) + (0x4104))

/* 寄存器说明：list register 2
   位域定义UNION结构:  SOC_GIC_NS_GICH_LR2_UNION */
#define SOC_GIC_NS_GICH_LR2_ADDR(base)                ((base) + (0x4108))

/* 寄存器说明：list register 3
   位域定义UNION结构:  SOC_GIC_NS_GICH_LR3_UNION */
#define SOC_GIC_NS_GICH_LR3_ADDR(base)                ((base) + (0x410C))

/* 寄存器说明：Virtual machine控制寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_CTLR_UNION */
#define SOC_GIC_NS_GICV_CTLR_ADDR(base)               ((base) + (0x6000))

/* 寄存器说明：Virtual machine优先级mask寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_PMR_UNION */
#define SOC_GIC_NS_GICV_PMR_ADDR(base)                ((base) + (0x6004))

/* 寄存器说明：Virtual machine Binary point寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_BPR_UNION */
#define SOC_GIC_NS_GICV_BPR_ADDR(base)                ((base) + (0x6008))

/* 寄存器说明：Virtual machine中断响应寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_IAR_UNION */
#define SOC_GIC_NS_GICV_IAR_ADDR(base)                ((base) + (0x600C))

/* 寄存器说明：Virtual machine EOI寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_EOIR_UNION */
#define SOC_GIC_NS_GICV_EOIR_ADDR(base)               ((base) + (0x6010))

/* 寄存器说明：Virtual machine Running Priority寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_RPR_UNION */
#define SOC_GIC_NS_GICV_RPR_ADDR(base)                ((base) + (0x6014))

/* 寄存器说明：Virtual machine 最高优先级pending中断寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_HPPIR_UNION */
#define SOC_GIC_NS_GICV_HPPIR_ADDR(base)              ((base) + (0x6018))

/* 寄存器说明：Virtual machine aliased Binary point寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_ABPR_UNION */
#define SOC_GIC_NS_GICV_ABPR_ADDR(base)               ((base) + (0x601C))

/* 寄存器说明：Virtual machine aliased中断响应寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_AIAR_UNION */
#define SOC_GIC_NS_GICV_AIAR_ADDR(base)               ((base) + (0x6020))

/* 寄存器说明：Virtual machine aliased EOI寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_AEOIR_UNION */
#define SOC_GIC_NS_GICV_AEOIR_ADDR(base)              ((base) + (0x6024))

/* 寄存器说明：Virtual machine aliased 最高优先级pending中断寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_AHPPIR_UNION */
#define SOC_GIC_NS_GICV_AHPPIR_ADDR(base)             ((base) + (0x6028))

/* 寄存器说明：Virtual machine活跃优先级寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_APR0_UNION */
#define SOC_GIC_NS_GICV_APR0_ADDR(base)               ((base) + (0x60D0))

/* 寄存器说明：Virtual machine CPU接口识别寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_IIDR_UNION */
#define SOC_GIC_NS_GICV_IIDR_ADDR(base)               ((base) + (0x60FC))

/* 寄存器说明：Virtual machine CPU接口中断Deactivate寄存器
   位域定义UNION结构:  SOC_GIC_NS_GICV_DIR_UNION */
#define SOC_GIC_NS_GICV_DIR_ADDR(base)                ((base) + (0x7000))





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
                     (1/1) GIC400_NS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CTLR_NS_UNION
 结构说明  : GICD_CTLR_NS 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: Distributor的使能控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EnableGrp0 : 1;  /* bit[0]   : Distributor的Group0中断的使能控制。 0： Group0中断不使能； 
                                                     1： Group0中断使能。 */
        unsigned int  EnableGrp1 : 1;  /* bit[1]   : Distributor的Group1中断的使能控制。 0： Group1中断不使能； 
                                                     1： Group1中断使能。 */
        unsigned int  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICD_CTLR_NS_UNION;
#endif
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp0_START  (0)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp0_END    (0)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp1_START  (1)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp1_END    (1)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_TYPER_UNION
 结构说明  : GICD_TYPER 寄存器结构定义。地址偏移量:0x1004，初值:0x0000FCE9，宽度:32
 寄存器说明: 中断控制器类型寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ITLinesNumber : 5;  /* bit[0-4]  : 指示GIC支持的中断个数
                                                         00000: 32个中断，不支持外部中断
                                                         00001: 64个中断，其中32个外部中断
                                                         00010: 96个中断，其中64个外部中断
                                                         .
                                                         .
                                                         01111: 512个中断，其中480个外部中断 */
        unsigned int  CPUNumber     : 3;  /* bit[5-7]  : 指示CPU接口的个数
                                                         000: 1
                                                         001: 2
                                                         010: 3
                                                         011: 4
                                                         其他值为后续扩展使用 */
        unsigned int  reserved_0    : 2;  /* bit[8-9]  :  */
        unsigned int  SecurityExtn  : 1;  /* bit[10]   : 指示GIC是否支持安全扩展
                                                         0: 不支持
                                                         1: 支持 */
        unsigned int  LSPI          : 5;  /* bit[11-15]: 返回LSPI(Lockable Shared Peripheral Interrupt)中断个数。
                                                         31 LSPI表示中断ID 32-62
                                                         CFGSDISABLE信号为高，则所有对LSPI相关寄存器操作都被禁止 */
        unsigned int  reserved_1    : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICD_TYPER_UNION;
#endif
#define SOC_GIC_NS_GICD_TYPER_ITLinesNumber_START  (0)
#define SOC_GIC_NS_GICD_TYPER_ITLinesNumber_END    (4)
#define SOC_GIC_NS_GICD_TYPER_CPUNumber_START      (5)
#define SOC_GIC_NS_GICD_TYPER_CPUNumber_END        (7)
#define SOC_GIC_NS_GICD_TYPER_SecurityExtn_START   (10)
#define SOC_GIC_NS_GICD_TYPER_SecurityExtn_END     (10)
#define SOC_GIC_NS_GICD_TYPER_LSPI_START           (11)
#define SOC_GIC_NS_GICD_TYPER_LSPI_END             (15)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_IIDR_UNION
 结构说明  : GICD_IIDR 寄存器结构定义。地址偏移量:0x1008，初值:0x20000000，宽度:32
 寄存器说明: 分发器集成识别寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Implementer : 12; /* bit[0-11] : 开发者
                                                       0x43B: ARM */
        unsigned int  Revision    : 4;  /* bit[12-15]: GIC的副版本号 */
        unsigned int  Variant     : 4;  /* bit[16-19]: GIC的主版本号 */
        unsigned int  reserved    : 4;  /* bit[20-23]: 保留 */
        unsigned int  ProductID   : 8;  /* bit[24-31]: 处理器
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICD_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICD_IIDR_Implementer_START  (0)
#define SOC_GIC_NS_GICD_IIDR_Implementer_END    (11)
#define SOC_GIC_NS_GICD_IIDR_Revision_START     (12)
#define SOC_GIC_NS_GICD_IIDR_Revision_END       (15)
#define SOC_GIC_NS_GICD_IIDR_Variant_START      (16)
#define SOC_GIC_NS_GICD_IIDR_Variant_END        (19)
#define SOC_GIC_NS_GICD_IIDR_ProductID_START    (24)
#define SOC_GIC_NS_GICD_IIDR_ProductID_END      (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ISENABLER0_UNION
 结构说明  : GICD_ISENABLER0 寄存器结构定义。地址偏移量:0x1100，初值:0x0000FFFF，宽度:32
 寄存器说明: 中断使能寄存器0（SGI/PPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setenable : 32; /* bit[0-31]: 每bit控制对应的中断分发使能，此寄存器只针对SGI和SPI中断
                                                    读操作：
                                                    0: 分发禁止
                                                    1: 分发使能
                                                    写操作：
                                                    0: 无效
                                                    1: 使能分发
                                                    注意：对SGI中断相关的bit写无效。对于SGI中断，复位态为使能。由于所有中断复位时处于安全的Group0，所以非安全读返回值为0x00000000,
                                                    只能写1，写0对该寄存器无用 */
    } reg;
} SOC_GIC_NS_GICD_ISENABLER0_UNION;
#endif
#define SOC_GIC_NS_GICD_ISENABLER0_setenable_START  (0)
#define SOC_GIC_NS_GICD_ISENABLER0_setenable_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ISENABLERN_UNION
 结构说明  : GICD_ISENABLERN 寄存器结构定义。地址偏移量:0x1104+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断使能寄存器（SPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setenable : 32; /* bit[0-31]: 每bit控制对应的中断分发使能，此寄存器只针对PPI中断
                                                    读操作：
                                                    0: 分发禁止
                                                    1: 分发使能
                                                    写操作：
                                                    0: 无效
                                                    1: 使能分发
                                                    地址偏移计算方法：
                                                    -> ID为中断号
                                                    -> 每个寄存器的偏移地址为(0x1104+(4*n))，n为ID/32的整数
                                                    -> 每个中断对应寄存器内部的bit为ID/32的余数
                                                    注意：只能写1，写0对该寄存器无用 */
    } reg;
} SOC_GIC_NS_GICD_ISENABLERN_UNION;
#endif
#define SOC_GIC_NS_GICD_ISENABLERN_setenable_START  (0)
#define SOC_GIC_NS_GICD_ISENABLERN_setenable_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICENABLER0_UNION
 结构说明  : GICD_ICENABLER0 寄存器结构定义。地址偏移量:0x1180，初值:0x0000FFFF，宽度:32
 寄存器说明: 中断清除寄存器0（SGI/PPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearEnable : 32; /* bit[0-31]: 每bit控制对应的中断分发禁止，此寄存器只针对SGI和SPI中断
                                                      读操作：
                                                      0: 分发禁止
                                                      1: 分发使能
                                                      写操作：
                                                      0: 无效
                                                      1: 禁止分发
                                                      注意：对SGI中断相关的bit写无效。对于SGI中断，复位态为使能。由于所有中断复位时处于安全的Group0，所以非安全读返回值为0x00000000 */
    } reg;
} SOC_GIC_NS_GICD_ICENABLER0_UNION;
#endif
#define SOC_GIC_NS_GICD_ICENABLER0_ClearEnable_START  (0)
#define SOC_GIC_NS_GICD_ICENABLER0_ClearEnable_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICENABLERn_UNION
 结构说明  : GICD_ICENABLERn 寄存器结构定义。地址偏移量:0x1184+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器（SPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearEnable : 32; /* bit[0-31]: 每bit控制对应的中断分发禁止，此寄存器只针对PPI中断
                                                      读操作：
                                                      0: 分发禁止
                                                      1: 分发使能
                                                      写操作：
                                                      0: 无效
                                                      1: 禁止分发
                                                      地址偏移计算方法：
                                                      -> ID为中断号
                                                      -> 每个寄存器的偏移地址为(0x1184+(4*n))，n为ID/32的整数
                                                      -> 每个中断对应寄存器内部的bit为ID/32的余数 */
    } reg;
} SOC_GIC_NS_GICD_ICENABLERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICENABLERn_ClearEnable_START  (0)
#define SOC_GIC_NS_GICD_ICENABLERn_ClearEnable_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ISPENDRN_UNION
 结构说明  : GICD_ISPENDRN 寄存器结构定义。地址偏移量:0x1200+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断Pending设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SetPending : 32; /* bit[0-31]: 每bit控制对应中断的pending状态，包括active and pending状态。
                                                     读操作：
                                                     0: 非pending状态
                                                     1: pending状态
                                                     写操作（只针对SPI和PPI中断，SGI中断的Pending状态由GICD_SPENDSGIRn寄存器控制）：
                                                     0: 无效
                                                     1: 对于边沿触发和电平触发中断效果不同
                                                      边沿触发:
                                                      - 如果之前为inactive，则进入pending状态
                                                      - 如果之前为active，则进入active and pending状态
                                                      - 如果之前为pending，则无效
                                                      电平触发:
                                                      - 如果之前为inactive，则进入pending状态
                                                      - 如果之前为active，则进入pending and active状态
                                                      - 如果之前为pending，写本寄存器无效，但是在信号撤销之后仍然保持pending状态
                                                     地址偏移计算方法：
                                                     -> ID为中断号
                                                     -> 每个寄存器的偏移地址为(0x1200+(4*n))，n为ID/32的整数
                                                     -> 每个中断对应寄存器内部的bit为ID/32的余数 */
    } reg;
} SOC_GIC_NS_GICD_ISPENDRN_UNION;
#endif
#define SOC_GIC_NS_GICD_ISPENDRN_SetPending_START  (0)
#define SOC_GIC_NS_GICD_ISPENDRN_SetPending_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICPENDRn_UNION
 结构说明  : GICD_ICPENDRn 寄存器结构定义。地址偏移量:0x1280+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断Pending清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearPending : 32; /* bit[0-31]: 每bit清除对应中断的pending状态，包括active and pending状态。
                                                       读操作：
                                                       0: 非pending状态
                                                       1: pending状态
                                                       写操作（只针对SPI和PPI中断，SGI中断的Pending状态由GICD_SPENDSGIRn寄存器控制）：
                                                       0: 无效
                                                       1: 对于边沿触发和电平触发中断效果不同
                                                        边沿触发:
                                                        - 如果之前为pending，则进入inactive状态
                                                        - 如果之前为active and pending，则进入active状态
                                                        - 如果之前为pending，则无效
                                                        电平触发:
                                                        如果中断的pending状态只是由写GICD_ISPENDRn寄存器使能，则：
                                                        - 如果之前为pending，则进入active状态
                                                        - 如果之前为active and pending，则进入active状态
                                                        其他原因的pending使能，只要中断信号有效，则始终保持pending状态
                                                       地址偏移计算方法：
                                                       -> ID为中断号
                                                       -> 每个寄存器的偏移地址为(0x1280+(4*n))，n为ID/32的整数
                                                       -> 每个中断对应寄存器内部的bit为ID/32的余数
                                                       备注：Writes 0 Has no effect. */
    } reg;
} SOC_GIC_NS_GICD_ICPENDRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICPENDRn_ClearPending_START  (0)
#define SOC_GIC_NS_GICD_ICPENDRn_ClearPending_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ISACTIVERn_UNION
 结构说明  : GICD_ISACTIVERn 寄存器结构定义。地址偏移量:0x1300+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断Active设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SetActive : 32; /* bit[0-31]: 每bit使能对应中断的Active状态
                                                    读操作：
                                                     0: No Active
                                                     1: Active
                                                    写操作：
                                                     0: 无效
                                                     1: 如果中断状态没有Active，则进入Active态；如果已经Active，则无效
                                                    地址偏移计算方法：
                                                    -> ID为中断号
                                                    -> 每个寄存器的偏移地址为(0x1300+(4*n))，n为ID/32的整数
                                                    -> 每个中断对应寄存器内部的bit为ID/32的余数 */
    } reg;
} SOC_GIC_NS_GICD_ISACTIVERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ISACTIVERn_SetActive_START  (0)
#define SOC_GIC_NS_GICD_ISACTIVERn_SetActive_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICACTIVERn_UNION
 结构说明  : GICD_ICACTIVERn 寄存器结构定义。地址偏移量:0x1380+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断Active清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearActive : 32; /* bit[0-31]: 每bit清除对应中断的Active状态
                                                      读操作：
                                                       0: No Active
                                                       1: Active
                                                      写操作：
                                                       0: 无效
                                                       1: 如果中断状态已经为Active，则清除Active状态；如果没有Active，则无效
                                                      地址偏移计算方法：
                                                      -> ID为中断号
                                                      -> 每个寄存器的偏移地址为(0x1380+(4*n))，n为ID/32的整数
                                                      -> 每个中断对应寄存器内部的bit为ID/32的余数 */
    } reg;
} SOC_GIC_NS_GICD_ICACTIVERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICACTIVERn_ClearActive_START  (0)
#define SOC_GIC_NS_GICD_ICACTIVERn_ClearActive_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_IPRIORITYRn_UNION
 结构说明  : GICD_IPRIORITYRn 寄存器结构定义。地址偏移量:0x1400+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断优先级设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 4;  /* bit[0-3]  :  */
        unsigned int  Priority_byte_offset0 : 4;  /* bit[4-7]  : Each priority field holds a priority value. The lower the value, the greater the priority of the corresponding interrupt.
                                                                 The GIC-400 implements 32 priority levels in Secure state and 16 priority levels in 
                                                                 Non-secure state. */
        unsigned int  reserved_1            : 4;  /* bit[8-11] :  */
        unsigned int  Priority_byte_offset1 : 4;  /* bit[12-15]:  */
        unsigned int  reserved_2            : 4;  /* bit[16-19]:  */
        unsigned int  Priority_byte_offset2 : 4;  /* bit[20-23]:  */
        unsigned int  reserved_3            : 4;  /* bit[24-27]:  */
        unsigned int  Priority_byte_offset3 : 4;  /* bit[28-31]:  */
    } reg;
} SOC_GIC_NS_GICD_IPRIORITYRn_UNION;
#endif
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset0_START  (4)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset1_START  (12)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset2_START  (20)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset3_START  (28)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ITARGETSR0_7_UNION
 结构说明  : GICD_ITARGETSR0_7 寄存器结构定义。地址偏移量:0x1800+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断目标处理器寄存器（SGI and PPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUtargets_byte_offset0 : 8;  /* bit[0-7]  : Processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means that the Pending 
                                                                   interrupt is sent to processors 0 and 1.
                                                                   For GICD_ITARGETSR0 to GICD_ITARGETSR7, a read of any CPU targets field returns 
                                                                   the number of the processor performing the read */
        unsigned int  CPUtargets_byte_offset1 : 8;  /* bit[8-15] :  */
        unsigned int  CPUtargets_byte_offset2 : 8;  /* bit[16-23]:  */
        unsigned int  CPUtargets_byte_offset3 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_GIC_NS_GICD_ITARGETSR0_7_UNION;
#endif
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset0_START  (0)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset1_START  (8)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset2_START  (16)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset3_START  (24)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ITARGETSRn_UNION
 结构说明  : GICD_ITARGETSRn 寄存器结构定义。地址偏移量:0x1820+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: 中断目标处理器寄存器（SPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUtargets_byte_offset0 : 8;  /* bit[0-7]  : Processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means that the Pending 
                                                                   interrupt is sent to processors 0 and 1.
                                                                   For GICD_ITARGETSR0 to GICD_ITARGETSR7, a read of any CPU targets field returns 
                                                                   the number of the processor performing the read */
        unsigned int  CPUtargets_byte_offset1 : 8;  /* bit[8-15] :  */
        unsigned int  CPUtargets_byte_offset2 : 8;  /* bit[16-23]:  */
        unsigned int  CPUtargets_byte_offset3 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_GIC_NS_GICD_ITARGETSRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset0_START  (0)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset1_START  (8)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset2_START  (16)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset3_START  (24)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset3_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICFGR0_UNION
 结构说明  : GICD_ICFGR0 寄存器结构定义。地址偏移量:0x1C00，初值:0xAAAAAAAA，宽度:32
 寄存器说明: 中断配置寄存器（SGI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGIConfigF0  : 2;  /* bit[0-1]  :  */
        unsigned int  SGIConfigF1  : 2;  /* bit[2-3]  :  */
        unsigned int  SGIConfigF2  : 2;  /* bit[4-5]  :  */
        unsigned int  SGIConfigF3  : 2;  /* bit[6-7]  :  */
        unsigned int  SGIConfigF4  : 2;  /* bit[8-9]  :  */
        unsigned int  SGIConfigF5  : 2;  /* bit[10-11]:  */
        unsigned int  SGIConfigF6  : 2;  /* bit[12-13]:  */
        unsigned int  SGIConfigF7  : 2;  /* bit[14-15]:  */
        unsigned int  SGIConfigF8  : 2;  /* bit[16-17]:  */
        unsigned int  SGIConfigF9  : 2;  /* bit[18-19]:  */
        unsigned int  SGIConfigF10 : 2;  /* bit[20-21]:  */
        unsigned int  SGIConfigF11 : 2;  /* bit[22-23]:  */
        unsigned int  SGIConfigF12 : 2;  /* bit[24-25]:  */
        unsigned int  SGIConfigF13 : 2;  /* bit[26-27]:  */
        unsigned int  SGIConfigF14 : 2;  /* bit[28-29]:  */
        unsigned int  SGIConfigF15 : 2;  /* bit[30-31]: 每2bit为一个offset，分别对应SGI中断0~15的配置
                                                        bit[0]: reserved
                                                        bit[1]: 表示中断的触发状态
                                                         0: 电平触发
                                                         1: 边沿触发 */
    } reg;
} SOC_GIC_NS_GICD_ICFGR0_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF0_START   (0)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF0_END     (1)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF1_START   (2)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF1_END     (3)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF2_START   (4)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF2_END     (5)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF3_START   (6)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF3_END     (7)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF4_START   (8)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF4_END     (9)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF5_START   (10)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF5_END     (11)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF6_START   (12)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF6_END     (13)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF7_START   (14)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF7_END     (15)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF8_START   (16)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF8_END     (17)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF9_START   (18)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF9_END     (19)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF10_START  (20)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF10_END    (21)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF11_START  (22)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF11_END    (23)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF12_START  (24)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF12_END    (25)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF13_START  (26)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF13_END    (27)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF14_START  (28)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF14_END    (29)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF15_START  (30)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF15_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICFGR1_UNION
 结构说明  : GICD_ICFGR1 寄存器结构定义。地址偏移量:0x1C04，初值:0x55540000，宽度:32
 寄存器说明: 中断配置寄存器（PPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PPIConfig0  : 2;  /* bit[0-1]  :  */
        unsigned int  PPIConfig1  : 2;  /* bit[2-3]  :  */
        unsigned int  PPIConfig2  : 2;  /* bit[4-5]  :  */
        unsigned int  PPIConfig3  : 2;  /* bit[6-7]  :  */
        unsigned int  PPIConfig4  : 2;  /* bit[8-9]  :  */
        unsigned int  PPIConfig5  : 2;  /* bit[10-11]:  */
        unsigned int  PPIConfig6  : 2;  /* bit[12-13]:  */
        unsigned int  PPIConfig7  : 2;  /* bit[14-15]:  */
        unsigned int  PPIConfig8  : 2;  /* bit[16-17]:  */
        unsigned int  PPIConfig9  : 2;  /* bit[18-19]:  */
        unsigned int  PPIConfig10 : 2;  /* bit[20-21]:  */
        unsigned int  PPIConfig11 : 2;  /* bit[22-23]:  */
        unsigned int  PPIConfig12 : 2;  /* bit[24-25]:  */
        unsigned int  PPIConfig13 : 2;  /* bit[26-27]:  */
        unsigned int  PPIConfig14 : 2;  /* bit[28-29]:  */
        unsigned int  PPIConfig15 : 2;  /* bit[30-31]: 每2bit为一个offset，分别对应PPI中断0~15的配置
                                                       bit[0]: reserved
                                                       bit[1]: 表示中断的触发状态
                                                        0: 电平触发
                                                        1: 边沿触发 */
    } reg;
} SOC_GIC_NS_GICD_ICFGR1_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig0_START   (0)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig0_END     (1)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig1_START   (2)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig1_END     (3)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig2_START   (4)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig2_END     (5)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig3_START   (6)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig3_END     (7)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig4_START   (8)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig4_END     (9)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig5_START   (10)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig5_END     (11)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig6_START   (12)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig6_END     (13)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig7_START   (14)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig7_END     (15)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig8_START   (16)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig8_END     (17)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig9_START   (18)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig9_END     (19)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig10_START  (20)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig10_END    (21)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig11_START  (22)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig11_END    (23)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig12_START  (24)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig12_END    (25)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig13_START  (26)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig13_END    (27)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig14_START  (28)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig14_END    (29)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig15_START  (30)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig15_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_ICFGRn_UNION
 结构说明  : GICD_ICFGRn 寄存器结构定义。地址偏移量:0x1C08+(4*(N))，初值:0x55540000，宽度:32
 寄存器说明: 中断配置寄存器（SPI）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PPIConfig0  : 2;  /* bit[0-1]  :  */
        unsigned int  PPIConfig1  : 2;  /* bit[2-3]  :  */
        unsigned int  PPIConfig2  : 2;  /* bit[4-5]  :  */
        unsigned int  PPIConfig3  : 2;  /* bit[6-7]  :  */
        unsigned int  PPIConfig4  : 2;  /* bit[8-9]  :  */
        unsigned int  PPIConfig5  : 2;  /* bit[10-11]:  */
        unsigned int  PPIConfig6  : 2;  /* bit[12-13]:  */
        unsigned int  PPIConfig7  : 2;  /* bit[14-15]:  */
        unsigned int  PPIConfig8  : 2;  /* bit[16-17]:  */
        unsigned int  PPIConfig9  : 2;  /* bit[18-19]:  */
        unsigned int  PPIConfig10 : 2;  /* bit[20-21]:  */
        unsigned int  PPIConfig11 : 2;  /* bit[22-23]:  */
        unsigned int  PPIConfig12 : 2;  /* bit[24-25]:  */
        unsigned int  PPIConfig13 : 2;  /* bit[26-27]:  */
        unsigned int  PPIConfig14 : 2;  /* bit[28-29]:  */
        unsigned int  PPIConfig15 : 2;  /* bit[30-31]: 每2bit为一个offset，分别对应PPI中断0~15的配置
                                                       bit[0]: reserved
                                                       bit[1]: 表示中断的触发状态
                                                        0: 电平触发
                                                        1: 边沿触发 */
    } reg;
} SOC_GIC_NS_GICD_ICFGRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig0_START   (0)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig0_END     (1)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig1_START   (2)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig1_END     (3)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig2_START   (4)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig2_END     (5)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig3_START   (6)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig3_END     (7)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig4_START   (8)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig4_END     (9)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig5_START   (10)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig5_END     (11)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig6_START   (12)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig6_END     (13)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig7_START   (14)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig7_END     (15)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig8_START   (16)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig8_END     (17)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig9_START   (18)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig9_END     (19)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig10_START  (20)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig10_END    (21)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig11_START  (22)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig11_END    (23)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig12_START  (24)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig12_END    (25)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig13_START  (26)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig13_END    (27)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig14_START  (28)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig14_END    (29)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig15_START  (30)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig15_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PPISR_UNION
 结构说明  : GICD_PPISR 寄存器结构定义。地址偏移量:0x1D00，初值:0x00000000，宽度:32
 寄存器说明: PPI中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 9;  /* bit[0-8]  :  */
        unsigned int  PPIStatus : 7;  /* bit[9-15] : 指示PPI中断的当前状态
                                                     0: PPI0 - nFIQ
                                                     1: PPI1 - Secure physical timer event
                                                     2: PPI2 - Non-secure physical timer event
                                                     3: PPI3 - nIRQ
                                                     4: PPI4 - Virtual timer event
                                                     5: PPI5 - Hypervisor timer event
                                                     6: PPI6 - Virtual Maintenance Interrupt */
        unsigned int  reserved_1: 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICD_PPISR_UNION;
#endif
#define SOC_GIC_NS_GICD_PPISR_PPIStatus_START  (9)
#define SOC_GIC_NS_GICD_PPISR_PPIStatus_END    (15)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_SPISRn_UNION
 结构说明  : GICD_SPISRn 寄存器结构定义。地址偏移量:0x1D04+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: SPI中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IRQS : 32; /* bit[0-31]: 指示SPI中断的当前状态。每bit对应一个SPI中断。
                                               地址偏移计算方法：
                                               -> ID为中断号
                                               -> 每个寄存器的偏移地址为(0x1D04+(4*n))，n为ID/32的整数
                                               -> 每个中断对应寄存器内部的bit为ID/32的余数 */
    } reg;
} SOC_GIC_NS_GICD_SPISRn_UNION;
#endif
#define SOC_GIC_NS_GICD_SPISRn_IRQS_START  (0)
#define SOC_GIC_NS_GICD_SPISRn_IRQS_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_SGIR_UNION
 结构说明  : GICD_SGIR 寄存器结构定义。地址偏移量:0x1F00，初值:0x00000000，宽度:32
 寄存器说明: SGI中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGIINTID         : 4;  /* bit[0-3]  : 定义需要分发到特定CPU接口的SGI中断号，范围为0~15 */
        unsigned int  reserved_0       : 11; /* bit[4-14] : 保留 */
        unsigned int  NSATT            : 1;  /* bit[15]   : SGI中断的安全相关配置：
                                                            0: 只有当针对某个CPU接口，SGI中断被配置为Group0，则将SGIINTID指示的中断分发到对应的CPU接口
                                                            1: 只有针对某个CPU接口，SGI中断被配置为Group0，则将SGIINTID指示的中断分发到对应的CPU接口 */
        unsigned int  CPUTargetList    : 8;  /* bit[16-23]: 指示中断目标处理器对应的CPU接口，每bit表示一个CPU接口，例如CPUTargetList[0]对应CPU接口0。如果为全零，则中断不分发 */
        unsigned int  TargetListFilter : 2;  /* bit[24-25]: 指定Distributor如何操作SGI中断
                                                            00: 将中断分发到CPUTargetList中指定的CPU接口
                                                            01: 将中断分发到除被请求处理器对应的CPU接口以外的所有CPU接口
                                                            10: 将中断只分发到被请求处理器对应的CPU接口
                                                            11: 保留 */
        unsigned int  reserved_1       : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICD_SGIR_UNION;
#endif
#define SOC_GIC_NS_GICD_SGIR_SGIINTID_START          (0)
#define SOC_GIC_NS_GICD_SGIR_SGIINTID_END            (3)
#define SOC_GIC_NS_GICD_SGIR_NSATT_START             (15)
#define SOC_GIC_NS_GICD_SGIR_NSATT_END               (15)
#define SOC_GIC_NS_GICD_SGIR_CPUTargetList_START     (16)
#define SOC_GIC_NS_GICD_SGIR_CPUTargetList_END       (23)
#define SOC_GIC_NS_GICD_SGIR_TargetListFilter_START  (24)
#define SOC_GIC_NS_GICD_SGIR_TargetListFilter_END    (25)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CPENDSGIRn_UNION
 结构说明  : GICD_CPENDSGIRn 寄存器结构定义。地址偏移量:0x1F10+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: SGI Clear-Pending Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGI_clear_pending_bits : 32; /* bit[0-31]: For each bit:
                                                                 Reads 0 SGI x from the corresponding processor is not pendinga.
                                                                  1 SGI x from the corresponding processor is pendinga.
                                                                 Writes 0 Has no effect.
                                                                  1 Removes the pending state of SGI x for the corresponding processor. */
    } reg;
} SOC_GIC_NS_GICD_CPENDSGIRn_UNION;
#endif
#define SOC_GIC_NS_GICD_CPENDSGIRn_SGI_clear_pending_bits_START  (0)
#define SOC_GIC_NS_GICD_CPENDSGIRn_SGI_clear_pending_bits_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_SPENDSGIRn_UNION
 结构说明  : GICD_SPENDSGIRn 寄存器结构定义。地址偏移量:0x1F20+(4*(N))，初值:0x00000000，宽度:32
 寄存器说明: SGI Set-Pending Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGI_set_pending_bits : 32; /* bit[0-31]: For each bit:
                                                               Reads 0 SGI x for the corresponding processor is not pendinga.
                                                                1 SGI x for the corresponding processor is pendinga.
                                                               Writes 0 Has no effect.
                                                                1 Adds the pending state of SGI x for the corresponding processor
                                                               if it is not already pending. If SGI x is already pending for the corresponding processor then the write has no effect. */
    } reg;
} SOC_GIC_NS_GICD_SPENDSGIRn_UNION;
#endif
#define SOC_GIC_NS_GICD_SPENDSGIRn_SGI_set_pending_bits_START  (0)
#define SOC_GIC_NS_GICD_SPENDSGIRn_SGI_set_pending_bits_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR4_UNION
 结构说明  : GICD_PIDR4 寄存器结构定义。地址偏移量:0x1FD0，初值:0x00000004，宽度:32
 寄存器说明: 外设ID4寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  continuationcode       : 4;  /* bit[0-3] :  */
        unsigned int  reserved               : 4;  /* bit[4-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR4_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR4_continuationcode_START        (0)
#define SOC_GIC_NS_GICD_PIDR4_continuationcode_END          (3)
#define SOC_GIC_NS_GICD_PIDR4_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR4_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR5_UNION
 结构说明  : GICD_PIDR5 寄存器结构定义。地址偏移量:0x1FD4，初值:0x00000000，宽度:32
 寄存器说明: 外设ID5寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR5_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR5_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR5_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR6_UNION
 结构说明  : GICD_PIDR6 寄存器结构定义。地址偏移量:0x1FD8，初值:0x00000000，宽度:32
 寄存器说明: 外设ID6寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR6_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR6_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR6_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR7_UNION
 结构说明  : GICD_PIDR7 寄存器结构定义。地址偏移量:0x1FDC，初值:0x00000000，宽度:32
 寄存器说明: 外设ID7寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR7_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR7_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR7_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR0_UNION
 结构说明  : GICD_PIDR0 寄存器结构定义。地址偏移量:0x1FE0，初值:0x00000090，宽度:32
 寄存器说明: 外设ID0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devid_7_0              : 8;  /* bit[0-7] : Bits [7:0] of the ARM-defined DevID field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR0_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR0_devid_7_0_START               (0)
#define SOC_GIC_NS_GICD_PIDR0_devid_7_0_END                 (7)
#define SOC_GIC_NS_GICD_PIDR0_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR0_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR1_UNION
 结构说明  : GICD_PIDR1 寄存器结构定义。地址偏移量:0x1FE4，初值:0x000000B4，宽度:32
 寄存器说明: 外设ID1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devid_11_8             : 4;  /* bit[0-3] : Bits [11:8] of the ARM-defined DevID field */
        unsigned int  archid_3_0             : 4;  /* bit[4-7] : Bits [3:0] of the ARM-defined ArchID field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR1_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR1_devid_11_8_START              (0)
#define SOC_GIC_NS_GICD_PIDR1_devid_11_8_END                (3)
#define SOC_GIC_NS_GICD_PIDR1_archid_3_0_START              (4)
#define SOC_GIC_NS_GICD_PIDR1_archid_3_0_END                (7)
#define SOC_GIC_NS_GICD_PIDR1_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR1_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR2_UNION
 结构说明  : GICD_PIDR2 寄存器结构定义。地址偏移量:0x1FE8，初值:0x0000002B，宽度:32
 寄存器说明: 外设ID2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  archid_6_4             : 3;  /* bit[0-2] : Bits [6:4] of the ARM-defined ArchID field */
        unsigned int  UsesJEPcode            : 1;  /* bit[3]   : ARM-defined UsesJEPcode field */
        unsigned int  ArchRev                : 4;  /* bit[4-7] : ArchRev field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR2_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR2_archid_6_4_START              (0)
#define SOC_GIC_NS_GICD_PIDR2_archid_6_4_END                (2)
#define SOC_GIC_NS_GICD_PIDR2_UsesJEPcode_START             (3)
#define SOC_GIC_NS_GICD_PIDR2_UsesJEPcode_END               (3)
#define SOC_GIC_NS_GICD_PIDR2_ArchRev_START                 (4)
#define SOC_GIC_NS_GICD_PIDR2_ArchRev_END                   (7)
#define SOC_GIC_NS_GICD_PIDR2_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR2_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_PIDR3_UNION
 结构说明  : GICD_PIDR3 寄存器结构定义。地址偏移量:0x1FEC，初值:0x00000000，宽度:32
 寄存器说明: 外设ID3寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  Revision               : 4;  /* bit[4-7] : ARM-defined Revision field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR3_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR3_Revision_START                (4)
#define SOC_GIC_NS_GICD_PIDR3_Revision_END                  (7)
#define SOC_GIC_NS_GICD_PIDR3_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR3_implementation_defined_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CIDR0_UNION
 结构说明  : GICD_CIDR0 寄存器结构定义。地址偏移量:0x1FF0，初值:0x0000000D，宽度:32
 寄存器说明: 模块ID0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: 模块ID0寄存器 */
    } reg;
} SOC_GIC_NS_GICD_CIDR0_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR0_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR0_Component_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CIDR1_UNION
 结构说明  : GICD_CIDR1 寄存器结构定义。地址偏移量:0x1FF4，初值:0x000000F0，宽度:32
 寄存器说明: 模块ID1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: 模块ID1寄存器 */
    } reg;
} SOC_GIC_NS_GICD_CIDR1_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR1_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR1_Component_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CIDR2_UNION
 结构说明  : GICD_CIDR2 寄存器结构定义。地址偏移量:0x1FF8，初值:0x00000005，宽度:32
 寄存器说明: 模块ID2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: 模块ID2寄存器 */
    } reg;
} SOC_GIC_NS_GICD_CIDR2_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR2_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR2_Component_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICD_CIDR3_UNION
 结构说明  : GICD_CIDR3 寄存器结构定义。地址偏移量:0x1FFC，初值:0x000000B1，宽度:32
 寄存器说明: 模块ID3寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: 模块ID3寄存器 */
    } reg;
} SOC_GIC_NS_GICD_CIDR3_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR3_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR3_Component_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_CTLR_NS_UNION
 结构说明  : GICC_CTLR_NS 寄存器结构定义。地址偏移量:0x2000，初值:0x00000000，宽度:32
 寄存器说明: CPU Interface使能以及顶层控制寄存器。（特别注意：GICC_CTLR是banked。此寄存器是在secure access下的备份。和在non_secure 的备份的位分配不一样）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enablegrp1    : 1;  /* bit[0]    : 对Group1的中断而言， 
                                                         0：不使能该中断 
                                                         1：使能该中断 */
        unsigned int  reserved_0    : 4;  /* bit[1-4]  : reserved */
        unsigned int  fiqbypdisgrp1 : 1;  /* bit[5]    : 当FIQs不使能时， 
                                                         0：Bypass FIQ被送到处理器核 
                                                         1：Bypass FIQ不被送到处理器核 */
        unsigned int  irqbypdisgrp1 : 1;  /* bit[6]    : 当IRQs不使能时， 
                                                         0：Bypass IRQ被送到处理器核 
                                                         1：Bypass IRQ不被送到处理器核 */
        unsigned int  reserved_1    : 2;  /* bit[7-8]  : reserved */
        unsigned int  eoimodens     : 1;  /* bit[9]    : 当访问为非安全访问时： 
                                                         0：访问GICC_EOIR可以完成priority drop和deactive 
                                                         1：访问GICC_EOIR只能完成priority drop，而deactive则通过访问GICC_DIR完成。 */
        unsigned int  reserved_2    : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICC_CTLR_NS_UNION;
#endif
#define SOC_GIC_NS_GICC_CTLR_NS_enablegrp1_START     (0)
#define SOC_GIC_NS_GICC_CTLR_NS_enablegrp1_END       (0)
#define SOC_GIC_NS_GICC_CTLR_NS_fiqbypdisgrp1_START  (5)
#define SOC_GIC_NS_GICC_CTLR_NS_fiqbypdisgrp1_END    (5)
#define SOC_GIC_NS_GICC_CTLR_NS_irqbypdisgrp1_START  (6)
#define SOC_GIC_NS_GICC_CTLR_NS_irqbypdisgrp1_END    (6)
#define SOC_GIC_NS_GICC_CTLR_NS_eoimodens_START      (9)
#define SOC_GIC_NS_GICC_CTLR_NS_eoimodens_END        (9)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_PMR_UNION
 结构说明  : GICC_PMR 寄存器结构定义。地址偏移量:0x2004，初值:0x00000000，宽度:32
 寄存器说明: CPU接口优先级屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  priority_low : 3;  /* bit[0-2] : For GIC-400 there is just 32 Priority Level, so the bit[2:0] should read as zero */
        unsigned int  priority     : 5;  /* bit[3-7] : CPU接口优先级屏蔽的等级。当中断优先级高于此寄存器的值，则将中断送给目标处理器。最高支持256个优先级。
                                                       0x00-0xFF(0-255): 256个等级
                                                       0x00-0xFE(0-254): 128个等级（偶数）
                                                       0x00-0xFC(0-252): 64个等级（步进为4）
                                                       0x00-0xF8(0-248): 32个等级（步进为8）
                                                       0x00-0xF0(0-240): 16个等级（步进为16）
                                                       当配置为0xFF时，表示所有中断都不屏蔽 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICC_PMR_UNION;
#endif
#define SOC_GIC_NS_GICC_PMR_priority_low_START  (0)
#define SOC_GIC_NS_GICC_PMR_priority_low_END    (2)
#define SOC_GIC_NS_GICC_PMR_priority_START      (3)
#define SOC_GIC_NS_GICC_PMR_priority_END        (7)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_BPR_NS_UNION
 结构说明  : GICC_BPR_NS 寄存器结构定义。地址偏移量:0x2008，初值:0x00000003，宽度:32
 寄存器说明: CPU接口BPR寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  binarypoint : 3;  /* bit[0-2] : 控制8-bit中断优先级域如何对应用于定义中断抢占操作的group优先级域，以及子优先级域
                                                      注：非安全访问，默认值为0x3 */
        unsigned int  reserved    : 29; /* bit[3-31]:  */
    } reg;
} SOC_GIC_NS_GICC_BPR_NS_UNION;
#endif
#define SOC_GIC_NS_GICC_BPR_NS_binarypoint_START  (0)
#define SOC_GIC_NS_GICC_BPR_NS_binarypoint_END    (2)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_IAR_UNION
 结构说明  : GICC_IAR 寄存器结构定义。地址偏移量:0x200C，初值:0x000003FF，宽度:32
 寄存器说明: CPU接口中断确认寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  cpuid       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回发出中断请求的CPU接口编号；对于所有其他中断，该域返回0 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICC_IAR_UNION;
#endif
#define SOC_GIC_NS_GICC_IAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICC_IAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICC_IAR_cpuid_START        (10)
#define SOC_GIC_NS_GICC_IAR_cpuid_END          (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_EOIR_UNION
 结构说明  : GICC_EOIR 寄存器结构定义。地址偏移量:0x2010，初值:0x00000000，宽度:32
 寄存器说明: CPU接口中断结束寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOIINTID : 10; /* bit[0-9]  : 中断号，与GICC_IAR一致 */
        unsigned int  CPUID    : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域与GICC_IAR一致；对于所有其他中断，该域无效 */
        unsigned int  reserved : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICC_EOIR_UNION;
#endif
#define SOC_GIC_NS_GICC_EOIR_EOIINTID_START  (0)
#define SOC_GIC_NS_GICC_EOIR_EOIINTID_END    (9)
#define SOC_GIC_NS_GICC_EOIR_CPUID_START     (10)
#define SOC_GIC_NS_GICC_EOIR_CPUID_END       (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_RPR_UNION
 结构说明  : GICC_RPR 寄存器结构定义。地址偏移量:0x2014，初值:0x000000FF，宽度:32
 寄存器说明: CPU接口Running优先级寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Priority : 8;  /* bit[0-7] : 当前CPU接口的running优先级 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICC_RPR_UNION;
#endif
#define SOC_GIC_NS_GICC_RPR_Priority_START  (0)
#define SOC_GIC_NS_GICC_RPR_Priority_END    (7)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_HPPIR_UNION
 结构说明  : GICC_HPPIR 寄存器结构定义。地址偏移量:0x2018，初值:0x000003FF，宽度:32
 寄存器说明: CPU接口最高优先级pending中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID     : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回生成该中断的CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICC_HPPIR_UNION;
#endif
#define SOC_GIC_NS_GICC_HPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICC_HPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICC_HPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICC_HPPIR_CPUID_END        (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_IIDR_UNION
 结构说明  : GICC_IIDR 寄存器结构定义。地址偏移量:0x20FC，初值:0x0202043B，宽度:32
 寄存器说明: CPU接口识别寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  implementer : 12; /* bit[0-11] : 开发者
                                                       0x43B: ARM */
        unsigned int  revision    : 4;  /* bit[12-15]: CPU接口版本
                                                       0x0: Revision 0 */
        unsigned int  archversion : 4;  /* bit[16-19]: GIC体系结构版本
                                                       0x2: Version 2.0 */
        unsigned int  productid   : 12; /* bit[20-31]: 处理器
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICC_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICC_IIDR_implementer_START  (0)
#define SOC_GIC_NS_GICC_IIDR_implementer_END    (11)
#define SOC_GIC_NS_GICC_IIDR_revision_START     (12)
#define SOC_GIC_NS_GICC_IIDR_revision_END       (15)
#define SOC_GIC_NS_GICC_IIDR_archversion_START  (16)
#define SOC_GIC_NS_GICC_IIDR_archversion_END    (19)
#define SOC_GIC_NS_GICC_IIDR_productid_START    (20)
#define SOC_GIC_NS_GICC_IIDR_productid_END      (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICC_DIR_UNION
 结构说明  : GICC_DIR 寄存器结构定义。地址偏移量:0x3000，初值:0x00000000，宽度:32
 寄存器说明: CPU接口中断Deactivate寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域提供发起请求的处理器CPUID */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICC_DIR_UNION;
#endif
#define SOC_GIC_NS_GICC_DIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICC_DIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICC_DIR_CPUID_START        (10)
#define SOC_GIC_NS_GICC_DIR_CPUID_END          (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_HCR_UNION
 结构说明  : GICH_HCR 寄存器结构定义。地址偏移量:0x4000，初值:0x00000000，宽度:32
 寄存器说明: Hypervisor控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  En       : 1;  /* bit[0]    : virtual CPU interface的全局使能
                                                    0：virtual CPU interface去使能
                                                    1：virtual CPU interface使能 */
        unsigned int  UIE      : 1;  /* bit[1]    : underflow中断使能：
                                                    0：Maintenance中断去使能
                                                    1：当list register中最多只有一个entry被标记为有效中断时发出Maintenance中断 */
        unsigned int  LRENPIE  : 1;  /* bit[2]    : list register无entry中断使能：
                                                    0：Maintenance中断去使能
                                                    1：EOICount不为0时发出Maintenance中断 */
        unsigned int  NPIE     : 1;  /* bit[3]    : 无pending中断使能：
                                                    0：Maintenance中断去使能
                                                    1：list register中无pending中断时发出Maintenance中断 */
        unsigned int  VGrp0EIE : 1;  /* bit[4]    : VM使能group0中断使能：
                                                    0：Maintenance中断去使能
                                                    1：GICV_CTLR.EnableGrp0设为1时发出Maintenance中断 */
        unsigned int  VGrp0DIE : 1;  /* bit[5]    : VM去使能group0中断使能：
                                                    0：Maintenance中断去使能
                                                    1：GICV_CTLR.EnableGrp0设为0时发出Maintenance中断 */
        unsigned int  VGrp1EIE : 1;  /* bit[6]    : VM使能group1中断使能：
                                                    0：Maintenance中断去使能
                                                    1：GICV_CTLR.EnableGrp1设为1时发出Maintenance中断 */
        unsigned int  VGrp1DIE : 1;  /* bit[7]    : VM去使能group1中断使能：
                                                    0：Maintenance中断去使能
                                                    1：GICV_CTLR.EnableGrp1设为0时发出Maintenance中断 */
        unsigned int  reserved : 19; /* bit[8-26] : 保留 */
        unsigned int  EOICount : 5;  /* bit[27-31]: 在list register中没有entry的EOI数量 */
    } reg;
} SOC_GIC_NS_GICH_HCR_UNION;
#endif
#define SOC_GIC_NS_GICH_HCR_En_START        (0)
#define SOC_GIC_NS_GICH_HCR_En_END          (0)
#define SOC_GIC_NS_GICH_HCR_UIE_START       (1)
#define SOC_GIC_NS_GICH_HCR_UIE_END         (1)
#define SOC_GIC_NS_GICH_HCR_LRENPIE_START   (2)
#define SOC_GIC_NS_GICH_HCR_LRENPIE_END     (2)
#define SOC_GIC_NS_GICH_HCR_NPIE_START      (3)
#define SOC_GIC_NS_GICH_HCR_NPIE_END        (3)
#define SOC_GIC_NS_GICH_HCR_VGrp0EIE_START  (4)
#define SOC_GIC_NS_GICH_HCR_VGrp0EIE_END    (4)
#define SOC_GIC_NS_GICH_HCR_VGrp0DIE_START  (5)
#define SOC_GIC_NS_GICH_HCR_VGrp0DIE_END    (5)
#define SOC_GIC_NS_GICH_HCR_VGrp1EIE_START  (6)
#define SOC_GIC_NS_GICH_HCR_VGrp1EIE_END    (6)
#define SOC_GIC_NS_GICH_HCR_VGrp1DIE_START  (7)
#define SOC_GIC_NS_GICH_HCR_VGrp1DIE_END    (7)
#define SOC_GIC_NS_GICH_HCR_EOICount_START  (27)
#define SOC_GIC_NS_GICH_HCR_EOICount_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_VTR_UNION
 结构说明  : GICH_VTR 寄存器结构定义。地址偏移量:0x4004，初值:0x8C000003，宽度:32
 寄存器说明: VGIC类型寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ListRegs : 6;  /* bit[0-5]  : 实现了的list register的个数减1 */
        unsigned int  reserved : 20; /* bit[6-25] : 保留 */
        unsigned int  PREbits  : 3;  /* bit[26-28]: 实现了的抢占位数减1 */
        unsigned int  PRIbits  : 3;  /* bit[29-31]: 实现了的优先级位数减1 */
    } reg;
} SOC_GIC_NS_GICH_VTR_UNION;
#endif
#define SOC_GIC_NS_GICH_VTR_ListRegs_START  (0)
#define SOC_GIC_NS_GICH_VTR_ListRegs_END    (5)
#define SOC_GIC_NS_GICH_VTR_PREbits_START   (26)
#define SOC_GIC_NS_GICH_VTR_PREbits_END     (28)
#define SOC_GIC_NS_GICH_VTR_PRIbits_START   (29)
#define SOC_GIC_NS_GICH_VTR_PRIbits_END     (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_VMCR_UNION
 结构说明  : GICH_VMCR 寄存器结构定义。地址偏移量:0x4008，初值:0x004C0000，宽度:32
 寄存器说明: Virtual machine控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VMGrp0En  : 1;  /* bit[0]    : Alias of GICV_CTLR.EnableGrp0 */
        unsigned int  VMGrp1En  : 1;  /* bit[1]    : Alias of GICV_CTLR.EnableGrp1 */
        unsigned int  VMAckCtl  : 1;  /* bit[2]    : Alias of GICV_CTLR.AckCtl */
        unsigned int  VMFIQEn   : 1;  /* bit[3]    : Alias of GICV_CTLR.FIQEn */
        unsigned int  VMCBPR    : 1;  /* bit[4]    : Alias of GICV_CTLR.CBPR */
        unsigned int  reserved_0: 4;  /* bit[5-8]  : 保留 */
        unsigned int  VEM       : 1;  /* bit[9]    : Alias of GICV_CTLR.EOImode */
        unsigned int  reserved_1: 8;  /* bit[10-17]: 保留 */
        unsigned int  VMABP     : 3;  /* bit[18-20]: Alias of GICV_ABPR.Binary point */
        unsigned int  VMBP      : 3;  /* bit[21-23]: Alias of GICV_BPR.Binary point */
        unsigned int  reserved_2: 3;  /* bit[24-26]: 保留 */
        unsigned int  VMPriMask : 5;  /* bit[27-31]: Alias of GICV_PMR.Priority */
    } reg;
} SOC_GIC_NS_GICH_VMCR_UNION;
#endif
#define SOC_GIC_NS_GICH_VMCR_VMGrp0En_START   (0)
#define SOC_GIC_NS_GICH_VMCR_VMGrp0En_END     (0)
#define SOC_GIC_NS_GICH_VMCR_VMGrp1En_START   (1)
#define SOC_GIC_NS_GICH_VMCR_VMGrp1En_END     (1)
#define SOC_GIC_NS_GICH_VMCR_VMAckCtl_START   (2)
#define SOC_GIC_NS_GICH_VMCR_VMAckCtl_END     (2)
#define SOC_GIC_NS_GICH_VMCR_VMFIQEn_START    (3)
#define SOC_GIC_NS_GICH_VMCR_VMFIQEn_END      (3)
#define SOC_GIC_NS_GICH_VMCR_VMCBPR_START     (4)
#define SOC_GIC_NS_GICH_VMCR_VMCBPR_END       (4)
#define SOC_GIC_NS_GICH_VMCR_VEM_START        (9)
#define SOC_GIC_NS_GICH_VMCR_VEM_END          (9)
#define SOC_GIC_NS_GICH_VMCR_VMABP_START      (18)
#define SOC_GIC_NS_GICH_VMCR_VMABP_END        (20)
#define SOC_GIC_NS_GICH_VMCR_VMBP_START       (21)
#define SOC_GIC_NS_GICH_VMCR_VMBP_END         (23)
#define SOC_GIC_NS_GICH_VMCR_VMPriMask_START  (27)
#define SOC_GIC_NS_GICH_VMCR_VMPriMask_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_MISR_UNION
 结构说明  : GICH_MISR 寄存器结构定义。地址偏移量:0x4010，初值:0x00000000，宽度:32
 寄存器说明: Maintenance中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOI      : 1;  /* bit[0]   : EOI maintenance中断 */
        unsigned int  U        : 1;  /* bit[1]   : Underflow maintenance中断 */
        unsigned int  LRENP    : 1;  /* bit[2]   : list register无entry maintenance中断 */
        unsigned int  NP       : 1;  /* bit[3]   : list register中无pending maintenance中断 */
        unsigned int  VGrp0E   : 1;  /* bit[4]   : 使能group0 maintenance中断 */
        unsigned int  VGrp0D   : 1;  /* bit[5]   : 去使能group0 maintenance中断 */
        unsigned int  VGrp1E   : 1;  /* bit[6]   : 使能group1 maintenance中断 */
        unsigned int  VGrp1D   : 1;  /* bit[7]   : 去使能group1 maintenance中断 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICH_MISR_UNION;
#endif
#define SOC_GIC_NS_GICH_MISR_EOI_START       (0)
#define SOC_GIC_NS_GICH_MISR_EOI_END         (0)
#define SOC_GIC_NS_GICH_MISR_U_START         (1)
#define SOC_GIC_NS_GICH_MISR_U_END           (1)
#define SOC_GIC_NS_GICH_MISR_LRENP_START     (2)
#define SOC_GIC_NS_GICH_MISR_LRENP_END       (2)
#define SOC_GIC_NS_GICH_MISR_NP_START        (3)
#define SOC_GIC_NS_GICH_MISR_NP_END          (3)
#define SOC_GIC_NS_GICH_MISR_VGrp0E_START    (4)
#define SOC_GIC_NS_GICH_MISR_VGrp0E_END      (4)
#define SOC_GIC_NS_GICH_MISR_VGrp0D_START    (5)
#define SOC_GIC_NS_GICH_MISR_VGrp0D_END      (5)
#define SOC_GIC_NS_GICH_MISR_VGrp1E_START    (6)
#define SOC_GIC_NS_GICH_MISR_VGrp1E_END      (6)
#define SOC_GIC_NS_GICH_MISR_VGrp1D_START    (7)
#define SOC_GIC_NS_GICH_MISR_VGrp1D_END      (7)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_EISR0_UNION
 结构说明  : GICH_EISR0 寄存器结构定义。地址偏移量:0x4020，初值:0x00000000，宽度:32
 寄存器说明: EOI状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  List_register_ECO_status : 32; /* bit[0-31]: 0：对应的list register不含有EOI
                                                                   1：对应的list register不含有EOI */
    } reg;
} SOC_GIC_NS_GICH_EISR0_UNION;
#endif
#define SOC_GIC_NS_GICH_EISR0_List_register_ECO_status_START  (0)
#define SOC_GIC_NS_GICH_EISR0_List_register_ECO_status_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_ELSR0_UNION
 结构说明  : GICH_ELSR0 寄存器结构定义。地址偏移量:0x4030，初值:0x0000000F，宽度:32
 寄存器说明: 空list register状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  List_register_status : 32; /* bit[0-31]: 0：对应的list register含有有效中断
                                                               1：对应的list register不不含有有效中断 */
    } reg;
} SOC_GIC_NS_GICH_ELSR0_UNION;
#endif
#define SOC_GIC_NS_GICH_ELSR0_List_register_status_START  (0)
#define SOC_GIC_NS_GICH_ELSR0_List_register_status_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_APR0_UNION
 结构说明  : GICH_APR0 寄存器结构定义。地址偏移量:0x40F0，初值:0x00000000，宽度:32
 寄存器说明: 活跃优先级寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Active_priority_bits : 32; /* bit[0-31]: 决定对应位的抢占级别是否活跃：
                                                               0：不活跃
                                                               1：活跃 */
    } reg;
} SOC_GIC_NS_GICH_APR0_UNION;
#endif
#define SOC_GIC_NS_GICH_APR0_Active_priority_bits_START  (0)
#define SOC_GIC_NS_GICH_APR0_Active_priority_bits_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_LR0_UNION
 结构说明  : GICH_LR0 寄存器结构定义。地址偏移量:0x4100，初值:0x00000000，宽度:32
 寄存器说明: list register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : 当中断通过GICV_IAR响应时，该ID返回给Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: 当GICH_LR.HW=0时：
                                                      [19] EOI 指示中断是否为EOI maintenance中断
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      当GICH_LR.HW=1时：
                                                      代表Hypervisor送给distributor的物理中断ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: 保留 */
        unsigned int  Priority   : 5;  /* bit[23-27]: 优先级 */
        unsigned int  State      : 2;  /* bit[28-29]: 中断状态：
                                                      00：invalid
                                                      01：pending
                                                      10：active
                                                      11：pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : 虚拟中断是否为gruop1：
                                                      0：中断为group0
                                                      1：中断为group1 */
        unsigned int  HW         : 1;  /* bit[31]   : 虚拟中断是否为硬中断：
                                                      0：中断为软中断
                                                      1：中断为硬中断 */
    } reg;
} SOC_GIC_NS_GICH_LR0_UNION;
#endif
#define SOC_GIC_NS_GICH_LR0_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR0_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR0_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR0_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR0_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR0_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR0_State_START       (28)
#define SOC_GIC_NS_GICH_LR0_State_END         (29)
#define SOC_GIC_NS_GICH_LR0_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR0_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR0_HW_START          (31)
#define SOC_GIC_NS_GICH_LR0_HW_END            (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_LR1_UNION
 结构说明  : GICH_LR1 寄存器结构定义。地址偏移量:0x4104，初值:0x00000000，宽度:32
 寄存器说明: list register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : 当中断通过GICV_IAR响应时，该ID返回给Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: 当GICH_LR.HW=0时：
                                                      [19] EOI 指示中断是否为EOI maintenance中断
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      当GICH_LR.HW=1时：
                                                      代表Hypervisor送给distributor的物理中断ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: 保留 */
        unsigned int  Priority   : 5;  /* bit[23-27]: 优先级 */
        unsigned int  State      : 2;  /* bit[28-29]: 中断状态：
                                                      00：invalid
                                                      01：pending
                                                      10：active
                                                      11：pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : 虚拟中断是否为gruop1：
                                                      0：中断为group0
                                                      1：中断为group1 */
        unsigned int  HW         : 1;  /* bit[31]   : 虚拟中断是否为硬中断：
                                                      0：中断为软中断
                                                      1：中断为硬中断 */
    } reg;
} SOC_GIC_NS_GICH_LR1_UNION;
#endif
#define SOC_GIC_NS_GICH_LR1_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR1_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR1_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR1_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR1_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR1_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR1_State_START       (28)
#define SOC_GIC_NS_GICH_LR1_State_END         (29)
#define SOC_GIC_NS_GICH_LR1_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR1_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR1_HW_START          (31)
#define SOC_GIC_NS_GICH_LR1_HW_END            (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_LR2_UNION
 结构说明  : GICH_LR2 寄存器结构定义。地址偏移量:0x4108，初值:0x00000000，宽度:32
 寄存器说明: list register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : 当中断通过GICV_IAR响应时，该ID返回给Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: 当GICH_LR.HW=0时：
                                                      [19] EOI 指示中断是否为EOI maintenance中断
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      当GICH_LR.HW=1时：
                                                      代表Hypervisor送给distributor的物理中断ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: 保留 */
        unsigned int  Priority   : 5;  /* bit[23-27]: 优先级 */
        unsigned int  State      : 2;  /* bit[28-29]: 中断状态：
                                                      00：invalid
                                                      01：pending
                                                      10：active
                                                      11：pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : 虚拟中断是否为gruop1：
                                                      0：中断为group0
                                                      1：中断为group1 */
        unsigned int  HW         : 1;  /* bit[31]   : 虚拟中断是否为硬中断：
                                                      0：中断为软中断
                                                      1：中断为硬中断 */
    } reg;
} SOC_GIC_NS_GICH_LR2_UNION;
#endif
#define SOC_GIC_NS_GICH_LR2_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR2_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR2_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR2_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR2_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR2_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR2_State_START       (28)
#define SOC_GIC_NS_GICH_LR2_State_END         (29)
#define SOC_GIC_NS_GICH_LR2_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR2_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR2_HW_START          (31)
#define SOC_GIC_NS_GICH_LR2_HW_END            (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICH_LR3_UNION
 结构说明  : GICH_LR3 寄存器结构定义。地址偏移量:0x410C，初值:0x00000000，宽度:32
 寄存器说明: list register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : 当中断通过GICV_IAR响应时，该ID返回给Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: 当GICH_LR.HW=0时：
                                                      [19] EOI 指示中断是否为EOI maintenance中断
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      当GICH_LR.HW=1时：
                                                      代表Hypervisor送给distributor的物理中断ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: 保留 */
        unsigned int  Priority   : 5;  /* bit[23-27]: 优先级 */
        unsigned int  State      : 2;  /* bit[28-29]: 中断状态：
                                                      00：invalid
                                                      01：pending
                                                      10：active
                                                      11：pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : 虚拟中断是否为gruop1：
                                                      0：中断为group0
                                                      1：中断为group1 */
        unsigned int  HW         : 1;  /* bit[31]   : 虚拟中断是否为硬中断：
                                                      0：中断为软中断
                                                      1：中断为硬中断 */
    } reg;
} SOC_GIC_NS_GICH_LR3_UNION;
#endif
#define SOC_GIC_NS_GICH_LR3_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR3_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR3_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR3_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR3_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR3_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR3_State_START       (28)
#define SOC_GIC_NS_GICH_LR3_State_END         (29)
#define SOC_GIC_NS_GICH_LR3_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR3_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR3_HW_START          (31)
#define SOC_GIC_NS_GICH_LR3_HW_END            (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_CTLR_UNION
 结构说明  : GICV_CTLR 寄存器结构定义。地址偏移量:0x6000，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EnableGrp0 : 1;  /* bit[0]    : 使能由虚拟CPU interface向virtual machine发出Group0虚拟中断：
                                                      0：去使能Group0中断
                                                      1：使能Group0中断 */
        unsigned int  EnableGrp1 : 1;  /* bit[1]    : 使能由虚拟CPU interface向virtual machine发出Group1虚拟中断：
                                                      0：去使能Group1中断
                                                      1：使能Group1中断 */
        unsigned int  AckCtl     : 1;  /* bit[2]    : ARM不建议使用该bit
                                                      当最高优先级pending中断为Group1中断时，对GICV_IAR的读操作是否会引起CPU interface响应中断：
                                                      0：返回的ID为1022
                                                      1：返回Group1中断的ID */
        unsigned int  FIQEn      : 1;  /* bit[3]    : Group0中断是否为虚拟FIQ：
                                                      0：Group0中断为虚拟IRQ
                                                      1：Group0中断为虚拟FIQ */
        unsigned int  CBPR       : 1;  /* bit[4]    : Group0和Group1虚拟中断是否都由GICV_BPR控制：
                                                      0：GICV_BPR控制Group0虚拟中断，GICV_ABPR控制Group1虚拟中断
                                                      1：GICV_BPR控制Group0和Group1虚拟中断 */
        unsigned int  reserved   : 4;  /* bit[5-8]  : 保留 */
        unsigned int  EOImode    : 1;  /* bit[9]    : 影响GICV_EOIR,GICV_AEOIR,GICV_DIR
                                                      0：GICV_EOIR和GICV_AEOIR同时执行优先级drop与中断失效操作，GICV_DIR未知
                                                      1：GICV_EOIR和GICV_AEOIR只执行优先级drop，GICV_DIR只执行中断失效操作 */
        unsigned int  HW         : 22; /* bit[10-31]: 虚拟中断是否为硬中断：
                                                      0：中断为软中断
                                                      1：中断为硬中断 */
    } reg;
} SOC_GIC_NS_GICV_CTLR_UNION;
#endif
#define SOC_GIC_NS_GICV_CTLR_EnableGrp0_START  (0)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp0_END    (0)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp1_START  (1)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp1_END    (1)
#define SOC_GIC_NS_GICV_CTLR_AckCtl_START      (2)
#define SOC_GIC_NS_GICV_CTLR_AckCtl_END        (2)
#define SOC_GIC_NS_GICV_CTLR_FIQEn_START       (3)
#define SOC_GIC_NS_GICV_CTLR_FIQEn_END         (3)
#define SOC_GIC_NS_GICV_CTLR_CBPR_START        (4)
#define SOC_GIC_NS_GICV_CTLR_CBPR_END          (4)
#define SOC_GIC_NS_GICV_CTLR_EOImode_START     (9)
#define SOC_GIC_NS_GICV_CTLR_EOImode_END       (9)
#define SOC_GIC_NS_GICV_CTLR_HW_START          (10)
#define SOC_GIC_NS_GICV_CTLR_HW_END            (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_PMR_UNION
 结构说明  : GICV_PMR 寄存器结构定义。地址偏移量:0x6004，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine优先级mask寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 3;  /* bit[0-2] : 保留 */
        unsigned int  Priority : 5;  /* bit[3-7] : CPU接口优先级屏蔽的等级。当中断优先级高于此寄存器的值，则将中断送给目标处理器。最高支持256个优先级。
                                                   0x00-0xFF(0-255): 256个等级
                                                   0x00-0xFE(0-254): 128个等级（偶数）
                                                   0x00-0xFC(0-252): 64个等级（步进为4）
                                                   0x00-0xF8(0-248): 32个等级（步进为8）
                                                   0x00-0xF0(0-240): 16个等级（步进为16）
                                                   当配置为0xFF时，表示所有中断都不屏蔽 */
        unsigned int  reserved_1: 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_PMR_UNION;
#endif
#define SOC_GIC_NS_GICV_PMR_Priority_START  (3)
#define SOC_GIC_NS_GICV_PMR_Priority_END    (7)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_BPR_UNION
 结构说明  : GICV_BPR 寄存器结构定义。地址偏移量:0x6008，初值:0x00000002，宽度:32
 寄存器说明: Virtual machine Binary point寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BinaryPoint : 3;  /* bit[0-2] : 控制8-bit中断优先级域如何对应用于定义中断抢占操作的group优先级域，以及子优先级域
                                                      注：非安全访问，默认值为0x3 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_BPR_UNION;
#endif
#define SOC_GIC_NS_GICV_BPR_BinaryPoint_START  (0)
#define SOC_GIC_NS_GICV_BPR_BinaryPoint_END    (2)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_IAR_UNION
 结构说明  : GICV_IAR 寄存器结构定义。地址偏移量:0x600C，初值:0x000003FF，宽度:32
 寄存器说明: Virtual machine中断响应寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回发出中断请求的CPU接口编号；对于所有其他中断，该域返回0 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_IAR_UNION;
#endif
#define SOC_GIC_NS_GICV_IAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_IAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_IAR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_IAR_CPUID_END          (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_EOIR_UNION
 结构说明  : GICV_EOIR 寄存器结构定义。地址偏移量:0x6010，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine EOI寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOIINTID : 10; /* bit[0-9]  : 中断号，与GICC_IAR一致 */
        unsigned int  CPUID    : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域与GICC_IAR一致；对于所有其他中断，该域无效 */
        unsigned int  reserved : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_EOIR_UNION;
#endif
#define SOC_GIC_NS_GICV_EOIR_EOIINTID_START  (0)
#define SOC_GIC_NS_GICV_EOIR_EOIINTID_END    (9)
#define SOC_GIC_NS_GICV_EOIR_CPUID_START     (10)
#define SOC_GIC_NS_GICV_EOIR_CPUID_END       (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_RPR_UNION
 结构说明  : GICV_RPR 寄存器结构定义。地址偏移量:0x6014，初值:0x000000FF，宽度:32
 寄存器说明: Virtual machine Running Priority寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUID    : 8;  /* bit[0-7] : 当前CPU接口的running优先级 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_RPR_UNION;
#endif
#define SOC_GIC_NS_GICV_RPR_CPUID_START     (0)
#define SOC_GIC_NS_GICV_RPR_CPUID_END       (7)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_HPPIR_UNION
 结构说明  : GICV_HPPIR 寄存器结构定义。地址偏移量:0x6018，初值:0x000003FF，宽度:32
 寄存器说明: Virtual machine 最高优先级pending中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID     : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回生成该中断的CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_HPPIR_UNION;
#endif
#define SOC_GIC_NS_GICV_HPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICV_HPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICV_HPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICV_HPPIR_CPUID_END        (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_ABPR_UNION
 结构说明  : GICV_ABPR 寄存器结构定义。地址偏移量:0x601C，初值:0x00000003，宽度:32
 寄存器说明: Virtual machine aliased Binary point寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BinaryPoint : 3;  /* bit[0-2] : 控制8-bit中断优先级域如何对应用于定义中断抢占操作的group优先级域，以及子优先级域 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_ABPR_UNION;
#endif
#define SOC_GIC_NS_GICV_ABPR_BinaryPoint_START  (0)
#define SOC_GIC_NS_GICV_ABPR_BinaryPoint_END    (2)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_AIAR_UNION
 结构说明  : GICV_AIAR 寄存器结构定义。地址偏移量:0x6020，初值:0x000003FF，宽度:32
 寄存器说明: Virtual machine aliased中断响应寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回发出中断请求的CPU接口编号；对于所有其他中断，该域返回0 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_AIAR_UNION;
#endif
#define SOC_GIC_NS_GICV_AIAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_AIAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_AIAR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_AIAR_CPUID_END          (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_AEOIR_UNION
 结构说明  : GICV_AEOIR 寄存器结构定义。地址偏移量:0x6024，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine aliased EOI寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号，与GICC_IAR一致 */
        unsigned int  CPUID       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域与GICC_IAR一致；对于所有其他中断，该域无效 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_AEOIR_UNION;
#endif
#define SOC_GIC_NS_GICV_AEOIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_AEOIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_AEOIR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_AEOIR_CPUID_END          (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_AHPPIR_UNION
 结构说明  : GICV_AHPPIR 寄存器结构定义。地址偏移量:0x6028，初值:0x000003FF，宽度:32
 寄存器说明: Virtual machine aliased 最高优先级pending中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : 如果是Group1中断，则返回中断号；否则，返回0x3FF */
        unsigned int  CPUID     : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域返回生成该中断的CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_GIC_NS_GICV_AHPPIR_UNION;
#endif
#define SOC_GIC_NS_GICV_AHPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICV_AHPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICV_AHPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICV_AHPPIR_CPUID_END        (12)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_APR0_UNION
 结构说明  : GICV_APR0 寄存器结构定义。地址偏移量:0x60D0，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine活跃优先级寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Active_priority_bits : 32; /* bit[0-31]: 决定对应位的抢占级别是否活跃：
                                                               0：不活跃
                                                               1：活跃 */
    } reg;
} SOC_GIC_NS_GICV_APR0_UNION;
#endif
#define SOC_GIC_NS_GICV_APR0_Active_priority_bits_START  (0)
#define SOC_GIC_NS_GICV_APR0_Active_priority_bits_END    (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_IIDR_UNION
 结构说明  : GICV_IIDR 寄存器结构定义。地址偏移量:0x60FC，初值:0x0202043B，宽度:32
 寄存器说明: Virtual machine CPU接口识别寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Implementer : 12; /* bit[0-11] : 开发者
                                                       0x43B: ARM */
        unsigned int  Revision    : 4;  /* bit[12-15]: CPU接口版本
                                                       0x0: Revision 0 */
        unsigned int  ArchVersion : 4;  /* bit[16-19]: GIC体系结构版本
                                                       0x2: Version 2.0 */
        unsigned int  ProductID   : 12; /* bit[20-31]: 处理器
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICV_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICV_IIDR_Implementer_START  (0)
#define SOC_GIC_NS_GICV_IIDR_Implementer_END    (11)
#define SOC_GIC_NS_GICV_IIDR_Revision_START     (12)
#define SOC_GIC_NS_GICV_IIDR_Revision_END       (15)
#define SOC_GIC_NS_GICV_IIDR_ArchVersion_START  (16)
#define SOC_GIC_NS_GICV_IIDR_ArchVersion_END    (19)
#define SOC_GIC_NS_GICV_IIDR_ProductID_START    (20)
#define SOC_GIC_NS_GICV_IIDR_ProductID_END      (31)


/*****************************************************************************
 结构名    : SOC_GIC_NS_GICV_DIR_UNION
 结构说明  : GICV_DIR 寄存器结构定义。地址偏移量:0x7000，初值:0x00000000，宽度:32
 寄存器说明: Virtual machine CPU接口中断Deactivate寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : 中断号 */
        unsigned int  CPUID       : 3;  /* bit[10-12]: 对于多核系统中的SGI中断，该域提供发起请求的处理器CPUID */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICV_DIR_UNION;
#endif
#define SOC_GIC_NS_GICV_DIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_DIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_DIR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_DIR_CPUID_END          (12)






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

#endif /* end of soc_gic_ns_interface.h */
